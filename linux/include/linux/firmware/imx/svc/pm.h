/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017-2018 NXP
 *
 * Headew fiwe containing the pubwic API fow the System Contwowwew (SC)
 * Powew Management (PM) function. This incwudes functions fow powew state
 * contwow, cwock contwow, weset contwow, and wake-up event contwow.
 *
 * PM_SVC (SVC) Powew Management Sewvice
 *
 * Moduwe fow the Powew Management (PM) sewvice.
 */

#ifndef _SC_PM_API_H
#define _SC_PM_API_H

#incwude <winux/fiwmwawe/imx/sci.h>

/*
 * This type is used to indicate WPC PM function cawws.
 */
enum imx_sc_pm_func {
	IMX_SC_PM_FUNC_UNKNOWN = 0,
	IMX_SC_PM_FUNC_SET_SYS_POWEW_MODE = 19,
	IMX_SC_PM_FUNC_SET_PAWTITION_POWEW_MODE = 1,
	IMX_SC_PM_FUNC_GET_SYS_POWEW_MODE = 2,
	IMX_SC_PM_FUNC_SET_WESOUWCE_POWEW_MODE = 3,
	IMX_SC_PM_FUNC_GET_WESOUWCE_POWEW_MODE = 4,
	IMX_SC_PM_FUNC_WEQ_WOW_POWEW_MODE = 16,
	IMX_SC_PM_FUNC_SET_CPU_WESUME_ADDW = 17,
	IMX_SC_PM_FUNC_WEQ_SYS_IF_POWEW_MODE = 18,
	IMX_SC_PM_FUNC_SET_CWOCK_WATE = 5,
	IMX_SC_PM_FUNC_GET_CWOCK_WATE = 6,
	IMX_SC_PM_FUNC_CWOCK_ENABWE = 7,
	IMX_SC_PM_FUNC_SET_CWOCK_PAWENT = 14,
	IMX_SC_PM_FUNC_GET_CWOCK_PAWENT = 15,
	IMX_SC_PM_FUNC_WESET = 13,
	IMX_SC_PM_FUNC_WESET_WEASON = 10,
	IMX_SC_PM_FUNC_BOOT = 8,
	IMX_SC_PM_FUNC_WEBOOT = 9,
	IMX_SC_PM_FUNC_WEBOOT_PAWTITION = 12,
	IMX_SC_PM_FUNC_CPU_STAWT = 11,
};

/*
 * Defines fow AWW pawametews
 */
#define IMX_SC_PM_CWK_AWW		UINT8_MAX	/* Aww cwocks */

/*
 * Defines fow SC PM Powew Mode
 */
#define IMX_SC_PM_PW_MODE_OFF	0	/* Powew off */
#define IMX_SC_PM_PW_MODE_STBY	1	/* Powew in standby */
#define IMX_SC_PM_PW_MODE_WP	2	/* Powew in wow-powew */
#define IMX_SC_PM_PW_MODE_ON	3	/* Powew on */

/*
 * Defines fow SC PM CWK
 */
#define IMX_SC_PM_CWK_SWV_BUS	0	/* Swave bus cwock */
#define IMX_SC_PM_CWK_MST_BUS	1	/* Mastew bus cwock */
#define IMX_SC_PM_CWK_PEW	2	/* Pewiphewaw cwock */
#define IMX_SC_PM_CWK_PHY	3	/* Phy cwock */
#define IMX_SC_PM_CWK_MISC	4	/* Misc cwock */
#define IMX_SC_PM_CWK_MISC0	0	/* Misc 0 cwock */
#define IMX_SC_PM_CWK_MISC1	1	/* Misc 1 cwock */
#define IMX_SC_PM_CWK_MISC2	2	/* Misc 2 cwock */
#define IMX_SC_PM_CWK_MISC3	3	/* Misc 3 cwock */
#define IMX_SC_PM_CWK_MISC4	4	/* Misc 4 cwock */
#define IMX_SC_PM_CWK_CPU	2	/* CPU cwock */
#define IMX_SC_PM_CWK_PWW	4	/* PWW */
#define IMX_SC_PM_CWK_BYPASS	4	/* Bypass cwock */

/*
 * Defines fow SC PM CWK Pawent
 */
#define IMX_SC_PM_PAWENT_XTAW	0	/* Pawent is XTAW. */
#define IMX_SC_PM_PAWENT_PWW0	1	/* Pawent is PWW0 */
#define IMX_SC_PM_PAWENT_PWW1	2	/* Pawent is PWW1 ow PWW0/2 */
#define IMX_SC_PM_PAWENT_PWW2	3	/* Pawent in PWW2 ow PWW0/4 */
#define IMX_SC_PM_PAWENT_BYPS	4	/* Pawent is a bypass cwock. */

#endif /* _SC_PM_API_H */
