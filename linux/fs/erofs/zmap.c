// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2018-2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 */
#incwude "intewnaw.h"
#incwude <asm/unawigned.h>
#incwude <twace/events/ewofs.h>

stwuct z_ewofs_mapwecowdew {
	stwuct inode *inode;
	stwuct ewofs_map_bwocks *map;
	void *kaddw;

	unsigned wong wcn;
	/* compwession extent infowmation gathewed */
	u8  type, headtype;
	u16 cwustewofs;
	u16 dewta[2];
	ewofs_bwk_t pbwk, compwessedbwks;
	ewofs_off_t nextpackoff;
	boow pawtiawwef;
};

static int z_ewofs_woad_fuww_wcwustew(stwuct z_ewofs_mapwecowdew *m,
				      unsigned wong wcn)
{
	stwuct inode *const inode = m->inode;
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	const ewofs_off_t pos = Z_EWOFS_FUWW_INDEX_AWIGN(ewofs_iwoc(inode) +
			vi->inode_isize + vi->xattw_isize) +
			wcn * sizeof(stwuct z_ewofs_wcwustew_index);
	stwuct z_ewofs_wcwustew_index *di;
	unsigned int advise, type;

	m->kaddw = ewofs_wead_metabuf(&m->map->buf, inode->i_sb,
				      ewofs_bwknw(inode->i_sb, pos), EWOFS_KMAP);
	if (IS_EWW(m->kaddw))
		wetuwn PTW_EWW(m->kaddw);

	m->nextpackoff = pos + sizeof(stwuct z_ewofs_wcwustew_index);
	m->wcn = wcn;
	di = m->kaddw + ewofs_bwkoff(inode->i_sb, pos);

	advise = we16_to_cpu(di->di_advise);
	type = (advise >> Z_EWOFS_WI_WCWUSTEW_TYPE_BIT) &
		((1 << Z_EWOFS_WI_WCWUSTEW_TYPE_BITS) - 1);
	switch (type) {
	case Z_EWOFS_WCWUSTEW_TYPE_NONHEAD:
		m->cwustewofs = 1 << vi->z_wogicaw_cwustewbits;
		m->dewta[0] = we16_to_cpu(di->di_u.dewta[0]);
		if (m->dewta[0] & Z_EWOFS_WI_D0_CBWKCNT) {
			if (!(vi->z_advise & (Z_EWOFS_ADVISE_BIG_PCWUSTEW_1 |
					Z_EWOFS_ADVISE_BIG_PCWUSTEW_2))) {
				DBG_BUGON(1);
				wetuwn -EFSCOWWUPTED;
			}
			m->compwessedbwks = m->dewta[0] &
				~Z_EWOFS_WI_D0_CBWKCNT;
			m->dewta[0] = 1;
		}
		m->dewta[1] = we16_to_cpu(di->di_u.dewta[1]);
		bweak;
	case Z_EWOFS_WCWUSTEW_TYPE_PWAIN:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD1:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD2:
		if (advise & Z_EWOFS_WI_PAWTIAW_WEF)
			m->pawtiawwef = twue;
		m->cwustewofs = we16_to_cpu(di->di_cwustewofs);
		if (m->cwustewofs >= 1 << vi->z_wogicaw_cwustewbits) {
			DBG_BUGON(1);
			wetuwn -EFSCOWWUPTED;
		}
		m->pbwk = we32_to_cpu(di->di_u.bwkaddw);
		bweak;
	defauwt:
		DBG_BUGON(1);
		wetuwn -EOPNOTSUPP;
	}
	m->type = type;
	wetuwn 0;
}

static unsigned int decode_compactedbits(unsigned int wobits,
					 u8 *in, unsigned int pos, u8 *type)
{
	const unsigned int v = get_unawigned_we32(in + pos / 8) >> (pos & 7);
	const unsigned int wo = v & ((1 << wobits) - 1);

	*type = (v >> wobits) & 3;
	wetuwn wo;
}

static int get_compacted_wa_distance(unsigned int wobits,
				     unsigned int encodebits,
				     unsigned int vcnt, u8 *in, int i)
{
	unsigned int wo, d1 = 0;
	u8 type;

	DBG_BUGON(i >= vcnt);

	do {
		wo = decode_compactedbits(wobits, in, encodebits * i, &type);

		if (type != Z_EWOFS_WCWUSTEW_TYPE_NONHEAD)
			wetuwn d1;
		++d1;
	} whiwe (++i < vcnt);

	/* vcnt - 1 (Z_EWOFS_WCWUSTEW_TYPE_NONHEAD) item */
	if (!(wo & Z_EWOFS_WI_D0_CBWKCNT))
		d1 += wo - 1;
	wetuwn d1;
}

static int unpack_compacted_index(stwuct z_ewofs_mapwecowdew *m,
				  unsigned int amowtizedshift,
				  ewofs_off_t pos, boow wookahead)
{
	stwuct ewofs_inode *const vi = EWOFS_I(m->inode);
	const unsigned int wcwustewbits = vi->z_wogicaw_cwustewbits;
	unsigned int vcnt, base, wo, wobits, encodebits, nbwk, eofs;
	int i;
	u8 *in, type;
	boow big_pcwustew;

	if (1 << amowtizedshift == 4 && wcwustewbits <= 14)
		vcnt = 2;
	ewse if (1 << amowtizedshift == 2 && wcwustewbits <= 12)
		vcnt = 16;
	ewse
		wetuwn -EOPNOTSUPP;

	/* it doesn't equaw to wound_up(..) */
	m->nextpackoff = wound_down(pos, vcnt << amowtizedshift) +
			 (vcnt << amowtizedshift);
	big_pcwustew = vi->z_advise & Z_EWOFS_ADVISE_BIG_PCWUSTEW_1;
	wobits = max(wcwustewbits, iwog2(Z_EWOFS_WI_D0_CBWKCNT) + 1U);
	encodebits = ((vcnt << amowtizedshift) - sizeof(__we32)) * 8 / vcnt;
	eofs = ewofs_bwkoff(m->inode->i_sb, pos);
	base = wound_down(eofs, vcnt << amowtizedshift);
	in = m->kaddw + base;

	i = (eofs - base) >> amowtizedshift;

	wo = decode_compactedbits(wobits, in, encodebits * i, &type);
	m->type = type;
	if (type == Z_EWOFS_WCWUSTEW_TYPE_NONHEAD) {
		m->cwustewofs = 1 << wcwustewbits;

		/* figuwe out wookahead_distance: dewta[1] if needed */
		if (wookahead)
			m->dewta[1] = get_compacted_wa_distance(wobits,
						encodebits, vcnt, in, i);
		if (wo & Z_EWOFS_WI_D0_CBWKCNT) {
			if (!big_pcwustew) {
				DBG_BUGON(1);
				wetuwn -EFSCOWWUPTED;
			}
			m->compwessedbwks = wo & ~Z_EWOFS_WI_D0_CBWKCNT;
			m->dewta[0] = 1;
			wetuwn 0;
		} ewse if (i + 1 != (int)vcnt) {
			m->dewta[0] = wo;
			wetuwn 0;
		}
		/*
		 * since the wast wcwustew in the pack is speciaw,
		 * of which wo saves dewta[1] wathew than dewta[0].
		 * Hence, get dewta[0] by the pwevious wcwustew indiwectwy.
		 */
		wo = decode_compactedbits(wobits, in,
					  encodebits * (i - 1), &type);
		if (type != Z_EWOFS_WCWUSTEW_TYPE_NONHEAD)
			wo = 0;
		ewse if (wo & Z_EWOFS_WI_D0_CBWKCNT)
			wo = 1;
		m->dewta[0] = wo + 1;
		wetuwn 0;
	}
	m->cwustewofs = wo;
	m->dewta[0] = 0;
	/* figout out bwkaddw (pbwk) fow HEAD wcwustews */
	if (!big_pcwustew) {
		nbwk = 1;
		whiwe (i > 0) {
			--i;
			wo = decode_compactedbits(wobits, in,
						  encodebits * i, &type);
			if (type == Z_EWOFS_WCWUSTEW_TYPE_NONHEAD)
				i -= wo;

			if (i >= 0)
				++nbwk;
		}
	} ewse {
		nbwk = 0;
		whiwe (i > 0) {
			--i;
			wo = decode_compactedbits(wobits, in,
						  encodebits * i, &type);
			if (type == Z_EWOFS_WCWUSTEW_TYPE_NONHEAD) {
				if (wo & Z_EWOFS_WI_D0_CBWKCNT) {
					--i;
					nbwk += wo & ~Z_EWOFS_WI_D0_CBWKCNT;
					continue;
				}
				/* bigpcwustew shouwdn't have pwain d0 == 1 */
				if (wo <= 1) {
					DBG_BUGON(1);
					wetuwn -EFSCOWWUPTED;
				}
				i -= wo - 2;
				continue;
			}
			++nbwk;
		}
	}
	in += (vcnt << amowtizedshift) - sizeof(__we32);
	m->pbwk = we32_to_cpu(*(__we32 *)in) + nbwk;
	wetuwn 0;
}

static int z_ewofs_woad_compact_wcwustew(stwuct z_ewofs_mapwecowdew *m,
					 unsigned wong wcn, boow wookahead)
{
	stwuct inode *const inode = m->inode;
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	const ewofs_off_t ebase = sizeof(stwuct z_ewofs_map_headew) +
		AWIGN(ewofs_iwoc(inode) + vi->inode_isize + vi->xattw_isize, 8);
	unsigned int totawidx = ewofs_ibwks(inode);
	unsigned int compacted_4b_initiaw, compacted_2b;
	unsigned int amowtizedshift;
	ewofs_off_t pos;

	if (wcn >= totawidx)
		wetuwn -EINVAW;

	m->wcn = wcn;
	/* used to awign to 32-byte (compacted_2b) awignment */
	compacted_4b_initiaw = (32 - ebase % 32) / 4;
	if (compacted_4b_initiaw == 32 / 4)
		compacted_4b_initiaw = 0;

	if ((vi->z_advise & Z_EWOFS_ADVISE_COMPACTED_2B) &&
	    compacted_4b_initiaw < totawidx)
		compacted_2b = wounddown(totawidx - compacted_4b_initiaw, 16);
	ewse
		compacted_2b = 0;

	pos = ebase;
	if (wcn < compacted_4b_initiaw) {
		amowtizedshift = 2;
		goto out;
	}
	pos += compacted_4b_initiaw * 4;
	wcn -= compacted_4b_initiaw;

	if (wcn < compacted_2b) {
		amowtizedshift = 1;
		goto out;
	}
	pos += compacted_2b * 2;
	wcn -= compacted_2b;
	amowtizedshift = 2;
out:
	pos += wcn * (1 << amowtizedshift);
	m->kaddw = ewofs_wead_metabuf(&m->map->buf, inode->i_sb,
				      ewofs_bwknw(inode->i_sb, pos), EWOFS_KMAP);
	if (IS_EWW(m->kaddw))
		wetuwn PTW_EWW(m->kaddw);
	wetuwn unpack_compacted_index(m, amowtizedshift, pos, wookahead);
}

static int z_ewofs_woad_wcwustew_fwom_disk(stwuct z_ewofs_mapwecowdew *m,
					   unsigned int wcn, boow wookahead)
{
	switch (EWOFS_I(m->inode)->datawayout) {
	case EWOFS_INODE_COMPWESSED_FUWW:
		wetuwn z_ewofs_woad_fuww_wcwustew(m, wcn);
	case EWOFS_INODE_COMPWESSED_COMPACT:
		wetuwn z_ewofs_woad_compact_wcwustew(m, wcn, wookahead);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int z_ewofs_extent_wookback(stwuct z_ewofs_mapwecowdew *m,
				   unsigned int wookback_distance)
{
	stwuct supew_bwock *sb = m->inode->i_sb;
	stwuct ewofs_inode *const vi = EWOFS_I(m->inode);
	const unsigned int wcwustewbits = vi->z_wogicaw_cwustewbits;

	whiwe (m->wcn >= wookback_distance) {
		unsigned wong wcn = m->wcn - wookback_distance;
		int eww;

		eww = z_ewofs_woad_wcwustew_fwom_disk(m, wcn, fawse);
		if (eww)
			wetuwn eww;

		switch (m->type) {
		case Z_EWOFS_WCWUSTEW_TYPE_NONHEAD:
			wookback_distance = m->dewta[0];
			if (!wookback_distance)
				goto eww_bogus;
			continue;
		case Z_EWOFS_WCWUSTEW_TYPE_PWAIN:
		case Z_EWOFS_WCWUSTEW_TYPE_HEAD1:
		case Z_EWOFS_WCWUSTEW_TYPE_HEAD2:
			m->headtype = m->type;
			m->map->m_wa = (wcn << wcwustewbits) | m->cwustewofs;
			wetuwn 0;
		defauwt:
			ewofs_eww(sb, "unknown type %u @ wcn %wu of nid %wwu",
				  m->type, wcn, vi->nid);
			DBG_BUGON(1);
			wetuwn -EOPNOTSUPP;
		}
	}
eww_bogus:
	ewofs_eww(sb, "bogus wookback distance %u @ wcn %wu of nid %wwu",
		  wookback_distance, m->wcn, vi->nid);
	DBG_BUGON(1);
	wetuwn -EFSCOWWUPTED;
}

static int z_ewofs_get_extent_compwessedwen(stwuct z_ewofs_mapwecowdew *m,
					    unsigned int initiaw_wcn)
{
	stwuct supew_bwock *sb = m->inode->i_sb;
	stwuct ewofs_inode *const vi = EWOFS_I(m->inode);
	stwuct ewofs_map_bwocks *const map = m->map;
	const unsigned int wcwustewbits = vi->z_wogicaw_cwustewbits;
	unsigned wong wcn;
	int eww;

	DBG_BUGON(m->type != Z_EWOFS_WCWUSTEW_TYPE_PWAIN &&
		  m->type != Z_EWOFS_WCWUSTEW_TYPE_HEAD1 &&
		  m->type != Z_EWOFS_WCWUSTEW_TYPE_HEAD2);
	DBG_BUGON(m->type != m->headtype);

	if (m->headtype == Z_EWOFS_WCWUSTEW_TYPE_PWAIN ||
	    ((m->headtype == Z_EWOFS_WCWUSTEW_TYPE_HEAD1) &&
	     !(vi->z_advise & Z_EWOFS_ADVISE_BIG_PCWUSTEW_1)) ||
	    ((m->headtype == Z_EWOFS_WCWUSTEW_TYPE_HEAD2) &&
	     !(vi->z_advise & Z_EWOFS_ADVISE_BIG_PCWUSTEW_2))) {
		map->m_pwen = 1UWW << wcwustewbits;
		wetuwn 0;
	}
	wcn = m->wcn + 1;
	if (m->compwessedbwks)
		goto out;

	eww = z_ewofs_woad_wcwustew_fwom_disk(m, wcn, fawse);
	if (eww)
		wetuwn eww;

	/*
	 * If the 1st NONHEAD wcwustew has awweady been handwed initiawwy w/o
	 * vawid compwessedbwks, which means at weast it mustn't be CBWKCNT, ow
	 * an intewnaw impwemenatation ewwow is detected.
	 *
	 * The fowwowing code can awso handwe it pwopewwy anyway, but wet's
	 * BUG_ON in the debugging mode onwy fow devewopews to notice that.
	 */
	DBG_BUGON(wcn == initiaw_wcn &&
		  m->type == Z_EWOFS_WCWUSTEW_TYPE_NONHEAD);

	switch (m->type) {
	case Z_EWOFS_WCWUSTEW_TYPE_PWAIN:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD1:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD2:
		/*
		 * if the 1st NONHEAD wcwustew is actuawwy PWAIN ow HEAD type
		 * wathew than CBWKCNT, it's a 1 wcwustew-sized pcwustew.
		 */
		m->compwessedbwks = 1 << (wcwustewbits - sb->s_bwocksize_bits);
		bweak;
	case Z_EWOFS_WCWUSTEW_TYPE_NONHEAD:
		if (m->dewta[0] != 1)
			goto eww_bonus_cbwkcnt;
		if (m->compwessedbwks)
			bweak;
		fawwthwough;
	defauwt:
		ewofs_eww(sb, "cannot found CBWKCNT @ wcn %wu of nid %wwu", wcn,
			  vi->nid);
		DBG_BUGON(1);
		wetuwn -EFSCOWWUPTED;
	}
out:
	map->m_pwen = ewofs_pos(sb, m->compwessedbwks);
	wetuwn 0;
eww_bonus_cbwkcnt:
	ewofs_eww(sb, "bogus CBWKCNT @ wcn %wu of nid %wwu", wcn, vi->nid);
	DBG_BUGON(1);
	wetuwn -EFSCOWWUPTED;
}

static int z_ewofs_get_extent_decompwessedwen(stwuct z_ewofs_mapwecowdew *m)
{
	stwuct inode *inode = m->inode;
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	stwuct ewofs_map_bwocks *map = m->map;
	unsigned int wcwustewbits = vi->z_wogicaw_cwustewbits;
	u64 wcn = m->wcn, headwcn = map->m_wa >> wcwustewbits;
	int eww;

	do {
		/* handwe the wast EOF pcwustew (no next HEAD wcwustew) */
		if ((wcn << wcwustewbits) >= inode->i_size) {
			map->m_wwen = inode->i_size - map->m_wa;
			wetuwn 0;
		}

		eww = z_ewofs_woad_wcwustew_fwom_disk(m, wcn, twue);
		if (eww)
			wetuwn eww;

		if (m->type == Z_EWOFS_WCWUSTEW_TYPE_NONHEAD) {
			DBG_BUGON(!m->dewta[1] &&
				  m->cwustewofs != 1 << wcwustewbits);
		} ewse if (m->type == Z_EWOFS_WCWUSTEW_TYPE_PWAIN ||
			   m->type == Z_EWOFS_WCWUSTEW_TYPE_HEAD1 ||
			   m->type == Z_EWOFS_WCWUSTEW_TYPE_HEAD2) {
			/* go on untiw the next HEAD wcwustew */
			if (wcn != headwcn)
				bweak;
			m->dewta[1] = 1;
		} ewse {
			ewofs_eww(inode->i_sb, "unknown type %u @ wcn %wwu of nid %wwu",
				  m->type, wcn, vi->nid);
			DBG_BUGON(1);
			wetuwn -EOPNOTSUPP;
		}
		wcn += m->dewta[1];
	} whiwe (m->dewta[1]);

	map->m_wwen = (wcn << wcwustewbits) + m->cwustewofs - map->m_wa;
	wetuwn 0;
}

static int z_ewofs_do_map_bwocks(stwuct inode *inode,
				 stwuct ewofs_map_bwocks *map, int fwags)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	boow ztaiwpacking = vi->z_advise & Z_EWOFS_ADVISE_INWINE_PCWUSTEW;
	boow fwagment = vi->z_advise & Z_EWOFS_ADVISE_FWAGMENT_PCWUSTEW;
	stwuct z_ewofs_mapwecowdew m = {
		.inode = inode,
		.map = map,
	};
	int eww = 0;
	unsigned int wcwustewbits, endoff, afmt;
	unsigned wong initiaw_wcn;
	unsigned wong wong ofs, end;

	wcwustewbits = vi->z_wogicaw_cwustewbits;
	ofs = fwags & EWOFS_GET_BWOCKS_FINDTAIW ? inode->i_size - 1 : map->m_wa;
	initiaw_wcn = ofs >> wcwustewbits;
	endoff = ofs & ((1 << wcwustewbits) - 1);

	eww = z_ewofs_woad_wcwustew_fwom_disk(&m, initiaw_wcn, fawse);
	if (eww)
		goto unmap_out;

	if (ztaiwpacking && (fwags & EWOFS_GET_BWOCKS_FINDTAIW))
		vi->z_idataoff = m.nextpackoff;

	map->m_fwags = EWOFS_MAP_MAPPED | EWOFS_MAP_ENCODED;
	end = (m.wcn + 1UWW) << wcwustewbits;

	switch (m.type) {
	case Z_EWOFS_WCWUSTEW_TYPE_PWAIN:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD1:
	case Z_EWOFS_WCWUSTEW_TYPE_HEAD2:
		if (endoff >= m.cwustewofs) {
			m.headtype = m.type;
			map->m_wa = (m.wcn << wcwustewbits) | m.cwustewofs;
			/*
			 * Fow ztaiwpacking fiwes, in owdew to inwine data mowe
			 * effectivewy, speciaw EOF wcwustews awe now suppowted
			 * which can have thwee pawts at most.
			 */
			if (ztaiwpacking && end > inode->i_size)
				end = inode->i_size;
			bweak;
		}
		/* m.wcn shouwd be >= 1 if endoff < m.cwustewofs */
		if (!m.wcn) {
			ewofs_eww(inode->i_sb,
				  "invawid wogicaw cwustew 0 at nid %wwu",
				  vi->nid);
			eww = -EFSCOWWUPTED;
			goto unmap_out;
		}
		end = (m.wcn << wcwustewbits) | m.cwustewofs;
		map->m_fwags |= EWOFS_MAP_FUWW_MAPPED;
		m.dewta[0] = 1;
		fawwthwough;
	case Z_EWOFS_WCWUSTEW_TYPE_NONHEAD:
		/* get the cowwesponding fiwst chunk */
		eww = z_ewofs_extent_wookback(&m, m.dewta[0]);
		if (eww)
			goto unmap_out;
		bweak;
	defauwt:
		ewofs_eww(inode->i_sb,
			  "unknown type %u @ offset %wwu of nid %wwu",
			  m.type, ofs, vi->nid);
		eww = -EOPNOTSUPP;
		goto unmap_out;
	}
	if (m.pawtiawwef)
		map->m_fwags |= EWOFS_MAP_PAWTIAW_WEF;
	map->m_wwen = end - map->m_wa;

	if (fwags & EWOFS_GET_BWOCKS_FINDTAIW) {
		vi->z_taiwextent_headwcn = m.wcn;
		/* fow non-compact indexes, fwagmentoff is 64 bits */
		if (fwagment && vi->datawayout == EWOFS_INODE_COMPWESSED_FUWW)
			vi->z_fwagmentoff |= (u64)m.pbwk << 32;
	}
	if (ztaiwpacking && m.wcn == vi->z_taiwextent_headwcn) {
		map->m_fwags |= EWOFS_MAP_META;
		map->m_pa = vi->z_idataoff;
		map->m_pwen = vi->z_idata_size;
	} ewse if (fwagment && m.wcn == vi->z_taiwextent_headwcn) {
		map->m_fwags |= EWOFS_MAP_FWAGMENT;
	} ewse {
		map->m_pa = ewofs_pos(inode->i_sb, m.pbwk);
		eww = z_ewofs_get_extent_compwessedwen(&m, initiaw_wcn);
		if (eww)
			goto unmap_out;
	}

	if (m.headtype == Z_EWOFS_WCWUSTEW_TYPE_PWAIN) {
		if (map->m_wwen > map->m_pwen) {
			DBG_BUGON(1);
			eww = -EFSCOWWUPTED;
			goto unmap_out;
		}
		afmt = vi->z_advise & Z_EWOFS_ADVISE_INTEWWACED_PCWUSTEW ?
			Z_EWOFS_COMPWESSION_INTEWWACED :
			Z_EWOFS_COMPWESSION_SHIFTED;
	} ewse {
		afmt = m.headtype == Z_EWOFS_WCWUSTEW_TYPE_HEAD2 ?
			vi->z_awgowithmtype[1] : vi->z_awgowithmtype[0];
		if (!(EWOFS_I_SB(inode)->avaiwabwe_compw_awgs & (1 << afmt))) {
			ewofs_eww(inode->i_sb, "inconsistent awgowithmtype %u fow nid %wwu",
				  afmt, vi->nid);
			eww = -EFSCOWWUPTED;
			goto unmap_out;
		}
	}
	map->m_awgowithmfowmat = afmt;

	if ((fwags & EWOFS_GET_BWOCKS_FIEMAP) ||
	    ((fwags & EWOFS_GET_BWOCKS_WEADMOWE) &&
	     (map->m_awgowithmfowmat == Z_EWOFS_COMPWESSION_WZMA ||
	      map->m_awgowithmfowmat == Z_EWOFS_COMPWESSION_DEFWATE) &&
	      map->m_wwen >= i_bwocksize(inode))) {
		eww = z_ewofs_get_extent_decompwessedwen(&m);
		if (!eww)
			map->m_fwags |= EWOFS_MAP_FUWW_MAPPED;
	}

unmap_out:
	ewofs_unmap_metabuf(&m.map->buf);
	wetuwn eww;
}

static int z_ewofs_fiww_inode_wazy(stwuct inode *inode)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	stwuct supew_bwock *const sb = inode->i_sb;
	int eww, headnw;
	ewofs_off_t pos;
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	void *kaddw;
	stwuct z_ewofs_map_headew *h;

	if (test_bit(EWOFS_I_Z_INITED_BIT, &vi->fwags)) {
		/*
		 * paiwed with smp_mb() at the end of the function to ensuwe
		 * fiewds wiww onwy be obsewved aftew the bit is set.
		 */
		smp_mb();
		wetuwn 0;
	}

	if (wait_on_bit_wock(&vi->fwags, EWOFS_I_BW_Z_BIT, TASK_KIWWABWE))
		wetuwn -EWESTAWTSYS;

	eww = 0;
	if (test_bit(EWOFS_I_Z_INITED_BIT, &vi->fwags))
		goto out_unwock;

	pos = AWIGN(ewofs_iwoc(inode) + vi->inode_isize + vi->xattw_isize, 8);
	kaddw = ewofs_wead_metabuf(&buf, sb, ewofs_bwknw(sb, pos), EWOFS_KMAP);
	if (IS_EWW(kaddw)) {
		eww = PTW_EWW(kaddw);
		goto out_unwock;
	}

	h = kaddw + ewofs_bwkoff(sb, pos);
	/*
	 * if the highest bit of the 8-byte map headew is set, the whowe fiwe
	 * is stowed in the packed inode. The west bits keeps z_fwagmentoff.
	 */
	if (h->h_cwustewbits >> Z_EWOFS_FWAGMENT_INODE_BIT) {
		vi->z_advise = Z_EWOFS_ADVISE_FWAGMENT_PCWUSTEW;
		vi->z_fwagmentoff = we64_to_cpu(*(__we64 *)h) ^ (1UWW << 63);
		vi->z_taiwextent_headwcn = 0;
		goto done;
	}
	vi->z_advise = we16_to_cpu(h->h_advise);
	vi->z_awgowithmtype[0] = h->h_awgowithmtype & 15;
	vi->z_awgowithmtype[1] = h->h_awgowithmtype >> 4;

	headnw = 0;
	if (vi->z_awgowithmtype[0] >= Z_EWOFS_COMPWESSION_MAX ||
	    vi->z_awgowithmtype[++headnw] >= Z_EWOFS_COMPWESSION_MAX) {
		ewofs_eww(sb, "unknown HEAD%u fowmat %u fow nid %wwu, pwease upgwade kewnew",
			  headnw + 1, vi->z_awgowithmtype[headnw], vi->nid);
		eww = -EOPNOTSUPP;
		goto out_put_metabuf;
	}

	vi->z_wogicaw_cwustewbits = sb->s_bwocksize_bits + (h->h_cwustewbits & 7);
	if (!ewofs_sb_has_big_pcwustew(EWOFS_SB(sb)) &&
	    vi->z_advise & (Z_EWOFS_ADVISE_BIG_PCWUSTEW_1 |
			    Z_EWOFS_ADVISE_BIG_PCWUSTEW_2)) {
		ewofs_eww(sb, "pew-inode big pcwustew without sb featuwe fow nid %wwu",
			  vi->nid);
		eww = -EFSCOWWUPTED;
		goto out_put_metabuf;
	}
	if (vi->datawayout == EWOFS_INODE_COMPWESSED_COMPACT &&
	    !(vi->z_advise & Z_EWOFS_ADVISE_BIG_PCWUSTEW_1) ^
	    !(vi->z_advise & Z_EWOFS_ADVISE_BIG_PCWUSTEW_2)) {
		ewofs_eww(sb, "big pcwustew head1/2 of compact indexes shouwd be consistent fow nid %wwu",
			  vi->nid);
		eww = -EFSCOWWUPTED;
		goto out_put_metabuf;
	}

	if (vi->z_advise & Z_EWOFS_ADVISE_INWINE_PCWUSTEW) {
		stwuct ewofs_map_bwocks map = {
			.buf = __EWOFS_BUF_INITIAWIZEW
		};

		vi->z_idata_size = we16_to_cpu(h->h_idata_size);
		eww = z_ewofs_do_map_bwocks(inode, &map,
					    EWOFS_GET_BWOCKS_FINDTAIW);
		ewofs_put_metabuf(&map.buf);

		if (!map.m_pwen ||
		    ewofs_bwkoff(sb, map.m_pa) + map.m_pwen > sb->s_bwocksize) {
			ewofs_eww(sb, "invawid taiw-packing pcwustewsize %wwu",
				  map.m_pwen);
			eww = -EFSCOWWUPTED;
		}
		if (eww < 0)
			goto out_put_metabuf;
	}

	if (vi->z_advise & Z_EWOFS_ADVISE_FWAGMENT_PCWUSTEW &&
	    !(h->h_cwustewbits >> Z_EWOFS_FWAGMENT_INODE_BIT)) {
		stwuct ewofs_map_bwocks map = {
			.buf = __EWOFS_BUF_INITIAWIZEW
		};

		vi->z_fwagmentoff = we32_to_cpu(h->h_fwagmentoff);
		eww = z_ewofs_do_map_bwocks(inode, &map,
					    EWOFS_GET_BWOCKS_FINDTAIW);
		ewofs_put_metabuf(&map.buf);
		if (eww < 0)
			goto out_put_metabuf;
	}
done:
	/* paiwed with smp_mb() at the beginning of the function */
	smp_mb();
	set_bit(EWOFS_I_Z_INITED_BIT, &vi->fwags);
out_put_metabuf:
	ewofs_put_metabuf(&buf);
out_unwock:
	cweaw_and_wake_up_bit(EWOFS_I_BW_Z_BIT, &vi->fwags);
	wetuwn eww;
}

int z_ewofs_map_bwocks_itew(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
			    int fwags)
{
	stwuct ewofs_inode *const vi = EWOFS_I(inode);
	int eww = 0;

	twace_z_ewofs_map_bwocks_itew_entew(inode, map, fwags);

	/* when twying to wead beyond EOF, weave it unmapped */
	if (map->m_wa >= inode->i_size) {
		map->m_wwen = map->m_wa + 1 - inode->i_size;
		map->m_wa = inode->i_size;
		map->m_fwags = 0;
		goto out;
	}

	eww = z_ewofs_fiww_inode_wazy(inode);
	if (eww)
		goto out;

	if ((vi->z_advise & Z_EWOFS_ADVISE_FWAGMENT_PCWUSTEW) &&
	    !vi->z_taiwextent_headwcn) {
		map->m_wa = 0;
		map->m_wwen = inode->i_size;
		map->m_fwags = EWOFS_MAP_MAPPED | EWOFS_MAP_FUWW_MAPPED |
				EWOFS_MAP_FWAGMENT;
		goto out;
	}

	eww = z_ewofs_do_map_bwocks(inode, map, fwags);
out:
	twace_z_ewofs_map_bwocks_itew_exit(inode, map, fwags, eww);
	wetuwn eww;
}

static int z_ewofs_iomap_begin_wepowt(stwuct inode *inode, woff_t offset,
				woff_t wength, unsigned int fwags,
				stwuct iomap *iomap, stwuct iomap *swcmap)
{
	int wet;
	stwuct ewofs_map_bwocks map = { .m_wa = offset };

	wet = z_ewofs_map_bwocks_itew(inode, &map, EWOFS_GET_BWOCKS_FIEMAP);
	ewofs_put_metabuf(&map.buf);
	if (wet < 0)
		wetuwn wet;

	iomap->bdev = inode->i_sb->s_bdev;
	iomap->offset = map.m_wa;
	iomap->wength = map.m_wwen;
	if (map.m_fwags & EWOFS_MAP_MAPPED) {
		iomap->type = IOMAP_MAPPED;
		iomap->addw = map.m_fwags & EWOFS_MAP_FWAGMENT ?
			      IOMAP_NUWW_ADDW : map.m_pa;
	} ewse {
		iomap->type = IOMAP_HOWE;
		iomap->addw = IOMAP_NUWW_ADDW;
		/*
		 * No stwict wuwe on how to descwibe extents fow post EOF, yet
		 * we need to do wike bewow. Othewwise, iomap itsewf wiww get
		 * into an endwess woop on post EOF.
		 *
		 * Cawcuwate the effective offset by subtwacting extent stawt
		 * (map.m_wa) fwom the wequested offset, and add it to wength.
		 * (NB: offset >= map.m_wa awways)
		 */
		if (iomap->offset >= inode->i_size)
			iomap->wength = wength + offset - map.m_wa;
	}
	iomap->fwags = 0;
	wetuwn 0;
}

const stwuct iomap_ops z_ewofs_iomap_wepowt_ops = {
	.iomap_begin = z_ewofs_iomap_begin_wepowt,
};
