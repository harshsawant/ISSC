/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "OR.hpp"
#include <iostream>
using namespace std;

int noc, nov, not_optimal, piv1, piv2, err;
double Mat[CMAX][VMAX];

//function to get input from user

void OR::getInput() {
    double R1, R2;
    char choice;
    int i, j;
    cout << "\n ---------Simplex Method---------\n";
    cout << "\nMAXIMIZE OR MINIMIZE LINEAR PROGRAMMING PROBLEM OR NOT(y/n) ? ";
    cin >> choice;
    cout << "\nHow Many Variables Of MAXIMIZE OR MINIMIZE AT (Z) FUNCTION ? ";
    cin >> nov;
    cout << "\nHow Many SUBJECT TO: No. Of Constraints ? ";
    cin >> noc;
    if (choice == 'Y' || choice == 'y')
        R1 = 1.0;
    else
        R1 = -1.0;

    cout << "\nEnter " << nov << " COEFFICIENTS OF MAXIMIZE OR MINIMIZE AT (Z) FUNCTION :: ";
    for (j = 1; j <= nov; j++) {
        cin >> R2;
        Mat[1][j + 1] = R2 * R1;
    }
    R2 = 0;
    Mat[1][1] = R2 * R1;

    for (i = 1; i <= noc; i++) {
        cout << "\nEnter " << nov << " COEFFICIENTS WITH SUBJECT TO: For Constraint AND Equality  "
                << i << "  :: ";
        for (j = 1; j <= nov; j++) {
            cin >> R2;
            Mat[i + 1][j + 1] = -R2;
        }
        cin >> Mat[i + 1][1];
    }
}

//function to display matrix

void OR::display() {
    cout << fixed;
    cout << setprecision(0);
    cout << "\n";
    for (int i = 0; i < noc + 2; ++i) {
        cout << "\n## ";
        for (int j = 0; j < nov + 2; ++j) {
            cout << "  " << Mat[i][j];
        }
    }
}

//function to find out the pivot cell

void OR::findPivot() {
    double R, V, max;
    int i, j;

    max = 0.0;
    for (j = 2; j <= nov + 1; j++) {
        if (Mat[1][j] > 0.0 && Mat[1][j] > max) {
            max = Mat[1][j];
            piv2 = j;
        }
    }

    R = 999999.0; //to find minimum value
    for (i = 2; i <= noc + 1; i++) {
        if (Mat[i][piv2] >= 0.0)
            continue;
        V = fabs(Mat[i][1] / Mat[i][piv2]); // ratio
        if (V < R) {
            R = V;
            piv1 = i; // min ratio >= 0
        }
    }
    cout << "\nFIRST: Pivote1 = " << piv1 << "  Pivote2 = " << piv2;
    cout << "\n Swapping : " << Mat[piv1][0] << " with " << Mat[0][piv2];
    V = Mat[0][piv2];
    Mat[0][piv2] = Mat[piv1][0];
    Mat[piv1][0] = V;
}

void OR::Formula() {
    int i, j;

    for (i = 1; i <= noc + 1; i++) // make other column elements zero
    {
        if (i == piv1)
            continue;
        for (j = 1; j <= nov + 1; j++) {
            if (j == piv2)
                continue;
            Mat[i][j] -= Mat[piv1][j] * Mat[i][piv2] / Mat[piv1][piv2];
        }
    }

    Mat[piv1][piv2] = 1.0 / Mat[piv1][piv2]; // make pivote element as 1

    for (j = 1; j <= nov + 1; j++) // make positive if pivote become -1
    {
        if (j == piv2)
            continue;
        Mat[piv1][j] *= fabs(Mat[piv1][piv2]);
    }

    for (i = 1; i <= noc + 1; i++) {
        if (i == piv1)
            continue;
        Mat[i][piv2] *= Mat[piv1][piv2];
    }
}

//Optimization function

void OR::Optimize() {
    int i, j;
    for (i = 2; i <= noc + 1; i++) // check if any Xb is negative or not
        if (Mat[i][1] < 0.0)
            err = 1;
    not_optimal = 0;
    if (err == 1)
        return;
    for (j = 2; j <= nov + 1; j++) // check if any Zj-Cj is > 0 then do next itr
        if (Mat[1][j] > 0.0)
            not_optimal = 1;
}

void OR::solution() {
    cout << "\n Solution :: \n";
    for (int j = 1; j <= nov; j++)
        Mat[0][j + 1] = j;
    for (int i = nov + 1; i <= nov + noc; i++)
        Mat[i - nov + 1][0] = i;
    display();
    do {
        findPivot();
        Formula();
        Optimize();
        display();
    } while (not_optimal == 1);

    if (err == 0) {
        for (int i = 1; i <= nov; i++)
            for (int j = 2; j <= noc + 1; j++) {
                if (Mat[j][0] != 1.0 * i)
                    continue;
                cout << "\n Variable " << i << " :: " << Mat[j][1] << "\n";
            }
        cout << "\n Object Function :: " << Mat[1][1] << "\n";
        cout << "\n";
    } else {
        cout << "\n No Solution.\n";
        cout << "\n";
    }
}