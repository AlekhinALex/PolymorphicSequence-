#include <gtest/gtest.h>
#include "../inc/listSequence.hpp"

TEST(ListSequenceTest, DefaultConstructor)
{
    ListSequence<int> seq;
    EXPECT_EQ(seq.getLength(), 0);
}

TEST(ListSequenceTest, CountConstructor)
{
    ListSequence<int> seq(5);
    EXPECT_EQ(seq.getLength(), 5);
}

TEST(ListSequenceTest, ItemsArrayConstructor)
{
    int items[] = {1, 2, 3};
    ListSequence<int> seq(items, 3);
    EXPECT_EQ(seq.getLength(), 3);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 2);
    EXPECT_EQ(seq.get(2), 3);
}

TEST(ListSequenceTest, CopyConstructor)
{
    ListSequence<int> seq1;
    seq1.append(1);
    seq1.append(2);
    ListSequence<int> seq2(seq1);
    EXPECT_EQ(seq2.getLength(), 2);
    EXPECT_EQ(seq2.get(0), 1);
    EXPECT_EQ(seq2.get(1), 2);
}

TEST(ListSequenceTest, GetFirstLast)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    EXPECT_EQ(seq.getFirst(), 1);
    EXPECT_EQ(seq.getLast(), 2);
    seq.clear();
    EXPECT_THROW(seq.getFirst(), std::out_of_range);
    EXPECT_THROW(seq.getLast(), std::out_of_range);
}

TEST(ListSequenceTest, GetSet)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    EXPECT_EQ(seq.get(1), 2);
    seq.set(1, 3);
    EXPECT_EQ(seq.get(1), 3);
    EXPECT_THROW(seq.get(2), std::out_of_range);
    EXPECT_THROW(seq.set(2, 0), std::out_of_range);
}

TEST(ListSequenceTest, AppendPrepend)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    seq.prepend(0);
    EXPECT_EQ(seq.getLength(), 3);
    EXPECT_EQ(seq.get(0), 0);
    EXPECT_EQ(seq.get(1), 1);
    EXPECT_EQ(seq.get(2), 2);
}

TEST(ListSequenceTest, InsertAt)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(3);
    seq.insertAt(2, 1);
    EXPECT_EQ(seq.getLength(), 3);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(seq.get(1), 2);
    EXPECT_EQ(seq.get(2), 3);
    EXPECT_THROW(seq.insertAt(0, -1), std::out_of_range);
    EXPECT_THROW(seq.insertAt(0, 5), std::out_of_range);
}

TEST(ListSequenceTest, GetSubsequence)
{
    ListSequence<int> seq;
    for (int i = 0; i < 5; i++)
        seq.append(i);
    Sequence<int> *sub = seq.getSubsequence(1, 3);
    EXPECT_EQ(sub->getLength(), 3);
    EXPECT_EQ(sub->get(0), 1);
    EXPECT_EQ(sub->get(1), 2);
    EXPECT_EQ(sub->get(2), 3);
    delete sub;
    EXPECT_THROW(seq.getSubsequence(-1, 3), std::out_of_range);
    EXPECT_THROW(seq.getSubsequence(1, 5), std::out_of_range);
    EXPECT_THROW(seq.getSubsequence(3, 1), std::out_of_range);
}

TEST(ListSequenceTest, Concat)
{
    ListSequence<int> seq1;
    seq1.append(1);
    seq1.append(2);
    ListSequence<int> seq2;
    seq2.append(3);
    seq2.append(4);
    Sequence<int> *combined = seq1.concat(&seq2);
    EXPECT_EQ(combined->getLength(), 4);
    EXPECT_EQ(combined->get(0), 1);
    EXPECT_EQ(combined->get(3), 4);
    EXPECT_THROW(seq1.concat(nullptr), std::invalid_argument);
}

TEST(ListSequenceTest, ImmutableOperations)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(2);

    Sequence<int> *appended = seq.appendImmutable(3);
    EXPECT_EQ(seq.getLength(), 2);
    EXPECT_EQ(appended->getLength(), 3);
    EXPECT_EQ(appended->get(2), 3);
    delete appended;

    Sequence<int> *prepended = seq.prependImmutable(0);
    EXPECT_EQ(seq.getLength(), 2);
    EXPECT_EQ(prepended->getLength(), 3);
    EXPECT_EQ(prepended->get(0), 0);
    delete prepended;

    Sequence<int> *inserted = seq.insertAtImmutable(5, 1);
    EXPECT_EQ(seq.getLength(), 2);
    EXPECT_EQ(inserted->getLength(), 3);
    EXPECT_EQ(inserted->get(1), 5);
    delete inserted;

    Sequence<int> *set = seq.setImmutable(0, 10);
    EXPECT_EQ(seq.get(0), 1);
    EXPECT_EQ(set->get(0), 10);
    delete set;
}

TEST(ListSequenceTest, OperatorBrackets)
{
    ListSequence<int> seq;
    seq.append(1);
    seq.append(2);
    EXPECT_EQ(seq[0], 1);
    EXPECT_EQ(seq[1], 2);
    seq[1] = 3;
    EXPECT_EQ(seq[1], 3);
    EXPECT_THROW(seq[2], std::out_of_range);
}