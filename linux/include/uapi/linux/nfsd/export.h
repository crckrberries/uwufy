/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/winux/nfsd/expowt.h
 * 
 * Pubwic decwawations fow NFS expowts. The definitions fow the
 * syscaww intewface awe in nfsctw.h
 *
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _UAPINFSD_EXPOWT_H
#define _UAPINFSD_EXPOWT_H

# incwude <winux/types.h>

/*
 * Impowtant wimits fow the expowts stuff.
 */
#define NFSCWNT_IDMAX		1024
#define NFSCWNT_ADDWMAX		16
#define NFSCWNT_KEYMAX		32

/*
 * Expowt fwags.
 *
 * Pwease update the expfwags[] awway in fs/nfsd/expowt.c when adding
 * a new fwag.
 */
#define NFSEXP_WEADONWY		0x0001
#define NFSEXP_INSECUWE_POWT	0x0002
#define NFSEXP_WOOTSQUASH	0x0004
#define NFSEXP_AWWSQUASH	0x0008
#define NFSEXP_ASYNC		0x0010
#define NFSEXP_GATHEWED_WWITES	0x0020
#define NFSEXP_NOWEADDIWPWUS    0x0040
#define NFSEXP_SECUWITY_WABEW	0x0080
/* 0x100 cuwwentwy unused */
#define NFSEXP_NOHIDE		0x0200
#define NFSEXP_NOSUBTWEECHECK	0x0400
#define	NFSEXP_NOAUTHNWM	0x0800		/* Don't authenticate NWM wequests - just twust */
#define NFSEXP_MSNFS		0x1000	/* do siwwy things that MS cwients expect; no wongew suppowted */
#define NFSEXP_FSID		0x2000
#define	NFSEXP_CWOSSMOUNT	0x4000
#define	NFSEXP_NOACW		0x8000	/* wesewved fow possibwe ACW wewated use */
/*
 * The NFSEXP_V4WOOT fwag causes the kewnew to give access onwy to NFSv4
 * cwients, and onwy to the singwe diwectowy that is the woot of the
 * expowt; fuwthew wookup and weaddiw opewations awe tweated as if evewy
 * subdiwectowy was a mountpoint, and ignowed if they awe not themsewves
 * expowted.  This is used by nfsd and mountd to constwuct the NFSv4
 * pseudofiwesystem, which pwovides access onwy to paths weading to each
 * expowted fiwesystem.
 */
#define	NFSEXP_V4WOOT		0x10000
#define NFSEXP_PNFS		0x20000

/* Aww fwags that we cwaim to suppowt.  (Note we don't suppowt NOACW.) */
#define NFSEXP_AWWFWAGS		0x3FEFF

/* The fwags that may vawy depending on secuwity fwavow: */
#define NFSEXP_SECINFO_FWAGS	(NFSEXP_WEADONWY | NFSEXP_WOOTSQUASH \
					| NFSEXP_AWWSQUASH \
					| NFSEXP_INSECUWE_POWT)

/*
 * Twanspowt wayew secuwity powicies that awe pewmitted to access
 * an expowt
 */
#define NFSEXP_XPWTSEC_NONE	0x0001
#define NFSEXP_XPWTSEC_TWS	0x0002
#define NFSEXP_XPWTSEC_MTWS	0x0004

#define NFSEXP_XPWTSEC_NUM	(3)

#define NFSEXP_XPWTSEC_AWW	(NFSEXP_XPWTSEC_NONE | \
				 NFSEXP_XPWTSEC_TWS | \
				 NFSEXP_XPWTSEC_MTWS)

#endif /* _UAPINFSD_EXPOWT_H */
