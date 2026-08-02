# C Doubly Linked List & String Utilities

A lightweight, self-contained C implementation of a doubly linked list supporting generic data types, accompanied by a custom string utility library. Designed for educational purposes, low-level programming practice, and exploring manual memory management in C.

## 📦 Features
- **Generic Doubly Linked List**: Stores arbitrary data via `void*` pointers
- **Core Operations**: Append, insert at index, delete at index, pop (tail removal), delete by value
- **Custom Comparators**: Value-based deletion using user-defined comparison functions
- **Recursive Design**: Traversal and modification implemented recursively for clean control flow
- **Standalone String Library**: Self-contained implementations of `strlen`, `strcpy`, and `strcmp`

## 🛠️ Build Instructions
This project uses CMake. Ensure you have a C compiler (GCC/Clang) and CMake installed.

```bash
# Create build directory and configure
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=<path/to/compiler> -S . -B ./build/

# Compile the project
cmake --build ./build/
