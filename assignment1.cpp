#include <iostream>
#include <fstream> 
#include <string>
#include "tree.h"  

using namespace std;

Tree<string> loadDeck(const string& filename) {
    Tree<string> tree;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        tree = tree.insert(line);
    }
    return tree;
}

void saveDeck(const Tree<string>& tree, const string& filename) {
    ofstream file(filename);
    tree.preorder([&file](const string& data) {
        file<<data<<endl;
    });
}


int displayMenu() {
  int choice;
  cout<<"\nIndex Card Manager Menu"<<endl;
  cout<<"Select one of the following:"<<endl;
  cout<<"1 - Enter a card into the deck"<<endl;
  cout<<"2 - Search for a card in the deck by keyword"<<endl;
  cout<<"3 - Save deck to file"<<endl;
  cout<<"4 - Exit program"<<endl;
  cout<<"Choice: ";
  cin>>choice;
  return choice;
}

int main() {
    Tree<string> cardDeck; 
    cardDeck = loadDeck("index_cards.txt");

    while (true) {
        int menuChoice = displayMenu();

        if (menuChoice == 1) {
            cout << "Enter the data of the card: ";
            string cardData;
            cin.ignore(); 
            getline(cin, cardData);
            cardDeck = cardDeck.insert(cardData);
            cout<<cardData + " has been inserted into the deck."<<endl;
        }

        else if (menuChoice == 2) {
            cout << "Enter a keyword to search for in the deck: ";
            string key;
            cin.ignore(); 
            getline(cin, key);
            int found = 0;
            cardDeck.preorder([&](const string& data) {
                if (data.find(key) != string::npos) {
                    cout<<"Card: "<<data<<endl;
                    found = 1;
                }});
            if (found == 0){
                cout <<"Nothing was found using your keyword."<<endl;
            }
        }

        else if (menuChoice == 3) {
            saveDeck(cardDeck, "indexCards.txt");
            cout<<"Cards saved to deck on file."<<endl;
        } 
    
        else if (menuChoice == 4) {
            cout<<"Program shutting down."<<endl;
            break;
        } 

        else {
            cout<<"Incorrect choice. Enter a number 1-4."<<endl;
        }
    }

    return 0;
}
