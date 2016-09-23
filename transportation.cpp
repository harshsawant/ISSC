/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "OR.hpp"
#include <iostream>
using namespace std;

int matrix[20][20], rows, cols, dem1[20], sup1[20];
int matrix2[20][20], cost[20][20];
int i, j, sum;

//function to get required input from user

void OR::TransportationgetInput() {
    int s1 = 0, s2 = 0;
    fstream fin("Example.txt");
    //	cout << "\n Enter the row & column i.e. matrix matrix :: ";
    fin >> rows >> cols;

    //	cout << "\n Enter the matrix matrix :: ";
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fin >> matrix[i][j];
            matrix2[i][j] = matrix[i][j];
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            cost[i][j] = 0;
        }
    }

    //	cout << "\n Enter the demand rows :: ";
    for (i = 0; i < cols; i++)
        fin >> dem1[i];

    //	cout << "\n Enter the supply column :: ";
    for (i = 0; i < rows; i++)
        fin >> sup1[i];

    for (i = 0; i < cols; i++)
        s1 += dem1[i];
    for (i = 0; i < rows; i++)
        s2 += sup1[i];

    cout << "\n****Matrix****\n";
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            cout << matrix[i][j] << " ";
        cout << sup1[i];
        cout << "\n";
    }
    for (j = 0; j < cols; j++)
        cout << dem1[j] << " ";

    if (s1 == s2)
        cout << "\n\nProblem is balanced\n";
    else {
        cout << "\n\nProblem is not balanced\n";
        //		exit(0);
    }
}

//function to find optimized value of Z by using North-West Corner Method

void OR::northWestCorner() {
    int dem[20], sup[20];
    for (i = 0; i < cols; ++i)
        dem[i] = dem1[i]; //stored into another array for further processing
    for (i = 0; i < rows; ++i)
        sup[i] = sup1[i]; //stored into another array for further processing

    for (i = 0, j = 0; (i < rows && j < cols);) {
        if (sup[i] < dem[j]) { //when supply < demands
            sum += matrix[i][j] * sup[i];
            dem[j] -= sup[i];
            i++;
        } else if (sup[i] > dem[j]) { //when supply > demands
            sum += matrix[i][j] * dem[j];
            sup[i] -= dem[j];
            j++;
        } else if (sup[i] == dem[j]) { //when supply = demands
            sum += matrix[i][j] * dem[j];
            i++;
            j++;
        }
    }
    cout << "\n\nCost by North-West Corner method :: " << sum << endl;
    sum = 0;
}

void OR::LeastcostMethod() {
    int b, d, c1, c2, p, q;
    int rf[20], cf[20];
    int min;
    int dem[20], sup[20];
    for (i = 0; i < cols; ++i)
        dem[i] = dem1[i];
    for (i = 0; i < rows; ++i)
        sup[i] = sup1[i];

    for (i = 0; i < rows; i++)
        rf[i] = 0;
    for (i = 0; i < cols; i++)
        cf[i] = 0;
    b = rows;
    d = cols;
    while (b > 0 && d > 0) {
        min = 1000; //to compare with other values
        for (i = 0; i < rows; i++) //to find minimum element from matrix matrix
        {
            if (rf[i] != 1) {
                for (j = 0; j < cols; j++) {
                    if (cf[j] != 1) {
                        if (min > matrix[i][j]) {
                            min = matrix[i][j];
                            p = i; //storing index of minimum element
                            q = j; //storing index of minimum element
                        }
                    }
                }
            }
        }
        if (sup[p] < dem[q])
            c1 = sup[p];
        else
            c1 = dem[q];
        for (i = 0; i < rows; i++) // parse whole matrix again considering minimum element
        {
            if (rf[i] != 1) {
                for (j = 0; j < cols; j++) {
                    if (cf[j] != 1) {
                        if (min == matrix[i][j]) {
                            if (sup[i] < dem[j])
                                c2 = sup[i];
                            else
                                c2 = dem[j];
                            if (c2 > c1) {
                                c1 = c2;
                                p = i; //storing index
                                q = j; //storing index
                            }
                        }
                    }
                }
            }
        }
        // cout << min << p << q;
        if (sup[p] < dem[q]) // allocate supply
        {
            sum = sum + matrix[p][q] * sup[p];
            dem[q] -= sup[p];
            rf[p] = 1;
            b--;
        } else if (sup[p] > dem[q]) // allocate demand
        {
            sum = sum + matrix[p][q] * dem[q];
            sup[p] -= dem[q];
            cf[q] = 1;
            d--;
        } else if (sup[p] == dem[q]) // balanced end condition
        {
            sum = sum + matrix[p][q] * sup[p];
            rf[p] = 1;
            cf[q] = 1;
            b--;
            d--;
        }
        //cout <<"\n %d",sum);
    } //while
    cout << "\n\n matrix by Least matrix method :: " << sum << endl;
    sum = 0;
}

