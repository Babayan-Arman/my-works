#include <iostream>
#include <math.h>
#include <string>
using namespace std;


struct popoxakan  
{
	bool arjeq;
	bool fiktiv;
}; //[#1.1]

struct list
{
	popoxakan info;
	list* next;
};//[#1.2]

struct list_int
{
	int info;
	string  gorcoxutyun;
	list_int* next;
};//[#1.3]

class C_list //[#1.4]
{
private:
	list* head;
	list* end;
public:
	C_list()
	{
		head = new list;
		head->next = end;
		end = head;
		end->next = head;
	}

	void add_right(popoxakan arjeq)
	{
		list* jamanakavor = new list;
		jamanakavor->info = arjeq;
		end->next = jamanakavor;
		end = jamanakavor;
		end->next = head;
	}

	popoxakan oxak(int dirq)
	{
		list* jamanakavor = new list;
		jamanakavor = head;
		for (int i = 0; i <= dirq; i++)
		{
			jamanakavor = jamanakavor->next;
		}
		return jamanakavor->info;
	}

	void popoxel_fiktivutyun(int dirq)
	{
		list* jamanakavor = new list;
		jamanakavor = head;
		for (int i = 0; i <= dirq; i++)
		{
			jamanakavor = jamanakavor->next;
		}
		jamanakavor->info.fiktiv = !(jamanakavor->info.fiktiv);

	}

	popoxakan iskutyan_vektori_tarr()
	{
		return end->info;
	}
	int size()
	{
		list* jamanakavor = new list;
		jamanakavor = head;
		int size=0;
		while(jamanakavor->next != head)
		{
			jamanakavor = jamanakavor->next;
			size++;
		}
		return size;
	}

	void tpel()
	{
		list* jamanakavor = new list;
		jamanakavor = head;
		cout << "\t";
		while (jamanakavor->next != head)
		{
			jamanakavor = jamanakavor->next;
			cout << "|   " <<(jamanakavor->info).arjeq <<  "\t";
		}
		cout << "|\n";
		jamanakavor = head;
	}
	
	~C_list()
	{

	}
};

class C_list_popoxakan   //[#1.5]
{
private:
	list_int* head;
	int popoxakanneri_qanak;
	int n;
	
public:
	C_list_popoxakan()
	{

	}
	void avelacnel(int popoxakanneri_qanak1)
	{
		popoxakanneri_qanak = popoxakanneri_qanak1;
		head = new list_int;
		head->info = n = 1;
		head->gorcoxutyun = "x" + to_string(n);
		head->next = NULL;
		for (int i = 2; i <= popoxakanneri_qanak1; i++)
		{
			list_int* jamanakavor = new list_int;
			list_int* avelacvox = new list_int;
			jamanakavor = head;
			while (jamanakavor->next != NULL)
			{
				jamanakavor = jamanakavor->next;
			}
			++n;
			avelacvox->info = n;
			avelacvox->gorcoxutyun = "x" + to_string(n);
			avelacvox->next = NULL;
			jamanakavor->next = avelacvox;
		}
	}

	list_int  oxak(int dirq)
	{
		list_int* jamanakavor = new list_int;
		jamanakavor = head;
		list_int oxak;
		for (int i = 1; i <= dirq; i++)
		{
			jamanakavor = jamanakavor->next;
		}
		oxak.info = jamanakavor->info;
		oxak.gorcoxutyun = jamanakavor->gorcoxutyun;
		return oxak;

	}

	void add_right(int hraman = 0, int syun1 = 0, int syun2 = 0)
	{
		
		list_int* jamanakavor = new list_int;
		jamanakavor = head;
		list_int* avelacvox = new list_int;
		while (jamanakavor->next != NULL)
		{
			jamanakavor = jamanakavor->next;
		}
		++n;
		avelacvox->info = n;
		avelacvox->next = NULL;
		jamanakavor->next = avelacvox;	
		switch (hraman)
		{
			case 0:
			{
				avelacvox->gorcoxutyun = "f(";
				for (int i = 0; i < popoxakanneri_qanak; i++)
				{
					avelacvox->gorcoxutyun = avelacvox->gorcoxutyun + oxak(i).gorcoxutyun + ",";
				}
				avelacvox->gorcoxutyun = avelacvox->gorcoxutyun + ")";
				break;
			}
			case 2:
			{
				
				avelacvox->gorcoxutyun = "(" + (oxak(syun1)).gorcoxutyun + ") AND ("  + (oxak(syun2)).gorcoxutyun +")";
				break;
			}
			case 3:
			{
				
				avelacvox->gorcoxutyun = "(" + (oxak(syun1)).gorcoxutyun + ") OR ("  + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 4:
			{

				avelacvox->gorcoxutyun = "NOT (" + (oxak(syun1)).gorcoxutyun + ")";
				break;
			}
			case 5:
			{
				avelacvox->gorcoxutyun = "only_0(" + (oxak(syun1)).gorcoxutyun +","+(oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 6:
			{
				avelacvox->gorcoxutyun = "only_1(" + (oxak(syun1)).gorcoxutyun + "," + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 7:
			{
				avelacvox->gorcoxutyun = "(" + (oxak(syun1)).gorcoxutyun + ") XOR (" + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 8:
			{
				avelacvox->gorcoxutyun = "(" + (oxak(syun1)).gorcoxutyun + ") NOR (" + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 9:
			{
				avelacvox->gorcoxutyun = "(" + (oxak(syun1)).gorcoxutyun + ") NAND (" + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 10:
			{
				avelacvox->gorcoxutyun = "equality(" + (oxak(syun1)).gorcoxutyun + "," + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
			case 11:
			{
				avelacvox->gorcoxutyun = "implication(" + (oxak(syun1)).gorcoxutyun + "," + (oxak(syun2)).gorcoxutyun + ")";
				break;
			}
		}
	}

	void  delete_right()
	{
		list_int* jamanakavor = new list_int;
		jamanakavor = head;
		while (jamanakavor->info != n-1)
		{
			jamanakavor = jamanakavor->next;
		}
		jamanakavor->next = NULL;
		--n;
	}

	int size()
	{
		list_int* jamanakavor = new list_int;
		jamanakavor = head;
		int size = 0;
		while (jamanakavor->next != NULL)
		{
			jamanakavor = jamanakavor->next;
			size++;
		}
		return size;
	}

	void tpel()
	{
		list_int* jamanakavor = new list_int;
		jamanakavor = head;

		while (jamanakavor  != NULL)
		{
			cout << "\t " << jamanakavor->info << ". " << (jamanakavor->gorcoxutyun) << endl;
			jamanakavor = jamanakavor->next;
		}
		cout << endl;
	}

	~C_list_popoxakan()
	{

	}
};

class C_popoxakan //[#1.6]
{
private:
	popoxakan** x;
	int n;
	
public:
	C_popoxakan()
	{

	}
	void avelacnel(int qanak) //[#1.6.1]
	{
		n = qanak;
		int i, erkarutyun = pow(2, qanak);
		x = new popoxakan * [qanak];
		for (i = 0; i < qanak; i++)
		{
			x[i] = new popoxakan[erkarutyun];
		}

		for (i = 0; i < qanak; i++)
		{

			int cucich = 0;
			while (cucich < erkarutyun)
			{
				for (int j = 0; j < pow(2, i); j++)
				{
					x[i][cucich].arjeq = false;
					x[i][cucich++].fiktiv = false;
				}

				for (int j = 0; j < pow(2, i); j++)
				{
					x[i][cucich].arjeq = true;
					x[i][cucich++].fiktiv = false;
				}
			}
		}
	}

	popoxakan tarr(int tox, int syun)
	{
		return x[n-syun-1][tox];
	}

	bool AND(bool x1, bool x2) //[#1.6.2]
	{
		return x1 && x2;
	}
	bool NOT(bool x1)
	{
		return !x1;
	}
	bool OR(bool x1, bool x2)
	{
		return x1 || x2;
	}
	bool only_0(bool x1, bool x2)
	{
		return 0;
	}
	bool only_1(bool x1, bool x2)
	{
		return 1;
	}
	bool mod2(bool x1, bool x2) //XOR
	{
		return ((x1 && !x2) || (!x1 && x2));
	}	
	bool Pirsslac(bool x1 , bool x2) //NOR
	{
		return (!x1 && !x2);
	}
	bool SheferShrix(bool x1, bool x2) //NAND
	{
		return (!x1 || !x2);
	}
	bool equality(bool x1, bool x2) 
	{
		return ((x1 && x2) || (!x1 && !x2));
	}
		
	bool implication(bool x1 , bool x2)
	{
		return (!x1 || x2);
	}

	void tpel()
	{
		for (int j = 0; j < pow(2, n); j++)
		{
			for (int i = n-1; i >= 0; i--)
			{
				cout << x[i][j].arjeq << " ";
			}
			cout << endl;
		}
	}

	void tpel_horizonakan()
	{
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < pow(2, n); j++)
			{
				cout << x[i][j].arjeq << " ";
			}
			cout << endl;
		}
	}

	void fiktivutyu_stugox(C_list* p1, C_list_popoxakan& anunner1) //[#1.6.3]
	{
		anunner1.add_right();
		system("cls");
		cout << "\t";
		for (int i = 0; i <= n; i++)
		{
			cout << "________";
		}
		cout << "_\n\t";
		for (int i = 0; i < n; i++)
		{
			cout << "|   " << (anunner1.oxak(i).info) << "\t";
		}
		cout << "|   " << (anunner1.oxak(p1[0].size()-1).info) << "\t";
		cout << "|\n";
		cout << "\t";
		for (int i = 0; i <= n; i++)
		{
			cout << "|_______";
		}
		cout << "|\n";
		for (int w = 0; w < pow(2, n); w++)
		{
			cout << "\t";
			for (int i = 0; i < n; i++)
			{
				cout << "|   " << p1[w].oxak(i).arjeq << "\t";
			}
			cout << "|   " << p1[w].oxak((p1[0].size() - 1)).arjeq << "\t|\n";
		}
		cout << "\t";
		for(int i =0;i<=n;i++)
		{
			cout << "|_______";
		}
		cout << "|\n";
		cout << "\n\n";
		for (int i = 0; i < n; i++)
		{
			cout << "\t" << anunner1.oxak(i).info << ". " << anunner1.oxak(i).gorcoxutyun << endl;;
		}
		cout << "\t" << anunner1.oxak(p1[0].size()-1).info << ". " << anunner1.oxak(p1[0].size()-1).gorcoxutyun << endl;
		cout << "\n";

		for (int popoxakan_hamar = 0; popoxakan_hamar < n; popoxakan_hamar++)
		{
			int fiktivutyun = 0, arajin_tarr, erkrord_tarr;
			cout << "\n\t\t" << anunner1.oxak(popoxakan_hamar).gorcoxutyun << endl;
			for (int arjeq = 0; arjeq < 2; arjeq++)
			{
				for (int i = 0; i < pow(2, n); i++)
				{
					int sum = 0;

					for (int j = 0; j < n; j++)
					{
						sum += (int)(p1[i].oxak(j)).arjeq;
					}
					if ((sum - int((p1[i].oxak(popoxakan_hamar)).arjeq)) % (n - 1) == 0 \
						&& int(((p1[i].oxak((popoxakan_hamar + 1) % n)).arjeq)) == arjeq)		//stuguma ete mnacac popoxakanneri gumari qanord@ ira mnacac popoxakanneri qakaki vra																																			//1d tarreric meky 0ya kam mek myusnern el en nuyn arajin [paymanic	
					{															// talisa 0 ete gumary 0ya aysinqn bolor tarrery 0 en kam(n - 1)a erb bolory 1 en u ete 
						arajin_tarr = i;
						for (i = i + 1; i < pow(2, n); i++)
						{
							sum = 0;
							for (int j = 0; j < n; j++)
							{
								sum += (int)(p1[i].oxak(j)).arjeq;
							}
							if ((sum - int((p1[i].oxak(popoxakan_hamar)).arjeq)) % (n - 1) == 0 \
								&& int(((p1[i].oxak((popoxakan_hamar + 1) % n)).arjeq)) == arjeq)
							{
								erkrord_tarr = i;
								if (equality(p1[arajin_tarr].iskutyan_vektori_tarr().arjeq, p1[erkrord_tarr].iskutyan_vektori_tarr().arjeq))
								{
									fiktivutyun++;

									cout << "\t" << arajin_tarr << "<->" << erkrord_tarr << " fiktiv" << endl;
									i = pow(2, n);
								}
								else
								{

									cout << "\t" << arajin_tarr << "<->" << erkrord_tarr << " eakan"  << endl;
									arjeq += 2;
								}

							}

						}
					}

				}


			}
			if (fiktivutyun == 2)
			{
				for (int k = 0; k < pow(2, n); k++)
				{
					p1[k].popoxel_fiktivutyun(popoxakan_hamar);
				}
			}
		}
		anunner1.delete_right();
		cout << endl << endl;
	}

	void aranc_fiktivneri(C_list* p)   //[#1.6.4]
	{
		int m = n, iq = 0, br;
		for (int j = 0; j < n; j++)
		{
			if ((p[0].oxak(j)).fiktiv)
			{
				m--;
			}
		}
		C_list *q = new C_list[pow(2, m)];
		C_list_popoxakan q_anunner;
		q_anunner.avelacnel(m);
		for (int i = 0; i < pow(2, n); i++)
		{
			br = 0;
			for (int w = 0; w < n; w++)
			{
				if ((p[i].oxak(w)).fiktiv && (p[i].oxak(w)).arjeq)
				{
					br++;
				}
			}
			if (br)
			{
				continue;
			}
			for (int j = 0; j < n; j++)
			{

				if ((p[i].oxak(j)).fiktiv)
				{
					continue;
				}
				else
				{
					q[iq].add_right(p[i].oxak(j));
				}
			}

			q[iq].add_right(p[i].iskutyan_vektori_tarr());
			iq++;
		}

		q_anunner.add_right();
		int  erkarutyun = q[0].size();
		cout << "\t";
		for (int i = 0; i < erkarutyun; i++)
		{
			cout << "________";
		}
		cout << "_\n";
		cout << "\t";
		for (int i = 0; i < erkarutyun; i++)
		{
			cout << "|   " << (q_anunner.oxak(i).info) << "\t";
		}
		cout << "|\n";
		cout << "\t";
		for (int i = 0; i < erkarutyun; i++)
		{
			cout << "|_______";
		}
		cout << "|\n";
		for (int i = 0; i < pow(2, m); i++)
		{
			q[i].tpel();
		}
		cout << "\t";
		for (int i = 0; i < erkarutyun; i++)
		{
			cout << "|_______";
		}
		cout << "|\n\n";
		for (int i = 0; i <= m; i++)
		{
			cout << "\t" << q_anunner.oxak(i).info << "."<< q_anunner.oxak(i).gorcoxutyun << endl;

		}
		q_anunner.delete_right();
	}

	void kdndz(C_list* p)  //[#1.6.5]
	{
		bool verjin1 = false;
		bool arajin1 = true;
		string kdndz = "";
		cout << "\n\tKataryal dizyunktiv normal dzev \n\n";
		for (int i = 0; i < pow(2, n); i++)
		{
			if (p[i].iskutyan_vektori_tarr().arjeq)
			{
				if (!arajin1)
				{
					verjin1 = true;
				}
				if (verjin1)
				{
					kdndz += " OR ";
					verjin1 = false;
				}
				kdndz += "(";
				for (int j = 0; j < n; j++)
				{
					if (p[i].oxak(j).arjeq)
					{
						kdndz += "(x" + to_string(j) + ")";
					}
					else
					{
						kdndz += "!(x" + to_string(j) + ")";
					}
					if (j != n - 1)
					{
						kdndz += " * ";
					}
					else
					{
						kdndz += ")";
					}
				}
				arajin1 = false;
			}
			else
			{
				continue;
			}
		}
		cout << "\t" << kdndz << endl;
	}

	void kkndz(C_list* p)  //[#1.6.6]
	{
		bool verjin2 = false;
		bool arajin2 = true;
		string kkndz = "";
		cout << "\n\tKataryal konyuktiv normal dzev \n\n";
		for (int i = 0; i < pow(2, n); i++)
		{
			if (p[i].iskutyan_vektori_tarr().arjeq)
			{
				continue;
			}
			else
			{
				if (!arajin2)
				{
					verjin2 = true;
				}
				if (verjin2)
				{
					kkndz += " ^ ";
					verjin2 = false;
				}
				kkndz += "(";
				for (int j = 0; j < n; j++)
				{
					if (p[i].oxak(j).arjeq)
					{
						kkndz += "!(x" + to_string(j) + ")";
					}
					else
					{
						kkndz += "(x" + to_string(j) + ")";
					}
					if (j != n - 1)
					{
						kkndz += " OR ";
					}
					else
					{
						kkndz += ")";
					}
				}
				arajin2 = false;
			}
		}
		cout << "\t" << kkndz << endl;
	}

	~C_popoxakan()
	{
		for (int i = 0; i < n; i++)
		{
			delete[] x[i];
			x[i] = 0;
		}
		delete[] x; 
		x = 0;
	}
};




int main() //[#1.7]
{
	int main_out = 1, main_hraman, n;
	bool arajin_qayl = true, erkrord_qayl,errord_qayl,jegalkin_in;
	int** anoroshi_matric = 0, **anoroshi_lracucich_matric=0;
	C_popoxakan ob;
	C_list* p =0;
	C_list_popoxakan anunner;
	while(main_out)
	{
		
		cout << "\t\t\t Menu\n";
		cout << "\t1. Nshel popoxakanneri qankany \n";
		cout << "\t2. Gorcoxutyunner \n";
		cout << "\t3. Fiktivutyan stugum \n";
		cout << "\t4. Tpel aranc fiktiv tareri \n";
		cout << "\t5. Kataryal normal dzever \n";
		cout << "\t6. Jegalkini bazmandam \n";
		cout << "\t7. EXIT \n\n\n";
		do
		{
			cout << "\thraman - ";
			cin >> main_hraman;
			if (main_hraman < 1 || main_hraman>7)
			{
				cout << "\tNman hraman chka!!!!\n";
			}
			else if (main_hraman !=1 && arajin_qayl)
			{
				cout << "\tSkzbic nermuceq popoxakanneri qanaky!!!\n";
				main_hraman = 0;

			}
		} while (main_hraman < 1 || main_hraman>7);
		switch (main_hraman)
		{
			case 1:
			{
				do
				{
					system("cls");
					cout << "\n\n\tpopoxakanneri qanaky = "; cin >> n;
				} while (n < 1);
				p = new C_list[pow(2, n)];
				ob.avelacnel(n);
				anunner.avelacnel(n);
				for (int i = 0; i < pow(2, n); i++)			//es cikly karevora skzbnarjeqavoruma !!!!!!!!!!!!!!!!!
				{
					for (int j = 0; j < n; j++)
					{
						p[i].add_right(ob.tarr(i, j));
					}
				}
				arajin_qayl = false;
				erkrord_qayl = true;
				errord_qayl = true;
				jegalkin_in = true;
				system("cls");
				break;
			}
			case 2:
			{
				int i, j;
				int hraman, out = 1, quest = 0;				
				while (out)
				{
					cout << "\t\t\t Gorcoxutyunner\n";
					cout << "\t1. Tpel \n";
					cout << "\t2. AND \n";
					cout << "\t3. OR \n";
					cout << "\t4. NOT \n";
					cout << "\t5. only_0 \n";
					cout << "\t6. only_1 \n";
					cout << "\t7. XOR \n";
					cout << "\t8. NOR \n";
					cout << "\t9. NAND \n";
					cout << "\t10. equality \n";
					cout << "\t11. implication \n";
					cout << "\t12. EXIT \n\n\n";
					if (quest)
					{
						hraman = 1;
						quest--;
					}
					else
					{
						do
						{
							cout << "\thraman - ";
							cin >> hraman;
							if (hraman < 1 || hraman>12)
							{
								cout << "\tNman hraman chka!!!!\n";
							}
						} while (hraman < 1 || hraman>12);
					}
					cout << "\n\n";
					switch (hraman)
					{
					case 1:
					{
						system("cls");
						int  erkarutyun = p[0].size();
						cout << "\t";
						for (int i = 0; i < erkarutyun; i++)
						{
							cout << "________";
						}
						cout << "_\n";
						cout << "\t";
						for (int i = 0; i < erkarutyun; i++)
						{
							cout << "|   " << (anunner.oxak(i).info) << "\t";
						}
						cout << "|\n";
						cout << "\t";
						for (int i = 0; i < erkarutyun; i++)
						{
							cout << "|_______";
						}
						cout << "|\n";
						for (i = 0; i < pow(2, n); i++)
						{
							p[i].tpel();
						}
						cout << "\t";
						for (int i = 0; i < erkarutyun; i++)
						{
							cout << "|_______";
						}
						cout << "|\n\n";
						anunner.tpel();
						cout << "\n";
						break;
					}
					case 2:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						// toxeri u syuneri hamarakalumy:     0  1  2   isk arjeqy yndunuma 1-ic orinak 8
						syun1--;							//									0 *  *  *
						syun2--;							//									1 *	 *	*
															//									2 *  *  *
						anunner.add_right(hraman, syun1, syun2);

						popoxakan m;
						//m.fiktiv = false;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.AND((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 3:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);

						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.OR((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 4:
					{
						int syun1, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);

						syun1--;
						anunner.add_right(hraman, syun1);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.NOT((p[i].oxak(syun1)).arjeq);
							p[i].add_right(m);

						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 5:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.only_0((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 6:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.only_1((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 7:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);

						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.mod2((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 8:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.Pirsslac((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 9:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.SheferShrix((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 10:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.equality((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 11:
					{
						int  syun1, syun2, erkarutyun = p[0].size();
						do
						{
							cout << "syun1 = "; cin >> syun1;
							if (syun1<1 || syun1>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun1<1 || syun1>  erkarutyun);
						do
						{
							cout << "syun2 = "; cin >> syun2;
							if (syun2<1 || syun2>  erkarutyun)
							{
								cout << "aydpisi popoxakan chka !!" << endl;
							}
						} while (syun2<1 || syun2>  erkarutyun);

						syun1--;
						syun2--;
						anunner.add_right(hraman, syun1, syun2);
						popoxakan m;
						for (int i = 0; i < pow(2, n); i++)
						{
							m.arjeq = ob.implication((p[i].oxak(syun1)).arjeq, (p[i].oxak(syun2)).arjeq);
							p[i].add_right(m);
						}
						cout << "case " << hraman << ": Done\n\n\n";
						quest++;
						erkrord_qayl = false;
						break;
					}
					case 12:
					{
						out--;
						system("cls");
						break;
					}
					}
				}
				break;
			}
			case 3:
			{
				// fiktivutyun stugman funkcia
				if (erkrord_qayl)
				{
					system("cls");
					cout << "\tIskutyan vektor chka!!!\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					ob.fiktivutyu_stugox(p, anunner);
					errord_qayl = false;
				}
				break;
			}
			case 4:
			{
				// fiktivner hanox, nor eakanneric stacox funkcia
				if (erkrord_qayl)
				{
					system("cls");
					cout << "\tIskutyan vektor chka!!!\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					if (errord_qayl)
					{
						ob.fiktivutyu_stugox(p, anunner);
						ob.aranc_fiktivneri(p);
					}
					else
					{
						ob.aranc_fiktivneri(p);
					}
				

				}
				break;
			}
			case 5:
			{
				
				if (erkrord_qayl)
				{
					system("cls");
					cout << "\tIskutyan vektor chka!!!\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					int hraman;
					int out = 1;

					while (out)
					{

						cout << "\t\t\t Kataryal normal dzever \n";
						cout << "\t1. Kataryal disyuktiv normal dzev\n";
						cout << "\t2. Kataryal konyuktiv normal dzev\n";
						cout << "\t3. Erkusn el miasin\n";
						cout << "\t4. Exit\n\n\n";
						do
						{
							cout << "\thraman - ";
							cin >> hraman;
							if (hraman > 4 || hraman < 1)
							{
								cout << "\tNman hraman chka!!!!\n";
							}
						} while (hraman > 4 || hraman < 1);
						switch (hraman)
						{
						case 1:
						{

							system("cls");
							int  erkarutyun = p[0].size();
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "________";
							}
							cout << "_\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|   " << (anunner.oxak(i).info) << "\t";
							}
							cout << "|\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n";
							for (int i = 0; i < pow(2, n); i++)
							{
								p[i].tpel();
							}
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n\n";
							ob.kdndz(p);

							break;
						}
						case 2:
						{
							system("cls");
							int  erkarutyun = p[0].size();
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "________";
							}
							cout << "_\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|   " << (anunner.oxak(i).info) << "\t";
							}
							cout << "|\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n";
							for (int i = 0; i < pow(2, n); i++)
							{
								p[i].tpel();
							}
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n\n";
							ob.kkndz(p);
							break;
						}
						case 3:
						{
							system("cls");
							int  erkarutyun = p[0].size();
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "________";
							}
							cout << "_\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|   " << (anunner.oxak(i).info) << "\t";
							}
							cout << "|\n";
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n";
							for (int i = 0; i < pow(2, n); i++)
							{
								p[i].tpel();
							}
							cout << "\t";
							for (int i = 0; i < erkarutyun; i++)
							{
								cout << "|_______";
							}
							cout << "|\n\n";
							ob.kdndz(p);
							ob.kkndz(p);
							break;
						}
						case 4:
						{
							system("cls");
							out--;
							break;
						}
						}
					}
				}
				

				break;
			}
			case 6:
			{

				if (erkrord_qayl)
				{
					system("cls");
					cout << "\tIskutyan vektor chka!!!\n\n";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					string jegalkin = "";
					int erkarutyun = pow(2, n);
					if (jegalkin_in)
					{
						anoroshi_matric = new int* [erkarutyun];
						for (int i = 0; i < erkarutyun; i++)
						{
							anoroshi_matric[i] = new int[erkarutyun + 1];
						}
						anoroshi_lracucich_matric = new int* [n];
						for (int i = 0; i < erkarutyun; i++)
						{
							anoroshi_lracucich_matric[i] = new int[erkarutyun];
						}
						jegalkin_in = false;
					}
					for (int i = 0; i < n; i++)
					{
						for (int j = 0; j < erkarutyun; j++)
						{
							anoroshi_lracucich_matric[i][j] = ob.tarr(j, i).arjeq;
						}
					}

					for (int i = 0; i < erkarutyun; i++)
					{
						for (int j = 0; j < erkarutyun+1; j++)
						{
							if (j == erkarutyun)
							{
								anoroshi_matric[i][j] = p[i].iskutyan_vektori_tarr().arjeq;
							}
							else
							{
								anoroshi_matric[i][j] = 1;
								for (int k = 0; k < n; k++)
								{

									int skizb = 0;
									if (anoroshi_lracucich_matric[k][j] == 0)
									{
										skizb++;
									}
									else
									{
										if (skizb != n)
										{
											anoroshi_matric[i][j] *= ob.tarr(i, k).arjeq;
										}
									}

								}
							}
							

						}
					}
					
					for (int i = 0; i < erkarutyun; i++)
					{
						int mekeri_qanak = 0,j;
						for (j = 0; j < i; j++)
						{
							if (anoroshi_matric[i][j] == 1)
								mekeri_qanak++;
						}
						if (anoroshi_matric[i][erkarutyun] == 1)
						{
							if (mekeri_qanak % 2 == 1)
							{
								for (int k = 0; k < erkarutyun; k++)
								{
									anoroshi_matric[k][j] = 0;
								}
							}
							
						}
						else
						{
							if (mekeri_qanak % 2 == 0)
							{
								for (int k = i; k < erkarutyun; k++)
								{
									anoroshi_matric[k][j] = 0;
								}
							}
						}

					
					}

					
					bool arajin = false;
					int errord=0,erkrord;
					for (int j = 0; j < erkarutyun ; j++)
					{
						string andam = "";
						
						if (anoroshi_matric[erkarutyun - 1][j] == 1)
						{
							int q = 0;
							erkrord = 0;
							for (int k = 0; k < n; k++)
							{
								if (anoroshi_lracucich_matric[k][j] == 1)
								{
									erkrord++;
									if (erkrord > 1)
									{
										andam += "^";
									}
									andam += "x" + to_string(k + 1);
									arajin = true;
								}
								else
								{
									q++;
								}
								if (q == n)
								{
									andam += "1";
									arajin = true;
								}
							}
							if(arajin) errord++;
							if (errord >1)
							{
								jegalkin += " XOR ";

							}
							jegalkin += andam;
							arajin = false;

						}
					}
					cout << "\n\tjegalkini bazmandamnn e` " << jegalkin << " = " << anoroshi_matric[erkarutyun - 1][erkarutyun] << "\n\n\n";
				}
				
				break;
			}
			case 7:
			{
				main_out--;
				break;
			}
		}
	}
	delete[] p; p = 0;
	return 0;
}

