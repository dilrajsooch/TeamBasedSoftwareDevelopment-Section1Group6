#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // for isalpha

// Constants
#define MAX_MOVIES 3
#define MAX_SEATS_PER_MOVIE 100
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 100
#define MAX_FOOD_ITEMS 3

// Structure for a food item
typedef struct {
    char name[20];
    int price;
    int quantity; // New field for quantity ordered
} FoodItem;

// Structure for a reservation
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    unsigned int phone;
    int seat_number;
    int movie_index;
    int total_price;
    FoodItem food_items[MAX_FOOD_ITEMS]; // Array to store food items ordered
} Reservation;

// Global variables
Reservation reservations[MAX_MOVIES][MAX_SEATS_PER_MOVIE];
int reservation_count[MAX_MOVIES] = {0}; // Initialize counts for each movie to 0
FoodItem food_menu[MAX_FOOD_ITEMS] = {
        {"Popcorn", 15, 0},    // Initialize quantity ordered to 0 for all food items
        {"Soft Drink", 10, 0},
        {"Nachos", 20, 0}
};

// Function prototypes
void display_menu();
void make_reservation();
void edit_reservation();
void cancel_reservation();
void view_reservations();
int order_food();
void process_payment(int total_cost, Reservation reservation);
void print_reservation_details(Reservation reservation);
bool validate_email(const char *email);
bool validate_phone(unsigned int phone);

// Movies
const char *movies[MAX_MOVIES] = {"Inception", "The Dark Knight", "Titanic"};

int main() {
    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                make_reservation();
                break;
            case 2:
                edit_reservation();
                break;
            case 3:
                cancel_reservation();
                break;
            case 4:
                view_reservations();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}

void display_menu() {
    printf("\nMovie Ticket Booking System\n");
    printf("1. Make a reservation\n");
    printf("2. Edit a reservation\n");
    printf("3. Cancel a reservation\n");
    printf("4. View reservations\n");
    printf("5. Exit\n");
}

void make_reservation() {
    int movie_choice;
    printf("Select a movie (or 0 to go back):\n");
    for (int i = 0; i < MAX_MOVIES; ++i) {
        printf("%d. %s\n", i + 1, movies[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &movie_choice);
    if (movie_choice == 0)
        return; // Go back to main menu
    if (movie_choice < 1 || movie_choice > MAX_MOVIES) {
        printf("Invalid movie choice.\n");
        return;
    }

    int seat_number;
    printf("Enter desired seat number (1 - %d) (or 0 to go back): ", MAX_SEATS_PER_MOVIE);
    scanf("%d", &seat_number);
    if (seat_number == 0)
        return; // Go back to main menu
    if (seat_number < 1 || seat_number > MAX_SEATS_PER_MOVIE) {
        printf("Invalid seat number.\n");
        return;
    }

    if (reservations[movie_choice - 1][seat_number - 1].id != 0) {
        printf("Seat already reserved.\n");
        return;
    }

    Reservation new_reservation;
    new_reservation.id = rand(); // Generate a random ID (not ideal but simple for this example)

    // Input name (only letters)
    printf("Enter your name (or 0 to go back): ");
    scanf("%s", new_reservation.name);
    if (strcmp(new_reservation.name, "0") == 0)
        return; // Go back to main menu
    for (int i = 0; new_reservation.name[i] != '\0'; ++i) {
        if (!isalpha(new_reservation.name[i])) {
            printf("Invalid name. Name should only contain letters.\n");
            return;
        }
    }

    // Input email (must contain '@' symbol)
    printf("Enter your email (or 0 to go back): ");
    scanf("%s", new_reservation.email);
    if (strcmp(new_reservation.email, "0") == 0)
        return; // Go back to main menu
    char *at_symbol = strchr(new_reservation.email, '@');
    if (at_symbol == NULL) {
        printf("Invalid email address. Email must contain '@' symbol.\n");
        return;
    }

    // Input phone number (exactly 10 digits)
    printf("Enter your phone number (10 digits) (or 0 to go back): ");
    unsigned long long temp_phone;
    if (scanf("%llu", &temp_phone) != 1) {
        printf("Invalid phone number. Please enter only digits.\n");
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    // Validate phone number length
    if (temp_phone < 1000000000LL || temp_phone > 9999999999LL) {
        printf("Invalid phone number length. Phone number must be exactly 10 digits.\n");
        return;
    }

    new_reservation.phone = temp_phone;

    new_reservation.seat_number = seat_number;
    new_reservation.movie_index = movie_choice - 1;
    new_reservation.total_price = 0; // Placeholder for now

    // Order food and calculate total price
    int food_cost = order_food();
    int ticket_price = 10; // Ticket price is $10
    new_reservation.total_price = food_cost + ticket_price;

    reservations[movie_choice - 1][seat_number - 1] = new_reservation;
    reservation_count[movie_choice - 1]++;
    printf("Reservation successful!\n");

    process_payment(new_reservation.total_price, new_reservation);
}

void edit_reservation() {
    int reservation_id;
    printf("Enter the reservation ID to edit: ");
    scanf("%d", &reservation_id);
    bool found = false;
    for (int i = 0; i < MAX_MOVIES; ++i) {
        for (int j = 0; j < MAX_SEATS_PER_MOVIE; ++j) {
            if (reservations[i][j].id == reservation_id) {
                printf("Reservation found:\n");
                print_reservation_details(reservations[i][j]);
                printf("Enter new name: ");
                scanf("%s", reservations[i][j].name);
                // Email input validation loop
                do {
                    printf("Enter new email: ");
                    scanf("%s", reservations[i][j].email);
                    if (!validate_email(reservations[i][j].email)) {
                        printf("Invalid email format. Please include the '@' symbol.\n");
                    } else {
                        break;
                    }
                } while (1);
                printf("Enter new phone number (10 digits): ");
                scanf("%u", &reservations[i][j].phone);
                printf("Reservation updated successfully!\n");
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    if (!found)
        printf("Reservation with ID %d not found.\n", reservation_id);
}

void cancel_reservation() {
    int reservation_id;
    printf("Enter the reservation ID to cancel: ");
    scanf("%d", &reservation_id);
    bool found = false;
    for (int i = 0; i < MAX_MOVIES; ++i) {
        for (int j = 0; j < MAX_SEATS_PER_MOVIE; ++j) {
            if (reservations[i][j].id == reservation_id) {
                reservations[i][j].id = 0;
                reservation_count[i]--;
                printf("Reservation canceled successfully!\n");
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    if (!found)
        printf("Reservation with ID %d not found.\n", reservation_id);
}

void view_reservations() {
    printf("\nReservations:\n");
    for (int i = 0; i < MAX_MOVIES; ++i) {
        printf("%s:\n", movies[i]);
        for (int j = 0; j < MAX_SEATS_PER_MOVIE; ++j) {
            if (reservations[i][j].id != 0) {
                printf("Reservation ID: %d, Name: %s, Email: %s, Phone: %u, Seat Number: %d\n",
                       reservations[i][j].id, reservations[i][j].name, reservations[i][j].email,
                       reservations[i][j].phone, reservations[i][j].seat_number);
            }
        }
        printf("\n");
    }
}

int order_food() {
    int total_cost = 0;
    printf("\nFood Menu:\n");
    for (int i = 0; i < MAX_FOOD_ITEMS; ++i) {
        printf("%d. %s - $%d\n", i + 1, food_menu[i].name, food_menu[i].price);
    }
    printf("Enter the number corresponding to the food item you want to order (0 to end): ");
    int choice;
    scanf("%d", &choice);
    while (choice != 0) {
        if (choice < 1 || choice > MAX_FOOD_ITEMS) {
            printf("Invalid choice.\n");
        } else {
            // Increment quantity ordered
            food_menu[choice - 1].quantity++;
            // Update total cost
            total_cost += food_menu[choice - 1].price;
        }
        printf("Enter the number corresponding to the next food item you want to order (0 to end): ");
        scanf("%d", &choice);
    }
    return total_cost;
}

void process_payment(int total_cost, Reservation reservation) {
    printf("Total Cost (including ticket): $%d\n", total_cost);

    int payment_option;
    do {
        printf("How would you like to pay?\n");
        printf("1. Cash\n");
        printf("2. Credit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &payment_option) != 1 || (payment_option != 1 && payment_option != 2)) {
            printf("Invalid payment option. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    } while (1);

    printf("Processing payment...\n");

    // Introducing a delay to simulate processing time


    printf("Payment successful!\n");

    // Display reservation details
    printf("\nReservation Details:\n");
    print_reservation_details(reservation);
}
void print_reservation_details(Reservation reservation) {
    printf("========================================\n");
    printf("            Movie Ticket                \n");
    printf("========================================\n");
    printf("Reservation ID: %d\n", reservation.id);
    printf("Movie: %s\n", movies[reservation.movie_index]);
    printf("Seat Number: %d\n", reservation.seat_number);
    printf("Name: %s\n", reservation.name);
    printf("Email: %s\n", reservation.email);
    printf("Phone: %010u\n", reservation.phone);
    printf("----------------------------------------\n");
    printf("     Total Price (including ticket): $%d\n", reservation.total_price);
    printf("========================================\n");
}

bool validate_email(const char *email) {
    // Ensure that the email contains the "@" symbol
    return strchr(email, '@') != NULL;
}

bool validate_phone(unsigned int phone) {
    // Check if phone number has exactly 10 digits
    int count = 0;
    while (phone != 0) {
        phone /= 10;
        count++;
    }
    return count == 10;
}
