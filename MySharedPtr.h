#pragma once
#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_




//*************************************************************************
//* implementing a generic pointer class.
//* the implementation is just after declaration out of the class block.
//*************************************************************************

template <typename C>  class MySharedPtr
{

public:

    MySharedPtr();
    MySharedPtr(C* value);
    MySharedPtr(const MySharedPtr<C>& org_obj);
    ~MySharedPtr();
    MySharedPtr<C>& operator=(const MySharedPtr<C>& org_obj);
    C& operator*();
    C* operator->();
    C* get();

private:
    C* value_;
    int*  counter_;
};


template <class C>
MySharedPtr<C>::MySharedPtr(){
    value_ = 0;
    counter_ = new int;
    (*counter_) = 0;
}

//*************************************************************************
//* Function name: MySharedPtr (C* value)
//* Description: contractor by pointer.
//* Parameters:
//*		value – pointer to ‘C’ Class.
//* Return Value: none.
//*************************************************************************

template <class C>
MySharedPtr<C>::MySharedPtr(C* value): value_(value){
	counter_ = new int;
    (*counter_) = 1;
}


//*************************************************************************
//* Function name: MySharedPtr (const MySharedPtr<C>& org_obj)
//* Description: copy constractor
//* Parameters:
//*		org_obj – an MySharedPtr<C> object.
//* Return Value: none.
//*************************************************************************

template <class C>
MySharedPtr<C>::MySharedPtr(const MySharedPtr<C>& org_obj): value_(org_obj.value_), counter_(org_obj.counter_){
    (*counter_)++;
}


//*************************************************************************
//* Function name: ~MySharedPtr
//* Description: distractor
//* Parameters: none.
//* Return Value: none.
//*************************************************************************

template <class C>
MySharedPtr<C>::~MySharedPtr(){
    (*counter_)--;
    if ((*counter_) <= 0){
        delete value_;
        delete counter_;
    }
}


//*************************************************************************
//* Function name: operator=
//* Description: copies one MySharedPtr<C> to anther and handling the case of
//*		dangling memories.
//* Parameters:
//*		org_obj – an MySharedPtr<C> object – the origin object
//* Return Value: none.
//*************************************************************************

template <class C>
MySharedPtr<C>& MySharedPtr<C>::operator=(const MySharedPtr& org_obj){
    if (this != &org_obj){
        (*counter_)--;
        if ((*counter_) <= 0){
            delete value_;
            delete counter_;
        }
        value_ = org_obj.value_;
        counter_=org_obj.counter_;
        (*counter_)++;
    }
    return *this;
}


//*************************************************************************
//* Function name: operator*
//* Description: returns the MySharedPtr<C> object value.
//* Parameters: none.
//* Return Value: an C class reference.
//*************************************************************************

template <class C>
C& MySharedPtr<C>::operator*() {
    return *value_;
}


//*************************************************************************
//* Function name: operator->
//* Description: returns the MySharedPtr<C> object value ponter.
//* Parameters: none.
//* Return Value: an C class pointer.
//*************************************************************************

template <class C>
C* MySharedPtr<C>::operator->() {
    return value_;
}


//*************************************************************************
//* Function name: get
//* Description: returns the MySharedPtr<C> object value ponter.
//* Parameters: none.
//* Return Value: an C class pointer.
//*************************************************************************

template <class C>
C* MySharedPtr<C>::get() {
    return value_;
}

#endif // _MY_SHARED_PTR_H_
