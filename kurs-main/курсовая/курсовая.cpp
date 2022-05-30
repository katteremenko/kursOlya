// курсовая.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <vector>
#include <math.h> 
#include "znak.h"

using namespace std;

/*/class Point {
public:
    double x;
    double y;
    double z;
    int type;

    Point() {}
};*/

void make_dilatazia(vector<Point> v, int m, vector<Point> se, int n, int g)
{
    ofstream dil_out("dilatazia.csv");
    vector<Point> dilatazia;
    int m1 = m;
    for (int i = 0; i < m; i++)
    {
        dilatazia.push_back(v[i]);
    }

    double** Mas = new double* [m];
    for (int i = 0; i < m; i++)
        Mas[i] = new double[5];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++) { Mas[i][j] = DBL_MAX; }
    }
    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++) { cout << Mas[i][j] << ";"; }
        cout << endl;
    }*/

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i != j)
            {
                double dist = sqrt((v[i].x - v[j].x) * (v[i].x - v[j].x) + (v[i].y - v[j].y) * (v[i].y - v[j].y) + (v[i].z - v[j].z) * (v[i].z - v[j].z));
                if (dist != 0)
                {
                    if (dist < Mas[i][0])
                    {
                        if (dist < Mas[i][1])
                        {
                            if (dist < Mas[i][2])
                            {
                                if (dist < Mas[i][3])
                                {
                                    if (dist < Mas[i][4])
                                    {
                                        double c4 = Mas[i][4];
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][4] = dist;
                                        Mas[i][3] = c4;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                    else
                                    {
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][3] = dist;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                }
                                else
                                {
                                    double c1 = Mas[i][2];
                                    double c2 = Mas[i][1];
                                    Mas[i][2] = dist;
                                    Mas[i][1] = c1;
                                    Mas[i][0] = c2;
                                }
                            }
                            else
                            {
                                double c = Mas[i][1];
                                Mas[i][1] = dist;
                                Mas[i][0] = c;
                            }
                        }
                        else { Mas[i][0] = dist; }
                    }
                }
            }
        }
    }

    double* dpp = new double[m];
    for (int i = 0; i < m; i++) { dpp[i] = 0; }

    for (int i = 0; i < m; i++)
    {
        if (m <= 5) 
        {
            for (int j = m; j > 5 - m; j--)
            {
                dpp[i] = dpp[i] + Mas[i][j];
            }
            dpp[i] = dpp[i] / 5;
        }
        else 
        {
            for (int j = 0; j < 5; j++)
            {
                dpp[i] = dpp[i] + Mas[i][j];
            }
            dpp[i] = dpp[i] / 5;
        }
    }


    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++) { cout << Mas[i][j] << ";"; }
        cout << endl;
    }*/
    //for (int i = 0; i < m; i++) { cout << dpp[i] << endl; }

    Point* SE = new Point[n];

    for (int i = 0; i < m; i++)
    {
        SE[g].x = v[i].x;
        SE[g].y = v[i].y;
        SE[g].z = v[i].z;

        double X, Y, Z;
        X = SE[g].x - se[g].x;
        Y = SE[g].y - se[g].y;
        Z = SE[g].z - se[g].z;

        for (int j = 0; j < n; j++)
        {
            SE[j].x = se[j].x + X;
            SE[j].y = se[j].y + Y;
            SE[j].z = se[j].z + Z;
        }
        //cout << endl << "x=" << v[i].x << "y=" << v[i].y << "z=" << v[i].z << endl;
        for (int j = 0; j < n; j++)
        {
            bool flag = false;
            //cout << "x=" << SE[j].x << "y=" << SE[j].y << "z=" << SE[j].z << endl;
            for (int l = 0; l < m; l++)
            {
                double dist = sqrt((v[l].x - SE[j].x) * (v[l].x - SE[j].x) + (v[l].y - SE[j].y) * (v[l].y - SE[j].y) + (v[l].z - SE[j].z) * (v[l].z - SE[j].z));
                if (dist <= 0.5*dpp[l])flag = true;
                //cout << dist << "<=" << 0.5 * dpp[l] << endl;
            }
            
            if (flag != true)
            {
                //cout << "x=" << SE[j].x << " y=" << SE[j].y << " z=" << SE[j].z << endl;
                dilatazia.push_back(SE[j]);
                m1++;
            }
        }
       // cout << endl;
    }

    if (!dil_out.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            dil_out << dilatazia[i].x << "," << dilatazia[i].y << "," << dilatazia[i].z << endl;
        }
        dil_out.close();
    }

    cout << "dilation complete " << endl;
}

void make_erosia(vector<Point> v, int m, vector<Point> se, int n, int g)
{
    int m1 = m;
    vector<Point> erosia;
    ofstream er_out("erosia.csv");
    double** Mas = new double* [m];
    for (int i = 0; i < m; i++)
        Mas[i] = new double[5];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++) { Mas[i][j] = DBL_MAX; }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i != j)
            {
                double dist = sqrt((v[i].x - v[j].x) * (v[i].x - v[j].x) + (v[i].y - v[j].y) * (v[i].y - v[j].y) + (v[i].z - v[j].z) * (v[i].z - v[j].z));
                if (dist != 0)
                {
                    if (dist < Mas[i][0])
                    {
                        if (dist < Mas[i][1])
                        {
                            if (dist < Mas[i][2])
                            {
                                if (dist < Mas[i][3])
                                {
                                    if (dist < Mas[i][4])
                                    {
                                        double c4 = Mas[i][4];
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][4] = dist;
                                        Mas[i][3] = c4;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                    else
                                    {
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][3] = dist;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                }
                                else
                                {
                                    double c1 = Mas[i][2];
                                    double c2 = Mas[i][1];
                                    Mas[i][2] = dist;
                                    Mas[i][1] = c1;
                                    Mas[i][0] = c2;
                                }
                            }
                            else
                            {
                                double c = Mas[i][1];
                                Mas[i][1] = dist;
                                Mas[i][0] = c;
                            }
                        }
                        else { Mas[i][0] = dist; }
                    }
                }
            }
        }
    }

    double* dpp = new double[m];
    for (int i = 0; i < m; i++) { dpp[i] = 0; }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dpp[i] = dpp[i] + Mas[i][j];
        }
        dpp[i] = dpp[i] / 5;

    }

    //for (int i = 0; i < m; i++) { cout << dpp[1] << endl; }

    Point* SE = new Point[n];

    for (int i = 0; i < m; i++)
    {
        SE[g].x = v[i].x;
        SE[g].y = v[i].y;
        SE[g].z = v[i].z;
        
        double X, Y, Z;
        X = SE[g].x - se[g].x;
        Y = SE[g].y - se[g].y;
        Z = SE[g].z - se[g].z;

        for (int j = 0; j < n; j++) 
        {
            SE[j].x = se[j].x + X;
            SE[j].y = se[j].y + Y;
            SE[j].z = se[j].z + Z;
        }

        bool* flag = new bool[n];
        for (int j = 0; j < n; j++) { flag[j] = false; }
        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < m; l++)
            {
                double dist = sqrt((v[l].x - SE[j].x) * (v[l].x - SE[j].x) + (v[l].y - SE[j].y) * (v[l].y - SE[j].y) + (v[l].z - SE[j].z) * (v[l].z - SE[j].z));
                //cout << dist << endl;
                if (dist <= 0.5 * dpp[l])flag[j] = true;
            }
        }
        erosia.push_back(v[i]);

        bool flag2 = true;
        for (int j = 0; j < n; j++) 
        {
            if (flag[j] != true) { flag2 = false; }
        }

        if (flag2 != true)
        {
            erosia.pop_back();
            m1--;
        }
    }

    if (!er_out.bad())
    {
        for (int i = 0; i < m1; i++)
        {
            er_out << erosia[i].x << "," << erosia[i].y << "," << erosia[i].z << endl;
        }
        er_out.close();
    }

    cout << "erosion complete "<< endl;
}

void make_opening(vector<Point> v, int m, vector<Point> se, int n, int g)
{
    make_erosia(v, m, se, n, g);

    ifstream erosia("erosia.csv");
    string line, str;
    vector<Point> vector;
    Point point;
    int m1 = 0;

    while (getline(erosia, line))
    {
        stringstream ss(line);
        int idx = 0;
        while (getline(ss, str, ','))
        {
            if (idx == 0)
            {
                stringstream Str;
                Str << str;
                Str >> point.x;
            }
            else if (idx == 1)
            {
                stringstream Str;
                Str << str;
                Str >> point.y;
            }
            else if (idx == 2)
            {
                stringstream Str;
                Str << str;
                Str >> point.z;
            }
            idx++;
        }
        vector.push_back(point);
        m1++;
    }
    make_dilatazia(vector, m1, se, n, g);

    cout << "opening complete" << endl;
}

double check(vector<Point> v, int m) 
{
    ifstream dilatazia("dilatazia.csv");
    string line, str;
    vector<Point> vector;
    Point point;
    int m1 = 0;
    while (getline(dilatazia, line))
    {
        stringstream ss(line);
        int idx = 0;
        while (getline(ss, str, ','))
        {
            if (idx == 0)
            {
                stringstream Str;
                Str << str;
                Str >> point.x;
            }
            else if (idx == 1)
            {
                stringstream Str;
                Str << str;
                Str >> point.y;
            }
            else if (idx == 2)
            {
                stringstream Str;
                Str << str;
                Str >> point.z;
            }
            idx++;
        }
        vector.push_back(point);
        m1++;
    }

    double** Mas = new double* [m];
    for (int i = 0; i < m; i++)
        Mas[i] = new double[5];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++) { Mas[i][j] = DBL_MAX; }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i != j)
            {
                double dist = sqrt((v[i].x - v[j].x) * (v[i].x - v[j].x) + (v[i].y - v[j].y) * (v[i].y - v[j].y) + (v[i].z - v[j].z) * (v[i].z - v[j].z));
                if (dist != 0)
                {
                    if (dist < Mas[i][0])
                    {
                        if (dist < Mas[i][1])
                        {
                            if (dist < Mas[i][2])
                            {
                                if (dist < Mas[i][3])
                                {
                                    if (dist < Mas[i][4])
                                    {
                                        double c4 = Mas[i][4];
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][4] = dist;
                                        Mas[i][3] = c4;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                    else
                                    {
                                        double c3 = Mas[i][3];
                                        double c1 = Mas[i][2];
                                        double c2 = Mas[i][1];
                                        Mas[i][3] = dist;
                                        Mas[i][2] = c3;
                                        Mas[i][1] = c1;
                                        Mas[i][0] = c2;
                                    }
                                }
                                else
                                {
                                    double c1 = Mas[i][2];
                                    double c2 = Mas[i][1];
                                    Mas[i][2] = dist;
                                    Mas[i][1] = c1;
                                    Mas[i][0] = c2;
                                }
                            }
                            else
                            {
                                double c = Mas[i][1];
                                Mas[i][1] = dist;
                                Mas[i][0] = c;
                            }
                        }
                        else { Mas[i][0] = dist; }
                    }
                }
            }
        }
    }

    double* dpp = new double[m];
    for (int i = 0; i < m; i++) { dpp[i] = 0; }

    for (int i = 0; i < m; i++)
    {
        if (m <= 5)
        {
            for (int j = m; j > 5 - m; j--)
            {
                dpp[i] = dpp[i] + Mas[i][j];
            }
            dpp[i] = dpp[i] / 5;
        }
        else
        {
            for (int j = 0; j < 5; j++)
            {
                dpp[i] = dpp[i] + Mas[i][j];
            }
            dpp[i] = dpp[i] / 5;
        }
    }


    int one = 0, zero = 0, none =0;
    for (int i = 0; i < m1; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            /*double dist = sqrt((v[j].x - vector[i].x) * (v[j].x - vector[i].x) + (v[j].y - vector[i].y) * (v[j].y - vector[i].y) + (v[j].z - vector[i].z) * (v[j].z - vector[i].z));
            if (dist <= 0.5 * dpp[j]) 
            {
                if (v[j].type == 1) { one++; cout << i << " " << j << endl; }
                else { zero++; }
                break;
            }*/
            if (v[j].x == vector[i].x && v[j].y == vector[i].y && v[j].z == vector[i].z) 
            {
                if (v[j].type == 1) { one++; /*cout << i << " " << j << endl;*/ }
                else if (v[j].type == 0) { zero++; }
                else { none++; }
                break;
            }
        }
    }
    int n = 0;
    for (int i = 0; i < m; i++) 
    {
        if (v[i].type == 1)n++;
    }

    //cout << zero + one + none<< endl;
    //cout << n << endl;
    //cout << zero << " " << one << " " << none << endl;
    return one * 100 / (zero + one + none);
}

void do_stuff() 
{
    fstream excel;
    excel.open("stat.xls", ios::app);
    ifstream bunny("sign.csv");
    ifstream bunny1("sign_bool.csv");
    ifstream se("se.csv");

    if (!bunny.is_open()) cout << "Can't open the 1st file" << endl;
    if (!se.is_open()) cout << "Can't open the 2nd file" << endl;
    if (!bunny1.is_open()) cout << "Can't open the 3d file" << endl;
    string line, str;
    vector<Point> vector, SE, vector1;
    Point point;
    int m = 0, n = 0, m1 = 0;
    while (getline(bunny, line))
    {
        stringstream ss(line);
        int idx = 0;
        while (getline(ss, str, ','))
        {
            if (idx == 0)
            {
                stringstream Str;
                Str << str;
                Str >> point.x;
            }
            else if (idx == 1)
            {
                stringstream Str;
                Str << str;
                Str >> point.y;
            }
            else if (idx == 2)
            {
                stringstream Str;
                Str << str;
                Str >> point.z;
            }
            idx++;
        }
        vector.push_back(point);
        m++;
    }

    while (getline(se, line))
    {
        stringstream ss(line);
        int idx = 0;
        while (getline(ss, str, ','))
        {
            if (idx == 0)
            {
                stringstream Str;
                Str << str;
                Str >> point.x;
            }
            else if (idx == 1)
            {
                stringstream Str;
                Str << str;
                Str >> point.y;
            }
            else if (idx == 2)
            {
                stringstream Str;
                Str << str;
                Str >> point.z;
            }
            idx++;
        }
        SE.push_back(point);
        n++;
    }

    while (getline(bunny1, line))
    {
        stringstream ss(line);
        int idx = 0;
        while (getline(ss, str, ','))
        {
            if (idx == 0)
            {
                stringstream Str;
                Str << str;
                Str >> point.x;
            }
            else if (idx == 1)
            {
                stringstream Str;
                Str << str;
                Str >> point.y;
            }
            else if (idx == 2)
            {
                stringstream Str;
                Str << str;
                Str >> point.z;
            }
            else if (idx == 3)
            {
                stringstream Str;
                Str << str;
                Str >> point.type;
            }
            idx++;
        }
        vector1.push_back(point);
        m1++;
    }

    double minsum = DBL_MAX;
    int g;
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < n; j++)
        {
            double dist = sqrt((SE[i].x - SE[j].x) * (SE[i].x - SE[j].x) + (SE[i].y - SE[j].y) * (SE[i].y - SE[j].y) + (SE[i].z - SE[j].z) * (SE[i].z - SE[j].z));
            sum = sum + dist;
        }
        if (sum < minsum)
        {
            minsum = sum;
            g = i;
        }
    }

    make_opening(vector, m, SE, n, g);
    double procent = check(vector1, m1);
    //cout << procent << endl;
    excel << procent << endl;
}

int main()
{
    double r, diam, s_length, p_length, dist, s_height;

    for (int i = 0; i < 333; i++)
    {
        srand(time(0));
        r = rand() % 40 + 30;
        diam = rand() % 5 + 5;
        p_length = rand() % 100 + 100;
        dist = rand() / RAND_MAX + 0.5;
        make_circle_sign(diam, p_length, r, dist);
        do_stuff();
    }

    for (int i = 0; i < 333; i++) 
    {
        srand(time(0));
        s_length = rand() % 30 + 70;
        diam = rand() % 5 + 5;
        p_length = rand() % 100 + 100;
        dist = rand() / RAND_MAX + 0.5;
        make_triangle_sign(diam, p_length, s_length, dist);
        do_stuff();
    }

    for (int i = 0; i < 400; i++) 
    {
        srand(time(0));
        s_length = rand() % 30 + 40;
        s_height = rand()% 50 + 20;
        diam = rand() % 5 + 5;
        p_length = rand() % 100 + 100;
        dist = rand() / RAND_MAX + 0.5;
        make_rectangle_sign(diam, p_length, s_height, s_length, dist);
        do_stuff();
    }

    return 0;
}