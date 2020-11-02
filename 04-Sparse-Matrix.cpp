/*
Implement an efficient data structure for sparse matrices.
date:2020-10-26
*/

#include <iostream>
#include <string>
using namespace std;

class llNode {
private:
  int value;
  int row_pos;
  int column_pos;
  llNode *next;

public:
  llNode() : next(NULL){};
  llNode(int a) : value(a), next(NULL){};

  friend class LinkedList;
};

class LinkedList {
private:
  llNode *first;

public:
  LinkedList() : first(NULL){};
  void PrintList();
  void addNode(int newrow_pos, int newcolumn_pos, int newvalue);
  void printMatrix(int m, int n);
  void matrixAdd(LinkedList A, LinkedList B);
};

int main() {
  int m, n, pos, value;

  cin >> m >> n;
  LinkedList list1;

  for (int i = 0; i < m; i++) {
    while (cin >> pos && pos != 0) {
      cin >> value;
      list1.addNode(i, pos, value);
    };
  }
  list1.PrintList();
  list1.printMatrix(m, n);

  return 0;
}

void LinkedList::addNode(int newrow_pos, int newcolumn_pos, int newvalue) {
  llNode *newNode = new llNode(newvalue);
  llNode *temp = new llNode();
  llNode *tempNew = new llNode();

  if (first == NULL) {
    temp->value = newvalue;
    temp->row_pos = newrow_pos;
    temp->column_pos = newcolumn_pos - 1;
    temp->next = NULL;

    first = temp;
  } else {
    temp = first;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    tempNew->value = newvalue;
    tempNew->row_pos = newrow_pos;
    tempNew->column_pos = newcolumn_pos - 1;
    tempNew->next = NULL;
    temp->next = tempNew;
  }
}

// for test
void LinkedList::PrintList() {
  if (first == NULL) {
    cout << "List is empty.\n";
    return;
  }

  llNode *current = first;
  while (current != NULL) {
    cout << current->value << " ";
    current = current->next;
  }
  cout << endl;
}

void LinkedList::printMatrix(int m, int n) {
  llNode *current = first;
  int **matrix;
  matrix = new int *[m];
  for (int i = 0; i < m; i++) {
    matrix[i] = new int[m];
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }
  while (current != NULL) {
    int row, col;
    row = current->row_pos;
    col = current->column_pos;

    matrix[row][col] = current->value;
    current = current->next;
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void LinkedList::matrixAdd(LinkedList A, LinkedList B) {}