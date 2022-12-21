#include "PProfile.h"
#include "Node.h"
#include "Element.h"
#include <string.h>
#include <stdio.h>
#include <math.h>



PProfile::PProfile(const char* name,
                   double sq, double t, double h, double w, double tf, double tw):
                   Profile(name)
{
    // assign dimension variables
    this->sq = sq;          // outer dimension of the square profile
    this->t  = t;           // thickness of the square profile's walls
    this->h  = h;           // height of the U-profile
    this->w  = w;           // width of the U-profile
    this->tf = tf;          // flange thickness of the U-profile
    this->tw = tw;          // weld thickness of the U-profile

    // check the input parameters
    check();

    // create the system
    create();
}

// Destructor
PProfile::~PProfile()
{
    //dtor
}

// Check the input parameters
void PProfile::check()
{
    // assign error counter
    int Err = 0;
    // Minimum thickness
    double  minTh = 1.0;

    if (sq   <  3.*t )   Err++;
    if (t    <  minTh)   Err++;
    if (h    <  3.*tf)   Err++;
    if (w    <  2.*tw)   Err++;
    if (tw   <  minTh)   Err++;
    if (tf   <  minTh)   Err++;

    if (Err > 0) throw ( "*** ERROR: Invalid input data, check dimensions!");
}

// create the system
void PProfile::create()
{
    addElementContainer(12);

    Node*       pN[14];
    Element*    pE[12];

    // Helpers
    // helpers for the U-Profile
    double uv = w - tw/2.;      // exact points for the U-Profile's weld/flange nodes (vertical)
    double uh = (h - tf)/2.;    // exact points for the U-Profile's flange/weld (horizontal)

    // helpers for the rod
    double rv = sq - t/2.;        // vertical coordinate for the rod
    double rh = h/2. - tf;        // horizontal coordinate for the rod

    // helpers for the square profile
    double shi = rh + t/2.;       // horizontal inner coordinate for the square
    double sho = rh + sq - t/2.;  // horizontal outer coordinate for the square
    double svb = t/2.;            // vertical coordinate (bottom) for the square
    double svt = sq - t/2.;       // vertical coordinate (top) for the square

    // Nodes
    pN[0]  = new Node( 1, - uh, - uv);
    pN[1]  = new Node( 2,   uh, - uv);
    pN[2]  = new Node( 3, - uh,   0.);
    pN[3]  = new Node( 4,   uh,   0.);
    pN[4]  = new Node( 5, -shi,  svb);
    pN[5]  = new Node( 6,  shi,  svb);
    pN[6]  = new Node( 7, -sho,  svb);
    pN[7]  = new Node( 8,  sho,  svb);
    pN[8]  = new Node( 9, -sho,  svt);
    pN[9]  = new Node(10,  sho,  svt);
    pN[10] = new Node(11, -shi,  svt);
    pN[11] = new Node(12,  shi,  svt);
    pN[12] = new Node(13, - rh,   rv);
    pN[13] = new Node(14,   rh,   rv);

    // Elements
    // U-Profile
    pE[0]  = new Element( 1, pN[0] , pN[ 1], tw);
    pE[1]  = new Element( 2, pN[0] , pN[ 2], tf);
    pE[2]  = new Element( 3, pN[1] , pN[ 3], tf);
    // Square-Profiles
    pE[3]  = new Element( 4, pN[4] , pN[ 6],  t);
    pE[4]  = new Element( 5, pN[5] , pN[ 7],  t);
    pE[5]  = new Element( 6, pN[4] , pN[10],  t);
    pE[6]  = new Element( 7, pN[5] , pN[11],  t);
    pE[7]  = new Element( 8, pN[6] , pN[ 8],  t);
    pE[8]  = new Element( 9, pN[7] , pN[ 9],  t);
    pE[9]  = new Element(10, pN[8] , pN[10],  t);
    pE[10] = new Element(11, pN[11], pN[ 9],  t);
    // Flat Steel
    pE[11] = new Element(12, pN[12], pN[13],  t);

    for (int i=0;i<12;i++) addElement(pE[i]);

    calculateResults();
}

// print the results
void PProfile::listData()
{
    Profile::listData();
}

