// A simple program that computes the square root of a number
//#include <stdio>
//#include <stdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include "CubePatterns.h"

using namespace patterns;
using namespace std;

int main (int argc, char *argv[])
{


    vector<int> nodes;
    vector<int> edges;

    nodes.push_back(61);
    nodes.push_back(62);
    nodes.push_back(63);
    nodes.push_back(64);
    nodes.push_back(65);
    nodes.push_back(66);
    nodes.push_back(67);
    nodes.push_back(68);
    nodes.push_back(168);
    nodes.push_back(194);

    edges.push_back(8);
    edges.push_back(10);



    CubePatterns *pattern = new CubePatterns(nodes, edges);

    pattern->rotate();

    delete pattern;

    return 0;
}
