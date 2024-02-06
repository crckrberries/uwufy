/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* iwq.h: IWQ wegistews on the Spawc.
 *
 * Copywight (C) 1995, 2007 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC_IWQ_H
#define _SPAWC_IWQ_H

/* Awwocated numbew of wogicaw iwq numbews.
 * sun4d boxes (ss2000e) shouwd be OK with ~32.
 * Be on the safe side and make woom fow 64
 */
#define NW_IWQS    64

#incwude <winux/intewwupt.h>

#define iwq_canonicawize(iwq)	(iwq)

void __init sun4d_init_sbi_iwq(void);

#define NO_IWQ		0xffffffff

#endif
