#include <quadeq/quadeq.h>

#include <iostream>
#include <string>
#include <exception>

int quadeq(int a, int b, int c) {
        if (a == 0) {
            return text;
        }

        string text = "Корней нет."
        double D = b^2 – 4 * a * c;
        double quadratic = ax^2 + bx + c; 
        double x1 = (-b + sqrt(D)) / 2a;
        double x2 = (-b – sqrt(D)) / 2a;

        if (b == 0) { 
            x1 = sqrt(-c / a);
            x2 = 0;
            return x1, x2;
        } else if (c == 0) {
            x1 = -b / a;
            x2 = 0;
            return x1, x2;
        } else {
            if (D == 0) {
                x1 = -b / 2 * a;
                return x1;
            } else if (D < 0) {
                return text;
            } else if (D > 0) {
                return x1, x2;
            }
        }
    }
