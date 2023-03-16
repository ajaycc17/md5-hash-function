#include "./md5_header.h"

// MD buffers
uint32_t A, B, C, D;

// function to initialize MD buffers
void initialize()
{
	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;
}

// function for circular left shift
void md5(uint8_t *in_msg, size_t in_len)
{

	// initialize MD buffers
	void initialize();

	// copy of MD buffers
	uint32_t a = A;
	uint32_t b = B;
	uint32_t c = C;
	uint32_t d = D;

	// calculate length of the message after padding
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
}

int main()
{
	char *msg = "ajay1137";
	size_t msg_len = strlen(msg);

	// invoke the md5 function
	md5(msg, msg_len);

	// hash
	printf("Hash for \"%s\" is: %x%x%x%x\n", msg, A, B, C, D);

	// 97 106 97 121 = 01100001 01101010 01100001 01111001 (ajay)
	// in little endian = 01111001 01100001 01101010 01100001 (121 97 106 97 - yaja)
	// need to reverse the little endianness
	uint8_t *temp = (uint8_t *)&A;
	printf("MD5 Hash for \"%s\" is: %x%x%x%x", msg, temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&B;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&C;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
	temp = (uint8_t *)&D;
	printf("%x%x%x%x", temp[0], temp[1], temp[2], temp[3]);
}
