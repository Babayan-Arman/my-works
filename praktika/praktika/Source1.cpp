#include <iostream>
using namespace std;

void jnjel(int, int, double**);

int main()
{
	int i, j, m, n, maxrow = 0, maxcol = 0, q = 0;
	double max, k;
	do
	{
		cout << "nermuceq matrici toxeri chap@" << endl << "m=";
		cin >> m;
	} while (m < 2); 

	do
	{
		cout << "nermuceq matrici syuneri chap@" << endl << "n=";
		cin >> n;
	} while (n < 2);

	double** p = new double* [m]; //stexic (1)
	if (p == 0)
	{
		return 0;
	}

	for (i = 0; i < m; i++)
	{
		p[i] = new double[n];
		if (p[i] == 0)
		{
			for (j = 0; j < i; j++)
			{
				delete[] p[j];
				p[j] = 0;
			}
			delete[] p;
			p = 0; 
			return 0;
		}
	}

	for (i = 0; i < m; i++)  //stexic(2)
	{
		for (j = 0; j < n; j++)
		{
			cout << "p[" << i << "][" << j << "]=";
			cin >> p[i][j];
		}
	}							//stex(2) matrici nermucum

	cout << endl;
	for (i = 0; i < m; i++)  //stexic(3)
	{
		for (j = 0; j < n; j++)
		{
			cout << p[i][j] << "\t";
		}
		cout << endl << endl << endl;
	}						//stex(3) matrici artacum

	max = p[0][0];
	for (i = 0; i < m; i++)  //stexic(4)
	{
		for (j = 0; j < n; j++)
		{
			if (p[i][j] > max)
			{
				maxrow = i;
				maxcol = j;
				max = p[i][j];
			}
		}
	}							//stex(4) matrici max
	cout << "maxrow =" << maxrow << endl << "maxcol =" << maxcol << endl << "max =" << max << endl << endl;

								//stexic(5)
	for (i = 0; i < m; i++)  
	{
		for (j = 0; j < n; j++)
		{
			if (p[i][j] == max)
			{
				q++;
			}
		}
	}							//stex(5) maximum tareri qanaky@
	


	if (q > 1)								//stexic(6)
	{
		int* maxrowid = new int[q];
		if (maxrowid == 0)
		{
			jnjel(m, n, p);
			return 0;
		}
		int* maxcolid = new int[q];
		if (maxcolid == 0)
		{
			delete[]maxrowid;
			jnjel(m, n, p);
			return 0;
		}
		q = 0;
		for (i = 0; i < m; i++)  
		{
			for (j = 0; j < n; j++)
			{
				if (p[i][j] == max)
				{
					maxrowid[q] = i;
					maxcolid[q] = j;
					q++;
				}
					
			}
		}

		cout << "krknvox maximumneri id-ner@" << endl;
		for (i = 0; i < q; i++)											//stex voroshuma poxvox tveri toxeri indexner@
		{
			cout << "toxi id" <<  maxrowid[i] << "\t" ;
		}
		cout << endl;
		for (i = 0; i < q; i++)
		{
			cout << "syan id" << maxcolid[i] << "\t";	//stex voroshuma poxvox tveri syuneri indexner@
		}
		cout << endl << endl;

		int tak = q;
		for (i = 0; i < q; i++)
		{
			
			int i2 = maxrowid[i];
			int j2 = maxcolid[i];
			int tik = -1;
			
		  	cout << "poxeq krknvox maximum@" << endl;
			cout << "p[" << i2 << "][" << j2 << "]=";
			cin >> p[i2][j2];
			if (p[i2][j2] == max)
			{
				maxrow = i2;
				maxcol = j2;
				for (i = i + 1; i < q; i++)
				{
					i2 = maxrowid[i];
					j2 = maxcolid[i];
					cout << "p[" << i2 << "][" << j2 << "]=";
					
					do
					{
						cout << "maximumi arjeqn e " << max << " nermuceq maximumic tarber arjeq" <<endl;
						cout << "p[" << i2 << "][" << j2 << "]=";
						cin >> p[i2][j2];

					} while (p[i2][j2] == max);
					
					if (p[i2][j2] > max)
					{
						max = p[i2][j2];
						maxrow = i2;
						maxcol = j2;
						tik++;
						break;
					}
					
				}
			}
			else if (p[i2][j2] > max)
			{
				max = p[i2][j2];
				maxrow = i2;
				maxcol = j2;
				break;
			}
			else 
			{
				tak--;
			}

			if (tik != -1)
			{
				break;
			}
			if (tak == 1)
			{
				i2 = maxrowid[i++]; //vorovehtev naxaverjin tari indeqsi vraya
				j2 = maxcolid[i++];
				max = p[i2][j2];
				maxrow = i2;
				maxcol = j2;
				break;
			}
			
		}
		delete[]maxrowid;
		maxrowid = 0;
		delete[]maxcolid;
		maxcolid = 0;

		cout << endl << endl;


		for (i = 0; i < m; i++)  //stexic(3)
		{
			for (j = 0; j < n; j++)
			{
				cout << p[i][j] << "\t";
			}
			cout << endl << endl << endl;
		}						//stex(3) matrici artacum

		cout << endl << endl;

	}										//stex(6) matrici mej poxuma krknvox maximumner@ u yst grvac tvi anum inch petqa
	
	cout << endl << endl;

	for (i = maxrow; i < m-1; i++) //stexic(7)
	{
		for (j = 0; j < n; j++)
		{
			k = p[i + 1][j];
			p[i + 1][j] = p[i][j];
			p[i][j] = k;
		}

		cout << endl << endl;

		for (int i3 = 0; i3 < m; i3++)  //stexic(3)
		{
			for (int j3 = 0; j3 < n; j3++)
			{
				cout << p[i3][j3] << "\t";
			}
			cout << endl  << endl << endl;
		}						//stex(3) matrici artacum
		cout << "***********************************" << endl;

	}															//stex(7) matrici toxerna poxum

	for (j = maxcol; j < n - 1; j++)							//stexic(8)
	{
		for (i = 0; i < m; i++)
		{
			k = p[i][j + 1];
			p[i ][j + 1] = p[i][j];
			p[i][j] = k;
		}
		cout << endl << endl;

		for (int i3 = 0; i3 < m; i3++)  //stexic(3)
		{
			for (int j3 = 0; j3 < n; j3++)
			{
				cout << p[i3][j3] << "\t";
			}
			cout << endl << endl << endl;
		}						//stex(3) matrici artacum
		cout << "***********************************" << endl;
	}																//stex(8) matrici syunerna poxum

	double** p2 = new double*[m - 1];	//stexic(9)
	if (p2 == 0)
	{
		jnjel(m, n, p);
		return 0;
	}
	for (i = 0; i < m-1; i++)
	{
		p2[i] = new double[n - 1];
		if (p2[i] == 0)
		{
			for (j = 0; j < i; j++)
			{
				delete[]p2[i];
				p2[i] = 0;
			}
			delete[]p2;
			p2 = 0;
			jnjel(m, n, p);
			return 0;
		}
	}									//stex(9) nor stacvox matrici hamar hishoxutyunum tex em pntrum

	for (i = 0; i < m-1; i++)			//stexic(10)
	{
		for (j = 0; j < n-1; j++)
		{
			p2[i][j] = p[i][j];
		}
	}				
	jnjel(m, n, p);						//stex(10) tver@ texapoxum em nor matric u jnjum hin@
	
	cout << endl << endl << endl;

	for (i = 0; i < m-1; i++)  //stexic(3)
	{
		for (j = 0; j < n-1; j++)
		{
			cout << p2[i][j] << "\t";
		}
		cout << endl << endl << endl;
	}						//stex(3) matrici artacum

	cout << endl << endl << endl;
	jnjel(m - 1, n - 1, p2);
	
	
	return 0;
}

void jnjel(int m1, int n1, double** p1)
{
	for (int i = 0; i < m1; i++)
	{
		delete[] p1[i];
		p1[i] = 0;
	}
	delete[]p1; 
	p1 = 0;
}