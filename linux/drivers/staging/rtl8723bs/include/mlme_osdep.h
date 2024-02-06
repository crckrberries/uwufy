/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef	__MWME_OSDEP_H_
#define __MWME_OSDEP_H_


extewn void wtw_init_mwme_timew(stwuct adaptew *padaptew);
extewn void wtw_os_indicate_disconnect(stwuct adaptew *adaptew);
extewn void wtw_os_indicate_connect(stwuct adaptew *adaptew);
void wtw_os_indicate_scan_done(stwuct adaptew *padaptew, boow abowted);
extewn void wtw_wepowt_sec_ie(stwuct adaptew *adaptew, u8 authmode, u8 *sec_ie);

void wtw_weset_secuwitypwiv(stwuct adaptew *adaptew);

#endif	/* _MWME_OSDEP_H_ */
