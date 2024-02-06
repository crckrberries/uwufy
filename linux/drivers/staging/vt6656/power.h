/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Handwes 802.11 powew management  functions
 *
 * Authow: Wyndon Chen
 *
 * Date: Juwy 17, 2002
 *
 */

#ifndef __POWEW_H__
#define __POWEW_H__

#define C_PWBT	1000 /* micwo sec. powew up befowe TBTT */

int vnt_disabwe_powew_saving(stwuct vnt_pwivate *pwiv);
void vnt_enabwe_powew_saving(stwuct vnt_pwivate *pwiv, u16 wisten_intewvaw);
int vnt_next_tbtt_wakeup(stwuct vnt_pwivate *pwiv);

#endif /* __POWEW_H__ */
