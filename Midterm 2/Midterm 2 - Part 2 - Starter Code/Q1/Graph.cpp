#include "Graph.hpp"
#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

/*
 * adds a vertex to the graph
 */
void Graph::addVertex(int n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->key == n){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->key = n;
        vertices.push_back(v);
    }
}

/*
 * adds an edge between two vertices (directed graph)
 */
void Graph::addEdge(int src, int dest){
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->key == src) {
            for(int j = 0; j < vertices.size(); j++) {
                if(vertices[j]->key == dest && i != j) {
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                }
            }
        }
    }
}

/*
 * Complete the following function which checks if vert is a boss vertex
 */

bool Graph::isVertexABoss(vertex *vert) {
    queue<vertex*>q;
    q.push(vert);
    vertex *x;
    while(!q.empty()){
        x=q.front();
        q.pop();
        for(int i=0; i<x->adj.size(); i++){
            if(x->adj[i].v->visited==false){
                x->adj[i].v->visited=true;
                q.push(x->adj[i].v);
            }
        }
    }
    for(int i=1; i<vertices.size(); i++){
        if(vertices[i]->visited==false){
            return false;
        }
    }
    return true;
}

/*
 * Complete the following function which checks if the graph is a Boss
 */
bool Graph::isGraphABoss() {
    for(int i=0; i<vertices.size(); i++){
        if(isVertexABoss(vertices[i])){
            return true;
        }
    }
    return false;
}
