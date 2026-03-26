#ifndef LAB1_ISORTER_H
#define LAB1_ISORTER_H

#include <iostream>
#include "../sequence_lib/Sequence.h"

template<typename T>
class ISorter {
protected:
    virtual ~ISorter() = default;
public:
    virtual Sequence<T>* Sort(Sequence<T>* seq) = 0;
    virtual std::string GetName() const = 0;
};

#endif //LAB1_ISORTER_H
