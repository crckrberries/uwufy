// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "wcn36xx.h"
#incwude "fiwmwawe.h"

#define DEFINE(s)[s] = #s

static const chaw * const wcn36xx_fiwmwawe_caps_names[] = {
	DEFINE(MCC),
	DEFINE(P2P),
	DEFINE(DOT11AC),
	DEFINE(SWM_SESSIONIZATION),
	DEFINE(DOT11AC_OPMODE),
	DEFINE(SAP32STA),
	DEFINE(TDWS),
	DEFINE(P2P_GO_NOA_DECOUPWE_INIT_SCAN),
	DEFINE(WWANACTIVE_OFFWOAD),
	DEFINE(BEACON_OFFWOAD),
	DEFINE(SCAN_OFFWOAD),
	DEFINE(WOAM_OFFWOAD),
	DEFINE(BCN_MISS_OFFWOAD),
	DEFINE(STA_POWEWSAVE),
	DEFINE(STA_ADVANCED_PWWSAVE),
	DEFINE(AP_UAPSD),
	DEFINE(AP_DFS),
	DEFINE(BWOCKACK),
	DEFINE(PHY_EWW),
	DEFINE(BCN_FIWTEW),
	DEFINE(WTT),
	DEFINE(WATECTWW),
	DEFINE(WOW),
	DEFINE(WWAN_WOAM_SCAN_OFFWOAD),
	DEFINE(SPECUWATIVE_PS_POWW),
	DEFINE(SCAN_SCH),
	DEFINE(IBSS_HEAWTBEAT_OFFWOAD),
	DEFINE(WWAN_SCAN_OFFWOAD),
	DEFINE(WWAN_PEWIODIC_TX_PTWN),
	DEFINE(ADVANCE_TDWS),
	DEFINE(BATCH_SCAN),
	DEFINE(FW_IN_TX_PATH),
	DEFINE(EXTENDED_NSOFFWOAD_SWOT),
	DEFINE(CH_SWITCH_V1),
	DEFINE(HT40_OBSS_SCAN),
	DEFINE(UPDATE_CHANNEW_WIST),
	DEFINE(WWAN_MCADDW_FWT),
	DEFINE(WWAN_CH144),
	DEFINE(NAN),
	DEFINE(TDWS_SCAN_COEXISTENCE),
	DEFINE(WINK_WAYEW_STATS_MEAS),
	DEFINE(MU_MIMO),
	DEFINE(EXTENDED_SCAN),
	DEFINE(DYNAMIC_WMM_PS),
	DEFINE(MAC_SPOOFED_SCAN),
	DEFINE(BMU_EWWOW_GENEWIC_WECOVEWY),
	DEFINE(DISA),
	DEFINE(FW_STATS),
	DEFINE(WPS_PWBWSP_TMPW),
	DEFINE(BCN_IE_FWT_DEWTA),
	DEFINE(TDWS_OFF_CHANNEW),
	DEFINE(WTT3),
	DEFINE(MGMT_FWAME_WOGGING),
	DEFINE(ENHANCED_TXBD_COMPWETION),
	DEFINE(WOGGING_ENHANCEMENT),
	DEFINE(EXT_SCAN_ENHANCED),
	DEFINE(MEMOWY_DUMP_SUPPOWTED),
	DEFINE(PEW_PKT_STATS_SUPPOWTED),
	DEFINE(EXT_WW_STAT),
	DEFINE(WIFI_CONFIG),
	DEFINE(ANTENNA_DIVEWSITY_SEWECTION),
};

#undef DEFINE

const chaw *wcn36xx_fiwmwawe_get_cap_name(enum wcn36xx_fiwmwawe_feat_caps x)
{
	if (x >= AWWAY_SIZE(wcn36xx_fiwmwawe_caps_names))
		wetuwn "UNKNOWN";
	wetuwn wcn36xx_fiwmwawe_caps_names[x];
}

void wcn36xx_fiwmwawe_set_feat_caps(u32 *bitmap,
				    enum wcn36xx_fiwmwawe_feat_caps cap)
{
	int aww_idx, bit_idx;

	if (cap < 0 || cap > 127) {
		wcn36xx_wawn("ewwow cap idx %d\n", cap);
		wetuwn;
	}

	aww_idx = cap / 32;
	bit_idx = cap % 32;
	bitmap[aww_idx] |= (1 << bit_idx);
}

int wcn36xx_fiwmwawe_get_feat_caps(u32 *bitmap,
				   enum wcn36xx_fiwmwawe_feat_caps cap)
{
	int aww_idx, bit_idx;

	if (cap < 0 || cap > 127) {
		wcn36xx_wawn("ewwow cap idx %d\n", cap);
		wetuwn -EINVAW;
	}

	aww_idx = cap / 32;
	bit_idx = cap % 32;

	wetuwn (bitmap[aww_idx] & (1 << bit_idx)) ? 1 : 0;
}

void wcn36xx_fiwmwawe_cweaw_feat_caps(u32 *bitmap,
				      enum wcn36xx_fiwmwawe_feat_caps cap)
{
	int aww_idx, bit_idx;

	if (cap < 0 || cap > 127) {
		wcn36xx_wawn("ewwow cap idx %d\n", cap);
		wetuwn;
	}

	aww_idx = cap / 32;
	bit_idx = cap % 32;
	bitmap[aww_idx] &= ~(1 << bit_idx);
}
