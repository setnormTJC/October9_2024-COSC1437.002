//
// Written by Aiden Sayre
// Last modified 10/15/2024
// 
// Lab10c: "Reading and storing data
//			from a file into an array"
// 
// As it says on the tin, this program
// reads and stores datasets from user
// submitted CSV (or space sep. value)
// files. Specifically, it stores data
// about the Titanic, displaying the
// dataset on the terminal and does
// some basic data analytics.
// 
// Contains my word scanner algorithm,
// which is massively upgraded since Lab7a.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct TitanicData
{
	int passID = 0;
	bool survived = 0;
	int passClass = 0;
	string lastName = "TBD";
	char passSex = 'U';
	int passAge = 0;
	double fareCost = 0;
};
struct DataCache
{
	string currentLine = "";
	string currentPoint = "";
	//string currentType = "";
};

const int MAX_DATAFILE_SIZE = 50;
ifstream userDataFile;
TitanicData passRecords[MAX_DATAFILE_SIZE];

static void extractDataPoint(DataCache& current_dataset, string file_type)
{
	int dataspot = 0;
	if (file_type == "TXT")
	{
		for (int position = 0; !isspace(current_dataset.currentLine[position]) && position < current_dataset.currentLine.length(); position++)
			dataspot++;
	}
	if (file_type == "CSV")
	{
		for (int position = 0; current_dataset.currentLine[position] != ',' && position < current_dataset.currentLine.length(); position++)
			dataspot++;
	}
	current_dataset.currentPoint = current_dataset.currentLine.substr(0, dataspot);
	current_dataset.currentLine.erase(0, dataspot + 1);
}

static void storeDataPoint(DataCache current_datacache, TitanicData(&current_dataset)[MAX_DATAFILE_SIZE], int current_loop, int current_index)
{
	switch (current_loop)
	{
	case 0:
		// passenger id (integer)
		current_dataset[current_index].passID = stoi(current_datacache.currentPoint);
		break;
	case 1:
		// passenger survival (boolean)
		current_dataset[current_index].survived = stoi(current_datacache.currentPoint);
		break;
	case 2:
		// passenger class (integer)
		current_dataset[current_index].passClass = stoi(current_datacache.currentPoint);
		break;
	case 3:
		// passenger last name (string)
		current_dataset[current_index].lastName = current_datacache.currentPoint;
		break;
	case 4:
		// passenger sex (character)
		current_dataset[current_index].passSex = current_datacache.currentPoint[0];
		break;
	case 5:
		// passenger age (integer)
		current_dataset[current_index].passAge = stoi(current_datacache.currentPoint);
		break;
	case 6:
		// passenger fare cost (double)
		current_dataset[current_index].fareCost = stod(current_datacache.currentPoint);
		break;
	default:
		cout << "[ERROR: something went wrong when storing data \"" << current_datacache.currentPoint << "\"]";
		break;
	}
}

static void displayDataset(TitanicData(&current_array)[MAX_DATAFILE_SIZE])
{
	cout << "|----|----------|-------|---------------------|------|------|--------|";

	cout << left << "\n| "
		<< setw(3) << "ID" << "| "
		<< setw(9) << "SURVIVED" << "| "
		<< setw(6) << "CLASS" << "| "
		<< setw(20) << "LAST NAME" << "| "
		<< setw(5) << "SEX" << "| "
		<< setw(5) << "AGE" << "| "
		<< setw(7) << "COST" << "| "
		<< endl;

	cout << "|----|----------|-------|---------------------|------|------|--------|\n";

	for (int index = 0; index < MAX_DATAFILE_SIZE; index++)
	{
		cout << left << "| "
			<< setw(3) << current_array[index].passID << "| "
			<< boolalpha
			<< setw(9) << current_array[index].survived << "| "
			<< setw(6) << current_array[index].passClass << "| "
			<< setw(20) << current_array[index].lastName << "| "
			<< setw(5) << current_array[index].passSex << "| "
			<< setw(5) << current_array[index].passAge << "| "
			<< fixed << setprecision(2) << right << "$"
			<< setw(6) << current_array[index].fareCost << "| "
			<< endl;
	}

	cout << "|----|----------|-------|---------------------|------|------|--------|\n";
}

static void calculateDataset(TitanicData(&current_array)[MAX_DATAFILE_SIZE], string request)
{
	if (request == "avgCost")
	{
		double calc_farecost_avg = 0;
		int calc_survival_total = 0;
		// avg fare & who survived
		for (int index = 0; index < MAX_DATAFILE_SIZE; index++)
		{
			calc_farecost_avg += passRecords[index].fareCost;

			if (passRecords[index].survived == true)
				calc_survival_total++;
		}
		calc_farecost_avg = calc_farecost_avg / MAX_DATAFILE_SIZE;

		cout << "The average cost of fare on the Titanic was $" << fixed << setprecision(2) << calc_farecost_avg << ".\n";
		cout << "Only " << calc_survival_total << " of the " << MAX_DATAFILE_SIZE << " people listed survived.";
	}

	if (request == "classSrvRate")
	{
		double class1_srvRate = 0, class2_srvRate = 0, class3_srvRate = 0;
		int class1_femRate = 0, class2_femRate = 0, class3_femRate = 0;
		int class1_malRate = 0, class2_malRate = 0, class3_malRate = 0;

		for (int index = 0; index < MAX_DATAFILE_SIZE; index++)
		{
			if (passRecords[index].survived == true)
			{
				switch (passRecords[index].passClass)
				{
				case 1:
					class1_srvRate++;
					if (passRecords[index].passSex == 'F')
						class1_femRate++;
					else
						class1_malRate++;
					break;
				case 2:
					class2_srvRate++;
					if (passRecords[index].passSex == 'F')
						class2_femRate++;
					else
						class2_malRate++;
					break;
				case 3:
					class3_srvRate++;
					if (passRecords[index].passSex == 'F')
						class3_femRate++;
					else
						class3_malRate++;
					break;
				}
			}
		}

		cout << "\nOf the people who survived,\n"
			<< fixed << setprecision(0)
			<< "- " << class1_srvRate << " were first class, "
			<< class1_femRate << " of whom were female and " << class1_malRate << " of whom were male\n"
			<< "- " << class2_srvRate << " were second class, "
			<< class2_femRate << " of whom were female and " << class2_malRate << " of whom were male\n"
			<< "- " << class3_srvRate << " were third class, "
			<< class3_femRate << " of whom were female and " << class3_malRate << " of whom were male\n";
	}

	cout << endl;
}

int main()
{
	DataCache titanicDataset;
	string file_name, file_type;

	// get file from user
	cout << "\nPlease input the name of the file to scan (CSV or TXT):\n> ";
	cin >> file_name;
	// check user file type
	if (file_name.length() >= 4)
	{
		if (file_name.substr(file_name.length() - 4, file_name.length()) == ".txt")
			file_type = "TXT";
		else if (file_name.substr(file_name.length() - 4, file_name.length()) == ".csv")
			file_type = "CSV";
		else
		{
			cout << "[ERROR: File extension must also be included, or \"" << file_name << "\" is not of a recognized file format]\n";
			return 2; // error! [EXIT]
		}
	}

	// open the user file (must be in same dir)
	userDataFile.open(file_name);
	if (!userDataFile.is_open())
	{
		cout << "[ERROR: Unable to locate file \"" << file_name << "\"]\n";
		return 1; // error! [EXIT]
	}

	int index_y = 0;
	while (!userDataFile.eof())
	{
		getline(userDataFile, titanicDataset.currentLine);
		for (int index_x = 0; index_x < 7; index_x++)
		{
			extractDataPoint(titanicDataset, file_type);
			storeDataPoint(titanicDataset, passRecords, index_x, index_y);
		}
		index_y++;
	}

	cout << "-- Data read successfully! --\n\n";
	displayDataset(passRecords);

	// do some math
	cout << "\n\nUsing the data from \"" << file_name << "\"...\n\n";
	calculateDataset(passRecords, "avgCost");
	calculateDataset(passRecords, "classSrvRate");

	userDataFile.close();
	return 0; // finish! [EXIT PRG]
}