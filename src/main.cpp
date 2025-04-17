// tests/sequence_tests.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "../inc/dynamicArray.hpp"
#include "../inc/linkedList.hpp"
#include "../inc/arraySequence.hpp"
#include "../inc/listSequence.hpp"

int main()
{
    // Create initial sequence
    ArraySequence<int> *arrSeq = new ArraySequence<int>();
    Sequence<int> *seq = arrSeq->append(1)->append(2)->append(3)->append(4)->append(5);

    std::cout << "Original sequence: ";
    seq->print(); // Should print: 1 2 3 4 5
    std::cout << "\n";
    std::cout << "Subsequence (1,3): ";
    Sequence<int> *subSeq = seq->getSubsequence(1, 3);
    subSeq->print(); // Should print: 2 3 4

    // Cleanup
    delete arrSeq;
    delete seq;
    delete subSeq;
    return 0;
}
