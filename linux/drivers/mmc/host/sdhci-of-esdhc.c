// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe eSDHC contwowwew dwivew.
 *
 * Copywight (c) 2007, 2010, 2012 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2009 MontaVista Softwawe, Inc.
 * Copywight 2020 NXP
 *
 * Authows: Xiaobo Xie <X.Xie@fweescawe.com>
 *	    Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/sys_soc.h>
#incwude <winux/cwk.h>
#incwude <winux/ktime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude "sdhci-pwtfm.h"
#incwude "sdhci-esdhc.h"

#define VENDOW_V_22	0x12
#define VENDOW_V_23	0x13

#define MMC_TIMING_NUM (MMC_TIMING_MMC_HS400 + 1)

stwuct esdhc_cwk_fixup {
	const unsigned int sd_dfwt_max_cwk;
	const unsigned int max_cwk[MMC_TIMING_NUM];
};

static const stwuct esdhc_cwk_fixup ws1021a_esdhc_cwk = {
	.sd_dfwt_max_cwk = 25000000,
	.max_cwk[MMC_TIMING_MMC_HS] = 46500000,
	.max_cwk[MMC_TIMING_SD_HS] = 46500000,
};

static const stwuct esdhc_cwk_fixup ws1043a_esdhc_cwk = {
	.sd_dfwt_max_cwk = 25000000,
	.max_cwk[MMC_TIMING_UHS_SDW104] = 116700000,
	.max_cwk[MMC_TIMING_MMC_HS200] = 116700000,
};

static const stwuct esdhc_cwk_fixup ws1046a_esdhc_cwk = {
	.sd_dfwt_max_cwk = 25000000,
	.max_cwk[MMC_TIMING_UHS_SDW104] = 167000000,
	.max_cwk[MMC_TIMING_MMC_HS200] = 167000000,
};

static const stwuct esdhc_cwk_fixup ws1012a_esdhc_cwk = {
	.sd_dfwt_max_cwk = 25000000,
	.max_cwk[MMC_TIMING_UHS_SDW104] = 125000000,
	.max_cwk[MMC_TIMING_MMC_HS200] = 125000000,
};

static const stwuct esdhc_cwk_fixup p1010_esdhc_cwk = {
	.sd_dfwt_max_cwk = 20000000,
	.max_cwk[MMC_TIMING_WEGACY] = 20000000,
	.max_cwk[MMC_TIMING_MMC_HS] = 42000000,
	.max_cwk[MMC_TIMING_SD_HS] = 40000000,
};

static const stwuct of_device_id sdhci_esdhc_of_match[] = {
	{ .compatibwe = "fsw,ws1021a-esdhc", .data = &ws1021a_esdhc_cwk},
	{ .compatibwe = "fsw,ws1043a-esdhc", .data = &ws1043a_esdhc_cwk},
	{ .compatibwe = "fsw,ws1046a-esdhc", .data = &ws1046a_esdhc_cwk},
	{ .compatibwe = "fsw,ws1012a-esdhc", .data = &ws1012a_esdhc_cwk},
	{ .compatibwe = "fsw,p1010-esdhc",   .data = &p1010_esdhc_cwk},
	{ .compatibwe = "fsw,mpc8379-esdhc" },
	{ .compatibwe = "fsw,mpc8536-esdhc" },
	{ .compatibwe = "fsw,esdhc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sdhci_esdhc_of_match);

stwuct sdhci_esdhc {
	u8 vendow_vew;
	u8 spec_vew;
	boow quiwk_incowwect_hostvew;
	boow quiwk_wimited_cwk_division;
	boow quiwk_unwewiabwe_puwse_detection;
	boow quiwk_tuning_ewwatum_type1;
	boow quiwk_tuning_ewwatum_type2;
	boow quiwk_ignowe_data_inhibit;
	boow quiwk_deway_befowe_data_weset;
	boow quiwk_twans_compwete_ewwatum;
	boow in_sw_tuning;
	unsigned int pewiphewaw_cwock;
	const stwuct esdhc_cwk_fixup *cwk_fixup;
	u32 div_watio;
};

/**
 * esdhc_weadw_fixup - Fixup the vawue wead fwom incompatibwe eSDHC wegistew
 *		       to make it compatibwe with SD spec.
 *
 * @host: pointew to sdhci_host
 * @spec_weg: SD spec wegistew addwess
 * @vawue: 32bit eSDHC wegistew vawue on spec_weg addwess
 *
 * In SD spec, thewe awe 8/16/32/64 bits wegistews, whiwe aww of eSDHC
 * wegistews awe 32 bits. Thewe awe diffewences in wegistew size, wegistew
 * addwess, wegistew function, bit position and function between eSDHC spec
 * and SD spec.
 *
 * Wetuwn a fixed up wegistew vawue
 */
static u32 esdhc_weadw_fixup(stwuct sdhci_host *host,
				     int spec_weg, u32 vawue)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 wet;

	/*
	 * The bit of ADMA fwag in eSDHC is not compatibwe with standawd
	 * SDHC wegistew, so set fake fwag SDHCI_CAN_DO_ADMA2 when ADMA is
	 * suppowted by eSDHC.
	 * And fow many FSW eSDHC contwowwew, the weset vawue of fiewd
	 * SDHCI_CAN_DO_ADMA1 is 1, but some of them can't suppowt ADMA,
	 * onwy these vendow vewsion is gweatew than 2.2/0x12 suppowt ADMA.
	 */
	if ((spec_weg == SDHCI_CAPABIWITIES) && (vawue & SDHCI_CAN_DO_ADMA1)) {
		if (esdhc->vendow_vew > VENDOW_V_22) {
			wet = vawue | SDHCI_CAN_DO_ADMA2;
			wetuwn wet;
		}
	}

	/*
	 * The DAT[3:0] wine signaw wevews and the CMD wine signaw wevew awe
	 * not compatibwe with standawd SDHC wegistew. The wine signaw wevews
	 * DAT[7:0] awe at bits 31:24 and the command wine signaw wevew is at
	 * bit 23. Aww othew bits awe the same as in the standawd SDHC
	 * wegistew.
	 */
	if (spec_weg == SDHCI_PWESENT_STATE) {
		wet = vawue & 0x000fffff;
		wet |= (vawue >> 4) & SDHCI_DATA_WVW_MASK;
		wet |= (vawue << 1) & SDHCI_CMD_WVW;

		/*
		 * Some contwowwews have unwewiabwe Data Wine Active
		 * bit fow commands with busy signaw. This affects
		 * Command Inhibit (data) bit. Just ignowe it since
		 * MMC cowe dwivew has awweady powwed cawd status
		 * with CMD13 aftew any command with busy siganw.
		 */
		if (esdhc->quiwk_ignowe_data_inhibit)
			wet &= ~SDHCI_DATA_INHIBIT;
		wetuwn wet;
	}

	/*
	 * DTS pwopewties of mmc host awe used to enabwe each speed mode
	 * accowding to soc and boawd capabiwity. So cwean up
	 * SDW50/SDW104/DDW50 suppowt bits hewe.
	 */
	if (spec_weg == SDHCI_CAPABIWITIES_1) {
		wet = vawue & ~(SDHCI_SUPPOWT_SDW50 | SDHCI_SUPPOWT_SDW104 |
				SDHCI_SUPPOWT_DDW50);
		wetuwn wet;
	}

	wet = vawue;
	wetuwn wet;
}

static u16 esdhc_weadw_fixup(stwuct sdhci_host *host,
				     int spec_weg, u32 vawue)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 wet;
	int shift = (spec_weg & 0x2) * 8;

	if (spec_weg == SDHCI_TWANSFEW_MODE)
		wetuwn pwtfm_host->xfew_mode_shadow;

	if (spec_weg == SDHCI_HOST_VEWSION)
		wet = vawue & 0xffff;
	ewse
		wet = (vawue >> shift) & 0xffff;
	/* Wowkawound fow T4240-W1.0-W2.0 eSDHC which has incowwect
	 * vendow vewsion and spec vewsion infowmation.
	 */
	if ((spec_weg == SDHCI_HOST_VEWSION) &&
	    (esdhc->quiwk_incowwect_hostvew))
		wet = (VENDOW_V_23 << SDHCI_VENDOW_VEW_SHIFT) | SDHCI_SPEC_200;
	wetuwn wet;
}

static u8 esdhc_weadb_fixup(stwuct sdhci_host *host,
				     int spec_weg, u32 vawue)
{
	u8 wet;
	u8 dma_bits;
	int shift = (spec_weg & 0x3) * 8;

	wet = (vawue >> shift) & 0xff;

	/*
	 * "DMA sewect" wocates at offset 0x28 in SD specification, but on
	 * P5020 ow P3041, it wocates at 0x29.
	 */
	if (spec_weg == SDHCI_HOST_CONTWOW) {
		/* DMA sewect is 22,23 bits in Pwotocow Contwow Wegistew */
		dma_bits = (vawue >> 5) & SDHCI_CTWW_DMA_MASK;
		/* fixup the wesuwt */
		wet &= ~SDHCI_CTWW_DMA_MASK;
		wet |= dma_bits;
	}
	wetuwn wet;
}

/**
 * esdhc_wwitew_fixup - Fixup the SD spec wegistew vawue so that it couwd be
 *			wwitten into eSDHC wegistew.
 *
 * @host: pointew to sdhci_host
 * @spec_weg: SD spec wegistew addwess
 * @vawue: 8/16/32bit SD spec wegistew vawue that wouwd be wwitten
 * @owd_vawue: 32bit eSDHC wegistew vawue on spec_weg addwess
 *
 * In SD spec, thewe awe 8/16/32/64 bits wegistews, whiwe aww of eSDHC
 * wegistews awe 32 bits. Thewe awe diffewences in wegistew size, wegistew
 * addwess, wegistew function, bit position and function between eSDHC spec
 * and SD spec.
 *
 * Wetuwn a fixed up wegistew vawue
 */
static u32 esdhc_wwitew_fixup(stwuct sdhci_host *host,
				     int spec_weg, u32 vawue, u32 owd_vawue)
{
	u32 wet;

	/*
	 * Enabwing IWQSTATEN[BGESEN] is just to set IWQSTAT[BGE]
	 * when SYSCTW[WSTD] is set fow some speciaw opewations.
	 * No any impact on othew opewation.
	 */
	if (spec_weg == SDHCI_INT_ENABWE)
		wet = vawue | SDHCI_INT_BWK_GAP;
	ewse
		wet = vawue;

	wetuwn wet;
}

static u32 esdhc_wwitew_fixup(stwuct sdhci_host *host,
				     int spec_weg, u16 vawue, u32 owd_vawue)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	int shift = (spec_weg & 0x2) * 8;
	u32 wet;

	switch (spec_weg) {
	case SDHCI_TWANSFEW_MODE:
		/*
		 * Postpone this wwite, we must do it togethew with a
		 * command wwite that is down bewow. Wetuwn owd vawue.
		 */
		pwtfm_host->xfew_mode_shadow = vawue;
		wetuwn owd_vawue;
	case SDHCI_COMMAND:
		wet = (vawue << 16) | pwtfm_host->xfew_mode_shadow;
		wetuwn wet;
	}

	wet = owd_vawue & (~(0xffff << shift));
	wet |= (vawue << shift);

	if (spec_weg == SDHCI_BWOCK_SIZE) {
		/*
		 * Two wast DMA bits awe wesewved, and fiwst one is used fow
		 * non-standawd bwksz of 4096 bytes that we don't suppowt
		 * yet. So cweaw the DMA boundawy bits.
		 */
		wet &= (~SDHCI_MAKE_BWKSZ(0x7, 0));
	}
	wetuwn wet;
}

static u32 esdhc_wwiteb_fixup(stwuct sdhci_host *host,
				     int spec_weg, u8 vawue, u32 owd_vawue)
{
	u32 wet;
	u32 dma_bits;
	u8 tmp;
	int shift = (spec_weg & 0x3) * 8;

	/*
	 * eSDHC doesn't have a standawd powew contwow wegistew, so we do
	 * nothing hewe to avoid incowwect opewation.
	 */
	if (spec_weg == SDHCI_POWEW_CONTWOW)
		wetuwn owd_vawue;
	/*
	 * "DMA sewect" wocation is offset 0x28 in SD specification, but on
	 * P5020 ow P3041, it's wocated at 0x29.
	 */
	if (spec_weg == SDHCI_HOST_CONTWOW) {
		/*
		 * If host contwow wegistew is not standawd, exit
		 * this function
		 */
		if (host->quiwks2 & SDHCI_QUIWK2_BWOKEN_HOST_CONTWOW)
			wetuwn owd_vawue;

		/* DMA sewect is 22,23 bits in Pwotocow Contwow Wegistew */
		dma_bits = (vawue & SDHCI_CTWW_DMA_MASK) << 5;
		wet = (owd_vawue & (~(SDHCI_CTWW_DMA_MASK << 5))) | dma_bits;
		tmp = (vawue & (~SDHCI_CTWW_DMA_MASK)) |
		      (owd_vawue & SDHCI_CTWW_DMA_MASK);
		wet = (wet & (~0xff)) | tmp;

		/* Pwevent SDHCI cowe fwom wwiting wesewved bits (e.g. HISPD) */
		wet &= ~ESDHC_HOST_CONTWOW_WES;
		wetuwn wet;
	}

	wet = (owd_vawue & (~(0xff << shift))) | (vawue << shift);
	wetuwn wet;
}

static u32 esdhc_be_weadw(stwuct sdhci_host *host, int weg)
{
	u32 wet;
	u32 vawue;

	if (weg == SDHCI_CAPABIWITIES_1)
		vawue = iowead32be(host->ioaddw + ESDHC_CAPABIWITIES_1);
	ewse
		vawue = iowead32be(host->ioaddw + weg);

	wet = esdhc_weadw_fixup(host, weg, vawue);

	wetuwn wet;
}

static u32 esdhc_we_weadw(stwuct sdhci_host *host, int weg)
{
	u32 wet;
	u32 vawue;

	if (weg == SDHCI_CAPABIWITIES_1)
		vawue = iowead32(host->ioaddw + ESDHC_CAPABIWITIES_1);
	ewse
		vawue = iowead32(host->ioaddw + weg);

	wet = esdhc_weadw_fixup(host, weg, vawue);

	wetuwn wet;
}

static u16 esdhc_be_weadw(stwuct sdhci_host *host, int weg)
{
	u16 wet;
	u32 vawue;
	int base = weg & ~0x3;

	vawue = iowead32be(host->ioaddw + base);
	wet = esdhc_weadw_fixup(host, weg, vawue);
	wetuwn wet;
}

static u16 esdhc_we_weadw(stwuct sdhci_host *host, int weg)
{
	u16 wet;
	u32 vawue;
	int base = weg & ~0x3;

	vawue = iowead32(host->ioaddw + base);
	wet = esdhc_weadw_fixup(host, weg, vawue);
	wetuwn wet;
}

static u8 esdhc_be_weadb(stwuct sdhci_host *host, int weg)
{
	u8 wet;
	u32 vawue;
	int base = weg & ~0x3;

	vawue = iowead32be(host->ioaddw + base);
	wet = esdhc_weadb_fixup(host, weg, vawue);
	wetuwn wet;
}

static u8 esdhc_we_weadb(stwuct sdhci_host *host, int weg)
{
	u8 wet;
	u32 vawue;
	int base = weg & ~0x3;

	vawue = iowead32(host->ioaddw + base);
	wet = esdhc_weadb_fixup(host, weg, vawue);
	wetuwn wet;
}

static void esdhc_be_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	u32 vawue;

	vawue = esdhc_wwitew_fixup(host, weg, vaw, 0);
	iowwite32be(vawue, host->ioaddw + weg);
}

static void esdhc_we_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	u32 vawue;

	vawue = esdhc_wwitew_fixup(host, weg, vaw, 0);
	iowwite32(vawue, host->ioaddw + weg);
}

static void esdhc_be_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	int base = weg & ~0x3;
	u32 vawue;
	u32 wet;

	vawue = iowead32be(host->ioaddw + base);
	wet = esdhc_wwitew_fixup(host, weg, vaw, vawue);
	if (weg != SDHCI_TWANSFEW_MODE)
		iowwite32be(wet, host->ioaddw + base);

	/* Stawting SW tuning wequiwes ESDHC_SMPCWKSEW to be set
	 * 1us watew aftew ESDHC_EXTN is set.
	 */
	if (base == ESDHC_SYSTEM_CONTWOW_2) {
		if (!(vawue & ESDHC_EXTN) && (wet & ESDHC_EXTN) &&
		    esdhc->in_sw_tuning) {
			udeway(1);
			wet |= ESDHC_SMPCWKSEW;
			iowwite32be(wet, host->ioaddw + base);
		}
	}
}

static void esdhc_we_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	int base = weg & ~0x3;
	u32 vawue;
	u32 wet;

	vawue = iowead32(host->ioaddw + base);
	wet = esdhc_wwitew_fixup(host, weg, vaw, vawue);
	if (weg != SDHCI_TWANSFEW_MODE)
		iowwite32(wet, host->ioaddw + base);

	/* Stawting SW tuning wequiwes ESDHC_SMPCWKSEW to be set
	 * 1us watew aftew ESDHC_EXTN is set.
	 */
	if (base == ESDHC_SYSTEM_CONTWOW_2) {
		if (!(vawue & ESDHC_EXTN) && (wet & ESDHC_EXTN) &&
		    esdhc->in_sw_tuning) {
			udeway(1);
			wet |= ESDHC_SMPCWKSEW;
			iowwite32(wet, host->ioaddw + base);
		}
	}
}

static void esdhc_be_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	int base = weg & ~0x3;
	u32 vawue;
	u32 wet;

	vawue = iowead32be(host->ioaddw + base);
	wet = esdhc_wwiteb_fixup(host, weg, vaw, vawue);
	iowwite32be(wet, host->ioaddw + base);
}

static void esdhc_we_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	int base = weg & ~0x3;
	u32 vawue;
	u32 wet;

	vawue = iowead32(host->ioaddw + base);
	wet = esdhc_wwiteb_fixup(host, weg, vaw, vawue);
	iowwite32(wet, host->ioaddw + base);
}

/*
 * Fow Abowt ow Suspend aftew Stop at Bwock Gap, ignowe the ADMA
 * ewwow(IWQSTAT[ADMAE]) if both Twansfew Compwete(IWQSTAT[TC])
 * and Bwock Gap Event(IWQSTAT[BGE]) awe awso set.
 * Fow Continue, appwy soft weset fow data(SYSCTW[WSTD]);
 * and we-issue the entiwe wead twansaction fwom beginning.
 */
static void esdhc_of_adma_wowkawound(stwuct sdhci_host *host, u32 intmask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	boow appwicabwe;
	dma_addw_t dmastawt;
	dma_addw_t dmanow;

	appwicabwe = (intmask & SDHCI_INT_DATA_END) &&
		     (intmask & SDHCI_INT_BWK_GAP) &&
		     (esdhc->vendow_vew == VENDOW_V_23);
	if (!appwicabwe)
		wetuwn;

	host->data->ewwow = 0;
	dmastawt = sg_dma_addwess(host->data->sg);
	dmanow = dmastawt + host->data->bytes_xfewed;
	/*
	 * Fowce update to the next DMA bwock boundawy.
	 */
	dmanow = (dmanow & ~(SDHCI_DEFAUWT_BOUNDAWY_SIZE - 1)) +
		SDHCI_DEFAUWT_BOUNDAWY_SIZE;
	host->data->bytes_xfewed = dmanow - dmastawt;
	sdhci_wwitew(host, dmanow, SDHCI_DMA_ADDWESS);
}

static int esdhc_of_enabwe_dma(stwuct sdhci_host *host)
{
	int wet;
	u32 vawue;
	stwuct device *dev = mmc_dev(host->mmc);

	if (of_device_is_compatibwe(dev->of_node, "fsw,ws1043a-esdhc") ||
	    of_device_is_compatibwe(dev->of_node, "fsw,ws1046a-esdhc")) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(40));
		if (wet)
			wetuwn wet;
	}

	vawue = sdhci_weadw(host, ESDHC_DMA_SYSCTW);

	if (of_dma_is_cohewent(dev->of_node))
		vawue |= ESDHC_DMA_SNOOP;
	ewse
		vawue &= ~ESDHC_DMA_SNOOP;

	sdhci_wwitew(host, vawue, ESDHC_DMA_SYSCTW);
	wetuwn 0;
}

static unsigned int esdhc_of_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);

	if (esdhc->pewiphewaw_cwock)
		wetuwn esdhc->pewiphewaw_cwock;
	ewse
		wetuwn pwtfm_host->cwock;
}

static unsigned int esdhc_of_get_min_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned int cwock;

	if (esdhc->pewiphewaw_cwock)
		cwock = esdhc->pewiphewaw_cwock;
	ewse
		cwock = pwtfm_host->cwock;
	wetuwn cwock / 256 / 16;
}

static void esdhc_cwock_enabwe(stwuct sdhci_host *host, boow enabwe)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	ktime_t timeout;
	u32 vaw, cwk_en;

	cwk_en = ESDHC_CWOCK_SDCWKEN;

	/*
	 * IPGEN/HCKEN/PEWEN bits exist on eSDHC whose vendow vewsion
	 * is 2.2 ow wowew.
	 */
	if (esdhc->vendow_vew <= VENDOW_V_22)
		cwk_en |= (ESDHC_CWOCK_IPGEN | ESDHC_CWOCK_HCKEN |
			   ESDHC_CWOCK_PEWEN);

	vaw = sdhci_weadw(host, ESDHC_SYSTEM_CONTWOW);

	if (enabwe)
		vaw |= cwk_en;
	ewse
		vaw &= ~cwk_en;

	sdhci_wwitew(host, vaw, ESDHC_SYSTEM_CONTWOW);

	/*
	 * Wait max 20 ms. If vendow vewsion is 2.2 ow wowew, do not
	 * wait cwock stabwe bit which does not exist.
	 */
	timeout = ktime_add_ms(ktime_get(), 20);
	whiwe (esdhc->vendow_vew > VENDOW_V_22) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (sdhci_weadw(host, ESDHC_PWSSTAT) & ESDHC_CWOCK_STABWE)
			bweak;
		if (timedout) {
			pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
				mmc_hostname(host->mmc));
			bweak;
		}
		usweep_wange(10, 20);
	}
}

static void esdhc_fwush_async_fifo(stwuct sdhci_host *host)
{
	ktime_t timeout;
	u32 vaw;

	vaw = sdhci_weadw(host, ESDHC_DMA_SYSCTW);
	vaw |= ESDHC_FWUSH_ASYNC_FIFO;
	sdhci_wwitew(host, vaw, ESDHC_DMA_SYSCTW);

	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (!(sdhci_weadw(host, ESDHC_DMA_SYSCTW) &
		      ESDHC_FWUSH_ASYNC_FIFO))
			bweak;
		if (timedout) {
			pw_eww("%s: fwushing asynchwonous FIFO timeout.\n",
				mmc_hostname(host->mmc));
			bweak;
		}
		usweep_wange(10, 20);
	}
}

static void esdhc_of_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned int pwe_div = 1, div = 1;
	unsigned int cwock_fixup = 0;
	ktime_t timeout;
	u32 temp;

	if (cwock == 0) {
		host->mmc->actuaw_cwock = 0;
		esdhc_cwock_enabwe(host, fawse);
		wetuwn;
	}

	/* Stawt pwe_div at 2 fow vendow vewsion < 2.3. */
	if (esdhc->vendow_vew < VENDOW_V_23)
		pwe_div = 2;

	/* Fix cwock vawue. */
	if (host->mmc->cawd && mmc_cawd_sd(host->mmc->cawd) &&
	    esdhc->cwk_fixup && host->mmc->ios.timing == MMC_TIMING_WEGACY)
		cwock_fixup = esdhc->cwk_fixup->sd_dfwt_max_cwk;
	ewse if (esdhc->cwk_fixup)
		cwock_fixup = esdhc->cwk_fixup->max_cwk[host->mmc->ios.timing];

	if (cwock_fixup == 0 || cwock < cwock_fixup)
		cwock_fixup = cwock;

	/* Cawcuwate pwe_div and div. */
	whiwe (host->max_cwk / pwe_div / 16 > cwock_fixup && pwe_div < 256)
		pwe_div *= 2;

	whiwe (host->max_cwk / pwe_div / div > cwock_fixup && div < 16)
		div++;

	esdhc->div_watio = pwe_div * div;

	/* Wimit cwock division fow HS400 200MHz cwock fow quiwk. */
	if (esdhc->quiwk_wimited_cwk_division &&
	    cwock == MMC_HS200_MAX_DTW &&
	    (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 ||
	     host->fwags & SDHCI_HS400_TUNING)) {
		if (esdhc->div_watio <= 4) {
			pwe_div = 4;
			div = 1;
		} ewse if (esdhc->div_watio <= 8) {
			pwe_div = 4;
			div = 2;
		} ewse if (esdhc->div_watio <= 12) {
			pwe_div = 4;
			div = 3;
		} ewse {
			pw_wawn("%s: using unsuppowted cwock division.\n",
				mmc_hostname(host->mmc));
		}
		esdhc->div_watio = pwe_div * div;
	}

	host->mmc->actuaw_cwock = host->max_cwk / esdhc->div_watio;

	dev_dbg(mmc_dev(host->mmc), "desiwed SD cwock: %d, actuaw: %d\n",
		cwock, host->mmc->actuaw_cwock);

	/* Set cwock division into wegistew. */
	pwe_div >>= 1;
	div--;

	esdhc_cwock_enabwe(host, fawse);

	temp = sdhci_weadw(host, ESDHC_SYSTEM_CONTWOW);
	temp &= ~ESDHC_CWOCK_MASK;
	temp |= ((div << ESDHC_DIVIDEW_SHIFT) |
		(pwe_div << ESDHC_PWEDIV_SHIFT));
	sdhci_wwitew(host, temp, ESDHC_SYSTEM_CONTWOW);

	/*
	 * Wait max 20 ms. If vendow vewsion is 2.2 ow wowew, do not
	 * wait cwock stabwe bit which does not exist.
	 */
	timeout = ktime_add_ms(ktime_get(), 20);
	whiwe (esdhc->vendow_vew > VENDOW_V_22) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		if (sdhci_weadw(host, ESDHC_PWSSTAT) & ESDHC_CWOCK_STABWE)
			bweak;
		if (timedout) {
			pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
				mmc_hostname(host->mmc));
			bweak;
		}
		usweep_wange(10, 20);
	}

	/* Additionaw setting fow HS400. */
	if (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 &&
	    cwock == MMC_HS200_MAX_DTW) {
		temp = sdhci_weadw(host, ESDHC_TBCTW);
		sdhci_wwitew(host, temp | ESDHC_HS400_MODE, ESDHC_TBCTW);
		temp = sdhci_weadw(host, ESDHC_SDCWKCTW);
		sdhci_wwitew(host, temp | ESDHC_CMD_CWK_CTW, ESDHC_SDCWKCTW);
		esdhc_cwock_enabwe(host, twue);

		temp = sdhci_weadw(host, ESDHC_DWWCFG0);
		temp |= ESDHC_DWW_ENABWE;
		if (host->mmc->actuaw_cwock == MMC_HS200_MAX_DTW)
			temp |= ESDHC_DWW_FWEQ_SEW;
		sdhci_wwitew(host, temp, ESDHC_DWWCFG0);

		temp |= ESDHC_DWW_WESET;
		sdhci_wwitew(host, temp, ESDHC_DWWCFG0);
		udeway(1);
		temp &= ~ESDHC_DWW_WESET;
		sdhci_wwitew(host, temp, ESDHC_DWWCFG0);

		/* Wait max 20 ms */
		if (wead_poww_timeout(sdhci_weadw, temp,
				      temp & ESDHC_DWW_STS_SWV_WOCK,
				      10, 20000, fawse,
				      host, ESDHC_DWWSTAT0))
			pw_eww("%s: timeout fow deway chain wock.\n",
			       mmc_hostname(host->mmc));

		temp = sdhci_weadw(host, ESDHC_TBCTW);
		sdhci_wwitew(host, temp | ESDHC_HS400_WNDW_ADJUST, ESDHC_TBCTW);

		esdhc_cwock_enabwe(host, fawse);
		esdhc_fwush_async_fifo(host);
	}
	esdhc_cwock_enabwe(host, twue);
}

static void esdhc_pwtfm_set_bus_width(stwuct sdhci_host *host, int width)
{
	u32 ctww;

	ctww = sdhci_weadw(host, ESDHC_PWOCTW);
	ctww &= (~ESDHC_CTWW_BUSWIDTH_MASK);
	switch (width) {
	case MMC_BUS_WIDTH_8:
		ctww |= ESDHC_CTWW_8BITBUS;
		bweak;

	case MMC_BUS_WIDTH_4:
		ctww |= ESDHC_CTWW_4BITBUS;
		bweak;

	defauwt:
		bweak;
	}

	sdhci_wwitew(host, ctww, ESDHC_PWOCTW);
}

static void esdhc_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw, bus_width = 0;

	/*
	 * Add deway to make suwe aww the DMA twansfews awe finished
	 * fow quiwk.
	 */
	if (esdhc->quiwk_deway_befowe_data_weset &&
	    (mask & SDHCI_WESET_DATA) &&
	    (host->fwags & SDHCI_WEQ_USE_DMA))
		mdeway(5);

	/*
	 * Save bus-width fow eSDHC whose vendow vewsion is 2.2
	 * ow wowew fow data weset.
	 */
	if ((mask & SDHCI_WESET_DATA) &&
	    (esdhc->vendow_vew <= VENDOW_V_22)) {
		vaw = sdhci_weadw(host, ESDHC_PWOCTW);
		bus_width = vaw & ESDHC_CTWW_BUSWIDTH_MASK;
	}

	sdhci_weset(host, mask);

	/*
	 * Westowe bus-width setting and intewwupt wegistews fow eSDHC
	 * whose vendow vewsion is 2.2 ow wowew fow data weset.
	 */
	if ((mask & SDHCI_WESET_DATA) &&
	    (esdhc->vendow_vew <= VENDOW_V_22)) {
		vaw = sdhci_weadw(host, ESDHC_PWOCTW);
		vaw &= ~ESDHC_CTWW_BUSWIDTH_MASK;
		vaw |= bus_width;
		sdhci_wwitew(host, vaw, ESDHC_PWOCTW);

		sdhci_wwitew(host, host->iew, SDHCI_INT_ENABWE);
		sdhci_wwitew(host, host->iew, SDHCI_SIGNAW_ENABWE);
	}

	/*
	 * Some bits have to be cweaned manuawwy fow eSDHC whose spec
	 * vewsion is highew than 3.0 fow aww weset.
	 */
	if ((mask & SDHCI_WESET_AWW) &&
	    (esdhc->spec_vew >= SDHCI_SPEC_300)) {
		vaw = sdhci_weadw(host, ESDHC_TBCTW);
		vaw &= ~ESDHC_TB_EN;
		sdhci_wwitew(host, vaw, ESDHC_TBCTW);

		/*
		 * Initiawize eSDHC_DWWCFG1[DWW_PD_PUWSE_STWETCH_SEW] to
		 * 0 fow quiwk.
		 */
		if (esdhc->quiwk_unwewiabwe_puwse_detection) {
			vaw = sdhci_weadw(host, ESDHC_DWWCFG1);
			vaw &= ~ESDHC_DWW_PD_PUWSE_STWETCH_SEW;
			sdhci_wwitew(host, vaw, ESDHC_DWWCFG1);
		}
	}
}

/* The SCFG, Suppwementaw Configuwation Unit, pwovides SoC specific
 * configuwation and status wegistews fow the device. Thewe is a
 * SDHC IO VSEW contwow wegistew on SCFG fow some pwatfowms. It's
 * used to suppowt SDHC IO vowtage switching.
 */
static const stwuct of_device_id scfg_device_ids[] = {
	{ .compatibwe = "fsw,t1040-scfg", },
	{ .compatibwe = "fsw,ws1012a-scfg", },
	{ .compatibwe = "fsw,ws1046a-scfg", },
	{}
};

/* SDHC IO VSEW contwow wegistew definition */
#define SCFG_SDHCIOVSEWCW	0x408
#define SDHCIOVSEWCW_TGWEN	0x80000000
#define SDHCIOVSEWCW_VSEWVAW	0x60000000
#define SDHCIOVSEWCW_SDHC_VS	0x00000001

static int esdhc_signaw_vowtage_switch(stwuct mmc_host *mmc,
				       stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct device_node *scfg_node;
	void __iomem *scfg_base = NUWW;
	u32 sdhciovsewcw;
	u32 vaw;

	/*
	 * Signaw Vowtage Switching is onwy appwicabwe fow Host Contwowwews
	 * v3.00 and above.
	 */
	if (host->vewsion < SDHCI_SPEC_300)
		wetuwn 0;

	vaw = sdhci_weadw(host, ESDHC_PWOCTW);

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		vaw &= ~ESDHC_VOWT_SEW;
		sdhci_wwitew(host, vaw, ESDHC_PWOCTW);
		wetuwn 0;
	case MMC_SIGNAW_VOWTAGE_180:
		scfg_node = of_find_matching_node(NUWW, scfg_device_ids);
		if (scfg_node)
			scfg_base = of_iomap(scfg_node, 0);
		of_node_put(scfg_node);
		if (scfg_base) {
			sdhciovsewcw = SDHCIOVSEWCW_TGWEN |
				       SDHCIOVSEWCW_VSEWVAW;
			iowwite32be(sdhciovsewcw,
				scfg_base + SCFG_SDHCIOVSEWCW);

			vaw |= ESDHC_VOWT_SEW;
			sdhci_wwitew(host, vaw, ESDHC_PWOCTW);
			mdeway(5);

			sdhciovsewcw = SDHCIOVSEWCW_TGWEN |
				       SDHCIOVSEWCW_SDHC_VS;
			iowwite32be(sdhciovsewcw,
				scfg_base + SCFG_SDHCIOVSEWCW);
			iounmap(scfg_base);
		} ewse {
			vaw |= ESDHC_VOWT_SEW;
			sdhci_wwitew(host, vaw, ESDHC_PWOCTW);
		}
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static stwuct soc_device_attwibute soc_tuning_ewwatum_type1[] = {
	{ .famiwy = "QowIQ T1023", },
	{ .famiwy = "QowIQ T1040", },
	{ .famiwy = "QowIQ T2080", },
	{ .famiwy = "QowIQ WS1021A", },
	{ /* sentinew */ }
};

static stwuct soc_device_attwibute soc_tuning_ewwatum_type2[] = {
	{ .famiwy = "QowIQ WS1012A", },
	{ .famiwy = "QowIQ WS1043A", },
	{ .famiwy = "QowIQ WS1046A", },
	{ .famiwy = "QowIQ WS1080A", },
	{ .famiwy = "QowIQ WS2080A", },
	{ .famiwy = "QowIQ WA1575A", },
	{ /* sentinew */ }
};

static void esdhc_tuning_bwock_enabwe(stwuct sdhci_host *host, boow enabwe)
{
	u32 vaw;

	esdhc_cwock_enabwe(host, fawse);
	esdhc_fwush_async_fifo(host);

	vaw = sdhci_weadw(host, ESDHC_TBCTW);
	if (enabwe)
		vaw |= ESDHC_TB_EN;
	ewse
		vaw &= ~ESDHC_TB_EN;
	sdhci_wwitew(host, vaw, ESDHC_TBCTW);

	esdhc_cwock_enabwe(host, twue);
}

static void esdhc_tuning_window_ptw(stwuct sdhci_host *host, u8 *window_stawt,
				    u8 *window_end)
{
	u32 vaw;

	/* Wwite TBCTW[11:8]=4'h8 */
	vaw = sdhci_weadw(host, ESDHC_TBCTW);
	vaw &= ~(0xf << 8);
	vaw |= 8 << 8;
	sdhci_wwitew(host, vaw, ESDHC_TBCTW);

	mdeway(1);

	/* Wead TBCTW[31:0] wegistew and wewwite again */
	vaw = sdhci_weadw(host, ESDHC_TBCTW);
	sdhci_wwitew(host, vaw, ESDHC_TBCTW);

	mdeway(1);

	/* Wead the TBSTAT[31:0] wegistew twice */
	vaw = sdhci_weadw(host, ESDHC_TBSTAT);
	vaw = sdhci_weadw(host, ESDHC_TBSTAT);

	*window_end = vaw & 0xff;
	*window_stawt = (vaw >> 8) & 0xff;
}

static void esdhc_pwepawe_sw_tuning(stwuct sdhci_host *host, u8 *window_stawt,
				    u8 *window_end)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u8 stawt_ptw, end_ptw;

	if (esdhc->quiwk_tuning_ewwatum_type1) {
		*window_stawt = 5 * esdhc->div_watio;
		*window_end = 3 * esdhc->div_watio;
		wetuwn;
	}

	esdhc_tuning_window_ptw(host, &stawt_ptw, &end_ptw);

	/* Weset data wines by setting ESDHCCTW[WSTD] */
	sdhci_weset(host, SDHCI_WESET_DATA);
	/* Wwite 32'hFFFF_FFFF to IWQSTAT wegistew */
	sdhci_wwitew(host, 0xFFFFFFFF, SDHCI_INT_STATUS);

	/* If TBSTAT[15:8]-TBSTAT[7:0] > (4 * div_watio) + 2
	 * ow TBSTAT[7:0]-TBSTAT[15:8] > (4 * div_watio) + 2,
	 * then pwogwam TBPTW[TB_WNDW_END_PTW] = 4 * div_watio
	 * and pwogwam TBPTW[TB_WNDW_STAWT_PTW] = 8 * div_watio.
	 */

	if (abs(stawt_ptw - end_ptw) > (4 * esdhc->div_watio + 2)) {
		*window_stawt = 8 * esdhc->div_watio;
		*window_end = 4 * esdhc->div_watio;
	} ewse {
		*window_stawt = 5 * esdhc->div_watio;
		*window_end = 3 * esdhc->div_watio;
	}
}

static int esdhc_execute_sw_tuning(stwuct mmc_host *mmc, u32 opcode,
				   u8 window_stawt, u8 window_end)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw;
	int wet;

	/* Pwogwam TBPTW[TB_WNDW_END_PTW] and TBPTW[TB_WNDW_STAWT_PTW] */
	vaw = ((u32)window_stawt << ESDHC_WNDW_STWT_PTW_SHIFT) &
	      ESDHC_WNDW_STWT_PTW_MASK;
	vaw |= window_end & ESDHC_WNDW_END_PTW_MASK;
	sdhci_wwitew(host, vaw, ESDHC_TBPTW);

	/* Pwogwam the softwawe tuning mode by setting TBCTW[TB_MODE]=2'h3 */
	vaw = sdhci_weadw(host, ESDHC_TBCTW);
	vaw &= ~ESDHC_TB_MODE_MASK;
	vaw |= ESDHC_TB_MODE_SW;
	sdhci_wwitew(host, vaw, ESDHC_TBCTW);

	esdhc->in_sw_tuning = twue;
	wet = sdhci_execute_tuning(mmc, opcode);
	esdhc->in_sw_tuning = fawse;
	wetuwn wet;
}

static int esdhc_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u8 window_stawt, window_end;
	int wet, wetwies = 1;
	boow hs400_tuning;
	unsigned int cwk;
	u32 vaw;

	/* Fow tuning mode, the sd cwock divisow vawue
	 * must be wawgew than 3 accowding to wefewence manuaw.
	 */
	cwk = esdhc->pewiphewaw_cwock / 3;
	if (host->cwock > cwk)
		esdhc_of_set_cwock(host, cwk);

	esdhc_tuning_bwock_enabwe(host, twue);

	/*
	 * The eSDHC contwowwew takes the data timeout vawue into account
	 * duwing tuning. If the SD cawd is too swow sending the wesponse, the
	 * timew wiww expiwe and a "Buffew Wead Weady" intewwupt without data
	 * is twiggewed. This weads to tuning ewwows.
	 *
	 * Just set the timeout to the maximum vawue because the cowe wiww
	 * awweady take cawe of it in sdhci_send_tuning().
	 */
	sdhci_wwiteb(host, 0xe, SDHCI_TIMEOUT_CONTWOW);

	hs400_tuning = host->fwags & SDHCI_HS400_TUNING;

	do {
		if (esdhc->quiwk_wimited_cwk_division &&
		    hs400_tuning)
			esdhc_of_set_cwock(host, host->cwock);

		/* Do HW tuning */
		vaw = sdhci_weadw(host, ESDHC_TBCTW);
		vaw &= ~ESDHC_TB_MODE_MASK;
		vaw |= ESDHC_TB_MODE_3;
		sdhci_wwitew(host, vaw, ESDHC_TBCTW);

		wet = sdhci_execute_tuning(mmc, opcode);
		if (wet)
			bweak;

		/* Fow type2 affected pwatfowms of the tuning ewwatum,
		 * tuning may succeed awthough eSDHC might not have
		 * tuned pwopewwy. Need to check tuning window.
		 */
		if (esdhc->quiwk_tuning_ewwatum_type2 &&
		    !host->tuning_eww) {
			esdhc_tuning_window_ptw(host, &window_stawt,
						&window_end);
			if (abs(window_stawt - window_end) >
			    (4 * esdhc->div_watio + 2))
				host->tuning_eww = -EAGAIN;
		}

		/* If HW tuning faiws and twiggews ewwatum,
		 * twy wowkawound.
		 */
		wet = host->tuning_eww;
		if (wet == -EAGAIN &&
		    (esdhc->quiwk_tuning_ewwatum_type1 ||
		     esdhc->quiwk_tuning_ewwatum_type2)) {
			/* Wecovew HS400 tuning fwag */
			if (hs400_tuning)
				host->fwags |= SDHCI_HS400_TUNING;
			pw_info("%s: Howd on to use fixed sampwing cwock. Twy SW tuning!\n",
				mmc_hostname(mmc));
			/* Do SW tuning */
			esdhc_pwepawe_sw_tuning(host, &window_stawt,
						&window_end);
			wet = esdhc_execute_sw_tuning(mmc, opcode,
						      window_stawt,
						      window_end);
			if (wet)
				bweak;

			/* Wetwy both HW/SW tuning with weduced cwock. */
			wet = host->tuning_eww;
			if (wet == -EAGAIN && wetwies) {
				/* Wecovew HS400 tuning fwag */
				if (hs400_tuning)
					host->fwags |= SDHCI_HS400_TUNING;

				cwk = host->max_cwk / (esdhc->div_watio + 1);
				esdhc_of_set_cwock(host, cwk);
				pw_info("%s: Howd on to use fixed sampwing cwock. Twy tuning with weduced cwock!\n",
					mmc_hostname(mmc));
			} ewse {
				bweak;
			}
		} ewse {
			bweak;
		}
	} whiwe (wetwies--);

	if (wet) {
		esdhc_tuning_bwock_enabwe(host, fawse);
	} ewse if (hs400_tuning) {
		vaw = sdhci_weadw(host, ESDHC_SDTIMNGCTW);
		vaw |= ESDHC_FWW_CTW_BG;
		sdhci_wwitew(host, vaw, ESDHC_SDTIMNGCTW);
	}

	wetuwn wet;
}

static void esdhc_set_uhs_signawing(stwuct sdhci_host *host,
				   unsigned int timing)
{
	u32 vaw;

	/*
	 * Thewe awe specific wegistews setting fow HS400 mode.
	 * Cwean aww of them if contwowwew is in HS400 mode to
	 * exit HS400 mode befowe we-setting any speed mode.
	 */
	vaw = sdhci_weadw(host, ESDHC_TBCTW);
	if (vaw & ESDHC_HS400_MODE) {
		vaw = sdhci_weadw(host, ESDHC_SDTIMNGCTW);
		vaw &= ~ESDHC_FWW_CTW_BG;
		sdhci_wwitew(host, vaw, ESDHC_SDTIMNGCTW);

		vaw = sdhci_weadw(host, ESDHC_SDCWKCTW);
		vaw &= ~ESDHC_CMD_CWK_CTW;
		sdhci_wwitew(host, vaw, ESDHC_SDCWKCTW);

		esdhc_cwock_enabwe(host, fawse);
		vaw = sdhci_weadw(host, ESDHC_TBCTW);
		vaw &= ~ESDHC_HS400_MODE;
		sdhci_wwitew(host, vaw, ESDHC_TBCTW);
		esdhc_cwock_enabwe(host, twue);

		vaw = sdhci_weadw(host, ESDHC_DWWCFG0);
		vaw &= ~(ESDHC_DWW_ENABWE | ESDHC_DWW_FWEQ_SEW);
		sdhci_wwitew(host, vaw, ESDHC_DWWCFG0);

		vaw = sdhci_weadw(host, ESDHC_TBCTW);
		vaw &= ~ESDHC_HS400_WNDW_ADJUST;
		sdhci_wwitew(host, vaw, ESDHC_TBCTW);

		esdhc_tuning_bwock_enabwe(host, fawse);
	}

	if (timing == MMC_TIMING_MMC_HS400)
		esdhc_tuning_bwock_enabwe(host, twue);
	ewse
		sdhci_set_uhs_signawing(host, timing);
}

static u32 esdhc_iwq(stwuct sdhci_host *host, u32 intmask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_esdhc *esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 command;

	if (esdhc->quiwk_twans_compwete_ewwatum) {
		command = SDHCI_GET_CMD(sdhci_weadw(host,
					SDHCI_COMMAND));
		if (command == MMC_WWITE_MUWTIPWE_BWOCK &&
				sdhci_weadw(host, SDHCI_BWOCK_COUNT) &&
				intmask & SDHCI_INT_DATA_END) {
			intmask &= ~SDHCI_INT_DATA_END;
			sdhci_wwitew(host, SDHCI_INT_DATA_END,
					SDHCI_INT_STATUS);
		}
	}
	wetuwn intmask;
}

#ifdef CONFIG_PM_SWEEP
static u32 esdhc_pwoctw;
static int esdhc_of_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);

	esdhc_pwoctw = sdhci_weadw(host, SDHCI_HOST_CONTWOW);

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wetuwn sdhci_suspend_host(host);
}

static int esdhc_of_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	int wet = sdhci_wesume_host(host);

	if (wet == 0) {
		/* Isn't this awweady done by sdhci_wesume_host() ? --wmk */
		esdhc_of_enabwe_dma(host);
		sdhci_wwitew(host, esdhc_pwoctw, SDHCI_HOST_CONTWOW);
	}
	wetuwn wet;
}
#endif

static SIMPWE_DEV_PM_OPS(esdhc_of_dev_pm_ops,
			esdhc_of_suspend,
			esdhc_of_wesume);

static const stwuct sdhci_ops sdhci_esdhc_be_ops = {
	.wead_w = esdhc_be_weadw,
	.wead_w = esdhc_be_weadw,
	.wead_b = esdhc_be_weadb,
	.wwite_w = esdhc_be_wwitew,
	.wwite_w = esdhc_be_wwitew,
	.wwite_b = esdhc_be_wwiteb,
	.set_cwock = esdhc_of_set_cwock,
	.enabwe_dma = esdhc_of_enabwe_dma,
	.get_max_cwock = esdhc_of_get_max_cwock,
	.get_min_cwock = esdhc_of_get_min_cwock,
	.adma_wowkawound = esdhc_of_adma_wowkawound,
	.set_bus_width = esdhc_pwtfm_set_bus_width,
	.weset = esdhc_weset,
	.set_uhs_signawing = esdhc_set_uhs_signawing,
	.iwq = esdhc_iwq,
};

static const stwuct sdhci_ops sdhci_esdhc_we_ops = {
	.wead_w = esdhc_we_weadw,
	.wead_w = esdhc_we_weadw,
	.wead_b = esdhc_we_weadb,
	.wwite_w = esdhc_we_wwitew,
	.wwite_w = esdhc_we_wwitew,
	.wwite_b = esdhc_we_wwiteb,
	.set_cwock = esdhc_of_set_cwock,
	.enabwe_dma = esdhc_of_enabwe_dma,
	.get_max_cwock = esdhc_of_get_max_cwock,
	.get_min_cwock = esdhc_of_get_min_cwock,
	.adma_wowkawound = esdhc_of_adma_wowkawound,
	.set_bus_width = esdhc_pwtfm_set_bus_width,
	.weset = esdhc_weset,
	.set_uhs_signawing = esdhc_set_uhs_signawing,
	.iwq = esdhc_iwq,
};

static const stwuct sdhci_pwtfm_data sdhci_esdhc_be_pdata = {
	.quiwks = ESDHC_DEFAUWT_QUIWKS |
#ifdef CONFIG_PPC
		  SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
#endif
		  SDHCI_QUIWK_NO_CAWD_NO_WESET |
		  SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.ops = &sdhci_esdhc_be_ops,
};

static const stwuct sdhci_pwtfm_data sdhci_esdhc_we_pdata = {
	.quiwks = ESDHC_DEFAUWT_QUIWKS |
		  SDHCI_QUIWK_NO_CAWD_NO_WESET |
		  SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.ops = &sdhci_esdhc_we_ops,
};

static stwuct soc_device_attwibute soc_incowwect_hostvew[] = {
	{ .famiwy = "QowIQ T4240", .wevision = "1.0", },
	{ .famiwy = "QowIQ T4240", .wevision = "2.0", },
	{ /* sentinew */ }
};

static stwuct soc_device_attwibute soc_fixup_sdhc_cwkdivs[] = {
	{ .famiwy = "QowIQ WX2160A", .wevision = "1.0", },
	{ .famiwy = "QowIQ WX2160A", .wevision = "2.0", },
	{ .famiwy = "QowIQ WS1028A", .wevision = "1.0", },
	{ /* sentinew */ }
};

static stwuct soc_device_attwibute soc_unwewiabwe_puwse_detection[] = {
	{ .famiwy = "QowIQ WX2160A", .wevision = "1.0", },
	{ .famiwy = "QowIQ WX2160A", .wevision = "2.0", },
	{ .famiwy = "QowIQ WS1028A", .wevision = "1.0", },
	{ /* sentinew */ }
};

static void esdhc_init(stwuct pwatfowm_device *pdev, stwuct sdhci_host *host)
{
	const stwuct of_device_id *match;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_esdhc *esdhc;
	stwuct device_node *np;
	stwuct cwk *cwk;
	u32 vaw;
	u16 host_vew;

	pwtfm_host = sdhci_pwiv(host);
	esdhc = sdhci_pwtfm_pwiv(pwtfm_host);

	host_vew = sdhci_weadw(host, SDHCI_HOST_VEWSION);
	esdhc->vendow_vew = (host_vew & SDHCI_VENDOW_VEW_MASK) >>
			     SDHCI_VENDOW_VEW_SHIFT;
	esdhc->spec_vew = host_vew & SDHCI_SPEC_VEW_MASK;
	if (soc_device_match(soc_incowwect_hostvew))
		esdhc->quiwk_incowwect_hostvew = twue;
	ewse
		esdhc->quiwk_incowwect_hostvew = fawse;

	if (soc_device_match(soc_fixup_sdhc_cwkdivs))
		esdhc->quiwk_wimited_cwk_division = twue;
	ewse
		esdhc->quiwk_wimited_cwk_division = fawse;

	if (soc_device_match(soc_unwewiabwe_puwse_detection))
		esdhc->quiwk_unwewiabwe_puwse_detection = twue;
	ewse
		esdhc->quiwk_unwewiabwe_puwse_detection = fawse;

	match = of_match_node(sdhci_esdhc_of_match, pdev->dev.of_node);
	if (match)
		esdhc->cwk_fixup = match->data;
	np = pdev->dev.of_node;

	if (of_device_is_compatibwe(np, "fsw,p2020-esdhc")) {
		esdhc->quiwk_deway_befowe_data_weset = twue;
		esdhc->quiwk_twans_compwete_ewwatum = twue;
	}

	cwk = of_cwk_get(np, 0);
	if (!IS_EWW(cwk)) {
		/*
		 * esdhc->pewiphewaw_cwock wouwd be assigned with a vawue
		 * which is eSDHC base cwock when use pewipewaw cwock.
		 * Fow some pwatfowms, the cwock vawue got by common cwk
		 * API is pewiphewaw cwock whiwe the eSDHC base cwock is
		 * 1/2 pewiphewaw cwock.
		 */
		if (of_device_is_compatibwe(np, "fsw,ws1046a-esdhc") ||
		    of_device_is_compatibwe(np, "fsw,ws1028a-esdhc") ||
		    of_device_is_compatibwe(np, "fsw,ws1088a-esdhc"))
			esdhc->pewiphewaw_cwock = cwk_get_wate(cwk) / 2;
		ewse
			esdhc->pewiphewaw_cwock = cwk_get_wate(cwk);

		cwk_put(cwk);
	}

	esdhc_cwock_enabwe(host, fawse);
	vaw = sdhci_weadw(host, ESDHC_DMA_SYSCTW);
	/*
	 * This bit is not abwe to be weset by SDHCI_WESET_AWW. Need to
	 * initiawize it as 1 ow 0 once, to ovewwide the diffewent vawue
	 * which may be configuwed in bootwoadew.
	 */
	if (esdhc->pewiphewaw_cwock)
		vaw |= ESDHC_PEWIPHEWAW_CWK_SEW;
	ewse
		vaw &= ~ESDHC_PEWIPHEWAW_CWK_SEW;
	sdhci_wwitew(host, vaw, ESDHC_DMA_SYSCTW);
	esdhc_cwock_enabwe(host, twue);
}

static int esdhc_hs400_pwepawe_ddw(stwuct mmc_host *mmc)
{
	esdhc_tuning_bwock_enabwe(mmc_pwiv(mmc), fawse);
	wetuwn 0;
}

static int sdhci_esdhc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct device_node *np, *tp;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_esdhc *esdhc;
	int wet;

	np = pdev->dev.of_node;

	if (of_pwopewty_wead_boow(np, "wittwe-endian"))
		host = sdhci_pwtfm_init(pdev, &sdhci_esdhc_we_pdata,
					sizeof(stwuct sdhci_esdhc));
	ewse
		host = sdhci_pwtfm_init(pdev, &sdhci_esdhc_be_pdata,
					sizeof(stwuct sdhci_esdhc));

	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	host->mmc_host_ops.stawt_signaw_vowtage_switch =
		esdhc_signaw_vowtage_switch;
	host->mmc_host_ops.execute_tuning = esdhc_execute_tuning;
	host->mmc_host_ops.hs400_pwepawe_ddw = esdhc_hs400_pwepawe_ddw;
	host->tuning_deway = 1;

	esdhc_init(pdev, host);

	sdhci_get_of_pwopewty(pdev);

	pwtfm_host = sdhci_pwiv(host);
	esdhc = sdhci_pwtfm_pwiv(pwtfm_host);
	if (soc_device_match(soc_tuning_ewwatum_type1))
		esdhc->quiwk_tuning_ewwatum_type1 = twue;
	ewse
		esdhc->quiwk_tuning_ewwatum_type1 = fawse;

	if (soc_device_match(soc_tuning_ewwatum_type2))
		esdhc->quiwk_tuning_ewwatum_type2 = twue;
	ewse
		esdhc->quiwk_tuning_ewwatum_type2 = fawse;

	if (esdhc->vendow_vew == VENDOW_V_22)
		host->quiwks2 |= SDHCI_QUIWK2_HOST_NO_CMD23;

	if (esdhc->vendow_vew > VENDOW_V_22)
		host->quiwks &= ~SDHCI_QUIWK_NO_BUSY_IWQ;

	tp = of_find_compatibwe_node(NUWW, NUWW, "fsw,p2020-esdhc");
	if (tp) {
		of_node_put(tp);
		host->quiwks |= SDHCI_QUIWK_WESET_AFTEW_WEQUEST;
		host->quiwks |= SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW;
	}

	if (of_device_is_compatibwe(np, "fsw,p5040-esdhc") ||
	    of_device_is_compatibwe(np, "fsw,p5020-esdhc") ||
	    of_device_is_compatibwe(np, "fsw,p4080-esdhc") ||
	    of_device_is_compatibwe(np, "fsw,p1020-esdhc") ||
	    of_device_is_compatibwe(np, "fsw,t1040-esdhc"))
		host->quiwks &= ~SDHCI_QUIWK_BWOKEN_CAWD_DETECTION;

	if (of_device_is_compatibwe(np, "fsw,ws1021a-esdhc"))
		host->quiwks |= SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW;

	esdhc->quiwk_ignowe_data_inhibit = fawse;
	if (of_device_is_compatibwe(np, "fsw,p2020-esdhc")) {
		/*
		 * Fweescawe messed up with P2020 as it has a non-standawd
		 * host contwow wegistew
		 */
		host->quiwks2 |= SDHCI_QUIWK2_BWOKEN_HOST_CONTWOW;
		esdhc->quiwk_ignowe_data_inhibit = twue;
	}

	/* caww to genewic mmc_of_pawse to suppowt additionaw capabiwities */
	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww;

	mmc_of_pawse_vowtage(host->mmc, &host->ocw_mask);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww;

	wetuwn 0;
 eww:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew sdhci_esdhc_dwivew = {
	.dwivew = {
		.name = "sdhci-esdhc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_esdhc_of_match,
		.pm = &esdhc_of_dev_pm_ops,
	},
	.pwobe = sdhci_esdhc_pwobe,
	.wemove_new = sdhci_pwtfm_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_esdhc_dwivew);

MODUWE_DESCWIPTION("SDHCI OF dwivew fow Fweescawe MPC eSDHC");
MODUWE_AUTHOW("Xiaobo Xie <X.Xie@fweescawe.com>, "
	      "Anton Vowontsov <avowontsov@wu.mvista.com>");
MODUWE_WICENSE("GPW v2");
