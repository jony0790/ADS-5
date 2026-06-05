// Copyright 2026

#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int SIZE>
class TStack {
 private:
    T data[SIZE];
    int pos;

 public:
    TStack() : pos(0) {}

    bool empty() const {
        return pos == 0;
    }

    bool full() const {
        return pos == SIZE;
    }

    void push(const T& value) {
        if (!full())
            data[pos++] = value;
    }

    void pop() {
        if (!empty())
            --pos;
    }

    T& top() {
        return data[pos - 1];
    }

    const T& top() const {
        return data[pos - 1];
    }

    int size() const {
        return pos;
    }
};

#endif  // INCLUDE_TSTACK_H_
