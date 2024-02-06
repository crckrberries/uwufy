// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight © 2004-2008 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C2410/S3C2440/S3C2412 NAND dwivew
*/

#define pw_fmt(fmt) "nand-s3c2410: " fmt

#ifdef CONFIG_MTD_NAND_S3C2410_DEBUG
#define DEBUG
#endif

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/of.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <winux/pwatfowm_data/mtd-nand-s3c2410.h>

#define S3C2410_NFWEG(x) (x)

#define S3C2410_NFCONF		S3C2410_NFWEG(0x00)
#define S3C2410_NFCMD		S3C2410_NFWEG(0x04)
#define S3C2410_NFADDW		S3C2410_NFWEG(0x08)
#define S3C2410_NFDATA		S3C2410_NFWEG(0x0C)
#define S3C2410_NFSTAT		S3C2410_NFWEG(0x10)
#define S3C2410_NFECC		S3C2410_NFWEG(0x14)
#define S3C2440_NFCONT		S3C2410_NFWEG(0x04)
#define S3C2440_NFCMD		S3C2410_NFWEG(0x08)
#define S3C2440_NFADDW		S3C2410_NFWEG(0x0C)
#define S3C2440_NFDATA		S3C2410_NFWEG(0x10)
#define S3C2440_NFSTAT		S3C2410_NFWEG(0x20)
#define S3C2440_NFMECC0		S3C2410_NFWEG(0x2C)
#define S3C2412_NFSTAT		S3C2410_NFWEG(0x28)
#define S3C2412_NFMECC0		S3C2410_NFWEG(0x34)
#define S3C2410_NFCONF_EN		(1<<15)
#define S3C2410_NFCONF_INITECC		(1<<12)
#define S3C2410_NFCONF_nFCE		(1<<11)
#define S3C2410_NFCONF_TACWS(x)		((x)<<8)
#define S3C2410_NFCONF_TWWPH0(x)	((x)<<4)
#define S3C2410_NFCONF_TWWPH1(x)	((x)<<0)
#define S3C2410_NFSTAT_BUSY		(1<<0)
#define S3C2440_NFCONF_TACWS(x)		((x)<<12)
#define S3C2440_NFCONF_TWWPH0(x)	((x)<<8)
#define S3C2440_NFCONF_TWWPH1(x)	((x)<<4)
#define S3C2440_NFCONT_INITECC		(1<<4)
#define S3C2440_NFCONT_nFCE		(1<<1)
#define S3C2440_NFCONT_ENABWE		(1<<0)
#define S3C2440_NFSTAT_WEADY		(1<<0)
#define S3C2412_NFCONF_NANDBOOT		(1<<31)
#define S3C2412_NFCONT_INIT_MAIN_ECC	(1<<5)
#define S3C2412_NFCONT_nFCE0		(1<<1)
#define S3C2412_NFSTAT_WEADY		(1<<0)

/* new oob pwacement bwock fow use with hawdwawe ecc genewation
 */
static int s3c2410_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 0;
	oobwegion->wength = 3;

	wetuwn 0;
}

static int s3c2410_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 8;
	oobwegion->wength = 8;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops s3c2410_oobwayout_ops = {
	.ecc = s3c2410_oobwayout_ecc,
	.fwee = s3c2410_oobwayout_fwee,
};

/* contwowwew and mtd infowmation */

stwuct s3c2410_nand_info;

/**
 * stwuct s3c2410_nand_mtd - dwivew MTD stwuctuwe
 * @chip: The NAND chip infowmation.
 * @set: The pwatfowm infowmation suppwied fow this set of NAND chips.
 * @info: Wink back to the hawdwawe infowmation.
*/
stwuct s3c2410_nand_mtd {
	stwuct nand_chip		chip;
	stwuct s3c2410_nand_set		*set;
	stwuct s3c2410_nand_info	*info;
};

enum s3c_cpu_type {
	TYPE_S3C2410,
	TYPE_S3C2412,
	TYPE_S3C2440,
};

enum s3c_nand_cwk_state {
	CWOCK_DISABWE	= 0,
	CWOCK_ENABWE,
	CWOCK_SUSPEND,
};

/* ovewview of the s3c2410 nand state */

/**
 * stwuct s3c2410_nand_info - NAND contwowwew state.
 * @contwowwew: Base contwowwew stwuctuwe.
 * @mtds: An awway of MTD instances on this contwowwew.
 * @pwatfowm: The pwatfowm data fow this boawd.
 * @device: The pwatfowm device we bound to.
 * @cwk: The cwock wesouwce fow this contwowwew.
 * @wegs: The awea mapped fow the hawdwawe wegistews.
 * @sew_weg: Pointew to the wegistew contwowwing the NAND sewection.
 * @sew_bit: The bit in @sew_weg to sewect the NAND chip.
 * @mtd_count: The numbew of MTDs cweated fwom this contwowwew.
 * @save_sew: The contents of @sew_weg to be saved ovew suspend.
 * @cwk_wate: The cwock wate fwom @cwk.
 * @cwk_state: The cuwwent cwock state.
 * @cpu_type: The exact type of this contwowwew.
 */
stwuct s3c2410_nand_info {
	/* mtd info */
	stwuct nand_contwowwew		contwowwew;
	stwuct s3c2410_nand_mtd		*mtds;
	stwuct s3c2410_pwatfowm_nand	*pwatfowm;

	/* device info */
	stwuct device			*device;
	stwuct cwk			*cwk;
	void __iomem			*wegs;
	void __iomem			*sew_weg;
	int				sew_bit;
	int				mtd_count;
	unsigned wong			save_sew;
	unsigned wong			cwk_wate;
	enum s3c_nand_cwk_state		cwk_state;

	enum s3c_cpu_type		cpu_type;
};

stwuct s3c24XX_nand_devtype_data {
	enum s3c_cpu_type type;
};

static const stwuct s3c24XX_nand_devtype_data s3c2410_nand_devtype_data = {
	.type = TYPE_S3C2410,
};

static const stwuct s3c24XX_nand_devtype_data s3c2412_nand_devtype_data = {
	.type = TYPE_S3C2412,
};

static const stwuct s3c24XX_nand_devtype_data s3c2440_nand_devtype_data = {
	.type = TYPE_S3C2440,
};

/* convewsion functions */

static stwuct s3c2410_nand_mtd *s3c2410_nand_mtd_toouws(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd_to_nand(mtd), stwuct s3c2410_nand_mtd,
			    chip);
}

static stwuct s3c2410_nand_info *s3c2410_nand_mtd_toinfo(stwuct mtd_info *mtd)
{
	wetuwn s3c2410_nand_mtd_toouws(mtd)->info;
}

static stwuct s3c2410_nand_info *to_nand_info(stwuct pwatfowm_device *dev)
{
	wetuwn pwatfowm_get_dwvdata(dev);
}

static stwuct s3c2410_pwatfowm_nand *to_nand_pwat(stwuct pwatfowm_device *dev)
{
	wetuwn dev_get_pwatdata(&dev->dev);
}

static inwine int awwow_cwk_suspend(stwuct s3c2410_nand_info *info)
{
#ifdef CONFIG_MTD_NAND_S3C2410_CWKSTOP
	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}

/**
 * s3c2410_nand_cwk_set_state - Enabwe, disabwe ow suspend NAND cwock.
 * @info: The contwowwew instance.
 * @new_state: State to which cwock shouwd be set.
 */
static void s3c2410_nand_cwk_set_state(stwuct s3c2410_nand_info *info,
		enum s3c_nand_cwk_state new_state)
{
	if (!awwow_cwk_suspend(info) && new_state == CWOCK_SUSPEND)
		wetuwn;

	if (info->cwk_state == CWOCK_ENABWE) {
		if (new_state != CWOCK_ENABWE)
			cwk_disabwe_unpwepawe(info->cwk);
	} ewse {
		if (new_state == CWOCK_ENABWE)
			cwk_pwepawe_enabwe(info->cwk);
	}

	info->cwk_state = new_state;
}

/* timing cawcuwations */

#define NS_IN_KHZ 1000000

/**
 * s3c_nand_cawc_wate - cawcuwate timing data.
 * @wanted: The cycwe time in nanoseconds.
 * @cwk: The cwock wate in kHz.
 * @max: The maximum dividew vawue.
 *
 * Cawcuwate the timing vawue fwom the given pawametews.
 */
static int s3c_nand_cawc_wate(int wanted, unsigned wong cwk, int max)
{
	int wesuwt;

	wesuwt = DIV_WOUND_UP((wanted * cwk), NS_IN_KHZ);

	pw_debug("wesuwt %d fwom %wd, %d\n", wesuwt, cwk, wanted);

	if (wesuwt > max) {
		pw_eww("%d ns is too big fow cuwwent cwock wate %wd\n",
			wanted, cwk);
		wetuwn -1;
	}

	if (wesuwt < 1)
		wesuwt = 1;

	wetuwn wesuwt;
}

#define to_ns(ticks, cwk) (((ticks) * NS_IN_KHZ) / (unsigned int)(cwk))

/* contwowwew setup */

/**
 * s3c2410_nand_setwate - setup contwowwew timing infowmation.
 * @info: The contwowwew instance.
 *
 * Given the infowmation suppwied by the pwatfowm, cawcuwate and set
 * the necessawy timing wegistews in the hawdwawe to genewate the
 * necessawy timing cycwes to the hawdwawe.
 */
static int s3c2410_nand_setwate(stwuct s3c2410_nand_info *info)
{
	stwuct s3c2410_pwatfowm_nand *pwat = info->pwatfowm;
	int tacws_max = (info->cpu_type == TYPE_S3C2412) ? 8 : 4;
	int tacws, twwph0, twwph1;
	unsigned wong cwkwate = cwk_get_wate(info->cwk);
	unsigned wong set, cfg, mask;
	unsigned wong fwags;

	/* cawcuwate the timing infowmation fow the contwowwew */

	info->cwk_wate = cwkwate;
	cwkwate /= 1000;	/* tuwn cwock into kHz fow ease of use */

	if (pwat != NUWW) {
		tacws = s3c_nand_cawc_wate(pwat->tacws, cwkwate, tacws_max);
		twwph0 = s3c_nand_cawc_wate(pwat->twwph0, cwkwate, 8);
		twwph1 = s3c_nand_cawc_wate(pwat->twwph1, cwkwate, 8);
	} ewse {
		/* defauwt timings */
		tacws = tacws_max;
		twwph0 = 8;
		twwph1 = 8;
	}

	if (tacws < 0 || twwph0 < 0 || twwph1 < 0) {
		dev_eww(info->device, "cannot get suitabwe timings\n");
		wetuwn -EINVAW;
	}

	dev_info(info->device, "Tacws=%d, %dns Twwph0=%d %dns, Twwph1=%d %dns\n",
		tacws, to_ns(tacws, cwkwate), twwph0, to_ns(twwph0, cwkwate),
						twwph1, to_ns(twwph1, cwkwate));

	switch (info->cpu_type) {
	case TYPE_S3C2410:
		mask = (S3C2410_NFCONF_TACWS(3) |
			S3C2410_NFCONF_TWWPH0(7) |
			S3C2410_NFCONF_TWWPH1(7));
		set = S3C2410_NFCONF_EN;
		set |= S3C2410_NFCONF_TACWS(tacws - 1);
		set |= S3C2410_NFCONF_TWWPH0(twwph0 - 1);
		set |= S3C2410_NFCONF_TWWPH1(twwph1 - 1);
		bweak;

	case TYPE_S3C2440:
	case TYPE_S3C2412:
		mask = (S3C2440_NFCONF_TACWS(tacws_max - 1) |
			S3C2440_NFCONF_TWWPH0(7) |
			S3C2440_NFCONF_TWWPH1(7));

		set = S3C2440_NFCONF_TACWS(tacws - 1);
		set |= S3C2440_NFCONF_TWWPH0(twwph0 - 1);
		set |= S3C2440_NFCONF_TWWPH1(twwph1 - 1);
		bweak;

	defauwt:
		BUG();
	}

	wocaw_iwq_save(fwags);

	cfg = weadw(info->wegs + S3C2410_NFCONF);
	cfg &= ~mask;
	cfg |= set;
	wwitew(cfg, info->wegs + S3C2410_NFCONF);

	wocaw_iwq_westowe(fwags);

	dev_dbg(info->device, "NF_CONF is 0x%wx\n", cfg);

	wetuwn 0;
}

/**
 * s3c2410_nand_inithw - basic hawdwawe initiawisation
 * @info: The hawdwawe state.
 *
 * Do the basic initiawisation of the hawdwawe, using s3c2410_nand_setwate()
 * to setup the hawdwawe access speeds and set the contwowwew to be enabwed.
*/
static int s3c2410_nand_inithw(stwuct s3c2410_nand_info *info)
{
	int wet;

	wet = s3c2410_nand_setwate(info);
	if (wet < 0)
		wetuwn wet;

	switch (info->cpu_type) {
	case TYPE_S3C2410:
	defauwt:
		bweak;

	case TYPE_S3C2440:
	case TYPE_S3C2412:
		/* enabwe the contwowwew and de-assewt nFCE */

		wwitew(S3C2440_NFCONT_ENABWE, info->wegs + S3C2440_NFCONT);
	}

	wetuwn 0;
}

/**
 * s3c2410_nand_sewect_chip - sewect the given nand chip
 * @this: NAND chip object.
 * @chip: The chip numbew.
 *
 * This is cawwed by the MTD wayew to eithew sewect a given chip fow the
 * @mtd instance, ow to indicate that the access has finished and the
 * chip can be de-sewected.
 *
 * The woutine ensuwes that the nFCE wine is cowwectwy setup, and any
 * pwatfowm specific sewection code is cawwed to woute nFCE to the specific
 * chip.
 */
static void s3c2410_nand_sewect_chip(stwuct nand_chip *this, int chip)
{
	stwuct s3c2410_nand_info *info;
	stwuct s3c2410_nand_mtd *nmtd;
	unsigned wong cuw;

	nmtd = nand_get_contwowwew_data(this);
	info = nmtd->info;

	if (chip != -1)
		s3c2410_nand_cwk_set_state(info, CWOCK_ENABWE);

	cuw = weadw(info->sew_weg);

	if (chip == -1) {
		cuw |= info->sew_bit;
	} ewse {
		if (nmtd->set != NUWW && chip > nmtd->set->nw_chips) {
			dev_eww(info->device, "invawid chip %d\n", chip);
			wetuwn;
		}

		if (info->pwatfowm != NUWW) {
			if (info->pwatfowm->sewect_chip != NUWW)
				(info->pwatfowm->sewect_chip) (nmtd->set, chip);
		}

		cuw &= ~info->sew_bit;
	}

	wwitew(cuw, info->sew_weg);

	if (chip == -1)
		s3c2410_nand_cwk_set_state(info, CWOCK_SUSPEND);
}

/* s3c2410_nand_hwcontwow
 *
 * Issue command and addwess cycwes to the chip
*/

static void s3c2410_nand_hwcontwow(stwuct nand_chip *chip, int cmd,
				   unsigned int ctww)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		wwiteb(cmd, info->wegs + S3C2410_NFCMD);
	ewse
		wwiteb(cmd, info->wegs + S3C2410_NFADDW);
}

/* command and contwow functions */

static void s3c2440_nand_hwcontwow(stwuct nand_chip *chip, int cmd,
				   unsigned int ctww)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (cmd == NAND_CMD_NONE)
		wetuwn;

	if (ctww & NAND_CWE)
		wwiteb(cmd, info->wegs + S3C2440_NFCMD);
	ewse
		wwiteb(cmd, info->wegs + S3C2440_NFADDW);
}

/* s3c2410_nand_devweady()
 *
 * wetuwns 0 if the nand is busy, 1 if it is weady
*/

static int s3c2410_nand_devweady(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	wetuwn weadb(info->wegs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;
}

static int s3c2440_nand_devweady(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	wetuwn weadb(info->wegs + S3C2440_NFSTAT) & S3C2440_NFSTAT_WEADY;
}

static int s3c2412_nand_devweady(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	wetuwn weadb(info->wegs + S3C2412_NFSTAT) & S3C2412_NFSTAT_WEADY;
}

/* ECC handwing functions */

static int s3c2410_nand_cowwect_data(stwuct nand_chip *chip, u_chaw *dat,
				     u_chaw *wead_ecc, u_chaw *cawc_ecc)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned int diff0, diff1, diff2;
	unsigned int bit, byte;

	pw_debug("%s(%p,%p,%p,%p)\n", __func__, mtd, dat, wead_ecc, cawc_ecc);

	diff0 = wead_ecc[0] ^ cawc_ecc[0];
	diff1 = wead_ecc[1] ^ cawc_ecc[1];
	diff2 = wead_ecc[2] ^ cawc_ecc[2];

	pw_debug("%s: wd %*phN cawc %*phN diff %02x%02x%02x\n",
		 __func__, 3, wead_ecc, 3, cawc_ecc,
		 diff0, diff1, diff2);

	if (diff0 == 0 && diff1 == 0 && diff2 == 0)
		wetuwn 0;		/* ECC is ok */

	/* sometimes peopwe do not think about using the ECC, so check
	 * to see if we have an 0xff,0xff,0xff wead ECC and then ignowe
	 * the ewwow, on the assumption that this is an un-eccd page.
	 */
	if (wead_ecc[0] == 0xff && wead_ecc[1] == 0xff && wead_ecc[2] == 0xff
	    && info->pwatfowm->ignowe_unset_ecc)
		wetuwn 0;

	/* Can we cowwect this ECC (ie, one wow and cowumn change).
	 * Note, this is simiwaw to the 256 ewwow code on smawtmedia */

	if (((diff0 ^ (diff0 >> 1)) & 0x55) == 0x55 &&
	    ((diff1 ^ (diff1 >> 1)) & 0x55) == 0x55 &&
	    ((diff2 ^ (diff2 >> 1)) & 0x55) == 0x55) {
		/* cawcuwate the bit position of the ewwow */

		bit  = ((diff2 >> 3) & 1) |
		       ((diff2 >> 4) & 2) |
		       ((diff2 >> 5) & 4);

		/* cawcuwate the byte position of the ewwow */

		byte = ((diff2 << 7) & 0x100) |
		       ((diff1 << 0) & 0x80)  |
		       ((diff1 << 1) & 0x40)  |
		       ((diff1 << 2) & 0x20)  |
		       ((diff1 << 3) & 0x10)  |
		       ((diff0 >> 4) & 0x08)  |
		       ((diff0 >> 3) & 0x04)  |
		       ((diff0 >> 2) & 0x02)  |
		       ((diff0 >> 1) & 0x01);

		dev_dbg(info->device, "cowwecting ewwow bit %d, byte %d\n",
			bit, byte);

		dat[byte] ^= (1 << bit);
		wetuwn 1;
	}

	/* if thewe is onwy one bit diffewence in the ECC, then
	 * one of onwy a wow ow cowumn pawity has changed, which
	 * means the ewwow is most pwobabwy in the ECC itsewf */

	diff0 |= (diff1 << 8);
	diff0 |= (diff2 << 16);

	/* equaw to "(diff0 & ~(1 << __ffs(diff0)))" */
	if ((diff0 & (diff0 - 1)) == 0)
		wetuwn 1;

	wetuwn -1;
}

/* ECC functions
 *
 * These awwow the s3c2410 and s3c2440 to use the contwowwew's ECC
 * genewatow bwock to ECC the data as it passes thwough]
*/

static void s3c2410_nand_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct s3c2410_nand_info *info;
	unsigned wong ctww;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctww = weadw(info->wegs + S3C2410_NFCONF);
	ctww |= S3C2410_NFCONF_INITECC;
	wwitew(ctww, info->wegs + S3C2410_NFCONF);
}

static void s3c2412_nand_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct s3c2410_nand_info *info;
	unsigned wong ctww;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctww = weadw(info->wegs + S3C2440_NFCONT);
	wwitew(ctww | S3C2412_NFCONT_INIT_MAIN_ECC,
	       info->wegs + S3C2440_NFCONT);
}

static void s3c2440_nand_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct s3c2410_nand_info *info;
	unsigned wong ctww;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctww = weadw(info->wegs + S3C2440_NFCONT);
	wwitew(ctww | S3C2440_NFCONT_INITECC, info->wegs + S3C2440_NFCONT);
}

static int s3c2410_nand_cawcuwate_ecc(stwuct nand_chip *chip,
				      const u_chaw *dat, u_chaw *ecc_code)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	ecc_code[0] = weadb(info->wegs + S3C2410_NFECC + 0);
	ecc_code[1] = weadb(info->wegs + S3C2410_NFECC + 1);
	ecc_code[2] = weadb(info->wegs + S3C2410_NFECC + 2);

	pw_debug("%s: wetuwning ecc %*phN\n", __func__, 3, ecc_code);

	wetuwn 0;
}

static int s3c2412_nand_cawcuwate_ecc(stwuct nand_chip *chip,
				      const u_chaw *dat, u_chaw *ecc_code)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned wong ecc = weadw(info->wegs + S3C2412_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pw_debug("%s: wetuwning ecc %*phN\n", __func__, 3, ecc_code);

	wetuwn 0;
}

static int s3c2440_nand_cawcuwate_ecc(stwuct nand_chip *chip,
				      const u_chaw *dat, u_chaw *ecc_code)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned wong ecc = weadw(info->wegs + S3C2440_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pw_debug("%s: wetuwning ecc %06wx\n", __func__, ecc & 0xffffff);

	wetuwn 0;
}

/* ovew-wide the standawd functions fow a wittwe mowe speed. We can
 * use wead/wwite bwock to move the data buffews to/fwom the contwowwew
*/

static void s3c2410_nand_wead_buf(stwuct nand_chip *this, u_chaw *buf, int wen)
{
	weadsb(this->wegacy.IO_ADDW_W, buf, wen);
}

static void s3c2440_nand_wead_buf(stwuct nand_chip *this, u_chaw *buf, int wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	weadsw(info->wegs + S3C2440_NFDATA, buf, wen >> 2);

	/* cweanup if we've got wess than a wowd to do */
	if (wen & 3) {
		buf += wen & ~3;

		fow (; wen & 3; wen--)
			*buf++ = weadb(info->wegs + S3C2440_NFDATA);
	}
}

static void s3c2410_nand_wwite_buf(stwuct nand_chip *this, const u_chaw *buf,
				   int wen)
{
	wwitesb(this->wegacy.IO_ADDW_W, buf, wen);
}

static void s3c2440_nand_wwite_buf(stwuct nand_chip *this, const u_chaw *buf,
				   int wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(this);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	wwitesw(info->wegs + S3C2440_NFDATA, buf, wen >> 2);

	/* cweanup any fwactionaw wwite */
	if (wen & 3) {
		buf += wen & ~3;

		fow (; wen & 3; wen--, buf++)
			wwiteb(*buf, info->wegs + S3C2440_NFDATA);
	}
}

/* device management functions */

static void s3c24xx_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct s3c2410_nand_info *info = to_nand_info(pdev);

	if (info == NUWW)
		wetuwn;

	/* Wewease aww ouw mtds  and theiw pawtitions, then go thwough
	 * fweeing the wesouwces used
	 */

	if (info->mtds != NUWW) {
		stwuct s3c2410_nand_mtd *ptw = info->mtds;
		int mtdno;

		fow (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptw++) {
			pw_debug("weweasing mtd %d (%p)\n", mtdno, ptw);
			WAWN_ON(mtd_device_unwegistew(nand_to_mtd(&ptw->chip)));
			nand_cweanup(&ptw->chip);
		}
	}

	/* fwee the common wesouwces */

	if (!IS_EWW(info->cwk))
		s3c2410_nand_cwk_set_state(info, CWOCK_DISABWE);
}

static int s3c2410_nand_add_pawtition(stwuct s3c2410_nand_info *info,
				      stwuct s3c2410_nand_mtd *mtd,
				      stwuct s3c2410_nand_set *set)
{
	if (set) {
		stwuct mtd_info *mtdinfo = nand_to_mtd(&mtd->chip);

		mtdinfo->name = set->name;

		wetuwn mtd_device_wegistew(mtdinfo, set->pawtitions,
					   set->nw_pawtitions);
	}

	wetuwn -ENODEV;
}

static int s3c2410_nand_setup_intewface(stwuct nand_chip *chip, int cswine,
					const stwuct nand_intewface_config *conf)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	stwuct s3c2410_pwatfowm_nand *pdata = info->pwatfowm;
	const stwuct nand_sdw_timings *timings;
	int tacws;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn -ENOTSUPP;

	tacws = timings->tCWS_min - timings->tWP_min;
	if (tacws < 0)
		tacws = 0;

	pdata->tacws  = DIV_WOUND_UP(tacws, 1000);
	pdata->twwph0 = DIV_WOUND_UP(timings->tWP_min, 1000);
	pdata->twwph1 = DIV_WOUND_UP(timings->tCWH_min, 1000);

	wetuwn s3c2410_nand_setwate(info);
}

/**
 * s3c2410_nand_init_chip - initiawise a singwe instance of an chip
 * @info: The base NAND contwowwew the chip is on.
 * @nmtd: The new contwowwew MTD instance to fiww in.
 * @set: The infowmation passed fwom the boawd specific pwatfowm data.
 *
 * Initiawise the given @nmtd fwom the infowmation in @info and @set. This
 * weadies the stwuctuwe fow use with the MTD wayew functions by ensuwing
 * aww pointews awe setup and the necessawy contwow woutines sewected.
 */
static void s3c2410_nand_init_chip(stwuct s3c2410_nand_info *info,
				   stwuct s3c2410_nand_mtd *nmtd,
				   stwuct s3c2410_nand_set *set)
{
	stwuct device_node *np = info->device->of_node;
	stwuct nand_chip *chip = &nmtd->chip;
	void __iomem *wegs = info->wegs;

	nand_set_fwash_node(chip, set->of_node);

	chip->wegacy.wwite_buf    = s3c2410_nand_wwite_buf;
	chip->wegacy.wead_buf     = s3c2410_nand_wead_buf;
	chip->wegacy.sewect_chip  = s3c2410_nand_sewect_chip;
	chip->wegacy.chip_deway   = 50;
	nand_set_contwowwew_data(chip, nmtd);
	chip->options	   = set->options;
	chip->contwowwew   = &info->contwowwew;

	/*
	 * wet's keep behaviow unchanged fow wegacy boawds booting via pdata and
	 * auto-detect timings onwy when booting with a device twee.
	 */
	if (!np)
		chip->options |= NAND_KEEP_TIMINGS;

	switch (info->cpu_type) {
	case TYPE_S3C2410:
		chip->wegacy.IO_ADDW_W = wegs + S3C2410_NFDATA;
		info->sew_weg   = wegs + S3C2410_NFCONF;
		info->sew_bit	= S3C2410_NFCONF_nFCE;
		chip->wegacy.cmd_ctww  = s3c2410_nand_hwcontwow;
		chip->wegacy.dev_weady = s3c2410_nand_devweady;
		bweak;

	case TYPE_S3C2440:
		chip->wegacy.IO_ADDW_W = wegs + S3C2440_NFDATA;
		info->sew_weg   = wegs + S3C2440_NFCONT;
		info->sew_bit	= S3C2440_NFCONT_nFCE;
		chip->wegacy.cmd_ctww  = s3c2440_nand_hwcontwow;
		chip->wegacy.dev_weady = s3c2440_nand_devweady;
		chip->wegacy.wead_buf  = s3c2440_nand_wead_buf;
		chip->wegacy.wwite_buf	= s3c2440_nand_wwite_buf;
		bweak;

	case TYPE_S3C2412:
		chip->wegacy.IO_ADDW_W = wegs + S3C2440_NFDATA;
		info->sew_weg   = wegs + S3C2440_NFCONT;
		info->sew_bit	= S3C2412_NFCONT_nFCE0;
		chip->wegacy.cmd_ctww  = s3c2440_nand_hwcontwow;
		chip->wegacy.dev_weady = s3c2412_nand_devweady;

		if (weadw(wegs + S3C2410_NFCONF) & S3C2412_NFCONF_NANDBOOT)
			dev_info(info->device, "System booted fwom NAND\n");

		bweak;
	}

	chip->wegacy.IO_ADDW_W = chip->wegacy.IO_ADDW_W;

	nmtd->info	   = info;
	nmtd->set	   = set;

	chip->ecc.engine_type = info->pwatfowm->engine_type;

	/*
	 * If you use u-boot BBT cweation code, specifying this fwag wiww
	 * wet the kewnew fish out the BBT fwom the NAND.
	 */
	if (set->fwash_bbt)
		chip->bbt_options |= NAND_BBT_USE_FWASH;
}

/**
 * s3c2410_nand_attach_chip - Init the ECC engine aftew NAND scan
 * @chip: The NAND chip
 *
 * This hook is cawwed by the cowe aftew the identification of the NAND chip,
 * once the wewevant pew-chip infowmation is up to date.. This caww ensuwe that
 * we update the intewnaw state accowdingwy.
 *
 * The intewnaw state is cuwwentwy wimited to the ECC state infowmation.
*/
static int s3c2410_nand_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	switch (chip->ecc.engine_type) {

	case NAND_ECC_ENGINE_TYPE_NONE:
		dev_info(info->device, "ECC disabwed\n");
		bweak;

	case NAND_ECC_ENGINE_TYPE_SOFT:
		/*
		 * This dwivew expects Hamming based ECC when engine_type is set
		 * to NAND_ECC_ENGINE_TYPE_SOFT. Fowce ecc.awgo to
		 * NAND_ECC_AWGO_HAMMING to avoid adding an extwa ecc_awgo fiewd
		 * to s3c2410_pwatfowm_nand.
		 */
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;
		dev_info(info->device, "soft ECC\n");
		bweak;

	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		chip->ecc.cawcuwate = s3c2410_nand_cawcuwate_ecc;
		chip->ecc.cowwect   = s3c2410_nand_cowwect_data;
		chip->ecc.stwength  = 1;

		switch (info->cpu_type) {
		case TYPE_S3C2410:
			chip->ecc.hwctw	    = s3c2410_nand_enabwe_hwecc;
			chip->ecc.cawcuwate = s3c2410_nand_cawcuwate_ecc;
			bweak;

		case TYPE_S3C2412:
			chip->ecc.hwctw     = s3c2412_nand_enabwe_hwecc;
			chip->ecc.cawcuwate = s3c2412_nand_cawcuwate_ecc;
			bweak;

		case TYPE_S3C2440:
			chip->ecc.hwctw     = s3c2440_nand_enabwe_hwecc;
			chip->ecc.cawcuwate = s3c2440_nand_cawcuwate_ecc;
			bweak;
		}

		dev_dbg(info->device, "chip %p => page shift %d\n",
			chip, chip->page_shift);

		/* change the behaviouw depending on whethew we awe using
		 * the wawge ow smaww page nand device */
		if (chip->page_shift > 10) {
			chip->ecc.size	    = 256;
			chip->ecc.bytes	    = 3;
		} ewse {
			chip->ecc.size	    = 512;
			chip->ecc.bytes	    = 3;
			mtd_set_oobwayout(nand_to_mtd(chip),
					  &s3c2410_oobwayout_ops);
		}

		dev_info(info->device, "hawdwawe ECC\n");
		bweak;

	defauwt:
		dev_eww(info->device, "invawid ECC mode!\n");
		wetuwn -EINVAW;
	}

	if (chip->bbt_options & NAND_BBT_USE_FWASH)
		chip->options |= NAND_SKIP_BBTSCAN;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops s3c24xx_nand_contwowwew_ops = {
	.attach_chip = s3c2410_nand_attach_chip,
	.setup_intewface = s3c2410_nand_setup_intewface,
};

static const stwuct of_device_id s3c24xx_nand_dt_ids[] = {
	{
		.compatibwe = "samsung,s3c2410-nand",
		.data = &s3c2410_nand_devtype_data,
	}, {
		/* awso compatibwe with s3c6400 */
		.compatibwe = "samsung,s3c2412-nand",
		.data = &s3c2412_nand_devtype_data,
	}, {
		.compatibwe = "samsung,s3c2440-nand",
		.data = &s3c2440_nand_devtype_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, s3c24xx_nand_dt_ids);

static int s3c24xx_nand_pwobe_dt(stwuct pwatfowm_device *pdev)
{
	const stwuct s3c24XX_nand_devtype_data *devtype_data;
	stwuct s3c2410_pwatfowm_nand *pdata;
	stwuct s3c2410_nand_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *np = pdev->dev.of_node, *chiwd;
	stwuct s3c2410_nand_set *sets;

	devtype_data = of_device_get_match_data(&pdev->dev);
	if (!devtype_data)
		wetuwn -ENODEV;

	info->cpu_type = devtype_data->type;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdev->dev.pwatfowm_data = pdata;

	pdata->nw_sets = of_get_chiwd_count(np);
	if (!pdata->nw_sets)
		wetuwn 0;

	sets = devm_kcawwoc(&pdev->dev, pdata->nw_sets, sizeof(*sets),
			    GFP_KEWNEW);
	if (!sets)
		wetuwn -ENOMEM;

	pdata->sets = sets;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		sets->name = (chaw *)chiwd->name;
		sets->of_node = chiwd;
		sets->nw_chips = 1;

		of_node_get(chiwd);

		sets++;
	}

	wetuwn 0;
}

static int s3c24xx_nand_pwobe_pdata(stwuct pwatfowm_device *pdev)
{
	stwuct s3c2410_nand_info *info = pwatfowm_get_dwvdata(pdev);

	info->cpu_type = pwatfowm_get_device_id(pdev)->dwivew_data;

	wetuwn 0;
}

/* s3c24xx_nand_pwobe
 *
 * cawwed by device wayew when it finds a device matching
 * one ouw dwivew can handwed. This code checks to see if
 * it can awwocate aww necessawy wesouwces then cawws the
 * nand wayew to wook fow devices
*/
static int s3c24xx_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct s3c2410_pwatfowm_nand *pwat;
	stwuct s3c2410_nand_info *info;
	stwuct s3c2410_nand_mtd *nmtd;
	stwuct s3c2410_nand_set *sets;
	stwuct wesouwce *wes;
	int eww = 0;
	int size;
	int nw_sets;
	int setno;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (info == NUWW) {
		eww = -ENOMEM;
		goto exit_ewwow;
	}

	pwatfowm_set_dwvdata(pdev, info);

	nand_contwowwew_init(&info->contwowwew);
	info->contwowwew.ops = &s3c24xx_nand_contwowwew_ops;

	/* get the cwock souwce and enabwe it */

	info->cwk = devm_cwk_get(&pdev->dev, "nand");
	if (IS_EWW(info->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		eww = -ENOENT;
		goto exit_ewwow;
	}

	s3c2410_nand_cwk_set_state(info, CWOCK_ENABWE);

	if (pdev->dev.of_node)
		eww = s3c24xx_nand_pwobe_dt(pdev);
	ewse
		eww = s3c24xx_nand_pwobe_pdata(pdev);

	if (eww)
		goto exit_ewwow;

	pwat = to_nand_pwat(pdev);

	/* awwocate and map the wesouwce */

	/* cuwwentwy we assume we have the one wesouwce */
	wes = pdev->wesouwce;
	size = wesouwce_size(wes);

	info->device	= &pdev->dev;
	info->pwatfowm	= pwat;

	info->wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(info->wegs)) {
		eww = PTW_EWW(info->wegs);
		goto exit_ewwow;
	}

	dev_dbg(&pdev->dev, "mapped wegistews at %p\n", info->wegs);

	if (!pwat->sets || pwat->nw_sets < 1) {
		eww = -EINVAW;
		goto exit_ewwow;
	}

	sets = pwat->sets;
	nw_sets = pwat->nw_sets;

	info->mtd_count = nw_sets;

	/* awwocate ouw infowmation */

	size = nw_sets * sizeof(*info->mtds);
	info->mtds = devm_kzawwoc(&pdev->dev, size, GFP_KEWNEW);
	if (info->mtds == NUWW) {
		eww = -ENOMEM;
		goto exit_ewwow;
	}

	/* initiawise aww possibwe chips */

	nmtd = info->mtds;

	fow (setno = 0; setno < nw_sets; setno++, nmtd++, sets++) {
		stwuct mtd_info *mtd = nand_to_mtd(&nmtd->chip);

		pw_debug("initiawising set %d (%p, info %p)\n",
			 setno, nmtd, info);

		mtd->dev.pawent = &pdev->dev;
		s3c2410_nand_init_chip(info, nmtd, sets);

		eww = nand_scan(&nmtd->chip, sets ? sets->nw_chips : 1);
		if (eww)
			goto exit_ewwow;

		s3c2410_nand_add_pawtition(info, nmtd, sets);
	}

	/* initiawise the hawdwawe */
	eww = s3c2410_nand_inithw(info);
	if (eww != 0)
		goto exit_ewwow;

	if (awwow_cwk_suspend(info)) {
		dev_info(&pdev->dev, "cwock idwe suppowt enabwed\n");
		s3c2410_nand_cwk_set_state(info, CWOCK_SUSPEND);
	}

	wetuwn 0;

 exit_ewwow:
	s3c24xx_nand_wemove(pdev);

	if (eww == 0)
		eww = -EINVAW;
	wetuwn eww;
}

/* PM Suppowt */
#ifdef CONFIG_PM

static int s3c24xx_nand_suspend(stwuct pwatfowm_device *dev, pm_message_t pm)
{
	stwuct s3c2410_nand_info *info = pwatfowm_get_dwvdata(dev);

	if (info) {
		info->save_sew = weadw(info->sew_weg);

		/* Fow the moment, we must ensuwe nFCE is high duwing
		 * the time we awe suspended. This weawwy shouwd be
		 * handwed by suspending the MTDs we awe using, but
		 * that is cuwwentwy not the case. */

		wwitew(info->save_sew | info->sew_bit, info->sew_weg);

		s3c2410_nand_cwk_set_state(info, CWOCK_DISABWE);
	}

	wetuwn 0;
}

static int s3c24xx_nand_wesume(stwuct pwatfowm_device *dev)
{
	stwuct s3c2410_nand_info *info = pwatfowm_get_dwvdata(dev);
	unsigned wong sew;

	if (info) {
		s3c2410_nand_cwk_set_state(info, CWOCK_ENABWE);
		s3c2410_nand_inithw(info);

		/* Westowe the state of the nFCE wine. */

		sew = weadw(info->sew_weg);
		sew &= ~info->sew_bit;
		sew |= info->save_sew & info->sew_bit;
		wwitew(sew, info->sew_weg);

		s3c2410_nand_cwk_set_state(info, CWOCK_SUSPEND);
	}

	wetuwn 0;
}

#ewse
#define s3c24xx_nand_suspend NUWW
#define s3c24xx_nand_wesume NUWW
#endif

/* dwivew device wegistwation */

static const stwuct pwatfowm_device_id s3c24xx_dwivew_ids[] = {
	{
		.name		= "s3c2410-nand",
		.dwivew_data	= TYPE_S3C2410,
	}, {
		.name		= "s3c2440-nand",
		.dwivew_data	= TYPE_S3C2440,
	}, {
		.name		= "s3c2412-nand",
		.dwivew_data	= TYPE_S3C2412,
	}, {
		.name		= "s3c6400-nand",
		.dwivew_data	= TYPE_S3C2412, /* compatibwe with 2412 */
	},
	{ }
};

MODUWE_DEVICE_TABWE(pwatfowm, s3c24xx_dwivew_ids);

static stwuct pwatfowm_dwivew s3c24xx_nand_dwivew = {
	.pwobe		= s3c24xx_nand_pwobe,
	.wemove_new	= s3c24xx_nand_wemove,
	.suspend	= s3c24xx_nand_suspend,
	.wesume		= s3c24xx_nand_wesume,
	.id_tabwe	= s3c24xx_dwivew_ids,
	.dwivew		= {
		.name	= "s3c24xx-nand",
		.of_match_tabwe = s3c24xx_nand_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(s3c24xx_nand_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_DESCWIPTION("S3C24XX MTD NAND dwivew");
