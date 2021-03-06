#include "dijkstra.h"
#include <iostream>
#include <limits>

namespace LIMoSim
{

Dijkstra::Dijkstra() :
    p_graph(nullptr)
{

}

/****************************************
 *             PUBLIC METHODS           *
 ***************************************/

RoutingPath Dijkstra::computeShortestPath(RoutingNode *_start, RoutingNode *_destination)
{
    init(_start);

    while(m_q.size()>0)
    {
        RoutingNode *u = getNearestNode();
        if(!u) // no path exists
        {
            //std::cout << "breaking" << std::endl;
            break;
        }

        removeNode(u);

        std::vector<RoutingNode*> neighbors = u->getConnections();
        for(auto v : neighbors)
        {
            if(getNodeIndex(v)>-1) // v is in Q
                updateDistance(u, v);
        }
    }

    // create the routing path
    RoutingPath path;
    RoutingNode *node = _destination;
    while(m_predecessors[node])
    {
        path.prepend(node);
        node = m_predecessors[node];

    }
    path.prepend(node);


    return path;
}

/****************************************
 *           PROPERTY ACCESSORS         *
 ***************************************/

void Dijkstra::setGraph(RoutingGraph *_graph)
{
    p_graph = _graph;
}

/****************************************
 *            PRIVATE METHODS           *
 ***************************************/

void Dijkstra::init(RoutingNode *_start)
{
    m_q = p_graph->getNodes();
    for(auto node : m_q)
    {
        m_distances[node] = std::numeric_limits<double>::infinity();
        m_predecessors[node] = nullptr;
    }

    m_distances[_start] = 0;
}

void Dijkstra::updateDistance(RoutingNode *_u, RoutingNode *_v)
{
    double distance_m = m_distances[_u] + _u->getCost(_v);
    if(distance_m<m_distances[_v])
    {
        m_distances[_v] = distance_m;
        m_predecessors[_v] = _u;
    }
}

RoutingNode* Dijkstra::getNearestNode()
{
    RoutingNode *node = nullptr;
    double minDistance_m = std::numeric_limits<double>::infinity();

    for(auto currentNode : m_q)
    {
        double distance_m = m_distances[currentNode];

        if(distance_m<minDistance_m)
        {
            node = currentNode;
            minDistance_m = distance_m;
        }
    }

    return node;
}

void Dijkstra::removeNode(RoutingNode *_node)
{
    int index = getNodeIndex(_node);
    if(index>-1)
        m_q.erase(m_q.begin() + index);
}

int Dijkstra::getNodeIndex(RoutingNode *_node)
{
    int index = -1;
    for(unsigned int i=0; i<m_q.size(); i++)
    {
        if(m_q.at(i)==_node)
        {
            index = i;
            break;
        }
    }

    return index;
}



}
