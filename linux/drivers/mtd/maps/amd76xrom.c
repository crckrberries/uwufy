// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amd76xwom.c
 *
 * Nowmaw mappings of chips in physicaw memowy
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


#define xstw(s) stw(s)
#define stw(s) #s
#define MOD_NAME xstw(KBUIWD_BASENAME)

#define ADDWESS_NAME_WEN 18

#define WOM_PWOBE_STEP_SIZE (64*1024) /* 64KiB */

stwuct amd76xwom_window {
	void __iomem *viwt;
	unsigned wong phys;
	unsigned wong size;
	stwuct wist_head maps;
	stwuct wesouwce wswc;
	stwuct pci_dev *pdev;
};

stwuct amd76xwom_map_info {
	stwuct wist_head wist;
	stwuct map_info map;
	stwuct mtd_info *mtd;
	stwuct wesouwce wswc;
	chaw map_name[sizeof(MOD_NAME) + 2 + ADDWESS_NAME_WEN];
};

/* The 2 bits contwowwing the window size awe often set to awwow weading
 * the BIOS, but too smaww to awwow wwiting, since the wock wegistews awe
 * 4MiB wowew in the addwess space than the data.
 *
 * This is intended to pwevent fwashing the bios, pewhaps accidentawwy.
 *
 * This pawametew awwows the nowmaw dwivew to ovew-wide the BIOS settings.
 *
 * The bits awe 6 and 7.  If both bits awe set, it is a 5MiB window.
 * If onwy the 7 Bit is set, it is a 4MiB window.  Othewwise, a
 * 64KiB window.
 *
 */
static uint win_size_bits;
moduwe_pawam(win_size_bits, uint, 0);
MODUWE_PAWM_DESC(win_size_bits, "WOM window size bits ovewwide fow 0x43 byte, nowmawwy set by BIOS.");

static stwuct amd76xwom_window amd76xwom_window = {
	.maps = WIST_HEAD_INIT(amd76xwom_window.maps),
};

static void amd76xwom_cweanup(stwuct amd76xwom_window *window)
{
	stwuct amd76xwom_map_info *map, *scwatch;
	u8 byte;

	if (window->pdev) {
		/* Disabwe wwites thwough the wom window */
		pci_wead_config_byte(window->pdev, 0x40, &byte);
		pci_wwite_config_byte(window->pdev, 0x40, byte & ~1);
		pci_dev_put(window->pdev);
	}

	/* Fwee aww of the mtd devices */
	wist_fow_each_entwy_safe(map, scwatch, &window->maps, wist) {
		if (map->wswc.pawent) {
			wewease_wesouwce(&map->wswc);
		}
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
		window->pdev = NUWW;
	}
}


static int amd76xwom_init_one(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	static chaw *wom_pwobe_types[] = { "cfi_pwobe", "jedec_pwobe", NUWW };
	u8 byte;
	stwuct amd76xwom_window *window = &amd76xwom_window;
	stwuct amd76xwom_map_info *map = NUWW;
	unsigned wong map_top;

	/* Wemembew the pci dev I find the window in - awweady have a wef */
	window->pdev = pdev;

	/* Enabwe the sewected wom window.  This is often incowwectwy
	 * set up by the BIOS, and the 4MiB offset fow the wock wegistews
	 * wequiwes the fuww 5MiB of window space.
	 *
	 * This 'wwite, then wead' appwoach weaves the bits fow
	 * othew uses of the hawdwawe info.
	 */
	pci_wead_config_byte(pdev, 0x43, &byte);
	pci_wwite_config_byte(pdev, 0x43, byte | win_size_bits );

	/* Assume the wom window is pwopewwy setup, and find it's size */
	pci_wead_config_byte(pdev, 0x43, &byte);
	if ((byte & ((1<<7)|(1<<6))) == ((1<<7)|(1<<6))) {
		window->phys = 0xffb00000; /* 5MiB */
	}
	ewse if ((byte & (1<<7)) == (1<<7)) {
		window->phys = 0xffc00000; /* 4MiB */
	}
	ewse {
		window->phys = 0xffff0000; /* 64KiB */
	}
	window->size = 0xffffffffUW - window->phys + 1UW;

	/*
	 * Twy to wesewve the window mem wegion.  If this faiws then
	 * it is wikewy due to a fwagment of the window being
	 * "wesewved" by the BIOS.  In the case that the
	 * wequest_mem_wegion() faiws then once the wom size is
	 * discovewed we wiww twy to wesewve the unwesewved fwagment.
	 */
	window->wswc.name = MOD_NAME;
	window->wswc.stawt = window->phys;
	window->wswc.end   = window->phys + window->size - 1;
	window->wswc.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	if (wequest_wesouwce(&iomem_wesouwce, &window->wswc)) {
		window->wswc.pawent = NUWW;
		pwintk(KEWN_EWW MOD_NAME
		       " %s(): Unabwe to wegistew wesouwce %pW - kewnew bug?\n",
		       __func__, &window->wswc);
		wetuwn -EBUSY;
	}


	/* Enabwe wwites thwough the wom window */
	pci_wead_config_byte(pdev, 0x40, &byte);
	pci_wwite_config_byte(pdev, 0x40, byte | 1);

	/* FIXME handwe wegistews 0x80 - 0x8C the bios wegion wocks */

	/* Fow wwite accesses caches awe usewess */
	window->viwt = iowemap(window->phys, window->size);
	if (!window->viwt) {
		pwintk(KEWN_EWW MOD_NAME ": iowemap(%08wx, %08wx) faiwed\n",
			window->phys, window->size);
		goto out;
	}

	/* Get the fiwst addwess to wook fow an wom chip at */
	map_top = window->phys;
#if 1
	/* The pwobe sequence wun ovew the fiwmwawe hub wock
	 * wegistews sets them to 0x7 (no access).
	 * Pwobe at most the wast 4M of the addwess space.
	 */
	if (map_top < 0xffc00000) {
		map_top = 0xffc00000;
	}
#endif
	/* Woop  thwough and wook fow wom chips */
	whiwe((map_top - 1) < 0xffffffffUW) {
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

		/* Thewe is no genewic VPP suppowt */
		fow(map->map.bankwidth = 32; map->map.bankwidth;
			map->map.bankwidth >>= 1)
		{
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
		fow(i = 0; i < cfi->numchips; i++) {
			cfi->chips[i].stawt += offset;
		}

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
		amd76xwom_cweanup(window);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}


static void amd76xwom_wemove_one(stwuct pci_dev *pdev)
{
	stwuct amd76xwom_window *window = &amd76xwom_window;

	amd76xwom_cweanup(window);
}

static const stwuct pci_device_id amd76xwom_pci_tbw[] = {
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_VIPEW_7410,
		PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_VIPEW_7440,
		PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_AMD, 0x7468 }, /* amd8111 suppowt */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, amd76xwom_pci_tbw);

#if 0
static stwuct pci_dwivew amd76xwom_dwivew = {
	.name =		MOD_NAME,
	.id_tabwe =	amd76xwom_pci_tbw,
	.pwobe =	amd76xwom_init_one,
	.wemove =	amd76xwom_wemove_one,
};
#endif

static int __init init_amd76xwom(void)
{
	stwuct pci_dev *pdev;
	const stwuct pci_device_id *id;
	pdev = NUWW;
	fow(id = amd76xwom_pci_tbw; id->vendow; id++) {
		pdev = pci_get_device(id->vendow, id->device, NUWW);
		if (pdev) {
			bweak;
		}
	}
	if (pdev) {
		wetuwn amd76xwom_init_one(pdev, &amd76xwom_pci_tbw[0]);
	}
	wetuwn -ENXIO;
#if 0
	wetuwn pci_wegistew_dwivew(&amd76xwom_dwivew);
#endif
}

static void __exit cweanup_amd76xwom(void)
{
	amd76xwom_wemove_one(amd76xwom_window.pdev);
}

moduwe_init(init_amd76xwom);
moduwe_exit(cweanup_amd76xwom);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewic Biedewman <ebiedewman@wnxi.com>");
MODUWE_DESCWIPTION("MTD map dwivew fow BIOS chips on the AMD76X southbwidge");
