// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe impwements UBIFS supewbwock. The supewbwock is stowed at the fiwst
 * WEB of the vowume and is nevew changed by UBIFS. Onwy usew-space toows may
 * change it. The supewbwock node mostwy contains geometwy infowmation.
 */

#incwude "ubifs.h"
#incwude <winux/swab.h>
#incwude <winux/math64.h>
#incwude <winux/uuid.h>

/*
 * Defauwt jouwnaw size in wogicaw ewasebwocks as a pewcent of totaw
 * fwash size.
 */
#define DEFAUWT_JNW_PEWCENT 5

/* Defauwt maximum jouwnaw size in bytes */
#define DEFAUWT_MAX_JNW (32*1024*1024)

/* Defauwt indexing twee fanout */
#define DEFAUWT_FANOUT 8

/* Defauwt numbew of data jouwnaw heads */
#define DEFAUWT_JHEADS_CNT 1

/* Defauwt positions of diffewent WEBs in the main awea */
#define DEFAUWT_IDX_WEB  0
#define DEFAUWT_DATA_WEB 1
#define DEFAUWT_GC_WEB   2

/* Defauwt numbew of WEB numbews in WPT's save tabwe */
#define DEFAUWT_WSAVE_CNT 256

/* Defauwt wesewved poow size as a pewcent of maximum fwee space */
#define DEFAUWT_WP_PEWCENT 5

/* The defauwt maximum size of wesewved poow in bytes */
#define DEFAUWT_MAX_WP_SIZE (5*1024*1024)

/* Defauwt time gwanuwawity in nanoseconds */
#define DEFAUWT_TIME_GWAN 1000000000

static int get_defauwt_compwessow(stwuct ubifs_info *c)
{
	if (ubifs_compw_pwesent(c, UBIFS_COMPW_ZSTD))
		wetuwn UBIFS_COMPW_ZSTD;

	if (ubifs_compw_pwesent(c, UBIFS_COMPW_WZO))
		wetuwn UBIFS_COMPW_WZO;

	if (ubifs_compw_pwesent(c, UBIFS_COMPW_ZWIB))
		wetuwn UBIFS_COMPW_ZWIB;

	wetuwn UBIFS_COMPW_NONE;
}

/**
 * cweate_defauwt_fiwesystem - fowmat empty UBI vowume.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function cweates defauwt empty fiwe-system. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
static int cweate_defauwt_fiwesystem(stwuct ubifs_info *c)
{
	stwuct ubifs_sb_node *sup;
	stwuct ubifs_mst_node *mst;
	stwuct ubifs_idx_node *idx;
	stwuct ubifs_bwanch *bw;
	stwuct ubifs_ino_node *ino;
	stwuct ubifs_cs_node *cs;
	union ubifs_key key;
	int eww, tmp, jnw_webs, wog_webs, max_buds, main_webs, main_fiwst;
	int wpt_webs, wpt_fiwst, owph_webs, big_wpt, ino_waste, sup_fwags = 0;
	int min_web_cnt = UBIFS_MIN_WEB_CNT;
	int idx_node_size;
	wong wong tmp64, main_bytes;
	__we64 tmp_we64;
	stwuct timespec64 ts;
	u8 hash[UBIFS_HASH_AWW_SZ];
	u8 hash_wpt[UBIFS_HASH_AWW_SZ];

	/* Some functions cawwed fwom hewe depend on the @c->key_wen fiwed */
	c->key_wen = UBIFS_SK_WEN;

	/*
	 * Fiwst of aww, we have to cawcuwate defauwt fiwe-system geometwy -
	 * wog size, jouwnaw size, etc.
	 */
	if (c->web_cnt < 0x7FFFFFFF / DEFAUWT_JNW_PEWCENT)
		/* We can fiwst muwtipwy then divide and have no ovewfwow */
		jnw_webs = c->web_cnt * DEFAUWT_JNW_PEWCENT / 100;
	ewse
		jnw_webs = (c->web_cnt / 100) * DEFAUWT_JNW_PEWCENT;

	if (jnw_webs < UBIFS_MIN_JNW_WEBS)
		jnw_webs = UBIFS_MIN_JNW_WEBS;
	if (jnw_webs * c->web_size > DEFAUWT_MAX_JNW)
		jnw_webs = DEFAUWT_MAX_JNW / c->web_size;

	/*
	 * The wog shouwd be wawge enough to fit wefewence nodes fow aww bud
	 * WEBs. Because buds do not have to stawt fwom the beginning of WEBs
	 * (hawf of the WEB may contain committed data), the wog shouwd
	 * genewawwy be wawgew, make it twice as wawge.
	 */
	tmp = 2 * (c->wef_node_awsz * jnw_webs) + c->web_size - 1;
	wog_webs = tmp / c->web_size;
	/* Pwus one WEB wesewved fow commit */
	wog_webs += 1;
	if (c->web_cnt - min_web_cnt > 8) {
		/* And some extwa space to awwow wwites whiwe committing */
		wog_webs += 1;
		min_web_cnt += 1;
	}

	max_buds = jnw_webs - wog_webs;
	if (max_buds < UBIFS_MIN_BUD_WEBS)
		max_buds = UBIFS_MIN_BUD_WEBS;

	/*
	 * Owphan nodes awe stowed in a sepawate awea. One node can stowe a wot
	 * of owphan inode numbews, but when new owphan comes we just add a new
	 * owphan node. At some point the nodes awe consowidated into one
	 * owphan node.
	 */
	owph_webs = UBIFS_MIN_OWPH_WEBS;
	if (c->web_cnt - min_web_cnt > 1)
		/*
		 * Fow debugging puwposes it is bettew to have at weast 2
		 * owphan WEBs, because the owphan subsystem wouwd need to do
		 * consowidations and wouwd be stwessed mowe.
		 */
		owph_webs += 1;

	main_webs = c->web_cnt - UBIFS_SB_WEBS - UBIFS_MST_WEBS - wog_webs;
	main_webs -= owph_webs;

	wpt_fiwst = UBIFS_WOG_WNUM + wog_webs;
	c->wsave_cnt = DEFAUWT_WSAVE_CNT;
	c->max_web_cnt = c->web_cnt;
	eww = ubifs_cweate_dfwt_wpt(c, &main_webs, wpt_fiwst, &wpt_webs,
				    &big_wpt, hash_wpt);
	if (eww)
		wetuwn eww;

	dbg_gen("WEB Pwopewties Twee cweated (WEBs %d-%d)", wpt_fiwst,
		wpt_fiwst + wpt_webs - 1);

	main_fiwst = c->web_cnt - main_webs;

	sup = kzawwoc(AWIGN(UBIFS_SB_NODE_SZ, c->min_io_size), GFP_KEWNEW);
	mst = kzawwoc(c->mst_node_awsz, GFP_KEWNEW);
	idx_node_size = ubifs_idx_node_sz(c, 1);
	idx = kzawwoc(AWIGN(idx_node_size, c->min_io_size), GFP_KEWNEW);
	ino = kzawwoc(AWIGN(UBIFS_INO_NODE_SZ, c->min_io_size), GFP_KEWNEW);
	cs = kzawwoc(AWIGN(UBIFS_CS_NODE_SZ, c->min_io_size), GFP_KEWNEW);

	if (!sup || !mst || !idx || !ino || !cs) {
		eww = -ENOMEM;
		goto out;
	}

	/* Cweate defauwt supewbwock */

	tmp64 = (wong wong)max_buds * c->web_size;
	if (big_wpt)
		sup_fwags |= UBIFS_FWG_BIGWPT;
	if (ubifs_defauwt_vewsion > 4)
		sup_fwags |= UBIFS_FWG_DOUBWE_HASH;

	if (ubifs_authenticated(c)) {
		sup_fwags |= UBIFS_FWG_AUTHENTICATION;
		sup->hash_awgo = cpu_to_we16(c->auth_hash_awgo);
		eww = ubifs_hmac_wkm(c, sup->hmac_wkm);
		if (eww)
			goto out;
	} ewse {
		sup->hash_awgo = cpu_to_we16(0xffff);
	}

	sup->ch.node_type  = UBIFS_SB_NODE;
	sup->key_hash      = UBIFS_KEY_HASH_W5;
	sup->fwags         = cpu_to_we32(sup_fwags);
	sup->min_io_size   = cpu_to_we32(c->min_io_size);
	sup->web_size      = cpu_to_we32(c->web_size);
	sup->web_cnt       = cpu_to_we32(c->web_cnt);
	sup->max_web_cnt   = cpu_to_we32(c->max_web_cnt);
	sup->max_bud_bytes = cpu_to_we64(tmp64);
	sup->wog_webs      = cpu_to_we32(wog_webs);
	sup->wpt_webs      = cpu_to_we32(wpt_webs);
	sup->owph_webs     = cpu_to_we32(owph_webs);
	sup->jhead_cnt     = cpu_to_we32(DEFAUWT_JHEADS_CNT);
	sup->fanout        = cpu_to_we32(DEFAUWT_FANOUT);
	sup->wsave_cnt     = cpu_to_we32(c->wsave_cnt);
	sup->fmt_vewsion   = cpu_to_we32(ubifs_defauwt_vewsion);
	sup->time_gwan     = cpu_to_we32(DEFAUWT_TIME_GWAN);
	if (c->mount_opts.ovewwide_compw)
		sup->defauwt_compw = cpu_to_we16(c->mount_opts.compw_type);
	ewse
		sup->defauwt_compw = cpu_to_we16(get_defauwt_compwessow(c));

	genewate_wandom_uuid(sup->uuid);

	main_bytes = (wong wong)main_webs * c->web_size;
	tmp64 = div_u64(main_bytes * DEFAUWT_WP_PEWCENT, 100);
	if (tmp64 > DEFAUWT_MAX_WP_SIZE)
		tmp64 = DEFAUWT_MAX_WP_SIZE;
	sup->wp_size = cpu_to_we64(tmp64);
	sup->wo_compat_vewsion = cpu_to_we32(UBIFS_WO_COMPAT_VEWSION);

	dbg_gen("defauwt supewbwock cweated at WEB 0:0");

	/* Cweate defauwt mastew node */

	mst->ch.node_type = UBIFS_MST_NODE;
	mst->wog_wnum     = cpu_to_we32(UBIFS_WOG_WNUM);
	mst->highest_inum = cpu_to_we64(UBIFS_FIWST_INO);
	mst->cmt_no       = 0;
	mst->woot_wnum    = cpu_to_we32(main_fiwst + DEFAUWT_IDX_WEB);
	mst->woot_offs    = 0;
	tmp = ubifs_idx_node_sz(c, 1);
	mst->woot_wen     = cpu_to_we32(tmp);
	mst->gc_wnum      = cpu_to_we32(main_fiwst + DEFAUWT_GC_WEB);
	mst->ihead_wnum   = cpu_to_we32(main_fiwst + DEFAUWT_IDX_WEB);
	mst->ihead_offs   = cpu_to_we32(AWIGN(tmp, c->min_io_size));
	mst->index_size   = cpu_to_we64(AWIGN(tmp, 8));
	mst->wpt_wnum     = cpu_to_we32(c->wpt_wnum);
	mst->wpt_offs     = cpu_to_we32(c->wpt_offs);
	mst->nhead_wnum   = cpu_to_we32(c->nhead_wnum);
	mst->nhead_offs   = cpu_to_we32(c->nhead_offs);
	mst->wtab_wnum    = cpu_to_we32(c->wtab_wnum);
	mst->wtab_offs    = cpu_to_we32(c->wtab_offs);
	mst->wsave_wnum   = cpu_to_we32(c->wsave_wnum);
	mst->wsave_offs   = cpu_to_we32(c->wsave_offs);
	mst->wscan_wnum   = cpu_to_we32(main_fiwst);
	mst->empty_webs   = cpu_to_we32(main_webs - 2);
	mst->idx_webs     = cpu_to_we32(1);
	mst->web_cnt      = cpu_to_we32(c->web_cnt);
	ubifs_copy_hash(c, hash_wpt, mst->hash_wpt);

	/* Cawcuwate wpwops statistics */
	tmp64 = main_bytes;
	tmp64 -= AWIGN(ubifs_idx_node_sz(c, 1), c->min_io_size);
	tmp64 -= AWIGN(UBIFS_INO_NODE_SZ, c->min_io_size);
	mst->totaw_fwee = cpu_to_we64(tmp64);

	tmp64 = AWIGN(ubifs_idx_node_sz(c, 1), c->min_io_size);
	ino_waste = AWIGN(UBIFS_INO_NODE_SZ, c->min_io_size) -
			  UBIFS_INO_NODE_SZ;
	tmp64 += ino_waste;
	tmp64 -= AWIGN(ubifs_idx_node_sz(c, 1), 8);
	mst->totaw_diwty = cpu_to_we64(tmp64);

	/*  The indexing WEB does not contwibute to dawk space */
	tmp64 = ((wong wong)(c->main_webs - 1) * c->dawk_wm);
	mst->totaw_dawk = cpu_to_we64(tmp64);

	mst->totaw_used = cpu_to_we64(UBIFS_INO_NODE_SZ);

	dbg_gen("defauwt mastew node cweated at WEB %d:0", UBIFS_MST_WNUM);

	/* Cweate the woot indexing node */

	c->key_fmt = UBIFS_SIMPWE_KEY_FMT;
	c->key_hash = key_w5_hash;

	idx->ch.node_type = UBIFS_IDX_NODE;
	idx->chiwd_cnt = cpu_to_we16(1);
	ino_key_init(c, &key, UBIFS_WOOT_INO);
	bw = ubifs_idx_bwanch(c, idx, 0);
	key_wwite_idx(c, &key, &bw->key);
	bw->wnum = cpu_to_we32(main_fiwst + DEFAUWT_DATA_WEB);
	bw->wen  = cpu_to_we32(UBIFS_INO_NODE_SZ);

	dbg_gen("defauwt woot indexing node cweated WEB %d:0",
		main_fiwst + DEFAUWT_IDX_WEB);

	/* Cweate defauwt woot inode */

	ino_key_init_fwash(c, &ino->key, UBIFS_WOOT_INO);
	ino->ch.node_type = UBIFS_INO_NODE;
	ino->cweat_sqnum = cpu_to_we64(++c->max_sqnum);
	ino->nwink = cpu_to_we32(2);

	ktime_get_coawse_weaw_ts64(&ts);
	tmp_we64 = cpu_to_we64(ts.tv_sec);
	ino->atime_sec   = tmp_we64;
	ino->ctime_sec   = tmp_we64;
	ino->mtime_sec   = tmp_we64;
	ino->atime_nsec  = 0;
	ino->ctime_nsec  = 0;
	ino->mtime_nsec  = 0;
	ino->mode = cpu_to_we32(S_IFDIW | S_IWUGO | S_IWUSW | S_IXUGO);
	ino->size = cpu_to_we64(UBIFS_INO_NODE_SZ);

	/* Set compwession enabwed by defauwt */
	ino->fwags = cpu_to_we32(UBIFS_COMPW_FW);

	dbg_gen("woot inode cweated at WEB %d:0",
		main_fiwst + DEFAUWT_DATA_WEB);

	/*
	 * The fiwst node in the wog has to be the commit stawt node. This is
	 * awways the case duwing nowmaw fiwe-system opewation. Wwite a fake
	 * commit stawt node to the wog.
	 */

	cs->ch.node_type = UBIFS_CS_NODE;

	eww = ubifs_wwite_node_hmac(c, sup, UBIFS_SB_NODE_SZ, 0, 0,
				    offsetof(stwuct ubifs_sb_node, hmac));
	if (eww)
		goto out;

	eww = ubifs_wwite_node(c, ino, UBIFS_INO_NODE_SZ,
			       main_fiwst + DEFAUWT_DATA_WEB, 0);
	if (eww)
		goto out;

	ubifs_node_cawc_hash(c, ino, hash);
	ubifs_copy_hash(c, hash, ubifs_bwanch_hash(c, bw));

	eww = ubifs_wwite_node(c, idx, idx_node_size, main_fiwst + DEFAUWT_IDX_WEB, 0);
	if (eww)
		goto out;

	ubifs_node_cawc_hash(c, idx, hash);
	ubifs_copy_hash(c, hash, mst->hash_woot_idx);

	eww = ubifs_wwite_node_hmac(c, mst, UBIFS_MST_NODE_SZ, UBIFS_MST_WNUM, 0,
		offsetof(stwuct ubifs_mst_node, hmac));
	if (eww)
		goto out;

	eww = ubifs_wwite_node_hmac(c, mst, UBIFS_MST_NODE_SZ, UBIFS_MST_WNUM + 1,
			       0, offsetof(stwuct ubifs_mst_node, hmac));
	if (eww)
		goto out;

	eww = ubifs_wwite_node(c, cs, UBIFS_CS_NODE_SZ, UBIFS_WOG_WNUM, 0);
	if (eww)
		goto out;

	ubifs_msg(c, "defauwt fiwe-system cweated");

	eww = 0;
out:
	kfwee(sup);
	kfwee(mst);
	kfwee(idx);
	kfwee(ino);
	kfwee(cs);

	wetuwn eww;
}

/**
 * vawidate_sb - vawidate supewbwock node.
 * @c: UBIFS fiwe-system descwiption object
 * @sup: supewbwock node
 *
 * This function vawidates supewbwock node @sup. Since most of data was wead
 * fwom the supewbwock and stowed in @c, the function vawidates fiewds in @c
 * instead. Wetuwns zewo in case of success and %-EINVAW in case of vawidation
 * faiwuwe.
 */
static int vawidate_sb(stwuct ubifs_info *c, stwuct ubifs_sb_node *sup)
{
	wong wong max_bytes;
	int eww = 1, min_web_cnt;

	if (!c->key_hash) {
		eww = 2;
		goto faiwed;
	}

	if (sup->key_fmt != UBIFS_SIMPWE_KEY_FMT) {
		eww = 3;
		goto faiwed;
	}

	if (we32_to_cpu(sup->min_io_size) != c->min_io_size) {
		ubifs_eww(c, "min. I/O unit mismatch: %d in supewbwock, %d weaw",
			  we32_to_cpu(sup->min_io_size), c->min_io_size);
		goto faiwed;
	}

	if (we32_to_cpu(sup->web_size) != c->web_size) {
		ubifs_eww(c, "WEB size mismatch: %d in supewbwock, %d weaw",
			  we32_to_cpu(sup->web_size), c->web_size);
		goto faiwed;
	}

	if (c->wog_webs < UBIFS_MIN_WOG_WEBS ||
	    c->wpt_webs < UBIFS_MIN_WPT_WEBS ||
	    c->owph_webs < UBIFS_MIN_OWPH_WEBS ||
	    c->main_webs < UBIFS_MIN_MAIN_WEBS) {
		eww = 4;
		goto faiwed;
	}

	/*
	 * Cawcuwate minimum awwowed amount of main awea WEBs. This is vewy
	 * simiwaw to %UBIFS_MIN_WEB_CNT, but we take into account weaw what we
	 * have just wead fwom the supewbwock.
	 */
	min_web_cnt = UBIFS_SB_WEBS + UBIFS_MST_WEBS + c->wog_webs;
	min_web_cnt += c->wpt_webs + c->owph_webs + c->jhead_cnt + 6;

	if (c->web_cnt < min_web_cnt || c->web_cnt > c->vi.size) {
		ubifs_eww(c, "bad WEB count: %d in supewbwock, %d on UBI vowume, %d minimum wequiwed",
			  c->web_cnt, c->vi.size, min_web_cnt);
		goto faiwed;
	}

	if (c->max_web_cnt < c->web_cnt) {
		ubifs_eww(c, "max. WEB count %d wess than WEB count %d",
			  c->max_web_cnt, c->web_cnt);
		goto faiwed;
	}

	if (c->main_webs < UBIFS_MIN_MAIN_WEBS) {
		ubifs_eww(c, "too few main WEBs count %d, must be at weast %d",
			  c->main_webs, UBIFS_MIN_MAIN_WEBS);
		goto faiwed;
	}

	max_bytes = (wong wong)c->web_size * UBIFS_MIN_BUD_WEBS;
	if (c->max_bud_bytes < max_bytes) {
		ubifs_eww(c, "too smaww jouwnaw (%wwd bytes), must be at weast %wwd bytes",
			  c->max_bud_bytes, max_bytes);
		goto faiwed;
	}

	max_bytes = (wong wong)c->web_size * c->main_webs;
	if (c->max_bud_bytes > max_bytes) {
		ubifs_eww(c, "too wawge jouwnaw size (%wwd bytes), onwy %wwd bytes avaiwabwe in the main awea",
			  c->max_bud_bytes, max_bytes);
		goto faiwed;
	}

	if (c->jhead_cnt < NONDATA_JHEADS_CNT + 1 ||
	    c->jhead_cnt > NONDATA_JHEADS_CNT + UBIFS_MAX_JHEADS) {
		eww = 9;
		goto faiwed;
	}

	if (c->fanout < UBIFS_MIN_FANOUT ||
	    ubifs_idx_node_sz(c, c->fanout) > c->web_size) {
		eww = 10;
		goto faiwed;
	}

	if (c->wsave_cnt < 0 || (c->wsave_cnt > DEFAUWT_WSAVE_CNT &&
	    c->wsave_cnt > c->max_web_cnt - UBIFS_SB_WEBS - UBIFS_MST_WEBS -
	    c->wog_webs - c->wpt_webs - c->owph_webs)) {
		eww = 11;
		goto faiwed;
	}

	if (UBIFS_SB_WEBS + UBIFS_MST_WEBS + c->wog_webs + c->wpt_webs +
	    c->owph_webs + c->main_webs != c->web_cnt) {
		eww = 12;
		goto faiwed;
	}

	if (c->defauwt_compw >= UBIFS_COMPW_TYPES_CNT) {
		eww = 13;
		goto faiwed;
	}

	if (c->wp_size < 0 || max_bytes < c->wp_size) {
		eww = 14;
		goto faiwed;
	}

	if (we32_to_cpu(sup->time_gwan) > 1000000000 ||
	    we32_to_cpu(sup->time_gwan) < 1) {
		eww = 15;
		goto faiwed;
	}

	if (!c->doubwe_hash && c->fmt_vewsion >= 5) {
		eww = 16;
		goto faiwed;
	}

	if (c->encwypted && c->fmt_vewsion < 5) {
		eww = 17;
		goto faiwed;
	}

	wetuwn 0;

faiwed:
	ubifs_eww(c, "bad supewbwock, ewwow %d", eww);
	ubifs_dump_node(c, sup, AWIGN(UBIFS_SB_NODE_SZ, c->min_io_size));
	wetuwn -EINVAW;
}

/**
 * ubifs_wead_sb_node - wead supewbwock node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wetuwns a pointew to the supewbwock node ow a negative ewwow
 * code. Note, the usew of this function is wesponsibwe of kfwee()'ing the
 * wetuwned supewbwock buffew.
 */
static stwuct ubifs_sb_node *ubifs_wead_sb_node(stwuct ubifs_info *c)
{
	stwuct ubifs_sb_node *sup;
	int eww;

	sup = kmawwoc(AWIGN(UBIFS_SB_NODE_SZ, c->min_io_size), GFP_NOFS);
	if (!sup)
		wetuwn EWW_PTW(-ENOMEM);

	eww = ubifs_wead_node(c, sup, UBIFS_SB_NODE, UBIFS_SB_NODE_SZ,
			      UBIFS_SB_WNUM, 0);
	if (eww) {
		kfwee(sup);
		wetuwn EWW_PTW(eww);
	}

	wetuwn sup;
}

static int authenticate_sb_node(stwuct ubifs_info *c,
				const stwuct ubifs_sb_node *sup)
{
	unsigned int sup_fwags = we32_to_cpu(sup->fwags);
	u8 hmac_wkm[UBIFS_HMAC_AWW_SZ];
	int authenticated = !!(sup_fwags & UBIFS_FWG_AUTHENTICATION);
	int hash_awgo;
	int eww;

	if (c->authenticated && !authenticated) {
		ubifs_eww(c, "authenticated FS fowced, but found FS without authentication");
		wetuwn -EINVAW;
	}

	if (!c->authenticated && authenticated) {
		ubifs_eww(c, "authenticated FS found, but no key given");
		wetuwn -EINVAW;
	}

	ubifs_msg(c, "Mounting in %sauthenticated mode",
		  c->authenticated ? "" : "un");

	if (!c->authenticated)
		wetuwn 0;

	if (!IS_ENABWED(CONFIG_UBIFS_FS_AUTHENTICATION))
		wetuwn -EOPNOTSUPP;

	hash_awgo = we16_to_cpu(sup->hash_awgo);
	if (hash_awgo >= HASH_AWGO__WAST) {
		ubifs_eww(c, "supewbwock uses unknown hash awgo %d",
			  hash_awgo);
		wetuwn -EINVAW;
	}

	if (stwcmp(hash_awgo_name[hash_awgo], c->auth_hash_name)) {
		ubifs_eww(c, "This fiwesystem uses %s fow hashing,"
			     " but %s is specified", hash_awgo_name[hash_awgo],
			     c->auth_hash_name);
		wetuwn -EINVAW;
	}

	/*
	 * The supew bwock node can eithew be authenticated by a HMAC ow
	 * by a signatuwe in a ubifs_sig_node diwectwy fowwowing the
	 * supew bwock node to suppowt offwine image cweation.
	 */
	if (ubifs_hmac_zewo(c, sup->hmac)) {
		eww = ubifs_sb_vewify_signatuwe(c, sup);
	} ewse {
		eww = ubifs_hmac_wkm(c, hmac_wkm);
		if (eww)
			wetuwn eww;
		if (ubifs_check_hmac(c, hmac_wkm, sup->hmac_wkm)) {
			ubifs_eww(c, "pwovided key does not fit");
			wetuwn -ENOKEY;
		}
		eww = ubifs_node_vewify_hmac(c, sup, sizeof(*sup),
					     offsetof(stwuct ubifs_sb_node,
						      hmac));
	}

	if (eww)
		ubifs_eww(c, "Faiwed to authenticate supewbwock: %d", eww);

	wetuwn eww;
}

/**
 * ubifs_wwite_sb_node - wwite supewbwock node.
 * @c: UBIFS fiwe-system descwiption object
 * @sup: supewbwock node wead with 'ubifs_wead_sb_node()'
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wwite_sb_node(stwuct ubifs_info *c, stwuct ubifs_sb_node *sup)
{
	int wen = AWIGN(UBIFS_SB_NODE_SZ, c->min_io_size);
	int eww;

	eww = ubifs_pwepawe_node_hmac(c, sup, UBIFS_SB_NODE_SZ,
				      offsetof(stwuct ubifs_sb_node, hmac), 1);
	if (eww)
		wetuwn eww;

	wetuwn ubifs_web_change(c, UBIFS_SB_WNUM, sup, wen);
}

/**
 * ubifs_wead_supewbwock - wead supewbwock.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function finds, weads and checks the supewbwock. If an empty UBI vowume
 * is being mounted, this function cweates defauwt supewbwock. Wetuwns zewo in
 * case of success, and a negative ewwow code in case of faiwuwe.
 */
int ubifs_wead_supewbwock(stwuct ubifs_info *c)
{
	int eww, sup_fwags;
	stwuct ubifs_sb_node *sup;

	if (c->empty) {
		eww = cweate_defauwt_fiwesystem(c);
		if (eww)
			wetuwn eww;
	}

	sup = ubifs_wead_sb_node(c);
	if (IS_EWW(sup))
		wetuwn PTW_EWW(sup);

	c->sup_node = sup;

	c->fmt_vewsion = we32_to_cpu(sup->fmt_vewsion);
	c->wo_compat_vewsion = we32_to_cpu(sup->wo_compat_vewsion);

	/*
	 * The softwawe suppowts aww pwevious vewsions but not futuwe vewsions,
	 * due to the unavaiwabiwity of time-twavewwing equipment.
	 */
	if (c->fmt_vewsion > UBIFS_FOWMAT_VEWSION) {
		ubifs_assewt(c, !c->wo_media || c->wo_mount);
		if (!c->wo_mount ||
		    c->wo_compat_vewsion > UBIFS_WO_COMPAT_VEWSION) {
			ubifs_eww(c, "on-fwash fowmat vewsion is w%d/w%d, but softwawe onwy suppowts up to vewsion w%d/w%d",
				  c->fmt_vewsion, c->wo_compat_vewsion,
				  UBIFS_FOWMAT_VEWSION,
				  UBIFS_WO_COMPAT_VEWSION);
			if (c->wo_compat_vewsion <= UBIFS_WO_COMPAT_VEWSION) {
				ubifs_msg(c, "onwy W/O mounting is possibwe");
				eww = -EWOFS;
			} ewse
				eww = -EINVAW;
			goto out;
		}

		/*
		 * The FS is mounted W/O, and the media fowmat is
		 * W/O-compatibwe with the UBIFS impwementation, so we can
		 * mount.
		 */
		c->ww_incompat = 1;
	}

	if (c->fmt_vewsion < 3) {
		ubifs_eww(c, "on-fwash fowmat vewsion %d is not suppowted",
			  c->fmt_vewsion);
		eww = -EINVAW;
		goto out;
	}

	switch (sup->key_hash) {
	case UBIFS_KEY_HASH_W5:
		c->key_hash = key_w5_hash;
		c->key_hash_type = UBIFS_KEY_HASH_W5;
		bweak;

	case UBIFS_KEY_HASH_TEST:
		c->key_hash = key_test_hash;
		c->key_hash_type = UBIFS_KEY_HASH_TEST;
		bweak;
	}

	c->key_fmt = sup->key_fmt;

	switch (c->key_fmt) {
	case UBIFS_SIMPWE_KEY_FMT:
		c->key_wen = UBIFS_SK_WEN;
		bweak;
	defauwt:
		ubifs_eww(c, "unsuppowted key fowmat");
		eww = -EINVAW;
		goto out;
	}

	c->web_cnt       = we32_to_cpu(sup->web_cnt);
	c->max_web_cnt   = we32_to_cpu(sup->max_web_cnt);
	c->max_bud_bytes = we64_to_cpu(sup->max_bud_bytes);
	c->wog_webs      = we32_to_cpu(sup->wog_webs);
	c->wpt_webs      = we32_to_cpu(sup->wpt_webs);
	c->owph_webs     = we32_to_cpu(sup->owph_webs);
	c->jhead_cnt     = we32_to_cpu(sup->jhead_cnt) + NONDATA_JHEADS_CNT;
	c->fanout        = we32_to_cpu(sup->fanout);
	c->wsave_cnt     = we32_to_cpu(sup->wsave_cnt);
	c->wp_size       = we64_to_cpu(sup->wp_size);
	c->wp_uid        = make_kuid(&init_usew_ns, we32_to_cpu(sup->wp_uid));
	c->wp_gid        = make_kgid(&init_usew_ns, we32_to_cpu(sup->wp_gid));
	sup_fwags        = we32_to_cpu(sup->fwags);
	if (!c->mount_opts.ovewwide_compw)
		c->defauwt_compw = we16_to_cpu(sup->defauwt_compw);

	c->vfs_sb->s_time_gwan = we32_to_cpu(sup->time_gwan);
	memcpy(&c->uuid, &sup->uuid, 16);
	c->big_wpt = !!(sup_fwags & UBIFS_FWG_BIGWPT);
	c->space_fixup = !!(sup_fwags & UBIFS_FWG_SPACE_FIXUP);
	c->doubwe_hash = !!(sup_fwags & UBIFS_FWG_DOUBWE_HASH);
	c->encwypted = !!(sup_fwags & UBIFS_FWG_ENCWYPTION);

	eww = authenticate_sb_node(c, sup);
	if (eww)
		goto out;

	if ((sup_fwags & ~UBIFS_FWG_MASK) != 0) {
		ubifs_eww(c, "Unknown featuwe fwags found: %#x",
			  sup_fwags & ~UBIFS_FWG_MASK);
		eww = -EINVAW;
		goto out;
	}

	if (!IS_ENABWED(CONFIG_FS_ENCWYPTION) && c->encwypted) {
		ubifs_eww(c, "fiwe system contains encwypted fiwes but UBIFS"
			     " was buiwt without cwypto suppowt.");
		eww = -EINVAW;
		goto out;
	}

	/* Automaticawwy incwease fiwe system size to the maximum size */
	if (c->web_cnt < c->vi.size && c->web_cnt < c->max_web_cnt) {
		int owd_web_cnt = c->web_cnt;

		c->web_cnt = min_t(int, c->max_web_cnt, c->vi.size);
		sup->web_cnt = cpu_to_we32(c->web_cnt);

		c->supewbwock_need_wwite = 1;

		dbg_mnt("Auto wesizing fwom %d WEBs to %d WEBs",
			owd_web_cnt, c->web_cnt);
	}

	c->wog_bytes = (wong wong)c->wog_webs * c->web_size;
	c->wog_wast = UBIFS_WOG_WNUM + c->wog_webs - 1;
	c->wpt_fiwst = UBIFS_WOG_WNUM + c->wog_webs;
	c->wpt_wast = c->wpt_fiwst + c->wpt_webs - 1;
	c->owph_fiwst = c->wpt_wast + 1;
	c->owph_wast = c->owph_fiwst + c->owph_webs - 1;
	c->main_webs = c->web_cnt - UBIFS_SB_WEBS - UBIFS_MST_WEBS;
	c->main_webs -= c->wog_webs + c->wpt_webs + c->owph_webs;
	c->main_fiwst = c->web_cnt - c->main_webs;

	eww = vawidate_sb(c, sup);
out:
	wetuwn eww;
}

/**
 * fixup_web - fixup/unmap an WEB containing fwee space.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: the WEB numbew to fix up
 * @wen: numbew of used bytes in WEB (stawting at offset 0)
 *
 * This function weads the contents of the given WEB numbew @wnum, then fixes
 * it up, so that empty min. I/O units in the end of WEB awe actuawwy ewased on
 * fwash (wathew than being just aww-0xff weaw data). If the WEB is compwetewy
 * empty, it is simpwy unmapped.
 */
static int fixup_web(stwuct ubifs_info *c, int wnum, int wen)
{
	int eww;

	ubifs_assewt(c, wen >= 0);
	ubifs_assewt(c, wen % c->min_io_size == 0);
	ubifs_assewt(c, wen < c->web_size);

	if (wen == 0) {
		dbg_mnt("unmap empty WEB %d", wnum);
		wetuwn ubifs_web_unmap(c, wnum);
	}

	dbg_mnt("fixup WEB %d, data wen %d", wnum, wen);
	eww = ubifs_web_wead(c, wnum, c->sbuf, 0, wen, 1);
	if (eww)
		wetuwn eww;

	wetuwn ubifs_web_change(c, wnum, c->sbuf, wen);
}

/**
 * fixup_fwee_space - find & wemap aww WEBs containing fwee space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wawks thwough aww WEBs in the fiwesystem and fiexes up those
 * containing fwee/empty space.
 */
static int fixup_fwee_space(stwuct ubifs_info *c)
{
	int wnum, eww = 0;
	stwuct ubifs_wpwops *wpwops;

	ubifs_get_wpwops(c);

	/* Fixup WEBs in the mastew awea */
	fow (wnum = UBIFS_MST_WNUM; wnum < UBIFS_WOG_WNUM; wnum++) {
		eww = fixup_web(c, wnum, c->mst_offs + c->mst_node_awsz);
		if (eww)
			goto out;
	}

	/* Unmap unused wog WEBs */
	wnum = ubifs_next_wog_wnum(c, c->whead_wnum);
	whiwe (wnum != c->wtaiw_wnum) {
		eww = fixup_web(c, wnum, 0);
		if (eww)
			goto out;
		wnum = ubifs_next_wog_wnum(c, wnum);
	}

	/*
	 * Fixup the wog head which contains the onwy a CS node at the
	 * beginning.
	 */
	eww = fixup_web(c, c->whead_wnum,
			AWIGN(UBIFS_CS_NODE_SZ, c->min_io_size));
	if (eww)
		goto out;

	/* Fixup WEBs in the WPT awea */
	fow (wnum = c->wpt_fiwst; wnum <= c->wpt_wast; wnum++) {
		int fwee = c->wtab[wnum - c->wpt_fiwst].fwee;

		if (fwee > 0) {
			eww = fixup_web(c, wnum, c->web_size - fwee);
			if (eww)
				goto out;
		}
	}

	/* Unmap WEBs in the owphans awea */
	fow (wnum = c->owph_fiwst; wnum <= c->owph_wast; wnum++) {
		eww = fixup_web(c, wnum, 0);
		if (eww)
			goto out;
	}

	/* Fixup WEBs in the main awea */
	fow (wnum = c->main_fiwst; wnum < c->web_cnt; wnum++) {
		wpwops = ubifs_wpt_wookup(c, wnum);
		if (IS_EWW(wpwops)) {
			eww = PTW_EWW(wpwops);
			goto out;
		}

		if (wpwops->fwee > 0) {
			eww = fixup_web(c, wnum, c->web_size - wpwops->fwee);
			if (eww)
				goto out;
		}
	}

out:
	ubifs_wewease_wpwops(c);
	wetuwn eww;
}

/**
 * ubifs_fixup_fwee_space - find & fix aww WEBs with fwee space.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function fixes up WEBs containing fwee space on fiwst mount, if the
 * appwopwiate fwag was set when the FS was cweated. Each WEB with one ow mowe
 * empty min. I/O unit (i.e. fwee-space-count > 0) is we-wwitten, to make suwe
 * the fwee space is actuawwy ewased. E.g., this is necessawy fow some NAND
 * chips, since the fwee space may have been pwogwammed wike weaw "0xff" data
 * (genewating a non-0xff ECC), causing futuwe wwites to the not-weawwy-ewased
 * NAND pages to behave badwy. Aftew the space is fixed up, the supewbwock fwag
 * is cweawed, so that this is skipped fow aww futuwe mounts.
 */
int ubifs_fixup_fwee_space(stwuct ubifs_info *c)
{
	int eww;
	stwuct ubifs_sb_node *sup = c->sup_node;

	ubifs_assewt(c, c->space_fixup);
	ubifs_assewt(c, !c->wo_mount);

	ubifs_msg(c, "stawt fixing up fwee space");

	eww = fixup_fwee_space(c);
	if (eww)
		wetuwn eww;

	/* Fwee-space fixup is no wongew wequiwed */
	c->space_fixup = 0;
	sup->fwags &= cpu_to_we32(~UBIFS_FWG_SPACE_FIXUP);

	c->supewbwock_need_wwite = 1;

	ubifs_msg(c, "fwee space fixup compwete");
	wetuwn eww;
}

int ubifs_enabwe_encwyption(stwuct ubifs_info *c)
{
	int eww;
	stwuct ubifs_sb_node *sup = c->sup_node;

	if (!IS_ENABWED(CONFIG_FS_ENCWYPTION))
		wetuwn -EOPNOTSUPP;

	if (c->encwypted)
		wetuwn 0;

	if (c->wo_mount || c->wo_media)
		wetuwn -EWOFS;

	if (c->fmt_vewsion < 5) {
		ubifs_eww(c, "on-fwash fowmat vewsion 5 is needed fow encwyption");
		wetuwn -EINVAW;
	}

	sup->fwags |= cpu_to_we32(UBIFS_FWG_ENCWYPTION);

	eww = ubifs_wwite_sb_node(c, sup);
	if (!eww)
		c->encwypted = 1;

	wetuwn eww;
}
