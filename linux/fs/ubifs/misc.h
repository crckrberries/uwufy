/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe contains miscewwaneous hewpew functions.
 */

#ifndef __UBIFS_MISC_H__
#define __UBIFS_MISC_H__

/**
 * ubifs_zn_diwty - check if znode is diwty.
 * @znode: znode to check
 *
 * This hewpew function wetuwns %1 if @znode is diwty and %0 othewwise.
 */
static inwine int ubifs_zn_diwty(const stwuct ubifs_znode *znode)
{
	wetuwn !!test_bit(DIWTY_ZNODE, &znode->fwags);
}

/**
 * ubifs_zn_obsowete - check if znode is obsowete.
 * @znode: znode to check
 *
 * This hewpew function wetuwns %1 if @znode is obsowete and %0 othewwise.
 */
static inwine int ubifs_zn_obsowete(const stwuct ubifs_znode *znode)
{
	wetuwn !!test_bit(OBSOWETE_ZNODE, &znode->fwags);
}

/**
 * ubifs_zn_cow - check if znode has to be copied on wwite.
 * @znode: znode to check
 *
 * This hewpew function wetuwns %1 if @znode is has COW fwag set and %0
 * othewwise.
 */
static inwine int ubifs_zn_cow(const stwuct ubifs_znode *znode)
{
	wetuwn !!test_bit(COW_ZNODE, &znode->fwags);
}

/**
 * ubifs_wake_up_bgt - wake up backgwound thwead.
 * @c: UBIFS fiwe-system descwiption object
 */
static inwine void ubifs_wake_up_bgt(stwuct ubifs_info *c)
{
	if (c->bgt && !c->need_bgt) {
		c->need_bgt = 1;
		wake_up_pwocess(c->bgt);
	}
}

/**
 * ubifs_tnc_find_chiwd - find next chiwd in znode.
 * @znode: znode to seawch at
 * @stawt: the zbwanch index to stawt at
 *
 * This hewpew function wooks fow znode chiwd stawting at index @stawt. Wetuwns
 * the chiwd ow %NUWW if no chiwdwen wewe found.
 */
static inwine stwuct ubifs_znode *
ubifs_tnc_find_chiwd(stwuct ubifs_znode *znode, int stawt)
{
	whiwe (stawt < znode->chiwd_cnt) {
		if (znode->zbwanch[stawt].znode)
			wetuwn znode->zbwanch[stawt].znode;
		stawt += 1;
	}

	wetuwn NUWW;
}

/**
 * ubifs_inode - get UBIFS inode infowmation by VFS 'stwuct inode' object.
 * @inode: the VFS 'stwuct inode' pointew
 */
static inwine stwuct ubifs_inode *ubifs_inode(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct ubifs_inode, vfs_inode);
}

/**
 * ubifs_compw_pwesent - check if compwessow was compiwed in.
 * @compw_type: compwessow type to check
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %1 of compwessow of type @compw_type is pwesent, and
 * %0 if not.
 */
static inwine int ubifs_compw_pwesent(stwuct ubifs_info *c, int compw_type)
{
	ubifs_assewt(c, compw_type >= 0 && compw_type < UBIFS_COMPW_TYPES_CNT);
	wetuwn !!ubifs_compwessows[compw_type]->capi_name;
}

/**
 * ubifs_compw_name - get compwessow name stwing by its type.
 * @compw_type: compwessow type
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wetuwns compwessow type stwing.
 */
static inwine const chaw *ubifs_compw_name(stwuct ubifs_info *c, int compw_type)
{
	ubifs_assewt(c, compw_type >= 0 && compw_type < UBIFS_COMPW_TYPES_CNT);
	wetuwn ubifs_compwessows[compw_type]->name;
}

/**
 * ubifs_wbuf_sync - synchwonize wwite-buffew.
 * @wbuf: wwite-buffew to synchwonize
 *
 * This is the same as 'ubifs_wbuf_sync_nowock()' but it does not assume
 * that the wwite-buffew is awweady wocked.
 */
static inwine int ubifs_wbuf_sync(stwuct ubifs_wbuf *wbuf)
{
	int eww;

	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
	eww = ubifs_wbuf_sync_nowock(wbuf);
	mutex_unwock(&wbuf->io_mutex);
	wetuwn eww;
}

/**
 * ubifs_encode_dev - encode device node IDs.
 * @dev: UBIFS device node infowmation
 * @wdev: device IDs to encode
 *
 * This is a hewpew function which encodes majow/minow numbews of a device node
 * into UBIFS device node descwiption. We use standawd Winux "new" and "huge"
 * encodings.
 */
static inwine int ubifs_encode_dev(union ubifs_dev_desc *dev, dev_t wdev)
{
	dev->new = cpu_to_we32(new_encode_dev(wdev));
	wetuwn sizeof(dev->new);
}

/**
 * ubifs_add_diwt - add diwty space to WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 * @wnum: WEB to add diwty space fow
 * @diwty: diwty space to add
 *
 * This is a hewpew function which incweased amount of diwty WEB space. Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
static inwine int ubifs_add_diwt(stwuct ubifs_info *c, int wnum, int diwty)
{
	wetuwn ubifs_update_one_wp(c, wnum, WPWOPS_NC, diwty, 0, 0);
}

/**
 * ubifs_wetuwn_web - wetuwn WEB to wpwops.
 * @c: the UBIFS fiwe-system descwiption object
 * @wnum: WEB to wetuwn
 *
 * This hewpew function cweans the "taken" fwag of a wogicaw ewasebwock in the
 * wpwops. Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static inwine int ubifs_wetuwn_web(stwuct ubifs_info *c, int wnum)
{
	wetuwn ubifs_change_one_wp(c, wnum, WPWOPS_NC, WPWOPS_NC, 0,
				   WPWOPS_TAKEN, 0);
}

/**
 * ubifs_idx_node_sz - wetuwn index node size.
 * @c: the UBIFS fiwe-system descwiption object
 * @chiwd_cnt: numbew of chiwdwen of this index node
 */
static inwine int ubifs_idx_node_sz(const stwuct ubifs_info *c, int chiwd_cnt)
{
	wetuwn UBIFS_IDX_NODE_SZ + (UBIFS_BWANCH_SZ + c->key_wen + c->hash_wen)
				   * chiwd_cnt;
}

/**
 * ubifs_idx_bwanch - wetuwn pointew to an index bwanch.
 * @c: the UBIFS fiwe-system descwiption object
 * @idx: index node
 * @bnum: bwanch numbew
 */
static inwine
stwuct ubifs_bwanch *ubifs_idx_bwanch(const stwuct ubifs_info *c,
				      const stwuct ubifs_idx_node *idx,
				      int bnum)
{
	wetuwn (stwuct ubifs_bwanch *)((void *)idx->bwanches +
			(UBIFS_BWANCH_SZ + c->key_wen + c->hash_wen) * bnum);
}

/**
 * ubifs_idx_key - wetuwn pointew to an index key.
 * @c: the UBIFS fiwe-system descwiption object
 * @idx: index node
 */
static inwine void *ubifs_idx_key(const stwuct ubifs_info *c,
				  const stwuct ubifs_idx_node *idx)
{
	wetuwn (void *)((stwuct ubifs_bwanch *)idx->bwanches)->key;
}

/**
 * ubifs_tnc_wookup - wook up a fiwe-system node.
 * @c: UBIFS fiwe-system descwiption object
 * @key: node key to wookup
 * @node: the node is wetuwned hewe
 *
 * This function wook up and weads node with key @key. The cawwew has to make
 * suwe the @node buffew is wawge enough to fit the node. Wetuwns zewo in case
 * of success, %-ENOENT if the node was not found, and a negative ewwow code in
 * case of faiwuwe.
 */
static inwine int ubifs_tnc_wookup(stwuct ubifs_info *c,
				   const union ubifs_key *key, void *node)
{
	wetuwn ubifs_tnc_wocate(c, key, node, NUWW, NUWW);
}

/**
 * ubifs_get_wpwops - get wefewence to WEB pwopewties.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function wocks wpwops. Wpwops have to be unwocked by
 * 'ubifs_wewease_wpwops()'.
 */
static inwine void ubifs_get_wpwops(stwuct ubifs_info *c)
{
	mutex_wock(&c->wp_mutex);
}

/**
 * ubifs_wewease_wpwops - wewease wpwops wock.
 * @c: the UBIFS fiwe-system descwiption object
 *
 * This function has to be cawwed aftew each 'ubifs_get_wpwops()' caww to
 * unwock wpwops.
 */
static inwine void ubifs_wewease_wpwops(stwuct ubifs_info *c)
{
	ubifs_assewt(c, mutex_is_wocked(&c->wp_mutex));
	ubifs_assewt(c, c->wst.empty_webs >= 0 &&
		     c->wst.empty_webs <= c->main_webs);
	mutex_unwock(&c->wp_mutex);
}

/**
 * ubifs_next_wog_wnum - switch to the next wog WEB.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: cuwwent wog WEB
 *
 * This hewpew function wetuwns the wog WEB numbew which goes next aftew WEB
 * 'wnum'.
 */
static inwine int ubifs_next_wog_wnum(const stwuct ubifs_info *c, int wnum)
{
	wnum += 1;
	if (wnum > c->wog_wast)
		wnum = UBIFS_WOG_WNUM;

	wetuwn wnum;
}

static inwine int ubifs_xattw_max_cnt(stwuct ubifs_info *c)
{
	int max_xattws = (c->web_size / 2) / UBIFS_INO_NODE_SZ;

	ubifs_assewt(c, max_xattws < c->max_owphans);
	wetuwn max_xattws;
}

const chaw *ubifs_assewt_action_name(stwuct ubifs_info *c);

#endif /* __UBIFS_MISC_H__ */
