#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

// Structure for Feedback Node
struct Feedback {
    int feedbackID; // Unique ID for each feedback
    string type;
    string subType;
    string category;
    string content;
    int points;
    Feedback* next;
};

// Class for Feedback Analyzer
class FeedbackAnalyzer {
private:
    map<string, Feedback*> userFeedbackMap; // Stores feedback list for each user
    priority_queue<pair<int, string>> leaderboard; // Points with username
    stack<Feedback*> undoStack;
    int categoryCounts[3]; // Suggestions, Complaints, Appreciations
    int totalFeedbacks;
    const string usersFile = "users.txt";
    string currentBadge;
    int feedbackCounter; // Counter for generating unique feedback IDs

    // Fun Facts
    string funFacts[5] = {
        "Did you know? Feedback boosts team productivity by 12%!",
        "Fun Fact: Constructive feedback improves retention by 30%.",
        "Feedback Tip: Appreciations create stronger relationships!",
        "Random Fact: The first use of 'feedback' was in 1920 for engineering.",
        "Fun Fact: Feedback loops are critical in AI learning models!"
    };

    // Trivia Questions
    string triviaQuestions[3] = {
        "What year was the term 'feedback' first used?\n1. 1920\n2. 1950\n3. 1880\n",
        "What category of feedback is known to improve relationships?\n1. Complaints\n2. Suggestions\n3. Appreciations\n",
        "How much can constructive feedback improve retention?\n1. 10%\n2. 30%\n3. 50%\n"
    };
    int triviaAnswers[3] = {1, 3, 2}; // Correct answers for the trivia questions

    // Helper Methods
    int calculatePoints(const string& content, const string& category) {
        int wordCount = 0;
        bool inWord = false;
        for (char c : content) {
            if (isspace(c)) {
                if (inWord) wordCount++;
                inWord = false;
            } else {
                inWord = true;
            }
        }
        if (inWord) wordCount++;

        int points;

    if (wordCount <= 10) {
    points = 5;
    } else if (wordCount <= 30) {
    points = 10;
    } else {
    points = 20;
    }

    if (category == "Appreciations") {
    points += 5;
    } else if (category == "Suggestions") {
    points += 3;
    }

    return points;
    }

    void updateAnalytics(const string& category, int increment) {
        if (category == "Suggestions") categoryCounts[0] += increment;
        else if (category == "Complaints") categoryCounts[1] += increment;
        else if (category == "Appreciations") categoryCounts[2] += increment;
    }

    void unlockBadge(int points) {
        if (points >= 20) currentBadge = "Insight Master";
        else if (points >= 10) currentBadge = "Feedback Guru";
        else if (points >= 5) currentBadge = "Rookie Analyst";
        cout << "You unlocked a new badge: " << currentBadge << "!\n";
    }

    void displayFunFact() {
        int index = rand() % 5;
        cout << "Fun Fact: " << funFacts[index] << endl;
    }

    void triviaQuiz(const string& username) {
        int questionIndex = rand() % 3;
        cout << "Trivia Time!\n";
        cout << triviaQuestions[questionIndex];
        cout << "Enter your answer: ";
        int userAnswer;
        cin >> userAnswer;

        if (userAnswer == triviaAnswers[questionIndex]) {
            cout << "Correct! You earned 10 bonus points!\n";

            // Add bonus points to all feedback for consistency
            Feedback* temp = userFeedbackMap[username];
            while (temp) {
                temp->points += 10;
                temp = temp->next;
            }

            // Re-evaluate and update badge
            unlockBadge(10); // Unlock a badge based on bonus points

            // Refresh leaderboard
            leaderboard.push({10, username});
        } else {
            cout << "Oops! The correct answer was option " << triviaAnswers[questionIndex] << ".\n";
        }
    }

public:
    FeedbackAnalyzer() {
    totalFeedbacks = 0;
    currentBadge = "No Badge";
    feedbackCounter = 1;

    // Initialize categoryCounts array
    for (int i = 0; i < 3; i++) {
        categoryCounts[i] = 0;
    }

    // Seed the random number generator
    srand(time(0));
}
    
    // Function to set console colors
    void setConsoleColor(const string& colorCode) {
        string command = "COLOR " + colorCode;
        system(command.c_str());
    }

    // Function to animate text
    void printAnimatedText(const string& text, int delayMs = 50) {
        for (char c : text) {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(delayMs));
        }
        cout << endl;
    }

    // Function to display welcome screen
    void welcomeScreen() {
        setConsoleColor("80"); 
        system("CLS");

        printAnimatedText("****************************************************", 10);
        printAnimatedText("*                                                  *", 10);
        printAnimatedText("*    ~~~~~Welcome to Gamified Feedback!~~~~~       *", 50);
        printAnimatedText("*                                                  *", 10);
        printAnimatedText("****************************************************", 10);
        printAnimatedText("*           Boost Your Feedback Game!              *", 50);
        printAnimatedText("****************************************************", 10);
    }

    // User Sign-Up
    void signUp() {
        string username, email, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter email: "<<endl;
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        ifstream inFile(usersFile);
        string line;
        while (getline(inFile, line)) {
            if (line.substr(0, line.find('|')) == username) {
                cout << "Username already exists.\n";
                inFile.close();
                return;
            }
        }
        inFile.close();
[[]]
        ofstream outFile(usersFile, ios::app);
        outFile << username << "|" << email << "|" << password << "\n";
        outFile.close();
        cout << "Account created successfully!\n";
    }

    // User Login
    bool login(string& username) {
        string password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream inFile(usersFile);
        string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');
            string fileUsername = line.substr(0, pos1);
            string filePassword = line.substr(pos2 + 1);
            if (fileUsername == username && filePassword == password) {
                cout << "Login successful!\n";
                inFile.close();
                return true;
            }
        }
        inFile.close();
        cout << "Invalid username or password.\n";
        return false;
    }

    // Clear user data
    void clearUserData() {
        ofstream outFile(usersFile, ios::trunc); // Open file in truncate mode to clear all data
        outFile.close();
        cout << "All user data has been cleared successfully!\n";
    }

       // Submit Feedback
    void submitFeedback(const string& username) {
        string type, subType, category, content;
        int points;

        cout << "Select feedback type:\n";
        cout << "1. University\n2. App\n3. Service\n4. Custom\n";
        cout << "Enter your choice: ";
        int feedbackTypeChoice;
        cin >> feedbackTypeChoice;

        switch (feedbackTypeChoice) {
            case 1:
                type = "University";
                cout << "Select sub-type:\n";
                cout << "1. IT Department\n2. Management\n3. Professors\n";
                cout << "Enter your choice: ";
                int uniChoice;
                cin >> uniChoice;
                if (uniChoice == 1) subType = "IT Department";
                else if (uniChoice == 2) subType = "Management";
                else if (uniChoice == 3) subType = "Professors";
                else {
                    cout << "Invalid choice. Defaulting to 'General'.\n";
                    subType = "General";
                }
                break;

            case 2:
                type = "App";
                cout << "Select sub-type:\n";
                cout << "1. Task Manager\n2. Fitness Tracker\n3. Budget Planner\n";
                cout << "Enter your choice: ";
                int appChoice;
                cin >> appChoice;
                if (appChoice == 1) subType = "Task Manager";
                else if (appChoice == 2) subType = "Fitness Tracker";
                else if (appChoice == 3) subType = "Budget Planner";
                else {
                    cout << "Invalid choice. Defaulting to 'General'.\n";
                    subType = "General";
                }
                break;

            case 3:
                type = "Service";
                cout << "Select sub-type:\n";
                cout << "1. Customer Support\n2. Delivery\n3. Maintenance\n";
                cout << "Enter your choice: ";
                int serviceChoice;
                cin >> serviceChoice;
                if (serviceChoice == 1) subType = "Customer Support";
                else if (serviceChoice == 2) subType = "Delivery";
                else if (serviceChoice == 3) subType = "Maintenance";
                else {
                    cout << "Invalid choice. Defaulting to 'General'.\n";
                    subType = "General";
                }
                break;

            case 4:
                type = "Custom";
                subType = "N/A";
                category = "N/A";
                break;

            default:
                cout << "Invalid feedback type. Setting type to 'Custom'.\n";
                type = "Custom";
                subType = "N/A";
                category = "N/A";
                break;
        }

       if (type != "Custom") {
    cout << "Enter category (Suggestions/Complaints/Appreciations): ";
    cin.ignore();
    getline(cin, category);

    // Validate category input
    if (category.empty()) {
        cout << "No category entered. Feedback submission cancelled.\n";
        return; // Exit the function without submitting feedback
    }

    // Optional: Ensure the category is one of the valid options
    if (category != "Suggestions" && category != "Complaints" && category != "Appreciations") {
        cout << "Invalid category entered. Feedback submission cancelled.\n";
        return; // Exit the function without submitting feedback
    }
}

        cout << "Enter feedback content: ";
        cin.ignore();
        getline(cin, content);

        points = calculatePoints(content, category);
        updateAnalytics(category, 1);


        Feedback* newFeedback = new Feedback{feedbackCounter++, type, subType, category, content, points, nullptr};

        undoStack.push(newFeedback);

        // Add feedback to the user's list
        if (userFeedbackMap[username] == nullptr) {
            userFeedbackMap[username] = newFeedback;
        } else {
            Feedback* temp = userFeedbackMap[username];
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newFeedback;
        }

        leaderboard.push({points, username});
        totalFeedbacks++;

        cout << "Feedback submitted successfully! You earned " << points << " points.\n";
        unlockBadge(points);
        displayFunFact();
        triviaQuiz(username); // Call updated trivia quiz with username
    }

    void undoLastFeedback(const string& username) {
    if (undoStack.empty()) {
        cout << "No feedback to undo.\n";
        return;
    }

    // Retrieve the last feedback from the stack
    Feedback* lastFeedback = undoStack.top();
    undoStack.pop();

    // Remove it from the user's feedback list
    Feedback* current = userFeedbackMap[username];
    Feedback* prev = nullptr;

    while (current) {
        if (current == lastFeedback) {
            if (prev) {
                prev->next = current->next;
            } else {
                userFeedbackMap[username] = current->next;
            }

            // Update analytics
            updateAnalytics(current->category, -1);
            totalFeedbacks--;

            delete current;
            cout << "Last feedback undone successfully!\n";
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Error: Unable to find the feedback in the user's list.\n";
}

   
    // Display Leaderboard
    void displayLeaderboard() {
        if (leaderboard.empty()) {
            cout << "Leaderboard is empty.\n";
            return;
        }

        cout << "\nLeaderboard Rankings:\n";
        priority_queue<pair<int, string>> tempLeaderboard = leaderboard;
        int rank = 1;

        while (!tempLeaderboard.empty()) {
            auto entry = tempLeaderboard.top();
            tempLeaderboard.pop();
            cout << rank++ << ". " << entry.second << " - " << entry.first << " points\n";
        }
    }

    void displayFeedbackHistory(const string& username) {
        if (userFeedbackMap[username] == nullptr) {
            cout << "No feedback history available for this user.\n";
            return;
        }

        Feedback* temp = userFeedbackMap[username];
        while (temp) {
            cout << "\nID: " << temp->feedbackID;
            cout << "\nType: " << temp->type;
            cout << "\nSub-Type: " << temp->subType;
            cout << "\nCategory: " << temp->category;
            cout << "\nContent: " << temp->content;
            cout << "\nPoints: " << temp->points;
            cout << "\n-------------------------\n";
            temp = temp->next;
        }
    }

    void displayAnalytics() {
        if (totalFeedbacks == 0) {
            cout << "No feedback data available for analytics.\n";
            return;
        }

        cout << "Real-Time Analytics:\n";
        cout << "Suggestions: " << (categoryCounts[0] * 100) / totalFeedbacks << "%\n";
        cout << "Complaints: " << (categoryCounts[1] * 100) / totalFeedbacks << "%\n";
        cout << "Appreciations: " << (categoryCounts[2] * 100) / totalFeedbacks << "%\n";
    }

    // Delete Feedback by ID
    void deleteFeedbackByID(const string& username, int feedbackID) {
        if (userFeedbackMap[username] == nullptr) {
            cout << "No feedback to delete.\n";
            return;
        }

        Feedback* current = userFeedbackMap[username];
        Feedback* prev = nullptr;

        while (current) {
            if (current->feedbackID == feedbackID) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    userFeedbackMap[username] = current->next;
                }

                // Update analytics
                updateAnalytics(current->category, -1);
                totalFeedbacks--;

                delete current;
                cout << "Feedback with ID " << feedbackID << " deleted successfully!\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "No feedback found with ID " << feedbackID << ".\n";
    }
};

// Main Menu
void mainMenu() {
    FeedbackAnalyzer analyzer;
    analyzer.welcomeScreen();

    string username;

    while (true) {
        cout << "1. Login\n2. Sign-Up\n3. Clear User Data\n4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (analyzer.login(username)) {
                    break; // Proceed to feedback system
                }
                continue;
            case 2:
                analyzer.signUp();
                continue;
            case 3:
                analyzer.clearUserData();
                continue;
            case 4:
                cout << "Exiting... Thank you for using Gamified Feedback Analyzer!\n";
                return;
            default:
                cout << "Invalid choice.\n";
        }

        while (true) {
            cout << "\nMain Menu:\n";
            cout << "1. Submit Feedback\n";
            cout << "2. View Feedback History\n";
            cout << "3. Display Analytics\n";
            cout << "4. Display Leaderboard\n";
            cout << "5. Delete Feedback by ID\n";
            cout << "6. Undo Last Feedback\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice) {
                case 1:
                    analyzer.submitFeedback(username);
                    break;
                case 2:
                    analyzer.displayFeedbackHistory(username);
                    break;
                case 3:
                    analyzer.displayAnalytics();
                    break;
                case 4:
                    analyzer.displayLeaderboard();
                    break;
                case 5: {
                    int feedbackID;
                    cout << "Enter the Feedback ID to delete: ";
                    cin >> feedbackID;
                    analyzer.deleteFeedbackByID(username, feedbackID);
                    break;
                }
                case 6: // Undo Last Feedback
                 analyzer.undoLastFeedback(username);
                    break;
                case 7:
                    cout << "Returning to Main Menu...\n";
                    goto MainMenu;
                default:
                    cout << "Invalid choice.\n";
            }
        }

        MainMenu:
        continue; 
    }
}

int main() {
    mainMenu();
    return 0;
}
