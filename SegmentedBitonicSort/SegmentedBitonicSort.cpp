// SegmentedBitonicSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BitonicSorter.h"

using namespace std;

// Not calling any function now.
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
	for (int i = 0; i < m; i++) {
		float* list = data + seg_start[i];
		int listLen = seg_start[i + 1] - seg_start[i];

		// BitonicSorter<float, float*> arraySorter(arr, arrLen);
		// arraySorter.nonRecursiveSort(true);

		if (listLen == 0) {
			return;
		}

		int N = n;
		--N;
		N |= N >> 1;
		N |= N >> 2;
		N |= N >> 4;
		N |= N >> 8;
		N |= N >> 16;
		N++;

		float* tempList = new float[N];

		float extremum = list[0];
		for (int i = 1; i < listLen; i++) {
			if (list[i] > extremum) {
				extremum = list[i];
			}
		}

		for (int i = 0; i < listLen; i++) {
			tempList[i] = list[i];
		}
		for (int i = listLen; i < N; i++) {
			tempList[i] = extremum;
		}

		// http://www.tools-of-computing.com/tc/CS/Sorts/bitonic_sort.htm
		int i, j, k;
		for (k = 2; k <= N; k = k << 1) {
			for (j = k >> 1; j > 0; j = j >> 1) {
				for (i = 0; i < N; i++) {
					int ixj = i ^ j;

					if ((ixj) > i) {
						if ((i & k) == 0 && (tempList[i] > tempList[ixj])) {
							float tmp = tempList[i];
							tempList[i] = tempList[ixj];
							tempList[ixj] = tmp;
						}
						if ((i & k) != 0 && (tempList[i] < tempList[ixj])) {
							float tmp = tempList[i];
							tempList[i] = tempList[ixj];
							tempList[ixj] = tmp;
						}
					}
				}
			}
		}

		for (int i = 0; i < listLen; i++) {
			list[i] = tempList[i];
		}
		delete[] tempList;
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

template <typename T>
void print(vector<T> vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
		std::cout << *iter << ',';
	}
	std::cout << std::endl;
}

int main() {
	float data[5] = { 0.8, 0.2, 0.4, 0.6, 0.5 };

	int seg_id[5] = { 0, 0, 1, 1, 1 };

	int seg_start[3] = { 0, 2, 5 };

	int n = 5;

	int m = 2;

	segmentedBitonicSort(data, seg_id, seg_start, n, m);

	for (int i = 0; i < 5; i++) {
		cout << data[i] << endl;
	}

	/*int len = 11;
	float *data = new float[len];
	generateRandomNums(data, len);
	BitonicSorter<float, float*> arraySorter(data, len);
	arraySorter.print();
	arraySorter.nonRecursiveSort(true);
	arraySorter.print();*/

	return 0;
}



