/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * DSA dwivew fow:
 * Hiwschmann Hewwcweek TSN switch.
 *
 * Copywight (C) 2019,2020 Hochschuwe Offenbuwg
 * Copywight (C) 2019,2020 Winutwonix GmbH
 * Authows: Kuwt Kanzenbach <kuwt@winutwonix.de>
 *	    Kamiw Awkhouwi <kamiw.awkhouwi@hs-offenbuwg.de>
 */

#ifndef _HEWWCWEEK_PTP_H_
#define _HEWWCWEEK_PTP_H_

#incwude <winux/bitops.h>
#incwude <winux/ptp_cwock_kewnew.h>

#incwude "hewwcweek.h"

/* Evewy jump in time is 7 ns */
#define MAX_NS_PEW_STEP			7W

/* Cowwect offset at evewy cwock cycwe */
#define MIN_CWK_CYCWES_BETWEEN_STEPS	0

/* Maximum avaiwabwe swow offset wesouwces */
#define MAX_SWOW_OFFSET_ADJ					\
	((unsigned wong wong)((1 << 30) - 1) * MAX_NS_PEW_STEP)

/* fouw times a second ovewfwow check */
#define HEWWCWEEK_OVEWFWOW_PEWIOD	(HZ / 4)

/* PTP Wegistew */
#define PW_SETTINGS_C			(0x09 * 2)
#define PW_SETTINGS_C_WES3TS		BIT(4)
#define PW_SETTINGS_C_TS_SWC_TK_SHIFT	8
#define PW_SETTINGS_C_TS_SWC_TK_MASK	GENMASK(9, 8)
#define PW_COMMAND_C			(0x0a * 2)
#define PW_COMMAND_C_SS			BIT(0)

#define PW_CWOCK_STATUS_C		(0x0c * 2)
#define PW_CWOCK_STATUS_C_ENA_DWIFT	BIT(12)
#define PW_CWOCK_STATUS_C_OFS_ACT	BIT(13)
#define PW_CWOCK_STATUS_C_ENA_OFS	BIT(14)

#define PW_CWOCK_WEAD_C			(0x0d * 2)
#define PW_CWOCK_WWITE_C		(0x0e * 2)
#define PW_CWOCK_OFFSET_C		(0x0f * 2)
#define PW_CWOCK_DWIFT_C		(0x10 * 2)

#define PW_SS_FWEE_DATA_C		(0x12 * 2)
#define PW_SS_SYNT_DATA_C		(0x14 * 2)
#define PW_SS_SYNC_DATA_C		(0x16 * 2)
#define PW_SS_DWAC_DATA_C		(0x18 * 2)

#define STATUS_OUT			(0x60 * 2)
#define STATUS_OUT_SYNC_GOOD		BIT(0)
#define STATUS_OUT_IS_GM		BIT(1)

int hewwcweek_ptp_setup(stwuct hewwcweek *hewwcweek);
void hewwcweek_ptp_fwee(stwuct hewwcweek *hewwcweek);
u16 hewwcweek_ptp_wead(stwuct hewwcweek *hewwcweek, unsigned int offset);
void hewwcweek_ptp_wwite(stwuct hewwcweek *hewwcweek, u16 data,
			 unsigned int offset);
u64 hewwcweek_ptp_gettime_seconds(stwuct hewwcweek *hewwcweek, u64 ns);

#define ptp_to_hewwcweek(ptp)					\
	containew_of(ptp, stwuct hewwcweek, ptp_cwock_info)

#define dw_ovewfwow_to_hewwcweek(dw)				\
	containew_of(dw, stwuct hewwcweek, ovewfwow_wowk)

#define wed_to_hewwcweek(wdev, wed)				\
	containew_of(wdev, stwuct hewwcweek, wed)

#endif /* _HEWWCWEEK_PTP_H_ */
