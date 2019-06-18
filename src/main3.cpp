#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>

using namespace std;

mutex mutObj;

// ========== [Функция обслужить покупателей] ==========
void serveBuyers(queue<vector<int>> buyers_queue)
{
	lock_guard<mutex> lockGuard(mutObj);// блокируем выполнение других потоков

	cout << "\nThere are " << buyers_queue.size() << " buyers at the cashbox No." << this_thread::get_id() << endl;
	
	short int counter = 1; // Счетчик покупателей
	int cashBoxSum = 0;
	while (buyers_queue.empty() == false) // пока очередь из покупателей не пуста
	{
		cout << "\tServing a " << counter << " customer. He got " << buyers_queue.front().size() << " products ";

		int sum = 0;
		for (int i = 0; i < buyers_queue.front().size(); i++)
		{
			sum += buyers_queue.front()[i]; // сумма покупки покупателя
		}
		cout << "(total sum: " << sum << " rub)" << endl;
		for (int j = 0; j < buyers_queue.front().size(); j++) // пройдемся по всем покупателям в очереди
		{
			this_thread::sleep_for(chrono::milliseconds(10 + rand()% 100)); // имитация обслуживания (задержка)
		}
		cashBoxSum += sum;
		buyers_queue.pop(); // исключим покупателя из очереди (обслужили)
		counter++; // увеличим счетчик
	}
	cout << "=== [Total cashBox sum: " << cashBoxSum << " rub] ===" << endl;
}

int main()
{
	vector <int> products;	// вектор продуктов
	vector <thread*> threads;	// вектор потоков
	queue <vector<int>> buyers;	// вектор покупателей

	srand(time(0));
	int buyers_number = rand() % 25; // количество покупателей

	cout << "Buyers in market: " << buyers_number << endl;

	int products_number; // количество продуктов
	for (int i = 0; i < buyers_number; i++) // пройдемся по всем покупателям
	{
		products_number = 1 + rand() % 10; // сгенерируем количество продуктов для покупателя
		
		// сгенерируем цену для каждого продукта
		while (products_number--)
		{
			int price = 1 + rand() % 150;
			products.push_back(price); // поместим цену для соответствующего элемента в вектор продуктов
		}

		buyers.push(products); // сохраним наши продукты для покупателя
		products.clear(); // очистим "корзину продуктов"
		
		if ((i == buyers_number - 1) || (buyers.size() % 5 == 0)) // для каждого последнего или 5ого покупателя
		{
			threads.push_back(new thread(serveBuyers, buyers)); // запустим новый поток
			while (buyers.empty() == false) buyers.pop(); // очистим вектор покупателей (чтобы не "копились")
		}
	}
	for (auto & thread : threads) thread->join(); // дождемся завершения выполнения всех потоков

	return 0;
}