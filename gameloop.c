void gameLoop(BITMAP* page, t_graph *g, t_case **terrain)
{
    int end=0, mx, my;
    int level = 1, edit = 0;
    int pauseTime;

    int type, state;

    volatile int timer = 0;
    void increment_timer()
    {
        timer++;
    }
    END_OF_FUNCTION(increment_timer);
    LOCK_FUNCTION(increment_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(increment_timer, SECS_TO_TIMER(1));

    while (!end)
    {
        mx = mouse_x/size;
        my = mouse_y/size;

        if(mouse_b & 1 && (mx > 45 && mx < 50))
        {
            switch(my)
            {
            case 2:
            {
                level = 1;
                break;
            }
            case 3:
            {
                level = 2;
                break;
            }
            case 4:
            {
                level = 3;
                break;
            }
            default:
                break;
            }
        }

        if(mouse_b & 1)
        {
            pauseTime = timer;
            rest(100);

            if (level == 1)
            {
                if (mx >= 46 && my == 12)
                {
                    edit = 1;
                    type = 1;
                    state = 4;
                    while (edit)
                    {
                        mx = mouse_x/size;
                        my = mouse_y/size;

                        if (mouse_b & 1)
                        {
                            if (mx >= 46 && my == 12)
                            {
                                edit = 0;
                                rest(50);
                            }
                            else if (mx <= xMax-1 && my <= yMax-1 && mx >= 0 && my >= 0 && !terrain[my][mx].type)
                            {
                                createVertex(g, mx, my, terrain, type);
                                connectRoads(g, terrain);
                                connectStructures(g, terrain);
                            }
                        }

                        updateGraphics(page, pauseTime, terrain, mx, my, state, level);
                    }
                    rest(100);
                }
                else if (mx >=46 && my == 6)
                {
                    nv_bat(g, page, terrain, timer, 2);
                    connectStructures(g, terrain);
                }
                else if (mx >=46 && my == 8)
                {
                    nv_bat(g, page, terrain, timer, 3);
                }
                else if (mx >=46 && my == 10)
                {
                    nv_bat(g, page, terrain, timer, 4);
                }
            }

            timer = pauseTime;
        }

        if (key[KEY_SPACE])
        {
            showG(g);
            rest(100);
        }

        updateGraphics(page, timer, terrain, mx, my, 0, level);

        if (key[KEY_ESC])
            end = 1;
    }
}
