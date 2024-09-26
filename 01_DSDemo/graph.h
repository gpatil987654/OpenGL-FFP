#ifndef __GRAPH_H
#define __GRAPH_H

#define SUCCESS 1
#define G_TRUE 1
#define G_FALSE 0
#define G_INVALID_VERTEX 2
#define G_INVALID_EDGE 3

typedef int vertex_t;
typedef struct vnode vnode_t;
typedef struct hnode hnode_t;
typedef vnode_t vlist_t;
typedef hnode_t hlist_t;
typedef struct graph graph_t;
typedef int status_t;
typedef struct vec3 vec3_t;

struct vec3
{
    float x, y, z;
};

struct graph
{
    vlist_t *pv_list;
    int nr_edges;
    int nr_vertices;
};

struct vnode
{
    vertex_t v;
    vec3_t pos;
    hlist_t *ph_list;

    vnode_t *next;
    vnode_t *prev;
};

struct hnode
{
    vertex_t v;
    vec3_t pos;
    double height;
    float fAngle1;
    float fAngle2;
    float rad;
    vnode_t *pv;

    hnode_t *next;
    hnode_t *prev;
};

// Directed Graph
graph_t *g_create_graph();
status_t g_add_edge(graph_t *g, vertex_t v_start, vec3_t v_start_pos, vertex_t v_end, vec3_t v_end_pos, double height, float fAngle1, float fAngle2, float rad);
status_t g_add_vertex(graph_t *g, vertex_t v, vec3_t pos);
status_t g_remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end);
status_t g_remove_vertex(graph_t *g, vertex_t v);
status_t g_destroy_graph(graph_t **pp_g);

// vnode
vlist_t *v_create_list();
vnode_t *v_get_node(vertex_t v, vec3_t pos);
status_t v_insert_end(vlist_t *pv_list, vertex_t v, vec3_t pos);
vnode_t *v_search_list(vlist_t *pv_list, vertex_t v);
status_t v_generic_insert(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end);
status_t v_remove_end(vlist_t *pv_list, vertex_t v);
status_t v_generic_delete(vnode_t *pv_delete);
status_t v_destroy_list(vlist_t **pp_vlist);

// hnode
hlist_t *h_create_list();
hnode_t *h_get_node(vertex_t v, vec3_t pos, double height, float fAngle1, float fAngle2, vnode_t *pv, float rad);
status_t h_insert_end(hlist_t *ph_list, vertex_t v, vec3_t pos, double height, float fAngle1, float fAngle2, vnode_t *pv, float rad);
status_t h_generic_insert(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end);
hnode_t *h_search_list(hlist_t *ph_list, vertex_t v);
status_t h_remove_end(hlist_t *ph_list, vertex_t v);
status_t h_generic_delete(hnode_t *ph_delete);
status_t h_destroy_list(hlist_t **pp_hlist);

void *xMalloc(size_t num_of_bytes);

#endif
