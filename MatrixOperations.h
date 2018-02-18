#ifndef MATRIXOPERATIONS_H_
#define MATRIXOPERATIONS_H_

namespace Autocorrelation {
namespace MatrixOperations{

vec_matrix transform_matrix(vec_matrix & matrix) {
	vec_matrix transformedMatrix { matrix };
	for (unsigned int i = 0; i < matrix.size(); i++) {
		for (unsigned int j = 0; j < matrix.size(); j++) {
			transformedMatrix[j][i] = matrix[i][(matrix.size() - 1) - j];
		}
	}
	return transformedMatrix;
}

vec_matrix scale_to_boundaries(vec_matrix matrix, std::vector<int> autocorrelations) {
	int max_correlation { *std::max_element(autocorrelations.begin() + 1, autocorrelations.end()) };
	matrix.erase(matrix.begin(), matrix.end() - max_correlation - 2);
	return matrix;
}

std::vector<std::vector<char>> prepare_iteration_bars(int count) {
	std::vector<std::vector<char>> rows { };
	for (int i = 0; i < count; i++) {
		std::string number { std::to_string(i) };
		for (unsigned int j = 0; j < number.size(); j++) {
			if (rows.size() <= j) {
				rows.push_back(std::vector<char>(count, ' '));
			}
			rows[j][i] = number[j];
		}
	}
	return rows;
}

vec_matrix enhanceWithRowInfo(vec_matrix matrix) {
	if (matrix.size() == 0)
		return matrix;
	std::vector<std::vector<char>> iterationRows = prepare_iteration_bars(matrix[0].size());
	int iterationRowsSize { static_cast<int>(iterationRows.size()) };
	matrix.insert(matrix.end(), iterationRows.begin(), iterationRows.end());
	for (unsigned int i = 0; i < matrix.size(); i++) {
		std::string matrix_size_number { std::to_string(matrix.size()) };
		std::string number { "" };
		if (i - iterationRowsSize >= 0) {
			number = std::to_string(i - iterationRowsSize);
		}
		number.resize(matrix_size_number.size() + 1, ' ');
		if (i - iterationRowsSize + 1 >= 0) {
			number[number.size() - 1] = '|';
		}
		matrix[matrix.size() - 1 - i].insert(matrix[matrix.size() - 1 - i].begin(), number.begin(), number.end());
	}
	return matrix;
}

}
}

#endif /* MATRIXOPERATIONS_H_ */
