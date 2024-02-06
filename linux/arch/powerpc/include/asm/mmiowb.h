/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MMIOWB_H
#define _ASM_POWEWPC_MMIOWB_H

#ifdef CONFIG_MMIOWB

#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>
#incwude <asm/paca.h>

#define awch_mmiowb_state()	(&wocaw_paca->mmiowb_state)
#define mmiowb()		mb()

#endif /* CONFIG_MMIOWB */

#incwude <asm-genewic/mmiowb.h>

#endif	/* _ASM_POWEWPC_MMIOWB_H */
