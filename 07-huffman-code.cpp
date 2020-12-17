#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Node {
  char data;
  int count;
  struct Node *left, *right;
};

struct MinHeap {
  int size;
  int capacity;
  struct Node** array;
};

struct Node* newNode(char data, int count){
  struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
  node1->left = node1->right = NULL;
  node1->data = data;
  node1->count = count;
  return node1;
};

struct MinHeap* createMinHeap(int capacity){
  struct MinHeap* minHeap1 = (struct MinHeap*)malloc(sizeof(struct MinHeap));
  minHeap1->size = 0;
  minHeap1->capacity = capacity;
  minHeap1->array = (struct Node**)malloc(minHeap1->capacity * sizeof(struct Node*));
  return minHeap1;
};

void swapNode(struct Node** a, struct Node** b){
  struct Node* temp = *a;
  *a = *b;
  *b = temp;
}

void minHeapify(struct MinHeap* a, int index){
  int minimum = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  if(left < a->size && a->array[left]->count < a->array[minimum]->count){
    minimum = left;
  }
  if(right < a->size && a->array[right]->count < a->array[minimum]->count){
    minimum = right;
  }
  if (minimum != index){
    swapNode(&a->array[minimum], &a->array[index]);
    minHeapify(a, minimum);
  }
}

void buildMinHeap(struct MinHeap* a){
  int i;
  int n = a->size - 1;
  for(i = (n-1)/2; i >= 0; i--){
    minHeapify(a, i);
  }
}

void insertMinHeap(struct MinHeap* a, struct Node* node){
  ++a->size;
  int i = a->size - 1;
  while(i && node->count < a->array[(i - 1) / 2]->count){
    a->array[i] = a-> array[(i - 1)];
    i = (i - 1)/2;
  }
  a->array[i] = node;
}

struct MinHeap* MinHeapOutcome(char data[], int count[], int size){
  struct MinHeap* outcome = createMinHeap(size);
  for (int i = 0; i < size; i++){
    outcome->array[i] = newNode(data[i], count[i]);
  }
  outcome->size = size;
  buildMinHeap(outcome);
  return outcome;
}

struct Node* extractMin(struct MinHeap* a){
  struct Node* tmp = a->array[0];
  a->array[0] = a->array[a->size - 1];

  --a->size;
  minHeapify(a, 0);

  return tmp;
}

//Huffman tree
struct Node* buildHuffmanTree(char data[], int count[], int size){
  struct Node *left, *right, *top;
  struct MinHeap* MinHeap = MinHeapOutcome(data, count, size);

  while(MinHeap->size != 1){
    left = extractMin(MinHeap);
    right = extractMin(MinHeap);

    top = newNode('#', left->count + right->count);

    top->left = left;
    top->right = right;

    insertMinHeap(MinHeap, top);

  }
  return extractMin(MinHeap);
}

void print(struct Node* rt, int arr[], int top){
  if (rt->left){
    arr[top] = 0;
    print(rt->left, arr, top + 1);
  }
  if (rt->right){
    arr[top] = 1;
    print(rt->right, arr, top + 1);
  }

  //if rt is leaf
  if (!(rt->left) && !(rt->right)){
    cout << rt->data << ": ";

    //print array
    for (int i = 0; i < top; i++){
      cout << arr[i];
    }
    cout << endl;
  }
}

void HuffmanCode(char data[], int count[], int size){
  struct Node* rt = buildHuffmanTree(data, count, size);
  int arr[128] = {0}, top = 0;

  print(rt, arr, top);
}

int main(){
  fstream file1;
  char ch, input[128] = {'\0'};
  int count[128] = {0}, inputI[128] = {0};
  int total = 0, ascii;

  file1.open("07-testfile.txt" , ios_base::in);

  // while(file1.get(ch)){
  //   int ascii;
  //   input[total] = ch;
  //   count[total]++;
  //   total++;
  // }

  while(file1.get(ch)){
    ascii = (int)ch;
    if (input[total] == '\0'){
      input[total] = ch;
    }
    count[ascii]++;
    total++;
  }
  for (int j = 0; j < 128; j++) {
    inputI[j] = count[((int)input[j])];
  }


  // while(file1.get(ch)){
  //   int ascii;
  //   cout << ch;

  //   ascii = (int)ch;
  //   input[ascii] = ch;
  //   count[ascii]++;
  //   total++;
  // }

  //HuffmanCode(input, count, total);


    for (int i = 0; i < total; i++){
      cout << input[i];
    }
    // for (int i = 0; i < 128; i++){
    //   cout << inputI[i];
    // }
    cout << endl;



  // //check the number of the alphabet
  // for(int j = 0; j < 127; j++){
  //   if (count[j] != 0){
  //     cout << (char)j << ": " << count[j] << endl;
  //   }
  // }
  // cout << total << endl;
  file1.close();
}
