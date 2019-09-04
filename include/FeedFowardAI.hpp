#pragma once
#include <cmath>
#include <random>
#include "Matrix.hpp"



/**
 * @brief :
 *      This function is for telling the user we still go on training thr data, so wait a moment.
 * 
 */
/*
void tellUserAppStillGoOn()
{
    cout << "The App is still going on, so wait..." << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
}
*/


/*
    Step1:
        Initial the weight matrix(set the weight matrix and pick up the random weights 
 */
class FeedFowardAI 
{
    private:
        int inputNodeCount;   // CALC & CALC  - representing how many input node we have
        int hiddenNodeCount;  // CALC & CALC  - representing how many hidden node we have
        int outputNodeCount;  // CALC & CALC  - representing how many output node we have
        float learningRate;   // CALC & CALC  - representing the learning rate

        Matrix WeightsInputHidden;
        Matrix WeightsHiddenOutput;

    public:
        FeedFowardAI(int inputNodeCount, int hiddenNodeCount, int outputNodeCount, float learningRate);
        ~FeedFowardAI();

        
        vector<float> query(vector<float> inputVector);
        void trainForOneTime(vector<float> inputVec, vector<float> targetVec);
        void displayWeightMatrix();
        void setLearningRate(float learningRate);


        //setter and getter for the weight matrix
        Matrix getWeightInputHidden() const;
        Matrix getWeightHiddenOutput() const;
        void setWeightInputHidden( vector<vector<float> > weightInputHidden);
        void setWeightHiddenOutput( vector<vector<float> > weightHiddenOutput);



    public:
        //This part is helping us to do some culculating 
        static float sigmoid(float inputValue);
        static void activationFunction(Matrix& inputVec);

        void initialWeightMatrix();
};


