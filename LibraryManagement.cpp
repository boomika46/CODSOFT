#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// ---------------- BOOK ----------------
class Book {
public:
    string title, author, isbn;
    bool issued;
    string borrower;

    Book() {}

    Book(string t, string a, string i, bool is = false, string b = "")
        : title(t), author(a), isbn(i), issued(is), borrower(b) {}

    string toString() {
        return title + "|" + author + "|" + isbn + "|" +
               (issued ? "1" : "0") + "|" + borrower;
    }

    static Book fromString(string line) {
        stringstream ss(line);
        string t, a, i, is, b;

        getline(ss, t, '|');
        getline(ss, a, '|');
        getline(ss, i, '|');
        getline(ss, is, '|');
        getline(ss, b, '|');

        return Book(t, a, i, is == "1", b);
    }
};

// ---------------- LIBRARY ----------------
class Library {
private:
    vector<Book> books;
    string bookFile = "books.txt";
    string logFile = "transactions.txt";

public:
    Library() {
        loadBooks();
    }

    // -------- FILE HANDLING --------
    void saveBooks() {
        ofstream file(bookFile);
        for (auto &b : books)
            file << b.toString() << endl;
        file.close();
    }

    void loadBooks() {
        books.clear();
        ifstream file(bookFile);
        string line;

        while (getline(file, line)) {
            if (!line.empty())
                books.push_back(Book::fromString(line));
        }

        file.close();
    }

    void logTransaction(string msg) {
        ofstream file(logFile, ios::app);
        file << msg << endl;
        file.close();
    }

    // -------- ADD BOOK --------
    void addBook() {
        string t, a, i;

        cin.ignore();
        cout << "\nEnter Title: ";
        getline(cin, t);

        cout << "Enter Author: ";
        getline(cin, a);

        cout << "Enter ISBN: ";
        getline(cin, i);

        books.push_back(Book(t, a, i));
        saveBooks();

        cout << "✔ Book Added Successfully!\n";
    }

    // -------- DISPLAY --------
    void displayBooks() {
        cout << "\n----- BOOK LIST -----\n";

        for (auto &b : books) {
            cout << "Title   : " << b.title << endl;
            cout << "Author  : " << b.author << endl;
            cout << "ISBN    : " << b.isbn << endl;
            cout << "Status  : " << (b.issued ? "Issued to " + b.borrower : "Available") << endl;
            cout << "----------------------\n";
        }
    }

    // -------- SEARCH (PARTIAL MATCH) --------
    void searchBook() {
        string key;
        cin.ignore();

        cout << "\nEnter keyword: ";
        getline(cin, key);

        bool found = false;

        for (auto &b : books) {
            if (b.title.find(key) != string::npos ||
                b.author.find(key) != string::npos ||
                b.isbn.find(key) != string::npos) {

                cout << "\n✔ Found Book:\n";
                cout << "Title : " << b.title << endl;
                cout << "Author: " << b.author << endl;
                cout << "ISBN  : " << b.isbn << endl;
                cout << "Status: " << (b.issued ? "Issued" : "Available") << endl;

                found = true;
            }
        }

        if (!found)
            cout << "❌ No book found.\n";
    }

    // -------- ISSUE BOOK --------
    void issueBook() {
        string isbn, borrower;

        cout << "\nEnter ISBN: ";
        cin >> isbn;

        for (auto &b : books) {
            if (b.isbn == isbn) {
                if (b.issued) {
                    cout << "❌ Already issued.\n";
                    return;
                }

                cin.ignore();
                cout << "Enter borrower name: ";
                getline(cin, borrower);

                b.issued = true;
                b.borrower = borrower;

                saveBooks();

                logTransaction("ISSUE -> " + isbn + " to " + borrower);

                cout << "✔ Book Issued Successfully!\n";
                return;
            }
        }

        cout << "❌ Book not found.\n";
    }

    // -------- RETURN BOOK --------
    void returnBook() {
        string isbn;

        cout << "\nEnter ISBN: ";
        cin >> isbn;

        for (auto &b : books) {
            if (b.isbn == isbn) {
                if (!b.issued) {
                    cout << "❌ Book was not issued.\n";
                    return;
                }

                logTransaction("RETURN -> " + isbn + " from " + b.borrower);

                b.issued = false;
                b.borrower = "";

                saveBooks();

                cout << "✔ Book Returned Successfully!\n";
                return;
            }
        }

        cout << "❌ Book not found.\n";
    }

    // -------- TRANSACTION LOG --------
    void showLogs() {
        ifstream file(logFile);
        string line;

        cout << "\n----- TRANSACTION LOG -----\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

// ---------------- MAIN ----------------
int main() {
    Library lib;
    int choice;

    do {
        cout << "\n========= LIBRARY SYSTEM =========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. View Transactions\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: lib.addBook(); break;
        case 2: lib.displayBooks(); break;
        case 3: lib.searchBook(); break;
        case 4: lib.issueBook(); break;
        case 5: lib.returnBook(); break;
        case 6: lib.showLogs(); break;
        case 7: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}
