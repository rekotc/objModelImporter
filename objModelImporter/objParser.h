#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <map>
//#include <ifstream>


using namespace std;

class objParser
{

public:
	static void objToTxt(	const string aInFilename,
							const string aOutFilename,
							bool aVerbose = false);
private:
	
	static void getValues(ofstream& file, string& group, vector<float>& verts, vector<float>& textures, vector<float>& norms);

	//static vector<std::string> explode(string aStr, char aDelim);
};