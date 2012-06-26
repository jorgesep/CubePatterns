/*
 * Cube.h
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <vector>
#include <map>
#include <iostream>
#include "Point.h"

using namespace std;

namespace patterns {

/**
 * Creates a basic cube
 *
 *       6--------7--------8
 *      /|                /|
 *     / |               / |
 *   15  |     16       17 |
 *   /   3        4    /   5
 * 24----+--25--------26   |
 *  | 12 |        13  |  14|
 *  |    0--------1---|----2
 *  |   /             |   /
 *  |  9        10    |  11
 * 21 /       22      23/
 *  |/                |/
 * 18--------19-------20
 *
 */
class Cube {
public:
    /**
     * Default constructor.
     */
    Cube();

    virtual ~Cube() { };

    /**
     * Creates a cube assigning edge and mid points.
     */
    Cube(const vector<int>& edges);

    /**
     * Copy constructor
     */
    Cube(const Cube & c) { *this = c; };

    /**
     * Assignment operator
     */
    Cube &operator =(const Cube &c)  
    {
        if (*this != c) { m_MapVertices = c.m_MapVertices; m_Edges = c.m_Edges; }
        return *this;
    };

    /**
     * Equals operator
     */ 
    bool operator ==(const Cube &c) const {
        return ( (m_MapVertices == c.m_MapVertices) || (m_Edges==c.m_Edges) );
    };

    bool operator !=(const Cube &c) const {
        return ( (m_MapVertices != c.m_MapVertices) || (m_Edges!=c.m_Edges) );
    };


    /**
     * Cube start over
     * Sets all hexahedron points to init condition, all rotations will lost.
     */
    void resetCube(); 

    /**
     * Adds on a new edge or face vertices to hexahedron.
     * Vertices already present in the cube are not appended.
     */
    void addNewPoint(int);

    /**
     * Removes a edge or face point currently in the hexahedron
     */
    void deletePoint(int);

    /**
     * Rotates cube in 90 degree steps.
     * Positive step is right hand direction rotation.
     * Rotation step of +1 unit is a 90 degree clockwise.
     */
    void rotX(int);

    /**
     * Rotates Y cube in 90 degree steps.
     * Positive step is right hand direction rotation.
     * Rotation step of +1 unit is a 90 degree clockwise.
     */
    void rotY(int);

    /**
     * Rotates Z cube in 90 degree steps.
     * Positive step is right hand direction rotation.
     * Rotation step of +1 unit is a 90 degree clockwise.
     */
    void rotZ(int);

    /**
     * Return init points
     */
    void getInitPoints(vector<int> & );

    /**
     * Return vector of points
     */
    void getCurrentPoints(vector<int> & );

    /**
     * Return vector of points
     */
    void getEdgePoints(vector<int> & );

private:
    /**
     * Creates eight default corner points of the hexahedron.
     * Each hexahedron point is defined by a three dimension vector (x,y,z).
     */
    void addCornerPointsMap();

    /**
     * Adds up edge and face vectors to the hexahedron. 
     */
    void addEdgePointsMap();

    /**
     * Calculates number of step repetions
     */
    int getRotationSteps(int);

    void rotate (int, int);

    typedef vector<Point> PointVector;
    typedef vector<Point>::iterator PointVectorIter;

    typedef map<int,Point> PointMap_t;
    typedef PointMap_t::iterator PointMapIter;

    PointMap_t  m_MapVertices;

    //PointVector m_Vertices;
    vector<int> m_Edges;
    vector<int> m_rotated_edges;

};

}

#endif /* CUBE_H_ */
