/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "CubePatterns.h"

using namespace std;

namespace patterns {

const unsigned int CubePatterns::TETRA_POINTS=4;
const unsigned int CubePatterns::PYRAMID_POINTS=5;
const unsigned int CubePatterns::PRISM_POINTS=6;
const unsigned int CubePatterns::CORNER_POINTS=8;
const unsigned int CubePatterns::EDGE_POINTS=12;
const unsigned int CubePatterns::FACE_POINTS=6;
const unsigned int CubePatterns::TOTAL_POINTS=27;
const unsigned int CubePatterns::PERMUTATIONS=30;

const int CubePatterns::InternalPoints[TOTAL_POINTS] = {
    0,  18, 20, 2, 6, 24, 26, 8,
    9,  19, 11, 1, 3, 21, 23, 5,
    15, 25, 17, 7,10, 12, 22,14,
    4,  16, 13
};

const int CubePatterns::ExternalPoints[TOTAL_POINTS] = {
    0, 11, 3,  12, 24, 15,  4, 19, 7,
    8, 20, 10, 21, 26, 23, 16, 25,18,
    1,  9, 2,  13, 22, 14,  5, 17, 6
};



const CubePatterns::Permutations_t CubePatterns::RotationMatrix[PERMUTATIONS] = {

    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 360 --> 0

    CubePatterns::Permutations_t(CubePatterns::Y,1), /// Y --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 360 --> 0

    CubePatterns::Permutations_t(CubePatterns::Y,1), /// Y --> 180  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 360 --> 0

    CubePatterns::Permutations_t(CubePatterns::Y,1), /// Y --> 270  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 360 --> 0

    CubePatterns::Permutations_t(CubePatterns::Y,1), /// Y --> 360 --> 0  
    CubePatterns::Permutations_t(CubePatterns::X,1), /// X --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 360

    CubePatterns::Permutations_t(CubePatterns::X,2), /// X --> 270 X-->180 is the same Y-->180  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 90  
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 180 
    CubePatterns::Permutations_t(CubePatterns::Z,1), /// Z --> 270
    CubePatterns::Permutations_t(CubePatterns::Z,1)  /// Z --> 360
};



CubePatterns::CubePatterns() :m_cube() { 
    
    createDefaultMapping(); 
}

CubePatterns::CubePatterns(const vector<int>& nodes): m_cube() {

    createNodesMapping(nodes);
}

CubePatterns::CubePatterns(const vector<int>& nodes,
        const vector<int>& edges) {

    createEdgesMapping(nodes, edges);
    m_cube = Cube(m_localVector);
}

void CubePatterns::createDefaultMapping() {

    for (int i=0; i<CORNER_POINTS; i++) 
        m_NodesMap.insert(make_pair(InternalPoints[i],CubeMapping_t(i , i)));

}
void CubePatterns::createNodesMapping(const vector<int>& nodes) {

    int SIZE = CORNER_POINTS;
    if (nodes.size() < SIZE)
        SIZE = nodes.size();

    TableIter it = nodes.begin();
    for (int i=0; i< SIZE; i++)
        m_NodesMap.insert(make_pair(InternalPoints[i],CubeMapping_t(i,*it++)));
}

void CubePatterns::createEdgesMapping(const vector<int>& nodes,
        const vector<int>& edges) {

    createNodesMapping(nodes);

    m_localVector.clear();

    //int SIZE = nodes.size() - edges.size();
    TableIter itn = nodes.begin() + CORNER_POINTS;
    TableIter ite;

    for (ite=edges.begin(); ite != edges.end(); ++ite) {
        cout << "createEdgesMapping --> size: " << edges.size() 
            <<" Edge: " << *ite << " InternalPoint[" << *ite << "]: " 
            << InternalPoints[*ite] << " Node: " << *itn << endl;

        m_NodesMap.insert(make_pair(InternalPoints[*ite], 
                    CubeMapping_t(*ite, *itn++)));

        m_localVector.push_back(InternalPoints[*ite]);

    }
}



bool CubePatterns::findLocalPattern()
{

    if ( (m_NodesMap.size() != 0) && (m_localEdgesMap.size() != 0) )
    {
        m_patternHasBeenFound = true;
    }
    else
        m_patternHasBeenFound = false;

    return m_patternHasBeenFound;

}

void CubePatterns::rotate() {

    Coordinate axis;
    int step;
    
    //const Permutations_t (*perm) = RotationMatrix;

    for (int i=0; i<PERMUTATIONS; i++) {

        axis = RotationMatrix[i].Axis;
        step = RotationMatrix[i].Step;
        if (axis == X)
            m_cube.rotX(step);
        else if (axis == Y)
            m_cube.rotY(step);
        else if (axis ==Z)
            m_cube.rotZ(step);


        std::cout << " Edge Number " ;
        unsigned int mask = 0;
        
        bitMask.reset();
        PatternTable_t local;

        m_cube.getEdgePoints(local);
        for (TableIter it=local.begin(); it != local.end(); ++it) {

            cout << *it << " --> " << ExternalPoints[*it] << " ";

            mask |= 1<<ExternalPoints[*it];

            bitMask.set(ExternalPoints[*it]);

        }
        cout << "  Edge Mask: " << mask << "  " << bitMask << " " << endl ;
        cout << "------------------------------------" << endl;

        
    }
}

void CubePatterns::rotateCubePatterns(int times = 1 )
{
//    if (m_localPatternMap.size() == CORNER_POINTS)
//    {
//        /*
//           for (int i=0; i<times; i++)
//           {
//           for (PatternTable_t::iterator it=m_localVector.begin(); it!=m_localVector.end(); ++it )
//           {
//           (*it).second = RotationMatrix[rotation_positions[turn][(*it).first]];
//           }
//           }
//           */
//    }
}


void CubePatterns::reset()
{
    if (m_localPatternMap.size() > 0)
        m_localPatternMap.clear();

    if (m_NodesMap.size() > 0)
        m_NodesMap.clear();

    initialize();
}


void CubePatterns::initialize()
{
    if (m_localVector.size() > 0)
        m_localVector.clear();

    for(unsigned int i=0; i<TOTAL_POINTS; i++)
    {
        m_localVector.push_back(i);
    }
}

}

