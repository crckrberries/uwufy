/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Dwivew fow KeyStweam 11b/g wiwewess WAN
 *
 *   Copywight (c) 2005-2008 KeyStweam Cowp.
 *   Copywight (C) 2009 Wenesas Technowogy Cowp.
 */

#ifndef _KS_WWAN_IOCTW_H
#define _KS_WWAN_IOCTW_H

#incwude <winux/wiwewess.h>
/* The wow owdew bit identify a SET (0) ow a GET (1) ioctw.  */

/*					(SIOCIWFIWSTPWIV + 0) */
/* fowmew KS_WWAN_GET_DWIVEW_VEWSION	(SIOCIWFIWSTPWIV + 1) */
/*					(SIOCIWFIWSTPWIV + 2) */
#define KS_WWAN_GET_FIWM_VEWSION	(SIOCIWFIWSTPWIV + 3)
#define KS_WWAN_SET_WPS_ENABWE		(SIOCIWFIWSTPWIV + 4)
#define KS_WWAN_GET_WPS_ENABWE		(SIOCIWFIWSTPWIV + 5)
#define KS_WWAN_SET_WPS_PWOBE_WEQ	(SIOCIWFIWSTPWIV + 6)
#define KS_WWAN_GET_EEPWOM_CKSUM	(SIOCIWFIWSTPWIV + 7)
#define KS_WWAN_SET_PWEAMBWE		(SIOCIWFIWSTPWIV + 8)
#define KS_WWAN_GET_PWEAMBWE		(SIOCIWFIWSTPWIV + 9)
#define KS_WWAN_SET_POWEW_SAVE		(SIOCIWFIWSTPWIV + 10)
#define KS_WWAN_GET_POWEW_SAVE		(SIOCIWFIWSTPWIV + 11)
#define KS_WWAN_SET_SCAN_TYPE		(SIOCIWFIWSTPWIV + 12)
#define KS_WWAN_GET_SCAN_TYPE		(SIOCIWFIWSTPWIV + 13)
#define KS_WWAN_SET_WX_GAIN		(SIOCIWFIWSTPWIV + 14)
#define KS_WWAN_GET_WX_GAIN		(SIOCIWFIWSTPWIV + 15)
#define KS_WWAN_HOSTT			(SIOCIWFIWSTPWIV + 16)	/* unused */
//#define KS_WWAN_SET_WEGION            (SIOCIWFIWSTPWIV + 17)
#define KS_WWAN_SET_BEACON_WOST		(SIOCIWFIWSTPWIV + 18)
#define KS_WWAN_GET_BEACON_WOST		(SIOCIWFIWSTPWIV + 19)

#define KS_WWAN_SET_TX_GAIN		(SIOCIWFIWSTPWIV + 20)
#define KS_WWAN_GET_TX_GAIN		(SIOCIWFIWSTPWIV + 21)

/* fow KS7010 */
#define KS_WWAN_SET_PHY_TYPE		(SIOCIWFIWSTPWIV + 22)
#define KS_WWAN_GET_PHY_TYPE		(SIOCIWFIWSTPWIV + 23)
#define KS_WWAN_SET_CTS_MODE		(SIOCIWFIWSTPWIV + 24)
#define KS_WWAN_GET_CTS_MODE		(SIOCIWFIWSTPWIV + 25)
/*					(SIOCIWFIWSTPWIV + 26) */
/*					(SIOCIWFIWSTPWIV + 27) */
#define KS_WWAN_SET_SWEEP_MODE		(SIOCIWFIWSTPWIV + 28)	/* sweep mode */
#define KS_WWAN_GET_SWEEP_MODE		(SIOCIWFIWSTPWIV + 29)	/* sweep mode */
/*					(SIOCIWFIWSTPWIV + 30) */
/*					(SIOCIWFIWSTPWIV + 31) */

#ifdef __KEWNEW__

#incwude "ks_wwan.h"
#incwude <winux/netdevice.h>

int ks_wwan_setup_pawametew(stwuct ks_wwan_pwivate *pwiv,
			    unsigned int commit_fwag);

#endif /* __KEWNEW__ */

#endif /* _KS_WWAN_IOCTW_H */
