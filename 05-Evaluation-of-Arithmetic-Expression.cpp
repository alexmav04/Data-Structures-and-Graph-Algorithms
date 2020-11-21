/*
Design and implement effcient data structure and algorithm for the evaluation of
arithmetic expressions and assignment operation, infix format.

date:2020-11-23
*/

#include <iostream>
using namespace std;

bool isOpertor(char ch);
int order(char ch);
void toPostfix(char infix[], char postfix[], char foo[], int posAnswer);
void getPostfix(char postfix[], char foo[], int answer[], int posAnswer);

class stackLL {
private:
  int topIndex;
  char *stack;

public:
  stackLL() : topIndex(-1) { stack = new char[1]; }
  bool isEmpty();     // verify if the stack is empty
  void push(char ch); // put the new element on the top of the stack
  void pop();         // delete the element on the top of the stack
  int top();          // return the element on the top of the stack
  int size();         // return the size of the stack
};

bool stackLL::isEmpty() {
  //
  return (topIndex == -1);
}

void stackLL::push(char ch) {
  //
  stack[++topIndex] = ch;
}

void stackLL::pop() {
  if (isEmpty()) {
    cout << "The stack is empty." << endl;
    return;
  }
  stack[topIndex] = 0;
  topIndex--;
}

int stackLL::top() {
  if (isEmpty()) {
    cout << "The stack is empty." << endl;
    return -1;
  }
  return stack[topIndex];
}

int stackLL::size() {
  //
  return topIndex + 1;
}

int main() {
  char infix[1000], postfix[1000];
  char foo[1000];
  int answer[1000], posAnswer;

  cout << "Enter something you want to calculat:" << endl;

  while (cin >> infix) {
    toPostfix(infix, postfix, foo, posAnswer);
    getPostfix(postfix, foo, answer, posAnswer);
  }

  return 0;
}
bool isOpertor(char ch) {
  // verify operator
  switch (ch) {
  case '+':
  case '-':
  case '*':
  case '/':
    return true;
  default:
    return false;
  }
}
int order(char ch) {
  // the order of the operator
  switch (ch) {
  case '(':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return -1;
  }
}

void toPostfix(char infix[], char postfix[], char foo[], int posAnswer) {
  stackLL s1;
  s1.push('#');
  int i = 0, j = 0;
  while (infix[i] != '\0') {
    if (infix[i] >= '0' && infix[i] <= '9') {
      postfix[j++] = infix[i];
    } else if (infix[i] == '(') {
      s1.push(infix[i]);
    } else if (infix[i] == ')') {
      // loop until find the left parentheses
      while (s1.top() != '(') {
        postfix[j++] = ' ';
        postfix[j++] = s1.top();
        s1.pop();
      }
      s1.pop();
    } else if (isOpertor(infix[i])) {
      postfix[j++] = ' ';
      if (s1.isEmpty()) {
        s1.push(infix[i]);
      } else {
        while (order(infix[i]) <= order(s1.top())) {
          postfix[j++] = s1.top();
          postfix[j++] = ' ';
          s1.pop();
        }
        s1.push(infix[i]);
      }
    } else if ((infix[i] >= 'a' && infix[i] <= 'z') ||
               (infix[i] >= 'A' && infix[i] <= 'Z')) {
      // store the variable
      foo[sizeof(*foo) + 1] = infix[i];
      posAnswer = sizeof(*foo) + 1;
      i++;
    }
    i++;
  }
  while (s1.size()) {
    postfix[j++] = ' ';
    postfix[j++] = s1.top();
    s1.pop();
  }
  postfix[j - 1] = '\0';
}

void getPostfix(char postfix[], char foo[], int answer[], int posAnswer) {
  stackLL s1;
  int i = 0, result = 0;
  int x1 = 0, x2 = 0;
  while (postfix[i] != '\0') {
    if (postfix[i] >= '0' && postfix[i] <= '9') {
      int x = 0;
      while (postfix[i] >= '0' && postfix[i] <= '9') {
        x = x * 10 + (postfix[i] - '0');
        i++;
      }
      s1.push(x);
    } else if (postfix[i] == ' ') {
      i++;
    } else if (postfix[i] == '+') {
      x1 = s1.top();
      s1.pop();
      x2 = s1.top();
      s1.pop();
      int temp = x2 + x1;
      s1.push(temp);
      i++;
    } else if (postfix[i] == '-') {
      x1 = s1.top();
      s1.pop();
      x2 = s1.top();
      s1.pop();
      int temp = x2 - x1;
      s1.push(temp);
      i++;
    } else if (postfix[i] == '*') {
      x1 = s1.top();
      s1.pop();
      x2 = s1.top();
      s1.pop();
      int temp = x2 * x1;
      s1.push(temp);
      i++;
    } else if (postfix[i] == '/') {
      x1 = s1.top();
      s1.pop();
      x2 = s1.top();
      s1.pop();
      int temp = x2 / x1;
      s1.push(temp);
      i++;
    } else {
      int k = 0;
      while (foo[k] != '\0') {
        if (postfix[i] == foo[k]){
          postfix[i] = answer[k];
        }
        k++;
      }
    }
  }
  result = s1.top();
  if (foo[0] != '\0') {
    cout << foo[0] << " = " << result << endl;
  } else {
    cout << result << endl;
  }
}
