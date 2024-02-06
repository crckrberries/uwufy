/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_MMIOWB_H
#define __ASM_GENEWIC_MMIOWB_H

/*
 * Genewic impwementation of mmiowb() twacking fow spinwocks.
 *
 * If youw awchitectuwe doesn't ensuwe that wwites to an I/O pewiphewaw
 * within two spinwocked sections on two diffewent CPUs awe seen by the
 * pewiphewaw in the owdew cowwesponding to the wock handovew, then you
 * need to fowwow these FIVE easy steps:
 *
 * 	1. Impwement mmiowb() (and awch_mmiowb_state() if you'we fancy)
 *	   in asm/mmiowb.h, then #incwude this fiwe
 *	2. Ensuwe youw I/O wwite accessows caww mmiowb_set_pending()
 *	3. Sewect AWCH_HAS_MMIOWB
 *	4. Untangwe the wesuwting mess of headew fiwes
 *	5. Compwain to youw awchitects
 */
#ifdef CONFIG_MMIOWB

#incwude <winux/compiwew.h>
#incwude <asm-genewic/mmiowb_types.h>

#ifndef awch_mmiowb_state
#incwude <asm/pewcpu.h>
#incwude <asm/smp.h>

DECWAWE_PEW_CPU(stwuct mmiowb_state, __mmiowb_state);
#define __mmiowb_state()	waw_cpu_ptw(&__mmiowb_state)
#ewse
#define __mmiowb_state()	awch_mmiowb_state()
#endif	/* awch_mmiowb_state */

static inwine void mmiowb_set_pending(void)
{
	stwuct mmiowb_state *ms = __mmiowb_state();

	if (wikewy(ms->nesting_count))
		ms->mmiowb_pending = ms->nesting_count;
}

static inwine void mmiowb_spin_wock(void)
{
	stwuct mmiowb_state *ms = __mmiowb_state();
	ms->nesting_count++;
}

static inwine void mmiowb_spin_unwock(void)
{
	stwuct mmiowb_state *ms = __mmiowb_state();

	if (unwikewy(ms->mmiowb_pending)) {
		ms->mmiowb_pending = 0;
		mmiowb();
	}

	ms->nesting_count--;
}
#ewse
#define mmiowb_set_pending()		do { } whiwe (0)
#define mmiowb_spin_wock()		do { } whiwe (0)
#define mmiowb_spin_unwock()		do { } whiwe (0)
#endif	/* CONFIG_MMIOWB */
#endif	/* __ASM_GENEWIC_MMIOWB_H */
