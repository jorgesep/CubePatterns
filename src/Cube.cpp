/*
 * Cube.cpp
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#include <math.h>
#include "Cube.h"


using namespace std;


namespace patterns {

Cube::Cube() { 
    this->addCornerPointsMap(); 
}

Cube::Cube(const vector<int>& edges ) {
    m_Edges = edges ;
    this->addCornerPointsMap();
    this->addEdgePointsMap();

}

void Cube::resetCube() {
    m_MapVertices.clear();
    this->addCornerPointsMap();
    this->addEdgePointsMap();
}

void Cube::addNewPoint(int point) {
    Point tmpPoint = Point(point);

    if (m_MapVertices.find(tmpPoint.getID()) == m_MapVertices.end())
    {
        m_MapVertices.insert(std::make_pair(tmpPoint.getID(), tmpPoint));
    }
}

void Cube::deletePoint(int point)
{
    m_MapVertices.erase (m_MapVertices.find(point));
}

void Cube::rotate(int axis, int rot) {
    if ((axis > -1) && (axis < 3)) {
        vector<int>::iterator Iter = m_Edges.begin();
        m_rotated_edges.clear();

        /// Gets the integer number of 90 degree steps.
        /// If negative rotation converts to similar positive rotation.
        int step = this->getRotationSteps(rot);

        for (PointMapIter it  = m_MapVertices.begin(); 
                it != m_MapVertices.end(); 
                ++it) {
            if (axis == 0)
                (*it).second.rotX(step);
            else if (axis == 1)
                (*it).second.rotY(step);
            else if (axis == 2)
                (*it).second.rotZ(step);

            if ( (*it).first == (*Iter) ) {

//                cout << "Cube::rotate :" << (*it).first
//                    << " --> " << (*it).second.getPoint() << " " ;
                m_rotated_edges.push_back((*it).second.getPoint());
                Iter++;
            }

        }
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

void Cube::getInitPoints(vector<int> & nodes) {
    nodes.clear();

    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        nodes.push_back( (*it).first );
    }
}


void Cube::getCurrentPoints(vector<int> & nodes) {
    nodes.clear();

    for (PointMapIter it  = m_MapVertices.begin(); 
            it != m_MapVertices.end(); 
            ++it) {
        nodes.push_back( (*it).second.getPoint() );
    }
}

void Cube::getEdgePoints(vector<int> & edges) {

    if (m_rotated_edges.empty())
        edges = m_Edges;
    else
        edges = m_rotated_edges;

}

void Cube::addCornerPointsMap() {

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
    if (!m_Edges.empty()) {

        for (vector<int>::iterator it  = m_Edges.begin(); 
                it != m_Edges.end(); 
                ++it)
            m_MapVertices.insert(std::make_pair( Point(*it).getID(), Point(*it)));
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

}
