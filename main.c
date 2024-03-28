//Navneet and Tiljeet please post your modules here
//authentication module (Navneet)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constants
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define AUTH_TOKEN_LENGTH 20

// User structure
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Array to store registered users
User users[MAX_USERS];
int user_count = 0;

// Function to register a new user
bool register_user(const char* username, const char* password) {
    // Check if user count exceeds maximum
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached\n");
        return false;
    }

    // Check if username already exists
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists\n");
            return false;
        }
    }

    // Add new user
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    user_count++;
    printf("User registered successfully\n");
    return true;
}

// Function to authenticate user and generate authentication token
bool authenticate_user(const char* username, const char* password, char* auth_token) {
    // Search for user
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            // Generate authentication token (dummy implementation)
            snprintf(auth_token, AUTH_TOKEN_LENGTH, "TOKEN_%d", i);
            printf("User authenticated successfully. Auth Token: %s\n", auth_token);
            return true;
        }
    }
    printf("Invalid credentials\n");
    return false;
}

// Sample function in another module that requires authentication
void reservation_function(const char* auth_token) {
    // Dummy implementation to demonstrate authentication check
    if (strstr(auth_token, "TOKEN_") == auth_token) {
        printf("Reservation function accessed with valid authentication token\n");
    }
    else {
        printf("Reservation function access denied. Invalid authentication token\n");
    }
}

int main() {
    // Register some users
    register_user("user1", "password1");
    register_user("user2", "password2");

    // Attempt login
    char auth_token[AUTH_TOKEN_LENGTH];
    if (authenticate_user("user1", "password1", auth_token)) {
        // Call reservation function with authentication token
        reservation_function(auth_token);
    }

    return 0;
}
____________________________________________________________________________________________________________________________
//movie module (Navneet)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants
#define MAX_MOVIES 100
#define MAX_TITLE_LENGTH 100
#define MAX_GENRE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200

// Structure to hold movie information
typedef struct {
    char title[MAX_TITLE_LENGTH];
    char showtime[50];
    char genre[MAX_GENRE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} Movie;

// Array to store movies
Movie movies[MAX_MOVIES];
int movie_count = 0;

// Function to add a new movie
bool add_movie(const char* title, const char* showtime, const char* genre, const char* description) {
    // Check if movie count exceeds maximum
    if (movie_count >= MAX_MOVIES) {
        printf("Maximum number of movies reached\n");
        return false;
    }

    // Add new movie
    strcpy(movies[movie_count].title, title);
    strcpy(movies[movie_count].showtime, showtime);
    strcpy(movies[movie_count].genre, genre);
    strcpy(movies[movie_count].description, description);
    movie_count++;
    printf("Movie added successfully\n");
    return true;
}

// Function to display movie information
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

int main() {
    // Add some movies
    add_movie("Inception", "8:00 PM", "Science Fiction", "A thief who enters the dreams of others to steal their secrets from their subconscious.");
    add_movie("The Dark Knight", "7:30 PM", "Action", "When the menace known as The Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.");
    add_movie("Titanic", "9:00 PM", "Romance", "A seventeen-year-old aristocrat falls in love with a kind but poor artist aboard the luxurious, ill-fated R.M.S. Titanic.");

    // Display movie information
    display_movies();

    return 0;
}
______________________________________________________________________________________________________________________
//Seats module (Navneet)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

// Constants
#define MAX_ROWS 10
#define MAX_COLS 10

// Seat structure
typedef struct {
    int row;
    int col;
    bool reserved;
} Seat;

// Array to store seat availability
Seat seats[MAX_ROWS][MAX_COLS];

// Function to initialize seat availability
void initialize_seats() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            seats[i][j].row = i + 1;
            seats[i][j].col = j + 1;
            seats[i][j].reserved = false;
        }
    }
}

// Function to check seat availability
bool is_seat_available(int row, int col) {
    if (row >= 1 && row <= MAX_ROWS && col >= 1 && col <= MAX_COLS) {
        return !seats[row - 1][col - 1].reserved;
    }
    return false;
}

// Function to reserve a seat
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

// Function to cancel seat reservation
bool cancel_seat_reservation(int row, int col) {
    if (row >= 1 && row <= MAX_ROWS && col >= 1 && col <= MAX_COLS) {
        seats[row - 1][col - 1].reserved = false;
        printf("Reservation for seat at row %d, column %d canceled successfully\n", row, col);
        return true;
    }
    else {
        printf("Invalid seat coordinates\n");
        return false;
    }
}

// Function to display seat availability
void display_seat_availability() {
    printf("Seat Availability:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c ", seats[i][j].reserved ? 'X' : 'O');
        }
        printf("\n");
    }
}

int main() {
    // Initialize seats
    initialize_seats();

    // Display initial seat availability
    printf("Initial Seat Availability:\n");
    display_seat_availability();
    printf("\n");

    // Reserve some seats
    reserve_seat(1, 2);
    reserve_seat(3, 4);

    // Display updated seat availability
    printf("\nUpdated Seat Availability:\n");
    display_seat_availability();
    printf("\n");

    // Cancel a reservation
    cancel_seat_reservation(1, 2);

    // Display final seat availability
    printf("\nFinal Seat Availability:\n");
    display_seat_availability();

    return 0;
}
_________________________________________________________________________________________________________________________________
