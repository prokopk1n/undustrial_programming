#include <iostream>
#include <cassert>
#include <cmath>
#include <windows.h>
#include <iomanip>

/**
 \brief Use for debug mode
*/
#define MODE TESTING


/**
 \brief Use for painting background in red color in debug mode
*/
#define _FAIL_ \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);


/**
 \brief Use for painting background in green color in debug mode
*/
#define _PASSED_ \
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);


/**
 \brief Use for testing program.
 \details If any test is failed background is red. Otherwise background is green.
 \param[in] calc_value Calculated value
 \param[in] real_val Real value
*/
#define $unittest(calc_value, real_value)\
    if (calc_value!=real_value)\
    {\
        _FAIL_ std::cout<<"[TEST FAILED] ";\
    }\
    else\
    {\
        _PASSED_ std::cout<<"[TEST PASSED] ";\
    }\
    std::cout<<std::setw(5)<<calc_value<<" "<<std::setw(5)<<real_value<<" ";\
    std::cout<<__FILE__<<" ("<<__LINE__<<")"<<std::endl;\
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


/**
 \brief It solves linear equations : ax+b=0.
 \param[out] x Solution, if it exists.
 \return Amount of solutions. (1/0/Inf)
*/
double linear_equation (double a, double b, double & x);


/**
 \brief It solves quadratic equations : ax^2+bx+c=0.
 \param[out] x1 Greatest solution, if it exists.
 \param[out] x2 Other solution, if it exists.
 \return Amount of solutions. (2/0/Inf)
*/
double quadratic_equation (double a, double b, double c, double & x1, double & x2);

int main()
{
    double a, b, c;
    double x1, x2;
    double res;

    #ifdef MODE

        $unittest (quadratic_equation(2,5,-3,x1,x2),2);              /* 2x^2+5x-3=0 */
        $unittest (x1,0.5);
        $unittest (x2,-3);
        $unittest (quadratic_equation(1,2,17,x1,x2),0);              /* x^2+2x+17=0 */
        $unittest (quadratic_equation(0,3,-6,x1,x2),1);              /*    3x-6=0   */
        $unittest (quadratic_equation(0,0,0,x1,x2),INFINITY);        /*     0=0     */
        $unittest (quadratic_equation(0,0,1,x1,x2),0);               /*     1=0     */

    #else

        std::cout<<"Input a,b and c: ";
        std::cin>>a>>b>>c;
        std::cout<<std::fixed;
        if ((res=quadratic_equation(a, b, c, x1, x2))==2)
            std::cout<<"x1="<<std::setprecision(5)<<x1<<" x2="<<std::setprecision(5)<<x2<<std::endl;
        else if (res==1)
            std::cout<<"x1="<<std::setprecision(5)<<x1<<std::endl;
        else if (res==0)
            std::cout<<"No roots"<<std::endl;
        else
            std::cout<<"Any number"<<std::endl;

    #endif

    return 0;
}



double linear_equation (double a, double b, double & x)
{
    if (a==0)
    {
        if (b==0)
            return INFINITY;
        else
            return 0;
    }
    else
    {
        x=-b/a;
        return 1;
    }
}



double quadratic_equation (double a, double b, double c, double & x1, double & x2)
{
    double discriminant;

    assert (std::isfinite(a));
    assert (std::isfinite(b));
    assert (std::isfinite(c));

    assert(&x1!=&x2);

    if (a==0)
        return linear_equation (b, c, x1);
    else
    {
        discriminant=b*b-4*a*c;

        if (discriminant>=0)
        {
            x1=(-b+sqrt(discriminant))/(2*a);
            x2=(-b-sqrt(discriminant))/(2*a);
            return 2;
        }

        else
            return 0;
    }
}
