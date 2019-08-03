#pragma once
#include <cmath>
#include <random>
#include "Matrix.hpp"


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
        FeedFowardAI();
        ~FeedFowardAI();

        
        void initialWeightMatrix();

    private:
        //This part is helping us to do some culculating 
        static float sigmoid(float inputValue);
};