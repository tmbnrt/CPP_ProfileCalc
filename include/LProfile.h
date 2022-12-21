#ifndef LPROFILE_H
#define LPROFILE_H

#include "Profile.h"

class LProfile : public Profile
{
    public:
        LProfile(const char* name,
                 double h, double w, double t);
        virtual ~LProfile();

        double  h;
        double  w;
        double  t;

        void check();       //                your JOB!!!
        void create();      //
        void listData();    //

    protected:
    private:
};

#endif // LPROFILE_H
