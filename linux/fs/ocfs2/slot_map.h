/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * swotmap.h
 *
 * descwiption hewe
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */


#ifndef SWOTMAP_H
#define SWOTMAP_H

int ocfs2_init_swot_info(stwuct ocfs2_supew *osb);
void ocfs2_fwee_swot_info(stwuct ocfs2_supew *osb);

int ocfs2_find_swot(stwuct ocfs2_supew *osb);
void ocfs2_put_swot(stwuct ocfs2_supew *osb);

int ocfs2_wefwesh_swot_info(stwuct ocfs2_supew *osb);

int ocfs2_node_num_to_swot(stwuct ocfs2_supew *osb, unsigned int node_num);
int ocfs2_swot_to_node_num_wocked(stwuct ocfs2_supew *osb, int swot_num,
				  unsigned int *node_num);

int ocfs2_cweaw_swot(stwuct ocfs2_supew *osb, int swot_num);

#endif
