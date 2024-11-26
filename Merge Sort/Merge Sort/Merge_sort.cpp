#include <iostream>
#include <cstdlib>
using namespace std;

void swap(int*, int, int);

void merge_sort(int* arr, int end, int start = 0)
{
	if (end - start < 2)
	{
		cout << arr[start] << endl;
		cout << "skip" << endl;
		return;
	}
	int i, j;
	int b = (start + end) / 2;
	//	cout << endl << start << "\t" << end << "\t" << "b = " << b << endl <<endl;
	for (int k = start; k < end; ++k)
	{
		cout << arr[k] << "\t";
	}
	cout << endl << "___________" << endl << endl;
	cout << "start = " << start << "\t" << "end = " << b << "\t" << "left " << endl;

	merge_sort(arr, b, start); //left
	cout << "#####################" << endl;


	cout << "start = " << b << "\t" << "end = " << end << "\t" << "right " << endl;
	merge_sort(arr, end, b); //right
	cout << "*********************" << endl;
	cout << endl << endl;


	//i = start;
	cout << "start = " << start << "\t" << "end = " << b << "\t" << "left " << endl;

	cout << "i = " << start << "\t" << arr[start] << endl;

	//j = b;
	cout << "start = " << b << "\t" << "end = " << end << "\t" << "right " << endl;

	cout << "j = " << b << "\t" << arr[b] << endl << endl;
	cout << "+++++++++++++++++++++++++++++++++++" << endl;
	int km = 0;
	for (int i = start; i < b; ++i)
	{
		int ind = i;
		for (int j = b; j < end; j++)
		{
			for (int i1 = start; i1 < b; ++i1)
			{
				cout << arr[i1] << "\t";

			}
			for (int j1 = b; j1 < end; ++j1)
			{
				cout << arr[j1] << "\t";

			}
			km++;
			cout << endl;
			cout << km << ". ---------------------------------" << endl;
			if (arr[ind] > arr[j])
			{
				swap(arr, ind, j);
				ind = j;
			}

		}

	}
	for (int i1 = start; i1 < b; ++i1)
	{
		cout << arr[i1] << "\t";
	}
	for (int j1 = b; j1 < end; ++j1)
	{
		cout << arr[j1] << "\t";
	}
	cout << endl;
	cout << "+++++++++++++++++++++++++++++++++++" << endl;

	//cout <<"i = "<< i << "\t" << arr[i] << "\t" << "j = " << j << "\t" << arr[j] << endl;
}

int main()
{

	int n;
	cout << "numbers of members: "; cin >> n;
	int* x = new int[n];

	for (int i = 0; i < n; ++i)
	{
		x[i] = rand() % (n + 1);
		cout << x[i] << "\t";
	}
	cout << endl;
	//for (int i = 0; i < n; ++i)
	//{
	//	x[i] = n;
	//	x[i]--;
	//}


	merge_sort(x, n);


	cout << endl;

	cout << endl << "______________________________________________________" << endl;
	cout << endl << "______________________________________________________" << endl;
	cout << endl << "______________________________________________________" << endl;
	for (int i = 0; i < n; ++i)
	{

		cout << x[i] << "\t";
	}

	delete[] x;
	return 0;
}


void swap(int* x, int a, int b)
{
	int k = x[b];
	x[b] = x[a];
	x[a] = k;
}