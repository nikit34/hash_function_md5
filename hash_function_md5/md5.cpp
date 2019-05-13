#include <iostream>
#include <string>

using namespace std;

typedef unsigned int uint;  // for to shorten

std::string to_hex(uint value);
uint F(uint X, uint Y, uint Z);
uint G(uint X, uint Y, uint Z);
uint H(uint X, uint Y, uint Z);
uint I(uint X, uint Y, uint Z);
uint rotate_left(uint value, int shift);
std::string get_md5(string in);

string to_hex(uint value) {
	string out;
	unsigned char hex;
	char hex_res[3];  // here we pass the value - split into three parts
	while (value) {
		hex = value % 256;
		_itoa_s(hex, hex_res, 16);
		if (hex_res[1] == '\0') {
			hex_res[1] = hex_res[0];  // second - body
			hex_res[0] = '0';  // empty value
			hex_res[2] = '\0'; // last with zero
		}
		out.append(hex_res);
		value /= 256;
	}  // for 'dec' value of two characters
	return out;
}

uint F(uint X, uint Y, uint Z) {
	return ((X & Y) | ((~X) & Z));
}

uint G(uint X, uint Y, uint Z) {
	return (X & Z) | (Y & (~Z));
}

uint H(uint X, uint Y, uint Z) {
	return X ^ Y^ Z;
}

uint I(uint X, uint Y, uint Z) {
	return Y ^ (X | (~Z));
}

// циклический сдвиг влево
uint rotate_left(uint value, int shift) {
	return value << shift | value >> (32 - shift);
}

string get_md5(string in) {
	int length = in.length();;  // get length input message 
	int rest = length%64;  // divide by 64 bits
	int size = 0;  // size first two messages


	if (rest < 56) 
		size = length - rest + 56 + 8;  // adjust the size so that it would be a multiple of 64 (+8 bytes for the 2nd step)
	else 
		size = length + 64 - rest + 56 + 8;  // same

	unsigned char* msg_for_decode = new unsigned char[size];

	for (int i = 0; i < length; i++) 
		msg_for_decode[i] = in[i];  // replace the input message with a coded

	msg_for_decode[length] = 0x80;  // set one bit in end

	for (int i = length + 1; i < size; i++)  // excess is reset 
		msg_for_decode[i] = 0; 

	__int64 bit_length = (uint)(length) * 8;  // lenght in bits

	for (int i = 0; i < 8; i++)  // last eight bits
		msg_for_decode[size - 8 + i] = (unsigned char)(bit_length >> i * 8);  // we fill with 64-bit representation before alignment

	uint A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;  // Initialize the initial values ​​of the registers
	uint T[64];  // data table

	for (int i = 0; i < 64; i++) // all table by algorithm
		T[i] = uint(pow(2, 32) * fabs(sin(i + 1))); 
			
	uint * X = (uint*)(msg_for_decode);  // drive the message msg_for_decode into the X array

	uint AA, BB, CC, DD;

	for (int i = 0; i<64; i++) {
	AA = A; BB = B; CC = C; DD = D;

	//raund 1
	A = B + rotate_left((A + F(B,C,D) + X[i + 0] + T[0]), 7);
	D = A + rotate_left((D + F(A,B,C) + X[i + 1] + T[1]), 12);
	C = D + rotate_left((C + F(D,A,B) + X[i + 2] + T[2]), 17);
	B = C + rotate_left((B + F(C,D,A) + X[i + 3] + T[3]), 22);

	A = B + rotate_left((A + F(B,C,D) + X[i + 4] + T[4]), 7);
	D = A + rotate_left((D + F(A,B,C) + X[i + 5] + T[5]), 12);
	C = D + rotate_left((C + F(D,A,B) + X[i + 6] + T[6]), 17);
	B = C + rotate_left((B + F(C,D,A) + X[i + 7] + T[7]), 22);

	A = B + rotate_left((A + F(B,C,D) + X[i + 8] + T[8]), 7);
	D = A + rotate_left((D + F(A,B,C) + X[i + 9] + T[9]), 12);
	C = D + rotate_left((C + F(D,A,B) + X[i + 10] + T[10]), 17);
	B = C + rotate_left((B + F(C,D,A) + X[i + 11] + T[11]), 22);

	A = B + rotate_left((A + F(B,C,D) + X[i + 12] + T[12]), 7);
	D = A + rotate_left((D + F(A,B,C) + X[i + 13] + T[13]), 12);
	C = D + rotate_left((C + F(D,A,B) + X[i + 14] + T[14]), 17);
	B = C + rotate_left((B + F(C,D,A) + X[i + 15] + T[15]), 22);

	//raund 2
	A = B + rotate_left((A + G(B,C,D) + X[i + 1] + T[16]), 5);
	D = A + rotate_left((D + G(A,B,C) + X[i + 6] + T[17]), 9);
	C = D + rotate_left((C + G(D,A,B) + X[i + 11] + T[18]), 14);
	B = C + rotate_left((B + G(C,D,A) + X[i + 0] + T[19]), 20);

	A = B + rotate_left((A + G(B,C,D) + X[i + 5] + T[20]), 5);
	D = A + rotate_left((D + G(A,B,C) + X[i + 10] + T[21]), 9);
	C = D + rotate_left((C + G(D,A,B) + X[i + 15] + T[22]), 14);
	B = C + rotate_left((B + G(C,D,A) + X[i + 4] + T[23]), 20);

	A = B + rotate_left((A + G(B,C,D) + X[i + 9] + T[24]), 5);
	D = A + rotate_left((D + G(A,B,C) + X[i + 14] + T[25]), 9);
	C = D + rotate_left((C + G(D,A,B) + X[i + 3] + T[26]), 14);
	B = C + rotate_left((B + G(C,D,A) + X[i + 8] + T[27]), 20);

	A = B + rotate_left((A + G(B,C,D) + X[i + 13] + T[28]), 5);
	D = A + rotate_left((D + G(A,B,C) + X[i + 2] + T[29]), 9);
	C = D + rotate_left((C + G(D,A,B) + X[i + 7] + T[30]), 14);
	B = C + rotate_left((B + G(C,D,A) + X[i + 12] + T[31]), 20);

	//raund 3
	A = B + rotate_left((A + H(B,C,D) + X[i + 5] + T[32]), 4);
	D = A + rotate_left((D + H(A,B,C) + X[i + 8] + T[33]), 11);
	C = D + rotate_left((C + H(D,A,B) + X[i + 11] + T[34]), 16);
	B = C + rotate_left((B + H(C,D,A) + X[i + 14] + T[35]), 23);

	A = B + rotate_left((A + H(B,C,D) + X[i + 1] + T[36]), 4);
	D = A + rotate_left((D + H(A,B,C) + X[i + 4] + T[37]), 11);
	C = D + rotate_left((C + H(D,A,B) + X[i + 7] + T[38]), 16);
	B = C + rotate_left((B + H(C,D,A) + X[i + 10] + T[39]), 23);

	A = B + rotate_left((A + H(B,C,D) + X[i + 13] + T[40]), 4);
	D = A + rotate_left((D + H(A,B,C) + X[i + 0] + T[41]), 11);
	C = D + rotate_left((C + H(D,A,B) + X[i + 3] + T[42]), 16);
	B = C + rotate_left((B + H(C,D,A) + X[i + 6] + T[43]), 23);

	A = B + rotate_left((A + H(B,C,D) + X[i + 9] + T[44]), 4);
	D = A + rotate_left((D + H(A,B,C) + X[i + 12] + T[45]), 11);
	C = D + rotate_left((C + H(D,A,B) + X[i + 15] + T[46]), 16);
	B = C + rotate_left((B + H(C,D,A) + X[i + 2] + T[47]), 23);

	//raund 4
	A = B + rotate_left((A + I(B,C,D) + X[i + 0] + T[48]), 6);
	D = A + rotate_left((D + I(A,B,C) + X[i + 7] + T[49]), 10);
	C = D + rotate_left((C + I(D,A,B) + X[i + 14] + T[50]), 15);
	B = C + rotate_left((B + I(C,D,A) + X[i + 5] + T[51]), 21);

	A = B + rotate_left((A + I(B,C,D) + X[i + 12] + T[52]), 6);
	D = A + rotate_left((D + I(A,B,C) + X[i + 3] + T[53]), 10);
	C = D + rotate_left((C + I(D,A,B) + X[i + 10] + T[54]), 15);
	B = C + rotate_left((B + I(C,D,A) + X[i + 1] + T[55]), 21);

	A = B + rotate_left((A + I(B,C,D) + X[i + 8] + T[56]), 6);
	D = A + rotate_left((D + I(A,B,C) + X[i + 15] + T[57]), 10);
	C = D + rotate_left((C + I(D,A,B) + X[i + 6] + T[58]), 15);
	B = C + rotate_left((B + I(C,D,A) + X[i + 13] + T[59]), 21);

	A = B + rotate_left((A + I(B,C,D) + X[i + 4] + T[60]), 6);
	D = A + rotate_left((D + I(A,B,C) + X[i + 11] + T[61]), 10);
	C = D + rotate_left((C + I(D,A,B) + X[i + 2] + T[62]), 15);
	B = C + rotate_left((B + I(C,D,A) + X[i + 9] + T[63]), 21);

	A += AA;
	B += BB;
	C += CC;
	D += DD;
}

	delete[]msg_for_decode;  // clear member
	
	std::string res = to_hex(A) + to_hex(B) + to_hex(C) + to_hex(D);  // fill in the result 

	return res;
}

int main()
{
	char* str = new char[100];
	cin >> str;
	std::cout << get_md5(str) << std::endl;
	return 0;
}