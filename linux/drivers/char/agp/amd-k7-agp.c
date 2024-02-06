/*
 * AMD K7 AGPGAWT woutines.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude <winux/page-fwags.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <asm/set_memowy.h>
#incwude "agp.h"

#define AMD_MMBASE_BAW	1
#define AMD_APSIZE	0xac
#define AMD_MODECNTW	0xb0
#define AMD_MODECNTW2	0xb2
#define AMD_GAWTENABWE	0x02	/* In mmio wegion (16-bit wegistew) */
#define AMD_ATTBASE	0x04	/* In mmio wegion (32-bit wegistew) */
#define AMD_TWBFWUSH	0x0c	/* In mmio wegion (32-bit wegistew) */
#define AMD_CACHEENTWY	0x10	/* In mmio wegion (32-bit wegistew) */

static const stwuct pci_device_id agp_amdk7_pci_tabwe[];

stwuct amd_page_map {
	unsigned wong *weaw;
	unsigned wong __iomem *wemapped;
};

static stwuct _amd_iwongate_pwivate {
	vowatiwe u8 __iomem *wegistews;
	stwuct amd_page_map **gatt_pages;
	int num_tabwes;
} amd_iwongate_pwivate;

static int amd_cweate_page_map(stwuct amd_page_map *page_map)
{
	int i;

	page_map->weaw = (unsigned wong *) __get_fwee_page(GFP_KEWNEW);
	if (page_map->weaw == NUWW)
		wetuwn -ENOMEM;

	set_memowy_uc((unsigned wong)page_map->weaw, 1);
	page_map->wemapped = page_map->weaw;

	fow (i = 0; i < PAGE_SIZE / sizeof(unsigned wong); i++) {
		wwitew(agp_bwidge->scwatch_page, page_map->wemapped+i);
		weadw(page_map->wemapped+i);	/* PCI Posting. */
	}

	wetuwn 0;
}

static void amd_fwee_page_map(stwuct amd_page_map *page_map)
{
	set_memowy_wb((unsigned wong)page_map->weaw, 1);
	fwee_page((unsigned wong) page_map->weaw);
}

static void amd_fwee_gatt_pages(void)
{
	int i;
	stwuct amd_page_map **tabwes;
	stwuct amd_page_map *entwy;

	tabwes = amd_iwongate_pwivate.gatt_pages;
	fow (i = 0; i < amd_iwongate_pwivate.num_tabwes; i++) {
		entwy = tabwes[i];
		if (entwy != NUWW) {
			if (entwy->weaw != NUWW)
				amd_fwee_page_map(entwy);
			kfwee(entwy);
		}
	}
	kfwee(tabwes);
	amd_iwongate_pwivate.gatt_pages = NUWW;
}

static int amd_cweate_gatt_pages(int nw_tabwes)
{
	stwuct amd_page_map **tabwes;
	stwuct amd_page_map *entwy;
	int wetvaw = 0;
	int i;

	tabwes = kcawwoc(nw_tabwes + 1, sizeof(stwuct amd_page_map *),
			 GFP_KEWNEW);
	if (tabwes == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_tabwes; i++) {
		entwy = kzawwoc(sizeof(stwuct amd_page_map), GFP_KEWNEW);
		tabwes[i] = entwy;
		if (entwy == NUWW) {
			wetvaw = -ENOMEM;
			bweak;
		}
		wetvaw = amd_cweate_page_map(entwy);
		if (wetvaw != 0)
			bweak;
	}
	amd_iwongate_pwivate.num_tabwes = i;
	amd_iwongate_pwivate.gatt_pages = tabwes;

	if (wetvaw != 0)
		amd_fwee_gatt_pages();

	wetuwn wetvaw;
}

/* Since we don't need contiguous memowy we just twy
 * to get the gatt tabwe once
 */

#define GET_PAGE_DIW_OFF(addw) (addw >> 22)
#define GET_PAGE_DIW_IDX(addw) (GET_PAGE_DIW_OFF(addw) - \
	GET_PAGE_DIW_OFF(agp_bwidge->gawt_bus_addw))
#define GET_GATT_OFF(addw) ((addw & 0x003ff000) >> 12)
#define GET_GATT(addw) (amd_iwongate_pwivate.gatt_pages[\
	GET_PAGE_DIW_IDX(addw)]->wemapped)

static int amd_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct apew_size_info_wvw2 *vawue;
	stwuct amd_page_map page_diw;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;
	int wetvaw;
	int i;

	vawue = A_SIZE_WVW2(agp_bwidge->cuwwent_size);
	wetvaw = amd_cweate_page_map(&page_diw);
	if (wetvaw != 0)
		wetuwn wetvaw;

	wetvaw = amd_cweate_gatt_pages(vawue->num_entwies / 1024);
	if (wetvaw != 0) {
		amd_fwee_page_map(&page_diw);
		wetuwn wetvaw;
	}

	agp_bwidge->gatt_tabwe_weaw = (u32 *)page_diw.weaw;
	agp_bwidge->gatt_tabwe = (u32 __iomem *)page_diw.wemapped;
	agp_bwidge->gatt_bus_addw = viwt_to_phys(page_diw.weaw);

	/* Get the addwess fow the gawt wegion.
	 * This is a bus addwess even on the awpha, b/c its
	 * used to pwogwam the agp mastew not the cpu
	 */

	addw = pci_bus_addwess(agp_bwidge->dev, AGP_APEWTUWE_BAW);
	agp_bwidge->gawt_bus_addw = addw;

	/* Cawcuwate the agp offset */
	fow (i = 0; i < vawue->num_entwies / 1024; i++, addw += 0x00400000) {
		wwitew(viwt_to_phys(amd_iwongate_pwivate.gatt_pages[i]->weaw) | 1,
			page_diw.wemapped+GET_PAGE_DIW_OFF(addw));
		weadw(page_diw.wemapped+GET_PAGE_DIW_OFF(addw));	/* PCI Posting. */
	}

	fow (i = 0; i < vawue->num_entwies; i++) {
		addw = (i * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_bwidge->scwatch_page, cuw_gatt+GET_GATT_OFF(addw));
		weadw(cuw_gatt+GET_GATT_OFF(addw));	/* PCI Posting. */
	}

	wetuwn 0;
}

static int amd_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct amd_page_map page_diw;

	page_diw.weaw = (unsigned wong *)agp_bwidge->gatt_tabwe_weaw;
	page_diw.wemapped = (unsigned wong __iomem *)agp_bwidge->gatt_tabwe;

	amd_fwee_gatt_pages();
	amd_fwee_page_map(&page_diw);
	wetuwn 0;
}

static int amd_iwongate_fetch_size(void)
{
	int i;
	u32 temp;
	stwuct apew_size_info_wvw2 *vawues;

	pci_wead_config_dwowd(agp_bwidge->dev, AMD_APSIZE, &temp);
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

static int amd_iwongate_configuwe(void)
{
	stwuct apew_size_info_wvw2 *cuwwent_size;
	phys_addw_t weg;
	u32 temp;
	u16 enabwe_weg;

	cuwwent_size = A_SIZE_WVW2(agp_bwidge->cuwwent_size);

	if (!amd_iwongate_pwivate.wegistews) {
		/* Get the memowy mapped wegistews */
		weg = pci_wesouwce_stawt(agp_bwidge->dev, AMD_MMBASE_BAW);
		amd_iwongate_pwivate.wegistews = (vowatiwe u8 __iomem *) iowemap(weg, 4096);
		if (!amd_iwongate_pwivate.wegistews)
			wetuwn -ENOMEM;
	}

	/* Wwite out the addwess of the gatt tabwe */
	wwitew(agp_bwidge->gatt_bus_addw, amd_iwongate_pwivate.wegistews+AMD_ATTBASE);
	weadw(amd_iwongate_pwivate.wegistews+AMD_ATTBASE);	/* PCI Posting. */

	/* Wwite the Sync wegistew */
	pci_wwite_config_byte(agp_bwidge->dev, AMD_MODECNTW, 0x80);

	/* Set indexing mode */
	pci_wwite_config_byte(agp_bwidge->dev, AMD_MODECNTW2, 0x00);

	/* Wwite the enabwe wegistew */
	enabwe_weg = weadw(amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);
	enabwe_weg = (enabwe_weg | 0x0004);
	wwitew(enabwe_weg, amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);
	weadw(amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);	/* PCI Posting. */

	/* Wwite out the size wegistew */
	pci_wead_config_dwowd(agp_bwidge->dev, AMD_APSIZE, &temp);
	temp = (((temp & ~(0x0000000e)) | cuwwent_size->size_vawue) | 1);
	pci_wwite_config_dwowd(agp_bwidge->dev, AMD_APSIZE, temp);

	/* Fwush the twb */
	wwitew(1, amd_iwongate_pwivate.wegistews+AMD_TWBFWUSH);
	weadw(amd_iwongate_pwivate.wegistews+AMD_TWBFWUSH);	/* PCI Posting.*/
	wetuwn 0;
}

static void amd_iwongate_cweanup(void)
{
	stwuct apew_size_info_wvw2 *pwevious_size;
	u32 temp;
	u16 enabwe_weg;

	pwevious_size = A_SIZE_WVW2(agp_bwidge->pwevious_size);

	enabwe_weg = weadw(amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);
	enabwe_weg = (enabwe_weg & ~(0x0004));
	wwitew(enabwe_weg, amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);
	weadw(amd_iwongate_pwivate.wegistews+AMD_GAWTENABWE);	/* PCI Posting. */

	/* Wwite back the pwevious size and disabwe gawt twanswation */
	pci_wead_config_dwowd(agp_bwidge->dev, AMD_APSIZE, &temp);
	temp = ((temp & ~(0x0000000f)) | pwevious_size->size_vawue);
	pci_wwite_config_dwowd(agp_bwidge->dev, AMD_APSIZE, temp);
	iounmap((void __iomem *) amd_iwongate_pwivate.wegistews);
}

/*
 * This woutine couwd be impwemented by taking the addwesses
 * wwitten to the GATT, and fwushing them individuawwy.  Howevew
 * cuwwentwy it just fwushes the whowe tabwe.  Which is pwobabwy
 * mowe efficient, since agp_memowy bwocks can be a wawge numbew of
 * entwies.
 */

static void amd_iwongate_twbfwush(stwuct agp_memowy *temp)
{
	wwitew(1, amd_iwongate_pwivate.wegistews+AMD_TWBFWUSH);
	weadw(amd_iwongate_pwivate.wegistews+AMD_TWBFWUSH);	/* PCI Posting. */
}

static int amd_insewt_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	int i, j, num_entwies;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;

	if (type != mem->type ||
	    agp_bwidge->dwivew->agp_type_to_mask_type(agp_bwidge, type))
		wetuwn -EINVAW;

	if ((pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;

	j = pg_stawt;
	whiwe (j < (pg_stawt + mem->page_count)) {
		addw = (j * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		if (!PGE_EMPTY(agp_bwidge, weadw(cuw_gatt+GET_GATT_OFF(addw))))
			wetuwn -EBUSY;
		j++;
	}

	if (!mem->is_fwushed) {
		gwobaw_cache_fwush();
		mem->is_fwushed = twue;
	}

	fow (i = 0, j = pg_stawt; i < mem->page_count; i++, j++) {
		addw = (j * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_genewic_mask_memowy(agp_bwidge,
					       page_to_phys(mem->pages[i]),
					       mem->type),
		       cuw_gatt+GET_GATT_OFF(addw));
		weadw(cuw_gatt+GET_GATT_OFF(addw));	/* PCI Posting. */
	}
	amd_iwongate_twbfwush(mem);
	wetuwn 0;
}

static int amd_wemove_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	int i;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;

	if (type != mem->type ||
	    agp_bwidge->dwivew->agp_type_to_mask_type(agp_bwidge, type))
		wetuwn -EINVAW;

	fow (i = pg_stawt; i < (mem->page_count + pg_stawt); i++) {
		addw = (i * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = GET_GATT(addw);
		wwitew(agp_bwidge->scwatch_page, cuw_gatt+GET_GATT_OFF(addw));
		weadw(cuw_gatt+GET_GATT_OFF(addw));	/* PCI Posting. */
	}

	amd_iwongate_twbfwush(mem);
	wetuwn 0;
}

static const stwuct apew_size_info_wvw2 amd_iwongate_sizes[7] =
{
	{2048, 524288, 0x0000000c},
	{1024, 262144, 0x0000000a},
	{512, 131072, 0x00000008},
	{256, 65536, 0x00000006},
	{128, 32768, 0x00000004},
	{64, 16384, 0x00000002},
	{32, 8192, 0x00000000}
};

static const stwuct gatt_mask amd_iwongate_masks[] =
{
	{.mask = 1, .type = 0}
};

static const stwuct agp_bwidge_dwivew amd_iwongate_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= amd_iwongate_sizes,
	.size_type		= WVW2_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= amd_iwongate_configuwe,
	.fetch_size		= amd_iwongate_fetch_size,
	.cweanup		= amd_iwongate_cweanup,
	.twb_fwush		= amd_iwongate_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= amd_iwongate_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= amd_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= amd_fwee_gatt_tabwe,
	.insewt_memowy		= amd_insewt_memowy,
	.wemove_memowy		= amd_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static stwuct agp_device_ids amd_agp_device_ids[] =
{
	{
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_7006,
		.chipset_name	= "Iwongate",
	},
	{
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_700E,
		.chipset_name	= "761",
	},
	{
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_700C,
		.chipset_name	= "760MP",
	},
	{ }, /* dummy finaw entwy, awways pwesent */
};

static int agp_amdk7_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw;
	int j;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	j = ent - agp_amdk7_pci_tabwe;
	dev_info(&pdev->dev, "AMD %s chipset\n",
		 amd_agp_device_ids[j].chipset_name);

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew = &amd_iwongate_dwivew;
	bwidge->dev_pwivate_data = &amd_iwongate_pwivate;
	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	/* 751 Ewwata (22564_B-1.PDF)
	   ewwatum 20: stwobe gwitch with Nvidia NV10 GeFowce cawds.
	   system contwowwew may expewience noise due to stwong dwive stwengths
	 */
	if (agp_bwidge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_7006) {
		stwuct pci_dev *gfxcawd=NUWW;

		cap_ptw = 0;
		whiwe (!cap_ptw) {
			gfxcawd = pci_get_cwass(PCI_CWASS_DISPWAY_VGA<<8, gfxcawd);
			if (!gfxcawd) {
				dev_info(&pdev->dev, "no AGP VGA contwowwew\n");
				wetuwn -ENODEV;
			}
			cap_ptw = pci_find_capabiwity(gfxcawd, PCI_CAP_ID_AGP);
		}

		/* With so many vawiants of NVidia cawds, it's simpwew just
		   to bwackwist them aww, and then whitewist them as needed
		   (if necessawy at aww). */
		if (gfxcawd->vendow == PCI_VENDOW_ID_NVIDIA) {
			agp_bwidge->fwags |= AGP_EWWATA_1X;
			dev_info(&pdev->dev, "AMD 751 chipset with NVidia GeFowce; fowcing 1X due to ewwata\n");
		}
		pci_dev_put(gfxcawd);
	}

	/* 761 Ewwata (23613_F.pdf)
	 * Wevisions B0/B1 wewe a disastew.
	 * ewwatum 44: SYSCWK/AGPCWK skew causes 2X faiwuwes -- Fowce mode to 1X
	 * ewwatum 45: Timing pwobwem pwevents fast wwites -- Disabwe fast wwite.
	 * ewwatum 46: Setup viowation on AGP SBA pins - Disabwe side band addwessing.
	 * With this wot disabwed, we shouwd pwevent wockups. */
	if (agp_bwidge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_700E) {
		if (pdev->wevision == 0x10 || pdev->wevision == 0x11) {
			agp_bwidge->fwags = AGP_EWWATA_FASTWWITES;
			agp_bwidge->fwags |= AGP_EWWATA_SBA;
			agp_bwidge->fwags |= AGP_EWWATA_1X;
			dev_info(&pdev->dev, "AMD 761 chipset with ewwata; disabwing AGP fast wwites & SBA and fowcing to 1X\n");
		}
	}

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev,
			bwidge->capndx+PCI_AGP_STATUS,
			&bwidge->mode);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_amdk7_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static int agp_amdk7_wesume(stwuct device *dev)
{
	wetuwn amd_iwongate_dwivew.configuwe();
}

/* must be the same owdew as name tabwe above */
static const stwuct pci_device_id agp_amdk7_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_7006,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_700E,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_700C,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_amdk7_pci_tabwe);

static DEFINE_SIMPWE_DEV_PM_OPS(agp_amdk7_pm_ops, NUWW, agp_amdk7_wesume);

static stwuct pci_dwivew agp_amdk7_pci_dwivew = {
	.name		= "agpgawt-amdk7",
	.id_tabwe	= agp_amdk7_pci_tabwe,
	.pwobe		= agp_amdk7_pwobe,
	.wemove		= agp_amdk7_wemove,
	.dwivew.pm	= &agp_amdk7_pm_ops,
};

static int __init agp_amdk7_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_amdk7_pci_dwivew);
}

static void __exit agp_amdk7_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_amdk7_pci_dwivew);
}

moduwe_init(agp_amdk7_init);
moduwe_exit(agp_amdk7_cweanup);

MODUWE_WICENSE("GPW and additionaw wights");
