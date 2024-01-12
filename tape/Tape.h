#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H

#include <string>

class Tape {
public:
    Tape(int readDelay, int writeDelay, int moveDelay, int rollDelay, int size) :
            readDelay(readDelay), writeDelay(writeDelay), moveDelay(moveDelay), rollDelay(rollDelay), size(size) {}

    virtual void write(int val) = 0;

    virtual int read() = 0;

    virtual int readAndMove() = 0;

    virtual void writeAndMove(int val) = 0;

    virtual void moveLeft() = 0;

    virtual void moveRight() = 0;

    virtual void rollBegin() = 0;

    virtual ~Tape() = default;

    int getReadDelay() const {
        return readDelay;
    }

    int getWriteDelay() const {
        return writeDelay;
    }

    int getMoveDelay() const {
        return moveDelay;
    }

    int getRollDelay() const {
        return rollDelay;
    }

    int getSize() const {
        return size;
    }

protected:
    int readDelay;
    int writeDelay;
    int moveDelay;
    int rollDelay;
    int size;
};

#endif //YADRO_TAPE_H
