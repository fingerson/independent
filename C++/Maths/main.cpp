#include <iostream>
#include "operations.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace operations;


long double func(long double t)
{
    return 2.307523*sin(0.06*TAU*t - 1.311509318) + 9.687;
    /*1.311509318
    //4.615046261
    long double x_red = angle_reduction(0.06*TAU*t);
    long double theta = 1.311509318;
    long double amplitude = 4.615046261;
    if((x_red >= theta) || (x_red <= -(TAU/2 - theta)))
    {
        return amplitude*sin(0.06*TAU*t - theta);
    }
    else
        return -amplitude*sin(0.06*TAU*t - theta); */
}

int main()
{
    long double upbound = 34;
    long double lowbound = 0;
    long double step = 0.01;

    int function_mode = 4;
    /*
        0 - Plot of one argument Integer Domain Functions
        1 - Plots func
        2 - Evaluation of functions with two ints
        3 - Evaluation of functions with two reals
        4 - Cheat mode
    */

    // 0 - Plot of one argument Integer Domain Functions
    if(function_mode == 0)
    {
        for(long long i = -10; i <=  20; i += 1)
        {
            long long j = factorial(i);
            if(control_variables::out_of_domain == 0)
                cout << i << "                      " << j << endl;
            control_variables::out_of_domain = 0;
        }
    }


    // 1 - Plots func
    else if(function_mode == 1)
    {
        plot(func, lowbound, upbound, step);

    }

    // 2 - Evaluation of functions with two ints
    else if(function_mode == 2)
    {
        long long i = 252;
        long long j = 144;
        cout << "lcm(" << i << "," << j << ") = " << lcm(i,j) << endl;
    }

    // 3 - Evaluation of functions with two reals
    else if(function_mode == 3)
    {
        long double k = 6;
        long double l = 3;
        long double result = derivative(func, k);
        cout << "Result = " << result << " Control:" << control_variables::out_of_domain << endl;
        cout << l << "^" << result << " = " << pow(l,result) << endl;
    }
    else if(function_mode == 4)
    {

        for(long double i = 10 ; i < 36; i += 4)
        {

            long double error1 = ln(i);
            long double error2 = ln(i);
            long long   aux = error2;
            error1 = 1000*(error1 - aux);
            aux = error1;
            aux = aux%10 + 1;
            cout << "#Error = " << 1 + 1.0*aux/100 << endl;

            long double f = 0.25639*i;
            f = f*(1 + 1.0*aux/100);

            cout << i << "                      " << f << endl;
        }

    }

    return 0;
}
