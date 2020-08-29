//
// Created by maria on 27.08.20.
//

#include "Graph.h"

bool cmp(node n1, node n2)
{
    return n1.price < n2.price;
}

Graph::Graph() {}

void Graph::sort_by_price()
{
    sort(this->edges.begin(), this->edges.end(), cmp);
}

Graph::~Graph() = default;

std::vector<node> Graph::unique_edges(std::vector<node> edges)
{
    int i = 0;
    int current_from;
    int current_to;
    std::vector<node> unique_array;
    while(i != edges.size())
    {
        int flag = 0;
        current_from = edges[i].departure_station;
        current_to = edges[i].arrival_station;
        for(int it = 0; it < unique_array.size(); it++)
        {
            if (unique_array[it].arrival_station == current_to && unique_array[it].departure_station == current_from)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            unique_array.insert(unique_array.end(), this->edges[i]);
        }
        i++;
    }

    return unique_array;

}

void Graph::change_nodes() {

    for(auto & edge : this->edges)
    {
        for(auto & vertex : this->vertexes)
        {
            if(edge.arrival_station == vertex.name)
            {
                edge.arrival_station = vertex.index;
            }
            if(edge.departure_station == vertex.name)
            {
                edge.departure_station = vertex.index;
            }
        }
    }
}

int Graph::find_better_price()
{
    //sort
    this->sort_by_price();
    //leave only vertises with lawest price
    std::vector<node> unique_array;
    unique_array = unique_edges(this->edges);
    //std::vector<std::pair<int, int>> arr;
    //arr = pairs(unique_array);
    //make spisok of smezhnost
    //replaceE(unique_array, arr);



    return 1;

    //do backtracking
}

std::vector<std::vector<int>> Graph::ad_list(std::vector<node> unique) {

    std::vector<std::vector<int>> ad_list;
    for(int i = 0; i< this->vertexes.size(); i++)
    {
        std::vector<int> v_n;
        ad_list.insert(ad_list.end(), v_n);
    }
    for(int i = 0; i< unique.size(); i++)
    {
        ad_list[unique[i].arrival_station].insert(ad_list[unique[i].arrival_station].end(), unique[i].departure_station);
    }

    return ad_list;
}

void DFS(int v, bool visited[], std::vector<std::vector<int>> ad_list)
{
    visited[v] = true;
    std::cout<<v<<std::endl;
    for(int i = 0; i< ad_list[v].size(); i++)
    {
        if(visited[ad_list[v][i]] == false)
        {
            DFS(ad_list[v][i], visited, ad_list);
        }
    }
}

void Graph::algo(std::vector<std::vector<int>> ad_list) {
    bool visited[6];
    for(int i = 0; i<6; i++)
    {
        visited[i] = false;
    }
    DFS(2, visited, ad_list);


}
