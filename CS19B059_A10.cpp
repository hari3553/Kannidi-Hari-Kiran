#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Minsweeper{
    int **mat;                               // used to store mines
    int n;                                  // size of matrix
  public:  
    Minsweeper(int n);                       // constructor
    void setmine(int loc);                  // sets mine at location loc       
    bool isvalid(int a,int b);             // used to check whether point is valid
    int countmines(int a,int b);          // used for counting mines in adjacent cells of (a,b)
    int play(int a,int b); 
};


/************************************ CLASS MINSWEEPER FUNCTIONS START ***********************************************/


Minsweeper::Minsweeper(int n)
{
    this->n = n;                                 // stores size of matrix
    mat = new int*[n];                           // allocating memory to matrix dynamically
    
    for(int i=0;i<n;i++)
    {
        mat[i] = new int[n];
        for(int j=0;j<n;j++)
        {
            mat[i][j] = 0;                        // intialising all blocks in matrix as 0.
        }
    }
}

void Minsweeper::setmine(int loc)
{
    mat[(loc)/n][(loc)%n ] = -1;                  // storing -1 at loc to indicate the presence of mine
}


bool Minsweeper::isvalid(int a, int b)
{
    if(a>=0 && a<n)                               // checking whether a is valid
    {
        if(b>=0 && b<n)                           // checking whether b is valid
        {
            return true;
        }
    }
    
    return false;
}


int Minsweeper::countmines(int a, int b)
{
    int count = 0;                                     // intialising count with 0
    
    for(int i =0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
        {    
            if(isvalid(a+i-1,b+j-1) && mat[a+i-1][b+j-1] == -1)               // checking whether block contains mine
            {
                count++;
            }
        }
    }
    
    return count;
}




int Minsweeper::play(int a,int b)
{
    if(mat[a][b] == -1)                                   // checking whether block contains mine
    {
        return -1;
    }
    
    if(mat[a][b]!= 0)                                   // checking whether block is revealed
    {
        return 0;
    }
    
    int count = countmines(a,b);                      // counting number of mines present in adjacent cells of (a,b)
    
    if(count!= 0)
    {
        mat[a][b] = count;                           // updating block(a,b)
        return 1;                                    // 1 block is revealed
    }
    
    else
    {
        mat[a][b] = -2;                                  // updating block (a,b)
        count = 1;                                      //  incrementing count
     
        for(int i =0;i<=2;i++)
        {
            for(int j=0;j<=2;j++)
            {
               if(isvalid(a+i-1,b+j-1) && mat[a+i-1][b+j-1] == 0 )
                {
                     count+=  play(a+i-1,b+j-1);                      // updating count
                }
            }
        }
    }
    
    return count;
}


/********************************** CLASS MINSWEEPER FUNCTIONS END ***************************************************/



int main() {
    int n,m;
    cin>>n>>m;
    
    Minsweeper a(n);                             // Minsweeper game of size nxn
    int res = 0;                                 // used to store the result        
    int c,d;
    int k;
    
    for(int i=0;i<m;i++)
    {
        cin>>k;
        a.setmine(k);                               // setting mines
    }
    
   
    while(cin>>c>>d)
    {
        k =  a.play(c,d);
        
        if(k == -1 )                                  // checking whether mine is found
        {
            cout<<"Lost"<<endl;
            break;
        }
        
        else
        {
            res += k;
            if(res == n*n -m)                        // checking whether all blocks are revealed
            {
                cout<<"Won"<<endl;
                break;
            }
            else
            {
                cout<<res<<endl;
            }
        }
    }
    
    return 0;
}
