#pragma once


//此类仅为学习造轮子，目前只支持POD类型
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
		cout << "无参构造" << endl;
	}
	myvector(T s) :sz(s), elem(new T[s]),save(nullptr)//构造函数，分配s个double元素，将s保存到size中并让elem指向首元素地址
	{
		startptr = elem[0];
		endptr = elem[s]
		remain = 0;
		cout << "有参构造" << endl;
	}

	myvector(const myvector& vec) :elem(new T[vec.sz]), sz(vec.sz) //拷贝构造函数 包含指针进行深拷贝 效率低下
	{
		cout << "拷贝构造" << endl;
		for (int i = 0; i < vec.sz; i++)
		{
			elem[i] = vec.elem[i];
		}
	}
	myvector(myvector&& vec) noexcept //移动构造，针对vec此后不需要的情况
	{
		this->elem = vec.elem;
		this->sz = vec.sz;
		delete vec.elem;
		vec.elem = nullptr	// 将vec释放
		cout << "移动构造" << endl;
	}
	T& operator[](int i) //返回下标为i的引用
	{
		return elem[i];
	}

	int size() const { return sz; }

	~myvector() //析构函数，释放elem
	{
		if(elem != nullptr)
			delete[] elem;
		//cout << "析构" << this << endl;
	}
	T at(int n) const //读
	{
		if(n<sz)
			return elem[n];
		return elem[sz+1];//越界返回nullptr;
	} 

	T back()
	{
		return elem[sz-1];
	}
	void set(T n, T v) //指定位置写入
	{ 
		if (n <= sz)
		{
			elem[n] = v;
		}


	}  
	void push_back(T value) //尾部写入
	{
		if (sz == 0)
		{
			elem = new T[sz + 5];//默认申请5个空间
			elem[sz] = value;
			startptr = &elem[0];
			//elem[sz +1] = '\s';	
			//for (int n = 0; n < sz+2; ++n)
			//{
			//	if (elem[n] == nullptr) //找到尾巴节点
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
				//如果没有剩余空间 则重新开辟+1空间
				//save = new T[sz]; 
				save = elem;		//保存之前的数据

				elem = new T[sz * 2];
				//elem = new T[sz +10];
				for (int n = 0; n < sz; ++n)//数据拷贝(拷贝有效数据区域)
				{
					elem[n] = save[n];
				}
				elem[sz] = value;
				startptr = &elem[0]; //头指针重新获取
				//for (int n = sz+1; n < sz+10; ++n)//将剩余空间赋值nullptr
				//{
					//elem[sz+1] = '\s';
				//}
				//for (int n = sz; n < sz + 2; ++n) //找到一个 sz+1 为nullptr
				//{
					//if (elem[n] == nullptr) //找到尾巴节点
					//{
						endptr = &elem[sz+1];
					//}
				//}
				sz++;
				delete save;
				save = nullptr;
				remain = sz-2;	//总的大小 减去 已使用大小-1(nullptr)
				//cout << "sz = " << sz << endl;
				cout << "push_back success" << endl;
			}
		
		}
	
	}

	T* erase(T num)//删除指定元素,返回指向下一个元素的指针
	{
		if (startptr) //存在有效元素
		{
			if (num == *startptr) //删除首元素
			{
				for (int i = 0; i < sz; i++)
					elem[i] = elem[i + 1];	//后一个元素 把前一个元素覆盖
				sz--;
				//endptr = &elem[sz];
				//cout << "earse " << num << "success" << endl;
				return &elem[0];
			}
			if (num == elem[sz])//删除末尾元素 末尾非sz+1 
			{
				elem[sz] = elem[sz + 1];
				sz--;
				//endptr = &elem[sz];
				//cout << "earse " << num << "success" << endl;
				return &elem[sz];
			}
			else//删除中间元素
			{
				for (int i = 0; i < sz + 1; i++)
				{
					if (elem[i] == *endptr)
					{
						//cout << "未找到该元素" << endl;
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
			cout << "vector还没有元素" << endl;
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

	void clear()	//删除容器所有元素
	{
		delete[]elem;
		elem = new T[sz];
		sz = 0;
	}
	T* reserve() //处理扩容带来的内存浪费问题
	{
		elem = realloc(elem, sz + 1);
		return &elem[0];//返回新空间首地址
	}

	void acess() //访问
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
	int sz;		//vector已用大小
	T* elem;	//可的移动指针
	T* save;	//临时保存上一次数据区指针
	T* endptr;	//头节点指针
	T* startptr;	//尾巴节点指针
	int remain;		//剩余空间	
};



