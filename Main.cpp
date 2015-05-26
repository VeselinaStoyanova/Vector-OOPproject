#include<iostream>
#include"Vector.h"
#include"Animal.h"
#include<string>
#include<vector>
using namespace std;


int main()
{
	Animal a1("Mammal", "Lion", "Grassland", 5);
	Animal a2("Bird", "Pengiun", " Antarctica", 1);
	Animal a3("Reptiles", "Snake", "Desert", 2);
	Animal a4("Aquatic Animal", "Dolphin", "Sea", 7);
	
	Vector<Animal> animals;
	animals.push_back(a1);
	animals.push_back(a2);
	animals.push_back(a3);
	animals.push_back(a4);
	

	Vector<int> v1;  
	v1.push_back(1); 
	v1.push_back(3);  
	v1.push_back(5);  
	v1.push_back(7); 
	v1.push_back(9);  
	v1.push_back(11);  
	v1.push_back(13); 
	v1.pop_back();  
	v1.push_back(777);
	v1.insert(5, 100);
	v1.erase(6);
	v1.print();
	cout << endl;
	cout << v1[4] << endl;
	
	Vector<string> Penguin;
	Penguin.push_back("Penguins");
	Penguin.push_back("were once");
	Penguin.push_back("able to");
	Penguin.push_back("fly");
	for (int i = 0; i < Penguin.size(); i++)
	{
		cout << Penguin[i] << " ";
	}
	cout << endl;
	cout << Penguin.front()<<" "<<"don't"<<" "<< Penguin.back() << endl;
	
	Vector<string> Lion;
	Lion.push_back("Lion");
	Lion.push_back("is common symbols");
	Lion.push_back(" for royalty and stateliness");
	Lion.insert(1, "The");  
	for (int i = 0; i < Lion.size(); i++)
	{
		cout << Lion[i] << " ";
	}
	cout << endl;
	Lion.erase(1); 
	for (int i = 0; i < Lion.size(); i++)
	{
		cout << Lion[i] << " ";
	}
	cout << endl;
	
	Vector<string> Snake;
	Snake.push_back("Snakes");
	Snake.push_back("are");
	Snake.push_back("dreadful");
	
	Vector<string> Dolphin;
	Dolphin.push_back("Dolphins");
	Dolphin.push_back("are");
	Dolphin.push_back("lovely");
	
	Snake.swap(Dolphin);
	for (int i = 0; i < Snake.size(); i++)
	{
		cout << Snake[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < Dolphin.size(); i++)
	{
		cout << Dolphin[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}