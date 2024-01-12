#include "TapeSortMergeImpl.h"

void TapeSortMergeImpl::sort(Tape &inputTape, Tape &outputTape, comparator cmp) {
    std::ofstream outFile("/tmp/tmp.tape");
    outFile.close();
    std::ofstream tmpInpFile("/tmp/input-tmp.tape");
    tmpInpFile.close();
    FileTapeImpl tmpTape = FileTapeImpl("/tmp/tmp.tape",
                                        inputTape.getReadDelay(),
                                        inputTape.getWriteDelay(),
                                        inputTape.getMoveDelay(),
                                        inputTape.getRollDelay(), inputTape.getSize() / 2 + 1);
    FileTapeImpl inputTmp = FileTapeImpl("/tmp/input-tmp.tape",
                                        inputTape.getReadDelay(),
                                        inputTape.getWriteDelay(),
                                        inputTape.getMoveDelay(),
                                        inputTape.getRollDelay(),
                                        inputTape.getSize());
    for(int i = 0; i < inputTape.getSize(); i++) {
        inputTmp.writeAndMove(inputTape.readAndMove());
    }
    int step = 2;
    int size = inputTmp.getSize();
    int half = inputTmp.getSize() / 2;
    while (step < size * 2) {
        inputTmp.rollBegin();
        tmpTape.rollBegin();
        outputTape.rollBegin();
        //fill the halves
        for (int i = 0; i < size; ++i) {
            int c = inputTmp.readAndMove();
            i <= half ? tmpTape.writeAndMove(c) : outputTape.writeAndMove(c);
        }
        inputTmp.rollBegin();
        tmpTape.rollBegin();
        outputTape.rollBegin();
        int stepCount = (size + 1) / step;
        //merge halves
        for (int stepIt = 0; stepIt < stepCount; ++stepIt) {
            int tmpChooseLeft = std::min((size - stepIt * step) / 2 + (size - stepIt * step) % 2, step / 2);
            int outChooseLeft = tmpChooseLeft;
            if (size % 2 == 1 && stepIt == stepCount - 1) {
                outChooseLeft--;
            }
            int tmpVal = tmpTape.readAndMove();
            int outVal = outChooseLeft > 0 ? outputTape.readAndMove() : 0;

            while (tmpChooseLeft > 0 || outChooseLeft > 0) {
                if ((cmp(tmpVal, outVal) > 0 && tmpChooseLeft > 0) || (outChooseLeft <= 0)) {
                    inputTmp.writeAndMove(tmpVal);
                    tmpChooseLeft--;
                    if (tmpChooseLeft >= 1) {
                        tmpVal = tmpTape.readAndMove();
                    }
                } else {
                    inputTmp.writeAndMove(outVal);
                    outChooseLeft--;
                    if (outChooseLeft >= 1) {
                        outVal = outputTape.readAndMove();
                    }
                }
            }
        }
        step *= 2;
    }
    inputTmp.rollBegin();
    outputTape.rollBegin();
    for(int i = 0; i < inputTmp.getSize(); i++) {
        outputTape.writeAndMove(inputTmp.readAndMove());
    }

}
