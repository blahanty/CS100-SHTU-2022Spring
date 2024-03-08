#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
public:
    // This constructor initializes the members with the parameters.
    Grade(const std::string &name, int number, double grade) {
        m_name = name;
        m_number = number;
        m_grade = grade;
    }

    std::string getName() const {
        return m_name;
    }

    void setName(const std::string &name) {
        m_name = name;
    }

    int getNumber() const {
        return m_number;
    }

    void setNumber(int number) {
        m_number = number;
    }

    double getGrade() const {
        return m_grade;
    }

    void setGrade(double grade) {
        m_grade = grade;
    }

private:
    std::string m_name;
    int m_number;
    double m_grade;
};

struct NameComparator {
    bool operator()(const Grade &a, const Grade &b) const {
        return a.getName() < b.getName();
    }
} nameComparator;

struct NumberComparator {
    bool operator()(const Grade &a, const Grade &b) const {
        return a.getNumber() < b.getNumber();
    }
} numberComparator;

struct GradeComparator {
    bool operator()(const Grade &a, const Grade &b) const {
        return a.getGrade() > b.getGrade();
    }
} gradeComparator;

class Gradesheet {
    friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet) {
        os << '/';
        for (int i = 0; i < 30; i++)
            os << '-';
        os << '\\' << std::endl << '|';
        os << std::left << std::setw(10) << "Name" << std::left << std::setw(10) << "Number" << std::left
           << std::setw(10) << "Grade" << '|' << std::endl << '|';
        for (int i = 0; i < 30; i++)
            os << '-';
        os << '|' << std::endl;
        for (const auto &m_grade: sheet.m_grades)
            os << '|' << std::left << std::setw(10) << m_grade.getName() << std::left << std::setw(10)
               << m_grade.getNumber() << std::left << std::setw(10) << std::setprecision(3) << m_grade.getGrade()
               << '|' << std::endl;
        os << '\\';
        for (int i = 0; i < 30; i++)
            os << '-';
        os << '/' << std::endl;
        return os;
    }

public:
    Gradesheet() = default;

    ~Gradesheet() = default;

    std::size_t size() const {
        return m_grades.size();
    }

    double average() const {
        double ave = 0;
        for (const auto &m_grade: m_grades)
            ave += m_grade.getGrade();
        return ave / double(m_grades.size());
    }

    bool addGrade(const Grade &grade) {
        for (const auto &m_grade: m_grades)
            if (grade.getName() == m_grade.getName() || grade.getNumber() == m_grade.getNumber())
                return false;
        m_grades.push_back(grade);
        return true;
    }

    double findByName(const std::string &name) const {
        for (const auto &m_grade: m_grades)
            if (name == m_grade.getName())
                return m_grade.getGrade();
        return -1;
    }

    double findByNumber(int number) const {
        for (const auto &m_grade: m_grades)
            if (number == m_grade.getNumber())
                return m_grade.getGrade();
        return -1;

    }

    Grade &operator[](std::size_t i) {
        return m_grades[i];
    }

    const Grade &operator[](std::size_t i) const {
        return m_grades[i];
    }

    void sortByName() {
        std::sort(m_grades.begin(), m_grades.end(), nameComparator);
    }

    void sortByNumber() {
        std::sort(m_grades.begin(), m_grades.end(), numberComparator);
    }

    void sortByGrade() {
        std::sort(m_grades.begin(), m_grades.end(), gradeComparator);
    }

private:
    std::vector<Grade> m_grades;
};

int main() {
    Gradesheet sheet;
    sheet.addGrade(Grade("Bob", 1, 95));
    sheet.addGrade(Grade("Carl", 2, 100));
    sheet.addGrade(Grade("Alex", 3, 90));
    sheet.sortByGrade();
    std::cout << "size == " << sheet.size() << "\n" << sheet;
    return 0;
}