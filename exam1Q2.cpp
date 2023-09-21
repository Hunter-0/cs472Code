#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
struct S {

    string firstName;

    string lastName;

    string address;

};


struct HashS {
    size_t operator()(const S& s) const noexcept
    {
        size_t hash1 = hash<string>{}(s.firstName);
        size_t hash2 = hash<string>{}(s.lastName);
        size_t hash3 = hash<string>{}(s.address);
        return hash1 ^ hash2 ^ hash3;
    }
};


int main()
{
    S data;
    cout<<"Enter First Name: ";
    cin>>data.firstName;

    cout<<"Enter Last Name: ";
    cin>>data.lastName;

    cout<<"Enter Address: ";
    cin>>data.address;

    HashS hasher;
    size_t hash_value = hasher(data);
    cout << "Hash Value from inputs: "<<hash_value<<endl;

    return 0;
}