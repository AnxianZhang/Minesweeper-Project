/**
 * @file Case.h
 * @author Anxian Zhang (gadanxianzhang@gmail.com.com)
           Vick Ye (vickye2908@gmail.com)
 * @brief Component of case(s)
 * @version 1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _CASE_
#define _CASE_

enum CaseState { UNMASK, MARK, HIDE };

struct Case {
    unsigned int content;
    CaseState state;
};

#endif // !_CASE_

