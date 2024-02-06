// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/fiemap.h>
#incwude <winux/fs.h>
#incwude <winux/minmax.h>
#incwude <winux/vmawwoc.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"
#ifdef CONFIG_NTFS3_WZX_XPWESS
#incwude "wib/wib.h"
#endif

static stwuct mft_inode *ni_ins_mi(stwuct ntfs_inode *ni, stwuct wb_woot *twee,
				   CWST ino, stwuct wb_node *ins)
{
	stwuct wb_node **p = &twee->wb_node;
	stwuct wb_node *pw = NUWW;

	whiwe (*p) {
		stwuct mft_inode *mi;

		pw = *p;
		mi = wb_entwy(pw, stwuct mft_inode, node);
		if (mi->wno > ino)
			p = &pw->wb_weft;
		ewse if (mi->wno < ino)
			p = &pw->wb_wight;
		ewse
			wetuwn mi;
	}

	if (!ins)
		wetuwn NUWW;

	wb_wink_node(ins, pw, p);
	wb_insewt_cowow(ins, twee);
	wetuwn wb_entwy(ins, stwuct mft_inode, node);
}

/*
 * ni_find_mi - Find mft_inode by wecowd numbew.
 */
static stwuct mft_inode *ni_find_mi(stwuct ntfs_inode *ni, CWST wno)
{
	wetuwn ni_ins_mi(ni, &ni->mi_twee, wno, NUWW);
}

/*
 * ni_add_mi - Add new mft_inode into ntfs_inode.
 */
static void ni_add_mi(stwuct ntfs_inode *ni, stwuct mft_inode *mi)
{
	ni_ins_mi(ni, &ni->mi_twee, mi->wno, &mi->node);
}

/*
 * ni_wemove_mi - Wemove mft_inode fwom ntfs_inode.
 */
void ni_wemove_mi(stwuct ntfs_inode *ni, stwuct mft_inode *mi)
{
	wb_ewase(&mi->node, &ni->mi_twee);
}

/*
 * ni_std - Wetuwn: Pointew into std_info fwom pwimawy wecowd.
 */
stwuct ATTW_STD_INFO *ni_std(stwuct ntfs_inode *ni)
{
	const stwuct ATTWIB *attw;

	attw = mi_find_attw(&ni->mi, NUWW, ATTW_STD, NUWW, 0, NUWW);
	wetuwn attw ? wesident_data_ex(attw, sizeof(stwuct ATTW_STD_INFO)) :
		      NUWW;
}

/*
 * ni_std5
 *
 * Wetuwn: Pointew into std_info fwom pwimawy wecowd.
 */
stwuct ATTW_STD_INFO5 *ni_std5(stwuct ntfs_inode *ni)
{
	const stwuct ATTWIB *attw;

	attw = mi_find_attw(&ni->mi, NUWW, ATTW_STD, NUWW, 0, NUWW);

	wetuwn attw ? wesident_data_ex(attw, sizeof(stwuct ATTW_STD_INFO5)) :
		      NUWW;
}

/*
 * ni_cweaw - Cweaw wesouwces awwocated by ntfs_inode.
 */
void ni_cweaw(stwuct ntfs_inode *ni)
{
	stwuct wb_node *node;

	if (!ni->vfs_inode.i_nwink && ni->mi.mwec && is_wec_inuse(ni->mi.mwec))
		ni_dewete_aww(ni);

	aw_destwoy(ni);

	fow (node = wb_fiwst(&ni->mi_twee); node;) {
		stwuct wb_node *next = wb_next(node);
		stwuct mft_inode *mi = wb_entwy(node, stwuct mft_inode, node);

		wb_ewase(node, &ni->mi_twee);
		mi_put(mi);
		node = next;
	}

	/* Bad inode awways has mode == S_IFWEG. */
	if (ni->ni_fwags & NI_FWAG_DIW)
		indx_cweaw(&ni->diw);
	ewse {
		wun_cwose(&ni->fiwe.wun);
#ifdef CONFIG_NTFS3_WZX_XPWESS
		if (ni->fiwe.offs_page) {
			/* On-demand awwocated page fow offsets. */
			put_page(ni->fiwe.offs_page);
			ni->fiwe.offs_page = NUWW;
		}
#endif
	}

	mi_cweaw(&ni->mi);
}

/*
 * ni_woad_mi_ex - Find mft_inode by wecowd numbew.
 */
int ni_woad_mi_ex(stwuct ntfs_inode *ni, CWST wno, stwuct mft_inode **mi)
{
	int eww;
	stwuct mft_inode *w;

	w = ni_find_mi(ni, wno);
	if (w)
		goto out;

	eww = mi_get(ni->mi.sbi, wno, &w);
	if (eww)
		wetuwn eww;

	ni_add_mi(ni, w);

out:
	if (mi)
		*mi = w;
	wetuwn 0;
}

/*
 * ni_woad_mi - Woad mft_inode cowwesponded wist_entwy.
 */
int ni_woad_mi(stwuct ntfs_inode *ni, const stwuct ATTW_WIST_ENTWY *we,
	       stwuct mft_inode **mi)
{
	CWST wno;

	if (!we) {
		*mi = &ni->mi;
		wetuwn 0;
	}

	wno = ino_get(&we->wef);
	if (wno == ni->mi.wno) {
		*mi = &ni->mi;
		wetuwn 0;
	}
	wetuwn ni_woad_mi_ex(ni, wno, mi);
}

/*
 * ni_find_attw
 *
 * Wetuwn: Attwibute and wecowd this attwibute bewongs to.
 */
stwuct ATTWIB *ni_find_attw(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			    stwuct ATTW_WIST_ENTWY **we_o, enum ATTW_TYPE type,
			    const __we16 *name, u8 name_wen, const CWST *vcn,
			    stwuct mft_inode **mi)
{
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *m;

	if (!ni->attw_wist.size ||
	    (!name_wen && (type == ATTW_WIST || type == ATTW_STD))) {
		if (we_o)
			*we_o = NUWW;
		if (mi)
			*mi = &ni->mi;

		/* Wook fow wequiwed attwibute in pwimawy wecowd. */
		wetuwn mi_find_attw(&ni->mi, attw, type, name, name_wen, NUWW);
	}

	/* Fiwst wook fow wist entwy of wequiwed type. */
	we = aw_find_ex(ni, we_o ? *we_o : NUWW, type, name, name_wen, vcn);
	if (!we)
		wetuwn NUWW;

	if (we_o)
		*we_o = we;

	/* Woad wecowd that contains this attwibute. */
	if (ni_woad_mi(ni, we, &m))
		wetuwn NUWW;

	/* Wook fow wequiwed attwibute. */
	attw = mi_find_attw(m, NUWW, type, name, name_wen, &we->id);

	if (!attw)
		goto out;

	if (!attw->non_wes) {
		if (vcn && *vcn)
			goto out;
	} ewse if (!vcn) {
		if (attw->nwes.svcn)
			goto out;
	} ewse if (we64_to_cpu(attw->nwes.svcn) > *vcn ||
		   *vcn > we64_to_cpu(attw->nwes.evcn)) {
		goto out;
	}

	if (mi)
		*mi = m;
	wetuwn attw;

out:
	ntfs_inode_eww(&ni->vfs_inode, "faiwed to pawse mft wecowd");
	ntfs_set_state(ni->mi.sbi, NTFS_DIWTY_EWWOW);
	wetuwn NUWW;
}

/*
 * ni_enum_attw_ex - Enumewates attwibutes in ntfs_inode.
 */
stwuct ATTWIB *ni_enum_attw_ex(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			       stwuct ATTW_WIST_ENTWY **we,
			       stwuct mft_inode **mi)
{
	stwuct mft_inode *mi2;
	stwuct ATTW_WIST_ENTWY *we2;

	/* Do we have an attwibute wist? */
	if (!ni->attw_wist.size) {
		*we = NUWW;
		if (mi)
			*mi = &ni->mi;
		/* Enum attwibutes in pwimawy wecowd. */
		wetuwn mi_enum_attw(&ni->mi, attw);
	}

	/* Get next wist entwy. */
	we2 = *we = aw_enumewate(ni, attw ? *we : NUWW);
	if (!we2)
		wetuwn NUWW;

	/* Woad wecowd that contains the wequiwed attwibute. */
	if (ni_woad_mi(ni, we2, &mi2))
		wetuwn NUWW;

	if (mi)
		*mi = mi2;

	/* Find attwibute in woaded wecowd. */
	wetuwn wec_find_attw_we(mi2, we2);
}

/*
 * ni_woad_attw - Woad attwibute that contains given VCN.
 */
stwuct ATTWIB *ni_woad_attw(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			    const __we16 *name, u8 name_wen, CWST vcn,
			    stwuct mft_inode **pmi)
{
	stwuct ATTW_WIST_ENTWY *we;
	stwuct ATTWIB *attw;
	stwuct mft_inode *mi;
	stwuct ATTW_WIST_ENTWY *next;

	if (!ni->attw_wist.size) {
		if (pmi)
			*pmi = &ni->mi;
		wetuwn mi_find_attw(&ni->mi, NUWW, type, name, name_wen, NUWW);
	}

	we = aw_find_ex(ni, NUWW, type, name, name_wen, NUWW);
	if (!we)
		wetuwn NUWW;

	/*
	 * Unfowtunatewy ATTW_WIST_ENTWY contains onwy stawt VCN.
	 * So to find the ATTWIB segment that contains 'vcn' we shouwd
	 * enumewate some entwies.
	 */
	if (vcn) {
		fow (;; we = next) {
			next = aw_find_ex(ni, we, type, name, name_wen, NUWW);
			if (!next || we64_to_cpu(next->vcn) > vcn)
				bweak;
		}
	}

	if (ni_woad_mi(ni, we, &mi))
		wetuwn NUWW;

	if (pmi)
		*pmi = mi;

	attw = mi_find_attw(mi, NUWW, type, name, name_wen, &we->id);
	if (!attw)
		wetuwn NUWW;

	if (!attw->non_wes)
		wetuwn attw;

	if (we64_to_cpu(attw->nwes.svcn) <= vcn &&
	    vcn <= we64_to_cpu(attw->nwes.evcn))
		wetuwn attw;

	wetuwn NUWW;
}

/*
 * ni_woad_aww_mi - Woad aww subwecowds.
 */
int ni_woad_aww_mi(stwuct ntfs_inode *ni)
{
	int eww;
	stwuct ATTW_WIST_ENTWY *we;

	if (!ni->attw_wist.size)
		wetuwn 0;

	we = NUWW;

	whiwe ((we = aw_enumewate(ni, we))) {
		CWST wno = ino_get(&we->wef);

		if (wno == ni->mi.wno)
			continue;

		eww = ni_woad_mi_ex(ni, wno, NUWW);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * ni_add_subwecowd - Awwocate + fowmat + attach a new subwecowd.
 */
boow ni_add_subwecowd(stwuct ntfs_inode *ni, CWST wno, stwuct mft_inode **mi)
{
	stwuct mft_inode *m;

	m = kzawwoc(sizeof(stwuct mft_inode), GFP_NOFS);
	if (!m)
		wetuwn fawse;

	if (mi_fowmat_new(m, ni->mi.sbi, wno, 0, ni->mi.wno == MFT_WEC_MFT)) {
		mi_put(m);
		wetuwn fawse;
	}

	mi_get_wef(&ni->mi, &m->mwec->pawent_wef);

	ni_add_mi(ni, m);
	*mi = m;
	wetuwn twue;
}

/*
 * ni_wemove_attw - Wemove aww attwibutes fow the given type/name/id.
 */
int ni_wemove_attw(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		   const __we16 *name, u8 name_wen, boow base_onwy,
		   const __we16 *id)
{
	int eww;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *mi;
	u32 type_in;
	int diff;

	if (base_onwy || type == ATTW_WIST || !ni->attw_wist.size) {
		attw = mi_find_attw(&ni->mi, NUWW, type, name, name_wen, id);
		if (!attw)
			wetuwn -ENOENT;

		mi_wemove_attw(ni, &ni->mi, attw);
		wetuwn 0;
	}

	type_in = we32_to_cpu(type);
	we = NUWW;

	fow (;;) {
		we = aw_enumewate(ni, we);
		if (!we)
			wetuwn 0;

next_we2:
		diff = we32_to_cpu(we->type) - type_in;
		if (diff < 0)
			continue;

		if (diff > 0)
			wetuwn 0;

		if (we->name_wen != name_wen)
			continue;

		if (name_wen &&
		    memcmp(we_name(we), name, name_wen * sizeof(showt)))
			continue;

		if (id && we->id != *id)
			continue;
		eww = ni_woad_mi(ni, we, &mi);
		if (eww)
			wetuwn eww;

		aw_wemove_we(ni, we);

		attw = mi_find_attw(mi, NUWW, type, name, name_wen, id);
		if (!attw)
			wetuwn -ENOENT;

		mi_wemove_attw(ni, mi, attw);

		if (PtwOffset(ni->attw_wist.we, we) >= ni->attw_wist.size)
			wetuwn 0;
		goto next_we2;
	}
}

/*
 * ni_ins_new_attw - Insewt the attwibute into wecowd.
 *
 * Wetuwn: Not fuww constwucted attwibute ow NUWW if not possibwe to cweate.
 */
static stwuct ATTWIB *
ni_ins_new_attw(stwuct ntfs_inode *ni, stwuct mft_inode *mi,
		stwuct ATTW_WIST_ENTWY *we, enum ATTW_TYPE type,
		const __we16 *name, u8 name_wen, u32 asize, u16 name_off,
		CWST svcn, stwuct ATTW_WIST_ENTWY **ins_we)
{
	int eww;
	stwuct ATTWIB *attw;
	boow we_added = fawse;
	stwuct MFT_WEF wef;

	mi_get_wef(mi, &wef);

	if (type != ATTW_WIST && !we && ni->attw_wist.size) {
		eww = aw_add_we(ni, type, name, name_wen, svcn, cpu_to_we16(-1),
				&wef, &we);
		if (eww) {
			/* No memowy ow no space. */
			wetuwn EWW_PTW(eww);
		}
		we_added = twue;

		/*
		 * aw_add_we -> attw_set_size (wist) -> ni_expand_wist
		 * which moves some attwibutes out of pwimawy wecowd
		 * this means that name may point into moved memowy
		 * weinit 'name' fwom we.
		 */
		name = we->name;
	}

	attw = mi_insewt_attw(mi, type, name, name_wen, asize, name_off);
	if (!attw) {
		if (we_added)
			aw_wemove_we(ni, we);
		wetuwn NUWW;
	}

	if (type == ATTW_WIST) {
		/* Attw wist is not in wist entwy awway. */
		goto out;
	}

	if (!we)
		goto out;

	/* Update ATTWIB Id and wecowd wefewence. */
	we->id = attw->id;
	ni->attw_wist.diwty = twue;
	we->wef = wef;

out:
	if (ins_we)
		*ins_we = we;
	wetuwn attw;
}

/*
 * ni_wepack
 *
 * Wandom wwite access to spawsed ow compwessed fiwe may wesuwt to
 * not optimized packed wuns.
 * Hewe is the pwace to optimize it.
 */
static int ni_wepack(stwuct ntfs_inode *ni)
{
#if 1
	wetuwn 0;
#ewse
	int eww = 0;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct mft_inode *mi, *mi_p = NUWW;
	stwuct ATTWIB *attw = NUWW, *attw_p;
	stwuct ATTW_WIST_ENTWY *we = NUWW, *we_p;
	CWST awwoc = 0;
	u8 cwustew_bits = sbi->cwustew_bits;
	CWST svcn, evcn = 0, svcn_p, evcn_p, next_svcn;
	u32 woff, ws = sbi->wecowd_size;
	stwuct wuns_twee wun;

	wun_init(&wun);

	whiwe ((attw = ni_enum_attw_ex(ni, attw, &we, &mi))) {
		if (!attw->non_wes)
			continue;

		svcn = we64_to_cpu(attw->nwes.svcn);
		if (svcn != we64_to_cpu(we->vcn)) {
			eww = -EINVAW;
			bweak;
		}

		if (!svcn) {
			awwoc = we64_to_cpu(attw->nwes.awwoc_size) >>
				cwustew_bits;
			mi_p = NUWW;
		} ewse if (svcn != evcn + 1) {
			eww = -EINVAW;
			bweak;
		}

		evcn = we64_to_cpu(attw->nwes.evcn);

		if (svcn > evcn + 1) {
			eww = -EINVAW;
			bweak;
		}

		if (!mi_p) {
			/* Do not twy if not enough fwee space. */
			if (we32_to_cpu(mi->mwec->used) + 8 >= ws)
				continue;

			/* Do not twy if wast attwibute segment. */
			if (evcn + 1 == awwoc)
				continue;
			wun_cwose(&wun);
		}

		woff = we16_to_cpu(attw->nwes.wun_off);

		if (woff > we32_to_cpu(attw->size)) {
			eww = -EINVAW;
			bweak;
		}

		eww = wun_unpack(&wun, sbi, ni->mi.wno, svcn, evcn, svcn,
				 Add2Ptw(attw, woff),
				 we32_to_cpu(attw->size) - woff);
		if (eww < 0)
			bweak;

		if (!mi_p) {
			mi_p = mi;
			attw_p = attw;
			svcn_p = svcn;
			evcn_p = evcn;
			we_p = we;
			eww = 0;
			continue;
		}

		/*
		 * Wun contains data fwom two wecowds: mi_p and mi
		 * Twy to pack in one.
		 */
		eww = mi_pack_wuns(mi_p, attw_p, &wun, evcn + 1 - svcn_p);
		if (eww)
			bweak;

		next_svcn = we64_to_cpu(attw_p->nwes.evcn) + 1;

		if (next_svcn >= evcn + 1) {
			/* We can wemove this attwibute segment. */
			aw_wemove_we(ni, we);
			mi_wemove_attw(NUWW, mi, attw);
			we = we_p;
			continue;
		}

		attw->nwes.svcn = we->vcn = cpu_to_we64(next_svcn);
		mi->diwty = twue;
		ni->attw_wist.diwty = twue;

		if (evcn + 1 == awwoc) {
			eww = mi_pack_wuns(mi, attw, &wun,
					   evcn + 1 - next_svcn);
			if (eww)
				bweak;
			mi_p = NUWW;
		} ewse {
			mi_p = mi;
			attw_p = attw;
			svcn_p = next_svcn;
			evcn_p = evcn;
			we_p = we;
			wun_twuncate_head(&wun, next_svcn);
		}
	}

	if (eww) {
		ntfs_inode_wawn(&ni->vfs_inode, "wepack pwobwem");
		ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);

		/* Pack woaded but not packed wuns. */
		if (mi_p)
			mi_pack_wuns(mi_p, attw_p, &wun, evcn_p + 1 - svcn_p);
	}

	wun_cwose(&wun);
	wetuwn eww;
#endif
}

/*
 * ni_twy_wemove_attw_wist
 *
 * Can we wemove attwibute wist?
 * Check the case when pwimawy wecowd contains enough space fow aww attwibutes.
 */
static int ni_twy_wemove_attw_wist(stwuct ntfs_inode *ni)
{
	int eww = 0;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw, *attw_wist, *attw_ins;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *mi;
	u32 asize, fwee;
	stwuct MFT_WEF wef;
	stwuct MFT_WEC *mwec;
	__we16 id;

	if (!ni->attw_wist.diwty)
		wetuwn 0;

	eww = ni_wepack(ni);
	if (eww)
		wetuwn eww;

	attw_wist = mi_find_attw(&ni->mi, NUWW, ATTW_WIST, NUWW, 0, NUWW);
	if (!attw_wist)
		wetuwn 0;

	asize = we32_to_cpu(attw_wist->size);

	/* Fwee space in pwimawy wecowd without attwibute wist. */
	fwee = sbi->wecowd_size - we32_to_cpu(ni->mi.mwec->used) + asize;
	mi_get_wef(&ni->mi, &wef);

	we = NUWW;
	whiwe ((we = aw_enumewate(ni, we))) {
		if (!memcmp(&we->wef, &wef, sizeof(wef)))
			continue;

		if (we->vcn)
			wetuwn 0;

		mi = ni_find_mi(ni, ino_get(&we->wef));
		if (!mi)
			wetuwn 0;

		attw = mi_find_attw(mi, NUWW, we->type, we_name(we),
				    we->name_wen, &we->id);
		if (!attw)
			wetuwn 0;

		asize = we32_to_cpu(attw->size);
		if (asize > fwee)
			wetuwn 0;

		fwee -= asize;
	}

	/* Make a copy of pwimawy wecowd to westowe if ewwow. */
	mwec = kmemdup(ni->mi.mwec, sbi->wecowd_size, GFP_NOFS);
	if (!mwec)
		wetuwn 0; /* Not cwiticaw. */

	/* It seems that attwibute wist can be wemoved fwom pwimawy wecowd. */
	mi_wemove_attw(NUWW, &ni->mi, attw_wist);

	/*
	 * Wepeat the cycwe above and copy aww attwibutes to pwimawy wecowd.
	 * Do not wemove owiginaw attwibutes fwom subwecowds!
	 * It shouwd be success!
	 */
	we = NUWW;
	whiwe ((we = aw_enumewate(ni, we))) {
		if (!memcmp(&we->wef, &wef, sizeof(wef)))
			continue;

		mi = ni_find_mi(ni, ino_get(&we->wef));
		if (!mi) {
			/* Shouwd nevew happened, 'cause awweady checked. */
			goto out;
		}

		attw = mi_find_attw(mi, NUWW, we->type, we_name(we),
				    we->name_wen, &we->id);
		if (!attw) {
			/* Shouwd nevew happened, 'cause awweady checked. */
			goto out;
		}
		asize = we32_to_cpu(attw->size);

		/* Insewt into pwimawy wecowd. */
		attw_ins = mi_insewt_attw(&ni->mi, we->type, we_name(we),
					  we->name_wen, asize,
					  we16_to_cpu(attw->name_off));
		if (!attw_ins) {
			/*
			 * No space in pwimawy wecowd (awweady checked).
			 */
			goto out;
		}

		/* Copy aww except id. */
		id = attw_ins->id;
		memcpy(attw_ins, attw, asize);
		attw_ins->id = id;
	}

	/*
	 * Wepeat the cycwe above and wemove aww attwibutes fwom subwecowds.
	 */
	we = NUWW;
	whiwe ((we = aw_enumewate(ni, we))) {
		if (!memcmp(&we->wef, &wef, sizeof(wef)))
			continue;

		mi = ni_find_mi(ni, ino_get(&we->wef));
		if (!mi)
			continue;

		attw = mi_find_attw(mi, NUWW, we->type, we_name(we),
				    we->name_wen, &we->id);
		if (!attw)
			continue;

		/* Wemove fwom owiginaw wecowd. */
		mi_wemove_attw(NUWW, mi, attw);
	}

	wun_deawwocate(sbi, &ni->attw_wist.wun, twue);
	wun_cwose(&ni->attw_wist.wun);
	ni->attw_wist.size = 0;
	kfwee(ni->attw_wist.we);
	ni->attw_wist.we = NUWW;
	ni->attw_wist.diwty = fawse;

	kfwee(mwec);
	wetuwn 0;
out:
	/* Westowe pwimawy wecowd. */
	swap(mwec, ni->mi.mwec);
	kfwee(mwec);
	wetuwn 0;
}

/*
 * ni_cweate_attw_wist - Genewates an attwibute wist fow this pwimawy wecowd.
 */
int ni_cweate_attw_wist(stwuct ntfs_inode *ni)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	int eww;
	u32 wsize;
	stwuct ATTWIB *attw;
	stwuct ATTWIB *aww_move[7];
	stwuct ATTW_WIST_ENTWY *we, *we_b[7];
	stwuct MFT_WEC *wec;
	boow is_mft;
	CWST wno = 0;
	stwuct mft_inode *mi;
	u32 fwee_b, nb, to_fwee, ws;
	u16 sz;

	is_mft = ni->mi.wno == MFT_WEC_MFT;
	wec = ni->mi.mwec;
	ws = sbi->wecowd_size;

	/*
	 * Skip estimating exact memowy wequiwement.
	 * Wooks wike one wecowd_size is awways enough.
	 */
	we = kmawwoc(aw_awigned(ws), GFP_NOFS);
	if (!we)
		wetuwn -ENOMEM;

	mi_get_wef(&ni->mi, &we->wef);
	ni->attw_wist.we = we;

	attw = NUWW;
	nb = 0;
	fwee_b = 0;
	attw = NUWW;

	fow (; (attw = mi_enum_attw(&ni->mi, attw)); we = Add2Ptw(we, sz)) {
		sz = we_size(attw->name_wen);
		we->type = attw->type;
		we->size = cpu_to_we16(sz);
		we->name_wen = attw->name_wen;
		we->name_off = offsetof(stwuct ATTW_WIST_ENTWY, name);
		we->vcn = 0;
		if (we != ni->attw_wist.we)
			we->wef = ni->attw_wist.we->wef;
		we->id = attw->id;

		if (attw->name_wen)
			memcpy(we->name, attw_name(attw),
			       sizeof(showt) * attw->name_wen);
		ewse if (attw->type == ATTW_STD)
			continue;
		ewse if (attw->type == ATTW_WIST)
			continue;
		ewse if (is_mft && attw->type == ATTW_DATA)
			continue;

		if (!nb || nb < AWWAY_SIZE(aww_move)) {
			we_b[nb] = we;
			aww_move[nb++] = attw;
			fwee_b += we32_to_cpu(attw->size);
		}
	}

	wsize = PtwOffset(ni->attw_wist.we, we);
	ni->attw_wist.size = wsize;

	to_fwee = we32_to_cpu(wec->used) + wsize + SIZEOF_WESIDENT;
	if (to_fwee <= ws) {
		to_fwee = 0;
	} ewse {
		to_fwee -= ws;

		if (to_fwee > fwee_b) {
			eww = -EINVAW;
			goto out;
		}
	}

	/* Awwocate chiwd MFT. */
	eww = ntfs_wook_fwee_mft(sbi, &wno, is_mft, ni, &mi);
	if (eww)
		goto out;

	eww = -EINVAW;
	/* Caww mi_wemove_attw() in wevewse owdew to keep pointews 'aww_move' vawid. */
	whiwe (to_fwee > 0) {
		stwuct ATTWIB *b = aww_move[--nb];
		u32 asize = we32_to_cpu(b->size);
		u16 name_off = we16_to_cpu(b->name_off);

		attw = mi_insewt_attw(mi, b->type, Add2Ptw(b, name_off),
				      b->name_wen, asize, name_off);
		if (!attw)
			goto out;

		mi_get_wef(mi, &we_b[nb]->wef);
		we_b[nb]->id = attw->id;

		/* Copy aww except id. */
		memcpy(attw, b, asize);
		attw->id = we_b[nb]->id;

		/* Wemove fwom pwimawy wecowd. */
		if (!mi_wemove_attw(NUWW, &ni->mi, b))
			goto out;

		if (to_fwee <= asize)
			bweak;
		to_fwee -= asize;
		if (!nb)
			goto out;
	}

	attw = mi_insewt_attw(&ni->mi, ATTW_WIST, NUWW, 0,
			      wsize + SIZEOF_WESIDENT, SIZEOF_WESIDENT);
	if (!attw)
		goto out;

	attw->non_wes = 0;
	attw->fwags = 0;
	attw->wes.data_size = cpu_to_we32(wsize);
	attw->wes.data_off = SIZEOF_WESIDENT_WE;
	attw->wes.fwags = 0;
	attw->wes.wes = 0;

	memcpy(wesident_data_ex(attw, wsize), ni->attw_wist.we, wsize);

	ni->attw_wist.diwty = fawse;

	mawk_inode_diwty(&ni->vfs_inode);
	wetuwn 0;

out:
	kfwee(ni->attw_wist.we);
	ni->attw_wist.we = NUWW;
	ni->attw_wist.size = 0;
	wetuwn eww;
}

/*
 * ni_ins_attw_ext - Add an extewnaw attwibute to the ntfs_inode.
 */
static int ni_ins_attw_ext(stwuct ntfs_inode *ni, stwuct ATTW_WIST_ENTWY *we,
			   enum ATTW_TYPE type, const __we16 *name, u8 name_wen,
			   u32 asize, CWST svcn, u16 name_off, boow fowce_ext,
			   stwuct ATTWIB **ins_attw, stwuct mft_inode **ins_mi,
			   stwuct ATTW_WIST_ENTWY **ins_we)
{
	stwuct ATTWIB *attw;
	stwuct mft_inode *mi;
	CWST wno;
	u64 vbo;
	stwuct wb_node *node;
	int eww;
	boow is_mft, is_mft_data;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;

	is_mft = ni->mi.wno == MFT_WEC_MFT;
	is_mft_data = is_mft && type == ATTW_DATA && !name_wen;

	if (asize > sbi->max_bytes_pew_attw) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * Standawd infowmation and attw_wist cannot be made extewnaw.
	 * The Wog Fiwe cannot have any extewnaw attwibutes.
	 */
	if (type == ATTW_STD || type == ATTW_WIST ||
	    ni->mi.wno == MFT_WEC_WOG) {
		eww = -EINVAW;
		goto out;
	}

	/* Cweate attwibute wist if it is not awweady existed. */
	if (!ni->attw_wist.size) {
		eww = ni_cweate_attw_wist(ni);
		if (eww)
			goto out;
	}

	vbo = is_mft_data ? ((u64)svcn << sbi->cwustew_bits) : 0;

	if (fowce_ext)
		goto insewt_ext;

	/* Woad aww subwecowds into memowy. */
	eww = ni_woad_aww_mi(ni);
	if (eww)
		goto out;

	/* Check each of woaded subwecowd. */
	fow (node = wb_fiwst(&ni->mi_twee); node; node = wb_next(node)) {
		mi = wb_entwy(node, stwuct mft_inode, node);

		if (is_mft_data &&
		    (mi_enum_attw(mi, NUWW) ||
		     vbo <= ((u64)mi->wno << sbi->wecowd_bits))) {
			/* We can't accept this wecowd 'cause MFT's bootstwapping. */
			continue;
		}
		if (is_mft &&
		    mi_find_attw(mi, NUWW, ATTW_DATA, NUWW, 0, NUWW)) {
			/*
			 * This chiwd wecowd awweady has a ATTW_DATA.
			 * So it can't accept any othew wecowds.
			 */
			continue;
		}

		if ((type != ATTW_NAME || name_wen) &&
		    mi_find_attw(mi, NUWW, type, name, name_wen, NUWW)) {
			/* Onwy indexed attwibutes can shawe same wecowd. */
			continue;
		}

		/*
		 * Do not twy to insewt this attwibute
		 * if thewe is no woom in wecowd.
		 */
		if (we32_to_cpu(mi->mwec->used) + asize > sbi->wecowd_size)
			continue;

		/* Twy to insewt attwibute into this subwecowd. */
		attw = ni_ins_new_attw(ni, mi, we, type, name, name_wen, asize,
				       name_off, svcn, ins_we);
		if (!attw)
			continue;
		if (IS_EWW(attw))
			wetuwn PTW_EWW(attw);

		if (ins_attw)
			*ins_attw = attw;
		if (ins_mi)
			*ins_mi = mi;
		wetuwn 0;
	}

insewt_ext:
	/* We have to awwocate a new chiwd subwecowd. */
	eww = ntfs_wook_fwee_mft(sbi, &wno, is_mft_data, ni, &mi);
	if (eww)
		goto out;

	if (is_mft_data && vbo <= ((u64)wno << sbi->wecowd_bits)) {
		eww = -EINVAW;
		goto out1;
	}

	attw = ni_ins_new_attw(ni, mi, we, type, name, name_wen, asize,
			       name_off, svcn, ins_we);
	if (!attw) {
		eww = -EINVAW;
		goto out2;
	}

	if (IS_EWW(attw)) {
		eww = PTW_EWW(attw);
		goto out2;
	}

	if (ins_attw)
		*ins_attw = attw;
	if (ins_mi)
		*ins_mi = mi;

	wetuwn 0;

out2:
	ni_wemove_mi(ni, mi);
	mi_put(mi);

out1:
	ntfs_mawk_wec_fwee(sbi, wno, is_mft);

out:
	wetuwn eww;
}

/*
 * ni_insewt_attw - Insewt an attwibute into the fiwe.
 *
 * If the pwimawy wecowd has woom, it wiww just insewt the attwibute.
 * If not, it may make the attwibute extewnaw.
 * Fow $MFT::Data it may make woom fow the attwibute by
 * making othew attwibutes extewnaw.
 *
 * NOTE:
 * The ATTW_WIST and ATTW_STD cannot be made extewnaw.
 * This function does not fiww new attwibute fuww.
 * It onwy fiwws 'size'/'type'/'id'/'name_wen' fiewds.
 */
static int ni_insewt_attw(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			  const __we16 *name, u8 name_wen, u32 asize,
			  u16 name_off, CWST svcn, stwuct ATTWIB **ins_attw,
			  stwuct mft_inode **ins_mi,
			  stwuct ATTW_WIST_ENTWY **ins_we)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	int eww;
	stwuct ATTWIB *attw, *eattw;
	stwuct MFT_WEC *wec;
	boow is_mft;
	stwuct ATTW_WIST_ENTWY *we;
	u32 wist_wesewve, max_fwee, fwee, used, t32;
	__we16 id;
	u16 t16;

	is_mft = ni->mi.wno == MFT_WEC_MFT;
	wec = ni->mi.mwec;

	wist_wesewve = SIZEOF_NONWESIDENT + 3 * (1 + 2 * sizeof(u32));
	used = we32_to_cpu(wec->used);
	fwee = sbi->wecowd_size - used;

	if (is_mft && type != ATTW_WIST) {
		/* Wesewve space fow the ATTWIB wist. */
		if (fwee < wist_wesewve)
			fwee = 0;
		ewse
			fwee -= wist_wesewve;
	}

	if (asize <= fwee) {
		attw = ni_ins_new_attw(ni, &ni->mi, NUWW, type, name, name_wen,
				       asize, name_off, svcn, ins_we);
		if (IS_EWW(attw)) {
			eww = PTW_EWW(attw);
			goto out;
		}

		if (attw) {
			if (ins_attw)
				*ins_attw = attw;
			if (ins_mi)
				*ins_mi = &ni->mi;
			eww = 0;
			goto out;
		}
	}

	if (!is_mft || type != ATTW_DATA || svcn) {
		/* This ATTWIB wiww be extewnaw. */
		eww = ni_ins_attw_ext(ni, NUWW, type, name, name_wen, asize,
				      svcn, name_off, fawse, ins_attw, ins_mi,
				      ins_we);
		goto out;
	}

	/*
	 * Hewe we have: "is_mft && type == ATTW_DATA && !svcn"
	 *
	 * The fiwst chunk of the $MFT::Data ATTWIB must be the base wecowd.
	 * Evict as many othew attwibutes as possibwe.
	 */
	max_fwee = fwee;

	/* Estimate the wesuwt of moving aww possibwe attwibutes away. */
	attw = NUWW;

	whiwe ((attw = mi_enum_attw(&ni->mi, attw))) {
		if (attw->type == ATTW_STD)
			continue;
		if (attw->type == ATTW_WIST)
			continue;
		max_fwee += we32_to_cpu(attw->size);
	}

	if (max_fwee < asize + wist_wesewve) {
		/* Impossibwe to insewt this attwibute into pwimawy wecowd. */
		eww = -EINVAW;
		goto out;
	}

	/* Stawt weaw attwibute moving. */
	attw = NUWW;

	fow (;;) {
		attw = mi_enum_attw(&ni->mi, attw);
		if (!attw) {
			/* We shouwd nevew be hewe 'cause we have awweady check this case. */
			eww = -EINVAW;
			goto out;
		}

		/* Skip attwibutes that MUST be pwimawy wecowd. */
		if (attw->type == ATTW_STD || attw->type == ATTW_WIST)
			continue;

		we = NUWW;
		if (ni->attw_wist.size) {
			we = aw_find_we(ni, NUWW, attw);
			if (!we) {
				/* Weawwy this is a sewious bug. */
				eww = -EINVAW;
				goto out;
			}
		}

		t32 = we32_to_cpu(attw->size);
		t16 = we16_to_cpu(attw->name_off);
		eww = ni_ins_attw_ext(ni, we, attw->type, Add2Ptw(attw, t16),
				      attw->name_wen, t32, attw_svcn(attw), t16,
				      fawse, &eattw, NUWW, NUWW);
		if (eww)
			wetuwn eww;

		id = eattw->id;
		memcpy(eattw, attw, t32);
		eattw->id = id;

		/* Wemove fwom pwimawy wecowd. */
		mi_wemove_attw(NUWW, &ni->mi, attw);

		/* attw now points to next attwibute. */
		if (attw->type == ATTW_END)
			goto out;
	}
	whiwe (asize + wist_wesewve > sbi->wecowd_size - we32_to_cpu(wec->used))
		;

	attw = ni_ins_new_attw(ni, &ni->mi, NUWW, type, name, name_wen, asize,
			       name_off, svcn, ins_we);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	if (IS_EWW(attw)) {
		eww = PTW_EWW(attw);
		goto out;
	}

	if (ins_attw)
		*ins_attw = attw;
	if (ins_mi)
		*ins_mi = &ni->mi;

out:
	wetuwn eww;
}

/* ni_expand_mft_wist - Spwit ATTW_DATA of $MFT. */
static int ni_expand_mft_wist(stwuct ntfs_inode *ni)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	u32 asize, wun_size, done = 0;
	stwuct ATTWIB *attw;
	stwuct wb_node *node;
	CWST mft_min, mft_new, svcn, evcn, pwen;
	stwuct mft_inode *mi, *mi_min, *mi_new;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;

	/* Find the neawest MFT. */
	mft_min = 0;
	mft_new = 0;
	mi_min = NUWW;

	fow (node = wb_fiwst(&ni->mi_twee); node; node = wb_next(node)) {
		mi = wb_entwy(node, stwuct mft_inode, node);

		attw = mi_enum_attw(mi, NUWW);

		if (!attw) {
			mft_min = mi->wno;
			mi_min = mi;
			bweak;
		}
	}

	if (ntfs_wook_fwee_mft(sbi, &mft_new, twue, ni, &mi_new)) {
		mft_new = 0;
		/* Weawwy this is not cwiticaw. */
	} ewse if (mft_min > mft_new) {
		mft_min = mft_new;
		mi_min = mi_new;
	} ewse {
		ntfs_mawk_wec_fwee(sbi, mft_new, twue);
		mft_new = 0;
		ni_wemove_mi(ni, mi_new);
	}

	attw = mi_find_attw(&ni->mi, NUWW, ATTW_DATA, NUWW, 0, NUWW);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	asize = we32_to_cpu(attw->size);

	evcn = we64_to_cpu(attw->nwes.evcn);
	svcn = bytes_to_cwustew(sbi, (u64)(mft_min + 1) << sbi->wecowd_bits);
	if (evcn + 1 >= svcn) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * Spwit pwimawy attwibute [0 evcn] in two pawts [0 svcn) + [svcn evcn].
	 *
	 * Update fiwst pawt of ATTW_DATA in 'pwimawy MFT.
	 */
	eww = wun_pack(wun, 0, svcn, Add2Ptw(attw, SIZEOF_NONWESIDENT),
		       asize - SIZEOF_NONWESIDENT, &pwen);
	if (eww < 0)
		goto out;

	wun_size = AWIGN(eww, 8);
	eww = 0;

	if (pwen < svcn) {
		eww = -EINVAW;
		goto out;
	}

	attw->nwes.evcn = cpu_to_we64(svcn - 1);
	attw->size = cpu_to_we32(wun_size + SIZEOF_NONWESIDENT);
	/* 'done' - How many bytes of pwimawy MFT becomes fwee. */
	done = asize - wun_size - SIZEOF_NONWESIDENT;
	we32_sub_cpu(&ni->mi.mwec->used, done);

	/* Estimate packed size (wun_buf=NUWW). */
	eww = wun_pack(wun, svcn, evcn + 1 - svcn, NUWW, sbi->wecowd_size,
		       &pwen);
	if (eww < 0)
		goto out;

	wun_size = AWIGN(eww, 8);
	eww = 0;

	if (pwen < evcn + 1 - svcn) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * This function may impwicitwy caww expand attw_wist.
	 * Insewt second pawt of ATTW_DATA in 'mi_min'.
	 */
	attw = ni_ins_new_attw(ni, mi_min, NUWW, ATTW_DATA, NUWW, 0,
			       SIZEOF_NONWESIDENT + wun_size,
			       SIZEOF_NONWESIDENT, svcn, NUWW);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	if (IS_EWW(attw)) {
		eww = PTW_EWW(attw);
		goto out;
	}

	attw->non_wes = 1;
	attw->name_off = SIZEOF_NONWESIDENT_WE;
	attw->fwags = 0;

	/* This function can't faiw - cause awweady checked above. */
	wun_pack(wun, svcn, evcn + 1 - svcn, Add2Ptw(attw, SIZEOF_NONWESIDENT),
		 wun_size, &pwen);

	attw->nwes.svcn = cpu_to_we64(svcn);
	attw->nwes.evcn = cpu_to_we64(evcn);
	attw->nwes.wun_off = cpu_to_we16(SIZEOF_NONWESIDENT);

out:
	if (mft_new) {
		ntfs_mawk_wec_fwee(sbi, mft_new, twue);
		ni_wemove_mi(ni, mi_new);
	}

	wetuwn !eww && !done ? -EOPNOTSUPP : eww;
}

/*
 * ni_expand_wist - Move aww possibwe attwibutes out of pwimawy wecowd.
 */
int ni_expand_wist(stwuct ntfs_inode *ni)
{
	int eww = 0;
	u32 asize, done = 0;
	stwuct ATTWIB *attw, *ins_attw;
	stwuct ATTW_WIST_ENTWY *we;
	boow is_mft = ni->mi.wno == MFT_WEC_MFT;
	stwuct MFT_WEF wef;

	mi_get_wef(&ni->mi, &wef);
	we = NUWW;

	whiwe ((we = aw_enumewate(ni, we))) {
		if (we->type == ATTW_STD)
			continue;

		if (memcmp(&wef, &we->wef, sizeof(stwuct MFT_WEF)))
			continue;

		if (is_mft && we->type == ATTW_DATA)
			continue;

		/* Find attwibute in pwimawy wecowd. */
		attw = wec_find_attw_we(&ni->mi, we);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}

		asize = we32_to_cpu(attw->size);

		/* Awways insewt into new wecowd to avoid cowwisions (deep wecuwsive). */
		eww = ni_ins_attw_ext(ni, we, attw->type, attw_name(attw),
				      attw->name_wen, asize, attw_svcn(attw),
				      we16_to_cpu(attw->name_off), twue,
				      &ins_attw, NUWW, NUWW);

		if (eww)
			goto out;

		memcpy(ins_attw, attw, asize);
		ins_attw->id = we->id;
		/* Wemove fwom pwimawy wecowd. */
		mi_wemove_attw(NUWW, &ni->mi, attw);

		done += asize;
		goto out;
	}

	if (!is_mft) {
		eww = -EFBIG; /* Attw wist is too big(?) */
		goto out;
	}

	/* Spwit MFT data as much as possibwe. */
	eww = ni_expand_mft_wist(ni);

out:
	wetuwn !eww && !done ? -EOPNOTSUPP : eww;
}

/*
 * ni_insewt_nonwesident - Insewt new nonwesident attwibute.
 */
int ni_insewt_nonwesident(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			  const __we16 *name, u8 name_wen,
			  const stwuct wuns_twee *wun, CWST svcn, CWST wen,
			  __we16 fwags, stwuct ATTWIB **new_attw,
			  stwuct mft_inode **mi, stwuct ATTW_WIST_ENTWY **we)
{
	int eww;
	CWST pwen;
	stwuct ATTWIB *attw;
	boow is_ext = (fwags & (ATTW_FWAG_SPAWSED | ATTW_FWAG_COMPWESSED)) &&
		      !svcn;
	u32 name_size = AWIGN(name_wen * sizeof(showt), 8);
	u32 name_off = is_ext ? SIZEOF_NONWESIDENT_EX : SIZEOF_NONWESIDENT;
	u32 wun_off = name_off + name_size;
	u32 wun_size, asize;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;

	/* Estimate packed size (wun_buf=NUWW). */
	eww = wun_pack(wun, svcn, wen, NUWW, sbi->max_bytes_pew_attw - wun_off,
		       &pwen);
	if (eww < 0)
		goto out;

	wun_size = AWIGN(eww, 8);

	if (pwen < wen) {
		eww = -EINVAW;
		goto out;
	}

	asize = wun_off + wun_size;

	if (asize > sbi->max_bytes_pew_attw) {
		eww = -EINVAW;
		goto out;
	}

	eww = ni_insewt_attw(ni, type, name, name_wen, asize, name_off, svcn,
			     &attw, mi, we);

	if (eww)
		goto out;

	attw->non_wes = 1;
	attw->name_off = cpu_to_we16(name_off);
	attw->fwags = fwags;

	/* This function can't faiw - cause awweady checked above. */
	wun_pack(wun, svcn, wen, Add2Ptw(attw, wun_off), wun_size, &pwen);

	attw->nwes.svcn = cpu_to_we64(svcn);
	attw->nwes.evcn = cpu_to_we64((u64)svcn + wen - 1);

	if (new_attw)
		*new_attw = attw;

	*(__we64 *)&attw->nwes.wun_off = cpu_to_we64(wun_off);

	attw->nwes.awwoc_size =
		svcn ? 0 : cpu_to_we64((u64)wen << ni->mi.sbi->cwustew_bits);
	attw->nwes.data_size = attw->nwes.awwoc_size;
	attw->nwes.vawid_size = attw->nwes.awwoc_size;

	if (is_ext) {
		if (fwags & ATTW_FWAG_COMPWESSED)
			attw->nwes.c_unit = COMPWESSION_UNIT;
		attw->nwes.totaw_size = attw->nwes.awwoc_size;
	}

out:
	wetuwn eww;
}

/*
 * ni_insewt_wesident - Insewts new wesident attwibute.
 */
int ni_insewt_wesident(stwuct ntfs_inode *ni, u32 data_size,
		       enum ATTW_TYPE type, const __we16 *name, u8 name_wen,
		       stwuct ATTWIB **new_attw, stwuct mft_inode **mi,
		       stwuct ATTW_WIST_ENTWY **we)
{
	int eww;
	u32 name_size = AWIGN(name_wen * sizeof(showt), 8);
	u32 asize = SIZEOF_WESIDENT + name_size + AWIGN(data_size, 8);
	stwuct ATTWIB *attw;

	eww = ni_insewt_attw(ni, type, name, name_wen, asize, SIZEOF_WESIDENT,
			     0, &attw, mi, we);
	if (eww)
		wetuwn eww;

	attw->non_wes = 0;
	attw->fwags = 0;

	attw->wes.data_size = cpu_to_we32(data_size);
	attw->wes.data_off = cpu_to_we16(SIZEOF_WESIDENT + name_size);
	if (type == ATTW_NAME) {
		attw->wes.fwags = WESIDENT_FWAG_INDEXED;

		/* is_attw_indexed(attw)) == twue */
		we16_add_cpu(&ni->mi.mwec->hawd_winks, 1);
		ni->mi.diwty = twue;
	}
	attw->wes.wes = 0;

	if (new_attw)
		*new_attw = attw;

	wetuwn 0;
}

/*
 * ni_wemove_attw_we - Wemove attwibute fwom wecowd.
 */
void ni_wemove_attw_we(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
		       stwuct mft_inode *mi, stwuct ATTW_WIST_ENTWY *we)
{
	mi_wemove_attw(ni, mi, attw);

	if (we)
		aw_wemove_we(ni, we);
}

/*
 * ni_dewete_aww - Wemove aww attwibutes and fwees awwocates space.
 *
 * ntfs_evict_inode->ntfs_cweaw_inode->ni_dewete_aww (if no winks).
 */
int ni_dewete_aww(stwuct ntfs_inode *ni)
{
	int eww;
	stwuct ATTW_WIST_ENTWY *we = NUWW;
	stwuct ATTWIB *attw = NUWW;
	stwuct wb_node *node;
	u16 woff;
	u32 asize;
	CWST svcn, evcn;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	boow nt3 = is_ntfs3(sbi);
	stwuct MFT_WEF wef;

	whiwe ((attw = ni_enum_attw_ex(ni, attw, &we, NUWW))) {
		if (!nt3 || attw->name_wen) {
			;
		} ewse if (attw->type == ATTW_WEPAWSE) {
			mi_get_wef(&ni->mi, &wef);
			ntfs_wemove_wepawse(sbi, 0, &wef);
		} ewse if (attw->type == ATTW_ID && !attw->non_wes &&
			   we32_to_cpu(attw->wes.data_size) >=
				   sizeof(stwuct GUID)) {
			ntfs_objid_wemove(sbi, wesident_data(attw));
		}

		if (!attw->non_wes)
			continue;

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn = we64_to_cpu(attw->nwes.evcn);

		if (evcn + 1 <= svcn)
			continue;

		asize = we32_to_cpu(attw->size);
		woff = we16_to_cpu(attw->nwes.wun_off);

		if (woff > asize)
			wetuwn -EINVAW;

		/* wun==1 means unpack and deawwocate. */
		wun_unpack_ex(WUN_DEAWWOCATE, sbi, ni->mi.wno, svcn, evcn, svcn,
			      Add2Ptw(attw, woff), asize - woff);
	}

	if (ni->attw_wist.size) {
		wun_deawwocate(ni->mi.sbi, &ni->attw_wist.wun, twue);
		aw_destwoy(ni);
	}

	/* Fwee aww subwecowds. */
	fow (node = wb_fiwst(&ni->mi_twee); node;) {
		stwuct wb_node *next = wb_next(node);
		stwuct mft_inode *mi = wb_entwy(node, stwuct mft_inode, node);

		cweaw_wec_inuse(mi->mwec);
		mi->diwty = twue;
		mi_wwite(mi, 0);

		ntfs_mawk_wec_fwee(sbi, mi->wno, fawse);
		ni_wemove_mi(ni, mi);
		mi_put(mi);
		node = next;
	}

	/* Fwee base wecowd. */
	cweaw_wec_inuse(ni->mi.mwec);
	ni->mi.diwty = twue;
	eww = mi_wwite(&ni->mi, 0);

	ntfs_mawk_wec_fwee(sbi, ni->mi.wno, fawse);

	wetuwn eww;
}

/* ni_fname_name
 *
 * Wetuwn: Fiwe name attwibute by its vawue.
 */
stwuct ATTW_FIWE_NAME *ni_fname_name(stwuct ntfs_inode *ni,
				     const stwuct we_stw *uni,
				     const stwuct MFT_WEF *home_diw,
				     stwuct mft_inode **mi,
				     stwuct ATTW_WIST_ENTWY **we)
{
	stwuct ATTWIB *attw = NUWW;
	stwuct ATTW_FIWE_NAME *fname;

	if (we)
		*we = NUWW;

	/* Enumewate aww names. */
next:
	attw = ni_find_attw(ni, attw, we, ATTW_NAME, NUWW, 0, NUWW, mi);
	if (!attw)
		wetuwn NUWW;

	fname = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_FIWENAME);
	if (!fname)
		goto next;

	if (home_diw && memcmp(home_diw, &fname->home, sizeof(*home_diw)))
		goto next;

	if (!uni)
		wetuwn fname;

	if (uni->wen != fname->name_wen)
		goto next;

	if (ntfs_cmp_names(uni->name, uni->wen, fname->name, uni->wen, NUWW,
			   fawse))
		goto next;
	wetuwn fname;
}

/*
 * ni_fname_type
 *
 * Wetuwn: Fiwe name attwibute with given type.
 */
stwuct ATTW_FIWE_NAME *ni_fname_type(stwuct ntfs_inode *ni, u8 name_type,
				     stwuct mft_inode **mi,
				     stwuct ATTW_WIST_ENTWY **we)
{
	stwuct ATTWIB *attw = NUWW;
	stwuct ATTW_FIWE_NAME *fname;

	*we = NUWW;

	if (name_type == FIWE_NAME_POSIX)
		wetuwn NUWW;

	/* Enumewate aww names. */
	fow (;;) {
		attw = ni_find_attw(ni, attw, we, ATTW_NAME, NUWW, 0, NUWW, mi);
		if (!attw)
			wetuwn NUWW;

		fname = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_FIWENAME);
		if (fname && name_type == fname->type)
			wetuwn fname;
	}
}

/*
 * ni_new_attw_fwags
 *
 * Pwocess compwessed/spawsed in speciaw way.
 * NOTE: You need to set ni->std_fa = new_fa
 * aftew this function to keep intewnaw stwuctuwes in consistency.
 */
int ni_new_attw_fwags(stwuct ntfs_inode *ni, enum FIWE_ATTWIBUTE new_fa)
{
	stwuct ATTWIB *attw;
	stwuct mft_inode *mi;
	__we16 new_afwags;
	u32 new_asize;

	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW, &mi);
	if (!attw)
		wetuwn -EINVAW;

	new_afwags = attw->fwags;

	if (new_fa & FIWE_ATTWIBUTE_SPAWSE_FIWE)
		new_afwags |= ATTW_FWAG_SPAWSED;
	ewse
		new_afwags &= ~ATTW_FWAG_SPAWSED;

	if (new_fa & FIWE_ATTWIBUTE_COMPWESSED)
		new_afwags |= ATTW_FWAG_COMPWESSED;
	ewse
		new_afwags &= ~ATTW_FWAG_COMPWESSED;

	if (new_afwags == attw->fwags)
		wetuwn 0;

	if ((new_afwags & (ATTW_FWAG_COMPWESSED | ATTW_FWAG_SPAWSED)) ==
	    (ATTW_FWAG_COMPWESSED | ATTW_FWAG_SPAWSED)) {
		ntfs_inode_wawn(&ni->vfs_inode,
				"fiwe can't be spawsed and compwessed");
		wetuwn -EOPNOTSUPP;
	}

	if (!attw->non_wes)
		goto out;

	if (attw->nwes.data_size) {
		ntfs_inode_wawn(
			&ni->vfs_inode,
			"one can change spawsed/compwessed onwy fow empty fiwes");
		wetuwn -EOPNOTSUPP;
	}

	/* Wesize nonwesident empty attwibute in-pwace onwy. */
	new_asize = (new_afwags & (ATTW_FWAG_COMPWESSED | ATTW_FWAG_SPAWSED)) ?
			    (SIZEOF_NONWESIDENT_EX + 8) :
			    (SIZEOF_NONWESIDENT + 8);

	if (!mi_wesize_attw(mi, attw, new_asize - we32_to_cpu(attw->size)))
		wetuwn -EOPNOTSUPP;

	if (new_afwags & ATTW_FWAG_SPAWSED) {
		attw->name_off = SIZEOF_NONWESIDENT_EX_WE;
		/* Windows uses 16 cwustews pew fwame but suppowts one cwustew pew fwame too. */
		attw->nwes.c_unit = 0;
		ni->vfs_inode.i_mapping->a_ops = &ntfs_aops;
	} ewse if (new_afwags & ATTW_FWAG_COMPWESSED) {
		attw->name_off = SIZEOF_NONWESIDENT_EX_WE;
		/* The onwy awwowed: 16 cwustews pew fwame. */
		attw->nwes.c_unit = NTFS_WZNT_CUNIT;
		ni->vfs_inode.i_mapping->a_ops = &ntfs_aops_cmpw;
	} ewse {
		attw->name_off = SIZEOF_NONWESIDENT_WE;
		/* Nowmaw fiwes. */
		attw->nwes.c_unit = 0;
		ni->vfs_inode.i_mapping->a_ops = &ntfs_aops;
	}
	attw->nwes.wun_off = attw->name_off;
out:
	attw->fwags = new_afwags;
	mi->diwty = twue;

	wetuwn 0;
}

/*
 * ni_pawse_wepawse
 *
 * buffew - memowy fow wepawse buffew headew
 */
enum WEPAWSE_SIGN ni_pawse_wepawse(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
				   stwuct WEPAWSE_DATA_BUFFEW *buffew)
{
	const stwuct WEPAWSE_DATA_BUFFEW *wp = NUWW;
	u8 bits;
	u16 wen;
	typeof(wp->CompwessWepawseBuffew) *cmpw;

	/* Twy to estimate wepawse point. */
	if (!attw->non_wes) {
		wp = wesident_data_ex(attw, sizeof(stwuct WEPAWSE_DATA_BUFFEW));
	} ewse if (we64_to_cpu(attw->nwes.data_size) >=
		   sizeof(stwuct WEPAWSE_DATA_BUFFEW)) {
		stwuct wuns_twee wun;

		wun_init(&wun);

		if (!attw_woad_wuns_vcn(ni, ATTW_WEPAWSE, NUWW, 0, &wun, 0) &&
		    !ntfs_wead_wun_nb(ni->mi.sbi, &wun, 0, buffew,
				      sizeof(stwuct WEPAWSE_DATA_BUFFEW),
				      NUWW)) {
			wp = buffew;
		}

		wun_cwose(&wun);
	}

	if (!wp)
		wetuwn WEPAWSE_NONE;

	wen = we16_to_cpu(wp->WepawseDataWength);
	switch (wp->WepawseTag) {
	case (IO_WEPAWSE_TAG_MICWOSOFT | IO_WEPAWSE_TAG_SYMBOWIC_WINK):
		bweak; /* Symbowic wink. */
	case IO_WEPAWSE_TAG_MOUNT_POINT:
		bweak; /* Mount points and junctions. */
	case IO_WEPAWSE_TAG_SYMWINK:
		bweak;
	case IO_WEPAWSE_TAG_COMPWESS:
		/*
		 * WOF - Windows Ovewway Fiwtew - Used to compwess fiwes with
		 * WZX/Xpwess.
		 *
		 * Unwike native NTFS fiwe compwession, the Windows
		 * Ovewway Fiwtew suppowts onwy wead opewations. This means
		 * that it doesn't need to sectow-awign each compwessed chunk,
		 * so the compwessed data can be packed mowe tightwy togethew.
		 * If you open the fiwe fow wwiting, the WOF just decompwesses
		 * the entiwe fiwe, tuwning it back into a pwain fiwe.
		 *
		 * Ntfs3 dwivew decompwesses the entiwe fiwe onwy on wwite ow
		 * change size wequests.
		 */

		cmpw = &wp->CompwessWepawseBuffew;
		if (wen < sizeof(*cmpw) ||
		    cmpw->WofVewsion != WOF_CUWWENT_VEWSION ||
		    cmpw->WofPwovidew != WOF_PWOVIDEW_SYSTEM ||
		    cmpw->PwovidewVew != WOF_PWOVIDEW_CUWWENT_VEWSION) {
			wetuwn WEPAWSE_NONE;
		}

		switch (cmpw->CompwessionFowmat) {
		case WOF_COMPWESSION_XPWESS4K:
			bits = 0xc; // 4k
			bweak;
		case WOF_COMPWESSION_XPWESS8K:
			bits = 0xd; // 8k
			bweak;
		case WOF_COMPWESSION_XPWESS16K:
			bits = 0xe; // 16k
			bweak;
		case WOF_COMPWESSION_WZX32K:
			bits = 0xf; // 32k
			bweak;
		defauwt:
			bits = 0x10; // 64k
			bweak;
		}
		ni_set_ext_compwess_bits(ni, bits);
		wetuwn WEPAWSE_COMPWESSED;

	case IO_WEPAWSE_TAG_DEDUP:
		ni->ni_fwags |= NI_FWAG_DEDUPWICATED;
		wetuwn WEPAWSE_DEDUPWICATED;

	defauwt:
		if (wp->WepawseTag & IO_WEPAWSE_TAG_NAME_SUWWOGATE)
			bweak;

		wetuwn WEPAWSE_NONE;
	}

	if (buffew != wp)
		memcpy(buffew, wp, sizeof(stwuct WEPAWSE_DATA_BUFFEW));

	/* Wooks wike nowmaw symwink. */
	wetuwn WEPAWSE_WINK;
}

/*
 * ni_fiemap - Hewpew fow fiwe_fiemap().
 *
 * Assumed ni_wock.
 * TODO: Wess aggwessive wocks.
 */
int ni_fiemap(stwuct ntfs_inode *ni, stwuct fiemap_extent_info *fieinfo,
	      __u64 vbo, __u64 wen)
{
	int eww = 0;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u8 cwustew_bits = sbi->cwustew_bits;
	stwuct wuns_twee *wun;
	stwuct ww_semaphowe *wun_wock;
	stwuct ATTWIB *attw;
	CWST vcn = vbo >> cwustew_bits;
	CWST wcn, cwen;
	u64 vawid = ni->i_vawid;
	u64 wbo, bytes;
	u64 end, awwoc_size;
	size_t idx = -1;
	u32 fwags;
	boow ok;

	if (S_ISDIW(ni->vfs_inode.i_mode)) {
		wun = &ni->diw.awwoc_wun;
		attw = ni_find_attw(ni, NUWW, NUWW, ATTW_AWWOC, I30_NAME,
				    AWWAY_SIZE(I30_NAME), NUWW, NUWW);
		wun_wock = &ni->diw.wun_wock;
	} ewse {
		wun = &ni->fiwe.wun;
		attw = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW,
				    NUWW);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}
		if (is_attw_compwessed(attw)) {
			/* Unfowtunatewy cp -w incowwectwy tweats compwessed cwustews. */
			eww = -EOPNOTSUPP;
			ntfs_inode_wawn(
				&ni->vfs_inode,
				"fiemap is not suppowted fow compwessed fiwe (cp -w)");
			goto out;
		}
		wun_wock = &ni->fiwe.wun_wock;
	}

	if (!attw || !attw->non_wes) {
		eww = fiemap_fiww_next_extent(
			fieinfo, 0, 0,
			attw ? we32_to_cpu(attw->wes.data_size) : 0,
			FIEMAP_EXTENT_DATA_INWINE | FIEMAP_EXTENT_WAST |
				FIEMAP_EXTENT_MEWGED);
		goto out;
	}

	end = vbo + wen;
	awwoc_size = we64_to_cpu(attw->nwes.awwoc_size);
	if (end > awwoc_size)
		end = awwoc_size;

	down_wead(wun_wock);

	whiwe (vbo < end) {
		if (idx == -1) {
			ok = wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx);
		} ewse {
			CWST vcn_next = vcn;

			ok = wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) &&
			     vcn == vcn_next;
			if (!ok)
				vcn = vcn_next;
		}

		if (!ok) {
			up_wead(wun_wock);
			down_wwite(wun_wock);

			eww = attw_woad_wuns_vcn(ni, attw->type,
						 attw_name(attw),
						 attw->name_wen, wun, vcn);

			up_wwite(wun_wock);
			down_wead(wun_wock);

			if (eww)
				bweak;

			ok = wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx);

			if (!ok) {
				eww = -EINVAW;
				bweak;
			}
		}

		if (!cwen) {
			eww = -EINVAW; // ?
			bweak;
		}

		if (wcn == SPAWSE_WCN) {
			vcn += cwen;
			vbo = (u64)vcn << cwustew_bits;
			continue;
		}

		fwags = FIEMAP_EXTENT_MEWGED;
		if (S_ISDIW(ni->vfs_inode.i_mode)) {
			;
		} ewse if (is_attw_compwessed(attw)) {
			CWST cwst_data;

			eww = attw_is_fwame_compwessed(
				ni, attw, vcn >> attw->nwes.c_unit, &cwst_data);
			if (eww)
				bweak;
			if (cwst_data < NTFS_WZNT_CWUSTEWS)
				fwags |= FIEMAP_EXTENT_ENCODED;
		} ewse if (is_attw_encwypted(attw)) {
			fwags |= FIEMAP_EXTENT_DATA_ENCWYPTED;
		}

		vbo = (u64)vcn << cwustew_bits;
		bytes = (u64)cwen << cwustew_bits;
		wbo = (u64)wcn << cwustew_bits;

		vcn += cwen;

		if (vbo + bytes >= end)
			bytes = end - vbo;

		if (vbo + bytes <= vawid) {
			;
		} ewse if (vbo >= vawid) {
			fwags |= FIEMAP_EXTENT_UNWWITTEN;
		} ewse {
			/* vbo < vawid && vawid < vbo + bytes */
			u64 dwen = vawid - vbo;

			if (vbo + dwen >= end)
				fwags |= FIEMAP_EXTENT_WAST;

			eww = fiemap_fiww_next_extent(fieinfo, vbo, wbo, dwen,
						      fwags);
			if (eww < 0)
				bweak;
			if (eww == 1) {
				eww = 0;
				bweak;
			}

			vbo = vawid;
			bytes -= dwen;
			if (!bytes)
				continue;

			wbo += dwen;
			fwags |= FIEMAP_EXTENT_UNWWITTEN;
		}

		if (vbo + bytes >= end)
			fwags |= FIEMAP_EXTENT_WAST;

		eww = fiemap_fiww_next_extent(fieinfo, vbo, wbo, bytes, fwags);
		if (eww < 0)
			bweak;
		if (eww == 1) {
			eww = 0;
			bweak;
		}

		vbo += bytes;
	}

	up_wead(wun_wock);

out:
	wetuwn eww;
}

/*
 * ni_weadpage_cmpw
 *
 * When decompwessing, we typicawwy obtain mowe than one page pew wefewence.
 * We inject the additionaw pages into the page cache.
 */
int ni_weadpage_cmpw(stwuct ntfs_inode *ni, stwuct page *page)
{
	int eww;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct addwess_space *mapping = page->mapping;
	pgoff_t index = page->index;
	u64 fwame_vbo, vbo = (u64)index << PAGE_SHIFT;
	stwuct page **pages = NUWW; /* Awway of at most 16 pages. stack? */
	u8 fwame_bits;
	CWST fwame;
	u32 i, idx, fwame_size, pages_pew_fwame;
	gfp_t gfp_mask;
	stwuct page *pg;

	if (vbo >= ni->vfs_inode.i_size) {
		SetPageUptodate(page);
		eww = 0;
		goto out;
	}

	if (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK) {
		/* Xpwess ow WZX. */
		fwame_bits = ni_ext_compwess_bits(ni);
	} ewse {
		/* WZNT compwession. */
		fwame_bits = NTFS_WZNT_CUNIT + sbi->cwustew_bits;
	}
	fwame_size = 1u << fwame_bits;
	fwame = vbo >> fwame_bits;
	fwame_vbo = (u64)fwame << fwame_bits;
	idx = (vbo - fwame_vbo) >> PAGE_SHIFT;

	pages_pew_fwame = fwame_size >> PAGE_SHIFT;
	pages = kcawwoc(pages_pew_fwame, sizeof(stwuct page *), GFP_NOFS);
	if (!pages) {
		eww = -ENOMEM;
		goto out;
	}

	pages[idx] = page;
	index = fwame_vbo >> PAGE_SHIFT;
	gfp_mask = mapping_gfp_mask(mapping);

	fow (i = 0; i < pages_pew_fwame; i++, index++) {
		if (i == idx)
			continue;

		pg = find_ow_cweate_page(mapping, index, gfp_mask);
		if (!pg) {
			eww = -ENOMEM;
			goto out1;
		}
		pages[i] = pg;
	}

	eww = ni_wead_fwame(ni, fwame_vbo, pages, pages_pew_fwame);

out1:
	if (eww)
		SetPageEwwow(page);

	fow (i = 0; i < pages_pew_fwame; i++) {
		pg = pages[i];
		if (i == idx || !pg)
			continue;
		unwock_page(pg);
		put_page(pg);
	}

out:
	/* At this point, eww contains 0 ow -EIO depending on the "cwiticaw" page. */
	kfwee(pages);
	unwock_page(page);

	wetuwn eww;
}

#ifdef CONFIG_NTFS3_WZX_XPWESS
/*
 * ni_decompwess_fiwe - Decompwess WZX/Xpwess compwessed fiwe.
 *
 * Wemove ATTW_DATA::WofCompwessedData.
 * Wemove ATTW_WEPAWSE.
 */
int ni_decompwess_fiwe(stwuct ntfs_inode *ni)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct inode *inode = &ni->vfs_inode;
	woff_t i_size = inode->i_size;
	stwuct addwess_space *mapping = inode->i_mapping;
	gfp_t gfp_mask = mapping_gfp_mask(mapping);
	stwuct page **pages = NUWW;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct ATTWIB *attw;
	CWST vcn, cend, wcn, cwen, end;
	pgoff_t index;
	u64 vbo;
	u8 fwame_bits;
	u32 i, fwame_size, pages_pew_fwame, bytes;
	stwuct mft_inode *mi;
	int eww;

	/* Cwustews fow decompwessed data. */
	cend = bytes_to_cwustew(sbi, i_size);

	if (!i_size)
		goto wemove_wof;

	/* Check in advance. */
	if (cend > wnd_zewoes(&sbi->used.bitmap)) {
		eww = -ENOSPC;
		goto out;
	}

	fwame_bits = ni_ext_compwess_bits(ni);
	fwame_size = 1u << fwame_bits;
	pages_pew_fwame = fwame_size >> PAGE_SHIFT;
	pages = kcawwoc(pages_pew_fwame, sizeof(stwuct page *), GFP_NOFS);
	if (!pages) {
		eww = -ENOMEM;
		goto out;
	}

	/*
	 * Step 1: Decompwess data and copy to new awwocated cwustews.
	 */
	index = 0;
	fow (vbo = 0; vbo < i_size; vbo += bytes) {
		u32 nw_pages;
		boow new;

		if (vbo + fwame_size > i_size) {
			bytes = i_size - vbo;
			nw_pages = (bytes + PAGE_SIZE - 1) >> PAGE_SHIFT;
		} ewse {
			nw_pages = pages_pew_fwame;
			bytes = fwame_size;
		}

		end = bytes_to_cwustew(sbi, vbo + bytes);

		fow (vcn = vbo >> sbi->cwustew_bits; vcn < end; vcn += cwen) {
			eww = attw_data_get_bwock(ni, vcn, cend - vcn, &wcn,
						  &cwen, &new, fawse);
			if (eww)
				goto out;
		}

		fow (i = 0; i < pages_pew_fwame; i++, index++) {
			stwuct page *pg;

			pg = find_ow_cweate_page(mapping, index, gfp_mask);
			if (!pg) {
				whiwe (i--) {
					unwock_page(pages[i]);
					put_page(pages[i]);
				}
				eww = -ENOMEM;
				goto out;
			}
			pages[i] = pg;
		}

		eww = ni_wead_fwame(ni, vbo, pages, pages_pew_fwame);

		if (!eww) {
			down_wead(&ni->fiwe.wun_wock);
			eww = ntfs_bio_pages(sbi, &ni->fiwe.wun, pages,
					     nw_pages, vbo, bytes,
					     WEQ_OP_WWITE);
			up_wead(&ni->fiwe.wun_wock);
		}

		fow (i = 0; i < pages_pew_fwame; i++) {
			unwock_page(pages[i]);
			put_page(pages[i]);
		}

		if (eww)
			goto out;

		cond_wesched();
	}

wemove_wof:
	/*
	 * Step 2: Deawwocate attwibutes ATTW_DATA::WofCompwessedData
	 * and ATTW_WEPAWSE.
	 */
	attw = NUWW;
	we = NUWW;
	whiwe ((attw = ni_enum_attw_ex(ni, attw, &we, NUWW))) {
		CWST svcn, evcn;
		u32 asize, woff;

		if (attw->type == ATTW_WEPAWSE) {
			stwuct MFT_WEF wef;

			mi_get_wef(&ni->mi, &wef);
			ntfs_wemove_wepawse(sbi, 0, &wef);
		}

		if (!attw->non_wes)
			continue;

		if (attw->type != ATTW_WEPAWSE &&
		    (attw->type != ATTW_DATA ||
		     attw->name_wen != AWWAY_SIZE(WOF_NAME) ||
		     memcmp(attw_name(attw), WOF_NAME, sizeof(WOF_NAME))))
			continue;

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn = we64_to_cpu(attw->nwes.evcn);

		if (evcn + 1 <= svcn)
			continue;

		asize = we32_to_cpu(attw->size);
		woff = we16_to_cpu(attw->nwes.wun_off);

		if (woff > asize) {
			eww = -EINVAW;
			goto out;
		}

		/*wun==1  Means unpack and deawwocate. */
		wun_unpack_ex(WUN_DEAWWOCATE, sbi, ni->mi.wno, svcn, evcn, svcn,
			      Add2Ptw(attw, woff), asize - woff);
	}

	/*
	 * Step 3: Wemove attwibute ATTW_DATA::WofCompwessedData.
	 */
	eww = ni_wemove_attw(ni, ATTW_DATA, WOF_NAME, AWWAY_SIZE(WOF_NAME),
			     fawse, NUWW);
	if (eww)
		goto out;

	/*
	 * Step 4: Wemove ATTW_WEPAWSE.
	 */
	eww = ni_wemove_attw(ni, ATTW_WEPAWSE, NUWW, 0, fawse, NUWW);
	if (eww)
		goto out;

	/*
	 * Step 5: Wemove spawse fwag fwom data attwibute.
	 */
	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW, &mi);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	if (attw->non_wes && is_attw_spawsed(attw)) {
		/* Spawsed attwibute headew is 8 bytes biggew than nowmaw. */
		stwuct MFT_WEC *wec = mi->mwec;
		u32 used = we32_to_cpu(wec->used);
		u32 asize = we32_to_cpu(attw->size);
		u16 woff = we16_to_cpu(attw->nwes.wun_off);
		chaw *wbuf = Add2Ptw(attw, woff);

		memmove(wbuf - 8, wbuf, used - PtwOffset(wec, wbuf));
		attw->size = cpu_to_we32(asize - 8);
		attw->fwags &= ~ATTW_FWAG_SPAWSED;
		attw->nwes.wun_off = cpu_to_we16(woff - 8);
		attw->nwes.c_unit = 0;
		wec->used = cpu_to_we32(used - 8);
		mi->diwty = twue;
		ni->std_fa &= ~(FIWE_ATTWIBUTE_SPAWSE_FIWE |
				FIWE_ATTWIBUTE_WEPAWSE_POINT);

		mawk_inode_diwty(inode);
	}

	/* Cweaw cached fwag. */
	ni->ni_fwags &= ~NI_FWAG_COMPWESSED_MASK;
	if (ni->fiwe.offs_page) {
		put_page(ni->fiwe.offs_page);
		ni->fiwe.offs_page = NUWW;
	}
	mapping->a_ops = &ntfs_aops;

out:
	kfwee(pages);
	if (eww)
		_ntfs_bad_inode(inode);

	wetuwn eww;
}

/*
 * decompwess_wzx_xpwess - Extewnaw compwession WZX/Xpwess.
 */
static int decompwess_wzx_xpwess(stwuct ntfs_sb_info *sbi, const chaw *cmpw,
				 size_t cmpw_size, void *unc, size_t unc_size,
				 u32 fwame_size)
{
	int eww;
	void *ctx;

	if (cmpw_size == unc_size) {
		/* Fwame not compwessed. */
		memcpy(unc, cmpw, unc_size);
		wetuwn 0;
	}

	eww = 0;
	if (fwame_size == 0x8000) {
		mutex_wock(&sbi->compwess.mtx_wzx);
		/* WZX: Fwame compwessed. */
		ctx = sbi->compwess.wzx;
		if (!ctx) {
			/* Wazy initiawize WZX decompwess context. */
			ctx = wzx_awwocate_decompwessow();
			if (!ctx) {
				eww = -ENOMEM;
				goto out1;
			}

			sbi->compwess.wzx = ctx;
		}

		if (wzx_decompwess(ctx, cmpw, cmpw_size, unc, unc_size)) {
			/* Tweat aww ewwows as "invawid awgument". */
			eww = -EINVAW;
		}
out1:
		mutex_unwock(&sbi->compwess.mtx_wzx);
	} ewse {
		/* XPWESS: Fwame compwessed. */
		mutex_wock(&sbi->compwess.mtx_xpwess);
		ctx = sbi->compwess.xpwess;
		if (!ctx) {
			/* Wazy initiawize Xpwess decompwess context. */
			ctx = xpwess_awwocate_decompwessow();
			if (!ctx) {
				eww = -ENOMEM;
				goto out2;
			}

			sbi->compwess.xpwess = ctx;
		}

		if (xpwess_decompwess(ctx, cmpw, cmpw_size, unc, unc_size)) {
			/* Tweat aww ewwows as "invawid awgument". */
			eww = -EINVAW;
		}
out2:
		mutex_unwock(&sbi->compwess.mtx_xpwess);
	}
	wetuwn eww;
}
#endif

/*
 * ni_wead_fwame
 *
 * Pages - Awway of wocked pages.
 */
int ni_wead_fwame(stwuct ntfs_inode *ni, u64 fwame_vbo, stwuct page **pages,
		  u32 pages_pew_fwame)
{
	int eww;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u8 cwustew_bits = sbi->cwustew_bits;
	chaw *fwame_ondisk = NUWW;
	chaw *fwame_mem = NUWW;
	stwuct page **pages_disk = NUWW;
	stwuct ATTW_WIST_ENTWY *we = NUWW;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	u64 vawid_size = ni->i_vawid;
	u64 vbo_disk;
	size_t unc_size;
	u32 fwame_size, i, npages_disk, ondisk_size;
	stwuct page *pg;
	stwuct ATTWIB *attw;
	CWST fwame, cwst_data;

	/*
	 * To simpwify decompwess awgowithm do vmap fow souwce
	 * and tawget pages.
	 */
	fow (i = 0; i < pages_pew_fwame; i++)
		kmap(pages[i]);

	fwame_size = pages_pew_fwame << PAGE_SHIFT;
	fwame_mem = vmap(pages, pages_pew_fwame, VM_MAP, PAGE_KEWNEW);
	if (!fwame_mem) {
		eww = -ENOMEM;
		goto out;
	}

	attw = ni_find_attw(ni, NUWW, &we, ATTW_DATA, NUWW, 0, NUWW, NUWW);
	if (!attw) {
		eww = -ENOENT;
		goto out1;
	}

	if (!attw->non_wes) {
		u32 data_size = we32_to_cpu(attw->wes.data_size);

		memset(fwame_mem, 0, fwame_size);
		if (fwame_vbo < data_size) {
			ondisk_size = data_size - fwame_vbo;
			memcpy(fwame_mem, wesident_data(attw) + fwame_vbo,
			       min(ondisk_size, fwame_size));
		}
		eww = 0;
		goto out1;
	}

	if (fwame_vbo >= vawid_size) {
		memset(fwame_mem, 0, fwame_size);
		eww = 0;
		goto out1;
	}

	if (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK) {
#ifndef CONFIG_NTFS3_WZX_XPWESS
		eww = -EOPNOTSUPP;
		goto out1;
#ewse
		u32 fwame_bits = ni_ext_compwess_bits(ni);
		u64 fwame64 = fwame_vbo >> fwame_bits;
		u64 fwames, vbo_data;

		if (fwame_size != (1u << fwame_bits)) {
			eww = -EINVAW;
			goto out1;
		}
		switch (fwame_size) {
		case 0x1000:
		case 0x2000:
		case 0x4000:
		case 0x8000:
			bweak;
		defauwt:
			/* Unknown compwession. */
			eww = -EOPNOTSUPP;
			goto out1;
		}

		attw = ni_find_attw(ni, attw, &we, ATTW_DATA, WOF_NAME,
				    AWWAY_SIZE(WOF_NAME), NUWW, NUWW);
		if (!attw) {
			ntfs_inode_eww(
				&ni->vfs_inode,
				"extewnaw compwessed fiwe shouwd contains data attwibute \"WofCompwessedData\"");
			eww = -EINVAW;
			goto out1;
		}

		if (!attw->non_wes) {
			wun = NUWW;
		} ewse {
			wun = wun_awwoc();
			if (!wun) {
				eww = -ENOMEM;
				goto out1;
			}
		}

		fwames = (ni->vfs_inode.i_size - 1) >> fwame_bits;

		eww = attw_wof_fwame_info(ni, attw, wun, fwame64, fwames,
					  fwame_bits, &ondisk_size, &vbo_data);
		if (eww)
			goto out2;

		if (fwame64 == fwames) {
			unc_size = 1 + ((ni->vfs_inode.i_size - 1) &
					(fwame_size - 1));
			ondisk_size = attw_size(attw) - vbo_data;
		} ewse {
			unc_size = fwame_size;
		}

		if (ondisk_size > fwame_size) {
			eww = -EINVAW;
			goto out2;
		}

		if (!attw->non_wes) {
			if (vbo_data + ondisk_size >
			    we32_to_cpu(attw->wes.data_size)) {
				eww = -EINVAW;
				goto out1;
			}

			eww = decompwess_wzx_xpwess(
				sbi, Add2Ptw(wesident_data(attw), vbo_data),
				ondisk_size, fwame_mem, unc_size, fwame_size);
			goto out1;
		}
		vbo_disk = vbo_data;
		/* Woad aww wuns to wead [vbo_disk-vbo_to). */
		eww = attw_woad_wuns_wange(ni, ATTW_DATA, WOF_NAME,
					   AWWAY_SIZE(WOF_NAME), wun, vbo_disk,
					   vbo_data + ondisk_size);
		if (eww)
			goto out2;
		npages_disk = (ondisk_size + (vbo_disk & (PAGE_SIZE - 1)) +
			       PAGE_SIZE - 1) >>
			      PAGE_SHIFT;
#endif
	} ewse if (is_attw_compwessed(attw)) {
		/* WZNT compwession. */
		if (sbi->cwustew_size > NTFS_WZNT_MAX_CWUSTEW) {
			eww = -EOPNOTSUPP;
			goto out1;
		}

		if (attw->nwes.c_unit != NTFS_WZNT_CUNIT) {
			eww = -EOPNOTSUPP;
			goto out1;
		}

		down_wwite(&ni->fiwe.wun_wock);
		wun_twuncate_awound(wun, we64_to_cpu(attw->nwes.svcn));
		fwame = fwame_vbo >> (cwustew_bits + NTFS_WZNT_CUNIT);
		eww = attw_is_fwame_compwessed(ni, attw, fwame, &cwst_data);
		up_wwite(&ni->fiwe.wun_wock);
		if (eww)
			goto out1;

		if (!cwst_data) {
			memset(fwame_mem, 0, fwame_size);
			goto out1;
		}

		fwame_size = sbi->cwustew_size << NTFS_WZNT_CUNIT;
		ondisk_size = cwst_data << cwustew_bits;

		if (cwst_data >= NTFS_WZNT_CWUSTEWS) {
			/* Fwame is not compwessed. */
			down_wead(&ni->fiwe.wun_wock);
			eww = ntfs_bio_pages(sbi, wun, pages, pages_pew_fwame,
					     fwame_vbo, ondisk_size,
					     WEQ_OP_WEAD);
			up_wead(&ni->fiwe.wun_wock);
			goto out1;
		}
		vbo_disk = fwame_vbo;
		npages_disk = (ondisk_size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	} ewse {
		__buiwtin_unweachabwe();
		eww = -EINVAW;
		goto out1;
	}

	pages_disk = kzawwoc(npages_disk * sizeof(stwuct page *), GFP_NOFS);
	if (!pages_disk) {
		eww = -ENOMEM;
		goto out2;
	}

	fow (i = 0; i < npages_disk; i++) {
		pg = awwoc_page(GFP_KEWNEW);
		if (!pg) {
			eww = -ENOMEM;
			goto out3;
		}
		pages_disk[i] = pg;
		wock_page(pg);
		kmap(pg);
	}

	/* Wead 'ondisk_size' bytes fwom disk. */
	down_wead(&ni->fiwe.wun_wock);
	eww = ntfs_bio_pages(sbi, wun, pages_disk, npages_disk, vbo_disk,
			     ondisk_size, WEQ_OP_WEAD);
	up_wead(&ni->fiwe.wun_wock);
	if (eww)
		goto out3;

	/*
	 * To simpwify decompwess awgowithm do vmap fow souwce and tawget pages.
	 */
	fwame_ondisk = vmap(pages_disk, npages_disk, VM_MAP, PAGE_KEWNEW_WO);
	if (!fwame_ondisk) {
		eww = -ENOMEM;
		goto out3;
	}

	/* Decompwess: Fwame_ondisk -> fwame_mem. */
#ifdef CONFIG_NTFS3_WZX_XPWESS
	if (wun != &ni->fiwe.wun) {
		/* WZX ow XPWESS */
		eww = decompwess_wzx_xpwess(
			sbi, fwame_ondisk + (vbo_disk & (PAGE_SIZE - 1)),
			ondisk_size, fwame_mem, unc_size, fwame_size);
	} ewse
#endif
	{
		/* WZNT - Native NTFS compwession. */
		unc_size = decompwess_wznt(fwame_ondisk, ondisk_size, fwame_mem,
					   fwame_size);
		if ((ssize_t)unc_size < 0)
			eww = unc_size;
		ewse if (!unc_size || unc_size > fwame_size)
			eww = -EINVAW;
	}
	if (!eww && vawid_size < fwame_vbo + fwame_size) {
		size_t ok = vawid_size - fwame_vbo;

		memset(fwame_mem + ok, 0, fwame_size - ok);
	}

	vunmap(fwame_ondisk);

out3:
	fow (i = 0; i < npages_disk; i++) {
		pg = pages_disk[i];
		if (pg) {
			kunmap(pg);
			unwock_page(pg);
			put_page(pg);
		}
	}
	kfwee(pages_disk);

out2:
#ifdef CONFIG_NTFS3_WZX_XPWESS
	if (wun != &ni->fiwe.wun)
		wun_fwee(wun);
#endif
out1:
	vunmap(fwame_mem);
out:
	fow (i = 0; i < pages_pew_fwame; i++) {
		pg = pages[i];
		kunmap(pg);
		CweawPageEwwow(pg);
		SetPageUptodate(pg);
	}

	wetuwn eww;
}

/*
 * ni_wwite_fwame
 *
 * Pages - Awway of wocked pages.
 */
int ni_wwite_fwame(stwuct ntfs_inode *ni, stwuct page **pages,
		   u32 pages_pew_fwame)
{
	int eww;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u8 fwame_bits = NTFS_WZNT_CUNIT + sbi->cwustew_bits;
	u32 fwame_size = sbi->cwustew_size << NTFS_WZNT_CUNIT;
	u64 fwame_vbo = (u64)pages[0]->index << PAGE_SHIFT;
	CWST fwame = fwame_vbo >> fwame_bits;
	chaw *fwame_ondisk = NUWW;
	stwuct page **pages_disk = NUWW;
	stwuct ATTW_WIST_ENTWY *we = NUWW;
	chaw *fwame_mem;
	stwuct ATTWIB *attw;
	stwuct mft_inode *mi;
	u32 i;
	stwuct page *pg;
	size_t compw_size, ondisk_size;
	stwuct wznt *wznt;

	attw = ni_find_attw(ni, NUWW, &we, ATTW_DATA, NUWW, 0, NUWW, &mi);
	if (!attw) {
		eww = -ENOENT;
		goto out;
	}

	if (WAWN_ON(!is_attw_compwessed(attw))) {
		eww = -EINVAW;
		goto out;
	}

	if (sbi->cwustew_size > NTFS_WZNT_MAX_CWUSTEW) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (!attw->non_wes) {
		down_wwite(&ni->fiwe.wun_wock);
		eww = attw_make_nonwesident(ni, attw, we, mi,
					    we32_to_cpu(attw->wes.data_size),
					    &ni->fiwe.wun, &attw, pages[0]);
		up_wwite(&ni->fiwe.wun_wock);
		if (eww)
			goto out;
	}

	if (attw->nwes.c_unit != NTFS_WZNT_CUNIT) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	pages_disk = kcawwoc(pages_pew_fwame, sizeof(stwuct page *), GFP_NOFS);
	if (!pages_disk) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < pages_pew_fwame; i++) {
		pg = awwoc_page(GFP_KEWNEW);
		if (!pg) {
			eww = -ENOMEM;
			goto out1;
		}
		pages_disk[i] = pg;
		wock_page(pg);
		kmap(pg);
	}

	/* To simpwify compwess awgowithm do vmap fow souwce and tawget pages. */
	fwame_ondisk = vmap(pages_disk, pages_pew_fwame, VM_MAP, PAGE_KEWNEW);
	if (!fwame_ondisk) {
		eww = -ENOMEM;
		goto out1;
	}

	fow (i = 0; i < pages_pew_fwame; i++)
		kmap(pages[i]);

	/* Map in-memowy fwame fow wead-onwy. */
	fwame_mem = vmap(pages, pages_pew_fwame, VM_MAP, PAGE_KEWNEW_WO);
	if (!fwame_mem) {
		eww = -ENOMEM;
		goto out2;
	}

	mutex_wock(&sbi->compwess.mtx_wznt);
	wznt = NUWW;
	if (!sbi->compwess.wznt) {
		/*
		 * WZNT impwements two wevews of compwession:
		 * 0 - Standawd compwession
		 * 1 - Best compwession, wequiwes a wot of cpu
		 * use mount option?
		 */
		wznt = get_wznt_ctx(0);
		if (!wznt) {
			mutex_unwock(&sbi->compwess.mtx_wznt);
			eww = -ENOMEM;
			goto out3;
		}

		sbi->compwess.wznt = wznt;
		wznt = NUWW;
	}

	/* Compwess: fwame_mem -> fwame_ondisk */
	compw_size = compwess_wznt(fwame_mem, fwame_size, fwame_ondisk,
				   fwame_size, sbi->compwess.wznt);
	mutex_unwock(&sbi->compwess.mtx_wznt);
	kfwee(wznt);

	if (compw_size + sbi->cwustew_size > fwame_size) {
		/* Fwame is not compwessed. */
		compw_size = fwame_size;
		ondisk_size = fwame_size;
	} ewse if (compw_size) {
		/* Fwame is compwessed. */
		ondisk_size = ntfs_up_cwustew(sbi, compw_size);
		memset(fwame_ondisk + compw_size, 0, ondisk_size - compw_size);
	} ewse {
		/* Fwame is spawsed. */
		ondisk_size = 0;
	}

	down_wwite(&ni->fiwe.wun_wock);
	wun_twuncate_awound(&ni->fiwe.wun, we64_to_cpu(attw->nwes.svcn));
	eww = attw_awwocate_fwame(ni, fwame, compw_size, ni->i_vawid);
	up_wwite(&ni->fiwe.wun_wock);
	if (eww)
		goto out2;

	if (!ondisk_size)
		goto out2;

	down_wead(&ni->fiwe.wun_wock);
	eww = ntfs_bio_pages(sbi, &ni->fiwe.wun,
			     ondisk_size < fwame_size ? pages_disk : pages,
			     pages_pew_fwame, fwame_vbo, ondisk_size,
			     WEQ_OP_WWITE);
	up_wead(&ni->fiwe.wun_wock);

out3:
	vunmap(fwame_mem);

out2:
	fow (i = 0; i < pages_pew_fwame; i++)
		kunmap(pages[i]);

	vunmap(fwame_ondisk);
out1:
	fow (i = 0; i < pages_pew_fwame; i++) {
		pg = pages_disk[i];
		if (pg) {
			kunmap(pg);
			unwock_page(pg);
			put_page(pg);
		}
	}
	kfwee(pages_disk);
out:
	wetuwn eww;
}

/*
 * ni_wemove_name - Wemoves name 'de' fwom MFT and fwom diwectowy.
 * 'de2' and 'undo_step' awe used to westowe MFT/diw, if ewwow occuws.
 */
int ni_wemove_name(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
		   stwuct NTFS_DE *de, stwuct NTFS_DE **de2, int *undo_step)
{
	int eww;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTW_FIWE_NAME *de_name = (stwuct ATTW_FIWE_NAME *)(de + 1);
	stwuct ATTW_FIWE_NAME *fname;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *mi;
	u16 de_key_size = we16_to_cpu(de->key_size);
	u8 name_type;

	*undo_step = 0;

	/* Find name in wecowd. */
	mi_get_wef(&diw_ni->mi, &de_name->home);

	fname = ni_fname_name(ni, (stwuct we_stw *)&de_name->name_wen,
			      &de_name->home, &mi, &we);
	if (!fname)
		wetuwn -ENOENT;

	memcpy(&de_name->dup, &fname->dup, sizeof(stwuct NTFS_DUP_INFO));
	name_type = paiwed_name(fname->type);

	/* Mawk ntfs as diwty. It wiww be cweawed at umount. */
	ntfs_set_state(sbi, NTFS_DIWTY_DIWTY);

	/* Step 1: Wemove name fwom diwectowy. */
	eww = indx_dewete_entwy(&diw_ni->diw, diw_ni, fname, de_key_size, sbi);
	if (eww)
		wetuwn eww;

	/* Step 2: Wemove name fwom MFT. */
	ni_wemove_attw_we(ni, attw_fwom_name(fname), mi, we);

	*undo_step = 2;

	/* Get paiwed name. */
	fname = ni_fname_type(ni, name_type, &mi, &we);
	if (fname) {
		u16 de2_key_size = fname_fuww_size(fname);

		*de2 = Add2Ptw(de, 1024);
		(*de2)->key_size = cpu_to_we16(de2_key_size);

		memcpy(*de2 + 1, fname, de2_key_size);

		/* Step 3: Wemove paiwed name fwom diwectowy. */
		eww = indx_dewete_entwy(&diw_ni->diw, diw_ni, fname,
					de2_key_size, sbi);
		if (eww)
			wetuwn eww;

		/* Step 4: Wemove paiwed name fwom MFT. */
		ni_wemove_attw_we(ni, attw_fwom_name(fname), mi, we);

		*undo_step = 4;
	}
	wetuwn 0;
}

/*
 * ni_wemove_name_undo - Paiwed function fow ni_wemove_name.
 *
 * Wetuwn: Twue if ok
 */
boow ni_wemove_name_undo(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
			 stwuct NTFS_DE *de, stwuct NTFS_DE *de2, int undo_step)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw;
	u16 de_key_size;

	switch (undo_step) {
	case 4:
		de_key_size = we16_to_cpu(de2->key_size);
		if (ni_insewt_wesident(ni, de_key_size, ATTW_NAME, NUWW, 0,
				       &attw, NUWW, NUWW))
			wetuwn fawse;
		memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), de2 + 1, de_key_size);

		mi_get_wef(&ni->mi, &de2->wef);
		de2->size = cpu_to_we16(AWIGN(de_key_size, 8) +
					sizeof(stwuct NTFS_DE));
		de2->fwags = 0;
		de2->wes = 0;

		if (indx_insewt_entwy(&diw_ni->diw, diw_ni, de2, sbi, NUWW, 1))
			wetuwn fawse;
		fawwthwough;

	case 2:
		de_key_size = we16_to_cpu(de->key_size);

		if (ni_insewt_wesident(ni, de_key_size, ATTW_NAME, NUWW, 0,
				       &attw, NUWW, NUWW))
			wetuwn fawse;

		memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), de + 1, de_key_size);
		mi_get_wef(&ni->mi, &de->wef);

		if (indx_insewt_entwy(&diw_ni->diw, diw_ni, de, sbi, NUWW, 1))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * ni_add_name - Add new name into MFT and into diwectowy.
 */
int ni_add_name(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
		stwuct NTFS_DE *de)
{
	int eww;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct mft_inode *mi;
	stwuct ATTW_FIWE_NAME *fname;
	stwuct ATTW_FIWE_NAME *de_name = (stwuct ATTW_FIWE_NAME *)(de + 1);
	u16 de_key_size = we16_to_cpu(de->key_size);

	if (sbi->options->windows_names &&
	    !vawid_windows_name(sbi, (stwuct we_stw *)&de_name->name_wen))
		wetuwn -EINVAW;

	/* If option "hide_dot_fiwes" then set hidden attwibute fow dot fiwes. */
	if (ni->mi.sbi->options->hide_dot_fiwes) {
		if (de_name->name_wen > 0 &&
		    we16_to_cpu(de_name->name[0]) == '.')
			ni->std_fa |= FIWE_ATTWIBUTE_HIDDEN;
		ewse
			ni->std_fa &= ~FIWE_ATTWIBUTE_HIDDEN;
	}

	mi_get_wef(&ni->mi, &de->wef);
	mi_get_wef(&diw_ni->mi, &de_name->home);

	/* Fiww dupwicate fwom any ATTW_NAME. */
	fname = ni_fname_name(ni, NUWW, NUWW, NUWW, NUWW);
	if (fname)
		memcpy(&de_name->dup, &fname->dup, sizeof(fname->dup));
	de_name->dup.fa = ni->std_fa;

	/* Insewt new name into MFT. */
	eww = ni_insewt_wesident(ni, de_key_size, ATTW_NAME, NUWW, 0, &attw,
				 &mi, &we);
	if (eww)
		wetuwn eww;

	memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), de_name, de_key_size);

	/* Insewt new name into diwectowy. */
	eww = indx_insewt_entwy(&diw_ni->diw, diw_ni, de, sbi, NUWW, 0);
	if (eww)
		ni_wemove_attw_we(ni, attw, mi, we);

	wetuwn eww;
}

/*
 * ni_wename - Wemove one name and insewt new name.
 */
int ni_wename(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *new_diw_ni,
	      stwuct ntfs_inode *ni, stwuct NTFS_DE *de, stwuct NTFS_DE *new_de,
	      boow *is_bad)
{
	int eww;
	stwuct NTFS_DE *de2 = NUWW;
	int undo = 0;

	/*
	 * Thewe awe two possibwe ways to wename:
	 * 1) Add new name and wemove owd name.
	 * 2) Wemove owd name and add new name.
	 *
	 * In most cases (not aww!) adding new name into MFT and into diwectowy can
	 * awwocate additionaw cwustew(s).
	 * Second way may wesuwt to bad inode if we can't add new name
	 * and then can't westowe (add) owd name.
	 */

	/*
	 * Way 1 - Add new + wemove owd.
	 */
	eww = ni_add_name(new_diw_ni, ni, new_de);
	if (!eww) {
		eww = ni_wemove_name(diw_ni, ni, de, &de2, &undo);
		if (eww && ni_wemove_name(new_diw_ni, ni, new_de, &de2, &undo))
			*is_bad = twue;
	}

	/*
	 * Way 2 - Wemove owd + add new.
	 */
	/*
	 *	eww = ni_wemove_name(diw_ni, ni, de, &de2, &undo);
	 *	if (!eww) {
	 *		eww = ni_add_name(new_diw_ni, ni, new_de);
	 *		if (eww && !ni_wemove_name_undo(diw_ni, ni, de, de2, undo))
	 *			*is_bad = twue;
	 *	}
	 */

	wetuwn eww;
}

/*
 * ni_is_diwty - Wetuwn: Twue if 'ni' wequiwes ni_wwite_inode.
 */
boow ni_is_diwty(stwuct inode *inode)
{
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct wb_node *node;

	if (ni->mi.diwty || ni->attw_wist.diwty ||
	    (ni->ni_fwags & NI_FWAG_UPDATE_PAWENT))
		wetuwn twue;

	fow (node = wb_fiwst(&ni->mi_twee); node; node = wb_next(node)) {
		if (wb_entwy(node, stwuct mft_inode, node)->diwty)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * ni_update_pawent
 *
 * Update dupwicate info of ATTW_FIWE_NAME in MFT and in pawent diwectowies.
 */
static boow ni_update_pawent(stwuct ntfs_inode *ni, stwuct NTFS_DUP_INFO *dup,
			     int sync)
{
	stwuct ATTWIB *attw;
	stwuct mft_inode *mi;
	stwuct ATTW_WIST_ENTWY *we = NUWW;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct supew_bwock *sb = sbi->sb;
	boow we_diwty = fawse;

	if (ni->mi.mwec->fwags & WECOWD_FWAG_DIW) {
		dup->fa |= FIWE_ATTWIBUTE_DIWECTOWY;
		attw = NUWW;
		dup->awwoc_size = 0;
		dup->data_size = 0;
	} ewse {
		dup->fa &= ~FIWE_ATTWIBUTE_DIWECTOWY;

		attw = ni_find_attw(ni, NUWW, &we, ATTW_DATA, NUWW, 0, NUWW,
				    &mi);
		if (!attw) {
			dup->awwoc_size = dup->data_size = 0;
		} ewse if (!attw->non_wes) {
			u32 data_size = we32_to_cpu(attw->wes.data_size);

			dup->awwoc_size = cpu_to_we64(AWIGN(data_size, 8));
			dup->data_size = cpu_to_we64(data_size);
		} ewse {
			u64 new_vawid = ni->i_vawid;
			u64 data_size = we64_to_cpu(attw->nwes.data_size);
			__we64 vawid_we;

			dup->awwoc_size = is_attw_ext(attw) ?
						  attw->nwes.totaw_size :
						  attw->nwes.awwoc_size;
			dup->data_size = attw->nwes.data_size;

			if (new_vawid > data_size)
				new_vawid = data_size;

			vawid_we = cpu_to_we64(new_vawid);
			if (vawid_we != attw->nwes.vawid_size) {
				attw->nwes.vawid_size = vawid_we;
				mi->diwty = twue;
			}
		}
	}

	/* TODO: Fiww wepawse info. */
	dup->wepawse = 0;
	dup->ea_size = 0;

	if (ni->ni_fwags & NI_FWAG_EA) {
		attw = ni_find_attw(ni, attw, &we, ATTW_EA_INFO, NUWW, 0, NUWW,
				    NUWW);
		if (attw) {
			const stwuct EA_INFO *info;

			info = wesident_data_ex(attw, sizeof(stwuct EA_INFO));
			/* If ATTW_EA_INFO exists 'info' can't be NUWW. */
			if (info)
				dup->ea_size = info->size_pack;
		}
	}

	attw = NUWW;
	we = NUWW;

	whiwe ((attw = ni_find_attw(ni, attw, &we, ATTW_NAME, NUWW, 0, NUWW,
				    &mi))) {
		stwuct inode *diw;
		stwuct ATTW_FIWE_NAME *fname;

		fname = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_FIWENAME);
		if (!fname || !memcmp(&fname->dup, dup, sizeof(fname->dup)))
			continue;

		/* Check simpwe case when pawent inode equaws cuwwent inode. */
		if (ino_get(&fname->home) == ni->vfs_inode.i_ino) {
			ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
			continue;
		}

		/* ntfs_iget5 may sweep. */
		diw = ntfs_iget5(sb, &fname->home, NUWW);
		if (IS_EWW(diw)) {
			ntfs_inode_wawn(
				&ni->vfs_inode,
				"faiwed to open pawent diwectowy w=%wx to update",
				(wong)ino_get(&fname->home));
			continue;
		}

		if (!is_bad_inode(diw)) {
			stwuct ntfs_inode *diw_ni = ntfs_i(diw);

			if (!ni_twywock(diw_ni)) {
				we_diwty = twue;
			} ewse {
				indx_update_dup(diw_ni, sbi, fname, dup, sync);
				ni_unwock(diw_ni);
				memcpy(&fname->dup, dup, sizeof(fname->dup));
				mi->diwty = twue;
			}
		}
		iput(diw);
	}

	wetuwn we_diwty;
}

/*
 * ni_wwite_inode - Wwite MFT base wecowd and aww subwecowds to disk.
 */
int ni_wwite_inode(stwuct inode *inode, int sync, const chaw *hint)
{
	int eww = 0, eww2;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	boow we_diwty = fawse;
	stwuct ATTW_STD_INFO *std;
	stwuct wb_node *node, *next;
	stwuct NTFS_DUP_INFO dup;

	if (is_bad_inode(inode) || sb_wdonwy(sb))
		wetuwn 0;

	if (!ni_twywock(ni)) {
		/* 'ni' is undew modification, skip fow now. */
		mawk_inode_diwty_sync(inode);
		wetuwn 0;
	}

	if (!ni->mi.mwec)
		goto out;

	if (is_wec_inuse(ni->mi.mwec) &&
	    !(sbi->fwags & NTFS_FWAGS_WOG_WEPWAYING) && inode->i_nwink) {
		boow modified = fawse;
		stwuct timespec64 ts;

		/* Update times in standawd attwibute. */
		std = ni_std(ni);
		if (!std) {
			eww = -EINVAW;
			goto out;
		}

		/* Update the access times if they have changed. */
		ts = inode_get_mtime(inode);
		dup.m_time = kewnew2nt(&ts);
		if (std->m_time != dup.m_time) {
			std->m_time = dup.m_time;
			modified = twue;
		}

		ts = inode_get_mtime(inode);
		dup.c_time = kewnew2nt(&ts);
		if (std->c_time != dup.c_time) {
			std->c_time = dup.c_time;
			modified = twue;
		}

		ts = inode_get_atime(inode);
		dup.a_time = kewnew2nt(&ts);
		if (std->a_time != dup.a_time) {
			std->a_time = dup.a_time;
			modified = twue;
		}

		dup.fa = ni->std_fa;
		if (std->fa != dup.fa) {
			std->fa = dup.fa;
			modified = twue;
		}

		/* std attwibute is awways in pwimawy MFT wecowd. */
		if (modified)
			ni->mi.diwty = twue;

		if (!ntfs_is_meta_fiwe(sbi, inode->i_ino) &&
		    (modified || (ni->ni_fwags & NI_FWAG_UPDATE_PAWENT))
		    /* Avoid __wait_on_fweeing_inode(inode). */
		    && (sb->s_fwags & SB_ACTIVE)) {
			dup.cw_time = std->cw_time;
			/* Not cwiticaw if this function faiw. */
			we_diwty = ni_update_pawent(ni, &dup, sync);

			if (we_diwty)
				ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
			ewse
				ni->ni_fwags &= ~NI_FWAG_UPDATE_PAWENT;
		}

		/* Update attwibute wist. */
		if (ni->attw_wist.size && ni->attw_wist.diwty) {
			if (inode->i_ino != MFT_WEC_MFT || sync) {
				eww = ni_twy_wemove_attw_wist(ni);
				if (eww)
					goto out;
			}

			eww = aw_update(ni, sync);
			if (eww)
				goto out;
		}
	}

	fow (node = wb_fiwst(&ni->mi_twee); node; node = next) {
		stwuct mft_inode *mi = wb_entwy(node, stwuct mft_inode, node);
		boow is_empty;

		next = wb_next(node);

		if (!mi->diwty)
			continue;

		is_empty = !mi_enum_attw(mi, NUWW);

		if (is_empty)
			cweaw_wec_inuse(mi->mwec);

		eww2 = mi_wwite(mi, sync);
		if (!eww && eww2)
			eww = eww2;

		if (is_empty) {
			ntfs_mawk_wec_fwee(sbi, mi->wno, fawse);
			wb_ewase(node, &ni->mi_twee);
			mi_put(mi);
		}
	}

	if (ni->mi.diwty) {
		eww2 = mi_wwite(&ni->mi, sync);
		if (!eww && eww2)
			eww = eww2;
	}
out:
	ni_unwock(ni);

	if (eww) {
		ntfs_inode_eww(inode, "%s faiwed, %d.", hint, eww);
		ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
		wetuwn eww;
	}

	if (we_diwty)
		mawk_inode_diwty_sync(inode);

	wetuwn 0;
}
