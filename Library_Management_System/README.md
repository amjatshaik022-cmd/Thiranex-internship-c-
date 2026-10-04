# Library Management System

A simple console-based Library Management System developed in C++.

## Project Objective

To develop a Library Management System that efficiently manages books, members, and borrowing records using object-oriented/structured programming concepts.

## Features

- Add new books
- Add library members
- Display all books
- Display all members
- Issue books to members
- Return books
- Search books by title
- Search books by author
- Shows whether a book is available or issued
- Simple menu-driven interface

## Technologies Used

- C++
- Standard C++ Library
- `vector`
- Structures
- Functions
- File/console-based project structure

## Folder Structure

```text
Library_Management_System/
│
├── src/
│   └── main.cpp
│
├── README.md
└── .gitignore
```

## How to Run

### Using VS Code

1. Open the project folder in Visual Studio Code.
2. Open `src/main.cpp`.
3. Make sure a C++ compiler such as MinGW is installed.
4. Compile the program:

```bash
g++ src/main.cpp -o library
```

5. Run it:

Windows:
```bash
library.exe
```

Linux/macOS:
```bash
./library
```

## Main Menu

```text
1. Add Book
2. Add Member
3. Display Books
4. Display Members
5. Issue Book
6. Return Book
7. Search Book
8. Exit
```

## Example

Add a book:

```text
Book ID: 101
Title: The C++ Programming Language
Author: Bjarne Stroustrup
```

Add a member:

```text
Member ID: 1
Name: John
Phone: 9876543210
```

Then use **Issue Book** to issue the book to that member.

## Learning Outcomes

This project demonstrates:

- Structures in C++
- Vectors
- Functions
- Conditional statements
- Loops
- Searching using strings
- Basic record management
- Menu-driven programming

## Future Improvements

- Add file handling for permanent data storage
- Add login/admin authentication
- Add due dates and fine calculation
- Add book deletion and updating
- Add GUI/web interface
- Store records in a database

## Author

Mohammed Zaheed
