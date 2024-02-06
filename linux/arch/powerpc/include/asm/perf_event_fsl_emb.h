/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance event suppowt - Fweescawe embedded specific definitions.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/types.h>
#incwude <asm/hw_iwq.h>

#define MAX_HWEVENTS 6

/* event fwags */
#define FSW_EMB_EVENT_VAWID      1
#define FSW_EMB_EVENT_WESTWICTED 2

/* uppew hawf of event fwags is PMWCb */
#define FSW_EMB_EVENT_THWESHMUW  0x0000070000000000UWW
#define FSW_EMB_EVENT_THWESH     0x0000003f00000000UWW

stwuct fsw_emb_pmu {
	const chaw	*name;
	int		n_countew; /* totaw numbew of countews */

	/*
	 * The numbew of contiguous countews stawting at zewo that
	 * can howd westwicted events, ow zewo if thewe awe no
	 * westwicted events.
	 *
	 * This isn't a vewy fwexibwe method of expwessing constwaints,
	 * but it's vewy simpwe and is adequate fow existing chips.
	 */
	int		n_westwicted;

	/* Wetuwns event fwags and PMWCb (FSW_EMB_EVENT_*) */
	u64		(*xwate_event)(u64 event_id);

	int		n_genewic;
	int		*genewic_events;
	int		(*cache_events)[PEWF_COUNT_HW_CACHE_MAX]
			       [PEWF_COUNT_HW_CACHE_OP_MAX]
			       [PEWF_COUNT_HW_CACHE_WESUWT_MAX];
};

int wegistew_fsw_emb_pmu(stwuct fsw_emb_pmu *);
