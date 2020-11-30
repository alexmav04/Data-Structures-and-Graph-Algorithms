/*
Design and implement efficient data structure and algorithm for finding shortest
path from the start cell s to the destination cell t in a maze of dimension m x
n.

date:2020-10-26
*/
#include <iostream>
using namespace std;

class llNode {
private:
  char value;
  int row_pos;
  int column_pos;
  llNode *next;

public:
  llNode() : next(NULL){};
  llNode(char a) : value(a), next(NULL){};

  friend class LinkedList;
};

class LinkedList {
private:
  llNode *first;

public:
  LinkedList() : first(NULL){};
  void PrintList();
  void addNode(int newrow_pos, int newcolumn_pos, char newvalue);
  void printMatrix(int m, int n);
  int search(LinkedList A, int row_index, int column_index);
};

int main() {
  int m, n, pos;
  char value;
  LinkedList list1, list2, list3;

  cout << "Enter the number of row and column:" << endl;
  cin >> m >> n;

  cout << "Enter the element of matrix A:" << endl;
  for (int i = 0; i < m; i++) {
    while (cin >> pos && pos != 0 && pos <= n) {
      cin >> value;
      pos = pos - 1;
      list1.addNode(i, pos, value);
    }
    if (pos > n) {
      cout << "It's not a valid value." << endl;
      break;
    }
  }
}

void LinkedList::addNode(int newrow_pos, int newcolumn_pos, char newvalue) {
  llNode *newNode = new llNode(newvalue);
  llNode *temp = new llNode();
  llNode *tempNew = new llNode();

  if (first == NULL) {
    temp->value = newvalue;
    temp->row_pos = newrow_pos;
    temp->column_pos = newcolumn_pos;
    temp->next = NULL;

    first = temp;
  } else {
    temp = first;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    tempNew->value = newvalue;
    tempNew->row_pos = newrow_pos;
    tempNew->column_pos = newcolumn_pos;
    tempNew->next = NULL;
    temp->next = tempNew;
  }
}