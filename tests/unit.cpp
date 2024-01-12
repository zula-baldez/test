#include <gtest/gtest.h>
#include "../tape/FileTapeImpl.h"
#include <filesystem>
#include "../tape-sort/TapeSortMergeImpl.h"

namespace fs = std::filesystem;

TEST(TapeClassTest, ReadWriteTest) {
    fs::copy_file("/home/egor/CLionProjects/yadro/tests/test.tape", "./tmp.tape", fs::copy_options::overwrite_existing);
    FileTapeImpl fileTape = FileTapeImpl("./tmp.tape", 0, 0, 0, 0, 7);
    for (int i = 0; i < fileTape.getSize(); i++) {
        int c = fileTape.readAndMove();
        if (i % 2 == 0) {
            EXPECT_EQ(c, 322);
        } else {
            EXPECT_EQ(c, 123);
        }
    }
    fileTape.rollBegin();
    for (int i = 0; i < fileTape.getSize(); i++) {
        if (i % 2 == 0) {
            fileTape.writeAndMove(1);
        } else {
            fileTape.writeAndMove(2);
        }
    }
    fileTape.rollBegin();
    for (int i = 0; i < fileTape.getSize(); i++) {
        int c = fileTape.readAndMove();
        if (i % 2 == 0) {
            EXPECT_EQ(c, 1);
        } else {
            EXPECT_EQ(c, 2);
        }
    }
    fs::remove("./tmp.tape");
}

TEST(Sorting, SortTest) {
    std::ofstream outputFile("./tmp.tape");
    outputFile.close();
    FileTapeImpl input = FileTapeImpl("/home/egor/CLionProjects/yadro/tests/test.tape", 0, 0, 0, 0, 7);
    FileTapeImpl output = FileTapeImpl("./tmp.tape", 0, 0, 0, 0, 7);
    TapeSortMergeImpl tapeSortMergeImpl = TapeSortMergeImpl();
    tapeSortMergeImpl.sort(input, output, [](int a, int b) { return a < b; });
    output.rollBegin();
    for (int i = 0; i < input.getSize(); i++) {
        int c = output.readAndMove();
        if (i < 3) {
            EXPECT_EQ(c, 123);
        } else {
            EXPECT_EQ(c, 322);
        }
    }
    fs::remove("./tmp.tape");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}