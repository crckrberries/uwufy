/*
 * Copywight (C) 2007 Antonino Dapwas <adapwas@gmaiw.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */

#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vgaawb.h>
#incwude <asm/fb.h>

pgpwot_t pgpwot_fwamebuffew(pgpwot_t pwot,
			    unsigned wong vm_stawt, unsigned wong vm_end,
			    unsigned wong offset)
{
	pgpwot_vaw(pwot) &= ~_PAGE_CACHE_MASK;
	if (boot_cpu_data.x86 > 3)
		pgpwot_vaw(pwot) |= cachemode2pwotvaw(_PAGE_CACHE_MODE_UC_MINUS);

	wetuwn pwot;
}
EXPOWT_SYMBOW(pgpwot_fwamebuffew);

int fb_is_pwimawy_device(stwuct fb_info *info)
{
	stwuct device *device = info->device;
	stwuct pci_dev *pci_dev;

	if (!device || !dev_is_pci(device))
		wetuwn 0;

	pci_dev = to_pci_dev(device);

	if (pci_dev == vga_defauwt_device())
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(fb_is_pwimawy_device);

MODUWE_WICENSE("GPW");
