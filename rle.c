/*
    MIT License

    Copyright (c) 2017 Nikita Kogut (github.com/MrOnlineCoder)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdio.h>
#include <time.h>
#include <limits.h>

#include "rle.h"

char* filename = NULL;
FILE* fp = NULL;
FILE* fp_out = NULL;

static void rle_write_block(RLE_BYTE* buff, RLE_BYTE* count) {
    fwrite(count, sizeof(RLE_BYTE), 1, fp_out);
    fwrite(buff, sizeof(RLE_BYTE), 1, fp_out);
}

int rle_process(int mode, char* file, char* file_out) {
    time_t start = time(NULL);
    if (mode == RLE_INVALID) {
        printf("ERROR: %s\n", RLE_ERR_INVALIDMODE);
        return 1;
    }
    filename = file;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror(RLE_ERR_NOFILE);
        return 1;
    }

    fp_out = fopen(file_out, "w");
    if (fp_out == NULL) {
        perror(RLE_ERR_NOFILEOUT);
        return 1;
    }
    int bytes = 0;

    if (mode == RLE_ENCODE) {
        bytes = rle_encode();
    } else if (mode == RLE_DECODE) {
        bytes = rle_decode();
    }
    time_t end = time(NULL);
    time_t time = end - start;
    if (time == 0) {
        printf(RLE_MSG_DONE_FAST, bytes);
    } else {
        printf(RLE_MSG_DONE, bytes, end - start);
    }


    fclose(fp);
    fclose(fp_out);
    return 0;
}

int rle_encode() {
    size_t bytes = 0;
    size_t size = 0;

    RLE_BYTE buffer = 0;
    RLE_BYTE byte = 0;
    RLE_BYTE count = 1;

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    /* Read the first byte */
    fread(&buffer, sizeof(RLE_BYTE), 1, fp);
    byte = buffer;
    bytes++;

    while (fread(&buffer, sizeof(RLE_BYTE), 1, fp) != 0) {
        if (byte == buffer) {
            count++;
            if (count == UCHAR_MAX) {
                rle_write_block(&byte, &count);
                count = 0;
            }
        } else {
            rle_write_block(&byte, &count);
            byte = buffer;
            count = 1;
        }
        bytes++;
    }

    printf("\r\n");

    /* Write the last block after EOF */
    rle_write_block(&byte, &count);

    return bytes;
}


int rle_decode() {
    size_t bytes = 0;
    size_t size = 0;

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);


    RLE_BYTE chunk[2]; /* first byte is count, second byte is value */

    while (fread(&chunk, sizeof(RLE_BYTE), 2, fp) != 0) {
        for (int i = 0; i < chunk[0]; i++) {
            fwrite(&chunk[1], sizeof(RLE_BYTE), 1, fp_out);
        }

        bytes += 2;
    }

    printf("\r\n");

    return bytes;
}

