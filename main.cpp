#include <iostream>
#include <stdexcept>
#include <fstream>
#include "Printer.h"
#include "CommandCollector.h"

// TODO: Extend this to make it work with UTF-8 Characters
// TODO: Integrate Diagramming Tool
// TODO: Refactor for better performance (a lot of copy ops right now)
// TODO: Fix multiline input text bug: only considers first line for shift

namespace CC = Autocorrelation::CommandCollector;

int main(int argc, char *argv[]) {
	CC::string_map command_value_map { };
	std::string text_to_analyze { "DEMO STRING" };
	if (argc > 1) {
		try {
			command_value_map = CC::collect_command_input(argc, argv);
			text_to_analyze = command_value_map.at("inputString");
		} catch (std::invalid_argument & ex) {
			std::cerr << ex.what();
			Printer{std::cout}.print_usage(argv);
			return 0;
		}
	}
	if (command_value_map.find("-out") != command_value_map.end()) {
		std::ofstream out_file { command_value_map.at("-out") };
		if (out_file.is_open()) {
			Printer{out_file}.print_to_output(text_to_analyze);
		} else {
			std::cerr << "Your provided -out doesn't seem to name a file!";
			Printer{std::cout}.print_usage(argv);
		}
	} else {
		Printer{std::cout}.print_to_output(text_to_analyze);
	}
}

