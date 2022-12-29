#ifndef THREADS_TEST_CPP
#define THREADS_TEST_CPP

#include "newMain.cpp"
#include <gtest/gtest.h>
// TODO: Include more files + libraries
// Develop skeleton test cases for now.

// TEST CASE 1a: Runtime of a single-key path query
// Compare sequential (single-thread) time to
// multi-threaded (parallel) time
// GT comparison (sequential runtime > parallel runtime)
TEST(SingleQuery, SeqVsParallel)
{
    double parallelTime = 0.0;
    double seqTime = 0.0;
    string key = "";

    // TODO: call path query function for sequential run
    // TODO: call path query fn for parallel run

    EXPECT_GT(seqTime, parallelTime);
}

// TEST CASE 1b: Runtime of a single-key path query
// Same as 1a, using a different comparator
// LT comparison (parallel runtime < sequential runtime)
TEST(SingleQuery, ParallelVsSeq)
{
    double parallelTime = 0.0;
    double seqTime = 0.0;
    string key = "";

    // TODO: call path query function for parallel run
    // TODO: call path query fn for sequential run

    ASSERT_LEQ(parallelTime, seqTime);
}

// TEST CASE 2: Successfully process 2 path queries
// Function should be able to take in two unique
// and separate path queries
// Successfully returns results for both path queries
TEST(MultQuery, TwoQueries)
{
    string keyOne = "";
    string keyTwo = "";

    // TODO: call path query functions
    // Each path query call should be unique (i.e., using different keys)
    // Which are pre-assigned in the above strings
    // For this test's simplicity, the values of those keys will be all same type

    // EXPECT_EQ(pathQueryCallOne, resultOne);
    // EXPECT_EQ(pathQueryCallTwo, resultTwo);
}

// TEST CASE 3: Successfully process 4 path queries
// Function should be able to take in n unique
// and separate paths
// Successfully returns results for 4 path queries
// 4 chosen as my '17 13-inch MBP is a dual-core CPU with hyperthreading
// (1 core, 2 threads/core)
TEST(MultQuery, FourQueries)
{
    string keyOne = "";
    string keyTwo = "";
    string keyThree = "";
    string keyFour = "";

    // TODO: call path query functions
    // Each path query call should be unique (i.e., using different keys)
    // Which are pre-assigned in the above strings
    // For this test's simplicity, the values of those keys will be all same type (i.e., all strings)

    // EXPECT_EQ(pathQueryCallOne, resultOne);
    // EXPECT_EQ(pathQueryCallTwo, resultTwo);
    // EXPECT_EQ(pathQueryCallThree, resultThree);
    // EXPECT_EQ(pathQueryCallFour, resultFour);
}

// CONSIDER:
// 1) Two path queries returning two different types
// (i.e., one path query returns a string value, the other returns an Object value)
// 2) More tests to cover more machines
// (i.e., machine with 4 cores should be tested with 8 threads)

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}