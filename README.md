# C++ Sequence Data Structures

A C++ library implementing sequence data structures with both array-based and linked list-based implementations.

## Features
- Generic sequence interface with multiple implementations
- Array-based sequence using dynamic arrays
- Linked list-based sequence implementation
- Comprehensive unit testing using Google Test framework
- Support for both mutable and immutable operations

## Project Structure
```
.
├── inc/               # Header files
├── src/              # Source files
└── tests/            # Unit tests
```

## Building
This project uses CMake for building. To build:

```bash
mkdir build
cd build
cmake ..
make
```

## Testing
Tests are implemented using Google Test framework. To run the tests:
```bash
./tests
```

## Requirements
- C++14 or higher
- CMake 3.10 or higher
- Google Test framework