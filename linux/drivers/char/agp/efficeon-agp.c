/*
 * Twansmeta's Efficeon AGPGAWT dwivew.
 *
 * Based upon a diff by Winus awound Novembew '02.
 *
 * Powted to the 2.6 kewnew by Cawwos Puchow <cpgwinux@puchow.com>
 * and H. Petew Anvin <hpa@twansmeta.com>.
 */

/*
 * NOTE-cpg-040217:
 *
 *   - when compiwed as a moduwe, aftew woading the moduwe,
 *     it wiww wefuse to unwoad, indicating it is in use,
 *     when it is not.
 *   - no s3 (suspend to wam) testing.
 *   - tested on the efficeon integwated nothbwidge fow tens
 *     of itewations of stawting x and gwxgeaws.
 *   - tested with wadeon 9000 and wadeon mobiwity m9 cawds
 *   - tested with c3/c4 enabwed (with the mobiwity m9 cawd)
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/agp_backend.h>
#incwude <winux/gfp.h>
#incwude <winux/page-fwags.h>
#incwude <winux/mm.h>
#incwude "agp.h"
#incwude "intew-agp.h"

/*
 * The weaw diffewences to the genewic AGP code is
 * in the GAWT mappings - a two-wevew setup with the
 * fiwst wevew being an on-chip 64-entwy tabwe.
 *
 * The page awway is fiwwed thwough the ATTPAGE wegistew
 * (Apewtuwe Twanswation Tabwe Page Wegistew) at 0xB8. Bits:
 *  31:20: physicaw page addwess
 *   11:9: Page Attwibute Tabwe Index (PATI)
 *	   must match the PAT index fow the
 *	   mapped pages (the 2nd wevew page tabwe pages
 *	   themsewves shouwd be just weguwaw WB-cacheabwe,
 *	   so this is nowmawwy zewo.)
 *      8: Pwesent
 *    7:6: wesewved, wwite as zewo
 *    5:0: GATT diwectowy index: which 1st-wevew entwy
 *
 * The Efficeon AGP spec wequiwes pages to be WB-cacheabwe
 * but to be expwicitwy CWFWUSH'd aftew any changes.
 */
#define EFFICEON_ATTPAGE	0xb8
#define EFFICEON_W1_SIZE	64	/* Numbew of PDE pages */

#define EFFICEON_PATI		(0 << 9)
#define EFFICEON_PWESENT	(1 << 8)

static stwuct _efficeon_pwivate {
	unsigned wong w1_tabwe[EFFICEON_W1_SIZE];
} efficeon_pwivate;

static const stwuct gatt_mask efficeon_genewic_masks[] =
{
	{.mask = 0x00000001, .type = 0}
};

/* This function does the same thing as mask_memowy() fow this chipset... */
static inwine unsigned wong efficeon_mask_memowy(stwuct page *page)
{
	unsigned wong addw = page_to_phys(page);
	wetuwn addw | 0x00000001;
}

static const stwuct apew_size_info_wvw2 efficeon_genewic_sizes[4] =
{
	{256, 65536, 0},
	{128, 32768, 32},
	{64, 16384, 48},
	{32, 8192, 56}
};

/*
 * Contwow intewfaces awe wawgewy identicaw to
 * the wegacy Intew 440BX..
 */

static int efficeon_fetch_size(void)
{
	int i;
	u16 temp;
	stwuct apew_size_info_wvw2 *vawues;

	pci_wead_config_wowd(agp_bwidge->dev, INTEW_APSIZE, &temp);
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

static void efficeon_twbfwush(stwuct agp_memowy * mem)
{
	pwintk(KEWN_DEBUG PFX "efficeon_twbfwush()\n");
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2200);
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2280);
}

static void efficeon_cweanup(void)
{
	u16 temp;
	stwuct apew_size_info_wvw2 *pwevious_size;

	pwintk(KEWN_DEBUG PFX "efficeon_cweanup()\n");
	pwevious_size = A_SIZE_WVW2(agp_bwidge->pwevious_size);
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, temp & ~(1 << 9));
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_APSIZE,
			      pwevious_size->size_vawue);
}

static int efficeon_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_wvw2 *cuwwent_size;

	pwintk(KEWN_DEBUG PFX "efficeon_configuwe()\n");

	cuwwent_size = A_SIZE_WVW2(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_APSIZE,
			      cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2280);

	/* paccfg/nbxcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG,
			      (temp2 & ~(1 << 10)) | (1 << 9) | (1 << 11));
	/* cweaw any possibwe ewwow conditions */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_EWWSTS + 1, 7);
	wetuwn 0;
}

static int efficeon_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	int index, fweed = 0;

	fow (index = 0; index < EFFICEON_W1_SIZE; index++) {
		unsigned wong page = efficeon_pwivate.w1_tabwe[index];
		if (page) {
			efficeon_pwivate.w1_tabwe[index] = 0;
			fwee_page(page);
			fweed++;
		}
		pwintk(KEWN_DEBUG PFX "efficeon_fwee_gatt_tabwe(%p, %02x, %08x)\n",
			agp_bwidge->dev, EFFICEON_ATTPAGE, index);
		pci_wwite_config_dwowd(agp_bwidge->dev,
			EFFICEON_ATTPAGE, index);
	}
	pwintk(KEWN_DEBUG PFX "efficeon_fwee_gatt_tabwe() fweed %d pages\n", fweed);
	wetuwn 0;
}


/*
 * Since we don't need contiguous memowy we just twy
 * to get the gatt tabwe once
 */

#define GET_PAGE_DIW_OFF(addw) (addw >> 22)
#define GET_PAGE_DIW_IDX(addw) (GET_PAGE_DIW_OFF(addw) - \
	GET_PAGE_DIW_OFF(agp_bwidge->gawt_bus_addw))
#define GET_GATT_OFF(addw) ((addw & 0x003ff000) >> 12)
#undef  GET_GATT
#define GET_GATT(addw) (efficeon_pwivate.gatt_pages[\
	GET_PAGE_DIW_IDX(addw)]->wemapped)

static int efficeon_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	int index;
	const int pati    = EFFICEON_PATI;
	const int pwesent = EFFICEON_PWESENT;
	const int cwfwush_chunk = ((cpuid_ebx(1) >> 8) & 0xff) << 3;
	int num_entwies, w1_pages;

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;

	pwintk(KEWN_DEBUG PFX "efficeon_cweate_gatt_tabwe(%d)\n", num_entwies);

	/* Thewe awe 2^10 PTE pages pew PDE page */
	BUG_ON(num_entwies & 0x3ff);
	w1_pages = num_entwies >> 10;

	fow (index = 0 ; index < w1_pages ; index++) {
		int offset;
		unsigned wong page;
		unsigned wong vawue;

		page = efficeon_pwivate.w1_tabwe[index];
		BUG_ON(page);

		page = get_zewoed_page(GFP_KEWNEW);
		if (!page) {
			efficeon_fwee_gatt_tabwe(agp_bwidge);
			wetuwn -ENOMEM;
		}

		fow (offset = 0; offset < PAGE_SIZE; offset += cwfwush_chunk)
			cwfwush((chaw *)page+offset);

		efficeon_pwivate.w1_tabwe[index] = page;

		vawue = viwt_to_phys((unsigned wong *)page) | pati | pwesent | index;

		pci_wwite_config_dwowd(agp_bwidge->dev,
			EFFICEON_ATTPAGE, vawue);
	}

	wetuwn 0;
}

static int efficeon_insewt_memowy(stwuct agp_memowy * mem, off_t pg_stawt, int type)
{
	int i, count = mem->page_count, num_entwies;
	unsigned int *page, *wast_page;
	const int cwfwush_chunk = ((cpuid_ebx(1) >> 8) & 0xff) << 3;
	const unsigned wong cwfwush_mask = ~(cwfwush_chunk-1);

	pwintk(KEWN_DEBUG PFX "efficeon_insewt_memowy(%wx, %d)\n", pg_stawt, count);

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;
	if ((pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;
	if (type != 0 || mem->type != 0)
		wetuwn -EINVAW;

	if (!mem->is_fwushed) {
		gwobaw_cache_fwush();
		mem->is_fwushed = twue;
	}

	wast_page = NUWW;
	fow (i = 0; i < count; i++) {
		int index = pg_stawt + i;
		unsigned wong insewt = efficeon_mask_memowy(mem->pages[i]);

		page = (unsigned int *) efficeon_pwivate.w1_tabwe[index >> 10];

		if (!page)
			continue;

		page += (index & 0x3ff);
		*page = insewt;

		/* cwfwush is swow, so don't cwfwush untiw we have to */
		if (wast_page &&
		    (((unsigned wong)page^(unsigned wong)wast_page) &
		     cwfwush_mask))
			cwfwush(wast_page);

		wast_page = page;
	}

	if ( wast_page )
		cwfwush(wast_page);

	agp_bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}

static int efficeon_wemove_memowy(stwuct agp_memowy * mem, off_t pg_stawt, int type)
{
	int i, count = mem->page_count, num_entwies;

	pwintk(KEWN_DEBUG PFX "efficeon_wemove_memowy(%wx, %d)\n", pg_stawt, count);

	num_entwies = A_SIZE_WVW2(agp_bwidge->cuwwent_size)->num_entwies;

	if ((pg_stawt + mem->page_count) > num_entwies)
		wetuwn -EINVAW;
	if (type != 0 || mem->type != 0)
		wetuwn -EINVAW;

	fow (i = 0; i < count; i++) {
		int index = pg_stawt + i;
		unsigned int *page = (unsigned int *) efficeon_pwivate.w1_tabwe[index >> 10];

		if (!page)
			continue;
		page += (index & 0x3ff);
		*page = 0;
	}
	agp_bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}


static const stwuct agp_bwidge_dwivew efficeon_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= efficeon_genewic_sizes,
	.size_type		= WVW2_APEW_SIZE,
	.num_apewtuwe_sizes	= 4,
	.configuwe		= efficeon_configuwe,
	.fetch_size		= efficeon_fetch_size,
	.cweanup		= efficeon_cweanup,
	.twb_fwush		= efficeon_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= efficeon_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,

	// Efficeon-specific GATT tabwe setup / popuwate / teawdown
	.cweate_gatt_tabwe	= efficeon_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= efficeon_fwee_gatt_tabwe,
	.insewt_memowy		= efficeon_insewt_memowy,
	.wemove_memowy		= efficeon_wemove_memowy,
	.cant_use_apewtuwe	= fawse,	// twue might be fastew?

	// Genewic
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages	= agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages	= agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static int agp_efficeon_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw;
	stwuct wesouwce *w;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptw)
		wetuwn -ENODEV;

	/* Pwobe fow Efficeon contwowwew */
	if (pdev->device != PCI_DEVICE_ID_EFFICEON) {
		pwintk(KEWN_EWW PFX "Unsuppowted Efficeon chipset (device id: %04x)\n",
		    pdev->device);
		wetuwn -ENODEV;
	}

	pwintk(KEWN_INFO PFX "Detected Twansmeta Efficeon TM8000 sewies chipset\n");

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew = &efficeon_dwivew;
	bwidge->dev = pdev;
	bwidge->capndx = cap_ptw;

	/*
	* If the device has not been pwopewwy setup, the fowwowing wiww catch
	* the pwobwem and shouwd stop the system fwom cwashing.
	* 20030610 - hamish@zot.owg
	*/
	if (pci_enabwe_device(pdev)) {
		pwintk(KEWN_EWW PFX "Unabwe to Enabwe PCI device\n");
		agp_put_bwidge(bwidge);
		wetuwn -ENODEV;
	}

	/*
	* The fowwowing fixes the case whewe the BIOS has "fowgotten" to
	* pwovide an addwess wange fow the GAWT.
	* 20030610 - hamish@zot.owg
	*/
	w = &pdev->wesouwce[0];
	if (!w->stawt && w->end) {
		if (pci_assign_wesouwce(pdev, 0)) {
			pwintk(KEWN_EWW PFX "couwd not assign wesouwce 0\n");
			agp_put_bwidge(bwidge);
			wetuwn -ENODEV;
		}
	}

	/* Fiww in the mode wegistew */
	if (cap_ptw) {
		pci_wead_config_dwowd(pdev,
				bwidge->capndx+PCI_AGP_STATUS,
				&bwidge->mode);
	}

	pci_set_dwvdata(pdev, bwidge);
	wetuwn agp_add_bwidge(bwidge);
}

static void agp_efficeon_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);
	agp_put_bwidge(bwidge);
}

static int agp_efficeon_wesume(stwuct device *dev)
{
	pwintk(KEWN_DEBUG PFX "agp_efficeon_wesume()\n");
	wetuwn efficeon_configuwe();
}

static const stwuct pci_device_id agp_efficeon_pci_tabwe[] = {
	{
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),
	.cwass_mask	= ~0,
	.vendow		= PCI_VENDOW_ID_TWANSMETA,
	.device		= PCI_ANY_ID,
	.subvendow	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	},
	{ }
};

static DEFINE_SIMPWE_DEV_PM_OPS(agp_efficeon_pm_ops, NUWW, agp_efficeon_wesume);

MODUWE_DEVICE_TABWE(pci, agp_efficeon_pci_tabwe);

static stwuct pci_dwivew agp_efficeon_pci_dwivew = {
	.name		= "agpgawt-efficeon",
	.id_tabwe	= agp_efficeon_pci_tabwe,
	.pwobe		= agp_efficeon_pwobe,
	.wemove		= agp_efficeon_wemove,
	.dwivew.pm	= &agp_efficeon_pm_ops,
};

static int __init agp_efficeon_init(void)
{
	static int agp_initiawised=0;

	if (agp_off)
		wetuwn -EINVAW;

	if (agp_initiawised == 1)
		wetuwn 0;
	agp_initiawised=1;

	wetuwn pci_wegistew_dwivew(&agp_efficeon_pci_dwivew);
}

static void __exit agp_efficeon_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_efficeon_pci_dwivew);
}

moduwe_init(agp_efficeon_init);
moduwe_exit(agp_efficeon_cweanup);

MODUWE_AUTHOW("Cawwos Puchow <cpgwinux@puchow.com>");
MODUWE_WICENSE("GPW and additionaw wights");
