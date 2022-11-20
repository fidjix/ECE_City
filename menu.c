void menu()
{
    int fin = 1;
    int x1 = 395; //Deux variables pour les intervalles des clics du menu
    int x2 = 671;

    //MUSIQUE
    SAMPLE *the_sample;
    int pan = 128;
    int pitch = 1000;

    // Double buffer
    BITMAP *page;
    // Image Choix
    BITMAP *jouer;
    BITMAP *charge;
    BITMAP *regles;
    BITMAP *classes;
    BITMAP *quitter;
    //Image Fond
    BITMAP *fond;
    //Image regles
    BITMAP *fondrules;
    //Image classes
    BITMAP *fondclass;
    BITMAP *choixclass;
    //Image choix joueur
    BITMAP *nbplay;
    BITMAP *retour;


    //https://sourceforge.net/p/alleg/allegro/ci/ecb3132864649d5728e403b511c206932bc23849/tree/examples/exsample.c
    /* Installation des drivers musique */
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0)
    {
        allegro_message("Error initialising sound system");
        return;
    }

    /* Lecture du fichier WAV */
    the_sample = load_sample("img/menu/music.wav");
    if (!the_sample)
    {
        allegro_message("Error reading WAV file");
        return;
    }

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // CHARGEMENT FOND
    fond=load_bitmap("img/menu/fond.bmp",NULL);
    if (!fond)
    {
        allegro_message("Fond introuvable :( ");
        exit(EXIT_FAILURE);
    }

    /******************************************/
    /*** INITIALISATION DES BOUTONS MENU*******/
    /******************************************/

    jouer=load_bitmap("img/menu/jouer.bmp",NULL);
    if (!jouer)
    {
        allegro_message("Photo Jouer introuvable :( ");
        exit(EXIT_FAILURE);
    }

    charge=load_bitmap("img/menu/charge.bmp",NULL);
    if (!charge)
    {
        allegro_message("Photo Charge introuvable :( ");
        exit(EXIT_FAILURE);
    }

    regles=load_bitmap("img/menu/regles.bmp",NULL);
    if (!regles)
    {
        allegro_message("Photo Regles introuvable :( ");
        exit(EXIT_FAILURE);
    }

    classes=load_bitmap("img/menu/classes.bmp",NULL);
    if (!classes)
    {
        allegro_message("Photo Classes introuvable :( ");
        exit(EXIT_FAILURE);
    }

    quitter=load_bitmap("img/menu/quitter.bmp",NULL);
    if (!quitter)
    {
        allegro_message("Photo Quitter introuvable :( ");
        return;
    }

    /* LANCEMENT MUSIQUE */
    play_sample(the_sample, 255, pan, pitch, TRUE);

    /*** CHARGEMENT DES FONDS INFORMATIONS MENU ***/
    fondrules=load_bitmap("img/menu/fondrules.bmp",NULL);
    if (!fondrules)
    {
        allegro_message("img/menu/Fond regles introuvable :( ");
        exit(EXIT_FAILURE);
    }

    fondclass=load_bitmap("img/menu/fondclasses.bmp",NULL);
    if (!fondclass)
    {
        allegro_message("Fond classes introuvable :( ");
        exit(EXIT_FAILURE);
    }

    choixclass=load_bitmap("img/menu/choixclasses.bmp",NULL);
    if (!choixclass)
    {
        allegro_message("Photo choix Classes introuvable :( ");
        exit(EXIT_FAILURE);
    }

    nbplay=load_bitmap("img/menu/player.bmp",NULL);
    if (!nbplay)
    {
        allegro_message("Photo nb joueur introuvable :( ");
        exit(EXIT_FAILURE);
    }

    retour=load_bitmap("img/menu/retour.bmp",NULL);
    if (!retour)
    {
        allegro_message("Bouton introuvable :( ");
        exit(EXIT_FAILURE);
    }


    //CODE DU MENU
    while(fin != 0)
    {

        //Affichage du menu en 1080-720
        clear(page);

        draw_sprite(fond, jouer, 395, 220);
        draw_sprite(fond, charge, 394, 290);
        draw_sprite(fond, regles, 395, 360);
        draw_sprite(fond, classes, 395, 430);
        draw_sprite(fond, quitter, 395, 500);
        draw_sprite(page, fond, 0, 0);


        //Boucle sur les règles
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>365 && mouse_y<421)
        {
            //BOUTON REGLES
            clear(page);
            draw_sprite(page, fondrules, 0, 0);
            draw_sprite(page, retour, 20, 20);

            while(!(mouse_b&1 && mouse_x>20 && mouse_x<90 && mouse_y>20 && mouse_y<72))
            {
                blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }

        }

        //Boucle pour explications des classes
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>435 && mouse_y<491)
        {
            //BOUTON CLASSES
            //Je vais faire faire une image aussi

            clear(page);
            draw_sprite(page, fondclass, 0, 0);
            draw_sprite(page, retour, 20, 20);

            while(!(mouse_b&1 && mouse_x>20 && mouse_x<90 && mouse_y>20 && mouse_y<72))
            {
                blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            }

        }

        //Boucle servant quitter le jeu
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>485 && mouse_y<561)
        {
            //BOUTON QUITTER
            fin = 0;
        }

        show_mouse(page);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }


    /* destroy the sample */
    destroy_sample(the_sample);

    destroy_bitmap(jouer);
    destroy_bitmap(charge);
    destroy_bitmap(regles);
    destroy_bitmap(classes);
    destroy_bitmap(quitter);
    destroy_bitmap(fond);
    destroy_bitmap(fondrules);
    destroy_bitmap(fondclass);
    destroy_bitmap(retour);
}
