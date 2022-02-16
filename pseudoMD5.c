// Pseudocode:

// declare arrays of constants t[64] and s[64]
// initialize MD buffers
// A = 0x67452301
// B = 0xefcdab89
// C = 0x98badcfe
// D = 0x10325476
// copy MD buffers to another variable
// a = A
// b = B
// c = C
// d = D
// Check the file/message size in bits and then, ----------------------------step 1
// get the size of message(m) and compute:
// p = len/512
// q = len % 512
// if q<64:
    // r = ((1+a)*512-m)-64
// else if q==64:
    // r = 0
// else:
    // if ((1+a)*512-m)<64:
        // r = ((a+2)*512-m)-64
    // else:
        // r = ((1+a)*512-m)-64
// if r != 0:
    // add one 1 and (r-1) 0's to m and put it into m1
// append length bits (original length mod 2^64)-----------------------------step 2
// Split m2 into 512-bit blocks----------------------------------------------step 3
// for each 512-bit block
    // Further split each 512-bit block into 16 sub-blocks of 32-bit each----step 4
    // for (i=0 to 63):
        // if (i=0 to i=15):
        // res = (b & c) | (!b & d)
        // if (i=16 to i=31):
        // res = (b & d) | (c & !d)
        // if (i=32 to i=47):
        // res = b ^ c ^ d
        // if (i=48 to i=63):
        // res = c ^ (b | !d)

        // res = a + res + m1[i] + t[i]
        // a = d
        // d = c
        // c = b
        // b = b + CLS(res, s[i])
    // come out of for inner loop
    // a = a + A
    // b = b + B
    // c = c + C
    // d = d + D
// come out of outer for loop
// hash = concatenate(a,b,c,d)---------------------------------------------final output


// code (incomplete)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *stringToBinary(char *s)
{
    if (s == NULL)
        return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len * 8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for (size_t i = 0; i < len; ++i)
    {
        char ch = s[i];
        for (int j = 7; j >= 0; --j)
        {
            if (ch & (1 << j))
            {
                strcat(binary, "1");
            }
            else
            {
                strcat(binary, "0");
            }
        }
    }
    return binary;
}

void main()
{
    int t[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    int s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // initialize MD buffers
    int A = 0x67452301;
    int B = 0xefcdab89;
    int C = 0x98badcfe;
    int D = 0x10325476;
    // copy MD buffers to another variable
    int a = A;
    int b = B;
    int c = C;
    int d = D;

    int len =  sizeof(m) * 8;
    int p = len / 512;
    int q = len % 512;
    int r = 0;
    if (q <= 64)
    {
        r = ((1 + a) * 512 - len) - 64;
    }
    else if (q > 64)
    {
        if (((1 + a) * 512 - m) < 64)
        {
            r = ((a + 2) * 512 - m) - 64;
        }
        else
        {
            r = ((1 + a) * 512 - m) - 64;
        }
    }
    // if (r!=0)
    // {
    //     // first --number or text should be in binary
    // }
}