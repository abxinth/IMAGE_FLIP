#pragma once
#include<iostream>
#include<fstream>


struct ImgProp {
	int Hpixels;
	int Vpixels;
	unsigned char HeaderInfo[54];
	unsigned long int Hbytes;
};
struct Pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
struct ImgProp ip;

unsigned char** ReadBmp(char* filename) {
	int i;
	std::ifstream file;
	file.open(filename, std::ios::in | std::ios::binary);
	unsigned char HeaderInfo[54];
	file.read((char*)HeaderInfo, sizeof(HeaderInfo));
	for (i = 0; i < 54; i++) { ip.HeaderInfo[i] = HeaderInfo[i]; }
	int width = *(int*)&HeaderInfo[18];
	int height = *(int*)&HeaderInfo[22];
	int RowBytes = (width * 3 + 3) & (~3);
	ip.Hbytes = RowBytes;
	ip.Vpixels = height;
	ip.Hpixels = width;

	unsigned char** Img = (unsigned char**)malloc(height * sizeof(unsigned char*));
	for (i = 0; i < height; i++) {
		Img[i] = (unsigned char*)malloc(RowBytes * sizeof(unsigned char));
	}
	for (i = 0; i < height; i++) {
		file.read((char*)Img[i], RowBytes);
	}
	file.close();
	return Img;
}

void WriteBMP(unsigned char** img, char* filename) {
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::binary);

	unsigned long int x, y;
	char temp;

	outfile.write((char*)ip.HeaderInfo, 54);
	for (x = 0; x < ip.Vpixels; x++) {
		for (y = 0; y < ip.Hbytes; y++) {
			temp = img[x][y];
			outfile.write((char*)&temp, sizeof(char));
		}
	}
	outfile.close();

}
