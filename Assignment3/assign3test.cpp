/*
hash map test
HashMap<MapElem<std::string, int>> *hm1 = new HashMap<MapElem<std::string, int>>(1000);

std::string func, key;
int value;

while (true)
{
    cin >> func >> key;

    if (func == "q")
    {
        break;
    }
    if (func == "insert")
    {
        cin >> value;
        hm1->insert(key, value);
    }
    if (func == "remove")
    {
        std::cout << hm1->remove(key) << '\n';
    }
    if (func == "find")
    {
        MapElem<std::string, int> *result = hm1->find(key);
        if (result)
            std::cout << result->key << " " << result->val << '\n';
        else
            std::cout << "not found" << '\n';
    }

    hm1->print();
    std::cout << hm1->size() << " " << hm1->isEmpty() << '\n';
}
*/

#include <iostream>

using namespace std;

int main(){

    int largest_prime;
    cin >> largest_prime;

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

    cout << largest_prime << endl;

}