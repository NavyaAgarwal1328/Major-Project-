#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_BOOKS 5
#define PASSWORD "1234"

// ----------------- STRUCTURES -----------------

typedef struct {
    int sr;
    char name[50];
    int quantity;
    int left;
} Book;

typedef struct {
    int roll;
    char name[50];
    char course[50];
    int issued;
    int daysSinceIssue;
    char bookName[50];
} Student;

// ----------------- GLOBAL DATA -----------------

Book books[MAX_BOOKS] = {
    {1, "Let Us C", 10, 10},
    {2, "Programming in C", 8, 8},
    {3, "Data Structures", 5, 5},
    {4, "Operating Systems", 6, 6},
    {5, "Computer Networks", 4, 4}
};
int totalBooks = 5;

Student students[MAX_STUDENTS];
int studentCount = 0;

// ----------------- UTILITY -----------------

void printLine() {
    printf("------------------------------------------------------------\n");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// ----------------- PRELOAD STUDENTS -----------------

void preloadStudents() {
    students[0] = (Student){101, "Rohan Sharma", "B.Tech", 1, 5, "Let Us C"};
    students[1] = (Student){102, "Priya Mehta", "BCA", 1, 10, "Data Structures"};
    students[2] = (Student){103, "Ankit Verma", "B.Sc", 1, 2, "Programming in C"};
    students[3] = (Student){104, "Sanya Gupta", "B.Tech", 1, 15, "Operating Systems"};
    students[4] = (Student){105, "Neha Singh", "BCA", 1, 6, "Computer Networks"};
    students[5] = (Student){106, "Aditya Kumar", "B.Com", 1, 3, "Let Us C"};
    students[6] = (Student){107, "Simran Kaur", "B.Sc", 1, 8, "Data Structures"};
    students[7] = (Student){108, "Vikram Joshi", "B.Tech", 1, 4, "Programming in C"};
    students[8] = (Student){109, "Pooja Reddy", "BCA", 1, 1, "Computer Networks"};
    students[9] = (Student){110, "Rahul Mehra", "B.Tech", 1, 12, "Operating Systems"};
    students[10] = (Student){111, "Aman Verma", "B.Sc", 1, 6, "Let Us C"};
    students[11] = (Student){112, "Neha Sharma", "BCA", 1, 9, "Programming in C"};
    students[12] = (Student){113, "Karan Singh", "B.Tech", 1, 2, "Data Structures"};
    students[13] = (Student){114, "Shreya Patel", "BCA", 1, 5, "Computer Networks"};
    students[14] = (Student){115, "Ritika Jain", "B.Sc", 1, 7, "Operating Systems"};
    students[15] = (Student){116, "Arjun Das", "B.Tech", 1, 4, "Let Us C"};

    studentCount = 16;
}

// ----------------- STUDENT FUNCTIONS -----------------

int verifyPassword() {
    char pass[20];
    printf("Enter password for Student Info: ");
    scanf("%s", pass);
    clearBuffer();

    if (strcmp(pass, PASSWORD) == 0) {
        return 1;
    } else {
        printf("Wrong password! Access denied.\n");
        return 0;
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list full!\n");
        return;
    }

    Student s;
    s.issued = 1;

    printf("Enter student roll number: ");
    scanf("%d", &s.roll);
    clearBuffer();

    printf("Enter student name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter student course: ");
    fgets(s.course, 50, stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter book name to issue: ");
    fgets(s.bookName, 50, stdin);
    s.bookName[strcspn(s.bookName, "\n")] = '\0';

    printf("Enter days since book was issued: ");
    scanf("%d", &s.daysSinceIssue);
    clearBuffer();

    // -------------- FIX 1: DECREASE BOOK STOCK --------------
    int found = 0;
    for (int i = 0; i < totalBooks; i++) {
        if (strcmp(books[i].name, s.bookName) == 0) {
            if (books[i].left > 0) {
                books[i].left--;
                found = 1;
            } else {
                printf("No copies available to issue!\n");
                return;
            }
        }
    }
    if (!found) {
        printf("Invalid book name! Try again.\n");
        return;
    }
    // --------------------------------------------------------

    students[studentCount++] = s;
    printf("Book issued to %s successfully!\n", s.name);
}

void viewAllStudents() {
    if (studentCount == 0) {
        printf("No students available.\n");
        return;
    }

    printLine();
    printf("All Students:\n");
    printLine();

    for (int i = 0; i < studentCount; i++) {
        printf("Roll: %d | Name: %s | Course: %s | Book Issued: %s | Days Since Issue: %d\n",
               students[i].roll, students[i].name, students[i].course,
               students[i].bookName, students[i].daysSinceIssue);
    }
}

void recentlyIssued() {
    printLine();
    printf("Students who issued book within a week:\n");
    printLine();

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].issued == 1 && students[i].daysSinceIssue <= 7) {
            printf("Roll: %d | Name: %s | Book: %s | Days: %d\n",
                   students[i].roll, students[i].name,
                   students[i].bookName, students[i].daysSinceIssue);
            found = 1;
        }
    }
    if (!found)
        printf("None.\n");
}

void lateStudents() {
    printLine();
    printf("Late students (Fine = ₹10/day after 7 days):\n");
    printLine();

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].issued == 1 && students[i].daysSinceIssue > 7) {
            int extraDays = students[i].daysSinceIssue - 7;
            int fine = extraDays * 10;

            printf("Roll: %d | Name: %s | Book: %s | Late by %d days | Fine = ₹%d\n",
                   students[i].roll, students[i].name,
                   students[i].bookName, extraDays, fine);
            found = 1;
        }
    }
    if (!found)
        printf("None.\n");
}

void showDetailedStudents() {
    viewAllStudents();

    printf("\nDo you want to SEARCH a student? (1=Yes, 0=No): ");
    int ch;
    scanf("%d", &ch);
    clearBuffer();

    if (ch == 1) {
        char key[50];
        printf("Enter name / roll / course to search: ");
        fgets(key, 50, stdin);
        key[strcspn(key, "\n")] = '\0';

        printLine();
        printf("Search Results:\n");
        printLine();

        int found = 0;
        for (int i = 0; i < studentCount; i++) {
            char rollStr[10];
            sprintf(rollStr, "%d", students[i].roll);

            if (strstr(students[i].name, key) ||
                strstr(rollStr, key) ||
                strstr(students[i].course, key)) {

                printf("Roll: %d | Name: %s | Course: %s | Book: %s | Days: %d\n",
                       students[i].roll, students[i].name,
                       students[i].course, students[i].bookName,
                       students[i].daysSinceIssue);
                found = 1;
            }
        }
        if (!found)
            printf("No match found.\n");
    }
}

// ----------------- BOOK FUNCTIONS -----------------

void showAllBooks() {
    printLine();
    printf("ALL BOOKS:\n");
    printLine();

    for (int i = 0; i < totalBooks; i++) {
        printf("%d | %s | Total: %d | Left: %d\n",
               books[i].sr, books[i].name, books[i].quantity, books[i].left);
    }
}

void showAvailableBooks() {
    printLine();
    printf("AVAILABLE BOOKS:\n");
    printLine();

    for (int i = 0; i < totalBooks; i++) {
        if (books[i].left > 0) {
            printf("%d | %s | Left: %d\n",
                   books[i].sr, books[i].name, books[i].left);
        }
    }
}

void searchBook() {
    char key[50];
    printf("Enter book name / sr number to search: ");
    fgets(key, 50, stdin);
    key[strcspn(key, "\n")] = '\0';

    printLine();
    printf("Search results:\n");
    printLine();

    int found = 0;
    for (int i = 0; i < totalBooks; i++) {
        char srStr[10];
        sprintf(srStr, "%d", books[i].sr);

        if (strstr(books[i].name, key) || strstr(srStr, key)) {
            printf("%d | %s | Total: %d | Left: %d\n",
                   books[i].sr, books[i].name,
                   books[i].quantity, books[i].left);
            found = 1;
        }
    }
    if (!found)
        printf("No match found.\n");
}

void issueBookToStudent() {
    addStudent();
}

// ------------------ FIX 2: CORRECT RETURN SYSTEM ------------------

void returnBook() {
    int roll;
    printf("Enter student roll to return book: ");
    scanf("%d", &roll);
    clearBuffer();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].roll == roll && students[i].issued == 1) {

            for (int j = 0; j < totalBooks; j++) {
                if (strcmp(books[j].name, students[i].bookName) == 0) {
                    books[j].left++;
                    break;
                }
            }

            printf("Book '%s' returned by %s successfully!\n",
                   students[i].bookName, students[i].name);

            students[i].issued = 0;
            students[i].daysSinceIssue = 0;
            strcpy(students[i].bookName, "None");
            return;
        }
    }

    printf("No issued book record found for this roll!\n");
}
// -------------------------------------------------------------------

void studentMenu() {
    if (!verifyPassword()) return;

    int choice;
    while (1) {
        printLine();
        printf("STUDENT INFO\n");
        printLine();
        printf("1. View All Students\n");
        printf("2. Recently Issued (Within a week)\n");
        printf("3. Late Students\n");
        printf("4. Detailed Student Info + Search\n");
        printf("5. Issue Book / Add Student\n");
        printf("0. Back\n");
        printLine();
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: viewAllStudents(); break;
            case 2: recentlyIssued(); break;
            case 3: lateStudents(); break;
            case 4: showDetailedStudents(); break;
            case 5: issueBookToStudent(); break;
            case 0: return;
            default: printf("Invalid!\n");
        }
    }
}

void bookMenu() {
    int choice;
    while (1) {
        printLine();
        printf("BOOK INFO\n");
        printLine();
        printf("1. Show All Books\n");
        printf("2. Show Available Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("0. Back\n");
        printLine();
        printf("Enter: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: showAllBooks(); break;
            case 2: showAvailableBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBookToStudent(); break;
            case 5: returnBook(); break;
            case 0: return;
            default: printf("Invalid!\n");
        }
    }
}

int main() {
    preloadStudents();

    int choice;
    while (1) {
        printLine();
        printf("       LIBRARY MANAGEMENT\n");
        printLine();
        printf("1. Student Info\n");
        printf("2. Book Info\n");
        printf("3. Exit\n");
        printLine();
        printf("Enter choice: ");

        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: studentMenu(); break;
            case 2: bookMenu(); break;
            case 3: printf("Goodbye!\n"); return 0;
            default: printf("Invalid!\n");
        }
    }
}