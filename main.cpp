/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: harsh
 *
 * Created on 30 August, 2016, 10:04 PM
 */

#include <cstdlib>
#include <iostream>
#include "OR.hpp"

using namespace std;

int main() {
    int ch;
    OR o;
    
   
    while (3) {
        cout << "\n************** MENU ***************";
        cout << "\n1. North-West Corner Method";
        cout << "\n2. Least-Cost Method";
        cout << "\n3. Simplex Method";
        //cout << "\n3. Vogel's Approximation Method\n";
        cout << "\nEnter your choice :: ";
        cin >> ch;
        switch (ch) {
            case 1:
                o.TransportationgetInput();
                o.northWestCorner();
                break;
            case 2:
                o.TransportationgetInput();
                o.LeastcostMethod();
                break;
            case 3:
                o.getInput();
                o.solution();
                break; 
            default:
                exit(0);
        }
    }
    return 0;
}
