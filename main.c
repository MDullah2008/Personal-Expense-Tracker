#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 1000
#define FILENAME "expenses.dat"

// Define a struct to store expense details
typedef struct {
    char date[11];    // Format: YYYY-MM-DD
    char category[50];
    double amount;
} Expense;

// Global variables
Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function prototypes
void addExpense();
void viewExpenses();
void deleteExpense();
void generateReport();
void loadExpenses();
void saveExpenses();

int main() {
    int choice;

    // Load expenses from file
    loadExpenses();

    while (1) {
        printf("\nPersonal Expense Tracker\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Generate Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline left by scanf

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                deleteExpense();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                saveExpenses();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

// Function to add an expense
void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Error: Expense list is full.\n");
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", expenses[expenseCount].date);
    printf("Enter category: ");
    scanf("%49s", expenses[expenseCount].category);
    printf("Enter amount: ");
    scanf("%lf", &expenses[expenseCount].amount);

    expenseCount++;
    printf("Expense added successfully.\n");
}

// Function to view all expenses
void viewExpenses() {
    if (expenseCount == 0) {
        printf("No expenses to display.\n");
        return;
    }

    printf("\nExpenses:\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("%d. Date: %s, Category: %s, Amount: %.2f\n",
               i + 1, expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}

// Function to delete an expense by index
void deleteExpense() {
    int index;

    if (expenseCount == 0) {
        printf("No expenses to delete.\n");
        return;
    }

    viewExpenses();
    printf("Enter the number of the expense to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > expenseCount) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index - 1; i < expenseCount - 1; i++) {
        expenses[i] = expenses[i + 1];
    }

    expenseCount--;
    printf("Expense deleted successfully.\n");
}

// Function to generate a report of total expenses
void generateReport() {
    double total = 0.0;

    if (expenseCount == 0) {
        printf("No expenses to report.\n");
        return;
    }

    for (int i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
    }

    printf("Total expenses: %.2f\n", total);
}

// Function to load expenses from file
void loadExpenses() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        // File doesn't exist, no expenses to load
        return;
    }

    while (fscanf(file, "%10s %49s %lf", expenses[expenseCount].date, expenses[expenseCount].category, &expenses[expenseCount].amount) == 3) {
        expenseCount++;
        if (expenseCount >= MAX_EXPENSES) {
            break;
        }
    }

    fclose(file);
}

// Function to save expenses to file
void saveExpenses() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < expenseCount; i++) {
        fprintf(file, "%s %s %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }

    fclose(file);
}

