//#include <iostream>
//
//using namespace std;
//
//class Queue
//{
//private:
//	int* arr;
//	int MAX_SIZE;
//	int front, rear;
//
//public:
//	Queue(int MAX_SIZE)
//	{
//		this->MAX_SIZE = MAX_SIZE;
//		this->arr = new int[MAX_SIZE];
//		this->front = this->rear = -1;
//	}
//	~Queue()
//	{
//		delete[] this->arr;
//	}
//
//	bool isEmpty()
//	{
//		return this->front == -1;
//	}
//
//	bool isFull()
//	{
//		return (this->front == 0 && this->rear == this->MAX_SIZE - 1) || (this->front == this->rear + 1);
//	}
//
//	void enqueue(int item)
//	{	
//		if (this->isFull())
//		{
//			cout << "Queue is full!\n";
//			return;
//		}
//
//		if (this->isEmpty())
//			this->front = this->rear = 0;
//		else
//			this->rear = (this->rear + 1) % this->MAX_SIZE;
//		
//		this->arr[this->rear] = item;
//	}
//
//	int dequeue()
//	{
//		if (this->isEmpty())
//		{
//			cout << "Queue is empty!\n";
//			return -1;
//		}
//
//		int temp = this->arr[this->front];
//
//		if (this->front == this->rear)
//			this->front = this->rear = -1;
//		else
//			this->front++;
//
//		return temp;
//	}
//
//	void print()
//	{
//		if (this->isEmpty())
//		{
//			cout << "Queue is empty!\n";
//			return;
//		}
//
//		for (int i = this->front; i <= this->rear; i = (i + 1))
//			cout << this->arr[i] << ' ';
//		cout << '\n';
//	}
//};
//
//int main(void)
//{
//	Queue q(5);
//
//	for (int i = 0; i < 5; i++)
//		q.enqueue(i + 1);
//
//	q.print();
//
//	for (int i = 0; i < 5; i++)
//	{
//		cout << q.dequeue() << '\n';
//		q.print();
//	}
//
//	return 0;
//}