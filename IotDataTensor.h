#ifndef IOTDATATENSOR_H
#define IOTDATATENSOR_H

#include "RankOneTensorType.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class IotDataTensor final : public RankOneTensorType<std::string> {
    private:
        std::vector<std::string> iot_category;
        std::vector<RankOneTensorType<std::string>> iot_data;

    public:
        IotDataTensor() { //default constructor resizes both tensors to 0 (empty)
            iot_category.resize(0);
            iot_data.resize(0);
        }

        double getValue(int row, int col) {
            if (row < 0 || row >= static_cast<int>(iot_data.size())) //use static cast to get proper index instead of size_t
                throw std::out_of_range("Row index is out of range!");
            
            if (col < 0 || col >= static_cast<int>(iot_category.size()))
                throw std::out_of_range("Column index is out of range!");

            //convert string at location [row][col] to double using .stoi() or static_cast
            return std::stod(iot_data[row][col]);
        }

        std::string getCategory(int col) { //simple getter for the iot_category vector
            return iot_category[col];
        }

        virtual void loadData() override { //function would be programmed differently if shard wasn't the only one and given.
            std::string fileLocation = "iot-shard.txt"; //I understood we needed to use the shard instead of 
            //RT_IOT2022 (I may be wrong, apologies if so).
            std::ifstream inputFile(fileLocation);

            if (!inputFile) {
                std::string error_message = fileLocation + " was not opened properly!";
                throw std::runtime_error(error_message);
            }

            iot_category.clear();
            iot_data.clear();

            std::string line;
            getline(inputFile, line);

            std::stringstream metadataString(line);
            int num_of_categories(0);
            std::string token;
            
            while (getline(metadataString, token, ',')) {
                iot_category.push_back(token); //does this work, or should I make a copy?
            }

            num_of_categories = iot_category.size();


            while (getline(inputFile, line)) {
                RankOneTensorType<std::string> row(num_of_categories);

                std::stringstream rowStream(line);
                int col = 0;

                while ((getline(rowStream, token, ',')) && col < num_of_categories) {
                    row[col] = token;
                    ++col;
                }

                if (col != num_of_categories) {
                    throw std::runtime_error("Row has too many columns!");
                }

                iot_data.push_back(row);
            }
        }

};


#endif