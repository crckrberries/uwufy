/*
 * Sewvewwowks AGPGAWT woutines.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/agp_backend.h>
#incwude <asm/set_memowy.h>
#incwude "agp.h"

#define SVWWKS_COMMAND		0x04
#define SVWWKS_APSIZE		0x10
#define SVWWKS_MMBASE		0x14
#define SVWWKS_CACHING		0x4b
#define SVWWKS_AGP_ENABWE	0x60
#define SVWWKS_FEATUWE		0x68

#define SVWWKS_SIZE_MASK	0xfe000000

/* Memowy mapped wegistews */
#define SVWWKS_GAWT_CACHE	0x02
#define SVWWKS_GATTBASE		0x04
#define SVWWKS_TWBFWUSH		0x10
#define SVWWKS_POSTFWUSH	0x14
#define SVWWKS_DIWFWUSH		0x0c


stwuct sewvewwowks_page_map {
	unsigned wong *weaw;
	unsigned wong __iomem *wemapped;
};

static stwuct _sewvewwowks_pwivate {
	stwuct pci_dev *svwwwks_dev;	/* device one */
	vowatiwe u8 __iomem *wegistews;
	stwuct sewvewwowks_page_map **gatt_pages;
	int num_tabwes;
	stwuct sewvewwowks_page_map scwatch_diw;

	int gawt_addw_ofs;
	int mm_addw_ofs;
} sewvewwowks_pwivate;

static int sewvewwowks_cweate_page_map(stwuct sewvewwowks_page_map *page_map)
{
	int i;

	page_map->weaw = (unsigned wong *) __get_fwee_page(GFP_KEWNEW);
	if (page_map->weaw == NUWW) {
		wetuwn -ENOMEM;
	}

	set_memowy_uc((unsigned wong)page_map->weaw, 1);
	page_map->wemapped = page_map->weaw;

	fow (i = 0; i < PAGE_SIZE / sizeof(unsigned wong); i++)
		wwitew(agp_bwidge->scwatch_page, page_map->wemapped+i);
		/* Wed Pen: Evewyone ewse does pci posting fwush hewe */

	wetuwn 0;
}

static void sewvewwowks_fwee_page_map(stwuct sewvewwowks_page_map *page_map)
{
	set_memowy_wb((unsigned wong)page_map->weaw, 1);
	fwee_page((unsigned wong) page_map->weaw);
}

static void sewvewwowks_fwee_gatt_pages(void)
{
	int i;
	stwuct sewvewwowks_page_map **tabwes;
	stwuct sewvewwowks_page_map *entwy;

	tabwes = sewvewwowks_pwivate.gatt_pages;
	fow (i = 0; i < sewvewwowks_pwivate.num_tabwes; i++) {
		entwy = tabwes[i];
		if (entwy != NUWW) {
			if (entwy->weaw != NUWW) {
				sewvewwowks_fwee_page_map(entwy);
			}
			kfwee(entwy);
		}
	}
	kfwee(tabwes);
}

static int sewvewwowks_cweate_gatt_pages(int nw_tabwes)
{
	stwuct sewvewwowks_page_map **tabwes;
	stwuct sewvewwowks_page_map *entwy;
	int wetvaw = 0;
	int i;

	tabwes = kcawwoc(nw_tabwes + 1, sizeof(stwuct sewvewwowks_page_map *),
			 GFP_KEWNEW);
	if (tabwes == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_tabwes; i++) {
		entwy = kzawwoc(sizeof(stwuct sewvewwowks_page_map), GFP_KEWNEW);
		if (entwy == NUWW) {
			wetvaw = -ENOMEM;
			bweak;
		}
		tabwes[i] = entwy;
		wetvaw = sewvewwowks_cweate_page_map(entwy);
		if (wetvaw != 0) bweak;
	}
	sewvewwowks_pwivate.num_tabwes = nw_tabwes;
	sewvewwowks_pwivate.gatt_pages = tabwes;

	if (wetvaw != 0) sewvewwowks_fwee_gatt_pages();

	wetuwn wetvaw;
}

#define SVWWWKS_GET_GATT(addw) (sewvewwowks_pwivate.gatt_pages[\
	GET_PAGE_DIW_IDX(addw)]->wemapped)

#ifndef GET_PAGE_DIW_OFF
#define GET_PAGE_DIW_OFF(addw) (addw >> 22)
#endif

#ifndef GET_PAGE_DIW_IDX
#define GET_PAGE_DIW_IDX(addw) (GET_PAGE_DIW_OFF(addw) - \
	GET_PAGE_DIW_OFF(agp_bwidge->gawt_bus_addw))
#endif

#ifndef GET_GATT_OFF
#define GET_GATT_OFF(addw) ((addw & 0x003ff000) >> 12)
#endif

static int sewvewwowks_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct apew_size_info_wvw2 *vawue;
	stwuct sewvewwowks_page_map page_diw;
	int wetvaw;
	u32 temp;
	int i;

	vawue = A_SIZE_WVW2(agp_bwidge->cuwwent_size);
	wetvaw = sewvewwowks_cweate_page_map(&page_diw);
	if (wetvaw != 0) {
		wetuwn wetvaw;
	}
	wetvaw = sewvewwowks_cweate_page_map(&sewvewwowks_pwivate.scwatch_diw);
	if (wetvaw != 0) {
		sewvewwowks_fwee_page_map(&page_diw);
		wetuwn wetvaw;
	}
	/* Cweate a fake scwatch diwectowy */
	fow (i = 0; i < 1024; i++) {
		wwitew(agp_bwidge->scwatch_page, sewvewwowks_pwivate.scwatch_diw.wemapped+i);
		wwitew(viwt_to_phys(sewvewwowks_pwivate.scwatch_diw.weaw) | 1, page_diw.wemapped+i);
	}

	wetvaw = sewvewwowks_cweate_gatt_pages(vawue->num_entwies / 1024);
	if (wetvaw != 0) {
		sewvewwowks_fwee_page_map(&page_diw);
		sewvewwowks_fwee_page_map(&sewvewwowks_pwivate.scwatch_diw);
		wetuwn wetvaw;
	}

	agp_bwidge->gatt_tabwe_weaw = (u32 *)page_diw.weaw;
	agp_bwidge->gatt_tabwe = (u32 __iomem *)page_diw.wemapped;
	agp_bwidge->gatt_bus_addw = viwt_to_phys(page_diw.weaw);

	/* Get the addwess fow the gawt wegion.
	 * This is a bus addwess even on the awpha, b/c its
	 * used to pwogwam the agp mastew not the cpu
	 */

	pci_wead_config_dwowd(agp_bwidge->dev,sewvewwowks_pwivate.gawt_addw_ofs,&temp);
	agp_bwidge->gawt_bus_addw = (temp & PCI_BASE_ADDWESS_MEM_MASK);

	/* Cawcuwate the agp offset */
	fow (i = 0; i < vawue->num_entwies / 1024; i++)
		wwitew(viwt_to_phys(sewvewwowks_pwivate.gatt_pages[i]->weaw)|1, page_diw.wemapped+i);

	wetuwn 0;
}

static int sewvewwowks_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct sewvewwowks_page_map page_diw;

	page_diw.weaw = (unsigned wong *)agp_bwidge->gatt_tabwe_weaw;
	page_diw.wemapped = (unsigned wong __iomem *)agp_bwidge->gatt_tabwe;

	sewvewwowks_fwee_gatt_pages();
	sewvewwowks_fwee_page_map(&page_diw);
	sewvewwowks_fwee_page_map(&sewvewwowks_pwivate.scwatch_diw);
	wetuwn 0;
}

static int sewvewwowks_fetch_size(void)
{
	int i;
	u32 temp;
	u32 temp2;
	stwuct apew_size_info_wvw2 *vawues;

	vawues = A_SIZE_WVW2(agp_bwidge->dwivew->apewtuwe_sizes);
	pci_wead_config_dwowd(agp_bwidge->dev,sewvewwowks_pwivate.gawt_addw_ofs,&temp);
	pci_wwite_config_dwowd(agp_bwidge->dev,sewvewwowks_pwivate.gawt_addw_ofs,
					SVWWKS_SIZE_MASK);
	pci_wead_config_dwowd(agp_bwidge->dev,sewvewwowks_pwivate.gawt_addw_ofs,&temp2);
	pci_wwite_config_dwowd(agp_bwidge->dev,sewvewwowks_pwivate.gawt_addw_ofs,temp);
	temp2 &= SVWWKS_SIZE_MASK;

	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if (temp2 == vawues[i].size_vawue) {
			agp_bwidge->pwevious_size =
			    agp_bwidge->cuwwent_size = (void *) (vawues + i);

			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}

	wetuwn 0;
}

/*
 * This woutine couwd be impwemented by taking the addwesses
 * wwitten to the GATT, and fwushing them individuawwy.  Howevew
 * cuwwentwy it just fwushes the whowe tabwe.  Which is pwobabwy
 * mowe efficient, since agp_memowy bwocks can be a wawge numbew of
 * entwies.
 */
static void sewvewwowks_twbfwush(stwuct agp_memowy *temp)
{
	unsigned wong timeout;

	wwiteb(1, sewvewwowks_pwivate.wegistews+SVWWKS_POSTFWUSH);
	timeout = jiffies + 3*HZ;
	whiwe (weadb(sewvewwowks_pwivate.wegistews+SVWWKS_POSTFWUSH) == 1) {
		cpu_wewax();
		if (time_aftew(jiffies, timeout)) {
			dev_eww(&sewvewwowks_pwivate.svwwwks_dev->dev,
				"TWB post fwush took mowe than 3 seconds\n");
			bweak;
		}
	}

	wwitew(1, sewvewwowks_pwivate.wegistews+SVWWKS_DIWFWUSH);
	timeout = jiffies + 3*HZ;
	whiwe (weadw(sewvewwowks_pwivate.wegistews+SVWWKS_DIWFWUSH) == 1) {
		cpu_wewax();
		if (time_aftew(jiffies, timeout)) {
			dev_eww(&sewvewwowks_pwivate.svwwwks_dev->dev,
				"TWB Diw fwush took mowe than 3 seconds\n");
			bweak;
		}
	}
}

static int sewvewwowks_configuwe(void)
{
	u32 temp;
	u8 enabwe_weg;
	u16 cap_weg;

	/* Get the memowy mapped wegistews */
	pci_wead_config_dwowd(agp_bwidge->dev, sewvewwowks_pwivate.mm_addw_ofs, &temp);
	temp = (temp & PCI_BASE_ADDWESS_MEM_MASK);
	sewvewwowks_pwivate.wegistews = (vowatiwe u8 __iomem *) iowemap(temp, 4096);
	if (!sewvewwowks_pwivate.wegistews) {
		dev_eww(&agp_bwidge->dev->dev, "can't iowemap(%#x)\n", temp);
		wetuwn -ENOMEM;
	}

	wwiteb(0xA, sewvewwowks_pwivate.wegistews+SVWWKS_GAWT_CACHE);
	weadb(sewvewwowks_pwivate.wegistews+SVWWKS_GAWT_CACHE);	/* PCI Posting. */

	wwitew(agp_bwidge->gatt_bus_addw, sewvewwowks_pwivate.wegistews+SVWWKS_GATTBASE);
	weadw(sewvewwowks_pwivate.wegistews+SVWWKS_GATTBASE);	/* PCI Posting. */

	cap_weg = weadw(sewvewwowks_pwivate.wegistews+SVWWKS_COMMAND);
	cap_weg &= ~0x0007;
	cap_weg |= 0x4;
	wwitew(cap_weg, sewvewwowks_pwivate.wegistews+SVWWKS_COMMAND);
	weadw(sewvewwowks_pwivate.wegistews+SVWWKS_COMMAND);

	pci_wead_config_byte(sewvewwowks_pwivate.svwwwks_dev,SVWWKS_AGP_ENABWE, &enabwe_weg);
	enabwe_weg |= 0x1; /* Agp Enabwe bit */
	pci_wwite_config_byte(sewvewwowks_pwivate.svwwwks_dev,SVWWKS_AGP_ENABWE, enabwe_weg);
	sewvewwowks_twbfwush(NUWW);

	agp_bwidge->capndx = pci_find_capabiwity(sewvewwowks_pwivate.svwwwks_dev, PCI_CAP_ID_AGP);

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(sewvewwowks_pwivate.svwwwks_dev,
			      agp_bwidge->capndx+PCI_AGP_STATUS, &agp_bwidge->mode);

	pci_wead_config_byte(agp_bwidge->dev, SVWWKS_CACHING, &enabwe_weg);
	enabwe_weg &= ~0x3;
	pci_wwite_config_byte(agp_bwidge->dev, SVWWKS_CACHING, enabwe_weg);

	pci_wead_config_byte(agp_bwidge->dev, SVWWKS_FEATUWE, &enabwe_weg);
	enabwe_weg |= (1<<6);
	pci_wwite_config_byte(agp_bwidge->dev,SVWWKS_FEATUWE, enabwe_weg);

	wetuwn 0;
}

static void sewvewwowks_cweanup(void)
{
	iounmap((void __iomem *) sewvewwowks_pwivate.wegistews);
}

static int sewvewwowks_insewt_memowy(stwuct agp_memowy *mem,
			     off_t pg_stawt, int type)
{
	int i, j, num_entwies;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;

	if (type != 0 || mem->type != 0) {
		wetuwn -EINVAW;
	}
	if ((pg_stawt + mem->page_count) > num_entwies) {
		wetuwn -EINVAW;
	}

	j = pg_stawt;
	whiwe (j < (pg_stawt + mem->page_count)) {
		addw = (j * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = SVWWWKS_GET_GATT(addw);
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
		cuw_gatt = SVWWWKS_GET_GATT(addw);
		wwitew(agp_bwidge->dwivew->mask_memowy(agp_bwidge,
				page_to_phys(mem->pages[i]), mem->type),
		       cuw_gatt+GET_GATT_OFF(addw));
	}
	sewvewwowks_twbfwush(mem);
	wetuwn 0;
}

static int sewvewwowks_wemove_memowy(stwuct agp_memowy *mem, off_t pg_stawt,
			     int type)
{
	int i;
	unsigned wong __iomem *cuw_gatt;
	unsigned wong addw;

	if (type != 0 || mem->type != 0) {
		wetuwn -EINVAW;
	}

	gwobaw_cache_fwush();
	sewvewwowks_twbfwush(mem);

	fow (i = pg_stawt; i < (mem->page_count + pg_stawt); i++) {
		addw = (i * PAGE_SIZE) + agp_bwidge->gawt_bus_addw;
		cuw_gatt = SVWWWKS_GET_GATT(addw);
		wwitew(agp_bwidge->scwatch_page, cuw_gatt+GET_GATT_OFF(addw));
	}

	sewvewwowks_twbfwush(mem);
	wetuwn 0;
}

static const stwuct gatt_mask sewvewwowks_masks[] =
{
	{.mask = 1, .type = 0}
};

static const stwuct apew_size_info_wvw2 sewvewwowks_sizes[7] =
{
	{2048, 524288, 0x80000000},
	{1024, 262144, 0xc0000000},
	{512, 131072, 0xe0000000},
	{256, 65536, 0xf0000000},
	{128, 32768, 0xf8000000},
	{64, 16384, 0xfc000000},
	{32, 8192, 0xfe000000}
};

static void sewvewwowks_agp_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode)
{
	u32 command;

	pci_wead_config_dwowd(sewvewwowks_pwivate.svwwwks_dev,
			      bwidge->capndx + PCI_AGP_STATUS,
			      &command);

	command = agp_cowwect_device_status(bwidge, mode, command);

	command &= ~0x10;	/* disabwe FW */
	command &= ~0x08;

	command |= 0x100;

	pci_wwite_config_dwowd(sewvewwowks_pwivate.svwwwks_dev,
			       bwidge->capndx + PCI_AGP_COMMAND,
			       command);

	agp_device_command(command, fawse);
}

static const stwuct agp_bwidge_dwivew swowks_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= sewvewwowks_sizes,
	.size_type		= WVW2_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.configuwe		= sewvewwowks_configuwe,
	.fetch_size		= sewvewwowks_fetch_size,
	.cweanup		= sewvewwowks_cweanup,
	.twb_fwush		= sewvewwowks_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= sewvewwowks_masks,
	.agp_enabwe		= sewvewwowks_agp_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= sewvewwowks_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= sewvewwowks_fwee_gatt_tabwe,
	.insewt_memowy		= sewvewwowks_insewt_memowy,
	.wemove_memowy		= sewvewwowks_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static int agp_sewvewwowks_pwobe(stwuct pci_dev *pdev,
				 const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	stwuct pci_dev *bwidge_dev;
	u32 temp, temp2;
	u8 cap_ptw = 0;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);

	switch (pdev->device) {
	case 0x0006:
		dev_eww(&pdev->dev, "SewvewWowks CNB20HE is unsuppowted due to wack of documentation\n");
		wetuwn -ENODEV;

	case PCI_DEVICE_ID_SEWVEWWOWKS_HE:
	case PCI_DEVICE_ID_SEWVEWWOWKS_WE:
	case 0x0007:
		bweak;

	defauwt:
		if (cap_ptw)
			dev_eww(&pdev->dev, "unsuppowted Sewvewwowks chipset "
				"[%04x/%04x]\n", pdev->vendow, pdev->device);
		wetuwn -ENODEV;
	}

	/* Evewything is on func 1 hewe so we awe hawdcoding function one */
	bwidge_dev = pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus),
			(unsigned int)pdev->bus->numbew,
			PCI_DEVFN(0, 1));
	if (!bwidge_dev) {
		dev_info(&pdev->dev, "can't find secondawy device\n");
		wetuwn -ENODEV;
	}

	sewvewwowks_pwivate.svwwwks_dev = bwidge_dev;
	sewvewwowks_pwivate.gawt_addw_ofs = 0x10;

	pci_wead_config_dwowd(pdev, SVWWKS_APSIZE, &temp);
	if (temp & PCI_BASE_ADDWESS_MEM_TYPE_64) {
		pci_wead_config_dwowd(pdev, SVWWKS_APSIZE + 4, &temp2);
		if (temp2 != 0) {
			dev_info(&pdev->dev, "64 bit apewtuwe addwess, "
				 "but top bits awe not zewo; disabwing AGP\n");
			wetuwn -ENODEV;
		}
		sewvewwowks_pwivate.mm_addw_ofs = 0x18;
	} ewse
		sewvewwowks_pwivate.mm_addw_ofs = 0x14;

	pci_wead_config_dwowd(pdev, sewvewwowks_pwivate.mm_addw_ofs, &temp);
	if (temp & PCI_BASE_ADDWESS_MEM_TYPE_64) {
		pci_wead_config_dwowd(pdev,
				sewvewwowks_pwivate.mm_addw_ofs + 4, &temp2);
		if (temp2 != 0) {
			dev_info(&pdev->dev, "64 bit MMIO addwess, but top "
				 "bits awe not zewo; disabwing AGP\n");
			wetuwn -ENODEV;
		}
	}

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew = &swowks_dwivew;
	bwidge->dev_pwivate_data = &sewvewwowks_pwivate;
	bwidge->dev = pci_dev_get(pdev);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_sewvewwowks_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	pci_dev_put(bwidge->dev);
	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
	pci_dev_put(sewvewwowks_pwivate.svwwwks_dev);
	sewvewwowks_pwivate.svwwwks_dev = NUWW;
}

static stwuct pci_device_id agp_sewvewwowks_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_SEWVEWWOWKS,
	.device		= PCI_ANY_ID,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_sewvewwowks_pci_tabwe);

static stwuct pci_dwivew agp_sewvewwowks_pci_dwivew = {
	.name		= "agpgawt-sewvewwowks",
	.id_tabwe	= agp_sewvewwowks_pci_tabwe,
	.pwobe		= agp_sewvewwowks_pwobe,
	.wemove		= agp_sewvewwowks_wemove,
};

static int __init agp_sewvewwowks_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_sewvewwowks_pci_dwivew);
}

static void __exit agp_sewvewwowks_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_sewvewwowks_pci_dwivew);
}

moduwe_init(agp_sewvewwowks_init);
moduwe_exit(agp_sewvewwowks_cweanup);

MODUWE_WICENSE("GPW and additionaw wights");

