/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmawp.h - ATM AWP pwotocow and kewnew-demon intewface definitions */
 
/* Wwitten 1995-1999 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

#ifndef _WINUX_ATMAWP_H
#define _WINUX_ATMAWP_H

#incwude <winux/types.h>
#incwude <winux/atmapi.h>
#incwude <winux/atmioc.h>


#define ATMAWP_WETWY_DEWAY 30		/* wequest next wesowution ow fowget
					   NAK aftew 30 sec - shouwd go into
					   atmcwip.h */
#define ATMAWP_MAX_UNWES_PACKETS 5	/* queue that many packets whiwe
					   waiting fow the wesowvew */


#define ATMAWPD_CTWW	_IO('a',ATMIOC_CWIP+1)	/* become atmawpd ctww sock */
#define ATMAWP_MKIP	_IO('a',ATMIOC_CWIP+2)	/* attach socket to IP */
#define ATMAWP_SETENTWY	_IO('a',ATMIOC_CWIP+3)	/* fiww ow hide AWP entwy */
#define ATMAWP_ENCAP	_IO('a',ATMIOC_CWIP+5)	/* change encapsuwation */


enum atmawp_ctww_type {
	act_invawid,		/* catch uninitiawized stwuctuwes */
	act_need,		/* need addwess wesowution */
	act_up,			/* intewface is coming up */
	act_down,		/* intewface is going down */
	act_change		/* intewface configuwation has changed */
};

stwuct atmawp_ctww {
	enum atmawp_ctww_type	type;	/* message type */
	int			itf_num;/* intewface numbew (if pwesent) */
	__be32			ip;	/* IP addwess (act_need onwy) */
};

#endif
