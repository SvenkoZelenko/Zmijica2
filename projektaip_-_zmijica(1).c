#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define CLEAR_SCREEN() printf("\033[H\033[J")
#define SLEEP(ms) usleep((ms) * 1000)

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void)
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void displayMenu()
{
    CLEAR_SCREEN();
    printf(" _______ ___ ___ _______   _____ _______ ______ _______  \n");
    printf("|__     |   |   |_     _|_|     |_     _|      |   _   | \n");
    printf("|     __|       |_|   |_|       |_|   |_|   ---|       | \n");
    printf("|_______|__|_|__|_______|_______|_______|______|___|___| \n");
    printf("####################\n");
    printf("1: Ulazak u igricu\n");
    printf("2: Zasluge\n");
    printf("3: O igrici\n");
    printf("4: Izlazak\n");
    printf("####################\n");
}

void displayCredits()
{
    CLEAR_SCREEN();
    printf("------------------------\n");
    SLEEP(1500);
    printf("Isprogramirali:\n");
    SLEEP(1500);
    printf("Martin Gorisek\n");
    SLEEP(1500);
    printf("Sven Becki\n");
    SLEEP(1500);
    printf("Pomogao:\n");
    SLEEP(1500);
    printf("IT PhD na YouTube '13) C language. Roguelike game with conio.h'\n");
    SLEEP(10000);
}

void displayAbout()
{
    CLEAR_SCREEN();
    SLEEP(1500);
    printf(" _______ ___ ___ _______   _____ _______ ______ _______  \n");
    printf("|__     |   |   |_     _|_|     |_     _|      |   _   | \n");
    printf("|     __|       |_|   |_|       |_|   |_|   ---|       | \n");
    printf("|_______|__|_|__|_______|_______|_______|______|___|___| \n");
    printf("\n");
    SLEEP(1500);
    printf("Originalnu igricu dizajnirao Gremlin industries.\n");
    SLEEP(1500);
    printf("Bila je dostupna na arkadnim masinama vec 1976.\n");
    SLEEP(1500);
    printf("Originalno ime je bilo 'Blockade'.\n");
    SLEEP(1500);
    printf("Nalazi se na skoro svim modelima Nokie od 1997.\n");
    SLEEP(1000);
    printf("-------------------------------------------------------\n");
    SLEEP(1500);
    printf("Nasa verzija je jednostavnija.\n");
    SLEEP(1500);
    printf("Nema aspekt 'repa' zbog kompliciranosti.\n");
    SLEEP(1500);
    printf("Ali se zato u nasoj verziji 'jabuka' pomice svake 3 sekunde kako bi se napravio izazov.\n");
    SLEEP(1500);
    printf("Takoder je igrac nagraden bodovima, 5 za svaku jabuku pojedenu, a ako igrac ne pojede jabuku na vrjeme gubi 1 bod.\n");
    SLEEP(10000);
}

void gameLoop()
{
    char polje[15][15];
    char action1 = ' ';
    int x = 4, y = 4;
    int xx, yy;
    int jabuka = 0;
    int score = 1;
    time_t diraoJabuku;

    srand((unsigned int)time(NULL));
    xx = rand() % 13 + 1;
    yy = rand() % 13 + 1;

    do
    {
        CLEAR_SCREEN();

        if (kbhit())
        {
            action1 = getch();
        }

        if (action1 == 'w' && x > 1)
        {
            x--;
        }
        else if (action1 == 's' && x < 13)
        {
            x++;
        }
        else if (action1 == 'a' && y > 1)
        {
            y--;
        }
        else if (action1 == 'd' && y < 13)
        {
            y++;
        }
        else if (action1 == 'x')
        {
            break;
        }

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (i == 0 || i == 14 || j == 0 || j == 14)
                {
                    polje[i][j] = '#';
                }
                else
                {
                    polje[i][j] = ' ';
                }
            }
        }

        polje[x][y] = '@';

        if (x == xx && y == yy)
        {
            jabuka = 0;
            score += 6;
            diraoJabuku = time(NULL);
        }

        time_t trenutno = time(NULL);
        if (!jabuka || difftime(trenutno, diraoJabuku) >= 3)
        {
            score -= 1;
            do
            {
                xx = rand() % 13 + 1;
                yy = rand() % 13 + 1;
            } while (polje[xx][yy] != ' ');
            jabuka = 1;
            diraoJabuku = trenutno;
        }

        polje[xx][yy] = '0';

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                printf("%c ", polje[i][j]);
            }
            printf("\n");
        }

        printf("Rezultat: %d\n", score);
        printf("Da izadete iz programa, pritisnite 'x'\n");

        if (x == 0 || x == 14 || y == 0 || y == 14)
        {
            printf("Izgubili ste!\n");
            break;
        }

        SLEEP(400);
    } while (1);
}

int main()
{
    int action2;

    while (1)
    {
        displayMenu();
        action2 = getch();

        if (action2 == '1')
        {
            gameLoop();
            return 0;
        }
        else if (action2 == '2')
        {
            displayCredits();
        }
        else if (action2 == '3')
        {
            displayAbout();
        }
        else if (action2 == '4')
        {
            break;
        }
    }

    return 0;
}
