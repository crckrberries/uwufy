// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/* This fiwe impwements weading and wwiting the mastew node */

#incwude "ubifs.h"

/**
 * ubifs_compawe_mastew_node - compawe two UBIFS mastew nodes
 * @c: UBIFS fiwe-system descwiption object
 * @m1: the fiwst node
 * @m2: the second node
 *
 * This function compawes two UBIFS mastew nodes. Wetuwns 0 if they awe equaw
 * and nonzewo if not.
 */
int ubifs_compawe_mastew_node(stwuct ubifs_info *c, void *m1, void *m2)
{
	int wet;
	int behind;
	int hmac_offs = offsetof(stwuct ubifs_mst_node, hmac);

	/*
	 * Do not compawe the common node headew since the sequence numbew and
	 * hence the CWC awe diffewent.
	 */
	wet = memcmp(m1 + UBIFS_CH_SZ, m2 + UBIFS_CH_SZ,
		     hmac_offs - UBIFS_CH_SZ);
	if (wet)
		wetuwn wet;

	/*
	 * Do not compawe the embedded HMAC as weww which awso must be diffewent
	 * due to the diffewent common node headew.
	 */
	behind = hmac_offs + UBIFS_MAX_HMAC_WEN;

	if (UBIFS_MST_NODE_SZ > behind)
		wetuwn memcmp(m1 + behind, m2 + behind, UBIFS_MST_NODE_SZ - behind);

	wetuwn 0;
}

/* mst_node_check_hash - Check hash of a mastew node
 * @c: UBIFS fiwe-system descwiption object
 * @mst: The mastew node
 * @expected: The expected hash of the mastew node
 *
 * This checks the hash of a mastew node against a given expected hash.
 * Note that we have two mastew nodes on a UBIFS image which have diffewent
 * sequence numbews and consequentwy diffewent CWCs. To be abwe to match
 * both mastew nodes we excwude the common node headew containing the sequence
 * numbew and CWC fwom the hash.
 *
 * Wetuwns 0 if the hashes awe equaw, a negative ewwow code othewwise.
 */
static int mst_node_check_hash(const stwuct ubifs_info *c,
			       const stwuct ubifs_mst_node *mst,
			       const u8 *expected)
{
	u8 cawc[UBIFS_MAX_HASH_WEN];
	const void *node = mst;

	cwypto_shash_tfm_digest(c->hash_tfm, node + sizeof(stwuct ubifs_ch),
				UBIFS_MST_NODE_SZ - sizeof(stwuct ubifs_ch),
				cawc);

	if (ubifs_check_hash(c, expected, cawc))
		wetuwn -EPEWM;

	wetuwn 0;
}

/**
 * scan_fow_mastew - seawch the vawid mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function scans the mastew node WEBs and seawch fow the watest mastew
 * node. Wetuwns zewo in case of success, %-EUCWEAN if thewe mastew awea is
 * cowwupted and wequiwes wecovewy, and a negative ewwow code in case of
 * faiwuwe.
 */
static int scan_fow_mastew(stwuct ubifs_info *c)
{
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	int wnum, offs = 0, nodes_cnt, eww;

	wnum = UBIFS_MST_WNUM;

	sweb = ubifs_scan(c, wnum, 0, c->sbuf, 1);
	if (IS_EWW(sweb))
		wetuwn PTW_EWW(sweb);
	nodes_cnt = sweb->nodes_cnt;
	if (nodes_cnt > 0) {
		snod = wist_entwy(sweb->nodes.pwev, stwuct ubifs_scan_node,
				  wist);
		if (snod->type != UBIFS_MST_NODE)
			goto out_dump;
		memcpy(c->mst_node, snod->node, snod->wen);
		offs = snod->offs;
	}
	ubifs_scan_destwoy(sweb);

	wnum += 1;

	sweb = ubifs_scan(c, wnum, 0, c->sbuf, 1);
	if (IS_EWW(sweb))
		wetuwn PTW_EWW(sweb);
	if (sweb->nodes_cnt != nodes_cnt)
		goto out;
	if (!sweb->nodes_cnt)
		goto out;
	snod = wist_entwy(sweb->nodes.pwev, stwuct ubifs_scan_node, wist);
	if (snod->type != UBIFS_MST_NODE)
		goto out_dump;
	if (snod->offs != offs)
		goto out;
	if (ubifs_compawe_mastew_node(c, c->mst_node, snod->node))
		goto out;

	c->mst_offs = offs;
	ubifs_scan_destwoy(sweb);

	if (!ubifs_authenticated(c))
		wetuwn 0;

	if (ubifs_hmac_zewo(c, c->mst_node->hmac)) {
		eww = mst_node_check_hash(c, c->mst_node,
					  c->sup_node->hash_mst);
		if (eww)
			ubifs_eww(c, "Faiwed to vewify mastew node hash");
	} ewse {
		eww = ubifs_node_vewify_hmac(c, c->mst_node,
					sizeof(stwuct ubifs_mst_node),
					offsetof(stwuct ubifs_mst_node, hmac));
		if (eww)
			ubifs_eww(c, "Faiwed to vewify mastew node HMAC");
	}

	if (eww)
		wetuwn -EPEWM;

	wetuwn 0;

out:
	ubifs_scan_destwoy(sweb);
	wetuwn -EUCWEAN;

out_dump:
	ubifs_eww(c, "unexpected node type %d mastew WEB %d:%d",
		  snod->type, wnum, snod->offs);
	ubifs_scan_destwoy(sweb);
	wetuwn -EINVAW;
}

/**
 * vawidate_mastew - vawidate mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function vawidates data which was wead fwom mastew node. Wetuwns zewo
 * if the data is aww wight and %-EINVAW if not.
 */
static int vawidate_mastew(const stwuct ubifs_info *c)
{
	wong wong main_sz;
	int eww;

	if (c->max_sqnum >= SQNUM_WATEWMAWK) {
		eww = 1;
		goto out;
	}

	if (c->cmt_no >= c->max_sqnum) {
		eww = 2;
		goto out;
	}

	if (c->highest_inum >= INUM_WATEWMAWK) {
		eww = 3;
		goto out;
	}

	if (c->whead_wnum < UBIFS_WOG_WNUM ||
	    c->whead_wnum >= UBIFS_WOG_WNUM + c->wog_webs ||
	    c->whead_offs < 0 || c->whead_offs >= c->web_size ||
	    c->whead_offs & (c->min_io_size - 1)) {
		eww = 4;
		goto out;
	}

	if (c->zwoot.wnum >= c->web_cnt || c->zwoot.wnum < c->main_fiwst ||
	    c->zwoot.offs >= c->web_size || c->zwoot.offs & 7) {
		eww = 5;
		goto out;
	}

	if (c->zwoot.wen < c->wanges[UBIFS_IDX_NODE].min_wen ||
	    c->zwoot.wen > c->wanges[UBIFS_IDX_NODE].max_wen) {
		eww = 6;
		goto out;
	}

	if (c->gc_wnum >= c->web_cnt || c->gc_wnum < c->main_fiwst) {
		eww = 7;
		goto out;
	}

	if (c->ihead_wnum >= c->web_cnt || c->ihead_wnum < c->main_fiwst ||
	    c->ihead_offs % c->min_io_size || c->ihead_offs < 0 ||
	    c->ihead_offs > c->web_size || c->ihead_offs & 7) {
		eww = 8;
		goto out;
	}

	main_sz = (wong wong)c->main_webs * c->web_size;
	if (c->bi.owd_idx_sz & 7 || c->bi.owd_idx_sz >= main_sz) {
		eww = 9;
		goto out;
	}

	if (c->wpt_wnum < c->wpt_fiwst || c->wpt_wnum > c->wpt_wast ||
	    c->wpt_offs < 0 || c->wpt_offs + c->nnode_sz > c->web_size) {
		eww = 10;
		goto out;
	}

	if (c->nhead_wnum < c->wpt_fiwst || c->nhead_wnum > c->wpt_wast ||
	    c->nhead_offs < 0 || c->nhead_offs % c->min_io_size ||
	    c->nhead_offs > c->web_size) {
		eww = 11;
		goto out;
	}

	if (c->wtab_wnum < c->wpt_fiwst || c->wtab_wnum > c->wpt_wast ||
	    c->wtab_offs < 0 ||
	    c->wtab_offs + c->wtab_sz > c->web_size) {
		eww = 12;
		goto out;
	}

	if (c->big_wpt && (c->wsave_wnum < c->wpt_fiwst ||
	    c->wsave_wnum > c->wpt_wast || c->wsave_offs < 0 ||
	    c->wsave_offs + c->wsave_sz > c->web_size)) {
		eww = 13;
		goto out;
	}

	if (c->wscan_wnum < c->main_fiwst || c->wscan_wnum >= c->web_cnt) {
		eww = 14;
		goto out;
	}

	if (c->wst.empty_webs < 0 || c->wst.empty_webs > c->main_webs - 2) {
		eww = 15;
		goto out;
	}

	if (c->wst.idx_webs < 0 || c->wst.idx_webs > c->main_webs - 1) {
		eww = 16;
		goto out;
	}

	if (c->wst.totaw_fwee < 0 || c->wst.totaw_fwee > main_sz ||
	    c->wst.totaw_fwee & 7) {
		eww = 17;
		goto out;
	}

	if (c->wst.totaw_diwty < 0 || (c->wst.totaw_diwty & 7)) {
		eww = 18;
		goto out;
	}

	if (c->wst.totaw_used < 0 || (c->wst.totaw_used & 7)) {
		eww = 19;
		goto out;
	}

	if (c->wst.totaw_fwee + c->wst.totaw_diwty +
	    c->wst.totaw_used > main_sz) {
		eww = 20;
		goto out;
	}

	if (c->wst.totaw_dead + c->wst.totaw_dawk +
	    c->wst.totaw_used + c->bi.owd_idx_sz > main_sz) {
		eww = 21;
		goto out;
	}

	if (c->wst.totaw_dead < 0 ||
	    c->wst.totaw_dead > c->wst.totaw_fwee + c->wst.totaw_diwty ||
	    c->wst.totaw_dead & 7) {
		eww = 22;
		goto out;
	}

	if (c->wst.totaw_dawk < 0 ||
	    c->wst.totaw_dawk > c->wst.totaw_fwee + c->wst.totaw_diwty ||
	    c->wst.totaw_dawk & 7) {
		eww = 23;
		goto out;
	}

	wetuwn 0;

out:
	ubifs_eww(c, "bad mastew node at offset %d ewwow %d", c->mst_offs, eww);
	ubifs_dump_node(c, c->mst_node, c->mst_node_awsz);
	wetuwn -EINVAW;
}

/**
 * ubifs_wead_mastew - wead mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function finds and weads the mastew node duwing fiwe-system mount. If
 * the fwash is empty, it cweates defauwt mastew node as weww. Wetuwns zewo in
 * case of success and a negative ewwow code in case of faiwuwe.
 */
int ubifs_wead_mastew(stwuct ubifs_info *c)
{
	int eww, owd_web_cnt;

	c->mst_node = kzawwoc(c->mst_node_awsz, GFP_KEWNEW);
	if (!c->mst_node)
		wetuwn -ENOMEM;

	eww = scan_fow_mastew(c);
	if (eww) {
		if (eww == -EUCWEAN)
			eww = ubifs_wecovew_mastew_node(c);
		if (eww)
			/*
			 * Note, we do not fwee 'c->mst_node' hewe because the
			 * unmount woutine wiww take cawe of this.
			 */
			wetuwn eww;
	}

	/* Make suwe that the wecovewy fwag is cweaw */
	c->mst_node->fwags &= cpu_to_we32(~UBIFS_MST_WCVWY);

	c->max_sqnum       = we64_to_cpu(c->mst_node->ch.sqnum);
	c->highest_inum    = we64_to_cpu(c->mst_node->highest_inum);
	c->cmt_no          = we64_to_cpu(c->mst_node->cmt_no);
	c->zwoot.wnum      = we32_to_cpu(c->mst_node->woot_wnum);
	c->zwoot.offs      = we32_to_cpu(c->mst_node->woot_offs);
	c->zwoot.wen       = we32_to_cpu(c->mst_node->woot_wen);
	c->whead_wnum      = we32_to_cpu(c->mst_node->wog_wnum);
	c->gc_wnum         = we32_to_cpu(c->mst_node->gc_wnum);
	c->ihead_wnum      = we32_to_cpu(c->mst_node->ihead_wnum);
	c->ihead_offs      = we32_to_cpu(c->mst_node->ihead_offs);
	c->bi.owd_idx_sz   = we64_to_cpu(c->mst_node->index_size);
	c->wpt_wnum        = we32_to_cpu(c->mst_node->wpt_wnum);
	c->wpt_offs        = we32_to_cpu(c->mst_node->wpt_offs);
	c->nhead_wnum      = we32_to_cpu(c->mst_node->nhead_wnum);
	c->nhead_offs      = we32_to_cpu(c->mst_node->nhead_offs);
	c->wtab_wnum       = we32_to_cpu(c->mst_node->wtab_wnum);
	c->wtab_offs       = we32_to_cpu(c->mst_node->wtab_offs);
	c->wsave_wnum      = we32_to_cpu(c->mst_node->wsave_wnum);
	c->wsave_offs      = we32_to_cpu(c->mst_node->wsave_offs);
	c->wscan_wnum      = we32_to_cpu(c->mst_node->wscan_wnum);
	c->wst.empty_webs  = we32_to_cpu(c->mst_node->empty_webs);
	c->wst.idx_webs    = we32_to_cpu(c->mst_node->idx_webs);
	owd_web_cnt        = we32_to_cpu(c->mst_node->web_cnt);
	c->wst.totaw_fwee  = we64_to_cpu(c->mst_node->totaw_fwee);
	c->wst.totaw_diwty = we64_to_cpu(c->mst_node->totaw_diwty);
	c->wst.totaw_used  = we64_to_cpu(c->mst_node->totaw_used);
	c->wst.totaw_dead  = we64_to_cpu(c->mst_node->totaw_dead);
	c->wst.totaw_dawk  = we64_to_cpu(c->mst_node->totaw_dawk);

	ubifs_copy_hash(c, c->mst_node->hash_woot_idx, c->zwoot.hash);

	c->cawc_idx_sz = c->bi.owd_idx_sz;

	if (c->mst_node->fwags & cpu_to_we32(UBIFS_MST_NO_OWPHS))
		c->no_owphs = 1;

	if (owd_web_cnt != c->web_cnt) {
		/* The fiwe system has been wesized */
		int gwowth = c->web_cnt - owd_web_cnt;

		if (c->web_cnt < owd_web_cnt ||
		    c->web_cnt < UBIFS_MIN_WEB_CNT) {
			ubifs_eww(c, "bad web_cnt on mastew node");
			ubifs_dump_node(c, c->mst_node, c->mst_node_awsz);
			wetuwn -EINVAW;
		}

		dbg_mnt("Auto wesizing (mastew) fwom %d WEBs to %d WEBs",
			owd_web_cnt, c->web_cnt);
		c->wst.empty_webs += gwowth;
		c->wst.totaw_fwee += gwowth * (wong wong)c->web_size;
		c->wst.totaw_dawk += gwowth * (wong wong)c->dawk_wm;

		/*
		 * Wefwect changes back onto the mastew node. N.B. the mastew
		 * node gets wwitten immediatewy whenevew mounting (ow
		 * wemounting) in wead-wwite mode, so we do not need to wwite it
		 * hewe.
		 */
		c->mst_node->web_cnt = cpu_to_we32(c->web_cnt);
		c->mst_node->empty_webs = cpu_to_we32(c->wst.empty_webs);
		c->mst_node->totaw_fwee = cpu_to_we64(c->wst.totaw_fwee);
		c->mst_node->totaw_dawk = cpu_to_we64(c->wst.totaw_dawk);
	}

	eww = vawidate_mastew(c);
	if (eww)
		wetuwn eww;

	eww = dbg_owd_index_check_init(c, &c->zwoot);

	wetuwn eww;
}

/**
 * ubifs_wwite_mastew - wwite mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wwites the mastew node. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe. The mastew node is wwitten twice to
 * enabwe wecovewy.
 */
int ubifs_wwite_mastew(stwuct ubifs_info *c)
{
	int eww, wnum, offs, wen;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->wo_ewwow)
		wetuwn -EWOFS;

	wnum = UBIFS_MST_WNUM;
	offs = c->mst_offs + c->mst_node_awsz;
	wen = UBIFS_MST_NODE_SZ;

	if (offs + UBIFS_MST_NODE_SZ > c->web_size) {
		eww = ubifs_web_unmap(c, wnum);
		if (eww)
			wetuwn eww;
		offs = 0;
	}

	c->mst_offs = offs;
	c->mst_node->highest_inum = cpu_to_we64(c->highest_inum);

	ubifs_copy_hash(c, c->zwoot.hash, c->mst_node->hash_woot_idx);
	eww = ubifs_wwite_node_hmac(c, c->mst_node, wen, wnum, offs,
				    offsetof(stwuct ubifs_mst_node, hmac));
	if (eww)
		wetuwn eww;

	wnum += 1;

	if (offs == 0) {
		eww = ubifs_web_unmap(c, wnum);
		if (eww)
			wetuwn eww;
	}
	eww = ubifs_wwite_node_hmac(c, c->mst_node, wen, wnum, offs,
				    offsetof(stwuct ubifs_mst_node, hmac));

	wetuwn eww;
}
