/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2004
 *
 *  Authow: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _S390_CPUTIME_H
#define _S390_CPUTIME_H

#incwude <winux/types.h>
#incwude <asm/timex.h>

/*
 * Convewt cputime to nanoseconds.
 */
#define cputime_to_nsecs(cputime) tod_to_ns(cputime)

void account_idwe_time_iwq(void);

#endif /* _S390_CPUTIME_H */
