#include <cstdlib>
#include <queue>
#include <random>
#include <stdexcept>

template <typename T> class Treap {
  struct TreapNode {
    size_t priority;
    T key;
    TreapNode *left = nullptr;
    TreapNode *right = nullptr;
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
      } else {
        left = nullptr;
      }

      if (other.right) {
        right = new TreapNode(*other.right);
      } else {
        right = nullptr;
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
      return {root, rr};
    } else {
      auto [ll, lr] = split(root->left, key);
      root->left = lr;
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
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
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
      oldRoot->right = nullptr;
      delete oldRoot;
      find = true;
    } else {
      std::pair<TreapNode *, bool> res = remove(t2->left, key, find);
      t2->left = res.first;
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

  T max(TreapNode *root) const {
    if (root->right) {
      return max(root->right);
    } else {
      return root->key;
    }
  }

  T min(TreapNode *root) const {
    if (root->left) {
      return min(root->left);
    } else {
      return root->key;
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
    return max(root);
  }

  T min() const {
    if (!root) {
      throw std::runtime_error("Data is empty");
    }
    return min(root);
  }

  std::vector<T> getSorted() { return getSorted(root); }

  ~Treap() { delete root; }

  class Iterator {
    TreapNode *current;
    std::queue<TreapNode *> queue;

  public:
    Iterator(TreapNode *root) {
      getLeftQueue(root);
      current = queue.front();
      queue.pop();
    }

    Iterator &operator++() {
      if (queue.empty()) {
        getLeftQueue(current->right);
      }
      current = queue.front();
      queue.pop();
      return *this;
    }
    Iterator operator++(int) {
      TreapNode *tmp = current;
      if (queue.empty()) {
        getLeftStack(current->right);
      }
      current = queue.front();
      queue.pop();
      return tmp;
    }

    void getLeftQueue(TreapNode *root) {
      if (!root) {
        return;
      }
      if (root->left) {
        getLeftQueue(root->left);
      }
      queue.push(root);
    }

    T &operator*() { return current->key; }

    TreapNode *operator->() { return current; }
    const TreapNode *operator->() const { return current; }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  Iterator begin() { return Iterator(root); }
  Iterator end() { return Iterator(nullptr); }
};