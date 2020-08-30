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

struct answer_time
{
    int time;
    std::vector<node> path;
};

struct answer_price
{
    double price;
    std::vector<node> path;
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
    std::vector<node> price_path_trains;
    void change_nodes();
    std::vector<std::vector<int>> ad_list(std::vector<node> unique);
    answer_price find_better_price();
    void algo_price(std::vector<std::vector<int>> ad_list);
    void DFS(int v, bool visited[], std::vector<std::vector<int>> ad_list);

    answer_time algo_time_util(int v);
    int amount_seconds(std::string time1);
    answer_time find_better_time();


~Graph();

};


#endif //TRAINS_GRAPH_H
