void enregistrer( t_pTbInfoJoueur tabJ, t_pcartes pLesCartes) {//t_infoProprio tabP[NB_PROPRIETES], int rangJOUEURjoue, t_infoGare tabG[4]){
//ouvrir fichier texte
//ecrire dedans toutes les infos sur les joueurs
    FILE* pf_enregistrer=fopen("partie_enregistree.txt","w");   //on ouvre un fichier pour ECRIRE dedans
    if (pf_enregistrer==NULL){
        printf("erreur d'ouverture du fichier");
    }
    //on écrit dans le fichier texte
    fprintf(pf_enregistrer, "%d\n",tabJ->nb_joueurs);   //nb de joueurs
    fprintf(pf_enregistrer,"%d\n", tabJ->joueur_courant);       //à qui est-ce de jouer ?
            /**pour tous les joueurs**/
    for (int a=0; a<tabJ->nb_joueurs; a++){
        fprintf(pf_enregistrer, "%s\n", tabJ->tabJs[a].nom);   //nom
        fprintf(pf_enregistrer, "%d\n", tabJ->tabJs[a].position);   //position
        fprintf(pf_enregistrer, "%d\n", tabJ->tabJs[a].symbole);   //symbole
        fprintf(pf_enregistrer, "%d\n", tabJ->tabJs[a].compte);   //compte
        fprintf(pf_enregistrer, "%d\n", tabJ->tabJs[a].tourENprison);   //tour en prison
        fprintf(pf_enregistrer, "%d\n", tabJ->tabJs[a].nb_cartesPrison);   //nb cartes prison
    }
            /*** en fonction des proprietes***/
    for(int b=0; b<NB_PROPRIETES; b++){
        fprintf(pf_enregistrer, "%d\n", pLesCartes->propri[b].numJoueur);        //num joueur dans prop
        fprintf(pf_enregistrer, "%d\n", pLesCartes->propri[b].nb_maisons);        //nb maisons
        fprintf(pf_enregistrer, "%d\n", pLesCartes->propri[b].nb_hotel);        //nb hotels
    }
    for(int c=0; c<4;c++){
        fprintf(pf_enregistrer, "%d\n", pLesCartes->lesgares[c].num_proprio);
    }
    fprintf(pf_enregistrer, "%d\n", pLesCartes->nb_maison_plat);
    fprintf(pf_enregistrer, "%d\n", pLesCartes->nb_hotl_plat);

    fclose(pf_enregistrer);
}



void partieENcours(t_pTbInfoJoueur tabJ, t_pcartes pLesCartes) { //t_infoProprio tabP[NB_PROPRIETES], int rangJOUEURjoue, t_infoGare tabG[4]){
    FILE* pf_lire_donnees=fopen("partie_enregistree.txt","r");   //on ouvre un fichier pour ECRIRE dedans
    if (pf_lire_donnees==NULL){
        printf("erreur d'ouverture du fichier");
    }
        //on lit dans le fichier texte
    fscanf(pf_lire_donnees, "%d\n",&(tabJ->nb_joueurs));   //nb de joueurs
    fscanf(pf_lire_donnees,"%d\n", &(tabJ->joueur_courant));    //à qui est-ce de jouer ?

    tabJ->tabJs=(t_infoJoueur*)realloc(tabJ->tabJs, tabJ->nb_joueurs*sizeof(t_infoJoueur));
    if (tabJ->tabJs==NULL){
        printf("erreur");
    }

    char buffer[LONG_PRENOM]="";

            /**pour tous les joueurs**/
    for (int a=0; a<tabJ->nb_joueurs; a++){
        buffer[0]=0;
        fgets(buffer, LONG_PRENOM, pf_lire_donnees);
        //Il faut enlever le \n
        tabJ->tabJs[a].nom[0] = 0;
        strncat(tabJ->tabJs[a].nom, buffer, strlen(buffer)-1);

        //ligne à modifier car chaine de carac  fprintf(pf_enregistrer, "%s", tabJ->tabJs[a].nom);   //nom
        fscanf(pf_lire_donnees, "%d\n", &(tabJ->tabJs[a].position));   //position
        fscanf(pf_lire_donnees, "%d\n", &(tabJ->tabJs[a].symbole));   //symbole
        fscanf(pf_lire_donnees, "%d\n", &(tabJ->tabJs[a].compte));   //compte
        fscanf(pf_lire_donnees, "%d\n", &(tabJ->tabJs[a].tourENprison));   //tour en prison
        fscanf(pf_lire_donnees, "%d\n", &(tabJ->tabJs[a].nb_cartesPrison));   //nb cartes prison
    }
            /*** en fonction des proprietes***/
    for(int b=0; b<NB_PROPRIETES; b++){
        fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->propri[b].numJoueur));        //num joueur dans prop
        fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->propri[b].nb_maisons));        //nb maisons
        fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->propri[b].nb_hotel));        //nb hotels
    }
    for(int c=0; c<4;c++){
        fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->lesgares[c].num_proprio));
    }
    fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->nb_maison_plat));
    fscanf(pf_lire_donnees, "%d\n", &(pLesCartes->nb_hotl_plat));

    fclose(pf_lire_donnees);
}
