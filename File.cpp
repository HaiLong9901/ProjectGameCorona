#include "File.h"

void ReadFile(const char* file) {//Read a File
    ifstream  open(file, ios::in);
    if (open.fail()) {
        cout << "Failed!!!" << endl;
        return;
    }
    if (open.is_open()) {
        string line;
        while (getline(open, line)) {
            cout << line << endl;
        }
    }
    /*while(!open.eof()){
        char n;
        open>>n;
        cout<<n<<" ";
        ++line;
    }
    open.close();
    cout<<line<<endl;*/
    open.close();
}
void WriteFile(const char* file, string m) {//Write File
    ofstream Wfile(file, ios::out);
    if (Wfile.fail()) {
        cout << "Failed!!!" << endl;
        return;
    }
    Wfile <<m;
    Wfile.close();
}
void WriteFileCont(const char* file, string m) {
    ofstream Wfile(file, ios::app);
    if (Wfile.fail()) {
        cout << "Failed!!!" << endl;
        return;
    }
    Wfile << "\n" << m;
    Wfile.close();
}
int ReadFile1(const char* file) {//Read a File
    ifstream  open(file, ios::in);
    if (open.fail()) {
        cout << "Failed!!!" << endl;
        return 0;
    }        
    string line;
    if (open.is_open()) {

        while (getline(open, line)) {
            cout << line << endl;
        }
    }
    open.close();
    int x;
    x = atoi(line.c_str());
    return x;
}
void removeVirus(string& a, int n) {
    switch (n) {
    case 0: {
        a = "Virus:  ";
    }
          break;
    case 1: {
        a = "Virus:  X ";
    }
          break;
    default: break;
    }
}