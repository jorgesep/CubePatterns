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
    //typedef unsigned int Uint;
    /**
     * Default constructor.
     */
    Cube();

    virtual ~Cube() { };

    /**
     * Creates a cube assigning edge and mid points.
     */
    Cube(const vector<Uint>& edges);

    /**
     * Copy constructor
     */
    Cube(const Cube & c) { *this = c; };

    /**
     * Assignment operator
     */
    Cube &operator =(const Cube &c)  
    {
        if (*this != c) { m_MapVertices = c.m_MapVertices; m_edges = c.m_edges; }
        return *this;
    };

    /**
     * Equals operator
     */ 
    bool operator ==(const Cube &c) const {
        return ( (m_MapVertices == c.m_MapVertices) || (m_edges==c.m_edges) );
    };

    bool operator !=(const Cube &c) const {
        return ( (m_MapVertices != c.m_MapVertices) || (m_edges!=c.m_edges) );
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
    void getInitPoints(vector<Uint> & );

    /**
     * Return vector of points
     */
    void getCurrentPoints(vector<Uint> & );

    /**
     * Return map of init and rotated value of each point.
     */
    void getCurrentPoints(map<Uint, Uint>& );

    /**
     * Return vector of points
     */
    void getEdgePoints(vector<Uint> & );

private:
    /**
     * Creates a default eight corner points.
     * Populates internal map with a vertice and object point.
     * Each point is defined by a vector of three dimensions (x,y,z).
     */
    void addCornerPointsMap();

    /**
     * Inserts edge vectors into the internal map
     */
    void addEdgePointsMap();

    /**
     * Calculates number of step repetions
     */
    int getRotationSteps(int);

    void rotate (int, int);

    typedef vector<Point> PointVector;
    typedef vector<Point>::iterator PointVectorIter;

    /**
     * Map of a vertice and object point (x,y,z)
     */
    typedef map<Uint,Point> PointMap_t;
    typedef PointMap_t::iterator PointMapIter;

    PointMap_t  m_MapVertices;

    vector<Uint> m_edges;
    vector<Uint> m_rotated_edges;

    // total number of cube points
    static const Uint TOTAL_POINTS = 27;

    /**
     * Public points defined in the patterns.
     */
    static const Uint ExternalToInternal[];

    /**
     * Container of internal points defined in cube class
     */
    static const Uint InternalToExternal[];



};

}

#endif /* CUBE_H_ */
