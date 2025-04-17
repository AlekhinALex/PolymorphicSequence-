#pragma once
#include <gtest/gtest.h>
#include "../inc/dynamicArray.hpp"

template <typename T>
class DynamicArrayTest : public ::testing::Test
{
protected:
    DynamicArray<T> *array;
    DynamicArray<T> *emptyArray;

    void SetUp() override
    {
        array = new DynamicArray<T>(3);
        emptyArray = new DynamicArray<T>();

        // Initialize with values 0, 1, 2
        for (int i = 0; i < 3; i++)
        {
            array->set(i, T(i));
        }
    }

    void TearDown() override
    {
        delete array;
        delete emptyArray;
    }
};

TYPED_TEST_SUITE_P(DynamicArrayTest);

TYPED_TEST_P(DynamicArrayTest, Constructors)
{
    // Test default constructor
    EXPECT_EQ(this->emptyArray->getSize(), 0);

    // Test size constructor
    DynamicArray<TypeParam> sized(5);
    EXPECT_EQ(sized.getSize(), 5);

    // Test items array constructor
    TypeParam items[] = {TypeParam(10), TypeParam(20), TypeParam(30)};
    DynamicArray<TypeParam> fromItems(items, 3);
    EXPECT_EQ(fromItems.getSize(), 3);
    EXPECT_EQ(fromItems.get(0), TypeParam(10));
    EXPECT_EQ(fromItems.get(1), TypeParam(20));
    EXPECT_EQ(fromItems.get(2), TypeParam(30));

    // Test copy constructor
    DynamicArray<TypeParam> copy(*this->array);
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.get(0), TypeParam(0));
    EXPECT_EQ(copy.get(1), TypeParam(1));
    EXPECT_EQ(copy.get(2), TypeParam(2));
}

TYPED_TEST_P(DynamicArrayTest, Getters)
{
    // Test getFirst
    EXPECT_EQ(this->array->getFirst(), TypeParam(0));

    // Test getLast
    EXPECT_EQ(this->array->getLast(), TypeParam(2));

    // Test get
    EXPECT_EQ(this->array->get(0), TypeParam(0));
    EXPECT_EQ(this->array->get(1), TypeParam(1));
    EXPECT_EQ(this->array->get(2), TypeParam(2));

    // Test getSize
    EXPECT_EQ(this->array->getSize(), 3);
    EXPECT_EQ(this->emptyArray->getSize(), 0);

    // Test getData
    TypeParam *data = this->array->getData();
    EXPECT_EQ(data[0], TypeParam(0));
    EXPECT_EQ(data[1], TypeParam(1));
    EXPECT_EQ(data[2], TypeParam(2));

    // Test out of bounds
    EXPECT_THROW(this->array->get(-1), std::out_of_range);
    EXPECT_THROW(this->array->get(3), std::out_of_range);
    EXPECT_THROW(this->emptyArray->getFirst(), std::out_of_range);
    EXPECT_THROW(this->emptyArray->getLast(), std::out_of_range);
}

TYPED_TEST_P(DynamicArrayTest, SubArray)
{
    // Test valid subarray
    DynamicArray<TypeParam> *sub = this->array->getSubArray(1, 2);
    EXPECT_EQ(sub->getSize(), 2);
    EXPECT_EQ(sub->get(0), TypeParam(1));
    EXPECT_EQ(sub->get(1), TypeParam(2));
    delete sub;

    // Test full array
    sub = this->array->getSubArray(0, 2);
    EXPECT_EQ(sub->getSize(), 3);
    delete sub;

    // Test single element
    sub = this->array->getSubArray(1, 1);
    EXPECT_EQ(sub->getSize(), 1);
    EXPECT_EQ(sub->get(0), TypeParam(1));
    delete sub;

    // Test invalid ranges
    EXPECT_THROW(this->array->getSubArray(-1, 2), std::out_of_range);
    EXPECT_THROW(this->array->getSubArray(1, 3), std::out_of_range);
    EXPECT_THROW(this->array->getSubArray(2, 1), std::out_of_range);
    EXPECT_THROW(this->emptyArray->getSubArray(0, 0), std::out_of_range);
}

TYPED_TEST_P(DynamicArrayTest, Modifiers)
{
    // Test append
    this->array->append(TypeParam(3));
    EXPECT_EQ(this->array->getSize(), 4);
    EXPECT_EQ(this->array->getLast(), TypeParam(3));

    // Test prepend
    this->array->prepend(TypeParam(-1));
    EXPECT_EQ(this->array->getSize(), 5);
    EXPECT_EQ(this->array->getFirst(), TypeParam(-1));

    // Test insertAt
    this->array->insertAt(TypeParam(10), 2);
    EXPECT_EQ(this->array->getSize(), 6);
    EXPECT_EQ(this->array->get(2), TypeParam(10));

    // Test set
    this->array->set(0, TypeParam(100));
    EXPECT_EQ(this->array->get(0), TypeParam(100));

    // Test resize
    this->array->resize(8);
    EXPECT_EQ(this->array->getSize(), 8);

    // Test concat
    DynamicArray<TypeParam> other(2);
    other.set(0, TypeParam(50));
    other.set(1, TypeParam(60));
    DynamicArray<TypeParam> *concated = this->array->concat(&other);
    EXPECT_EQ(concated->getSize(), 10);
    EXPECT_EQ(concated->get(8), TypeParam(50));
    EXPECT_EQ(concated->get(9), TypeParam(60));
    delete concated;

    // Test clear
    this->array->clear();
    EXPECT_EQ(this->array->getSize(), 0);

    // Test invalid modifications
    EXPECT_THROW(this->array->insertAt(TypeParam(0), -1), std::out_of_range);
    EXPECT_THROW(this->array->insertAt(TypeParam(0), 100), std::out_of_range);
    EXPECT_THROW(this->array->set(-1, TypeParam(0)), std::out_of_range);
    EXPECT_THROW(this->array->set(100, TypeParam(0)), std::out_of_range);
    EXPECT_THROW(this->array->resize(-1), std::invalid_argument);
    EXPECT_THROW(this->array->concat(nullptr), std::invalid_argument);
}

TYPED_TEST_P(DynamicArrayTest, Operators)
{
    // Test non-const operator[]
    (*this->array)[1] = TypeParam(100);
    EXPECT_EQ(this->array->get(1), TypeParam(100));

    // Test const operator[]
    const DynamicArray<TypeParam> &constRef = *this->array;
    EXPECT_EQ(constRef[0], TypeParam(0));

    // Test assignment operator
    DynamicArray<TypeParam> assigned;
    assigned = *this->array;
    EXPECT_EQ(assigned.getSize(), 3);
    EXPECT_EQ(assigned.get(0), TypeParam(0));
    EXPECT_EQ(assigned.get(1), TypeParam(100));
    EXPECT_EQ(assigned.get(2), TypeParam(2));

    // Test self-assignment
    assigned = assigned;
    EXPECT_EQ(assigned.getSize(), 3);

    // Test out of bounds
    EXPECT_THROW((*this->array)[-1], std::out_of_range);
    EXPECT_THROW((*this->array)[3], std::out_of_range);
    EXPECT_THROW(constRef[-1], std::out_of_range);
    EXPECT_THROW(constRef[3], std::out_of_range);
}

REGISTER_TYPED_TEST_SUITE_P(DynamicArrayTest,
                            Constructors, Getters, SubArray, Modifiers, Operators);