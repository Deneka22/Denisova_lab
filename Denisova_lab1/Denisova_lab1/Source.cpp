#include <iostream>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

struct pipe 
{
	float lenght, diameter;
	bool inRepair;
};

struct compressorStation 
{
	int allShop, workShop, efficienty;
	string name;
};

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
	return input;
}

void initializePipe(pipe& pipeline) 
{
	cout << "Enter pipe lenght: ";
	pipeline.lenght = read<float>(10.0, 1000.0);
	cout << "Enter pipe diameter: ";
	pipeline.diameter = read<float>(1.0, 1000.0);
	cout << "The pipe is under repair(yes or no): ";
	pipeline.inRepair = read(0, 1);
}

void initializeCS(compressorStation& station)
{
	cout << "Enter total number of station: ";
	station.allShop = read(1, 100);
	cout << "Enter number of stations in work: ";
	station.workShop = read(0, station.allShop);
	cout << "What is the performance of the station in percent: ";
	station.efficienty = read(0, 100);
	cout << "Enter station name: "; //нет ограничений
	cin >> ws;
	getline(cin, station.name);
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

void infoPipe(pipe& pipe)
{
	cout << "Date about pipe:" << endl
		<< "Lenght: " << pipe.lenght << endl
		<< "Diameter: " << pipe.diameter << endl
		<< "In repair: " << pipe.inRepair << endl;
}

void infoCS(compressorStation& station)
{
	cout << "Date about compressor station: " << endl
		<< "All shop: " << station.allShop << endl
		<< "Work shop: " << station.workShop << endl
		<< "Efficienty: " << station.efficienty << endl
		<< "Name station: " << station.name << endl;
}

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

void save(pipe& pipe, compressorStation& station)
{
	ofstream out; //https://metanit.com/cpp/tutorial/8.3.php
	out.open("date.txt", ios::out);
	if (out.is_open())	//проверка, открылся ли файл
	{
		out << "Pipe"
			<< endl << pipe.lenght << " " << pipe.diameter << " " << pipe.inRepair << endl
			<<"CompressorStation"<<endl
			<<station.allShop << " " << station.workShop << " " << station.efficienty << " " <<endl
			<< station.name << endl;
	}
	out.close();
}

void loading(pipe& pipe, compressorStation& station)
{
	ifstream in;
	in.open("date.txt", ios::in);
	if (in.is_open())	//проверка, открылся ли файл
	{
		string StringCheck = "";
		int number = -1;
		cout << "Enter '1', if you want loading" << endl
			<< "Enter '0', if you don't want to load anything" << endl;
		number = read(0, 1);

		switch (number) 
		{
		case 1:
			do
			{
				getline(in, StringCheck);
			} while (in.eof() == 0 && StringCheck != "Pipe");
			in >> pipe.lenght >> pipe.diameter >> pipe.inRepair;
			do
			{
				getline(in, StringCheck);
			} while (in.eof() == 0 && StringCheck != "CompressorStation");
			in >> station.allShop >> station.workShop >> station.efficienty;
			in.ignore(1000, '\n');
			in.clear();
			getline(in, station.name);
			break;
		case 0:
			in.close();
			return;
		}	
	}
	in.close();
}

int main() 
{
	int numberFromMenu = -1;	
	pipe pipe = {};
	compressorStation station = {};
	while (numberFromMenu)
	{
		cout << endl;
		mainMenu();
		numberFromMenu = read(0,7);
		switch (numberFromMenu)
		{
		case 1:
			initializePipe(pipe);
			break;
		case 2:
			initializeCS(station);
			break;
		case 3:
			if (pipe.lenght > 0)
			{
				infoPipe(pipe);
			}

			if (station.allShop > 0) 
			{
			cout << endl;
			infoCS(station);
			}

			else {
				cout << "No data" << endl;
			}

			break;
		case 4:
			if (pipe.lenght > 0) {
				editPipe(pipe);
			}
			else {
				cout << "No data" << endl;
			}
			break;
		case 5:
			if (station.allShop > 0) {
				editStation(station);
			}
			else {
				cout << "No data" << endl;
			}
			break;
		case 6:
			save(pipe, station);
			break;
		case 7:
			loading(pipe, station);
			break;
		case 0:
			return 0;
		}
	}
}