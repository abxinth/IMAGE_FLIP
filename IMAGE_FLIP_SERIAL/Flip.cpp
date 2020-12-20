
#include<time.h>

#include "ImageRW.h"
#define REPS 129

unsigned char** FlipImageV(unsigned char** img)
{
	struct Pixel pix; //temp swap pixel
	int row, col;
	for (col = 0; col < ip.Hbytes; col += 3) {
		row = 0;
		while (row < ip.Vpixels / 2) {
			pix.B = img[row][col];
			pix.G = img[row][col + 1];
			pix.R = img[row][col + 2];
			img[row][col] = img[ip.Vpixels - (row + 1)][col];
			img[row][col + 1] = img[ip.Vpixels - (row + 1)][col + 1];
			img[row][col + 2] = img[ip.Vpixels - (row + 1)][col + 2];
			img[ip.Vpixels - (row + 1)][col] = pix.B;
			img[ip.Vpixels - (row + 1)][col + 1] = pix.G;
			img[ip.Vpixels - (row + 1)][col + 2] = pix.R;
			row++;
		}
	}
	return img;
}
unsigned char** FlipImageH(unsigned char** img)
{
	struct Pixel pix; //temp swap pixel
	int row, col;
	//horizontal flip
	for (row = 0; row < ip.Vpixels; row++) { // go through the rows
		col = 0;
		while (col < (ip.Hpixels * 3) / 2) { // go through the columns
			pix.B = img[row][col];
			pix.G = img[row][col + 1];
			pix.R = img[row][col + 2];
			img[row][col] = img[row][ip.Hpixels * 3 - (col + 3)];
			img[row][col + 1] = img[row][ip.Hpixels * 3 - (col + 2)];
			img[row][col + 2] = img[row][ip.Hpixels * 3 - (col + 1)];
			img[row][ip.Hpixels * 3 - (col + 3)] = pix.B;
			img[row][ip.Hpixels * 3 - (col + 2)] = pix.G;
			img[row][ip.Hpixels * 3 - (col + 1)] = pix.R;
			col += 3;
		}
	}
	return img;
}
int main() {
	double timer;
	unsigned int a;
	clock_t start, stop;
	char fname[20];

	std::cout << "***\n";
	char arr[4] = { 'A','B','C','D' };
	char* p= arr;

	std::cout <<*(int*)&arr;
	std::cout << "\n***\n";


	std::cout << "FILE NAME : ";
	std::cin >> fname;	
	char outfname[20] = "outf.bmp";
	unsigned char** data = ReadBmp(fname);
	int choice;
	std::cout << "1.FLIP HORIZONTALLY 2.FLIP VERTICALLY\n";
	std::cin >> choice;

	start = clock();
	if (choice == 1) {
		data = FlipImageH(data);
	}
	else if (choice == 2) {
		data = FlipImageV(data);
	}
	else {
		std::cout << "invalid choice inverting vertically";
		data = FlipImageV(data);
	}
	
	stop = clock();
	WriteBMP(data, outfname);
	

	free(data);
	timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC / (double)REPS;
	printf("\n\nTotal execution time: %9.4f ms", timer);
	return 0;
}