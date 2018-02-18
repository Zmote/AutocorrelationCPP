#include "Printer.h"

#include <algorithm>
#include <iterator>

#include "AutocorrelationOperations.h"
#include "MatrixOperations.h"

namespace AC = Autocorrelation::AutocorrelationOperations;
namespace MO = Autocorrelation::MatrixOperations;

Printer::Printer(std::ostream& p_out) :
		out { p_out } {
}

void Printer::print_usage(char* argv[]) {
	out << "\n/********************************/\n"
			"/      HOW TO USE THIS TOOL      /\n"
			"/********************************/\n"
			"Direct string calculation: " << *argv[0] << " Your String Here\n"
			"Console output from file input: " << *argv[0] << " -in infile.txt\n"
			"File output from file input: " << *argv[0] << " -in infile.txt -out outfile.txt\n";
}

void Printer::print_to_output(std::string& text_to_analyze) {
	out << "Text to Analyze: \n\n";
	out << text_to_analyze << "\n\n";

	vec_matrix auto_correlation_matrix = AC::calculate_autocorrelation_matrix(text_to_analyze);

	out << "Autocorrelations Map: \n\n";
	print_matrix(auto_correlation_matrix);

	out << "\nAutocorelation Counts: \n\n";
	std::vector<int> autocorrelations = AC::calculate_autocorrelation(auto_correlation_matrix);
	printVector(autocorrelations);

	out << "\nAutocorelations Graph: \n\n";
	print_autocorrelations_graph(autocorrelations);
}

void Printer::print_autocorrelations_graph(std::vector<int> autocorrelations) {
	int max_correlation { *std::max_element(autocorrelations.begin() + 1, autocorrelations.end()) };
	std::string emptyRow { std::string { }.insert(0, autocorrelations.size(), ' ') };
	vec_matrix emptyMatrix = AC::calculate_word_matrix(emptyRow);
	for (unsigned int i = 0; i < emptyMatrix.size(); i++) {
		std::vector<char> & row = emptyMatrix[i];
		for (unsigned int j = 0; j < row.size(); j++) {
			if (static_cast<unsigned int>(autocorrelations[i]) == j) {
				if (autocorrelations[i] == max_correlation) {
					row[j] = '+';
				} else {
					row[j] = '-';
				}
			} else {
				row[j] = ' ';
			}
		}
	}
	print_matrix_with_graph_info(MO::scale_to_boundaries(MO::transform_matrix(emptyMatrix), autocorrelations));

}

void Printer::print_line_to_output(std::string delimiter, int count) {
	for (int i = 0; i < count; i++) {
		out << delimiter;
	}
	out << "\n";
}

void Printer::print_matrix(vec_matrix matrix) {
	std::for_each(matrix.begin(), matrix.end(), [this](std::vector<char> & row) {
		std::copy(row.begin(),row.end(),std::ostream_iterator<char> {this->out, " "});
		this->out << "\n";
	});
}

void Printer::print_matrix_with_graph_info(vec_matrix matrix) {
	print_matrix(MO::enhanceWithRowInfo(matrix));
}
