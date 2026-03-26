#ifndef LAB1_COCKTAILSORTER_H
#define LAB1_COCKTAILSORTER_H

#include <iostream>
#include "ISorter.h"
#include "../sequence_lib/Sequence.h"

template<typename T>
class CocktailSorter : public ISorter<T> {
public:
    Sequence<T>* Sort(Sequence<T>* seq) override;
    std::string GetName() const override { return "Shaker Sort"; };
};

template<typename T>
Sequence<T>* CocktailSorter<T>::Sort(Sequence<T>* seq) {
    if (seq->GetLength() <= 1) { return seq; }

    int left = 0;
    int right = seq->GetLength() - 1;
    int is_moves = 1;
    int last_move = -1;

    while ((left < right) && is_moves) {
        is_moves = 0;
        for (int i = left; i < right; i++) {
            if (seq->Get(i) > seq->Get(i + 1)) {
                T temp = seq->Get(i);
                seq->Set(i, seq->Get(i + 1));
                seq->Set(i + 1, temp);
                last_move = i;
                is_moves = 1;
            }
        }
        right = last_move;
        for (int i = right; i > left; i--) {
            if (seq->Get(i) < seq->Get(i - 1)) {
                T temp = seq->Get(i);
                seq->Set(i, seq->Get(i - 1));
                seq->Set(i - 1, temp);
                last_move = i;
                is_moves = 1;
            }
        }
        left = last_move;
    }

    return seq;
}

#endif //LAB1_COCKTAILSORTER_H
