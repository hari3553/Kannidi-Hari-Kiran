#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

template <class T> class Graph{
    int vertices;                           // indicates number of vertices in the graph
    int edges;                              // indicates number of edges in the graph
    list <pair<int,T>> *l;                   // adjacency list 
  public:
    Graph(int vertices,int queries);            //constructor
    ~Graph();                                   // destructor
    void addv();       
    void adde(int u,int v,T weight);
    void addtolist(int source,int dest,T weight);
    void dele(int u,int v);
    bool searchedge(int u,int v,T *p);
    void BFS(int v);
    void SSSP(int v);
};

/*************************** CLASS GRAPH FUNCTIONS START ***************************************************/


template <class T> Graph<T>::Graph(int vertices,int queries)
{
    this->vertices = vertices;                       // intialising num of vertices
    edges = 0;                                       // intialising num of edges
    l = new list<pair<int,T>>[vertices + queries];      //dynamically allocating memory to adjacency list 
    
    for(int i=0;i<vertices;i++)
    {
        pair <int,T> temp;                    // temporary variable to store vertex
        temp.first = i;
        temp.second = 0;
        l[i].push_back(temp);              // adding vertex in its own list as head
    }
    
}
  

template <class T> Graph<T>::~Graph()
{
    for(int i=0;i<vertices;i++)
    {
        l[i].clear();               // clearing all lists
    }
   
}


template <class T> void Graph<T>::addv()
{
   
    pair <int,T> temp;                         // temporary variable to store vertex
    temp.first = vertices;
    temp.second = 0;
    l[vertices].push_back(temp);             //  adding vertex in its own list as head
    vertices++;                              // updating num of vertices
    
}



template <class T> void Graph<T>::adde(int u, int v, T weight)
{
   if(u >= vertices || v >= vertices || u < 0 || v < 0)     // checking whether vertices are valid
    {
       cerr<<"Invalid indices"<<endl;
       return;
    }
    
    addtolist(u,v,weight);                       // adding vertex v in adjacency list of u
    addtolist(v,u,weight);                       // adding vertex u in adjacency list of v
    edges++;                                     // updating number of edges
}


/*****************************************************************************************************

* takes source vertex destination vertex and weight of the edge as arguments.

* searches for the appriopriate position of weight in source adjacency list.

* inserts the vertex v and weight w at iterator it so that the sorted proprty of list doesnt change.

*****************************************************************************************************/


template<class T> void Graph<T>::addtolist(int source,int dest,T weight)
{
    pair<int,T> temp;                //  stores the copy of new edge
    pair<int,T> elem;               // used to access the edges of source vertex
    
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



template <class T> void Graph<T>::dele(int u,int v)
{
    T weight;                                  // used to store the weight of edge uv if exists
    bool check;                                // used to check whether edge uv exists
    pair<int,T> edge1;                         // used to store elem in adjacency list of u
    pair<int,T> edge2;                         // used to store elem in adjacency list of u
    
    check = searchedge(u,v,&weight);          // searches for edge uv 
    
    if(!check)
    {
        cerr<<"Invalid edge"<<endl;               // prints error message if edge is not present
        return;
    }
    
    edge1.first  = v;                        // creating a copy of element in adjacency list of u
    edge1.second = weight;
    edge2.first  = u;                       // creating a copy of element in adjacency list of u
    edge2.second = weight;
    
    l[u].remove(edge1);                       // removing edge in adjacency list of u
    l[v].remove(edge2);                        // removing edge in adjacency list of u
  
}


template <class T> bool Graph<T>::searchedge(int u,int v,T *p)
{
    pair<int,T> temp;                     // used to store the weight of edge uv if exists
    
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



template <class T> void Graph<T>::BFS(int v)
{
    bool visited[vertices];                      // used to store the visited vertices 
    pair<int,T> temp;                         // used for accessing elements in adjacency list
    queue<int> q;                              // used to store vertices that are reachable from v
    int u;                                    
    
    
    for(int i=0;i<vertices;i++)
    {
        visited[i] = false;                      // marking all vertices as unvisited
    }
    
    visited[v] = true;
    q.push(v);                                    // pushing source vertex into the queue
    
    while(!q.empty())
    {
        u = q.front();                            
        q.pop();                                 // poping the top element of the queue
        
        cout<<u<<" ";
        
        for(auto it = l[u].begin();it!= l[u].end();it++)
        {
            if(it == l[u].begin())                // ignoring the popped vertex
            {
                continue;
            }
            
            temp = *it;
            if(visited[temp.first] == false)  // checking whether adjacent vertices of top vertex are visited
            {
                visited[temp.first] = true;       // marking vertex as visited
                q.push(temp.first);            // pushing the visited vertex into the queue
            }
        }
    }
    cout<<endl;
}
    


template <class T> void Graph<T>::SSSP(int v)
{
    vector<T> dist(vertices,INT_MAX);              // used to store the distances from source vertex
    dist[v] = 0;                         // marking source vertex distance as 0
    pair<T,int> m;                     // used to access top element of the priority queue
    pair<int,T> p;                    // used to access adjacent elements of top element of the priority queue
    int u ;
    
    priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<T,int>>> d; // priority queue d
    
   d.push(make_pair(dist[v],v));           // pushing source vertex and its distance
    while(!d.empty() )
    {
       
        m = d.top();                          // accessing the top element of the queue
        d.pop();                              // poping the top element of the queue
        
        u = m.second;                        
      
        
         for(auto it = l[u].begin();it!= l[u].end();it++)
        {
            if(it == l[u].begin())            // ignoring the head of the list
            {
                continue;
            }
          
            p = *it;
             
            if( dist[p.first] > dist[u] + p.second)  // updating the distances of adjacent vertices of top
            {
                
                dist[p.first] = dist[u] + p.second;
                d.push(make_pair(dist[p.first],p.first));  // pushing the updated distances into the queue
                
                
            }
        }
    }
    
    for(int i=0;i<vertices;i++)
    {
        cout<<dist[i]<<" ";    // printing distances of all vertices from the source vertec
    }
    cout<<endl;
    
}


/*************************** CLASS GRAPH FUNCTIONS END ***************************************************/


void queries(int q,Graph<int>&g)
{
     string s;               // stores input string
     int a,b,w;              // stores input vertices and weight
     while(q--)
    {
       
        cin>>s;
        if(s == "ADDV")
        {
            g.addv();                 // calling adv function
           
        }
        else if(s == "ADDE")
        {
            cin>>a>>b>>w;
           g.adde(a,b,w);             // calling add edge function
        }
        
         else if(s == "DELE")
        {
            cin>>a>>b;
           g.dele(a,b);                  // calling delete edge function
            
        }
    }
   
    int t=2;
    while(t--)
    {
        cin>>s;
        int a;
        if(s == "BFS")
        {
            cin>>a;
            g.BFS(a);             // calling BFS function
        }
        else if(s == "SSP")
        {
            cin>>a;
            g.SSSP(a);               // calling SSSP function
        }
    }
   
}

int main() {
    int q;                   // stores query number
    int v;                   // stores vertex number
    cin>>v>>q;
    Graph<int> g(v,q);             // graph g with v vertices
    queries(q,g);        
   
    return 0;
}
