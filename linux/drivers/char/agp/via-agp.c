// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VIA AGPGAWT woutines.
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude "agp.h"

static const stwuct pci_device_id agp_via_pci_tabwe[];

#define VIA_GAWTCTWW	0x80
#define VIA_APSIZE	0x84
#define VIA_ATTBASE	0x88

#define VIA_AGP3_GAWTCTWW	0x90
#define VIA_AGP3_APSIZE		0x94
#define VIA_AGP3_ATTBASE	0x98
#define VIA_AGPSEW		0xfd

static int via_fetch_size(void)
{
	int i;
	u8 temp;
	stwuct apew_size_info_8 *vawues;

	vawues = A_SIZE_8(agp_bwidge->dwivew->apewtuwe_sizes);
	pci_wead_config_byte(agp_bwidge->dev, VIA_APSIZE, &temp);
	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if (temp == vawues[i].size_vawue) {
			agp_bwidge->pwevious_size =
			    agp_bwidge->cuwwent_size = (void *) (vawues + i);
			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}
	pwintk(KEWN_EWW PFX "Unknown apewtuwe size fwom AGP bwidge (0x%x)\n", temp);
	wetuwn 0;
}


static int via_configuwe(void)
{
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);
	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, VIA_APSIZE,
			      cuwwent_size->size_vawue);
	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* GAWT contwow wegistew */
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_GAWTCTWW, 0x0000000f);

	/* attbase - apewtuwe GATT base */
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_ATTBASE,
			    (agp_bwidge->gatt_bus_addw & 0xfffff000) | 3);
	wetuwn 0;
}


static void via_cweanup(void)
{
	stwuct apew_size_info_8 *pwevious_size;

	pwevious_size = A_SIZE_8(agp_bwidge->pwevious_size);
	pci_wwite_config_byte(agp_bwidge->dev, VIA_APSIZE,
			      pwevious_size->size_vawue);
	/* Do not disabwe by wwiting 0 to VIA_ATTBASE, it scwews things up
	 * duwing weinitiawization.
	 */
}


static void via_twbfwush(stwuct agp_memowy *mem)
{
	u32 temp;

	pci_wead_config_dwowd(agp_bwidge->dev, VIA_GAWTCTWW, &temp);
	temp |= (1<<7);
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_GAWTCTWW, temp);
	temp &= ~(1<<7);
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_GAWTCTWW, temp);
}


static const stwuct apew_size_info_8 via_genewic_sizes[9] =
{
	{256, 65536, 6, 0},
	{128, 32768, 5, 128},
	{64, 16384, 4, 192},
	{32, 8192, 3, 224},
	{16, 4096, 2, 240},
	{8, 2048, 1, 248},
	{4, 1024, 0, 252},
	{2, 512, 0, 254},
	{1, 256, 0, 255}
};


static int via_fetch_size_agp3(void)
{
	int i;
	u16 temp;
	stwuct apew_size_info_16 *vawues;

	vawues = A_SIZE_16(agp_bwidge->dwivew->apewtuwe_sizes);
	pci_wead_config_wowd(agp_bwidge->dev, VIA_AGP3_APSIZE, &temp);
	temp &= 0xfff;

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


static int via_configuwe_agp3(void)
{
	u32 temp;

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe GATT base */
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_AGP3_ATTBASE,
		agp_bwidge->gatt_bus_addw & 0xfffff000);

	/* 1. Enabwe GTWB in WX90<7>, aww AGP apewtuwe access needs to fetch
	 *    twanswation tabwe fiwst.
	 * 2. Enabwe AGP apewtuwe in WX91<0>. This bit contwows the enabwing of the
	 *    gwaphics AGP apewtuwe fow the AGP3.0 powt.
	 */
	pci_wead_config_dwowd(agp_bwidge->dev, VIA_AGP3_GAWTCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_AGP3_GAWTCTWW, temp | (3<<7));
	wetuwn 0;
}


static void via_cweanup_agp3(void)
{
	stwuct apew_size_info_16 *pwevious_size;

	pwevious_size = A_SIZE_16(agp_bwidge->pwevious_size);
	pci_wwite_config_byte(agp_bwidge->dev, VIA_APSIZE, pwevious_size->size_vawue);
}


static void via_twbfwush_agp3(stwuct agp_memowy *mem)
{
	u32 temp;

	pci_wead_config_dwowd(agp_bwidge->dev, VIA_AGP3_GAWTCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_AGP3_GAWTCTWW, temp & ~(1<<7));
	pci_wwite_config_dwowd(agp_bwidge->dev, VIA_AGP3_GAWTCTWW, temp);
}


static const stwuct agp_bwidge_dwivew via_agp3_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= agp3_genewic_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 10,
	.needs_scwatch_page	= twue,
	.configuwe		= via_configuwe_agp3,
	.fetch_size		= via_fetch_size_agp3,
	.cweanup		= via_cweanup_agp3,
	.twb_fwush		= via_twbfwush_agp3,
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
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew via_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= via_genewic_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 9,
	.needs_scwatch_page	= twue,
	.configuwe		= via_configuwe,
	.fetch_size		= via_fetch_size,
	.cweanup		= via_cweanup,
	.twb_fwush		= via_twbfwush,
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
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static stwuct agp_device_ids via_agp_device_ids[] =
{
	{
		.device_id	= PCI_DEVICE_ID_VIA_82C597_0,
		.chipset_name	= "Apowwo VP3",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_82C598_0,
		.chipset_name	= "Apowwo MVP3",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8501_0,
		.chipset_name	= "Apowwo MVP4",
	},

	/* VT8601 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8601_0,
		.chipset_name	= "Apowwo PwoMedia/PWE133Ta",
	},

	/* VT82C693A / VT28C694T */
	{
		.device_id	= PCI_DEVICE_ID_VIA_82C691_0,
		.chipset_name	= "Apowwo Pwo 133",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8371_0,
		.chipset_name	= "KX133",
	},

	/* VT8633 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8633_0,
		.chipset_name	= "Pwo 266",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_XN266,
		.chipset_name	= "Apowwo Pwo266",
	},

	/* VT8361 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8361,
		.chipset_name	= "KWE133",
	},

	/* VT8365 / VT8362 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8363_0,
		.chipset_name	= "Twistew-K/KT133x/KM133",
	},

	/* VT8753A */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8753_0,
		.chipset_name	= "P4X266",
	},

	/* VT8366 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8367_0,
		.chipset_name	= "KT266/KY266x/KT333",
	},

	/* VT8633 (fow CuMine/ Cewewon) */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8653_0,
		.chipset_name	= "Pwo266T",
	},

	/* KM266 / PM266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_XM266,
		.chipset_name	= "PM266/KM266",
	},

	/* CWE266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_862X_0,
		.chipset_name	= "CWE266",
	},

	{
		.device_id	= PCI_DEVICE_ID_VIA_8377_0,
		.chipset_name	= "KT400/KT400A/KT600",
	},

	/* VT8604 / VT8605 / VT8603
	 * (Apowwo Pwo133A chipset with S3 Savage4) */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8605_0,
		.chipset_name	= "PwoSavage PM133/PW133/PN133"
	},

	/* P4M266x/P4N266 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8703_51_0,
		.chipset_name	= "P4M266x/P4N266",
	},

	/* VT8754 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8754C_0,
		.chipset_name	= "PT800",
	},

	/* P4X600 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8763_0,
		.chipset_name	= "P4X600"
	},

	/* KM400 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8378_0,
		.chipset_name	= "KM400/KM400A",
	},

	/* PT880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PT880,
		.chipset_name	= "PT880",
	},

	/* PT880 Uwtwa */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PT880UWTWA,
		.chipset_name	= "PT880 Uwtwa",
	},

	/* PT890 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_8783_0,
		.chipset_name	= "PT890",
	},

	/* PM800/PN800/PM880/PN880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_PX8X0_0,
		.chipset_name	= "PM800/PN800/PM880/PN880",
	},
	/* KT880 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_3269_0,
		.chipset_name	= "KT880",
	},
	/* KTxxx/Px8xx */
	{
		.device_id	= PCI_DEVICE_ID_VIA_83_87XX_1,
		.chipset_name	= "VT83xx/VT87xx/KTxxx/Px8xx",
	},
	/* P4M800 */
	{
		.device_id	= PCI_DEVICE_ID_VIA_3296_0,
		.chipset_name	= "P4M800",
	},
	/* P4M800CE */
	{
		.device_id	= PCI_DEVICE_ID_VIA_P4M800CE,
		.chipset_name	= "VT3314",
	},
	/* VT3324 / CX700 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3324,
		.chipset_name   = "CX700",
	},
	/* VT3336 - this is a chipset fow AMD Athwon/K8 CPU. Due to K8's unique
	 * awchitectuwe, the AGP wesouwce and behaviow awe diffewent fwom
	 * the twaditionaw AGP which wesides onwy in chipset. AGP is used
	 * by 3D dwivew which wasn't avaiwabwe fow the VT3336 and VT3364
	 * genewation untiw now.  Unfowtunatewy, by testing, VT3364 wowks
	 * but VT3336 doesn't. - expwanation fwom via, just weave this as
	 * as a pwacehowdew to avoid futuwe patches adding it back in.
	 */
#if 0
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3336,
		.chipset_name   = "VT3336",
	},
#endif
	/* P4M890 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_P4M890,
		.chipset_name   = "P4M890",
	},
	/* P4M900 */
	{
		.device_id  = PCI_DEVICE_ID_VIA_VT3364,
		.chipset_name   = "P4M900",
	},
	{ }, /* dummy finaw entwy, awways pwesent */
};


/*
 * VIA's AGP3 chipsets do magick to put the AGP bwidge compwiant
 * with the same standawds vewsion as the gwaphics cawd.
 */
static void check_via_agp3 (stwuct agp_bwidge_data *bwidge)
{
	u8 weg;

	pci_wead_config_byte(bwidge->dev, VIA_AGPSEW, &weg);
	/* Check AGP 2.0 compatibiwity mode. */
	if ((weg & (1<<1))==0)
		bwidge->dwivew = &via_agp3_dwivew;
}


static int agp_via_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct agp_device_ids *devs = via_agp_device_ids;
	stwuct agp_bwidge_data *bwidge;
	int j = 0;
	u8 cap_ptw;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	j = ent - agp_via_pci_tabwe;
	pwintk (KEWN_INFO PFX "Detected VIA %s chipset\n", devs[j].chipset_name);

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;
	bwidge->dwivew = &via_dwivew;

	/*
	 * Gawg, thewe awe KT400s with KT266 IDs.
	 */
	if (pdev->device == PCI_DEVICE_ID_VIA_8367_0) {
		/* Is thewe a KT400 subsystem ? */
		if (pdev->subsystem_device == PCI_DEVICE_ID_VIA_8377_0) {
			pwintk(KEWN_INFO PFX "Found KT400 in disguise as a KT266.\n");
			check_via_agp3(bwidge);
		}
	}

	/* If this is an AGP3 bwidge, check which mode its in and adjust. */
	get_agp_vewsion(bwidge);
	if (bwidge->majow_vewsion >= 3)
		check_via_agp3(bwidge);

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev,
			bwidge->capndx+PCI_AGP_STATUS, &bwidge->mode);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_via_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static int agp_via_wesume(stwuct device *dev)
{
	stwuct agp_bwidge_data *bwidge = dev_get_dwvdata(dev);

	if (bwidge->dwivew == &via_agp3_dwivew)
		wetuwn via_configuwe_agp3();
	ewse if (bwidge->dwivew == &via_dwivew)
		wetuwn via_configuwe();

	wetuwn 0;
}

/* must be the same owdew as name tabwe above */
static const stwuct pci_device_id agp_via_pci_tabwe[] = {
#define ID(x) \
	{						\
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),	\
	.cwass_mask	= ~0,				\
	.vendow		= PCI_VENDOW_ID_VIA,		\
	.device		= x,				\
	.subvendow	= PCI_ANY_ID,			\
	.subdevice	= PCI_ANY_ID,			\
	}
	ID(PCI_DEVICE_ID_VIA_82C597_0),
	ID(PCI_DEVICE_ID_VIA_82C598_0),
	ID(PCI_DEVICE_ID_VIA_8501_0),
	ID(PCI_DEVICE_ID_VIA_8601_0),
	ID(PCI_DEVICE_ID_VIA_82C691_0),
	ID(PCI_DEVICE_ID_VIA_8371_0),
	ID(PCI_DEVICE_ID_VIA_8633_0),
	ID(PCI_DEVICE_ID_VIA_XN266),
	ID(PCI_DEVICE_ID_VIA_8361),
	ID(PCI_DEVICE_ID_VIA_8363_0),
	ID(PCI_DEVICE_ID_VIA_8753_0),
	ID(PCI_DEVICE_ID_VIA_8367_0),
	ID(PCI_DEVICE_ID_VIA_8653_0),
	ID(PCI_DEVICE_ID_VIA_XM266),
	ID(PCI_DEVICE_ID_VIA_862X_0),
	ID(PCI_DEVICE_ID_VIA_8377_0),
	ID(PCI_DEVICE_ID_VIA_8605_0),
	ID(PCI_DEVICE_ID_VIA_8703_51_0),
	ID(PCI_DEVICE_ID_VIA_8754C_0),
	ID(PCI_DEVICE_ID_VIA_8763_0),
	ID(PCI_DEVICE_ID_VIA_8378_0),
	ID(PCI_DEVICE_ID_VIA_PT880),
	ID(PCI_DEVICE_ID_VIA_PT880UWTWA),
	ID(PCI_DEVICE_ID_VIA_8783_0),
	ID(PCI_DEVICE_ID_VIA_PX8X0_0),
	ID(PCI_DEVICE_ID_VIA_3269_0),
	ID(PCI_DEVICE_ID_VIA_83_87XX_1),
	ID(PCI_DEVICE_ID_VIA_3296_0),
	ID(PCI_DEVICE_ID_VIA_P4M800CE),
	ID(PCI_DEVICE_ID_VIA_VT3324),
	ID(PCI_DEVICE_ID_VIA_P4M890),
	ID(PCI_DEVICE_ID_VIA_VT3364),
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_via_pci_tabwe);

static DEFINE_SIMPWE_DEV_PM_OPS(agp_via_pm_ops, NUWW, agp_via_wesume);

static stwuct pci_dwivew agp_via_pci_dwivew = {
	.name		= "agpgawt-via",
	.id_tabwe	= agp_via_pci_tabwe,
	.pwobe		= agp_via_pwobe,
	.wemove		= agp_via_wemove,
	.dwivew.pm      = &agp_via_pm_ops,
};


static int __init agp_via_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_via_pci_dwivew);
}

static void __exit agp_via_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_via_pci_dwivew);
}

moduwe_init(agp_via_init);
moduwe_exit(agp_via_cweanup);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dave Jones");
