#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <unistd.h>
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
    int jabuka = 0;
    int score = 1;
    time_t diraoJabuku;

    // brise se prijasnja informacija u datoteci
    ofstream outDatoteka("C:\\Users\\Svenko\\Documents\\GitHub\\projektni_SvenBecki\\leaderboard.bin", ios::binary | ios::trunc);
    outDatoteka.close();

    // za leaderboard
    struct Igrac igraci[10];
    int brIgraca = -1;
    while (1)
    {
    izbornik:
        system("cls");
        cout << " _______ ___ ___ _______   _____ _______ ______ _______  " << endl;
        cout << "|__     |   |   |_     _|_|     |_     _|      |   _   | " << endl;
        cout << "|     __|       |_|   |_|       |_|   |_|   ---|       | " << endl;
        cout << "|_______|__|_|__|_______|_______|_______|______|___|___| " << endl;
        cout << "####################" << endl;
        cout << "1: Ulazak u igricu" << endl;
        cout << "2: Ljestvica" << endl;
        cout << "3: Ducan" << endl;
        cout << "4: Izlazak" << endl;
        cout << "####################" << endl;

        action2 = getch();

        if (action2 == '1')
        {

            x = 4;
            y = 4;
            jabuka = 0;
            score = 1;
            action1 = 0;

            srand(time(NULL));
            xx = rand() % 13 + 1;
            yy = rand() % 13 + 1;

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
                if (x == xx && y == yy)
                {
                    jabuka = 0;
                    score += 6;
                    diraoJabuku = time(NULL);
                }

                // postavlja jabuku
                time_t trenutno = time(NULL);
                if (!jabuka || difftime(trenutno, diraoJabuku) >= 3)
                {
                    score -= 1;
                    do
                    {
                        xx = rand() % 15 + 1;
                        yy = rand() % 15 + 1;
                    } while (polje[xx][yy] != ' ');
                    jabuka = 1;
                    diraoJabuku = trenutno;
                }

                // jabuka
                polje[xx][yy] = '0';

                // ispisivanje okvira
                for (int i = 0; i < 15; i++)
                {
                    for (int j = 0; j < 15; j++)
                        printf("%c ", polje[i][j]);
                    printf("\n");
                }

                // gleda da li se zmijica zabila u zid
                if (x >= 14 || x <= 0 || y >= 14 || y <= 0)
                {
                    cout << "Izgubili ste!" << endl;
                    usleep(1500000);
                    cout << "Rezultat: " << score << endl;

                    igraci[brIgraca].score = score; // sejvanje scorea u strukturu

                    // zapisivanje u datoteku
                    ofstream inDatoteka("C:\\Users\\Svenko\\Documents\\GitHub\\projektni_SvenBecki\\leaderboard.bin", ios::binary | ios::app);
                    inDatoteka.write((char *)&igraci[brIgraca], sizeof(Igrac));
                    inDatoteka.close();
                    brIgraca++;

                    usleep(1500000);
                    goto izbornik;
                }
                usleep(40000);
            } while (1);
        }
        if (action2 == '2')
        {
            ifstream inDatoteka("C:\\Users\\Svenko\\Documents\\GitHub\\projektni_SvenBecki\\leaderboard.bin", ios::binary);
            int citac = 0;
            while (inDatoteka.read((char *)&igraci[citac], sizeof(Igrac)))
            {
                citac++; // tako da zna koliko je procitano igraca, svaki put kad procita igraca poveca
            }
            inDatoteka.close();

            sort(igraci, igraci + citac, cmp);

            system("cls");
            cout << "Ljestvica:" << endl;
            for (int i = 0; i < citac; i++)
            {
                cout << igraci[i].ime << " " << igraci[i].score << endl;
            }
            cout << "Pritisnite bilo koju tipku za povratak na izbornik" << endl;
            getch();
        }
        if (action2 == '4')
        {
            break;
        }
    }
    return 0;
}