///    Copyright (C) 2018 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    Common Functions.
///
///    \author   deguangchow
///    \version  1.0
///    \2019/07/05

#pragma once
#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

namespace common_functions {

//清理vector<T>
template<typename T>
static void purge(vector<T*>& vctData) {
    for (int i = 0; i < vctData.size(); ++i) {
        if (vctData[i]) {
            delete vctData[i];
            vctData[i] = nullptr;
        }
    }
    vctData.clear();
}


}//namespace common_functions

#endif  //COMMON_FUNCTIONS_H
