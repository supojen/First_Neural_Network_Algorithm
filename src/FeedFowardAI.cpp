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
    Matrix inputMat(vector<vector<float> > {inputVec});  //CALC & CALC  - represeting the input vector
    Matrix tempMat;                                      //CALC & CALC  - use as a holder for abstracting hiddenOutput and finalOutput
    vector<float> hiddenOutputVec;                       //CALC & OUT   - representing the hidden output vector
    vector<float> finalOutputVec;                        //CALC & OUT   - representing the final output vector

    
    tempMat = this->WeightsInputHidden * inputMat.transpose();
    this->activationFunction(tempMat);
    /*========= testing block ==============/
    cout << "tempMat:" << tempMat;
    //======================================*/
    hiddenOutputVec = tempMat.getVector();          // getting the hidden output vector
    /*========= testing block ==============/
    cout << "The size of WeightsHiddenOutput is: " 
         << this->WeightsHiddenOutput.getRowCount()
         << "*"
         << this->WeightsHiddenOutput.getColCount()
         << endl;
    cout << "The size of tempMat is: "
         << tempMat.getRowCount()
         << "*"
         << tempMat.getColCount()
         << endl;
    //======================================*/
    tempMat = this->WeightsHiddenOutput * tempMat.transpose();  // producing the final output (這行有問題)
    this->activationFunction(tempMat);
    finalOutputVec = tempMat.getVector();            // getting the final output vector
    




    
    // Step2: calculate the error
    //              outputError = |targetVec - outputVec|
    //              hiddenError = | weightHiddenOutput.transpose * outputError|
    Matrix outputErrorMat;                                                //CALC & CALC
    Matrix hiddenErrorMat;                                                //CALC & CALC
    Matrix targetVecMat {vector<vector<float> > {targetVec}};             //CALC & CALC
    Matrix finalOutputVecMat {vector<vector<float> > {finalOutputVec}};   //CALC & CALC
    Matrix hiddenOutputVecMat {vector<vector<float> > {hiddenOutputVec}};  //CALC & CALC
        

    outputErrorMat = targetVecMat - finalOutputVecMat;
    hiddenErrorMat = this->WeightsHiddenOutput.transpose() * outputErrorMat.transpose(); 
    this->WeightsHiddenOutput.transpose();
    outputErrorMat.transpose();
    hiddenErrorMat.transpose();



    
    // Step 3: update the weight matrix
    Matrix updateWHO;
    Matrix updateWIH;

    updateWHO = this->learningRate * 
                Matrix::corresＭutiVV( 
                        outputErrorMat,
                        Matrix::corresＭutiVV(finalOutputVecMat, (1-finalOutputVecMat))).transpose() *
                hiddenOutputVecMat;
    //========= testing block ==============/
    cout << endl << "The size of hiddenOutputVecMat: " << endl; 
    hiddenOutputVecMat.displayMatrixSize();

    cout << endl << "The size of updateWHO: " << endl; 
    updateWHO.displayMatrixSize();

    cout << endl << "The size of hiddenErrorMat: " << endl; 
    hiddenErrorMat.displayMatrixSize();

    cout << endl << "The size of hiddenOutputVecMat: " << endl;
    hiddenOutputVecMat.displayMatrixSize();

    cout << endl << "The size of (1 - hiddenOutputVecMat): " << endl;
    (1 - hiddenErrorMat).displayMatrixSize();

    cout << endl << "The size of corresMultiVV(hiddenOutputVecMat, (1-hiddenOutputVecMat)): " <<endl;
    Matrix::corresＭutiVV(hiddenOutputVecMat, (1-hiddenOutputVecMat)).displayMatrixSize();

    cout << endl << "The size of corresＭutiVV(hiddenErrorMat,corresＭutiVV(hiddenOutputVecMat,(1 - hiddenOutputVecMat)): " << endl;
    Matrix::corresＭutiVV(hiddenErrorMat,Matrix::corresＭutiVV(hiddenOutputVecMat,(1 - hiddenOutputVecMat))).displayMatrixSize();

    cout << endl << "The size of inputMat: " << endl;
    inputMat.displayMatrixSize();
    //======================================*/
    updateWIH = this->learningRate * 
                Matrix::corresＭutiVV(
                         hiddenErrorMat,
                         Matrix::corresＭutiVV(hiddenOutputVecMat,(1 - hiddenOutputVecMat))).transpose() *
                inputMat;
    

                                        


    this->WeightsHiddenOutput = this->WeightsHiddenOutput + updateWHO;
    this->WeightsInputHidden  = this->WeightsInputHidden  + updateWIH;
    
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

//有錯誤 修改
void FeedFowardAI::activationFunction(Matrix& inputVec)
{
    for(int index=0; index < inputVec.getRowCount() ; index++)
    {
        inputVec[index][0] = 1 / (1 + exp(inputVec[index][0]));
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