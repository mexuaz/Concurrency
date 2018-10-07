#include "list_util.h"

#include <random>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


void list_util::generate_random_list(const string& filename, vector<int>& list, int low /*= 0*/, int high /*= 1e6*/, uint count /*= 1e6*/) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(low, high);

    ofstream ofile(filename);
    if(!ofile.good()) {
        ostringstream oss;
        oss << "Could not open file " << filename << " for writing!" << endl;
        throw std::runtime_error(oss.str());
    }

    list.clear();

    cout << "Writing list ..." << endl;

    for(uint i = 0; i < count; i++) {
        int val(dist(gen));
        list.push_back(val);
        ofile << val << endl;
    }

    ofile.flush();
    ofile.close();
}


void list_util::read_list(const string& filename, vector<int>& list) {
    ifstream ifile(filename);

    if(!ifile.good()) {
        ostringstream oss;
        oss << "Could not open file " << filename << " for reading!" << endl;
        throw std::runtime_error(oss.str());
    }


    list.clear();

    cout << "Reading list ..." << endl;

    while(!ifile.eof()) {
        string strLine;
        getline(ifile, strLine);
        list.push_back(atoi(strLine.c_str()));
    }


    ifile.close();
}
