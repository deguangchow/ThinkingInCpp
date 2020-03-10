﻿///    Copyright (C) 2020 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    stdafx
///
///    \author   deguangchow
///    \version  1.0
///    \2020/03/10

#pragma once
#ifndef STDAFX_H
#define STDAFX_H
                  
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <functional>
#include <set>
#include <map>
#include <ctime>
#include <numeric>
#include <random>

using std::string;
using std::copy;
using std::remove_copy_if;
using std::vector;
using std::back_inserter;
using std::equal;
using std::cout;
using std::endl;
using std::replace_if;
using std::ostream_iterator;
using std::istream_iterator;
using std::ofstream;
using std::ifstream;
using std::bind1st;
using std::bind2nd;
using std::greater;
using std::count_if;
using std::not1;
using std::not2;
using std::equal_to;
using std::not_equal_to;
using std::binder1st;
using std::unary_function;
using std::binary_function;
using std::set;
using std::strlen;
using std::transform;
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::modulus;
using std::negate;
using std::greater_equal;
using std::less_equal;
using std::less;
using std::logical_and;
using std::logical_or;
using std::logical_not;
using std::generate;
using std::generate_n;
using std::sort;
using std::stable_sort;
using std::ptr_fun;
using std::pointer_to_unary_function;
using std::pointer_to_binary_function;
using std::mem_fun;
using std::mem_fun_ref;
using std::ios;
using std::random_access_iterator_tag;
using std::ptrdiff_t;
using std::pair;
using std::ostream;
using std::fill;
using std::swap_ranges;
using std::reverse;
using std::reverse_copy;
using std::copy_backward;
using std::rotate;
using std::next_permutation;
using std::prev_permutation;
using std::find;
using std::find_if;
using std::adjacent_find;
using std::find_first_of;
using std::find_end;
using std::search;
using std::search_n;
using std::min_element;
using std::max_element;
using std::lexicographical_compare;
using std::mismatch;
using std::unique;
using std::unique_copy;
using std::remove;
using std::remove_if;
using std::partial_sort;
using std::partial_sort_copy;
using std::nth_element;
using std::binary_search;
using std::lower_bound;
using std::upper_bound;
using std::equal_range;
using std::map;
using std::merge;
using std::inplace_merge;
using std::set_union;
using std::includes;
using std::set_intersection;
using std::set_difference;
using std::set_symmetric_difference;
using std::for_each;
using std::accumulate;
using std::inner_product;
using std::partial_sum;
using std::adjacent_difference;
using std::random_device;
using std::to_string;

//在此处引用程序需要的其他头文件
#include "CommonFunctions.h"
#include "PrintSequence.h"
#include "generic_algorithm.h"

#endif  //STDAFX_H


