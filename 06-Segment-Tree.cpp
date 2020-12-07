/*
Design and implement effcient data structure and algorithm for the evaluation of
arithmetic expressions and assignment operation, infix format.
*/
#include <iostream>
#include <vector>

using namespace std;
#define MAX 9999;

struct Node {
  int l, r;
  int min, max;
  Node *left, *right;
};

int max(int a, int b);
int min(int a, int b);
void update(Node *root, int x, int value);
void query(Node *root, int l, int r);
void build(Node *root, int l, int r);

Node tree[20000];
int num[10000];
int nNodeCount = 0;

void build(Node *root, int l, int r) {
  root->l = l;
  root->r = r;
  if (l == r) {
    root->min = root->max = num[l];
    return;
  }

  nNodeCount++;
  root->left = tree + nNodeCount;
  nNodeCount++;
  root->right = tree + nNodeCount;

  int m = (l + r) >> 1;
  build(root->left, l, m);
  build(root->right, m + 1, r);
  root->max = max(root->left->max, root->right->max);
  root->min = min(root->left->min, root->right->min);
}

void update(Node *root, int pos, int value) {
  if (root->l == root->r) {
    root->max += value;
    root->min = root->max;
    return;
  }

  int m = (root->l + root->r) >> 1;
  if (pos <= m) {
    update(root->left, pos, value);
  } else {
    update(root->right, pos, value);
  }
  root->max = max(root->left->max, root->right->max);
  root->min = min(root->left->min, root->right->min);
}

int max(int a, int b) {
  int maxValue;
  maxValue = a > b ? a : b;
  return maxValue;
}

int min(int a, int b) {
  int minValue;
  minValue = a < b ? a : b;
  return minValue;
}

int ans_max, ans_min;
void query(Node *root, int l, int r) {
  if (root->l == l && root->r == r) {
    cout << "L:" << l << " R:" << r << endl;
    ans_max = ans_max > root->max ? ans_max : root->max;
    ans_min = ans_min < root->min ? ans_min : root->min;
    return;
  }

  int m = (root->l + root->r) >> 1;
  cout << "L:" << l << " R:" << r << " M:" << m << endl;
  cout << endl;
  if (r <= m) {
    query(root->left, l, r);
  } else if (l > m) {
    query(root->right, l, r);
  } else {
    query(root->left, l, m);
    query(root->right, m + 1, r);
  }
}

int main() {
  int i = 0;
  int input, L, R;
  cout << "Enter a sequence (-1 is the end):\n";
  while (cin >> input && input != -1) {
    num[i] = input;
    i++;
  }

  cout << "Enter left bound: ";
  cin >> L;
  cout << "Enter right bound: ";
  cin >> R;

  build(tree, 0, i);
  query(tree, L, R);
  cout << "max:" << ans_max << endl;
}