#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <climits>
#include <cstring>
using namespace std;

struct edge{
    int first;            // denotes smaller vertex
    int second;           // denotes larger vertex
    int weight;           // stores weight of the edge
};

void addtoedgelist(list<edge>&t,int u,int v,int w)
{
    edge temp,temp1;
    temp.first = (u<v)? u:v;                     // stores smaller vertex
    temp.second = (u<v)? v:u;                    // stores larger vertex
    temp.weight = w;                             // stores edgeweight
    auto it = t.begin();
    for(it = t.begin();it!= t.end();it++)
    {
        temp1 = *it;
        if(temp1.weight > w)                          // searching for weight greater than w in edgelist
        {
            break;
        }
        else if(temp1.weight == w)
        {
            if(temp1.first > temp.first ||(temp1.first == temp.first && temp1.second > temp.second))
            {
                break;
            }
        }
    }
    t.insert(it,temp);                       // inserting at correct position it so that the list remains sorted
}


class Graph{
  protected:
    int vertices;                           // indicates number of vertices in the graph
    int edges;                              // indicates number of edges in the graph
    list <pair<int,int>> *l;                // adjacency list 
    list <edge> g;                          // stores all edges in ascending order of their weights    
    bool condition1;                        // used for uptodate function in mst class
    bool condition2;
  public:
    Graph(int vertices,int queries);            //constructor
    ~Graph();                                   // destructor
    void addv();       
    void adde(int u,int v,int weight);
    void addtolist(list<pair<int,int>>l[],int source,int dest,int weight);
    void dele(int u,int v);
    bool searchedge(int u,int v,int *p); 
    friend void addtoedgelist(list<edge>&t,int u,int v,int w);
};


/*************************** CLASS GRAPH FUNCTIONS START *************************************************************/


Graph::Graph(int vertices,int queries)
{
    this->vertices = vertices;                       // intialising num of vertices
    edges = 0;                                       // intialising num of edges
    l = new list<pair<int,int>>[vertices + queries];      //dynamically allocating memory to adjacency list 
    
    for(int i=0;i<vertices;i++)
    {
        l[i].push_back(make_pair(i,0));              // adding vertex in its own list as head
    }
    condition1 = false;
    condition2 = false;
}

Graph::~Graph()
{
    for(int i=0;i<vertices;i++)
    {
        l[i].clear();               // clearing all lists
    }
}

void Graph::addv()
{
    if(condition2)
    {
        condition1 = false;
    }
 
    l[vertices].push_back(make_pair(vertices,0));             //  adding vertex in its own list as head
    vertices++;                                                // updating num of vertices
}

void Graph::adde(int u, int v, int weight)
{
    
    
    if(u >= vertices || v >= vertices || u < 0 || v < 0)     // checking whether vertices are valid
    {
       cerr<<"Invalid indices"<<endl;
       return;
    }
    
    if(condition2)
    {
        condition1 = false;
    }
    
    addtolist(l,u,v,weight);                       // adding vertex v in adjacency list of u
    addtolist(l,v,u,weight);                       // adding vertex u in adjacency list of v
    addtoedgelist(g,u,v,weight);
    edges++;                                     // updating number of edges
}


/*****************************************************************************************************

* takes source vertex destination vertex and weight of the edge as arguments.

* searches for the appriopriate position of weight in source adjacency list.

* inserts the vertex v and weight w at iterator it so that the sorted proprty of list doesnt change.

*****************************************************************************************************/


void Graph::addtolist(list<pair<int,int>>l[],int source, int dest, int weight)
{
    pair<int,int> temp;                //  stores the copy of new edge
    pair<int,int> elem;               // used to access the edges of source vertex
    
    temp.first  = dest;             // creating copy of new edge
    temp.second = weight;
    auto it     = l[source].begin();     // iterator for adjacency list of source vertex
    it++;
    
    for(;it!=l[source].end();it++)
    {
        elem = *it;
        
        if(elem.second > temp.second || (elem.second == temp.second && elem.first > temp.first))
        {
            break;
        }
    }
    
    l[source].insert(it,temp);                     // inserting edge at it

}


void Graph::dele(int u, int v)
{
    int weight;                                  // used to store the weight of edge uv if exists
    bool check;                                // used to check whether edge uv exists
    edge temp;
    pair<int,int> edge1;                         // used to store elem in adjacency list of u
    pair<int,int> edge2;                         // used to store elem in adjacency list of u
    
    check = searchedge(u,v,&weight);          // searches for edge uv 
    
    if(!check)
    {
        cerr<<"Invalid edge"<<endl;               // prints error message if edge is not present
        return;
    }
    
    if(condition2)
    {
        condition1 = false;
    }
    
    edge1.first  = v;                        // creating a copy of element in adjacency list of u
    edge1.second = weight;
    edge2.first  = u;                       // creating a copy of element in adjacency list of u
    edge2.second = weight;
    
    l[u].remove(edge1);                       // removing edge in adjacency list of u
    l[v].remove(edge2);                        // removing edge in adjacency list of u
    edges--;
    
    for(auto it =g.begin();it!= g.end();it++)
    {
        temp = *it;
        if((temp.first == u || temp.second == u) && temp.weight == weight)         // deleting edge in the edgelist
        {
            g.erase(it);
            return;
        }
    }
    
}

bool Graph::searchedge(int u, int v, int *p)
{
     pair<int,int> temp;                     // used to store the weight of edge uv if exists
    
    for(auto it =l[u].begin();it!= l[u].end();it++)
    {
        temp = *it;
        if(temp.first == v)                     // checking whether edge uv exists
        {
            *p = temp.second;                   // storing weight of edge uv 
            return true;                        // returns true as edge uv is found
        }
    }
    
    return false;
}

/******************************** CLASS GRAPH FUNCTIONS END *********************************************************/


class MST : public Graph{
    list <pair<int,int>> *mst;                   // adjacency list to hold variable tree
    list <edge> t;                               // stores all edges acc to the weights
  public:
    
    MST(int vertices,int queries):Graph(vertices,queries)
    {
       mst = new list<pair<int,int>>[vertices + queries];         //dynamically allocating memory to tree 
    }
    
    bool mstvertex(int v);                                          // checks whether vertex v is present in mst
    void add(int v);                                               // adds vertex to the tree
    void addedge(int u,int v,int weight);                         // adds edge to the tree
    friend void addtoedgelist(list<edge>&t,int u,int v,int w);   // adds edges in the tree to the list t 
    bool DFSrec(int s,int p,bool visited[]);
    bool iscyclic();                                             // detects cycle
    int primsalgo(int v);
    void Displaytree();
    int kruskalsalgo();
    bool Uptodate();
};


/************************************** CLASS MST FUNCTIONS START ****************************************************/


bool MST::Uptodate()
{
    if(condition1 && condition2)    // if prim is called and no other delete/add functions are called after calling prim
    {
        return true;
    }
    return false;
}

void MST::add(int v)
{
    mst[v].push_back(make_pair(v,0));             //  adding vertex in its own list as head
}

void MST::addedge(int u,int v, int weight)
{   
    mst[u].push_back(make_pair(v,weight));          // adding vertex v in adjacency list of u
    mst[v].push_back(make_pair(u,weight));          // adding vertex u in adjacency list of v
    addtoedgelist(t,u,v,weight);                   // adding edge uv in list t
}

bool MST::mstvertex(int v)
{
    return (mst[v].empty()) ? false : true;              // checking whether adjacency list of v is empty
}

int MST::primsalgo(int v)
{
    condition1 = true;
    condition2 = true;
    
    if(v >= vertices || v < 0)     // checking whether vertices are valid
    {
       cerr<<"Invalid indices"<<endl;
       return -1;
    }
    
    for(int i=0;i<vertices;i++)
    {
        mst[i].clear();               // clearing all lists
    }
    t.clear();                        // clearing all edges in list t
    
    int parent[vertices];             // stores the parent of vertices 
    int res;                         // stores the sum of edgeweights of tree
    int temp;                       
    int key[vertices];                 // stores minimum edgeweight associated with the vertex
    
    memset(parent,-1,vertices);       // intialising parent of all vertices to -1
    
    for(int i=0;i<vertices;i++)
    {
        key[i] = INT_MAX;                // intialising all key values to INT_MAX
    }
    key[v] = 0;                             // intialising all key value of source vertex to 0           
    res = 0;                               // intialising res to 0 
    
    for(int i=0;i<vertices;i++)
    {
       temp = -1;
        for(int j=0;j<vertices;j++)
        {
            if(!mstvertex(j) && (temp == -1 || key[j]<key[temp]) ) // searching for the vertex with lowest key value
            {
                temp = j;
            }
        }
    
       add(temp);       // adding vertex with lowest key(among non mst vertices) value to the tree
        
        if(key[temp]!= 0)
        {
          addedge(temp,parent[temp],key[temp]);     // adding edge between temp and parent of temp
        }
       res += key[temp];                            // adding edgeweight to res
        
       for(auto it = l[temp].begin();it!= l[temp].end();it++)  // adjacency list of temp
       {
           pair<int,int> t = *it;
           if(!mstvertex(t.first) && t.second < key[t.first]) // updating key values of adjacent vertices of temp
           {
               key[t.first] = t.second;
               parent[t.first] = temp;                       // updating parent of adjacent vertex
           }
       }  
    }
    return res;
}

void MST::Displaytree()
{
    edge temp;                                     // used to access the edges in edgelist t
    for(auto it = t.begin();it!= t.end();it++)
    {
      temp = *it;
      cout<<temp.first<<" "<<temp.second<<" "<<temp.weight<<endl;  // printing edges in edgelist t
    }
}

bool MST::DFSrec(int s, int p, bool visited[])
{
    visited[s] = true;                              // marking source vertex as visited
    pair<int,int> temp;                             // used to access adjacent vertices of source vertex
    
    for(auto it = mst[s].begin();it!= mst[s].end();it++)
    {
        temp = *it;
       
       if(!visited[temp.first])                         // if adjacent vertex is not visited
        {
            if(DFSrec(temp.first,s,visited))
            {
               return true;
            }
        }
        else if(temp.first!= p && temp.first != s)  // if adjacent vertex is not visited and not equal to p and s
        {
            return true;
        }
    }
    return false;
   
}

bool MST::iscyclic()
{
     bool visited[vertices];                                // used to mark the vertices as visited // 
     memset(visited,false,vertices);                       // marking all vertices as not visited //
    
    for(int i=0;i<vertices;i++)
    {
        if(visited[i] == false)
        {
            if(DFSrec(i,-1,visited))            // calling dfsrec with i as source and -1 as parent //
            {
                return true;
            }
        }
    }
    return false;
    
}
int MST::kruskalsalgo()
{
    for(int i=0;i<vertices;i++)
    {
        mst[i].clear();               // clearing all lists
    }
    t.clear();                        // clearing all edges in list t
    
    condition1 = true;
    condition2 = true;
    
    edge temp;
    int res =0;                        // stores the sum of edgeweights of tree
    
    for(int i=0;i<vertices;i++)
    {
        add(i);                           // adding all vertices to mst
    }
    
    for(auto it = g.begin();it!= g.end();it++)    // traversing all edges in graph in ascending order
    {
        temp = *it;
        mst[temp.first].push_back(make_pair(temp.second,temp.weight));  // adding edge uv into tree
        mst[temp.second].push_back(make_pair(temp.first,temp.weight));
        
       if(iscyclic())                  // if cycle is detected on adding edge uv
       {
          mst[temp.first].pop_back();              // removing edge uv
          mst[temp.second].pop_back();  
       }
       else
        {
           res = res+temp.weight;                                       // adding edgeweight to res
           addtoedgelist(t,temp.first,temp.second,temp.weight);       // adding edge to edgelist t
        }
    }
   return res; 
}

/************************************ CLASS MST FUNCTIONS END *********************************************************/


int main() {
    int vertices;             // used to store num of vertices
    int queries;             // used to store num of queries
    int u;                   // used to store first vertex
    int v;                   // used to store second vertex
    int w;                  // used to store weight
    int res;                // used to store res of mst
    
    cin>>vertices>>queries;
    MST m(vertices,queries);                   // creating a mst
    
    while(queries--)
    {
        string s;
        cin>>s;
        if(s == "ADDV")
        {
          m.addv();                                  // calling addv function 
        }
        else if (s == "ADDE")
        {
            cin>>u>>v>>w;
            m.adde(u,v,w);                            // calling adde function
        }
        else if(s == "DELE")
        {
            cin>>u>>v;
            m.dele(u,v);                               // calling dele function
        }
        else if(s == "Prims")
        {
            cin>>u;
            res = m.primsalgo(u);                      // calling primsalgo function
            cout<<res<<endl;
        }
        else if(s == "DisplayTree")
        {
            m.Displaytree();                          // calling displaytree function
        }
        else if(s == "Kruskal")
        {
          res = m.kruskalsalgo();                     // calling kruskalsalgo function
            cout<<res<<endl;
        }
        else if(s == "TreeUptodate")
        {
            if(m.Uptodate())                                // calling uptodate function
            {
                cout<<"YES"<<endl;
            }
            else
            {
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}
