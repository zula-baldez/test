#ifndef YADRO_TAPESORTIMPL_H
#define YADRO_TAPESORTIMPL_H

#include <fstream>
#include "TapeSort.h"
#include "../tape/FileTapeImpl.h"

class TapeSortMergeImpl : public TapeSort {
public:
    void sort(Tape& inputTape, Tape& outputTape, comparator cmp) override;
};


#endif //YADRO_TAPESORTIMPL_H
