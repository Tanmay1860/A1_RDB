#include "Driver.h"
/*
* File : main.cpp
* Project: File Management System
* Programmers: Juan Jose Bejarano and Brayan Rojas
* First version: 27/09/2024
* Description:
* This program serves as the main entry point for a file management system,
* allowing the user to interact with different types of file access methods including
* delimited files (CSV), random access files, and a placeholder for sequential access files.
*/
int main(void) {
    int choice;
    char buffer[50]; // Buffer for input
    
    while (1) {
        // Display menu options
        printf("\nPrincipal Menu\n");
        printf("---------------\n");
        printf("1. Delimited Files(CSV)\n");
        printf("2. Random Access Files\n");
        printf("3. Sequential Access File\n");
        printf("4. Exit\n");
        printf("-> Enter your choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &choice); // Parse the integer from the buffer

        switch (choice) {
        case 1:
            MenuDelimitedFile();
            break;
        case 2:
            menuRandomAccess();
            break;
        case 3:

            break;
        case 4:
            printf("Exiting the program. Goodbye!\n");
            return 0;  // Exit the program
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}