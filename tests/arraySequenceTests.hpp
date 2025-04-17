#pragma once
#include "sequenceTest.hpp"

template <typename T>
class ArraySequenceTest : public SequenceTest<T>
{
protected:
    void SetUp() override
    {
        this->sequence = new ArraySequence<T>(3);
        this->emptySequence = new ArraySequence<T>();

        // Initialize with values 0, 1, 2
        for (int i = 0; i < 3; i++)
        {
            this->sequence->set(i, T(i));
        }
    }

    void TestConstructors() override
    {
        // Test default constructor
        EXPECT_EQ(this->emptySequence->getLength(), 0);

        // Test size constructor
        ArraySequence<T> sized(5);
        EXPECT_EQ(sized.getLength(), 5);

        // Test items array constructor
        T items[] = {T(10), T(20), T(30)};
        ArraySequence<T> fromItems(items, 3);
        EXPECT_EQ(fromItems.getLength(), 3);
        EXPECT_EQ(fromItems.get(0), T(10));
        EXPECT_EQ(fromItems.get(1), T(20));
        EXPECT_EQ(fromItems.get(2), T(30));

        // Test copy constructor
        ArraySequence<T> copy(*dynamic_cast<ArraySequence<T> *>(this->sequence));
        EXPECT_EQ(copy.getLength(), 3);
        EXPECT_EQ(copy.get(0), T(0));
        EXPECT_EQ(copy.get(1), T(1));
        EXPECT_EQ(copy.get(2), T(2));
    }

    void TestGetters() override
    {
        // Test getFirst
        EXPECT_EQ(this->sequence->getFirst(), T(0));

        // Test getLast
        EXPECT_EQ(this->sequence->getLast(), T(2));

        // Test get
        EXPECT_EQ(this->sequence->get(0), T(0));
        EXPECT_EQ(this->sequence->get(1), T(1));
        EXPECT_EQ(this->sequence->get(2), T(2));

        // Test getLength
        EXPECT_EQ(this->sequence->getLength(), 3);
        EXPECT_EQ(this->emptySequence->getLength(), 0);

        // Test out of bounds
        EXPECT_THROW(this->sequence->get(-1), std::out_of_range);
        EXPECT_THROW(this->sequence->get(3), std::out_of_range);
        EXPECT_THROW(this->emptySequence->getFirst(), std::out_of_range);
        EXPECT_THROW(this->emptySequence->getLast(), std::out_of_range);
    }

    void TestSubsequence() override
    {
        // Test valid subsequence
        Sequence<T> *sub = this->sequence->getSubsequence(1, 2);
        EXPECT_EQ(sub->getLength(), 2);
        EXPECT_EQ(sub->get(0), T(1));
        EXPECT_EQ(sub->get(1), T(2));
        delete sub;

        // Test full sequence
        sub = this->sequence->getSubsequence(0, 2);
        EXPECT_EQ(sub->getLength(), 3);
        delete sub;

        // Test single element
        sub = this->sequence->getSubsequence(1, 1);
        EXPECT_EQ(sub->getLength(), 1);
        EXPECT_EQ(sub->get(0), T(1));
        delete sub;

        // Test invalid ranges
        EXPECT_THROW(this->sequence->getSubsequence(-1, 2), std::out_of_range);
        EXPECT_THROW(this->sequence->getSubsequence(1, 3), std::out_of_range);
        EXPECT_THROW(this->sequence->getSubsequence(2, 1), std::out_of_range);
        EXPECT_THROW(this->emptySequence->getSubsequence(0, 0), std::out_of_range);
    }

    void TestModifiers() override
    {
        // Test append
        this->sequence->append(T(3));
        EXPECT_EQ(this->sequence->getLength(), 4);
        EXPECT_EQ(this->sequence->getLast(), T(3));

        // Test prepend
        this->sequence->prepend(T(-1));
        EXPECT_EQ(this->sequence->getLength(), 5);
        EXPECT_EQ(this->sequence->getFirst(), T(-1));

        // Test insertAt
        this->sequence->insertAt(T(10), 2);
        EXPECT_EQ(this->sequence->getLength(), 6);
        EXPECT_EQ(this->sequence->get(2), T(10));

        // Test set
        this->sequence->set(0, T(100));
        EXPECT_EQ(this->sequence->get(0), T(100));

        // Test concat
        ArraySequence<T> other(2);
        other.set(0, T(50));
        other.set(1, T(60));
        this->sequence->concat(&other);
        EXPECT_EQ(this->sequence->getLength(), 8);
        EXPECT_EQ(this->sequence->get(6), T(50));
        EXPECT_EQ(this->sequence->get(7), T(60));

        // Test invalid modifications
        EXPECT_THROW(this->sequence->insertAt(T(0), -1), std::out_of_range);
        EXPECT_THROW(this->sequence->insertAt(T(0), 100), std::out_of_range);
        EXPECT_THROW(this->sequence->set(-1, T(0)), std::out_of_range);
        EXPECT_THROW(this->sequence->set(100, T(0)), std::out_of_range);
        EXPECT_THROW(this->sequence->concat(nullptr), std::invalid_argument);
    }

    void TestImmutableOperations() override
    {
        // Test immutable set
        Sequence<T> *newSeq = this->sequence->setImmutable(1, T(100));
        EXPECT_EQ(this->sequence->get(1), T(1)); // Original unchanged
        EXPECT_EQ(newSeq->get(1), T(100));       // New has change
        EXPECT_EQ(newSeq->getLength(), 3);       // Same length
        delete newSeq;

        // Test immutable append
        newSeq = this->sequence->appendImmutable(T(3));
        EXPECT_EQ(this->sequence->getLength(), 3); // Original unchanged
        EXPECT_EQ(newSeq->getLength(), 4);         // New has extra item
        EXPECT_EQ(newSeq->getLast(), T(3));
        delete newSeq;

        // Test immutable prepend
        newSeq = this->sequence->prependImmutable(T(-1));
        EXPECT_EQ(this->sequence->getLength(), 3); // Original unchanged
        EXPECT_EQ(newSeq->getLength(), 4);         // New has extra item
        EXPECT_EQ(newSeq->getFirst(), T(-1));
        delete newSeq;

        // Test immutable insert
        newSeq = this->sequence->insertAtImmutable(T(10), 1);
        EXPECT_EQ(this->sequence->getLength(), 3); // Original unchanged
        EXPECT_EQ(newSeq->getLength(), 4);         // New has extra item
        EXPECT_EQ(newSeq->get(1), T(10));
        delete newSeq;

        // Test immutable concat
        ArraySequence<T> other(2);
        other.set(0, T(50));
        other.set(1, T(60));
        newSeq = this->sequence->concatImmutable(&other);
        EXPECT_EQ(this->sequence->getLength(), 3); // Original unchanged
        EXPECT_EQ(newSeq->getLength(), 5);         // Combined length
        EXPECT_EQ(newSeq->get(3), T(50));
        EXPECT_EQ(newSeq->get(4), T(60));
        delete newSeq;
    }

    void TestOperators() override
    {
        ArraySequence<T> &seqRef = *dynamic_cast<ArraySequence<T> *>(this->sequence);

        // Test non-const operator[]
        seqRef[1] = T(100);
        EXPECT_EQ(seqRef.get(1), T(100));

        // Test const operator[]
        const ArraySequence<T> &constRef = seqRef;
        EXPECT_EQ(constRef[0], T(0));

        // Test out of bounds
        EXPECT_THROW(seqRef[-1], std::out_of_range);
        EXPECT_THROW(seqRef[3], std::out_of_range);
        EXPECT_THROW(constRef[-1], std::out_of_range);
        EXPECT_THROW(constRef[3], std::out_of_range);
    }
};