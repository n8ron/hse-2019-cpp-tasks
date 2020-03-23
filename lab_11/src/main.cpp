#include "employees.h"	
#include "bin_manip.h"
#include <sstream>
#include <assert.h>

Employee * create_employee(int type) {
    Employee * added_employee;
    if (type == Employee::Type::developer) { 
        added_employee = new Developer; 
    }
    else if (type == Employee::Type::sales_manager) { 
        added_employee = new SalesManager;
    }
    return added_employee;
}

void add(EmployeesArray & Database) {
    int type;
    std::cin >> type;

    Employee * added_employee = create_employee(type);
    std::cin >> *added_employee;
    if (!std::cin.fail()) {
        Database.add(added_employee);
    }
    else {
        delete added_employee;
        std::cout << "Incorrect Data\n";
        delete &Database; 
        std::abort();
    }
}

void load(EmployeesArray & Database) {
    std::string FileName;
    std::cin >> FileName;
    std::ifstream fin;
    fin.open(FileName);
    int32_t number_of_employee = 0;
    int32_t type;
    fin >> read_le_int32(number_of_employee);
    for (int32_t i = 0; i < number_of_employee; i++) {
        fin >> read_le_int32(type);
        if ((type != Employee::Type::developer) && (type != Employee::Type::sales_manager)) {
            std::cout << "Type of " << i + 1 << " employee is incorrect\n";
        }
        else {
            Employee * added_employee = create_employee(type);
            fin >> *added_employee; 
            Database.add(added_employee);
        } 
    } 
    if (fin.fail()) {
        std::cout << "Incorrect Data\n";
        delete &Database; 
        std::abort();
    }
    fin.close();
}

void save(EmployeesArray & Database) {
    std::string FileName;
    std::cin >> FileName;
    std::ofstream fout;
    fout.open(FileName);
    fout << Database;
    fout.close();
}
int main() {
    bool is_finish = false;
    EmployeesArray * Database = new EmployeesArray();
    std::string command;
    while (!is_finish) {
        std::cin >> command;
        if (command == "exit") {
            is_finish = true;
        }
        else if (command == "add") {
            add(*Database);     
        }
        else if (command == "load") {
            load(*Database);       
        }
        else if (command == "save") {
            save(*Database);
        }
        else if (command == "list") {
            std::cout << *Database << '\n';
        }
    }  
    delete Database; 
}