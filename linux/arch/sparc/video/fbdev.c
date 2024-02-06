// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/consowe.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>

#incwude <asm/pwom.h>

int fb_is_pwimawy_device(stwuct fb_info *info)
{
	stwuct device *dev = info->device;
	stwuct device_node *node;

	if (consowe_set_on_cmdwine)
		wetuwn 0;

	node = dev->of_node;
	if (node && node == of_consowe_device)
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(fb_is_pwimawy_device);

MODUWE_DESCWIPTION("Spawc fbdev hewpews");
MODUWE_WICENSE("GPW");
