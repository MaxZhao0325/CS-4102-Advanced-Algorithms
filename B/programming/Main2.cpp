#include<iostream>
#include<ctime>
#include<fstream>
#include"Supply.cpp"
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int main(int argc, char** argv) {
    string fileName = "test1.txt";
    ifstream inFile;
    inFile.open(fileName.c_str());

    vector<string> lines;
    string line;

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            getline(inFile, line);
            lines.push_back(line);
        }
        inFile.close(); // CLose input file
            
        // Call method and print the result
        time_t start = time(NULL);
        Supply supply;
        vector<vector<string> > temp = supply.compute(lines);
        for (int i = 0 ; i< temp.size();i++){
            cout << temp[i][0] << " " << temp[i][1] << " " << temp[i][2] << endl;
        }
        time_t end = time(NULL);
        cout << "time: " << (end - start) << "\n";
    }
    else { //Error message
        cerr << "Error opening file " << fileName << endl;
    }
}

