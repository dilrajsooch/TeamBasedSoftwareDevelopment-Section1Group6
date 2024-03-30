#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <time.h> // for srand

// Constants
#define MAX_MOVIES 3
#define MAX_SEATS_PER_MOVIE 100
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 100
#define MAX_FOOD_ITEMS 3

// Structure for a reservation
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    unsigned int phone;
    int seat_number;
    int movie_index;
    int total_price;
} Reservation;

// Structure for a food item
typedef struct {
    char name[20];
    int price;
} FoodItem;

// Global variables
Reservation reservations[MAX_MOVIES][MAX_SEATS_PER_MOVIE];
int reservation_count[MAX_MOVIES] = {0}; // Initialize counts for each movie to 0
FoodItem food_menu[MAX_FOOD_ITEMS] = {
        {"Popcorn", 15},
        {"Soft Drink", 10},
        {"Nachos", 20}
};

// Function prototypes
void display_menu();
void make_reservation();
void edit_reservation();
void cancel_reservation();
void view_reservations();
int order_food();
void print_reservation_details(Reservation reservation);

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
    printf("Select a movie:\n");
    for (int i = 0; i < MAX_MOVIES; ++i) {
        printf("%d. %s\n", i + 1, movies[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &movie_choice);
    if (movie_choice < 1 || movie_choice > MAX_MOVIES) {
        printf("Invalid movie choice.\n");
        return;
    }

    int seat_number;
    printf("Enter desired seat number (1 - %d): ", MAX_SEATS_PER_MOVIE);
    scanf("%d", &seat_number);
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
    printf("Enter your name: ");
    scanf("%s", new_reservation.name);
    printf("Enter your email: ");
    scanf("%s", new_reservation.email);
    printf("Enter your phone number: ");
    scanf("%u", &new_reservation.phone);
    new_reservation.seat_number = seat_number;
    new_reservation.movie_index = movie_choice - 1;
    new_reservation.total_price = 0; // Placeholder for now

    reservations[movie_choice - 1][seat_number - 1] = new_reservation;
    reservation_count[movie_choice - 1]++;
    printf("Reservation successful!\n");
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
                printf("Enter new email: ");
                scanf("%s", reservations[i][j].email);
                printf("Enter new phone number: ");
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
            total_cost += food_menu[choice - 1].price;
        }
        printf("Enter the number corresponding to the next food item you want to order (0 to end): ");
        scanf("%d", &choice);
    }
    return total_cost;
}

void print_reservation_details(Reservation reservation) {
    printf("Reservation ID: %d\n", reservation.id);
    printf("Name: %s\n", reservation.name);
    printf("Email: %s\n", reservation.email);
    printf("Phone: %u\n", reservation.phone);
    printf("Seat Number: %d\n", reservation.seat_number);
}



_________________________________________________________________________________________________________________________________
