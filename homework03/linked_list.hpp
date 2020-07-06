#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

template <typename T>
class LinkedList {
   private:
    class Node {
       public:
        Node() = default;

        explicit Node(T *value) : value(value) {}

        T *value;
        Node *next{};
        Node *prev{};
    };

    class Iterator {
        Node *cur;

       public:
        explicit Iterator(Node *first) : cur(first) {}

        Iterator &operator++() {
            cur = cur->next;
            return *this;
        }

        Iterator &operator+(size_t n) {
            for (size_t i = 0; i < n; ++i) {
                cur = cur->next;
            }

            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return cur != other.cur;
        }

        T &operator*() {
            return *cur->value;
        }

        const T &operator*() const {
            return cur->value;
        }

        friend LinkedList;
    };

    class ConstIterator {
        const Node *cur;

       public:
        explicit ConstIterator(const Node *first) : cur(first) {}

        ConstIterator &operator++() {
            cur = cur->next;
            return *this;
        }

        ConstIterator &operator+(size_t n) {
            for (size_t i = 0; i < n; ++i) {
                cur = cur->next;
            }

            return *this;
        }

        bool operator!=(const ConstIterator &other) const {
            return cur != other.cur;
        }

        const T &operator*() const {
            return *cur->value;
        }
    };

   public:
    LinkedList() {
        head->next = tail;
        tail->prev = head;
    }

    LinkedList(const LinkedList &other) : LinkedList() {
        for (const T &elem : other) {
            push_back(elem);
        }
    }

    LinkedList(LinkedList &&other) : head(other.head), tail(other.tail), length(other.length) {
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }

    LinkedList(size_t count, const T &value) : LinkedList() {
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    ~LinkedList() {
        if (head != nullptr) {
            for (auto node = head->next; node != nullptr; node = node->next) {
                delete node->prev;
            }
        }

        if (tail != nullptr) {
            delete tail;
        }
    }

    Iterator begin() {
        return Iterator(head->next);
    }

    Iterator end() {
        return Iterator(tail);
    }

    ConstIterator begin() const {
        return ConstIterator(head->next);
    }

    ConstIterator end() const {
        return ConstIterator(tail);
    }

    T &operator[](int index) {
        return *find_node(index)->value;
    };

    const T &operator[](int index) const {
        return *find_node(index)->value;
    };

    LinkedList &operator=(const LinkedList &other) {
        if (this == &other) {
            return *this;
        }

        clear();
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }

        return *this;
    }

    T &front() {
        return *head->next->value;
    }

    const T &front() const {
        return *head->next->value;
    }

    T &back() {
        return *tail->prev->value;
    }

    const T &back() const {
        return *tail->prev->value;
    }

    void clear() {
        if (empty()) {
            return;
        }

        for (auto node = head->next->next; node != nullptr; node = node->next) {
            delete node->prev;
        }

        head->next = tail;
        tail->prev = head;
        length = 0;
    }

    size_t size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }

    void insert(size_t pos, const T &value) {
        auto new_node = new Node(new T(value));
        auto old_node = find_node(pos);

        old_node->prev->next = new_node;
        new_node->prev = old_node->prev;
        new_node->next = old_node;
        old_node->prev = new_node;
        ++length;
    }

    void push_front(const T &value) {
        insert(0, value);
    }

    void push_back(const T &value) {
        insert(length, value);
    }

    void pop_front() {
        delete_node(head->next);
    }

    void pop_back() {
        delete_node(tail->prev);
    }

    void erase(Iterator it) {
        delete_node(it.cur);
    }

    void erase(size_t pos) {
        safe_delete_node(find_node(pos));
    }

    LinkedList splice(size_t startPos, size_t count) {
        auto splice_head = find_node(startPos);
        auto splice_tail = find_node(startPos + count - 1);

        splice_head->prev->next = splice_tail->next;
        splice_tail->next->prev = splice_head->prev;
        length -= count;

        return LinkedList<T>(splice_head, splice_tail, count);
    }

    LinkedList &merge(LinkedList &other) {
        auto other_first = other.head->next;
        auto other_last = other.tail->prev;
        auto last = tail->prev;

        other.head->next = other.tail;
        other.tail->prev = other.head;
        last->next = other_first;
        other_first->prev = last;
        other_last->next = tail;
        tail->prev = other_last;
        length += other.length;
        other.length = 0;

        return *this;
    }

    void reverse() {
        for (auto node = head; node != nullptr; node = node->prev) {
            std::swap(node->next, node->prev);
        }

        std::swap(head, tail);
    }

    void swap(LinkedList &other) {
        std::swap(length, other.length);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }

   private:
    Node *head = new Node{};
    Node *tail = new Node{};
    size_t length = 0;

    Node *find_node(size_t index) {
        if (index < 0 || index > length) {
            throw std::out_of_range("pos is out of range [0, size]");
        }

        if (index < length / 2) {
            auto node = head->next;

            for (size_t i = 0; i < index; ++i) {
                node = node->next;
            }

            return node;
        } else {
            auto node = tail;

            for (size_t i = length; i > index; --i) {
                node = node->prev;
            }

            return node;
        }
    }

    const Node *find_node(size_t index) const {
        return const_cast<LinkedList<T> *>(this)->find_node(index);
    }

    void safe_delete_node(Node *node) {
        if (node == head || node == tail) {
            throw std::out_of_range("cannot delete head or tail");
        }

        delete_node(node);
    }

    void delete_node(Node *node) {
        auto nextNode = node->next;
        auto prevNode = node->prev;

        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }

        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }

        delete node;
        --length;
    }

    LinkedList(Node *front_node, Node *back_node, size_t count) {
        head->next = front_node;
        front_node->prev = head;
        tail->prev = back_node;
        back_node->next = tail;
        length = count;
    }

    friend std::istream &operator>>(std::istream &stream, LinkedList &list) {
        T tmp;

        while (stream >> tmp) {
            list.push_back(tmp);
        }

        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const LinkedList &list) {
        std::cout << "LinkedList{";

        if (!list.empty()) {
            auto it = list.begin();
            std::cout << *it;

            for (++it; it != list.end(); ++it) {
                std::cout << ", " << *it;
            }
        }

        std::cout << '}';
        return stream;
    }
};