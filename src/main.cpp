#include <cassert>
#include <iostream>
#include "../inc/listSequence.hpp"

void testListSequenceConstructors()
{
    std::cout << "Testing constructors..." << std::endl;

    // Default constructor
    ListSequence<int> seq1;
    assert(seq1.getLength() == 0);

    // Array constructor
    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq2(arr, 5);
    assert(seq2.getLength() == 5);
    assert(seq2.getFirst() == 1);
    assert(seq2.getLast() == 5);

    // Count constructor
    ListSequence<int> seq3(3);
    assert(seq3.getLength() == 3);

    // Copy constructor from LinkedList
    LinkedList<int> list(arr, 5);
    ListSequence<int> seq4(list);
    assert(seq4.getLength() == 5);
    assert(seq4.getFirst() == 1);
    assert(seq4.getLast() == 5);

    std::cout << "Constructor tests passed!" << std::endl;
}

void testBasicOperations()
{
    std::cout << "Testing basic operations..." << std::endl;

    int arr[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(arr, 5);

    // Test getFirst, getLast
    assert(seq.getFirst() == 1);
    assert(seq.getLast() == 5);

    // Test get and operator[]
    assert(seq.get(2) == 3);
    assert(seq[2] == 3);

    // Test getLength
    assert(seq.getLength() == 5);

    std::cout << "Basic operations tests passed!" << std::endl;
}

void testModificationOperations()
{
    std::cout << "Testing modification operations..." << std::endl;

    ListSequence<int> seq;

    // Test append
    Sequence<int> *seq1 = seq.append(1);
    assert(seq1->getLength() == 1);
    assert(seq1->getFirst() == 1);

    // Test prepend
    Sequence<int> *seq2 = seq1->prepend(0);
    assert(seq2->getLength() == 2);
    assert(seq2->getFirst() == 0);
    assert(seq2->getLast() == 1);

    // Test insertAt
    Sequence<int> *seq3 = seq2->insertAt(5, 1);
    assert(seq3->getLength() == 3);
    assert(seq3->get(1) == 5);

    // Test set
    Sequence<int> *seq4 = seq3->set(1, 10);
    assert(seq4->get(1) == 10);

    // Cleanup
    delete seq1;
    delete seq2;
    delete seq3;
    delete seq4;

    std::cout << "Modification operations tests passed!" << std::endl;
}

void testImmutableOperations()
{
    std::cout << "Testing immutable operations..." << std::endl;

    int arr[] = {1, 2, 3};
    ListSequence<int> seq(arr, 3);

    // Test setImmutable
    Sequence<int> *seq1 = seq.setImmutable(1, 10);
    assert(seq1->get(1) == 10);
    assert(seq.get(1) == 2); // Original unchanged

    // Test appendImmutable
    Sequence<int> *seq2 = seq.appendImmutable(4);
    assert(seq2->getLength() == 4);
    assert(seq2->getLast() == 4);
    assert(seq.getLength() == 3); // Original unchanged

    // Test prependImmutable
    Sequence<int> *seq3 = seq.prependImmutable(0);
    assert(seq3->getLength() == 4);
    assert(seq3->getFirst() == 0);
    assert(seq.getLength() == 3); // Original unchanged

    // Cleanup
    delete seq1;
    delete seq2;
    delete seq3;

    std::cout << "Immutable operations tests passed!" << std::endl;
}

void testSubsequenceAndConcat()
{
    std::cout << "Testing subsequence and concatenation..." << std::endl;

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8};
    ListSequence<int> seq1(arr1, 5);
    ListSequence<int> seq2(arr2, 3);

    // Test getSubsequence
    Sequence<int> *sub = seq1.getSubsequence(1, 3);
    assert(sub->getLength() == 3);
    assert(sub->getFirst() == 2);
    assert(sub->getLast() == 4);

    // Test concat
    Sequence<int> *concat = seq1.concat(&seq2);
    assert(concat->getLength() == 8);
    assert(concat->getFirst() == 1);
    assert(concat->getLast() == 8);

    // Test concatImmutable
    Sequence<int> *concatImm = seq1.concatImmutable(&seq2);
    assert(concatImm->getLength() == 8);
    assert(seq1.getLength() == 5); // Original unchanged

    // Cleanup
    delete sub;
    delete concat;
    delete concatImm;

    std::cout << "Subsequence and concatenation tests passed!" << std::endl;
}

void testExceptionHandling()
{
    std::cout << "Testing exception handling..." << std::endl;

    ListSequence<int> seq;

    // Test out of range access
    try
    {
        seq.get(0);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &)
    {
        // Expected
    }

    // Test invalid subsequence range
    try
    {
        seq.getSubsequence(-1, 1);
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range &)
    {
        // Expected
    }

    // Test null concatenation
    try
    {
        seq.concat(nullptr);
        assert(false); // Should not reach here
    }
    catch (const std::invalid_argument &)
    {
        // Expected
    }

    std::cout << "Exception handling tests passed!" << std::endl;
}

int main()
{
    try
    {
        testListSequenceConstructors();
        testBasicOperations();
        testModificationOperations();
        testImmutableOperations();
        testSubsequenceAndConcat();
        testExceptionHandling();

        std::cout << "\nAll tests passed successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
