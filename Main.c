#include <stdio.h>

#define FIM    -5
#define LIVRE  -1
#define PAREDE -2

#define START 0
#define RIGHT 1
#define DOWN  2
#define TOP   3
#define LEFT  4

#define GOING    0
#define RETURING 1

typedef unsigned char UCHAR;

typedef struct _XY
{
    int X;
    int Y;

} XY;

int labirinto[][12] = {
{-1, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2},
{-2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2},
{-1, -1, -1, -1, -1, -1, -2, -2, -1, -1, -1, -2},
{-1, -2, -1, -2, -2, -1, -2, -2, -2, -2, -1, -2},
{-1, -2, -1, -2, -2, -1, -1, -2, -1, -1, -1, -2},
{-1, -2, -1, -1, -1, -2, -1, -1, -2, -2, -2, -2},
{-1, -1, -2, -2, -2, -2, -2, -1, -1, -2, -2, -2},
{-1, -2, -1, -2, -2, -2, -2, -2, -1, -2, -2, -1},
{-1, -2, -1, -1, -2, -2, -2, -2, -1, -2, -2, -1},
{-1, -2, -2, -1, -1, -2, -2, -2, -1, -1, -1, -1},
{-1, -1, -2, -2, -1, -1, -1, -1, -1, -2, -2, -1},
{-2, -1, -1, -2, -1, -1, -2, -1, -1, -1, -2, -1},
{-2, -2, -1, -2, -1, -1, -2, -1, -2, -1, -1, -1},
{-2, -2, -1, -2, -2, -1, -2, -2, -2, -2, -2, -1},
{-1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{-1, -2, -1, -2, -2, -2, -1, -1, -1, -1, -2, -2},
{-5, -1, -1, -2, -2, -2, -1, -2, -1, -1, -1, -2},
{-1, -2, -1, -2, -2, -2, -1, -1, -1, -2, -1, -2},
{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1},
{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}
};

void imprimir(int lab[20][12]) {
    int i, j;

    for (i = 0; i < 20; i++) {
        printf("|");
        for (j = 0; j < 12; j++) {
            int n = lab[i][j];
            switch (n) {
                case -1:
                    printf("[   ]\t");
                    break;
                case -2:
                    printf("[ X ]\t");
                    break;
                case -5:
                    printf("[ F ]\t");
                    break;
                default:
                    printf("[%00d]\t", n);
                    break;
            }
        }
        printf("|\n");
    }
}

UCHAR ValidateBoundaries(XY pos)
{
    if ((pos.X < 20 && pos.X >= 0) && (pos.Y < 12 && pos.Y >= 0))
        return 1;

    return 0;
}

UCHAR ValidatePath(XY pos)
{
    if (labirinto[pos.X][pos.Y] < 0 || labirinto[pos.X][pos.Y] == -5)
        return 1;

    return 0;
}

void Resolve(XY pos, int step, UCHAR lastMoviment)
{
    UCHAR ucActualPositionOK = ValidateBoundaries(pos) && ValidatePath(pos);

    if (ucActualPositionOK)
        labirinto[pos.X][pos.Y] = step;

    if (ucActualPositionOK && labirinto[pos.X][pos.Y] == -5)
        return;

    {
        XY nextPos = pos;
        nextPos.Y++;

        UCHAR ucNextPositionOK = ValidateBoundaries(nextPos) && ValidatePath(nextPos);

        if (ucActualPositionOK && ucNextPositionOK && (labirinto[nextPos.X][nextPos.Y] == -1 || labirinto[nextPos.X][nextPos.Y] == -5))
        {
            pos.Y++;
            return Resolve(pos, ++step, RIGHT);
        }
    }


    {
        XY nextPos = pos;
        nextPos.X++;

        UCHAR ucNextPositionOK = ValidateBoundaries(nextPos) && ValidatePath(nextPos);

        if (ucActualPositionOK && ucNextPositionOK && (labirinto[nextPos.X][nextPos.Y] == -1 || labirinto[nextPos.X][nextPos.Y] == -5))
        {
            pos.X++;
            return Resolve(pos, ++step, DOWN);
        }
    }

    {
        XY nextPos = pos;
        nextPos.X--;

        UCHAR ucNextPositionOK = ValidateBoundaries(nextPos) && ValidatePath(nextPos);

        if (ucActualPositionOK && ucNextPositionOK && (labirinto[nextPos.X][nextPos.Y] == -1 || labirinto[nextPos.X][nextPos.Y] == -5))
        {
            pos.X--;
            return Resolve(pos, ++step, TOP);
        }
    }

    {
        XY nextPos = pos;
        nextPos.Y--;

        UCHAR ucNextPositionOK = ValidateBoundaries(nextPos) && ValidatePath(nextPos);

        if (ucActualPositionOK && ucNextPositionOK && (labirinto[nextPos.X][nextPos.Y] == -1 || labirinto[nextPos.X][nextPos.Y] == -5))
        {
            pos.Y--;
            return Resolve(pos, ++step, LEFT);
        }
    }

    switch (lastMoviment)
    {
        case RIGHT:
        {
            pos.Y--;
            lastMoviment = LEFT;
        }
        break;

        case DOWN:
        {
            pos.X--;
            lastMoviment = TOP;
        }
        break;

        case TOP:
        {
            pos.X++;
            lastMoviment = DOWN;
        }
        break;

        case LEFT:
        {
            pos.Y++;
            lastMoviment = RIGHT;
        }
        break;
    }

    if (lastMoviment && step)
    {
        return Resolve(pos, --step, lastMoviment);
    }
}

int main()
{
    printf("Labirinto:\n");
    imprimir(labirinto);

    XY InitialPosition = {0};
    int InitialStep = 0;

    Resolve(InitialPosition, InitialStep, START);

    printf("Resultado:\n");
    imprimir(labirinto);
}
