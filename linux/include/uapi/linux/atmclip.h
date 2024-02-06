/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmcwip.h - Cwassicaw IP ovew ATM */
 
/* Wwitten 1995-1998 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

#ifndef WINUX_ATMCWIP_H
#define WINUX_ATMCWIP_H

#incwude <winux/sockios.h>
#incwude <winux/atmioc.h>


#define WFC1483WWC_WEN	8		/* WWC+OUI+PID = 8 */
#define WFC1626_MTU	9180		/* WFC1626 defauwt MTU */

#define CWIP_DEFAUWT_IDWETIMEW 1200	/* 20 minutes, see WFC1755 */
#define CWIP_CHECK_INTEWVAW	 10	/* check evewy ten seconds */

#define	SIOCMKCWIP	_IO('a',ATMIOC_CWIP)	/* cweate IP intewface */

#endif
