#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Constants
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define AUTH_TOKEN_LENGTH 20
#define MAX_MOVIES 100
#define MAX_TITLE_LENGTH 100
#define MAX_GENRE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_ROWS 10
#define MAX_COLS 10

// User structure
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Movie structure
typedef struct {
    char title[MAX_TITLE_LENGTH];
    char showtime[50];
    char genre[MAX_GENRE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} Movie;

// Seat structure
typedef struct {
    int row;
    int col;
    bool reserved;
} Seat;

// Reservation structure
struct MovieDetails {
    char name[20];
    unsigned int phone;
    int seat;
    int id;
    int totalPrice;
};

// Declare global variables
User users[MAX_USERS];
int user_count = 0;
Movie movies[MAX_MOVIES];
int movie_count = 0;
Seat seats[MAX_ROWS][MAX_COLS];
int count = 0;
struct MovieDetails person[300];

// Function prototypes
bool register_user(const char* username, const char* password);
bool authenticate_user(const char* username, const char* password, char* auth_token);
bool add_movie(const char* title, const char* showtime, const char* genre, const char* description);
void display_movies();
void initialize_seats();
bool is_seat_available(int row, int col);
bool reserve_seat(int row, int col);
bool cancel_seat_reservation(int row, int col);
void display_seat_availability();
int reservationChoice();
int changeName();
void reservation(char* auth_token, int selection);
void viewBookedDetails(struct MovieDetails person);
int orderFood(const char *food_choice);
void details();
int movieSelection();
void cancel(int selection);

int main() {
    // Register users
    register_user("user1", "password1");
    register_user("user2", "password2");

    // Add movies
    add_movie("Inception", "8:00 PM", "Science Fiction", "A thief who enters the dreams of others to steal their secrets from their subconscious.");
    add_movie("The Dark Knight", "7:30 PM", "Action", "When the menace known as The Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.");
    add_movie("Titanic", "9:00 PM", "Romance", "A seventeen-year-old aristocrat falls in love with a kind but poor artist aboard the luxurious, ill-fated R.M.S. Titanic.");

    // Initialize seats
    initialize_seats();

    // Attempt login
    char auth_token[AUTH_TOKEN_LENGTH];
    if (authenticate_user("user1", "password1", auth_token)) {
        printf("Authentication successful. Welcome!\n");

        // Display available movies
        display_movies();

        // Reserve seats
        reserve_seat(1, 2);
        reserve_seat(3, 4);

        // Reservation process
        int choice;
        do {
            choice = reservationChoice();
            switch (choice) {
                case 1:
                    changeName();
                    break;
                case 2:
                    details();
                    break;
                case 3: {
                    // Let the user select a movie
                    int movieSelectionResult = movieSelection();
                    reservation(auth_token, movieSelectionResult);
                    break;
                }
                case 4: {
                    // Let the user select a movie
                    int cancelSelectionResult = movieSelection();
                    cancel(cancelSelectionResult);
                    break;
                }
                case 5:
                    // Exit the program
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        } while (choice != 5);
    } else {
        printf("Authentication failed. Invalid credentials\n");
    }

    return 0;
}

// Authentication module
bool register_user(const char* username, const char* password) {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached\n");
        return false;
    }
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists\n");
            return false;
        }
    }
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    printf("User registered successfully\n");
    return true;
}

bool authenticate_user(const char* username, const char* password, char* auth_token) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            snprintf(auth_token, AUTH_TOKEN_LENGTH, "TOKEN_%d", i);
            printf("User authenticated successfully. Auth Token: %s\n", auth_token);
            return true;
        }
    }
    printf("Invalid credentials\n");
    return false;
}

// Movie module
bool add_movie(const char* title, const char* showtime, const char* genre, const char* description) {
    if (movie_count >= MAX_MOVIES) {
        printf("Maximum number of movies reached\n");
        return false;
    }
    strcpy(movies[movie_count].title, title);
    strcpy(movies[movie_count].showtime, showtime);
    strcpy(movies[movie_count].genre, genre);
    strcpy(movies[movie_count].description, description);
    movie_count++;
    printf("Movie added successfully\n");
    return true;
}

void display_movies() {
    printf("Available Movies:\n");
    for (int i = 0; i < movie_count; i++) {
        printf("Title: %s\n", movies[i].title);
        printf("Showtime: %s\n", movies[i].showtime);
        printf("Genre: %s\n", movies[i].genre);
        printf("Description: %s\n", movies[i].description);
        printf("\n");
    }
}

// Seats module
void initialize_seats() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            seats[i][j].row = i + 1;
            seats[i][j].col = j + 1;
            seats[i][j].reserved = false;
        }
    }
}

bool is_seat_available(int row, int col) {
    if (row >= 1 && row <= MAX_ROWS && col >= 1 && col <= MAX_COLS) {
        return !seats[row - 1][col - 1].reserved;
    }
    return false;
}

bool reserve_seat(int row, int col) {
    if (is_seat_available(row, col)) {
        seats[row - 1][col - 1].reserved = true;
        printf("Seat at row %d, column %d reserved successfully\n", row, col);
        return true;
    }
    else {
        printf("Seat at row %d, column %d is already reserved or invalid\n", row, col);
        return false;
    }
}

void display_seat_availability() {
    printf("Seat Availability:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c ", seats[i][j].reserved ? 'X' : 'O');
        }
        printf("\n");
    }
}

// Reservation module
int reservationChoice() {
    int choice;
    printf("Movie Ticket Booking System\n");
    printf("1- To edit the reservation name\n");
    printf("2- To view reserved tickets\n");
    printf("3- To purchase ticket\n");
    printf("4- To cancel the seat\n");
    printf("5- Exit system\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int changeName() {
    int bookingId;
    printf("Please enter your booking id: ");
    if (scanf("%d", &bookingId) != 1) {
        printf("Error: Invalid input. Please enter a valid booking ID.\n");
        while (getchar() != '\n');
        return 0;
    }

    char isFound = 'N';
    for(int i = 0; i < count; i++) {
        if(bookingId == person[i].id) {
            printf("Please enter your name: ");
            scanf(" %19[^\n]%*c", &person[i].name);
            printf("\n");
            printf("Name successfully Updated, Below are the new Booking details\n");
            viewBookedDetails(person[i]);
            isFound = 'Y';
            sleep(2);
            break;
        }
    }
    if(isFound != 'Y') {
        printf("\nNo Booking details found for the provided ID\n");
        sleep(2);
        return 0;
    }
    return 0;
}

void reservation(char* auth_token, int selection) {
    int i, j;
    char food_choice[4];
    char email[100];

    printf("Screen\n");
    for (i = 1; i <= 100; i++) {
        if (is_seat_available(selection, i))
            printf("%d\t", i);
        else
            printf("*\t");
        if (i % 10 == 0)
            printf("\n\n");
    }
    printf("Please enter your name: ");
    scanf(" %19[^\n]%*c", &person[count].name);
    printf("Please enter your email address: ");
    scanf("%99s", email);
    printf("Please enter your phone number: ");
    scanf("%u", &person[count].phone);
    printf("Which seat number you want? ");
    scanf("%d", &j);
    if (!is_seat_available(selection, j)) {
        printf("Sorry, this ticket is already booked! Please choose another seat.\n");
        return;
    } else
        seats[selection - 1][j - 1].reserved = true;
    person[count].seat = j;

    int totalFoodCost = orderFood(food_choice);
    int totalBill = 20 + totalFoodCost;
    person[count].totalPrice = totalBill;
    printf("Processing your payment...\n");
    for(int k=0;k<3;k++) {
        printf(".\n");
        sleep(1);
    }
    printf("Your payment has been processed\n");
    printf("Reservation details have been emailed to %s.\n", email);
    srand(time(NULL));
    int r = rand();
    person[count].id = r;
    viewBookedDetails(person[count]);
    sleep(2);
}

int orderFood(const char *food_choice) {
    int totalFood = 0;
    printf("Do you want to order food? (yes/no): ");
    scanf("%s", food_choice);
    if (strcmp(food_choice, "yes") == 0) {
        printf("Food Menu\n");
        printf("1. Popcorn - $15\n");
        printf("2. Soft Drink - $10\n");
        printf("3. Nachos - $20\n");
        printf("0 - End Order\n");
        int totalFoodItems = 3;
        int order[totalFoodItems];
        memset(order, 0, sizeof(order));
        printf("Enter the number corresponding to the food item you want to order:\n");
        int choice;
        while (1) {
            scanf("%d", &choice);
            if (choice == 0)
                break;
            if (choice < 1 || choice > totalFoodItems) {
                printf("Invalid choice. Please enter a valid option.\n");
                continue;
            }
            order[choice - 1]++;
        }
        printf("Your Food Order:\n");
        for (int i = 0; i < totalFoodItems; i++) {
            if (order[i] > 0) {
                printf("Quantity: %d, Item: %d, Price: $%d\n", order[i], i + 1, (i + 1) * order[i]);
                totalFood += (i + 1) * order[i];
            }
        }
        printf("Total Food Bill: $%d\n", totalFood);
    }
    return totalFood;
}

void details() {
    if (count == 0) {
        printf("No Booking details found\n");
        sleep(2);
        return;
    }
    printf("Reservation Details:\n");
    for (int i = 0; i < count; i++) {
        if (person[i].id > 0) {
            viewBookedDetails(person[i]);
        }
    }
    sleep(2);
}

int movieSelection() {
    int i;
    printf("Select A Movie\n");
    printf("Enter 1 for Inception\n");
    printf("Enter 2 for The Dark Knight\n");
    printf("Enter 3 for Titanic\n");
    printf("Enter your choice: ");
    scanf("%d", &i);
    return i;
}

void viewBookedDetails(struct MovieDetails person) {
    printf("\nBooking ID: %d\n", person.id);
    printf("Name: %s\n", person.name);
    printf("Phone: %u\n", person.phone);
    printf("Seat No: %d\n", person.seat);
    printf("Total Price: %d\n", person.totalPrice);
    printf("\n");
}

void cancel(int selection) {
    printf("Enter your Booking ID: ");
    int id;
    scanf("%d", &id);
    char confirmation;
    printf("Are you sure you want to cancel your reservation? (Y/N): ");
    scanf(" %c", &confirmation);
    if (confirmation == 'Y' || confirmation == 'y') {
        for (int i = 0; i < count; i++) {
            if (person[i].id == id) {
                person[i].id = -1;
                printf("Your reservation has been canceled successfully.\n");
                seats[selection - 1][person[i].seat - 1].reserved = false;
                return;
            }
        }
        printf("No reservation found with the provided ID.\n");
    } else if (confirmation == 'N' || confirmation == 'n') {
        printf("Reservation cancellation aborted.\n");
    } else {
        printf("Invalid choice.\n");
    }
}




_________________________________________________________________________________________________________________________________
