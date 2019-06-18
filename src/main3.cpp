#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>

using namespace std;

mutex mutObj;

// ========== [������� ��������� �����������] ==========
void serveBuyers(queue<vector<int>> buyers_queue)
{
	lock_guard<mutex> lockGuard(mutObj);// ��������� ���������� ������ �������

	cout << "\nThere are " << buyers_queue.size() << " buyers at the cashbox No." << this_thread::get_id() << endl;
	
	short int counter = 1; // ������� �����������
	int cashBoxSum = 0;
	while (buyers_queue.empty() == false) // ���� ������� �� ����������� �� �����
	{
		cout << "\tServing a " << counter << " customer. He got " << buyers_queue.front().size() << " products ";

		int sum = 0;
		for (int i = 0; i < buyers_queue.front().size(); i++)
		{
			sum += buyers_queue.front()[i]; // ����� ������� ����������
		}
		cout << "(total sum: " << sum << " rub)" << endl;
		for (int j = 0; j < buyers_queue.front().size(); j++) // ��������� �� ���� ����������� � �������
		{
			this_thread::sleep_for(chrono::milliseconds(10 + rand()% 100)); // �������� ������������ (��������)
		}
		cashBoxSum += sum;
		buyers_queue.pop(); // �������� ���������� �� ������� (���������)
		counter++; // �������� �������
	}
	cout << "=== [Total cashBox sum: " << cashBoxSum << " rub] ===" << endl;
}

int main()
{
	vector <int> products;	// ������ ���������
	vector <thread*> threads;	// ������ �������
	queue <vector<int>> buyers;	// ������ �����������

	srand(time(0));
	int buyers_number = rand() % 25; // ���������� �����������

	cout << "Buyers in market: " << buyers_number << endl;

	int products_number; // ���������� ���������
	for (int i = 0; i < buyers_number; i++) // ��������� �� ���� �����������
	{
		products_number = 1 + rand() % 10; // ����������� ���������� ��������� ��� ����������
		
		// ����������� ���� ��� ������� ��������
		while (products_number--)
		{
			int price = 1 + rand() % 150;
			products.push_back(price); // �������� ���� ��� ���������������� �������� � ������ ���������
		}

		buyers.push(products); // �������� ���� �������� ��� ����������
		products.clear(); // ������� "������� ���������"
		
		if ((i == buyers_number - 1) || (buyers.size() % 5 == 0)) // ��� ������� ���������� ��� 5��� ����������
		{
			threads.push_back(new thread(serveBuyers, buyers)); // �������� ����� �����
			while (buyers.empty() == false) buyers.pop(); // ������� ������ ����������� (����� �� "��������")
		}
	}
	for (auto & thread : threads) thread->join(); // �������� ���������� ���������� ���� �������

	return 0;
}