#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;

const string fileUserPasw = "infoLogin.csv";
const string fileDataUser = "dataUser.csv";
const string fileProfileUser = "profileUser.csv";

bool loginUser(string usn, string pasw);
bool registerUser(string usn, string pasw);
void firstMenu(string &usn);
void profileUser(string &usn);
void mainMenu();
void tambahKendaraan(string &usn);
void tambahTotalKendaraan(string &usn);
void listKendaraan(string &usn);
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
    int pil;

    firstMenu(user);

    while(pil != 5){
        system("cls");
        cout << "Selamat Datang, " << user << "!\n";
        cout << "[1]. Menambah Kendaraan\n";
        cout << "[2]. Membayar Pajak\n";
        cout << "[3]. Info Kendaraan\n";
        cout << "[4]. Info Pajak\n";
        cout << "[6]. Profile\n";
        cout << "[7]. LOG OUT\n";
        cout << "[8]. EXIT\n";
        cout << "Input: ";
        // cout << "[4]. Tambah Teman\n"; == Coming Soon ==
        cin >> pil;

        switch(pil){
            case 1:
                tambahKendaraan(user);
            break;
            case 3:
                listKendaraan(user);
            break;
            case 6:
                profileUser(user);
            break;
            case 7:
                cout << "Anda Akan diarahkan ke Menu Awal!\n";
                system("pause");
                firstMenu(user);
            break;
            case 8:
                cout << "Terimakasih Telah Mengunjungi BaPakE!\n";
                system("pause");
                exit(0);
            
        }
    }
}


void profileUser(string &usn){
    system("cls");
    ifstream fileCheck(fileProfileUser);
    users u;
    string lines;
    bool sudahAda = false;

    if(!fileCheck.is_open()){
        cout << "File Tidak Ada, File Baru Akan Dibuat!\n";
        system("pause");
        ofstream createFile(fileProfileUser);
        createFile.close();
    }

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

        
        file << usn << ',' << u.NIK << ',' << u.namaUser << ',' << u.jenisKelamin << ',' << '0' << '\n';
        file.close();
        
        cout << "Profile Berhasil Dilengkapi!\n";
        system("pause");
        return;
    }else{
        tambahTotalKendaraan(usn);
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

void listKendaraan(string &usn){
    ifstream file(fileDataUser);
    string line;

    if(!file.is_open()){
        cout << "File Tidak Ada, File Baru Akan Dibuat!\n";
        system("pause");
        ofstream createFile(fileProfileUser);
        createFile.close();
    }

    bool sudahAda = false;

    while(getline(file, line)){
        if(line.rfind(usn + ',', 0) == 0){
            sudahAda = true;
            break;
        }
    }

    
    if(sudahAda){
        ifstream fileCount(fileDataUser);
        string linez;

        int count = 0;
        while(getline(fileCount, linez)){
            if(linez.rfind(usn + ',', 0) == 0){
                count += 1;
            }
        }

        ifstream files(fileDataUser);
        string lines;
        int i = 0;

        while(getline(files,lines)){
            if(lines.rfind(usn + ',', 0) == 0){
                system("cls");
                i += 1;
                cout << "Berikut Informasi Kendaraan Anda: \n";
                cout << "---------------------------------------------\n";
                string noPol, jenis, merk, model, warna, tahunProduksiStr;
                stringstream ss(lines);
        
                getline(ss, usn, ',');
                getline(ss, noPol, ',');
                getline(ss, jenis, ',');
                getline(ss, merk, ',');
                getline(ss, model, ',');
                getline(ss, warna, ',');
                getline(ss, tahunProduksiStr, ',');

                cout << "No Polisi          : " << noPol << '\n';
                cout << "Jenis Kendaraan    : " << jenis << '\n';
                cout << "Merk               : " << merk << '\n';
                cout << "Model              : " << model << '\n';
                cout << "Warna              : " << warna << '\n';
                cout << "Tahun Produksi     : " << tahunProduksiStr << '\n';
                cout << "---------------------------------------------\n";

                cout << "Page " << i << "/" << count << '\n';
                system("pause");
            }
        }

    }else{
        system("cls");
        cout << "Silakan ke Menu [6] Untuk Melengkapi Profile Terlebih Dahulu!\n";
        system("pause");
        return;
    }
}

void tambahKendaraan(string &usn){
    system("cls");

    ifstream fileCheck(fileProfileUser);
    string lines;

    if(!fileCheck.is_open()){
        cout << "File Tidak Ada, File Baru Akan Dibuat!\n";
        system("pause");
        ofstream createFile(fileProfileUser);
        createFile.close();
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
        cout << "Data Kendaraan Berhasil Ditambahkan!\n";
        system("pause");
        return;

    }else{
            system("cls");
            cout << "Silakan ke Menu [6] Untuk Melengkapi Profile Terlebih Dahulu!\n";
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
            system("pause");
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

void tambahTotalKendaraan(string &usn){
    ifstream fileCount(fileDataUser);
    string line;
    
    int count, Jkend;
    count = 0;
    
    while(getline(fileCount, line)){
        if(line.rfind(usn + ',', 0) == 0){
            count += 1;
        }
    }
    
    Jkend = count;
    
    ifstream fileInput(fileProfileUser);
    vector <string> changedLine;
    string linez;

    while(getline(fileInput, linez)){
        stringstream ss(linez);
        string usrnm, nik, nama, gender, jKendaraan;
        getline(ss, usrnm, ',');
        getline(ss, nik, ',');
        getline(ss, nama, ',');
        getline(ss, gender, ',');
        getline(ss, jKendaraan);

        if(usrnm == usn){
            string updatedLine = usn + ',' + nik + ',' + nama + ',' + gender + ',' + to_string(Jkend);
            changedLine.push_back(updatedLine);
        }else{
        changedLine.push_back(linez);
        }

    }
    fileInput.close();

    ofstream fileOutput(fileProfileUser);
    for(const string& l : changedLine){
        fileOutput << l << '\n';
    }
    fileOutput.close();
    return;
}