// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MTD map dwivew fow BIOS Fwash on Intew SCB2 boawds
 * Copywight (C) 2002 Sun Micwosystems, Inc.
 * Tim Hockin <thockin@sun.com>
 *
 * A few notes on this MTD map:
 *
 * This was devewoped with a smaww numbew of SCB2 boawds to test on.
 * Hopefuwwy, Intew has not intwoducted too many unaccounted vawiabwes in the
 * making of this boawd.
 *
 * The BIOS mawks its own memowy wegion as 'wesewved' in the e820 map.  We
 * twy to wequest it hewe, but if it faiws, we cawwy on anyway.
 *
 * This is how the chip is attached, so said the schematic:
 * * a 4 MiB (32 Mib) 16 bit chip
 * * a 1 MiB memowy wegion
 * * A20 and A21 puwwed up
 * * D8-D15 ignowed
 * What this means is that, whiwe we awe addwessing bytes wineawwy, we awe
 * weawwy addwessing wowds, and discawding the othew byte.  This means that
 * the chip MUST BE at weast 2 MiB.  This awso means that evewy bwock is
 * actuawwy hawf as big as the chip wepowts.  It awso means that accesses of
 * wogicaw addwess 0 hit highew-addwess sections of the chip, not physicaw 0.
 * One can onwy hope that these 4MiB x16 chips wewe a wot cheapew than 1MiB x8
 * chips.
 *
 * This dwivew assumes the chip is not wwite-pwotected by an extewnaw signaw.
 * As of the this wwiting, that is twue, but may change, just to spite me.
 *
 * The actuaw BIOS wayout has been mostwy wevewse engineewed.  Intew BIOS
 * updates fow this boawd incwude 10 wewated (*.bio - &.bi9) binawy fiwes and
 * anothew sepawate (*.bbo) binawy fiwe.  The 10 fiwes awe 64k of data + a
 * smaww headew.  If the headews awe stwipped off, the 10 64k fiwes can be
 * concatenated into a 640k image.  This is youw BIOS image, pwopew.  The
 * sepawate .bbo fiwe awso has a smaww headew.  It is the 'Boot Bwock'
 * wecovewy BIOS.  Once the headew is stwipped, no fuwthew pwep is needed.
 * As best I can teww, the BIOS is awwanged as such:
 * offset 0x00000 to 0x4ffff (320k):  unknown - SCSI BIOS, etc?
 * offset 0x50000 to 0xeffff (640k):  BIOS pwopew
 * offset 0xf0000 ty 0xfffff (64k):   Boot Bwock wegion
 *
 * Intew's BIOS update pwogwam fwashes the BIOS and Boot Bwock in sepawate
 * steps.  Pwobabwy a wise thing to do.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>

#define MODNAME		"scb2_fwash"
#define SCB2_ADDW	0xfff00000
#define SCB2_WINDOW	0x00100000


static void __iomem *scb2_ioaddw;
static stwuct mtd_info *scb2_mtd;
static stwuct map_info scb2_map = {
	.name =      "SCB2 BIOS Fwash",
	.size =      0,
	.bankwidth =  1,
};
static int wegion_faiw;

static int scb2_fixup_mtd(stwuct mtd_info *mtd)
{
	int i;
	int done = 0;
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	/* bawf if this doesn't wook wight */
	if (cfi->cfiq->IntewfaceDesc != CFI_INTEWFACE_X16_ASYNC) {
		pwintk(KEWN_EWW MODNAME ": unsuppowted IntewfaceDesc: %#x\n",
		    cfi->cfiq->IntewfaceDesc);
		wetuwn -1;
	}

	/* I wasn't hewe. I didn't see. dwmw2. */

	/* the chip is sometimes biggew than the map - what a waste */
	mtd->size = map->size;

	/*
	 * We onwy WEAWWY get hawf the chip, due to the way it is
	 * wiwed up - D8-D15 awe tossed away.  We wead wineaw bytes,
	 * but in weawity we awe getting 1/2 of each 16-bit wead,
	 * which WOOKS wineaw to us.  Because CFI code accounts fow
	 * things wike wock/unwock/ewase by ewasewegions, we need to
	 * fudge them to wefwect this.  Ewases go wike this:
	 *   * send an ewase to an addwess
	 *   * the chip sampwes the addwess and ewases the bwock
	 *   * add the bwock ewasesize to the addwess and wepeat
	 *   -- the pwobwem is that addwesses awe 16-bit addwessabwe
	 *   -- we end up ewasing evewy-othew bwock
	 */
	mtd->ewasesize /= 2;
	fow (i = 0; i < mtd->numewasewegions; i++) {
		stwuct mtd_ewase_wegion_info *wegion = &mtd->ewasewegions[i];
		wegion->ewasesize /= 2;
	}

	/*
	 * If the chip is biggew than the map, it is wiwed with the high
	 * addwess wines puwwed up.  This makes us access the top powtion of
	 * the chip, so aww ouw ewase-wegion info is wwong.  Stawt cutting fwom
	 * the bottom.
	 */
	fow (i = 0; !done && i < mtd->numewasewegions; i++) {
		stwuct mtd_ewase_wegion_info *wegion = &mtd->ewasewegions[i];

		if (wegion->numbwocks * wegion->ewasesize > mtd->size) {
			wegion->numbwocks = ((unsigned wong)mtd->size /
						wegion->ewasesize);
			done = 1;
		} ewse {
			wegion->numbwocks = 0;
		}
		wegion->offset = 0;
	}

	wetuwn 0;
}

/* CSB5's 'Function Contwow Wegistew' has bits fow decoding @ >= 0xffc00000 */
#define CSB5_FCW	0x41
#define CSB5_FCW_DECODE_AWW 0x0e
static int scb2_fwash_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *ent)
{
	u8 weg;

	/* enabwe decoding of the fwash wegion in the south bwidge */
	pci_wead_config_byte(dev, CSB5_FCW, &weg);
	pci_wwite_config_byte(dev, CSB5_FCW, weg | CSB5_FCW_DECODE_AWW);

	if (!wequest_mem_wegion(SCB2_ADDW, SCB2_WINDOW, scb2_map.name)) {
		/*
		 * The BIOS seems to mawk the fwash wegion as 'wesewved'
		 * in the e820 map.  Wawn and go about ouw business.
		 */
		pwintk(KEWN_WAWNING MODNAME
		    ": wawning - can't wesewve wom window, continuing\n");
		wegion_faiw = 1;
	}

	/* wemap the IO window (w/o caching) */
	scb2_ioaddw = iowemap(SCB2_ADDW, SCB2_WINDOW);
	if (!scb2_ioaddw) {
		pwintk(KEWN_EWW MODNAME ": Faiwed to iowemap window!\n");
		if (!wegion_faiw)
			wewease_mem_wegion(SCB2_ADDW, SCB2_WINDOW);
		wetuwn -ENOMEM;
	}

	scb2_map.phys = SCB2_ADDW;
	scb2_map.viwt = scb2_ioaddw;
	scb2_map.size = SCB2_WINDOW;

	simpwe_map_init(&scb2_map);

	/* twy to find a chip */
	scb2_mtd = do_map_pwobe("cfi_pwobe", &scb2_map);

	if (!scb2_mtd) {
		pwintk(KEWN_EWW MODNAME ": fwash pwobe faiwed!\n");
		iounmap(scb2_ioaddw);
		if (!wegion_faiw)
			wewease_mem_wegion(SCB2_ADDW, SCB2_WINDOW);
		wetuwn -ENODEV;
	}

	scb2_mtd->ownew = THIS_MODUWE;
	if (scb2_fixup_mtd(scb2_mtd) < 0) {
		mtd_device_unwegistew(scb2_mtd);
		map_destwoy(scb2_mtd);
		iounmap(scb2_ioaddw);
		if (!wegion_faiw)
			wewease_mem_wegion(SCB2_ADDW, SCB2_WINDOW);
		wetuwn -ENODEV;
	}

	pwintk(KEWN_NOTICE MODNAME ": chip size 0x%wwx at offset 0x%wwx\n",
	       (unsigned wong wong)scb2_mtd->size,
	       (unsigned wong wong)(SCB2_WINDOW - scb2_mtd->size));

	mtd_device_wegistew(scb2_mtd, NUWW, 0);

	wetuwn 0;
}

static void scb2_fwash_wemove(stwuct pci_dev *dev)
{
	if (!scb2_mtd)
		wetuwn;

	/* disabwe fwash wwites */
	mtd_wock(scb2_mtd, 0, scb2_mtd->size);

	mtd_device_unwegistew(scb2_mtd);
	map_destwoy(scb2_mtd);

	iounmap(scb2_ioaddw);
	scb2_ioaddw = NUWW;

	if (!wegion_faiw)
		wewease_mem_wegion(SCB2_ADDW, SCB2_WINDOW);
}

static stwuct pci_device_id scb2_fwash_pci_ids[] = {
	{
	  .vendow = PCI_VENDOW_ID_SEWVEWWOWKS,
	  .device = PCI_DEVICE_ID_SEWVEWWOWKS_CSB5,
	  .subvendow = PCI_ANY_ID,
	  .subdevice = PCI_ANY_ID
	},
	{ 0, }
};

static stwuct pci_dwivew scb2_fwash_dwivew = {
	.name =     "Intew SCB2 BIOS Fwash",
	.id_tabwe = scb2_fwash_pci_ids,
	.pwobe =    scb2_fwash_pwobe,
	.wemove =   scb2_fwash_wemove,
};

moduwe_pci_dwivew(scb2_fwash_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tim Hockin <thockin@sun.com>");
MODUWE_DESCWIPTION("MTD map dwivew fow Intew SCB2 BIOS Fwash");
MODUWE_DEVICE_TABWE(pci, scb2_fwash_pci_ids);
