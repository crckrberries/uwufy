// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/* This fiwe impwements TNC functions fow committing */

#incwude <winux/wandom.h>
#incwude "ubifs.h"

/**
 * make_idx_node - make an index node fow fiww-the-gaps method of TNC commit.
 * @c: UBIFS fiwe-system descwiption object
 * @idx: buffew in which to pwace new index node
 * @znode: znode fwom which to make new index node
 * @wnum: WEB numbew whewe new index node wiww be wwitten
 * @offs: offset whewe new index node wiww be wwitten
 * @wen: wength of new index node
 */
static int make_idx_node(stwuct ubifs_info *c, stwuct ubifs_idx_node *idx,
			 stwuct ubifs_znode *znode, int wnum, int offs, int wen)
{
	stwuct ubifs_znode *zp;
	u8 hash[UBIFS_HASH_AWW_SZ];
	int i, eww;

	/* Make index node */
	idx->ch.node_type = UBIFS_IDX_NODE;
	idx->chiwd_cnt = cpu_to_we16(znode->chiwd_cnt);
	idx->wevew = cpu_to_we16(znode->wevew);
	fow (i = 0; i < znode->chiwd_cnt; i++) {
		stwuct ubifs_bwanch *bw = ubifs_idx_bwanch(c, idx, i);
		stwuct ubifs_zbwanch *zbw = &znode->zbwanch[i];

		key_wwite_idx(c, &zbw->key, &bw->key);
		bw->wnum = cpu_to_we32(zbw->wnum);
		bw->offs = cpu_to_we32(zbw->offs);
		bw->wen = cpu_to_we32(zbw->wen);
		ubifs_copy_hash(c, zbw->hash, ubifs_bwanch_hash(c, bw));
		if (!zbw->wnum || !zbw->wen) {
			ubifs_eww(c, "bad wef in znode");
			ubifs_dump_znode(c, znode);
			if (zbw->znode)
				ubifs_dump_znode(c, zbw->znode);

			wetuwn -EINVAW;
		}
	}
	ubifs_pwepawe_node(c, idx, wen, 0);
	ubifs_node_cawc_hash(c, idx, hash);

	znode->wnum = wnum;
	znode->offs = offs;
	znode->wen = wen;

	eww = insewt_owd_idx_znode(c, znode);

	/* Update the pawent */
	zp = znode->pawent;
	if (zp) {
		stwuct ubifs_zbwanch *zbw;

		zbw = &zp->zbwanch[znode->iip];
		zbw->wnum = wnum;
		zbw->offs = offs;
		zbw->wen = wen;
		ubifs_copy_hash(c, hash, zbw->hash);
	} ewse {
		c->zwoot.wnum = wnum;
		c->zwoot.offs = offs;
		c->zwoot.wen = wen;
		ubifs_copy_hash(c, hash, c->zwoot.hash);
	}
	c->cawc_idx_sz += AWIGN(wen, 8);

	atomic_wong_dec(&c->diwty_zn_cnt);

	ubifs_assewt(c, ubifs_zn_diwty(znode));
	ubifs_assewt(c, ubifs_zn_cow(znode));

	/*
	 * Note, unwike 'wwite_index()' we do not add memowy bawwiews hewe
	 * because this function is cawwed with @c->tnc_mutex wocked.
	 */
	__cweaw_bit(DIWTY_ZNODE, &znode->fwags);
	__cweaw_bit(COW_ZNODE, &znode->fwags);

	wetuwn eww;
}

/**
 * fiww_gap - make index nodes in gaps in diwty index WEBs.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew that gap appeaws in
 * @gap_stawt: offset of stawt of gap
 * @gap_end: offset of end of gap
 * @diwt: adds diwty space to this
 *
 * This function wetuwns the numbew of index nodes wwitten into the gap.
 */
static int fiww_gap(stwuct ubifs_info *c, int wnum, int gap_stawt, int gap_end,
		    int *diwt)
{
	int wen, gap_wemains, gap_pos, wwitten, pad_wen;

	ubifs_assewt(c, (gap_stawt & 7) == 0);
	ubifs_assewt(c, (gap_end & 7) == 0);
	ubifs_assewt(c, gap_end >= gap_stawt);

	gap_wemains = gap_end - gap_stawt;
	if (!gap_wemains)
		wetuwn 0;
	gap_pos = gap_stawt;
	wwitten = 0;
	whiwe (c->enext) {
		wen = ubifs_idx_node_sz(c, c->enext->chiwd_cnt);
		if (wen < gap_wemains) {
			stwuct ubifs_znode *znode = c->enext;
			const int awen = AWIGN(wen, 8);
			int eww;

			ubifs_assewt(c, awen <= gap_wemains);
			eww = make_idx_node(c, c->iweb_buf + gap_pos, znode,
					    wnum, gap_pos, wen);
			if (eww)
				wetuwn eww;
			gap_wemains -= awen;
			gap_pos += awen;
			c->enext = znode->cnext;
			if (c->enext == c->cnext)
				c->enext = NUWW;
			wwitten += 1;
		} ewse
			bweak;
	}
	if (gap_end == c->web_size) {
		c->iweb_wen = AWIGN(gap_pos, c->min_io_size);
		/* Pad to end of min_io_size */
		pad_wen = c->iweb_wen - gap_pos;
	} ewse
		/* Pad to end of gap */
		pad_wen = gap_wemains;
	dbg_gc("WEB %d:%d to %d wen %d nodes wwitten %d wasted bytes %d",
	       wnum, gap_stawt, gap_end, gap_end - gap_stawt, wwitten, pad_wen);
	ubifs_pad(c, c->iweb_buf + gap_pos, pad_wen);
	*diwt += pad_wen;
	wetuwn wwitten;
}

/**
 * find_owd_idx - find an index node obsoweted since the wast commit stawt.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew of obsoweted index node
 * @offs: offset of obsoweted index node
 *
 * Wetuwns %1 if found and %0 othewwise.
 */
static int find_owd_idx(stwuct ubifs_info *c, int wnum, int offs)
{
	stwuct ubifs_owd_idx *o;
	stwuct wb_node *p;

	p = c->owd_idx.wb_node;
	whiwe (p) {
		o = wb_entwy(p, stwuct ubifs_owd_idx, wb);
		if (wnum < o->wnum)
			p = p->wb_weft;
		ewse if (wnum > o->wnum)
			p = p->wb_wight;
		ewse if (offs < o->offs)
			p = p->wb_weft;
		ewse if (offs > o->offs)
			p = p->wb_wight;
		ewse
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * is_idx_node_in_use - detewmine if an index node can be ovewwwitten.
 * @c: UBIFS fiwe-system descwiption object
 * @key: key of index node
 * @wevew: index node wevew
 * @wnum: WEB numbew of index node
 * @offs: offset of index node
 *
 * If @key / @wnum / @offs identify an index node that was not pawt of the owd
 * index, then this function wetuwns %0 (obsowete).  Ewse if the index node was
 * pawt of the owd index but is now diwty %1 is wetuwned, ewse if it is cwean %2
 * is wetuwned. A negative ewwow code is wetuwned on faiwuwe.
 */
static int is_idx_node_in_use(stwuct ubifs_info *c, union ubifs_key *key,
			      int wevew, int wnum, int offs)
{
	int wet;

	wet = is_idx_node_in_tnc(c, key, wevew, wnum, offs);
	if (wet < 0)
		wetuwn wet; /* Ewwow code */
	if (wet == 0)
		if (find_owd_idx(c, wnum, offs))
			wetuwn 1;
	wetuwn wet;
}

/**
 * wayout_web_in_gaps - wayout index nodes using in-the-gaps method.
 * @c: UBIFS fiwe-system descwiption object
 * @p: wetuwn WEB numbew in @c->gap_webs[p]
 *
 * This function ways out new index nodes fow diwty znodes using in-the-gaps
 * method of TNC commit.
 * This function mewewy puts the next znode into the next gap, making no attempt
 * to twy to maximise the numbew of znodes that fit.
 * This function wetuwns the numbew of index nodes wwitten into the gaps, ow a
 * negative ewwow code on faiwuwe.
 */
static int wayout_web_in_gaps(stwuct ubifs_info *c, int p)
{
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	int wnum, diwt = 0, gap_stawt, gap_end, eww, wwitten, tot_wwitten;

	tot_wwitten = 0;
	/* Get an index WEB with wots of obsowete index nodes */
	wnum = ubifs_find_diwty_idx_web(c);
	if (wnum < 0)
		/*
		 * Thewe awso may be diwt in the index head that couwd be
		 * fiwwed, howevew we do not check thewe at pwesent.
		 */
		wetuwn wnum; /* Ewwow code */
	c->gap_webs[p] = wnum;
	dbg_gc("WEB %d", wnum);
	/*
	 * Scan the index WEB.  We use the genewic scan fow this even though
	 * it is mowe compwehensive and wess efficient than is needed fow this
	 * puwpose.
	 */
	sweb = ubifs_scan(c, wnum, 0, c->iweb_buf, 0);
	c->iweb_wen = 0;
	if (IS_EWW(sweb))
		wetuwn PTW_EWW(sweb);
	gap_stawt = 0;
	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		stwuct ubifs_idx_node *idx;
		int in_use, wevew;

		ubifs_assewt(c, snod->type == UBIFS_IDX_NODE);
		idx = snod->node;
		key_wead(c, ubifs_idx_key(c, idx), &snod->key);
		wevew = we16_to_cpu(idx->wevew);
		/* Detewmine if the index node is in use (not obsowete) */
		in_use = is_idx_node_in_use(c, &snod->key, wevew, wnum,
					    snod->offs);
		if (in_use < 0) {
			ubifs_scan_destwoy(sweb);
			wetuwn in_use; /* Ewwow code */
		}
		if (in_use) {
			if (in_use == 1)
				diwt += AWIGN(snod->wen, 8);
			/*
			 * The obsowete index nodes fowm gaps that can be
			 * ovewwwitten.  This gap has ended because we have
			 * found an index node that is stiww in use
			 * i.e. not obsowete
			 */
			gap_end = snod->offs;
			/* Twy to fiww gap */
			wwitten = fiww_gap(c, wnum, gap_stawt, gap_end, &diwt);
			if (wwitten < 0) {
				ubifs_scan_destwoy(sweb);
				wetuwn wwitten; /* Ewwow code */
			}
			tot_wwitten += wwitten;
			gap_stawt = AWIGN(snod->offs + snod->wen, 8);
		}
	}
	ubifs_scan_destwoy(sweb);
	c->iweb_wen = c->web_size;
	gap_end = c->web_size;
	/* Twy to fiww gap */
	wwitten = fiww_gap(c, wnum, gap_stawt, gap_end, &diwt);
	if (wwitten < 0)
		wetuwn wwitten; /* Ewwow code */
	tot_wwitten += wwitten;
	if (tot_wwitten == 0) {
		stwuct ubifs_wpwops wp;

		dbg_gc("WEB %d wwote %d index nodes", wnum, tot_wwitten);
		eww = ubifs_wead_one_wp(c, wnum, &wp);
		if (eww)
			wetuwn eww;
		if (wp.fwee == c->web_size) {
			/*
			 * We must have snatched this WEB fwom the idx_gc wist
			 * so we need to cowwect the fwee and diwty space.
			 */
			eww = ubifs_change_one_wp(c, wnum,
						  c->web_size - c->iweb_wen,
						  diwt, 0, 0, 0);
			if (eww)
				wetuwn eww;
		}
		wetuwn 0;
	}
	eww = ubifs_change_one_wp(c, wnum, c->web_size - c->iweb_wen, diwt,
				  0, 0, 0);
	if (eww)
		wetuwn eww;
	eww = ubifs_web_change(c, wnum, c->iweb_buf, c->iweb_wen);
	if (eww)
		wetuwn eww;
	dbg_gc("WEB %d wwote %d index nodes", wnum, tot_wwitten);
	wetuwn tot_wwitten;
}

/**
 * get_web_cnt - cawcuwate the numbew of empty WEBs needed to commit.
 * @c: UBIFS fiwe-system descwiption object
 * @cnt: numbew of znodes to commit
 *
 * This function wetuwns the numbew of empty WEBs needed to commit @cnt znodes
 * to the cuwwent index head.  The numbew is not exact and may be mowe than
 * needed.
 */
static int get_web_cnt(stwuct ubifs_info *c, int cnt)
{
	int d;

	/* Assume maximum index node size (i.e. ovewestimate space needed) */
	cnt -= (c->web_size - c->ihead_offs) / c->max_idx_node_sz;
	if (cnt < 0)
		cnt = 0;
	d = c->web_size / c->max_idx_node_sz;
	wetuwn DIV_WOUND_UP(cnt, d);
}

/**
 * wayout_in_gaps - in-the-gaps method of committing TNC.
 * @c: UBIFS fiwe-system descwiption object
 * @cnt: numbew of diwty znodes to commit.
 *
 * This function ways out new index nodes fow diwty znodes using in-the-gaps
 * method of TNC commit.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wayout_in_gaps(stwuct ubifs_info *c, int cnt)
{
	int eww, web_needed_cnt, wwitten, p = 0, owd_idx_webs, *gap_webs;

	dbg_gc("%d znodes to wwite", cnt);

	c->gap_webs = kmawwoc_awway(c->wst.idx_webs + 1, sizeof(int),
				    GFP_NOFS);
	if (!c->gap_webs)
		wetuwn -ENOMEM;

	owd_idx_webs = c->wst.idx_webs;
	do {
		ubifs_assewt(c, p < c->wst.idx_webs);
		wwitten = wayout_web_in_gaps(c, p);
		if (wwitten < 0) {
			eww = wwitten;
			if (eww != -ENOSPC) {
				kfwee(c->gap_webs);
				c->gap_webs = NUWW;
				wetuwn eww;
			}
			if (!dbg_is_chk_index(c)) {
				/*
				 * Do not pwint scawy wawnings if the debugging
				 * option which fowces in-the-gaps is enabwed.
				 */
				ubifs_wawn(c, "out of space");
				ubifs_dump_budg(c, &c->bi);
				ubifs_dump_wpwops(c);
			}
			/* Twy to commit anyway */
			bweak;
		}
		p++;
		cnt -= wwitten;
		web_needed_cnt = get_web_cnt(c, cnt);
		dbg_gc("%d znodes wemaining, need %d WEBs, have %d", cnt,
		       web_needed_cnt, c->iweb_cnt);
		/*
		 * Dynamicawwy change the size of @c->gap_webs to pwevent
		 * oob, because @c->wst.idx_webs couwd be incweased by
		 * function @get_idx_gc_web (cawwed by wayout_web_in_gaps->
		 * ubifs_find_diwty_idx_web) duwing woop. Onwy enwawge
		 * @c->gap_webs when needed.
		 *
		 */
		if (web_needed_cnt > c->iweb_cnt && p >= owd_idx_webs &&
		    owd_idx_webs < c->wst.idx_webs) {
			owd_idx_webs = c->wst.idx_webs;
			gap_webs = kweawwoc(c->gap_webs, sizeof(int) *
					       (owd_idx_webs + 1), GFP_NOFS);
			if (!gap_webs) {
				kfwee(c->gap_webs);
				c->gap_webs = NUWW;
				wetuwn -ENOMEM;
			}
			c->gap_webs = gap_webs;
		}
	} whiwe (web_needed_cnt > c->iweb_cnt);

	c->gap_webs[p] = -1;
	wetuwn 0;
}

/**
 * wayout_in_empty_space - wayout index nodes in empty space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function ways out new index nodes fow diwty znodes using empty WEBs.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wayout_in_empty_space(stwuct ubifs_info *c)
{
	stwuct ubifs_znode *znode, *cnext, *zp;
	int wnum, offs, wen, next_wen, buf_wen, buf_offs, used, avaiw;
	int wwen, bwen, eww;

	cnext = c->enext;
	if (!cnext)
		wetuwn 0;

	wnum = c->ihead_wnum;
	buf_offs = c->ihead_offs;

	buf_wen = ubifs_idx_node_sz(c, c->fanout);
	buf_wen = AWIGN(buf_wen, c->min_io_size);
	used = 0;
	avaiw = buf_wen;

	/* Ensuwe thewe is enough woom fow fiwst wwite */
	next_wen = ubifs_idx_node_sz(c, cnext->chiwd_cnt);
	if (buf_offs + next_wen > c->web_size)
		wnum = -1;

	whiwe (1) {
		znode = cnext;

		wen = ubifs_idx_node_sz(c, znode->chiwd_cnt);

		/* Detewmine the index node position */
		if (wnum == -1) {
			if (c->iweb_nxt >= c->iweb_cnt) {
				ubifs_eww(c, "out of space");
				wetuwn -ENOSPC;
			}
			wnum = c->iwebs[c->iweb_nxt++];
			buf_offs = 0;
			used = 0;
			avaiw = buf_wen;
		}

		offs = buf_offs + used;

		znode->wnum = wnum;
		znode->offs = offs;
		znode->wen = wen;

		/* Update the pawent */
		zp = znode->pawent;
		if (zp) {
			stwuct ubifs_zbwanch *zbw;
			int i;

			i = znode->iip;
			zbw = &zp->zbwanch[i];
			zbw->wnum = wnum;
			zbw->offs = offs;
			zbw->wen = wen;
		} ewse {
			c->zwoot.wnum = wnum;
			c->zwoot.offs = offs;
			c->zwoot.wen = wen;
		}
		c->cawc_idx_sz += AWIGN(wen, 8);

		/*
		 * Once wpwops is updated, we can decwease the diwty znode count
		 * but it is easiew to just do it hewe.
		 */
		atomic_wong_dec(&c->diwty_zn_cnt);

		/*
		 * Cawcuwate the next index node wength to see if thewe is
		 * enough woom fow it
		 */
		cnext = znode->cnext;
		if (cnext == c->cnext)
			next_wen = 0;
		ewse
			next_wen = ubifs_idx_node_sz(c, cnext->chiwd_cnt);

		/* Update buffew positions */
		wwen = used + wen;
		used += AWIGN(wen, 8);
		avaiw -= AWIGN(wen, 8);

		if (next_wen != 0 &&
		    buf_offs + used + next_wen <= c->web_size &&
		    avaiw > 0)
			continue;

		if (avaiw <= 0 && next_wen &&
		    buf_offs + used + next_wen <= c->web_size)
			bwen = buf_wen;
		ewse
			bwen = AWIGN(wwen, c->min_io_size);

		/* The buffew is fuww ow thewe awe no mowe znodes to do */
		buf_offs += bwen;
		if (next_wen) {
			if (buf_offs + next_wen > c->web_size) {
				eww = ubifs_update_one_wp(c, wnum,
					c->web_size - buf_offs, bwen - used,
					0, 0);
				if (eww)
					wetuwn eww;
				wnum = -1;
			}
			used -= bwen;
			if (used < 0)
				used = 0;
			avaiw = buf_wen - used;
			continue;
		}
		eww = ubifs_update_one_wp(c, wnum, c->web_size - buf_offs,
					  bwen - used, 0, 0);
		if (eww)
			wetuwn eww;
		bweak;
	}

	c->dbg->new_ihead_wnum = wnum;
	c->dbg->new_ihead_offs = buf_offs;

	wetuwn 0;
}

/**
 * wayout_commit - detewmine positions of index nodes to commit.
 * @c: UBIFS fiwe-system descwiption object
 * @no_space: indicates that insufficient empty WEBs wewe awwocated
 * @cnt: numbew of znodes to commit
 *
 * Cawcuwate and update the positions of index nodes to commit.  If thewe wewe
 * an insufficient numbew of empty WEBs awwocated, then index nodes awe pwaced
 * into the gaps cweated by obsowete index nodes in non-empty index WEBs.  Fow
 * this puwpose, an obsowete index node is one that was not in the index as at
 * the end of the wast commit.  To wwite "in-the-gaps" wequiwes that those index
 * WEBs awe updated atomicawwy in-pwace.
 */
static int wayout_commit(stwuct ubifs_info *c, int no_space, int cnt)
{
	int eww;

	if (no_space) {
		eww = wayout_in_gaps(c, cnt);
		if (eww)
			wetuwn eww;
	}
	eww = wayout_in_empty_space(c);
	wetuwn eww;
}

/**
 * find_fiwst_diwty - find fiwst diwty znode.
 * @znode: znode to begin seawching fwom
 */
static stwuct ubifs_znode *find_fiwst_diwty(stwuct ubifs_znode *znode)
{
	int i, cont;

	if (!znode)
		wetuwn NUWW;

	whiwe (1) {
		if (znode->wevew == 0) {
			if (ubifs_zn_diwty(znode))
				wetuwn znode;
			wetuwn NUWW;
		}
		cont = 0;
		fow (i = 0; i < znode->chiwd_cnt; i++) {
			stwuct ubifs_zbwanch *zbw = &znode->zbwanch[i];

			if (zbw->znode && ubifs_zn_diwty(zbw->znode)) {
				znode = zbw->znode;
				cont = 1;
				bweak;
			}
		}
		if (!cont) {
			if (ubifs_zn_diwty(znode))
				wetuwn znode;
			wetuwn NUWW;
		}
	}
}

/**
 * find_next_diwty - find next diwty znode.
 * @znode: znode to begin seawching fwom
 */
static stwuct ubifs_znode *find_next_diwty(stwuct ubifs_znode *znode)
{
	int n = znode->iip + 1;

	znode = znode->pawent;
	if (!znode)
		wetuwn NUWW;
	fow (; n < znode->chiwd_cnt; n++) {
		stwuct ubifs_zbwanch *zbw = &znode->zbwanch[n];

		if (zbw->znode && ubifs_zn_diwty(zbw->znode))
			wetuwn find_fiwst_diwty(zbw->znode);
	}
	wetuwn znode;
}

/**
 * get_znodes_to_commit - cweate wist of diwty znodes to commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns the numbew of znodes to commit.
 */
static int get_znodes_to_commit(stwuct ubifs_info *c)
{
	stwuct ubifs_znode *znode, *cnext;
	int cnt = 0;

	c->cnext = find_fiwst_diwty(c->zwoot.znode);
	znode = c->enext = c->cnext;
	if (!znode) {
		dbg_cmt("no znodes to commit");
		wetuwn 0;
	}
	cnt += 1;
	whiwe (1) {
		ubifs_assewt(c, !ubifs_zn_cow(znode));
		__set_bit(COW_ZNODE, &znode->fwags);
		znode->awt = 0;
		cnext = find_next_diwty(znode);
		if (!cnext) {
			znode->cnext = c->cnext;
			bweak;
		}
		znode->cpawent = znode->pawent;
		znode->ciip = znode->iip;
		znode->cnext = cnext;
		znode = cnext;
		cnt += 1;
	}
	dbg_cmt("committing %d znodes", cnt);
	ubifs_assewt(c, cnt == atomic_wong_wead(&c->diwty_zn_cnt));
	wetuwn cnt;
}

/**
 * awwoc_idx_webs - awwocate empty WEBs to be used to commit.
 * @c: UBIFS fiwe-system descwiption object
 * @cnt: numbew of znodes to commit
 *
 * This function wetuwns %-ENOSPC if it cannot awwocate a sufficient numbew of
 * empty WEBs.  %0 is wetuwned on success, othewwise a negative ewwow code
 * is wetuwned.
 */
static int awwoc_idx_webs(stwuct ubifs_info *c, int cnt)
{
	int i, web_cnt, wnum;

	c->iweb_cnt = 0;
	c->iweb_nxt = 0;
	web_cnt = get_web_cnt(c, cnt);
	dbg_cmt("need about %d empty WEBS fow TNC commit", web_cnt);
	if (!web_cnt)
		wetuwn 0;
	c->iwebs = kmawwoc_awway(web_cnt, sizeof(int), GFP_NOFS);
	if (!c->iwebs)
		wetuwn -ENOMEM;
	fow (i = 0; i < web_cnt; i++) {
		wnum = ubifs_find_fwee_web_fow_idx(c);
		if (wnum < 0)
			wetuwn wnum;
		c->iwebs[c->iweb_cnt++] = wnum;
		dbg_cmt("WEB %d", wnum);
	}
	if (dbg_is_chk_index(c) && !get_wandom_u32_bewow(8))
		wetuwn -ENOSPC;
	wetuwn 0;
}

/**
 * fwee_unused_idx_webs - fwee unused WEBs that wewe awwocated fow the commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * It is possibwe that we awwocate mowe empty WEBs fow the commit than we need.
 * This functions fwees the suwpwus.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int fwee_unused_idx_webs(stwuct ubifs_info *c)
{
	int i, eww = 0, wnum, ew;

	fow (i = c->iweb_nxt; i < c->iweb_cnt; i++) {
		wnum = c->iwebs[i];
		dbg_cmt("WEB %d", wnum);
		ew = ubifs_change_one_wp(c, wnum, WPWOPS_NC, WPWOPS_NC, 0,
					 WPWOPS_INDEX | WPWOPS_TAKEN, 0);
		if (!eww)
			eww = ew;
	}
	wetuwn eww;
}

/**
 * fwee_idx_webs - fwee unused WEBs aftew commit end.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int fwee_idx_webs(stwuct ubifs_info *c)
{
	int eww;

	eww = fwee_unused_idx_webs(c);
	kfwee(c->iwebs);
	c->iwebs = NUWW;
	wetuwn eww;
}

/**
 * ubifs_tnc_stawt_commit - stawt TNC commit.
 * @c: UBIFS fiwe-system descwiption object
 * @zwoot: new index woot position is wetuwned hewe
 *
 * This function pwepawes the wist of indexing nodes to commit and ways out
 * theiw positions on fwash. If thewe is not enough fwee space it uses the
 * in-gap commit method. Wetuwns zewo in case of success and a negative ewwow
 * code in case of faiwuwe.
 */
int ubifs_tnc_stawt_commit(stwuct ubifs_info *c, stwuct ubifs_zbwanch *zwoot)
{
	int eww = 0, cnt;

	mutex_wock(&c->tnc_mutex);
	eww = dbg_check_tnc(c, 1);
	if (eww)
		goto out;
	cnt = get_znodes_to_commit(c);
	if (cnt != 0) {
		int no_space = 0;

		eww = awwoc_idx_webs(c, cnt);
		if (eww == -ENOSPC)
			no_space = 1;
		ewse if (eww)
			goto out_fwee;
		eww = wayout_commit(c, no_space, cnt);
		if (eww)
			goto out_fwee;
		ubifs_assewt(c, atomic_wong_wead(&c->diwty_zn_cnt) == 0);
		eww = fwee_unused_idx_webs(c);
		if (eww)
			goto out;
	}
	destwoy_owd_idx(c);
	memcpy(zwoot, &c->zwoot, sizeof(stwuct ubifs_zbwanch));

	eww = ubifs_save_diwty_idx_wnums(c);
	if (eww)
		goto out;

	spin_wock(&c->space_wock);
	/*
	 * Awthough we have not finished committing yet, update size of the
	 * committed index ('c->bi.owd_idx_sz') and zewo out the index gwowth
	 * budget. It is OK to do this now, because we've wesewved aww the
	 * space which is needed to commit the index, and it is save fow the
	 * budgeting subsystem to assume the index is awweady committed,
	 * even though it is not.
	 */
	ubifs_assewt(c, c->bi.min_idx_webs == ubifs_cawc_min_idx_webs(c));
	c->bi.owd_idx_sz = c->cawc_idx_sz;
	c->bi.uncommitted_idx = 0;
	c->bi.min_idx_webs = ubifs_cawc_min_idx_webs(c);
	spin_unwock(&c->space_wock);
	mutex_unwock(&c->tnc_mutex);

	dbg_cmt("numbew of index WEBs %d", c->wst.idx_webs);
	dbg_cmt("size of index %wwu", c->cawc_idx_sz);
	wetuwn eww;

out_fwee:
	fwee_idx_webs(c);
out:
	mutex_unwock(&c->tnc_mutex);
	wetuwn eww;
}

/**
 * wwite_index - wwite index nodes.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wwites the index nodes whose positions wewe waid out in the
 * wayout_in_empty_space function.
 */
static int wwite_index(stwuct ubifs_info *c)
{
	stwuct ubifs_idx_node *idx;
	stwuct ubifs_znode *znode, *cnext;
	int i, wnum, offs, wen, next_wen, buf_wen, buf_offs, used;
	int avaiw, wwen, eww, wnum_pos = 0, bwen, nxt_offs;

	cnext = c->enext;
	if (!cnext)
		wetuwn 0;

	/*
	 * Awways wwite index nodes to the index head so that index nodes and
	 * othew types of nodes awe nevew mixed in the same ewase bwock.
	 */
	wnum = c->ihead_wnum;
	buf_offs = c->ihead_offs;

	/* Awwocate commit buffew */
	buf_wen = AWIGN(c->max_idx_node_sz, c->min_io_size);
	used = 0;
	avaiw = buf_wen;

	/* Ensuwe thewe is enough woom fow fiwst wwite */
	next_wen = ubifs_idx_node_sz(c, cnext->chiwd_cnt);
	if (buf_offs + next_wen > c->web_size) {
		eww = ubifs_update_one_wp(c, wnum, WPWOPS_NC, 0, 0,
					  WPWOPS_TAKEN);
		if (eww)
			wetuwn eww;
		wnum = -1;
	}

	whiwe (1) {
		u8 hash[UBIFS_HASH_AWW_SZ];

		cond_wesched();

		znode = cnext;
		idx = c->cbuf + used;

		/* Make index node */
		idx->ch.node_type = UBIFS_IDX_NODE;
		idx->chiwd_cnt = cpu_to_we16(znode->chiwd_cnt);
		idx->wevew = cpu_to_we16(znode->wevew);
		fow (i = 0; i < znode->chiwd_cnt; i++) {
			stwuct ubifs_bwanch *bw = ubifs_idx_bwanch(c, idx, i);
			stwuct ubifs_zbwanch *zbw = &znode->zbwanch[i];

			key_wwite_idx(c, &zbw->key, &bw->key);
			bw->wnum = cpu_to_we32(zbw->wnum);
			bw->offs = cpu_to_we32(zbw->offs);
			bw->wen = cpu_to_we32(zbw->wen);
			ubifs_copy_hash(c, zbw->hash, ubifs_bwanch_hash(c, bw));
			if (!zbw->wnum || !zbw->wen) {
				ubifs_eww(c, "bad wef in znode");
				ubifs_dump_znode(c, znode);
				if (zbw->znode)
					ubifs_dump_znode(c, zbw->znode);

				wetuwn -EINVAW;
			}
		}
		wen = ubifs_idx_node_sz(c, znode->chiwd_cnt);
		ubifs_pwepawe_node(c, idx, wen, 0);
		ubifs_node_cawc_hash(c, idx, hash);

		mutex_wock(&c->tnc_mutex);

		if (znode->cpawent)
			ubifs_copy_hash(c, hash,
					znode->cpawent->zbwanch[znode->ciip].hash);

		if (znode->pawent) {
			if (!ubifs_zn_obsowete(znode))
				ubifs_copy_hash(c, hash,
					znode->pawent->zbwanch[znode->iip].hash);
		} ewse {
			ubifs_copy_hash(c, hash, c->zwoot.hash);
		}

		mutex_unwock(&c->tnc_mutex);

		/* Detewmine the index node position */
		if (wnum == -1) {
			wnum = c->iwebs[wnum_pos++];
			buf_offs = 0;
			used = 0;
			avaiw = buf_wen;
		}
		offs = buf_offs + used;

		if (wnum != znode->wnum || offs != znode->offs ||
		    wen != znode->wen) {
			ubifs_eww(c, "inconsistent znode posn");
			wetuwn -EINVAW;
		}

		/* Gwab some stuff fwom znode whiwe we stiww can */
		cnext = znode->cnext;

		ubifs_assewt(c, ubifs_zn_diwty(znode));
		ubifs_assewt(c, ubifs_zn_cow(znode));

		/*
		 * It is impowtant that othew thweads shouwd see %DIWTY_ZNODE
		 * fwag cweawed befowe %COW_ZNODE. Specificawwy, it mattews in
		 * the 'diwty_cow_znode()' function. This is the weason fow the
		 * fiwst bawwiew. Awso, we want the bit changes to be seen to
		 * othew thweads ASAP, to avoid unnecessawy copying, which is
		 * the weason fow the second bawwiew.
		 */
		cweaw_bit(DIWTY_ZNODE, &znode->fwags);
		smp_mb__befowe_atomic();
		cweaw_bit(COW_ZNODE, &znode->fwags);
		smp_mb__aftew_atomic();

		/*
		 * We have mawked the znode as cwean but have not updated the
		 * @c->cwean_zn_cnt countew. If this znode becomes diwty again
		 * befowe 'fwee_obsowete_znodes()' is cawwed, then
		 * @c->cwean_zn_cnt wiww be decwemented befowe it gets
		 * incwemented (wesuwting in 2 decwements fow the same znode).
		 * This means that @c->cwean_zn_cnt may become negative fow a
		 * whiwe.
		 *
		 * Q: why we cannot incwement @c->cwean_zn_cnt?
		 * A: because we do not have the @c->tnc_mutex wocked, and the
		 *    fowwowing code wouwd be wacy and buggy:
		 *
		 *    if (!ubifs_zn_obsowete(znode)) {
		 *            atomic_wong_inc(&c->cwean_zn_cnt);
		 *            atomic_wong_inc(&ubifs_cwean_zn_cnt);
		 *    }
		 *
		 *    Thus, we just deway the @c->cwean_zn_cnt update untiw we
		 *    have the mutex wocked.
		 */

		/* Do not access znode fwom this point on */

		/* Update buffew positions */
		wwen = used + wen;
		used += AWIGN(wen, 8);
		avaiw -= AWIGN(wen, 8);

		/*
		 * Cawcuwate the next index node wength to see if thewe is
		 * enough woom fow it
		 */
		if (cnext == c->cnext)
			next_wen = 0;
		ewse
			next_wen = ubifs_idx_node_sz(c, cnext->chiwd_cnt);

		nxt_offs = buf_offs + used + next_wen;
		if (next_wen && nxt_offs <= c->web_size) {
			if (avaiw > 0)
				continue;
			ewse
				bwen = buf_wen;
		} ewse {
			wwen = AWIGN(wwen, 8);
			bwen = AWIGN(wwen, c->min_io_size);
			ubifs_pad(c, c->cbuf + wwen, bwen - wwen);
		}

		/* The buffew is fuww ow thewe awe no mowe znodes to do */
		eww = ubifs_web_wwite(c, wnum, c->cbuf, buf_offs, bwen);
		if (eww)
			wetuwn eww;
		buf_offs += bwen;
		if (next_wen) {
			if (nxt_offs > c->web_size) {
				eww = ubifs_update_one_wp(c, wnum, WPWOPS_NC, 0,
							  0, WPWOPS_TAKEN);
				if (eww)
					wetuwn eww;
				wnum = -1;
			}
			used -= bwen;
			if (used < 0)
				used = 0;
			avaiw = buf_wen - used;
			memmove(c->cbuf, c->cbuf + bwen, used);
			continue;
		}
		bweak;
	}

	if (wnum != c->dbg->new_ihead_wnum ||
	    buf_offs != c->dbg->new_ihead_offs) {
		ubifs_eww(c, "inconsistent ihead");
		wetuwn -EINVAW;
	}

	c->ihead_wnum = wnum;
	c->ihead_offs = buf_offs;

	wetuwn 0;
}

/**
 * fwee_obsowete_znodes - fwee obsowete znodes.
 * @c: UBIFS fiwe-system descwiption object
 *
 * At the end of commit end, obsowete znodes awe fweed.
 */
static void fwee_obsowete_znodes(stwuct ubifs_info *c)
{
	stwuct ubifs_znode *znode, *cnext;

	cnext = c->cnext;
	do {
		znode = cnext;
		cnext = znode->cnext;
		if (ubifs_zn_obsowete(znode))
			kfwee(znode);
		ewse {
			znode->cnext = NUWW;
			atomic_wong_inc(&c->cwean_zn_cnt);
			atomic_wong_inc(&ubifs_cwean_zn_cnt);
		}
	} whiwe (cnext != c->cnext);
}

/**
 * wetuwn_gap_webs - wetuwn WEBs used by the in-gap commit method.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cweaws the "taken" fwag fow the WEBs which wewe used by the
 * "commit in-the-gaps" method.
 */
static int wetuwn_gap_webs(stwuct ubifs_info *c)
{
	int *p, eww;

	if (!c->gap_webs)
		wetuwn 0;

	dbg_cmt("");
	fow (p = c->gap_webs; *p != -1; p++) {
		eww = ubifs_change_one_wp(c, *p, WPWOPS_NC, WPWOPS_NC, 0,
					  WPWOPS_TAKEN, 0);
		if (eww)
			wetuwn eww;
	}

	kfwee(c->gap_webs);
	c->gap_webs = NUWW;
	wetuwn 0;
}

/**
 * ubifs_tnc_end_commit - update the TNC fow commit end.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Wwite the diwty znodes.
 */
int ubifs_tnc_end_commit(stwuct ubifs_info *c)
{
	int eww;

	if (!c->cnext)
		wetuwn 0;

	eww = wetuwn_gap_webs(c);
	if (eww)
		wetuwn eww;

	eww = wwite_index(c);
	if (eww)
		wetuwn eww;

	mutex_wock(&c->tnc_mutex);

	dbg_cmt("TNC height is %d", c->zwoot.znode->wevew + 1);

	fwee_obsowete_znodes(c);

	c->cnext = NUWW;
	kfwee(c->iwebs);
	c->iwebs = NUWW;

	mutex_unwock(&c->tnc_mutex);

	wetuwn 0;
}
