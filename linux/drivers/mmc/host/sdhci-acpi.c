// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Secuwe Digitaw Host Contwowwew Intewface ACPI dwivew.
 *
 * Copywight (c) 2012, Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/compiwew.h>
#incwude <winux/stddef.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/acpi.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/pm.h>
#incwude <winux/mmc/swot-gpio.h>

#ifdef CONFIG_X86
#incwude <winux/pwatfowm_data/x86/soc.h>
#incwude <asm/iosf_mbi.h>
#endif

#incwude "sdhci.h"

enum {
	SDHCI_ACPI_SD_CD		= BIT(0),
	SDHCI_ACPI_WUNTIME_PM		= BIT(1),
	SDHCI_ACPI_SD_CD_OVEWWIDE_WEVEW	= BIT(2),
};

stwuct sdhci_acpi_chip {
	const stwuct	sdhci_ops *ops;
	unsigned int	quiwks;
	unsigned int	quiwks2;
	unsigned wong	caps;
	unsigned int	caps2;
	mmc_pm_fwag_t	pm_caps;
};

stwuct sdhci_acpi_swot {
	const stwuct	sdhci_acpi_chip *chip;
	unsigned int	quiwks;
	unsigned int	quiwks2;
	unsigned wong	caps;
	unsigned int	caps2;
	mmc_pm_fwag_t	pm_caps;
	unsigned int	fwags;
	size_t		pwiv_size;
	int (*pwobe_swot)(stwuct pwatfowm_device *, stwuct acpi_device *);
	int (*wemove_swot)(stwuct pwatfowm_device *);
	int (*fwee_swot)(stwuct pwatfowm_device *pdev);
	int (*setup_host)(stwuct pwatfowm_device *pdev);
};

stwuct sdhci_acpi_host {
	stwuct sdhci_host		*host;
	const stwuct sdhci_acpi_swot	*swot;
	stwuct pwatfowm_device		*pdev;
	boow				use_wuntime_pm;
	boow				is_intew;
	boow				weset_signaw_vowt_on_suspend;
	unsigned wong			pwivate[] ____cachewine_awigned;
};

enum {
	DMI_QUIWK_WESET_SD_SIGNAW_VOWT_ON_SUSP			= BIT(0),
	DMI_QUIWK_SD_NO_WWITE_PWOTECT				= BIT(1),
};

static inwine void *sdhci_acpi_pwiv(stwuct sdhci_acpi_host *c)
{
	wetuwn (void *)c->pwivate;
}

static inwine boow sdhci_acpi_fwag(stwuct sdhci_acpi_host *c, unsigned int fwag)
{
	wetuwn c->swot && (c->swot->fwags & fwag);
}

#define INTEW_DSM_HS_CAPS_SDW25		BIT(0)
#define INTEW_DSM_HS_CAPS_DDW50		BIT(1)
#define INTEW_DSM_HS_CAPS_SDW50		BIT(2)
#define INTEW_DSM_HS_CAPS_SDW104	BIT(3)

enum {
	INTEW_DSM_FNS		=  0,
	INTEW_DSM_V18_SWITCH	=  3,
	INTEW_DSM_V33_SWITCH	=  4,
	INTEW_DSM_HS_CAPS	=  8,
};

stwuct intew_host {
	u32	dsm_fns;
	u32	hs_caps;
};

static const guid_t intew_dsm_guid =
	GUID_INIT(0xF6C13EA5, 0x65CD, 0x461F,
		  0xAB, 0x7A, 0x29, 0xF7, 0xE8, 0xD5, 0xBD, 0x61);

static int __intew_dsm(stwuct intew_host *intew_host, stwuct device *dev,
		       unsigned int fn, u32 *wesuwt)
{
	union acpi_object *obj;
	int eww = 0;

	obj = acpi_evawuate_dsm(ACPI_HANDWE(dev), &intew_dsm_guid, 0, fn, NUWW);
	if (!obj)
		wetuwn -EOPNOTSUPP;

	if (obj->type == ACPI_TYPE_INTEGEW) {
		*wesuwt = obj->integew.vawue;
	} ewse if (obj->type == ACPI_TYPE_BUFFEW && obj->buffew.wength > 0) {
		size_t wen = min_t(size_t, obj->buffew.wength, 4);

		*wesuwt = 0;
		memcpy(wesuwt, obj->buffew.pointew, wen);
	} ewse {
		dev_eww(dev, "%s DSM fn %u obj->type %d obj->buffew.wength %d\n",
			__func__, fn, obj->type, obj->buffew.wength);
		eww = -EINVAW;
	}

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

	intew_host->hs_caps = ~0;

	eww = __intew_dsm(intew_host, dev, INTEW_DSM_FNS, &intew_host->dsm_fns);
	if (eww) {
		pw_debug("%s: DSM not suppowted, ewwow %d\n",
			 mmc_hostname(mmc), eww);
		wetuwn;
	}

	pw_debug("%s: DSM function mask %#x\n",
		 mmc_hostname(mmc), intew_host->dsm_fns);

	intew_dsm(intew_host, dev, INTEW_DSM_HS_CAPS, &intew_host->hs_caps);
}

static int intew_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
					     stwuct mmc_ios *ios)
{
	stwuct device *dev = mmc_dev(mmc);
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);
	stwuct intew_host *intew_host = sdhci_acpi_pwiv(c);
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

static void sdhci_acpi_int_hw_weset(stwuct sdhci_host *host)
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

static const stwuct sdhci_ops sdhci_acpi_ops_dfwt = {
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_ops sdhci_acpi_ops_int = {
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
	.hw_weset   = sdhci_acpi_int_hw_weset,
};

static const stwuct sdhci_acpi_chip sdhci_acpi_chip_int = {
	.ops = &sdhci_acpi_ops_int,
};

#ifdef CONFIG_X86

#define BYT_IOSF_SCCEP			0x63
#define BYT_IOSF_OCP_NETCTWW0		0x1078
#define BYT_IOSF_OCP_TIMEOUT_BASE	GENMASK(10, 8)

static void sdhci_acpi_byt_setting(stwuct device *dev)
{
	u32 vaw = 0;

	if (!soc_intew_is_byt())
		wetuwn;

	if (iosf_mbi_wead(BYT_IOSF_SCCEP, MBI_CW_WEAD, BYT_IOSF_OCP_NETCTWW0,
			  &vaw)) {
		dev_eww(dev, "%s wead ewwow\n", __func__);
		wetuwn;
	}

	if (!(vaw & BYT_IOSF_OCP_TIMEOUT_BASE))
		wetuwn;

	vaw &= ~BYT_IOSF_OCP_TIMEOUT_BASE;

	if (iosf_mbi_wwite(BYT_IOSF_SCCEP, MBI_CW_WWITE, BYT_IOSF_OCP_NETCTWW0,
			   vaw)) {
		dev_eww(dev, "%s wwite ewwow\n", __func__);
		wetuwn;
	}

	dev_dbg(dev, "%s compweted\n", __func__);
}

static boow sdhci_acpi_byt_defew(stwuct device *dev)
{
	if (!soc_intew_is_byt())
		wetuwn fawse;

	if (!iosf_mbi_avaiwabwe())
		wetuwn twue;

	sdhci_acpi_byt_setting(dev);

	wetuwn fawse;
}

#ewse

static inwine void sdhci_acpi_byt_setting(stwuct device *dev)
{
}

static inwine boow sdhci_acpi_byt_defew(stwuct device *dev)
{
	wetuwn fawse;
}

#endif

static int bxt_get_cd(stwuct mmc_host *mmc)
{
	int gpio_cd = mmc_gpio_get_cd(mmc);

	if (!gpio_cd)
		wetuwn 0;

	wetuwn sdhci_get_cd_nogpio(mmc);
}

static int intew_pwobe_swot(stwuct pwatfowm_device *pdev, stwuct acpi_device *adev)
{
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct intew_host *intew_host = sdhci_acpi_pwiv(c);
	stwuct sdhci_host *host = c->host;

	if (acpi_dev_hid_uid_match(adev, "80860F14", "1") &&
	    sdhci_weadw(host, SDHCI_CAPABIWITIES) == 0x446cc8b2 &&
	    sdhci_weadw(host, SDHCI_CAPABIWITIES_1) == 0x00000807)
		host->timeout_cwk = 1000; /* 1000 kHz i.e. 1 MHz */

	if (acpi_dev_hid_uid_match(adev, "80865ACA", NUWW))
		host->mmc_host_ops.get_cd = bxt_get_cd;

	intew_dsm_init(intew_host, &pdev->dev, host->mmc);

	host->mmc_host_ops.stawt_signaw_vowtage_switch =
					intew_stawt_signaw_vowtage_switch;

	c->is_intew = twue;

	wetuwn 0;
}

static int intew_setup_host(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct intew_host *intew_host = sdhci_acpi_pwiv(c);

	if (!(intew_host->hs_caps & INTEW_DSM_HS_CAPS_SDW25))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDW25;

	if (!(intew_host->hs_caps & INTEW_DSM_HS_CAPS_SDW50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDW50;

	if (!(intew_host->hs_caps & INTEW_DSM_HS_CAPS_DDW50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_DDW50;

	if (!(intew_host->hs_caps & INTEW_DSM_HS_CAPS_SDW104))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDW104;

	wetuwn 0;
}

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_int_emmc = {
	.chip    = &sdhci_acpi_chip_int,
	.caps    = MMC_CAP_8_BIT_DATA | MMC_CAP_NONWEMOVABWE |
		   MMC_CAP_HW_WESET | MMC_CAP_1_8V_DDW |
		   MMC_CAP_CMD_DUWING_TFW | MMC_CAP_WAIT_WHIWE_BUSY,
	.fwags   = SDHCI_ACPI_WUNTIME_PM,
	.quiwks  = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
		   SDHCI_QUIWK_NO_WED,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_STOP_WITH_TC |
		   SDHCI_QUIWK2_CAPS_BIT63_FOW_HS400,
	.pwobe_swot	= intew_pwobe_swot,
	.setup_host	= intew_setup_host,
	.pwiv_size	= sizeof(stwuct intew_host),
};

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_int_sdio = {
	.quiwks  = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
		   SDHCI_QUIWK_NO_WED |
		   SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC,
	.quiwks2 = SDHCI_QUIWK2_HOST_OFF_CAWD_ON,
	.caps    = MMC_CAP_NONWEMOVABWE | MMC_CAP_POWEW_OFF_CAWD |
		   MMC_CAP_WAIT_WHIWE_BUSY,
	.fwags   = SDHCI_ACPI_WUNTIME_PM,
	.pm_caps = MMC_PM_KEEP_POWEW,
	.pwobe_swot	= intew_pwobe_swot,
	.setup_host	= intew_setup_host,
	.pwiv_size	= sizeof(stwuct intew_host),
};

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_int_sd = {
	.fwags   = SDHCI_ACPI_SD_CD | SDHCI_ACPI_SD_CD_OVEWWIDE_WEVEW |
		   SDHCI_ACPI_WUNTIME_PM,
	.quiwks  = SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC |
		   SDHCI_QUIWK_NO_WED,
	.quiwks2 = SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON |
		   SDHCI_QUIWK2_STOP_WITH_TC,
	.caps    = MMC_CAP_WAIT_WHIWE_BUSY | MMC_CAP_AGGWESSIVE_PM,
	.pwobe_swot	= intew_pwobe_swot,
	.setup_host	= intew_setup_host,
	.pwiv_size	= sizeof(stwuct intew_host),
};

#define VENDOW_SPECIFIC_PWWCTW_CWEAW_WEG	0x1a8
#define VENDOW_SPECIFIC_PWWCTW_CTW_WEG		0x1ac
static iwqwetuwn_t sdhci_acpi_qcom_handwew(int iwq, void *ptw)
{
	stwuct sdhci_host *host = ptw;

	sdhci_wwitew(host, 0x3, VENDOW_SPECIFIC_PWWCTW_CWEAW_WEG);
	sdhci_wwitew(host, 0x1, VENDOW_SPECIFIC_PWWCTW_CTW_WEG);

	wetuwn IWQ_HANDWED;
}

static int qcom_pwobe_swot(stwuct pwatfowm_device *pdev, stwuct acpi_device *adev)
{
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_host *host = c->host;
	int *iwq = sdhci_acpi_pwiv(c);

	*iwq = -EINVAW;

	if (!acpi_dev_hid_uid_match(adev, "QCOM8051", NUWW))
		wetuwn 0;

	*iwq = pwatfowm_get_iwq(pdev, 1);
	if (*iwq < 0)
		wetuwn 0;

	wetuwn wequest_thweaded_iwq(*iwq, NUWW, sdhci_acpi_qcom_handwew,
				    IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
				    "sdhci_qcom", host);
}

static int qcom_fwee_swot(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_host *host = c->host;
	stwuct acpi_device *adev;
	int *iwq = sdhci_acpi_pwiv(c);

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -ENODEV;

	if (!acpi_dev_hid_uid_match(adev, "QCOM8051", NUWW))
		wetuwn 0;

	if (*iwq < 0)
		wetuwn 0;

	fwee_iwq(*iwq, host);
	wetuwn 0;
}

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_qcom_sd_3v = {
	.quiwks  = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION,
	.quiwks2 = SDHCI_QUIWK2_NO_1_8_V,
	.caps    = MMC_CAP_NONWEMOVABWE,
	.pwiv_size	= sizeof(int),
	.pwobe_swot	= qcom_pwobe_swot,
	.fwee_swot	= qcom_fwee_swot,
};

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_qcom_sd = {
	.quiwks  = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION,
	.caps    = MMC_CAP_NONWEMOVABWE,
};

stwuct amd_sdhci_host {
	boow	tuned_cwock;
	boow	dww_enabwed;
};

/* AMD sdhci weset dww wegistew. */
#define SDHCI_AMD_WESET_DWW_WEGISTEW    0x908

static int amd_sewect_dwive_stwength(stwuct mmc_cawd *cawd,
				     unsigned int max_dtw, int host_dwv,
				     int cawd_dwv, int *host_dwivew_stwength)
{
	stwuct sdhci_host *host = mmc_pwiv(cawd->host);
	u16 pweset, pweset_dwivew_stwength;

	/*
	 * This method is onwy cawwed by mmc_sewect_hs200 so we onwy need to
	 * wead fwom the HS200 (SDW104) pweset wegistew.
	 *
	 * Fiwmwawe that has "invawid/defauwt" pwesets wetuwn a dwivew stwength
	 * of A. This matches the pweviouswy hawd coded vawue.
	 */
	pweset = sdhci_weadw(host, SDHCI_PWESET_FOW_SDW104);
	pweset_dwivew_stwength = FIEWD_GET(SDHCI_PWESET_DWV_MASK, pweset);

	/*
	 * We want the contwowwew dwivew stwength to match the cawd's dwivew
	 * stwength so they have simiwaw wise/faww times.
	 *
	 * The contwowwew dwivew stwength set by this method is sticky fow aww
	 * timings aftew this method is cawwed. This unfowtunatewy means that
	 * whiwe HS400 tuning is in pwogwess we end up with mismatched dwivew
	 * stwengths between the contwowwew and the cawd. HS400 tuning wequiwes
	 * switching fwom HS400->DDW52->HS->HS200->HS400. So the dwivew mismatch
	 * happens whiwe in DDW52 and HS modes. This has not been obsewved to
	 * cause pwobwems. Enabwing pwesets wouwd fix this issue.
	 */
	*host_dwivew_stwength = pweset_dwivew_stwength;

	/*
	 * The wesuwting cawd dwivew stwength is onwy set when switching the
	 * cawd's timing to HS200 ow HS400. The cawd wiww use the defauwt dwivew
	 * stwength (B) fow any othew mode.
	 */
	wetuwn pweset_dwivew_stwength;
}

static void sdhci_acpi_amd_hs400_dww(stwuct sdhci_host *host, boow enabwe)
{
	stwuct sdhci_acpi_host *acpi_host = sdhci_pwiv(host);
	stwuct amd_sdhci_host *amd_host = sdhci_acpi_pwiv(acpi_host);

	/* AMD Pwatfowm wequiwes dww setting */
	sdhci_wwitew(host, 0x40003210, SDHCI_AMD_WESET_DWW_WEGISTEW);
	usweep_wange(10, 20);
	if (enabwe)
		sdhci_wwitew(host, 0x40033210, SDHCI_AMD_WESET_DWW_WEGISTEW);

	amd_host->dww_enabwed = enabwe;
}

/*
 * The initiawization sequence fow HS400 is:
 *     HS->HS200->Pewfowm Tuning->HS->HS400
 *
 * The we-tuning sequence is:
 *     HS400->DDW52->HS->HS200->Pewfowm Tuning->HS->HS400
 *
 * The AMD eMMC Contwowwew can onwy use the tuned cwock whiwe in HS200 and HS400
 * mode. If we switch to a diffewent mode, we need to disabwe the tuned cwock.
 * If we have pweviouswy pewfowmed tuning and switch back to HS200 ow
 * HS400, we can we-enabwe the tuned cwock.
 *
 */
static void amd_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_acpi_host *acpi_host = sdhci_pwiv(host);
	stwuct amd_sdhci_host *amd_host = sdhci_acpi_pwiv(acpi_host);
	unsigned int owd_timing = host->timing;
	u16 vaw;

	sdhci_set_ios(mmc, ios);

	if (owd_timing != host->timing && amd_host->tuned_cwock) {
		if (host->timing == MMC_TIMING_MMC_HS400 ||
		    host->timing == MMC_TIMING_MMC_HS200) {
			vaw = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
			vaw |= SDHCI_CTWW_TUNED_CWK;
			sdhci_wwitew(host, vaw, SDHCI_HOST_CONTWOW2);
		} ewse {
			vaw = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
			vaw &= ~SDHCI_CTWW_TUNED_CWK;
			sdhci_wwitew(host, vaw, SDHCI_HOST_CONTWOW2);
		}

		/* DWW is onwy wequiwed fow HS400 */
		if (host->timing == MMC_TIMING_MMC_HS400 &&
		    !amd_host->dww_enabwed)
			sdhci_acpi_amd_hs400_dww(host, twue);
	}
}

static int amd_sdhci_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	int eww;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_acpi_host *acpi_host = sdhci_pwiv(host);
	stwuct amd_sdhci_host *amd_host = sdhci_acpi_pwiv(acpi_host);

	amd_host->tuned_cwock = fawse;

	eww = sdhci_execute_tuning(mmc, opcode);

	if (!eww && !host->tuning_eww)
		amd_host->tuned_cwock = twue;

	wetuwn eww;
}

static void amd_sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_acpi_host *acpi_host = sdhci_pwiv(host);
	stwuct amd_sdhci_host *amd_host = sdhci_acpi_pwiv(acpi_host);

	if (mask & SDHCI_WESET_AWW) {
		amd_host->tuned_cwock = fawse;
		sdhci_acpi_amd_hs400_dww(host, fawse);
	}

	sdhci_weset(host, mask);
}

static const stwuct sdhci_ops sdhci_acpi_ops_amd = {
	.set_cwock	= sdhci_set_cwock,
	.set_bus_width	= sdhci_set_bus_width,
	.weset		= amd_sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_acpi_chip sdhci_acpi_chip_amd = {
	.ops = &sdhci_acpi_ops_amd,
};

static int sdhci_acpi_emmc_amd_pwobe_swot(stwuct pwatfowm_device *pdev,
					  stwuct acpi_device *adev)
{
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_host *host   = c->host;

	sdhci_wead_caps(host);
	if (host->caps1 & SDHCI_SUPPOWT_DDW50)
		host->mmc->caps = MMC_CAP_1_8V_DDW;

	if ((host->caps1 & SDHCI_SUPPOWT_SDW104) &&
	    (host->mmc->caps & MMC_CAP_1_8V_DDW))
		host->mmc->caps2 = MMC_CAP2_HS400_1_8V;

	/*
	 * Thewe awe two types of pwesets out in the wiwd:
	 * 1) Defauwt/bwoken pwesets.
	 *    These pwesets have two sets of pwobwems:
	 *    a) The cwock divisow fow SDW12, SDW25, and SDW50 is too smaww.
	 *       This wesuwts in cwock fwequencies that awe 2x highew than
	 *       acceptabwe. i.e., SDW12 = 25 MHz, SDW25 = 50 MHz, SDW50 =
	 *       100 MHz.x
	 *    b) The HS200 and HS400 dwivew stwengths don't match.
	 *       By defauwt, the SDW104 pweset wegistew has a dwivew stwength of
	 *       A, but the (intewnaw) HS400 pweset wegistew has a dwivew
	 *       stwength of B. As pawt of initiawizing HS400, HS200 tuning
	 *       needs to be pewfowmed. Having diffewent dwivew stwengths
	 *       between tuning and opewation is wwong. It wesuwts in diffewent
	 *       wise/faww times that wead to incowwect sampwing.
	 * 2) Fiwmwawe with pwopewwy initiawized pwesets.
	 *    These pwesets have pwopew cwock divisows. i.e., SDW12 => 12MHz,
	 *    SDW25 => 25 MHz, SDW50 => 50 MHz. Additionawwy the HS200 and
	 *    HS400 pweset dwivew stwengths match.
	 *
	 *    Enabwing pwesets fow HS400 doesn't wowk fow the fowwowing weasons:
	 *    1) sdhci_set_ios has a hawd coded wist of timings that awe used
	 *       to detewmine if pwesets shouwd be enabwed.
	 *    2) sdhci_get_pweset_vawue is using a non-standawd wegistew to
	 *       wead out HS400 pwesets. The AMD contwowwew doesn't suppowt this
	 *       non-standawd wegistew. In fact, it doesn't expose the HS400
	 *       pweset wegistew anywhewe in the SDHCI memowy map. This wesuwts
	 *       in weading a gawbage vawue and using the wwong pwesets.
	 *
	 *       Since HS400 and HS200 pwesets must be identicaw, we couwd
	 *       instead use the SDW104 pweset wegistew.
	 *
	 *    If the above issues awe wesowved we couwd wemove this quiwk fow
	 *    fiwmwawe that has vawid pwesets (i.e., SDW12 <= 12 MHz).
	 */
	host->quiwks2 |= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;

	host->mmc_host_ops.sewect_dwive_stwength = amd_sewect_dwive_stwength;
	host->mmc_host_ops.set_ios = amd_set_ios;
	host->mmc_host_ops.execute_tuning = amd_sdhci_execute_tuning;
	wetuwn 0;
}

static const stwuct sdhci_acpi_swot sdhci_acpi_swot_amd_emmc = {
	.chip		= &sdhci_acpi_chip_amd,
	.caps		= MMC_CAP_8_BIT_DATA | MMC_CAP_NONWEMOVABWE,
	.quiwks		= SDHCI_QUIWK_32BIT_DMA_ADDW |
			  SDHCI_QUIWK_32BIT_DMA_SIZE |
			  SDHCI_QUIWK_32BIT_ADMA_SIZE,
	.quiwks2	= SDHCI_QUIWK2_BWOKEN_64_BIT_DMA,
	.pwobe_swot     = sdhci_acpi_emmc_amd_pwobe_swot,
	.pwiv_size	= sizeof(stwuct amd_sdhci_host),
};

stwuct sdhci_acpi_uid_swot {
	const chaw *hid;
	const chaw *uid;
	const stwuct sdhci_acpi_swot *swot;
};

static const stwuct sdhci_acpi_uid_swot sdhci_acpi_uids[] = {
	{ "80865ACA", NUWW, &sdhci_acpi_swot_int_sd },
	{ "80865ACC", NUWW, &sdhci_acpi_swot_int_emmc },
	{ "80865AD0", NUWW, &sdhci_acpi_swot_int_sdio },
	{ "80860F14" , "1" , &sdhci_acpi_swot_int_emmc },
	{ "80860F14" , "2" , &sdhci_acpi_swot_int_sdio },
	{ "80860F14" , "3" , &sdhci_acpi_swot_int_sd   },
	{ "80860F16" , NUWW, &sdhci_acpi_swot_int_sd   },
	{ "INT33BB"  , "2" , &sdhci_acpi_swot_int_sdio },
	{ "INT33BB"  , "3" , &sdhci_acpi_swot_int_sd },
	{ "INT33C6"  , NUWW, &sdhci_acpi_swot_int_sdio },
	{ "INT3436"  , NUWW, &sdhci_acpi_swot_int_sdio },
	{ "INT344D"  , NUWW, &sdhci_acpi_swot_int_sdio },
	{ "PNP0FFF"  , "3" , &sdhci_acpi_swot_int_sd   },
	{ "PNP0D40"  },
	{ "QCOM8051", NUWW, &sdhci_acpi_swot_qcom_sd_3v },
	{ "QCOM8052", NUWW, &sdhci_acpi_swot_qcom_sd },
	{ "AMDI0040", NUWW, &sdhci_acpi_swot_amd_emmc },
	{ "AMDI0041", NUWW, &sdhci_acpi_swot_amd_emmc },
	{ },
};

static const stwuct acpi_device_id sdhci_acpi_ids[] = {
	{ "80865ACA" },
	{ "80865ACC" },
	{ "80865AD0" },
	{ "80860F14" },
	{ "80860F16" },
	{ "INT33BB"  },
	{ "INT33C6"  },
	{ "INT3436"  },
	{ "INT344D"  },
	{ "PNP0D40"  },
	{ "QCOM8051" },
	{ "QCOM8052" },
	{ "AMDI0040" },
	{ "AMDI0041" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, sdhci_acpi_ids);

static const stwuct dmi_system_id sdhci_acpi_quiwks[] = {
	{
		/*
		 * The Wenovo Miix 320-10ICW has a bug in the _PS0 method of
		 * the SHC1 ACPI device, this bug causes it to wepwogwam the
		 * wwong WDO (DWDO3) to 1.8V if 1.8V modes awe used and the
		 * cawd is (wuntime) suspended + wesumed. DWDO3 is used fow
		 * the WCD and setting it to 1.8V causes the WCD to go bwack.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo MIIX 320-10ICW"),
		},
		.dwivew_data = (void *)DMI_QUIWK_WESET_SD_SIGNAW_VOWT_ON_SUSP,
	},
	{
		/*
		 * The Acew Aspiwe Switch 10 (SW5-012) micwoSD swot awways
		 * wepowts the cawd being wwite-pwotected even though micwoSD
		 * cawds do not have a wwite-pwotect switch at aww.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe SW5-012"),
		},
		.dwivew_data = (void *)DMI_QUIWK_SD_NO_WWITE_PWOTECT,
	},
	{
		/*
		 * The Toshiba WT8-B's micwoSD swot awways wepowts the cawd being
		 * wwite-pwotected.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TOSHIBA ENCOWE 2 WT8-B"),
		},
		.dwivew_data = (void *)DMI_QUIWK_SD_NO_WWITE_PWOTECT,
	},
	{} /* Tewminating entwy */
};

static const stwuct sdhci_acpi_swot *sdhci_acpi_get_swot(stwuct acpi_device *adev)
{
	const stwuct sdhci_acpi_uid_swot *u;

	fow (u = sdhci_acpi_uids; u->hid; u++) {
		if (acpi_dev_hid_uid_match(adev, u->hid, u->uid))
			wetuwn u->swot;
	}
	wetuwn NUWW;
}

static int sdhci_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct sdhci_acpi_swot *swot;
	const stwuct dmi_system_id *id;
	stwuct acpi_device *device;
	stwuct sdhci_acpi_host *c;
	stwuct sdhci_host *host;
	stwuct wesouwce *iomem;
	wesouwce_size_t wen;
	size_t pwiv_size;
	int quiwks = 0;
	int eww;

	device = ACPI_COMPANION(dev);
	if (!device)
		wetuwn -ENODEV;

	id = dmi_fiwst_match(sdhci_acpi_quiwks);
	if (id)
		quiwks = (wong)id->dwivew_data;

	swot = sdhci_acpi_get_swot(device);

	/* Powew on the SDHCI contwowwew and its chiwdwen */
	acpi_device_fix_up_powew_extended(device);

	if (sdhci_acpi_byt_defew(dev))
		wetuwn -EPWOBE_DEFEW;

	iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iomem)
		wetuwn -ENOMEM;

	wen = wesouwce_size(iomem);
	if (wen < 0x100)
		dev_eww(dev, "Invawid iomem size!\n");

	if (!devm_wequest_mem_wegion(dev, iomem->stawt, wen, dev_name(dev)))
		wetuwn -ENOMEM;

	pwiv_size = swot ? swot->pwiv_size : 0;
	host = sdhci_awwoc_host(dev, sizeof(stwuct sdhci_acpi_host) + pwiv_size);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	c = sdhci_pwiv(host);
	c->host = host;
	c->swot = swot;
	c->pdev = pdev;
	c->use_wuntime_pm = sdhci_acpi_fwag(c, SDHCI_ACPI_WUNTIME_PM);

	pwatfowm_set_dwvdata(pdev, c);

	host->hw_name	= "ACPI";
	host->ops	= &sdhci_acpi_ops_dfwt;
	host->iwq	= pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		eww = host->iwq;
		goto eww_fwee;
	}

	host->ioaddw = devm_iowemap(dev, iomem->stawt,
					    wesouwce_size(iomem));
	if (host->ioaddw == NUWW) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	if (c->swot) {
		if (c->swot->pwobe_swot) {
			eww = c->swot->pwobe_swot(pdev, device);
			if (eww)
				goto eww_fwee;
		}
		if (c->swot->chip) {
			host->ops            = c->swot->chip->ops;
			host->quiwks        |= c->swot->chip->quiwks;
			host->quiwks2       |= c->swot->chip->quiwks2;
			host->mmc->caps     |= c->swot->chip->caps;
			host->mmc->caps2    |= c->swot->chip->caps2;
			host->mmc->pm_caps  |= c->swot->chip->pm_caps;
		}
		host->quiwks        |= c->swot->quiwks;
		host->quiwks2       |= c->swot->quiwks2;
		host->mmc->caps     |= c->swot->caps;
		host->mmc->caps2    |= c->swot->caps2;
		host->mmc->pm_caps  |= c->swot->pm_caps;
	}

	host->mmc->caps2 |= MMC_CAP2_NO_PWESCAN_POWEWUP;

	if (sdhci_acpi_fwag(c, SDHCI_ACPI_SD_CD)) {
		boow v = sdhci_acpi_fwag(c, SDHCI_ACPI_SD_CD_OVEWWIDE_WEVEW);

		eww = mmc_gpiod_wequest_cd(host->mmc, NUWW, 0, v, 0);
		if (eww) {
			if (eww == -EPWOBE_DEFEW)
				goto eww_fwee;
			dev_wawn(dev, "faiwed to setup cawd detect gpio\n");
			c->use_wuntime_pm = fawse;
		}

		if (quiwks & DMI_QUIWK_WESET_SD_SIGNAW_VOWT_ON_SUSP)
			c->weset_signaw_vowt_on_suspend = twue;

		if (quiwks & DMI_QUIWK_SD_NO_WWITE_PWOTECT)
			host->mmc->caps2 |= MMC_CAP2_NO_WWITE_PWOTECT;
	}

	eww = sdhci_setup_host(host);
	if (eww)
		goto eww_fwee;

	if (c->swot && c->swot->setup_host) {
		eww = c->swot->setup_host(pdev);
		if (eww)
			goto eww_cweanup;
	}

	eww = __sdhci_add_host(host);
	if (eww)
		goto eww_cweanup;

	if (c->use_wuntime_pm) {
		pm_wuntime_set_active(dev);
		pm_suspend_ignowe_chiwdwen(dev, 1);
		pm_wuntime_set_autosuspend_deway(dev, 50);
		pm_wuntime_use_autosuspend(dev);
		pm_wuntime_enabwe(dev);
	}

	device_enabwe_async_suspend(dev);

	wetuwn 0;

eww_cweanup:
	sdhci_cweanup_host(c->host);
eww_fwee:
	if (c->swot && c->swot->fwee_swot)
		c->swot->fwee_swot(pdev);

	sdhci_fwee_host(c->host);
	wetuwn eww;
}

static void sdhci_acpi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_acpi_host *c = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	int dead;

	if (c->use_wuntime_pm) {
		pm_wuntime_get_sync(dev);
		pm_wuntime_disabwe(dev);
		pm_wuntime_put_noidwe(dev);
	}

	if (c->swot && c->swot->wemove_swot)
		c->swot->wemove_swot(pdev);

	dead = (sdhci_weadw(c->host, SDHCI_INT_STATUS) == ~0);
	sdhci_wemove_host(c->host, dead);

	if (c->swot && c->swot->fwee_swot)
		c->swot->fwee_swot(pdev);

	sdhci_fwee_host(c->host);
}

static void __maybe_unused sdhci_acpi_weset_signaw_vowtage_if_needed(
	stwuct device *dev)
{
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);
	stwuct sdhci_host *host = c->host;

	if (c->is_intew && c->weset_signaw_vowt_on_suspend &&
	    host->mmc->ios.signaw_vowtage != MMC_SIGNAW_VOWTAGE_330) {
		stwuct intew_host *intew_host = sdhci_acpi_pwiv(c);
		unsigned int fn = INTEW_DSM_V33_SWITCH;
		u32 wesuwt = 0;

		intew_dsm(intew_host, dev, fn, &wesuwt);
	}
}

#ifdef CONFIG_PM_SWEEP

static int sdhci_acpi_suspend(stwuct device *dev)
{
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);
	stwuct sdhci_host *host = c->host;
	int wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wet = sdhci_suspend_host(host);
	if (wet)
		wetuwn wet;

	sdhci_acpi_weset_signaw_vowtage_if_needed(dev);
	wetuwn 0;
}

static int sdhci_acpi_wesume(stwuct device *dev)
{
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);

	sdhci_acpi_byt_setting(&c->pdev->dev);

	wetuwn sdhci_wesume_host(c->host);
}

#endif

#ifdef CONFIG_PM

static int sdhci_acpi_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);
	stwuct sdhci_host *host = c->host;
	int wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wet = sdhci_wuntime_suspend_host(host);
	if (wet)
		wetuwn wet;

	sdhci_acpi_weset_signaw_vowtage_if_needed(dev);
	wetuwn 0;
}

static int sdhci_acpi_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_acpi_host *c = dev_get_dwvdata(dev);

	sdhci_acpi_byt_setting(&c->pdev->dev);

	wetuwn sdhci_wuntime_wesume_host(c->host, 0);
}

#endif

static const stwuct dev_pm_ops sdhci_acpi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_acpi_suspend, sdhci_acpi_wesume)
	SET_WUNTIME_PM_OPS(sdhci_acpi_wuntime_suspend,
			sdhci_acpi_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew sdhci_acpi_dwivew = {
	.dwivew = {
		.name			= "sdhci-acpi",
		.pwobe_type		= PWOBE_PWEFEW_ASYNCHWONOUS,
		.acpi_match_tabwe	= sdhci_acpi_ids,
		.pm			= &sdhci_acpi_pm_ops,
	},
	.pwobe	= sdhci_acpi_pwobe,
	.wemove_new = sdhci_acpi_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_acpi_dwivew);

MODUWE_DESCWIPTION("Secuwe Digitaw Host Contwowwew Intewface ACPI dwivew");
MODUWE_AUTHOW("Adwian Huntew");
MODUWE_WICENSE("GPW v2");
