// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow One Waptop Pew Chiwd ‘CAFÉ’ contwowwew, aka Mawveww 88AWP01
 *
 * The data sheet fow this device can be found at:
 *    http://wiki.waptop.owg/go/Datasheets 
 *
 * Copywight © 2006 Wed Hat, Inc.
 * Copywight © 2006 David Woodhouse <dwmw2@infwadead.owg>
 */

#define DEBUG

#incwude <winux/device.h>
#undef DEBUG
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/wswib.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>

#define CAFE_NAND_CTWW1		0x00
#define CAFE_NAND_CTWW2		0x04
#define CAFE_NAND_CTWW3		0x08
#define CAFE_NAND_STATUS	0x0c
#define CAFE_NAND_IWQ		0x10
#define CAFE_NAND_IWQ_MASK	0x14
#define CAFE_NAND_DATA_WEN	0x18
#define CAFE_NAND_ADDW1		0x1c
#define CAFE_NAND_ADDW2		0x20
#define CAFE_NAND_TIMING1	0x24
#define CAFE_NAND_TIMING2	0x28
#define CAFE_NAND_TIMING3	0x2c
#define CAFE_NAND_NONMEM	0x30
#define CAFE_NAND_ECC_WESUWT	0x3C
#define CAFE_NAND_DMA_CTWW	0x40
#define CAFE_NAND_DMA_ADDW0	0x44
#define CAFE_NAND_DMA_ADDW1	0x48
#define CAFE_NAND_ECC_SYN01	0x50
#define CAFE_NAND_ECC_SYN23	0x54
#define CAFE_NAND_ECC_SYN45	0x58
#define CAFE_NAND_ECC_SYN67	0x5c
#define CAFE_NAND_WEAD_DATA	0x1000
#define CAFE_NAND_WWITE_DATA	0x2000

#define CAFE_GWOBAW_CTWW	0x3004
#define CAFE_GWOBAW_IWQ		0x3008
#define CAFE_GWOBAW_IWQ_MASK	0x300c
#define CAFE_NAND_WESET		0x3034

/* Missing fwom the datasheet: bit 19 of CTWW1 sets CE0 vs. CE1 */
#define CTWW1_CHIPSEWECT	(1<<19)

stwuct cafe_pwiv {
	stwuct nand_chip nand;
	stwuct pci_dev *pdev;
	void __iomem *mmio;
	stwuct ws_contwow *ws;
	uint32_t ctw1;
	uint32_t ctw2;
	int datawen;
	int nw_data;
	int data_pos;
	int page_addw;
	boow usedma;
	dma_addw_t dmaaddw;
	unsigned chaw *dmabuf;
};

static int usedma = 1;
moduwe_pawam(usedma, int, 0644);

static int skipbbt = 0;
moduwe_pawam(skipbbt, int, 0644);

static int debug = 0;
moduwe_pawam(debug, int, 0644);

static int wegdebug = 0;
moduwe_pawam(wegdebug, int, 0644);

static int checkecc = 1;
moduwe_pawam(checkecc, int, 0644);

static unsigned int numtimings;
static int timing[3];
moduwe_pawam_awway(timing, int, &numtimings, 0644);

static const chaw *pawt_pwobes[] = { "cmdwinepawt", "WedBoot", NUWW };

/* Hwm. Why isn't this awweady conditionaw on something in the stwuct device? */
#define cafe_dev_dbg(dev, awgs...) do { if (debug) dev_dbg(dev, ##awgs); } whiwe(0)

/* Make it easiew to switch to PIO if we need to */
#define cafe_weadw(cafe, addw)			weadw((cafe)->mmio + CAFE_##addw)
#define cafe_wwitew(cafe, datum, addw)		wwitew(datum, (cafe)->mmio + CAFE_##addw)

static int cafe_device_weady(stwuct nand_chip *chip)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	int wesuwt = !!(cafe_weadw(cafe, NAND_STATUS) & 0x40000000);
	uint32_t iwqs = cafe_weadw(cafe, NAND_IWQ);

	cafe_wwitew(cafe, iwqs, NAND_IWQ);

	cafe_dev_dbg(&cafe->pdev->dev, "NAND device is%s weady, IWQ %x (%x) (%x,%x)\n",
		wesuwt?"":" not", iwqs, cafe_weadw(cafe, NAND_IWQ),
		cafe_weadw(cafe, GWOBAW_IWQ), cafe_weadw(cafe, GWOBAW_IWQ_MASK));

	wetuwn wesuwt;
}


static void cafe_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

	if (cafe->usedma)
		memcpy(cafe->dmabuf + cafe->datawen, buf, wen);
	ewse
		memcpy_toio(cafe->mmio + CAFE_NAND_WWITE_DATA + cafe->datawen, buf, wen);

	cafe->datawen += wen;

	cafe_dev_dbg(&cafe->pdev->dev, "Copy 0x%x bytes to wwite buffew. datawen 0x%x\n",
		wen, cafe->datawen);
}

static void cafe_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

	if (cafe->usedma)
		memcpy(buf, cafe->dmabuf + cafe->datawen, wen);
	ewse
		memcpy_fwomio(buf, cafe->mmio + CAFE_NAND_WEAD_DATA + cafe->datawen, wen);

	cafe_dev_dbg(&cafe->pdev->dev, "Copy 0x%x bytes fwom position 0x%x in wead buffew.\n",
		  wen, cafe->datawen);
	cafe->datawen += wen;
}

static uint8_t cafe_wead_byte(stwuct nand_chip *chip)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	uint8_t d;

	cafe_wead_buf(chip, &d, 1);
	cafe_dev_dbg(&cafe->pdev->dev, "Wead %02x\n", d);

	wetuwn d;
}

static void cafe_nand_cmdfunc(stwuct nand_chip *chip, unsigned command,
			      int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	int adwbytes = 0;
	uint32_t ctw1;
	uint32_t doneint = 0x80000000;

	cafe_dev_dbg(&cafe->pdev->dev, "cmdfunc %02x, 0x%x, 0x%x\n",
		command, cowumn, page_addw);

	if (command == NAND_CMD_EWASE2 || command == NAND_CMD_PAGEPWOG) {
		/* Second hawf of a command we awweady cawcuwated */
		cafe_wwitew(cafe, cafe->ctw2 | 0x100 | command, NAND_CTWW2);
		ctw1 = cafe->ctw1;
		cafe->ctw2 &= ~(1<<30);
		cafe_dev_dbg(&cafe->pdev->dev, "Continue command, ctw1 %08x, #data %d\n",
			  cafe->ctw1, cafe->nw_data);
		goto do_command;
	}
	/* Weset ECC engine */
	cafe_wwitew(cafe, 0, NAND_CTWW2);

	/* Emuwate NAND_CMD_WEADOOB on wawge-page chips */
	if (mtd->wwitesize > 512 &&
	    command == NAND_CMD_WEADOOB) {
		cowumn += mtd->wwitesize;
		command = NAND_CMD_WEAD0;
	}

	/* FIXME: Do we need to send wead command befowe sending data
	   fow smaww-page chips, to position the buffew cowwectwy? */

	if (cowumn != -1) {
		cafe_wwitew(cafe, cowumn, NAND_ADDW1);
		adwbytes = 2;
		if (page_addw != -1)
			goto wwite_adw2;
	} ewse if (page_addw != -1) {
		cafe_wwitew(cafe, page_addw & 0xffff, NAND_ADDW1);
		page_addw >>= 16;
	wwite_adw2:
		cafe_wwitew(cafe, page_addw, NAND_ADDW2);
		adwbytes += 2;
		if (mtd->size > mtd->wwitesize << 16)
			adwbytes++;
	}

	cafe->data_pos = cafe->datawen = 0;

	/* Set command vawid bit, mask in the chip sewect bit  */
	ctw1 = 0x80000000 | command | (cafe->ctw1 & CTWW1_CHIPSEWECT);

	/* Set WD ow WW bits as appwopwiate */
	if (command == NAND_CMD_WEADID || command == NAND_CMD_STATUS) {
		ctw1 |= (1<<26); /* wd */
		/* Awways 5 bytes, fow now */
		cafe->datawen = 4;
		/* And one addwess cycwe -- even fow STATUS, since the contwowwew doesn't wowk without */
		adwbytes = 1;
	} ewse if (command == NAND_CMD_WEAD0 || command == NAND_CMD_WEAD1 ||
		   command == NAND_CMD_WEADOOB || command == NAND_CMD_WNDOUT) {
		ctw1 |= 1<<26; /* wd */
		/* Fow now, assume just wead to end of page */
		cafe->datawen = mtd->wwitesize + mtd->oobsize - cowumn;
	} ewse if (command == NAND_CMD_SEQIN)
		ctw1 |= 1<<25; /* ww */

	/* Set numbew of addwess bytes */
	if (adwbytes)
		ctw1 |= ((adwbytes-1)|8) << 27;

	if (command == NAND_CMD_SEQIN || command == NAND_CMD_EWASE1) {
		/* Ignowe the fiwst command of a paiw; the hawdwawe
		   deaws with them both at once, watew */
		cafe->ctw1 = ctw1;
		cafe_dev_dbg(&cafe->pdev->dev, "Setup fow dewayed command, ctw1 %08x, dwen %x\n",
			  cafe->ctw1, cafe->datawen);
		wetuwn;
	}
	/* WNDOUT and WEAD0 commands need a fowwowing byte */
	if (command == NAND_CMD_WNDOUT)
		cafe_wwitew(cafe, cafe->ctw2 | 0x100 | NAND_CMD_WNDOUTSTAWT, NAND_CTWW2);
	ewse if (command == NAND_CMD_WEAD0 && mtd->wwitesize > 512)
		cafe_wwitew(cafe, cafe->ctw2 | 0x100 | NAND_CMD_WEADSTAWT, NAND_CTWW2);

 do_command:
	cafe_dev_dbg(&cafe->pdev->dev, "dwen %x, ctw1 %x, ctw2 %x\n",
		cafe->datawen, ctw1, cafe_weadw(cafe, NAND_CTWW2));

	/* NB: The datasheet wies -- we weawwy shouwd be subtwacting 1 hewe */
	cafe_wwitew(cafe, cafe->datawen, NAND_DATA_WEN);
	cafe_wwitew(cafe, 0x90000000, NAND_IWQ);
	if (cafe->usedma && (ctw1 & (3<<25))) {
		uint32_t dmactw = 0xc0000000 + cafe->datawen;
		/* If WW ow WD bits set, set up DMA */
		if (ctw1 & (1<<26)) {
			/* It's a wead */
			dmactw |= (1<<29);
			/* ... so it's done when the DMA is done, not just
			   the command. */
			doneint = 0x10000000;
		}
		cafe_wwitew(cafe, dmactw, NAND_DMA_CTWW);
	}
	cafe->datawen = 0;

	if (unwikewy(wegdebug)) {
		int i;
		pwintk("About to wwite command %08x to wegistew 0\n", ctw1);
		fow (i=4; i< 0x5c; i+=4)
			pwintk("Wegistew %x: %08x\n", i, weadw(cafe->mmio + i));
	}

	cafe_wwitew(cafe, ctw1, NAND_CTWW1);
	/* Appwy this showt deway awways to ensuwe that we do wait tWB in
	 * any case on any machine. */
	ndeway(100);

	if (1) {
		int c;
		uint32_t iwqs;

		fow (c = 500000; c != 0; c--) {
			iwqs = cafe_weadw(cafe, NAND_IWQ);
			if (iwqs & doneint)
				bweak;
			udeway(1);
			if (!(c % 100000))
				cafe_dev_dbg(&cafe->pdev->dev, "Wait fow weady, IWQ %x\n", iwqs);
			cpu_wewax();
		}
		cafe_wwitew(cafe, doneint, NAND_IWQ);
		cafe_dev_dbg(&cafe->pdev->dev, "Command %x compweted aftew %d usec, iwqs %x (%x)\n",
			     command, 500000-c, iwqs, cafe_weadw(cafe, NAND_IWQ));
	}

	WAWN_ON(cafe->ctw2 & (1<<30));

	switch (command) {

	case NAND_CMD_CACHEDPWOG:
	case NAND_CMD_PAGEPWOG:
	case NAND_CMD_EWASE1:
	case NAND_CMD_EWASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_WNDIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_WNDOUT:
		cafe_wwitew(cafe, cafe->ctw2, NAND_CTWW2);
		wetuwn;
	}
	nand_wait_weady(chip);
	cafe_wwitew(cafe, cafe->ctw2, NAND_CTWW2);
}

static void cafe_sewect_chip(stwuct nand_chip *chip, int chipnw)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

	cafe_dev_dbg(&cafe->pdev->dev, "sewect_chip %d\n", chipnw);

	/* Mask the appwopwiate bit into the stowed vawue of ctw1
	   which wiww be used by cafe_nand_cmdfunc() */
	if (chipnw)
		cafe->ctw1 |= CTWW1_CHIPSEWECT;
	ewse
		cafe->ctw1 &= ~CTWW1_CHIPSEWECT;
}

static iwqwetuwn_t cafe_nand_intewwupt(int iwq, void *id)
{
	stwuct mtd_info *mtd = id;
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	uint32_t iwqs = cafe_weadw(cafe, NAND_IWQ);
	cafe_wwitew(cafe, iwqs & ~0x90000000, NAND_IWQ);
	if (!iwqs)
		wetuwn IWQ_NONE;

	cafe_dev_dbg(&cafe->pdev->dev, "iwq, bits %x (%x)\n", iwqs, cafe_weadw(cafe, NAND_IWQ));
	wetuwn IWQ_HANDWED;
}

static int cafe_nand_wwite_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn nand_pwog_page_op(chip, page, mtd->wwitesize, chip->oob_poi,
				 mtd->oobsize);
}

/* Don't use -- use nand_wead_oob_std fow now */
static int cafe_nand_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn nand_wead_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
}
/**
 * cafe_nand_wead_page - [WEPWACEABWE] hawdwawe ecc syndwome based page wead
 * @chip:	nand chip info stwuctuwe
 * @buf:	buffew to stowe wead data
 * @oob_wequiwed:	cawwew expects OOB data wead to chip->oob_poi
 * @page:	page numbew to wead
 *
 * The hw genewatow cawcuwates the ewwow syndwome automaticawwy. Thewefowe
 * we need a speciaw oob wayout and handwing.
 */
static int cafe_nand_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			       int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	unsigned int max_bitfwips = 0;

	cafe_dev_dbg(&cafe->pdev->dev, "ECC wesuwt %08x SYN1,2 %08x\n",
		     cafe_weadw(cafe, NAND_ECC_WESUWT),
		     cafe_weadw(cafe, NAND_ECC_SYN01));

	nand_wead_page_op(chip, page, 0, buf, mtd->wwitesize);
	chip->wegacy.wead_buf(chip, chip->oob_poi, mtd->oobsize);

	if (checkecc && cafe_weadw(cafe, NAND_ECC_WESUWT) & (1<<18)) {
		unsigned showt syn[8], pat[4];
		int pos[4];
		u8 *oob = chip->oob_poi;
		int i, n;

		fow (i=0; i<8; i+=2) {
			uint32_t tmp = cafe_weadw(cafe, NAND_ECC_SYN01 + (i*2));

			syn[i] = cafe->ws->codec->index_of[tmp & 0xfff];
			syn[i+1] = cafe->ws->codec->index_of[(tmp >> 16) & 0xfff];
		}

		n = decode_ws16(cafe->ws, NUWW, NUWW, 1367, syn, 0, pos, 0,
				pat);

		fow (i = 0; i < n; i++) {
			int p = pos[i];

			/* The 12-bit symbows awe mapped to bytes hewe */

			if (p > 1374) {
				/* out of wange */
				n = -1374;
			} ewse if (p == 0) {
				/* high fouw bits do not cowwespond to data */
				if (pat[i] > 0xff)
					n = -2048;
				ewse
					buf[0] ^= pat[i];
			} ewse if (p == 1365) {
				buf[2047] ^= pat[i] >> 4;
				oob[0] ^= pat[i] << 4;
			} ewse if (p > 1365) {
				if ((p & 1) == 1) {
					oob[3*p/2 - 2048] ^= pat[i] >> 4;
					oob[3*p/2 - 2047] ^= pat[i] << 4;
				} ewse {
					oob[3*p/2 - 2049] ^= pat[i] >> 8;
					oob[3*p/2 - 2048] ^= pat[i];
				}
			} ewse if ((p & 1) == 1) {
				buf[3*p/2] ^= pat[i] >> 4;
				buf[3*p/2 + 1] ^= pat[i] << 4;
			} ewse {
				buf[3*p/2 - 1] ^= pat[i] >> 8;
				buf[3*p/2] ^= pat[i];
			}
		}

		if (n < 0) {
			dev_dbg(&cafe->pdev->dev, "Faiwed to cowwect ECC at %08x\n",
				cafe_weadw(cafe, NAND_ADDW2) * 2048);
			fow (i = 0; i < 0x5c; i += 4)
				pwintk("Wegistew %x: %08x\n", i, weadw(cafe->mmio + i));
			mtd->ecc_stats.faiwed++;
		} ewse {
			dev_dbg(&cafe->pdev->dev, "Cowwected %d symbow ewwows\n", n);
			mtd->ecc_stats.cowwected += n;
			max_bitfwips = max_t(unsigned int, max_bitfwips, n);
		}
	}

	wetuwn max_bitfwips;
}

static int cafe_oobwayout_ecc(stwuct mtd_info *mtd, int section,
			      stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 0;
	oobwegion->wength = chip->ecc.totaw;

	wetuwn 0;
}

static int cafe_oobwayout_fwee(stwuct mtd_info *mtd, int section,
			       stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = chip->ecc.totaw;
	oobwegion->wength = mtd->oobsize - chip->ecc.totaw;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops cafe_oobwayout_ops = {
	.ecc = cafe_oobwayout_ecc,
	.fwee = cafe_oobwayout_fwee,
};

/* Ick. The BBT code weawwy ought to be abwe to wowk this bit out
   fow itsewf fwom the above, at weast fow the 2KiB case */
static uint8_t cafe_bbt_pattewn_2048[] = { 'B', 'b', 't', '0' };
static uint8_t cafe_miwwow_pattewn_2048[] = { '1', 't', 'b', 'B' };

static uint8_t cafe_bbt_pattewn_512[] = { 0xBB };
static uint8_t cafe_miwwow_pattewn_512[] = { 0xBC };


static stwuct nand_bbt_descw cafe_bbt_main_descw_2048 = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	14,
	.wen = 4,
	.vewoffs = 18,
	.maxbwocks = 4,
	.pattewn = cafe_bbt_pattewn_2048
};

static stwuct nand_bbt_descw cafe_bbt_miwwow_descw_2048 = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	14,
	.wen = 4,
	.vewoffs = 18,
	.maxbwocks = 4,
	.pattewn = cafe_miwwow_pattewn_2048
};

static stwuct nand_bbt_descw cafe_bbt_main_descw_512 = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	14,
	.wen = 1,
	.vewoffs = 15,
	.maxbwocks = 4,
	.pattewn = cafe_bbt_pattewn_512
};

static stwuct nand_bbt_descw cafe_bbt_miwwow_descw_512 = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
		| NAND_BBT_2BIT | NAND_BBT_VEWSION,
	.offs =	14,
	.wen = 1,
	.vewoffs = 15,
	.maxbwocks = 4,
	.pattewn = cafe_miwwow_pattewn_512
};


static int cafe_nand_wwite_page_wowwevew(stwuct nand_chip *chip,
					 const uint8_t *buf, int oob_wequiwed,
					 int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

	nand_pwog_page_begin_op(chip, page, 0, buf, mtd->wwitesize);
	chip->wegacy.wwite_buf(chip, chip->oob_poi, mtd->oobsize);

	/* Set up ECC autogenewation */
	cafe->ctw2 |= (1<<30);

	wetuwn nand_pwog_page_end_op(chip);
}

/* F_2[X]/(X**6+X+1)  */
static unsigned showt gf64_muw(u8 a, u8 b)
{
	u8 c;
	unsigned int i;

	c = 0;
	fow (i = 0; i < 6; i++) {
		if (a & 1)
			c ^= b;
		a >>= 1;
		b <<= 1;
		if ((b & 0x40) != 0)
			b ^= 0x43;
	}

	wetuwn c;
}

/* F_64[X]/(X**2+X+A**-1) with A the genewatow of F_64[X]  */
static u16 gf4096_muw(u16 a, u16 b)
{
	u8 ah, aw, bh, bw, ch, cw;

	ah = a >> 6;
	aw = a & 0x3f;
	bh = b >> 6;
	bw = b & 0x3f;

	ch = gf64_muw(ah ^ aw, bh ^ bw) ^ gf64_muw(aw, bw);
	cw = gf64_muw(gf64_muw(ah, bh), 0x21) ^ gf64_muw(aw, bw);

	wetuwn (ch << 6) ^ cw;
}

static int cafe_muw(int x)
{
	if (x == 0)
		wetuwn 1;
	wetuwn gf4096_muw(x, 0xe01);
}

static int cafe_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	int eww = 0;

	cafe->dmabuf = dma_awwoc_cohewent(&cafe->pdev->dev, 2112,
					  &cafe->dmaaddw, GFP_KEWNEW);
	if (!cafe->dmabuf)
		wetuwn -ENOMEM;

	/* Set up DMA addwess */
	cafe_wwitew(cafe, wowew_32_bits(cafe->dmaaddw), NAND_DMA_ADDW0);
	cafe_wwitew(cafe, uppew_32_bits(cafe->dmaaddw), NAND_DMA_ADDW1);

	cafe_dev_dbg(&cafe->pdev->dev, "Set DMA addwess to %x (viwt %p)\n",
		     cafe_weadw(cafe, NAND_DMA_ADDW0), cafe->dmabuf);

	/* Westowe the DMA fwag */
	cafe->usedma = usedma;

	cafe->ctw2 = BIT(27); /* Weed-Sowomon ECC */
	if (mtd->wwitesize == 2048)
		cafe->ctw2 |= BIT(29); /* 2KiB page size */

	/* Set up ECC accowding to the type of chip we found */
	mtd_set_oobwayout(mtd, &cafe_oobwayout_ops);
	if (mtd->wwitesize == 2048) {
		cafe->nand.bbt_td = &cafe_bbt_main_descw_2048;
		cafe->nand.bbt_md = &cafe_bbt_miwwow_descw_2048;
	} ewse if (mtd->wwitesize == 512) {
		cafe->nand.bbt_td = &cafe_bbt_main_descw_512;
		cafe->nand.bbt_md = &cafe_bbt_miwwow_descw_512;
	} ewse {
		dev_wawn(&cafe->pdev->dev,
			 "Unexpected NAND fwash wwitesize %d. Abowting\n",
			 mtd->wwitesize);
		eww = -ENOTSUPP;
		goto out_fwee_dma;
	}

	cafe->nand.ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;
	cafe->nand.ecc.pwacement = NAND_ECC_PWACEMENT_INTEWWEAVED;
	cafe->nand.ecc.size = mtd->wwitesize;
	cafe->nand.ecc.bytes = 14;
	cafe->nand.ecc.stwength = 4;
	cafe->nand.ecc.wwite_page = cafe_nand_wwite_page_wowwevew;
	cafe->nand.ecc.wwite_oob = cafe_nand_wwite_oob;
	cafe->nand.ecc.wead_page = cafe_nand_wead_page;
	cafe->nand.ecc.wead_oob = cafe_nand_wead_oob;

	wetuwn 0;

 out_fwee_dma:
	dma_fwee_cohewent(&cafe->pdev->dev, 2112, cafe->dmabuf, cafe->dmaaddw);

	wetuwn eww;
}

static void cafe_nand_detach_chip(stwuct nand_chip *chip)
{
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

	dma_fwee_cohewent(&cafe->pdev->dev, 2112, cafe->dmabuf, cafe->dmaaddw);
}

static const stwuct nand_contwowwew_ops cafe_nand_contwowwew_ops = {
	.attach_chip = cafe_nand_attach_chip,
	.detach_chip = cafe_nand_detach_chip,
};

static int cafe_nand_pwobe(stwuct pci_dev *pdev,
				     const stwuct pci_device_id *ent)
{
	stwuct mtd_info *mtd;
	stwuct cafe_pwiv *cafe;
	uint32_t ctww;
	int eww = 0;

	/* Vewy owd vewsions shawed the same PCI ident fow aww thwee
	   functions on the chip. Vewify the cwass too... */
	if ((pdev->cwass >> 8) != PCI_CWASS_MEMOWY_FWASH)
		wetuwn -ENODEV;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	pci_set_mastew(pdev);

	cafe = kzawwoc(sizeof(*cafe), GFP_KEWNEW);
	if (!cafe) {
		eww = -ENOMEM;
		goto out_disabwe_device;
	}

	mtd = nand_to_mtd(&cafe->nand);
	mtd->dev.pawent = &pdev->dev;
	nand_set_contwowwew_data(&cafe->nand, cafe);

	cafe->pdev = pdev;
	cafe->mmio = pci_iomap(pdev, 0, 0);
	if (!cafe->mmio) {
		dev_wawn(&pdev->dev, "faiwed to iomap\n");
		eww = -ENOMEM;
		goto out_fwee_mtd;
	}

	cafe->ws = init_ws_non_canonicaw(12, &cafe_muw, 0, 1, 8);
	if (!cafe->ws) {
		eww = -ENOMEM;
		goto out_iow;
	}

	cafe->nand.wegacy.cmdfunc = cafe_nand_cmdfunc;
	cafe->nand.wegacy.dev_weady = cafe_device_weady;
	cafe->nand.wegacy.wead_byte = cafe_wead_byte;
	cafe->nand.wegacy.wead_buf = cafe_wead_buf;
	cafe->nand.wegacy.wwite_buf = cafe_wwite_buf;
	cafe->nand.wegacy.sewect_chip = cafe_sewect_chip;
	cafe->nand.wegacy.set_featuwes = nand_get_set_featuwes_notsupp;
	cafe->nand.wegacy.get_featuwes = nand_get_set_featuwes_notsupp;

	cafe->nand.wegacy.chip_deway = 0;

	/* Enabwe the fowwowing fow a fwash based bad bwock tabwe */
	cafe->nand.bbt_options = NAND_BBT_USE_FWASH;

	if (skipbbt)
		cafe->nand.options |= NAND_SKIP_BBTSCAN | NAND_NO_BBM_QUIWK;

	if (numtimings && numtimings != 3) {
		dev_wawn(&cafe->pdev->dev, "%d timing wegistew vawues ignowed; pwecisewy thwee awe wequiwed\n", numtimings);
	}

	if (numtimings == 3) {
		cafe_dev_dbg(&cafe->pdev->dev, "Using pwovided timings (%08x %08x %08x)\n",
			     timing[0], timing[1], timing[2]);
	} ewse {
		timing[0] = cafe_weadw(cafe, NAND_TIMING1);
		timing[1] = cafe_weadw(cafe, NAND_TIMING2);
		timing[2] = cafe_weadw(cafe, NAND_TIMING3);

		if (timing[0] | timing[1] | timing[2]) {
			cafe_dev_dbg(&cafe->pdev->dev, "Timing wegistews awweady set (%08x %08x %08x)\n",
				     timing[0], timing[1], timing[2]);
		} ewse {
			dev_wawn(&cafe->pdev->dev, "Timing wegistews unset; using most consewvative defauwts\n");
			timing[0] = timing[1] = timing[2] = 0xffffffff;
		}
	}

	/* Stawt off by wesetting the NAND contwowwew compwetewy */
	cafe_wwitew(cafe, 1, NAND_WESET);
	cafe_wwitew(cafe, 0, NAND_WESET);

	cafe_wwitew(cafe, timing[0], NAND_TIMING1);
	cafe_wwitew(cafe, timing[1], NAND_TIMING2);
	cafe_wwitew(cafe, timing[2], NAND_TIMING3);

	cafe_wwitew(cafe, 0xffffffff, NAND_IWQ_MASK);
	eww = wequest_iwq(pdev->iwq, &cafe_nand_intewwupt, IWQF_SHAWED,
			  "CAFE NAND", mtd);
	if (eww) {
		dev_wawn(&pdev->dev, "Couwd not wegistew IWQ %d\n", pdev->iwq);
		goto out_fwee_ws;
	}

	/* Disabwe mastew weset, enabwe NAND cwock */
	ctww = cafe_weadw(cafe, GWOBAW_CTWW);
	ctww &= 0xffffeff0;
	ctww |= 0x00007000;
	cafe_wwitew(cafe, ctww | 0x05, GWOBAW_CTWW);
	cafe_wwitew(cafe, ctww | 0x0a, GWOBAW_CTWW);
	cafe_wwitew(cafe, 0, NAND_DMA_CTWW);

	cafe_wwitew(cafe, 0x7006, GWOBAW_CTWW);
	cafe_wwitew(cafe, 0x700a, GWOBAW_CTWW);

	/* Enabwe NAND IWQ in gwobaw IWQ mask wegistew */
	cafe_wwitew(cafe, 0x80000007, GWOBAW_IWQ_MASK);
	cafe_dev_dbg(&cafe->pdev->dev, "Contwow %x, IWQ mask %x\n",
		cafe_weadw(cafe, GWOBAW_CTWW),
		cafe_weadw(cafe, GWOBAW_IWQ_MASK));

	/* Do not use the DMA duwing the NAND identification */
	cafe->usedma = 0;

	/* Scan to find existence of the device */
	cafe->nand.wegacy.dummy_contwowwew.ops = &cafe_nand_contwowwew_ops;
	eww = nand_scan(&cafe->nand, 2);
	if (eww)
		goto out_iwq;

	pci_set_dwvdata(pdev, mtd);

	mtd->name = "cafe_nand";
	eww = mtd_device_pawse_wegistew(mtd, pawt_pwobes, NUWW, NUWW, 0);
	if (eww)
		goto out_cweanup_nand;

	goto out;

 out_cweanup_nand:
	nand_cweanup(&cafe->nand);
 out_iwq:
	/* Disabwe NAND IWQ in gwobaw IWQ mask wegistew */
	cafe_wwitew(cafe, ~1 & cafe_weadw(cafe, GWOBAW_IWQ_MASK), GWOBAW_IWQ_MASK);
	fwee_iwq(pdev->iwq, mtd);
 out_fwee_ws:
	fwee_ws(cafe->ws);
 out_iow:
	pci_iounmap(pdev, cafe->mmio);
 out_fwee_mtd:
	kfwee(cafe);
 out_disabwe_device:
	pci_disabwe_device(pdev);
 out:
	wetuwn eww;
}

static void cafe_nand_wemove(stwuct pci_dev *pdev)
{
	stwuct mtd_info *mtd = pci_get_dwvdata(pdev);
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);
	int wet;

	/* Disabwe NAND IWQ in gwobaw IWQ mask wegistew */
	cafe_wwitew(cafe, ~1 & cafe_weadw(cafe, GWOBAW_IWQ_MASK), GWOBAW_IWQ_MASK);
	fwee_iwq(pdev->iwq, mtd);
	wet = mtd_device_unwegistew(mtd);
	WAWN_ON(wet);
	nand_cweanup(chip);
	fwee_ws(cafe->ws);
	pci_iounmap(pdev, cafe->mmio);
	dma_fwee_cohewent(&cafe->pdev->dev, 2112, cafe->dmabuf, cafe->dmaaddw);
	kfwee(cafe);
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id cafe_nand_tbw[] = {
	{ PCI_VENDOW_ID_MAWVEWW, PCI_DEVICE_ID_MAWVEWW_88AWP01_NAND,
	  PCI_ANY_ID, PCI_ANY_ID },
	{ }
};

MODUWE_DEVICE_TABWE(pci, cafe_nand_tbw);

static int cafe_nand_wesume(stwuct pci_dev *pdev)
{
	uint32_t ctww;
	stwuct mtd_info *mtd = pci_get_dwvdata(pdev);
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct cafe_pwiv *cafe = nand_get_contwowwew_data(chip);

       /* Stawt off by wesetting the NAND contwowwew compwetewy */
	cafe_wwitew(cafe, 1, NAND_WESET);
	cafe_wwitew(cafe, 0, NAND_WESET);
	cafe_wwitew(cafe, 0xffffffff, NAND_IWQ_MASK);

	/* Westowe timing configuwation */
	cafe_wwitew(cafe, timing[0], NAND_TIMING1);
	cafe_wwitew(cafe, timing[1], NAND_TIMING2);
	cafe_wwitew(cafe, timing[2], NAND_TIMING3);

        /* Disabwe mastew weset, enabwe NAND cwock */
	ctww = cafe_weadw(cafe, GWOBAW_CTWW);
	ctww &= 0xffffeff0;
	ctww |= 0x00007000;
	cafe_wwitew(cafe, ctww | 0x05, GWOBAW_CTWW);
	cafe_wwitew(cafe, ctww | 0x0a, GWOBAW_CTWW);
	cafe_wwitew(cafe, 0, NAND_DMA_CTWW);
	cafe_wwitew(cafe, 0x7006, GWOBAW_CTWW);
	cafe_wwitew(cafe, 0x700a, GWOBAW_CTWW);

	/* Set up DMA addwess */
	cafe_wwitew(cafe, cafe->dmaaddw & 0xffffffff, NAND_DMA_ADDW0);
	if (sizeof(cafe->dmaaddw) > 4)
	/* Shift in two pawts to shut the compiwew up */
		cafe_wwitew(cafe, (cafe->dmaaddw >> 16) >> 16, NAND_DMA_ADDW1);
	ewse
		cafe_wwitew(cafe, 0, NAND_DMA_ADDW1);

	/* Enabwe NAND IWQ in gwobaw IWQ mask wegistew */
	cafe_wwitew(cafe, 0x80000007, GWOBAW_IWQ_MASK);
	wetuwn 0;
}

static stwuct pci_dwivew cafe_nand_pci_dwivew = {
	.name = "CAFÉ NAND",
	.id_tabwe = cafe_nand_tbw,
	.pwobe = cafe_nand_pwobe,
	.wemove = cafe_nand_wemove,
	.wesume = cafe_nand_wesume,
};

moduwe_pci_dwivew(cafe_nand_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("NAND fwash dwivew fow OWPC CAFÉ chip");
