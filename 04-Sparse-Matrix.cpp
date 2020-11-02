/*
Implement an efficient data structure for sparse matrices.

date:2020-10-26
*/

// C program for Sparse Matrix Representation
// using Linked Lists

#include <iostream>
using namespace std;
void newNode(struct llNode **start, int newrow_pos, int newcolumn_pos,
             int newvalue);
int *strSplit(string s, string sep);


struct llNode {
  int value;
  int row_pos;
  int column_pos;
  llNode *next;
};

class LinkedList {
private:
  llNode *first;

public:
  LinkedList() : first(0){}; 
  void PrintList();
};

int main() {
  int m, n;
  cin >> m >> n;

  int input_value, input_col;
  int *input;
  string inputStr;
  struct llNode *tmpNode = NULL;

  for (int i = 0; i < m; i++) { // m行內
    int j = 0;

    cin >> inputStr;
    input = strSplit(inputStr, " ");

    while (j < sizeof(input)) {
      if (input[j] != 0) {
        input_col = input[j + 1];
        newNode(&tmpNode, i, input_col, input_value);

        j = j + 2;
      } else {
        break;
      }
    }
  }
}

void newNode(struct llNode **start, int newrow_pos, int newcolumn_pos,
             int newvalue) {
  struct llNode *temp, *tempNew;
  temp = *start;
  if (temp == NULL) {
    temp = (struct llNode *)malloc(sizeof(struct llNode));

    temp->value = newvalue;
    temp->row_pos = newrow_pos;
    temp->column_pos = newcolumn_pos;
    temp->next = NULL;

    *start = temp;
  } else {
    while (temp->next != NULL)
      temp = temp->next;

    tempNew = (struct llNode *)malloc(sizeof(struct llNode));
    tempNew->value = newvalue;
    tempNew->row_pos = newrow_pos;
    tempNew->column_pos = newcolumn_pos;
    tempNew->next = NULL;
    temp->next = tempNew;
  }
}

void LinkedList::PrintList() {
  if (first == 0) {
    cout << "List is empty.\n";
    return;
  }

  llNode *current = first;
  while (current != 0) {
    cout << current->value << " ";
    current = current->next;
  }
  cout << endl;
}

int *strSplit(string s, string sep) {
  int *str_split;
  int pos_current = 0;
  int pos_next = 0;
  int i = 0;
  int inttmp;

  while (pos_next < s.length()) {
    pos_next = s.find_first_of(sep, pos_current);
    if (pos_next != pos_current) {
      string strtmp = s.substr(pos_current, pos_next - pos_current);
      if (!strtmp.empty()) {
        inttmp = atoi(strtmp.c_str());
        str_split[i] = inttmp;
        i++;
      }
    }
    pos_current = pos_next + 1;
  }
  return str_split;
}