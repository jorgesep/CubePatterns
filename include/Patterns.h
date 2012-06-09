/*
 * PatternsDefault.h
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include <vector>
#include <map>
#include "Cube.h"


#ifndef PATTERNSDEFAULT_H_
#define PATTERNSDEFAULT_H_


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
 *        / 12           / 15
 *       5---+---17-----6   |
 *       |   |          |   |
 *      13   |         14   |
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
class CubePatterns 
{

public:
	/// Defines six possible rotations in x,y,z
	enum Rotation
	{
		Z_left=0,
		Z_right,
		X_left,
		X_right,
		Y_left,
		Y_right
	};

        /// Default constructor, creates an empty cube it needs to be initialized
	CubePatterns();

       /**
        * Creates an assigns input vectors to internal local map and finds the pattern 
        * associated to hexahedron defined by vectors.
        */
	CubePatterns(const std::vector<unsigned int>& , const std::vector<unsigned int>& );

	virtual ~CubePatterns();

       /**
        * Rotate the cube to left or right position in one of the 
        * three x,y,z axis.
        *
        * For each of the axis movement has been defined a default 
        * start position.
        *
        * Axis 'z' start position
        *      4----9------7
        *     /|          /|
        *    / |         / |
        *   5-----------6  |
        *   |  |        |  |
        *   |  0----8---|--3
        *   | /         | /
        *   |/          |/
        *   1-----------2
        *
        * Axis 'x' start position
        *      5-----------6
        *     /|          /|
        *    / |         / |
        *   1-----------2  |
        *   |  |        |  |
        *   |  4----9---|--7
        *   | /         | /
        *   |/          |/
        *   0----8------3
        *
        * Axis 'y' start position
        *      3-----------2
        *     /|          /|
        *    / 8         / |
        *   7-----------6  |
        *   |  |        |  |
        *   9  0--------|--1
        *   | /         | /
        *   |/          |/
        *   4-----------5
        *
        */
	void rotate() {};
	void setFacePoints();
	void setEdgePoints();
	void setCornerPoints();

	/** It creates an internal map of the input nodes into defined vertexs
	 *  numbered from 0 to 25 of a basic hexahedron. The first eight nodes
	 *  (0-7) are the corner vertexs of this hexahedron, the other left
	 *  nodes are vertexs located either at any edges or any of the faces
	 *  of this hexahedron.
	 */
	void mapLocalCubePatterns(const std::vector<unsigned int>& , 
                                  const std::vector<unsigned int>& );

	/**
	 * Match the input hexahedron to any of the patterns defined.
	 */
	bool findLocalPattern();

	/**
	 * Rotates hexahedron n times to Rotation position.
	 */
	void rotateCubePatterns(Rotation, int);

	void reset();

private:

	/**
	 * Initializes hexahedron pattern to default node positions.
	 */
	void initialize();


	typedef std::vector<unsigned int> PatternTable_t;
	typedef PatternTable_t::const_iterator TableIter;
	typedef std::map< unsigned int, unsigned int > PatternMap_t;
	typedef PatternMap_t::const_iterator MapIter;

	static const unsigned int TETRA_POINTS;
	static const unsigned int PYRAMID_POINTS;
	static const unsigned int PRISM_POINTS;
	static const unsigned int CORNER_POINTS;
	static const unsigned int EDGE_POINTS;
	static const unsigned int FACE_POINTS;
	static const unsigned int TOTAL_POINTS;



	int m_numVertex;
	int m_numTetra;
	int m_numPyramid;
	int m_numPrism;

	bool m_patternHasBeenFound;

	PatternTable_t m_localVector;
	PatternMap_t m_localNodesMap;
	PatternMap_t m_localEdgesMap;
	PatternMap_t m_localPatternMap;

    /**
     * Matrix of rotations
     * Return new vertex values after one turn in one of the three x,y,z axis.
     */
    static const int RotationMatrix[26][6];


/*
	typedef std::map< int, AMBSystem::AmbChannel > ChanMap_t;
	  typedef ChanMap_t::const_iterator CHMapIter;

	  typedef std::multimap< CAI_t, LookupTable_t > MMapT;
	  typedef MMapT::const_iterator MMIterT;
	  typedef std::map< CAI_t, LookupTable_t > SMapT;
	  typedef SMapT::const_iterator SMIterT;


	  typedef std::vector<CAIChannel_t> CAIChannelVec_t;
	  typedef CAIChannelVec_t::const_iterator ChanIter;
*/

};



class RotationCube
{


};

}

#endif /* PATTERNSDEFAULT_H_ */
