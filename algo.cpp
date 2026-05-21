#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// STRUKTUR DATA
struct Obat {
    int id;
    char nama[30];
    int stok;
    long harga;
};

// DOUBLE LINKED LIST
typedef struct Node *typeptr;

struct Node {
    Obat info;
    typeptr kiri;
    typeptr kanan;
};

typeptr awal = NULL, akhir = NULL;

// SINGLE LINKED LIST
struct NodeSingle {
    Obat info;
    NodeSingle* next;
};

NodeSingle* headSingle = NULL;

// DOUBLE LINKED LIST 
void buatListBaru() {
    awal = NULL;
    akhir = NULL;
}

int listKosong() {
    return (awal == NULL);
}

void tambahObat(Obat dataBaru) {
    typeptr NB = new Node;

    NB->info = dataBaru;
    NB->kiri = NULL;
    NB->kanan = NULL;

    if (listKosong()) {
        awal = NB;
        akhir = NB;
    } else {
        NB->kiri = akhir;
        akhir->kanan = NB;
        akhir = NB;
    }
}

// SINGLE LINKED LIST 
void tambahObatSingle(Obat dataBaru) {
    NodeSingle* baru = new NodeSingle;

    baru->info = dataBaru;
    baru->next = NULL;

    if (headSingle == NULL) {
        headSingle = baru;
    } else {
        NodeSingle* bantu = headSingle;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }
}

void tampilkanSingleList() {
    if (headSingle == NULL) {
        cout << "Single Linked List kosong.\n";
        return;
    }

    NodeSingle* bantu = headSingle;

    cout << "\n DATA SINGLE LINKED LIST \n";
    cout << "ID\tNama Obat\t\tStok\tHarga\n";
    cout << "--------------------------------------------------\n";

    while (bantu != NULL) {
        printf("%d\t%-20s\t%d\tRp%ld\n",
               bantu->info.id,
               bantu->info.nama,
               bantu->info.stok,
               bantu->info.harga);

        bantu = bantu->next;
    }
}

// QUICK SORT 
void quickSort(Obat arr[], int low, int high, int mode) {
    int i = low, j = high;

    Obat temp;
    Obat pivot = arr[(low + high) / 2];

    while (i <= j) {

        if (mode == 1) {
            while (arr[i].id < pivot.id) i++;
            while (arr[j].id > pivot.id) j--;
        }

        else if (mode == 2) {
            while (arr[i].harga < pivot.harga) i++;
            while (arr[j].harga > pivot.harga) j--;
        }

        else if (mode == 3) {
            while (arr[i].harga > pivot.harga) i++;
            while (arr[j].harga < pivot.harga) j--;
        }

        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if (low < j)
        quickSort(arr, low, j, mode);

    if (i < high)
        quickSort(arr, i, high, mode);
}

// SEARCHING 
int cariBerdasarkanID(Obat arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == key)
            return i;
    }

    return -1;
}

int cariBerdasarkanNama(Obat arr[], int n, char key[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].nama, key) == 0)
            return i;
    }

    return -1;
}

// HAPUS DATA 
void hapusObat(int idHapus) {

    if (listKosong()) {
        cout << "Data kosong.\n";
        return;
    }

    typeptr bantu = awal;

    while (bantu != NULL && bantu->info.id != idHapus) {
        bantu = bantu->kanan;
    }

    if (bantu == NULL) {
        cout << "ID tidak ditemukan.\n";
        return;
    }

    if (bantu == awal) {

        if (awal == akhir) {
            awal = akhir = NULL;
        }

        else {
            awal = awal->kanan;
            awal->kiri = NULL;
        }
    }

    else if (bantu == akhir) {
        akhir = akhir->kiri;
        akhir->kanan = NULL;
    }

    else {
        bantu->kiri->kanan = bantu->kanan;
        bantu->kanan->kiri = bantu->kiri;
    }

    delete bantu;

    cout << "Data berhasil dihapus.\n";
}

// DATA SAMPEL
void tambahDataSampel() {

    Obat sampel[5] = {
        {101, "Paracetamol", 50, 5000},
        {105, "Amoxicillin", 30, 12000},
        {102, "Vitamin C", 100, 2500},
        {104, "Obat Batuk", 25, 15000},
        {103, "Antasida", 40, 8000}
    };

    for (int i = 0; i < 5; i++) {
        tambahObat(sampel[i]);
        tambahObatSingle(sampel[i]);
    }
}

// FILE 
void simpanKeFile() {

    FILE *pf = fopen("apotek_data.dat", "wb");

    if (pf == NULL)
        return;

    typeptr bantu = awal;

    while (bantu != NULL) {
        fwrite(&bantu->info, sizeof(Obat), 1, pf);
        bantu = bantu->kanan;
    }

    fclose(pf);
}

void loadDariFile() {

    FILE *pf = fopen("apotek_data.dat", "rb");

    if (pf == NULL) {
        tambahDataSampel();
        return;
    }

    Obat temp;

    buatListBaru();

    while (fread(&temp, sizeof(Obat), 1, pf) == 1) {
        tambahObat(temp);
        tambahObatSingle(temp);
    }

    fclose(pf);
}

// TAMPIL DATA 
int hitungNode() {

    int count = 0;

    typeptr bantu = awal;

    while (bantu != NULL) {
        count++;
        bantu = bantu->kanan;
    }

    return count;
}

void tampilkanData() {

    if (listKosong()) {
        cout << "Data kosong.\n";
        return;
    }

    typeptr bantu = awal;

    cout << "\nID\tNama Obat\t\tStok\tHarga\n";
    cout << "--------------------------------------------------\n";

    while (bantu != NULL) {

        printf("%d\t%-20s\t%d\tRp%ld\n",
               bantu->info.id,
               bantu->info.nama,
               bantu->info.stok,
               bantu->info.harga);

        bantu = bantu->kanan;
    }
}

void tekanEnter() {
    cout << "\nTekan ENTER...";
    cin.ignore();
    cin.get();
}

// MAIN 
int main() {

    loadDariFile();

    int pilihan;

    do {

        system("cls");

        cout << "====================================\n";
        cout << "      SISTEM MANAJEMEN APOTEK       \n";
        cout << "====================================\n";

        cout << "1. Tambah Obat\n";
        cout << "2. Tampilkan Semua Obat\n";
        cout << "3. Pengurutan\n";
        cout << "4. Pencarian\n";
        cout << "5. Hapus Obat\n";
        cout << "6. Tampilkan Single Linked List\n";
        cout << "7. Simpan & Keluar\n";

        cout << "====================================\n";

        cout << "Pilih Menu : ";
        cin >> pilihan;

        // TAMBAH 
        if (pilihan == 1) {

            system("cls");

            Obat o;

            cout << "ID Obat   : ";
            cin >> o.id;

            cout << "Nama Obat : ";
            cin.ignore();
            cin.getline(o.nama, 30);

            cout << "Stok      : ";
            cin >> o.stok;

            cout << "Harga     : ";
            cin >> o.harga;

            tambahObat(o);
            tambahObatSingle(o);

            cout << "\nData berhasil ditambahkan.";

            tekanEnter();
        }

        // TAMPIL 
        else if (pilihan == 2) {
            system("cls");

            tampilkanData();

            tekanEnter();
        }

        // SORTING
        else if (pilihan == 3) {

            int n = hitungNode();

            Obat *tempArr = new Obat[n];

            typeptr bantu = awal;

            for (int i = 0; i < n; i++) {
                tempArr[i] = bantu->info;
                bantu = bantu->kanan;
            }

            int pSort;

            system("cls");

            cout << "1. Sort ID Ascending\n";
            cout << "2. Sort Harga Ascending\n";
            cout << "3. Sort Harga Descending\n";

            cout << "Pilih : ";
            cin >> pSort;

            quickSort(tempArr, 0, n - 1, pSort);

            buatListBaru();

            for (int i = 0; i < n; i++) {
                tambahObat(tempArr[i]);
            }

            delete[] tempArr;

            tampilkanData();

            tekanEnter();
        }

        // SEARCH
        else if (pilihan == 4) {

            int n = hitungNode();

            Obat *tempArr = new Obat[n];

            typeptr bantu = awal;

            for (int i = 0; i < n; i++) {
                tempArr[i] = bantu->info;
                bantu = bantu->kanan;
            }

            int pCari;

            system("cls");

            cout << "1. Cari ID\n";
            cout << "2. Cari Nama\n";

            cout << "Pilih : ";
            cin >> pCari;

            if (pCari == 1) {

                int idK;

                cout << "Masukkan ID : ";
                cin >> idK;

                int h = cariBerdasarkanID(tempArr, n, idK);

                if (h != -1)
                    cout << "Ditemukan : " << tempArr[h].nama;

                else
                    cout << "Tidak ditemukan.";
            }

            else if (pCari == 2) {

                char namaK[30];

                cout << "Masukkan Nama : ";

                cin.ignore();
                cin.getline(namaK, 30);

                int h = cariBerdasarkanNama(tempArr, n, namaK);

                if (h != -1)
                    cout << "Ditemukan ID : " << tempArr[h].id;

                else
                    cout << "Tidak ditemukan.";
            }

            delete[] tempArr;

            tekanEnter();
        }

        // HAPUS 
        else if (pilihan == 5) {

            system("cls");

            tampilkanData();

            int idH;

            cout << "\nMasukkan ID yang dihapus : ";
            cin >> idH;

            hapusObat(idH);

            tekanEnter();
        }

        // SINGLE LINKED LIST
        else if (pilihan == 6) {

            system("cls");

            tampilkanSingleList();

            tekanEnter();
        }

    } while (pilihan != 7);

    simpanKeFile();

    system("cls");

    cout << "====================================\n";
    cout << "   DATA BERHASIL DISIMPAN           \n";
    cout << "====================================\n";

    return 0;
}