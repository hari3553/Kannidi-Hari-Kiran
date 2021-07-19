#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

struct Node               // nodes of linked list //
{
    int elem;             // element stored in node //
    Node* next;           // next pointer //
};

class Stack{
    
  Node* Top;            // pointer to the top of the stack //
    
  public :
    Stack();               // constructor //
    int top();             // returns top of the stack //
    int pop();            // pops out the top elem //
    int empty();          // checks whether stack is empty //
    void push(int x);     // pushes new element into the stack //
};

class Graph{
    int** adj;                          // adjacency matrix //
    int  vertices;                      // denotes number of vertices //
  public :
    Graph(int v);                               // constuctor //
    void operator+=(pair<int,int> p);
    void operator-=(pair<int,int> p);
    bool dfsRec(int s,int p,bool visited[]);        // recursive dfs //
    void dfsStack(int source,bool visited[]);       // stack dfs //
    int  detectcycle();
    int components();
    int reach(int u,int v);
   
        
    
};


/*******************************CLASS Stack FUNCTIONS START **********************************************************/


Stack::Stack()
{
    Top = new Node[1];          // allocating memory to the top //
    Top = NULL;
}

int Stack::top()
{
    if(Top == NULL)
    {
        return -1;
    }
    return Top->elem;
}
int Stack::pop()
{
    if(Top == NULL)
    {
        return -1;
    }
    int elem;
    elem = Top->elem;                      // storing top element //
    Top = Top->next;                       // updating the top //
    return elem;
}
int Stack::empty()
{
    if(Top == NULL)
    {
        return 1;
    }
    return 0;
}
void Stack::push(int x)
{
    Node* temp;                           // used to store new element //
    temp = new Node;                     // allocating memory dynamically //
    temp->elem = x;
    temp->next = Top;                  // adding elem at the top //
    Top = temp;                        // updating the top //
}

/************************************** CLASS Stack FUNCTIONS END ****************************************************/


/************************************** CLASS Graph FUNCTIONS START **************************************************/


Graph::Graph(int v)
{
    vertices = v;                          // storing num of vertices //
    adj = new int*[v];                     // allocating memory dynamically //
    for(int i=0;i<v;i++)
    {
        adj[i] = new int[v];
        for(int j=0;j<v;j++)
        {
            adj[i][j] = 0;
        }
    }
}

void Graph::operator+=(pair<int,int> p)
{
    adj[p.first][p.second] = 1;                // adding edge p.first p.second //
    adj[p.second][p.first] = 1;
}

void Graph::operator-=(pair<int,int> p)
{
    adj[p.first][p.second] = 0;
    adj[p.second][p.first] = 0;                  // deleting edge p.first p.second //
}

/*************************************************************************************

* dfsRec - takes source vertex ,visited array ,parent vertex as inputs.

* recursively calls dfs function .

* checks whether all adjacent vertices of source vertex are visited.

* if any of adjacent vertex is visited and not equal to parent then returns true.
**************************************************************************************/

bool Graph::dfsRec(int s, int p,bool visited[])
{
    visited[s] = true;                 // marking source vertex as visited //
    for(int i=0;i<vertices;i++)
    {
        if(adj[i][s] == 1 && i!=s)
        {
            if(visited[i] == false)            // if not visited and adjacent then calls recursively //
            {
                if(dfsRec(i, s, visited))
                {
                    return true;              
                }
            }
          else if(i!=p)
            {
              return true;            // if visited and not equal to parent returns true //       
            }
        }             
    }
  return false;
}

/************************************************************************************

* performs  dfsStack function on unvisited vertices .

* number of components = no of dfsStack function called in the components function.

*************************************************************************************/

int Graph::components()
{
    bool visited[vertices];             // used to mark the vertices as visited //
    int count =0;                       // used to store the count of calls of dfsStack function //
    for(int i=0;i<vertices;i++)
    {
        visited[i] = false;              // marking all vertices as not visited //
    }
    for(int i=0;i<vertices;i++)
    {
        if(!visited[i])
        {
            dfsStack(i,visited);                // calling dfsStack function for not visited vertices //
            count++;                           // incrementing the count //
        }
    }
    return count;
      
}

/********************************************************************************************************************

* Performs dfsStack function with source vertex as u.

* if vertex is v is not visited after dfsStack function then it is present in other component and cant be reached.

* else it can be reached from u.

********************************************************************************************************************/

int Graph::reach(int u, int v)
{
    bool visited[vertices];                   // used to mark the vertices as visited //
    
    for(int i=0;i<vertices;i++)
    {
        visited[i] = false;                    // marking all vertices as not visited //
    } 
    
    dfsStack(u,visited);                    // calling DFs stack function //
    
    if(visited[v])                       // checking whether vertex v is visited //
    {
        return 1;
    }
    return 0;
}

/**************************************************************

* Performs dfsRec on  unvisited vertices.

* if any of the dfsRec returns 1 then a cycle is detected.

* else no cycle is present.

**************************************************************/

int Graph::detectcycle()
{
   bool visited[vertices];                                // used to mark the vertices as visited // 
    
    for(int i=0;i<vertices;i++)
    {
        visited[i] = false;                               // marking all vertices as not visited //
    }
    for(int i=0;i<vertices;i++)
    {
        if(visited[i] == false)
        {
            if(dfsRec(i,-1,visited))            // calling dfsrec with i as source and -1 as parent //
            {
                return 1;
            }
        }
    }
    return 0;
}

/************************************************************************************************

* Uses Stack to perform Dfs.

* Marks the source vertex as visited.

* Pushes source vertex into the stack.

* pops out the top vertex and marks it as visited.

* pushes all adjacent vertices of top which are not visited.

* this process repeats until stack becomes empty.

***************************************************************************************************/


void Graph::dfsStack(int source,bool visited[])
{
    visited[source] = true;              // marking source vertex as visited //
    Stack s;
    s.push(source);                      // pushing source vertex into the stack //
    int u;                               // used to store the top vertex //
    while(!s.empty())
    {
       u = s.pop();                      // poping the top vertex //
       visited[u] = true;                // marking top vertex as visited //
       for(int j=0;j<vertices;j++)
        {
          if(adj[j][u] == 1 && !visited[j])           // pushing all adjacent vertices of u if they are not visited //
          {
            s.push(j);
          }
        }
     }
   
}

/***************************************** CLASS Graph FUNCTIONS END *************************************************/


int main() {
    int q;                 // used to store the query number //
    Stack a;               // stack a //
    int v;                 // used to store number of vertices //
    cin>>q;
    while(q--)
    {
        string s;              // used to store the input string //
        int res;               // used to store the returned element //
        int elem;              // used to store the input element //
        cin>>s;
        if(s== "top")
        {
            res = a.top();
            cout<<res<<endl;
        }
        else if(s== "pop")
        {
             res = a.pop();
            cout<<res<<endl;
        }
         else if(s== "empty")
        {
             res = a.empty();
            cout<<res<<endl;
        }
        else
        {
            
            cin>>elem;
            a.push(elem);
        }
        
    }
    
   
    cin>>v;
    Graph g(v);              // creating graph with vertices = v //
    cin>>q;
    
    while(q--)
    {
        string s;             // used to store the  input string //   
        int x,y;              // used to store the vertices //
        pair<int,int> p;      // used to store vertex pair //
        int res;               // used to store the result //
        cin>>s;
        
        if(s== "add")
          {
            
            cin>>x>>y;
            p.first = x;
            p.second = y;
            g+=p;                          // adding edge x,y //
          }
         else if(s== "del")
           {
            
            cin>>x>>y;
            p.first = x;
            p.second = y;
            g-=p;                           // deleting edge x,y //
           }
        else if(s=="cycle")
        {
            res=  g.detectcycle();           // detecting cycle //
            cout<<res<<endl;
        }
        else if(s == "components")
        {
            res = g.components();             // calling component function //
            cout<<res<<endl;
        }
        else
        {
            
            cin>>x>>y;
            res = g.reach(x,y);                 // calling reach function //
            cout<<res<<endl;
        }
    }
    return 0;
}
