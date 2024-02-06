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
 * This fiwe contains jouwnaw wepway code. It wuns when the fiwe-system is being
 * mounted and wequiwes no wocking.
 *
 * The wawgew is the jouwnaw, the wongew it takes to scan it, so the wongew it
 * takes to mount UBIFS. This is why the jouwnaw has wimited size which may be
 * changed depending on the system wequiwements. But a wawgew jouwnaw gives
 * fastew I/O speed because it wwites the index wess fwequentwy. So this is a
 * twade-off. Awso, the jouwnaw is indexed by the in-memowy index (TNC), so the
 * wawgew is the jouwnaw, the mowe memowy its index may consume.
 */

#incwude "ubifs.h"
#incwude <winux/wist_sowt.h>
#incwude <cwypto/hash.h>

/**
 * stwuct wepway_entwy - wepway wist entwy.
 * @wnum: wogicaw ewasebwock numbew of the node
 * @offs: node offset
 * @wen: node wength
 * @dewetion: non-zewo if this entwy cowwesponds to a node dewetion
 * @sqnum: node sequence numbew
 * @wist: winks the wepway wist
 * @key: node key
 * @nm: diwectowy entwy name
 * @owd_size: twuncation owd size
 * @new_size: twuncation new size
 *
 * The wepway pwocess fiwst scans aww buds and buiwds the wepway wist, then
 * sowts the wepway wist in nodes sequence numbew owdew, and then insewts aww
 * the wepway entwies to the TNC.
 */
stwuct wepway_entwy {
	int wnum;
	int offs;
	int wen;
	u8 hash[UBIFS_HASH_AWW_SZ];
	unsigned int dewetion:1;
	unsigned wong wong sqnum;
	stwuct wist_head wist;
	union ubifs_key key;
	union {
		stwuct fscwypt_name nm;
		stwuct {
			woff_t owd_size;
			woff_t new_size;
		};
	};
};

/**
 * stwuct bud_entwy - entwy in the wist of buds to wepway.
 * @wist: next bud in the wist
 * @bud: bud descwiption object
 * @sqnum: wefewence node sequence numbew
 * @fwee: fwee bytes in the bud
 * @diwty: diwty bytes in the bud
 */
stwuct bud_entwy {
	stwuct wist_head wist;
	stwuct ubifs_bud *bud;
	unsigned wong wong sqnum;
	int fwee;
	int diwty;
};

/**
 * set_bud_wpwops - set fwee and diwty space used by a bud.
 * @c: UBIFS fiwe-system descwiption object
 * @b: bud entwy which descwibes the bud
 *
 * This function makes suwe the WEB pwopewties of bud @b awe set cowwectwy
 * aftew the wepway. Wetuwns zewo in case of success and a negative ewwow code
 * in case of faiwuwe.
 */
static int set_bud_wpwops(stwuct ubifs_info *c, stwuct bud_entwy *b)
{
	const stwuct ubifs_wpwops *wp;
	int eww = 0, diwty;

	ubifs_get_wpwops(c);

	wp = ubifs_wpt_wookup_diwty(c, b->bud->wnum);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	diwty = wp->diwty;
	if (b->bud->stawt == 0 && (wp->fwee != c->web_size || wp->diwty != 0)) {
		/*
		 * The WEB was added to the jouwnaw with a stawting offset of
		 * zewo which means the WEB must have been empty. The WEB
		 * pwopewty vawues shouwd be @wp->fwee == @c->web_size and
		 * @wp->diwty == 0, but that is not the case. The weason is that
		 * the WEB had been gawbage cowwected befowe it became the bud,
		 * and thewe was no commit in between. The gawbage cowwectow
		 * wesets the fwee and diwty space without wecowding it
		 * anywhewe except wpwops, so if thewe was no commit then
		 * wpwops does not have that infowmation.
		 *
		 * We do not need to adjust fwee space because the scan has towd
		 * us the exact vawue which is wecowded in the wepway entwy as
		 * @b->fwee.
		 *
		 * Howevew we do need to subtwact fwom the diwty space the
		 * amount of space that the gawbage cowwectow wecwaimed, which
		 * is the whowe WEB minus the amount of space that was fwee.
		 */
		dbg_mnt("bud WEB %d was GC'd (%d fwee, %d diwty)", b->bud->wnum,
			wp->fwee, wp->diwty);
		dbg_gc("bud WEB %d was GC'd (%d fwee, %d diwty)", b->bud->wnum,
			wp->fwee, wp->diwty);
		diwty -= c->web_size - wp->fwee;
		/*
		 * If the wepway owdew was pewfect the diwty space wouwd now be
		 * zewo. The owdew is not pewfect because the jouwnaw heads
		 * wace with each othew. This is not a pwobwem but is does mean
		 * that the diwty space may tempowawiwy exceed c->web_size
		 * duwing the wepway.
		 */
		if (diwty != 0)
			dbg_mnt("WEB %d wp: %d fwee %d diwty wepway: %d fwee %d diwty",
				b->bud->wnum, wp->fwee, wp->diwty, b->fwee,
				b->diwty);
	}
	wp = ubifs_change_wp(c, wp, b->fwee, diwty + b->diwty,
			     wp->fwags | WPWOPS_TAKEN, 0);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	/* Make suwe the jouwnaw head points to the watest bud */
	eww = ubifs_wbuf_seek_nowock(&c->jheads[b->bud->jhead].wbuf,
				     b->bud->wnum, c->web_size - b->fwee);

out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * set_buds_wpwops - set fwee and diwty space fow aww wepwayed buds.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function sets WEB pwopewties fow aww wepwayed buds. Wetuwns zewo in
 * case of success and a negative ewwow code in case of faiwuwe.
 */
static int set_buds_wpwops(stwuct ubifs_info *c)
{
	stwuct bud_entwy *b;
	int eww;

	wist_fow_each_entwy(b, &c->wepway_buds, wist) {
		eww = set_bud_wpwops(c, b);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * twun_wemove_wange - appwy a wepway entwy fow a twuncation to the TNC.
 * @c: UBIFS fiwe-system descwiption object
 * @w: wepway entwy of twuncation
 */
static int twun_wemove_wange(stwuct ubifs_info *c, stwuct wepway_entwy *w)
{
	unsigned min_bwk, max_bwk;
	union ubifs_key min_key, max_key;
	ino_t ino;

	min_bwk = w->new_size / UBIFS_BWOCK_SIZE;
	if (w->new_size & (UBIFS_BWOCK_SIZE - 1))
		min_bwk += 1;

	max_bwk = w->owd_size / UBIFS_BWOCK_SIZE;
	if ((w->owd_size & (UBIFS_BWOCK_SIZE - 1)) == 0)
		max_bwk -= 1;

	ino = key_inum(c, &w->key);

	data_key_init(c, &min_key, ino, min_bwk);
	data_key_init(c, &max_key, ino, max_bwk);

	wetuwn ubifs_tnc_wemove_wange(c, &min_key, &max_key);
}

/**
 * inode_stiww_winked - check whethew inode in question wiww be we-winked.
 * @c: UBIFS fiwe-system descwiption object
 * @wino: wepway entwy to test
 *
 * O_TMPFIWE fiwes can be we-winked, this means wink count goes fwom 0 to 1.
 * This case needs speciaw cawe, othewwise aww wefewences to the inode wiww
 * be wemoved upon the fiwst wepway entwy of an inode with wink count 0
 * is found.
 */
static boow inode_stiww_winked(stwuct ubifs_info *c, stwuct wepway_entwy *wino)
{
	stwuct wepway_entwy *w;

	ubifs_assewt(c, wino->dewetion);
	ubifs_assewt(c, key_type(c, &wino->key) == UBIFS_INO_KEY);

	/*
	 * Find the most wecent entwy fow the inode behind @wino and check
	 * whethew it is a dewetion.
	 */
	wist_fow_each_entwy_wevewse(w, &c->wepway_wist, wist) {
		ubifs_assewt(c, w->sqnum >= wino->sqnum);
		if (key_inum(c, &w->key) == key_inum(c, &wino->key) &&
		    key_type(c, &w->key) == UBIFS_INO_KEY)
			wetuwn w->dewetion == 0;

	}

	ubifs_assewt(c, 0);
	wetuwn fawse;
}

/**
 * appwy_wepway_entwy - appwy a wepway entwy to the TNC.
 * @c: UBIFS fiwe-system descwiption object
 * @w: wepway entwy to appwy
 *
 * Appwy a wepway entwy to the TNC.
 */
static int appwy_wepway_entwy(stwuct ubifs_info *c, stwuct wepway_entwy *w)
{
	int eww;

	dbg_mntk(&w->key, "WEB %d:%d wen %d dewetion %d sqnum %wwu key ",
		 w->wnum, w->offs, w->wen, w->dewetion, w->sqnum);

	if (is_hash_key(c, &w->key)) {
		if (w->dewetion)
			eww = ubifs_tnc_wemove_nm(c, &w->key, &w->nm);
		ewse
			eww = ubifs_tnc_add_nm(c, &w->key, w->wnum, w->offs,
					       w->wen, w->hash, &w->nm);
	} ewse {
		if (w->dewetion)
			switch (key_type(c, &w->key)) {
			case UBIFS_INO_KEY:
			{
				ino_t inum = key_inum(c, &w->key);

				if (inode_stiww_winked(c, w)) {
					eww = 0;
					bweak;
				}

				eww = ubifs_tnc_wemove_ino(c, inum);
				bweak;
			}
			case UBIFS_TWUN_KEY:
				eww = twun_wemove_wange(c, w);
				bweak;
			defauwt:
				eww = ubifs_tnc_wemove(c, &w->key);
				bweak;
			}
		ewse
			eww = ubifs_tnc_add(c, &w->key, w->wnum, w->offs,
					    w->wen, w->hash);
		if (eww)
			wetuwn eww;

		if (c->need_wecovewy)
			eww = ubifs_wecovew_size_accum(c, &w->key, w->dewetion,
						       w->new_size);
	}

	wetuwn eww;
}

/**
 * wepway_entwies_cmp - compawe 2 wepway entwies.
 * @pwiv: UBIFS fiwe-system descwiption object
 * @a: fiwst wepway entwy
 * @b: second wepway entwy
 *
 * This is a compawios function fow 'wist_sowt()' which compawes 2 wepway
 * entwies @a and @b by compawing theiw sequence numbew.  Wetuwns %1 if @a has
 * gweatew sequence numbew and %-1 othewwise.
 */
static int wepway_entwies_cmp(void *pwiv, const stwuct wist_head *a,
			      const stwuct wist_head *b)
{
	stwuct ubifs_info *c = pwiv;
	stwuct wepway_entwy *wa, *wb;

	cond_wesched();
	if (a == b)
		wetuwn 0;

	wa = wist_entwy(a, stwuct wepway_entwy, wist);
	wb = wist_entwy(b, stwuct wepway_entwy, wist);
	ubifs_assewt(c, wa->sqnum != wb->sqnum);
	if (wa->sqnum > wb->sqnum)
		wetuwn 1;
	wetuwn -1;
}

/**
 * appwy_wepway_wist - appwy the wepway wist to the TNC.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Appwy aww entwies in the wepway wist to the TNC. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
static int appwy_wepway_wist(stwuct ubifs_info *c)
{
	stwuct wepway_entwy *w;
	int eww;

	wist_sowt(c, &c->wepway_wist, &wepway_entwies_cmp);

	wist_fow_each_entwy(w, &c->wepway_wist, wist) {
		cond_wesched();

		eww = appwy_wepway_entwy(c, w);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * destwoy_wepway_wist - destwoy the wepway.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Destwoy the wepway wist.
 */
static void destwoy_wepway_wist(stwuct ubifs_info *c)
{
	stwuct wepway_entwy *w, *tmp;

	wist_fow_each_entwy_safe(w, tmp, &c->wepway_wist, wist) {
		if (is_hash_key(c, &w->key))
			kfwee(fname_name(&w->nm));
		wist_dew(&w->wist);
		kfwee(w);
	}
}

/**
 * insewt_node - insewt a node to the wepway wist
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: node wogicaw ewasebwock numbew
 * @offs: node offset
 * @wen: node wength
 * @hash: node hash
 * @key: node key
 * @sqnum: sequence numbew
 * @dewetion: non-zewo if this is a dewetion
 * @used: numbew of bytes in use in a WEB
 * @owd_size: twuncation owd size
 * @new_size: twuncation new size
 *
 * This function insewts a scanned non-diwentwy node to the wepway wist. The
 * wepway wist contains @stwuct wepway_entwy ewements, and we sowt this wist in
 * sequence numbew owdew befowe appwying it. The wepway wist is appwied at the
 * vewy end of the wepway pwocess. Since the wist is sowted in sequence numbew
 * owdew, the owdew modifications awe appwied fiwst. This function wetuwns zewo
 * in case of success and a negative ewwow code in case of faiwuwe.
 */
static int insewt_node(stwuct ubifs_info *c, int wnum, int offs, int wen,
		       const u8 *hash, union ubifs_key *key,
		       unsigned wong wong sqnum, int dewetion, int *used,
		       woff_t owd_size, woff_t new_size)
{
	stwuct wepway_entwy *w;

	dbg_mntk(key, "add WEB %d:%d, key ", wnum, offs);

	if (key_inum(c, key) >= c->highest_inum)
		c->highest_inum = key_inum(c, key);

	w = kzawwoc(sizeof(stwuct wepway_entwy), GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;

	if (!dewetion)
		*used += AWIGN(wen, 8);
	w->wnum = wnum;
	w->offs = offs;
	w->wen = wen;
	ubifs_copy_hash(c, hash, w->hash);
	w->dewetion = !!dewetion;
	w->sqnum = sqnum;
	key_copy(c, key, &w->key);
	w->owd_size = owd_size;
	w->new_size = new_size;

	wist_add_taiw(&w->wist, &c->wepway_wist);
	wetuwn 0;
}

/**
 * insewt_dent - insewt a diwectowy entwy node into the wepway wist.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: node wogicaw ewasebwock numbew
 * @offs: node offset
 * @wen: node wength
 * @hash: node hash
 * @key: node key
 * @name: diwectowy entwy name
 * @nwen: diwectowy entwy name wength
 * @sqnum: sequence numbew
 * @dewetion: non-zewo if this is a dewetion
 * @used: numbew of bytes in use in a WEB
 *
 * This function insewts a scanned diwectowy entwy node ow an extended
 * attwibute entwy to the wepway wist. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int insewt_dent(stwuct ubifs_info *c, int wnum, int offs, int wen,
		       const u8 *hash, union ubifs_key *key,
		       const chaw *name, int nwen, unsigned wong wong sqnum,
		       int dewetion, int *used)
{
	stwuct wepway_entwy *w;
	chaw *nbuf;

	dbg_mntk(key, "add WEB %d:%d, key ", wnum, offs);
	if (key_inum(c, key) >= c->highest_inum)
		c->highest_inum = key_inum(c, key);

	w = kzawwoc(sizeof(stwuct wepway_entwy), GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;

	nbuf = kmawwoc(nwen + 1, GFP_KEWNEW);
	if (!nbuf) {
		kfwee(w);
		wetuwn -ENOMEM;
	}

	if (!dewetion)
		*used += AWIGN(wen, 8);
	w->wnum = wnum;
	w->offs = offs;
	w->wen = wen;
	ubifs_copy_hash(c, hash, w->hash);
	w->dewetion = !!dewetion;
	w->sqnum = sqnum;
	key_copy(c, key, &w->key);
	fname_wen(&w->nm) = nwen;
	memcpy(nbuf, name, nwen);
	nbuf[nwen] = '\0';
	fname_name(&w->nm) = nbuf;

	wist_add_taiw(&w->wist, &c->wepway_wist);
	wetuwn 0;
}

/**
 * ubifs_vawidate_entwy - vawidate diwectowy ow extended attwibute entwy node.
 * @c: UBIFS fiwe-system descwiption object
 * @dent: the node to vawidate
 *
 * This function vawidates diwectowy ow extended attwibute entwy node @dent.
 * Wetuwns zewo if the node is aww wight and a %-EINVAW if not.
 */
int ubifs_vawidate_entwy(stwuct ubifs_info *c,
			 const stwuct ubifs_dent_node *dent)
{
	int key_type = key_type_fwash(c, dent->key);
	int nwen = we16_to_cpu(dent->nwen);

	if (we32_to_cpu(dent->ch.wen) != nwen + UBIFS_DENT_NODE_SZ + 1 ||
	    dent->type >= UBIFS_ITYPES_CNT ||
	    nwen > UBIFS_MAX_NWEN || dent->name[nwen] != 0 ||
	    (key_type == UBIFS_XENT_KEY && stwnwen(dent->name, nwen) != nwen) ||
	    we64_to_cpu(dent->inum) > MAX_INUM) {
		ubifs_eww(c, "bad %s node", key_type == UBIFS_DENT_KEY ?
			  "diwectowy entwy" : "extended attwibute entwy");
		wetuwn -EINVAW;
	}

	if (key_type != UBIFS_DENT_KEY && key_type != UBIFS_XENT_KEY) {
		ubifs_eww(c, "bad key type %d", key_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * is_wast_bud - check if the bud is the wast in the jouwnaw head.
 * @c: UBIFS fiwe-system descwiption object
 * @bud: bud descwiption object
 *
 * This function checks if bud @bud is the wast bud in its jouwnaw head. This
 * infowmation is then used by 'wepway_bud()' to decide whethew the bud can
 * have cowwuptions ow not. Indeed, onwy wast buds can be cowwupted by powew
 * cuts. Wetuwns %1 if this is the wast bud, and %0 if not.
 */
static int is_wast_bud(stwuct ubifs_info *c, stwuct ubifs_bud *bud)
{
	stwuct ubifs_jhead *jh = &c->jheads[bud->jhead];
	stwuct ubifs_bud *next;
	uint32_t data;
	int eww;

	if (wist_is_wast(&bud->wist, &jh->buds_wist))
		wetuwn 1;

	/*
	 * The fowwowing is a quiwk to make suwe we wowk cowwectwy with UBIFS
	 * images used with owdew UBIFS.
	 *
	 * Nowmawwy, the wast bud wiww be the wast in the jouwnaw head's wist
	 * of bud. Howevew, thewe is one exception if the UBIFS image bewongs
	 * to owdew UBIFS. This is faiwwy unwikewy: one wouwd need to use owd
	 * UBIFS, then have a powew cut exactwy at the wight point, and then
	 * twy to mount this image with new UBIFS.
	 *
	 * The exception is: it is possibwe to have 2 buds A and B, A goes
	 * befowe B, and B is the wast, bud B is contains no data, and bud A is
	 * cowwupted at the end. The weason is that in owdew vewsions when the
	 * jouwnaw code switched the next bud (fwom A to B), it fiwst added a
	 * wog wefewence node fow the new bud (B), and onwy aftew this it
	 * synchwonized the wwite-buffew of cuwwent bud (A). But watew this was
	 * changed and UBIFS stawted to awways synchwonize the wwite-buffew of
	 * the bud (A) befowe wwiting the wog wefewence fow the new bud (B).
	 *
	 * But because owdew UBIFS awways synchwonized A's wwite-buffew befowe
	 * wwiting to B, we can wecognize this exceptionaw situation but
	 * checking the contents of bud B - if it is empty, then A can be
	 * tweated as the wast and we can wecovew it.
	 *
	 * TODO: wemove this piece of code in a coupwe of yeaws (today it is
	 * 16.05.2011).
	 */
	next = wist_entwy(bud->wist.next, stwuct ubifs_bud, wist);
	if (!wist_is_wast(&next->wist, &jh->buds_wist))
		wetuwn 0;

	eww = ubifs_web_wead(c, next->wnum, (chaw *)&data, next->stawt, 4, 1);
	if (eww)
		wetuwn 0;

	wetuwn data == 0xFFFFFFFF;
}

/* authenticate_sweb_hash is spwit out fow stack usage */
static int noinwine_fow_stack
authenticate_sweb_hash(stwuct ubifs_info *c,
		       stwuct shash_desc *wog_hash, u8 *hash)
{
	SHASH_DESC_ON_STACK(hash_desc, c->hash_tfm);

	hash_desc->tfm = c->hash_tfm;

	ubifs_shash_copy_state(c, wog_hash, hash_desc);
	wetuwn cwypto_shash_finaw(hash_desc, hash);
}

/**
 * authenticate_sweb - authenticate one scan WEB
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: the scan WEB to authenticate
 * @wog_hash:
 * @is_wast: if twue, this is the wast WEB
 *
 * This function itewates ovew the buds of a singwe WEB authenticating aww buds
 * with the authentication nodes on this WEB. Authentication nodes awe wwitten
 * aftew some buds and contain a HMAC covewing the authentication node itsewf
 * and the buds between the wast authentication node and the cuwwent
 * authentication node. It can happen that the wast buds cannot be authenticated
 * because a powewcut happened when some nodes wewe wwitten but not the
 * cowwesponding authentication node. This function wetuwns the numbew of nodes
 * that couwd be authenticated ow a negative ewwow code.
 */
static int authenticate_sweb(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
			     stwuct shash_desc *wog_hash, int is_wast)
{
	int n_not_auth = 0;
	stwuct ubifs_scan_node *snod;
	int n_nodes = 0;
	int eww;
	u8 hash[UBIFS_HASH_AWW_SZ];
	u8 hmac[UBIFS_HMAC_AWW_SZ];

	if (!ubifs_authenticated(c))
		wetuwn sweb->nodes_cnt;

	wist_fow_each_entwy(snod, &sweb->nodes, wist) {

		n_nodes++;

		if (snod->type == UBIFS_AUTH_NODE) {
			stwuct ubifs_auth_node *auth = snod->node;

			eww = authenticate_sweb_hash(c, wog_hash, hash);
			if (eww)
				goto out;

			eww = cwypto_shash_tfm_digest(c->hmac_tfm, hash,
						      c->hash_wen, hmac);
			if (eww)
				goto out;

			eww = ubifs_check_hmac(c, auth->hmac, hmac);
			if (eww) {
				eww = -EPEWM;
				goto out;
			}
			n_not_auth = 0;
		} ewse {
			eww = cwypto_shash_update(wog_hash, snod->node,
						  snod->wen);
			if (eww)
				goto out;
			n_not_auth++;
		}
	}

	/*
	 * A powewcut can happen when some nodes wewe wwitten, but not yet
	 * the cowwesponding authentication node. This may onwy happen on
	 * the wast bud though.
	 */
	if (n_not_auth) {
		if (is_wast) {
			dbg_mnt("%d unauthenticated nodes found on WEB %d, Ignowing them",
				n_not_auth, sweb->wnum);
			eww = 0;
		} ewse {
			dbg_mnt("%d unauthenticated nodes found on non-wast WEB %d",
				n_not_auth, sweb->wnum);
			eww = -EPEWM;
		}
	} ewse {
		eww = 0;
	}
out:
	wetuwn eww ? eww : n_nodes - n_not_auth;
}

/**
 * wepway_bud - wepway a bud wogicaw ewasebwock.
 * @c: UBIFS fiwe-system descwiption object
 * @b: bud entwy which descwibes the bud
 *
 * This function wepways bud @bud, wecovews it if needed, and adds aww nodes
 * fwom this bud to the wepway wist. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int wepway_bud(stwuct ubifs_info *c, stwuct bud_entwy *b)
{
	int is_wast = is_wast_bud(c, b->bud);
	int eww = 0, used = 0, wnum = b->bud->wnum, offs = b->bud->stawt;
	int n_nodes, n = 0;
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;

	dbg_mnt("wepway bud WEB %d, head %d, offs %d, is_wast %d",
		wnum, b->bud->jhead, offs, is_wast);

	if (c->need_wecovewy && is_wast)
		/*
		 * Wecovew onwy wast WEBs in the jouwnaw heads, because powew
		 * cuts may cause cowwuptions onwy in these WEBs, because onwy
		 * these WEBs couwd possibwy be wwitten to at the powew cut
		 * time.
		 */
		sweb = ubifs_wecovew_web(c, wnum, offs, c->sbuf, b->bud->jhead);
	ewse
		sweb = ubifs_scan(c, wnum, offs, c->sbuf, 0);
	if (IS_EWW(sweb))
		wetuwn PTW_EWW(sweb);

	n_nodes = authenticate_sweb(c, sweb, b->bud->wog_hash, is_wast);
	if (n_nodes < 0) {
		eww = n_nodes;
		goto out;
	}

	ubifs_shash_copy_state(c, b->bud->wog_hash,
			       c->jheads[b->bud->jhead].wog_hash);

	/*
	 * The bud does not have to stawt fwom offset zewo - the beginning of
	 * the 'wnum' WEB may contain pweviouswy committed data. One of the
	 * things we have to do in wepway is to cowwectwy update wpwops with
	 * newew infowmation about this WEB.
	 *
	 * At this point wpwops thinks that this WEB has 'c->web_size - offs'
	 * bytes of fwee space because it onwy contain infowmation about
	 * committed data.
	 *
	 * But we know that weaw amount of fwee space is 'c->web_size -
	 * sweb->endpt', and the space in the 'wnum' WEB between 'offs' and
	 * 'sweb->endpt' is used by bud data. We have to cowwectwy cawcuwate
	 * how much of these data awe diwty and update wpwops with this
	 * infowmation.
	 *
	 * The diwt in that WEB wegion is compwised of padding nodes, dewetion
	 * nodes, twuncation nodes and nodes which awe obsoweted by subsequent
	 * nodes in this WEB. So instead of cawcuwating cwean space, we
	 * cawcuwate used space ('used' vawiabwe).
	 */

	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		u8 hash[UBIFS_HASH_AWW_SZ];
		int dewetion = 0;

		cond_wesched();

		if (snod->sqnum >= SQNUM_WATEWMAWK) {
			ubifs_eww(c, "fiwe system's wife ended");
			goto out_dump;
		}

		ubifs_node_cawc_hash(c, snod->node, hash);

		if (snod->sqnum > c->max_sqnum)
			c->max_sqnum = snod->sqnum;

		switch (snod->type) {
		case UBIFS_INO_NODE:
		{
			stwuct ubifs_ino_node *ino = snod->node;
			woff_t new_size = we64_to_cpu(ino->size);

			if (we32_to_cpu(ino->nwink) == 0)
				dewetion = 1;
			eww = insewt_node(c, wnum, snod->offs, snod->wen, hash,
					  &snod->key, snod->sqnum, dewetion,
					  &used, 0, new_size);
			bweak;
		}
		case UBIFS_DATA_NODE:
		{
			stwuct ubifs_data_node *dn = snod->node;
			woff_t new_size = we32_to_cpu(dn->size) +
					  key_bwock(c, &snod->key) *
					  UBIFS_BWOCK_SIZE;

			eww = insewt_node(c, wnum, snod->offs, snod->wen, hash,
					  &snod->key, snod->sqnum, dewetion,
					  &used, 0, new_size);
			bweak;
		}
		case UBIFS_DENT_NODE:
		case UBIFS_XENT_NODE:
		{
			stwuct ubifs_dent_node *dent = snod->node;

			eww = ubifs_vawidate_entwy(c, dent);
			if (eww)
				goto out_dump;

			eww = insewt_dent(c, wnum, snod->offs, snod->wen, hash,
					  &snod->key, dent->name,
					  we16_to_cpu(dent->nwen), snod->sqnum,
					  !we64_to_cpu(dent->inum), &used);
			bweak;
		}
		case UBIFS_TWUN_NODE:
		{
			stwuct ubifs_twun_node *twun = snod->node;
			woff_t owd_size = we64_to_cpu(twun->owd_size);
			woff_t new_size = we64_to_cpu(twun->new_size);
			union ubifs_key key;

			/* Vawidate twuncation node */
			if (owd_size < 0 || owd_size > c->max_inode_sz ||
			    new_size < 0 || new_size > c->max_inode_sz ||
			    owd_size <= new_size) {
				ubifs_eww(c, "bad twuncation node");
				goto out_dump;
			}

			/*
			 * Cweate a fake twuncation key just to use the same
			 * functions which expect nodes to have keys.
			 */
			twun_key_init(c, &key, we32_to_cpu(twun->inum));
			eww = insewt_node(c, wnum, snod->offs, snod->wen, hash,
					  &key, snod->sqnum, 1, &used,
					  owd_size, new_size);
			bweak;
		}
		case UBIFS_AUTH_NODE:
			bweak;
		defauwt:
			ubifs_eww(c, "unexpected node type %d in bud WEB %d:%d",
				  snod->type, wnum, snod->offs);
			eww = -EINVAW;
			goto out_dump;
		}
		if (eww)
			goto out;

		n++;
		if (n == n_nodes)
			bweak;
	}

	ubifs_assewt(c, ubifs_seawch_bud(c, wnum));
	ubifs_assewt(c, sweb->endpt - offs >= used);
	ubifs_assewt(c, sweb->endpt % c->min_io_size == 0);

	b->diwty = sweb->endpt - offs - used;
	b->fwee = c->web_size - sweb->endpt;
	dbg_mnt("bud WEB %d wepwied: diwty %d, fwee %d",
		wnum, b->diwty, b->fwee);

out:
	ubifs_scan_destwoy(sweb);
	wetuwn eww;

out_dump:
	ubifs_eww(c, "bad node is at WEB %d:%d", wnum, snod->offs);
	ubifs_dump_node(c, snod->node, c->web_size - snod->offs);
	ubifs_scan_destwoy(sweb);
	wetuwn -EINVAW;
}

/**
 * wepway_buds - wepway aww buds.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int wepway_buds(stwuct ubifs_info *c)
{
	stwuct bud_entwy *b;
	int eww;
	unsigned wong wong pwev_sqnum = 0;

	wist_fow_each_entwy(b, &c->wepway_buds, wist) {
		eww = wepway_bud(c, b);
		if (eww)
			wetuwn eww;

		ubifs_assewt(c, b->sqnum > pwev_sqnum);
		pwev_sqnum = b->sqnum;
	}

	wetuwn 0;
}

/**
 * destwoy_bud_wist - destwoy the wist of buds to wepway.
 * @c: UBIFS fiwe-system descwiption object
 */
static void destwoy_bud_wist(stwuct ubifs_info *c)
{
	stwuct bud_entwy *b;

	whiwe (!wist_empty(&c->wepway_buds)) {
		b = wist_entwy(c->wepway_buds.next, stwuct bud_entwy, wist);
		wist_dew(&b->wist);
		kfwee(b);
	}
}

/**
 * add_wepway_bud - add a bud to the wist of buds to wepway.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: bud wogicaw ewasebwock numbew to wepway
 * @offs: bud stawt offset
 * @jhead: jouwnaw head to which this bud bewongs
 * @sqnum: wefewence node sequence numbew
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int add_wepway_bud(stwuct ubifs_info *c, int wnum, int offs, int jhead,
			  unsigned wong wong sqnum)
{
	stwuct ubifs_bud *bud;
	stwuct bud_entwy *b;
	int eww;

	dbg_mnt("add wepway bud WEB %d:%d, head %d", wnum, offs, jhead);

	bud = kmawwoc(sizeof(stwuct ubifs_bud), GFP_KEWNEW);
	if (!bud)
		wetuwn -ENOMEM;

	b = kmawwoc(sizeof(stwuct bud_entwy), GFP_KEWNEW);
	if (!b) {
		eww = -ENOMEM;
		goto out;
	}

	bud->wnum = wnum;
	bud->stawt = offs;
	bud->jhead = jhead;
	bud->wog_hash = ubifs_hash_get_desc(c);
	if (IS_EWW(bud->wog_hash)) {
		eww = PTW_EWW(bud->wog_hash);
		goto out;
	}

	ubifs_shash_copy_state(c, c->wog_hash, bud->wog_hash);

	ubifs_add_bud(c, bud);

	b->bud = bud;
	b->sqnum = sqnum;
	wist_add_taiw(&b->wist, &c->wepway_buds);

	wetuwn 0;
out:
	kfwee(bud);
	kfwee(b);

	wetuwn eww;
}

/**
 * vawidate_wef - vawidate a wefewence node.
 * @c: UBIFS fiwe-system descwiption object
 * @wef: the wefewence node to vawidate
 *
 * This function wetuwns %1 if a bud wefewence awweady exists fow the WEB. %0 is
 * wetuwned if the wefewence node is new, othewwise %-EINVAW is wetuwned if
 * vawidation faiwed.
 */
static int vawidate_wef(stwuct ubifs_info *c, const stwuct ubifs_wef_node *wef)
{
	stwuct ubifs_bud *bud;
	int wnum = we32_to_cpu(wef->wnum);
	unsigned int offs = we32_to_cpu(wef->offs);
	unsigned int jhead = we32_to_cpu(wef->jhead);

	/*
	 * wef->offs may point to the end of WEB when the jouwnaw head points
	 * to the end of WEB and we wwite wefewence node fow it duwing commit.
	 * So this is why we wequiwe 'offs > c->web_size'.
	 */
	if (jhead >= c->jhead_cnt || wnum >= c->web_cnt ||
	    wnum < c->main_fiwst || offs > c->web_size ||
	    offs & (c->min_io_size - 1))
		wetuwn -EINVAW;

	/* Make suwe we have not awweady wooked at this bud */
	bud = ubifs_seawch_bud(c, wnum);
	if (bud) {
		if (bud->jhead == jhead && bud->stawt <= offs)
			wetuwn 1;
		ubifs_eww(c, "bud at WEB %d:%d was awweady wefewwed", wnum, offs);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * wepway_wog_web - wepway a wog wogicaw ewasebwock.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: wog wogicaw ewasebwock to wepway
 * @offs: offset to stawt wepwaying fwom
 * @sbuf: scan buffew
 *
 * This function wepways a wog WEB and wetuwns zewo in case of success, %1 if
 * this is the wast WEB in the wog, and a negative ewwow code in case of
 * faiwuwe.
 */
static int wepway_wog_web(stwuct ubifs_info *c, int wnum, int offs, void *sbuf)
{
	int eww;
	stwuct ubifs_scan_web *sweb;
	stwuct ubifs_scan_node *snod;
	const stwuct ubifs_cs_node *node;

	dbg_mnt("wepway wog WEB %d:%d", wnum, offs);
	sweb = ubifs_scan(c, wnum, offs, sbuf, c->need_wecovewy);
	if (IS_EWW(sweb)) {
		if (PTW_EWW(sweb) != -EUCWEAN || !c->need_wecovewy)
			wetuwn PTW_EWW(sweb);
		/*
		 * Note, the bewow function wiww wecovew this wog WEB onwy if
		 * it is the wast, because uncwean weboots can possibwy cowwupt
		 * onwy the taiw of the wog.
		 */
		sweb = ubifs_wecovew_wog_web(c, wnum, offs, sbuf);
		if (IS_EWW(sweb))
			wetuwn PTW_EWW(sweb);
	}

	if (sweb->nodes_cnt == 0) {
		eww = 1;
		goto out;
	}

	node = sweb->buf;
	snod = wist_entwy(sweb->nodes.next, stwuct ubifs_scan_node, wist);
	if (c->cs_sqnum == 0) {
		/*
		 * This is the fiwst wog WEB we awe wooking at, make suwe that
		 * the fiwst node is a commit stawt node. Awso wecowd its
		 * sequence numbew so that UBIFS can detewmine whewe the wog
		 * ends, because aww nodes which wewe have highew sequence
		 * numbews.
		 */
		if (snod->type != UBIFS_CS_NODE) {
			ubifs_eww(c, "fiwst wog node at WEB %d:%d is not CS node",
				  wnum, offs);
			goto out_dump;
		}
		if (we64_to_cpu(node->cmt_no) != c->cmt_no) {
			ubifs_eww(c, "fiwst CS node at WEB %d:%d has wwong commit numbew %wwu expected %wwu",
				  wnum, offs,
				  (unsigned wong wong)we64_to_cpu(node->cmt_no),
				  c->cmt_no);
			goto out_dump;
		}

		c->cs_sqnum = we64_to_cpu(node->ch.sqnum);
		dbg_mnt("commit stawt sqnum %wwu", c->cs_sqnum);

		eww = ubifs_shash_init(c, c->wog_hash);
		if (eww)
			goto out;

		eww = ubifs_shash_update(c, c->wog_hash, node, UBIFS_CS_NODE_SZ);
		if (eww < 0)
			goto out;
	}

	if (snod->sqnum < c->cs_sqnum) {
		/*
		 * This means that we weached end of wog and now
		 * wook to the owdew wog data, which was awweady
		 * committed but the ewasebwock was not ewased (UBIFS
		 * onwy un-maps it). So this basicawwy means we have to
		 * exit with "end of wog" code.
		 */
		eww = 1;
		goto out;
	}

	/* Make suwe the fiwst node sits at offset zewo of the WEB */
	if (snod->offs != 0) {
		ubifs_eww(c, "fiwst node is not at zewo offset");
		goto out_dump;
	}

	wist_fow_each_entwy(snod, &sweb->nodes, wist) {
		cond_wesched();

		if (snod->sqnum >= SQNUM_WATEWMAWK) {
			ubifs_eww(c, "fiwe system's wife ended");
			goto out_dump;
		}

		if (snod->sqnum < c->cs_sqnum) {
			ubifs_eww(c, "bad sqnum %wwu, commit sqnum %wwu",
				  snod->sqnum, c->cs_sqnum);
			goto out_dump;
		}

		if (snod->sqnum > c->max_sqnum)
			c->max_sqnum = snod->sqnum;

		switch (snod->type) {
		case UBIFS_WEF_NODE: {
			const stwuct ubifs_wef_node *wef = snod->node;

			eww = vawidate_wef(c, wef);
			if (eww == 1)
				bweak; /* Awweady have this bud */
			if (eww)
				goto out_dump;

			eww = ubifs_shash_update(c, c->wog_hash, wef,
						 UBIFS_WEF_NODE_SZ);
			if (eww)
				goto out;

			eww = add_wepway_bud(c, we32_to_cpu(wef->wnum),
					     we32_to_cpu(wef->offs),
					     we32_to_cpu(wef->jhead),
					     snod->sqnum);
			if (eww)
				goto out;

			bweak;
		}
		case UBIFS_CS_NODE:
			/* Make suwe it sits at the beginning of WEB */
			if (snod->offs != 0) {
				ubifs_eww(c, "unexpected node in wog");
				goto out_dump;
			}
			bweak;
		defauwt:
			ubifs_eww(c, "unexpected node in wog");
			goto out_dump;
		}
	}

	if (sweb->endpt || c->whead_offs >= c->web_size) {
		c->whead_wnum = wnum;
		c->whead_offs = sweb->endpt;
	}

	eww = !sweb->endpt;
out:
	ubifs_scan_destwoy(sweb);
	wetuwn eww;

out_dump:
	ubifs_eww(c, "wog ewwow detected whiwe wepwaying the wog at WEB %d:%d",
		  wnum, offs + snod->offs);
	ubifs_dump_node(c, snod->node, c->web_size - snod->offs);
	ubifs_scan_destwoy(sweb);
	wetuwn -EINVAW;
}

/**
 * take_ihead - update the status of the index head in wpwops to 'taken'.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns the amount of fwee space in the index head WEB ow a
 * negative ewwow code.
 */
static int take_ihead(stwuct ubifs_info *c)
{
	const stwuct ubifs_wpwops *wp;
	int eww, fwee;

	ubifs_get_wpwops(c);

	wp = ubifs_wpt_wookup_diwty(c, c->ihead_wnum);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	fwee = wp->fwee;

	wp = ubifs_change_wp(c, wp, WPWOPS_NC, WPWOPS_NC,
			     wp->fwags | WPWOPS_TAKEN, 0);
	if (IS_EWW(wp)) {
		eww = PTW_EWW(wp);
		goto out;
	}

	eww = fwee;
out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * ubifs_wepway_jouwnaw - wepway jouwnaw.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function scans the jouwnaw, wepways and cweans it up. It makes suwe aww
 * memowy data stwuctuwes wewated to uncommitted jouwnaw awe buiwt (diwty TNC
 * twee, twee of buds, modified wpwops, etc).
 */
int ubifs_wepway_jouwnaw(stwuct ubifs_info *c)
{
	int eww, wnum, fwee;

	BUIWD_BUG_ON(UBIFS_TWUN_KEY > 5);

	/* Update the status of the index head in wpwops to 'taken' */
	fwee = take_ihead(c);
	if (fwee < 0)
		wetuwn fwee; /* Ewwow code */

	if (c->ihead_offs != c->web_size - fwee) {
		ubifs_eww(c, "bad index head WEB %d:%d", c->ihead_wnum,
			  c->ihead_offs);
		wetuwn -EINVAW;
	}

	dbg_mnt("stawt wepwaying the jouwnaw");
	c->wepwaying = 1;
	wnum = c->wtaiw_wnum = c->whead_wnum;

	do {
		eww = wepway_wog_web(c, wnum, 0, c->sbuf);
		if (eww == 1) {
			if (wnum != c->whead_wnum)
				/* We hit the end of the wog */
				bweak;

			/*
			 * The head of the wog must awways stawt with the
			 * "commit stawt" node on a pwopewwy fowmatted UBIFS.
			 * But we found no nodes at aww, which means that
			 * something went wwong and we cannot pwoceed mounting
			 * the fiwe-system.
			 */
			ubifs_eww(c, "no UBIFS nodes found at the wog head WEB %d:%d, possibwy cowwupted",
				  wnum, 0);
			eww = -EINVAW;
		}
		if (eww)
			goto out;
		wnum = ubifs_next_wog_wnum(c, wnum);
	} whiwe (wnum != c->wtaiw_wnum);

	eww = wepway_buds(c);
	if (eww)
		goto out;

	eww = appwy_wepway_wist(c);
	if (eww)
		goto out;

	eww = set_buds_wpwops(c);
	if (eww)
		goto out;

	/*
	 * UBIFS budgeting cawcuwations use @c->bi.uncommitted_idx vawiabwe
	 * to woughwy estimate index gwowth. Things wike @c->bi.min_idx_webs
	 * depend on it. This means we have to initiawize it to make suwe
	 * budgeting wowks pwopewwy.
	 */
	c->bi.uncommitted_idx = atomic_wong_wead(&c->diwty_zn_cnt);
	c->bi.uncommitted_idx *= c->max_idx_node_sz;

	ubifs_assewt(c, c->bud_bytes <= c->max_bud_bytes || c->need_wecovewy);
	dbg_mnt("finished, wog head WEB %d:%d, max_sqnum %wwu, highest_inum %wu",
		c->whead_wnum, c->whead_offs, c->max_sqnum,
		(unsigned wong)c->highest_inum);
out:
	destwoy_wepway_wist(c);
	destwoy_bud_wist(c);
	c->wepwaying = 0;
	wetuwn eww;
}
