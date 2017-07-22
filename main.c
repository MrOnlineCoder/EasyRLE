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

#include <string.h>

#include "rle.h"

int main(int argc, char* argv[]) {
	int flag = RLE_INVALID;
	char* file = NULL;
	char* out = NULL;

    printf("* %s %s by %s *\n", RLE_NAME, RLE_VERSION, RLE_AUTHOR);

	if (argc == 1) {
        printf("%s\n", RLE_HELP);
        return 0;
	}

	for (int i = 0;i<argc;i++) {
		if (strcmp(argv[i], "--encode") == 0 || strcmp(argv[i], "-e") == 0) {
			flag = RLE_ENCODE;
			continue;
		}

		if (strcmp(argv[i], "--decode") == 0 || strcmp(argv[i], "-d") == 0) {
			flag = RLE_DECODE;
			continue;
		}

		if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i+1 >= argc) {
                printf("ERROR: %s\n", RLE_ERR_INVALID_ARGS);
                return 1;
            }
            out = argv[++i];
			continue;
		}

		file = argv[i];
	}

	return rle_process(flag, file, out);
}
