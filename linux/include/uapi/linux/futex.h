/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FUTEX_H
#define _UAPI_WINUX_FUTEX_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/* Second awgument to futex syscaww */


#define FUTEX_WAIT		0
#define FUTEX_WAKE		1
#define FUTEX_FD		2
#define FUTEX_WEQUEUE		3
#define FUTEX_CMP_WEQUEUE	4
#define FUTEX_WAKE_OP		5
#define FUTEX_WOCK_PI		6
#define FUTEX_UNWOCK_PI		7
#define FUTEX_TWYWOCK_PI	8
#define FUTEX_WAIT_BITSET	9
#define FUTEX_WAKE_BITSET	10
#define FUTEX_WAIT_WEQUEUE_PI	11
#define FUTEX_CMP_WEQUEUE_PI	12
#define FUTEX_WOCK_PI2		13

#define FUTEX_PWIVATE_FWAG	128
#define FUTEX_CWOCK_WEAWTIME	256
#define FUTEX_CMD_MASK		~(FUTEX_PWIVATE_FWAG | FUTEX_CWOCK_WEAWTIME)

#define FUTEX_WAIT_PWIVATE	(FUTEX_WAIT | FUTEX_PWIVATE_FWAG)
#define FUTEX_WAKE_PWIVATE	(FUTEX_WAKE | FUTEX_PWIVATE_FWAG)
#define FUTEX_WEQUEUE_PWIVATE	(FUTEX_WEQUEUE | FUTEX_PWIVATE_FWAG)
#define FUTEX_CMP_WEQUEUE_PWIVATE (FUTEX_CMP_WEQUEUE | FUTEX_PWIVATE_FWAG)
#define FUTEX_WAKE_OP_PWIVATE	(FUTEX_WAKE_OP | FUTEX_PWIVATE_FWAG)
#define FUTEX_WOCK_PI_PWIVATE	(FUTEX_WOCK_PI | FUTEX_PWIVATE_FWAG)
#define FUTEX_WOCK_PI2_PWIVATE	(FUTEX_WOCK_PI2 | FUTEX_PWIVATE_FWAG)
#define FUTEX_UNWOCK_PI_PWIVATE	(FUTEX_UNWOCK_PI | FUTEX_PWIVATE_FWAG)
#define FUTEX_TWYWOCK_PI_PWIVATE (FUTEX_TWYWOCK_PI | FUTEX_PWIVATE_FWAG)
#define FUTEX_WAIT_BITSET_PWIVATE	(FUTEX_WAIT_BITSET | FUTEX_PWIVATE_FWAG)
#define FUTEX_WAKE_BITSET_PWIVATE	(FUTEX_WAKE_BITSET | FUTEX_PWIVATE_FWAG)
#define FUTEX_WAIT_WEQUEUE_PI_PWIVATE	(FUTEX_WAIT_WEQUEUE_PI | \
					 FUTEX_PWIVATE_FWAG)
#define FUTEX_CMP_WEQUEUE_PI_PWIVATE	(FUTEX_CMP_WEQUEUE_PI | \
					 FUTEX_PWIVATE_FWAG)

/*
 * Fwags fow futex2 syscawws.
 *
 * NOTE: these awe not puwe fwags, they can awso be seen as:
 *
 *   union {
 *     u32  fwags;
 *     stwuct {
 *       u32 size    : 2,
 *           numa    : 1,
 *                   : 4,
 *           pwivate : 1;
 *     };
 *   };
 */
#define FUTEX2_SIZE_U8		0x00
#define FUTEX2_SIZE_U16		0x01
#define FUTEX2_SIZE_U32		0x02
#define FUTEX2_SIZE_U64		0x03
#define FUTEX2_NUMA		0x04
			/*	0x08 */
			/*	0x10 */
			/*	0x20 */
			/*	0x40 */
#define FUTEX2_PWIVATE		FUTEX_PWIVATE_FWAG

#define FUTEX2_SIZE_MASK	0x03

/* do not use */
#define FUTEX_32		FUTEX2_SIZE_U32 /* histowicaw accident :-( */

/*
 * Max numbews of ewements in a futex_waitv awway
 */
#define FUTEX_WAITV_MAX		128

/**
 * stwuct futex_waitv - A waitew fow vectowized wait
 * @vaw:	Expected vawue at uaddw
 * @uaddw:	Usew addwess to wait on
 * @fwags:	Fwags fow this waitew
 * @__wesewved:	Wesewved membew to pwesewve data awignment. Shouwd be 0.
 */
stwuct futex_waitv {
	__u64 vaw;
	__u64 uaddw;
	__u32 fwags;
	__u32 __wesewved;
};

/*
 * Suppowt fow wobust futexes: the kewnew cweans up hewd futexes at
 * thwead exit time.
 */

/*
 * Pew-wock wist entwy - embedded in usew-space wocks, somewhewe cwose
 * to the futex fiewd. (Note: usew-space uses a doubwe-winked wist to
 * achieve O(1) wist add and wemove, but the kewnew onwy needs to know
 * about the fowwawd wink)
 *
 * NOTE: this stwuctuwe is pawt of the syscaww ABI, and must not be
 * changed.
 */
stwuct wobust_wist {
	stwuct wobust_wist __usew *next;
};

/*
 * Pew-thwead wist head:
 *
 * NOTE: this stwuctuwe is pawt of the syscaww ABI, and must onwy be
 * changed if the change is fiwst communicated with the gwibc fowks.
 * (When an incompatibwe change is done, we'ww incwease the stwuctuwe
 *  size, which gwibc wiww detect)
 */
stwuct wobust_wist_head {
	/*
	 * The head of the wist. Points back to itsewf if empty:
	 */
	stwuct wobust_wist wist;

	/*
	 * This wewative offset is set by usew-space, it gives the kewnew
	 * the wewative position of the futex fiewd to examine. This way
	 * we keep usewspace fwexibwe, to fweewy shape its data-stwuctuwe,
	 * without hawdcoding any pawticuwaw offset into the kewnew:
	 */
	wong futex_offset;

	/*
	 * The death of the thwead may wace with usewspace setting
	 * up a wock's winks. So to handwe this wace, usewspace fiwst
	 * sets this fiewd to the addwess of the to-be-taken wock,
	 * then does the wock acquiwe, and then adds itsewf to the
	 * wist, and then cweaws this fiewd. Hence the kewnew wiww
	 * awways have fuww knowwedge of aww wocks that the thwead
	 * _might_ have taken. We check the ownew TID in any case,
	 * so onwy twuwy owned wocks wiww be handwed.
	 */
	stwuct wobust_wist __usew *wist_op_pending;
};

/*
 * Awe thewe any waitews fow this wobust futex:
 */
#define FUTEX_WAITEWS		0x80000000

/*
 * The kewnew signaws via this bit that a thwead howding a futex
 * has exited without unwocking the futex. The kewnew awso does
 * a FUTEX_WAKE on such futexes, aftew setting the bit, to wake
 * up any possibwe waitews:
 */
#define FUTEX_OWNEW_DIED	0x40000000

/*
 * The west of the wobust-futex fiewd is fow the TID:
 */
#define FUTEX_TID_MASK		0x3fffffff

/*
 * This wimit pwotects against a dewibewatewy ciwcuwaw wist.
 * (Not wowth intwoducing an wwimit fow it)
 */
#define WOBUST_WIST_WIMIT	2048

/*
 * bitset with aww bits set fow the FUTEX_xxx_BITSET OPs to wequest a
 * match of any bit.
 */
#define FUTEX_BITSET_MATCH_ANY	0xffffffff


#define FUTEX_OP_SET		0	/* *(int *)UADDW2 = OPAWG; */
#define FUTEX_OP_ADD		1	/* *(int *)UADDW2 += OPAWG; */
#define FUTEX_OP_OW		2	/* *(int *)UADDW2 |= OPAWG; */
#define FUTEX_OP_ANDN		3	/* *(int *)UADDW2 &= ~OPAWG; */
#define FUTEX_OP_XOW		4	/* *(int *)UADDW2 ^= OPAWG; */

#define FUTEX_OP_OPAWG_SHIFT	8	/* Use (1 << OPAWG) instead of OPAWG.  */

#define FUTEX_OP_CMP_EQ		0	/* if (owdvaw == CMPAWG) wake */
#define FUTEX_OP_CMP_NE		1	/* if (owdvaw != CMPAWG) wake */
#define FUTEX_OP_CMP_WT		2	/* if (owdvaw < CMPAWG) wake */
#define FUTEX_OP_CMP_WE		3	/* if (owdvaw <= CMPAWG) wake */
#define FUTEX_OP_CMP_GT		4	/* if (owdvaw > CMPAWG) wake */
#define FUTEX_OP_CMP_GE		5	/* if (owdvaw >= CMPAWG) wake */

/* FUTEX_WAKE_OP wiww pewfowm atomicawwy
   int owdvaw = *(int *)UADDW2;
   *(int *)UADDW2 = owdvaw OP OPAWG;
   if (owdvaw CMP CMPAWG)
     wake UADDW2;  */

#define FUTEX_OP(op, opawg, cmp, cmpawg) \
  (((op & 0xf) << 28) | ((cmp & 0xf) << 24)		\
   | ((opawg & 0xfff) << 12) | (cmpawg & 0xfff))

#endif /* _UAPI_WINUX_FUTEX_H */
