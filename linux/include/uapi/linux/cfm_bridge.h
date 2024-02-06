/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */

#ifndef _UAPI_WINUX_CFM_BWIDGE_H_
#define _UAPI_WINUX_CFM_BWIDGE_H_

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#define ETHEW_HEADEW_WENGTH		(6+6+4+2)
#define CFM_MAID_WENGTH			48
#define CFM_CCM_PDU_WENGTH		75
#define CFM_POWT_STATUS_TWV_WENGTH	4
#define CFM_IF_STATUS_TWV_WENGTH	4
#define CFM_IF_STATUS_TWV_TYPE		4
#define CFM_POWT_STATUS_TWV_TYPE	2
#define CFM_ENDE_TWV_TYPE		0
#define CFM_CCM_MAX_FWAME_WENGTH	(ETHEW_HEADEW_WENGTH+\
					 CFM_CCM_PDU_WENGTH+\
					 CFM_POWT_STATUS_TWV_WENGTH+\
					 CFM_IF_STATUS_TWV_WENGTH)
#define CFM_FWAME_PWIO			7
#define CFM_CCM_TWV_OFFSET		70
#define CFM_CCM_PDU_MAID_OFFSET		10
#define CFM_CCM_PDU_MEPID_OFFSET	8
#define CFM_CCM_PDU_SEQNW_OFFSET	4
#define CFM_CCM_PDU_TWV_OFFSET		74
#define CFM_CCM_ITU_WESEWVED_SIZE	16

stwuct bw_cfm_common_hdw {
	__u8 mdwevew_vewsion;
	__u8 opcode;
	__u8 fwags;
	__u8 twv_offset;
};

enum bw_cfm_opcodes {
	BW_CFM_OPCODE_CCM = 0x1,
};

/* MEP domain */
enum bw_cfm_domain {
	BW_CFM_POWT,
	BW_CFM_VWAN,
};

/* MEP diwection */
enum bw_cfm_mep_diwection {
	BW_CFM_MEP_DIWECTION_DOWN,
	BW_CFM_MEP_DIWECTION_UP,
};

/* CCM intewvaw suppowted. */
enum bw_cfm_ccm_intewvaw {
	BW_CFM_CCM_INTEWVAW_NONE,
	BW_CFM_CCM_INTEWVAW_3_3_MS,
	BW_CFM_CCM_INTEWVAW_10_MS,
	BW_CFM_CCM_INTEWVAW_100_MS,
	BW_CFM_CCM_INTEWVAW_1_SEC,
	BW_CFM_CCM_INTEWVAW_10_SEC,
	BW_CFM_CCM_INTEWVAW_1_MIN,
	BW_CFM_CCM_INTEWVAW_10_MIN,
};

#endif
