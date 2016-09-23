/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OR.hpp
 * Author: harsh
 *
 * Created on 30 August, 2016, 10:05 PM
 */

#ifndef OR_HPP
#define OR_HPP
#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include <iomanip>
#define CMAX  100
#define VMAX  100
using namespace std;

class OR {
public:

    void getInput();
    void display();
    void findPivot();
    void Formula();
    void Optimize();
    void solution();
    void TransportationgetInput();
    void northWestCorner();
    void LeastcostMethod();



};



#endif /* OR_HPP */

