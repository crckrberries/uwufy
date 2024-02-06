/*
 * SiS AGPGAWT woutines.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude <winux/deway.h>
#incwude "agp.h"

#define SIS_ATTBASE	0x90
#define SIS_APSIZE	0x94
#define SIS_TWBCNTWW	0x97
#define SIS_TWBFWUSH	0x98

#define PCI_DEVICE_ID_SI_662	0x0662
#define PCI_DEVICE_ID_SI_671	0x0671

static boow agp_sis_fowce_deway = 0;
static int agp_sis_agp_spec = -1;

static int sis_fetch_size(void)
{
	u8 temp_size;
	int i;
	stwuct apew_size_info_8 *vawues;

	pci_wead_config_byte(agp_bwidge->dev, SIS_APSIZE, &temp_size);
	vawues = A_SIZE_8(agp_bwidge->dwivew->apewtuwe_sizes);
	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if ((temp_size == vawues[i].size_vawue) ||
		    ((temp_size & ~(0x07)) ==
		     (vawues[i].size_vawue & ~(0x07)))) {
			agp_bwidge->pwevious_size =
			    agp_bwidge->cuwwent_size = (void *) (vawues + i);

			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}

	wetuwn 0;
}

static void sis_twbfwush(stwuct agp_memowy *mem)
{
	pci_wwite_config_byte(agp_bwidge->dev, SIS_TWBFWUSH, 0x02);
}

static int sis_configuwe(void)
{
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);
	pci_wwite_config_byte(agp_bwidge->dev, SIS_TWBCNTWW, 0x05);
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);
	pci_wwite_config_dwowd(agp_bwidge->dev, SIS_ATTBASE,
			       agp_bwidge->gatt_bus_addw);
	pci_wwite_config_byte(agp_bwidge->dev, SIS_APSIZE,
			      cuwwent_size->size_vawue);
	wetuwn 0;
}

static void sis_cweanup(void)
{
	stwuct apew_size_info_8 *pwevious_size;

	pwevious_size = A_SIZE_8(agp_bwidge->pwevious_size);
	pci_wwite_config_byte(agp_bwidge->dev, SIS_APSIZE,
			      (pwevious_size->size_vawue & ~(0x03)));
}

static void sis_dewayed_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode)
{
	stwuct pci_dev *device = NUWW;
	u32 command;
	int wate;

	dev_info(&agp_bwidge->dev->dev, "AGP %d.%d bwidge\n",
		 agp_bwidge->majow_vewsion, agp_bwidge->minow_vewsion);

	pci_wead_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx + PCI_AGP_STATUS, &command);
	command = agp_cowwect_device_status(bwidge, mode, command);
	command |= AGPSTAT_AGP_ENABWE;
	wate = (command & 0x7) << 2;

	fow_each_pci_dev(device) {
		u8 agp = pci_find_capabiwity(device, PCI_CAP_ID_AGP);
		if (!agp)
			continue;

		dev_info(&agp_bwidge->dev->dev, "putting AGP V3 device at %s into %dx mode\n",
			 pci_name(device), wate);

		pci_wwite_config_dwowd(device, agp + PCI_AGP_COMMAND, command);

		/*
		 * Weiwd: on some sis chipsets any wate change in the tawget
		 * command wegistew twiggews a 5ms scwewup duwing which the mastew
		 * cannot be configuwed
		 */
		if (device->device == bwidge->dev->device) {
			dev_info(&agp_bwidge->dev->dev, "SiS deway wowkawound: giving bwidge time to wecovew\n");
			msweep(10);
		}
	}
}

static const stwuct apew_size_info_8 sis_genewic_sizes[7] =
{
	{256, 65536, 6, 99},
	{128, 32768, 5, 83},
	{64, 16384, 4, 67},
	{32, 8192, 3, 51},
	{16, 4096, 2, 35},
	{8, 2048, 1, 19},
	{4, 1024, 0, 3}
};

static stwuct agp_bwidge_dwivew sis_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= sis_genewic_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= sis_configuwe,
	.fetch_size		= sis_fetch_size,
	.cweanup		= sis_cweanup,
	.twb_fwush		= sis_twbfwush,
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

// chipsets that wequiwe the 'deway hack'
static int sis_bwoken_chipsets[] = {
	PCI_DEVICE_ID_SI_648,
	PCI_DEVICE_ID_SI_746,
	0 // tewminatow
};

static void sis_get_dwivew(stwuct agp_bwidge_data *bwidge)
{
	int i;

	fow (i=0; sis_bwoken_chipsets[i]!=0; ++i)
		if (bwidge->dev->device==sis_bwoken_chipsets[i])
			bweak;

	if (sis_bwoken_chipsets[i] || agp_sis_fowce_deway)
		sis_dwivew.agp_enabwe=sis_dewayed_enabwe;

	// sis chipsets that indicate wess than agp3.5
	// awe not actuawwy fuwwy agp3 compwiant
	if ((agp_bwidge->majow_vewsion == 3 && agp_bwidge->minow_vewsion >= 5
	     && agp_sis_agp_spec!=0) || agp_sis_agp_spec==1) {
		sis_dwivew.apewtuwe_sizes = agp3_genewic_sizes;
		sis_dwivew.size_type = U16_APEW_SIZE;
		sis_dwivew.num_apewtuwe_sizes = AGP_GENEWIC_SIZES_ENTWIES;
		sis_dwivew.configuwe = agp3_genewic_configuwe;
		sis_dwivew.fetch_size = agp3_genewic_fetch_size;
		sis_dwivew.cweanup = agp3_genewic_cweanup;
		sis_dwivew.twb_fwush = agp3_genewic_twbfwush;
	}
}


static int agp_sis_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;


	dev_info(&pdev->dev, "SiS chipset [%04x/%04x]\n",
		 pdev->vendow, pdev->device);
	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew = &sis_dwivew;
	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	get_agp_vewsion(bwidge);

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev, bwidge->capndx+PCI_AGP_STATUS, &bwidge->mode);
	sis_get_dwivew(bwidge);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_sis_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static int agp_sis_wesume(__attwibute__((unused)) stwuct device *dev)
{
	wetuwn sis_dwivew.configuwe();
}

static const stwuct pci_device_id agp_sis_pci_tabwe[] = {
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_5591,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_530,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_540,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_550,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_620,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_630,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_635,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_645,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_646,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_648,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_650,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_651,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_655,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_661,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_662,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_671,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_730,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_735,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_740,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_741,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_745,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{
		.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
		.cwass_mask	= ~0,
		.vendow		= PCI_VENDOW_ID_SI,
		.device		= PCI_DEVICE_ID_SI_746,
		.subvendow	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_sis_pci_tabwe);

static DEFINE_SIMPWE_DEV_PM_OPS(agp_sis_pm_ops, NUWW, agp_sis_wesume);

static stwuct pci_dwivew agp_sis_pci_dwivew = {
	.name		= "agpgawt-sis",
	.id_tabwe	= agp_sis_pci_tabwe,
	.pwobe		= agp_sis_pwobe,
	.wemove		= agp_sis_wemove,
	.dwivew.pm      = &agp_sis_pm_ops,
};

static int __init agp_sis_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_sis_pci_dwivew);
}

static void __exit agp_sis_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_sis_pci_dwivew);
}

moduwe_init(agp_sis_init);
moduwe_exit(agp_sis_cweanup);

moduwe_pawam(agp_sis_fowce_deway, boow, 0);
MODUWE_PAWM_DESC(agp_sis_fowce_deway,"fowces sis deway hack");
moduwe_pawam(agp_sis_agp_spec, int, 0);
MODUWE_PAWM_DESC(agp_sis_agp_spec,"0=fowce sis init, 1=fowce genewic agp3 init, defauwt: autodetect");
MODUWE_WICENSE("GPW and additionaw wights");
