#pragma once

using namespace std;

template <typename T>
class vector
{
private:
	T* ptr;
	int data;
	int capacity;
public:
	vector()
	{
		capacity = 0;
		data = 0;
		ptr = (T*)malloc(sizeof(T) * capacity);
	}

	vector(int a)
	{
		capacity = a;
		ptr = (T*)malloc(sizeof(T) * capacity);
		for (T* ptr_i = begin(); ptr_i != begin() + a; ++ptr_i)
		{
			push_back(0);
		}
	}

	vector(int a, int b)
	{
		capacity = a;
		ptr = (T*)malloc(sizeof(T) * capacity);
		for (T* ptr_i = begin(); ptr_i != begin() + a; ++ptr_i)
		{
			push_back(b);
		}
	}

	T* begin()
	{
		return  ptr;
	}

	T* end()  //ete sa jnjem "range based for"-@ chi ashxati ???????
	{
		return ptr + data;
	}

	void push_back(T a)
	{
		if (data >= capacity)
		{
			T* R_ptr;
			if (capacity == 0)
			{
				R_ptr = (T*)realloc(ptr, sizeof(T));
				capacity++;
			}
			else
			{
				R_ptr = (T*)realloc(ptr, sizeof(T) * 2 * capacity);
				capacity *= 2;
			}
			if (R_ptr == nullptr)
			{
				cout << "there isn't memory \n\n";
			}
			else
			{
				cout << "Capacity changed! adress.1: " << ptr << " adress.2: " << R_ptr<<  endl;
				ptr = R_ptr;
				*(begin() + data) = a;
				data++;
			}
			
		}
		else
		{
			*(begin() + data) = a;
			data++;
		}
	}
	
	void pop_back()
	{
		data--;
	}

	void size()
	{
		cout << "capacity = " << capacity << endl;
		cout << "data = " << data << endl;

	}
	int size_data()
	{
		return data;
	}
	int size_capacity()
	{
		return capacity;
	}

	void print_v()
	{
		for (T* ptr_i = begin(); ptr_i != end(); ++ptr_i)
		{
			cout << *(ptr_i)<<endl;
		}
	}

	T& operator [] (int index)
	{
		return *(begin() + index);
	}
	
	void operator = (vector<T>& obj)
	{
		if (capacity >= obj.size_data())
		{
			data = obj.size_data();
			for (int i = 0; i < obj.size_data(); ++i)
			{
				*(begin() + i) = obj[i];
			}
			for (int i = obj.size_data(); i < this->capacity; ++i)
			{
				*(begin() + i) = 0;
			}
		}
		else
		{
			data = capacity;
			for (int i = 0; i < this->capacity; i++)
			{
				*(begin() + i) = obj[i];
			}
			for (int i = this->capacity; i < obj.size_data(); i++)
			{
				push_back(obj[i]);
			}
		}
	}

	bool operator == (vector<T>& obj)
	{
		if (data != obj.size_data()) return false;
		for (int i = 0; i < data; i++)
		{
			if (ptr[i] != obj[i]) return false;
		}
		return true;
	}

	
	
	void ptrshow()
	{
		cout << ptr << endl;
	}
	~vector()
	{
		free(ptr);
		cout << "end of vector " << data << " " << capacity << " " << ptr << "\n\n";
	}

};