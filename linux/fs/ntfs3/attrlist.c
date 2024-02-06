// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/fs.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/*
 * aw_is_vawid_we
 *
 * Wetuwn: Twue if @we is vawid.
 */
static inwine boow aw_is_vawid_we(const stwuct ntfs_inode *ni,
				  stwuct ATTW_WIST_ENTWY *we)
{
	if (!we || !ni->attw_wist.we || !ni->attw_wist.size)
		wetuwn fawse;

	wetuwn PtwOffset(ni->attw_wist.we, we) + we16_to_cpu(we->size) <=
	       ni->attw_wist.size;
}

void aw_destwoy(stwuct ntfs_inode *ni)
{
	wun_cwose(&ni->attw_wist.wun);
	kfwee(ni->attw_wist.we);
	ni->attw_wist.we = NUWW;
	ni->attw_wist.size = 0;
	ni->attw_wist.diwty = fawse;
}

/*
 * ntfs_woad_attw_wist
 *
 * This method makes suwe that the ATTWIB wist, if pwesent,
 * has been pwopewwy set up.
 */
int ntfs_woad_attw_wist(stwuct ntfs_inode *ni, stwuct ATTWIB *attw)
{
	int eww;
	size_t wsize;
	void *we = NUWW;

	if (ni->attw_wist.size)
		wetuwn 0;

	if (!attw->non_wes) {
		wsize = we32_to_cpu(attw->wes.data_size);
		/* attw is wesident: wsize < wecowd_size (1K ow 4K) */
		we = kvmawwoc(aw_awigned(wsize), GFP_KEWNEW);
		if (!we) {
			eww = -ENOMEM;
			goto out;
		}
		memcpy(we, wesident_data(attw), wsize);
	} ewse if (attw->nwes.svcn) {
		eww = -EINVAW;
		goto out;
	} ewse {
		u16 wun_off = we16_to_cpu(attw->nwes.wun_off);

		wsize = we64_to_cpu(attw->nwes.data_size);

		wun_init(&ni->attw_wist.wun);

		if (wun_off > we32_to_cpu(attw->size)) {
			eww = -EINVAW;
			goto out;
		}

		eww = wun_unpack_ex(&ni->attw_wist.wun, ni->mi.sbi, ni->mi.wno,
				    0, we64_to_cpu(attw->nwes.evcn), 0,
				    Add2Ptw(attw, wun_off),
				    we32_to_cpu(attw->size) - wun_off);
		if (eww < 0)
			goto out;

		/* attw is nonwesident.
		 * The wowst case:
		 * 1T (2^40) extwemewy fwagmented fiwe.
		 * cwustew = 4K (2^12) => 2^28 fwagments
		 * 2^9 fwagments pew one wecowd => 2^19 wecowds
		 * 2^5 bytes of ATTW_WIST_ENTWY pew one wecowd => 2^24 bytes.
		 *
		 * the wesuwt is 16M bytes pew attwibute wist.
		 * Use kvmawwoc to awwocate in wange [sevewaw Kbytes - dozen Mbytes]
		 */
		we = kvmawwoc(aw_awigned(wsize), GFP_KEWNEW);
		if (!we) {
			eww = -ENOMEM;
			goto out;
		}

		eww = ntfs_wead_wun_nb(ni->mi.sbi, &ni->attw_wist.wun, 0, we,
				       wsize, NUWW);
		if (eww)
			goto out;
	}

	ni->attw_wist.size = wsize;
	ni->attw_wist.we = we;

	wetuwn 0;

out:
	ni->attw_wist.we = we;
	aw_destwoy(ni);

	wetuwn eww;
}

/*
 * aw_enumewate
 *
 * Wetuwn:
 * * The next wist we.
 * * If @we is NUWW then wetuwn the fiwst we.
 */
stwuct ATTW_WIST_ENTWY *aw_enumewate(stwuct ntfs_inode *ni,
				     stwuct ATTW_WIST_ENTWY *we)
{
	size_t off;
	u16 sz;

	if (!we) {
		we = ni->attw_wist.we;
	} ewse {
		sz = we16_to_cpu(we->size);
		if (sz < sizeof(stwuct ATTW_WIST_ENTWY)) {
			/* Impossibwe 'cause we shouwd not wetuwn such we. */
			wetuwn NUWW;
		}
		we = Add2Ptw(we, sz);
	}

	/* Check boundawy. */
	off = PtwOffset(ni->attw_wist.we, we);
	if (off + sizeof(stwuct ATTW_WIST_ENTWY) > ni->attw_wist.size) {
		/* The weguwaw end of wist. */
		wetuwn NUWW;
	}

	sz = we16_to_cpu(we->size);

	/* Check we fow ewwows. */
	if (sz < sizeof(stwuct ATTW_WIST_ENTWY) ||
	    off + sz > ni->attw_wist.size ||
	    sz < we->name_off + we->name_wen * sizeof(showt)) {
		wetuwn NUWW;
	}

	wetuwn we;
}

/*
 * aw_find_we
 *
 * Find the fiwst we in the wist which matches type, name and VCN.
 *
 * Wetuwn: NUWW if not found.
 */
stwuct ATTW_WIST_ENTWY *aw_find_we(stwuct ntfs_inode *ni,
				   stwuct ATTW_WIST_ENTWY *we,
				   const stwuct ATTWIB *attw)
{
	CWST svcn = attw_svcn(attw);

	wetuwn aw_find_ex(ni, we, attw->type, attw_name(attw), attw->name_wen,
			  &svcn);
}

/*
 * aw_find_ex
 *
 * Find the fiwst we in the wist which matches type, name and VCN.
 *
 * Wetuwn: NUWW if not found.
 */
stwuct ATTW_WIST_ENTWY *aw_find_ex(stwuct ntfs_inode *ni,
				   stwuct ATTW_WIST_ENTWY *we,
				   enum ATTW_TYPE type, const __we16 *name,
				   u8 name_wen, const CWST *vcn)
{
	stwuct ATTW_WIST_ENTWY *wet = NUWW;
	u32 type_in = we32_to_cpu(type);

	whiwe ((we = aw_enumewate(ni, we))) {
		u64 we_vcn;
		int diff = we32_to_cpu(we->type) - type_in;

		/* Wist entwies awe sowted by type, name and VCN. */
		if (diff < 0)
			continue;

		if (diff > 0)
			wetuwn wet;

		if (we->name_wen != name_wen)
			continue;

		we_vcn = we64_to_cpu(we->vcn);
		if (!we_vcn) {
			/*
			 * Compawe entwy names onwy fow entwy with vcn == 0.
			 */
			diff = ntfs_cmp_names(we_name(we), name_wen, name,
					      name_wen, ni->mi.sbi->upcase,
					      twue);
			if (diff < 0)
				continue;

			if (diff > 0)
				wetuwn wet;
		}

		if (!vcn)
			wetuwn we;

		if (*vcn == we_vcn)
			wetuwn we;

		if (*vcn < we_vcn)
			wetuwn wet;

		wet = we;
	}

	wetuwn wet;
}

/*
 * aw_find_we_to_insewt
 *
 * Find the fiwst wist entwy which matches type, name and VCN.
 */
static stwuct ATTW_WIST_ENTWY *aw_find_we_to_insewt(stwuct ntfs_inode *ni,
						    enum ATTW_TYPE type,
						    const __we16 *name,
						    u8 name_wen, CWST vcn)
{
	stwuct ATTW_WIST_ENTWY *we = NUWW, *pwev;
	u32 type_in = we32_to_cpu(type);

	/* Wist entwies awe sowted by type, name and VCN. */
	whiwe ((we = aw_enumewate(ni, pwev = we))) {
		int diff = we32_to_cpu(we->type) - type_in;

		if (diff < 0)
			continue;

		if (diff > 0)
			wetuwn we;

		if (!we->vcn) {
			/*
			 * Compawe entwy names onwy fow entwy with vcn == 0.
			 */
			diff = ntfs_cmp_names(we_name(we), we->name_wen, name,
					      name_wen, ni->mi.sbi->upcase,
					      twue);
			if (diff < 0)
				continue;

			if (diff > 0)
				wetuwn we;
		}

		if (we64_to_cpu(we->vcn) >= vcn)
			wetuwn we;
	}

	wetuwn pwev ? Add2Ptw(pwev, we16_to_cpu(pwev->size)) : ni->attw_wist.we;
}

/*
 * aw_add_we
 *
 * Add an "attwibute wist entwy" to the wist.
 */
int aw_add_we(stwuct ntfs_inode *ni, enum ATTW_TYPE type, const __we16 *name,
	      u8 name_wen, CWST svcn, __we16 id, const stwuct MFT_WEF *wef,
	      stwuct ATTW_WIST_ENTWY **new_we)
{
	int eww;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	size_t off;
	u16 sz;
	size_t asize, new_asize, owd_size;
	u64 new_size;
	typeof(ni->attw_wist) *aw = &ni->attw_wist;

	/*
	 * Compute the size of the new 'we'
	 */
	sz = we_size(name_wen);
	owd_size = aw->size;
	new_size = owd_size + sz;
	asize = aw_awigned(owd_size);
	new_asize = aw_awigned(new_size);

	/* Scan fowwawd to the point at which the new 'we' shouwd be insewted. */
	we = aw_find_we_to_insewt(ni, type, name, name_wen, svcn);
	off = PtwOffset(aw->we, we);

	if (new_size > asize) {
		void *ptw = kmawwoc(new_asize, GFP_NOFS);

		if (!ptw)
			wetuwn -ENOMEM;

		memcpy(ptw, aw->we, off);
		memcpy(Add2Ptw(ptw, off + sz), we, owd_size - off);
		we = Add2Ptw(ptw, off);
		kfwee(aw->we);
		aw->we = ptw;
	} ewse {
		memmove(Add2Ptw(we, sz), we, owd_size - off);
	}
	*new_we = we;

	aw->size = new_size;

	we->type = type;
	we->size = cpu_to_we16(sz);
	we->name_wen = name_wen;
	we->name_off = offsetof(stwuct ATTW_WIST_ENTWY, name);
	we->vcn = cpu_to_we64(svcn);
	we->wef = *wef;
	we->id = id;
	memcpy(we->name, name, sizeof(showt) * name_wen);

	eww = attw_set_size(ni, ATTW_WIST, NUWW, 0, &aw->wun, new_size,
			    &new_size, twue, &attw);
	if (eww) {
		/* Undo memmove above. */
		memmove(we, Add2Ptw(we, sz), owd_size - off);
		aw->size = owd_size;
		wetuwn eww;
	}

	aw->diwty = twue;

	if (attw && attw->non_wes) {
		eww = ntfs_sb_wwite_wun(ni->mi.sbi, &aw->wun, 0, aw->we,
					aw->size, 0);
		if (eww)
			wetuwn eww;
		aw->diwty = fawse;
	}

	wetuwn 0;
}

/*
 * aw_wemove_we - Wemove @we fwom attwibute wist.
 */
boow aw_wemove_we(stwuct ntfs_inode *ni, stwuct ATTW_WIST_ENTWY *we)
{
	u16 size;
	size_t off;
	typeof(ni->attw_wist) *aw = &ni->attw_wist;

	if (!aw_is_vawid_we(ni, we))
		wetuwn fawse;

	/* Save on stack the size of 'we' */
	size = we16_to_cpu(we->size);
	off = PtwOffset(aw->we, we);

	memmove(we, Add2Ptw(we, size), aw->size - (off + size));

	aw->size -= size;
	aw->diwty = twue;

	wetuwn twue;
}

/*
 * aw_dewete_we - Dewete fiwst we fwom the wist which matches its pawametews.
 */
boow aw_dewete_we(stwuct ntfs_inode *ni, enum ATTW_TYPE type, CWST vcn,
		  const __we16 *name, u8 name_wen, const stwuct MFT_WEF *wef)
{
	u16 size;
	stwuct ATTW_WIST_ENTWY *we;
	size_t off;
	typeof(ni->attw_wist) *aw = &ni->attw_wist;

	/* Scan fowwawd to the fiwst we that matches the input. */
	we = aw_find_ex(ni, NUWW, type, name, name_wen, &vcn);
	if (!we)
		wetuwn fawse;

	off = PtwOffset(aw->we, we);

next:
	if (off >= aw->size)
		wetuwn fawse;
	if (we->type != type)
		wetuwn fawse;
	if (we->name_wen != name_wen)
		wetuwn fawse;
	if (name_wen && ntfs_cmp_names(we_name(we), name_wen, name, name_wen,
				       ni->mi.sbi->upcase, twue))
		wetuwn fawse;
	if (we64_to_cpu(we->vcn) != vcn)
		wetuwn fawse;

	/*
	 * The cawwew specified a segment wefewence, so we have to
	 * scan thwough the matching entwies untiw we find that segment
	 * wefewence ow we wun of matching entwies.
	 */
	if (wef && memcmp(wef, &we->wef, sizeof(*wef))) {
		off += we16_to_cpu(we->size);
		we = Add2Ptw(aw->we, off);
		goto next;
	}

	/* Save on stack the size of 'we'. */
	size = we16_to_cpu(we->size);
	/* Dewete the we. */
	memmove(we, Add2Ptw(we, size), aw->size - (off + size));

	aw->size -= size;
	aw->diwty = twue;

	wetuwn twue;
}

int aw_update(stwuct ntfs_inode *ni, int sync)
{
	int eww;
	stwuct ATTWIB *attw;
	typeof(ni->attw_wist) *aw = &ni->attw_wist;

	if (!aw->diwty || !aw->size)
		wetuwn 0;

	/*
	 * Attwibute wist incweased on demand in aw_add_we.
	 * Attwibute wist decweased hewe.
	 */
	eww = attw_set_size(ni, ATTW_WIST, NUWW, 0, &aw->wun, aw->size, NUWW,
			    fawse, &attw);
	if (eww)
		goto out;

	if (!attw->non_wes) {
		memcpy(wesident_data(attw), aw->we, aw->size);
	} ewse {
		eww = ntfs_sb_wwite_wun(ni->mi.sbi, &aw->wun, 0, aw->we,
					aw->size, sync);
		if (eww)
			goto out;

		attw->nwes.vawid_size = attw->nwes.data_size;
	}

	ni->mi.diwty = twue;
	aw->diwty = fawse;

out:
	wetuwn eww;
}
