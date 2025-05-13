#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string fileUserPasw = "logOrReg.txt";
const string fileDataUser = "dataUser.txt";

bool loginUser(string usn, string pasw);
bool registerUser(string usn, string pasw);
void firstMenu(string &user);

void mainMenu();
void tambahKendaraan(string user);

struct user{
    string namaUser;
    int NIK;
};

struct informasiPajak{
    string latestPembayaran;
    int masaBerlaku;
    int jumlahPajak;
    string statusPajak;
};

struct kendaraan{
    user pemilik;
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
        cout << "[3]. List Kendaraan\n";
        cout << "[4]. Informasi\n";
        cout << "[5]. EXIT\n";
        cout << "Input: ";
        // cout << "[4]. Tambah Teman\n"; == Coming Soon ==
        // cout << "[5]. Profile\n"; == Coming Soon ==
        cin >> pil;

        switch(pil){
            case 1:
                tambahKendaraan(user);
            break;
        }
    }
}

void tambahKendaraan(string user){
    system("cls");
    ofstream file(fileDataUser, ios::app);
    kendaraan k;

    cout << "Masukkan Nomor Polisi: ";
    cin.ignore();
    getline(cin, k.noPol);
    cout << "Masukkan Jenis Kendaraan(Motor/Mobil): ";
    cin >> k.jenisKendaraan;
    cout << "Masukkan Merk: ";
    cin >> k.merk;
    cout << "Masukkan Model: ";
    cin.ignore();
    getline(cin, k.model);
    cout << "Masukkan Warna: ";
    cin.ignore();
    getline(cin, k.warna);
    cout << "Masukkan Tahun Produksi: ";
    cin >> k.tahunProduksi;

    file << user << ',' << k.noPol << ',' << k.jenisKendaraan << ',' << k.merk << ',' << k.model << ',' << k.warna << ',' << k.tahunProduksi << '\n';
    file.close();
    cout << "Data Kendaraan Berhasil Ditambahkan!\n";
    system("pause");
    return;
}


































// LOGIN OR REGISTER //

void firstMenu(string &user){
    system("cls");

    string usn, pasw;
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