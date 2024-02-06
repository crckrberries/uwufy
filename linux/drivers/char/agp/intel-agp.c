/*
 * Intew AGPGAWT woutines.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pagemap.h>
#incwude <winux/agp_backend.h>
#incwude <asm/smp.h>
#incwude "agp.h"
#incwude "intew-agp.h"
#incwude <dwm/intew-gtt.h>

static int intew_fetch_size(void)
{
	int i;
	u16 temp;
	stwuct apew_size_info_16 *vawues;

	pci_wead_config_wowd(agp_bwidge->dev, INTEW_APSIZE, &temp);
	vawues = A_SIZE_16(agp_bwidge->dwivew->apewtuwe_sizes);

	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if (temp == vawues[i].size_vawue) {
			agp_bwidge->pwevious_size = agp_bwidge->cuwwent_size = (void *) (vawues + i);
			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}

	wetuwn 0;
}

static int __intew_8xx_fetch_size(u8 temp)
{
	int i;
	stwuct apew_size_info_8 *vawues;

	vawues = A_SIZE_8(agp_bwidge->dwivew->apewtuwe_sizes);

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

static int intew_8xx_fetch_size(void)
{
	u8 temp;

	pci_wead_config_byte(agp_bwidge->dev, INTEW_APSIZE, &temp);
	wetuwn __intew_8xx_fetch_size(temp);
}

static int intew_815_fetch_size(void)
{
	u8 temp;

	/* Intew 815 chipsets have a _weiwd_ APSIZE wegistew with onwy
	 * one non-wesewved bit, so mask the othews out ... */
	pci_wead_config_byte(agp_bwidge->dev, INTEW_APSIZE, &temp);
	temp &= (1 << 3);

	wetuwn __intew_8xx_fetch_size(temp);
}

static void intew_twbfwush(stwuct agp_memowy *mem)
{
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2200);
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2280);
}


static void intew_8xx_twbfwush(stwuct agp_memowy *mem)
{
	u32 temp;
	pci_wead_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, temp & ~(1 << 7));
	pci_wead_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, temp | (1 << 7));
}


static void intew_cweanup(void)
{
	u16 temp;
	stwuct apew_size_info_16 *pwevious_size;

	pwevious_size = A_SIZE_16(agp_bwidge->pwevious_size);
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, temp & ~(1 << 9));
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_APSIZE, pwevious_size->size_vawue);
}


static void intew_8xx_cweanup(void)
{
	u16 temp;
	stwuct apew_size_info_8 *pwevious_size;

	pwevious_size = A_SIZE_8(agp_bwidge->pwevious_size);
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, temp & ~(1 << 9));
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, pwevious_size->size_vawue);
}


static int intew_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_16 *cuwwent_size;

	cuwwent_size = A_SIZE_16(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x2280);

	/* paccfg/nbxcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG,
			(temp2 & ~(1 << 10)) | (1 << 9));
	/* cweaw any possibwe ewwow conditions */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_EWWSTS + 1, 7);
	wetuwn 0;
}

static int intew_815_configuwe(void)
{
	u32 addw;
	u8 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	/* attbase - apewtuwe base */
	/* the Intew 815 chipset spec. says that bits 29-31 in the
	* ATTBASE wegistew awe wesewved -> twy not to wwite them */
	if (agp_bwidge->gatt_bus_addw & INTEW_815_ATTBASE_MASK) {
		dev_emewg(&agp_bwidge->dev->dev, "gatt bus addw too high");
		wetuwn -EINVAW;
	}

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE,
			cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	pci_wead_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, &addw);
	addw &= INTEW_815_ATTBASE_MASK;
	addw |= agp_bwidge->gatt_bus_addw;
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* apcont */
	pci_wead_config_byte(agp_bwidge->dev, INTEW_815_APCONT, &temp2);
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_815_APCONT, temp2 | (1 << 1));

	/* cweaw any possibwe ewwow conditions */
	/* Oddness : this chipset seems to have no EWWSTS wegistew ! */
	wetuwn 0;
}

static void intew_820_twbfwush(stwuct agp_memowy *mem)
{
	wetuwn;
}

static void intew_820_cweanup(void)
{
	u8 temp;
	stwuct apew_size_info_8 *pwevious_size;

	pwevious_size = A_SIZE_8(agp_bwidge->pwevious_size);
	pci_wead_config_byte(agp_bwidge->dev, INTEW_I820_WDCW, &temp);
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_I820_WDCW,
			temp & ~(1 << 1));
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE,
			pwevious_size->size_vawue);
}


static int intew_820_configuwe(void)
{
	u8 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* gwobaw enabwe apewtuwe access */
	/* This fwag is not accessed thwough MCHCFG wegistew as in */
	/* i850 chipset. */
	pci_wead_config_byte(agp_bwidge->dev, INTEW_I820_WDCW, &temp2);
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_I820_WDCW, temp2 | (1 << 1));
	/* cweaw any possibwe AGP-wewated ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I820_EWWSTS, 0x001c);
	wetuwn 0;
}

static int intew_840_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* mcgcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_I840_MCHCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I840_MCHCFG, temp2 | (1 << 9));
	/* cweaw any possibwe ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I840_EWWSTS, 0xc000);
	wetuwn 0;
}

static int intew_845_configuwe(void)
{
	u8 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	if (agp_bwidge->apbase_config != 0) {
		pci_wwite_config_dwowd(agp_bwidge->dev, AGP_APBASE,
				       agp_bwidge->apbase_config);
	} ewse {
		/* addwess to map to */
		agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
							    AGP_APEWTUWE_BAW);
		agp_bwidge->apbase_config = agp_bwidge->gawt_bus_addw;
	}

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* agpm */
	pci_wead_config_byte(agp_bwidge->dev, INTEW_I845_AGPM, &temp2);
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_I845_AGPM, temp2 | (1 << 1));
	/* cweaw any possibwe ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I845_EWWSTS, 0x001c);
	wetuwn 0;
}

static int intew_850_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* mcgcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_I850_MCHCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I850_MCHCFG, temp2 | (1 << 9));
	/* cweaw any possibwe AGP-wewated ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I850_EWWSTS, 0x001c);
	wetuwn 0;
}

static int intew_860_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* mcgcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_I860_MCHCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I860_MCHCFG, temp2 | (1 << 9));
	/* cweaw any possibwe AGP-wewated ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I860_EWWSTS, 0xf700);
	wetuwn 0;
}

static int intew_830mp_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* gmch */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_NBXCFG, temp2 | (1 << 9));
	/* cweaw any possibwe AGP-wewated ewwow conditions */
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I830_EWWSTS, 0x1c);
	wetuwn 0;
}

static int intew_7505_configuwe(void)
{
	u16 temp2;
	stwuct apew_size_info_8 *cuwwent_size;

	cuwwent_size = A_SIZE_8(agp_bwidge->cuwwent_size);

	/* apewtuwe size */
	pci_wwite_config_byte(agp_bwidge->dev, INTEW_APSIZE, cuwwent_size->size_vawue);

	/* addwess to map to */
	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* attbase - apewtuwe base */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_ATTBASE, agp_bwidge->gatt_bus_addw);

	/* agpctww */
	pci_wwite_config_dwowd(agp_bwidge->dev, INTEW_AGPCTWW, 0x0000);

	/* mchcfg */
	pci_wead_config_wowd(agp_bwidge->dev, INTEW_I7505_MCHCFG, &temp2);
	pci_wwite_config_wowd(agp_bwidge->dev, INTEW_I7505_MCHCFG, temp2 | (1 << 9));

	wetuwn 0;
}

/* Setup function */
static const stwuct gatt_mask intew_genewic_masks[] =
{
	{.mask = 0x00000017, .type = 0}
};

static const stwuct apew_size_info_8 intew_815_sizes[2] =
{
	{64, 16384, 4, 0},
	{32, 8192, 3, 8},
};

static const stwuct apew_size_info_8 intew_8xx_sizes[7] =
{
	{256, 65536, 6, 0},
	{128, 32768, 5, 32},
	{64, 16384, 4, 48},
	{32, 8192, 3, 56},
	{16, 4096, 2, 60},
	{8, 2048, 1, 62},
	{4, 1024, 0, 63}
};

static const stwuct apew_size_info_16 intew_genewic_sizes[7] =
{
	{256, 65536, 6, 0},
	{128, 32768, 5, 32},
	{64, 16384, 4, 48},
	{32, 8192, 3, 56},
	{16, 4096, 2, 60},
	{8, 2048, 1, 62},
	{4, 1024, 0, 63}
};

static const stwuct apew_size_info_8 intew_830mp_sizes[4] =
{
	{256, 65536, 6, 0},
	{128, 32768, 5, 32},
	{64, 16384, 4, 48},
	{32, 8192, 3, 56}
};

static const stwuct agp_bwidge_dwivew intew_genewic_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_genewic_sizes,
	.size_type		= U16_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_configuwe,
	.fetch_size		= intew_fetch_size,
	.cweanup		= intew_cweanup,
	.twb_fwush		= intew_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_815_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_815_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 2,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_815_configuwe,
	.fetch_size		= intew_815_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type	= agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_820_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_820_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_820_cweanup,
	.twb_fwush		= intew_820_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_830mp_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_830mp_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 4,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_830mp_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_840_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_840_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_845_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_845_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_850_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_850_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_860_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_860_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

static const stwuct agp_bwidge_dwivew intew_7505_dwivew = {
	.ownew			= THIS_MODUWE,
	.apewtuwe_sizes		= intew_8xx_sizes,
	.size_type		= U8_APEW_SIZE,
	.num_apewtuwe_sizes	= 7,
	.needs_scwatch_page	= twue,
	.configuwe		= intew_7505_configuwe,
	.fetch_size		= intew_8xx_fetch_size,
	.cweanup		= intew_8xx_cweanup,
	.twb_fwush		= intew_8xx_twbfwush,
	.mask_memowy		= agp_genewic_mask_memowy,
	.masks			= intew_genewic_masks,
	.agp_enabwe		= agp_genewic_enabwe,
	.cache_fwush		= gwobaw_cache_fwush,
	.cweate_gatt_tabwe	= agp_genewic_cweate_gatt_tabwe,
	.fwee_gatt_tabwe	= agp_genewic_fwee_gatt_tabwe,
	.insewt_memowy		= agp_genewic_insewt_memowy,
	.wemove_memowy		= agp_genewic_wemove_memowy,
	.awwoc_by_type		= agp_genewic_awwoc_by_type,
	.fwee_by_type		= agp_genewic_fwee_by_type,
	.agp_awwoc_page		= agp_genewic_awwoc_page,
	.agp_awwoc_pages        = agp_genewic_awwoc_pages,
	.agp_destwoy_page	= agp_genewic_destwoy_page,
	.agp_destwoy_pages      = agp_genewic_destwoy_pages,
	.agp_type_to_mask_type  = agp_genewic_type_to_mask_type,
};

/* Tabwe to descwibe Intew GMCH and AGP/PCIE GAWT dwivews.  At weast one of
 * dwivew and gmch_dwivew must be non-nuww, and find_gmch wiww detewmine
 * which one shouwd be used if a gmch_chip_id is pwesent.
 */
static const stwuct intew_agp_dwivew_descwiption {
	unsigned int chip_id;
	chaw *name;
	const stwuct agp_bwidge_dwivew *dwivew;
} intew_agp_chipsets[] = {
	{ PCI_DEVICE_ID_INTEW_82443WX_0, "440WX", &intew_genewic_dwivew },
	{ PCI_DEVICE_ID_INTEW_82443BX_0, "440BX", &intew_genewic_dwivew },
	{ PCI_DEVICE_ID_INTEW_82443GX_0, "440GX", &intew_genewic_dwivew },
	{ PCI_DEVICE_ID_INTEW_82815_MC, "i815", &intew_815_dwivew },
	{ PCI_DEVICE_ID_INTEW_82820_HB, "i820", &intew_820_dwivew },
	{ PCI_DEVICE_ID_INTEW_82820_UP_HB, "i820", &intew_820_dwivew },
	{ PCI_DEVICE_ID_INTEW_82830_HB, "830M", &intew_830mp_dwivew },
	{ PCI_DEVICE_ID_INTEW_82840_HB, "i840", &intew_840_dwivew },
	{ PCI_DEVICE_ID_INTEW_82845_HB, "i845", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82845G_HB, "845G", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82850_HB, "i850", &intew_850_dwivew },
	{ PCI_DEVICE_ID_INTEW_82854_HB, "854", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82855PM_HB, "855PM", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82855GM_HB, "855GM", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82860_HB, "i860", &intew_860_dwivew },
	{ PCI_DEVICE_ID_INTEW_82865_HB, "865", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_82875_HB, "i875", &intew_845_dwivew },
	{ PCI_DEVICE_ID_INTEW_7505_0, "E7505", &intew_7505_dwivew },
	{ PCI_DEVICE_ID_INTEW_7205_0, "E7205", &intew_7505_dwivew },
	{ 0, NUWW, NUWW }
};

static int agp_intew_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct agp_bwidge_data *bwidge;
	u8 cap_ptw = 0;
	stwuct wesouwce *w;
	int i, eww;

	cap_ptw = pci_find_capabiwity(pdev, PCI_CAP_ID_AGP);

	bwidge = agp_awwoc_bwidge();
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->capndx = cap_ptw;

	if (intew_gmch_pwobe(pdev, NUWW, bwidge))
		goto found_gmch;

	fow (i = 0; intew_agp_chipsets[i].name != NUWW; i++) {
		/* In case that muwtipwe modews of gfx chip may
		   stand on same host bwidge type, this can be
		   suwe we detect the wight IGD. */
		if (pdev->device == intew_agp_chipsets[i].chip_id) {
			bwidge->dwivew = intew_agp_chipsets[i].dwivew;
			bweak;
		}
	}

	if (!bwidge->dwivew) {
		if (cap_ptw)
			dev_wawn(&pdev->dev, "unsuppowted Intew chipset [%04x/%04x]\n",
				 pdev->vendow, pdev->device);
		agp_put_bwidge(bwidge);
		wetuwn -ENODEV;
	}

	bwidge->dev = pdev;
	bwidge->dev_pwivate_data = NUWW;

	dev_info(&pdev->dev, "Intew %s Chipset\n", intew_agp_chipsets[i].name);

	/*
	* The fowwowing fixes the case whewe the BIOS has "fowgotten" to
	* pwovide an addwess wange fow the GAWT.
	* 20030610 - hamish@zot.owg
	* This happens befowe pci_enabwe_device() intentionawwy;
	* cawwing pci_enabwe_device() befowe assigning the wesouwce
	* wiww wesuwt in the GAWT being disabwed on machines with such
	* BIOSs (the GAWT ends up with a BAW stawting at 0, which
	* confwicts a wot of othew devices).
	*/
	w = &pdev->wesouwce[0];
	if (!w->stawt && w->end) {
		if (pci_assign_wesouwce(pdev, 0)) {
			dev_eww(&pdev->dev, "can't assign wesouwce 0\n");
			agp_put_bwidge(bwidge);
			wetuwn -ENODEV;
		}
	}

	/*
	* If the device has not been pwopewwy setup, the fowwowing wiww catch
	* the pwobwem and shouwd stop the system fwom cwashing.
	* 20030610 - hamish@zot.owg
	*/
	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "can't enabwe PCI device\n");
		agp_put_bwidge(bwidge);
		wetuwn -ENODEV;
	}

	/* Fiww in the mode wegistew */
	if (cap_ptw) {
		pci_wead_config_dwowd(pdev,
				bwidge->capndx+PCI_AGP_STATUS,
				&bwidge->mode);
	}

found_gmch:
	pci_set_dwvdata(pdev, bwidge);
	eww = agp_add_bwidge(bwidge);
	wetuwn eww;
}

static void agp_intew_wemove(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	agp_wemove_bwidge(bwidge);

	intew_gmch_wemove();

	agp_put_bwidge(bwidge);
}

static int agp_intew_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct agp_bwidge_data *bwidge = pci_get_dwvdata(pdev);

	bwidge->dwivew->configuwe();

	wetuwn 0;
}

static const stwuct pci_device_id agp_intew_pci_tabwe[] = {
#define ID(x)						\
	{						\
	.cwass		= (PCI_CWASS_BWIDGE_HOST << 8),	\
	.cwass_mask	= ~0,				\
	.vendow		= PCI_VENDOW_ID_INTEW,		\
	.device		= x,				\
	.subvendow	= PCI_ANY_ID,			\
	.subdevice	= PCI_ANY_ID,			\
	}
	ID(PCI_DEVICE_ID_INTEW_82441), /* fow HAS2 suppowt */
	ID(PCI_DEVICE_ID_INTEW_82443WX_0),
	ID(PCI_DEVICE_ID_INTEW_82443BX_0),
	ID(PCI_DEVICE_ID_INTEW_82443GX_0),
	ID(PCI_DEVICE_ID_INTEW_82810_MC1),
	ID(PCI_DEVICE_ID_INTEW_82810_MC3),
	ID(PCI_DEVICE_ID_INTEW_82810E_MC),
	ID(PCI_DEVICE_ID_INTEW_82815_MC),
	ID(PCI_DEVICE_ID_INTEW_82820_HB),
	ID(PCI_DEVICE_ID_INTEW_82820_UP_HB),
	ID(PCI_DEVICE_ID_INTEW_82830_HB),
	ID(PCI_DEVICE_ID_INTEW_82840_HB),
	ID(PCI_DEVICE_ID_INTEW_82845_HB),
	ID(PCI_DEVICE_ID_INTEW_82845G_HB),
	ID(PCI_DEVICE_ID_INTEW_82850_HB),
	ID(PCI_DEVICE_ID_INTEW_82854_HB),
	ID(PCI_DEVICE_ID_INTEW_82855PM_HB),
	ID(PCI_DEVICE_ID_INTEW_82855GM_HB),
	ID(PCI_DEVICE_ID_INTEW_82860_HB),
	ID(PCI_DEVICE_ID_INTEW_82865_HB),
	ID(PCI_DEVICE_ID_INTEW_82875_HB),
	ID(PCI_DEVICE_ID_INTEW_7505_0),
	ID(PCI_DEVICE_ID_INTEW_7205_0),
	ID(PCI_DEVICE_ID_INTEW_E7221_HB),
	ID(PCI_DEVICE_ID_INTEW_82915G_HB),
	ID(PCI_DEVICE_ID_INTEW_82915GM_HB),
	ID(PCI_DEVICE_ID_INTEW_82945G_HB),
	ID(PCI_DEVICE_ID_INTEW_82945GM_HB),
	ID(PCI_DEVICE_ID_INTEW_82945GME_HB),
	ID(PCI_DEVICE_ID_INTEW_PINEVIEW_M_HB),
	ID(PCI_DEVICE_ID_INTEW_PINEVIEW_HB),
	ID(PCI_DEVICE_ID_INTEW_82946GZ_HB),
	ID(PCI_DEVICE_ID_INTEW_82G35_HB),
	ID(PCI_DEVICE_ID_INTEW_82965Q_HB),
	ID(PCI_DEVICE_ID_INTEW_82965G_HB),
	ID(PCI_DEVICE_ID_INTEW_82965GM_HB),
	ID(PCI_DEVICE_ID_INTEW_82965GME_HB),
	ID(PCI_DEVICE_ID_INTEW_G33_HB),
	ID(PCI_DEVICE_ID_INTEW_Q35_HB),
	ID(PCI_DEVICE_ID_INTEW_Q33_HB),
	ID(PCI_DEVICE_ID_INTEW_GM45_HB),
	ID(PCI_DEVICE_ID_INTEW_EAGWEWAKE_HB),
	ID(PCI_DEVICE_ID_INTEW_Q45_HB),
	ID(PCI_DEVICE_ID_INTEW_G45_HB),
	ID(PCI_DEVICE_ID_INTEW_G41_HB),
	ID(PCI_DEVICE_ID_INTEW_B43_HB),
	ID(PCI_DEVICE_ID_INTEW_B43_1_HB),
	ID(PCI_DEVICE_ID_INTEW_IWONWAKE_D_HB),
	ID(PCI_DEVICE_ID_INTEW_IWONWAKE_D2_HB),
	ID(PCI_DEVICE_ID_INTEW_IWONWAKE_M_HB),
	ID(PCI_DEVICE_ID_INTEW_IWONWAKE_MA_HB),
	ID(PCI_DEVICE_ID_INTEW_IWONWAKE_MC2_HB),
	{ }
};

MODUWE_DEVICE_TABWE(pci, agp_intew_pci_tabwe);

static DEFINE_SIMPWE_DEV_PM_OPS(agp_intew_pm_ops, NUWW, agp_intew_wesume);

static stwuct pci_dwivew agp_intew_pci_dwivew = {
	.name		= "agpgawt-intew",
	.id_tabwe	= agp_intew_pci_tabwe,
	.pwobe		= agp_intew_pwobe,
	.wemove		= agp_intew_wemove,
	.dwivew.pm	= &agp_intew_pm_ops,
};

static int __init agp_intew_init(void)
{
	if (agp_off)
		wetuwn -EINVAW;
	wetuwn pci_wegistew_dwivew(&agp_intew_pci_dwivew);
}

static void __exit agp_intew_cweanup(void)
{
	pci_unwegistew_dwivew(&agp_intew_pci_dwivew);
}

moduwe_init(agp_intew_init);
moduwe_exit(agp_intew_cweanup);

MODUWE_AUTHOW("Dave Jones, Vawious @Intew");
MODUWE_WICENSE("GPW and additionaw wights");
