#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Book 
{
    int id;
    string title;
    string author;
};

const string FILE_NAME = "books.txt";

// Helper: print one book nicely
void printBook(const Book &b) {
    cout << "-----------------------------------\n";
    cout << "Book ID : " << b.id << "\n";
    cout << "Title   : " << b.title << "\n";
    cout << "Author  : " << b.author << "\n";
    cout << "-----------------------------------\n";
}

// Add Book
void addBook() {
    Book b;
    cout<<"\n=== Add New Book ===\n";
    cout<<"Enter Book ID: ";
    cin>>b.id;
    cin.ignore(); // clear newline
    cout<<"Enter Title: ";
    getline(cin, b.title);
    cout<<"Enter Author: ";
    getline(cin, b.author);

    ofstream fout(FILE_NAME, ios::app);
    if (!fout)
     {
        cout<<"Error: Cannot open file for writing.\n";
        return;
    }

    // Store each book on one line: id|title|author
    fout<<b.id<< '|' <<b.title<< '|' <<b.author<<'\n';
    fout.close();

    cout<<"Book added successfully.\n";
}

// Search Book By ID
void searchBookById() 
{
    cout<<"\n=== Search Book By ID ===\n";
    int searchId;
    cout<<"Enter Book ID to search: ";
    cin>>searchId;

    ifstream fin(FILE_NAME);
    if (!fin) 
    {
        cout<<"No data file found.\n";
        return;
    }

    bool found = false;
    Book b;
    string line;

    while (getline(fin, line)) 
    {
        if (line.empty()) continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        b.id = stoi(line.substr(0, p1));
        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.author = line.substr(p2 + 1);

        if (b.id == searchId) {
            cout << "\nBook found:\n";
            printBook(b);
            found = true;
            break;
        }
    }
    fin.close();

    if (!found) {
        cout << "No book with ID " << searchId << " found.\n";
    }
}

// Count Total Books
void countBooks() {
    cout << "\n=== Count Total Books ===\n";
    ifstream fin(FILE_NAME);
    if (!fin) {
        cout << "No data file found. Total books: 0\n";
        return;
    }

    int count = 0;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) count++;
    }
    fin.close();

    cout << "Total number of books: " << count << "\n";
}

// Delete Book (ID-Based)
void deleteBookById() {
    cout << "\n=== Delete Book By ID ===\n";
    int deleteId;
    cout << "Enter Book ID to delete: ";
    cin >> deleteId;

    ifstream fin(FILE_NAME);
    if (!fin) {
        cout << "No data file found.\n";
        return;
    }

    ofstream temp("temp.txt");
    if (!temp) {
        cout << "Error: Cannot open temporary file.\n";
        fin.close();
        return;
    }

    string line;
    bool deleted = false;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find('|');
        if (p1 == string::npos) {
            temp << line << "\n";
            continue;
        }

        int id = stoi(line.substr(0, p1));
        if (id == deleteId) {
            deleted = true; // skip writing this line
        } else {
            temp << line << "\n";
        }
    }

    fin.close();
    temp.close();

    // Replace old file with updated file
    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (deleted) {
        cout << "Book with ID " << deleteId << " deleted successfully.\n";
    } else {
        cout << "No book with ID " << deleteId << " found.\n";
    }
}

// Display All Books
void displayAllBooks() {
    cout << "\n=========== All Books ===========\n";
    ifstream fin(FILE_NAME);
    if (!fin) {
        cout << "No data file found.\n";
        return;
    }

    string line;
    int count = 0;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        Book b;
        b.id = stoi(line.substr(0, p1));
        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.author = line.substr(p2 + 1);

        printBook(b);
        count++;
    }
    fin.close();

    if (count == 0) {
        cout << "No books to display.\n";
    } else {
        cout << "Total books displayed: " << count << "\n";
    }
}

// Show Menu
void showMenu() {
    cout << "\n=================================\n";
    cout << "      Library Management System  \n";
    cout << "=================================\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book By ID\n";
    cout << "3. Count Books\n";
    cout << "4. Delete Book By ID\n";
    cout << "5. Display All Books\n";
    cout << "6. Exit\n";
    cout << "=================================\n";
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
                searchBookById();
                break;
            case 3:
                countBooks();
                break;
            case 4:
                deleteBookById();
                break;
            case 5:
                displayAllBooks();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
