///    Copyright (C) 2020 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    generic algorithm
///
///    \author   deguangchow
///    \version  1.0
///    \2020/03/07

#pragma once
#ifndef GENERIC_ALGORITHM_H
#define GENERIC_ALGORITHM_H

//6.1概述
void testCopyInts();
void testCopyString();
void testCopyVector();
void testCopyVector2();

template<typename Iterator>
void copy_(Iterator begin, Iterator end, Iterator dest) {
    while (begin != end) {
        *dest++ = *begin++;
    }
}

//6.1.1 判定函数
void testCopyInts2();
void testCopyString2();
void testReplaceStrings();

//6.1.2 流迭代器
void testCopyInts3();
void testCopyIntsToFiles();
void testCopyIntsFromFiles();
void testCopyIntsFromFilesToFiles();

//6.2 函数对象
class gt_n : public unary_function<int, bool> {
    int value;
public:
    explicit gt_n(int val) : value(val) {}
    bool operator()(int n) { return n > value; }
};
void testGreaterThanN();

//6.2.1 函数对象的分类

//6.2.2 自动创建函数对象
void testCopyInts4();
void testCountNotEqual();

//6.2.3 可调整的函数对象
template<class Op, class T>
binder1st<Op> bind1st_(const Op &f, const T &val) {
    typedef typename Op::first_argument_type Arg1_t;
    return binder1st<Op>(f, Arg1_t(val));
}

template<class Arg, class Result>
struct unary_function_ {
    typedef Arg argument_type;
    typedef Result result_type;
};

//6.2.4 更多的函数对象的例子
class SkipGen {
    int i;
    int skp;
public:
    explicit SkipGen(int start = 0, int skip = 1) : i(start), skp(skip) {}
    int operator()() {
        int r = i;
        i += skp;
        return r;
    }
};

class URandGen {
    set<int> used;
    int limit;
public:
    explicit URandGen(int lim) : limit(lim) {}
    int operator()() {
        random_device rd;
        while (true) {
            int i = static_cast<int>(rd()) % limit;
            if (used.find(i) == used.end()) {
                used.insert(i);
                return i;
            }
            if (used.size() == limit - 1) {
                break;
            }
        }
        return limit;
    }
};

class CharGen {
    static const char *source;
    static const size_t len;
public:
    char operator()() {
        return source[rand() % len];
    }
};

template<typename Contain, typename UnaryFunc>
void testUnary(Contain &source, Contain &dest, UnaryFunc f) {
    transform(source.begin(), source.end(), dest.begin(), f);
}

template<typename Contain1, typename Contain2, typename BinaryFunc>
void testBinary(Contain1 &src1, Contain1 &src2, Contain2 &dest, BinaryFunc f) {
    transform(src1.begin(), src1.end(), src2.begin(), dest.begin(), f);
}

#define T(EXPR) EXPR; print(r.begin(), r.end(), "After " #EXPR);
#define B(EXPR) EXPR; print(br.begin(), br.end(), "After " #EXPR);

struct BRand {
    bool operator()() {
        return rand() % 2 == 0;
    }
};

void testFunctionObjects();
void testFBinder();
void testBinderValue();

//6.2.5 函数指针适配器

//Result f(Arg);
template<class Arg, class Result>
pointer_to_unary_function<Arg, Result> ptr_unary_fun(Result(*fptr)(Arg)) {
    return pointer_to_unary_function<Arg, Result>(fptr);
}

//Result f(Arg);
template<class Arg, class Result>
class pointer_to_unary_function_ : public unary_function<Arg, Result> {
    Result(*fptr)(Arg);
public:
    explicit pointer_to_unary_function_(Result(*f)(Arg)) : fptr(f) {}
    Result operator()(Arg x) const {
        return fptr(x);
    }
};
template<class Arg, class Result>
pointer_to_unary_function_<Arg, Result> ptr_unary_fun_(Result(*fptr)(Arg)) {
    return pointer_to_unary_function_<Arg, Result>(fptr);
}

void testPtrFun1();

//Result f(Arg1, Arg2);
template<class Arg1, class Arg2, class Result>
pointer_to_binary_function<Arg1, Arg2, Result> ptr_binary_fun(Result(*fptr)(Arg1, Arg2)) {
    return pointer_to_binary_function<Arg1, Arg2, Result>(fptr);
}

//Result f(Arg1, Arg2);
template<class Arg1, class Arg2, class Result>
class pointer_to_binary_function_ : public binary_function<Arg1, Arg2, Result> {
    Result(*fptr)(Arg1, Arg2);
public:
    explicit pointer_to_binary_function_(Result(*f)(Arg1, Arg2)) :fptr(f) {}
    Result operator()(Arg1 x, Arg2 y) const {
        return fptr(x, y);
    }
};
template<class Arg1, class Arg2, class Result>
pointer_to_binary_function_<Arg1, Arg2, Result> ptr_binary_fun_(Result(*fptr)(Arg1, Arg2)) {
    return pointer_to_binary_function_<Arg1, Arg2, Result>(fptr);
}

void testPtrFun2();

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};
class Circle : public Shape {
public:
    virtual void draw() {
        cout << "Circle::Draw()" << endl;
    }
    ~Circle() {
        cout << "~Circle()" << endl;
    }
};
class Square : public Shape {
public:
    virtual void draw() {
        cout << "Square::Draw()" << endl;
    }
    ~Square() {
        cout << "~Square()" << endl;
    }
};

void testMemFun1();

class Angle {
    int degress;
public:
    explicit Angle(int deg) : degress(deg) {}
    int mul(int times) {
        return degress *= times;
    }
};

void testMemFun2();
void testFindBlanks();

//6.2.6 编写自己的函数对象适配器
class NumStringGen {
    const int sz;
public:
    explicit NumStringGen(int ssz = 5) :sz(ssz) {}
    string operator()() {
        string digits("0123456789");
        const int ndigits = digits.size();
        string r(sz, ' ');
        r[0] = digits[rand() % (ndigits - 1)] + 1;
        for (int i = 1; i < sz; ++i) {
            if (sz >= 3 && i == sz / 2) {
                r[i] = '.';
            } else {
                r[i] = digits[rand() % ndigits];
            }
        }
        return r;
    }
};
void testMemFun3();

//将函数进行组合
//一元组合器
template<typename R, typename E, typename F1, typename F2>
class unary_composer {
    F1 f1;
    F2 f2;
public:
    unary_composer(F1 fone, F2 ftwo) : f1(fone), f2(ftwo) {}
    R operator()(E x) {
        return f1(f2(x));
    }
};
template<typename R, typename E, typename F1, typename F2>
unary_composer<R, E, F1, F2> compose(F1 f1, F2 f2) {
    return unary_composer<R, E, F1, F2>(f1, f2);
}

void testComposeTry();

template<typename F1, typename F2>
//必须使用 typename 来使编译器知道涉及的成员是一个嵌套类型
class unary_composer_ : public unary_function<typename F2::argument_type, typename F1::result_type> {
    F1 f1;
    F2 f2;
public:
    unary_composer_(F1 fone, F2 ftwo) :f1(fone), f2(ftwo) {}
    typename F1::result_type operator()(typename F2::argument_type x) {
        return f1(f2(x));
    }
};

template<typename F1, typename F2>
unary_composer_<F1, F2> compose(F1 f1, F2 f2) {
    return unary_composer_<F1, F2>(f1, f2);
}

void testComposeFinal();

//6.3.1 实例创建的支持工具
template<class T>
struct iterator_traits_ {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};

class NString {
    string s;
    int thisOccurrence;
    typedef map<string, int> words_type;
    static words_type words;
    void addString(const string &x) {
        auto pos = words.find(x);
        if (pos != words.end()) {
            thisOccurrence = ++pos->second;
        } else {
            thisOccurrence = words[x] = 0;
        }
    }

public:
    NString() : thisOccurrence(0) {}
    /*explicit*/ NString(const string &x) : s(x) { addString(x); }
    explicit NString(const char *x) : s(x) { addString(x); }
    friend ostream& operator<<(ostream &os, const NString &ns) {
        return os << ns.s << "[" << ns.thisOccurrence << "]";
    }
    friend bool operator<(const NString &l, const NString &r) {
        return l.s < r.s;
    }
    friend bool operator==(const NString &l, const NString &r) {
        return l.s == r.s;
    }
    friend bool operator>(const NString &l, const NString &r) {
        return l.s > r.s;
    }
    operator const std::string&() const {
        return s;
    }
};

//6.3.2 填充和生成
void testFillGenerate();

//6.3.3 计数
void testCounting();

//6.3.4 操作序列
void testManipulations();

//6.3.5 查找和替换
struct PlusOne {
    bool operator()(int i, int j) {
        return i + 1 == j;
    }
};
class MulMoreThan {
    int value;
public:
    explicit MulMoreThan(int val) : value(val) {}
    bool operator()(int v, int m) {
        return v * m > value;
    }
};

void testSearchReplace();

//6.3.6 比较范围
void testComparison();

//6.3.7 删除元素
struct IsUpper {
    bool operator()(char c) {
        return isupper(c);
    }
};
void testRemoving();

//6.3.8 对已排序的序列进行排序和运算
void testSortedSearchTest();

void testMerge();

void testSetOperations();

//6.3.9 堆运算
class Counted {
    static int count;
    char *ident;
public:
    explicit Counted(char *id) : ident(id) {
        cout << "Counted(" << ident << ") count = " << ++count << endl;
    }
    ~Counted() {
        cout << "~Counted()" << ident << " count = " << --count << endl;
    }
};

class CountedVector : public vector<Counted*> {
public:
    explicit CountedVector(char *id) {
        for (int i = 0; i < 5; ++i) {
            push_back(new Counted(id));
        }
    }
};

template<class T>
class DeleteT {
public:
    void operator()(T *x) {
        delete x;
        x = nullptr;
    }
};

template<class T>
void wipe(T *x) {
    delete x;
    x = nullptr;
}

void testForEach();

template<class T>
T* deleteP(T *x) {
    delete x;
    return x = nullptr;
}

template<class T>
struct Deleter {
    T* operator()(T *x) {
        delete x;
        return x = nullptr;
    }
};

void testTransform();

class Inventory {
    char item;
    int quantity;
    int value;
public:
    Inventory(char it, int quant, int val) : item(it), quantity(quant), value(val) {}
    char getItem() const { return item; }
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
    int getValue() const { return value; }
    void setValue(int val) { value = val; }
    friend ostream& operator<<(ostream &os, const Inventory &inv) {
        return os << inv.item << "(" << inv.quantity << ", " << inv.value << ")" << endl;
    }
};

struct InvenGen {
    Inventory operator()() {
        static char c = 'a';
        random_device rd;
        int q = rd() % 100;
        int v = rd() % 500;
        return Inventory(c++, q, v);
    }
};

class InvAccum {
    int quantity;
    int val;
public:
    InvAccum() : quantity(0), val(0) {}
    void operator()(const Inventory & inv) {
        quantity += inv.getQuantity();
        val += inv.getQuantity() * inv.getValue();
    }
    friend ostream& operator<<(ostream &os, const InvAccum &ia) {
        return os << "total quantity: " << ia.quantity << ", total value: " << ia.val;
    }
};

void testCalcInventory();

struct NewImproved {
    Inventory operator()(const Inventory &inv) {
        return Inventory(toupper(inv.getItem()), inv.getQuantity(), inv.getValue());
    }
};

void testTransformNames();

struct Discounter {
    Inventory operator()(const Inventory &inv, float discount) {
        return Inventory(inv.getItem(), inv.getQuantity(), static_cast<int>(inv.getValue()*(1 - discount)));
    }
};

struct DiscGen {
    float operator()() {
        random_device rd;
        float r = static_cast<float>(rd() % 10);
        return r / 100.0;
    }
};

void testSpecialList();

void testNumeric();



#endif  //GENERIC_ALGORITHM_H

