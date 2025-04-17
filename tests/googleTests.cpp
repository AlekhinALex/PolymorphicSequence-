#include <gtest/gtest.h>
#include "../inc/arraySequence.hpp"

class ArraySequenceTest : public ::testing::Test
{
protected:
    ArraySequence<int> *sequence;

    void SetUp() override
    {
        sequence = new ArraySequence<int>();
    }

    void TearDown() override
    {
        delete sequence;
    }
};

// Constructor Tests
TEST_F(ArraySequenceTest, DefaultConstructor)
{
    EXPECT_EQ(sequence->getLength(), 0);
}

TEST_F(ArraySequenceTest, ArrayConstructor)
{
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(items, 5);
    EXPECT_EQ(seq.getLength(), 5);
    EXPECT_EQ(seq.getFirst(), 1);
    EXPECT_EQ(seq.getLast(), 5);
}

TEST_F(ArraySequenceTest, SizeConstructor)
{
    ArraySequence<int> seq(3);
    EXPECT_EQ(seq.getLength(), 3);
}

// Basic Operations Tests
TEST_F(ArraySequenceTest, GetOperations)
{
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(items, 5);

    EXPECT_EQ(seq.getFirst(), 1);
    EXPECT_EQ(seq.getLast(), 5);
    EXPECT_EQ(seq.get(2), 3);
}

TEST_F(ArraySequenceTest, AppendOperation)
{
    sequence->append(1);
    sequence->append(2);

    EXPECT_EQ(sequence->getLength(), 2);
    EXPECT_EQ(sequence->getLast(), 2);
}

TEST_F(ArraySequenceTest, PrependOperation)
{
    sequence->prepend(1);
    sequence->prepend(2);

    EXPECT_EQ(sequence->getLength(), 2);
    EXPECT_EQ(sequence->getFirst(), 2);
}

TEST_F(ArraySequenceTest, InsertAtOperation)
{
    sequence->append(1);
    sequence->append(3);
    sequence->insertAt(2, 1);

    EXPECT_EQ(sequence->getLength(), 3);
    EXPECT_EQ(sequence->get(1), 2);
}

// Immutable Operations Tests
TEST_F(ArraySequenceTest, AppendImmutable)
{
    int items[] = {1, 2, 3};
    ArraySequence<int> seq(items, 3);

    Sequence<int> *newSeq = seq.appendImmutable(4);

    EXPECT_EQ(seq.getLength(), 3);
    EXPECT_EQ(newSeq->getLength(), 4);
    EXPECT_EQ(newSeq->getLast(), 4);

    delete newSeq;
}

TEST_F(ArraySequenceTest, PrependImmutable)
{
    int items[] = {1, 2, 3};
    ArraySequence<int> seq(items, 3);

    Sequence<int> *newSeq = seq.prependImmutable(0);

    EXPECT_EQ(seq.getLength(), 3);
    EXPECT_EQ(newSeq->getLength(), 4);
    EXPECT_EQ(newSeq->getFirst(), 0);

    delete newSeq;
}

// Subsequence Test
TEST_F(ArraySequenceTest, GetSubsequence)
{
    int items[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(items, 5);

    Sequence<int> *subSeq = seq.getSubsequence(1, 3);

    EXPECT_EQ(subSeq->getLength(), 3);
    EXPECT_EQ(subSeq->getFirst(), 2);
    EXPECT_EQ(subSeq->getLast(), 4);

    delete subSeq;
}

// Concatenation Test
TEST_F(ArraySequenceTest, ConcatOperation)
{
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5, 6};

    ArraySequence<int> seq1(items1, 3);
    ArraySequence<int> seq2(items2, 3);

    Sequence<int> *result = seq1.concat(&seq2);
    EXPECT_EQ(result->getLength(), 6);
    EXPECT_EQ(result->getFirst(), 1);
    EXPECT_EQ(result->getLast(), 6);
}

// Operator Tests
TEST_F(ArraySequenceTest, OperatorAccess)
{
    int items[] = {1, 2, 3};
    ArraySequence<int> seq(items, 3);

    EXPECT_EQ(seq[0], 1);
    EXPECT_EQ(seq[1], 2);
    EXPECT_EQ(seq[2], 3);
}

// Exception Tests
TEST_F(ArraySequenceTest, IndexOutOfRange)
{
    int items[] = {1, 2, 3};
    ArraySequence<int> seq(items, 3);

    EXPECT_THROW(seq.get(-1), std::out_of_range);
    EXPECT_THROW(seq.get(3), std::out_of_range);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
