

#include <iostream>
#include <string>
#include <array>
#include <thread>

using namespace std;

int main(int argc, char** argv) {

    std::string pr(argv[0]);
    pr.erase(0, pr.find_last_of('/')+1);

    cout << "The Barbershop Problem " << endl
         << "Required at least C++17 "
         << "Your C++ version is " << __cplusplus << endl
         << "Implemented by Amir Mehrafsa (mehrafsa@live.com)" << endl
         << "Usage :" << endl
         << pr << endl;





    return 0;
}
