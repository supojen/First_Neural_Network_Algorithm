#include "FeedFowardAI.hpp"

FeedFowardAI::FeedFowardAI() {

}

FeedFowardAI::~FeedFowardAI() {

}

void FeedFowardAI::initialWeightMatrix()
{
    //Set the weight matrix size
    this->WeightsInputHidden.setMatrixSize(this->hiddenNodeCount, this->inputNodeCount);
    this->WeightsHiddenOutput.setMatrixSize(this->outputNodeCount, this->hiddenNodeCount);

    
}

float FeedFowardAI::sigmoid(float inputValue)
{
    return 1 / (1 + exp(-inputValue));
}