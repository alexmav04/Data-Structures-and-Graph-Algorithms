#include <fstream>
#include <iostream>

using namespace std;

void decode(int, const string, double);

class chNode {
private:
  char ch;
  int freq;

public:
  int nodeCompare(const void *elem1, const void *elem2);

  friend class Tree;
};

class treeNode {
  char lcode;
  char rcode;
  treeNode *leftChild;
  treeNode *rightChild;

  friend class chNode;
};

int chNode::nodeCompare(const void *elem1, const void *elem2) {
  chNode a = *(chNode *)elem1;
  chNode b = *(chNode *)elem2;

  if (a.freq < b.freq)
    return 1;
  else if (a.freq > b.freq)
    return -1;
  else
    return 0;
}






int main() {
  int count[128] = {0};
  char ch;

  ifstream f_article("test_article.txt", ios::in);

  if (!f_article) {
    cerr << "File could not be opened." << endl;
    exit(1);
  }

  while (f_article.get(ch)) {
    int ch_i;

    ch_i = (int)ch;
    cout << ch_i << " ";
    count[ch_i]++;
  }

  // print numbers of code
  // cout << endl;

  // for (int i = 0; i < 128; i++){
  //   if (count[i] != 0){
  //     cout << (char)i << ": " << count[i] << endl;
  //   }
  // }

  f_article.close();
}

void decode(int, const string, double){};
