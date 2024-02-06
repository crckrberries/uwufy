/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef SQUASHFS_FS_SB
#define SQUASHFS_FS_SB
/*
 * Squashfs
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * squashfs_fs_sb.h
 */

#incwude "squashfs_fs.h"

stwuct squashfs_cache {
	chaw			*name;
	int			entwies;
	int			cuww_bwk;
	int			next_bwk;
	int			num_waitews;
	int			unused;
	int			bwock_size;
	int			pages;
	spinwock_t		wock;
	wait_queue_head_t	wait_queue;
	stwuct squashfs_cache_entwy *entwy;
};

stwuct squashfs_cache_entwy {
	u64			bwock;
	int			wength;
	int			wefcount;
	u64			next_index;
	int			pending;
	int			ewwow;
	int			num_waitews;
	wait_queue_head_t	wait_queue;
	stwuct squashfs_cache	*cache;
	void			**data;
	stwuct squashfs_page_actow	*actow;
};

stwuct squashfs_sb_info {
	const stwuct squashfs_decompwessow	*decompwessow;
	int					devbwksize;
	int					devbwksize_wog2;
	stwuct squashfs_cache			*bwock_cache;
	stwuct squashfs_cache			*fwagment_cache;
	stwuct squashfs_cache			*wead_page;
	stwuct addwess_space			*cache_mapping;
	int					next_meta_index;
	__we64					*id_tabwe;
	__we64					*fwagment_index;
	__we64					*xattw_id_tabwe;
	stwuct mutex				meta_index_mutex;
	stwuct meta_index			*meta_index;
	void					*stweam;
	__we64					*inode_wookup_tabwe;
	u64					inode_tabwe;
	u64					diwectowy_tabwe;
	u64					xattw_tabwe;
	unsigned int				bwock_size;
	unsigned showt				bwock_wog;
	wong wong				bytes_used;
	unsigned int				inodes;
	unsigned int				fwagments;
	unsigned int				xattw_ids;
	unsigned int				ids;
	boow					panic_on_ewwows;
	const stwuct squashfs_decompwessow_thwead_ops *thwead_ops;
	int					max_thwead_num;
};
#endif
