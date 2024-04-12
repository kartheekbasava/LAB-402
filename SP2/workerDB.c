#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h> // Added for strcasecmp
#include "readfile.h"

#define MAXNAME 64

// Removed redefinition of NULL

extern FILE *file; // File variable used to read the data from txt file

// Definition of the employee structure
struct employee {
    int id;
    char firstName[MAXNAME];
    char lastName[MAXNAME];
    int salary;
};

// Function prototypes
void printEmployee(struct employee *empPtr);
void printDB(struct employee (*empList)[1024], int *numEmployees);
void sortDB(struct employee (*empList)[1024], int *numEmployees);
void enterEmp(struct employee *empList, int *numEmployees);
int lookUpID(struct employee (*empList)[1024], int *numEmployees);
void lookUpLastName(struct employee (*empList)[1024], int *numEmployees);
void removeEmp(struct employee (*empList)[1024], int *numEmployees);
void updateEmp(struct employee (*empList)[1024], int *numEmployees);
void mSalary(struct employee (*empList)[1024], int *numEmployees);
void allLastName(struct employee (*empList)[1024], int *numEmployees);

// Function to read firstname from user // Function implementation
void read_firstName(char (*firstName)[MAXNAME]) {
    char test[MAXNAME];
    bool valid = false;
    printf("Enter the first name of the employee: ");
    scanf("%s", test);
    do {
        if (strlen(test) < MAXNAME - 1) {
            strcpy(*firstName, test);
            valid = true;
        } else {
            printf("Enter a valid first name with only %d characters: ", MAXNAME - 1);
            scanf("%s", test);
        }
    } while (!valid);
}

// Function to read lastname from user
void read_lastName(char (*lastName)[MAXNAME]) {
    char test[MAXNAME];
    bool valid = false;
    printf("Enter the last name of the employee: ");
    scanf("%s", test);
    do {
        if (strlen(test) < MAXNAME - 1) {
            strcpy(*lastName, test);
            valid = true;
        } else {
            printf("Enter a valid last name with only %d characters: ", MAXNAME - 1);
            scanf("%s", test);
        }
    } while (!valid);
}

// Function to read salary from user
void read_salary(int *salary) {
    bool valid = false;
    printf("Enter employee's salary (30,000 to 1,50,000): ");
    scanf("%d", salary);
    do {
        if (*salary >= 30000 && *salary <= 150000) {
            valid = true;
        } else {
            printf("Enter a valid valid salary in the range 30,000 to 1,50,000 (inclusive): ");
            scanf("%d", salary);
        }
    } while (!valid);
}

// Here you add the enterEmp function
void enterEmp(struct employee *empList, int *numEmployees) {
    printf("Adding a new employee...\n");

    struct employee newEmp;

    read_firstName(&(newEmp.firstName));
    read_lastName(&(newEmp.lastName));
    read_salary(&(newEmp.salary));

    printf("Do you want to add the following employee to the DataBase?\n\t%s %s, salary: %d\nEnter 1 for yes, 0 for no: ", newEmp.firstName, newEmp.lastName, newEmp.salary);
    int confirm;
    scanf("%d", &confirm);
    if (confirm == 1) {
        // Assign the next highest ID based on the last employee's ID in the list
        if (*numEmployees > 0) {
            newEmp.id = empList[*numEmployees - 1].id + 1;
        } else {
            newEmp.id = 1; // Start from 1 if no employees are present
        }

        empList[*numEmployees] = newEmp;
        (*numEmployees)++;

        printf("New employee added successfully!\n");
    } else {
        printf("Employee not added.\n");
    }
}

//Function to print each employee
void printEmployee(struct employee *empPtr) {
    printf("%-10s %-15s $%7d %10d\n", empPtr->firstName, empPtr->lastName, empPtr->salary, empPtr->id);
}

//Function to print the structure array
void printDB(struct employee (*empList)[1024], int *numEmployees) {
    printf("%-10s %-15s %7s %10s\n", "NAME", "LASTNAME", "SALARY", "ID");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < *numEmployees; i++) {
        printEmployee(&(*empList)[i]);
    }
    printf("---------------------------------------------------------------\n");
    printf("Number of Employees = %d\n\n", *numEmployees);
}


void sortDB(struct employee (*empList)[1024], int *numEmployees) {
    int i, j;
    int swapped;
    struct employee temp;
    for (i = 0; i < *numEmployees - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numEmployees - i - 1; j++) {
            if ((*empList)[j].salary < (*empList)[j + 1].salary) { // Compare salaries for sorting in decreasing order
                temp = (*empList)[j];
                (*empList)[j] = (*empList)[j + 1];
                (*empList)[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

//Function to lookup by ID
int lookUpID(struct employee (*empList)[1024], int *numEmployees) {
    printf("Enter a 6 digit employee id: ");
    int searchID;
    scanf("%d", &searchID);
    printf("The search ID is : %d\n", searchID);
    int found = 0;
    int i = 0;
    while (!found && i < *numEmployees) {
        if ((*empList)[i].id == searchID) {
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        } else
            i++;
    }

    //IF no matching iD is found
    if (!found) {
        i = -1;
        printf("Employee with that ID not found !\n\n");
    }

    //return index to use in allLastName function
    return i;
}

//Function to lookup by lastname
void lookUpLastName(struct employee (*empList)[1024], int *numEmployees) {
    char searchName[MAXNAME];
    printf("Enter Employee's last name (no extra spaces & case insensitive): ");
    fflush(stdout);
    scanf("%s", searchName);
    printf("The search Last Name is : %s\n", searchName);
    int found = 0;
    int i = 0;
    while (!found && i < *numEmployees) {
        if (strcasecmp((*empList)[i].lastName, searchName) == 0) {
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        }
        i++;
    }
    if (!found) {
        printf("Employee with that last name not found !\n\n");
    }
}

// Function to remove an employee by ID
void removeEmp(struct employee (*empList)[1024], int *numEmployees) {
    int idToRemove;
    printf("Enter the ID of the employee to remove: ");
    scanf("%d", &idToRemove);

    int foundIndex = -1;
    for (int i = 0; i < *numEmployees; i++) {
        if ((*empList)[i].id == idToRemove) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Employee found:\n");
        printEmployee(&(*empList)[foundIndex]);

        printf("Are you sure you want to remove this employee? (1 for yes, 0 for no): ");
        int confirm;
        scanf("%d", &confirm);

        if (confirm == 1) {
            // Shift elements to fill the gap
            for (int i = foundIndex; i < *numEmployees - 1; i++) {
                (*empList)[i] = (*empList)[i + 1];
            }
            (*numEmployees)--;
            printf("Employee removed successfully!\n");
        } else {
            printf("Employee not removed.\n");
        }
    } else {
        printf("Employee with ID %d not found.\n", idToRemove);
    }
}

// Function to update an employee's information
void updateEmp(struct employee (*empList)[1024], int *numEmployees) {
    int idToUpdate;
    printf("Enter the ID of the employee to update: ");
    scanf("%d", &idToUpdate);

    int foundIndex = -1;
    for (int i = 0; i < *numEmployees; i++) {
        if ((*empList)[i].id == idToUpdate) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Employee found:\n");
        printEmployee(&(*empList)[foundIndex]);

        // Prompt user for updated information
        read_firstName(&((*empList)[foundIndex].firstName));
        read_lastName(&((*empList)[foundIndex].lastName));
        read_salary(&((*empList)[foundIndex].salary));

        printf("Employee information updated successfully!\n");
    } else {
        printf("Employee with ID %d not found.\n", idToUpdate);
    }
}


// Function to sort the structure based on ID
void sortByID(struct employee (*empList)[1024], int *numEmployees) {
    int i, j;
    int swapped;
    struct employee temp;
    for (i = 0; i < *numEmployees - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numEmployees - i - 1; j++) {
            if ((*empList)[j].id > (*empList)[j + 1].id) {
                temp = (*empList)[j];
                (*empList)[j] = (*empList)[j + 1];
                (*empList)[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}



// Function to print the M employees with the highest salaries
void mSalary(struct employee (*empList)[1024], int *numEmployees) {
    int M;
    printf("Enter the number of employees with the highest salaries to print: ");
    scanf("%d", &M);

    if (M <= 0) {
        printf("Invalid input. Number of employees must be greater than 0.\n");
        return;
    }

    if (M > *numEmployees) {
        printf("Number of employees with highest salaries exceeds the total number of employees.\n");
        return;
    }

    printf("Printing the %d employee(s) with the highest salaries:\n", M);
    // Sort by salary in decreasing order
    sortDB(empList, numEmployees);

    // Print M employees with highest salaries
    for (int i = 0; i < M; i++) {
        printEmployee(&(*empList)[i]);
    }

    // Re-sort by employee ID to maintain the original order
    sortByID(empList, numEmployees);
}



// Function to find all employees with matching last name
void allLastName(struct employee (*empList)[1024], int *numEmployees) {
    char searchName[MAXNAME];
    printf("Enter the last name to search for (case insensitive): ");
    scanf("%s", searchName);

    printf("Employees with last name \"%s\":\n", searchName);
    int found = 0;
    for (int i = 0; i < *numEmployees; i++) {
        if (strcasecmp((*empList)[i].lastName, searchName) == 0) {
            found = 1;
            printEmployee(&(*empList)[i]);
        }
    }

    if (!found) {
        printf("No employees found with last name \"%s\".\n", searchName);
    }
}

//Main Function to run the program***********************************************************************************************
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]); // Instructs the user how to run the program correctly
        return 1; // Exits the program with a non-zero value indicating an error
    }

    char *filename = argv[1]; //Assinged the string passed in commandline to the filename to be opened

    struct employee empList[1024];
    int numEmployees = 0;

    if (open_file(filename) == 0) {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file)) {
            ret = read_int(buffer, 1, &empList[numEmployees].id);
            ret = read_int(buffer, 2, &empList[numEmployees].salary);
            ret = read_string(buffer, 1, empList[numEmployees].firstName);
            ret = read_string(buffer, 2, empList[numEmployees].lastName);
            numEmployees++;
        }

        if (feof(file)) // hit end of file
        {
            close_file();
        }
    } else {
        printf("Error! Re-run the program with a proper filename");
        return -1;
    }

    // Sort the structure
    sortByID(&empList, &numEmployees);

    int choice;
    do {
        printf("Employee DataBase Menu:\n");
        printf("----------------------------------\n");
        printf("  (1) Print the Database\n");
        printf("  (2) Lookup by ID\n");
        printf("  (3) Lookup by Last Name\n");
        printf("  (4) Add an Employee\n");
        printf("  (5) Remove an Employee\n");
        printf("  (6) Update an Employee's information\n");
        printf("  (7) Print the M employees with the highest salaries\n");
        printf("  (8) Find all employees with matching last name\n");
        printf("  (9) Quit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        
        if(scanf("%d", &choice) != 1 || choice < 1|| choice > 9){
            choice = 0;
            printf("Invalid input. Please enter a number b/w 1 to 9. \n");
            while(getchar() != '\n');
        };

        switch (choice) {
            case 1:
                printDB(&empList, &numEmployees);
                break;
            case 2:
                lookUpID(&empList, &numEmployees);
                break;
            case 3:
                lookUpLastName(&empList, &numEmployees);
                break;
            case 4:
                enterEmp(empList, &numEmployees); // Correct call
                break; // This break was missing, causing fall-through to case 5
            case 5:
                removeEmp(&empList, &numEmployees);
                break;
            case 6:
                updateEmp(&empList, &numEmployees);
                break;
            case 7:
                mSalary(&empList, &numEmployees);
                break;
            case 8:
                allLastName(&empList, &numEmployees);
                break;
            case 9:
                printf("Thank You goodbye!\n");
                break; // Ensure this break is here
            default:
                printf("Hey, %d is not between 1 and 9, try again...\n", choice);
                break; // Added break here for consistency
        }
    } while (choice != 9); // This line is correct

    return 0;
}
