#include <iostream>

using namespace std;

class SmartPointer  /*Shared pointer actually*/
{
  private:
    int* ptr;
    /*Using address to int for reference counting instead of "integer" itself is necessary as when reference 
    count is copied while creating new SmartPointer object from old one, the value of refence count will be copied 
    and that value will be increased and reference count of original SmartPointer object will remain same*/
    int * reference = new int (0);
    
  public:
    explicit SmartPointer(int* p)   /*explicit to prevent implicit conversion*/
    {
        *reference = 1;
        ptr = p;
    }
    
    /*These two operators i.e. "*" and "->" need to be overload so that SmartPointer "object" can be used as a pointer
    even though it is allocated on stack*/
    int& operator*()
    {
        return *ptr;
    }
    
    int* operator->()
    {
        return ptr;
    }
    
    SmartPointer(SmartPointer& sp)
    {
        
        ptr = sp.ptr;
        reference = sp.reference;
        
        ++(*reference);
        //cout<<this->reference<<endl;
    }
    
    ~SmartPointer()
    {
        --(*reference);
        if(*reference == 0)
        { 
            cout<<"Deleting SmartPointer"<<endl;
            delete ptr;
        }
    }
    
    
    SmartPointer& operator=(SmartPointer& sp)
    {
        if(this != &sp)
        {
           ++(*reference);
           this->ptr = sp.ptr;
        }
        return *this;
    }
    
    int getRefCount()
    {
        return *reference;
    }
};

int main()
{
    SmartPointer sp1 (new int (10));
    {
        SmartPointer sp2 = sp1;
        {
            SmartPointer sp3 (sp2);
              cout<<sp1.getRefCount()<<" "<<sp2.getRefCount()<<" "<<sp3.getRefCount()<<endl;
        }
        cout<<sp1.getRefCount()<<" "<<sp2.getRefCount()<<endl;
    }
    cout<<sp1.getRefCount()<<endl;
    return 0;
}
