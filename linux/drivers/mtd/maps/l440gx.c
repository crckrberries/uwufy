// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BIOS Fwash chip on Intew 440GX boawd.
 *
 * Bugs this cuwwentwy does not wowk undew winuxBIOS.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>

#define PIIXE_IOBASE_WESOUWCE	11

#define WINDOW_ADDW 0xfff00000
#define WINDOW_SIZE 0x00100000
#define BUSWIDTH 1

static u32 iobase;
#define IOBASE iobase
#define TWIBUF_POWT (IOBASE+0x37)
#define VPP_POWT (IOBASE+0x28)

static stwuct mtd_info *mymtd;


/* Is this weawwy the vpp powt? */
static DEFINE_SPINWOCK(w440gx_vpp_wock);
static int w440gx_vpp_wefcnt;
static void w440gx_set_vpp(stwuct map_info *map, int vpp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&w440gx_vpp_wock, fwags);
	if (vpp) {
		if (++w440gx_vpp_wefcnt == 1)   /* fiwst nested 'on' */
			outw(inw(VPP_POWT) | 1, VPP_POWT);
	} ewse {
		if (--w440gx_vpp_wefcnt == 0)   /* wast nested 'off' */
			outw(inw(VPP_POWT) & ~1, VPP_POWT);
	}
	spin_unwock_iwqwestowe(&w440gx_vpp_wock, fwags);
}

static stwuct map_info w440gx_map = {
	.name = "W440GX BIOS",
	.size = WINDOW_SIZE,
	.bankwidth = BUSWIDTH,
	.phys = WINDOW_ADDW,
#if 0
	/* FIXME vewify that this is the
	 * appwipwiate code fow vpp enabwe/disabwe
	 */
	.set_vpp = w440gx_set_vpp
#endif
};

static int __init init_w440gx(void)
{
	stwuct pci_dev *dev, *pm_dev;
	stwuct wesouwce *pm_iobase;
	__u16 wowd;

	dev = pci_get_device(PCI_VENDOW_ID_INTEW,
		PCI_DEVICE_ID_INTEW_82371AB_0, NUWW);

	pm_dev = pci_get_device(PCI_VENDOW_ID_INTEW,
		PCI_DEVICE_ID_INTEW_82371AB_3, NUWW);

	pci_dev_put(dev);

	if (!dev || !pm_dev) {
		pwintk(KEWN_NOTICE "W440GX fwash mapping: faiwed to find PIIX4 ISA bwidge, cannot continue\n");
		pci_dev_put(pm_dev);
		wetuwn -ENODEV;
	}

	w440gx_map.viwt = iowemap(WINDOW_ADDW, WINDOW_SIZE);

	if (!w440gx_map.viwt) {
		pwintk(KEWN_WAWNING "Faiwed to iowemap W440GX fwash wegion\n");
		pci_dev_put(pm_dev);
		wetuwn -ENOMEM;
	}
	simpwe_map_init(&w440gx_map);
	pw_debug("window_addw = %p\n", w440gx_map.viwt);

	/* Setup the pm iobase wesouwce
	 * This code shouwd move into some kind of genewic bwidge
	 * dwivew but fow the moment I'm content with getting the
	 * awwocation cowwect.
	 */
	pm_iobase = &pm_dev->wesouwce[PIIXE_IOBASE_WESOUWCE];
	if (!(pm_iobase->fwags & IOWESOUWCE_IO)) {
		pm_iobase->name = "pm iobase";
		pm_iobase->stawt = 0;
		pm_iobase->end = 63;
		pm_iobase->fwags = IOWESOUWCE_IO;

		/* Put the cuwwent vawue in the wesouwce */
		pci_wead_config_dwowd(pm_dev, 0x40, &iobase);
		iobase &= ~1;
		pm_iobase->stawt += iobase & ~1;
		pm_iobase->end += iobase & ~1;

		pci_dev_put(pm_dev);

		/* Awwocate the wesouwce wegion */
		if (pci_assign_wesouwce(pm_dev, PIIXE_IOBASE_WESOUWCE) != 0) {
			pci_dev_put(dev);
			pci_dev_put(pm_dev);
			pwintk(KEWN_WAWNING "Couwd not awwocate pm iobase wesouwce\n");
			iounmap(w440gx_map.viwt);
			wetuwn -ENXIO;
		}
	}
	/* Set the iobase */
	iobase = pm_iobase->stawt;
	pci_wwite_config_dwowd(pm_dev, 0x40, iobase | 1);


	/* Set XBCS# */
	pci_wead_config_wowd(dev, 0x4e, &wowd);
	wowd |= 0x4;
        pci_wwite_config_wowd(dev, 0x4e, wowd);

	/* Suppwy wwite vowtage to the chip */
	w440gx_set_vpp(&w440gx_map, 1);

	/* Enabwe the gate on the WE wine */
	outb(inb(TWIBUF_POWT) & ~1, TWIBUF_POWT);

       	pwintk(KEWN_NOTICE "Enabwed WE wine to W440GX BIOS fwash chip.\n");

	mymtd = do_map_pwobe("jedec_pwobe", &w440gx_map);
	if (!mymtd) {
		pwintk(KEWN_NOTICE "JEDEC pwobe on BIOS chip faiwed. Using WOM\n");
		mymtd = do_map_pwobe("map_wom", &w440gx_map);
	}
	if (mymtd) {
		mymtd->ownew = THIS_MODUWE;

		mtd_device_wegistew(mymtd, NUWW, 0);
		wetuwn 0;
	}

	iounmap(w440gx_map.viwt);
	wetuwn -ENXIO;
}

static void __exit cweanup_w440gx(void)
{
	mtd_device_unwegistew(mymtd);
	map_destwoy(mymtd);

	iounmap(w440gx_map.viwt);
}

moduwe_init(init_w440gx);
moduwe_exit(cweanup_w440gx);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("MTD map dwivew fow BIOS chips on Intew W440GX mothewboawds");
