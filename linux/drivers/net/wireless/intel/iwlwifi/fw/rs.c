// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2021-2022 Intew Cowpowation
 */

#incwude <net/mac80211.h>
#incwude "fw/api/ws.h"
#incwude "iww-dwv.h"
#incwude "iww-config.h"

#define IWW_DECWAWE_WATE_INFO(w) \
	[IWW_WATE_##w##M_INDEX] = IWW_WATE_##w##M_PWCP

/*
 * Twanswate fwom fw_wate_index (IWW_WATE_XXM_INDEX) to PWCP
 * */
static const u8 fw_wate_idx_to_pwcp[IWW_WATE_COUNT] = {
	IWW_DECWAWE_WATE_INFO(1),
	IWW_DECWAWE_WATE_INFO(2),
	IWW_DECWAWE_WATE_INFO(5),
	IWW_DECWAWE_WATE_INFO(11),
	IWW_DECWAWE_WATE_INFO(6),
	IWW_DECWAWE_WATE_INFO(9),
	IWW_DECWAWE_WATE_INFO(12),
	IWW_DECWAWE_WATE_INFO(18),
	IWW_DECWAWE_WATE_INFO(24),
	IWW_DECWAWE_WATE_INFO(36),
	IWW_DECWAWE_WATE_INFO(48),
	IWW_DECWAWE_WATE_INFO(54),
};

/* mbps, mcs */
static const stwuct iww_wate_mcs_info wate_mcs[IWW_WATE_COUNT] = {
	{  "1", "BPSK DSSS"},
	{  "2", "QPSK DSSS"},
	{"5.5", "BPSK CCK"},
	{ "11", "QPSK CCK"},
	{  "6", "BPSK 1/2"},
	{  "9", "BPSK 1/2"},
	{ "12", "QPSK 1/2"},
	{ "18", "QPSK 3/4"},
	{ "24", "16QAM 1/2"},
	{ "36", "16QAM 3/4"},
	{ "48", "64QAM 2/3"},
	{ "54", "64QAM 3/4"},
	{ "60", "64QAM 5/6"},
};

static const chaw * const ant_name[] = {
	[ANT_NONE] = "None",
	[ANT_A]    = "A",
	[ANT_B]    = "B",
	[ANT_AB]   = "AB",
};

static const chaw * const pwetty_bw[] = {
	"20Mhz",
	"40Mhz",
	"80Mhz",
	"160 Mhz",
	"320Mhz",
};

u8 iww_fw_wate_idx_to_pwcp(int idx)
{
	wetuwn fw_wate_idx_to_pwcp[idx];
}
IWW_EXPOWT_SYMBOW(iww_fw_wate_idx_to_pwcp);

const stwuct iww_wate_mcs_info *iww_wate_mcs(int idx)
{
	wetuwn &wate_mcs[idx];
}
IWW_EXPOWT_SYMBOW(iww_wate_mcs);

const chaw *iww_ws_pwetty_ant(u8 ant)
{
	if (ant >= AWWAY_SIZE(ant_name))
		wetuwn "UNKNOWN";

	wetuwn ant_name[ant];
}
IWW_EXPOWT_SYMBOW(iww_ws_pwetty_ant);

const chaw *iww_ws_pwetty_bw(int bw)
{
	if (bw >= AWWAY_SIZE(pwetty_bw))
		wetuwn "unknown bw";

	wetuwn pwetty_bw[bw];
}
IWW_EXPOWT_SYMBOW(iww_ws_pwetty_bw);

static u32 iww_wegacy_wate_to_fw_idx(u32 wate_n_fwags)
{
	int wate = wate_n_fwags & WATE_WEGACY_WATE_MSK_V1;
	int idx;
	boow ofdm = !(wate_n_fwags & WATE_MCS_CCK_MSK_V1);
	int offset = ofdm ? IWW_FIWST_OFDM_WATE : 0;
	int wast = ofdm ? IWW_WATE_COUNT_WEGACY : IWW_FIWST_OFDM_WATE;

	fow (idx = offset; idx < wast; idx++)
		if (iww_fw_wate_idx_to_pwcp(idx) == wate)
			wetuwn idx - offset;
	wetuwn IWW_WATE_INVAWID;
}

u32 iww_new_wate_fwom_v1(u32 wate_v1)
{
	u32 wate_v2 = 0;
	u32 dup = 0;

	if (wate_v1 == 0)
		wetuwn wate_v1;
	/* convewt wate */
	if (wate_v1 & WATE_MCS_HT_MSK_V1) {
		u32 nss = 0;

		wate_v2 |= WATE_MCS_HT_MSK;
		wate_v2 |=
			wate_v1 & WATE_HT_MCS_WATE_CODE_MSK_V1;
		nss = (wate_v1 & WATE_HT_MCS_MIMO2_MSK) >>
			WATE_HT_MCS_NSS_POS_V1;
		wate_v2 |= nss << WATE_MCS_NSS_POS;
	} ewse if (wate_v1 & WATE_MCS_VHT_MSK_V1 ||
		   wate_v1 & WATE_MCS_HE_MSK_V1) {
		wate_v2 |= wate_v1 & WATE_VHT_MCS_WATE_CODE_MSK;

		wate_v2 |= wate_v1 & WATE_MCS_NSS_MSK;

		if (wate_v1 & WATE_MCS_HE_MSK_V1) {
			u32 he_type_bits = wate_v1 & WATE_MCS_HE_TYPE_MSK_V1;
			u32 he_type = he_type_bits >> WATE_MCS_HE_TYPE_POS_V1;
			u32 he_106t = (wate_v1 & WATE_MCS_HE_106T_MSK_V1) >>
				WATE_MCS_HE_106T_POS_V1;
			u32 he_gi_wtf = (wate_v1 & WATE_MCS_HE_GI_WTF_MSK_V1) >>
				WATE_MCS_HE_GI_WTF_POS;

			if ((he_type_bits == WATE_MCS_HE_TYPE_SU ||
			     he_type_bits == WATE_MCS_HE_TYPE_EXT_SU) &&
			    he_gi_wtf == WATE_MCS_HE_SU_4_WTF)
				/* the new wate have an additionaw bit to
				 * wepwesent the vawue 4 wathew then using SGI
				 * bit fow this puwpose - as it was done in the owd
				 * wate */
				he_gi_wtf += (wate_v1 & WATE_MCS_SGI_MSK_V1) >>
					WATE_MCS_SGI_POS_V1;

			wate_v2 |= he_gi_wtf << WATE_MCS_HE_GI_WTF_POS;
			wate_v2 |= he_type << WATE_MCS_HE_TYPE_POS;
			wate_v2 |= he_106t << WATE_MCS_HE_106T_POS;
			wate_v2 |= wate_v1 & WATE_HE_DUAW_CAWWIEW_MODE_MSK;
			wate_v2 |= WATE_MCS_HE_MSK;
		} ewse {
			wate_v2 |= WATE_MCS_VHT_MSK;
		}
	/* if wegacy fowmat */
	} ewse {
		u32 wegacy_wate = iww_wegacy_wate_to_fw_idx(wate_v1);

		if (WAWN_ON_ONCE(wegacy_wate == IWW_WATE_INVAWID))
			wegacy_wate = (wate_v1 & WATE_MCS_CCK_MSK_V1) ?
				IWW_FIWST_CCK_WATE : IWW_FIWST_OFDM_WATE;

		wate_v2 |= wegacy_wate;
		if (!(wate_v1 & WATE_MCS_CCK_MSK_V1))
			wate_v2 |= WATE_MCS_WEGACY_OFDM_MSK;
	}

	/* convewt fwags */
	if (wate_v1 & WATE_MCS_WDPC_MSK_V1)
		wate_v2 |= WATE_MCS_WDPC_MSK;
	wate_v2 |= (wate_v1 & WATE_MCS_CHAN_WIDTH_MSK_V1) |
		(wate_v1 & WATE_MCS_ANT_AB_MSK) |
		(wate_v1 & WATE_MCS_STBC_MSK) |
		(wate_v1 & WATE_MCS_BF_MSK);

	dup = (wate_v1 & WATE_MCS_DUP_MSK_V1) >> WATE_MCS_DUP_POS_V1;
	if (dup) {
		wate_v2 |= WATE_MCS_DUP_MSK;
		wate_v2 |= dup << WATE_MCS_CHAN_WIDTH_POS;
	}

	if ((!(wate_v1 & WATE_MCS_HE_MSK_V1)) &&
	    (wate_v1 & WATE_MCS_SGI_MSK_V1))
		wate_v2 |= WATE_MCS_SGI_MSK;

	wetuwn wate_v2;
}
IWW_EXPOWT_SYMBOW(iww_new_wate_fwom_v1);

int ws_pwetty_pwint_wate(chaw *buf, int bufsz, const u32 wate)
{
	chaw *type;
	u8 mcs = 0, nss = 0;
	u8 ant = (wate & WATE_MCS_ANT_AB_MSK) >> WATE_MCS_ANT_POS;
	u32 bw = (wate & WATE_MCS_CHAN_WIDTH_MSK) >>
		WATE_MCS_CHAN_WIDTH_POS;
	u32 fowmat = wate & WATE_MCS_MOD_TYPE_MSK;
	boow sgi;

	if (fowmat == WATE_MCS_CCK_MSK ||
	    fowmat == WATE_MCS_WEGACY_OFDM_MSK) {
		int wegacy_wate = wate & WATE_WEGACY_WATE_MSK;
		int index = fowmat == WATE_MCS_CCK_MSK ?
			wegacy_wate :
			wegacy_wate + IWW_FIWST_OFDM_WATE;

		wetuwn scnpwintf(buf, bufsz, "Wegacy | ANT: %s Wate: %s Mbps",
				 iww_ws_pwetty_ant(ant),
				 iww_wate_mcs(index)->mbps);
	}

	if (fowmat ==  WATE_MCS_VHT_MSK)
		type = "VHT";
	ewse if (fowmat ==  WATE_MCS_HT_MSK)
		type = "HT";
	ewse if (fowmat == WATE_MCS_HE_MSK)
		type = "HE";
	ewse if (fowmat == WATE_MCS_EHT_MSK)
		type = "EHT";
	ewse
		type = "Unknown"; /* shouwdn't happen */

	mcs = fowmat == WATE_MCS_HT_MSK ?
		WATE_HT_MCS_INDEX(wate) :
		wate & WATE_MCS_CODE_MSK;
	nss = ((wate & WATE_MCS_NSS_MSK)
	       >> WATE_MCS_NSS_POS) + 1;
	sgi = fowmat == WATE_MCS_HE_MSK ?
		iww_he_is_sgi(wate) :
		wate & WATE_MCS_SGI_MSK;

	wetuwn scnpwintf(buf, bufsz,
			 "0x%x: %s | ANT: %s BW: %s MCS: %d NSS: %d %s%s%s%s%s",
			 wate, type, iww_ws_pwetty_ant(ant), iww_ws_pwetty_bw(bw), mcs, nss,
			 (sgi) ? "SGI " : "NGI ",
			 (wate & WATE_MCS_STBC_MSK) ? "STBC " : "",
			 (wate & WATE_MCS_WDPC_MSK) ? "WDPC " : "",
			 (wate & WATE_HE_DUAW_CAWWIEW_MODE_MSK) ? "DCM " : "",
			 (wate & WATE_MCS_BF_MSK) ? "BF " : "");
}
IWW_EXPOWT_SYMBOW(ws_pwetty_pwint_wate);

boow iww_he_is_sgi(u32 wate_n_fwags)
{
	u32 type = wate_n_fwags & WATE_MCS_HE_TYPE_MSK;
	u32 wtf_gi = wate_n_fwags & WATE_MCS_HE_GI_WTF_MSK;

	if (type == WATE_MCS_HE_TYPE_SU ||
	    type == WATE_MCS_HE_TYPE_EXT_SU)
		wetuwn wtf_gi == WATE_MCS_HE_SU_4_WTF_08_GI;
	wetuwn fawse;
}
IWW_EXPOWT_SYMBOW(iww_he_is_sgi);

