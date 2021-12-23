//
// - Implementation -
//

// constructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
	mapsize = 0;
	
	//find largest prime number smaller than c

	int largest_prime = c;

	while(true){

        bool flag = true;

        for(int i=largest_prime/2;i>=2;i--){
			if(largest_prime % i == 0){
				largest_prime--;
                flag = false;
				break;
			}
		}

        if(flag) break;
	}

	capacity = largest_prime;
	divisor = largest_prime;

	ht = new HashMapElemType* [capacity];

	for(int i=0;i<capacity;++i){
		ht[i] = new HashMapElemType;
	}
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	for(int i=0;i<capacity;++i){ 
		delete[] ht[i]; 
	} 
	
	delete[] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{ 
	unsigned int hash_v = hashfunction(k);
	HashMapElemType * curr = ht[hash_v]->link;

	while(curr){
		if(curr->key == k){
			return curr;
		}
		curr = curr->link;
	}

	return NULL;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
	HashMapElemType * result = find(k);

	if(result){
		result->val = v;
	}

	else{
		unsigned int hash_v = hashfunction(k);

		HashMapElemType * newEntry = new HashMapElemType;

		newEntry->key = k;
		newEntry->val = v;
		newEntry->link = ht[hash_v]->link;
		ht[hash_v]->link = newEntry;

		mapsize++;
	}
	
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
	 if(find(k)){

		unsigned int hash_v = hashfunction(k);
		HashMapElemType *curr = ht[hash_v], *target;

		while(curr->link){
			if(curr->link->key == k){
				target = curr->link;
				break;
			}
			curr = curr->link;
		}

		curr->link = target->link;
		delete target;

		mapsize--;
		
		return true;
	}

	return false;
}

template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	// 1. change key to int

	int number = 0;
	int len = k.length();

	for (int i = 0; i < len; i += 2)
	{
		number += (int)k[i];
		if (i + 1 < len)
		{
			number += ((int)k[i + 1]) << 8;
		}
	}

	// 2. division

	number = number % divisor;

	return number;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	for(int i=0;i<capacity;++i){

		std::cout << "bucket " << i << ")" << '\n';
		HashMapElemType *curr = ht[i]->link;

		while(curr){
			std::cout << curr->key << " : " << curr->val << '\n';
			curr = curr->link;
		}
	}

}