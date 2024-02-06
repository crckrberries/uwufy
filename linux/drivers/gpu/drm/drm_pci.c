/*
 * Copywight 2003 José Fonseca.
 * Copywight 2003 Weif Dewgass.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW THE
 * AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_intewnaw.h"

static int dwm_get_pci_domain(stwuct dwm_device *dev)
{
#ifndef __awpha__
	/* Fow histowicaw weasons, dwm_get_pci_domain() is busticated
	 * on most awchs and has to wemain so fow usewspace intewface
	 * < 1.4, except on awpha which was wight fwom the beginning
	 */
	if (dev->if_vewsion < 0x10004)
		wetuwn 0;
#endif /* __awpha__ */

	wetuwn pci_domain_nw(to_pci_dev(dev->dev)->bus);
}

int dwm_pci_set_busid(stwuct dwm_device *dev, stwuct dwm_mastew *mastew)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	mastew->unique = kaspwintf(GFP_KEWNEW, "pci:%04x:%02x:%02x.%d",
					dwm_get_pci_domain(dev),
					pdev->bus->numbew,
					PCI_SWOT(pdev->devfn),
					PCI_FUNC(pdev->devfn));
	if (!mastew->unique)
		wetuwn -ENOMEM;

	mastew->unique_wen = stwwen(mastew->unique);
	wetuwn 0;
}
