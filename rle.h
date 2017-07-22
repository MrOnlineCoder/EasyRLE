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

#ifndef EASYRLE_H
#define EASYRLE_H

#include <stdio.h>

#define RLE_ENCODE 0
#define RLE_DECODE 1
#define RLE_INVALID -1

#define RLE_VERSION "1.0.0"
#define RLE_NAME "EasyRLE"
#define RLE_AUTHOR "MrOnlineCoder"

#define RLE_HELP "Usage: easyrle <--encode|-e|--decode|-d> <--output|-o> output_file input_file"

#define RLE_ERR_INVALIDMODE "Unknown mode. Use --encode or --decode flags to specify mode"
#define RLE_ERR_NOFILE "Cannot open input file"
#define RLE_ERR_NOFILEOUT "Cannot open output file"
#define RLE_ERR_INVALID_ARGS "Invalid arguments count."

#define RLE_MSG_DONE_FAST "Processed %d bytes. Operation finished in less than a second\n"
#define RLE_MSG_DONE "Processed %d bytes. Operation finished in %d seconds\n"

typedef unsigned char RLE_BYTE;

int rle_encode();

int rle_decode();

int rle_process(int mode, char* file, char* file_out);

#endif
