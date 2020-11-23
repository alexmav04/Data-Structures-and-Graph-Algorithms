#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isOperator(char ch);
int order(char ch);
void toPostfix(char input[], char postfix[], char variable[],
               double variable_value[], int pos, int check);
double getValue(char postfix[]);
string ConvertToString(double db);

int main() {
  char input[500] = {'\0'}, postfix[500] = {'\0'}, variable[500] = {'\0'};
  double variable_value[500] = {0};
  int pos = 0;

  while (cin >> input) {
    toPostfix(input, postfix, variable, variable_value, pos, 0);
    double result = getValue(postfix);
    cout << result << endl;
    pos++;
  }

  return 0;
}
class stackLL {
private:
  int topIndex;
  double *stack;

public:
  stackLL() : topIndex(-1) { stack = new double[1]; }
  bool isEmpty();       // verify if the stack is empty
  void push(double db); // put the new element on the top of the stack
  void pop();           // delete the element on the top of the stack
  double top();         // return the element on the top of the stack
  int size();           // return the size of the stack
};

bool stackLL::isEmpty() {
  //
  return (topIndex == -1);
}

void stackLL::push(double db) {
  //
  stack[++topIndex] = db;
}

void stackLL::pop() {
  if (isEmpty()) {
    cout << "The stack is empty." << endl;
    return;
  }
  stack[topIndex] = 0;
  topIndex--;
}

double stackLL::top() {
  if (isEmpty()) {
    return -1;
  }
  return stack[topIndex];
}

int stackLL::size() {
  //
  return topIndex + 1;
}

bool isOperator(char ch) {
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
void toPostfix(char input[], char postfix[], char variable[],
               double variable_value[], int pos, int check) {
  stackLL stk1;
  stk1.push('#');
  int i = 0, j = 0;
  while (input[i] != '\0') {
    if ((input[i] >= 'a' && input[i] <= 'z') ||
        (input[i] >= 'A' && input[i] <= 'Z')) {
      if (input[i + 1] == '=' && check == 0) {
        variable[pos] = input[i];
        toPostfix(input, postfix, variable, variable_value, pos, 1);
        variable_value[pos] = getValue(postfix);
        pos++;
      } else {
        int k = 0;
        while (variable[k] != '\0') {
          if (input[i] == variable[k]) {
            const char *tmp;
            double tmpdb = variable_value[k];
            tmp = ConvertToString(tmpdb).c_str();
            // toPostfix(input, postfix, variable, variable_value, pos, 1);
            int m = 0;
            while (tmp[m] != '\0') {
              postfix[j++] = tmp[m];
              m++;
            }
            break;
          }
          k++;
        }
      }
    }
    if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
      postfix[j++] = input[i];
    } else if (input[i] == '(') {
      stk1.push(input[i]);
    } else if (input[i] == ')') {
      while (stk1.top() != '(') {
        postfix[j++] = ' ';
        postfix[j++] = stk1.top();
        stk1.pop();
      }
      stk1.pop();
    } else if (isOperator(input[i])) {
      postfix[j++] = ' ';
      if (stk1.isEmpty()) {
        stk1.push(input[i]);
      } else {
        while (order(input[i]) <= order(stk1.top())) {
          postfix[j++] = stk1.top();
          postfix[j++] = ' ';
          stk1.pop();
        }
        stk1.push(input[i]);
      }
    }
    i++;
  }
  while (stk1.size()) {
    postfix[j++] = ' ';
    postfix[j++] = stk1.top();
    stk1.pop();
  }
  postfix[j - 1] = '\0';
}

double getValue(char postfix[]) {
  stackLL stk1;
  int i = 0;
  double result = 0;
  double x1 = 0, x2 = 0;
  while (postfix[i] != '\0') {
    if (postfix[i] >= '0' && postfix[i] <= '9') {
      double x = 0;
      int n = 0;
      while (postfix[i] >= '0' && postfix[i] <= '9') {
        x = x * 10 + (postfix[i] - '0');
        i++;
      }
      if (postfix[i] == '.') {
        i++;
        while (postfix[i] >= '0' && postfix[i] <= '9') {
          x = x * 10 + (postfix[i] - '0');
          i++;
          n++;
        }
      }
      while (n) {
        x /= 10;
        n--;
      }
      stk1.push(x);
    } else if (postfix[i] == ' ') {
      i++;
    } else if (postfix[i] == '+') {
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 + x1;
      stk1.push(temp);
      i++;
    } else if (postfix[i] == '-') {
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 - x1;
      stk1.push(temp);
      i++;
    } else if (postfix[i] == '*') {
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 * x1;
      stk1.push(temp);
      i++;
    } else if (postfix[i] == '/') {
      x1 = stk1.top();
      stk1.pop();
      x2 = stk1.top();
      stk1.pop();
      double temp = x2 / x1;
      stk1.push(temp);
      i++;
    }
  }
  result = stk1.top();
  return result;
}

string ConvertToString(double db) {
  std::stringstream ss;
  ss << db;
  return ss.str();
}