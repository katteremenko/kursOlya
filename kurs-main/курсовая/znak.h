#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <vector>
#include <math.h>

const double PI = acos(-1.0);

class Point {
public:
    double x;
    double y;
    double z;
    int type;

    Point() {}
};

void make_circle_sign(double diam, double length, double r, double dist);
void make_triangle_sign(double diam, double p_length, double s_length, double dist);
void make_rectangle_sign(double diam, double p_length, double s_height, double s_length, double dist);
