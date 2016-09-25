#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


// see [ http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2 ]
// example [
//  cout << LeastPowerOf2NotLessThan( 3 ) << LeastPowerOf2NotLessThan( 4 ) << LeastPowerOf2NotLessThan( 5 ) << endl;
// ] output [ 448 ]
int LeastPowerOf2NotLessThan(int n)
{
	--n;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return (n + 1);
}
int GreatestPowerOf2LessThan(int n)
{
	return LeastPowerOf2NotLessThan(n) >> 1;
}

template <typename T>
static void bitonicSort_Ascend(std::vector<T> &vec, const T &max)
{
	int originLen = vec.size();
	int listLen = LeastPowerOf2NotLessThan(originLen);
	vec.resize(listLen, max);

	int i, j, k;
	// k selects the bit position that determines whether the pairs of 
	// elements are to be exchanged into ascending or descending order.
	// length of sort interval get doubled every iteration
	// (because sort recursion is post-ordered).
	for (k = 2; k <= listLen; k <<= 1) {

		// j corresponds to the distance apart the elements are that 
		// are to be compared and conditionally exchanged.
		// length of merge interval get halved every iteration
		// (because merge recursion is pre-ordered).
		for (j = k >> 1; j > 0; j >>= 1) {

			for (i = 0; i < listLen; ++i) {
				int ixj = i ^ j;
				std::cout << "k=" << k << std::endl;
				std::cout << "j=" << j << std::endl;
				std::cout << "i=" << i << std::endl;
				std::cout << "ixj=" << ixj << std::endl;

				if (i < ixj) {
					if ((i & k) != 0) {
						if (vec[i] < vec[ixj]) {
							std::swap(vec[i], vec[ixj]);
						}
					}
					else {    // ((i & k) == 0)
						if (vec[i] > vec[ixj]) {
							std::swap(vec[i], vec[ixj]);
						}
					}
				}

				for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
					std::cout << *iter << ',';
				}
				std::cout << std::endl;
			}

		}
	}

	vec.resize(originLen);
}

// type of items in List must be Item.
// there must be operator[] in List.
template <typename Item, typename List>
class BitonicSorter
{
public:
	BitonicSorter(List &list, int len) : list(list), listLen(len) {}

	// if (ascend == true), the list will be sorted in ascending order
	void recursiveSort(bool ascend = true)
	{
		bitonicSort(ascend, 0, listLen);
	}


    // http://www.tools-of-computing.com/tc/CS/Sorts/bitonic_sort.htm
	void nonRecursiveSort(bool ascend = true) {
		if (listLen == 0) {
			return ;
		}

		int N = LeastPowerOf2NotLessThan(listLen);
		List tempList = new Item[N];

		int extremum = list[0];
		if (ascend) {
			for (int i = 1; i < listLen; i++) {
				if (list[i] > extremum) {
					extremum = list[i];
				}
			}
		}
		else {
			for (int i = 1; i < listLen; i++) {
				if (list[i] < extremum) {
					extremum = list[i];
				}
			}
		}

		for (int i = 0; i < listLen; i++) {
			tempList[i] = list[i];
		}
		for (int i = listLen; i < N; i++) {
			tempList[i] = extremum;
		}

		int i, j, k;
		for (k = 2; k <= N; k = k << 1) {
			for (j = k >> 1; j > 0; j = j >> 1) {
				for (i = 0; i < N; i++) {
					int ixj = i ^ j;

					if ((ixj) > i) {
						if ((i & k) == 0 && (tempList[i] > tempList[ixj]) == ascend) {
							swap(tempList[i], tempList[ixj]);
						}
						if ((i & k) != 0 && (tempList[i] < tempList[ixj]) == ascend) {
							swap(tempList[i], tempList[ixj]);
						}
					}
				}
			}
			// print();
		}

		for (int i = 0; i < listLen; i++) {
			list[i] = tempList[i];
		}
		delete[] tempList;
	}

	void print() const {
		for (int i = 0; i < listLen; ++i) {
			std::cout << list[i] << ',';
		}
		std::cout << std::endl;
	}

	void print(int offset, int len) const {
		std::cout << offset << ',' << offset + len << std::endl;
		for (int i = 0; i < listLen; ++i) {
			if (i == offset + len || i == offset) {
				std::cout << "|";
			}

			std::cout << list[i] << ',';
		}
		std::cout << std::endl;
	}

private:
	void bitonicSort(bool ascend, int offset, int len)
	{
		if (len <= 1) { return; }

		printOperation( "sort", ascend, offset, len );

		int halfLen = len / 2;
		bitonicSort(!ascend, offset, halfLen);
		bitonicSort(ascend, offset + halfLen, len - halfLen);

		bitonicMerge(ascend, offset, len);
	}

	void bitonicMerge(bool ascend, int offset, int len)
	{
		if (len <= 1) { return; }

		printOperation( "merge", ascend, offset, len );

		int halfLen = GreatestPowerOf2LessThan(len);
		int left = offset;
		int right = offset + halfLen;
		for (int i = halfLen; i < len; ++i, ++left, ++right) {
			if ((list[left] > list[right]) == ascend) { std::swap(list[left], list[right]); }
		}
		bitonicMerge(ascend, offset, halfLen);
		bitonicMerge(ascend, offset + halfLen, len - halfLen);
	}

	static void printOperation(std::string operation, bool ascend, int offset, int len)
	{
		std::cout << operation << " " << (ascend ? "up" : "down") << "[" << offset << ", " << offset + len << ")" << std::endl;
		
	}

	List &list;
	int listLen;
};