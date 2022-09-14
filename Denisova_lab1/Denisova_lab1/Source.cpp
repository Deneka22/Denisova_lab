#include <iostream>
using namespace std;

struct pipe 
{
	int lenght;
	float diameter;
	string inRepair;
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
	cout << "The pipe is under repair or not: ";
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
		<< "7.Download: " << endl
		<< "0.Exit: " << endl;
}

int main() 
{
	pipe pipeNumberOne;
	initializePipe(pipeNumberOne);

	compressorStation stationNumberOne;
	initializeCompressorStation(stationNumberOne);


	mainMenu();
	return 0;
}