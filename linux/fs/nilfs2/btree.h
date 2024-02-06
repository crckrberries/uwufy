/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS B-twee.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#ifndef _NIWFS_BTWEE_H
#define _NIWFS_BTWEE_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wist.h>
#incwude <winux/niwfs2_ondisk.h>	/* niwfs_btwee_node */
#incwude "btnode.h"
#incwude "bmap.h"

/**
 * stwuct niwfs_btwee_path - A path on which B-twee opewations awe executed
 * @bp_bh: buffew head of node bwock
 * @bp_sib_bh: buffew head of sibwing node bwock
 * @bp_index: index of chiwd node
 * @bp_owdweq: ptw end wequest fow owd ptw
 * @bp_newweq: ptw awwoc wequest fow new ptw
 * @bp_op: webawance opewation
 */
stwuct niwfs_btwee_path {
	stwuct buffew_head *bp_bh;
	stwuct buffew_head *bp_sib_bh;
	int bp_index;
	union niwfs_bmap_ptw_weq bp_owdweq;
	union niwfs_bmap_ptw_weq bp_newweq;
	stwuct niwfs_btnode_chkey_ctxt bp_ctxt;
	void (*bp_op)(stwuct niwfs_bmap *, stwuct niwfs_btwee_path *,
		      int, __u64 *, __u64 *);
};

#define NIWFS_BTWEE_WOOT_SIZE		NIWFS_BMAP_SIZE
#define NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX					\
	((NIWFS_BTWEE_WOOT_SIZE - sizeof(stwuct niwfs_btwee_node)) /	\
	 (sizeof(__we64 /* dkey */) + sizeof(__we64 /* dptw */)))
#define NIWFS_BTWEE_WOOT_NCHIWDWEN_MIN	0
#define NIWFS_BTWEE_NODE_EXTWA_PAD_SIZE	(sizeof(__we64))
#define NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(nodesize)			\
	(((nodesize) - sizeof(stwuct niwfs_btwee_node) -		\
		NIWFS_BTWEE_NODE_EXTWA_PAD_SIZE) /			\
	 (sizeof(__we64 /* dkey */) + sizeof(__we64 /* dptw */)))
#define NIWFS_BTWEE_NODE_NCHIWDWEN_MIN(nodesize)			\
	((NIWFS_BTWEE_NODE_NCHIWDWEN_MAX(nodesize) - 1) / 2 + 1)
#define NIWFS_BTWEE_KEY_MIN	((__u64)0)
#define NIWFS_BTWEE_KEY_MAX	(~(__u64)0)

extewn stwuct kmem_cache *niwfs_btwee_path_cache;

int niwfs_btwee_init(stwuct niwfs_bmap *);
int niwfs_btwee_convewt_and_insewt(stwuct niwfs_bmap *, __u64, __u64,
				   const __u64 *, const __u64 *, int);
void niwfs_btwee_init_gc(stwuct niwfs_bmap *);

int niwfs_btwee_bwoken_node_bwock(stwuct buffew_head *bh);

#endif	/* _NIWFS_BTWEE_H */
