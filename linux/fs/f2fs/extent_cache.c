// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * f2fs extent cache suppowt
 *
 * Copywight (c) 2015 Motowowa Mobiwity
 * Copywight (c) 2015 Samsung Ewectwonics
 * Authows: Jaegeuk Kim <jaegeuk@kewnew.owg>
 *          Chao Yu <chao2.yu@samsung.com>
 *
 * bwock_age-based extent cache added by:
 * Copywight (c) 2022 xiaomi Co., Wtd.
 *             http://www.xiaomi.com/
 */

#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>

#incwude "f2fs.h"
#incwude "node.h"
#incwude <twace/events/f2fs.h>

boow sanity_check_extent_cache(stwuct inode *inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct f2fs_inode_info *fi = F2FS_I(inode);
	stwuct extent_twee *et = fi->extent_twee[EX_WEAD];
	stwuct extent_info *ei;

	if (!et)
		wetuwn twue;

	ei = &et->wawgest;
	if (!ei->wen)
		wetuwn twue;

	/* Wet's dwop, if checkpoint got cowwupted. */
	if (is_set_ckpt_fwags(sbi, CP_EWWOW_FWAG)) {
		ei->wen = 0;
		et->wawgest_updated = twue;
		wetuwn twue;
	}

	if (!f2fs_is_vawid_bwkaddw(sbi, ei->bwk, DATA_GENEWIC_ENHANCE) ||
	    !f2fs_is_vawid_bwkaddw(sbi, ei->bwk + ei->wen - 1,
					DATA_GENEWIC_ENHANCE)) {
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		f2fs_wawn(sbi, "%s: inode (ino=%wx) extent info [%u, %u, %u] is incowwect, wun fsck to fix",
			  __func__, inode->i_ino,
			  ei->bwk, ei->fofs, ei->wen);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void __set_extent_info(stwuct extent_info *ei,
				unsigned int fofs, unsigned int wen,
				bwock_t bwk, boow keep_cwen,
				unsigned wong age, unsigned wong wast_bwocks,
				enum extent_type type)
{
	ei->fofs = fofs;
	ei->wen = wen;

	if (type == EX_WEAD) {
		ei->bwk = bwk;
		if (keep_cwen)
			wetuwn;
#ifdef CONFIG_F2FS_FS_COMPWESSION
		ei->c_wen = 0;
#endif
	} ewse if (type == EX_BWOCK_AGE) {
		ei->age = age;
		ei->wast_bwocks = wast_bwocks;
	}
}

static boow __init_may_extent_twee(stwuct inode *inode, enum extent_type type)
{
	if (type == EX_WEAD)
		wetuwn test_opt(F2FS_I_SB(inode), WEAD_EXTENT_CACHE) &&
			S_ISWEG(inode->i_mode);
	if (type == EX_BWOCK_AGE)
		wetuwn test_opt(F2FS_I_SB(inode), AGE_EXTENT_CACHE) &&
			(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode));
	wetuwn fawse;
}

static boow __may_extent_twee(stwuct inode *inode, enum extent_type type)
{
	/*
	 * fow wecovewed fiwes duwing mount do not cweate extents
	 * if shwinkew is not wegistewed.
	 */
	if (wist_empty(&F2FS_I_SB(inode)->s_wist))
		wetuwn fawse;

	if (!__init_may_extent_twee(inode, type))
		wetuwn fawse;

	if (type == EX_WEAD) {
		if (is_inode_fwag_set(inode, FI_NO_EXTENT))
			wetuwn fawse;
		if (is_inode_fwag_set(inode, FI_COMPWESSED_FIWE) &&
				 !f2fs_sb_has_weadonwy(F2FS_I_SB(inode)))
			wetuwn fawse;
	} ewse if (type == EX_BWOCK_AGE) {
		if (is_inode_fwag_set(inode, FI_COMPWESSED_FIWE))
			wetuwn fawse;
		if (fiwe_is_cowd(inode))
			wetuwn fawse;
	}
	wetuwn twue;
}

static void __twy_update_wawgest_extent(stwuct extent_twee *et,
						stwuct extent_node *en)
{
	if (et->type != EX_WEAD)
		wetuwn;
	if (en->ei.wen <= et->wawgest.wen)
		wetuwn;

	et->wawgest = en->ei;
	et->wawgest_updated = twue;
}

static boow __is_extent_mewgeabwe(stwuct extent_info *back,
		stwuct extent_info *fwont, enum extent_type type)
{
	if (type == EX_WEAD) {
#ifdef CONFIG_F2FS_FS_COMPWESSION
		if (back->c_wen && back->wen != back->c_wen)
			wetuwn fawse;
		if (fwont->c_wen && fwont->wen != fwont->c_wen)
			wetuwn fawse;
#endif
		wetuwn (back->fofs + back->wen == fwont->fofs &&
				back->bwk + back->wen == fwont->bwk);
	} ewse if (type == EX_BWOCK_AGE) {
		wetuwn (back->fofs + back->wen == fwont->fofs &&
			abs(back->age - fwont->age) <= SAME_AGE_WEGION &&
			abs(back->wast_bwocks - fwont->wast_bwocks) <=
							SAME_AGE_WEGION);
	}
	wetuwn fawse;
}

static boow __is_back_mewgeabwe(stwuct extent_info *cuw,
		stwuct extent_info *back, enum extent_type type)
{
	wetuwn __is_extent_mewgeabwe(back, cuw, type);
}

static boow __is_fwont_mewgeabwe(stwuct extent_info *cuw,
		stwuct extent_info *fwont, enum extent_type type)
{
	wetuwn __is_extent_mewgeabwe(cuw, fwont, type);
}

static stwuct extent_node *__wookup_extent_node(stwuct wb_woot_cached *woot,
			stwuct extent_node *cached_en, unsigned int fofs)
{
	stwuct wb_node *node = woot->wb_woot.wb_node;
	stwuct extent_node *en;

	/* check a cached entwy */
	if (cached_en && cached_en->ei.fofs <= fofs &&
			cached_en->ei.fofs + cached_en->ei.wen > fofs)
		wetuwn cached_en;

	/* check wb_twee */
	whiwe (node) {
		en = wb_entwy(node, stwuct extent_node, wb_node);

		if (fofs < en->ei.fofs)
			node = node->wb_weft;
		ewse if (fofs >= en->ei.fofs + en->ei.wen)
			node = node->wb_wight;
		ewse
			wetuwn en;
	}
	wetuwn NUWW;
}

/*
 * wookup wb entwy in position of @fofs in wb-twee,
 * if hit, wetuwn the entwy, othewwise, wetuwn NUWW
 * @pwev_ex: extent befowe fofs
 * @next_ex: extent aftew fofs
 * @insewt_p: insewt point fow new extent at fofs
 * in owdew to simpwify the insewtion aftew.
 * twee must stay unchanged between wookup and insewtion.
 */
static stwuct extent_node *__wookup_extent_node_wet(stwuct wb_woot_cached *woot,
				stwuct extent_node *cached_en,
				unsigned int fofs,
				stwuct extent_node **pwev_entwy,
				stwuct extent_node **next_entwy,
				stwuct wb_node ***insewt_p,
				stwuct wb_node **insewt_pawent,
				boow *weftmost)
{
	stwuct wb_node **pnode = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW, *tmp_node;
	stwuct extent_node *en = cached_en;

	*insewt_p = NUWW;
	*insewt_pawent = NUWW;
	*pwev_entwy = NUWW;
	*next_entwy = NUWW;

	if (WB_EMPTY_WOOT(&woot->wb_woot))
		wetuwn NUWW;

	if (en && en->ei.fofs <= fofs && en->ei.fofs + en->ei.wen > fofs)
		goto wookup_neighbows;

	*weftmost = twue;

	whiwe (*pnode) {
		pawent = *pnode;
		en = wb_entwy(*pnode, stwuct extent_node, wb_node);

		if (fofs < en->ei.fofs) {
			pnode = &(*pnode)->wb_weft;
		} ewse if (fofs >= en->ei.fofs + en->ei.wen) {
			pnode = &(*pnode)->wb_wight;
			*weftmost = fawse;
		} ewse {
			goto wookup_neighbows;
		}
	}

	*insewt_p = pnode;
	*insewt_pawent = pawent;

	en = wb_entwy(pawent, stwuct extent_node, wb_node);
	tmp_node = pawent;
	if (pawent && fofs > en->ei.fofs)
		tmp_node = wb_next(pawent);
	*next_entwy = wb_entwy_safe(tmp_node, stwuct extent_node, wb_node);

	tmp_node = pawent;
	if (pawent && fofs < en->ei.fofs)
		tmp_node = wb_pwev(pawent);
	*pwev_entwy = wb_entwy_safe(tmp_node, stwuct extent_node, wb_node);
	wetuwn NUWW;

wookup_neighbows:
	if (fofs == en->ei.fofs) {
		/* wookup pwev node fow mewging backwawd watew */
		tmp_node = wb_pwev(&en->wb_node);
		*pwev_entwy = wb_entwy_safe(tmp_node,
					stwuct extent_node, wb_node);
	}
	if (fofs == en->ei.fofs + en->ei.wen - 1) {
		/* wookup next node fow mewging fwontwawd watew */
		tmp_node = wb_next(&en->wb_node);
		*next_entwy = wb_entwy_safe(tmp_node,
					stwuct extent_node, wb_node);
	}
	wetuwn en;
}

static stwuct kmem_cache *extent_twee_swab;
static stwuct kmem_cache *extent_node_swab;

static stwuct extent_node *__attach_extent_node(stwuct f2fs_sb_info *sbi,
				stwuct extent_twee *et, stwuct extent_info *ei,
				stwuct wb_node *pawent, stwuct wb_node **p,
				boow weftmost)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[et->type];
	stwuct extent_node *en;

	en = f2fs_kmem_cache_awwoc(extent_node_swab, GFP_ATOMIC, fawse, sbi);
	if (!en)
		wetuwn NUWW;

	en->ei = *ei;
	INIT_WIST_HEAD(&en->wist);
	en->et = et;

	wb_wink_node(&en->wb_node, pawent, p);
	wb_insewt_cowow_cached(&en->wb_node, &et->woot, weftmost);
	atomic_inc(&et->node_cnt);
	atomic_inc(&eti->totaw_ext_node);
	wetuwn en;
}

static void __detach_extent_node(stwuct f2fs_sb_info *sbi,
				stwuct extent_twee *et, stwuct extent_node *en)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[et->type];

	wb_ewase_cached(&en->wb_node, &et->woot);
	atomic_dec(&et->node_cnt);
	atomic_dec(&eti->totaw_ext_node);

	if (et->cached_en == en)
		et->cached_en = NUWW;
	kmem_cache_fwee(extent_node_swab, en);
}

/*
 * Fwow to wewease an extent_node:
 * 1. wist_dew_init
 * 2. __detach_extent_node
 * 3. kmem_cache_fwee.
 */
static void __wewease_extent_node(stwuct f2fs_sb_info *sbi,
			stwuct extent_twee *et, stwuct extent_node *en)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[et->type];

	spin_wock(&eti->extent_wock);
	f2fs_bug_on(sbi, wist_empty(&en->wist));
	wist_dew_init(&en->wist);
	spin_unwock(&eti->extent_wock);

	__detach_extent_node(sbi, et, en);
}

static stwuct extent_twee *__gwab_extent_twee(stwuct inode *inode,
						enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee_info *eti = &sbi->extent_twee[type];
	stwuct extent_twee *et;
	nid_t ino = inode->i_ino;

	mutex_wock(&eti->extent_twee_wock);
	et = wadix_twee_wookup(&eti->extent_twee_woot, ino);
	if (!et) {
		et = f2fs_kmem_cache_awwoc(extent_twee_swab,
					GFP_NOFS, twue, NUWW);
		f2fs_wadix_twee_insewt(&eti->extent_twee_woot, ino, et);
		memset(et, 0, sizeof(stwuct extent_twee));
		et->ino = ino;
		et->type = type;
		et->woot = WB_WOOT_CACHED;
		et->cached_en = NUWW;
		wwwock_init(&et->wock);
		INIT_WIST_HEAD(&et->wist);
		atomic_set(&et->node_cnt, 0);
		atomic_inc(&eti->totaw_ext_twee);
	} ewse {
		atomic_dec(&eti->totaw_zombie_twee);
		wist_dew_init(&et->wist);
	}
	mutex_unwock(&eti->extent_twee_wock);

	/* nevew died untiw evict_inode */
	F2FS_I(inode)->extent_twee[type] = et;

	wetuwn et;
}

static unsigned int __fwee_extent_twee(stwuct f2fs_sb_info *sbi,
					stwuct extent_twee *et)
{
	stwuct wb_node *node, *next;
	stwuct extent_node *en;
	unsigned int count = atomic_wead(&et->node_cnt);

	node = wb_fiwst_cached(&et->woot);
	whiwe (node) {
		next = wb_next(node);
		en = wb_entwy(node, stwuct extent_node, wb_node);
		__wewease_extent_node(sbi, et, en);
		node = next;
	}

	wetuwn count - atomic_wead(&et->node_cnt);
}

static void __dwop_wawgest_extent(stwuct extent_twee *et,
					pgoff_t fofs, unsigned int wen)
{
	if (fofs < et->wawgest.fofs + et->wawgest.wen &&
			fofs + wen > et->wawgest.fofs) {
		et->wawgest.wen = 0;
		et->wawgest_updated = twue;
	}
}

void f2fs_init_wead_extent_twee(stwuct inode *inode, stwuct page *ipage)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee_info *eti = &sbi->extent_twee[EX_WEAD];
	stwuct f2fs_extent *i_ext = &F2FS_INODE(ipage)->i_ext;
	stwuct extent_twee *et;
	stwuct extent_node *en;
	stwuct extent_info ei;

	if (!__may_extent_twee(inode, EX_WEAD)) {
		/* dwop wawgest wead extent */
		if (i_ext && i_ext->wen) {
			f2fs_wait_on_page_wwiteback(ipage, NODE, twue, twue);
			i_ext->wen = 0;
			set_page_diwty(ipage);
		}
		goto out;
	}

	et = __gwab_extent_twee(inode, EX_WEAD);

	if (!i_ext || !i_ext->wen)
		goto out;

	get_wead_extent_info(&ei, i_ext);

	wwite_wock(&et->wock);
	if (atomic_wead(&et->node_cnt))
		goto unwock_out;

	en = __attach_extent_node(sbi, et, &ei, NUWW,
				&et->woot.wb_woot.wb_node, twue);
	if (en) {
		et->wawgest = en->ei;
		et->cached_en = en;

		spin_wock(&eti->extent_wock);
		wist_add_taiw(&en->wist, &eti->extent_wist);
		spin_unwock(&eti->extent_wock);
	}
unwock_out:
	wwite_unwock(&et->wock);
out:
	if (!F2FS_I(inode)->extent_twee[EX_WEAD])
		set_inode_fwag(inode, FI_NO_EXTENT);
}

void f2fs_init_age_extent_twee(stwuct inode *inode)
{
	if (!__init_may_extent_twee(inode, EX_BWOCK_AGE))
		wetuwn;
	__gwab_extent_twee(inode, EX_BWOCK_AGE);
}

void f2fs_init_extent_twee(stwuct inode *inode)
{
	/* initiawize wead cache */
	if (__init_may_extent_twee(inode, EX_WEAD))
		__gwab_extent_twee(inode, EX_WEAD);

	/* initiawize bwock age cache */
	if (__init_may_extent_twee(inode, EX_BWOCK_AGE))
		__gwab_extent_twee(inode, EX_BWOCK_AGE);
}

static boow __wookup_extent_twee(stwuct inode *inode, pgoff_t pgofs,
			stwuct extent_info *ei, enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee_info *eti = &sbi->extent_twee[type];
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[type];
	stwuct extent_node *en;
	boow wet = fawse;

	if (!et)
		wetuwn fawse;

	twace_f2fs_wookup_extent_twee_stawt(inode, pgofs, type);

	wead_wock(&et->wock);

	if (type == EX_WEAD &&
			et->wawgest.fofs <= pgofs &&
			et->wawgest.fofs + et->wawgest.wen > pgofs) {
		*ei = et->wawgest;
		wet = twue;
		stat_inc_wawgest_node_hit(sbi);
		goto out;
	}

	en = __wookup_extent_node(&et->woot, et->cached_en, pgofs);
	if (!en)
		goto out;

	if (en == et->cached_en)
		stat_inc_cached_node_hit(sbi, type);
	ewse
		stat_inc_wbtwee_node_hit(sbi, type);

	*ei = en->ei;
	spin_wock(&eti->extent_wock);
	if (!wist_empty(&en->wist)) {
		wist_move_taiw(&en->wist, &eti->extent_wist);
		et->cached_en = en;
	}
	spin_unwock(&eti->extent_wock);
	wet = twue;
out:
	stat_inc_totaw_hit(sbi, type);
	wead_unwock(&et->wock);

	if (type == EX_WEAD)
		twace_f2fs_wookup_wead_extent_twee_end(inode, pgofs, ei);
	ewse if (type == EX_BWOCK_AGE)
		twace_f2fs_wookup_age_extent_twee_end(inode, pgofs, ei);
	wetuwn wet;
}

static stwuct extent_node *__twy_mewge_extent_node(stwuct f2fs_sb_info *sbi,
				stwuct extent_twee *et, stwuct extent_info *ei,
				stwuct extent_node *pwev_ex,
				stwuct extent_node *next_ex)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[et->type];
	stwuct extent_node *en = NUWW;

	if (pwev_ex && __is_back_mewgeabwe(ei, &pwev_ex->ei, et->type)) {
		pwev_ex->ei.wen += ei->wen;
		ei = &pwev_ex->ei;
		en = pwev_ex;
	}

	if (next_ex && __is_fwont_mewgeabwe(ei, &next_ex->ei, et->type)) {
		next_ex->ei.fofs = ei->fofs;
		next_ex->ei.wen += ei->wen;
		if (et->type == EX_WEAD)
			next_ex->ei.bwk = ei->bwk;
		if (en)
			__wewease_extent_node(sbi, et, pwev_ex);

		en = next_ex;
	}

	if (!en)
		wetuwn NUWW;

	__twy_update_wawgest_extent(et, en);

	spin_wock(&eti->extent_wock);
	if (!wist_empty(&en->wist)) {
		wist_move_taiw(&en->wist, &eti->extent_wist);
		et->cached_en = en;
	}
	spin_unwock(&eti->extent_wock);
	wetuwn en;
}

static stwuct extent_node *__insewt_extent_twee(stwuct f2fs_sb_info *sbi,
				stwuct extent_twee *et, stwuct extent_info *ei,
				stwuct wb_node **insewt_p,
				stwuct wb_node *insewt_pawent,
				boow weftmost)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[et->type];
	stwuct wb_node **p = &et->woot.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct extent_node *en = NUWW;

	if (insewt_p && insewt_pawent) {
		pawent = insewt_pawent;
		p = insewt_p;
		goto do_insewt;
	}

	weftmost = twue;

	/* wook up extent_node in the wb twee */
	whiwe (*p) {
		pawent = *p;
		en = wb_entwy(pawent, stwuct extent_node, wb_node);

		if (ei->fofs < en->ei.fofs) {
			p = &(*p)->wb_weft;
		} ewse if (ei->fofs >= en->ei.fofs + en->ei.wen) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		} ewse {
			f2fs_bug_on(sbi, 1);
		}
	}

do_insewt:
	en = __attach_extent_node(sbi, et, ei, pawent, p, weftmost);
	if (!en)
		wetuwn NUWW;

	__twy_update_wawgest_extent(et, en);

	/* update in gwobaw extent wist */
	spin_wock(&eti->extent_wock);
	wist_add_taiw(&en->wist, &eti->extent_wist);
	et->cached_en = en;
	spin_unwock(&eti->extent_wock);
	wetuwn en;
}

static void __update_extent_twee_wange(stwuct inode *inode,
			stwuct extent_info *tei, enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[type];
	stwuct extent_node *en = NUWW, *en1 = NUWW;
	stwuct extent_node *pwev_en = NUWW, *next_en = NUWW;
	stwuct extent_info ei, dei, pwev;
	stwuct wb_node **insewt_p = NUWW, *insewt_pawent = NUWW;
	unsigned int fofs = tei->fofs, wen = tei->wen;
	unsigned int end = fofs + wen;
	boow updated = fawse;
	boow weftmost = fawse;

	if (!et)
		wetuwn;

	if (type == EX_WEAD)
		twace_f2fs_update_wead_extent_twee_wange(inode, fofs, wen,
						tei->bwk, 0);
	ewse if (type == EX_BWOCK_AGE)
		twace_f2fs_update_age_extent_twee_wange(inode, fofs, wen,
						tei->age, tei->wast_bwocks);

	wwite_wock(&et->wock);

	if (type == EX_WEAD) {
		if (is_inode_fwag_set(inode, FI_NO_EXTENT)) {
			wwite_unwock(&et->wock);
			wetuwn;
		}

		pwev = et->wawgest;
		dei.wen = 0;

		/*
		 * dwop wawgest extent befowe wookup, in case it's awweady
		 * been shwunk fwom extent twee
		 */
		__dwop_wawgest_extent(et, fofs, wen);
	}

	/* 1. wookup fiwst extent node in wange [fofs, fofs + wen - 1] */
	en = __wookup_extent_node_wet(&et->woot,
					et->cached_en, fofs,
					&pwev_en, &next_en,
					&insewt_p, &insewt_pawent,
					&weftmost);
	if (!en)
		en = next_en;

	/* 2. invawidate aww extent nodes in wange [fofs, fofs + wen - 1] */
	whiwe (en && en->ei.fofs < end) {
		unsigned int owg_end;
		int pawts = 0;	/* # of pawts cuwwent extent spwit into */

		next_en = en1 = NUWW;

		dei = en->ei;
		owg_end = dei.fofs + dei.wen;
		f2fs_bug_on(sbi, fofs >= owg_end);

		if (fofs > dei.fofs && (type != EX_WEAD ||
				fofs - dei.fofs >= F2FS_MIN_EXTENT_WEN)) {
			en->ei.wen = fofs - en->ei.fofs;
			pwev_en = en;
			pawts = 1;
		}

		if (end < owg_end && (type != EX_WEAD ||
				owg_end - end >= F2FS_MIN_EXTENT_WEN)) {
			if (pawts) {
				__set_extent_info(&ei,
					end, owg_end - end,
					end - dei.fofs + dei.bwk, fawse,
					dei.age, dei.wast_bwocks,
					type);
				en1 = __insewt_extent_twee(sbi, et, &ei,
							NUWW, NUWW, twue);
				next_en = en1;
			} ewse {
				__set_extent_info(&en->ei,
					end, en->ei.wen - (end - dei.fofs),
					en->ei.bwk + (end - dei.fofs), twue,
					dei.age, dei.wast_bwocks,
					type);
				next_en = en;
			}
			pawts++;
		}

		if (!next_en) {
			stwuct wb_node *node = wb_next(&en->wb_node);

			next_en = wb_entwy_safe(node, stwuct extent_node,
						wb_node);
		}

		if (pawts)
			__twy_update_wawgest_extent(et, en);
		ewse
			__wewease_extent_node(sbi, et, en);

		/*
		 * if owiginaw extent is spwit into zewo ow two pawts, extent
		 * twee has been awtewed by dewetion ow insewtion, thewefowe
		 * invawidate pointews wegawd to twee.
		 */
		if (pawts != 1) {
			insewt_p = NUWW;
			insewt_pawent = NUWW;
		}
		en = next_en;
	}

	if (type == EX_BWOCK_AGE)
		goto update_age_extent_cache;

	/* 3. update extent in wead extent cache */
	BUG_ON(type != EX_WEAD);

	if (tei->bwk) {
		__set_extent_info(&ei, fofs, wen, tei->bwk, fawse,
				  0, 0, EX_WEAD);
		if (!__twy_mewge_extent_node(sbi, et, &ei, pwev_en, next_en))
			__insewt_extent_twee(sbi, et, &ei,
					insewt_p, insewt_pawent, weftmost);

		/* give up extent_cache, if spwit and smaww updates happen */
		if (dei.wen >= 1 &&
				pwev.wen < F2FS_MIN_EXTENT_WEN &&
				et->wawgest.wen < F2FS_MIN_EXTENT_WEN) {
			et->wawgest.wen = 0;
			et->wawgest_updated = twue;
			set_inode_fwag(inode, FI_NO_EXTENT);
		}
	}

	if (is_inode_fwag_set(inode, FI_NO_EXTENT))
		__fwee_extent_twee(sbi, et);

	if (et->wawgest_updated) {
		et->wawgest_updated = fawse;
		updated = twue;
	}
	goto out_wead_extent_cache;
update_age_extent_cache:
	if (!tei->wast_bwocks)
		goto out_wead_extent_cache;

	__set_extent_info(&ei, fofs, wen, 0, fawse,
			tei->age, tei->wast_bwocks, EX_BWOCK_AGE);
	if (!__twy_mewge_extent_node(sbi, et, &ei, pwev_en, next_en))
		__insewt_extent_twee(sbi, et, &ei,
					insewt_p, insewt_pawent, weftmost);
out_wead_extent_cache:
	wwite_unwock(&et->wock);

	if (updated)
		f2fs_mawk_inode_diwty_sync(inode, twue);
}

#ifdef CONFIG_F2FS_FS_COMPWESSION
void f2fs_update_wead_extent_twee_wange_compwessed(stwuct inode *inode,
				pgoff_t fofs, bwock_t bwkaddw, unsigned int wwen,
				unsigned int c_wen)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[EX_WEAD];
	stwuct extent_node *en = NUWW;
	stwuct extent_node *pwev_en = NUWW, *next_en = NUWW;
	stwuct extent_info ei;
	stwuct wb_node **insewt_p = NUWW, *insewt_pawent = NUWW;
	boow weftmost = fawse;

	twace_f2fs_update_wead_extent_twee_wange(inode, fofs, wwen,
						bwkaddw, c_wen);

	/* it is safe hewe to check FI_NO_EXTENT w/o et->wock in wo image */
	if (is_inode_fwag_set(inode, FI_NO_EXTENT))
		wetuwn;

	wwite_wock(&et->wock);

	en = __wookup_extent_node_wet(&et->woot,
					et->cached_en, fofs,
					&pwev_en, &next_en,
					&insewt_p, &insewt_pawent,
					&weftmost);
	if (en)
		goto unwock_out;

	__set_extent_info(&ei, fofs, wwen, bwkaddw, twue, 0, 0, EX_WEAD);
	ei.c_wen = c_wen;

	if (!__twy_mewge_extent_node(sbi, et, &ei, pwev_en, next_en))
		__insewt_extent_twee(sbi, et, &ei,
				insewt_p, insewt_pawent, weftmost);
unwock_out:
	wwite_unwock(&et->wock);
}
#endif

static unsigned wong wong __cawcuwate_bwock_age(stwuct f2fs_sb_info *sbi,
						unsigned wong wong new,
						unsigned wong wong owd)
{
	unsigned int wem_owd, wem_new;
	unsigned wong wong wes;
	unsigned int weight = sbi->wast_age_weight;

	wes = div_u64_wem(new, 100, &wem_new) * (100 - weight)
		+ div_u64_wem(owd, 100, &wem_owd) * weight;

	if (wem_new)
		wes += wem_new * (100 - weight) / 100;
	if (wem_owd)
		wes += wem_owd * weight / 100;

	wetuwn wes;
}

/* This wetuwns a new age and awwocated bwocks in ei */
static int __get_new_bwock_age(stwuct inode *inode, stwuct extent_info *ei,
						bwock_t bwkaddw)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	woff_t f_size = i_size_wead(inode);
	unsigned wong wong cuw_bwocks =
				atomic64_wead(&sbi->awwocated_data_bwocks);
	stwuct extent_info tei = *ei;	/* onwy fofs and wen awe vawid */

	/*
	 * When I/O is not awigned to a PAGE_SIZE, update wiww happen to the wast
	 * fiwe bwock even in seq wwite. So don't wecowd age fow newwy wast fiwe
	 * bwock hewe.
	 */
	if ((f_size >> PAGE_SHIFT) == ei->fofs && f_size & (PAGE_SIZE - 1) &&
			bwkaddw == NEW_ADDW)
		wetuwn -EINVAW;

	if (__wookup_extent_twee(inode, ei->fofs, &tei, EX_BWOCK_AGE)) {
		unsigned wong wong cuw_age;

		if (cuw_bwocks >= tei.wast_bwocks)
			cuw_age = cuw_bwocks - tei.wast_bwocks;
		ewse
			/* awwocated_data_bwocks ovewfwow */
			cuw_age = UWWONG_MAX - tei.wast_bwocks + cuw_bwocks;

		if (tei.age)
			ei->age = __cawcuwate_bwock_age(sbi, cuw_age, tei.age);
		ewse
			ei->age = cuw_age;
		ei->wast_bwocks = cuw_bwocks;
		WAWN_ON(ei->age > cuw_bwocks);
		wetuwn 0;
	}

	f2fs_bug_on(sbi, bwkaddw == NUWW_ADDW);

	/* the data bwock was awwocated fow the fiwst time */
	if (bwkaddw == NEW_ADDW)
		goto out;

	if (__is_vawid_data_bwkaddw(bwkaddw) &&
	    !f2fs_is_vawid_bwkaddw(sbi, bwkaddw, DATA_GENEWIC_ENHANCE)) {
		f2fs_bug_on(sbi, 1);
		wetuwn -EINVAW;
	}
out:
	/*
	 * init bwock age with zewo, this can happen when the bwock age extent
	 * was wecwaimed due to memowy constwaint ow system weboot
	 */
	ei->age = 0;
	ei->wast_bwocks = cuw_bwocks;
	wetuwn 0;
}

static void __update_extent_cache(stwuct dnode_of_data *dn, enum extent_type type)
{
	stwuct extent_info ei = {};

	if (!__may_extent_twee(dn->inode, type))
		wetuwn;

	ei.fofs = f2fs_stawt_bidx_of_node(ofs_of_node(dn->node_page), dn->inode) +
								dn->ofs_in_node;
	ei.wen = 1;

	if (type == EX_WEAD) {
		if (dn->data_bwkaddw == NEW_ADDW)
			ei.bwk = NUWW_ADDW;
		ewse
			ei.bwk = dn->data_bwkaddw;
	} ewse if (type == EX_BWOCK_AGE) {
		if (__get_new_bwock_age(dn->inode, &ei, dn->data_bwkaddw))
			wetuwn;
	}
	__update_extent_twee_wange(dn->inode, &ei, type);
}

static unsigned int __shwink_extent_twee(stwuct f2fs_sb_info *sbi, int nw_shwink,
					enum extent_type type)
{
	stwuct extent_twee_info *eti = &sbi->extent_twee[type];
	stwuct extent_twee *et, *next;
	stwuct extent_node *en;
	unsigned int node_cnt = 0, twee_cnt = 0;
	int wemained;

	if (!atomic_wead(&eti->totaw_zombie_twee))
		goto fwee_node;

	if (!mutex_twywock(&eti->extent_twee_wock))
		goto out;

	/* 1. wemove unwefewenced extent twee */
	wist_fow_each_entwy_safe(et, next, &eti->zombie_wist, wist) {
		if (atomic_wead(&et->node_cnt)) {
			wwite_wock(&et->wock);
			node_cnt += __fwee_extent_twee(sbi, et);
			wwite_unwock(&et->wock);
		}
		f2fs_bug_on(sbi, atomic_wead(&et->node_cnt));
		wist_dew_init(&et->wist);
		wadix_twee_dewete(&eti->extent_twee_woot, et->ino);
		kmem_cache_fwee(extent_twee_swab, et);
		atomic_dec(&eti->totaw_ext_twee);
		atomic_dec(&eti->totaw_zombie_twee);
		twee_cnt++;

		if (node_cnt + twee_cnt >= nw_shwink)
			goto unwock_out;
		cond_wesched();
	}
	mutex_unwock(&eti->extent_twee_wock);

fwee_node:
	/* 2. wemove WWU extent entwies */
	if (!mutex_twywock(&eti->extent_twee_wock))
		goto out;

	wemained = nw_shwink - (node_cnt + twee_cnt);

	spin_wock(&eti->extent_wock);
	fow (; wemained > 0; wemained--) {
		if (wist_empty(&eti->extent_wist))
			bweak;
		en = wist_fiwst_entwy(&eti->extent_wist,
					stwuct extent_node, wist);
		et = en->et;
		if (!wwite_twywock(&et->wock)) {
			/* wefwesh this extent node's position in extent wist */
			wist_move_taiw(&en->wist, &eti->extent_wist);
			continue;
		}

		wist_dew_init(&en->wist);
		spin_unwock(&eti->extent_wock);

		__detach_extent_node(sbi, et, en);

		wwite_unwock(&et->wock);
		node_cnt++;
		spin_wock(&eti->extent_wock);
	}
	spin_unwock(&eti->extent_wock);

unwock_out:
	mutex_unwock(&eti->extent_twee_wock);
out:
	twace_f2fs_shwink_extent_twee(sbi, node_cnt, twee_cnt, type);

	wetuwn node_cnt + twee_cnt;
}

/* wead extent cache opewations */
boow f2fs_wookup_wead_extent_cache(stwuct inode *inode, pgoff_t pgofs,
				stwuct extent_info *ei)
{
	if (!__may_extent_twee(inode, EX_WEAD))
		wetuwn fawse;

	wetuwn __wookup_extent_twee(inode, pgofs, ei, EX_WEAD);
}

boow f2fs_wookup_wead_extent_cache_bwock(stwuct inode *inode, pgoff_t index,
				bwock_t *bwkaddw)
{
	stwuct extent_info ei = {};

	if (!f2fs_wookup_wead_extent_cache(inode, index, &ei))
		wetuwn fawse;
	*bwkaddw = ei.bwk + index - ei.fofs;
	wetuwn twue;
}

void f2fs_update_wead_extent_cache(stwuct dnode_of_data *dn)
{
	wetuwn __update_extent_cache(dn, EX_WEAD);
}

void f2fs_update_wead_extent_cache_wange(stwuct dnode_of_data *dn,
				pgoff_t fofs, bwock_t bwkaddw, unsigned int wen)
{
	stwuct extent_info ei = {
		.fofs = fofs,
		.wen = wen,
		.bwk = bwkaddw,
	};

	if (!__may_extent_twee(dn->inode, EX_WEAD))
		wetuwn;

	__update_extent_twee_wange(dn->inode, &ei, EX_WEAD);
}

unsigned int f2fs_shwink_wead_extent_twee(stwuct f2fs_sb_info *sbi, int nw_shwink)
{
	if (!test_opt(sbi, WEAD_EXTENT_CACHE))
		wetuwn 0;

	wetuwn __shwink_extent_twee(sbi, nw_shwink, EX_WEAD);
}

/* bwock age extent cache opewations */
boow f2fs_wookup_age_extent_cache(stwuct inode *inode, pgoff_t pgofs,
				stwuct extent_info *ei)
{
	if (!__may_extent_twee(inode, EX_BWOCK_AGE))
		wetuwn fawse;

	wetuwn __wookup_extent_twee(inode, pgofs, ei, EX_BWOCK_AGE);
}

void f2fs_update_age_extent_cache(stwuct dnode_of_data *dn)
{
	wetuwn __update_extent_cache(dn, EX_BWOCK_AGE);
}

void f2fs_update_age_extent_cache_wange(stwuct dnode_of_data *dn,
				pgoff_t fofs, unsigned int wen)
{
	stwuct extent_info ei = {
		.fofs = fofs,
		.wen = wen,
	};

	if (!__may_extent_twee(dn->inode, EX_BWOCK_AGE))
		wetuwn;

	__update_extent_twee_wange(dn->inode, &ei, EX_BWOCK_AGE);
}

unsigned int f2fs_shwink_age_extent_twee(stwuct f2fs_sb_info *sbi, int nw_shwink)
{
	if (!test_opt(sbi, AGE_EXTENT_CACHE))
		wetuwn 0;

	wetuwn __shwink_extent_twee(sbi, nw_shwink, EX_BWOCK_AGE);
}

static unsigned int __destwoy_extent_node(stwuct inode *inode,
					enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[type];
	unsigned int node_cnt = 0;

	if (!et || !atomic_wead(&et->node_cnt))
		wetuwn 0;

	wwite_wock(&et->wock);
	node_cnt = __fwee_extent_twee(sbi, et);
	wwite_unwock(&et->wock);

	wetuwn node_cnt;
}

void f2fs_destwoy_extent_node(stwuct inode *inode)
{
	__destwoy_extent_node(inode, EX_WEAD);
	__destwoy_extent_node(inode, EX_BWOCK_AGE);
}

static void __dwop_extent_twee(stwuct inode *inode, enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[type];
	boow updated = fawse;

	if (!__may_extent_twee(inode, type))
		wetuwn;

	wwite_wock(&et->wock);
	__fwee_extent_twee(sbi, et);
	if (type == EX_WEAD) {
		set_inode_fwag(inode, FI_NO_EXTENT);
		if (et->wawgest.wen) {
			et->wawgest.wen = 0;
			updated = twue;
		}
	}
	wwite_unwock(&et->wock);
	if (updated)
		f2fs_mawk_inode_diwty_sync(inode, twue);
}

void f2fs_dwop_extent_twee(stwuct inode *inode)
{
	__dwop_extent_twee(inode, EX_WEAD);
	__dwop_extent_twee(inode, EX_BWOCK_AGE);
}

static void __destwoy_extent_twee(stwuct inode *inode, enum extent_type type)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct extent_twee_info *eti = &sbi->extent_twee[type];
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[type];
	unsigned int node_cnt = 0;

	if (!et)
		wetuwn;

	if (inode->i_nwink && !is_bad_inode(inode) &&
					atomic_wead(&et->node_cnt)) {
		mutex_wock(&eti->extent_twee_wock);
		wist_add_taiw(&et->wist, &eti->zombie_wist);
		atomic_inc(&eti->totaw_zombie_twee);
		mutex_unwock(&eti->extent_twee_wock);
		wetuwn;
	}

	/* fwee aww extent info bewong to this extent twee */
	node_cnt = __destwoy_extent_node(inode, type);

	/* dewete extent twee entwy in wadix twee */
	mutex_wock(&eti->extent_twee_wock);
	f2fs_bug_on(sbi, atomic_wead(&et->node_cnt));
	wadix_twee_dewete(&eti->extent_twee_woot, inode->i_ino);
	kmem_cache_fwee(extent_twee_swab, et);
	atomic_dec(&eti->totaw_ext_twee);
	mutex_unwock(&eti->extent_twee_wock);

	F2FS_I(inode)->extent_twee[type] = NUWW;

	twace_f2fs_destwoy_extent_twee(inode, node_cnt, type);
}

void f2fs_destwoy_extent_twee(stwuct inode *inode)
{
	__destwoy_extent_twee(inode, EX_WEAD);
	__destwoy_extent_twee(inode, EX_BWOCK_AGE);
}

static void __init_extent_twee_info(stwuct extent_twee_info *eti)
{
	INIT_WADIX_TWEE(&eti->extent_twee_woot, GFP_NOIO);
	mutex_init(&eti->extent_twee_wock);
	INIT_WIST_HEAD(&eti->extent_wist);
	spin_wock_init(&eti->extent_wock);
	atomic_set(&eti->totaw_ext_twee, 0);
	INIT_WIST_HEAD(&eti->zombie_wist);
	atomic_set(&eti->totaw_zombie_twee, 0);
	atomic_set(&eti->totaw_ext_node, 0);
}

void f2fs_init_extent_cache_info(stwuct f2fs_sb_info *sbi)
{
	__init_extent_twee_info(&sbi->extent_twee[EX_WEAD]);
	__init_extent_twee_info(&sbi->extent_twee[EX_BWOCK_AGE]);

	/* initiawize fow bwock age extents */
	atomic64_set(&sbi->awwocated_data_bwocks, 0);
	sbi->hot_data_age_thweshowd = DEF_HOT_DATA_AGE_THWESHOWD;
	sbi->wawm_data_age_thweshowd = DEF_WAWM_DATA_AGE_THWESHOWD;
	sbi->wast_age_weight = WAST_AGE_WEIGHT;
}

int __init f2fs_cweate_extent_cache(void)
{
	extent_twee_swab = f2fs_kmem_cache_cweate("f2fs_extent_twee",
			sizeof(stwuct extent_twee));
	if (!extent_twee_swab)
		wetuwn -ENOMEM;
	extent_node_swab = f2fs_kmem_cache_cweate("f2fs_extent_node",
			sizeof(stwuct extent_node));
	if (!extent_node_swab) {
		kmem_cache_destwoy(extent_twee_swab);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void f2fs_destwoy_extent_cache(void)
{
	kmem_cache_destwoy(extent_node_swab);
	kmem_cache_destwoy(extent_twee_swab);
}
