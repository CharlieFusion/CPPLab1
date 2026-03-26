#ifndef LAB1_QUICKSORTER_H
#define LAB1_QUICKSORTER_H

#include <iostream>
#include "ISorter.h"
#include "../sequence_lib/Sequence.h"

template<typename T>
class QuickSorter : public ISorter<T> {
private:
    int Partition(Sequence<T>* seq, int low, int high);
    void QuickSort(Sequence<T>* seq, int low, int high);
public:
    Sequence<T>* Sort(Sequence<T>* seq) override;
    std::string GetName() const override { return "Quick Sort"; };
};

template<typename T>
int QuickSorter<T>::Partition(Sequence<T>* seq, int low, int high) {
    T pivot = seq->Get(high);
    int i = low - 1;

    for (int j = low; j <= high; j++) {
        if (seq->Get(j) <= pivot) {
            i++;
            T temp = seq->Get(i);
            seq->Set(i, seq->Get(j));
            seq->Set(j, temp);
        }
    }


    T temp = seq->Get(i + 1);
    seq->Set(i + 1, seq->Get(high));
    seq->Set(high, temp);

    return i + 1;
}

template<typename T>
void QuickSorter<T>::QuickSort(Sequence<T>* seq, int low, int high) {
    if (low < high) {
        int pi = Partition(seq, low, high);

        QuickSort(seq, low, pi - 1);
        QuickSort(seq, pi + 1, high);
    }
}

template<typename T>
Sequence<T>* QuickSorter<T>::Sort(Sequence<T>* seq) {
    if (seq->GetLength() <= 1) { return seq; }

    QuickSort(seq, 0, seq->GetLength() - 1);
    return seq;
}


#endif //LAB1_QUICKSORTER_H
