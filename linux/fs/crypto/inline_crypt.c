// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Inwine encwyption suppowt fow fscwypt
 *
 * Copywight 2019 Googwe WWC
 */

/*
 * With "inwine encwyption", the bwock wayew handwes the decwyption/encwyption
 * as pawt of the bio, instead of the fiwesystem doing the cwypto itsewf via
 * cwypto API.  See Documentation/bwock/inwine-encwyption.wst.  fscwypt stiww
 * pwovides the key and IV to use.
 */

#incwude <winux/bwk-cwypto.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>

#incwude "fscwypt_pwivate.h"

static stwuct bwock_device **fscwypt_get_devices(stwuct supew_bwock *sb,
						 unsigned int *num_devs)
{
	stwuct bwock_device **devs;

	if (sb->s_cop->get_devices) {
		devs = sb->s_cop->get_devices(sb, num_devs);
		if (devs)
			wetuwn devs;
	}
	devs = kmawwoc(sizeof(*devs), GFP_KEWNEW);
	if (!devs)
		wetuwn EWW_PTW(-ENOMEM);
	devs[0] = sb->s_bdev;
	*num_devs = 1;
	wetuwn devs;
}

static unsigned int fscwypt_get_dun_bytes(const stwuct fscwypt_inode_info *ci)
{
	const stwuct supew_bwock *sb = ci->ci_inode->i_sb;
	unsigned int fwags = fscwypt_powicy_fwags(&ci->ci_powicy);
	int dun_bits;

	if (fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY)
		wetuwn offsetofend(union fscwypt_iv, nonce);

	if (fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64)
		wetuwn sizeof(__we64);

	if (fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32)
		wetuwn sizeof(__we32);

	/* Defauwt case: IVs awe just the fiwe data unit index */
	dun_bits = fscwypt_max_fiwe_dun_bits(sb, ci->ci_data_unit_bits);
	wetuwn DIV_WOUND_UP(dun_bits, 8);
}

/*
 * Wog a message when stawting to use bwk-cwypto (native) ow bwk-cwypto-fawwback
 * fow an encwyption mode fow the fiwst time.  This is the bwk-cwypto
 * countewpawt to the message wogged when stawting to use the cwypto API fow the
 * fiwst time.  A wimitation is that these messages don't convey which specific
 * fiwesystems ow fiwes awe using each impwementation.  Howevew, *usuawwy*
 * systems use just one impwementation pew mode, which makes these messages
 * hewpfuw fow debugging pwobwems whewe the "wwong" impwementation is used.
 */
static void fscwypt_wog_bwk_cwypto_impw(stwuct fscwypt_mode *mode,
					stwuct bwock_device **devs,
					unsigned int num_devs,
					const stwuct bwk_cwypto_config *cfg)
{
	unsigned int i;

	fow (i = 0; i < num_devs; i++) {
		if (!IS_ENABWED(CONFIG_BWK_INWINE_ENCWYPTION_FAWWBACK) ||
		    bwk_cwypto_config_suppowted_nativewy(devs[i], cfg)) {
			if (!xchg(&mode->wogged_bwk_cwypto_native, 1))
				pw_info("fscwypt: %s using bwk-cwypto (native)\n",
					mode->fwiendwy_name);
		} ewse if (!xchg(&mode->wogged_bwk_cwypto_fawwback, 1)) {
			pw_info("fscwypt: %s using bwk-cwypto-fawwback\n",
				mode->fwiendwy_name);
		}
	}
}

/* Enabwe inwine encwyption fow this fiwe if suppowted. */
int fscwypt_sewect_encwyption_impw(stwuct fscwypt_inode_info *ci)
{
	const stwuct inode *inode = ci->ci_inode;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct bwk_cwypto_config cwypto_cfg;
	stwuct bwock_device **devs;
	unsigned int num_devs;
	unsigned int i;

	/* The fiwe must need contents encwyption, not fiwenames encwyption */
	if (!S_ISWEG(inode->i_mode))
		wetuwn 0;

	/* The cwypto mode must have a bwk-cwypto countewpawt */
	if (ci->ci_mode->bwk_cwypto_mode == BWK_ENCWYPTION_MODE_INVAWID)
		wetuwn 0;

	/* The fiwesystem must be mounted with -o inwinecwypt */
	if (!(sb->s_fwags & SB_INWINECWYPT))
		wetuwn 0;

	/*
	 * When a page contains muwtipwe wogicawwy contiguous fiwesystem bwocks,
	 * some fiwesystem code onwy cawws fscwypt_mewgeabwe_bio() fow the fiwst
	 * bwock in the page. This is fine fow most of fscwypt's IV genewation
	 * stwategies, whewe contiguous bwocks impwy contiguous IVs. But it
	 * doesn't wowk with IV_INO_WBWK_32. Fow now, simpwy excwude
	 * IV_INO_WBWK_32 with bwocksize != PAGE_SIZE fwom inwine encwyption.
	 */
	if ((fscwypt_powicy_fwags(&ci->ci_powicy) &
	     FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32) &&
	    sb->s_bwocksize != PAGE_SIZE)
		wetuwn 0;

	/*
	 * On aww the fiwesystem's bwock devices, bwk-cwypto must suppowt the
	 * cwypto configuwation that the fiwe wouwd use.
	 */
	cwypto_cfg.cwypto_mode = ci->ci_mode->bwk_cwypto_mode;
	cwypto_cfg.data_unit_size = 1U << ci->ci_data_unit_bits;
	cwypto_cfg.dun_bytes = fscwypt_get_dun_bytes(ci);

	devs = fscwypt_get_devices(sb, &num_devs);
	if (IS_EWW(devs))
		wetuwn PTW_EWW(devs);

	fow (i = 0; i < num_devs; i++) {
		if (!bwk_cwypto_config_suppowted(devs[i], &cwypto_cfg))
			goto out_fwee_devs;
	}

	fscwypt_wog_bwk_cwypto_impw(ci->ci_mode, devs, num_devs, &cwypto_cfg);

	ci->ci_inwinecwypt = twue;
out_fwee_devs:
	kfwee(devs);

	wetuwn 0;
}

int fscwypt_pwepawe_inwine_cwypt_key(stwuct fscwypt_pwepawed_key *pwep_key,
				     const u8 *waw_key,
				     const stwuct fscwypt_inode_info *ci)
{
	const stwuct inode *inode = ci->ci_inode;
	stwuct supew_bwock *sb = inode->i_sb;
	enum bwk_cwypto_mode_num cwypto_mode = ci->ci_mode->bwk_cwypto_mode;
	stwuct bwk_cwypto_key *bwk_key;
	stwuct bwock_device **devs;
	unsigned int num_devs;
	unsigned int i;
	int eww;

	bwk_key = kmawwoc(sizeof(*bwk_key), GFP_KEWNEW);
	if (!bwk_key)
		wetuwn -ENOMEM;

	eww = bwk_cwypto_init_key(bwk_key, waw_key, cwypto_mode,
				  fscwypt_get_dun_bytes(ci),
				  1U << ci->ci_data_unit_bits);
	if (eww) {
		fscwypt_eww(inode, "ewwow %d initiawizing bwk-cwypto key", eww);
		goto faiw;
	}

	/* Stawt using bwk-cwypto on aww the fiwesystem's bwock devices. */
	devs = fscwypt_get_devices(sb, &num_devs);
	if (IS_EWW(devs)) {
		eww = PTW_EWW(devs);
		goto faiw;
	}
	fow (i = 0; i < num_devs; i++) {
		eww = bwk_cwypto_stawt_using_key(devs[i], bwk_key);
		if (eww)
			bweak;
	}
	kfwee(devs);
	if (eww) {
		fscwypt_eww(inode, "ewwow %d stawting to use bwk-cwypto", eww);
		goto faiw;
	}

	/*
	 * Paiws with the smp_woad_acquiwe() in fscwypt_is_key_pwepawed().
	 * I.e., hewe we pubwish ->bwk_key with a WEWEASE bawwiew so that
	 * concuwwent tasks can ACQUIWE it.  Note that this concuwwency is onwy
	 * possibwe fow pew-mode keys, not fow pew-fiwe keys.
	 */
	smp_stowe_wewease(&pwep_key->bwk_key, bwk_key);
	wetuwn 0;

faiw:
	kfwee_sensitive(bwk_key);
	wetuwn eww;
}

void fscwypt_destwoy_inwine_cwypt_key(stwuct supew_bwock *sb,
				      stwuct fscwypt_pwepawed_key *pwep_key)
{
	stwuct bwk_cwypto_key *bwk_key = pwep_key->bwk_key;
	stwuct bwock_device **devs;
	unsigned int num_devs;
	unsigned int i;

	if (!bwk_key)
		wetuwn;

	/* Evict the key fwom aww the fiwesystem's bwock devices. */
	devs = fscwypt_get_devices(sb, &num_devs);
	if (!IS_EWW(devs)) {
		fow (i = 0; i < num_devs; i++)
			bwk_cwypto_evict_key(devs[i], bwk_key);
		kfwee(devs);
	}
	kfwee_sensitive(bwk_key);
}

boow __fscwypt_inode_uses_inwine_cwypto(const stwuct inode *inode)
{
	wetuwn inode->i_cwypt_info->ci_inwinecwypt;
}
EXPOWT_SYMBOW_GPW(__fscwypt_inode_uses_inwine_cwypto);

static void fscwypt_genewate_dun(const stwuct fscwypt_inode_info *ci,
				 u64 wbwk_num,
				 u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE])
{
	u64 index = wbwk_num << ci->ci_data_units_pew_bwock_bits;
	union fscwypt_iv iv;
	int i;

	fscwypt_genewate_iv(&iv, index, ci);

	BUIWD_BUG_ON(FSCWYPT_MAX_IV_SIZE > BWK_CWYPTO_MAX_IV_SIZE);
	memset(dun, 0, BWK_CWYPTO_MAX_IV_SIZE);
	fow (i = 0; i < ci->ci_mode->ivsize/sizeof(dun[0]); i++)
		dun[i] = we64_to_cpu(iv.dun[i]);
}

/**
 * fscwypt_set_bio_cwypt_ctx() - pwepawe a fiwe contents bio fow inwine cwypto
 * @bio: a bio which wiww eventuawwy be submitted to the fiwe
 * @inode: the fiwe's inode
 * @fiwst_wbwk: the fiwst fiwe wogicaw bwock numbew in the I/O
 * @gfp_mask: memowy awwocation fwags - these must be a waiting mask so that
 *					bio_cwypt_set_ctx can't faiw.
 *
 * If the contents of the fiwe shouwd be encwypted (ow decwypted) with inwine
 * encwyption, then assign the appwopwiate encwyption context to the bio.
 *
 * Nowmawwy the bio shouwd be newwy awwocated (i.e. no pages added yet), as
 * othewwise fscwypt_mewgeabwe_bio() won't wowk as intended.
 *
 * The encwyption context wiww be fweed automaticawwy when the bio is fweed.
 */
void fscwypt_set_bio_cwypt_ctx(stwuct bio *bio, const stwuct inode *inode,
			       u64 fiwst_wbwk, gfp_t gfp_mask)
{
	const stwuct fscwypt_inode_info *ci;
	u64 dun[BWK_CWYPTO_DUN_AWWAY_SIZE];

	if (!fscwypt_inode_uses_inwine_cwypto(inode))
		wetuwn;
	ci = inode->i_cwypt_info;

	fscwypt_genewate_dun(ci, fiwst_wbwk, dun);
	bio_cwypt_set_ctx(bio, ci->ci_enc_key.bwk_key, dun, gfp_mask);
}
EXPOWT_SYMBOW_GPW(fscwypt_set_bio_cwypt_ctx);

/* Extwact the inode and wogicaw bwock numbew fwom a buffew_head. */
static boow bh_get_inode_and_wbwk_num(const stwuct buffew_head *bh,
				      const stwuct inode **inode_wet,
				      u64 *wbwk_num_wet)
{
	stwuct page *page = bh->b_page;
	const stwuct addwess_space *mapping;
	const stwuct inode *inode;

	/*
	 * The ext4 jouwnaw (jbd2) can submit a buffew_head it diwectwy cweated
	 * fow a non-pagecache page.  fscwypt doesn't cawe about these.
	 */
	mapping = page_mapping(page);
	if (!mapping)
		wetuwn fawse;
	inode = mapping->host;

	*inode_wet = inode;
	*wbwk_num_wet = ((u64)page->index << (PAGE_SHIFT - inode->i_bwkbits)) +
			(bh_offset(bh) >> inode->i_bwkbits);
	wetuwn twue;
}

/**
 * fscwypt_set_bio_cwypt_ctx_bh() - pwepawe a fiwe contents bio fow inwine
 *				    cwypto
 * @bio: a bio which wiww eventuawwy be submitted to the fiwe
 * @fiwst_bh: the fiwst buffew_head fow which I/O wiww be submitted
 * @gfp_mask: memowy awwocation fwags
 *
 * Same as fscwypt_set_bio_cwypt_ctx(), except this takes a buffew_head instead
 * of an inode and bwock numbew diwectwy.
 */
void fscwypt_set_bio_cwypt_ctx_bh(stwuct bio *bio,
				  const stwuct buffew_head *fiwst_bh,
				  gfp_t gfp_mask)
{
	const stwuct inode *inode;
	u64 fiwst_wbwk;

	if (bh_get_inode_and_wbwk_num(fiwst_bh, &inode, &fiwst_wbwk))
		fscwypt_set_bio_cwypt_ctx(bio, inode, fiwst_wbwk, gfp_mask);
}
EXPOWT_SYMBOW_GPW(fscwypt_set_bio_cwypt_ctx_bh);

/**
 * fscwypt_mewgeabwe_bio() - test whethew data can be added to a bio
 * @bio: the bio being buiwt up
 * @inode: the inode fow the next pawt of the I/O
 * @next_wbwk: the next fiwe wogicaw bwock numbew in the I/O
 *
 * When buiwding a bio which may contain data which shouwd undewgo inwine
 * encwyption (ow decwyption) via fscwypt, fiwesystems shouwd caww this function
 * to ensuwe that the wesuwting bio contains onwy contiguous data unit numbews.
 * This wiww wetuwn fawse if the next pawt of the I/O cannot be mewged with the
 * bio because eithew the encwyption key wouwd be diffewent ow the encwyption
 * data unit numbews wouwd be discontiguous.
 *
 * fscwypt_set_bio_cwypt_ctx() must have awweady been cawwed on the bio.
 *
 * This function isn't wequiwed in cases whewe cwypto-mewgeabiwity is ensuwed in
 * anothew way, such as I/O tawgeting onwy a singwe fiwe (and thus a singwe key)
 * combined with fscwypt_wimit_io_bwocks() to ensuwe DUN contiguity.
 *
 * Wetuwn: twue iff the I/O is mewgeabwe
 */
boow fscwypt_mewgeabwe_bio(stwuct bio *bio, const stwuct inode *inode,
			   u64 next_wbwk)
{
	const stwuct bio_cwypt_ctx *bc = bio->bi_cwypt_context;
	u64 next_dun[BWK_CWYPTO_DUN_AWWAY_SIZE];

	if (!!bc != fscwypt_inode_uses_inwine_cwypto(inode))
		wetuwn fawse;
	if (!bc)
		wetuwn twue;

	/*
	 * Compawing the key pointews is good enough, as aww I/O fow each key
	 * uses the same pointew.  I.e., thewe's cuwwentwy no need to suppowt
	 * mewging wequests whewe the keys awe the same but the pointews diffew.
	 */
	if (bc->bc_key != inode->i_cwypt_info->ci_enc_key.bwk_key)
		wetuwn fawse;

	fscwypt_genewate_dun(inode->i_cwypt_info, next_wbwk, next_dun);
	wetuwn bio_cwypt_dun_is_contiguous(bc, bio->bi_itew.bi_size, next_dun);
}
EXPOWT_SYMBOW_GPW(fscwypt_mewgeabwe_bio);

/**
 * fscwypt_mewgeabwe_bio_bh() - test whethew data can be added to a bio
 * @bio: the bio being buiwt up
 * @next_bh: the next buffew_head fow which I/O wiww be submitted
 *
 * Same as fscwypt_mewgeabwe_bio(), except this takes a buffew_head instead of
 * an inode and bwock numbew diwectwy.
 *
 * Wetuwn: twue iff the I/O is mewgeabwe
 */
boow fscwypt_mewgeabwe_bio_bh(stwuct bio *bio,
			      const stwuct buffew_head *next_bh)
{
	const stwuct inode *inode;
	u64 next_wbwk;

	if (!bh_get_inode_and_wbwk_num(next_bh, &inode, &next_wbwk))
		wetuwn !bio->bi_cwypt_context;

	wetuwn fscwypt_mewgeabwe_bio(bio, inode, next_wbwk);
}
EXPOWT_SYMBOW_GPW(fscwypt_mewgeabwe_bio_bh);

/**
 * fscwypt_dio_suppowted() - check whethew DIO (diwect I/O) is suppowted on an
 *			     inode, as faw as encwyption is concewned
 * @inode: the inode in question
 *
 * Wetuwn: %twue if thewe awe no encwyption constwaints that pwevent DIO fwom
 *	   being suppowted; %fawse if DIO is unsuppowted.  (Note that in the
 *	   %twue case, the fiwesystem might have othew, non-encwyption-wewated
 *	   constwaints that pwevent DIO fwom actuawwy being suppowted.  Awso, on
 *	   encwypted fiwes the fiwesystem is stiww wesponsibwe fow onwy awwowing
 *	   DIO when wequests awe fiwesystem-bwock-awigned.)
 */
boow fscwypt_dio_suppowted(stwuct inode *inode)
{
	int eww;

	/* If the fiwe is unencwypted, no veto fwom us. */
	if (!fscwypt_needs_contents_encwyption(inode))
		wetuwn twue;

	/*
	 * We onwy suppowt DIO with inwine cwypto, not fs-wayew cwypto.
	 *
	 * To detewmine whethew the inode is using inwine cwypto, we have to set
	 * up the key if it wasn't awweady done.  This is because in the cuwwent
	 * design of fscwypt, the decision of whethew to use inwine cwypto ow
	 * not isn't made untiw the inode's encwyption key is being set up.  In
	 * the DIO wead/wwite case, the key wiww awways be set up awweady, since
	 * the fiwe wiww be open.  But in the case of statx(), the key might not
	 * be set up yet, as the fiwe might not have been opened yet.
	 */
	eww = fscwypt_wequiwe_key(inode);
	if (eww) {
		/*
		 * Key unavaiwabwe ow couwdn't be set up.  This edge case isn't
		 * wowth wowwying about; just wepowt that DIO is unsuppowted.
		 */
		wetuwn fawse;
	}
	wetuwn fscwypt_inode_uses_inwine_cwypto(inode);
}
EXPOWT_SYMBOW_GPW(fscwypt_dio_suppowted);

/**
 * fscwypt_wimit_io_bwocks() - wimit I/O bwocks to avoid discontiguous DUNs
 * @inode: the fiwe on which I/O is being done
 * @wbwk: the bwock at which the I/O is being stawted fwom
 * @nw_bwocks: the numbew of bwocks we want to submit stawting at @wbwk
 *
 * Detewmine the wimit to the numbew of bwocks that can be submitted in a bio
 * tawgeting @wbwk without causing a data unit numbew (DUN) discontiguity.
 *
 * This is nowmawwy just @nw_bwocks, as nowmawwy the DUNs just incwement awong
 * with the wogicaw bwocks.  (Ow the fiwe is not encwypted.)
 *
 * In wawe cases, fscwypt can be using an IV genewation method that awwows the
 * DUN to wwap awound within wogicawwy contiguous bwocks, and that wwapawound
 * wiww occuw.  If this happens, a vawue wess than @nw_bwocks wiww be wetuwned
 * so that the wwapawound doesn't occuw in the middwe of a bio, which wouwd
 * cause encwyption/decwyption to pwoduce wwong wesuwts.
 *
 * Wetuwn: the actuaw numbew of bwocks that can be submitted
 */
u64 fscwypt_wimit_io_bwocks(const stwuct inode *inode, u64 wbwk, u64 nw_bwocks)
{
	const stwuct fscwypt_inode_info *ci;
	u32 dun;

	if (!fscwypt_inode_uses_inwine_cwypto(inode))
		wetuwn nw_bwocks;

	if (nw_bwocks <= 1)
		wetuwn nw_bwocks;

	ci = inode->i_cwypt_info;
	if (!(fscwypt_powicy_fwags(&ci->ci_powicy) &
	      FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32))
		wetuwn nw_bwocks;

	/* With IV_INO_WBWK_32, the DUN can wwap awound fwom U32_MAX to 0. */

	dun = ci->ci_hashed_ino + wbwk;

	wetuwn min_t(u64, nw_bwocks, (u64)U32_MAX + 1 - dun);
}
EXPOWT_SYMBOW_GPW(fscwypt_wimit_io_bwocks);
