
#include<time.h>
#include<thread>
#include "ImgRw.h"
#include<mutex>
std::mutex m;

#define REPS 129
#define NUM_THREADS 6;

unsigned char** TheImage;
void MTFlipH(int tid)
{
	struct Pixel pix; //temp swap pixel
	int row, col;
	long ts; // My thread ID is stored here
	ts =  tid*(ip.Vpixels / 6); // start index
	long te = ts + (ip.Vpixels / 6) - 1; // end index
	

	if (tid == 5 && te < ip.Vpixels -1) {
		te = ip.Vpixels - 1;
	}
	

	if (te>ip.Vpixels-1) {
		te = ip.Vpixels - 1;
	}
	
	for (ts; ts <= te;ts++) {
		col = 0;
		for (int i = 0; i < (ip.Hpixels * 3) / 2;i+=3) {
			pix.B = TheImage[ts][i];
			pix.G = TheImage[ts][i + 1];
			pix.R = TheImage[ts][i + 2];

			TheImage[ts][i] = TheImage[ts][ip.Hpixels * 3 - (i + 3)];
			TheImage[ts][i + 1] = TheImage[ts][ip.Hpixels * 3 - (i + 2)];
			TheImage[ts][i + 2] = TheImage[ts][ip.Hpixels * 3 - (i + 1)];

			TheImage[ts][ip.Hpixels * 3 - (i + 3)] = pix.B;
			TheImage[ts][ip.Hpixels * 3 - (i + 2)] = pix.G;
			TheImage[ts][ip.Hpixels * 3 - (i + 1)] = pix.R;

		}

	}
	
	m.lock();
	std::cout << ts << " " << te << "\n";
	m.unlock();
}



int main() {
	double timer;
	unsigned int a;
	clock_t start, stop;
	char fname[20];

	std::cout << "***\n";
	char arr[4] = { 'A','B','C','D' };
	char* p = arr;

	std::cout << *(int*)&arr;
	std::cout << "\n***\n";


	std::cout << "FILE NAME : ";
	std::cin >> fname;
	char outfname[20] = "outf.bmp";
	unsigned char** data = ReadBmp(fname);
	int choice;
	std::cout << "1.FLIP HORIZONTALLY 2.FLIP VERTICALLY\n";
	std::cin >> choice;
	TheImage = data;
	std::thread t[6];
	start = clock();
	////////////////////////////////////
	if (choice == 1 || choice == 2) {
		for (int i = 0; i < 6;i++) {
			t[i] = std::thread(MTFlipH, i);
		}
	}
	else {
		std::cout << "invalid choice inverting vertically";
		
	}
	/////////////////////////////////////
	for (int i = 0; i < 6; i++) {
		t[i].join();
	}


	stop = clock();
	WriteBMP(data, outfname);


	free(data);
	timer = 1000 * ((double)(stop - start)) / (double)CLOCKS_PER_SEC / (double)REPS;
	printf("\n\nTotal execution time: %9.4f ms", timer);
	return 0;
}