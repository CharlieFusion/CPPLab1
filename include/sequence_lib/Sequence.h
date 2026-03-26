#ifndef LAB0_SEQUENCE_H
#define LAB0_SEQUENCE_H
#pragma once

template<typename TElement>
class Sequence {
private:
    int length;
    int isEmpty;

public:
    virtual int GetLength() const = 0;
    virtual int GetIsEmpty() const = 0;

    virtual TElement Get(int index) const = 0;
    virtual TElement GetLast() const = 0;
    virtual TElement GetFirst() const = 0;
    virtual Sequence<TElement>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual void Append(TElement item) = 0;
    virtual void Prepend(TElement item) = 0;
    virtual void InsertAt(int index, TElement item) = 0;
    virtual void Remove(TElement item) = 0;

    virtual void Set(int index, TElement item) = 0;
};

#endif //LAB0_SEQUENCE_H
