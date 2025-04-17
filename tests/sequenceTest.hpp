#pragma once
#include <gtest/gtest.h>
#include "../inc/arraySequence.hpp"
#include "../inc/listSequence.hpp"

template <typename T>
class SequenceTest : public ::testing::Test
{
protected:
    Sequence<T> *sequence;
    Sequence<T> *emptySequence;

    virtual void SetUp()
    {
        // To be implemented by derived classes
    }

    virtual void TearDown()
    {
        delete sequence;
        delete emptySequence;
    }

    void TestAll()
    {
        TestConstructors();
        TestGetters();
        TestSubsequence();
        TestModifiers();
        TestImmutableOperations();
        TestOperators();
    }

    virtual void TestConstructors() = 0;
    virtual void TestGetters() = 0;
    virtual void TestSubsequence() = 0;
    virtual void TestModifiers() = 0;
    virtual void TestImmutableOperations() = 0;
    virtual void TestOperators() = 0;
};