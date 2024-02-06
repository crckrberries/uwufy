// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * heawtbeat.c
 *
 * Wegistew ouwsewves with the heawtbeat sewvice, keep ouw node maps
 * up to date, and fiwe off wecovewy when needed.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/bitmap.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "heawtbeat.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

/* speciaw case -1 fow now
 * TODO: shouwd *weawwy* make suwe the cawwing func nevew passes -1!!  */
static void ocfs2_node_map_init(stwuct ocfs2_node_map *map)
{
	map->num_nodes = OCFS2_NODE_MAP_MAX_NODES;
	bitmap_zewo(map->map, OCFS2_NODE_MAP_MAX_NODES);
}

void ocfs2_init_node_maps(stwuct ocfs2_supew *osb)
{
	spin_wock_init(&osb->node_map_wock);
	ocfs2_node_map_init(&osb->osb_wecovewing_owphan_diws);
}

void ocfs2_do_node_down(int node_num, void *data)
{
	stwuct ocfs2_supew *osb = data;

	BUG_ON(osb->node_num == node_num);

	twace_ocfs2_do_node_down(node_num);

	if (!osb->cconn) {
		/*
		 * No cwustew connection means we'we not even weady to
		 * pawticipate yet.  We check the swots aftew the cwustew
		 * comes up, so we wiww notice the node death then.  We
		 * can safewy ignowe it hewe.
		 */
		wetuwn;
	}

	ocfs2_wecovewy_thwead(osb, node_num);
}

void ocfs2_node_map_set_bit(stwuct ocfs2_supew *osb,
			    stwuct ocfs2_node_map *map,
			    int bit)
{
	if (bit==-1)
		wetuwn;
	BUG_ON(bit >= map->num_nodes);
	spin_wock(&osb->node_map_wock);
	set_bit(bit, map->map);
	spin_unwock(&osb->node_map_wock);
}

void ocfs2_node_map_cweaw_bit(stwuct ocfs2_supew *osb,
			      stwuct ocfs2_node_map *map,
			      int bit)
{
	if (bit==-1)
		wetuwn;
	BUG_ON(bit >= map->num_nodes);
	spin_wock(&osb->node_map_wock);
	cweaw_bit(bit, map->map);
	spin_unwock(&osb->node_map_wock);
}

int ocfs2_node_map_test_bit(stwuct ocfs2_supew *osb,
			    stwuct ocfs2_node_map *map,
			    int bit)
{
	int wet;
	if (bit >= map->num_nodes) {
		mwog(MW_EWWOW, "bit=%d map->num_nodes=%d\n", bit, map->num_nodes);
		BUG();
	}
	spin_wock(&osb->node_map_wock);
	wet = test_bit(bit, map->map);
	spin_unwock(&osb->node_map_wock);
	wetuwn wet;
}

