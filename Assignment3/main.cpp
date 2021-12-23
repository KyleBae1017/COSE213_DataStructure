#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * 2021. 11. 1   Won-Ki Jeong
  *
  */

HashMap<MapElem<std::string, int> > *dic = new HashMap<MapElem<std::string, int> >;

void spellcheck(std::string s)
{
	std::cout << "> " << s;
	
	if(dic->find(s)){
		std::cout << " is in the dictionary" << '\n'; 
	}

	else{
		std::cout << " is NOT in the dictionary" << '\n';
		std::cout << "> " << s << " ";

		int len = s.length();
		bool isRecommended = false;
		
		for(int i=0;i<len;++i){
			for(int j=0;j<26;++j){

				std::string new_s = s;

				if('a'+j != (int) s[i]){

					new_s.replace(new_s.begin()+i, new_s.begin()+i+1, 1, (char) 'a'+j);

					if(dic->find(new_s)){
						if(!isRecommended){ //first recommending
							isRecommended = true;
							std::cout << ": " << new_s;
						}
						else{
							std::cout << ", " << new_s;
						}
					}

				}
			}
		}
		if(!isRecommended) std::cout << ": no suggestion";
		std::cout << '\n';
	}
}


int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();
		
	for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// Insert token to hash map
				dic->insert(token, 1);
				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}

	//
	// infinite loop to accept user input word
	//
	while(1)
	{
		std::string s;
		std::cout << "> ";
		std::cin >> s;
		
		if(s.compare("q") == 0) break;	
		
		spellcheck( s );
	}
	
	
	return 0;
}