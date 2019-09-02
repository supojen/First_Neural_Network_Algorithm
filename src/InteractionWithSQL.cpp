#include "InteractionWithSQL.hpp"






InteractionWithSQL::InteractionWithSQL()
{

    connectionString = getConnectionString();
    con = new pqxx::connection {connectionString.c_str()};
    wrk = new pqxx::work {*con};

}


InteractionWithSQL::~InteractionWithSQL()
{
    delete con;
    delete wrk;
}


/**
 * @brief : 
 *      This function get an weight matrix, and than produce an array string.
 * 
 * @param weightMat :
 *      Representing an weight matrix.
 * 
 * @return string :
 *      An array string about the weight matrix.
 */
string InteractionWithSQL::getArrayString(Matrix weightMat)
{
    string sqlString;   // CALC & Out - this is the array which will stored in the database 's string
    sqlString += "ARRAY[";

    for(auto rowIndex = 0; rowIndex < weightMat.getRowCount(); rowIndex++)
    {
        for(auto colIndex = 0; colIndex < weightMat.getColCount(); colIndex++)
        {
            sqlString += to_string(weightMat.getMatrixValue()[rowIndex][colIndex]);

            if(!(
                   rowIndex == (weightMat.getRowCount() - 1) && 
                   colIndex == (weightMat.getColCount() - 1) 
              ))
              {
                  sqlString += ",";
              }
                
        }   
    }

    sqlString += "]";

    return sqlString;
}


/**
 * @brief :
 *      This function get two array string about the inputHiddenWeight matrix and 
 *      hiddenOutputWeight matrix, and use the two string to prduce the insert statement.
 *      (Insert an data into weight_matrix data base)
 * 
 * @param inputHiddenArrStr :
 *      Representing the string of input hidden weight matrix.
 * 
 * @param hiddenOutputArrStr 
 *      representing the string of hidden output weight matrix.
 * 
 * @return string 
 *      An insert statement for inserting data wo weight_matrix data base.
 * 
 */
string InteractionWithSQL::getInsertString(string inputHiddenArrStr,string hiddenOutputArrStr)
{
    string sqlString;
    sqlString += "INSERT INTO weight_matrix (input_hidden, hidden_output) values (";
    sqlString += "";
    sqlString += inputHiddenArrStr;
    sqlString += ",";
    sqlString += hiddenOutputArrStr;
    sqlString += ");";

    return sqlString;
}


/**
 * @brief :
 *      This function is for storing the weights of the AI to the database(weight_matrix).
 * 
 * @param wrk :
 *      An poxx::work object, this object is used to run the spl script.
 * 
 * @param ai 
 *      An AI object, this is the ai that we wnat to store it's weights.
 * 
 */
void InteractionWithSQL::storeWeightMatIntoDB(FeedFowardAI &ai)
{
    string arrayStrInputHidden;
    string arrayStrHiddenOutput;
    string insertStatement;

    arrayStrInputHidden  += getArrayString(ai.getWeightInputHidden());
    arrayStrHiddenOutput += getArrayString(ai.getWeightHiddenOutput());
    insertStatement      += getInsertString(arrayStrInputHidden, arrayStrHiddenOutput); 

    
    wrk->exec("delete from weight_matrix;");
    wrk->exec(insertStatement);
    wrk->commit();
    

}


/*****************************************************************************
 * DESCRIPTION:
 *      This is an function that will help us to read the connection string 
 *      from the file named connectionString.txt
 * OUTPUT:
 *      string :The connection string
*****************************************************************************/
string InteractionWithSQL::getConnectionString()
{
    string connectionString;
    //open the connection string file
    fstream connectionStringFile("connectionString.txt", ios::in );
    if(connectionStringFile.bad())
    {
        cerr << "Fail to open the file." << endl;
    }
    //reading the connection string from connection string file
    getline(connectionStringFile,connectionString);
    
    //close the connection string file
    connectionStringFile.close();

    return connectionString;
}

//正在測試這個 function
void InteractionWithSQL::deserializeAI(FeedFowardAI &ai,
                                                         int inputs_node_count, 
                                                         int hidden_node_count,
                                                         int output_node_count)
{
    pqxx::result res;
    vector<vector<float> > inputHiddenWeightMat;  // hidden_node_count * input_node_count
    vector<vector<float> > hiddenoutputWeightMat; // output_node_count * hidden_node_count
    vector<float> weightsFromSQL;
    int indexForWeightsFromSQL;

    // Step 1 : Getting the input hidden weight matrix
    // Get the weights data from data base
    res = this->wrk->exec("select input_hidden from weight_matrix;");
    weightsFromSQL = retriveWeightsDataFromString(res[0][0].as<string>());

    

    indexForWeightsFromSQL = 0;
    for(int rowCount = 0; rowCount < hidden_node_count; rowCount++)
    {
        vector<float> row;
        for(int colCount = 0; colCount < inputs_node_count; colCount++)
        {
            row.push_back(weightsFromSQL[indexForWeightsFromSQL]);
            indexForWeightsFromSQL++;
        }// Store the weight into the row

        inputHiddenWeightMat.push_back(row);

    }// Store the row to the input hidden weight matrix


    
    // Step 2 : Getting the hidden output weight matrix
    // Get the weights data from data base
    res = this->wrk->exec("select hidden_output from weight_matrix;");
    weightsFromSQL = retriveWeightsDataFromString(res[0][0].as<string>());

    indexForWeightsFromSQL = 0;
    for(int rowCount = 0; rowCount < output_node_count; rowCount++)
    {
        vector<float> row;
        for(int colCount = 0; colCount < hidden_node_count; colCount++)
        {
            row.push_back(weightsFromSQL[indexForWeightsFromSQL]);
            indexForWeightsFromSQL++;
        }// Store the weight into the row

        hiddenoutputWeightMat.push_back(row);

    }// Store the row to the input hidden weight matrix

    

    // Step 3 : Deserialize the AI
    ai.setWeightInputHidden(inputHiddenWeightMat);
    ai.setWeightHiddenOutput(hiddenoutputWeightMat);

}



vector<float> InteractionWithSQL::retriveWeightsDataFromString(string sqlOutputString)
{
    stringstream strStream;
    strStream.str(sqlOutputString);
    vector<string> weightStrings;
    vector<string>::iterator iterWStr;
    vector<float> weights;
    

    //splitting the string with demli ','
    while(strStream.good())
    {
        string weightString;
        getline(strStream, weightString, ',');
        weightStrings.push_back(weightString);
    }
    strStream.flush();
     
    //erase the '{' character from the first element of weight string
    iterWStr = weightStrings.begin();
    iterWStr->erase(iterWStr->begin());

    //erase the '}' character from the last element of weight string
    iterWStr = weightStrings.end()-1;
    iterWStr->erase(iterWStr->end()-1);


    // Converting the string to the float
    for(auto &weightString : weightStrings)
    {
        weights.push_back(stof(weightString));
    }



    return weights;

}