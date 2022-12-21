#include "Base.h"
#include "Element.h"
#include <stdio.h>
#include <memory.h>         // for memset
#include <math.h>

//class Node;     // sufficient only for addresses
#include "Node.h"

// constructor for a line element
Element::Element(int no, Node* n1, Node* n2, double t)
        : Base()
{
    this->no    = no;
    this->t     = t;

    type = ELE_LINE;
    nN   = 2;           // number of nodes per element
    pN   = new Node*[nN];

    pN[0] = n1;
    pN[1] = n2;

    // initializations
    dL = 0.;
    dA = 0.;
    //      |starting address of memory
    //               |byte to use for initialization
    //                  |number of bytes to copy
    memset((void*)dS,0,sizeof(double)*2);
    memset((void*)dI,0,sizeof(double)*3);

    // calculate
    setData();
}

Element::~Element()
{
    delete [] pN;
}

// print element's data into the log
void Element::listData()
{
    //                   || or operator
    if (type == ELE_LINE || type == ELE_ARC)
    {
    sprintf(msg,"> element: no = %2d, t = %8.2f\n",no,t);
    appendLog(msg);
    }

    else if (type == ELE_TRIANGLE)
    {
    sprintf(msg,"> element: no = %2d\n",no);
    appendLog(msg);
    }

    // result values
    sprintf(msg,"   L........: %12.3f mm\n",dL);
    appendLog(msg);
    sprintf(msg,"   A........: %12.3f mm^2\n",dA);
    appendLog(msg);
    sprintf(msg,"   S........: %12.3f %12.3f mm^3\n",dS[0],dS[1]);
    appendLog(msg);
    sprintf(msg,"   I........: %12.3f %12.3f %12.3f mm^4\n",dI[0],dI[1],dI[2]);
    appendLog(msg);

    // print node's data
    for (int i=0;i<nN;i++)  pN[i]->listData();
}

// calculate element's section data
// only valid for line elements!!!
void Element::setData()
{
    double dLp[2];      // projected lengths
    double dxc[2];      // center of mass coordinates of the element

    // over all directions
    for (int i=0;i<2;i++)
    {
        dxc[i] = (pN[0]->x[i] + pN[1]->x[i])/2.;
        dLp[i] = pN[1]->x[i] - pN[0]->x[i];
    }

    // element length
    dL = sqrt(dLp[0]*dLp[0] + dLp[1]*dLp[1]);       // Pythagoras
    //        |power function            |exponent
    //dL = sqrt(pow(dLp[0],2) + pow(dLp[1],2));

    // area
    dA = dL*t;

    // static moment
    for (int i=0;i<2;i++)
    {   //               ||cycling loop (similar to Python)
        dS[i] = dxc[(i+1)%2]*dA;
    }

    // moment of inertia
    for (int i=0;i<2;i++)
    {   //               ||cycling loop (similar to Python)
        int j = (i+1)%2;
        dI[i] = (pow(dLp[i+1],2)/12. + pow(dxc[j],2))*dA;
    }
    dI[2] = (dLp[0]*dLp[1]/12. + dxc[0]*dxc[1])*dA;
}

