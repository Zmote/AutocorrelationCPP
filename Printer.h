#ifndef PRINTER_H_
#define PRINTER_H_
#include <ostream>
#include <vector>
#include <string>

using vec_matrix = std::vector<std::vector<char>>;

class Printer {
	std::ostream & out;
public:
	Printer(std::ostream & p_out);
	void print_usage(char * argv[]);
	void print_to_output(std::string & text_to_analyze);
	void print_autocorrelations_graph(std::vector<int> autocorrelations);
	void print_line_to_output(std::string delimiter, int count);
	void print_matrix(vec_matrix matrix);
	void print_matrix_with_graph_info(vec_matrix matrix);
	template<typename T>
	void printVector(std::vector<T> & vector);
	template<typename T>
	void printVectors(std::vector<std::vector<T>> & vectors);
};

template<typename T>
void Printer::printVector(std::vector<T> & vector){
	for (T type : vector) {
		out << type << " ";
	}
	out << "\n";
}

template<typename T>
void Printer::printVectors(std::vector<std::vector<T>> & vectors){
	for (std::vector<T> row : vectors) {
		printVector(row, out);
	}
}

#endif /* PRINTER_H_ */
