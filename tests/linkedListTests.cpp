#include <gtest/gtest.h>
#include "../inc/linkedList.hpp"

TEST(LinkedListTest, DefaultConstructor)
{
    LinkedList<int> list;
    EXPECT_EQ(list.getLength(), 0);
}

TEST(LinkedListTest, CountConstructor)
{
    LinkedList<int> list(5);
    EXPECT_EQ(list.getLength(), 5);
    EXPECT_THROW(LinkedList<int>(-1), std::invalid_argument);
}

TEST(LinkedListTest, ItemsArrayConstructor)
{
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    EXPECT_EQ(list.getLength(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

TEST(LinkedListTest, CopyConstructor)
{
    LinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    LinkedList<int> list2(list1);
    EXPECT_EQ(list2.getLength(), 2);
    EXPECT_EQ(list2.get(0), 1);
    EXPECT_EQ(list2.get(1), 2);
}

TEST(LinkedListTest, Append)
{
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    EXPECT_EQ(list.getLength(), 2);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
}

TEST(LinkedListTest, Prepend)
{
    LinkedList<int> list;
    list.prepend(1);
    list.prepend(2);
    EXPECT_EQ(list.getLength(), 2);
    EXPECT_EQ(list.get(0), 2);
    EXPECT_EQ(list.get(1), 1);
}

TEST(LinkedListTest, GetFirstLast)
{
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    EXPECT_EQ(list.getFirst(), 1);
    EXPECT_EQ(list.getLast(), 2);
    list.clear();
    EXPECT_THROW(list.getFirst(), std::out_of_range);
    EXPECT_THROW(list.getLast(), std::out_of_range);
}

TEST(LinkedListTest, GetSet)
{
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    EXPECT_EQ(list.get(1), 2);
    list.set(1, 3);
    EXPECT_EQ(list.get(1), 3);
    EXPECT_THROW(list.get(2), std::out_of_range);
    EXPECT_THROW(list.set(2, 0), std::out_of_range);
}

TEST(LinkedListTest, InsertAt)
{
    LinkedList<int> list;
    list.insertAt(1, 0);
    list.insertAt(3, 1);
    list.insertAt(2, 1);
    EXPECT_EQ(list.getLength(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
    EXPECT_THROW(list.insertAt(0, -1), std::out_of_range);
    EXPECT_THROW(list.insertAt(0, 5), std::out_of_range);
}

TEST(LinkedListTest, GetSubList)
{
    LinkedList<int> list;
    for (int i = 0; i < 5; i++)
        list.append(i);
    LinkedList<int> *sub = list.getSubList(1, 3);
    EXPECT_EQ(sub->getLength(), 3);
    EXPECT_EQ(sub->get(0), 1);
    EXPECT_EQ(sub->get(1), 2);
    EXPECT_EQ(sub->get(2), 3);
    delete sub;
    EXPECT_THROW(list.getSubList(-1, 3), std::out_of_range);
    EXPECT_THROW(list.getSubList(1, 5), std::out_of_range);
    EXPECT_THROW(list.getSubList(3, 1), std::out_of_range);
}

TEST(LinkedListTest, Concat)
{
    LinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    LinkedList<int> list2;
    list2.append(3);
    list2.append(4);
    LinkedList<int> *combined = list1.concat(&list2);
    EXPECT_EQ(combined->getLength(), 4);
    EXPECT_EQ(combined->get(0), 1);
    EXPECT_EQ(combined->get(3), 4);
    delete combined;
}

TEST(LinkedListTest, Clear)
{
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.clear();
    EXPECT_EQ(list.getLength(), 0);
}

TEST(LinkedListTest, OperatorBrackets)
{
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    list[1] = 3;
    EXPECT_EQ(list[1], 3);
    EXPECT_THROW(list[2], std::out_of_range);
}

TEST(LinkedListTest, AssignmentOperator)
{
    LinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    LinkedList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.getLength(), 2);
    EXPECT_EQ(list2.get(0), 1);
    EXPECT_EQ(list2.get(1), 2);
}