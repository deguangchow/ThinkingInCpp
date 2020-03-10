///    Copyright (C) 2018 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    Print the contents of any sequence.
///
///    \author   deguangchow
///    \version  1.0
///    \2019/07/03

#pragma once
#ifndef PRINT_SEQUENCE_H
#define PRINT_SEQUENCE_H

template<typename Iter>
void print(Iter first, Iter last, const char* nm = "", const char* sep = " ", std::ostream& os = std::cout) {
    if (nm != nullptr && *nm != '\0') {
        os << nm << ": " << sep;
    }
    typedef typename std::iterator_traits<Iter>::value_type T;
    std::copy(first, last, std::ostream_iterator<T>(std::cout, sep));
    os << std::endl;
}

#endif  //PRINT_SEQUENCE_H
