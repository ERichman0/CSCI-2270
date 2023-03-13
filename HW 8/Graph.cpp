#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addEdge(string v1, string v2){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    for(int i=0; i<vertices.size(); i++){
        cout<<vertices[i]->name<<" --> ";
        for(int j=0; j<vertices[i]->adj.size(); j++){
            cout<<vertices[i]->adj[j].v->name<<" ";
        }
        cout<<endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex *vStart;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == sourceVertex) {
            vStart = vertices[i];
        }
    }
    cout<<"Starting vertex (root): "<<vStart->name<<"-> ";

    vStart->visited = true;
    
    queue<vertex*> q;
    q.push(vStart);

    vertex *n;
    while(!q.empty()) {
        n = q.front();
        q.pop();

        for (int x = 0; x < n->adj.size(); x++) {
            if (!n->adj[x].v->visited) {
                n->adj[x].v->distance = n->distance + 1;
                n->adj[x].v->visited = true;
                q.push(n->adj[x].v);
                cout<< n->adj[x].v->name << "(" << n->adj[x].v->distance << ")" << " ";
            }
        }
    }
}


int Graph::getConnectedBuildings(){
    int connections=0;
    for(int i=0; i<vertices.size(); i++){
        vertices[i]->visited=false;
    }
    for(int i=0; i<vertices.size(); i++){
        if(!vertices[i]->visited){
            vertices[i]->visited=true;
            queue<vertex*> q;
            q.push(vertices[i]);
            vertex* a;
            while(!q.empty()){
                a=q.front();
                q.pop();
                for(int j=0; j<a->adj.size(); j++){
                    if(!a->adj[j].v->visited){
                        a->adj[j].v->visited=true;
                        a->adj[j].v->distance=a->distance+1;
                        q.push(a->adj[j].v);
                    }
                }
            }
            connections++;
        }
    }
    return connections;
}