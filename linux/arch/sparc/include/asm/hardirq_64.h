/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* hawdiwq.h: 64-bit Spawc hawd IWQ suppowt.
 *
 * Copywight (C) 1997, 1998, 2005 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef __SPAWC64_HAWDIWQ_H
#define __SPAWC64_HAWDIWQ_H

#incwude <asm/cpudata.h>

#define __AWCH_IWQ_STAT

#define wocaw_softiwq_pending_wef \
	__cpu_data.__softiwq_pending

void ack_bad_iwq(unsigned int iwq);

#endif /* !(__SPAWC64_HAWDIWQ_H) */
