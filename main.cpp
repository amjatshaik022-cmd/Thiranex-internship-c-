#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
    int issuedToMemberId;
};

struct Member {
    int id;
    string name;
    string phone;
};

vector<Book> books;
vector<Member> members;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addBook() {
    Book book;
    cout << "\nEnter Book ID: ";
    cin >> book.id;
    clearInput();

    cout << "Enter Book Title: ";
    getline(cin, book.title);

    cout << "Enter Author Name: ";
    getline(cin, book.author);

    book.issued = false;
    book.issuedToMemberId = -1;

    books.push_back(book);
    cout << "\nBook added successfully!\n";
}

void addMember() {
    Member member;
    cout << "\nEnter Member ID: ";
    cin >> member.id;
    clearInput();

    cout << "Enter Member Name: ";
    getline(cin, member.name);

    cout << "Enter Phone Number: ";
    getline(cin, member.phone);

    members.push_back(member);
    cout << "\nMember added successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\n========== BOOK LIST ==========\n";
    for (const auto& book : books) {
        cout << "ID: " << book.id << "\n";
        cout << "Title: " << book.title << "\n";
        cout << "Author: " << book.author << "\n";
        cout << "Status: " << (book.issued ? "Issued" : "Available") << "\n";
        if (book.issued) {
            cout << "Issued To Member ID: " << book.issuedToMemberId << "\n";
        }
        cout << "-------------------------------\n";
    }
}

void displayMembers() {
    if (members.empty()) {
        cout << "\nNo members registered.\n";
        return;
    }

    cout << "\n========== MEMBER LIST ==========\n";
    for (const auto& member : members) {
        cout << "ID: " << member.id << "\n";
        cout << "Name: " << member.name << "\n";
        cout << "Phone: " << member.phone << "\n";
        cout << "---------------------------------\n";
    }
}

void issueBook() {
    int bookId, memberId;

    cout << "\nEnter Book ID to issue: ";
    cin >> bookId;

    auto bookIt = find_if(books.begin(), books.end(),
        [bookId](const Book& book) { return book.id == bookId; });

    if (bookIt == books.end()) {
        cout << "Book not found.\n";
        return;
    }

    if (bookIt->issued) {
        cout << "Book is already issued.\n";
        return;
    }

    cout << "Enter Member ID: ";
    cin >> memberId;

    auto memberIt = find_if(members.begin(), members.end(),
        [memberId](const Member& member) { return member.id == memberId; });

    if (memberIt == members.end()) {
        cout << "Member not found.\n";
        return;
    }

    bookIt->issued = true;
    bookIt->issuedToMemberId = memberId;

    cout << "Book issued successfully to " << memberIt->name << ".\n";
}

void returnBook() {
    int bookId;

    cout << "\nEnter Book ID to return: ";
    cin >> bookId;

    auto bookIt = find_if(books.begin(), books.end(),
        [bookId](const Book& book) { return book.id == bookId; });

    if (bookIt == books.end()) {
        cout << "Book not found.\n";
        return;
    }

    if (!bookIt->issued) {
        cout << "This book is already available.\n";
        return;
    }

    bookIt->issued = false;
    bookIt->issuedToMemberId = -1;

    cout << "Book returned successfully.\n";
}

void searchBooks() {
    int choice;
    string keyword;

    clearInput();
    cout << "\nSearch by:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "Enter choice: ";
    cin >> choice;
    clearInput();

    cout << "Enter search keyword: ";
    getline(cin, keyword);

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    bool found = false;

    for (const auto& book : books) {
        string field = (choice == 1) ? book.title : book.author;
        string lowerField = field;
        transform(lowerField.begin(), lowerField.end(), lowerField.begin(), ::tolower);

        if (lowerField.find(lowerKeyword) != string::npos) {
            cout << "\nBook ID: " << book.id;
            cout << "\nTitle: " << book.title;
            cout << "\nAuthor: " << book.author;
            cout << "\nStatus: " << (book.issued ? "Issued" : "Available");
            cout << "\n-------------------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo matching books found.\n";
    }
}

void showMenu() {
    cout << "\n\n====================================\n";
    cout << "       LIBRARY MANAGEMENT SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Add Book\n";
    cout << "2. Add Member\n";
    cout << "3. Display Books\n";
    cout << "4. Display Members\n";
    cout << "5. Issue Book\n";
    cout << "6. Return Book\n";
    cout << "7. Search Book\n";
    cout << "8. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                addMember();
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                displayMembers();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                searchBooks();
                break;
            case 8:
                cout << "\nThank you for using the Library Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
