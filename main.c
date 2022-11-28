#include <stdio.h>
#include <stdlib.h>
#include "allegro.h"

void initialisationAllegro()
{
    allegro_init();
    install_timer();
    install_mouse();
    install_keyboard();
    set_window_title("ECE City");
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0))!=0)
    {
        allegro_message("Erreur de mode graphique\n") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void menu()
{
    int fin = 1;
    int x1 = 290;  //Variable pour le clic du menu
    int x2 = 347;

    //MUSIQUE
    SAMPLE *the_sample;
    int pan = 128;
    int pitch = 1000;

    // Double buffer
    BITMAP *page;

    //Image Fond
    BITMAP *fond;

    //Image regles
    BITMAP *fondrules;

    //Image choix joueur
    BITMAP *mode;
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

    /* LANCEMENT MUSIQUE */
    play_sample(the_sample, 255, pan, pitch, TRUE);

    /*** CHARGEMENT DES FONDS INFORMATIONS MENU ***/
    fondrules=load_bitmap("img/menu/fondrules.bmp",NULL);
    if (!fondrules)
    {
        allegro_message("img/menu/Fond regles introuvable :( ");
        exit(EXIT_FAILURE);
    }


    mode=load_bitmap("img/menu/mode.bmp",NULL);
    if (!mode)
    {
        allegro_message("Photo mode de jeu introuvable :( ");
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

        //Affichage du menu en 1024-768
        clear(page);
        draw_sprite(page, fond, 0, 0);

        //Boucle servant à lancer le jeu
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>196 && mouse_y<261)
        {
            //stop_sample(the_sample);
            stop_sample(the_sample);
            show_mouse(NULL);

            //CHOIX MODE DE JEU
            clear(page);
            draw_sprite(page, mode, 0, 0);


            //on initialise le terrain, les differentes structures pour le jeu



           // play_sample(the_sample, 255, pan, pitch, TRUE); je sais pas si je le met
            clear(fond);
            blit(page, fond, 0, 0, 0, 0, 1024, 768);
        }


        //Boucle servant à lancer la partie déjà en cours
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>300 && mouse_y<370)
        {
            //reprendre le jeu? DONC on lance sauvegarde
        }

        //Boucle sur les règles
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>415 && mouse_y<479)
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

        //Boucle servant quitter le jeu
        if(mouse_b&1 && mouse_x>x1 && mouse_x<x2 && mouse_y>519 && mouse_y<589)
        {
            //BOUTON QUITTER
            fin = 0;
        }

        //textprintf_ex(fond, font, 60,300, makecol(0,255,0), makecol(255, 0,0), "%4d  %4d", mouse_x, mouse_y);
        //textprintf_ex(fond, font, 60,300, makecol(0,255,0), makecol(255, 0,0), "%4d  %4d", mouse_x, mouse_y);
        show_mouse(page);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }


    /* destroy the sample */
    destroy_sample(the_sample);
    destroy_bitmap(mode);
    destroy_bitmap(fond);
    destroy_bitmap(fondrules);
    destroy_bitmap(retour);
}

int main()
{
    initialisationAllegro();
    menu();

    return 0;
}
END_OF_MAIN();
