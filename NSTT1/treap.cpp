#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

class TreapNode {
public:
  int key;
  int priority;
  TreapNode *left;
  TreapNode *right;

  TreapNode(int key, int priority)
      : key(key), priority(priority), left(nullptr), right(nullptr) {}
};

class Treap {
private:
  TreapNode *root;

  void split(TreapNode *root, int key, TreapNode *&left, TreapNode *&right) {
    if (root == nullptr) {
      left = nullptr;
      right = nullptr;
    } else if (key <= root->key) {
      split(root->left, key, left, root->left);
      right = root;
    } else {
      split(root->right, key, root->right, right);
      left = root;
    }
  }

  TreapNode *merge(TreapNode *left, TreapNode *right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }

    if (left->priority > right->priority) {
      left->right = merge(left->right, right);
      return left;
    } else {
      right->left = merge(left, right->left);
      return right;
    }
  }

  TreapNode *insert(TreapNode *root, int key, int priority) {
    TreapNode *left, *right;
    split(root, key, left, right);
    TreapNode *newNode = new TreapNode(key, priority);
    root = merge(merge(left, newNode), right);
    return root;
  }

  TreapNode *remove(TreapNode *root, int key) {
    if (root == nullptr) {
      return nullptr;
    }

    if (key < root->key) {
      root->left = remove(root->left, key);
    } else if (key > root->key) {
      root->right = remove(root->right, key);
    } else {
      if (root->left == nullptr) {
        root = root->right;
      } else if (root->right == nullptr) {
        root = root->left;
      }
    }
    return root;
  }

public:
  Treap() : root(nullptr) {}

  Treap(Treap &&other) : root(other.root) { other.root = nullptr; }

  Treap &operator=(Treap &&other) {

    if (this != &other) {
      delete this->root;
      this->root = other.root;
      other.root = nullptr;
    }

    return *this;
  }

  void insert(int key) {
    int priority = rand() % 1000000 + 1;
    root = insert(root, key, priority);
  }

  pair<Treap, Treap> split(int key) {
    Treap left, right;
    split(root, key, left.root, right.root);
    return {left, right};
  }

  void merge(Treap &other) {
    root = merge(root, other.root);
    other.root = nullptr;
  }

  void remove(int key) { root = remove(root, key); }

  void inorderTraversal(TreapNode *root) {
    if (root != nullptr) {
      inorderTraversal(root->left);
      cout << "(" << root->key << ", " << root->priority << ") ";
      inorderTraversal(root->right);
    }
  }

  void display() {
    inorderTraversal(root);
    cout << std::endl;
  }

  bool contains(int key) {
    TreapNode *node = root; // Assuming 'root' is the root node of the Treap.
    while (node != nullptr) {
      if (node->key == key) {
        return true;
      } else if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    };
    return false;
  }
};

void testInsert() {
  Treap treap;
  treap.insert(10);
  treap.insert(20);
  treap.insert(5);

  // Check if the keys exist in the treap
  assert(treap.contains(10));
  assert(treap.contains(20));
  assert(treap.contains(5));
  // Check if a non-existent key does not exist in the treap
  assert(!treap.contains(15));
  cout << "Test insert passed." << std::endl;
}

void testRemove() {
  Treap treap;
  treap.insert(10);
  treap.insert(20);
  treap.insert(5);
  treap.remove(20);

  // Check if the key was removed
  assert(!treap.contains(20));
  // Check if other keys still exist
  assert(treap.contains(10));
  assert(treap.contains(5));
  cout << "Test remove passed." << std::endl;
}

void testSplit() {
  Treap treap;
  treap.insert(10);
  treap.insert(20);
  treap.insert(5);
  auto [leftTreap, rightTreap] = treap.split(10);

  // Check if split occurred correctly
  assert(leftTreap.contains(5) && !leftTreap.contains(10));
  assert(rightTreap.contains(20) && rightTreap.contains(10));
  cout << "Test split passed." << std::endl;
}

void testMerge() {
  Treap treap1, treap2;
  treap1.insert(10);
  treap1.insert(5);
  treap2.insert(20);
  treap1.merge(treap2);

  // Check if all keys are in the merged treap
  assert(treap1.contains(5));
  assert(treap1.contains(10));
  assert(treap1.contains(20));
  // Ensure treap2 is empty after merge
  assert(!treap2.contains(20));
  cout << "Test merge passed." << std::endl;
}

int main() {
  // int* x = new int[10];
  testInsert();
  testRemove();
  testSplit();
  testMerge();

  cout << "All tests passed." << endl;

  return 0;
};