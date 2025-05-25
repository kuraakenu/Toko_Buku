#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileLoginInfo = "loginInfo.txt";
const string fileAdmin = "adminInfo.txt";
const string fileListBuku = "listBuku.txt";
const int kapasitasBuku = 100;

// Function Edit String DLL ===========================
string spaceToUnderscore(string str);
string UnderscoreToSpace(string str);
string EditUpLowCase(string str);
// ====================================================

// Function Menu ======================================
void mainMenu();
void firstMenu(string &user, int &mode);
void adminMenu(string user);
void buyerMenu(string user);
// ====================================================

// Function Login Register ============================
bool registerUsers(string &user, string pasw);
bool loginUsers(string &user, string pasw, int &mode);
bool cekUsername(string user);
// ====================================================

// Function di dalam Menu =============================
void addBook(int tambahBuku, int jumlahBuku);
void listBook(int jumlahBuku);
void fileLoader(int *a);
void searchBook(int jumlahBuku);
void sortBook(int jumlahBuku);
void buybook(int jumlahBuku);
void removeData(int jumlahBuku);
//=====================================================

struct buku{
    string idBuku;
    string judulBuku;
    string penerbitBuku;
    string authorBuku;
    string genre;
    string tahunTerbit;
    int harga;
    int stok;
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

// Memindahkan data file kedalam Struct Array
void fileLoader(int *a){
    // klo gada file, membuat file
    ifstream fileCheck(fileListBuku);
    if(!fileCheck.is_open()){
        ofstream fileCreate(fileListBuku);
        fileCreate.close();
    }
    fileCheck.close();

    ifstream fileLoad(fileListBuku);
    string judulTemp, idTemp, authorTemp, penerbitTemp, tahunTemp, genreTemp;
    int i = 0;
    int hargaInt, stokInt;
    while(fileLoad >> idTemp >> judulTemp >> genreTemp >> authorTemp >> penerbitTemp >> tahunTemp >> hargaInt >> stokInt){
        judulTemp = UnderscoreToSpace(judulTemp);
        genreTemp = UnderscoreToSpace(genreTemp);
        authorTemp = UnderscoreToSpace(authorTemp);
        penerbitTemp = UnderscoreToSpace(penerbitTemp);

        daftarBuku[i].idBuku = idTemp;
        daftarBuku[i].judulBuku = judulTemp;
        daftarBuku[i].genre = genreTemp;
        daftarBuku[i].authorBuku = authorTemp;
        daftarBuku[i].penerbitBuku = penerbitTemp;
        daftarBuku[i].tahunTerbit = tahunTemp;
        daftarBuku[i].harga = hargaInt;
        daftarBuku[i].stok = stokInt;
        i++;
    }

    fileLoad.close();
    *a = i;
}

// Menu dari POV Atmin
void adminMenu(string user){
    
    int pil, newBook, tambahBuku;
    pil = 0;
    
    int jumlahBukuDiGudang = 0;
    while(pil != 7){
        tambahBuku = 0;
        // Fungsi Memindah File ke Struct Array
        fileLoader(&jumlahBukuDiGudang);

        system("cls");
        cout << "Hai Admin "<< user << "! \n";
        cout << "Selamat Datang di Dashboard Cihuy Online\n";
        cout << "[1]. Tambah Buku\n";
        cout << "[2]. List Buku\n"; // jika file kosong maka tidak tampil
        cout << "[3]. Cari Buku\n"; // jika file kosong maka tidak tampil
        cout << "[4]. Sort Buku\n"; // jika file kosong maka tidak tampil
        cout << "[5]. Hapus Data\n"; 
        cout << "[6]. LOGOUT\n";
        cout << "[7]. EXIT\n";
        cout << "Input: ";
        cin >> pil;
        switch(pil){
            case 1:
                cout << "Jumlah Buku Yang Ingin Ditambahkan: ";
                cin >> tambahBuku;
                if(cin.fail()){
                    cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                    cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                    cout << "Input Harus Angka!\n";
                    system("pause");
                }else{
                    addBook(tambahBuku, jumlahBukuDiGudang);
                }
            break;
            case 2:
                if(jumlahBukuDiGudang == 0){
                    cout << "Gudang Kosong!\n";
                    cout << "Tambahkan Buku Dulu!\n";
                    system("pause");
                }else{
                    listBook(jumlahBukuDiGudang);
                }
            break;
            case 3:
                if(jumlahBukuDiGudang == 0){
                    cout << "Gudang Kosong!\n";
                    cout << "Tambahkan Buku Dulu!\n";
                    system("pause");
                }else{
                    searchBook(jumlahBukuDiGudang);
                }
            break;
            case 4:
                if(jumlahBukuDiGudang == 0){
                    cout << "Gudang Kosong!\n";
                    cout << "Tambahkan Buku Dulu!\n";
                    system("pause");
                }else{
                    sortBook(jumlahBukuDiGudang);
                }
            break;
            case 5:
                if(jumlahBukuDiGudang == 0){
                    cout << "Gudang Kosong!\n";
                    cout << "Tambahkan Buku Dulu!\n";
                    system("pause");
                }else{
                    removeData(jumlahBukuDiGudang);
                }
            break;
            case 6:
                mainMenu();
            break;
            case 7:
                system("cls");
                cout << "Terimakasih Telah Berkunjung!\n";
                cout << "  (\\_/)\n";
                cout << " ( o_o)\n";
                cout << " / >[  ]>\n";
                cout << "Jangan Lupa Baca Buku!\n";
                system("pause");
                exit(0);
            break;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;
        }
    }
}

// Menambahkan Buku Menggunakan Rekursi
void addBook(int tambahBuku, int jumlahBuku){
    ofstream fileInput(fileListBuku, ios::app);
    string judulTemp, penerbitTemp, authorTemp, genreTemp, lineCheck, idTemp;
    int stokTemp;

    // Cek Apakah file ada atau tidak / terbuka atau tidak
    if(!fileInput.is_open()){
        cout << "File Error!\n";
        system("pause");
        return;
    }

    // karna rekursi, tambahBuku akan terus berkurang sampai 0
    if(tambahBuku == 0){
        fileInput.close();
        int count = 0;
        ifstream fileCount(fileListBuku);
        while(getline(fileCount, lineCheck)){ // cara kerjanya, getline akan baca kata dari fileCount sampai ke baris akhir, kalau ketemu newline di linecheck=0 maka linecheck +1, baca baris selanjutnya di linecheck = 1 dan seterusnya
            count++;
        }
        fileCount.close();

        system("cls");
        cout << "Selesai! Anda Baru Saja Menambahkan Buku Kedalam Gudang!\n";
        cout << "Di Gudang Sekarang Berisi " << count + 1 << " Judul Buku!\n"; // + 1 karena count masih menghitung file yang sblm masuk ke rekursi, setelah masuk karna blm return atau masuk rekursi lagi, datanya blm ke update 
        system("pause");
        return;
    }

    bool sudahAda = false;

    while(!sudahAda){
        system("cls");
        cout << "Masukkan ID Buku: ";
        cin >> idTemp;
    
        for(int i = 0; i < jumlahBuku; i++){
            if(daftarBuku[i].idBuku == idTemp){
                sudahAda = true;
            }
        }
        if(sudahAda){
            cout << "ID Buku Sudah Ada!\n";
            cout << "Gunakan Setelah " << idTemp << "!\n";
            system("pause");
            sudahAda = false;
        }else{
            break;
        }
    }

    cout << "Masukkan Judul Buku: ";
    cin.ignore();

    //anjay bisa, kalo judul ada, tinggal nambah stok
    getline(cin, judulTemp);
    judulTemp = EditUpLowCase(judulTemp);

    for(int i = 0; i < jumlahBuku; i++){
        if(judulTemp == daftarBuku[i].judulBuku){
            ofstream fileTrunc(fileListBuku, ios::trunc);
            cout << "Tambah Stok Buku: ";
            cin >> stokTemp;
            daftarBuku[i].stok += stokTemp;
                for(int j = 0; j < jumlahBuku; j++){
                    fileTrunc << daftarBuku[j].idBuku << ' ' << spaceToUnderscore(daftarBuku[j].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[j].genre) << ' ' << spaceToUnderscore(daftarBuku[j].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[j].penerbitBuku) << ' ' << daftarBuku[j].tahunTerbit << ' ' << daftarBuku[j].harga << ' ' << daftarBuku[j].stok << '\n';
                }
                cout << "Anda Berhasil Menambahkan Stok ke Buku " << daftarBuku[i].judulBuku << " Menjadi " << daftarBuku[i].stok << "!\n";
                system("pause");
                fileTrunc.close();
                fileInput.close();
                return;
        }
    }

    cout << "Masukkan Genre Buku: ";
    getline(cin, daftarBuku[tambahBuku].genre);
    genreTemp = EditUpLowCase(daftarBuku[tambahBuku].genre);
    genreTemp = spaceToUnderscore(genreTemp);
    
    cout << "Masukkan Author Buku: ";
    getline(cin, daftarBuku[tambahBuku].authorBuku);
    authorTemp = EditUpLowCase(daftarBuku[tambahBuku].authorBuku);
    authorTemp = spaceToUnderscore(authorTemp);

    cout << "Masukkan Penerbit Buku: ";
    getline(cin, daftarBuku[tambahBuku].penerbitBuku);
    penerbitTemp = EditUpLowCase(daftarBuku[tambahBuku].penerbitBuku);
    penerbitTemp = spaceToUnderscore(penerbitTemp);

    cout << "Masukkan Tahun Terbit: ";
    cin >> daftarBuku[tambahBuku].tahunTerbit;
    cout << "Masukkan Harga Buku: ";
    cin >> daftarBuku[tambahBuku].harga;

    cout << "Masukkan Jumlah Stok: ";
    cin >> daftarBuku[tambahBuku].stok;

    fileInput << idTemp << ' ' << spaceToUnderscore(judulTemp) << ' ' << genreTemp << ' ' << authorTemp << ' ' << penerbitTemp << ' ' << daftarBuku[tambahBuku].tahunTerbit << ' ' << daftarBuku[tambahBuku].harga << ' ' << daftarBuku[tambahBuku].stok << '\n';
    system("cls");

    // masukkin ke struct array, biar kebaca data barunya. karna ini rekursi dan fileLoader ada di Menu, jadi tidak terbaca kalau tidak ditambahkan ke struct array dulu
    daftarBuku[jumlahBuku].idBuku = idTemp;
    daftarBuku[jumlahBuku].judulBuku = judulTemp;
    daftarBuku[jumlahBuku].genre = genreTemp;
    daftarBuku[jumlahBuku].authorBuku = authorTemp;
    daftarBuku[jumlahBuku].penerbitBuku = penerbitTemp;
    daftarBuku[jumlahBuku].tahunTerbit = daftarBuku[tambahBuku].tahunTerbit;
    daftarBuku[jumlahBuku].harga = daftarBuku[tambahBuku].harga;
    daftarBuku[jumlahBuku].stok = daftarBuku[tambahBuku].stok;

    return addBook(tambahBuku - 1, jumlahBuku + 1);
}

// Menampilkan List Buku Yang Ada Di File
void listBook(int jumlahBuku){
    // Output
    system("cls");
    cout << string(65, '=') << '\n';
    cout << left << setw(15) << "ID" << setw(25) << "Judul" << setw(15) << "Stok" << setw(15) << "Harga" << '\n';
    cout << string(65, '=') << '\n';
    for(int f = 0; f < jumlahBuku; f++){
        cout << left << setw(15) << daftarBuku[f].idBuku << setw(25) << daftarBuku[f].judulBuku << setw(15) << daftarBuku[f].stok << setw(15) << daftarBuku[f].harga << '\n';
    }
    cout << string(65, '=') << '\n';
    system("pause");

}

// Mencari Buku di dalam Struct Array menggunakan Sequential Search
void searchBook(int jumlahBuku){
    int pil = 0;
    while(pil != 4){
        system("cls");
        cout << "[1]. Cari Judul Buku\n";
        cout << "[2]. Cari Author Buku\n";
        cout << "[3]. Cari Genre Buku\n";
        cout << "[4]. BACK\n";
        cout << "Input: ";
        cin >> pil;

        string cari;
        int i, j;
        bool found = false;

        switch(pil){
            case 1: // Sequential without Sentinel
                cout << "Masukkan Judul Buku: ";
                cin.ignore();
                getline(cin, cari);
                cari = EditUpLowCase(cari);
                i = 0;
                while(i <= jumlahBuku){
                    if(daftarBuku[i].judulBuku == cari){
                        found = true;
                        break;
                    }else{
                        i += 1;
                    }
                }
                if(!found){
                    cout << "Judul Buku " << cari << " Tidak Tersedia!\n";
                }else{
                    system("cls");
                    cout << "Buku Ditemukan!\n";
                    cout << "-\n";
                    cout << "=================================================\n";
                    cout << "Judul Buku     : " << daftarBuku[i].judulBuku << '\n';
                    cout << "Genre          : " << daftarBuku[i].genre << '\n';
                    cout << "Author         : " << daftarBuku[i].authorBuku << '\n';
                    cout << "Penerbit       : " << daftarBuku[i].penerbitBuku<< '\n';
                    cout << "Tahun Terbit   : " << daftarBuku[i].tahunTerbit << '\n';
                    cout << "Harga          : " << daftarBuku[i].harga << '\n';
                    cout << "Stok           : " << daftarBuku[i].stok << '\n';
                    cout << "=================================================\n";
                }
                system("pause");
            break;
            case 2: // Sequential without Sentinel
                cout << "Masukkan Author Buku: ";
                cin.ignore();
                getline(cin, cari);
                cari = EditUpLowCase(cari);
                j = 0;
                system("cls");
                cout << string(45, '=') << '\n';
                cout << left << setw(30) << "Judul" << setw(8) << "Stok" << setw(6) << "Harga" << '\n';
                cout << string(45, '=') << '\n';

                for(int i = 0; i <= jumlahBuku; i++){
                    if(daftarBuku[i].authorBuku == cari){
                        cout << left << setw(30) << daftarBuku[i].judulBuku << setw(8) << daftarBuku[i].stok << setw(6) << daftarBuku[i].harga << '\n';
                        found = true;
                        j++;
                    }
                }
                cout << string(45, '=') << '\n';

                if(!found){
                    system("cls");
                    cout << "Buku Dengan Author " << cari << " Tidak Tersedia!\n";
                }
                system("pause");

            break;
            case 3: // Sequential without Sentinel
                cout << "Masukkan Genre Buku: ";
                cin.ignore();
                getline(cin, cari);
                cari = EditUpLowCase(cari);
                j = 0;
                system("cls");
                cout << string(45, '=') << '\n';
                cout << left << setw(30) << "Judul" << setw(8) << "Stok" << setw(6) << "Harga" << '\n';
                cout << string(45, '=') << '\n';

                for(int i = 0; i <= jumlahBuku; i++){
                    if(daftarBuku[i].genre == cari){
                        cout << left << setw(30) << daftarBuku[i].judulBuku << setw(8) << daftarBuku[i].stok << setw(6) << daftarBuku[i].harga << '\n';
                        found = true;
                        j++;
                    }
                }
                cout << string(45, '=') << '\n';

                if(!found){
                    system("cls");
                    cout << "Buku Dengan Genre " << cari << " Tidak Tersedia!\n";
                }
                system("pause");
            break;
            case 4:
                // disini dikasi cin clear biar klo misal input 4a, a nya ga kebawa ke menu returnnya
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                return;
            break;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;
        }
    }

}

// Mensortir Buku di dalam Struct Array menggunakan Quick Sort
void sortBook(int jumlahBuku){
    system("cls");
    int pil = 0;
    bool done = false;
    while(pil != 3){
        system("cls");
        cout << "[1]. Urutkan Berdasarkan Judul\n";
        cout << "[2]. Urutkan Berdasarkan Harga\n";
        cout << "[3]. BACK\n";
        cout << "Input: ";
        cin >> pil;
        int temp;
        switch(pil){
            case 1: // Bubble Sort
                for(int i = 0; i < jumlahBuku - 1; i++){
                    for(int j = 0; j < jumlahBuku - 1 - i; j++){
                        if(daftarBuku[j].judulBuku > daftarBuku[j+1].judulBuku){
                            buku temp = daftarBuku[j];
                            daftarBuku[j] = daftarBuku[j+1];
                            daftarBuku[j+1] = temp;
                        }
                    }
                }
                done = true;
            break;
            case 2: // Straight Selection Sort
                for(int i = 0; i < jumlahBuku; i++){
                    for(int j = i + 1; j < jumlahBuku; j++){
                        if(daftarBuku[i].harga > daftarBuku[j].harga){
                            buku temp = daftarBuku[i];
                            daftarBuku[i] = daftarBuku[j];
                            daftarBuku[j] = temp;
                        }
                    }
                }
                done = true;
            break;
            case 3:
                // disini dikasi cin clear biar klo misal input 4a, a nya ga kebawa ke menu returnnya
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                return;
            break;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;
        }

        if(done){
            ofstream SaveFile(fileListBuku, ios::out);
            for(int i = 0; i < jumlahBuku; i++){
                SaveFile << daftarBuku[i].idBuku << " " << spaceToUnderscore(daftarBuku[i].judulBuku) << " " << spaceToUnderscore(daftarBuku[i].genre) << " " 
                << spaceToUnderscore(daftarBuku[i].authorBuku) << " " << spaceToUnderscore(daftarBuku[i].penerbitBuku)<< " " <<
                daftarBuku[i].tahunTerbit << " " << daftarBuku[i].harga << " " << daftarBuku[i].stok << '\n';
            }
            SaveFile.close();
            cout << "Data Telah Berhasil Diurutkan dan Disimpan Kedalam File\n";
            system("pause");
        }else{
            cout << "Gagal Mensort Data!\n";
            system("pause");
            return;
        
        }
    }
}


void removeData(int jumlahBuku){
    int pil = 0;
    bool terhapus = false;
    string cari;
    while(pil != 3 && !terhapus){
        system("cls");
        cout << "[1]. Hapus Menggunakan ID Buku\n";
        cout << "[2]. Hapus Menggunakan Judul Buku\n";
        cout << "[3]. BACK\n";
        cout << "Input: ";
        cin >> pil;
        
        switch(pil){
            case 1:
                cout << "Masukkan ID Buku: ";
                cin >> cari;
                for(int i = 0; i < jumlahBuku; i++){
                    if(cari == daftarBuku[i].idBuku){
                        for(int j = i; j < jumlahBuku - 1; j++){
                            daftarBuku[j] = daftarBuku[j + 1];
                        }
                        jumlahBuku--;
                        terhapus = true;
                    }
                }
            break;
            case 2:
                cout << "Masukkan Judul Buku: ";
                cin >> cari;
                for(int i = 0; i < jumlahBuku; i++){
                    if(cari == daftarBuku[i].judulBuku){
                        for(int j = i; j < jumlahBuku - 1; j++){
                            daftarBuku[j] = daftarBuku[j + 1];
                        }
                        jumlahBuku--;
                        terhapus = true;
                    }
                }
            break;
            case 3:
                // disini dikasi cin clear biar klo misal input 4a, a nya ga kebawa ke menu returnnya
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                return;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;
        }
    }

    if(terhapus){
        ofstream fileTrunc(fileListBuku, ios::trunc);
        for(int j = 0; j < jumlahBuku; j++){
            fileTrunc << daftarBuku[j].idBuku << ' ' << spaceToUnderscore(daftarBuku[j].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[j].genre) << ' ' << spaceToUnderscore(daftarBuku[j].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[j].penerbitBuku) << ' ' << daftarBuku[j].tahunTerbit << ' ' << daftarBuku[j].harga << ' ' << daftarBuku[j].stok << '\n';
        }
        fileTrunc.close();
        cout << "Buku Telah Terhapus!\n";
        system("pause");
    }else{
        cout << "Buku Tidak Ditemukan!\n";
        system("pause");
    }
}

void buybook(int jumlahBuku){
    string cari; char balik;
    int i, j, bayar, kembalian, jmlhbli, totalharga;
    bool found = false, lanjut;
    system("cls");
    cout << "Masukkan judul buku : ";
    cin.ignore();
    getline(cin, cari);
    cari = EditUpLowCase(cari);
    i = 0;
    while(i <= jumlahBuku){
        if(daftarBuku[i].judulBuku == cari){
            found = true;
            break;
        }else{
            i += 1;
        }
    }
    if(!found){
        cout << "Judul Buku " << cari << " Tidak Tersedia!\n";
    }else{
        cout << "Berikut Detil Buku yang ingin dibeli!\n";
        cout << "Judul : " << daftarBuku[i].judulBuku << '\n';
        cout << "Harga : " << daftarBuku[i].harga << '\n';
        cout << "Stok  : " << daftarBuku[i]. stok << '\n';
        cout << "-\n";
        cout << "Jumlah buku yang ingin dibeli : ";
        cin >> jmlhbli;

        if(daftarBuku[i].stok < jmlhbli){
            cout << "Stok Tidak Cukup!\n";
            system("pause");
            return;
        }

        totalharga = daftarBuku[i].harga * jmlhbli;

        daftarBuku[i].stok = daftarBuku[i].stok - jmlhbli;

        cout << "Total Harga : " << totalharga << endl;
        cout << "-\n";
        cout << "Silahkan Melakukan Pembayaran\n";
        cout << "Masukkan Nominal Uang :";
        cin >> bayar;

        if(bayar >= totalharga){
            system("cls");
            kembalian = bayar - totalharga;
            cout << "Pembayaran Berhasil\n";
            cout << "-\n\n";
            cout << "===============================================\n";
            cout << "                 Nota Pembelian\n";
            cout << "-----------------------------------------------\n\n";
            cout << "                Toko Buku Cihuyy\n";
            cout << "===============================================\n";
            cout << "| " <<  left   << setw(20) << "Judul Buku"  
                 << "| " << setw(10) << "Jumlah" 
                 << "| " << setw(10) << "Harga"   << "|\n";
            cout << "-----------------------------------------------\n";
            cout << "| " <<  left  << setw(20) << daftarBuku[i].judulBuku 
                 << "| " << setw(10) << jmlhbli 
                 << "| " << setw(10) << daftarBuku[i].harga << "|\n";
            cout << "===============================================\n";
            cout << "| Total Harga         : " << totalharga << endl;
            cout << "| Uang Dibayarkan     : " << bayar << endl;
            cout << "| Kembalian           : " << kembalian << endl;
            cout << "===============================================\n\n";
            cout << "Terimakasih Telah Membeli Buku\n";
            ofstream fileTrunc(fileListBuku, ios::trunc);
            for(int j = 0; j < jumlahBuku; j++){
                    fileTrunc << daftarBuku[j].idBuku << ' ' << spaceToUnderscore(daftarBuku[j].judulBuku) << ' ' << spaceToUnderscore(daftarBuku[j].genre) << ' ' << spaceToUnderscore(daftarBuku[j].authorBuku) << ' ' << spaceToUnderscore(daftarBuku[j].penerbitBuku) << ' ' << daftarBuku[j].tahunTerbit << ' ' << daftarBuku[j].harga << ' ' << daftarBuku[j].stok << '\n';
                }
            fileTrunc.close();

        } else if(bayar < totalharga){
            cout << "Maaf Uang Anda Tidak Cukup\n";
            cout << "Silahkan mengulang\n";
        }
    }
    system("pause");
}

// Menu dari POV Buyer
void buyerMenu(string user){
    int pil = 0;
    int jumlahBukuDiToko = 0;
    while(pil != 6){
        system("cls");
        fileLoader(&jumlahBukuDiToko);
        cout << "Hai "<< user << "! \n";
        cout << "Selamat Datang di Toko Buku Cihuy\n";
        cout << "[1]. Beli Buku\n"; 
        cout << "[2]. List Buku\n"; 
        cout << "[3]. Cari Buku\n"; 
        cout << "[4]. Sort Buku\n";
        cout << "[5]. LOGOUT\n";
        cout << "[6]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                if(jumlahBukuDiToko == 0){
                    cout << "Buku Habis!\n";
                    cout << "Toko Sedang Tutup!\n";
                    system("pause");
                }else{
                    // gas coy
                    buybook(jumlahBukuDiToko);
                }
            break;
            case 2:
                if(jumlahBukuDiToko == 0){
                    cout << "Buku Habis!\n";
                    cout << "Toko Sedang Tutup!\n";
                    system("pause");
                }else{
                    listBook(jumlahBukuDiToko);
                }
            break;
            case 3:
                if(jumlahBukuDiToko == 0){
                    cout << "Buku Habis!\n";
                    cout << "Toko Sedang Tutup!\n";
                    system("pause");
                }else{
                    searchBook(jumlahBukuDiToko);
                }
            break;
            case 4:
                if(jumlahBukuDiToko == 0){
                    cout << "Buku Habis!\n";
                    cout << "Toko Sedang Tutup!\n";
                    system("pause");
                }else{
                    sortBook(jumlahBukuDiToko);
                }
            break;
            case 5:
                mainMenu();
            break;
            case 6:
                system("cls");
                cout << "Terimakasih Telah Berkunjung!\n";
                cout << "  (\\_/)\n";
                cout << " ( o_o)\n";
                cout << " / >[  ]>\n";
                cout << "Jangan Lupa Baca Buku!\n";
                system("pause");
                exit(0);
            break;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;

        }

    }
}

void firstMenu(string &user, int &mode){ // kenapa pake reference user? karena biar ga perlu return dan nilai yang di mainMenu() terganti sementara dengan perubahan user yang ada disini, mode juga gitu
    int pil = 0;
    string pasw;

    while(true){ //infinite loop, akan berhenti jika ada break, return dan exit
        system("cls");
        cout << "|| Selamat Datang di Toko Buku Cihuy ||\n";
        cout << "[1]. Register\n";
        cout << "[2]. Login\n";
        cout << "[3]. EXIT\n";
        cout << "Input: ";
        cin >> pil;

        switch(pil){
            case 1:
                cout << "Username: ";
                cin.ignore();
                getline(cin, user);
                if(cin.fail()){
                    cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                    cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                    cout << "Input Harus Angka!\n";
                    system("pause");
                }else{
                    if(cekUsername(user)){
                        cout << "Password: ";
                        cin >> pasw;
                        if(registerUsers(user, pasw)){ // klo hasil return true
                            cout << "Registrasi Berhasil! Silakan Login!\n";
                            system("pause");
                        }
                    }
                }
                break;
                
            case 2:
                cout << "Username: ";
                cin.ignore();
                getline(cin, user);
                if(cin.fail()){
                    cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                    cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                    cout << "Input Harus Angka!\n";
                    system("pause");
                }else{
                    if(cekUsername(user)){
                        cout << "Password: ";
                        cin >> pasw;
                        if(loginUsers(user, pasw, mode)){ // klo hasil return true
                            cout << "Login Berhasil!\n";
                            system("pause");
                            return;
                        }
                    }
                }
            break;
            case 3:
                system("cls");
                cout << "Terimakasih Telah Berkunjung!\n";
                cout << "  (\\_/)\n";
                cout << " ( o_o)\n";
                cout << " / >[  ]>\n";
                cout << "Jangan Lupa Baca Buku!\n";
                system("pause");
                exit(0);
            break;
            default:
                cin.clear();              // Reset status cin kembali ke normal, gampangnya misal tipe data int tapi input string, nah error kan, nah yang di reset itu status errornya jadi normal
                cin.ignore(1000, '\n');  // 10000 adalah jumlah karakter yang diabaikan, '\n' sampai ditemukan enter/newline, fungsi cin.ignorenya buat buang karakter di buffer input
                cout << "Input Salah!\n";
                system("pause");
            break;
        }
    }
}

bool registerUsers(string &user, string pasw){ 

    ifstream fileCheck(fileLoginInfo);
    ifstream fileAdminCheck(fileAdmin);
    string tempUsn;
    bool sudahAda = false; 
    bool admin = false;

    if(!fileCheck.is_open()){
        cout << "File Error!\n";
        system("pause");
        return false;
    }

    while(fileAdminCheck >> tempUsn){ // ini cek perkata di file user admin, "aku " gitu. password jg kena cek sih 
        if(tempUsn == user){ // klo ada admin, true
            admin = true; 
        }
    }

    if(admin){ // klo true, kena return false;
        cout << "Username Telah Digunakan!\n";
        system("pause");
        return false;
    }else{ // klo false, lanjut cek di file user buyer
        while(fileCheck >> tempUsn){ // ini cek perkata di file user buyer, "aku " gitu. password jg kena cek sih
            if(tempUsn == user){ 
                sudahAda = true;
            }
        }
    }

    if(sudahAda){
        cout << "Username Telah Digunakan!\n";
        system("pause");
        return false;
    }

    fileCheck.close();

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

    while(fileCheckAdmin >> tempUsn >> tempPasw){ // ini cek di perkata di file, "aku " gitu. password jg kena cek sih 
        if(tempUsn == user){ // nah disini itu yang dicek file admin dlu, jadi klo username ada di admin, dia admin
            adminCoy = true;
            fileCheckAdmin.close();
            break;
        }
    }

    if(adminCoy){ // klo true dia admin, mode 1, cek mode 1 itu buat apa di mainMenu()
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
    }else{ // klo false dia user buyer, tapi cek dulu ada gk usernamenya, klo ada true
        while(fileCheckUsers >> tempUsn >> tempPasw){
            if(tempUsn == user){
                userCoy = true;
                fileCheckUsers.close();
                break;
            }
        }
    }

    if(userCoy){ // klo true dia user buyer , mode 2, cek mode 2 itu buat apa di mainMenu()
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
    }else{ // ini kalo usercoy false, username gada di file user buyer ama admin
        cout << "Username Tidak Ada! Silakan Register Terlebih Dahulu!\n";
        fileCheckUsers.close();
        system("pause");
        return false;
    }

}

string spaceToUnderscore(string str){
    string temp = str;

    for(int i = 0; i < str.length(); i++){ // loop nya i < panjang str
        if(temp[i] == ' '){ // cek dlu ada space atau ga 
            temp.replace(i,1,1,'_'); // klo ada, direplace sesuai urutan spasi di char tempnya, 1 pertama itu jumlah char yg di hapus, 1 kedua itu banyak char si '_' buat gantiin yang diapus
        }
    }

    return temp;
}

string UnderscoreToSpace(string str){
    string temp = str;

    for(int i = 0; i < str.length(); i++){ // loop nya i < panjang str
        if(temp[i] == '_'){ // cek dlu ada space atau ga 
            temp.replace(i,1,1,' '); // klo ada, direplace sesuai urutan underscore di char tempnya, 1 pertama itu jumlah char yg di hapus, 1 kedua itu banyak char si ' ' buat gantiin yang diapus
        }
    }
 
    return temp;
}

string EditUpLowCase(string str){
    bool newWord = true; // apakah awal kata baru

    for(char &lw : str){ // loop mengubah semua char di str menjadi kecil , // : adalah range-based loop, melakukan pengulangan untuk setiap elemen str
        lw = tolower(lw); // mengubah char yang ada di variabel lw menjadi kecil
    }

    for(char &up : str){
        if(isspace(up)){ // cek apakah char tersebut merupakan spasi, jika iya, next char bakal kapital
            newWord = true; // setelah spasi adalah awal kata baru
        }else if(newWord){ // dan jika new word, char selanjutnya setelah spasi
            up = toupper(up); // mengubah char yang ada di variabel up menjadi kapital
            newWord = false; // setelah diubah artinya, next char bukan kapital
        }
    }

    return str;
}

bool cekUsername(string user){

    bool space = false;

    for(char &up : user){
        if(isspace(up)){
            space = true;
            break;
        }
    }

    if(space){
        cout << "Username Tidak Boleh Ada Spasi!\n";
        system("pause");
        return false;
    }else{
        return true;
    }
}