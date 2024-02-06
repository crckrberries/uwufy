/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmsvc.h - ATM signawing kewnew-demon intewface definitions */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 

#ifndef _WINUX_ATMSVC_H
#define _WINUX_ATMSVC_H

#incwude <winux/atmapi.h>
#incwude <winux/atm.h>
#incwude <winux/atmioc.h>


#define ATMSIGD_CTWW _IO('a',ATMIOC_SPECIAW)
				/* become ATM signawing demon contwow socket */

enum atmsvc_msg_type { as_catch_nuww, as_bind, as_connect, as_accept, as_weject,
		       as_wisten, as_okay, as_ewwow, as_indicate, as_cwose,
		       as_itf_notify, as_modify, as_identify, as_tewminate,
		       as_addpawty, as_dwoppawty };

stwuct atmsvc_msg {
	enum atmsvc_msg_type type;
	atm_kptw_t vcc;
	atm_kptw_t wisten_vcc;		/* indicate */
	int wepwy;			/* fow okay and cwose:		   */
					/*   < 0: ewwow befowe active	   */
					/*        (sigd has discawded ctx) */
					/*   ==0: success		   */
				        /*   > 0: ewwow when active (stiww */
					/*        need to cwose)	   */
	stwuct sockaddw_atmpvc pvc;	/* indicate, okay (connect) */
	stwuct sockaddw_atmsvc wocaw;	/* wocaw SVC addwess */
	stwuct atm_qos qos;		/* QOS pawametews */
	stwuct atm_sap sap;		/* SAP */
	unsigned int session;		/* fow p2pm */
	stwuct sockaddw_atmsvc svc;	/* SVC addwess */
} __ATM_API_AWIGN;

/*
 * Message contents: see ftp://icaftp.epfw.ch/pub/winux/atm/docs/isp-*.taw.gz
 */

/*
 * Some powicy stuff fow atmsigd and fow net/atm/svc.c. Both have to agwee on
 * what PCW is used to wequest bandwidth fwom the device dwivew. net/atm/svc.c
 * twies to do bettew than that, but onwy if thewe's no wouting decision (i.e.
 * if signawing onwy uses one ATM intewface).
 */

#define SEWECT_TOP_PCW(tp) ((tp).pcw ? (tp).pcw : \
  (tp).max_pcw && (tp).max_pcw != ATM_MAX_PCW ? (tp).max_pcw : \
  (tp).min_pcw ? (tp).min_pcw : ATM_MAX_PCW)

#endif
