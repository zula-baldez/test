#include "tape-sort/TapeSortMergeImpl.h"

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cout << "wrong args" << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::fstream config;
    config.open("/home/egor/CLionProjects/yadro/config");
    if(!config.is_open()) {
        std::cout<<"No such file"<<std::endl;
        return 1;
    }
    int size;
    int readDelay;
    int writeDelay;
    int moveDelay;
    int rollDelay;
    if(!(config >> size)) {
        std::cout << "No size in config" << std::endl;
        return 1;
    }
    if(!(config >> readDelay)) {
        std::cout << "No read delay in config" << std::endl;
        return 1;
    }
    if(!(config >> writeDelay)) {
        std::cout<<"No write delay in config"<<std::endl;
        return 1;
    }
    if(!(config >> moveDelay)) {
        std::cout<<"No move delay in config"<<std::endl;
        return 1;
    }
    if(!(config >> rollDelay)) {
        std::cout<<"No roll delay in config"<<std::endl;
        return 1;
    }
    FileTapeImpl tape = FileTapeImpl(inputFile,
                                     readDelay,
                                     writeDelay,
                                     moveDelay,
                                     rollDelay,
                                     size);
    FileTapeImpl output = FileTapeImpl(outputFile,
                                       readDelay,
                                       writeDelay,
                                       moveDelay,
                                       rollDelay,
                                       size);
    TapeSortMergeImpl tapeSortMergeImpl = TapeSortMergeImpl();
    tapeSortMergeImpl.sort(tape, output, [](int a, int b) { return a < b; });

    return 0;
}
