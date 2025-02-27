#include <iostream>
#include <iomanip>

using namespace std;

void menu(int a);
int showBook(int i, int jumlahBuku);

const int  kapasitasBuku = 100;

struct buku{
    string namaBuku;
    string penerbitBuku;
    string authorBuku;
    int tahunTerbit;
    int harga;
};

buku daftarBuku[kapasitasBuku];

int main(){
    system("cls");
    bool found = false;
    char pil;
    int jumlahBuku = 0;

    do{
        menu(jumlahBuku);
        cin >> pil;

        switch(pil){
            case '1':
            system("cls");
                if(jumlahBuku < kapasitasBuku){
                    cout << "Masukkan Nama Buku: ";
                    cin.ignore();
                    getline(cin, daftarBuku[jumlahBuku].namaBuku);
                    cout << "Masukkan Penerbit Buku: ";
                    getline(cin, daftarBuku[jumlahBuku].penerbitBuku);
                    cout << "Masukkan Author Buku: ";
                    getline(cin, daftarBuku[jumlahBuku].authorBuku);
                    cout << "Masukkan Tahun Terbit: ";
                    cin >> daftarBuku[jumlahBuku].tahunTerbit;
                    jumlahBuku++;
                    system("cls");
                    cout << "===| Buku Berhasil Ditambahkan! |===\n";
                    system("pause");
                    system("cls");
                }else{
                    cout << "===| Kapasitas Rak Sudah Penuh! |===\n";
                    system("pause");
                    system("cls");
                }
            break;
            case '2':
                cout << left << setw(5) << "No" << setw(30) << "Judul Buku" << setw(30) << "Penerbit" << setw(30) << "Pengarang" << setw(15) << "Tahun Terbit" << '\n';
                showBook(0, jumlahBuku);
                system("pause");
                system("cls");
            break;
            case '3':
                cout << "Good Bye!\n";
                system("pause");
                system("cls");
            break;
            default:
            cout << "Input Salah!\n";
            system("pause");
            system("cls");
            break;
        }

    }while(pil != '3');
    
    return 0;
}

int showBook(int i, int jumlahBuku){
    if (jumlahBuku <= 0) {
        system("cls");
        cout << "==============================\n";
        cout << "|       Tidak ada buku       |\n";
        cout << "==============================\n";
        return 0;
    }
    if (i < sizeof(jumlahBuku)/sizeof(int)) {
        cout << "---------------------------------------------------------------------------------------------------------------\n";
        cout << left << setw(5) << i + 1 << setw(30) << daftarBuku[i].namaBuku << setw(30) << daftarBuku[i].penerbitBuku << setw(30) << daftarBuku[i].authorBuku << setw(15) << daftarBuku[i].tahunTerbit << '\n';
        return showBook(i + 1, jumlahBuku);
    }
}

void menu(int a){
    system("cls");
    cout << "==============| Book Store |==============\n";
    cout << "| 1. Tambah Buku                         |\n";
    cout << "| 2. Tampilkan Buku                      |\n";
    cout << "| 3. EXIT                                |\n";
    cout << "=============| " << "In Stock = " << a << " |=============\n";
    cout << "Input: ";
}