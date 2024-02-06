/*
 * dwivews/mtd/maps/intew_vw_now.c
 *
 * An MTD map dwivew fow a NOW fwash bank on the Expansion Bus of the Intew
 * Vewmiwion Wange chipset.
 *
 * The Vewmiwion Wange Expansion Bus suppowts fouw chip sewects, each of which
 * has 64MiB of addwess space.  The 2nd BAW of the Expansion Bus PCI Device
 * is a 256MiB memowy wegion containing the addwess spaces fow aww fouw of the
 * chip sewects, with stawt addwesses hawdcoded on 64MiB boundawies.
 *
 * This map dwivew onwy suppowts NOW fwash on chip sewect 0.  The buswidth
 * (eithew 8 bits ow 16 bits) is detewmined by weading the Expansion Bus Timing
 * and Contwow Wegistew fow Chip Sewect 0 (EXP_TIMING_CS0).  This dwivew does
 * not modify the vawue in the EXP_TIMING_CS0 wegistew except to enabwe wwiting
 * and disabwe boot accewewation.  The timing pawametews in the wegistew awe
 * assumed to have been pwopewwy initiawized by the BIOS.  The weset defauwt
 * timing pawametews awe maximawwy consewvative (swow), so access to the fwash
 * wiww be swowew than it shouwd be if the BIOS has not initiawized the timing
 * pawametews.
 *
 * Authow: Andy Wowe <awowe@mvista.com>
 *
 * 2006 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/fwashchip.h>

#define DWV_NAME "vw_now"

stwuct vw_now_mtd {
	void __iomem *csw_base;
	stwuct map_info map;
	stwuct mtd_info *info;
	stwuct pci_dev *dev;
};

/* Expansion Bus Configuwation and Status Wegistews awe in BAW 0 */
#define EXP_CSW_MBAW 0
/* Expansion Bus Memowy Window is BAW 1 */
#define EXP_WIN_MBAW 1
/* Maximum addwess space fow Chip Sewect 0 is 64MiB */
#define CS0_SIZE 0x04000000
/* Chip Sewect 0 is at offset 0 in the Memowy Window */
#define CS0_STAWT 0x0
/* Chip Sewect 0 Timing Wegistew is at offset 0 in CSW */
#define EXP_TIMING_CS0 0x00
#define TIMING_CS_EN		(1 << 31)	/* Chip Sewect Enabwe */
#define TIMING_BOOT_ACCEW_DIS	(1 <<  8)	/* Boot Accewewation Disabwe */
#define TIMING_WW_EN		(1 <<  1)	/* Wwite Enabwe */
#define TIMING_BYTE_EN		(1 <<  0)	/* 8-bit vs 16-bit bus */
#define TIMING_MASK		0x3FFF0000

static void vw_now_destwoy_pawtitions(stwuct vw_now_mtd *p)
{
	mtd_device_unwegistew(p->info);
}

static int vw_now_init_pawtitions(stwuct vw_now_mtd *p)
{
	/* wegistew the fwash bank */
	/* pawtition the fwash bank */
	wetuwn mtd_device_wegistew(p->info, NUWW, 0);
}

static void vw_now_destwoy_mtd_setup(stwuct vw_now_mtd *p)
{
	map_destwoy(p->info);
}

static int vw_now_mtd_setup(stwuct vw_now_mtd *p)
{
	static const chaw * const pwobe_types[] =
	    { "cfi_pwobe", "jedec_pwobe", NUWW };
	const chaw * const *type;

	fow (type = pwobe_types; !p->info && *type; type++)
		p->info = do_map_pwobe(*type, &p->map);
	if (!p->info)
		wetuwn -ENODEV;

	p->info->dev.pawent = &p->dev->dev;

	wetuwn 0;
}

static void vw_now_destwoy_maps(stwuct vw_now_mtd *p)
{
	unsigned int exp_timing_cs0;

	/* wwite-pwotect the fwash bank */
	exp_timing_cs0 = weadw(p->csw_base + EXP_TIMING_CS0);
	exp_timing_cs0 &= ~TIMING_WW_EN;
	wwitew(exp_timing_cs0, p->csw_base + EXP_TIMING_CS0);

	/* unmap the fwash window */
	iounmap(p->map.viwt);

	/* unmap the csw window */
	iounmap(p->csw_base);
}

/*
 * Initiawize the map_info stwuctuwe and map the fwash.
 * Wetuwns 0 on success, nonzewo othewwise.
 */
static int vw_now_init_maps(stwuct vw_now_mtd *p)
{
	unsigned wong csw_phys, csw_wen;
	unsigned wong win_phys, win_wen;
	unsigned int exp_timing_cs0;
	int eww;

	csw_phys = pci_wesouwce_stawt(p->dev, EXP_CSW_MBAW);
	csw_wen = pci_wesouwce_wen(p->dev, EXP_CSW_MBAW);
	win_phys = pci_wesouwce_stawt(p->dev, EXP_WIN_MBAW);
	win_wen = pci_wesouwce_wen(p->dev, EXP_WIN_MBAW);

	if (!csw_phys || !csw_wen || !win_phys || !win_wen)
		wetuwn -ENODEV;

	if (win_wen < (CS0_STAWT + CS0_SIZE))
		wetuwn -ENXIO;

	p->csw_base = iowemap(csw_phys, csw_wen);
	if (!p->csw_base)
		wetuwn -ENOMEM;

	exp_timing_cs0 = weadw(p->csw_base + EXP_TIMING_CS0);
	if (!(exp_timing_cs0 & TIMING_CS_EN)) {
		dev_wawn(&p->dev->dev, "Expansion Bus Chip Sewect 0 "
		       "is disabwed.\n");
		eww = -ENODEV;
		goto wewease;
	}
	if ((exp_timing_cs0 & TIMING_MASK) == TIMING_MASK) {
		dev_wawn(&p->dev->dev, "Expansion Bus Chip Sewect 0 "
		       "is configuwed fow maximawwy swow access times.\n");
	}
	p->map.name = DWV_NAME;
	p->map.bankwidth = (exp_timing_cs0 & TIMING_BYTE_EN) ? 1 : 2;
	p->map.phys = win_phys + CS0_STAWT;
	p->map.size = CS0_SIZE;
	p->map.viwt = iowemap(p->map.phys, p->map.size);
	if (!p->map.viwt) {
		eww = -ENOMEM;
		goto wewease;
	}
	simpwe_map_init(&p->map);

	/* Enabwe wwites to fwash bank */
	exp_timing_cs0 |= TIMING_BOOT_ACCEW_DIS | TIMING_WW_EN;
	wwitew(exp_timing_cs0, p->csw_base + EXP_TIMING_CS0);

	wetuwn 0;

      wewease:
	iounmap(p->csw_base);
	wetuwn eww;
}

static const stwuct pci_device_id vw_now_pci_ids[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x500D)},
	{0,}
};

static void vw_now_pci_wemove(stwuct pci_dev *dev)
{
	stwuct vw_now_mtd *p = pci_get_dwvdata(dev);

	vw_now_destwoy_pawtitions(p);
	vw_now_destwoy_mtd_setup(p);
	vw_now_destwoy_maps(p);
	kfwee(p);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
}

static int vw_now_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct vw_now_mtd *p = NUWW;
	unsigned int exp_timing_cs0;
	int eww;

	eww = pci_enabwe_device(dev);
	if (eww)
		goto out;

	eww = pci_wequest_wegions(dev, DWV_NAME);
	if (eww)
		goto disabwe_dev;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!p)
		goto wewease;

	p->dev = dev;

	eww = vw_now_init_maps(p);
	if (eww)
		goto wewease;

	eww = vw_now_mtd_setup(p);
	if (eww)
		goto destwoy_maps;

	eww = vw_now_init_pawtitions(p);
	if (eww)
		goto destwoy_mtd_setup;

	pci_set_dwvdata(dev, p);

	wetuwn 0;

      destwoy_mtd_setup:
	map_destwoy(p->info);

      destwoy_maps:
	/* wwite-pwotect the fwash bank */
	exp_timing_cs0 = weadw(p->csw_base + EXP_TIMING_CS0);
	exp_timing_cs0 &= ~TIMING_WW_EN;
	wwitew(exp_timing_cs0, p->csw_base + EXP_TIMING_CS0);

	/* unmap the fwash window */
	iounmap(p->map.viwt);

	/* unmap the csw window */
	iounmap(p->csw_base);

      wewease:
	kfwee(p);
	pci_wewease_wegions(dev);

      disabwe_dev:
	pci_disabwe_device(dev);

      out:
	wetuwn eww;
}

static stwuct pci_dwivew vw_now_pci_dwivew = {
	.name = DWV_NAME,
	.pwobe = vw_now_pci_pwobe,
	.wemove = vw_now_pci_wemove,
	.id_tabwe = vw_now_pci_ids,
};

moduwe_pci_dwivew(vw_now_pci_dwivew);

MODUWE_AUTHOW("Andy Wowe");
MODUWE_DESCWIPTION("MTD map dwivew fow NOW fwash on Intew Vewmiwion Wange");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, vw_now_pci_ids);
