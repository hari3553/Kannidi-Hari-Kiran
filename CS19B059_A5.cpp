#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


int Max(int a,int b,int c)
{
   int d = a>b ? a:b;
   int e = d>c ? d:c;
   return e;   
}


struct room{
    int seraphic ;                              // stores seraphic number of the room
    bool occupy;                               // denotes the occupancy of the room
};

class Boombrain{
  int   size;                                      // denotes the size of the center
  room* center;                                    // represents rooms in center 
 public :
    Boombrain(int n);
    long long int update(int arr[]);
    void join(int x);
    void leave(int x);
    int  occupied();
    int  play();
    int  Maxsubarray(int arr[],int low,int high);
    int  Maxcrossingsubarray(int arr[],int low,int mid,int high);
    long long int talk();
    long long int Countinv(int arr[],int l,int h);
    long long int Countmerge(int arr[],int l,int m,int h);
};


/********************************* CLASS FUNCTIONS START **************************************************************/


Boombrain::Boombrain(int n)
{
    size =n;                                              // upadting size of  the center
    center = new room[n];                                // dynamically allocating memory
    for(int i=0;i<size;i++)
    {
        center[i].occupy = true;                         // marking all rooms in the center as occupied
    }
    
}
long long int Boombrain::update(int arr[])
{
    long long int talkcount;                           // used to store total number of talks
    
    for(int i=0;i<size;i++)
    {    
      center[i].seraphic = arr[i];                       // upadating seraphic numbers of rooms
    }
    
    talkcount= talk();                                  // calling talk function
    return talkcount;
}

void Boombrain::join(int x)
{
   for(int i=size-1;i>=0;i--)
   {
       if(!center[i].occupy)                                         // searching for last unoccupied room
       {
           center[i].seraphic = x;                                 // updating room seraphic number to x
           center[i].occupy   = true;                             // marking the room as occupied
           return;
       }
   }
    
}

void Boombrain::leave(int x)
{
    
    center[x].seraphic = 0;                                      // assigning 0 to seraphic number of room at xth index 
    center[x].occupy   = false;                                 // marking the room as unoccupied
   
}

int Boombrain::occupied()
{
    int count =0 ;                                    // used to store total num of occupied rooms
    
    for(int i=0;i<size;i++)
    {
        if(center[i].occupy)
        {
            count++;                             //  checking whether room is occupied and incrementing the count
        }
    }
    return count;
}

int Boombrain::play()
{
    int arr[size];                        // temporary array to store the seraphic numbers of occupied rooms
    int n=0;                              // stores the size of temporary array
    int res;                              // used to store maximum subarray sum
    for(int i=0;i<size;i++)
    {
        if(center[i].occupy)
        {
            arr[n] = center[i].seraphic;
            n++;
        }
    }
    res = Maxsubarray(arr,0,n-1);                   // calling Maxsubarray
    return res;
}

/***************************************************************************

* if low and high are equal then returns arr[low].

* calculates maximum  sum of subarray in left part.

* calculates maximum sum of subarray in  right part.

* calculates maximum sum crossing mid.

* returns the max of among all three.

******************************************************************************/


int Boombrain::Maxsubarray(int arr[], int low, int high)
{
    if(low == high)
    {
        return arr[low];
    }
    
    int mid;                             // represents the mid in (low,high) 
    int max_sum_left;                    // stores maximum sum in (low,mid)
    int max_sum_right;                  // stores maximum sum in (mid+1,high)
    int max_crossing_sum;                // stores max sum crossing mid in (low,high)
    
    mid              = (low+high)/2;
    max_sum_left     = Maxsubarray(arr,low,mid);
    max_sum_right    = Maxsubarray(arr,mid+1,high);
    max_crossing_sum = Maxcrossingsubarray(arr,low,mid,high);
    
    return Max(max_sum_left,max_sum_right,max_crossing_sum);         // returns max among all three
    
}


/***********************************************************************

* calculates max prefix sum in (low,mid)

* calculates max suffix sum in (mid+1,high)

* adds both the sums and returns it

**********************************************************************/



int Boombrain::Maxcrossingsubarray(int arr[], int low, int mid, int high)
{
    int left_sum;                        // used to store maximum prefix sum of (low,mid)
    int right_sum;                       // used to store maximum suffix sum of (mid+1,high)
    int sum1;                            // used to calculate prefix sum
    int sum2;                           // used to calculate suffix sum
    int k;
    
    left_sum  = INT_MIN;                  // intialising maximum prefix sum to INT_MIN
    right_sum = INT_MIN;                  // intialising maximum suffix sum to INT_MIN              
    sum1      = 0;                        // intialising prefix sum to 0
    sum2      = 0;                        // intialising suffix sum to 0
    k         = 0;
    
    for(int i=mid;i>=low;i--)
    {
        sum1     += arr[i];
        left_sum  = sum1 > left_sum ? sum1 : left_sum;         // storing max(sum1,left_sum) in left_sum
        
        if(i+2*k+1 <= high)
        {
         sum2     += arr[i+2*k+1];
         right_sum = sum2 >right_sum ? sum2 : right_sum;         // storing max(sum2,right_sum) in right_sum
         k++;
        }   
    }
    
    return (left_sum + right_sum);                         // returning max sum crossing mid 
}


long long int Boombrain::talk()
{
    int arr[size];                               // temporary array to store the seraphic numbers of occupied rooms
    long long int res;                          // used to store number of talks 
    int n=0;                                    // stores the size of temporary array 
    for(int i=0;i<size;i++)
    {
        if(center[i].occupy)
        {
            arr[n] = center[i].seraphic;
            n++;  
        }
    }
    res = Countinv(arr,0,n-1);                    // calling Countinv function on (0,n-1)
    
    return res;
}

long long int Boombrain::Countinv(int arr[], int l, int h)
{
   long long int res =0;                          // used to store number of inversions
    if(l<h)
    {
        int m = l +(h-l)/2;
        res += Countinv(arr,l,m);                       // adds number of inversions in (l,m) to res
        res += Countinv(arr,m+1,h);                     // adds number of inversions in (m+1,h) to res
        res += Countmerge(arr,l,m,h);                  // adds number of inversions in (l,m,h) to res
    }
    return res;
}


/**********************************************************************************************************************

*Uses idea of Merge sort.

* left array stores elements in [low,mid].

* right array stores elements in [mid+1,high].

* merges leftarray and rightarray.

* While merging if left[i] is found greater than right[j] then all elements in [i,mid] form ann inversion with right[j].

***********************************************************************************************************************/


long long int Boombrain::Countmerge(int arr[], int l, int m, int h)
{
    int lsize;                              // stores size of left array
    int rsize;                             // stores size of right array
    long long  int res;                   // stores num of inversions
    long long  int i;                     // index pointer for left array
    long long  int j;                     // index pointer for right array
    long long  int k;                    
    
    lsize = m-l+1;
    rsize = h-m;
    res   = 0;
    i     = 0;
    j     = 0;
    k     = l;
    
    int left[lsize];                // left array
    int right[rsize];               // right array
    
    for(int i=0;i<lsize;i++) 
    {
        left[i] = arr[l+i];                  // copying elements in [low,mid] into left array
    }
    for(int i=0;i<rsize;i++)
    {
        right[i] = arr[m+i+1];               // copying elements in [mid+1,high] into right array
    }
    
   
    while(i<lsize && j<rsize)
    {
        if(left[i] <= right[j])
        {
            arr[k++] = left[i];
            i++;
        }
        else
        {
            arr[k++] = right[j];
            j++;
            res += lsize-i;                       // storing inversions 
        }
    }
    
    while(i<lsize)                                 // if right array is exhausted before left array
    {
        arr[k++] = left[i++];                     
    }
    
    while(j<rsize)                                // if left array is exhausted before right array
    {
        arr[k++] = right[j++];
    }
    return res;
    
}


/************************************** CLASS FUNCTIONS END **********************************************************/


int main() {
    
    int n;                    // stores num of rooms in center
    int q;                    // stores query number
    cin>>n>>q;
    
    int arr[n];                // used to scan input seraphic numbers
    Boombrain b(n);           // boombrain class b
    
    while(q--)
    {
        string s;
        long long int talk;              // stores num of talks
        int  seraphic;                   // stores the input seraphic number when join is called
        int  index;                      // stores the input index when leave is called 
        long long  int res;              // stores minimum guru value
            
        cin>>s;
        
        if(s== "update")
        {
           
            for(int i=0;i<n;i++)
            {
                cin>>arr[i];
            }
            
           talk =b.update(arr);                 // calling upadate function with argument as array
           cout<<talk<<endl;
        }
        else if(s == "join")
        {
            
            cin>>seraphic;
            b.join(seraphic);                   // calling join function
        }
        else if(s == "leave")
        {
            
            cin>>index;
            b.leave(index);                 // calling leave function
        }
        else if(s == "occupied")
        {
            res = b.occupied();             // calling occupied function
            cout<<res<<endl;
        }
        else if(s == "play")
        {
            res = b.play();                // calling play function
            cout<<res<<endl;
        }
    }
}
