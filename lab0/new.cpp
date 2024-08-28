#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    
    vector<int> vec = { 4, 2, 4, 6, 7 };

    vector<int>::iterator it;

    for (it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }

    return 0;
}