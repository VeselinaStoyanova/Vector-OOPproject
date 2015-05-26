#ifndef ANIMAL_H
#define ANIMAL_H

#include<iostream>
#include<string>
using namespace std;

class Animal
{
public:
	Animal() : type(""), kind(""), habitat(""), age(0){}
	Animal(string type, string kind, string habitat, int age) : type(type), kind(kind), habitat(habitat), age(age) {}


private:
	string type;
	string kind;
	string habitat;
	int age;
};




#endif
