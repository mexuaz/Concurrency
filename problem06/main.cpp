#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <experimental/execution>
#include <experimental/barrier>

using namespace std;


void generate_random_list(const string& filename, vector<int>& list, int low = 0, int high = 1e6, uint count = 1e6) {
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


void read_list(const string& filename, vector<int>& list) {
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

int main(int argc, char** argv)
{



    const string arg1 = "--generate-and-use-list";
    const string arg2 = "--use-list";

    if(argc < 3 || !(argv[1] == arg1 || argv[1] == arg2)) {
        cout << "C++ version: "
             << __cplusplus << endl;
        cout << "Usage: " << endl
             << "program " << arg1 << " [filename] " << endl
             << " or " << endl
             << "program " << arg2 << " [filename] " << endl;
    }

    vector<int> list;

    if(argv[1] == arg1) {
        generate_random_list(argv[2], list);
    } else if(argv[1] == arg2){
        read_list(argv[2], list);
    }


    /****
     * start sorting
     */





    auto wcts = std::chrono::system_clock::now();

    //sort(std::seq, list.begin(), list.end());

    std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);
    std::cout << "Finished in " << wctduration.count() << " seconds" << std::endl;



    return 0;
}
