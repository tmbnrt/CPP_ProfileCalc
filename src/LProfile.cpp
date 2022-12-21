#include "LProfile.h"


LProfile::LProfile(const char* name,
                   double h, double w, double t):
                   Profile(name)
{
    this->h = h;
    this->w = w;
    this->t = t;

    // check          YOUR JOB!!!
    // check()  ->  exception?

    // create the system
    create();

}

LProfile::~LProfile()
{
    //dtor
}

// create the system
void LProfile::create()
{
    addElementContainer(2);

    Node*       pN[3];
    Element*    pE[2];

    // Nodes
    pN[0] = new Node(1,   w , t/2.);
    pN[1] = new Node(2, t/2., t/2.);
    pN[2] = new Node(3, t/2.,   h );

    // Elements
    pE[0] = new Element(1, pN[0], pN[1], t);
    pE[1] = new Element(2, pN[1], pN[2], t);

    for (int i=0;i<2;i++) addElement(pE[i]);

    calculateResults();
}

// print the results
void LProfile::listData()
{
    Profile::listData();
}
