#include <stdio.h>
#include <string.h>

#define MAX 100

struct Patient
{
    int id;
    char name[50];
    int age;
    char condition[100];
    int priority;
    int arrival;
};

struct Patient queue[MAX];
int count = 0;
int arrivalCounter = 0;

void displayPriority(int priority)
{
    if (priority == 1)
        printf("Critical");
    else if (priority == 2)
        printf("Urgent");
    else
        printf("Normal");
}

void addPatient()
{
    if (count == MAX)
    {
        printf("\nQueue is full!\n");
        return;
    }

    struct Patient p;

    printf("\n--- Add New Patient ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);

    for (int i = 0; i < count; i++)
    {
        if (queue[i].id == p.id)
        {
            printf("Patient ID already exists!\n");
            return;
        }
    }

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Medical Condition: ");
    scanf(" %[^\n]", p.condition);

    printf("\nPriority Levels:\n");
    printf("1. Critical\n");
    printf("2. Urgent\n");
    printf("3. Normal\n");

    printf("Enter Priority: ");
    scanf("%d", &p.priority);

    if (p.priority < 1 || p.priority > 3)
    {
        printf("Invalid priority!\n");
        return;
    }

    arrivalCounter++;
    p.arrival = arrivalCounter;

    int position = count;

    for (int i = 0; i < count; i++)
    {
        if (p.priority < queue[i].priority)
        {
            position = i;
            break;
        }
    }

    for (int i = count; i > position; i--)
    {
        queue[i] = queue[i - 1];
    }

    queue[position] = p;
    count++;

    printf("\nPatient added successfully!\n");
}

void treatPatient()
{
    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\n--- Patient Being Treated ---\n");

    printf("Patient ID : %d\n", queue[0].id);
    printf("Name       : %s\n", queue[0].name);
    printf("Age        : %d\n", queue[0].age);
    printf("Condition  : %s\n", queue[0].condition);

    printf("Priority   : ");
    displayPriority(queue[0].priority);
    printf("\n");

    for (int i = 0; i < count - 1; i++)
    {
        queue[i] = queue[i + 1];
    }

    count--;

    printf("\nPatient removed from waiting queue.\n");
}

void displayQueue()
{
    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    printf("\n========== WAITING PATIENTS ==========\n");

    printf("%-10s %-20s %-8s %-25s %-12s\n",
           "ID", "Name", "Age", "Condition", "Priority");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-20s %-8d %-25s ",
               queue[i].id,
               queue[i].name,
               queue[i].age,
               queue[i].condition);

        displayPriority(queue[i].priority);
        printf("\n");
    }
}

void searchPatient()
{
    if (count == 0)
    {
        printf("\nNo patients are waiting.\n");
        return;
    }

    int id;
    int found = 0;

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (queue[i].id == id)
        {
            printf("\n--- Patient Found ---\n");

            printf("Patient ID : %d\n", queue[i].id);
            printf("Name       : %s\n", queue[i].name);
            printf("Age        : %d\n", queue[i].age);
            printf("Condition  : %s\n", queue[i].condition);

            printf("Priority   : ");
            displayPriority(queue[i].priority);
            printf("\n");

            printf("Queue Position : %d\n", i + 1);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nPatient not found!\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n=====================================\n");
        printf("     HOSPITAL QUEUE MANAGEMENT\n");
        printf("=====================================\n");

        printf("1. Add Patient\n");
        printf("2. Treat Next Patient\n");
        printf("3. Display Waiting Patients\n");
        printf("4. Search Patient\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                treatPatient();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                searchPatient();
                break;

            case 5:
                printf("\nExiting Hospital Queue Management System...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
