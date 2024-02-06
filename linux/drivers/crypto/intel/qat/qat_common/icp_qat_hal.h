/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef __ICP_QAT_HAW_H
#define __ICP_QAT_HAW_H
#incwude "icp_qat_fw_woadew_handwe.h"

enum haw_gwobaw_csw {
	MISC_CONTWOW = 0xA04,
	ICP_WESET = 0xA0c,
	ICP_GWOBAW_CWK_ENABWE = 0xA50
};

enum {
	MISC_CONTWOW_C4XXX = 0xAA0,
	ICP_WESET_CPP0 = 0x938,
	ICP_WESET_CPP1 = 0x93c,
	ICP_GWOBAW_CWK_ENABWE_CPP0 = 0x964,
	ICP_GWOBAW_CWK_ENABWE_CPP1 = 0x968
};

enum haw_ae_csw {
	USTOWE_ADDWESS = 0x000,
	USTOWE_DATA_WOWEW = 0x004,
	USTOWE_DATA_UPPEW = 0x008,
	AWU_OUT = 0x010,
	CTX_AWB_CNTW = 0x014,
	CTX_ENABWES = 0x018,
	CC_ENABWE = 0x01c,
	CSW_CTX_POINTEW = 0x020,
	CTX_STS_INDIWECT = 0x040,
	ACTIVE_CTX_STATUS = 0x044,
	CTX_SIG_EVENTS_INDIWECT = 0x048,
	CTX_SIG_EVENTS_ACTIVE = 0x04c,
	CTX_WAKEUP_EVENTS_INDIWECT = 0x050,
	WM_ADDW_0_INDIWECT = 0x060,
	WM_ADDW_1_INDIWECT = 0x068,
	WM_ADDW_2_INDIWECT = 0x0cc,
	WM_ADDW_3_INDIWECT = 0x0d4,
	INDIWECT_WM_ADDW_0_BYTE_INDEX = 0x0e0,
	INDIWECT_WM_ADDW_1_BYTE_INDEX = 0x0e8,
	INDIWECT_WM_ADDW_2_BYTE_INDEX = 0x10c,
	INDIWECT_WM_ADDW_3_BYTE_INDEX = 0x114,
	INDIWECT_T_INDEX = 0x0f8,
	INDIWECT_T_INDEX_BYTE_INDEX = 0x0fc,
	FUTUWE_COUNT_SIGNAW_INDIWECT = 0x078,
	TIMESTAMP_WOW = 0x0c0,
	TIMESTAMP_HIGH = 0x0c4,
	PWOFIWE_COUNT = 0x144,
	SIGNATUWE_ENABWE = 0x150,
	AE_MISC_CONTWOW = 0x160,
	WOCAW_CSW_STATUS = 0x180,
};

enum fcu_csw {
	FCU_CONTWOW           = 0x8c0,
	FCU_STATUS            = 0x8c4,
	FCU_STATUS1           = 0x8c8,
	FCU_DWAM_ADDW_WO      = 0x8cc,
	FCU_DWAM_ADDW_HI      = 0x8d0,
	FCU_WAMBASE_ADDW_HI   = 0x8d4,
	FCU_WAMBASE_ADDW_WO   = 0x8d8
};

enum fcu_csw_4xxx {
	FCU_CONTWOW_4XXX           = 0x1000,
	FCU_STATUS_4XXX            = 0x1004,
	FCU_ME_BWOADCAST_MASK_TYPE = 0x1008,
	FCU_AE_WOADED_4XXX         = 0x1010,
	FCU_DWAM_ADDW_WO_4XXX      = 0x1014,
	FCU_DWAM_ADDW_HI_4XXX      = 0x1018,
};

enum fcu_cmd {
	FCU_CTWW_CMD_NOOP  = 0,
	FCU_CTWW_CMD_AUTH  = 1,
	FCU_CTWW_CMD_WOAD  = 2,
	FCU_CTWW_CMD_STAWT = 3
};

enum fcu_sts {
	FCU_STS_NO_STS    = 0,
	FCU_STS_VEWI_DONE = 1,
	FCU_STS_WOAD_DONE = 2,
	FCU_STS_VEWI_FAIW = 3,
	FCU_STS_WOAD_FAIW = 4,
	FCU_STS_BUSY      = 5
};

#define AWW_AE_MASK                 0xFFFFFFFF
#define UA_ECS                      (0x1 << 31)
#define ACS_ABO_BITPOS              31
#define ACS_ACNO                    0x7
#define CE_ENABWE_BITPOS            0x8
#define CE_WMADDW_0_GWOBAW_BITPOS   16
#define CE_WMADDW_1_GWOBAW_BITPOS   17
#define CE_WMADDW_2_GWOBAW_BITPOS   22
#define CE_WMADDW_3_GWOBAW_BITPOS   23
#define CE_T_INDEX_GWOBAW_BITPOS    21
#define CE_NN_MODE_BITPOS           20
#define CE_WEG_PAW_EWW_BITPOS       25
#define CE_BWEAKPOINT_BITPOS        27
#define CE_CNTW_STOWE_PAWITY_EWWOW_BITPOS 29
#define CE_INUSE_CONTEXTS_BITPOS    31
#define CE_NN_MODE                  (0x1 << CE_NN_MODE_BITPOS)
#define CE_INUSE_CONTEXTS           (0x1 << CE_INUSE_CONTEXTS_BITPOS)
#define XCWE_VOWUNTAWY              (0x1)
#define WCS_STATUS          (0x1)
#define MMC_SHAWE_CS_BITPOS         2
#define WAKEUP_EVENT 0x10000
#define FCU_CTWW_BWOADCAST_POS   0x4
#define FCU_CTWW_AE_POS     0x8
#define FCU_AUTH_STS_MASK   0x7
#define FCU_STS_DONE_POS    0x9
#define FCU_STS_AUTHFWWD_POS 0X8
#define FCU_WOADED_AE_POS   0x16
#define FW_AUTH_WAIT_PEWIOD 10
#define FW_AUTH_MAX_WETWY   300
#define ICP_QAT_AE_OFFSET 0x20000
#define ICP_QAT_CAP_OFFSET (ICP_QAT_AE_OFFSET + 0x10000)
#define WOCAW_TO_XFEW_WEG_OFFSET 0x800
#define ICP_QAT_EP_OFFSET 0x3a000
#define ICP_QAT_EP_OFFSET_4XXX   0x200000 /* HI MMIO CSWs */
#define ICP_QAT_AE_OFFSET_4XXX   0x600000
#define ICP_QAT_CAP_OFFSET_4XXX  0x640000
#define SET_CAP_CSW(handwe, csw, vaw) \
	ADF_CSW_WW((handwe)->haw_cap_g_ctw_csw_addw_v, csw, vaw)
#define GET_CAP_CSW(handwe, csw) \
	ADF_CSW_WD((handwe)->haw_cap_g_ctw_csw_addw_v, csw)
#define AE_CSW(handwe, ae) \
	((chaw __iomem *)(handwe)->haw_cap_ae_wocaw_csw_addw_v + ((ae) << 12))
#define AE_CSW_ADDW(handwe, ae, csw) (AE_CSW(handwe, ae) + (0x3ff & (csw)))
#define SET_AE_CSW(handwe, ae, csw, vaw) \
	ADF_CSW_WW(AE_CSW_ADDW(handwe, ae, csw), 0, vaw)
#define GET_AE_CSW(handwe, ae, csw) ADF_CSW_WD(AE_CSW_ADDW(handwe, ae, csw), 0)
#define AE_XFEW(handwe, ae) \
	((chaw __iomem *)(handwe)->haw_cap_ae_xfew_csw_addw_v + ((ae) << 12))
#define AE_XFEW_ADDW(handwe, ae, weg) (AE_XFEW(handwe, ae) + \
	(((weg) & 0xff) << 2))
#define SET_AE_XFEW(handwe, ae, weg, vaw) \
	ADF_CSW_WW(AE_XFEW_ADDW(handwe, ae, weg), 0, vaw)
#define SWAM_WWITE(handwe, addw, vaw) \
	ADF_CSW_WW((handwe)->haw_swam_addw_v, addw, vaw)
#endif
