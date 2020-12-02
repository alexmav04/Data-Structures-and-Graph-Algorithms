#include <ctime>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

void MaxHeap(vector<int> &array, int root, int size);
void BuildMaxHeap(vector<int> &array);
void heap_sort(vector<int> &array);
void printArray(vector<int> &array, int size);

clock_t startTime;
clock_t endTime;
float costTime;

int main() {
  string strInput;
  int arrayNum;
  srand((unsigned)time(NULL));

  cout << "Enter a number:" << endl;
  cin >> strInput;

  arrayNum = atoi(strInput.c_str());

  vector<int> arrayOld(arrayNum), array1(arrayNum), array2(arrayNum);

  // generate random numbers
  for (int i = 0; i < arrayNum; i++) {
    arrayOld[i] = rand();
    array1[i] = arrayOld[i];
    array2[i] = arrayOld[i];
  }

  // Heap sort
  cout << "before heap sorting:\n";
  printArray(arrayOld, arrayNum);
  heap_sort(array1);
  cout << "after heap sorting:\n";
  printArray(array1, arrayNum);








}

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

void printArray(vector<int> &array, int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}



