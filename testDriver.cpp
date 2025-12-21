#include "IotDataTensor.h"
#include <iostream>

using namespace std;


void testIotDataTensor() {
    IotDataTensor iot;
    try {
        iot.loadData();
        int row = 0;
        int col = 5;
        cout << iot.getCategory(col) << " : " << iot.getValue(row, col); //expected output: flow_duration & 32.011598
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
}

int main() {
    testIotDataTensor();
    return 0;
}



