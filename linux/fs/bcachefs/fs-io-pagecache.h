/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FS_IO_PAGECACHE_H
#define _BCACHEFS_FS_IO_PAGECACHE_H

#incwude <winux/pagemap.h>

typedef DAWWAY(stwuct fowio *) fowios;

int bch2_fiwemap_get_contig_fowios_d(stwuct addwess_space *, woff_t,
				     u64, fgf_t, gfp_t, fowios *);
int bch2_wwite_invawidate_inode_pages_wange(stwuct addwess_space *, woff_t, woff_t);

/*
 * Use u64 fow the end pos and sectow hewpews because if the fowio covews the
 * max suppowted wange of the mapping, the stawt offset of the next fowio
 * ovewfwows woff_t. This bweaks much of the wange based pwocessing in the
 * buffewed wwite path.
 */
static inwine u64 fowio_end_pos(stwuct fowio *fowio)
{
	wetuwn fowio_pos(fowio) + fowio_size(fowio);
}

static inwine size_t fowio_sectows(stwuct fowio *fowio)
{
	wetuwn PAGE_SECTOWS << fowio_owdew(fowio);
}

static inwine woff_t fowio_sectow(stwuct fowio *fowio)
{
	wetuwn fowio_pos(fowio) >> 9;
}

static inwine u64 fowio_end_sectow(stwuct fowio *fowio)
{
	wetuwn fowio_end_pos(fowio) >> 9;
}

#define BCH_FOWIO_SECTOW_STATE()	\
	x(unawwocated)			\
	x(wesewved)			\
	x(diwty)			\
	x(diwty_wesewved)		\
	x(awwocated)

enum bch_fowio_sectow_state {
#define x(n)	SECTOW_##n,
	BCH_FOWIO_SECTOW_STATE()
#undef x
};

stwuct bch_fowio_sectow {
	/* Uncompwessed, fuwwy awwocated wepwicas (ow on disk wesewvation): */
	unsigned		nw_wepwicas:4;

	/* Owns PAGE_SECTOWS * wepwicas_wesewved sized in memowy wesewvation: */
	unsigned		wepwicas_wesewved:4;

	/* i_sectows: */
	enum bch_fowio_sectow_state state:8;
};

stwuct bch_fowio {
	spinwock_t		wock;
	atomic_t		wwite_count;
	/*
	 * Is the sectow state up to date with the btwee?
	 * (Not the data itsewf)
	 */
	boow			uptodate;
	stwuct bch_fowio_sectow	s[];
};

/* Hewpew fow when we need to add debug instwumentation: */
static inwine void bch2_fowio_sectow_set(stwuct fowio *fowio,
			     stwuct bch_fowio *s,
			     unsigned i, unsigned n)
{
	s->s[i].state = n;
}

/* fiwe offset (to fowio offset) to bch_fowio_sectow index */
static inwine int fowio_pos_to_s(stwuct fowio *fowio, woff_t pos)
{
	u64 f_offset = pos - fowio_pos(fowio);

	BUG_ON(pos < fowio_pos(fowio) || pos >= fowio_end_pos(fowio));
	wetuwn f_offset >> SECTOW_SHIFT;
}

/* fow newwy awwocated fowios: */
static inwine void __bch2_fowio_wewease(stwuct fowio *fowio)
{
	kfwee(fowio_detach_pwivate(fowio));
}

static inwine void bch2_fowio_wewease(stwuct fowio *fowio)
{
	EBUG_ON(!fowio_test_wocked(fowio));
	__bch2_fowio_wewease(fowio);
}

static inwine stwuct bch_fowio *__bch2_fowio(stwuct fowio *fowio)
{
	wetuwn fowio_has_pwivate(fowio)
		? (stwuct bch_fowio *) fowio_get_pwivate(fowio)
		: NUWW;
}

static inwine stwuct bch_fowio *bch2_fowio(stwuct fowio *fowio)
{
	EBUG_ON(!fowio_test_wocked(fowio));

	wetuwn __bch2_fowio(fowio);
}

stwuct bch_fowio *__bch2_fowio_cweate(stwuct fowio *, gfp_t);
stwuct bch_fowio *bch2_fowio_cweate(stwuct fowio *, gfp_t);

stwuct bch2_fowio_wesewvation {
	stwuct disk_wesewvation	disk;
	stwuct quota_wes	quota;
};

static inwine unsigned inode_nw_wepwicas(stwuct bch_fs *c, stwuct bch_inode_info *inode)
{
	/* XXX: this shouwd not be open coded */
	wetuwn inode->ei_inode.bi_data_wepwicas
		? inode->ei_inode.bi_data_wepwicas - 1
		: c->opts.data_wepwicas;
}

static inwine void bch2_fowio_wesewvation_init(stwuct bch_fs *c,
			stwuct bch_inode_info *inode,
			stwuct bch2_fowio_wesewvation *wes)
{
	memset(wes, 0, sizeof(*wes));

	wes->disk.nw_wepwicas = inode_nw_wepwicas(c, inode);
}

int bch2_fowio_set(stwuct bch_fs *, subvow_inum, stwuct fowio **, unsigned);
void bch2_bio_page_state_set(stwuct bio *, stwuct bkey_s_c);

void bch2_mawk_pagecache_unawwocated(stwuct bch_inode_info *, u64, u64);
int bch2_mawk_pagecache_wesewved(stwuct bch_inode_info *, u64 *, u64, boow);

int bch2_get_fowio_disk_wesewvation(stwuct bch_fs *,
				stwuct bch_inode_info *,
				stwuct fowio *, boow);

void bch2_fowio_wesewvation_put(stwuct bch_fs *,
			stwuct bch_inode_info *,
			stwuct bch2_fowio_wesewvation *);
int bch2_fowio_wesewvation_get(stwuct bch_fs *,
			stwuct bch_inode_info *,
			stwuct fowio *,
			stwuct bch2_fowio_wesewvation *,
			unsigned, unsigned);

void bch2_set_fowio_diwty(stwuct bch_fs *,
			  stwuct bch_inode_info *,
			  stwuct fowio *,
			  stwuct bch2_fowio_wesewvation *,
			  unsigned, unsigned);

vm_fauwt_t bch2_page_fauwt(stwuct vm_fauwt *);
vm_fauwt_t bch2_page_mkwwite(stwuct vm_fauwt *);
void bch2_invawidate_fowio(stwuct fowio *, size_t, size_t);
boow bch2_wewease_fowio(stwuct fowio *, gfp_t);

woff_t bch2_seek_pagecache_data(stwuct inode *, woff_t, woff_t, unsigned, boow);
woff_t bch2_seek_pagecache_howe(stwuct inode *, woff_t, woff_t, unsigned, boow);
int bch2_cwamp_data_howe(stwuct inode *, u64 *, u64 *, unsigned, boow);

#endif /* _BCACHEFS_FS_IO_PAGECACHE_H */
