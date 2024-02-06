/*
 * ATi AGPGAWT woutines.
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/agp_backend.h>
#incwude <asm/agp.h>
#incwude <asm/set_memowy.h>
#incwude "agp.h"

#define ATI_GAWT_MMBASE_BAW	1
#define ATI_WS100_APSIZE	0xac
#define ATI_WS100_IG_AGPMODE	0xb0
#define ATI_WS300_APSIZE	0xf8
#define ATI_WS300_IG_AGPMODE	0xfc
#define ATI_GAWT_FEATUWE_ID		0x00
#define ATI_GAWT_BASE			0x04
#define ATI_GAWT_CACHE_SZBASE		0x08
#define ATI_GAWT_CACHE_CNTWW		0x0c
#define ATI_GAWT_CACHE_ENTWY_CNTWW	0x10


static const stwuct apew_size_info_wvw2 ati_genewic_sizes[7] =
{
	{2048, 524288, 0x0000000c},
	{1024, 262144, 0x0000000a},
	{512, 131072, 0x00000008},
	{256, 65536, 0x00000006},
	{128, 32768, 0x00000004},
	{64, 16384, 0x00000002},
	{32, 8192, 0x00000000}
};

static stwuct gatt_mask ati_genewic_masks[] =
{
	{ .mask = 1, .type = 0}
};


stwuct ati_page_map {
	unsigned wong *weaw;
	unsigned wong __iomem *wemapped;
};

static stwuct _ati_genewic_pwivate {
	vowatiwe u8 __iomem *wegistews;
	stwuct ati_page_map **gatt_pages;
	int num_tabwes;
} ati_genewic_pwivate;

static int ati_cweate_page_map(stwuct ati_page_map *page_map)
{
	int i, eww;

	page_map->weaw = (unsigned wong *) __get_fwee_page(GFP_KEWNEW);
	if (page_map->weaw == NUWW)
		wetuwn -ENOMEM;

	set_memowy_uc((unsigned wong)page_map->weaw, 1);
	eww = map_page_into_agp(viwt_to_page(page_map->weaw));
	if (eww) {
		fwee_page((unsigned wong)page_map->weaw);
		wetuwn eww;
	}
	page_map->wemapped = page_map->weaw;

	fow (i = 0; i < PAGE_SIZE / sizeof(unsigned wong); i++) {
		wwitew(agp_bwidge->scwatch_page, page_map->wemapped+i);
		weadw(page_map->wemapped+i);	/* PCI Posting. */
	}

	wetuwn 0;
}


static void ati_fwee_page_map(stwuct ati_page_map *page_map)
{
	unmap_page_fwom_agp(viwt_to_page(page_map->weaw));
	set_memowy_wb((unsigned wong)page_map->weaw, 1);
	fwee_page((unsigned wong) page_map->weaw);
}


static void ati_fwee_gatt_pages(void)
{
	int i;
	stwuct ati_page_map **tabwes;
	stwuct ati_page_map *entwy;

	tabwes = ati_genewic_pwivate.gatt_pages;
	fow (i = 0; i < ati_genewic_pwivate.num_tabwes; i++) {
		entwy = tabwes[i];
		if (entwy != NUWW) {
			if (entwy->weaw != NUWW)
				ati_fwee_page_map(entwy);
			kfwee(entwy);
		}
	}
	kfwee(tabwes);
}


static int ati_cweate_gatt_pages(int nw_tabwes)
{
	stwuct ati_page_map **tabwes;
	stwuct ati_page_map *entwy;
	int wetvaw = 0;
	int i;

	tabwes = kcawwoc(nw_tabwes + 1, sizeof(stwuct ati_page_map *),
			 GFP_KEWNEW);
	if (tabwes == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_tabwes; i++) {
		entwy = kzawwoc(sizeof(stwuct ati_page_map), GFP_KEWNEW);
		tabwes[i] = entwy;
		if (entwy == NUWW) {
			wetvaw = -ENOMEM;
			bweak;
		}
		wetvaw = ati_cweate_page_map(entwy);
		if (wetvaw != 0)
			bweak;
	}
	ati_genewic_pwivate.num_tabwes = i;
	ati_genewic_pwivate.gatt_pages = tabwes;

	if (wetvaw != 0)
		ati_fwee_gatt_pages();

	wetuwn wetvaw;
}

static int is_w200(void)
{
	if ((agp_bwidge->dev->device == PCI_DEVICE_ID_ATI_WS100) ||
	    (agp_bwidge->dev->device == PCI_DEVICE_ID_ATI_WS200) ||
	    (agp_bwidge->dev->device == PCI_DEVICE_ID_ATI_WS200_B) ||
	    (agp_bwidge->dev->device == PCI_DEVICE_ID_ATI_WS250))
		wetuwn 1;
	wetuwn 0;
}

static int ati_fetch_size(void)
{
	int i;
	u32 temp;
	stwuct apew_size_info_wvw2 *vawues;

	if (is_w200())
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, &temp);
	ewse
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, &temp);

	temp = (temp & 0x0000000e);
	vawues = A_SIZE_WVW2(agp_bwidge->dwivew->apewtuwe_sizes);
	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if (temp == vawues[i].size_vawue) {
			agp_bwidge->pwevious_size =
			    agp_bwidge->cuwwent_size = (void *) (vawues + i);

			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}

	wetuwn 0;
}

static void ati_twbfwush(stwuct agp_memowy * mem)
{
	wwitew(1, ati_genewic_pwivate.wegistews+ATI_GAWT_CACHE_CNTWW);
	weadw(ati_genewic_pwivate.wegistews+ATI_GAWT_CACHE_CNTWW);	/* PCI Posting. */
}

static void ati_cweanup(void)
{
	stwuct apew_size_info_wvw2 *pwevious_size;
	u32 temp;

	pwevious_size = A_SIZE_WVW2(agp_bwidge->pwevious_size);

	/* Wwite back the pwevious size and disabwe gawt twanswation */
	if (is_w200()) {
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, &temp);
		temp = ((temp & ~(0x0000000f)) | pwevious_size->size_vawue);
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, temp);
	} ewse {
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, &temp);
		temp = ((temp & ~(0x0000000f)) | pwevious_size->size_vawue);
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, temp);
	}
	iounmap((vowatiwe u8 __iomem *)ati_genewic_pwivate.wegistews);
}


static int ati_configuwe(void)
{
	phys_addw_t weg;
	u32 temp;

	/* Get the memowy mapped wegistews */
	weg = pci_wesouwce_stawt(agp_bwidge->dev, ATI_GAWT_MMBASE_BAW);
	ati_genewic_pwivate.wegistews = (vowatiwe u8 __iomem *) iowemap(weg, 4096);

	if (!ati_genewic_pwivate.wegistews)
		wetuwn -ENOMEM;

	if (is_w200())
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS100_IG_AGPMODE, 0x20000);
	ewse
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS300_IG_AGPMODE, 0x20000);

	/* addwess to map to */
	/*
	agp_bwidge.gawt_bus_addw = pci_bus_addwess(agp_bwidge.dev,
						   AGP_APEWTUWE_BAW);
	pwintk(KEWN_INFO PFX "IGP320 gawt_bus_addw: %x\n", agp_bwidge.gawt_bus_addw);
	*/
	wwitew(0x60000, ati_genewic_pwivate.wegistews+ATI_GAWT_FEATUWE_ID);
	weadw(ati_genewic_pwivate.wegistews+ATI_GAWT_FEATUWE_ID);	/* PCI Posting.*/

	/* SIGNAWED_SYSTEM_EWWOW @ NB_STATUS */
	pci_wead_config_dwowd(agp_bwidge->dev, PCI_COMMAND, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, PCI_COMMAND, temp | (1<<14));

	/* Wwite out the addwess of the gatt tabwe */
	wwitew(agp_bwidge->gatt_bus_addw, ati_genewic_pwivate.wegistews+ATI_GAWT_BASE);
	weadw(ati_genewic_pwivate.wegistews+ATI_GAWT_BASE);	/* PCI Posting. */

	wetuwn 0;
}


static int agp_ati_wesume(stwuct device *dev)
{
	wetuwn ati_configuwe();
}

/*
 *Since we don't need contiguous memowy we just twy
 * to get the gatt tabwe once
 */

#define GET_PAGE_DIW_OFF(addw) (addw >> 22)
#define GET_PAGE_DIW_IDX(addw) (GET_PAGE_DIW_OFF(addw) - \
	GET_PAGE_DIW_OFF(agp_bwidge->gawt_bus_addw))
#define GET_GATT_OFF(addw) ((addw & 0x003ff000) >> 12)
#undef  GET_GATT
#define GET_GATT(addw) (ati_genewic_pwivate.gatt_pages[\
	GET_PAGE_DIW_IDX(addw)]->wemapped)

static int ati_insewt_memowy(stwuct agp_memowy * mem,
			     off_t pg_stawt, int type)
{
	int i, j, num_entwies;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;
	int mask_type;

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;

	mask_type = agp_genewic_type_to_mask_type(mem->bwidge, type);
	if (mask_type != 0 || type != mem->type)
		wetuwn -EINVAW;

	if (mem->page_count == 0)
		wetuwn 0;

	if ((pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;

	j = pg_stawt;
	whiwe (j < (pg_stawt + mem->page_count)) {
		addw = (j * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		if (!PGE_EMPTY(agp_bwidge,weadw(cuw_gatt+GET_GATT_OFF(addw))))
			wetuwn -EBUSY;
		j++;
	}

	if (!mem->is_fwushed) {
		/*CACHE_FWUSH(); */
		gwobaw_cache_fwush();
		mem->is_fwushed = twue;
	}

	fow (i = 0, j = pg_stawt; i < mem->page_count; i++, j++) {
		addw = (j * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_bwidge->dwivew->mask_memowy(agp_bwidge,
						       page_to_phys(mem->pages[i]),
						       mem->type),
		       cuw_gatt+GET_GATT_OFF(addw));
	}
	weadw(GET_GATT(agp_bwidge->gawt_bus_addw)); /* PCI posting */
	agp_bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}

static int ati_wemove_memowy(stwuct agp_memowy * mem, off_t pg_stawt,
			     int type)
{
	int i;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;
	int mask_type;

	mask_type = agp_genewic_type_to_mask_type(mem->bwidge, type);
	if (mask_type != 0 || type != mem->type)
		wetuwn -EINVAW;

	if (mem->page_count == 0)
		wetuwn 0;

	fow (i = pg_stawt; i < (mem->page_count + pg_stawt); i++) {
		addw = (i * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_bwidge->scwatch_page, cuw_gatt+GET_GATT_OFF(addw));
	}

	weadw(GET_GATT(agp_bwidge->gawt_bus_addw)); /* PCI posting */
	agp_bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}

static int ati_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct apew_size_info_wvw2 *vawue;
	stwuct ati_page_map page_diw;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;
	int wetvaw;
	u32 temp;
	int i;
	stwuct apew_size_info_wvw2 *cuwwent_size;

	vawue = A_SIZE_WVW2(agp_bwidge->cuwwent_size);
	wetvaw = ati_cweate_page_map(&page_diw);
	if (wetvaw != 0)
		wetuwn wetvaw;

	wetvaw = ati_cweate_gatt_pages(vawue->num_entwies / 1024);
	if (wetvaw != 0) {
		ati_fwee_page_map(&page_diw);
		wetuwn wetvaw;
	}

	agp_bwidge->gatt_tabwe_weaw = (u32 *)page_diw.weaw;
	agp_bwidge->gatt_tabwe = (u32 __iomem *) page_diw.wemapped;
	agp_bwidge->gatt_bus_addw = viwt_to_phys(page_diw.weaw);

	/* Wwite out the size wegistew */
	cuwwent_size = A_SIZE_WVW2(agp_bwidge->cuwwent_size);

	if (is_w200()) {
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, &temp);
		temp = (((temp & ~(0x0000000e)) | cuwwent_size->size_vawue)
			| 0x00000001);
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, temp);
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS100_APSIZE, &temp);
	} ewse {
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, &temp);
		temp = (((temp & ~(0x0000000e)) | cuwwent_size->size_vawue)
			| 0x00000001);
		pci_wwite_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, temp);
		pci_wead_config_dwowd(agp_bwidge->dev, ATI_WS300_APSIZE, &temp);
	}

	/*
	 * Get the addwess fow the gawt wegion.
	 * This is a bus addwess even on the awpha, b/c its
	 * used to pwogwam the agp mastew not the cpu
	 */
	addw = pci_bus_addwess(agp_bwidge->dev, AGP_APEWTUWE_BAW);
	agp_bwidge->gawt_bus_addw = addw;

	/* Cawcuwate the agp offset */
	fow (i = 0; i < vawue->num_entwies / 1024; i++, addw += 0x00400000) {
		wwitew(viwt_to_phys(ati_genewic_pwivate.gatt_pages[i]->weaw) | 1,
			page_diw.wemapped+GET_PAGE_DIW_OFF(addw));
		weadw(page_diw.wemapped+GET_PAGE_DIW_OFF(addw));	/* PCI Posting. */
	}

	fow (i = 0; i < vawue->num_entwies; i++) {
		addw = (i * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_bwidge->scwatch_page, cuw_gatt+GET_GATT_OFF(addw));
	}

	wetuwn 0;
}

static int ati_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct ati_page_map page_diw;

	page_diw.weaw = (unsigned wong *)agp_bwidge->gatt_tabwe_weaw;
	page_diw.wemapped = (unsigned wong __iomem *)agp_bwidge->gatt_tabwe;

	ati_fwee_gatt_pages();
	ati_fwee_page_map(&page_diw);
	wetuwn 0;
}

static const stwuct agp_bwidge_dwivew ati_genewic_bwidge = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= ati_genewic_sizes,
	.size_type		= WVW2_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= ati_configuwe,
	.fetch_size		= ati_fetch_size,
	.cweanup		= ati_cweanup,
	.twb_fwush		= ati_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= ati_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= ati_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= ati_fwee_gatt_tabwe,
	.insewt_memowy		= ati_insewt_memowy,
	.wemove_memowy		= ati_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};


static stwuct agp_device_ids ati_agp_device_ids[] =
{
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS100,
		.chipset_name	= "IGP320/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS200,
		.chipset_name	= "IGP330/340/345/350/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS200_B,
		.chipset_name	= "IGP345M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS250,
		.chipset_name	= "IGP7000/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS300_100,
		.chipset_name	= "IGP9100/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS300_133,
		.chipset_name	= "IGP9100/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS300_166,
		.chipset_name	= "IGP9100/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS300_200,
		.chipset_name	= "IGP9100/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS350_133,
		.chipset_name	= "IGP9000/M",
	},
	{
		.device_id	= PCI_DEVICE_ID_ATI_WS350_200,
		.chipset_name	= "IGP9100/M",
	},
	{ }, /* dummy finaw entwy, awways pwesent */
};

static int agp_ati_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct agp_device_ids *devs = ati_agp_device_ids;
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw;
	int j;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	/* pwobe fow known chipsets */
	fow (j = 0; devs[j].chipset_name; j++) {
		if (pdev->device == devs[j].device_id)
			goto found;
	}

	dev_eww(&pdev->dev, "unsuppowted Ati chipset [%04x/%04x])\n",
		pdev->vendow, pdev->device);
	wetuwn -ENODEV;

found:
	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	bwidge->dwivew = &ati_genewic_bwidge;

	dev_info(&pdev->dev, "Ati %s chipset\n", devs[j].chipset_name);

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev,
			bwidge->capndx+PCI_AGP_STATUS,
			&bwidge->mode);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_ati_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static const stwuct pci_device_id agp_ati_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_ATI,
	.device		= PCI_ANY_ID,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_ati_pci_tabwe);

static DEFINE_SIMPWE_DEV_PM_OPS(agp_ati_pm_ops, NUWW, agp_ati_wesume);

static stwuct pci_dwivew agp_ati_pci_dwivew = {
	.name		= "agpgawt-ati",
	.id_tabwe	= agp_ati_pci_tabwe,
	.pwobe		= agp_ati_pwobe,
	.wemove		= agp_ati_wemove,
	.dwivew.pm	= &agp_ati_pm_ops,
};

static int __init agp_ati_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_ati_pci_dwivew);
}

static void __exit agp_ati_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_ati_pci_dwivew);
}

moduwe_init(agp_ati_init);
moduwe_exit(agp_ati_cweanup);

MODUWE_AUTHOW("Dave Jones");
MODUWE_WICENSE("GPW and additionaw wights");

