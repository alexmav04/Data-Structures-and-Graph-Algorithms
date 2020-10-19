/*
Design and implement efficient data structure and algorithm for finding shortest
path from the start cell s to the destination cell t in a maze of dimension m x
n.

date:2020-10-01
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int m, n; // for dimension m x n
struct QueueNode;
struct Queue;

int main(int argc, char *argv[]) {
  Queue q;
  q.enQueue(10);
}

struct QueueNode {
  int data;
  QueueNode *next;
  QueueNode() {
    data = 0;
    next = NULL;
  }
  QueueNode(int x) {
    data = x;
    next = NULL;
  }
};

struct Queue {
  QueueNode *front, *rear;
  int size;
  Queue() {
    front = rear = NULL;
    size = 0;
  }

  void enQueue(int x) {
    QueueNode *temp = new QueueNode(x);

    if (rear == NULL) {
      front = rear = temp;
      return;
    }
    rear->next = temp;
    rear = temp;
    size++;
  }
  void deQueue() {
    if (front == NULL)
      return;

    QueueNode *temp = front;
    front = front->next;

    if (front == NULL)
      rear = NULL;

    delete (temp);
    size--;
  }
  bool isEmpty() {
    if (size == 0)
      return 1;
    else
      return 0;
  }
  int getFront() {
    if (isEmpty()) {
      cout << "The queue is empty." << endl;
      return -1;
    }
    return front->data;
  }
  int getRear() {
    if (isEmpty()) {
      cout << "The queue is empty." << endl;
      return -1;
    }
    return rear->data;
  }
  int getSize() { return size; };
};

class QueueMethod {
private:
  QueueNode *front;
  QueueNode *rear;
  int size;

public:
  QueueMethod() {
    front = rear = NULL;
    size = 0;
  }
  // void Push(int x);
  // void Pop();
  bool isEmpty();
  int getFront();
  int getBack();
  int getSize();
};
