#include <stdio.h>

#define MENU_SIZE 5

/* Display the available food items and their prices. */
void displayMenu(void) {
    printf("\n========== BARKADA BITES ==========\n");
    printf("1. Burger          - P50.00\n");
    printf("2. Fries           - P35.00\n");
    printf("3. Fried Chicken   - P85.00\n");
    printf("4. Spaghetti       - P60.00\n");
    printf("5. Soft Drink      - P25.00\n");
    printf("0. Finish order\n");
    printf("===================================\n");
}

/* Read an integer and reject non-numeric or out-of-range input. */
int getValidInteger(const char prompt[], int minimum, int maximum) {
    int value;
    int result;
    int ch;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == 1) {
            /* Remove any extra characters left on this input line. */
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard extra input. */
            }

            if (value >= minimum && value <= maximum) {
                return value;
            }

            printf("Please enter a number from %d to %d.\n", minimum, maximum);
        } else {
            /* Clear invalid input so the program can ask again. */
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard extra input. */
            }
            printf("Invalid input. Please enter a whole number.\n");
        }
    }
}

/* Print an itemized receipt and calculate the final bill. */
void displayReceipt(const int quantities[], const double prices[]) {
    const char *names[MENU_SIZE] = {
        "Burger", "Fries", "Fried Chicken", "Spaghetti", "Soft Drink"
    };
    int i;
    double total = 0.0;

    printf("\n============== RECEIPT ==============\n");
    printf("%-16s %5s %10s %10s\n", "Item", "Qty", "Price", "Subtotal");
    printf("-------------------------------------\n");

    for (i = 0; i < MENU_SIZE; i++) {
        if (quantities[i] > 0) {
            double subtotal = quantities[i] * prices[i];
            printf("%-16s %5d %9.2f %10.2f\n",
                   names[i], quantities[i], prices[i], subtotal);
            total += subtotal;
        }
    }

    printf("-------------------------------------\n");
    printf("TOTAL BILL: P%.2f\n", total);
    printf("Thank you for ordering at Barkada Bites!\n");
    printf("=====================================\n");
}

int main(void) {
    const double prices[MENU_SIZE] = {50.00, 35.00, 85.00, 60.00, 25.00};
    int quantities[MENU_SIZE] = {0, 0, 0, 0, 0};
    int choice;
    int quantity;
    char answer;
    int ch;

    printf("Welcome to Barkada Bites!\n");

    do {
        displayMenu();
        choice = getValidInteger("Choose an item (0-5): ", 0, MENU_SIZE);

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                printf("You selected Burger.\n");
                break;
            case 2:
                printf("You selected Fries.\n");
                break;
            case 3:
                printf("You selected Fried Chicken.\n");
                break;
            case 4:
                printf("You selected Spaghetti.\n");
                break;
            case 5:
                printf("You selected Soft Drink.\n");
                break;
            default:
                /* The input-validation function should prevent this case. */
                printf("Invalid selection.\n");
                continue;
        }

        quantity = getValidInteger("Enter quantity (1-100): ", 1, 100);
        quantities[choice - 1] += quantity;

        printf("Added %d item(s) to your order.\n", quantity);

        /* Ask whether the customer wants to order another item. */
        while (1) {
            printf("Would you like to order another item? (Y/N): ");

            if (scanf(" %c", &answer) == 1) {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    /* Discard extra input. */
                }

                if (answer == 'Y' || answer == 'y' ||
                    answer == 'N' || answer == 'n') {
                    break;
                }
            } else {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    /* Discard extra input. */
                }
            }

            printf("Please enter Y or N.\n");
        }

        if (answer == 'N' || answer == 'n') {
            break;
        }

    } while (1);

    displayReceipt(quantities, prices);
    return 0;
}
