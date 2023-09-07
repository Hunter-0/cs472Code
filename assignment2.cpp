#include <iostream>
#include <string>
#include <memory>
#include "rope.h"
using namespace std;
// https://www.geeksforgeeks.org/ropes-data-structure-fast-string-concatenation/
// https://iq.opengenus.org/rope-data-structure/
// https://www.geeksforgeeks.org/stl-ropes-in-c/
// https://www.boost.org/sgi/stl/Rope.html
// https://github.com/alaroldai/cpp-rope
void printMenu() {
    cout<<"Choose an option:"<<endl;
    cout<<"1 - Insert"<<endl;
    cout<<"2 - Delete"<<endl;
    cout<<"3 - Split"<<endl;
    cout<<"4 - Exit"<<endl;
}

int main() {
    string userString;
    cout<<"Enter your Rope string: ";
    getline(cin, userString);
    Rope rope(userString);

    while (true) {
        cout<<"Your rope: "<<rope.subrope(1, rope.getLength())<<endl;
        printMenu();
        char userInput;
        cin >> userInput;
        cin.ignore();

        if (userInput == '4') {
            break;
        } else if (userInput == '1') {
            int pos;
            string insertText;
            cout<<"Choose the position to insert: ";
            cin >> pos;
            cin.ignore();
            cout<<"Enter text to insert: ";
            getline(cin, insertText);
            rope.insert(pos, insertText);
        } else if (userInput == '2') {
            int start, length;
            cout<<"Choose the position to delete: ";
            cin >> start;
            cin.ignore();
            cout<<"Choose length to delete: ";
            cin >> length;
            cin.ignore();
            rope.deleteRope(start, length);
        } else if (userInput == '3') {
            int splitPos;
            cout<<"Choose the position to split: ";
            cin >> splitPos;
            cin.ignore();
            rope.split(splitPos);
        } else {
            cout<<"Error in input, enter an option 1-4"<<endl;
        }
    }


    return 0;
}
