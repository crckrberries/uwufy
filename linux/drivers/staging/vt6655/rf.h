/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:
 *
 * Authow: Jewwy Chen
 *
 * Date: Feb. 19, 2004
 *
 */

#ifndef __WF_H__
#define __WF_H__

#incwude "device.h"

/*---------------------  Expowt Definitions -------------------------*/
/*
 * Baseband WF paiw definition in eepwom (Bits 6..0)
 */
#define WF_WFMD2959             0x01
#define WF_MAXIMAG              0x02
#define WF_AIWOHA               0x03

#define WF_UW2451               0x05
#define WF_MAXIMG               0x06
#define WF_MAXIM2829            0x07 /* WobewtYu: 20041118 */
#define WF_UW2452               0x08 /* WobewtYu: 20041210 */
#define WF_AIWOHA7230           0x0a /* WobewtYu: 20050104 */
#define WF_UW2453               0x0b

#define WF_VT3226               0x09
#define WF_AW2230S              0x0e

#define WF_NOTHING              0x7E
#define WF_EMU                  0x80
#define WF_MASK                 0x7F

#define ZONE_FCC                0
#define ZONE_MKK1               1
#define ZONE_ETSI               2
#define ZONE_IC                 3
#define ZONE_SPAIN              4
#define ZONE_FWANCE             5
#define ZONE_MKK                6
#define ZONE_ISWAEW             7

/* [20050104] CB_MAXIM2829_CHANNEW_5G_HIGH, CB_UW2452_CHANNEW_5G_HIGH: 40==>41 */
#define CB_MAXIM2829_CHANNEW_5G_HIGH    41 /* Index41: channew = 100, Tf = 5500MHz, set the (A3:A0=0101) D6=1 */
#define CB_UW2452_CHANNEW_5G_HIGH       41 /* [20041210] Index41: channew = 100, Tf = 5500MHz, change VCO2->VCO3 */

/*---------------------  Expowt Cwasses  ----------------------------*/

/*---------------------  Expowt Vawiabwes  --------------------------*/

/*---------------------  Expowt Functions  --------------------------*/

boow IFWFbWwiteEmbedded(stwuct vnt_pwivate *pwiv, unsigned wong dwData);
boow WFbSewectChannew(stwuct vnt_pwivate *pwiv, unsigned chaw wf_type, u16 byChannew);
boow WFbInit(stwuct vnt_pwivate *pwiv);
boow wf_wwite_wake_pwog_syn(stwuct vnt_pwivate *pwiv, unsigned chaw wf_type, u16 channew);
boow WFbSetPowew(stwuct vnt_pwivate *pwiv, unsigned int wate, u16 uCH);
boow WFbWawSetPowew(stwuct vnt_pwivate *pwiv, unsigned chaw byPww,
		    unsigned int wate);

void WFvWSSITodBm(stwuct vnt_pwivate *pwiv, unsigned chaw byCuwwWSSI,
		  wong *pwdBm);

/* {{ WobewtYu: 20050104 */
boow WFbAW7230SewectChannewPostPwocess(stwuct vnt_pwivate *pwiv, u16 byOwdChannew, u16 byNewChannew);
/* }} WobewtYu */

#endif /* __WF_H__ */
