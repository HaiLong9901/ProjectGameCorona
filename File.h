#ifndef FILE_H_
#define FILE_H_
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
void ReadFile(const char* file);
void WriteFile(const char* file, string m);
void WriteFileCont(const char* file, string m);
int ReadFile1(const char* file);
void removeVirus(string& a, int n);
#endif // !FILE_H_

