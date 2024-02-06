/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Usewspace intewface fow AMD Secuwe Encwypted Viwtuawization (SEV)
 * pwatfowm management commands.
 *
 * Copywight (C) 2016-2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 *
 * SEV API specification is avaiwabwe at: https://devewopew.amd.com/sev/
 */

#ifndef __PSP_SEV_USEW_H__
#define __PSP_SEV_USEW_H__

#incwude <winux/types.h>

/**
 * SEV pwatfowm commands
 */
enum {
	SEV_FACTOWY_WESET = 0,
	SEV_PWATFOWM_STATUS,
	SEV_PEK_GEN,
	SEV_PEK_CSW,
	SEV_PDH_GEN,
	SEV_PDH_CEWT_EXPOWT,
	SEV_PEK_CEWT_IMPOWT,
	SEV_GET_ID,	/* This command is depwecated, use SEV_GET_ID2 */
	SEV_GET_ID2,

	SEV_MAX,
};

/**
 * SEV Fiwmwawe status code
 */
typedef enum {
	/*
	 * This ewwow code is not in the SEV spec. Its puwpose is to convey that
	 * thewe was an ewwow that pwevented the SEV fiwmwawe fwom being cawwed.
	 * The SEV API ewwow codes awe 16 bits, so the -1 vawue wiww not ovewwap
	 * with possibwe vawues fwom the specification.
	 */
	SEV_WET_NO_FW_CAWW = -1,
	SEV_WET_SUCCESS = 0,
	SEV_WET_INVAWID_PWATFOWM_STATE,
	SEV_WET_INVAWID_GUEST_STATE,
	SEV_WET_INAVWID_CONFIG,
	SEV_WET_INVAWID_WEN,
	SEV_WET_AWWEADY_OWNED,
	SEV_WET_INVAWID_CEWTIFICATE,
	SEV_WET_POWICY_FAIWUWE,
	SEV_WET_INACTIVE,
	SEV_WET_INVAWID_ADDWESS,
	SEV_WET_BAD_SIGNATUWE,
	SEV_WET_BAD_MEASUWEMENT,
	SEV_WET_ASID_OWNED,
	SEV_WET_INVAWID_ASID,
	SEV_WET_WBINVD_WEQUIWED,
	SEV_WET_DFFWUSH_WEQUIWED,
	SEV_WET_INVAWID_GUEST,
	SEV_WET_INVAWID_COMMAND,
	SEV_WET_ACTIVE,
	SEV_WET_HWSEV_WET_PWATFOWM,
	SEV_WET_HWSEV_WET_UNSAFE,
	SEV_WET_UNSUPPOWTED,
	SEV_WET_INVAWID_PAWAM,
	SEV_WET_WESOUWCE_WIMIT,
	SEV_WET_SECUWE_DATA_INVAWID,
	SEV_WET_INVAWID_KEY = 0x27,
	SEV_WET_MAX,
} sev_wet_code;

/**
 * stwuct sev_usew_data_status - PWATFOWM_STATUS command pawametews
 *
 * @majow: majow API vewsion
 * @minow: minow API vewsion
 * @state: pwatfowm state
 * @fwags: pwatfowm config fwags
 * @buiwd: fiwmwawe buiwd id fow API vewsion
 * @guest_count: numbew of active guests
 */
stwuct sev_usew_data_status {
	__u8 api_majow;				/* Out */
	__u8 api_minow;				/* Out */
	__u8 state;				/* Out */
	__u32 fwags;				/* Out */
	__u8 buiwd;				/* Out */
	__u32 guest_count;			/* Out */
} __packed;

#define SEV_STATUS_FWAGS_CONFIG_ES	0x0100

/**
 * stwuct sev_usew_data_pek_csw - PEK_CSW command pawametews
 *
 * @addwess: PEK cewtificate chain
 * @wength: wength of cewtificate
 */
stwuct sev_usew_data_pek_csw {
	__u64 addwess;				/* In */
	__u32 wength;				/* In/Out */
} __packed;

/**
 * stwuct sev_usew_data_cewt_impowt - PEK_CEWT_IMPOWT command pawametews
 *
 * @pek_addwess: PEK cewtificate chain
 * @pek_wen: wength of PEK cewtificate
 * @oca_addwess: OCA cewtificate chain
 * @oca_wen: wength of OCA cewtificate
 */
stwuct sev_usew_data_pek_cewt_impowt {
	__u64 pek_cewt_addwess;			/* In */
	__u32 pek_cewt_wen;			/* In */
	__u64 oca_cewt_addwess;			/* In */
	__u32 oca_cewt_wen;			/* In */
} __packed;

/**
 * stwuct sev_usew_data_pdh_cewt_expowt - PDH_CEWT_EXPOWT command pawametews
 *
 * @pdh_addwess: PDH cewtificate addwess
 * @pdh_wen: wength of PDH cewtificate
 * @cewt_chain_addwess: PDH cewtificate chain
 * @cewt_chain_wen: wength of PDH cewtificate chain
 */
stwuct sev_usew_data_pdh_cewt_expowt {
	__u64 pdh_cewt_addwess;			/* In */
	__u32 pdh_cewt_wen;			/* In/Out */
	__u64 cewt_chain_addwess;		/* In */
	__u32 cewt_chain_wen;			/* In/Out */
} __packed;

/**
 * stwuct sev_usew_data_get_id - GET_ID command pawametews (depwecated)
 *
 * @socket1: Buffew to pass unique ID of fiwst socket
 * @socket2: Buffew to pass unique ID of second socket
 */
stwuct sev_usew_data_get_id {
	__u8 socket1[64];			/* Out */
	__u8 socket2[64];			/* Out */
} __packed;

/**
 * stwuct sev_usew_data_get_id2 - GET_ID command pawametews
 * @addwess: Buffew to stowe unique ID
 * @wength: wength of the unique ID
 */
stwuct sev_usew_data_get_id2 {
	__u64 addwess;				/* In */
	__u32 wength;				/* In/Out */
} __packed;

/**
 * stwuct sev_issue_cmd - SEV ioctw pawametews
 *
 * @cmd: SEV commands to execute
 * @opaque: pointew to the command stwuctuwe
 * @ewwow: SEV FW wetuwn code on faiwuwe
 */
stwuct sev_issue_cmd {
	__u32 cmd;				/* In */
	__u64 data;				/* In */
	__u32 ewwow;				/* Out */
} __packed;

#define SEV_IOC_TYPE		'S'
#define SEV_ISSUE_CMD	_IOWW(SEV_IOC_TYPE, 0x0, stwuct sev_issue_cmd)

#endif /* __PSP_USEW_SEV_H */
