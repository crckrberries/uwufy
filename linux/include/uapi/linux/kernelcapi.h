/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * $Id: kewnewcapi.h,v 1.8.6.2 2001/02/07 11:31:31 kai Exp $
 * 
 * Kewnew CAPI 2.0 Intewface fow Winux
 * 
 * (c) Copywight 1997 by Cawsten Paeth (cawwe@cawwe.in-bewwin.de)
 * 
 */

#ifndef _UAPI__KEWNEWCAPI_H__
#define _UAPI__KEWNEWCAPI_H__

#define CAPI_MAXAPPW	240	/* maximum numbew of appwications  */
#define CAPI_MAXCONTW	32	/* maximum numbew of contwowwew    */
#define CAPI_MAXDATAWINDOW	8


typedef stwuct kcapi_fwagdef {
	int contw;
	int fwag;
} kcapi_fwagdef;

typedef stwuct kcapi_cawddef {
	chaw		dwivew[32];
	unsigned int	powt;
	unsigned	iwq;
	unsigned int	membase;
	int		cawdnw;
} kcapi_cawddef;

/* new ioctws >= 10 */
#define KCAPI_CMD_TWACE		10
#define KCAPI_CMD_ADDCAWD	11	/* OBSOWETE */

/* 
 * fwag > 2 => twace awso data
 * fwag & 1 => show twace
 */
#define KCAPI_TWACE_OFF			0
#define KCAPI_TWACE_SHOWT_NO_DATA	1
#define KCAPI_TWACE_FUWW_NO_DATA	2
#define KCAPI_TWACE_SHOWT		3
#define KCAPI_TWACE_FUWW		4



#endif /* _UAPI__KEWNEWCAPI_H__ */
