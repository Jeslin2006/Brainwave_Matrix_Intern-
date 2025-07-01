#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Account {
    string name;
    string pin;
    double balance = 0;
};

map<int, Account> accounts;
int accNumber = 1000;

bool login(int accNum, const string& pin) {
    return accounts.count(accNum) && accounts[accNum].pin == pin;
}

void createAccount() {
    Account acc;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, acc.name);
    cout << "Set a 4-digit PIN: ";
    cin >> acc.pin;

    accNumber++;
    accounts[accNumber] = acc;

    cout << "Account created successfully! Your Account Number: " << accNumber << "\n\n";
}

void deposit() {
    int accNum;
    string pin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;

    if (login(accNum, pin)) {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        accounts[accNum].balance += amount;
        cout << "Deposited successfully! New Balance: ₹" << accounts[accNum].balance << "\n\n";
    } else {
        cout << "Invalid credentials.\n\n";
    }
}

void withdraw() {
    int accNum;
    string pin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;

    if (login(accNum, pin)) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (amount <= accounts[accNum].balance) {
            accounts[accNum].balance -= amount;
            cout << "Withdrawal successful! New Balance: ₹" << accounts[accNum].balance << "\n\n";
        } else {
            cout << "Insufficient balance.\n\n";
        }
    } else {
        cout << "Invalid credentials.\n\n";
    }
}

void transfer() {
    int fromAcc, toAcc;
    string pin;
    double amount;

    cout << "Enter Your Account Number: ";
    cin >> fromAcc;
    cout << "Enter PIN: ";
    cin >> pin;

    if (!login(fromAcc, pin)) {
        cout << "Invalid credentials.\n\n";
        return;
    }

    cout << "Enter Recipient Account Number: ";
    cin >> toAcc;

    if (!accounts.count(toAcc)) {
        cout << "Recipient account doesn't exist.\n\n";
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if (amount <= accounts[fromAcc].balance) {
        accounts[fromAcc].balance -= amount;
        accounts[toAcc].balance += amount;
        cout << "Transferred successfully!\nYour New Balance: ₹" << accounts[fromAcc].balance << "\n\n";
    } else {
        cout << "Insufficient balance.\n\n";
    }
}

void checkBalance() {
    int accNum;
    string pin;

    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;

    if (login(accNum, pin)) {
        cout << "Hello, " << accounts[accNum].name << "! Your Balance is: ₹" << accounts[accNum].balance << "\n\n";
    } else {
        cout << "Invalid credentials.\n\n";
    }
}

int main() {
    int choice;

    do {
        cout << "=== Online Banking System ===\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Check Balance\n6. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: transfer(); break;
            case 5: checkBalance(); break;
            case 6: cout << "Thank you for using our bank!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
