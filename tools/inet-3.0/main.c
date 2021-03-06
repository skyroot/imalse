/*
 * Copyright (c) 1999, 2000 University of Michigan, Ann Arbor.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Michigan, Ann Arbor. The name of the University 
 * may not be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Author: Jared Winick (jwinick@eecs.umich.edu)
 *         Cheng Jin (chengjin@eecs.umich.edu)
 *         Qian Chen (qianc@eecs.umich.edu)
 *
 * "@(#) $Id: main.c,v 1.2 2002/06/04 13:23:23 jwinick Exp $ (UM)";
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.h"
#include "inet.h"

#define VERSION "3.0"

/*****************************************************/
/* variables needed for parsing command line options */
/*****************************************************/
extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

/***************************************************************************/
/* the following  constants are computed by poly-fit data of degree 1 node */
/* growth from Nov 1997 to 2000 with respect to the total number of nodes  */
/***************************************************************************/
#define DEGREE_1_SLOPE .292 /* poly-fit under matlab */
//#define DEGREE_1_SLOPE .35
#define DEGREE_1_INTERCEPT 462  /* poly-fit under matlab */

FILE *my_stderr;

/****************************************************/
/* compute the euclidean distance between two nodes */
/****************************************************/
int euclidean(node_type *n1p, node_type *n2p)
{
  float x1, x2, y1, y2, dist;
  
  x1 = n1p->x; x2 = n2p->x; y1 = n1p->y, y2 = n2p->y;
  dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

  return (int) (pow(dist, .5));
}

/************************************************/
/* generate the output of graph in the format   */
/* 3 sections: the first section 1 line gives   */
/* the number of nodes and the number of links. */
/* the second section gives the list of nodes   */
/* and their x and y coordinates.  The third    */
/* section is the adjacency list with each link */
/* listed only once, i.e. symmetric links       */
/*						*/
/* nodes links                                  */
/* id	x_cord 	y_cord			        */
/* ...					        */
/* id	id	cost			        */
/* ...					        */
/************************************************/
void generate_output(node_type *np, int node_num)
{
  #define NODE_LINK
  #define XY_CORD
  #define LINK_WEIGHT
  #define SYMMETRY

  int i, j, dist;
  int link_num = 0;

  for (i=0; i<node_num; ++i)
  {
    link_num += np[i].degree - np[i].free_degree;
    np[i].degree -= np[i].free_degree;
  }

  if ((link_num % 2) != 0)
  {
    fprintf(stderr, "generate_output: error, total outdegree is odd!\n");
    exit(-1);
  }

#ifdef NODE_LINK
  //printf("Num of nodes: %d  Num of links: %d\n", node_num, link_num);
  printf("%d %d\n", node_num,  link_num/2);
#endif /* NODE_LINK */

#ifdef XY_CORD
  for (i=0; i<node_num; ++i)
    printf("%d\t%d\t%d\n", np[i].nid, np[i].x, np[i].y);
#endif /* XY_CORD */

  for (i=0; i<node_num; ++i)
  {
    for(j=0; j<np[i].degree; ++j)
    {
#ifdef SYMMETRY
      if (np[i].nnp[j] && np[i].nnp[j]->nid > np[i].nid) 
      /* output one of the two links assuming symmetry */
#endif /* SYMMETRY */
      {
#ifdef LINK_WEIGHT
        dist = euclidean(&np[i], np[i].nnp[j]); 
        printf("%d\t%d\t%d\n", np[i].nid, np[i].nnp[j]->nid, dist);
#else
        printf("%d\t%d\n", np[i].nid, np[i].nnp[j]->nid);
	// doing this just for clique script, it wants nodeA:nodeB
	//printf("%d:%d\n", np[i].nid, np[i].nnp[j]->nid);
	
#endif /* LINK_WEIGHT */

      } 
    }
  }
}

#define ARGS 4

int usage()
{
  fprintf(stderr, "Usage: inet [-n topology_size] [-d fraction of degree_one_nodes]\n            [-p plane_dimension] [-s seed] [-f debug_output] [-V(sersion)]\n\n");

  return 0;
}

int main(int argc, char **argv)
{
  int node_num;
  int grid_size = 10000;
  int degree_one = 0;
  int placement = 0;
  int expansion = 0;
  int seed = 0;
  int ch;
  int print_version = 0;
  float frac = 0.0;
 
  node_type *node;

  my_stderr = stderr;

  /**************************************/
  /* getopt the command line arguments */
  /**************************************/

  if (argc == 1)
  {
    usage();
    exit(-1);
  }

  while ((ch = getopt(argc, argv, "d:f:p:n:s:Vvh")) != -1)
  {
    switch (ch)
    {
      case 'd':
        frac = atof(optarg);
        break;
      case 'f':
        my_stderr = fopen(optarg, "w");
        if (!my_stderr)
        {
          fprintf(stderr, "unable to open \"%s\" to output debugging info!\n", optarg);
          exit(-1);
        }
        break;
      case 'p':
        grid_size = atoi(optarg);
        break;
      case 'n':
        node_num = atoi(optarg);
        break;
      case 's':
        seed = atoi(optarg) % 64;
        break;
      case 'V':
      case 'v':
        print_version = 1;
        break;
      case 'h':
      default:
        usage();
	exit(-1);
    }
  }
    
  if ( print_version )
  {
    printf("Inet %s\n", VERSION);
    exit(0);
  }
 
  if ( node_num < 3037 )
  {
    fprintf(stderr, "Error! the number of nodes must be no less than 3037!\n");
    exit(-1);
  }

  /****************************************************/
  /* the default is computed by a linear relationship */
  /****************************************************/
  degree_one = (int)((float)node_num * frac);
  if (degree_one == 0)
    degree_one = DEGREE_1_SLOPE * node_num + DEGREE_1_INTERCEPT;
 
  /*******************************************/
  /* initializes the random number generator */
  /*******************************************/
  random_reset();  
  

  /*******************/
  /* allocate memory */
  /*******************/
  node = (node_type *)malloc(sizeof(node_type) * node_num);
  if (!node)
  {
    fprintf(stderr, "no enough memory for node array (%d bytes needed)!\n", sizeof(node_type) * node_num);
    exit(-1);
  }

  /*****************************/
  /* go ahead, make a topology */
  /*****************************/
  generate_degrees(node, node_num, degree_one, seed);
  place_nodes(node, node_num, grid_size, placement, seed);
  connect_nodes(node, node_num, seed);

  generate_output(node, node_num);

  if (my_stderr != stderr)
  {
    fclose(my_stderr);
  }
}
