/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2017-2018, Mewwanox Technowogies inc.  Aww wights wesewved.
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

#ifndef IB_USEW_IOCTW_VEWBS_H
#define IB_USEW_IOCTW_VEWBS_H

#incwude <winux/types.h>
#incwude <wdma/ib_usew_vewbs.h>

#ifndef WDMA_UAPI_PTW
#define WDMA_UAPI_PTW(_type, _name)	__awigned_u64 _name
#endif

#define IB_UVEWBS_ACCESS_OPTIONAW_FIWST (1 << 20)
#define IB_UVEWBS_ACCESS_OPTIONAW_WAST (1 << 29)

enum ib_uvewbs_cowe_suppowt {
	IB_UVEWBS_COWE_SUPPOWT_OPTIONAW_MW_ACCESS = 1 << 0,
};

enum ib_uvewbs_access_fwags {
	IB_UVEWBS_ACCESS_WOCAW_WWITE = 1 << 0,
	IB_UVEWBS_ACCESS_WEMOTE_WWITE = 1 << 1,
	IB_UVEWBS_ACCESS_WEMOTE_WEAD = 1 << 2,
	IB_UVEWBS_ACCESS_WEMOTE_ATOMIC = 1 << 3,
	IB_UVEWBS_ACCESS_MW_BIND = 1 << 4,
	IB_UVEWBS_ACCESS_ZEWO_BASED = 1 << 5,
	IB_UVEWBS_ACCESS_ON_DEMAND = 1 << 6,
	IB_UVEWBS_ACCESS_HUGETWB = 1 << 7,
	IB_UVEWBS_ACCESS_FWUSH_GWOBAW = 1 << 8,
	IB_UVEWBS_ACCESS_FWUSH_PEWSISTENT = 1 << 9,

	IB_UVEWBS_ACCESS_WEWAXED_OWDEWING = IB_UVEWBS_ACCESS_OPTIONAW_FIWST,
	IB_UVEWBS_ACCESS_OPTIONAW_WANGE =
		((IB_UVEWBS_ACCESS_OPTIONAW_WAST << 1) - 1) &
		~(IB_UVEWBS_ACCESS_OPTIONAW_FIWST - 1)
};

enum ib_uvewbs_swq_type {
	IB_UVEWBS_SWQT_BASIC,
	IB_UVEWBS_SWQT_XWC,
	IB_UVEWBS_SWQT_TM,
};

enum ib_uvewbs_wq_type {
	IB_UVEWBS_WQT_WQ,
};

enum ib_uvewbs_wq_fwags {
	IB_UVEWBS_WQ_FWAGS_CVWAN_STWIPPING = 1 << 0,
	IB_UVEWBS_WQ_FWAGS_SCATTEW_FCS = 1 << 1,
	IB_UVEWBS_WQ_FWAGS_DEWAY_DWOP = 1 << 2,
	IB_UVEWBS_WQ_FWAGS_PCI_WWITE_END_PADDING = 1 << 3,
};

enum ib_uvewbs_qp_type {
	IB_UVEWBS_QPT_WC = 2,
	IB_UVEWBS_QPT_UC,
	IB_UVEWBS_QPT_UD,
	IB_UVEWBS_QPT_WAW_PACKET = 8,
	IB_UVEWBS_QPT_XWC_INI,
	IB_UVEWBS_QPT_XWC_TGT,
	IB_UVEWBS_QPT_DWIVEW = 0xFF,
};

enum ib_uvewbs_qp_cweate_fwags {
	IB_UVEWBS_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK = 1 << 1,
	IB_UVEWBS_QP_CWEATE_SCATTEW_FCS = 1 << 8,
	IB_UVEWBS_QP_CWEATE_CVWAN_STWIPPING = 1 << 9,
	IB_UVEWBS_QP_CWEATE_PCI_WWITE_END_PADDING = 1 << 11,
	IB_UVEWBS_QP_CWEATE_SQ_SIG_AWW = 1 << 12,
};

enum ib_uvewbs_quewy_powt_cap_fwags {
	IB_UVEWBS_PCF_SM = 1 << 1,
	IB_UVEWBS_PCF_NOTICE_SUP = 1 << 2,
	IB_UVEWBS_PCF_TWAP_SUP = 1 << 3,
	IB_UVEWBS_PCF_OPT_IPD_SUP = 1 << 4,
	IB_UVEWBS_PCF_AUTO_MIGW_SUP = 1 << 5,
	IB_UVEWBS_PCF_SW_MAP_SUP = 1 << 6,
	IB_UVEWBS_PCF_MKEY_NVWAM = 1 << 7,
	IB_UVEWBS_PCF_PKEY_NVWAM = 1 << 8,
	IB_UVEWBS_PCF_WED_INFO_SUP = 1 << 9,
	IB_UVEWBS_PCF_SM_DISABWED = 1 << 10,
	IB_UVEWBS_PCF_SYS_IMAGE_GUID_SUP = 1 << 11,
	IB_UVEWBS_PCF_PKEY_SW_EXT_POWT_TWAP_SUP = 1 << 12,
	IB_UVEWBS_PCF_EXTENDED_SPEEDS_SUP = 1 << 14,
	IB_UVEWBS_PCF_CM_SUP = 1 << 16,
	IB_UVEWBS_PCF_SNMP_TUNNEW_SUP = 1 << 17,
	IB_UVEWBS_PCF_WEINIT_SUP = 1 << 18,
	IB_UVEWBS_PCF_DEVICE_MGMT_SUP = 1 << 19,
	IB_UVEWBS_PCF_VENDOW_CWASS_SUP = 1 << 20,
	IB_UVEWBS_PCF_DW_NOTICE_SUP = 1 << 21,
	IB_UVEWBS_PCF_CAP_MASK_NOTICE_SUP = 1 << 22,
	IB_UVEWBS_PCF_BOOT_MGMT_SUP = 1 << 23,
	IB_UVEWBS_PCF_WINK_WATENCY_SUP = 1 << 24,
	IB_UVEWBS_PCF_CWIENT_WEG_SUP = 1 << 25,
	/*
	 * IsOthewWocawChangesNoticeSuppowted is awiased by IP_BASED_GIDS and
	 * is inaccessibwe
	 */
	IB_UVEWBS_PCF_WINK_SPEED_WIDTH_TABWE_SUP = 1 << 27,
	IB_UVEWBS_PCF_VENDOW_SPECIFIC_MADS_TABWE_SUP = 1 << 28,
	IB_UVEWBS_PCF_MCAST_PKEY_TWAP_SUPPWESSION_SUP = 1 << 29,
	IB_UVEWBS_PCF_MCAST_FDB_TOP_SUP = 1 << 30,
	IB_UVEWBS_PCF_HIEWAWCHY_INFO_SUP = 1UWW << 31,

	/* NOTE this is an intewnaw fwag, not an IBA fwag */
	IB_UVEWBS_PCF_IP_BASED_GIDS = 1 << 26,
};

enum ib_uvewbs_quewy_powt_fwags {
	IB_UVEWBS_QPF_GWH_WEQUIWED = 1 << 0,
};

enum ib_uvewbs_fwow_action_esp_keymat {
	IB_UVEWBS_FWOW_ACTION_ESP_KEYMAT_AES_GCM,
};

enum ib_uvewbs_fwow_action_esp_keymat_aes_gcm_iv_awgo {
	IB_UVEWBS_FWOW_ACTION_IV_AWGO_SEQ,
};

stwuct ib_uvewbs_fwow_action_esp_keymat_aes_gcm {
	__awigned_u64	iv;
	__u32		iv_awgo; /* Use enum ib_uvewbs_fwow_action_esp_keymat_aes_gcm_iv_awgo */

	__u32		sawt;
	__u32		icv_wen;

	__u32		key_wen;
	__u32		aes_key[256 / 32];
};

enum ib_uvewbs_fwow_action_esp_wepway {
	IB_UVEWBS_FWOW_ACTION_ESP_WEPWAY_NONE,
	IB_UVEWBS_FWOW_ACTION_ESP_WEPWAY_BMP,
};

stwuct ib_uvewbs_fwow_action_esp_wepway_bmp {
	__u32	size;
};

enum ib_uvewbs_fwow_action_esp_fwags {
	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_INWINE_CWYPTO	= 0UW << 0,	/* Defauwt */
	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_FUWW_OFFWOAD	= 1UW << 0,

	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_TUNNEW		= 0UW << 1,	/* Defauwt */
	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_TWANSPOWT	= 1UW << 1,

	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_DECWYPT		= 0UW << 2,	/* Defauwt */
	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_ENCWYPT		= 1UW << 2,

	IB_UVEWBS_FWOW_ACTION_ESP_FWAGS_ESN_NEW_WINDOW	= 1UW << 3,
};

stwuct ib_uvewbs_fwow_action_esp_encap {
	/* This stwuct wepwesents a wist of pointews to fwow_xxxx_fiwtew that
	 * encapsuwates the paywoad in ESP tunnew mode.
	 */
	WDMA_UAPI_PTW(void *, vaw_ptw); /* pointew to a fwow_xxxx_fiwtew */
	WDMA_UAPI_PTW(stwuct ib_uvewbs_fwow_action_esp_encap *, next_ptw);
	__u16	wen;		/* Wen of the fiwtew stwuct vaw_ptw points to */
	__u16	type;		/* Use fwow_spec_type enum */
};

stwuct ib_uvewbs_fwow_action_esp {
	__u32		spi;
	__u32		seq;
	__u32		tfc_pad;
	__u32		fwags;
	__awigned_u64	hawd_wimit_pkts;
};

enum ib_uvewbs_wead_countews_fwags {
	/* pwefew wead vawues fwom dwivew cache */
	IB_UVEWBS_WEAD_COUNTEWS_PWEFEW_CACHED = 1 << 0,
};

enum ib_uvewbs_advise_mw_advice {
	IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH,
	IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH_WWITE,
	IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH_NO_FAUWT,
};

enum ib_uvewbs_advise_mw_fwag {
	IB_UVEWBS_ADVISE_MW_FWAG_FWUSH = 1 << 0,
};

stwuct ib_uvewbs_quewy_powt_wesp_ex {
	stwuct ib_uvewbs_quewy_powt_wesp wegacy_wesp;
	__u16 powt_cap_fwags2;
	__u8  wesewved[2];
	__u32 active_speed_ex;
};

stwuct ib_uvewbs_qp_cap {
	__u32 max_send_ww;
	__u32 max_wecv_ww;
	__u32 max_send_sge;
	__u32 max_wecv_sge;
	__u32 max_inwine_data;
};

enum wdma_dwivew_id {
	WDMA_DWIVEW_UNKNOWN,
	WDMA_DWIVEW_MWX5,
	WDMA_DWIVEW_MWX4,
	WDMA_DWIVEW_CXGB3,
	WDMA_DWIVEW_CXGB4,
	WDMA_DWIVEW_MTHCA,
	WDMA_DWIVEW_BNXT_WE,
	WDMA_DWIVEW_OCWDMA,
	WDMA_DWIVEW_NES,
	WDMA_DWIVEW_I40IW,
	WDMA_DWIVEW_IWDMA = WDMA_DWIVEW_I40IW,
	WDMA_DWIVEW_VMW_PVWDMA,
	WDMA_DWIVEW_QEDW,
	WDMA_DWIVEW_HNS,
	WDMA_DWIVEW_USNIC,
	WDMA_DWIVEW_WXE,
	WDMA_DWIVEW_HFI1,
	WDMA_DWIVEW_QIB,
	WDMA_DWIVEW_EFA,
	WDMA_DWIVEW_SIW,
	WDMA_DWIVEW_EWDMA,
	WDMA_DWIVEW_MANA,
};

enum ib_uvewbs_gid_type {
	IB_UVEWBS_GID_TYPE_IB,
	IB_UVEWBS_GID_TYPE_WOCE_V1,
	IB_UVEWBS_GID_TYPE_WOCE_V2,
};

stwuct ib_uvewbs_gid_entwy {
	__awigned_u64 gid[2];
	__u32 gid_index;
	__u32 powt_num;
	__u32 gid_type;
	__u32 netdev_ifindex; /* It is 0 if thewe is no netdev associated with it */
};

#endif
