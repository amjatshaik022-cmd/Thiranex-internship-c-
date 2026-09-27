# Bank Management Application (C++)

A console-based banking demo that uses object-oriented C++ and file handling. It supports account creation, deposits, withdrawals, and balance inquiries. Account records are saved locally and loaded when the program starts.

## Features

- Create a customer account with a unique account number.
- Deposit money and view the updated balance.
- Withdraw money while preventing overdrafts.
- Check an account's balance.
- Persist account numbers, customer names, and balances in `accounts.txt`.
- Validate numeric input and reject non-positive transaction amounts.

## Project files

```text
bank-management-application/
├── src/
│   └── main.cpp
├── .gitignore
└── README.md
```

## Requirements

- A C++17-compatible compiler such as GCC, Clang, or Microsoft Visual C++.
- No third-party libraries are required.

## Compile and run

### GCC or Clang (Linux, macOS, or MinGW)

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o bank_management
./bank_management
```

### Microsoft Visual C++ (Developer Command Prompt)

From the project directory:

```bat
cl /std:c++17 /EHsc /W4 src\main.cpp /Fe:bank_management.exe
bank_management.exe
```

The app creates or updates `accounts.txt` in the current working directory. Keep this file if you want to retain your demo accounts. It is ignored by Git by default.

## Upload to GitHub

1. Extract the ZIP file.
2. Create a new empty repository on GitHub.
3. Upload the contents of the `bank-management-application` folder, or use Git:

   ```bash
   git init
   git add README.md .gitignore src/main.cpp
   git commit -m "Add bank management application"
   git branch -M main
   git remote add origin https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
   git push -u origin main
   ```

Replace the remote URL with your repository's URL. Account data is intentionally excluded from the repository.

## Important security note

This is an educational console demo, not production banking software. The local account file is plain text and the program has no authentication, encryption, audit trail, or real payment integration. Do not store real customer or financial data in it. The Git ignore rule prevents accidental commits in this project, but it does not encrypt data or protect the file on your computer.
