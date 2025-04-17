#pragma once
#include <gtest/gtest.h>
#include "../inc/linkedList.hpp"

template <typename T>
class LinkedListTest : public ::testing::Test
{
protected:
    LinkedList<T> *list;
    LinkedList<T> *emptyList;

    void SetUp() override
    {
        list = new LinkedList<T>(3);
        emptyList = new LinkedList<T>();

        // Initialize with values 0, 1, 2
        for (int i = 0; i < 3; i++)
        {
            list->set(i, T(i));
        }
    }

    void TearDown() override
    {
        delete list;
        delete emptyList;
    }
};

TYPED_TEST_SUITE_P(LinkedListTest);

TYPED_TEST_P(LinkedListTest, Constructors)
{
    // Test default constructor
    EXPECT_EQ(this->emptyList->getLength(), 0);

    // Test size constructor
    LinkedList<TypeParam> sized(5);
    EXPECT_EQ(sized.getLength(), 5);

    // Test items array constructor
    TypeParam items[] = {TypeParam(10), TypeParam(20), TypeParam(30)};
    LinkedList<TypeParam> fromItems(items, 3);
    EXPECT_EQ(fromItems.getLength(), 3);
    EXPECT_EQ(fromItems.get(0), TypeParam(10));
    EXPECT_EQ(fromItems.get(1), TypeParam(20));
    EXPECT_EQ(fromItems.get(2), TypeParam(30));

    // Test copy constructor
    LinkedList<TypeParam> copy(*this->list);
    EXPECT_EQ(copy.getLength(), 3);
    EXPECT_EQ(copy.get(0), TypeParam(0));
    EXPECT_EQ(copy.get(1), TypeParam(1));
    EXPECT_EQ(copy.get(2), TypeParam(2));
}

TYPED_TEST_P(LinkedListTest, Getters)
{
    // Test getFirst
    EXPECT_EQ(this->list->getFirst(), TypeParam(0));

    // Test getLast
    EXPECT_EQ(this->list->getLast(), TypeParam(2));

    // Test get
    EXPECT_EQ(this->list->get(0), TypeParam(0));
    EXPECT_EQ(this->list->get(1), TypeParam(1));
    EXPECT_EQ(this->list->get(2), TypeParam(2));

    // Test getLength
    EXPECT_EQ(this->list->getLength(), 3);
    EXPECT_EQ(this->emptyList->getLength(), 0);

    // Test out of bounds
    EXPECT_THROW(this->list->get(-1), std::out_of_range);
    EXPECT_THROW(this->list->get(3), std::out_of_range);
    EXPECT_THROW(this->emptyList->getFirst(), std::out_of_range);
    EXPECT_THROW(this->emptyList->getLast(), std::out_of_range);
}

TYPED_TEST_P(LinkedListTest, SubList)
{
    // Test valid sublist
    LinkedList<TypeParam> *sub = this->list->getSubList(1, 2);
    EXPECT_EQ(sub->getLength(), 2);
    EXPECT_EQ(sub->get(0), TypeParam(1));
    EXPECT_EQ(sub->get(1), TypeParam(2));
    delete sub;

    // Test full list
    sub = this->list->getSubList(0, 2);
    EXPECT_EQ(sub->getLength(), 3);
    delete sub;

    // Test single element
    sub = this->list->getSubList(1, 1);
    EXPECT_EQ(sub->getLength(), 1);
    EXPECT_EQ(sub->get(0), TypeParam(1));
    delete sub;

    // Test invalid ranges
    EXPECT_THROW(this->list->getSubList(-1, 2), std::out_of_range);
    EXPECT_THROW(this->list->getSubList(1, 3), std::out_of_range);
    EXPECT_THROW(this->list->getSubList(2, 1), std::out_of_range);
    EXPECT_THROW(this->emptyList->getSubList(0, 0), std::out_of_range);
}

TYPED_TEST_P(LinkedListTest, Modifiers)
{
    // Test append
    this->list->append(TypeParam(3));
    EXPECT_EQ(this->list->getLength(), 4);
    EXPECT_EQ(this->list->getLast(), TypeParam(3));

    // Test prepend
    this->list->prepend(TypeParam(-1));
    EXPECT_EQ(this->list->getLength(), 5);
    EXPECT_EQ(this->list->getFirst(), TypeParam(-1));

    // Test insertAt
    this->list->insertAt(TypeParam(10), 2);
    EXPECT_EQ(this->list->getLength(), 6);
    EXPECT_EQ(this->list->get(2), TypeParam(10));

    // Test set
    this->list->set(0, TypeParam(100));
    EXPECT_EQ(this->list->get(0), TypeParam(100));

    // Test concat
    LinkedList<TypeParam> other(2);
    other.set(0, TypeParam(50));
    other.set(1, TypeParam(60));
    LinkedList<TypeParam> *concated = this->list->concat(&other);
    EXPECT_EQ(concated->getLength(), 8);
    EXPECT_EQ(concated->get(6), TypeParam(50));
    EXPECT_EQ(concated->get(7), TypeParam(60));
    delete concated;

    // Test clear
    this->list->clear();
    EXPECT_EQ(this->list->getLength(), 0);

    // Test invalid modifications
    EXPECT_THROW(this->list->insertAt(TypeParam(0), -1), std::out_of_range);
    EXPECT_THROW(this->list->insertAt(TypeParam(0), 100), std::out_of_range);
    EXPECT_THROW(this->list->set(-1, TypeParam(0)), std::out_of_range);
    EXPECT_THROW(this->list->set(100, TypeParam(0)), std::out_of_range);
    EXPECT_THROW(this->list->concat(nullptr), std::invalid_argument);
}

TYPED_TEST_P(LinkedListTest, Operators)
{
    // Test non-const operator[]
    (*this->list)[1] = TypeParam(100);
    EXPECT_EQ(this->list->get(1), TypeParam(100));

    // Test const operator[]
    const LinkedList<TypeParam> &constRef = *this->list;
    EXPECT_EQ(constRef[0], TypeParam(0));

    // Test assignment operator
    LinkedList<TypeParam> assigned;
    assigned = *this->list;
    EXPECT_EQ(assigned.getLength(), 3);
    EXPECT_EQ(assigned.get(0), TypeParam(0));
    EXPECT_EQ(assigned.get(1), TypeParam(100));
    EXPECT_EQ(assigned.get(2), TypeParam(2));

    // Test self-assignment
    assigned = assigned;
    EXPECT_EQ(assigned.getLength(), 3);

    // Test out of bounds
    EXPECT_THROW((*this->list)[-1], std::out_of_range);
    EXPECT_THROW((*this->list)[3], std::out_of_range);
    EXPECT_THROW(constRef[-1], std::out_of_range);
    EXPECT_THROW(constRef[3], std::out_of_range);
}

REGISTER_TYPED_TEST_SUITE_P(LinkedListTest,
                            Constructors, Getters, SubList, Modifiers, Operators);