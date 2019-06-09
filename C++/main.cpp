#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <fstream>


//wyszukiwanie
//edycja
// problem ze strzalkami w wpisywaniu(pojawiaja sie litery)
//oraz wybieranie
//wyglad

using namespace std;
CONSOLE_SCREEN_BUFFER_INFO csbi;// Zawiera informacje o buforze ekranu konsoli.
HANDLE uchwytDoKonsoli = GetStdHandle( STD_OUTPUT_HANDLE );//Pobiera uchwyt do okreœlonego urz¹dzenia (standardowe wejœcie, standardowe wyjœcie, standardowe wyjœcie b³êdów).


class kontakt{
public:
    char nazwisko[20];
    char imie[20];
    char miejscowosc[50];
    char numer[12];

    kontakt(char _nazwisko[],char _imie[],char _numer[],char _miejscowosc[]){
        strcpy(nazwisko,_nazwisko);
        strcpy(imie,_imie);
        strcpy(miejscowosc,_miejscowosc);
        strcpy(numer,_numer);
    }

    kontakt(){
        strcpy(nazwisko,"");
        strcpy(imie,"");
        strcpy(miejscowosc,"");
        strcpy(numer,"");
    }

    void wypisz(){
    cout<<nazwisko;
    for(int i(0);i<20-strlen(nazwisko);i++)cout<<" ";
    cout<<imie;
    for(int i(0);i<20-strlen(imie);i++)cout<<" ";
    cout<<miejscowosc;
    for(int i(0);i<50-strlen(miejscowosc);i++)cout<<" ";
    cout<<numer;
    for(int i(0);i<12-strlen(numer);i++)cout<<" ";
    cout<<endl;
    }

    void dodajKontakt(){
        cout<<"Nazwisko :";
        cin>>nazwisko;
        cout<<"Imie :";
        cin>>imie;
        cout<<"Miejsce zamieszkania :";
        cin>>miejscowosc;
        cout<<"Numer :";
        cin>>numer;
        cout<<miejscowosc;
    }
};

    int BialeTloCzarneLitery=240;
    int CzarneTloBialeLitery=15;
    int BialeTlo=255;
    int CzarneTlo=0;
    int domyslneNieWybrane=15;
    int domyslneWybrane=240;
    int domyslneKontaktyDoWypisanieNaStrone=3;
    int domyslneObramowanie[6]={187,201,188,200,186,205};//lewy gorny,prawy gorny, lewy dolne, prawy dolny, poziome ,pionowo

    char szukane[50]={""};

    int Obramowanie0[6]={187,201,188,200,186,205};
    int Obramowanie1[6]={178,178,178,178,178,178};
    int Obramowanie2[6]={177,177,177,177,177,177};

    int ktoreObramwanie=0;
    int Obramowanie[6]={187,201,188,200,186,205};//lewy gorny,prawy gorny, lewy dolne, prawy dolny, poziome ,pionowo
    int NieWybrane=15;
    int Wybrane=240;

    int PoprzedniaNieWybrana=NieWybrane;
    int PoprzedniaWybrana=Wybrane;




class ksiazka
{
    private:
        kontakt *t[1001];
    public:
        char nazwaPliku[50];
        int n;
        int kontaktyDoWypisaniaNaStrone=3;

        ksiazka()
        {
            this->n=0;
            this->nazwaPliku[0]=NULL;
        }

    void ustawKolor(int kolor){
    SetConsoleTextAttribute(uchwytDoKonsoli,kolor);
    }

    void srodkowanie(char co[]){
        GetConsoleScreenBufferInfo(uchwytDoKonsoli, &csbi);
        int szerkosciKonsoli = csbi.srWindow.Right;//ustala wiekosc tabelki w prawo
        int wysokoscKonsoli = csbi.srWindow.Bottom;//ustala wiekosc tabelki w dol
        csbi.dwCursorPosition.X=(szerkosciKonsoli/2)-(strlen(co)/2);
        SetConsoleCursorPosition(uchwytDoKonsoli, csbi.dwCursorPosition);
        cout<<co;
    }

    void ustawianieKursora(int x=0,int y=0){
    csbi.dwCursorPosition.X=x;
    csbi.dwCursorPosition.Y=y;
    SetConsoleCursorPosition(uchwytDoKonsoli, csbi.dwCursorPosition);
    }

    void obramowanieWypiszKontakty(){

        //GetConsoleScreenBufferInfo(uchwytDoKonsoli, &csbi);
        int szerkosciKonsoli = csbi.srWindow.Right;//ustala wiekosc tabelki w prawo
        int wysokoscKonsoli = csbi.srWindow.Bottom;//ustala wiekosc tabelki w dol
        cout<<(char)Obramowanie[1];
        for(int i(0);i<szerkosciKonsoli-2;i++)cout<<(char)Obramowanie[5];
        cout<<(char)Obramowanie[0]<<endl;
        cout<<(char)Obramowanie[4];
        ustawKolor(BialeTlo);
        for(int i(0);i<(szerkosciKonsoli-2)/2-30;i++)cout<<" ";
        ustawKolor(NieWybrane);
        if(szerkosciKonsoli%2!=0){
                cout<<" Wyszukaj :";
        }else {
            cout<<"Wyszukaj :";
        }
        for(int i(0);i<50;i++)cout<<" ";
        ustawKolor(BialeTlo);
        for(int i(0);i<((szerkosciKonsoli-2)/2-30);i++)cout<<" ";
        ustawianieKursora((szerkosciKonsoli-2)/2-18,1);
        ustawKolor(NieWybrane);
        cout<<szukane;
        ustawKolor(BialeTlo);
        ustawianieKursora(szerkosciKonsoli-1,1);
        ustawKolor(NieWybrane);
        cout<<(char)Obramowanie[4]<<endl;//pion
        cout<<(char)Obramowanie[3];
        for(int i(0);i<szerkosciKonsoli-2;i++)cout<<(char)Obramowanie[5];
        cout<<(char)Obramowanie[2]<<endl;
        cout<<"Nazwisko";
        for(int i(0);i<12;i++)cout<<" ";
        cout<<"Imie";
        for(int i(0);i<16;i++)cout<<" ";
        cout<<"Miejscowosc";
        for(int i(0);i<39;i++)cout<<" ";
        cout<<"Numer";
        for(int i(0);i<7;i++)cout<<" ";
    }

    void przepisywanieObramowan(int Obramowanie_0[], int Obramowanie_1[]){
        for(int i(0);i<6;i++)
            Obramowanie_0[i]=Obramowanie_1[i];
    }

    int PobieranieZnaku(){
        char znak;
        while(true){
            if(kbhit()){
            znak=getch();
            return znak;
            }
        }
    }

    int PobiernieZnakowZOgraniczeniam(char doCzego[],int ile,int czyNumer=0, bool czyDuzeZnaki=0){
        int i=0;
        while(i<ile-1){
            doCzego[i]=PobieranieZnaku();
            if((int)doCzego[i]!=8 && (int)doCzego[i]!=13){
                    if(i==0 && doCzego[i]<='z' && doCzego[i]>='a' && czyNumer!=2 || doCzego[i]<='z' && doCzego[i]>='a' && doCzego[i-1]==' ' && czyDuzeZnaki==1 && i<ile-1 && czyNumer!=2){
                        doCzego[i]=doCzego[i]-' ';
                    }
                    if(doCzego[i]!=' ' && i<ile-1 && doCzego[i]<='z' && doCzego[i]>='a' && czyNumer==0 || doCzego[i]!=' ' && doCzego[i]<='Z' && doCzego[i]>='A' && czyNumer==0 && i<ile-1 || doCzego[i]==' ' && i<ile-1){
                        cout<<doCzego[i];
                        i++;
                    }else if(i<ile-1 && czyNumer==1 && doCzego[i]<='9' && doCzego[i]>='0'){
                        cout<<doCzego[i];
                        i++;
                    }
                    if(doCzego[i]!=' ' && doCzego[i]<='z' && doCzego[i]>='a' && i<ile-1 && czyNumer==2 || doCzego[i]!=' ' && doCzego[i]<='9' && doCzego[i]>='0'  && i<ile-1 && czyNumer==2 || doCzego[i]!=' ' && doCzego[i]<='Z' && doCzego[i]>='A' && czyNumer==2 && i<ile-1){
                        cout<<doCzego[i];
                        i++;
                    }
            }else if((int)doCzego[i]==8 && i>0){
                cout<<"\b \b";
                i--;
            }else if((int)doCzego[i]==13){
                doCzego[i]=NULL;
                return 0;
            }
            if((int)doCzego[i]==27){
                return 27;
            }
        }
        doCzego[i]=NULL;
    }

    void obramowanieMenu(){
        GetConsoleScreenBufferInfo(uchwytDoKonsoli, &csbi);
        int szerkosciKonsoli = csbi.srWindow.Right;//ustala wiekosc tabelki w prawo
        int wysokoscKonsoli = csbi.srWindow.Bottom;//ustala wiekosc tabelki w dol
        cout<<(char)Obramowanie[1];
        for(int i(0);i<szerkosciKonsoli-2;i++)cout<<(char)Obramowanie[5];
        cout<<(char)Obramowanie[0]<<endl;
        for(int i(0);i<wysokoscKonsoli-1;i++){
            ustawianieKursora(0,i+1);
            cout<<(char)Obramowanie[4];
            ustawianieKursora(szerkosciKonsoli-1,i+1);
            cout<<(char)Obramowanie[4]<<endl;
        }
        cout<<(char)Obramowanie[3];
        for(int i(0);i<szerkosciKonsoli-2;i++)cout<<(char)Obramowanie[5];
        cout<<(char)Obramowanie[2]<<endl;
    }

    void przepisywanieWDol(int i, int n,int CzyRowne=0){
        t[1001]=t[n];
        int dlugoscTable=n;
        for(int j(n-i+(CzyRowne));j>0;j--,dlugoscTable--){
            t[dlugoscTable+1]=t[dlugoscTable];
        }
        t[i+(!CzyRowne)]=t[1001];
    }

    void przepisywanieWGore(int i){
        for(int a(i);a<n;a++){
            t[a]=t[a+1];
        }
        n--;
    }

    void wczystajDomyslneUstawienia(){
        NieWybrane=domyslneNieWybrane;
        Wybrane=domyslneWybrane;
        przepisywanieObramowan(Obramowanie,domyslneObramowanie);
        kontaktyDoWypisaniaNaStrone=domyslneKontaktyDoWypisanieNaStrone;
    }

    void strzalki_litery(){
    cout<<"Wcisniecie strzalki w prawo spowoduje wpisanie znaku: 'M'"<<endl;
    cout<<"Wcisniecie strzalki w lewo spowoduje wpisanie znaku: 'K'"<<endl;
    cout<<"Wcisniecie strzalki w gora spowoduje wpisanie znaku 'H'"<<endl;
    cout<<"Wcisniecie strzalki w dol spowoduje wpisanie znaku 'P'"<<endl;
    }

    int sortowanie(){
        for(int i(0);i<n;i++){
            if(t[i]->nazwisko[0]>t[n]->nazwisko[0]){//Jesli dodany kontakt powinien byc wyzej
                przepisywanieWDol(i,n,1);
                n++;
                return 0;
            }else
                if(t[i]->nazwisko[0]==t[n]->nazwisko[0]){
                    for(int j(1);j<(strlen(t[i]->nazwisko));j++){
                        if(t[i]->nazwisko[j]>t[n]->nazwisko[j]){//jesli dodany kontakt powinien byc wyzej
                            przepisywanieWDol(i,n,1);
                            n++;
                            return 0;
                        }else if(t[i]->nazwisko[j]<t[n]->nazwisko[j]){//jesli dodany kontakt powinien byc nizej
                                przepisywanieWDol(i,n);
                                n++;
                                return 0;
                                }
                        }
                        if(t[i]->nazwisko[strlen(t[i]->nazwisko)]==NULL && t[n]->nazwisko[strlen(t[i]->nazwisko)]==NULL){
                            if(t[n]->imie[0]==NULL){
                                przepisywanieWDol(i,n,1);
                                n++;
                                return 0;
                            }
                        //imie
                        for(int k(1);k<(strlen(t[i]->imie));k++){
                            if(t[i]->imie[k]>t[n]->imie[k]){//jesli dodany kontakt powinien byc wyzej
                                przepisywanieWDol(i,n);
                                n++;
                                return 0;
                            }else if(t[i]->imie[k]<t[n]->imie[k]){//jesli dodany kontakt powinien byc nizej
                                    przepisywanieWDol(i,n,1);
                                    n++;
                                    return 0;
                                    }
                            }
                        }
            }
        }
        n++;
    }

    int wypiszMenu(){
        int n=8;
        int wybrane=0;
        char menu[n][40]={
            {"Wypisz kontakty"},
            {"Dodaj kontakt"},
            {"Zapisz kontakty"},
            {"Wczytaj ksiazke z pliku tekstowego"},
            {"Wczytaj ksiazke z pliku binarnego"},
            {"Ustawienia"},
            {"Instrukcja oraz Pomoc"},
            {"Wyjdz"}};
        int i=0;
        while(true){
            obramowanieMenu();
            for(int i(0);i<n;i++){
            ustawianieKursora(1,i+1);
            if(wybrane==i){
                ustawKolor(Wybrane);
            }else{
                ustawKolor(NieWybrane);
            }
            srodkowanie(menu[i]);
            cout<<endl;
            }
            ustawianieKursora(0,0);
            switch(PobieranieStrzalek()){
                case 1://gora
                    if(wybrane==0){
                        wybrane=n-1;
                    }else{
                        wybrane--;
                        ustawKolor(NieWybrane);
                    }
                    break;
                case 2://dol
                    if(wybrane==n-1){
                        wybrane=0;
                        ustawKolor(NieWybrane);
                    }else{
                        wybrane++;
                    }
                    break;
                case 3://enter
                    switch(wybrane){
                        case 0:
                            szukane[0]=NULL;
                            wypisz();
                            break;
                        case 1:
                            dodajKontakt();
                            break;
                        case 2:
                            zapisz();
                            break;
                        case 3:
                            wczytajZPilikuTekstowego();
                            break;
                        case 4:
                            wczytajZPilikuBinernego();
                            break;
                        case 5:
                            ustawienia();
                            break;
                        case 6:
                            system("cls");
                            strzalki_litery();
                            cout<<endl;
                            cout<<"Jezeli wystepuje jaki kolwiek problem z wpisywaniem nalezy wylaczyc i wlaczyc program."<<endl;
                            cout<<endl;
                            cout<<"Jezeli obraz jest zle ulozony nalerzy powiekszyc okno"<<endl;
                            cout<<endl;
                            cout<<"Mozliwe jest tworzenie pustych kontaktow"<<endl;
                            cout<<endl;
                            cout<<"Wciskajac klawisz 'spacja', bedac w czlonie 'wypisz kontakty' \nzostanie uruchomiona funkcja wyszukaj kontakt, \npo wpisaniu wybranej frazy nalezy nacisnac enter.\nBedac w tym trybie nie nalezy uzywac funkcji usun, ktora znajduje sie pod klawiszem 'deleta"<<endl;
                            cout<<endl;
                            cout<<"Wciskajac klawisz 'Delete', bedac w czlonie 'wypisz kontakty' \nzostanie uruchomiona funkcja usuwajaca wybrany kontakt."<<endl;
                            cout<<endl;
                            cout<<"Poruszanie mozliwe jest za pomoca klawiszy: strzalka w gore, strzalka w dol,\nstrzalka w lewo zmniejsza wybrany parametr, strzalka w prawo zwieksza go."<<endl;
                            cout<<endl;
                            cout<<"Zapisujac kontakty nalezy podac nazwe bez rozszerzen, np .txt"<<endl;
                            cout<<"Wczytujac kontakty z pliku tekstowego badz binarnego nalezy podac nazwe bez rozszerzenia, np .txt"<<endl;
                            cout<<endl;
                            cout<<"Nacisnij dowolny klawisz aby wrocic do menu"<<endl;
                            getch();
                            break;
                        case 7:
                            ustawKolor(NieWybrane);
                            system("cls");
                            return 0;
                        default:
                            continue;
                        }
                        break;
                case 4:
                    ustawKolor(NieWybrane);
                    system("cls");
                    return 0;
                default:
                    continue;
                }
                system("cls");
            }
        }

    int wyszukiwanie(){
        int szerkosciKonsoli=csbi.srWindow.Right;
        ustawianieKursora((szerkosciKonsoli-2)/2-18,1);
        cout<<"                                                  ";
        ustawianieKursora((szerkosciKonsoli-2)/2-18,1);
        if(PobiernieZnakowZOgraniczeniam(szukane,50,2,0)==27){
            szukane[0]=NULL;
        };
    }

    int ustawienia(){
        int wybrane=0;
        int a=8;
        int zmiennaPomocniczaDoTekstuWybrany=0;
        int zmiennaPomocniczaDoTekstuNieWybrany=15;
        int zmiennaPomocniczaDoTlaWybrany=0;
        int zmiennaPomocniczaDoTlaNieWybranyWybrany=0;
        int wysokoscKonsoli = csbi.srWindow.Bottom;//ustala wiekosc tabelki w dol
        char ustawienieTeks[a][60]={
            {"Ilosc kontaktow do wyswietlenia na strone : "},
            {"Kolot tekstu (niewybranego) : "},
            {"Kolot tekstu (wybranego) : "},
            {"Kolot tla (niewybranego) : "},
            {"Kolot tla (wybranego) : "},
            {"Obramowanie :"},
            {"Przywroc domyslne"},
            {"Wyjscie"}};
        while(true){
        system("cls");
        obramowanieMenu();
        ustawianieKursora(0,1);
        for(int i(0);i<a;i++){
            if(wybrane==i){
                ustawKolor(Wybrane);
            }else{
                ustawKolor(NieWybrane);
            }
            srodkowanie(ustawienieTeks[i]);
            switch(i){
                case 0:
                    cout<<kontaktyDoWypisaniaNaStrone<<endl;
                    break;
                case 1:
                    ustawKolor(NieWybrane);
                    cout<<"Tekst"<<endl;
                    break;
                case 2:
                    ustawKolor(Wybrane);
                    cout<<"Tekst"<<endl;
                    break;
                case 3:
                    ustawKolor(NieWybrane);
                    cout<<"Tlo"<<endl;
                    break;
                case 4:
                    ustawKolor(Wybrane);
                    cout<<"Tlo"<<endl;
                    break;
                case 5:
                    cout<<ktoreObramwanie<<endl;
                    break;
                default:
                    cout<<endl;
                    break;
            }
        }
        ustawianieKursora();
            switch(PobieranieStrzalek()){
                case 1://gora
                    if(wybrane==0){
                        wybrane=a-1;
                    }else{
                        ustawKolor(NieWybrane);
                        wybrane--;
                    }
                    break;
                case 2://dol
                    if(wybrane==a-1){
                        ustawKolor(NieWybrane);
                        wybrane=0;
                    }else{
                        wybrane++;
                    }
                    break;
                case 6://lewo
                    switch(wybrane){
                        case 0:

                            if(kontaktyDoWypisaniaNaStrone>1){
                                kontaktyDoWypisaniaNaStrone--;
                            }
                            break;
                        case 1:
                            if(NieWybrane%16!=0){
                                NieWybrane--;
                            }else{
                                NieWybrane+=15;
                            }
                            break;
                        case 2:
                            if(Wybrane%16!=0){
                                Wybrane--;
                            }else{
                                Wybrane+=15;
                            }
                            break;
                        case 3:
                            if(NieWybrane-16>0){
                                NieWybrane-=16;
                            }
                            break;
                        case 4:
                            if(Wybrane-16>0){
                                Wybrane-=16;
                            }
                            break;
                        case 5://obramowanie
                            if(ktoreObramwanie==0){
                                ktoreObramwanie=2;
                                przepisywanieObramowan(Obramowanie,Obramowanie2);
                            }else if(ktoreObramwanie==1){
                                przepisywanieObramowan(Obramowanie,Obramowanie0);
                                ktoreObramwanie=0;
                            }else if(ktoreObramwanie==2){
                                przepisywanieObramowan(Obramowanie,Obramowanie1);
                                ktoreObramwanie=1;
                            }
                            break;
                    }
                    break;
                case 7://prawo
                    switch(wybrane){
                        case 0:
                            if(kontaktyDoWypisaniaNaStrone<wysokoscKonsoli-4)
                            kontaktyDoWypisaniaNaStrone++;
                            break;
                        case 1:
                            if((NieWybrane+1)%16!=0){
                                NieWybrane++;
                            }else{
                                NieWybrane-=15;
                            }
                            break;
                        case 2:
                            if((Wybrane+1)%16!=0){
                                Wybrane++;
                            }else{
                                Wybrane-=15;
                            }
                            break;
                        case 3:
                            NieWybrane+=16;
                            break;
                        case 4:
                            Wybrane+=16;
                            break;
                        case 5://obramowanie
                            if(ktoreObramwanie==2){
                                przepisywanieObramowan(Obramowanie,Obramowanie0);
                                ktoreObramwanie=0;
                            }else if(ktoreObramwanie==0){
                                przepisywanieObramowan(Obramowanie,Obramowanie1);
                                ktoreObramwanie=1;
                            }else if(ktoreObramwanie==1){
                                przepisywanieObramowan(Obramowanie,Obramowanie2);
                                ktoreObramwanie=2;
                            }
                            break;
                    }
                    break;
                case 3://enter
                    //zapisz wybrane
                    if(wybrane==7){
                            ustawKolor(NieWybrane);
                            system("cls");
                            return 0;
                    }else if(wybrane==6){
                    wczystajDomyslneUstawienia();
                    }
                        break;
                    break;
                case 4://wyjscie
                    return 0;
                default:
                    continue;
                }
            ustawKolor(NieWybrane);
        }
    }

    int PobieranieStrzalek(){
    while(true){
        int bajt=PobieranieZnaku();
        if(bajt==(-32)){
        switch((int)PobieranieZnaku()){
            case 75:
                //lewo
                return 6;
            case 72:
                //gora
                return 1;
            case 77:
                //prawo
                return 7;
            case 80:
                //dol
                return 2;
            case 83:
                //del
                return 5;
                default:
                    continue;
            }
        }else if(bajt==13){//enter
            return 3;
        }else if(bajt==27){
            return 4;//wyjscie
        }else if(bajt==32){
            return 32;//spacja
        }
    }
    }

    int dodajKontakt(){
        kontakt *k=new kontakt();
        system("cls");
        cout<<"Nazwisko :";
        if(PobiernieZnakowZOgraniczeniam(k->nazwisko,20,0,1)==27) return 0;
        cout<<endl;
        cout<<"Imie :";
        if(PobiernieZnakowZOgraniczeniam(k->imie,20,0,1)==27) return 0;
        cout<<endl;
        cout<<"Miejsce zamieszkania :";
        if(PobiernieZnakowZOgraniczeniam(k->miejscowosc,50,0,1)==27) return 0;
        cout<<endl;
        cout<<"Numer :";
        if(PobiernieZnakowZOgraniczeniam(k->numer,12,1)==27) return 0;
        cout<<endl;
        t[n]=k;
        sortowanie();
    }

    int wypisz(){

        int wybrane=0;
        int WypisaneKontakty=1;
        int strona=1;
        int wypisaneNaStronie=0;
        int wypisaneNaStroniePodczasWyszukiwania=0;
        bool czPoliczone=0;
        int zmiennapomocnicza=0;
        int tablica[n];
        while(true){
            system("cls");
            obramowanieWypiszKontakty();
            cout<<endl;
            for(int i(0);i<n;i++){
            WypisaneKontakty=(strona-1)*kontaktyDoWypisaniaNaStrone+1;
            if(szukane[0]==NULL){
                if(wybrane==i){
                ustawKolor(Wybrane);
                }else{
                ustawKolor(NieWybrane);
                }
            }else{
                if(tablica[zmiennapomocnicza]==i){
                ustawKolor(Wybrane);
                }else{
                ustawKolor(NieWybrane);
                }
            }
                if(WypisaneKontakty+i<=n && i<kontaktyDoWypisaniaNaStrone && szukane[0]==NULL){
                    t[WypisaneKontakty-1+i]->wypisz();
                    wypisaneNaStronie++;
                }else{
                        if(WypisaneKontakty-1+i<n)
                            if(strstr(t[WypisaneKontakty-1+i]->nazwisko,szukane)!=NULL
                                || strstr(t[WypisaneKontakty-1+i]->imie,szukane)!=NULL
                                || strstr(t[WypisaneKontakty-1+i]->miejscowosc,szukane)!=NULL
                                || strstr(t[WypisaneKontakty-1+i]->numer,szukane)!=NULL){
                                    if(szukane[0]!=NULL){
                                        if(czPoliczone==0){
                                            tablica[zmiennapomocnicza]=i;
                                            zmiennapomocnicza++;
                                        }
                                    }
                                    if(wypisaneNaStronie<kontaktyDoWypisaniaNaStrone && wypisaneNaStronie<kontaktyDoWypisaniaNaStrone && szukane[0]!=NULL){
                                           if(WypisaneKontakty-1+wypisaneNaStronie<zmiennapomocnicza){
                                            t[tablica[WypisaneKontakty-1+wypisaneNaStronie]]->wypisz();
                                            wypisaneNaStronie++;
                                           }
                                        }
                    }
                }
            }
            wypisaneNaStronie--;
            if(szukane[0]!=NULL)
                czPoliczone=1;
            int wysokoscKonsoli = csbi.srWindow.Bottom;//ustala wiekosc tabelki w dol
            int szerkosciKonsoli = csbi.srWindow.Right;//ustala wiekosc tabelki w prawo
            ustawianieKursora(szerkosciKonsoli/2-2,wysokoscKonsoli);
            ustawKolor(NieWybrane);
            cout<<strona;
            switch(PobieranieStrzalek()){
                case 1://gora
                    if(wybrane==0){
                        wybrane=wypisaneNaStronie;
                        ustawKolor(NieWybrane);
                    }else{
                        wybrane--;
                        ustawKolor(NieWybrane);
                    }
                    break;
                case 2://dol

                    if(wybrane==wypisaneNaStronie){
                        wybrane=0;
                    }else if(wybrane<wypisaneNaStronie){
                        wybrane++;
                    }
                    break;
                case 4:
                    ustawKolor(NieWybrane);
                    system("cls");
                    return 0;
                case 5:
                    //del
                    przepisywanieWGore(WypisaneKontakty+wybrane);
                    //usuwanie
                    break;
                case 6://lewo
                    if(strona > 1){
                        strona--;
                    }
                    //strona w lewo
                    break;
                case 7://prawo
                    if(n-(strona*kontaktyDoWypisaniaNaStrone)>0 && szukane[0]==NULL){
                        strona++;
                    }else if(zmiennapomocnicza/kontaktyDoWypisaniaNaStrone>strona && n-(strona*kontaktyDoWypisaniaNaStrone)>0 && szukane[0]!=NULL
                              || zmiennapomocnicza/kontaktyDoWypisaniaNaStrone==strona && zmiennapomocnicza%kontaktyDoWypisaniaNaStrone>0 && n-(strona*kontaktyDoWypisaniaNaStrone)>0 && szukane[0]!=NULL){
                             strona++;
                    }
                    //strona w prawo
                    break;
                case 32:
                    strona=1;
                    wyszukiwanie();
                    break;
                    //spcja
                    //wyszukaj
                default:
                    continue;
                }
        wypisaneNaStronie=0;
        wypisaneNaStroniePodczasWyszukiwania=0;
        }
    }

    int zapisz(){
        system("cls");
        cout << "Podaj nazwe pliku: ";
        if(PobiernieZnakowZOgraniczeniam(nazwaPliku,50,2,0)==27) return 0;
        ofstream plik;
        plik.open(nazwaPliku, ios_base::binary);
            for(int i=0; i<n; i++)
            {
                plik.write((const char*) t[i], sizeof(kontakt));
            }
            plik.close();
            char nazwa_Pliku[50];
            strcpy(nazwa_Pliku,nazwaPliku);
            strcat(nazwa_Pliku,".txt");
            {
                ofstream plik;
                plik.open(nazwa_Pliku);
                    for(int i=0; i<n; i++)
                    {
                        plik <<t[i]->imie<<";";
                        plik <<t[i]->nazwisko<<";";
                        plik <<t[i]->miejscowosc<<";";
                        plik <<t[i]->numer<<";";
                        if(i<n-1)
                        plik << endl;
                    }
                    plik.close();
            }
            cout<<endl;
            cout<<"Zapis przebiegl pomyslnie"<<endl;
            cout<<"Przycisnij dowolny przycisk aby powrocic do menu"<<endl;
            getch();
        }

    int wczytajZPilikuBinernego(){
        system("cls");
        srodkowanie("Podaj nazwe pliku: ");
        if(PobiernieZnakowZOgraniczeniam(nazwaPliku,50,2,0)==27) return 0;
        ifstream plik;
        plik.open(nazwaPliku, ios_base::binary);
        if(plik.good()==false){
            cout<<"Podany plik nie istnieje."<<endl;
            wczytajZPilikuBinernego();
        }else{
            this->n=0;
            while(!plik.eof())
            {
                t[n] = new kontakt();
                plik.read((char*) t[n], sizeof(kontakt));
                n++;
            }
        }
        plik.close();
        cout<<endl;
        cout<<"Wczytywanie przebieglo pomyslnie"<<endl;
        cout<<"Przycisnij dowolny przycisk aby powrocic do menu"<<endl;
        getch();
    }

    int wczytajZPilikuTekstowego(){
        system("cls");
        cout << "Podaj nazwe pliku: ";
        if(PobiernieZnakowZOgraniczeniam(nazwaPliku,50,2,0)==27) return 0;
        strcat(nazwaPliku,".txt");
        ifstream plik0;
        plik0.open(nazwaPliku);
        if(plik0.good()==false){
            cout<<"Podany plik nie istnieje."<<endl;
            wczytajZPilikuTekstowego();
            plik0.close();
        }else{
            this->n=0;
            while(!plik0.eof()){
                t[n] = new kontakt();
                plik0.get(t[n]->nazwisko,20,';'); plik0.get();
                plik0.get(t[n]->imie,20,';'); plik0.get();
                plik0.get(t[n]->miejscowosc,50,';'); plik0.get();
                plik0.getline(t[n]->numer,12,';');plik0.get();
                n++;
            }
            plik0.close();
        }
        cout<<endl;
        cout<<"Wczytywanie przebieglo pomyslnie"<<endl;
        cout<<"Przycisnij dowolny przycisk aby powrocic do menu"<<endl;
        getch();
    }
};

ksiazka k;

int main()
{
k.wypiszMenu();




    return 0;
}




