/*#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class FileHelper
{
public:
	FileHelper();

	~FileHelper();
	void Save(string path, vector<string> lines) {
		ofstream myfile(path);
		if (myfile.is_open())
		{   
			for (string line : lines)
			{
				myfile << line +"\n";
			}
			myfile.close();
		}
	}

	vector<string> Load(std::string path) {
		vector<string> lines;
		string line;
		string newline = ("\n");
		ifstream myfile(path);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				lines.push_back(line);
			}
			myfile.close();
		}
		else cout << "Unable to open file";
		return lines;
	}

	void TestSaveLoad() {
		// enabled
		bool runTest = true;
		if (!runTest) return;

		// init
		string path = "test.txt"; 
		vector<string> lines = { "asd", "bsd", "csd", "dsd", "esd" };
		
		// run
		Save(path, lines);
		vector<string> file = Load(path);

		// check results
		int failTest = 0;
		for (int i = 0; i < file.size(); i++)
		{
			if (file[i] != lines[i])
			{
				cout << "Failed test, different line " << file[i] << " != " << lines[i];
				failTest++;
			}
		}
		cout << "Test done. Fails: " << failTest;
	}
};
*/