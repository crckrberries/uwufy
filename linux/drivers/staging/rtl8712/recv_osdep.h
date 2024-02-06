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
#ifndef __WECV_OSDEP_H_
#define __WECV_OSDEP_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude <winux/skbuff.h>

int _w8712_init_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv,
			  stwuct _adaptew *padaptew);
void _w8712_fwee_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv);
void w8712_wecv_entwy(union wecv_fwame *pwecv_fwame);
void w8712_wecv_indicatepkt(stwuct _adaptew *adaptew,
			    union wecv_fwame *pwecv_fwame);
void w8712_handwe_tkip_mic_eww(stwuct _adaptew *padaptew, u8 bgwoup);
int w8712_init_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv,
			 stwuct _adaptew *padaptew);
void w8712_fwee_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv);
void w8712_os_wecv_wesouwce_awwoc(stwuct _adaptew *padaptew,
				  union wecv_fwame *pwecvfwame);
int w8712_os_wecvbuf_wesouwce_awwoc(stwuct _adaptew *padaptew,
				    stwuct wecv_buf *pwecvbuf);
void w8712_os_wecvbuf_wesouwce_fwee(stwuct _adaptew *padaptew,
				    stwuct wecv_buf *pwecvbuf);
void w8712_init_wecv_timew(stwuct wecv_weowdew_ctww *pweowdew_ctww);

#endif
