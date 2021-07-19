#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{
    
private:
    int rows;                                // used to num of rows  //
    int columns;                            // used to num of columns  //
    int **a;                               // used to store the matrix dynamically //

public:
    void creatematrix(int n,int m);                // creates matrix of (n)x(m)dimensions //
    void setelement(int i,int j,int elem);         // stores k in a[i][j]//
    int  getelement(int i,int j);                  // returns a[i][j] //
    int  getrows();                                // returns num of rows //
    int  getcolumns();                            // returns num of columns //
    int  findmaxelem();                           // returns max elem of matrix //
    int  findminelem();                           // returns min elem of matrix //
    int  binarysearch(int x,int k);
    int* matrixsearch(int x);
    
};


class MatrixMedian : public Matrix{
    
public:
    int upperbound(int x,int k);
    int median();
    
}; 

/********************************** CLASS MATRIX FUNCTIONS START **************************************************/


/**************************************************************

*creatematrix - Takes size as input and creats the matrix.

* Dynamically allocates memory for matrix.

* stores the size of the matrix.

**************************************************************/

void Matrix::creatematrix(int n, int m)
{
   rows = n;                             // storing the size of matrix //
   columns =m;
   
   a = new int*[rows];
   for(int i=0;i<rows;i++)
     {                                                
       a[i] = new int[columns];                  // dynamically allocating memory //
     }   
}

void Matrix::setelement(int i,int j,int elem)
{
    a[i][j] = elem;
}

int Matrix::getelement(int i,int j)
{
    return a[i][j];
}

int Matrix::getcolumns()
{
    return columns;
}

int Matrix::getrows()
{
    return rows;
}

int Matrix::findmaxelem()
{
    int max;
    max = a[0][columns-1];
    for(int i=0;i<rows;i++)
      {
        if(max < a[i][columns-1])
          {
            max = a[i][columns-1];  
          }
      }
    return max;
}
int Matrix::findminelem()
{
    int min;
    min = a[0][0];
    
    for(int i=0;i<rows;i++)
      {
        if(min > a[i][0])
          {
            min = a[i][0];  
          }
      }
   return min;  
}


/********************************************************************************************************************

* binarysearch - Takes input x,k and returns largest index j such that a[k][j] <= x .

* low and high point to starting and ending of the row intially.

* if the mid element is less than or equal to x then store the index of mid and search for the part [mid+1,high].

* else search in the part [low,mid-1] as all elements in [mid,high] will be greater than x.

* time complexity - O(log m).

**********************************************************************************************************************/


int Matrix::binarysearch(int x, int k)
{
    if(x < a[k][0])     //checking whether x is less than the 1st element of the kth row //
     {
        return -1;
     }
    int low = 0;            // iterator used to point least element //
    int high = columns-1;   // iterator used to point greatest element //
    int mid;
    int index= -1;
    while(low<=high)
     {
        mid = (low+high)/2;
        if(a[k][mid] <= x)  // checking whether mid element is less than or equal to x //
        {
            index =  mid;           // storing mid in index //
            low   = mid+1;          // moving low iterator //
        }
        
       else 
         {
           high = mid-1;            // moving high iterator //
         }
     }
    return index;           // returns the largest index such that a[k][index] <= x //
}


/*********************************************************************************************************

* matrixsearch - takes input x and returns i,j if a[i][j] =x else returns -1 if x  is not present.

* apply binary search in each row until x is found.

* modify binarysearch such that it searchs the leftmost occurence of x.

* if mid element equals to x store the mid index and again search in the part [low,mid-1].

* time complexity - O(n*log m).

************************************************************************************************************/


int* Matrix::matrixsearch(int x)
{
    int* index;               // used to store the coordinates i,j //
    bool found;               // used to check whether x is present in matrix //
    int low;                   // iterator used to point least element //         
    int high;                  // iterator used to point greatest element //
    int mid;                   // iterator used to point mid element in [low,high] //
    
    index = new int[2];               // dynamically allocating memeory to index //
    found = false;                    // intialising found to false //
    
    index[0] = -1;
    index[1] = -1;
    
    for(int i=0;i<rows && !(found);i++)      // checking x in ith row if it is not present previosly //
       {
         low = 0;
         high = columns -1;
         while(low<= high)
           {
               mid = (low+high)/2;
            
              if(a[i][mid] == x)         // checking whether mid element = x //
                {
                   index[0] = i;           // storing values of i  and mid in index //
                   index[1] = mid;
                   found    = true;          // assigning true to found //
                   high     = mid-1;         // moving high iterator to left //
                }
              else if(a[i][mid] < x)         // checking whether mid element < x //
               {
                   low = mid+1;              // moving low iterator to right //
               }
              else
               {
                   high = mid-1;           // moving high iterator to left //
               }
           }
        
       }
    
       return index;                      // returns (i,j) if a[i][j] =x or (-1,-1) if x is not present in matrix //
}

/**************************** CLASS MATRIX FUNCTIONS END ***********************************************************/



/********************************** CLASS MATRIXMEDIAN FUNCTIONS START **********************************************/


int MatrixMedian::upperbound(int x, int k)
{
    int index;           // used to store the upperbound //
    int columns;         // used to store number of columns in matrix //
    
    columns = getcolumns();                     // storing num of columns //
    index = binarysearch(x,k);                 // finding largest index such that a[k][index] <= x //
    
    if(index == columns-1)
    {
        return -1;
    } 
    else
    {
        return (index+1);           // returning index +1 //
    } 
    
}


/*************************************************************************************************

* median() - finds the median of the matrix.

* apply binary search in the range (min,max).

* find out the element m such that number of elements less than or equal to x =(n*m +1)/2.

* if count < (n*m +1)/2 then search in [mid+1,max];

* else search in [min,mid].

* time complexity - O(n*log m).

****************************************************************************************************/


int MatrixMedian::median()
{
    int min;                    // used to store the min of matrix //
    int max;                    // used to store the max of matrix //
    int count;                 
    int pcount;                 // used to store number of elements <= mid  in matrix //
    int mid;
    int rows,columns;           // used to store numof rows and columns //
    int ubound;                 // used to store value returned from upperbound function //
    
    min     = findminelem();
    max     = findmaxelem();
    rows    = getrows();
    columns = getcolumns();
    count   = (rows*columns +1)/2;
    
    
    
    while(min < max)
    {
        
        mid    = min + (max-min)/2;
        pcount = 0;
        for(int i=0;i<rows;i++)
        {
            ubound = upperbound(mid,i);          // calculating smallest j such that a[i][j]>mid //
            
            if(ubound!= -1) 
            {   
                pcount += ubound;   
            }
            else           // all elements in the row are less than or equal to mid //
            {
                pcount+= columns;
               
            }
           
        }
        if(pcount < count) // there are more elements in the right of mid so median lies in the right //
        {
            min = mid +1 ;
        }
        else  // more elements are present in left of median so median lies in the left //
        {
            max = mid ;
        }
        
    }
  
   return min; 
}

/*************************************** CLASS MATRIXMEDIAN FUNCTIONS END ********************************************/

int main() {
       
    int n,m;           // used to store numof rows and columns //
    int elem;          // used to read elements //
    int q;              // used to store num of queries //
    Matrix a;             // matrix a //
    MatrixMedian b;       // matrixmedain b //
    cin>>n>>m;
    a.creatematrix(n,m);       // creating matrix and matrixmedian //
    b.creatematrix(n,m);
    
    for(int i=0;i<n;i++)
     {
        for(int j=0;j<m;j++)
         {
            
            cin>>elem;
            a.setelement(i,j,elem);
            b.setelement(i,j,elem);       // storing elements in matrix and matrixmedian //
         }
     }
    
    cin>>q;
    while(q--)
     {
        string s;
        int x;
        int k;
        int result;         // used to store result //
        int *index;         // used to store the indices i,j //
        
        cin>>s;
        if(s == "BS")       // checking whether s= BS //
          {
            cin>>x>>k;
            result = a.binarysearch(x,k);       // calling binarysearch //
            cout<<result<<endl;
          }
        else if(s == "MS")        // checking whether s= BS //
          {
            cin>>x;
            index =  a.matrixsearch(x);           // calling matrixsearch //
            cout<<index[0]<<" "<<index[1]<<endl;
          }
        else
         {
            result=b.median();                   // calling median //
            cout<<result<<endl;
         }
        
     }
    return 0;
}