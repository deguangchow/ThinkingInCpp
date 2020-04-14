///    Copyright (C) 2020 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    generic container
///
///    \author   deguangchow
///    \version  1.0
///    \2020/03/14

#include "stdafx.h"
#include "generic_container.h"

void testIntSet() {
    set<int> intset;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 10; ++j) {
            intset.insert(j);
        }
    }
    assert(intset.size() == 10);
}

void testWordSet() {
    ifstream source("WordSet.dat");
    string word;
    set<string> words;
    while (source >> word) {
        words.insert(word);
    }
    copy(words.cbegin(), words.cend(), ostream_iterator<string>(cout, "\n"));
    cout << "Number of unique words:" << words.size() << endl;
}

void testStlShape() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle);
    shapes.push_back(new Square);
    shapes.push_back(new Triangle);

    for (auto pos = shapes.cbegin(); pos != shapes.cend(); ++pos) {
        (*pos)->draw();
    }
    for (auto pos = shapes.cbegin(); pos != shapes.cend(); ++pos) {
        delete (*pos);
    }
}

void testStringVector() {
    const char *fname = "StringVector.dat";
    ifstream in(fname);
    vector<string> strings;
    string line;
    while (getline(in, line)) {
        strings.push_back(line);
    }
    int i = 1;
    for (auto pos = strings.begin(); pos != strings.end(); ++pos) {
        ostringstream ss;
        ss << i++;
        *pos = ss.str() + ": " + *pos;
    }

    copy(strings.cbegin(), strings.cend(), ostream_iterator<string>(cout, "\n"));
}

void testFEdit() {
    FilterEditor file;
    file.open("FilterEditor.dat");

    int i = 1;
    auto pos = file.begin();
    while (pos != file.end()) {
        ostringstream ss;
        ss << i++;
        *pos = ss.str() + ": " + *pos;
        ++pos;
    }
    file.write();
}

void testApply() {
}
