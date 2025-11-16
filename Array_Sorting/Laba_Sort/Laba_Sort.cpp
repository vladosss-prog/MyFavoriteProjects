#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <chrono>
using namespace std;

void PrintArr(vector<int> arr) { 
	for (int x = 0; x < arr.size(); x++) cout << arr[x] << " ";
	cout << "\n\n\n\n\n\n";
}
	
void BubbleSort(vector<int>& arr, int& comparisons, int& swaps) {
	comparisons = 0;
	swaps = 0;
	for (int i = 0; i < arr.size() - 1; i++) {
		for (int j = 0; j < arr.size() - i - 1; j++) {
			comparisons++;
			if (arr[j] > arr[j + 1]) {
				swaps++;
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}

}
void selectionSort(vector<int>& arr, int& comparisons, int& swaps) { //Сортировка выбором(выбираем минимальный элемент в массиве и ставим его в начало, после оставляем первый элемент в покое и проделываем данное действие для всех оставшихся элементов меняя их местами
	comparisons = 0;
	swaps = 0;
	for (int i = 0; i < arr.size() - 1; i++) {
		int min_index = i;
		for (int j = i + 1; j < arr.size(); j++) {
			comparisons++;
			if(arr[min_index] > arr[j]) min_index = j;
		}
		if (min_index != i) {
			int temp = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = temp;
			swaps++;
		}
	}

}
void insertionSort(vector<int>& arr, int& comparisons, int& swaps) { //Сортировка вставками(сравниваем элементы подмассива с помощью while при каждой итерации for делая подмассив больше
	comparisons = 0;
	swaps = 0;
	for (int i = 1; i < arr.size(); i++) {
		int sorted = i - 1;
		while (sorted > -1 && arr[sorted] > arr[sorted + 1]) {
			comparisons++;
			if (arr[sorted] > arr[sorted + 1]) {
				swaps++;
				int temp = arr[sorted];
				arr[sorted] = arr[sorted + 1];
				arr[sorted + 1] = temp;
				sorted--;
			}
		}
	}

}
int partOfSortHoara(vector<int>& arr, int left, int right, int& comparisons, int& swaps) {
	int pivot = arr[(left + right) / 2]; // Опорный элемент
	while (left <= right) {
		while (true) {
			comparisons++;
			if (!(arr[left] < pivot)) break;
			left++;
		}
		while (true) {
			comparisons++;
			if (!(arr[right] > pivot)) break;
			right--;
		}
		if (left <= right) {
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			left++; right--;
			swaps++;
		}
	}
	return left;
}
void quickSortHoara(vector<int>& arr, int start, int end, int& comparisons, int& swaps) {
	if (start >= end) return;
	int rightStart = partOfSortHoara(arr, start, end, comparisons, swaps);
	quickSortHoara(arr, start, rightStart - 1, comparisons, swaps);
	quickSortHoara(arr, rightStart, end, comparisons, swaps);
};
void quickSortHoara(vector<int>& arr,int &comparisons, int &swaps) {
	comparisons = 0;
	swaps = 0;
	quickSortHoara(arr, 0, arr.size() - 1, comparisons, swaps);
}

int partOfSortLomuto(vector<int>& arr, int start, int end, int& comparisons, int& swaps) {
	int left = start;
	for (int current = start; current < end; current++) {
		comparisons++;
		if (arr[current] <= arr[end]) {
			int temp = arr[left];
			arr[left] = arr[current];
			arr[current] = temp;
			swaps++;
			left++;
		}
	}
	int temp = arr[left];
	arr[left] = arr[end];
	arr[end] = temp;
	swaps++;
	return left;
}
void quickSortLomuto(vector<int>& arr, int start, int end, int& comparisons, int& swaps) {
	if (start >= end) return;

	int rightStart = partOfSortLomuto(arr, start, end, comparisons, swaps);
	quickSortLomuto(arr, start, rightStart - 1, comparisons, swaps);
	quickSortLomuto(arr, rightStart + 1, end, comparisons, swaps);
};
void quickSortLomuto(vector<int>& arr, int& comparisons, int& swaps) {
	comparisons = 0;
	swaps = 0;
	quickSortLomuto(arr, 0, arr.size() - 1, comparisons, swaps);
}

int main()
{
	setlocale(LC_ALL, "rus");
	double p = 0.3;
	// Массив
	int n = 10000;
	vector<int> arr(n);

	random_device rd; // Источник случайности rd
	mt19937 gen(rd()); //Мощный генератор случайных чисел 
	geometric_distribution<> geom(p); // Создание объекта геометрического распределения

	for (int i = 0; i < n; i++) 
		arr[i] = geom(gen);


	int C = 0, M = 0;
	double timeBubble, timeSelection, timeInsertion, timeHoara, timeLomuto;

	// Bubble Sort
	vector<int> arrBubble = arr;
	auto start = chrono::high_resolution_clock::now();
	BubbleSort(arrBubble, C, M);
	auto end = chrono::high_resolution_clock::now();
	int cBubble = C, mBubble = M;
	timeBubble = chrono::duration<double, milli>(end - start).count();

	// Selection Sort
	vector<int> arrSelection = arr;
	start = chrono::high_resolution_clock::now();
	selectionSort(arrSelection, C, M);
	end = chrono::high_resolution_clock::now();
	int cSelection = C, mSelection = M;
	timeSelection = chrono::duration<double, milli>(end - start).count();

	// Insertion Sort
	vector<int> arrInsertion = arr;
	start = chrono::high_resolution_clock::now();
	insertionSort(arrInsertion, C, M);
	end = chrono::high_resolution_clock::now();
	int cInsertion = C, mInsertion = M;
	timeInsertion = chrono::duration<double, milli>(end - start).count();

	// QuickSort Hoara
	vector<int> arrHoara = arr;
	start = chrono::high_resolution_clock::now();
	quickSortHoara(arrHoara, C, M);
	end = chrono::high_resolution_clock::now();
	int cHoara = C, mHoara = M;
	timeHoara = chrono::duration<double, milli>(end - start).count();

	// QuickSort Lomuto
	vector<int> arrLomuto = arr;
	start = chrono::high_resolution_clock::now();
	quickSortLomuto(arrLomuto, C, M);
	end = chrono::high_resolution_clock::now();
	int cLomuto = C, mLomuto = M;
	timeLomuto = chrono::duration<double, milli>(end - start).count();

	// Удобный заголовок
	cout << left
		<< setw(18) << "Метод"
		<< setw(10) << "C/N"
		<< setw(10) << "M/N"
		<< setw(13) << "Сравнения"
		<< setw(15) << "Перестановки"
		<< setw(12) << "Время, мс"
		<< setw(14) << "Сложность" << endl;
	cout << string(88, '-') << endl;

	// Вывод строк
	cout << setw(18) << "BubbleSort"
		<< setw(10) << fixed << setprecision(2) << double(cBubble) / n
		<< setw(10) << fixed << setprecision(2) << double(mBubble) / n
		<< setw(13) << cBubble
		<< setw(15) << mBubble
		<< setw(12) << fixed << setprecision(2) << timeBubble
		<< setw(14) << "O(n^2)" << endl;

	cout << setw(18) << "SelectionSort"
		<< setw(10) << double(cSelection) / n
		<< setw(10) << double(mSelection) / n
		<< setw(13) << cSelection
		<< setw(15) << mSelection
		<< setw(12) << fixed << setprecision(2) << timeSelection
		<< setw(14) << "O(n^2)" << endl;

	cout << setw(18) << "InsertionSort"
		<< setw(10) << double(cInsertion) / n
		<< setw(10) << double(mInsertion) / n
		<< setw(13) << cInsertion
		<< setw(15) << mInsertion
		<< setw(12) << fixed << setprecision(2) << timeInsertion
		<< setw(14) << "O(n^2)" << endl;

	cout << setw(18) << "QuickSort Hoara"
		<< setw(10) << double(cHoara) / n
		<< setw(10) << double(mHoara) / n
		<< setw(13) << cHoara
		<< setw(15) << mHoara
		<< setw(12) << fixed << setprecision(2) << timeHoara
		<< setw(14) << "O(n*log n)" << endl;

	cout << setw(18) << "QuickSort Lomuto"
		<< setw(10) << double(cLomuto) / n
		<< setw(10) << double(mLomuto) / n
		<< setw(13) << cLomuto
		<< setw(15) << mLomuto
		<< setw(12) << fixed << setprecision(2) << timeLomuto
		<< setw(14) << "O(n*log n)" << endl;

	cout << endl;
	return 0;
}



