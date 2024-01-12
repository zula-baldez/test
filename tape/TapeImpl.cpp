#include "FileTapeImpl.h"

FileTapeImpl::FileTapeImpl(const std::string &input, int readDelay, int writeDelay, int moveDelay, int rollDelay, int size) :
        Tape(readDelay, writeDelay, moveDelay, rollDelay, size) {
    file.open(input ,std::ios::in | std::ios::out);
    if(!file.is_open()) {
        throw std::runtime_error("File not found");
    }
}

FileTapeImpl::FileTapeImpl(FileTapeImpl &&other) noexcept : Tape(other.readDelay, other.writeDelay, other.moveDelay, other.rollDelay, other.size) {
    if (this == &other) {
        file = std::move(other.file);
    }
}

FileTapeImpl &FileTapeImpl::operator=(FileTapeImpl &&other) noexcept {
    if (this == &other) {
        file = std::move(other.file);
    }
    return *this;
}

int FileTapeImpl::read() {
    int symbol;
    if(!(file >> symbol)) {
        throw std::runtime_error("Failed to read from file");
    }
    file.seekp(-12, std::ios::cur);
    file.seekg(-12, std::ios::cur);
    return symbol;
}

void FileTapeImpl::moveLeft() {
    file.seekp(-12, std::ios::cur);
    file.seekg(-12, std::ios::cur);
    emulateDelay(moveDelay);
}

void FileTapeImpl::moveRight() {
    file.seekp(12, std::ios::cur);
    file.seekg(12, std::ios::cur);
    emulateDelay(moveDelay);
}

void FileTapeImpl::rollBegin() {
    file.seekg(0, std::ios::beg);
    file.seekp(0, std::ios::beg);
    emulateDelay(rollDelay);
}

void FileTapeImpl::write(int val) {
    file << std::setw(11) << std::setfill('0') << val << std::endl;
    file.seekp(-12, std::ios::cur);
    file.seekg(-12, std::ios::cur);
    emulateDelay(writeDelay);
}

int FileTapeImpl::readAndMove() {
    int symbol;
    if(!(file >> symbol)) {
        throw std::runtime_error("Failed to read from file");
    }
    emulateDelay(readDelay);
    emulateDelay(moveDelay);
    return symbol;

};

void FileTapeImpl::writeAndMove(int val) {
    file << std::setw(11) << std::setfill('0') << val << std::endl;
    emulateDelay(writeDelay);
    emulateDelay(moveDelay);
};


void FileTapeImpl::emulateDelay(int millis) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(millis));
}

FileTapeImpl::~FileTapeImpl() {
    file.close();
}
