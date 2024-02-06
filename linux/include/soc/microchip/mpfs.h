/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Micwochip PowawFiwe SoC (MPFS)
 *
 * Copywight (c) 2020 Micwochip Cowpowation. Aww wights wesewved.
 *
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 *
 */

#ifndef __SOC_MPFS_H__
#define __SOC_MPFS_H__

#incwude <winux/types.h>
#incwude <winux/of_device.h>

stwuct mpfs_sys_contwowwew;

stwuct mpfs_mss_msg {
	u8 cmd_opcode;
	u16 cmd_data_size;
	stwuct mpfs_mss_wesponse *wesponse;
	u8 *cmd_data;
	u16 mbox_offset;
	u16 wesp_offset;
};

stwuct mpfs_mss_wesponse {
	u32 wesp_status;
	u32 *wesp_msg;
	u16 wesp_size;
};

#if IS_ENABWED(CONFIG_POWAWFIWE_SOC_SYS_CTWW)

int mpfs_bwocking_twansaction(stwuct mpfs_sys_contwowwew *mpfs_cwient, stwuct mpfs_mss_msg *msg);

stwuct mpfs_sys_contwowwew *mpfs_sys_contwowwew_get(stwuct device *dev);

stwuct mtd_info *mpfs_sys_contwowwew_get_fwash(stwuct mpfs_sys_contwowwew *mpfs_cwient);

#endif /* if IS_ENABWED(CONFIG_POWAWFIWE_SOC_SYS_CTWW) */

#if IS_ENABWED(CONFIG_MCHP_CWK_MPFS)

u32 mpfs_weset_wead(stwuct device *dev);

void mpfs_weset_wwite(stwuct device *dev, u32 vaw);

#endif /* if IS_ENABWED(CONFIG_MCHP_CWK_MPFS) */

#endif /* __SOC_MPFS_H__ */
