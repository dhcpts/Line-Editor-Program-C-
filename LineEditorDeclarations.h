#pragma once
//Libraries needed to carry out various operations
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;
//Declarations of all functions used in this program.
void write(string argument1);
void read(string argument1);
int jumpTo(int to, int check);
void insert(string newstring, int currLine);
void insertNext(string newstring, int currLine);
void list(int from, int to);
void deleteLine(int lineDeleted1, int LineDeleted2);
void quit(bool saved);
void help();
