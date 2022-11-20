#include "header.h"

void addEdge(t_graph *g, t_vertex *src, t_vertex *dest)
{
    t_edge *newEdge = malloc(sizeof(t_edge));

    newEdge->distance = 1;
    newEdge->forwardEdgeWater = newEdge->backwardEdgeWater = 0;
    newEdge->forwardEdgeElec = newEdge->backwardEdgeElec = 0;
    newEdge->nextEdge= NULL;
    newEdge->adjVertex = dest;

    if (!src->edges)
        src->edges = newEdge;
    else
    {

        t_edge *temp = src->edges;
        while (temp)
            if (temp->adjVertex == newEdge->adjVertex)
                return;
            else
                temp = temp->nextEdge;

        temp = src->edges;
        while (temp->nextEdge)
            if (temp->adjVertex == newEdge->adjVertex)
                return;
            else
                temp = temp->nextEdge;
        temp->nextEdge = newEdge;
    }
}


void createVertex(t_graph *g, int x, int y, t_case **terrain, int type)
{
    if (terrain[y][x].type == 1)
        return;

    t_vertex *newVertex = malloc(sizeof(t_vertex));

    newVertex->x = x;
    newVertex->y = y;
    newVertex->parent = NULL;
    newVertex->visited = 0;
    newVertex->group = 0;
    newVertex->id = g->ordre;
    newVertex->edges = NULL;

    switch(type)
    {
    case 1:
    {
        newVertex->structure = 1;
        //connectVertexes(g);
        terrain[y][x].type = 1;
        break;
    }
    case 2:
    {
        newVertex->structure = 2;
        //connectVertexes(g);
        terrain[y][x].type = 2;
        break;
    }
    case 3:
    {
        newVertex->structure = 3;
        //connectVertexes(g);
        terrain[y][x].type = 3;
        break;
    }
    case 4:
    {
        newVertex->structure = 4;
        //connectVertexes(g);
        terrain[y][x].type = 4;
        break;
    }
    }

    terrain[y][x].vertexId = newVertex->id;
    g->vertexes[g->ordre] = newVertex;
    g->ordre++;
}

t_vertex *find(t_graph *g, int x, int y)
{
    t_vertex *res = NULL;
    for (int i=0; i<g->ordre; i++)
    {
        if (g->vertexes[i]->x == x && g->vertexes[i]->y == y)
            res = g->vertexes[i];
    }

    return res;
}

void connectStructures(t_graph *g, t_case **terrain)
{
    t_vertex *u, *v = NULL;
    int x, y, i;
    for (int k=0; k<g->ordre; k++)
    {
        u = g->vertexes[k];
        x = u->x;
        y = u->y;

        if (u->structure == 2)
        {
            if (x > 1 && y > 1 && x < xMax-2 && y < yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == 1 && y == 1)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == xMax-2 && y == yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
        }
            else if (x == 1 && y > 1)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }

            }
            else if (x > 1 && y == 1)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == xMax-2 && y < yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x < xMax-2 && y == yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
        }
        if (u->structure == 3)
        {
            if (x > 1 && y > 2 && x < xMax-3 && y < yMax-4)
            {
                for(i=-3; i<5; i++)
                {
                    if (terrain[y+i][x+3].type == 1)
                    {
                        v = find(g, x+3, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-3; i<5; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-2; i<4; i++)
                {
                    if (terrain[y-3][x+i].type == 1)
                    {
                        v = find(g, x+i, y-3);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-2; i<4; i++)
                {
                    if (terrain[y+4][x+i].type == 1)
                    {
                        v = find(g, x+i, y+4);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == 1 && y == 2)
            {
                for(i=-2; i<5; i++)
                {
                    if (terrain[y+i][x+3].type == 1)
                    {
                        v = find(g, x+3, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<4; i++)
                {
                    if (terrain[y+4][x+i].type == 1)
                    {
                        v = find(g, x+i, y+4 );
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == xMax-2 && y == yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
        }
            else if (x == 1 && y > 1)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }

            }
            else if (x > 1 && y == 1)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x == xMax-2 && y < yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+2][x+i].type == 1)
                    {
                        v = find(g, x+i, y+2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
            else if (x < xMax-2 && y == yMax-2)
            {
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x+2].type == 1)
                    {
                        v = find(g, x+2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y+i][x-2].type == 1)
                    {
                        v = find(g, x-2, y+i);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
                for(i=-1; i<2; i++)
                {
                    if (terrain[y-2][x+i].type == 1)
                    {
                        v = find(g, x+i, y-2);
                        if (v)
                        {
                            addEdge(g, u, v);
                            addEdge(g, v, u);
                        }
                    }
                }
            }
        }
    }
}


void connectRoads(t_graph *g, t_case **terrain)
{
    for (int i=0; i<g->ordre; i++)
    {
        for (int j=0; j<g->ordre; j++)
        {
            if ((g->vertexes[i]->x+1 == g->vertexes[j]->x && g->vertexes[i]->y == g->vertexes[j]->y))
            {
                addEdge(g, g->vertexes[i], g->vertexes[j]);
                addEdge(g, g->vertexes[j], g->vertexes[i]);
            }
            if (g->vertexes[i]->x-1 == g->vertexes[j]->x && g->vertexes[i]->y == g->vertexes[j]->y)
            {
                addEdge(g, g->vertexes[i], g->vertexes[j]);
                addEdge(g, g->vertexes[j], g->vertexes[i]);
            }
            if (g->vertexes[i]->x == g->vertexes[j]->x && g->vertexes[i]->y+1 == g->vertexes[j]->y)
            {
                addEdge(g, g->vertexes[i], g->vertexes[j]);
                addEdge(g, g->vertexes[j], g->vertexes[i]);
            }
            if (g->vertexes[i]->x == g->vertexes[j]->x && g->vertexes[i]->y-1 == g->vertexes[j]->y)
            {
                addEdge(g, g->vertexes[i], g->vertexes[j]);
                addEdge(g, g->vertexes[j], g->vertexes[i]);
            }
        }
    }
}
