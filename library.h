//g++ isearch2.cpp -o srch.exe
//time ./srch weblog.txt
#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class fileInput
{
private:
        int argc;
        char** argv;
	const char* filename;
public:
    fileInput(int ac=0, char** av=0){
        argc = ac;
        argv = av;
	//cout << "argc: " << argc << " argv: " << argv[0] << " : " << argv[1]<<endl;
    }
    int checkUsage(){
	//cout << "argc: " << argc << " argv: " << argv[0] << " : " << argv[1]<<endl;
        if (argc != 2){
            cout << "usage:\n" << argv[ 0 ] << " *FILENAME.txt*\n\n";
            return 1;
        }
	else{
	    return 0;
	}
    }
    int checkFile(){
        filename = argv[ 1 ];
	//cout << "name: " <<filename << endl;
        ifstream file(filename);
        if (!file){
            cerr << "Could not open file \"" << filename << "\"\n"<< endl;
            return 1;
        }
	else{
	    return 0;
	}
	
    }
    const char* getFilename(){
	return filename;
    }
};

class rdFile
{
private:
    const char* filename;
    vector<string> lines;

public:
    rdFile(const char* fname){
        filename = fname;
        cout << "filename: " << filename << endl;
    }
    void rdLines(){
        ifstream file(filename);
        string fileline;
        while (getline( file, fileline )){
            lines.push_back(fileline);
        }
        file.close();
    }
    vector<string> gList(){
        return lines;
    }
};

class iSearch
{
private:
    int listSize;
    vector<string> allLines;
    vector<string> Ips;
    vector<string> Urls;
    string ip;
    vector<string> uniqueIps;
    string line;
    int uniqueSize;
public:
    iSearch(int size, vector<string> listIn){
        listSize = size;
        allLines = listIn;
    }
    void sortIpsUrls(){
        for(int t = 0; t < listSize; t++){
            string list_Line = allLines.at(t);
            
            int position = list_Line.find (' ');
            Ips.push_back(list_Line.substr (0,position));
            
            string url = list_Line.substr (position);
            int position1 = url.find ('[');
            Urls.push_back(url.substr (position1));
            //cout << IPs.at(t) << "\n";
        }
    }
    void gUniqueIps(){
        for(int u = 0; u < Ips.size(); u++){
            ip = Ips.at(u);
            uniqueIps.push_back(ip); //put the ip in unique list
            int count = 0; //reset for every IP to check
            //cout << "\n" << u << " ip " << ip << endl;

            for(int w = 0; w < uniqueIps.size(); w++){ //read the IPs currently in unique vector
                line = uniqueIps.at(w);
                //cout << w << " unique " << line << endl;

                if(line.find( ip, 0 ) != string::npos){//check if the IP exists in unique list, count will increment for every time it finds it
                    count++;	              
                    //cout << "found : count :" << count << endl;
                }
            }
            if(count > 1){//If the IP inserted already exists in uniqueIP remove it
                uniqueIps.pop_back();
            }
        }
        uniqueSize = uniqueIps.size();
    }

    void pUniqueIps(){
        cout << "unique IP list" << endl;
        for(int x = 0; x < uniqueSize; x++){
            cout << uniqueIps.at(x) << endl;
        }
    }
    void pIps_W_Urls(){//Prints the URLs with the same IP
        for(int y = 0; y < uniqueSize; y++){
            ip = uniqueIps.at(y);
            cout << "\n" << ip << endl;
            for(int z = 0; z < listSize; z++){ //Read the entire list(file)
                line = allLines.at(z);
                if(line.find( ip, 0 ) != string::npos){ //Prints the URLs that match IP
                        cout << "\t" << Urls.at(z) << endl;
                }
            }
        }
        cout << "Size:" << uniqueSize << endl;
    }
};
#endif

