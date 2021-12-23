//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//
// COSE213 Fall 2021
//

template<class type>
Stack<type>::~Stack()
{
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	const char *EmptyError = "Error: Stack is empty";

	if(IsEmpty()) throw EmptyError;

	return array[top];

}

template<class type>
void Stack<type>::Push(const type& item)
{
	if(top + 1 == capacity){

		type *tmparray = new type[capacity];

		for(int i=0;i<=top;++i){
			tmparray[i] = array[i];
		}

		delete[] array;

		capacity *= 2;
		array = new type[capacity];
		
		for(int i=0;i<=top;++i){
			array[i] = tmparray[i];
		}
		
		delete[] tmparray;
	}

	array[++top] = item;
}

template<class type>
void Stack<type>::Pop()
{
	const char *EmptyError = "Error: Stack is empty";

	if(IsEmpty()) throw EmptyError;

	--top;

}

template<class type>
bool Stack<type>::IsEmpty() const
{

	if(top > -1) return false;
	return true;

}

