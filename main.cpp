/* *************Function overriding and virtual functions.***************
 *
 * Constructors/Destructors are special. Table those for now.
 * This applies to all other functions that are members of a class.
 *
 * Below I have a base class and a derived class.
 *
 * I define print() only in the base class. Of course both the
 * base and derived class have the same definition of print().
 *
 * I define print2() in the base class and I override it with a
 * different definition in the derived class.
 *
 * I define print3() in the base class as VIRTUAL and I override
 * with a different definition in the derived class.
 *
 * I instantiate the base class as b and the derived class as d.
 * b.print2() and d.print2() do different things.
 * b.print3() and d.print3() do different things.
 *
 * This is not a surprise. The compiler can figure this all out.
 *
 * But if I make a POINTER to the base class, and assign it to
 * the address of b and do p->print2, then assign the pointer to
 * the address of d and do p->print2, I get the b.print2()
 * behavior! Only p->print3 uses the d.print3() behavior!
 *
 * That's what VIRTUAL does for me.
 *
 * And note that making a pointer to the derived class and
 * assigning it to the address of b is a compiler error.
 *
 * *******************************/
/* ************* $ ./main.exe ***************
 * 
 * The derived class can override a function whether it's virtual or not.
 * 
 * main():           bBb.print()
 * -- print():       my_base::print() (only defined for base class)
 * main():           bBb.print2()
 * -- print2():      my_base::print2()
 * main():           bBb.print3()
 * -- print3():      my_base::print3()
 * main():           dDd.print()
 * -- print():       my_base::print() (only defined for base class)
 * main():           dDd.print2()
 * -- print2():      my_deriv::print2() <----- LOOK HERE
 * main():           dDd.print3()
 * -- print3():      my_deriv::print3() <----- LOOK HERE
 * 
 * But if I make a pointer of type pointer to base class
 * 
 * main():           my_base *p;
 * 
 * And I access members of the base and derived:
 * 
 * main():           p = &bBb;
 * main():           p->print()
 * -- print():       my_base::print() (only defined for base class)
 * main():           p->print2()
 * -- print2():      my_base::print2()
 * main():           p->print3()
 * -- print3():      my_base::print3()
 * 
 * When I go to POINT at the derived type, only the virtual is overriden:
 * 
 * main():           p = &dDd;
 * main():           p->print()
 * -- print():       my_base::print() (only defined for base class)
 * main():           p->print2()
 * -- print2():      my_base::print2() <----- LOOK HERE
 * main():           p->print3()
 * -- print3():      my_deriv::print3() <----- LOOK HERE
 * *******************************/
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include "pretty.h"

class my_base
{
public:
    void print(void)  const { LOG(CALL,"my_base::print() (only defined for base class)"); }
    void print2(void) const { LOG(CALL, "my_base::print2()"); }
    virtual void print3(void) const { LOG(CALL, "my_base::print3()"); }
};
class my_deriv : public my_base
{
public:
    void print2(void) const { LOG(CALL, "my_deriv::print2()"); }
    virtual void print3(void) const { LOG(CALL, "my_deriv::print3()"); }
};

int main()
{
    printf("\nThe derived class can override a function whether it's virtual or not.\n\n");

    my_base bBb; my_deriv dDd;

    LOG(MAIN, "bBb.print()\n"); bBb.print(); NL;                // my_base::print()
    LOG(MAIN, "bBb.print2()\n"); bBb.print2(); NL;              // my_base::print2()
    LOG(MAIN, "bBb.print3()\n"); bBb.print3(); NL;              // my_base::print3()

    LOG(MAIN, "dDd.print()\n"); dDd.print(); NL;                // my_base::print()
    LOG(MAIN, "dDd.print2()\n"); dDd.print2(); LOOK_HERE(); NL; // my_deriv::print2()
    LOG(MAIN, "dDd.print3()\n"); dDd.print3(); LOOK_HERE(); NL; // my_deriv::print3()

    printf("\nBut if I make a pointer of type pointer to base class\n\n");

    my_base *p; LOG(MAIN, "my_base *p;\n");

    printf("\nAnd I access members of the base and derived:\n\n");

    p = &bBb; LOG(MAIN, "p = &bBb;\n");
    LOG(MAIN, "p->print()\n");  p->print(); NL;                 // my_base::print()
    LOG(MAIN, "p->print2()\n"); p->print2(); NL;                // my_base::print2()
    LOG(MAIN, "p->print3()\n"); p->print3(); NL;                // my_base::print3()
                                                                //
    printf("\nWhen I go to POINT at the derived type, only the virtual is overriden:\n\n");

    p = &dDd; LOG(MAIN, "p = &dDd;\n");
    LOG(MAIN, "p->print()\n");  p->print(); printf("\n");       // my_base::print()
    LOG(MAIN, "p->print2()\n"); p->print2(); LOOK_HERE(); NL;   // my_base::print2()
    LOG(MAIN, "p->print3()\n"); p->print3(); LOOK_HERE(); NL;   // my_deriv::print3()
}
