typedef struct graph {

    int ordre, flotEau, flotElec;
    t_city *ville;
    t_vertex **vertexes;

} t_graph;

typedef struct edge {

    int distance;
    int forwardEdgeWater, backwardEdgeWater;
    int forwardEdgeElec, backwardEdgeElec;

    struct vertex *adjVertex;
    struct edge *nextEdge;

} t_edge;

typedef struct vertex {

    int id, x, y;
    int visited;
    int group;
    struct vertex *parent;
    t_edge *edges;
    int structure;  //1=route   2=maison 3=eau 4=elec

} t_vertex;

typedef struct city{
    int money, hab, eau, elec, nb_bat;
    int* home;
    //t_case* home;
}t_city;

t_graph *initialisationGraph()
{
    t_graph *g = NULL;
    g = malloc(sizeof(t_graph));
    g->ordre = 0;
    g->vertexes = malloc(xMax*yMax*sizeof(t_vertex*));
    for (int i=0; i<xMax*yMax; i++)
    {
        g->vertexes[i] = malloc(sizeof(t_vertex));
        g->vertexes[i] = NULL;
    }

    g->ville = malloc(sizeof(t_city));

    g->ville->nb_bat = 0;
    g->ville->eau = 0;
    g->ville->elec = 0;
    g->ville->hab = 0;
    g->ville->money = 500000;

    g->ville->home = malloc(20 * sizeof(int));

    return g;
}
