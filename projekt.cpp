#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Igrac
{
    char ime[5];
    int score;
};
bool cmp(Igrac &a, Igrac &b)
{
    return a.score > b.score;
}
int main()
{
    int izbor, action2;
    int i, j;
    char polje[15][15];
    char action1;
    char x = 4, y = 4;
    char xx, yy;
    char xxBomba, yyBomba;
    char xxJabuka, yyJabuka;
    int jabuka = 0;
    int score = 1;
    time_t diraoJabuku;
    bool BoljeJabuke = false;
    bool EkstraZivot = false;
    bool ManjeBombi = false;
    bool ViseJabuka = false;

    // brise se prijasnja informacija u datoteci
    ofstream outDatoteka("leaderboard.bin", ios::binary | ios::trunc);
    outDatoteka.close();

    // za leaderboard
    struct Igrac igraci[10];
    int brIgraca = 0;

    while (1)
    {
    izbornik:
        system("cls");
        cout << " _______  _______  _______    _____  _______  ______  _______      ______      ______ " << endl;
        cout << "|__     ||   |   ||_     _| _|     ||_     _||      ||   _   |    |__    |    |      |" << endl;
        cout << "|     __||       | _|   |_ |       | _|   |_ |   ---||       |    |    __| __ |  --  |" << endl;
        cout << "|_______||__|_|__||_______||_______||_______||______||___|___|    |______||__||______|" << endl;
        cout << "####################" << endl;
        cout << "1: Ulazak u igricu" << endl;
        cout << "2: Ljestvica" << endl;
        cout << "3: Ducan" << endl;
        cout << "4: Izlazak" << endl;
        cout << "####################" << endl;

        action2 = getch();

        if (action2 == '1')
        {
        pocetak:
            x = 4;
            y = 4;
            jabuka = 0;
            score = 1;
            action1 = 0;

            srand(time(NULL));
            xx = rand() % 13 + 1;
            yy = rand() % 13 + 1;

            if (!ManjeBombi)
            {
                xxBomba = rand() % 13 + 1;
                yyBomba = rand() % 13 + 1;
            }

            if (ViseJabuka)
            {
                xxJabuka = rand() % 13 + 1;
                yyJabuka = rand() % 13 + 1;
            }

            // unos imena
            cout << "Unesite 4-slovno ime: ";
            cin.getline(igraci[brIgraca].ime, 5);
            do
            {
                system("cls");

                // kretanje
                if (kbhit())
                {
                    action1 = getch();
                }
                else if (action1 == 'w' || action1 == 'W' && x > 0)
                {
                    x--;
                }
                else if (action1 == 's' || action1 == 'S' && x < 14)
                {
                    x++;
                }
                else if (action1 == 'a' || action1 == 'A' && y > 0)
                {
                    y--;
                }
                else if (action1 == 'd' || action1 == 'D' && y < 14)
                {
                    y++;
                }
                else if (action1 == 'x')
                    break;

                // inicijalizira okvir
                for (int i = 0; i < 15; i++)
                {
                    for (int j = 0; j < 15; j++)
                    {
                        if (i == 0 || i == 14 || j == 0 || j == 14)
                            polje[i][j] = '#';
                        else
                            polje[i][j] = ' ';
                    }
                }

                // zmijica
                polje[x][y] = '@';

                // gleda da li je zmijica pojela jabuku
                if (x == xx && y == yy || (x == xxJabuka && y == yyJabuka))
                {
                    jabuka = 0;
                    score += BoljeJabuke ? 11 : 6;
                    diraoJabuku = time(NULL);
                }

                // postavlja jabuku
                time_t trenutno = time(NULL);
                if (!jabuka || difftime(trenutno, diraoJabuku) >= 3)
                {
                    score -= 1;
                    do
                    {
                        xx = rand() % 13 + 1;
                        yy = rand() % 13 + 1; // za pomicanje jabuke
                        do
                        {
                            xxBomba = rand() % 13 + 1;
                            yyBomba = rand() % 13 + 1;
                        } while (xx == xxBomba && yy == yyBomba); // da bomba i jabuka ne budu na istom mjestu
                        do
                        {
                            xxJabuka = rand() % 13 + 1;
                            yyJabuka = rand() % 13 + 1;
                        } while (xx == xxJabuka && yy == yyJabuka && xxJabuka == xxBomba && yyJabuka == yyBomba);
                    } while (polje[xx][yy] != ' ');
                    jabuka = 1;
                    diraoJabuku = trenutno;
                }

                // jabuka
                polje[xx][yy] = '0';

                // ViseJabuka
                if (ViseJabuka)
                    polje[xxJabuka][yyJabuka] = '0';

                // bomba
                if (!ManjeBombi)
                    polje[xxBomba][yyBomba] = 'X';

                // ispisivanje okvira
                for (int i = 0; i < 15; i++)
                {
                    for (int j = 0; j < 15; j++)
                        cout << polje[i][j] << " ";
                    cout << "\n";
                }

                // gleda da li se zmijica zabila u zid
                if (x >= 14 || x <= 0 || y >= 14 || y <= 0 || (x == xxBomba && y == yyBomba))
                {
                    if (EkstraZivot == true)
                    {
                        EkstraZivot = false;
                        goto pocetak;
                    }
                    cout << "Izgubili ste!" << endl;
                    usleep(1500000);
                    cout << "Rezultat: " << score << endl;

                    bool postoji = false;
                    for (int i = 0; i < brIgraca; i++)
                    {
                        if (strcmp(igraci[i].ime, igraci[brIgraca].ime) == 0) // igraci[i].ime --> trenutni igrac iz polja, igraci[brIgraca].ime --> ko je igrao sad
                        {
                            if (score > igraci[i].score)
                            {
                                igraci[i].score = score;
                            }
                            postoji = true;
                            break;
                        }
                    }

                    if (!postoji)
                    {
                        igraci[brIgraca].score = score;
                        brIgraca++;
                    }

                    // zapisivanje u datoteku
                    ofstream inDatoteka("leaderboard.bin", ios::binary | ios::trunc);
                    inDatoteka.write((char *)igraci, sizeof(Igrac) * brIgraca);
                    inDatoteka.close();

                    usleep(1500000);
                    goto izbornik;
                }
                usleep(70000);
            } while (1);
        }
        if (action2 == '2')
        {
            ifstream inDatoteka("leaderboard.bin", ios::binary);
            int citac = 0;
            while (inDatoteka.read((char *)&igraci[citac], sizeof(Igrac)))
            {
                citac++; // tako da zna koliko je procitano igraca, svaki put kad procita igraca poveca
            }
            inDatoteka.close();

            sort(igraci, igraci + citac, cmp);

            system("cls");
            cout << "####################" << endl;
            cout << "     LJESTVICA      " << endl;
            cout << "####################" << endl;
            for (int i = 0; i < citac; i++)
            {
                cout << igraci[i].ime << " " << igraci[i].score << endl;
            }
            cout << "Pritisnite bilo koju tipku za povratak na izbornik" << endl;
            getch();
        }
        if (action2 == '3') // ducan 1. -2 speed za zmijucu, 2.dodatni extra 1 život, 3. malo vise jabuka onak 2x, 4. myb onak da nestaju bumbice  5. bonus pointovi kad se pojede jabuka (2x)
        {
            ifstream ducan("shop.txt");
            string citac;
            system("cls");
            cout << "####################" << endl;
            cout << "       DUCAN        " << endl;
            cout << "####################" << endl;
            while (getline(ducan, citac))
            {
                cout << citac << endl;
            }
            cout << "\nVas trenutacni iznos: " << score << endl;
            cout << "Unesite sto zelite kupiti ili unesite 0 da se vratite u izbornik: " << endl;
            char izbor = getch();
            if (izbor == '1')
            {
                if (score >= 10)
                {
                    score -= 10;
                    BoljeJabuke = true;
                    cout << "Kupili ste BoljeJabuke" << endl;
                    cout << "Ostatak: " << score << endl;
                }
                else
                {
                    cout << "\nNemate dovoljno bodova za BoljeJabuke" << endl;
                }
            }
            else if (izbor == '2')
            {
                if (score >= 15)
                {
                    score -= 15;
                    EkstraZivot = true;
                    cout << "Kupili ste EkstraZivot" << endl;
                    cout << "Ostatak: " << score << endl;
                }
                else
                {
                    cout << "\nNemate dovoljno bodova za EkstraZivot" << endl;
                }
            }
            else if (izbor == '3')
            {
                if (score >= 20)
                {
                    score -= 20;
                    ManjeBombi = true;
                    cout << "Kupili ste ManjeBombi" << endl;
                    cout << "Ostatak: " << score << endl;
                }
                else
                {
                    cout << "\nNemate dovoljno bodova za ManjeBombi" << endl;
                }
            }
            else if (izbor == '4')
            {
                if (score >= 25)
                {
                    score -= 25;
                    ViseJabuka = true;
                    cout << "Kupili ste ViseJabuka" << endl;
                    cout << "Ostatak: " << score << endl;
                }
                else
                {
                    cout << "\nNemate dovoljno bodova za ViseJabuka" << endl;
                }
            }
            else if (izbor == '0')
            {
                goto izbornik;
            }
            else
            {
                cout << "\nKrivi unos, pokusajte ponovo" << endl;
            }
            getch();
        }
        if (action2 == '4')
        {
            break;
        }
    }
    return 0;
}