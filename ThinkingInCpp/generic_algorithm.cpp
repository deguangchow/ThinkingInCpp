///    Copyright (C) 2020 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    generic algorithm
///
///    \author   deguangchow
///    \version  1.0
///    \2020/03/07
#include "stdafx.h"
#include "generic_algorithm.h"

const char* CharGen::source = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const size_t CharGen::len = strlen(source);

NString::words_type NString::words;

int Counted::count = 0;


void testCopyInts() {
    int a[] = { 10, 20, 30 };
    const size_t SIZE = sizeof a / sizeof a[0];
    int b[SIZE];
    copy(a, a + SIZE, b);
    for (size_t i = 0; i < SIZE; ++i) {
        assert(a[i] == b[i]);
    }
}

void testCopyString() {
    string a[] = { "read", "my", "lips" };
    const size_t SIZE = sizeof a / sizeof a[0];
    string b[SIZE];
    copy(a, a + SIZE, b);
    assert(equal(a, a + SIZE, b));
}

void testCopyVector() {
    int a[] = { 10, 20, 30 };
    const size_t SIZE = sizeof a / sizeof a[0];
    vector<int> v1(a, a + SIZE);
    vector<int> v2(SIZE);
    copy(v1.cbegin(), v1.cend(), v2.begin());
    assert(equal(v1.cbegin(), v1.cend(), v2.cbegin()));
}

void testCopyVector2() {
    int a[] = { 10, 20, 30 };
    const size_t SIZE = sizeof a / sizeof a[0];
    vector<int> v1(a, a + SIZE);
    vector<int> v2;
    copy(v1.cbegin(), v1.cend(), back_inserter(v2));
    assert(equal(v1.cbegin(), v1.cend(), v2.cbegin()));
}

void testCopyInts2() {
    int a[] = { 10, 20, 30 };
    auto const SIZE = sizeof a / sizeof a[0];
    int b[SIZE];
    int *endb = remove_copy_if(a, a + SIZE, b, [](int x) {return x > 15; });
    int *beginb = b;
    while (beginb != endb) {
        cout << *beginb++ << endl;
    }
}

void testCopyString2() {
    string a[] = { "read", "my", "lips" };
    auto const SIZE = sizeof a / sizeof a[0];
    string b[SIZE];
    string *endb = replace_copy_if(a, a + SIZE, b, [](string const &s) {
        return s.find('e') != string::npos;
    }, string("kiss"));
    auto *beginb = b;
    while (beginb != endb) {
        cout << *beginb++ << endl;
    }
}

void testReplaceStrings() {
    string a[] = { "read", "my", "lips" };
    auto const SIZE = sizeof a / sizeof a[0];
    replace_if(a, a + SIZE, [](string const &s) {
        return s.find('e') != string::npos;
    }, string("kiss"));
    for (auto &&s : a) {
        cout << s << endl;
    }
}

void testCopyInts3() {
    int a[] = { 10, 20, 30 };
    auto const SIZE = sizeof a / sizeof  a[0];
    remove_copy_if(a, a + SIZE, ostream_iterator<int>(cout, "\n"), [](int x) {return x > 15; });
    for (auto && x : a) {
        cout << x << endl;
    }
}

void testCopyIntsToFiles() {
    int a[] = { 10, 20, 30 };
    auto const SIZE = sizeof a / sizeof a[0];
    ofstream outf("ints.out");
    remove_copy_if(a, a + SIZE, ostream_iterator<int>(outf, "\n"), [](int x) {return x > 25; });
}

void testCopyIntsFromFiles() {
    ofstream ints("someInts.dat");
    ints << "1 3 47 5 84 9";
    ints.close();
    ifstream inf("someInts.dat");
    assert(inf, "someInts.dat");
#if 0
    remove_copy_if(istream_iterator<int>(inf), istream_iterator<int>(), ostream_iterator<int>(cout, "\n"), [](int x) {
        return x > 15;
    });
#else
    copy_if(istream_iterator<int>(inf), istream_iterator<int>(), ostream_iterator<int>(cout, "\n"), [](int x) {
        return x <= 15;
    });
#endif
}

void testCopyIntsFromFilesToFiles() {
    ofstream outdat("someInts.dat");
    outdat << "1 2 3 4 5 6 7 8 9 10";
    outdat.close();

    ifstream inf("someInts.dat");
    assert(inf, "someInts.dat");

    ofstream outf("ints.out");
#if 0
    remove_copy_if(istream_iterator<int>(inf), istream_iterator<int>(), ostream_iterator<int>(outf, "\n"), [](int x) {
        return x % 2 == 0;
    });
#else
    copy_if(istream_iterator<int>(inf), istream_iterator<int>(), ostream_iterator<int>(outf, "\n"), [](int x) {
        return x % 2 != 0;
    });
#endif
}

void testGreaterThanN() {
    gt_n f(4);
    cout << f(3) << endl;
    cout << f(5) << endl;
}

void testCopyInts4() {
    int a[] = { 10, 20, 30 };
    auto const SIZE = sizeof a / sizeof  a[0];
    remove_copy_if(a, a + SIZE, ostream_iterator<int>(cout, "\n"), bind2nd(greater<int>(), 15));
}

void testCountNotEqual() {
    int a[] = { 10, 20, 30 };
    auto const SIZE = sizeof a / sizeof a[0];
#if 0
    cout << count_if(a, a + SIZE, not1(bind2nd(equal_to<int>(), 20)));
#elif 0
    cout << count_if(a, a + SIZE, not1(bind1st(equal_to<int>(), 20)));
#elif 1
    cout << count_if(a, a + SIZE, not1(bind1st_(equal_to<int>(), 20)));
#elif 0
    cout << count_if(a, a + SIZE, bind2nd(not_equal_to<int>(), 20));
#else
    cout << count_if(a, a + SIZE, [](int x) {return x != 20; });
#endif
}

void testFunctionObjects() {
    //cout.setf(std::ios::boolalpha);

    const int SZ = 10;
    const int MAX = 50;
    vector<int> x(SZ), y(SZ), r(SZ);
    URandGen urg(MAX);
    srand(static_cast<unsigned>(time(0)));
    generate_n(x.begin(), SZ, urg);
    generate_n(y.begin(), SZ, urg);
    print(x.begin(), x.end(), "generate_n(x)");
    print(y.begin(), y.end(), "generate_n(y)");

    transform(y.begin(), y.end(), y.begin(), bind2nd(plus<int>(), 1));
    print(y.begin(), y.end(), "y plus(1)    ");

    T(testBinary(x, y, r, plus<int>()));
    T(testBinary(x, y, r, minus<int>()));
    T(testBinary(x, y, r, multiplies<int>()));
    T(testBinary(x, y, r, divides<int>()));
    T(testBinary(x, y, r, modulus<int>()));
    T(testUnary(x, r, negate<int>()));

    vector<bool> br(SZ);
    B(testBinary(x, y, br, equal_to<int>()));
    B(testBinary(x, y, br, not_equal_to<int>()));
    B(testBinary(x, y, br, greater<int>()));
    B(testBinary(x, y, br, less<int>()));
    B(testBinary(x, y, br, greater_equal<int>()));
    B(testBinary(x, y, br, less_equal<int>()));
    B(testBinary(x, y, br, not2(greater_equal<int>())));
    B(testBinary(x, y, br, not2(less_equal<int>())));

    vector<bool> b1(SZ), b2(SZ);
    generate_n(b1.begin(), SZ, BRand());
    generate_n(b2.begin(), SZ, BRand());
    print(b1.begin(), b1.end(), "generate_n(b1)");
    print(b2.begin(), b2.end(), "generate_n(b2)");
    B(testBinary(b1, b2, br, logical_and<int>()));
    B(testBinary(b1, b2, br, logical_or<int>()));
    B(testUnary(b1, br, logical_not<int>()));
    B(testUnary(b1, br, not1(logical_not<int>())));
}

void testFBinder() {
    ostream_iterator<int> out(cout, " ");
    vector<int> v(15);
    srand(time(0));
    generate(v.begin(), v.end(), URandGen(20));
    copy(v.begin(), v.end(), out);
    transform(v.begin(), v.end(), v.begin(), bind2nd(multiplies<int>(), 10));
    copy(v.begin(), v.end(), out);
}

int boundedRand() {
    return rand() % 100;
}
void testBinderValue() {
    srand(time(0));

    const int SZ = 20;
    int a[SZ], b[SZ] = { 0 };
    generate(a, a + SZ, boundedRand);
    int val = boundedRand();
    int *end = remove_copy_if(a, a + SZ, b, bind2nd(greater<int>(), val));

    sort(a, a + SZ);
    sort(b, end);
    ostream_iterator<int> out(cout, " ");
    cout << "Original Sequence:" << endl;
    copy(a, a + SZ, out);
    cout << endl;
    cout << "Values <= " << val << endl;
    copy(b, end, out);
    cout << endl;
}

bool isEven(int x) {
    return x % 2 == 0;
}
void testPtrFun1() {
    int d[] = { 123, 94, 10, 314, 315 };
    const int DSZ = sizeof d / sizeof d[0];

    vector<bool> vb;
#if 1
    transform(d, d + DSZ, back_inserter(vb), not1(ptr_fun(isEven)));
#elif 0
    transform(d, d + DSZ, back_inserter(vb), not1(ptr_unary_fun(isEven)));
#else
    transform(d, d + DSZ, back_inserter(vb), not1(ptr_unary_fun_(isEven)));
#endif
    copy(vb.begin(), vb.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void testPtrFun2() {
    double d[] = { 01.23, 91.0370, 56.661, 023.230, 19.959, 1.0, 3.14159 };
    const int DSZ = sizeof d / sizeof d[0];

    vector<double> vd;
#if 1
    //double pow(double, double)
    transform(d, d + DSZ, back_inserter(vd), bind2nd(ptr_fun<double, double, double>(pow), 2.0));
#elif 0
    //double pow(double, int)
    transform(d, d + DSZ, back_inserter(vd), bind2nd(ptr_fun<double, int, double>(pow), 2));
#elif 0
    //double pow(double, double)
    transform(d, d + DSZ, back_inserter(vd), bind2nd(ptr_binary_fun<double, double, double>(pow), 2.0));
#elif 0
    //double pow(double, int)
    transform(d, d + DSZ, back_inserter(vd), bind2nd(ptr_binary_fun_<double, int, double>(pow), 2));
#else
    transform(d, d + DSZ, back_inserter(vd), [](double const &d) {return pow(d, 2.0); });
#endif
    copy(vd.begin(), vd.end(), ostream_iterator<double>(cout, ", "));
    cout << endl;
}

void testMemFun1() {
    vector<Shape*> vs;
    vs.push_back(new Circle);
    vs.push_back(new Square);
    for_each(vs.begin(), vs.end(), mem_fun(&Shape::draw));
    common_functions::purge(vs);
}

void testMemFun2() {
    vector<Angle> va;
    for (int i = 0; i < 50; i += 10) {
        va.push_back(Angle(i));
    }
    int x[] = { 1, 2, 3, 4, 5 };
    transform(va.begin(), va.end(), x, ostream_iterator<int>(cout, "\n"), mem_fun_ref(&Angle::mul));
    cout << endl;
}

void testFindBlanks() {
    vector<string> vs{ "read", "my", "lips", "", " " };
    vector<string> cpy = vs;
    auto pos = find_if(vs.begin(), vs.end(), mem_fun_ref(&string::empty));
    while (pos != vs.end()) {
        *pos = "A BLANK LINE";
        pos = find_if(vs.begin(), vs.end(), mem_fun_ref(&string::empty));
    }
    for (auto i = 0U; i < cpy.size(); ++i) {
        if (cpy[i].size() == 0) {
            assert(vs[i] == "A BLANK LINE");
        } else {
            assert(vs[i] != "A BLANK LINE");
        }
    }
}

void testMemFun3() {
    const int SZ = 9;
    vector<string> vs(SZ);
    srand(time(0));
    generate(vs.begin(), vs.end(), NumStringGen());
    copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\t"));
    cout << endl;

    const char *vcp[SZ];
    transform(vs.begin(), vs.end(), vcp, mem_fun_ref(&string::c_str));
#if 1
    vector<double> vd;
    transform(vcp, vcp + SZ, back_inserter(vd), atof);
#else
    vector<double> vd(SZ);
    transform(vcp, vcp + SZ, vd.begin(), atof);
#endif
    cout.precision(4);
    cout.setf(ios::showpoint);
    copy(vd.begin(), vd.end(), ostream_iterator<double>(cout, "\t"));
    cout << endl;
}

void testComposeTry() {
    //F1, F2 从调用中推断出来
    double x = compose<double, const string &>(atof, mem_fun_ref(&string::c_str))("12.34");
    assert(x == 12.34);
}

void testComposeFinal() {
    const int SZ = 9;
    vector<string> vs(SZ);
    generate(vs.begin(), vs.end(), NumStringGen());
    copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\t"));
    cout << endl;

    vector<double> vd;
    transform(vs.begin(), vs.end(), back_inserter(vd), compose(ptr_fun(atof), mem_fun_ref(&string::c_str)));
    copy(vd.begin(), vd.end(), ostream_iterator<double>(cout, "\t"));
    cout << endl;
}

void testFillGenerate() {
    vector<string> v1(5);
    fill(v1.begin(), v1.end(), "howdy");
    print(v1.cbegin(), v1.cend(), "v1", " ");

    vector<string> v2;
    fill_n(back_inserter(v2), 7, "bye");
    print(v2.cbegin(), v2.cend(), "v2", " ");

    vector<int> v3(10);
    generate(v3.begin(), v3.end(), SkipGen(4, 5));
    print(v3.cbegin(), v3.cend(), "v3", " ");

    vector<int> v4;
    generate_n(back_inserter(v4), 15, URandGen(30));
    print(v4.cbegin(), v4.cend(), "v4", " ");
}

void testCounting() {
    vector<char> v;
    generate_n(back_inserter(v), 50, CharGen());
    print(v.begin(), v.end(), "v", ", ");

    set<char> cs(v.begin(), v.end());
    for (auto pos = cs.begin(); pos != cs.end(); ++pos) {
        int n = count(v.begin(), v.end(), *pos);
        cout << *pos << ": " << n << "\t";
    }
    int lc = count_if(v.begin(), v.end(), bind2nd(greater<char>(), 'a'));
    cout << "\nLowercase letters: " << lc << endl;

    sort(v.begin(), v.end());
    print(v.cbegin(), v.cend(), "sorted", ", ");
}

void testManipulations() {
    vector<int> v1(10);
    generate(v1.begin(), v1.end(), SkipGen());
    print(v1.cbegin(), v1.cend(), "v1", " ");

    vector<int> v2(v1.size());
    copy_backward(v1.begin(), v1.end(), v2.end());
    print(v2.cbegin(), v2.cend(), "copy_backward", " ");

    reverse_copy(v1.begin(), v1.end(), v2.begin());
    print(v2.cbegin(), v2.cend(), "reverse_copy", " ");

    reverse(v1.begin(), v1.end());
    print(v1.cbegin(), v1.cend(), "reverse", " ");

    int half = v1.size() / 2;
    swap_ranges(v1.begin(), v1.begin() + half, v1.begin() + half);
    print(v1.cbegin(), v1.cend(), "swap_ranges", " ");

    generate(v1.begin(), v1.end(), SkipGen());
    print(v1.cbegin(), v1.cend(), "v1", " ");

    int third = v1.size() / 3;
    for (int i = 0; i < 10; ++i) {
        rotate(v1.begin(), v1.begin() + third, v1.end());
        print(v1.cbegin(), v1.cend(), "rotate", " ");
    }
    cout << "Second rotate example:" << endl;

    char c[] = "aabbccddeeffgghhiijj";
    const auto CSZ = strlen(c);
    for (int i = 0; i < 10; ++i) {
        rotate(c, c + 2, c + CSZ);
        print(c, c + CSZ, "", "");
    }

    cout << "All n! permutations of abcd:" << endl;
    int nf = 4 * 3 * 2 * 1;
    char p[] = "1234";
    for (int i = 0; i < nf; ++i) {
        //排列组合：升序
        next_permutation(p, p + 4);
        print(p, p + 4, "", "");
    }

    cout << "Using prev_premutation:" << endl;
    for (int i = 0; i < nf; ++i) {
        //排列组合：降序
        prev_permutation(p, p + 4);
        print(p, p + 4, "", "");
    }

    cout << "random_shuffling a word:" << endl;
    string s("hello");
    cout << s << endl;
    for (int i = 0; i < 5; ++i) {
        //随机洗牌
        random_shuffle(s.begin(), s.end());
        cout << s << endl;
    }

    string sa[] = { "a", "b", "c", "d", "a1", "b1", "c1", "d1", "a2", "b2", "c2" };
    const int SASZ = sizeof sa / sizeof *sa;
    vector<NString> ns(sa, sa + SASZ);
    print(ns.cbegin(), ns.cend(), "ns", " ");

    //分区
    auto pos = partition(ns.begin(), ns.end(), bind2nd(greater<NString>(), "b"));
    cout << "Partition point: " << *pos << endl;
    print(ns.cbegin(), ns.cend(), "", " ");

    copy(sa, sa + SASZ, ns.begin());
    //稳定分区
    pos = stable_partition(ns.begin(), ns.end(), bind2nd(greater<NString>(), "b"));
    cout << "Stable partition" << endl;
    cout << "Partition point: " << *pos << endl;
    print(ns.cbegin(), ns.cend(), "", " ");
}

void testSearchReplace() {
    int a[] = { 1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8, 11, 11, 11, 11, 11, 12 };
    const int ASZ = sizeof a / sizeof a[0];
    vector<int> v(a, a + ASZ);
    print(v.begin(), v.end(), "v", " ");

    auto pos = find(v.begin(), v.end(), 4);
    cout << "find: " << *pos << endl;

    pos = find_if(v.begin(), v.end(), bind2nd(greater<int>(), 8));
    cout << "find_if: " << *pos << endl;

    //查找相邻的：5，6  6，7  7，8
    pos = adjacent_find(v.begin(), v.end());
    while (pos != v.end()) {
        cout << "adjacent_find PlusOne: " << *(pos - 1) << ", " << *pos << ", " << *(pos + 1) << endl;
        pos = adjacent_find(pos + 1, v.end(), PlusOne());
    }

    int b[] = { 8, 11 };
    const int BSZ = sizeof b / sizeof b[0];
    print(b, b + BSZ, "b", " ");
    pos = find_first_of(v.begin(), v.end(), b, b + BSZ, PlusOne());
    print(pos, pos + BSZ, "find_first_of PlusOne", " ");

    //查找开始位置为 b，BSZ 个元素，返回在集合 v 中的位置。
    pos = search(v.begin(), v.end(), b, b + BSZ);
    print(pos, pos + BSZ, "search", " ");

    int c[] = { 5, 6, 7 };
    const int CSZ = sizeof c / sizeof c[0];
    print(c, c + CSZ, "c", " ");
    pos = search(v.begin(), v.end(), c, c + CSZ, PlusOne());
    print(pos, pos + CSZ, "search PlusOne", " ");

    int d[] = { 11, 11, 11 };
    const int DSZ = sizeof d / sizeof d[0];
    print(d, d + DSZ, "d", " ");
    pos = find_end(v.begin(), v.end(), d, d + DSZ);
    print(pos, pos + DSZ, "find_end", " ");

    int e[] = { 9, 9 };
    const int ESZ = sizeof e / sizeof e[0];
    print(e, e + ESZ, "e", " ");
    pos = find_end(v.begin(), v.end(), e, e + ESZ, PlusOne());
    print(pos, pos + ESZ, "find_end PlusOne", " ");
    pos = search_n(v.begin(), v.end(), 3, 7);
    print(pos, pos + 3, "search_n 3, 7", " ");
    pos = search_n(v.begin(), v.end(), 6, 15, MulMoreThan(100));
    print(pos, pos + 6, "search_n 6, 15, MulMoreThan(100)", " ");

    cout << "min_element: " << *min_element(v.begin(), v.end()) << endl;
    cout << "max_element: " << *max_element(v.begin(), v.end()) << endl;

    vector<int> v2;
    replace_copy(v.begin(), v.end(), back_inserter(v2), 8, 47);
    print(v2.begin(), v2.end(), "v2", " ");

    replace_if(v.begin(), v.end(), bind2nd(greater_equal<int>(), 7), -1);
    print(v.begin(), v.end(), "replace_if >= 7 -> -1", " ");
}

void testComparison() {
    string s1("This is a test");
    string s2("This is a Test");
    cout << "s1: " << s1 << endl << "s2: " << s2 << endl;
    cout << "Compare s1 & s1: " << equal(s1.begin(), s1.end(), s1.begin()) << endl;
    cout << "Compare s1 & s2: " << equal(s1.begin(), s1.end(), s2.begin()) << endl;

    //字典比较
    cout << "lexicographical_compare s1 & s1: " << lexicographical_compare(s1.begin(), s1.end(), s1.begin(), s1.end())
        << endl;
    cout << "lexicographical_compare s1 & s2: " << lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end())
        << endl;
    cout << "lexicographical_compare s2 & s1: " << lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end())
        << endl;

    cout << "lexicographical_compare shortened s3 & full-length s2: " << endl;
    string s3(s1);
    while (s3.length() != 0) {
        bool result = lexicographical_compare(s3.begin(), s3.end(), s2.begin(), s2.end());
        cout << s3 << endl << s2 << ", result = " << result << endl;
        if (result == true) {
            break;
        }
        s3 = s3.substr(0, s3.length() - 1);
    }

    //返回不匹配的开始位置
    auto pos = mismatch(s1.begin(), s1.end(), s2.begin());
    print(pos.first, s1.end(), "p.first", "");
    print(pos.second, s2.end(), "p.second", "");
}

void testRemoving() {
    srand(time(0));

    string v;
    v.resize(25);
    generate(v.begin(), v.end(), CharGen());
    print(v.begin(), v.end(), "v", " ");

    string us(v.begin(), v.end());
    sort(us.begin(), us.end());
    print(us.begin(), us.end(), "us", " ");

    //unique 去除相邻的重复元素，按照集合尾部的元素，补充元素到集合尾
    auto posUs = us.begin(), posV = v.end(), uend = unique(us.begin(), us.end());
    print(us.begin(), us.end(), "us", " ");

    while (posUs != uend) {
        posV = remove(v.begin(), posV, *posUs);
        print(v.begin(), v.end(), "Complete\nv", " ");
        print(v.begin(), posV, "Pseudo\nv", " ");
        cout << "Remove element:\t" << *posUs << "\nPsuedo Last Element:\t" << *posV << endl << endl;
        ++posUs;
    }

    generate(v.begin(), v.end(), CharGen());
    print(v.begin(), v.end(), "v", " ");
    posV = remove_if(v.begin(), v.end(), IsUpper());
    print(v.begin(), posV, "after remove_if IsUpper\nv", " ");

    sort(v.begin(), posV);
    print(v.begin(), posV, "sorted\nv", " ");

    string v2;
    v2.resize(posV - v.begin());
    unique_copy(v.begin(), posV, v2.begin());
    print(v2.begin(), v2.end(), "unique_copy\nv", " ");

    posV = unique(v.begin(), posV, equal_to<char>());
    print(v.begin(), posV, "unique equal_to<char>\nv", " ");
}

void require(bool, string const&) {}
void testSortedSearchTest() {
    char *fname = "Test.txt";
    ifstream in(fname);
    assert(in, fname);
    srand(time(0));
    cout.setf(ios::boolalpha);

    vector<NString> original;
    copy(istream_iterator<string>(in), istream_iterator<string>(), back_inserter(original));
    require(original.size() >= 4, "Must have four elements");
    print(original.begin(), original.end(), "original\n", " ");

    vector<NString> v(original.begin(), original.end()), w(original.size() / 2);
    sort(v.begin(), v.end());
    print(v.begin(), v.end(), "sort\nv", " ");

    v = original;
    stable_sort(v.begin(), v.end());
    print(v.begin(), v.end(), "stable_sort\nv", " ");

    v = original;
    auto pos = v.begin();
    for (auto i = 0U; i < v.size() / 2; ++i) {
        ++pos;
    }
    partial_sort(v.begin(), pos, v.end());
    cout << "middle = " << *pos << endl;
    print(v.begin(), v.end(), "partial_sort\nv", " ");

    v = original;
    pos = v.begin();
    for (auto i = 0U; i < v.size() / 4; ++i) {
        ++pos;
    }
    cout << "quarter = " << *pos << endl;
    partial_sort_copy(v.begin(), pos, w.begin(), w.end());
    print(w.begin(), w.end(), "partial_sort_copy\nw", " ");
    partial_sort_copy(v.begin(), v.end(), w.begin(), w.end());
    print(w.begin(), w.end(), "partial_sort_copy\nw", " ");

    assert(v == original);

    //排序
    nth_element(v.begin(), pos, v.end());
    cout << "The nth_element = " << *pos << endl;
    print(v.begin(), v.end(), "nth_element\nv");
    auto f = original[rand() % original.size()];
    cout << "binary_search(v.begin(), v.end(), " << f << ")" << binary_search(v.begin(), v.end(), f) << endl;
    sort(v.begin(), v.end());
    print(v.begin(), v.end(), "sort\nv", " ");
    //[pos, pos2)
    pos = lower_bound(v.begin(), v.end(), f);
    auto pos2 = upper_bound(v.begin(), v.end(), f);
    print(pos, pos2, "found range");
    auto range = equal_range(v.begin(), v.end(), f);
    print(range.first, range.second, "equal_range", " ");
}

void testMerge() {
    const int SZ = 15;
    int a[SZ * 2] = { 0 };
    generate(a, a + SZ, SkipGen(0, 2));
#if 1
    a[3] = 4;
    a[4] = 4;
#endif
    generate(a + SZ, a + SZ * 2, SkipGen(1, 3));
    print(a, a + SZ, "range1\na", ",");
    print(a + SZ, a + SZ * 2, "range2\na", ",");

#if 1
    int b[SZ * 2] = { 0 };
    merge(a, a + SZ, a + SZ, a + SZ * 2, b);
    print(b, b + SZ * 2, "merge\nb", ",");
    for (int i = 0; i < SZ * 2; ++i) {
        b[i] = 0;
    }

    //就地合并
    inplace_merge(a, a + SZ, a + SZ * 2);
    print(a, a + SZ * 2, "inplace_merge\na", ",");

    //并集：两个集合都需要是升序的
    auto *end = set_union(a, a + SZ, a + SZ, a + SZ * 2, b);
    print(b, end, "set_union\nb", ",");
#else
    //并集：两个集合都需要是升序的
    cout << "set_union" << endl;
    set_union(a, a + SZ, a + SZ, a + SZ * 2, ostream_iterator<int>(cout, ","));
    cout << endl;
#endif
}

void testSetOperations() {
    const int SZ = 30;
    char v[SZ + 1], v2[SZ + 1];
    CharGen g;
    generate(v, v + SZ, g);
    generate(v2, v2 + SZ, g);
    sort(v, v + SZ);
    sort(v2, v2 + SZ);
    print(v, v + SZ, "v", ",");
    print(v2, v2 + SZ, "v2", ",");

    //第1个集合中的元素都来自于第2个集合
    bool b = includes(v, v + SZ, v + (SZ / 2), v + SZ);
    cout.setf(ios::boolalpha);
    cout << "includes: " << b << endl;

    //并集
    char v3[SZ * 2 + 1];
    auto *end = set_union(v, v + SZ, v2, v2 + SZ, v3);
    print(v3, end, "set_union\nv3", ",");

    //交集
    end = set_intersection(v, v + SZ, v2, v2 + SZ, v3);
    print(v3, end, "set_intersection\nv3", ",");

    //差集
    end = set_difference(v, v + SZ, v2, v2 + SZ, v3);
    print(v3, end, "set_difference\nv3", ",");

    //对称差集：并集-交集
    end = set_symmetric_difference(v, v + SZ, v2, v2 + SZ, v3);
    print(v3, end, "set_symmetric_difference\nv3", ",");
}

void testForEach() {
    CountedVector cv("two");
    for_each(cv.begin(), cv.end(), DeleteT<Counted>());

    CountedVector cv2("three");
    for_each(cv2.begin(), cv2.end(), wipe<Counted>);
}

void testTransform() {
    CountedVector cv("one");
    transform(cv.begin(), cv.end(), cv.begin(), deleteP<Counted>);

    CountedVector cv2("two");
    transform(cv2.begin(), cv2.end(), cv2.begin(), Deleter<Counted>());
}

void testCalcInventory() {
    vector<Inventory> vi;
    srand(time(0));
    generate_n(back_inserter(vi), 15, InvenGen());
    print(vi.begin(), vi.end(), "vi");
    InvAccum ia = for_each(vi.begin(), vi.end(), InvAccum());
    cout << ia << endl;
}

void testTransformNames() {
    vector<Inventory> vi;
    srand(time(0));
    generate_n(back_inserter(vi), 15, InvenGen());
    print(vi.begin(), vi.end(), "vi");

    transform(vi.begin(), vi.end(), vi.begin(), NewImproved());
    print(vi.begin(), vi.end(), "vi");
}

void testSpecialList() {
    srand(time(0));

    vector<Inventory> vi;
    generate_n(back_inserter(vi), 15, InvenGen());
    print(vi.begin(), vi.end(), "vi");

    vector<float> disc;
    generate_n(back_inserter(disc), 15, DiscGen());
    print(disc.begin(), disc.end(), "Discounts:");

    vector<Inventory> discounted;
    transform(vi.begin(), vi.end(), disc.begin(), back_inserter(discounted), Discounter());
    print(discounted.begin(), discounted.end(), "discounted");
}

void testNumeric() {
    int a[] = { 1, 1, 2, 2, 3, 5, 7, 9, 11, 13 };
    const int ASZ = sizeof a / sizeof a[0];
    print(a, a + ASZ, "a", ",");

    //sum(a1, a2, ……)
    int r = accumulate(a, a + ASZ, 0);
    cout << "accumulate 1: " << r << endl;
    r = accumulate(a, a + ASZ, 0, plus<int>());
    cout << "accumulate 2: " << r << endl;

    int b[] = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2 };
    const int BSZ = sizeof b / sizeof b[0];
    print(b, b + BSZ, "b", ",");

    //2个集合乘积累加之和：sum(a1*b1, a2*b2, ……)
    r = inner_product(a, a + ASZ, b, 0);
    cout << "inner_product 1: " << r << endl;
    r = inner_product(a, a + ASZ, b, 0, plus<int>(), multiplies<int>());
    cout << "inner_product 2: " << r << endl;

    //前n个元素累加之和
    int *it = partial_sum(a, a + ASZ, b);
    print(b, it, "partial_sum 1", ",");
    it = partial_sum(a, a + ASZ, b, plus<int>());
    print(b, it, "partial_sum 2", ",");

    //和前1个元素的差值
    it = adjacent_difference(a, a + ASZ, b);
    print(b, it, "adjacent_difference 1", ",");
    it = adjacent_difference(a, a + ASZ, b, minus<int>());
    print(b, it, "adjacent_difference 2", ",");
}
