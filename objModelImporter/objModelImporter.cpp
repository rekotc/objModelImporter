#include <ostream>
#include <iostream>
#include <string>
#include "objParser.h"
//versione iniziale
using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2)
		cout << "Usage: " << argv[0]
		<< " [output filename] [input filename] [0|1 = verbose]"
		<< endl;

	string obj_filename;
	string out_filename;
	


	if (argc > 1)
	{
		out_filename = argv[1];
		out_filename += ".txt";
		obj_filename = argv[1];
		obj_filename += ".obj";
	}
	else
	{
		cout << "Enter name of .obj file to parse: ";
		getline(cin, obj_filename);
		out_filename = obj_filename + ".txt";
		obj_filename += ".obj";
		
	
	}

	bool verbose = true;
	if (argc > 2)
		if (argv[2][0] != '0')
			verbose = true;

	objParser::objToTxt(obj_filename, out_filename, verbose);

	return 0;
}
