#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// initial MD buffers
uint32_t A, B, C, D;
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// function for circular left shift

void md5(uint8_t *in_msg, size_t in_len)
{
	// define the constants
	uint32_t t[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	// initialize MD buffers
	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;

	// copy of MD buffers
	uint32_t a = A;
	uint32_t b = B;
	uint32_t c = C;
	uint32_t d = D;

	// calculate length of the message after padding --------- to be derived
	// here it should be 448 bits = 448/8 = 56 bytes
	int pad_len = 56;

	// for length bit we need to add 64 bits = 64/8 = 8 bytes
	// 56 + 8 = 64 bytes
	uint8_t new_msg[64] = {0};

	// copy the messages ascii value to the new message
	for (int i = 0; i < in_len; i++)
	{
		new_msg[i] = in_msg[i];
	}

	// add a 1 just after the message for the beginning of padding bits
	// ascii of 128 = 10000000
	new_msg[in_len] = 128;

	// length bit: here a string is taken hence each character is of 1 byte
	// thus, 8*in_len = length of message
	uint8_t len_bit = 8 * in_len;

	// add the length bit to the new message
	memcpy(new_msg + pad_len, &len_bit, 1);

	// a loop for accessing 512-bit blocks
	// a loop for accessing all 16 32-bit blocks in the 512-bit block
	// here only one 512-bit block is there -> skipping the outer loop
	uint32_t i;
	uint32_t *lit_end_msg = (uint32_t *)(new_msg);

	// print the new message in
	for (i = 0; i < 64; i++)
	{
		uint32_t f, g;
		if (i < 16)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (d & b) | ((~d) & c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = c ^ (b | (~d));
			g = (7 * i) % 16;
		}

		// swap buffers
		f = f + a + t[i] + lit_end_msg[g];
		a = d;
		d = c;
		c = b;
		b = b + LEFTROTATE(f, s[i]);
	}

	// Add this chunk's hash to result so far:
	A += a;
	B += b;
	C += c;
	D += d;

	// // print the new message
	// for (int i = 0; i < 64; i++)
	// {
	// 	printf("%d: %d\n", i + 1, new_msg[i]);
	// }
	// // print the little endian message
	// // 97 106 97 121 = 01100001 01101010 01100001 01111001 (ajay)
	// // in lit endian = 01111001 01100001 01101010 01100001 (121 97 106 97 - yaja)
	// for (int i = 0; i < 64; i++)
	// {
	// 	printf("%d: %d\n", i + 1, lit_end_msg[i]);
	// }
}

int main()
{
	char *msg = "ajay";
	size_t msg_len = strlen(msg);

	// invoke the md5 function
	md5(msg, msg_len);

	// hash
	// printf("Hash: %x%x%x%x\n", A, B, C, D);
	// need to reverse the little endianness
	uint8_t *temp = (uint8_t *)&A;
	printf("MD5 Hash: %x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&B;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&C;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&D;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
}
