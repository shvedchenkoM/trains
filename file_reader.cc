#include <sstream>
#include <fstream>
#include "file_reader.h"
#include "Vertex.h"

FileReader::FileReader(){}

std::vector<std::string> FileReader::split(std::string line, char delimiter)
{
	std::vector<std::string> result;
    std::stringstream ss (line);
    std::string item;

    while (getline (ss, item, delimiter)) {
        result.push_back (item);
    }

    return result;
}

std::vector<node> FileReader::file_to_nodes(std::string file_name)
{
	std::vector<node> result;

	std::ifstream grFile(file_name);
	
	if (!grFile.is_open()) 
		throw std::runtime_error("Could not open file");
	
	std::string line;
	while ( getline(grFile, line) )
	{
		std::stringstream ss(line);
		
		node pattern;

		std::vector<std::string> columns;
		columns = split(line, ',');

		pattern = {
			.train_number = atoi(columns[0].c_str()),
			.departure_station = atoi(columns[1].c_str()),
			.arrival_station = atoi(columns[2].c_str()),
			.price = atof(columns[3].c_str()),
			.departure_time = columns[4],
			.arrival_time = columns[5],
		};
		result.insert(result.end(), pattern);

	}

	return result;
}

Graph FileReader::file_to_graph(std::string filename)
{
    std::set<int> vert;
    std::vector<Vertex> vertex;
    Graph* graph = new Graph();
    std::vector<node> edges;
    edges = file_to_nodes(filename);

    for(int i = 0; i<edges.size(); i++)
    {
        vert.insert(edges[i].arrival_station);
        vert.insert(edges[i].departure_station);
    }
    graph->edges = edges;
    graph->size = vert.size();
    int i =0;
    for (std::set<int>::iterator it=vert.begin(); it!=vert.end(); ++it) {
        Vertex *curr_ver = new Vertex(*it, i);
        vertex.insert(vertex.end(), *curr_ver);
        i++;
    }

    graph->vertexes = vertex;
    return *graph;
}

FileReader::~FileReader(){}
