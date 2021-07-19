#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class matrix{
    int n;                   // used to store the size of matrix //
    int **a;                // used to store the matrix dynamically //
 public:
    void creatematrix(int size);                 // creates matrix of (size)x(size)dimensions //
    void setelement(int i,int j,int k);          // stores k in a[i][j]//
    int getelement(int i,int j);                 // returns a[i][j] //
    int getrowsandcolumns();                     // returns size of the matrix either rows or columns //
    void ADDMatrix(matrix b);                    // adds matrix b with class matrix a //
    void SpecialSum();
    void ModMultiplication();
    void MatrixRightShift(int k);
    void MADD(matrix b,int x);
    void TransformMatrix();
    
    
};
/*************************** class functions start ************************************************/


    int matrix::getrowsandcolumns()
    {
        return n;
    }
    void matrix::setelement(int i,int j,int elem)
    {
        a[i][j] = elem;
    }
    int matrix::getelement(int i,int j)
    {
        return a[i][j];
    }

    void matrix::ADDMatrix(matrix b)
    {
        for(int i=0;i<n;i++)
          {
            for(int j=0;j<n;j++)
              {
                a[i][j] = a[i][j] + b.getelement(i,j);      // adding b[i][j] to a[i][j] //
                cout<<a[i][j]<<" ";
              }
          
            cout<<endl;
          }
    }
 

/**************************************************************

*creatematrix - Takes size as input and creats the matrix.

* Dynamically allocates memory for matrix.

* stores the size of the matrix.

**************************************************************/

    void matrix::creatematrix(int size)
    {
        n = size;                        // storing the size of matrix //
        a = new int*[size];             // dynamically allocating memory //
        
        for(int i=0;i<size;i++)
          {
            a[i] = new int[size];
          }
    }
    
    
/**************************************************************************

* SpecialSum - swaps the elements a[i][j] and a[j][i] if i+j is odd.

* temp is used for swapping the elements.

* after swapping computes the sum of each row.

**************************************************************************/

    void matrix::SpecialSum()
    {
        int temp;                 // temporary variable for swapping //
        int sum ;                 // used to store the sum of each row //
        
        for(int i=0;i<n;i++)
          { 
            for(int j=0;j<n;j++)
              {
                if(i<j &&(i+j)%2 !=0)          // checking the sum of i and j //
                  {
                    temp = a[i][j];
                    a[i][j] = a[j][i];
                    a[j][i] = temp;
                  }
              }
          }
        
        for(int i=0;i<n;i++)
          {
            sum = 0;
            
            for(int j=0;j<n;j++)
              {
                sum += a[i][j];          // computing the sum of each row //
              }
            
            cout<<sum;
            
            if(i!= n-1)
              {
              cout<<",";
              }
          }
        cout<<endl;
    }

/**************************************************************************************************************

* ModMultiplication - checks the remainder of each row number with n and computes the following:-

* if remainder is 0 then computes the maximum of the row.

* if remainder is 1 then computes the minimum of the row.

* else computes the floor of average of elements of the row.

* prints the product of all computed values.

***************************************************************************************************************/


    void matrix::ModMultiplication()
    {
        int max;                 // used to store the maximum of each row //
        int min;                 // used to store the minimum of each row //
        int sum;                 // used to store the sum of each row //
        int rem;                 // used to the remainder of each row when divided by n //
        long long int  prod=1;   // used to store the product //
        
        for(int i=0;i<n;i++)
          {
            max = a[i][0];
            min = a[i][0];
            sum=0;
            
            for(int j=0;j<n;j++)
              {
                if(max < a[i][j])
                  {
                    max = a[i][j];
                  }
                if(min > a[i][j])
                  {
                    min = a[i][j];
                  }
                sum = sum+a[i][j];          // computing sum of ith row //
              }
            
              rem = (i%3);                   // computing remainder of ith row //
              switch(rem){
                case 0: 
                    prod = prod* max;         
                    break;
                    
                case 1:
                    prod = prod*min;
                    break;
                default:
                    prod = prod*floor(sum/n); 
                       }              
          }
        
        cout<<prod<<endl;
    }
  
/*********************************************************************************************

* MatrixRightShift - takes input k and right shifts the matrix k times.

* shifts each element position to its right such that last element is shifted to 1st place.

* continues the same process for k times.

*********************************************************************************************/
    
    void matrix::MatrixRightShift(int k)
    {
        int elem;                      // used to store the last element of the array //
        
        for(int l=0;l<k;l++)
          {
            elem = a[n-1][n-1];
            
            for(int i=n-1;i>=0;i--)
              {
                for(int j=n-1;j>=0;j--)
                  {
                    if(j==0 && i!=0)
                      {
                        a[i][j] = a[i-1][n-1];         // shifting n-1th element of i-1th row to i,j //                 
                      }
                    else if(i==0 && j==0)
                      {
                        a[i][j] =elem;                  // storing last element in first place //
                      }
                    else
                      {
                        a[i][j] = a[i][j-1];            // shifting each element to its right //
                      } 
                  }
              }
          }
    }

/*******************************************************************************

* Transform matrix - transforms the matrix to its transpose.

* swaps a[i][j] with a[j][i] using temporary variable.

*******************************************************************************/

    void matrix::TransformMatrix()
    {
        for(int i=0;i<n;i++)
          {
            for(int j=0;j<n;j++)
              {
                if(i<j)
                 {
                    int temp = a[i][j];          // storing a[i][j] in temp //
                    a[i][j]  = a[j][i];          // storing a[j][i] in a[i][j] //
                    a[j][i]  = temp;            // storing temp in a[j][i] //
                 }
              }
          }
    }
    

/*******************************************************

* MADD - Takes matrix and integer as input .

* if input integer is 1 then transforms the class matrix.

* if input integer is 2 then transforms the input matrix.

* prints the sum of transformed matrix and other matrix.

*********************************************************/

    void matrix::MADD(matrix b,int x)
    {
        if(x==1)
          {
            TransformMatrix();              // transforming matrix a //
          }
        if(x == 2)
          {
            b.TransformMatrix();            // transforming matrix b //
          }
        ADDMatrix(b);                      // adding matrix b to a //
    }
 

/********************************* class functions end *****************************************/

int main() {
    int q;                   // used to store number of queries //
    int n;                  // used to store size of matrix //
    int value;              // used to store the input value // 
    int matrix1[50][50];    // used to store the elements of 1st input matrix //
    int matrix2[50][50];     // used to store the inputs of 2nd input matrix //
    
    cin>>q;
    cin>>n;
    
    for(int i=0;i<n;i++)
      {
        for(int j=0;j<n;j++)
          {
            cin>>matrix1[i][j];
          }
      }
    for(int i=0;i<n;i++)
     {
       for(int j=0;j<n;j++)
         {
            cin>>matrix2[i][j];
         }
     }
    
   while(q--)
    {
        matrix a,b;                  // creating two matrices //
        a.creatematrix(n);
        b.creatematrix(n);
        for(int i=0;i<n;i++)
          {
            for(int j=0;j<n;j++)
              {
                a.setelement(i,j,matrix1[i][j]);        // storing elements in the class matrices //
                b.setelement(i,j,matrix2[i][j]);   
              }
          }
        string s;                 // used to store the input string //
        cin>>s;
        if(s == "SPSUM")
          {
             a.SpecialSum();        // calling SpecialSum function in class a //
          }
        else if(s == "MOD" )
          {
            a.ModMultiplication();     // calling ModMultiplication function in class a //
          }
        else if(s == "MRS")
          {
          
            cin>>value;
            a.MatrixRightShift(value);         // calling MatrixRightShift function in both classes and adding them //
            b.MatrixRightShift(value);
            a.ADDMatrix(b);
          
          }
        else
         {
           
            cin>>value;
            a.MADD(b,value);          // calling MADD function in class a //
         }
    }
   
    return 0;
}