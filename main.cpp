#include <iostream>
#include <mysql.h>
#include <sstream> // Include for stringstream

using namespace std;

// Global function prototypes
void addUser(MYSQL *conn);
void viewUsers(MYSQL *conn);
void deleteUser(MYSQL *conn);
void addExam(MYSQL *conn);
void viewExams(MYSQL *conn);
void deleteExam(MYSQL *conn);

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cerr << "mysql_init() failed\n";
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "127.0.0.1", "root", "123456", "OnlineExamSystem", 3306, NULL, 0) == NULL) {
        cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    int choice;
    while (true) {
        cout << "Online Exam System Menu:\n";
        cout << "1. Add User\n";
        cout << "2. View Users\n";
        cout << "3. Delete User\n";
        cout << "4. Add Exam\n";
        cout << "5. View Exams\n";
        cout << "6. Delete Exam\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addUser(conn);
                break;
            case 2:
                viewUsers(conn);
                break;
            case 3:
                deleteUser(conn);
                break;
            case 4:
                addExam(conn);
                break;
            case 5:
                viewExams(conn);
                break;
            case 6:
                deleteExam(conn);
                break;
            case 7:
                mysql_close(conn);
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void addUser(MYSQL *conn) {
    string username, password, role;
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);
    cout << "Enter Role (Admin/Student): ";
    getline(cin, role);

    string query = "INSERT INTO Users (Username, Password, Role) VALUES ('" + username + "', '" + password + "', '" + role + "')";
    if (mysql_query(conn, query.c_str())) {
        cerr << "INSERT error: " << mysql_error(conn) << endl;
    } else {
        cout << "User added successfully.\n";
    }
}

void viewUsers(MYSQL *conn) {
    if (mysql_query(conn, "SELECT * FROM Users")) {
        cerr << "SELECT error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        cerr << "STORE RESULT error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        cout << "UserID: " << row[0]
             << ", Username: " << row[1]
             << ", Role: " << row[3] << endl;
    }

    mysql_free_result(res);
}

void deleteUser(MYSQL *conn) {
    int userId;
    cout << "Enter UserID to delete: ";
    cin >> userId;
    cin.ignore();

    stringstream ss;
    ss << userId;
    string userIdStr = ss.str();

    string query = "DELETE FROM Users WHERE UserID = " + userIdStr;
    if (mysql_query(conn, query.c_str())) {
        cerr << "DELETE error: " << mysql_error(conn) << endl;
    } else {
        cout << "User deleted successfully.\n";
    }
}

void addExam(MYSQL *conn) {
    string examName;
    int duration, totalMarks;

    cout << "Enter Exam Name: ";
    getline(cin, examName);
    cout << "Enter Duration (minutes): ";
    cin >> duration;
    cout << "Enter Total Marks: ";
    cin >> totalMarks;
    cin.ignore();

    stringstream ss;
    ss << duration;
    string durationStr = ss.str();
    ss.str(""); // Clear stringstream
    ss << totalMarks;
    string totalMarksStr = ss.str();

    string query = "INSERT INTO Exams (ExamName, Duration, TotalMarks) VALUES ('" + examName + "', " + durationStr + ", " + totalMarksStr + ")";
    if (mysql_query(conn, query.c_str())) {
        cerr << "INSERT error: " << mysql_error(conn) << endl;
    } else {
        cout << "Exam added successfully.\n";
    }
}

void viewExams(MYSQL *conn) {
    if (mysql_query(conn, "SELECT * FROM Exams")) {
        cerr << "SELECT error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        cerr << "STORE RESULT error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        cout << "ExamID: " << row[0]
             << ", ExamName: " << row[1]
             << ", Duration: " << row[2] << " minutes"
             << ", TotalMarks: " << row[3] << endl;
    }

    mysql_free_result(res);
}

void deleteExam(MYSQL *conn) {
    int examId;
    cout << "Enter ExamID to delete: ";
    cin >> examId;
    cin.ignore();

    stringstream ss;
    ss << examId;
    string examIdStr = ss.str();

    string query = "DELETE FROM Exams WHERE ExamID = " + examIdStr;
    if (mysql_query(conn, query.c_str())) {
        cerr << "DELETE error: " << mysql_error(conn) << endl;
    } else {
        cout << "Exam deleted successfully.\n";
    }
}

