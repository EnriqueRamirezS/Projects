#include <iostream>
#include <string>
#include <fstream>
#include "encryption.h"


using namespace std;



int main(int argc, char* argv[]){
    
    bool e = false;
    bool d = false;

    
    int key = 0;
    string input ="";
    string output = ""; 
    string inputFile = "";
    string outputFile = "";
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i]; /// makes a string to check each of the argv
        if (arg == "-e") {
            e = true;
            if(i + 1 < argc && string(argv[i + 1]) == "-d"){
            cout<<"cannot encrypt and decrypt at the same time"<<endl;
            return 0;
            }
        }
        else if(arg == "-d") {
            d = true;
            if (i + 1 < argc && string(argv[i + 1]) == "-e") {
            cout<<"cannot encrypt and decrypt at the same time"<<endl;
            return 0;
            }
        }
        else if(arg == "-k" && i + 1 < argc) {
            key = stoi(argv[i + 1]);
        } 
        else if(arg == "-i" && i + 1 < argc) {
             inputFile = argv[i + 1];
        } 
        else if(arg == "-o" && i + 1 < argc) {
             outputFile = argv[i + 1];
        }
    }
    
    
    // copy whats in the -i file into the input varible 
    if(inputFile!=""){
    ifstream inFile;
    inFile.open(inputFile);
    
    if(!inFile.is_open()){
        cout << "Unable to open file!" << endl;
        return 0;
    }
    while(!inFile.eof()){
        getline(inFile, input);
    }
    
    inFile.close();

    }
    else{
        cout<<"no input file"<<endl;
        return 0;
    }
    
    
    
    // encrypt or decrypt and put into the output file 
    if(outputFile!=""){
        
    if (e){
        for(int i = 0; i< input.length(); i++){
        output += en(input[i], key);
        }
    }
    
    if (d){
        for(int i = 0; i< input.length(); i++){
        output += de(input[i], key);
        }
    }
    
    
    ofstream outFile;
    outFile.open(outputFile);
    outFile << output << endl;
    outFile.close();
    
    }
    else {
        cout<<"No output file"<<endl;
        return 0;
    }
    
    cout<<"Done!"<<endl;
    
    
    
    return 0;
}