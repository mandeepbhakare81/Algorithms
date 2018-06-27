/******************************************************************************
This program is C++ implementation of Dijkstra's algorithm to find the shortest path
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define INFINITY 100000
using namespace std;
//    vector<char> visited(nodes);
//int shortestpath(char , std::vector<char> , std::vector<char> , std::vector<int> , char [], int*);

int shortestpath(char startnode, std::vector<char> &nodes, std::vector<char> &unvisited, std::vector<int> &mindistance, vector<char> &previousnode, std::vector<vector <int> > &nodematrix){
    int present = 0;
    for(std::vector<char>::iterator itr=unvisited.begin(); itr<unvisited.end(); ){
        if(startnode == *itr){
           present = 1;
           unvisited.erase(itr);
           break;
        }
        itr++;
    }
    if(!present)
      return 1;
    //unvisited.erase(std::remove_if(unvisited.begin(), unvisited.end(), [](char startnode){retun startnode==} );
    int noofndoes = nodes.size();
    int startnodeindex = startnode-'A';
    for(int j=0; j<noofndoes; j++){
        if(mindistance[j] > (mindistance[startnodeindex]+nodematrix[startnodeindex][j])){
            mindistance[j] = mindistance[startnodeindex]+nodematrix[startnodeindex][j];
            previousnode[j] = startnode;
            shortestpath(nodes[j], nodes, unvisited, mindistance, previousnode, nodematrix);
        }
        
    }  
}

int main()
{
    int noofnodes = 0;
    cout<<"Please enter the number of nodes"<<endl;
    std::cin>>noofnodes;
    
    
    vector<int> mindistance;
    for (int i=0; i<noofnodes; i++){
        mindistance.push_back(INFINITY);
    }
    
    /*cout<<"Enter the distance between the nodes"<<endl;
    cout<<"Each row represents a particular node in the user given order and distance from a node to itself is 0"<<endl<<"If there is no connection then the distance is infinity"<<endl;*/
    std::vector<std::vector<int>> nodematrix;
    nodematrix.resize(noofnodes);
    for (int i=0; i<noofnodes; i++){
        nodematrix[i].resize(noofnodes);
        for(int j=0; j<noofnodes; j++){
          if(i==j){
            nodematrix[i][j]=0;
          }else{
            nodematrix[i][j] = INFINITY;
          }
        }
    }

    vector<char> nodes;
    char fromnode, tonode;
    int distance;
    char input;
    while(1){
        cout<<"Press Escape if you don't want to add more nodes"<<endl;
        cout<<"From node ="<<endl;
        cin>>fromnode;
        if(fromnode==27)
          break;
        nodes.push_back(fromnode);
        cout<<"To node ="<<endl;
        cin>>tonode;
        nodes.push_back(tonode);
        cout<<"Distance =";
        cin>>distance;
        
        nodematrix[fromnode-'A'][tonode-'A']=distance;
    }
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    vector<char> unvisited(nodes);
    for (int i=0; i<noofnodes; i++){
        for(int j=0; j<noofnodes; j++){
            std::cout<<nodematrix[i][j]<<endl;
        }
    }
    
    cout<<"Please enter the start node"<<endl;
    char startnode;
    cin>>startnode;
    std::vector<char> previousnode(noofnodes, startnode);
    mindistance[startnode-'A']=0;
    shortestpath(startnode, nodes, unvisited, mindistance, previousnode, nodematrix);

    cout<<"The shortest distance of the nodes from"<<startnode<<"is"<<endl;
    for (auto i: mindistance){
        cout<<i<<" ";
    }
    
    return 0;
}
