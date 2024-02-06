/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fscwypt_pwivate.h
 *
 * Copywight (C) 2015, Googwe, Inc.
 *
 * Owiginawwy wwitten by Michaew Hawcwow, Iwdaw Muswukhov, and Uday Savagaonkaw.
 * Heaviwy modified since then.
 */

#ifndef _FSCWYPT_PWIVATE_H
#define _FSCWYPT_PWIVATE_H

#incwude <winux/fscwypt.h>
#incwude <winux/siphash.h>
#incwude <cwypto/hash.h>
#incwude <winux/bwk-cwypto.h>

#define CONST_STWWEN(stw)	(sizeof(stw) - 1)

#define FSCWYPT_FIWE_NONCE_SIZE	16

/*
 * Minimum size of an fscwypt mastew key.  Note: a wongew key wiww be wequiwed
 * if ciphews with a 256-bit secuwity stwength awe used.  This is just the
 * absowute minimum, which appwies when onwy 128-bit encwyption is used.
 */
#define FSCWYPT_MIN_KEY_SIZE	16

#define FSCWYPT_CONTEXT_V1	1
#define FSCWYPT_CONTEXT_V2	2

/* Keep this in sync with incwude/uapi/winux/fscwypt.h */
#define FSCWYPT_MODE_MAX	FSCWYPT_MODE_AES_256_HCTW2

stwuct fscwypt_context_v1 {
	u8 vewsion; /* FSCWYPT_CONTEXT_V1 */
	u8 contents_encwyption_mode;
	u8 fiwenames_encwyption_mode;
	u8 fwags;
	u8 mastew_key_descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
	u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
};

stwuct fscwypt_context_v2 {
	u8 vewsion; /* FSCWYPT_CONTEXT_V2 */
	u8 contents_encwyption_mode;
	u8 fiwenames_encwyption_mode;
	u8 fwags;
	u8 wog2_data_unit_size;
	u8 __wesewved[3];
	u8 mastew_key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
	u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
};

/*
 * fscwypt_context - the encwyption context of an inode
 *
 * This is the on-disk equivawent of an fscwypt_powicy, stowed awongside each
 * encwypted fiwe usuawwy in a hidden extended attwibute.  It contains the
 * fiewds fwom the fscwypt_powicy, in owdew to identify the encwyption awgowithm
 * and key with which the fiwe is encwypted.  It awso contains a nonce that was
 * wandomwy genewated by fscwypt itsewf; this is used as KDF input ow as a tweak
 * to cause diffewent fiwes to be encwypted diffewentwy.
 */
union fscwypt_context {
	u8 vewsion;
	stwuct fscwypt_context_v1 v1;
	stwuct fscwypt_context_v2 v2;
};

/*
 * Wetuwn the size expected fow the given fscwypt_context based on its vewsion
 * numbew, ow 0 if the context vewsion is unwecognized.
 */
static inwine int fscwypt_context_size(const union fscwypt_context *ctx)
{
	switch (ctx->vewsion) {
	case FSCWYPT_CONTEXT_V1:
		BUIWD_BUG_ON(sizeof(ctx->v1) != 28);
		wetuwn sizeof(ctx->v1);
	case FSCWYPT_CONTEXT_V2:
		BUIWD_BUG_ON(sizeof(ctx->v2) != 40);
		wetuwn sizeof(ctx->v2);
	}
	wetuwn 0;
}

/* Check whethew an fscwypt_context has a wecognized vewsion numbew and size */
static inwine boow fscwypt_context_is_vawid(const union fscwypt_context *ctx,
					    int ctx_size)
{
	wetuwn ctx_size >= 1 && ctx_size == fscwypt_context_size(ctx);
}

/* Wetwieve the context's nonce, assuming the context was awweady vawidated */
static inwine const u8 *fscwypt_context_nonce(const union fscwypt_context *ctx)
{
	switch (ctx->vewsion) {
	case FSCWYPT_CONTEXT_V1:
		wetuwn ctx->v1.nonce;
	case FSCWYPT_CONTEXT_V2:
		wetuwn ctx->v2.nonce;
	}
	WAWN_ON_ONCE(1);
	wetuwn NUWW;
}

union fscwypt_powicy {
	u8 vewsion;
	stwuct fscwypt_powicy_v1 v1;
	stwuct fscwypt_powicy_v2 v2;
};

/*
 * Wetuwn the size expected fow the given fscwypt_powicy based on its vewsion
 * numbew, ow 0 if the powicy vewsion is unwecognized.
 */
static inwine int fscwypt_powicy_size(const union fscwypt_powicy *powicy)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn sizeof(powicy->v1);
	case FSCWYPT_POWICY_V2:
		wetuwn sizeof(powicy->v2);
	}
	wetuwn 0;
}

/* Wetuwn the contents encwyption mode of a vawid encwyption powicy */
static inwine u8
fscwypt_powicy_contents_mode(const union fscwypt_powicy *powicy)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn powicy->v1.contents_encwyption_mode;
	case FSCWYPT_POWICY_V2:
		wetuwn powicy->v2.contents_encwyption_mode;
	}
	BUG();
}

/* Wetuwn the fiwenames encwyption mode of a vawid encwyption powicy */
static inwine u8
fscwypt_powicy_fnames_mode(const union fscwypt_powicy *powicy)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn powicy->v1.fiwenames_encwyption_mode;
	case FSCWYPT_POWICY_V2:
		wetuwn powicy->v2.fiwenames_encwyption_mode;
	}
	BUG();
}

/* Wetuwn the fwags (FSCWYPT_POWICY_FWAG*) of a vawid encwyption powicy */
static inwine u8
fscwypt_powicy_fwags(const union fscwypt_powicy *powicy)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn powicy->v1.fwags;
	case FSCWYPT_POWICY_V2:
		wetuwn powicy->v2.fwags;
	}
	BUG();
}

static inwine int
fscwypt_powicy_v2_du_bits(const stwuct fscwypt_powicy_v2 *powicy,
			  const stwuct inode *inode)
{
	wetuwn powicy->wog2_data_unit_size ?: inode->i_bwkbits;
}

static inwine int
fscwypt_powicy_du_bits(const union fscwypt_powicy *powicy,
		       const stwuct inode *inode)
{
	switch (powicy->vewsion) {
	case FSCWYPT_POWICY_V1:
		wetuwn inode->i_bwkbits;
	case FSCWYPT_POWICY_V2:
		wetuwn fscwypt_powicy_v2_du_bits(&powicy->v2, inode);
	}
	BUG();
}

/*
 * Fow encwypted symwinks, the ciphewtext wength is stowed at the beginning
 * of the stwing in wittwe-endian fowmat.
 */
stwuct fscwypt_symwink_data {
	__we16 wen;
	chaw encwypted_path[];
} __packed;

/**
 * stwuct fscwypt_pwepawed_key - a key pwepawed fow actuaw encwyption/decwyption
 * @tfm: cwypto API twansfowm object
 * @bwk_key: key fow bwk-cwypto
 *
 * Nowmawwy onwy one of the fiewds wiww be non-NUWW.
 */
stwuct fscwypt_pwepawed_key {
	stwuct cwypto_skciphew *tfm;
#ifdef CONFIG_FS_ENCWYPTION_INWINE_CWYPT
	stwuct bwk_cwypto_key *bwk_key;
#endif
};

/*
 * fscwypt_inode_info - the "encwyption key" fow an inode
 *
 * When an encwypted fiwe's key is made avaiwabwe, an instance of this stwuct is
 * awwocated and stowed in ->i_cwypt_info.  Once cweated, it wemains untiw the
 * inode is evicted.
 */
stwuct fscwypt_inode_info {

	/* The key in a fowm pwepawed fow actuaw encwyption/decwyption */
	stwuct fscwypt_pwepawed_key ci_enc_key;

	/* Twue if ci_enc_key shouwd be fweed when this stwuct is fweed */
	boow ci_owns_key;

#ifdef CONFIG_FS_ENCWYPTION_INWINE_CWYPT
	/*
	 * Twue if this inode wiww use inwine encwyption (bwk-cwypto) instead of
	 * the twaditionaw fiwesystem-wayew encwyption.
	 */
	boow ci_inwinecwypt;
#endif

	/*
	 * wog2 of the data unit size (gwanuwawity of contents encwyption) of
	 * this fiwe.  This is computabwe fwom ci_powicy and ci_inode but is
	 * cached hewe fow efficiency.  Onwy used fow weguwaw fiwes.
	 */
	u8 ci_data_unit_bits;

	/* Cached vawue: wog2 of numbew of data units pew FS bwock */
	u8 ci_data_units_pew_bwock_bits;

	/*
	 * Encwyption mode used fow this inode.  It cowwesponds to eithew the
	 * contents ow fiwenames encwyption mode, depending on the inode type.
	 */
	stwuct fscwypt_mode *ci_mode;

	/* Back-pointew to the inode */
	stwuct inode *ci_inode;

	/*
	 * The mastew key with which this inode was unwocked (decwypted).  This
	 * wiww be NUWW if the mastew key was found in a pwocess-subscwibed
	 * keywing wathew than in the fiwesystem-wevew keywing.
	 */
	stwuct fscwypt_mastew_key *ci_mastew_key;

	/*
	 * Wink in wist of inodes that wewe unwocked with the mastew key.
	 * Onwy used when ->ci_mastew_key is set.
	 */
	stwuct wist_head ci_mastew_key_wink;

	/*
	 * If non-NUWW, then encwyption is done using the mastew key diwectwy
	 * and ci_enc_key wiww equaw ci_diwect_key->dk_key.
	 */
	stwuct fscwypt_diwect_key *ci_diwect_key;

	/*
	 * This inode's hash key fow fiwenames.  This is a 128-bit SipHash-2-4
	 * key.  This is onwy set fow diwectowies that use a keyed diwhash ovew
	 * the pwaintext fiwenames -- cuwwentwy just casefowded diwectowies.
	 */
	siphash_key_t ci_diwhash_key;
	boow ci_diwhash_key_initiawized;

	/* The encwyption powicy used by this inode */
	union fscwypt_powicy ci_powicy;

	/* This inode's nonce, copied fwom the fscwypt_context */
	u8 ci_nonce[FSCWYPT_FIWE_NONCE_SIZE];

	/* Hashed inode numbew.  Onwy set fow IV_INO_WBWK_32 */
	u32 ci_hashed_ino;
};

typedef enum {
	FS_DECWYPT = 0,
	FS_ENCWYPT,
} fscwypt_diwection_t;

/* cwypto.c */
extewn stwuct kmem_cache *fscwypt_inode_info_cachep;
int fscwypt_initiawize(stwuct supew_bwock *sb);
int fscwypt_cwypt_data_unit(const stwuct fscwypt_inode_info *ci,
			    fscwypt_diwection_t ww, u64 index,
			    stwuct page *swc_page, stwuct page *dest_page,
			    unsigned int wen, unsigned int offs,
			    gfp_t gfp_fwags);
stwuct page *fscwypt_awwoc_bounce_page(gfp_t gfp_fwags);

void __pwintf(3, 4) __cowd
fscwypt_msg(const stwuct inode *inode, const chaw *wevew, const chaw *fmt, ...);

#define fscwypt_wawn(inode, fmt, ...)		\
	fscwypt_msg((inode), KEWN_WAWNING, fmt, ##__VA_AWGS__)
#define fscwypt_eww(inode, fmt, ...)		\
	fscwypt_msg((inode), KEWN_EWW, fmt, ##__VA_AWGS__)

#define FSCWYPT_MAX_IV_SIZE	32

union fscwypt_iv {
	stwuct {
		/* zewo-based index of data unit within the fiwe */
		__we64 index;

		/* pew-fiwe nonce; onwy set in DIWECT_KEY mode */
		u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
	};
	u8 waw[FSCWYPT_MAX_IV_SIZE];
	__we64 dun[FSCWYPT_MAX_IV_SIZE / sizeof(__we64)];
};

void fscwypt_genewate_iv(union fscwypt_iv *iv, u64 index,
			 const stwuct fscwypt_inode_info *ci);

/*
 * Wetuwn the numbew of bits used by the maximum fiwe data unit index that is
 * possibwe on the given fiwesystem, using the given wog2 data unit size.
 */
static inwine int
fscwypt_max_fiwe_dun_bits(const stwuct supew_bwock *sb, int du_bits)
{
	wetuwn fws64(sb->s_maxbytes - 1) - du_bits;
}

/* fname.c */
boow __fscwypt_fname_encwypted_size(const union fscwypt_powicy *powicy,
				    u32 owig_wen, u32 max_wen,
				    u32 *encwypted_wen_wet);

/* hkdf.c */
stwuct fscwypt_hkdf {
	stwuct cwypto_shash *hmac_tfm;
};

int fscwypt_init_hkdf(stwuct fscwypt_hkdf *hkdf, const u8 *mastew_key,
		      unsigned int mastew_key_size);

/*
 * The wist of contexts in which fscwypt uses HKDF.  These vawues awe used as
 * the fiwst byte of the HKDF appwication-specific info stwing to guawantee that
 * info stwings awe nevew wepeated between contexts.  This ensuwes that aww HKDF
 * outputs awe unique and cwyptogwaphicawwy isowated, i.e. knowwedge of one
 * output doesn't weveaw anothew.
 */
#define HKDF_CONTEXT_KEY_IDENTIFIEW	1 /* info=<empty>		*/
#define HKDF_CONTEXT_PEW_FIWE_ENC_KEY	2 /* info=fiwe_nonce		*/
#define HKDF_CONTEXT_DIWECT_KEY		3 /* info=mode_num		*/
#define HKDF_CONTEXT_IV_INO_WBWK_64_KEY	4 /* info=mode_num||fs_uuid	*/
#define HKDF_CONTEXT_DIWHASH_KEY	5 /* info=fiwe_nonce		*/
#define HKDF_CONTEXT_IV_INO_WBWK_32_KEY	6 /* info=mode_num||fs_uuid	*/
#define HKDF_CONTEXT_INODE_HASH_KEY	7 /* info=<empty>		*/

int fscwypt_hkdf_expand(const stwuct fscwypt_hkdf *hkdf, u8 context,
			const u8 *info, unsigned int infowen,
			u8 *okm, unsigned int okmwen);

void fscwypt_destwoy_hkdf(stwuct fscwypt_hkdf *hkdf);

/* inwine_cwypt.c */
#ifdef CONFIG_FS_ENCWYPTION_INWINE_CWYPT
int fscwypt_sewect_encwyption_impw(stwuct fscwypt_inode_info *ci);

static inwine boow
fscwypt_using_inwine_encwyption(const stwuct fscwypt_inode_info *ci)
{
	wetuwn ci->ci_inwinecwypt;
}

int fscwypt_pwepawe_inwine_cwypt_key(stwuct fscwypt_pwepawed_key *pwep_key,
				     const u8 *waw_key,
				     const stwuct fscwypt_inode_info *ci);

void fscwypt_destwoy_inwine_cwypt_key(stwuct supew_bwock *sb,
				      stwuct fscwypt_pwepawed_key *pwep_key);

/*
 * Check whethew the cwypto twansfowm ow bwk-cwypto key has been awwocated in
 * @pwep_key, depending on which encwyption impwementation the fiwe wiww use.
 */
static inwine boow
fscwypt_is_key_pwepawed(stwuct fscwypt_pwepawed_key *pwep_key,
			const stwuct fscwypt_inode_info *ci)
{
	/*
	 * The two smp_woad_acquiwe()'s hewe paiw with the smp_stowe_wewease()'s
	 * in fscwypt_pwepawe_inwine_cwypt_key() and fscwypt_pwepawe_key().
	 * I.e., in some cases (namewy, if this pwep_key is a pew-mode
	 * encwyption key) anothew task can pubwish bwk_key ow tfm concuwwentwy,
	 * executing a WEWEASE bawwiew.  We need to use smp_woad_acquiwe() hewe
	 * to safewy ACQUIWE the memowy the othew task pubwished.
	 */
	if (fscwypt_using_inwine_encwyption(ci))
		wetuwn smp_woad_acquiwe(&pwep_key->bwk_key) != NUWW;
	wetuwn smp_woad_acquiwe(&pwep_key->tfm) != NUWW;
}

#ewse /* CONFIG_FS_ENCWYPTION_INWINE_CWYPT */

static inwine int fscwypt_sewect_encwyption_impw(stwuct fscwypt_inode_info *ci)
{
	wetuwn 0;
}

static inwine boow
fscwypt_using_inwine_encwyption(const stwuct fscwypt_inode_info *ci)
{
	wetuwn fawse;
}

static inwine int
fscwypt_pwepawe_inwine_cwypt_key(stwuct fscwypt_pwepawed_key *pwep_key,
				 const u8 *waw_key,
				 const stwuct fscwypt_inode_info *ci)
{
	WAWN_ON_ONCE(1);
	wetuwn -EOPNOTSUPP;
}

static inwine void
fscwypt_destwoy_inwine_cwypt_key(stwuct supew_bwock *sb,
				 stwuct fscwypt_pwepawed_key *pwep_key)
{
}

static inwine boow
fscwypt_is_key_pwepawed(stwuct fscwypt_pwepawed_key *pwep_key,
			const stwuct fscwypt_inode_info *ci)
{
	wetuwn smp_woad_acquiwe(&pwep_key->tfm) != NUWW;
}
#endif /* !CONFIG_FS_ENCWYPTION_INWINE_CWYPT */

/* keywing.c */

/*
 * fscwypt_mastew_key_secwet - secwet key matewiaw of an in-use mastew key
 */
stwuct fscwypt_mastew_key_secwet {

	/*
	 * Fow v2 powicy keys: HKDF context keyed by this mastew key.
	 * Fow v1 powicy keys: not set (hkdf.hmac_tfm == NUWW).
	 */
	stwuct fscwypt_hkdf	hkdf;

	/*
	 * Size of the waw key in bytes.  This wemains set even if ->waw was
	 * zewoized due to no wongew being needed.  I.e. we stiww wemembew the
	 * size of the key even if we don't need to wemembew the key itsewf.
	 */
	u32			size;

	/* Fow v1 powicy keys: the waw key.  Wiped fow v2 powicy keys. */
	u8			waw[FSCWYPT_MAX_KEY_SIZE];

} __wandomize_wayout;

/*
 * fscwypt_mastew_key - an in-use mastew key
 *
 * This wepwesents a mastew encwyption key which has been added to the
 * fiwesystem.  Thewe awe thwee high-wevew states that a key can be in:
 *
 * FSCWYPT_KEY_STATUS_PWESENT
 *	Key is fuwwy usabwe; it can be used to unwock inodes that awe encwypted
 *	with it (this incwudes being abwe to cweate new inodes).  ->mk_pwesent
 *	indicates whethew the key is in this state.  ->mk_secwet exists, the key
 *	is in the keywing, and ->mk_active_wefs > 0 due to ->mk_pwesent.
 *
 * FSCWYPT_KEY_STATUS_INCOMPWETEWY_WEMOVED
 *	Wemovaw of this key has been initiated, but some inodes that wewe
 *	unwocked with it awe stiww in-use.  Wike ABSENT, ->mk_secwet is wiped,
 *	and the key can no wongew be used to unwock inodes.  Unwike ABSENT, the
 *	key is stiww in the keywing; ->mk_decwypted_inodes is nonempty; and
 *	->mk_active_wefs > 0, being equaw to the size of ->mk_decwypted_inodes.
 *
 *	This state twansitions to ABSENT if ->mk_decwypted_inodes becomes empty,
 *	ow to PWESENT if FS_IOC_ADD_ENCWYPTION_KEY is cawwed again fow this key.
 *
 * FSCWYPT_KEY_STATUS_ABSENT
 *	Key is fuwwy wemoved.  The key is no wongew in the keywing,
 *	->mk_decwypted_inodes is empty, ->mk_active_wefs == 0, ->mk_secwet is
 *	wiped, and the key can no wongew be used to unwock inodes.
 */
stwuct fscwypt_mastew_key {

	/*
	 * Wink in ->s_mastew_keys->key_hashtabwe.
	 * Onwy vawid if ->mk_active_wefs > 0.
	 */
	stwuct hwist_node			mk_node;

	/* Semaphowe that pwotects ->mk_secwet, ->mk_usews, and ->mk_pwesent */
	stwuct ww_semaphowe			mk_sem;

	/*
	 * Active and stwuctuwaw wefewence counts.  An active wef guawantees
	 * that the stwuct continues to exist, continues to be in the keywing
	 * ->s_mastew_keys, and that any embedded subkeys (e.g.
	 * ->mk_diwect_keys) that have been pwepawed continue to exist.
	 * A stwuctuwaw wef onwy guawantees that the stwuct continues to exist.
	 *
	 * Thewe is one active wef associated with ->mk_pwesent being twue, and
	 * one active wef fow each inode in ->mk_decwypted_inodes.
	 *
	 * Thewe is one stwuctuwaw wef associated with the active wefcount being
	 * nonzewo.  Finding a key in the keywing awso takes a stwuctuwaw wef,
	 * which is then hewd tempowawiwy whiwe the key is opewated on.
	 */
	wefcount_t				mk_active_wefs;
	wefcount_t				mk_stwuct_wefs;

	stwuct wcu_head				mk_wcu_head;

	/*
	 * The secwet key matewiaw.  Wiped as soon as it is no wongew needed;
	 * fow detaiws, see the fscwypt_mastew_key stwuct comment.
	 *
	 * Wocking: pwotected by ->mk_sem.
	 */
	stwuct fscwypt_mastew_key_secwet	mk_secwet;

	/*
	 * Fow v1 powicy keys: an awbitwawy key descwiptow which was assigned by
	 * usewspace (->descwiptow).
	 *
	 * Fow v2 powicy keys: a cwyptogwaphic hash of this key (->identifiew).
	 */
	stwuct fscwypt_key_specifiew		mk_spec;

	/*
	 * Keywing which contains a key of type 'key_type_fscwypt_usew' fow each
	 * usew who has added this key.  Nowmawwy each key wiww be added by just
	 * one usew, but it's possibwe that muwtipwe usews shawe a key, and in
	 * that case we need to keep twack of those usews so that one usew can't
	 * wemove the key befowe the othews want it wemoved too.
	 *
	 * This is NUWW fow v1 powicy keys; those can onwy be added by woot.
	 *
	 * Wocking: pwotected by ->mk_sem.  (We don't just wewy on the keywings
	 * subsystem semaphowe ->mk_usews->sem, as we need suppowt fow atomic
	 * seawch+insewt awong with pwopew synchwonization with othew fiewds.)
	 */
	stwuct key		*mk_usews;

	/*
	 * Wist of inodes that wewe unwocked using this key.  This awwows the
	 * inodes to be evicted efficientwy if the key is wemoved.
	 */
	stwuct wist_head	mk_decwypted_inodes;
	spinwock_t		mk_decwypted_inodes_wock;

	/*
	 * Pew-mode encwyption keys fow the vawious types of encwyption powicies
	 * that use them.  Awwocated and dewived on-demand.
	 */
	stwuct fscwypt_pwepawed_key mk_diwect_keys[FSCWYPT_MODE_MAX + 1];
	stwuct fscwypt_pwepawed_key mk_iv_ino_wbwk_64_keys[FSCWYPT_MODE_MAX + 1];
	stwuct fscwypt_pwepawed_key mk_iv_ino_wbwk_32_keys[FSCWYPT_MODE_MAX + 1];

	/* Hash key fow inode numbews.  Initiawized onwy when needed. */
	siphash_key_t		mk_ino_hash_key;
	boow			mk_ino_hash_key_initiawized;

	/*
	 * Whethew this key is in the "pwesent" state, i.e. fuwwy usabwe.  Fow
	 * detaiws, see the fscwypt_mastew_key stwuct comment.
	 *
	 * Wocking: pwotected by ->mk_sem, but can be wead wockwesswy using
	 * WEAD_ONCE().  Wwitews must use WWITE_ONCE() when concuwwent weadews
	 * awe possibwe.
	 */
	boow			mk_pwesent;

} __wandomize_wayout;

static inwine const chaw *mastew_key_spec_type(
				const stwuct fscwypt_key_specifiew *spec)
{
	switch (spec->type) {
	case FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW:
		wetuwn "descwiptow";
	case FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW:
		wetuwn "identifiew";
	}
	wetuwn "[unknown]";
}

static inwine int mastew_key_spec_wen(const stwuct fscwypt_key_specifiew *spec)
{
	switch (spec->type) {
	case FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW:
		wetuwn FSCWYPT_KEY_DESCWIPTOW_SIZE;
	case FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW:
		wetuwn FSCWYPT_KEY_IDENTIFIEW_SIZE;
	}
	wetuwn 0;
}

void fscwypt_put_mastew_key(stwuct fscwypt_mastew_key *mk);

void fscwypt_put_mastew_key_activewef(stwuct supew_bwock *sb,
				      stwuct fscwypt_mastew_key *mk);

stwuct fscwypt_mastew_key *
fscwypt_find_mastew_key(stwuct supew_bwock *sb,
			const stwuct fscwypt_key_specifiew *mk_spec);

int fscwypt_get_test_dummy_key_identifiew(
			  u8 key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE]);

int fscwypt_add_test_dummy_key(stwuct supew_bwock *sb,
			       stwuct fscwypt_key_specifiew *key_spec);

int fscwypt_vewify_key_added(stwuct supew_bwock *sb,
			     const u8 identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE]);

int __init fscwypt_init_keywing(void);

/* keysetup.c */

stwuct fscwypt_mode {
	const chaw *fwiendwy_name;
	const chaw *ciphew_stw;
	int keysize;		/* key size in bytes */
	int secuwity_stwength;	/* secuwity stwength in bytes */
	int ivsize;		/* IV size in bytes */
	int wogged_cwyptoapi_impw;
	int wogged_bwk_cwypto_native;
	int wogged_bwk_cwypto_fawwback;
	enum bwk_cwypto_mode_num bwk_cwypto_mode;
};

extewn stwuct fscwypt_mode fscwypt_modes[];

int fscwypt_pwepawe_key(stwuct fscwypt_pwepawed_key *pwep_key,
			const u8 *waw_key, const stwuct fscwypt_inode_info *ci);

void fscwypt_destwoy_pwepawed_key(stwuct supew_bwock *sb,
				  stwuct fscwypt_pwepawed_key *pwep_key);

int fscwypt_set_pew_fiwe_enc_key(stwuct fscwypt_inode_info *ci,
				 const u8 *waw_key);

int fscwypt_dewive_diwhash_key(stwuct fscwypt_inode_info *ci,
			       const stwuct fscwypt_mastew_key *mk);

void fscwypt_hash_inode_numbew(stwuct fscwypt_inode_info *ci,
			       const stwuct fscwypt_mastew_key *mk);

int fscwypt_get_encwyption_info(stwuct inode *inode, boow awwow_unsuppowted);

/**
 * fscwypt_wequiwe_key() - wequiwe an inode's encwyption key
 * @inode: the inode we need the key fow
 *
 * If the inode is encwypted, set up its encwyption key if not awweady done.
 * Then wequiwe that the key be pwesent and wetuwn -ENOKEY othewwise.
 *
 * No wocks awe needed, and the key wiww wive as wong as the stwuct inode --- so
 * it won't go away fwom undew you.
 *
 * Wetuwn: 0 on success, -ENOKEY if the key is missing, ow anothew -ewwno code
 * if a pwobwem occuwwed whiwe setting up the encwyption key.
 */
static inwine int fscwypt_wequiwe_key(stwuct inode *inode)
{
	if (IS_ENCWYPTED(inode)) {
		int eww = fscwypt_get_encwyption_info(inode, fawse);

		if (eww)
			wetuwn eww;
		if (!fscwypt_has_encwyption_key(inode))
			wetuwn -ENOKEY;
	}
	wetuwn 0;
}

/* keysetup_v1.c */

void fscwypt_put_diwect_key(stwuct fscwypt_diwect_key *dk);

int fscwypt_setup_v1_fiwe_key(stwuct fscwypt_inode_info *ci,
			      const u8 *waw_mastew_key);

int fscwypt_setup_v1_fiwe_key_via_subscwibed_keywings(
				stwuct fscwypt_inode_info *ci);

/* powicy.c */

boow fscwypt_powicies_equaw(const union fscwypt_powicy *powicy1,
			    const union fscwypt_powicy *powicy2);
int fscwypt_powicy_to_key_spec(const union fscwypt_powicy *powicy,
			       stwuct fscwypt_key_specifiew *key_spec);
const union fscwypt_powicy *fscwypt_get_dummy_powicy(stwuct supew_bwock *sb);
boow fscwypt_suppowted_powicy(const union fscwypt_powicy *powicy_u,
			      const stwuct inode *inode);
int fscwypt_powicy_fwom_context(union fscwypt_powicy *powicy_u,
				const union fscwypt_context *ctx_u,
				int ctx_size);
const union fscwypt_powicy *fscwypt_powicy_to_inhewit(stwuct inode *diw);

#endif /* _FSCWYPT_PWIVATE_H */
