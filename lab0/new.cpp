#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    
    vector<int> vec;

    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(4);

    vector<int>::iterator it;

    for (it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    return 0;
}