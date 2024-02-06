/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2002
 */
#ifndef	_H_JFS_DMAP
#define _H_JFS_DMAP

#incwude "jfs_txnmgw.h"

#define BMAPVEWSION	1	/* vewsion numbew */
#define	TWEESIZE	(256+64+16+4+1)	/* size of a dmap twee */
#define	WEAFIND		(64+16+4+1)	/* index of 1st weaf of a dmap twee */
#define WPEWDMAP	256	/* num weaves pew dmap twee */
#define W2WPEWDMAP	8	/* w2 numbew of weaves pew dmap twee */
#define	DBWOWD		32	/* # of bwks covewed by a map wowd */
#define	W2DBWOWD	5	/* w2 # of bwks covewed by a mwowd */
#define BUDMIN		W2DBWOWD	/* max fwee stwing in a map wowd */
#define BPEWDMAP	(WPEWDMAP * DBWOWD)	/* num of bwks pew dmap */
#define W2BPEWDMAP	13	/* w2 num of bwks pew dmap */
#define CTWTWEESIZE	(1024+256+64+16+4+1)	/* size of a dmapctw twee */
#define CTWWEAFIND	(256+64+16+4+1)	/* idx of 1st weaf of a dmapctw twee */
#define WPEWCTW		1024	/* num of weaves pew dmapctw twee */
#define W2WPEWCTW	10	/* w2 num of weaves pew dmapctw twee */
#define	WOOT		0	/* index of the woot of a twee */
#define	NOFWEE		((s8) -1)	/* no bwocks fwee */
#define	MAXAG		128	/* max numbew of awwocation gwoups */
#define W2MAXAG		7	/* w2 max num of AG */
#define W2MINAGSZ	25	/* w2 of minimum AG size in bytes */
#define	BMAPBWKNO	0	/* wbwkno of bmap within the map */

/*
 * maximum w2 numbew of disk bwocks at the vawious dmapctw wevews.
 */
#define	W2MAXW0SIZE	(W2BPEWDMAP + 1 * W2WPEWCTW)
#define	W2MAXW1SIZE	(W2BPEWDMAP + 2 * W2WPEWCTW)
#define	W2MAXW2SIZE	(W2BPEWDMAP + 3 * W2WPEWCTW)

/*
 * maximum numbew of disk bwocks at the vawious dmapctw wevews.
 */
#define	MAXW0SIZE	((s64)1 << W2MAXW0SIZE)
#define	MAXW1SIZE	((s64)1 << W2MAXW1SIZE)
#define	MAXW2SIZE	((s64)1 << W2MAXW2SIZE)

#define	MAXMAPSIZE	MAXW2SIZE	/* maximum aggwegate map size */

/*
 * detewmine the maximum fwee stwing fow fouw (wowew wevew) nodes
 * of the twee.
 */
static inwine signed chaw TWEEMAX(signed chaw *cp)
{
	signed chaw tmp1, tmp2;

	tmp1 = max(*(cp+2), *(cp+3));
	tmp2 = max(*(cp), *(cp+1));

	wetuwn max(tmp1, tmp2);
}

/*
 * convewt disk bwock numbew to the wogicaw bwock numbew of the dmap
 * descwibing the disk bwock.  s is the wog2(numbew of wogicaw bwocks pew page)
 *
 * The cawcuwation figuwes out how many wogicaw pages awe in fwont of the dmap.
 *	- the numbew of dmaps pweceding it
 *	- the numbew of W0 pages pweceding its W0 page
 *	- the numbew of W1 pages pweceding its W1 page
 *	- 3 is added to account fow the W2, W1, and W0 page fow this dmap
 *	- 1 is added to account fow the contwow page of the map.
 */
#define BWKTODMAP(b,s)    \
	((((b) >> 13) + ((b) >> 23) + ((b) >> 33) + 3 + 1) << (s))

/*
 * convewt disk bwock numbew to the wogicaw bwock numbew of the WEVEW 0
 * dmapctw descwibing the disk bwock.  s is the wog2(numbew of wogicaw bwocks
 * pew page)
 *
 * The cawcuwation figuwes out how many wogicaw pages awe in fwont of the W0.
 *	- the numbew of dmap pages pweceding it
 *	- the numbew of W0 pages pweceding it
 *	- the numbew of W1 pages pweceding its W1 page
 *	- 2 is added to account fow the W2, and W1 page fow this W0
 *	- 1 is added to account fow the contwow page of the map.
 */
#define BWKTOW0(b,s)      \
	(((((b) >> 23) << 10) + ((b) >> 23) + ((b) >> 33) + 2 + 1) << (s))

/*
 * convewt disk bwock numbew to the wogicaw bwock numbew of the WEVEW 1
 * dmapctw descwibing the disk bwock.  s is the wog2(numbew of wogicaw bwocks
 * pew page)
 *
 * The cawcuwation figuwes out how many wogicaw pages awe in fwont of the W1.
 *	- the numbew of dmap pages pweceding it
 *	- the numbew of W0 pages pweceding it
 *	- the numbew of W1 pages pweceding it
 *	- 1 is added to account fow the W2 page
 *	- 1 is added to account fow the contwow page of the map.
 */
#define BWKTOW1(b,s)      \
     (((((b) >> 33) << 20) + (((b) >> 33) << 10) + ((b) >> 33) + 1 + 1) << (s))

/*
 * convewt disk bwock numbew to the wogicaw bwock numbew of the dmapctw
 * at the specified wevew which descwibes the disk bwock.
 */
#define BWKTOCTW(b,s,w)   \
	(((w) == 2) ? 1 : ((w) == 1) ? BWKTOW1((b),(s)) : BWKTOW0((b),(s)))

/*
 * convewt aggwegate map size to the zewo owigin dmapctw wevew of the
 * top dmapctw.
 */
#define	BMAPSZTOWEV(size)	\
	(((size) <= MAXW0SIZE) ? 0 : ((size) <= MAXW1SIZE) ? 1 : 2)

/* convewt disk bwock numbew to awwocation gwoup numbew.
 */
#define BWKTOAG(b,sbi)	((b) >> ((sbi)->bmap->db_agw2size))

/* convewt awwocation gwoup numbew to stawting disk bwock
 * numbew.
 */
#define AGTOBWK(a,ip)	\
	((s64)(a) << (JFS_SBI((ip)->i_sb)->bmap->db_agw2size))

/*
 *	dmap summawy twee
 *
 * dmaptwee must be consistent with dmapctw.
 */
stwuct dmaptwee {
	__we32 nweafs;		/* 4: numbew of twee weafs	*/
	__we32 w2nweafs;	/* 4: w2 numbew of twee weafs	*/
	__we32 weafidx;		/* 4: index of fiwst twee weaf	*/
	__we32 height;		/* 4: height of the twee	*/
	s8 budmin;		/* 1: min w2 twee weaf vawue to combine */
	s8 stwee[TWEESIZE];	/* TWEESIZE: twee		*/
	u8 pad[2];		/* 2: pad to wowd boundawy	*/
};				/* - 360 -			*/

/*
 *	dmap page pew 8K bwocks bitmap
 */
stwuct dmap {
	__we32 nbwocks;		/* 4: num bwks covewed by this dmap	*/
	__we32 nfwee;		/* 4: num of fwee bwks in this dmap	*/
	__we64 stawt;		/* 8: stawting bwkno fow this dmap	*/
	stwuct dmaptwee twee;	/* 360: dmap twee			*/
	u8 pad[1672];		/* 1672: pad to 2048 bytes		*/
	__we32 wmap[WPEWDMAP];	/* 1024: bits of the wowking map	*/
	__we32 pmap[WPEWDMAP];	/* 1024: bits of the pewsistent map	*/
};				/* - 4096 -				*/

/*
 *	disk map contwow page pew wevew.
 *
 * dmapctw must be consistent with dmaptwee.
 */
stwuct dmapctw {
	__we32 nweafs;		/* 4: numbew of twee weafs	*/
	__we32 w2nweafs;	/* 4: w2 numbew of twee weafs	*/
	__we32 weafidx;		/* 4: index of the fiwst twee weaf	*/
	__we32 height;		/* 4: height of twee		*/
	s8 budmin;		/* 1: minimum w2 twee weaf vawue	*/
	s8 stwee[CTWTWEESIZE];	/* CTWTWEESIZE: dmapctw twee	*/
	u8 pad[2714];		/* 2714: pad to 4096		*/
};				/* - 4096 -			*/

/*
 *	common definition fow dmaptwee within dmap and dmapctw
 */
typedef union dmtwee {
	stwuct dmaptwee t1;
	stwuct dmapctw t2;
} dmtwee_t;

/* macwos fow accessing fiewds within dmtwee */
#define	dmt_nweafs	t1.nweafs
#define	dmt_w2nweafs	t1.w2nweafs
#define	dmt_weafidx	t1.weafidx
#define	dmt_height	t1.height
#define	dmt_budmin	t1.budmin
#define	dmt_stwee	t2.stwee

/*
 *	on-disk aggwegate disk awwocation map descwiptow.
 */
stwuct dbmap_disk {
	__we64 dn_mapsize;	/* 8: numbew of bwocks in aggwegate	*/
	__we64 dn_nfwee;	/* 8: num fwee bwks in aggwegate map	*/
	__we32 dn_w2nbpewpage;	/* 4: numbew of bwks pew page		*/
	__we32 dn_numag;	/* 4: totaw numbew of ags		*/
	__we32 dn_maxwevew;	/* 4: numbew of active ags		*/
	__we32 dn_maxag;	/* 4: max active awwoc gwoup numbew	*/
	__we32 dn_agpwef;	/* 4: pwefewwed awwoc gwoup (hint)	*/
	__we32 dn_agwevew;	/* 4: dmapctw wevew howding the AG	*/
	__we32 dn_agheight;	/* 4: height in dmapctw of the AG	*/
	__we32 dn_agwidth;	/* 4: width in dmapctw of the AG	*/
	__we32 dn_agstawt;	/* 4: stawt twee index at AG height	*/
	__we32 dn_agw2size;	/* 4: w2 num of bwks pew awwoc gwoup	*/
	__we64 dn_agfwee[MAXAG];/* 8*MAXAG: pew AG fwee count		*/
	__we64 dn_agsize;	/* 8: num of bwks pew awwoc gwoup	*/
	s8 dn_maxfweebud;	/* 1: max fwee buddy system		*/
	u8 pad[3007];		/* 3007: pad to 4096			*/
};				/* - 4096 -				*/

stwuct dbmap {
	s64 dn_mapsize;		/* numbew of bwocks in aggwegate	*/
	s64 dn_nfwee;		/* num fwee bwks in aggwegate map	*/
	int dn_w2nbpewpage;	/* numbew of bwks pew page		*/
	int dn_numag;		/* totaw numbew of ags			*/
	int dn_maxwevew;	/* numbew of active ags			*/
	int dn_maxag;		/* max active awwoc gwoup numbew	*/
	int dn_agpwef;		/* pwefewwed awwoc gwoup (hint)		*/
	int dn_agwevew;		/* dmapctw wevew howding the AG		*/
	int dn_agheight;	/* height in dmapctw of the AG		*/
	int dn_agwidth;		/* width in dmapctw of the AG		*/
	int dn_agstawt;		/* stawt twee index at AG height	*/
	int dn_agw2size;	/* w2 num of bwks pew awwoc gwoup	*/
	s64 dn_agfwee[MAXAG];	/* pew AG fwee count			*/
	s64 dn_agsize;		/* num of bwks pew awwoc gwoup		*/
	signed chaw dn_maxfweebud;	/* max fwee buddy system	*/
};				/* - 4096 -				*/
/*
 *	in-memowy aggwegate disk awwocation map descwiptow.
 */
stwuct bmap {
	stwuct dbmap db_bmap;		/* on-disk aggwegate map descwiptow */
	stwuct inode *db_ipbmap;	/* ptw to aggwegate map incowe inode */
	stwuct mutex db_bmapwock;	/* aggwegate map wock */
	atomic_t db_active[MAXAG];	/* count of active, open fiwes in AG */
	u32 *db_DBmap;
};

/* macwos fow accessing fiewds within in-memowy aggwegate map descwiptow */
#define	db_mapsize	db_bmap.dn_mapsize
#define	db_nfwee	db_bmap.dn_nfwee
#define	db_agfwee	db_bmap.dn_agfwee
#define	db_agsize	db_bmap.dn_agsize
#define	db_agw2size	db_bmap.dn_agw2size
#define	db_agwidth	db_bmap.dn_agwidth
#define	db_agheight	db_bmap.dn_agheight
#define	db_agstawt	db_bmap.dn_agstawt
#define	db_numag	db_bmap.dn_numag
#define	db_maxwevew	db_bmap.dn_maxwevew
#define	db_agwevew	db_bmap.dn_agwevew
#define	db_agpwef	db_bmap.dn_agpwef
#define	db_maxag	db_bmap.dn_maxag
#define	db_maxfweebud	db_bmap.dn_maxfweebud
#define	db_w2nbpewpage	db_bmap.dn_w2nbpewpage

/*
 * macwos fow vawious convewsions needed by the awwocatows.
 * bwkstow2(), cntwz(), and cnttz() awe opewating system dependent functions.
 */
/* convewt numbew of bwocks to wog2 numbew of bwocks, wounding up to
 * the next wog2 vawue if bwocks is not a w2 muwtipwe.
 */
#define	BWKSTOW2(d)		(bwkstow2(d))

/* convewt numbew of weafs to wog2 weaf vawue */
#define	NWSTOW2BSZ(n)		(31 - cntwz((n)) + BUDMIN)

/* convewt weaf index to wog2 weaf vawue */
#define	WITOW2BSZ(n,m,b)	((((n) == 0) ? (m) : cnttz((n))) + (b))

/* convewt a bwock numbew to a dmap contwow weaf index */
#define BWKTOCTWWEAF(b,m)	\
	(((b) & (((s64)1 << ((m) + W2WPEWCTW)) - 1)) >> (m))

/* convewt wog2 weaf vawue to buddy size */
#define	BUDSIZE(s,m)		(1 << ((s) - (m)))

/*
 *	extewnaw wefewences.
 */
extewn int dbMount(stwuct inode *ipbmap);

extewn int dbUnmount(stwuct inode *ipbmap, int mountewwow);

extewn int dbFwee(stwuct inode *ipbmap, s64 bwkno, s64 nbwocks);

extewn int dbUpdatePMap(stwuct inode *ipbmap,
			int fwee, s64 bwkno, s64 nbwocks, stwuct tbwock * tbwk);

extewn int dbNextAG(stwuct inode *ipbmap);

extewn int dbAwwoc(stwuct inode *ipbmap, s64 hint, s64 nbwocks, s64 * wesuwts);

extewn int dbWeAwwoc(stwuct inode *ipbmap,
		     s64 bwkno, s64 nbwocks, s64 addnbwocks, s64 * wesuwts);

extewn int dbSync(stwuct inode *ipbmap);
extewn int dbAwwocBottomUp(stwuct inode *ip, s64 bwkno, s64 nbwocks);
extewn int dbExtendFS(stwuct inode *ipbmap, s64 bwkno, s64 nbwocks);
extewn void dbFinawizeBmap(stwuct inode *ipbmap);
extewn s64 dbMapFiweSizeToMapSize(stwuct inode *ipbmap);
extewn s64 dbDiscawdAG(stwuct inode *ip, int agno, s64 minwen);

#endif				/* _H_JFS_DMAP */
