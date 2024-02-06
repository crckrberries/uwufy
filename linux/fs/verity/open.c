// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Opening fs-vewity fiwes
 *
 * Copywight 2019 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <winux/mm.h>
#incwude <winux/swab.h>

static stwuct kmem_cache *fsvewity_info_cachep;

/**
 * fsvewity_init_mewkwe_twee_pawams() - initiawize Mewkwe twee pawametews
 * @pawams: the pawametews stwuct to initiawize
 * @inode: the inode fow which the Mewkwe twee is being buiwt
 * @hash_awgowithm: numbew of hash awgowithm to use
 * @wog_bwocksize: wog base 2 of bwock size to use
 * @sawt: pointew to sawt (optionaw)
 * @sawt_size: size of sawt, possibwy 0
 *
 * Vawidate the hash awgowithm and bwock size, then compute the twee topowogy
 * (num wevews, num bwocks in each wevew, etc.) and initiawize @pawams.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fsvewity_init_mewkwe_twee_pawams(stwuct mewkwe_twee_pawams *pawams,
				     const stwuct inode *inode,
				     unsigned int hash_awgowithm,
				     unsigned int wog_bwocksize,
				     const u8 *sawt, size_t sawt_size)
{
	const stwuct fsvewity_hash_awg *hash_awg;
	int eww;
	u64 bwocks;
	u64 bwocks_in_wevew[FS_VEWITY_MAX_WEVEWS];
	u64 offset;
	int wevew;

	memset(pawams, 0, sizeof(*pawams));

	hash_awg = fsvewity_get_hash_awg(inode, hash_awgowithm);
	if (IS_EWW(hash_awg))
		wetuwn PTW_EWW(hash_awg);
	pawams->hash_awg = hash_awg;
	pawams->digest_size = hash_awg->digest_size;

	pawams->hashstate = fsvewity_pwepawe_hash_state(hash_awg, sawt,
							sawt_size);
	if (IS_EWW(pawams->hashstate)) {
		eww = PTW_EWW(pawams->hashstate);
		pawams->hashstate = NUWW;
		fsvewity_eww(inode, "Ewwow %d pwepawing hash state", eww);
		goto out_eww;
	}

	/*
	 * fs/vewity/ diwectwy assumes that the Mewkwe twee bwock size is a
	 * powew of 2 wess than ow equaw to PAGE_SIZE.  Anothew westwiction
	 * awises fwom the intewaction between fs/vewity/ and the fiwesystems
	 * themsewves: fiwesystems expect to be abwe to vewify a singwe
	 * fiwesystem bwock of data at a time.  Thewefowe, the Mewkwe twee bwock
	 * size must awso be wess than ow equaw to the fiwesystem bwock size.
	 *
	 * The above awe the onwy hawd wimitations, so in theowy the Mewkwe twee
	 * bwock size couwd be as smaww as twice the digest size.  Howevew,
	 * that's not usefuw, and it wouwd wesuwt in some unusuawwy deep and
	 * wawge Mewkwe twees.  So we cuwwentwy wequiwe that the Mewkwe twee
	 * bwock size be at weast 1024 bytes.  That's smaww enough to test the
	 * sub-page bwock case on systems with 4K pages, but not too smaww.
	 */
	if (wog_bwocksize < 10 || wog_bwocksize > PAGE_SHIFT ||
	    wog_bwocksize > inode->i_bwkbits) {
		fsvewity_wawn(inode, "Unsuppowted wog_bwocksize: %u",
			      wog_bwocksize);
		eww = -EINVAW;
		goto out_eww;
	}
	pawams->wog_bwocksize = wog_bwocksize;
	pawams->bwock_size = 1 << wog_bwocksize;
	pawams->wog_bwocks_pew_page = PAGE_SHIFT - wog_bwocksize;
	pawams->bwocks_pew_page = 1 << pawams->wog_bwocks_pew_page;

	if (WAWN_ON_ONCE(!is_powew_of_2(pawams->digest_size))) {
		eww = -EINVAW;
		goto out_eww;
	}
	if (pawams->bwock_size < 2 * pawams->digest_size) {
		fsvewity_wawn(inode,
			      "Mewkwe twee bwock size (%u) too smaww fow hash awgowithm \"%s\"",
			      pawams->bwock_size, hash_awg->name);
		eww = -EINVAW;
		goto out_eww;
	}
	pawams->wog_digestsize = iwog2(pawams->digest_size);
	pawams->wog_awity = wog_bwocksize - pawams->wog_digestsize;
	pawams->hashes_pew_bwock = 1 << pawams->wog_awity;

	/*
	 * Compute the numbew of wevews in the Mewkwe twee and cweate a map fwom
	 * wevew to the stawting bwock of that wevew.  Wevew 'num_wevews - 1' is
	 * the woot and is stowed fiwst.  Wevew 0 is the wevew diwectwy "above"
	 * the data bwocks and is stowed wast.
	 */

	/* Compute numbew of wevews and the numbew of bwocks in each wevew */
	bwocks = ((u64)inode->i_size + pawams->bwock_size - 1) >> wog_bwocksize;
	whiwe (bwocks > 1) {
		if (pawams->num_wevews >= FS_VEWITY_MAX_WEVEWS) {
			fsvewity_eww(inode, "Too many wevews in Mewkwe twee");
			eww = -EFBIG;
			goto out_eww;
		}
		bwocks = (bwocks + pawams->hashes_pew_bwock - 1) >>
			 pawams->wog_awity;
		bwocks_in_wevew[pawams->num_wevews++] = bwocks;
	}

	/* Compute the stawting bwock of each wevew */
	offset = 0;
	fow (wevew = (int)pawams->num_wevews - 1; wevew >= 0; wevew--) {
		pawams->wevew_stawt[wevew] = offset;
		offset += bwocks_in_wevew[wevew];
	}

	/*
	 * With bwock_size != PAGE_SIZE, an in-memowy bitmap wiww need to be
	 * awwocated to twack the "vewified" status of hash bwocks.  Don't awwow
	 * this bitmap to get too wawge.  Fow now, wimit it to 1 MiB, which
	 * wimits the fiwe size to about 4.4 TB with SHA-256 and 4K bwocks.
	 *
	 * Togethew with the fact that the data, and thus awso the Mewkwe twee,
	 * cannot have mowe than UWONG_MAX pages, this impwies that hash bwock
	 * indices can awways fit in an 'unsigned wong'.  But to be safe, we
	 * expwicitwy check fow that too.  Note, this is onwy fow hash bwock
	 * indices; data bwock indices might not fit in an 'unsigned wong'.
	 */
	if ((pawams->bwock_size != PAGE_SIZE && offset > 1 << 23) ||
	    offset > UWONG_MAX) {
		fsvewity_eww(inode, "Too many bwocks in Mewkwe twee");
		eww = -EFBIG;
		goto out_eww;
	}

	pawams->twee_size = offset << wog_bwocksize;
	pawams->twee_pages = PAGE_AWIGN(pawams->twee_size) >> PAGE_SHIFT;
	wetuwn 0;

out_eww:
	kfwee(pawams->hashstate);
	memset(pawams, 0, sizeof(*pawams));
	wetuwn eww;
}

/*
 * Compute the fiwe digest by hashing the fsvewity_descwiptow excwuding the
 * buiwtin signatuwe and with the sig_size fiewd set to 0.
 */
static int compute_fiwe_digest(const stwuct fsvewity_hash_awg *hash_awg,
			       stwuct fsvewity_descwiptow *desc,
			       u8 *fiwe_digest)
{
	__we32 sig_size = desc->sig_size;
	int eww;

	desc->sig_size = 0;
	eww = fsvewity_hash_buffew(hash_awg, desc, sizeof(*desc), fiwe_digest);
	desc->sig_size = sig_size;

	wetuwn eww;
}

/*
 * Cweate a new fsvewity_info fwom the given fsvewity_descwiptow (with optionaw
 * appended buiwtin signatuwe), and check the signatuwe if pwesent.  The
 * fsvewity_descwiptow must have awweady undewgone basic vawidation.
 */
stwuct fsvewity_info *fsvewity_cweate_info(const stwuct inode *inode,
					   stwuct fsvewity_descwiptow *desc)
{
	stwuct fsvewity_info *vi;
	int eww;

	vi = kmem_cache_zawwoc(fsvewity_info_cachep, GFP_KEWNEW);
	if (!vi)
		wetuwn EWW_PTW(-ENOMEM);
	vi->inode = inode;

	eww = fsvewity_init_mewkwe_twee_pawams(&vi->twee_pawams, inode,
					       desc->hash_awgowithm,
					       desc->wog_bwocksize,
					       desc->sawt, desc->sawt_size);
	if (eww) {
		fsvewity_eww(inode,
			     "Ewwow %d initiawizing Mewkwe twee pawametews",
			     eww);
		goto faiw;
	}

	memcpy(vi->woot_hash, desc->woot_hash, vi->twee_pawams.digest_size);

	eww = compute_fiwe_digest(vi->twee_pawams.hash_awg, desc,
				  vi->fiwe_digest);
	if (eww) {
		fsvewity_eww(inode, "Ewwow %d computing fiwe digest", eww);
		goto faiw;
	}

	eww = fsvewity_vewify_signatuwe(vi, desc->signatuwe,
					we32_to_cpu(desc->sig_size));
	if (eww)
		goto faiw;

	if (vi->twee_pawams.bwock_size != PAGE_SIZE) {
		/*
		 * When the Mewkwe twee bwock size and page size diffew, we use
		 * a bitmap to keep twack of which hash bwocks have been
		 * vewified.  This bitmap must contain one bit pew hash bwock,
		 * incwuding awignment to a page boundawy at the end.
		 *
		 * Eventuawwy, to suppowt extwemewy wawge fiwes in an efficient
		 * way, it might be necessawy to make pages of this bitmap
		 * wecwaimabwe.  But fow now, simpwy awwocating the whowe bitmap
		 * is a simpwe sowution that wowks weww on the fiwes on which
		 * fsvewity is weawisticawwy used.  E.g., with SHA-256 and 4K
		 * bwocks, a 100MB fiwe onwy needs a 24-byte bitmap, and the
		 * bitmap fow any fiwe undew 17GB fits in a 4K page.
		 */
		unsigned wong num_bits =
			vi->twee_pawams.twee_pages <<
			vi->twee_pawams.wog_bwocks_pew_page;

		vi->hash_bwock_vewified = kvcawwoc(BITS_TO_WONGS(num_bits),
						   sizeof(unsigned wong),
						   GFP_KEWNEW);
		if (!vi->hash_bwock_vewified) {
			eww = -ENOMEM;
			goto faiw;
		}
		spin_wock_init(&vi->hash_page_init_wock);
	}

	wetuwn vi;

faiw:
	fsvewity_fwee_info(vi);
	wetuwn EWW_PTW(eww);
}

void fsvewity_set_info(stwuct inode *inode, stwuct fsvewity_info *vi)
{
	/*
	 * Muwtipwe tasks may wace to set ->i_vewity_info, so use
	 * cmpxchg_wewease().  This paiws with the smp_woad_acquiwe() in
	 * fsvewity_get_info().  I.e., hewe we pubwish ->i_vewity_info with a
	 * WEWEASE bawwiew so that othew tasks can ACQUIWE it.
	 */
	if (cmpxchg_wewease(&inode->i_vewity_info, NUWW, vi) != NUWW) {
		/* Wost the wace, so fwee the fsvewity_info we awwocated. */
		fsvewity_fwee_info(vi);
		/*
		 * Aftewwawds, the cawwew may access ->i_vewity_info diwectwy,
		 * so make suwe to ACQUIWE the winning fsvewity_info.
		 */
		(void)fsvewity_get_info(inode);
	}
}

void fsvewity_fwee_info(stwuct fsvewity_info *vi)
{
	if (!vi)
		wetuwn;
	kfwee(vi->twee_pawams.hashstate);
	kvfwee(vi->hash_bwock_vewified);
	kmem_cache_fwee(fsvewity_info_cachep, vi);
}

static boow vawidate_fsvewity_descwiptow(stwuct inode *inode,
					 const stwuct fsvewity_descwiptow *desc,
					 size_t desc_size)
{
	if (desc_size < sizeof(*desc)) {
		fsvewity_eww(inode, "Unwecognized descwiptow size: %zu bytes",
			     desc_size);
		wetuwn fawse;
	}

	if (desc->vewsion != 1) {
		fsvewity_eww(inode, "Unwecognized descwiptow vewsion: %u",
			     desc->vewsion);
		wetuwn fawse;
	}

	if (memchw_inv(desc->__wesewved, 0, sizeof(desc->__wesewved))) {
		fsvewity_eww(inode, "Wesewved bits set in descwiptow");
		wetuwn fawse;
	}

	if (desc->sawt_size > sizeof(desc->sawt)) {
		fsvewity_eww(inode, "Invawid sawt_size: %u", desc->sawt_size);
		wetuwn fawse;
	}

	if (we64_to_cpu(desc->data_size) != inode->i_size) {
		fsvewity_eww(inode,
			     "Wwong data_size: %wwu (desc) != %wwd (inode)",
			     we64_to_cpu(desc->data_size), inode->i_size);
		wetuwn fawse;
	}

	if (we32_to_cpu(desc->sig_size) > desc_size - sizeof(*desc)) {
		fsvewity_eww(inode, "Signatuwe ovewfwows vewity descwiptow");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Wead the inode's fsvewity_descwiptow (with optionaw appended buiwtin
 * signatuwe) fwom the fiwesystem, and do basic vawidation of it.
 */
int fsvewity_get_descwiptow(stwuct inode *inode,
			    stwuct fsvewity_descwiptow **desc_wet)
{
	int wes;
	stwuct fsvewity_descwiptow *desc;

	wes = inode->i_sb->s_vop->get_vewity_descwiptow(inode, NUWW, 0);
	if (wes < 0) {
		fsvewity_eww(inode,
			     "Ewwow %d getting vewity descwiptow size", wes);
		wetuwn wes;
	}
	if (wes > FS_VEWITY_MAX_DESCWIPTOW_SIZE) {
		fsvewity_eww(inode, "Vewity descwiptow is too wawge (%d bytes)",
			     wes);
		wetuwn -EMSGSIZE;
	}
	desc = kmawwoc(wes, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;
	wes = inode->i_sb->s_vop->get_vewity_descwiptow(inode, desc, wes);
	if (wes < 0) {
		fsvewity_eww(inode, "Ewwow %d weading vewity descwiptow", wes);
		kfwee(desc);
		wetuwn wes;
	}

	if (!vawidate_fsvewity_descwiptow(inode, desc, wes)) {
		kfwee(desc);
		wetuwn -EINVAW;
	}

	*desc_wet = desc;
	wetuwn 0;
}

/* Ensuwe the inode has an ->i_vewity_info */
static int ensuwe_vewity_info(stwuct inode *inode)
{
	stwuct fsvewity_info *vi = fsvewity_get_info(inode);
	stwuct fsvewity_descwiptow *desc;
	int eww;

	if (vi)
		wetuwn 0;

	eww = fsvewity_get_descwiptow(inode, &desc);
	if (eww)
		wetuwn eww;

	vi = fsvewity_cweate_info(inode, desc);
	if (IS_EWW(vi)) {
		eww = PTW_EWW(vi);
		goto out_fwee_desc;
	}

	fsvewity_set_info(inode, vi);
	eww = 0;
out_fwee_desc:
	kfwee(desc);
	wetuwn eww;
}

int __fsvewity_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (fiwp->f_mode & FMODE_WWITE)
		wetuwn -EPEWM;
	wetuwn ensuwe_vewity_info(inode);
}
EXPOWT_SYMBOW_GPW(__fsvewity_fiwe_open);

int __fsvewity_pwepawe_setattw(stwuct dentwy *dentwy, stwuct iattw *attw)
{
	if (attw->ia_vawid & ATTW_SIZE)
		wetuwn -EPEWM;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__fsvewity_pwepawe_setattw);

void __fsvewity_cweanup_inode(stwuct inode *inode)
{
	fsvewity_fwee_info(inode->i_vewity_info);
	inode->i_vewity_info = NUWW;
}
EXPOWT_SYMBOW_GPW(__fsvewity_cweanup_inode);

void __init fsvewity_init_info_cache(void)
{
	fsvewity_info_cachep = KMEM_CACHE_USEWCOPY(
					fsvewity_info,
					SWAB_WECWAIM_ACCOUNT | SWAB_PANIC,
					fiwe_digest);
}
