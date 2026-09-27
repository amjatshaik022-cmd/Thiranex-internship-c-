# Student Management System (C++)

A small console-based student record manager written in standard C++. It provides a menu for adding, updating, deleting, and displaying student records. Records are saved to `students.csv` in the current working directory and loaded again when the program starts.

## Features

- Add a student with a unique positive ID, name, course, and marks.
- Update a student's name, course, and marks by ID.
- Delete a student by ID.
- Display all saved students in a readable table.
- Keep records between runs using a plain-text CSV file.
- Validate IDs and marks (0–100); skip malformed rows when loading.

Names and courses cannot contain commas because the data file uses a simple CSV format.

## Project files

```text
student-management-system/
├── src/
│   └── main.cpp
├── .gitignore
└── README.md
```

## Requirements

- A C++17-compatible compiler, such as GCC, Clang, or Microsoft Visual C++.
- No third-party libraries are required.

## Compile and run

### GCC or Clang (Linux, macOS, or MinGW)

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o student_management
./student_management
```

### Microsoft Visual C++ (Developer Command Prompt)

From the project directory:

```bat
cl /std:c++17 /EHsc /W4 src\main.cpp /Fe:student_management.exe
student_management.exe
```

The program creates or updates `students.csv` beside the directory from which it is run. Keep that file to retain your records. It is ignored by Git by default so personal data is not uploaded accidentally.

## Upload to GitHub

1. Extract the ZIP file.
2. Create a new empty repository on GitHub.
3. Upload the contents of the `student-management-system` folder (including `src`, `.gitignore`, and this README) to the repository. Alternatively, use Git:

   ```bash
   git init
   git add README.md .gitignore src/main.cpp
   git commit -m "Add student management system"
   git branch -M main
   git remote add origin https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
   git push -u origin main
   ```

Replace the remote URL with your repository's URL. The sample student data file is intentionally excluded; users generate their own by running the program.

## Data format

Each line in `students.csv` stores `ID,Name,Course,Marks`, for example:

```text
101,Asha Kumar,Computer Science,92.50
```

## License

This project is provided for learning and educational use. Add a license file if you want to specify formal reuse terms.
