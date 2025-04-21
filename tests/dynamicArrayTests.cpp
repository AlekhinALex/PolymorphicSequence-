#include <gtest/gtest.h>
#include "../inc/dynamicArray.hpp"

TEST(DynamicArrayTest, DefaultConstructor)
{
    DynamicArray<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(DynamicArrayTest, SizeConstructor)
{
    DynamicArray<int> arr(5);
    EXPECT_EQ(arr.getSize(), 5);
}

TEST(DynamicArrayTest, ItemsArrayConstructor)
{
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_THROW(DynamicArray<int>(nullptr, 1), std::invalid_argument);
}

TEST(DynamicArrayTest, CopyConstructor)
{
    DynamicArray<int> arr1(2);
    arr1[0] = 1;
    arr1[1] = 2;
    DynamicArray<int> arr2(arr1);
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(DynamicArrayTest, GetFirstLast)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    EXPECT_EQ(arr.getFirst(), 1);
    EXPECT_EQ(arr.getLast(), 2);
    arr.clear();
    EXPECT_THROW(arr.getFirst(), std::out_of_range);
    EXPECT_THROW(arr.getLast(), std::out_of_range);
}

TEST(DynamicArrayTest, AppendPrepend)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    arr.prepend(0);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);
}

TEST(DynamicArrayTest, InsertAt)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(3);
    arr.insertAt(2, 1);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_THROW(arr.insertAt(0, -1), std::out_of_range);
    EXPECT_THROW(arr.insertAt(0, 5), std::out_of_range);
}

TEST(DynamicArrayTest, GetSubArray)
{
    DynamicArray<int> arr;
    for (int i = 0; i < 5; i++)
        arr.append(i);
    DynamicArray<int> *sub = arr.getSubArray(1, 3);
    EXPECT_EQ(sub->getSize(), 3);
    EXPECT_EQ((*sub)[0], 1);
    EXPECT_EQ((*sub)[1], 2);
    EXPECT_EQ((*sub)[2], 3);
    delete sub;
    EXPECT_THROW(arr.getSubArray(-1, 3), std::out_of_range);
    EXPECT_THROW(arr.getSubArray(1, 5), std::out_of_range);
    EXPECT_THROW(arr.getSubArray(3, 1), std::out_of_range);
}

TEST(DynamicArrayTest, Concat)
{
    DynamicArray<int> arr1;
    arr1.append(1);
    arr1.append(2);
    DynamicArray<int> arr2;
    arr2.append(3);
    arr2.append(4);
    DynamicArray<int> *combined = arr1.concat(&arr2);
    EXPECT_EQ(combined->getSize(), 4);
    EXPECT_EQ((*combined)[0], 1);
    EXPECT_EQ((*combined)[3], 4);
    EXPECT_THROW(arr1.concat(nullptr), std::invalid_argument);
}

TEST(DynamicArrayTest, Resize)
{
    DynamicArray<int> arr;
    arr.resize(5);
    EXPECT_EQ(arr.getSize(), 5);
    arr.resize(2);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_THROW(arr.resize(-1), std::invalid_argument);
}

TEST(DynamicArrayTest, Clear)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    arr.clear();
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(DynamicArrayTest, OperatorBrackets)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    arr[1] = 3;
    EXPECT_EQ(arr[1], 3);
    EXPECT_THROW(arr[2], std::out_of_range);
}

TEST(DynamicArrayTest, AssignmentOperator)
{
    DynamicArray<int> arr1;
    arr1.append(1);
    arr1.append(2);
    DynamicArray<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}