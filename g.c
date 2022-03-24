#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 100
#define WIDTH 100


void dfs(int v, int visited[], int vert, int matrix[][100])
{
    if(visited[v]){
        return;
    }
    visited[v] = 1;
    for(int i = 0; i < vert; i++){
        if(matrix[v][i]){
            dfs(i, visited, vert, matrix);
        }
    }
}

int main()
{
    int len = 100;
    char line[len];
    int matrix[HEIGHT][WIDTH];

    int w = 0, h = 0, cc = 0;

    int visited[len];



    FILE * matrixFile;
    FILE * graphFile;

    matrixFile = fopen("graph copy.txt", "r");
        if (!matrixFile)
        exit(EXIT_FAILURE);

    while(fgets(line, len, matrixFile)){
        w = 0;
        for(int i = 0; line[i]; i++){
            if(line[i] != ' '){
                matrix[h][w] = line[i]-'0';
                w++;
            }
        }
        h++;
    }

    dfs(0, visited, h, matrix);
    
    for(int i = 0; i < h; i++){
        if(visited[i]){
            cc += 1;
        }
    }
    if(cc == h){
        printf("График связан ");
    }else{
        printf("График не связан ");
    }


    graphFile = fopen("graf.gv", "w");
    
    fputs("graph  {", graphFile);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(matrix[i][j] >= 1){
                if(i > j){
                    fprintf(graphFile, "%d", i);
                    fputs("--", graphFile);
                    fprintf(graphFile, "%d;", j);
                    fputs("\n", graphFile);

                }

            }
        }
        
    }
    fputs("}", graphFile);
    fclose(graphFile);
    fclose(matrixFile);
    system("dot -Tpng graf.gv -o file.png");
    return (EXIT_SUCCESS);
}