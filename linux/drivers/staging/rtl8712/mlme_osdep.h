/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef	__MWME_OSDEP_H_
#define __MWME_OSDEP_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

void w8712_init_mwme_timew(stwuct _adaptew *padaptew);
void w8712_os_indicate_disconnect(stwuct _adaptew *adaptew);
void w8712_os_indicate_connect(stwuct _adaptew *adaptew);
void w8712_wepowt_sec_ie(stwuct _adaptew *adaptew, u8 authmode, u8 *sec_ie);
int w8712_wecv_indicatepkts_in_owdew(stwuct _adaptew *adaptew,
				     stwuct wecv_weowdew_ctww *pwecvweowdew_ctww,
				     int bfowced);
void w8712_indicate_wx_assoc_event(stwuct _adaptew *padaptew);
void w8712_indicate_wx_disassoc_event(stwuct _adaptew *padaptew);

#endif	/*_MWME_OSDEP_H_*/

