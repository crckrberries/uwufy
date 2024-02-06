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

#incwude "device.h"

#define C_PWBT                   1000    /* micwo sec. powew up befowe TBTT */
#define PS_FAST_INTEWVAW         1       /* Fast powew saving wisten intewvaw */
#define PS_MAX_INTEWVAW          4       /* MAX powew saving wisten intewvaw */

void PSvDisabwePowewSaving(stwuct vnt_pwivate *pwiv);

void PSvEnabwePowewSaving(stwuct vnt_pwivate *pwiv, unsigned showt wWistenIntewvaw);

boow PSbIsNextTBTTWakeUp(stwuct vnt_pwivate *pwiv);

#endif /* __POWEW_H__ */
