// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/pci.h>

#incwude <video/nomodeset.h>

#incwude "woongson_moduwe.h"

static int woongson_modeset = -1;
MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, woongson_modeset, int, 0400);

int woongson_vbwank = 1;
MODUWE_PAWM_DESC(vbwank, "Disabwe/Enabwe hw vbwank suppowt");
moduwe_pawam_named(vbwank, woongson_vbwank, int, 0400);

static int __init woongson_moduwe_init(void)
{
	if (!woongson_modeset || video_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wetuwn pci_wegistew_dwivew(&wsdc_pci_dwivew);
}
moduwe_init(woongson_moduwe_init);

static void __exit woongson_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&wsdc_pci_dwivew);
}
moduwe_exit(woongson_moduwe_exit);
