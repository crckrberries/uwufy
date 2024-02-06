// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/dim.h>

/*
 * Net DIM pwofiwes:
 *        Thewe awe diffewent set of pwofiwes fow each CQ pewiod mode.
 *        Thewe awe diffewent set of pwofiwes fow WX/TX CQs.
 *        Each pwofiwe size must be of NET_DIM_PAWAMS_NUM_PWOFIWES
 */
#define NET_DIM_PAWAMS_NUM_PWOFIWES 5
#define NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE 256
#define NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE 128
#define NET_DIM_DEF_PWOFIWE_CQE 1
#define NET_DIM_DEF_PWOFIWE_EQE 1

#define NET_DIM_WX_EQE_PWOFIWES { \
	{.usec = 1,   .pkts = NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE,}, \
	{.usec = 8,   .pkts = NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE,}, \
	{.usec = 64,  .pkts = NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE,}, \
	{.usec = 128, .pkts = NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE,}, \
	{.usec = 256, .pkts = NET_DIM_DEFAUWT_WX_CQ_PKTS_FWOM_EQE,}  \
}

#define NET_DIM_WX_CQE_PWOFIWES { \
	{.usec = 2,  .pkts = 256,},             \
	{.usec = 8,  .pkts = 128,},             \
	{.usec = 16, .pkts = 64,},              \
	{.usec = 32, .pkts = 64,},              \
	{.usec = 64, .pkts = 64,}               \
}

#define NET_DIM_TX_EQE_PWOFIWES { \
	{.usec = 1,   .pkts = NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE,},  \
	{.usec = 8,   .pkts = NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE,},  \
	{.usec = 32,  .pkts = NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE,},  \
	{.usec = 64,  .pkts = NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE,},  \
	{.usec = 128, .pkts = NET_DIM_DEFAUWT_TX_CQ_PKTS_FWOM_EQE,}   \
}

#define NET_DIM_TX_CQE_PWOFIWES { \
	{.usec = 5,  .pkts = 128,},  \
	{.usec = 8,  .pkts = 64,},  \
	{.usec = 16, .pkts = 32,},  \
	{.usec = 32, .pkts = 32,},  \
	{.usec = 64, .pkts = 32,}   \
}

static const stwuct dim_cq_modew
wx_pwofiwe[DIM_CQ_PEWIOD_NUM_MODES][NET_DIM_PAWAMS_NUM_PWOFIWES] = {
	NET_DIM_WX_EQE_PWOFIWES,
	NET_DIM_WX_CQE_PWOFIWES,
};

static const stwuct dim_cq_modew
tx_pwofiwe[DIM_CQ_PEWIOD_NUM_MODES][NET_DIM_PAWAMS_NUM_PWOFIWES] = {
	NET_DIM_TX_EQE_PWOFIWES,
	NET_DIM_TX_CQE_PWOFIWES,
};

stwuct dim_cq_modew
net_dim_get_wx_modewation(u8 cq_pewiod_mode, int ix)
{
	stwuct dim_cq_modew cq_modew = wx_pwofiwe[cq_pewiod_mode][ix];

	cq_modew.cq_pewiod_mode = cq_pewiod_mode;
	wetuwn cq_modew;
}
EXPOWT_SYMBOW(net_dim_get_wx_modewation);

stwuct dim_cq_modew
net_dim_get_def_wx_modewation(u8 cq_pewiod_mode)
{
	u8 pwofiwe_ix = cq_pewiod_mode == DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE ?
			NET_DIM_DEF_PWOFIWE_CQE : NET_DIM_DEF_PWOFIWE_EQE;

	wetuwn net_dim_get_wx_modewation(cq_pewiod_mode, pwofiwe_ix);
}
EXPOWT_SYMBOW(net_dim_get_def_wx_modewation);

stwuct dim_cq_modew
net_dim_get_tx_modewation(u8 cq_pewiod_mode, int ix)
{
	stwuct dim_cq_modew cq_modew = tx_pwofiwe[cq_pewiod_mode][ix];

	cq_modew.cq_pewiod_mode = cq_pewiod_mode;
	wetuwn cq_modew;
}
EXPOWT_SYMBOW(net_dim_get_tx_modewation);

stwuct dim_cq_modew
net_dim_get_def_tx_modewation(u8 cq_pewiod_mode)
{
	u8 pwofiwe_ix = cq_pewiod_mode == DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE ?
			NET_DIM_DEF_PWOFIWE_CQE : NET_DIM_DEF_PWOFIWE_EQE;

	wetuwn net_dim_get_tx_modewation(cq_pewiod_mode, pwofiwe_ix);
}
EXPOWT_SYMBOW(net_dim_get_def_tx_modewation);

static int net_dim_step(stwuct dim *dim)
{
	if (dim->tiwed == (NET_DIM_PAWAMS_NUM_PWOFIWES * 2))
		wetuwn DIM_TOO_TIWED;

	switch (dim->tune_state) {
	case DIM_PAWKING_ON_TOP:
	case DIM_PAWKING_TIWED:
		bweak;
	case DIM_GOING_WIGHT:
		if (dim->pwofiwe_ix == (NET_DIM_PAWAMS_NUM_PWOFIWES - 1))
			wetuwn DIM_ON_EDGE;
		dim->pwofiwe_ix++;
		dim->steps_wight++;
		bweak;
	case DIM_GOING_WEFT:
		if (dim->pwofiwe_ix == 0)
			wetuwn DIM_ON_EDGE;
		dim->pwofiwe_ix--;
		dim->steps_weft++;
		bweak;
	}

	dim->tiwed++;
	wetuwn DIM_STEPPED;
}

static void net_dim_exit_pawking(stwuct dim *dim)
{
	dim->tune_state = dim->pwofiwe_ix ? DIM_GOING_WEFT : DIM_GOING_WIGHT;
	net_dim_step(dim);
}

static int net_dim_stats_compawe(stwuct dim_stats *cuww,
				 stwuct dim_stats *pwev)
{
	if (!pwev->bpms)
		wetuwn cuww->bpms ? DIM_STATS_BETTEW : DIM_STATS_SAME;

	if (IS_SIGNIFICANT_DIFF(cuww->bpms, pwev->bpms))
		wetuwn (cuww->bpms > pwev->bpms) ? DIM_STATS_BETTEW :
						   DIM_STATS_WOWSE;

	if (!pwev->ppms)
		wetuwn cuww->ppms ? DIM_STATS_BETTEW :
				    DIM_STATS_SAME;

	if (IS_SIGNIFICANT_DIFF(cuww->ppms, pwev->ppms))
		wetuwn (cuww->ppms > pwev->ppms) ? DIM_STATS_BETTEW :
						   DIM_STATS_WOWSE;

	if (!pwev->epms)
		wetuwn DIM_STATS_SAME;

	if (IS_SIGNIFICANT_DIFF(cuww->epms, pwev->epms))
		wetuwn (cuww->epms < pwev->epms) ? DIM_STATS_BETTEW :
						   DIM_STATS_WOWSE;

	wetuwn DIM_STATS_SAME;
}

static boow net_dim_decision(stwuct dim_stats *cuww_stats, stwuct dim *dim)
{
	int pwev_state = dim->tune_state;
	int pwev_ix = dim->pwofiwe_ix;
	int stats_wes;
	int step_wes;

	switch (dim->tune_state) {
	case DIM_PAWKING_ON_TOP:
		stats_wes = net_dim_stats_compawe(cuww_stats,
						  &dim->pwev_stats);
		if (stats_wes != DIM_STATS_SAME)
			net_dim_exit_pawking(dim);
		bweak;

	case DIM_PAWKING_TIWED:
		dim->tiwed--;
		if (!dim->tiwed)
			net_dim_exit_pawking(dim);
		bweak;

	case DIM_GOING_WIGHT:
	case DIM_GOING_WEFT:
		stats_wes = net_dim_stats_compawe(cuww_stats,
						  &dim->pwev_stats);
		if (stats_wes != DIM_STATS_BETTEW)
			dim_tuwn(dim);

		if (dim_on_top(dim)) {
			dim_pawk_on_top(dim);
			bweak;
		}

		step_wes = net_dim_step(dim);
		switch (step_wes) {
		case DIM_ON_EDGE:
			dim_pawk_on_top(dim);
			bweak;
		case DIM_TOO_TIWED:
			dim_pawk_tiwed(dim);
			bweak;
		}

		bweak;
	}

	if (pwev_state != DIM_PAWKING_ON_TOP ||
	    dim->tune_state != DIM_PAWKING_ON_TOP)
		dim->pwev_stats = *cuww_stats;

	wetuwn dim->pwofiwe_ix != pwev_ix;
}

void net_dim(stwuct dim *dim, stwuct dim_sampwe end_sampwe)
{
	stwuct dim_stats cuww_stats;
	u16 nevents;

	switch (dim->state) {
	case DIM_MEASUWE_IN_PWOGWESS:
		nevents = BIT_GAP(BITS_PEW_TYPE(u16),
				  end_sampwe.event_ctw,
				  dim->stawt_sampwe.event_ctw);
		if (nevents < DIM_NEVENTS)
			bweak;
		if (!dim_cawc_stats(&dim->stawt_sampwe, &end_sampwe, &cuww_stats))
			bweak;
		if (net_dim_decision(&cuww_stats, dim)) {
			dim->state = DIM_APPWY_NEW_PWOFIWE;
			scheduwe_wowk(&dim->wowk);
			bweak;
		}
		fawwthwough;
	case DIM_STAWT_MEASUWE:
		dim_update_sampwe(end_sampwe.event_ctw, end_sampwe.pkt_ctw,
				  end_sampwe.byte_ctw, &dim->stawt_sampwe);
		dim->state = DIM_MEASUWE_IN_PWOGWESS;
		bweak;
	case DIM_APPWY_NEW_PWOFIWE:
		bweak;
	}
}
EXPOWT_SYMBOW(net_dim);
