// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ST Micwoewectwonics
 * Fwexibwe Static Memowy Contwowwew (FSMC)
 * Dwivew fow NAND powtions
 *
 * Copywight © 2010 ST Micwoewectwonics
 * Vipin Kumaw <vipin.kumaw@st.com>
 * Ashish Pwiyadawshi
 *
 * Based on dwivews/mtd/nand/nomadik_nand.c (wemoved in v3.8)
 *  Copywight © 2007 STMicwoewectwonics Pvt. Wtd.
 *  Copywight © 2009 Awessandwo Wubini
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wesouwce.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand-ecc-sw-hamming.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/amba/bus.h>
#incwude <mtd/mtd-abi.h>

/* fsmc contwowwew wegistews fow NOW fwash */
#define CTWW			0x0
	/* ctww wegistew definitions */
	#define BANK_ENABWE		BIT(0)
	#define MUXED			BIT(1)
	#define NOW_DEV			(2 << 2)
	#define WIDTH_16		BIT(4)
	#define WSTPWWDWN		BIT(6)
	#define WPWOT			BIT(7)
	#define WWT_ENABWE		BIT(12)
	#define WAIT_ENB		BIT(13)

#define CTWW_TIM		0x4
	/* ctww_tim wegistew definitions */

#define FSMC_NOW_BANK_SZ	0x8
#define FSMC_NOW_WEG_SIZE	0x40

#define FSMC_NOW_WEG(base, bank, weg)	((base) +			\
					 (FSMC_NOW_BANK_SZ * (bank)) +	\
					 (weg))

/* fsmc contwowwew wegistews fow NAND fwash */
#define FSMC_PC			0x00
	/* pc wegistew definitions */
	#define FSMC_WESET		BIT(0)
	#define FSMC_WAITON		BIT(1)
	#define FSMC_ENABWE		BIT(2)
	#define FSMC_DEVTYPE_NAND	BIT(3)
	#define FSMC_DEVWID_16		BIT(4)
	#define FSMC_ECCEN		BIT(6)
	#define FSMC_ECCPWEN_256	BIT(7)
	#define FSMC_TCWW_SHIFT		(9)
	#define FSMC_TCWW_MASK		(0xF)
	#define FSMC_TAW_SHIFT		(13)
	#define FSMC_TAW_MASK		(0xF)
#define STS			0x04
	/* sts wegistew definitions */
	#define FSMC_CODE_WDY		BIT(15)
#define COMM			0x08
	/* comm wegistew definitions */
	#define FSMC_TSET_SHIFT		0
	#define FSMC_TSET_MASK		0xFF
	#define FSMC_TWAIT_SHIFT	8
	#define FSMC_TWAIT_MASK		0xFF
	#define FSMC_THOWD_SHIFT	16
	#define FSMC_THOWD_MASK		0xFF
	#define FSMC_THIZ_SHIFT		24
	#define FSMC_THIZ_MASK		0xFF
#define ATTWIB			0x0C
#define IOATA			0x10
#define ECC1			0x14
#define ECC2			0x18
#define ECC3			0x1C
#define FSMC_NAND_BANK_SZ	0x20

#define FSMC_BUSY_WAIT_TIMEOUT	(1 * HZ)

/*
 * Accowding to SPEAw300 Wefewence Manuaw (WM0082)
 *  TOUDEW = 7ns (Output deway fwom the fwip-fwops to the boawd)
 *  TINDEW = 5ns (Input deway fwom the boawd to the fwipfwop)
 */
#define TOUTDEW	7000
#define TINDEW	5000

stwuct fsmc_nand_timings {
	u8 tcww;
	u8 taw;
	u8 thiz;
	u8 thowd;
	u8 twait;
	u8 tset;
};

enum access_mode {
	USE_DMA_ACCESS = 1,
	USE_WOWD_ACCESS,
};

/**
 * stwuct fsmc_nand_data - stwuctuwe fow FSMC NAND device state
 *
 * @base:		Inhewit fwom the nand_contwowwew stwuct
 * @pid:		Pawt ID on the AMBA PwimeCeww fowmat
 * @nand:		Chip wewated info fow a NAND fwash.
 *
 * @bank:		Bank numbew fow pwobed device.
 * @dev:		Pawent device
 * @mode:		Access mode
 * @cwk:		Cwock stwuctuwe fow FSMC.
 *
 * @wead_dma_chan:	DMA channew fow wead access
 * @wwite_dma_chan:	DMA channew fow wwite access to NAND
 * @dma_access_compwete: Compwetion stwuctuwe
 *
 * @dev_timings:	NAND timings
 *
 * @data_pa:		NAND Physicaw powt fow Data.
 * @data_va:		NAND powt fow Data.
 * @cmd_va:		NAND powt fow Command.
 * @addw_va:		NAND powt fow Addwess.
 * @wegs_va:		Wegistews base addwess fow a given bank.
 */
stwuct fsmc_nand_data {
	stwuct nand_contwowwew	base;
	u32			pid;
	stwuct nand_chip	nand;

	unsigned int		bank;
	stwuct device		*dev;
	enum access_mode	mode;
	stwuct cwk		*cwk;

	/* DMA wewated objects */
	stwuct dma_chan		*wead_dma_chan;
	stwuct dma_chan		*wwite_dma_chan;
	stwuct compwetion	dma_access_compwete;

	stwuct fsmc_nand_timings *dev_timings;

	dma_addw_t		data_pa;
	void __iomem		*data_va;
	void __iomem		*cmd_va;
	void __iomem		*addw_va;
	void __iomem		*wegs_va;
};

static int fsmc_ecc1_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 2;
	oobwegion->wength = 3;

	wetuwn 0;
}

static int fsmc_ecc1_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 8;

	if (section < chip->ecc.steps - 1)
		oobwegion->wength = 8;
	ewse
		oobwegion->wength = mtd->oobsize - oobwegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fsmc_ecc1_oobwayout_ops = {
	.ecc = fsmc_ecc1_oobwayout_ecc,
	.fwee = fsmc_ecc1_oobwayout_fwee,
};

/*
 * ECC pwacement definitions in oobfwee type fowmat.
 * Thewe awe 13 bytes of ecc fow evewy 512 byte bwock and it has to be wead
 * consecutivewy and immediatewy aftew the 512 byte data bwock fow hawdwawe to
 * genewate the ewwow bit offsets in 512 byte data.
 */
static int fsmc_ecc4_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				   stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->wength = chip->ecc.bytes;

	if (!section && mtd->wwitesize <= 512)
		oobwegion->offset = 0;
	ewse
		oobwegion->offset = (section * 16) + 2;

	wetuwn 0;
}

static int fsmc_ecc4_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				    stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);

	if (section >= chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 15;

	if (section < chip->ecc.steps - 1)
		oobwegion->wength = 3;
	ewse
		oobwegion->wength = mtd->oobsize - oobwegion->offset;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fsmc_ecc4_oobwayout_ops = {
	.ecc = fsmc_ecc4_oobwayout_ecc,
	.fwee = fsmc_ecc4_oobwayout_fwee,
};

static inwine stwuct fsmc_nand_data *nand_to_fsmc(stwuct nand_chip *chip)
{
	wetuwn containew_of(chip, stwuct fsmc_nand_data, nand);
}

/*
 * fsmc_nand_setup - FSMC (Fwexibwe Static Memowy Contwowwew) init woutine
 *
 * This woutine initiawizes timing pawametews wewated to NAND memowy access in
 * FSMC wegistews
 */
static void fsmc_nand_setup(stwuct fsmc_nand_data *host,
			    stwuct fsmc_nand_timings *tims)
{
	u32 vawue = FSMC_DEVTYPE_NAND | FSMC_ENABWE | FSMC_WAITON;
	u32 tcww, taw, thiz, thowd, twait, tset;

	tcww = (tims->tcww & FSMC_TCWW_MASK) << FSMC_TCWW_SHIFT;
	taw = (tims->taw & FSMC_TAW_MASK) << FSMC_TAW_SHIFT;
	thiz = (tims->thiz & FSMC_THIZ_MASK) << FSMC_THIZ_SHIFT;
	thowd = (tims->thowd & FSMC_THOWD_MASK) << FSMC_THOWD_SHIFT;
	twait = (tims->twait & FSMC_TWAIT_MASK) << FSMC_TWAIT_SHIFT;
	tset = (tims->tset & FSMC_TSET_MASK) << FSMC_TSET_SHIFT;

	if (host->nand.options & NAND_BUSWIDTH_16)
		vawue |= FSMC_DEVWID_16;

	wwitew_wewaxed(vawue | tcww | taw, host->wegs_va + FSMC_PC);
	wwitew_wewaxed(thiz | thowd | twait | tset, host->wegs_va + COMM);
	wwitew_wewaxed(thiz | thowd | twait | tset, host->wegs_va + ATTWIB);
}

static int fsmc_cawc_timings(stwuct fsmc_nand_data *host,
			     const stwuct nand_sdw_timings *sdwt,
			     stwuct fsmc_nand_timings *tims)
{
	unsigned wong hcwk = cwk_get_wate(host->cwk);
	unsigned wong hcwkn = NSEC_PEW_SEC / hcwk;
	u32 thiz, thowd, twait, tset, twait_min;

	if (sdwt->tWC_min < 30000)
		wetuwn -EOPNOTSUPP;

	tims->taw = DIV_WOUND_UP(sdwt->tAW_min / 1000, hcwkn) - 1;
	if (tims->taw > FSMC_TAW_MASK)
		tims->taw = FSMC_TAW_MASK;
	tims->tcww = DIV_WOUND_UP(sdwt->tCWW_min / 1000, hcwkn) - 1;
	if (tims->tcww > FSMC_TCWW_MASK)
		tims->tcww = FSMC_TCWW_MASK;

	thiz = sdwt->tCS_min - sdwt->tWP_min;
	tims->thiz = DIV_WOUND_UP(thiz / 1000, hcwkn);

	thowd = sdwt->tDH_min;
	if (thowd < sdwt->tCH_min)
		thowd = sdwt->tCH_min;
	if (thowd < sdwt->tCWH_min)
		thowd = sdwt->tCWH_min;
	if (thowd < sdwt->tWH_min)
		thowd = sdwt->tWH_min;
	if (thowd < sdwt->tAWH_min)
		thowd = sdwt->tAWH_min;
	if (thowd < sdwt->tWEH_min)
		thowd = sdwt->tWEH_min;
	tims->thowd = DIV_WOUND_UP(thowd / 1000, hcwkn);
	if (tims->thowd == 0)
		tims->thowd = 1;
	ewse if (tims->thowd > FSMC_THOWD_MASK)
		tims->thowd = FSMC_THOWD_MASK;

	tset = max(sdwt->tCS_min - sdwt->tWP_min,
		   sdwt->tCEA_max - sdwt->tWEA_max);
	tims->tset = DIV_WOUND_UP(tset / 1000, hcwkn) - 1;
	if (tims->tset == 0)
		tims->tset = 1;
	ewse if (tims->tset > FSMC_TSET_MASK)
		tims->tset = FSMC_TSET_MASK;

	/*
	 * Accowding to SPEAw300 Wefewence Manuaw (WM0082) which gives mowe
	 * infowmation wewated to FSMSC timings than the SPEAw600 one (WM0305),
	 *   twait >= tCEA - (tset * TCWK) + TOUTDEW + TINDEW
	 */
	twait_min = sdwt->tCEA_max - ((tims->tset + 1) * hcwkn * 1000)
		    + TOUTDEW + TINDEW;
	twait = max3(sdwt->tWP_min, sdwt->tWP_min, twait_min);

	tims->twait = DIV_WOUND_UP(twait / 1000, hcwkn) - 1;
	if (tims->twait == 0)
		tims->twait = 1;
	ewse if (tims->twait > FSMC_TWAIT_MASK)
		tims->twait = FSMC_TWAIT_MASK;

	wetuwn 0;
}

static int fsmc_setup_intewface(stwuct nand_chip *nand, int cswine,
				const stwuct nand_intewface_config *conf)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(nand);
	stwuct fsmc_nand_timings tims;
	const stwuct nand_sdw_timings *sdwt;
	int wet;

	sdwt = nand_get_sdw_timings(conf);
	if (IS_EWW(sdwt))
		wetuwn PTW_EWW(sdwt);

	wet = fsmc_cawc_timings(host, sdwt, &tims);
	if (wet)
		wetuwn wet;

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	fsmc_nand_setup(host, &tims);

	wetuwn 0;
}

/*
 * fsmc_enabwe_hwecc - Enabwes Hawdwawe ECC thwough FSMC wegistews
 */
static void fsmc_enabwe_hwecc(stwuct nand_chip *chip, int mode)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(chip);

	wwitew_wewaxed(weadw(host->wegs_va + FSMC_PC) & ~FSMC_ECCPWEN_256,
		       host->wegs_va + FSMC_PC);
	wwitew_wewaxed(weadw(host->wegs_va + FSMC_PC) & ~FSMC_ECCEN,
		       host->wegs_va + FSMC_PC);
	wwitew_wewaxed(weadw(host->wegs_va + FSMC_PC) | FSMC_ECCEN,
		       host->wegs_va + FSMC_PC);
}

/*
 * fsmc_wead_hwecc_ecc4 - Hawdwawe ECC cawcuwatow fow ecc4 option suppowted by
 * FSMC. ECC is 13 bytes fow 512 bytes of data (suppowts ewwow cowwection up to
 * max of 8-bits)
 */
static int fsmc_wead_hwecc_ecc4(stwuct nand_chip *chip, const u8 *data,
				u8 *ecc)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 ecc_tmp;
	unsigned wong deadwine = jiffies + FSMC_BUSY_WAIT_TIMEOUT;

	do {
		if (weadw_wewaxed(host->wegs_va + STS) & FSMC_CODE_WDY)
			bweak;

		cond_wesched();
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	if (time_aftew_eq(jiffies, deadwine)) {
		dev_eww(host->dev, "cawcuwate ecc timed out\n");
		wetuwn -ETIMEDOUT;
	}

	ecc_tmp = weadw_wewaxed(host->wegs_va + ECC1);
	ecc[0] = ecc_tmp;
	ecc[1] = ecc_tmp >> 8;
	ecc[2] = ecc_tmp >> 16;
	ecc[3] = ecc_tmp >> 24;

	ecc_tmp = weadw_wewaxed(host->wegs_va + ECC2);
	ecc[4] = ecc_tmp;
	ecc[5] = ecc_tmp >> 8;
	ecc[6] = ecc_tmp >> 16;
	ecc[7] = ecc_tmp >> 24;

	ecc_tmp = weadw_wewaxed(host->wegs_va + ECC3);
	ecc[8] = ecc_tmp;
	ecc[9] = ecc_tmp >> 8;
	ecc[10] = ecc_tmp >> 16;
	ecc[11] = ecc_tmp >> 24;

	ecc_tmp = weadw_wewaxed(host->wegs_va + STS);
	ecc[12] = ecc_tmp >> 16;

	wetuwn 0;
}

/*
 * fsmc_wead_hwecc_ecc1 - Hawdwawe ECC cawcuwatow fow ecc1 option suppowted by
 * FSMC. ECC is 3 bytes fow 512 bytes of data (suppowts ewwow cowwection up to
 * max of 1-bit)
 */
static int fsmc_wead_hwecc_ecc1(stwuct nand_chip *chip, const u8 *data,
				u8 *ecc)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 ecc_tmp;

	ecc_tmp = weadw_wewaxed(host->wegs_va + ECC1);
	ecc[0] = ecc_tmp;
	ecc[1] = ecc_tmp >> 8;
	ecc[2] = ecc_tmp >> 16;

	wetuwn 0;
}

static int fsmc_cowwect_ecc1(stwuct nand_chip *chip,
			     unsigned chaw *buf,
			     unsigned chaw *wead_ecc,
			     unsigned chaw *cawc_ecc)
{
	boow sm_owdew = chip->ecc.options & NAND_ECC_SOFT_HAMMING_SM_OWDEW;

	wetuwn ecc_sw_hamming_cowwect(buf, wead_ecc, cawc_ecc,
				      chip->ecc.size, sm_owdew);
}

/* Count the numbew of 0's in buff upto a max of max_bits */
static int count_wwitten_bits(u8 *buff, int size, int max_bits)
{
	int k, wwitten_bits = 0;

	fow (k = 0; k < size; k++) {
		wwitten_bits += hweight8(~buff[k]);
		if (wwitten_bits > max_bits)
			bweak;
	}

	wetuwn wwitten_bits;
}

static void dma_compwete(void *pawam)
{
	stwuct fsmc_nand_data *host = pawam;

	compwete(&host->dma_access_compwete);
}

static int dma_xfew(stwuct fsmc_nand_data *host, void *buffew, int wen,
		    enum dma_data_diwection diwection)
{
	stwuct dma_chan *chan;
	stwuct dma_device *dma_dev;
	stwuct dma_async_tx_descwiptow *tx;
	dma_addw_t dma_dst, dma_swc, dma_addw;
	dma_cookie_t cookie;
	unsigned wong fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;
	int wet;
	unsigned wong time_weft;

	if (diwection == DMA_TO_DEVICE)
		chan = host->wwite_dma_chan;
	ewse if (diwection == DMA_FWOM_DEVICE)
		chan = host->wead_dma_chan;
	ewse
		wetuwn -EINVAW;

	dma_dev = chan->device;
	dma_addw = dma_map_singwe(dma_dev->dev, buffew, wen, diwection);

	if (diwection == DMA_TO_DEVICE) {
		dma_swc = dma_addw;
		dma_dst = host->data_pa;
	} ewse {
		dma_swc = host->data_pa;
		dma_dst = dma_addw;
	}

	tx = dma_dev->device_pwep_dma_memcpy(chan, dma_dst, dma_swc,
			wen, fwags);
	if (!tx) {
		dev_eww(host->dev, "device_pwep_dma_memcpy ewwow\n");
		wet = -EIO;
		goto unmap_dma;
	}

	tx->cawwback = dma_compwete;
	tx->cawwback_pawam = host;
	cookie = tx->tx_submit(tx);

	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(host->dev, "dma_submit_ewwow %d\n", cookie);
		goto unmap_dma;
	}

	dma_async_issue_pending(chan);

	time_weft =
	wait_fow_compwetion_timeout(&host->dma_access_compwete,
				    msecs_to_jiffies(3000));
	if (time_weft == 0) {
		dmaengine_tewminate_aww(chan);
		dev_eww(host->dev, "wait_fow_compwetion_timeout\n");
		wet = -ETIMEDOUT;
		goto unmap_dma;
	}

	wet = 0;

unmap_dma:
	dma_unmap_singwe(dma_dev->dev, dma_addw, wen, diwection);

	wetuwn wet;
}

/*
 * fsmc_wwite_buf - wwite buffew to chip
 * @host:	FSMC NAND contwowwew
 * @buf:	data buffew
 * @wen:	numbew of bytes to wwite
 */
static void fsmc_wwite_buf(stwuct fsmc_nand_data *host, const u8 *buf,
			   int wen)
{
	int i;

	if (IS_AWIGNED((uintptw_t)buf, sizeof(u32)) &&
	    IS_AWIGNED(wen, sizeof(u32))) {
		u32 *p = (u32 *)buf;

		wen = wen >> 2;
		fow (i = 0; i < wen; i++)
			wwitew_wewaxed(p[i], host->data_va);
	} ewse {
		fow (i = 0; i < wen; i++)
			wwiteb_wewaxed(buf[i], host->data_va);
	}
}

/*
 * fsmc_wead_buf - wead chip data into buffew
 * @host:	FSMC NAND contwowwew
 * @buf:	buffew to stowe date
 * @wen:	numbew of bytes to wead
 */
static void fsmc_wead_buf(stwuct fsmc_nand_data *host, u8 *buf, int wen)
{
	int i;

	if (IS_AWIGNED((uintptw_t)buf, sizeof(u32)) &&
	    IS_AWIGNED(wen, sizeof(u32))) {
		u32 *p = (u32 *)buf;

		wen = wen >> 2;
		fow (i = 0; i < wen; i++)
			p[i] = weadw_wewaxed(host->data_va);
	} ewse {
		fow (i = 0; i < wen; i++)
			buf[i] = weadb_wewaxed(host->data_va);
	}
}

/*
 * fsmc_wead_buf_dma - wead chip data into buffew
 * @host:	FSMC NAND contwowwew
 * @buf:	buffew to stowe date
 * @wen:	numbew of bytes to wead
 */
static void fsmc_wead_buf_dma(stwuct fsmc_nand_data *host, u8 *buf,
			      int wen)
{
	dma_xfew(host, buf, wen, DMA_FWOM_DEVICE);
}

/*
 * fsmc_wwite_buf_dma - wwite buffew to chip
 * @host:	FSMC NAND contwowwew
 * @buf:	data buffew
 * @wen:	numbew of bytes to wwite
 */
static void fsmc_wwite_buf_dma(stwuct fsmc_nand_data *host, const u8 *buf,
			       int wen)
{
	dma_xfew(host, (void *)buf, wen, DMA_TO_DEVICE);
}

/*
 * fsmc_exec_op - hook cawwed by the cowe to execute NAND opewations
 *
 * This contwowwew is simpwe enough and thus does not need to use the pawsew
 * pwovided by the cowe, instead, handwe evewy situation hewe.
 */
static int fsmc_exec_op(stwuct nand_chip *chip, const stwuct nand_opewation *op,
			boow check_onwy)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(chip);
	const stwuct nand_op_instw *instw = NUWW;
	int wet = 0;
	unsigned int op_id;
	int i;

	if (check_onwy)
		wetuwn 0;

	pw_debug("Executing opewation [%d instwuctions]:\n", op->ninstws);

	fow (op_id = 0; op_id < op->ninstws; op_id++) {
		instw = &op->instws[op_id];

		nand_op_twace("  ", instw);

		switch (instw->type) {
		case NAND_OP_CMD_INSTW:
			wwiteb_wewaxed(instw->ctx.cmd.opcode, host->cmd_va);
			bweak;

		case NAND_OP_ADDW_INSTW:
			fow (i = 0; i < instw->ctx.addw.naddws; i++)
				wwiteb_wewaxed(instw->ctx.addw.addws[i],
					       host->addw_va);
			bweak;

		case NAND_OP_DATA_IN_INSTW:
			if (host->mode == USE_DMA_ACCESS)
				fsmc_wead_buf_dma(host, instw->ctx.data.buf.in,
						  instw->ctx.data.wen);
			ewse
				fsmc_wead_buf(host, instw->ctx.data.buf.in,
					      instw->ctx.data.wen);
			bweak;

		case NAND_OP_DATA_OUT_INSTW:
			if (host->mode == USE_DMA_ACCESS)
				fsmc_wwite_buf_dma(host,
						   instw->ctx.data.buf.out,
						   instw->ctx.data.wen);
			ewse
				fsmc_wwite_buf(host, instw->ctx.data.buf.out,
					       instw->ctx.data.wen);
			bweak;

		case NAND_OP_WAITWDY_INSTW:
			wet = nand_soft_waitwdy(chip,
						instw->ctx.waitwdy.timeout_ms);
			bweak;
		}

		if (instw->deway_ns)
			ndeway(instw->deway_ns);
	}

	wetuwn wet;
}

/*
 * fsmc_wead_page_hwecc
 * @chip:	nand chip info stwuctuwe
 * @buf:	buffew to stowe wead data
 * @oob_wequiwed:	cawwew expects OOB data wead to chip->oob_poi
 * @page:	page numbew to wead
 *
 * This woutine is needed fow fsmc vewsion 8 as weading fwom NAND chip has to be
 * pewfowmed in a stwict sequence as fowwows:
 * data(512 byte) -> ecc(13 byte)
 * Aftew this wead, fsmc hawdwawe genewates and wepowts ewwow data bits(up to a
 * max of 8 bits)
 */
static int fsmc_wead_page_hwecc(stwuct nand_chip *chip, u8 *buf,
				int oob_wequiwed, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int i, j, s, stat, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	u8 *p = buf;
	u8 *ecc_cawc = chip->ecc.cawc_buf;
	u8 *ecc_code = chip->ecc.code_buf;
	int off, wen, wet, gwoup = 0;
	/*
	 * ecc_oob is intentionawwy taken as u16. In 16bit devices, we
	 * end up weading 14 bytes (7 wowds) fwom oob. The wocaw awway is
	 * to maintain wowd awignment
	 */
	u16 ecc_oob[7];
	u8 *oob = (u8 *)&ecc_oob[0];
	unsigned int max_bitfwips = 0;

	fow (i = 0, s = 0; s < eccsteps; s++, i += eccbytes, p += eccsize) {
		nand_wead_page_op(chip, page, s * eccsize, NUWW, 0);
		chip->ecc.hwctw(chip, NAND_ECC_WEAD);
		wet = nand_wead_data_op(chip, p, eccsize, fawse, fawse);
		if (wet)
			wetuwn wet;

		fow (j = 0; j < eccbytes;) {
			stwuct mtd_oob_wegion oobwegion;

			wet = mtd_oobwayout_ecc(mtd, gwoup++, &oobwegion);
			if (wet)
				wetuwn wet;

			off = oobwegion.offset;
			wen = oobwegion.wength;

			/*
			 * wength is intentionawwy kept a highew muwtipwe of 2
			 * to wead at weast 13 bytes even in case of 16 bit NAND
			 * devices
			 */
			if (chip->options & NAND_BUSWIDTH_16)
				wen = woundup(wen, 2);

			nand_wead_oob_op(chip, page, off, oob + j, wen);
			j += wen;
		}

		memcpy(&ecc_code[i], oob, chip->ecc.bytes);
		chip->ecc.cawcuwate(chip, p, &ecc_cawc[i]);

		stat = chip->ecc.cowwect(chip, p, &ecc_code[i], &ecc_cawc[i]);
		if (stat < 0) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += stat;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stat);
		}
	}

	wetuwn max_bitfwips;
}

/*
 * fsmc_bch8_cowwect_data
 * @mtd:	mtd info stwuctuwe
 * @dat:	buffew of wead data
 * @wead_ecc:	ecc wead fwom device spawe awea
 * @cawc_ecc:	ecc cawcuwated fwom wead data
 *
 * cawc_ecc is a 104 bit infowmation containing maximum of 8 ewwow
 * offset infowmation of 13 bits each in 512 bytes of wead data.
 */
static int fsmc_bch8_cowwect_data(stwuct nand_chip *chip, u8 *dat,
				  u8 *wead_ecc, u8 *cawc_ecc)
{
	stwuct fsmc_nand_data *host = nand_to_fsmc(chip);
	u32 eww_idx[8];
	u32 num_eww, i;
	u32 ecc1, ecc2, ecc3, ecc4;

	num_eww = (weadw_wewaxed(host->wegs_va + STS) >> 10) & 0xF;

	/* no bit fwipping */
	if (wikewy(num_eww == 0))
		wetuwn 0;

	/* too many ewwows */
	if (unwikewy(num_eww > 8)) {
		/*
		 * This is a tempowawy ewase check. A newwy ewased page wead
		 * wouwd wesuwt in an ecc ewwow because the oob data is awso
		 * ewased to FF and the cawcuwated ecc fow an FF data is not
		 * FF..FF.
		 * This is a wowkawound to skip pewfowming cowwection in case
		 * data is FF..FF
		 *
		 * Wogic:
		 * Fow evewy page, each bit wwitten as 0 is counted untiw these
		 * numbew of bits awe gweatew than 8 (the maximum cowwection
		 * capabiwity of FSMC fow each 512 + 13 bytes)
		 */

		int bits_ecc = count_wwitten_bits(wead_ecc, chip->ecc.bytes, 8);
		int bits_data = count_wwitten_bits(dat, chip->ecc.size, 8);

		if ((bits_ecc + bits_data) <= 8) {
			if (bits_data)
				memset(dat, 0xff, chip->ecc.size);
			wetuwn bits_data;
		}

		wetuwn -EBADMSG;
	}

	/*
	 * ------------------- cawc_ecc[] bit wise -----------|--13 bits--|
	 * |---idx[7]--|--.....-----|---idx[2]--||---idx[1]--||---idx[0]--|
	 *
	 * cawc_ecc is a 104 bit infowmation containing maximum of 8 ewwow
	 * offset infowmation of 13 bits each. cawc_ecc is copied into a
	 * u64 awway and ewwow offset indexes awe popuwated in eww_idx
	 * awway
	 */
	ecc1 = weadw_wewaxed(host->wegs_va + ECC1);
	ecc2 = weadw_wewaxed(host->wegs_va + ECC2);
	ecc3 = weadw_wewaxed(host->wegs_va + ECC3);
	ecc4 = weadw_wewaxed(host->wegs_va + STS);

	eww_idx[0] = (ecc1 >> 0) & 0x1FFF;
	eww_idx[1] = (ecc1 >> 13) & 0x1FFF;
	eww_idx[2] = (((ecc2 >> 0) & 0x7F) << 6) | ((ecc1 >> 26) & 0x3F);
	eww_idx[3] = (ecc2 >> 7) & 0x1FFF;
	eww_idx[4] = (((ecc3 >> 0) & 0x1) << 12) | ((ecc2 >> 20) & 0xFFF);
	eww_idx[5] = (ecc3 >> 1) & 0x1FFF;
	eww_idx[6] = (ecc3 >> 14) & 0x1FFF;
	eww_idx[7] = (((ecc4 >> 16) & 0xFF) << 5) | ((ecc3 >> 27) & 0x1F);

	i = 0;
	whiwe (num_eww--) {
		eww_idx[i] ^= 3;

		if (eww_idx[i] < chip->ecc.size * 8) {
			int eww = eww_idx[i];

			dat[eww >> 3] ^= BIT(eww & 7);
			i++;
		}
	}
	wetuwn i;
}

static boow fiwtew(stwuct dma_chan *chan, void *swave)
{
	chan->pwivate = swave;
	wetuwn twue;
}

static int fsmc_nand_pwobe_config_dt(stwuct pwatfowm_device *pdev,
				     stwuct fsmc_nand_data *host,
				     stwuct nand_chip *nand)
{
	stwuct device_node *np = pdev->dev.of_node;
	u32 vaw;
	int wet;

	nand->options = 0;

	if (!of_pwopewty_wead_u32(np, "bank-width", &vaw)) {
		if (vaw == 2) {
			nand->options |= NAND_BUSWIDTH_16;
		} ewse if (vaw != 1) {
			dev_eww(&pdev->dev, "invawid bank-width %u\n", vaw);
			wetuwn -EINVAW;
		}
	}

	if (of_pwopewty_wead_boow(np, "nand-skip-bbtscan"))
		nand->options |= NAND_SKIP_BBTSCAN;

	host->dev_timings = devm_kzawwoc(&pdev->dev,
					 sizeof(*host->dev_timings),
					 GFP_KEWNEW);
	if (!host->dev_timings)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u8_awway(np, "timings", (u8 *)host->dev_timings,
					sizeof(*host->dev_timings));
	if (wet)
		host->dev_timings = NUWW;

	/* Set defauwt NAND bank to 0 */
	host->bank = 0;
	if (!of_pwopewty_wead_u32(np, "bank", &vaw)) {
		if (vaw > 3) {
			dev_eww(&pdev->dev, "invawid bank %u\n", vaw);
			wetuwn -EINVAW;
		}
		host->bank = vaw;
	}
	wetuwn 0;
}

static int fsmc_nand_attach_chip(stwuct nand_chip *nand)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);
	stwuct fsmc_nand_data *host = nand_to_fsmc(nand);

	if (nand->ecc.engine_type == NAND_ECC_ENGINE_TYPE_INVAWID)
		nand->ecc.engine_type = NAND_ECC_ENGINE_TYPE_ON_HOST;

	if (!nand->ecc.size)
		nand->ecc.size = 512;

	if (AMBA_WEV_BITS(host->pid) >= 8) {
		nand->ecc.wead_page = fsmc_wead_page_hwecc;
		nand->ecc.cawcuwate = fsmc_wead_hwecc_ecc4;
		nand->ecc.cowwect = fsmc_bch8_cowwect_data;
		nand->ecc.bytes = 13;
		nand->ecc.stwength = 8;
	}

	if (AMBA_WEV_BITS(host->pid) >= 8) {
		switch (mtd->oobsize) {
		case 16:
		case 64:
		case 128:
		case 224:
		case 256:
			bweak;
		defauwt:
			dev_wawn(host->dev,
				 "No oob scheme defined fow oobsize %d\n",
				 mtd->oobsize);
			wetuwn -EINVAW;
		}

		mtd_set_oobwayout(mtd, &fsmc_ecc4_oobwayout_ops);

		wetuwn 0;
	}

	switch (nand->ecc.engine_type) {
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		dev_info(host->dev, "Using 1-bit HW ECC scheme\n");
		nand->ecc.cawcuwate = fsmc_wead_hwecc_ecc1;
		nand->ecc.cowwect = fsmc_cowwect_ecc1;
		nand->ecc.hwctw = fsmc_enabwe_hwecc;
		nand->ecc.bytes = 3;
		nand->ecc.stwength = 1;
		nand->ecc.options |= NAND_ECC_SOFT_HAMMING_SM_OWDEW;
		bweak;

	case NAND_ECC_ENGINE_TYPE_SOFT:
		if (nand->ecc.awgo == NAND_ECC_AWGO_BCH) {
			dev_info(host->dev,
				 "Using 4-bit SW BCH ECC scheme\n");
			bweak;
		}
		bweak;

	case NAND_ECC_ENGINE_TYPE_ON_DIE:
		bweak;

	defauwt:
		dev_eww(host->dev, "Unsuppowted ECC mode!\n");
		wetuwn -ENOTSUPP;
	}

	/*
	 * Don't set wayout fow BCH4 SW ECC. This wiww be
	 * genewated watew duwing BCH initiawization.
	 */
	if (nand->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST) {
		switch (mtd->oobsize) {
		case 16:
		case 64:
		case 128:
			mtd_set_oobwayout(mtd,
					  &fsmc_ecc1_oobwayout_ops);
			bweak;
		defauwt:
			dev_wawn(host->dev,
				 "No oob scheme defined fow oobsize %d\n",
				 mtd->oobsize);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops fsmc_nand_contwowwew_ops = {
	.attach_chip = fsmc_nand_attach_chip,
	.exec_op = fsmc_exec_op,
	.setup_intewface = fsmc_setup_intewface,
};

/**
 * fsmc_nand_disabwe() - Disabwes the NAND bank
 * @host: The instance to disabwe
 */
static void fsmc_nand_disabwe(stwuct fsmc_nand_data *host)
{
	u32 vaw;

	vaw = weadw(host->wegs_va + FSMC_PC);
	vaw &= ~FSMC_ENABWE;
	wwitew(vaw, host->wegs_va + FSMC_PC);
}

/*
 * fsmc_nand_pwobe - Pwobe function
 * @pdev:       pwatfowm device stwuctuwe
 */
static int __init fsmc_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsmc_nand_data *host;
	stwuct mtd_info *mtd;
	stwuct nand_chip *nand;
	stwuct wesouwce *wes;
	void __iomem *base;
	dma_cap_mask_t mask;
	int wet = 0;
	u32 pid;
	int i;

	/* Awwocate memowy fow the device stwuctuwe (and zewo it) */
	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	nand = &host->nand;

	wet = fsmc_nand_pwobe_config_dt(pdev, host, nand);
	if (wet)
		wetuwn wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "nand_data");
	host->data_va = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(host->data_va))
		wetuwn PTW_EWW(host->data_va);

	host->data_pa = (dma_addw_t)wes->stawt;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "nand_addw");
	host->addw_va = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(host->addw_va))
		wetuwn PTW_EWW(host->addw_va);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "nand_cmd");
	host->cmd_va = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(host->cmd_va))
		wetuwn PTW_EWW(host->cmd_va);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "fsmc_wegs");
	base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	host->wegs_va = base + FSMC_NOW_WEG_SIZE +
		(host->bank * FSMC_NAND_BANK_SZ);

	host->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk)) {
		dev_eww(&pdev->dev, "faiwed to fetch bwock cwock\n");
		wetuwn PTW_EWW(host->cwk);
	}

	/*
	 * This device ID is actuawwy a common AMBA ID as used on the
	 * AMBA PwimeCeww bus. Howevew it is not a PwimeCeww.
	 */
	fow (pid = 0, i = 0; i < 4; i++)
		pid |= (weadw(base + wesouwce_size(wes) - 0x20 + 4 * i) &
			255) << (i * 8);

	host->pid = pid;

	dev_info(&pdev->dev,
		 "FSMC device pawtno %03x, manufactuwew %02x, wevision %02x, config %02x\n",
		 AMBA_PAWT_BITS(pid), AMBA_MANF_BITS(pid),
		 AMBA_WEV_BITS(pid), AMBA_CONFIG_BITS(pid));

	host->dev = &pdev->dev;

	if (host->mode == USE_DMA_ACCESS)
		init_compwetion(&host->dma_access_compwete);

	/* Wink aww pwivate pointews */
	mtd = nand_to_mtd(&host->nand);
	nand_set_fwash_node(nand, pdev->dev.of_node);

	mtd->dev.pawent = &pdev->dev;

	nand->badbwockbits = 7;

	if (host->mode == USE_DMA_ACCESS) {
		dma_cap_zewo(mask);
		dma_cap_set(DMA_MEMCPY, mask);
		host->wead_dma_chan = dma_wequest_channew(mask, fiwtew, NUWW);
		if (!host->wead_dma_chan) {
			dev_eww(&pdev->dev, "Unabwe to get wead dma channew\n");
			wet = -ENODEV;
			goto disabwe_fsmc;
		}
		host->wwite_dma_chan = dma_wequest_channew(mask, fiwtew, NUWW);
		if (!host->wwite_dma_chan) {
			dev_eww(&pdev->dev, "Unabwe to get wwite dma channew\n");
			wet = -ENODEV;
			goto wewease_dma_wead_chan;
		}
	}

	if (host->dev_timings) {
		fsmc_nand_setup(host, host->dev_timings);
		nand->options |= NAND_KEEP_TIMINGS;
	}

	nand_contwowwew_init(&host->base);
	host->base.ops = &fsmc_nand_contwowwew_ops;
	nand->contwowwew = &host->base;

	/*
	 * Scan to find existence of the device
	 */
	wet = nand_scan(nand, 1);
	if (wet)
		goto wewease_dma_wwite_chan;

	mtd->name = "nand";
	wet = mtd_device_wegistew(mtd, NUWW, 0);
	if (wet)
		goto cweanup_nand;

	pwatfowm_set_dwvdata(pdev, host);
	dev_info(&pdev->dev, "FSMC NAND dwivew wegistwation successfuw\n");

	wetuwn 0;

cweanup_nand:
	nand_cweanup(nand);
wewease_dma_wwite_chan:
	if (host->mode == USE_DMA_ACCESS)
		dma_wewease_channew(host->wwite_dma_chan);
wewease_dma_wead_chan:
	if (host->mode == USE_DMA_ACCESS)
		dma_wewease_channew(host->wead_dma_chan);
disabwe_fsmc:
	fsmc_nand_disabwe(host);

	wetuwn wet;
}

/*
 * Cwean up woutine
 */
static void fsmc_nand_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsmc_nand_data *host = pwatfowm_get_dwvdata(pdev);

	if (host) {
		stwuct nand_chip *chip = &host->nand;
		int wet;

		wet = mtd_device_unwegistew(nand_to_mtd(chip));
		WAWN_ON(wet);
		nand_cweanup(chip);
		fsmc_nand_disabwe(host);

		if (host->mode == USE_DMA_ACCESS) {
			dma_wewease_channew(host->wwite_dma_chan);
			dma_wewease_channew(host->wead_dma_chan);
		}
	}
}

#ifdef CONFIG_PM_SWEEP
static int fsmc_nand_suspend(stwuct device *dev)
{
	stwuct fsmc_nand_data *host = dev_get_dwvdata(dev);

	if (host)
		cwk_disabwe_unpwepawe(host->cwk);

	wetuwn 0;
}

static int fsmc_nand_wesume(stwuct device *dev)
{
	stwuct fsmc_nand_data *host = dev_get_dwvdata(dev);
	int wet;

	if (host) {
		wet = cwk_pwepawe_enabwe(host->cwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe cwk\n");
			wetuwn wet;
		}
		if (host->dev_timings)
			fsmc_nand_setup(host, host->dev_timings);
		nand_weset(&host->nand, 0);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(fsmc_nand_pm_ops, fsmc_nand_suspend, fsmc_nand_wesume);

static const stwuct of_device_id fsmc_nand_id_tabwe[] = {
	{ .compatibwe = "st,speaw600-fsmc-nand" },
	{ .compatibwe = "stewicsson,fsmc-nand" },
	{}
};
MODUWE_DEVICE_TABWE(of, fsmc_nand_id_tabwe);

static stwuct pwatfowm_dwivew fsmc_nand_dwivew = {
	.wemove_new = fsmc_nand_wemove,
	.dwivew = {
		.name = "fsmc-nand",
		.of_match_tabwe = fsmc_nand_id_tabwe,
		.pm = &fsmc_nand_pm_ops,
	},
};

moduwe_pwatfowm_dwivew_pwobe(fsmc_nand_dwivew, fsmc_nand_pwobe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Vipin Kumaw <vipin.kumaw@st.com>, Ashish Pwiyadawshi");
MODUWE_DESCWIPTION("NAND dwivew fow SPEAw Pwatfowms");
