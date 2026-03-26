#include <iostream>
#include <cassert>
#include "../include/sequence_lib/ArraySequence.h"
#include "../include/sequence_lib/ListSequence.h"

void TestArraySequence() {
    ArraySequence<int> seq;

    assert(seq.GetLength() == 0);

    seq.Append(23);

    assert(seq.GetLength() == 1);
    assert(seq.GetFirst() == 23);
    assert(seq.GetLast() == 23);
    assert(seq.Get(0) == 23);

    seq.Append(43);

    assert(seq.GetLength() == 2);
    assert(seq.GetLast() == 43);

    seq.Prepend(53);
    assert(seq.GetFirst() == 53);
}

void TestListSequence() {
    ListSequence<int> seq;

    assert(seq.GetLength() == 0);

    seq.Append(23);

    assert(seq.GetLength() == 1);
    assert(seq.GetFirst() == 23);
    assert(seq.GetLast() == 23);
    assert(seq.Get(0) == 23);

    seq.Append(43);

    assert(seq.GetLength() == 2);
    assert(seq.GetLast() == 43);

    seq.Prepend(53);
    assert(seq.GetFirst() == 53);
}

int main() {

    TestArraySequence();
    TestListSequence();
    std::cout << "Tests passed" << std::endl;

    return 0;
}