/** 
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 11. 21
  *
  */
  
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
 
using namespace std;

typedef Entry<int, float> EntryType;

struct time_set{

	float r_insert;
	float r_find;
	float s_insert;
	float s_find;

};

typedef time_set time_set;

template <typename TreeType>
time_set test(int nElem){

	TreeType st_skewed, st_random;

	time_set res = {0, 0, 0, 0};

	//make random dataset

	int *key = new int[nElem];
	int *find_key = new int[nElem];
	float *val = new float[nElem];
	bool *isInserted = new bool[nElem+1]; //check duplicate insertion

	for(int i=0;i<nElem+1;i++){
		isInserted[i] = false;
	}

	std::srand(std::time(0));
	
	for(int i=0;i<nElem;++i){

		find_key[i] = std::rand();
		while(true){
			int tmp = (std::rand() % nElem) + 1; //1 ~ nElem
			if(!isInserted[tmp]){
				isInserted[tmp] = true;
				key[i] = tmp;
				val[i] = (float)std::rand() / RAND_MAX * 20000;
				break;
			}
		}

	}

	//insert - random
	
	clock_t tm;
    tm = clock();
	for(int i=0; i<nElem; i++){
		st_random.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	res.r_insert = ((float)tm / (float)CLOCKS_PER_SEC);

	//find - random

	tm = clock();
	for(int i=0;i<nElem;i++){
		st_random.find(find_key[i]);
	}
	tm = clock() - tm;
	res.r_find = ((float)tm / (float)CLOCKS_PER_SEC);
	
	if(nElem < 1000000 || std::is_same<TreeType, AVLTree<EntryType> >::value){

		// make skewed dataset
		for(int i=0;i<nElem;i++){
			key[i] = i+1;
		}

		//insert - skewed

		tm = clock();
		for(int i=0;i<nElem;i++){
			st_skewed.insert(key[i], val[i]);
		}
		tm = clock() - tm;
		res.s_insert = ((float)tm / (float)CLOCKS_PER_SEC);

		//find - skewed

		tm = clock();
		for(int i=0;i<nElem;i++){
			st_skewed.find(find_key[i]);
		}
		tm = clock() - tm;
		res.s_find = ((float)tm / (float)CLOCKS_PER_SEC);
	}
		

	delete[] key;
	delete[] val;
	delete[] find_key;
	delete[] isInserted;

	return res;

}

int main(){

	/*
	LinkedBinaryTree<EntryType> t;
	std::cout << "Size : " << t.size() << std::endl;
	
	t.addRoot();
	std::cout << "Size : " << t.size() << std::endl;

	//Search Tree Test
	SearchTree<EntryType> st;
	std::cout << "Size : " << st.size() << std::endl;

	//insert
	for(int i=1;i<=100;i++){
		st.insert(i, 1);
	}
	st.insert(1, 2.5);
	st.insert(7, 4.5);
	st.insert(3, 5.5);
	std::cout << "Size : " << st.size() << std::endl;
	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
	//find
	cout << "key 1 : ";
	if(st.find(1) != st.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	cout << "key 26 : ";
	if(st.find(26) != st.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	cout << "key 101 : ";
	if(st.find(101) != st.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	//erase
	st.erase(100);
	std::cout << "Size : " << st.size() << std::endl;
	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}	

	for(int i=1;i<100;i++){
		st.erase(i);
	}
	std::cout << "Size : " << st.size() << std::endl;
	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}

	std::cout << "------------" << std::endl;

	AVLTree<EntryType> avl;
	std::cout << "Size : " << avl.size() << std::endl;

	//insert
	for(int i=1;i<=100;i++){
		avl.insert(i, 1);
	}
	avl.insert(1, 2.5);
	avl.insert(7, 4.5);
	avl.insert(3, 5.5);
	std::cout << "Size : " << avl.size() << std::endl;
	for(AVLTree<EntryType>::Iterator it = avl.begin(); it != avl.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
	//find
	cout << "key 1 : ";
	if(avl.find(1) != avl.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	cout << "key 26 : ";
	if(avl.find(26) != avl.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	cout << "key 101 : ";
	if(avl.find(101) != avl.end()) cout << "found" << endl;
	else cout << "not found" << endl;

	//erase
	avl.erase(100);
	std::cout << "Size : " << avl.size() << std::endl;
	for(AVLTree<EntryType>::Iterator it = avl.begin(); it != avl.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}	

	for(int i=1;i<100;i++){
		avl.erase(i);
	}
	std::cout << "Size : " << avl.size() << std::endl;
	for(AVLTree<EntryType>::Iterator it = avl.begin(); it != avl.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
	
	std::cout << "------------" << std::endl;
	*/

	//
	//
	//

	int test_size[5] = {1000, 10000, 50000, 100000, 1000000};
	
	cout << "< BST Test >" << endl;
	for(int s=0;s<5;s++){

		time_set test_res_BST = test<SearchTree<EntryType> >(test_size[s]);

		cout << "Test Size : " << test_size[s] << endl;
		cout << "BST Insert (Random) takes " << test_res_BST.r_insert << " seconds." << endl;
		cout << "BST Find (Random) takes " << test_res_BST.r_find << " seconds." << endl;
		if(s<4){
			cout << "BST Insert (Skewed) takes " << test_res_BST.s_insert << " seconds." << endl;
			cout << "BST Find (Skewed) takes " << test_res_BST.s_find << " seconds." << endl;
		}
		
	}

	cout << "< AVL Test >" << endl;
	for(int s=0;s<5;s++){

		time_set test_res_AVL = test<AVLTree<EntryType> >(test_size[s]);

		cout << "Test Size : " << test_size[s] << endl;
		cout << "AVL Insert (Random) takes " << test_res_AVL.r_insert << " seconds." << endl;
		cout << "AVL Find (Random) takes " << test_res_AVL.r_find << " seconds." << endl;
		cout << "AVL Insert (Skewed) takes " << test_res_AVL.s_insert << " seconds." << endl;
		cout << "AVL Find (Skewed) takes " << test_res_AVL.s_find << " seconds." << endl;

	}

	return 0;
}