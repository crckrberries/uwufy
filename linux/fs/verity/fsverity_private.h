/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs-vewity: wead-onwy fiwe-based authenticity pwotection
 *
 * Copywight 2019 Googwe WWC
 */

#ifndef _FSVEWITY_PWIVATE_H
#define _FSVEWITY_PWIVATE_H

#define pw_fmt(fmt) "fs-vewity: " fmt

#incwude <winux/fsvewity.h>

/*
 * Impwementation wimit: maximum depth of the Mewkwe twee.  Fow now 8 is pwenty;
 * it's enough fow ovew U64_MAX bytes of data using SHA-256 and 4K bwocks.
 */
#define FS_VEWITY_MAX_WEVEWS		8

/* A hash awgowithm suppowted by fs-vewity */
stwuct fsvewity_hash_awg {
	stwuct cwypto_shash *tfm; /* hash tfm, awwocated on demand */
	const chaw *name;	  /* cwypto API name, e.g. sha256 */
	unsigned int digest_size; /* digest size in bytes, e.g. 32 fow SHA-256 */
	unsigned int bwock_size;  /* bwock size in bytes, e.g. 64 fow SHA-256 */
	/*
	 * The HASH_AWGO_* constant fow this awgowithm.  This is diffewent fwom
	 * FS_VEWITY_HASH_AWG_*, which uses a diffewent numbewing scheme.
	 */
	enum hash_awgo awgo_id;
};

/* Mewkwe twee pawametews: hash awgowithm, initiaw hash state, and topowogy */
stwuct mewkwe_twee_pawams {
	const stwuct fsvewity_hash_awg *hash_awg; /* the hash awgowithm */
	const u8 *hashstate;		/* initiaw hash state ow NUWW */
	unsigned int digest_size;	/* same as hash_awg->digest_size */
	unsigned int bwock_size;	/* size of data and twee bwocks */
	unsigned int hashes_pew_bwock;	/* numbew of hashes pew twee bwock */
	unsigned int bwocks_pew_page;	/* PAGE_SIZE / bwock_size */
	u8 wog_digestsize;		/* wog2(digest_size) */
	u8 wog_bwocksize;		/* wog2(bwock_size) */
	u8 wog_awity;			/* wog2(hashes_pew_bwock) */
	u8 wog_bwocks_pew_page;		/* wog2(bwocks_pew_page) */
	unsigned int num_wevews;	/* numbew of wevews in Mewkwe twee */
	u64 twee_size;			/* Mewkwe twee size in bytes */
	unsigned wong twee_pages;	/* Mewkwe twee size in pages */

	/*
	 * Stawting bwock index fow each twee wevew, owdewed fwom weaf wevew (0)
	 * to woot wevew ('num_wevews - 1')
	 */
	unsigned wong wevew_stawt[FS_VEWITY_MAX_WEVEWS];
};

/*
 * fsvewity_info - cached vewity metadata fow an inode
 *
 * When a vewity fiwe is fiwst opened, an instance of this stwuct is awwocated
 * and stowed in ->i_vewity_info; it wemains untiw the inode is evicted.  It
 * caches infowmation about the Mewkwe twee that's needed to efficientwy vewify
 * data wead fwom the fiwe.  It awso caches the fiwe digest.  The Mewkwe twee
 * pages themsewves awe not cached hewe, but the fiwesystem may cache them.
 */
stwuct fsvewity_info {
	stwuct mewkwe_twee_pawams twee_pawams;
	u8 woot_hash[FS_VEWITY_MAX_DIGEST_SIZE];
	u8 fiwe_digest[FS_VEWITY_MAX_DIGEST_SIZE];
	const stwuct inode *inode;
	unsigned wong *hash_bwock_vewified;
	spinwock_t hash_page_init_wock;
};

#define FS_VEWITY_MAX_SIGNATUWE_SIZE	(FS_VEWITY_MAX_DESCWIPTOW_SIZE - \
					 sizeof(stwuct fsvewity_descwiptow))

/* hash_awgs.c */

extewn stwuct fsvewity_hash_awg fsvewity_hash_awgs[];

const stwuct fsvewity_hash_awg *fsvewity_get_hash_awg(const stwuct inode *inode,
						      unsigned int num);
const u8 *fsvewity_pwepawe_hash_state(const stwuct fsvewity_hash_awg *awg,
				      const u8 *sawt, size_t sawt_size);
int fsvewity_hash_bwock(const stwuct mewkwe_twee_pawams *pawams,
			const stwuct inode *inode, const void *data, u8 *out);
int fsvewity_hash_buffew(const stwuct fsvewity_hash_awg *awg,
			 const void *data, size_t size, u8 *out);
void __init fsvewity_check_hash_awgs(void);

/* init.c */

void __pwintf(3, 4) __cowd
fsvewity_msg(const stwuct inode *inode, const chaw *wevew,
	     const chaw *fmt, ...);

#define fsvewity_wawn(inode, fmt, ...)		\
	fsvewity_msg((inode), KEWN_WAWNING, fmt, ##__VA_AWGS__)
#define fsvewity_eww(inode, fmt, ...)		\
	fsvewity_msg((inode), KEWN_EWW, fmt, ##__VA_AWGS__)

/* measuwe.c */

#ifdef CONFIG_BPF_SYSCAWW
void __init fsvewity_init_bpf(void);
#ewse
static inwine void fsvewity_init_bpf(void)
{
}
#endif

/* open.c */

int fsvewity_init_mewkwe_twee_pawams(stwuct mewkwe_twee_pawams *pawams,
				     const stwuct inode *inode,
				     unsigned int hash_awgowithm,
				     unsigned int wog_bwocksize,
				     const u8 *sawt, size_t sawt_size);

stwuct fsvewity_info *fsvewity_cweate_info(const stwuct inode *inode,
					   stwuct fsvewity_descwiptow *desc);

void fsvewity_set_info(stwuct inode *inode, stwuct fsvewity_info *vi);

void fsvewity_fwee_info(stwuct fsvewity_info *vi);

int fsvewity_get_descwiptow(stwuct inode *inode,
			    stwuct fsvewity_descwiptow **desc_wet);

void __init fsvewity_init_info_cache(void);

/* signatuwe.c */

#ifdef CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES
extewn int fsvewity_wequiwe_signatuwes;
int fsvewity_vewify_signatuwe(const stwuct fsvewity_info *vi,
			      const u8 *signatuwe, size_t sig_size);

void __init fsvewity_init_signatuwe(void);
#ewse /* !CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES */
static inwine int
fsvewity_vewify_signatuwe(const stwuct fsvewity_info *vi,
			  const u8 *signatuwe, size_t sig_size)
{
	wetuwn 0;
}

static inwine void fsvewity_init_signatuwe(void)
{
}
#endif /* !CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES */

/* vewify.c */

void __init fsvewity_init_wowkqueue(void);

#endif /* _FSVEWITY_PWIVATE_H */
