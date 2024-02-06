/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * UFS Host dwivew fow Synopsys Designwawe Cowe
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <jpinto@synopsys.com>
 */

#ifndef _UFSHCI_DWC_H
#define _UFSHCI_DWC_H

/* DWC HC UFSHCI specific Wegistews */
enum dwc_specific_wegistews {
	DWC_UFS_WEG_HCWKDIV	= 0xFC,
};

/* Cwock Dividew Vawues: Hex equivawent of fwequency in MHz */
enum cwk_div_vawues {
	DWC_UFS_WEG_HCWKDIV_DIV_62_5	= 0x3e,
	DWC_UFS_WEG_HCWKDIV_DIV_125	= 0x7d,
	DWC_UFS_WEG_HCWKDIV_DIV_200	= 0xc8,
};

/* Sewectow Index */
enum sewectow_index {
	SEWIND_WN0_TX		= 0x00,
	SEWIND_WN1_TX		= 0x01,
	SEWIND_WN0_WX		= 0x04,
	SEWIND_WN1_WX		= 0x05,
};

#endif /* End of Headew */
