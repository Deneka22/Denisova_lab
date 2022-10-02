#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct pipe 
{
	int lenght;
	float diameter;
	bool inRepair;
};

void pointLenght(pipe& pipeline) 
{
	cout << "Enter pipe lenght: ";
	cin >> pipeline.lenght;
}

void pointDiameter(pipe& pipeline) 
{
	cout << "Enter pipe diameter(with point, not comma): ";
	cin >> pipeline.diameter;
}

void pointInRepair(pipe& pipeline) 
{
	cout << "The pipe is under repair(yes or no): ";
	cin >> pipeline.inRepair;
}

void initializePipe(pipe& pipeline) 
{
	pointLenght(pipeline);
	pointDiameter(pipeline);
	pointInRepair(pipeline);
}

struct compressorStation {
	int allShop, workShop;
	double efficienty;
	string name;
};

void pointAllShop(compressorStation& station)
{
	cout << "Enter total number of station: ";
	cin >> station.allShop;
}

void pointWorkShop(compressorStation& station)
{
	cout << "Enter number of stations in work: ";
	cin >> station.workShop;
}

void pointEfficienty(compressorStation& station) 
{
	cout << "What is the performance of the station in percent(with point, not comma): ";
	cin >> station.efficienty;
}

void pointName(compressorStation& station)
{
	cout << "Enter station name: ";
	cin >> station.name;
}

void initializeCompressorStation(compressorStation& station)
{
	pointAllShop(station);
	pointWorkShop(station);
	pointEfficienty(station);
	pointName(station);
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

void printInfo(pipe& pipeNumberOne, compressorStation& stationNumberOne)
{
	cout << "Date about pipe number one:" << endl
		<< "Lenght: " << pipeNumberOne.lenght << endl
		<< "Diameter: " << pipeNumberOne.diameter << endl
		<< "In repair: " << pipeNumberOne.inRepair << endl
		<< endl << "Date about compressor station number one: " << endl
		<< "All shop: " << stationNumberOne.allShop << endl
		<< "Work shop: " << stationNumberOne.workShop << endl
		<< "Efficienty: " << stationNumberOne.efficienty << endl
		<< "Name station: " << stationNumberOne.name << endl;
}

void editPipe(pipe& pipeNumberOne)
{
	cout << "Want to change the status 'InRepair' for this pipe? (Enter '1', if yes and '0', if no)" << endl;
	bool answer;
	cin >> answer;
	if (answer == 1)
	{
		pointInRepair(pipeNumberOne);
	}
}

void editStation(compressorStation& stationNumberOne)
{
	cout << "Want to change number of workstations? (Enter '1', if yes and '0', if no)" << endl;
	bool answer;
	cin >> answer;
	if (answer == 1)
	{
		pointWorkShop(stationNumberOne);
	}
}

void save(pipe& pipeNumberOne, compressorStation& stationNumberOne)
{
	ofstream out; //https://metanit.com/cpp/tutorial/8.3.php
	out.open("date.txt", ios::out);
	if (out.is_open())
	{
		out << pipeNumberOne.lenght << " " << pipeNumberOne.diameter << " " << pipeNumberOne.inRepair << endl
			<< stationNumberOne.allShop << " " << stationNumberOne.workShop << " " << stationNumberOne.efficienty << " " << stationNumberOne.name << endl;
	}
	out.close();
}

void loading(pipe& pipeNumberOne, compressorStation& stationNumberOne)
{
	ifstream in;
	in.open("date.txt", ios::in);
	if (in.is_open())
	{
		in >> pipeNumberOne.lenght >> pipeNumberOne.diameter >> pipeNumberOne.inRepair >> stationNumberOne.allShop >> stationNumberOne.workShop >> stationNumberOne.efficienty >> stationNumberOne.name;
	}
	in.close();
}

int main() 
{
	int numberFromMenu = -1;	
	pipe pipeNumberOne;
	compressorStation stationNumberOne;
	while (numberFromMenu)
	{
		cout << endl;
		mainMenu();
		cin >> numberFromMenu;

		switch (numberFromMenu)
		{
		case 1:
			initializePipe(pipeNumberOne);
			break;
		case 2:
			initializeCompressorStation(stationNumberOne);
			break;
		case 3:
			printInfo(pipeNumberOne, stationNumberOne);
			break;
		case 4:
			editPipe(pipeNumberOne);
			break;
		case 5:
			editStation(stationNumberOne);
			break;
		case 6:
			save(pipeNumberOne, stationNumberOne);
			break;
		case 7:
			loading(pipeNumberOne, stationNumberOne);
			break;

		}
	}

	
}