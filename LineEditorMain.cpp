/*
@filename: Line Editor - Main


@author: Doc Holloway
@date: 10/1/2025

@description: This program operates a line editor that is able to save, load, and edit text from a file.

Compilation instructions:
Using Ubuntu 22.04:
g++ -c LineEditorMain.cpp -o main.o
g++ -c LineEditorFunctions.cpp -o sourceCode.o
g++ main.o sourceCode.o -o LineEditor

Using Visual Studio: Run local Windows debugger.

*/
#include "LineEditorDeclarations.h"
/*
* Main function contains conditions for command line prompt, variable definitions, and an infinite while loop that checks for each
* potential operation and carries out the function tied to various commands.
*
* @param[in]: A filename from the command prompt.
*
* @return: Nothing or the data of the used vector loaded into various files, as determined by user.
*/
int main(int argc, char* argv[])
{

	if (argc == 2)
	{
		read(argv[1]);
	}

	string commandLine;
	char commandChar;
	bool quitState = 0;
	bool saveState = 0;
	int currentLine = 1;
	cout << "Welcome to Line Editor! For Help, type command 'H'" << endl;

	while (quitState != 1)
	{
		getline(cin,commandLine);
		commandChar = commandLine[0];
		string argument1 = "";
		string argument2 = "";

		if (commandLine.length() > 1)
		{
			int i = 2;
			for (i; i < commandLine.length() && commandLine[i] != ' '; i++)
			{
				argument1 += commandLine[i];
			}
			if (commandLine.length() > i)
			{
				for (i; commandLine.length() && commandLine[i]; i++)
				{
					argument2 += commandLine[i];
				}
			}
		}


		if (commandChar == 'W')
		{
			write(argument1);
			saveState = 1;
		}
		else if (commandChar == 'R')
		{
			read(argument1);
			saveState = 0;
		}
		else if (commandChar == 'J')
		{
			int arg1 = stoi(argument1);
			currentLine = jumpTo(arg1, currentLine);
		}
		else if (commandChar == 'I')
		{
			insert(argument1, currentLine);
			saveState = 0;
		}
		else if (commandChar == 'A')
		{
			insertNext(argument1, currentLine);
			saveState = 0;
		}
		else if (commandChar == 'L')
		{
			if (argument1 == "")
			{
				list(1, -1);
			}
			else if (argument2 == "")
			{
				int arg1 = stoi(argument1);
				list(arg1, arg1);
			}
			else
			{
				int arg1 = stoi(argument1);
				int arg2 = stoi(argument2);
				list(arg1, arg2);
			}
			saveState = 0;
		}
		else if (commandChar == 'D')
		{
			if (argument1 == "")
			{
				deleteLine(currentLine, currentLine);
			}
			else if (argument2 == "")
			{
				int arg1 = stoi(argument1);
				deleteLine(arg1, arg1);
			}
			else
			{
				int arg1 = stoi(argument1);
				int arg2 = stoi(argument2);
				deleteLine(arg1, arg2);
			}
			saveState = 0;
		}
		else if (commandChar == 'Q')
		{
			quit(saveState);
			quitState = 1;
		}
		else if (commandChar == 'H')
		{
			help();
		}
		else
		{
			cout << "Error: Not a correct command. Please try again." << endl;
			help();
		}
		
		cout << "Current Line: " << currentLine << endl;
		cout << "Next Command (H for help): " << endl;
	}
	return 0;
}