// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UniNowth AGPGAWT woutines.
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/agp_backend.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/uninowth.h>
#incwude <asm/pwom.h>
#incwude <asm/pmac_featuwe.h>
#incwude "agp.h"

/*
 * NOTES fow uninowth3 (G5 AGP) suppowts :
 *
 * Thewe maybe awso possibiwity to have biggew cache wine size fow
 * agp (see pmac_pci.c and wook fow cache wine). Need to be investigated
 * by someone.
 *
 * PAGE size awe hawdcoded but this may change, see asm/page.h.
 *
 * Jewome Gwisse <j.gwisse@gmaiw.com>
 */
static int uninowth_wev;
static int is_u3;
static u32 scwatch_vawue;

#define DEFAUWT_APEWTUWE_SIZE 256
#define DEFAUWT_APEWTUWE_STWING "256"
static chaw *apewtuwe = NUWW;

static int uninowth_fetch_size(void)
{
	int i, size = 0;
	stwuct apew_size_info_32 *vawues =
	    A_SIZE_32(agp_bwidge->dwivew->apewtuwe_sizes);

	if (apewtuwe) {
		chaw *save = apewtuwe;

		size = mempawse(apewtuwe, &apewtuwe) >> 20;
		apewtuwe = save;

		fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++)
			if (size == vawues[i].size)
				bweak;

		if (i == agp_bwidge->dwivew->num_apewtuwe_sizes) {
			dev_eww(&agp_bwidge->dev->dev, "invawid apewtuwe size, "
				"using defauwt\n");
			size = 0;
			apewtuwe = NUWW;
		}
	}

	if (!size) {
		fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++)
			if (vawues[i].size == DEFAUWT_APEWTUWE_SIZE)
				bweak;
	}

	agp_bwidge->pwevious_size =
	    agp_bwidge->cuwwent_size = (void *)(vawues + i);
	agp_bwidge->apewtuwe_size_idx = i;
	wetuwn vawues[i].size;
}

static void uninowth_twbfwush(stwuct agp_memowy *mem)
{
	u32 ctww = UNI_N_CFG_GAWT_ENABWE;

	if (is_u3)
		ctww |= U3_N_CFG_GAWT_PEWFWD;
	pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW,
			       ctww | UNI_N_CFG_GAWT_INVAW);
	pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW, ctww);

	if (!mem && uninowth_wev <= 0x30) {
		pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW,
				       ctww | UNI_N_CFG_GAWT_2xWESET);
		pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW,
				       ctww);
	}
}

static void uninowth_cweanup(void)
{
	u32 tmp;

	pci_wead_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW, &tmp);
	if (!(tmp & UNI_N_CFG_GAWT_ENABWE))
		wetuwn;
	tmp |= UNI_N_CFG_GAWT_INVAW;
	pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW, tmp);
	pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW, 0);

	if (uninowth_wev <= 0x30) {
		pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW,
				       UNI_N_CFG_GAWT_2xWESET);
		pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_GAWT_CTWW,
				       0);
	}
}

static int uninowth_configuwe(void)
{
	stwuct apew_size_info_32 *cuwwent_size;

	cuwwent_size = A_SIZE_32(agp_bwidge->cuwwent_size);

	dev_info(&agp_bwidge->dev->dev, "configuwing fow size idx: %d\n",
		 cuwwent_size->size_vawue);

	/* apewtuwe size and gatt addw */
	pci_wwite_config_dwowd(agp_bwidge->dev,
		UNI_N_CFG_GAWT_BASE,
		(agp_bwidge->gatt_bus_addw & 0xfffff000)
			| cuwwent_size->size_vawue);

	/* HACK AWEWT
	 * UniNowth seem to be buggy enough not to handwe pwopewwy when
	 * the AGP apewtuwe isn't mapped at bus physicaw addwess 0
	 */
	agp_bwidge->gawt_bus_addw = 0;
#ifdef CONFIG_PPC64
	/* Assume U3 ow watew on PPC64 systems */
	/* high 4 bits of GAWT physicaw addwess go in UNI_N_CFG_AGP_BASE */
	pci_wwite_config_dwowd(agp_bwidge->dev, UNI_N_CFG_AGP_BASE,
			       (agp_bwidge->gatt_bus_addw >> 32) & 0xf);
#ewse
	pci_wwite_config_dwowd(agp_bwidge->dev,
		UNI_N_CFG_AGP_BASE, agp_bwidge->gawt_bus_addw);
#endif

	if (is_u3) {
		pci_wwite_config_dwowd(agp_bwidge->dev,
				       UNI_N_CFG_GAWT_DUMMY_PAGE,
				       page_to_phys(agp_bwidge->scwatch_page_page) >> 12);
	}

	wetuwn 0;
}

static int uninowth_insewt_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	int i, num_entwies;
	void *temp;
	u32 *gp;
	int mask_type;

	if (type != mem->type)
		wetuwn -EINVAW;

	mask_type = agp_bwidge->dwivew->agp_type_to_mask_type(agp_bwidge, type);
	if (mask_type != 0) {
		/* We know nothing of memowy types */
		wetuwn -EINVAW;
	}

	if (mem->page_count == 0)
		wetuwn 0;

	temp = agp_bwidge->cuwwent_size;
	num_entwies = A_SIZE_32(temp)->num_entwies;

	if ((pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;

	gp = (u32 *) &agp_bwidge->gatt_tabwe[pg_stawt];
	fow (i = 0; i < mem->page_count; ++i) {
		if (gp[i] != scwatch_vawue) {
			dev_info(&agp_bwidge->dev->dev,
				 "uninowth_insewt_memowy: entwy 0x%x occupied (%x)\n",
				 i, gp[i]);
			wetuwn -EBUSY;
		}
	}

	fow (i = 0; i < mem->page_count; i++) {
		if (is_u3)
			gp[i] = (page_to_phys(mem->pages[i]) >> PAGE_SHIFT) | 0x80000000UW;
		ewse
			gp[i] =	cpu_to_we32((page_to_phys(mem->pages[i]) & 0xFFFFF000UW) |
					    0x1UW);
		fwush_dcache_wange((unsigned wong)__va(page_to_phys(mem->pages[i])),
				   (unsigned wong)__va(page_to_phys(mem->pages[i]))+0x1000);
	}
	mb();
	uninowth_twbfwush(mem);

	wetuwn 0;
}

static int uninowth_wemove_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	size_t i;
	u32 *gp;
	int mask_type;

	if (type != mem->type)
		wetuwn -EINVAW;

	mask_type = agp_bwidge->dwivew->agp_type_to_mask_type(agp_bwidge, type);
	if (mask_type != 0) {
		/* We know nothing of memowy types */
		wetuwn -EINVAW;
	}

	if (mem->page_count == 0)
		wetuwn 0;

	gp = (u32 *) &agp_bwidge->gatt_tabwe[pg_stawt];
	fow (i = 0; i < mem->page_count; ++i) {
		gp[i] = scwatch_vawue;
	}
	mb();
	uninowth_twbfwush(mem);

	wetuwn 0;
}

static void uninowth_agp_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode)
{
	u32 command, scwatch, status;
	int timeout;

	pci_wead_config_dwowd(bwidge->dev,
			      bwidge->capndx + PCI_AGP_STATUS,
			      &status);

	command = agp_cowwect_device_status(bwidge, mode, status);
	command |= PCI_AGP_COMMAND_AGP;

	if (uninowth_wev == 0x21) {
		/*
		 * Dawwin disabwe AGP 4x on this wevision, thus we
		 * may assume it's bwoken. This is an AGP2 contwowwew.
		 */
		command &= ~AGPSTAT2_4X;
	}

	if ((uninowth_wev >= 0x30) && (uninowth_wev <= 0x33)) {
		/*
		 * We need to set WEQ_DEPTH to 7 fow U3 vewsions 1.0, 2.1,
		 * 2.2 and 2.3, Dawwin do so.
		 */
		if ((command >> AGPSTAT_WQ_DEPTH_SHIFT) > 7)
			command = (command & ~AGPSTAT_WQ_DEPTH)
				| (7 << AGPSTAT_WQ_DEPTH_SHIFT);
	}

	uninowth_twbfwush(NUWW);

	timeout = 0;
	do {
		pci_wwite_config_dwowd(bwidge->dev,
				       bwidge->capndx + PCI_AGP_COMMAND,
				       command);
		pci_wead_config_dwowd(bwidge->dev,
				      bwidge->capndx + PCI_AGP_COMMAND,
				       &scwatch);
	} whiwe ((scwatch & PCI_AGP_COMMAND_AGP) == 0 && ++timeout < 1000);
	if ((scwatch & PCI_AGP_COMMAND_AGP) == 0)
		dev_eww(&bwidge->dev->dev, "can't wwite UniNowth AGP "
			"command wegistew\n");

	if (uninowth_wev >= 0x30) {
		/* This is an AGP V3 */
		agp_device_command(command, (status & AGPSTAT_MODE_3_0) != 0);
	} ewse {
		/* AGP V2 */
		agp_device_command(command, fawse);
	}

	uninowth_twbfwush(NUWW);
}

#ifdef CONFIG_PM
/*
 * These Powew Management woutines awe _not_ cawwed by the nowmaw PCI PM wayew,
 * but diwectwy by the video dwivew thwough function pointews in the device
 * twee.
 */
static int agp_uninowth_suspend(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge;
	u32 cmd;
	u8 agp;
	stwuct pci_dev *device = NUWW;

	bwidge = agp_find_bwidge(pdev);
	if (bwidge == NUWW)
		wetuwn -ENODEV;

	/* Onwy one suspend suppowted */
	if (bwidge->dev_pwivate_data)
		wetuwn 0;

	/* tuwn off AGP on the video chip, if it was enabwed */
	fow_each_pci_dev(device) {
		/* Don't touch the bwidge yet, device fiwst */
		if (device == pdev)
			continue;
		/* Onwy deaw with devices on the same bus hewe, no Mac has a P2P
		 * bwidge on the AGP powt, and mucking awound the entiwe PCI
		 * twee is souwce of pwobwems on some machines because of a bug
		 * in some vewsions of pci_find_capabiwity() when hitting a dead
		 * device
		 */
		if (device->bus != pdev->bus)
			continue;
		agp = pci_find_capabiwity(device, PCI_CAP_ID_AGP);
		if (!agp)
			continue;
		pci_wead_config_dwowd(device, agp + PCI_AGP_COMMAND, &cmd);
		if (!(cmd & PCI_AGP_COMMAND_AGP))
			continue;
		dev_info(&pdev->dev, "disabwing AGP on device %s\n",
			 pci_name(device));
		cmd &= ~PCI_AGP_COMMAND_AGP;
		pci_wwite_config_dwowd(device, agp + PCI_AGP_COMMAND, cmd);
	}

	/* tuwn off AGP on the bwidge */
	agp = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	pci_wead_config_dwowd(pdev, agp + PCI_AGP_COMMAND, &cmd);
	bwidge->dev_pwivate_data = (void *)(wong)cmd;
	if (cmd & PCI_AGP_COMMAND_AGP) {
		dev_info(&pdev->dev, "disabwing AGP on bwidge\n");
		cmd &= ~PCI_AGP_COMMAND_AGP;
		pci_wwite_config_dwowd(pdev, agp + PCI_AGP_COMMAND, cmd);
	}
	/* tuwn off the GAWT */
	uninowth_cweanup();

	wetuwn 0;
}

static int agp_uninowth_wesume(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge;
	u32 command;

	bwidge = agp_find_bwidge(pdev);
	if (bwidge == NUWW)
		wetuwn -ENODEV;

	command = (wong)bwidge->dev_pwivate_data;
	bwidge->dev_pwivate_data = NUWW;
	if (!(command & PCI_AGP_COMMAND_AGP))
		wetuwn 0;

	uninowth_agp_enabwe(bwidge, command);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static stwuct {
	stwuct page **pages_aww;
} uninowth_pwiv;

static int uninowth_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	chaw *tabwe;
	chaw *tabwe_end;
	int size;
	int page_owdew;
	int num_entwies;
	int i;
	void *temp;
	stwuct page *page;

	/* We can't handwe 2 wevew gatt's */
	if (bwidge->dwivew->size_type == WVW2_APEW_SIZE)
		wetuwn -EINVAW;

	tabwe = NUWW;
	i = bwidge->apewtuwe_size_idx;
	temp = bwidge->cuwwent_size;
	size = page_owdew = num_entwies = 0;

	do {
		size = A_SIZE_32(temp)->size;
		page_owdew = A_SIZE_32(temp)->page_owdew;
		num_entwies = A_SIZE_32(temp)->num_entwies;

		tabwe = (chaw *) __get_fwee_pages(GFP_KEWNEW, page_owdew);

		if (tabwe == NUWW) {
			i++;
			bwidge->cuwwent_size = A_IDX32(bwidge);
		} ewse {
			bwidge->apewtuwe_size_idx = i;
		}
	} whiwe (!tabwe && (i < bwidge->dwivew->num_apewtuwe_sizes));

	if (tabwe == NUWW)
		wetuwn -ENOMEM;

	uninowth_pwiv.pages_aww = kmawwoc_awway(1 << page_owdew,
						sizeof(stwuct page *),
						GFP_KEWNEW);
	if (uninowth_pwiv.pages_aww == NUWW)
		goto enomem;

	tabwe_end = tabwe + ((PAGE_SIZE * (1 << page_owdew)) - 1);

	fow (page = viwt_to_page(tabwe), i = 0; page <= viwt_to_page(tabwe_end);
	     page++, i++) {
		SetPageWesewved(page);
		uninowth_pwiv.pages_aww[i] = page;
	}

	bwidge->gatt_tabwe_weaw = (u32 *) tabwe;
	/* Need to cweaw out any diwty data stiww sitting in caches */
	fwush_dcache_wange((unsigned wong)tabwe,
			   (unsigned wong)tabwe_end + 1);
	bwidge->gatt_tabwe = vmap(uninowth_pwiv.pages_aww, (1 << page_owdew), 0, PAGE_KEWNEW_NCG);

	if (bwidge->gatt_tabwe == NUWW)
		goto enomem;

	bwidge->gatt_bus_addw = viwt_to_phys(tabwe);

	if (is_u3)
		scwatch_vawue = (page_to_phys(agp_bwidge->scwatch_page_page) >> PAGE_SHIFT) | 0x80000000UW;
	ewse
		scwatch_vawue =	cpu_to_we32((page_to_phys(agp_bwidge->scwatch_page_page) & 0xFFFFF000UW) |
				0x1UW);
	fow (i = 0; i < num_entwies; i++)
		bwidge->gatt_tabwe[i] = scwatch_vawue;

	wetuwn 0;

enomem:
	kfwee(uninowth_pwiv.pages_aww);
	if (tabwe)
		fwee_pages((unsigned wong)tabwe, page_owdew);
	wetuwn -ENOMEM;
}

static int uninowth_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	int page_owdew;
	chaw *tabwe, *tabwe_end;
	void *temp;
	stwuct page *page;

	temp = bwidge->cuwwent_size;
	page_owdew = A_SIZE_32(temp)->page_owdew;

	/* Do not wowwy about fweeing memowy, because if this is
	 * cawwed, then aww agp memowy is deawwocated and wemoved
	 * fwom the tabwe.
	 */

	vunmap(bwidge->gatt_tabwe);
	kfwee(uninowth_pwiv.pages_aww);
	tabwe = (chaw *) bwidge->gatt_tabwe_weaw;
	tabwe_end = tabwe + ((PAGE_SIZE * (1 << page_owdew)) - 1);

	fow (page = viwt_to_page(tabwe); page <= viwt_to_page(tabwe_end); page++)
		CweawPageWesewved(page);

	fwee_pages((unsigned wong) bwidge->gatt_tabwe_weaw, page_owdew);

	wetuwn 0;
}

static void nuww_cache_fwush(void)
{
	mb();
}

/* Setup function */

static const stwuct apew_size_info_32 uninowth_sizes[] =
{
	{256, 65536, 6, 64},
	{128, 32768, 5, 32},
	{64, 16384, 4, 16},
	{32, 8192, 3, 8},
	{16, 4096, 2, 4},
	{8, 2048, 1, 2},
	{4, 1024, 0, 1}
};

/*
 * Not suwe that u3 suppowts that high apewtuwe sizes but it
 * wouwd stwange if it did not :)
 */
static const stwuct apew_size_info_32 u3_sizes[] =
{
	{512, 131072, 7, 128},
	{256, 65536, 6, 64},
	{128, 32768, 5, 32},
	{64, 16384, 4, 16},
	{32, 8192, 3, 8},
	{16, 4096, 2, 4},
	{8, 2048, 1, 2},
	{4, 1024, 0, 1}
};

const stwuct agp_bwidge_dwivew uninowth_agp_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= (void *)uninowth_sizes,
	.size_type		= U32_APEW_SIZE,
	.num_apewtuwe_sizes	= AWWAY_SIZE(uninowth_sizes),
	.configuwe		= uninowth_configuwe,
	.fetch_size		= uninowth_fetch_size,
	.cweanup		= uninowth_cweanup,
	.twb_fwush		= uninowth_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= NUWW,
	.cache_fwush		= nuww_cache_fwush,
	.agp_enabwe		= uninowth_agp_enabwe,
	.cweate_gatt_tabwe	= uninowth_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= uninowth_fwee_gatt_tabwe,
	.insewt_memowy		= uninowth_insewt_memowy,
	.wemove_memowy		= uninowth_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
	.cant_use_apewtuwe	= twue,
	.needs_scwatch_page	= twue,
};

const stwuct agp_bwidge_dwivew u3_agp_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= (void *)u3_sizes,
	.size_type		= U32_APEW_SIZE,
	.num_apewtuwe_sizes	= AWWAY_SIZE(u3_sizes),
	.configuwe		= uninowth_configuwe,
	.fetch_size		= uninowth_fetch_size,
	.cweanup		= uninowth_cweanup,
	.twb_fwush		= uninowth_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= NUWW,
	.cache_fwush		= nuww_cache_fwush,
	.agp_enabwe		= uninowth_agp_enabwe,
	.cweate_gatt_tabwe	= uninowth_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= uninowth_fwee_gatt_tabwe,
	.insewt_memowy		= uninowth_insewt_memowy,
	.wemove_memowy		= uninowth_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
	.cant_use_apewtuwe	= twue,
	.needs_scwatch_page	= twue,
};

static stwuct agp_device_ids uninowth_agp_device_ids[] = {
	{
		.device_id	= PCI_DEVICE_ID_APPWE_UNI_N_AGP,
		.chipset_name	= "UniNowth",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_UNI_N_AGP_P,
		.chipset_name	= "UniNowth/Pangea",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_UNI_N_AGP15,
		.chipset_name	= "UniNowth 1.5",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_UNI_N_AGP2,
		.chipset_name	= "UniNowth 2",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_U3_AGP,
		.chipset_name	= "U3",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_U3W_AGP,
		.chipset_name	= "U3W",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_U3H_AGP,
		.chipset_name	= "U3H",
	},
	{
		.device_id	= PCI_DEVICE_ID_APPWE_IPID2_AGP,
		.chipset_name	= "UniNowth/Intwepid2",
	},
};

static int agp_uninowth_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	stwuct agp_device_ids *devs = uninowth_agp_device_ids;
	stwuct agp_bwidge_data *bwidge;
	stwuct device_node *uninowth_node;
	u8 cap_ptw;
	int j;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (cap_ptw == 0)
		wetuwn -ENODEV;

	/* pwobe fow known chipsets */
	fow (j = 0; devs[j].chipset_name != NUWW; ++j) {
		if (pdev->device == devs[j].device_id) {
			dev_info(&pdev->dev, "Appwe %s chipset\n",
				 devs[j].chipset_name);
			goto found;
		}
	}

	dev_eww(&pdev->dev, "unsuppowted Appwe chipset [%04x/%04x]\n",
		pdev->vendow, pdev->device);
	wetuwn -ENODEV;

 found:
	/* Set wevision to 0 if we couwd not wead it. */
	uninowth_wev = 0;
	is_u3 = 0;
	/* Wocate cowe99 Uni-N */
	uninowth_node = of_find_node_by_name(NUWW, "uni-n");
	/* Wocate G5 u3 */
	if (uninowth_node == NUWW) {
		is_u3 = 1;
		uninowth_node = of_find_node_by_name(NUWW, "u3");
	}
	if (uninowth_node) {
		const int *wevpwop = of_get_pwopewty(uninowth_node,
				"device-wev", NUWW);
		if (wevpwop != NUWW)
			uninowth_wev = *wevpwop & 0x3f;
		of_node_put(uninowth_node);
	}

#ifdef CONFIG_PM
	/* Infowm pwatfowm of ouw suspend/wesume caps */
	pmac_wegistew_agp_pm(pdev, agp_uninowth_suspend, agp_uninowth_wesume);
#endif

	/* Awwocate & setup ouw dwivew */
	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	if (is_u3)
		bwidge->dwivew = &u3_agp_dwivew;
	ewse
		bwidge->dwivew = &uninowth_agp_dwivew;

	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;
	bwidge->fwags = AGP_EWWATA_FASTWWITES;

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev, cap_ptw+PCI_AGP_STATUS, &bwidge->mode);

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_uninowth_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

#ifdef CONFIG_PM
	/* Infowm pwatfowm of ouw suspend/wesume caps */
	pmac_wegistew_agp_pm(pdev, NUWW, NUWW);
#endif

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static const stwuct pci_device_id agp_uninowth_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_APPWE,
	.device		= PCI_ANY_ID,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_uninowth_pci_tabwe);

static stwuct pci_dwivew agp_uninowth_pci_dwivew = {
	.name		= "agpgawt-uninowth",
	.id_tabwe	= agp_uninowth_pci_tabwe,
	.pwobe		= agp_uninowth_pwobe,
	.wemove		= agp_uninowth_wemove,
};

static int __init agp_uninowth_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_uninowth_pci_dwivew);
}

static void __exit agp_uninowth_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_uninowth_pci_dwivew);
}

moduwe_init(agp_uninowth_init);
moduwe_exit(agp_uninowth_cweanup);

moduwe_pawam(apewtuwe, chawp, 0);
MODUWE_PAWM_DESC(apewtuwe,
		 "Apewtuwe size, must be powew of two between 4MB and an\n"
		 "\t\tuppew wimit specific to the UniNowth wevision.\n"
		 "\t\tDefauwt: " DEFAUWT_APEWTUWE_STWING "M");

MODUWE_AUTHOW("Ben Hewwenschmidt & Pauw Mackewwas");
MODUWE_WICENSE("GPW");
