#ifndef BASETENSOR_H
#define BASETENSOR_H

#include <vector>
#include <random>

template <typename T>
class BaseTensor {
	private:
		std::vector<T> data; //One dimensional tensor accepting any data_type as input.

	public:
		virtual void loadData() = 0; //Load data is overriden based on dimensionality, and specific data type of tensor.

		double valueGen() { //simple value generator (serves as a test for load data in the assignment).
			std::random_device rd;
			std::mt19937 mt(rd());

			// Create a uniform distribution between 0 and 1
			std::uniform_real_distribution<double> dist(0.0, 1.0);

			// Generate and print a random double value
			double randomValue = dist(mt);
			return randomValue;
		}
};

#endif