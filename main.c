#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//check in subroutines
void checkIn();


//dinner subroutines
void dinner(char userDetails[12][24]);
int eligible(char bookingIDdinner[20]);
void findTable(char bookingIDdinner[20], char userDetails[12][24]);
void quitProgram(char userDetails[12][24]);




char data[7][12][24];
char tables[2][3][12];
int guest=0;
int main(void) {
    int run = 1;
    char userDetails[12][24] = {0};    // Initialize user details


    printf("Welcome to Kashyyk Hotel\n");
    while (run == 1) {
        char userChoice;
        printf("Would you like to check in(a), Book dinner(b) or check out(c): ");
        fflush(stdin);
        scanf(" %c", &userChoice);

        switch (userChoice) {
            case 'a':
                checkIn(data, userDetails);
            break;
            case 'b':
                dinner(userDetails);
            break;
            case 'c':
                printf("Thank you for visiting Kashyyk Hotel. Goodbye!\n");
            run = 0;
            break;
            default:
                printf("That is not a valid option. Please try again.\n");
            break;
        }
    }

    return 0;
}


void checkIn(char userDetails[12][24]) {

    if (guest >= 7) {
        printf("No more guests can be accommodated.\n");
        return;
    }

    char firstName[20], lastName[20], board[4], newspaper[2], bookingID[24], temp[20];
    int day, month, year, age,kids,guests, adults, days, room, valid = 0, random;
    srand(time(NULL));

    printf("Enter your full name:");
    fflush(stdin);
    scanf("%s %s", firstName, lastName);

    // Date of birth and age validation
    do {
        printf("What is your date of birth?Enter day,month,and year(dd/mm/yy):");
        fflush(stdin);
        scanf("%d/%d/%d", &day, &month, &year);
        int currentYear = 2024;
        age = currentYear - (year < 24 ? 2000 + year : 1900 + year);
        if (age < 16) {
            printf("You must be at least 16 years old to check in.\n");
        }
    } while (age < 16);

    // Guest and children validation
    do {
        printf("Enter the number of guests (max 4):");
        fflush(stdin);
        scanf("%d", &guests);
        if (guests < 1 || guests > 4) {
            printf("Invalid number of guests. Please enter between 1 and 4.\n");
        }
    } while (guests < 1 || guests > 4);

    do {
        printf("\nHow many children will be staying with you?:");
        fflush(stdin);
        scanf("%d", &kids);
        if (kids < 0 || kids > guests) {
            printf("Invalid number of children. Please enter between 0 and %d.\n", guests);
        }
    } while (kids < 0 || kids > guests);

    adults = guests - kids;

    // Board type selection
    do {
        printf("\nWhat board type do you want to book?\nFull Board(FB)\tHalf Board(HB)\tBed and Breakfast(BB):");
        fflush(stdin);
        scanf("%s", board);
        if (strcmp(board, "FB") != 0 && strcmp(board, "HB") != 0 && strcmp(board, "BB") != 0) {
            printf("Invalid board type. Please try again.\n");
        }
    } while (strcmp(board, "FB") != 0 && strcmp(board, "HB") != 0 && strcmp(board, "BB") != 0);

    // Stay duration
    do {
        printf("\nHow many days will you be staying with us?:");
        fflush(stdin);
        scanf("%d", &days);
        if (days <= 0) {
            printf("Invalid number of days. Please enter a positive number.\n");
        }
    } while (days <= 0);

    // Newspaper preference
    do {
        printf("\nDo you want a daily newspaper? (Y/N): ");
        fflush(stdin);
        scanf(" %c", newspaper);
        if (newspaper[0] != 'Y' && newspaper[0] != 'N') {
            printf("Invalid option. Please enter Y or N.\n");
        }
    } while (newspaper[0] != 'Y' && newspaper[0] != 'N');

    // Room selection
    do {
        printf("What room would you like to book (1-6):\n"
               "Room 1(100)\tRoom 2(100)\tRoom 3(85)\tRoom 4(75)\tRoom 5(75)\tRoom 6(50):");
        fflush(stdin);
        scanf("%d", &room);
        if (room < 1 || room > 6) {
            printf("Invalid room number. Please select between 1 and 6.\n");
            valid = 0;
        } else {
            valid = 1;
            for (int i = 0; i < 7; i++) {
                if (data[i][8][0] != '\0' && atoi(data[i][8]) == room) {
                    printf("Sorry, that room is unavailable.\nPlease pick another.\n");
                    valid = 0;
                    break;
                }
            }
        }
    } while (!valid);

    // Generate booking ID
    random = 1000 + rand() % 9000;
    snprintf(temp, sizeof(temp), "%d", random);
    snprintf(bookingID, sizeof(bookingID), "%s%d", lastName, random);
    printf("Booking ID:%s\n", bookingID);
    // Save to `data` and `userDetails`


    snprintf(data[guest][0], 24, "%s", firstName);
    snprintf(data[guest][1], 24, "%s", lastName);
    snprintf(data[guest][2], 24, "%d", age);
    snprintf(data[guest][3], 24, "%d", kids);
    snprintf(data[guest][4], 24, "%d", adults);
    snprintf(data[guest][5], 24, "%s", board);
    snprintf(data[guest][6], 24, "%d", days);
    data[guest][7][0] = newspaper[0];
    snprintf(data[guest][8], 24, "%d", room);
    snprintf(data[guest][9], 24, "%s", bookingID);

    for (int i = 0; i < 10; i++) {
        strncpy(userDetails[i], data[guest][i], 24);
    }

    guest ++;
    printf("\n%d\n",guest);





    printf("Check-in complete!\n");
}


//dinner stuff now

void dinner(char userDetails[12][24]) {
    char bookingIDdinner[20];
    printf("\nHello! Welcome to dinner.\n");


    printf("\nWhat's your booking ID?: ");
    fflush(stdin);
    fgets(bookingIDdinner, sizeof(bookingIDdinner), stdin);
    bookingIDdinner[strcspn(bookingIDdinner, "\n")] = '\0'; // Remove trailing newline

    if (eligible(bookingIDdinner) == 1) {
        findTable(bookingIDdinner,userDetails);
    } else {
        printf("Sorry, you're not eligible for dinner. Only Full Board (FB) and Half Board (HB) guest are allowed.\n");
        quitProgram(userDetails);
    }
}


int eligible(char bookingIDdinner[20]) {


    for (int i = 0; i < 7; i++) {
        if (strcmp(data[i][9], bookingIDdinner) == 0) {
            if (strcmp(data[i][5], "FB") == 0 || strcmp(data[i][5], "HB") == 0) {
                printf("Booking ID '%s' is eligible for dinner.\n", bookingIDdinner);
                return 1; // Eligible
            } else {
                printf("Booking ID '%s' found, but board type '%s' is not eligible.\n", bookingIDdinner, data[i][5]);
            }
        }
    }
    printf("Booking ID '%s' not found or not eligible.\n", bookingIDdinner);
    return 0; // Not eligible
}


void findTable(char bookingIDdinner[20], char userDetails[12][24]) {
    char tableChoice[10];
    int available = 0;

    // Display available tables
    if (strcmp(tables[0][0], "") == 0) {
        printf("\nEndor is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[0][1], "") == 0) {
        printf("Naboo is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[0][2], "") == 0) {
        printf("Tatooine is available at 7pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][0], "") == 0) {
        printf("Endor is available at 9pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][1], "") == 0) {
        printf("Naboo is available at 9pm.\n");
        available = 1;
    }
    if (strcmp(tables[1][2], "") == 0) {
        printf("Tatooine is available at 9pm.\n");
        available = 1;
    }

    if (!available) {
        printf("\nNo tables available right now.\n");
        quitProgram(userDetails);
        return;
    }

    printf("\nWhich table and time would you like to book?\nFor example, type: Naboo7 for table Naboo at 7pm\nEnter: ");
    fflush(stdin);
    scanf("%s", tableChoice);

    // Process table choice
    if (strcmp(tableChoice, "Endor7") == 0 && strcmp(tables[0][0], "") == 0) {
        strcpy(tables[0][0], bookingIDdinner);
        printf("\nReservation confirmed for Endor at 7pm.\n");
    } else if (strcmp(tableChoice, "Naboo7") == 0 && strcmp(tables[0][1], "") == 0) {
        strcpy(tables[0][1], bookingIDdinner);
        printf("\nReservation confirmed for Naboo at 7pm.\n");
    } else if (strcmp(tableChoice, "Tatooine7") == 0 && strcmp(tables[0][2], "") == 0) {
        strcpy(tables[0][2], bookingIDdinner);
        printf("\nReservation confirmed for Tatooine at 7pm.\n");
    } else if (strcmp(tableChoice, "Endor9") == 0 && strcmp(tables[1][0], "") == 0) {
        strcpy(tables[1][0], bookingIDdinner);
        printf("\nReservation confirmed for Endor at 9pm.\n");
    } else if (strcmp(tableChoice, "Naboo9") == 0 && strcmp(tables[1][1], "") == 0) {
        strcpy(tables[1][1], bookingIDdinner);
        printf("\nReservation confirmed for Naboo at 9pm.\n");
    } else if (strcmp(tableChoice, "Tatooine9") == 0 && strcmp(tables[1][2], "") == 0) {
        strcpy(tables[1][2], bookingIDdinner);
        printf("\nReservation confirmed for Tatooine at 9pm.\n");
    } else {
        printf("That is not a valid table/time or it is already booked. Try again later.\n");
    }

    quitProgram(userDetails);
}


void quitProgram(char userDetails[12][24]) {
    for (int i = 0; i < 12; i++) {
        memset(userDetails[i], 0, 24); // Clear each row of the 2D array
    }
}



