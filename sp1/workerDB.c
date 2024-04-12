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
    char test[128];
    bool valid = false;
    printf("Enter the first name of the employee: ");
    scanf("%s", test);
    do{
        if(strlen(test)<63){
            strcpy(*firstName,test);
            valid = true;
        }
        else {
            printf("Enter a valid first name with only 63 characters: ");
            scanf("%s", test);
        }  
    } while(valid != true);
    
}
 

// Function to read lastname from user
void read_lastName(char (*lastName)[MAXNAME]) {
 char test[128];
    bool valid = false;
    printf("Enter the last name of the employee: ");
    scanf("%s", test);
    do{
        if(strlen(test)<63){
            strcpy(*lastName,test);
            valid = true;
        }
        else {
            printf("Enter a valid last name with only 63 characters: ");
            scanf("%s", test);
        }  
    } while(valid != true);
}
   


// Function to read salary from user
void read_salary(int *salary) {
    bool valid = false;
    printf("Enter employee's salary (30,000 to 1,50,000): ");
    scanf("%d", salary);
    do{
        if(*salary>=30000 && *salary<=150000){
            valid = true;
        }
        else {
            printf("Enter a valid valid salary in the range 30,000 to 1,50,000 (inclusive): ");
            scanf("%d", salary);
        }
    } while(valid != true);
}

// Here you add the enterEmp function
void enterEmp(struct employee *empList, int *numEmployees) {
    printf("Adding a new employee...\n");
    
    struct employee newEmp;
    
    printf("Enter the first name of the employee: ");
    scanf("%63s", newEmp.firstName); // Ensure we do not exceed array bounds
    
    printf("Enter the last name of the employee: ");
    scanf("%63s", newEmp.lastName);
    
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &newEmp.salary);
    while(newEmp.salary < 30000 || newEmp.salary > 150000) {
        printf("Invalid salary. Please enter a value between 30000 and 150000: ");
        scanf("%d", &newEmp.salary);
    }
 printf("Do you want to add the following employee to the DataBase?\n\t%s %s, salary: %d\nEnter 1 for yes, 0 for no: ", newEmp.firstName, newEmp.lastName, newEmp.salary);
    int confirm;
    scanf("%d", &confirm);    
     if(confirm == 1) {
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
void printEmployee(struct employee *empPtr){
    printf("%-10s %-15s $%7d %10d\n", empPtr->firstName, empPtr->lastName, empPtr->salary, empPtr->id);
}

//Function to print the structure array
void printDB(struct employee (*empList)[1024], int *numEmployees){
    printf("%-10s %-15s %7s %10s\n", "NAME", "LASTNAME", "SALARY", "ID");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < *numEmployees; i++){
        printEmployee(&(*empList)[i]);
    }
    printf("---------------------------------------------------------------\n");
    printf("Number of Employees = %d\n\n", *numEmployees);
}

//Funciton to sort the strucutre based on ID
void sortDB(struct employee (*empList)[1024], int *numEmployees){   
    int i, j;
    int swapped;
    struct employee temp;
    for (i = 0; i < *numEmployees - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numEmployees - i - 1; j++) {
            if ((*empList)[j].id > (*empList)[j + 1].id) {
                temp = (*empList)[j];
                (*empList)[j] = (*empList)[j + 1];
                (*empList)[j+1] = temp;
                swapped = 1;
            }
        }
    }
}

//Function to lookup by ID
int lookUpID(struct employee (*empList)[1024], int *numEmployees){
    printf("Enter a 6 digit employee id: ");
    int searchID = 999999;
    fflush(stdout);
    scanf("%d", &searchID);
    printf("The search ID is : %d\n", searchID);
    int found=0;
    int i=0;
    while(!found && i<*numEmployees){ 
        if((*empList)[i].id == searchID){
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        }
        else
            i++;
    }

    //IF no matching iD is found
    if(!found){
        i = -1;
        printf("Employee with that ID not found !\n\n");
    }

    //return index to use in allLastName function
    return i;
}

//Function to lookup by lastname
void lookUpLastName(struct employee (*empList)[1024], int *numEmployees){
    char searchName[64];
    printf("Enter Employee's last name (no extra spaces & case insensitive): ");
    fflush(stdout);
    scanf("%s", searchName);
    printf("The search Last Name is : %s\n", searchName);
    int found=0;
    int i=0;
    while(!found && i<*numEmployees){
        if(strcasecmp((*empList)[i].lastName,searchName)==0){
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        }
        i++;
    }
    if(!found){
        printf("Employee with that last name not found !\n\n");
    }
}

int main(int argc, char **argv) {
if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]); // Instructs the user how to run the program correctly
        return 1; // Exits the program with a non-zero value indicating an error
    }

    char *filename = argv[1]; //Assinged the string passed in commandline to the filename to be opened

    struct employee empList[1024], temp;
    int numEmployees = 0;
    int i = 0;

    if (open_file(filename) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file))
        {
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
    }
    else{
        printf("Error! Re-run the program with a proper filename");
        return -1;
    }

   
    // Sort the structure 
    sortDB(&empList, &numEmployees);

     int choice;
    do {
        printf("Employee DataBase Menu:\n");
        printf("----------------------------------\n");
        printf("  (1) Print the Database\n");
        printf("  (2) Lookup by ID\n");
        printf("  (3) Lookup by Last Name\n");
        printf("  (4) Add an Employee\n");
        printf("  (5) Quit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
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
                printf("Thank You goodbye!\n");
                break; // Ensure this break is here
            default:
                printf("Hey, %d is not between 1 and 5, try again...\n", choice);
                break; // Added break here for consistency
        }
    } while(choice != 5); // This line is correct

    return 0;
}


