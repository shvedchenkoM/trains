//
// Created by maria on 27.08.20.
//

#include <sstream>
#include "Graph.h"

std::vector<std::string> split(std::string line, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss (line);
    std::string item;

    while (getline (ss, item, delimiter)) {
        result.push_back (item);
    }

    return result;
}


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

void Graph::DFS(int v, bool visited[], std::vector<std::vector<int>> ad_list)
{
    int flag = 0;
    visited[v] = true;
    this->price_path.insert(this->price_path.end(), v);

    for(int i = 0; i< ad_list[v].size(); i++)
    {
        if(visited[ad_list[v][i]] == false)
        {
            flag++;
            DFS(ad_list[v][i], visited, ad_list);
        }
    }

}

void Graph::algo_price(std::vector<std::vector<int>> ad_list) {

    bool *visited = new bool[6];
    for (int i = 0; i < 6; i++)
        visited[i] = false;

    for(int i = 0; i<6; i++)
    {
        visited[i] = false;
    }
    DFS(1, visited, ad_list);

    for(int i = 0; i<this->price_path.size(); i++)
    {
        std::cout << this->price_path[i]<<" ";
    }
    std::cout<<std::endl;

}

double Graph::find_better_price()
{
    double total_price = 0;
    this->change_nodes();
    this->sort_by_price();
    std::vector<node> unique;
    unique = this->unique_edges(this->edges);
    std::vector<std::vector<int>> ad_list;
    ad_list = this->ad_list(unique);
    this->algo_price(ad_list);
    for(int i = 0; i<this->price_path.size() - 1; i++)
    {
        for(int j = 0; j<unique.size(); j++)
        {
            if(unique[j].arrival_station == this->price_path[i+1] &&
               unique[j].departure_station == this->price_path[i]) {
                total_price += unique[j].price;
                this->price_path_trains.insert(this->price_path_trains.end(), unique[j]);
            }
        }

    }



    return total_price;

    //do backtracking
}

int Graph::amount_seconds(std::string time1) {
    std::vector<std::string> arr1;
    arr1 = split(time1, ':');
    int ss1;
    ss1 = 3600 * atoi(arr1[0].c_str()) + 60 * atoi(arr1[1].c_str()) + atoi(arr1[2].c_str());
    return ss1;
}

//return seconds
int Graph::algo_time(int v)
{
    bool visited[6];
    for(int i = 0; i < 6; i++)
    {
        visited[i] = false;
    }
    visited[v] = true;

    int total_time = 0;
    this->change_nodes();
    std::vector<node> path;

    int ss1, ss2, time;
    while(
            visited[0] == true &&
            visited[1] == true &&
            visited[2] == true &&
            visited[3] == true &&
            visited[4] == true &&
            visited[5] == true)
    {
        int miin_time = 10000001;
        node curr_node;

        for (int i = 0; i < this->edges.size(); i++)
        {
            //
            if (this->edges[i].departure_station == v) {
                if (visited[this->edges[i].arrival_station] == false) {
                    if(path.size() == 0)
                    {
                        ss1 = amount_seconds(this->edges[i].departure_time);
                    } else
                    ss1 = amount_seconds(path[path.size()-1].arrival_time);
                    ss2 = amount_seconds(this->edges[i].arrival_time);
                    if(ss2 >= ss1) time = ss2 - ss1;
                    else time = 24*3600 - ss1 + ss2;
                    if (time < miin_time) {
                        miin_time = time;
                        curr_node = this->edges[i];
                    }
                }
            }
        }
        if (miin_time < 1000001) {
            visited[curr_node.arrival_station] = true;
            path.insert(path.end(), curr_node);
            v = curr_node.arrival_station;
            total_time += miin_time;
        }
    }

 return total_time;

}



