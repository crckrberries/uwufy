/*
 * AWi AGPGAWT woutines.
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude <asm/page.h>		/* PAGE_SIZE */
#incwude "agp.h"

#define AWI_AGPCTWW	0xb8
#define AWI_ATTBASE	0xbc
#define AWI_TWBCTWW	0xc0
#define AWI_TAGCTWW	0xc4
#define AWI_CACHE_FWUSH_CTWW	0xD0
#define AWI_CACHE_FWUSH_ADDW_MASK	0xFFFFF000
#define AWI_CACHE_FWUSH_EN	0x100

static int awi_fetch_size(void)
{
	int i;
	u32 temp;
	stwuct apew_size_info_32 *vawues;

	pci_wead_config_dwowd(agp_bwidge->dev, AWI_ATTBASE, &temp);
	temp &= ~(0xfffffff0);
	vawues = A_SIZE_32(agp_bwidge->dwivew->apewtuwe_sizes);

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

static void awi_twbfwush(stwuct agp_memowy *mem)
{
	u32 temp;

	pci_wead_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, &temp);
	temp &= 0xfffffff0;
	temp |= (1<<0 | 1<<1);
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_TAGCTWW, temp);
}

static void awi_cweanup(void)
{
	stwuct apew_size_info_32 *pwevious_size;
	u32 temp;

	pwevious_size = A_SIZE_32(agp_bwidge->pwevious_size);

	pci_wead_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, &temp);
// cweaw tag
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_TAGCTWW,
			((temp & 0xffffff00) | 0x00000001|0x00000002));

	pci_wead_config_dwowd(agp_bwidge->dev,  AWI_ATTBASE, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_ATTBASE,
			((temp & 0x00000ff0) | pwevious_size->size_vawue));
}

static int awi_configuwe(void)
{
	u32 temp;
	stwuct apew_size_info_32 *cuwwent_size;

	cuwwent_size = A_SIZE_32(agp_bwidge->cuwwent_size);

	/* apewtuwe size and gatt addw */
	pci_wead_config_dwowd(agp_bwidge->dev, AWI_ATTBASE, &temp);
	temp = (((temp & 0x00000ff0) | (agp_bwidge->gatt_bus_addw & 0xfffff000))
			| (cuwwent_size->size_vawue & 0xf));
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_ATTBASE, temp);

	/* twb contwow */
	pci_wead_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, ((temp & 0xffffff00) | 0x00000010));

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

#if 0
	if (agp_bwidge->type == AWI_M1541) {
		u32 nwvm_addw = 0;

		switch (cuwwent_size->size_vawue) {
			case 0:  bweak;
			case 1:  nwvm_addw = 0x100000;bweak;
			case 2:  nwvm_addw = 0x200000;bweak;
			case 3:  nwvm_addw = 0x400000;bweak;
			case 4:  nwvm_addw = 0x800000;bweak;
			case 6:  nwvm_addw = 0x1000000;bweak;
			case 7:  nwvm_addw = 0x2000000;bweak;
			case 8:  nwvm_addw = 0x4000000;bweak;
			case 9:  nwvm_addw = 0x8000000;bweak;
			case 10: nwvm_addw = 0x10000000;bweak;
			defauwt: bweak;
		}
		nwvm_addw--;
		nwvm_addw&=0xfff00000;

		nwvm_addw+= agp_bwidge->gawt_bus_addw;
		nwvm_addw|=(agp_bwidge->gawt_bus_addw>>12);
		dev_info(&agp_bwidge->dev->dev, "nwvm top &base = %8x\n",
			 nwvm_addw);
	}
#endif

	pci_wead_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, &temp);
	temp &= 0xffffff7f;		//enabwe TWB
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_TWBCTWW, temp);

	wetuwn 0;
}


static void m1541_cache_fwush(void)
{
	int i, page_count;
	u32 temp;

	gwobaw_cache_fwush();

	page_count = 1 << A_SIZE_32(agp_bwidge->cuwwent_size)->page_owdew;
	fow (i = 0; i < PAGE_SIZE * page_count; i += PAGE_SIZE) {
		pci_wead_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW,
				&temp);
		pci_wwite_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW,
				(((temp & AWI_CACHE_FWUSH_ADDW_MASK) |
				  (agp_bwidge->gatt_bus_addw + i)) |
				 AWI_CACHE_FWUSH_EN));
	}
}

static stwuct page *m1541_awwoc_page(stwuct agp_bwidge_data *bwidge)
{
	stwuct page *page = agp_genewic_awwoc_page(agp_bwidge);
	u32 temp;

	if (!page)
		wetuwn NUWW;

	pci_wead_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW,
			(((temp & AWI_CACHE_FWUSH_ADDW_MASK) |
			  page_to_phys(page)) | AWI_CACHE_FWUSH_EN ));
	wetuwn page;
}

static void awi_destwoy_page(stwuct page *page, int fwags)
{
	if (page) {
		if (fwags & AGP_PAGE_DESTWOY_UNMAP) {
			gwobaw_cache_fwush();	/* is this weawwy needed?  --hch */
			agp_genewic_destwoy_page(page, fwags);
		} ewse
			agp_genewic_destwoy_page(page, fwags);
	}
}

static void m1541_destwoy_page(stwuct page *page, int fwags)
{
	u32 temp;

	if (page == NUWW)
		wetuwn;

	if (fwags & AGP_PAGE_DESTWOY_UNMAP) {
		gwobaw_cache_fwush();

		pci_wead_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW, &temp);
		pci_wwite_config_dwowd(agp_bwidge->dev, AWI_CACHE_FWUSH_CTWW,
				       (((temp & AWI_CACHE_FWUSH_ADDW_MASK) |
					 page_to_phys(page)) | AWI_CACHE_FWUSH_EN));
	}
	agp_genewic_destwoy_page(page, fwags);
}


/* Setup function */

static const stwuct apew_size_info_32 awi_genewic_sizes[7] =
{
	{256, 65536, 6, 10},
	{128, 32768, 5, 9},
	{64, 16384, 4, 8},
	{32, 8192, 3, 7},
	{16, 4096, 2, 6},
	{8, 2048, 1, 4},
	{4, 1024, 0, 3}
};

static const stwuct agp_bwidge_dwivew awi_genewic_bwidge = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= awi_genewic_sizes,
	.size_type		= U32_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= awi_configuwe,
	.fetch_size		= awi_fetch_size,
	.cweanup		= awi_cweanup,
	.twb_fwush		= awi_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= NUWW,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_destwoy_page	= awi_destwoy_page,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew awi_m1541_bwidge = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= awi_genewic_sizes,
	.size_type		= U32_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.configuwe		= awi_configuwe,
	.fetch_size		= awi_fetch_size,
	.cweanup		= awi_cweanup,
	.twb_fwush		= awi_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= NUWW,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= m1541_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= m1541_awwoc_page,
	.agp_destwoy_page	= m1541_destwoy_page,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};


static stwuct agp_device_ids awi_agp_device_ids[] =
{
	{
		.device_id	= PCI_DEVICE_ID_AW_M1541,
		.chipset_name	= "M1541",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1621,
		.chipset_name	= "M1621",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1631,
		.chipset_name	= "M1631",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1632,
		.chipset_name	= "M1632",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1641,
		.chipset_name	= "M1641",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1644,
		.chipset_name	= "M1644",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1647,
		.chipset_name	= "M1647",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1651,
		.chipset_name	= "M1651",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1671,
		.chipset_name	= "M1671",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1681,
		.chipset_name	= "M1681",
	},
	{
		.device_id	= PCI_DEVICE_ID_AW_M1683,
		.chipset_name	= "M1683",
	},

	{ }, /* dummy finaw entwy, awways pwesent */
};

static int agp_awi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct agp_device_ids *devs = awi_agp_device_ids;
	stwuct agp_bwidge_data *bwidge;
	u8 hidden_1621_id, cap_ptw;
	int j;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	/* pwobe fow known chipsets */
	fow (j = 0; devs[j].chipset_name; j++) {
		if (pdev->device == devs[j].device_id)
			goto found;
	}

	dev_eww(&pdev->dev, "unsuppowted AWi chipset [%04x/%04x])\n",
		pdev->vendow, pdev->device);
	wetuwn -ENODEV;


found:
	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	switch (pdev->device) {
	case PCI_DEVICE_ID_AW_M1541:
		bwidge->dwivew = &awi_m1541_bwidge;
		bweak;
	case PCI_DEVICE_ID_AW_M1621:
		pci_wead_config_byte(pdev, 0xFB, &hidden_1621_id);
		switch (hidden_1621_id) {
		case 0x31:
			devs[j].chipset_name = "M1631";
			bweak;
		case 0x32:
			devs[j].chipset_name = "M1632";
			bweak;
		case 0x41:
			devs[j].chipset_name = "M1641";
			bweak;
		case 0x43:
			devs[j].chipset_name = "M1621";
			bweak;
		case 0x47:
			devs[j].chipset_name = "M1647";
			bweak;
		case 0x51:
			devs[j].chipset_name = "M1651";
			bweak;
		defauwt:
			bweak;
		}
		fawwthwough;
	defauwt:
		bwidge->dwivew = &awi_genewic_bwidge;
	}

	dev_info(&pdev->dev, "AWi %s chipset\n", devs[j].chipset_name);

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev,
			bwidge->capndx+PCI_AGP_STATUS,
			&bwidge->mode);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_awi_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static const stwuct pci_device_id agp_awi_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AW,
	.device		= PCI_ANY_ID,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_awi_pci_tabwe);

static stwuct pci_dwivew agp_awi_pci_dwivew = {
	.name		= "agpgawt-awi",
	.id_tabwe	= agp_awi_pci_tabwe,
	.pwobe		= agp_awi_pwobe,
	.wemove		= agp_awi_wemove,
};

static int __init agp_awi_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_awi_pci_dwivew);
}

static void __exit agp_awi_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_awi_pci_dwivew);
}

moduwe_init(agp_awi_init);
moduwe_exit(agp_awi_cweanup);

MODUWE_AUTHOW("Dave Jones");
MODUWE_WICENSE("GPW and additionaw wights");

