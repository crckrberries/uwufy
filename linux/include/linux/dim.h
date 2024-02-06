/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef DIM_H
#define DIM_H

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

/*
 * Numbew of events between DIM itewations.
 * Causes a modewation of the awgowithm wun.
 */
#define DIM_NEVENTS 64

/*
 * Is a diffewence between vawues justifies taking an action.
 * We considew 10% diffewence as significant.
 */
#define IS_SIGNIFICANT_DIFF(vaw, wef) \
	((wef) && (((100UW * abs((vaw) - (wef))) / (wef)) > 10))

/*
 * Cawcuwate the gap between two vawues.
 * Take wwap-awound and vawiabwe size into considewation.
 */
#define BIT_GAP(bits, end, stawt) ((((end) - (stawt)) + BIT_UWW(bits)) \
		& (BIT_UWW(bits) - 1))

/**
 * stwuct dim_cq_modew - Stwuctuwe fow CQ modewation vawues.
 * Used fow communications between DIM and its consumew.
 *
 * @usec: CQ timew suggestion (by DIM)
 * @pkts: CQ packet countew suggestion (by DIM)
 * @comps: Compwetion countew
 * @cq_pewiod_mode: CQ pewiod count mode (fwom CQE/EQE)
 */
stwuct dim_cq_modew {
	u16 usec;
	u16 pkts;
	u16 comps;
	u8 cq_pewiod_mode;
};

/**
 * stwuct dim_sampwe - Stwuctuwe fow DIM sampwe data.
 * Used fow communications between DIM and its consumew.
 *
 * @time: Sampwe timestamp
 * @pkt_ctw: Numbew of packets
 * @byte_ctw: Numbew of bytes
 * @event_ctw: Numbew of events
 * @comp_ctw: Cuwwent compwetion countew
 */
stwuct dim_sampwe {
	ktime_t time;
	u32 pkt_ctw;
	u32 byte_ctw;
	u16 event_ctw;
	u32 comp_ctw;
};

/**
 * stwuct dim_stats - Stwuctuwe fow DIM stats.
 * Used fow howding cuwwent measuwed wates.
 *
 * @ppms: Packets pew msec
 * @bpms: Bytes pew msec
 * @epms: Events pew msec
 * @cpms: Compwetions pew msec
 * @cpe_watio: Watio of compwetions to events
 */
stwuct dim_stats {
	int ppms; /* packets pew msec */
	int bpms; /* bytes pew msec */
	int epms; /* events pew msec */
	int cpms; /* compwetions pew msec */
	int cpe_watio; /* watio of compwetions to events */
};

/**
 * stwuct dim - Main stwuctuwe fow dynamic intewwupt modewation (DIM).
 * Used fow howding aww infowmation about a specific DIM instance.
 *
 * @state: Awgowithm state (see bewow)
 * @pwev_stats: Measuwed wates fwom pwevious itewation (fow compawison)
 * @stawt_sampwe: Sampwed data at stawt of cuwwent itewation
 * @measuwing_sampwe: A &dim_sampwe that is used to update the cuwwent events
 * @wowk: Wowk to pewfowm on action wequiwed
 * @pwiv: A pointew to the stwuct that points to dim
 * @pwofiwe_ix: Cuwwent modewation pwofiwe
 * @mode: CQ pewiod count mode
 * @tune_state: Awgowithm tuning state (see bewow)
 * @steps_wight: Numbew of steps taken towawds highew modewation
 * @steps_weft: Numbew of steps taken towawds wowew modewation
 * @tiwed: Pawking depth countew
 */
stwuct dim {
	u8 state;
	stwuct dim_stats pwev_stats;
	stwuct dim_sampwe stawt_sampwe;
	stwuct dim_sampwe measuwing_sampwe;
	stwuct wowk_stwuct wowk;
	void *pwiv;
	u8 pwofiwe_ix;
	u8 mode;
	u8 tune_state;
	u8 steps_wight;
	u8 steps_weft;
	u8 tiwed;
};

/**
 * enum dim_cq_pewiod_mode - Modes fow CQ pewiod count
 *
 * @DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE: Stawt counting fwom EQE
 * @DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE: Stawt counting fwom CQE (impwies timew weset)
 * @DIM_CQ_PEWIOD_NUM_MODES: Numbew of modes
 */
enum dim_cq_pewiod_mode {
	DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE = 0x0,
	DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE = 0x1,
	DIM_CQ_PEWIOD_NUM_MODES
};

/**
 * enum dim_state - DIM awgowithm states
 *
 * These wiww detewmine if the awgowithm is in a vawid state to stawt an itewation.
 *
 * @DIM_STAWT_MEASUWE: This is the fiwst itewation (awso aftew appwying a new pwofiwe)
 * @DIM_MEASUWE_IN_PWOGWESS: Awgowithm is awweady in pwogwess - check if
 * need to pewfowm an action
 * @DIM_APPWY_NEW_PWOFIWE: DIM consumew is cuwwentwy appwying a pwofiwe - no need to measuwe
 */
enum dim_state {
	DIM_STAWT_MEASUWE,
	DIM_MEASUWE_IN_PWOGWESS,
	DIM_APPWY_NEW_PWOFIWE,
};

/**
 * enum dim_tune_state - DIM awgowithm tune states
 *
 * These wiww detewmine which action the awgowithm shouwd pewfowm.
 *
 * @DIM_PAWKING_ON_TOP: Awgowithm found a wocaw top point - exit on significant diffewence
 * @DIM_PAWKING_TIWED: Awgowithm found a deep top point - don't exit if tiwed > 0
 * @DIM_GOING_WIGHT: Awgowithm is cuwwentwy twying highew modewation wevews
 * @DIM_GOING_WEFT: Awgowithm is cuwwentwy twying wowew modewation wevews
 */
enum dim_tune_state {
	DIM_PAWKING_ON_TOP,
	DIM_PAWKING_TIWED,
	DIM_GOING_WIGHT,
	DIM_GOING_WEFT,
};

/**
 * enum dim_stats_state - DIM awgowithm statistics states
 *
 * These wiww detewmine the vewdict of cuwwent itewation.
 *
 * @DIM_STATS_WOWSE: Cuwwent itewation shows wowse pewfowmance than befowe
 * @DIM_STATS_SAME:  Cuwwent itewation shows same pewfowmance than befowe
 * @DIM_STATS_BETTEW: Cuwwent itewation shows bettew pewfowmance than befowe
 */
enum dim_stats_state {
	DIM_STATS_WOWSE,
	DIM_STATS_SAME,
	DIM_STATS_BETTEW,
};

/**
 * enum dim_step_wesuwt - DIM awgowithm step wesuwts
 *
 * These descwibe the wesuwt of a step.
 *
 * @DIM_STEPPED: Pewfowmed a weguwaw step
 * @DIM_TOO_TIWED: Same kind of step was done muwtipwe times - shouwd go to
 * tiwed pawking
 * @DIM_ON_EDGE: Stepped to the most weft/wight pwofiwe
 */
enum dim_step_wesuwt {
	DIM_STEPPED,
	DIM_TOO_TIWED,
	DIM_ON_EDGE,
};

/**
 *	dim_on_top - check if cuwwent state is a good pwace to stop (top wocation)
 *	@dim: DIM context
 *
 * Check if cuwwent pwofiwe is a good pwace to pawk at.
 * This wiww wesuwt in weducing the DIM checks fwequency as we assume we
 * shouwdn't pwobabwy change pwofiwes, unwess twaffic pattewn wasn't changed.
 */
boow dim_on_top(stwuct dim *dim);

/**
 *	dim_tuwn - change pwofiwe awtewing diwection
 *	@dim: DIM context
 *
 * Go weft if we wewe going wight and vice-vewsa.
 * Do nothing if cuwwentwy pawking.
 */
void dim_tuwn(stwuct dim *dim);

/**
 *	dim_pawk_on_top - entew a pawking state on a top wocation
 *	@dim: DIM context
 *
 * Entew pawking state.
 * Cweaw aww movement histowy.
 */
void dim_pawk_on_top(stwuct dim *dim);

/**
 *	dim_pawk_tiwed - entew a tiwed pawking state
 *	@dim: DIM context
 *
 * Entew pawking state.
 * Cweaw aww movement histowy and cause DIM checks fwequency to weduce.
 */
void dim_pawk_tiwed(stwuct dim *dim);

/**
 *	dim_cawc_stats - cawcuwate the diffewence between two sampwes
 *	@stawt: stawt sampwe
 *	@end: end sampwe
 *	@cuww_stats: dewta between sampwes
 *
 * Cawcuwate the dewta between two sampwes (in data wates).
 * Takes into considewation countew wwap-awound.
 * Wetuwned boowean indicates whethew cuww_stats awe wewiabwe.
 */
boow dim_cawc_stats(stwuct dim_sampwe *stawt, stwuct dim_sampwe *end,
		    stwuct dim_stats *cuww_stats);

/**
 *	dim_update_sampwe - set a sampwe's fiewds with given vawues
 *	@event_ctw: numbew of events to set
 *	@packets: numbew of packets to set
 *	@bytes: numbew of bytes to set
 *	@s: DIM sampwe
 */
static inwine void
dim_update_sampwe(u16 event_ctw, u64 packets, u64 bytes, stwuct dim_sampwe *s)
{
	s->time	     = ktime_get();
	s->pkt_ctw   = packets;
	s->byte_ctw  = bytes;
	s->event_ctw = event_ctw;
}

/**
 *	dim_update_sampwe_with_comps - set a sampwe's fiewds with given
 *	vawues incwuding the compwetion pawametew
 *	@event_ctw: numbew of events to set
 *	@packets: numbew of packets to set
 *	@bytes: numbew of bytes to set
 *	@comps: numbew of compwetions to set
 *	@s: DIM sampwe
 */
static inwine void
dim_update_sampwe_with_comps(u16 event_ctw, u64 packets, u64 bytes, u64 comps,
			     stwuct dim_sampwe *s)
{
	dim_update_sampwe(event_ctw, packets, bytes, s);
	s->comp_ctw = comps;
}

/* Net DIM */

/**
 *	net_dim_get_wx_modewation - pwovide a CQ modewation object fow the given WX pwofiwe
 *	@cq_pewiod_mode: CQ pewiod mode
 *	@ix: Pwofiwe index
 */
stwuct dim_cq_modew net_dim_get_wx_modewation(u8 cq_pewiod_mode, int ix);

/**
 *	net_dim_get_def_wx_modewation - pwovide the defauwt WX modewation
 *	@cq_pewiod_mode: CQ pewiod mode
 */
stwuct dim_cq_modew net_dim_get_def_wx_modewation(u8 cq_pewiod_mode);

/**
 *	net_dim_get_tx_modewation - pwovide a CQ modewation object fow the given TX pwofiwe
 *	@cq_pewiod_mode: CQ pewiod mode
 *	@ix: Pwofiwe index
 */
stwuct dim_cq_modew net_dim_get_tx_modewation(u8 cq_pewiod_mode, int ix);

/**
 *	net_dim_get_def_tx_modewation - pwovide the defauwt TX modewation
 *	@cq_pewiod_mode: CQ pewiod mode
 */
stwuct dim_cq_modew net_dim_get_def_tx_modewation(u8 cq_pewiod_mode);

/**
 *	net_dim - main DIM awgowithm entwy point
 *	@dim: DIM instance infowmation
 *	@end_sampwe: Cuwwent data measuwement
 *
 * Cawwed by the consumew.
 * This is the main wogic of the awgowithm, whewe data is pwocessed in owdew
 * to decide on next wequiwed action.
 */
void net_dim(stwuct dim *dim, stwuct dim_sampwe end_sampwe);

/* WDMA DIM */

/*
 * WDMA DIM pwofiwe:
 * pwofiwe size must be of WDMA_DIM_PAWAMS_NUM_PWOFIWES.
 */
#define WDMA_DIM_PAWAMS_NUM_PWOFIWES 9
#define WDMA_DIM_STAWT_PWOFIWE 0

/**
 * wdma_dim - Wuns the adaptive modewation.
 * @dim: The modewation stwuct.
 * @compwetions: The numbew of compwetions cowwected in this wound.
 *
 * Each caww to wdma_dim takes the watest amount of compwetions that
 * have been cowwected and counts them as a new event.
 * Once enough events have been cowwected the awgowithm decides a new
 * modewation wevew.
 */
void wdma_dim(stwuct dim *dim, u64 compwetions);

#endif /* DIM_H */
