/*
Segment tree
date:2020-12-02
*/

#include <iostream>
#include <vector>

using namespace std;

class trNode {
private:
  int value;
  trNode *leftChild, *rightChild;

public:
  trNode() : leftChild(NULL), rightChild(NULL), value(0){};
  friend class Tree;
};

class Tree {
private:
  trNode *root;

public:
  Tree() : root(NULL){};
  void MaxHeapify();
  void PrintList();
};

void swap(int &value1, int &value2) {
  int temp;
  value1 = value2;
  value2 = temp;
}

void MaxHeapify(vector<int> &array, int root, int size) {
  int left, right, largest; // record the position
  left = 2 * root;
  right = 2 * root + 1;

  if (left <= size && array[left] > array[root]) {
    largest = left;
  } else {
    largest = root;
  }
  if (right <= size && array[right] > array[root]) {
    largest = right;
  } else {
    largest = root;
  }

  if (largest != root) {
    swap(array[largest], array[root]);
    MaxHeapify(array, largest, size);
  }
}

void BuildMaxHeap(vector<int> &array) {
  for (int i = (int)array.size() / 2; i >= 1; i--) {
    MaxHeapify(array, i, (int)array.size() - 1);
  }
}

void HeapSort(vector<int> &array) {
  array.insert(array.begin(), 0);

  BuildMaxHeap(array);

  int size = (int)array.size() - 1;
  for (int i = (int)array.size() - 1; i >= 2; i--) {
    swap(array[1], array[i]);
    size--;
    MaxHeapify(array, 1, size);
  }
  array.erase(array.begin());
}
void printArray(vector<int> &array) {
  for (int i = 0; i < array.size(); i++) {
    cout << array[i] << " ";
  }
}

int main() {
  int arr[5] = {6, 7, 3, 1, 2};
  vector<int> array(arr, arr + sizeof(arr) / sizeof(int));

  HeapSort(array);
  cout << "sorted:\n";
  printArray(array);
}
