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


vector<string> rows;

void print_out(const vector<Uint>& , const vector<Uint>& , const vector< vector<Uint> >&);
void read_file(string);
void get_nodes(vector<Uint> & , vector<Uint> & ); 


int main (int argc, char *argv[])
{

    if(argc != 3) {
      cout << endl << "Usage:" << endl;
      cout << argv[0] << " -f Filename" << endl << endl;
      return 1;
    }
   
    string filename;
    if(strcmp(argv[1], "-f") == 0) {
        filename = argv[2];
    }

    read_file(filename);


    while(rows.size() > 0 ) {

        vector<Uint> nodes;
        vector<Uint> edges;
        vector< vector<Uint> > result;

        get_nodes(nodes,edges);

        CubePatterns *pattern = new CubePatterns(nodes, edges);
    
        pattern->search();
    
        pattern->vectors(result);
    
        print_out(nodes,edges,result);
    
        delete pattern;
    }

    return 0;
}

void print_out(const vector<Uint>& cp,
        const vector<Uint>& ep, 
        const vector< vector<Uint> >& res) {

    cout << "Hexahedron: " ;
    if ( cp.size() > 0 ) {
        for (int i=0; i<8; i++)
            cout << cp[i] << " ";
    }

    int size = cp.size() - 8;
    if( ep.size() > 0 ) {
       for (int i=0; i<size; i++)
           cout << cp[i+8] << "(" << ep[i] << ") ";
    }

    cout << endl;

    if( res.size() > 0 ){

        for (vector< vector<Uint> >::const_iterator it=res.begin(); it != res.end() ; ++it) {
            if      ( (*it).size() == 4) cout << " tetra ";
            else if ( (*it).size() == 5) cout << " pyram ";
            else if ( (*it).size() == 6) cout << " prism ";
            else if ( (*it).size() == 8) cout << " hexa  ";
            for (vector<Uint>::const_iterator it1=(*it).begin(); it1 != (*it).end(); ++it1) {
    
                cout << (*it1) << " ";
            }
            cout << endl;
        }

    }
    else
        cout << "Pattern not found !! " << endl;
}

void read_file(string name) {

    ifstream file;
    string line;

    file.open (name.c_str());

    if (file.is_open()) {
        while(!file.eof()) {

            getline (file,line);

            if ((line.find("#") == string::npos) && (!line.empty())){ 

                rows.push_back(line);

            }
        }
    }
    else {

        cout << "File " << name << " not found ..." << endl;
        exit(1);

    }

    file.close();
}

void get_nodes(vector<Uint> & _cp, vector<Uint> & _ep) {

    vector<string>::iterator it = rows.begin();
    string line(*it);
    rows.erase(it);
    
    int pos = line.find(" ");

    if ( pos  != string::npos)  {

        string cp = line.substr(0,pos);
        string ep = line.substr(pos+1);

        int num;

        while ((pos = cp.find("," )) != string::npos ) {

            istringstream(cp.substr(0,pos)) >> num ;
            _cp.push_back(num);

            cp = cp.substr(pos+1);

        }
        if ( cp.size() > 0 ) {

            istringstream(cp) >> num ;
            _cp.push_back(num);

        }

        while ((pos = ep.find("," )) != string::npos ) {

            istringstream(ep.substr(0,pos)) >> num ;
            _ep.push_back(num);

            ep = ep.substr(pos+1);

//            if ( ( ep.find(",") == string::npos ) && ( ep.size() > 0 ) ) {
//
//                istringstream(ep) >> num ;
//                _ep.push_back(num);
//
//            }
        }
        if (  ep.size() > 0  ) {

            istringstream(ep) >> num ;
            _ep.push_back(num);

        }



    }
}



