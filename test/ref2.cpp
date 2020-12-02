#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct cNode {
  char ch;   // character
  float pro; // probability
};

struct treeNode : public cNode {
  char lcode;
  char rcode;
  treeNode *left;  // left child
  treeNode *right; // right child
};

static int nodeCompare(const void *elem1, const void *elem2) {
  const cNode a = *(cNode *)elem1;
  const cNode b = *(cNode *)elem2;

  if (a.pro < b.pro)
    return 1;
  else if (a.pro > b.pro)
    return -1;
  else
    return 0;
}

class HCode {
private:
  int tsize;               // table size (number of chars)
  cNode *ptable;           // table of probabilities
  map<char, string> codes; // codeword for each char

public:
  void enCode(const char *inputFilepath, const char *outputFilepath) {
    map<char, int> freqs; // frequency for each char from input text
    int i;

    // Opening input file
    //
    ifstream inputFile;
    inputFile.open(inputFilepath, ifstream::in);
    if (!inputFile) {
      cerr << "error: unable to open input file: " << inputFilepath << endl;
    }

    // Counting chars
    //
    // bug 1, use eof() to judge the end of file will bring error。
    char ch; // char
    unsigned total = 0;
    while (true) {
      inputFile.get(ch);
      if (inputFile.eof())
        break;
      freqs[ch]++;
      total++;
    }
    tsize = (int)freqs.size();

    // Building decreasing freqs table
    //
    ptable = new cNode[tsize];
    // assert(ptable);
    float ftot = float(total);
    map<char, int>::iterator fi;
    for (fi = freqs.begin(), i = 0; fi != freqs.end(); ++fi, ++i) {
      ptable[i].ch = (*fi).first;
      ptable[i].pro = float((*fi).second) / ftot;
    }
    qsort(ptable, tsize, sizeof(cNode), nodeCompare);

    // Encoding
    //
    EncHuffman();

    // Opening output file
    //
    ofstream outputFile;
    outputFile.open(outputFilepath, ofstream::out);
    if (!outputFile) {
      cerr << "error: unable to open output file: " << outputFilepath << endl;
    }

    // Outputing ptable and codes
    //
    std::cout << endl << tsize << endl;
    outputFile << tsize << endl;
    for (int i = 0; i < tsize; i++) {
      std::cout << ptable[i].ch << "\t" << ptable[i].pro << "\t"
                << codes[ptable[i].ch].c_str() << endl;
      outputFile << ptable[i].ch << "\t" << ptable[i].pro << "\t"
                 << codes[ptable[i].ch].c_str() << endl;
    }

    // Outputing encoded text
    //
    // bug 2, if inputfile's eofbit is ture,the seekg()function will out of
    // work.
    // so you have to use clear() to reset inputfile‘s state.
    inputFile.clear();
    inputFile.seekg(0, inputFile.beg);
    std::cout << endl;
    outputFile << endl;
    while (true) {
      inputFile.get(ch);
      if (inputFile.eof())
        break;
      std::cout << codes[ch].c_str();
      outputFile << codes[ch].c_str();
    }
    std::cout << endl;

    // Cleaning
    //
    codes.clear();
    delete[] ptable;

    // Closing files
    //
    outputFile.close();
    outputFile.clear();
    inputFile.close();
    inputFile.clear();
  }

  void Decode(const char *inputFilename, const char *outputFilename) {
    // Opening input file
    ifstream inputFile;
    inputFile.open(inputFilename);
    if (!inputFile) {
      cerr << "error: unable to open input file: " << inputFilename << endl;
    }

    // Loading codes
    //
    inputFile >> tsize;
    char ch, code[128];
    float p;
    int i;
    inputFile.get();
    for (i = 0; i < tsize; i++) {
      inputFile.get(ch);
      inputFile >> p >> code;
      codes[ch] = code;
      inputFile.get();
    }
    inputFile.get();

    // Opening output file
    //
    ofstream outputFile;
    outputFile.open(outputFilename);
    if (!outputFile) {
      cerr << "error: unable to open output file: " << outputFilename << endl;
    }

    // Decoding and outputing to file
    //
    string accum = "";
    map<char, string>::iterator ci;
    while (true) {
      inputFile.get(ch);
      if (inputFile.eof())
        break;
      accum += ch;
      for (ci = codes.begin(); ci != codes.end(); ++ci) {
        if (!strcmp((*ci).second.c_str(), accum.c_str())) {
          accum = "";
          std::cout << (*ci).first;
          outputFile << (*ci).first;
        }
      }
    }
    std::cout << endl;

    // Cleaning
    //
    outputFile.close();
    outputFile.clear();
    inputFile.close();
    inputFile.clear();
  }

private:
  void EncHuffman() {
    // Creating leaves (initial top-nodes)
    //
    treeNode *n;
    vector<treeNode *> tops; // top-nodes
    int i, numtop = tsize;
    for (i = 0; i < numtop; i++) {
      n = new treeNode;
      // assert(n);
      n->ch = ptable[i].ch;
      n->pro = ptable[i].pro;
      n->left = NULL;
      n->right = NULL;
      tops.push_back(n);
    }

    // Building binary tree.
    // Combining last two nodes, replacing them by new node
    // without invalidating sort
    //
    while (numtop > 1) {
      n = new treeNode;
      // assert(n);
      n->pro = tops[numtop - 2]->pro + tops[numtop - 1]->pro;
      n->left = tops[numtop - 2];
      n->right = tops[numtop - 1];

      if (n->left->pro < n->right->pro) {
        n->lcode = '0';
        n->rcode = '1';
      } else {
        n->lcode = '1';
        n->rcode = '0';
      }
      tops.pop_back();
      tops.pop_back();

      bool isins = false;
      std::vector<treeNode *>::iterator ti;
      for (ti = tops.begin(); ti != tops.end(); ++ti) {
        if ((*ti)->pro < n->pro) {
          tops.insert(ti, n);
          isins = true;
          break;
        }
      }
      if (!isins)
        tops.push_back(n);
      numtop--;
    }

    // Building codes
    //
    treeNode *root = tops[0];
    GenerateCode(root);

    // Cleaning
    //
    DestroyNode(root);
    tops.clear();
  }

  void GenerateCode(treeNode *node) // for outside call: node is root
  {
    static string sequence = "";
    if (node->left) {
      sequence += node->lcode;
      GenerateCode(node->left);
    }

    if (node->right) {
      sequence += node->rcode;
      GenerateCode(node->right);
    }

    if (!node->left && !node->right)
      codes[node->ch] = sequence;

    int l = (int)sequence.length();
    if (l > 1)
      sequence = sequence.substr(0, l - 1);
    else
      sequence = "";
  }

  void DestroyNode(treeNode *node) // for outside call: node is root
  {
    if (node->left) {
      DestroyNode(node->left);
      delete node->left;
      node->left = NULL;
    }

    if (node->right) {
      DestroyNode(node->right);
      delete node->right;
      node->right = NULL;
    }
  }
};

int show_usage() {
  cout << "Huffman Coding Algorithm Version 1.0" << endl;
  cout << "  Modifier:Jeremy Lin 2015-03-14 @HQU" << endl;
  cout << "  Email:jianmin1990@outlook.com" << endl;
  cout << endl;
  cout << "Usage:" << endl;
  cout << " huffman [OPTIONS] input [output]" << endl;
  cout << " The defaul action is to encode the input file." << endl;
  cout << " -d\tDecode file." << endl;
  cout << endl;
  cout << "Examples:" << endl;
  cout << " huffman input.txt" << endl;
  cout << " huffman input.txt encoded.txt" << endl;
  cout << " huffman -d encoded.txt" << endl;
  exit(0);
}

int main(int argc, char **argv) {
  int i = 1;
  bool decFlag = false; // decode flag
  char inputFilename[128];
  char outputFilename[128];

  if (argc < 2) {
    show_usage();
  }

  if (strcmp(argv[i], "-d") == 0) {
    decFlag = true;
    ++i;
    if (i == argc) {
      show_usage();
    }
  }

  strcpy(inputFilename, argv[i]);
  ++i;

  if (i < argc) {
    strcpy(outputFilename, argv[i]);
  } else {
    if (decFlag)
      strcpy(outputFilename, "decoded.txt");
    else
      strcpy(outputFilename, "encoded.txt");
  }

  // Calling encoding or decoding subroutine
  //
  HCode *pCoder;
  pCoder = new HCode;
  if (!pCoder) {
    cerr << "error: unable to create a pointer to HCode" << endl;
  }

  if (!decFlag) {
    pCoder->enCode(inputFilename, outputFilename);
  } else {
    pCoder->Decode(inputFilename, outputFilename);
  }
  delete pCoder;

  return 0;
}