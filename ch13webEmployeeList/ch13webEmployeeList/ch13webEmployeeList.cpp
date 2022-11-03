// ch13webEmployeeList.cpp

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ColorCodedStream : public fstream
{
public:
	void writeInColor(string str, string aColor)
	{
		*this << "<span style = \"color:" << aColor << "\">";
		*this << str << " <br/> ";
		*this << "</span>\n";
	}
};

void openFile(fstream& file, string descr); //prototype

int main()
{
	ColorCodedStream outputFile;
	fstream blackFile, blueFile;
	openFile(blackFile, "black");
	openFile(blueFile, "blue");
	openFile(outputFile, "output");

	string blackInput, blueInput;
	// read the first line from each file
	getline(blackFile, blackInput);
	getline(blueFile, blueInput);
	
	while (blackFile || blueFile)
	{
		if (blackFile && blueFile)
		{
			//Both buffers have fresh data
			if (blackInput <= blueInput)
			{
				outputFile.writeInColor(blackInput, "black");
				getline(blackFile, blackInput);
			}
			else
			{
				outputFile.writeInColor(blueInput, "blue");
				getline(blueFile, blueInput);
			}
		}
		if (blackFile && !blueFile)
		{
			//Only blackFile has fresh data
			outputFile.writeInColor(blackInput, "black");
			getline(blackFile, blackInput);
		}
		if (blueFile && !blackFile)
		{
			//Only blueFile has fresh data
			outputFile.writeInColor(blueInput, "blue");
			getline(blueFile, blueInput);
		}
	}
	return 0;
}
//********************************************************************
// Opens a specified file for reading or writing. The descr argument *
// is used in prompting the user for the file name.					 *
//********************************************************************
void openFile(fstream &file, string descr)
{
	string fileName;
	cout << "Enter the name of the " << descr << " file: ";
	cin >> fileName;
	
	if (descr == "output")
		file.open(fileName.c_str(), ios::out);
	else
		file.open(fileName.c_str(), ios::in);
	
	if (!file)
	{
		cout << "Error opening " << fileName << endl;
		exit(1);
	}
}