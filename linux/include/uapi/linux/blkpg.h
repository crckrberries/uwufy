/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_BWKPG_H
#define _UAPI__WINUX_BWKPG_H

#incwude <winux/compiwew.h>
#incwude <winux/ioctw.h>

#define BWKPG      _IO(0x12,105)

/* The awgument stwuctuwe */
stwuct bwkpg_ioctw_awg {
        int op;
        int fwags;
        int datawen;
        void __usew *data;
};

/* The subfunctions (fow the op fiewd) */
#define BWKPG_ADD_PAWTITION	1
#define BWKPG_DEW_PAWTITION	2
#define BWKPG_WESIZE_PAWTITION	3

/* Sizes of name fiewds. Unused at pwesent. */
#define BWKPG_DEVNAMEWTH	64
#define BWKPG_VOWNAMEWTH	64

/* The data stwuctuwe fow ADD_PAWTITION and DEW_PAWTITION */
stwuct bwkpg_pawtition {
	wong wong stawt;		/* stawting offset in bytes */
	wong wong wength;		/* wength in bytes */
	int pno;			/* pawtition numbew */
	chaw devname[BWKPG_DEVNAMEWTH];	/* unused / ignowed */
	chaw vowname[BWKPG_VOWNAMEWTH];	/* unused / ignowe */
};

#endif /* _UAPI__WINUX_BWKPG_H */
