#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>


using namespace std;
/*             task #1           */
template<class T, class N>

void bubbleSort(T * pArray, size_t size, const N& comparator)
{
	for (auto i = 0; i < size; ++i)
		for (auto j = 0; j < size; ++j)
			if (!comparator(pArray[i], pArray[j]))
				swap(pArray[i], pArray[j]);
	return;
}
namespace myspace
{
	template<class A>
	auto lesser = [](A a, A b) { return a < b ? true : false; };

	template<class B>
	auto greater = [](B a, B b) { return a > b ? true : false; };

	template<class C, int bound>
	auto modSort = [](C a, C b) { return (a  % bound) > b ? true : false; };
}


int main()
{

	cout << endl << endl<< "********** task #1 ***********" << endl << endl;

	size_t size = 10;
	int  arr1[] = { 2,1,4,0,3,4,6,-2,-2,11 };
	float  arr2[] = { 2.1,1.19,4.0,0.123,3,4.005,6.7,-2.22,-2.22,11.5 };
	auto *pArr1 = arr1;
	auto *pArr2 = arr2;
	cout << "unsorted array1: " << endl;
	for (auto i = 0; i < size; ++i)
		cout << pArr1[i] << " ";
	cout << endl;
	cout << endl;
	cout << "unsorted array2: " << endl;
	for (auto i = 0; i < size; ++i)
		cout << pArr2[i] << " ";
	cout << endl;
	cout << endl;
	cout << endl;
	comparator 1
	cout << "comparator \"lesser\" for array1: " << endl<<endl;
	bubbleSort(pArr1, size, myspace::lesser<int>);
	for (auto i = 0; i < size; ++i)
		cout << pArr1[i] << " ";
	cout << endl;
	cout << endl;
	comparator 2
	cout << "comparator \"greater\" for array2: " << endl << endl;
	bubbleSort(pArr2, size, myspace::greater<float>);
	for (auto i = 0; i < size; ++i)
		cout << pArr2[i] << " ";
	cout << endl;
	cout << endl;
	comparator 3
	cout << "comparator with capture weght=2  for array1: " << endl << endl;
	int weight = 2;
	bubbleSort(pArr1, size, [weight](int a, int b) { return a*weight >= b ? true : false; });
	for (auto i = 0; i < size; ++i)
		cout << pArr1[i] << " ";
	cout << endl;
	cout << endl;
	comparator 4
	cout << "comparator with capture bound=3.14 for array2: " << endl << endl;
	float bound = 3.14;
	bubbleSort(pArr2, size, [bound](float a, float b) { return a < bound ? true : false; });
	for (auto i = 0; i < size; ++i)
		cout << pArr2[i] << " ";
	cout << endl;
	cout << endl;
	comparator 5
	cout << "comparator sort by modSort for array1: " << endl << endl;
	bubbleSort(pArr1, size, myspace::modSort<int,4>);
	for (auto i = 0; i < size; ++i)
		cout << pArr1[i] << " ";
	cout << endl;
	
	system("pause");
}