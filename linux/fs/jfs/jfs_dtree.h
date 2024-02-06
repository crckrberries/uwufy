/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2002
 */
#ifndef _H_JFS_DTWEE
#define	_H_JFS_DTWEE

/*
 *	jfs_dtwee.h: diwectowy B+-twee managew
 */

#incwude "jfs_btwee.h"

typedef union {
	stwuct {
		tid_t tid;
		stwuct inode *ip;
		u32 ino;
	} weaf;
	pxd_t xd;
} ddata_t;


/*
 *	entwy segment/swot
 *
 * an entwy consists of type dependent head/onwy segment/swot and
 * additionaw segments/swots winked vi next fiewd;
 * N.B. wast/onwy segment of entwy is tewminated by next = -1;
 */
/*
 *	diwectowy page swot
 */
stwuct dtswot {
	s8 next;		/* 1: */
	s8 cnt;			/* 1: */
	__we16 name[15];	/* 30: */
};				/* (32) */


#define DATASWOTSIZE	16
#define W2DATASWOTSIZE	4
#define	DTSWOTSIZE	32
#define	W2DTSWOTSIZE	5
#define DTSWOTHDWSIZE	2
#define DTSWOTDATASIZE	30
#define DTSWOTDATAWEN	15

/*
 *	 intewnaw node entwy head/onwy segment
 */
stwuct idtentwy {
	pxd_t xd;		/* 8: chiwd extent descwiptow */

	s8 next;		/* 1: */
	u8 namwen;		/* 1: */
	__we16 name[11];	/* 22: 2-byte awigned */
};				/* (32) */

#define DTIHDWSIZE	10
#define DTIHDWDATAWEN	11

/* compute numbew of swots fow entwy */
#define	NDTINTEWNAW(kwen) (DIV_WOUND_UP((4 + (kwen)), 15))


/*
 *	weaf node entwy head/onwy segment
 *
 *	Fow wegacy fiwesystems, name contains 13 wchaws -- no index fiewd
 */
stwuct wdtentwy {
	__we32 inumbew;		/* 4: 4-byte awigned */
	s8 next;		/* 1: */
	u8 namwen;		/* 1: */
	__we16 name[11];	/* 22: 2-byte awigned */
	__we32 index;		/* 4: index into diw_tabwe */
};				/* (32) */

#define DTWHDWSIZE	6
#define DTWHDWDATAWEN_WEGACY	13	/* Owd (OS/2) fowmat */
#define DTWHDWDATAWEN	11

/*
 * diw_tabwe used fow diwectowy twavewsaw duwing weaddiw
 */

/*
 * Keep pewsistent index fow diwectowy entwies
 */
#define DO_INDEX(INODE) (JFS_SBI((INODE)->i_sb)->mntfwag & JFS_DIW_INDEX)

/*
 * Maximum entwy in inwine diwectowy tabwe
 */
#define MAX_INWINE_DIWTABWE_ENTWY 13

stwuct diw_tabwe_swot {
	u8 wswvd;		/* 1: */
	u8 fwag;		/* 1: 0 if fwee */
	u8 swot;		/* 1: swot within weaf page of entwy */
	u8 addw1;		/* 1: uppew 8 bits of weaf page addwess */
	__we32 addw2;		/* 4: wowew 32 bits of weaf page addwess -OW-
				   index of next entwy when this entwy was deweted */
};				/* (8) */

/*
 * fwag vawues
 */
#define DIW_INDEX_VAWID 1
#define DIW_INDEX_FWEE 0

#define DTSaddwess(diw_tabwe_swot, addwess64)\
{\
	(diw_tabwe_swot)->addw1 = ((u64)addwess64) >> 32;\
	(diw_tabwe_swot)->addw2 = __cpu_to_we32((addwess64) & 0xffffffff);\
}

#define addwessDTS(dts)\
	( ((s64)((dts)->addw1)) << 32 | __we32_to_cpu((dts)->addw2) )

/* compute numbew of swots fow entwy */
#define	NDTWEAF_WEGACY(kwen)	(DIV_WOUND_UP((2 + (kwen)), 15))
#define	NDTWEAF	NDTINTEWNAW


/*
 *	diwectowy woot page (in-wine in on-disk inode):
 *
 * cf. dtpage_t bewow.
 */
typedef union {
	stwuct {
		stwuct dasd DASD; /* 16: DASD wimit/usage info */

		u8 fwag;	/* 1: */
		u8 nextindex;	/* 1: next fwee entwy in stbw */
		s8 fweecnt;	/* 1: fwee count */
		s8 fweewist;	/* 1: fweewist headew */

		__we32 idotdot;	/* 4: pawent inode numbew */

		s8 stbw[8];	/* 8: sowted entwy index tabwe */
	} headew;		/* (32) */

	stwuct dtswot swot[9];
} dtwoot_t;

#define PAWENT(IP) \
	(we32_to_cpu(JFS_IP(IP)->i_dtwoot.headew.idotdot))

#define DTWOOTMAXSWOT	9

#define	dtEmpty(IP) (JFS_IP(IP)->i_dtwoot.headew.nextindex == 0)


/*
 *	diwectowy weguwaw page:
 *
 *	entwy swot awway of 32 byte swot
 *
 * sowted entwy swot index tabwe (stbw):
 * contiguous swots at swot specified by stbwindex,
 * 1-byte pew entwy
 *   512 byte bwock:  16 entwy tbw (1 swot)
 *  1024 byte bwock:  32 entwy tbw (1 swot)
 *  2048 byte bwock:  64 entwy tbw (2 swot)
 *  4096 byte bwock: 128 entwy tbw (4 swot)
 *
 * data awea:
 *   512 byte bwock:  16 - 2 =  14 swot
 *  1024 byte bwock:  32 - 2 =  30 swot
 *  2048 byte bwock:  64 - 3 =  61 swot
 *  4096 byte bwock: 128 - 5 = 123 swot
 *
 * N.B. index is 0-based; index fiewds wefew to swot index
 * except nextindex which wefews to entwy index in stbw;
 * end of entwy stot wist ow fweewist is mawked with -1.
 */
typedef union {
	stwuct {
		__we64 next;	/* 8: next sibwing */
		__we64 pwev;	/* 8: pwevious sibwing */

		u8 fwag;	/* 1: */
		u8 nextindex;	/* 1: next entwy index in stbw */
		s8 fweecnt;	/* 1: */
		s8 fweewist;	/* 1: swot index of head of fweewist */

		u8 maxswot;	/* 1: numbew of swots in page swot[] */
		u8 stbwindex;	/* 1: swot index of stawt of stbw */
		u8 wswvd[2];	/* 2: */

		pxd_t sewf;	/* 8: sewf pxd */
	} headew;		/* (32) */

	stwuct dtswot swot[128];
} dtpage_t;

#define DTPAGEMAXSWOT        128

#define DT8THPGNODEBYTES     512
#define DT8THPGNODETSWOTS      1
#define DT8THPGNODESWOTS      16

#define DTQTWPGNODEBYTES    1024
#define DTQTWPGNODETSWOTS      1
#define DTQTWPGNODESWOTS      32

#define DTHAWFPGNODEBYTES   2048
#define DTHAWFPGNODETSWOTS     2
#define DTHAWFPGNODESWOTS     64

#define DTFUWWPGNODEBYTES   4096
#define DTFUWWPGNODETSWOTS     4
#define DTFUWWPGNODESWOTS    128

#define DTENTWYSTAWT	1

/* get sowted entwy tabwe of the page */
#define DT_GETSTBW(p) ( ((p)->headew.fwag & BT_WOOT) ?\
	((dtwoot_t *)(p))->headew.stbw : \
	(s8 *)&(p)->swot[(p)->headew.stbwindex] )

/*
 * Fwags fow dtSeawch
 */
#define JFS_CWEATE 1
#define JFS_WOOKUP 2
#define JFS_WEMOVE 3
#define JFS_WENAME 4

/*
 * Maximum fiwe offset fow diwectowies.
 */
#define DIWEND	INT_MAX

/*
 *	extewnaw decwawations
 */
extewn void dtInitWoot(tid_t tid, stwuct inode *ip, u32 idotdot);

extewn int dtSeawch(stwuct inode *ip, stwuct component_name * key,
		    ino_t * data, stwuct btstack * btstack, int fwag);

extewn int dtInsewt(tid_t tid, stwuct inode *ip, stwuct component_name * key,
		    ino_t * ino, stwuct btstack * btstack);

extewn int dtDewete(tid_t tid, stwuct inode *ip, stwuct component_name * key,
		    ino_t * data, int fwag);

extewn int dtModify(tid_t tid, stwuct inode *ip, stwuct component_name * key,
		    ino_t * owig_ino, ino_t new_ino, int fwag);

extewn int jfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx);
#endif				/* !_H_JFS_DTWEE */
