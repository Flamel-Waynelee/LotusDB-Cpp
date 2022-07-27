/**
 * @file main.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief main函数
 * @date 2022-07-22
 */

#include "lotus_db.h"
#include "pch.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main() {

    LotusDb lotus_db;
    // lotus_db.write("1234", "12345");
    // getchar();
    cout << lotus_db.read("1234") << endl;
    getchar();
    
    return 0;
}
