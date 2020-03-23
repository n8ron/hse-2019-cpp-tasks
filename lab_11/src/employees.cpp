#include "employees.h"
#include <cstdio>
#include <malloc.h>
#include <assert.h>
#include <string.h>

// Creation ----------------------------

Employee::Employee(){
    _name = new char[101];
}

Developer::Developer() : Employee() {}

SalesManager::SalesManager() : Employee() {}

Employee::~Employee(){
    delete [] _name;
}

//--------------------------------------

// Operators----------------------------

//----------Ostream--<<-----------------

std::ostream & operator<<(std::ostream& os, const Employee & employee) {
    return employee << os;
}

std::ostream& SalesManager::operator<<(std::ostream& os) const {
    os << "Sales Manager" << '\n';
    os << "Name: " << _name << '\n';
    os << "Base Salary: " << _base_salary << '\n';
    os << "Sold items: " << _sold_nm << '\n';
    os << "Item price: " << _price << '\n';
    return os;
}

std::ostream& Developer::operator<<(std::ostream& os) const {
    os << "Developer" << '\n';
    os << "Name: " << _name << '\n';
    os << "Base Salary: " << _base_salary << '\n';
    os << "Has bonus: " << (_has_bonus ? "+" : "-") << '\n';
    return os;
}

//-------------------------------------
//---------Istream-->>-----------------

std::istream& operator>>(std::istream& is, Employee & employee) {
    return employee >> is;
}

std::istream& SalesManager::operator>>(std::istream& is) {
    std::string name;
    is >> name >> _base_salary >> _sold_nm >> _price;
    if (name.length() > 99) {
        is.setstate(std::ios::failbit);
    }
    else {
        strcpy(_name, name.c_str());
    }
    return is;
}

std::istream& Developer::operator>>(std::istream& is) {
	std::string name;
    is >> name >> _base_salary;
    if (name.length() > 99) {
        is.setstate(std::ios::failbit);
    }
    else {
        strcpy(_name, name.c_str());
    }
    int has_bonus; 
    is >> has_bonus;
    _has_bonus = has_bonus;
    return is;
}

//----------Ofstream--<<-----------------

std::ofstream & operator<<(std::ofstream& ofs, const Employee & employee) {
    return employee << ofs;
}

std::ofstream& SalesManager::operator<<(std::ofstream& ofs) const {
    int32_t type = 2;
    ofs << write_le_int32(type) 
        << write_c_str(_name)
        << write_le_int32(_base_salary)
        << write_le_int32(_sold_nm)
        << write_le_int32(_price);
    return ofs;
}

std::ofstream& Developer::operator<<(std::ofstream& ofs) const {
    int32_t type = 1;
    ofs << write_le_int32(type) 
        << write_c_str(_name)
        << write_le_int32(_base_salary)
        << write_bool(_has_bonus);
    return ofs;
}
//----------Ifstream-->>-----------------

std::ifstream & operator>>(std::ifstream& ifs, Employee & employee) {
    return employee >> ifs;
}

std::ifstream& SalesManager::operator>>(std::ifstream& ifs) {
    size_t max_size = 100;
    ifs >> read_c_str(_name, max_size)
        >> read_le_int32(_base_salary)
        >> read_le_int32(_sold_nm)
        >> read_le_int32(_price);
    return ifs;
}

std::ifstream& Developer::operator>>(std::ifstream& ifs) {
    size_t max_size = 100;
    ifs >> read_c_str(_name, max_size)
        >> read_le_int32(_base_salary)
        >> read_bool(_has_bonus);
    return ifs;
}

//--------------------------------------
//--------Salary-and-Fail---------------
int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

int Employee::_get_base_salary() {
    return _base_salary;
}

//--------------------------------------
//------EmployeesArray------------------
EmployeesArray::EmployeesArray(size_t capacity) {
    assert(capacity > 0);
    _employees = new Employee * [capacity];
    _size = 0;
    _capacity = capacity;
}

EmployeesArray::~EmployeesArray() {
    for (size_t i = 0; i < _size; i++) {
        delete _employees[i];
    }
    delete [] _employees;
}

void EmployeesArray::add(Employee * e) {
    if (_size  == _capacity) {
        Employee ** temp_array;
        temp_array = new Employee * [2 * _capacity];
        for (size_t i = 0; i < _size; i++) {
             temp_array[i] = _employees[i];
        }
        delete [] _employees;
        _capacity *= 2;
        _employees = temp_array;
    }
    _employees[_size] = e;
    _size++;   
}

int EmployeesArray::total_salary() const {
    int sum_salary = 0;
    for (size_t i = 0; i < _size; i++) {
        sum_salary += _employees[i]->salary();
    }
    return sum_salary;
}
//--------------------------------------

//----ArrayOperator---------------------

std::istream& operator>>(std::istream& is, EmployeesArray & array) {
    return array >> is;
}

std::istream& EmployeesArray::operator>>(std::istream& is) {
    for (size_t i = 0; i < _size; i++) {
        is >> *_employees[i];
    }
    return is;
}

std::ostream & operator<<(std::ostream& os, const EmployeesArray & array) {
    return array << os;
}

std::ostream& EmployeesArray::operator<<(std::ostream& os) const {
    for (size_t i = 0; i < _size; i++) {
        os << i + 1 << ". ";
        os << *_employees[i];
    }
    os << "== Total salary: " << total_salary() << '\n';
    return os;
}

std::ofstream & operator<<(std::ofstream& ofs, const EmployeesArray & array) {
    return array << ofs;
}

std::ofstream& EmployeesArray::operator<<(std::ofstream& ofs) const {
    ofs << write_le_int32(_size);
    for (size_t i = 0; i < _size; i++) {
        ofs << *_employees[i];
    }
    return ofs;
}

//--------------------------------------