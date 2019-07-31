#pragma once
#include <iostream>
using namespace std;
#include<iostream>
#include<vector>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <windows.h>
#include <ctime>
#include <thread>
#include <mutex>


template <typename T>
class myvector
{
public:

	myvector()
	{
		elem = nullptr;
		startptr = nullptr;
			endptr = nullptr;
			save = nullptr;
		sz = 0;
		remain = 0;
		cout << "�޲ι���" << endl;
	}
	myvector(T s) :sz(s), elem(new T[s]),save(nullptr)//���캯��������s��doubleԪ�أ���s���浽size�в���elemָ����Ԫ�ص�ַ
	{
		startptr = elem[0];
		endptr = elem[s]
		remain = 0;
		cout << "�вι���" << endl;
	}

	myvector(const myvector& vec) :elem(new T[vec.sz]), sz(vec.sz) //�������캯�� ����ָ�������� Ч�ʵ���
	{
		cout << "��������" << endl;
		for (int i = 0; i < vec.sz; i++)
		{
			elem[i] = vec.elem[i];
		}
	}
	myvector(myvector&& vec) noexcept //�ƶ����죬���vec�˺���Ҫ�����
	{
		this->elem = vec.elem;
		this->sz = vec.sz;
		delete vec.elem;
		vec.elem = nullptr	// ��vec�ͷ�
		cout << "�ƶ�����" << endl;
	}
	T& operator[](int i) //�����±�Ϊi������
	{
		return elem[i];
	}

	int size() const { return sz; }

	~myvector() //�����������ͷ�elem
	{
		if(elem != nullptr)
			delete[] elem;
		//cout << "����" << this << endl;
	}
	T at(int n) const //��
	{
		if(n<sz)
			return elem[n];
		return elem[sz+1];//Խ�緵��nullptr;
	} 

	T back()
	{
		return elem[sz-1];
	}
	void set(T n, T v) //ָ��λ��д��
	{ 
		if (n <= sz)
		{
			elem[n] = v;
		}


	}  
	void push_back(T value) //β��д��
	{
		if (sz == 0)
		{
			elem = new T[sz + 5];//Ĭ������5���ռ�
			elem[sz] = value;
			startptr = &elem[0];
			//elem[sz +1] = '\s';	
			//for (int n = 0; n < sz+2; ++n)
			//{
			//	if (elem[n] == nullptr) //�ҵ�β�ͽڵ�
			//	{
					endptr = &elem[sz+1];
			//	}
			//}
					remain = 3;
			sz++;
			cout << "push_back success" << endl;
		}
		else
		{
			if (remain)
			{
				elem[sz] = value;
				sz++;
				remain--;
				startptr = &elem[0];
				endptr = &elem[sz + 1];
				//cout << "remain " << remain << endl;
				cout << "push_back success" << endl;
			}
			else 
			{ 
				//���û��ʣ��ռ� �����¿���+1�ռ�
				//save = new T[sz]; 
				save = elem;		//����֮ǰ������

				elem = new T[sz * 2];
				//elem = new T[sz +10];
				for (int n = 0; n < sz; ++n)//���ݿ���(������Ч��������)
				{
					elem[n] = save[n];
				}
				elem[sz] = value;
				startptr = &elem[0]; //ͷָ�����»�ȡ
				//for (int n = sz+1; n < sz+10; ++n)//��ʣ��ռ丳ֵnullptr
				//{
					//elem[sz+1] = '\s';
				//}
				//for (int n = sz; n < sz + 2; ++n) //�ҵ�һ�� sz+1 Ϊnullptr
				//{
					//if (elem[n] == nullptr) //�ҵ�β�ͽڵ�
					//{
						endptr = &elem[sz+1];
					//}
				//}
				sz++;
				delete save;
				save = nullptr;
				remain = sz-2;	//�ܵĴ�С ��ȥ ��ʹ�ô�С-1(nullptr)
				//cout << "sz = " << sz << endl;
				cout << "push_back success" << endl;
			}
		
		}
	
	}

	T* erase(T num)//ɾ��ָ��Ԫ��,����ָ����һ��Ԫ�ص�ָ��
	{
		if (startptr) //������ЧԪ��
		{
			if (num == *startptr) //ɾ����Ԫ��
			{
				for (int i = 0; i < sz; i++)
					elem[i] = elem[i + 1];	//��һ��Ԫ�� ��ǰһ��Ԫ�ظ���
				sz--;
				//endptr = &elem[sz];
				//cout << "earse " << num << "success" << endl;
				return &elem[0];
			}
			if (num == elem[sz])//ɾ��ĩβԪ�� ĩβ��sz+1 
			{
				elem[sz] = elem[sz + 1];
				sz--;
				//endptr = &elem[sz];
				//cout << "earse " << num << "success" << endl;
				return &elem[sz];
			}
			else//ɾ���м�Ԫ��
			{
				for (int i = 0; i < sz + 1; i++)
				{
					if (elem[i] == *endptr)
					{
						//cout << "δ�ҵ���Ԫ��" << endl;
						return 0;
					}
					else
					{
						if (num == elem[i])
						{
							for (int k = i; k < sz; k++)
							{
								elem[k] = elem[k + 1];
							}
							sz--;
							//endptr = &elem[sz];
							//cout << "earse " << num << "success" << endl;
							return &elem[i];
						}
					}
				}
			}
		}
		else
		{
			cout << "vector��û��Ԫ��" << endl;
		}
	}	

	T* end()
	{
		return &elem[sz];
	}
	T* begin()
	{
		return &elem[0];
	}

	bool empty()
	{
		if (!startptr)
			return true;
		return false;
	}

	void clear()	//ɾ����������Ԫ��
	{
		delete[]elem;
		elem = new T[sz];
		sz = 0;
	}
	T* reserve() //�������ݴ������ڴ��˷�����
	{
		elem = realloc(elem, sz + 1);
		return &elem[0];//�����¿ռ��׵�ַ
	}

	void acess() //����
	{


	}
	T front()
	{
		return elem[0];
	}

	void pop_back()
	{
		elem[sz - 1] = elem[sz];
		sz--;
	}

	int max_size()
	{
		return remain +sz;
	}

	int capacity()
	{
		return remain;
	}

	myvector&& move()
	{
		return myvector(1);
	}
private:
	int sz;		//vector���ô�С
	T* elem;	//�ɵ��ƶ�ָ��
	T* save;	//��ʱ������һ��������ָ��
	T* endptr;	//ͷ�ڵ�ָ��
	T* startptr;	//β�ͽڵ�ָ��
	int remain;		//ʣ��ռ�	
};



