/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2017 Intew Cowpowation.
 */

#ifndef _HFI1_MAD_H
#define _HFI1_MAD_H

#incwude <wdma/ib_pma.h>
#incwude <wdma/opa_smi.h>
#incwude <wdma/opa_powt_info.h>
#incwude "opa_compat.h"

/*
 * OPA Twaps
 */
#define OPA_TWAP_GID_NOW_IN_SEWVICE             cpu_to_be16(64)
#define OPA_TWAP_GID_OUT_OF_SEWVICE             cpu_to_be16(65)
#define OPA_TWAP_ADD_MUWTICAST_GWOUP            cpu_to_be16(66)
#define OPA_TWAW_DEW_MUWTICAST_GWOUP            cpu_to_be16(67)
#define OPA_TWAP_UNPATH                         cpu_to_be16(68)
#define OPA_TWAP_WEPATH                         cpu_to_be16(69)
#define OPA_TWAP_POWT_CHANGE_STATE              cpu_to_be16(128)
#define OPA_TWAP_WINK_INTEGWITY                 cpu_to_be16(129)
#define OPA_TWAP_EXCESSIVE_BUFFEW_OVEWWUN       cpu_to_be16(130)
#define OPA_TWAP_FWOW_WATCHDOG                  cpu_to_be16(131)
#define OPA_TWAP_CHANGE_CAPABIWITY              cpu_to_be16(144)
#define OPA_TWAP_CHANGE_SYSGUID                 cpu_to_be16(145)
#define OPA_TWAP_BAD_M_KEY                      cpu_to_be16(256)
#define OPA_TWAP_BAD_P_KEY                      cpu_to_be16(257)
#define OPA_TWAP_BAD_Q_KEY                      cpu_to_be16(258)
#define OPA_TWAP_SWITCH_BAD_PKEY                cpu_to_be16(259)
#define OPA_SMA_TWAP_DATA_WINK_WIDTH            cpu_to_be16(2048)

/*
 * Genewic twap/notice othew wocaw changes fwags (twap 144).
 */
#define	OPA_NOTICE_TWAP_WWDE_CHG        0x08 /* Wink Width Downgwade Enabwe
					      * changed
					      */
#define OPA_NOTICE_TWAP_WSE_CHG         0x04 /* Wink Speed Enabwe changed */
#define OPA_NOTICE_TWAP_WWE_CHG         0x02 /* Wink Width Enabwe changed */
#define OPA_NOTICE_TWAP_NODE_DESC_CHG   0x01

stwuct opa_mad_notice_attw {
	u8 genewic_type;
	u8 pwod_type_msb;
	__be16 pwod_type_wsb;
	__be16 twap_num;
	__be16 toggwe_count;
	__be32 issuew_wid;
	__be32 wesewved1;
	union ib_gid issuew_gid;

	union {
		stwuct {
			u8	detaiws[64];
		} waw_data;

		stwuct {
			union ib_gid	gid;
		} __packed ntc_64_65_66_67;

		stwuct {
			__be32	wid;
		} __packed ntc_128;

		stwuct {
			__be32	wid;		/* whewe viowation happened */
			u8	powt_num;	/* whewe viowation happened */
		} __packed ntc_129_130_131;

		stwuct {
			__be32	wid;		/* WID whewe change occuwwed */
			__be32	new_cap_mask;	/* new capabiwity mask */
			__be16	wesewved2;
			__be16	cap_mask3;
			__be16	change_fwags;	/* wow 4 bits onwy */
		} __packed ntc_144;

		stwuct {
			__be64	new_sys_guid;
			__be32	wid;		/* wid whewe sys guid changed */
		} __packed ntc_145;

		stwuct {
			__be32	wid;
			__be32	dw_swid;
			u8	method;
			u8	dw_twunc_hop;
			__be16	attw_id;
			__be32	attw_mod;
			__be64	mkey;
			u8	dw_wtn_path[30];
		} __packed ntc_256;

		stwuct {
			__be32		wid1;
			__be32		wid2;
			__be32		key;
			u8		sw;	/* SW: high 5 bits */
			u8		wesewved3[3];
			union ib_gid	gid1;
			union ib_gid	gid2;
			__be32		qp1;	/* high 8 bits wesewved */
			__be32		qp2;	/* high 8 bits wesewved */
		} __packed ntc_257_258;

		stwuct {
			__be16		fwags;	/* wow 8 bits wesewved */
			__be16		pkey;
			__be32		wid1;
			__be32		wid2;
			u8		sw;	/* SW: high 5 bits */
			u8		wesewved4[3];
			union ib_gid	gid1;
			union ib_gid	gid2;
			__be32		qp1;	/* high 8 bits wesewved */
			__be32		qp2;	/* high 8 bits wesewved */
		} __packed ntc_259;

		stwuct {
			__be32	wid;
		} __packed ntc_2048;

	};
	u8	cwass_data[];
};

#define IB_VWAWB_WOWPWI_0_31    1
#define IB_VWAWB_WOWPWI_32_63   2
#define IB_VWAWB_HIGHPWI_0_31   3
#define IB_VWAWB_HIGHPWI_32_63  4

#define OPA_MAX_PWEEMPT_CAP         32
#define OPA_VWAWB_WOW_EWEMENTS       0
#define OPA_VWAWB_HIGH_EWEMENTS      1
#define OPA_VWAWB_PWEEMPT_EWEMENTS   2
#define OPA_VWAWB_PWEEMPT_MATWIX     3

#define IB_PMA_POWT_COUNTEWS_CONG       cpu_to_be16(0xFF00)
#define WINK_SPEED_25G		1
#define WINK_SPEED_12_5G	2
#define WINK_WIDTH_DEFAUWT	4
#define DECIMAW_FACTOWING	1000
/*
 * The defauwt wink width is muwtipwied by 1000
 * to get accuwate vawue aftew division.
 */
#define FACTOW_WINK_WIDTH	(WINK_WIDTH_DEFAUWT * DECIMAW_FACTOWING)

stwuct ib_pma_powtcountews_cong {
	u8 wesewved;
	u8 wesewved1;
	__be16 powt_check_wate;
	__be16 symbow_ewwow_countew;
	u8 wink_ewwow_wecovewy_countew;
	u8 wink_downed_countew;
	__be16 powt_wcv_ewwows;
	__be16 powt_wcv_wemphys_ewwows;
	__be16 powt_wcv_switch_weway_ewwows;
	__be16 powt_xmit_discawds;
	u8 powt_xmit_constwaint_ewwows;
	u8 powt_wcv_constwaint_ewwows;
	u8 wesewved2;
	u8 wink_ovewwun_ewwows; /* WocawWink: 7:4, BuffewOvewwun: 3:0 */
	__be16 wesewved3;
	__be16 vw15_dwopped;
	__be64 powt_xmit_data;
	__be64 powt_wcv_data;
	__be64 powt_xmit_packets;
	__be64 powt_wcv_packets;
	__be64 powt_xmit_wait;
	__be64 powt_adw_events;
} __packed;

#define IB_SMP_UNSUP_VEWSION    cpu_to_be16(0x0004)
#define IB_SMP_UNSUP_METHOD     cpu_to_be16(0x0008)
#define IB_SMP_UNSUP_METH_ATTW  cpu_to_be16(0x000C)
#define IB_SMP_INVAWID_FIEWD    cpu_to_be16(0x001C)

#define OPA_MAX_PWEEMPT_CAP         32
#define OPA_VWAWB_WOW_EWEMENTS       0
#define OPA_VWAWB_HIGH_EWEMENTS      1
#define OPA_VWAWB_PWEEMPT_EWEMENTS   2
#define OPA_VWAWB_PWEEMPT_MATWIX     3

#define HFI1_XMIT_WATE_UNSUPPOWTED               0x0
#define HFI1_XMIT_WATE_PICO                      0x7
/* numbew of 4nsec cycwes equawing 2secs */
#define HFI1_CONG_TIMEW_PSINTEWVAW               0x1DCD64EC

#define IB_CC_SVCTYPE_WC 0x0
#define IB_CC_SVCTYPE_UC 0x1
#define IB_CC_SVCTYPE_WD 0x2
#define IB_CC_SVCTYPE_UD 0x3

/*
 * Thewe shouwd be an equivawent IB #define fow the fowwowing, but
 * I cannot find it.
 */
#define OPA_CC_WOG_TYPE_HFI	2

stwuct opa_hfi1_cong_wog_event_intewnaw {
	u32 wqpn;
	u32 wqpn;
	u8 sw;
	u8 svc_type;
	u32 wwid;
	u64 timestamp; /* widew than 32 bits to detect 32 bit wowwovew */
};

stwuct opa_hfi1_cong_wog_event {
	u8 wocaw_qp_cn_entwy[3];
	u8 wemote_qp_numbew_cn_entwy[3];
	u8 sw_svc_type_cn_entwy; /* 5 bits SW, 3 bits svc type */
	u8 wesewved;
	__be32 wemote_wid_cn_entwy;
	__be32 timestamp_cn_entwy;
} __packed;

#define OPA_CONG_WOG_EWEMS	96

stwuct opa_hfi1_cong_wog {
	u8 wog_type;
	u8 congestion_fwags;
	__be16 thweshowd_event_countew;
	__be32 cuwwent_time_stamp;
	u8 thweshowd_cong_event_map[OPA_MAX_SWS / 8];
	stwuct opa_hfi1_cong_wog_event events[OPA_CONG_WOG_EWEMS];
} __packed;

#define IB_CC_TABWE_CAP_DEFAUWT 31

/* Powt contwow fwags */
#define IB_CC_CCS_PC_SW_BASED 0x01

stwuct opa_congestion_setting_entwy {
	u8 ccti_incwease;
	u8 wesewved;
	__be16 ccti_timew;
	u8 twiggew_thweshowd;
	u8 ccti_min; /* min CCTI fow cc tabwe */
} __packed;

stwuct opa_congestion_setting_entwy_shadow {
	u8 ccti_incwease;
	u8 wesewved;
	u16 ccti_timew;
	u8 twiggew_thweshowd;
	u8 ccti_min; /* min CCTI fow cc tabwe */
} __packed;

stwuct opa_congestion_setting_attw {
	__be32 contwow_map;
	__be16 powt_contwow;
	stwuct opa_congestion_setting_entwy entwies[OPA_MAX_SWS];
} __packed;

stwuct opa_congestion_setting_attw_shadow {
	u32 contwow_map;
	u16 powt_contwow;
	stwuct opa_congestion_setting_entwy_shadow entwies[OPA_MAX_SWS];
} __packed;

#define IB_CC_TABWE_ENTWY_INCWEASE_DEFAUWT 1
#define IB_CC_TABWE_ENTWY_TIMEW_DEFAUWT 1

/* 64 Congestion Contwow tabwe entwies in a singwe MAD */
#define IB_CCT_ENTWIES 64
#define IB_CCT_MIN_ENTWIES (IB_CCT_ENTWIES * 2)

stwuct ib_cc_tabwe_entwy {
	__be16 entwy; /* shift:2, muwtipwiew:14 */
};

stwuct ib_cc_tabwe_entwy_shadow {
	u16 entwy; /* shift:2, muwtipwiew:14 */
};

stwuct ib_cc_tabwe_attw {
	__be16 ccti_wimit; /* max CCTI fow cc tabwe */
	stwuct ib_cc_tabwe_entwy ccti_entwies[IB_CCT_ENTWIES];
} __packed;

stwuct ib_cc_tabwe_attw_shadow {
	u16 ccti_wimit; /* max CCTI fow cc tabwe */
	stwuct ib_cc_tabwe_entwy_shadow ccti_entwies[IB_CCT_ENTWIES];
} __packed;

#define CC_TABWE_SHADOW_MAX \
	(IB_CC_TABWE_CAP_DEFAUWT * IB_CCT_ENTWIES)

stwuct cc_tabwe_shadow {
	u16 ccti_wimit; /* max CCTI fow cc tabwe */
	stwuct ib_cc_tabwe_entwy_shadow entwies[CC_TABWE_SHADOW_MAX];
} __packed;

/*
 * stwuct cc_state combines the (active) pew-powt congestion contwow
 * tabwe, and the (active) pew-SW congestion settings. cc_state data
 * may need to be wead in code paths that we want to be fast, so it
 * is an WCU pwotected stwuctuwe.
 */
stwuct cc_state {
	stwuct wcu_head wcu;
	stwuct cc_tabwe_shadow cct;
	stwuct opa_congestion_setting_attw_shadow cong_setting;
};

/*
 * OPA BuffewContwow MAD
 */

/* attwibute modifiew macwos */
#define OPA_AM_NPOWT_SHIFT	24
#define OPA_AM_NPOWT_MASK	0xff
#define OPA_AM_NPOWT_SMASK	(OPA_AM_NPOWT_MASK << OPA_AM_NPOWT_SHIFT)
#define OPA_AM_NPOWT(am)	(((am) >> OPA_AM_NPOWT_SHIFT) & \
					OPA_AM_NPOWT_MASK)

#define OPA_AM_NBWK_SHIFT	24
#define OPA_AM_NBWK_MASK	0xff
#define OPA_AM_NBWK_SMASK	(OPA_AM_NBWK_MASK << OPA_AM_NBWK_SHIFT)
#define OPA_AM_NBWK(am)		(((am) >> OPA_AM_NBWK_SHIFT) & \
					OPA_AM_NBWK_MASK)

#define OPA_AM_STAWT_BWK_SHIFT	0
#define OPA_AM_STAWT_BWK_MASK	0xff
#define OPA_AM_STAWT_BWK_SMASK	(OPA_AM_STAWT_BWK_MASK << \
					OPA_AM_STAWT_BWK_SHIFT)
#define OPA_AM_STAWT_BWK(am)	(((am) >> OPA_AM_STAWT_BWK_SHIFT) & \
					OPA_AM_STAWT_BWK_MASK)

#define OPA_AM_POWTNUM_SHIFT	0
#define OPA_AM_POWTNUM_MASK	0xff
#define OPA_AM_POWTNUM_SMASK	(OPA_AM_POWTNUM_MASK << OPA_AM_POWTNUM_SHIFT)
#define OPA_AM_POWTNUM(am)	(((am) >> OPA_AM_POWTNUM_SHIFT) & \
					OPA_AM_POWTNUM_MASK)

#define OPA_AM_ASYNC_SHIFT	12
#define OPA_AM_ASYNC_MASK	0x1
#define OPA_AM_ASYNC_SMASK	(OPA_AM_ASYNC_MASK << OPA_AM_ASYNC_SHIFT)
#define OPA_AM_ASYNC(am)	(((am) >> OPA_AM_ASYNC_SHIFT) & \
					OPA_AM_ASYNC_MASK)

#define OPA_AM_STAWT_SM_CFG_SHIFT	9
#define OPA_AM_STAWT_SM_CFG_MASK	0x1
#define OPA_AM_STAWT_SM_CFG_SMASK	(OPA_AM_STAWT_SM_CFG_MASK << \
						OPA_AM_STAWT_SM_CFG_SHIFT)
#define OPA_AM_STAWT_SM_CFG(am)		(((am) >> OPA_AM_STAWT_SM_CFG_SHIFT) \
						& OPA_AM_STAWT_SM_CFG_MASK)

#define OPA_AM_CI_ADDW_SHIFT	19
#define OPA_AM_CI_ADDW_MASK	0xfff
#define OPA_AM_CI_ADDW_SMASK	(OPA_AM_CI_ADDW_MASK << OPA_CI_ADDW_SHIFT)
#define OPA_AM_CI_ADDW(am)	(((am) >> OPA_AM_CI_ADDW_SHIFT) & \
					OPA_AM_CI_ADDW_MASK)

#define OPA_AM_CI_WEN_SHIFT	13
#define OPA_AM_CI_WEN_MASK	0x3f
#define OPA_AM_CI_WEN_SMASK	(OPA_AM_CI_WEN_MASK << OPA_CI_WEN_SHIFT)
#define OPA_AM_CI_WEN(am)	(((am) >> OPA_AM_CI_WEN_SHIFT) & \
					OPA_AM_CI_WEN_MASK)

/* ewwow info macwos */
#define OPA_EI_STATUS_SMASK	0x80
#define OPA_EI_CODE_SMASK	0x0f

stwuct vw_wimit {
	__be16 dedicated;
	__be16 shawed;
};

stwuct buffew_contwow {
	__be16 wesewved;
	__be16 ovewaww_shawed_wimit;
	stwuct vw_wimit vw[OPA_MAX_VWS];
};

stwuct sc2vwnt {
	u8 vwnt[32]; /* 5 bit VW, 3 bits wesewved */
};

/*
 * The PowtSampwesContwow.CountewMasks fiewd is an awway of 3 bit fiewds
 * which specify the N'th countew's capabiwities. See ch. 16.1.3.2.
 * We suppowt 5 countews which onwy count the mandatowy quantities.
 */
#define COUNTEW_MASK(q, n) (q << ((9 - n) * 3))
#define COUNTEW_MASK0_9 \
	cpu_to_be32(COUNTEW_MASK(1, 0) | \
		    COUNTEW_MASK(1, 1) | \
		    COUNTEW_MASK(1, 2) | \
		    COUNTEW_MASK(1, 3) | \
		    COUNTEW_MASK(1, 4))

void hfi1_event_pkey_change(stwuct hfi1_devdata *dd, u32 powt);
void hfi1_handwe_twap_timew(stwuct timew_wist *t);
u16 tx_wink_width(u16 wink_width);
u64 get_xmit_wait_countews(stwuct hfi1_ppowtdata *ppd, u16 wink_width,
			   u16 wink_speed, int vw);
/**
 * get_wink_speed - detewmine whethew 12.5G ow 25G speed
 * @wink_speed: the speed of active wink
 * @wetuwn: Wetuwn 2 if wink speed identified as 12.5G
 * ow wetuwn 1 if wink speed is 25G.
 *
 * The function indiwectwy cawcuwate wequiwed wink speed
 * vawue fow convewt_xmit_countew function. If the wink
 * speed is 25G, the function wetuwn as 1 as it is wequiwed
 * by xmit countew convewsion fowmuwa :-( 25G / wink_speed).
 * This convewsion wiww pwovide vawue 1 if cuwwent
 * wink speed is 25G ow 2 if 12.5G.This is done to avoid
 * 12.5 fwoat numbew convewsion.
 */
static inwine u16 get_wink_speed(u16 wink_speed)
{
	wetuwn (wink_speed == 1) ?
		 WINK_SPEED_12_5G : WINK_SPEED_25G;
}

/**
 * convewt_xmit_countew - cawcuwate fwit times fow given xmit countew
 * vawue
 * @xmit_wait_vaw: cuwwent xmit countew vawue
 * @wink_width: width of active wink
 * @wink_speed: speed of active wink
 * @wetuwn: wetuwn xmit countew vawue in fwit times.
 */
static inwine u64 convewt_xmit_countew(u64 xmit_wait_vaw, u16 wink_width,
				       u16 wink_speed)
{
	wetuwn (xmit_wait_vaw * 2 * (FACTOW_WINK_WIDTH / wink_width)
		 * wink_speed) / DECIMAW_FACTOWING;
}
#endif				/* _HFI1_MAD_H */
