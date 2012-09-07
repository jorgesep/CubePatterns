/*
 * Cube.cpp
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#include <math.h>
#include <algorithm>
#include "Cube.h"


using namespace std;


namespace patterns {

const Uint Cube::ExternalToInternal[TOTAL_POINTS] = {
    0,  18, 20, 2, 6, 24, 26, 8,
    9,  19, 11, 1, 3, 21, 23, 5,
    15, 25, 17, 7,10, 12, 22,14,
    4,  16, 13
};

const Uint Cube::InternalToExternal[TOTAL_POINTS] = {
    0, 11, 3,  12, 24, 15,  4, 19, 7,
    8, 20, 10, 21, 26, 23, 16, 25,18,
    1,  9, 2,  13, 22, 14,  5, 17, 6
};


Cube::Cube(): m_mask(0) { 
    //Default eight corner point.
    addCornerPointsMap(); 
}

Cube::Cube(const vector<Uint>& edges ): m_mask(0) {

    if (edges.size() > 0) {        

        for (int i=0; i<edges.size(); i++)
            // Convert input edge points to local internal mapping.
            m_edges.push_back(ExternalToInternal[edges[i]]);
        
        // Sort points ascending.
        sort (m_edges.begin(), m_edges.begin() + m_edges.size() );

        //Inserts input edge points into the same map of corner points.
        addEdgePointsMap();
    }

    //Insert eight default corner points into the map.
    addCornerPointsMap();
}

void Cube::resetCube() {
    m_MapVertices.clear();
    addCornerPointsMap();
    addEdgePointsMap();
}

void Cube::addNewPoint(int point) {
    Point tmpPoint = Point(point);

    if (m_MapVertices.find(tmpPoint.getInitPoint()) == m_MapVertices.end())
        m_MapVertices.insert(std::make_pair(tmpPoint.getInitPoint(), tmpPoint));
}

void Cube::deletePoint(int point)
{
    m_MapVertices.erase (m_MapVertices.find(point));
}

void Cube::rotate(int axis, int rot) {

    if ((axis > -1) && (axis < 3)) {

        //Mask of rotated edge points.
        Uint mask = 0;
        
        // Get edge points iterator already configured in the constructor.
        vector<Uint>::iterator Iter = m_edges.begin();

        // Clean up all previous rotation
        m_rotated_edges.clear();

        /// Gets a number of 90 degree steps.
        /// If negative rotation converts to similar positive rotation.
        int step = this->getRotationSteps(rot);

        /// This loop rotates toward axis direction.
        /// Rotates all points of the map (corner and edge points)
        for (PointMapIter it  = m_MapVertices.begin(); it != m_MapVertices.end(); 
                ++it) {
            if      (axis == 0)
                (*it).second.rotX(step);

            else if (axis == 1)
                (*it).second.rotY(step);

            else if (axis == 2)
                (*it).second.rotZ(step);
            
            if (!m_edges.empty()) 
            {
                if ( (*it).first == (*Iter) && (Iter != m_edges.end()) ) {
                    
                    // Shift a left value edge point times to build a mask.
                    mask |=1<<InternalToExternal[(*it).second.getRotatedPoint()];
    
                    // Puts into local vector the point number the result 
                    // of rotated edge points.
                    m_rotated_edges.push_back((*it).second.getRotatedPoint());
                    ++Iter;
                    
                    //This display rotation of points.
                    //cout << " " << (*it).first << "-->" << (*it).second.getRotatedPoint() << " ";
                }

            }

        }
        /// Save obtained mask in public variable.
        if (mask)
            m_mask = mask;
    }
}

void Cube::rotX(int rotation) {
    this->rotate(0,rotation);
}

void Cube::rotY(int rotation) {
    this->rotate(1,rotation);
}

void Cube::rotZ(int rotation) {
    this->rotate(2,rotation);
}

void Cube::getInitPoints(vector<Uint> & nodes) {
    nodes.clear();

    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        nodes.push_back( InternalToExternal[(*it).first] );
    }
}


void Cube::getCurrentPoints(vector<Uint> & nodes) {
    nodes.clear();

    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        nodes.push_back( InternalToExternal[(*it).second.getRotatedPoint()] );
    }
}

void Cube::getCurrentPoints(map<Uint, Uint> & nodes) {
    nodes.clear();

    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        nodes.insert( make_pair(InternalToExternal[(*it).second.getRotatedPoint()],
                                InternalToExternal[(*it).second.getInitPoint()]));
    }
}



void Cube::getEdgePoints(vector<Uint> & edges) {

    if (m_rotated_edges.empty()) {
        for (Uint i=0; i<m_edges.size(); i++)
            edges.push_back( InternalToExternal[ m_edges[i] ] );
    }
    else {
        for (Uint i=0; i<m_rotated_edges.size(); i++)
            edges.push_back( InternalToExternal[ m_rotated_edges[i] ] );
    }

}

void Cube::addCornerPointsMap() {

    // Map of defaultvertices.
    m_MapVertices.insert(std::make_pair(0, Point(0,0,0)));/// 0
    m_MapVertices.insert(std::make_pair(18,Point(0,0,2)));/// 18
    m_MapVertices.insert(std::make_pair(20,Point(2,0,2)));/// 20
    m_MapVertices.insert(std::make_pair(2, Point(2,0,0)));/// 2
    m_MapVertices.insert(std::make_pair(6, Point(0,2,0)));/// 6
    m_MapVertices.insert(std::make_pair(24,Point(0,2,2)));/// 24
    m_MapVertices.insert(std::make_pair(26,Point(2,2,2)));/// 26
    m_MapVertices.insert(std::make_pair(8, Point(2,2,0)));/// 8

}

void Cube::addEdgePointsMap() {
    if ( m_edges.size() > 0 ) {

        for (vector<Uint>::iterator it  = m_edges.begin(); 
                it != m_edges.end(); 
                ++it) 
            m_MapVertices.insert(std::make_pair( Point(*it).getInitPoint(), Point(*it)));
    }

}

int Cube::getRotationSteps(int rotation) {
    int step = 0;

    /// Check positive or negative 90 degree steps.
    if (rotation < 0) {
        step = (int)fabs(rotation) % 4;
        if      (step == 3) step = 1;
        else if (step == 1) step = 3;
    }
    else
        step = rotation % 4;

    return step;
}


string Cube::reportRotation() {
    stringstream report ;
    
    report << "|SIZE: "<< m_edges.size() << " NODES:";
    
    for (vector<Uint>::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
        report << " " << InternalToExternal[(*it)] ;
    
    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        report << "| " << InternalToExternal[(*it).second.getInitPoint()] << 
            "-->" << InternalToExternal[(*it).second.getRotatedPoint()] ;
    }
    return report.str();
}



}
