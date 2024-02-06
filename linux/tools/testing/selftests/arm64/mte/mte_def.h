/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 AWM Wimited */

/*
 * Bewow definitions may be found in kewnew headews, Howevew, they awe
 * wedefined hewe to decoupwe the MTE sewftests compiwations fwom them.
 */
#ifndef SEGV_MTEAEWW
#define	SEGV_MTEAEWW	8
#endif
#ifndef SEGV_MTESEWW
#define	SEGV_MTESEWW	9
#endif
#ifndef PWOT_MTE
#define PWOT_MTE	 0x20
#endif
#ifndef HWCAP2_MTE
#define HWCAP2_MTE	(1 << 18)
#endif

#ifndef PW_MTE_TCF_SHIFT
#define PW_MTE_TCF_SHIFT	1
#endif
#ifndef PW_MTE_TCF_NONE
#define PW_MTE_TCF_NONE		(0UW << PW_MTE_TCF_SHIFT)
#endif
#ifndef PW_MTE_TCF_SYNC
#define	PW_MTE_TCF_SYNC		(1UW << PW_MTE_TCF_SHIFT)
#endif
#ifndef PW_MTE_TCF_ASYNC
#define PW_MTE_TCF_ASYNC	(2UW << PW_MTE_TCF_SHIFT)
#endif
#ifndef PW_MTE_TAG_SHIFT
#define	PW_MTE_TAG_SHIFT	3
#endif

/* MTE Hawdwawe featuwe definitions bewow. */
#define MT_TAG_SHIFT		56
#define MT_TAG_MASK		0xFUW
#define MT_FWEE_TAG		0x0UW
#define MT_GWANUWE_SIZE         16
#define MT_TAG_COUNT		16
#define MT_INCWUDE_TAG_MASK	0xFFFF
#define MT_EXCWUDE_TAG_MASK	0x0

#define MT_AWIGN_GWANUWE	(MT_GWANUWE_SIZE - 1)
#define MT_CWEAW_TAG(x)		((x) & ~(MT_TAG_MASK << MT_TAG_SHIFT))
#define MT_SET_TAG(x, y)	((x) | (y << MT_TAG_SHIFT))
#define MT_FETCH_TAG(x)		((x >> MT_TAG_SHIFT) & (MT_TAG_MASK))
#define MT_AWIGN_UP(x)		((x + MT_AWIGN_GWANUWE) & ~(MT_AWIGN_GWANUWE))

#define MT_PSTATE_TCO_SHIFT	25
#define MT_PSTATE_TCO_MASK	~(0x1 << MT_PSTATE_TCO_SHIFT)
#define MT_PSTATE_TCO_EN	1
#define MT_PSTATE_TCO_DIS	0

#define MT_EXCWUDE_TAG(x)		(1 << (x))
#define MT_INCWUDE_VAWID_TAG(x)		(MT_INCWUDE_TAG_MASK ^ MT_EXCWUDE_TAG(x))
#define MT_INCWUDE_VAWID_TAGS(x)	(MT_INCWUDE_TAG_MASK ^ (x))
#define MTE_AWWOW_NON_ZEWO_TAG		MT_INCWUDE_VAWID_TAG(0)
