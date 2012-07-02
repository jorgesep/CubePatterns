/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "CubePatterns.h"

using namespace std;

namespace patterns {

const CubePatterns::Permutations_t CubePatterns::RotationMatrix[PERMUTATIONS] = {

    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 90  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 180  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 270  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 360 --> 0  
    Permutations_t(X,1), /// X --> 90  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360

    Permutations_t(X,2), /// X --> 270 X-->180 is the same Y-->180  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1)  /// Z --> 360
};


CubePatterns::CubePatterns()  { 

    m_cube = new Cube();

    // builds a map with default values of corner points (0,1,..7)
    createDefaultMapping(); 

    factory = PatternFactory::instance();
}

CubePatterns::CubePatterns(const UintVec& nodes) {

    m_cube = new Cube();
    // makes map with values of input vector
    createNodesMapping(nodes);

    factory = PatternFactory::instance();
}

CubePatterns::CubePatterns(const UintVec& nodes, const UintVec& edges) {

    if (edges.size() > 0 ) {
        // Creates a map with nodes and edge values.
        createEdgesMapping(nodes, edges);
        m_cube = new Cube(m_localVector);
    }
    else {
        createNodesMapping(nodes);
        m_cube = new Cube();
    }

    factory = PatternFactory::instance();
}

void CubePatterns::createDefaultMapping() {

    for (Uint i=0; i<CORNER_POINTS; i++) 
        m_NodesMap.insert( make_pair( i, CubeMapping_t(i , i)) );

}

/// Insert input vector into internal map.
void CubePatterns::createNodesMapping(const UintVec& nodes) {

    Uint SIZE = CORNER_POINTS;
    if (nodes.size() < SIZE)
        SIZE = nodes.size();

    UintVecIt it = nodes.begin();
    for (Uint i=0; i< SIZE; i++)
        m_NodesMap.insert( make_pair( i, CubeMapping_t(i,*it++)) );
}

/// Insert the input vector of edge point into local vector.
void CubePatterns::createEdgesMapping(const UintVec& nodes, const UintVec& edges) {

    // insert first eight input nodes into an internal map.
    createNodesMapping(nodes);

    m_localVector.clear();

    UintVecIt itn = nodes.begin() + CORNER_POINTS;
    UintVecIt ite = edges.begin();

    int SIZE;
    if ( nodes.size() > CORNER_POINTS)
        SIZE = nodes.size() - CORNER_POINTS;
    else 
        SIZE = nodes.size();


    for ( ;itn != nodes.end(); ++itn) {

        // This map is a link of internal and external points
        // The constructor was created with point 123 which is linked to 11
        // Example: 11 --> (11,123)
        m_NodesMap.insert( make_pair( *ite, CubeMapping_t(*ite, *itn) ) );

        //Keep a local copy of edge nodes.
        m_localVector.push_back(*ite);

        ++ite;

    }
}

/// Rotate cube until find a pattern
void CubePatterns::search() {

    Coordinate axis;
    int step;

    // Max cube rotation defined in PERMUTATIONS
    for (int i=0; i<PERMUTATIONS; i++) {

        axis = RotationMatrix[i].Axis;
        step = RotationMatrix[i].Step;
        if (axis == X)
            m_cube->rotX(step);
        else if (axis == Y)
            m_cube->rotY(step);
        else if (axis ==Z) 
            m_cube->rotZ(step);

        //Uint mask = m_cube->getEdgePointsMask();

        //Check if rotated cube mask matchs to one the masks in factory.
        if( factory->createPattern( m_cube->getEdgePointsMask() ) ){
            factory->vectors(m_result);
            break;
        }
    }
}


void CubePatterns::reset()
{

    if (m_NodesMap.size() > 0)
        m_NodesMap.clear();

    initialize();
}


void CubePatterns::initialize()
{
    if (m_localVector.size() > 0)
        m_localVector.clear();

    for(Uint i=0; i<TOTAL_POINTS; i++)
    {
        m_localVector.push_back(i);
    }
}

void CubePatterns::vectors(VectorTable &v) {

    UintMap points;

    // Returns: rotated --> init point
    m_cube->getCurrentPoints(points);

    if(!m_result.empty()) {
       for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {
   
           UintVec p;
   
           for (UintVecIt it1=(*it).begin(); it1!=(*it).end(); ++it1) {
               Uint internal = points.find(*it1)->second;
               p.push_back( m_NodesMap.find(internal)->second.External );
           }
   
           v.push_back(p);
       }
    }
}

void CubePatterns::normal_vectors(VectorTable &v) {

    UintMap points;

    // Returns: rotated --> init point
    m_cube->getCurrentPoints(points);


    for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {

        UintVec p;

        for (UintVecIt it1=(*it).begin(); it1!=(*it).end(); ++it1) 
            p.push_back(points.find(*it1)->second);

        v.push_back(p);
    }
}
}

