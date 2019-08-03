#include <iostream>
#include "Matrix.hpp"

int main() {
    

    vector<vector<float> > vec1;
    vec1.push_back({0,1,0});

    Matrix m1(vec1);
    cout << m1;

    vector<vector<float> > vec2;
    vec2.push_back({1});
    vec2.push_back({2});
    vec2.push_back({3});
    Matrix m2(vec2);
    cout << m2;

    cout << "--- m2 * m1 ---" << endl;
    cout << m1 * m2;





    return 0;
    
}