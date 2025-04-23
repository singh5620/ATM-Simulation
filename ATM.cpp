#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Account {
    int accountNumber;
    int pin;
    float balance;
};

vector<Account> loadAccounts(string filename) {
    vector<Account> accounts;
    ifstream file(filename);
    Account acc;
    while (file >> acc.accountNumber >> acc.pin >> acc.balance) {
        accounts.push_back(acc);
    }
    file.close();
    return accounts;
}

void saveAccounts(string filename, vector<Account> &accounts) {
    ofstream file(filename);
    for (auto acc : accounts) {
        file << acc.accountNumber << " " << acc.pin << " " << acc.balance << endl;
    }
    file.close();
}

int findAccount(vector<Account> &accounts, int accNo, int pin) {
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == accNo && accounts[i].pin == pin) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Account> accounts = loadAccounts("accounts.txt");

    int accNo, pin, attempts = 0;
    int index = -1;

    while (attempts < 3) {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;
        index = findAccount(accounts, accNo, pin);
        if (index != -1) break;
        cout << "Invalid credentials. Try again.\n";
        attempts++;
    }

    if (index == -1) {
        cout << "Too many failed attempts. Exiting.\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n--- ATM Menu ---\n";
        cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Change PIN\n5. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        float amount;
        switch (choice) {
            case 1:
                cout << "Balance: ₹" << accounts[index].balance << endl;
                break;
            case 2:
                cout << "Amount to deposit: ";
                cin >> amount;
                accounts[index].balance += amount;
                cout << "Deposited successfully.\n";
                break;
            case 3:
                cout << "Amount to withdraw: ";
                cin >> amount;
                if (amount <= accounts[index].balance) {
                    accounts[index].balance -= amount;
                    cout << "Withdrawn successfully.\n";
                } else {
                    cout << "Insufficient balance.\n";
                }
                break;
            case 4:
                int newPin;
                cout << "Enter new PIN: ";
                cin >> newPin;
                accounts[index].pin = newPin;
                cout << "PIN updated successfully.\n";
                break;
            case 5:
                cout << "Thanks for using the ATM.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 5);

    saveAccounts("accounts.txt", accounts);
    return 0;
}