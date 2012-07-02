/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "PatternFactory.h"

using namespace std;

namespace patterns {

    
PatternFactory* PatternFactory::m_Instance = NULL;
int PatternFactory::m_NumInstances = 0;

//const PatternFactory::Element PatternFactory::elements [MAX_ELEMENTS] = {
const PatternFactory::Element PatternFactory::elements [] = {
    {   //Pattern1: 4 pyramid mask: 11       
        2048,   {
                { PYRAMID_POINTS, {0,1,5,4,11}            },
                { PYRAMID_POINTS, {1,2,6,5,11}            },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {5,6,7,4,11}            } }
    },
    {   //Pattern2: 3 prisms
        526336, {
                { PRISM_POINTS,   {0,1,4,5,11,19}         },
                { PRISM_POINTS,   {1,2,6,5,11,19}         },
                { PRISM_POINTS,   {2,3,7,4,11,19}         } }
    },   
    {   //Pattern3: 6 tetrahedra - 2 pyramid  mask: 11|17  
        133120, {
                { TETRA_POINTS,   {1,2,17,11}             },
                { TETRA_POINTS,   {4,11,7,17}             },
                { TETRA_POINTS,   {1,17,5,11}             },
                { TETRA_POINTS,   {5,17,4,11}             },
                { TETRA_POINTS,   {2,6,17,11}             },
                { TETRA_POINTS,   {17,6,7,11}             },
                { PYRAMID_POINTS, {0,1,5,4,11}            },
                { PYRAMID_POINTS, {2,3,7,6,11}            } }
    },
    {   //Pattern4: 6 tetrahedra - 2 pyramid  mask: 11|13
        10240,  {
                { TETRA_POINTS,   {0,1,13,11}             },
                { TETRA_POINTS,   {4,13,5,11}             },
                { TETRA_POINTS,   {0,13,4,11}             },
                { TETRA_POINTS,   {1,2,8,13}              },
                { TETRA_POINTS,   {5,6,13,11}             },
                { TETRA_POINTS,   {13,2,6,11}             },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {4,5,6,7,11}            } }

    },
    {//Pattern4.1: 6 tetrahedra - 2 pyramid    11|14
         18432, {
                { TETRA_POINTS,   {0,1,14,11}             },
                { TETRA_POINTS,   {4,14,5,11}             },
                { TETRA_POINTS,   {0,14,4,11}             },
                { TETRA_POINTS,   {1,2,8,14}              },
                { TETRA_POINTS,   {5,6,14,11}             },
                { TETRA_POINTS,   {14,2,6,11}             },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {4,5,6,7,11}            } }
    },
    {//Pattern5: 12 tetrahedra mask:11|13|18
         272384,{
                { TETRA_POINTS,   {5,13,6,11}             },
                { TETRA_POINTS,   {2,6,13,11}             },
                { TETRA_POINTS,   {5,6,18,11}             },
                { TETRA_POINTS,   {0,1,13,11}             },
                { TETRA_POINTS,   {4,18,5,11}             },
                { TETRA_POINTS,   {0,18,4,11}             },
                { TETRA_POINTS,   {3,18,7,11}             },
                { TETRA_POINTS,   {4,18,7,11}             },
                { TETRA_POINTS,   {4,5,18,11}             },
                { TETRA_POINTS,   {2,6,18,11}             },
                { TETRA_POINTS,   {2,3,18,11}             },
                { TETRA_POINTS,   {18,1,2,11}             } }

    },
    {//Pattern6: 4 tetrahedra - 2 pyramid - 1 prism  mask: 11|13|19
         534528,{
                { TETRA_POINTS,   {0,1,13,11}             },
                { TETRA_POINTS,   {4,5,9,13}              },
                { TETRA_POINTS,   {1,2,13,11}             },
                { TETRA_POINTS,   {13,6,5,19}             },
                { PYRAMID_POINTS, {0,4,19,11,13}          },
                { PYRAMID_POINTS, {2,11,19,6,13}          },
                { PRISM_POINTS,   {2,3,7,6,11,19}         } }
    },
/*    
    {//Pattern6.1: 4 tetrahedra - 2 pyramid - 1 prism  mask :11|14|19
         542720,{
                { TETRA_POINTS,   {0,1,14,11}             },
                { TETRA_POINTS,   {4,5,9,14}              },
                { TETRA_POINTS,   {1,2,14,11}             },
                { TETRA_POINTS,   {14,6,5,19}             },
                { PYRAMID_POINTS, {0,4,19,11,14}          },
                { PYRAMID_POINTS, {2,11,19,6,14}          },
                { PRISM_POINTS,   {2,3,7,6,11,19}         } }
    },
*/    
    {//Pattern7: 5 tetrahedra - 3 pyramid   mask: 10|11|12
         6400,  {
                { TETRA_POINTS,   {0,8,11,12}             },
                { TETRA_POINTS,   {11,12,8,6}             },
                { TETRA_POINTS,   {2,11,8,6}              },
                { TETRA_POINTS,   {6,7,11,12}             },
                { TETRA_POINTS,   {5,12,8,6}              },
                { PYRAMID_POINTS, {1,2,6,5,8}             },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {4,5,6,7,12}            } }

    },
    {//Pattern8: 3 tetrahedra - 7 pyramid (Added centroid point) mask: 11|17|19
         657408,{
                { TETRA_POINTS,   {1,2,17,26}             },
                { TETRA_POINTS,   {2,6,17,26}             },
                { PYRAMID_POINTS, {1,1,7,5,26}            },
                { PYRAMID_POINTS, {0,1,2,3,26}            },
                { PYRAMID_POINTS, {3,7,19,11,26}          },
                { PYRAMID_POINTS, {0,4,19,11,26}          },
                { PYRAMID_POINTS, {0,1,5,4,26}            },
                { PYRAMID_POINTS, {2,3,7,6,26}            },
                { PYRAMID_POINTS, {4,5,17,19,26}          },
                { PYRAMID_POINTS, {17,6,7,19,26}          } }

    },
    {//Pattern9: 2 tetrahedra - 1 pyramid - 2 prism  mask: 11|12|19
         530432,{
                { TETRA_POINTS,   {1,12,0,11}             },
                { TETRA_POINTS,   {5,12,4,19}             },
                { PYRAMID_POINTS, {1,11,19,5,12}          },
                { PRISM_POINTS,   {2,3,7,6,19,11}         },
                { PRISM_POINTS,   {1,11,19,5,2,6}         } }

    },
/*
    {//Pattern9.1: 2 tetrahedra - 1 pyramid - 2 prism mask: 11|15|19 
         559104,{
                { TETRA_POINTS,   {2,3,11,15}             },
                { TETRA_POINTS,   {6,7,15,19}             },
                { PYRAMID_POINTS, {2,11,19,6,15}          },
                { PRISM_POINTS,   {0,1,4,5,19,11}         },
                { PRISM_POINTS,   {1,2,6,19,11}           } }
    },
*/    
    {//Pattern10: 2 tetrahedra - 3 pyramid - 1 prism  //mask: 8|11|19
         526592,{
                { TETRA_POINTS,   {4,5,19,8}              },
                { TETRA_POINTS,   {6,19,8,5}              },
                { PYRAMID_POINTS, {0,11,19,4,8}           },
                { PYRAMID_POINTS, {1,2,6,5,8}             },
                { PYRAMID_POINTS, {2,6,19,11,8}           },
                { PRISM_POINTS,   {6,19,11,2,7,3}         } }

    },
    {//Pattern10.1: 2 tetrahedra - 3 pyramid - 1 prism  //mask: 8|11|19
         527360,{
                { TETRA_POINTS,   {6,7,19,10}              },
                { TETRA_POINTS,   {5,6,10,19}              },
                { PYRAMID_POINTS, {3,11,19,7,10}           },
                { PYRAMID_POINTS, {1,2,6,5,10}             },
                { PYRAMID_POINTS, {1,5,19,11,10}           },
                { PRISM_POINTS,   {0,1,4,5,11,19}         } }

    },
    {//Pattern11: 2 tetrahedra - 4 pyramid - 1 prism //mask:11|12|15|19|24
         17340416,{
                { TETRA_POINTS,   {1,24,12,5}             },
                { TETRA_POINTS,   {6,24,15,2}             },
                { PYRAMID_POINTS, {0,11,24,12,1}          },
                { PYRAMID_POINTS, {11,3,15,24,2}          },
                { PYRAMID_POINTS, {15,7,19,24,6}          },
                { PYRAMID_POINTS, {12,24,19,4,5}          },
                { PRISM_POINTS,   {19,11,2,6,5,1}         } }

    },
    {//Pattern12: 2 hexahedra //mask:9|11|17|19
         657920,{
                { HEXA_POINTS,    {0,1,9,11,4,5,17,19}    },
                { HEXA_POINTS,    {11,9,2,3,19,17,6,7}    } }

    },
    {//Pattern13: 5 tetrahedra - 4 pyramid //mask:11|13|14|19
         550912,{
                { TETRA_POINTS,   {0,11,1,13}             },
                { TETRA_POINTS,   {4,5,19,13}             },
                { TETRA_POINTS,   {6,14,19,7}             },
                { TETRA_POINTS,   {14,3,11,2}             },
                { TETRA_POINTS,   {11,19,14,13}           },
                { PYRAMID_POINTS, {1,2,14,13,2}           },
                { PYRAMID_POINTS, {13,14,6,5,19}          },
                { PYRAMID_POINTS, {11,19,7,3,14}          },
                { PYRAMID_POINTS, {11,19,4,0,13}          } }

    },
    {//Pattern14: 4 prism  mask:8|10|12|15
         38144, {
                { PRISM_POINTS,   {12,15,6,5,8,10}        },
                { PRISM_POINTS,   {8,10,6,5,1,2}          },
                { PRISM_POINTS,   {4,5,6,7,12,15}         },
                { PRISM_POINTS,   {0,3,15,12,8,10}        } }

    },
    {//Pattern15: 5 tetrahedra - 2 pyramid - 1 prism //11|12|13|19
         538624,{
                { TETRA_POINTS,   {13,2,11,6}             },
                { TETRA_POINTS,   {1,2,11,13}             },
                { TETRA_POINTS,   {12,19,11,13}           },
                { TETRA_POINTS,   {5,6,11,19}             },
                { TETRA_POINTS,   {13,6,11,5}             },
                { PYRAMID_POINTS, {0,1,13,12,11}          },
                { PYRAMID_POINTS, {12,13,5,4,19}          },
                { PRISM_POINTS,   {2,11,19,6,7,3}         } }

    },
    {//Pattern16: 2 tetrahedra - 4 pyramis - 2 prism //9|11|12|15|19|24
        17340928,{
                { TETRA_POINTS,   {5,19,6,24}             },
                { TETRA_POINTS,   {5,9,6,24}              },
                { PYRAMID_POINTS, {15,7,19,24,6}          },
                { PYRAMID_POINTS, {4,19,24,12,5}          },
                { PYRAMID_POINTS, {0,11,12,1,5}           },
                { PYRAMID_POINTS, {2,15,24,9,6}           },
                { PRISM_POINTS,   {12,0,11,24,1,9}        },
                { PRISM_POINTS,   {3,15,24,11,2,9}        } }

    },
    {//Pattern17: 6 tetrahedra - 5 pyramid // 8|11|12|15|19|24
          17340672,{
                { TETRA_POINTS,   {5,19,6,24}             },
                { TETRA_POINTS,   {2,15,6,24}             },
                { TETRA_POINTS,   {8,24,5,12}             },
                { TETRA_POINTS,   {8,1,5,24}              },
                { TETRA_POINTS,   {2,11,8,24}             },
                { TETRA_POINTS,   {8,2,1,24}              },
                { PYRAMID_POINTS, {15,7,19,24,6}          },
                { PYRAMID_POINTS, {4,19,24,12,5}          },
                { PYRAMID_POINTS, {15,24,11,3,2}          },
                { PYRAMID_POINTS, {12,24,11,0,8}          },
                { PYRAMID_POINTS, {1,5,6,2,24}            } }

    },
    {    //Pattern18: 4 tetrahedra - 5 pyramid - 1 prism (Added centroid point) mask: 8|11|12|15|19|24
         300288,{
                { TETRA_POINTS,   {4,5,18,12}             },
                { TETRA_POINTS,   {12,8,5,18}             },
                { TETRA_POINTS,   {8,1,5,26}              },
                { TETRA_POINTS,   {5,6,18,26}             },
                { PYRAMID_POINTS, {12,15,7,4,18}          },
                { PYRAMID_POINTS, {8,10,15,12,18}         },
                { PYRAMID_POINTS, {2,10,18,6,26}          },
                { PYRAMID_POINTS, {1,8,10,2,26}           },
                { PYRAMID_POINTS, {1,2,6,5,26}            },
                { PRISM_POINTS,   {8,10,3,0,12,9}         } }

    },
    {//Pattern19: 3 tetrahedra - 4 pyramid - 2 pris mask: 11|12|13|14|15|19|24
         17357312,{
                { TETRA_POINTS,   {9,14,5,24}             },
                { TETRA_POINTS,   {1,24,2,11}             },
                { TETRA_POINTS,   {9,2,14,24}             },
                { PYRAMID_POINTS, {12,24,19,4,5}          },
                { PYRAMID_POINTS, {0,11,24,12,1}          },
                { PYRAMID_POINTS, {1,9,24,12,5}           },
                { PYRAMID_POINTS, {14,24,19,6,5}          },
                { PRISM_POINTS,   {14,15,7,6,19,24}       },
                { PRISM_POINTS,   {2,3,15,14,24,11}       } }

    },
    {//Pattern20: 6 prism mask: 9|11|12|13|14|15|17|19
         17364992,{
                { PRISM_POINTS,   {0,11,24,12,13,1}       },
                { PRISM_POINTS,   {3,15,24,11,2,14}       },
                { PRISM_POINTS,   {12,15,7,6,19,24}       },
                { PRISM_POINTS,   {4,5,13,12,24,19}       },
                { PRISM_POINTS,   {1,2,14,13,11,24}       },
                { PRISM_POINTS,   {5,13,14,6,19,24}       } }

    },
    {//Pattern21: 4 hexahedra
         719360,  {
                { HEXA_POINTS,    {0,1,9,11,12,13,22,24}  },
                { HEXA_POINTS,    {12,13,22,24,4,5,17,19} },
                { HEXA_POINTS,    {11,9,2,3,24,22,14,15}  },
                { HEXA_POINTS,    {24,22,14,15,19,17,6,7} } }

    },
    {//Pattern22: 4 tetrahedra - 3 pyramid
        6144, {
                { TETRA_POINTS,   {1,11,0,12}             },
                { TETRA_POINTS,   {1,12,5,11}             },
                { TETRA_POINTS,   {11,12,7,6}             },
                { TETRA_POINTS,   {11,12,5,6}             },
                { PYRAMID_POINTS, {4,5,6,7,12}            },
                { PYRAMID_POINTS, {2,3,7,6,11}            },
                { PYRAMID_POINTS, {1,2,6,5,11}            } }

    },
    {//Pattern23: 2 tetrahedra - 4 pyramid - 3 prism
         18390784, {
                { TETRA_POINTS,   {5,9,6,20}              },
                { TETRA_POINTS,   {5,19,6,24}             },
                { PYRAMID_POINTS, {12,24,19,4,5}          },
                { PYRAMID_POINTS, {24,15,7,19,6}          },
                { PYRAMID_POINTS, {1,8,20,9,5}            },
                { PYRAMID_POINTS, {9,2,10,20,6}           },
                { PRISM_POINTS,   {0,8,20,11,12,24}       },
                { PRISM_POINTS,   {20,10,3,11,24,13}      },
                { PRISM_POINTS,   {8,10,13,12,6,5}        } }

    },
    {//Pattern24: 3 tetrahedra - 9 pyramid - 3 prism (Added centroid point)
         20496128, {
                { TETRA_POINTS,   {6,20,24,26}            },
                { TETRA_POINTS,   {6,20,21,26}            },
                { TETRA_POINTS,   {6,21,24,26}            },
                { PRISM_POINTS,   {8,1,9,20,21,13}        },
                { PRISM_POINTS,   {21,24,19,16,4,12}      },
                { PRISM_POINTS,   {20,10,3,11,15,24}      },
                { PYRAMID_POINTS, {9,20,10,2,6}           },
                { PYRAMID_POINTS, {9,20,21,13,6}          },
                { PYRAMID_POINTS, {5,16,21,13,6}          },
                { PYRAMID_POINTS, {20,10,15,24,6}         },
                { PYRAMID_POINTS, {24,15,7,19,6}          },
                { PYRAMID_POINTS, {21,24,19,16,6}         },
                { PYRAMID_POINTS, {0,8,20,11,26}          },
                { PYRAMID_POINTS, {0,8,21,12,26}          },
                { PYRAMID_POINTS, {0,11,24,12,26}         } }
    }
};


bool PatternFactory::createPattern(Uint mask) {

    const Element *el = elements;
    Uint SIZE = sizeof(elements)/sizeof(Element);

    pattern.clear();

    for (Uint i=0; i<SIZE; i++) {
        if (el[i].mask == mask) {

            const item *it = el[i].items;
            for(Uint j=0; j<MAX_ELEMENTS; j++) { 
                if (it->size == 0)
                    break;
                pattern.push_back(vector<Uint>(it->points, it->points + it->size));
                it++;
            }

            return true;
        }
    }

    return false;
}

void PatternFactory::deleteInstance () {

    if (m_Instance) {
        delete m_Instance;
        m_Instance = NULL;
    }

}

PatternFactory* PatternFactory::instance() {

    if (!m_Instance) {
        m_Instance = new PatternFactory();
    }
    else
        cout << "INSTANCE ALREADY CREATED" << endl;

    //m_NumInstances++;
    return m_Instance;
}

}

