#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include "bin_manip.h"
#include <iostream>
#include <fstream>

class Employee {
public:
    Employee();
    virtual ~Employee();
    virtual int salary() const = 0;
    Employee & operator=(Employee &) = delete;
    Employee (Employee & ) = delete;
    int32_t _get_base_salary();
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
    virtual std::istream& operator>>(std::istream& is) = 0;
    virtual std::ofstream& operator<<(std::ofstream& ofs) const = 0; 
    virtual std::ifstream& operator>>(std::ifstream& ifs) = 0;
    enum Type {
        sales_manager = 2,
        developer = 1
    };
protected:
    char *_name;
    int32_t _base_salary = 0;  
};

std::ostream& operator<<(std::ostream& os, const Employee & employee);
std::ofstream& operator<<(std::ofstream& ofs, const Employee & employee); 
std::istream& operator>>(std::istream& is, Employee & employee);
std::ifstream& operator>>(std::ifstream& ifs,  Employee & employee); 

class Developer final : public Employee {
public:
    Developer();
    int salary() const override;
    std::ostream& operator<<(std::ostream& ost) const override;
    std::istream& operator>>(std::istream& ist) override;
    std::ofstream& operator<<(std::ofstream& ofs) const override; 
    std::ifstream& operator>>(std::ifstream& ifs) override;
private: 
    bool _has_bonus;
};

class SalesManager final : public Employee {
public:
    SalesManager();
    int salary() const override; 
    std::ostream& operator<<(std::ostream& ost) const override;
    std::istream& operator>>(std::istream& ist) override;
    std::ofstream& operator<<(std::ofstream& ofs) const override; 
    std::ifstream& operator>>(std::ifstream& ifs) override;
private: 
    int32_t _sold_nm = 0, _price = 0;
};

class EmployeesArray final {
public:
    EmployeesArray(size_t capacity = 10);
    ~EmployeesArray();
    std::ostream& operator<<(std::ostream& ost) const;
    std::istream& operator>>(std::istream& ist);
    std::ofstream& operator<<(std::ofstream& ofs) const; 
    void add(Employee * e);
    int total_salary() const;    
private:
    Employee ** _employees;
    size_t _capacity;
    size_t _size;
};

std::ostream & operator<<(std::ostream& os, const EmployeesArray & array);
std::ofstream & operator<<(std::ofstream& ofs, const EmployeesArray & array); 
std::istream & operator>>(std::istream& is, EmployeesArray & array);

#endif  