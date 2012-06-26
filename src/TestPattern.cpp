#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include "CubePatterns.h"


using namespace patterns;
using namespace std;

void getNodesFromFile(string, vector<int> & , vector<int> & ); 

int main (int argc, char *argv[])
{
    string filename;

    if(argc != 3) {
      cout << "Usage:" << endl;
      cout << argv[0] << "-f Filename" << endl;
      return 1;
    }
   
    if(strcmp(argv[1], "-f") == 0) {
        filename = argv[2];
    }

    vector<int> nodes;
    vector<int> edges;

    getNodesFromFile(filename,nodes,edges);


    CubePatterns *pattern = new CubePatterns(nodes, edges);

    pattern->rotate();

    vector< vector<Uint> > result;
    pattern->vectors(result);

//    for (vector< vector<Uint> >::iterator it = result.begin(); it != result.end(); ++it) {
//        for (vector<Uint>::iterator it1=(*it).begin(); it1=(*it).end(); ++it1) {
//        //    cout << " " << (*it1) ;
//        }
//        cout << endl;
//    }

for (vector< vector<Uint> >::iterator it=result.begin(); it != result.end() ; ++it) {
    for (vector<Uint>::iterator it1=(*it).begin(); it1 != (*it).end(); ++it1) {
        cout << (*it1) << endl;
    }
}



    delete pattern;

    return 0;
}




void getNodesFromFile(string name, vector<int> & _cp, vector<int> & _ep) {

    ifstream file;
    string line;

    //file.open ("patterns.txt");
    file.open (name.c_str());

    if (file.is_open()) {
        while(!file.eof()) {
            getline (file,line);
            
            int pos = line.find(" ");

            if ( pos  != string::npos)  {

                string cp = line.substr(0,pos);
                string ep = line.substr(pos+1);

                int num;

                while ((pos = cp.find("," )) != string::npos ) {

                    istringstream(cp.substr(0,pos)) >> num ;
                    _cp.push_back(num);

                    cp = cp.substr(pos+1);

                    if ( ( cp.find(",") == string::npos ) && ( cp.size() > 0 ) ) {

                        istringstream(cp) >> num ;
                        _cp.push_back(num);

                    }
                }

                while ((pos = ep.find("," )) != string::npos ) {

                    istringstream(ep.substr(0,pos)) >> num ;
                    _ep.push_back(num);

                    ep = ep.substr(pos+1);

                    if ( ( ep.find(",") == string::npos ) && ( ep.size() > 0 ) ) {

                        istringstream(ep) >> num ;
                        _ep.push_back(num);

                    }
                }
            }
        }
    }
    else {

        cout << "File not found ..." << endl;
        exit(0);

    }

    file.close();
}
