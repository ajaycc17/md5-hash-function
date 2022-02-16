#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

string decToBinary(int n)
{
    // array to store binary number
    string bin = "";
    // counter for binary array
    while (n > 0)
    {
        // storing remainder in binary array
        (n % 2) ? bin.push_back('1') : bin.push_back('0');
        n = n / 2;
    }
    // printing binary array in reverse order
    reverse(bin.begin(), bin.end());
    cout << bin << " ";
    return bin;
}

string strToBinary(string s)
{
    int n = s.length();
    string final = "";
    for (int i = 0; i <= n; i++)
    {
        // convert each char to ASCII value
        int val = int(s[i]);
        // Convert ASCII value to binary
        string bin = "";
        while (val > 0)
        {
            (val % 2) ? bin.push_back('1') : bin.push_back('0');
            val /= 2;
        }
        reverse(bin.begin(), bin.end());
        final = final + bin;
        cout << bin << " ";
    }
    return final;
}
string* divideString(string s, int n)
{
    int num = s.length()/n;
    string* block = new string[num];
    int p = n;
    int j = 0;
    for (int i = 0; i<num;i++)
    {
        block[i] = s.substr(j,p);
        cout<<"\n"<<block[i];
        j = n + 1;
        p = p + n;
    }
    return block;
}

int main()
{
    string message = "ajay";
    string bin = strToBinary(message);
    cout << bin;

    uint32_t t[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    int s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // initialize MD buffers
    uint32_t A = 0x67452301;
    uint32_t B = 0xefcdab89;
    uint32_t C = 0x98badcfe;
    uint32_t D = 0x10325476;
    // copy MD buffers to another variable
    uint32_t a = A;
    uint32_t b = B;
    uint32_t c = C;
    uint32_t d = D;

    // step 1 : padding bits
    int len = bin.length();
    int original_len = len;
    int p = len / 512;
    int q = len % 512;
    int r = 0;
    if (q <= 448 & q >= 0)
    {
        r = ((p + 1) * 512 - len) - 64;
    }
    else
    {
        r = ((p + 2) * 512 - len) - 64;
    }
    if (r != 0)
    {
        bin = bin + "1";
        for (int i = 0; i < r - 1; i++)
        {
            bin = bin + "0";
        }
    }
    cout << bin << " " << bin.length();

    // step 2 : length bits
    int len64 = pow(2, 64);
    int lenbit = 256 % len64;
    cout << "\n"
         << lenbit << "\n";
    string len_bin = decToBinary(lenbit);
    if (len_bin.length() < 64)
    {
        int x = 64 - len_bin.length();
        for (int i = 0; i < x; i++)
        {
            len_bin = len_bin + "0";
        }
    }
    bin = bin + len_bin;
    cout<<"\n"<<bin<<"\n";
    // step 3: divide into 512 bit blocks
    int bsize = 512;
    int sbsize = 32;
    string *block = divideString(bin, sbsize);
    int num = bin.length()/sbsize;
    for (int i = 0; i<num; i++)
    {
        cout<<"\n"<<block[i]<<"\n";     // check
        // step 4: divide into 16 subblocks of 32 bit each
        // string *sblock = new string[num];
        // sblock[i] = divideString(bin, sbsize);

    }

    return 0;
}
