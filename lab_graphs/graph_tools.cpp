/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
    unordered_map<Vertex,Vertex> predecessor;
    set<pair<Vertex,Vertex>> seen;
    unordered_map<Vertex,int> distance;
    distance.insert(make_pair(start,0));
    predecessor.insert(make_pair(start,-1));////////
    queue<Vertex> myQueue;
    myQueue.push(start);

    while(!myQueue.empty()){
        Vertex out= myQueue.front();
        myQueue.pop();
        vector<Vertex> adj=graph.getAdjacent(out);
        for(size_t i=0;i<adj.size();i++){
            Vertex v=adj[i];
            if(seen.find(make_pair(out,v))==seen.end()){
                seen.insert(make_pair(out,v));
                seen.insert(make_pair(v,out));
                predecessor.insert(make_pair(v,out));
                distance.insert(make_pair(v,distance[out]+1));
                if(v==end){
                    break;
                }
                myQueue.push(v);
            }

        }

    }
    int out=distance[end];
    Vertex second =end;
    Vertex first;
    first=predecessor[second];

    do{ 
        graph.setEdgeLabel(first,second,"MINPATH");
        second =first;
        first=predecessor[second];
        if(second==start){
            break;
        }
        
    }while(first!=start);
    if(first==start){
        graph.setEdgeLabel(first,second,"MINPATH");
    }
    return out;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
    
    int out=std::numeric_limits<int>::max();
    Vertex outu;
    Vertex outv;
    vector<Vertex> nodes=graph.getVertices();
    set<pair<Vertex,Vertex>> seen;
    for(size_t i=0;i<nodes.size();i++){
        Vertex u=nodes[i];
        vector<Vertex> adj=graph.getAdjacent(u);
        for(size_t j=0;j<adj.size();j++){
            Vertex v=adj[j];
            if(seen.find(make_pair(u,v))==seen.end()){
                seen.insert(make_pair(u,v));
                seen.insert(make_pair(v,u));
                int compare=graph.getEdgeWeight(u,v);
                if(compare<out){
                    out=compare;
                    outu=u;
                    outv=v;
                }
            }
        }
    }
    graph.setEdgeLabel(outu,outv,"MIN");
    return out;

}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
bool GraphTools::myFunction(Edge i,Edge j){
    return i.weight<j.weight;
}
  

void GraphTools::findMST(Graph & graph)
{   
    vector<Edge> edges=graph.getEdges();
    std::sort(edges.begin(),edges.end(),myFunction);

    vector<Vertex> nodes=graph.getVertices();
    int numberNodes=nodes.size();
    for(size_t i=0;i<nodes.size();i++){
        string name=to_string(i);
        graph.setVertexLabel(nodes[i],name);
    }

    int need=numberNodes-1;

    DisjointSets set;
    set.addelements(numberNodes);

    int count=0;
    
        for(size_t i=0;i<edges.size();i++){
            Vertex u=edges[i].source;
            string firstName=graph.getVertexLabel(u);
            istringstream buffer(firstName);
            int first;
            buffer >> first;  
           // cout<<first<<"dasdasdsad"<<endl; 

            Vertex v=edges[i].dest;
            string secondName=graph.getVertexLabel(v);
            istringstream buffer1(secondName);
            int second;
            buffer1 >> second; 
          //  cout<<second<<"dfffffffffasdasdsad"<<endl;

            if(set.find(first)!=set.find(second)){
                set.setunion(first,second);
                graph.setEdgeLabel(u,v,"MST");
                count++;
            }
            if(count==need){
                break;
            }

        }
    
}
