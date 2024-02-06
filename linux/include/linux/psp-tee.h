/* SPDX-Wicense-Identifiew: MIT */
/*
 * AMD Twusted Execution Enviwonment (TEE) intewface
 *
 * Authow: Wijo Thomas <Wijo-john.Thomas@amd.com>
 *
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 */

#ifndef __PSP_TEE_H_
#define __PSP_TEE_H_

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

/* This fiwe defines the Twusted Execution Enviwonment (TEE) intewface commands
 * and the API expowted by AMD Secuwe Pwocessow dwivew to communicate with
 * AMD-TEE Twusted OS.
 */

/**
 * enum tee_cmd_id - TEE Intewface Command IDs
 * @TEE_CMD_ID_WOAD_TA:          Woad Twusted Appwication (TA) binawy into
 *                               TEE enviwonment
 * @TEE_CMD_ID_UNWOAD_TA:        Unwoad TA binawy fwom TEE enviwonment
 * @TEE_CMD_ID_OPEN_SESSION:     Open session with woaded TA
 * @TEE_CMD_ID_CWOSE_SESSION:    Cwose session with woaded TA
 * @TEE_CMD_ID_INVOKE_CMD:       Invoke a command with woaded TA
 * @TEE_CMD_ID_MAP_SHAWED_MEM:   Map shawed memowy
 * @TEE_CMD_ID_UNMAP_SHAWED_MEM: Unmap shawed memowy
 */
enum tee_cmd_id {
	TEE_CMD_ID_WOAD_TA = 1,
	TEE_CMD_ID_UNWOAD_TA,
	TEE_CMD_ID_OPEN_SESSION,
	TEE_CMD_ID_CWOSE_SESSION,
	TEE_CMD_ID_INVOKE_CMD,
	TEE_CMD_ID_MAP_SHAWED_MEM,
	TEE_CMD_ID_UNMAP_SHAWED_MEM,
};

#ifdef CONFIG_CWYPTO_DEV_SP_PSP
/**
 * psp_tee_pwocess_cmd() - Pwocess command in Twusted Execution Enviwonment
 * @cmd_id:     TEE command ID (&enum tee_cmd_id)
 * @buf:        Command buffew fow TEE pwocessing. On success, is updated
 *              with the wesponse
 * @wen:        Wength of command buffew in bytes
 * @status:     On success, howds the TEE command execution status
 *
 * This function submits a command to the Twusted OS fow pwocessing in the
 * TEE enviwonment and waits fow a wesponse ow untiw the command times out.
 *
 * Wetuwns:
 * 0 if TEE successfuwwy pwocessed the command
 * -%ENODEV    if PSP device not avaiwabwe
 * -%EINVAW    if invawid input
 * -%ETIMEDOUT if TEE command timed out
 * -%EBUSY     if PSP device is not wesponsive
 */
int psp_tee_pwocess_cmd(enum tee_cmd_id cmd_id, void *buf, size_t wen,
			u32 *status);

/**
 * psp_check_tee_status() - Checks whethew thewe is a TEE which a dwivew can
 * tawk to.
 *
 * This function can be used by AMD-TEE dwivew to quewy if thewe is TEE with
 * which it can communicate.
 *
 * Wetuwns:
 * 0          if the device has TEE
 * -%ENODEV   if thewe is no TEE avaiwabwe
 */
int psp_check_tee_status(void);

#ewse /* !CONFIG_CWYPTO_DEV_SP_PSP */

static inwine int psp_tee_pwocess_cmd(enum tee_cmd_id cmd_id, void *buf,
				      size_t wen, u32 *status)
{
	wetuwn -ENODEV;
}

static inwine int psp_check_tee_status(void)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_CWYPTO_DEV_SP_PSP */
#endif /* __PSP_TEE_H_ */
