/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "Patterns.h"

using namespace std;

namespace patterns {

const unsigned int CubePatterns::TETRA_POINTS=4;
const unsigned int CubePatterns::PYRAMID_POINTS=5;
const unsigned int CubePatterns::PRISM_POINTS=6;
const unsigned int CubePatterns::CORNER_POINTS=8;
const unsigned int CubePatterns::EDGE_POINTS=12;
const unsigned int CubePatterns::FACE_POINTS=6;
const unsigned int CubePatterns::TOTAL_POINTS=26;



const int CubePatterns::RotationMatrix[26][6] =
{       ///Z:L,R X:L,R Y:L,R
		{3,1,4,3,1,4},
		{0,2,5,2,5,0},
		{1,3,1,6,6,3},
		{2,0,0,7,2,7},
		{7,5,7,0,0,5},
		{4,6,6,1,4,1},
		{5,7,2,5,7,2},
		{6,4,3,4,3,6},
		{11,9,16,10,13,12},
		{8,10,13,14,17,11},
		{9,11,8,18,14,15},
		{10,8,12,15,9,19},
		{15,13,19,11,8,16},
		{12,14,17,9,16,8},
		{13,15,9,17,18,10},
		{14,12,11,19,10,18},
		{19,17,18,8,12,13},
		{16,18,14,13,19,9},
		{17,19,10,16,15,14},
		{18,16,15,12,11,17},
		{20,20,21,23,22,24},
		{24,22,25,20,21,21},
		{21,23,22,22,25,20},
		{22,24,20,25,23,23},
		{23,21,24,24,20,25},
		{25,25,23,21,24,22}
};

CubePatterns::CubePatterns()
:m_numVertex(0),
 m_numTetra(0),
 m_numPyramid(0),
 m_numPrism(0),
 m_patternHasBeenFound(false)
{
	initialize();
}

CubePatterns::CubePatterns(const std::vector<unsigned int>& nodes, 
				const std::vector<unsigned int>& edges)
: m_numVertex(nodes.size()),
  m_numTetra(0),
  m_numPyramid(0),
  m_numPrism(0),
  m_patternHasBeenFound(false)
{
	initialize();
	mapLocalCubePatterns(nodes,edges);
}

CubePatterns::~CubePatterns() {
}

void CubePatterns::mapLocalCubePatterns(const std::vector<unsigned int>& nodes, const std::vector<unsigned int>& edges)
{
	if (nodes.size() >= CORNER_POINTS)
	{
		if (m_localNodesMap.size() > 0)
			m_localNodesMap.clear();

		//Creates the mapping.
		unsigned int i=0;
		TableIter itEdges = edges.begin();
		for (TableIter it=nodes.begin(); it!=nodes.end() ; ++it)
		{
			if (i<CORNER_POINTS)
				m_localNodesMap.insert(std::pair<unsigned int, unsigned int>\
                               (i++, *it));
			else {
				m_localNodesMap.insert(std::pair<unsigned int, unsigned int>\
                                (*itEdges++,*it));
				if (itEdges == edges.end())
					break;
			}

			m_numVertex++;
		}
	}
}

bool CubePatterns::findLocalPattern()
{

	if ( (m_localNodesMap.size() != 0) && (m_localEdgesMap.size() != 0) )
	{
		m_patternHasBeenFound = true;
	}
	else
		m_patternHasBeenFound = false;

	return m_patternHasBeenFound;

}

void CubePatterns::rotateCubePatterns(CubePatterns::Rotation turn, int times = 1 )
{
	if (m_localPatternMap.size() == CORNER_POINTS)
	{
/*
		for (int i=0; i<times; i++)
		{
			for (PatternTable_t::iterator it=m_localVector.begin(); it!=m_localVector.end(); ++it )
			{
				(*it).second = RotationMatrix[rotation_positions[turn][(*it).first]];
			}
		}
*/
	}
}


void CubePatterns::reset()
{
	if (m_localPatternMap.size() > 0)
		m_localPatternMap.clear();

	if (m_localNodesMap.size() > 0)
		m_localNodesMap.clear();

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

