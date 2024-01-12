#ifndef YADRO_FILETAPEIMPL_H
#define YADRO_FILETAPEIMPL_H

#include "Tape.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>

class FileTapeImpl : public Tape {

public:
    FileTapeImpl(const std::string &input, int readDelay, int writeDelay, int moveDelay, int rollDelay, int size);

    FileTapeImpl(const FileTapeImpl &other) = delete;

    FileTapeImpl &operator=(const FileTapeImpl &other) = delete;

    FileTapeImpl(FileTapeImpl &&other) noexcept;

    FileTapeImpl &operator=(FileTapeImpl &&other) noexcept;

    void write(int val) override;

    int read() override;

    void moveLeft() override;

    void moveRight() override;

    void rollBegin() override;

    int readAndMove() override;

    void writeAndMove(int val) override;

    ~FileTapeImpl() override;

private:
    static void emulateDelay(int millis);

private:
    std::fstream file;
};

#endif //YADRO_FILETAPEIMPL_H
