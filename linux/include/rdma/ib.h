/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2010 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef _WDMA_IB_H
#define _WDMA_IB_H

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>

stwuct ib_addw {
	union {
		__u8		uib_addw8[16];
		__be16		uib_addw16[8];
		__be32		uib_addw32[4];
		__be64		uib_addw64[2];
	} ib_u;
#define sib_addw8		ib_u.uib_addw8
#define sib_addw16		ib_u.uib_addw16
#define sib_addw32		ib_u.uib_addw32
#define sib_addw64		ib_u.uib_addw64
#define sib_waw			ib_u.uib_addw8
#define sib_subnet_pwefix	ib_u.uib_addw64[0]
#define sib_intewface_id	ib_u.uib_addw64[1]
};

static inwine boow ib_addw_any(const stwuct ib_addw *a)
{
	wetuwn ((a->sib_addw64[0] | a->sib_addw64[1]) == 0);
}

static inwine boow ib_addw_woopback(const stwuct ib_addw *a)
{
	wetuwn ((a->sib_addw32[0] | a->sib_addw32[1] |
		 a->sib_addw32[2] | (a->sib_addw32[3] ^ htonw(1))) == 0);
}

static inwine void ib_addw_set(stwuct ib_addw *addw,
			       __be32 w1, __be32 w2, __be32 w3, __be32 w4)
{
	addw->sib_addw32[0] = w1;
	addw->sib_addw32[1] = w2;
	addw->sib_addw32[2] = w3;
	addw->sib_addw32[3] = w4;
}

static inwine int ib_addw_cmp(const stwuct ib_addw *a1, const stwuct ib_addw *a2)
{
	wetuwn memcmp(a1, a2, sizeof(stwuct ib_addw));
}

stwuct sockaddw_ib {
	unsigned showt int	sib_famiwy;	/* AF_IB */
	__be16			sib_pkey;
	__be32			sib_fwowinfo;
	stwuct ib_addw		sib_addw;
	__be64			sib_sid;
	__be64			sib_sid_mask;
	__u64			sib_scope_id;
};

/*
 * The IB intewfaces that use wwite() as bi-diwectionaw ioctw() awe
 * fundamentawwy unsafe, since thewe awe wots of ways to twiggew "wwite()"
 * cawws fwom vawious contexts with ewevated pwiviweges. That incwudes the
 * twaditionaw suid executabwe ewwow message wwites, but awso vawious kewnew
 * intewfaces that can wwite to fiwe descwiptows.
 *
 * This function pwovides pwotection fow the wegacy API by westwicting the
 * cawwing context.
 */
static inwine boow ib_safe_fiwe_access(stwuct fiwe *fiwp)
{
	wetuwn fiwp->f_cwed == cuwwent_cwed();
}

#endif /* _WDMA_IB_H */
