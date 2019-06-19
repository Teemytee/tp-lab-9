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


void Sort(int array_size, string a[], bool comparison(string first, string second)) {

	string temp ;
	

	for (int i=1; i < array_size; ++i)
	{
		
		for (int int_counter = 0; int_counter < (array_size - i - 1); ++int_counter)
			if (comparison(a[int_counter], a[int_counter + 1]))
			{
				temp = a[int_counter];
				a[int_counter] = a[int_counter + 1];
				a[int_counter + 1] = temp;
				
			}


		
		
	}
	for (int i=0; i < array_size; i++)
	{
		cout << a[i] << ", ";
	}

}

int main()
{

	string a[] = {"Crab","throw","ladder","lie"};
	int array_size = sizeof(a) / sizeof(string);
Sort(array_size, a, [](string a, string b) {return a.length() < b.length(); });


return 0;
}