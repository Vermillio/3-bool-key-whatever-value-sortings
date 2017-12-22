#pragma once

#define uint unsigned int

#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

//1. complexity Î(n); 
//2. stable; 
//3) additional memory O(1);


namespace sorting
{

	template<typename T>
	struct dat
	{
	
		bool key;
		T value;
		dat() {};

	};

	template<typename T>
	class Sort
	{
	public:

		///<summary> Complexity O(N), stable.</summary>
		void sort12(vector<dat<T>> &x);

		///<summary>Complexity O(N*log(N)), stable, no additional memory.</summary>
		void sort23(vector<dat<T>> &x);

		///<summary>Complexity O(N), no additional memory.</summary>
		void sort13(vector<dat<T>> &x);

		///<summary>Counts working time of sorting procedure and prints it.</summary>
		void testSort(vector<dat<T>> arr);

		///<summary>Creates random vector and implements 3 types of sorting on it printing working time for each case.</summary>
		void demo();

		///<summary>Prints vector of given elements per line.</summary>
		void print(vector<dat<T>> arr, uint elementsPerLine);
	};
}


//IMPLEMENTATION
//
//template<typename T>
//bool operator== (sorting::dat<T> x, sorting::dat<T> y) {
//	return x.key == y.key;
//}

template<typename T>
vector<sorting::dat<T>> operator+ (vector<sorting::dat<T>> x, vector<sorting::dat<T>> y)
{
	x.insert(x.end(), y.begin(), y.end());
	return x;
}

template<typename T>
void sorting::Sort<T>::sort13(vector<sorting::dat<T>> &x)
{
	int l = 0, r = x.size() - 1;
	while (l < r)
	{
		while (x[l].key == 0)
			++l;
		while (x[r].key == 1)
			--r;
		if (l < r)
			swap(x[l], x[r]);
		++l;
		--r;
	}
}

template<typename T>
void sorting::Sort<T>::testSort(vector<sorting::dat<T>> arr)
{

	cout << "		<O(N) STABLE SORTING>" << endl;
	time_t t = clock();
	sort12(arr);
	print(arr, 10);
	t = clock() - t;
	cout << "Took " << t / 1000 << " s." << endl;
	cout << "		<O(N) NO ADDITIONAL MEMORY SORTING>" << endl;
	t = clock();
	sort13(arr);
	print(arr, 10);
	t = clock() - t;
	cout << "Took " << t / 1000 << " s." << endl;
	cout << "		<O(N*logN) STABLE NO ADDITIONAL MEMORY SORTING>" << endl;
	t = clock();
	sort23(arr);
	print(arr, 10);
	t = clock() - t;
	cout << "Took " << t / 1000 << " s." << endl;

}

template<typename T>
void sorting::Sort<T>::sort23(vector<sorting::dat<T>> &x)
{
	int chunkSize = 1;
	while (chunkSize <= x.size())
	{
		for (int i = 0; i < x.size(); i += 2 * chunkSize)
		{
			int l = i;
			int m = i + chunkSize;
			if (m >= x.size())
				break;
			int r = i+2*chunkSize >= x.size() ? x.size()-1 : i + 2 * chunkSize - 1;
			if (r >= x.size())
			{
				r = x.size();
				m = (l + r) / 2;
			}
			while (l < m && x[l].key == 0)
				++l;
			if (l == m)
				continue;
			while (r >= m && x[r].key == 1)
				--r;
			if (r == m - 1)
				continue;
			rotate(x.begin() + l, x.begin() + r, x.begin() + m);
		}
		chunkSize *= 2;
	}


}

template<typename T>
void sorting::Sort<T>::sort12(vector<sorting::dat<T>> &x)
{
	vector<dat<T>> l, r;
	for (int i = 0; i < x.size(); ++i)
	{
		if (x[i].key)
			r.push_back(x[i]);
		else l.push_back(x[i]);
	}
	x = l + r;
}


template<typename T>
void sorting::Sort<T>::demo()
{
	srand(clock());
	int N;
	cout << "Enter size: " << endl;
	cin >> N;
	vector<dat<T>> arr(N);
	for (int i = 0; i < N; ++i)
	{
		arr[i].key = rand()%2;
		arr[i].value = rand();
	}
	print(arr, 10);
	vector<dat<T>> sorted = arr;
	testSort(sorted);
}

template<typename T>
void sorting::Sort<T>::print(vector<sorting::dat<T>> arr, uint elementsPerLine)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr[i].key << " - " << arr[i].value << "  ";
		if ((i +1)% elementsPerLine == 0)
			cout << endl;
	}
	cout << endl;
}

