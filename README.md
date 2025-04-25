# Sequence Manager

A Qt-based application for managing and manipulating sequences of integers, supporting both array-based and linked list-based implementations.

## Features

- Create and manage multiple sequences (Array or List based)
- Perform operations on sequences:
  - Append elements
  - Prepend elements
  - Insert at specific positions
  - Set values at specific indices
  - Get values from specific indices
- View sequence contents
- Delete sequences
- Russian language support

## Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler
- Qt6 or Qt5 (with Widgets and LinguistTools components)

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Configure with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

## Project Structure

```
.
├── CMakeLists.txt
├── controllers/
│   ├── MainController.cpp
│   └── MainController.h
├── models/
│   ├── inc/
│   │   ├── arraySequence.hpp
│   │   ├── dynamicArray.hpp
│   │   ├── linkedList.hpp
│   │   ├── listSequence.hpp
│   │   └── sequence.hpp
│   └── SequenceManagerModel.hpp
├── views/
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── createSequenceDialog.cpp
│   ├── createSequenceDialog.h
│   ├── operationdialog.cpp
│   └── operationdialog.h
└── Sequence_ru_RU.ts
```

## Components

- **Models**: Contains the core sequence data structures
  - `arraySequence`: Array-based sequence implementation
  - `listSequence`: Linked list-based sequence implementation
  - `sequence`: Base sequence interface
  - `dynamicArray`: Dynamic array implementation
  - `linkedList`: Linked list implementation

- **Controllers**: 
  - `MainController`: Manages sequence operations and coordinates between views and models

- **Views**:
  - `MainWindow`: Main application window
  - `OperationDialog`: Dialog for sequence operations

## Internationalization

The application includes Russian language support through the `Sequence_ru_RU.ts` translation file.
