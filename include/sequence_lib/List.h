//
// Created by chudo on 17.03.2026.
//

#ifndef LAB0_LIST_H
#define LAB0_LIST_H

#pragma once

template <typename TElement>
struct List {
    TElement data;
    List* next;
    List* prev;

    List(TElement value)  {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

#endif //LAB0_LIST_H
