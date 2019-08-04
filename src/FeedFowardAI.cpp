#include "FeedFowardAI.hpp"

FeedFowardAI::FeedFowardAI(int inputNodeCount, int hiddenNodeCount, int outputNodeCount)
{
    this->inputNodeCount = inputNodeCount;
    this->hiddenNodeCount = hiddenNodeCount;
    this->outputNodeCount = outputNodeCount;
    initialWeightMatrix();
}


//*********************************************************************************
FeedFowardAI::~FeedFowardAI() {

}



//*********************************************************************************
void FeedFowardAI::initialWeightMatrix()
{
    default_random_engine seed;
    normal_distribution<float> GeneratorIH(0.0, pow(this->inputNodeCount,-0.5));
    normal_distribution<float> GeneratorHO(0.0, pow(this->hiddenNodeCount,-0.5));

    //Set the weight matrix size
    this->WeightsInputHidden.setMatrixSize(this->hiddenNodeCount, this->inputNodeCount);
    this->WeightsHiddenOutput.setMatrixSize(this->outputNodeCount, this->hiddenNodeCount);

    
    //generate random value for WeightsInputHidden
    for(int rowIndex = 0; rowIndex < this->hiddenNodeCount; rowIndex++)
    {
        for(int colIndex = 0; colIndex < this->inputNodeCount; colIndex++)
        {
            this->WeightsInputHidden[rowIndex][colIndex] = GeneratorIH(seed);
        }
    }
    
    //generate random value for WeightsHiddenOutput
    for(int rowIndex = 0; rowIndex < this->outputNodeCount; rowIndex++)
    {
        for(int colIndex = 0; colIndex < this->hiddenNodeCount; colIndex++)
        {
            this->WeightsHiddenOutput[rowIndex][colIndex] = GeneratorHO(seed);
        }
    }
    

}



//*********************************************************************************
vector<float> FeedFowardAI::query(vector<float> inputVector)
{
    Matrix outputMatrix;
    Matrix inputMatrix(vector<vector<float> > {inputVector});

    
    outputMatrix = this->WeightsInputHidden * inputMatrix.transpose();
    this->activationFunction(outputMatrix);
    outputMatrix = this->WeightsHiddenOutput * outputMatrix;
    this->activationFunction(outputMatrix);


    return outputMatrix.getVector();
}


//修改當中
//*********************************************************************************
void FeedFowardAI::trainForOneTime(vector<float> inputVec, vector<float> targetVec)
{
    // Step1: calculate the output vector(Both finalOutput and hiddenOutput)
    Matrix inputMat(vector<vector<float> > {inputVec});  //CALC & CALC  - represeting the input vector
    Matrix outputMat;                                    //CALC & CALC  - use as a holder for abstracting hiddenOutput and finalOutput
    vector<float> hiddenOutputVec;                       //CALC & OUT   - representing the hidden output vector
    vector<float> finalOutputVec;                        //CALC & OUT   - representing the final output vector

    outputMat = this->WeightsInputHidden * inputMat.transpose();
    this->activationFunction(outputMat);
    hiddenOutputVec = outputMat.getVector();
    outputMat = this->WeightsHiddenOutput * outputMat;
    this->activationFunction(outputMat);
    finalOutputVec = outputMat.getVector();
    
    
    // Step2: calculate the error
    //              outputError = |targetVec - outputVec|
    //              hiddenError = | weightHiddenOutput.transpose * outputError|
    Matrix outputErrorMat;
    Matrix hiddenErrorMat;
    



    

}





//*********************************************************************************
void FeedFowardAI::displayWeightMatrix()
{
    cout << "WeightsInputHidden" << endl;
    cout << this->WeightsInputHidden;
    cout << "WeightsHiddenOutput" << endl;
    cout << this->WeightsHiddenOutput;
}



float FeedFowardAI::sigmoid(float inputValue)
{
    return 1 / (1 + exp(-inputValue));
}

//有錯誤 修改
void FeedFowardAI::activationFunction(Matrix& inputVec)
{
    for(int index=0; index < inputVec.getRowCount() ; index++)
    {
        inputVec[index][0] = 1 / (1 + exp(inputVec[index][0]));
    }
}