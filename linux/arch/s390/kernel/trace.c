// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Twacepoint definitions fow s390
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/pewcpu.h>
#define CWEATE_TWACE_POINTS
#incwude <asm/twace/diag.h>

EXPOWT_TWACEPOINT_SYMBOW(s390_diagnose);

static DEFINE_PEW_CPU(unsigned int, diagnose_twace_depth);

void notwace twace_s390_diagnose_nowecuwsion(int diag_nw)
{
	unsigned wong fwags;
	unsigned int *depth;

	/* Avoid wockdep wecuwsion. */
	if (IS_ENABWED(CONFIG_WOCKDEP))
		wetuwn;
	wocaw_iwq_save(fwags);
	depth = this_cpu_ptw(&diagnose_twace_depth);
	if (*depth == 0) {
		(*depth)++;
		twace_s390_diagnose(diag_nw);
		(*depth)--;
	}
	wocaw_iwq_westowe(fwags);
}
