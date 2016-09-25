// SegmentedBitonicSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BitonicSorter.h"

using namespace std;

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
	for (int i = 0; i < m; i++) {
		float* arr = data + seg_start[i];
		int arrLen = seg_start[i + 1] - seg_start[i];

		BitonicSorter<float, float*> arraySorter(arr, arrLen);
		arraySorter.sort(true);
		cout << endl;
	}
}

float randNumForTest() {
	float n = (rand() % 100), m = (rand() % 10), q = (rand() % 10);
	float a = n; // +m / 10 + q / 100;
	return a;
}

bool generateRandomNums(float *data, int len) {
	for (int i = 0; i < len; i++) {
		data[i] = randNumForTest();
	}

	return true;
}

int main() {
	/*float data[5] = { 0.8, 0.2, 0.4, 0.6, 0.5 };

	int seg_id[5] = { 0, 0, 1, 1, 1 };

	int seg_start[3] = { 0, 2, 5 };

	int n = 5;

	int m = 2;

	segmentedBitonicSort(data, seg_id, seg_start, n, m);

	for (int i = 0; i < 5; i++) {
		cout << data[i] << endl;
	}*/

	int len = 10;
	float *data = new float[len];
	generateRandomNums(data, len);
	BitonicSorter<float, float*> arraySorter(data, len);
	arraySorter.print();
	arraySorter.sort(true);


	return 0;
}



