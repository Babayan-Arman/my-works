
#include "logic.h"

int main()
{
	system("cls");
	cout << "\t\t\t\tTertis \n\n\n";
	cout << "\t1. sksel\n";
	cout << "\t2. karavarum\n";
	bool over = true,onetime = false;
	char n;
	n = _getch();
	while (over)
	{
		
		if (n == '1')
		{
			system("cls");
			start();
			over = false;
			onetime = false;
			
		}
		else if (n == '2')
		{
			system("cls");
			cout << "\t\t\t\tTertis \n\n\n";
			cout << "\t1. sksel\n";
			cout << "\t2. karavarum\n\n";
			cout << "\t 'w' for hard drop\n";
			cout << "\t 'a' for down\n";
			cout << "\t 's' for left\n";
			cout << "\t 'd' for right\n";
			cout << "\t 'k' for left rotate \n";
			cout << "\t 'l' for right rotate \n";
			cout << "\t 'o' for reserv\n";
			n = _getch();
		}
		else
		{
			system("cls");
			cout << "\t\t\t\tTertis \n\n\n";
			cout << "\t1. sksel\n";
			cout << "\t2. karavarum\n\n";
			cout << "nman hraman chka!!\n";
			n = _getch();
		}
		
		while (!over)
		{
			if (!onetime)
			{
				cout << "\t1. Restart \n";
				cout << "\t2. Exit\n";
			}
			n = _getch();
			if (n == '1') over = !over;
			else if (n == '2') break;
			else
			{
				if (!onetime)
				{
					cout << "nman hraman chka!!\n";
					onetime = !onetime;
				}
			}
		}
			

	}

	return 0;
}