#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct moviedetails {
    char name[20];
    unsigned int phone;
    int seat;
    int id;
};

struct moviedetails person[300];
int count = 0;
int id2 = 1000;

int **seat;

void display_reserved_tickets(void) {
    printf("Currently reserved tickets:\n");
    for (int i = 0; i < count; i++) {
        printf("Booking ID: %d, Name: %s, Seat: %d\n", person[i].id, person[i].name, person[i].seat);
    }
}

void display_booked_seats() {
    printf("Booked seats for each movie:\n");
    for (int movie = 0; movie < 3; movie++) {
        printf("Movie %d:\n", movie + 1);
        printf("Seats: ");
        for (int seat_number = 1; seat_number <= 100; seat_number++) {
            if (seat[movie][seat_number] == 1) {
                printf("%d ", seat_number);
            }
        }
        printf("\n");
    }
}

int choice1(void) {
    int choice;
    printf("Please select an option:\n");
    printf("1. Show Movie Details\n");
    printf("2. Make a Reservation\n");
    printf("3. Cancel a Reservation\n");
    printf("4. Admin Menu\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int changeprize(int prize);
void details(void) {
    printf("Available Movies:\n");
    printf("1. Toy Story 6\n");
    printf("2. Pokemon\n");
    printf("3. Naruto: Movie 1\n");
}

int movie(void) {
    int selection;
    printf("Select a movie (1-3): ");
    scanf("%d", &selection);
    return selection;
}

int cmovie(void) {
    int booking_id;
    printf("Enter your Booking ID to cancel: ");
    scanf("%d", &booking_id);
    return booking_id;
}

void cancel(int *array) {
    int booking_id = cmovie();
    for (int i = 0; i < count; i++) {
        if (person[i].id == booking_id) {
            array[person[i].seat] = 0;
            printf("Reservation with Booking ID %d has been cancelled.\n", booking_id);
            for (int j = i; j < count - 1; j++) {
                person[j] = person[j + 1];
            }
            count--;
            return;
        }
    }
    printf("Invalid Booking ID.\n");
}

void print_ticket(int choice, char name[20], int id2, int price, char *show_name, char *date, char *time, int hall) {
    printf("\n\n");
    printf("\t-----------------THEATER BOOKING TICKET----------------\n");
    printf("\t============================================================\n");
    printf("\t Booking ID : %d \t\t\tShow Name : %s\n", id2, show_name);
    printf("\t Customer  : %s\n", name);
    printf("\t\t\t                              Date      : %s\n", date);
    printf("\t                                              Time      : %s\n", time);
    printf("\t                                              Hall      : %d\n", hall);
    printf("\t                                              seats No. : %d\n", choice);
    printf("\t                                              price . : %d\n\n", price);
    person[count].id = id2;
    printf("\t============================================================\n");
}

void reservation(int *array, int price, int selection);

void admin_menu() {
    int choice;
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. View Booked Seats\n");
        printf("2. Change Ticket Price\n");
        printf("3. Exit Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_booked_seats();
                break;
            case 2:
                printf("Change ticket price functionality not implemented yet.\n");
                break;
            case 3:
                printf("Exiting admin menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);
}

int main() {
    int choice, price = 500, selection, i;
    seat = (int **)calloc(3, sizeof(int *));
    for (i = 0; i < 3; i++)
        seat[i] = (int *)calloc(101, sizeof(int));

    int x = 0;
    while (x != 5) {
        choice = choice1();
        switch (choice) {
        case 1:
            details();
            break;
        case 2:
            selection = movie();
            reservation(seat[selection - 1], price, selection);
            count++;
            break;
        case 3:
            selection = cmovie();
            cancel(seat[selection - 1]);
            break;
        case 4:
            admin_menu();
            break;
        case 5:
            x = 5;
            break;
        default:
            printf("Choice not available\n");
            break;
        }
    }

    for (i = 0; i < 3; i++) {
        free(seat[i]);
    }
    free(seat);
}

int changeprize(int prize) {
    char pass[10], pak[10] = "admin";
    printf("Enter the password to change price of ticket: ");
    scanf("%s", pass);
    if (strcmp(pass, pak) == 0) {
        printf("Please enter new price: ");
        scanf("%d", &prize);
        system("PAUSE");
        system("CLS");
    } else {
        printf("The entered password is wrong! ");
    }
    return prize;
}

void reservation(int *array, int price, int selection) {
    int num_tickets;
    printf("How many tickets do you want to purchase? ");
    scanf("%d", &num_tickets);
    for (int t = 0; t < num_tickets; t++) {
        int j;
        printf("\n                                SCREEN\n\n\n");
        for (int i = 1; i <= 100; i++) {
            if (array[i] == 0)
                printf("%d\t", i);
            else
                printf("*\t");
            if (i % 10 == 0)
                printf("\n\n");
        }
        printf("Please enter your name for ticket %d: ", t + 1);
        scanf(" %19[^\n]", person[count].name);
        printf("Please enter your phone number for ticket %d: ", t + 1);
        scanf("%u", &person[count].phone);

        printf("Which seat number do you want for ticket %d? ", t + 1);
        scanf("%d", &j);

        while (j > 100 || j < 1 || array[j] == 1) {
            if (j > 100 || j < 1) {
                printf("Seat number is unavailable in this theater\n");
            } else {
                printf("Sorry, this ticket is already booked! Please choose another seat.\n");
            }
            printf("Please re-enter seat number: ");
            scanf("%d", &j);
        }
        array[j] = 1;
        person[count].seat = j;

        if (selection == 1)
            print_ticket(j, person[count].name, id2, price, "Toy Story 6", "29-04-2024", "08:00pm", 2);
        else if (selection == 2)
            print_ticket(j, person[count].name, id2, price, "Pokemon", "15-04-2022", "09:00pm", 3);
        else
            print_ticket(j, person[count].name, id2, price, "Naruto: Movie 1", "12-05-2021", "10:00pm", 4);
    
        id2++;
        count++;
    }
}