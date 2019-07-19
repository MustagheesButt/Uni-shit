#include <iostream>

#define SIZE 6

using namespace std;

void insertion_sort(int arr[], int size);
void merge_sort(int arr[], int low, int high);
void print_arr(int arr[], int size);

int main(void)
{
	int array_to_sort[SIZE] = { 3, 2, 7, 11, 4, 1 };

	print_arr(array_to_sort, SIZE);

	//insertion_sort(array_to_sort, SIZE);
	merge_sort(array_to_sort, 0, SIZE - 1);

	print_arr(array_to_sort, SIZE);

	return 0;
}

void insertion_sort(int arr[], int size)
{
	int comparisons = 0, swaps = 0;
	
	for (int i = 1; i < size; i++)
	{
		int j = i;
		while (j > 0 && arr[j] < arr[j - 1])
		{
			swap(arr[j], arr[j - 1]); swaps++;
			j--;
		}
		comparisons += 2;
		print_arr(arr, size);
	}

	cout << "Comparisons: " << comparisons << " Swaps: " << swaps << '\n';
}

void merge_sort(int arr[], int low, int high)
{
	if (low >= high)
		return;

	int mid = low + (high - low) / 2;

	merge_sort(arr, low, mid);
	merge_sort(arr, mid + 1, high);

	// merge from low to high
	int* new_arr = new int[high - low + 1];

	int i = low, j = mid + 1, k = 0;
	
	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
		{
			new_arr[k] = arr[i];
			i++;
		}
		else
		{
			new_arr[k] = arr[j];
			j++;
		}
		k++;
	}
	// copy remaining shit
	while (i <= mid)
		new_arr[k++] = arr[i++];

	while (j <= high)
		new_arr[k++] = arr[j++];
	
	// assign new_arr to arr
	k = 0;
	for (int i = low; i <= high; i++)
	{
		arr[i] = new_arr[k];
		k++;
	}
}

void print_arr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << ' ';
	cout << '\n';
}
