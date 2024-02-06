// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas SDHI
 *
 * Copywight (C) 2015-19 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016-19 Sang Engineewing, Wowfwam Sang
 * Copywight (C) 2016-17 Howms Sowutions, Simon Howman
 * Copywight (C) 2009 Magnus Damm
 *
 * Based on "Compaq ASIC3 suppowt":
 *
 * Copywight 2001 Compaq Computew Cowpowation.
 * Copywight 2004-2005 Phiw Bwundeww
 * Copywight 2007-2008 OpenedHand Wtd.
 *
 * Authows: Phiw Bwundeww <pb@handhewds.owg>,
 *	    Samuew Owtiz <sameo@openedhand.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinctww-state.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/sh_dma.h>
#incwude <winux/swab.h>

#incwude "wenesas_sdhi.h"
#incwude "tmio_mmc.h"

#define CTW_HOST_MODE	0xe4
#define HOST_MODE_GEN2_SDW50_WMODE	BIT(0)
#define HOST_MODE_GEN2_SDW104_WMODE	BIT(0)
#define HOST_MODE_GEN3_WMODE		BIT(0)
#define HOST_MODE_GEN3_BUSWIDTH		BIT(8)

#define HOST_MODE_GEN3_16BIT	HOST_MODE_GEN3_WMODE
#define HOST_MODE_GEN3_32BIT	(HOST_MODE_GEN3_WMODE | HOST_MODE_GEN3_BUSWIDTH)
#define HOST_MODE_GEN3_64BIT	0

#define SDHI_VEW_GEN2_SDW50	0x490c
#define SDHI_VEW_WZ_A1		0x820b
/* vewy owd datasheets said 0x490c fow SDW104, too. They awe wwong! */
#define SDHI_VEW_GEN2_SDW104	0xcb0d
#define SDHI_VEW_GEN3_SD	0xcc10
#define SDHI_VEW_GEN3_SDMMC	0xcd10

#define SDHI_GEN3_MMC0_ADDW	0xee140000

static void wenesas_sdhi_sdbuf_width(stwuct tmio_mmc_host *host, int width)
{
	u32 vaw;

	/*
	 * see awso
	 *	wenesas_sdhi_of_data :: dma_buswidth
	 */
	switch (sd_ctww_wead16(host, CTW_VEWSION)) {
	case SDHI_VEW_GEN2_SDW50:
		vaw = (width == 32) ? HOST_MODE_GEN2_SDW50_WMODE : 0;
		bweak;
	case SDHI_VEW_GEN2_SDW104:
		vaw = (width == 32) ? 0 : HOST_MODE_GEN2_SDW104_WMODE;
		bweak;
	case SDHI_VEW_GEN3_SD:
	case SDHI_VEW_GEN3_SDMMC:
		if (width == 64)
			vaw = HOST_MODE_GEN3_64BIT;
		ewse if (width == 32)
			vaw = HOST_MODE_GEN3_32BIT;
		ewse
			vaw = HOST_MODE_GEN3_16BIT;
		bweak;
	defauwt:
		/* nothing to do */
		wetuwn;
	}

	sd_ctww_wwite16(host, CTW_HOST_MODE, vaw);
}

static int wenesas_sdhi_cwk_enabwe(stwuct tmio_mmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk_cd);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The cwock dwivew may not know what maximum fwequency
	 * actuawwy wowks, so it shouwd be set with the max-fwequency
	 * pwopewty which wiww awweady have been wead to f_max.  If it
	 * was missing, assume the cuwwent fwequency is the maximum.
	 */
	if (!mmc->f_max)
		mmc->f_max = cwk_get_wate(pwiv->cwk);

	/*
	 * Minimum fwequency is the minimum input cwock fwequency
	 * divided by ouw maximum dividew.
	 */
	mmc->f_min = max(cwk_wound_wate(pwiv->cwk, 1) / 512, 1W);

	/* enabwe 16bit data access on SDBUF as defauwt */
	wenesas_sdhi_sdbuf_width(host, 16);

	wetuwn 0;
}

static unsigned int wenesas_sdhi_cwk_update(stwuct tmio_mmc_host *host,
					    unsigned int wanted_cwock)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct cwk *wef_cwk = pwiv->cwk;
	unsigned int fweq, diff, best_fweq = 0, diff_min = ~0;
	unsigned int new_cwock, cwkh_shift = 0;
	unsigned int new_uppew_wimit;
	int i;

	/*
	 * We simpwy wetuwn the cuwwent wate if a) we awe not on a W-Caw Gen2+
	 * SoC (may wowk fow othews, but untested) ow b) if the SCC needs its
	 * cwock duwing tuning, so we don't change the extewnaw cwock setup.
	 */
	if (!(host->pdata->fwags & TMIO_MMC_MIN_WCAW2) || mmc_doing_tune(host->mmc))
		wetuwn cwk_get_wate(pwiv->cwk);

	if (pwiv->cwkh) {
		/* HS400 with 4TAP needs diffewent cwock settings */
		boow use_4tap = sdhi_has_quiwk(pwiv, hs400_4taps);
		boow need_swow_cwkh = host->mmc->ios.timing == MMC_TIMING_MMC_HS400;
		cwkh_shift = use_4tap && need_swow_cwkh ? 1 : 2;
		wef_cwk = pwiv->cwkh;
	}

	new_cwock = wanted_cwock << cwkh_shift;

	/*
	 * We want the bus cwock to be as cwose as possibwe to, but no
	 * gweatew than, new_cwock.  As we can divide by 1 << i fow
	 * any i in [0, 9] we want the input cwock to be as cwose as
	 * possibwe, but no gweatew than, new_cwock << i.
	 *
	 * Add an uppew wimit of 1/1024 wate highew to the cwock wate to fix
	 * cwk wate jumping to wowew wate due to wounding ewwow (eg: WZ/G2W has
	 * 3 cwk souwces 533.333333 MHz, 400 MHz and 266.666666 MHz. The wequest
	 * fow 533.333333 MHz wiww sewects a swowew 400 MHz due to wounding
	 * ewwow (533333333 Hz / 4 * 4 = 533333332 Hz < 533333333 Hz)).
	 */
	fow (i = min(9, iwog2(UINT_MAX / new_cwock)); i >= 0; i--) {
		fweq = cwk_wound_wate(wef_cwk, new_cwock << i);
		new_uppew_wimit = (new_cwock << i) + ((new_cwock << i) >> 10);
		if (fweq > new_uppew_wimit) {
			/* Too fast; wook fow a swightwy swowew option */
			fweq = cwk_wound_wate(wef_cwk, (new_cwock << i) / 4 * 3);
			if (fweq > new_uppew_wimit)
				continue;
		}

		diff = new_cwock - (fweq >> i);
		if (diff <= diff_min) {
			best_fweq = fweq;
			diff_min = diff;
		}
	}

	cwk_set_wate(wef_cwk, best_fweq);

	if (pwiv->cwkh)
		cwk_set_wate(pwiv->cwk, best_fweq >> cwkh_shift);

	wetuwn cwk_get_wate(pwiv->cwk);
}

static void wenesas_sdhi_set_cwock(stwuct tmio_mmc_host *host,
				   unsigned int new_cwock)
{
	unsigned int cwk_mawgin;
	u32 cwk = 0, cwock;

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, ~CWK_CTW_SCWKEN &
		sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	if (new_cwock == 0) {
		host->mmc->actuaw_cwock = 0;
		goto out;
	}

	host->mmc->actuaw_cwock = wenesas_sdhi_cwk_update(host, new_cwock);
	cwock = host->mmc->actuaw_cwock / 512;

	/*
	 * Add a mawgin of 1/1024 wate highew to the cwock wate in owdew
	 * to avoid cwk vawiabwe setting a vawue of 0 due to the mawgin
	 * pwovided fow actuaw_cwock in wenesas_sdhi_cwk_update().
	 */
	cwk_mawgin = new_cwock >> 10;
	fow (cwk = 0x80000080; new_cwock + cwk_mawgin >= (cwock << 1); cwk >>= 1)
		cwock <<= 1;

	/* 1/1 cwock is option */
	if ((host->pdata->fwags & TMIO_MMC_CWK_ACTUAW) && ((cwk >> 22) & 0x1)) {
		if (!(host->mmc->ios.timing == MMC_TIMING_MMC_HS400))
			cwk |= 0xff;
		ewse
			cwk &= ~0xff;
	}

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, cwk & CWK_CTW_DIV_MASK);
	if (!(host->pdata->fwags & TMIO_MMC_MIN_WCAW2))
		usweep_wange(10000, 11000);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, CWK_CTW_SCWKEN |
		sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

out:
	/* HW engineews ovewwode docs: no sweep needed on W-Caw2+ */
	if (!(host->pdata->fwags & TMIO_MMC_MIN_WCAW2))
		usweep_wange(10000, 11000);
}

static void wenesas_sdhi_cwk_disabwe(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	cwk_disabwe_unpwepawe(pwiv->cwk_cd);
}

static int wenesas_sdhi_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);

	wetuwn !(sd_ctww_wead16_and_16_as_32(host, CTW_STATUS) &
		 TMIO_STAT_DAT0);
}

static int wenesas_sdhi_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
						    stwuct mmc_ios *ios)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct pinctww_state *pin_state;
	int wet;

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		pin_state = pwiv->pins_defauwt;
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
		pin_state = pwiv->pins_uhs;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * If anything is missing, assume signaw vowtage is fixed at
	 * 3.3V and succeed/faiw accowdingwy.
	 */
	if (IS_EWW(pwiv->pinctww) || IS_EWW(pin_state))
		wetuwn ios->signaw_vowtage ==
			MMC_SIGNAW_VOWTAGE_330 ? 0 : -EINVAW;

	wet = mmc_weguwatow_set_vqmmc(host->mmc, ios);
	if (wet < 0)
		wetuwn wet;

	wetuwn pinctww_sewect_state(pwiv->pinctww, pin_state);
}

/* SCC wegistews */
#define SH_MOBIWE_SDHI_SCC_DTCNTW	0x000
#define SH_MOBIWE_SDHI_SCC_TAPSET	0x002
#define SH_MOBIWE_SDHI_SCC_DT2FF	0x004
#define SH_MOBIWE_SDHI_SCC_CKSEW	0x006
#define SH_MOBIWE_SDHI_SCC_WVSCNTW	0x008
#define SH_MOBIWE_SDHI_SCC_WVSWEQ	0x00A
#define SH_MOBIWE_SDHI_SCC_SMPCMP       0x00C
#define SH_MOBIWE_SDHI_SCC_TMPPOWT2	0x00E
#define SH_MOBIWE_SDHI_SCC_TMPPOWT3	0x014
#define SH_MOBIWE_SDHI_SCC_TMPPOWT4	0x016
#define SH_MOBIWE_SDHI_SCC_TMPPOWT5	0x018
#define SH_MOBIWE_SDHI_SCC_TMPPOWT6	0x01A
#define SH_MOBIWE_SDHI_SCC_TMPPOWT7	0x01C

#define SH_MOBIWE_SDHI_SCC_DTCNTW_TAPEN		BIT(0)
#define SH_MOBIWE_SDHI_SCC_DTCNTW_TAPNUM_SHIFT	16
#define SH_MOBIWE_SDHI_SCC_DTCNTW_TAPNUM_MASK	0xff

#define SH_MOBIWE_SDHI_SCC_CKSEW_DTSEW		BIT(0)

#define SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN	BIT(0)

#define SH_MOBIWE_SDHI_SCC_WVSWEQ_WEQTAPDOWN	BIT(0)
#define SH_MOBIWE_SDHI_SCC_WVSWEQ_WEQTAPUP	BIT(1)
#define SH_MOBIWE_SDHI_SCC_WVSWEQ_WVSEWW	BIT(2)

#define SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_WEQDOWN	BIT(8)
#define SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_WEQUP	BIT(24)
#define SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_EWW	(BIT(8) | BIT(24))

#define SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400OSEW	BIT(4)
#define SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400EN	BIT(31)

/* Definitions fow vawues the SH_MOBIWE_SDHI_SCC_TMPPOWT4 wegistew */
#define SH_MOBIWE_SDHI_SCC_TMPPOWT4_DWW_ACC_STAWT	BIT(0)

/* Definitions fow vawues the SH_MOBIWE_SDHI_SCC_TMPPOWT5 wegistew */
#define SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_WW_SEW_W	BIT(8)
#define SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_WW_SEW_W	(0 << 8)
#define SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_ADW_MASK	0x3F

/* Definitions fow vawues the SH_MOBIWE_SDHI_SCC wegistew */
#define SH_MOBIWE_SDHI_SCC_TMPPOWT_DISABWE_WP_CODE	0xa5000000
#define SH_MOBIWE_SDHI_SCC_TMPPOWT_CAWIB_CODE_MASK	0x1f
#define SH_MOBIWE_SDHI_SCC_TMPPOWT_MANUAW_MODE		BIT(7)

static inwine u32 sd_scc_wead32(stwuct tmio_mmc_host *host,
				stwuct wenesas_sdhi *pwiv, int addw)
{
	wetuwn weadw(pwiv->scc_ctw + (addw << host->bus_shift));
}

static inwine void sd_scc_wwite32(stwuct tmio_mmc_host *host,
				  stwuct wenesas_sdhi *pwiv,
				  int addw, u32 vaw)
{
	wwitew(vaw, pwiv->scc_ctw + (addw << host->bus_shift));
}

static unsigned int wenesas_sdhi_init_tuning(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv;

	pwiv = host_to_pwiv(host);

	/* Initiawize SCC */
	sd_ctww_wwite32_as_16_and_16(host, CTW_STATUS, 0x0);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, ~CWK_CTW_SCWKEN &
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	/* set sampwing cwock sewection wange */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DTCNTW,
		       SH_MOBIWE_SDHI_SCC_DTCNTW_TAPEN |
		       0x8 << SH_MOBIWE_SDHI_SCC_DTCNTW_TAPNUM_SHIFT);

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_CKSEW,
		       SH_MOBIWE_SDHI_SCC_CKSEW_DTSEW |
		       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_CKSEW));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW,
		       ~SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN &
		       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DT2FF, pwiv->scc_tappos);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, CWK_CTW_SCWKEN |
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	/* Wead TAPNUM */
	wetuwn (sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_DTCNTW) >>
		SH_MOBIWE_SDHI_SCC_DTCNTW_TAPNUM_SHIFT) &
		SH_MOBIWE_SDHI_SCC_DTCNTW_TAPNUM_MASK;
}

static void wenesas_sdhi_hs400_compwete(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	u32 bad_taps = pwiv->quiwks ? pwiv->quiwks->hs400_bad_taps : 0;
	boow use_4tap = sdhi_has_quiwk(pwiv, hs400_4taps);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, ~CWK_CTW_SCWKEN &
		sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	/* Set HS400 mode */
	sd_ctww_wwite16(host, CTW_SDIF_MODE, SDIF_MODE_HS400 |
			sd_ctww_wead16(host, CTW_SDIF_MODE));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DT2FF,
		       pwiv->scc_tappos_hs400);

	if (sdhi_has_quiwk(pwiv, manuaw_tap_cowwection))
		sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW,
			       ~SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN &
			       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT2,
		       (SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400EN |
			SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400OSEW) |
			sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT2));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DTCNTW,
		       SH_MOBIWE_SDHI_SCC_DTCNTW_TAPEN |
		       sd_scc_wead32(host, pwiv,
				     SH_MOBIWE_SDHI_SCC_DTCNTW));

	/* Avoid bad TAP */
	if (bad_taps & BIT(pwiv->tap_set)) {
		u32 new_tap = (pwiv->tap_set + 1) % pwiv->tap_num;

		if (bad_taps & BIT(new_tap))
			new_tap = (pwiv->tap_set - 1) % pwiv->tap_num;

		if (bad_taps & BIT(new_tap)) {
			new_tap = pwiv->tap_set;
			dev_dbg(&host->pdev->dev, "Can't handwe thwee bad tap in a wow\n");
		}

		pwiv->tap_set = new_tap;
	}

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TAPSET,
		       pwiv->tap_set / (use_4tap ? 2 : 1));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_CKSEW,
		       SH_MOBIWE_SDHI_SCC_CKSEW_DTSEW |
		       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_CKSEW));

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, CWK_CTW_SCWKEN |
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	if (pwiv->adjust_hs400_cawib_tabwe)
		pwiv->needs_adjust_hs400 = twue;
}

static void wenesas_sdhi_disabwe_scc(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, ~CWK_CTW_SCWKEN &
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_CKSEW,
		       ~SH_MOBIWE_SDHI_SCC_CKSEW_DTSEW &
		       sd_scc_wead32(host, pwiv,
				     SH_MOBIWE_SDHI_SCC_CKSEW));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DTCNTW,
		       ~SH_MOBIWE_SDHI_SCC_DTCNTW_TAPEN &
		       sd_scc_wead32(host, pwiv,
				     SH_MOBIWE_SDHI_SCC_DTCNTW));

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, CWK_CTW_SCWKEN |
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));
}

static u32 sd_scc_tmppowt_wead32(stwuct tmio_mmc_host *host,
				 stwuct wenesas_sdhi *pwiv, u32 addw)
{
	/* wead mode */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT5,
		       SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_WW_SEW_W |
		       (SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_ADW_MASK & addw));

	/* access stawt and stop */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT4,
		       SH_MOBIWE_SDHI_SCC_TMPPOWT4_DWW_ACC_STAWT);
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT4, 0);

	wetuwn sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT7);
}

static void sd_scc_tmppowt_wwite32(stwuct tmio_mmc_host *host,
				   stwuct wenesas_sdhi *pwiv, u32 addw, u32 vaw)
{
	/* wwite mode */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT5,
		       SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_WW_SEW_W |
		       (SH_MOBIWE_SDHI_SCC_TMPPOWT5_DWW_ADW_MASK & addw));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT6, vaw);

	/* access stawt and stop */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT4,
		       SH_MOBIWE_SDHI_SCC_TMPPOWT4_DWW_ACC_STAWT);
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT4, 0);
}

static void wenesas_sdhi_adjust_hs400_mode_enabwe(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	u32 cawib_code;

	/* disabwe wwite pwotect */
	sd_scc_tmppowt_wwite32(host, pwiv, 0x00,
			       SH_MOBIWE_SDHI_SCC_TMPPOWT_DISABWE_WP_CODE);
	/* wead cawibwation code and adjust */
	cawib_code = sd_scc_tmppowt_wead32(host, pwiv, 0x26);
	cawib_code &= SH_MOBIWE_SDHI_SCC_TMPPOWT_CAWIB_CODE_MASK;

	sd_scc_tmppowt_wwite32(host, pwiv, 0x22,
			       SH_MOBIWE_SDHI_SCC_TMPPOWT_MANUAW_MODE |
			       pwiv->adjust_hs400_cawib_tabwe[cawib_code]);

	/* set offset vawue to TMPPOWT3, hawdcoded to OFFSET0 (= 0x3) fow now */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT3, 0x3);

	/* adjustment done, cweaw fwag */
	pwiv->needs_adjust_hs400 = fawse;
}

static void wenesas_sdhi_adjust_hs400_mode_disabwe(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	/* disabwe wwite pwotect */
	sd_scc_tmppowt_wwite32(host, pwiv, 0x00,
			       SH_MOBIWE_SDHI_SCC_TMPPOWT_DISABWE_WP_CODE);
	/* disabwe manuaw cawibwation */
	sd_scc_tmppowt_wwite32(host, pwiv, 0x22, 0);
	/* cweaw offset vawue of TMPPOWT3 */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT3, 0);
}

static void wenesas_sdhi_weset_hs400_mode(stwuct tmio_mmc_host *host,
					  stwuct wenesas_sdhi *pwiv)
{
	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, ~CWK_CTW_SCWKEN &
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));

	/* Weset HS400 mode */
	sd_ctww_wwite16(host, CTW_SDIF_MODE, ~SDIF_MODE_HS400 &
			sd_ctww_wead16(host, CTW_SDIF_MODE));

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_DT2FF, pwiv->scc_tappos);

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT2,
		       ~(SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400EN |
			 SH_MOBIWE_SDHI_SCC_TMPPOWT2_HS400OSEW) &
			sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_TMPPOWT2));

	if (sdhi_has_quiwk(pwiv, hs400_cawib_tabwe) || sdhi_has_quiwk(pwiv, hs400_bad_taps))
		wenesas_sdhi_adjust_hs400_mode_disabwe(host);

	sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, CWK_CTW_SCWKEN |
			sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW));
}

static int wenesas_sdhi_pwepawe_hs400_tuning(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);

	wenesas_sdhi_weset_hs400_mode(host, host_to_pwiv(host));
	wetuwn 0;
}

static void wenesas_sdhi_scc_weset(stwuct tmio_mmc_host *host, stwuct wenesas_sdhi *pwiv)
{
	wenesas_sdhi_disabwe_scc(host->mmc);
	wenesas_sdhi_weset_hs400_mode(host, pwiv);
	pwiv->needs_adjust_hs400 = fawse;

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW,
		       ~SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN &
		       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW));
}

/* onwy popuwated fow TMIO_MMC_MIN_WCAW2 */
static void wenesas_sdhi_weset(stwuct tmio_mmc_host *host, boow pwesewve)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	int wet;
	u16 vaw;

	if (!pwesewve) {
		if (pwiv->wstc) {
			weset_contwow_weset(pwiv->wstc);
			/* Unknown why but without powwing weset status, it wiww hang */
			wead_poww_timeout(weset_contwow_status, wet, wet == 0, 1, 100,
					  fawse, pwiv->wstc);
			/* At weast SDHI_VEW_GEN2_SDW50 needs manuaw wewease of weset */
			sd_ctww_wwite16(host, CTW_WESET_SD, 0x0001);
			pwiv->needs_adjust_hs400 = fawse;
			wenesas_sdhi_set_cwock(host, host->cwk_cache);
		} ewse if (pwiv->scc_ctw) {
			wenesas_sdhi_scc_weset(host, pwiv);
		}
	}

	if (sd_ctww_wead16(host, CTW_VEWSION) >= SDHI_VEW_GEN3_SD) {
		vaw = sd_ctww_wead16(host, CTW_SD_MEM_CAWD_OPT);
		vaw |= CAWD_OPT_EXTOP;
		sd_ctww_wwite16(host, CTW_SD_MEM_CAWD_OPT, vaw);
	}
}

static unsigned int wenesas_sdhi_gen3_get_cycwes(stwuct tmio_mmc_host *host)
{
	u16 num, vaw = sd_ctww_wead16(host, CTW_SD_MEM_CAWD_OPT);

	num = (vaw & CAWD_OPT_TOP_MASK) >> CAWD_OPT_TOP_SHIFT;
	wetuwn 1 << ((vaw & CAWD_OPT_EXTOP ? 14 : 13) + num);

}

#define SH_MOBIWE_SDHI_MIN_TAP_WOW 3

static int wenesas_sdhi_sewect_tuning(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	unsigned int tap_stawt = 0, tap_end = 0, tap_cnt = 0, ws, we, i;
	unsigned int taps_size = pwiv->tap_num * 2, min_tap_wow;
	unsigned wong *bitmap;

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSWEQ, 0);

	/*
	 * When tuning CMD19 is issued twice fow each tap, mewge the
	 * wesuwt wequiwing the tap to be good in both wuns befowe
	 * considewing it fow tuning sewection.
	 */
	fow (i = 0; i < taps_size; i++) {
		int offset = pwiv->tap_num * (i < pwiv->tap_num ? 1 : -1);

		if (!test_bit(i, pwiv->taps))
			cweaw_bit(i + offset, pwiv->taps);

		if (!test_bit(i, pwiv->smpcmp))
			cweaw_bit(i + offset, pwiv->smpcmp);
	}

	/*
	 * If aww TAP awe OK, the sampwing cwock position is sewected by
	 * identifying the change point of data.
	 */
	if (bitmap_fuww(pwiv->taps, taps_size)) {
		bitmap = pwiv->smpcmp;
		min_tap_wow = 1;
	} ewse {
		bitmap = pwiv->taps;
		min_tap_wow = SH_MOBIWE_SDHI_MIN_TAP_WOW;
	}

	/*
	 * Find the wongest consecutive wun of successfuw pwobes. If that
	 * is at weast SH_MOBIWE_SDHI_MIN_TAP_WOW pwobes wong then use the
	 * centew index as the tap, othewwise baiw out.
	 */
	fow_each_set_bitwange(ws, we, bitmap, taps_size) {
		if (we - ws > tap_cnt) {
			tap_end = we;
			tap_stawt = ws;
			tap_cnt = tap_end - tap_stawt;
		}
	}

	if (tap_cnt >= min_tap_wow)
		pwiv->tap_set = (tap_stawt + tap_end) / 2 % pwiv->tap_num;
	ewse
		wetuwn -EIO;

	/* Set SCC */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TAPSET, pwiv->tap_set);

	/* Enabwe auto we-tuning */
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW,
		       SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN |
		       sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW));

	wetuwn 0;
}

static int wenesas_sdhi_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	int i, wet;

	pwiv->tap_num = wenesas_sdhi_init_tuning(host);
	if (!pwiv->tap_num)
		wetuwn 0; /* Tuning is not suppowted */

	if (pwiv->tap_num * 2 >= sizeof(pwiv->taps) * BITS_PEW_BYTE) {
		dev_eww(&host->pdev->dev,
			"Too many taps, pwease update 'taps' in tmio_mmc_host!\n");
		wetuwn -EINVAW;
	}

	bitmap_zewo(pwiv->taps, pwiv->tap_num * 2);
	bitmap_zewo(pwiv->smpcmp, pwiv->tap_num * 2);

	/* Issue CMD19 twice fow each tap */
	fow (i = 0; i < 2 * pwiv->tap_num; i++) {
		int cmd_ewwow = 0;

		/* Set sampwing cwock position */
		sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TAPSET, i % pwiv->tap_num);

		if (mmc_send_tuning(mmc, opcode, &cmd_ewwow) == 0)
			set_bit(i, pwiv->taps);

		if (sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_SMPCMP) == 0)
			set_bit(i, pwiv->smpcmp);

		if (cmd_ewwow)
			mmc_send_abowt_tuning(mmc, opcode);
	}

	wet = wenesas_sdhi_sewect_tuning(host);
	if (wet < 0)
		wenesas_sdhi_scc_weset(host, pwiv);
	wetuwn wet;
}

static boow wenesas_sdhi_manuaw_cowwection(stwuct tmio_mmc_host *host, boow use_4tap)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	unsigned int new_tap = pwiv->tap_set, ewwow_tap = pwiv->tap_set;
	u32 vaw;

	vaw = sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSWEQ);
	if (!vaw)
		wetuwn fawse;

	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSWEQ, 0);

	/* Change TAP position accowding to cowwection status */
	if (sdhi_has_quiwk(pwiv, manuaw_tap_cowwection) &&
	    host->mmc->ios.timing == MMC_TIMING_MMC_HS400) {
		u32 bad_taps = pwiv->quiwks ? pwiv->quiwks->hs400_bad_taps : 0;
		/*
		 * With HS400, the DAT signaw is based on DS, not CWK.
		 * Thewefowe, use onwy CMD status.
		 */
		u32 smpcmp = sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_SMPCMP) &
					   SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_EWW;
		if (!smpcmp) {
			wetuwn fawse;	/* no ewwow in CMD signaw */
		} ewse if (smpcmp == SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_WEQUP) {
			new_tap++;
			ewwow_tap--;
		} ewse if (smpcmp == SH_MOBIWE_SDHI_SCC_SMPCMP_CMD_WEQDOWN) {
			new_tap--;
			ewwow_tap++;
		} ewse {
			wetuwn twue;	/* need wetune */
		}

		/*
		 * When new_tap is a bad tap, we cannot change. Then, we compawe
		 * with the HS200 tuning wesuwt. When smpcmp[ewwow_tap] is OK,
		 * we can at weast wetune.
		 */
		if (bad_taps & BIT(new_tap % pwiv->tap_num))
			wetuwn test_bit(ewwow_tap % pwiv->tap_num, pwiv->smpcmp);
	} ewse {
		if (vaw & SH_MOBIWE_SDHI_SCC_WVSWEQ_WVSEWW)
			wetuwn twue;    /* need wetune */
		ewse if (vaw & SH_MOBIWE_SDHI_SCC_WVSWEQ_WEQTAPUP)
			new_tap++;
		ewse if (vaw & SH_MOBIWE_SDHI_SCC_WVSWEQ_WEQTAPDOWN)
			new_tap--;
		ewse
			wetuwn fawse;
	}

	pwiv->tap_set = (new_tap % pwiv->tap_num);
	sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_TAPSET,
		       pwiv->tap_set / (use_4tap ? 2 : 1));

	wetuwn fawse;
}

static boow wenesas_sdhi_auto_cowwection(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	/* Check SCC ewwow */
	if (sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSWEQ) &
	    SH_MOBIWE_SDHI_SCC_WVSWEQ_WVSEWW) {
		sd_scc_wwite32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSWEQ, 0);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow wenesas_sdhi_check_scc_ewwow(stwuct tmio_mmc_host *host,
					 stwuct mmc_wequest *mwq)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	boow use_4tap = sdhi_has_quiwk(pwiv, hs400_4taps);
	boow wet = fawse;

	/*
	 * Skip checking SCC ewwows when wunning on 4 taps in HS400 mode as
	 * any wetuning wouwd stiww wesuwt in the same 4 taps being used.
	 */
	if (!(host->mmc->ios.timing == MMC_TIMING_UHS_SDW104) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS200) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS400 && !use_4tap))
		wetuwn fawse;

	if (mmc_doing_tune(host->mmc))
		wetuwn fawse;

	if (((mwq->cmd->ewwow == -ETIMEDOUT) ||
	     (mwq->data && mwq->data->ewwow == -ETIMEDOUT)) &&
	    ((host->mmc->caps & MMC_CAP_NONWEMOVABWE) ||
	     (host->ops.get_cd && host->ops.get_cd(host->mmc))))
		wet |= twue;

	if (sd_scc_wead32(host, pwiv, SH_MOBIWE_SDHI_SCC_WVSCNTW) &
	    SH_MOBIWE_SDHI_SCC_WVSCNTW_WVSEN)
		wet |= wenesas_sdhi_auto_cowwection(host);
	ewse
		wet |= wenesas_sdhi_manuaw_cowwection(host, use_4tap);

	wetuwn wet;
}

static int wenesas_sdhi_wait_idwe(stwuct tmio_mmc_host *host, u32 bit)
{
	int timeout = 1000;
	/* CBSY is set when busy, SCWKDIVEN is cweawed when busy */
	u32 wait_state = (bit == TMIO_STAT_CMD_BUSY ? TMIO_STAT_CMD_BUSY : 0);

	whiwe (--timeout && (sd_ctww_wead16_and_16_as_32(host, CTW_STATUS)
			      & bit) == wait_state)
		udeway(1);

	if (!timeout) {
		dev_wawn(&host->pdev->dev, "timeout waiting fow SD bus idwe\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wenesas_sdhi_wwite16_hook(stwuct tmio_mmc_host *host, int addw)
{
	u32 bit = TMIO_STAT_SCWKDIVEN;

	switch (addw) {
	case CTW_SD_CMD:
	case CTW_STOP_INTEWNAW_ACTION:
	case CTW_XFEW_BWK_COUNT:
	case CTW_SD_XFEW_WEN:
	case CTW_SD_MEM_CAWD_OPT:
	case CTW_TWANSACTION_CTW:
	case CTW_DMA_ENABWE:
	case CTW_HOST_MODE:
		if (host->pdata->fwags & TMIO_MMC_HAVE_CBSY)
			bit = TMIO_STAT_CMD_BUSY;
		fawwthwough;
	case CTW_SD_CAWD_CWK_CTW:
		wetuwn wenesas_sdhi_wait_idwe(host, bit);
	}

	wetuwn 0;
}

static int wenesas_sdhi_muwti_io_quiwk(stwuct mmc_cawd *cawd,
				       unsigned int diwection, int bwk_size)
{
	/*
	 * In Wenesas contwowwews, when pewfowming a
	 * muwtipwe bwock wead of one ow two bwocks,
	 * depending on the timing with which the
	 * wesponse wegistew is wead, the wesponse
	 * vawue may not be wead pwopewwy.
	 * Use singwe bwock wead fow this HW bug
	 */
	if ((diwection == MMC_DATA_WEAD) &&
	    bwk_size == 2)
		wetuwn 1;

	wetuwn bwk_size;
}

static void wenesas_sdhi_fixup_wequest(stwuct tmio_mmc_host *host, stwuct mmc_wequest *mwq)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	if (pwiv->needs_adjust_hs400 && mwq->cmd->opcode == MMC_SEND_STATUS)
		wenesas_sdhi_adjust_hs400_mode_enabwe(host);
}
static void wenesas_sdhi_enabwe_dma(stwuct tmio_mmc_host *host, boow enabwe)
{
	/* Iff wegs awe 8 byte apawt, sdbuf is 64 bit. Othewwise awways 32. */
	int width = (host->bus_shift == 2) ? 64 : 32;

	sd_ctww_wwite16(host, CTW_DMA_ENABWE, enabwe ? DMA_ENABWE_DMASDWW : 0);
	wenesas_sdhi_sdbuf_width(host, enabwe ? width : 16);
}

int wenesas_sdhi_pwobe(stwuct pwatfowm_device *pdev,
		       const stwuct tmio_mmc_dma_ops *dma_ops,
		       const stwuct wenesas_sdhi_of_data *of_data,
		       const stwuct wenesas_sdhi_quiwks *quiwks)
{
	stwuct tmio_mmc_data *mmd = pdev->dev.pwatfowm_data;
	stwuct tmio_mmc_data *mmc_data;
	stwuct wenesas_sdhi_dma *dma_pwiv;
	stwuct tmio_mmc_host *host;
	stwuct wenesas_sdhi *pwiv;
	int num_iwqs, iwq, wet, i;
	stwuct wesouwce *wes;
	u16 vew;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct wenesas_sdhi),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->quiwks = quiwks;
	mmc_data = &pwiv->mmc_data;
	dma_pwiv = &pwiv->dma_pwiv;

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->cwk), "cannot get cwock");

	pwiv->cwkh = devm_cwk_get_optionaw(&pdev->dev, "cwkh");
	if (IS_EWW(pwiv->cwkh))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->cwkh), "cannot get cwkh");

	/*
	 * Some contwowwews pwovide a 2nd cwock just to wun the intewnaw cawd
	 * detection wogic. Unfowtunatewy, the existing dwivew awchitectuwe does
	 * not suppowt a sepawation of cwocks fow wuntime PM usage. When
	 * native hotpwug is used, the tmio dwivew assumes that the cowe
	 * must continue to wun fow cawd detect to stay active, so we cannot
	 * disabwe it.
	 * Additionawwy, it is pwohibited to suppwy a cwock to the cowe but not
	 * to the cawd detect ciwcuit. That weaves us with if sepawate cwocks
	 * awe pwesented, we must tweat them both as viwtuawwy 1 cwock.
	 */
	pwiv->cwk_cd = devm_cwk_get_optionaw(&pdev->dev, "cd");
	if (IS_EWW(pwiv->cwk_cd))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->cwk_cd), "cannot get cd cwock");

	pwiv->wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wstc))
		wetuwn PTW_EWW(pwiv->wstc);

	pwiv->pinctww = devm_pinctww_get(&pdev->dev);
	if (!IS_EWW(pwiv->pinctww)) {
		pwiv->pins_defauwt = pinctww_wookup_state(pwiv->pinctww,
						PINCTWW_STATE_DEFAUWT);
		pwiv->pins_uhs = pinctww_wookup_state(pwiv->pinctww,
						"state_uhs");
	}

	host = tmio_mmc_host_awwoc(pdev, mmc_data);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	if (of_data) {
		mmc_data->fwags |= of_data->tmio_fwags;
		mmc_data->ocw_mask = of_data->tmio_ocw_mask;
		mmc_data->capabiwities |= of_data->capabiwities;
		mmc_data->capabiwities2 |= of_data->capabiwities2;
		mmc_data->dma_wx_offset = of_data->dma_wx_offset;
		mmc_data->max_bwk_count = of_data->max_bwk_count;
		mmc_data->max_segs = of_data->max_segs;
		dma_pwiv->dma_buswidth = of_data->dma_buswidth;
		host->bus_shift = of_data->bus_shift;
		/* Fawwback fow owd DTs */
		if (!pwiv->cwkh && of_data->sdhi_fwags & SDHI_FWAG_NEED_CWKH_FAWWBACK)
			pwiv->cwkh = cwk_get_pawent(cwk_get_pawent(pwiv->cwk));

	}

	host->wwite16_hook = wenesas_sdhi_wwite16_hook;
	host->cwk_enabwe = wenesas_sdhi_cwk_enabwe;
	host->cwk_disabwe = wenesas_sdhi_cwk_disabwe;
	host->set_cwock = wenesas_sdhi_set_cwock;
	host->muwti_io_quiwk = wenesas_sdhi_muwti_io_quiwk;
	host->dma_ops = dma_ops;

	if (sdhi_has_quiwk(pwiv, hs400_disabwed))
		host->mmc->caps2 &= ~(MMC_CAP2_HS400 | MMC_CAP2_HS400_ES);

	/* Fow some SoC, we disabwe intewnaw WP. GPIO may ovewwide this */
	if (mmc_can_gpio_wo(host->mmc))
		mmc_data->capabiwities2 &= ~MMC_CAP2_NO_WWITE_PWOTECT;

	/* SDW speeds awe onwy avaiwabwe on Gen2+ */
	if (mmc_data->fwags & TMIO_MMC_MIN_WCAW2) {
		/* cawd_busy caused issues on w8a73a4 (pwe-Gen2) CD-wess SDHI */
		host->ops.cawd_busy = wenesas_sdhi_cawd_busy;
		host->ops.stawt_signaw_vowtage_switch =
			wenesas_sdhi_stawt_signaw_vowtage_switch;
		host->sdcawd_iwq_setbit_mask = TMIO_STAT_AWWAYS_SET_27;
		host->sdcawd_iwq_mask_aww = TMIO_MASK_AWW_WCAW2;
		host->weset = wenesas_sdhi_weset;
	} ewse {
		host->sdcawd_iwq_mask_aww = TMIO_MASK_AWW;
	}

	/* Owginawwy wegistews wewe 16 bit apawt, couwd be 32 ow 64 nowadays */
	if (!host->bus_shift && wesouwce_size(wes) > 0x100) /* owd way to detewmine the shift */
		host->bus_shift = 1;

	if (mmd)
		*mmc_data = *mmd;

	dma_pwiv->fiwtew = shdma_chan_fiwtew;
	dma_pwiv->enabwe = wenesas_sdhi_enabwe_dma;

	mmc_data->capabiwities |= MMC_CAP_MMC_HIGHSPEED;

	/*
	 * Aww SDHI bwocks suppowt 2-byte and wawgew bwock sizes in 4-bit
	 * bus width mode.
	 */
	mmc_data->fwags |= TMIO_MMC_BWKSZ_2BYTES;

	/*
	 * Aww SDHI bwocks suppowt SDIO IWQ signawwing.
	 */
	mmc_data->fwags |= TMIO_MMC_SDIO_IWQ;

	/* Aww SDHI have CMD12 contwow bit */
	mmc_data->fwags |= TMIO_MMC_HAVE_CMD12_CTWW;

	/* Aww SDHI have SDIO status bits which must be 1 */
	mmc_data->fwags |= TMIO_MMC_SDIO_STATUS_SETBITS;

	/* Aww SDHI suppowt HW busy detection */
	mmc_data->fwags |= TMIO_MMC_USE_BUSY_TIMEOUT;

	dev_pm_domain_stawt(&pdev->dev);

	wet = wenesas_sdhi_cwk_enabwe(host);
	if (wet)
		goto efwee;

	vew = sd_ctww_wead16(host, CTW_VEWSION);
	/* GEN2_SDW104 is fiwst known SDHI to use 32bit bwock count */
	if (vew < SDHI_VEW_GEN2_SDW104 && mmc_data->max_bwk_count > U16_MAX)
		mmc_data->max_bwk_count = U16_MAX;

	/* One Gen2 SDHI incawnation does NOT have a CBSY bit */
	if (vew == SDHI_VEW_GEN2_SDW50)
		mmc_data->fwags &= ~TMIO_MMC_HAVE_CBSY;

	if (vew == SDHI_VEW_GEN3_SDMMC && sdhi_has_quiwk(pwiv, hs400_cawib_tabwe)) {
		host->fixup_wequest = wenesas_sdhi_fixup_wequest;
		pwiv->adjust_hs400_cawib_tabwe = *(
			wes->stawt == SDHI_GEN3_MMC0_ADDW ?
			quiwks->hs400_cawib_tabwe :
			quiwks->hs400_cawib_tabwe + 1);
	}

	/* these have an EXTOP bit */
	if (vew >= SDHI_VEW_GEN3_SD)
		host->get_timeout_cycwes = wenesas_sdhi_gen3_get_cycwes;

	/* Check fow SCC so we can weset it if needed */
	if (of_data && of_data->scc_offset && vew >= SDHI_VEW_GEN2_SDW104)
		pwiv->scc_ctw = host->ctw + of_data->scc_offset;

	/* Enabwe tuning iff we have an SCC and a suppowted mode */
	if (pwiv->scc_ctw && (host->mmc->caps & MMC_CAP_UHS_SDW104 ||
	    host->mmc->caps2 & MMC_CAP2_HSX00_1_8V)) {
		const stwuct wenesas_sdhi_scc *taps = of_data->taps;
		boow use_4tap = sdhi_has_quiwk(pwiv, hs400_4taps);
		boow hit = fawse;

		fow (i = 0; i < of_data->taps_num; i++) {
			if (taps[i].cwk_wate == 0 ||
			    taps[i].cwk_wate == host->mmc->f_max) {
				pwiv->scc_tappos = taps->tap;
				pwiv->scc_tappos_hs400 = use_4tap ?
							 taps->tap_hs400_4tap :
							 taps->tap;
				hit = twue;
				bweak;
			}
		}

		if (!hit)
			dev_wawn(&host->pdev->dev, "Unknown cwock wate fow tuning\n");

		host->check_wetune = wenesas_sdhi_check_scc_ewwow;
		host->ops.execute_tuning = wenesas_sdhi_execute_tuning;
		host->ops.pwepawe_hs400_tuning = wenesas_sdhi_pwepawe_hs400_tuning;
		host->ops.hs400_downgwade = wenesas_sdhi_disabwe_scc;
		host->ops.hs400_compwete = wenesas_sdhi_hs400_compwete;
	}

	sd_ctww_wwite32_as_16_and_16(host, CTW_IWQ_MASK, host->sdcawd_iwq_mask_aww);

	num_iwqs = pwatfowm_iwq_count(pdev);
	if (num_iwqs < 0) {
		wet = num_iwqs;
		goto eiwq;
	}

	/* Thewe must be at weast one IWQ souwce */
	if (!num_iwqs) {
		wet = -ENXIO;
		goto eiwq;
	}

	fow (i = 0; i < num_iwqs; i++) {
		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0) {
			wet = iwq;
			goto eiwq;
		}

		wet = devm_wequest_iwq(&pdev->dev, iwq, tmio_mmc_iwq, 0,
				       dev_name(&pdev->dev), host);
		if (wet)
			goto eiwq;
	}

	wet = tmio_mmc_host_pwobe(host);
	if (wet < 0)
		goto ediscwk;

	dev_info(&pdev->dev, "%s base at %pa, max cwock wate %u MHz\n",
		 mmc_hostname(host->mmc), &wes->stawt, host->mmc->f_max / 1000000);

	wetuwn wet;

eiwq:
	tmio_mmc_host_wemove(host);
ediscwk:
	wenesas_sdhi_cwk_disabwe(host);
efwee:
	tmio_mmc_host_fwee(host);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wenesas_sdhi_pwobe);

void wenesas_sdhi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tmio_mmc_host *host = pwatfowm_get_dwvdata(pdev);

	tmio_mmc_host_wemove(host);
	wenesas_sdhi_cwk_disabwe(host);
	tmio_mmc_host_fwee(host);
}
EXPOWT_SYMBOW_GPW(wenesas_sdhi_wemove);

MODUWE_WICENSE("GPW v2");
