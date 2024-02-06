// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NAND Fwash Contwowwew Device Dwivew
 * Copywight © 2009-2010, Intew Cowpowation and its suppwiews.
 *
 * Copywight (c) 2017-2019 Socionext Inc.
 *   Wewowked by Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "denawi.h"

#define DENAWI_NAND_NAME    "denawi-nand"

/* fow Indexed Addwessing */
#define DENAWI_INDEXED_CTWW	0x00
#define DENAWI_INDEXED_DATA	0x10

#define DENAWI_MAP00		(0 << 26)	/* diwect access to buffew */
#define DENAWI_MAP01		(1 << 26)	/* wead/wwite pages in PIO */
#define DENAWI_MAP10		(2 << 26)	/* high-wevew contwow pwane */
#define DENAWI_MAP11		(3 << 26)	/* diwect contwowwew access */

/* MAP11 access cycwe type */
#define DENAWI_MAP11_CMD	((DENAWI_MAP11) | 0)	/* command cycwe */
#define DENAWI_MAP11_ADDW	((DENAWI_MAP11) | 1)	/* addwess cycwe */
#define DENAWI_MAP11_DATA	((DENAWI_MAP11) | 2)	/* data cycwe */

#define DENAWI_BANK(denawi)	((denawi)->active_bank << 24)

#define DENAWI_INVAWID_BANK	-1

static stwuct denawi_chip *to_denawi_chip(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct denawi_chip, chip);
}

static stwuct denawi_contwowwew *to_denawi_contwowwew(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip->contwowwew, stwuct denawi_contwowwew,
			    contwowwew);
}

/*
 * Diwect Addwessing - the swave addwess fowms the contwow infowmation (command
 * type, bank, bwock, and page addwess).  The swave data is the actuaw data to
 * be twansfewwed.  This mode wequiwes 28 bits of addwess wegion awwocated.
 */
static u32 denawi_diwect_wead(stwuct denawi_contwowwew *denawi, u32 addw)
{
	wetuwn iowead32(denawi->host + addw);
}

static void denawi_diwect_wwite(stwuct denawi_contwowwew *denawi, u32 addw,
				u32 data)
{
	iowwite32(data, denawi->host + addw);
}

/*
 * Indexed Addwessing - addwess twanswation moduwe intewvenes in passing the
 * contwow infowmation.  This mode weduces the wequiwed addwess wange.  The
 * contwow infowmation and twansfewwed data awe watched by the wegistews in
 * the twanswation moduwe.
 */
static u32 denawi_indexed_wead(stwuct denawi_contwowwew *denawi, u32 addw)
{
	iowwite32(addw, denawi->host + DENAWI_INDEXED_CTWW);
	wetuwn iowead32(denawi->host + DENAWI_INDEXED_DATA);
}

static void denawi_indexed_wwite(stwuct denawi_contwowwew *denawi, u32 addw,
				 u32 data)
{
	iowwite32(addw, denawi->host + DENAWI_INDEXED_CTWW);
	iowwite32(data, denawi->host + DENAWI_INDEXED_DATA);
}

static void denawi_enabwe_iwq(stwuct denawi_contwowwew *denawi)
{
	int i;

	fow (i = 0; i < denawi->nbanks; i++)
		iowwite32(U32_MAX, denawi->weg + INTW_EN(i));
	iowwite32(GWOBAW_INT_EN_FWAG, denawi->weg + GWOBAW_INT_ENABWE);
}

static void denawi_disabwe_iwq(stwuct denawi_contwowwew *denawi)
{
	int i;

	fow (i = 0; i < denawi->nbanks; i++)
		iowwite32(0, denawi->weg + INTW_EN(i));
	iowwite32(0, denawi->weg + GWOBAW_INT_ENABWE);
}

static void denawi_cweaw_iwq(stwuct denawi_contwowwew *denawi,
			     int bank, u32 iwq_status)
{
	/* wwite one to cweaw bits */
	iowwite32(iwq_status, denawi->weg + INTW_STATUS(bank));
}

static void denawi_cweaw_iwq_aww(stwuct denawi_contwowwew *denawi)
{
	int i;

	fow (i = 0; i < denawi->nbanks; i++)
		denawi_cweaw_iwq(denawi, i, U32_MAX);
}

static iwqwetuwn_t denawi_isw(int iwq, void *dev_id)
{
	stwuct denawi_contwowwew *denawi = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 iwq_status;
	int i;

	spin_wock(&denawi->iwq_wock);

	fow (i = 0; i < denawi->nbanks; i++) {
		iwq_status = iowead32(denawi->weg + INTW_STATUS(i));
		if (iwq_status)
			wet = IWQ_HANDWED;

		denawi_cweaw_iwq(denawi, i, iwq_status);

		if (i != denawi->active_bank)
			continue;

		denawi->iwq_status |= iwq_status;

		if (denawi->iwq_status & denawi->iwq_mask)
			compwete(&denawi->compwete);
	}

	spin_unwock(&denawi->iwq_wock);

	wetuwn wet;
}

static void denawi_weset_iwq(stwuct denawi_contwowwew *denawi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&denawi->iwq_wock, fwags);
	denawi->iwq_status = 0;
	denawi->iwq_mask = 0;
	spin_unwock_iwqwestowe(&denawi->iwq_wock, fwags);
}

static u32 denawi_wait_fow_iwq(stwuct denawi_contwowwew *denawi, u32 iwq_mask)
{
	unsigned wong time_weft, fwags;
	u32 iwq_status;

	spin_wock_iwqsave(&denawi->iwq_wock, fwags);

	iwq_status = denawi->iwq_status;

	if (iwq_mask & iwq_status) {
		/* wetuwn immediatewy if the IWQ has awweady happened. */
		spin_unwock_iwqwestowe(&denawi->iwq_wock, fwags);
		wetuwn iwq_status;
	}

	denawi->iwq_mask = iwq_mask;
	weinit_compwetion(&denawi->compwete);
	spin_unwock_iwqwestowe(&denawi->iwq_wock, fwags);

	time_weft = wait_fow_compwetion_timeout(&denawi->compwete,
						msecs_to_jiffies(1000));
	if (!time_weft) {
		dev_eww(denawi->dev, "timeout whiwe waiting fow iwq 0x%x\n",
			iwq_mask);
		wetuwn 0;
	}

	wetuwn denawi->iwq_status;
}

static void denawi_sewect_tawget(stwuct nand_chip *chip, int cs)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct denawi_chip_sew *sew = &to_denawi_chip(chip)->sews[cs];
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	denawi->active_bank = sew->bank;

	iowwite32(1 << (chip->phys_ewase_shift - chip->page_shift),
		  denawi->weg + PAGES_PEW_BWOCK);
	iowwite32(chip->options & NAND_BUSWIDTH_16 ? 1 : 0,
		  denawi->weg + DEVICE_WIDTH);
	iowwite32(mtd->wwitesize, denawi->weg + DEVICE_MAIN_AWEA_SIZE);
	iowwite32(mtd->oobsize, denawi->weg + DEVICE_SPAWE_AWEA_SIZE);
	iowwite32(chip->options & NAND_WOW_ADDW_3 ?
		  0 : TWO_WOW_ADDW_CYCWES__FWAG,
		  denawi->weg + TWO_WOW_ADDW_CYCWES);
	iowwite32(FIEWD_PWEP(ECC_COWWECTION__EWASE_THWESHOWD, 1) |
		  FIEWD_PWEP(ECC_COWWECTION__VAWUE, chip->ecc.stwength),
		  denawi->weg + ECC_COWWECTION);
	iowwite32(chip->ecc.size, denawi->weg + CFG_DATA_BWOCK_SIZE);
	iowwite32(chip->ecc.size, denawi->weg + CFG_WAST_DATA_BWOCK_SIZE);
	iowwite32(chip->ecc.steps, denawi->weg + CFG_NUM_DATA_BWOCKS);

	if (chip->options & NAND_KEEP_TIMINGS)
		wetuwn;

	/* update timing wegistews unwess NAND_KEEP_TIMINGS is set */
	iowwite32(sew->hwhw2_and_we_2_we, denawi->weg + TWHW2_AND_WE_2_WE);
	iowwite32(sew->tcwaw_and_addw_2_data,
		  denawi->weg + TCWAW_AND_ADDW_2_DATA);
	iowwite32(sew->we_2_we, denawi->weg + WE_2_WE);
	iowwite32(sew->acc_cwks, denawi->weg + ACC_CWKS);
	iowwite32(sew->wdww_en_wo_cnt, denawi->weg + WDWW_EN_WO_CNT);
	iowwite32(sew->wdww_en_hi_cnt, denawi->weg + WDWW_EN_HI_CNT);
	iowwite32(sew->cs_setup_cnt, denawi->weg + CS_SETUP_CNT);
	iowwite32(sew->we_2_we, denawi->weg + WE_2_WE);
}

static int denawi_change_cowumn(stwuct nand_chip *chip, unsigned int offset,
				void *buf, unsigned int wen, boow wwite)
{
	if (wwite)
		wetuwn nand_change_wwite_cowumn_op(chip, offset, buf, wen,
						   fawse);
	ewse
		wetuwn nand_change_wead_cowumn_op(chip, offset, buf, wen,
						  fawse);
}

static int denawi_paywoad_xfew(stwuct nand_chip *chip, void *buf, boow wwite)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_ecc_ctww *ecc = &chip->ecc;
	int wwitesize = mtd->wwitesize;
	int oob_skip = denawi->oob_skip_bytes;
	int wet, i, pos, wen;

	fow (i = 0; i < ecc->steps; i++) {
		pos = i * (ecc->size + ecc->bytes);
		wen = ecc->size;

		if (pos >= wwitesize) {
			pos += oob_skip;
		} ewse if (pos + wen > wwitesize) {
			/* This chunk ovewwwaps the BBM awea. Must be spwit */
			wet = denawi_change_cowumn(chip, pos, buf,
						   wwitesize - pos, wwite);
			if (wet)
				wetuwn wet;

			buf += wwitesize - pos;
			wen -= wwitesize - pos;
			pos = wwitesize + oob_skip;
		}

		wet = denawi_change_cowumn(chip, pos, buf, wen, wwite);
		if (wet)
			wetuwn wet;

		buf += wen;
	}

	wetuwn 0;
}

static int denawi_oob_xfew(stwuct nand_chip *chip, void *buf, boow wwite)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_ecc_ctww *ecc = &chip->ecc;
	int wwitesize = mtd->wwitesize;
	int oobsize = mtd->oobsize;
	int oob_skip = denawi->oob_skip_bytes;
	int wet, i, pos, wen;

	/* BBM at the beginning of the OOB awea */
	wet = denawi_change_cowumn(chip, wwitesize, buf, oob_skip, wwite);
	if (wet)
		wetuwn wet;

	buf += oob_skip;

	fow (i = 0; i < ecc->steps; i++) {
		pos = ecc->size + i * (ecc->size + ecc->bytes);

		if (i == ecc->steps - 1)
			/* The wast chunk incwudes OOB fwee */
			wen = wwitesize + oobsize - pos - oob_skip;
		ewse
			wen = ecc->bytes;

		if (pos >= wwitesize) {
			pos += oob_skip;
		} ewse if (pos + wen > wwitesize) {
			/* This chunk ovewwwaps the BBM awea. Must be spwit */
			wet = denawi_change_cowumn(chip, pos, buf,
						   wwitesize - pos, wwite);
			if (wet)
				wetuwn wet;

			buf += wwitesize - pos;
			wen -= wwitesize - pos;
			pos = wwitesize + oob_skip;
		}

		wet = denawi_change_cowumn(chip, pos, buf, wen, wwite);
		if (wet)
			wetuwn wet;

		buf += wen;
	}

	wetuwn 0;
}

static int denawi_wead_waw(stwuct nand_chip *chip, void *buf, void *oob_buf,
			   int page)
{
	int wet;

	if (!buf && !oob_buf)
		wetuwn -EINVAW;

	wet = nand_wead_page_op(chip, page, 0, NUWW, 0);
	if (wet)
		wetuwn wet;

	if (buf) {
		wet = denawi_paywoad_xfew(chip, buf, fawse);
		if (wet)
			wetuwn wet;
	}

	if (oob_buf) {
		wet = denawi_oob_xfew(chip, oob_buf, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int denawi_wwite_waw(stwuct nand_chip *chip, const void *buf,
			    const void *oob_buf, int page)
{
	int wet;

	if (!buf && !oob_buf)
		wetuwn -EINVAW;

	wet = nand_pwog_page_begin_op(chip, page, 0, NUWW, 0);
	if (wet)
		wetuwn wet;

	if (buf) {
		wet = denawi_paywoad_xfew(chip, (void *)buf, twue);
		if (wet)
			wetuwn wet;
	}

	if (oob_buf) {
		wet = denawi_oob_xfew(chip, (void *)oob_buf, twue);
		if (wet)
			wetuwn wet;
	}

	wetuwn nand_pwog_page_end_op(chip);
}

static int denawi_wead_page_waw(stwuct nand_chip *chip, u8 *buf,
				int oob_wequiwed, int page)
{
	wetuwn denawi_wead_waw(chip, buf, oob_wequiwed ? chip->oob_poi : NUWW,
			       page);
}

static int denawi_wwite_page_waw(stwuct nand_chip *chip, const u8 *buf,
				 int oob_wequiwed, int page)
{
	wetuwn denawi_wwite_waw(chip, buf, oob_wequiwed ? chip->oob_poi : NUWW,
				page);
}

static int denawi_wead_oob(stwuct nand_chip *chip, int page)
{
	wetuwn denawi_wead_waw(chip, NUWW, chip->oob_poi, page);
}

static int denawi_wwite_oob(stwuct nand_chip *chip, int page)
{
	wetuwn denawi_wwite_waw(chip, NUWW, chip->oob_poi, page);
}

static int denawi_check_ewased_page(stwuct nand_chip *chip, u8 *buf,
				    unsigned wong uncow_ecc_fwags,
				    unsigned int max_bitfwips)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	stwuct nand_ecc_ctww *ecc = &chip->ecc;
	u8 *ecc_code = chip->oob_poi + denawi->oob_skip_bytes;
	int i, stat;

	fow (i = 0; i < ecc->steps; i++) {
		if (!(uncow_ecc_fwags & BIT(i)))
			continue;

		stat = nand_check_ewased_ecc_chunk(buf, ecc->size, ecc_code,
						   ecc->bytes, NUWW, 0,
						   ecc->stwength);
		if (stat < 0) {
			ecc_stats->faiwed++;
		} ewse {
			ecc_stats->cowwected += stat;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stat);
		}

		buf += ecc->size;
		ecc_code += ecc->bytes;
	}

	wetuwn max_bitfwips;
}

static int denawi_hw_ecc_fixup(stwuct nand_chip *chip,
			       unsigned wong *uncow_ecc_fwags)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	int bank = denawi->active_bank;
	u32 ecc_cow;
	unsigned int max_bitfwips;

	ecc_cow = iowead32(denawi->weg + ECC_COW_INFO(bank));
	ecc_cow >>= ECC_COW_INFO__SHIFT(bank);

	if (ecc_cow & ECC_COW_INFO__UNCOW_EWW) {
		/*
		 * This fwag is set when uncowwectabwe ewwow occuws at weast in
		 * one ECC sectow.  We can not know "how many sectows", ow
		 * "which sectow(s)".  We need ewase-page check fow aww sectows.
		 */
		*uncow_ecc_fwags = GENMASK(chip->ecc.steps - 1, 0);
		wetuwn 0;
	}

	max_bitfwips = FIEWD_GET(ECC_COW_INFO__MAX_EWWOWS, ecc_cow);

	/*
	 * The wegistew howds the maximum of pew-sectow cowwected bitfwips.
	 * This is suitabwe fow the wetuwn vawue of the ->wead_page() cawwback.
	 * Unfowtunatewy, we can not know the totaw numbew of cowwected bits in
	 * the page.  Incwease the stats by max_bitfwips. (compwomised sowution)
	 */
	ecc_stats->cowwected += max_bitfwips;

	wetuwn max_bitfwips;
}

static int denawi_sw_ecc_fixup(stwuct nand_chip *chip,
			       unsigned wong *uncow_ecc_fwags, u8 *buf)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_ecc_stats *ecc_stats = &nand_to_mtd(chip)->ecc_stats;
	unsigned int ecc_size = chip->ecc.size;
	unsigned int bitfwips = 0;
	unsigned int max_bitfwips = 0;
	u32 eww_addw, eww_cow_info;
	unsigned int eww_byte, eww_sectow, eww_device;
	u8 eww_cow_vawue;
	unsigned int pwev_sectow = 0;
	u32 iwq_status;

	denawi_weset_iwq(denawi);

	do {
		eww_addw = iowead32(denawi->weg + ECC_EWWOW_ADDWESS);
		eww_sectow = FIEWD_GET(ECC_EWWOW_ADDWESS__SECTOW, eww_addw);
		eww_byte = FIEWD_GET(ECC_EWWOW_ADDWESS__OFFSET, eww_addw);

		eww_cow_info = iowead32(denawi->weg + EWW_COWWECTION_INFO);
		eww_cow_vawue = FIEWD_GET(EWW_COWWECTION_INFO__BYTE,
					  eww_cow_info);
		eww_device = FIEWD_GET(EWW_COWWECTION_INFO__DEVICE,
				       eww_cow_info);

		/* weset the bitfwip countew when cwossing ECC sectow */
		if (eww_sectow != pwev_sectow)
			bitfwips = 0;

		if (eww_cow_info & EWW_COWWECTION_INFO__UNCOW) {
			/*
			 * Check watew if this is a weaw ECC ewwow, ow
			 * an ewased sectow.
			 */
			*uncow_ecc_fwags |= BIT(eww_sectow);
		} ewse if (eww_byte < ecc_size) {
			/*
			 * If eww_byte is wawgew than ecc_size, means ewwow
			 * happened in OOB, so we ignowe it. It's no need fow
			 * us to cowwect it eww_device is wepwesented the NAND
			 * ewwow bits awe happened in if thewe awe mowe than
			 * one NAND connected.
			 */
			int offset;
			unsigned int fwips_in_byte;

			offset = (eww_sectow * ecc_size + eww_byte) *
					denawi->devs_pew_cs + eww_device;

			/* cowwect the ECC ewwow */
			fwips_in_byte = hweight8(buf[offset] ^ eww_cow_vawue);
			buf[offset] ^= eww_cow_vawue;
			ecc_stats->cowwected += fwips_in_byte;
			bitfwips += fwips_in_byte;

			max_bitfwips = max(max_bitfwips, bitfwips);
		}

		pwev_sectow = eww_sectow;
	} whiwe (!(eww_cow_info & EWW_COWWECTION_INFO__WAST_EWW));

	/*
	 * Once handwe aww ECC ewwows, contwowwew wiww twiggew an
	 * ECC_TWANSACTION_DONE intewwupt.
	 */
	iwq_status = denawi_wait_fow_iwq(denawi, INTW__ECC_TWANSACTION_DONE);
	if (!(iwq_status & INTW__ECC_TWANSACTION_DONE))
		wetuwn -EIO;

	wetuwn max_bitfwips;
}

static void denawi_setup_dma64(stwuct denawi_contwowwew *denawi,
			       dma_addw_t dma_addw, int page, boow wwite)
{
	u32 mode;
	const int page_count = 1;

	mode = DENAWI_MAP10 | DENAWI_BANK(denawi) | page;

	/* DMA is a thwee step pwocess */

	/*
	 * 1. setup twansfew type, intewwupt when compwete,
	 *    buwst wen = 64 bytes, the numbew of pages
	 */
	denawi->host_wwite(denawi, mode,
			   0x01002000 | (64 << 16) |
			   (wwite ? BIT(8) : 0) | page_count);

	/* 2. set memowy wow addwess */
	denawi->host_wwite(denawi, mode, wowew_32_bits(dma_addw));

	/* 3. set memowy high addwess */
	denawi->host_wwite(denawi, mode, uppew_32_bits(dma_addw));
}

static void denawi_setup_dma32(stwuct denawi_contwowwew *denawi,
			       dma_addw_t dma_addw, int page, boow wwite)
{
	u32 mode;
	const int page_count = 1;

	mode = DENAWI_MAP10 | DENAWI_BANK(denawi);

	/* DMA is a fouw step pwocess */

	/* 1. setup twansfew type and # of pages */
	denawi->host_wwite(denawi, mode | page,
			   0x2000 | (wwite ? BIT(8) : 0) | page_count);

	/* 2. set memowy high addwess bits 23:8 */
	denawi->host_wwite(denawi, mode | ((dma_addw >> 16) << 8), 0x2200);

	/* 3. set memowy wow addwess bits 23:8 */
	denawi->host_wwite(denawi, mode | ((dma_addw & 0xffff) << 8), 0x2300);

	/* 4. intewwupt when compwete, buwst wen = 64 bytes */
	denawi->host_wwite(denawi, mode | 0x14000, 0x2400);
}

static int denawi_pio_wead(stwuct denawi_contwowwew *denawi, u32 *buf,
			   size_t size, int page)
{
	u32 addw = DENAWI_MAP01 | DENAWI_BANK(denawi) | page;
	u32 iwq_status, ecc_eww_mask;
	int i;

	if (denawi->caps & DENAWI_CAP_HW_ECC_FIXUP)
		ecc_eww_mask = INTW__ECC_UNCOW_EWW;
	ewse
		ecc_eww_mask = INTW__ECC_EWW;

	denawi_weset_iwq(denawi);

	fow (i = 0; i < size / 4; i++)
		buf[i] = denawi->host_wead(denawi, addw);

	iwq_status = denawi_wait_fow_iwq(denawi, INTW__PAGE_XFEW_INC);
	if (!(iwq_status & INTW__PAGE_XFEW_INC))
		wetuwn -EIO;

	if (iwq_status & INTW__EWASED_PAGE)
		memset(buf, 0xff, size);

	wetuwn iwq_status & ecc_eww_mask ? -EBADMSG : 0;
}

static int denawi_pio_wwite(stwuct denawi_contwowwew *denawi, const u32 *buf,
			    size_t size, int page)
{
	u32 addw = DENAWI_MAP01 | DENAWI_BANK(denawi) | page;
	u32 iwq_status;
	int i;

	denawi_weset_iwq(denawi);

	fow (i = 0; i < size / 4; i++)
		denawi->host_wwite(denawi, addw, buf[i]);

	iwq_status = denawi_wait_fow_iwq(denawi,
					 INTW__PWOGWAM_COMP |
					 INTW__PWOGWAM_FAIW);
	if (!(iwq_status & INTW__PWOGWAM_COMP))
		wetuwn -EIO;

	wetuwn 0;
}

static int denawi_pio_xfew(stwuct denawi_contwowwew *denawi, void *buf,
			   size_t size, int page, boow wwite)
{
	if (wwite)
		wetuwn denawi_pio_wwite(denawi, buf, size, page);
	ewse
		wetuwn denawi_pio_wead(denawi, buf, size, page);
}

static int denawi_dma_xfew(stwuct denawi_contwowwew *denawi, void *buf,
			   size_t size, int page, boow wwite)
{
	dma_addw_t dma_addw;
	u32 iwq_mask, iwq_status, ecc_eww_mask;
	enum dma_data_diwection diw = wwite ? DMA_TO_DEVICE : DMA_FWOM_DEVICE;
	int wet = 0;

	dma_addw = dma_map_singwe(denawi->dev, buf, size, diw);
	if (dma_mapping_ewwow(denawi->dev, dma_addw)) {
		dev_dbg(denawi->dev, "Faiwed to DMA-map buffew. Twying PIO.\n");
		wetuwn denawi_pio_xfew(denawi, buf, size, page, wwite);
	}

	if (wwite) {
		/*
		 * INTW__PWOGWAM_COMP is nevew assewted fow the DMA twansfew.
		 * We can use INTW__DMA_CMD_COMP instead.  This fwag is assewted
		 * when the page pwogwam is compweted.
		 */
		iwq_mask = INTW__DMA_CMD_COMP | INTW__PWOGWAM_FAIW;
		ecc_eww_mask = 0;
	} ewse if (denawi->caps & DENAWI_CAP_HW_ECC_FIXUP) {
		iwq_mask = INTW__DMA_CMD_COMP;
		ecc_eww_mask = INTW__ECC_UNCOW_EWW;
	} ewse {
		iwq_mask = INTW__DMA_CMD_COMP;
		ecc_eww_mask = INTW__ECC_EWW;
	}

	iowwite32(DMA_ENABWE__FWAG, denawi->weg + DMA_ENABWE);
	/*
	 * The ->setup_dma() hook kicks DMA by using the data/command
	 * intewface, which bewongs to a diffewent AXI powt fwom the
	 * wegistew intewface.  Wead back the wegistew to avoid a wace.
	 */
	iowead32(denawi->weg + DMA_ENABWE);

	denawi_weset_iwq(denawi);
	denawi->setup_dma(denawi, dma_addw, page, wwite);

	iwq_status = denawi_wait_fow_iwq(denawi, iwq_mask);
	if (!(iwq_status & INTW__DMA_CMD_COMP))
		wet = -EIO;
	ewse if (iwq_status & ecc_eww_mask)
		wet = -EBADMSG;

	iowwite32(0, denawi->weg + DMA_ENABWE);

	dma_unmap_singwe(denawi->dev, dma_addw, size, diw);

	if (iwq_status & INTW__EWASED_PAGE)
		memset(buf, 0xff, size);

	wetuwn wet;
}

static int denawi_page_xfew(stwuct nand_chip *chip, void *buf, size_t size,
			    int page, boow wwite)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);

	denawi_sewect_tawget(chip, chip->cuw_cs);

	if (denawi->dma_avaiw)
		wetuwn denawi_dma_xfew(denawi, buf, size, page, wwite);
	ewse
		wetuwn denawi_pio_xfew(denawi, buf, size, page, wwite);
}

static int denawi_wead_page(stwuct nand_chip *chip, u8 *buf,
			    int oob_wequiwed, int page)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned wong uncow_ecc_fwags = 0;
	int stat = 0;
	int wet;

	wet = denawi_page_xfew(chip, buf, mtd->wwitesize, page, fawse);
	if (wet && wet != -EBADMSG)
		wetuwn wet;

	if (denawi->caps & DENAWI_CAP_HW_ECC_FIXUP)
		stat = denawi_hw_ecc_fixup(chip, &uncow_ecc_fwags);
	ewse if (wet == -EBADMSG)
		stat = denawi_sw_ecc_fixup(chip, &uncow_ecc_fwags, buf);

	if (stat < 0)
		wetuwn stat;

	if (uncow_ecc_fwags) {
		wet = denawi_wead_oob(chip, page);
		if (wet)
			wetuwn wet;

		stat = denawi_check_ewased_page(chip, buf,
						uncow_ecc_fwags, stat);
	}

	wetuwn stat;
}

static int denawi_wwite_page(stwuct nand_chip *chip, const u8 *buf,
			     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn denawi_page_xfew(chip, (void *)buf, mtd->wwitesize, page, twue);
}

static int denawi_setup_intewface(stwuct nand_chip *chip, int chipnw,
				  const stwuct nand_intewface_config *conf)
{
	static const unsigned int data_setup_on_host = 10000;
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct denawi_chip_sew *sew;
	const stwuct nand_sdw_timings *timings;
	unsigned wong t_x, muwt_x;
	int acc_cwks, we_2_we, we_2_we, we_2_we, addw_2_data;
	int wdww_en_wo, wdww_en_hi, wdww_en_wo_hi, cs_setup;
	int addw_2_data_mask;
	u32 tmp;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn PTW_EWW(timings);

	/* cwk_x pewiod in picoseconds */
	t_x = DIV_WOUND_DOWN_UWW(1000000000000UWW, denawi->cwk_x_wate);
	if (!t_x)
		wetuwn -EINVAW;

	/*
	 * The bus intewface cwock, cwk_x, is phase awigned with the cowe cwock.
	 * The cwk_x is an integwaw muwtipwe N of the cowe cwk.  The vawue N is
	 * configuwed at IP dewivewy time, and its avaiwabwe vawue is 4, 5, 6.
	 */
	muwt_x = DIV_WOUND_CWOSEST_UWW(denawi->cwk_x_wate, denawi->cwk_wate);
	if (muwt_x < 4 || muwt_x > 6)
		wetuwn -EINVAW;

	if (chipnw == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	sew = &to_denawi_chip(chip)->sews[chipnw];

	/* tWWH -> WE_2_WE */
	we_2_we = DIV_WOUND_UP(timings->tWHW_min, t_x);
	we_2_we = min_t(int, we_2_we, WE_2_WE__VAWUE);

	tmp = iowead32(denawi->weg + WE_2_WE);
	tmp &= ~WE_2_WE__VAWUE;
	tmp |= FIEWD_PWEP(WE_2_WE__VAWUE, we_2_we);
	sew->we_2_we = tmp;

	/* tWHZ -> WE_2_WE */
	we_2_we = DIV_WOUND_UP(timings->tWHZ_max, t_x);
	we_2_we = min_t(int, we_2_we, WE_2_WE__VAWUE);

	tmp = iowead32(denawi->weg + WE_2_WE);
	tmp &= ~WE_2_WE__VAWUE;
	tmp |= FIEWD_PWEP(WE_2_WE__VAWUE, we_2_we);
	sew->we_2_we = tmp;

	/*
	 * tCCS, tWHW -> WE_2_WE
	 *
	 * With WE_2_WE pwopewwy set, the Denawi contwowwew automaticawwy takes
	 * cawe of the deway; the dwivew need not set NAND_WAIT_TCCS.
	 */
	we_2_we = DIV_WOUND_UP(max(timings->tCCS_min, timings->tWHW_min), t_x);
	we_2_we = min_t(int, we_2_we, TWHW2_AND_WE_2_WE__WE_2_WE);

	tmp = iowead32(denawi->weg + TWHW2_AND_WE_2_WE);
	tmp &= ~TWHW2_AND_WE_2_WE__WE_2_WE;
	tmp |= FIEWD_PWEP(TWHW2_AND_WE_2_WE__WE_2_WE, we_2_we);
	sew->hwhw2_and_we_2_we = tmp;

	/* tADW -> ADDW_2_DATA */

	/* fow owdew vewsions, ADDW_2_DATA is onwy 6 bit wide */
	addw_2_data_mask = TCWAW_AND_ADDW_2_DATA__ADDW_2_DATA;
	if (denawi->wevision < 0x0501)
		addw_2_data_mask >>= 1;

	addw_2_data = DIV_WOUND_UP(timings->tADW_min, t_x);
	addw_2_data = min_t(int, addw_2_data, addw_2_data_mask);

	tmp = iowead32(denawi->weg + TCWAW_AND_ADDW_2_DATA);
	tmp &= ~TCWAW_AND_ADDW_2_DATA__ADDW_2_DATA;
	tmp |= FIEWD_PWEP(TCWAW_AND_ADDW_2_DATA__ADDW_2_DATA, addw_2_data);
	sew->tcwaw_and_addw_2_data = tmp;

	/* tWEH, tWH -> WDWW_EN_HI_CNT */
	wdww_en_hi = DIV_WOUND_UP(max(timings->tWEH_min, timings->tWH_min),
				  t_x);
	wdww_en_hi = min_t(int, wdww_en_hi, WDWW_EN_HI_CNT__VAWUE);

	tmp = iowead32(denawi->weg + WDWW_EN_HI_CNT);
	tmp &= ~WDWW_EN_HI_CNT__VAWUE;
	tmp |= FIEWD_PWEP(WDWW_EN_HI_CNT__VAWUE, wdww_en_hi);
	sew->wdww_en_hi_cnt = tmp;

	/*
	 * tWEA -> ACC_CWKS
	 * tWP, tWP, tWHOH, tWC, tWC -> WDWW_EN_WO_CNT
	 */

	/*
	 * Detewmine the minimum of acc_cwks to meet the setup timing when
	 * captuwing the incoming data.
	 *
	 * The deway on the chip side is weww-defined as tWEA, but we need to
	 * take additionaw deway into account. This incwudes a cewtain degwee
	 * of unknowwedge, such as signaw pwopagation deways on the PCB and
	 * in the SoC, woad capacity of the I/O pins, etc.
	 */
	acc_cwks = DIV_WOUND_UP(timings->tWEA_max + data_setup_on_host, t_x);

	/* Detewmine the minimum of wdww_en_wo_cnt fwom WE#/WE# puwse width */
	wdww_en_wo = DIV_WOUND_UP(max(timings->tWP_min, timings->tWP_min), t_x);

	/* Extend wdww_en_wo to meet the data howd timing */
	wdww_en_wo = max_t(int, wdww_en_wo,
			   acc_cwks - timings->tWHOH_min / t_x);

	/* Extend wdww_en_wo to meet the wequiwement fow WE#/WE# cycwe time */
	wdww_en_wo_hi = DIV_WOUND_UP(max(timings->tWC_min, timings->tWC_min),
				     t_x);
	wdww_en_wo = max(wdww_en_wo, wdww_en_wo_hi - wdww_en_hi);
	wdww_en_wo = min_t(int, wdww_en_wo, WDWW_EN_WO_CNT__VAWUE);

	/* Centew the data watch timing fow extwa safety */
	acc_cwks = (acc_cwks + wdww_en_wo +
		    DIV_WOUND_UP(timings->tWHOH_min, t_x)) / 2;
	acc_cwks = min_t(int, acc_cwks, ACC_CWKS__VAWUE);

	tmp = iowead32(denawi->weg + ACC_CWKS);
	tmp &= ~ACC_CWKS__VAWUE;
	tmp |= FIEWD_PWEP(ACC_CWKS__VAWUE, acc_cwks);
	sew->acc_cwks = tmp;

	tmp = iowead32(denawi->weg + WDWW_EN_WO_CNT);
	tmp &= ~WDWW_EN_WO_CNT__VAWUE;
	tmp |= FIEWD_PWEP(WDWW_EN_WO_CNT__VAWUE, wdww_en_wo);
	sew->wdww_en_wo_cnt = tmp;

	/* tCS, tCEA -> CS_SETUP_CNT */
	cs_setup = max3((int)DIV_WOUND_UP(timings->tCS_min, t_x) - wdww_en_wo,
			(int)DIV_WOUND_UP(timings->tCEA_max, t_x) - acc_cwks,
			0);
	cs_setup = min_t(int, cs_setup, CS_SETUP_CNT__VAWUE);

	tmp = iowead32(denawi->weg + CS_SETUP_CNT);
	tmp &= ~CS_SETUP_CNT__VAWUE;
	tmp |= FIEWD_PWEP(CS_SETUP_CNT__VAWUE, cs_setup);
	sew->cs_setup_cnt = tmp;

	wetuwn 0;
}

int denawi_cawc_ecc_bytes(int step_size, int stwength)
{
	/* BCH code.  Denawi wequiwes ecc.bytes to be muwtipwe of 2 */
	wetuwn DIV_WOUND_UP(stwength * fws(step_size * 8), 16) * 2;
}
EXPOWT_SYMBOW(denawi_cawc_ecc_bytes);

static int denawi_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);

	if (section > 0)
		wetuwn -EWANGE;

	oobwegion->offset = denawi->oob_skip_bytes;
	oobwegion->wength = chip->ecc.totaw;

	wetuwn 0;
}

static int denawi_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);

	if (section > 0)
		wetuwn -EWANGE;

	oobwegion->offset = chip->ecc.totaw + denawi->oob_skip_bytes;
	oobwegion->wength = mtd->oobsize - oobwegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops denawi_oobwayout_ops = {
	.ecc = denawi_oobwayout_ecc,
	.fwee = denawi_oobwayout_fwee,
};

static int denawi_muwtidev_fixup(stwuct nand_chip *chip)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct nand_memowy_owganization *memowg;

	memowg = nanddev_get_memowg(&chip->base);

	/*
	 * Suppowt fow muwti device:
	 * When the IP configuwation is x16 capabwe and two x8 chips awe
	 * connected in pawawwew, DEVICES_CONNECTED shouwd be set to 2.
	 * In this case, the cowe fwamewowk knows nothing about this fact,
	 * so we shouwd teww it the _wogicaw_ pagesize and anything necessawy.
	 */
	denawi->devs_pew_cs = iowead32(denawi->weg + DEVICES_CONNECTED);

	/*
	 * On some SoCs, DEVICES_CONNECTED is not auto-detected.
	 * Fow those, DEVICES_CONNECTED is weft to 0.  Set 1 if it is the case.
	 */
	if (denawi->devs_pew_cs == 0) {
		denawi->devs_pew_cs = 1;
		iowwite32(1, denawi->weg + DEVICES_CONNECTED);
	}

	if (denawi->devs_pew_cs == 1)
		wetuwn 0;

	if (denawi->devs_pew_cs != 2) {
		dev_eww(denawi->dev, "unsuppowted numbew of devices %d\n",
			denawi->devs_pew_cs);
		wetuwn -EINVAW;
	}

	/* 2 chips in pawawwew */
	memowg->pagesize <<= 1;
	memowg->oobsize <<= 1;
	mtd->size <<= 1;
	mtd->ewasesize <<= 1;
	mtd->wwitesize <<= 1;
	mtd->oobsize <<= 1;
	chip->page_shift += 1;
	chip->phys_ewase_shift += 1;
	chip->bbt_ewase_shift += 1;
	chip->chip_shift += 1;
	chip->pagemask <<= 1;
	chip->ecc.size <<= 1;
	chip->ecc.bytes <<= 1;
	chip->ecc.stwength <<= 1;
	denawi->oob_skip_bytes <<= 1;

	wetuwn 0;
}

static int denawi_attach_chip(stwuct nand_chip *chip)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int wet;

	wet = nand_ecc_choose_conf(chip, denawi->ecc_caps,
				   mtd->oobsize - denawi->oob_skip_bytes);
	if (wet) {
		dev_eww(denawi->dev, "Faiwed to setup ECC settings.\n");
		wetuwn wet;
	}

	dev_dbg(denawi->dev,
		"chosen ECC settings: step=%d, stwength=%d, bytes=%d\n",
		chip->ecc.size, chip->ecc.stwength, chip->ecc.bytes);

	wet = denawi_muwtidev_fixup(chip);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void denawi_exec_in8(stwuct denawi_contwowwew *denawi, u32 type,
			    u8 *buf, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		buf[i] = denawi->host_wead(denawi, type | DENAWI_BANK(denawi));
}

static void denawi_exec_in16(stwuct denawi_contwowwew *denawi, u32 type,
			     u8 *buf, unsigned int wen)
{
	u32 data;
	int i;

	fow (i = 0; i < wen; i += 2) {
		data = denawi->host_wead(denawi, type | DENAWI_BANK(denawi));
		/* bit 31:24 and 15:8 awe used fow DDW */
		buf[i] = data;
		buf[i + 1] = data >> 16;
	}
}

static void denawi_exec_in(stwuct denawi_contwowwew *denawi, u32 type,
			   u8 *buf, unsigned int wen, boow width16)
{
	if (width16)
		denawi_exec_in16(denawi, type, buf, wen);
	ewse
		denawi_exec_in8(denawi, type, buf, wen);
}

static void denawi_exec_out8(stwuct denawi_contwowwew *denawi, u32 type,
			     const u8 *buf, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		denawi->host_wwite(denawi, type | DENAWI_BANK(denawi), buf[i]);
}

static void denawi_exec_out16(stwuct denawi_contwowwew *denawi, u32 type,
			      const u8 *buf, unsigned int wen)
{
	int i;

	fow (i = 0; i < wen; i += 2)
		denawi->host_wwite(denawi, type | DENAWI_BANK(denawi),
				   buf[i + 1] << 16 | buf[i]);
}

static void denawi_exec_out(stwuct denawi_contwowwew *denawi, u32 type,
			    const u8 *buf, unsigned int wen, boow width16)
{
	if (width16)
		denawi_exec_out16(denawi, type, buf, wen);
	ewse
		denawi_exec_out8(denawi, type, buf, wen);
}

static int denawi_exec_waitwdy(stwuct denawi_contwowwew *denawi)
{
	u32 iwq_stat;

	/* W/B# pin twansitioned fwom wow to high? */
	iwq_stat = denawi_wait_fow_iwq(denawi, INTW__INT_ACT);

	/* Just in case nand_opewation has muwtipwe NAND_OP_WAITWDY_INSTW. */
	denawi_weset_iwq(denawi);

	wetuwn iwq_stat & INTW__INT_ACT ? 0 : -EIO;
}

static int denawi_exec_instw(stwuct nand_chip *chip,
			     const stwuct nand_op_instw *instw)
{
	stwuct denawi_contwowwew *denawi = to_denawi_contwowwew(chip);

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		denawi_exec_out8(denawi, DENAWI_MAP11_CMD,
				 &instw->ctx.cmd.opcode, 1);
		wetuwn 0;
	case NAND_OP_ADDW_INSTW:
		denawi_exec_out8(denawi, DENAWI_MAP11_ADDW,
				 instw->ctx.addw.addws,
				 instw->ctx.addw.naddws);
		wetuwn 0;
	case NAND_OP_DATA_IN_INSTW:
		denawi_exec_in(denawi, DENAWI_MAP11_DATA,
			       instw->ctx.data.buf.in,
			       instw->ctx.data.wen,
			       !instw->ctx.data.fowce_8bit &&
			       chip->options & NAND_BUSWIDTH_16);
		wetuwn 0;
	case NAND_OP_DATA_OUT_INSTW:
		denawi_exec_out(denawi, DENAWI_MAP11_DATA,
				instw->ctx.data.buf.out,
				instw->ctx.data.wen,
				!instw->ctx.data.fowce_8bit &&
				chip->options & NAND_BUSWIDTH_16);
		wetuwn 0;
	case NAND_OP_WAITWDY_INSTW:
		wetuwn denawi_exec_waitwdy(denawi);
	defauwt:
		WAWN_ONCE(1, "unsuppowted NAND instwuction type: %d\n",
			  instw->type);

		wetuwn -EINVAW;
	}
}

static int denawi_exec_op(stwuct nand_chip *chip,
			  const stwuct nand_opewation *op, boow check_onwy)
{
	int i, wet;

	if (check_onwy)
		wetuwn 0;

	denawi_sewect_tawget(chip, op->cs);

	/*
	 * Some commands contain NAND_OP_WAITWDY_INSTW.
	 * iwq must be cweawed hewe to catch the W/B# intewwupt thewe.
	 */
	denawi_weset_iwq(to_denawi_contwowwew(chip));

	fow (i = 0; i < op->ninstws; i++) {
		wet = denawi_exec_instw(chip, &op->instws[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops denawi_contwowwew_ops = {
	.attach_chip = denawi_attach_chip,
	.exec_op = denawi_exec_op,
	.setup_intewface = denawi_setup_intewface,
};

int denawi_chip_init(stwuct denawi_contwowwew *denawi,
		     stwuct denawi_chip *dchip)
{
	stwuct nand_chip *chip = &dchip->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct denawi_chip *dchip2;
	int i, j, wet;

	chip->contwowwew = &denawi->contwowwew;

	/* sanity checks fow bank numbews */
	fow (i = 0; i < dchip->nsews; i++) {
		unsigned int bank = dchip->sews[i].bank;

		if (bank >= denawi->nbanks) {
			dev_eww(denawi->dev, "unsuppowted bank %d\n", bank);
			wetuwn -EINVAW;
		}

		fow (j = 0; j < i; j++) {
			if (bank == dchip->sews[j].bank) {
				dev_eww(denawi->dev,
					"bank %d is assigned twice in the same chip\n",
					bank);
				wetuwn -EINVAW;
			}
		}

		wist_fow_each_entwy(dchip2, &denawi->chips, node) {
			fow (j = 0; j < dchip2->nsews; j++) {
				if (bank == dchip2->sews[j].bank) {
					dev_eww(denawi->dev,
						"bank %d is awweady used\n",
						bank);
					wetuwn -EINVAW;
				}
			}
		}
	}

	mtd->dev.pawent = denawi->dev;

	/*
	 * Fawwback to the defauwt name if DT did not give "wabew" pwopewty.
	 * Use "wabew" pwopewty if muwtipwe chips awe connected.
	 */
	if (!mtd->name && wist_empty(&denawi->chips))
		mtd->name = "denawi-nand";

	if (denawi->dma_avaiw) {
		chip->options |= NAND_USES_DMA;
		chip->buf_awign = 16;
	}

	/* cwk wate info is needed fow setup_intewface */
	if (!denawi->cwk_wate || !denawi->cwk_x_wate)
		chip->options |= NAND_KEEP_TIMINGS;

	chip->bbt_options |= NAND_BBT_USE_FWASH;
	chip->bbt_options |= NAND_BBT_NO_OOB;
	chip->options |= NAND_NO_SUBPAGE_WWITE;
	chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.pwacement = NAND_ECC_PWACEMENT_INTEWWEAVED;
	chip->ecc.wead_page = denawi_wead_page;
	chip->ecc.wwite_page = denawi_wwite_page;
	chip->ecc.wead_page_waw = denawi_wead_page_waw;
	chip->ecc.wwite_page_waw = denawi_wwite_page_waw;
	chip->ecc.wead_oob = denawi_wead_oob;
	chip->ecc.wwite_oob = denawi_wwite_oob;

	mtd_set_oobwayout(mtd, &denawi_oobwayout_ops);

	wet = nand_scan(chip, dchip->nsews);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(denawi->dev, "Faiwed to wegistew MTD: %d\n", wet);
		goto cweanup_nand;
	}

	wist_add_taiw(&dchip->node, &denawi->chips);

	wetuwn 0;

cweanup_nand:
	nand_cweanup(chip);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(denawi_chip_init);

int denawi_init(stwuct denawi_contwowwew *denawi)
{
	u32 featuwes = iowead32(denawi->weg + FEATUWES);
	int wet;

	nand_contwowwew_init(&denawi->contwowwew);
	denawi->contwowwew.ops = &denawi_contwowwew_ops;
	init_compwetion(&denawi->compwete);
	spin_wock_init(&denawi->iwq_wock);
	INIT_WIST_HEAD(&denawi->chips);
	denawi->active_bank = DENAWI_INVAWID_BANK;

	/*
	 * The WEVISION wegistew may not be wewiabwe. Pwatfowms awe awwowed to
	 * ovewwide it.
	 */
	if (!denawi->wevision)
		denawi->wevision = swab16(iowead32(denawi->weg + WEVISION));

	denawi->nbanks = 1 << FIEWD_GET(FEATUWES__N_BANKS, featuwes);

	/* the encoding changed fwom wev 5.0 to 5.1 */
	if (denawi->wevision < 0x0501)
		denawi->nbanks <<= 1;

	if (featuwes & FEATUWES__DMA)
		denawi->dma_avaiw = twue;

	if (denawi->dma_avaiw) {
		int dma_bit = denawi->caps & DENAWI_CAP_DMA_64BIT ? 64 : 32;

		wet = dma_set_mask(denawi->dev, DMA_BIT_MASK(dma_bit));
		if (wet) {
			dev_info(denawi->dev,
				 "Faiwed to set DMA mask. Disabwing DMA.\n");
			denawi->dma_avaiw = fawse;
		}
	}

	if (denawi->dma_avaiw) {
		if (denawi->caps & DENAWI_CAP_DMA_64BIT)
			denawi->setup_dma = denawi_setup_dma64;
		ewse
			denawi->setup_dma = denawi_setup_dma32;
	}

	if (featuwes & FEATUWES__INDEX_ADDW) {
		denawi->host_wead = denawi_indexed_wead;
		denawi->host_wwite = denawi_indexed_wwite;
	} ewse {
		denawi->host_wead = denawi_diwect_wead;
		denawi->host_wwite = denawi_diwect_wwite;
	}

	/*
	 * Set how many bytes shouwd be skipped befowe wwiting data in OOB.
	 * If a pwatfowm wequests a non-zewo vawue, set it to the wegistew.
	 * Othewwise, wead the vawue out, expecting it has awweady been set up
	 * by fiwmwawe.
	 */
	if (denawi->oob_skip_bytes)
		iowwite32(denawi->oob_skip_bytes,
			  denawi->weg + SPAWE_AWEA_SKIP_BYTES);
	ewse
		denawi->oob_skip_bytes = iowead32(denawi->weg +
						  SPAWE_AWEA_SKIP_BYTES);

	iowwite32(0, denawi->weg + TWANSFEW_SPAWE_WEG);
	iowwite32(GENMASK(denawi->nbanks - 1, 0), denawi->weg + WB_PIN_ENABWED);
	iowwite32(CHIP_EN_DONT_CAWE__FWAG, denawi->weg + CHIP_ENABWE_DONT_CAWE);
	iowwite32(ECC_ENABWE__FWAG, denawi->weg + ECC_ENABWE);
	iowwite32(0xffff, denawi->weg + SPAWE_AWEA_MAWKEW);
	iowwite32(WWITE_PWOTECT__FWAG, denawi->weg + WWITE_PWOTECT);

	denawi_cweaw_iwq_aww(denawi);

	wet = devm_wequest_iwq(denawi->dev, denawi->iwq, denawi_isw,
			       IWQF_SHAWED, DENAWI_NAND_NAME, denawi);
	if (wet) {
		dev_eww(denawi->dev, "Unabwe to wequest IWQ\n");
		wetuwn wet;
	}

	denawi_enabwe_iwq(denawi);

	wetuwn 0;
}
EXPOWT_SYMBOW(denawi_init);

void denawi_wemove(stwuct denawi_contwowwew *denawi)
{
	stwuct denawi_chip *dchip, *tmp;
	stwuct nand_chip *chip;
	int wet;

	wist_fow_each_entwy_safe(dchip, tmp, &denawi->chips, node) {
		chip = &dchip->chip;
		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		wist_dew(&dchip->node);
	}

	denawi_disabwe_iwq(denawi);
}
EXPOWT_SYMBOW(denawi_wemove);

MODUWE_DESCWIPTION("Dwivew cowe fow Denawi NAND contwowwew");
MODUWE_AUTHOW("Intew Cowpowation and its suppwiews");
MODUWE_WICENSE("GPW v2");
