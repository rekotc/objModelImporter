

#include "objParser.h"


void objParser::objToTxt(const string aInFilename,	const string aOutFilename,	bool aVerbose)
{
	if (aVerbose) cout << "Loading OBJ file <"
		<< aInFilename << ">" << endl;

	// Open file
	fstream objFile(aInFilename.c_str());

	if (objFile.fail())
	{
		cout << "Error: could not open file <"
			<< aInFilename << ">" << endl;
		exit(1);
	}


	// Extract verts, normals, textures, and faces
	vector<float> verts, norms, textures;
	vector<float> faces;
	std::map<string, float> faceHash;

	vector<float> finalVerts, finalNorms, finalTextures;
	vector<float> finalFaces;

	string line;
	int hashIndex = 0;

	if (aVerbose) cout << "Extracting values from file" << endl;

	string temp = "temporary.txt";
	ofstream out(temp.c_str());

	if (out.fail())
	{
		cout << "Error: could not create output file " << temp << endl;
		exit(1);
	}

	if (aVerbose) cout << "Saving data to " << temp << endl;

	out << "Vertex Count: ";

	out << "\n\n";

	out << "Data:\n\n";

	int vertexCount = 0;
	// Visit each line of the obj file
	while (getline(objFile, line))
	{
		// Extract vertex
		// Line starts with v[space]...
		//MEMO: una linea v è del tipo:
		//v 1.599700 27.217400 1.472304

		if (line[0] == 'v' && line[1] == ' ')
		{
			//acquisisco la stringa in lineVals a partire dalla prima posizione dopo "v "
			string lineVals = line.substr(2);
			float val;

			//estraggo la sottostringa val0 da lineVals,
			//prendo tutto fino al primo spazio
			string val0 = lineVals.substr(0, lineVals.find(' '));
			//lo converto e lo metto nel vettore
			val = (float)atof(val0.c_str());
			verts.push_back(val);
			//estraggo la sottostringa val1 da lineVals,
			//prendo tutto fino al secondo spazio
			string val1 = lineVals.substr(val0.length() + 1, lineVals.find(' '));
			//lo converto e lo metto nel vettore
			val = (float)atof(val1.c_str());
			verts.push_back(val);
			//estraggo la sottostringa val2 da lineVals,
			//prendo tutto a partire da subito dopo il secondo spazio
			string val2 = lineVals.substr(lineVals.find_last_of(' ') + 1);
			//lo converto e lo metto nel vettore
			val = (float)atof(val2.c_str());
			verts.push_back(val);
		}


		// Extract textures
		// Line starts with vt[space]...
		//MEMO: una linea vt è del tipo:
		//vt 0.185200 0.636700
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
		{
			string lineVals = line.substr(3);
			float val;

			string val0 = lineVals.substr(0, lineVals.find(' '));
			val = (float)atof(val0.c_str());
			textures.push_back(val);

			string val1 = lineVals.substr(val0.length() + 1, lineVals.find(' '));
			val = (float)atof(val1.c_str());
			textures.push_back(val);
		}


		// Extract normals
		// Line starts with vn[space]...
		//MEMO: una linea vn è del tipo:
		//vn - 0.225900 - 0.395600 0.890200
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
		{
			string lineVals = line.substr(3);
			float val;

			string val0 = lineVals.substr(0, lineVals.find(' '));
			val = (float)atof(val0.c_str());
			norms.push_back(val);

			string val1 = lineVals.substr(val0.length() + 1, lineVals.find(' '));
			val = (float)atof(val1.c_str());
			norms.push_back(val);

			string val2 = lineVals.substr(lineVals.find_last_of(' ') + 1);
			val = (float)atof(val2.c_str());
			norms.push_back(val);
		}


		//
		// 2. Hash faces
		//
		// Extract faces
		// Line starts with f[space]...
		//MEMO: una linea f è del tipo:
		//f 15/15/16 16/16/18 17/17/19
		//ogni faccia f è un triangolo, quindi per ogni riga f mi aspetto di trovare 3 gruppi di valori
		//un gruppo per ogni vertice del triangolo
		//prendendo ad esempio il commento di poche righe sopra, i 3 vertici saranno definiti rispettivamente da
		//15/15/15 per il primo vertice, 16/16/18 per il secondo vertice, 17/17/19 per il terzo vertice
		//prendendo poi ad esempio il primo vertice, 15/15/15 rappresenterà:
		//15 = l'indice v del vertice in questione
		//15 = l'indice t della coordinata texture associata a questo vertice
		//15 = l'indice vn della normale associata a questo vertice


		else if (line[0] == 'f' && line[1] == ' ')
		{
			vertexCount += 3;

			string lineVals = line.substr(2);

			string val0 = lineVals.substr(0, lineVals.find_first_of(' '));

			// If the value for this face includes texture and/or 
			// normal, parse them out
			//val0 contiene l'intera riga contenente i 3 gruppi, meno "f "
			//es: "4/5/12 7/5/21 8/3/4" 
			if (val0.find('/') >= 0)
			{
				// Get first group of values
				string g1;
				string g2;
				string g3;
				string temp, temp2, temp3;
				int vt, v, vn;
				g1 = val0.substr(0, val0.find(' '));

				g2 = line.substr(line.find(' ') + 2);
				g2 = g2.substr(g2.find(' ') + 1);
				g2 = g2.substr(0, g2.find(' '));

				g3 = line.substr(line.find_last_of(' ') + 1);

				getValues(out, g1, verts, textures, norms );
				getValues(out, g2, verts, textures, norms);
				getValues(out, g3, verts, textures, norms);


				

			}
		} /* end getline(file, line) */

		
	}

	// a questo punto posso aggiornare il contatore dei vertici sul file
	out.close();

	//std::ifstream infile(aOutFilename);

	//const string fileout= "tentativo.txt";
	//ofstream outUpdate(fileout.c_str());

	std::ifstream inFile(temp);
	std::ofstream outFile(aOutFilename);
	std::string linea;

	int count = 0;
	while (getline(inFile, linea)){

		if(linea.compare("Vertex Count: ") == 0)
			outFile << "Vertex Count: " << vertexCount << std::endl;
		else
			outFile << linea << std::endl;
		
		count++;
	}
	outFile.close();
	inFile.close();
	remove(temp.c_str());

			
	if (aVerbose) cout << "All done!" << endl;
	
}

//la funzione, data una stringa rappresentate un gruppo v/vt/vn , recupera i valori corrispondenti a tali indici
//es: string group = "4/13/7"
//4 rappresenta il vertice con indice 4, vado allora a recuperarne le coordinate x,y,z dall'array verts[]
//13 rappresenta le coordinate texture con indice 13, vado allora a recuperarne le coordinate u,v dall'array textures[]
//7 rappresenta le coordinate della normale con indice 7, vado allora a recuperarne le coordinate x,y,z dall'array norms[]



void objParser::getValues(ofstream& file, string& group, vector<float>& verts, vector<float>& textures, vector<float>& norms){

	int g;
	string temp = group.substr(0, group.find_first_of('/'));
	int v = (int)atoi(temp.c_str());
	g = 3 * (v - 1);
	file << verts[g] << " ";
	file << verts[++g] << " ";
	file << verts[++g] << " ";

	/*for (g = 3 * (v - 1); g <= 3 * (v - 1) + 2; g++){
		file << verts[g] << " ";
	}*/

	

	string temp2 = group.substr(temp.length() + 1, temp.find_first_of('/'));
	int vt = (int)atoi(temp2.c_str());
	for (int g = 2 * (vt - 1); g <= 2 * (vt - 1) + 1; g++){

		if (g % 2 == 0){
			file << textures[g] << " ";
		}
		else file << 1 - textures[g] << " ";
	}
	
	string temp3 = group.substr(group.find_last_of('/') + 1);
	int vn = (int)atoi(temp3.c_str());
	for (g = 3 * (vn - 1); g <= 3 * (vn - 1) + 2; g++){
		file << norms[g] << " ";
	}

	file << "\n";
}