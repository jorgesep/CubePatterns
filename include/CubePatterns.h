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
#include "PatternFactory.h"


#ifndef CUBEPATTERNS_H_
#define CUBEPATTERNS_H_

using namespace std;

/**
 * This is a base class for polyhedron
 * it defines basic operations
 */

namespace patterns {


/**
 * CubePatterns:
 * Receives a vector of corner and edge hexahedron points as a input 
 * parameters, it classifies into a known pattern, splits up and returns a 
 * vector of regular polyhedra corner points vectors. These vectors are 
 * composed by tetraedra, prisms or pyramids according to a previous
 * division of the known patterns.
 *
 * The corner, edge and mid points of the hexahedron have been defined by
 * the following arrangement.
 *
 *           4----19--------7
 *          /|             /|
 *         16|    25      18|
 *        / 12           /  15
 *       5---+---17-----6   |
 *       |  1|          |  3|
 *      13 2 |         14 2 |
 *       |   0-----11---|---3
 *       |  /           |  /
 *       | 8     20     |10
 *       |/             |/
 *       1------9-------2
 *
 *
 * Example:
 * std::vector<int> cp // {0,1,2,4,5,6,7}
 * std::vector<int> edge //{17,12} 
 * cube = CubePatterns(cp,edge);
 * std::vector< std::vector<int> > results = cube.getPatternResults();
 *
 */
class CubePatterns {

public:

    typedef vector< vector<Uint> > VectorTable;
    enum Coordinate { X, Y, Z };

    /**
     * Internal struct to link external to local points.
     */
    struct CubeMapping_t {
        //Default constructor
        CubeMapping_t (): Local(0), External(0) { };

        //Default constructor
        CubeMapping_t (int p1, int p2): Local(p1), External(p2) { };

        //Copy constructor
        CubeMapping_t (const CubeMapping_t & m ) { *this = m; };

        //Assignment operator
        CubeMapping_t & operator=( const CubeMapping_t & m ) {
            if (*this != m) {
                Local = m.Local;
                External = m.External;
            }
            return *this;
        }

        //Equals operator
        bool operator ==(const CubeMapping_t &m) const {
            return ((Local == m.Local)&&(External == m.External));
        }

        //Not Equals operator
        bool operator !=(const CubeMapping_t &m) const {
            return ((Local != m.Local) || (External != m.External));
        }

        int Local;
        int External;
    };

    struct Permutations_t {
        //Default constructor
        Permutations_t (): Axis(X), Step(0) { };

        //Default constructor
        Permutations_t (Coordinate c, int s): Axis(c), Step(s) { };

        //Copy constructor
        Permutations_t (const Permutations_t & p ) { *this = p; };

        //Assignment operator
        Permutations_t & operator=( const Permutations_t & p ) {
            if (*this != p) {
                Axis = p.Axis;
                Step = p.Step;
            }
            return *this;
        }

        //Equals operator
        bool operator ==(const Permutations_t &p) const {
            return ((Axis == p.Axis)&&(Step == p.Step));
        }

        //Not Equals operator
        bool operator !=(const Permutations_t &p) const {
            return ((Axis != p.Axis) || (Step != p.Step));
        }

        Coordinate Axis;
        int Step;
    };
    
    /**
     * Default constructor.
     * Creates a default eight corner point cube.
     */
    CubePatterns();

    /**
     * Cube parametric constructor.
     * Takes first eight number as corner points, the other input number are
     * not considered.
     */
    CubePatterns( const vector<int>& );

    /**
     * Cube parametric constructor.
     * Takes first eight number as corner points, the left number are taking
     * as edge points. 
     * The second vector is the mapping of edge points to internal convention.
     */
    CubePatterns(const vector<int>&, const vector<int>& );

    virtual ~CubePatterns() { };

    /**
     * Rotate the cube to left or right position in one of the 
     * three x,y,z axis.
     *
     * For each of the axis movement has been defined a default 
     * start position.
     *
     * Axis 'z' start position
     *      4----9------7     5-----------6      3-----------2
     *     /|          /|    /|          /|     /|          /|
     *    / |         / |   / |         / |    / 8         / |
     *   5-----------6  |  1-----------2  |   7-----------6  |
     *   |  |        |  |  |  |        |  |   |  |        |  |
     *   |  0----8---|--3  |  4----9---|--7   9  0--------|--1
     *   | /         | /   | /         | /    | /         | / 
     *   |/          |/    |/          |/     |/          |/  
     *   1-----------2     0----8------3      4-----------5  
     *
     */
    void rotate();
    void setFacePoints();
    void setEdgePoints();
    void setCornerPoints();

    /** 
     *  Creates an internal map of the input nodes into defined vertexs
     *  numbered from 0 to 25 of a basic hexahedron. The first eight nodes
     *  (0-7) are the corner vertexs of this hexahedron, the other left
     *  nodes are vertexs located either at any edges or any of the faces
     *  of this hexahedron.
     */
//    void mapLocalCubePatterns(const std::vector<unsigned int>& , 
//            const std::vector<unsigned int>& );

    void createLocalMapping(const vector<int>& );

    /**
     * Match the input hexahedron to any of the patterns defined.
     */
    bool findLocalPattern();

    /**
     * Rotates hexahedron n times to Rotation position.
     */
    void rotateCubePatterns(int);

    void reset();

    void vectors(VectorTable &v) { v = m_result; }; 

private:

    /**
     * Initializes hexahedron pattern to default node positions.
     */
    void initialize();

    void createDefaultMapping();
    void createNodesMapping(const vector<int>&);
    void createEdgesMapping(const vector<int>&, const vector<int>&);

    typedef vector<int> PatternTable_t;
    typedef PatternTable_t::const_iterator TableIter;
    typedef map<int, CubeMapping_t> PatternMap_t;
    typedef PatternMap_t::const_iterator MapIter;

    Cube m_cube;

    int m_numVertex;
    int m_numTetra;
    int m_numPyramid;
    int m_numPrism;

    bool m_patternHasBeenFound;

    bitset<27> bitMask;

    PatternTable_t m_localVector;
    PatternMap_t m_NodesMap;
    PatternMap_t m_localEdgesMap;
    PatternMap_t m_localPatternMap;

    VectorTable m_result;

    /**
     * Matrix of rotations
     * Return new vertex values after one turn in one of the three x,y,z axis.
     */
    static const Permutations_t RotationMatrix[];

    static const int ExternalPoints[];

    static const int InternalPoints[];

    /**
     * Mask is the result to left shift number 1 by the value of the edge point.
     * Final outcome is a logical OR combination of all edge points in the pattern.
     */ 
    static const int PatternMask[23];

};



}

#endif /* CUBEPATTERNS_H_ */
