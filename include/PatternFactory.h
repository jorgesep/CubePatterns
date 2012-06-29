/*
 * PatternsDefault.h
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include "Cube.h"


#ifndef PATTERN_FACTORY_H_
#define PATTERN_FACTORY_H_

using namespace std;

namespace patterns {

typedef unsigned int Uint;
typedef vector< vector<Uint> > VTable;
typedef vector< vector<Uint> >::iterator VTableIter;

static const Uint TETRA_POINTS  =4;
static const Uint PYRAMID_POINTS=5;
static const Uint PRISM_POINTS  =6;
static const Uint HEXA_POINTS   =8;
static const Uint CORNER_POINTS =8;
static const Uint EDGE_POINTS   =12;
static const Uint FACE_POINTS   =6;
static const Uint TOTAL_POINTS  =27;
static const Uint PERMUTATIONS  =30;
static const Uint MAX_ELEMENTS  =20;
static const Uint NUM_PATTERNS  =26;


class PatternFactory {
public:
    struct Element {
        Uint size;
        Uint points[CORNER_POINTS];
    };

    PatternFactory():index(0) { };
    PatternFactory(Uint i):index(i) { };
    virtual ~PatternFactory() {};
    virtual void createPattern(vector< vector<Uint> > & p);
private:

    static const Element elements[][MAX_ELEMENTS];

    Uint index;

    static const bitset<27> Mask[2];

};

}

#endif /* PATTERN_FACTORY_H_ */
