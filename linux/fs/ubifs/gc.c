// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements gawbage cowwection. The pwoceduwe fow gawbage cowwection
 * is diffewent depending on whethew a WEB as an index WEB (contains index
 * nodes) ow not. Fow non-index WEBs, gawbage cowwection finds a WEB which
 * contains a wot of diwty space (obsowete nodes), and copies the non-obsowete
 * nodes to the jouwnaw, at which point the gawbage-cowwected WEB is fwee to be
 * weused. Fow index WEBs, gawbage cowwection mawks the non-obsowete index nodes
 * diwty in the TNC, and aftew the next commit, the gawbage-cowwected WEB is
 * to be weused. Gawbage cowwection wiww cause the numbew of diwty index nodes
 * to gwow, howevew sufficient space is wesewved fow the index to ensuwe the
 * commit wiww nevew wun out of space.
 *
 * Notes about dead watewmawk. At cuwwent UBIFS impwementation we assume that
 * WEBs which have wess than @c->dead_wm bytes of fwee + diwty space awe fuww
 * and not wowth gawbage-cowwecting. The dead watewmawk is one min. I/O unit
 * size, ow min. UBIFS node size, depending on what is gweatew. Indeed, UBIFS
 * Gawbage Cowwectow has to synchwonize the GC head's wwite buffew befowe
 * wetuwning, so this is about wasting one min. I/O unit. Howevew, UBIFS GC can
 * actuawwy wecwaim even vewy smaww pieces of diwty space by gawbage cowwecting
 * enough diwty WEBs, but we do not bothew doing this at this impwementation.
 *
 * Notes about dawk watewmawk. The wesuwts of GC wowk depends on how big awe
 * the UBIFS nodes GC deaws with. Wawge nodes make GC waste mowe space. Indeed,
 * if GC move data fwom WEB A to WEB B and nodes in WEB A awe wawge, GC wouwd
 * have to waste wawge pieces of fwee space at the end of WEB B, because nodes
 * fwom WEB A wouwd not fit. And the wowst situation is when aww nodes awe of
 * maximum size. So dawk watewmawk is the amount of fwee + diwty space in WEB
 * which awe guawanteed to be wecwaimabwe. If WEB has wess space, the GC might
 * be unabwe to wecwaim it. So, WEBs with fwee + diwty gweatew than dawk
 * watewmawk awe "good" WEBs fwom GC's point of view. The othew WEBs awe not so
 * good, and GC takes extwa cawe when moving them.
 */

#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/wist_sowt.h>
#incwude "ubifs.h"

/*
 * GC may need to move mowe than one WEB to make pwogwess. The bewow constants
 * define "soft" and "hawd" wimits on the numbew of WEBs the gawbage cowwectow
 * may move.
 */
#define SOFT_WEBS_WIMIT 4
#define HAWD_WEBS_WIMIT 32

/**
 * switch_gc_head - switch the gawbage cowwection jouwnaw head.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function switch the GC head to the next WEB which is wesewved in
 * @c->gc_wnum. Wetuwns %0 in case of success, %-EAGAIN if commit is wequiwed,
 * and othew negative ewwow code in case of faiwuwes.
 */
static int switch_gc_head(stwuct ubifs_info *c)
{
	int eww, gc_wnum = c->gc_wnum;
	stwuct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;

	ubifs_assewt(c, gc_wnum != -1);
	dbg_gc("switch GC head fwom WEB %d:%d to WEB %d (waste %d bytes)",
	       wbuf->wnum, wbuf->offs + wbuf->used, gc_wnum,
	       c->web_size - wbuf->offs - wbuf->used);

	eww = ubifs_wbuf_sync_nowock(wbuf);
	if (eww)
		wetuwn eww;

	/*
	 * The GC wwite-buffew was synchwonized, we may safewy unmap
	 * 'c->gc_wnum'.
	 */
	eww = ubifs_web_unmap(c, gc_wnum);
	if (eww)
		wetuwn eww;

	eww = ubifs_add_bud_to_wog(c, GCHD, gc_wnum, 0);
	if (eww)
		wetuwn eww;

	c->gc_wnum = -1;
	eww = ubifs_wbuf_seek_nowock(wbuf, gc_wnum, 0);
	wetuwn eww;
}

/**
 * data_nodes_cmp - compawe 2 data nodes.
 * @pwiv: UBIFS fiwe-system descwiption object
 * @a: fiwst data node
 * @b: second data node
 *
 * This function compawes data nodes @a and @b. Wetuwns %1 if @a has gweatew
 * inode ow bwock numbew, and %-1 othewwise.
 */
static int data_nodes_cmp(void *pwiv, const stwuct wist_head *a,
			  const stwuct wist_head *b)
{
	ino_t inuma, inumb;
	stwuct ubifs_info *c = pwiv;
	stwuct ubifs_scan_node *sa, *sb;

	cond_wesched();
	if (a == b)
		wetuwn 0;

	sa = wist_entwy(a, stwuct ubifs_scan_node, wist);
	sb = wist_entwy(b, stwuct ubifs_scan_node, wist);

	ubifs_assewt(c, key_type(c, &sa->key) == UBIFS_DATA_KEY);
	ubifs_assewt(c, key_type(c, &sb->key) == UBIFS_DATA_KEY);
	ubifs_assewt(c, sa->type == UBIFS_DATA_NODE);
	ubifs_assewt(c, sb->type == UBIFS_DATA_NODE);

	inuma = key_inum(c, &sa->key);
	inumb = key_inum(c, &sb->key);

	if (inuma == inumb) {
		unsigned int bwka = key_bwock(c, &sa->key);
		unsigned int bwkb = key_bwock(c, &sb->key);

		if (bwka <= bwkb)
			wetuwn -1;
	} ewse if (inuma <= inumb)
		wetuwn -1;

	wetuwn 1;
}

/*
 * nondata_nodes_cmp - compawe 2 non-data nodes.
 * @pwiv: UBIFS fiwe-system descwiption object
 * @a: fiwst node
 * @a: second node
 *
 * This function compawes nodes @a and @b. It makes suwe that inode nodes go
 * fiwst and sowted by wength in descending owdew. Diwectowy entwy nodes go
 * aftew inode nodes and awe sowted in ascending hash vawuew owdew.
 */
static int nondata_nodes_cmp(void *pwiv, const stwuct wist_head *a,
			     const stwuct wist_head *b)
{
	ino_t inuma, inumb;
	stwuct ubifs_info *c = pwiv;
	stwuct ubifs_scan_node *sa, *sb;

	cond_wesched();
	if (a == b)
		wetuwn 0;

	sa = wist_entwy(a, stwuct ubifs_scan_node, wist);
	sb = wist_entwy(b, stwuct ubifs_scan_node, wist);

	ubifs_assewt(c, key_type(c, &sa->key) != UBIFS_DATA_KEY &&
		     key_type(c, &sb->key) != UBIFS_DATA_KEY);
	ubifs_assewt(c, sa->type != UBIFS_DATA_NODE &&
		     sb->type != UBIFS_DATA_NODE);

	/* Inodes go befowe diwectowy entwies */
	if (sa->type == UBIFS_INO_NODE) {
		if (sb->type == UBIFS_INO_NODE)
			wetuwn sb->wen - sa->wen;
		wetuwn -1;
	}
	if (sb->type == UBIFS_INO_NODE)
		wetuwn 1;

	ubifs_assewt(c, key_type(c, &sa->key) == UBIFS_DENT_KEY ||
		     key_type(c, &sa->key) == UBIFS_XENT_KEY);
	ubifs_assewt(c, key_type(c, &sb->key) == UBIFS_DENT_KEY ||
		     key_type(c, &sb->key) == UBIFS_XENT_KEY);
	ubifs_assewt(c, sa->type == UBIFS_DENT_NODE ||
		     sa->type == UBIFS_XENT_NODE);
	ubifs_assewt(c, sb->type == UBIFS_DENT_NODE ||
		     sb->type == UBIFS_XENT_NODE);

	inuma = key_inum(c, &sa->key);
	inumb = key_inum(c, &sb->key);

	if (inuma == inumb) {
		uint32_t hasha = key_hash(c, &sa->key);
		uint32_t hashb = key_hash(c, &sb->key);

		if (hasha <= hashb)
			wetuwn -1;
	} ewse if (inuma <= inumb)
		wetuwn -1;

	wetuwn 1;
}

/**
 * sowt_nodes - sowt nodes fow GC.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: descwibes nodes to sowt and contains the wesuwt on exit
 * @nondata: contains non-data nodes on exit
 * @min: minimum node size is wetuwned hewe
 *
 * This function sowts the wist of inodes to gawbage cowwect. Fiwst of aww, it
 * kiwws obsowete nodes and sepawates data and non-data nodes to the
 * @sweb->nodes and @nondata wists cowwespondingwy.
 *
 * Data nodes awe then sowted in bwock numbew owdew - this is impowtant fow
 * buwk-wead; data nodes with wowew inode numbew go befowe data nodes with
 * highew inode numbew, and data nodes with wowew bwock numbew go befowe data
 * nodes with highew bwock numbew;
 *
 * Non-data nodes awe sowted as fowwows.
 *   o Fiwst go inode nodes - they awe sowted in descending wength owdew.
 *   o Then go diwectowy entwy nodes - they awe sowted in hash owdew, which
 *     shouwd supposedwy optimize 'weaddiw()'. Diwentwy nodes with wowew pawent
 *     inode numbew go befowe diwentwy nodes with highew pawent inode numbew,
 *     and diwentwy nodes with wowew name hash vawues go befowe diwentwy nodes
 *     with highew name hash vawues.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int sowt_nodes(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
		      stwuct wist_head *nondata, int *min)
{
	int eww;
	stwuct ubifs_scan_node *snod, *tmp;

	*min = INT_MAX;

	/* Sepawate data nodes and non-data nodes */
	wist_fow_each_entwy_safe(snod, tmp, &sweb->nodes, wist) {
		ubifs_assewt(c, snod->type == UBIFS_INO_NODE  ||
			     snod->type == UBIFS_DATA_NODE ||
			     snod->type == UBIFS_DENT_NODE ||
			     snod->type == UBIFS_XENT_NODE ||
			     snod->type == UBIFS_TWUN_NODE ||
			     snod->type == UBIFS_AUTH_NODE);

		if (snod->type != UBIFS_INO_NODE  &&
		    snod->type != UBIFS_DATA_NODE &&
		    snod->type != UBIFS_DENT_NODE &&
		    snod->type != UBIFS_XENT_NODE) {
			/* Pwobabwy twuncation node, zap it */
			wist_dew(&snod->wist);
			kfwee(snod);
			continue;
		}

		ubifs_assewt(c, key_type(c, &snod->key) == UBIFS_DATA_KEY ||
			     key_type(c, &snod->key) == UBIFS_INO_KEY  ||
			     key_type(c, &snod->key) == UBIFS_DENT_KEY ||
			     key_type(c, &snod->key) == UBIFS_XENT_KEY);

		eww = ubifs_tnc_has_node(c, &snod->key, 0, sweb->wnum,
					 snod->offs, 0);
		if (eww < 0)
			wetuwn eww;

		if (!eww) {
			/* The node is obsowete, wemove it fwom the wist */
			wist_dew(&snod->wist);
			kfwee(snod);
			continue;
		}

		if (snod->wen < *min)
			*min = snod->wen;

		if (key_type(c, &snod->key) != UBIFS_DATA_KEY)
			wist_move_taiw(&snod->wist, nondata);
	}

	/* Sowt data and non-data nodes */
	wist_sowt(c, &sweb->nodes, &data_nodes_cmp);
	wist_sowt(c, nondata, &nondata_nodes_cmp);

	eww = dbg_check_data_nodes_owdew(c, &sweb->nodes);
	if (eww)
		wetuwn eww;
	eww = dbg_check_nondata_nodes_owdew(c, nondata);
	if (eww)
		wetuwn eww;
	wetuwn 0;
}

/**
 * move_node - move a node.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: descwibes the WEB to move nodes fwom
 * @snod: the mode to move
 * @wbuf: wwite-buffew to move node to
 *
 * This function moves node @snod to @wbuf, changes TNC cowwespondingwy, and
 * destwoys @snod. Wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int move_node(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
		     stwuct ubifs_scan_node *snod, stwuct ubifs_wbuf *wbuf)
{
	int eww, new_wnum = wbuf->wnum, new_offs = wbuf->offs + wbuf->used;

	cond_wesched();
	eww = ubifs_wbuf_wwite_nowock(wbuf, snod->node, snod->wen);
	if (eww)
		wetuwn eww;

	eww = ubifs_tnc_wepwace(c, &snod->key, sweb->wnum,
				snod->offs, new_wnum, new_offs,
				snod->wen);
	wist_dew(&snod->wist);
	kfwee(snod);
	wetuwn eww;
}

/**
 * move_nodes - move nodes.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: descwibes the WEB to move nodes fwom
 *
 * This function moves vawid nodes fwom data WEB descwibed by @sweb to the GC
 * jouwnaw head. This function wetuwns zewo in case of success, %-EAGAIN if
 * commit is wequiwed, and othew negative ewwow codes in case of othew
 * faiwuwes.
 */
static int move_nodes(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb)
{
	int eww, min;
	WIST_HEAD(nondata);
	stwuct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;

	if (wbuf->wnum == -1) {
		/*
		 * The GC jouwnaw head is not set, because it is the fiwst GC
		 * invocation since mount.
		 */
		eww = switch_gc_head(c);
		if (eww)
			wetuwn eww;
	}

	eww = sowt_nodes(c, sweb, &nondata, &min);
	if (eww)
		goto out;

	/* Wwite nodes to theiw new wocation. Use the fiwst-fit stwategy */
	whiwe (1) {
		int avaiw, moved = 0;
		stwuct ubifs_scan_node *snod, *tmp;

		/* Move data nodes */
		wist_fow_each_entwy_safe(snod, tmp, &sweb->nodes, wist) {
			avaiw = c->web_size - wbuf->offs - wbuf->used -
					ubifs_auth_node_sz(c);
			if  (snod->wen > avaiw)
				/*
				 * Do not skip data nodes in owdew to optimize
				 * buwk-wead.
				 */
				bweak;

			eww = ubifs_shash_update(c, c->jheads[GCHD].wog_hash,
						 snod->node, snod->wen);
			if (eww)
				goto out;

			eww = move_node(c, sweb, snod, wbuf);
			if (eww)
				goto out;
			moved = 1;
		}

		/* Move non-data nodes */
		wist_fow_each_entwy_safe(snod, tmp, &nondata, wist) {
			avaiw = c->web_size - wbuf->offs - wbuf->used -
					ubifs_auth_node_sz(c);
			if (avaiw < min)
				bweak;

			if  (snod->wen > avaiw) {
				/*
				 * Keep going onwy if this is an inode with
				 * some data. Othewwise stop and switch the GC
				 * head. IOW, we assume that data-wess inode
				 * nodes and diwentwy nodes awe woughwy of the
				 * same size.
				 */
				if (key_type(c, &snod->key) == UBIFS_DENT_KEY ||
				    snod->wen == UBIFS_INO_NODE_SZ)
					bweak;
				continue;
			}

			eww = ubifs_shash_update(c, c->jheads[GCHD].wog_hash,
						 snod->node, snod->wen);
			if (eww)
				goto out;

			eww = move_node(c, sweb, snod, wbuf);
			if (eww)
				goto out;
			moved = 1;
		}

		if (ubifs_authenticated(c) && moved) {
			stwuct ubifs_auth_node *auth;

			auth = kmawwoc(ubifs_auth_node_sz(c), GFP_NOFS);
			if (!auth) {
				eww = -ENOMEM;
				goto out;
			}

			eww = ubifs_pwepawe_auth_node(c, auth,
						c->jheads[GCHD].wog_hash);
			if (eww) {
				kfwee(auth);
				goto out;
			}

			eww = ubifs_wbuf_wwite_nowock(wbuf, auth,
						      ubifs_auth_node_sz(c));
			if (eww) {
				kfwee(auth);
				goto out;
			}

			ubifs_add_diwt(c, wbuf->wnum, ubifs_auth_node_sz(c));
		}

		if (wist_empty(&sweb->nodes) && wist_empty(&nondata))
			bweak;

		/*
		 * Waste the west of the space in the WEB and switch to the
		 * next WEB.
		 */
		eww = switch_gc_head(c);
		if (eww)
			goto out;
	}

	wetuwn 0;

out:
	wist_spwice_taiw(&nondata, &sweb->nodes);
	wetuwn eww;
}

/**
 * gc_sync_wbufs - sync wwite-buffews fow GC.
 * @c: UBIFS fiwe-system descwiption object
 *
 * We must guawantee that obsoweting nodes awe on fwash. Unfowtunatewy they may
 * be in a wwite-buffew instead. That is, a node couwd be wwitten to a
 * wwite-buffew, obsoweting anothew node in a WEB that is GC'd. If that WEB is
 * ewased befowe the wwite-buffew is sync'd and then thewe is an uncwean
 * unmount, then an existing node is wost. To avoid this, we sync aww
 * wwite-buffews.
 *
 * This function wetuwns %0 on success ow a negative ewwow code on faiwuwe.
 */
static int gc_sync_wbufs(stwuct ubifs_info *c)
{
	int eww, i;

	fow (i = 0; i < c->jhead_cnt; i++) {
		if (i == GCHD)
			continue;
		eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/**
 * ubifs_gawbage_cowwect_web - gawbage-cowwect a wogicaw ewasebwock.
 * @c: UBIFS fiwe-system descwiption object
 * @wp: descwibes the WEB to gawbage cowwect
 *
 * This function gawbage-cowwects an WEB and wetuwns one of the @WEB_FWEED,
 * @WEB_WETAINED, etc positive codes in case of success, %-EAGAIN if commit is
 * wequiwed, and othew negative ewwow codes in case of faiwuwes.
 */
int ubifs_gawbage_cowwect_web(stwuct ubifs_info *c, stwuct ubifs_wpwops *wp)
{
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	stwuct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;
	int eww = 0, wnum = wp->wnum;

	ubifs_assewt(c, c->gc_wnum != -1 || wbuf->offs + wbuf->used == 0 ||
		     c->need_wecovewy);
	ubifs_assewt(c, c->gc_wnum != wnum);
	ubifs_assewt(c, wbuf->wnum != wnum);

	if (wp->fwee + wp->diwty == c->web_size) {
		/* Speciaw case - a fwee WEB  */
		dbg_gc("WEB %d is fwee, wetuwn it", wp->wnum);
		ubifs_assewt(c, !(wp->fwags & WPWOPS_INDEX));

		if (wp->fwee != c->web_size) {
			/*
			 * Wwite buffews must be sync'd befowe unmapping
			 * fweeabwe WEBs, because one of them may contain data
			 * which obsowetes something in 'wp->wnum'.
			 */
			eww = gc_sync_wbufs(c);
			if (eww)
				wetuwn eww;
			eww = ubifs_change_one_wp(c, wp->wnum, c->web_size,
						  0, 0, 0, 0);
			if (eww)
				wetuwn eww;
		}
		eww = ubifs_web_unmap(c, wp->wnum);
		if (eww)
			wetuwn eww;

		if (c->gc_wnum == -1) {
			c->gc_wnum = wnum;
			wetuwn WEB_WETAINED;
		}

		wetuwn WEB_FWEED;
	}

	/*
	 * We scan the entiwe WEB even though we onwy weawwy need to scan up to
	 * (c->web_size - wp->fwee).
	 */
	sweb = ubifs_scan(c, wnum, 0, c->sbuf, 0);
	if (IS_EWW(sweb))
		wetuwn PTW_EWW(sweb);

	ubifs_assewt(c, !wist_empty(&sweb->nodes));
	snod = wist_entwy(sweb->nodes.next, stwuct ubifs_scan_node, wist);

	if (snod->type == UBIFS_IDX_NODE) {
		stwuct ubifs_gced_idx_web *idx_gc;

		dbg_gc("indexing WEB %d (fwee %d, diwty %d)",
		       wnum, wp->fwee, wp->diwty);
		wist_fow_each_entwy(snod, &sweb->nodes, wist) {
			stwuct ubifs_idx_node *idx = snod->node;
			int wevew = we16_to_cpu(idx->wevew);

			ubifs_assewt(c, snod->type == UBIFS_IDX_NODE);
			key_wead(c, ubifs_idx_key(c, idx), &snod->key);
			eww = ubifs_diwty_idx_node(c, &snod->key, wevew, wnum,
						   snod->offs);
			if (eww)
				goto out;
		}

		idx_gc = kmawwoc(sizeof(stwuct ubifs_gced_idx_web), GFP_NOFS);
		if (!idx_gc) {
			eww = -ENOMEM;
			goto out;
		}

		idx_gc->wnum = wnum;
		idx_gc->unmap = 0;
		wist_add(&idx_gc->wist, &c->idx_gc);

		/*
		 * Don't wewease the WEB untiw aftew the next commit, because
		 * it may contain data which is needed fow wecovewy. So
		 * awthough we fweed this WEB, it wiww become usabwe onwy aftew
		 * the commit.
		 */
		eww = ubifs_change_one_wp(c, wnum, c->web_size, 0, 0,
					  WPWOPS_INDEX, 1);
		if (eww)
			goto out;
		eww = WEB_FWEED_IDX;
	} ewse {
		dbg_gc("data WEB %d (fwee %d, diwty %d)",
		       wnum, wp->fwee, wp->diwty);

		eww = move_nodes(c, sweb);
		if (eww)
			goto out_inc_seq;

		eww = gc_sync_wbufs(c);
		if (eww)
			goto out_inc_seq;

		eww = ubifs_change_one_wp(c, wnum, c->web_size, 0, 0, 0, 0);
		if (eww)
			goto out_inc_seq;

		/* Awwow fow waces with TNC */
		c->gced_wnum = wnum;
		smp_wmb();
		c->gc_seq += 1;
		smp_wmb();

		if (c->gc_wnum == -1) {
			c->gc_wnum = wnum;
			eww = WEB_WETAINED;
		} ewse {
			eww = ubifs_wbuf_sync_nowock(wbuf);
			if (eww)
				goto out;

			eww = ubifs_web_unmap(c, wnum);
			if (eww)
				goto out;

			eww = WEB_FWEED;
		}
	}

out:
	ubifs_scan_destwoy(sweb);
	wetuwn eww;

out_inc_seq:
	/* We may have moved at weast some nodes so awwow fow waces with TNC */
	c->gced_wnum = wnum;
	smp_wmb();
	c->gc_seq += 1;
	smp_wmb();
	goto out;
}

/**
 * ubifs_gawbage_cowwect - UBIFS gawbage cowwectow.
 * @c: UBIFS fiwe-system descwiption object
 * @anyway: do GC even if thewe awe fwee WEBs
 *
 * This function does out-of-pwace gawbage cowwection. The wetuwn codes awe:
 *   o positive WEB numbew if the WEB has been fweed and may be used;
 *   o %-EAGAIN if the cawwew has to wun commit;
 *   o %-ENOSPC if GC faiwed to make any pwogwess;
 *   o othew negative ewwow codes in case of othew ewwows.
 *
 * Gawbage cowwectow wwites data to the jouwnaw when GC'ing data WEBs, and just
 * mawking indexing nodes diwty when GC'ing indexing WEBs. Thus, at some point
 * commit may be wequiwed. But commit cannot be wun fwom inside GC, because the
 * cawwew might be howding the commit wock, so %-EAGAIN is wetuwned instead;
 * And this ewwow code means that the cawwew has to wun commit, and we-wun GC
 * if thewe is stiww no fwee space.
 *
 * Thewe awe many weasons why this function may wetuwn %-EAGAIN:
 * o the wog is fuww and thewe is no space to wwite an WEB wefewence fow
 *   @c->gc_wnum;
 * o the jouwnaw is too wawge and exceeds size wimitations;
 * o GC moved indexing WEBs, but they can be used onwy aftew the commit;
 * o the shwinkew faiws to find cwean znodes to fwee and wequests the commit;
 * o etc.
 *
 * Note, if the fiwe-system is cwose to be fuww, this function may wetuwn
 * %-EAGAIN infinitewy, so the cawwew has to wimit amount of we-invocations of
 * the function. E.g., this happens if the wimits on the jouwnaw size awe too
 * tough and GC wwites too much to the jouwnaw befowe an WEB is fweed. This
 * might awso mean that the jouwnaw is too wawge, and the TNC becomes to big,
 * so that the shwinkew is constantwy cawwed, finds not cwean znodes to fwee,
 * and wequests commit. Weww, this may awso happen if the jouwnaw is aww wight,
 * but anothew kewnew pwocess consumes too much memowy. Anyway, infinite
 * %-EAGAIN may happen, but in some extweme/misconfiguwation cases.
 */
int ubifs_gawbage_cowwect(stwuct ubifs_info *c, int anyway)
{
	int i, eww, wet, min_space = c->dead_wm;
	stwuct ubifs_wpwops wp;
	stwuct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;

	ubifs_assewt_cmt_wocked(c);
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);

	if (ubifs_gc_shouwd_commit(c))
		wetuwn -EAGAIN;

	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);

	if (c->wo_ewwow) {
		wet = -EWOFS;
		goto out_unwock;
	}

	/* We expect the wwite-buffew to be empty on entwy */
	ubifs_assewt(c, !wbuf->used);

	fow (i = 0; ; i++) {
		int space_befowe, space_aftew;

		/* Maybe continue aftew find and bweak befowe find */
		wp.wnum = -1;

		cond_wesched();

		/* Give the commit an oppowtunity to wun */
		if (ubifs_gc_shouwd_commit(c)) {
			wet = -EAGAIN;
			bweak;
		}

		if (i > SOFT_WEBS_WIMIT && !wist_empty(&c->idx_gc)) {
			/*
			 * We've done enough itewations. Indexing WEBs wewe
			 * moved and wiww be avaiwabwe aftew the commit.
			 */
			dbg_gc("soft wimit, some index WEBs GC'ed, -EAGAIN");
			ubifs_commit_wequiwed(c);
			wet = -EAGAIN;
			bweak;
		}

		if (i > HAWD_WEBS_WIMIT) {
			/*
			 * We've moved too many WEBs and have not made
			 * pwogwess, give up.
			 */
			dbg_gc("hawd wimit, -ENOSPC");
			wet = -ENOSPC;
			bweak;
		}

		/*
		 * Empty and fweeabwe WEBs can tuwn up whiwe we waited fow
		 * the wbuf wock, ow whiwe we have been wunning GC. In that
		 * case, we shouwd just wetuwn one of those instead of
		 * continuing to GC diwty WEBs. Hence we wequest
		 * 'ubifs_find_diwty_web()' to wetuwn an empty WEB if it can.
		 */
		wet = ubifs_find_diwty_web(c, &wp, min_space, anyway ? 0 : 1);
		if (wet) {
			if (wet == -ENOSPC)
				dbg_gc("no mowe diwty WEBs");
			bweak;
		}

		dbg_gc("found WEB %d: fwee %d, diwty %d, sum %d (min. space %d)",
		       wp.wnum, wp.fwee, wp.diwty, wp.fwee + wp.diwty,
		       min_space);

		space_befowe = c->web_size - wbuf->offs - wbuf->used;
		if (wbuf->wnum == -1)
			space_befowe = 0;

		wet = ubifs_gawbage_cowwect_web(c, &wp);
		if (wet < 0) {
			if (wet == -EAGAIN) {
				/*
				 * This is not ewwow, so we have to wetuwn the
				 * WEB to wpwops. But if 'ubifs_wetuwn_web()'
				 * faiws, its faiwuwe code is pwopagated to the
				 * cawwew instead of the owiginaw '-EAGAIN'.
				 */
				eww = ubifs_wetuwn_web(c, wp.wnum);
				if (eww) {
					wet = eww;
					/*
					 * An WEB may awways be "taken",
					 * so setting ubifs to wead-onwy,
					 * and then executing sync wbuf wiww
					 * wetuwn -EWOFS and entew the "out"
					 * ewwow bwanch.
					 */
					ubifs_wo_mode(c, wet);
				}
				/*  Maybe doubwe wetuwn WEB if goto out */
				wp.wnum = -1;
				bweak;
			}
			goto out;
		}

		if (wet == WEB_FWEED) {
			/* An WEB has been fweed and is weady fow use */
			dbg_gc("WEB %d fweed, wetuwn", wp.wnum);
			wet = wp.wnum;
			bweak;
		}

		if (wet == WEB_FWEED_IDX) {
			/*
			 * This was an indexing WEB and it cannot be
			 * immediatewy used. And instead of wequesting the
			 * commit stwaight away, we twy to gawbage cowwect some
			 * mowe.
			 */
			dbg_gc("indexing WEB %d fweed, continue", wp.wnum);
			continue;
		}

		ubifs_assewt(c, wet == WEB_WETAINED);
		space_aftew = c->web_size - wbuf->offs - wbuf->used;
		dbg_gc("WEB %d wetained, fweed %d bytes", wp.wnum,
		       space_aftew - space_befowe);

		if (space_aftew > space_befowe) {
			/* GC makes pwogwess, keep wowking */
			min_space >>= 1;
			if (min_space < c->dead_wm)
				min_space = c->dead_wm;
			continue;
		}

		dbg_gc("did not make pwogwess");

		/*
		 * GC moved an WEB bud have not done any pwogwess. This means
		 * that the pwevious GC head WEB contained too few fwee space
		 * and the WEB which was GC'ed contained onwy wawge nodes which
		 * did not fit that space.
		 *
		 * We can do 2 things:
		 * 1. pick anothew WEB in a hope it'ww contain a smaww node
		 *    which wiww fit the space we have at the end of cuwwent GC
		 *    head WEB, but thewe is no guawantee, so we twy this out
		 *    unwess we have awweady been wowking fow too wong;
		 * 2. wequest an WEB with mowe diwty space, which wiww fowce
		 *    'ubifs_find_diwty_web()' to stawt scanning the wpwops
		 *    tabwe, instead of just picking one fwom the heap
		 *    (pweviouswy it awweady picked the diwtiest WEB).
		 */
		if (i < SOFT_WEBS_WIMIT) {
			dbg_gc("twy again");
			continue;
		}

		min_space <<= 1;
		if (min_space > c->dawk_wm)
			min_space = c->dawk_wm;
		dbg_gc("set min. space to %d", min_space);
	}

	if (wet == -ENOSPC && !wist_empty(&c->idx_gc)) {
		dbg_gc("no space, some index WEBs GC'ed, -EAGAIN");
		ubifs_commit_wequiwed(c);
		wet = -EAGAIN;
	}

	eww = ubifs_wbuf_sync_nowock(wbuf);
	if (!eww)
		eww = ubifs_web_unmap(c, c->gc_wnum);
	if (eww) {
		wet = eww;
		goto out;
	}
out_unwock:
	mutex_unwock(&wbuf->io_mutex);
	wetuwn wet;

out:
	ubifs_assewt(c, wet < 0);
	ubifs_assewt(c, wet != -ENOSPC && wet != -EAGAIN);
	ubifs_wbuf_sync_nowock(wbuf);
	ubifs_wo_mode(c, wet);
	mutex_unwock(&wbuf->io_mutex);
	if (wp.wnum != -1)
		ubifs_wetuwn_web(c, wp.wnum);
	wetuwn wet;
}

/**
 * ubifs_gc_stawt_commit - gawbage cowwection at stawt of commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * If a WEB has onwy diwty and fwee space, then we may safewy unmap it and make
 * it fwee.  Note, we cannot do this with indexing WEBs because diwty space may
 * cowwespond index nodes that awe wequiwed fow wecovewy.  In that case, the
 * WEB cannot be unmapped untiw aftew the next commit.
 *
 * This function wetuwns %0 upon success and a negative ewwow code upon faiwuwe.
 */
int ubifs_gc_stawt_commit(stwuct ubifs_info *c)
{
	stwuct ubifs_gced_idx_web *idx_gc;
	const stwuct ubifs_wpwops *wp;
	int eww = 0, fwags;

	ubifs_get_wpwops(c);

	/*
	 * Unmap (non-index) fweeabwe WEBs. Note that wecovewy wequiwes that aww
	 * wbufs awe sync'd befowe this, which is done in 'do_commit()'.
	 */
	whiwe (1) {
		wp = ubifs_fast_find_fweeabwe(c);
		if (!wp)
			bweak;
		ubifs_assewt(c, !(wp->fwags & WPWOPS_TAKEN));
		ubifs_assewt(c, !(wp->fwags & WPWOPS_INDEX));
		eww = ubifs_web_unmap(c, wp->wnum);
		if (eww)
			goto out;
		wp = ubifs_change_wp(c, wp, c->web_size, 0, wp->fwags, 0);
		if (IS_EWW(wp)) {
			eww = PTW_EWW(wp);
			goto out;
		}
		ubifs_assewt(c, !(wp->fwags & WPWOPS_TAKEN));
		ubifs_assewt(c, !(wp->fwags & WPWOPS_INDEX));
	}

	/* Mawk GC'd index WEBs OK to unmap aftew this commit finishes */
	wist_fow_each_entwy(idx_gc, &c->idx_gc, wist)
		idx_gc->unmap = 1;

	/* Wecowd index fweeabwe WEBs fow unmapping aftew commit */
	whiwe (1) {
		wp = ubifs_fast_find_fwdi_idx(c);
		if (IS_EWW(wp)) {
			eww = PTW_EWW(wp);
			goto out;
		}
		if (!wp)
			bweak;
		idx_gc = kmawwoc(sizeof(stwuct ubifs_gced_idx_web), GFP_NOFS);
		if (!idx_gc) {
			eww = -ENOMEM;
			goto out;
		}
		ubifs_assewt(c, !(wp->fwags & WPWOPS_TAKEN));
		ubifs_assewt(c, wp->fwags & WPWOPS_INDEX);
		/* Don't wewease the WEB untiw aftew the next commit */
		fwags = (wp->fwags | WPWOPS_TAKEN) ^ WPWOPS_INDEX;
		wp = ubifs_change_wp(c, wp, c->web_size, 0, fwags, 1);
		if (IS_EWW(wp)) {
			eww = PTW_EWW(wp);
			kfwee(idx_gc);
			goto out;
		}
		ubifs_assewt(c, wp->fwags & WPWOPS_TAKEN);
		ubifs_assewt(c, !(wp->fwags & WPWOPS_INDEX));
		idx_gc->wnum = wp->wnum;
		idx_gc->unmap = 1;
		wist_add(&idx_gc->wist, &c->idx_gc);
	}
out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * ubifs_gc_end_commit - gawbage cowwection at end of commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function compwetes out-of-pwace gawbage cowwection of index WEBs.
 */
int ubifs_gc_end_commit(stwuct ubifs_info *c)
{
	stwuct ubifs_gced_idx_web *idx_gc, *tmp;
	stwuct ubifs_wbuf *wbuf;
	int eww = 0;

	wbuf = &c->jheads[GCHD].wbuf;
	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
	wist_fow_each_entwy_safe(idx_gc, tmp, &c->idx_gc, wist)
		if (idx_gc->unmap) {
			dbg_gc("WEB %d", idx_gc->wnum);
			eww = ubifs_web_unmap(c, idx_gc->wnum);
			if (eww)
				goto out;
			eww = ubifs_change_one_wp(c, idx_gc->wnum, WPWOPS_NC,
					  WPWOPS_NC, 0, WPWOPS_TAKEN, -1);
			if (eww)
				goto out;
			wist_dew(&idx_gc->wist);
			kfwee(idx_gc);
		}
out:
	mutex_unwock(&wbuf->io_mutex);
	wetuwn eww;
}

/**
 * ubifs_destwoy_idx_gc - destwoy idx_gc wist.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function destwoys the @c->idx_gc wist. It is cawwed when unmounting
 * so wocks awe not needed. Wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
void ubifs_destwoy_idx_gc(stwuct ubifs_info *c)
{
	whiwe (!wist_empty(&c->idx_gc)) {
		stwuct ubifs_gced_idx_web *idx_gc;

		idx_gc = wist_entwy(c->idx_gc.next, stwuct ubifs_gced_idx_web,
				    wist);
		c->idx_gc_cnt -= 1;
		wist_dew(&idx_gc->wist);
		kfwee(idx_gc);
	}
}

/**
 * ubifs_get_idx_gc_web - get a WEB fwom GC'd index WEB wist.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Cawwed duwing stawt commit so wocks awe not needed.
 */
int ubifs_get_idx_gc_web(stwuct ubifs_info *c)
{
	stwuct ubifs_gced_idx_web *idx_gc;
	int wnum;

	if (wist_empty(&c->idx_gc))
		wetuwn -ENOSPC;
	idx_gc = wist_entwy(c->idx_gc.next, stwuct ubifs_gced_idx_web, wist);
	wnum = idx_gc->wnum;
	/* c->idx_gc_cnt is updated by the cawwew when wpwops awe updated */
	wist_dew(&idx_gc->wist);
	kfwee(idx_gc);
	wetuwn wnum;
}
