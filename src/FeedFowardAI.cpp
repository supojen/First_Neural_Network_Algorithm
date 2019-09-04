#include "FeedFowardAI.hpp"

FeedFowardAI::FeedFowardAI(int inputNodeCount, int hiddenNodeCount, int outputNodeCount, float learningRate)
{
    this->inputNodeCount = inputNodeCount;
    this->hiddenNodeCount = hiddenNodeCount;
    this->outputNodeCount = outputNodeCount;
    setLearningRate(learningRate);
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


// This function need to be tested
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


//This function need to be tested
//*********************************************************************************
void FeedFowardAI::trainForOneTime(vector<float> inputVec, vector<float> targetVec)
{
    // Step1: calculate the output vector(Both finalOutput and hiddenOutput)
    //        and setting up them to matrix object.
    Matrix inputMat(vector<vector<float> > {inputVec});  //IN   & CALC  - represeting the input vector
    Matrix tempMat;                                      //CALC & CALC  - use as a holder for abstracting hiddenOutput and finalOutput
    vector<float> hiddenOutputVec;                       //CALC & OUT   - representing the hidden output vector
    vector<float> finalOutputVec;                        //CALC & OUT   - representing the final output vector
    Matrix finalOutputVecMat;                            //CALC & CALC
    Matrix hiddenOutputVecMat;                           //CALC & CALC

    // INPUT
    // Transpose the input into an col vector
    inputMat.transpose();
    

    
    // CALC
    tempMat = this->WeightsInputHidden * inputMat;
    /********* testing block ***************
    cout << "WeightsInputHidden" << endl << this->WeightsInputHidden;
    cout << "InputMat"           << endl << inputMat;
    cout << "tempMat"            << endl << tempMat;

    ***************************************/
    this->activationFunction(tempMat);
    hiddenOutputVec = tempMat.getVector();          // getting the hidden output vector
    //tempMat = this->WeightsHiddenOutput * tempMat;  // producing the final output (這行有問題)
    //this->activationFunction(tempMat);
    //finalOutputVec = tempMat.getVector();            // getting the final output vector 
    /********* testing block ***************
    cout << endl << "The size of WeightsInputHidden:" << endl;
    this->WeightsInputHidden.displayMatrixSize();
    cout << endl << "The size of inputMat:" << endl;
    inputMat.displayMatrixSize();
    cout << endl  << "The size of tempMat:" << endl;
    tempMat.displayMatrixSize();
    ***************************************/

    /*
    // OUTPUT
    finalOutputVecMat.setMatrix(vector<vector<float> > {finalOutputVec});
    finalOutputVecMat.transpose();
    hiddenOutputVecMat.setMatrix(vector<vector<float> > {hiddenOutputVec});
    hiddenOutputVecMat.transpose();
    */

    
    /*
    // Step2: calculate the error
    //              outputError = |targetVec - outputVec|
    //              hiddenError = | weightHiddenOutput.transpose * outputError|
    Matrix outputErrorMat;                                                //CALC & CALC
    Matrix hiddenErrorMat;                                                //CALC & CALC
    Matrix targetVecMat {vector<vector<float> > {targetVec}};             //CALC & CALC
        
    // INPUT 
    targetVecMat.transpose();

    // CALC
    // CALC the final error, E = T - O
    outputErrorMat = targetVecMat - finalOutputVecMat;
    // CALC the hidden error, E = HiddenOutputmatrix * FinalErrorMatrix
    hiddenErrorMat = this->WeightsHiddenOutput.transpose() * outputErrorMat; 

    // OUTPUT
    // After calculating, reset the WeightHiddenOutput to the initial position(Transpose to the initial situation)
    this->WeightsHiddenOutput.transpose();
    */

    /********* testing block ***************
    cout << "The size of outputErrorMat:" << endl;
    outputErrorMat.displayMatrixSize();
    ***************************************/



    /*
    // Step 3: calculate the value for weight change
    Matrix updateWHO;
    Matrix updateWIH;

    updateWHO = this->learningRate * 
                outputErrorMat * 
                finalOutputVecMat * 
                ( 1 - finalOutputVecMat ) * 
                hiddenOutputVecMat.transpose();

    updateWIH = this->learningRate *
                hiddenErrorMat *
                hiddenOutputVecMat *
                ( 1 - hiddenOutputVecMat ) * 
                inputMat.transpose();

                                        

    // Step 4 : update the weights
    this->WeightsHiddenOutput = this->WeightsHiddenOutput + updateWHO;
    this->WeightsInputHidden  = this->WeightsInputHidden  + updateWIH;
    */
}



void FeedFowardAI::setLearningRate(float learningRate)
{
    this->learningRate = learningRate;
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



void FeedFowardAI::activationFunction(Matrix& mat)
{
    for(int rowIndex = 0; rowIndex < mat.getRowCount(); rowIndex++)
    {
        for(auto &element : mat[rowIndex])
        {
            element = sigmoid(element);
        }
    }
}




Matrix FeedFowardAI::getWeightInputHidden() const
{
    return this->WeightsInputHidden;
}

Matrix FeedFowardAI::getWeightHiddenOutput() const
{
    return this->WeightsHiddenOutput;
}

void FeedFowardAI::setWeightInputHidden( vector<vector<float> > weightInputHidden)
{
    this->WeightsInputHidden = weightInputHidden;
}


void FeedFowardAI::setWeightHiddenOutput( vector<vector<float> > weightHiddenOutput)
{
    this->WeightsHiddenOutput = weightHiddenOutput;
}