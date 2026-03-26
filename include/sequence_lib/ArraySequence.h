#ifndef LAB0_ARRAYSEQUENCE_H
#define LAB0_ARRAYSEQUENCE_H

#pragma once
#include <iostream>
#include <stdexcept>
#include "Sequence.h"

template <typename TElement>
class ArraySequence : public Sequence<TElement> {
private:
    TElement* data;
    int length;
    int isEmpty;
    int capacity;

    void Resize(int newCapacity);

public:
    ArraySequence();
    ~ArraySequence();

    int GetLength() const override;
    int GetIsEmpty() const override;

    TElement Get(int index) const override;
    TElement GetFirst() const override;
    TElement GetLast() const override;

    ArraySequence<TElement>* GetSubsequence(int startIndex, int endIndex) const override;

    void Append(TElement item) override;
    void Prepend(TElement item) override;
    void InsertAt(int index, TElement item) override;
    void Remove(TElement item) override;

    void Set(int index, TElement item) override;
};

template <typename TElement>
ArraySequence<TElement>::ArraySequence() {
    capacity = 1;
    length = 0;
    isEmpty = 1;
    data = new TElement[capacity];
}

template <typename TElement>
ArraySequence<TElement>::~ArraySequence() {
    delete[] data;
}

template <typename TElement>
void ArraySequence<TElement>::Resize(int newCapacity) {
    auto* new_data = new TElement[newCapacity];

    for (int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }

    delete[] data;
    capacity = newCapacity;
    data = new_data;
}

template <typename TElement>
int ArraySequence<TElement>::GetLength() const {
    return length;
}

template <typename TElement>
int ArraySequence<TElement>::GetIsEmpty() const {
    return isEmpty;
}

template <typename TElement>
TElement ArraySequence<TElement>::Get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Array index out of range");
    }
    return data[index];
}

template <typename TElement>
TElement ArraySequence<TElement>::GetFirst() const {
    return data[0];
}

template <typename TElement>
TElement ArraySequence<TElement>::GetLast() const {
    return data[length - 1];
}

template <typename TElement>
ArraySequence<TElement>* ArraySequence<TElement>::GetSubsequence(int startIndex, int endIndex) const {
    if ((startIndex < 0 || startIndex >= length) || (endIndex < 0 || endIndex >= length)) {
        throw std::out_of_range("Array index out of range");
    }

    if (startIndex > endIndex) {
        throw std::logic_error("endIndex parameter can't be greater than startIndex");
    }

    int new_size = endIndex - startIndex + 1;

    auto* subsequence = new ArraySequence<TElement>;
    subsequence->Resize(new_size);
    subsequence->length = new_size;
    subsequence->isEmpty = 0;
    for (int i = 0; i < new_size; i++) {
        subsequence->data[i] = data[startIndex + i];
    }

    return subsequence;
}

template <typename TElement>
void ArraySequence<TElement>::Append(TElement item) {
    if (length + 1 >= capacity) {
        Resize(capacity + 1);
    }

    data[length] = item;

    length++;

    if (isEmpty) {
        isEmpty = 0;
    }
}

template <typename TElement>
void ArraySequence<TElement>::Prepend(TElement item) {
    if (length + 1 >= capacity) {
        Resize(capacity + 1);
    }

    for (int i = length; i > 0; i--) {
        data[i] = data[i - 1];
    }
    data[0] = item;

    length++;

    if (isEmpty) {
        isEmpty = 0;
    }
}

template <typename TElement>
void ArraySequence<TElement>::InsertAt(int index, TElement item) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Array index out of range");
    }

    if (length + 1 >= capacity) {
        Resize(capacity + 1);
    }

    for (int i=length; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = item;

    length++;

    if (isEmpty) {
        isEmpty = 0;
    }
}

template <typename TElement>
void ArraySequence<TElement>::Set(int index, TElement item) {
    if (index < 0 || index > length - 1) {
        throw std::out_of_range("Array index out of range");
    }

    data[index] = item;
}

template <typename TElement>
void ArraySequence<TElement>::Remove(TElement item) {
    if (isEmpty) {
        throw std::logic_error("Array Sequence is empty");
    }
    int item_index = -1;

    for (int i = 0; i < length; i++) {
        if (data[i] == item) {
            item_index = i;
            break;
        }
    }

    if (item_index != -1) {
        for (int i = item_index; i < length - 1; i++) {
            data[i] = data[i + 1];
        }

        length--;
        if (length < capacity - 10) {
            Resize(capacity - 10);
        }
        if (length == 0) {
            isEmpty = 1;
        }
    }
}

#endif //LAB0_ARRAYSEQUENCE_H
