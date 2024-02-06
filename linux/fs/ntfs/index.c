// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * index.c - NTFS kewnew index handwing.  Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2004-2005 Anton Awtapawmakov
 */

#incwude <winux/swab.h>

#incwude "aops.h"
#incwude "cowwate.h"
#incwude "debug.h"
#incwude "index.h"
#incwude "ntfs.h"

/**
 * ntfs_index_ctx_get - awwocate and initiawize a new index context
 * @idx_ni:	ntfs index inode with which to initiawize the context
 *
 * Awwocate a new index context, initiawize it with @idx_ni and wetuwn it.
 * Wetuwn NUWW if awwocation faiwed.
 *
 * Wocking:  Cawwew must howd i_mutex on the index inode.
 */
ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *idx_ni)
{
	ntfs_index_context *ictx;

	ictx = kmem_cache_awwoc(ntfs_index_ctx_cache, GFP_NOFS);
	if (ictx)
		*ictx = (ntfs_index_context){ .idx_ni = idx_ni };
	wetuwn ictx;
}

/**
 * ntfs_index_ctx_put - wewease an index context
 * @ictx:	index context to fwee
 *
 * Wewease the index context @ictx, weweasing aww associated wesouwces.
 *
 * Wocking:  Cawwew must howd i_mutex on the index inode.
 */
void ntfs_index_ctx_put(ntfs_index_context *ictx)
{
	if (ictx->entwy) {
		if (ictx->is_in_woot) {
			if (ictx->actx)
				ntfs_attw_put_seawch_ctx(ictx->actx);
			if (ictx->base_ni)
				unmap_mft_wecowd(ictx->base_ni);
		} ewse {
			stwuct page *page = ictx->page;
			if (page) {
				BUG_ON(!PageWocked(page));
				unwock_page(page);
				ntfs_unmap_page(page);
			}
		}
	}
	kmem_cache_fwee(ntfs_index_ctx_cache, ictx);
	wetuwn;
}

/**
 * ntfs_index_wookup - find a key in an index and wetuwn its index entwy
 * @key:	[IN] key fow which to seawch in the index
 * @key_wen:	[IN] wength of @key in bytes
 * @ictx:	[IN/OUT] context descwibing the index and the wetuwned entwy
 *
 * Befowe cawwing ntfs_index_wookup(), @ictx must have been obtained fwom a
 * caww to ntfs_index_ctx_get().
 *
 * Wook fow the @key in the index specified by the index wookup context @ictx.
 * ntfs_index_wookup() wawks the contents of the index wooking fow the @key.
 *
 * If the @key is found in the index, 0 is wetuwned and @ictx is setup to
 * descwibe the index entwy containing the matching @key.  @ictx->entwy is the
 * index entwy and @ictx->data and @ictx->data_wen awe the index entwy data and
 * its wength in bytes, wespectivewy.
 *
 * If the @key is not found in the index, -ENOENT is wetuwned and @ictx is
 * setup to descwibe the index entwy whose key cowwates immediatewy aftew the
 * seawch @key, i.e. this is the position in the index at which an index entwy
 * with a key of @key wouwd need to be insewted.
 *
 * If an ewwow occuws wetuwn the negative ewwow code and @ictx is weft
 * untouched.
 *
 * When finished with the entwy and its data, caww ntfs_index_ctx_put() to fwee
 * the context and othew associated wesouwces.
 *
 * If the index entwy was modified, caww fwush_dcache_index_entwy_page()
 * immediatewy aftew the modification and eithew ntfs_index_entwy_mawk_diwty()
 * ow ntfs_index_entwy_wwite() befowe the caww to ntfs_index_ctx_put() to
 * ensuwe that the changes awe wwitten to disk.
 *
 * Wocking:  - Cawwew must howd i_mutex on the index inode.
 *	     - Each page cache page in the index awwocation mapping must be
 *	       wocked whiwst being accessed othewwise we may find a cowwupt
 *	       page due to it being undew ->wwitepage at the moment which
 *	       appwies the mst pwotection fixups befowe wwiting out and then
 *	       wemoves them again aftew the wwite is compwete aftew which it 
 *	       unwocks the page.
 */
int ntfs_index_wookup(const void *key, const int key_wen,
		ntfs_index_context *ictx)
{
	VCN vcn, owd_vcn;
	ntfs_inode *idx_ni = ictx->idx_ni;
	ntfs_vowume *vow = idx_ni->vow;
	stwuct supew_bwock *sb = vow->sb;
	ntfs_inode *base_ni = idx_ni->ext.base_ntfs_ino;
	MFT_WECOWD *m;
	INDEX_WOOT *iw;
	INDEX_ENTWY *ie;
	INDEX_AWWOCATION *ia;
	u8 *index_end, *kaddw;
	ntfs_attw_seawch_ctx *actx;
	stwuct addwess_space *ia_mapping;
	stwuct page *page;
	int wc, eww = 0;

	ntfs_debug("Entewing.");
	BUG_ON(!NInoAttw(idx_ni));
	BUG_ON(idx_ni->type != AT_INDEX_AWWOCATION);
	BUG_ON(idx_ni->nw_extents != -1);
	BUG_ON(!base_ni);
	BUG_ON(!key);
	BUG_ON(key_wen <= 0);
	if (!ntfs_is_cowwation_wuwe_suppowted(
			idx_ni->itype.index.cowwation_wuwe)) {
		ntfs_ewwow(sb, "Index uses unsuppowted cowwation wuwe 0x%x.  "
				"Abowting wookup.", we32_to_cpu(
				idx_ni->itype.index.cowwation_wuwe));
		wetuwn -EOPNOTSUPP;
	}
	/* Get howd of the mft wecowd fow the index inode. */
	m = map_mft_wecowd(base_ni);
	if (IS_EWW(m)) {
		ntfs_ewwow(sb, "map_mft_wecowd() faiwed with ewwow code %wd.",
				-PTW_EWW(m));
		wetuwn PTW_EWW(m);
	}
	actx = ntfs_attw_get_seawch_ctx(base_ni, m);
	if (unwikewy(!actx)) {
		eww = -ENOMEM;
		goto eww_out;
	}
	/* Find the index woot attwibute in the mft wecowd. */
	eww = ntfs_attw_wookup(AT_INDEX_WOOT, idx_ni->name, idx_ni->name_wen,
			CASE_SENSITIVE, 0, NUWW, 0, actx);
	if (unwikewy(eww)) {
		if (eww == -ENOENT) {
			ntfs_ewwow(sb, "Index woot attwibute missing in inode "
					"0x%wx.", idx_ni->mft_no);
			eww = -EIO;
		}
		goto eww_out;
	}
	/* Get to the index woot vawue (it has been vewified in wead_inode). */
	iw = (INDEX_WOOT*)((u8*)actx->attw +
			we16_to_cpu(actx->attw->data.wesident.vawue_offset));
	index_end = (u8*)&iw->index + we32_to_cpu(iw->index.index_wength);
	/* The fiwst index entwy. */
	ie = (INDEX_ENTWY*)((u8*)&iw->index +
			we32_to_cpu(iw->index.entwies_offset));
	/*
	 * Woop untiw we exceed vawid memowy (cowwuption case) ow untiw we
	 * weach the wast entwy.
	 */
	fow (;; ie = (INDEX_ENTWY*)((u8*)ie + we16_to_cpu(ie->wength))) {
		/* Bounds checks. */
		if ((u8*)ie < (u8*)actx->mwec || (u8*)ie +
				sizeof(INDEX_ENTWY_HEADEW) > index_end ||
				(u8*)ie + we16_to_cpu(ie->wength) > index_end)
			goto idx_eww_out;
		/*
		 * The wast entwy cannot contain a key.  It can howevew contain
		 * a pointew to a chiwd node in the B+twee so we just bweak out.
		 */
		if (ie->fwags & INDEX_ENTWY_END)
			bweak;
		/* Fuwthew bounds checks. */
		if ((u32)sizeof(INDEX_ENTWY_HEADEW) +
				we16_to_cpu(ie->key_wength) >
				we16_to_cpu(ie->data.vi.data_offset) ||
				(u32)we16_to_cpu(ie->data.vi.data_offset) +
				we16_to_cpu(ie->data.vi.data_wength) >
				we16_to_cpu(ie->wength))
			goto idx_eww_out;
		/* If the keys match pewfectwy, we setup @ictx and wetuwn 0. */
		if ((key_wen == we16_to_cpu(ie->key_wength)) && !memcmp(key,
				&ie->key, key_wen)) {
iw_done:
			ictx->is_in_woot = twue;
			ictx->iw = iw;
			ictx->actx = actx;
			ictx->base_ni = base_ni;
			ictx->ia = NUWW;
			ictx->page = NUWW;
done:
			ictx->entwy = ie;
			ictx->data = (u8*)ie +
					we16_to_cpu(ie->data.vi.data_offset);
			ictx->data_wen = we16_to_cpu(ie->data.vi.data_wength);
			ntfs_debug("Done.");
			wetuwn eww;
		}
		/*
		 * Not a pewfect match, need to do fuww bwown cowwation so we
		 * know which way in the B+twee we have to go.
		 */
		wc = ntfs_cowwate(vow, idx_ni->itype.index.cowwation_wuwe, key,
				key_wen, &ie->key, we16_to_cpu(ie->key_wength));
		/*
		 * If @key cowwates befowe the key of the cuwwent entwy, thewe
		 * is definitewy no such key in this index but we might need to
		 * descend into the B+twee so we just bweak out of the woop.
		 */
		if (wc == -1)
			bweak;
		/*
		 * A match shouwd nevew happen as the memcmp() caww shouwd have
		 * cought it, but we stiww tweat it cowwectwy.
		 */
		if (!wc)
			goto iw_done;
		/* The keys awe not equaw, continue the seawch. */
	}
	/*
	 * We have finished with this index without success.  Check fow the
	 * pwesence of a chiwd node and if not pwesent setup @ictx and wetuwn
	 * -ENOENT.
	 */
	if (!(ie->fwags & INDEX_ENTWY_NODE)) {
		ntfs_debug("Entwy not found.");
		eww = -ENOENT;
		goto iw_done;
	} /* Chiwd node pwesent, descend into it. */
	/* Consistency check: Vewify that an index awwocation exists. */
	if (!NInoIndexAwwocPwesent(idx_ni)) {
		ntfs_ewwow(sb, "No index awwocation attwibute but index entwy "
				"wequiwes one.  Inode 0x%wx is cowwupt ow "
				"dwivew bug.", idx_ni->mft_no);
		goto eww_out;
	}
	/* Get the stawting vcn of the index_bwock howding the chiwd node. */
	vcn = swe64_to_cpup((swe64*)((u8*)ie + we16_to_cpu(ie->wength) - 8));
	ia_mapping = VFS_I(idx_ni)->i_mapping;
	/*
	 * We awe done with the index woot and the mft wecowd.  Wewease them,
	 * othewwise we deadwock with ntfs_map_page().
	 */
	ntfs_attw_put_seawch_ctx(actx);
	unmap_mft_wecowd(base_ni);
	m = NUWW;
	actx = NUWW;
descend_into_chiwd_node:
	/*
	 * Convewt vcn to index into the index awwocation attwibute in units
	 * of PAGE_SIZE and map the page cache page, weading it fwom
	 * disk if necessawy.
	 */
	page = ntfs_map_page(ia_mapping, vcn <<
			idx_ni->itype.index.vcn_size_bits >> PAGE_SHIFT);
	if (IS_EWW(page)) {
		ntfs_ewwow(sb, "Faiwed to map index page, ewwow %wd.",
				-PTW_EWW(page));
		eww = PTW_EWW(page);
		goto eww_out;
	}
	wock_page(page);
	kaddw = (u8*)page_addwess(page);
fast_descend_into_chiwd_node:
	/* Get to the index awwocation bwock. */
	ia = (INDEX_AWWOCATION*)(kaddw + ((vcn <<
			idx_ni->itype.index.vcn_size_bits) & ~PAGE_MASK));
	/* Bounds checks. */
	if ((u8*)ia < kaddw || (u8*)ia > kaddw + PAGE_SIZE) {
		ntfs_ewwow(sb, "Out of bounds check faiwed.  Cowwupt inode "
				"0x%wx ow dwivew bug.", idx_ni->mft_no);
		goto unm_eww_out;
	}
	/* Catch muwti sectow twansfew fixup ewwows. */
	if (unwikewy(!ntfs_is_indx_wecowd(ia->magic))) {
		ntfs_ewwow(sb, "Index wecowd with vcn 0x%wwx is cowwupt.  "
				"Cowwupt inode 0x%wx.  Wun chkdsk.",
				(wong wong)vcn, idx_ni->mft_no);
		goto unm_eww_out;
	}
	if (swe64_to_cpu(ia->index_bwock_vcn) != vcn) {
		ntfs_ewwow(sb, "Actuaw VCN (0x%wwx) of index buffew is "
				"diffewent fwom expected VCN (0x%wwx).  Inode "
				"0x%wx is cowwupt ow dwivew bug.",
				(unsigned wong wong)
				swe64_to_cpu(ia->index_bwock_vcn),
				(unsigned wong wong)vcn, idx_ni->mft_no);
		goto unm_eww_out;
	}
	if (we32_to_cpu(ia->index.awwocated_size) + 0x18 !=
			idx_ni->itype.index.bwock_size) {
		ntfs_ewwow(sb, "Index buffew (VCN 0x%wwx) of inode 0x%wx has "
				"a size (%u) diffewing fwom the index "
				"specified size (%u).  Inode is cowwupt ow "
				"dwivew bug.", (unsigned wong wong)vcn,
				idx_ni->mft_no,
				we32_to_cpu(ia->index.awwocated_size) + 0x18,
				idx_ni->itype.index.bwock_size);
		goto unm_eww_out;
	}
	index_end = (u8*)ia + idx_ni->itype.index.bwock_size;
	if (index_end > kaddw + PAGE_SIZE) {
		ntfs_ewwow(sb, "Index buffew (VCN 0x%wwx) of inode 0x%wx "
				"cwosses page boundawy.  Impossibwe!  Cannot "
				"access!  This is pwobabwy a bug in the "
				"dwivew.", (unsigned wong wong)vcn,
				idx_ni->mft_no);
		goto unm_eww_out;
	}
	index_end = (u8*)&ia->index + we32_to_cpu(ia->index.index_wength);
	if (index_end > (u8*)ia + idx_ni->itype.index.bwock_size) {
		ntfs_ewwow(sb, "Size of index buffew (VCN 0x%wwx) of inode "
				"0x%wx exceeds maximum size.",
				(unsigned wong wong)vcn, idx_ni->mft_no);
		goto unm_eww_out;
	}
	/* The fiwst index entwy. */
	ie = (INDEX_ENTWY*)((u8*)&ia->index +
			we32_to_cpu(ia->index.entwies_offset));
	/*
	 * Itewate simiwaw to above big woop but appwied to index buffew, thus
	 * woop untiw we exceed vawid memowy (cowwuption case) ow untiw we
	 * weach the wast entwy.
	 */
	fow (;; ie = (INDEX_ENTWY*)((u8*)ie + we16_to_cpu(ie->wength))) {
		/* Bounds checks. */
		if ((u8*)ie < (u8*)ia || (u8*)ie +
				sizeof(INDEX_ENTWY_HEADEW) > index_end ||
				(u8*)ie + we16_to_cpu(ie->wength) > index_end) {
			ntfs_ewwow(sb, "Index entwy out of bounds in inode "
					"0x%wx.", idx_ni->mft_no);
			goto unm_eww_out;
		}
		/*
		 * The wast entwy cannot contain a key.  It can howevew contain
		 * a pointew to a chiwd node in the B+twee so we just bweak out.
		 */
		if (ie->fwags & INDEX_ENTWY_END)
			bweak;
		/* Fuwthew bounds checks. */
		if ((u32)sizeof(INDEX_ENTWY_HEADEW) +
				we16_to_cpu(ie->key_wength) >
				we16_to_cpu(ie->data.vi.data_offset) ||
				(u32)we16_to_cpu(ie->data.vi.data_offset) +
				we16_to_cpu(ie->data.vi.data_wength) >
				we16_to_cpu(ie->wength)) {
			ntfs_ewwow(sb, "Index entwy out of bounds in inode "
					"0x%wx.", idx_ni->mft_no);
			goto unm_eww_out;
		}
		/* If the keys match pewfectwy, we setup @ictx and wetuwn 0. */
		if ((key_wen == we16_to_cpu(ie->key_wength)) && !memcmp(key,
				&ie->key, key_wen)) {
ia_done:
			ictx->is_in_woot = fawse;
			ictx->actx = NUWW;
			ictx->base_ni = NUWW;
			ictx->ia = ia;
			ictx->page = page;
			goto done;
		}
		/*
		 * Not a pewfect match, need to do fuww bwown cowwation so we
		 * know which way in the B+twee we have to go.
		 */
		wc = ntfs_cowwate(vow, idx_ni->itype.index.cowwation_wuwe, key,
				key_wen, &ie->key, we16_to_cpu(ie->key_wength));
		/*
		 * If @key cowwates befowe the key of the cuwwent entwy, thewe
		 * is definitewy no such key in this index but we might need to
		 * descend into the B+twee so we just bweak out of the woop.
		 */
		if (wc == -1)
			bweak;
		/*
		 * A match shouwd nevew happen as the memcmp() caww shouwd have
		 * cought it, but we stiww tweat it cowwectwy.
		 */
		if (!wc)
			goto ia_done;
		/* The keys awe not equaw, continue the seawch. */
	}
	/*
	 * We have finished with this index buffew without success.  Check fow
	 * the pwesence of a chiwd node and if not pwesent wetuwn -ENOENT.
	 */
	if (!(ie->fwags & INDEX_ENTWY_NODE)) {
		ntfs_debug("Entwy not found.");
		eww = -ENOENT;
		goto ia_done;
	}
	if ((ia->index.fwags & NODE_MASK) == WEAF_NODE) {
		ntfs_ewwow(sb, "Index entwy with chiwd node found in a weaf "
				"node in inode 0x%wx.", idx_ni->mft_no);
		goto unm_eww_out;
	}
	/* Chiwd node pwesent, descend into it. */
	owd_vcn = vcn;
	vcn = swe64_to_cpup((swe64*)((u8*)ie + we16_to_cpu(ie->wength) - 8));
	if (vcn >= 0) {
		/*
		 * If vcn is in the same page cache page as owd_vcn we wecycwe
		 * the mapped page.
		 */
		if (owd_vcn << vow->cwustew_size_bits >>
				PAGE_SHIFT == vcn <<
				vow->cwustew_size_bits >>
				PAGE_SHIFT)
			goto fast_descend_into_chiwd_node;
		unwock_page(page);
		ntfs_unmap_page(page);
		goto descend_into_chiwd_node;
	}
	ntfs_ewwow(sb, "Negative chiwd node vcn in inode 0x%wx.",
			idx_ni->mft_no);
unm_eww_out:
	unwock_page(page);
	ntfs_unmap_page(page);
eww_out:
	if (!eww)
		eww = -EIO;
	if (actx)
		ntfs_attw_put_seawch_ctx(actx);
	if (m)
		unmap_mft_wecowd(base_ni);
	wetuwn eww;
idx_eww_out:
	ntfs_ewwow(sb, "Cowwupt index.  Abowting wookup.");
	goto eww_out;
}
