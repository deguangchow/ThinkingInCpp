///    Copyright (C) 2020 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    generic container
///
///    \author   deguangchow
///    \version  1.0
///    \2020/03/14

#pragma once
#ifndef GENERIC_CONTAINER_H
#define GENERIC_CONTAINER_H

//7.1 容器和迭代器

//7.2概述
void testIntSet();

void testWordSet();

#if 0
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};
class Circle : public Shape {
public:
    void draw() {
        cout << "Circle::draw" << endl;
    }
    ~Circle() {
        cout << "~Circle()" << endl;
    }
};
#endif
class Triangle : public Shape {
public:
    void draw() {
        cout << "Triangle::draw" << endl;
    }
    ~Triangle() {
        cout << "~Triangle()" << endl;
    }
};
#if 0
class Square : public Shape {
public:
    void draw() {
        cout << "Square::draw" << endl;
    }
    ~Square() {
        cout << "~Square()" << endl;
    }
};
#endif
void testStlShape();

void testStringVector();

//7.2.2 从STL容器继承
class FilterEditor : public vector<string> {
public:
    void open(const char *filename) {
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            push_back(line);
        }
    }
    explicit FilterEditor(const char *filename) {
        open(filename);
    }
    FilterEditor() {}
    void write(ostream &out = cout) {
        for (auto pos = cbegin(); pos != cend(); ++pos) {
            out << *pos << endl;
        }
    }
};

void testFEdit();

//7.3 更多的容器
void testApply();

#endif  //GENERIC_CONTAINER_H
