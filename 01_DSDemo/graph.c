#include "common.h"
#include "graph.h"

// Directed Graph
graph_t *g_create_graph()
{
    graph_t *g = NULL;
    g = (graph_t *)xMalloc(sizeof(graph_t));

    g->nr_edges = 0;
    g->nr_vertices = 0;
    g->pv_list = v_create_list();

    return g;
}

status_t g_add_edge(graph_t *g, vertex_t v_start, vec3_t v_start_pos, vertex_t v_end, vec3_t v_end_pos, double height, float fAngle1, float fAngle2, float rad)
{
    vnode_t *pv_start = NULL;
    vnode_t *pv_end = NULL;
    hnode_t *ph_node = NULL;

    pv_start = v_search_list(g->pv_list, v_start);

    if (pv_start == NULL)
    {
        v_insert_end(g->pv_list, v_start, v_start_pos);
        g->nr_vertices++;
    }

    pv_end = v_search_list(g->pv_list, v_end);

    if (pv_end == NULL)
    {
        v_insert_end(g->pv_list, v_end, v_end_pos);
        g->nr_vertices++;
    }

    ph_node = h_search_list(pv_start->ph_list, v_end);

    if (ph_node == NULL)
    {
        h_insert_end(pv_start->ph_list, v_end, v_end_pos, height, fAngle1, fAngle2, pv_end, rad);
        g->nr_edges++;
    }

    return SUCCESS;
}

status_t g_add_vertex(graph_t *g, vertex_t v, vec3_t pos)
{
    return v_insert_end(g->pv_list, v, pos);
}

status_t g_remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end)
{

    return SUCCESS;
}

status_t g_remove_vertex(graph_t *g, vertex_t v)
{
    return SUCCESS;
}

status_t g_destroy_graph(graph_t **pp_g)
{
    graph_t *g = *pp_g;

    // vnode_t *pv_run = NULL;
    // vnode_t *pv_next = NULL;
    v_destroy_list(&g->pv_list);

    free(g);
    *pp_g = NULL;

    return SUCCESS;
}

// vnode
vlist_t *v_create_list()
{
    vlist_t *pv_list = NULL;
    vec3_t pos = {0, 0, 0};
    pv_list = v_get_node(0, pos);

    pv_list->next = pv_list;
    pv_list->prev = pv_list;

    return pv_list;
}
vnode_t *v_search_list(vlist_t *pv_list, vertex_t v)
{
    vnode_t *pv_run = NULL;

    pv_run = pv_list->next;

    while (pv_run != pv_list)
    {
        if (pv_run->v == v)
            return pv_run;
        pv_run = pv_run->next;
    }

    return NULL;
}

vnode_t *v_get_node(vertex_t v, vec3_t pos)
{
    vnode_t *pv_node = NULL;

    pv_node = (vnode_t *)xMalloc(sizeof(vnode_t));
    pv_node->pos = pos;
    pv_node->v = v;

    pv_node->ph_list = h_create_list();
    pv_node->next = NULL;
    pv_node->prev = NULL;

    return pv_node;
}

status_t v_insert_end(vlist_t *pv_list, vertex_t v, vec3_t pos)
{
    return v_generic_insert(pv_list->prev, v_get_node(v, pos), pv_list);
}
status_t v_generic_insert(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end)
{
    p_mid->prev = p_beg;
    p_mid->next = p_end;

    p_beg->next = p_mid;
    p_end->prev = p_mid;
    return SUCCESS;
}

status_t v_remove_end(vlist_t *pv_list, vertex_t v)
{
    return SUCCESS;
}
status_t v_generic_delete(vnode_t *pv_delete)
{
    return SUCCESS;
}
status_t v_destroy_list(vlist_t **pp_vlist)
{
    vlist_t *pv_list = *pp_vlist;
    vnode_t *pv_run;
    vnode_t *pv_next;

    pv_run = pv_list->next;

    while (pv_run != pv_list)
    {
        pv_next = pv_run->next;
        h_destroy_list(&(pv_run->ph_list));
        free(pv_run);
        pv_run = pv_next;
    }
    free(pv_list);

    *pp_vlist = NULL;
    return SUCCESS;
}

// hnode
hlist_t *h_create_list()
{
    hlist_t *ph_list = NULL;
    vec3_t pos = {0, 0, 0};
    ph_list = h_get_node(0, pos, 0, 0, 0, NULL, 0);

    ph_list->next = ph_list;
    ph_list->prev = ph_list;

    return ph_list;
}

hnode_t *h_get_node(vertex_t v, vec3_t pos, double height, float fAngle1, float fAngle2, vnode_t *pv, float rad)
{
    hnode_t *ph_node = NULL;

    ph_node = (hnode_t *)xMalloc(sizeof(hnode_t));

    ph_node->v = v;
    ph_node->pos = pos;
    ph_node->height = height;
    ph_node->fAngle1 = fAngle1;
    ph_node->fAngle2 = fAngle2;
    ph_node->pv = pv;
    ph_node->rad = rad;

    ph_node->next = NULL;
    ph_node->prev = NULL;

    return ph_node;
}

status_t h_insert_end(hlist_t *ph_list, vertex_t v, vec3_t pos, double height, float fAngle1, float fAngle2, vnode_t *pv, float rad)
{
    return h_generic_insert(ph_list->prev, h_get_node(v, pos, height, fAngle1, fAngle2, pv, rad), ph_list);
}

hnode_t *h_search_list(hlist_t *ph_list, vertex_t v)
{
    hnode_t *ph_run = NULL;

    ph_run = ph_list->next;

    while (ph_run != ph_list)
    {
        if (ph_run->v == v)
            return ph_run;
        ph_run = ph_run->next;
    }

    return NULL;
}

status_t h_generic_insert(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end)
{
    p_mid->prev = p_beg;
    p_mid->next = p_end;

    p_beg->next = p_mid;
    p_end->prev = p_mid;
    return SUCCESS;
}

status_t h_remove_end(hlist_t *ph_list, vertex_t v)
{
    return SUCCESS;
}

status_t h_generic_delete(hnode_t *ph_delete)
{
    return SUCCESS;
}
status_t h_destroy_list(hlist_t **pp_hlist)
{
    hlist_t *ph_list = *pp_hlist;
    hnode_t *ph_run;
    hnode_t *ph_next;

    ph_run = ph_list->next;

    while (ph_run != ph_list)
    {
        ph_next = ph_run->next;
        free(ph_run);
        ph_run = ph_next;
    }

    free(ph_list);
    *pp_hlist = NULL;

    return SUCCESS;
}

void *xMalloc(size_t num_of_bytes)
{
    void *p = malloc(num_of_bytes);

    if (p == NULL)
    {
        printf("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    return p;
}
