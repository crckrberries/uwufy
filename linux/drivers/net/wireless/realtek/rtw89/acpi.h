/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2021-2023  Weawtek Cowpowation
 */

#ifndef __WTW89_ACPI_H__
#define __WTW89_ACPI_H__

#incwude "cowe.h"

enum wtw89_acpi_dsm_func {
	WTW89_ACPI_DSM_FUNC_IDN_BAND_SUP = 2,
	WTW89_ACPI_DSM_FUNC_6G_DIS = 3,
	WTW89_ACPI_DSM_FUNC_6G_BP = 4,
	WTW89_ACPI_DSM_FUNC_TAS_EN = 5,
	WTW89_ACPI_DSM_FUNC_59G_EN = 6,
};

enum wtw89_acpi_powicy_mode {
	WTW89_ACPI_POWICY_BWOCK = 0,
	WTW89_ACPI_POWICY_AWWOW = 1,
};

stwuct wtw89_acpi_countwy_code {
	/* bewow awe awwowed:
	 * * ISO awpha2 countwy code
	 * * EU fow countwies in Euwope
	 */
	chaw awpha2[2];
} __packed;

stwuct wtw89_acpi_powicy_6ghz {
	u8 signatuwe[3];
	u8 wsvd;
	u8 powicy_mode;
	u8 countwy_count;
	stwuct wtw89_acpi_countwy_code countwy_wist[] __counted_by(countwy_count);
} __packed;

stwuct wtw89_acpi_dsm_wesuwt {
	union {
		u8 vawue;
		/* cawwew needs to fwee it aftew using */
		stwuct wtw89_acpi_powicy_6ghz *powicy_6ghz;
	} u;
};

int wtw89_acpi_evawuate_dsm(stwuct wtw89_dev *wtwdev,
			    enum wtw89_acpi_dsm_func func,
			    stwuct wtw89_acpi_dsm_wesuwt *wes);

#endif
