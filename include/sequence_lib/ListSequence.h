#ifndef LAB0_LISTSEQUENCE_H
#define LAB0_LISTSEQUENCE_H

#pragma once
#include <iostream>
#include "Sequence.h"
#include "List.h"

template <typename TElement>
class ListSequence : public Sequence<TElement> {
private:
    List<TElement>* head;
    List<TElement>* tail;
    int length;
    int isEmpty;

public:
    ListSequence();
    ~ListSequence();

    int GetLength() const override;
    int GetIsEmpty() const override;

    TElement Get(int index) const override;
    TElement GetFirst() const override;
    TElement GetLast() const override;

    ListSequence<TElement>* GetSubsequence(int startIndex, int endIndex) const override;

    void Append(TElement item) override;
    void Prepend(TElement item) override;
    void InsertAt(int index, TElement item) override;
    void Remove(TElement item) override;

    void Set(int index, TElement item) override;
};

template <typename TElement>
ListSequence<TElement>::ListSequence() {
    head = nullptr;
    tail = nullptr;
    length = 0;
    isEmpty = 1;
}

template <typename TElement>
ListSequence<TElement>::~ListSequence() {
    List<TElement>* current = head;

    while (current != tail) {
        List<TElement>* next = current->next;
        delete current;
        current = next;
    }
    delete current;
}

template <typename TElement>
int ListSequence<TElement>::GetLength() const {
    return length;
}

template <typename TElement>
int ListSequence<TElement>::GetIsEmpty() const {
    return isEmpty;
}

template <typename TElement>
TElement ListSequence<TElement>::Get(int index) const {
    if (index < 0 || index > length - 1) {
        throw std::out_of_range("Array index out of range");
    }

    if (index < length / 2) {
        List<TElement>* current = head;
        for (int i=0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    } else {
        List<TElement>* current = tail;
        for (int i=length - 1; i > index; i--) {
            current = current->prev;
        }
        return current->data;
    }
}

template <typename TElement>
TElement ListSequence<TElement>::GetFirst() const {
    return head->data;
}

template <typename TElement>
TElement ListSequence<TElement>::GetLast() const {
    return tail->data;
}

template <typename TElement>
ListSequence<TElement> *ListSequence<TElement>::GetSubsequence(int startIndex, int endIndex) const {
    // TODO: Clone each node of subseq


    if ((startIndex < 0 || startIndex >= length) || (endIndex < 0 || endIndex >= length)) {
        throw std::out_of_range("Array index out of range");
    }

    if (startIndex > endIndex) {
        throw std::logic_error("endIndex parameter can't be greater than startIndex");
    }

    ListSequence<TElement>* new_seq = new ListSequence<TElement>();
    new_seq->length = endIndex - startIndex + 1;
    new_seq->isEmpty = 0;

    if(startIndex < length - endIndex) {
        List<TElement>* current = head;
        for (int i=0; i<startIndex; i++) {
            current = current->next;
        }
        List<TElement>* cur_item = new List<TElement>(current->data);
        new_seq->head = cur_item;
        for (int i=0; i<new_seq->length; i++) {
            current = current->next;
            List<TElement>* new_item = new List<TElement>(current->data);
            new_item->prev = cur_item;
            cur_item->next = new_item;
            cur_item = new_item;
        }
        new_seq->tail = cur_item;
        new_seq->head->prev = new_seq->tail;
        new_seq->tail->next = new_seq->head;

    } else {
        List<TElement>* current = tail;
        for (int i=length - 1; i > endIndex; i--) {
            current = current->prev;
        }
        List<TElement>* cur_item = new List<TElement>(current->data);
        new_seq->tail = cur_item;
        for (int i=0; i<new_seq->length; i++) {
            current = current->prev;
            List<TElement>* new_item = new List<TElement>(current->data);
            new_item->next = cur_item;
            cur_item->prev = new_item;
            cur_item = new_item;
        }
        new_seq->head = cur_item;
        new_seq->head->prev = new_seq->tail;
        new_seq->tail->next = new_seq->head;
    }

    return new_seq;
}

template <typename TElement>
void ListSequence<TElement>::Append(TElement item) {
    List<TElement>* new_item = new List<TElement>(item);
    if (GetIsEmpty()) {
        head = new_item;
        tail = new_item;
    } else {
        tail->next = new_item;
    }
    new_item->prev = tail;
    new_item->next = head;
    tail = new_item;
    isEmpty = 0;
    length++;
}

template <typename TElement>
void ListSequence<TElement>::Prepend(TElement item) {
    List<TElement>* new_item = new List<TElement>(item);
    if (GetIsEmpty()) {
        head = new_item;
        tail = new_item;
    } else {
        head->prev = new_item;
    }
    new_item->prev = tail;
    new_item->next = head;
    head = new_item;
    isEmpty = 0;
    length++;
}

template <typename TElement>
void ListSequence<TElement>::InsertAt(int index, TElement item) {
    if (index < 0 || index > length - 1) {
        throw std::out_of_range("Array index out of range");
    }

    List<TElement>* new_item = new List<TElement>(item);

    if (isEmpty) {
        head = new_item;
        tail = new_item;
        new_item->prev = tail;
        new_item->next = head;
    } else {
        if (index < length / 2) {
            List<TElement> *prev = head;
            for (int i = 0; i < index; i++) {
                prev = prev->next;
            }
            new_item->prev = prev;
            new_item->next = prev->next;
            prev->next->prev = new_item;
            prev->next = new_item;
        } else {
            List<TElement> *next = tail;
            for (int i = length - 1; i > index; i--) {
                next = next->prev;
            }
            new_item->prev = next->prev;
            new_item->next = next;
            next->prev->next = new_item;
            next->prev = new_item;
        }
    }
    isEmpty = 0;
    length++;
}

template <typename TElement>
void ListSequence<TElement>::Set(int index, TElement item) {
    if (index < 0 || index > length - 1) {
        throw std::out_of_range("Array index out of range");
    }

    List<TElement>* current;

    if (index < length / 2) {
        current = head;
        for (int i=0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int i=length - 1; i > index; i--) {
            current = current->prev;
        }
    }
    current->data = item;
}

template <typename TElement>
void ListSequence<TElement>::Remove(TElement item) {
    List<TElement>* current = head;
    for (int i = 0; i < length; i++) {
        if (current->data == item) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
            if (length <= 0) {
                isEmpty = 1;
            }
            break;
        }
        current = current->next;
    }
}

#endif //LAB0_LISTSEQUENCE_H
