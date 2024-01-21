// Ömer Çağrı Sarıgöl 2312721005 Bir milyoncu envanter takip sistemi
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
using namespace std;

struct Urun
{
    char urunAdi[80];
    unsigned int urunMiktari;
    unsigned int urunFiyati;
};

// Urun1'e Urun2'yi kopyalar
void urunKopyala(Urun &urun1, Urun &urun2)
{
    strcpy(urun1.urunAdi, urun2.urunAdi);
    urun1.urunFiyati = urun2.urunFiyati;
    urun1.urunMiktari = urun2.urunMiktari;
}

void urunYazdir(Urun &urun)
{
    cout << "   Urunun Adi: " << urun.urunAdi << endl;
    cout << "   Urunun miktari: " << urun.urunMiktari << endl;
    cout << "   Urunun fiyati: " << urun.urunFiyati << endl;
}

void charDizisiAl(const string &yazdirilacak, char a[], int boyut)
{
    cin.ignore();
    cout << yazdirilacak;
    cin.getline(a, boyut);
}

void intAl(const string &yazdirilacak, unsigned int &a)
{
    cout << yazdirilacak;
    cin >> a;
}

void UrunEkle()
{
    Urun urun;
    ofstream yaz("urunler.dat", ios::binary | ios::app);
    char secim;
    do
    {
        charDizisiAl("Urunun Adini Giriniz: ", urun.urunAdi, sizeof(urun.urunAdi));
        intAl("Urunun Miktarini Giriniz:", urun.urunMiktari);
        intAl("Urunun Fiyatini Giriniz:", urun.urunFiyati);

        yaz.write((char *)&urun, sizeof(urun));
        cout << urun.urunAdi << " basariyla eklendi." << endl;
        cout << "Baska Kayit Eklemek Ister misiniz? (E/H)" << endl;
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');
    yaz.close();
}

void UrunleriListele()
{
    Urun urun;
    ifstream oku("urunler.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(urun);
    cout << "Toplam Urun Sayisi:" << kayits << endl;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(urun));
            oku.read((char *)&urun, sizeof(urun));

            cout << i + 1 << ". Urunun Bilgileri" << endl;
            urunYazdir(urun);
        }
    }
    else
    {
        cout << "Kayit Bulunamadi..." << endl;
    }
    oku.close();
}

void UrunArama()
{
    Urun urun;
    ifstream oku("urunler.dat", ios::binary | ios::app);
    bool bulundu = false;

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(urun);

    char urunAdi[80];
    charDizisiAl("Aranan urunun adini giriniz: ", urunAdi, sizeof(urunAdi));

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(urun));
            oku.read((char *)&urun, sizeof(urun));

            if (strcmp(urun.urunAdi, urunAdi) == 0)
            {
                bulundu = true;
                cout << "Bulunan Urunun Bilgileri" << endl;
                urunYazdir(urun);
            }
        }
    }
    if (!bulundu)
        cout << "Kayit Bulunamadi..." << endl;

    oku.close();
}

void UrunSil()
{
    Urun urun;
    char urunAdi[80];
    char secim = ' ';
    bool var = false;
    ifstream oku("urunler.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(urun);

    charDizisiAl("Kaydini Sileceginiz Urun Adini Giriniz : ", urunAdi, sizeof(urunAdi));

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(urun));
        oku.read((char *)&urun, sizeof(urun));

        if (strcmp(urun.urunAdi, urunAdi) == 0)
        {
            cout << endl;
            cout << "Urunun";
            cout << "   Adi: " << urun.urunAdi;
            cout << "   Miktari: " << urun.urunMiktari;
            cout << "   Fiyati: " << urun.urunFiyati;
            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if (secim == 'H' || secim == 'h')
            {
                Urun y_urun;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

                strcpy(y_urun.urunAdi, urun.urunAdi);
                y_urun.urunFiyati = urun.urunFiyati;
                y_urun.urunMiktari = urun.urunMiktari;
                y_dosya.write((char *)&y_urun, sizeof(y_urun));
                y_dosya.close();
            }
            if (secim == 'e' || secim == 'E')
            {
                var = true;
            }
        }
        else
        {
            Urun y_urun;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

            strcpy(y_urun.urunAdi, urun.urunAdi);
            y_urun.urunFiyati = urun.urunFiyati;
            y_urun.urunMiktari = urun.urunMiktari;
            y_dosya.write((char *)&y_urun, sizeof(y_urun));
            y_dosya.close();
        }
    }
    oku.close();
    if (var)
    {
        remove("urunler.dat");
        rename("Yedek.dat", "urunler.dat");
        cout << "\n Kayit Silindi" << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kayit Bulunamadi" << endl;
    }
}

void UrunDuzenle()
{
    Urun urun;
    char urunAdi[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("urunler.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(urun);

    cout << "Kaydini Duzelteceginiz Urun Adini Giriniz : ";
    cin >> urunAdi;

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(urun));
        oku.read((char *)&urun, sizeof(urun));

        if (strcmp(urun.urunAdi, urunAdi) == 0)
        {

            cout << endl;
            cout << "Urunun";
            cout << "   Adi: " << urun.urunAdi;
            cout << "   Miktari: " << urun.urunMiktari;
            cout << "   Fiyati: " << urun.urunFiyati;
            cout << "\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H] : ";

            secim = getche();
            if (secim == 'E' || secim == 'e')
            {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                intAl("Urunun yeni miktarini giriniz: ", urun.urunMiktari);
                intAl("Urunun yeni fiyatini giriniz: ", urun.urunFiyati);
                cout << endl;

                dosya.write((char *)&urun, sizeof(urun));
                dosya.close();
            }
            else
            {
                Urun y_urun;
                ofstream y_dosya;
                y_dosya.open("Yedek.dat", ios::app | ios::binary);

                strcpy(y_urun.urunAdi, urun.urunAdi);
                y_urun.urunFiyati = urun.urunFiyati;
                y_urun.urunMiktari = y_urun.urunMiktari;

                y_dosya.write((char *)&y_urun, sizeof(y_urun));
                y_dosya.close();
            }
        }
    }
    oku.close();
    if (var)
    {
        remove("urunler.dat");
        rename("Yedek.dat", "urunler.dat");
        cout << "\nKayit Duzeltildi." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\nKayit Bulunamadi" << endl;
    }
}

int main()
{
    char anamenu;
    do
    {
        cout << "|-------Hosgeldiniz------|" << endl;
        cout << "|      Secim Yapiniz     |" << endl;
        cout << "|    1- Urun Ekleme      |" << endl;
        cout << "|    2- Urun Listeleme   |" << endl;
        cout << "|    3- Urun Arama       |" << endl;
        cout << "|    4- Urun Sil         |" << endl;
        cout << "|    5- Urun Duzenle     |" << endl;
        cout << "|------------------------|" << endl;
        char secim;
        cin >> secim;

        switch (secim)
        {
        case '1':
        {
            UrunEkle();
            break;
        }
        case '2':
        {
            UrunleriListele();
            break;
        }
        case '3':
        {
            UrunArama();
            break;
        }
        case '4':
        {
            UrunSil();
            break;
        }
        case '5':
        {
            UrunDuzenle();
            break;
        }
        }
        cout << "Anamenuye Donmek icin: a basin cikmak icin: c" << endl;
        anamenu = getche();
        cout << endl;
    } while (anamenu != 'c');

    return 0;
}
