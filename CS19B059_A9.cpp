#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <iomanip>
using namespace std;


class Currencies{
    int n;                   // number of currencies
    int *colour;             // stores colour of vertices
    float **adj;            // currencies exchanging matrix
    int col_num;           // num of colors
    int** cmat;           // graph matrix of colour
  public:
    void getcolnum(int col_num);
    void addcoledge(int c1,int c2);
    void getcurrnum(int n);
    void addedge(int source,int target,float weight);
    void assigncolour(int curr,int col );
    double bellman(int source,int destination);
   
};

/********************************** CLASS CURRENCIES FUNCTIONS START**************************************************/


double Currencies::bellman(int source, int destination)
{
    double d[n];     // used to store maximum value that can be attained on conversion from start currency
    
    for(int i=0;i<n;i++)
    {
        d[i] = INT_MIN;      // intialising all d values to INT_MIN
    }
    d[source] = 1;
    
    for(int i=0;i<n-1;i++)                       // relaxing all edges v-1 times
    {
      for(int i=0;i<n;i++)
     {
        for(int j=0;j<n;j++)
        {
            if((cmat[colour[i]][colour[j]] == 1 || colour[i] == colour[j]) && (i!=j)) // searching for adjacent vertices
            {
                if(d[i]!= INT_MIN && d[i]*adj[i][j] > d[j])
                {
                    d[j] = d[i]*adj[i][j];            // updating the distance of j
                }
            }
        }
    }
    }
    if(d[destination] == INT_MIN)           // checking if there is no path from source to destination
    {
       return -1;
    }
    
    for(int i=0;i<n;i++) 
     {
        for(int j=0;j<n;j++)
        {
            if((cmat[colour[i]][colour[j]] == 1 || colour[i] == colour[j]) && (i!=j)) // searching for adjacent vertices
            {
                if(d[i]!= INT_MIN && d[i]*adj[i][j] > d[j]) // checking for increasing weight cycles
                {
                    return 0;
                }
            }
        }
    }
    
    return d[destination];                  
    
}

void Currencies::getcurrnum(int n)
{
    this->n = n;                  // stores number of currencies 
    adj = new float*[n];          // dynamically allocating memory for adjacency matrix
    colour = new int[n];         // dynamically allocating memory for colour graph matrix
    for(int i=0;i<n;i++)
    {
        adj[i] = new float[n];      
    }
}

void Currencies::addedge(int source, int target, float weight)
{
    adj[source][target] = weight;                
}

void Currencies::assigncolour(int curr, int col)
{
    colour[curr] = col;                  // assigning colour to currency 
}

void Currencies::getcolnum(int col_num)
{
    this->col_num = col_num;            // stores number of colours
    cmat = new int*[col_num];          // allocating memory dynamically to colour matrix
    for(int i=0;i<col_num;i++)
    {
        cmat[i] = new int[col_num];
        for(int j=0;j<col_num;j++)
        {
            cmat[i][j] = 0;
        }
    }
}

void Currencies::addcoledge(int c1, int c2)
{
    cmat[c1][c2] = 1;                   // adding edges if they are changeable
    cmat[c2][c1] = 1;
}

/*********************************** CLASS CURRENCIES FUNCTIONS END ***************************************************/


int main() {
     
    int c,m,a,b;
    Currencies C;
    cin>>c>>m;
    C.getcolnum(c);               // calling getcolnum function
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        C.addcoledge(a,b);       // calling addcoledge function
    }
    
    int n;
    cin>>n;
    C.getcurrnum(n);               // calling getcurrnum function
    for(int i=0;i<n;i++)
    {
        cin>>a;
        C.assigncolour(i,a);        // calling assigncolour function
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            float a;
            cin>>a;
            C.addedge(i,j,a);        // calling addedge function
        }
    }
    
    int q;
    cin>>q;
    while(q--)
    {
        int s,t,x;
        cin>>s>>t>>x;
        double res = C.bellman(s,t);    // calling bellman function
        
        if(res > 0)
        {
            res = res*x;                     // multiplying res with x
        printf("%.3lf\n",res);
        }
        else if(res == -1){
             cout<<res<<endl;
        }
        else
        {
            cout<<"INF"<<endl;
        }
    }
    return 0;
}
