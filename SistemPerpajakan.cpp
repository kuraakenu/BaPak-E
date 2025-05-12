#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string fileUserPasw = "logOrReg.txt";
const string fileDataUser = "dataUser.txt";

bool loginUser(string usn, string pasw);
bool registerUser(string usn, string pasw);
void logOrReg(string &user);

int main(){
    string user;

    logOrReg(user);
    system("cls");

    cout << "Selamat Datang, " << user << "!\n";
    
    return 0;
}

// LOGIN OR REGISTER //

void logOrReg(string &user){
    system("cls");

    string usn, pasw;
    int pil;
    
    while(true){

        cout << "== Selamat Datang di BaPakE ==\n";
        cout << "[1]. Register\n";
        cout << "[2]. Login\n";
        cout << "[3]. Cek Data Kendaraan\n";
        cout << "[4]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                cout << "Username: ";
                cin >> usn;
                cout << "Password: ";
                cin >> pasw;
                if(registerUser(usn, pasw)){
                    cout << "Registrasi Sukses!\n";
                    system("pause");
                    system("cls");
                }
            break;

            case 2:
                cout << "Username: ";
                cin >> usn;
                cout << "Password: ";
                cin >> pasw;
                if(loginUser(usn, pasw)){
                    user = usn;
                    cout << "Login Sukses!\n";
                    system("pause");
                    return;
                }else{
                    cout << "Username atau Password Salah!\n";
                    system("pause");
                    system("cls");
                }
            break;
                
        }
    }
}

bool loginUser(string usn, string pasw){
    ifstream file(fileUserPasw);
    string line, us, ps;
    
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, us, ',');
        getline(ss, ps, ',');

        if(us == usn && ps == pasw){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool registerUser(string usn, string pasw){
    ifstream fileCheck(fileUserPasw);
    string line, us, ps;

    while(getline(fileCheck, line)){
        stringstream ss(line);
        getline(ss, us, ',');
        if(us == usn){
            cout << "Username Telah Digunakan!\n";
            fileCheck.close();
            return false;
        }
    }
    fileCheck.close();

    ofstream file(fileUserPasw, ios::app);
    if(file.is_open()){
        file << usn << "," << pasw << '\n';
        file.close();
        return true;
    }else{
        cout << "Gagal Mengakses File!\n";
        return false;
    }
}