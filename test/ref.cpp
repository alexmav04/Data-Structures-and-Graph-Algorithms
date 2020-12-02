#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>


using namespace std;

const int size1 = 10;
struct node {
  unsigned key;
  node *lchild;
  node *rchild;
};
deque<node *> forest;
deque<bool> code;
node *ptr;
int frequency[size1] = {0};

void printCode(deque<bool> ptr);

bool compare(node *a, node *b) { return a->key < b->key; }
int main(int argc, char *argv[]) {
  for (int i = 0; i < size1; i++) {
    cin >> frequency[i];
    ptr = new node;
    ptr->key = frequency[i];
    ptr->lchild = NULL;
    ptr->rchild = NULL;
    forest.push_back(ptr);
  } 

  for (int i = 0; i < size1 - 1; i++) {
    sort(forest.begin(), forest.end(), compare);
    ptr = new node;
  
    ptr->key = forest[0]->key + forest[1]->key;
    ptr->lchild = forest[0];
    ptr->rchild = forest[1];
    forest.pop_front();
    forest.pop_front();
    forest.push_back(ptr);
  }
  ptr = forest.front();
  system("PAUSE");
  return EXIT_SUCCESS;
}

void printCode(deque<bool> ptr) {
  // deque<bool>
  for (int i = 0; i < ptr.size(); i++) {
    if (ptr[i])
      cout << "1";
    else
      cout << "0";
  }
}