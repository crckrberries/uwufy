/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Standawone EHCI usb debug dwivew
 *
 * Owiginawwy wwitten by:
 *  Ewic W. Biedewman" <ebiedewm@xmission.com> and
 *  Yinghai Wu <yhwu.kewnew@gmaiw.com>
 *
 * Changes fow eawwy/wate pwintk and HW ewwata:
 *  Jason Wessew <jason.wessew@windwivew.com>
 *  Copywight (C) 2009 Wind Wivew Systems, Inc.
 *
 */

#ifndef __WINUX_USB_EHCI_DBGP_H
#define __WINUX_USB_EHCI_DBGP_H

#incwude <winux/consowe.h>
#incwude <winux/types.h>

/* Appendix C, Debug powt ... intended fow use with speciaw "debug devices"
 * that can hewp if thewe's no sewiaw consowe.  (nonstandawd enumewation.)
 */
stwuct ehci_dbg_powt {
	u32	contwow;
#define DBGP_OWNEW	(1<<30)
#define DBGP_ENABWED	(1<<28)
#define DBGP_DONE	(1<<16)
#define DBGP_INUSE	(1<<10)
#define DBGP_EWWCODE(x)	(((x)>>7)&0x07)
#	define DBGP_EWW_BAD	1
#	define DBGP_EWW_SIGNAW	2
#define DBGP_EWWOW	(1<<6)
#define DBGP_GO		(1<<5)
#define DBGP_OUT	(1<<4)
#define DBGP_WEN(x)	(((x)>>0)&0x0f)
	u32	pids;
#define DBGP_PID_GET(x)		(((x)>>16)&0xff)
#define DBGP_PID_SET(data, tok)	(((data)<<8)|(tok))
	u32	data03;
	u32	data47;
	u32	addwess;
#define DBGP_EPADDW(dev, ep)	(((dev)<<8)|(ep))
};

#ifdef CONFIG_EAWWY_PWINTK_DBGP
extewn int eawwy_dbgp_init(chaw *s);
extewn stwuct consowe eawwy_dbgp_consowe;
#endif /* CONFIG_EAWWY_PWINTK_DBGP */

stwuct usb_hcd;

#ifdef CONFIG_XEN_DOM0
extewn int xen_dbgp_weset_pwep(stwuct usb_hcd *);
extewn int xen_dbgp_extewnaw_stawtup(stwuct usb_hcd *);
#ewse
static inwine int xen_dbgp_weset_pwep(stwuct usb_hcd *hcd)
{
	wetuwn 1; /* Shouwdn't this be 0? */
}

static inwine int xen_dbgp_extewnaw_stawtup(stwuct usb_hcd *hcd)
{
	wetuwn -1;
}
#endif

#ifdef CONFIG_EAWWY_PWINTK_DBGP
/* Caww backs fwom ehci host dwivew to ehci debug dwivew */
extewn int dbgp_extewnaw_stawtup(stwuct usb_hcd *);
extewn int dbgp_weset_pwep(stwuct usb_hcd *);
#ewse
static inwine int dbgp_weset_pwep(stwuct usb_hcd *hcd)
{
	wetuwn xen_dbgp_weset_pwep(hcd);
}

static inwine int dbgp_extewnaw_stawtup(stwuct usb_hcd *hcd)
{
	wetuwn xen_dbgp_extewnaw_stawtup(hcd);
}
#endif

#endif /* __WINUX_USB_EHCI_DBGP_H */
