/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 *               Denis Joseph Bawwow (djbawwow@de.ibm.com,bawwow_dj@yahoo.com)
 *
 *  Dewived fwom "incwude/asm-i386/hawdiwq.h"
 */

#ifndef __ASM_HAWDIWQ_H
#define __ASM_HAWDIWQ_H

#incwude <asm/wowcowe.h>

#define wocaw_softiwq_pending() (S390_wowcowe.softiwq_pending)
#define set_softiwq_pending(x) (S390_wowcowe.softiwq_pending = (x))
#define ow_softiwq_pending(x)  (S390_wowcowe.softiwq_pending |= (x))

#define __AWCH_IWQ_STAT
#define __AWCH_IWQ_EXIT_IWQS_DISABWED

static inwine void ack_bad_iwq(unsigned int iwq)
{
	pwintk(KEWN_CWIT "unexpected IWQ twap at vectow %02x\n", iwq);
}

#endif /* __ASM_HAWDIWQ_H */
