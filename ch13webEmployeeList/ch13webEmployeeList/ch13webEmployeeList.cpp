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
		//doctype statement, the opening and closing html tag, the head tag and its contents, and the body tag and its contents
		*this << "<!DOCTYPE html>" << endl;
		*this << "<html>" << endl;
		*this << "<head>" << endl;
		*this << "<title>Combined Employee List</title>" << endl;
		*this << "</head>" << endl;
		*this << "<body>" << endl;
		*this << "<span style = \"color:" << aColor << "\">";
		*this << str << " <br/> ";
		*this << "</span>\n";
		*this << "</body>" << endl;
		*this << "</html>" << endl;
		
		
	}
};

void openFile(fstream& file, string descr); //prototype

int main()
{
	ColorCodedStream outputFile;
	fstream blackFile, blueFile, greenFile;
	openFile(blackFile, "black");
	openFile(blueFile, "blue");
	openFile(greenFile, "green");
	openFile(outputFile, "output");

	string blackInput, blueInput, greenInput;
	// read the first line from each file
	getline(blackFile, blackInput);
	getline(blueFile, blueInput);
	getline(greenFile, greenInput);
	
	while (blackFile || blueFile || greenFile)
	{
		if (blackFile && blueFile && greenFile)
		{
			//Both buffers have fresh data
			if (blackInput < blueInput && blackInput < greenInput)
			{
				outputFile.writeInColor(blackInput, "black");
				getline(blackFile, blackInput);
			}
			else if (blueInput < blackInput && blueInput < greenInput)
			{
				outputFile.writeInColor(blueInput, "blue");
				getline(blueFile, blueInput);
			}
			else
			{
				outputFile.writeInColor(greenInput, "green");
				getline(greenFile, greenInput);
			}
		}
		else if (blackFile && blueFile)
		{
			//Only black and blue buffers have fresh data
			if (blackInput < blueInput)
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
		else if (blackFile && greenFile)
		{
			//Only black and green buffers have fresh data
			if (blackInput < greenInput)
			{
				outputFile.writeInColor(blackInput, "black");
				getline(blackFile, blackInput);
			}
			else
			{
				outputFile.writeInColor(greenInput, "green");
				getline(greenFile, greenInput);
			}
		}
		else if (blueFile && greenFile)
		{
			//Only blue and green buffers have fresh data
			if (blueInput < greenInput)
			{
				outputFile.writeInColor(blueInput, "blue");
				getline(blueFile, blueInput);
			}
			else
			{
				outputFile.writeInColor(greenInput, "green");
				getline(greenFile, greenInput);
			}
		}
		else if (blackFile)
		{
			//Only black buffer has fresh data
			outputFile.writeInColor(blackInput, "black");
			getline(blackFile, blackInput);
		}
		else if (blueFile)
		{
			//Only blue buffer has fresh data
			outputFile.writeInColor(blueInput, "blue");
			getline(blueFile, blueInput);
		}
		else if (greenFile)
		{
			//Only green buffer has fresh data
			outputFile.writeInColor(greenInput, "green");
			getline(greenFile, greenInput);
		}
	} //end while loop
	
	blackFile.close();
	blueFile.close();
	greenFile.close();
	outputFile.close();
	
	system("pause");
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
} //end openFile function
