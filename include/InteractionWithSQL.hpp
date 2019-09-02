#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include "Matrix.hpp"
#include "FeedFowardAI.hpp"



class InteractionWithSQL{

    private:
        string connectionString;
        pqxx::connection *con;
        pqxx::work *wrk;

    public: 
        InteractionWithSQL();
        ~InteractionWithSQL();

    private:
        /********************************************************
         *  Helper function for connecting to data base
        ********************************************************/
        static string getConnectionString();

        /********************************************************
         *  Helper function for inserting the data into data base
        ********************************************************/
        static string getArrayString(Matrix weightMat);
        static string getInsertString(string inputHiddenArrStr,string hiddenOutputArrStr);

        /********************************************************
         *  Helper function for deserialization of the ai
        ********************************************************/
        vector<float> retriveWeightsDataFromString(string sqlOutputString);

    public:
        void storeWeightMatIntoDB(FeedFowardAI &ai);
        void deserializeAI(FeedFowardAI &ai,
                           int inputs_node_count, 
                           int hidden_node_count,
                           int output_node_count);
        
};






