#ifndef YADRO_TAPESORT_H
#define YADRO_TAPESORT_H

#include <iostream>
#include "../tape/Tape.h"
using comparator = bool (*)(int, int);

class TapeSort {
public:
    virtual void sort(Tape& inputTape, Tape& outputTape, comparator cmp) = 0;
    virtual ~TapeSort() = default;
};


#endif //YADRO_TAPESORT_H
