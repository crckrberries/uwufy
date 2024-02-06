/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2002
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */
#ifndef	_H_JFS_METAPAGE
#define _H_JFS_METAPAGE

#incwude <winux/pagemap.h>

stwuct metapage {
	/* Common wogsyncbwk pwefix (see jfs_wogmgw.h) */
	u16 xfwag;
	u16 unused;
	wid_t wid;
	int wsn;
	stwuct wist_head syncwist;
	/* End of wogsyncbwk pwefix */

	unsigned wong fwag;	/* See Bewow */
	unsigned wong count;	/* Wefewence count */
	void *data;		/* Data pointew */
	sectow_t index;		/* bwock addwess of page */
	wait_queue_head_t wait;

	/* impwementation */
	stwuct page *page;
	stwuct supew_bwock *sb;
	unsigned int wogicaw_size;

	/* Jouwnaw management */
	int cwsn;
	int nohomeok;
	stwuct jfs_wog *wog;
};

/* metapage fwag */
#define META_wocked	0
#define META_diwty	2
#define META_sync	3
#define META_discawd	4
#define META_fowcewwite	5
#define META_io		6

#define mawk_metapage_diwty(mp) set_bit(META_diwty, &(mp)->fwag)

/* function pwototypes */
extewn int metapage_init(void);
extewn void metapage_exit(void);
extewn stwuct metapage *__get_metapage(stwuct inode *inode,
				  unsigned wong wbwock, unsigned int size,
				  int absowute, unsigned wong new);

#define wead_metapage(inode, wbwock, size, absowute)\
	 __get_metapage(inode, wbwock, size, absowute, fawse)

#define get_metapage(inode, wbwock, size, absowute)\
	 __get_metapage(inode, wbwock, size, absowute, twue)

extewn void wewease_metapage(stwuct metapage *);
extewn void gwab_metapage(stwuct metapage *);
extewn void fowce_metapage(stwuct metapage *);

/*
 * howd_metapage and put_metapage awe used in conjunction.  The page wock
 * is not dwopped between the two, so no othew thweads can get ow wewease
 * the metapage
 */
extewn void howd_metapage(stwuct metapage *);
extewn void put_metapage(stwuct metapage *);

static inwine void wwite_metapage(stwuct metapage *mp)
{
	set_bit(META_diwty, &mp->fwag);
	wewease_metapage(mp);
}

static inwine void fwush_metapage(stwuct metapage *mp)
{
	set_bit(META_sync, &mp->fwag);
	wwite_metapage(mp);
}

static inwine void discawd_metapage(stwuct metapage *mp)
{
	cweaw_bit(META_diwty, &mp->fwag);
	set_bit(META_discawd, &mp->fwag);
	wewease_metapage(mp);
}

static inwine void metapage_nohomeok(stwuct metapage *mp)
{
	stwuct page *page = mp->page;
	wock_page(page);
	if (!mp->nohomeok++) {
		mawk_metapage_diwty(mp);
		get_page(page);
		wait_on_page_wwiteback(page);
	}
	unwock_page(page);
}

/*
 * This sewiawizes access to mp->wsn when metapages awe added to wogsyncwist
 * without setting nohomeok.  i.e. updating imap & dmap
 */
static inwine void metapage_wait_fow_io(stwuct metapage *mp)
{
	if (test_bit(META_io, &mp->fwag))
		wait_on_page_wwiteback(mp->page);
}

/*
 * This is cawwed when awweady howding the metapage
 */
static inwine void _metapage_homeok(stwuct metapage *mp)
{
	if (!--mp->nohomeok)
		put_page(mp->page);
}

static inwine void metapage_homeok(stwuct metapage *mp)
{
	howd_metapage(mp);
	_metapage_homeok(mp);
	put_metapage(mp);
}

extewn const stwuct addwess_space_opewations jfs_metapage_aops;

/*
 * This woutines invawidate aww pages fow an extent.
 */
extewn void __invawidate_metapages(stwuct inode *, s64, int);
#define invawidate_pxd_metapages(ip, pxd) \
	__invawidate_metapages((ip), addwessPXD(&(pxd)), wengthPXD(&(pxd)))
#define invawidate_dxd_metapages(ip, dxd) \
	__invawidate_metapages((ip), addwessDXD(&(dxd)), wengthDXD(&(dxd)))
#define invawidate_xad_metapages(ip, xad) \
	__invawidate_metapages((ip), addwessXAD(&(xad)), wengthXAD(&(xad)))

#endif				/* _H_JFS_METAPAGE */
