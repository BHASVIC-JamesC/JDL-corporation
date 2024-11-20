#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getbill(char data[7][12][24]);

int main(void) {
    // Data: firstname surname dob age kids days board guests newspaper rooms Id
    char data[7][12][24] = {
        {"james", "cook","16","0","2","FB","3", "N", "3", "cook1234"},
        {"emma", "smith", "10/05/1992", "31", "1", "1", "BB", "5", "Y", "1", "smith2345"},
        {"liam", "johnson", "15/08/1985", "38", "2", "2", "HB", "7", "N", "6", "johnson6789"},
        {"olivia", "brown", "28/11/2001", "22", "0", "1", "FB", "4", "Y", "2", "brown4521"},
        {"noah", "williams", "04/02/1995", "29", "1", "2", "FB", "10", "N", "4", "williams7890"},
        {"sophia", "martin", "19/07/1988", "35", "3", "2", "HB", "6", "Y", "5", "martin3456"}
    };

    getbill(data);
    return 0;
}

int getbill() {
    int person = -1;
    char who[20];

    // Get the ID of the person checking out
    printf("Enter your ID:");
    scanf("%s", who);

    // Find the person by ID
    for (int i = 0; i < 7; i++) {
        if (strcmp(who, data[i][9]) == 0) {
            person = i;
            break;
        }
    }

    if (person == -1) {
        printf("Error: ID not found.\n");
        return -1;
    }

    // Extract and convert data
    char *paper = data[person][7];
    int kids = atoi(data[person][3]);
    int age = atoi(data[person][2]);
    int rooms = atoi(data[person][8]);
    int days = atoi(data[person][6]);
    int adults = atoi(data[person][4]);
    int guests = kids + adults;

    float total_bill = 0;
    float Roomcost = 0;
    float adultboard = 0;
    float childboard = 0;
    float total_board = 0;

    // Add cost for newspaper
    if (strcmp(paper, "Y") == 0) {
        total_bill += 5.5;
    }

    // Calculate room cost
    if (rooms == 1 || rooms == 2) {
        Roomcost = rooms * 100 * days;
    } else if (rooms == 3) {
        Roomcost = rooms * 85 * days;
    } else if (rooms == 4 || rooms == 5) {
        Roomcost = rooms * 75 * days;
    } else if (rooms == 6) {
        Roomcost = rooms * 50 * days;
    }

    // Discount for senior citizens
    if (age >= 65) {
        Roomcost *= 0.9;
    }

    // Calculate board cost for kids
    if (kids >= 1) {
        if (strcmp(data[person][5], "FB") == 0) {
            childboard = kids * 20;
        } else if (strcmp(data[person][5], "HB") == 0) {
            childboard = kids * 15;
        } else if (strcmp(data[person][5], "BB") == 0) {
            childboard = kids * 5;
        }
        childboard /= 2;  // Half-price for kids under 16
    }

    // Calculate board cost for adults
    if (strcmp(data[person][5], "FB") == 0) {
        adultboard = adults * 20;
    } else if (strcmp(data[person][5], "HB") == 0) {
        adultboard = adults * 15;
    } else if (strcmp(data[person][5], "BB") == 0) {
        adultboard = adults * 5;
    }

    // Calculate total board cost
    total_board = childboard + adultboard;

    // Total bill
    total_bill += Roomcost + total_board;

    // Output the bill
    printf("\n%s %s\nID: %s\nChild Board: %.2f\nAdult Board: %.2f\nRoom Cost: %.2f\nTotal: %.2f\n",
           data[person][0], data[person][1], data[person][9], childboard, adultboard, Roomcost, total_bill);

    // Remove the person from the data array
    for (int i = person; i < 6; i++) {
        for (int j = 0; j < 12; j++) {
            strcpy(data[i][j], data[i + 1][j]);
        }
    }

    printf("\nThank you for staying!\n");
    return 0;
}
