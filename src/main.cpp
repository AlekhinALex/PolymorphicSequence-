// tests/data_structures_tests.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "../inc/dynamicArray.hpp"
#include "../inc/linkedList.hpp"
#include "../inc/arraySequence.hpp"
#include "../inc/listSequence.hpp"

class Tests
{
private:
    static void printTestName(const std::string &testName)
    {
        std::cout << "\n=== " << testName << " ===" << std::endl;
    }

    // DynamicArray Tests
    static void testDynamicArray()
    {
        printTestName("DynamicArray Tests");

        // Test default constructor
        DynamicArray<int> arr1;
        assert(arr1.getSize() == 0);

        // Test size constructor
        DynamicArray<int> arr2(5);
        assert(arr2.getSize() == 5);
        for (int i = 0; i < 5; i++)
        {
            assert(arr2.get(i) == 0);
        }

        // Test array constructor
        int items[] = {1, 2, 3, 4, 5};
        DynamicArray<int> arr3(items, 5);
        assert(arr3.getSize() == 5);
        for (int i = 0; i < 5; i++)
        {
            assert(arr3.get(i) == items[i]);
        }

        // Test copy constructor
        DynamicArray<int> arr4(arr3);
        assert(arr4.getSize() == arr3.getSize());
        for (int i = 0; i < arr3.getSize(); i++)
        {
            assert(arr4.get(i) == arr3.get(i));
        }

        // Test append and resize
        DynamicArray<int> arr5;
        for (int i = 0; i < 10; i++)
        {
            arr5.append(i);
            assert(arr5.getLast() == i);
        }
        assert(arr5.getSize() == 10);

        // Test prepend
        arr5.prepend(100);
        assert(arr5.getFirst() == 100);
        assert(arr5.getSize() == 11);

        // Test insertAt
        arr5.insertAt(200, 5);
        assert(arr5.get(5) == 200);

        // Test exceptions
        try
        {
            arr5.get(-1);
            assert(false); // Should not reach here
        }
        catch (const std::out_of_range &)
        {
        }

        try
        {
            arr5.insertAt(1, -1);
            assert(false);
        }
        catch (const std::out_of_range &)
        {
        }

        std::cout << "DynamicArray tests passed!" << std::endl;
    }

    // LinkedList Tests
    static void testLinkedList()
    {
        printTestName("LinkedList Tests");

        // Test default constructor
        LinkedList<int> list1;
        assert(list1.getLength() == 0);

        // Test array constructor
        int items[] = {1, 2, 3, 4, 5};
        LinkedList<int> list2(items, 5);
        assert(list2.getLength() == 5);
        for (int i = 0; i < 5; i++)
        {
            assert(list2.get(i) == items[i]);
        }

        // Test copy constructor
        LinkedList<int> list3(list2);
        assert(list3.getLength() == list2.getLength());
        for (int i = 0; i < list2.getLength(); i++)
        {
            assert(list3.get(i) == list2.get(i));
        }

        // Test append and prepend
        LinkedList<int> list4;
        list4.append(1);
        list4.append(2);
        list4.prepend(0);
        assert(list4.getFirst() == 0);
        assert(list4.getLast() == 2);
        assert(list4.getLength() == 3);

        // Test insertAt
        list4.insertAt(100, 1);
        assert(list4.get(1) == 100);

        // Test sublist
        LinkedList<int> *subList = list4.getSubList(1, 2);
        assert(subList->getLength() == 2);
        assert(subList->getFirst() == 100);
        delete subList;

        std::cout << "LinkedList tests passed!" << std::endl;
    }

    // Sequence Tests
    static void testSequences()
    {
        printTestName("Sequence Tests");

        // Test ArraySequence
        ArraySequence<int> arrSeq;
        arrSeq.append(1);
        arrSeq.append(2);
        arrSeq.append(3);
        arrSeq.print();
        std::cout << "\n";
        assert(arrSeq.getLength() == 3);
        assert(arrSeq.getFirst() == 1);
        assert(arrSeq.getLast() == 3);

        // Test ListSequence
        ListSequence<int> listSeq;
        listSeq.append(1);
        listSeq.append(2);
        listSeq.append(3);
        assert(listSeq.getLength() == 3);
        assert(listSeq.getFirst() == 1);
        assert(listSeq.getLast() == 3);

        // Test concatenation
        Sequence<int> *concat1 = arrSeq.concat(&listSeq);
        assert(concat1->getLength() == 6);
        assert(concat1->getFirst() == 1);
        assert(concat1->getLast() == 3);
        delete concat1;

        // Test subsequence
        Sequence<int> *sub1 = arrSeq.getSubsequence(0, 1);
        assert(sub1->getLength() == 2);
        assert(sub1->getFirst() == 1);
        assert(sub1->getLast() == 2);
        delete sub1;

        std::cout << "Sequence tests passed!" << std::endl;
    }

    // Stress Tests
    static void stressTests()
    {
        printTestName("Stress Tests");

        // DynamicArray stress test
        DynamicArray<int> bigArray;
        for (int i = 0; i < 10000; i++)
        {
            bigArray.append(i);
        }
        assert(bigArray.getSize() == 10000);

        // LinkedList stress test
        LinkedList<int> bigList;
        for (int i = 0; i < 10000; i++)
        {
            bigList.append(i);
        }
        assert(bigList.getLength() == 10000);

        std::cout << "Stress tests passed!" << std::endl;
    }

public:
    static void runAllTests()
    {
        std::cout << "Starting all tests..." << std::endl;

        testDynamicArray();
        testLinkedList();
        testSequences();
        stressTests();

        std::cout << "\nAll tests completed successfully!" << std::endl;
    }
};

int main()
{
    try
    {
        Tests::runAllTests();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
