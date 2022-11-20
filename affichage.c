#include "header.h"

void showG(t_graph *g)
{
    for (int i=0; i<g->ordre; i++)
    {
        if(g->vertexes[i]->structure == 3)
        {
        printf("Vertex : id %d, \tx:%d  y:%d    type:%d\n", g->vertexes[i]->id, g->vertexes[i]->x, g->vertexes[i]->y,g->vertexes[i]->structure);
        printf("list : \n");
        t_edge *temp = g->vertexes[i]->edges;
        while (temp)
        {
            printf("adj:%d, %d %d\n", temp->adjVertex->id, temp->adjVertex->x, temp->adjVertex->y);
            temp = temp->nextEdge;
        }
        printf("\n\n");
        }
    }
}

void carrelage(BITMAP* page)
{
    for (int i=0; i < yMax; i++)
        for (int j=0; j < xMax; j++)
            rect(page, j*size, i*size, j*size+size, i*size+size, makecol(200, 200, 200));
}


void caseFill(BITMAP *page, t_case **terrain, int level)
{
    for (int i=0; i<yMax; i++)
        for (int j=0; j<xMax; j++)
            switch(terrain[i][j].type)
            {
            case 1:
            {
                switch (level)
                {
                case 1:
                {
                    rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(0, 0, 0));
                    break;
                }
                case 2:
                {
                    rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(0, 150, 255));
                    break;
                }
                case 3:
                {
                    rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(255, 200, 0));
                    break;
                }
                default:
                {
                    rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(0, 0, 0));
                    break;
                }
                }
                break;
            }
            case 2:
            {
                rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(255, 50, 50));
                break;

            }
            case 3 :
            {
                rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(50, 50, 200));
                break;
            }
            case 4 :
            {
                rectfill(page, terrain[i][j].x*size, terrain[i][j].y*size, terrain[i][j].x*size+size, terrain[i][j].y*size+size, makecol(250, 250, 0));
                break;
            }
            default:
                break;
            }
}


void updateGraphics(BITMAP* page, int time, t_case **terrain, int mx, int my, int state, int level)
{
    clear_bitmap(page);
    rectfill(page, 0, 0, SCREEN_W, SCREEN_H, makecol(255, 255, 255));

    if (level == 1)
    {
        rectfill(page,46*size,6*size,50*size,7*size,makecol(150,0,0));
        rectfill(page,46*size,8*size,50*size,9*size,makecol(0,150,255));
        rectfill(page,46*size,10*size,50*size,11*size,makecol(255,200,0));
        rectfill(page,46*size,12*size,50*size,13*size,makecol(0,0,0));
    }

    switch (state)
    {
    case 1:
    {
        if (mx < xMax-1 && my < yMax-1 && mx > 0 && my > 0)
            rectfill(page,(mx-1)*size,(my-1)*size,(mx+2)*size,(my+2)*size,makecol(255,0,0));
        break;
    }
    case 2:
    {
        if (mx < xMax-2 && my < yMax-3 && mx > 0 && my > 1)
            rectfill(page,(mx-1)*size,(my-2)*size,(mx+3)*size,(my+4)*size,makecol(50,0,200));
        break;
    }
    case 3:
    {
        if (mx < xMax-3 && my < yMax-2 && mx > 1 && my > 0)
            rectfill(page,(mx-2)*size,(my-1)*size,(mx+4)*size,(my+3)*size,makecol(255,255,0));
        break;
    }
    case 4: //route
    {
        rectfill(page,46*size,12*size,50*size,13*size,makecol(100,0,0));
        break;
    }
    default:
    {
        break;
    }
    }

    switch (level)
    {
    case 1:
    {
        textprintf_ex(page, font, 46*size, 2*size, makecol(0, 0, 0), makecol(200, 200, 200), "Niveau 0");
        textprintf_ex(page, font, 46*size, 3*size, makecol(0, 150, 255), -1, "Niveau 1");
        textprintf_ex(page, font, 46*size, 4*size, makecol(255, 200, 0), -1, "Niveau 2");
        caseFill(page, terrain, level);
        break;
    }
    case 2:
    {
        textprintf_ex(page, font, 46*size, 2*size, makecol(0, 0, 0), -1, "Niveau 0");
        textprintf_ex(page, font, 46*size, 3*size, makecol(0, 150, 255), makecol(200, 200, 200), "Niveau 1");
        textprintf_ex(page, font, 46*size, 4*size, makecol(255, 200, 0), -1, "Niveau 2");
        caseFill(page, terrain, level);
        break;
    }
    case 3:
    {
        textprintf_ex(page, font, 46*size, 2*size, makecol(0, 0, 0), -1, "Niveau 0");
        textprintf_ex(page, font, 46*size, 3*size, makecol(0, 150, 255), -1, "Niveau 1");
        textprintf_ex(page, font, 46*size, 4*size, makecol(255, 200, 0), makecol(200, 200, 200), "Niveau 2");
        caseFill(page, terrain, level);
        break;
    }
    default:
    {
        textprintf_ex(page, font, 46*size, 2*size, makecol(0, 0, 0), -1, "Niveau 0");
        textprintf_ex(page, font, 46*size, 3*size, makecol(0, 150, 255), -1, "Niveau 1");
        textprintf_ex(page, font, 46*size, 4*size, makecol(255, 200, 0), -1, "Niveau 2");
        caseFill(page, terrain, 1);
    }
    }


    caseFill(page, terrain, level);
    carrelage(page);

    textprintf_ex(page, font, 500, 20, makecol(250, 0, 0), -1, "x: %d    y: %d", mx, my);
    if (mx < xMax && my < yMax)
        textprintf_ex(page, font, 500, 30, makecol(250, 0, 0), -1, "type: %d  id: %d", terrain[my][mx].type, terrain[my][mx].vertexId);
    if (!(time%15))
        textprintf_ex(page, font, 905, 20, makecol(255, 0, 0), -1, "temps: %ds", time);
    else
        textprintf_ex(page, font, 905, 20, makecol(0, 0, 0), -1, "temps: %ds", time);
    show_mouse(page);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
