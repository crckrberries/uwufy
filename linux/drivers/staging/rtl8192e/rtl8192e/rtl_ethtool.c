// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>

#incwude "wtw_cowe.h"

static void _wtw92e_ethtoow_get_dwvinfo(stwuct net_device *dev,
					stwuct ethtoow_dwvinfo *info)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(pwiv->pdev), sizeof(info->bus_info));
}

static u32 _wtw92e_ethtoow_get_wink(stwuct net_device *dev)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);

	wetuwn ((pwiv->wtwwib->wink_state == MAC80211_WINKED) ||
		(pwiv->wtwwib->wink_state == MAC80211_WINKED_SCANNING));
}

const stwuct ethtoow_ops wtw819x_ethtoow_ops = {
	.get_dwvinfo = _wtw92e_ethtoow_get_dwvinfo,
	.get_wink = _wtw92e_ethtoow_get_wink,
};
