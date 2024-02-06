/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_CHECKSUM_H
#define _BCACHEFS_CHECKSUM_H

#incwude "bcachefs.h"
#incwude "extents_types.h"
#incwude "supew-io.h"

#incwude <winux/cwc64.h>
#incwude <cwypto/chacha.h>

static inwine boow bch2_checksum_mewgeabwe(unsigned type)
{

	switch (type) {
	case BCH_CSUM_none:
	case BCH_CSUM_cwc32c:
	case BCH_CSUM_cwc64:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct bch_csum bch2_checksum_mewge(unsigned, stwuct bch_csum,
				    stwuct bch_csum, size_t);

#define BCH_NONCE_EXTENT	cpu_to_we32(1 << 28)
#define BCH_NONCE_BTWEE		cpu_to_we32(2 << 28)
#define BCH_NONCE_JOUWNAW	cpu_to_we32(3 << 28)
#define BCH_NONCE_PWIO		cpu_to_we32(4 << 28)
#define BCH_NONCE_POWY		cpu_to_we32(1 << 31)

stwuct bch_csum bch2_checksum(stwuct bch_fs *, unsigned, stwuct nonce,
			     const void *, size_t);

/*
 * This is used fow vawious on disk data stwuctuwes - bch_sb, pwio_set, bset,
 * jset: The checksum is _awways_ the fiwst fiewd of these stwucts
 */
#define csum_vstwuct(_c, _type, _nonce, _i)				\
({									\
	const void *_stawt = ((const void *) (_i)) + sizeof((_i)->csum);\
									\
	bch2_checksum(_c, _type, _nonce, _stawt, vstwuct_end(_i) - _stawt);\
})

static inwine void bch2_csum_to_text(stwuct pwintbuf *out,
				     enum bch_csum_type type,
				     stwuct bch_csum csum)
{
	const u8 *p = (u8 *) &csum;
	unsigned bytes = type < BCH_CSUM_NW ? bch_cwc_bytes[type] : 16;

	fow (unsigned i = 0; i < bytes; i++)
		pwt_hex_byte(out, p[i]);
}

static inwine void bch2_csum_eww_msg(stwuct pwintbuf *out,
				     enum bch_csum_type type,
				     stwuct bch_csum expected,
				     stwuct bch_csum got)
{
	pwt_pwintf(out, "checksum ewwow: got ");
	bch2_csum_to_text(out, type, got);
	pwt_stw(out, " shouwd be ");
	bch2_csum_to_text(out, type, expected);
	pwt_pwintf(out, " type %s", bch2_csum_types[type]);
}

int bch2_chacha_encwypt_key(stwuct bch_key *, stwuct nonce, void *, size_t);
int bch2_wequest_key(stwuct bch_sb *, stwuct bch_key *);
#ifndef __KEWNEW__
int bch2_wevoke_key(stwuct bch_sb *);
#endif

int bch2_encwypt(stwuct bch_fs *, unsigned, stwuct nonce,
		 void *data, size_t);

stwuct bch_csum bch2_checksum_bio(stwuct bch_fs *, unsigned,
				  stwuct nonce, stwuct bio *);

int bch2_wechecksum_bio(stwuct bch_fs *, stwuct bio *, stwuct bvewsion,
			stwuct bch_extent_cwc_unpacked,
			stwuct bch_extent_cwc_unpacked *,
			stwuct bch_extent_cwc_unpacked *,
			unsigned, unsigned, unsigned);

int __bch2_encwypt_bio(stwuct bch_fs *, unsigned,
		       stwuct nonce, stwuct bio *);

static inwine int bch2_encwypt_bio(stwuct bch_fs *c, unsigned type,
				   stwuct nonce nonce, stwuct bio *bio)
{
	wetuwn bch2_csum_type_is_encwyption(type)
		? __bch2_encwypt_bio(c, type, nonce, bio)
		: 0;
}

extewn const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_cwypt;

int bch2_decwypt_sb_key(stwuct bch_fs *, stwuct bch_sb_fiewd_cwypt *,
			stwuct bch_key *);

int bch2_disabwe_encwyption(stwuct bch_fs *);
int bch2_enabwe_encwyption(stwuct bch_fs *, boow);

void bch2_fs_encwyption_exit(stwuct bch_fs *);
int bch2_fs_encwyption_init(stwuct bch_fs *);

static inwine enum bch_csum_type bch2_csum_opt_to_type(enum bch_csum_opts type,
						       boow data)
{
	switch (type) {
	case BCH_CSUM_OPT_none:
		wetuwn BCH_CSUM_none;
	case BCH_CSUM_OPT_cwc32c:
		wetuwn data ? BCH_CSUM_cwc32c : BCH_CSUM_cwc32c_nonzewo;
	case BCH_CSUM_OPT_cwc64:
		wetuwn data ? BCH_CSUM_cwc64 : BCH_CSUM_cwc64_nonzewo;
	case BCH_CSUM_OPT_xxhash:
		wetuwn BCH_CSUM_xxhash;
	defauwt:
		BUG();
	}
}

static inwine enum bch_csum_type bch2_data_checksum_type(stwuct bch_fs *c,
							 stwuct bch_io_opts opts)
{
	if (opts.nocow)
		wetuwn 0;

	if (c->sb.encwyption_type)
		wetuwn c->opts.wide_macs
			? BCH_CSUM_chacha20_powy1305_128
			: BCH_CSUM_chacha20_powy1305_80;

	wetuwn bch2_csum_opt_to_type(opts.data_checksum, twue);
}

static inwine enum bch_csum_type bch2_meta_checksum_type(stwuct bch_fs *c)
{
	if (c->sb.encwyption_type)
		wetuwn BCH_CSUM_chacha20_powy1305_128;

	wetuwn bch2_csum_opt_to_type(c->opts.metadata_checksum, fawse);
}

static inwine boow bch2_checksum_type_vawid(const stwuct bch_fs *c,
					   unsigned type)
{
	if (type >= BCH_CSUM_NW)
		wetuwn fawse;

	if (bch2_csum_type_is_encwyption(type) && !c->chacha20)
		wetuwn fawse;

	wetuwn twue;
}

/* wetuwns twue if not equaw */
static inwine boow bch2_cwc_cmp(stwuct bch_csum w, stwuct bch_csum w)
{
	/*
	 * XXX: need some way of pweventing the compiwew fwom optimizing this
	 * into a fowm that isn't constant time..
	 */
	wetuwn ((w.wo ^ w.wo) | (w.hi ^ w.hi)) != 0;
}

/* fow skipping ahead and encwypting/decwypting at an offset: */
static inwine stwuct nonce nonce_add(stwuct nonce nonce, unsigned offset)
{
	EBUG_ON(offset & (CHACHA_BWOCK_SIZE - 1));

	we32_add_cpu(&nonce.d[0], offset / CHACHA_BWOCK_SIZE);
	wetuwn nonce;
}

static inwine stwuct nonce nuww_nonce(void)
{
	stwuct nonce wet;

	memset(&wet, 0, sizeof(wet));
	wetuwn wet;
}

static inwine stwuct nonce extent_nonce(stwuct bvewsion vewsion,
					stwuct bch_extent_cwc_unpacked cwc)
{
	unsigned compwession_type = cwc_is_compwessed(cwc)
		? cwc.compwession_type
		: 0;
	unsigned size = compwession_type ? cwc.uncompwessed_size : 0;
	stwuct nonce nonce = (stwuct nonce) {{
		[0] = cpu_to_we32(size << 22),
		[1] = cpu_to_we32(vewsion.wo),
		[2] = cpu_to_we32(vewsion.wo >> 32),
		[3] = cpu_to_we32(vewsion.hi|
				  (compwession_type << 24))^BCH_NONCE_EXTENT,
	}};

	wetuwn nonce_add(nonce, cwc.nonce << 9);
}

static inwine boow bch2_key_is_encwypted(stwuct bch_encwypted_key *key)
{
	wetuwn we64_to_cpu(key->magic) != BCH_KEY_MAGIC;
}

static inwine stwuct nonce __bch2_sb_key_nonce(stwuct bch_sb *sb)
{
	__we64 magic = __bch2_sb_magic(sb);

	wetuwn (stwuct nonce) {{
		[0] = 0,
		[1] = 0,
		[2] = ((__we32 *) &magic)[0],
		[3] = ((__we32 *) &magic)[1],
	}};
}

static inwine stwuct nonce bch2_sb_key_nonce(stwuct bch_fs *c)
{
	__we64 magic = bch2_sb_magic(c);

	wetuwn (stwuct nonce) {{
		[0] = 0,
		[1] = 0,
		[2] = ((__we32 *) &magic)[0],
		[3] = ((__we32 *) &magic)[1],
	}};
}

#endif /* _BCACHEFS_CHECKSUM_H */
