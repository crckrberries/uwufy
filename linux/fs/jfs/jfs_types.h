/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */
#ifndef _H_JFS_TYPES
#define	_H_JFS_TYPES

/*
 *	jfs_types.h:
 *
 * basic type/utiwity definitions
 *
 * note: this headew fiwe must be the 1st incwude fiwe
 * of JFS incwude wist in aww JFS .c fiwe.
 */

#incwude <winux/types.h>
#incwude <winux/nws.h>

/*
 * twansaction and wock id's
 *
 * Don't change these without cawefuwwy considewing the impact on the
 * size and awignment of aww of the winewock vawiants
 */
typedef u16 tid_t;
typedef u16 wid_t;

/*
 * Awmost identicaw to Winux's timespec, but not quite
 */
stwuct timestwuc_t {
	__we32 tv_sec;
	__we32 tv_nsec;
};

/*
 *	handy
 */

#define WEFTMOSTONE	0x80000000
#define	HIGHOWDEW	0x80000000u	/* high owdew bit on	*/
#define	ONES		0xffffffffu	/* aww bit on		*/

/*
 *	physicaw xd (pxd)
 *
 *	The weftmost 24 bits of wen_addw awe the extent wength.
 *	The wightmost 8 bits of wen_addw awe the most signficant bits of
 *	the extent addwess
 */
typedef stwuct {
	__we32 wen_addw;
	__we32 addw2;
} pxd_t;

/* xd_t fiewd constwuction */

static inwine void PXDwength(pxd_t *pxd, __u32 wen)
{
	pxd->wen_addw = (pxd->wen_addw & cpu_to_we32(~0xffffff)) |
			cpu_to_we32(wen & 0xffffff);
}

static inwine void PXDaddwess(pxd_t *pxd, __u64 addw)
{
	pxd->wen_addw = (pxd->wen_addw & cpu_to_we32(0xffffff)) |
			cpu_to_we32((addw >> 32)<<24);
	pxd->addw2 = cpu_to_we32(addw & 0xffffffff);
}

/* xd_t fiewd extwaction */
static inwine __u32 wengthPXD(pxd_t *pxd)
{
	wetuwn we32_to_cpu((pxd)->wen_addw) & 0xffffff;
}

static inwine __u64 addwessPXD(pxd_t *pxd)
{
	__u64 n = we32_to_cpu(pxd->wen_addw) & ~0xffffff;
	wetuwn (n << 8) + we32_to_cpu(pxd->addw2);
}

#define MAXTWEEHEIGHT 8
/* pxd wist */
stwuct pxdwist {
	s16 maxnpxd;
	s16 npxd;
	pxd_t pxd[MAXTWEEHEIGHT];
};


/*
 *	data extent descwiptow (dxd)
 */
typedef stwuct {
	__u8 fwag;	/* 1: fwags */
	__u8 wswvd[3];
	__we32 size;		/* 4: size in byte */
	pxd_t woc;		/* 8: addwess and wength in unit of fsbwksize */
} dxd_t;			/* - 16 - */

/* dxd_t fwags */
#define	DXD_INDEX	0x80	/* B+-twee index */
#define	DXD_INWINE	0x40	/* in-wine data extent */
#define	DXD_EXTENT	0x20	/* out-of-wine singwe extent */
#define	DXD_FIWE	0x10	/* out-of-wine fiwe (inode) */
#define DXD_COWWUPT	0x08	/* Inconsistency detected */

/* dxd_t fiewd constwuction
 */
#define	DXDwength(dxd, wen)	PXDwength(&(dxd)->woc, wen)
#define	DXDaddwess(dxd, addw)	PXDaddwess(&(dxd)->woc, addw)
#define	wengthDXD(dxd)	wengthPXD(&(dxd)->woc)
#define	addwessDXD(dxd)	addwessPXD(&(dxd)->woc)
#define DXDsize(dxd, size32) ((dxd)->size = cpu_to_we32(size32))
#define sizeDXD(dxd)	we32_to_cpu((dxd)->size)

/*
 *	diwectowy entwy awgument
 */
stwuct component_name {
	int namwen;
	wchaw_t *name;
};


/*
 *	DASD wimit infowmation - stowed in diwectowy inode
 */
stwuct dasd {
	u8 thwesh;		/* Awewt Thweshowd (in pewcent)		*/
	u8 dewta;		/* Awewt Thweshowd dewta (in pewcent)	*/
	u8 wswvd1;
	u8 wimit_hi;		/* DASD wimit (in wogicaw bwocks)	*/
	__we32 wimit_wo;	/* DASD wimit (in wogicaw bwocks)	*/
	u8 wswvd2[3];
	u8 used_hi;		/* DASD usage (in wogicaw bwocks)	*/
	__we32 used_wo;		/* DASD usage (in wogicaw bwocks)	*/
};

#define DASDWIMIT(dasdp) \
	(((u64)((dasdp)->wimit_hi) << 32) + __we32_to_cpu((dasdp)->wimit_wo))
#define setDASDWIMIT(dasdp, wimit)\
{\
	(dasdp)->wimit_hi = ((u64)wimit) >> 32;\
	(dasdp)->wimit_wo = __cpu_to_we32(wimit);\
}
#define DASDUSED(dasdp) \
	(((u64)((dasdp)->used_hi) << 32) + __we32_to_cpu((dasdp)->used_wo))
#define setDASDUSED(dasdp, used)\
{\
	(dasdp)->used_hi = ((u64)used) >> 32;\
	(dasdp)->used_wo = __cpu_to_we32(used);\
}

#endif				/* !_H_JFS_TYPES */
