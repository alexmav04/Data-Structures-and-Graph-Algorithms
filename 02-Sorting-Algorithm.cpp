/*
Implement the following sorting algorithms and compare their performances.
1. Insertion sort
2. Selection sort
3. Quick sort
4. Merge sort
5. Heap sort

date:2020-10-01
*/

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define Max 100000000

using namespace std;

void swap(int *a, int *b);
void insertion_sort(vector<int> &array, int size);
void selection_sort(vector<int> &array, int size);
int array_partition(vector<int> &array, int left, int right);
void quick_sort(vector<int> &array, int left, int right);
void Merge(vector<int> &array, int front, int mid, int end);
void merge_sort(vector<int> &array, int front, int end);
void MaxHeap(vector<int> &array, int root, int size);
void BuildMaxHeap(vector<int> &array);
void heap_sort(vector<int> &array);
void array_print(vector<int> &array, int size);
clock_t startTime;
clock_t endTime;
float costTime;

int main() {
  string strInput;
  int arrayNum;
  srand((unsigned)time(NULL));
  
  cout << "Enter a number / \"debug\" :" << endl;
  cin >> strInput;

  if (strInput == "debug") {
    arrayNum = 20;
  } else {
    arrayNum = atoi(strInput.c_str());
  }

  vector<int> array(arrayNum);

  // generate random numbers
  for (int i = 0; i < arrayNum; i++) {
    array[i] = rand();
  }

  // show the initial array in the debug mode
  if (strInput == "debug") {
    cout << "\n initial array:" << endl;
    array_print(array, arrayNum);
  }

  // Insertion sort
  cout << "\n--- Insertion sort ---" << endl;
  insertion_sort(array, arrayNum);
  if (strInput == "debug") {
    array_print(array, arrayNum);
  }

  // Selection sort
  cout << "\n--- Selecton sort ---" << endl;
  selection_sort(array, arrayNum);
  if (strInput == "debug") {
    array_print(array, arrayNum);
  }

  // Quick sort
  cout << "\n--- Quick sort ---" << endl;
  startTime = clock();
  quick_sort(array, 0, arrayNum - 1);
  endTime = clock();

  cout << "start :" << startTime << " ms" << endl;
  cout << "end :" << endTime << " ms" << endl;
  cout << "cpu time :" << (float)(endTime - startTime) / CLK_TCK << " s"
       << endl;
  if (strInput == "debug") {
    array_print(array, arrayNum);
  }

  // Merge sort
  cout << "\n--- Merge sort ---" << endl;
  startTime = clock();
  merge_sort(array, 0, arrayNum - 1);
  endTime = clock();

  cout << "start :" << startTime << " ms" << endl;
  cout << "end :" << endTime << " ms" << endl;
  cout << "cpu time :" << (float)(endTime - startTime) / CLK_TCK << " s"
       << endl;
  if (strInput == "debug") {
    array_print(array, arrayNum);
  }

  // Heap sort
  cout << "\n--- Heap sort: ---" << endl;
  heap_sort(array);
  if (strInput == "debug") {
    array_print(array, arrayNum);
  }

  system("pause");
  return 0;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// insertion sort
void insertion_sort(vector<int> &array, int size) {
  int i, j, current;
  startTime = clock();

  for (i = 1; i < size; i++) {
    current = array[i];
    j = i - 1;
    while ((j >= 0) && array[j] > current) {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = current;
  }
  endTime = clock();

  cout << "start :" << startTime << " ms" << endl;
  cout << "end :" << endTime << " ms" << endl;
  cout << "cpu time :" << (float)(endTime - startTime) / CLK_TCK << " s"
       << endl;
}

// selection sort
void selection_sort(vector<int> &array, int size) {
  int i, j, temp;
  startTime = clock();

  for (i = 0; i < size - 1; i++) {
    int min = i;

    // the smallest number in the unsorted array
    for (j = i + 1; j < size; j++) {
      if (array[j] < array[min]) {
        min = j;
      }
    }
    swap(&array[min], &array[i]);
  }
  endTime = clock();

  cout << "start :" << startTime << " ms" << endl;
  cout << "end :" << endTime << " ms" << endl;
  cout << "cpu time :" << (float)(endTime - startTime) / CLK_TCK << " s"
       << endl;
}

// quick sort
int array_partition(vector<int> &array, int left, int right) {
  int pivot = array[right];
  int i = left - 1;
  for (int j = left; j < right; j++) {
    if (array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  i++;
  swap(&array[i], &array[right]);
  return i;
}

void quick_sort(vector<int> &array, int left, int right) {
  if (left < right) {
    int pivot = array_partition(array, left, right);
    quick_sort(array, left, pivot - 1);
    quick_sort(array, pivot + 1, right);
  }
}

// merge sort
void Merge(vector<int> &array, int front, int mid, int end) {
  vector<int> LeftArr(array.begin() + front, array.begin() + mid + 1);
  vector<int> RightArr(array.begin() + mid + 1, array.begin() + end + 1);

  LeftArr.insert(LeftArr.end(), Max);
  RightArr.insert(RightArr.end(), Max);

  int idxLeft = 0, idxRight = 0;

  for (int i = front; i <= end; i++) {
    if (LeftArr[idxLeft] <= RightArr[idxRight]) {
      array[i] = LeftArr[idxLeft];
      idxLeft++;
    } else {
      array[i] = RightArr[idxRight];
      idxRight++;
    }
  }
}

void merge_sort(vector<int> &array, int front, int end) {
  if (front < end) {
    int mid = (front + end) / 2;
    merge_sort(array, front, mid);
    merge_sort(array, mid + 1, end);
    Merge(array, front, mid, end);
  }
}

// heap sort
void MaxHeap(vector<int> &array, int root, int size) {
  int left = 2 * root, right = 2 * root + 1, largest;

  if (left <= size && array[left] > array[root])
    largest = left;
  else
    largest = root;

  if (right <= size && array[right] > array[largest])
    largest = right;

  if (largest != root) {
    swap(array[largest], array[root]);
    MaxHeap(array, largest, size);
  }
}

void BuildMaxHeap(vector<int> &array) {
  for (int i = (int)array.size() / 2; i >= 1; i--) {
    MaxHeap(array, i, (int)array.size() - 1);
  }
}

void heap_sort(vector<int> &array) {
  startTime = clock();

  array.insert(array.begin(), 0);
  // keep the index 0 empty(delete it in the end)

  BuildMaxHeap(array);

  int size = (int)array.size() - 1; // the size of current array
  for (int i = (int)array.size() - 1; 2 <= i; i--) {
    swap(array[1], array[i]);
    size--;
    MaxHeap(array, 1, size); // sort the new array
  }
  array.erase(array.begin());
  endTime = clock();

  cout << "start :" << startTime << " ms" << endl;
  cout << "end :" << endTime << " ms" << endl;
  cout << "cpu time :" << (float)(endTime - startTime) / CLK_TCK << " s"
       << endl;
}

void array_print(vector<int> &array, int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}
