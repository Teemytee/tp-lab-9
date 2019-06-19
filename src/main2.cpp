#include <vector>
#include <iostream>
#include <thread>    
#include <cstdlib> 
#include <stdio.h>
#include <chrono>
#include <string>
#include <mutex>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;
int b = 0;
std::mutex g;
std::mutex mtx;
condition_variable d;

bool g_notified=false;
bool g_notified1=true;
#include <condition_variable>

void cou(string *a, int array_size) {
	
		
	while (b !=1) {
		unique_lock<mutex>lk(g);
		d.wait(lk, []() {return g_notified1; });
		for (int i = 0; i < array_size; i++)
		{
			cout << a[i] << ", ";

		}
		cout << endl;
		g_notified1 = false;
		g_notified = true;
		lk.unlock();
		d.notify_all();
	}
		 
		 
	
	}
	


void Sort(int array_size, string a[], bool comparison(string first, string second)) {

	string temp ;
	
	
	for (int i=0; i < array_size; ++i)
	{
		
		for (int int_counter = 0; int_counter < (array_size - i - 1); ++int_counter){
			if (comparison(a[int_counter], a[int_counter + 1]))
			{
				
				g.lock();
				temp = a[int_counter];
				a[int_counter] = a[int_counter + 1];
				a[int_counter + 1] = temp;

				g_notified = true;
				g.unlock();
				g_notified = false;
			};
			
			
			
			
		
			
			
		}
		
	
			
		}
	b = 1;
		
	}



int main()
{
	


	string a[] = {"Crab","throw","ladder","lie","Hornburg"};
	int array_size = sizeof(a) / sizeof(string);
	
	
	thread t(Sort,array_size, a, [](string a, string b) {return a.length() < b.length(); });
	
	while (b != 1) {
		if (g_notified == true) {
			mtx.lock();
			
			

			for (int i = 0; i < array_size; ++i) {
				std::cout << a[i] << std::endl;
			}

			g_notified = false;
			mtx.unlock();
		}
	}


	t.join();
	
	
//	getchar();


return 0;
}