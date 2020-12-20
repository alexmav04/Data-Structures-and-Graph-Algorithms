#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define MAX_TREE_HT 100
string CODE = "";

struct MinHeapNode {
  char data;
  unsigned freq;
  struct MinHeapNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHeapNode **array;
};

struct MinHeapNode *newNode(char data, unsigned freq) {
  struct MinHeapNode *temp =
      (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;

  return temp;
}

struct MinHeap *createMinHeap(unsigned capacity) {
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity *
                                                 sizeof(struct MinHeapNode *));
  return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
  struct MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(struct MinHeap *minHeap) { return (minHeap->size == 1); }

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
  struct MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}
void printArr(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    cout << arr[i];
    CODE += to_string(arr[i]);
  }
  cout << "\n";
}
int isLeaf(struct MinHeapNode *root) { return !(root->left) && !(root->right); }

struct MinHeap *createAndBuildMinHeap(char data[], int freq[], int size) {
  struct MinHeap *minHeap = createMinHeap(size);
  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(data[i], freq[i]);
  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}
struct MinHeapNode *buildHuffmanTree(char data[], int freq[], int size) {
  struct MinHeapNode *left, *right, *top;
  struct MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);

  while (!isSizeOne(minHeap)) {
    left = extractMin(minHeap);
    right = extractMin(minHeap);
    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);
  }
  return extractMin(minHeap);
}

void printCodes(struct MinHeapNode *root, int arr[], int top) {
  if (root->left) {
    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }

  if (root->right) {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root)) {
    cout << root->data << ": ";
    printArr(arr, top);
  }
}
void HuffmanCodes(char data[], int freq[], int size) {
  struct MinHeapNode *root = buildHuffmanTree(data, freq, size);
  int arr[MAX_TREE_HT], top = 0;

  printCodes(root, arr, top);
}

bool checkExist(char data[], char ch) {
  for (int i = 0; i < 128; i++) {
    if (data[i] == ch)
      return 1;
  }
  return 0;
}

int main() {
  fstream file1;
  char ch, input[128] = {'\0'}, output[128] = {'\0'};
  int count[128] = {0}, inputI[128] = {0}, outputI[128] = {0};
  int total = 0, ascii;
  int set = 0;

  file1.open("07-testfile.txt", ios_base::in);

  // input the file words into array "input"
  while (file1.get(ch)) {
    ascii = (int)ch;
    if (!checkExist(input, ch)) {
      input[total] = ch;
    }
    count[ascii]++;
    total++;
  }
  // input the freqency of each word into "inputI"
  for (int j = 0; j < 128; j++) {
    inputI[j] = count[((int)input[j])];
  }

  for (int i = 0; i < 128; i++) {
    if (inputI[i] != 0) {
      output[set] = input[i];
      outputI[set] = inputI[i];
      set++;
    }
  }
  HuffmanCodes(output, outputI, set);
  cout << endl;
  cout << CODE << endl;
  cout << "compression ratio: " << (float)CODE.size() / ((float)total * 8) << endl;

  return 0;
}