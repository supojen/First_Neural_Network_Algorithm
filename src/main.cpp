#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "Matrix.hpp"
#include "FeedFowardAI.hpp"
#include "InteractionWithSQL.hpp"
using namespace std;



/**
 * @brief :
 *      This function retrieve the expect output and the data input from the stringstream.
 *      
 * 
 * @param strLineStream :
 *          This is the string stream that contained the data ew want to retrieved
 * @param expOutput :
 *          This function get the expect output and store it in this variable.
 * @param inputs :
 *          This function get the inputs data and store it in this variable.
 */
void readDataFromCsv(stringstream &strLineStream,int &expOutput,vector<float> &inputs);



//***************** main *********************************
int main() 
{
    
    FeedFowardAI ai(784,100,10,0.3);
    InteractionWithSQL database;
    

    Matrix m1 { vector<vector<float> > { {1,2,3} } };
    Matrix m2 { vector<vector<float> > { {1},{2},{3} } };
    Matrix m3 = Matrix::corresＭutiVV(m1, m2);
    vector<float> vec = m3.getVector();
    cout << "corresMutiVV" << endl;
    for(auto &value : vec)
    {
        cout << value << ",";
    }
    cout << endl;


    /*
    database.deserializeAI(ai,3,3,3);
    cout << "========= Input Hidden Weight Mat =========" << endl;
    cout << ai.getWeightInputHidden();
    cout << "========= Hidden Output Weight Mat =========" << endl;
    cout << ai.getWeightHiddenOutput();
    */
    
    



    
    //train the AI
    fstream trainFile("mnist_train_100.csv");
    string strLine;          
    int expOutput;
    vector<float> inputs;
    
    
    while(trainFile.good())
    {
        getline(trainFile,strLine);
        stringstream strStream(strLine);
        vector<float> outputVec(10,0.0);
        
        
        readDataFromCsv(strStream, expOutput, inputs);
        //========= testing block ==============/
        cout << "The expect output:" << expOutput << endl;
        //======================================/
        outputVec[expOutput] = 1.0;
        ai.trainForOneTime(inputs, outputVec);
        

        inputs.clear();
    }
    trainFile.close();


    database.storeWeightMatIntoDB(ai);
    
    
    
    //use the AI
    fstream testFile("mnist_test_10.csv");


    while(testFile.good())
    {
        vector<float> answerVec(10,0.0);
        stringstream answerStrStream;
        int outputValue = -1;

        getline(testFile, strLine);
        answerStrStream.str(strLine);
        
        
        readDataFromCsv(answerStrStream, expOutput, inputs);
        
        answerVec = ai.query(inputs);


        
        int index = 0;
        auto maxOutputNode = max_element(answerVec.begin(), answerVec.end());
        for(auto iter = answerVec.begin() ; iter < answerVec.end(); iter++)
        {
            if(iter == maxOutputNode)
                outputValue = index;
            index++;
        }
        
        cout << "output value is " << outputValue << endl;

        inputs.clear();
        
    }
    
    
    

    
    
    return 0;

}
//********************************************************







void readDataFromCsv(stringstream &strLineStream,int &expOutput,vector<float> &inputs)
{
    string valueStr;   // CALC & CALC  -  This is an value holder for holding the value we extracted

    while(strLineStream.good())
    {
        getline(strLineStream, valueStr, ',');
        inputs.push_back(stof(valueStr));
    }

    expOutput = inputs[0];
    inputs.erase(inputs.begin());
}