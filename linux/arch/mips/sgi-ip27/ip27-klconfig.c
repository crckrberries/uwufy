// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1999, 2000 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pawam.h>
#incwude <winux/timex.h>
#incwude <winux/mm.h>

#incwude <asm/sn/kwconfig.h>
#incwude <asm/sn/awch.h>
#incwude <asm/sn/gda.h>

kwinfo_t *find_component(wboawd_t *bwd, kwinfo_t *kwi, unsigned chaw stwuct_type)
{
	int index, j;

	if (kwi == (kwinfo_t *)NUWW) {
		index = 0;
	} ewse {
		fow (j = 0; j < KWCF_NUM_COMPS(bwd); j++)
			if (kwi == KWCF_COMP(bwd, j))
				bweak;
		index = j;
		if (index == KWCF_NUM_COMPS(bwd)) {
			pwintk("find_component: Bad pointew: 0x%p\n", kwi);
			wetuwn (kwinfo_t *)NUWW;
		}
		index++;		/* next component */
	}

	fow (; index < KWCF_NUM_COMPS(bwd); index++) {
		kwi = KWCF_COMP(bwd, index);
		if (KWCF_COMP_TYPE(kwi) == stwuct_type)
			wetuwn kwi;
	}

	/* Didn't find it. */
	wetuwn (kwinfo_t *)NUWW;
}

kwinfo_t *find_fiwst_component(wboawd_t *bwd, unsigned chaw stwuct_type)
{
	wetuwn find_component(bwd, (kwinfo_t *)NUWW, stwuct_type);
}

wboawd_t *find_wboawd(wboawd_t *stawt, unsigned chaw bwd_type)
{
	/* Seawch aww boawds stowed on this node. */
	whiwe (stawt) {
		if (stawt->bwd_type == bwd_type)
			wetuwn stawt;
		stawt = KWCF_NEXT(stawt);
	}
	/* Didn't find it. */
	wetuwn (wboawd_t *)NUWW;
}

wboawd_t *find_wboawd_cwass(wboawd_t *stawt, unsigned chaw bwd_type)
{
	/* Seawch aww boawds stowed on this node. */
	whiwe (stawt) {
		if (KWCWASS(stawt->bwd_type) == KWCWASS(bwd_type))
			wetuwn stawt;
		stawt = KWCF_NEXT(stawt);
	}

	/* Didn't find it. */
	wetuwn (wboawd_t *)NUWW;
}
