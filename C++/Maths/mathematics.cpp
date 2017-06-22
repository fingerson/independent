#include <iostream>
#include "operations.h"

namespace control_variables
{
int out_of_domain(0);
}

namespace operations
{
//########################################################################################################################################################
// Utility functions
//###############################################################################################################################

void    nl(int number_of_lines)
{
    for(int i=0; i<number_of_lines; i++)
    {
        cout << endl;
    }
}


//########################################################################################################################################################
// Auxiliar functions
//###############################################################################################################################

long double derivative(long double (*foo)(long double), long double point)
{
    long double f_x = foo(point);
    if(control_variables::out_of_domain == 0)
    {
        long double sup_deriv = (foo(point + DERIVPRECISION)-f_x)/DERIVPRECISION;
        long double inf_deriv(0);
        if(control_variables::out_of_domain == 0)
        {
            inf_deriv = (f_x - foo(point - DERIVPRECISION))/(DERIVPRECISION);

            if(control_variables::out_of_domain == 0)
            {
                return (inf_deriv + sup_deriv)/2;
            }
            else
            {
                control_variables::out_of_domain = 1;
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

long double integrate(long double (*foo)(long double), long double lowbound, long double highbound)
{
        long double sum = 0;
        int flag = 1;   // Indicates if the lower bound is bigger than the higher bound
        if(lowbound > highbound)
        {
            long double aux = highbound;
            highbound = lowbound;
            lowbound = aux;
            flag = -1;
        }
        for(long double i = lowbound; i <=  highbound; i += INTEGPRECISION)
        {
            long double j = (*foo)(i)*INTEGPRECISION;
            if(control_variables::out_of_domain == 0)
                sum += j;
            control_variables::out_of_domain = 0;
        }
        return flag*sum;
}

void plot(long double (*foo)(long double), long double lowbound, long double highbound, long double step)
{
        for(long double i = lowbound; i <=  highbound; i += step)
        {
            long double j = (*foo)(i);
            if(control_variables::out_of_domain == 0)
                cout << i << "                      " << j << endl;
            control_variables::out_of_domain = 0;
        }
}

long double spow(long double base, long long level)
{
    long double result(1);

    for(long long i = 0; i < module(level); i++)
    {
        result = result*base;
    }
    if(level < 0)
    {
        if(eql(result, 0))
        {
            control_variables::out_of_domain = 1;
        }
        result = 1/result;
    }

    return result;
}

long double tenth_root(long double base)
{
    if(base > 0)
    {
        long double used_number = base;
        long long   integer_division(0);

        if(base < 1)
        {
            used_number = 1/base;
        }

        // This first part makes the number that comes as a base smaller than 10
        for(; used_number >= 10; integer_division++)
        {
            used_number = used_number/10;
        }


        long double candidate(1.26);    /*
                                                    Since the tenth root of ten is ~1.2589 and used_number is smaller than ten,
                                                    1.26 is a valid starting value, as 1.26^10 will be bigger than ten.
                                                */
        for(long double decrement = 0.1; decrement > EPSILON; candidate -= decrement)
        {
            // If the candidate for root is smaller than used_number, than add decrement to it
            if(spow(candidate, 10) < used_number)
            {
                candidate += decrement;
                decrement = decrement/10;           // Update decrement's value;
            }


            // Break if the number is met before the precision requirement is sufficed
            if(eql(spow(candidate,10), used_number))
            {
                break;
            }

        }

        if(base < 1)
        {
            used_number = 1/base;
            return 1/(candidate * spow(TENROOTTEN, integer_division));
        }

        return candidate * spow(TENROOTTEN, integer_division);
    }
    else if(eql(base, 0))
    {
        return 0;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }

}


//########################################################################################################################################################
// Trigonometric functions
//###############################################################################################################################

long double angle_reduction(long double angle)
{
    long double   value = angle;
    if(value < 0)
    {
        while(value <= -TAU)
        {
            value += TAU;
        }
    }
    else if(value > 0)
    {
        while(value >= TAU)
        {
            value -= TAU;
        }
    }

    if(value < -TAU/2)
    {
        value += TAU;
    }
    else if(value > TAU/2)
    {
        value -= TAU;
    }

    if(eql(value, -TAU/2))
    {
        value = TAU/2;
    }

    return value;
}

long double arccos(long double number)
{
    if(number > -1 && number < 1)
    {
        long double number_rec = module(number);
        long double candidate(0);
        long double start_value = 0.1;

        // Turning the function more precise for values around 0;
        while(number_rec < start_value && start_value > EPSILON)
        {
            start_value = start_value/10;
        }

        // For when number = 0, we have to set a special condition
        if(module(number_rec) <= EPSILON)
        {
            candidate = TAU/4;
        }

        for(long double add = start_value; add > EPSILON && candidate <= TAU/4; candidate += add)
        {
            if(cos(candidate) < number_rec)
            {
                candidate -= add;
                add = add/10;
            }

            // Break if the number is found before the precision condition
            if(eql(cos(candidate), number_rec))
            {
                break;
            }

        }

        if(number < 0)
        {
            candidate = TAU/2 - candidate;
        }

        return candidate;
    }

    //  This allows the boundaries to exist
    else if(eql(number, 1))
    {
        return 0;
    }
    else if(eql(number, -1))
    {
        return TAU/2;
    }

    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }

}

long double arcsin(long double number)
{
    if(number > -1 && number < 1)
    {
        long double number_rec = module(number);
        long double candidate(0);

        for(long double add = 0.1; candidate <= TAU/4 && add > EPSILON; candidate += add)
        {
            if(sin(candidate) > number_rec)
            {
                candidate -= add;
                add = add/10;
            }

            // Break if the condition of equality is met before the condition of precision
            if(eql(sin(candidate), number_rec))
            {
                break;
            }
        }
        if(number < 0)
        {
            candidate = -candidate;
        }

        return candidate;
    }

    //  This allows the boundaries to exist
    else if(eql(number, 1))
    {
        return TAU/4;
    }
    else if(eql(number, -1))
    {
        return -TAU/2;
    }

    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }



}

long double arctg(long double number)
{
    long double red_number = module(number);
    long double candidate = 0;

    long double start_value = 0.1;

    // Turning the function more precise for values around 0;
    while(red_number < start_value && start_value > EPSILON)
    {
        start_value = start_value/10;
    }

    for(long double add = start_value; add > EPSILON && candidate <= TAU/4; candidate += add)
    {
        if(tg(candidate) > red_number)
        {
            candidate -= add;
            add = add/10;
        }
    }

    if(number < 0)
    {
        candidate = -candidate;
    }

    return candidate;
}

long double cos(long double angle)
{
    long double red_angle = angle_reduction(angle);
    long double resultant(0);
    int         signal = 1;

    for(long long i = 0; i < TRIGPRECISION; i+=2)
    {
        resultant += signal*pow(red_angle, i)/factorial(i);
        signal = -signal;
    }
    return resultant;
}

long double cossec(long double angle)
{
    long double red_angle = angle_reduction(angle);
    if(eql(red_angle, TAU/2) == 0 && eql(red_angle, -TAU/2) == 0 && eql(red_angle, 0) == 0)
    {
        return 1/sin(red_angle);
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }

}

long double cotg(long double angle)
{
    long double red_angle = angle_reduction(angle);

    if(eql(red_angle, TAU/2) || eql(red_angle, 0))
    {
        control_variables::out_of_domain = 1;
    }

    return cos(red_angle)/sin(red_angle);
}

long double sec(long double angle)
{
    long double red_angle = angle_reduction(angle);
    if(eql(red_angle, TAU/4) == 0 && eql(red_angle, -TAU/4) == 0)
    {
        return 1/cos(red_angle);
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }

}

long double sin(long double angle)
{
    long double red_angle = angle_reduction(angle);
    long double resultant(0);
    int         signal = 1;

    for(long long i = 1; i < TRIGPRECISION; i+=2)
    {
        resultant += signal*pow(red_angle, i)/factorial(i);
        signal = -signal;
    }
    return resultant;
}

long double sinc(long double angle)
{
    if(eql(angle, 0))
    {
        return 1;
    }
    else
    {
        return sin(angle)/angle;
    }
}

long double tg(long double angle)
{
    long double red_angle = angle_reduction(angle);

    if(eql(red_angle, TAU/4) || eql(red_angle, -TAU/4))
    {
        control_variables::out_of_domain = 1;
    }

    return sin(red_angle)/cos(red_angle);
}


//########################################################################################################################################################
// Hyperbolic operations
//###############################################################################################################################

long double arccosh(long double number)
{
    if(number > 1)
    {
        long double candidate = ln(number);     // Good first aproximation
        long double start_add = 1;

        // For tuneing the precision values
        while(start_add > candidate && start_add > EPSILON)
        {
            start_add = start_add/10;
        }

        for(long double add = start_add; add > EPSILON; candidate += add)
        {
            if(eql(cosh(candidate), number))
            {
                break;
            }

            if(cosh(candidate) > number)
            {
                candidate -= add;
                add = add/10;
            }
        }
        return candidate;
    }
    else if(eql(number, 1))
    {
        return 0;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }

}

long double arcsinh(long double number)
{
    if(eql(number, 0))
    {
        return 0;
    }

    long double red_number = module(number);
    long double candidate = 0;
    long double start_add = 1;

    if(red_number > 1)
    {
        candidate = ln(red_number);     // Good first aproximation
    }

    // For tuneing the precision values
    while(start_add > red_number && start_add > EPSILON)
    {
        start_add = start_add/10;
    }

    for(long double add = start_add; add > EPSILON; candidate += add)
    {
        if(eql(sinh(candidate), red_number))
        {
            break;
        }

        if(sinh(candidate) > red_number)
        {
            candidate -= add;
            add = add/10;
        }
    }

    if(number < 0)
    {
        candidate = -candidate;
    }

    return candidate;
}

long double arctgh(long double number)
{
    if(number < 1 && number > -1)
    {
        long double red_number = module(number);
        long double candidate = 0;

        long double start_value = 0.1;

        // Turning the function more precise for values around 1 and -1;
        while((1-red_number) < start_value && start_value > EPSILON)
        {
            start_value = start_value/10;
        }

        for(long double add = start_value; add > EPSILON && candidate <= TAU/4; candidate += add)
        {
            if(tgh(candidate) > red_number || candidate + add > TAU/4)
            {
                candidate -= add;
                add = add/10;
            }
        }

        if(number < 0)
        {
            candidate = -candidate;
        }

        return candidate;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
}

long double cosh(long double number)
{
    return (exp(number) + exp(-number))/2;
}

long double cosech(long double number)
{
    if(eql(number, 0))
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
    else
    {
        return 1/sinh(number);
    }
}

long double cotgh(long double number)
{
    if(eql(number, 0))
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
    else
    {
        return cosh(number)/sinh(number);
    }
}

long double sech(long double number)
{
    return 1/cosh(number);
}

long double sinh(long double number)
{
    return (exp(number) - exp(-number))/2;
}

long double tgh(long double number)
{
    return sinh(number)/cosh(number);
}

//########################################################################################################################################################
// Numeric operations
//###############################################################################################################################

long double eql(long double number1, long double number2)
{
    if(module(number1 - number2) <= EPSILON)
    {
        return 1;
    }
    return 0;
}

long long   is_prime(long long prime_candidate)
{
    long long i = 1;
    while(1 == 1)
    {
        long long j = prime(i);
        if(j < prime_candidate)
        {
            i++;
        }
        else if(j == prime_candidate)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

long long   factorial(long long number)
{
    long long result(1);
    if(number < 0)
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
    else
    {
        for(int i=2; i<=number; i++)
        {
            result = result*i;
        }
        return result;
    }
}

long long   gcd(long long number1, long long number2)
{
    if(number1 == number2 && number2 != 0)
    {
        return number1;
    }
    if(number1 > 0 && number2 > 0)
    {
        long long answer(1);
        long long prime_div = 2;

        for(long long i = 2; number1 > prime_div && number2 > prime_div; i++)
        {
            if(number1%prime_div == 0 && number2%prime_div == 0)
            {
                answer = answer*prime_div;
                number1 = number1/prime_div;
                number2 = number2/prime_div;
                i--;
            }
            else
            {
                prime_div = prime(i);
            }
        }
        return answer;
    }
    else if(number1 == 0 && number2 != 0)
    {
        return number2;
    }
    else if(number2 == 0 && number1 != 0)
    {
        return number1;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
}

long long   lcm(long long number1, long long number2)
{
    long long answer = number1/gcd(number1, number2);
    return answer*number2;
}

long double module(long double number)
{
    if(number < 0)
    {
        return -1.0*number;
    }
    else
        return number;
}
long long   module(long long number)
{
    if(number < 0)
    {
        return -1*number;
    }
    else
    {
        return number;
    }
}

long long   prime(long long position)
{
    if(position > 1)
    {
        long long prime_candidate = 3;
        for(long long i = 1; i < position; prime_candidate += 2)
        {
            long long divisor_candidate = 3;
            long long root_candidate = 9;
            for(; root_candidate <= prime_candidate; divisor_candidate += 2)
            {
                root_candidate = divisor_candidate*divisor_candidate;
                if(prime_candidate%divisor_candidate == 0)
                {
                    i--;
                    break;
                }
            }
            i++;
        }
        return prime_candidate-2;
    }
    else if(position == 1)
    {
        return 2;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
}


//###############################################################################################################################
// Exponentiation and Logarithm related functions
//###############################################################################################################################

long double exp(long double level)
{
    return pow(EULER, level);
}

long double ln(long double number)
{
    if(number > 0)
    {
        // The operation of this function will involve decomposing the number in the form a*2^b, where b is an integer and 1 <= a < 2;
        long long   division_by_two(0);
        long double red_number = number;

        while(red_number >= 2)
        {
            red_number = red_number/2;
            division_by_two++;
        }

        while(red_number < 1)
        {
            red_number = 2*red_number;
            division_by_two--;
        }

        // This part will use the identity ln x = sum{1 to inf}{(-1)^(k-1) * (x-1)^k / k!}

        long double resultant(0);
        for(int i = 1; i < LNPRECISION; i++)
        {
            resultant += pow(-1, i-1)*pow(red_number-1, i) / factorial(i);
        }

        // For increased precision, we use the aproximation function
        for(long double add = 0.01; add > EPSILON; resultant += add)
        {
            if(eql(red_number, exp(resultant)))
            {
                break;
            }
            if(red_number < exp(resultant))
            {
                resultant -= add;
                add = add/10;
            }
        }

        return resultant + division_by_two*LN2;
    }
    else
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
}

long double log(long double number, long double base)
{
    if(number <= 0 || base <= 0)
    {
        control_variables::out_of_domain = 1;
        return 0;
    }
    else
    {
        return ln(number)/ln(base);
    }
}

long double pow(long double base, long double level)
{
    long double resultant(1);
    long double current_level(level);
    for(long double i = 0; i < EXPPRECISION; i++)
    {
        long double partial;
        partial = spow(base, (long long)current_level);
        for(long double j = 0; j < i; j++)
        {
            partial = tenth_root(partial);
        }
        resultant = resultant*partial;
        current_level = 10*(current_level - (long long)current_level);
    }
    return resultant;
}

}

