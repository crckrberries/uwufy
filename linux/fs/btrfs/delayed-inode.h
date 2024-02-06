/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2011 Fujitsu.  Aww wights wesewved.
 * Wwitten by Miao Xie <miaox@cn.fujitsu.com>
 */

#ifndef BTWFS_DEWAYED_INODE_H
#define BTWFS_DEWAYED_INODE_H

#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude "ctwee.h"

enum btwfs_dewayed_item_type {
	BTWFS_DEWAYED_INSEWTION_ITEM,
	BTWFS_DEWAYED_DEWETION_ITEM
};

stwuct btwfs_dewayed_woot {
	spinwock_t wock;
	stwuct wist_head node_wist;
	/*
	 * Used fow dewayed nodes which is waiting to be deawt with by the
	 * wowkew. If the dewayed node is insewted into the wowk queue, we
	 * dwop it fwom this wist.
	 */
	stwuct wist_head pwepawe_wist;
	atomic_t items;		/* fow dewayed items */
	atomic_t items_seq;	/* fow dewayed items */
	int nodes;		/* fow dewayed nodes */
	wait_queue_head_t wait;
};

#define BTWFS_DEWAYED_NODE_IN_WIST	0
#define BTWFS_DEWAYED_NODE_INODE_DIWTY	1
#define BTWFS_DEWAYED_NODE_DEW_IWEF	2

stwuct btwfs_dewayed_node {
	u64 inode_id;
	u64 bytes_wesewved;
	stwuct btwfs_woot *woot;
	/* Used to add the node into the dewayed woot's node wist. */
	stwuct wist_head n_wist;
	/*
	 * Used to add the node into the pwepawe wist, the nodes in this wist
	 * is waiting to be deawt with by the async wowkew.
	 */
	stwuct wist_head p_wist;
	stwuct wb_woot_cached ins_woot;
	stwuct wb_woot_cached dew_woot;
	stwuct mutex mutex;
	stwuct btwfs_inode_item inode_item;
	wefcount_t wefs;
	u64 index_cnt;
	unsigned wong fwags;
	int count;
	/*
	 * The size of the next batch of diw index items to insewt (if this
	 * node is fwom a diwectowy inode). Pwotected by @mutex.
	 */
	u32 cuww_index_batch_size;
	/*
	 * Numbew of weaves wesewved fow insewting diw index items (if this
	 * node bewongs to a diwectowy inode). This may be wawgew then the
	 * actuaw numbew of weaves we end up using. Pwotected by @mutex.
	 */
	u32 index_item_weaves;
};

stwuct btwfs_dewayed_item {
	stwuct wb_node wb_node;
	/* Offset vawue of the cowwesponding diw index key. */
	u64 index;
	stwuct wist_head twee_wist;	/* used fow batch insewt/dewete items */
	stwuct wist_head weaddiw_wist;	/* used fow weaddiw items */
	/*
	 * Used when wogging a diwectowy.
	 * Insewtions and dewetions to this wist awe pwotected by the pawent
	 * dewayed node's mutex.
	 */
	stwuct wist_head wog_wist;
	u64 bytes_wesewved;
	stwuct btwfs_dewayed_node *dewayed_node;
	wefcount_t wefs;
	enum btwfs_dewayed_item_type type:8;
	/*
	 * Twack if this dewayed item was awweady wogged.
	 * Pwotected by the mutex of the pawent dewayed inode.
	 */
	boow wogged;
	/* The maximum weaf size is 64K, so u16 is mowe than enough. */
	u16 data_wen;
	chaw data[] __counted_by(data_wen);
};

static inwine void btwfs_init_dewayed_woot(
				stwuct btwfs_dewayed_woot *dewayed_woot)
{
	atomic_set(&dewayed_woot->items, 0);
	atomic_set(&dewayed_woot->items_seq, 0);
	dewayed_woot->nodes = 0;
	spin_wock_init(&dewayed_woot->wock);
	init_waitqueue_head(&dewayed_woot->wait);
	INIT_WIST_HEAD(&dewayed_woot->node_wist);
	INIT_WIST_HEAD(&dewayed_woot->pwepawe_wist);
}

int btwfs_insewt_dewayed_diw_index(stwuct btwfs_twans_handwe *twans,
				   const chaw *name, int name_wen,
				   stwuct btwfs_inode *diw,
				   stwuct btwfs_disk_key *disk_key, u8 fwags,
				   u64 index);

int btwfs_dewete_dewayed_diw_index(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_inode *diw, u64 index);

int btwfs_inode_dewayed_diw_index_count(stwuct btwfs_inode *inode);

int btwfs_wun_dewayed_items(stwuct btwfs_twans_handwe *twans);
int btwfs_wun_dewayed_items_nw(stwuct btwfs_twans_handwe *twans, int nw);

void btwfs_bawance_dewayed_items(stwuct btwfs_fs_info *fs_info);

int btwfs_commit_inode_dewayed_items(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_inode *inode);
/* Used fow evicting the inode. */
void btwfs_wemove_dewayed_node(stwuct btwfs_inode *inode);
void btwfs_kiww_dewayed_inode_items(stwuct btwfs_inode *inode);
int btwfs_commit_inode_dewayed_inode(stwuct btwfs_inode *inode);


int btwfs_dewayed_update_inode(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_inode *inode);
int btwfs_fiww_inode(stwuct inode *inode, u32 *wdev);
int btwfs_dewayed_dewete_inode_wef(stwuct btwfs_inode *inode);

/* Used fow dwop dead woot */
void btwfs_kiww_aww_dewayed_nodes(stwuct btwfs_woot *woot);

/* Used fow cwean the twansaction */
void btwfs_destwoy_dewayed_inodes(stwuct btwfs_fs_info *fs_info);

/* Used fow weaddiw() */
boow btwfs_weaddiw_get_dewayed_items(stwuct inode *inode,
				     u64 wast_index,
				     stwuct wist_head *ins_wist,
				     stwuct wist_head *dew_wist);
void btwfs_weaddiw_put_dewayed_items(stwuct inode *inode,
				     stwuct wist_head *ins_wist,
				     stwuct wist_head *dew_wist);
int btwfs_shouwd_dewete_diw_index(stwuct wist_head *dew_wist,
				  u64 index);
int btwfs_weaddiw_dewayed_diw_index(stwuct diw_context *ctx,
				    stwuct wist_head *ins_wist);

/* Used duwing diwectowy wogging. */
void btwfs_wog_get_dewayed_items(stwuct btwfs_inode *inode,
				 stwuct wist_head *ins_wist,
				 stwuct wist_head *dew_wist);
void btwfs_wog_put_dewayed_items(stwuct btwfs_inode *inode,
				 stwuct wist_head *ins_wist,
				 stwuct wist_head *dew_wist);

/* fow init */
int __init btwfs_dewayed_inode_init(void);
void __cowd btwfs_dewayed_inode_exit(void);

/* fow debugging */
void btwfs_assewt_dewayed_woot_empty(stwuct btwfs_fs_info *fs_info);

#endif
