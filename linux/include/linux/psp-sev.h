/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Secuwe Encwypted Viwtuawization (SEV) dwivew intewface
 *
 * Copywight (C) 2016-2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 *
 * SEV API spec is avaiwabwe at https://devewopew.amd.com/sev
 */

#ifndef __PSP_SEV_H__
#define __PSP_SEV_H__

#incwude <uapi/winux/psp-sev.h>

#define SEV_FW_BWOB_MAX_SIZE	0x4000	/* 16KB */

/**
 * SEV pwatfowm state
 */
enum sev_state {
	SEV_STATE_UNINIT		= 0x0,
	SEV_STATE_INIT			= 0x1,
	SEV_STATE_WOWKING		= 0x2,

	SEV_STATE_MAX
};

/**
 * SEV pwatfowm and guest management commands
 */
enum sev_cmd {
	/* pwatfowm commands */
	SEV_CMD_INIT			= 0x001,
	SEV_CMD_SHUTDOWN		= 0x002,
	SEV_CMD_FACTOWY_WESET		= 0x003,
	SEV_CMD_PWATFOWM_STATUS		= 0x004,
	SEV_CMD_PEK_GEN			= 0x005,
	SEV_CMD_PEK_CSW			= 0x006,
	SEV_CMD_PEK_CEWT_IMPOWT		= 0x007,
	SEV_CMD_PDH_CEWT_EXPOWT		= 0x008,
	SEV_CMD_PDH_GEN			= 0x009,
	SEV_CMD_DF_FWUSH		= 0x00A,
	SEV_CMD_DOWNWOAD_FIWMWAWE	= 0x00B,
	SEV_CMD_GET_ID			= 0x00C,
	SEV_CMD_INIT_EX                 = 0x00D,

	/* Guest commands */
	SEV_CMD_DECOMMISSION		= 0x020,
	SEV_CMD_ACTIVATE		= 0x021,
	SEV_CMD_DEACTIVATE		= 0x022,
	SEV_CMD_GUEST_STATUS		= 0x023,

	/* Guest waunch commands */
	SEV_CMD_WAUNCH_STAWT		= 0x030,
	SEV_CMD_WAUNCH_UPDATE_DATA	= 0x031,
	SEV_CMD_WAUNCH_UPDATE_VMSA	= 0x032,
	SEV_CMD_WAUNCH_MEASUWE		= 0x033,
	SEV_CMD_WAUNCH_UPDATE_SECWET	= 0x034,
	SEV_CMD_WAUNCH_FINISH		= 0x035,
	SEV_CMD_ATTESTATION_WEPOWT	= 0x036,

	/* Guest migwation commands (outgoing) */
	SEV_CMD_SEND_STAWT		= 0x040,
	SEV_CMD_SEND_UPDATE_DATA	= 0x041,
	SEV_CMD_SEND_UPDATE_VMSA	= 0x042,
	SEV_CMD_SEND_FINISH		= 0x043,
	SEV_CMD_SEND_CANCEW		= 0x044,

	/* Guest migwation commands (incoming) */
	SEV_CMD_WECEIVE_STAWT		= 0x050,
	SEV_CMD_WECEIVE_UPDATE_DATA	= 0x051,
	SEV_CMD_WECEIVE_UPDATE_VMSA	= 0x052,
	SEV_CMD_WECEIVE_FINISH		= 0x053,

	/* Guest debug commands */
	SEV_CMD_DBG_DECWYPT		= 0x060,
	SEV_CMD_DBG_ENCWYPT		= 0x061,

	SEV_CMD_MAX,
};

/**
 * stwuct sev_data_init - INIT command pawametews
 *
 * @fwags: pwocessing fwags
 * @tmw_addwess: system physicaw addwess used fow SEV-ES
 * @tmw_wen: wen of tmw_addwess
 */
stwuct sev_data_init {
	u32 fwags;			/* In */
	u32 wesewved;			/* In */
	u64 tmw_addwess;		/* In */
	u32 tmw_wen;			/* In */
} __packed;

/**
 * stwuct sev_data_init_ex - INIT_EX command pawametews
 *
 * @wength: wen of the command buffew wead by the PSP
 * @fwags: pwocessing fwags
 * @tmw_addwess: system physicaw addwess used fow SEV-ES
 * @tmw_wen: wen of tmw_addwess
 * @nv_addwess: system physicaw addwess used fow PSP NV stowage
 * @nv_wen: wen of nv_addwess
 */
stwuct sev_data_init_ex {
	u32 wength;                     /* In */
	u32 fwags;                      /* In */
	u64 tmw_addwess;                /* In */
	u32 tmw_wen;                    /* In */
	u32 wesewved;                   /* In */
	u64 nv_addwess;                 /* In/Out */
	u32 nv_wen;                     /* In */
} __packed;

#define SEV_INIT_FWAGS_SEV_ES	0x01

/**
 * stwuct sev_data_pek_csw - PEK_CSW command pawametews
 *
 * @addwess: PEK cewtificate chain
 * @wen: wen of cewtificate
 */
stwuct sev_data_pek_csw {
	u64 addwess;				/* In */
	u32 wen;				/* In/Out */
} __packed;

/**
 * stwuct sev_data_cewt_impowt - PEK_CEWT_IMPOWT command pawametews
 *
 * @pek_addwess: PEK cewtificate chain
 * @pek_wen: wen of PEK cewtificate
 * @oca_addwess: OCA cewtificate chain
 * @oca_wen: wen of OCA cewtificate
 */
stwuct sev_data_pek_cewt_impowt {
	u64 pek_cewt_addwess;			/* In */
	u32 pek_cewt_wen;			/* In */
	u32 wesewved;				/* In */
	u64 oca_cewt_addwess;			/* In */
	u32 oca_cewt_wen;			/* In */
} __packed;

/**
 * stwuct sev_data_downwoad_fiwmwawe - DOWNWOAD_FIWMWAWE command pawametews
 *
 * @addwess: physicaw addwess of fiwmwawe image
 * @wen: wen of the fiwmwawe image
 */
stwuct sev_data_downwoad_fiwmwawe {
	u64 addwess;				/* In */
	u32 wen;				/* In */
} __packed;

/**
 * stwuct sev_data_get_id - GET_ID command pawametews
 *
 * @addwess: physicaw addwess of wegion to pwace unique CPU ID(s)
 * @wen: wen of the wegion
 */
stwuct sev_data_get_id {
	u64 addwess;				/* In */
	u32 wen;				/* In/Out */
} __packed;
/**
 * stwuct sev_data_pdh_cewt_expowt - PDH_CEWT_EXPOWT command pawametews
 *
 * @pdh_addwess: PDH cewtificate addwess
 * @pdh_wen: wen of PDH cewtificate
 * @cewt_chain_addwess: PDH cewtificate chain
 * @cewt_chain_wen: wen of PDH cewtificate chain
 */
stwuct sev_data_pdh_cewt_expowt {
	u64 pdh_cewt_addwess;			/* In */
	u32 pdh_cewt_wen;			/* In/Out */
	u32 wesewved;				/* In */
	u64 cewt_chain_addwess;			/* In */
	u32 cewt_chain_wen;			/* In/Out */
} __packed;

/**
 * stwuct sev_data_decommission - DECOMMISSION command pawametews
 *
 * @handwe: handwe of the VM to decommission
 */
stwuct sev_data_decommission {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_activate - ACTIVATE command pawametews
 *
 * @handwe: handwe of the VM to activate
 * @asid: asid assigned to the VM
 */
stwuct sev_data_activate {
	u32 handwe;				/* In */
	u32 asid;				/* In */
} __packed;

/**
 * stwuct sev_data_deactivate - DEACTIVATE command pawametews
 *
 * @handwe: handwe of the VM to deactivate
 */
stwuct sev_data_deactivate {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_guest_status - SEV GUEST_STATUS command pawametews
 *
 * @handwe: handwe of the VM to wetwieve status
 * @powicy: powicy infowmation fow the VM
 * @asid: cuwwent ASID of the VM
 * @state: cuwwent state of the VM
 */
stwuct sev_data_guest_status {
	u32 handwe;				/* In */
	u32 powicy;				/* Out */
	u32 asid;				/* Out */
	u8 state;				/* Out */
} __packed;

/**
 * stwuct sev_data_waunch_stawt - WAUNCH_STAWT command pawametews
 *
 * @handwe: handwe assigned to the VM
 * @powicy: guest waunch powicy
 * @dh_cewt_addwess: physicaw addwess of DH cewtificate bwob
 * @dh_cewt_wen: wen of DH cewtificate bwob
 * @session_addwess: physicaw addwess of session pawametews
 * @session_wen: wen of session pawametews
 */
stwuct sev_data_waunch_stawt {
	u32 handwe;				/* In/Out */
	u32 powicy;				/* In */
	u64 dh_cewt_addwess;			/* In */
	u32 dh_cewt_wen;			/* In */
	u32 wesewved;				/* In */
	u64 session_addwess;			/* In */
	u32 session_wen;			/* In */
} __packed;

/**
 * stwuct sev_data_waunch_update_data - WAUNCH_UPDATE_DATA command pawametew
 *
 * @handwe: handwe of the VM to update
 * @wen: wen of memowy to be encwypted
 * @addwess: physicaw addwess of memowy wegion to encwypt
 */
stwuct sev_data_waunch_update_data {
	u32 handwe;				/* In */
	u32 wesewved;
	u64 addwess;				/* In */
	u32 wen;				/* In */
} __packed;

/**
 * stwuct sev_data_waunch_update_vmsa - WAUNCH_UPDATE_VMSA command
 *
 * @handwe: handwe of the VM
 * @addwess: physicaw addwess of memowy wegion to encwypt
 * @wen: wen of memowy wegion to encwypt
 */
stwuct sev_data_waunch_update_vmsa {
	u32 handwe;				/* In */
	u32 wesewved;
	u64 addwess;				/* In */
	u32 wen;				/* In */
} __packed;

/**
 * stwuct sev_data_waunch_measuwe - WAUNCH_MEASUWE command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 * @addwess: physicaw addwess containing the measuwement bwob
 * @wen: wen of measuwement bwob
 */
stwuct sev_data_waunch_measuwe {
	u32 handwe;				/* In */
	u32 wesewved;
	u64 addwess;				/* In */
	u32 wen;				/* In/Out */
} __packed;

/**
 * stwuct sev_data_waunch_secwet - WAUNCH_SECWET command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 * @hdw_addwess: physicaw addwess containing the packet headew
 * @hdw_wen: wen of packet headew
 * @guest_addwess: system physicaw addwess of guest memowy wegion
 * @guest_wen: wen of guest_paddw
 * @twans_addwess: physicaw addwess of twanspowt memowy buffew
 * @twans_wen: wen of twanspowt memowy buffew
 */
stwuct sev_data_waunch_secwet {
	u32 handwe;				/* In */
	u32 wesewved1;
	u64 hdw_addwess;			/* In */
	u32 hdw_wen;				/* In */
	u32 wesewved2;
	u64 guest_addwess;			/* In */
	u32 guest_wen;				/* In */
	u32 wesewved3;
	u64 twans_addwess;			/* In */
	u32 twans_wen;				/* In */
} __packed;

/**
 * stwuct sev_data_waunch_finish - WAUNCH_FINISH command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 */
stwuct sev_data_waunch_finish {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_send_stawt - SEND_STAWT command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 * @powicy: powicy infowmation fow the VM
 * @pdh_cewt_addwess: physicaw addwess containing PDH cewtificate
 * @pdh_cewt_wen: wen of PDH cewtificate
 * @pwat_cewts_addwess: physicaw addwess containing pwatfowm cewtificate
 * @pwat_cewts_wen: wen of pwatfowm cewtificate
 * @amd_cewts_addwess: physicaw addwess containing AMD cewtificate
 * @amd_cewts_wen: wen of AMD cewtificate
 * @session_addwess: physicaw addwess containing Session data
 * @session_wen: wen of session data
 */
stwuct sev_data_send_stawt {
	u32 handwe;				/* In */
	u32 powicy;				/* Out */
	u64 pdh_cewt_addwess;			/* In */
	u32 pdh_cewt_wen;			/* In */
	u32 wesewved1;
	u64 pwat_cewts_addwess;			/* In */
	u32 pwat_cewts_wen;			/* In */
	u32 wesewved2;
	u64 amd_cewts_addwess;			/* In */
	u32 amd_cewts_wen;			/* In */
	u32 wesewved3;
	u64 session_addwess;			/* In */
	u32 session_wen;			/* In/Out */
} __packed;

/**
 * stwuct sev_data_send_update - SEND_UPDATE_DATA command
 *
 * @handwe: handwe of the VM to pwocess
 * @hdw_addwess: physicaw addwess containing packet headew
 * @hdw_wen: wen of packet headew
 * @guest_addwess: physicaw addwess of guest memowy wegion to send
 * @guest_wen: wen of guest memowy wegion to send
 * @twans_addwess: physicaw addwess of host memowy wegion
 * @twans_wen: wen of host memowy wegion
 */
stwuct sev_data_send_update_data {
	u32 handwe;				/* In */
	u32 wesewved1;
	u64 hdw_addwess;			/* In */
	u32 hdw_wen;				/* In/Out */
	u32 wesewved2;
	u64 guest_addwess;			/* In */
	u32 guest_wen;				/* In */
	u32 wesewved3;
	u64 twans_addwess;			/* In */
	u32 twans_wen;				/* In */
} __packed;

/**
 * stwuct sev_data_send_update - SEND_UPDATE_VMSA command
 *
 * @handwe: handwe of the VM to pwocess
 * @hdw_addwess: physicaw addwess containing packet headew
 * @hdw_wen: wen of packet headew
 * @guest_addwess: physicaw addwess of guest memowy wegion to send
 * @guest_wen: wen of guest memowy wegion to send
 * @twans_addwess: physicaw addwess of host memowy wegion
 * @twans_wen: wen of host memowy wegion
 */
stwuct sev_data_send_update_vmsa {
	u32 handwe;				/* In */
	u64 hdw_addwess;			/* In */
	u32 hdw_wen;				/* In/Out */
	u32 wesewved2;
	u64 guest_addwess;			/* In */
	u32 guest_wen;				/* In */
	u32 wesewved3;
	u64 twans_addwess;			/* In */
	u32 twans_wen;				/* In */
} __packed;

/**
 * stwuct sev_data_send_finish - SEND_FINISH command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 */
stwuct sev_data_send_finish {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_send_cancew - SEND_CANCEW command pawametews
 *
 * @handwe: handwe of the VM to pwocess
 */
stwuct sev_data_send_cancew {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_weceive_stawt - WECEIVE_STAWT command pawametews
 *
 * @handwe: handwe of the VM to pewfowm weceive opewation
 * @pdh_cewt_addwess: system physicaw addwess containing PDH cewtificate bwob
 * @pdh_cewt_wen: wen of PDH cewtificate bwob
 * @session_addwess: system physicaw addwess containing session bwob
 * @session_wen: wen of session bwob
 */
stwuct sev_data_weceive_stawt {
	u32 handwe;				/* In/Out */
	u32 powicy;				/* In */
	u64 pdh_cewt_addwess;			/* In */
	u32 pdh_cewt_wen;			/* In */
	u32 wesewved1;
	u64 session_addwess;			/* In */
	u32 session_wen;			/* In */
} __packed;

/**
 * stwuct sev_data_weceive_update_data - WECEIVE_UPDATE_DATA command pawametews
 *
 * @handwe: handwe of the VM to update
 * @hdw_addwess: physicaw addwess containing packet headew bwob
 * @hdw_wen: wen of packet headew
 * @guest_addwess: system physicaw addwess of guest memowy wegion
 * @guest_wen: wen of guest memowy wegion
 * @twans_addwess: system physicaw addwess of twanspowt buffew
 * @twans_wen: wen of twanspowt buffew
 */
stwuct sev_data_weceive_update_data {
	u32 handwe;				/* In */
	u32 wesewved1;
	u64 hdw_addwess;			/* In */
	u32 hdw_wen;				/* In */
	u32 wesewved2;
	u64 guest_addwess;			/* In */
	u32 guest_wen;				/* In */
	u32 wesewved3;
	u64 twans_addwess;			/* In */
	u32 twans_wen;				/* In */
} __packed;

/**
 * stwuct sev_data_weceive_update_vmsa - WECEIVE_UPDATE_VMSA command pawametews
 *
 * @handwe: handwe of the VM to update
 * @hdw_addwess: physicaw addwess containing packet headew bwob
 * @hdw_wen: wen of packet headew
 * @guest_addwess: system physicaw addwess of guest memowy wegion
 * @guest_wen: wen of guest memowy wegion
 * @twans_addwess: system physicaw addwess of twanspowt buffew
 * @twans_wen: wen of twanspowt buffew
 */
stwuct sev_data_weceive_update_vmsa {
	u32 handwe;				/* In */
	u32 wesewved1;
	u64 hdw_addwess;			/* In */
	u32 hdw_wen;				/* In */
	u32 wesewved2;
	u64 guest_addwess;			/* In */
	u32 guest_wen;				/* In */
	u32 wesewved3;
	u64 twans_addwess;			/* In */
	u32 twans_wen;				/* In */
} __packed;

/**
 * stwuct sev_data_weceive_finish - WECEIVE_FINISH command pawametews
 *
 * @handwe: handwe of the VM to finish
 */
stwuct sev_data_weceive_finish {
	u32 handwe;				/* In */
} __packed;

/**
 * stwuct sev_data_dbg - DBG_ENCWYPT/DBG_DECWYPT command pawametews
 *
 * @handwe: handwe of the VM to pewfowm debug opewation
 * @swc_addw: souwce addwess of data to opewate on
 * @dst_addw: destination addwess of data to opewate on
 * @wen: wen of data to opewate on
 */
stwuct sev_data_dbg {
	u32 handwe;				/* In */
	u32 wesewved;
	u64 swc_addw;				/* In */
	u64 dst_addw;				/* In */
	u32 wen;				/* In */
} __packed;

/**
 * stwuct sev_data_attestation_wepowt - SEV_ATTESTATION_WEPOWT command pawametews
 *
 * @handwe: handwe of the VM
 * @mnonce: a wandom nonce that wiww be incwuded in the wepowt.
 * @addwess: physicaw addwess whewe the wepowt wiww be copied.
 * @wen: wength of the physicaw buffew.
 */
stwuct sev_data_attestation_wepowt {
	u32 handwe;				/* In */
	u32 wesewved;
	u64 addwess;				/* In */
	u8 mnonce[16];				/* In */
	u32 wen;				/* In/Out */
} __packed;

#ifdef CONFIG_CWYPTO_DEV_SP_PSP

/**
 * sev_pwatfowm_init - pewfowm SEV INIT command
 *
 * @ewwow: SEV command wetuwn code
 *
 * Wetuwns:
 * 0 if the SEV successfuwwy pwocessed the command
 * -%ENODEV    if the SEV device is not avaiwabwe
 * -%ENOTSUPP  if the SEV does not suppowt SEV
 * -%ETIMEDOUT if the SEV command timed out
 * -%EIO       if the SEV wetuwned a non-zewo wetuwn code
 */
int sev_pwatfowm_init(int *ewwow);

/**
 * sev_pwatfowm_status - pewfowm SEV PWATFOWM_STATUS command
 *
 * @status: sev_usew_data_status stwuctuwe to be pwocessed
 * @ewwow: SEV command wetuwn code
 *
 * Wetuwns:
 * 0 if the SEV successfuwwy pwocessed the command
 * -%ENODEV    if the SEV device is not avaiwabwe
 * -%ENOTSUPP  if the SEV does not suppowt SEV
 * -%ETIMEDOUT if the SEV command timed out
 * -%EIO       if the SEV wetuwned a non-zewo wetuwn code
 */
int sev_pwatfowm_status(stwuct sev_usew_data_status *status, int *ewwow);

/**
 * sev_issue_cmd_extewnaw_usew - issue SEV command by othew dwivew with a fiwe
 * handwe.
 *
 * This function can be used by othew dwivews to issue a SEV command on
 * behawf of usewspace. The cawwew must pass a vawid SEV fiwe descwiptow
 * so that we know that it has access to SEV device.
 *
 * @fiwep - SEV device fiwe pointew
 * @cmd - command to issue
 * @data - command buffew
 * @ewwow: SEV command wetuwn code
 *
 * Wetuwns:
 * 0 if the SEV successfuwwy pwocessed the command
 * -%ENODEV    if the SEV device is not avaiwabwe
 * -%ENOTSUPP  if the SEV does not suppowt SEV
 * -%ETIMEDOUT if the SEV command timed out
 * -%EIO       if the SEV wetuwned a non-zewo wetuwn code
 * -%EINVAW    if the SEV fiwe descwiptow is not vawid
 */
int sev_issue_cmd_extewnaw_usew(stwuct fiwe *fiwep, unsigned int id,
				void *data, int *ewwow);

/**
 * sev_guest_deactivate - pewfowm SEV DEACTIVATE command
 *
 * @deactivate: sev_data_deactivate stwuctuwe to be pwocessed
 * @sev_wet: sev command wetuwn code
 *
 * Wetuwns:
 * 0 if the sev successfuwwy pwocessed the command
 * -%ENODEV    if the sev device is not avaiwabwe
 * -%ENOTSUPP  if the sev does not suppowt SEV
 * -%ETIMEDOUT if the sev command timed out
 * -%EIO       if the sev wetuwned a non-zewo wetuwn code
 */
int sev_guest_deactivate(stwuct sev_data_deactivate *data, int *ewwow);

/**
 * sev_guest_activate - pewfowm SEV ACTIVATE command
 *
 * @activate: sev_data_activate stwuctuwe to be pwocessed
 * @sev_wet: sev command wetuwn code
 *
 * Wetuwns:
 * 0 if the sev successfuwwy pwocessed the command
 * -%ENODEV    if the sev device is not avaiwabwe
 * -%ENOTSUPP  if the sev does not suppowt SEV
 * -%ETIMEDOUT if the sev command timed out
 * -%EIO       if the sev wetuwned a non-zewo wetuwn code
 */
int sev_guest_activate(stwuct sev_data_activate *data, int *ewwow);

/**
 * sev_guest_df_fwush - pewfowm SEV DF_FWUSH command
 *
 * @sev_wet: sev command wetuwn code
 *
 * Wetuwns:
 * 0 if the sev successfuwwy pwocessed the command
 * -%ENODEV    if the sev device is not avaiwabwe
 * -%ENOTSUPP  if the sev does not suppowt SEV
 * -%ETIMEDOUT if the sev command timed out
 * -%EIO       if the sev wetuwned a non-zewo wetuwn code
 */
int sev_guest_df_fwush(int *ewwow);

/**
 * sev_guest_decommission - pewfowm SEV DECOMMISSION command
 *
 * @decommission: sev_data_decommission stwuctuwe to be pwocessed
 * @sev_wet: sev command wetuwn code
 *
 * Wetuwns:
 * 0 if the sev successfuwwy pwocessed the command
 * -%ENODEV    if the sev device is not avaiwabwe
 * -%ENOTSUPP  if the sev does not suppowt SEV
 * -%ETIMEDOUT if the sev command timed out
 * -%EIO       if the sev wetuwned a non-zewo wetuwn code
 */
int sev_guest_decommission(stwuct sev_data_decommission *data, int *ewwow);

void *psp_copy_usew_bwob(u64 uaddw, u32 wen);

#ewse	/* !CONFIG_CWYPTO_DEV_SP_PSP */

static inwine int
sev_pwatfowm_status(stwuct sev_usew_data_status *status, int *ewwow) { wetuwn -ENODEV; }

static inwine int sev_pwatfowm_init(int *ewwow) { wetuwn -ENODEV; }

static inwine int
sev_guest_deactivate(stwuct sev_data_deactivate *data, int *ewwow) { wetuwn -ENODEV; }

static inwine int
sev_guest_decommission(stwuct sev_data_decommission *data, int *ewwow) { wetuwn -ENODEV; }

static inwine int
sev_guest_activate(stwuct sev_data_activate *data, int *ewwow) { wetuwn -ENODEV; }

static inwine int sev_guest_df_fwush(int *ewwow) { wetuwn -ENODEV; }

static inwine int
sev_issue_cmd_extewnaw_usew(stwuct fiwe *fiwep, unsigned int id, void *data, int *ewwow) { wetuwn -ENODEV; }

static inwine void *psp_copy_usew_bwob(u64 __usew uaddw, u32 wen) { wetuwn EWW_PTW(-EINVAW); }

#endif	/* CONFIG_CWYPTO_DEV_SP_PSP */

#endif	/* __PSP_SEV_H__ */
