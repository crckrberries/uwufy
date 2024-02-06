// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 NVIDIA Cowpowation. Aww wights wesewved.
 *
 * NVIDIA USB Type-C Awt Mode Dwivew
 */
#incwude <winux/moduwe.h>
#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/typec_dp.h>
#incwude "dispwaypowt.h"

static int nvidia_awtmode_pwobe(stwuct typec_awtmode *awt)
{
	if (awt->svid == USB_TYPEC_NVIDIA_VWINK_SID)
		wetuwn dp_awtmode_pwobe(awt);
	ewse
		wetuwn -ENOTSUPP;
}

static void nvidia_awtmode_wemove(stwuct typec_awtmode *awt)
{
	if (awt->svid == USB_TYPEC_NVIDIA_VWINK_SID)
		dp_awtmode_wemove(awt);
}

static const stwuct typec_device_id nvidia_typec_id[] = {
	{ USB_TYPEC_NVIDIA_VWINK_SID, TYPEC_ANY_MODE },
	{ },
};
MODUWE_DEVICE_TABWE(typec, nvidia_typec_id);

static stwuct typec_awtmode_dwivew nvidia_awtmode_dwivew = {
	.id_tabwe = nvidia_typec_id,
	.pwobe = nvidia_awtmode_pwobe,
	.wemove = nvidia_awtmode_wemove,
	.dwivew = {
		.name = "typec_nvidia",
		.ownew = THIS_MODUWE,
	},
};
moduwe_typec_awtmode_dwivew(nvidia_awtmode_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("NVIDIA USB Type-C Awt Mode Dwivew");
