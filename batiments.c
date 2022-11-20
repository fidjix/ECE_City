int ajout_bat(t_case** sol,int mx,int my,int type)     //doit renvoyer valeur car si clic pas possible on reste dedans
{
    int **tab = NULL;
    int a,b,possible=1;

    ///test pour le terrain s'il est libre
    if(type == 2)   //maison
    {
        tab = malloc(3*sizeof(int*));
        for (int i=0; i<3; i++)
            tab[i] = malloc(3*sizeof(int));

        b=my-1;
        for(int i=0; i<3; i++)
        {
            a = mx-1;
            for(int j=0; j<3; j++)
            {
                if(!sol[b][a].type)
                    tab[i][j]=1;
                else
                    tab[i][j]=0;
                a++;
            }
            b++;
        }

        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(tab[i][j]==0)
                {
                    possible = 0;
                }
            }
        }
        for (int i=0; i<3; i++)
            free(tab[i]);
        free(tab);
    }
    else if(type == 3)  //eau
    {
        tab = malloc(6*sizeof(int*));
        for (int i=0; i<6; i++)
            tab[i] = malloc(4*sizeof(int));

        b=my-2;
        for(int i=0; i<6; i++)
        {
            a = mx-1;
            for(int j=0; j<4; j++)
            {
                if(!sol[b][a].type)
                    tab[i][j]=1;
                else
                    tab[i][j]=0;
                a++;
            }
            b++;
        }

        for(int i=0; i<6; i++)
        {
            for(int j=0; j<4; j++)
            {
                if(tab[i][j]==0)
                {
                    possible = 0;
                }
            }
        }
        for (int i=0; i<6; i++)
            free(tab[i]);
        free(tab);

    }
    else if(type == 4)  //elec
    {
        tab = malloc(4*sizeof(int*));
        for (int i=0; i<4; i++)
            tab[i] = malloc(6*sizeof(int));

        b=my-1;
        for(int i=0; i<4; i++)
        {
            a = mx-2;
            for(int j=0; j<6; j++)
            {
                if(!sol[b][a].type)
                    tab[i][j]=1;
                else
                    tab[i][j]=0;
                a++;
            }
            b++;
        }

        for(int i=0; i<4; i++)
        {
            for(int j=0; j<6; j++)
            {
                if(tab[i][j]==0)
                {
                    possible = 0;
                }
            }
        }
        for (int i=0; i<4; i++)
            free(tab[i]);
        free(tab);
    }

    return possible;
}


void nv_bat(t_graph *g, BITMAP* page, t_case** terr, int time, int type)
{
    int cont = 0, a = 0, b = 0,ste=0;
    int mx, my, id;

    while(!cont)
    {
        mx = mouse_x/20;
        my = mouse_y/20;

        switch (type)
        {
        case 2: //maisons
        {
            ste = 1;
            if(mouse_b & 1 && (mx < xMax-1 && my < yMax-1 && my > 0 && mx > 0))
            {
                cont = ajout_bat(terr,mx,my,type);
                if(cont)
                {
                    createVertex(g, mx, my, terr, type);
                    id = g->vertexes[g->ordre-1]->id;

                    b = my-1;
                    for(int i=0; i<3; i++)
                    {
                        a = mx-1;
                        for(int j=0; j<3; j++)
                        {
                            terr[b][a].type = 2;
                            //createVertex(g, a, b, terr, type);
                            //g->vertexes[g->ordre-1]->id = id;
                            terr[b][a].vertexId = id;
                            a++;
                        }
                        b++;
                    }
                }
            }
            break;
        }
        case 3:     //eau
        {
            ste = 2;
            if(mouse_b & 1 && (mx < xMax-1 && my < yMax-1 && my > 0 && mx > 0))
            {
                cont = ajout_bat(terr,mx,my,type);
                if(cont)
                {
                    createVertex(g, mx, my, terr, type);
                    b = my-2;
                    for(int i=0; i<6; i++)
                    {
                        a = mx-1;
                        for(int j=0; j<4; j++)
                        {
                            terr[b][a].type = 3;
                            terr[b][a].vertexId = g->vertexes[g->ordre-1]->id;
                            a++;
                        }
                        b++;
                    }
                }
            }
            break;
        }
        case 4: //elec
        {
            ste = 3;
            if(mouse_b & 1 && (mx < xMax-1 && my < yMax-1 && my > 0 && mx > 0))
            {
                cont = ajout_bat(terr,mx,my,type);
                if(cont)
                {
                    createVertex(g, mx, my, terr, type);
                    b = my-1;
                    for(int i=0; i<4; i++)
                    {
                        a = mx-2;
                        for(int j=0; j<6; j++)
                        {
                            terr[b][a].type = 4;
                            a++;
                        }
                        b++;
                    }
                }
                createVertex(g, mx, my, terr, type);
            }
            break;
        }
        default:
            break;
        }

        updateGraphics(page, time, terr, mx, my, ste, 1);
    }
    clear_bitmap(page);
}
