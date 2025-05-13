#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

const string fileUserPasw = "logOrReg.txt";
const string fileDataUser = "dataUser.txt";
const string fileProfileUser = "profileUser.txt";

bool loginUser(string usn, string pasw);
bool registerUser(string usn, string pasw);
void firstMenu(string &usn);
void profileUser(string &usn, int jKend);
void mainMenu();
void tambahKendaraan(string &usn, int *jKend);
string EditUpLowCase(string a);

struct users{
    int NIK;
    string namaUser;
    char jenisKelamin;
    int jumlahKendaraan;
};

struct informasiPajak{
    string latestPembayaran;
    int masaBerlaku;
    int jumlahPajak;
    string statusPajak;
};

struct kendaraan{
    users pemilik;
    string noPol;
    string jenisKendaraan;
    string merk;
    string model;
    string warna;
    int tahunProduksi;
    informasiPajak info;
};

int main(){
    system("cls");
    mainMenu();
    return 0;
}

void mainMenu(){
    
    string user;
    int pil, jKend;
    jKend = 0;
    firstMenu(user);

    while(pil != 5){
        system("cls");
        cout << "Selamat Datang, " << user << "!\n";
        cout << "[1]. Menambah Kendaraan\n";
        cout << "[2]. Membayar Pajak\n";
        cout << "[3]. List Kendaraan\n";
        cout << "[4]. Informasi\n";
        cout << "[6]. Profile\n";
        cout << "[7]. EXIT\n";
        cout << "Input: ";
        // cout << "[4]. Tambah Teman\n"; == Coming Soon ==
        cin >> pil;

        switch(pil){
            case 1:
                tambahKendaraan(user, &jKend);
            break;
            case 6:
                profileUser(user, jKend);
            break;
        }
    }
}


void profileUser(string &usn, int jKend){
    system("cls");
    ifstream fileCheck(fileProfileUser);
    users u;
    string lines;

    if(!fileCheck.is_open()){
        cout << "File Error!";
        system("pause");
        return;
    }

    bool sudahAda = false;

    while(getline(fileCheck, lines)){
        if(lines.rfind(usn + ',', 0) == 0){
            sudahAda = true;
            break;
        }
    }
    
    if(!sudahAda){
        fileCheck.close();
        ofstream file(fileProfileUser, ios::app);

        cout << "Hai, " << usn << "!\n";
        cout << "Silakan Lengkapi Profile Anda!\n";
        cout << "NIK: ";
        cin >> u.NIK;
        cout << "Nama Lengkap: ";
        cin.ignore();
        getline(cin, u.namaUser);

        u.namaUser = EditUpLowCase(u.namaUser);

        cout << "Jenis Kelamin(L/P): ";
        cin >> u.jenisKelamin;
        u.jenisKelamin = toupper(u.jenisKelamin);

        file << usn << ',' << u.NIK << ',' << u.namaUser << ',' << u.jenisKelamin << ',' << jKend << '\n';
        file.close();

        cout << "Profile Berhasil Dilengkapi!\n";
        system("pause");
        return;
    }else{
        ifstream file(fileProfileUser);
        cout << "Hai, " << usn << "!\n";
        cout << "Profile Anda Sebagai Berikut: \n";
        string line;

        while(getline(file,line)){
            if(line.rfind(usn + ',', 0) == 0){
                stringstream ss(line);
                string namaLengkap, nikStr, gender, jKendStr, tempUsn;
                
                getline(ss, usn, ',');
                getline(ss, nikStr, ',');
                getline(ss, namaLengkap, ',');
                getline(ss, gender, ',');
                getline(ss, jKendStr, ',');
                
                cout << "NIK               : " << nikStr << '\n';
                cout << "Nama Lengkap      : " << namaLengkap << '\n';
                cout << "Jenis kelamin     : " << gender << '\n';
                cout << "Jumlah Kendaraan  : " << jKendStr << '\n';
                break;
            }
        }

        system("pause");
        return;
    }
}


void tambahKendaraan(string &usn, int *jKend){
    system("cls");

    ifstream fileCheck(fileProfileUser);
    string lines;
    if(!fileCheck.is_open()){
        cout << "File Error!";
        system("pause");
        return;
    }

    bool sudahAda = false;

    while(getline(fileCheck, lines)){
        if(lines.rfind(usn + ',', 0) == 0){
            sudahAda = true;
            break;
        }
    }    

    if(sudahAda){
        ofstream file(fileDataUser, ios::app);
        kendaraan k;
        
        if(!file.is_open()){
            cout << "File Error!";
            system("pause");
            return;
        }
    
        cout << "Masukkan Nomor Polisi: ";
        cin.ignore();
        getline(cin, k.noPol);
        cout << "Masukkan Jenis Kendaraan(Motor/Mobil): ";
        cin >> k.jenisKendaraan;
        k.jenisKendaraan = EditUpLowCase(k.jenisKendaraan);
        cout << "Masukkan Merk: ";
        cin >> k.merk;
        k.merk = EditUpLowCase(k.merk);
        cout << "Masukkan Model: ";
        cin.ignore();
        getline(cin, k.model);
        cout << "Masukkan Warna: ";
        getline(cin, k.warna);
        k.warna = EditUpLowCase(k.warna);
        cout << "Masukkan Tahun Produksi: ";
        cin >> k.tahunProduksi;
    
        file << usn << ',' << k.noPol << ',' << k.jenisKendaraan << ',' << k.merk << ',' << k.model << ',' << k.warna << ',' << k.tahunProduksi << '\n';
        file.close();
        *jKend = *jKend + 1;
        cout << "Data Kendaraan Berhasil Ditambahkan!\n";
        system("pause");
        return;

    }else{
            cout << "Silakan ke Menu [6] Untuk Membuat Profil Terlebih Dahulu!\n";
            system("pause");
            return;
    }
}

// LOGIN OR REGISTER //

void firstMenu(string &usn){
    system("cls");

    string pasw;
    int pil;
    
    while(true){
        system("cls");

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
                    cout << "Login Sukses!\n";
                    system("pause");
                    return;
                }else{
                    cout << "Username atau Password Salah!\n";
                    system("pause");
                    system("cls");
                }
            break;
            
            case 3:
                system("cls");
                cout << "==[COMING SOON!]==\n";
                system("pause");
            break;

            case 4:
                cout << "Sampai Jumpa!\n";
                system("pause");
                exit(0);
            break;
        }
    }
}

bool loginUser(string usn, string pasw){
    ifstream file(fileUserPasw);
    string line, us, ps;
    if(!file.is_open()){
        cout << "File Error!";
        system("pause");
        return false;
    }
    
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
        cout << "File Error!\n";
        return false;
    }
}

string EditUpLowCase(string a){
        bool newWord = true;
        for(char &lw : a){
            lw = tolower(lw);
        }
        for (char &up : a){
            if(isspace(up)){
                newWord = true;
            }else if (newWord) {
                up = toupper(up);
                newWord = false;
            }
        }
    return a;
}