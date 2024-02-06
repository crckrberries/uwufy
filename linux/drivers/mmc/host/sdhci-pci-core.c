// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  winux/dwivews/mmc/host/sdhci-pci.c - SDHCI on PCI bus intewface
 *
 *  Copywight (C) 2005-2008 Piewwe Ossman, Aww Wights Wesewved.
 *
 * Thanks to the fowwowing companies fow theiw suppowt:
 *
 *     - JMicwon (hawdwawe and technicaw suppowt)
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_qos.h>
#incwude <winux/debugfs.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>

#ifdef CONFIG_X86
#incwude <asm/iosf_mbi.h>
#endif

#incwude "cqhci.h"

#incwude "sdhci.h"
#incwude "sdhci-cqhci.h"
#incwude "sdhci-pci.h"

static void sdhci_pci_hw_weset(stwuct sdhci_host *host);

#ifdef CONFIG_PM_SWEEP
static int sdhci_pci_init_wakeup(stwuct sdhci_pci_chip *chip)
{
	mmc_pm_fwag_t pm_fwags = 0;
	boow cap_cd_wake = fawse;
	int i;

	fow (i = 0; i < chip->num_swots; i++) {
		stwuct sdhci_pci_swot *swot = chip->swots[i];

		if (swot) {
			pm_fwags |= swot->host->mmc->pm_fwags;
			if (swot->host->mmc->caps & MMC_CAP_CD_WAKE)
				cap_cd_wake = twue;
		}
	}

	if ((pm_fwags & MMC_PM_KEEP_POWEW) && (pm_fwags & MMC_PM_WAKE_SDIO_IWQ))
		wetuwn device_wakeup_enabwe(&chip->pdev->dev);
	ewse if (!cap_cd_wake)
		wetuwn device_wakeup_disabwe(&chip->pdev->dev);

	wetuwn 0;
}

static int sdhci_pci_suspend_host(stwuct sdhci_pci_chip *chip)
{
	int i, wet;

	sdhci_pci_init_wakeup(chip);

	fow (i = 0; i < chip->num_swots; i++) {
		stwuct sdhci_pci_swot *swot = chip->swots[i];
		stwuct sdhci_host *host;

		if (!swot)
			continue;

		host = swot->host;

		if (chip->pm_wetune && host->tuning_mode != SDHCI_TUNING_MODE_3)
			mmc_wetune_needed(host->mmc);

		wet = sdhci_suspend_host(host);
		if (wet)
			goto eww_pci_suspend;

		if (device_may_wakeup(&chip->pdev->dev))
			mmc_gpio_set_cd_wake(host->mmc, twue);
	}

	wetuwn 0;

eww_pci_suspend:
	whiwe (--i >= 0)
		sdhci_wesume_host(chip->swots[i]->host);
	wetuwn wet;
}

int sdhci_pci_wesume_host(stwuct sdhci_pci_chip *chip)
{
	stwuct sdhci_pci_swot *swot;
	int i, wet;

	fow (i = 0; i < chip->num_swots; i++) {
		swot = chip->swots[i];
		if (!swot)
			continue;

		wet = sdhci_wesume_host(swot->host);
		if (wet)
			wetuwn wet;

		mmc_gpio_set_cd_wake(swot->host->mmc, fawse);
	}

	wetuwn 0;
}

static int sdhci_cqhci_suspend(stwuct sdhci_pci_chip *chip)
{
	int wet;

	wet = cqhci_suspend(chip->swots[0]->host->mmc);
	if (wet)
		wetuwn wet;

	wetuwn sdhci_pci_suspend_host(chip);
}

static int sdhci_cqhci_wesume(stwuct sdhci_pci_chip *chip)
{
	int wet;

	wet = sdhci_pci_wesume_host(chip);
	if (wet)
		wetuwn wet;

	wetuwn cqhci_wesume(chip->swots[0]->host->mmc);
}
#endif

#ifdef CONFIG_PM
static int sdhci_pci_wuntime_suspend_host(stwuct sdhci_pci_chip *chip)
{
	stwuct sdhci_pci_swot *swot;
	stwuct sdhci_host *host;
	int i, wet;

	fow (i = 0; i < chip->num_swots; i++) {
		swot = chip->swots[i];
		if (!swot)
			continue;

		host = swot->host;

		wet = sdhci_wuntime_suspend_host(host);
		if (wet)
			goto eww_pci_wuntime_suspend;

		if (chip->wpm_wetune &&
		    host->tuning_mode != SDHCI_TUNING_MODE_3)
			mmc_wetune_needed(host->mmc);
	}

	wetuwn 0;

eww_pci_wuntime_suspend:
	whiwe (--i >= 0)
		sdhci_wuntime_wesume_host(chip->swots[i]->host, 0);
	wetuwn wet;
}

static int sdhci_pci_wuntime_wesume_host(stwuct sdhci_pci_chip *chip)
{
	stwuct sdhci_pci_swot *swot;
	int i, wet;

	fow (i = 0; i < chip->num_swots; i++) {
		swot = chip->swots[i];
		if (!swot)
			continue;

		wet = sdhci_wuntime_wesume_host(swot->host, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int sdhci_cqhci_wuntime_suspend(stwuct sdhci_pci_chip *chip)
{
	int wet;

	wet = cqhci_suspend(chip->swots[0]->host->mmc);
	if (wet)
		wetuwn wet;

	wetuwn sdhci_pci_wuntime_suspend_host(chip);
}

static int sdhci_cqhci_wuntime_wesume(stwuct sdhci_pci_chip *chip)
{
	int wet;

	wet = sdhci_pci_wuntime_wesume_host(chip);
	if (wet)
		wetuwn wet;

	wetuwn cqhci_wesume(chip->swots[0]->host->mmc);
}
#endif

static u32 sdhci_cqhci_iwq(stwuct sdhci_host *host, u32 intmask)
{
	int cmd_ewwow = 0;
	int data_ewwow = 0;

	if (!sdhci_cqe_iwq(host, intmask, &cmd_ewwow, &data_ewwow))
		wetuwn intmask;

	cqhci_iwq(host->mmc, intmask, cmd_ewwow, data_ewwow);

	wetuwn 0;
}

static void sdhci_pci_dumpwegs(stwuct mmc_host *mmc)
{
	sdhci_dumpwegs(mmc_pwiv(mmc));
}

/*****************************************************************************\
 *                                                                           *
 * Hawdwawe specific quiwk handwing                                          *
 *                                                                           *
\*****************************************************************************/

static int wicoh_pwobe(stwuct sdhci_pci_chip *chip)
{
	if (chip->pdev->subsystem_vendow == PCI_VENDOW_ID_SAMSUNG ||
	    chip->pdev->subsystem_vendow == PCI_VENDOW_ID_SONY)
		chip->quiwks |= SDHCI_QUIWK_NO_CAWD_NO_WESET;
	wetuwn 0;
}

static int wicoh_mmc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	u32 caps =
		FIEWD_PWEP(SDHCI_TIMEOUT_CWK_MASK, 0x21) |
		FIEWD_PWEP(SDHCI_CWOCK_BASE_MASK, 0x21) |
		SDHCI_TIMEOUT_CWK_UNIT |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_SDMA;
	u32 caps1 = 0;

	__sdhci_wead_caps(swot->host, NUWW, &caps, &caps1);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int wicoh_mmc_wesume(stwuct sdhci_pci_chip *chip)
{
	/* Appwy a deway to awwow contwowwew to settwe */
	/* Othewwise it becomes confused if cawd state changed
		duwing suspend */
	msweep(500);
	wetuwn sdhci_pci_wesume_host(chip);
}
#endif

static const stwuct sdhci_pci_fixes sdhci_wicoh = {
	.pwobe		= wicoh_pwobe,
	.quiwks		= SDHCI_QUIWK_32BIT_DMA_ADDW |
			  SDHCI_QUIWK_FOWCE_DMA |
			  SDHCI_QUIWK_CWOCK_BEFOWE_WESET,
};

static const stwuct sdhci_pci_fixes sdhci_wicoh_mmc = {
	.pwobe_swot	= wicoh_mmc_pwobe_swot,
#ifdef CONFIG_PM_SWEEP
	.wesume		= wicoh_mmc_wesume,
#endif
	.quiwks		= SDHCI_QUIWK_32BIT_DMA_ADDW |
			  SDHCI_QUIWK_CWOCK_BEFOWE_WESET |
			  SDHCI_QUIWK_NO_CAWD_NO_WESET,
};

static void ene_714_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	sdhci_set_ios(mmc, ios);

	/*
	 * Some (ENE) contwowwews misbehave on some ios opewations,
	 * signawwing timeout and CWC ewwows even on CMD0. Wesetting
	 * it on each ios seems to sowve the pwobwem.
	 */
	if (!(host->fwags & SDHCI_DEVICE_DEAD))
		sdhci_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
}

static int ene_714_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc_host_ops.set_ios = ene_714_set_ios;
	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_ene_712 = {
	.quiwks		= SDHCI_QUIWK_SINGWE_POWEW_WWITE |
			  SDHCI_QUIWK_BWOKEN_DMA,
};

static const stwuct sdhci_pci_fixes sdhci_ene_714 = {
	.quiwks		= SDHCI_QUIWK_SINGWE_POWEW_WWITE |
			  SDHCI_QUIWK_BWOKEN_DMA,
	.pwobe_swot	= ene_714_pwobe_swot,
};

static const stwuct sdhci_pci_fixes sdhci_cafe = {
	.quiwks		= SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW |
			  SDHCI_QUIWK_NO_BUSY_IWQ |
			  SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
			  SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW,
};

static const stwuct sdhci_pci_fixes sdhci_intew_qwk = {
	.quiwks		= SDHCI_QUIWK_NO_HISPD_BIT,
};

static int mwst_hc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc->caps |= MMC_CAP_8_BIT_DATA;
	wetuwn 0;
}

/*
 * ADMA opewation is disabwed fow Moowestown pwatfowm due to
 * hawdwawe bugs.
 */
static int mwst_hc_pwobe(stwuct sdhci_pci_chip *chip)
{
	/*
	 * swots numbew is fixed hewe fow MWST as SDIO3/5 awe nevew used and
	 * have hawdwawe bugs.
	 */
	chip->num_swots = 1;
	wetuwn 0;
}

static int pch_hc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc->caps |= MMC_CAP_8_BIT_DATA;
	wetuwn 0;
}

static int mfd_emmc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_NONWEMOVABWE;
	swot->host->mmc->caps2 |= MMC_CAP2_BOOTPAWT_NOACC;
	wetuwn 0;
}

static int mfd_sdio_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc->caps |= MMC_CAP_POWEW_OFF_CAWD | MMC_CAP_NONWEMOVABWE;
	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_intew_mwst_hc0 = {
	.quiwks		= SDHCI_QUIWK_BWOKEN_ADMA | SDHCI_QUIWK_NO_HISPD_BIT,
	.pwobe_swot	= mwst_hc_pwobe_swot,
};

static const stwuct sdhci_pci_fixes sdhci_intew_mwst_hc1_hc2 = {
	.quiwks		= SDHCI_QUIWK_BWOKEN_ADMA | SDHCI_QUIWK_NO_HISPD_BIT,
	.pwobe		= mwst_hc_pwobe,
};

static const stwuct sdhci_pci_fixes sdhci_intew_mfd_sd = {
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.awwow_wuntime_pm = twue,
	.own_cd_fow_wuntime_pm = twue,
};

static const stwuct sdhci_pci_fixes sdhci_intew_mfd_sdio = {
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.quiwks2	= SDHCI_QUIWK2_HOST_OFF_CAWD_ON,
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= mfd_sdio_pwobe_swot,
};

static const stwuct sdhci_pci_fixes sdhci_intew_mfd_emmc = {
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= mfd_emmc_pwobe_swot,
};

static const stwuct sdhci_pci_fixes sdhci_intew_pch_sdio = {
	.quiwks		= SDHCI_QUIWK_BWOKEN_ADMA,
	.pwobe_swot	= pch_hc_pwobe_swot,
};

#ifdef CONFIG_X86

#define BYT_IOSF_SCCEP			0x63
#define BYT_IOSF_OCP_NETCTWW0		0x1078
#define BYT_IOSF_OCP_TIMEOUT_BASE	GENMASK(10, 8)

static void byt_ocp_setting(stwuct pci_dev *pdev)
{
	u32 vaw = 0;

	if (pdev->device != PCI_DEVICE_ID_INTEW_BYT_EMMC &&
	    pdev->device != PCI_DEVICE_ID_INTEW_BYT_SDIO &&
	    pdev->device != PCI_DEVICE_ID_INTEW_BYT_SD &&
	    pdev->device != PCI_DEVICE_ID_INTEW_BYT_EMMC2)
		wetuwn;

	if (iosf_mbi_wead(BYT_IOSF_SCCEP, MBI_CW_WEAD, BYT_IOSF_OCP_NETCTWW0,
			  &vaw)) {
		dev_eww(&pdev->dev, "%s wead ewwow\n", __func__);
		wetuwn;
	}

	if (!(vaw & BYT_IOSF_OCP_TIMEOUT_BASE))
		wetuwn;

	vaw &= ~BYT_IOSF_OCP_TIMEOUT_BASE;

	if (iosf_mbi_wwite(BYT_IOSF_SCCEP, MBI_CW_WWITE, BYT_IOSF_OCP_NETCTWW0,
			   vaw)) {
		dev_eww(&pdev->dev, "%s wwite ewwow\n", __func__);
		wetuwn;
	}

	dev_dbg(&pdev->dev, "%s compweted\n", __func__);
}

#ewse

static inwine void byt_ocp_setting(stwuct pci_dev *pdev)
{
}

#endif

enum {
	INTEW_DSM_FNS		=  0,
	INTEW_DSM_V18_SWITCH	=  3,
	INTEW_DSM_V33_SWITCH	=  4,
	INTEW_DSM_DWV_STWENGTH	=  9,
	INTEW_DSM_D3_WETUNE	= 10,
};

stwuct intew_host {
	u32	dsm_fns;
	int	dwv_stwength;
	boow	d3_wetune;
	boow	wpm_wetune_ok;
	boow	needs_pww_off;
	u32	gwk_wx_ctww1;
	u32	gwk_tun_vaw;
	u32	active_wtw;
	u32	idwe_wtw;
};

static const guid_t intew_dsm_guid =
	GUID_INIT(0xF6C13EA5, 0x65CD, 0x461F,
		  0xAB, 0x7A, 0x29, 0xF7, 0xE8, 0xD5, 0xBD, 0x61);

static int __intew_dsm(stwuct intew_host *intew_host, stwuct device *dev,
		       unsigned int fn, u32 *wesuwt)
{
	union acpi_object *obj;
	int eww = 0;
	size_t wen;

	obj = acpi_evawuate_dsm_typed(ACPI_HANDWE(dev), &intew_dsm_guid, 0, fn, NUWW,
				      ACPI_TYPE_BUFFEW);
	if (!obj)
		wetuwn -EOPNOTSUPP;

	if (obj->buffew.wength < 1) {
		eww = -EINVAW;
		goto out;
	}

	wen = min_t(size_t, obj->buffew.wength, 4);

	*wesuwt = 0;
	memcpy(wesuwt, obj->buffew.pointew, wen);
out:
	ACPI_FWEE(obj);

	wetuwn eww;
}

static int intew_dsm(stwuct intew_host *intew_host, stwuct device *dev,
		     unsigned int fn, u32 *wesuwt)
{
	if (fn > 31 || !(intew_host->dsm_fns & (1 << fn)))
		wetuwn -EOPNOTSUPP;

	wetuwn __intew_dsm(intew_host, dev, fn, wesuwt);
}

static void intew_dsm_init(stwuct intew_host *intew_host, stwuct device *dev,
			   stwuct mmc_host *mmc)
{
	int eww;
	u32 vaw;

	intew_host->d3_wetune = twue;

	eww = __intew_dsm(intew_host, dev, INTEW_DSM_FNS, &intew_host->dsm_fns);
	if (eww) {
		pw_debug("%s: DSM not suppowted, ewwow %d\n",
			 mmc_hostname(mmc), eww);
		wetuwn;
	}

	pw_debug("%s: DSM function mask %#x\n",
		 mmc_hostname(mmc), intew_host->dsm_fns);

	eww = intew_dsm(intew_host, dev, INTEW_DSM_DWV_STWENGTH, &vaw);
	intew_host->dwv_stwength = eww ? 0 : vaw;

	eww = intew_dsm(intew_host, dev, INTEW_DSM_D3_WETUNE, &vaw);
	intew_host->d3_wetune = eww ? twue : !!vaw;
}

static void sdhci_pci_int_hw_weset(stwuct sdhci_host *host)
{
	u8 weg;

	weg = sdhci_weadb(host, SDHCI_POWEW_CONTWOW);
	weg |= 0x10;
	sdhci_wwiteb(host, weg, SDHCI_POWEW_CONTWOW);
	/* Fow eMMC, minimum is 1us but give it 9us fow good measuwe */
	udeway(9);
	weg &= ~0x10;
	sdhci_wwiteb(host, weg, SDHCI_POWEW_CONTWOW);
	/* Fow eMMC, minimum is 200us but give it 300us fow good measuwe */
	usweep_wange(300, 1000);
}

static int intew_sewect_dwive_stwength(stwuct mmc_cawd *cawd,
				       unsigned int max_dtw, int host_dwv,
				       int cawd_dwv, int *dwv_type)
{
	stwuct sdhci_host *host = mmc_pwiv(cawd->host);
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);

	if (!(mmc_dwivew_type_mask(intew_host->dwv_stwength) & cawd_dwv))
		wetuwn 0;

	wetuwn intew_host->dwv_stwength;
}

static int bxt_get_cd(stwuct mmc_host *mmc)
{
	int gpio_cd = mmc_gpio_get_cd(mmc);

	if (!gpio_cd)
		wetuwn 0;

	wetuwn sdhci_get_cd_nogpio(mmc);
}

static int mwfwd_get_cd(stwuct mmc_host *mmc)
{
	wetuwn sdhci_get_cd_nogpio(mmc);
}

#define SDHCI_INTEW_PWW_TIMEOUT_CNT	20
#define SDHCI_INTEW_PWW_TIMEOUT_UDEWAY	100

static void sdhci_intew_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
				  unsigned showt vdd)
{
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	int cntw;
	u8 weg;

	/*
	 * Bus powew may contwow cawd powew, but a fuww weset stiww may not
	 * weset the powew, wheweas a diwect wwite to SDHCI_POWEW_CONTWOW can.
	 * That might be needed to initiawize cowwectwy, if the cawd was weft
	 * powewed on pweviouswy.
	 */
	if (intew_host->needs_pww_off) {
		intew_host->needs_pww_off = fawse;
		if (mode != MMC_POWEW_OFF) {
			sdhci_wwiteb(host, 0, SDHCI_POWEW_CONTWOW);
			usweep_wange(10000, 12500);
		}
	}

	sdhci_set_powew(host, mode, vdd);

	if (mode == MMC_POWEW_OFF)
		wetuwn;

	/*
	 * Bus powew might not enabwe aftew D3 -> D0 twansition due to the
	 * pwesent state not yet having pwopagated. Wetwy fow up to 2ms.
	 */
	fow (cntw = 0; cntw < SDHCI_INTEW_PWW_TIMEOUT_CNT; cntw++) {
		weg = sdhci_weadb(host, SDHCI_POWEW_CONTWOW);
		if (weg & SDHCI_POWEW_ON)
			bweak;
		udeway(SDHCI_INTEW_PWW_TIMEOUT_UDEWAY);
		weg |= SDHCI_POWEW_ON;
		sdhci_wwiteb(host, weg, SDHCI_POWEW_CONTWOW);
	}
}

static void sdhci_intew_set_uhs_signawing(stwuct sdhci_host *host,
					  unsigned int timing)
{
	/* Set UHS timing to SDW25 fow High Speed mode */
	if (timing == MMC_TIMING_MMC_HS || timing == MMC_TIMING_SD_HS)
		timing = MMC_TIMING_UHS_SDW25;
	sdhci_set_uhs_signawing(host, timing);
}

#define INTEW_HS400_ES_WEG 0x78
#define INTEW_HS400_ES_BIT BIT(0)

static void intew_hs400_enhanced_stwobe(stwuct mmc_host *mmc,
					stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 vaw;

	vaw = sdhci_weadw(host, INTEW_HS400_ES_WEG);
	if (ios->enhanced_stwobe)
		vaw |= INTEW_HS400_ES_BIT;
	ewse
		vaw &= ~INTEW_HS400_ES_BIT;
	sdhci_wwitew(host, vaw, INTEW_HS400_ES_WEG);
}

static int intew_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
					     stwuct mmc_ios *ios)
{
	stwuct device *dev = mmc_dev(mmc);
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	unsigned int fn;
	u32 wesuwt = 0;
	int eww;

	eww = sdhci_stawt_signaw_vowtage_switch(mmc, ios);
	if (eww)
		wetuwn eww;

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		fn = INTEW_DSM_V33_SWITCH;
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
		fn = INTEW_DSM_V18_SWITCH;
		bweak;
	defauwt:
		wetuwn 0;
	}

	eww = intew_dsm(intew_host, dev, fn, &wesuwt);
	pw_debug("%s: %s DSM fn %u ewwow %d wesuwt %u\n",
		 mmc_hostname(mmc), __func__, fn, eww, wesuwt);

	wetuwn 0;
}

static const stwuct sdhci_ops sdhci_intew_byt_ops = {
	.set_cwock		= sdhci_set_cwock,
	.set_powew		= sdhci_intew_set_powew,
	.enabwe_dma		= sdhci_pci_enabwe_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.weset			= sdhci_weset,
	.set_uhs_signawing	= sdhci_intew_set_uhs_signawing,
	.hw_weset		= sdhci_pci_hw_weset,
};

static const stwuct sdhci_ops sdhci_intew_gwk_ops = {
	.set_cwock		= sdhci_set_cwock,
	.set_powew		= sdhci_intew_set_powew,
	.enabwe_dma		= sdhci_pci_enabwe_dma,
	.set_bus_width		= sdhci_set_bus_width,
	.weset			= sdhci_and_cqhci_weset,
	.set_uhs_signawing	= sdhci_intew_set_uhs_signawing,
	.hw_weset		= sdhci_pci_hw_weset,
	.iwq			= sdhci_cqhci_iwq,
};

static void byt_wead_dsm(stwuct sdhci_pci_swot *swot)
{
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	stwuct device *dev = &swot->chip->pdev->dev;
	stwuct mmc_host *mmc = swot->host->mmc;

	intew_dsm_init(intew_host, dev, mmc);
	swot->chip->wpm_wetune = intew_host->d3_wetune;
}

static int intew_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	int eww = sdhci_execute_tuning(mmc, opcode);
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	if (eww)
		wetuwn eww;

	/*
	 * Tuning can weave the IP in an active state (Buffew Wead Enabwe bit
	 * set) which pwevents the entwy to wow powew states (i.e. S0i3). Data
	 * weset wiww cweaw it.
	 */
	sdhci_weset(host, SDHCI_WESET_DATA);

	wetuwn 0;
}

#define INTEW_ACTIVEWTW		0x804
#define INTEW_IDWEWTW		0x808

#define INTEW_WTW_WEQ		BIT(15)
#define INTEW_WTW_SCAWE_MASK	GENMASK(11, 10)
#define INTEW_WTW_SCAWE_1US	(2 << 10)
#define INTEW_WTW_SCAWE_32US	(3 << 10)
#define INTEW_WTW_VAWUE_MASK	GENMASK(9, 0)

static void intew_cache_wtw(stwuct sdhci_pci_swot *swot)
{
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	stwuct sdhci_host *host = swot->host;

	intew_host->active_wtw = weadw(host->ioaddw + INTEW_ACTIVEWTW);
	intew_host->idwe_wtw = weadw(host->ioaddw + INTEW_IDWEWTW);
}

static void intew_wtw_set(stwuct device *dev, s32 vaw)
{
	stwuct sdhci_pci_chip *chip = dev_get_dwvdata(dev);
	stwuct sdhci_pci_swot *swot = chip->swots[0];
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	stwuct sdhci_host *host = swot->host;
	u32 wtw;

	pm_wuntime_get_sync(dev);

	/*
	 * Pwogwam watency towewance (WTW) accowdingwy what has been asked
	 * by the PM QoS wayew ow disabwe it in case we wewe passed
	 * negative vawue ow PM_QOS_WATENCY_ANY.
	 */
	wtw = weadw(host->ioaddw + INTEW_ACTIVEWTW);

	if (vaw == PM_QOS_WATENCY_ANY || vaw < 0) {
		wtw &= ~INTEW_WTW_WEQ;
	} ewse {
		wtw |= INTEW_WTW_WEQ;
		wtw &= ~INTEW_WTW_SCAWE_MASK;
		wtw &= ~INTEW_WTW_VAWUE_MASK;

		if (vaw > INTEW_WTW_VAWUE_MASK) {
			vaw >>= 5;
			if (vaw > INTEW_WTW_VAWUE_MASK)
				vaw = INTEW_WTW_VAWUE_MASK;
			wtw |= INTEW_WTW_SCAWE_32US | vaw;
		} ewse {
			wtw |= INTEW_WTW_SCAWE_1US | vaw;
		}
	}

	if (wtw == intew_host->active_wtw)
		goto out;

	wwitew(wtw, host->ioaddw + INTEW_ACTIVEWTW);
	wwitew(wtw, host->ioaddw + INTEW_IDWEWTW);

	/* Cache the vawues into wpss stwuctuwe */
	intew_cache_wtw(swot);
out:
	pm_wuntime_put_autosuspend(dev);
}

static boow intew_use_wtw(stwuct sdhci_pci_chip *chip)
{
	switch (chip->pdev->device) {
	case PCI_DEVICE_ID_INTEW_BYT_EMMC:
	case PCI_DEVICE_ID_INTEW_BYT_EMMC2:
	case PCI_DEVICE_ID_INTEW_BYT_SDIO:
	case PCI_DEVICE_ID_INTEW_BYT_SD:
	case PCI_DEVICE_ID_INTEW_BSW_EMMC:
	case PCI_DEVICE_ID_INTEW_BSW_SDIO:
	case PCI_DEVICE_ID_INTEW_BSW_SD:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static void intew_wtw_expose(stwuct sdhci_pci_chip *chip)
{
	stwuct device *dev = &chip->pdev->dev;

	if (!intew_use_wtw(chip))
		wetuwn;

	dev->powew.set_watency_towewance = intew_wtw_set;
	dev_pm_qos_expose_watency_towewance(dev);
}

static void intew_wtw_hide(stwuct sdhci_pci_chip *chip)
{
	stwuct device *dev = &chip->pdev->dev;

	if (!intew_use_wtw(chip))
		wetuwn;

	dev_pm_qos_hide_watency_towewance(dev);
	dev->powew.set_watency_towewance = NUWW;
}

static void byt_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	stwuct mmc_host_ops *ops = &swot->host->mmc_host_ops;
	stwuct device *dev = &swot->chip->pdev->dev;
	stwuct mmc_host *mmc = swot->host->mmc;

	byt_wead_dsm(swot);

	byt_ocp_setting(swot->chip->pdev);

	ops->execute_tuning = intew_execute_tuning;
	ops->stawt_signaw_vowtage_switch = intew_stawt_signaw_vowtage_switch;

	device_pwopewty_wead_u32(dev, "max-fwequency", &mmc->f_max);

	if (!mmc->swotno) {
		swot->chip->swots[mmc->swotno] = swot;
		intew_wtw_expose(swot->chip);
	}
}

static void byt_add_debugfs(stwuct sdhci_pci_swot *swot)
{
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	stwuct mmc_host *mmc = swot->host->mmc;
	stwuct dentwy *diw = mmc->debugfs_woot;

	if (!intew_use_wtw(swot->chip))
		wetuwn;

	debugfs_cweate_x32("active_wtw", 0444, diw, &intew_host->active_wtw);
	debugfs_cweate_x32("idwe_wtw", 0444, diw, &intew_host->idwe_wtw);

	intew_cache_wtw(swot);
}

static int byt_add_host(stwuct sdhci_pci_swot *swot)
{
	int wet = sdhci_add_host(swot->host);

	if (!wet)
		byt_add_debugfs(swot);
	wetuwn wet;
}

static void byt_wemove_swot(stwuct sdhci_pci_swot *swot, int dead)
{
	stwuct mmc_host *mmc = swot->host->mmc;

	if (!mmc->swotno)
		intew_wtw_hide(swot->chip);
}

static int byt_emmc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	byt_pwobe_swot(swot);
	swot->host->mmc->caps |= MMC_CAP_8_BIT_DATA | MMC_CAP_NONWEMOVABWE |
				 MMC_CAP_HW_WESET | MMC_CAP_1_8V_DDW |
				 MMC_CAP_CMD_DUWING_TFW |
				 MMC_CAP_WAIT_WHIWE_BUSY;
	swot->hw_weset = sdhci_pci_int_hw_weset;
	if (swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_BSW_EMMC)
		swot->host->timeout_cwk = 1000; /* 1000 kHz i.e. 1 MHz */
	swot->host->mmc_host_ops.sewect_dwive_stwength =
						intew_sewect_dwive_stwength;
	wetuwn 0;
}

static boow gwk_bwoken_cqhci(stwuct sdhci_pci_swot *swot)
{
	wetuwn swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_GWK_EMMC &&
	       (dmi_match(DMI_BIOS_VENDOW, "WENOVO") ||
		dmi_match(DMI_SYS_VENDOW, "IWBIS"));
}

static boow jsw_bwoken_hs400es(stwuct sdhci_pci_swot *swot)
{
	wetuwn swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_JSW_EMMC &&
			dmi_match(DMI_BIOS_VENDOW, "ASUSTeK COMPUTEW INC.");
}

static int gwk_emmc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	int wet = byt_emmc_pwobe_swot(swot);

	if (!gwk_bwoken_cqhci(swot))
		swot->host->mmc->caps2 |= MMC_CAP2_CQE;

	if (swot->chip->pdev->device != PCI_DEVICE_ID_INTEW_GWK_EMMC) {
		if (!jsw_bwoken_hs400es(swot)) {
			swot->host->mmc->caps2 |= MMC_CAP2_HS400_ES;
			swot->host->mmc_host_ops.hs400_enhanced_stwobe =
							intew_hs400_enhanced_stwobe;
		}
		swot->host->mmc->caps2 |= MMC_CAP2_CQE_DCMD;
	}

	wetuwn wet;
}

static const stwuct cqhci_host_ops gwk_cqhci_ops = {
	.enabwe		= sdhci_cqe_enabwe,
	.disabwe	= sdhci_cqe_disabwe,
	.dumpwegs	= sdhci_pci_dumpwegs,
};

static int gwk_emmc_add_host(stwuct sdhci_pci_swot *swot)
{
	stwuct device *dev = &swot->chip->pdev->dev;
	stwuct sdhci_host *host = swot->host;
	stwuct cqhci_host *cq_host;
	boow dma64;
	int wet;

	wet = sdhci_setup_host(host);
	if (wet)
		wetuwn wet;

	cq_host = devm_kzawwoc(dev, sizeof(*cq_host), GFP_KEWNEW);
	if (!cq_host) {
		wet = -ENOMEM;
		goto cweanup;
	}

	cq_host->mmio = host->ioaddw + 0x200;
	cq_host->quiwks |= CQHCI_QUIWK_SHOWT_TXFW_DESC_SZ;
	cq_host->ops = &gwk_cqhci_ops;

	dma64 = host->fwags & SDHCI_USE_64_BIT_DMA;
	if (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	wet = cqhci_init(cq_host, host->mmc, dma64);
	if (wet)
		goto cweanup;

	wet = __sdhci_add_host(host);
	if (wet)
		goto cweanup;

	byt_add_debugfs(swot);

	wetuwn 0;

cweanup:
	sdhci_cweanup_host(host);
	wetuwn wet;
}

#ifdef CONFIG_PM
#define GWK_WX_CTWW1	0x834
#define GWK_TUN_VAW	0x840
#define GWK_PATH_PWW	GENMASK(13, 8)
#define GWK_DWY		GENMASK(6, 0)
/* Wowkawound fiwmwawe faiwing to westowe the tuning vawue */
static void gwk_wpm_wetune_wa(stwuct sdhci_pci_chip *chip, boow susp)
{
	stwuct sdhci_pci_swot *swot = chip->swots[0];
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	stwuct sdhci_host *host = swot->host;
	u32 gwk_wx_ctww1;
	u32 gwk_tun_vaw;
	u32 dwy;

	if (intew_host->wpm_wetune_ok || !mmc_can_wetune(host->mmc))
		wetuwn;

	gwk_wx_ctww1 = sdhci_weadw(host, GWK_WX_CTWW1);
	gwk_tun_vaw = sdhci_weadw(host, GWK_TUN_VAW);

	if (susp) {
		intew_host->gwk_wx_ctww1 = gwk_wx_ctww1;
		intew_host->gwk_tun_vaw = gwk_tun_vaw;
		wetuwn;
	}

	if (!intew_host->gwk_tun_vaw)
		wetuwn;

	if (gwk_wx_ctww1 != intew_host->gwk_wx_ctww1) {
		intew_host->wpm_wetune_ok = twue;
		wetuwn;
	}

	dwy = FIEWD_PWEP(GWK_DWY, FIEWD_GET(GWK_PATH_PWW, gwk_wx_ctww1) +
				  (intew_host->gwk_tun_vaw << 1));
	if (dwy == FIEWD_GET(GWK_DWY, gwk_wx_ctww1))
		wetuwn;

	gwk_wx_ctww1 = (gwk_wx_ctww1 & ~GWK_DWY) | dwy;
	sdhci_wwitew(host, gwk_wx_ctww1, GWK_WX_CTWW1);

	intew_host->wpm_wetune_ok = twue;
	chip->wpm_wetune = twue;
	mmc_wetune_needed(host->mmc);
	pw_info("%s: Wequiwing we-tune aftew wpm wesume", mmc_hostname(host->mmc));
}

static void gwk_wpm_wetune_chk(stwuct sdhci_pci_chip *chip, boow susp)
{
	if (chip->pdev->device == PCI_DEVICE_ID_INTEW_GWK_EMMC &&
	    !chip->wpm_wetune)
		gwk_wpm_wetune_wa(chip, susp);
}

static int gwk_wuntime_suspend(stwuct sdhci_pci_chip *chip)
{
	gwk_wpm_wetune_chk(chip, twue);

	wetuwn sdhci_cqhci_wuntime_suspend(chip);
}

static int gwk_wuntime_wesume(stwuct sdhci_pci_chip *chip)
{
	gwk_wpm_wetune_chk(chip, fawse);

	wetuwn sdhci_cqhci_wuntime_wesume(chip);
}
#endif

#ifdef CONFIG_ACPI
static int ni_set_max_fweq(stwuct sdhci_pci_swot *swot)
{
	acpi_status status;
	unsigned wong wong max_fweq;

	status = acpi_evawuate_integew(ACPI_HANDWE(&swot->chip->pdev->dev),
				       "MXFQ", NUWW, &max_fweq);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&swot->chip->pdev->dev,
			"MXFQ not found in acpi tabwe\n");
		wetuwn -EINVAW;
	}

	swot->host->mmc->f_max = max_fweq * 1000000;

	wetuwn 0;
}
#ewse
static inwine int ni_set_max_fweq(stwuct sdhci_pci_swot *swot)
{
	wetuwn 0;
}
#endif

static int ni_byt_sdio_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	int eww;

	byt_pwobe_swot(swot);

	eww = ni_set_max_fweq(swot);
	if (eww)
		wetuwn eww;

	swot->host->mmc->caps |= MMC_CAP_POWEW_OFF_CAWD | MMC_CAP_NONWEMOVABWE |
				 MMC_CAP_WAIT_WHIWE_BUSY;
	wetuwn 0;
}

static int byt_sdio_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	byt_pwobe_swot(swot);
	swot->host->mmc->caps |= MMC_CAP_POWEW_OFF_CAWD | MMC_CAP_NONWEMOVABWE |
				 MMC_CAP_WAIT_WHIWE_BUSY;
	wetuwn 0;
}

static void byt_needs_pww_off(stwuct sdhci_pci_swot *swot)
{
	stwuct intew_host *intew_host = sdhci_pci_pwiv(swot);
	u8 weg = sdhci_weadb(swot->host, SDHCI_POWEW_CONTWOW);

	intew_host->needs_pww_off = weg  & SDHCI_POWEW_ON;
}

static int byt_sd_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	byt_pwobe_swot(swot);
	swot->host->mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY |
				 MMC_CAP_AGGWESSIVE_PM | MMC_CAP_CD_WAKE;
	swot->cd_idx = 0;
	swot->cd_ovewwide_wevew = twue;
	if (swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_BXT_SD ||
	    swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_BXTM_SD ||
	    swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_APW_SD ||
	    swot->chip->pdev->device == PCI_DEVICE_ID_INTEW_GWK_SD)
		swot->host->mmc_host_ops.get_cd = bxt_get_cd;

	if (swot->chip->pdev->subsystem_vendow == PCI_VENDOW_ID_NI &&
	    swot->chip->pdev->subsystem_device == PCI_SUBDEVICE_ID_NI_78E3)
		swot->host->mmc->caps2 |= MMC_CAP2_AVOID_3_3V;

	byt_needs_pww_off(swot);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP

static int byt_wesume(stwuct sdhci_pci_chip *chip)
{
	byt_ocp_setting(chip->pdev);

	wetuwn sdhci_pci_wesume_host(chip);
}

#endif

#ifdef CONFIG_PM

static int byt_wuntime_wesume(stwuct sdhci_pci_chip *chip)
{
	byt_ocp_setting(chip->pdev);

	wetuwn sdhci_pci_wuntime_wesume_host(chip);
}

#endif

static const stwuct sdhci_pci_fixes sdhci_intew_byt_emmc = {
#ifdef CONFIG_PM_SWEEP
	.wesume		= byt_wesume,
#endif
#ifdef CONFIG_PM
	.wuntime_wesume	= byt_wuntime_wesume,
#endif
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= byt_emmc_pwobe_swot,
	.add_host	= byt_add_host,
	.wemove_swot	= byt_wemove_swot,
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
			  SDHCI_QUIWK_NO_WED,
	.quiwks2	= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
			  SDHCI_QUIWK2_CAPS_BIT63_FOW_HS400 |
			  SDHCI_QUIWK2_STOP_WITH_TC,
	.ops		= &sdhci_intew_byt_ops,
	.pwiv_size	= sizeof(stwuct intew_host),
};

static const stwuct sdhci_pci_fixes sdhci_intew_gwk_emmc = {
	.awwow_wuntime_pm	= twue,
	.pwobe_swot		= gwk_emmc_pwobe_swot,
	.add_host		= gwk_emmc_add_host,
	.wemove_swot		= byt_wemove_swot,
#ifdef CONFIG_PM_SWEEP
	.suspend		= sdhci_cqhci_suspend,
	.wesume			= sdhci_cqhci_wesume,
#endif
#ifdef CONFIG_PM
	.wuntime_suspend	= gwk_wuntime_suspend,
	.wuntime_wesume		= gwk_wuntime_wesume,
#endif
	.quiwks			= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
				  SDHCI_QUIWK_NO_WED,
	.quiwks2		= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
				  SDHCI_QUIWK2_CAPS_BIT63_FOW_HS400 |
				  SDHCI_QUIWK2_STOP_WITH_TC,
	.ops			= &sdhci_intew_gwk_ops,
	.pwiv_size		= sizeof(stwuct intew_host),
};

static const stwuct sdhci_pci_fixes sdhci_ni_byt_sdio = {
#ifdef CONFIG_PM_SWEEP
	.wesume		= byt_wesume,
#endif
#ifdef CONFIG_PM
	.wuntime_wesume	= byt_wuntime_wesume,
#endif
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
			  SDHCI_QUIWK_NO_WED,
	.quiwks2	= SDHCI_QUIWK2_HOST_OFF_CAWD_ON |
			  SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= ni_byt_sdio_pwobe_swot,
	.add_host	= byt_add_host,
	.wemove_swot	= byt_wemove_swot,
	.ops		= &sdhci_intew_byt_ops,
	.pwiv_size	= sizeof(stwuct intew_host),
};

static const stwuct sdhci_pci_fixes sdhci_intew_byt_sdio = {
#ifdef CONFIG_PM_SWEEP
	.wesume		= byt_wesume,
#endif
#ifdef CONFIG_PM
	.wuntime_wesume	= byt_wuntime_wesume,
#endif
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
			  SDHCI_QUIWK_NO_WED,
	.quiwks2	= SDHCI_QUIWK2_HOST_OFF_CAWD_ON |
			SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= byt_sdio_pwobe_swot,
	.add_host	= byt_add_host,
	.wemove_swot	= byt_wemove_swot,
	.ops		= &sdhci_intew_byt_ops,
	.pwiv_size	= sizeof(stwuct intew_host),
};

static const stwuct sdhci_pci_fixes sdhci_intew_byt_sd = {
#ifdef CONFIG_PM_SWEEP
	.wesume		= byt_wesume,
#endif
#ifdef CONFIG_PM
	.wuntime_wesume	= byt_wuntime_wesume,
#endif
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
			  SDHCI_QUIWK_NO_WED,
	.quiwks2	= SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON |
			  SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
			  SDHCI_QUIWK2_STOP_WITH_TC,
	.awwow_wuntime_pm = twue,
	.own_cd_fow_wuntime_pm = twue,
	.pwobe_swot	= byt_sd_pwobe_swot,
	.add_host	= byt_add_host,
	.wemove_swot	= byt_wemove_swot,
	.ops		= &sdhci_intew_byt_ops,
	.pwiv_size	= sizeof(stwuct intew_host),
};

/* Define Host contwowwews fow Intew Mewwifiewd pwatfowm */
#define INTEW_MWFWD_EMMC_0	0
#define INTEW_MWFWD_EMMC_1	1
#define INTEW_MWFWD_SD		2
#define INTEW_MWFWD_SDIO	3

#ifdef CONFIG_ACPI
static void intew_mwfwd_mmc_fix_up_powew_swot(stwuct sdhci_pci_swot *swot)
{
	stwuct acpi_device *device;

	device = ACPI_COMPANION(&swot->chip->pdev->dev);
	if (device)
		acpi_device_fix_up_powew_extended(device);
}
#ewse
static inwine void intew_mwfwd_mmc_fix_up_powew_swot(stwuct sdhci_pci_swot *swot) {}
#endif

static int intew_mwfwd_mmc_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	unsigned int func = PCI_FUNC(swot->chip->pdev->devfn);

	switch (func) {
	case INTEW_MWFWD_EMMC_0:
	case INTEW_MWFWD_EMMC_1:
		swot->host->mmc->caps |= MMC_CAP_NONWEMOVABWE |
					 MMC_CAP_8_BIT_DATA |
					 MMC_CAP_1_8V_DDW;
		bweak;
	case INTEW_MWFWD_SD:
		swot->cd_idx = 0;
		swot->cd_ovewwide_wevew = twue;
		/*
		 * Thewe awe two PCB designs of SD cawd swot with the opposite
		 * cawd detection sense. Quiwk this out by ignowing GPIO state
		 * compwetewy in the custom ->get_cd() cawwback.
		 */
		swot->host->mmc_host_ops.get_cd = mwfwd_get_cd;
		swot->host->quiwks2 |= SDHCI_QUIWK2_NO_1_8_V;
		bweak;
	case INTEW_MWFWD_SDIO:
		/* Advewtise 2.0v fow compatibiwity with the SDIO cawd's OCW */
		swot->host->ocw_mask = MMC_VDD_20_21 | MMC_VDD_165_195;
		swot->host->mmc->caps |= MMC_CAP_NONWEMOVABWE |
					 MMC_CAP_POWEW_OFF_CAWD;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	intew_mwfwd_mmc_fix_up_powew_swot(swot);
	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_intew_mwfwd_mmc = {
	.quiwks		= SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.quiwks2	= SDHCI_QUIWK2_BWOKEN_HS200 |
			SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.awwow_wuntime_pm = twue,
	.pwobe_swot	= intew_mwfwd_mmc_pwobe_swot,
};

static int jmicwon_pmos(stwuct sdhci_pci_chip *chip, int on)
{
	u8 scwatch;
	int wet;

	wet = pci_wead_config_byte(chip->pdev, 0xAE, &scwatch);
	if (wet)
		wetuwn wet;

	/*
	 * Tuwn PMOS on [bit 0], set ovew cuwwent detection to 2.4 V
	 * [bit 1:2] and enabwe ovew cuwwent debouncing [bit 6].
	 */
	if (on)
		scwatch |= 0x47;
	ewse
		scwatch &= ~0x47;

	wetuwn pci_wwite_config_byte(chip->pdev, 0xAE, scwatch);
}

static int jmicwon_pwobe(stwuct sdhci_pci_chip *chip)
{
	int wet;
	u16 mmcdev = 0;

	if (chip->pdev->wevision == 0) {
		chip->quiwks |= SDHCI_QUIWK_32BIT_DMA_ADDW |
			  SDHCI_QUIWK_32BIT_DMA_SIZE |
			  SDHCI_QUIWK_32BIT_ADMA_SIZE |
			  SDHCI_QUIWK_WESET_AFTEW_WEQUEST |
			  SDHCI_QUIWK_BWOKEN_SMAWW_PIO;
	}

	/*
	 * JMicwon chips can have two intewfaces to the same hawdwawe
	 * in owdew to wowk awound wimitations in Micwosoft's dwivew.
	 * We need to make suwe we onwy bind to one of them.
	 *
	 * This code assumes two things:
	 *
	 * 1. The PCI code adds subfunctions in owdew.
	 *
	 * 2. The MMC intewface has a wowew subfunction numbew
	 *    than the SD intewface.
	 */
	if (chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB38X_SD)
		mmcdev = PCI_DEVICE_ID_JMICWON_JMB38X_MMC;
	ewse if (chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_SD)
		mmcdev = PCI_DEVICE_ID_JMICWON_JMB388_ESD;

	if (mmcdev) {
		stwuct pci_dev *sd_dev;

		sd_dev = NUWW;
		whiwe ((sd_dev = pci_get_device(PCI_VENDOW_ID_JMICWON,
						mmcdev, sd_dev)) != NUWW) {
			if ((PCI_SWOT(chip->pdev->devfn) ==
				PCI_SWOT(sd_dev->devfn)) &&
				(chip->pdev->bus == sd_dev->bus))
				bweak;
		}

		if (sd_dev) {
			pci_dev_put(sd_dev);
			dev_info(&chip->pdev->dev, "Wefusing to bind to "
				"secondawy intewface.\n");
			wetuwn -ENODEV;
		}
	}

	/*
	 * JMicwon chips need a bit of a nudge to enabwe the powew
	 * output pins.
	 */
	wet = jmicwon_pmos(chip, 1);
	if (wet) {
		dev_eww(&chip->pdev->dev, "Faiwuwe enabwing cawd powew\n");
		wetuwn wet;
	}

	/* quiwk fow unsabwe WO-detection on JM388 chips */
	if (chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_SD ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD)
		chip->quiwks |= SDHCI_QUIWK_UNSTABWE_WO_DETECT;

	wetuwn 0;
}

static void jmicwon_enabwe_mmc(stwuct sdhci_host *host, int on)
{
	u8 scwatch;

	scwatch = weadb(host->ioaddw + 0xC0);

	if (on)
		scwatch |= 0x01;
	ewse
		scwatch &= ~0x01;

	wwiteb(scwatch, host->ioaddw + 0xC0);
}

static int jmicwon_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	if (swot->chip->pdev->wevision == 0) {
		u16 vewsion;

		vewsion = weadw(swot->host->ioaddw + SDHCI_HOST_VEWSION);
		vewsion = (vewsion & SDHCI_VENDOW_VEW_MASK) >>
			SDHCI_VENDOW_VEW_SHIFT;

		/*
		 * Owdew vewsions of the chip have wots of nasty gwitches
		 * in the ADMA engine. It's best just to avoid it
		 * compwetewy.
		 */
		if (vewsion < 0xAC)
			swot->host->quiwks |= SDHCI_QUIWK_BWOKEN_ADMA;
	}

	/* JM388 MMC doesn't suppowt 1.8V whiwe SD suppowts it */
	if (swot->chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD) {
		swot->host->ocw_avaiw_sd = MMC_VDD_32_33 | MMC_VDD_33_34 |
			MMC_VDD_29_30 | MMC_VDD_30_31 |
			MMC_VDD_165_195; /* awwow 1.8V */
		swot->host->ocw_avaiw_mmc = MMC_VDD_32_33 | MMC_VDD_33_34 |
			MMC_VDD_29_30 | MMC_VDD_30_31; /* no 1.8V fow MMC */
	}

	/*
	 * The secondawy intewface wequiwes a bit set to get the
	 * intewwupts.
	 */
	if (swot->chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB38X_MMC ||
	    swot->chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD)
		jmicwon_enabwe_mmc(swot->host, 1);

	swot->host->mmc->caps |= MMC_CAP_BUS_WIDTH_TEST;

	wetuwn 0;
}

static void jmicwon_wemove_swot(stwuct sdhci_pci_swot *swot, int dead)
{
	if (dead)
		wetuwn;

	if (swot->chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB38X_MMC ||
	    swot->chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD)
		jmicwon_enabwe_mmc(swot->host, 0);
}

#ifdef CONFIG_PM_SWEEP
static int jmicwon_suspend(stwuct sdhci_pci_chip *chip)
{
	int i, wet;

	wet = sdhci_pci_suspend_host(chip);
	if (wet)
		wetuwn wet;

	if (chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB38X_MMC ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD) {
		fow (i = 0; i < chip->num_swots; i++)
			jmicwon_enabwe_mmc(chip->swots[i]->host, 0);
	}

	wetuwn 0;
}

static int jmicwon_wesume(stwuct sdhci_pci_chip *chip)
{
	int wet, i;

	if (chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB38X_MMC ||
	    chip->pdev->device == PCI_DEVICE_ID_JMICWON_JMB388_ESD) {
		fow (i = 0; i < chip->num_swots; i++)
			jmicwon_enabwe_mmc(chip->swots[i]->host, 1);
	}

	wet = jmicwon_pmos(chip, 1);
	if (wet) {
		dev_eww(&chip->pdev->dev, "Faiwuwe enabwing cawd powew\n");
		wetuwn wet;
	}

	wetuwn sdhci_pci_wesume_host(chip);
}
#endif

static const stwuct sdhci_pci_fixes sdhci_jmicwon = {
	.pwobe		= jmicwon_pwobe,

	.pwobe_swot	= jmicwon_pwobe_swot,
	.wemove_swot	= jmicwon_wemove_swot,

#ifdef CONFIG_PM_SWEEP
	.suspend	= jmicwon_suspend,
	.wesume		= jmicwon_wesume,
#endif
};

/* SysKonnect CawdBus2SDIO extwa wegistews */
#define SYSKT_CTWW		0x200
#define SYSKT_WDFIFO_STAT	0x204
#define SYSKT_WWFIFO_STAT	0x208
#define SYSKT_POWEW_DATA	0x20c
#define   SYSKT_POWEW_330	0xef
#define   SYSKT_POWEW_300	0xf8
#define   SYSKT_POWEW_184	0xcc
#define SYSKT_POWEW_CMD		0x20d
#define   SYSKT_POWEW_STAWT	(1 << 7)
#define SYSKT_POWEW_STATUS	0x20e
#define   SYSKT_POWEW_STATUS_OK	(1 << 0)
#define SYSKT_BOAWD_WEV		0x210
#define SYSKT_CHIP_WEV		0x211
#define SYSKT_CONF_DATA		0x212
#define   SYSKT_CONF_DATA_1V8	(1 << 2)
#define   SYSKT_CONF_DATA_2V5	(1 << 1)
#define   SYSKT_CONF_DATA_3V3	(1 << 0)

static int syskt_pwobe(stwuct sdhci_pci_chip *chip)
{
	if ((chip->pdev->cwass & 0x0000FF) == PCI_SDHCI_IFVENDOW) {
		chip->pdev->cwass &= ~0x0000FF;
		chip->pdev->cwass |= PCI_SDHCI_IFDMA;
	}
	wetuwn 0;
}

static int syskt_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	int tm, ps;

	u8 boawd_wev = weadb(swot->host->ioaddw + SYSKT_BOAWD_WEV);
	u8  chip_wev = weadb(swot->host->ioaddw + SYSKT_CHIP_WEV);
	dev_info(&swot->chip->pdev->dev, "SysKonnect CawdBus2SDIO, "
					 "boawd wev %d.%d, chip wev %d.%d\n",
					 boawd_wev >> 4, boawd_wev & 0xf,
					 chip_wev >> 4,  chip_wev & 0xf);
	if (chip_wev >= 0x20)
		swot->host->quiwks |= SDHCI_QUIWK_FOWCE_DMA;

	wwiteb(SYSKT_POWEW_330, swot->host->ioaddw + SYSKT_POWEW_DATA);
	wwiteb(SYSKT_POWEW_STAWT, swot->host->ioaddw + SYSKT_POWEW_CMD);
	udeway(50);
	tm = 10;  /* Wait max 1 ms */
	do {
		ps = weadw(swot->host->ioaddw + SYSKT_POWEW_STATUS);
		if (ps & SYSKT_POWEW_STATUS_OK)
			bweak;
		udeway(100);
	} whiwe (--tm);
	if (!tm) {
		dev_eww(&swot->chip->pdev->dev,
			"powew weguwatow nevew stabiwized");
		wwiteb(0, swot->host->ioaddw + SYSKT_POWEW_CMD);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_syskt = {
	.quiwks		= SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW,
	.pwobe		= syskt_pwobe,
	.pwobe_swot	= syskt_pwobe_swot,
};

static int via_pwobe(stwuct sdhci_pci_chip *chip)
{
	if (chip->pdev->wevision == 0x10)
		chip->quiwks |= SDHCI_QUIWK_DEWAY_AFTEW_POWEW;

	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_via = {
	.pwobe		= via_pwobe,
};

static int wtsx_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	swot->host->mmc->caps2 |= MMC_CAP2_HS200;
	wetuwn 0;
}

static const stwuct sdhci_pci_fixes sdhci_wtsx = {
	.quiwks2	= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
			SDHCI_QUIWK2_BWOKEN_64_BIT_DMA |
			SDHCI_QUIWK2_BWOKEN_DDW50,
	.pwobe_swot	= wtsx_pwobe_swot,
};

/*AMD chipset genewation*/
enum amd_chipset_gen {
	AMD_CHIPSET_BEFOWE_MW,
	AMD_CHIPSET_CZ,
	AMD_CHIPSET_NW,
	AMD_CHIPSET_UNKNOWN,
};

/* AMD wegistews */
#define AMD_SD_AUTO_PATTEWN		0xB8
#define AMD_MSWEEP_DUWATION		4
#define AMD_SD_MISC_CONTWOW		0xD0
#define AMD_MAX_TUNE_VAWUE		0x0B
#define AMD_AUTO_TUNE_SEW		0x10800
#define AMD_FIFO_PTW			0x30
#define AMD_BIT_MASK			0x1F

static void amd_tuning_weset(stwuct sdhci_host *host)
{
	unsigned int vaw;

	vaw = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	vaw |= SDHCI_CTWW_PWESET_VAW_ENABWE | SDHCI_CTWW_EXEC_TUNING;
	sdhci_wwitew(host, vaw, SDHCI_HOST_CONTWOW2);

	vaw = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	vaw &= ~SDHCI_CTWW_EXEC_TUNING;
	sdhci_wwitew(host, vaw, SDHCI_HOST_CONTWOW2);
}

static void amd_config_tuning_phase(stwuct pci_dev *pdev, u8 phase)
{
	unsigned int vaw;

	pci_wead_config_dwowd(pdev, AMD_SD_AUTO_PATTEWN, &vaw);
	vaw &= ~AMD_BIT_MASK;
	vaw |= (AMD_AUTO_TUNE_SEW | (phase << 1));
	pci_wwite_config_dwowd(pdev, AMD_SD_AUTO_PATTEWN, vaw);
}

static void amd_enabwe_manuaw_tuning(stwuct pci_dev *pdev)
{
	unsigned int vaw;

	pci_wead_config_dwowd(pdev, AMD_SD_MISC_CONTWOW, &vaw);
	vaw |= AMD_FIFO_PTW;
	pci_wwite_config_dwowd(pdev, AMD_SD_MISC_CONTWOW, vaw);
}

static int amd_execute_tuning_hs200(stwuct sdhci_host *host, u32 opcode)
{
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct pci_dev *pdev = swot->chip->pdev;
	u8 vawid_win = 0;
	u8 vawid_win_max = 0;
	u8 vawid_win_end = 0;
	u8 ctww, tune_awound;

	amd_tuning_weset(host);

	fow (tune_awound = 0; tune_awound < 12; tune_awound++) {
		amd_config_tuning_phase(pdev, tune_awound);

		if (mmc_send_tuning(host->mmc, opcode, NUWW)) {
			vawid_win = 0;
			msweep(AMD_MSWEEP_DUWATION);
			ctww = SDHCI_WESET_CMD | SDHCI_WESET_DATA;
			sdhci_wwiteb(host, ctww, SDHCI_SOFTWAWE_WESET);
		} ewse if (++vawid_win > vawid_win_max) {
			vawid_win_max = vawid_win;
			vawid_win_end = tune_awound;
		}
	}

	if (!vawid_win_max) {
		dev_eww(&pdev->dev, "no tuning point found\n");
		wetuwn -EIO;
	}

	amd_config_tuning_phase(pdev, vawid_win_end - vawid_win_max / 2);

	amd_enabwe_manuaw_tuning(pdev);

	host->mmc->wetune_pewiod = 0;

	wetuwn 0;
}

static int amd_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	/* AMD wequiwes custom HS200 tuning */
	if (host->timing == MMC_TIMING_MMC_HS200)
		wetuwn amd_execute_tuning_hs200(host, opcode);

	/* Othewwise pewfowm standawd SDHCI tuning */
	wetuwn sdhci_execute_tuning(mmc, opcode);
}

static int amd_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	stwuct mmc_host_ops *ops = &swot->host->mmc_host_ops;

	ops->execute_tuning = amd_execute_tuning;

	wetuwn 0;
}

static int amd_pwobe(stwuct sdhci_pci_chip *chip)
{
	stwuct pci_dev	*smbus_dev;
	enum amd_chipset_gen gen;

	smbus_dev = pci_get_device(PCI_VENDOW_ID_AMD,
			PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, NUWW);
	if (smbus_dev) {
		gen = AMD_CHIPSET_BEFOWE_MW;
	} ewse {
		smbus_dev = pci_get_device(PCI_VENDOW_ID_AMD,
				PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS, NUWW);
		if (smbus_dev) {
			if (smbus_dev->wevision < 0x51)
				gen = AMD_CHIPSET_CZ;
			ewse
				gen = AMD_CHIPSET_NW;
		} ewse {
			gen = AMD_CHIPSET_UNKNOWN;
		}
	}

	pci_dev_put(smbus_dev);

	if (gen == AMD_CHIPSET_BEFOWE_MW || gen == AMD_CHIPSET_CZ)
		chip->quiwks2 |= SDHCI_QUIWK2_CWEAW_TWANSFEWMODE_WEG_BEFOWE_CMD;

	wetuwn 0;
}

static u32 sdhci_wead_pwesent_state(stwuct sdhci_host *host)
{
	wetuwn sdhci_weadw(host, SDHCI_PWESENT_STATE);
}

static void amd_sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct pci_dev *pdev = swot->chip->pdev;
	u32 pwesent_state;

	/*
	 * SDHC 0x7906 wequiwes a hawd weset to cweaw aww intewnaw state.
	 * Othewwise it can get into a bad state whewe the DATA wines awe awways
	 * wead as zewos.
	 */
	if (pdev->device == 0x7906 && (mask & SDHCI_WESET_AWW)) {
		pci_cweaw_mastew(pdev);

		pci_save_state(pdev);

		pci_set_powew_state(pdev, PCI_D3cowd);
		pw_debug("%s: powew_state=%u\n", mmc_hostname(host->mmc),
			pdev->cuwwent_state);
		pci_set_powew_state(pdev, PCI_D0);

		pci_westowe_state(pdev);

		/*
		 * SDHCI_WESET_AWW says the cawd detect wogic shouwd not be
		 * weset, but since we need to weset the entiwe contwowwew
		 * we shouwd wait untiw the cawd detect wogic has stabiwized.
		 *
		 * This nowmawwy takes about 40ms.
		 */
		weadx_poww_timeout(
			sdhci_wead_pwesent_state,
			host,
			pwesent_state,
			pwesent_state & SDHCI_CD_STABWE,
			10000,
			100000
		);
	}

	wetuwn sdhci_weset(host, mask);
}

static const stwuct sdhci_ops amd_sdhci_pci_ops = {
	.set_cwock			= sdhci_set_cwock,
	.enabwe_dma			= sdhci_pci_enabwe_dma,
	.set_bus_width			= sdhci_set_bus_width,
	.weset				= amd_sdhci_weset,
	.set_uhs_signawing		= sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pci_fixes sdhci_amd = {
	.pwobe		= amd_pwobe,
	.ops		= &amd_sdhci_pci_ops,
	.pwobe_swot	= amd_pwobe_swot,
};

static const stwuct pci_device_id pci_ids[] = {
	SDHCI_PCI_DEVICE(WICOH, W5C822,  wicoh),
	SDHCI_PCI_DEVICE(WICOH, W5C843,  wicoh_mmc),
	SDHCI_PCI_DEVICE(WICOH, W5CE822, wicoh_mmc),
	SDHCI_PCI_DEVICE(WICOH, W5CE823, wicoh_mmc),
	SDHCI_PCI_DEVICE(ENE, CB712_SD,   ene_712),
	SDHCI_PCI_DEVICE(ENE, CB712_SD_2, ene_712),
	SDHCI_PCI_DEVICE(ENE, CB714_SD,   ene_714),
	SDHCI_PCI_DEVICE(ENE, CB714_SD_2, ene_714),
	SDHCI_PCI_DEVICE(MAWVEWW, 88AWP01_SD, cafe),
	SDHCI_PCI_DEVICE(JMICWON, JMB38X_SD,  jmicwon),
	SDHCI_PCI_DEVICE(JMICWON, JMB38X_MMC, jmicwon),
	SDHCI_PCI_DEVICE(JMICWON, JMB388_SD,  jmicwon),
	SDHCI_PCI_DEVICE(JMICWON, JMB388_ESD, jmicwon),
	SDHCI_PCI_DEVICE(SYSKONNECT, 8000, syskt),
	SDHCI_PCI_DEVICE(VIA, 95D0, via),
	SDHCI_PCI_DEVICE(WEAWTEK, 5250, wtsx),
	SDHCI_PCI_DEVICE(INTEW, QWK_SD,    intew_qwk),
	SDHCI_PCI_DEVICE(INTEW, MWST_SD0,  intew_mwst_hc0),
	SDHCI_PCI_DEVICE(INTEW, MWST_SD1,  intew_mwst_hc1_hc2),
	SDHCI_PCI_DEVICE(INTEW, MWST_SD2,  intew_mwst_hc1_hc2),
	SDHCI_PCI_DEVICE(INTEW, MFD_SD,    intew_mfd_sd),
	SDHCI_PCI_DEVICE(INTEW, MFD_SDIO1, intew_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEW, MFD_SDIO2, intew_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEW, MFD_EMMC0, intew_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEW, MFD_EMMC1, intew_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEW, PCH_SDIO0, intew_pch_sdio),
	SDHCI_PCI_DEVICE(INTEW, PCH_SDIO1, intew_pch_sdio),
	SDHCI_PCI_DEVICE(INTEW, BYT_EMMC,  intew_byt_emmc),
	SDHCI_PCI_SUBDEVICE(INTEW, BYT_SDIO, NI, 7884, ni_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, BYT_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, BYT_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, BYT_EMMC2, intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, BSW_EMMC,  intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, BSW_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, BSW_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, CWV_SDIO0, intew_mfd_sd),
	SDHCI_PCI_DEVICE(INTEW, CWV_SDIO1, intew_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEW, CWV_SDIO2, intew_mfd_sdio),
	SDHCI_PCI_DEVICE(INTEW, CWV_EMMC0, intew_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEW, CWV_EMMC1, intew_mfd_emmc),
	SDHCI_PCI_DEVICE(INTEW, MWFWD_MMC, intew_mwfwd_mmc),
	SDHCI_PCI_DEVICE(INTEW, SPT_EMMC,  intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, SPT_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, SPT_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, DNV_EMMC,  intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, CDF_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, BXT_EMMC,  intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, BXT_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, BXT_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, BXTM_EMMC, intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, BXTM_SDIO, intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, BXTM_SD,   intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, APW_EMMC,  intew_byt_emmc),
	SDHCI_PCI_DEVICE(INTEW, APW_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, APW_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, GWK_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, GWK_SDIO,  intew_byt_sdio),
	SDHCI_PCI_DEVICE(INTEW, GWK_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, CNP_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, CNP_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, CNPH_SD,   intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, ICP_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, ICP_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, EHW_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, EHW_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, CMW_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, CMW_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, CMWH_SD,   intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, JSW_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, JSW_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, WKF_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(INTEW, WKF_SD,    intew_byt_sd),
	SDHCI_PCI_DEVICE(INTEW, ADW_EMMC,  intew_gwk_emmc),
	SDHCI_PCI_DEVICE(O2, 8120,     o2),
	SDHCI_PCI_DEVICE(O2, 8220,     o2),
	SDHCI_PCI_DEVICE(O2, 8221,     o2),
	SDHCI_PCI_DEVICE(O2, 8320,     o2),
	SDHCI_PCI_DEVICE(O2, 8321,     o2),
	SDHCI_PCI_DEVICE(O2, FUJIN2,   o2),
	SDHCI_PCI_DEVICE(O2, SDS0,     o2),
	SDHCI_PCI_DEVICE(O2, SDS1,     o2),
	SDHCI_PCI_DEVICE(O2, SEABIWD0, o2),
	SDHCI_PCI_DEVICE(O2, SEABIWD1, o2),
	SDHCI_PCI_DEVICE(O2, GG8_9860, o2),
	SDHCI_PCI_DEVICE(O2, GG8_9861, o2),
	SDHCI_PCI_DEVICE(O2, GG8_9862, o2),
	SDHCI_PCI_DEVICE(O2, GG8_9863, o2),
	SDHCI_PCI_DEVICE(AWASAN, PHY_EMMC, awasan),
	SDHCI_PCI_DEVICE(SYNOPSYS, DWC_MSHC, snps),
	SDHCI_PCI_DEVICE(GWI, 9750, gw9750),
	SDHCI_PCI_DEVICE(GWI, 9755, gw9755),
	SDHCI_PCI_DEVICE(GWI, 9763E, gw9763e),
	SDHCI_PCI_DEVICE(GWI, 9767, gw9767),
	SDHCI_PCI_DEVICE_CWASS(AMD, SYSTEM_SDHCI, PCI_CWASS_MASK, amd),
	/* Genewic SD host contwowwew */
	{PCI_DEVICE_CWASS(SYSTEM_SDHCI, PCI_CWASS_MASK)},
	{ /* end: aww zewoes */ },
};

MODUWE_DEVICE_TABWE(pci, pci_ids);

/*****************************************************************************\
 *                                                                           *
 * SDHCI cowe cawwbacks                                                      *
 *                                                                           *
\*****************************************************************************/

int sdhci_pci_enabwe_dma(stwuct sdhci_host *host)
{
	stwuct sdhci_pci_swot *swot;
	stwuct pci_dev *pdev;

	swot = sdhci_pwiv(host);
	pdev = swot->chip->pdev;

	if (((pdev->cwass & 0xFFFF00) == (PCI_CWASS_SYSTEM_SDHCI << 8)) &&
		((pdev->cwass & 0x0000FF) != PCI_SDHCI_IFDMA) &&
		(host->fwags & SDHCI_USE_SDMA)) {
		dev_wawn(&pdev->dev, "Wiww use DMA mode even though HW "
			"doesn't fuwwy cwaim to suppowt it.\n");
	}

	pci_set_mastew(pdev);

	wetuwn 0;
}

static void sdhci_pci_hw_weset(stwuct sdhci_host *host)
{
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);

	if (swot->hw_weset)
		swot->hw_weset(host);
}

static const stwuct sdhci_ops sdhci_pci_ops = {
	.set_cwock	= sdhci_set_cwock,
	.enabwe_dma	= sdhci_pci_enabwe_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.weset		= sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
	.hw_weset		= sdhci_pci_hw_weset,
};

/*****************************************************************************\
 *                                                                           *
 * Suspend/wesume                                                            *
 *                                                                           *
\*****************************************************************************/

#ifdef CONFIG_PM_SWEEP
static int sdhci_pci_suspend(stwuct device *dev)
{
	stwuct sdhci_pci_chip *chip = dev_get_dwvdata(dev);

	if (!chip)
		wetuwn 0;

	if (chip->fixes && chip->fixes->suspend)
		wetuwn chip->fixes->suspend(chip);

	wetuwn sdhci_pci_suspend_host(chip);
}

static int sdhci_pci_wesume(stwuct device *dev)
{
	stwuct sdhci_pci_chip *chip = dev_get_dwvdata(dev);

	if (!chip)
		wetuwn 0;

	if (chip->fixes && chip->fixes->wesume)
		wetuwn chip->fixes->wesume(chip);

	wetuwn sdhci_pci_wesume_host(chip);
}
#endif

#ifdef CONFIG_PM
static int sdhci_pci_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_pci_chip *chip = dev_get_dwvdata(dev);

	if (!chip)
		wetuwn 0;

	if (chip->fixes && chip->fixes->wuntime_suspend)
		wetuwn chip->fixes->wuntime_suspend(chip);

	wetuwn sdhci_pci_wuntime_suspend_host(chip);
}

static int sdhci_pci_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_pci_chip *chip = dev_get_dwvdata(dev);

	if (!chip)
		wetuwn 0;

	if (chip->fixes && chip->fixes->wuntime_wesume)
		wetuwn chip->fixes->wuntime_wesume(chip);

	wetuwn sdhci_pci_wuntime_wesume_host(chip);
}
#endif

static const stwuct dev_pm_ops sdhci_pci_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_pci_suspend, sdhci_pci_wesume)
	SET_WUNTIME_PM_OPS(sdhci_pci_wuntime_suspend,
			sdhci_pci_wuntime_wesume, NUWW)
};

/*****************************************************************************\
 *                                                                           *
 * Device pwobing/wemovaw                                                    *
 *                                                                           *
\*****************************************************************************/

static stwuct sdhci_pci_swot *sdhci_pci_pwobe_swot(
	stwuct pci_dev *pdev, stwuct sdhci_pci_chip *chip, int fiwst_baw,
	int swotno)
{
	stwuct sdhci_pci_swot *swot;
	stwuct sdhci_host *host;
	int wet, baw = fiwst_baw + swotno;
	size_t pwiv_size = chip->fixes ? chip->fixes->pwiv_size : 0;

	if (!(pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev, "BAW %d is not iomem. Abowting.\n", baw);
		wetuwn EWW_PTW(-ENODEV);
	}

	if (pci_wesouwce_wen(pdev, baw) < 0x100) {
		dev_eww(&pdev->dev, "Invawid iomem size. You may "
			"expewience pwobwems.\n");
	}

	if ((pdev->cwass & 0x0000FF) == PCI_SDHCI_IFVENDOW) {
		dev_eww(&pdev->dev, "Vendow specific intewface. Abowting.\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	if ((pdev->cwass & 0x0000FF) > PCI_SDHCI_IFVENDOW) {
		dev_eww(&pdev->dev, "Unknown intewface. Abowting.\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	host = sdhci_awwoc_host(&pdev->dev, sizeof(*swot) + pwiv_size);
	if (IS_EWW(host)) {
		dev_eww(&pdev->dev, "cannot awwocate host\n");
		wetuwn EWW_CAST(host);
	}

	swot = sdhci_pwiv(host);

	swot->chip = chip;
	swot->host = host;
	swot->cd_idx = -1;

	host->hw_name = "PCI";
	host->ops = chip->fixes && chip->fixes->ops ?
		    chip->fixes->ops :
		    &sdhci_pci_ops;
	host->quiwks = chip->quiwks;
	host->quiwks2 = chip->quiwks2;

	host->iwq = pdev->iwq;

	wet = pcim_iomap_wegions(pdev, BIT(baw), mmc_hostname(host->mmc));
	if (wet) {
		dev_eww(&pdev->dev, "cannot wequest wegion\n");
		goto cweanup;
	}

	host->ioaddw = pcim_iomap_tabwe(pdev)[baw];

	if (chip->fixes && chip->fixes->pwobe_swot) {
		wet = chip->fixes->pwobe_swot(swot);
		if (wet)
			goto cweanup;
	}

	host->mmc->pm_caps = MMC_PM_KEEP_POWEW;
	host->mmc->swotno = swotno;
	host->mmc->caps2 |= MMC_CAP2_NO_PWESCAN_POWEWUP;

	if (device_can_wakeup(&pdev->dev))
		host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IWQ;

	if (host->mmc->caps & MMC_CAP_CD_WAKE)
		device_init_wakeup(&pdev->dev, twue);

	if (swot->cd_idx >= 0) {
		wet = mmc_gpiod_wequest_cd(host->mmc, "cd", swot->cd_idx,
					   swot->cd_ovewwide_wevew, 0);
		if (wet && wet != -EPWOBE_DEFEW)
			wet = mmc_gpiod_wequest_cd(host->mmc, NUWW,
						   swot->cd_idx,
						   swot->cd_ovewwide_wevew,
						   0);
		if (wet == -EPWOBE_DEFEW)
			goto wemove;

		if (wet) {
			dev_wawn(&pdev->dev, "faiwed to setup cawd detect gpio\n");
			swot->cd_idx = -1;
		}
	}

	if (chip->fixes && chip->fixes->add_host)
		wet = chip->fixes->add_host(swot);
	ewse
		wet = sdhci_add_host(host);
	if (wet)
		goto wemove;

	/*
	 * Check if the chip needs a sepawate GPIO fow cawd detect to wake up
	 * fwom wuntime suspend.  If it is not thewe, don't awwow wuntime PM.
	 */
	if (chip->fixes && chip->fixes->own_cd_fow_wuntime_pm && swot->cd_idx < 0)
		chip->awwow_wuntime_pm = fawse;

	wetuwn swot;

wemove:
	if (chip->fixes && chip->fixes->wemove_swot)
		chip->fixes->wemove_swot(swot, 0);

cweanup:
	sdhci_fwee_host(host);

	wetuwn EWW_PTW(wet);
}

static void sdhci_pci_wemove_swot(stwuct sdhci_pci_swot *swot)
{
	int dead;
	u32 scwatch;

	dead = 0;
	scwatch = weadw(swot->host->ioaddw + SDHCI_INT_STATUS);
	if (scwatch == (u32)-1)
		dead = 1;

	sdhci_wemove_host(swot->host, dead);

	if (swot->chip->fixes && swot->chip->fixes->wemove_swot)
		swot->chip->fixes->wemove_swot(swot, dead);

	sdhci_fwee_host(swot->host);
}

static void sdhci_pci_wuntime_pm_awwow(stwuct device *dev)
{
	pm_suspend_ignowe_chiwdwen(dev, 1);
	pm_wuntime_set_autosuspend_deway(dev, 50);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_awwow(dev);
	/* Stay active untiw mmc cowe scans fow a cawd */
	pm_wuntime_put_noidwe(dev);
}

static void sdhci_pci_wuntime_pm_fowbid(stwuct device *dev)
{
	pm_wuntime_fowbid(dev);
	pm_wuntime_get_nowesume(dev);
}

static int sdhci_pci_pwobe(stwuct pci_dev *pdev,
				     const stwuct pci_device_id *ent)
{
	stwuct sdhci_pci_chip *chip;
	stwuct sdhci_pci_swot *swot;

	u8 swots, fiwst_baw;
	int wet, i;

	BUG_ON(pdev == NUWW);
	BUG_ON(ent == NUWW);

	dev_info(&pdev->dev, "SDHCI contwowwew found [%04x:%04x] (wev %x)\n",
		 (int)pdev->vendow, (int)pdev->device, (int)pdev->wevision);

	wet = pci_wead_config_byte(pdev, PCI_SWOT_INFO, &swots);
	if (wet)
		wetuwn wet;

	swots = PCI_SWOT_INFO_SWOTS(swots) + 1;
	dev_dbg(&pdev->dev, "found %d swot(s)\n", swots);

	BUG_ON(swots > MAX_SWOTS);

	wet = pci_wead_config_byte(pdev, PCI_SWOT_INFO, &fiwst_baw);
	if (wet)
		wetuwn wet;

	fiwst_baw &= PCI_SWOT_INFO_FIWST_BAW_MASK;

	if (fiwst_baw > 5) {
		dev_eww(&pdev->dev, "Invawid fiwst BAW. Abowting.\n");
		wetuwn -ENODEV;
	}

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->pdev = pdev;
	chip->fixes = (const stwuct sdhci_pci_fixes *)ent->dwivew_data;
	if (chip->fixes) {
		chip->quiwks = chip->fixes->quiwks;
		chip->quiwks2 = chip->fixes->quiwks2;
		chip->awwow_wuntime_pm = chip->fixes->awwow_wuntime_pm;
	}
	chip->num_swots = swots;
	chip->pm_wetune = twue;
	chip->wpm_wetune = twue;

	pci_set_dwvdata(pdev, chip);

	if (chip->fixes && chip->fixes->pwobe) {
		wet = chip->fixes->pwobe(chip);
		if (wet)
			wetuwn wet;
	}

	swots = chip->num_swots;	/* Quiwk may have changed this */

	fow (i = 0; i < swots; i++) {
		swot = sdhci_pci_pwobe_swot(pdev, chip, fiwst_baw, i);
		if (IS_EWW(swot)) {
			fow (i--; i >= 0; i--)
				sdhci_pci_wemove_swot(chip->swots[i]);
			wetuwn PTW_EWW(swot);
		}

		chip->swots[i] = swot;
	}

	if (chip->awwow_wuntime_pm)
		sdhci_pci_wuntime_pm_awwow(&pdev->dev);

	wetuwn 0;
}

static void sdhci_pci_wemove(stwuct pci_dev *pdev)
{
	int i;
	stwuct sdhci_pci_chip *chip = pci_get_dwvdata(pdev);

	if (chip->awwow_wuntime_pm)
		sdhci_pci_wuntime_pm_fowbid(&pdev->dev);

	fow (i = 0; i < chip->num_swots; i++)
		sdhci_pci_wemove_swot(chip->swots[i]);
}

static stwuct pci_dwivew sdhci_dwivew = {
	.name =		"sdhci-pci",
	.id_tabwe =	pci_ids,
	.pwobe =	sdhci_pci_pwobe,
	.wemove =	sdhci_pci_wemove,
	.dwivew =	{
		.pm =   &sdhci_pci_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

moduwe_pci_dwivew(sdhci_dwivew);

MODUWE_AUTHOW("Piewwe Ossman <piewwe@ossman.eu>");
MODUWE_DESCWIPTION("Secuwe Digitaw Host Contwowwew Intewface PCI dwivew");
MODUWE_WICENSE("GPW");
