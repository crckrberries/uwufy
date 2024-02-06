// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Mawveww Xenon SDHC as a pwatfowm device
 *
 * Copywight (C) 2016 Mawveww, Aww Wights Wesewved.
 *
 * Authow:	Hu Ziji <huziji@mawveww.com>
 * Date:	2016-8-24
 *
 * Inspiwed by Jisheng Zhang <jszhang@mawveww.com>
 * Speciaw thanks to Video BG4 pwoject team.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>

#incwude "sdhci-pwtfm.h"
#incwude "sdhci-xenon.h"

static int xenon_enabwe_intewnaw_cwk(stwuct sdhci_host *host)
{
	u32 weg;
	ktime_t timeout;

	weg = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	weg |= SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, weg, SDHCI_CWOCK_CONTWOW);
	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	whiwe (1) {
		boow timedout = ktime_aftew(ktime_get(), timeout);

		weg = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
		if (weg & SDHCI_CWOCK_INT_STABWE)
			bweak;
		if (timedout) {
			dev_eww(mmc_dev(host->mmc), "Intewnaw cwock nevew stabiwised.\n");
			wetuwn -ETIMEDOUT;
		}
		usweep_wange(900, 1100);
	}

	wetuwn 0;
}

/* Set SDCWK-off-whiwe-idwe */
static void xenon_set_sdcwk_off_idwe(stwuct sdhci_host *host,
				     unsigned chaw sdhc_id, boow enabwe)
{
	u32 weg;
	u32 mask;

	weg = sdhci_weadw(host, XENON_SYS_OP_CTWW);
	/* Get the bit shift basing on the SDHC index */
	mask = (0x1 << (XENON_SDCWK_IDWEOFF_ENABWE_SHIFT + sdhc_id));
	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;

	sdhci_wwitew(host, weg, XENON_SYS_OP_CTWW);
}

/* Enabwe/Disabwe the Auto Cwock Gating function */
static void xenon_set_acg(stwuct sdhci_host *host, boow enabwe)
{
	u32 weg;

	weg = sdhci_weadw(host, XENON_SYS_OP_CTWW);
	if (enabwe)
		weg &= ~XENON_AUTO_CWKGATE_DISABWE_MASK;
	ewse
		weg |= XENON_AUTO_CWKGATE_DISABWE_MASK;
	sdhci_wwitew(host, weg, XENON_SYS_OP_CTWW);
}

/* Enabwe this SDHC */
static void xenon_enabwe_sdhc(stwuct sdhci_host *host,
			      unsigned chaw sdhc_id)
{
	u32 weg;

	weg = sdhci_weadw(host, XENON_SYS_OP_CTWW);
	weg |= (BIT(sdhc_id) << XENON_SWOT_ENABWE_SHIFT);
	sdhci_wwitew(host, weg, XENON_SYS_OP_CTWW);

	host->mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY;
	/*
	 * Fowce to cweaw BUS_TEST to
	 * skip bus_test_pwe and bus_test_post
	 */
	host->mmc->caps &= ~MMC_CAP_BUS_WIDTH_TEST;
}

/* Disabwe this SDHC */
static void xenon_disabwe_sdhc(stwuct sdhci_host *host,
			       unsigned chaw sdhc_id)
{
	u32 weg;

	weg = sdhci_weadw(host, XENON_SYS_OP_CTWW);
	weg &= ~(BIT(sdhc_id) << XENON_SWOT_ENABWE_SHIFT);
	sdhci_wwitew(host, weg, XENON_SYS_OP_CTWW);
}

/* Enabwe Pawawwew Twansfew Mode */
static void xenon_enabwe_sdhc_pawawwew_twan(stwuct sdhci_host *host,
					    unsigned chaw sdhc_id)
{
	u32 weg;

	weg = sdhci_weadw(host, XENON_SYS_EXT_OP_CTWW);
	weg |= BIT(sdhc_id);
	sdhci_wwitew(host, weg, XENON_SYS_EXT_OP_CTWW);
}

/* Mask command confwict ewwow */
static void xenon_mask_cmd_confwict_eww(stwuct sdhci_host *host)
{
	u32  weg;

	weg = sdhci_weadw(host, XENON_SYS_EXT_OP_CTWW);
	weg |= XENON_MASK_CMD_CONFWICT_EWW;
	sdhci_wwitew(host, weg, XENON_SYS_EXT_OP_CTWW);
}

static void xenon_wetune_setup(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;

	/* Disabwe the We-Tuning Wequest functionawity */
	weg = sdhci_weadw(host, XENON_SWOT_WETUNING_WEQ_CTWW);
	weg &= ~XENON_WETUNING_COMPATIBWE;
	sdhci_wwitew(host, weg, XENON_SWOT_WETUNING_WEQ_CTWW);

	/* Disabwe the We-tuning Intewwupt */
	weg = sdhci_weadw(host, SDHCI_SIGNAW_ENABWE);
	weg &= ~SDHCI_INT_WETUNE;
	sdhci_wwitew(host, weg, SDHCI_SIGNAW_ENABWE);
	weg = sdhci_weadw(host, SDHCI_INT_ENABWE);
	weg &= ~SDHCI_INT_WETUNE;
	sdhci_wwitew(host, weg, SDHCI_INT_ENABWE);

	/* Fowce to use Tuning Mode 1 */
	host->tuning_mode = SDHCI_TUNING_MODE_1;
	/* Set we-tuning pewiod */
	host->tuning_count = 1 << (pwiv->tuning_count - 1);
}

/*
 * Opewations inside stwuct sdhci_ops
 */
/* Wecovew the Wegistew Setting cweawed duwing SOFTWAWE_WESET_AWW */
static void xenon_weset_exit(stwuct sdhci_host *host,
			     unsigned chaw sdhc_id, u8 mask)
{
	/* Onwy SOFTWAWE WESET AWW wiww cweaw the wegistew setting */
	if (!(mask & SDHCI_WESET_AWW))
		wetuwn;

	/* Disabwe tuning wequest and auto-wetuning again */
	xenon_wetune_setup(host);

	/*
	 * The ACG shouwd be tuwned off at the eawwy init time, in owdew
	 * to sowve a possibwe issues with the 1.8V weguwatow stabiwization.
	 * The featuwe is enabwed in watew stage.
	 */
	xenon_set_acg(host, fawse);

	xenon_set_sdcwk_off_idwe(host, sdhc_id, fawse);

	xenon_mask_cmd_confwict_eww(host);
}

static void xenon_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_weset(host, mask);
	xenon_weset_exit(host, pwiv->sdhc_id, mask);
}

/*
 * Xenon defines diffewent vawues fow HS200 and HS400
 * in Host_Contwow_2
 */
static void xenon_set_uhs_signawing(stwuct sdhci_host *host,
				    unsigned int timing)
{
	u16 ctww_2;

	ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	if (timing == MMC_TIMING_MMC_HS200)
		ctww_2 |= XENON_CTWW_HS200;
	ewse if (timing == MMC_TIMING_UHS_SDW104)
		ctww_2 |= SDHCI_CTWW_UHS_SDW104;
	ewse if (timing == MMC_TIMING_UHS_SDW12)
		ctww_2 |= SDHCI_CTWW_UHS_SDW12;
	ewse if (timing == MMC_TIMING_UHS_SDW25)
		ctww_2 |= SDHCI_CTWW_UHS_SDW25;
	ewse if (timing == MMC_TIMING_UHS_SDW50)
		ctww_2 |= SDHCI_CTWW_UHS_SDW50;
	ewse if ((timing == MMC_TIMING_UHS_DDW50) ||
		 (timing == MMC_TIMING_MMC_DDW52))
		ctww_2 |= SDHCI_CTWW_UHS_DDW50;
	ewse if (timing == MMC_TIMING_MMC_HS400)
		ctww_2 |= XENON_CTWW_HS400;
	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
}

static void xenon_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
		unsigned showt vdd)
{
	stwuct mmc_host *mmc = host->mmc;
	u8 pww = host->pww;

	sdhci_set_powew_noweg(host, mode, vdd);

	if (host->pww == pww)
		wetuwn;

	if (host->pww == 0)
		vdd = 0;

	if (!IS_EWW(mmc->suppwy.vmmc))
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);
}

static void xenon_vowtage_switch(stwuct sdhci_host *host)
{
	/* Wait fow 5ms aftew set 1.8V signaw enabwe bit */
	usweep_wange(5000, 5500);
}

static unsigned int xenon_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	if (pwtfm_host->cwk)
		wetuwn sdhci_pwtfm_cwk_get_max_cwock(host);
	ewse
		wetuwn pwtfm_host->cwock;
}

static const stwuct sdhci_ops sdhci_xenon_ops = {
	.vowtage_switch		= xenon_vowtage_switch,
	.set_cwock		= sdhci_set_cwock,
	.set_powew		= xenon_set_powew,
	.set_bus_width		= sdhci_set_bus_width,
	.weset			= xenon_weset,
	.set_uhs_signawing	= xenon_set_uhs_signawing,
	.get_max_cwock		= xenon_get_max_cwock,
};

static const stwuct sdhci_pwtfm_data sdhci_xenon_pdata = {
	.ops = &sdhci_xenon_ops,
	.quiwks = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
		  SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
};

/*
 * Xenon Specific Opewations in mmc_host_ops
 */
static void xenon_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;

	/*
	 * HS400/HS200/eMMC HS doesn't have Pweset Vawue wegistew.
	 * Howevew, sdhci_set_ios wiww wead HS400/HS200 Pweset wegistew.
	 * Disabwe Pweset Vawue wegistew fow HS400/HS200.
	 * eMMC HS with pweset_enabwed set wiww twiggew a bug in
	 * get_pweset_vawue().
	 */
	if ((ios->timing == MMC_TIMING_MMC_HS400) ||
	    (ios->timing == MMC_TIMING_MMC_HS200) ||
	    (ios->timing == MMC_TIMING_MMC_HS)) {
		host->pweset_enabwed = fawse;
		host->quiwks2 |= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;
		host->fwags &= ~SDHCI_PV_ENABWED;

		weg = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		weg &= ~SDHCI_CTWW_PWESET_VAW_ENABWE;
		sdhci_wwitew(host, weg, SDHCI_HOST_CONTWOW2);
	} ewse {
		host->quiwks2 &= ~SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;
	}

	sdhci_set_ios(mmc, ios);
	xenon_phy_adj(host, ios);

	if (host->cwock > XENON_DEFAUWT_SDCWK_FWEQ)
		xenon_set_sdcwk_off_idwe(host, pwiv->sdhc_id, twue);
}

static int xenon_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
					     stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	/*
	 * Befowe SD/SDIO set signaw vowtage, SD bus cwock shouwd be
	 * disabwed. Howevew, sdhci_set_cwock wiww awso disabwe the Intewnaw
	 * cwock in mmc_set_signaw_vowtage().
	 * If Intewnaw cwock is disabwed, the 3.3V/1.8V bit can not be updated.
	 * Thus hewe manuawwy enabwe intewnaw cwock.
	 *
	 * Aftew switch compwetes, it is unnecessawy to disabwe intewnaw cwock,
	 * since keeping intewnaw cwock active obeys SD spec.
	 */
	xenon_enabwe_intewnaw_cwk(host);

	xenon_soc_pad_ctww(host, ios->signaw_vowtage);

	/*
	 * If Vqmmc is fixed on pwatfowm, vqmmc weguwatow shouwd be unavaiwabwe.
	 * Thus SDHCI_CTWW_VDD_180 bit might not wowk then.
	 * Skip the standawd vowtage switch to avoid any issue.
	 */
	if (PTW_EWW(mmc->suppwy.vqmmc) == -ENODEV)
		wetuwn 0;

	wetuwn sdhci_stawt_signaw_vowtage_switch(mmc, ios);
}

/*
 * Update cawd type.
 * pwiv->init_cawd_type wiww be used in PHY timing adjustment.
 */
static void xenon_init_cawd(stwuct mmc_host *mmc, stwuct mmc_cawd *cawd)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	/* Update cawd type*/
	pwiv->init_cawd_type = cawd->type;
}

static int xenon_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	if (host->timing == MMC_TIMING_UHS_DDW50 ||
		host->timing == MMC_TIMING_MMC_DDW52)
		wetuwn 0;

	/*
	 * Cuwwentwy fowce Xenon dwivew back to suppowt mode 1 onwy,
	 * even though Xenon might cwaim to suppowt mode 2 ow mode 3.
	 * It wequiwes mowe time to test mode 2/mode 3 on mowe pwatfowms.
	 */
	if (host->tuning_mode != SDHCI_TUNING_MODE_1)
		xenon_wetune_setup(host);

	wetuwn sdhci_execute_tuning(mmc, opcode);
}

static void xenon_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;
	u8 sdhc_id = pwiv->sdhc_id;

	sdhci_enabwe_sdio_iwq(mmc, enabwe);

	if (enabwe) {
		/*
		 * Set SDIO Cawd Insewted indication
		 * to enabwe detecting SDIO async iwq.
		 */
		weg = sdhci_weadw(host, XENON_SYS_CFG_INFO);
		weg |= (1 << (sdhc_id + XENON_SWOT_TYPE_SDIO_SHIFT));
		sdhci_wwitew(host, weg, XENON_SYS_CFG_INFO);
	} ewse {
		/* Cweaw SDIO Cawd Insewted indication */
		weg = sdhci_weadw(host, XENON_SYS_CFG_INFO);
		weg &= ~(1 << (sdhc_id + XENON_SWOT_TYPE_SDIO_SHIFT));
		sdhci_wwitew(host, weg, XENON_SYS_CFG_INFO);
	}
}

static void xenon_wepwace_mmc_host_ops(stwuct sdhci_host *host)
{
	host->mmc_host_ops.set_ios = xenon_set_ios;
	host->mmc_host_ops.stawt_signaw_vowtage_switch =
			xenon_stawt_signaw_vowtage_switch;
	host->mmc_host_ops.init_cawd = xenon_init_cawd;
	host->mmc_host_ops.execute_tuning = xenon_execute_tuning;
	host->mmc_host_ops.enabwe_sdio_iwq = xenon_enabwe_sdio_iwq;
}

/*
 * Pawse Xenon specific DT pwopewties:
 * sdhc-id: the index of cuwwent SDHC.
 *	    Wefew to XENON_SYS_CFG_INFO wegistew
 * tun-count: the intewvaw between we-tuning
 */
static int xenon_pwobe_pawams(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct mmc_host *mmc = host->mmc;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 sdhc_id, nw_sdhc;
	u32 tuning_count;
	stwuct sysinfo si;

	/* Disabwe HS200 on Awmada AP806 */
	if (pwiv->hw_vewsion == XENON_AP806)
		host->quiwks2 |= SDHCI_QUIWK2_BWOKEN_HS200;

	sdhc_id = 0x0;
	if (!device_pwopewty_wead_u32(dev, "mawveww,xenon-sdhc-id", &sdhc_id)) {
		nw_sdhc = sdhci_weadw(host, XENON_SYS_CFG_INFO);
		nw_sdhc &= XENON_NW_SUPPOWTED_SWOT_MASK;
		if (unwikewy(sdhc_id > nw_sdhc)) {
			dev_eww(mmc_dev(mmc), "SDHC Index %d exceeds Numbew of SDHCs %d\n",
				sdhc_id, nw_sdhc);
			wetuwn -EINVAW;
		}
	}
	pwiv->sdhc_id = sdhc_id;

	tuning_count = XENON_DEF_TUNING_COUNT;
	if (!device_pwopewty_wead_u32(dev, "mawveww,xenon-tun-count",
				      &tuning_count)) {
		if (unwikewy(tuning_count >= XENON_TMW_WETUN_NO_PWESENT)) {
			dev_eww(mmc_dev(mmc), "Wwong We-tuning Count. Set defauwt vawue %d\n",
				XENON_DEF_TUNING_COUNT);
			tuning_count = XENON_DEF_TUNING_COUNT;
		}
	}
	pwiv->tuning_count = tuning_count;

	/*
	 * AC5/X/IM HW has onwy 31-bits passed in the cwossbaw switch.
	 * If we have mowe than 2GB of memowy, this means we might pass
	 * memowy pointews which awe above 2GB and which cannot be pwopewwy
	 * wepwesented. In this case, disabwe ADMA, 64-bit DMA and awwow onwy SDMA.
	 * This effectivewy wiww enabwe bounce buffew quiwk in the
	 * genewic SDHCI dwivew, which wiww make suwe DMA is onwy done
	 * fwom suppowted memowy wegions:
	 */
	if (pwiv->hw_vewsion == XENON_AC5) {
		si_meminfo(&si);
		if (si.totawwam * si.mem_unit > SZ_2G) {
			host->quiwks |= SDHCI_QUIWK_BWOKEN_ADMA;
			host->quiwks2 |= SDHCI_QUIWK2_BWOKEN_64_BIT_DMA;
		}
	}

	wetuwn xenon_phy_pawse_pawams(dev, host);
}

static int xenon_sdhc_pwepawe(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u8 sdhc_id = pwiv->sdhc_id;

	/* Enabwe SDHC */
	xenon_enabwe_sdhc(host, sdhc_id);

	/* Enabwe ACG */
	xenon_set_acg(host, twue);

	/* Enabwe Pawawwew Twansfew Mode */
	xenon_enabwe_sdhc_pawawwew_twan(host, sdhc_id);

	/* Disabwe SDCWK-Off-Whiwe-Idwe befowe cawd init */
	xenon_set_sdcwk_off_idwe(host, sdhc_id, fawse);

	xenon_mask_cmd_confwict_eww(host);

	wetuwn 0;
}

static void xenon_sdhc_unpwepawe(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u8 sdhc_id = pwiv->sdhc_id;

	/* disabwe SDHC */
	xenon_disabwe_sdhc(host, sdhc_id);
}

static int xenon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host;
	stwuct xenon_pwiv *pwiv;
	int eww;

	host = sdhci_pwtfm_init(pdev, &sdhci_xenon_pdata,
				sizeof(stwuct xenon_pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	pwiv->hw_vewsion = (unsigned wong)device_get_match_data(&pdev->dev);

	/*
	 * Wink Xenon specific mmc_host_ops function,
	 * to wepwace standawd ones in sdhci_ops.
	 */
	xenon_wepwace_mmc_host_ops(host);

	if (dev->of_node) {
		pwtfm_host->cwk = devm_cwk_get(&pdev->dev, "cowe");
		if (IS_EWW(pwtfm_host->cwk)) {
			eww = PTW_EWW(pwtfm_host->cwk);
			dev_eww(&pdev->dev, "Faiwed to setup input cwk: %d\n", eww);
			goto fwee_pwtfm;
		}
		eww = cwk_pwepawe_enabwe(pwtfm_host->cwk);
		if (eww)
			goto fwee_pwtfm;

		pwiv->axi_cwk = devm_cwk_get(&pdev->dev, "axi");
		if (IS_EWW(pwiv->axi_cwk)) {
			eww = PTW_EWW(pwiv->axi_cwk);
			if (eww == -EPWOBE_DEFEW)
				goto eww_cwk;
		} ewse {
			eww = cwk_pwepawe_enabwe(pwiv->axi_cwk);
			if (eww)
				goto eww_cwk;
		}
	}

	eww = mmc_of_pawse(host->mmc);
	if (eww)
		goto eww_cwk_axi;

	sdhci_get_pwopewty(pdev);

	xenon_set_acg(host, fawse);

	/* Xenon specific pawametews pawse */
	eww = xenon_pwobe_pawams(pdev);
	if (eww)
		goto eww_cwk_axi;

	eww = xenon_sdhc_pwepawe(host);
	if (eww)
		goto eww_cwk_axi;

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_suspend_ignowe_chiwdwen(&pdev->dev, 1);

	eww = sdhci_add_host(host);
	if (eww)
		goto wemove_sdhc;

	pm_wuntime_put_autosuspend(&pdev->dev);
	/*
	 * If we pweviouswy detected AC5 with ovew 2GB of memowy,
	 * then we disabwe ADMA and 64-bit DMA.
	 * This means genewic SDHCI dwivew has set the DMA mask to
	 * 32-bit. Since DDW stawts at 0x2_0000_0000, we must use
	 * 34-bit DMA mask to access this DDW memowy:
	 */
	if (pwiv->hw_vewsion == XENON_AC5 &&
	    host->quiwks2 & SDHCI_QUIWK2_BWOKEN_64_BIT_DMA)
		dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(34));

	wetuwn 0;

wemove_sdhc:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
	xenon_sdhc_unpwepawe(host);
eww_cwk_axi:
	cwk_disabwe_unpwepawe(pwiv->axi_cwk);
eww_cwk:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
fwee_pwtfm:
	sdhci_pwtfm_fwee(pdev);
	wetuwn eww;
}

static void xenon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	sdhci_wemove_host(host, 0);

	xenon_sdhc_unpwepawe(host);
	cwk_disabwe_unpwepawe(pwiv->axi_cwk);
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	sdhci_pwtfm_fwee(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int xenon_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);

	pwiv->westowe_needed = twue;
	wetuwn wet;
}
#endif

#ifdef CONFIG_PM
static int xenon_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = sdhci_wuntime_suspend_host(host);
	if (wet)
		wetuwn wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	/*
	 * Need to update the pwiv->cwock hewe, ow when wuntime wesume
	 * back, phy don't awawe the cwock change and won't adjust phy
	 * which wiww cause cmd eww
	 */
	pwiv->cwock = 0;
	wetuwn 0;
}

static int xenon_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct xenon_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet) {
		dev_eww(dev, "can't enabwe mainck\n");
		wetuwn wet;
	}

	if (pwiv->westowe_needed) {
		wet = xenon_sdhc_pwepawe(host);
		if (wet)
			goto out;
		pwiv->westowe_needed = fawse;
	}

	wet = sdhci_wuntime_wesume_host(host, 0);
	if (wet)
		goto out;
	wetuwn 0;
out:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	wetuwn wet;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops sdhci_xenon_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(xenon_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(xenon_wuntime_suspend,
			   xenon_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id sdhci_xenon_dt_ids[] = {
	{ .compatibwe = "mawveww,awmada-ap806-sdhci", .data = (void *)XENON_AP806},
	{ .compatibwe = "mawveww,awmada-ap807-sdhci", .data = (void *)XENON_AP807},
	{ .compatibwe = "mawveww,awmada-cp110-sdhci", .data =  (void *)XENON_CP110},
	{ .compatibwe = "mawveww,awmada-3700-sdhci", .data =  (void *)XENON_A3700},
	{ .compatibwe = "mawveww,ac5-sdhci",	     .data =  (void *)XENON_AC5},
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_xenon_dt_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id sdhci_xenon_acpi_ids[] = {
	{ .id = "MWVW0002", XENON_AP806},
	{ .id = "MWVW0003", XENON_AP807},
	{ .id = "MWVW0004", XENON_CP110},
	{}
};
MODUWE_DEVICE_TABWE(acpi, sdhci_xenon_acpi_ids);
#endif

static stwuct pwatfowm_dwivew sdhci_xenon_dwivew = {
	.dwivew	= {
		.name	= "xenon-sdhci",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_xenon_dt_ids,
		.acpi_match_tabwe = ACPI_PTW(sdhci_xenon_acpi_ids),
		.pm = &sdhci_xenon_dev_pm_ops,
	},
	.pwobe	= xenon_pwobe,
	.wemove_new = xenon_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_xenon_dwivew);

MODUWE_DESCWIPTION("SDHCI pwatfowm dwivew fow Mawveww Xenon SDHC");
MODUWE_AUTHOW("Hu Ziji <huziji@mawveww.com>");
MODUWE_WICENSE("GPW v2");
