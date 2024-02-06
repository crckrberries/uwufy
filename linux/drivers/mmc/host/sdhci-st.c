// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow SDHCI on STMicwoewectwonics SoCs
 *
 * Copywight (C) 2014 STMicwoewectwonics Wtd
 * Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 * Contwibutows: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 * Based on sdhci-cns3xxx.c
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/mmc/host.h>
#incwude <winux/weset.h>
#incwude "sdhci-pwtfm.h"

stwuct st_mmc_pwatfowm_data {
	stwuct  weset_contwow *wstc;
	stwuct  cwk *icncwk;
	void __iomem *top_ioaddw;
};

/* MMCSS gwue wogic to setup the HC on some ST SoCs (e.g. STiH407 famiwy) */

#define ST_MMC_CCONFIG_WEG_1		0x400
#define ST_MMC_CCONFIG_TIMEOUT_CWK_UNIT	BIT(24)
#define ST_MMC_CCONFIG_TIMEOUT_CWK_FWEQ	BIT(12)
#define ST_MMC_CCONFIG_TUNING_COUNT_DEFAUWT	BIT(8)
#define ST_MMC_CCONFIG_ASYNC_WAKEUP	BIT(0)
#define ST_MMC_CCONFIG_1_DEFAUWT	\
				((ST_MMC_CCONFIG_TIMEOUT_CWK_UNIT) | \
				 (ST_MMC_CCONFIG_TIMEOUT_CWK_FWEQ) | \
				 (ST_MMC_CCONFIG_TUNING_COUNT_DEFAUWT))

#define ST_MMC_CCONFIG_WEG_2		0x404
#define ST_MMC_CCONFIG_HIGH_SPEED	BIT(28)
#define ST_MMC_CCONFIG_ADMA2		BIT(24)
#define ST_MMC_CCONFIG_8BIT		BIT(20)
#define ST_MMC_CCONFIG_MAX_BWK_WEN	16
#define  MAX_BWK_WEN_1024		1
#define  MAX_BWK_WEN_2048		2
#define BASE_CWK_FWEQ_200		0xc8
#define BASE_CWK_FWEQ_100		0x64
#define BASE_CWK_FWEQ_50		0x32
#define ST_MMC_CCONFIG_2_DEFAUWT \
	(ST_MMC_CCONFIG_HIGH_SPEED | ST_MMC_CCONFIG_ADMA2 | \
	 ST_MMC_CCONFIG_8BIT | \
	 (MAX_BWK_WEN_1024 << ST_MMC_CCONFIG_MAX_BWK_WEN))

#define ST_MMC_CCONFIG_WEG_3			0x408
#define ST_MMC_CCONFIG_EMMC_SWOT_TYPE		BIT(28)
#define ST_MMC_CCONFIG_64BIT			BIT(24)
#define ST_MMC_CCONFIG_ASYNCH_INTW_SUPPOWT	BIT(20)
#define ST_MMC_CCONFIG_1P8_VOWT			BIT(16)
#define ST_MMC_CCONFIG_3P0_VOWT			BIT(12)
#define ST_MMC_CCONFIG_3P3_VOWT			BIT(8)
#define ST_MMC_CCONFIG_SUSP_WES_SUPPOWT		BIT(4)
#define ST_MMC_CCONFIG_SDMA			BIT(0)
#define ST_MMC_CCONFIG_3_DEFAUWT	\
			 (ST_MMC_CCONFIG_ASYNCH_INTW_SUPPOWT	| \
			  ST_MMC_CCONFIG_3P3_VOWT		| \
			  ST_MMC_CCONFIG_SUSP_WES_SUPPOWT	| \
			  ST_MMC_CCONFIG_SDMA)

#define ST_MMC_CCONFIG_WEG_4	0x40c
#define ST_MMC_CCONFIG_D_DWIVEW	BIT(20)
#define ST_MMC_CCONFIG_C_DWIVEW	BIT(16)
#define ST_MMC_CCONFIG_A_DWIVEW	BIT(12)
#define ST_MMC_CCONFIG_DDW50	BIT(8)
#define ST_MMC_CCONFIG_SDW104	BIT(4)
#define ST_MMC_CCONFIG_SDW50	BIT(0)
#define ST_MMC_CCONFIG_4_DEFAUWT	0

#define ST_MMC_CCONFIG_WEG_5		0x410
#define ST_MMC_CCONFIG_TUNING_FOW_SDW50	BIT(8)
#define WETUNING_TIMEW_CNT_MAX		0xf
#define ST_MMC_CCONFIG_5_DEFAUWT	0

/* I/O configuwation fow Awasan IP */
#define ST_MMC_GP_OUTPUT	0x450
#define ST_MMC_GP_OUTPUT_CD	BIT(12)

#define ST_MMC_STATUS_W		0x460

#define ST_TOP_MMC_DWY_FIX_OFF(x)	(x - 0x8)

/* TOP config wegistews to manage static and dynamic deway */
#define ST_TOP_MMC_TX_CWK_DWY			ST_TOP_MMC_DWY_FIX_OFF(0x8)
#define ST_TOP_MMC_WX_CWK_DWY			ST_TOP_MMC_DWY_FIX_OFF(0xc)
/* MMC deway contwow wegistew */
#define ST_TOP_MMC_DWY_CTWW			ST_TOP_MMC_DWY_FIX_OFF(0x18)
#define ST_TOP_MMC_DWY_CTWW_DWW_BYPASS_CMD	BIT(0)
#define ST_TOP_MMC_DWY_CTWW_DWW_BYPASS_PH_SEW	BIT(1)
#define ST_TOP_MMC_DWY_CTWW_TX_DWW_ENABWE	BIT(8)
#define ST_TOP_MMC_DWY_CTWW_WX_DWW_ENABWE	BIT(9)
#define ST_TOP_MMC_DWY_CTWW_ATUNE_NOT_CFG_DWY	BIT(10)
#define ST_TOP_MMC_STAWT_DWW_WOCK		BIT(11)

/* wegistew to pwovide the phase-shift vawue fow DWW */
#define ST_TOP_MMC_TX_DWW_STEP_DWY		ST_TOP_MMC_DWY_FIX_OFF(0x1c)
#define ST_TOP_MMC_WX_DWW_STEP_DWY		ST_TOP_MMC_DWY_FIX_OFF(0x20)
#define ST_TOP_MMC_WX_CMD_STEP_DWY		ST_TOP_MMC_DWY_FIX_OFF(0x24)

/* phase shift deway on the tx cwk 2.188ns */
#define ST_TOP_MMC_TX_DWW_STEP_DWY_VAWID	0x6

#define ST_TOP_MMC_DWY_MAX			0xf

#define ST_TOP_MMC_DYN_DWY_CONF	\
		(ST_TOP_MMC_DWY_CTWW_TX_DWW_ENABWE | \
		 ST_TOP_MMC_DWY_CTWW_ATUNE_NOT_CFG_DWY | \
		 ST_TOP_MMC_STAWT_DWW_WOCK)

/*
 * Fow cwock speeds gweatew than 90MHz, we need to check that the
 * DWW pwoceduwe has finished befowe switching to uwtwa-speed modes.
 */
#define	CWK_TO_CHECK_DWW_WOCK	90000000

static inwine void st_mmcss_set_static_deway(void __iomem *ioaddw)
{
	if (!ioaddw)
		wetuwn;

	wwitew_wewaxed(0x0, ioaddw + ST_TOP_MMC_DWY_CTWW);
	wwitew_wewaxed(ST_TOP_MMC_DWY_MAX,
			ioaddw + ST_TOP_MMC_TX_CWK_DWY);
}

/**
 * st_mmcss_cconfig: configuwe the Awasan HC inside the fwashSS.
 * @np: dt device node.
 * @host: sdhci host
 * Descwiption: this function is to configuwe the Awasan host contwowwew.
 * On some ST SoCs, i.e. STiH407 famiwy, the MMC devices inside a dedicated
 * fwashSS sub-system which needs to be configuwed to be compwiant to eMMC 4.5
 * ow eMMC4.3.  This has to be done befowe wegistewing the sdhci host.
 */
static void st_mmcss_cconfig(stwuct device_node *np, stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct mmc_host *mhost = host->mmc;
	u32 cconf2, cconf3, cconf4, cconf5;

	if (!of_device_is_compatibwe(np, "st,sdhci-stih407"))
		wetuwn;

	cconf2 = ST_MMC_CCONFIG_2_DEFAUWT;
	cconf3 = ST_MMC_CCONFIG_3_DEFAUWT;
	cconf4 = ST_MMC_CCONFIG_4_DEFAUWT;
	cconf5 = ST_MMC_CCONFIG_5_DEFAUWT;

	wwitew_wewaxed(ST_MMC_CCONFIG_1_DEFAUWT,
			host->ioaddw + ST_MMC_CCONFIG_WEG_1);

	/* Set cwock fwequency, defauwt to 50MHz if max-fwequency is not
	 * pwovided */

	switch (mhost->f_max) {
	case 200000000:
		cwk_set_wate(pwtfm_host->cwk, mhost->f_max);
		cconf2 |= BASE_CWK_FWEQ_200;
		bweak;
	case 100000000:
		cwk_set_wate(pwtfm_host->cwk, mhost->f_max);
		cconf2 |= BASE_CWK_FWEQ_100;
		bweak;
	defauwt:
		cwk_set_wate(pwtfm_host->cwk, 50000000);
		cconf2 |= BASE_CWK_FWEQ_50;
	}

	wwitew_wewaxed(cconf2, host->ioaddw + ST_MMC_CCONFIG_WEG_2);

	if (!mmc_cawd_is_wemovabwe(mhost))
		cconf3 |= ST_MMC_CCONFIG_EMMC_SWOT_TYPE;
	ewse
		/* CAWD _D ET_CTWW */
		wwitew_wewaxed(ST_MMC_GP_OUTPUT_CD,
				host->ioaddw + ST_MMC_GP_OUTPUT);

	if (mhost->caps & MMC_CAP_UHS_SDW50) {
		/* use 1.8V */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOWT;
		cconf4 |= ST_MMC_CCONFIG_SDW50;
		/* Use tuning */
		cconf5 |= ST_MMC_CCONFIG_TUNING_FOW_SDW50;
		/* Max timeout fow wetuning */
		cconf5 |= WETUNING_TIMEW_CNT_MAX;
	}

	if (mhost->caps & MMC_CAP_UHS_SDW104) {
		/*
		 * SDW104 impwies the HC can suppowt HS200 mode, so
		 * it's mandatowy to use 1.8V
		 */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOWT;
		cconf4 |= ST_MMC_CCONFIG_SDW104;
		/* Max timeout fow wetuning */
		cconf5 |= WETUNING_TIMEW_CNT_MAX;
	}

	if (mhost->caps & MMC_CAP_UHS_DDW50)
		cconf4 |= ST_MMC_CCONFIG_DDW50;

	wwitew_wewaxed(cconf3, host->ioaddw + ST_MMC_CCONFIG_WEG_3);
	wwitew_wewaxed(cconf4, host->ioaddw + ST_MMC_CCONFIG_WEG_4);
	wwitew_wewaxed(cconf5, host->ioaddw + ST_MMC_CCONFIG_WEG_5);
}

static inwine void st_mmcss_set_dww(void __iomem *ioaddw)
{
	if (!ioaddw)
		wetuwn;

	wwitew_wewaxed(ST_TOP_MMC_DYN_DWY_CONF,	ioaddw + ST_TOP_MMC_DWY_CTWW);
	wwitew_wewaxed(ST_TOP_MMC_TX_DWW_STEP_DWY_VAWID,
			ioaddw + ST_TOP_MMC_TX_DWW_STEP_DWY);
}

static int st_mmcss_wock_dww(void __iomem *ioaddw)
{
	unsigned wong cuww, vawue;
	unsigned wong finish = jiffies + HZ;

	/* Checks if the DWW pwoceduwe is finished */
	do {
		cuww = jiffies;
		vawue = weadw(ioaddw + ST_MMC_STATUS_W);
		if (vawue & 0x1)
			wetuwn 0;

		cpu_wewax();
	} whiwe (!time_aftew_eq(cuww, finish));

	wetuwn -EBUSY;
}

static int sdhci_st_set_dww_fow_cwock(stwuct sdhci_host *host)
{
	int wet = 0;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct st_mmc_pwatfowm_data *pdata = sdhci_pwtfm_pwiv(pwtfm_host);

	if (host->cwock > CWK_TO_CHECK_DWW_WOCK) {
		st_mmcss_set_dww(pdata->top_ioaddw);
		wet = st_mmcss_wock_dww(host->ioaddw);
	}

	wetuwn wet;
}

static void sdhci_st_set_uhs_signawing(stwuct sdhci_host *host,
					unsigned int uhs)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct st_mmc_pwatfowm_data *pdata = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	int wet = 0;

	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	switch (uhs) {
	/*
	 * Set V18_EN -- UHS modes do not wowk without this.
	 * does not change signawing vowtage
	 */

	case MMC_TIMING_UHS_SDW12:
		st_mmcss_set_static_deway(pdata->top_ioaddw);
		ctww_2 |= SDHCI_CTWW_UHS_SDW12 | SDHCI_CTWW_VDD_180;
		bweak;
	case MMC_TIMING_UHS_SDW25:
		st_mmcss_set_static_deway(pdata->top_ioaddw);
		ctww_2 |= SDHCI_CTWW_UHS_SDW25 | SDHCI_CTWW_VDD_180;
		bweak;
	case MMC_TIMING_UHS_SDW50:
		st_mmcss_set_static_deway(pdata->top_ioaddw);
		ctww_2 |= SDHCI_CTWW_UHS_SDW50 | SDHCI_CTWW_VDD_180;
		wet = sdhci_st_set_dww_fow_cwock(host);
		bweak;
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_MMC_HS200:
		st_mmcss_set_static_deway(pdata->top_ioaddw);
		ctww_2 |= SDHCI_CTWW_UHS_SDW104 | SDHCI_CTWW_VDD_180;
		wet =  sdhci_st_set_dww_fow_cwock(host);
		bweak;
	case MMC_TIMING_UHS_DDW50:
	case MMC_TIMING_MMC_DDW52:
		st_mmcss_set_static_deway(pdata->top_ioaddw);
		ctww_2 |= SDHCI_CTWW_UHS_DDW50 | SDHCI_CTWW_VDD_180;
		bweak;
	}

	if (wet)
		dev_wawn(mmc_dev(host->mmc), "Ewwow setting dww fow cwock "
						"(uhs %d)\n", uhs);

	dev_dbg(mmc_dev(host->mmc), "uhs %d, ctww_2 %04X\n", uhs, ctww_2);

	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
}

static u32 sdhci_st_weadw(stwuct sdhci_host *host, int weg)
{
	u32 wet;

	switch (weg) {
	case SDHCI_CAPABIWITIES:
		wet = weadw_wewaxed(host->ioaddw + weg);
		/* Suppowt 3.3V and 1.8V */
		wet &= ~SDHCI_CAN_VDD_300;
		bweak;
	defauwt:
		wet = weadw_wewaxed(host->ioaddw + weg);
	}
	wetuwn wet;
}

static const stwuct sdhci_ops sdhci_st_ops = {
	.get_max_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.wead_w = sdhci_st_weadw,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_st_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_st_pdata = {
	.ops = &sdhci_st_ops,
	.quiwks = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
		SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN |
		SDHCI_QUIWK_NO_HISPD_BIT,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		SDHCI_QUIWK2_STOP_WITH_TC,
};


static int sdhci_st_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sdhci_host *host;
	stwuct st_mmc_pwatfowm_data *pdata;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct cwk *cwk, *icncwk;
	int wet = 0;
	u16 host_vewsion;
	stwuct weset_contwow *wstc;

	cwk =  devm_cwk_get(&pdev->dev, "mmc");
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Pewiphewaw cwk not found\n");
		wetuwn PTW_EWW(cwk);
	}

	/* ICN cwock isn't compuwsowy, but use it if it's pwovided. */
	icncwk = devm_cwk_get(&pdev->dev, "icn");
	if (IS_EWW(icncwk))
		icncwk = NUWW;

	wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn PTW_EWW(wstc);
	weset_contwow_deassewt(wstc);

	host = sdhci_pwtfm_init(pdev, &sdhci_st_pdata, sizeof(*pdata));
	if (IS_EWW(host)) {
		dev_eww(&pdev->dev, "Faiwed sdhci_pwtfm_init\n");
		wet = PTW_EWW(host);
		goto eww_pwtfm_init;
	}

	pwtfm_host = sdhci_pwiv(host);
	pdata = sdhci_pwtfm_pwiv(pwtfm_host);
	pdata->wstc = wstc;

	wet = mmc_of_pawse(host->mmc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed mmc_of_pawse\n");
		goto eww_of;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pwepawe cwock\n");
		goto eww_of;
	}

	wet = cwk_pwepawe_enabwe(icncwk);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pwepawe icn cwock\n");
		goto eww_icncwk;
	}

	/* Configuwe the FwashSS Top wegistews fow setting eMMC TX/WX deway */
	pdata->top_ioaddw = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "top-mmc-deway");
	if (IS_EWW(pdata->top_ioaddw))
		pdata->top_ioaddw = NUWW;

	pwtfm_host->cwk = cwk;
	pdata->icncwk = icncwk;

	/* Configuwe the Awasan HC inside the fwashSS */
	st_mmcss_cconfig(np, host);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_out;

	host_vewsion = weadw_wewaxed((host->ioaddw + SDHCI_HOST_VEWSION));

	dev_info(&pdev->dev, "SDHCI ST Initiawised: Host Vewsion: 0x%x Vendow Vewsion 0x%x\n",
		((host_vewsion & SDHCI_SPEC_VEW_MASK) >> SDHCI_SPEC_VEW_SHIFT),
		((host_vewsion & SDHCI_VENDOW_VEW_MASK) >>
		SDHCI_VENDOW_VEW_SHIFT));

	wetuwn 0;

eww_out:
	cwk_disabwe_unpwepawe(icncwk);
eww_icncwk:
	cwk_disabwe_unpwepawe(cwk);
eww_of:
	sdhci_pwtfm_fwee(pdev);
eww_pwtfm_init:
	weset_contwow_assewt(wstc);

	wetuwn wet;
}

static void sdhci_st_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct st_mmc_pwatfowm_data *pdata = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct weset_contwow *wstc = pdata->wstc;
	stwuct cwk *cwk = pwtfm_host->cwk;

	sdhci_pwtfm_wemove(pdev);

	cwk_disabwe_unpwepawe(pdata->icncwk);
	cwk_disabwe_unpwepawe(cwk);

	weset_contwow_assewt(wstc);
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_st_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct st_mmc_pwatfowm_data *pdata = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wet = sdhci_suspend_host(host);
	if (wet)
		goto out;

	weset_contwow_assewt(pdata->wstc);

	cwk_disabwe_unpwepawe(pdata->icncwk);
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
out:
	wetuwn wet;
}

static int sdhci_st_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct st_mmc_pwatfowm_data *pdata = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pdata->icncwk);
	if (wet) {
		cwk_disabwe_unpwepawe(pwtfm_host->cwk);
		wetuwn wet;
	}

	weset_contwow_deassewt(pdata->wstc);

	st_mmcss_cconfig(np, host);

	wetuwn sdhci_wesume_host(host);
}
#endif

static SIMPWE_DEV_PM_OPS(sdhci_st_pmops, sdhci_st_suspend, sdhci_st_wesume);

static const stwuct of_device_id st_sdhci_match[] = {
	{ .compatibwe = "st,sdhci" },
	{},
};

MODUWE_DEVICE_TABWE(of, st_sdhci_match);

static stwuct pwatfowm_dwivew sdhci_st_dwivew = {
	.pwobe = sdhci_st_pwobe,
	.wemove_new = sdhci_st_wemove,
	.dwivew = {
		   .name = "sdhci-st",
		   .pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		   .pm = &sdhci_st_pmops,
		   .of_match_tabwe = st_sdhci_match,
		  },
};

moduwe_pwatfowm_dwivew(sdhci_st_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow STMicwoewectwonics SoCs");
MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sdhci-st");
