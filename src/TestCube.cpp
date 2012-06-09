// A simple program that computes the square root of a number
//#include <stdio>
//#include <stdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include "Cube.h"

using namespace patterns;
using namespace std;

int main (int argc, char *argv[])
{

    vector<int> init;
    vector<int> _90deg;
    vector<int> _180deg;
    vector<int> _270deg;
    vector<int> _0deg;
    vector<int> nodes;

    vector<int>::const_iterator Iter0 ;
    vector<int>::const_iterator Iter1 ;
    vector<int>::const_iterator Iter2 ;
    vector<int>::const_iterator Iter3 ;


    vector<int> edges;
    edges.push_back(9);
    edges.push_back(11);

    Cube pattern = Cube(edges);
    pattern.getInitPoints(init);

    pattern.rotX(1);
    pattern.getCurrentPoints(_90deg);

    pattern.rotX(1);
    pattern.getCurrentPoints(_180deg);

    pattern.rotX(1);
    pattern.getCurrentPoints(_270deg);

    pattern.rotX(1);
    pattern.getCurrentPoints(_0deg);

    pattern.rotX(2);
    pattern.resetCube();

    Iter0 = _0deg.begin() ;
    Iter1 = _90deg.begin() ;
    Iter2 = _180deg.begin() ;
    Iter3 = _270deg.begin() ;

    for (vector<int>::const_iterator it  = init.begin();
                               it != init.end();
                             ++it)
    {
        cout << *it << " --> " << (*Iter1++) << " --> " << (*Iter2++)  << " --> " << (*Iter3++) << " --> " << (*Iter0++) << endl;
    }

    cout << "--------------------" << endl << endl;

    pattern.rotY(1);
    pattern.getCurrentPoints(_90deg);

    pattern.rotY(1);
    pattern.getCurrentPoints(_180deg);

    pattern.rotY(1);
    pattern.getCurrentPoints(_270deg);

    pattern.rotY(1);
    pattern.getCurrentPoints(_0deg);

    pattern.rotY(2);
    pattern.resetCube();

    Iter0 = _0deg.begin() ;
    Iter1 = _90deg.begin() ;
    Iter2 = _180deg.begin() ;
    Iter3 = _270deg.begin() ;

    for (vector<int>::const_iterator it  = init.begin();
                               it != init.end();
                             ++it)
    {
        cout << *it << " --> " << (*Iter1++) << " --> " << (*Iter2++)  << " --> " << (*Iter3++) << " --> " << (*Iter0++) << endl;
    }

    cout << "--------------------" << endl << endl;

    pattern.rotZ(1);
    pattern.getCurrentPoints(_90deg);

    pattern.rotZ(1);
    pattern.getCurrentPoints(_180deg);

    pattern.rotZ(1);
    pattern.getCurrentPoints(_270deg);

    pattern.rotZ(1);
    pattern.getCurrentPoints(_0deg);

    pattern.rotZ(2);
    pattern.resetCube();

    Iter0 = _0deg.begin() ;
    Iter1 = _90deg.begin() ;
    Iter2 = _180deg.begin() ;
    Iter3 = _270deg.begin() ;

    for (vector<int>::const_iterator it  = init.begin();
                               it != init.end();
                             ++it)
    {
        cout << *it << " --> " << (*Iter1++) << " --> " << (*Iter2++)  << " --> " << (*Iter3++) << " --> " << (*Iter0++) << endl;
    }



//    pattern.rotX(1);
//    pattern.getPoints(nodes);
//
//    cout << "--------------------" << endl;
//    i = 0 ;
//    for (vector<int>::iterator it  = nodes.begin();
//                               it != nodes.end();
//                             ++it)
//    {
//        cout << i++ << "--> " << *it << endl;
//    }
//
//    pattern.rotX(1);
//    pattern.getPoints(nodes);
//
//    cout << "--------------------" << endl;
//    i = 0 ;
//    for (vector<int>::iterator it  = nodes.begin();
//                               it != nodes.end();
//                             ++it)
//    {
//        cout << i++ << "--> " << *it << endl;
//    }
//
//    pattern.rotX(1);
//    pattern.getPoints(nodes);
//    cout << "--------------------" << endl;
//    i = 0 ;
//    for (vector<int>::iterator it  = nodes.begin();
//                               it != nodes.end();
//                             ++it)
//    {
//        cout << i++ << "--> " << *it << endl;
//    }
//
//    pattern.resetCube();
//    pattern.getPoints(nodes);
//     cout << "--------------------" << endl;
//    i = 0 ;
//    for (vector<int>::iterator it  = nodes.begin();
//                               it != nodes.end();
//                             ++it)
//    {
//        cout << i++ << "--> " << *it << endl;
//    }


    return 0;
}
