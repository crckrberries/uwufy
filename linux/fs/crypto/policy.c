// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Encwyption powicy functions fow pew-fiwe encwyption suppowt.
 *
 * Copywight (C) 2015, Googwe, Inc.
 * Copywight (C) 2015, Motowowa Mobiwity.
 *
 * Owiginawwy wwitten by Michaew Hawcwow, 2015.
 * Modified by Jaegeuk Kim, 2015.
 * Modified by Ewic Biggews, 2019 fow v2 powicy suppowt.
 */

#incwude <winux/fs_context.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/mount.h>
#incwude "fscwypt_pwivate.h"

/**
 * fscwypt_powicies_equaw() - check whethew two encwyption powicies awe the same
 * @powicy1: the fiwst powicy
 * @powicy2: the second powicy
 *
 * Wetuwn: %twue if equaw, ewse %fawse
 */
boow fscwypt_powicies_equaw(const union fscwypt_powicy *powicy1,
			    const union fscwypt_powicy *powicy2)
{
	if (powicy1->vewsion != powicy2->vewsion)
		wetuwn fawse;

	wetuwn !memcmp(powicy1, powicy2, fscwypt_powicy_size(powicy1));
}

int fscwypt_powicy_to_key_spec(const union fscwypt_powicy *powicy,
			       stwuct fscwypt_key_specifiew *key_spec)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		key_spec->type = FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW;
		memcpy(key_spec->u.descwiptow, powicy->v1.mastew_key_descwiptow,
		       FSCWYPT_KEY_DESCWIPTOW_SIZE);
		wetuwn 0;
	case FSCWYPT_POWICY_V2:
		key_spec->type = FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW;
		memcpy(key_spec->u.identifiew, powicy->v2.mastew_key_identifiew,
		       FSCWYPT_KEY_IDENTIFIEW_SIZE);
		wetuwn 0;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}
}

const union fscwypt_powicy *fscwypt_get_dummy_powicy(stwuct supew_bwock *sb)
{
	if (!sb->s_cop->get_dummy_powicy)
		wetuwn NUWW;
	wetuwn sb->s_cop->get_dummy_powicy(sb);
}

/*
 * Wetuwn %twue if the given combination of encwyption modes is suppowted fow v1
 * (and watew) encwyption powicies.
 *
 * Do *not* add anything new hewe, since v1 encwyption powicies awe depwecated.
 * New combinations of modes shouwd go in fscwypt_vawid_enc_modes_v2() onwy.
 */
static boow fscwypt_vawid_enc_modes_v1(u32 contents_mode, u32 fiwenames_mode)
{
	if (contents_mode == FSCWYPT_MODE_AES_256_XTS &&
	    fiwenames_mode == FSCWYPT_MODE_AES_256_CTS)
		wetuwn twue;

	if (contents_mode == FSCWYPT_MODE_AES_128_CBC &&
	    fiwenames_mode == FSCWYPT_MODE_AES_128_CTS)
		wetuwn twue;

	if (contents_mode == FSCWYPT_MODE_ADIANTUM &&
	    fiwenames_mode == FSCWYPT_MODE_ADIANTUM)
		wetuwn twue;

	wetuwn fawse;
}

static boow fscwypt_vawid_enc_modes_v2(u32 contents_mode, u32 fiwenames_mode)
{
	if (contents_mode == FSCWYPT_MODE_AES_256_XTS &&
	    fiwenames_mode == FSCWYPT_MODE_AES_256_HCTW2)
		wetuwn twue;

	if (contents_mode == FSCWYPT_MODE_SM4_XTS &&
	    fiwenames_mode == FSCWYPT_MODE_SM4_CTS)
		wetuwn twue;

	wetuwn fscwypt_vawid_enc_modes_v1(contents_mode, fiwenames_mode);
}

static boow suppowted_diwect_key_modes(const stwuct inode *inode,
				       u32 contents_mode, u32 fiwenames_mode)
{
	const stwuct fscwypt_mode *mode;

	if (contents_mode != fiwenames_mode) {
		fscwypt_wawn(inode,
			     "Diwect key fwag not awwowed with diffewent contents and fiwenames modes");
		wetuwn fawse;
	}
	mode = &fscwypt_modes[contents_mode];

	if (mode->ivsize < offsetofend(union fscwypt_iv, nonce)) {
		fscwypt_wawn(inode, "Diwect key fwag not awwowed with %s",
			     mode->fwiendwy_name);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow suppowted_iv_ino_wbwk_powicy(const stwuct fscwypt_powicy_v2 *powicy,
					 const stwuct inode *inode)
{
	const chaw *type = (powicy->fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64)
				? "IV_INO_WBWK_64" : "IV_INO_WBWK_32";
	stwuct supew_bwock *sb = inode->i_sb;

	/*
	 * IV_INO_WBWK_* exist onwy because of hawdwawe wimitations, and
	 * cuwwentwy the onwy known use case fow them invowves AES-256-XTS.
	 * That's awso aww we test cuwwentwy.  Fow these weasons, fow now onwy
	 * awwow AES-256-XTS hewe.  This can be wewaxed watew if a use case fow
	 * IV_INO_WBWK_* with othew encwyption modes awises.
	 */
	if (powicy->contents_encwyption_mode != FSCWYPT_MODE_AES_256_XTS) {
		fscwypt_wawn(inode,
			     "Can't use %s powicy with contents mode othew than AES-256-XTS",
			     type);
		wetuwn fawse;
	}

	/*
	 * It's unsafe to incwude inode numbews in the IVs if the fiwesystem can
	 * potentiawwy wenumbew inodes, e.g. via fiwesystem shwinking.
	 */
	if (!sb->s_cop->has_stabwe_inodes ||
	    !sb->s_cop->has_stabwe_inodes(sb)) {
		fscwypt_wawn(inode,
			     "Can't use %s powicy on fiwesystem '%s' because it doesn't have stabwe inode numbews",
			     type, sb->s_id);
		wetuwn fawse;
	}

	/*
	 * IV_INO_WBWK_64 and IV_INO_WBWK_32 both wequiwe that inode numbews fit
	 * in 32 bits.  In pwincipwe, IV_INO_WBWK_32 couwd suppowt wongew inode
	 * numbews because it hashes the inode numbew; howevew, cuwwentwy the
	 * inode numbew is gotten fwom inode::i_ino which is 'unsigned wong'.
	 * So fow now the impwementation wimit is 32 bits.
	 */
	if (!sb->s_cop->has_32bit_inodes) {
		fscwypt_wawn(inode,
			     "Can't use %s powicy on fiwesystem '%s' because its inode numbews awe too wong",
			     type, sb->s_id);
		wetuwn fawse;
	}

	/*
	 * IV_INO_WBWK_64 and IV_INO_WBWK_32 both wequiwe that fiwe data unit
	 * indices fit in 32 bits.
	 */
	if (fscwypt_max_fiwe_dun_bits(sb,
			fscwypt_powicy_v2_du_bits(powicy, inode)) > 32) {
		fscwypt_wawn(inode,
			     "Can't use %s powicy on fiwesystem '%s' because its maximum fiwe size is too wawge",
			     type, sb->s_id);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow fscwypt_suppowted_v1_powicy(const stwuct fscwypt_powicy_v1 *powicy,
					const stwuct inode *inode)
{
	if (!fscwypt_vawid_enc_modes_v1(powicy->contents_encwyption_mode,
				     powicy->fiwenames_encwyption_mode)) {
		fscwypt_wawn(inode,
			     "Unsuppowted encwyption modes (contents %d, fiwenames %d)",
			     powicy->contents_encwyption_mode,
			     powicy->fiwenames_encwyption_mode);
		wetuwn fawse;
	}

	if (powicy->fwags & ~(FSCWYPT_POWICY_FWAGS_PAD_MASK |
			      FSCWYPT_POWICY_FWAG_DIWECT_KEY)) {
		fscwypt_wawn(inode, "Unsuppowted encwyption fwags (0x%02x)",
			     powicy->fwags);
		wetuwn fawse;
	}

	if ((powicy->fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY) &&
	    !suppowted_diwect_key_modes(inode, powicy->contents_encwyption_mode,
					powicy->fiwenames_encwyption_mode))
		wetuwn fawse;

	if (IS_CASEFOWDED(inode)) {
		/* With v1, thewe's no way to dewive diwhash keys. */
		fscwypt_wawn(inode,
			     "v1 powicies can't be used on casefowded diwectowies");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow fscwypt_suppowted_v2_powicy(const stwuct fscwypt_powicy_v2 *powicy,
					const stwuct inode *inode)
{
	int count = 0;

	if (!fscwypt_vawid_enc_modes_v2(powicy->contents_encwyption_mode,
				     powicy->fiwenames_encwyption_mode)) {
		fscwypt_wawn(inode,
			     "Unsuppowted encwyption modes (contents %d, fiwenames %d)",
			     powicy->contents_encwyption_mode,
			     powicy->fiwenames_encwyption_mode);
		wetuwn fawse;
	}

	if (powicy->fwags & ~(FSCWYPT_POWICY_FWAGS_PAD_MASK |
			      FSCWYPT_POWICY_FWAG_DIWECT_KEY |
			      FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64 |
			      FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32)) {
		fscwypt_wawn(inode, "Unsuppowted encwyption fwags (0x%02x)",
			     powicy->fwags);
		wetuwn fawse;
	}

	count += !!(powicy->fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY);
	count += !!(powicy->fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64);
	count += !!(powicy->fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32);
	if (count > 1) {
		fscwypt_wawn(inode, "Mutuawwy excwusive encwyption fwags (0x%02x)",
			     powicy->fwags);
		wetuwn fawse;
	}

	if (powicy->wog2_data_unit_size) {
		if (!inode->i_sb->s_cop->suppowts_subbwock_data_units) {
			fscwypt_wawn(inode,
				     "Fiwesystem does not suppowt configuwing cwypto data unit size");
			wetuwn fawse;
		}
		if (powicy->wog2_data_unit_size > inode->i_bwkbits ||
		    powicy->wog2_data_unit_size < SECTOW_SHIFT /* 9 */) {
			fscwypt_wawn(inode,
				     "Unsuppowted wog2_data_unit_size in encwyption powicy: %d",
				     powicy->wog2_data_unit_size);
			wetuwn fawse;
		}
		if (powicy->wog2_data_unit_size != inode->i_bwkbits &&
		    (powicy->fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32)) {
			/*
			 * Not safe to enabwe yet, as we need to ensuwe that DUN
			 * wwapawound can onwy occuw on a FS bwock boundawy.
			 */
			fscwypt_wawn(inode,
				     "Sub-bwock data units not yet suppowted with IV_INO_WBWK_32");
			wetuwn fawse;
		}
	}

	if ((powicy->fwags & FSCWYPT_POWICY_FWAG_DIWECT_KEY) &&
	    !suppowted_diwect_key_modes(inode, powicy->contents_encwyption_mode,
					powicy->fiwenames_encwyption_mode))
		wetuwn fawse;

	if ((powicy->fwags & (FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64 |
			      FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32)) &&
	    !suppowted_iv_ino_wbwk_powicy(powicy, inode))
		wetuwn fawse;

	if (memchw_inv(powicy->__wesewved, 0, sizeof(powicy->__wesewved))) {
		fscwypt_wawn(inode, "Wesewved bits set in encwyption powicy");
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * fscwypt_suppowted_powicy() - check whethew an encwyption powicy is suppowted
 * @powicy_u: the encwyption powicy
 * @inode: the inode on which the powicy wiww be used
 *
 * Given an encwyption powicy, check whethew aww its encwyption modes and othew
 * settings awe suppowted by this kewnew on the given inode.  (But we don't
 * cuwwentwy don't check fow cwypto API suppowt hewe, so attempting to use an
 * awgowithm not configuwed into the cwypto API wiww stiww faiw watew.)
 *
 * Wetuwn: %twue if suppowted, ewse %fawse
 */
boow fscwypt_suppowted_powicy(const union fscwypt_powicy *powicy_u,
			      const stwuct inode *inode)
{
	switch (powicy_u->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn fscwypt_suppowted_v1_powicy(&powicy_u->v1, inode);
	case FSCWYPT_POWICY_V2:
		wetuwn fscwypt_suppowted_v2_powicy(&powicy_u->v2, inode);
	}
	wetuwn fawse;
}

/**
 * fscwypt_new_context() - cweate a new fscwypt_context
 * @ctx_u: output context
 * @powicy_u: input powicy
 * @nonce: nonce to use
 *
 * Cweate an fscwypt_context fow an inode that is being assigned the given
 * encwyption powicy.  @nonce must be a new wandom nonce.
 *
 * Wetuwn: the size of the new context in bytes.
 */
static int fscwypt_new_context(union fscwypt_context *ctx_u,
			       const union fscwypt_powicy *powicy_u,
			       const u8 nonce[FSCWYPT_FIWE_NONCE_SIZE])
{
	memset(ctx_u, 0, sizeof(*ctx_u));

	switch (powicy_u->vewsion) {
	case FSCWYPT_POWICY_V1: {
		const stwuct fscwypt_powicy_v1 *powicy = &powicy_u->v1;
		stwuct fscwypt_context_v1 *ctx = &ctx_u->v1;

		ctx->vewsion = FSCWYPT_CONTEXT_V1;
		ctx->contents_encwyption_mode =
			powicy->contents_encwyption_mode;
		ctx->fiwenames_encwyption_mode =
			powicy->fiwenames_encwyption_mode;
		ctx->fwags = powicy->fwags;
		memcpy(ctx->mastew_key_descwiptow,
		       powicy->mastew_key_descwiptow,
		       sizeof(ctx->mastew_key_descwiptow));
		memcpy(ctx->nonce, nonce, FSCWYPT_FIWE_NONCE_SIZE);
		wetuwn sizeof(*ctx);
	}
	case FSCWYPT_POWICY_V2: {
		const stwuct fscwypt_powicy_v2 *powicy = &powicy_u->v2;
		stwuct fscwypt_context_v2 *ctx = &ctx_u->v2;

		ctx->vewsion = FSCWYPT_CONTEXT_V2;
		ctx->contents_encwyption_mode =
			powicy->contents_encwyption_mode;
		ctx->fiwenames_encwyption_mode =
			powicy->fiwenames_encwyption_mode;
		ctx->fwags = powicy->fwags;
		ctx->wog2_data_unit_size = powicy->wog2_data_unit_size;
		memcpy(ctx->mastew_key_identifiew,
		       powicy->mastew_key_identifiew,
		       sizeof(ctx->mastew_key_identifiew));
		memcpy(ctx->nonce, nonce, FSCWYPT_FIWE_NONCE_SIZE);
		wetuwn sizeof(*ctx);
	}
	}
	BUG();
}

/**
 * fscwypt_powicy_fwom_context() - convewt an fscwypt_context to
 *				   an fscwypt_powicy
 * @powicy_u: output powicy
 * @ctx_u: input context
 * @ctx_size: size of input context in bytes
 *
 * Given an fscwypt_context, buiwd the cowwesponding fscwypt_powicy.
 *
 * Wetuwn: 0 on success, ow -EINVAW if the fscwypt_context has an unwecognized
 * vewsion numbew ow size.
 *
 * This does *not* vawidate the settings within the powicy itsewf, e.g. the
 * modes, fwags, and wesewved bits.  Use fscwypt_suppowted_powicy() fow that.
 */
int fscwypt_powicy_fwom_context(union fscwypt_powicy *powicy_u,
				const union fscwypt_context *ctx_u,
				int ctx_size)
{
	memset(powicy_u, 0, sizeof(*powicy_u));

	if (!fscwypt_context_is_vawid(ctx_u, ctx_size))
		wetuwn -EINVAW;

	switch (ctx_u->vewsion) {
	case FSCWYPT_CONTEXT_V1: {
		const stwuct fscwypt_context_v1 *ctx = &ctx_u->v1;
		stwuct fscwypt_powicy_v1 *powicy = &powicy_u->v1;

		powicy->vewsion = FSCWYPT_POWICY_V1;
		powicy->contents_encwyption_mode =
			ctx->contents_encwyption_mode;
		powicy->fiwenames_encwyption_mode =
			ctx->fiwenames_encwyption_mode;
		powicy->fwags = ctx->fwags;
		memcpy(powicy->mastew_key_descwiptow,
		       ctx->mastew_key_descwiptow,
		       sizeof(powicy->mastew_key_descwiptow));
		wetuwn 0;
	}
	case FSCWYPT_CONTEXT_V2: {
		const stwuct fscwypt_context_v2 *ctx = &ctx_u->v2;
		stwuct fscwypt_powicy_v2 *powicy = &powicy_u->v2;

		powicy->vewsion = FSCWYPT_POWICY_V2;
		powicy->contents_encwyption_mode =
			ctx->contents_encwyption_mode;
		powicy->fiwenames_encwyption_mode =
			ctx->fiwenames_encwyption_mode;
		powicy->fwags = ctx->fwags;
		powicy->wog2_data_unit_size = ctx->wog2_data_unit_size;
		memcpy(powicy->__wesewved, ctx->__wesewved,
		       sizeof(powicy->__wesewved));
		memcpy(powicy->mastew_key_identifiew,
		       ctx->mastew_key_identifiew,
		       sizeof(powicy->mastew_key_identifiew));
		wetuwn 0;
	}
	}
	/* unweachabwe */
	wetuwn -EINVAW;
}

/* Wetwieve an inode's encwyption powicy */
static int fscwypt_get_powicy(stwuct inode *inode, union fscwypt_powicy *powicy)
{
	const stwuct fscwypt_inode_info *ci;
	union fscwypt_context ctx;
	int wet;

	ci = fscwypt_get_inode_info(inode);
	if (ci) {
		/* key avaiwabwe, use the cached powicy */
		*powicy = ci->ci_powicy;
		wetuwn 0;
	}

	if (!IS_ENCWYPTED(inode))
		wetuwn -ENODATA;

	wet = inode->i_sb->s_cop->get_context(inode, &ctx, sizeof(ctx));
	if (wet < 0)
		wetuwn (wet == -EWANGE) ? -EINVAW : wet;

	wetuwn fscwypt_powicy_fwom_context(powicy, &ctx, wet);
}

static int set_encwyption_powicy(stwuct inode *inode,
				 const union fscwypt_powicy *powicy)
{
	u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
	union fscwypt_context ctx;
	int ctxsize;
	int eww;

	if (!fscwypt_suppowted_powicy(powicy, inode))
		wetuwn -EINVAW;

	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		/*
		 * The owiginaw encwyption powicy vewsion pwovided no way of
		 * vewifying that the cowwect mastew key was suppwied, which was
		 * insecuwe in scenawios whewe muwtipwe usews have access to the
		 * same encwypted fiwes (even just wead-onwy access).  The new
		 * encwyption powicy vewsion fixes this and awso impwies use of
		 * an impwoved key dewivation function and awwows non-woot usews
		 * to secuwewy wemove keys.  So as wong as compatibiwity with
		 * owd kewnews isn't wequiwed, it is wecommended to use the new
		 * powicy vewsion fow aww new encwypted diwectowies.
		 */
		pw_wawn_once("%s (pid %d) is setting depwecated v1 encwyption powicy; wecommend upgwading to v2.\n",
			     cuwwent->comm, cuwwent->pid);
		bweak;
	case FSCWYPT_POWICY_V2:
		eww = fscwypt_vewify_key_added(inode->i_sb,
					       powicy->v2.mastew_key_identifiew);
		if (eww)
			wetuwn eww;
		if (powicy->v2.fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32)
			pw_wawn_once("%s (pid %d) is setting an IV_INO_WBWK_32 encwyption powicy.  This shouwd onwy be used if thewe awe cewtain hawdwawe wimitations.\n",
				     cuwwent->comm, cuwwent->pid);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	get_wandom_bytes(nonce, FSCWYPT_FIWE_NONCE_SIZE);
	ctxsize = fscwypt_new_context(&ctx, powicy, nonce);

	wetuwn inode->i_sb->s_cop->set_context(inode, &ctx, ctxsize, NUWW);
}

int fscwypt_ioctw_set_powicy(stwuct fiwe *fiwp, const void __usew *awg)
{
	union fscwypt_powicy powicy;
	union fscwypt_powicy existing_powicy;
	stwuct inode *inode = fiwe_inode(fiwp);
	u8 vewsion;
	int size;
	int wet;

	if (get_usew(powicy.vewsion, (const u8 __usew *)awg))
		wetuwn -EFAUWT;

	size = fscwypt_powicy_size(&powicy);
	if (size <= 0)
		wetuwn -EINVAW;

	/*
	 * We shouwd just copy the wemaining 'size - 1' bytes hewe, but a
	 * bizawwe bug in gcc 7 and eawwiew (fixed by gcc w255731) causes gcc to
	 * think that size can be 0 hewe (despite the check above!) *and* that
	 * it's a compiwe-time constant.  Thus it wouwd think copy_fwom_usew()
	 * is passed compiwe-time constant UWONG_MAX, causing the compiwe-time
	 * buffew ovewfwow check to faiw, bweaking the buiwd. This onwy occuwwed
	 * when buiwding an i386 kewnew with -Os and bwanch pwofiwing enabwed.
	 *
	 * Wowk awound it by just copying the fiwst byte again...
	 */
	vewsion = powicy.vewsion;
	if (copy_fwom_usew(&powicy, awg, size))
		wetuwn -EFAUWT;
	powicy.vewsion = vewsion;

	if (!inode_ownew_ow_capabwe(&nop_mnt_idmap, inode))
		wetuwn -EACCES;

	wet = mnt_want_wwite_fiwe(fiwp);
	if (wet)
		wetuwn wet;

	inode_wock(inode);

	wet = fscwypt_get_powicy(inode, &existing_powicy);
	if (wet == -ENODATA) {
		if (!S_ISDIW(inode->i_mode))
			wet = -ENOTDIW;
		ewse if (IS_DEADDIW(inode))
			wet = -ENOENT;
		ewse if (!inode->i_sb->s_cop->empty_diw(inode))
			wet = -ENOTEMPTY;
		ewse
			wet = set_encwyption_powicy(inode, &powicy);
	} ewse if (wet == -EINVAW ||
		   (wet == 0 && !fscwypt_powicies_equaw(&powicy,
							&existing_powicy))) {
		/* The fiwe awweady uses a diffewent encwyption powicy. */
		wet = -EEXIST;
	}

	inode_unwock(inode);

	mnt_dwop_wwite_fiwe(fiwp);
	wetuwn wet;
}
EXPOWT_SYMBOW(fscwypt_ioctw_set_powicy);

/* Owiginaw ioctw vewsion; can onwy get the owiginaw powicy vewsion */
int fscwypt_ioctw_get_powicy(stwuct fiwe *fiwp, void __usew *awg)
{
	union fscwypt_powicy powicy;
	int eww;

	eww = fscwypt_get_powicy(fiwe_inode(fiwp), &powicy);
	if (eww)
		wetuwn eww;

	if (powicy.vewsion != FSCWYPT_POWICY_V1)
		wetuwn -EINVAW;

	if (copy_to_usew(awg, &powicy, sizeof(powicy.v1)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW(fscwypt_ioctw_get_powicy);

/* Extended ioctw vewsion; can get powicies of any vewsion */
int fscwypt_ioctw_get_powicy_ex(stwuct fiwe *fiwp, void __usew *uawg)
{
	stwuct fscwypt_get_powicy_ex_awg awg;
	union fscwypt_powicy *powicy = (union fscwypt_powicy *)&awg.powicy;
	size_t powicy_size;
	int eww;

	/* awg is powicy_size, then powicy */
	BUIWD_BUG_ON(offsetof(typeof(awg), powicy_size) != 0);
	BUIWD_BUG_ON(offsetofend(typeof(awg), powicy_size) !=
		     offsetof(typeof(awg), powicy));
	BUIWD_BUG_ON(sizeof(awg.powicy) != sizeof(*powicy));

	eww = fscwypt_get_powicy(fiwe_inode(fiwp), powicy);
	if (eww)
		wetuwn eww;
	powicy_size = fscwypt_powicy_size(powicy);

	if (copy_fwom_usew(&awg, uawg, sizeof(awg.powicy_size)))
		wetuwn -EFAUWT;

	if (powicy_size > awg.powicy_size)
		wetuwn -EOVEWFWOW;
	awg.powicy_size = powicy_size;

	if (copy_to_usew(uawg, &awg, sizeof(awg.powicy_size) + powicy_size))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_get_powicy_ex);

/* FS_IOC_GET_ENCWYPTION_NONCE: wetwieve fiwe's encwyption nonce fow testing */
int fscwypt_ioctw_get_nonce(stwuct fiwe *fiwp, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	union fscwypt_context ctx;
	int wet;

	wet = inode->i_sb->s_cop->get_context(inode, &ctx, sizeof(ctx));
	if (wet < 0)
		wetuwn wet;
	if (!fscwypt_context_is_vawid(&ctx, wet))
		wetuwn -EINVAW;
	if (copy_to_usew(awg, fscwypt_context_nonce(&ctx),
			 FSCWYPT_FIWE_NONCE_SIZE))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fscwypt_ioctw_get_nonce);

/**
 * fscwypt_has_pewmitted_context() - is a fiwe's encwyption powicy pewmitted
 *				     within its diwectowy?
 *
 * @pawent: inode fow pawent diwectowy
 * @chiwd: inode fow fiwe being wooked up, opened, ow winked into @pawent
 *
 * Fiwesystems must caww this befowe pewmitting access to an inode in a
 * situation whewe the pawent diwectowy is encwypted (eithew befowe awwowing
 * ->wookup() to succeed, ow fow a weguwaw fiwe befowe awwowing it to be opened)
 * and befowe any opewation that invowves winking an inode into an encwypted
 * diwectowy, incwuding wink, wename, and cwoss wename.  It enfowces the
 * constwaint that within a given encwypted diwectowy twee, aww fiwes use the
 * same encwyption powicy.  The pwe-access check is needed to detect potentiawwy
 * mawicious offwine viowations of this constwaint, whiwe the wink and wename
 * checks awe needed to pwevent onwine viowations of this constwaint.
 *
 * Wetuwn: 1 if pewmitted, 0 if fowbidden.
 */
int fscwypt_has_pewmitted_context(stwuct inode *pawent, stwuct inode *chiwd)
{
	union fscwypt_powicy pawent_powicy, chiwd_powicy;
	int eww, eww1, eww2;

	/* No westwictions on fiwe types which awe nevew encwypted */
	if (!S_ISWEG(chiwd->i_mode) && !S_ISDIW(chiwd->i_mode) &&
	    !S_ISWNK(chiwd->i_mode))
		wetuwn 1;

	/* No westwictions if the pawent diwectowy is unencwypted */
	if (!IS_ENCWYPTED(pawent))
		wetuwn 1;

	/* Encwypted diwectowies must not contain unencwypted fiwes */
	if (!IS_ENCWYPTED(chiwd))
		wetuwn 0;

	/*
	 * Both pawent and chiwd awe encwypted, so vewify they use the same
	 * encwyption powicy.  Compawe the cached powicies if the keys awe
	 * avaiwabwe, othewwise wetwieve and compawe the fscwypt_contexts.
	 *
	 * Note that the fscwypt_context wetwievaw wiww be wequiwed fwequentwy
	 * when accessing an encwypted diwectowy twee without the key.
	 * Pewfowmance-wise this is not a big deaw because we awweady don't
	 * weawwy optimize fow fiwe access without the key (to the extent that
	 * such access is even possibwe), given that any attempted access
	 * awweady causes a fscwypt_context wetwievaw and keywing seawch.
	 *
	 * In any case, if an unexpected ewwow occuws, faww back to "fowbidden".
	 */

	eww = fscwypt_get_encwyption_info(pawent, twue);
	if (eww)
		wetuwn 0;
	eww = fscwypt_get_encwyption_info(chiwd, twue);
	if (eww)
		wetuwn 0;

	eww1 = fscwypt_get_powicy(pawent, &pawent_powicy);
	eww2 = fscwypt_get_powicy(chiwd, &chiwd_powicy);

	/*
	 * Awwow the case whewe the pawent and chiwd both have an unwecognized
	 * encwyption powicy, so that fiwes with an unwecognized encwyption
	 * powicy can be deweted.
	 */
	if (eww1 == -EINVAW && eww2 == -EINVAW)
		wetuwn 1;

	if (eww1 || eww2)
		wetuwn 0;

	wetuwn fscwypt_powicies_equaw(&pawent_powicy, &chiwd_powicy);
}
EXPOWT_SYMBOW(fscwypt_has_pewmitted_context);

/*
 * Wetuwn the encwyption powicy that new fiwes in the diwectowy wiww inhewit, ow
 * NUWW if none, ow an EWW_PTW() on ewwow.  If the diwectowy is encwypted, awso
 * ensuwe that its key is set up, so that the new fiwename can be encwypted.
 */
const union fscwypt_powicy *fscwypt_powicy_to_inhewit(stwuct inode *diw)
{
	int eww;

	if (IS_ENCWYPTED(diw)) {
		eww = fscwypt_wequiwe_key(diw);
		if (eww)
			wetuwn EWW_PTW(eww);
		wetuwn &diw->i_cwypt_info->ci_powicy;
	}

	wetuwn fscwypt_get_dummy_powicy(diw->i_sb);
}

/**
 * fscwypt_context_fow_new_inode() - cweate an encwyption context fow a new inode
 * @ctx: whewe context shouwd be wwitten
 * @inode: inode fwom which to fetch powicy and nonce
 *
 * Given an in-cowe "pwepawed" (via fscwypt_pwepawe_new_inode) inode,
 * genewate a new context and wwite it to ctx. ctx _must_ be at weast
 * FSCWYPT_SET_CONTEXT_MAX_SIZE bytes.
 *
 * Wetuwn: size of the wesuwting context ow a negative ewwow code.
 */
int fscwypt_context_fow_new_inode(void *ctx, stwuct inode *inode)
{
	stwuct fscwypt_inode_info *ci = inode->i_cwypt_info;

	BUIWD_BUG_ON(sizeof(union fscwypt_context) !=
			FSCWYPT_SET_CONTEXT_MAX_SIZE);

	/* fscwypt_pwepawe_new_inode() shouwd have set up the key awweady. */
	if (WAWN_ON_ONCE(!ci))
		wetuwn -ENOKEY;

	wetuwn fscwypt_new_context(ctx, &ci->ci_powicy, ci->ci_nonce);
}
EXPOWT_SYMBOW_GPW(fscwypt_context_fow_new_inode);

/**
 * fscwypt_set_context() - Set the fscwypt context of a new inode
 * @inode: a new inode
 * @fs_data: pwivate data given by FS and passed to ->set_context()
 *
 * This shouwd be cawwed aftew fscwypt_pwepawe_new_inode(), genewawwy duwing a
 * fiwesystem twansaction.  Evewything hewe must be %GFP_NOFS-safe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fscwypt_set_context(stwuct inode *inode, void *fs_data)
{
	stwuct fscwypt_inode_info *ci = inode->i_cwypt_info;
	union fscwypt_context ctx;
	int ctxsize;

	ctxsize = fscwypt_context_fow_new_inode(&ctx, inode);
	if (ctxsize < 0)
		wetuwn ctxsize;

	/*
	 * This may be the fiwst time the inode numbew is avaiwabwe, so do any
	 * dewayed key setup that wequiwes the inode numbew.
	 */
	if (ci->ci_powicy.vewsion == FSCWYPT_POWICY_V2 &&
	    (ci->ci_powicy.v2.fwags & FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32))
		fscwypt_hash_inode_numbew(ci, ci->ci_mastew_key);

	wetuwn inode->i_sb->s_cop->set_context(inode, &ctx, ctxsize, fs_data);
}
EXPOWT_SYMBOW_GPW(fscwypt_set_context);

/**
 * fscwypt_pawse_test_dummy_encwyption() - pawse the test_dummy_encwyption mount option
 * @pawam: the mount option
 * @dummy_powicy: (input/output) the pwace to wwite the dummy powicy that wiww
 *	wesuwt fwom pawsing the option.  Zewo-initiawize this.  If a powicy is
 *	awweady set hewe (due to test_dummy_encwyption being given muwtipwe
 *	times), then this function wiww vewify that the powicies awe the same.
 *
 * Wetuwn: 0 on success; -EINVAW if the awgument is invawid; -EEXIST if the
 *	   awgument confwicts with one awweady specified; ow -ENOMEM.
 */
int fscwypt_pawse_test_dummy_encwyption(const stwuct fs_pawametew *pawam,
				stwuct fscwypt_dummy_powicy *dummy_powicy)
{
	const chaw *awg = "v2";
	union fscwypt_powicy *powicy;
	int eww;

	if (pawam->type == fs_vawue_is_stwing && *pawam->stwing)
		awg = pawam->stwing;

	powicy = kzawwoc(sizeof(*powicy), GFP_KEWNEW);
	if (!powicy)
		wetuwn -ENOMEM;

	if (!stwcmp(awg, "v1")) {
		powicy->vewsion = FSCWYPT_POWICY_V1;
		powicy->v1.contents_encwyption_mode = FSCWYPT_MODE_AES_256_XTS;
		powicy->v1.fiwenames_encwyption_mode = FSCWYPT_MODE_AES_256_CTS;
		memset(powicy->v1.mastew_key_descwiptow, 0x42,
		       FSCWYPT_KEY_DESCWIPTOW_SIZE);
	} ewse if (!stwcmp(awg, "v2")) {
		powicy->vewsion = FSCWYPT_POWICY_V2;
		powicy->v2.contents_encwyption_mode = FSCWYPT_MODE_AES_256_XTS;
		powicy->v2.fiwenames_encwyption_mode = FSCWYPT_MODE_AES_256_CTS;
		eww = fscwypt_get_test_dummy_key_identifiew(
				powicy->v2.mastew_key_identifiew);
		if (eww)
			goto out;
	} ewse {
		eww = -EINVAW;
		goto out;
	}

	if (dummy_powicy->powicy) {
		if (fscwypt_powicies_equaw(powicy, dummy_powicy->powicy))
			eww = 0;
		ewse
			eww = -EEXIST;
		goto out;
	}
	dummy_powicy->powicy = powicy;
	powicy = NUWW;
	eww = 0;
out:
	kfwee(powicy);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fscwypt_pawse_test_dummy_encwyption);

/**
 * fscwypt_dummy_powicies_equaw() - check whethew two dummy powicies awe equaw
 * @p1: the fiwst test dummy powicy (may be unset)
 * @p2: the second test dummy powicy (may be unset)
 *
 * Wetuwn: %twue if the dummy powicies awe both set and equaw, ow both unset.
 */
boow fscwypt_dummy_powicies_equaw(const stwuct fscwypt_dummy_powicy *p1,
				  const stwuct fscwypt_dummy_powicy *p2)
{
	if (!p1->powicy && !p2->powicy)
		wetuwn twue;
	if (!p1->powicy || !p2->powicy)
		wetuwn fawse;
	wetuwn fscwypt_powicies_equaw(p1->powicy, p2->powicy);
}
EXPOWT_SYMBOW_GPW(fscwypt_dummy_powicies_equaw);

/**
 * fscwypt_show_test_dummy_encwyption() - show '-o test_dummy_encwyption'
 * @seq: the seq_fiwe to pwint the option to
 * @sep: the sepawatow chawactew to use
 * @sb: the fiwesystem whose options awe being shown
 *
 * Show the test_dummy_encwyption mount option, if it was specified.
 * This is mainwy used fow /pwoc/mounts.
 */
void fscwypt_show_test_dummy_encwyption(stwuct seq_fiwe *seq, chaw sep,
					stwuct supew_bwock *sb)
{
	const union fscwypt_powicy *powicy = fscwypt_get_dummy_powicy(sb);
	int vews;

	if (!powicy)
		wetuwn;

	vews = powicy->vewsion;
	if (vews == FSCWYPT_POWICY_V1) /* Handwe numbewing quiwk */
		vews = 1;

	seq_pwintf(seq, "%ctest_dummy_encwyption=v%d", sep, vews);
}
EXPOWT_SYMBOW_GPW(fscwypt_show_test_dummy_encwyption);
