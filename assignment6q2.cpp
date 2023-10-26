#include <iostream>
#include <string>
using namespace std;
//  https://refactoring.guru/design-patterns/factory-method
//  https://refactoring.guru/design-patterns/factory-method/cpp/example
struct Office {
    string m_street;
    string m_city;
    int32_t m_cubicle;
};

class Employee {
private:
    string m_name;
    Office* m_office;

    Employee(string n, Office* o) : m_name(n), m_office(o) {}

public:
    Employee(const Employee& rhs) : m_name(rhs.m_name), m_office(new Office{ *rhs.m_office }) {}

    Employee& operator=(const Employee& rhs) {
        if (this == &rhs) return *this;
        m_name = rhs.m_name;
        m_office = new Office{ *rhs.m_office };
        return *this;
    }
    ~Employee() {
        delete m_office;
    }

    friend ostream& operator<<(ostream& os, const Employee& o) {
        return os<<o.m_name<<" works at "<<o.m_office->m_street<<" "<<o.m_office->m_city<<" seats @"<<o.m_office->m_cubicle;       
    }

    friend class EmployeeFactory;
};

class EmployeeFactory {
public:
   static Employee addEmployee(const std::string& name, const std::string& street, const std::string& city, int cubicle) {
    return Employee(name, new Office{ street, city, cubicle });
}

};

int main() {
    Employee hunter = EmployeeFactory::addEmployee("Hunter Elkins", "789 Rocky Rd", "Little Rock", 115);
    Employee gabe = EmployeeFactory::addEmployee("Gabe Gabesen", "105 Circle St", "Dallas", 309);
    Employee karen = EmployeeFactory::addEmployee("Karen Smith", "102 Circle St", "Dallas", 215);

    cout<<hunter<<endl;
    cout<<gabe<<endl;
    cout<<karen<<endl;

    return 0;
}
