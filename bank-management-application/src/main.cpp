#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class BankAccount {
public:
    BankAccount() = default;
    BankAccount(long long number, std::string customer, double openingBalance)
        : number_(number), customer_(std::move(customer)), balance_(openingBalance) {}

    long long number() const { return number_; }
    const std::string& customer() const { return customer_; }
    double balance() const { return balance_; }

    bool deposit(double amount) {
        if (!std::isfinite(amount) || amount <= 0 || amount > 1'000'000'000.0) return false;
        balance_ += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (!std::isfinite(amount) || amount <= 0 || amount > balance_) return false;
        balance_ -= amount;
        return true;
    }

private:
    long long number_{};
    std::string customer_;
    double balance_{};
};

namespace {
const std::string DATA_FILE = "accounts.txt";

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    return value.substr(first, value.find_last_not_of(" \t\r\n") - first + 1);
}

std::string readText(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        value = trim(value);
        if (!value.empty()) return value;
        std::cout << "Please enter a value.\n";
    }
}

template <typename T>
T readNumber(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream input(line);
        T value{};
        char extra;
        if ((input >> value) && !(input >> extra)) return value;
        std::cout << "Please enter a valid number.\n";
    }
}

std::vector<BankAccount> loadAccounts() {
    std::vector<BankAccount> accounts;
    std::ifstream file(DATA_FILE);
    long long number;
    std::string customer;
    double balance;
    while (file >> number >> std::quoted(customer) >> balance) {
        if (number > 0 && balance >= 0)
            accounts.emplace_back(number, customer, balance);
    }
    return accounts;
}

bool saveAccounts(const std::vector<BankAccount>& accounts) {
    std::ofstream file(DATA_FILE, std::ios::trunc);
    if (!file) return false;
    file << std::fixed << std::setprecision(2);
    for (const auto& account : accounts)
        file << account.number() << ' ' << std::quoted(account.customer()) << ' '
             << account.balance() << '\n';
    return static_cast<bool>(file);
}

auto findAccount(std::vector<BankAccount>& accounts, long long number) {
    return std::find_if(accounts.begin(), accounts.end(), [number](const auto& account) {
        return account.number() == number;
    });
}

void createAccount(std::vector<BankAccount>& accounts) {
    const long long number = readNumber<long long>("New account number: ");
    if (number <= 0 || findAccount(accounts, number) != accounts.end()) {
        std::cout << "Use a unique account number greater than zero.\n";
        return;
    }
    const std::string name = readText("Customer name: ");
    accounts.emplace_back(number, name, 0.0);
    if (saveAccounts(accounts)) std::cout << "Account created with a zero balance.\n";
    else std::cout << "Could not save account data.\n";
}

void deposit(std::vector<BankAccount>& accounts) {
    const auto number = readNumber<long long>("Account number: ");
    auto account = findAccount(accounts, number);
    if (account == accounts.end()) { std::cout << "Account not found.\n"; return; }
    const double amount = readNumber<double>("Deposit amount: ");
    if (!account->deposit(amount)) { std::cout << "Enter an amount greater than zero.\n"; return; }
    if (saveAccounts(accounts)) std::cout << "Deposit recorded. New balance: $" << std::fixed << std::setprecision(2) << account->balance() << '\n';
    else std::cout << "Could not save account data.\n";
}

void withdraw(std::vector<BankAccount>& accounts) {
    const auto number = readNumber<long long>("Account number: ");
    auto account = findAccount(accounts, number);
    if (account == accounts.end()) { std::cout << "Account not found.\n"; return; }
    const double amount = readNumber<double>("Withdrawal amount: ");
    if (!account->withdraw(amount)) { std::cout << "Invalid amount or insufficient funds.\n"; return; }
    if (saveAccounts(accounts)) std::cout << "Withdrawal recorded. New balance: $" << std::fixed << std::setprecision(2) << account->balance() << '\n';
    else std::cout << "Could not save account data.\n";
}

void checkBalance(const std::vector<BankAccount>& accounts) {
    const auto number = readNumber<long long>("Account number: ");
    const auto account = std::find_if(accounts.begin(), accounts.end(), [number](const auto& item) {
        return item.number() == number;
    });
    if (account == accounts.end()) { std::cout << "Account not found.\n"; return; }
    std::cout << "Account: " << account->number() << " | Customer: " << account->customer()
              << " | Balance: $" << std::fixed << std::setprecision(2) << account->balance() << '\n';
}

void showMenu() {
    std::cout << "\n=== Bank Management Application ===\n"
              << "1. Create account\n2. Deposit\n3. Withdraw\n"
              << "4. Check balance\n5. Exit\n";
}
} // namespace

int main() {
    auto accounts = loadAccounts();
    std::cout << "Account data is stored in " << DATA_FILE << " in the current working directory.\n";
    while (true) {
        showMenu();
        switch (readNumber<int>("Choose an option: ")) {
            case 1: createAccount(accounts); break;
            case 2: deposit(accounts); break;
            case 3: withdraw(accounts); break;
            case 4: checkBalance(accounts); break;
            case 5: std::cout << "Goodbye!\n"; return 0;
            default: std::cout << "Choose an option from 1 to 5.\n";
        }
    }
}
