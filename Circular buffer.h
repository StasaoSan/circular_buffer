//
// Created by Тихонов Александр on 01.04.2023.
//

#ifndef INC_7_LAB_CIRCULAR_BUFFER_H
#define INC_7_LAB_CIRCULAR_BUFFER_H
#include <iostream>
#include <iterator>
#include <stdexcept>

template <class T>
class CircularBuffer {
private:
    T *buffer_;
    size_t size_;
    size_t start_;
    size_t end_;

public:
    CircularBuffer(size_t size) : buffer_(new T[size+1]), size_(size+1), start_(0), end_(0) {}

    ~CircularBuffer() { delete[] buffer_; }

    void push_back(T item){
        buffer_[end_] = item;
        end_ = (end_ + 1) % size_;
        if (end_ == start_) {
            start_ = (start_ + 1) % size_;
        }
    }
    void push_front(T item){
        start_ = (start_ + size_ - 1) % size_;
        buffer_[start_] = item;
        if ((end_ + 1) % size_ == start_) {
            end_ = start_;
        }
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Circular buffer is empty");
        }
        T item = buffer_[start_];
        start_ = (start_ + 1) % size_;
        return item;
    }
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Circular buffer is empty");
        }
        T item = buffer_[end_-1];
        end_ = (end_ - 1) % size_;
        return item;
    }

    bool empty() const { return start_ == end_; }

    size_t size() const { return (end_ + size_ - start_) % size_; }
    size_t capacity() const { return size_-1; }

    void set_capacity(size_t new_size) {
        if (new_size == size_)
            return;
        if (new_size < size_) {
            for (int i = 0; i < (size_ - new_size); ++i) {
                this->pop_front();
            }
        } else {
            T *new_buffer = new T[new_size];
            size_t new_end = 0;
            size_t buffer_size = size();

            for (size_t i = 0; i < buffer_size && new_end < new_size; i++) {
                new_buffer[new_end++] = buffer_[(start_ + i) % size_];
            }

            delete[] buffer_;
            buffer_ = new_buffer;
            size_ = new_size;
            start_ = 0;
            end_ = new_end;
        }
    }

    T &operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return buffer_[(start_ + index) % size_];
    }
    const T &operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return buffer_[(start_ + index) % size_];
    }

    class iterator {
    private:
        CircularBuffer* buffer_;
        size_t index_;
    public:
        size_t GetIndex_(){ return index_;}

        iterator(CircularBuffer* buffer, size_t index) : buffer_(buffer), index_(index) {}

        //operators here
        T& operator*() { return (*buffer_)[index_]; }
        const T& operator*() const { return (*buffer_)[index_]; }

        T* operator->() { return &(*buffer_)[index_]; }
        const T* operator->() const { return &(*buffer_)[index_]; }

        iterator &operator++() {
            index_++;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator &operator--() {
            index_--;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(ptrdiff_t n) const { return iterator(buffer_, index_ + n); }

        iterator operator-(ptrdiff_t n) const {
            return iterator(buffer_, index_ - n);
        }

        iterator &operator+=(ptrdiff_t n) {
            index_ += n;
            return *this;
        }

        iterator &operator-=(ptrdiff_t n) {
            index_ -= n;
            return *this;
        }

        std::ptrdiff_t operator-(const iterator &other) const {
            return index_ - other.index_;
        }

        bool operator==(const iterator &other) const {
            return buffer_ == other.buffer_ && index_ == other.index_;
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

        bool operator<(const iterator &other) const {
            return index_ < other.index_;
        }

        bool operator>(const iterator &other) const {
            return index_ > other.index_;
        }

        bool operator<=(const iterator &other) const {
            return !(*this > other);
        }

        bool operator>=(const iterator &other) const {
            return !(*this < other);
        }

        T &operator[](ptrdiff_t n) {
            return *(*this + n);
        }

        const T &operator[](ptrdiff_t n) const { return *(*this + n); }
    };

    iterator begin() { return iterator(this, 0); }
    iterator end() { return iterator(this, size()); }

    const iterator cbegin() const { return iterator(const_cast<CircularBuffer *>(this), 0); }
    const iterator cend() const { return iterator(const_cast<CircularBuffer*>(this), size()); }

    iterator insert(iterator position, const T &value) {
        if (size() == capacity()) {
            throw std::out_of_range("Buffer is full");
        }

        if (position > end()){
            throw std::out_of_range("Not correct iterator");
        }

        size_t index = position.GetIndex_();
        size_t new_end = (end_ + 1) % capacity();

        for (size_t i = new_end; i != index; i = (i + capacity() - 1) % capacity()) {
            buffer_[i] = buffer_[(i + capacity() - 1) % capacity()];
        }

        buffer_[index] = value;
        end_ = new_end;
        size_++;

        return iterator(this, index);
    }
    iterator erase(iterator position) {
        if (position == end()) {
            return position;
        }

        iterator next_it = position;
        ++next_it;
        while (next_it != end()) {
            *position = *next_it;
            position = next_it;
            ++next_it;
        }

        end_ = (end_ + size_ - 1) % size_;
        return iterator(this, position.GetIndex_());
    }
};
#endif //INC_7_LAB_CIRCULAR_BUFFER_H
