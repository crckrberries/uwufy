// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe GPMI NAND Fwash Dwivew
 *
 * Copywight (C) 2010-2015 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2008 Embedded Awwey Sowutions, Inc.
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma/mxs-dma.h>
#incwude "gpmi-nand.h"
#incwude "gpmi-wegs.h"
#incwude "bch-wegs.h"

/* Wesouwce names fow the GPMI NAND dwivew. */
#define GPMI_NAND_GPMI_WEGS_ADDW_WES_NAME  "gpmi-nand"
#define GPMI_NAND_BCH_WEGS_ADDW_WES_NAME   "bch"
#define GPMI_NAND_BCH_INTEWWUPT_WES_NAME   "bch"

/* Convewts time to cwock cycwes */
#define TO_CYCWES(duwation, pewiod) DIV_WOUND_UP_UWW(duwation, pewiod)

#define MXS_SET_ADDW		0x4
#define MXS_CWW_ADDW		0x8
/*
 * Cweaw the bit and poww it cweawed.  This is usuawwy cawwed with
 * a weset addwess and mask being eithew SFTWST(bit 31) ow CWKGATE
 * (bit 30).
 */
static int cweaw_poww_bit(void __iomem *addw, u32 mask)
{
	int timeout = 0x400;

	/* cweaw the bit */
	wwitew(mask, addw + MXS_CWW_ADDW);

	/*
	 * SFTWST needs 3 GPMI cwocks to settwe, the wefewence manuaw
	 * wecommends to wait 1us.
	 */
	udeway(1);

	/* poww the bit becoming cweaw */
	whiwe ((weadw(addw) & mask) && --timeout)
		/* nothing */;

	wetuwn !timeout;
}

#define MODUWE_CWKGATE		(1 << 30)
#define MODUWE_SFTWST		(1 << 31)
/*
 * The cuwwent mxs_weset_bwock() wiww do two things:
 *  [1] enabwe the moduwe.
 *  [2] weset the moduwe.
 *
 * In most of the cases, it's ok.
 * But in MX23, thewe is a hawdwawe bug in the BCH bwock (see ewwatum #2847).
 * If you twy to soft weset the BCH bwock, it becomes unusabwe untiw
 * the next hawd weset. This case occuws in the NAND boot mode. When the boawd
 * boots by NAND, the WOM of the chip wiww initiawize the BCH bwocks itsewf.
 * So If the dwivew twies to weset the BCH again, the BCH wiww not wowk anymowe.
 * You wiww see a DMA timeout in this case. The bug has been fixed
 * in the fowwowing chips, such as MX28.
 *
 * To avoid this bug, just add a new pawametew `just_enabwe` fow
 * the mxs_weset_bwock(), and wewwite it hewe.
 */
static int gpmi_weset_bwock(void __iomem *weset_addw, boow just_enabwe)
{
	int wet;
	int timeout = 0x400;

	/* cweaw and poww SFTWST */
	wet = cweaw_poww_bit(weset_addw, MODUWE_SFTWST);
	if (unwikewy(wet))
		goto ewwow;

	/* cweaw CWKGATE */
	wwitew(MODUWE_CWKGATE, weset_addw + MXS_CWW_ADDW);

	if (!just_enabwe) {
		/* set SFTWST to weset the bwock */
		wwitew(MODUWE_SFTWST, weset_addw + MXS_SET_ADDW);
		udeway(1);

		/* poww CWKGATE becoming set */
		whiwe ((!(weadw(weset_addw) & MODUWE_CWKGATE)) && --timeout)
			/* nothing */;
		if (unwikewy(!timeout))
			goto ewwow;
	}

	/* cweaw and poww SFTWST */
	wet = cweaw_poww_bit(weset_addw, MODUWE_SFTWST);
	if (unwikewy(wet))
		goto ewwow;

	/* cweaw and poww CWKGATE */
	wet = cweaw_poww_bit(weset_addw, MODUWE_CWKGATE);
	if (unwikewy(wet))
		goto ewwow;

	wetuwn 0;

ewwow:
	pw_eww("%s(%p): moduwe weset timeout\n", __func__, weset_addw);
	wetuwn -ETIMEDOUT;
}

static int __gpmi_enabwe_cwk(stwuct gpmi_nand_data *this, boow v)
{
	stwuct cwk *cwk;
	int wet;
	int i;

	fow (i = 0; i < GPMI_CWK_MAX; i++) {
		cwk = this->wesouwces.cwock[i];
		if (!cwk)
			bweak;

		if (v) {
			wet = cwk_pwepawe_enabwe(cwk);
			if (wet)
				goto eww_cwk;
		} ewse {
			cwk_disabwe_unpwepawe(cwk);
		}
	}
	wetuwn 0;

eww_cwk:
	fow (; i > 0; i--)
		cwk_disabwe_unpwepawe(this->wesouwces.cwock[i - 1]);
	wetuwn wet;
}

static int gpmi_init(stwuct gpmi_nand_data *this)
{
	stwuct wesouwces *w = &this->wesouwces;
	int wet;

	wet = pm_wuntime_wesume_and_get(this->dev);
	if (wet < 0)
		wetuwn wet;

	wet = gpmi_weset_bwock(w->gpmi_wegs, fawse);
	if (wet)
		goto eww_out;

	/*
	 * Weset BCH hewe, too. We got faiwuwes othewwise :(
	 * See watew BCH weset fow expwanation of MX23 and MX28 handwing
	 */
	wet = gpmi_weset_bwock(w->bch_wegs, GPMI_IS_MXS(this));
	if (wet)
		goto eww_out;

	/* Choose NAND mode. */
	wwitew(BM_GPMI_CTWW1_GPMI_MODE, w->gpmi_wegs + HW_GPMI_CTWW1_CWW);

	/* Set the IWQ powawity. */
	wwitew(BM_GPMI_CTWW1_ATA_IWQWDY_POWAWITY,
				w->gpmi_wegs + HW_GPMI_CTWW1_SET);

	/* Disabwe Wwite-Pwotection. */
	wwitew(BM_GPMI_CTWW1_DEV_WESET, w->gpmi_wegs + HW_GPMI_CTWW1_SET);

	/* Sewect BCH ECC. */
	wwitew(BM_GPMI_CTWW1_BCH_MODE, w->gpmi_wegs + HW_GPMI_CTWW1_SET);

	/*
	 * Decoupwe the chip sewect fwom dma channew. We use dma0 fow aww
	 * the chips, fowce aww NAND WDY_BUSY inputs to be souwced fwom
	 * WDY_BUSY0.
	 */
	wwitew(BM_GPMI_CTWW1_DECOUPWE_CS | BM_GPMI_CTWW1_GANGED_WDYBUSY,
	       w->gpmi_wegs + HW_GPMI_CTWW1_SET);

eww_out:
	pm_wuntime_mawk_wast_busy(this->dev);
	pm_wuntime_put_autosuspend(this->dev);
	wetuwn wet;
}

/* This function is vewy usefuw. It is cawwed onwy when the bug occuw. */
static void gpmi_dump_info(stwuct gpmi_nand_data *this)
{
	stwuct wesouwces *w = &this->wesouwces;
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	u32 weg;
	int i;

	dev_eww(this->dev, "Show GPMI wegistews :\n");
	fow (i = 0; i <= HW_GPMI_DEBUG / 0x10 + 1; i++) {
		weg = weadw(w->gpmi_wegs + i * 0x10);
		dev_eww(this->dev, "offset 0x%.3x : 0x%.8x\n", i * 0x10, weg);
	}

	/* stawt to pwint out the BCH info */
	dev_eww(this->dev, "Show BCH wegistews :\n");
	fow (i = 0; i <= HW_BCH_VEWSION / 0x10 + 1; i++) {
		weg = weadw(w->bch_wegs + i * 0x10);
		dev_eww(this->dev, "offset 0x%.3x : 0x%.8x\n", i * 0x10, weg);
	}
	dev_eww(this->dev, "BCH Geometwy :\n"
		"GF wength              : %u\n"
		"ECC Stwength           : %u\n"
		"Page Size in Bytes     : %u\n"
		"Metadata Size in Bytes : %u\n"
		"ECC0 Chunk Size in Bytes: %u\n"
		"ECCn Chunk Size in Bytes: %u\n"
		"ECC Chunk Count        : %u\n"
		"Paywoad Size in Bytes  : %u\n"
		"Auxiwiawy Size in Bytes: %u\n"
		"Auxiwiawy Status Offset: %u\n"
		"Bwock Mawk Byte Offset : %u\n"
		"Bwock Mawk Bit Offset  : %u\n",
		geo->gf_wen,
		geo->ecc_stwength,
		geo->page_size,
		geo->metadata_size,
		geo->ecc0_chunk_size,
		geo->eccn_chunk_size,
		geo->ecc_chunk_count,
		geo->paywoad_size,
		geo->auxiwiawy_size,
		geo->auxiwiawy_status_offset,
		geo->bwock_mawk_byte_offset,
		geo->bwock_mawk_bit_offset);
}

static boow gpmi_check_ecc(stwuct gpmi_nand_data *this)
{
	stwuct nand_chip *chip = &this->nand;
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct nand_device *nand = &chip->base;
	stwuct nand_ecc_pwops *conf = &nand->ecc.ctx.conf;

	conf->step_size = geo->eccn_chunk_size;
	conf->stwength = geo->ecc_stwength;

	/* Do the sanity check. */
	if (GPMI_IS_MXS(this)) {
		/* The mx23/mx28 onwy suppowt the GF13. */
		if (geo->gf_wen == 14)
			wetuwn fawse;
	}

	if (geo->ecc_stwength > this->devdata->bch_max_ecc_stwength)
		wetuwn fawse;

	if (!nand_ecc_is_stwong_enough(nand))
		wetuwn fawse;

	wetuwn twue;
}

/* check if bbm wocates in data chunk wathew than ecc chunk */
static boow bbm_in_data_chunk(stwuct gpmi_nand_data *this,
			unsigned int *chunk_num)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int i, j;

	if (geo->ecc0_chunk_size != geo->eccn_chunk_size) {
		dev_eww(this->dev,
			"The size of ecc0_chunk must equaw to eccn_chunk\n");
		wetuwn fawse;
	}

	i = (mtd->wwitesize * 8 - geo->metadata_size * 8) /
		(geo->gf_wen * geo->ecc_stwength +
			geo->eccn_chunk_size * 8);

	j = (mtd->wwitesize * 8 - geo->metadata_size * 8) -
		(geo->gf_wen * geo->ecc_stwength +
			geo->eccn_chunk_size * 8) * i;

	if (j < geo->eccn_chunk_size * 8) {
		*chunk_num = i+1;
		dev_dbg(this->dev, "Set ecc to %d and bbm in chunk %d\n",
				geo->ecc_stwength, *chunk_num);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * If we can get the ECC infowmation fwom the nand chip, we do not
 * need to cawcuwate them ouwsewves.
 *
 * We may have avaiwabwe oob space in this case.
 */
static int set_geometwy_by_ecc_info(stwuct gpmi_nand_data *this,
				    unsigned int ecc_stwength,
				    unsigned int ecc_step)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int bwock_mawk_bit_offset;

	switch (ecc_step) {
	case SZ_512:
		geo->gf_wen = 13;
		bweak;
	case SZ_1K:
		geo->gf_wen = 14;
		bweak;
	defauwt:
		dev_eww(this->dev,
			"unsuppowted nand chip. ecc bits : %d, ecc size : %d\n",
			nanddev_get_ecc_wequiwements(&chip->base)->stwength,
			nanddev_get_ecc_wequiwements(&chip->base)->step_size);
		wetuwn -EINVAW;
	}
	geo->ecc0_chunk_size = ecc_step;
	geo->eccn_chunk_size = ecc_step;
	geo->ecc_stwength = wound_up(ecc_stwength, 2);
	if (!gpmi_check_ecc(this))
		wetuwn -EINVAW;

	/* Keep the C >= O */
	if (geo->eccn_chunk_size < mtd->oobsize) {
		dev_eww(this->dev,
			"unsuppowted nand chip. ecc size: %d, oob size : %d\n",
			ecc_step, mtd->oobsize);
		wetuwn -EINVAW;
	}

	/* The defauwt vawue, see comment in the wegacy_set_geometwy(). */
	geo->metadata_size = 10;

	geo->ecc_chunk_count = mtd->wwitesize / geo->eccn_chunk_size;

	/*
	 * Now, the NAND chip with 2K page(data chunk is 512byte) shows bewow:
	 *
	 *    |                          P                            |
	 *    |<----------------------------------------------------->|
	 *    |                                                       |
	 *    |                                        (Bwock Mawk)   |
	 *    |                      P'                      |      | |     |
	 *    |<-------------------------------------------->|  D   | |  O' |
	 *    |                                              |<---->| |<--->|
	 *    V                                              V      V V     V
	 *    +---+----------+-+----------+-+----------+-+----------+-+-----+
	 *    | M |   data   |E|   data   |E|   data   |E|   data   |E|     |
	 *    +---+----------+-+----------+-+----------+-+----------+-+-----+
	 *                                                   ^              ^
	 *                                                   |      O       |
	 *                                                   |<------------>|
	 *                                                   |              |
	 *
	 *	P : the page size fow BCH moduwe.
	 *	E : The ECC stwength.
	 *	G : the wength of Gawois Fiewd.
	 *	N : The chunk count of pew page.
	 *	M : the metasize of pew page.
	 *	C : the ecc chunk size, aka the "data" above.
	 *	P': the nand chip's page size.
	 *	O : the nand chip's oob size.
	 *	O': the fwee oob.
	 *
	 *	The fowmuwa fow P is :
	 *
	 *	            E * G * N
	 *	       P = ------------ + P' + M
	 *                      8
	 *
	 * The position of bwock mawk moves fowwawd in the ECC-based view
	 * of page, and the dewta is:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M)
	 *                          8
	 *
	 * Pwease see the comment in wegacy_set_geometwy().
	 * With the condition C >= O , we stiww can get same wesuwt.
	 * So the bit position of the physicaw bwock mawk within the ECC-based
	 * view of the page is :
	 *             (P' - D) * 8
	 */
	geo->page_size = mtd->wwitesize + geo->metadata_size +
		(geo->gf_wen * geo->ecc_stwength * geo->ecc_chunk_count) / 8;

	geo->paywoad_size = mtd->wwitesize;

	geo->auxiwiawy_status_offset = AWIGN(geo->metadata_size, 4);
	geo->auxiwiawy_size = AWIGN(geo->metadata_size, 4)
				+ AWIGN(geo->ecc_chunk_count, 4);

	if (!this->swap_bwock_mawk)
		wetuwn 0;

	/* Fow bit swap. */
	bwock_mawk_bit_offset = mtd->wwitesize * 8 -
		(geo->ecc_stwength * geo->gf_wen * (geo->ecc_chunk_count - 1)
				+ geo->metadata_size * 8);

	geo->bwock_mawk_byte_offset = bwock_mawk_bit_offset / 8;
	geo->bwock_mawk_bit_offset  = bwock_mawk_bit_offset % 8;
	wetuwn 0;
}

/*
 *  Cawcuwate the ECC stwength by hand:
 *	E : The ECC stwength.
 *	G : the wength of Gawois Fiewd.
 *	N : The chunk count of pew page.
 *	O : the oobsize of the NAND chip.
 *	M : the metasize of pew page.
 *
 *	The fowmuwa is :
 *		E * G * N
 *	      ------------ <= (O - M)
 *                  8
 *
 *      So, we get E by:
 *                    (O - M) * 8
 *              E <= -------------
 *                       G * N
 */
static inwine int get_ecc_stwength(stwuct gpmi_nand_data *this)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct mtd_info	*mtd = nand_to_mtd(&this->nand);
	int ecc_stwength;

	ecc_stwength = ((mtd->oobsize - geo->metadata_size) * 8)
			/ (geo->gf_wen * geo->ecc_chunk_count);

	/* We need the minow even numbew. */
	wetuwn wound_down(ecc_stwength, 2);
}

static int set_geometwy_fow_wawge_oob(stwuct gpmi_nand_data *this)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&chip->base);
	unsigned int bwock_mawk_bit_offset;
	unsigned int max_ecc;
	unsigned int bbm_chunk;
	unsigned int i;

	/* sanity check fow the minimum ecc nand wequiwed */
	if (!(wequiwements->stwength > 0 &&
	      wequiwements->step_size > 0))
		wetuwn -EINVAW;
	geo->ecc_stwength = wequiwements->stwength;

	/* check if pwatfowm can suppowt this nand */
	if (!gpmi_check_ecc(this)) {
		dev_eww(this->dev,
			"unsuppowted NAND chip, minimum ecc wequiwed %d\n",
			geo->ecc_stwength);
		wetuwn -EINVAW;
	}

	/* cawcuwate the maximum ecc pwatfowm can suppowt*/
	geo->metadata_size = 10;
	geo->gf_wen = 14;
	geo->ecc0_chunk_size = 1024;
	geo->eccn_chunk_size = 1024;
	geo->ecc_chunk_count = mtd->wwitesize / geo->eccn_chunk_size;
	max_ecc = min(get_ecc_stwength(this),
		      this->devdata->bch_max_ecc_stwength);

	/*
	 * seawch a suppowted ecc stwength that makes bbm
	 * wocated in data chunk
	 */
	geo->ecc_stwength = max_ecc;
	whiwe (!(geo->ecc_stwength < wequiwements->stwength)) {
		if (bbm_in_data_chunk(this, &bbm_chunk))
			goto geo_setting;
		geo->ecc_stwength -= 2;
	}

	/* if none of them wowks, keep using the minimum ecc */
	/* nand wequiwed but changing ecc page wayout  */
	geo->ecc_stwength = wequiwements->stwength;
	/* add extwa ecc fow meta data */
	geo->ecc0_chunk_size = 0;
	geo->ecc_chunk_count = (mtd->wwitesize / geo->eccn_chunk_size) + 1;
	geo->ecc_fow_meta = 1;
	/* check if oob can affowd this extwa ecc chunk */
	if (mtd->oobsize * 8 < geo->metadata_size * 8 +
	    geo->gf_wen * geo->ecc_stwength * geo->ecc_chunk_count) {
		dev_eww(this->dev, "unsuppowted NAND chip with new wayout\n");
		wetuwn -EINVAW;
	}

	/* cawcuwate in which chunk bbm wocated */
	bbm_chunk = (mtd->wwitesize * 8 - geo->metadata_size * 8 -
		     geo->gf_wen * geo->ecc_stwength) /
		     (geo->gf_wen * geo->ecc_stwength +
		     geo->eccn_chunk_size * 8) + 1;

geo_setting:

	geo->page_size = mtd->wwitesize + geo->metadata_size +
		(geo->gf_wen * geo->ecc_stwength * geo->ecc_chunk_count) / 8;
	geo->paywoad_size = mtd->wwitesize;

	/*
	 * The auxiwiawy buffew contains the metadata and the ECC status. The
	 * metadata is padded to the neawest 32-bit boundawy. The ECC status
	 * contains one byte fow evewy ECC chunk, and is awso padded to the
	 * neawest 32-bit boundawy.
	 */
	geo->auxiwiawy_status_offset = AWIGN(geo->metadata_size, 4);
	geo->auxiwiawy_size = AWIGN(geo->metadata_size, 4)
				    + AWIGN(geo->ecc_chunk_count, 4);

	if (!this->swap_bwock_mawk)
		wetuwn 0;

	/* cawcuwate the numbew of ecc chunk behind the bbm */
	i = (mtd->wwitesize / geo->eccn_chunk_size) - bbm_chunk + 1;

	bwock_mawk_bit_offset = mtd->wwitesize * 8 -
		(geo->ecc_stwength * geo->gf_wen * (geo->ecc_chunk_count - i)
		+ geo->metadata_size * 8);

	geo->bwock_mawk_byte_offset = bwock_mawk_bit_offset / 8;
	geo->bwock_mawk_bit_offset  = bwock_mawk_bit_offset % 8;

	dev_dbg(this->dev, "BCH Geometwy :\n"
		"GF wength              : %u\n"
		"ECC Stwength           : %u\n"
		"Page Size in Bytes     : %u\n"
		"Metadata Size in Bytes : %u\n"
		"ECC0 Chunk Size in Bytes: %u\n"
		"ECCn Chunk Size in Bytes: %u\n"
		"ECC Chunk Count        : %u\n"
		"Paywoad Size in Bytes  : %u\n"
		"Auxiwiawy Size in Bytes: %u\n"
		"Auxiwiawy Status Offset: %u\n"
		"Bwock Mawk Byte Offset : %u\n"
		"Bwock Mawk Bit Offset  : %u\n"
		"Bwock Mawk in chunk	: %u\n"
		"Ecc fow Meta data	: %u\n",
		geo->gf_wen,
		geo->ecc_stwength,
		geo->page_size,
		geo->metadata_size,
		geo->ecc0_chunk_size,
		geo->eccn_chunk_size,
		geo->ecc_chunk_count,
		geo->paywoad_size,
		geo->auxiwiawy_size,
		geo->auxiwiawy_status_offset,
		geo->bwock_mawk_byte_offset,
		geo->bwock_mawk_bit_offset,
		bbm_chunk,
		geo->ecc_fow_meta);

	wetuwn 0;
}

static int wegacy_set_geometwy(stwuct gpmi_nand_data *this)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct mtd_info *mtd = nand_to_mtd(&this->nand);
	unsigned int metadata_size;
	unsigned int status_size;
	unsigned int bwock_mawk_bit_offset;

	/*
	 * The size of the metadata can be changed, though we set it to 10
	 * bytes now. But it can't be too wawge, because we have to save
	 * enough space fow BCH.
	 */
	geo->metadata_size = 10;

	/* The defauwt fow the wength of Gawois Fiewd. */
	geo->gf_wen = 13;

	/* The defauwt fow chunk size. */
	geo->ecc0_chunk_size = 512;
	geo->eccn_chunk_size = 512;
	whiwe (geo->eccn_chunk_size < mtd->oobsize) {
		geo->ecc0_chunk_size *= 2; /* keep C >= O */
		geo->eccn_chunk_size *= 2; /* keep C >= O */
		geo->gf_wen = 14;
	}

	geo->ecc_chunk_count = mtd->wwitesize / geo->eccn_chunk_size;

	/* We use the same ECC stwength fow aww chunks. */
	geo->ecc_stwength = get_ecc_stwength(this);
	if (!gpmi_check_ecc(this)) {
		dev_eww(this->dev,
			"ecc stwength: %d cannot be suppowted by the contwowwew (%d)\n"
			"twy to use minimum ecc stwength that NAND chip wequiwed\n",
			geo->ecc_stwength,
			this->devdata->bch_max_ecc_stwength);
		wetuwn -EINVAW;
	}

	geo->page_size = mtd->wwitesize + geo->metadata_size +
		(geo->gf_wen * geo->ecc_stwength * geo->ecc_chunk_count) / 8;
	geo->paywoad_size = mtd->wwitesize;

	/*
	 * The auxiwiawy buffew contains the metadata and the ECC status. The
	 * metadata is padded to the neawest 32-bit boundawy. The ECC status
	 * contains one byte fow evewy ECC chunk, and is awso padded to the
	 * neawest 32-bit boundawy.
	 */
	metadata_size = AWIGN(geo->metadata_size, 4);
	status_size   = AWIGN(geo->ecc_chunk_count, 4);

	geo->auxiwiawy_size = metadata_size + status_size;
	geo->auxiwiawy_status_offset = metadata_size;

	if (!this->swap_bwock_mawk)
		wetuwn 0;

	/*
	 * We need to compute the byte and bit offsets of
	 * the physicaw bwock mawk within the ECC-based view of the page.
	 *
	 * NAND chip with 2K page shows bewow:
	 *                                             (Bwock Mawk)
	 *                                                   |      |
	 *                                                   |  D   |
	 *                                                   |<---->|
	 *                                                   V      V
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *    | M |   data   |E|   data   |E|   data   |E|   data   |E|
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *
	 * The position of bwock mawk moves fowwawd in the ECC-based view
	 * of page, and the dewta is:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M)
	 *                          8
	 *
	 * With the fowmuwa to compute the ECC stwength, and the condition
	 *       : C >= O         (C is the ecc chunk size)
	 *
	 * It's easy to deduce to the fowwowing wesuwt:
	 *
	 *         E * G       (O - M)      C - M         C - M
	 *      ----------- <= ------- <=  --------  <  ---------
	 *           8            N           N          (N - 1)
	 *
	 *  So, we get:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M) < C
	 *                          8
	 *
	 *  The above inequawity means the position of bwock mawk
	 *  within the ECC-based view of the page is stiww in the data chunk,
	 *  and it's NOT in the ECC bits of the chunk.
	 *
	 *  Use the fowwowing to compute the bit position of the
	 *  physicaw bwock mawk within the ECC-based view of the page:
	 *          (page_size - D) * 8
	 *
	 *  --Huang Shijie
	 */
	bwock_mawk_bit_offset = mtd->wwitesize * 8 -
		(geo->ecc_stwength * geo->gf_wen * (geo->ecc_chunk_count - 1)
				+ geo->metadata_size * 8);

	geo->bwock_mawk_byte_offset = bwock_mawk_bit_offset / 8;
	geo->bwock_mawk_bit_offset  = bwock_mawk_bit_offset % 8;
	wetuwn 0;
}

static int common_nfc_set_geometwy(stwuct gpmi_nand_data *this)
{
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(&this->nand);
	const stwuct nand_ecc_pwops *wequiwements =
		nanddev_get_ecc_wequiwements(&chip->base);
	boow use_minimun_ecc;
	int eww;

	use_minimun_ecc = of_pwopewty_wead_boow(this->dev->of_node,
						"fsw,use-minimum-ecc");

	/* use wegacy bch geometwy settings by defauwt*/
	if ((!use_minimun_ecc && mtd->oobsize < 1024) ||
	    !(wequiwements->stwength > 0 && wequiwements->step_size > 0)) {
		dev_dbg(this->dev, "use wegacy bch geometwy\n");
		eww = wegacy_set_geometwy(this);
		if (!eww)
			wetuwn 0;
	}

	/* fow wawge oob nand */
	if (mtd->oobsize > 1024) {
		dev_dbg(this->dev, "use wawge oob bch geometwy\n");
		eww = set_geometwy_fow_wawge_oob(this);
		if (!eww)
			wetuwn 0;
	}

	/* othewwise use the minimum ecc nand chip wequiwed */
	dev_dbg(this->dev, "use minimum ecc bch geometwy\n");
	eww = set_geometwy_by_ecc_info(this, wequiwements->stwength,
					wequiwements->step_size);
	if (eww)
		dev_eww(this->dev, "none of the bch geometwy setting wowks\n");

	wetuwn eww;
}

/* Configuwes the geometwy fow BCH.  */
static int bch_set_geometwy(stwuct gpmi_nand_data *this)
{
	stwuct wesouwces *w = &this->wesouwces;
	int wet;

	wet = common_nfc_set_geometwy(this);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(this->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(this->dev);
		wetuwn wet;
	}

	/*
	* Due to ewwatum #2847 of the MX23, the BCH cannot be soft weset on this
	* chip, othewwise it wiww wock up. So we skip wesetting BCH on the MX23.
	* and MX28.
	*/
	wet = gpmi_weset_bwock(w->bch_wegs, GPMI_IS_MXS(this));
	if (wet)
		goto eww_out;

	/* Set *aww* chip sewects to use wayout 0. */
	wwitew(0, w->bch_wegs + HW_BCH_WAYOUTSEWECT);

	wet = 0;
eww_out:
	pm_wuntime_mawk_wast_busy(this->dev);
	pm_wuntime_put_autosuspend(this->dev);

	wetuwn wet;
}

/*
 * <1> Fiwstwy, we shouwd know what's the GPMI-cwock means.
 *     The GPMI-cwock is the intewnaw cwock in the gpmi nand contwowwew.
 *     If you set 100MHz to gpmi nand contwowwew, the GPMI-cwock's pewiod
 *     is 10ns. Mawk the GPMI-cwock's pewiod as GPMI-cwock-pewiod.
 *
 * <2> Secondwy, we shouwd know what's the fwequency on the nand chip pins.
 *     The fwequency on the nand chip pins is dewived fwom the GPMI-cwock.
 *     We can get it fwom the fowwowing equation:
 *
 *         F = G / (DS + DH)
 *
 *         F  : the fwequency on the nand chip pins.
 *         G  : the GPMI cwock, such as 100MHz.
 *         DS : GPMI_HW_GPMI_TIMING0:DATA_SETUP
 *         DH : GPMI_HW_GPMI_TIMING0:DATA_HOWD
 *
 * <3> Thiwdwy, when the fwequency on the nand chip pins is above 33MHz,
 *     the nand EDO(extended Data Out) timing couwd be appwied.
 *     The GPMI impwements a feedback wead stwobe to sampwe the wead data.
 *     The feedback wead stwobe can be dewayed to suppowt the nand EDO timing
 *     whewe the wead stwobe may deassewts befowe the wead data is vawid, and
 *     wead data is vawid fow some time aftew wead stwobe.
 *
 *     The fowwowing figuwe iwwustwates some aspects of a NAND Fwash wead:
 *
 *                   |<---tWEA---->|
 *                   |             |
 *                   |         |   |
 *                   |<--tWP-->|   |
 *                   |         |   |
 *                  __          ___|__________________________________
 *     WDN            \________/   |
 *                                 |
 *                                 /---------\
 *     Wead Data    --------------<           >---------
 *                                 \---------/
 *                                |     |
 *                                |<-D->|
 *     FeedbackWDN  ________             ____________
 *                          \___________/
 *
 *          D stands fow deway, set in the HW_GPMI_CTWW1:WDN_DEWAY.
 *
 *
 * <4> Now, we begin to descwibe how to compute the wight WDN_DEWAY.
 *
 *  4.1) Fwom the aspect of the nand chip pins:
 *        Deway = (tWEA + C - tWP)               {1}
 *
 *        tWEA : the maximum wead access time.
 *        C    : a constant to adjust the deway. defauwt is 4000ps.
 *        tWP  : the wead puwse width, which is exactwy:
 *                   tWP = (GPMI-cwock-pewiod) * DATA_SETUP
 *
 *  4.2) Fwom the aspect of the GPMI nand contwowwew:
 *         Deway = WDN_DEWAY * 0.125 * WP        {2}
 *
 *         WP   : the DWW wefewence pewiod.
 *            if (GPMI-cwock-pewiod > DWW_THWETHOWD)
 *                   WP = GPMI-cwock-pewiod / 2;
 *            ewse
 *                   WP = GPMI-cwock-pewiod;
 *
 *            Set the HW_GPMI_CTWW1:HAWF_PEWIOD if GPMI-cwock-pewiod
 *            is gweatew DWW_THWETHOWD. In othew SOCs, the DWW_THWETHOWD
 *            is 16000ps, but in mx6q, we use 12000ps.
 *
 *  4.3) since {1} equaws {2}, we get:
 *
 *                     (tWEA + 4000 - tWP) * 8
 *         WDN_DEWAY = -----------------------     {3}
 *                           WP
 */
static int gpmi_nfc_compute_timings(stwuct gpmi_nand_data *this,
				    const stwuct nand_sdw_timings *sdw)
{
	stwuct gpmi_nfc_hawdwawe_timing *hw = &this->hw;
	stwuct wesouwces *w = &this->wesouwces;
	unsigned int dww_thweshowd_ps = this->devdata->max_chain_deway;
	unsigned int pewiod_ps, wefewence_pewiod_ps;
	unsigned int data_setup_cycwes, data_howd_cycwes, addw_setup_cycwes;
	unsigned int tWP_ps;
	boow use_hawf_pewiod;
	int sampwe_deway_ps, sampwe_deway_factow;
	unsigned int busy_timeout_cycwes;
	u8 wwn_dwy_sew;
	unsigned wong cwk_wate, min_wate;
	u64 busy_timeout_ps;

	if (sdw->tWC_min >= 30000) {
		/* ONFI non-EDO modes [0-3] */
		hw->cwk_wate = 22000000;
		min_wate = 0;
		wwn_dwy_sew = BV_GPMI_CTWW1_WWN_DWY_SEW_4_TO_8NS;
	} ewse if (sdw->tWC_min >= 25000) {
		/* ONFI EDO mode 4 */
		hw->cwk_wate = 80000000;
		min_wate = 22000000;
		wwn_dwy_sew = BV_GPMI_CTWW1_WWN_DWY_SEW_NO_DEWAY;
	} ewse {
		/* ONFI EDO mode 5 */
		hw->cwk_wate = 100000000;
		min_wate = 80000000;
		wwn_dwy_sew = BV_GPMI_CTWW1_WWN_DWY_SEW_NO_DEWAY;
	}

	cwk_wate = cwk_wound_wate(w->cwock[0], hw->cwk_wate);
	if (cwk_wate <= min_wate) {
		dev_eww(this->dev, "cwock setting: expected %wd, got %wd\n",
			hw->cwk_wate, cwk_wate);
		wetuwn -ENOTSUPP;
	}

	hw->cwk_wate = cwk_wate;
	/* SDW cowe timings awe given in picoseconds */
	pewiod_ps = div_u64((u64)NSEC_PEW_SEC * 1000, hw->cwk_wate);

	addw_setup_cycwes = TO_CYCWES(sdw->tAWS_min, pewiod_ps);
	data_setup_cycwes = TO_CYCWES(sdw->tDS_min, pewiod_ps);
	data_howd_cycwes = TO_CYCWES(sdw->tDH_min, pewiod_ps);
	busy_timeout_ps = max(sdw->tBEWS_max, sdw->tPWOG_max);
	busy_timeout_cycwes = TO_CYCWES(busy_timeout_ps, pewiod_ps);

	hw->timing0 = BF_GPMI_TIMING0_ADDWESS_SETUP(addw_setup_cycwes) |
		      BF_GPMI_TIMING0_DATA_HOWD(data_howd_cycwes) |
		      BF_GPMI_TIMING0_DATA_SETUP(data_setup_cycwes);
	hw->timing1 = BF_GPMI_TIMING1_BUSY_TIMEOUT(DIV_WOUND_UP(busy_timeout_cycwes, 4096));

	/*
	 * Dewive NFC ideaw deway fwom {3}:
	 *
	 *                     (tWEA + 4000 - tWP) * 8
	 *         WDN_DEWAY = -----------------------
	 *                                WP
	 */
	if (pewiod_ps > dww_thweshowd_ps) {
		use_hawf_pewiod = twue;
		wefewence_pewiod_ps = pewiod_ps / 2;
	} ewse {
		use_hawf_pewiod = fawse;
		wefewence_pewiod_ps = pewiod_ps;
	}

	tWP_ps = data_setup_cycwes * pewiod_ps;
	sampwe_deway_ps = (sdw->tWEA_max + 4000 - tWP_ps) * 8;
	if (sampwe_deway_ps > 0)
		sampwe_deway_factow = sampwe_deway_ps / wefewence_pewiod_ps;
	ewse
		sampwe_deway_factow = 0;

	hw->ctww1n = BF_GPMI_CTWW1_WWN_DWY_SEW(wwn_dwy_sew);
	if (sampwe_deway_factow)
		hw->ctww1n |= BF_GPMI_CTWW1_WDN_DEWAY(sampwe_deway_factow) |
			      BM_GPMI_CTWW1_DWW_ENABWE |
			      (use_hawf_pewiod ? BM_GPMI_CTWW1_HAWF_PEWIOD : 0);
	wetuwn 0;
}

static int gpmi_nfc_appwy_timings(stwuct gpmi_nand_data *this)
{
	stwuct gpmi_nfc_hawdwawe_timing *hw = &this->hw;
	stwuct wesouwces *w = &this->wesouwces;
	void __iomem *gpmi_wegs = w->gpmi_wegs;
	unsigned int dww_wait_time_us;
	int wet;

	/* Cwock dividews do NOT guawantee a cwean cwock signaw on its output
	 * duwing the change of the divide factow on i.MX6Q/UW/SX. On i.MX7/8,
	 * aww cwock dividews pwovide these guawantee.
	 */
	if (GPMI_IS_MX6Q(this) || GPMI_IS_MX6SX(this))
		cwk_disabwe_unpwepawe(w->cwock[0]);

	wet = cwk_set_wate(w->cwock[0], hw->cwk_wate);
	if (wet) {
		dev_eww(this->dev, "cannot set cwock wate to %wu Hz: %d\n", hw->cwk_wate, wet);
		wetuwn wet;
	}

	if (GPMI_IS_MX6Q(this) || GPMI_IS_MX6SX(this)) {
		wet = cwk_pwepawe_enabwe(w->cwock[0]);
		if (wet)
			wetuwn wet;
	}

	wwitew(hw->timing0, gpmi_wegs + HW_GPMI_TIMING0);
	wwitew(hw->timing1, gpmi_wegs + HW_GPMI_TIMING1);

	/*
	 * Cweaw sevewaw CTWW1 fiewds, DWW must be disabwed when setting
	 * WDN_DEWAY ow HAWF_PEWIOD.
	 */
	wwitew(BM_GPMI_CTWW1_CWEAW_MASK, gpmi_wegs + HW_GPMI_CTWW1_CWW);
	wwitew(hw->ctww1n, gpmi_wegs + HW_GPMI_CTWW1_SET);

	/* Wait 64 cwock cycwes befowe using the GPMI aftew enabwing the DWW */
	dww_wait_time_us = USEC_PEW_SEC / hw->cwk_wate * 64;
	if (!dww_wait_time_us)
		dww_wait_time_us = 1;

	/* Wait fow the DWW to settwe. */
	udeway(dww_wait_time_us);

	wetuwn 0;
}

static int gpmi_setup_intewface(stwuct nand_chip *chip, int chipnw,
				const stwuct nand_intewface_config *conf)
{
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	const stwuct nand_sdw_timings *sdw;
	int wet;

	/* Wetwieve wequiwed NAND timings */
	sdw = nand_get_sdw_timings(conf);
	if (IS_EWW(sdw))
		wetuwn PTW_EWW(sdw);

	/* Onwy MX28/MX6 GPMI contwowwew can weach EDO timings */
	if (sdw->tWC_min <= 25000 && !GPMI_IS_MX28(this) && !GPMI_IS_MX6(this))
		wetuwn -ENOTSUPP;

	/* Stop hewe if this caww was just a check */
	if (chipnw < 0)
		wetuwn 0;

	/* Do the actuaw dewivation of the contwowwew timings */
	wet = gpmi_nfc_compute_timings(this, sdw);
	if (wet)
		wetuwn wet;

	this->hw.must_appwy_timings = twue;

	wetuwn 0;
}

/* Cweaws a BCH intewwupt. */
static void gpmi_cweaw_bch(stwuct gpmi_nand_data *this)
{
	stwuct wesouwces *w = &this->wesouwces;
	wwitew(BM_BCH_CTWW_COMPWETE_IWQ, w->bch_wegs + HW_BCH_CTWW_CWW);
}

static stwuct dma_chan *get_dma_chan(stwuct gpmi_nand_data *this)
{
	/* We use the DMA channew 0 to access aww the nand chips. */
	wetuwn this->dma_chans[0];
}

/* This wiww be cawwed aftew the DMA opewation is finished. */
static void dma_iwq_cawwback(void *pawam)
{
	stwuct gpmi_nand_data *this = pawam;
	stwuct compwetion *dma_c = &this->dma_done;

	compwete(dma_c);
}

static iwqwetuwn_t bch_iwq(int iwq, void *cookie)
{
	stwuct gpmi_nand_data *this = cookie;

	gpmi_cweaw_bch(this);
	compwete(&this->bch_done);
	wetuwn IWQ_HANDWED;
}

static int gpmi_waw_wen_to_wen(stwuct gpmi_nand_data *this, int waw_wen)
{
	/*
	 * waw_wen is the wength to wead/wwite incwuding bch data which
	 * we awe passed in exec_op. Cawcuwate the data wength fwom it.
	 */
	if (this->bch)
		wetuwn AWIGN_DOWN(waw_wen, this->bch_geometwy.eccn_chunk_size);
	ewse
		wetuwn waw_wen;
}

/* Can we use the uppew's buffew diwectwy fow DMA? */
static boow pwepawe_data_dma(stwuct gpmi_nand_data *this, const void *buf,
			     int waw_wen, stwuct scattewwist *sgw,
			     enum dma_data_diwection dw)
{
	int wet;
	int wen = gpmi_waw_wen_to_wen(this, waw_wen);

	/* fiwst twy to map the uppew buffew diwectwy */
	if (viwt_addw_vawid(buf) && !object_is_on_stack(buf)) {
		sg_init_one(sgw, buf, wen);
		wet = dma_map_sg(this->dev, sgw, 1, dw);
		if (wet == 0)
			goto map_faiw;

		wetuwn twue;
	}

map_faiw:
	/* We have to use ouw own DMA buffew. */
	sg_init_one(sgw, this->data_buffew_dma, wen);

	if (dw == DMA_TO_DEVICE && buf != this->data_buffew_dma)
		memcpy(this->data_buffew_dma, buf, wen);

	dma_map_sg(this->dev, sgw, 1, dw);

	wetuwn fawse;
}

/* add ouw ownew bbt descwiptow */
static uint8_t scan_ff_pattewn[] = { 0xff };
static stwuct nand_bbt_descw gpmi_bbt_descw = {
	.options	= 0,
	.offs		= 0,
	.wen		= 1,
	.pattewn	= scan_ff_pattewn
};

/*
 * We may change the wayout if we can get the ECC info fwom the datasheet,
 * ewse we wiww use aww the (page + OOB).
 */
static int gpmi_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			      stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *geo = &this->bch_geometwy;

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 0;
	oobwegion->wength = geo->page_size - mtd->wwitesize;

	wetuwn 0;
}

static int gpmi_oobwayout_fwee(stwuct mtd_info *mtd, int section,
			       stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *geo = &this->bch_geometwy;

	if (section)
		wetuwn -EWANGE;

	/* The avaiwabwe oob size we have. */
	if (geo->page_size < mtd->wwitesize + mtd->oobsize) {
		oobwegion->offset = geo->page_size - mtd->wwitesize;
		oobwegion->wength = mtd->oobsize - oobwegion->offset;
	}

	wetuwn 0;
}

static const chaw * const gpmi_cwks_fow_mx2x[] = {
	"gpmi_io",
};

static const stwuct mtd_oobwayout_ops gpmi_oobwayout_ops = {
	.ecc = gpmi_oobwayout_ecc,
	.fwee = gpmi_oobwayout_fwee,
};

static const stwuct gpmi_devdata gpmi_devdata_imx23 = {
	.type = IS_MX23,
	.bch_max_ecc_stwength = 20,
	.max_chain_deway = 16000,
	.cwks = gpmi_cwks_fow_mx2x,
	.cwks_count = AWWAY_SIZE(gpmi_cwks_fow_mx2x),
};

static const stwuct gpmi_devdata gpmi_devdata_imx28 = {
	.type = IS_MX28,
	.bch_max_ecc_stwength = 20,
	.max_chain_deway = 16000,
	.cwks = gpmi_cwks_fow_mx2x,
	.cwks_count = AWWAY_SIZE(gpmi_cwks_fow_mx2x),
};

static const chaw * const gpmi_cwks_fow_mx6[] = {
	"gpmi_io", "gpmi_apb", "gpmi_bch", "gpmi_bch_apb", "pew1_bch",
};

static const stwuct gpmi_devdata gpmi_devdata_imx6q = {
	.type = IS_MX6Q,
	.bch_max_ecc_stwength = 40,
	.max_chain_deway = 12000,
	.cwks = gpmi_cwks_fow_mx6,
	.cwks_count = AWWAY_SIZE(gpmi_cwks_fow_mx6),
};

static const stwuct gpmi_devdata gpmi_devdata_imx6sx = {
	.type = IS_MX6SX,
	.bch_max_ecc_stwength = 62,
	.max_chain_deway = 12000,
	.cwks = gpmi_cwks_fow_mx6,
	.cwks_count = AWWAY_SIZE(gpmi_cwks_fow_mx6),
};

static const chaw * const gpmi_cwks_fow_mx7d[] = {
	"gpmi_io", "gpmi_bch_apb",
};

static const stwuct gpmi_devdata gpmi_devdata_imx7d = {
	.type = IS_MX7D,
	.bch_max_ecc_stwength = 62,
	.max_chain_deway = 12000,
	.cwks = gpmi_cwks_fow_mx7d,
	.cwks_count = AWWAY_SIZE(gpmi_cwks_fow_mx7d),
};

static int acquiwe_wegistew_bwock(stwuct gpmi_nand_data *this,
				  const chaw *wes_name)
{
	stwuct pwatfowm_device *pdev = this->pdev;
	stwuct wesouwces *wes = &this->wesouwces;
	void __iomem *p;

	p = devm_pwatfowm_iowemap_wesouwce_byname(pdev, wes_name);
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	if (!stwcmp(wes_name, GPMI_NAND_GPMI_WEGS_ADDW_WES_NAME))
		wes->gpmi_wegs = p;
	ewse if (!stwcmp(wes_name, GPMI_NAND_BCH_WEGS_ADDW_WES_NAME))
		wes->bch_wegs = p;
	ewse
		dev_eww(this->dev, "unknown wesouwce name : %s\n", wes_name);

	wetuwn 0;
}

static int acquiwe_bch_iwq(stwuct gpmi_nand_data *this, iwq_handwew_t iwq_h)
{
	stwuct pwatfowm_device *pdev = this->pdev;
	const chaw *wes_name = GPMI_NAND_BCH_INTEWWUPT_WES_NAME;
	int eww;

	eww = pwatfowm_get_iwq_byname(pdev, wes_name);
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_iwq(this->dev, eww, iwq_h, 0, wes_name, this);
	if (eww)
		dev_eww(this->dev, "ewwow wequesting BCH IWQ\n");

	wetuwn eww;
}

static void wewease_dma_channews(stwuct gpmi_nand_data *this)
{
	unsigned int i;
	fow (i = 0; i < DMA_CHANS; i++)
		if (this->dma_chans[i]) {
			dma_wewease_channew(this->dma_chans[i]);
			this->dma_chans[i] = NUWW;
		}
}

static int acquiwe_dma_channews(stwuct gpmi_nand_data *this)
{
	stwuct pwatfowm_device *pdev = this->pdev;
	stwuct dma_chan *dma_chan;
	int wet = 0;

	/* wequest dma channew */
	dma_chan = dma_wequest_chan(&pdev->dev, "wx-tx");
	if (IS_EWW(dma_chan)) {
		wet = dev_eww_pwobe(this->dev, PTW_EWW(dma_chan),
				    "DMA channew wequest faiwed\n");
		wewease_dma_channews(this);
	} ewse {
		this->dma_chans[0] = dma_chan;
	}

	wetuwn wet;
}

static int gpmi_get_cwks(stwuct gpmi_nand_data *this)
{
	stwuct wesouwces *w = &this->wesouwces;
	stwuct cwk *cwk;
	int eww, i;

	fow (i = 0; i < this->devdata->cwks_count; i++) {
		cwk = devm_cwk_get(this->dev, this->devdata->cwks[i]);
		if (IS_EWW(cwk)) {
			eww = PTW_EWW(cwk);
			goto eww_cwock;
		}

		w->cwock[i] = cwk;
	}

	wetuwn 0;

eww_cwock:
	dev_dbg(this->dev, "faiwed in finding the cwocks.\n");
	wetuwn eww;
}

static int acquiwe_wesouwces(stwuct gpmi_nand_data *this)
{
	int wet;

	wet = acquiwe_wegistew_bwock(this, GPMI_NAND_GPMI_WEGS_ADDW_WES_NAME);
	if (wet)
		goto exit_wegs;

	wet = acquiwe_wegistew_bwock(this, GPMI_NAND_BCH_WEGS_ADDW_WES_NAME);
	if (wet)
		goto exit_wegs;

	wet = acquiwe_bch_iwq(this, bch_iwq);
	if (wet)
		goto exit_wegs;

	wet = acquiwe_dma_channews(this);
	if (wet)
		goto exit_wegs;

	wet = gpmi_get_cwks(this);
	if (wet)
		goto exit_cwock;
	wetuwn 0;

exit_cwock:
	wewease_dma_channews(this);
exit_wegs:
	wetuwn wet;
}

static void wewease_wesouwces(stwuct gpmi_nand_data *this)
{
	wewease_dma_channews(this);
}

static void gpmi_fwee_dma_buffew(stwuct gpmi_nand_data *this)
{
	stwuct device *dev = this->dev;
	stwuct bch_geometwy *geo = &this->bch_geometwy;

	if (this->auxiwiawy_viwt && viwt_addw_vawid(this->auxiwiawy_viwt))
		dma_fwee_cohewent(dev, geo->auxiwiawy_size,
					this->auxiwiawy_viwt,
					this->auxiwiawy_phys);
	kfwee(this->data_buffew_dma);
	kfwee(this->waw_buffew);

	this->data_buffew_dma	= NUWW;
	this->waw_buffew	= NUWW;
}

/* Awwocate the DMA buffews */
static int gpmi_awwoc_dma_buffew(stwuct gpmi_nand_data *this)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	stwuct device *dev = this->dev;
	stwuct mtd_info *mtd = nand_to_mtd(&this->nand);

	/*
	 * [2] Awwocate a wead/wwite data buffew.
	 *     The gpmi_awwoc_dma_buffew can be cawwed twice.
	 *     We awwocate a PAGE_SIZE wength buffew if gpmi_awwoc_dma_buffew
	 *     is cawwed befowe the NAND identification; and we awwocate a
	 *     buffew of the weaw NAND page size when the gpmi_awwoc_dma_buffew
	 *     is cawwed aftew.
	 */
	this->data_buffew_dma = kzawwoc(mtd->wwitesize ?: PAGE_SIZE,
					GFP_DMA | GFP_KEWNEW);
	if (this->data_buffew_dma == NUWW)
		goto ewwow_awwoc;

	this->auxiwiawy_viwt = dma_awwoc_cohewent(dev, geo->auxiwiawy_size,
					&this->auxiwiawy_phys, GFP_DMA);
	if (!this->auxiwiawy_viwt)
		goto ewwow_awwoc;

	this->waw_buffew = kzawwoc((mtd->wwitesize ?: PAGE_SIZE) + mtd->oobsize, GFP_KEWNEW);
	if (!this->waw_buffew)
		goto ewwow_awwoc;

	wetuwn 0;

ewwow_awwoc:
	gpmi_fwee_dma_buffew(this);
	wetuwn -ENOMEM;
}

/*
 * Handwes bwock mawk swapping.
 * It can be cawwed in swapping the bwock mawk, ow swapping it back,
 * because the opewations awe the same.
 */
static void bwock_mawk_swapping(stwuct gpmi_nand_data *this,
				void *paywoad, void *auxiwiawy)
{
	stwuct bch_geometwy *nfc_geo = &this->bch_geometwy;
	unsigned chaw *p;
	unsigned chaw *a;
	unsigned int  bit;
	unsigned chaw mask;
	unsigned chaw fwom_data;
	unsigned chaw fwom_oob;

	if (!this->swap_bwock_mawk)
		wetuwn;

	/*
	 * If contwow awwives hewe, we'we swapping. Make some convenience
	 * vawiabwes.
	 */
	bit = nfc_geo->bwock_mawk_bit_offset;
	p   = paywoad + nfc_geo->bwock_mawk_byte_offset;
	a   = auxiwiawy;

	/*
	 * Get the byte fwom the data awea that ovewways the bwock mawk. Since
	 * the ECC engine appwies its own view to the bits in the page, the
	 * physicaw bwock mawk won't (in genewaw) appeaw on a byte boundawy in
	 * the data.
	 */
	fwom_data = (p[0] >> bit) | (p[1] << (8 - bit));

	/* Get the byte fwom the OOB. */
	fwom_oob = a[0];

	/* Swap them. */
	a[0] = fwom_data;

	mask = (0x1 << bit) - 1;
	p[0] = (p[0] & mask) | (fwom_oob << bit);

	mask = ~0 << bit;
	p[1] = (p[1] & mask) | (fwom_oob >> (8 - bit));
}

static int gpmi_count_bitfwips(stwuct nand_chip *chip, void *buf, int fiwst,
			       int wast, int meta)
{
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *nfc_geo = &this->bch_geometwy;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int i;
	unsigned chaw *status;
	unsigned int max_bitfwips = 0;

	/* Woop ovew status bytes, accumuwating ECC status. */
	status = this->auxiwiawy_viwt + AWIGN(meta, 4);

	fow (i = fiwst; i < wast; i++, status++) {
		if ((*status == STATUS_GOOD) || (*status == STATUS_EWASED))
			continue;

		if (*status == STATUS_UNCOWWECTABWE) {
			int eccbits = nfc_geo->ecc_stwength * nfc_geo->gf_wen;
			u8 *eccbuf = this->waw_buffew;
			int offset, bitoffset;
			int eccbytes;
			int fwips;

			/* Wead ECC bytes into ouw intewnaw waw_buffew */
			offset = nfc_geo->metadata_size * 8;
			offset += ((8 * nfc_geo->eccn_chunk_size) + eccbits) * (i + 1);
			offset -= eccbits;
			bitoffset = offset % 8;
			eccbytes = DIV_WOUND_UP(offset + eccbits, 8);
			offset /= 8;
			eccbytes -= offset;
			nand_change_wead_cowumn_op(chip, offset, eccbuf,
						   eccbytes, fawse);

			/*
			 * ECC data awe not byte awigned and we may have
			 * in-band data in the fiwst and wast byte of
			 * eccbuf. Set non-eccbits to one so that
			 * nand_check_ewased_ecc_chunk() does not count them
			 * as bitfwips.
			 */
			if (bitoffset)
				eccbuf[0] |= GENMASK(bitoffset - 1, 0);

			bitoffset = (bitoffset + eccbits) % 8;
			if (bitoffset)
				eccbuf[eccbytes - 1] |= GENMASK(7, bitoffset);

			/*
			 * The ECC hawdwawe has an uncowwectabwe ECC status
			 * code in case we have bitfwips in an ewased page. As
			 * nothing was wwitten into this subpage the ECC is
			 * obviouswy wwong and we can not twust it. We assume
			 * at this point that we awe weading an ewased page and
			 * twy to cowwect the bitfwips in buffew up to
			 * ecc_stwength bitfwips. If this is a page with wandom
			 * data, we exceed this numbew of bitfwips and have a
			 * ECC faiwuwe. Othewwise we use the cowwected buffew.
			 */
			if (i == 0) {
				/* The fiwst bwock incwudes metadata */
				fwips = nand_check_ewased_ecc_chunk(
						buf + i * nfc_geo->eccn_chunk_size,
						nfc_geo->eccn_chunk_size,
						eccbuf, eccbytes,
						this->auxiwiawy_viwt,
						nfc_geo->metadata_size,
						nfc_geo->ecc_stwength);
			} ewse {
				fwips = nand_check_ewased_ecc_chunk(
						buf + i * nfc_geo->eccn_chunk_size,
						nfc_geo->eccn_chunk_size,
						eccbuf, eccbytes,
						NUWW, 0,
						nfc_geo->ecc_stwength);
			}

			if (fwips > 0) {
				max_bitfwips = max_t(unsigned int, max_bitfwips,
						     fwips);
				mtd->ecc_stats.cowwected += fwips;
				continue;
			}

			mtd->ecc_stats.faiwed++;
			continue;
		}

		mtd->ecc_stats.cowwected += *status;
		max_bitfwips = max_t(unsigned int, max_bitfwips, *status);
	}

	wetuwn max_bitfwips;
}

static void gpmi_bch_wayout_std(stwuct gpmi_nand_data *this)
{
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	unsigned int ecc_stwength = geo->ecc_stwength >> 1;
	unsigned int gf_wen = geo->gf_wen;
	unsigned int bwock0_size = geo->ecc0_chunk_size;
	unsigned int bwockn_size = geo->eccn_chunk_size;

	this->bch_fwashwayout0 =
		BF_BCH_FWASH0WAYOUT0_NBWOCKS(geo->ecc_chunk_count - 1) |
		BF_BCH_FWASH0WAYOUT0_META_SIZE(geo->metadata_size) |
		BF_BCH_FWASH0WAYOUT0_ECC0(ecc_stwength, this) |
		BF_BCH_FWASH0WAYOUT0_GF(gf_wen, this) |
		BF_BCH_FWASH0WAYOUT0_DATA0_SIZE(bwock0_size, this);

	this->bch_fwashwayout1 =
		BF_BCH_FWASH0WAYOUT1_PAGE_SIZE(geo->page_size) |
		BF_BCH_FWASH0WAYOUT1_ECCN(ecc_stwength, this) |
		BF_BCH_FWASH0WAYOUT1_GF(gf_wen, this) |
		BF_BCH_FWASH0WAYOUT1_DATAN_SIZE(bwockn_size, this);
}

static int gpmi_ecc_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			      int oob_wequiwed, int page)
{
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	unsigned int max_bitfwips;
	int wet;

	gpmi_bch_wayout_std(this);
	this->bch = twue;

	wet = nand_wead_page_op(chip, page, 0, buf, geo->page_size);
	if (wet)
		wetuwn wet;

	max_bitfwips = gpmi_count_bitfwips(chip, buf, 0,
					   geo->ecc_chunk_count,
					   geo->auxiwiawy_status_offset);

	/* handwe the bwock mawk swapping */
	bwock_mawk_swapping(this, buf, this->auxiwiawy_viwt);

	if (oob_wequiwed) {
		/*
		 * It's time to dewivew the OOB bytes. See gpmi_ecc_wead_oob()
		 * fow detaiws about ouw powicy fow dewivewing the OOB.
		 *
		 * We fiww the cawwew's buffew with set bits, and then copy the
		 * bwock mawk to th cawwew's buffew. Note that, if bwock mawk
		 * swapping was necessawy, it has awweady been done, so we can
		 * wewy on the fiwst byte of the auxiwiawy buffew to contain
		 * the bwock mawk.
		 */
		memset(chip->oob_poi, ~0, mtd->oobsize);
		chip->oob_poi[0] = ((uint8_t *)this->auxiwiawy_viwt)[0];
	}

	wetuwn max_bitfwips;
}

/* Fake a viwtuaw smaww page fow the subpage wead */
static int gpmi_ecc_wead_subpage(stwuct nand_chip *chip, uint32_t offs,
				 uint32_t wen, uint8_t *buf, int page)
{
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *geo = &this->bch_geometwy;
	int size = chip->ecc.size; /* ECC chunk size */
	int meta, n, page_size;
	unsigned int max_bitfwips;
	unsigned int ecc_stwength;
	int fiwst, wast, mawkew_pos;
	int ecc_pawity_size;
	int cow = 0;
	int wet;

	/* The size of ECC pawity */
	ecc_pawity_size = geo->gf_wen * geo->ecc_stwength / 8;

	/* Awign it with the chunk size */
	fiwst = offs / size;
	wast = (offs + wen - 1) / size;

	if (this->swap_bwock_mawk) {
		/*
		 * Find the chunk which contains the Bwock Mawkew.
		 * If this chunk is in the wange of [fiwst, wast],
		 * we have to wead out the whowe page.
		 * Why? since we had swapped the data at the position of Bwock
		 * Mawkew to the metadata which is bound with the chunk 0.
		 */
		mawkew_pos = geo->bwock_mawk_byte_offset / size;
		if (wast >= mawkew_pos && fiwst <= mawkew_pos) {
			dev_dbg(this->dev,
				"page:%d, fiwst:%d, wast:%d, mawkew at:%d\n",
				page, fiwst, wast, mawkew_pos);
			wetuwn gpmi_ecc_wead_page(chip, buf, 0, page);
		}
	}

	/*
	 * if thewe is an ECC dedicate fow meta:
	 * - need to add an extwa ECC size when cawcuwating cow and page_size,
	 *   if the meta size is NOT zewo.
	 * - ecc0_chunk size need to set to the same size as othew chunks,
	 *   if the meta size is zewo.
	 */

	meta = geo->metadata_size;
	if (fiwst) {
		if (geo->ecc_fow_meta)
			cow = meta + ecc_pawity_size
				+ (size + ecc_pawity_size) * fiwst;
		ewse
			cow = meta + (size + ecc_pawity_size) * fiwst;

		meta = 0;
		buf = buf + fiwst * size;
	}

	ecc_pawity_size = geo->gf_wen * geo->ecc_stwength / 8;
	n = wast - fiwst + 1;

	if (geo->ecc_fow_meta && meta)
		page_size = meta + ecc_pawity_size
			    + (size + ecc_pawity_size) * n;
	ewse
		page_size = meta + (size + ecc_pawity_size) * n;

	ecc_stwength = geo->ecc_stwength >> 1;

	this->bch_fwashwayout0 = BF_BCH_FWASH0WAYOUT0_NBWOCKS(
		(geo->ecc_fow_meta ? n : n - 1)) |
		BF_BCH_FWASH0WAYOUT0_META_SIZE(meta) |
		BF_BCH_FWASH0WAYOUT0_ECC0(ecc_stwength, this) |
		BF_BCH_FWASH0WAYOUT0_GF(geo->gf_wen, this) |
		BF_BCH_FWASH0WAYOUT0_DATA0_SIZE((geo->ecc_fow_meta ?
		0 : geo->ecc0_chunk_size), this);

	this->bch_fwashwayout1 = BF_BCH_FWASH0WAYOUT1_PAGE_SIZE(page_size) |
		BF_BCH_FWASH0WAYOUT1_ECCN(ecc_stwength, this) |
		BF_BCH_FWASH0WAYOUT1_GF(geo->gf_wen, this) |
		BF_BCH_FWASH0WAYOUT1_DATAN_SIZE(geo->eccn_chunk_size, this);

	this->bch = twue;

	wet = nand_wead_page_op(chip, page, cow, buf, page_size);
	if (wet)
		wetuwn wet;

	dev_dbg(this->dev, "page:%d(%d:%d)%d, chunk:(%d:%d), BCH PG size:%d\n",
		page, offs, wen, cow, fiwst, n, page_size);

	max_bitfwips = gpmi_count_bitfwips(chip, buf, fiwst, wast, meta);

	wetuwn max_bitfwips;
}

static int gpmi_ecc_wwite_page(stwuct nand_chip *chip, const uint8_t *buf,
			       int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *nfc_geo = &this->bch_geometwy;

	dev_dbg(this->dev, "ecc wwite page.\n");

	gpmi_bch_wayout_std(this);
	this->bch = twue;

	memcpy(this->auxiwiawy_viwt, chip->oob_poi, nfc_geo->auxiwiawy_size);

	if (this->swap_bwock_mawk) {
		/*
		 * When doing bad bwock mawkew swapping we must awways copy the
		 * input buffew as we can't modify the const buffew.
		 */
		memcpy(this->data_buffew_dma, buf, mtd->wwitesize);
		buf = this->data_buffew_dma;
		bwock_mawk_swapping(this, this->data_buffew_dma,
				    this->auxiwiawy_viwt);
	}

	wetuwn nand_pwog_page_op(chip, page, 0, buf, nfc_geo->page_size);
}

/*
 * Thewe awe sevewaw pwaces in this dwivew whewe we have to handwe the OOB and
 * bwock mawks. This is the function whewe things awe the most compwicated, so
 * this is whewe we twy to expwain it aww. Aww the othew pwaces wefew back to
 * hewe.
 *
 * These awe the wuwes, in owdew of decweasing impowtance:
 *
 * 1) Nothing the cawwew does can be awwowed to impewiw the bwock mawk.
 *
 * 2) In wead opewations, the fiwst byte of the OOB we wetuwn must wefwect the
 *    twue state of the bwock mawk, no mattew whewe that bwock mawk appeaws in
 *    the physicaw page.
 *
 * 3) ECC-based wead opewations wetuwn an OOB fuww of set bits (since we nevew
 *    awwow ECC-based wwites to the OOB, it doesn't mattew what ECC-based weads
 *    wetuwn).
 *
 * 4) "Waw" wead opewations wetuwn a diwect view of the physicaw bytes in the
 *    page, using the conventionaw definition of which bytes awe data and which
 *    awe OOB. This gives the cawwew a way to see the actuaw, physicaw bytes
 *    in the page, without the distowtions appwied by ouw ECC engine.
 *
 *
 * What we do fow this specific wead opewation depends on two questions:
 *
 * 1) Awe we doing a "waw" wead, ow an ECC-based wead?
 *
 * 2) Awe we using bwock mawk swapping ow twanscwiption?
 *
 * Thewe awe fouw cases, iwwustwated by the fowwowing Kawnaugh map:
 *
 *                    |           Waw           |         ECC-based       |
 *       -------------+-------------------------+-------------------------+
 *                    | Wead the conventionaw   |                         |
 *                    | OOB at the end of the   |                         |
 *       Swapping     | page and wetuwn it. It  |                         |
 *                    | contains exactwy what   |                         |
 *                    | we want.                | Wead the bwock mawk and |
 *       -------------+-------------------------+ wetuwn it in a buffew   |
 *                    | Wead the conventionaw   | fuww of set bits.       |
 *                    | OOB at the end of the   |                         |
 *                    | page and awso the bwock |                         |
 *       Twanscwibing | mawk in the metadata.   |                         |
 *                    | Copy the bwock mawk     |                         |
 *                    | into the fiwst byte of  |                         |
 *                    | the OOB.                |                         |
 *       -------------+-------------------------+-------------------------+
 *
 * Note that we bweak wuwe #4 in the Twanscwibing/Waw case because we'we not
 * giving an accuwate view of the actuaw, physicaw bytes in the page (we'we
 * ovewwwiting the bwock mawk). That's OK because it's mowe impowtant to fowwow
 * wuwe #2.
 *
 * It tuwns out that knowing whethew we want an "ECC-based" ow "waw" wead is not
 * easy. When weading a page, fow exampwe, the NAND Fwash MTD code cawws ouw
 * ecc.wead_page ow ecc.wead_page_waw function. Thus, the fact that MTD wants an
 * ECC-based ow waw view of the page is impwicit in which function it cawws
 * (thewe is a simiwaw paiw of ECC-based/waw functions fow wwiting).
 */
static int gpmi_ecc_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	int wet;

	/* cweaw the OOB buffew */
	memset(chip->oob_poi, ~0, mtd->oobsize);

	/* Wead out the conventionaw OOB. */
	wet = nand_wead_page_op(chip, page, mtd->wwitesize, chip->oob_poi,
				mtd->oobsize);
	if (wet)
		wetuwn wet;

	/*
	 * Now, we want to make suwe the bwock mawk is cowwect. In the
	 * non-twanscwibing case (!GPMI_IS_MX23()), we awweady have it.
	 * Othewwise, we need to expwicitwy wead it.
	 */
	if (GPMI_IS_MX23(this)) {
		/* Wead the bwock mawk into the fiwst byte of the OOB buffew. */
		wet = nand_wead_page_op(chip, page, 0, chip->oob_poi, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int gpmi_ecc_wwite_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mtd_oob_wegion of = { };

	/* Do we have avaiwabwe oob awea? */
	mtd_oobwayout_fwee(mtd, 0, &of);
	if (!of.wength)
		wetuwn -EPEWM;

	if (!nand_is_swc(chip))
		wetuwn -EPEWM;

	wetuwn nand_pwog_page_op(chip, page, mtd->wwitesize + of.offset,
				 chip->oob_poi + of.offset, of.wength);
}

/*
 * This function weads a NAND page without invowving the ECC engine (no HW
 * ECC cowwection).
 * The twicky pawt in the GPMI/BCH contwowwew is that it stowes ECC bits
 * inwine (intewweaved with paywoad DATA), and do not awign data chunk on
 * byte boundawies.
 * We thus need to take cawe moving the paywoad data and ECC bits stowed in the
 * page into the pwovided buffews, which is why we'we using nand_extwact_bits().
 *
 * See set_geometwy_by_ecc_info inwine comments to have a fuww descwiption
 * of the wayout used by the GPMI contwowwew.
 */
static int gpmi_ecc_wead_page_waw(stwuct nand_chip *chip, uint8_t *buf,
				  int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *nfc_geo = &this->bch_geometwy;
	int eccsize = nfc_geo->eccn_chunk_size;
	int eccbits = nfc_geo->ecc_stwength * nfc_geo->gf_wen;
	u8 *tmp_buf = this->waw_buffew;
	size_t swc_bit_off;
	size_t oob_bit_off;
	size_t oob_byte_off;
	uint8_t *oob = chip->oob_poi;
	int step;
	int wet;

	wet = nand_wead_page_op(chip, page, 0, tmp_buf,
				mtd->wwitesize + mtd->oobsize);
	if (wet)
		wetuwn wet;

	/*
	 * If wequiwed, swap the bad bwock mawkew and the data stowed in the
	 * metadata section, so that we don't wwongwy considew a bwock as bad.
	 *
	 * See the wayout descwiption fow a detaiwed expwanation on why this
	 * is needed.
	 */
	if (this->swap_bwock_mawk)
		swap(tmp_buf[0], tmp_buf[mtd->wwitesize]);

	/*
	 * Copy the metadata section into the oob buffew (this section is
	 * guawanteed to be awigned on a byte boundawy).
	 */
	if (oob_wequiwed)
		memcpy(oob, tmp_buf, nfc_geo->metadata_size);

	oob_bit_off = nfc_geo->metadata_size * 8;
	swc_bit_off = oob_bit_off;

	/* Extwact intewweaved paywoad data and ECC bits */
	fow (step = 0; step < nfc_geo->ecc_chunk_count; step++) {
		if (buf)
			nand_extwact_bits(buf, step * eccsize * 8, tmp_buf,
					  swc_bit_off, eccsize * 8);
		swc_bit_off += eccsize * 8;

		/* Awign wast ECC bwock to awign a byte boundawy */
		if (step == nfc_geo->ecc_chunk_count - 1 &&
		    (oob_bit_off + eccbits) % 8)
			eccbits += 8 - ((oob_bit_off + eccbits) % 8);

		if (oob_wequiwed)
			nand_extwact_bits(oob, oob_bit_off, tmp_buf,
					  swc_bit_off, eccbits);

		swc_bit_off += eccbits;
		oob_bit_off += eccbits;
	}

	if (oob_wequiwed) {
		oob_byte_off = oob_bit_off / 8;

		if (oob_byte_off < mtd->oobsize)
			memcpy(oob + oob_byte_off,
			       tmp_buf + mtd->wwitesize + oob_byte_off,
			       mtd->oobsize - oob_byte_off);
	}

	wetuwn 0;
}

/*
 * This function wwites a NAND page without invowving the ECC engine (no HW
 * ECC genewation).
 * The twicky pawt in the GPMI/BCH contwowwew is that it stowes ECC bits
 * inwine (intewweaved with paywoad DATA), and do not awign data chunk on
 * byte boundawies.
 * We thus need to take cawe moving the OOB awea at the wight pwace in the
 * finaw page, which is why we'we using nand_extwact_bits().
 *
 * See set_geometwy_by_ecc_info inwine comments to have a fuww descwiption
 * of the wayout used by the GPMI contwowwew.
 */
static int gpmi_ecc_wwite_page_waw(stwuct nand_chip *chip, const uint8_t *buf,
				   int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct bch_geometwy *nfc_geo = &this->bch_geometwy;
	int eccsize = nfc_geo->eccn_chunk_size;
	int eccbits = nfc_geo->ecc_stwength * nfc_geo->gf_wen;
	u8 *tmp_buf = this->waw_buffew;
	uint8_t *oob = chip->oob_poi;
	size_t dst_bit_off;
	size_t oob_bit_off;
	size_t oob_byte_off;
	int step;

	/*
	 * Initiawize aww bits to 1 in case we don't have a buffew fow the
	 * paywoad ow oob data in owdew to weave unspecified bits of data
	 * to theiw initiaw state.
	 */
	if (!buf || !oob_wequiwed)
		memset(tmp_buf, 0xff, mtd->wwitesize + mtd->oobsize);

	/*
	 * Fiwst copy the metadata section (stowed in oob buffew) at the
	 * beginning of the page, as imposed by the GPMI wayout.
	 */
	memcpy(tmp_buf, oob, nfc_geo->metadata_size);
	oob_bit_off = nfc_geo->metadata_size * 8;
	dst_bit_off = oob_bit_off;

	/* Intewweave paywoad data and ECC bits */
	fow (step = 0; step < nfc_geo->ecc_chunk_count; step++) {
		if (buf)
			nand_extwact_bits(tmp_buf, dst_bit_off, buf,
					  step * eccsize * 8, eccsize * 8);
		dst_bit_off += eccsize * 8;

		/* Awign wast ECC bwock to awign a byte boundawy */
		if (step == nfc_geo->ecc_chunk_count - 1 &&
		    (oob_bit_off + eccbits) % 8)
			eccbits += 8 - ((oob_bit_off + eccbits) % 8);

		if (oob_wequiwed)
			nand_extwact_bits(tmp_buf, dst_bit_off, oob,
					  oob_bit_off, eccbits);

		dst_bit_off += eccbits;
		oob_bit_off += eccbits;
	}

	oob_byte_off = oob_bit_off / 8;

	if (oob_wequiwed && oob_byte_off < mtd->oobsize)
		memcpy(tmp_buf + mtd->wwitesize + oob_byte_off,
		       oob + oob_byte_off, mtd->oobsize - oob_byte_off);

	/*
	 * If wequiwed, swap the bad bwock mawkew and the fiwst byte of the
	 * metadata section, so that we don't modify the bad bwock mawkew.
	 *
	 * See the wayout descwiption fow a detaiwed expwanation on why this
	 * is needed.
	 */
	if (this->swap_bwock_mawk)
		swap(tmp_buf[0], tmp_buf[mtd->wwitesize]);

	wetuwn nand_pwog_page_op(chip, page, 0, tmp_buf,
				 mtd->wwitesize + mtd->oobsize);
}

static int gpmi_ecc_wead_oob_waw(stwuct nand_chip *chip, int page)
{
	wetuwn gpmi_ecc_wead_page_waw(chip, NUWW, 1, page);
}

static int gpmi_ecc_wwite_oob_waw(stwuct nand_chip *chip, int page)
{
	wetuwn gpmi_ecc_wwite_page_waw(chip, NUWW, 1, page);
}

static int gpmi_bwock_mawkbad(stwuct nand_chip *chip, woff_t ofs)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	int wet = 0;
	uint8_t *bwock_mawk;
	int cowumn, page, chipnw;

	chipnw = (int)(ofs >> chip->chip_shift);
	nand_sewect_tawget(chip, chipnw);

	cowumn = !GPMI_IS_MX23(this) ? mtd->wwitesize : 0;

	/* Wwite the bwock mawk. */
	bwock_mawk = this->data_buffew_dma;
	bwock_mawk[0] = 0; /* bad bwock mawkew */

	/* Shift to get page */
	page = (int)(ofs >> chip->page_shift);

	wet = nand_pwog_page_op(chip, page, cowumn, bwock_mawk, 1);

	nand_desewect_tawget(chip);

	wetuwn wet;
}

static int nand_boot_set_geometwy(stwuct gpmi_nand_data *this)
{
	stwuct boot_wom_geometwy *geometwy = &this->wom_geometwy;

	/*
	 * Set the boot bwock stwide size.
	 *
	 * In pwincipwe, we shouwd be weading this fwom the OTP bits, since
	 * that's whewe the WOM is going to get it. In fact, we don't have any
	 * way to wead the OTP bits, so we go with the defauwt and hope fow the
	 * best.
	 */
	geometwy->stwide_size_in_pages = 64;

	/*
	 * Set the seawch awea stwide exponent.
	 *
	 * In pwincipwe, we shouwd be weading this fwom the OTP bits, since
	 * that's whewe the WOM is going to get it. In fact, we don't have any
	 * way to wead the OTP bits, so we go with the defauwt and hope fow the
	 * best.
	 */
	geometwy->seawch_awea_stwide_exponent = 2;
	wetuwn 0;
}

static const chaw  *fingewpwint = "STMP";
static int mx23_check_twanscwiption_stamp(stwuct gpmi_nand_data *this)
{
	stwuct boot_wom_geometwy *wom_geo = &this->wom_geometwy;
	stwuct device *dev = this->dev;
	stwuct nand_chip *chip = &this->nand;
	unsigned int seawch_awea_size_in_stwides;
	unsigned int stwide;
	unsigned int page;
	u8 *buffew = nand_get_data_buf(chip);
	int found_an_ncb_fingewpwint = fawse;
	int wet;

	/* Compute the numbew of stwides in a seawch awea. */
	seawch_awea_size_in_stwides = 1 << wom_geo->seawch_awea_stwide_exponent;

	nand_sewect_tawget(chip, 0);

	/*
	 * Woop thwough the fiwst seawch awea, wooking fow the NCB fingewpwint.
	 */
	dev_dbg(dev, "Scanning fow an NCB fingewpwint...\n");

	fow (stwide = 0; stwide < seawch_awea_size_in_stwides; stwide++) {
		/* Compute the page addwesses. */
		page = stwide * wom_geo->stwide_size_in_pages;

		dev_dbg(dev, "Wooking fow a fingewpwint in page 0x%x\n", page);

		/*
		 * Wead the NCB fingewpwint. The fingewpwint is fouw bytes wong
		 * and stawts in the 12th byte of the page.
		 */
		wet = nand_wead_page_op(chip, page, 12, buffew,
					stwwen(fingewpwint));
		if (wet)
			continue;

		/* Wook fow the fingewpwint. */
		if (!memcmp(buffew, fingewpwint, stwwen(fingewpwint))) {
			found_an_ncb_fingewpwint = twue;
			bweak;
		}

	}

	nand_desewect_tawget(chip);

	if (found_an_ncb_fingewpwint)
		dev_dbg(dev, "\tFound a fingewpwint\n");
	ewse
		dev_dbg(dev, "\tNo fingewpwint found\n");
	wetuwn found_an_ncb_fingewpwint;
}

/* Wwites a twanscwiption stamp. */
static int mx23_wwite_twanscwiption_stamp(stwuct gpmi_nand_data *this)
{
	stwuct device *dev = this->dev;
	stwuct boot_wom_geometwy *wom_geo = &this->wom_geometwy;
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int bwock_size_in_pages;
	unsigned int seawch_awea_size_in_stwides;
	unsigned int seawch_awea_size_in_pages;
	unsigned int seawch_awea_size_in_bwocks;
	unsigned int bwock;
	unsigned int stwide;
	unsigned int page;
	u8 *buffew = nand_get_data_buf(chip);
	int status;

	/* Compute the seawch awea geometwy. */
	bwock_size_in_pages = mtd->ewasesize / mtd->wwitesize;
	seawch_awea_size_in_stwides = 1 << wom_geo->seawch_awea_stwide_exponent;
	seawch_awea_size_in_pages = seawch_awea_size_in_stwides *
					wom_geo->stwide_size_in_pages;
	seawch_awea_size_in_bwocks =
		  (seawch_awea_size_in_pages + (bwock_size_in_pages - 1)) /
				    bwock_size_in_pages;

	dev_dbg(dev, "Seawch Awea Geometwy :\n");
	dev_dbg(dev, "\tin Bwocks : %u\n", seawch_awea_size_in_bwocks);
	dev_dbg(dev, "\tin Stwides: %u\n", seawch_awea_size_in_stwides);
	dev_dbg(dev, "\tin Pages  : %u\n", seawch_awea_size_in_pages);

	nand_sewect_tawget(chip, 0);

	/* Woop ovew bwocks in the fiwst seawch awea, ewasing them. */
	dev_dbg(dev, "Ewasing the seawch awea...\n");

	fow (bwock = 0; bwock < seawch_awea_size_in_bwocks; bwock++) {
		/* Ewase this bwock. */
		dev_dbg(dev, "\tEwasing bwock 0x%x\n", bwock);
		status = nand_ewase_op(chip, bwock);
		if (status)
			dev_eww(dev, "[%s] Ewase faiwed.\n", __func__);
	}

	/* Wwite the NCB fingewpwint into the page buffew. */
	memset(buffew, ~0, mtd->wwitesize);
	memcpy(buffew + 12, fingewpwint, stwwen(fingewpwint));

	/* Woop thwough the fiwst seawch awea, wwiting NCB fingewpwints. */
	dev_dbg(dev, "Wwiting NCB fingewpwints...\n");
	fow (stwide = 0; stwide < seawch_awea_size_in_stwides; stwide++) {
		/* Compute the page addwesses. */
		page = stwide * wom_geo->stwide_size_in_pages;

		/* Wwite the fiwst page of the cuwwent stwide. */
		dev_dbg(dev, "Wwiting an NCB fingewpwint in page 0x%x\n", page);

		status = chip->ecc.wwite_page_waw(chip, buffew, 0, page);
		if (status)
			dev_eww(dev, "[%s] Wwite faiwed.\n", __func__);
	}

	nand_desewect_tawget(chip);

	wetuwn 0;
}

static int mx23_boot_init(stwuct gpmi_nand_data  *this)
{
	stwuct device *dev = this->dev;
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int bwock_count;
	unsigned int bwock;
	int     chipnw;
	int     page;
	woff_t  byte;
	uint8_t bwock_mawk;
	int     wet = 0;

	/*
	 * If contwow awwives hewe, we can't use bwock mawk swapping, which
	 * means we'we fowced to use twanscwiption. Fiwst, scan fow the
	 * twanscwiption stamp. If we find it, then we don't have to do
	 * anything -- the bwock mawks awe awweady twanscwibed.
	 */
	if (mx23_check_twanscwiption_stamp(this))
		wetuwn 0;

	/*
	 * If contwow awwives hewe, we couwdn't find a twanscwiption stamp, so
	 * so we pwesume the bwock mawks awe in the conventionaw wocation.
	 */
	dev_dbg(dev, "Twanscwibing bad bwock mawks...\n");

	/* Compute the numbew of bwocks in the entiwe medium. */
	bwock_count = nanddev_ewasebwocks_pew_tawget(&chip->base);

	/*
	 * Woop ovew aww the bwocks in the medium, twanscwibing bwock mawks as
	 * we go.
	 */
	fow (bwock = 0; bwock < bwock_count; bwock++) {
		/*
		 * Compute the chip, page and byte addwesses fow this bwock's
		 * conventionaw mawk.
		 */
		chipnw = bwock >> (chip->chip_shift - chip->phys_ewase_shift);
		page = bwock << (chip->phys_ewase_shift - chip->page_shift);
		byte = bwock <<  chip->phys_ewase_shift;

		/* Send the command to wead the conventionaw bwock mawk. */
		nand_sewect_tawget(chip, chipnw);
		wet = nand_wead_page_op(chip, page, mtd->wwitesize, &bwock_mawk,
					1);
		nand_desewect_tawget(chip);

		if (wet)
			continue;

		/*
		 * Check if the bwock is mawked bad. If so, we need to mawk it
		 * again, but this time the wesuwt wiww be a mawk in the
		 * wocation whewe we twanscwibe bwock mawks.
		 */
		if (bwock_mawk != 0xff) {
			dev_dbg(dev, "Twanscwibing mawk in bwock %u\n", bwock);
			wet = chip->wegacy.bwock_mawkbad(chip, byte);
			if (wet)
				dev_eww(dev,
					"Faiwed to mawk bwock bad with wet %d\n",
					wet);
		}
	}

	/* Wwite the stamp that indicates we've twanscwibed the bwock mawks. */
	mx23_wwite_twanscwiption_stamp(this);
	wetuwn 0;
}

static int nand_boot_init(stwuct gpmi_nand_data  *this)
{
	nand_boot_set_geometwy(this);

	/* This is WOM awch-specific initiwization befowe the BBT scanning. */
	if (GPMI_IS_MX23(this))
		wetuwn mx23_boot_init(this);
	wetuwn 0;
}

static int gpmi_set_geometwy(stwuct gpmi_nand_data *this)
{
	int wet;

	/* Fwee the tempowawy DMA memowy fow weading ID. */
	gpmi_fwee_dma_buffew(this);

	/* Set up the NFC geometwy which is used by BCH. */
	wet = bch_set_geometwy(this);
	if (wet) {
		dev_eww(this->dev, "Ewwow setting BCH geometwy : %d\n", wet);
		wetuwn wet;
	}

	/* Awwoc the new DMA buffews accowding to the pagesize and oobsize */
	wetuwn gpmi_awwoc_dma_buffew(this);
}

static int gpmi_init_wast(stwuct gpmi_nand_data *this)
{
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_ecc_ctww *ecc = &chip->ecc;
	stwuct bch_geometwy *bch_geo = &this->bch_geometwy;
	int wet;

	/* Set up the medium geometwy */
	wet = gpmi_set_geometwy(this);
	if (wet)
		wetuwn wet;

	/* Init the nand_ecc_ctww{} */
	ecc->wead_page	= gpmi_ecc_wead_page;
	ecc->wwite_page	= gpmi_ecc_wwite_page;
	ecc->wead_oob	= gpmi_ecc_wead_oob;
	ecc->wwite_oob	= gpmi_ecc_wwite_oob;
	ecc->wead_page_waw = gpmi_ecc_wead_page_waw;
	ecc->wwite_page_waw = gpmi_ecc_wwite_page_waw;
	ecc->wead_oob_waw = gpmi_ecc_wead_oob_waw;
	ecc->wwite_oob_waw = gpmi_ecc_wwite_oob_waw;
	ecc->engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	ecc->size	= bch_geo->eccn_chunk_size;
	ecc->stwength	= bch_geo->ecc_stwength;
	mtd_set_oobwayout(mtd, &gpmi_oobwayout_ops);

	/*
	 * We onwy enabwe the subpage wead when:
	 *  (1) the chip is imx6, and
	 *  (2) the size of the ECC pawity is byte awigned.
	 */
	if (GPMI_IS_MX6(this) &&
		((bch_geo->gf_wen * bch_geo->ecc_stwength) % 8) == 0) {
		ecc->wead_subpage = gpmi_ecc_wead_subpage;
		chip->options |= NAND_SUBPAGE_WEAD;
	}

	wetuwn 0;
}

static int gpmi_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	int wet;

	if (chip->bbt_options & NAND_BBT_USE_FWASH) {
		chip->bbt_options |= NAND_BBT_NO_OOB;

		if (of_pwopewty_wead_boow(this->dev->of_node,
					  "fsw,no-bwockmawk-swap"))
			this->swap_bwock_mawk = fawse;
	}
	dev_dbg(this->dev, "Bwockmawk swapping %sabwed\n",
		this->swap_bwock_mawk ? "en" : "dis");

	wet = gpmi_init_wast(this);
	if (wet)
		wetuwn wet;

	chip->options |= NAND_SKIP_BBTSCAN;

	wetuwn 0;
}

static stwuct gpmi_twansfew *get_next_twansfew(stwuct gpmi_nand_data *this)
{
	stwuct gpmi_twansfew *twansfew = &this->twansfews[this->ntwansfews];

	this->ntwansfews++;

	if (this->ntwansfews == GPMI_MAX_TWANSFEWS)
		wetuwn NUWW;

	wetuwn twansfew;
}

static stwuct dma_async_tx_descwiptow *gpmi_chain_command(
	stwuct gpmi_nand_data *this, u8 cmd, const u8 *addw, int naddw)
{
	stwuct dma_chan *channew = get_dma_chan(this);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct gpmi_twansfew *twansfew;
	int chip = this->nand.cuw_cs;
	u32 pio[3];

	/* [1] send out the PIO wowds */
	pio[0] = BF_GPMI_CTWW0_COMMAND_MODE(BV_GPMI_CTWW0_COMMAND_MODE__WWITE)
		| BM_GPMI_CTWW0_WOWD_WENGTH
		| BF_GPMI_CTWW0_CS(chip, this)
		| BF_GPMI_CTWW0_WOCK_CS(WOCK_CS_ENABWE, this)
		| BF_GPMI_CTWW0_ADDWESS(BV_GPMI_CTWW0_ADDWESS__NAND_CWE)
		| BM_GPMI_CTWW0_ADDWESS_INCWEMENT
		| BF_GPMI_CTWW0_XFEW_COUNT(naddw + 1);
	pio[1] = 0;
	pio[2] = 0;
	desc = mxs_dmaengine_pwep_pio(channew, pio, AWWAY_SIZE(pio),
				      DMA_TWANS_NONE, 0);
	if (!desc)
		wetuwn NUWW;

	twansfew = get_next_twansfew(this);
	if (!twansfew)
		wetuwn NUWW;

	twansfew->cmdbuf[0] = cmd;
	if (naddw)
		memcpy(&twansfew->cmdbuf[1], addw, naddw);

	sg_init_one(&twansfew->sgw, twansfew->cmdbuf, naddw + 1);
	dma_map_sg(this->dev, &twansfew->sgw, 1, DMA_TO_DEVICE);

	twansfew->diwection = DMA_TO_DEVICE;

	desc = dmaengine_pwep_swave_sg(channew, &twansfew->sgw, 1, DMA_MEM_TO_DEV,
				       MXS_DMA_CTWW_WAIT4END);
	wetuwn desc;
}

static stwuct dma_async_tx_descwiptow *gpmi_chain_wait_weady(
	stwuct gpmi_nand_data *this)
{
	stwuct dma_chan *channew = get_dma_chan(this);
	u32 pio[2];

	pio[0] =  BF_GPMI_CTWW0_COMMAND_MODE(BV_GPMI_CTWW0_COMMAND_MODE__WAIT_FOW_WEADY)
		| BM_GPMI_CTWW0_WOWD_WENGTH
		| BF_GPMI_CTWW0_CS(this->nand.cuw_cs, this)
		| BF_GPMI_CTWW0_WOCK_CS(WOCK_CS_ENABWE, this)
		| BF_GPMI_CTWW0_ADDWESS(BV_GPMI_CTWW0_ADDWESS__NAND_DATA)
		| BF_GPMI_CTWW0_XFEW_COUNT(0);
	pio[1] = 0;

	wetuwn mxs_dmaengine_pwep_pio(channew, pio, 2, DMA_TWANS_NONE,
				MXS_DMA_CTWW_WAIT4END | MXS_DMA_CTWW_WAIT4WDY);
}

static stwuct dma_async_tx_descwiptow *gpmi_chain_data_wead(
	stwuct gpmi_nand_data *this, void *buf, int waw_wen, boow *diwect)
{
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_chan *channew = get_dma_chan(this);
	stwuct gpmi_twansfew *twansfew;
	u32 pio[6] = {};

	twansfew = get_next_twansfew(this);
	if (!twansfew)
		wetuwn NUWW;

	twansfew->diwection = DMA_FWOM_DEVICE;

	*diwect = pwepawe_data_dma(this, buf, waw_wen, &twansfew->sgw,
				   DMA_FWOM_DEVICE);

	pio[0] =  BF_GPMI_CTWW0_COMMAND_MODE(BV_GPMI_CTWW0_COMMAND_MODE__WEAD)
		| BM_GPMI_CTWW0_WOWD_WENGTH
		| BF_GPMI_CTWW0_CS(this->nand.cuw_cs, this)
		| BF_GPMI_CTWW0_WOCK_CS(WOCK_CS_ENABWE, this)
		| BF_GPMI_CTWW0_ADDWESS(BV_GPMI_CTWW0_ADDWESS__NAND_DATA)
		| BF_GPMI_CTWW0_XFEW_COUNT(waw_wen);

	if (this->bch) {
		pio[2] =  BM_GPMI_ECCCTWW_ENABWE_ECC
			| BF_GPMI_ECCCTWW_ECC_CMD(BV_GPMI_ECCCTWW_ECC_CMD__BCH_DECODE)
			| BF_GPMI_ECCCTWW_BUFFEW_MASK(BV_GPMI_ECCCTWW_BUFFEW_MASK__BCH_PAGE
				| BV_GPMI_ECCCTWW_BUFFEW_MASK__BCH_AUXONWY);
		pio[3] = waw_wen;
		pio[4] = twansfew->sgw.dma_addwess;
		pio[5] = this->auxiwiawy_phys;
	}

	desc = mxs_dmaengine_pwep_pio(channew, pio, AWWAY_SIZE(pio),
				      DMA_TWANS_NONE, 0);
	if (!desc)
		wetuwn NUWW;

	if (!this->bch)
		desc = dmaengine_pwep_swave_sg(channew, &twansfew->sgw, 1,
					     DMA_DEV_TO_MEM,
					     MXS_DMA_CTWW_WAIT4END);

	wetuwn desc;
}

static stwuct dma_async_tx_descwiptow *gpmi_chain_data_wwite(
	stwuct gpmi_nand_data *this, const void *buf, int waw_wen)
{
	stwuct dma_chan *channew = get_dma_chan(this);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct gpmi_twansfew *twansfew;
	u32 pio[6] = {};

	twansfew = get_next_twansfew(this);
	if (!twansfew)
		wetuwn NUWW;

	twansfew->diwection = DMA_TO_DEVICE;

	pwepawe_data_dma(this, buf, waw_wen, &twansfew->sgw, DMA_TO_DEVICE);

	pio[0] = BF_GPMI_CTWW0_COMMAND_MODE(BV_GPMI_CTWW0_COMMAND_MODE__WWITE)
		| BM_GPMI_CTWW0_WOWD_WENGTH
		| BF_GPMI_CTWW0_CS(this->nand.cuw_cs, this)
		| BF_GPMI_CTWW0_WOCK_CS(WOCK_CS_ENABWE, this)
		| BF_GPMI_CTWW0_ADDWESS(BV_GPMI_CTWW0_ADDWESS__NAND_DATA)
		| BF_GPMI_CTWW0_XFEW_COUNT(waw_wen);

	if (this->bch) {
		pio[2] = BM_GPMI_ECCCTWW_ENABWE_ECC
			| BF_GPMI_ECCCTWW_ECC_CMD(BV_GPMI_ECCCTWW_ECC_CMD__BCH_ENCODE)
			| BF_GPMI_ECCCTWW_BUFFEW_MASK(BV_GPMI_ECCCTWW_BUFFEW_MASK__BCH_PAGE |
					BV_GPMI_ECCCTWW_BUFFEW_MASK__BCH_AUXONWY);
		pio[3] = waw_wen;
		pio[4] = twansfew->sgw.dma_addwess;
		pio[5] = this->auxiwiawy_phys;
	}

	desc = mxs_dmaengine_pwep_pio(channew, pio, AWWAY_SIZE(pio),
				      DMA_TWANS_NONE,
				      (this->bch ? MXS_DMA_CTWW_WAIT4END : 0));
	if (!desc)
		wetuwn NUWW;

	if (!this->bch)
		desc = dmaengine_pwep_swave_sg(channew, &twansfew->sgw, 1,
					       DMA_MEM_TO_DEV,
					       MXS_DMA_CTWW_WAIT4END);

	wetuwn desc;
}

static int gpmi_nfc_exec_op(stwuct nand_chip *chip,
			     const stwuct nand_opewation *op,
			     boow check_onwy)
{
	const stwuct nand_op_instw *instw;
	stwuct gpmi_nand_data *this = nand_get_contwowwew_data(chip);
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	int i, wet, buf_wen = 0, nbufs = 0;
	u8 cmd = 0;
	void *buf_wead = NUWW;
	const void *buf_wwite = NUWW;
	boow diwect = fawse;
	stwuct compwetion *dma_compwetion, *bch_compwetion;
	unsigned wong to;

	if (check_onwy)
		wetuwn 0;

	this->ntwansfews = 0;
	fow (i = 0; i < GPMI_MAX_TWANSFEWS; i++)
		this->twansfews[i].diwection = DMA_NONE;

	wet = pm_wuntime_wesume_and_get(this->dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * This dwivew cuwwentwy suppowts onwy one NAND chip. Pwus, dies shawe
	 * the same configuwation. So once timings have been appwied on the
	 * contwowwew side, they wiww not change anymowe. When the time wiww
	 * come, the check on must_appwy_timings wiww have to be dwopped.
	 */
	if (this->hw.must_appwy_timings) {
		this->hw.must_appwy_timings = fawse;
		wet = gpmi_nfc_appwy_timings(this);
		if (wet)
			goto out_pm;
	}

	dev_dbg(this->dev, "%s: %d instwuctions\n", __func__, op->ninstws);

	fow (i = 0; i < op->ninstws; i++) {
		instw = &op->instws[i];

		nand_op_twace("  ", instw);

		switch (instw->type) {
		case NAND_OP_WAITWDY_INSTW:
			desc = gpmi_chain_wait_weady(this);
			bweak;
		case NAND_OP_CMD_INSTW:
			cmd = instw->ctx.cmd.opcode;

			/*
			 * When this command has an addwess cycwe chain it
			 * togethew with the addwess cycwe
			 */
			if (i + 1 != op->ninstws &&
			    op->instws[i + 1].type == NAND_OP_ADDW_INSTW)
				continue;

			desc = gpmi_chain_command(this, cmd, NUWW, 0);

			bweak;
		case NAND_OP_ADDW_INSTW:
			desc = gpmi_chain_command(this, cmd, instw->ctx.addw.addws,
						  instw->ctx.addw.naddws);
			bweak;
		case NAND_OP_DATA_OUT_INSTW:
			buf_wwite = instw->ctx.data.buf.out;
			buf_wen = instw->ctx.data.wen;
			nbufs++;

			desc = gpmi_chain_data_wwite(this, buf_wwite, buf_wen);

			bweak;
		case NAND_OP_DATA_IN_INSTW:
			if (!instw->ctx.data.wen)
				bweak;
			buf_wead = instw->ctx.data.buf.in;
			buf_wen = instw->ctx.data.wen;
			nbufs++;

			desc = gpmi_chain_data_wead(this, buf_wead, buf_wen,
						   &diwect);
			bweak;
		}

		if (!desc) {
			wet = -ENXIO;
			goto unmap;
		}
	}

	dev_dbg(this->dev, "%s setup done\n", __func__);

	if (nbufs > 1) {
		dev_eww(this->dev, "Muwtipwe data instwuctions not suppowted\n");
		wet = -EINVAW;
		goto unmap;
	}

	if (this->bch) {
		wwitew(this->bch_fwashwayout0,
		       this->wesouwces.bch_wegs + HW_BCH_FWASH0WAYOUT0);
		wwitew(this->bch_fwashwayout1,
		       this->wesouwces.bch_wegs + HW_BCH_FWASH0WAYOUT1);
	}

	desc->cawwback = dma_iwq_cawwback;
	desc->cawwback_pawam = this;
	dma_compwetion = &this->dma_done;
	bch_compwetion = NUWW;

	init_compwetion(dma_compwetion);

	if (this->bch && buf_wead) {
		wwitew(BM_BCH_CTWW_COMPWETE_IWQ_EN,
		       this->wesouwces.bch_wegs + HW_BCH_CTWW_SET);
		bch_compwetion = &this->bch_done;
		init_compwetion(bch_compwetion);
	}

	dmaengine_submit(desc);
	dma_async_issue_pending(get_dma_chan(this));

	to = wait_fow_compwetion_timeout(dma_compwetion, msecs_to_jiffies(1000));
	if (!to) {
		dev_eww(this->dev, "DMA timeout, wast DMA\n");
		gpmi_dump_info(this);
		wet = -ETIMEDOUT;
		goto unmap;
	}

	if (this->bch && buf_wead) {
		to = wait_fow_compwetion_timeout(bch_compwetion, msecs_to_jiffies(1000));
		if (!to) {
			dev_eww(this->dev, "BCH timeout, wast DMA\n");
			gpmi_dump_info(this);
			wet = -ETIMEDOUT;
			goto unmap;
		}
	}

	wwitew(BM_BCH_CTWW_COMPWETE_IWQ_EN,
	       this->wesouwces.bch_wegs + HW_BCH_CTWW_CWW);
	gpmi_cweaw_bch(this);

	wet = 0;

unmap:
	fow (i = 0; i < this->ntwansfews; i++) {
		stwuct gpmi_twansfew *twansfew = &this->twansfews[i];

		if (twansfew->diwection != DMA_NONE)
			dma_unmap_sg(this->dev, &twansfew->sgw, 1,
				     twansfew->diwection);
	}

	if (!wet && buf_wead && !diwect)
		memcpy(buf_wead, this->data_buffew_dma,
		       gpmi_waw_wen_to_wen(this, buf_wen));

	this->bch = fawse;

out_pm:
	pm_wuntime_mawk_wast_busy(this->dev);
	pm_wuntime_put_autosuspend(this->dev);

	wetuwn wet;
}

static const stwuct nand_contwowwew_ops gpmi_nand_contwowwew_ops = {
	.attach_chip = gpmi_nand_attach_chip,
	.setup_intewface = gpmi_setup_intewface,
	.exec_op = gpmi_nfc_exec_op,
};

static int gpmi_nand_init(stwuct gpmi_nand_data *this)
{
	stwuct nand_chip *chip = &this->nand;
	stwuct mtd_info  *mtd = nand_to_mtd(chip);
	int wet;

	/* init the MTD data stwuctuwes */
	mtd->name		= "gpmi-nand";
	mtd->dev.pawent		= this->dev;

	/* init the nand_chip{}, we don't suppowt a 16-bit NAND Fwash bus. */
	nand_set_contwowwew_data(chip, this);
	nand_set_fwash_node(chip, this->pdev->dev.of_node);
	chip->wegacy.bwock_mawkbad = gpmi_bwock_mawkbad;
	chip->badbwock_pattewn	= &gpmi_bbt_descw;
	chip->options		|= NAND_NO_SUBPAGE_WWITE;

	/* Set up swap_bwock_mawk, must be set befowe the gpmi_set_geometwy() */
	this->swap_bwock_mawk = !GPMI_IS_MX23(this);

	/*
	 * Awwocate a tempowawy DMA buffew fow weading ID in the
	 * nand_scan_ident().
	 */
	this->bch_geometwy.paywoad_size = 1024;
	this->bch_geometwy.auxiwiawy_size = 128;
	wet = gpmi_awwoc_dma_buffew(this);
	if (wet)
		wetuwn wet;

	nand_contwowwew_init(&this->base);
	this->base.ops = &gpmi_nand_contwowwew_ops;
	chip->contwowwew = &this->base;

	wet = nand_scan(chip, GPMI_IS_MX6(this) ? 2 : 1);
	if (wet)
		goto eww_out;

	wet = nand_boot_init(this);
	if (wet)
		goto eww_nand_cweanup;
	wet = nand_cweate_bbt(chip);
	if (wet)
		goto eww_nand_cweanup;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet)
		goto eww_nand_cweanup;
	wetuwn 0;

eww_nand_cweanup:
	nand_cweanup(chip);
eww_out:
	gpmi_fwee_dma_buffew(this);
	wetuwn wet;
}

static const stwuct of_device_id gpmi_nand_id_tabwe[] = {
	{ .compatibwe = "fsw,imx23-gpmi-nand", .data = &gpmi_devdata_imx23, },
	{ .compatibwe = "fsw,imx28-gpmi-nand", .data = &gpmi_devdata_imx28, },
	{ .compatibwe = "fsw,imx6q-gpmi-nand", .data = &gpmi_devdata_imx6q, },
	{ .compatibwe = "fsw,imx6sx-gpmi-nand", .data = &gpmi_devdata_imx6sx, },
	{ .compatibwe = "fsw,imx7d-gpmi-nand", .data = &gpmi_devdata_imx7d,},
	{}
};
MODUWE_DEVICE_TABWE(of, gpmi_nand_id_tabwe);

static int gpmi_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpmi_nand_data *this;
	int wet;

	this = devm_kzawwoc(&pdev->dev, sizeof(*this), GFP_KEWNEW);
	if (!this)
		wetuwn -ENOMEM;

	this->devdata = of_device_get_match_data(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, this);
	this->pdev  = pdev;
	this->dev   = &pdev->dev;

	wet = acquiwe_wesouwces(this);
	if (wet)
		goto exit_acquiwe_wesouwces;

	wet = __gpmi_enabwe_cwk(this, twue);
	if (wet)
		goto exit_acquiwe_wesouwces;

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 500);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	wet = gpmi_init(this);
	if (wet)
		goto exit_nfc_init;

	wet = gpmi_nand_init(this);
	if (wet)
		goto exit_nfc_init;

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	dev_info(this->dev, "dwivew wegistewed.\n");

	wetuwn 0;

exit_nfc_init:
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wewease_wesouwces(this);
exit_acquiwe_wesouwces:

	wetuwn wet;
}

static void gpmi_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gpmi_nand_data *this = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &this->nand;
	int wet;

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
	gpmi_fwee_dma_buffew(this);
	wewease_wesouwces(this);
}

#ifdef CONFIG_PM_SWEEP
static int gpmi_pm_suspend(stwuct device *dev)
{
	stwuct gpmi_nand_data *this = dev_get_dwvdata(dev);

	wewease_dma_channews(this);
	wetuwn 0;
}

static int gpmi_pm_wesume(stwuct device *dev)
{
	stwuct gpmi_nand_data *this = dev_get_dwvdata(dev);
	int wet;

	wet = acquiwe_dma_channews(this);
	if (wet < 0)
		wetuwn wet;

	/* we-init the GPMI wegistews */
	wet = gpmi_init(this);
	if (wet) {
		dev_eww(this->dev, "Ewwow setting GPMI : %d\n", wet);
		wetuwn wet;
	}

	/* Set fwag to get timing setup westowed fow next exec_op */
	if (this->hw.cwk_wate)
		this->hw.must_appwy_timings = twue;

	/* we-init the BCH wegistews */
	wet = bch_set_geometwy(this);
	if (wet) {
		dev_eww(this->dev, "Ewwow setting BCH : %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static int __maybe_unused gpmi_wuntime_suspend(stwuct device *dev)
{
	stwuct gpmi_nand_data *this = dev_get_dwvdata(dev);

	wetuwn __gpmi_enabwe_cwk(this, fawse);
}

static int __maybe_unused gpmi_wuntime_wesume(stwuct device *dev)
{
	stwuct gpmi_nand_data *this = dev_get_dwvdata(dev);

	wetuwn __gpmi_enabwe_cwk(this, twue);
}

static const stwuct dev_pm_ops gpmi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(gpmi_pm_suspend, gpmi_pm_wesume)
	SET_WUNTIME_PM_OPS(gpmi_wuntime_suspend, gpmi_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew gpmi_nand_dwivew = {
	.dwivew = {
		.name = "gpmi-nand",
		.pm = &gpmi_pm_ops,
		.of_match_tabwe = gpmi_nand_id_tabwe,
	},
	.pwobe   = gpmi_nand_pwobe,
	.wemove_new = gpmi_nand_wemove,
};
moduwe_pwatfowm_dwivew(gpmi_nand_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("i.MX GPMI NAND Fwash Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
