
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <unistd.h>

using namespace std;

struct Ucenik
{
    char imePrezime[50];
    float prosjek;
};
bool cmpp(Ucenik &a, Ucenik &b)
{
    return a.prosjek > b.prosjek;
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

    // izbornik
    while (1)
    {
    izbornik:
        system("cls");
        cout << " _______ ___ ___ _______   _____ _______ ______ _______ " << endl;
        cout << "|__     |   |   |_     _|_|     |_     _|      |   _   |" << endl;
        cout << "|     __|       |_|   |_|       |_|   |_|   ---|       |" << endl;
        cout << "|_______|__|_|__|_______|_______|_______|______|___|___|" << endl;
        cout << "####################" << endl;
        cout << "1: Ulazak u igricu" << endl;
        cout << "2: Zasluge " << endl;
        cout << "3: O igrici " << endl;
        cout << "4: Izlazak" << endl;
        cout << "####################" << endl;

        action2 = getch();

        if (action2 == '1')
        {
            srand(time(NULL));
            // koordinate za jabuku
            xx = rand() % 15 + 1;
            yy = rand() % 15 + 1;

            do
            {
                system("cls");

                // kretanje
                if (kbhit())
                {
                    action1 = getch();
                }
                else if (action1 == 'w' && x > 0)
                {
                    x--;
                }
                else if (action1 == 's' && x < 14)
                {
                    x++;
                }
                else if (action1 == 'a' && y > 0)
                {
                    y--;
                }
                else if (action1 == 'd' && y < 14)
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
                        cout << polje[i][j] << endl;
                    cout << endl;
                }

                // tekst ispod programa
                cout << "Rezultat:" << score << endl;
                cout << "Da izadete iz programa, pritisnite 'x'\n"
                     << endl;

                // gleda da li se zmijica zabila u zid
                if (x >= 14 || x <= 0 || y >= 14 || y <= 0)
                {
                    cout << "Izgubili ste :(\n"
                         << endl;
                    break;
                }
                usleep(40000);
            } while (1);
            return 0;
        }
        if (action2 == '2')
        {
            system("cls");
            usleep(1500000);
            cout << "------------------------" << endl;
            usleep(1500000);
            cout << "Isprogramirali:" << endl;
            usleep(1500000);
            cout << "Paula Luheni" << endl;
            usleep(1500000);
            cout << "Sven Becki" << endl;
            usleep(1500000);
            cout << "Pomogao" << endl;
            usleep(1500000);
            cout << "IT PhD na YouTube '13) C language. Roguelike game with conio.h'" << endl;
            sleep(10);
            goto izbornik;
        }
        if (action2 == '3')
        {
            system("cls");
            usleep(1500000);
            cout << " _______ ___ ___ _______   _____ _______ ______ _______ " << endl;
            cout << "|__     |   |   |_     _|_|     |_     _|      |   _   |" << endl;
            cout << "|     __|       |_|   |_|       |_|   |_|   ---|       |" << endl;
            cout << "|_______|__|_|__|_______|_______|_______|______|___|___|" << endl;
            usleep(1500000);
            cout << "Originalnu igricu dizajnirao Gremlin industries." << endl;
            usleep(1500000);
            cout << "Bila je dostupna na arkadnim masinama vec 1976." << endl;
            usleep(1500000);
            cout << "Originalno ime je bilo 'Blockade'." << endl;
            usleep(1500000);
            cout << "Nalazi se na skoro svim modelima Nokie od 1997." << endl;
            usleep(1000000);
            cout << "-------------------------------------------------------" << endl;
            usleep(1500000);
            cout << "Nasa verzija je jednostavnija." << endl;
            usleep(1500000);
            cout << "Nema aspekt 'repa' zbog kompliciranosti." << endl;
            usleep(1500000);
            cout << "Ali se zato u nasoj verziji 'jabuka' pomice svake 3 sekunde kako bi se napravio izazov." << endl;
            usleep(1500000);
            cout << "Takoder je igrac nagraden bodovima, 5 za svaku jabuku pojedenu, a ako igrac ne pojede jabuku na vrjeme gubi 1 bod." << endl;
            sleep(10);
            goto izbornik;
        }
        else
            break;
    }
    return 0;
}