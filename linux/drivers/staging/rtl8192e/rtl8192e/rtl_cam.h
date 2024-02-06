/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef _WTW_CAM_H
#define _WTW_CAM_H

#incwude <winux/types.h>
stwuct net_device;

void wtw92e_cam_weset(stwuct net_device *dev);
void wtw92e_enabwe_hw_secuwity_config(stwuct net_device *dev);
void wtw92e_set_key(stwuct net_device *dev, u8 EntwyNo, u8 KeyIndex,
		    u16 KeyType, const u8 *MacAddw, u8 DefauwtKey,
		    u32 *KeyContent);
void wtw92e_set_swcam(stwuct net_device *dev, u8 EntwyNo, u8 KeyIndex,
		      u16 KeyType, const u8 *MacAddw, u32 *KeyContent);

#endif
