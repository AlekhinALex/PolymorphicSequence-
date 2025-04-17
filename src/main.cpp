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
    Sequence<int> *seq = arrSeq;

    // Build sequence
    for (int i = 1; i <= 5; i++)
    {
        Sequence<int> *newSeq = seq->append(i);
        if (seq != arrSeq)
        { // Don't delete the original arrSeq
            delete seq;
        }
        seq = newSeq;
    }

    std::cout << "Original sequence: ";
    seq->print();

    std::cout << "\nSubsequence (1,3): ";
    Sequence<int> *subSeq = seq->getSubsequence(0, 3);
    subSeq->print();

    // Cleanup
    if (seq != arrSeq)
    {
        delete seq;
    }
    delete arrSeq;
    delete subSeq;

    return 0;
}
