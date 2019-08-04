#include <iostream>
#include <cmath>
#include "Matrix.hpp"
#include "FeedFowardAI.hpp"
using namespace std;



int main() 
{
    /* 
    FeedFowardAI ai(3,3,3);

    ai.displayWeightMatrix();


    cout << endl << "++++++++++ Query the Neural Network ++++++++++" << endl;
    cout << fixed << setprecision(3);
    vector<float> outputVec = ai.query(vector<float> {0.1 , 0.2 , 0.3});
    for(auto &item : outputVec)
        cout << left << setw(10) << item;
    cout << endl;


    for(auto &item : ai.query(vector<float> {0.5 , 0.1 , 0.3}))
        cout << left << setw(10) << item;
    cout << endl;
    */



   
    Matrix mat(vector<vector<float> >
              {
                 vector<float>{1,2,3},
                 vector<float>{1,2,3},
                 vector<float>{1,2,3}
              });
    
    Matrix vec(vector<vector<float> >
              {
                 vector<float>{0,2,3},
              });
   
    cout << vec.transpose();
    cout << vec;
    cout << vec.transpose();
    cout << vec;



    return 0;
    
}