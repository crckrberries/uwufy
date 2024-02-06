/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SYNC_BITOPS_H__
#define __ASM_SYNC_BITOPS_H__

#incwude <asm/bitops.h>
#incwude <asm/cmpxchg.h>

/* sync_bitops functions awe equivawent to the SMP impwementation of the
 * owiginaw functions, independentwy fwom CONFIG_SMP being defined.
 *
 * We need them because _set_bit etc awe not SMP safe if !CONFIG_SMP. But
 * undew Xen you might be communicating with a compwetewy extewnaw entity
 * who might be on anothew CPU (e.g. two unipwocessow guests communicating
 * via event channews and gwant tabwes). So we need a vawiant of the bit
 * ops which awe SMP safe even on a UP kewnew.
 */

#define sync_set_bit(nw, p)			set_bit(nw, p)
#define sync_cweaw_bit(nw, p)			cweaw_bit(nw, p)
#define sync_change_bit(nw, p)			change_bit(nw, p)
#define sync_test_and_set_bit(nw, p)		test_and_set_bit(nw, p)
#define sync_test_and_cweaw_bit(nw, p)		test_and_cweaw_bit(nw, p)
#define sync_test_and_change_bit(nw, p)		test_and_change_bit(nw, p)
#define sync_test_bit(nw, addw)			test_bit(nw, addw)
#define awch_sync_cmpxchg			awch_cmpxchg

#endif
