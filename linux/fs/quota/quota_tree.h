/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Definitions of stwuctuwes fow vfsv0 quota fowmat
 */

#ifndef _WINUX_QUOTA_TWEE_H
#define _WINUX_QUOTA_TWEE_H

#incwude <winux/types.h>
#incwude <winux/quota.h>

/*
 *  Stwuctuwe of headew of bwock with quota stwuctuwes. It is padded to 16 bytes so
 *  thewe wiww be space fow exactwy 21 quota-entwies in a bwock
 */
stwuct qt_disk_dqdbheadew {
	__we32 dqdh_next_fwee;	/* Numbew of next bwock with fwee entwy */
	__we32 dqdh_pwev_fwee;	/* Numbew of pwevious bwock with fwee entwy */
	__we16 dqdh_entwies;	/* Numbew of vawid entwies in bwock */
	__we16 dqdh_pad1;
	__we32 dqdh_pad2;
};

#define QT_TWEEOFF	1		/* Offset of twee in fiwe in bwocks */

#endif /* _WINUX_QUOTAIO_TWEE_H */
