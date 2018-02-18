#ifndef COMMANDCOLLECTOR_H_
#define COMMANDCOLLECTOR_H_

#include <string>
#include <map>
#include <fstream>

namespace Autocorrelation {
namespace CommandCollector {

using string_map = std::map<std::string, std::string>;
using string_pair = std::pair<std::string,std::string>;

bool is_command_value_pair(int argc, char * argv[], int index, std::string param) {
	return (std::string { argv[index] } == param) && ((index + 1) < argc) && (argv[index + 1][0] != '-');
}

string_map collect_command_input(int argc, char * argv[]) {
	if ((argc == 2) && (std::string { argv[1] } == "-in" || std::string { argv[1] } == "-out"))
		throw std::invalid_argument { "Can't use -in or -out flags as input." };
	string_map command_value_map { };
	for (int i = 1; i < argc; i++) {
		if (is_command_value_pair(argc, argv, i, "-in")) {
			command_value_map.insert(string_pair("-in", std::string { argv[i + 1] }));
			i++;
		} else if (is_command_value_pair(argc, argv, i, "-out")) {
			command_value_map.insert(string_pair("-out", std::string { argv[i + 1] }));
			i++;
		} else {
			if (command_value_map.find("inputString") != command_value_map.end()) {
				std::string & ref = command_value_map.at("inputString");
				ref = ref + " " + std::string { argv[i] };
			} else {
				command_value_map.insert(string_pair("inputString", std::string { argv[i] }));
			}
		}
	}
	if (command_value_map.find("-in") == command_value_map.end()) {
		return command_value_map;
	} else {
		std::ifstream file { command_value_map.at("-in") };
		std::string input { };
		if (file.is_open()) {
			std::string line { };
			while (std::getline(file, line)) {
				input = input + line + "\n";
			}
			file.close();
		} else {
			throw std::invalid_argument { "Your -in input doesn't seem to be a file or "
					"couldn't be found (is it in same location like the exe?). "
					"You entered: " + command_value_map.at("-in") };
		}
		if (command_value_map.find("inputString") != command_value_map.end()) {
			std::string & ref = command_value_map.at("inputString");
			ref = input;
		} else {
			command_value_map.insert(string_pair { "inputString", input });
		}
	}
	return command_value_map;
}
}
}

#endif /* COMMANDCOLLECTOR_H_ */
