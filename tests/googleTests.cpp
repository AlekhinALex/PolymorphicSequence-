#include <gtest/gtest.h>
#include "../inc/arraySequence.hpp"
#include "../inc/listSequence.hpp"
#include "../inc/dynamicArray.hpp"
#include "../inc/linkedList.hpp"

// Test fixture for sequences
template <typename T>
class SequenceTest : public testing::Test
{
protected:
    Sequence<T> *sequence;
    Sequence<T> *emptySequence;

    void TearDown() override
    {
        delete sequence;
        delete emptySequence;
    }
};

// ArraySequence test fixture
template <typename T>
class ArraySequenceTest : public SequenceTest<T>
{
protected:
    void SetUp() override
    {
        this->sequence = new ArraySequence<T>(3);
        this->emptySequence = new ArraySequence<T>();

        // Initialize sequence with values 0, 1, 2
        for (int i = 0; i < 3; i++)
        {
            dynamic_cast<ArraySequence<T> *>(this->sequence)->set(i, T(i));
        }
    }
};

// ListSequence test fixture
template <typename T>
class ListSequenceTest : public SequenceTest<T>
{
protected:
    void SetUp() override
    {
        this->sequence = new ListSequence<T>(3);
        this->emptySequence = new ListSequence<T>();

        // Initialize sequence with values 0, 1, 2
        for (int i = 0; i < 3; i++)
        {
            dynamic_cast<ListSequence<T> *>(this->sequence)->set(i, T(i));
        }
    }
};

// Define test cases
TYPED_TEST_SUITE_P(ArraySequenceTest);
TYPED_TEST_SUITE_P(ListSequenceTest);

// Test cases for both sequence types
TYPED_TEST_P(ArraySequenceTest, Construction)
{
    EXPECT_EQ(this->sequence->getLength(), 3);
    EXPECT_EQ(this->emptySequence->getLength(), 0);
}

TYPED_TEST_P(ArraySequenceTest, GetOperations)
{
    EXPECT_EQ(this->sequence->getFirst(), TypeParam(0));
    EXPECT_EQ(this->sequence->getLast(), TypeParam(2));
    EXPECT_EQ(this->sequence->get(1), TypeParam(1));
}

TYPED_TEST_P(ArraySequenceTest, MutableOperations)
{
    this->sequence->append(TypeParam(3));
    EXPECT_EQ(this->sequence->getLength(), 4);
    EXPECT_EQ(this->sequence->getLast(), TypeParam(3));

    this->sequence->prepend(TypeParam(-1));
    EXPECT_EQ(this->sequence->getLength(), 5);
    EXPECT_EQ(this->sequence->getFirst(), TypeParam(-1));
}

TYPED_TEST_P(ArraySequenceTest, ImmutableOperations)
{
    Sequence<TypeParam> *newSeq = this->sequence->appendImmutable(TypeParam(3));
    EXPECT_EQ(this->sequence->getLength(), 3); // Original unchanged
    EXPECT_EQ(newSeq->getLength(), 4);
    EXPECT_EQ(newSeq->getLast(), TypeParam(3));
    delete newSeq;
}

// Register ArraySequence tests
REGISTER_TYPED_TEST_SUITE_P(ArraySequenceTest,
                            Construction,
                            GetOperations,
                            MutableOperations,
                            ImmutableOperations);

// Similar tests for ListSequence
TYPED_TEST_P(ListSequenceTest, Construction)
{
    EXPECT_EQ(this->sequence->getLength(), 3);
    EXPECT_EQ(this->emptySequence->getLength(), 0);
}

// Add more ListSequence tests...

// Register ListSequence tests
REGISTER_TYPED_TEST_SUITE_P(ListSequenceTest,
                            Construction
                            // Add other test names
);

// Define types to test
typedef ::testing::Types<int, double> TestTypes;

// Instantiate test suites
INSTANTIATE_TYPED_TEST_SUITE_P(Numeric, ArraySequenceTest, TestTypes);
INSTANTIATE_TYPED_TEST_SUITE_P(Numeric, ListSequenceTest, TestTypes);

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
