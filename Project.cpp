#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

struct Book
{
    int ID;
    string title;
    string author;
};

const string FILE_NAME = "books.txt";  //const for keeping the file name constant.

//Function to add Book:

void addBook()
{
    Book b;
    cout<<"Enter Book ID: ";
    cin>>b.ID;
    cin.ignore(); // to ignore the newline character after integer input
    cout<<"Enter Book Title: ";
    getline(cin, b.title);
    cout<<"Enter Book Author: ";
    getline(cin, b.author);

    ofstream fout(FILE_NAME, ios::app);
    fout<<b.ID<<"|"<<b.title<<"|"<<b.author<<endl;
    fout.close();
    cout<<"\nBook added successfully!\n"<<endl;

}


//Function to display all Books:
void displayBooks()
{
    ifstream fin(FILE_NAME);
    if (!fin)
    {
        cout<<"No books found!"<<endl;
        return;
    }
    string line;
    while (getline(fin, line))
        {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            string id = line.substr(0, pos1);
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string author = line.substr(pos2 + 1);
            cout << "ID: " << id << "| Title: " << title << "| Author: " << author << endl;
        }
    fin.close();
}

//Search Book by ID
void searchBook()
{
    int searchID;
    cout<<"Enter Book ID to search: ";
    cin>>searchID;

    ifstream fin(FILE_NAME);
    string line;
    bool found = false;

    while(getline(fin, line))
    {
        int first = line.find(',');
        int second = line.find(',', first + 1);

        int id = stoi(line.substr(0, first));
        string title = line.substr(first + 1, second - first - 1);
        string author = line.substr(second + 1);

        if (id == searchID)
        {
            cout<<"Book Found: "<<endl;
            cout<<"Book ID: "<<id<<"\n";
            cout<<"Title: "<<title<<"\n";
            cout<<"Author: "<<author<<"\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout<<"\n Book with ID "<<searchID<<" not found."<<endl;
    fin.close();
}

//Count Total Books:

void countBooks()
{
    ifstream fin(FILE_NAME);
    int count = 0;
    string line;

    while(getline(fin, line))
    {
        count++;
    }
    cout<<"\nTotal number of books: "<<count<<endl;
    fin.close();
    
}

//Delete Book by ID:

void deleteBook()
{
    int delID;
    cout << "\nEnter Book ID to delete: ";
    cin >> delID;

    ifstream fin(FILE_NAME);
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(fin, line)) {
        int first = line.find(',');
        int id = stoi(line.substr(0, first));

        if (id != delID) {
            temp << line << "\n";
        } else {
            found = true;
        }
    }

    fin.close();
    temp.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found)
        cout << "\n Book Deleted Successfully!\n";
    else
        cout << "\n Book ID Not Found.\n";
}

//Menu:

int main()
{
    int choice;
    do
    {
        cout<<"\n==================================================\n";
        cout<<"\n============= Book Management System =============\n";
        cout<<"\n==================================================\n";
        cout<<"1. Add Book\n";
        cout<<"2. Display All Books\n";
        cout<<"3. Search Book by ID\n";
        cout<<"4. Count Total Books\n";
        cout<<"5. Delete Book by ID\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                countBooks();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                cout<<"Exiting the program."<<endl;
                break;
            default:
                cout<<"Invalid choice! Please try again."<<endl;
        }
    } while(choice != 6);

    return 0;
}