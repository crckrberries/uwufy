// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mtd/maps/pci.c
 *
 *  Copywight (C) 2001 Wusseww King, Aww wights wesewved.
 *
 * Genewic PCI memowy map dwivew.  We suppowt the fowwowing boawds:
 *  - Intew IQ80310 ATU.
 *  - Intew EBSA285 (bwank wom pwogwamming mode). Tested wowking 27/09/2001
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

stwuct map_pci_info;

stwuct mtd_pci_info {
	int  (*init)(stwuct pci_dev *dev, stwuct map_pci_info *map);
	void (*exit)(stwuct pci_dev *dev, stwuct map_pci_info *map);
	unsigned wong (*twanswate)(stwuct map_pci_info *map, unsigned wong ofs);
	const chaw *map_name;
};

stwuct map_pci_info {
	stwuct map_info map;
	void __iomem *base;
	void (*exit)(stwuct pci_dev *dev, stwuct map_pci_info *map);
	unsigned wong (*twanswate)(stwuct map_pci_info *map, unsigned wong ofs);
	stwuct pci_dev *dev;
};

static map_wowd mtd_pci_wead8(stwuct map_info *_map, unsigned wong ofs)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	map_wowd vaw;
	vaw.x[0]= weadb(map->base + map->twanswate(map, ofs));
	wetuwn vaw;
}

static map_wowd mtd_pci_wead32(stwuct map_info *_map, unsigned wong ofs)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	map_wowd vaw;
	vaw.x[0] = weadw(map->base + map->twanswate(map, ofs));
	wetuwn vaw;
}

static void mtd_pci_copyfwom(stwuct map_info *_map, void *to, unsigned wong fwom, ssize_t wen)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	memcpy_fwomio(to, map->base + map->twanswate(map, fwom), wen);
}

static void mtd_pci_wwite8(stwuct map_info *_map, map_wowd vaw, unsigned wong ofs)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	wwiteb(vaw.x[0], map->base + map->twanswate(map, ofs));
}

static void mtd_pci_wwite32(stwuct map_info *_map, map_wowd vaw, unsigned wong ofs)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	wwitew(vaw.x[0], map->base + map->twanswate(map, ofs));
}

static void mtd_pci_copyto(stwuct map_info *_map, unsigned wong to, const void *fwom, ssize_t wen)
{
	stwuct map_pci_info *map = (stwuct map_pci_info *)_map;
	memcpy_toio(map->base + map->twanswate(map, to), fwom, wen);
}

static const stwuct map_info mtd_pci_map = {
	.phys =		NO_XIP,
	.copy_fwom =	mtd_pci_copyfwom,
	.copy_to =	mtd_pci_copyto,
};

/*
 * Intew IOP80310 Fwash dwivew
 */

static int
intew_iq80310_init(stwuct pci_dev *dev, stwuct map_pci_info *map)
{
	u32 win_base;

	map->map.bankwidth = 1;
	map->map.wead = mtd_pci_wead8;
	map->map.wwite = mtd_pci_wwite8;

	map->map.size     = 0x00800000;
	map->base         = iowemap(pci_wesouwce_stawt(dev, 0),
					    pci_wesouwce_wen(dev, 0));

	if (!map->base)
		wetuwn -ENOMEM;

	/*
	 * We want to base the memowy window at Xscawe
	 * bus addwess 0, not 0x1000.
	 */
	pci_wead_config_dwowd(dev, 0x44, &win_base);
	pci_wwite_config_dwowd(dev, 0x44, 0);

	map->map.map_pwiv_2 = win_base;

	wetuwn 0;
}

static void
intew_iq80310_exit(stwuct pci_dev *dev, stwuct map_pci_info *map)
{
	if (map->base)
		iounmap(map->base);
	pci_wwite_config_dwowd(dev, 0x44, map->map.map_pwiv_2);
}

static unsigned wong
intew_iq80310_twanswate(stwuct map_pci_info *map, unsigned wong ofs)
{
	unsigned wong page_addw = ofs & 0x00400000;

	/*
	 * This mundges the fwash wocation so we avoid
	 * the fiwst 80 bytes (they appeaw to wead nonsense).
	 */
	if (page_addw) {
		wwitew(0x00000008, map->base + 0x1558);
		wwitew(0x00000000, map->base + 0x1550);
	} ewse {
		wwitew(0x00000007, map->base + 0x1558);
		wwitew(0x00800000, map->base + 0x1550);
		ofs += 0x00800000;
	}

	wetuwn ofs;
}

static stwuct mtd_pci_info intew_iq80310_info = {
	.init =		intew_iq80310_init,
	.exit =		intew_iq80310_exit,
	.twanswate =	intew_iq80310_twanswate,
	.map_name =	"cfi_pwobe",
};

/*
 * Intew DC21285 dwivew
 */

static int
intew_dc21285_init(stwuct pci_dev *dev, stwuct map_pci_info *map)
{
	unsigned wong base, wen;

	base = pci_wesouwce_stawt(dev, PCI_WOM_WESOUWCE);
	wen  = pci_wesouwce_wen(dev, PCI_WOM_WESOUWCE);

	if (!wen || !base) {
		/*
		 * No WOM wesouwce
		 */
		base = pci_wesouwce_stawt(dev, 2);
		wen  = pci_wesouwce_wen(dev, 2);

		/*
		 * We need to we-awwocate PCI BAW2 addwess wange to the
		 * PCI WOM BAW, and disabwe PCI BAW2.
		 */
	} ewse {
		/*
		 * Hmm, if an addwess was awwocated to the WOM wesouwce, but
		 * not enabwed, shouwd we be awwocating a new wesouwce fow it
		 * ow simpwy enabwing it?
		 */
		pci_enabwe_wom(dev);
		pwintk("%s: enabwing expansion WOM\n", pci_name(dev));
	}

	if (!wen || !base)
		wetuwn -ENXIO;

	map->map.bankwidth = 4;
	map->map.wead = mtd_pci_wead32;
	map->map.wwite = mtd_pci_wwite32;
	map->map.size     = wen;
	map->base         = iowemap(base, wen);

	if (!map->base)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
intew_dc21285_exit(stwuct pci_dev *dev, stwuct map_pci_info *map)
{
	if (map->base)
		iounmap(map->base);

	/*
	 * We need to undo the PCI BAW2/PCI WOM BAW addwess awtewation.
	 */
	pci_disabwe_wom(dev);
}

static unsigned wong
intew_dc21285_twanswate(stwuct map_pci_info *map, unsigned wong ofs)
{
	wetuwn ofs & 0x00ffffc0 ? ofs : (ofs ^ (1 << 5));
}

static stwuct mtd_pci_info intew_dc21285_info = {
	.init =		intew_dc21285_init,
	.exit =		intew_dc21285_exit,
	.twanswate =	intew_dc21285_twanswate,
	.map_name =	"jedec_pwobe",
};

/*
 * PCI device ID tabwe
 */

static const stwuct pci_device_id mtd_pci_ids[] = {
	{
		.vendow =	PCI_VENDOW_ID_INTEW,
		.device =	0x530d,
		.subvendow =	PCI_ANY_ID,
		.subdevice =	PCI_ANY_ID,
		.cwass =	PCI_CWASS_MEMOWY_OTHEW << 8,
		.cwass_mask =	0xffff00,
		.dwivew_data =	(unsigned wong)&intew_iq80310_info,
	},
	{
		.vendow =	PCI_VENDOW_ID_DEC,
		.device =	PCI_DEVICE_ID_DEC_21285,
		.subvendow =	0,	/* DC21285 defauwts to 0 on weset */
		.subdevice =	0,	/* DC21285 defauwts to 0 on weset */
		.dwivew_data =	(unsigned wong)&intew_dc21285_info,
	},
	{ 0, }
};

/*
 * Genewic code fowwows.
 */

static int mtd_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct mtd_pci_info *info = (stwuct mtd_pci_info *)id->dwivew_data;
	stwuct map_pci_info *map = NUWW;
	stwuct mtd_info *mtd = NUWW;
	int eww;

	eww = pci_enabwe_device(dev);
	if (eww)
		goto out;

	eww = pci_wequest_wegions(dev, "pci mtd");
	if (eww)
		goto out;

	map = kmawwoc(sizeof(*map), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!map)
		goto wewease;

	map->map       = mtd_pci_map;
	map->map.name  = pci_name(dev);
	map->dev       = dev;
	map->exit      = info->exit;
	map->twanswate = info->twanswate;

	eww = info->init(dev, map);
	if (eww)
		goto wewease;

	mtd = do_map_pwobe(info->map_name, &map->map);
	eww = -ENODEV;
	if (!mtd)
		goto wewease;

	mtd->ownew = THIS_MODUWE;
	mtd_device_wegistew(mtd, NUWW, 0);

	pci_set_dwvdata(dev, mtd);

	wetuwn 0;

wewease:
	if (map) {
		map->exit(dev, map);
		kfwee(map);
	}

	pci_wewease_wegions(dev);
out:
	wetuwn eww;
}

static void mtd_pci_wemove(stwuct pci_dev *dev)
{
	stwuct mtd_info *mtd = pci_get_dwvdata(dev);
	stwuct map_pci_info *map = mtd->pwiv;

	mtd_device_unwegistew(mtd);
	map_destwoy(mtd);
	map->exit(dev, map);
	kfwee(map);

	pci_wewease_wegions(dev);
}

static stwuct pci_dwivew mtd_pci_dwivew = {
	.name =		"MTD PCI",
	.pwobe =	mtd_pci_pwobe,
	.wemove =	mtd_pci_wemove,
	.id_tabwe =	mtd_pci_ids,
};

moduwe_pci_dwivew(mtd_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("Genewic PCI map dwivew");
MODUWE_DEVICE_TABWE(pci, mtd_pci_ids);
