#include "file_reader.h"
#include "Graph.h"
#include <vector>
using namespace std;


int main()
{
    std::vector<node> result;
    result = FileReader::file_to_nodes("../test_task_data.csv");
    Graph* graph = new Graph();

    *graph = FileReader::file_to_graph("../test_task_data.csv");
    answer_price res = graph->find_better_price();
    std::cout<<"get better price"<<std::endl;

    for(int i = 0; i< res.path.size(); i++)
    {
        std::cout <<
                  res.path[i].train_number<<std::endl<<
                  res.path[i].departure_station<<std::endl<<
                  res.path[i].arrival_station<<std::endl<<
                  res.path[i].price<<std::endl<<
                  res.path[i].departure_time<<std::endl<<
                  res.path[i].arrival_time<<std::endl<<std::endl;
    }
    cout <<"better Price: "<< res.price<<endl;
    Graph* graph1 = new Graph();
    *graph1 = FileReader::file_to_graph("../test_task_data.csv");
    answer_time t = graph1->find_better_time();

    std::cout<<"Find better time "<<std::endl;

    for(int i = 0; i< t.path.size(); i++)
    {
        std::cout <<
                  t.path[i].train_number<<std::endl<<
                  t.path[i].departure_station<<std::endl<<
                  t.path[i].arrival_station<<std::endl<<
                  t.path[i].price<<std::endl<<
                  t.path[i].departure_time<<std::endl<<
                  t.path[i].arrival_time<<std::endl<<std::endl;
    }
    cout <<"better time in seconds: " << t.time;

	return 0;
}
