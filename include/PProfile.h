#ifndef PPROFILE_H
#define PPROFILE_H

#include "Profile.h"

class PProfile : public Profile
{
    public:
        PProfile(const char* name,
                 double sq, double t, double h, double w, double tf, double tw);
        virtual ~PProfile();

        double  sq;         // outer dimension of the square profile
        double  t;          // thickness of the square profile's walls
        double  h;          // height of the U-profile
        double  w;          // width of the U-profile
        double  tf;         // flange thickness of the U-profile
        double  tw;         // weld thickness of the U-profile

        // error counter
        int Err;

        void check();       //  check the profile input data
        void create();      //  create the profile part
        void listData();    //  list data to output device

    protected:
    private:
};

#endif // PPROFILE_H
