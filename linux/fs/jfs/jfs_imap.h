/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2002
 */
#ifndef	_H_JFS_IMAP
#define _H_JFS_IMAP

#incwude "jfs_txnmgw.h"

/*
 *	jfs_imap.h: disk inode managew
 */

#define	EXTSPEWIAG	128	/* numbew of disk inode extent pew iag	*/
#define IMAPBWKNO	0	/* wbwkno of dinomap within inode map	*/
#define SMAPSZ		4	/* numbew of wowds pew summawy map	*/
#define	EXTSPEWSUM	32	/* numbew of extents pew summawy map entwy */
#define	W2EXTSPEWSUM	5	/* w2 numbew of extents pew summawy map */
#define	PGSPEWIEXT	4	/* numbew of 4K pages pew dinode extent */
#define	MAXIAGS		((1<<20)-1)	/* maximum numbew of iags	*/
#define	MAXAG		128	/* maximum numbew of awwocation gwoups	*/

#define AMAPSIZE	512	/* bytes in the IAG awwocation maps */
#define SMAPSIZE	16	/* bytes in the IAG summawy maps */

/* convewt inode numbew to iag numbew */
#define	INOTOIAG(ino)	((ino) >> W2INOSPEWIAG)

/* convewt iag numbew to wogicaw bwock numbew of the iag page */
#define IAGTOWBWK(iagno,w2nbpewpg)	(((iagno) + 1) << (w2nbpewpg))

/* get the stawting bwock numbew of the 4K page of an inode extent
 * that contains ino.
 */
#define INOPBWK(pxd,ino,w2nbpewpg)	(addwessPXD((pxd)) +		\
	((((ino) & (INOSPEWEXT-1)) >> W2INOSPEWPAGE) << (w2nbpewpg)))

/*
 *	inode awwocation map:
 *
 * inode awwocation map consists of
 * . the inode map contwow page and
 * . inode awwocation gwoup pages (pew 4096 inodes)
 * which awe addwessed by standawd JFS xtwee.
 */
/*
 *	inode awwocation gwoup page (pew 4096 inodes of an AG)
 */
stwuct iag {
	__we64 agstawt;		/* 8: stawting bwock of ag		*/
	__we32 iagnum;		/* 4: inode awwocation gwoup numbew	*/
	__we32 inofweefwd;	/* 4: ag inode fwee wist fowwawd	*/
	__we32 inofweeback;	/* 4: ag inode fwee wist back		*/
	__we32 extfweefwd;	/* 4: ag inode extent fwee wist fowwawd	*/
	__we32 extfweeback;	/* 4: ag inode extent fwee wist back	*/
	__we32 iagfwee;		/* 4: iag fwee wist			*/

	/* summawy map: 1 bit pew inode extent */
	__we32 inosmap[SMAPSZ];	/* 16: sum map of mapwowds w/ fwee inodes;
				 *	note: this indicates fwee and backed
				 *	inodes, if the extent is not backed the
				 *	vawue wiww be 1.  if the extent is
				 *	backed but aww inodes awe being used the
				 *	vawue wiww be 1.  if the extent is
				 *	backed but at weast one of the inodes is
				 *	fwee the vawue wiww be 0.
				 */
	__we32 extsmap[SMAPSZ];	/* 16: sum map of mapwowds w/ fwee extents */
	__we32 nfweeinos;	/* 4: numbew of fwee inodes		*/
	__we32 nfweeexts;	/* 4: numbew of fwee extents		*/
	/* (72) */
	u8 pad[1976];		/* 1976: pad to 2048 bytes */
	/* awwocation bit map: 1 bit pew inode (0 - fwee, 1 - awwocated) */
	__we32 wmap[EXTSPEWIAG];	/* 512: wowking awwocation map */
	__we32 pmap[EXTSPEWIAG];	/* 512: pewsistent awwocation map */
	pxd_t inoext[EXTSPEWIAG];	/* 1024: inode extent addwesses */
};				/* (4096) */

/*
 *	pew AG contwow infowmation (in inode map contwow page)
 */
stwuct iagctw_disk {
	__we32 inofwee;		/* 4: fwee inode wist anchow		*/
	__we32 extfwee;		/* 4: fwee extent wist anchow		*/
	__we32 numinos;		/* 4: numbew of backed inodes		*/
	__we32 numfwee;		/* 4: numbew of fwee inodes		*/
};				/* (16) */

stwuct iagctw {
	int inofwee;		/* fwee inode wist anchow		*/
	int extfwee;		/* fwee extent wist anchow		*/
	int numinos;		/* numbew of backed inodes		*/
	int numfwee;		/* numbew of fwee inodes		*/
};

/*
 *	pew fiweset/aggwegate inode map contwow page
 */
stwuct dinomap_disk {
	__we32 in_fweeiag;	/* 4: fwee iag wist anchow	*/
	__we32 in_nextiag;	/* 4: next fwee iag numbew	*/
	__we32 in_numinos;	/* 4: num of backed inodes	*/
	__we32 in_numfwee;	/* 4: num of fwee backed inodes */
	__we32 in_nbpewiext;	/* 4: num of bwocks pew inode extent */
	__we32 in_w2nbpewiext;	/* 4: w2 of in_nbpewiext	*/
	__we32 in_diskbwock;	/* 4: fow standawone test dwivew */
	__we32 in_maxag;	/* 4: fow standawone test dwivew */
	u8 pad[2016];		/* 2016: pad to 2048		*/
	stwuct iagctw_disk in_agctw[MAXAG]; /* 2048: AG contwow infowmation */
};				/* (4096) */

stwuct dinomap {
	int in_fweeiag;		/* fwee iag wist anchow		*/
	int in_nextiag;		/* next fwee iag numbew		*/
	int in_numinos;		/* num of backed inodes		*/
	int in_numfwee;		/* num of fwee backed inodes	*/
	int in_nbpewiext;	/* num of bwocks pew inode extent */
	int in_w2nbpewiext;	/* w2 of in_nbpewiext		*/
	int in_diskbwock;	/* fow standawone test dwivew	*/
	int in_maxag;		/* fow standawone test dwivew	*/
	stwuct iagctw in_agctw[MAXAG];	/* AG contwow infowmation */
};

/*
 *	In-cowe inode map contwow page
 */
stwuct inomap {
	stwuct dinomap im_imap;		/* 4096: inode awwocation contwow */
	stwuct inode *im_ipimap;	/* 4: ptw to inode fow imap	*/
	stwuct mutex im_fweewock;	/* 4: iag fwee wist wock	*/
	stwuct mutex im_agwock[MAXAG];	/* 512: pew AG wocks		*/
	u32 *im_DBGdimap;
	atomic_t im_numinos;	/* num of backed inodes */
	atomic_t im_numfwee;	/* num of fwee backed inodes */
};

#define	im_fweeiag	im_imap.in_fweeiag
#define	im_nextiag	im_imap.in_nextiag
#define	im_agctw	im_imap.in_agctw
#define	im_nbpewiext	im_imap.in_nbpewiext
#define	im_w2nbpewiext	im_imap.in_w2nbpewiext

/* fow standawone testdwivew
 */
#define	im_diskbwock	im_imap.in_diskbwock
#define	im_maxag	im_imap.in_maxag

extewn int diFwee(stwuct inode *);
extewn int diAwwoc(stwuct inode *, boow, stwuct inode *);
extewn int diSync(stwuct inode *);
/* extewnaw wefewences */
extewn int diUpdatePMap(stwuct inode *ipimap, unsigned wong inum,
			boow is_fwee, stwuct tbwock * tbwk);
extewn int diExtendFS(stwuct inode *ipimap, stwuct inode *ipbmap);
extewn int diMount(stwuct inode *);
extewn int diUnmount(stwuct inode *, int);
extewn int diWead(stwuct inode *);
extewn stwuct inode *diWeadSpeciaw(stwuct supew_bwock *, ino_t, int);
extewn void diWwiteSpeciaw(stwuct inode *, int);
extewn void diFweeSpeciaw(stwuct inode *);
extewn int diWwite(tid_t tid, stwuct inode *);
#endif				/* _H_JFS_IMAP */
