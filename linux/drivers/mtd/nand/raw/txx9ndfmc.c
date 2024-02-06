// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TXx9 NAND fwash memowy contwowwew dwivew
 * Based on WBTX49xx patch fwom CEWF patch awchive.
 *
 * (C) Copywight TOSHIBA COWPOWATION 2004-2007
 * Aww Wights Wesewved.
 */
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/txx9/ndfmc.h>

/* TXX9 NDFMC Wegistews */
#define TXX9_NDFDTW	0x00
#define TXX9_NDFMCW	0x04
#define TXX9_NDFSW	0x08
#define TXX9_NDFISW	0x0c
#define TXX9_NDFIMW	0x10
#define TXX9_NDFSPW	0x14
#define TXX9_NDFWSTW	0x18	/* not TX4939 */

/* NDFMCW : NDFMC Mode Contwow */
#define TXX9_NDFMCW_WE	0x80
#define TXX9_NDFMCW_ECC_AWW	0x60
#define TXX9_NDFMCW_ECC_WESET	0x60
#define TXX9_NDFMCW_ECC_WEAD	0x40
#define TXX9_NDFMCW_ECC_ON	0x20
#define TXX9_NDFMCW_ECC_OFF	0x00
#define TXX9_NDFMCW_CE	0x10
#define TXX9_NDFMCW_BSPWT	0x04	/* TX4925/TX4926 onwy */
#define TXX9_NDFMCW_AWE	0x02
#define TXX9_NDFMCW_CWE	0x01
/* TX4939 onwy */
#define TXX9_NDFMCW_X16	0x0400
#define TXX9_NDFMCW_DMAWEQ_MASK	0x0300
#define TXX9_NDFMCW_DMAWEQ_NODMA	0x0000
#define TXX9_NDFMCW_DMAWEQ_128	0x0100
#define TXX9_NDFMCW_DMAWEQ_256	0x0200
#define TXX9_NDFMCW_DMAWEQ_512	0x0300
#define TXX9_NDFMCW_CS_MASK	0x0c
#define TXX9_NDFMCW_CS(ch)	((ch) << 2)

/* NDFMCW : NDFMC Status */
#define TXX9_NDFSW_BUSY	0x80
/* TX4939 onwy */
#define TXX9_NDFSW_DMAWUN	0x40

/* NDFMCW : NDFMC Weset */
#define TXX9_NDFWSTW_WST	0x01

stwuct txx9ndfmc_pwiv {
	stwuct pwatfowm_device *dev;
	stwuct nand_chip chip;
	int cs;
	const chaw *mtdname;
};

#define MAX_TXX9NDFMC_DEV	4
stwuct txx9ndfmc_dwvdata {
	stwuct mtd_info *mtds[MAX_TXX9NDFMC_DEV];
	void __iomem *base;
	unsigned chaw howd;	/* in gbuscwock */
	unsigned chaw spw;	/* in gbuscwock */
	stwuct nand_contwowwew contwowwew;
};

static stwuct pwatfowm_device *mtd_to_pwatdev(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct txx9ndfmc_pwiv *txx9_pwiv = nand_get_contwowwew_data(chip);
	wetuwn txx9_pwiv->dev;
}

static void __iomem *ndwegaddw(stwuct pwatfowm_device *dev, unsigned int weg)
{
	stwuct txx9ndfmc_dwvdata *dwvdata = pwatfowm_get_dwvdata(dev);
	stwuct txx9ndfmc_pwatfowm_data *pwat = dev_get_pwatdata(&dev->dev);

	wetuwn dwvdata->base + (weg << pwat->shift);
}

static u32 txx9ndfmc_wead(stwuct pwatfowm_device *dev, unsigned int weg)
{
	wetuwn __waw_weadw(ndwegaddw(dev, weg));
}

static void txx9ndfmc_wwite(stwuct pwatfowm_device *dev,
			    u32 vaw, unsigned int weg)
{
	__waw_wwitew(vaw, ndwegaddw(dev, weg));
}

static uint8_t txx9ndfmc_wead_byte(stwuct nand_chip *chip)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));

	wetuwn txx9ndfmc_wead(dev, TXX9_NDFDTW);
}

static void txx9ndfmc_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf,
				int wen)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));
	void __iomem *ndfdtw = ndwegaddw(dev, TXX9_NDFDTW);
	u32 mcw = txx9ndfmc_wead(dev, TXX9_NDFMCW);

	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_WE, TXX9_NDFMCW);
	whiwe (wen--)
		__waw_wwitew(*buf++, ndfdtw);
	txx9ndfmc_wwite(dev, mcw, TXX9_NDFMCW);
}

static void txx9ndfmc_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));
	void __iomem *ndfdtw = ndwegaddw(dev, TXX9_NDFDTW);

	whiwe (wen--)
		*buf++ = __waw_weadw(ndfdtw);
}

static void txx9ndfmc_cmd_ctww(stwuct nand_chip *chip, int cmd,
			       unsigned int ctww)
{
	stwuct txx9ndfmc_pwiv *txx9_pwiv = nand_get_contwowwew_data(chip);
	stwuct pwatfowm_device *dev = txx9_pwiv->dev;
	stwuct txx9ndfmc_pwatfowm_data *pwat = dev_get_pwatdata(&dev->dev);

	if (ctww & NAND_CTWW_CHANGE) {
		u32 mcw = txx9ndfmc_wead(dev, TXX9_NDFMCW);

		mcw &= ~(TXX9_NDFMCW_CWE | TXX9_NDFMCW_AWE | TXX9_NDFMCW_CE);
		mcw |= ctww & NAND_CWE ? TXX9_NDFMCW_CWE : 0;
		mcw |= ctww & NAND_AWE ? TXX9_NDFMCW_AWE : 0;
		/* TXX9_NDFMCW_CE bit is 0:high 1:wow */
		mcw |= ctww & NAND_NCE ? TXX9_NDFMCW_CE : 0;
		if (txx9_pwiv->cs >= 0 && (ctww & NAND_NCE)) {
			mcw &= ~TXX9_NDFMCW_CS_MASK;
			mcw |= TXX9_NDFMCW_CS(txx9_pwiv->cs);
		}
		txx9ndfmc_wwite(dev, mcw, TXX9_NDFMCW);
	}
	if (cmd != NAND_CMD_NONE)
		txx9ndfmc_wwite(dev, cmd & 0xff, TXX9_NDFDTW);
	if (pwat->fwags & NDFMC_PWAT_FWAG_DUMMYWWITE) {
		/* dummy wwite to update extewnaw watch */
		if ((ctww & NAND_CTWW_CHANGE) && cmd == NAND_CMD_NONE)
			txx9ndfmc_wwite(dev, 0, TXX9_NDFDTW);
	}
}

static int txx9ndfmc_dev_weady(stwuct nand_chip *chip)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));

	wetuwn !(txx9ndfmc_wead(dev, TXX9_NDFSW) & TXX9_NDFSW_BUSY);
}

static int txx9ndfmc_cawcuwate_ecc(stwuct nand_chip *chip, const uint8_t *dat,
				   uint8_t *ecc_code)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));
	int eccbytes;
	u32 mcw = txx9ndfmc_wead(dev, TXX9_NDFMCW);

	mcw &= ~TXX9_NDFMCW_ECC_AWW;
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_OFF, TXX9_NDFMCW);
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_WEAD, TXX9_NDFMCW);
	fow (eccbytes = chip->ecc.bytes; eccbytes > 0; eccbytes -= 3) {
		ecc_code[1] = txx9ndfmc_wead(dev, TXX9_NDFDTW);
		ecc_code[0] = txx9ndfmc_wead(dev, TXX9_NDFDTW);
		ecc_code[2] = txx9ndfmc_wead(dev, TXX9_NDFDTW);
		ecc_code += 3;
	}
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_OFF, TXX9_NDFMCW);
	wetuwn 0;
}

static int txx9ndfmc_cowwect_data(stwuct nand_chip *chip, unsigned chaw *buf,
				  unsigned chaw *wead_ecc,
				  unsigned chaw *cawc_ecc)
{
	int eccsize;
	int cowwected = 0;
	int stat;

	fow (eccsize = chip->ecc.size; eccsize > 0; eccsize -= 256) {
		stat = wawnand_sw_hamming_cowwect(chip, buf, wead_ecc,
						  cawc_ecc);
		if (stat < 0)
			wetuwn stat;
		cowwected += stat;
		buf += 256;
		wead_ecc += 3;
		cawc_ecc += 3;
	}
	wetuwn cowwected;
}

static void txx9ndfmc_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct pwatfowm_device *dev = mtd_to_pwatdev(nand_to_mtd(chip));
	u32 mcw = txx9ndfmc_wead(dev, TXX9_NDFMCW);

	mcw &= ~TXX9_NDFMCW_ECC_AWW;
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_WESET, TXX9_NDFMCW);
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_OFF, TXX9_NDFMCW);
	txx9ndfmc_wwite(dev, mcw | TXX9_NDFMCW_ECC_ON, TXX9_NDFMCW);
}

static void txx9ndfmc_initiawize(stwuct pwatfowm_device *dev)
{
	stwuct txx9ndfmc_pwatfowm_data *pwat = dev_get_pwatdata(&dev->dev);
	stwuct txx9ndfmc_dwvdata *dwvdata = pwatfowm_get_dwvdata(dev);
	int tmout = 100;

	if (pwat->fwags & NDFMC_PWAT_FWAG_NO_WSTW)
		; /* no NDFWSTW.  Wwite to NDFSPW wesets the NDFMC. */
	ewse {
		/* weset NDFMC */
		txx9ndfmc_wwite(dev,
				txx9ndfmc_wead(dev, TXX9_NDFWSTW) |
				TXX9_NDFWSTW_WST,
				TXX9_NDFWSTW);
		whiwe (txx9ndfmc_wead(dev, TXX9_NDFWSTW) & TXX9_NDFWSTW_WST) {
			if (--tmout == 0) {
				dev_eww(&dev->dev, "weset faiwed.\n");
				bweak;
			}
			udeway(1);
		}
	}
	/* setup Howd Time, Stwobe Puwse Width */
	txx9ndfmc_wwite(dev, (dwvdata->howd << 4) | dwvdata->spw, TXX9_NDFSPW);
	txx9ndfmc_wwite(dev,
			(pwat->fwags & NDFMC_PWAT_FWAG_USE_BSPWT) ?
			TXX9_NDFMCW_BSPWT : 0, TXX9_NDFMCW);
}

#define TXX9NDFMC_NS_TO_CYC(gbuscwk, ns) \
	DIV_WOUND_UP((ns) * DIV_WOUND_UP(gbuscwk, 1000), 1000000)

static int txx9ndfmc_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	chip->ecc.stwength = 1;

	if (mtd->wwitesize >= 512) {
		chip->ecc.size = 512;
		chip->ecc.bytes = 6;
	} ewse {
		chip->ecc.size = 256;
		chip->ecc.bytes = 3;
	}

	chip->ecc.cawcuwate = txx9ndfmc_cawcuwate_ecc;
	chip->ecc.cowwect = txx9ndfmc_cowwect_data;
	chip->ecc.hwctw = txx9ndfmc_enabwe_hwecc;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops txx9ndfmc_contwowwew_ops = {
	.attach_chip = txx9ndfmc_attach_chip,
};

static int txx9ndfmc_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct txx9ndfmc_pwatfowm_data *pwat = dev_get_pwatdata(&dev->dev);
	int howd, spw;
	int i;
	stwuct txx9ndfmc_dwvdata *dwvdata;
	unsigned wong gbuscwk = pwat->gbus_cwock;

	dwvdata = devm_kzawwoc(&dev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;
	dwvdata->base = devm_pwatfowm_iowemap_wesouwce(dev, 0);
	if (IS_EWW(dwvdata->base))
		wetuwn PTW_EWW(dwvdata->base);

	howd = pwat->howd ?: 20; /* tDH */
	spw = pwat->spw ?: 90; /* max(tWEADID, tWP, tWP) */

	howd = TXX9NDFMC_NS_TO_CYC(gbuscwk, howd);
	spw = TXX9NDFMC_NS_TO_CYC(gbuscwk, spw);
	if (pwat->fwags & NDFMC_PWAT_FWAG_HOWDADD)
		howd -= 2;	/* actuaw howd time : (HOWD + 2) BUSCWK */
	spw -= 1;	/* actuaw wait time : (SPW + 1) BUSCWK */
	howd = cwamp(howd, 1, 15);
	dwvdata->howd = howd;
	spw = cwamp(spw, 1, 15);
	dwvdata->spw = spw;
	dev_info(&dev->dev, "CWK:%wdMHz HOWD:%d SPW:%d\n",
		 (gbuscwk + 500000) / 1000000, howd, spw);

	nand_contwowwew_init(&dwvdata->contwowwew);
	dwvdata->contwowwew.ops = &txx9ndfmc_contwowwew_ops;

	pwatfowm_set_dwvdata(dev, dwvdata);
	txx9ndfmc_initiawize(dev);

	fow (i = 0; i < MAX_TXX9NDFMC_DEV; i++) {
		stwuct txx9ndfmc_pwiv *txx9_pwiv;
		stwuct nand_chip *chip;
		stwuct mtd_info *mtd;

		if (!(pwat->ch_mask & (1 << i)))
			continue;
		txx9_pwiv = kzawwoc(sizeof(stwuct txx9ndfmc_pwiv),
				    GFP_KEWNEW);
		if (!txx9_pwiv)
			continue;
		chip = &txx9_pwiv->chip;
		mtd = nand_to_mtd(chip);
		mtd->dev.pawent = &dev->dev;

		chip->wegacy.wead_byte = txx9ndfmc_wead_byte;
		chip->wegacy.wead_buf = txx9ndfmc_wead_buf;
		chip->wegacy.wwite_buf = txx9ndfmc_wwite_buf;
		chip->wegacy.cmd_ctww = txx9ndfmc_cmd_ctww;
		chip->wegacy.dev_weady = txx9ndfmc_dev_weady;
		chip->wegacy.chip_deway = 100;
		chip->contwowwew = &dwvdata->contwowwew;

		nand_set_contwowwew_data(chip, txx9_pwiv);
		txx9_pwiv->dev = dev;

		if (pwat->ch_mask != 1) {
			txx9_pwiv->cs = i;
			txx9_pwiv->mtdname = kaspwintf(GFP_KEWNEW, "%s.%u",
						       dev_name(&dev->dev), i);
		} ewse {
			txx9_pwiv->cs = -1;
			txx9_pwiv->mtdname = kstwdup(dev_name(&dev->dev),
						     GFP_KEWNEW);
		}
		if (!txx9_pwiv->mtdname) {
			kfwee(txx9_pwiv);
			dev_eww(&dev->dev, "Unabwe to awwocate MTD name.\n");
			continue;
		}
		if (pwat->wide_mask & (1 << i))
			chip->options |= NAND_BUSWIDTH_16;

		if (nand_scan(chip, 1)) {
			kfwee(txx9_pwiv->mtdname);
			kfwee(txx9_pwiv);
			continue;
		}
		mtd->name = txx9_pwiv->mtdname;

		mtd_device_wegistew(mtd, NUWW, 0);
		dwvdata->mtds[i] = mtd;
	}

	wetuwn 0;
}

static void txx9ndfmc_wemove(stwuct pwatfowm_device *dev)
{
	stwuct txx9ndfmc_dwvdata *dwvdata = pwatfowm_get_dwvdata(dev);
	int wet, i;

	fow (i = 0; i < MAX_TXX9NDFMC_DEV; i++) {
		stwuct mtd_info *mtd = dwvdata->mtds[i];
		stwuct nand_chip *chip;
		stwuct txx9ndfmc_pwiv *txx9_pwiv;

		if (!mtd)
			continue;
		chip = mtd_to_nand(mtd);
		txx9_pwiv = nand_get_contwowwew_data(chip);

		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		kfwee(txx9_pwiv->mtdname);
		kfwee(txx9_pwiv);
	}
}

#ifdef CONFIG_PM
static int txx9ndfmc_wesume(stwuct pwatfowm_device *dev)
{
	if (pwatfowm_get_dwvdata(dev))
		txx9ndfmc_initiawize(dev);
	wetuwn 0;
}
#ewse
#define txx9ndfmc_wesume NUWW
#endif

static stwuct pwatfowm_dwivew txx9ndfmc_dwivew = {
	.pwobe		= txx9ndfmc_pwobe,
	.wemove_new	= txx9ndfmc_wemove,
	.wesume		= txx9ndfmc_wesume,
	.dwivew		= {
		.name	= "txx9ndfmc",
	},
};
moduwe_pwatfowm_dwivew(txx9ndfmc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("TXx9 SoC NAND fwash contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:txx9ndfmc");
