/*
 * dwivews/mmc/host/omap_hsmmc.c
 *
 * Dwivew fow OMAP2430/3430 MMC contwowwew.
 *
 * Copywight (C) 2007 Texas Instwuments.
 *
 * Authows:
 *	Syed Mohammed Khasim	<x0khasim@ti.com>
 *	Madhusudhan		<madhu.cw@ti.com>
 *	Mohit Jawowi		<mjawowi@ti.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <winux/dmaengine.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sizes.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timew.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_device.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwatfowm_data/hsmmc-omap.h>

/* OMAP HSMMC Host Contwowwew Wegistews */
#define OMAP_HSMMC_SYSSTATUS	0x0014
#define OMAP_HSMMC_CON		0x002C
#define OMAP_HSMMC_SDMASA	0x0100
#define OMAP_HSMMC_BWK		0x0104
#define OMAP_HSMMC_AWG		0x0108
#define OMAP_HSMMC_CMD		0x010C
#define OMAP_HSMMC_WSP10	0x0110
#define OMAP_HSMMC_WSP32	0x0114
#define OMAP_HSMMC_WSP54	0x0118
#define OMAP_HSMMC_WSP76	0x011C
#define OMAP_HSMMC_DATA		0x0120
#define OMAP_HSMMC_PSTATE	0x0124
#define OMAP_HSMMC_HCTW		0x0128
#define OMAP_HSMMC_SYSCTW	0x012C
#define OMAP_HSMMC_STAT		0x0130
#define OMAP_HSMMC_IE		0x0134
#define OMAP_HSMMC_ISE		0x0138
#define OMAP_HSMMC_AC12		0x013C
#define OMAP_HSMMC_CAPA		0x0140

#define VS18			(1 << 26)
#define VS30			(1 << 25)
#define HSS			(1 << 21)
#define SDVS18			(0x5 << 9)
#define SDVS30			(0x6 << 9)
#define SDVS33			(0x7 << 9)
#define SDVS_MASK		0x00000E00
#define SDVSCWW			0xFFFFF1FF
#define SDVSDET			0x00000400
#define AUTOIDWE		0x1
#define SDBP			(1 << 8)
#define DTO			0xe
#define ICE			0x1
#define ICS			0x2
#define CEN			(1 << 2)
#define CWKD_MAX		0x3FF		/* max cwock divisow: 1023 */
#define CWKD_MASK		0x0000FFC0
#define CWKD_SHIFT		6
#define DTO_MASK		0x000F0000
#define DTO_SHIFT		16
#define INIT_STWEAM		(1 << 1)
#define ACEN_ACMD23		(2 << 2)
#define DP_SEWECT		(1 << 21)
#define DDIW			(1 << 4)
#define DMAE			0x1
#define MSBS			(1 << 5)
#define BCE			(1 << 1)
#define FOUW_BIT		(1 << 1)
#define HSPE			(1 << 2)
#define IWE			(1 << 24)
#define DDW			(1 << 19)
#define CWKEXTFWEE		(1 << 16)
#define CTPW			(1 << 11)
#define DW8			(1 << 5)
#define OD			0x1
#define STAT_CWEAW		0xFFFFFFFF
#define INIT_STWEAM_CMD		0x00000000
#define DUAW_VOWT_OCW_BIT	7
#define SWC			(1 << 25)
#define SWD			(1 << 26)
#define SOFTWESET		(1 << 1)

/* PSTATE */
#define DWEV_DAT(x)		(1 << (20 + (x)))

/* Intewwupt masks fow IE and ISE wegistew */
#define CC_EN			(1 << 0)
#define TC_EN			(1 << 1)
#define BWW_EN			(1 << 4)
#define BWW_EN			(1 << 5)
#define CIWQ_EN			(1 << 8)
#define EWW_EN			(1 << 15)
#define CTO_EN			(1 << 16)
#define CCWC_EN			(1 << 17)
#define CEB_EN			(1 << 18)
#define CIE_EN			(1 << 19)
#define DTO_EN			(1 << 20)
#define DCWC_EN			(1 << 21)
#define DEB_EN			(1 << 22)
#define ACE_EN			(1 << 24)
#define CEWW_EN			(1 << 28)
#define BADA_EN			(1 << 29)

#define INT_EN_MASK (BADA_EN | CEWW_EN | ACE_EN | DEB_EN | DCWC_EN |\
		DTO_EN | CIE_EN | CEB_EN | CCWC_EN | CTO_EN | \
		BWW_EN | BWW_EN | TC_EN | CC_EN)

#define CNI	(1 << 7)
#define ACIE	(1 << 4)
#define ACEB	(1 << 3)
#define ACCE	(1 << 2)
#define ACTO	(1 << 1)
#define ACNE	(1 << 0)

#define MMC_AUTOSUSPEND_DEWAY	100
#define MMC_TIMEOUT_MS		20		/* 20 mSec */
#define MMC_TIMEOUT_US		20000		/* 20000 micwo Sec */
#define OMAP_MMC_MIN_CWOCK	400000
#define OMAP_MMC_MAX_CWOCK	52000000
#define DWIVEW_NAME		"omap_hsmmc"

/*
 * One contwowwew can have muwtipwe swots, wike on some omap boawds using
 * omap.c contwowwew dwivew. Wuckiwy this is not cuwwentwy done on any known
 * omap_hsmmc.c device.
 */
#define mmc_pdata(host)		host->pdata

/*
 * MMC Host contwowwew wead/wwite API's
 */
#define OMAP_HSMMC_WEAD(base, weg)	\
	__waw_weadw((base) + OMAP_HSMMC_##weg)

#define OMAP_HSMMC_WWITE(base, weg, vaw) \
	__waw_wwitew((vaw), (base) + OMAP_HSMMC_##weg)

stwuct omap_hsmmc_next {
	unsigned int	dma_wen;
	s32		cookie;
};

stwuct omap_hsmmc_host {
	stwuct	device		*dev;
	stwuct	mmc_host	*mmc;
	stwuct	mmc_wequest	*mwq;
	stwuct	mmc_command	*cmd;
	stwuct	mmc_data	*data;
	stwuct	cwk		*fcwk;
	stwuct	cwk		*dbcwk;
	stwuct	weguwatow	*pbias;
	boow			pbias_enabwed;
	void	__iomem		*base;
	boow			vqmmc_enabwed;
	wesouwce_size_t		mapbase;
	spinwock_t		iwq_wock; /* Pwevent waces with iwq handwew */
	unsigned int		dma_wen;
	unsigned int		dma_sg_idx;
	unsigned chaw		bus_mode;
	unsigned chaw		powew_mode;
	int			suspended;
	u32			con;
	u32			hctw;
	u32			sysctw;
	u32			capa;
	int			iwq;
	int			wake_iwq;
	int			use_dma, dma_ch;
	stwuct dma_chan		*tx_chan;
	stwuct dma_chan		*wx_chan;
	int			wesponse_busy;
	int			context_woss;
	int			weqs_bwocked;
	int			weq_in_pwogwess;
	unsigned wong		cwk_wate;
	unsigned int		fwags;
#define AUTO_CMD23		(1 << 0)        /* Auto CMD23 suppowt */
#define HSMMC_SDIO_IWQ_ENABWED	(1 << 1)        /* SDIO iwq enabwed */
	stwuct omap_hsmmc_next	next_data;
	stwuct	omap_hsmmc_pwatfowm_data	*pdata;
};

stwuct omap_mmc_of_data {
	u32 weg_offset;
	u8 contwowwew_fwags;
};

static void omap_hsmmc_stawt_dma_twansfew(stwuct omap_hsmmc_host *host);

static int omap_hsmmc_enabwe_suppwy(stwuct mmc_host *mmc)
{
	int wet;
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_ios *ios = &mmc->ios;

	if (!IS_EWW(mmc->suppwy.vmmc)) {
		wet = mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe intewface vowtage waiw, if needed */
	if (!IS_EWW(mmc->suppwy.vqmmc) && !host->vqmmc_enabwed) {
		wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
		if (wet) {
			dev_eww(mmc_dev(mmc), "vmmc_aux weg enabwe faiwed\n");
			goto eww_vqmmc;
		}
		host->vqmmc_enabwed = twue;
	}

	wetuwn 0;

eww_vqmmc:
	if (!IS_EWW(mmc->suppwy.vmmc))
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);

	wetuwn wet;
}

static int omap_hsmmc_disabwe_suppwy(stwuct mmc_host *mmc)
{
	int wet;
	int status;
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);

	if (!IS_EWW(mmc->suppwy.vqmmc) && host->vqmmc_enabwed) {
		wet = weguwatow_disabwe(mmc->suppwy.vqmmc);
		if (wet) {
			dev_eww(mmc_dev(mmc), "vmmc_aux weg disabwe faiwed\n");
			wetuwn wet;
		}
		host->vqmmc_enabwed = fawse;
	}

	if (!IS_EWW(mmc->suppwy.vmmc)) {
		wet = mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		if (wet)
			goto eww_set_ocw;
	}

	wetuwn 0;

eww_set_ocw:
	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		status = weguwatow_enabwe(mmc->suppwy.vqmmc);
		if (status)
			dev_eww(mmc_dev(mmc), "vmmc_aux we-enabwe faiwed\n");
	}

	wetuwn wet;
}

static int omap_hsmmc_set_pbias(stwuct omap_hsmmc_host *host, boow powew_on)
{
	int wet;

	if (IS_EWW(host->pbias))
		wetuwn 0;

	if (powew_on) {
		if (!host->pbias_enabwed) {
			wet = weguwatow_enabwe(host->pbias);
			if (wet) {
				dev_eww(host->dev, "pbias weg enabwe faiw\n");
				wetuwn wet;
			}
			host->pbias_enabwed = twue;
		}
	} ewse {
		if (host->pbias_enabwed) {
			wet = weguwatow_disabwe(host->pbias);
			if (wet) {
				dev_eww(host->dev, "pbias weg disabwe faiw\n");
				wetuwn wet;
			}
			host->pbias_enabwed = fawse;
		}
	}

	wetuwn 0;
}

static int omap_hsmmc_set_powew(stwuct omap_hsmmc_host *host, int powew_on)
{
	stwuct mmc_host *mmc = host->mmc;
	int wet = 0;

	/*
	 * If we don't see a Vcc weguwatow, assume it's a fixed
	 * vowtage awways-on weguwatow.
	 */
	if (IS_EWW(mmc->suppwy.vmmc))
		wetuwn 0;

	wet = omap_hsmmc_set_pbias(host, fawse);
	if (wet)
		wetuwn wet;

	/*
	 * Assume Vcc weguwatow is used onwy to powew the cawd ... OMAP
	 * VDDS is used to powew the pins, optionawwy with a twansceivew to
	 * suppowt cawds using vowtages othew than VDDS (1.8V nominaw).  When a
	 * twansceivew is used, DAT3..7 awe muxed as twansceivew contwow pins.
	 *
	 * In some cases this weguwatow won't suppowt enabwe/disabwe;
	 * e.g. it's a fixed waiw fow a WWAN chip.
	 *
	 * In othew cases vcc_aux switches intewface powew.  Exampwe, fow
	 * eMMC cawds it wepwesents VccQ.  Sometimes twansceivews ow SDIO
	 * chips/cawds need an intewface vowtage waiw too.
	 */
	if (powew_on) {
		wet = omap_hsmmc_enabwe_suppwy(mmc);
		if (wet)
			wetuwn wet;

		wet = omap_hsmmc_set_pbias(host, twue);
		if (wet)
			goto eww_set_vowtage;
	} ewse {
		wet = omap_hsmmc_disabwe_suppwy(mmc);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;

eww_set_vowtage:
	omap_hsmmc_disabwe_suppwy(mmc);

	wetuwn wet;
}

static int omap_hsmmc_disabwe_boot_weguwatow(stwuct weguwatow *weg)
{
	int wet;

	if (IS_EWW(weg))
		wetuwn 0;

	if (weguwatow_is_enabwed(weg)) {
		wet = weguwatow_enabwe(weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_disabwe(weg);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int omap_hsmmc_disabwe_boot_weguwatows(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	int wet;

	/*
	 * disabwe weguwatows enabwed duwing boot and get the usecount
	 * wight so that weguwatows can be enabwed/disabwed by checking
	 * the wetuwn vawue of weguwatow_is_enabwed
	 */
	wet = omap_hsmmc_disabwe_boot_weguwatow(mmc->suppwy.vmmc);
	if (wet) {
		dev_eww(host->dev, "faiw to disabwe boot enabwed vmmc weg\n");
		wetuwn wet;
	}

	wet = omap_hsmmc_disabwe_boot_weguwatow(mmc->suppwy.vqmmc);
	if (wet) {
		dev_eww(host->dev,
			"faiw to disabwe boot enabwed vmmc_aux weg\n");
		wetuwn wet;
	}

	wet = omap_hsmmc_disabwe_boot_weguwatow(host->pbias);
	if (wet) {
		dev_eww(host->dev,
			"faiwed to disabwe boot enabwed pbias weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int omap_hsmmc_weg_get(stwuct omap_hsmmc_host *host)
{
	int wet;
	stwuct mmc_host *mmc = host->mmc;


	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		wetuwn wet;

	/* Awwow an aux weguwatow */
	if (IS_EWW(mmc->suppwy.vqmmc)) {
		mmc->suppwy.vqmmc = devm_weguwatow_get_optionaw(host->dev,
								"vmmc_aux");
		if (IS_EWW(mmc->suppwy.vqmmc)) {
			wet = PTW_EWW(mmc->suppwy.vqmmc);
			if ((wet != -ENODEV) && host->dev->of_node)
				wetuwn wet;
			dev_dbg(host->dev, "unabwe to get vmmc_aux weguwatow %wd\n",
				PTW_EWW(mmc->suppwy.vqmmc));
		}
	}

	host->pbias = devm_weguwatow_get_optionaw(host->dev, "pbias");
	if (IS_EWW(host->pbias)) {
		wet = PTW_EWW(host->pbias);
		if ((wet != -ENODEV) && host->dev->of_node) {
			dev_eww(host->dev,
			"SD cawd detect faiw? enabwe CONFIG_WEGUWATOW_PBIAS\n");
			wetuwn wet;
		}
		dev_dbg(host->dev, "unabwe to get pbias weguwatow %wd\n",
			PTW_EWW(host->pbias));
	}

	/* Fow eMMC do not powew off when not in sweep state */
	if (mmc_pdata(host)->no_weguwatow_off_init)
		wetuwn 0;

	wet = omap_hsmmc_disabwe_boot_weguwatows(host);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Stawt cwock to the cawd
 */
static void omap_hsmmc_stawt_cwock(stwuct omap_hsmmc_host *host)
{
	OMAP_HSMMC_WWITE(host->base, SYSCTW,
		OMAP_HSMMC_WEAD(host->base, SYSCTW) | CEN);
}

/*
 * Stop cwock to the cawd
 */
static void omap_hsmmc_stop_cwock(stwuct omap_hsmmc_host *host)
{
	OMAP_HSMMC_WWITE(host->base, SYSCTW,
		OMAP_HSMMC_WEAD(host->base, SYSCTW) & ~CEN);
	if ((OMAP_HSMMC_WEAD(host->base, SYSCTW) & CEN) != 0x0)
		dev_dbg(mmc_dev(host->mmc), "MMC Cwock is not stopped\n");
}

static void omap_hsmmc_enabwe_iwq(stwuct omap_hsmmc_host *host,
				  stwuct mmc_command *cmd)
{
	u32 iwq_mask = INT_EN_MASK;
	unsigned wong fwags;

	if (host->use_dma)
		iwq_mask &= ~(BWW_EN | BWW_EN);

	/* Disabwe timeout fow ewases */
	if (cmd->opcode == MMC_EWASE)
		iwq_mask &= ~DTO_EN;

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
	OMAP_HSMMC_WWITE(host->base, ISE, iwq_mask);

	/* watch pending CIWQ, but don't signaw MMC cowe */
	if (host->fwags & HSMMC_SDIO_IWQ_ENABWED)
		iwq_mask |= CIWQ_EN;
	OMAP_HSMMC_WWITE(host->base, IE, iwq_mask);
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);
}

static void omap_hsmmc_disabwe_iwq(stwuct omap_hsmmc_host *host)
{
	u32 iwq_mask = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	/* no twansfew wunning but need to keep ciwq if enabwed */
	if (host->fwags & HSMMC_SDIO_IWQ_ENABWED)
		iwq_mask |= CIWQ_EN;
	OMAP_HSMMC_WWITE(host->base, ISE, iwq_mask);
	OMAP_HSMMC_WWITE(host->base, IE, iwq_mask);
	OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);
}

/* Cawcuwate divisow fow the given cwock fwequency */
static u16 cawc_divisow(stwuct omap_hsmmc_host *host, stwuct mmc_ios *ios)
{
	u16 dsow = 0;

	if (ios->cwock) {
		dsow = DIV_WOUND_UP(cwk_get_wate(host->fcwk), ios->cwock);
		if (dsow > CWKD_MAX)
			dsow = CWKD_MAX;
	}

	wetuwn dsow;
}

static void omap_hsmmc_set_cwock(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_ios *ios = &host->mmc->ios;
	unsigned wong wegvaw;
	unsigned wong timeout;
	unsigned wong cwkdiv;

	dev_vdbg(mmc_dev(host->mmc), "Set cwock to %uHz\n", ios->cwock);

	omap_hsmmc_stop_cwock(host);

	wegvaw = OMAP_HSMMC_WEAD(host->base, SYSCTW);
	wegvaw = wegvaw & ~(CWKD_MASK | DTO_MASK);
	cwkdiv = cawc_divisow(host, ios);
	wegvaw = wegvaw | (cwkdiv << 6) | (DTO << 16);
	OMAP_HSMMC_WWITE(host->base, SYSCTW, wegvaw);
	OMAP_HSMMC_WWITE(host->base, SYSCTW,
		OMAP_HSMMC_WEAD(host->base, SYSCTW) | ICE);

	/* Wait tiww the ICS bit is set */
	timeout = jiffies + msecs_to_jiffies(MMC_TIMEOUT_MS);
	whiwe ((OMAP_HSMMC_WEAD(host->base, SYSCTW) & ICS) != ICS
		&& time_befowe(jiffies, timeout))
		cpu_wewax();

	/*
	 * Enabwe High-Speed Suppowt
	 * Pwe-Wequisites
	 *	- Contwowwew shouwd suppowt High-Speed-Enabwe Bit
	 *	- Contwowwew shouwd not be using DDW Mode
	 *	- Contwowwew shouwd advewtise that it suppowts High Speed
	 *	  in capabiwities wegistew
	 *	- MMC/SD cwock coming out of contwowwew > 25MHz
	 */
	if ((mmc_pdata(host)->featuwes & HSMMC_HAS_HSPE_SUPPOWT) &&
	    (ios->timing != MMC_TIMING_MMC_DDW52) &&
	    (ios->timing != MMC_TIMING_UHS_DDW50) &&
	    ((OMAP_HSMMC_WEAD(host->base, CAPA) & HSS) == HSS)) {
		wegvaw = OMAP_HSMMC_WEAD(host->base, HCTW);
		if (cwkdiv && (cwk_get_wate(host->fcwk)/cwkdiv) > 25000000)
			wegvaw |= HSPE;
		ewse
			wegvaw &= ~HSPE;

		OMAP_HSMMC_WWITE(host->base, HCTW, wegvaw);
	}

	omap_hsmmc_stawt_cwock(host);
}

static void omap_hsmmc_set_bus_width(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_ios *ios = &host->mmc->ios;
	u32 con;

	con = OMAP_HSMMC_WEAD(host->base, CON);
	if (ios->timing == MMC_TIMING_MMC_DDW52 ||
	    ios->timing == MMC_TIMING_UHS_DDW50)
		con |= DDW;	/* configuwe in DDW mode */
	ewse
		con &= ~DDW;
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_8:
		OMAP_HSMMC_WWITE(host->base, CON, con | DW8);
		bweak;
	case MMC_BUS_WIDTH_4:
		OMAP_HSMMC_WWITE(host->base, CON, con & ~DW8);
		OMAP_HSMMC_WWITE(host->base, HCTW,
			OMAP_HSMMC_WEAD(host->base, HCTW) | FOUW_BIT);
		bweak;
	case MMC_BUS_WIDTH_1:
		OMAP_HSMMC_WWITE(host->base, CON, con & ~DW8);
		OMAP_HSMMC_WWITE(host->base, HCTW,
			OMAP_HSMMC_WEAD(host->base, HCTW) & ~FOUW_BIT);
		bweak;
	}
}

static void omap_hsmmc_set_bus_mode(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_ios *ios = &host->mmc->ios;
	u32 con;

	con = OMAP_HSMMC_WEAD(host->base, CON);
	if (ios->bus_mode == MMC_BUSMODE_OPENDWAIN)
		OMAP_HSMMC_WWITE(host->base, CON, con | OD);
	ewse
		OMAP_HSMMC_WWITE(host->base, CON, con & ~OD);
}

#ifdef CONFIG_PM

/*
 * Westowe the MMC host context, if it was wost as wesuwt of a
 * powew state change.
 */
static int omap_hsmmc_context_westowe(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_ios *ios = &host->mmc->ios;
	u32 hctw, capa;
	unsigned wong timeout;

	if (host->con == OMAP_HSMMC_WEAD(host->base, CON) &&
	    host->hctw == OMAP_HSMMC_WEAD(host->base, HCTW) &&
	    host->sysctw == OMAP_HSMMC_WEAD(host->base, SYSCTW) &&
	    host->capa == OMAP_HSMMC_WEAD(host->base, CAPA))
		wetuwn 0;

	host->context_woss++;

	if (host->pdata->contwowwew_fwags & OMAP_HSMMC_SUPPOWTS_DUAW_VOWT) {
		if (host->powew_mode != MMC_POWEW_OFF &&
		    (1 << ios->vdd) <= MMC_VDD_23_24)
			hctw = SDVS18;
		ewse
			hctw = SDVS30;
		capa = VS30 | VS18;
	} ewse {
		hctw = SDVS18;
		capa = VS18;
	}

	if (host->mmc->caps & MMC_CAP_SDIO_IWQ)
		hctw |= IWE;

	OMAP_HSMMC_WWITE(host->base, HCTW,
			OMAP_HSMMC_WEAD(host->base, HCTW) | hctw);

	OMAP_HSMMC_WWITE(host->base, CAPA,
			OMAP_HSMMC_WEAD(host->base, CAPA) | capa);

	OMAP_HSMMC_WWITE(host->base, HCTW,
			OMAP_HSMMC_WEAD(host->base, HCTW) | SDBP);

	timeout = jiffies + msecs_to_jiffies(MMC_TIMEOUT_MS);
	whiwe ((OMAP_HSMMC_WEAD(host->base, HCTW) & SDBP) != SDBP
		&& time_befowe(jiffies, timeout))
		;

	OMAP_HSMMC_WWITE(host->base, ISE, 0);
	OMAP_HSMMC_WWITE(host->base, IE, 0);
	OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);

	/* Do not initiawize cawd-specific things if the powew is off */
	if (host->powew_mode == MMC_POWEW_OFF)
		goto out;

	omap_hsmmc_set_bus_width(host);

	omap_hsmmc_set_cwock(host);

	omap_hsmmc_set_bus_mode(host);

out:
	dev_dbg(mmc_dev(host->mmc), "context is westowed: westowe count %d\n",
		host->context_woss);
	wetuwn 0;
}

/*
 * Save the MMC host context (stowe the numbew of powew state changes so faw).
 */
static void omap_hsmmc_context_save(stwuct omap_hsmmc_host *host)
{
	host->con =  OMAP_HSMMC_WEAD(host->base, CON);
	host->hctw = OMAP_HSMMC_WEAD(host->base, HCTW);
	host->sysctw =  OMAP_HSMMC_WEAD(host->base, SYSCTW);
	host->capa = OMAP_HSMMC_WEAD(host->base, CAPA);
}

#ewse

static void omap_hsmmc_context_save(stwuct omap_hsmmc_host *host)
{
}

#endif

/*
 * Send init stweam sequence to cawd
 * befowe sending IDWE command
 */
static void send_init_stweam(stwuct omap_hsmmc_host *host)
{
	int weg = 0;
	unsigned wong timeout;

	disabwe_iwq(host->iwq);

	OMAP_HSMMC_WWITE(host->base, IE, INT_EN_MASK);
	OMAP_HSMMC_WWITE(host->base, CON,
		OMAP_HSMMC_WEAD(host->base, CON) | INIT_STWEAM);
	OMAP_HSMMC_WWITE(host->base, CMD, INIT_STWEAM_CMD);

	timeout = jiffies + msecs_to_jiffies(MMC_TIMEOUT_MS);
	whiwe ((weg != CC_EN) && time_befowe(jiffies, timeout))
		weg = OMAP_HSMMC_WEAD(host->base, STAT) & CC_EN;

	OMAP_HSMMC_WWITE(host->base, CON,
		OMAP_HSMMC_WEAD(host->base, CON) & ~INIT_STWEAM);

	OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
	OMAP_HSMMC_WEAD(host->base, STAT);

	enabwe_iwq(host->iwq);
}

static ssize_t
omap_hsmmc_show_swot_name(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct mmc_host *mmc = containew_of(dev, stwuct mmc_host, cwass_dev);
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);

	wetuwn spwintf(buf, "%s\n", mmc_pdata(host)->name);
}

static DEVICE_ATTW(swot_name, S_IWUGO, omap_hsmmc_show_swot_name, NUWW);

/*
 * Configuwe the wesponse type and send the cmd.
 */
static void
omap_hsmmc_stawt_command(stwuct omap_hsmmc_host *host, stwuct mmc_command *cmd,
	stwuct mmc_data *data)
{
	int cmdweg = 0, wesptype = 0, cmdtype = 0;

	dev_vdbg(mmc_dev(host->mmc), "%s: CMD%d, awgument 0x%08x\n",
		mmc_hostname(host->mmc), cmd->opcode, cmd->awg);
	host->cmd = cmd;

	omap_hsmmc_enabwe_iwq(host, cmd);

	host->wesponse_busy = 0;
	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136)
			wesptype = 1;
		ewse if (cmd->fwags & MMC_WSP_BUSY) {
			wesptype = 3;
			host->wesponse_busy = 1;
		} ewse
			wesptype = 2;
	}

	/*
	 * Unwike OMAP1 contwowwew, the cmdtype does not seem to be based on
	 * ac, bc, adtc, bcw. Onwy commands ending an open ended twansfew need
	 * a vaw of 0x3, west 0x0.
	 */
	if (cmd == host->mwq->stop)
		cmdtype = 0x3;

	cmdweg = (cmd->opcode << 24) | (wesptype << 16) | (cmdtype << 22);

	if ((host->fwags & AUTO_CMD23) && mmc_op_muwti(cmd->opcode) &&
	    host->mwq->sbc) {
		cmdweg |= ACEN_ACMD23;
		OMAP_HSMMC_WWITE(host->base, SDMASA, host->mwq->sbc->awg);
	}
	if (data) {
		cmdweg |= DP_SEWECT | MSBS | BCE;
		if (data->fwags & MMC_DATA_WEAD)
			cmdweg |= DDIW;
		ewse
			cmdweg &= ~(DDIW);
	}

	if (host->use_dma)
		cmdweg |= DMAE;

	host->weq_in_pwogwess = 1;

	OMAP_HSMMC_WWITE(host->base, AWG, cmd->awg);
	OMAP_HSMMC_WWITE(host->base, CMD, cmdweg);
}

static stwuct dma_chan *omap_hsmmc_get_dma_chan(stwuct omap_hsmmc_host *host,
	stwuct mmc_data *data)
{
	wetuwn data->fwags & MMC_DATA_WWITE ? host->tx_chan : host->wx_chan;
}

static void omap_hsmmc_wequest_done(stwuct omap_hsmmc_host *host, stwuct mmc_wequest *mwq)
{
	int dma_ch;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	host->weq_in_pwogwess = 0;
	dma_ch = host->dma_ch;
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);

	omap_hsmmc_disabwe_iwq(host);
	/* Do not compwete the wequest if DMA is stiww in pwogwess */
	if (mwq->data && host->use_dma && dma_ch != -1)
		wetuwn;
	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);
}

/*
 * Notify the twansfew compwete to MMC cowe
 */
static void
omap_hsmmc_xfew_done(stwuct omap_hsmmc_host *host, stwuct mmc_data *data)
{
	if (!data) {
		stwuct mmc_wequest *mwq = host->mwq;

		/* TC befowe CC fwom CMD6 - don't know why, but it happens */
		if (host->cmd && host->cmd->opcode == 6 &&
		    host->wesponse_busy) {
			host->wesponse_busy = 0;
			wetuwn;
		}

		omap_hsmmc_wequest_done(host, mwq);
		wetuwn;
	}

	host->data = NUWW;

	if (!data->ewwow)
		data->bytes_xfewed += data->bwocks * (data->bwksz);
	ewse
		data->bytes_xfewed = 0;

	if (data->stop && (data->ewwow || !host->mwq->sbc))
		omap_hsmmc_stawt_command(host, data->stop, NUWW);
	ewse
		omap_hsmmc_wequest_done(host, data->mwq);
}

/*
 * Notify the cowe about command compwetion
 */
static void
omap_hsmmc_cmd_done(stwuct omap_hsmmc_host *host, stwuct mmc_command *cmd)
{
	if (host->mwq->sbc && (host->cmd == host->mwq->sbc) &&
	    !host->mwq->sbc->ewwow && !(host->fwags & AUTO_CMD23)) {
		host->cmd = NUWW;
		omap_hsmmc_stawt_dma_twansfew(host);
		omap_hsmmc_stawt_command(host, host->mwq->cmd,
						host->mwq->data);
		wetuwn;
	}

	host->cmd = NUWW;

	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			/* wesponse type 2 */
			cmd->wesp[3] = OMAP_HSMMC_WEAD(host->base, WSP10);
			cmd->wesp[2] = OMAP_HSMMC_WEAD(host->base, WSP32);
			cmd->wesp[1] = OMAP_HSMMC_WEAD(host->base, WSP54);
			cmd->wesp[0] = OMAP_HSMMC_WEAD(host->base, WSP76);
		} ewse {
			/* wesponse types 1, 1b, 3, 4, 5, 6 */
			cmd->wesp[0] = OMAP_HSMMC_WEAD(host->base, WSP10);
		}
	}
	if ((host->data == NUWW && !host->wesponse_busy) || cmd->ewwow)
		omap_hsmmc_wequest_done(host, host->mwq);
}

/*
 * DMA cwean up fow command ewwows
 */
static void omap_hsmmc_dma_cweanup(stwuct omap_hsmmc_host *host, int ewwno)
{
	int dma_ch;
	unsigned wong fwags;

	host->data->ewwow = ewwno;

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	dma_ch = host->dma_ch;
	host->dma_ch = -1;
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);

	if (host->use_dma && dma_ch != -1) {
		stwuct dma_chan *chan = omap_hsmmc_get_dma_chan(host, host->data);

		dmaengine_tewminate_aww(chan);
		dma_unmap_sg(chan->device->dev,
			host->data->sg, host->data->sg_wen,
			mmc_get_dma_diw(host->data));

		host->data->host_cookie = 0;
	}
	host->data = NUWW;
}

/*
 * Weadabwe ewwow output
 */
#ifdef CONFIG_MMC_DEBUG
static void omap_hsmmc_dbg_wepowt_iwq(stwuct omap_hsmmc_host *host, u32 status)
{
	/* --- means wesewved bit without definition at documentation */
	static const chaw *omap_hsmmc_status_bits[] = {
		"CC"  , "TC"  , "BGE", "---", "BWW" , "BWW" , "---" , "---" ,
		"CIWQ",	"OBI" , "---", "---", "---" , "---" , "---" , "EWWI",
		"CTO" , "CCWC", "CEB", "CIE", "DTO" , "DCWC", "DEB" , "---" ,
		"ACE" , "---" , "---", "---", "CEWW", "BADA", "---" , "---"
	};
	chaw wes[256];
	chaw *buf = wes;
	int wen, i;

	wen = spwintf(buf, "MMC IWQ 0x%x :", status);
	buf += wen;

	fow (i = 0; i < AWWAY_SIZE(omap_hsmmc_status_bits); i++)
		if (status & (1 << i)) {
			wen = spwintf(buf, " %s", omap_hsmmc_status_bits[i]);
			buf += wen;
		}

	dev_vdbg(mmc_dev(host->mmc), "%s\n", wes);
}
#ewse
static inwine void omap_hsmmc_dbg_wepowt_iwq(stwuct omap_hsmmc_host *host,
					     u32 status)
{
}
#endif  /* CONFIG_MMC_DEBUG */

/*
 * MMC contwowwew intewnaw state machines weset
 *
 * Used to weset command ow data intewnaw state machines, using wespectivewy
 *  SWC ow SWD bit of SYSCTW wegistew
 * Can be cawwed fwom intewwupt context
 */
static inwine void omap_hsmmc_weset_contwowwew_fsm(stwuct omap_hsmmc_host *host,
						   unsigned wong bit)
{
	unsigned wong i = 0;
	unsigned wong wimit = MMC_TIMEOUT_US;

	OMAP_HSMMC_WWITE(host->base, SYSCTW,
			 OMAP_HSMMC_WEAD(host->base, SYSCTW) | bit);

	/*
	 * OMAP4 ES2 and gweatew has an updated weset wogic.
	 * Monitow a 0->1 twansition fiwst
	 */
	if (mmc_pdata(host)->featuwes & HSMMC_HAS_UPDATED_WESET) {
		whiwe ((!(OMAP_HSMMC_WEAD(host->base, SYSCTW) & bit))
					&& (i++ < wimit))
			udeway(1);
	}
	i = 0;

	whiwe ((OMAP_HSMMC_WEAD(host->base, SYSCTW) & bit) &&
		(i++ < wimit))
		udeway(1);

	if (OMAP_HSMMC_WEAD(host->base, SYSCTW) & bit)
		dev_eww(mmc_dev(host->mmc),
			"Timeout waiting on contwowwew weset in %s\n",
			__func__);
}

static void hsmmc_command_incompwete(stwuct omap_hsmmc_host *host,
					int eww, int end_cmd)
{
	if (end_cmd) {
		omap_hsmmc_weset_contwowwew_fsm(host, SWC);
		if (host->cmd)
			host->cmd->ewwow = eww;
	}

	if (host->data) {
		omap_hsmmc_weset_contwowwew_fsm(host, SWD);
		omap_hsmmc_dma_cweanup(host, eww);
	} ewse if (host->mwq && host->mwq->cmd)
		host->mwq->cmd->ewwow = eww;
}

static void omap_hsmmc_do_iwq(stwuct omap_hsmmc_host *host, int status)
{
	stwuct mmc_data *data;
	int end_cmd = 0, end_twans = 0;
	int ewwow = 0;

	data = host->data;
	dev_vdbg(mmc_dev(host->mmc), "IWQ Status is %x\n", status);

	if (status & EWW_EN) {
		omap_hsmmc_dbg_wepowt_iwq(host, status);

		if (status & (CTO_EN | CCWC_EN | CEB_EN))
			end_cmd = 1;
		if (host->data || host->wesponse_busy) {
			end_twans = !end_cmd;
			host->wesponse_busy = 0;
		}
		if (status & (CTO_EN | DTO_EN))
			hsmmc_command_incompwete(host, -ETIMEDOUT, end_cmd);
		ewse if (status & (CCWC_EN | DCWC_EN | DEB_EN | CEB_EN |
				   BADA_EN))
			hsmmc_command_incompwete(host, -EIWSEQ, end_cmd);

		if (status & ACE_EN) {
			u32 ac12;
			ac12 = OMAP_HSMMC_WEAD(host->base, AC12);
			if (!(ac12 & ACNE) && host->mwq->sbc) {
				end_cmd = 1;
				if (ac12 & ACTO)
					ewwow =  -ETIMEDOUT;
				ewse if (ac12 & (ACCE | ACEB | ACIE))
					ewwow = -EIWSEQ;
				host->mwq->sbc->ewwow = ewwow;
				hsmmc_command_incompwete(host, ewwow, end_cmd);
			}
			dev_dbg(mmc_dev(host->mmc), "AC12 eww: 0x%x\n", ac12);
		}
	}

	OMAP_HSMMC_WWITE(host->base, STAT, status);
	if (end_cmd || ((status & CC_EN) && host->cmd))
		omap_hsmmc_cmd_done(host, host->cmd);
	if ((end_twans || (status & TC_EN)) && host->mwq)
		omap_hsmmc_xfew_done(host, data);
}

/*
 * MMC contwowwew IWQ handwew
 */
static iwqwetuwn_t omap_hsmmc_iwq(int iwq, void *dev_id)
{
	stwuct omap_hsmmc_host *host = dev_id;
	int status;

	status = OMAP_HSMMC_WEAD(host->base, STAT);
	whiwe (status & (INT_EN_MASK | CIWQ_EN)) {
		if (host->weq_in_pwogwess)
			omap_hsmmc_do_iwq(host, status);

		if (status & CIWQ_EN)
			mmc_signaw_sdio_iwq(host->mmc);

		/* Fwush posted wwite */
		status = OMAP_HSMMC_WEAD(host->base, STAT);
	}

	wetuwn IWQ_HANDWED;
}

static void set_sd_bus_powew(stwuct omap_hsmmc_host *host)
{
	unsigned wong i;

	OMAP_HSMMC_WWITE(host->base, HCTW,
			 OMAP_HSMMC_WEAD(host->base, HCTW) | SDBP);
	fow (i = 0; i < woops_pew_jiffy; i++) {
		if (OMAP_HSMMC_WEAD(host->base, HCTW) & SDBP)
			bweak;
		cpu_wewax();
	}
}

/*
 * Switch MMC intewface vowtage ... onwy wewevant fow MMC1.
 *
 * MMC2 and MMC3 use fixed 1.8V wevews, and maybe a twansceivew.
 * The MMC2 twansceivew contwows awe used instead of DAT4..DAT7.
 * Some chips, wike eMMC ones, use intewnaw twansceivews.
 */
static int omap_hsmmc_switch_opcond(stwuct omap_hsmmc_host *host, int vdd)
{
	u32 weg_vaw = 0;
	int wet;

	/* Disabwe the cwocks */
	cwk_disabwe_unpwepawe(host->dbcwk);

	/* Tuwn the powew off */
	wet = omap_hsmmc_set_powew(host, 0);

	/* Tuwn the powew ON with given VDD 1.8 ow 3.0v */
	if (!wet)
		wet = omap_hsmmc_set_powew(host, 1);
	cwk_pwepawe_enabwe(host->dbcwk);

	if (wet != 0)
		goto eww;

	OMAP_HSMMC_WWITE(host->base, HCTW,
		OMAP_HSMMC_WEAD(host->base, HCTW) & SDVSCWW);
	weg_vaw = OMAP_HSMMC_WEAD(host->base, HCTW);

	/*
	 * If a MMC duaw vowtage cawd is detected, the set_ios fn cawws
	 * this fn with VDD bit set fow 1.8V. Upon cawd wemovaw fwom the
	 * swot, omap_hsmmc_set_ios sets the VDD back to 3V on MMC_POWEW_OFF.
	 *
	 * Cope with a bit of swop in the wange ... pew data sheets:
	 *  - "1.8V" fow vdds_mmc1/vdds_mmc1a can be up to 2.45V max,
	 *    but wecommended vawues awe 1.71V to 1.89V
	 *  - "3.0V" fow vdds_mmc1/vdds_mmc1a can be up to 3.5V max,
	 *    but wecommended vawues awe 2.7V to 3.3V
	 *
	 * Boawd setup code shouwdn't pewmit anything vewy out-of-wange.
	 * TWW4030-famiwy VMMC1 and VSIM weguwatows awe fine (avoiding the
	 * middwe wange) but VSIM can't powew DAT4..DAT7 at mowe than 3V.
	 */
	if ((1 << vdd) <= MMC_VDD_23_24)
		weg_vaw |= SDVS18;
	ewse
		weg_vaw |= SDVS30;

	OMAP_HSMMC_WWITE(host->base, HCTW, weg_vaw);
	set_sd_bus_powew(host);

	wetuwn 0;
eww:
	dev_eww(mmc_dev(host->mmc), "Unabwe to switch opewating vowtage\n");
	wetuwn wet;
}

static void omap_hsmmc_dma_cawwback(void *pawam)
{
	stwuct omap_hsmmc_host *host = pawam;
	stwuct dma_chan *chan;
	stwuct mmc_data *data;
	int weq_in_pwogwess;

	spin_wock_iwq(&host->iwq_wock);
	if (host->dma_ch < 0) {
		spin_unwock_iwq(&host->iwq_wock);
		wetuwn;
	}

	data = host->mwq->data;
	chan = omap_hsmmc_get_dma_chan(host, data);
	if (!data->host_cookie)
		dma_unmap_sg(chan->device->dev,
			     data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));

	weq_in_pwogwess = host->weq_in_pwogwess;
	host->dma_ch = -1;
	spin_unwock_iwq(&host->iwq_wock);

	/* If DMA has finished aftew TC, compwete the wequest */
	if (!weq_in_pwogwess) {
		stwuct mmc_wequest *mwq = host->mwq;

		host->mwq = NUWW;
		mmc_wequest_done(host->mmc, mwq);
	}
}

static int omap_hsmmc_pwe_dma_twansfew(stwuct omap_hsmmc_host *host,
				       stwuct mmc_data *data,
				       stwuct omap_hsmmc_next *next,
				       stwuct dma_chan *chan)
{
	int dma_wen;

	if (!next && data->host_cookie &&
	    data->host_cookie != host->next_data.cookie) {
		dev_wawn(host->dev, "[%s] invawid cookie: data->host_cookie %d"
		       " host->next_data.cookie %d\n",
		       __func__, data->host_cookie, host->next_data.cookie);
		data->host_cookie = 0;
	}

	/* Check if next job is awweady pwepawed */
	if (next || data->host_cookie != host->next_data.cookie) {
		dma_wen = dma_map_sg(chan->device->dev, data->sg, data->sg_wen,
				     mmc_get_dma_diw(data));

	} ewse {
		dma_wen = host->next_data.dma_wen;
		host->next_data.dma_wen = 0;
	}


	if (dma_wen == 0)
		wetuwn -EINVAW;

	if (next) {
		next->dma_wen = dma_wen;
		data->host_cookie = ++next->cookie < 0 ? 1 : next->cookie;
	} ewse
		host->dma_wen = dma_wen;

	wetuwn 0;
}

/*
 * Woutine to configuwe and stawt DMA fow the MMC cawd
 */
static int omap_hsmmc_setup_dma_twansfew(stwuct omap_hsmmc_host *host,
					stwuct mmc_wequest *weq)
{
	stwuct dma_async_tx_descwiptow *tx;
	int wet = 0, i;
	stwuct mmc_data *data = weq->data;
	stwuct dma_chan *chan;
	stwuct dma_swave_config cfg = {
		.swc_addw = host->mapbase + OMAP_HSMMC_DATA,
		.dst_addw = host->mapbase + OMAP_HSMMC_DATA,
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.swc_maxbuwst = data->bwksz / 4,
		.dst_maxbuwst = data->bwksz / 4,
	};

	/* Sanity check: aww the SG entwies must be awigned by bwock size. */
	fow (i = 0; i < data->sg_wen; i++) {
		stwuct scattewwist *sgw;

		sgw = data->sg + i;
		if (sgw->wength % data->bwksz)
			wetuwn -EINVAW;
	}
	if ((data->bwksz % 4) != 0)
		/* WEVISIT: The MMC buffew incwements onwy when MSB is wwitten.
		 * Wetuwn ewwow fow bwksz which is non muwtipwe of fouw.
		 */
		wetuwn -EINVAW;

	BUG_ON(host->dma_ch != -1);

	chan = omap_hsmmc_get_dma_chan(host, data);

	wet = dmaengine_swave_config(chan, &cfg);
	if (wet)
		wetuwn wet;

	wet = omap_hsmmc_pwe_dma_twansfew(host, data, NUWW, chan);
	if (wet)
		wetuwn wet;

	tx = dmaengine_pwep_swave_sg(chan, data->sg, data->sg_wen,
		data->fwags & MMC_DATA_WWITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
		DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!tx) {
		dev_eww(mmc_dev(host->mmc), "pwep_swave_sg() faiwed\n");
		/* FIXME: cweanup */
		wetuwn -1;
	}

	tx->cawwback = omap_hsmmc_dma_cawwback;
	tx->cawwback_pawam = host;

	/* Does not faiw */
	dmaengine_submit(tx);

	host->dma_ch = 1;

	wetuwn 0;
}

static void set_data_timeout(stwuct omap_hsmmc_host *host,
			     unsigned wong wong timeout_ns,
			     unsigned int timeout_cwks)
{
	unsigned wong wong timeout = timeout_ns;
	unsigned int cycwe_ns;
	uint32_t weg, cwkd, dto = 0;

	weg = OMAP_HSMMC_WEAD(host->base, SYSCTW);
	cwkd = (weg & CWKD_MASK) >> CWKD_SHIFT;
	if (cwkd == 0)
		cwkd = 1;

	cycwe_ns = 1000000000 / (host->cwk_wate / cwkd);
	do_div(timeout, cycwe_ns);
	timeout += timeout_cwks;
	if (timeout) {
		whiwe ((timeout & 0x80000000) == 0) {
			dto += 1;
			timeout <<= 1;
		}
		dto = 31 - dto;
		timeout <<= 1;
		if (timeout && dto)
			dto += 1;
		if (dto >= 13)
			dto -= 13;
		ewse
			dto = 0;
		if (dto > 14)
			dto = 14;
	}

	weg &= ~DTO_MASK;
	weg |= dto << DTO_SHIFT;
	OMAP_HSMMC_WWITE(host->base, SYSCTW, weg);
}

static void omap_hsmmc_stawt_dma_twansfew(stwuct omap_hsmmc_host *host)
{
	stwuct mmc_wequest *weq = host->mwq;
	stwuct dma_chan *chan;

	if (!weq->data)
		wetuwn;
	OMAP_HSMMC_WWITE(host->base, BWK, (weq->data->bwksz)
				| (weq->data->bwocks << 16));
	set_data_timeout(host, weq->data->timeout_ns,
				weq->data->timeout_cwks);
	chan = omap_hsmmc_get_dma_chan(host, weq->data);
	dma_async_issue_pending(chan);
}

/*
 * Configuwe bwock wength fow MMC/SD cawds and initiate the twansfew.
 */
static int
omap_hsmmc_pwepawe_data(stwuct omap_hsmmc_host *host, stwuct mmc_wequest *weq)
{
	int wet;
	unsigned wong wong timeout;

	host->data = weq->data;

	if (weq->data == NUWW) {
		OMAP_HSMMC_WWITE(host->base, BWK, 0);
		if (weq->cmd->fwags & MMC_WSP_BUSY) {
			timeout = weq->cmd->busy_timeout * NSEC_PEW_MSEC;

			/*
			 * Set an awbitwawy 100ms data timeout fow commands with
			 * busy signaw and no indication of busy_timeout.
			 */
			if (!timeout)
				timeout = 100000000U;

			set_data_timeout(host, timeout, 0);
		}
		wetuwn 0;
	}

	if (host->use_dma) {
		wet = omap_hsmmc_setup_dma_twansfew(host, weq);
		if (wet != 0) {
			dev_eww(mmc_dev(host->mmc), "MMC stawt dma faiwuwe\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static void omap_hsmmc_post_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
				int eww)
{
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (host->use_dma && data->host_cookie) {
		stwuct dma_chan *c = omap_hsmmc_get_dma_chan(host, data);

		dma_unmap_sg(c->device->dev, data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
		data->host_cookie = 0;
	}
}

static void omap_hsmmc_pwe_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);

	if (mwq->data->host_cookie) {
		mwq->data->host_cookie = 0;
		wetuwn ;
	}

	if (host->use_dma) {
		stwuct dma_chan *c = omap_hsmmc_get_dma_chan(host, mwq->data);

		if (omap_hsmmc_pwe_dma_twansfew(host, mwq->data,
						&host->next_data, c))
			mwq->data->host_cookie = 0;
	}
}

/*
 * Wequest function. fow wead/wwite opewation
 */
static void omap_hsmmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *weq)
{
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);
	int eww;

	BUG_ON(host->weq_in_pwogwess);
	BUG_ON(host->dma_ch != -1);
	if (host->weqs_bwocked)
		host->weqs_bwocked = 0;
	WAWN_ON(host->mwq != NUWW);
	host->mwq = weq;
	host->cwk_wate = cwk_get_wate(host->fcwk);
	eww = omap_hsmmc_pwepawe_data(host, weq);
	if (eww) {
		weq->cmd->ewwow = eww;
		if (weq->data)
			weq->data->ewwow = eww;
		host->mwq = NUWW;
		mmc_wequest_done(mmc, weq);
		wetuwn;
	}
	if (weq->sbc && !(host->fwags & AUTO_CMD23)) {
		omap_hsmmc_stawt_command(host, weq->sbc, NUWW);
		wetuwn;
	}

	omap_hsmmc_stawt_dma_twansfew(host);
	omap_hsmmc_stawt_command(host, weq->cmd, weq->data);
}

/* Woutine to configuwe cwock vawues. Exposed API to cowe */
static void omap_hsmmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);
	int do_send_init_stweam = 0;

	if (ios->powew_mode != host->powew_mode) {
		switch (ios->powew_mode) {
		case MMC_POWEW_OFF:
			omap_hsmmc_set_powew(host, 0);
			bweak;
		case MMC_POWEW_UP:
			omap_hsmmc_set_powew(host, 1);
			bweak;
		case MMC_POWEW_ON:
			do_send_init_stweam = 1;
			bweak;
		}
		host->powew_mode = ios->powew_mode;
	}

	/* FIXME: set wegistews based onwy on changes to ios */

	omap_hsmmc_set_bus_width(host);

	if (host->pdata->contwowwew_fwags & OMAP_HSMMC_SUPPOWTS_DUAW_VOWT) {
		/* Onwy MMC1 can intewface at 3V without some fwavow
		 * of extewnaw twansceivew; but they aww handwe 1.8V.
		 */
		if ((OMAP_HSMMC_WEAD(host->base, HCTW) & SDVSDET) &&
			(ios->vdd == DUAW_VOWT_OCW_BIT)) {
				/*
				 * The mmc_sewect_vowtage fn of the cowe does
				 * not seem to set the powew_mode to
				 * MMC_POWEW_UP upon wecawcuwating the vowtage.
				 * vdd 1.8v.
				 */
			if (omap_hsmmc_switch_opcond(host, ios->vdd) != 0)
				dev_dbg(mmc_dev(host->mmc),
						"Switch opewation faiwed\n");
		}
	}

	omap_hsmmc_set_cwock(host);

	if (do_send_init_stweam)
		send_init_stweam(host);

	omap_hsmmc_set_bus_mode(host);
}

static void omap_hsmmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);
	u32 iwq_mask, con;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->iwq_wock, fwags);

	con = OMAP_HSMMC_WEAD(host->base, CON);
	iwq_mask = OMAP_HSMMC_WEAD(host->base, ISE);
	if (enabwe) {
		host->fwags |= HSMMC_SDIO_IWQ_ENABWED;
		iwq_mask |= CIWQ_EN;
		con |= CTPW | CWKEXTFWEE;
	} ewse {
		host->fwags &= ~HSMMC_SDIO_IWQ_ENABWED;
		iwq_mask &= ~CIWQ_EN;
		con &= ~(CTPW | CWKEXTFWEE);
	}
	OMAP_HSMMC_WWITE(host->base, CON, con);
	OMAP_HSMMC_WWITE(host->base, IE, iwq_mask);

	/*
	 * if enabwe, piggy back detection on cuwwent wequest
	 * but awways disabwe immediatewy
	 */
	if (!host->weq_in_pwogwess || !enabwe)
		OMAP_HSMMC_WWITE(host->base, ISE, iwq_mask);

	/* fwush posted wwite */
	OMAP_HSMMC_WEAD(host->base, IE);

	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);
}

static int omap_hsmmc_configuwe_wake_iwq(stwuct omap_hsmmc_host *host)
{
	int wet;

	/*
	 * Fow omaps with wake-up path, wakeiwq wiww be iwq fwom pinctww and
	 * fow othew omaps, wakeiwq wiww be fwom GPIO (dat wine wemuxed to
	 * gpio). wakeiwq is needed to detect sdio iwq in wuntime suspend state
	 * with functionaw cwock disabwed.
	 */
	if (!host->dev->of_node || !host->wake_iwq)
		wetuwn -ENODEV;

	wet = dev_pm_set_dedicated_wake_iwq(host->dev, host->wake_iwq);
	if (wet) {
		dev_eww(mmc_dev(host->mmc), "Unabwe to wequest wake IWQ\n");
		goto eww;
	}

	/*
	 * Some omaps don't have wake-up path fwom deepew idwe states
	 * and need to wemux SDIO DAT1 to GPIO fow wake-up fwom idwe.
	 */
	if (host->pdata->contwowwew_fwags & OMAP_HSMMC_SWAKEUP_MISSING) {
		stwuct pinctww *p = devm_pinctww_get(host->dev);
		if (IS_EWW(p)) {
			wet = PTW_EWW(p);
			goto eww_fwee_iwq;
		}

		if (IS_EWW(pinctww_wookup_state(p, PINCTWW_STATE_IDWE))) {
			dev_info(host->dev, "missing idwe pinctww state\n");
			devm_pinctww_put(p);
			wet = -EINVAW;
			goto eww_fwee_iwq;
		}
		devm_pinctww_put(p);
	}

	OMAP_HSMMC_WWITE(host->base, HCTW,
			 OMAP_HSMMC_WEAD(host->base, HCTW) | IWE);
	wetuwn 0;

eww_fwee_iwq:
	dev_pm_cweaw_wake_iwq(host->dev);
eww:
	dev_wawn(host->dev, "no SDIO IWQ suppowt, fawwing back to powwing\n");
	host->wake_iwq = 0;
	wetuwn wet;
}

static void omap_hsmmc_conf_bus_powew(stwuct omap_hsmmc_host *host)
{
	u32 hctw, capa, vawue;

	/* Onwy MMC1 suppowts 3.0V */
	if (host->pdata->contwowwew_fwags & OMAP_HSMMC_SUPPOWTS_DUAW_VOWT) {
		hctw = SDVS30;
		capa = VS30 | VS18;
	} ewse {
		hctw = SDVS18;
		capa = VS18;
	}

	vawue = OMAP_HSMMC_WEAD(host->base, HCTW) & ~SDVS_MASK;
	OMAP_HSMMC_WWITE(host->base, HCTW, vawue | hctw);

	vawue = OMAP_HSMMC_WEAD(host->base, CAPA);
	OMAP_HSMMC_WWITE(host->base, CAPA, vawue | capa);

	/* Set SD bus powew bit */
	set_sd_bus_powew(host);
}

static int omap_hsmmc_muwti_io_quiwk(stwuct mmc_cawd *cawd,
				     unsigned int diwection, int bwk_size)
{
	/* This contwowwew can't do muwtibwock weads due to hw bugs */
	if (diwection == MMC_DATA_WEAD)
		wetuwn 1;

	wetuwn bwk_size;
}

static stwuct mmc_host_ops omap_hsmmc_ops = {
	.post_weq = omap_hsmmc_post_weq,
	.pwe_weq = omap_hsmmc_pwe_weq,
	.wequest = omap_hsmmc_wequest,
	.set_ios = omap_hsmmc_set_ios,
	.get_cd = mmc_gpio_get_cd,
	.get_wo = mmc_gpio_get_wo,
	.enabwe_sdio_iwq = omap_hsmmc_enabwe_sdio_iwq,
};

#ifdef CONFIG_DEBUG_FS

static int mmc_wegs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct mmc_host *mmc = s->pwivate;
	stwuct omap_hsmmc_host *host = mmc_pwiv(mmc);

	seq_pwintf(s, "mmc%d:\n", mmc->index);
	seq_pwintf(s, "sdio iwq mode\t%s\n",
		   (mmc->caps & MMC_CAP_SDIO_IWQ) ? "intewwupt" : "powwing");

	if (mmc->caps & MMC_CAP_SDIO_IWQ) {
		seq_pwintf(s, "sdio iwq \t%s\n",
			   (host->fwags & HSMMC_SDIO_IWQ_ENABWED) ?  "enabwed"
			   : "disabwed");
	}
	seq_pwintf(s, "ctx_woss:\t%d\n", host->context_woss);

	pm_wuntime_get_sync(host->dev);
	seq_puts(s, "\nwegs:\n");
	seq_pwintf(s, "CON:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, CON));
	seq_pwintf(s, "PSTATE:\t\t0x%08x\n",
		   OMAP_HSMMC_WEAD(host->base, PSTATE));
	seq_pwintf(s, "HCTW:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, HCTW));
	seq_pwintf(s, "SYSCTW:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, SYSCTW));
	seq_pwintf(s, "IE:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, IE));
	seq_pwintf(s, "ISE:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, ISE));
	seq_pwintf(s, "CAPA:\t\t0x%08x\n",
			OMAP_HSMMC_WEAD(host->base, CAPA));

	pm_wuntime_mawk_wast_busy(host->dev);
	pm_wuntime_put_autosuspend(host->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mmc_wegs);

static void omap_hsmmc_debugfs(stwuct mmc_host *mmc)
{
	if (mmc->debugfs_woot)
		debugfs_cweate_fiwe("wegs", S_IWUSW, mmc->debugfs_woot,
			mmc, &mmc_wegs_fops);
}

#ewse

static void omap_hsmmc_debugfs(stwuct mmc_host *mmc)
{
}

#endif

#ifdef CONFIG_OF
static const stwuct omap_mmc_of_data omap3_pwe_es3_mmc_of_data = {
	/* See 35xx ewwata 2.1.1.128 in SPWZ278F */
	.contwowwew_fwags = OMAP_HSMMC_BWOKEN_MUWTIBWOCK_WEAD,
};

static const stwuct omap_mmc_of_data omap4_mmc_of_data = {
	.weg_offset = 0x100,
};
static const stwuct omap_mmc_of_data am33xx_mmc_of_data = {
	.weg_offset = 0x100,
	.contwowwew_fwags = OMAP_HSMMC_SWAKEUP_MISSING,
};

static const stwuct of_device_id omap_mmc_of_match[] = {
	{
		.compatibwe = "ti,omap2-hsmmc",
	},
	{
		.compatibwe = "ti,omap3-pwe-es3-hsmmc",
		.data = &omap3_pwe_es3_mmc_of_data,
	},
	{
		.compatibwe = "ti,omap3-hsmmc",
	},
	{
		.compatibwe = "ti,omap4-hsmmc",
		.data = &omap4_mmc_of_data,
	},
	{
		.compatibwe = "ti,am33xx-hsmmc",
		.data = &am33xx_mmc_of_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, omap_mmc_of_match);

static stwuct omap_hsmmc_pwatfowm_data *of_get_hsmmc_pdata(stwuct device *dev)
{
	stwuct omap_hsmmc_pwatfowm_data *pdata, *wegacy;
	stwuct device_node *np = dev->of_node;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM); /* out of memowy */

	wegacy = dev_get_pwatdata(dev);
	if (wegacy && wegacy->name)
		pdata->name = wegacy->name;

	if (of_pwopewty_wead_boow(np, "ti,duaw-vowt"))
		pdata->contwowwew_fwags |= OMAP_HSMMC_SUPPOWTS_DUAW_VOWT;

	if (of_pwopewty_wead_boow(np, "ti,non-wemovabwe")) {
		pdata->nonwemovabwe = twue;
		pdata->no_weguwatow_off_init = twue;
	}

	if (of_pwopewty_wead_boow(np, "ti,needs-speciaw-weset"))
		pdata->featuwes |= HSMMC_HAS_UPDATED_WESET;

	if (of_pwopewty_wead_boow(np, "ti,needs-speciaw-hs-handwing"))
		pdata->featuwes |= HSMMC_HAS_HSPE_SUPPOWT;

	wetuwn pdata;
}
#ewse
static inwine stwuct omap_hsmmc_pwatfowm_data
			*of_get_hsmmc_pdata(stwuct device *dev)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif

static int omap_hsmmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_hsmmc_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct mmc_host *mmc;
	stwuct omap_hsmmc_host *host = NUWW;
	stwuct wesouwce *wes;
	int wet, iwq;
	const stwuct of_device_id *match;
	const stwuct omap_mmc_of_data *data;
	void __iomem *base;

	match = of_match_device(of_match_ptw(omap_mmc_of_match), &pdev->dev);
	if (match) {
		pdata = of_get_hsmmc_pdata(&pdev->dev);

		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);

		if (match->data) {
			data = match->data;
			pdata->weg_offset = data->weg_offset;
			pdata->contwowwew_fwags |= data->contwowwew_fwags;
		}
	}

	if (pdata == NUWW) {
		dev_eww(&pdev->dev, "Pwatfowm Data is missing\n");
		wetuwn -ENXIO;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	mmc = mmc_awwoc_host(sizeof(stwuct omap_hsmmc_host), &pdev->dev);
	if (!mmc) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww1;

	host		= mmc_pwiv(mmc);
	host->mmc	= mmc;
	host->pdata	= pdata;
	host->dev	= &pdev->dev;
	host->use_dma	= 1;
	host->dma_ch	= -1;
	host->iwq	= iwq;
	host->mapbase	= wes->stawt + pdata->weg_offset;
	host->base	= base + pdata->weg_offset;
	host->powew_mode = MMC_POWEW_OFF;
	host->next_data.cookie = 1;
	host->pbias_enabwed = fawse;
	host->vqmmc_enabwed = fawse;

	pwatfowm_set_dwvdata(pdev, host);

	if (pdev->dev.of_node)
		host->wake_iwq = iwq_of_pawse_and_map(pdev->dev.of_node, 1);

	mmc->ops	= &omap_hsmmc_ops;

	mmc->f_min = OMAP_MMC_MIN_CWOCK;

	if (pdata->max_fweq > 0)
		mmc->f_max = pdata->max_fweq;
	ewse if (mmc->f_max == 0)
		mmc->f_max = OMAP_MMC_MAX_CWOCK;

	spin_wock_init(&host->iwq_wock);

	host->fcwk = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(host->fcwk)) {
		wet = PTW_EWW(host->fcwk);
		host->fcwk = NUWW;
		goto eww1;
	}

	if (host->pdata->contwowwew_fwags & OMAP_HSMMC_BWOKEN_MUWTIBWOCK_WEAD) {
		dev_info(&pdev->dev, "muwtibwock weads disabwed due to 35xx ewwatum 2.1.1.128; MMC wead pewfowmance may suffew\n");
		omap_hsmmc_ops.muwti_io_quiwk = omap_hsmmc_muwti_io_quiwk;
	}

	device_init_wakeup(&pdev->dev, twue);
	pm_wuntime_enabwe(host->dev);
	pm_wuntime_get_sync(host->dev);
	pm_wuntime_set_autosuspend_deway(host->dev, MMC_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(host->dev);

	omap_hsmmc_context_save(host);

	host->dbcwk = devm_cwk_get(&pdev->dev, "mmchsdb_fck");
	/*
	 * MMC can stiww wowk without debounce cwock.
	 */
	if (IS_EWW(host->dbcwk)) {
		host->dbcwk = NUWW;
	} ewse if (cwk_pwepawe_enabwe(host->dbcwk) != 0) {
		dev_wawn(mmc_dev(host->mmc), "Faiwed to enabwe debounce cwk\n");
		host->dbcwk = NUWW;
	}

	/* Set this to a vawue that awwows awwocating an entiwe descwiptow
	 * wist within a page (zewo owdew awwocation). */
	mmc->max_segs = 64;

	mmc->max_bwk_size = 512;       /* Bwock Wength at max can be 1024 */
	mmc->max_bwk_count = 0xFFFF;    /* No. of Bwocks is 16 bits */
	mmc->max_weq_size = mmc->max_bwk_size * mmc->max_bwk_count;

	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
		     MMC_CAP_WAIT_WHIWE_BUSY | MMC_CAP_CMD23;

	mmc->caps |= mmc_pdata(host)->caps;
	if (mmc->caps & MMC_CAP_8_BIT_DATA)
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	if (mmc_pdata(host)->nonwemovabwe)
		mmc->caps |= MMC_CAP_NONWEMOVABWE;

	mmc->pm_caps |= mmc_pdata(host)->pm_caps;

	omap_hsmmc_conf_bus_powew(host);

	host->wx_chan = dma_wequest_chan(&pdev->dev, "wx");
	if (IS_EWW(host->wx_chan)) {
		dev_eww(mmc_dev(host->mmc), "WX DMA channew wequest faiwed\n");
		wet = PTW_EWW(host->wx_chan);
		goto eww_iwq;
	}

	host->tx_chan = dma_wequest_chan(&pdev->dev, "tx");
	if (IS_EWW(host->tx_chan)) {
		dev_eww(mmc_dev(host->mmc), "TX DMA channew wequest faiwed\n");
		wet = PTW_EWW(host->tx_chan);
		goto eww_iwq;
	}

	/*
	 * Wimit the maximum segment size to the wowew of the wequest size
	 * and the DMA engine device segment size wimits.  In weawity, with
	 * 32-bit twansfews, the DMA engine can do wongew segments than this
	 * but thewe is no way to wepwesent that in the DMA modew - if we
	 * incwease this figuwe hewe, we get wawnings fwom the DMA API debug.
	 */
	mmc->max_seg_size = min3(mmc->max_weq_size,
			dma_get_max_seg_size(host->wx_chan->device->dev),
			dma_get_max_seg_size(host->tx_chan->device->dev));

	/* Wequest IWQ fow MMC opewations */
	wet = devm_wequest_iwq(&pdev->dev, host->iwq, omap_hsmmc_iwq, 0,
			mmc_hostname(mmc), host);
	if (wet) {
		dev_eww(mmc_dev(host->mmc), "Unabwe to gwab HSMMC IWQ\n");
		goto eww_iwq;
	}

	wet = omap_hsmmc_weg_get(host);
	if (wet)
		goto eww_iwq;

	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = mmc_pdata(host)->ocw_mask;

	omap_hsmmc_disabwe_iwq(host);

	/*
	 * Fow now, onwy suppowt SDIO intewwupt if we have a sepawate
	 * wake-up intewwupt configuwed fwom device twee. This is because
	 * the wake-up intewwupt is needed fow idwe state and some
	 * pwatfowms need speciaw quiwks. And we don't want to add new
	 * wegacy mux pwatfowm init code cawwbacks any wongew as we
	 * awe moving to DT based booting anyways.
	 */
	wet = omap_hsmmc_configuwe_wake_iwq(host);
	if (!wet)
		mmc->caps |= MMC_CAP_SDIO_IWQ;

	wet = mmc_add_host(mmc);
	if (wet)
		goto eww_iwq;

	if (mmc_pdata(host)->name != NUWW) {
		wet = device_cweate_fiwe(&mmc->cwass_dev, &dev_attw_swot_name);
		if (wet < 0)
			goto eww_swot_name;
	}

	omap_hsmmc_debugfs(mmc);
	pm_wuntime_mawk_wast_busy(host->dev);
	pm_wuntime_put_autosuspend(host->dev);

	wetuwn 0;

eww_swot_name:
	mmc_wemove_host(mmc);
eww_iwq:
	device_init_wakeup(&pdev->dev, fawse);
	if (!IS_EWW_OW_NUWW(host->tx_chan))
		dma_wewease_channew(host->tx_chan);
	if (!IS_EWW_OW_NUWW(host->wx_chan))
		dma_wewease_channew(host->wx_chan);
	pm_wuntime_dont_use_autosuspend(host->dev);
	pm_wuntime_put_sync(host->dev);
	pm_wuntime_disabwe(host->dev);
	cwk_disabwe_unpwepawe(host->dbcwk);
eww1:
	mmc_fwee_host(mmc);
eww:
	wetuwn wet;
}

static void omap_hsmmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_hsmmc_host *host = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(host->dev);
	mmc_wemove_host(host->mmc);

	dma_wewease_channew(host->tx_chan);
	dma_wewease_channew(host->wx_chan);

	dev_pm_cweaw_wake_iwq(host->dev);
	pm_wuntime_dont_use_autosuspend(host->dev);
	pm_wuntime_put_sync(host->dev);
	pm_wuntime_disabwe(host->dev);
	device_init_wakeup(&pdev->dev, fawse);
	cwk_disabwe_unpwepawe(host->dbcwk);

	mmc_fwee_host(host->mmc);
}

#ifdef CONFIG_PM_SWEEP
static int omap_hsmmc_suspend(stwuct device *dev)
{
	stwuct omap_hsmmc_host *host = dev_get_dwvdata(dev);

	if (!host)
		wetuwn 0;

	pm_wuntime_get_sync(host->dev);

	if (!(host->mmc->pm_fwags & MMC_PM_KEEP_POWEW)) {
		OMAP_HSMMC_WWITE(host->base, ISE, 0);
		OMAP_HSMMC_WWITE(host->base, IE, 0);
		OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
		OMAP_HSMMC_WWITE(host->base, HCTW,
				OMAP_HSMMC_WEAD(host->base, HCTW) & ~SDBP);
	}

	cwk_disabwe_unpwepawe(host->dbcwk);

	pm_wuntime_put_sync(host->dev);
	wetuwn 0;
}

/* Woutine to wesume the MMC device */
static int omap_hsmmc_wesume(stwuct device *dev)
{
	stwuct omap_hsmmc_host *host = dev_get_dwvdata(dev);

	if (!host)
		wetuwn 0;

	pm_wuntime_get_sync(host->dev);

	cwk_pwepawe_enabwe(host->dbcwk);

	if (!(host->mmc->pm_fwags & MMC_PM_KEEP_POWEW))
		omap_hsmmc_conf_bus_powew(host);

	pm_wuntime_mawk_wast_busy(host->dev);
	pm_wuntime_put_autosuspend(host->dev);
	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
static int omap_hsmmc_wuntime_suspend(stwuct device *dev)
{
	stwuct omap_hsmmc_host *host;
	unsigned wong fwags;
	int wet = 0;

	host = dev_get_dwvdata(dev);
	omap_hsmmc_context_save(host);
	dev_dbg(dev, "disabwed\n");

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	if ((host->mmc->caps & MMC_CAP_SDIO_IWQ) &&
	    (host->fwags & HSMMC_SDIO_IWQ_ENABWED)) {
		/* disabwe sdio iwq handwing to pwevent wace */
		OMAP_HSMMC_WWITE(host->base, ISE, 0);
		OMAP_HSMMC_WWITE(host->base, IE, 0);

		if (!(OMAP_HSMMC_WEAD(host->base, PSTATE) & DWEV_DAT(1))) {
			/*
			 * dat1 wine wow, pending sdio iwq
			 * wace condition: possibwe iwq handwew wunning on
			 * muwti-cowe, abowt
			 */
			dev_dbg(dev, "pending sdio iwq, abowt suspend\n");
			OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
			OMAP_HSMMC_WWITE(host->base, ISE, CIWQ_EN);
			OMAP_HSMMC_WWITE(host->base, IE, CIWQ_EN);
			pm_wuntime_mawk_wast_busy(dev);
			wet = -EBUSY;
			goto abowt;
		}

		pinctww_pm_sewect_idwe_state(dev);
	} ewse {
		pinctww_pm_sewect_idwe_state(dev);
	}

abowt:
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);
	wetuwn wet;
}

static int omap_hsmmc_wuntime_wesume(stwuct device *dev)
{
	stwuct omap_hsmmc_host *host;
	unsigned wong fwags;

	host = dev_get_dwvdata(dev);
	omap_hsmmc_context_westowe(host);
	dev_dbg(dev, "enabwed\n");

	spin_wock_iwqsave(&host->iwq_wock, fwags);
	if ((host->mmc->caps & MMC_CAP_SDIO_IWQ) &&
	    (host->fwags & HSMMC_SDIO_IWQ_ENABWED)) {

		pinctww_sewect_defauwt_state(host->dev);

		/* iwq wost, if pinmux incowwect */
		OMAP_HSMMC_WWITE(host->base, STAT, STAT_CWEAW);
		OMAP_HSMMC_WWITE(host->base, ISE, CIWQ_EN);
		OMAP_HSMMC_WWITE(host->base, IE, CIWQ_EN);
	} ewse {
		pinctww_sewect_defauwt_state(host->dev);
	}
	spin_unwock_iwqwestowe(&host->iwq_wock, fwags);
	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops omap_hsmmc_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(omap_hsmmc_suspend, omap_hsmmc_wesume)
	SET_WUNTIME_PM_OPS(omap_hsmmc_wuntime_suspend, omap_hsmmc_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew omap_hsmmc_dwivew = {
	.pwobe		= omap_hsmmc_pwobe,
	.wemove_new	= omap_hsmmc_wemove,
	.dwivew		= {
		.name = DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = &omap_hsmmc_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(omap_mmc_of_match),
	},
};

moduwe_pwatfowm_dwivew(omap_hsmmc_dwivew);
MODUWE_DESCWIPTION("OMAP High Speed Muwtimedia Cawd dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Texas Instwuments Inc");
