#include "Profile.h"
#include "Element.h"
#include <memory.h>
#include <math.h>       // fabs, pow
#include <string.h>     // strcpy
#include <stdio.h>      // sprintf
#include <cmath>


Profile::Profile(const char* name) : Base()
{
    strcpy(this->name,name);
}

Profile::~Profile()
{
    resetElementContainer();
    resetNodeContainer();
}

// create an element container
int Profile::addElementContainer(int length)
{
    // clear memory
    resetElementContainer();

    if (length < 1) return 0;   // condition for the element length (>0)  --> 0: false

    // create the container
    pEC = new Element*[length];
    nEC = length;

    // initialize the addresses
    memset((void*)pEC,0,sizeof(Element*)*nEC);

    // create node container
    resetNodeContainer();

    // create the node container
    pNC = new Node*[length*2];
    nNC = length*2;

    // initialize the addresses
    memset((void*)pNC,0,sizeof(Node*)*nNC);

    return length;
}

/*
    int         nEC;        // element container's length
    Element**   pEC;        //
*/

void Profile::resetElementContainer()
{
    // delete the content
    for (int i=0;i<nEC;i++)
    {
        if (pEC[i]) delete pEC[i];  // delete element if it exists
    }
    delete [] pEC;                  // delete container
    nEC = 0;
}

// clear the node container
void Profile::resetNodeContainer()
{
    // delete the content
    for (int i=0;i<nNC;i++)
    {
        if (pNC[i]) delete pNC[i];  // delete node if it exists
    }
    delete [] pNC;
    nNC = 0;
}

// add an element instance to the container
void Profile::addElement(Element* pE)
{
    if (!pE)    throw("*** Error: Invalid Element address! ***");
    if (!pEC)   throw("*** Error: No Element container found! ***");

    // check the Element instance
    checkElement(pE);

    // add the Element instance
    pEC[pE->no -1] = pE;
    pE->setData();

    // store Node instances
    for (int i=0;i<pE->nN;i++)
    {
        addNode(pE->pN[i]);
    }
}

// check Element data
void Profile::checkElement(Element* pE)
{
    for (int i=0;i<pE->nN;i++)
    {
        if (!pE->pN[i]) throw ("*** Error: Node instance not available! ***");
    }
    if (pE->no < 1 || pE->no > nEC)   throw ("*** Error: Element number invalid! ***");
}

// add a Node instance
void Profile::addNode(Node* pN)
{
    if (!pN)    throw ("*** Error: Invalid Node address! ***");

    if (pN->no < 1 || pN->no > nNC)
        throw("*** Error: Node number invalid! ***");

    if (pNC[pN->no -1] && pNC[pN->no -1] != pN)
        throw ("*** Error: Node number / address invalid! ***");

    pNC[pN->no -1] = pN;
}

// calculate profile result data
// - summing element results
void Profile::calculateResults()
{
    // initialize result data
    dA = 0.;
    memset((void*)dS, 0,sizeof(double)*2);
    memset((void*)dIu,0,sizeof(double)*3);

    // sum up over all elements
    for (int i=0;i<nEC;i++)
    {
        // element available?
        if (!pEC[i]) continue;
        Element* pE = pEC[i];
        dA += pE->dA;
        for (int j=0; j<2; j++)  dS[j] += pE->dS[j];
        for (int j=0; j<3; j++) dIu[j] += pE->dI[j];
    }
    if (fabs(dA) < 0.01) throw ("*** Error: No elements found! ***");

    // center of mass
    de[0] = dS[1]/dA;
    de[1] = dS[0]/dA;

    // moment of inertia in "center of mass" coordinates
    dIc[0] = dIu[0] - de[1]*de[1]*dA;
    dIc[1] = dIu[1] - de[0]*de[0]*dA;
    dIc[2] = dIu[2] - de[0]*de[1]*dA;

    // calculate principle values
    double dIDif = dIc[0] - dIc[1];
    double dISum = dIc[0] + dIc[1];
    double dISqr = sqrt(dIDif*dIDif + 4.*dIc[2]*dIc[2]);

    dIp[0] = 0.5*(dISum + dISqr);
    dIp[1] = 0.5*(dISum - dISqr);

    // rotation angle
    alpha = 0.5*atan2(2.*dIc[2],dIDif);
}

// list data to output device
void Profile::listData()
{
    sprintf(msg,"Profile '%s'",name);
    appendLog(msg);

    // print element list
    for (int i=0;i<nEC;i++)
    {
        if (pEC[i]) pEC[i]->listData();
    }

    appendLog((char*)"Resulting profile data:\n");
    sprintf(msg,"  Area ....................: %12.2f cm^2\n", dA/1.e2);
    appendLog(msg);
    sprintf(msg,"  Static moments ..........: %12.2f %12.2f cm^3\n",
            dS[0]/1.e3,dS[1]/1.e3);
    appendLog(msg);
    sprintf(msg,"  MoI in user coord. ......: %12.2f %12.2f %12.2f cm^4\n",
            dIu[0]/1.e4,dIu[1]/1.e4,dIu[2]/1.e4);
    sprintf(msg,"  Excentricity ............: %12.2f %12.2f cm\n",
            de[0]/1.e1,de[1]/1.e1);
    appendLog(msg);
    sprintf(msg,"  MoI in center coord. ....: %12.2f %12.2f %12.2f cm^4\n",
            dIc[0]/1.e4,dIc[1]/1.e4,dIc[2]/1.e4);
    appendLog(msg);
    sprintf(msg,"  MoI principle values ....: %12.2f %12.2f %12.2f cm^4\n",
            dIp[0]/1.e4,dIp[1]/1.e4,dIp[2]/1.e4);
    appendLog(msg);
    sprintf(msg,"  Rotation angle ..........: %12.2f deg\n",
            alpha*180/(atan(1)*4));
    appendLog(msg);
}
