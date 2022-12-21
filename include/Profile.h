#ifndef PROFILE_H
#define PROFILE_H

#include <string.h>
#include "Element.h"
#include "Node.h"
#include "Base.h"

class Profile : public Base
{
    public:
        Profile(const char* name);
        virtual ~Profile();

        // attributes
        char    name[156];

        // element container
        int         nEC;        // element container length
        Element**   pEC;        // store element instance addresses

        // node container (not really needed)
        int     nNC;            // node container's length
        Node**  pNC;            // store node instance addresses

        // result data attributes
        double      dA;         // area
        double      dS[2];      // static moment
        double      dIu[3];     // moment of inertia in user coordinates
        double      de[2];      // center of mass coordinates
        double      dIc[3];     // moment of inertia in center of mass coordinates
        double      dIp[2];     // principle values
        double      alpha;      // rotation angle

        // methods
        int addElementContainer(int length);
        void addElement(Element* e);
        void checkElement(Element* e);
        void resetElementContainer();

        void calculateResults();
        void listData();

    private:
        void addNode(Node* n);
        void resetNodeContainer();

    protected:

};

#endif // PROFILE_H
