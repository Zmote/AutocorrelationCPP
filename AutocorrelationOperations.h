#ifndef AUTOCORRELATIONOPERATIONS_H_
#define AUTOCORRELATIONOPERATIONS_H_

#include <vector>

namespace Autocorrelation {
namespace AutocorrelationOperations {

using vec_matrix = std::vector<std::vector<char>>;

int calculate_correlations(std::vector<char> & original, std::vector<char> & compare) {
	int sum { 0 };
	for (unsigned int i = 0; i < original.size(); i++) {
		if (original[i] == compare[i]) {
			++sum;
		}
	}
	return sum;
}

std::vector<int> calculate_autocorrelation(vec_matrix matrix) {
	std::vector<char> & originalInput = matrix.at(0);
	std::vector<int> autocorellations { };
	for (unsigned int i = 0; i < matrix.size(); i++) {
		autocorellations.push_back(calculate_correlations(originalInput, matrix.at(i)));
	}
	return autocorellations;
}

vec_matrix calculate_autocorrelation_matrix(std::string input_string) {
	int is_length = input_string.size();
	vec_matrix matrix { };
	for (int i = 0; i < is_length; i++) {
		std::string iteration_string { input_string };
		iteration_string.insert(0, i, ' ');
		std::vector<char> row { };
		for (unsigned int j = 0; j < input_string.size(); j++) {
			row.push_back(iteration_string[j]);
		}
		matrix.push_back(row);
	}
	return matrix;
}

vec_matrix calculate_word_matrix(std::string input_string) {
	int is_length = input_string.size();
	vec_matrix matrix { };
	for (int i = 0; i < is_length; i++) {
		std::vector<char> row { };
		for (int j = 0; j < is_length; j++) {
			row.push_back(input_string[(i + j) % is_length]);
		}
		matrix.push_back(row);
	}
	return matrix;
}

}
}

#endif /* AUTOCORRELATIONOPERATIONS_H_ */
