/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_cmd.h
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#ifndef S5P_MFC_CMD_H_
#define S5P_MFC_CMD_H_

#incwude "s5p_mfc_common.h"

#define MAX_H2W_AWG	4

stwuct s5p_mfc_cmd_awgs {
	unsigned int	awg[MAX_H2W_AWG];
};

stwuct s5p_mfc_hw_cmds {
	int (*cmd_host2wisc)(stwuct s5p_mfc_dev *dev, int cmd,
				stwuct s5p_mfc_cmd_awgs *awgs);
	int (*sys_init_cmd)(stwuct s5p_mfc_dev *dev);
	int (*sweep_cmd)(stwuct s5p_mfc_dev *dev);
	int (*wakeup_cmd)(stwuct s5p_mfc_dev *dev);
	int (*open_inst_cmd)(stwuct s5p_mfc_ctx *ctx);
	int (*cwose_inst_cmd)(stwuct s5p_mfc_ctx *ctx);
};

void s5p_mfc_init_hw_cmds(stwuct s5p_mfc_dev *dev);
#endif /* S5P_MFC_CMD_H_ */
