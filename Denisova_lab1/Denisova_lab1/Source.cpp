#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <unordered_map>

#include "CS.h"
#include "Pipe.h"

using namespace std;

template <typename T>
T read(T min, T max)
{
	T input;
	cin >> input;
	while (cin.fail() || input<min || input>max)
	{
		cout << "Entering value is incorrect, please try again" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> input;
	}
	cin.ignore(10000, '\n');
	return input;
}

void mainMenu() 
{
	cout << "Select an action: " << endl
		<< "1.Add a pipe: " << endl
		<< "2.Add a compression station: " << endl
		<< "3.Viewing all objects: " << endl
		<< "4.Edit pipe: " << endl
		<< "5.Edit compression station: " << endl
		<< "6.Save: " << endl
		<< "7.Loading: " << endl
		<< "0.Exit: " << endl;
}

istream& operator >> (istream& in, pipe& pipeline)
{
	cout << "Enter name for pipe: ";
	getline(in, pipeline.name);
	cout << "Enter pipe lenght: ";
	pipeline.lenght = read<float>(10.0, 100000.0);
	cout << "Enter pipe diameter: ";
	pipeline.diameter = read<float>(1.0, 100000.0);
	cout << "The pipe is under repair(yes or no): ";
	pipeline.inRepair = read(0, 1);

	return in;
}

ostream& operator << (ostream& out, pipe& pipeline)
{
	cout << "Name: " << pipeline.name << endl
		<< "Lenght: " << pipeline.lenght << endl
		<< "Diameter: " << pipeline.diameter << endl
		<< "In repair: " << pipeline.inRepair << endl << endl;

	return out;
}

istream& operator >> (istream& in, compressorStation& station)
{
	cout << "Enter station name: "; //нет ограничений
	cin >> ws;
	getline(cin, station.name);
	cout << "Enter total number of station: ";
	station.allShop = read(1, 100);
	cout << "Enter number of stations in work: ";
	station.workShop = read(0, station.allShop);
	cout << "What is the performance of the station in percent: ";
	station.efficienty = read(0, 100);
	return in;
}

ostream& operator << (ostream& out, const compressorStation& station)
{
	cout << "Name: " << station.name << endl
		<< "All shop: " << station.allShop << endl
		<< "Work shop: " << station.workShop << endl
		<< "Efficienty: " << station.efficienty << endl << endl;
	return out;
}

ofstream& saveInFile(ofstream& out, pipe& pipeline)
{
	out << pipeline.name << endl
		<< pipeline.lenght << endl
		<< pipeline.diameter << endl
		<< pipeline.inRepair << endl;
	return out;
}

ofstream& saveInFile(ofstream& out, compressorStation& station)
{
	out << station.name << endl
		<< station.allShop << endl
		<< station.workShop << endl
		<< station.efficienty << endl;
	return out;
}

ifstream& operator >> (ifstream& in, pipe& pipeline)
{
	in >> ws;
	getline(in, pipeline.name);

	in >> pipeline.lenght;
	in >> pipeline.diameter;
	in >> pipeline.inRepair;

	return in;
}

ifstream& operator >> (ifstream& in, compressorStation& station)
{
	in >> ws;
	getline(in, station.name);

	in >> station.allShop;
	in >> station.workShop;
	in >> station.efficienty;

	return in;
}

/*
void editPipe(pipe& pipe)
{
	cout << "Enter the new status for pipe: ";
	cin >> pipe.inRepair;
}

void editStation(compressorStation& station)
{
	cout << "Enter the new number of workstations: ";
	cin >> station.workShop;
}
*/

string enteringFileName()
{
	cout << endl << "Enter file's name: ";
	string way = "";
	cin >> ws;
	getline(cin, way);

	way.insert(0, "./Data/");
	way.append(".txt");
	return way;
}

string enteringFragmentName()
{
	string Name = "NoName";

	cout << "Enter fragment of the name of the desired objects" << endl << "Filter: ";
	cin >> ws;
	getline(cin, Name);

	return Name;
}

template<typename T, typename T1>
using Filter = bool (*)(const T1& Obj, T param);

template<typename T>
bool checkByName(const T& Obj, string param)
{
	return (Obj.getName().find(param) != string::npos);
}

bool checkByEffectiveness(const  compressorStation& Cs, double param)
{
	double  allShop = Cs.getAllShop();
	double  workShop = Cs.getWorkShop();
	double Effectivenness = param / 100;
	return((1 - workShop / allShop) >= Effectivenness);
}
bool checkByStatus(const pipe& P, bool param)
{
	return (P.getInRepair() == param);
}


template<typename T, typename T1>
void filterResults(unordered_map<int, T1>& Obj, unordered_map<int, int>& IDs, Filter<T, T1> f, T param)
{
	int count = 0;
	for (const auto& elem : Obj)
	{
		if (f(elem.second, param))
		{
			++count;
			cout << "Number in list: " << count << endl;
			cout << "ID object: " << elem.first << endl;
			cout << (T1)elem.second << endl;
			IDs.emplace(count, elem.first);
		}
	}
	if (count == 0)
	{
		cout << "No objects found!" << endl;
		return;
	}
}


void informationOutput(unordered_map<int, pipe>& pipes, unordered_map<int, compressorStation>& stations)
{
	cout << "1. Enter information about all pipes" << endl
		 << "2. Enter information about all CS" << endl
		 << "3. Enter information about all object" << endl
		 << "4. Enter information by filter CS's name" << endl
		 << "5. Enter information by filter percentage of unused workshops" << endl
		 << "0. Exit in main menu" << endl << endl;

	string Name = "NoName";
	int numberFromMenu = -1;
	numberFromMenu = read(0, 7);
	double Effectiveness = 0;

	switch (numberFromMenu)
	{
	case 1:
	{
		for (auto& pipe : pipes)
			cout << pipe.second;
		break;
	}

	case 2:
	{
		for (auto& cs : stations)
			cout << cs.second;
		break;
	}

	case 3:
	{

		for (auto& pipe : pipes)
			cout << pipe.second;

		for (auto& cs : stations)
			cout << cs.second;

		break;
	}

	case 4:
	{
		if (stations.size() == 0)
		{
			cout << "It is necessary to create at least one element!";
		}
		Name = enteringFragmentName();	

		unordered_map<int, int> IDs;
		filterResults(stations, IDs, checkByName, Name);
		break;
	}

	case 5:
	{
		if (stations.size() == 0)
		{
			cout << "It is necessary to create at least one element!";
		}
		cout << "¬ведите процент незадействованных цехов (от 0 до 100): " << endl;
		Effectiveness = read(0., 100.);
		unordered_map<int, int> IDs;
		filterResults(stations, IDs, checkByEffectiveness, Effectiveness);

		break;
	}
	case 0:
		return;
	}

}

void save( unordered_map<int ,pipe>& pipes, unordered_map<int, compressorStation>& stations)
{
	ofstream out; 
	string way = enteringFileName();
	out.open(way, ios::out);
	if (out.is_open())	//проверка, открылс€ ли файл
	{
		out << pipes.size() << endl
			<< stations.size() << endl
			<< endl;

		out << pipe::getId() << endl
			<< compressorStation::getId() << endl;

		for (auto& elem : pipes)
		{
			out << elem.first << endl;
			saveInFile(out, elem.second);
			out << endl;
		}
		for (auto& elem : stations)
		{
			out << elem.first << endl;
			saveInFile(out, elem.second);
			out << endl;
		}
	}
	else cout << "File not open!" << endl;
	out.close();
}

void loading(unordered_map<int, pipe>& pipes, unordered_map<int, compressorStation>& stations)
{
	ifstream in;
	string way = enteringFileName();
	int numberOfPipes;
	int numberOfStations;
	int pipeId;
	int compressorStationId;
	in.open(way, ios::in);
	if (in.is_open())
	{
		in >> numberOfPipes;
		in >> numberOfStations;

		in >> pipeId;
		in >> compressorStationId;

		pipe::changePipeMaxId(pipeId);
		compressorStation::changeCsMaxId(compressorStationId);
		pipe Pipe;
		compressorStation station;
		int Id = 0;

		for (int i = 0; i < numberOfPipes; i++)
		{
			in >> Id;
			in >> Pipe;
			pipes.emplace(Id, Pipe);
		}
		for (int i = 0; i < numberOfStations; i++)
		{
			in >> Id;
			in >> station;
			stations.emplace(Id, station);
		}

		in.close();
	}
	else cout << "File not open!" << endl;
}

int main() 
{
	int numberFromMenu = -1;	
	unordered_map<int, pipe> groupP;
	unordered_map<int, compressorStation> groupCS;
	while (numberFromMenu)
	{
		cout << endl;
		mainMenu();
		numberFromMenu = read(0,7);
		switch (numberFromMenu)
		{
		case 1:
		{
			pipe pipe;
			cin >> pipe;
			groupP.insert({++pipe::pipeMaxId, pipe});
			break;
		}

		case 2:
		{
			compressorStation station;
			cin >> station;
			groupCS.insert({++compressorStation::csMaxId, station});
			break;
		}

		case 3:
		{
			informationOutput(groupP, groupCS);

			break;
		}

		case 4:
		{
			for (auto& pipe : groupP)
			{
				//editPipe(pipe);
				cout << endl;
			}
			break;
		}

		case 5:
		{
			for (auto& station : groupCS)
			{
				//editStation(station.second);
				cout << endl;
			}
			break;
		}

		case 6:
		{
			save(groupP, groupCS);
			break;
		}

		case 7:
		{
			loading(groupP, groupCS);
			break;
		}

		case 0:
			return 0;
		}
	}
}