#pragma once
#include "Graph.h"

class FileReader{
	public:
		FileReader();
		static std::vector<node> file_to_nodes(std::string filename);
		static std::vector<std::string> split(std::string line, char delimiter);
		static Graph file_to_graph(std::string filename);
		~FileReader();
};

