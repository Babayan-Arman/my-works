#include <iostream>
using namespace std;



struct kox
{
	int skizb;
	int verj;
	kox* next;
	kox* prev;
};

class koxer  //[#2.1]
{
private:
	int **koxeri_matric;
	int** harevanutyan_matric;
	kox* head;
	int n;  //koxeri, hanguycneri, zugaherneri qanaky miasin
	int gagatner = -1;
public:
	koxer()
	{
		head = new kox;
		head->next = head;
		head->prev = head;
		n = 0;
	}
	~koxer() 
	{
		for (int i = 0; i < gagatner; i++)
		{
			delete[] koxeri_matric[i]; koxeri_matric[i] = 0;
		}
		delete[] koxeri_matric; koxeri_matric = 0;
		for (int i = 0; i < gagatner; i++)
		{
			delete[] harevanutyan_matric[i]; harevanutyan_matric[i] = 0;
		}
		delete[] harevanutyan_matric; harevanutyan_matric = 0;
	}
	int gagatneri_tiv()
	{
		return gagatner;
	}

	void avelacnel() //[#2.1.1]
	{
		if (n == 0)
		{
			cout << "\t nermuceq gagatneri qanaky\n";
			do
			{
				cin >> gagatner;
				if (gagatner < 0)
					cout << "chi karox 0-ic poqr linel\n";
			} while (gagatner < 1);
			koxeri_matric = new int* [gagatner];
			for (int i = 0; i < gagatner; i++)
			{
				koxeri_matric[i] = new int[gagatner];
				for (int j = 0; j < gagatner; j++)
				{
					koxeri_matric[i][j] = 0;
				}
			}
			harevanutyan_matric = new int* [gagatner];
			for (int i = 0; i < gagatner; i++)
			{
				harevanutyan_matric[i] = new int[gagatner];
				for (int j = 0; j < gagatner; j++)
				{
					harevanutyan_matric[i][j] = 0;
				}
			}
			cout << "\t nermuceq 1in gagaty heto 2rd\n";
			do
			{
				cin >> head->skizb >> head->verj;
				if (head->skizb < 0 || head->verj < 0)
					cout << "chi karox 0-ic poqr linel\n";
				else if (head->skizb > gagatner - 1 || head->verj > gagatner - 1)
				{
					cout << "chi karox" << gagatner - 1 << "-ic mec linel\n";
				}
				else 
				{
					koxeri_matric[head->skizb][head->verj] = 1;
				}
			} while (head->skizb < 0 || head->verj < 0 || head->skizb > gagatner-1 || head->verj > gagatner - 1);
			n++;
		}
		else
		{
			if(n == gagatner*gagatner)
			{
				cout << "aylevs hnaravor che kox avelacnel\n";
			}
			else
			{
				kox* jamanakavor = new kox;
				jamanakavor = head;
				kox* avelacvox = new kox;
				do
				{
					cin >> avelacvox->skizb >> avelacvox->verj;
					if (avelacvox->skizb < 0 || avelacvox->verj < 0)
						cout << "chi karox 0-ic poqr linel\n";
					else if (avelacvox->skizb > gagatner - 1 || avelacvox->verj > gagatner - 1)
					{
						cout << "chi karox " << gagatner - 1 << "-ic mec linel\n";
					}
					else
					{
						if (koxeri_matric[avelacvox->skizb][avelacvox->verj] == 1)
						{
							avelacvox->skizb = -1;
							cout << "ayd koxy arden ka!\n";
						}
						else
							koxeri_matric[avelacvox->skizb][avelacvox->verj] = 1;
					}
				} while (avelacvox->skizb < 0 || avelacvox->verj < 0 || avelacvox->skizb > gagatner - 1 || avelacvox->verj > gagatner - 1);
				avelacvox->next = head;
				head->prev = avelacvox;
				while (jamanakavor->next != head)
				{
					jamanakavor = jamanakavor->next;
				}
				jamanakavor->next = avelacvox;
				avelacvox->prev = jamanakavor;
				n++;
			}
		}
	}

	void jnjel(int dirq)
	{
		if (dirq > n)
			dirq = n - 1;
		else if (dirq < 0)
		{
			dirq = 0;
		}
		if (dirq == 0)
		{
			head->next->prev = head->prev;
			head->prev->next = head->next;
			koxeri_matric[head->skizb][head->verj] = 0;
			head->next = head;
			n--;
		}
		else
		{
			kox* jamanakavor = new kox;
			jamanakavor = head;
			for (int i = 0; i < dirq; i++)
			{
				jamanakavor = jamanakavor->next;
			}
			jamanakavor->next->prev = jamanakavor->prev;
			jamanakavor->prev->next = jamanakavor->next;
			koxeri_matric[jamanakavor->skizb][jamanakavor->verj] = 0;
			n--;
		}
		
		
	}

	void tpel_matric()
	{
		cout << endl;
		for (int i = -1; i < gagatner; i++)
		{
			if (i < 0) cout << "   ";
			else cout << "V" << i << " ";
		}
		cout << endl;
		for (int i = 0; i < gagatner; i++)
		{
			for (int j = -1; j < gagatner; j++)
			{
				if(j<0) cout << "V" << i << " ";
				else cout << koxeri_matric[i][j] << "  ";
			}
			cout << endl;
		}
	}

	int koxeri_qanak()
	{
		int q = 0;
		for (int i = 0; i < gagatner - 1; i++)
		{
			for (int j = i + 1; j < gagatner; j++)
			{
				if (koxeri_matric[i][j] == 1 || koxeri_matric[j][i] ==1) q++;
			}
		}
		return q;
	}

	void tpel()
	{
		kox* jamanakavor = new kox;
		jamanakavor = head;
		for (int i = 0; i < n; i++)
		{
			cout << "(" << jamanakavor->skizb << "," << jamanakavor->verj << ")\t";
			jamanakavor = jamanakavor->next;
		}
	}

	void harevanutyan_matric_ctacum() //[#2.1․2]
	{
		cout << endl << endl;
		for (int i = 0; i < gagatner - 1; i++)
		{
			for (int j = i + 1; j < gagatner; j++)
			{
				if (koxeri_matric[i][j] == 1 || koxeri_matric[j][i] == 1)
				{
					harevanutyan_matric[i][j] = harevanutyan_matric[j][i] = 1;
				}
				else
				{
					harevanutyan_matric[i][j] = harevanutyan_matric[j][i] = 0;
				}
			}
		}
		cout << endl;
		for (int i = -1; i < gagatner; i++)
		{
			if (i < 0) cout << "   ";
			else cout << "V" << i << " ";
		}
		cout << endl;
		for (int i = 0; i < gagatner; i++)
		{
			for (int j = -1; j < gagatner; j++)
			{
				if (j < 0) cout << "V" << i << " ";
				else cout << harevanutyan_matric[i][j] << "  ";
			}
			cout << endl;
		}
	}

	void kcutyan_matrici_stacum() //[#2.1․3]
	{
		bool bolory_mekusacvac = false;
		for (int i = 0; i < gagatner - 1; i++)
		{
			for (int j = i + 1; j < gagatner; j++)
			{
				if (harevanutyan_matric[i][j] == 1)
				{
					if (!bolory_mekusacvac)
					{
						cout << endl << endl << "   ";
						for (int i2 = 0; i2 < gagatner; i2++)
						{
							cout << "V" << i2 << " ";
						}
						cout << endl;
						bolory_mekusacvac = true;
					}
					cout << "e" << i << " ";
					for (int k = 0; k < gagatner; k++)
					{
						if (k == i || k == j) cout << "1  ";
						else cout << "0  ";
					}
					cout << endl;
				}
			}
		}
		if (!bolory_mekusacvac) cout << "grafum koxer chkan!\n\n";
	}

	void kaxvac_mekusacvac() //[#2.1․4]
	{
		bool kaxvac = false, mekusacvac = false;
		int mekeri_qanak ;
		for (int i = 0; i < gagatner; i++)
		{
			mekeri_qanak = 0;
			for (int j = 0; j < gagatner; j++)
			{
				if (i == j)continue;
				else if (harevanutyan_matric[i][j] == 1) mekeri_qanak++;
				
			}
			if (mekeri_qanak == 0)
			{
				cout << "V" << i << " - mekusacvac e\n";
				mekusacvac = true;
			}
			else if (mekeri_qanak == 1)
			{
				cout << "V" << i << " - kaxvac e\n";
				kaxvac = true;
			}
		}
		if (!kaxvac && !mekusacvac) cout << "ckan kaxvac kam mekusacvac gagatner !!\n\n";
	}

	void gagati_astijan_hajordakanutyun() //[#2.1․5]
	{
		int* hajordakanutyun = new int[gagatner];
		int q;
		for (int i = 0; i < gagatner; i++)
		{
			q = 0;
			for (int j = 0; j < gagatner; j++)
			{
				if (i == j) continue;
				else
				{
					if (harevanutyan_matric[i][j] == 1) q++;
				}
			}
			hajordakanutyun[i] = q;
			cout << "V" << i << " - " <<q << endl;
		}
		bool qanider = true;
		while (qanider)
		{
			qanider = false;
			for (int i = 0; i < gagatner-1; i++)
			{
				if (hajordakanutyun[i + 1] < hajordakanutyun[i])
				{
					qanider = true;
					q = hajordakanutyun[i+1] ;
					hajordakanutyun[i + 1] = hajordakanutyun[i];
					hajordakanutyun[i] = q;
				}
			}
		}
		cout << "hajordakanutyun` ";
		for (int i = 0; i < gagatner; i++)
		{
			cout  << hajordakanutyun[i] << " ";
		}
		cout << endl;
	}

	void max_gagati_astijan() //[#2.1․6]
	{
		bool arajin = false;
		int mekeri_qanak, max=0;
		for (int i = 0; i < gagatner; i++)
		{
			mekeri_qanak = 0;
			for (int j = 0; j < gagatner; j++)
			{
				if (i == j)continue;
				else if (harevanutyan_matric[i][j] == 1) mekeri_qanak++;

			}
			if (mekeri_qanak > max) max = mekeri_qanak;
		}
		for (int i = 0; i < gagatner; i++)
		{
			mekeri_qanak = 0;
			for (int j = 0; j < gagatner; j++)
			{
				if (i == j)continue;
				else if (harevanutyan_matric[i][j] == 1) mekeri_qanak++;

			}
			if (mekeri_qanak == max && max !=0)
			{
				if (arajin)
					cout << " = ";
				cout << "V" << i << "  astijan";
				arajin = true;
			}
		}
		if (max == 0) cout << "grafum koxer chkan!\n";
		else cout << " = " << max;
	}

	int min_heravorutyun3(int gagat1, int gagat2) //[#2.1․7]
	{
		int** stugvox_harevanutyan_matric = new int* [gagatner];
		for (int i = 0; i < gagatner; i++)
		{
			stugvox_harevanutyan_matric[i] = new int[gagatner];
			for (int j = 0; j < gagatner; j++)
			{
				stugvox_harevanutyan_matric[i][j] = 0;
			}
		}
		for (int i = 0; i < gagatner; i++)
		{
			for (int j = 0; j < gagatner; j++)
			{
				stugvox_harevanutyan_matric[i][j] = harevanutyan_matric[i][j];
			}
		}
		int chap = koxeri_qanak();
		int* hert = new int[chap];
		int* hajord_hert = new int[chap];
		for (int i = 0; i < chap; i++) hert[i] = hajord_hert[i] = 0;
		hert[0] = gagat1;
		int herti_hert = 1,k;
		int heravorutyun = 0;
		while (gagat1 != gagat2)
		{
			for (int l = 0; l < herti_hert; l++)
			{
				k = hert[l];
				for (int i = 0; i < gagatner; i++)
				{
					stugvox_harevanutyan_matric[i][k] = 0;
				}
			}
			int fiqsvac = herti_hert;
			herti_hert = 0;
			for (int l = 0; l < fiqsvac; l++)
			{
				k = hert[l];
				for (int i = 0; i < gagatner; i++)
				{
					if (stugvox_harevanutyan_matric[k][i] == 1)
					{
						hajord_hert[herti_hert] = i; 
						herti_hert++;
						if (i == gagat2)
						{
							gagat1 = gagat2; break;
						}
					}
				}
			}
			for (int m = 0; m < gagatner; m++)
			{
				hert[m] = hajord_hert[m];
			}
			heravorutyun++;
		}
		return heravorutyun;
	}

	int  ciklomatik() //[#2.1․8]
	{
		return koxeri_qanak() - gagatner + 1; 
	}

	int diametr() //[#2.1․9]
	{
		int heravorutyun, max = 0;
		for (int i = 0; i < gagatner; i++) 
		{
			for (int j = 0; j < gagatner; j++) 
			{ 
				heravorutyun = min_heravorutyun3(i, j); 
				if (heravorutyun > max) max = heravorutyun;
			}
		}
		return max; 
	} 

	int sharavix() //[#2.1․10]
	{
	 int heravorutyun, min,max=0; 
	 int* maximumner = new int[gagatner];
	 for (int i = 0; i < gagatner; i++) 
	 {
		 for (int j = 0; j < gagatner; j++) 
		 {
			 heravorutyun = min_heravorutyun3(i, j);
			 if (heravorutyun > max)max = heravorutyun;
			
		 }
		 maximumner[i] = max;
	 }
	 min = maximumner[0];
	 for (int i = 1; i < gagatner; i++)
	 {
		 if (maximumner[i] < min) min = maximumner[i];
	 }
	 return min; 
	}

	int ankaxutyan_tiv() //[#2.1․11]
	{
		int q = 0;
		for (int i = 0; i < gagatner - 1; i++)
		{
			for (int j = i+1; j < gagatner; j++)
			{
				if (harevanutyan_matric[i][j] == 0) q++;
			}
		}
		return q / 2;
	}

};

int main()
{
	koxer ob;
	ob.avelacnel(); // 0-1
	ob.avelacnel(); // 0-3 
	ob.avelacnel(); // 0-4
	ob.avelacnel(); // 0-5
	ob.avelacnel(); // 1-2
	ob.avelacnel(); // 1-3
	ob.avelacnel(); // 1-5
	ob.avelacnel(); // 2-3
	ob.avelacnel(); // 4-5
	ob.avelacnel(); // 5-6
	int  gagatner = ob.gagatneri_tiv();

	cout << "koxeri qanaky = " << ob.koxeri_qanak() << endl;
	cout << endl << endl;
	
	ob.harevanutyan_matric_ctacum();
	ob.kcutyan_matrici_stacum();
	cout << endl;
	ob.kaxvac_mekusacvac();
	cout << endl;
	ob.gagati_astijan_hajordakanutyun();
	cout << endl;
	ob.max_gagati_astijan();
	int arajin, erkrord;
	cout << endl;
	do
	{
		cout << endl << "nermuceq gagatner" << endl;
		cin >> arajin >> erkrord;
		if ((arajin < 0 || arajin >gagatner) && (erkrord < 0 || erkrord >gagatner))
		{
			cout << "tivy petqa lini 0ic " << gagatner << " hatvacum\n";
		}
	} while ((arajin < 0 || arajin >gagatner) && (erkrord < 0 || erkrord >gagatner));
	cout << endl;
	cout << "min heravorutyun = "<< ob.min_heravorutyun3(arajin, erkrord) << endl;
	cout << endl;
	cout << "diametr = " << ob.diametr() << endl;
	cout << endl;
	cout << "sharavix = " << ob.sharavix() << endl;
	cout << endl;
	cout << "ciklomatik = " << ob.ciklomatik() << endl;
	cout << endl;
	cout << "ankaxutyan tivy = " << ob.ankaxutyan_tiv() << endl;
	return 0;
}