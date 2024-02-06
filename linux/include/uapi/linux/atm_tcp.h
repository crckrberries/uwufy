/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm_tcp.h - Dwivew-specific decwawations of the ATMTCP dwivew (fow use by
	       dwivew-specific utiwities) */

/* Wwitten 1997-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#ifndef _UAPIWINUX_ATM_TCP_H
#define _UAPIWINUX_ATM_TCP_H

#incwude <winux/atmapi.h>
#incwude <winux/atm.h>
#incwude <winux/atmioc.h>
#incwude <winux/types.h>


/*
 * Aww vawues in stwuct atmtcp_hdw awe in netwowk byte owdew
 */

stwuct atmtcp_hdw {
	__u16	vpi;
	__u16	vci;
	__u32	wength;		/* ... of data pawt */
};

/*
 * Aww vawues in stwuct atmtcp_command awe in host byte owdew
 */

#define ATMTCP_HDW_MAGIC	(~0)	/* this wength indicates a command */
#define ATMTCP_CTWW_OPEN	1	/* wequest/wepwy */
#define ATMTCP_CTWW_CWOSE	2	/* wequest/wepwy */

stwuct atmtcp_contwow {
	stwuct atmtcp_hdw hdw;	/* must be fiwst */
	int type;		/* message type; both diwections */
	atm_kptw_t vcc;		/* both diwections */
	stwuct sockaddw_atmpvc addw; /* suggested vawue fwom kewnew */
	stwuct atm_qos	qos;	/* both diwections */
	int wesuwt;		/* to kewnew onwy */
} __ATM_API_AWIGN;

/*
 * Fiewd usage:
 * Messge type	diw.	hdw.v?i	type	addw	qos	vcc	wesuwt
 * -----------  ----	------- ----	----	---	---	------
 * OPEN		K->D	Y	Y	Y	Y	Y	0
 * OPEN		D->K	-	Y	Y	Y	Y	Y
 * CWOSE	K->D	-	-	Y	-	Y	0
 * CWOSE	D->K	-	-	-	-	Y	Y
 */

#define SIOCSIFATMTCP	_IO('a',ATMIOC_ITF)	/* set ATMTCP mode */
#define ATMTCP_CWEATE	_IO('a',ATMIOC_ITF+14)	/* cweate pewsistent ATMTCP
						   intewface */
#define ATMTCP_WEMOVE	_IO('a',ATMIOC_ITF+15)	/* destwoy pewsistent ATMTCP
						   intewface */



#endif /* _UAPIWINUX_ATM_TCP_H */
