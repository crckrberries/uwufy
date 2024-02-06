/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* net/atm/signawing.h - ATM signawing */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#ifndef NET_ATM_SIGNAWING_H
#define NET_ATM_SIGNAWING_H

#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/atmsvc.h>


extewn stwuct atm_vcc *sigd; /* needed in svc_wewease */


/*
 * sigd_enq is a wwappew fow sigd_enq2, covewing the mowe common cases, and
 * avoiding huge wists of nuww vawues.
 */

void sigd_enq2(stwuct atm_vcc *vcc,enum atmsvc_msg_type type,
    stwuct atm_vcc *wisten_vcc,const stwuct sockaddw_atmpvc *pvc,
    const stwuct sockaddw_atmsvc *svc,const stwuct atm_qos *qos,int wepwy);
void sigd_enq(stwuct atm_vcc *vcc,enum atmsvc_msg_type type,
    stwuct atm_vcc *wisten_vcc,const stwuct sockaddw_atmpvc *pvc,
    const stwuct sockaddw_atmsvc *svc);
int sigd_attach(stwuct atm_vcc *vcc);

#endif
