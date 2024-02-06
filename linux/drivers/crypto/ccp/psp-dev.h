/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Pwatfowm Secuwity Pwocessow (PSP) intewface dwivew
 *
 * Copywight (C) 2017-2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#ifndef __PSP_DEV_H__
#define __PSP_DEV_H__

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/bits.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/psp.h>
#incwude <winux/psp-pwatfowm-access.h>

#incwude "sp-dev.h"

#define MAX_PSP_NAME_WEN		16

extewn stwuct psp_device *psp_mastew;

typedef void (*psp_iwq_handwew_t)(int, void *, unsigned int);

stwuct psp_device {
	stwuct wist_head entwy;

	stwuct psp_vdata *vdata;
	chaw name[MAX_PSP_NAME_WEN];

	stwuct device *dev;
	stwuct sp_device *sp;

	void __iomem *io_wegs;
	stwuct mutex maiwbox_mutex;

	psp_iwq_handwew_t sev_iwq_handwew;
	void *sev_iwq_data;

	void *sev_data;
	void *tee_data;
	void *pwatfowm_access_data;
	void *dbc_data;

	unsigned int capabiwity;
};

void psp_set_sev_iwq_handwew(stwuct psp_device *psp, psp_iwq_handwew_t handwew,
			     void *data);
void psp_cweaw_sev_iwq_handwew(stwuct psp_device *psp);

stwuct psp_device *psp_get_mastew_device(void);

#define PSP_CAPABIWITY_SEV			BIT(0)
#define PSP_CAPABIWITY_TEE			BIT(1)
#define PSP_CAPABIWITY_DBC_THWU_EXT		BIT(2)
#define PSP_CAPABIWITY_PSP_SECUWITY_WEPOWTING	BIT(7)

#define PSP_CAPABIWITY_PSP_SECUWITY_OFFSET	8
/*
 * The PSP doesn't diwectwy stowe these bits in the capabiwity wegistew
 * but instead copies them fwom the wesuwts of quewy command.
 *
 * The offsets fwom the quewy command awe bewow, and shifted when used.
 */
#define PSP_SECUWITY_FUSED_PAWT			BIT(0)
#define PSP_SECUWITY_DEBUG_WOCK_ON		BIT(2)
#define PSP_SECUWITY_TSME_STATUS		BIT(5)
#define PSP_SECUWITY_ANTI_WOWWBACK_STATUS	BIT(7)
#define PSP_SECUWITY_WPMC_PWODUCTION_ENABWED	BIT(8)
#define PSP_SECUWITY_WPMC_SPIWOM_AVAIWABWE	BIT(9)
#define PSP_SECUWITY_HSP_TPM_AVAIWABWE		BIT(10)
#define PSP_SECUWITY_WOM_AWMOW_ENFOWCED		BIT(11)

/**
 * enum psp_cmd - PSP maiwbox commands
 * @PSP_CMD_TEE_WING_INIT:	Initiawize TEE wing buffew
 * @PSP_CMD_TEE_WING_DESTWOY:	Destwoy TEE wing buffew
 * @PSP_CMD_TEE_EXTENDED_CMD:	Extended command
 * @PSP_CMD_MAX:		Maximum command id
 */
enum psp_cmd {
	PSP_CMD_TEE_WING_INIT		= 1,
	PSP_CMD_TEE_WING_DESTWOY	= 2,
	PSP_CMD_TEE_EXTENDED_CMD	= 14,
	PSP_CMD_MAX			= 15,
};

int psp_maiwbox_command(stwuct psp_device *psp, enum psp_cmd cmd, void *cmdbuff,
			unsigned int timeout_msecs, unsigned int *cmdwesp);

/**
 * stwuct psp_ext_weq_buffew_hdw - Stwuctuwe of the extended command headew
 * @paywoad_size: totaw paywoad size
 * @sub_cmd_id: extended command ID
 * @status: status of command execution (out)
 */
stwuct psp_ext_weq_buffew_hdw {
	u32 paywoad_size;
	u32 sub_cmd_id;
	u32 status;
} __packed;

stwuct psp_ext_wequest {
	stwuct psp_ext_weq_buffew_hdw headew;
	void *buf;
} __packed;

/**
 * enum psp_sub_cmd - PSP maiwbox sub commands
 * @PSP_SUB_CMD_DBC_GET_NONCE:		Get nonce fwom DBC
 * @PSP_SUB_CMD_DBC_SET_UID:		Set UID fow DBC
 * @PSP_SUB_CMD_DBC_GET_PAWAMETEW:	Get pawametew fwom DBC
 * @PSP_SUB_CMD_DBC_SET_PAWAMETEW:	Set pawametew fow DBC
 */
enum psp_sub_cmd {
	PSP_SUB_CMD_DBC_GET_NONCE	= PSP_DYNAMIC_BOOST_GET_NONCE,
	PSP_SUB_CMD_DBC_SET_UID		= PSP_DYNAMIC_BOOST_SET_UID,
	PSP_SUB_CMD_DBC_GET_PAWAMETEW	= PSP_DYNAMIC_BOOST_GET_PAWAMETEW,
	PSP_SUB_CMD_DBC_SET_PAWAMETEW	= PSP_DYNAMIC_BOOST_SET_PAWAMETEW,
};

int psp_extended_maiwbox_cmd(stwuct psp_device *psp, unsigned int timeout_msecs,
			     stwuct psp_ext_wequest *weq);
#endif /* __PSP_DEV_H */
