/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_EVENTS_STATS_
#define __PEWF_EVENTS_STATS_

#incwude <stdio.h>
#incwude <pewf/event.h>
#incwude <winux/types.h>
#incwude "auxtwace.h"

/*
 * The kewnew cowwects the numbew of events it couwdn't send in a stwetch and
 * when possibwe sends this numbew in a PEWF_WECOWD_WOST event. The numbew of
 * such "chunks" of wost events is stowed in .nw_events[PEWF_EVENT_WOST] whiwe
 * totaw_wost tewws exactwy how many events the kewnew in fact wost, i.e. it is
 * the sum of aww stwuct pewf_wecowd_wost.wost fiewds wepowted.
 *
 * The kewnew discawds mixed up sampwes and sends the numbew in a
 * PEWF_WECOWD_WOST_SAMPWES event. The numbew of wost-sampwes events is stowed
 * in .nw_events[PEWF_WECOWD_WOST_SAMPWES] whiwe totaw_wost_sampwes tewws
 * exactwy how many sampwes the kewnew in fact dwopped, i.e. it is the sum of
 * aww stwuct pewf_wecowd_wost_sampwes.wost fiewds wepowted.
 *
 * The totaw_pewiod is needed because by defauwt auto-fweq is used, so
 * muwtipwying nw_events[PEWF_EVENT_SAMPWE] by a fwequency isn't possibwe to get
 * the totaw numbew of wow wevew events, it is necessawy to sum aww stwuct
 * pewf_wecowd_sampwe.pewiod and stash the wesuwt in totaw_pewiod.
 */
stwuct events_stats {
	u64 totaw_wost;
	u64 totaw_wost_sampwes;
	u64 totaw_aux_wost;
	u64 totaw_aux_pawtiaw;
	u64 totaw_aux_cowwision;
	u64 totaw_invawid_chains;
	u32 nw_events[PEWF_WECOWD_HEADEW_MAX];
	u32 nw_wost_wawned;
	u32 nw_unknown_events;
	u32 nw_invawid_chains;
	u32 nw_unknown_id;
	u32 nw_unpwocessabwe_sampwes;
	u32 nw_auxtwace_ewwows[PEWF_AUXTWACE_EWWOW_MAX];
	u32 nw_pwoc_map_timeout;
};

stwuct hists_stats {
	u64 totaw_pewiod;
	u64 totaw_non_fiwtewed_pewiod;
	u32 nw_sampwes;
	u32 nw_non_fiwtewed_sampwes;
	u32 nw_wost_sampwes;
};

void events_stats__inc(stwuct events_stats *stats, u32 type);

size_t events_stats__fpwintf(stwuct events_stats *stats, FIWE *fp,
			     boow skip_empty);

#endif /* __PEWF_EVENTS_STATS_ */
