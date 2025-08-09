// This program reads in from the keyboard a record of financial information
// consisting of a person's name, income, rent, food costs, utilities and
// miscellaneous expenses. It then determines the net money
// (income minus all expenses)and places that information in a record
// which is then written to an output file. This program also records multiple...
// people's information as well. 

// Aditi Menon 

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int NAMESIZE = 20;

struct budget {
    char name[NAMESIZE + 1];
    float income;
    float rent;
    float food;
    float utilities;
    float miscell;
    float net;
};

int main() {
    fstream indata;
    ofstream outdata;

    indata.open("income.dat", ios::out | ios::binary);
    outdata.open("student.out");

    outdata << left << fixed << setprecision(2);

    char moreData = 'Y'; // Variable to control loop for inputting multiple records 
    budget person; 

    // While loop to allow repeated input for multiple persons 
    while (toupper(moreData) == 'Y') { // 'toupper' ensures user can enter lowercase 'y' or uppercase 'Y'
        cin.ignore(); // Clear the input buffer before taking string input 
        cout << "Enter the following information" << endl;
        cout << "Person's name: ";
        cin.getline(person.name, NAMESIZE);
        cout << "Income: ";
        cin >> person.income;
        cout << "Rent: ";
        cin >> person.rent;
        cout << "Food: ";
        cin >> person.food;
        cout << "Utilities: ";
        cin >> person.utilities;
        cout << "Miscellaneous: ";
        cin >> person.miscell;

        person.net = person.income - (person.rent + person.food + person.utilities + person.miscell);

        // write the 'person' structure to the binary file 
        indata.write(reinterpret_cast<char*>(&person), sizeof(person));

        // Prompt the user to enter another set of of data if they wish 
        cout << "Enter a Y if you would like to input more data ";
        cin >> moreData;
    }

    cout << "That's all the information" << endl;

    indata.close();

    // reopen the binary file for reading 
    indata.open("income.dat", ios::in | ios::binary);

    // Write the header for the output text file with formatted columns 
    outdata << setw(20) << "Name"
            << setw(10) << "Income"
            << setw(10) << "Rent"
            << setw(10) << "Food"
            << setw(15) << "Utilities"
            << setw(15) << "Miscellaneous"
            << setw(10) << "Net Money" << endl << endl;
    // while loop to read each record from the binary file and print formatted output 
    while (indata.read(reinterpret_cast<char*>(&person), sizeof(person))) {
        // Write the 'person' structure's data to the output file 
        outdata << setw(20) << person.name
                << setw(10) << person.income
                << setw(10) << person.rent
                << setw(10) << person.food
                << setw(15) << person.utilities
                << setw(15) << person.miscell
                << setw(10) << person.net << endl;
    }

    indata.close();
    outdata.close();

    return 0;
}