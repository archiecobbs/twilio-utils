
/*
 * Copyright 2013 Archie L. Cobbs <archie.cobbs@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <arpa/inet.h>
#include "config.h"

#define DEFAULT_INPUT_ENCODING     "UTF-8"

static int calculate_length(int gsm_bits, int utf16_bits, int need_utf16);
static int gsm338len(uint16_t unicode);
static void usage(void);

int
main(int argc, char **argv)
{

    // Configuration
    const char *input_encoding = DEFAULT_INPUT_ENCODING;
    const char *input_desc = "(stdin)";
    FILE *input = stdin;
    int limit = -1;

    // iconv(3) stuff
    iconv_t icd = NULL;
    char ibuf[64];
    char obuf[64];
    char *iptr;
    char *optr;
    size_t iremain;
    size_t oremain;

    // State
    int utf16_bits = 0;
    int gsm_bits = 0;
    int need_utf16 = 0;
    int input_mark;
    int input_count;

    // Copy buffer
    char *copy_buf = NULL;
    size_t copy_len = 0;
    size_t copy_alloc = 0;

    // Misc
    int r;

    // Parse command line
    while ((r = getopt(argc, argv, "i:hr:t:")) != -1) {
        switch (r) {
        case 'i':
            input_encoding = optarg;
            break;
        case 't':
            if ((copy_buf = realloc(copy_buf, 256)) == NULL)
                err(1, "malloc");
            copy_alloc = 256;
            // FALLTHROUGH
        case 'r':
            if (limit != -1)
                errx(1, "only one of `-r' or `-t' is allowed");
            limit = atoi(optarg);
            if (limit < 0)
                errx(1, "invalid value `%s' for `-%c'", optarg, (char)r);
            break;
        case 'h':
        case '?':
            usage();
            return 0;
        default:
            usage();
            return 1;
        }
    }
    switch (argc - optind) {
    case 1:
        if ((input = fopen(argv[optind], "r")) == NULL)
            err(1, "%s", argv[optind]);
        input_desc = argv[optind];
        break;
    case 0:
        break;
    default:
        usage();
        return 1;
    }

    // Set up character decoder
    if ((icd = iconv_open("UTF-16BE", input_encoding)) == (iconv_t)-1)
        err(1, "iconv");

    // Initialize state
    iptr = ibuf;
    optr = obuf;
    iremain = 0;
    oremain = sizeof(obuf);
    input_mark = 0;
    input_count = 0;

    // Process input
    while ((r = fgetc(input)) != EOF) {
        char *optr2;
        size_t icr;
        int bytes;

        // Update input count
        input_count++;

        // Copy input into copy buffer for the `-t' case
        if (copy_buf != NULL) {
            if (copy_alloc == copy_len) {
                if ((copy_buf = realloc(copy_buf, copy_alloc * 2)) == NULL)
                    err(1, "malloc");
                copy_alloc *= 2;
            }
            copy_buf[copy_len++] = (char)r;
        }

        // Add to input buffer and attempt to convert input buffer into one or more output characters
        iptr[iremain++] = (char)r;
        icr = iconv(icd, &iptr, &iremain, &optr, &oremain);

        // Shift and reset input buffer, based on what was consumed
        memmove(ibuf, iptr, iremain);
        iptr = ibuf;

        // Check result
        if (icr == (size_t)-1) {
            switch (errno) {
            case EINVAL:                // more input needed for the next conversion
                continue;
            case EILSEQ:
                errx(1, "%s: offset %d: invalid multibyte sequence", input_desc, input_count);
            default:
                err(1, "iconv");
            }
        }

        // Process entire output buffer
        for (optr2 = obuf; optr2 < optr; optr2 += 2) {
            uint16_t unicode;
            int gsm_len;

            memcpy(&unicode, optr2, 2);
            unicode = ntohs(unicode);
            if (!need_utf16) {
                gsm_len = gsm338len(unicode);
                if (gsm_len == -1)
                    need_utf16 = 1;
                else
                    gsm_bits += gsm_len * 7;
            }
            utf16_bits += 16;
        }
        bytes = calculate_length(gsm_bits, utf16_bits, need_utf16);

        // Reset output buffer
        optr = obuf;
        oremain = sizeof(obuf);

        // If `-r' in effect, check whether we have just gone over the limit
        if (limit != -1 && bytes > limit)
            break;

        // We have not gone over the limit, so update mark
        input_mark = input_count;
    }
    if (ferror(input))
        err(1, "%s", input_desc);

    // Output result
    if (limit != -1) {
        if (copy_buf != NULL)
            fwrite(copy_buf, 1, input_mark, stdout);
        else
            printf("%d\n", input_mark);
    } else
        printf("%d\n", calculate_length(gsm_bits, utf16_bits, need_utf16));

    // Done
    iconv_close(icd);
    return 0;
}

static int
calculate_length(int gsm_bits, int utf16_bits, int need_utf16)
{
    int bits = need_utf16 ? utf16_bits : gsm_bits;
    int bytes = (bits + 7) / 8;
    return bytes;
}

static void
usage(void)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\tsmslen [-i encoding] [filename]\n");
    fprintf(stderr, "\tsmslen -r limit [-i encoding] [filename]\n");
    fprintf(stderr, "\tsmslen -t limit [-i encoding] [filename]\n");
    fprintf(stderr, "\nThe first form prints the number of bytes to encode the input in an SMS message.\n");
    fprintf(stderr, "\nThe `-r' form inverts the calcaulation, printing the number of input bytes that\n");
    fprintf(stderr, "will fit under the given limit on encoded length.\n");
    fprintf(stderr, "\nThe `-t' form performs the same calculation as `-r' but copies the input to the\n");
    fprintf(stderr, "output, truncating it when the calculated limit is reached.\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -i    Set input character encoding (default `%s')\n", DEFAULT_INPUT_ENCODING);
    fprintf(stderr, "  -r    Print the number of input bytes that can fit under the given limit\n");
    fprintf(stderr, "  -t    Copy to stdout all the input bytes that can fit under the given limit\n");
    fprintf(stderr, "  -h    Show this help message\n");
}

//
// Get the number of bytes in the GSM 03.38 default 7-bit encoding of the given character, if such exists.
// Note that each "byte" only uses up seven bits in this encoding.
//
// Returns GSM 03.38 encoded characater length in bytes: either 1 or 2, or -1 if character does not have a GSM 03.38 encoding
//
static int
gsm338len(uint16_t unicode)
{
    switch (unicode) {
    case '\r': case '\n': case ' ':
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(':
    case ')': case '*': case '+': case ',': case '-': case '.': case '/':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case ':': case ';': case '<': case '=': case '>': case '?': case '@':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K':
    case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
    case 'W': case 'X': case 'Y': case 'Z': case '_': case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q':
    case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 0x00a1: case 0x00a3: case 0x00a4: case 0x00a5: case 0x00a7: case 0x00bf: case 0x00c4:
    case 0x00c5: case 0x00c6: case 0x00c7: case 0x00c9: case 0x00d1: case 0x00d6: case 0x00d8:
    case 0x00dc: case 0x00df: case 0x00e0: case 0x00e4: case 0x00e5: case 0x00e6: case 0x00e8:
    case 0x00e9: case 0x00ec: case 0x00f1: case 0x00f2: case 0x00f6: case 0x00f8: case 0x00f9:
    case 0x00fc: case 0x0393: case 0x0394: case 0x0398: case 0x039b: case 0x039e: case 0x03a0:
    case 0x03a3: case 0x03a6: case 0x03a8: case 0x03a9:
        return 1;
    case '|': case '^': case '{': case '}': case '[': case '~': case ']': case '\\': case '\f': case 0x20ac:
        return 2;
    default:
        return -1;
    }
}

