// SegmentedBitonicSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

// Not calling any function now.
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
	for (int i = 0; i < m; i++) {
		float* list = data + seg_start[i];
		int listLen = seg_start[i + 1] - seg_start[i];

		if (listLen == 0) {
			return;
		}

		// Find the max value.
		float extremum = list[0];
		for (int i = 1; i < listLen; i++) {
			if (list[i] > extremum || extremum != extremum) {
				extremum = list[i];
			}
		}

		// Padding the length of the array to the power of 2.
		int N = n;
		--N;
		N |= N >> 1;
		N |= N >> 2;
		N |= N >> 4;
		N |= N >> 8;
		N |= N >> 16;
		N++;
		float* tempList = new float[N];
		for (int i = 0; i < listLen; i++) {
			tempList[i] = list[i];
		}
		for (int i = listLen; i < N; i++) {
			tempList[i] = extremum;
		}

		// Start bottom-up sort.

		// http://www.tools-of-computing.com/tc/CS/Sorts/bitonic_sort.htm
		// Variable k selects the bit position that determines whether the pairs of elements are to be exchanged into ascending or descending order.
		int i, j, k;
		for (k = 2; k <= N; k = k << 1) {
			// Variable j corresponds to the distance apart the elements are that are to be compared and conditionally exchanged.
			for (j = k >> 1; j > 0; j = j >> 1) {
				// Variable i goes through all the elements
				// This part can be implemented in parallel.
				for (i = 0; i < N; i++) {
					// Variable ixj is the element that is the pair of element i.
					// For example, when k = 2, j = 1, i = 0, then ixj = 1, thus compare list[0] and list[1]
					int ixj = i ^ j;

					// Avoids comparing them twice, for example k = 2, j = 1, i = 1, then ixj = 0
					if ((ixj > i)) {
						// ascending, for example k = 2, j = 1, i = 0, ixj = 1, so list[0] and list[1] should be ascending
						if ((i & k) == 0 && ((tempList[ixj] != tempList[ixj]) || (tempList[i] > tempList[ixj]))) {
							float tmp = tempList[i];
							tempList[i] = tempList[ixj];
							tempList[ixj] = tmp;
						}
						// descending, for example k = 2, j = 1, i = 2, ixj = 3, so list[2] and list[3] should be descending
						if ((i & k) != 0 && ((tempList[i] != tempList[i]) || (tempList[i] < tempList[ixj]))) {
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
	if (rand() % 100 > 20) {
		float n = (rand() % 100), m = (rand() % 10), q = (rand() % 10);
		float a = n + m / 10 + q / 100;
		return a;
	}
	else {
		return sqrt(-1.f);
	}
}

bool generateRandomNums(float *data, int len) {
	for (int i = 0; i < len; i++) {
		data[i] = randNumForTest();
	}

	return true;
}

void test(int count) {
	int t;
	while (count--) {
		srand(time(NULL));

		int n = rand() % 10 + 20;

		float *data = new float[n];
		generateRandomNums(data, n);

		int *seg_id = new int[n];

		int group = 0;
		for (int i = 0; i < n; i++) {
			if (i / 2 < rand() % (i + 1)) {
				group++;
			}
			seg_id[i] = group;
		}

		int m = seg_id[n - 1] + 1;
		int *seg_start = new int[m + 1];

		seg_start[0] = 0;
		seg_start[m] = n;
		int pos = 0;
		for (int i = 1; i < m; i++) {
			while (pos + 1 < n) {
				if (seg_id[pos] != seg_id[pos + 1]) {
					seg_start[i] = pos + 1;
					pos++;
					break;
				}
				else {
					pos++;
				}
			}
		}

		cout << "Test case " << 10 - count << endl;
		cout << "The seg_id is: " << endl;
		for (int i = 0; i < n; i++) {
			cout << seg_id[i] << " ";
		}
		cout << endl;

		cout << "The seg_start is: " << endl;
		for (int i = 0; i <= m; i++) {
			cout << seg_start[i] << " ";
		}
		cout << endl;

		cout << "The input is: " << endl;
		for (int i = 0; i < n; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
		segmentedBitonicSort(data, seg_id, seg_start, n, m);

		cout << "The output is: " << endl;
		for (int i = 0; i < n; i++) {
			cout << data[i] << " ";
		}
		cout << endl;

		delete[] data;
		delete[] seg_id;
		delete[] seg_start;
	}


}

int main() {
	//float data[5] = { 0.8, sqrt(-1.f), sqrt(-1.f), 0.6, 0.5 };
	//int seg_id[5] = { 0, 0, 1, 1, 1 };
	//int seg_start[3] = { 0, 2, 5 };
	//int n = 5;
	//int m = 2;

	//segmentedBitonicSort(data, seg_id, seg_start, n, m);

	//for (int i = 0; i < 5; i++) {
	//	cout << data[i] << endl;
	//}

	test(10);

	system("pause");
	return 0;
}



