#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

class Point {
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    double distanceTo(const Point& other) const {
        return std::hypot(x - other.x, y - other.y);
    }
};

class Line {
public:
    double a, b, c; // Representation of line: ax + by + c = 0

    Line(double a, double b, double c) : a(a), b(b), c(c) {}

    Line(const Point& p1, const Point& p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
    }

    bool contains(const Point& point) const {
        return std::abs(a * point.x + b * point.y + c) < 1e-9;
    }

    double distanceTo(const Point& point) const {
        return std::abs(a * point.x + b * point.y + c) / std::hypot(a, b);
    }
};

// Tests for Point and Line classes

void testPointDistance() {
    Point p1(0, 0), p2(3, 4);
    assert(p1.distanceTo(p2) == 5.0 && "Distance between points is incorrect");
    std::cout << "Test Point Distance Passed.\n";
}

void testLineContains() {
    Point p1(0, 0), p2(2, 2), p3(1, 1);
    Line line(p1, p2);
    assert(line.contains(p3) && "Point should lie on the line");
    std::cout << "Test Line Contains Passed.\n";
}

void testLineDistanceTo() {
    Point p1(0, 0), p2(2, 2), p3(3, 0);
    Line line(p1, p2);
    assert(std::abs(line.distanceTo(p3) - 2.12132) < 1e-5 && "Distance from point to line is incorrect");
    std::cout << "Test Line DistanceTo Passed.\n";
}

void runTests() {
    testPointDistance();
    testLineContains();
    testLineDistanceTo();
    std::cout << "All tests passed.\n";
}

int main() {
    runTests();
}