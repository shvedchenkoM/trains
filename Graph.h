//
// Created by maria on 27.08.20.
//
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include "Vertex.h"

#ifndef TRAINS_GRAPH_H
#define TRAINS_GRAPH_H


struct node
{
    int train_number;
    int departure_station;
    int arrival_station;
    double price;
    std::string departure_time;
    std::string arrival_time;
};

class Graph {

public:
    Graph();

    std::vector<Vertex> vertexes;
    void sort_by_price();
    int size;
    std::vector<node> edges;
    std::vector<node> unique_edges(std::vector<node> edges);
    std::vector<int> price_path;
    void change_nodes();
    std::vector<std::vector<int>> ad_list(std::vector<node> unique);
    int find_better_price();
    void algo(std::vector<std::vector<int>> ad_list);
    void DFS(int v, bool visited[], std::vector<std::vector<int>> ad_list);//need being improved cause something strange, he doesn't understan that there ane no connection


~Graph();

};


#endif //TRAINS_GRAPH_H
