#include <iostream>
#include<windows.h>
#include <time.h>
#include<conio.h>
#include<locale.h>
#define TAM 15

using namespace std;

void tempo(int tempo){
        clock_t inicio, fim;
        inicio = clock();
        bool temp = true;
        while(temp == true){
            fim = clock();
            if ((fim-inicio)/CLOCKS_PER_SEC == tempo) {
                temp = false;
                break;
            }
        }
}

void desenhar_bomba(int i, int j, int m[TAM][TAM]){
    m[i][j] = 4;
    if(m[i+1][j] != 1){
        m[i+1][j] = 4;
    }
    if(m[i-1][j] != 1){
        m[i-1][j] = 4;
    }
    if(m[i][j+1] != 1){
        m[i][j+1] = 4;
    }
    if(m[i][j-1] != 1){
        m[i][j-1] = 4;
    }
}

void mapa(int x, int y, int m[TAM][TAM], int &bomba, int s, int d, int &inimigo, int &jogador){
        if(m[s][d] == 4){
            inimigo = 0;
        }
        if(m[x][y] == 4){
        jogador = 0;
        }
        for(int i=0;i<TAM;i++){
            for(int j=0;j<TAM;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else if((i == s && j == d) && inimigo != 0) {
                    cout << char(190);
                } else {
                            switch (m[i][j]){
                                case 0: cout<< char(176); break; //caminho
                                case 1: cout<<char(219); break; //parede
                                case 2: cout <<char(178);  break; // parede que pode ser quebrada
                                case 3: if(bomba != 0) { break; } else { cout << char(208); bomba = bomba + 1; desenhar_bomba(i,j, m); } break; //bomba
                                case 4: cout << char(158); tempo(5); m[i][j] = 0;bomba = 0; break; // explosão bomba
                            }
                        }
            }
            cout<<"\n";
        }
}

int quantidade(int number, int m[TAM][TAM]){
    int contador = 0;
   for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            if (m[i][j] == number) {
                contador++;
            }
        }
    }
    return contador;
}

int verificar_posicao(int &x, int &y, int m[TAM][TAM], char tecla){
            switch(tecla){
                case 72: case 'w': ///cima
                    x--;
                if(m[x][y] == 1 || m[x][y] == 2){
                    x++;
                }
                break;
                case 80: case 's': ///baixo
                    x++;
                if(m[x][y] == 1 || m[x][y] == 2){
                    x--;
                }
                break;
                case 75:case 'a': ///esquerda
                    y--;
                    if(m[x][y] == 1 || m[x][y] == 2){
                        y++;
                    }
                break;
                case 77: case 'd': ///direita
                    y++;
                    if(m[x][y] == 1 || m[x][y] == 2){
                        y--;
                    }
                break;
                case 'e':
                    m[x][y] = 3;
                break;
            }
}

void mover(int &x,int &y, int m[TAM][TAM], int inimigo) {
        if(inimigo != 0){
            int direcao = rand() % 4; // 0: cima, 1: baixo, 2: esquerda, 3: direita
        switch (direcao) {
            case 0:
                if(m[x-1][y] == 1 || m[x-1][y] == 2){
                    break;
                }
                x--;
                break;
            case 1:
                if(m[x+1][y] == 1 || m[x+1][y] == 2){
                    break;
                }
                x++;
                break;
            case 2:
                if(m[x][y-1] == 1 || m[x][y-1] == 2){
                    break;
                }
                y--;
                break;
            case 3:
                if(m[x][y+1] == 1 || m[x][y+1] == 2){
                    break;
                }
                y++;
                break;
        }
        }
    }

int main(){
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);

        cursorInfo.bVisible = false;

        SetConsoleCursorInfo(out, &cursorInfo);

        int CX=0, CY=0;

        COORD coord;

        coord.X = CX;

        coord.Y = CY;

        int m[TAM][TAM] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 2, 0, 1, 0, 0, 2, 2, 0, 1, 0, 1, 0, 1},
            {1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
            {1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
            {1, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
            {1, 2, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 2, 0, 1},
            {1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

        int x=5, y=5, bomba = 0, s = 8, d = 5, inimigo = 1, paredes = 0, jogador = 1;
        char tecla;
        bool jogo = true;
        while(jogo == true){
            paredes = quantidade(2, m);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            mapa(x,y, m, bomba, s,d, inimigo, jogador);
            if (_kbhit()){
                tecla = getch();
                verificar_posicao(x,y, m, tecla);
                mover(s, d, m, inimigo);
            } else if((x == s && y == d) || jogador == 0){
                setlocale(LC_ALL, "Portuguese");
                system("cls");
                jogo = false;
                cout << "Você Perdeu! O inimigo te capturou ou a bomba explodiu no jogador";
            } else if(paredes == 0 || inimigo == 0){
                setlocale(LC_ALL, "Portuguese");
                system("cls");
                jogo = false;
                cout << "Você Ganhou!";
            }
        }
    return 0;
}
