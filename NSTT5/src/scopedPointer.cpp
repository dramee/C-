template <typename T> class ScopedPointerTransfer {
  T *pointer;

public:
  ScopedPointerTransfer(T *raw) : pointer(raw) {}

  ~ScopedPointerTransfer() { delete pointer; }

  ScopedPointerTransfer(const ScopedPointerTransfer &other) = delete;
  ScopedPointerTransfer &operator=(const ScopedPointerTransfer &other) = delete;

  ScopedPointerTransfer(ScopedPointerTransfer &&other)
      : pointer(other.pointer) {
    other.pointer = nullptr;
  }
  ScopedPointerTransfer<T> &operator=(ScopedPointerTransfer<T> &&other) {
    if (this != &other) {
      delete pointer;
      pointer = other.pointer;
      other.pointer = nullptr;
    }
    return *this;
  }

  bool isEmpty() { return !pointer; }

  T &operator*() { return *pointer; }
  const T &operator*() const { return *pointer; }

  T *operator->() { return pointer; }
  const T *operator->() const { return pointer; }
};

template <typename T> class ScopedPointerDeep {
  T *pointer;

public:
  ScopedPointerDeep(T *raw) : pointer(raw) {}

  ~ScopedPointerDeep() { delete pointer; }

  ScopedPointerDeep(const ScopedPointerDeep &other)
      : pointer(new T(*other.pointer)) {}
  ScopedPointerDeep &operator=(const ScopedPointerDeep &other) {
    if (this != &other) {
      delete pointer;
      pointer = new T(*other.pointer);
    }
    return *this;
  }

  ScopedPointerDeep(ScopedPointerDeep &&other) : pointer(other.pointer) {
    other.pointer = nullptr;
  }
  ScopedPointerTransfer<T> &operator=(ScopedPointerTransfer<T> &&other) {
    if (this != &other) {
      delete pointer;
      pointer = other.pointer;
      other.pointer = nullptr;
    }
    return *this;
  }

  T &operator*() { return *pointer; }
  const T &operator*() const { return *pointer; }

  T *operator->() { return pointer; }
  const T *operator->() const { return pointer; }
};