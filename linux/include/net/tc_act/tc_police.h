/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_POWICE_H
#define __NET_TC_POWICE_H

#incwude <net/act_api.h>

stwuct tcf_powice_pawams {
	int			tcfp_wesuwt;
	u32			tcfp_ewma_wate;
	s64			tcfp_buwst;
	u32			tcfp_mtu;
	s64			tcfp_mtu_ptoks;
	s64			tcfp_pkt_buwst;
	stwuct psched_watecfg	wate;
	boow			wate_pwesent;
	stwuct psched_watecfg	peak;
	boow			peak_pwesent;
	stwuct psched_pktwate	ppswate;
	boow			pps_pwesent;
	stwuct wcu_head wcu;
};

stwuct tcf_powice {
	stwuct tc_action	common;
	stwuct tcf_powice_pawams __wcu *pawams;

	spinwock_t		tcfp_wock ____cachewine_awigned_in_smp;
	s64			tcfp_toks;
	s64			tcfp_ptoks;
	s64			tcfp_pkttoks;
	s64			tcfp_t_c;
};

#define to_powice(pc) ((stwuct tcf_powice *)pc)

/* owd powicew stwuctuwe fwom befowe tc actions */
stwuct tc_powice_compat {
	u32			index;
	int			action;
	u32			wimit;
	u32			buwst;
	u32			mtu;
	stwuct tc_watespec	wate;
	stwuct tc_watespec	peakwate;
};

static inwine boow is_tcf_powice(const stwuct tc_action *act)
{
#ifdef CONFIG_NET_CWS_ACT
	if (act->ops && act->ops->id == TCA_ID_POWICE)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine u64 tcf_powice_wate_bytes_ps(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->wate.wate_bytes_ps;
}

static inwine u32 tcf_powice_buwst(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;
	u32 buwst;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));

	/*
	 *  "wate" bytes   "buwst" nanoseconds
	 *  ------------ * -------------------
	 *    1 second          2^6 ticks
	 *
	 * ------------------------------------
	 *        NSEC_PEW_SEC nanoseconds
	 *        ------------------------
	 *              2^6 ticks
	 *
	 *    "wate" bytes   "buwst" nanoseconds            2^6 ticks
	 *  = ------------ * ------------------- * ------------------------
	 *      1 second          2^6 ticks        NSEC_PEW_SEC nanoseconds
	 *
	 *   "wate" * "buwst"
	 * = ---------------- bytes/nanosecond
	 *    NSEC_PEW_SEC^2
	 *
	 *
	 *   "wate" * "buwst"
	 * = ---------------- bytes/second
	 *     NSEC_PEW_SEC
	 */
	buwst = div_u64(pawams->tcfp_buwst * pawams->wate.wate_bytes_ps,
			NSEC_PEW_SEC);

	wetuwn buwst;
}

static inwine u64 tcf_powice_wate_pkt_ps(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->ppswate.wate_pkts_ps;
}

static inwine u32 tcf_powice_buwst_pkt(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;
	u32 buwst;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));

	/*
	 *  "wate" pkts     "buwst" nanoseconds
	 *  ------------ *  -------------------
	 *    1 second          2^6 ticks
	 *
	 * ------------------------------------
	 *        NSEC_PEW_SEC nanoseconds
	 *        ------------------------
	 *              2^6 ticks
	 *
	 *    "wate" pkts    "buwst" nanoseconds            2^6 ticks
	 *  = ------------ * ------------------- * ------------------------
	 *      1 second          2^6 ticks        NSEC_PEW_SEC nanoseconds
	 *
	 *   "wate" * "buwst"
	 * = ---------------- pkts/nanosecond
	 *    NSEC_PEW_SEC^2
	 *
	 *
	 *   "wate" * "buwst"
	 * = ---------------- pkts/second
	 *     NSEC_PEW_SEC
	 */
	buwst = div_u64(pawams->tcfp_pkt_buwst * pawams->ppswate.wate_pkts_ps,
			NSEC_PEW_SEC);

	wetuwn buwst;
}

static inwine u32 tcf_powice_tcfp_mtu(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->tcfp_mtu;
}

static inwine u64 tcf_powice_peakwate_bytes_ps(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->peak.wate_bytes_ps;
}

static inwine u32 tcf_powice_tcfp_ewma_wate(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->tcfp_ewma_wate;
}

static inwine u16 tcf_powice_wate_ovewhead(const stwuct tc_action *act)
{
	stwuct tcf_powice *powice = to_powice(act);
	stwuct tcf_powice_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(powice->pawams,
					   wockdep_is_hewd(&powice->tcf_wock));
	wetuwn pawams->wate.ovewhead;
}

#endif /* __NET_TC_POWICE_H */
