#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileLoginInfo = "loginInfo.csv";
const string fileAdmin = "adminInfo.csv";
const int kapasitasBuku = 100;

void mainMenu();
void firstMenu(string &user, int &mode);
void adminMenu(string user);
void buyerMenu(string user);

bool registerUsers(string &user, string pasw);
bool loginUsers(string &user, string pasw, int &mode);

struct buku{
    string namaBuku;
    string penerbitBuku;
    string authorBuku;
    string genre;
    int tahunTerbit;
    int harga;
};
buku daftarBuku[kapasitasBuku];

int main(){
    system("cls");
    mainMenu();
    return 0;
}

void mainMenu(){

    string user;
    int mode = 0;
    firstMenu(user, mode);

    switch(mode){
        case 1:
            system("cls");
            adminMenu(user);
        break;
        case 2:
            system("cls");
            buyerMenu(user);
        break;
    }
}

void adminMenu(string user){
    cout << "Hai Admin "<< user << "! \n";
    cout << "Selamat Datang di Dashboard GaraMedia Online\n";
    cout << "[1]. Tambah Buku\n"; // ya kaya tambah buku biasa, masukin dulu ke struct array baru masukin ke file, formatnya (judul, genre, penulis, penerbit, tahun terbit)
    cout << "[2]. List Buku\n"; // showing judul dari buku aja, nanti contohnya misal 
                                //1. Buku A
                                //2. Buku B
                                //3. dst
                                // 4. back
    cout << "[3]. Cari Buku\n"; // fungsi cari yg di file gw blm tau kek apa si, buat apa aja yang penting bisa dicari, nanti pas dah ketemu dibuat list kek gini aja atau buat sendiri lah bebas
                                // =================================================
                                // Judul Buku   : Buku A
                                // Genre        : Seegs
                                // Penulis      : Wahyu
                                // Penerbit     : blabal
                                // Tahun Terbit : 2424
                                // =================================================
                                // menu back
    cout << "[4]. EXIT\n";
    cout << "Input: ";
}

void buyerMenu(string user){
    cout << "Hai "<< user << "! \n";
    cout << "Selamat Datang di GaraMedia Online\n";
    cout << "[1]. Beli Buku\n"; // beli buku dibuat ada struknya si yak, jadi pas user udh cekout brp buku, insert duitnya, nanti muncul struknya
    cout << "[2]. List Buku\n"; // jadiin 1 fungsi aja ama yang versi adminnya, sama soalnya tinggal panggil doang
    cout << "[3]. Cari Buku\n"; // jadiin 1 fungsi aja ama yang versi adminnya, sama soalnya tinggal panggil doang, kasih kondisi tambahan deh, abis dicari, ada menu beli, kek gini
                                // =================================================
                                // Judul Buku   : Buku A
                                // Genre        : Seegs
                                // Penulis      : Wahyu
                                // Penerbit     : blabal
                                // Tahun Terbit : 2424
                                // =================================================
                                // menu beli // ini ngarah ke fungsi menu Beli Buku
                                // menu back
    cout << "[4]. EXIT\n";
    cout << "Input: ";
}


void firstMenu(string &user, int &mode){
    int pil;
    string pasw;

    while(true){
        system("cls");
        cout << "|| Selamat Datang di GaraMedia ||\n";
        cout << "[1]. Register\n";
        cout << "[2]. Login\n";
        cout << "[3]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pasw;
                if(registerUsers(user, pasw)){
                    cout << "Registrasi Berhasil! Silakan Login!\n";
                    system("pause");
                }
                break;
                
            case 2:
                cout << "Username: ";
                cin >> user;
                cout << "Password: ";
                cin >> pasw;
                if(loginUsers(user, pasw, mode)){
                    cout << "Login Berhasil!\n";
                    system("pause");
                    return;
                }
            break;
            case 3:
                cout << "Terimakasih Telah Berkunjung!\n";
                system("pause");
                exit(0);
            break;
            default:
                cout << "Input Salah!\n";
                system("pause");
        }
    }
}

bool registerUsers(string &user, string pasw){

    // Check apakah username available or tidak

    ifstream fileCheck(fileLoginInfo);
    string tempUsn;
    bool sudahAda = false;

    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileCheck >> tempUsn){
        if(tempUsn == user){
            sudahAda = true;
        }
    }

    if(sudahAda){
        cout << "Username Telah Digunakan!\n";
        system("pause");
        return false;
    }

    fileCheck.close();

    // Jika, available lanjut 

    ofstream fileInput(fileLoginInfo, ios::app);
    fileInput << user << ' ' << pasw << '\n';
    fileInput.close();

    return true;
}

bool loginUsers(string &user, string pasw, int &mode){
    ifstream fileCheckAdmin(fileAdmin);
    ifstream fileCheckUsers(fileLoginInfo);
    string tempUsn, tempPasw;
    bool adminCoy = false;
    bool userCoy = false;

    if(!fileCheckAdmin.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    if(!fileCheckUsers.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileCheckAdmin >> tempUsn >> tempPasw){
        if(tempUsn == user){
            adminCoy = true;
            fileCheckAdmin.close();
            break;
        }else{
            break;
        }
    }

    if(adminCoy){
        if(tempPasw != pasw){
            cout << "Username atau Password Admin Salah!\n";
            system("pause");
            fileCheckAdmin.close();
            return false;
        }else{
            fileCheckAdmin.close();
            mode = 1;
            return true;
        }
    }else{
        while(fileCheckUsers >> tempUsn >> tempPasw){
            if(tempUsn == user){
                userCoy = true;
                fileCheckUsers.close();
                break;
            }
        }
    }

    if(userCoy){
        if(tempPasw != pasw){
            cout << "Username atau Password Salah!\n";
            system("pause");
            fileCheckUsers.close();
            return false;
        }else{
            fileCheckUsers.close();
            mode = 2;
            return true;
        }
    }else{
        cout << "Username Tidak Ada! Silakan Register Terlebih Dahulu!\n";
        fileCheckUsers.close();
        system("pause");
        return false;
    }

}

