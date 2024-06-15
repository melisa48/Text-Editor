#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class TextEditor {
private:
    vector<string> lines;
    stack<vector<string>> undoStack;
    stack<vector<string>> redoStack;
    string clipboard;

public:
    void createNewFile(const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            cout << "New file '" << fileName << "' created successfully.\n";
            file.close();
        } else {
            cerr << "Error: Unable to create file '" << fileName << "'.\n";
        }
    }

    void openFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            lines.clear();
            string line;
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
            cout << "File '" << fileName << "' opened successfully.\n";
        } else {
            cerr << "Error: Unable to open file '" << fileName << "'.\n";
        }
    }

    void saveFile(const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& line : lines) {
                file << line << endl;
            }
            cout << "Changes saved to file '" << fileName << "'.\n";
            file.close();
        } else {
            cerr << "Error: Unable to save changes to file '" << fileName << "'.\n";
        }
    }

    void copyText(const string& text) {
        clipboard = text;
        cout << "Text copied to clipboard.\n";
    }

    void cutText(string& text) {
        clipboard = text;
        text.clear();
        cout << "Text cut and copied to clipboard.\n";
    }

    void pasteText(string& text) {
        text += clipboard;
        cout << "Text pasted from clipboard.\n";
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(lines);
            lines = undoStack.top();
            undoStack.pop();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(lines);
            lines = redoStack.top();
            redoStack.pop();
        }
    }

    void displayText() const {
        for (size_t i = 0; i < lines.size(); ++i) {
            cout << "[" << i + 1 << "] " << lines[i] << endl;
        }
    }

    void addText(const string& text) {
        undoStack.push(lines);
        lines.push_back(text);
        redoStack = stack<vector<string>>(); // Clear redo stack
    }

    void findAndReplace(const string& findStr, const string& replaceStr) {
        undoStack.push(lines);
        for (auto& line : lines) {
            size_t startPos = 0;
            while ((startPos = line.find(findStr, startPos)) != string::npos) {
                line.replace(startPos, findStr.length(), replaceStr);
                startPos += replaceStr.length();
            }
        }
        redoStack = stack<vector<string>>(); // Clear redo stack
    }
};

void displayMenu() {
    cout << "\nText Editor Menu:\n";
    cout << "1. Create New File\n";
    cout << "2. Open File\n";
    cout << "3. Save File\n";
    cout << "4. Add Text\n";
    cout << "5. Display Text\n";
    cout << "6. Copy Text\n";
    cout << "7. Cut Text\n";
    cout << "8. Paste Text\n";
    cout << "9. Undo\n";
    cout << "10. Redo\n";
    cout << "11. Find and Replace\n";
    cout << "12. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    TextEditor editor;
    string fileName, text, findStr, replaceStr;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // To clear the newline character from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                getline(cin, fileName);
                editor.createNewFile(fileName);
                break;
            case 2:
                cout << "Enter file name: ";
                getline(cin, fileName);
                editor.openFile(fileName);
                break;
            case 3:
                cout << "Enter file name: ";
                getline(cin, fileName);
                editor.saveFile(fileName);
                break;
            case 4:
                cout << "Enter text: ";
                getline(cin, text);
                editor.addText(text);
                break;
            case 5:
                editor.displayText();
                break;
            case 6:
                cout << "Enter text to copy: ";
                getline(cin, text);
                editor.copyText(text);
                break;
            case 7:
                cout << "Enter text to cut: ";
                getline(cin, text);
                editor.cutText(text);
                break;
            case 8:
                cout << "Enter text to paste: ";
                getline(cin, text);
                editor.pasteText(text);
                break;
            case 9:
                editor.undo();
                break;
            case 10:
                editor.redo();
                break;
            case 11:
                cout << "Enter text to find: ";
                getline(cin, findStr);
                cout << "Enter text to replace with: ";
                getline(cin, replaceStr);
                editor.findAndReplace(findStr, replaceStr);
                break;
            case 12:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 12);

    return 0;
}
