#include <cstdlib>
#include <queue>
#include <random>
#include <stdexcept>
#include <iostream>

template <typename T> class Treap {
  struct TreapNode {
    size_t priority;
    T key;
    TreapNode *left = nullptr;
    TreapNode *right = nullptr;
    TreapNode *parent = nullptr;
    TreapNode(T value) : key(value) {
      std::random_device dev;
      std::mt19937 rng(dev());
      std::uniform_int_distribution<std::mt19937::result_type> dist(1,
                                                                    1'000'000);
      priority = dist(dev);
    };

    TreapNode(T value, size_t priority) : key(value), priority(priority) {}

    TreapNode(const TreapNode &other)
        : key(other.key), priority(other.priority) {
      if (other.left) {
        left = new TreapNode(*other.left);
        left->parent = this;
      }

      if (other.right) {
        right = new TreapNode(*other.right);
        right->parent = this;
      }
    }

    TreapNode &operator=(TreapNode other) {
      std::swap(key, other.key);
      std::swap(priority, other.priority);
      std::swap(left, other.left);
      std::swap(right, other.right);
      return *this;
    }

    ~TreapNode() {
      delete left;
      delete right;
    }
  };

  TreapNode *root = nullptr;

  std::pair<TreapNode *, TreapNode *> split(TreapNode *root, T key) {
    if (!root) {
      return {nullptr, nullptr};
    }
    if (key > root->key) {
      auto [rl, rr] = split(root->right, key);
      root->right = rl;
      if (rl) {
        rl->parent = root;
      }
      return {root, rr};
    } else {
      auto [ll, lr] = split(root->left, key);
      root->left = lr;
      if (lr) {
        lr->parent = root;
      }
      return {ll, root};
    }
  }

  TreapNode *merge(TreapNode *t1, TreapNode *t2) {
    if (!t1) {
      return t2;
    }
    if (!t2) {
      return t1;
    }
    if (t1->priority < t2->priority) {
      t1->right = merge(t1->right, t2);
      if (t1->right) {
        t1->right->parent = t1;
      }
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
      if (t2->left) {
        t2->left->parent = t2;
      }
      return t2;
    }
  }

  std::pair<TreapNode *, bool> remove(TreapNode *root, T key, bool find) {
    if (!root) {
      return {nullptr, false};
    }
    std::pair<TreapNode *, TreapNode *> res = split(root, key);
    TreapNode *t1 = res.first;
    TreapNode *t2 = res.second;
    if (t2->key == key) {
      TreapNode *oldRoot = t2;
      t2 = t2->right;
      if (t2) {
        t2->parent = oldRoot->parent;
      }
      oldRoot->right = nullptr;
      delete oldRoot;
      find = true;
    } else {
      std::pair<TreapNode *, bool> res = remove(t2->left, key, find);
      t2->left = res.first;
      if (res.first) {
        res.first->parent = t2;
      }
      find = res.second;
    }
    return {merge(t1, t2), find};
  }

  bool find(TreapNode *root, T key) const {
    if (!root) {
      return false;
    }
    if (root->key == key) {
      return true;
    } else {
      return find(root->left, key) || find(root->right, key);
    }
  }

  static TreapNode *findMaxNode(TreapNode *root) {
    if (root->right) {
      return findMaxNode(root->right);
    } else {
      return root;
    }
  }

  static TreapNode *findMinNode(TreapNode *root) {
    if (root->left) {
      return findMinNode(root->left);
    } else {
      return root;
    }
  }

  std::vector<T> getSorted(TreapNode *root) const {
    if (!root) {
      std::vector<T> res;
      return res;
    }
    std::vector<T> previous = getSorted(root->left);
    previous.push_back(root->key);
    std::vector<T> next = getSorted(root->right);
    previous.insert(previous.end(), next.begin(), next.end());
    return previous;
  }

  void print(TreapNode *root) {
    if (root->left) {
      print(root->left);
    }
    std::cout << root->key << ": "
              << root->priority << std::endl;
    if (root->right) {
      print(root->right);
    }
  }

public:
  Treap() = default;

  Treap(const Treap &other) { root = new TreapNode(*other.root); }

  Treap &operator=(Treap other) {
    std::swap(root, other.root);
    return *this;
  }

  Treap(Treap &&other) {
    root = other.root;
    other.root = nullptr;
  }

  void insert(T key) {
    std::pair<TreapNode *, TreapNode *> res = split(root, key);
    TreapNode *t1 = res.first;
    TreapNode *t2 = res.second;
    TreapNode *newNode = new TreapNode{key};
    root = merge(merge(t1, newNode), t2);
  }

  void insert(T key, size_t priority) {
    std::pair<TreapNode *, TreapNode *> res = split(root, key);
    TreapNode *t1 = res.first;
    TreapNode *t2 = res.second;
    TreapNode *newNode = new TreapNode{key, priority};
    root = merge(merge(t1, newNode), t2);
  }

  void remove(T key) {
    std::pair<TreapNode *, bool> res = remove(root, key, false);
    if (!res.second) {
      throw std::invalid_argument("Remove error: no such element");
    } else {
      root = res.first;
    }
  }

  bool empty() const { return !root; }

  bool find(T key) const { return find(root, key); }

  T max() const {
    if (!root) {
      throw std::runtime_error("Data is empty");
    }
    return findMaxNode(root)->key;
  }

  T min() const {
    if (!root) {
      throw std::runtime_error("Data is empty");
    }
    return findMinNode(root)->key;
  }

  std::vector<T> getSorted() { return getSorted(root); }

  ~Treap() { delete root; }

  class Iterator {
    TreapNode *current;

    TreapNode *returnToParent(TreapNode *root) {
      if (!root->parent) {
        return nullptr;
      }
      if (root->parent->right == root) {
        return returnToParent(root->parent);
      } else {
        return root->parent;
      }
    }

  public:
    Iterator(TreapNode *root) { current = root; }

    Iterator &operator++() {
      if (current->right) {
        current = findMinNode(current->right);
      } else {
        current = returnToParent(current);
      }
      return *this;
    }
    Iterator operator++(int) {
      TreapNode *tmp = current;
      if (current->right) {
        current = findMinNode(current->right);
      } else if (current->parent->right == current) {
        current = current->parent->parent;
      } else {
        current = current->parent;
      }
      return tmp;
    }

    T &operator*() { return current->key; }

    TreapNode *operator->() { return current; }
    const TreapNode *operator->() const { return current; }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  void print() { print(root); }

  Iterator begin() { return Iterator(findMinNode(root)); }
  Iterator end() { return Iterator(nullptr); }
};