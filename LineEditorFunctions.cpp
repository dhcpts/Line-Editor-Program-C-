/*
@filename: Line Editor Functions - Source code


@author: Doc Holloway
@date: 10/1/2025

@description: This file contains all of the functions for each command possible in the line editor.

Compilation instructions:
Using Ubuntu 22.04:
g++ -c LineEditorMain.cpp -o main.o
g++ -c LineEditorFunctions.cpp -o sourceCode.o
g++ main.o sourceCode.o -o LineEditor

Using Visual Studio: Run local Windows debugger.

*/
#include "LineEditorDeclarations.h"
//Global file objects for use in functions.
ofstream FileOut;
ifstream FileIn;
//Vector and heldFilename used for storing default save file and list of data from file.
string heldFileName = "";
vector<string> textLines;

/*
* Write function writes out vector data into a file, either determined by the user upon execution or saved as 
default when program starts. Opens file and loops out all vector data.
*
* @param[in]: A filename to write to.
*
* @return: Vector data loaded into a document capable of holding text.
*/
void write(string fileName)
{
	if (fileName == "" && heldFileName == "")
	{
		cout << "Please Enter a filename" << endl;
		getline(cin,heldFileName);
		FileOut.open(heldFileName);
	}
	else if(fileName == "")
	{
		FileOut.open(heldFileName);
	}
	else
	{
		FileOut.open(fileName);
	}
	if (textLines.empty())
	{
		FileOut.close();
		return;
	}
	int i = 0;
	for (i; i < textLines.size() - 1; i++)
	{
		FileOut << textLines[i] << endl;
	}
	FileOut << textLines[i] << endl;

	FileOut.close();
}


/*
* Read function reads in information from a file and saves it into the vector. Reads over file and copies each line into vector.
*
* @param[in]: A filename to read from.
*
* @return: A vector containing all data from read file.
*/
void read(string fileName)
{
	if (heldFileName == "")
	{
		heldFileName = fileName;
	}
	string InputString = "";
	if (fileName == "")
	{
		cout << "Error: Please add file address" << endl;
		return;
	}
	else 
	{
		FileIn.open(fileName);
		if (FileIn.is_open())
		{
			textLines.clear();

			while (getline(FileIn, InputString))
			{
				textLines.push_back(InputString);
			}
			FileIn.close();
		}
		else
		{
			cout << "Error: File does not exist. Please add name of existing file." << endl;
		}
	}
}


/*
* Jump function simply changes currentLine variable in main, modifying access to vector sections.
*
* @param[in]: New current line and existing current line.
*
* @return: Value to become current line, either new value or existing one if deemed to not change.
*/
int jumpTo(int to, int check)
{
	if (to == -1)
	{
		return textLines.size();
	}
	else if (to > -1 && to <= textLines.size())
	{
		return to;
	}
	else
	{
		cout << "Line does not exist" << endl;
		return check;
	}
}


/*
* Insert function inserts a string at the current line in the editor.
*
* @param[in]: New string to insert and current line of list.
*
* @return: Vector updated with most recent addition.
*/
void insert(string newstring, int currLine)
{
	if (textLines.size() == 0)
	{
		textLines.push_back(newstring);
		return;
	}
	int insertIndex = currLine - 1;
	string temp = textLines[insertIndex];
	textLines[insertIndex] = newstring;
	if (textLines.size() == 1)
	{
		textLines.push_back(temp);
		return;
	}
	for (int i = insertIndex + 1; i < textLines.size(); i++)
	{
		string temp2 = textLines[i];
		textLines[i] = temp;
		temp = temp2;
	}
	textLines.push_back(temp);
}

/*
* InsertNext function inserts a string at the line after the current line in the editor.
*
* @param[in]: New string to insert and current line of list.
*
* @return: Vector updated with most recent addition.
*/
void insertNext(string newstring, int currLine)
{
	if (textLines.size() == 0)
	{
		textLines.push_back(newstring);
		return;
	}
	int insertIndex = currLine;
	if (insertIndex + 1 > textLines.size())
	{
		textLines.push_back(newstring);
	}
	else
	{
		string temp = textLines[insertIndex];
		textLines[insertIndex] = newstring;
		for (int i = insertIndex + 1; i < textLines.size(); i++)
		{
			string temp2 = textLines[i];
			textLines[i] = temp;
			temp = temp2;
		}
		textLines.push_back(temp);
	}
}

/*
* Function lists desired line, desired line range, or full range of vector list of data.
*
* @param[in]: To and from lines to determine range of list.
*
* @return: A printout of each value in the list.
*/
void list(int from, int to)
{
	if (from < 1)
	{
		from = 1;
	}
	if (to > textLines.size())
	{
		to = textLines.size();
	}
	if (to == from)
	{
		if (from == -1)
		{
			cout << textLines.size() << ") " << textLines[textLines.size() - 1] << endl;
		}
		else
		{
			cout << from << ") " << textLines[from - 1] << endl;
		}
		return;
	}
	else if(from > to && to != -1)
	{
		cout << "Error: Please check order of lines." << endl;
		return;
	}
	else
	{
		if (to == -1)
		{
			to = textLines.size();
		}
		for (int i = from - 1; i <= to - 1; i++)
		{
			int line = i + 1;
			cout << line << ") " << textLines[i] << endl;
		}
	}

}

/*
* Delete function removes either one line or a range of lines from the list. Checks list size, and loops over list to scale down
* remaining values and shrink list size.
*
* @param[in]: Start and finish line numbers to establish deletion range.
*
* @return: Vector updated with most recent removal of value.
*/
void deleteLine(int lineDeleted1, int lineDeleted2)
{
	if (textLines.size() == 0)
	{
		cout << "Nothing in list to delete." << endl;
		return;
	}
	if (lineDeleted1 < 1)
	{
		lineDeleted1 = 1;
	}
	if (lineDeleted2 > textLines.size())
	{
		lineDeleted2 = textLines.size();
	}
	if (lineDeleted2 < lineDeleted1)
	{
		cout << "Error: Check order of lines in input." << endl;
		return;
	}
	if (lineDeleted2 == lineDeleted1)
	{
		if (lineDeleted2 == textLines.size())
		{
			textLines.pop_back();
			return;
		}

		for (int i = lineDeleted1 - 1; i < textLines.size() - 1; i++)
		{
			textLines[i] = textLines[i + 1];
		}
		textLines.pop_back();
	}
	else
	{
		int x = lineDeleted2 - lineDeleted1 + 1;
		for (int i = lineDeleted2; i < textLines.size(); i++)
		{
			textLines[i - x] = textLines[i];
		}
		textLines.resize(textLines.size() - x);
	}
}

/*
* Quit function results in termination of the program, but provides opportunity to save work with write if not done so.
*
* @param[in]: Boolean value determining if work has been saved.
*
* @return: Nothing or current work saved into a file via write, as needed by user.
*/
void quit(bool saved)
{
	if (saved == 0)
	{
		int x = 0;
		char confirm;
		cout << "Changes to file are unsaved. Do you wish to save to file?[Y/N]" << endl;
		while (x != 1)
		{
			cin >> confirm;
			if (confirm == 'Y')
			{
				write("");
				return;
			}
			else if (confirm == 'N')
			{
				return;
			}
			else
			{
				cout << "Invalid command, please enter Q again and select either [Y/N]" << endl;
			}
		}
	}
	else
	{
		return;
	}
}

/*
* Help function lists out commands of the line editor to assist users with operation.
*
* @param[in]: Nothing.
*
* @return: Printout of all functions and uses within line editor.
*/
void help()
{
	cout << "Function Guide (Bracketed items are optional inputs)" << endl;
	cout << "W [<filename>] - Writes the contents of the current buffer to a file." << endl;
	cout << "J <line number> - Jump to a line in the file. -1 will jump to the end of the file, 1 will jump to the beginning of the file." << endl;
	cout << "I [<some text>] - Insert the text at the current line. If no text is given, will insert a blank line" << endl;
	cout << "A [<some text>] - Insert the text after the current line. If no text is given, will insert a blank line" << endl;
	cout << "L [<line number>] [<line number>] - Lists the contents of the buffer." << endl;
	cout << "D [<line number>] [<line number>] - Deletes one or more lines. If no line numbers are given, deletes the current line." << endl;
	cout << "Q - Quits the editor." << endl;
}