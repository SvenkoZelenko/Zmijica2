#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int izbor, action2;
    int i, j;
    char polje[15][15];
    char action1;
    char x = 4, y = 4;
    char xx, yy;
    int jabuka = 0;
    int score = 1;
    time_t diraoJabuku;

    //izbornik
    while (1){
        izbornik:
            system("cls");
            printf(" _______ ___ ___ _______   _____ _______ ______ _______  \n");
            printf("|__     |   |   |_     _|_|     |_     _|      |   _   | \n");
            printf("|     __|       |_|   |_|       |_|   |_|   ---|       | \n");
            printf("|_______|__|_|__|_______|_______|_______|______|___|___| \n");
            printf("####################\n");
            printf("1: Ulazak u igricu\n");
            printf("2: Zasluge\n");
            printf("3: O igrici\n");
            printf("4: Izlazak\n");
            printf("####################");

            action2=getch();

        if (action2=='1'){
            srand(time(NULL));
            //koordinate za jabuku
            xx = rand()%15+1;
            yy = rand()%15+1;

            do {
                system("cls");

                // kretanje
                if (kbhit()){
                    action1=getch();
                }
                else if (action1 == 'w' && x>0){
                    x--;
                }
                else if (action1 == 's' && x<14){
                    x++;
                }
                else if (action1 == 'a' && y>0){
                    y--;
                }
                else if(action1 == 'd' && y<14){
                    y++;
                }
                else if (action1 == 'x')
                    break;

                //inicijalizira okvir
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 15; j++) {
                        if (i==0 || i==14 || j==0 || j==14 )
                            polje[i][j] = '#';
                        else
                            polje[i][j] = ' ';

                    }
                }

                // zmijica
                polje[x][y]='@';

                //gleda da li je zmijica pojela jabuku
                if (x==xx && y==yy){
                    jabuka=0;
                    score+=6;
                    diraoJabuku = time(NULL);
                }

                //postavlja jabuku
                time_t trenutno = time(NULL);
                if (!jabuka || difftime(trenutno, diraoJabuku) >= 3){
                    score-=1;
                    do{
                        xx=rand()%15+1;
                        yy=rand()%15+1;
                    } while (polje[xx][yy]!=' ');
                    jabuka=1;
                    diraoJabuku = trenutno;
                }

                //jabuka
                polje[xx][yy]='0';

                //ispisivanje okvira
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 15; j++)
                            printf("%c ", polje[i][j]);
                    printf("\n");
                }

                //tekst ispod programa
                printf("Rezultat: %d\n", score);
                printf("Da izadete iz programa, pritisnite 'x'\n");

                // gleda da li se zmijica zabila u zid
                if (x >= 14 || x <= 0 || y >= 14 || y <= 0) {
                    printf("Izgubili ste!\n");
                    break;
                }
            usleep(40000);
        } while (1);
        return 0;
    }
    if (action2=='2'){
        system("cls");
        usleep(1500000);
        printf("------------------------\n");
        usleep(1500000);
        printf("Isprogramirali:\n");
        usleep(1500000);
        printf("Martin Gorisek\n");
        usleep(1500000);
        printf("Sven Becki\n");
        usleep(1500000);
        printf("Pomogao:\n");
        usleep(1500000);
        printf("IT PhD na YouTube '13) C language. Roguelike game with conio.h'\n");
        sleep(10);
        goto izbornik;
    }
    if (action2=='3'){
        system("cls");
        usleep(1500000);
        printf(" _______ ___ ___ _______   _____ _______ ______ _______  \n");
        printf("|__     |   |   |_     _|_|     |_     _|      |   _   | \n");
        printf("|     __|       |_|   |_|       |_|   |_|   ---|       | \n");
        printf("|_______|__|_|__|_______|_______|_______|______|___|___| \n");
        printf("\n");
        usleep(1500000);
        printf("Originalnu igricu dizajnirao Gremlin industries.\n");
        usleep(1500000);
        printf("Bila je dostupna na arkadnim masinama vec 1976.\n");
        usleep(1500000);
        printf("Originalno ime je bilo 'Blockade'.\n");
        usleep(1500000);
        printf("Nalazi se na skoro svim modelima Nokie od 1997.\n");
        usleep(1000000);
        printf("-------------------------------------------------------\n");
        usleep(1500000);
        printf("Nasa verzija je jednostavnija.\n");
        usleep(1500000);
        printf("Nema aspekt 'repa' zbog kompliciranosti.\n");
        usleep(1500000);
        printf("Ali se zato u nasoj verziji 'jabuka' pomice svake 3 sekunde kako bi se napravio izazov.\n");
        usleep(1500000);
        printf("Takoder je igrac nagraden bodovima, 5 za svaku jabuku pojedenu, a ako igrac ne pojede jabuku na vrjeme gubi 1 bod.\n");
        sleep(10);
        goto izbornik;
    }
    else
        break;
    }
    return 0;
}
