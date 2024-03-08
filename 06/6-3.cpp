#include <string>

// REMOVE THIS CLASS WHEN SUBMITTING!!!
//class Point {
//    double x{0}, y{0};
//    std::string label;
//
//public:
//    Point(double x0, double y0, const std::string &l = "")
//            : x(x0), y(y0), label(l) {}
//
//    Point() = default;
//
//    double get_x() const {
//        return x;
//    }
//
//    double get_y() const {
//        return y;
//    }
//
//    std::string get_label() const {
//        return label;
//    }
//
//    Point &set_x(double x0) {
//        x = x0;
//        return *this;
//    }
//
//    Point &set_y(double y0) {
//        y = y0;
//        return *this;
//    }
//
//    Point &set_label(const std::string &l) {
//        label = l;
//        return *this;
//    }
//};

class Point_counted {
    friend class Point_handle;

    // All the members are private.

    Point p;
    unsigned cnt;

    // Define some helper member functions if you need.
};

class Point_handle {
    Point_counted *ptr;
public:
    Point_handle(const Point_handle &point) {
        ptr = point.ptr;
        ptr->cnt++;
    }

    Point_handle &operator=(const Point_handle &point) {
        if (this != &point) {
            if (ptr != nullptr)
                if (!--ptr->cnt)
                    delete ptr;
            ptr = point.ptr;
            ptr->cnt++;
        }
        return *this;
    }

    ~Point_handle() {
        if (!--ptr->cnt)
            delete ptr;
    }

    Point_handle() {
        ptr = new Point_counted;
        ptr->p = Point();
        ptr->cnt = 1;
    }

    Point_handle(const Point &point) {
        ptr = new Point_counted;
        ptr->p = Point(point.get_x(), point.get_y(), point.get_label());
        ptr->cnt = 1;
    }

    Point_handle(double x, double y, const std::string &l = "") {
        ptr = new Point_counted;
        ptr->p = Point(x, y, l);
        ptr->cnt = 1;
    }

    unsigned ref_count() const {
        return ptr->cnt;
    }

    double get_x() const {
        return ptr->p.get_x();
    }

    double get_y() const {
        return ptr->p.get_y();
    }

    std::string get_label() const {
        return ptr->p.get_label();
    }

    Point_handle &set_x(double x0) {
        if (ptr->cnt > 1) {
            auto *ptr_copy = new Point_counted;
            ptr_copy->p = ptr->p;
            ptr_copy->cnt = 1;
            ptr->cnt--;
            ptr = ptr_copy;
        }
        ptr->p.set_x(x0);
        return *this;
    }

    Point_handle &set_y(double y0) {
        if (ptr->cnt > 1) {
            auto *ptr_copy = new Point_counted;
            ptr_copy->p = ptr->p;
            ptr_copy->cnt = 1;
            ptr->cnt--;
            ptr = ptr_copy;
        }
        ptr->p.set_y(y0);
        return *this;
    }

    Point_handle &set_label(const std::string &l) {
        if (ptr->cnt > 1) {
            auto *ptr_copy = new Point_counted;
            ptr_copy->p = ptr->p;
            ptr_copy->cnt = 1;
            ptr->cnt--;
            ptr = ptr_copy;
        }
        ptr->p.set_label(l);
        return *this;
    }
};
