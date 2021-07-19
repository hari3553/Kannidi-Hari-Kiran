#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

 template <class T> class Vector{
  size_t capacity;              // denotes capacity
  size_t currentSize;          // denotes size
  T*vec;                       // vec to store elements
public:
      Vector();                 // constructor
     ~Vector();                // destructor
      Vector(size_t c);        // constructor
      Vector(size_t c,T x);    // constructor
      size_t Capacity();      
      size_t CurrentSize();
      void push(T x);
      void Newvector(size_t c);
      void pop();
      T  front();
      T  back();
      T  operator[](size_t i);
      void qsort(size_t low,size_t high);
      void sort();       
protected:     
      size_t partition(size_t l,size_t h);
};


/******************************* TEMPLATE FUNCTIONS START ************************************************************/

template <class T> Vector<T>::Vector()
{
    currentSize = 0;           // assigning 0 to size
    capacity    = 1;           // assigning 1 to capacity
    vec         = new T[1];    // dynamically allocating memory
}

template <class T>  Vector<T>::Vector(size_t c)
{
    capacity        = c;            // assigning c to capacity
    currentSize     = 0;           // assigning 0 to size
    vec             = new T[c];   // dynamically allocating memory
}
 
template <class T> Vector<T>::Vector(size_t c, T x)
{
    capacity        = c;             // assigning c to capacity
    currentSize     = 0;             // assigning 0 to size
    vec             = new T[c];      // dynamically allocating memory
    
    for(size_t i=0;i<c;i++)
    {
        vec[i] = x;                   // stores x in vector at all indices
        currentSize++;                // incrementing size
    }
}

template <class T> Vector<T>::~Vector()
{
    delete [] vec;             // deleting the dynamically allocated memory
}


template <class T> size_t Vector<T>::Capacity()
{
    return capacity;           // returns capacity 
}

template <class T> size_t Vector<T>::CurrentSize()
{
    return currentSize;        // returns size
}

/************************************************************************************************

* Pushes the element x into vector.

* If the vector is already full calls Newvector function with 2*capacity as argument .

* Stores x and increments the currentsize.

*************************************************************************************************/


template <class T> void Vector<T>::push(T x)
{
   
    if(currentSize == capacity)            // checking whether the vector is full
      {
        Newvector(2*capacity);            // calling Newvector function
      }
    
    currentSize++;                       // incrementing size 
    vec[currentSize -1] = x;             // storing x at last index
    
}

/**********************************************************************************************************************

* Takes input c.

* Creates a new array of size c

* Copies all the elements in old arrray to new array.

* Deletes the old array.

* old array is now pointed to new array.

* Capacity is updated.

**********************************************************************************************************************/


template <class T> void Vector<T>::Newvector(size_t c)
{
    T*newvec;                        // new array is created 
    newvec = new T[c];              // dynamically allocating memory to new array
    
    for(size_t i=0;i<capacity;i++)
    {
        newvec[i] = vec[i];               // copying elements of old array into new array
    }
   
    delete [] vec;                      // deleting old array
    vec      = newvec;                 // old vector is pointed to new vector
    capacity = c;                      // updating capacity
     
}


template <class T> void Vector<T>::pop()
{
    if(currentSize == 0)
    {
        return ;
    }
    currentSize --;                     // reducing the size
}

template <class T> T Vector<T>::front()
{
    if(currentSize == 0)             // checking whether vector is empty
    {
        return -1;
    }
    return vec[0];                    // returning front element if present
}


template <class T> T Vector<T>::back()
{
    if(currentSize == 0)                 // checking whether vector is empty
    {
        return -1;
    }
    return vec[currentSize - 1];          // returning last element if present
}


template <class T> T Vector<T>::operator[](size_t i)
{
    
    if(i >= currentSize)               // checks whether i is greater than size
    {
      return -1;
    }
    return vec[i];                        // returns ith element of the vector
}

template <class T> void Vector<T>::sort()
{
    qsort(0,currentSize-1);                          // calls qsort on (0,currentsize-1)
    for(size_t i=0;i<currentSize;i++)
    {
        cout<<vec[i]<<" ";                          // prints vector elements
    }
    cout<<endl;
    
}
   

template <class T> void  Vector<T>::qsort(size_t low,size_t high)
{
    
    if(low< high)
    {
        size_t p = partition(low,high);                    // calls partition function on (low,high)
        qsort(low,p);                                      // calls qsort recursively on (low,p)
        qsort(p+1,high);                                  // calls qsort recursively on (p+1,high)
    }
    
}
template <class T> size_t Vector<T>:: partition(size_t l,size_t h)
{
    T pivot;                  // stores the pivot element
    T temp ;                 // temporary variable used for swapping
    size_t startPtr;         // index pointer pointing to start
    size_t endPtr;          // index pointer pointing to end
    
    pivot    = vec[l];       // taking 1st element as pivot 
    startPtr = l-1;
    endPtr   = h+1;
    
    while(true)
    {  
        do{
            startPtr++;                       // incrementing start pointer
            
          }while(vec[startPtr]<pivot);         // checking whether element present at start pointer is less than pivot
        
       do{
           endPtr--;                          // decrementing end pointer
           
         }while(vec[endPtr]>pivot);          // checking whether element present at end pointer is greater than pivot
        
       if(startPtr>=endPtr)                      // checking whether start pointer has crossed end pointer
        {
          return endPtr;
        }
        
    temp = vec[startPtr];                  // swapping elements present at start pointer and end pointer
    vec[startPtr] = vec[endPtr];
    vec[endPtr] = temp;
    }
    
}

/************************************* TEMPLATE FUNCTIONS END *********************************************************/


/**********************************************************************************************

* Takes vector as input argument.

* bool scan is given as argument which indicates whether the query number is scanned or not.

* int r indicates the query number if it is previously scanned .

**********************************************************************************************/


void queries(Vector<int>& v,bool scan,int r)
{
    int q;                   // stores query number
    string str;              // stores the input operation
    int res ;               // stores the result
    int elem;               // stores the input element
    size_t val;             // stores the result of size_t type
    size_t ind;             // used to store the input index
    
    q  = r;
    if(!scan)                   // checking whether query number is already scanned 
    {
     cin>>q;
    }
    
   for(int i=0;i<q;i++)
    {
       
        cin>>str;
        
        if(str == "push")
        {
            cin>>elem;
            v.push(elem);                  // pushing elem into the vector
        }
       else if(str == "pop")
        {
          v.pop();                        // poping last elem from vector
        }
        else if(str == "front")
        {
            res = v.front();
            cout<<res<<endl;                      // printing front elem of vector
        }
        else if(str == "back")
        {
            res = v.back();                         // printing last elem of vector
            cout<<res<<endl;
        }
        else if(str == "capacity")
        {
            val = v.Capacity();                       // printing capacity of vector
            cout<<val<<endl;
            
        }
       else if(str == "size")
       {
            val = v.CurrentSize();                   // printing size of vector
            cout<<val<<endl;
       }
       else if(str == "element")
       {
           
           cin>>ind;
           res = v[ind];                           // printing elem present at given index
           cout<<res<<endl;   
       }
       else
       {
           v.sort();                               // printing elements of vector in sorted order
       }
       
    }
}


int main() {
    char c;                                              // stores character scanned
    int x,b,q;
    
    for(int i=0;i<6;i++)
    {
        scanf("%c",&c);                                 // scanning "vector" word
    }
    
    scanf("%c",&c);                                    // scanning next character after vector //
    
    if(c!= ' ')
    {
        Vector<int> v;                               // calling vector v
        queries(v,false,0);
    }
    else
    {
        scanf("%d%c",&x,&c);                        // scanning integer present after space
        
        if(c == ' ')
        {
             scanf("%d",&b);
             Vector<int> v(x,b);                    // calling vector v with capacity as x and elem as b
             queries(v,false,0);
        }
        else if(scanf("%d",&q)!=0)                  // checking whether integer is present after space
        {
            Vector<int> v(x);                       // calling vector v with capacity as x
            queries(v,true,q); 
        }
        else
        {
            Vector<int> v;                            // calling vector v
            queries(v,true,x);
        }
    }
    return 0;
}
