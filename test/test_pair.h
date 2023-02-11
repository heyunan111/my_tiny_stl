//
// Created by hyn on 2023/2/11.
//

#ifndef MY_TINY_STL_TEST_PAIR_H
#define MY_TINY_STL_TEST_PAIR_H

#include "..\stl\utility.h"
#include <iostream>

void test_pair() {
    hyn::stl::pair<int, int> pair1(1, 2);
    hyn::stl::pair<int, int> pair2(1, 3);

    using namespace std;
    std::cout << pair1.first << pair1.second << std::endl;
    if (pair1 == pair2)
        std::cout << "=" << std::endl;


    if (pair1 > pair2)
        cout << ">" << endl;
    if (pair1 >= pair2)
        cout << ">=" << endl;
    if (pair1 < pair2)
        cout << "<" << endl;
    if (pair1 <= pair2)
        cout << "<=" << endl;
}

#endif //MY_TINY_STL_TEST_PAIR_H
