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
void update(Node *root, int x, int v);
void query(Node *root, int l, int r);

Node tree[10000];// << 1];
int num[10000];
int nNodeCnt = 0;

void build(Node *root, int l, int r) {
  root->l = l;
  root->r = r;
  if (l == r) {
    root->min = root->max = num[l];
    return;
  }

  nNodeCnt++;
  root->left = tree + nNodeCnt;
  nNodeCnt++;
  root->right = tree + nNodeCnt;

  int m = (l + r) >> 1;
  build(root->left, l, m);
  build(root->right, m + 1, r);
  root->max = max(root->left->max, root->right->max);
  root->min = min(root->left->min, root->right->min);
}

void update(Node *root, int x, int v) {
  if (root->l == root->r) {
    root->max += v;
    root->min = root->max;
    return;
  }

  int m = (root->l + root->r) >> 1;
  if (x <= m) {
    update(root->left, x, v);
  } else {
    update(root->right, x, v);
  }
  root->max = max(root->left->max, root->right->max);
  root->min = min(root->left->min, root->right->min);
}

int max(int a, int b){
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
    ans_max = ans_max > root->max ? ans_max : root->max;
    ans_min = ans_min < root->min ? ans_min : root->min;
    return;
  }

  int m = (root->l + root->r) >> 1;
  if (r <= m) {
    query(root->left, l, r);
  } else if (l > m) {
    query(root->right, l, r);
  } else {
    query(root->left, l, m);
    query(root->right, m + 1, r);
  }
}

int main(){

}

// int main() {
//   cout << "Program started.\n";
//   vector<int> v1 = {4, 5, 1};
//   vector<int> v2 = {2, 8, 5, 3, 9, 4, 1};

//   sgt::SegmentTree<int> srcmakeSegmentTree1 = sgt::SegmentTree<int>(v1);
//   srcmakeSegmentTree1.print();

//   // Instantiate our segment tree data structure.
//   sgt::SegmentTree<int> srcmakeSegmentTree2 = sgt::SegmentTree<int>(v2);
//   srcmakeSegmentTree2.print();

//   // Some example queries and updates.
//   int L = 0;
//   int R = 6;
//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   R = 5;
//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   L = 1;
//   R = 1;
//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   L = 4;
//   R = 5;
//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   srcmakeSegmentTree2.update(5, 6);

//   srcmakeSegmentTree2.print();

//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   R = 6;
//   cout << "Min from " << L << " to " << R << " is "
//        << srcmakeSegmentTree2.query(L, R) << ".\n";

//   ////////////////////////////////////////////////////////////

//   cout << "Program finished.\n";
// }