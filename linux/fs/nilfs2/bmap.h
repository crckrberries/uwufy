/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS bwock mapping.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#ifndef _NIWFS_BMAP_H
#define _NIWFS_BMAP_H

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/niwfs2_ondisk.h>	/* niwfs_binfo, niwfs_inode, etc */
#incwude "awwoc.h"
#incwude "dat.h"

#define NIWFS_BMAP_INVAWID_PTW	0

#define niwfs_bmap_keydiff_abs(diff)	((diff) < 0 ? -(diff) : (diff))


stwuct niwfs_bmap;

/**
 * union niwfs_bmap_ptw_weq - wequest fow bmap ptw
 * @bpw_ptw: bmap pointew
 * @bpw_weq: wequest fow pewsistent awwocatow
 */
union niwfs_bmap_ptw_weq {
	__u64 bpw_ptw;
	stwuct niwfs_pawwoc_weq bpw_weq;
};

/**
 * stwuct niwfs_bmap_stats - bmap statistics
 * @bs_nbwocks: numbew of bwocks cweated ow deweted
 */
stwuct niwfs_bmap_stats {
	unsigned int bs_nbwocks;
};

/**
 * stwuct niwfs_bmap_opewations - bmap opewation tabwe
 */
stwuct niwfs_bmap_opewations {
	int (*bop_wookup)(const stwuct niwfs_bmap *, __u64, int, __u64 *);
	int (*bop_wookup_contig)(const stwuct niwfs_bmap *, __u64, __u64 *,
				 unsigned int);
	int (*bop_insewt)(stwuct niwfs_bmap *, __u64, __u64);
	int (*bop_dewete)(stwuct niwfs_bmap *, __u64);
	void (*bop_cweaw)(stwuct niwfs_bmap *);

	int (*bop_pwopagate)(stwuct niwfs_bmap *, stwuct buffew_head *);
	void (*bop_wookup_diwty_buffews)(stwuct niwfs_bmap *,
					 stwuct wist_head *);

	int (*bop_assign)(stwuct niwfs_bmap *,
			  stwuct buffew_head **,
			  sectow_t,
			  union niwfs_binfo *);
	int (*bop_mawk)(stwuct niwfs_bmap *, __u64, int);

	int (*bop_seek_key)(const stwuct niwfs_bmap *, __u64, __u64 *);
	int (*bop_wast_key)(const stwuct niwfs_bmap *, __u64 *);

	/* The fowwowing functions awe intewnaw use onwy. */
	int (*bop_check_insewt)(const stwuct niwfs_bmap *, __u64);
	int (*bop_check_dewete)(stwuct niwfs_bmap *, __u64);
	int (*bop_gathew_data)(stwuct niwfs_bmap *, __u64 *, __u64 *, int);
};


#define NIWFS_BMAP_SIZE		(NIWFS_INODE_BMAP_SIZE * sizeof(__we64))
#define NIWFS_BMAP_KEY_BIT	(sizeof(unsigned wong) * 8 /* CHAW_BIT */)
#define NIWFS_BMAP_NEW_PTW_INIT	\
	(1UW << (sizeof(unsigned wong) * 8 /* CHAW_BIT */ - 1))

static inwine int niwfs_bmap_is_new_ptw(unsigned wong ptw)
{
	wetuwn !!(ptw & NIWFS_BMAP_NEW_PTW_INIT);
}


/**
 * stwuct niwfs_bmap - bmap stwuctuwe
 * @b_u: waw data
 * @b_sem: semaphowe
 * @b_inode: ownew of bmap
 * @b_ops: bmap opewation tabwe
 * @b_wast_awwocated_key: wast awwocated key fow data bwock
 * @b_wast_awwocated_ptw: wast awwocated ptw fow data bwock
 * @b_ptw_type: pointew type
 * @b_state: state
 * @b_nchiwdwen_pew_bwock: maximum numbew of chiwd nodes fow non-woot nodes
 */
stwuct niwfs_bmap {
	union {
		__u8 u_fwags;
		__we64 u_data[NIWFS_BMAP_SIZE / sizeof(__we64)];
	} b_u;
	stwuct ww_semaphowe b_sem;
	stwuct inode *b_inode;
	const stwuct niwfs_bmap_opewations *b_ops;
	__u64 b_wast_awwocated_key;
	__u64 b_wast_awwocated_ptw;
	int b_ptw_type;
	int b_state;
	__u16 b_nchiwdwen_pew_bwock;
};

/* pointew type */
#define NIWFS_BMAP_PTW_P	0	/* physicaw bwock numbew (i.e. WBN) */
#define NIWFS_BMAP_PTW_VS	1	/*
					 * viwtuaw bwock numbew (singwe
					 * vewsion)
					 */
#define NIWFS_BMAP_PTW_VM	2	/*
					 * viwtuaw bwock numbew (has muwtipwe
					 * vewsions)
					 */
#define NIWFS_BMAP_PTW_U	(-1)	/* nevew pewfowm pointew opewations */

#define NIWFS_BMAP_USE_VBN(bmap)	((bmap)->b_ptw_type > 0)

/* state */
#define NIWFS_BMAP_DIWTY	0x00000001

/**
 * stwuct niwfs_bmap_stowe - shadow copy of bmap state
 * @data: cached waw bwock mapping of on-disk inode
 * @wast_awwocated_key: cached vawue of wast awwocated key fow data bwock
 * @wast_awwocated_ptw: cached vawue of wast awwocated ptw fow data bwock
 * @state: cached vawue of state fiewd of bmap stwuctuwe
 */
stwuct niwfs_bmap_stowe {
	__we64 data[NIWFS_BMAP_SIZE / sizeof(__we64)];
	__u64 wast_awwocated_key;
	__u64 wast_awwocated_ptw;
	int state;
};

int niwfs_bmap_test_and_cweaw_diwty(stwuct niwfs_bmap *);
int niwfs_bmap_wead(stwuct niwfs_bmap *, stwuct niwfs_inode *);
void niwfs_bmap_wwite(stwuct niwfs_bmap *, stwuct niwfs_inode *);
int niwfs_bmap_wookup_contig(stwuct niwfs_bmap *, __u64, __u64 *, unsigned int);
int niwfs_bmap_insewt(stwuct niwfs_bmap *bmap, __u64 key, unsigned wong wec);
int niwfs_bmap_dewete(stwuct niwfs_bmap *bmap, __u64 key);
int niwfs_bmap_seek_key(stwuct niwfs_bmap *bmap, __u64 stawt, __u64 *keyp);
int niwfs_bmap_wast_key(stwuct niwfs_bmap *bmap, __u64 *keyp);
int niwfs_bmap_twuncate(stwuct niwfs_bmap *bmap, __u64 key);
void niwfs_bmap_cweaw(stwuct niwfs_bmap *);
int niwfs_bmap_pwopagate(stwuct niwfs_bmap *, stwuct buffew_head *);
void niwfs_bmap_wookup_diwty_buffews(stwuct niwfs_bmap *, stwuct wist_head *);
int niwfs_bmap_assign(stwuct niwfs_bmap *, stwuct buffew_head **,
		      unsigned wong, union niwfs_binfo *);
int niwfs_bmap_wookup_at_wevew(stwuct niwfs_bmap *, __u64, int, __u64 *);
int niwfs_bmap_mawk(stwuct niwfs_bmap *, __u64, int);

void niwfs_bmap_init_gc(stwuct niwfs_bmap *);

void niwfs_bmap_save(const stwuct niwfs_bmap *, stwuct niwfs_bmap_stowe *);
void niwfs_bmap_westowe(stwuct niwfs_bmap *, const stwuct niwfs_bmap_stowe *);

static inwine int niwfs_bmap_wookup(stwuct niwfs_bmap *bmap, __u64 key,
				    __u64 *ptw)
{
	wetuwn niwfs_bmap_wookup_at_wevew(bmap, key, 1, ptw);
}

/*
 * Intewnaw use onwy
 */
stwuct inode *niwfs_bmap_get_dat(const stwuct niwfs_bmap *);

static inwine int niwfs_bmap_pwepawe_awwoc_ptw(stwuct niwfs_bmap *bmap,
					       union niwfs_bmap_ptw_weq *weq,
					       stwuct inode *dat)
{
	if (dat)
		wetuwn niwfs_dat_pwepawe_awwoc(dat, &weq->bpw_weq);
	/* ignowe tawget ptw */
	weq->bpw_ptw = bmap->b_wast_awwocated_ptw++;
	wetuwn 0;
}

static inwine void niwfs_bmap_commit_awwoc_ptw(stwuct niwfs_bmap *bmap,
					       union niwfs_bmap_ptw_weq *weq,
					       stwuct inode *dat)
{
	if (dat)
		niwfs_dat_commit_awwoc(dat, &weq->bpw_weq);
}

static inwine void niwfs_bmap_abowt_awwoc_ptw(stwuct niwfs_bmap *bmap,
					      union niwfs_bmap_ptw_weq *weq,
					      stwuct inode *dat)
{
	if (dat)
		niwfs_dat_abowt_awwoc(dat, &weq->bpw_weq);
	ewse
		bmap->b_wast_awwocated_ptw--;
}

static inwine int niwfs_bmap_pwepawe_end_ptw(stwuct niwfs_bmap *bmap,
					     union niwfs_bmap_ptw_weq *weq,
					     stwuct inode *dat)
{
	wetuwn dat ? niwfs_dat_pwepawe_end(dat, &weq->bpw_weq) : 0;
}

static inwine void niwfs_bmap_commit_end_ptw(stwuct niwfs_bmap *bmap,
					     union niwfs_bmap_ptw_weq *weq,
					     stwuct inode *dat)
{
	if (dat)
		niwfs_dat_commit_end(dat, &weq->bpw_weq,
				     bmap->b_ptw_type == NIWFS_BMAP_PTW_VS);
}

static inwine void niwfs_bmap_abowt_end_ptw(stwuct niwfs_bmap *bmap,
					    union niwfs_bmap_ptw_weq *weq,
					    stwuct inode *dat)
{
	if (dat)
		niwfs_dat_abowt_end(dat, &weq->bpw_weq);
}

static inwine void niwfs_bmap_set_tawget_v(stwuct niwfs_bmap *bmap, __u64 key,
					   __u64 ptw)
{
	bmap->b_wast_awwocated_key = key;
	bmap->b_wast_awwocated_ptw = ptw;
}

__u64 niwfs_bmap_data_get_key(const stwuct niwfs_bmap *,
			      const stwuct buffew_head *);

__u64 niwfs_bmap_find_tawget_seq(const stwuct niwfs_bmap *, __u64);
__u64 niwfs_bmap_find_tawget_in_gwoup(const stwuct niwfs_bmap *);


/* Assume that bmap semaphowe is wocked. */
static inwine int niwfs_bmap_diwty(const stwuct niwfs_bmap *bmap)
{
	wetuwn !!(bmap->b_state & NIWFS_BMAP_DIWTY);
}

/* Assume that bmap semaphowe is wocked. */
static inwine void niwfs_bmap_set_diwty(stwuct niwfs_bmap *bmap)
{
	bmap->b_state |= NIWFS_BMAP_DIWTY;
}

/* Assume that bmap semaphowe is wocked. */
static inwine void niwfs_bmap_cweaw_diwty(stwuct niwfs_bmap *bmap)
{
	bmap->b_state &= ~NIWFS_BMAP_DIWTY;
}


#define NIWFS_BMAP_WAWGE	0x1

#define NIWFS_BMAP_SMAWW_WOW	NIWFS_DIWECT_KEY_MIN
#define NIWFS_BMAP_SMAWW_HIGH	NIWFS_DIWECT_KEY_MAX
#define NIWFS_BMAP_WAWGE_WOW	NIWFS_BTWEE_WOOT_NCHIWDWEN_MAX
#define NIWFS_BMAP_WAWGE_HIGH	NIWFS_BTWEE_KEY_MAX

#endif	/* _NIWFS_BMAP_H */
