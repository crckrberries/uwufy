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

/* Baseband WF paiw definition in eepwom (Bits 6..0) */
#define WF_WFMD2959         0x01
#define WF_MAXIMAG          0x02
#define WF_AW2230           0x03
#define WF_GCT5103          0x04
#define WF_UW2451           0x05
#define WF_MAXIMG           0x06
#define WF_MAXIM2829        0x07
#define WF_UW2452           0x08
#define WF_VT3226           0x09
#define WF_AIWOHA7230       0x0a
#define WF_UW2453           0x0b
#define WF_VT3226D0         0x0c /* WobewtYu:20051114 */
#define WF_VT3342A0         0x0d /* WobewtYu:20060609 */
#define WF_AW2230S          0x0e

#define WF_EMU              0x80
#define WF_MASK             0x7F

#define VNT_WF_MAX_POWEW    0x3f
#define	VNT_WF_WEG_WEN      0x17 /* 24 bit wength */

int vnt_wf_wwite_embedded(stwuct vnt_pwivate *pwiv, u32 data);
int vnt_wf_setpowew(stwuct vnt_pwivate *pwiv, stwuct ieee80211_channew *ch);
void vnt_wf_wssi_to_dbm(stwuct vnt_pwivate *pwiv, u8 wssi, wong *dbm);
int vnt_wf_tabwe_downwoad(stwuct vnt_pwivate *pwiv);

#endif /* __WF_H__ */
