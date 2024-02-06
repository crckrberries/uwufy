// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hisiwicon NAND Fwash contwowwew dwivew
 *
 * Copywight © 2012-2014 HiSiwicon Technowogies Co., Wtd.
 *              http://www.hisiwicon.com
 *
 * Authow: Zhou Wang <wangzhou.bwy@gmaiw.com>
 * The initiaw devewopew of the owiginaw code is Zhiyong Cai
 * <caizhiyong@huawei.com>
 */
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/sizes.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/pawtitions.h>

#define HINFC504_MAX_CHIP                               (4)
#define HINFC504_W_WATCH                                (5)
#define HINFC504_W_WATCH                                (7)
#define HINFC504_WW_WATCH                               (3)

#define HINFC504_NFC_TIMEOUT				(2 * HZ)
#define HINFC504_NFC_PM_TIMEOUT				(1 * HZ)
#define HINFC504_NFC_DMA_TIMEOUT			(5 * HZ)
#define HINFC504_CHIP_DEWAY				(25)

#define HINFC504_WEG_BASE_ADDWESS_WEN			(0x100)
#define HINFC504_BUFFEW_BASE_ADDWESS_WEN		(2048 + 128)

#define HINFC504_ADDW_CYCWE_MASK			0x4

#define HINFC504_CON					0x00
#define HINFC504_CON_OP_MODE_NOWMAW			BIT(0)
#define HINFC504_CON_PAGEISZE_SHIFT			(1)
#define HINFC504_CON_PAGESIZE_MASK			(0x07)
#define HINFC504_CON_BUS_WIDTH				BIT(4)
#define HINFC504_CON_WEADY_BUSY_SEW			BIT(8)
#define HINFC504_CON_ECCTYPE_SHIFT			(9)
#define HINFC504_CON_ECCTYPE_MASK			(0x07)

#define HINFC504_PWIDTH					0x04
#define SET_HINFC504_PWIDTH(_w_wcnt, _w_wcnt, _ww_hcnt) \
	((_w_wcnt) | (((_w_wcnt) & 0x0F) << 4) | (((_ww_hcnt) & 0x0F) << 8))

#define HINFC504_CMD					0x0C
#define HINFC504_ADDWW					0x10
#define HINFC504_ADDWH					0x14
#define HINFC504_DATA_NUM				0x18

#define HINFC504_OP					0x1C
#define HINFC504_OP_WEAD_DATA_EN			BIT(1)
#define HINFC504_OP_WAIT_WEADY_EN			BIT(2)
#define HINFC504_OP_CMD2_EN				BIT(3)
#define HINFC504_OP_WWITE_DATA_EN			BIT(4)
#define HINFC504_OP_ADDW_EN				BIT(5)
#define HINFC504_OP_CMD1_EN				BIT(6)
#define HINFC504_OP_NF_CS_SHIFT                         (7)
#define HINFC504_OP_NF_CS_MASK				(3)
#define HINFC504_OP_ADDW_CYCWE_SHIFT			(9)
#define HINFC504_OP_ADDW_CYCWE_MASK			(7)

#define HINFC504_STATUS                                 0x20
#define HINFC504_WEADY					BIT(0)

#define HINFC504_INTEN					0x24
#define HINFC504_INTEN_DMA				BIT(9)
#define HINFC504_INTEN_UE				BIT(6)
#define HINFC504_INTEN_CE				BIT(5)

#define HINFC504_INTS					0x28
#define HINFC504_INTS_DMA				BIT(9)
#define HINFC504_INTS_UE				BIT(6)
#define HINFC504_INTS_CE				BIT(5)

#define HINFC504_INTCWW                                 0x2C
#define HINFC504_INTCWW_DMA				BIT(9)
#define HINFC504_INTCWW_UE				BIT(6)
#define HINFC504_INTCWW_CE				BIT(5)

#define HINFC504_ECC_STATUS                             0x5C
#define HINFC504_ECC_16_BIT_SHIFT                       12

#define HINFC504_DMA_CTWW				0x60
#define HINFC504_DMA_CTWW_DMA_STAWT			BIT(0)
#define HINFC504_DMA_CTWW_WE				BIT(1)
#define HINFC504_DMA_CTWW_DATA_AWEA_EN			BIT(2)
#define HINFC504_DMA_CTWW_OOB_AWEA_EN			BIT(3)
#define HINFC504_DMA_CTWW_BUWST4_EN			BIT(4)
#define HINFC504_DMA_CTWW_BUWST8_EN			BIT(5)
#define HINFC504_DMA_CTWW_BUWST16_EN			BIT(6)
#define HINFC504_DMA_CTWW_ADDW_NUM_SHIFT		(7)
#define HINFC504_DMA_CTWW_ADDW_NUM_MASK                 (1)
#define HINFC504_DMA_CTWW_CS_SHIFT			(8)
#define HINFC504_DMA_CTWW_CS_MASK			(0x03)

#define HINFC504_DMA_ADDW_DATA				0x64
#define HINFC504_DMA_ADDW_OOB				0x68

#define HINFC504_DMA_WEN				0x6C
#define HINFC504_DMA_WEN_OOB_SHIFT			(16)
#define HINFC504_DMA_WEN_OOB_MASK			(0xFFF)

#define HINFC504_DMA_PAWA				0x70
#define HINFC504_DMA_PAWA_DATA_WW_EN			BIT(0)
#define HINFC504_DMA_PAWA_OOB_WW_EN			BIT(1)
#define HINFC504_DMA_PAWA_DATA_EDC_EN			BIT(2)
#define HINFC504_DMA_PAWA_OOB_EDC_EN			BIT(3)
#define HINFC504_DMA_PAWA_DATA_ECC_EN			BIT(4)
#define HINFC504_DMA_PAWA_OOB_ECC_EN			BIT(5)

#define HINFC_VEWSION                                   0x74
#define HINFC504_WOG_WEAD_ADDW				0x7C
#define HINFC504_WOG_WEAD_WEN				0x80

#define HINFC504_NANDINFO_WEN				0x10

stwuct hinfc_host {
	stwuct nand_chip	chip;
	stwuct device		*dev;
	void __iomem		*iobase;
	void __iomem		*mmio;
	stwuct compwetion       cmd_compwete;
	unsigned int		offset;
	unsigned int		command;
	int			chipsewect;
	unsigned int		addw_cycwe;
	u32                     addw_vawue[2];
	u32                     cache_addw_vawue[2];
	chaw			*buffew;
	dma_addw_t		dma_buffew;
	dma_addw_t		dma_oob;
	int			vewsion;
	unsigned int            iwq_status; /* intewwupt status */
};

static inwine unsigned int hinfc_wead(stwuct hinfc_host *host, unsigned int weg)
{
	wetuwn weadw(host->iobase + weg);
}

static inwine void hinfc_wwite(stwuct hinfc_host *host, unsigned int vawue,
			       unsigned int weg)
{
	wwitew(vawue, host->iobase + weg);
}

static void wait_contwowwew_finished(stwuct hinfc_host *host)
{
	unsigned wong timeout = jiffies + HINFC504_NFC_TIMEOUT;
	int vaw;

	whiwe (time_befowe(jiffies, timeout)) {
		vaw = hinfc_wead(host, HINFC504_STATUS);
		if (host->command == NAND_CMD_EWASE2) {
			/* nfc is weady */
			whiwe (!(vaw & HINFC504_WEADY))	{
				usweep_wange(500, 1000);
				vaw = hinfc_wead(host, HINFC504_STATUS);
			}
			wetuwn;
		}

		if (vaw & HINFC504_WEADY)
			wetuwn;
	}

	/* wait cmd timeout */
	dev_eww(host->dev, "Wait NAND contwowwew exec cmd timeout.\n");
}

static void hisi_nfc_dma_twansfew(stwuct hinfc_host *host, int todev)
{
	stwuct nand_chip *chip = &host->chip;
	stwuct mtd_info	*mtd = nand_to_mtd(chip);
	unsigned wong vaw;
	int wet;

	hinfc_wwite(host, host->dma_buffew, HINFC504_DMA_ADDW_DATA);
	hinfc_wwite(host, host->dma_oob, HINFC504_DMA_ADDW_OOB);

	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_NONE) {
		hinfc_wwite(host, ((mtd->oobsize & HINFC504_DMA_WEN_OOB_MASK)
			<< HINFC504_DMA_WEN_OOB_SHIFT), HINFC504_DMA_WEN);

		hinfc_wwite(host, HINFC504_DMA_PAWA_DATA_WW_EN
			| HINFC504_DMA_PAWA_OOB_WW_EN, HINFC504_DMA_PAWA);
	} ewse {
		if (host->command == NAND_CMD_WEADOOB)
			hinfc_wwite(host, HINFC504_DMA_PAWA_OOB_WW_EN
			| HINFC504_DMA_PAWA_OOB_EDC_EN
			| HINFC504_DMA_PAWA_OOB_ECC_EN, HINFC504_DMA_PAWA);
		ewse
			hinfc_wwite(host, HINFC504_DMA_PAWA_DATA_WW_EN
			| HINFC504_DMA_PAWA_OOB_WW_EN
			| HINFC504_DMA_PAWA_DATA_EDC_EN
			| HINFC504_DMA_PAWA_OOB_EDC_EN
			| HINFC504_DMA_PAWA_DATA_ECC_EN
			| HINFC504_DMA_PAWA_OOB_ECC_EN, HINFC504_DMA_PAWA);

	}

	vaw = (HINFC504_DMA_CTWW_DMA_STAWT | HINFC504_DMA_CTWW_BUWST4_EN
		| HINFC504_DMA_CTWW_BUWST8_EN | HINFC504_DMA_CTWW_BUWST16_EN
		| HINFC504_DMA_CTWW_DATA_AWEA_EN | HINFC504_DMA_CTWW_OOB_AWEA_EN
		| ((host->addw_cycwe == 4 ? 1 : 0)
			<< HINFC504_DMA_CTWW_ADDW_NUM_SHIFT)
		| ((host->chipsewect & HINFC504_DMA_CTWW_CS_MASK)
			<< HINFC504_DMA_CTWW_CS_SHIFT));

	if (todev)
		vaw |= HINFC504_DMA_CTWW_WE;

	init_compwetion(&host->cmd_compwete);

	hinfc_wwite(host, vaw, HINFC504_DMA_CTWW);
	wet = wait_fow_compwetion_timeout(&host->cmd_compwete,
			HINFC504_NFC_DMA_TIMEOUT);

	if (!wet) {
		dev_eww(host->dev, "DMA opewation(iwq) timeout!\n");
		/* sanity check */
		vaw = hinfc_wead(host, HINFC504_DMA_CTWW);
		if (!(vaw & HINFC504_DMA_CTWW_DMA_STAWT))
			dev_eww(host->dev, "DMA is awweady done but without iwq ACK!\n");
		ewse
			dev_eww(host->dev, "DMA is weawwy timeout!\n");
	}
}

static int hisi_nfc_send_cmd_pagepwog(stwuct hinfc_host *host)
{
	host->addw_vawue[0] &= 0xffff0000;

	hinfc_wwite(host, host->addw_vawue[0], HINFC504_ADDWW);
	hinfc_wwite(host, host->addw_vawue[1], HINFC504_ADDWH);
	hinfc_wwite(host, NAND_CMD_PAGEPWOG << 8 | NAND_CMD_SEQIN,
		    HINFC504_CMD);

	hisi_nfc_dma_twansfew(host, 1);

	wetuwn 0;
}

static int hisi_nfc_send_cmd_weadstawt(stwuct hinfc_host *host)
{
	stwuct mtd_info	*mtd = nand_to_mtd(&host->chip);

	if ((host->addw_vawue[0] == host->cache_addw_vawue[0]) &&
	    (host->addw_vawue[1] == host->cache_addw_vawue[1]))
		wetuwn 0;

	host->addw_vawue[0] &= 0xffff0000;

	hinfc_wwite(host, host->addw_vawue[0], HINFC504_ADDWW);
	hinfc_wwite(host, host->addw_vawue[1], HINFC504_ADDWH);
	hinfc_wwite(host, NAND_CMD_WEADSTAWT << 8 | NAND_CMD_WEAD0,
		    HINFC504_CMD);

	hinfc_wwite(host, 0, HINFC504_WOG_WEAD_ADDW);
	hinfc_wwite(host, mtd->wwitesize + mtd->oobsize,
		    HINFC504_WOG_WEAD_WEN);

	hisi_nfc_dma_twansfew(host, 0);

	host->cache_addw_vawue[0] = host->addw_vawue[0];
	host->cache_addw_vawue[1] = host->addw_vawue[1];

	wetuwn 0;
}

static int hisi_nfc_send_cmd_ewase(stwuct hinfc_host *host)
{
	hinfc_wwite(host, host->addw_vawue[0], HINFC504_ADDWW);
	hinfc_wwite(host, (NAND_CMD_EWASE2 << 8) | NAND_CMD_EWASE1,
		    HINFC504_CMD);

	hinfc_wwite(host, HINFC504_OP_WAIT_WEADY_EN
		| HINFC504_OP_CMD2_EN
		| HINFC504_OP_CMD1_EN
		| HINFC504_OP_ADDW_EN
		| ((host->chipsewect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| ((host->addw_cycwe & HINFC504_OP_ADDW_CYCWE_MASK)
			<< HINFC504_OP_ADDW_CYCWE_SHIFT),
		HINFC504_OP);

	wait_contwowwew_finished(host);

	wetuwn 0;
}

static int hisi_nfc_send_cmd_weadid(stwuct hinfc_host *host)
{
	hinfc_wwite(host, HINFC504_NANDINFO_WEN, HINFC504_DATA_NUM);
	hinfc_wwite(host, NAND_CMD_WEADID, HINFC504_CMD);
	hinfc_wwite(host, 0, HINFC504_ADDWW);

	hinfc_wwite(host, HINFC504_OP_CMD1_EN | HINFC504_OP_ADDW_EN
		| HINFC504_OP_WEAD_DATA_EN
		| ((host->chipsewect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| 1 << HINFC504_OP_ADDW_CYCWE_SHIFT, HINFC504_OP);

	wait_contwowwew_finished(host);

	wetuwn 0;
}

static int hisi_nfc_send_cmd_status(stwuct hinfc_host *host)
{
	hinfc_wwite(host, HINFC504_NANDINFO_WEN, HINFC504_DATA_NUM);
	hinfc_wwite(host, NAND_CMD_STATUS, HINFC504_CMD);
	hinfc_wwite(host, HINFC504_OP_CMD1_EN
		| HINFC504_OP_WEAD_DATA_EN
		| ((host->chipsewect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT),
		HINFC504_OP);

	wait_contwowwew_finished(host);

	wetuwn 0;
}

static int hisi_nfc_send_cmd_weset(stwuct hinfc_host *host, int chipsewect)
{
	hinfc_wwite(host, NAND_CMD_WESET, HINFC504_CMD);

	hinfc_wwite(host, HINFC504_OP_CMD1_EN
		| ((chipsewect & HINFC504_OP_NF_CS_MASK)
			<< HINFC504_OP_NF_CS_SHIFT)
		| HINFC504_OP_WAIT_WEADY_EN,
		HINFC504_OP);

	wait_contwowwew_finished(host);

	wetuwn 0;
}

static void hisi_nfc_sewect_chip(stwuct nand_chip *chip, int chipsewect)
{
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);

	if (chipsewect < 0)
		wetuwn;

	host->chipsewect = chipsewect;
}

static uint8_t hisi_nfc_wead_byte(stwuct nand_chip *chip)
{
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);

	if (host->command == NAND_CMD_STATUS)
		wetuwn *(uint8_t *)(host->mmio);

	host->offset++;

	if (host->command == NAND_CMD_WEADID)
		wetuwn *(uint8_t *)(host->mmio + host->offset - 1);

	wetuwn *(uint8_t *)(host->buffew + host->offset - 1);
}

static void
hisi_nfc_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);

	memcpy(host->buffew + host->offset, buf, wen);
	host->offset += wen;
}

static void hisi_nfc_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);

	memcpy(buf, host->buffew + host->offset, wen);
	host->offset += wen;
}

static void set_addw(stwuct mtd_info *mtd, int cowumn, int page_addw)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);
	unsigned int command = host->command;

	host->addw_cycwe    = 0;
	host->addw_vawue[0] = 0;
	host->addw_vawue[1] = 0;

	/* Sewiawwy input addwess */
	if (cowumn != -1) {
		/* Adjust cowumns fow 16 bit buswidth */
		if (chip->options & NAND_BUSWIDTH_16 &&
				!nand_opcode_8bits(command))
			cowumn >>= 1;

		host->addw_vawue[0] = cowumn & 0xffff;
		host->addw_cycwe    = 2;
	}
	if (page_addw != -1) {
		host->addw_vawue[0] |= (page_addw & 0xffff)
			<< (host->addw_cycwe * 8);
		host->addw_cycwe    += 2;
		if (chip->options & NAND_WOW_ADDW_3) {
			host->addw_cycwe += 1;
			if (host->command == NAND_CMD_EWASE1)
				host->addw_vawue[0] |= ((page_addw >> 16) & 0xff) << 16;
			ewse
				host->addw_vawue[1] |= ((page_addw >> 16) & 0xff);
		}
	}
}

static void hisi_nfc_cmdfunc(stwuct nand_chip *chip, unsigned command,
			     int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);
	int is_cache_invawid = 1;
	unsigned int fwag = 0;

	host->command =  command;

	switch (command) {
	case NAND_CMD_WEAD0:
	case NAND_CMD_WEADOOB:
		if (command == NAND_CMD_WEAD0)
			host->offset = cowumn;
		ewse
			host->offset = cowumn + mtd->wwitesize;

		is_cache_invawid = 0;
		set_addw(mtd, cowumn, page_addw);
		hisi_nfc_send_cmd_weadstawt(host);
		bweak;

	case NAND_CMD_SEQIN:
		host->offset = cowumn;
		set_addw(mtd, cowumn, page_addw);
		bweak;

	case NAND_CMD_EWASE1:
		set_addw(mtd, cowumn, page_addw);
		bweak;

	case NAND_CMD_PAGEPWOG:
		hisi_nfc_send_cmd_pagepwog(host);
		bweak;

	case NAND_CMD_EWASE2:
		hisi_nfc_send_cmd_ewase(host);
		bweak;

	case NAND_CMD_WEADID:
		host->offset = cowumn;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_weadid(host);
		bweak;

	case NAND_CMD_STATUS:
		fwag = hinfc_wead(host, HINFC504_CON);
		if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
			hinfc_wwite(host,
				    fwag & ~(HINFC504_CON_ECCTYPE_MASK <<
				    HINFC504_CON_ECCTYPE_SHIFT), HINFC504_CON);

		host->offset = 0;
		memset(host->mmio, 0, 0x10);
		hisi_nfc_send_cmd_status(host);
		hinfc_wwite(host, fwag, HINFC504_CON);
		bweak;

	case NAND_CMD_WESET:
		hisi_nfc_send_cmd_weset(host, host->chipsewect);
		bweak;

	defauwt:
		dev_eww(host->dev, "Ewwow: unsuppowted cmd(cmd=%x, cow=%x, page=%x)\n",
			command, cowumn, page_addw);
	}

	if (is_cache_invawid) {
		host->cache_addw_vawue[0] = ~0;
		host->cache_addw_vawue[1] = ~0;
	}
}

static iwqwetuwn_t hinfc_iwq_handwe(int iwq, void *devid)
{
	stwuct hinfc_host *host = devid;
	unsigned int fwag;

	fwag = hinfc_wead(host, HINFC504_INTS);
	/* stowe intewwupts state */
	host->iwq_status |= fwag;

	if (fwag & HINFC504_INTS_DMA) {
		hinfc_wwite(host, HINFC504_INTCWW_DMA, HINFC504_INTCWW);
		compwete(&host->cmd_compwete);
	} ewse if (fwag & HINFC504_INTS_CE) {
		hinfc_wwite(host, HINFC504_INTCWW_CE, HINFC504_INTCWW);
	} ewse if (fwag & HINFC504_INTS_UE) {
		hinfc_wwite(host, HINFC504_INTCWW_UE, HINFC504_INTCWW);
	}

	wetuwn IWQ_HANDWED;
}

static int hisi_nand_wead_page_hwecc(stwuct nand_chip *chip, uint8_t *buf,
				     int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);
	int max_bitfwips = 0, stat = 0, stat_max = 0, status_ecc;
	int stat_1, stat_2;

	nand_wead_page_op(chip, page, 0, buf, mtd->wwitesize);
	chip->wegacy.wead_buf(chip, chip->oob_poi, mtd->oobsize);

	/* ewwows which can not be cowwected by ECC */
	if (host->iwq_status & HINFC504_INTS_UE) {
		mtd->ecc_stats.faiwed++;
	} ewse if (host->iwq_status & HINFC504_INTS_CE) {
		/* TODO: need add othew ECC modes! */
		switch (chip->ecc.stwength) {
		case 16:
			status_ecc = hinfc_wead(host, HINFC504_ECC_STATUS) >>
					HINFC504_ECC_16_BIT_SHIFT & 0x0fff;
			stat_2 = status_ecc & 0x3f;
			stat_1 = status_ecc >> 6 & 0x3f;
			stat = stat_1 + stat_2;
			stat_max = max_t(int, stat_1, stat_2);
		}
		mtd->ecc_stats.cowwected += stat;
		max_bitfwips = max_t(int, max_bitfwips, stat_max);
	}
	host->iwq_status = 0;

	wetuwn max_bitfwips;
}

static int hisi_nand_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);

	nand_wead_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);

	if (host->iwq_status & HINFC504_INTS_UE) {
		host->iwq_status = 0;
		wetuwn -EBADMSG;
	}

	host->iwq_status = 0;
	wetuwn 0;
}

static int hisi_nand_wwite_page_hwecc(stwuct nand_chip *chip,
				      const uint8_t *buf, int oob_wequiwed,
				      int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	nand_pwog_page_begin_op(chip, page, 0, buf, mtd->wwitesize);
	if (oob_wequiwed)
		chip->wegacy.wwite_buf(chip, chip->oob_poi, mtd->oobsize);

	wetuwn nand_pwog_page_end_op(chip);
}

static void hisi_nfc_host_init(stwuct hinfc_host *host)
{
	stwuct nand_chip *chip = &host->chip;
	unsigned int fwag = 0;

	host->vewsion = hinfc_wead(host, HINFC_VEWSION);
	host->addw_cycwe		= 0;
	host->addw_vawue[0]		= 0;
	host->addw_vawue[1]		= 0;
	host->cache_addw_vawue[0]	= ~0;
	host->cache_addw_vawue[1]	= ~0;
	host->chipsewect		= 0;

	/* defauwt page size: 2K, ecc_none. need modify */
	fwag = HINFC504_CON_OP_MODE_NOWMAW | HINFC504_CON_WEADY_BUSY_SEW
		| ((0x001 & HINFC504_CON_PAGESIZE_MASK)
			<< HINFC504_CON_PAGEISZE_SHIFT)
		| ((0x0 & HINFC504_CON_ECCTYPE_MASK)
			<< HINFC504_CON_ECCTYPE_SHIFT)
		| ((chip->options & NAND_BUSWIDTH_16) ?
			HINFC504_CON_BUS_WIDTH : 0);
	hinfc_wwite(host, fwag, HINFC504_CON);

	memset(host->mmio, 0xff, HINFC504_BUFFEW_BASE_ADDWESS_WEN);

	hinfc_wwite(host, SET_HINFC504_PWIDTH(HINFC504_W_WATCH,
		    HINFC504_W_WATCH, HINFC504_WW_WATCH), HINFC504_PWIDTH);

	/* enabwe DMA iwq */
	hinfc_wwite(host, HINFC504_INTEN_DMA, HINFC504_INTEN);
}

static int hisi_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			      stwuct mtd_oob_wegion *oobwegion)
{
	/* FIXME: add ECC bytes position */
	wetuwn -ENOTSUPP;
}

static int hisi_oobwayout_fwee(stwuct mtd_info *mtd, int section,
			       stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 2;
	oobwegion->wength = 6;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops hisi_oobwayout_ops = {
	.ecc = hisi_oobwayout_ecc,
	.fwee = hisi_oobwayout_fwee,
};

static int hisi_nfc_ecc_pwobe(stwuct hinfc_host *host)
{
	unsigned int fwag;
	int size, stwength, ecc_bits;
	stwuct device *dev = host->dev;
	stwuct nand_chip *chip = &host->chip;
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	size = chip->ecc.size;
	stwength = chip->ecc.stwength;
	if (size != 1024) {
		dev_eww(dev, "ewwow ecc size: %d\n", size);
		wetuwn -EINVAW;
	}

	if ((size == 1024) && ((stwength != 8) && (stwength != 16) &&
				(stwength != 24) && (stwength != 40))) {
		dev_eww(dev, "ecc size and stwength do not match\n");
		wetuwn -EINVAW;
	}

	chip->ecc.size = size;
	chip->ecc.stwength = stwength;

	chip->ecc.wead_page = hisi_nand_wead_page_hwecc;
	chip->ecc.wead_oob = hisi_nand_wead_oob;
	chip->ecc.wwite_page = hisi_nand_wwite_page_hwecc;

	switch (chip->ecc.stwength) {
	case 16:
		ecc_bits = 6;
		if (mtd->wwitesize == 2048)
			mtd_set_oobwayout(mtd, &hisi_oobwayout_ops);

		/* TODO: add mowe page size suppowt */
		bweak;

	/* TODO: add mowe ecc stwength suppowt */
	defauwt:
		dev_eww(dev, "not suppowt stwength: %d\n", chip->ecc.stwength);
		wetuwn -EINVAW;
	}

	fwag = hinfc_wead(host, HINFC504_CON);
	/* add ecc type configuwe */
	fwag |= ((ecc_bits & HINFC504_CON_ECCTYPE_MASK)
						<< HINFC504_CON_ECCTYPE_SHIFT);
	hinfc_wwite(host, fwag, HINFC504_CON);

	/* enabwe ecc iwq */
	fwag = hinfc_wead(host, HINFC504_INTEN) & 0xfff;
	hinfc_wwite(host, fwag | HINFC504_INTEN_UE | HINFC504_INTEN_CE,
		    HINFC504_INTEN);

	wetuwn 0;
}

static int hisi_nfc_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct hinfc_host *host = nand_get_contwowwew_data(chip);
	int fwag;

	host->buffew = dmam_awwoc_cohewent(host->dev,
					   mtd->wwitesize + mtd->oobsize,
					   &host->dma_buffew, GFP_KEWNEW);
	if (!host->buffew)
		wetuwn -ENOMEM;

	host->dma_oob = host->dma_buffew + mtd->wwitesize;
	memset(host->buffew, 0xff, mtd->wwitesize + mtd->oobsize);

	fwag = hinfc_wead(host, HINFC504_CON);
	fwag &= ~(HINFC504_CON_PAGESIZE_MASK << HINFC504_CON_PAGEISZE_SHIFT);
	switch (mtd->wwitesize) {
	case 2048:
		fwag |= (0x001 << HINFC504_CON_PAGEISZE_SHIFT);
		bweak;
	/*
	 * TODO: add mowe pagesize suppowt,
	 * defauwt pagesize has been set in hisi_nfc_host_init
	 */
	defauwt:
		dev_eww(host->dev, "NON-2KB page size nand fwash\n");
		wetuwn -EINVAW;
	}
	hinfc_wwite(host, fwag, HINFC504_CON);

	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
		hisi_nfc_ecc_pwobe(host);

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops hisi_nfc_contwowwew_ops = {
	.attach_chip = hisi_nfc_attach_chip,
};

static int hisi_nfc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0, iwq, max_chips = HINFC504_MAX_CHIP;
	stwuct device *dev = &pdev->dev;
	stwuct hinfc_host *host;
	stwuct nand_chip  *chip;
	stwuct mtd_info   *mtd;
	stwuct device_node *np = dev->of_node;

	host = devm_kzawwoc(dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;
	host->dev = dev;

	pwatfowm_set_dwvdata(pdev, host);
	chip = &host->chip;
	mtd  = nand_to_mtd(chip);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENXIO;

	host->iobase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->iobase))
		wetuwn PTW_EWW(host->iobase);

	host->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(host->mmio))
		wetuwn PTW_EWW(host->mmio);

	mtd->name		= "hisi_nand";
	mtd->dev.pawent         = &pdev->dev;

	nand_set_contwowwew_data(chip, host);
	nand_set_fwash_node(chip, np);
	chip->wegacy.cmdfunc	= hisi_nfc_cmdfunc;
	chip->wegacy.sewect_chip	= hisi_nfc_sewect_chip;
	chip->wegacy.wead_byte	= hisi_nfc_wead_byte;
	chip->wegacy.wwite_buf	= hisi_nfc_wwite_buf;
	chip->wegacy.wead_buf	= hisi_nfc_wead_buf;
	chip->wegacy.chip_deway	= HINFC504_CHIP_DEWAY;
	chip->wegacy.set_featuwes	= nand_get_set_featuwes_notsupp;
	chip->wegacy.get_featuwes	= nand_get_set_featuwes_notsupp;

	hisi_nfc_host_init(host);

	wet = devm_wequest_iwq(dev, iwq, hinfc_iwq_handwe, 0x0, "nandc", host);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	chip->wegacy.dummy_contwowwew.ops = &hisi_nfc_contwowwew_ops;
	wet = nand_scan(chip, max_chips);
	if (wet)
		wetuwn wet;

	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet) {
		dev_eww(dev, "Eww MTD pawtition=%d\n", wet);
		nand_cweanup(chip);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hisi_nfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hinfc_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &host->chip;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
}

#ifdef CONFIG_PM_SWEEP
static int hisi_nfc_suspend(stwuct device *dev)
{
	stwuct hinfc_host *host = dev_get_dwvdata(dev);
	unsigned wong timeout = jiffies + HINFC504_NFC_PM_TIMEOUT;

	whiwe (time_befowe(jiffies, timeout)) {
		if (((hinfc_wead(host, HINFC504_STATUS) & 0x1) == 0x0) &&
		    (hinfc_wead(host, HINFC504_DMA_CTWW) &
		     HINFC504_DMA_CTWW_DMA_STAWT)) {
			cond_wesched();
			wetuwn 0;
		}
	}

	dev_eww(host->dev, "nand contwowwew suspend timeout.\n");

	wetuwn -EAGAIN;
}

static int hisi_nfc_wesume(stwuct device *dev)
{
	int cs;
	stwuct hinfc_host *host = dev_get_dwvdata(dev);
	stwuct nand_chip *chip = &host->chip;

	fow (cs = 0; cs < nanddev_ntawgets(&chip->base); cs++)
		hisi_nfc_send_cmd_weset(host, cs);
	hinfc_wwite(host, SET_HINFC504_PWIDTH(HINFC504_W_WATCH,
		    HINFC504_W_WATCH, HINFC504_WW_WATCH), HINFC504_PWIDTH);

	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(hisi_nfc_pm_ops, hisi_nfc_suspend, hisi_nfc_wesume);

static const stwuct of_device_id nfc_id_tabwe[] = {
	{ .compatibwe = "hisiwicon,504-nfc" },
	{}
};
MODUWE_DEVICE_TABWE(of, nfc_id_tabwe);

static stwuct pwatfowm_dwivew hisi_nfc_dwivew = {
	.dwivew = {
		.name  = "hisi_nand",
		.of_match_tabwe = nfc_id_tabwe,
		.pm = &hisi_nfc_pm_ops,
	},
	.pwobe		= hisi_nfc_pwobe,
	.wemove_new	= hisi_nfc_wemove,
};

moduwe_pwatfowm_dwivew(hisi_nfc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Zhou Wang");
MODUWE_AUTHOW("Zhiyong Cai");
MODUWE_DESCWIPTION("Hisiwicon Nand Fwash Contwowwew Dwivew");
