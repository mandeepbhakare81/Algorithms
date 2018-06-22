/******************************************************************************/

                            
/*The input should be in the form of seccessive letters i.e. after A the next input cannot be K or L*/


/*******************************************************************************/

#include <stdio.h>
#include <set>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
/********************************************************************************************************/
void parenthesize(char parentnode, list<char> nodeslist[]){
    char ch;
    cout<<"("<<parentnode;
    //[](){parenthesize(nodeslist[int(parentnode)-65].pop_front()}  C++11 lambda function can be used to here to read and pop at the same time
    while(!nodeslist[int(parentnode)-65].empty()){
        ch = nodeslist[int(parentnode)-65].front();
        nodeslist[int(parentnode)-65].pop_front();
        parenthesize(ch, nodeslist);
    }
    cout<<")";
}
/*********************************************************************************************************/
/*Input pairs can be in any order*/
/*Rules of a tree
    1. Root will not have any node pointing to it so column for root node will be all 0.
    2. If there are more than two children then the row will contain more than two 1s.
    3. Cycle is present when there are more than 1 nodes pointing to the node i.e. column contails more than one 1s
    4. If there are more than one empty colums then there are multiple Root
    All above observations can be used to detect the errors*/

string SExpression (string nodestring){
    char rootnode;
    nodestring.erase(std::remove(nodestring.begin(), nodestring.end(), '('), nodestring.end());
    
    nodestring.erase(std::remove(nodestring.begin(), nodestring.end(), ')'), nodestring.end());
    std::replace(nodestring.begin(), nodestring.end(), ',', ' ');

    //int nodearray [numnodes];
    vector<string> vec;
    
    /*There can be 26 nodes from A to Z*/
    string::iterator it;
    
    for (it=nodestring.begin(); it != nodestring.end(); it++){
        if((*it) != ' '){
            if((*it)<65 || (*it)>90){
                cout<<"Please enter valid sequence"<<endl;
                return "E5";
            }
            vec.push_back({*it});
        }
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    int numnodes = vec.size();
    cout<<"Number of nodes present in the tree!"<<numnodes<<endl;
    
    
    std::list<char> nodeslist[numnodes];   
    
    int leafnodes[numnodes];
    int rootnodes[numnodes];
    for(int i=0; i<numnodes; i++){
        rootnodes[i]=1;
        leafnodes[i]=0;
    }
    
    string::iterator it1;
    string::iterator it2;
    for (it1=nodestring.begin(); it1<nodestring.end() && it2<nodestring.end();){
            it2 = it1+2;
            rootnodes[int(*it2 )-65] = 0;
            if(leafnodes[(*it2)-65] == 1){
              cout<<"Cycle is present in the tree"<<endl;
              return "E3";
            }
            nodeslist[int(*it1)-65].push_back(*it2);
            leafnodes[int(*it2)-65] = 1;
            it1=it2;
            it1=it1+2;
    }
    int sum = 0;
    for(int i=0; i<numnodes; i++){
        if(rootnodes[i] == 1){
           rootnode = char(i+65);
        }
        sum = sum+rootnodes[i];
    }
    if(sum>1){
        cout<<"There are multiple roots in the tree"<<endl;
        return "E4";
    }
    
    for(int i=0; i<numnodes; i++){
        if(nodeslist[i].size()>2){
            cout<<"Node has more than two children"<<endl;
            return "E1";
        }
            
    }
    parenthesize(rootnode, nodeslist);  //This function will be called recursively to print the tree in S-Expression
}    
    

    
    
/***************************************************************************************************************/    

int main()
{
    string str;
    cout<<"Please enter the nodes and edges"<<endl;
    std::getline(std::cin, str);
    SExpression(str);
    return 0;
}

/***************************************************************************************************************/

