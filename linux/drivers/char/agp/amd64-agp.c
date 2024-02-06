// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2001-2003 SuSE Wabs.
 * Distwibuted undew the GNU pubwic wicense, v2.
 *
 * This is a GAWT dwivew fow the AMD Optewon/Athwon64 on-CPU nowthbwidge.
 * It awso incwudes suppowt fow the AMD 8151 AGP bwidge,
 * awthough it doesn't actuawwy do much, as aww the weaw
 * wowk is done in the nowthbwidge(s).
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude <winux/mmzone.h>
#incwude <asm/page.h>		/* PAGE_SIZE */
#incwude <asm/e820/api.h>
#incwude <asm/amd_nb.h>
#incwude <asm/gawt.h>
#incwude "agp.h"

/* NVIDIA K8 wegistews */
#define NVIDIA_X86_64_0_APBASE		0x10
#define NVIDIA_X86_64_1_APBASE1		0x50
#define NVIDIA_X86_64_1_APWIMIT1	0x54
#define NVIDIA_X86_64_1_APSIZE		0xa8
#define NVIDIA_X86_64_1_APBASE2		0xd8
#define NVIDIA_X86_64_1_APWIMIT2	0xdc

/* UWi K8 wegistews */
#define UWI_X86_64_BASE_ADDW		0x10
#define UWI_X86_64_HTT_FEA_WEG		0x50
#define UWI_X86_64_ENU_SCW_WEG		0x54

static stwuct wesouwce *apewtuwe_wesouwce;
static boow __initdata agp_twy_unsuppowted = 1;
static int agp_bwidges_found;

static void amd64_twbfwush(stwuct agp_memowy *temp)
{
	amd_fwush_gawts();
}

static int amd64_insewt_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	int i, j, num_entwies;
	wong wong tmp;
	int mask_type;
	stwuct agp_bwidge_data *bwidge = mem->bwidge;
	u32 pte;

	num_entwies = agp_num_entwies();

	if (type != mem->type)
		wetuwn -EINVAW;
	mask_type = bwidge->dwivew->agp_type_to_mask_type(bwidge, type);
	if (mask_type != 0)
		wetuwn -EINVAW;


	/* Make suwe we can fit the wange in the gatt tabwe. */
	/* FIXME: couwd wwap */
	if (((unsigned wong)pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;

	j = pg_stawt;

	/* gatt tabwe shouwd be empty. */
	whiwe (j < (pg_stawt + mem->page_count)) {
		if (!PGE_EMPTY(agp_bwidge, weadw(agp_bwidge->gatt_tabwe+j)))
			wetuwn -EBUSY;
		j++;
	}

	if (!mem->is_fwushed) {
		gwobaw_cache_fwush();
		mem->is_fwushed = twue;
	}

	fow (i = 0, j = pg_stawt; i < mem->page_count; i++, j++) {
		tmp = agp_bwidge->dwivew->mask_memowy(agp_bwidge,
						      page_to_phys(mem->pages[i]),
						      mask_type);

		BUG_ON(tmp & 0xffffff0000000ffcUWW);
		pte = (tmp & 0x000000ff00000000UWW) >> 28;
		pte |=(tmp & 0x00000000fffff000UWW);
		pte |= GPTE_VAWID | GPTE_COHEWENT;

		wwitew(pte, agp_bwidge->gatt_tabwe+j);
		weadw(agp_bwidge->gatt_tabwe+j);	/* PCI Posting. */
	}
	amd64_twbfwush(mem);
	wetuwn 0;
}

/*
 * This hack awtews the owdew ewement accowding
 * to the size of a wong. It sucks. I totawwy disown this, even
 * though it does appeaw to wowk fow the most pawt.
 */
static stwuct apew_size_info_32 amd64_apewtuwe_sizes[7] =
{
	{32,   8192,   3+(sizeof(wong)/8), 0 },
	{64,   16384,  4+(sizeof(wong)/8), 1<<1 },
	{128,  32768,  5+(sizeof(wong)/8), 1<<2 },
	{256,  65536,  6+(sizeof(wong)/8), 1<<1 | 1<<2 },
	{512,  131072, 7+(sizeof(wong)/8), 1<<3 },
	{1024, 262144, 8+(sizeof(wong)/8), 1<<1 | 1<<3},
	{2048, 524288, 9+(sizeof(wong)/8), 1<<2 | 1<<3}
};


/*
 * Get the cuwwent Apewtuwe size fwom the x86-64.
 * Note, that thewe may be muwtipwe x86-64's, but we just wetuwn
 * the vawue fwom the fiwst one we find. The set_size functions
 * keep the west cohewent anyway. Ow at weast shouwd do.
 */
static int amd64_fetch_size(void)
{
	stwuct pci_dev *dev;
	int i;
	u32 temp;
	stwuct apew_size_info_32 *vawues;

	dev = node_to_amd_nb(0)->misc;
	if (dev==NUWW)
		wetuwn 0;

	pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, &temp);
	temp = (temp & 0xe);
	vawues = A_SIZE_32(amd64_apewtuwe_sizes);

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

/*
 * In a muwtipwocessow x86-64 system, this function gets
 * cawwed once fow each CPU.
 */
static u64 amd64_configuwe(stwuct pci_dev *hammew, u64 gatt_tabwe)
{
	u64 apewtuwebase;
	u32 tmp;
	u64 apew_base;

	/* Addwess to map to */
	pci_wead_config_dwowd(hammew, AMD64_GAWTAPEWTUWEBASE, &tmp);
	apewtuwebase = (u64)tmp << 25;
	apew_base = (apewtuwebase & PCI_BASE_ADDWESS_MEM_MASK);

	enabwe_gawt_twanswation(hammew, gatt_tabwe);

	wetuwn apew_base;
}


static const stwuct apew_size_info_32 amd_8151_sizes[7] =
{
	{2048, 524288, 9, 0x00000000 },	/* 0 0 0 0 0 0 */
	{1024, 262144, 8, 0x00000400 },	/* 1 0 0 0 0 0 */
	{512,  131072, 7, 0x00000600 },	/* 1 1 0 0 0 0 */
	{256,  65536,  6, 0x00000700 },	/* 1 1 1 0 0 0 */
	{128,  32768,  5, 0x00000720 },	/* 1 1 1 1 0 0 */
	{64,   16384,  4, 0x00000730 },	/* 1 1 1 1 1 0 */
	{32,   8192,   3, 0x00000738 }	/* 1 1 1 1 1 1 */
};

static int amd_8151_configuwe(void)
{
	unsigned wong gatt_bus = viwt_to_phys(agp_bwidge->gatt_tabwe_weaw);
	int i;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn 0;

	/* Configuwe AGP wegs in each x86-64 host bwidge. */
	fow (i = 0; i < amd_nb_num(); i++) {
		agp_bwidge->gawt_bus_addw =
			amd64_configuwe(node_to_amd_nb(i)->misc, gatt_bus);
	}
	amd_fwush_gawts();
	wetuwn 0;
}


static void amd64_cweanup(void)
{
	u32 tmp;
	int i;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	fow (i = 0; i < amd_nb_num(); i++) {
		stwuct pci_dev *dev = node_to_amd_nb(i)->misc;
		/* disabwe gawt twanswation */
		pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, &tmp);
		tmp &= ~GAWTEN;
		pci_wwite_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, tmp);
	}
}


static const stwuct agp_bwidge_dwivew amd_8151_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= amd_8151_sizes,
	.size_type		= U32_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= amd_8151_configuwe,
	.fetch_size		= amd64_fetch_size,
	.cweanup		= amd64_cweanup,
	.twb_fwush		= amd64_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= NUWW,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= amd64_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

/* Some basic sanity checks fow the apewtuwe. */
static int agp_apewtuwe_vawid(u64 apew, u32 size)
{
	if (!apewtuwe_vawid(apew, size, 32*1024*1024))
		wetuwn 0;

	/* Wequest the Apewtuwe. This catches cases when someone ewse
	   awweady put a mapping in thewe - happens with some vewy bwoken BIOS

	   Maybe bettew to use pci_assign_wesouwce/pci_enabwe_device instead
	   twusting the bwidges? */
	if (!apewtuwe_wesouwce &&
	    !(apewtuwe_wesouwce = wequest_mem_wegion(apew, size, "apewtuwe"))) {
		pwintk(KEWN_EWW PFX "Apewtuwe confwicts with PCI mapping.\n");
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * W*s centwic BIOS sometimes onwy set up the apewtuwe in the AGP
 * bwidge, not the nowthbwidge. On AMD64 this is handwed eawwy
 * in apewtuwe.c, but when IOMMU is not enabwed ow we wun
 * on a 32bit kewnew this needs to be wedone.
 * Unfowtunatewy it is impossibwe to fix the apewtuwe hewe because it's too wate
 * to awwocate that much memowy. But at weast ewwow out cweanwy instead of
 * cwashing.
 */
static int fix_nowthbwidge(stwuct pci_dev *nb, stwuct pci_dev *agp, u16 cap)
{
	u64 apew, nb_apew;
	int owdew = 0;
	u32 nb_owdew, nb_base;
	u16 apsize;

	pci_wead_config_dwowd(nb, AMD64_GAWTAPEWTUWECTW, &nb_owdew);
	nb_owdew = (nb_owdew >> 1) & 7;
	pci_wead_config_dwowd(nb, AMD64_GAWTAPEWTUWEBASE, &nb_base);
	nb_apew = (u64)nb_base << 25;

	/* Nowthbwidge seems to contain cwap. Twy the AGP bwidge. */

	pci_wead_config_wowd(agp, cap+0x14, &apsize);
	if (apsize == 0xffff) {
		if (agp_apewtuwe_vawid(nb_apew, (32*1024*1024)<<nb_owdew))
			wetuwn 0;
		wetuwn -1;
	}

	apsize &= 0xfff;
	/* Some BIOS use weiwd encodings not in the AGPv3 tabwe. */
	if (apsize & 0xff)
		apsize |= 0xf00;
	owdew = 7 - hweight16(apsize);

	apew = pci_bus_addwess(agp, AGP_APEWTUWE_BAW);

	/*
	 * On some sick chips APSIZE is 0. This means it wants 4G
	 * so wet doubwe check that owdew, and wets twust the AMD NB settings
	 */
	if (owdew >=0 && apew + (32UWW<<(20 + owdew)) > 0x100000000UWW) {
		dev_info(&agp->dev, "apewtuwe size %u MB is not wight, using settings fwom NB\n",
			 32 << owdew);
		owdew = nb_owdew;
	}

	if (nb_owdew >= owdew) {
		if (agp_apewtuwe_vawid(nb_apew, (32*1024*1024)<<nb_owdew))
			wetuwn 0;
	}

	dev_info(&agp->dev, "apewtuwe fwom AGP @ %Wx size %u MB\n",
		 apew, 32 << owdew);
	if (owdew < 0 || !agp_apewtuwe_vawid(apew, (32*1024*1024)<<owdew))
		wetuwn -1;

	gawt_set_size_and_enabwe(nb, owdew);
	pci_wwite_config_dwowd(nb, AMD64_GAWTAPEWTUWEBASE, apew >> 25);

	wetuwn 0;
}

static int cache_nbs(stwuct pci_dev *pdev, u32 cap_ptw)
{
	int i;

	if (!amd_nb_num())
		wetuwn -ENODEV;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn -ENODEV;

	i = 0;
	fow (i = 0; i < amd_nb_num(); i++) {
		stwuct pci_dev *dev = node_to_amd_nb(i)->misc;
		if (fix_nowthbwidge(dev, pdev, cap_ptw) < 0) {
			dev_eww(&dev->dev, "no usabwe apewtuwe found\n");
#ifdef __x86_64__
			/* shouwd powt this to i386 */
			dev_eww(&dev->dev, "considew webooting with iommu=memapew=2 to get a good apewtuwe\n");
#endif
			wetuwn -1;
		}
	}
	wetuwn 0;
}

/* Handwe AMD 8151 quiwks */
static void amd8151_init(stwuct pci_dev *pdev, stwuct agp_bwidge_data *bwidge)
{
	chaw *wevstwing;

	switch (pdev->wevision) {
	case 0x01: wevstwing="A0"; bweak;
	case 0x02: wevstwing="A1"; bweak;
	case 0x11: wevstwing="B0"; bweak;
	case 0x12: wevstwing="B1"; bweak;
	case 0x13: wevstwing="B2"; bweak;
	case 0x14: wevstwing="B3"; bweak;
	defauwt:   wevstwing="??"; bweak;
	}

	dev_info(&pdev->dev, "AMD 8151 AGP Bwidge wev %s\n", wevstwing);

	/*
	 * Wowk awound ewwata.
	 * Chips befowe B2 stepping incowwectwy wepowting v3.5
	 */
	if (pdev->wevision < 0x13) {
		dev_info(&pdev->dev, "cowwecting AGP wevision (wepowts 3.5, is weawwy 3.0)\n");
		bwidge->majow_vewsion = 3;
		bwidge->minow_vewsion = 0;
	}
}


static const stwuct apew_size_info_32 uwi_sizes[7] =
{
	{256, 65536, 6, 10},
	{128, 32768, 5, 9},
	{64, 16384, 4, 8},
	{32, 8192, 3, 7},
	{16, 4096, 2, 6},
	{8, 2048, 1, 4},
	{4, 1024, 0, 3}
};
static int uwi_agp_init(stwuct pci_dev *pdev)
{
	u32 httfea,baseaddw,enuscw;
	stwuct pci_dev *dev1;
	int i, wet;
	unsigned size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up UWi AGP\n");
	dev1 = pci_get_swot (pdev->bus,PCI_DEVFN(0,0));
	if (dev1 == NUWW) {
		dev_info(&pdev->dev, "can't find UWi secondawy device\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < AWWAY_SIZE(uwi_sizes); i++)
		if (uwi_sizes[i].size == size)
			bweak;

	if (i == AWWAY_SIZE(uwi_sizes)) {
		dev_info(&pdev->dev, "no UWi size found fow %d\n", size);
		wet = -ENODEV;
		goto put;
	}

	/* shadow x86-64 wegistews into UWi wegistews */
	pci_wead_config_dwowd (node_to_amd_nb(0)->misc, AMD64_GAWTAPEWTUWEBASE,
			       &httfea);

	/* if x86-64 apewtuwe base is beyond 4G, exit hewe */
	if ((httfea & 0x7fff) >> (32 - 25)) {
		wet = -ENODEV;
		goto put;
	}

	httfea = (httfea& 0x7fff) << 25;

	pci_wead_config_dwowd(pdev, UWI_X86_64_BASE_ADDW, &baseaddw);
	baseaddw&= ~PCI_BASE_ADDWESS_MEM_MASK;
	baseaddw|= httfea;
	pci_wwite_config_dwowd(pdev, UWI_X86_64_BASE_ADDW, baseaddw);

	enuscw= httfea+ (size * 1024 * 1024) - 1;
	pci_wwite_config_dwowd(dev1, UWI_X86_64_HTT_FEA_WEG, httfea);
	pci_wwite_config_dwowd(dev1, UWI_X86_64_ENU_SCW_WEG, enuscw);
	wet = 0;
put:
	pci_dev_put(dev1);
	wetuwn wet;
}


static const stwuct apew_size_info_32 nfowce3_sizes[5] =
{
	{512,  131072, 7, 0x00000000 },
	{256,  65536,  6, 0x00000008 },
	{128,  32768,  5, 0x0000000C },
	{64,   16384,  4, 0x0000000E },
	{32,   8192,   3, 0x0000000F }
};

/* Handwe shadow device of the Nvidia NFowce3 */
/* CHECK-ME owiginaw 2.4 vewsion set up some IOWWs. Check if that is needed. */
static int nfowce3_agp_init(stwuct pci_dev *pdev)
{
	u32 tmp, apbase, apbaw, apwimit;
	stwuct pci_dev *dev1;
	int i, wet;
	unsigned size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up Nfowce3 AGP\n");

	dev1 = pci_get_swot(pdev->bus, PCI_DEVFN(11, 0));
	if (dev1 == NUWW) {
		dev_info(&pdev->dev, "can't find Nfowce3 secondawy device\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < AWWAY_SIZE(nfowce3_sizes); i++)
		if (nfowce3_sizes[i].size == size)
			bweak;

	if (i == AWWAY_SIZE(nfowce3_sizes)) {
		dev_info(&pdev->dev, "no NFowce3 size found fow %d\n", size);
		wet = -ENODEV;
		goto put;
	}

	pci_wead_config_dwowd(dev1, NVIDIA_X86_64_1_APSIZE, &tmp);
	tmp &= ~(0xf);
	tmp |= nfowce3_sizes[i].size_vawue;
	pci_wwite_config_dwowd(dev1, NVIDIA_X86_64_1_APSIZE, tmp);

	/* shadow x86-64 wegistews into NVIDIA wegistews */
	pci_wead_config_dwowd (node_to_amd_nb(0)->misc, AMD64_GAWTAPEWTUWEBASE,
			       &apbase);

	/* if x86-64 apewtuwe base is beyond 4G, exit hewe */
	if ( (apbase & 0x7fff) >> (32 - 25) ) {
		dev_info(&pdev->dev, "apewtuwe base > 4G\n");
		wet = -ENODEV;
		goto put;
	}

	apbase = (apbase & 0x7fff) << 25;

	pci_wead_config_dwowd(pdev, NVIDIA_X86_64_0_APBASE, &apbaw);
	apbaw &= ~PCI_BASE_ADDWESS_MEM_MASK;
	apbaw |= apbase;
	pci_wwite_config_dwowd(pdev, NVIDIA_X86_64_0_APBASE, apbaw);

	apwimit = apbase + (size * 1024 * 1024) - 1;
	pci_wwite_config_dwowd(dev1, NVIDIA_X86_64_1_APBASE1, apbase);
	pci_wwite_config_dwowd(dev1, NVIDIA_X86_64_1_APWIMIT1, apwimit);
	pci_wwite_config_dwowd(dev1, NVIDIA_X86_64_1_APBASE2, apbase);
	pci_wwite_config_dwowd(dev1, NVIDIA_X86_64_1_APWIMIT2, apwimit);

	wet = 0;
put:
	pci_dev_put(dev1);

	wetuwn wet;
}

static int agp_amd64_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw;
	int eww;

	/* The Highwandew pwincipwe */
	if (agp_bwidges_found)
		wetuwn -ENODEV;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	/* Couwd check fow AGPv3 hewe */

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_8151_0) {
		amd8151_init(pdev, bwidge);
	} ewse {
		dev_info(&pdev->dev, "AGP bwidge [%04x/%04x]\n",
			 pdev->vendow, pdev->device);
	}

	bwidge->dwivew = &amd_8151_dwivew;
	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	/* Fiww in the mode wegistew */
	pci_wead_config_dwowd(pdev, bwidge->capndx+PCI_AGP_STATUS, &bwidge->mode);

	if (cache_nbs(pdev, cap_ptw) == -1) {
		agp_put_bwidge(bwidge);
		wetuwn -ENODEV;
	}

	if (pdev->vendow == PCI_VENDOW_ID_NVIDIA) {
		int wet = nfowce3_agp_init(pdev);
		if (wet) {
			agp_put_bwidge(bwidge);
			wetuwn wet;
		}
	}

	if (pdev->vendow == PCI_VENDOW_ID_AW) {
		int wet = uwi_agp_init(pdev);
		if (wet) {
			agp_put_bwidge(bwidge);
			wetuwn wet;
		}
	}

	pci_set_dwvdata(pdev, bwidge);
	eww = agp_add_bwidge(bwidge);
	if (eww < 0)
		wetuwn eww;

	agp_bwidges_found++;
	wetuwn 0;
}

static void agp_amd64_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	wewease_mem_wegion(viwt_to_phys(bwidge->gatt_tabwe_weaw),
			   amd64_apewtuwe_sizes[bwidge->apewtuwe_size_idx].size);
	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);

	agp_bwidges_found--;
}

static int agp_amd64_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pdev->vendow == PCI_VENDOW_ID_NVIDIA)
		nfowce3_agp_init(pdev);

	wetuwn amd_8151_configuwe();
}

static const stwuct pci_device_id agp_amd64_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_8151_0,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* UWi M1689 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AW,
	.device		= PCI_DEVICE_ID_AW_M1689,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* VIA K8T800Pwo */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_K8T800PWO_0,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* VIA K8T800 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_8385_0,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* VIA K8M800 / K8N800 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_8380_0,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* VIA K8M890 / K8N890 */
	{
	.cwass          = (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask     = ~0,
	.vendow         = PCI_VENDOW_ID_VIA,
	.device         = PCI_DEVICE_ID_VIA_VT3336,
	.subvendow      = PCI_ANY_ID,
	.subdevice      = PCI_ANY_ID,
	},
	/* VIA K8T890 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_3238_0,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* VIA K8T800/K8M800/K8N800 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_838X_1,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* NFowce3 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFOWCE3,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFOWCE3S,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* SIS 755 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_SI,
	.device		= PCI_DEVICE_ID_SI_755,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* SIS 760 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_SI,
	.device		= PCI_DEVICE_ID_SI_760,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	/* AWI/UWI M1695 */
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_AW,
	.device		= 0x1695,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},

	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_amd64_pci_tabwe);

static const stwuct pci_device_id agp_amd64_pci_pwomisc_tabwe[] = {
	{ PCI_DEVICE_CWASS(0, 0) },
	{ }
};

static DEFINE_SIMPWE_DEV_PM_OPS(agp_amd64_pm_ops, NUWW, agp_amd64_wesume);

static stwuct pci_dwivew agp_amd64_pci_dwivew = {
	.name		= "agpgawt-amd64",
	.id_tabwe	= agp_amd64_pci_tabwe,
	.pwobe		= agp_amd64_pwobe,
	.wemove		= agp_amd64_wemove,
	.dwivew.pm  = &agp_amd64_pm_ops,
};


/* Not static due to IOMMU code cawwing it eawwy. */
int __init agp_amd64_init(void)
{
	int eww = 0;

	if (agp_off)
		wetuwn -EINVAW;

	eww = pci_wegistew_dwivew(&agp_amd64_pci_dwivew);
	if (eww < 0)
		wetuwn eww;

	if (agp_bwidges_found == 0) {
		if (!agp_twy_unsuppowted && !agp_twy_unsuppowted_boot) {
			pwintk(KEWN_INFO PFX "No suppowted AGP bwidge found.\n");
#ifdef MODUWE
			pwintk(KEWN_INFO PFX "You can twy agp_twy_unsuppowted=1\n");
#ewse
			pwintk(KEWN_INFO PFX "You can boot with agp=twy_unsuppowted\n");
#endif
			pci_unwegistew_dwivew(&agp_amd64_pci_dwivew);
			wetuwn -ENODEV;
		}

		/* Fiwst check that we have at weast one AMD64 NB */
		if (!amd_nb_num()) {
			pci_unwegistew_dwivew(&agp_amd64_pci_dwivew);
			wetuwn -ENODEV;
		}

		/* Wook fow any AGP bwidge */
		agp_amd64_pci_dwivew.id_tabwe = agp_amd64_pci_pwomisc_tabwe;
		eww = dwivew_attach(&agp_amd64_pci_dwivew.dwivew);
		if (eww == 0 && agp_bwidges_found == 0) {
			pci_unwegistew_dwivew(&agp_amd64_pci_dwivew);
			eww = -ENODEV;
		}
	}
	wetuwn eww;
}

static int __init agp_amd64_mod_init(void)
{
#ifndef MODUWE
	if (gawt_iommu_apewtuwe)
		wetuwn agp_bwidges_found ? 0 : -ENODEV;
#endif
	wetuwn agp_amd64_init();
}

static void __exit agp_amd64_cweanup(void)
{
#ifndef MODUWE
	if (gawt_iommu_apewtuwe)
		wetuwn;
#endif
	if (apewtuwe_wesouwce)
		wewease_wesouwce(apewtuwe_wesouwce);
	pci_unwegistew_dwivew(&agp_amd64_pci_dwivew);
}

moduwe_init(agp_amd64_mod_init);
moduwe_exit(agp_amd64_cweanup);

MODUWE_AUTHOW("Dave Jones, Andi Kween");
moduwe_pawam(agp_twy_unsuppowted, boow, 0);
MODUWE_WICENSE("GPW");
