/*
Implement an efficient data structure for sparse matrices.

date:2020-10-26
*/
#include <iostream>

using namespace std;

int main() {
}

// Node of LinkedList
class LinkedList;
class llNode {
private:
  int value;
  llNode *next;

public:
  llNode() : value(0), next(0){};
  llNode(int a) : value(a), next(0){};

  friend class LinkedList;
};

// LinkedList
class LinkedList {
private:
  llNode *first;

public:
  LinkedList() : first(0){}; // the first node of linked list
  void pushHead(int x);      // push a node to the head of linked list
  void pushTail(int x);      // push a node to the tail of linked list
  void Delete(int x);        // delete a node from the linked list
  void Clear();              // clear all the element in the linked list
  // void Reverse();
  void PrintList();
};

void LinkedList::pushHead(int x) {
  llNode *newNode = new llNode(x);
  newNode->next = first;
  first = newNode;
}

void LinkedList::pushTail(int x) {
  llNode *newNode = new llNode(x);

  if (first == 0) {
    first = newNode;
    return;
  }

  llNode *current = first;
  while (current->next != 0) {
    current = current->next;
  }
  current->next = newNode;
}

void LinkedList::Delete(int x) {
  llNode *current = first;
  llNode *pre = 0;

  // do the loop to traversal the linked list
  while (current != 0 && current->value != x) {
    pre = current;
    current = current->next;
  }

  if (current == 0) { // if there is no node to be deleted
    cout << x << " is not in the list" << endl;
  } else if (current == first) { // if the delete one is the first node
    first = current->next;
    delete current;
    current = 0;
  } else {
    pre->next = current->next;
    delete current;
    current = 0;
  }
}

void LinkedList::Clear() {
  while (first != 0) {
    llNode *current = first;
    first = first->next;
    delete current;
    current = 0;
  }
}

void LinkedList::PrintList() {

  if (first == 0) { // 如果first node指向NULL, 表示list沒有資料
    cout << "List is empty.\n";
    return;
  }

  llNode *current = first; // 用pointer *current在list中移動
  while (current != 0) {     // Traversal
    cout << current->value << " ";
    current = current->next;
  }
  cout << endl;
}
