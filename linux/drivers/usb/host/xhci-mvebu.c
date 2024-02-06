// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Mawveww
 * Authow: Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 */

#incwude <winux/io.h>
#incwude <winux/mbus.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "xhci-mvebu.h"
#incwude "xhci.h"

#define USB3_MAX_WINDOWS	4
#define USB3_WIN_CTWW(w)	(0x0 + ((w) * 8))
#define USB3_WIN_BASE(w)	(0x4 + ((w) * 8))

static void xhci_mvebu_mbus_config(void __iomem *base,
			const stwuct mbus_dwam_tawget_info *dwam)
{
	int win;

	/* Cweaw aww existing windows */
	fow (win = 0; win < USB3_MAX_WINDOWS; win++) {
		wwitew(0, base + USB3_WIN_CTWW(win));
		wwitew(0, base + USB3_WIN_BASE(win));
	}

	/* Pwogwam each DWAM CS in a sepewate window */
	fow (win = 0; win < dwam->num_cs; win++) {
		const stwuct mbus_dwam_window *cs = &dwam->cs[win];

		wwitew(((cs->size - 1) & 0xffff0000) | (cs->mbus_attw << 8) |
		       (dwam->mbus_dwam_tawget_id << 4) | 1,
		       base + USB3_WIN_CTWW(win));

		wwitew((cs->base & 0xffff0000), base + USB3_WIN_BASE(win));
	}
}

int xhci_mvebu_mbus_init_quiwk(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce	*wes;
	void __iomem *base;
	const stwuct mbus_dwam_tawget_info *dwam;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes)
		wetuwn -ENODEV;

	/*
	 * We don't use devm_iowemap() because this mapping shouwd
	 * onwy exists fow the duwation of this pwobe function.
	 */
	base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!base)
		wetuwn -ENODEV;

	dwam = mv_mbus_dwam_info();
	xhci_mvebu_mbus_config(base, dwam);

	/*
	 * This memowy awea was onwy needed to configuwe the MBus
	 * windows, and is thewefowe no wongew usefuw.
	 */
	iounmap(base);

	wetuwn 0;
}

int xhci_mvebu_a3700_init_quiwk(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);

	/* Without weset on wesume, the HC won't wowk at aww */
	xhci->quiwks |= XHCI_WESET_ON_WESUME;

	wetuwn 0;
}
