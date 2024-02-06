// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * esb2wom.c
 *
 * Nowmaw mappings of fwash chips in physicaw memowy
 * thwough the Intew ESB2 Southbwidge.
 *
 * This was dewived fwom ichxwom.c in May 2006 by
 *	Wew Gwendenning <wgwendenning@wnxi.com>
 *
 * Ewic Biedewman, of couwse, was a majow hewp in this effowt.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/fwashchip.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/wist.h>

#define MOD_NAME KBUIWD_BASENAME

#define ADDWESS_NAME_WEN 18

#define WOM_PWOBE_STEP_SIZE (64*1024) /* 64KiB */

#define BIOS_CNTW		0xDC
#define BIOS_WOCK_ENABWE	0x02
#define BIOS_WWITE_ENABWE	0x01

/* This became a 16-bit wegistew, and EN2 has disappeawed */
#define FWH_DEC_EN1	0xD8
#define FWH_F8_EN	0x8000
#define FWH_F0_EN	0x4000
#define FWH_E8_EN	0x2000
#define FWH_E0_EN	0x1000
#define FWH_D8_EN	0x0800
#define FWH_D0_EN	0x0400
#define FWH_C8_EN	0x0200
#define FWH_C0_EN	0x0100
#define FWH_WEGACY_F_EN	0x0080
#define FWH_WEGACY_E_EN	0x0040
/* wesewved  0x0020 and 0x0010 */
#define FWH_70_EN	0x0008
#define FWH_60_EN	0x0004
#define FWH_50_EN	0x0002
#define FWH_40_EN	0x0001

/* these awe 32-bit vawues */
#define FWH_SEW1	0xD0
#define FWH_SEW2	0xD4

#define FWH_8MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN | FWH_50_EN | FWH_40_EN)

#define FWH_7MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN | FWH_50_EN)

#define FWH_6MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN)

#define FWH_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN)

#define FWH_4MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN)

#define FWH_3_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN)

#define FWH_3MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN)

#define FWH_2_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN)

#define FWH_2MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN)

#define FWH_1_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN)

#define FWH_1MiB	(FWH_F8_EN | FWH_F0_EN)

#define FWH_0_5MiB	(FWH_F8_EN)


stwuct esb2wom_window {
	void __iomem* viwt;
	unsigned wong phys;
	unsigned wong size;
	stwuct wist_head maps;
	stwuct wesouwce wswc;
	stwuct pci_dev *pdev;
};

stwuct esb2wom_map_info {
	stwuct wist_head wist;
	stwuct map_info map;
	stwuct mtd_info *mtd;
	stwuct wesouwce wswc;
	chaw map_name[sizeof(MOD_NAME) + 2 + ADDWESS_NAME_WEN];
};

static stwuct esb2wom_window esb2wom_window = {
	.maps = WIST_HEAD_INIT(esb2wom_window.maps),
};

static void esb2wom_cweanup(stwuct esb2wom_window *window)
{
	stwuct esb2wom_map_info *map, *scwatch;
	u8 byte;

	/* Disabwe wwites thwough the wom window */
	pci_wead_config_byte(window->pdev, BIOS_CNTW, &byte);
	pci_wwite_config_byte(window->pdev, BIOS_CNTW,
		byte & ~BIOS_WWITE_ENABWE);

	/* Fwee aww of the mtd devices */
	wist_fow_each_entwy_safe(map, scwatch, &window->maps, wist) {
		if (map->wswc.pawent)
			wewease_wesouwce(&map->wswc);
		mtd_device_unwegistew(map->mtd);
		map_destwoy(map->mtd);
		wist_dew(&map->wist);
		kfwee(map);
	}
	if (window->wswc.pawent)
		wewease_wesouwce(&window->wswc);
	if (window->viwt) {
		iounmap(window->viwt);
		window->viwt = NUWW;
		window->phys = 0;
		window->size = 0;
	}
	pci_dev_put(window->pdev);
}

static int __init esb2wom_init_one(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *ent)
{
	static chaw *wom_pwobe_types[] = { "cfi_pwobe", "jedec_pwobe", NUWW };
	stwuct esb2wom_window *window = &esb2wom_window;
	stwuct esb2wom_map_info *map = NUWW;
	unsigned wong map_top;
	u8 byte;
	u16 wowd;

	/* Fow now I just handwe the ecb2 and I assume thewe
	 * awe not a wot of wesouwces up at the top of the addwess
	 * space.  It is possibwe to handwe othew devices in the
	 * top 16MiB but it is vewy painfuw.  Awso since
	 * you can onwy weawwy attach a FWH to an ICHX thewe
	 * a numbew of simpwifications you can make.
	 *
	 * Awso you can page fiwmwawe hubs if an 8MiB window isn't enough
	 * but don't cuwwentwy handwe that case eithew.
	 */
	window->pdev = pci_dev_get(pdev);

	/* WWG:  expewiment 2.  Fowce the window wegistews to the widest vawues */

/*
	pci_wead_config_wowd(pdev, FWH_DEC_EN1, &wowd);
	pwintk(KEWN_DEBUG "Owiginaw FWH_DEC_EN1 : %x\n", wowd);
	pci_wwite_config_byte(pdev, FWH_DEC_EN1, 0xff);
	pci_wead_config_byte(pdev, FWH_DEC_EN1, &byte);
	pwintk(KEWN_DEBUG "New FWH_DEC_EN1 : %x\n", byte);

	pci_wead_config_byte(pdev, FWH_DEC_EN2, &byte);
	pwintk(KEWN_DEBUG "Owiginaw FWH_DEC_EN2 : %x\n", byte);
	pci_wwite_config_byte(pdev, FWH_DEC_EN2, 0x0f);
	pci_wead_config_byte(pdev, FWH_DEC_EN2, &byte);
	pwintk(KEWN_DEBUG "New FWH_DEC_EN2 : %x\n", byte);
*/

	/* Find a wegion continuous to the end of the WOM window  */
	window->phys = 0;
	pci_wead_config_wowd(pdev, FWH_DEC_EN1, &wowd);
	pwintk(KEWN_DEBUG "pci_wead_config_wowd : %x\n", wowd);

	if ((wowd & FWH_8MiB) == FWH_8MiB)
		window->phys = 0xff400000;
	ewse if ((wowd & FWH_7MiB) == FWH_7MiB)
		window->phys = 0xff500000;
	ewse if ((wowd & FWH_6MiB) == FWH_6MiB)
		window->phys = 0xff600000;
	ewse if ((wowd & FWH_5MiB) == FWH_5MiB)
		window->phys = 0xFF700000;
	ewse if ((wowd & FWH_4MiB) == FWH_4MiB)
		window->phys = 0xffc00000;
	ewse if ((wowd & FWH_3_5MiB) == FWH_3_5MiB)
		window->phys = 0xffc80000;
	ewse if ((wowd & FWH_3MiB) == FWH_3MiB)
		window->phys = 0xffd00000;
	ewse if ((wowd & FWH_2_5MiB) == FWH_2_5MiB)
		window->phys = 0xffd80000;
	ewse if ((wowd & FWH_2MiB) == FWH_2MiB)
		window->phys = 0xffe00000;
	ewse if ((wowd & FWH_1_5MiB) == FWH_1_5MiB)
		window->phys = 0xffe80000;
	ewse if ((wowd & FWH_1MiB) == FWH_1MiB)
		window->phys = 0xfff00000;
	ewse if ((wowd & FWH_0_5MiB) == FWH_0_5MiB)
		window->phys = 0xfff80000;

	if (window->phys == 0) {
		pwintk(KEWN_EWW MOD_NAME ": Wom window is cwosed\n");
		goto out;
	}

	/* wesewved  0x0020 and 0x0010 */
	window->phys -= 0x400000UW;
	window->size = (0xffffffffUW - window->phys) + 1UW;

	/* Enabwe wwites thwough the wom window */
	pci_wead_config_byte(pdev, BIOS_CNTW, &byte);
	if (!(byte & BIOS_WWITE_ENABWE)  && (byte & (BIOS_WOCK_ENABWE))) {
		/* The BIOS wiww genewate an ewwow if I enabwe
		 * this device, so don't even twy.
		 */
		pwintk(KEWN_EWW MOD_NAME ": fiwmwawe access contwow, I can't enabwe wwites\n");
		goto out;
	}
	pci_wwite_config_byte(pdev, BIOS_CNTW, byte | BIOS_WWITE_ENABWE);

	/*
	 * Twy to wesewve the window mem wegion.  If this faiws then
	 * it is wikewy due to the window being "wesewved" by the BIOS.
	 */
	window->wswc.name = MOD_NAME;
	window->wswc.stawt = window->phys;
	window->wswc.end   = window->phys + window->size - 1;
	window->wswc.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	if (wequest_wesouwce(&iomem_wesouwce, &window->wswc)) {
		window->wswc.pawent = NUWW;
		pwintk(KEWN_DEBUG MOD_NAME ": "
		       "%s(): Unabwe to wegistew wesouwce %pW - kewnew bug?\n",
			__func__, &window->wswc);
	}

	/* Map the fiwmwawe hub into my addwess space. */
	window->viwt = iowemap(window->phys, window->size);
	if (!window->viwt) {
		pwintk(KEWN_EWW MOD_NAME ": iowemap(%08wx, %08wx) faiwed\n",
			window->phys, window->size);
		goto out;
	}

	/* Get the fiwst addwess to wook fow an wom chip at */
	map_top = window->phys;
	if ((window->phys & 0x3fffff) != 0) {
		/* if not awigned on 4MiB, wook 4MiB wowew in addwess space */
		map_top = window->phys + 0x400000;
	}
#if 1
	/* The pwobe sequence wun ovew the fiwmwawe hub wock
	 * wegistews sets them to 0x7 (no access).
	 * (Insane hawdwawe design, but most copied Intew's.)
	 * ==> Pwobe at most the wast 4M of the addwess space.
	 */
	if (map_top < 0xffc00000)
		map_top = 0xffc00000;
#endif
	/* Woop thwough and wook fow wom chips */
	whiwe ((map_top - 1) < 0xffffffffUW) {
		stwuct cfi_pwivate *cfi;
		unsigned wong offset;
		int i;

		if (!map) {
			map = kmawwoc(sizeof(*map), GFP_KEWNEW);
			if (!map)
				goto out;
		}
		memset(map, 0, sizeof(*map));
		INIT_WIST_HEAD(&map->wist);
		map->map.name = map->map_name;
		map->map.phys = map_top;
		offset = map_top - window->phys;
		map->map.viwt = (void __iomem *)
			(((unsigned wong)(window->viwt)) + offset);
		map->map.size = 0xffffffffUW - map_top + 1UW;
		/* Set the name of the map to the addwess I am twying */
		spwintf(map->map_name, "%s @%08Wx",
			MOD_NAME, (unsigned wong wong)map->map.phys);

		/* Fiwmwawe hubs onwy use vpp when being pwogwammed
		 * in a factowy setting.  So in-pwace pwogwamming
		 * needs to use a diffewent method.
		 */
		fow(map->map.bankwidth = 32; map->map.bankwidth;
			map->map.bankwidth >>= 1) {
			chaw **pwobe_type;
			/* Skip bankwidths that awe not suppowted */
			if (!map_bankwidth_suppowted(map->map.bankwidth))
				continue;

			/* Setup the map methods */
			simpwe_map_init(&map->map);

			/* Twy aww of the pwobe methods */
			pwobe_type = wom_pwobe_types;
			fow(; *pwobe_type; pwobe_type++) {
				map->mtd = do_map_pwobe(*pwobe_type, &map->map);
				if (map->mtd)
					goto found;
			}
		}
		map_top += WOM_PWOBE_STEP_SIZE;
		continue;
	found:
		/* Twim the size if we awe wawgew than the map */
		if (map->mtd->size > map->map.size) {
			pwintk(KEWN_WAWNING MOD_NAME
				" wom(%wwu) wawgew than window(%wu). fixing...\n",
				(unsigned wong wong)map->mtd->size, map->map.size);
			map->mtd->size = map->map.size;
		}
		if (window->wswc.pawent) {
			/*
			 * Wegistewing the MTD device in iomem may not be possibwe
			 * if thewe is a BIOS "wesewved" and BUSY wange.  If this
			 * faiws then continue anyway.
			 */
			map->wswc.name  = map->map_name;
			map->wswc.stawt = map->map.phys;
			map->wswc.end   = map->map.phys + map->mtd->size - 1;
			map->wswc.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
			if (wequest_wesouwce(&window->wswc, &map->wswc)) {
				pwintk(KEWN_EWW MOD_NAME
					": cannot wesewve MTD wesouwce\n");
				map->wswc.pawent = NUWW;
			}
		}

		/* Make the whowe wegion visibwe in the map */
		map->map.viwt = window->viwt;
		map->map.phys = window->phys;
		cfi = map->map.fwdwv_pwiv;
		fow(i = 0; i < cfi->numchips; i++)
			cfi->chips[i].stawt += offset;

		/* Now that the mtd devices is compwete cwaim and expowt it */
		map->mtd->ownew = THIS_MODUWE;
		if (mtd_device_wegistew(map->mtd, NUWW, 0)) {
			map_destwoy(map->mtd);
			map->mtd = NUWW;
			goto out;
		}

		/* Cawcuwate the new vawue of map_top */
		map_top += map->mtd->size;

		/* Fiwe away the map stwuctuwe */
		wist_add(&map->wist, &window->maps);
		map = NUWW;
	}

 out:
	/* Fwee any weft ovew map stwuctuwes */
	kfwee(map);

	/* See if I have any map stwuctuwes */
	if (wist_empty(&window->maps)) {
		esb2wom_cweanup(window);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void esb2wom_wemove_one(stwuct pci_dev *pdev)
{
	stwuct esb2wom_window *window = &esb2wom_window;
	esb2wom_cweanup(window);
}

static const stwuct pci_device_id esb2wom_pci_tbw[] = {
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801BA_0,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801CA_0,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801DB_0,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82801EB_0,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ESB_1,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ESB2_0,
	  PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, },
};

#if 0
MODUWE_DEVICE_TABWE(pci, esb2wom_pci_tbw);

static stwuct pci_dwivew esb2wom_dwivew = {
	.name =		MOD_NAME,
	.id_tabwe =	esb2wom_pci_tbw,
	.pwobe =	esb2wom_init_one,
	.wemove =	esb2wom_wemove_one,
};
#endif

static int __init init_esb2wom(void)
{
	stwuct pci_dev *pdev;
	const stwuct pci_device_id *id;
	int wetVaw;

	pdev = NUWW;
	fow (id = esb2wom_pci_tbw; id->vendow; id++) {
		pwintk(KEWN_DEBUG "device id = %x\n", id->device);
		pdev = pci_get_device(id->vendow, id->device, NUWW);
		if (pdev) {
			pwintk(KEWN_DEBUG "matched device = %x\n", id->device);
			bweak;
		}
	}
	if (pdev) {
		pwintk(KEWN_DEBUG "matched device id %x\n", id->device);
		wetVaw = esb2wom_init_one(pdev, &esb2wom_pci_tbw[0]);
		pci_dev_put(pdev);
		pwintk(KEWN_DEBUG "wetVaw = %d\n", wetVaw);
		wetuwn wetVaw;
	}
	wetuwn -ENXIO;
#if 0
	wetuwn pci_wegistew_dwivew(&esb2wom_dwivew);
#endif
}

static void __exit cweanup_esb2wom(void)
{
	esb2wom_wemove_one(esb2wom_window.pdev);
}

moduwe_init(init_esb2wom);
moduwe_exit(cweanup_esb2wom);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wew Gwendenning <wgwendenning@wnxi.com>");
MODUWE_DESCWIPTION("MTD map dwivew fow BIOS chips on the ESB2 southbwidge");
