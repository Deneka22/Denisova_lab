#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class compressorStation
{
private:
	int id;
	string name;
	int allShop, workShop, efficienty;
public:
	static int csMaxId;
	friend istream& operator >> (istream& in, compressorStation& station);
	friend ostream& operator << (ostream& out, const compressorStation& station);
	friend ofstream& saveInFile(ofstream& out, compressorStation& station);
	friend ifstream& operator >> (ifstream& in, compressorStation& station);

	string getName() const;
	int getAllShop() const;
	int getWorkShop() const;

	static int getId();
	static void changeCsMaxId(int Id);
};