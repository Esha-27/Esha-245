#include <iostream>
#include <string>
using namespace std;

// Inner node: each expense
struct ExpenseNode {
    string item;
    float amount;
    ExpenseNode* next;

    ExpenseNode(string item, float amount) {
        this->item = item;
        this->amount = amount;
        next = nullptr;
    }
};

// Outer node: each month
struct MonthNode {
    string month;
    ExpenseNode* expenseHead;
    MonthNode* next;

    MonthNode(string month) {
        this->month = month;
        expenseHead = nullptr;
        next = nullptr;
    }
};

class ExpenseTracker {
private:
    MonthNode* head;

    MonthNode* findMonth(string month) {
        MonthNode* temp = head;
        while (temp) {
            if (temp->month == month)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

public:
    ExpenseTracker() {
        head = nullptr;
    }

    // Create or add expense
    void addExpense(string month, string item, float amount) {
        MonthNode* monthNode = findMonth(month);
        if (!monthNode) {
            monthNode = new MonthNode(month);
            monthNode->next = head;
            head = monthNode;
        }

        ExpenseNode* newExpense = new ExpenseNode(item, amount);
        newExpense->next = monthNode->expenseHead;
        monthNode->expenseHead = newExpense;

        cout << "Added expense: " << item << " in " << month << endl;
    }

    // Read/display all expenses
    void displayExpenses() {
        MonthNode* monthPtr = head;
        while (monthPtr) {
            cout << "\nMonth: " << monthPtr->month << endl;
            ExpenseNode* expPtr = monthPtr->expenseHead;
            if (!expPtr) {
                cout << "  No expenses.\n";
            }
            while (expPtr) {
                cout << "  " << expPtr->item << ": $" << expPtr->amount << endl;
                expPtr = expPtr->next;
            }
            monthPtr = monthPtr->next;
        }
    }

    // Update an expense
    void updateExpense(string month, string item, float newAmount) {
        MonthNode* monthNode = findMonth(month);
        if (!monthNode) {
            cout << "Month not found.\n";
            return;
        }

        ExpenseNode* temp = monthNode->expenseHead;
        while (temp) {
            if (temp->item == item) {
                temp->amount = newAmount;
                cout << "Updated " << item << " in " << month << " to $" << newAmount << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Expense item not found.\n";
    }

    // Delete an expense
    void deleteExpense(string month, string item) {
        MonthNode* monthNode = findMonth(month);
        if (!monthNode) {
            cout << "Month not found.\n";
            return;
        }

        ExpenseNode* curr = monthNode->expenseHead;
        ExpenseNode* prev = nullptr;

        while (curr) {
            if (curr->item == item) {
                if (prev) prev->next = curr->next;
                else monthNode->expenseHead = curr->next;

                delete curr;
                cout << "Deleted " << item << " from " << month << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Expense item not found.\n";
    }

    // Most expensive item in a month
    void mostExpensiveInMonth(string month) {
        MonthNode* monthNode = findMonth(month);
        if (!monthNode || !monthNode->expenseHead) {
            cout << "No expenses found for " << month << endl;
            return;
        }

        ExpenseNode* temp = monthNode->expenseHead;
        ExpenseNode* maxItem = temp;

        while (temp) {
            if (temp->amount > maxItem->amount) {
                maxItem = temp;
            }
            temp = temp->next;
        }

        cout << "Most expensive in " << month << ": " << maxItem->item << " ($" << maxItem->amount << ")" << endl;
    }
};
