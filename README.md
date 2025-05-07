# Sequence Data Structure Library with Qt GUI

A C++ library that provides flexible sequence data structures with a Qt-based graphical user interface. The library supports both array-based and linked list-based sequences with immutable operations and type-safe value handling.

This project implements a comprehensive sequence management system that allows users to create, modify, and manipulate sequences through an intuitive graphical interface. It supports both integer and double value types, with operations including append, prepend, insert, and concatenate. The implementation follows the Model-View-Controller (MVC) pattern and provides both mutable and immutable sequence operations for robust data handling.

## Repository Structure
```
.
├── CMakeLists.txt              # CMake build configuration file
├── controllers/                # MVC Controllers
│   ├── MainController.cpp      # Core sequence management logic
│   └── MainController.h        # Controller interface definitions
├── models/                     # Data structure implementations
│   └── inc/
│       ├── arraySequence.hpp   # Array-based sequence implementation
│       ├── dynamicArray.hpp    # Dynamic array data structure
│       ├── linkedList.hpp      # Linked list data structure
│       ├── listSequence.hpp    # List-based sequence implementation
│       └── sequence.hpp        # Base sequence interface
├── views/                      # Qt GUI components
│   ├── createSequenceDialog.*  # Dialog for creating new sequences
│   ├── mainwindow.*           # Main application window
│   └── operationdialog.*      # Dialog for sequence operations
├── main.cpp                    # Application entry point
└── Sequence_ru_RU.ts          # Russian language translation file
```

## Usage Instructions
### Prerequisites
- C++17 compatible compiler
- Qt 5.x or Qt 6.x
- CMake 3.16 or higher
- Build tools (Make/Ninja)

For different platforms:
#### Linux
```bash
sudo apt-get install build-essential
sudo apt-get install qt6-base-dev
sudo apt-get install cmake
```

#### macOS
```bash
brew install qt
brew install cmake
```

#### Windows
- Install Qt using the official installer from Qt website
- Install Visual Studio with C++ development tools
- Install CMake

### Installation
1. Clone the repository:
```bash
git clone <repository-url>
cd sequence-library
```

2. Create build directory:
```bash
mkdir build && cd build
```

3. Configure and build:
```bash
cmake ..
cmake --build .
```

### Quick Start
1. Launch the application:
```bash
./Sequence
```

2. Create a new sequence:
- Click "Create Sequence"
- Enter sequence name
- Select sequence type (Array/List)
- Select value type (Int/Double)

3. Basic Operations:
```cpp
// Example: Creating and modifying a sequence
createSequence("mySequence", SequenceType::Array, ValueType::Int);
appendToSequence("mySequence", 42);
prependToSequence("mySequence", 10);
```

### More Detailed Examples
```cpp
// Creating an immutable copy with modifications
appendToImmutableSequence("original", 100, "newSequence");

// Concatenating sequences
concatImmutable("sequence1", "sequence2", "combinedSequence");

// Accessing elements
auto value = getFromSequence("mySequence", 0);
```

### Troubleshooting
Common issues and solutions:

1. Build Fails with Qt Not Found
- Ensure Qt is properly installed
- Set Qt_DIR environment variable
- Check CMake configuration

2. Runtime Errors
- Check sequence names for uniqueness
- Verify index bounds when accessing elements
- Enable debug logging:
```cpp
export QT_LOGGING_RULES="*.debug=true"
```

## Data Flow
The application follows a Model-View-Controller pattern for sequence management.

```ascii
[User Input] -> [View (Qt GUI)]
                     |
                     v
[MainController] <-> [Sequence Models]
         ^               |
         |               v
         +--- [Data Validation]
```

Component Interactions:
1. User interacts with Qt GUI components
2. MainController validates operations and manages sequences
3. Sequence models (Array/List) handle data storage
4. Views update to reflect sequence changes
5. Error handling propagates through controller to views