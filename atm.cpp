#include <iostream>
#include <string>
#include <iomanip>      // for setprecision
#include <sstream>      // for ostringstream
using namespace std;

class ATM {
private:
    int pin;                        // Stores user PIN
    float balance;                  // Stores account balance
    string transaction_history[100];  // Array for storing transaction logs
    int transaction_count = 0;        // Counter for transactions

    // Format float amount to string with 2 decimal places
    string format_amount(float amount) {
        ostringstream out;
        out << fixed << setprecision(2) << amount;
        return out.str();
    }

public:
    // Constructor initializes PIN and balance
    ATM(int userpin, float balance_amount) {
        pin = userpin;
        balance = balance_amount;
    }

    // Verify if entered PIN matches stored PIN
    bool authenticate(int entered_pin) {
        return (pin == entered_pin);
    }

    // Show current balance and record this action
    void check_balance() {
        cout << "The Current Balance amount in your account: Rs." << balance << endl;
        if (transaction_count < 100)
            transaction_history[transaction_count++] = "Checked balance";
    }

    // Deposit money if amount valid, update balance and record transaction
    void deposit(float deposit_amount) {
        if (deposit_amount > 0) {
            balance += deposit_amount;
            cout << "Successfully deposited Rs." << deposit_amount << endl;
            if (transaction_count < 100)
                transaction_history[transaction_count++] = "Deposited Rs." + format_amount(deposit_amount);
        } else {
            cout << "Invalid deposit amount entered!" << endl;
        }
    }

    // Withdraw money if valid and sufficient balance, update and record
    void withdraw(float withdraw_amount) {
        if (withdraw_amount <= 0) {
            cout << "Invalid withdrawal amount entered!" << endl;
        } else if (withdraw_amount > balance) {
            cout << "Insufficient Balance!" << endl;
        } else {
            balance -= withdraw_amount;
            cout << "Successfully withdrawn Rs." << withdraw_amount << endl;
            if (transaction_count < 100)
                transaction_history[transaction_count++] = "Withdrew Rs." + format_amount(withdraw_amount);
        }
    }

    // Print all stored transactions
    void show_transaction_history() {
        cout << "\n--- Transaction History ---" << endl;
        if (transaction_count == 0) {
            cout << "No transactions yet." << endl;
        } else {
            for (int i = 0; i < transaction_count; ++i) {
                cout << "- " << transaction_history[i] << endl;
            }
        }
    }
};

int main() {
    int pin = 12138;          // Predefined PIN for the ATM user
    float balance = 120000;   // Initial balance amount
    ATM atm(pin, balance);    // Create ATM object with PIN and balance
    int pin_input;
    int attempts = 0;

    cout << "\n----------WELCOME TO ATM INTERFACE!----------\n";

    // Allow up to 3 attempts for entering correct PIN
    cout << "ENTER THE PIN CODE: ";
    cin >> pin_input;

    while (!atm.authenticate(pin_input)) {
        attempts++;
        if (attempts >= 3) {
            cout << "Too many incorrect attempts. Access denied!" << endl;
            return 0;  // Exit if PIN entered incorrectly 3 times
        }
        cout << "Invalid pincode! Please try again: ";
        cin >> pin_input;
    }

    int choice;

    do {
        // Show menu options to the user
        cout << "\n----------MENU----------\n";
        cout << "1. CHECK THE ACCOUNT BALANCE\n";
        cout << "2. DEPOSIT AMOUNT\n";
        cout << "3. WITHDRAW AMOUNT\n";
        cout << "4. VIEW TRANSACTION HISTORY\n";
        cout << "5. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            atm.check_balance();
            break;

        case 2: {
            float d;
            cout << "Enter the amount to deposit: ";
            cin >> d;
            atm.deposit(d);
            break;
        }

        case 3: {
            float w;
            cout << "Enter the amount to withdraw: ";
            cin >> w;
            atm.withdraw(w);
            break;
        }

        case 4:
            atm.show_transaction_history();
            break;

        case 5:
            cout << "Thank you for using ATM!\n";
            break;

        default:
            cout << "Invalid Choice! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
