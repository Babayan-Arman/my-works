#include <iostream>
#include <cstdlib>
using namespace std;

void swap(int*, int, int);

void qsort(int* arr, int end, int start = 0)
{
	/*cout << "end-start = " << end - start << endl;
	cout << "start = " << start << endl;
	cout << "end = " << end << endl;*/
	if (end - start < 2)
	{
		/*cout << "SKIP" << endl;*/
		return;
	}
	int pivot = end - 1, b = start;


	for (int i = start; i < end; ++i)
	{
		/*cout << "a = " << i << "\t" << "b =  " << b << endl;*/
		if (arr[i] < arr[pivot])
		{
			if (b == i)
			{
				b++;
			}
			else
			{
				swap(arr, i, b);
				b++;
			}
		}
		/*for (int j = start; j < end ; ++j)
		{
			cout << arr[j] << "\t";
		}
		cout << endl << "###################################" << endl;*/
	}
	swap(arr, b, pivot);
	/*for (int j = start; j < end ; ++j)
	{
		cout << arr[j] << "\t";
	}
	cout << endl << "______________________________________________________" << endl;*/

	qsort(arr, end, b + 1);
	qsort(arr, b, start);


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
	//for (int i = 0; i < n; ++i)
	//{
	//	x[i] = n;
	//	x[i]--;
	//}
	cout << endl;

	qsort(x, n);

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