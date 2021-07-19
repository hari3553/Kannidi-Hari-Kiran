#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int min(int a,int b)
{
    return a>b ? b:a;                 // returns minimum of (a,b)
}

class EDD{
    string str1;                        // stores 1st string
    string str2;                       //  stores 2nd string
    int **mat;                         // stores matrix used for dynamic programming
    bool assigned = false;            // checks whether string are intialised
    bool compt = false;              // checks whether matrix is updated
    
  public:      
    void assign(string str1,string str2);
    void comptdist();
    int dist();
    void table();
};

/************************************ CLASS EDD FUNCTION START ********************************************************/


void EDD::assign(string str1,string str2)
{
    this->str1 = str1;                           // storing 1st string in str1
    this->str2 = str2;                           // stroing 2nd string in str2
    assigned = true;                            // strings are intialised
    compt = false;                              // matrix is not updated 
    
    int rows = str1.length();                  // num of rows = length of 1st string
    int coloumns = str2.length();              // num of columns = length of 2nd string
    mat = new int*[rows];                      // dynamically allocating memory to mat
    
    for(int i=0;i<rows;i++)
    {
        mat[i] = new int[coloumns];           // dynamically allocating memory to each row of mat
    }
}


void EDD::comptdist()
{
    if(!assigned)                              // checking whether the strings are not intialised
    { 
        throw "strings not found!";            // throwing exception                
        
    }
    
    compt = true;                             // updating the matrix
    int path1;                               // describes that removing a character from 1st string leads to 2nd string
    int path2;                              // describes that inserting a character into 1st string leads to 2nd string
    int path3;                             // describes that replacing a character from 1st string leads to 2nd string
    int temp ;
    
    for(unsigned long int i=0;i<str1.length();i++)
    {
        for(unsigned long int j=0;j<str2.length();j++)
        {
            temp = -1;
            path1 = (i == 0) ? j+1 : mat[i-1][j] + 1;   // addding 1 to mat[i-1][j] as remove operation is performed.
            path2 = (j == 0) ? i+1 : mat[i][j-1] + 1;  // adding 1 to mat[i][j-1] as insert operation is performed.
            
            if(i == 0 || j ==0)
            {
              temp = (i == 0) ? j : i;                
            }
            
            path3 = (temp == -1) ? mat[i-1][j-1] : temp;
            path3 = (str1[i] == str2[j]) ? path3 : path3+1;   // if characters are not equal performs replace operation
            mat[i][j]  = min(path3,min(path1,path2));         // returning minimum of three paths
        }
    }
}


int EDD::dist()
{
    if(!assigned)                                             // checking whether the strings are not intialised
    {
         throw "strings not found!";                          // throwing exception 
         
    }
    if(!compt)                                               // checking if the matrix is not updated
    {
        comptdist();                                        // updating matrix
    }
    
    return mat[str1.length()-1][str2.length()-1];          // returning last element of the matrix
}



void EDD::table()
{
    if(!assigned)                                           // checking whether the strings are not intialised
    {
         throw "strings not found!";                        // throwing exception 
        
    }
    if(!compt)                                              // checking if the matrix is not updated
    {
        comptdist();                                       // updating matrix
    }
    
    
    for(unsigned long int i=0;i<str1.length();i++)
    {
        for(unsigned long int j=0;j<str2.length();j++)
        {
            cout<<mat[i][j]<<" ";                                   // printing the elements of matrix 
        }
        cout<<endl;
    }
    
}

/************************************ CLASS EDD FUNCTIONS END *********************************************************/


int main() {
       int q;                                                    // used to store querynum
       string s;                                                // used to store input command
       string s1;                                              // used to store 1st string
       string s2;                                              // used to store 2nd string
       int res;                                                // used to store edit distance
       
       cin>>q;                                                 
       EDD d;                                               // object d of class EDD                
       
       while(q--)
       {
         cin>>s;
         
         if(s == "assign")
         {
           cin>>s1>>s2;
           d.assign(s1,s2);                                        // calling assign function
         }
         
         else if(s == "compdist")
         {
           try
            {
              d.comptdist();                                      // calling comptdist function
            }
           catch(string msg)
            {
              cout<<msg<<endl;
            }
         }
         
         else if(s == "table")
         {
           try
            {
              d.table();                                           // calling table function
            }
           catch(string msg)
            {
              cout<<msg<<endl;
            }
         }
         
         else if(s == "dist")
         {
            
           try
            {
              res = d.dist();                                     // calling dist function
              cout<<res<<endl;
            }
           catch(string msg)
            {
              cout<<msg<<endl;
            }
         }
       }
       
    return 0;
}
