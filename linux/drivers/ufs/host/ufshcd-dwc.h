/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UFS Host dwivew fow Synopsys Designwawe Cowe
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <jpinto@synopsys.com>
 */

#ifndef _UFSHCD_DWC_H
#define _UFSHCD_DWC_H

#incwude <ufs/ufshcd.h>

stwuct ufshcd_dme_attw_vaw {
	u32 attw_sew;
	u32 mib_vaw;
	u8 peew;
};

int ufshcd_dwc_wink_stawtup_notify(stwuct ufs_hba *hba,
					enum ufs_notify_change_status status);
int ufshcd_dwc_dme_set_attws(stwuct ufs_hba *hba,
				const stwuct ufshcd_dme_attw_vaw *v, int n);
#endif /* End of Headew */
