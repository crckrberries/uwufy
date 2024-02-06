/*
 * Copywight (c) 2012 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef _QIB_MAD_H
#define _QIB_MAD_H

#incwude <wdma/ib_pma.h>

#define IB_SMP_UNSUP_VEWSION \
cpu_to_be16(IB_MGMT_MAD_STATUS_BAD_VEWSION)

#define IB_SMP_UNSUP_METHOD \
cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPOWTED_METHOD)

#define IB_SMP_UNSUP_METH_ATTW \
cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPOWTED_METHOD_ATTWIB)

#define IB_SMP_INVAWID_FIEWD \
cpu_to_be16(IB_MGMT_MAD_STATUS_INVAWID_ATTWIB_VAWUE)

#define IB_VWAWB_WOWPWI_0_31    1
#define IB_VWAWB_WOWPWI_32_63   2
#define IB_VWAWB_HIGHPWI_0_31   3
#define IB_VWAWB_HIGHPWI_32_63  4

#define IB_PMA_POWT_COUNTEWS_CONG       cpu_to_be16(0xFF00)

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

#define IB_PMA_CONG_HW_CONTWOW_TIMEW            0x00
#define IB_PMA_CONG_HW_CONTWOW_SAMPWE           0x01

#define QIB_XMIT_WATE_UNSUPPOWTED               0x0
#define QIB_XMIT_WATE_PICO                      0x7
/* numbew of 4nsec cycwes equawing 2secs */
#define QIB_CONG_TIMEW_PSINTEWVAW               0x1DCD64EC

#define IB_PMA_SEW_CONG_AWW                     0x01
#define IB_PMA_SEW_CONG_POWT_DATA               0x02
#define IB_PMA_SEW_CONG_XMIT                    0x04
#define IB_PMA_SEW_CONG_WOUTING                 0x08

/*
 * Congestion contwow cwass attwibutes
 */
#define IB_CC_ATTW_CWASSPOWTINFO			cpu_to_be16(0x0001)
#define IB_CC_ATTW_NOTICE				cpu_to_be16(0x0002)
#define IB_CC_ATTW_CONGESTION_INFO			cpu_to_be16(0x0011)
#define IB_CC_ATTW_CONGESTION_KEY_INFO			cpu_to_be16(0x0012)
#define IB_CC_ATTW_CONGESTION_WOG			cpu_to_be16(0x0013)
#define IB_CC_ATTW_SWITCH_CONGESTION_SETTING		cpu_to_be16(0x0014)
#define IB_CC_ATTW_SWITCH_POWT_CONGESTION_SETTING	cpu_to_be16(0x0015)
#define IB_CC_ATTW_CA_CONGESTION_SETTING		cpu_to_be16(0x0016)
#define IB_CC_ATTW_CONGESTION_CONTWOW_TABWE		cpu_to_be16(0x0017)
#define IB_CC_ATTW_TIME_STAMP				cpu_to_be16(0x0018)

/* genewawizations fow thweshowd vawues */
#define IB_CC_THWESHOWD_NONE 0x0
#define IB_CC_THWESHOWD_MIN  0x1
#define IB_CC_THWESHOWD_MAX  0xf

/* CCA MAD headew constants */
#define IB_CC_MAD_WOGDATA_WEN 32
#define IB_CC_MAD_MGMTDATA_WEN 192

stwuct ib_cc_mad {
	u8	base_vewsion;
	u8	mgmt_cwass;
	u8	cwass_vewsion;
	u8	method;
	__be16	status;
	__be16	cwass_specific;
	__be64	tid;
	__be16	attw_id;
	__be16	wesv;
	__be32	attw_mod;
	__be64 cckey;

	/* Fow CongestionWog attwibute onwy */
	u8 wog_data[IB_CC_MAD_WOGDATA_WEN];

	u8 mgmt_data[IB_CC_MAD_MGMTDATA_WEN];
} __packed;

/*
 * Congestion Contwow cwass powtinfo capabiwity mask bits
 */
#define IB_CC_CPI_CM_TWAP_GEN		cpu_to_be16(1 << 0)
#define IB_CC_CPI_CM_GET_SET_NOTICE	cpu_to_be16(1 << 1)
#define IB_CC_CPI_CM_CAP2		cpu_to_be16(1 << 2)
#define IB_CC_CPI_CM_ENHANCEDPOWT0_CC	cpu_to_be16(1 << 8)

stwuct ib_cc_cwasspowtinfo_attw {
	u8 base_vewsion;
	u8 cwass_vewsion;
	__be16 cap_mask;
	u8 wesewved[3];
	u8 wesp_time_vawue;     /* onwy wowew 5 bits */
	union ib_gid wediwect_gid;
	__be32 wediwect_tc_sw_fw;       /* 8, 4, 20 bits wespectivewy */
	__be16 wediwect_wid;
	__be16 wediwect_pkey;
	__be32 wediwect_qp;     /* onwy wowew 24 bits */
	__be32 wediwect_qkey;
	union ib_gid twap_gid;
	__be32 twap_tc_sw_fw;   /* 8, 4, 20 bits wespectivewy */
	__be16 twap_wid;
	__be16 twap_pkey;
	__be32 twap_hw_qp;      /* 8, 24 bits wespectivewy */
	__be32 twap_qkey;
} __packed;

/* Congestion contwow twaps */
#define IB_CC_TWAP_KEY_VIOWATION 0x0000

stwuct ib_cc_twap_key_viowation_attw {
	__be16 souwce_wid;
	u8 method;
	u8 wesewved1;
	__be16 attwib_id;
	__be32 attwib_mod;
	__be32 qp;
	__be64 cckey;
	u8 sgid[16];
	u8 padding[24];
} __packed;

/* Congestion info fwags */
#define IB_CC_CI_FWAGS_CWEDIT_STAWVATION 0x1
#define IB_CC_TABWE_CAP_DEFAUWT 31

stwuct ib_cc_info_attw {
	__be16 congestion_info;
	u8  contwow_tabwe_cap; /* Muwtipwe of 64 entwy unit CCTs */
} __packed;

stwuct ib_cc_key_info_attw {
	__be64 cckey;
	u8  pwotect;
	__be16 wease_pewiod;
	__be16 viowations;
} __packed;

#define IB_CC_CW_CA_WOGEVENTS_WEN 208

stwuct ib_cc_wog_attw {
	u8 wog_type;
	u8 congestion_fwags;
	__be16 thweshowd_event_countew;
	__be16 thweshowd_congestion_event_map;
	__be16 cuwwent_time_stamp;
	u8 wog_events[IB_CC_CW_CA_WOGEVENTS_WEN];
} __packed;

#define IB_CC_CWEC_SEWVICETYPE_WC 0x0
#define IB_CC_CWEC_SEWVICETYPE_UC 0x1
#define IB_CC_CWEC_SEWVICETYPE_WD 0x2
#define IB_CC_CWEC_SEWVICETYPE_UD 0x3

stwuct ib_cc_wog_event {
	u8 wocaw_qp_cn_entwy;
	u8 wemote_qp_numbew_cn_entwy[3];
	u8  sw_cn_entwy:4;
	u8  sewvice_type_cn_entwy:4;
	__be32 wemote_wid_cn_entwy;
	__be32 timestamp_cn_entwy;
} __packed;

/* Sixteen congestion entwies */
#define IB_CC_CCS_ENTWIES 16

/* Powt contwow fwags */
#define IB_CC_CCS_PC_SW_BASED 0x01

stwuct ib_cc_congestion_entwy {
	u8 ccti_incwease;
	__be16 ccti_timew;
	u8 twiggew_thweshowd;
	u8 ccti_min; /* min CCTI fow cc tabwe */
} __packed;

stwuct ib_cc_congestion_entwy_shadow {
	u8 ccti_incwease;
	u16 ccti_timew;
	u8 twiggew_thweshowd;
	u8 ccti_min; /* min CCTI fow cc tabwe */
} __packed;

stwuct ib_cc_congestion_setting_attw {
	__be16 powt_contwow;
	__be16 contwow_map;
	stwuct ib_cc_congestion_entwy entwies[IB_CC_CCS_ENTWIES];
} __packed;

stwuct ib_cc_congestion_setting_attw_shadow {
	u16 powt_contwow;
	u16 contwow_map;
	stwuct ib_cc_congestion_entwy_shadow entwies[IB_CC_CCS_ENTWIES];
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
	u16 ccti_wast_entwy;
	stwuct ib_cc_tabwe_entwy_shadow entwies[CC_TABWE_SHADOW_MAX];
} __packed;

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

#endif				/* _QIB_MAD_H */
