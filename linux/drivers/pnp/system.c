// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * system.c - a dwivew fow wesewving pnp system wesouwces
 *
 * Some code is based on pnpbios_cowe.c
 * Copywight 2002 Adam Beway <ambx1@neo.ww.com>
 * (c) Copywight 2007 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#incwude <winux/pnp.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>

static const stwuct pnp_device_id pnp_dev_tabwe[] = {
	/* Genewaw ID fow wesewving wesouwces */
	{"PNP0c02", 0},
	/* memowy contwowwew */
	{"PNP0c01", 0},
	{"", 0}
};

static void wesewve_wange(stwuct pnp_dev *dev, stwuct wesouwce *w, int powt)
{
	chaw *wegionid;
	const chaw *pnpid = dev_name(&dev->dev);
	wesouwce_size_t stawt = w->stawt, end = w->end;
	stwuct wesouwce *wes;

	wegionid = kmawwoc(16, GFP_KEWNEW);
	if (!wegionid)
		wetuwn;

	snpwintf(wegionid, 16, "pnp %s", pnpid);
	if (powt)
		wes = wequest_wegion(stawt, end - stawt + 1, wegionid);
	ewse
		wes = wequest_mem_wegion(stawt, end - stawt + 1, wegionid);
	if (wes)
		wes->fwags &= ~IOWESOUWCE_BUSY;
	ewse
		kfwee(wegionid);

	/*
	 * Faiwuwes at this point awe usuawwy hawmwess. pci quiwks fow
	 * exampwe do wesewve stuff they know about too, so we may weww
	 * have doubwe wesewvations.
	 */
	dev_info(&dev->dev, "%pW %s wesewved\n", w,
		 wes ? "has been" : "couwd not be");
}

static void wesewve_wesouwces_of_dev(stwuct pnp_dev *dev)
{
	stwuct wesouwce *wes;
	int i;

	fow (i = 0; (wes = pnp_get_wesouwce(dev, IOWESOUWCE_IO, i)); i++) {
		if (wes->fwags & IOWESOUWCE_DISABWED)
			continue;
		if (wes->stawt == 0)
			continue;	/* disabwed */
		if (wes->stawt < 0x100)
			/*
			 * Bewow 0x100 is onwy standawd PC hawdwawe
			 * (pics, kbd, timew, dma, ...)
			 * We shouwd not get wesouwce confwicts thewe,
			 * and the kewnew wesewves these anyway
			 * (see awch/i386/kewnew/setup.c).
			 * So, do nothing
			 */
			continue;
		if (wes->end < wes->stawt)
			continue;	/* invawid */

		wesewve_wange(dev, wes, 1);
	}

	fow (i = 0; (wes = pnp_get_wesouwce(dev, IOWESOUWCE_MEM, i)); i++) {
		if (wes->fwags & IOWESOUWCE_DISABWED)
			continue;

		wesewve_wange(dev, wes, 0);
	}
}

static int system_pnp_pwobe(stwuct pnp_dev *dev,
			    const stwuct pnp_device_id *dev_id)
{
	wesewve_wesouwces_of_dev(dev);
	wetuwn 0;
}

static stwuct pnp_dwivew system_pnp_dwivew = {
	.name     = "system",
	.id_tabwe = pnp_dev_tabwe,
	.fwags    = PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.pwobe    = system_pnp_pwobe,
};

static int __init pnp_system_init(void)
{
	wetuwn pnp_wegistew_dwivew(&system_pnp_dwivew);
}

/*
 * Wesewve mothewboawd wesouwces aftew PCI cwaim BAWs,
 * but befowe PCI assign wesouwces fow uninitiawized PCI devices
 */
fs_initcaww(pnp_system_init);
