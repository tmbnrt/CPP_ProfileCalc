/*
Main program of checkTWA including the the three
different profile cases and their specific input parameters
*/
#include "Base.h"
#include "Node.h"
#include "Element.h"
#include "Profile.h"
#include <stdio.h>
#include "LProfile.h"
#include "PProfile.h"

#define _CASE_1         // checking the PProfile class (PROJECT case 1)
//#define _CASE_2         // checking the PProfile class (PROJECT case 2)
//#define _CASE_3         // checking the PProfile class (PROJECT case 3)

int main()
{
    // reset the LOG
    Base::resetLog();

#ifdef _CASE_1
    try
    {                       //     |name    |sq  |t |h   |w  |tf  |tw
    PProfile* pP = new PProfile("myProfile1",100.,4.0,200.,75.,11.5,8.5);
    pP->listData();
    }

    catch(const char* e)
    {
        printf("*** Exception: %s",e);
    }
#endif // _CASE_1

#ifdef _CASE_2
    try
    {                       //     |name     |sq  |t  |h   |w  |tf  |tw
    PProfile* pP = new PProfile("myProfile2",120.,4.5,200.,75.,11.5,8.5);
    pP->listData();
    }

    catch(const char* e)
    {
        printf("*** Exception: %s",e);
    }
#endif // _CASE_2

#ifdef _CASE_3
    try
    {                       //     |name     |sq  |t  |h   |w  |tf  |tw
    PProfile* pP = new PProfile("myProfile3",140.,5.6,200.,75.,11.5,8.5);
    pP->listData();
    }

    catch(const char* e)
    {
        printf("*** Exception: %s",e);
    }
#endif // _CASE_3

    return 0;
}
