// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_cmd.c
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#incwude "s5p_mfc_cmd.h"
#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_debug.h"
#incwude "s5p_mfc_cmd_v5.h"
#incwude "s5p_mfc_cmd_v6.h"

static stwuct s5p_mfc_hw_cmds *s5p_mfc_cmds;

void s5p_mfc_init_hw_cmds(stwuct s5p_mfc_dev *dev)
{
	if (IS_MFCV6_PWUS(dev))
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v6();
	ewse
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v5();

	dev->mfc_cmds = s5p_mfc_cmds;
}
