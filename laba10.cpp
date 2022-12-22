#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <queue>
using namespace std;

queue<int>q;
void BFSD(int s, int n, int* dis, int** G, int* ex) {
    int l = s;
    q.push(s);
    dis[l] = 0;
    while (!q.empty()) {
        l = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (G[l][i] != 0 && dis[i] == -1)
            {
                q.push(i);
                dis[i] = dis[l] + G[l][i];
                printf("%d[%d->%d] ", dis[i], l, i);
                if (dis[i] > ex[l])
                    ex[l] = dis[i];
            }
        }
    }
}

int main() {
    int n, i = 0;
    int R = 100, D = 0;
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    printf("Введите количество вершин для матрицы: ");
    scanf_s("%d", &n);
    int** G = new int* [n];
    int* dis = new int[n];
    int* ex = new int[n];
    for (int i = 0; i < n; i++)
    {
        G[i] = new int[n];
        ex[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (i == j)
            {
                G[i][j] = 0;
            }
            else if (i != j)
            {
                G[i][j] = rand() % 10;
                G[j][i] = G[i][j];
            }
        }
    }

    printf("Матрица смежности:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            dis[j] = -1;
        BFSD(i, n, &dis[0], &(&G)[0][0], &ex[0]);
        printf("\n");
    }

    printf("Эксцентриситет\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d[%d]\n", ex[i], i);
        if (ex[i] > D)
            D = ex[i];
        if (ex[i] < R)
            R = ex[i];
    }
    printf("Диаметр - %d\nРадиус - %d", D, R);
    for (int i = 0; i < n; i++)
    {
        if (ex[i] == D)
            printf("\nПерифирийная вершина - % d", i);
        if (ex[i] == R)
            printf("\nЦентральная вершина - % d", i);
    }
}