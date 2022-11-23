#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class pipe
{
private:
	int id;
	string name;
	float lenght, diameter;
	bool inRepair;

public:
	static int pipeMaxId;
	friend istream& operator >> (istream& in, pipe& pipeline);
	friend ostream& operator << (ostream& out, pipe& pipeline);
	friend ofstream& saveInFile(ofstream& out, pipe& pipeline);
	friend ifstream& operator >> (ifstream& in, pipe& pipeline);

	string getName() const;
	static void changePipeMaxId(int Id);
	static int getId();
	bool getInRepair() const;
};

