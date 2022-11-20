typedef struct caseTerrain {

    int type, x, y;
    int vertexId;
    //bmp;

} t_case;

t_case **initialisationTerrain()
{
    t_case **terrain;
    terrain = malloc(yMax*sizeof(t_case*));
    for (int i=0; i<yMax; i++)
        terrain[i] = malloc(xMax*sizeof(t_case));

    for (int i=0; i<yMax; i++)
        for (int j=0; j<xMax; j++)
        {
            terrain[i][j].type = 0;
            terrain[i][j].x = j;
            terrain[i][j].y = i;
            terrain[i][j].vertexId = 0;
        }

    return terrain;
}
