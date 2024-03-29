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
// Tijeet Singh Modules
// main.c 

#include "reservation.h"


int main() {
    int **seat, choice, price = 20, selection, i;
    seat = (int **)calloc(101, sizeof(int *));
    for (i = 0; i < 3; i++)
        *(seat + i) = (int *)calloc(101, sizeof(int));
    int x;
    while (x != 5) {
        choice = reservationChoice();
        switch (choice) {
            case 1:
                price = changeName();
                break;
            case 2:
                details();
                break;
            case 3:
                selection = movieSelection();
                reservation(seat[selection - 1], price, selection);
                break;
            case 4:
                selection = movieSelection();
                cancel(seat[selection - 1]);
                break;
            case 5:
                x = 5;
                break;
            default:
                printf("Choice not available\n");
                break;
        }
    }
    return 0;
}
// reservation.c

#include "reservation.h"

int count=0;
float totalFoodBill;

// Declare an array of food items
struct FoodItem foodMenu[] = {
        {"Popcorn", 15},
        {"Soft Drink", 10},
        {"Nachos", 20},
        // Add more food items as needed
};
// function to edit user name 
int changeName() {
    int bookingId;
    printf("Please enter your booking id: ");
    if (scanf_s("%d", &bookingId) != 1) {
        printf("Error: Invalid input. Please enter a valid booking ID.\n");
        // Clear input buffer
        while (getchar() != '\n');
        return 0;
    }

    char isFound = 'N'; // Initialize isFound to 'N'
    for(int i = 0; i < count; i++) {
        if(bookingId == person[i].id) {
            printf("Please enter your name: ");
            scanf_s(" %19[^\n]%*c", &person[i].name);
            printf("\n");
            printf("Name successfully Updated, Below are the new Booking details\n");
            viewBookedDetails(person[i]);
            isFound = 'Y';
            sleep(2);
            break; // Exit the loop once booking ID is found
        }
    }
    if(isFound != 'Y') {
        printf("\n<<<<<<<<<< No Booking details found for the provided ID >>>>>>>>>>\n\n");
        sleep(2);
        return 0;
    }
    return 0;
}
// fucntion to reserve a booking for user 
void reservation(int *array, int price, int selection) {
    int i, j;
    char food_choice[4];
    char email[100];

    printf("\n                                SCREEN\n\n\n");
    for (i = 1; i <= 100; i++) {
        if (array[i] == 0)
            printf("%d\t", i);
        else
            printf("*\t", i);
        if (i % 10 == 0)
            printf("\n\n");
    }
    printf("Please enter your name: ");
    scanf_s(" %19[^\n]%*c", &person[count].name);
    printf("Please enter your email address: ");
    scanf_s("%99s", email);
    printf("Please enter your phone number: ");
    if (scanf_s("%u", &person[count].phone) != 1) {
        printf("Error: Invalid input. Please enter a valid phone number.\n");
        // Clear input buffer
        while (getchar() != '\n');
        return;
    }
    printf("Which seat number you want? ");
    if (scanf_s("%d", &j) != 1 || j > 100 || j < 1) {
        printf("Error: Invalid input. Please enter a seat number between 1 and 100.\n");
        // Clear input buffer
        while (getchar() != '\n');
        return;
    }
    if (array[j] == 1) {
        printf("Sorry, this ticket is already booked! Please choose another seat.\n");
        return;
    } else
        array[j] = 1;
    person[count].seat = j;

    // Food ordering
    int totalFoodCost = orderFood(food_choice);

    // Calculate total bill including ticket price and food
    int totalBill = price + totalFoodCost;
    person[count].totalPrice = totalBill;
    printf("\nProcessing your payment\n");

    for(int k=0;k<3;k++) {
        printf(".\n");
        sleep(1);
    }

    printf("\n\n\nYour payment has been processed\n");
    printf("\nReservation details have been emailed to %s.\n", email);
    // Print all reservation details along with the total bill
    printf("\nBelow is your emailed Reservation Details:\n");
    srand(time(NULL));
    int r = rand();
    person[count].id= r;
    viewBookedDetails(person[count]);
    sleep(2);
}
// fucntion for ordering food 
int orderFood(const char *food_choice) {
    int totalFood = 0;
    printf("Do you want to order food? (yes/no): ");
    scanf_s("%s", food_choice);
    if (strcmp(food_choice, "yes") == 0) {
        printf("=========== FOOD MENU ===========\n");
        for (int i = 0; i < sizeof(foodMenu) / sizeof(foodMenu[0]); i++) {
            printf("%d. %s - $%d\n", i + 1, foodMenu[i].name, foodMenu[i].price);
        }
        printf("0 - End Order\n");
        printf("=================================\n");

        int totalFoodItems = sizeof(foodMenu) / sizeof(foodMenu[0]);
        int order[totalFoodItems];
        memset(order, 0, sizeof(order)); // Initialize order array to zeros

        printf("Enter the number corresponding to the food item you want to order :\n");
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

        // Calculate and print the total bill for food items

        printf("\nYour Food Order:\n");
        for (int i = 0; i < totalFoodItems; i++) {
            if (order[i] > 0) {
                printf("%s - Quantity: %d - Price: $%d\n", foodMenu[i].name, order[i], foodMenu[i].price * order[i]);
                totalFood += foodMenu[i].price * order[i];
            }
        }
        printf("Total Food Bill: $%d\n\n", totalFood);
    }
    else if (strcmp(food_choice, "no") == 0) {
       // do nothing
    } else {
        printf("Wrong Input");
    }
    return totalFood;
}
// fucntion to view number of bookings 
void viewBookedDetails(struct MovieDetails psn) {
    printf("------------------------------------\n");
    printf(ANSI_COLOR_RED "Booking ID: %d\n" ANSI_COLOR_RESET, psn.id);
    printf("Name: %s\n", psn.name);
    printf("Phone Number: %u\n", psn.phone);
    printf("Seat Number: %d\n", psn.seat);
    printf("Total Bill: $%d\n", psn.totalPrice);
    printf("------------------------------------\n");
    count++;

}

void details() {
    if(count ==0) {
        printf("\n<<<<<<<<<< No Booking details found >>>>>>>>>>\n\n");
        sleep(2);
        return;
    }
    printf("\n<<<<<<<<<< Reservation Details : Start >>>>>>>>>>\n\n");
        for (int i = 0; i < count; i++) {
            if(person[i].id >0) {
                viewBookedDetails(person[i]);
            }
        }
    printf("\n<<<<<<<<<< Reservation Details : End >>>>>>>>>>\n\n");
        sleep(2);
  }
// fucntion to print main menu 
int reservationChoice() {
    int choice;
    printf("                 Movie Ticket Booking System\n");
    printf("||================================================================||\n");
    printf("||             1- To edit the reservation name:                   ||\n");
    printf("||             2- To view reserved tickets :                      ||\n");
    printf("||             3- To purchase ticket:                             ||\n");
    printf("||             4- To cancel the seat:                             ||\n");
    printf("||             5- Exit system:                                    ||\n");
    printf("||================================================================||\n");
    printf("  Enter your choice: \n");

    while (1) {
        if (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 5) {
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
            // Clear input buffer
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return choice;
}

// fucntion to print movie menu 
int movieSelection() {
    int i;

    printf("\t\t\tSelect A Movie to start\n");
    printf("\t\t\t----------------------------\n\n");
    printf("\t\t\tPress 1 for Avengers: EndGame\n\n");
    printf("\t\t\tPress 2 for Captain Marvel\n\n");
    printf("\t\t\tPress 3 for Spider-Man: Far From Home\n\n");
    printf("\t\t\t----------------------------\n\n");
    printf("Choice:");

    while (1) {
        if (scanf_s("%d", &i) != 1 || (i < 1 || i > 3)) {
            printf("Error: Invalid input. Please enter a valid movie selection (1-3).\n");
            // Clear input buffer
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    return i;
}

// fucntion to cancel booking 
void cancel(int *array) {
    int Cseat, i, stop;
    printf("Please enter ID number of ticket: ");
    if (scanf_s("%d", &Cseat) != 1) {
        printf("Error: Invalid input. Please enter a valid ticket ID.\n");
        // Clear input buffer
        while (getchar() != '\n');
        return;
    }

    for (i = 0; i < count; i++) {
        if (Cseat == person[i].id) {
            stop = 5;

            printf("%s, your seat %d is cancelled.\n", person[i].name, person[i].seat);
            array[person[i].seat] = 0;

            // Remove canceled reservation from the list
            for (int j = i; j < count - 1; j++) {
                person[j] = person[j + 1];
            }
            count--; // Decrease the count of reservations
            i--; // Adjust the index after removal
            break;
        }
    }
    if (stop != 5)
        printf("Ticket ID number is incorrect. Please enter the correct one to cancel the ticket.\n");
}

// reservation.h

#pragma once
#ifndef RESERVATION_H_
#define RESERVATION_H_

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>



// Define a structure for food items
struct FoodItem {
    char name[50];
    int price;
};



struct MovieDetails {
    char name[20];
    unsigned int phone;
    int seat;
    int id;
    int totalPrice;
};




struct MovieDetails person[300];

int changeName();
void reservation(int *array, int price, int selection);
void viewBookedDetails(struct MovieDetails person);
int orderFood(const char *food_choice);
int reservationChoice();
int movieSelection();
void cancel(int *array);
void details();

#endif



_________________________________________________________________________________________________________________________________
