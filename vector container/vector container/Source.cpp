/*#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<int> arr = {1,2,3,4,5,6};
    
    cout << arr[0] << endl;
    
    vector<int>::iterator it;
    
    cout << arr.max_size()<< endl;
    cout <<arr.size()<<endl;
    for( it = arr.begin()+1;it <arr.end();++it)
    {
 
        cout << *it << " " ;
        
    }
    
    return 0;
}	*/

#include <iostream>
#include <stdlib.h>
#include "Vector_Header.h"

using namespace std;

int main()
{
	vector<float> obj(16);
	obj.size();
	obj.print_v();
	cout << "##############\n";

    for (int i = 0; i < 16; i++)
    {
        cout << obj[i] << "\t";
    }
    cout << endl; cout << endl;
    for (int i = 0; i < 16; i++)
    {
        obj[i] = i + 2;
        cout << obj[i] << "\t";
    }

    vector<float> obj2;

    obj2.size();
    obj2.push_back(3);
    obj2.size();
    obj2.push_back(5);
    obj2.size();
    obj2.push_back(7);
    obj2.size();

    cout << endl; cout << endl;
    
    obj2 = obj;


    obj2.pop_back();
    for (auto i : obj2)
    {
        cout << i << endl;
    }
    /*obj.size();
    for (int i = 0; i < 16; i++)
    {
        cout << obj[i] << "\t";
    }
    cout << endl; cout << endl;

    vector<int> p;*/

  /*  obj = p;
    obj.size();*/
  

    if (obj2 == obj)
    {
        obj.print_v();
        cout << endl << endl;
        obj2.print_v();
        cout << "end" << endl;

    }
    else
        cout << "error" << endl;
	return 0;
}