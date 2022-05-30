#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <vector>
#include <math.h>
#include "znak.h"

using namespace std;



void make_circle_sign(double diam, double length, double r, double dist) 
{
    ofstream out("sign.csv");
    ofstream out_bool("sign_bool.csv");
    ofstream out_se("se.csv");
    vector<Point> vector, vector1;
    Point point;
    int m1 = 0, m = 0;

    point.type = 0;
    for (double i = 0; i > -length; i -= dist)
    {
        point.z = i;
        for (double j = 0; j <= 2*PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            vector.push_back(point);
            m1++;
        }
    }

    for (double i = 0; i < 2 * r; i += dist) 
    {
        point.z = i;
        for (double j = 0; j <= 2 * PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            if (point.x == 0 && point.y == 0) { point.type = 1; }
            else { point.type = 0; }
            vector.push_back(point);
            m1++;
        }
    }
    
    point.type = 1;
    point.y = 0;
    for (double i = 0; i < r; i += dist) 
    {
        for (double j = 0; j <= 2 * PI; j += asin(dist / (r - i)))
        {
            point.x = (r - i) * sin(j);
            point.z = (r - i) * cos(j) + r;
            vector.push_back(point);
            m1++;
        }
    }

    /*for (double i = 0; i < 4 * dist; i += dist)
    {
        for (double j = 0; j <= 2 * PI; j += asin(dist / (4 * dist - i)))
        {
            point.x = (4 * dist - i) * sin(j);
            point.z = (4 * dist - i) * cos(j);
            vector1.push_back(point);
            m++;
        }
        /*point.z = i;
        for (double j = -dist * 2; j < 2 * dist; j += dist)
        {
            point.x = j;
            if ((i != 0 || j != -dist * 2) && (i != 0 || j != dist) && (i != 3*dist || j != dist) && (i != 3 * dist || j != -dist * 2))
            {
                vector1.push_back(point);
                m++;
            }
        }
    }*/

    point.x = 0;
    point.y = 0;
    point.z = 0;
    for (double i = -dist; i <= dist; i += dist) 
    {
        point.x = i;
        vector1.push_back(point);
        m++;
    }
    point.x = 0;
    for (double i = -dist; i <= dist; i += dist)
    {
        if (i != 0) 
        {
            point.z = i;
            vector1.push_back(point);
            m++;
        }
    }

    if (!out.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out << vector[i].x << "," << vector[i].y << "," << vector[i].z << endl;
        }
        out.close();
    }
    if (!out_se.bad())
    {
        for (int i = 0; i < m; i++)
        {
            out_se << vector1[i].x << "," << vector1[i].y << "," << vector1[i].z << endl;
        }
        out_se.close();
    }
    if (!out_bool.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out_bool << vector[i].x << "," << vector[i].y << "," << vector[i].z << "," << vector[i].type << endl;
        }
        out_bool.close();
    }
    cout << "circle sign is made" << endl;
}

void make_triangle_sign(double diam, double p_length, double s_length, double dist) 
{
    ofstream out("sign.csv");
    ofstream out_bool("sign_bool.csv");
    ofstream out_se("se.csv");
    vector<Point> vector, vector1;
    Point point;
    int m1 = 0, m = 0;

    point.type = 0;
    for (double i = 0; i > -p_length; i -= dist)
    {
        point.z = i;
        for (double j = 0; j <= 2 * PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            vector.push_back(point);
            m1++;
        }
    }

    for (double i = 0; i < sqrt(3) / 2 * s_length; i += dist)
    {
        point.z = i;
        for (double j = 0; j <= 2 * PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            if (point.x == 0 && point.y == 0) { point.type = 1; }
            else { point.type = 0; }
            vector.push_back(point);
            m1++;
        }
    }

    point.type = 1;
    point.y = 0;
    double k = 0;
    for (double i = 0; i < sqrt(3) / 2 * s_length; i += sqrt(3) / 2 * dist)
    {
        point.z = i;
        for (double j = -((s_length - k) / 2); j < (s_length - k) / 2; j += dist)
        {
            point.x = j;
            vector.push_back(point);
            m1++;
        }
        k += dist;
    }

    k = 0;
    for (double i = 0; i < sqrt(3) / 2 * (dist * 4); i += sqrt(3) / 2 * dist)
    {
        point.z = i;
        for (double l = -((dist * 4 - k) / 2); l < (dist * 4 - k) / 2; l += dist)
        {
            if (abs(((dist * 4) - k) / 2 - l) > 0.000000000000001)
            {
                point.x = l;
                vector1.push_back(point);
                m++;
            }
            /*point.x = l;
            vector1.push_back(point);
            m++;
            if (((dist * 4) - k) / 2 >= l) cout << ((dist * 4) - k) / 2 - l << endl;
            */
        }

        k += dist;
    }




    if (!out.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out << vector[i].x << "," << vector[i].y << "," << vector[i].z << endl;
        }
        out.close();
    }
    if (!out_se.bad())
    {
        for (int i = 0; i < m; i++)
        {
            out_se << vector1[i].x << "," << vector1[i].y << "," << vector1[i].z << endl;
        }
        out_se.close();
    }
    if (!out_bool.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out_bool << vector[i].x << "," << vector[i].y << "," << vector[i].z << "," << vector[i].type << endl;
        }
        out_bool.close();
    }
    cout << "triangle sign is made" << endl;
}

void make_rectangle_sign(double diam, double p_length,double s_height, double s_length, double dist) 
{
    ofstream out("sign.csv");
    ofstream out_bool("sign_bool.csv");
    ofstream out_se("se.csv");
    vector<Point> vector, vector1;
    Point point;
    int m1 = 0,m = 0;

    point.type = 0;
    for (double i = 0; i > -p_length; i -= dist)
    {
        point.z = i;
        for (double j = 0; j <= 2 * PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            vector.push_back(point);
            m1++;
        }
    }

    for (double i = 0; i < s_height; i += dist)
    {
        point.z = i;
        for (double j = 0; j <= 2 * PI; j += asin(dist / (diam / 2)))
        {
            point.x = diam / 2 * sin(j);
            point.y = diam / 2 * cos(j) - diam / 2;
            if (point.x == 0 && point.y == 0) { point.type = 1; }
            else { point.type = 0; }
            vector.push_back(point);
            m1++;
        }
    }

    point.type = 1;
    point.y = 0;
    if (s_height > s_length) 
    {
        for (double k = 0; k < s_length; k += dist) 
        {
            for (double i = 0; i < s_height - k; i += dist)
            {
                point.z = i;
                for (double j = -((s_length - k) / 2); j < (s_length - k) / 2; j += dist)
                {
                    point.x = j;
                    vector.push_back(point);
                    m1++;
                }
            }
        }
    }
    else
    {
        for (double k = 0; k < s_height; k += dist)
        {
            for (double i = 0; i < s_height - k; i += dist)
            {
                point.z = i;
                for (double j = -((s_length - k) / 2); j < (s_length - k) / 2; j += dist)
                {
                    point.x = j;
                    vector.push_back(point);
                    m1++;
                }
            }
        }
    }

    point.x = 0;
    point.y = 0;
    point.z = 0;
    

    for (double i = -dist * 2; i < 2 * dist; i += dist)
    {
        point.z = i;
        for (double j = -dist * 2; j < 2 * dist; j += dist) 
        {
            point.x = j;
            vector1.push_back(point);
            m++;
        }
    }


    if (!out.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out << vector[i].x << "," << vector[i].y << "," << vector[i].z << endl;
        }
        out.close();
    }
    if(!out_se.bad())
    {
        for (int i = 0; i < m; i++)
        {
            out_se << vector1[i].x << "," << vector1[i].y << "," << vector1[i].z << endl;
        }
        out_se.close();
    }
    if (!out_bool.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            out_bool << vector[i].x << "," << vector[i].y << "," << vector[i].z << "," << vector[i].type << endl;
        }
        out_bool.close();
    }
    cout << "rectangle sign is made" << endl;
}

/*int main()
{
    setlocale(LC_ALL, "Russian");
    double type;

    cout << "Выберите форму знака:" << endl;
    cout << "1) круг;" << endl;
    cout << "2) треугольник;" << endl;
    cout << "3) прямоугольник." << endl;
    cin >> type;
    double r, diam, s_length, p_length, dist, s_height;

    if (type == 1) 
    {
        cout << "Введите радиус окружности(в см)" << endl;
        cin >> r;
        cout << "Введите диаметр стойки(в см)" << endl;
        cin >> diam;
        cout << "Введите длину стойки(в см)" << endl;
        cin >> p_length;
        cout << "Введите расстояние между точками(в см)" << endl;
        cin >> dist;
        make_circle_sign(diam, p_length, r, dist);
    }
    else if (type == 3) 
    {
        cout << "Введите высоту знака(в см)" << endl;
        cin >> s_height;
        cout << "Введите ширину знака(в см)" << endl;
        cin >> s_length;
        cout << "Введите диаметр стойки(в см)" << endl;
        cin >> diam;
        cout << "Введите длину стойки(в см)" << endl;
        cin >> p_length;
        cout << "Введите расстояние между точками(в см)" << endl;
        cin >> dist;
        make_rectangle_sign(diam, p_length, s_height, s_length, dist);

    }
    else if (type == 2) 
    {
        cout << "Введите длину стороны знака(в см)" << endl;
        cin >> s_length;
        cout << "Введите диаметр стойки(в см)" << endl;
        cin >> diam;
        cout << "Введите длину стойки(в см)" << endl;
        cin >> p_length;
        cout << "Введите расстояние между точками(в см)" << endl;
        cin >> dist;
        make_triangle_sign(diam, p_length, s_length, dist);
    }
    else { cout << "Ошибка: нет такого варианта ответа!" << endl; }




    
    return 0;
}*/


