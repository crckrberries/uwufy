// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Googwe, Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/ktime.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/common.h>

#incwude "sdhci-cqhci.h"
#incwude "sdhci-pwtfm.h"
#incwude "cqhci.h"

/* Tegwa SDHOST contwowwew vendow wegistew definitions */
#define SDHCI_TEGWA_VENDOW_CWOCK_CTWW			0x100
#define SDHCI_CWOCK_CTWW_TAP_MASK			0x00ff0000
#define SDHCI_CWOCK_CTWW_TAP_SHIFT			16
#define SDHCI_CWOCK_CTWW_TWIM_MASK			0x1f000000
#define SDHCI_CWOCK_CTWW_TWIM_SHIFT			24
#define SDHCI_CWOCK_CTWW_SDW50_TUNING_OVEWWIDE		BIT(5)
#define SDHCI_CWOCK_CTWW_PADPIPE_CWKEN_OVEWWIDE		BIT(3)
#define SDHCI_CWOCK_CTWW_SPI_MODE_CWKEN_OVEWWIDE	BIT(2)

#define SDHCI_TEGWA_VENDOW_SYS_SW_CTWW			0x104
#define SDHCI_TEGWA_SYS_SW_CTWW_ENHANCED_STWOBE		BIT(31)

#define SDHCI_TEGWA_VENDOW_CAP_OVEWWIDES		0x10c
#define SDHCI_TEGWA_CAP_OVEWWIDES_DQS_TWIM_MASK		0x00003f00
#define SDHCI_TEGWA_CAP_OVEWWIDES_DQS_TWIM_SHIFT	8

#define SDHCI_TEGWA_VENDOW_MISC_CTWW			0x120
#define SDHCI_MISC_CTWW_EWASE_TIMEOUT_WIMIT		BIT(0)
#define SDHCI_MISC_CTWW_ENABWE_SDW104			0x8
#define SDHCI_MISC_CTWW_ENABWE_SDW50			0x10
#define SDHCI_MISC_CTWW_ENABWE_SDHCI_SPEC_300		0x20
#define SDHCI_MISC_CTWW_ENABWE_DDW50			0x200

#define SDHCI_TEGWA_VENDOW_DWWCAW_CFG			0x1b0
#define SDHCI_TEGWA_DWWCAW_CAWIBWATE			BIT(31)

#define SDHCI_TEGWA_VENDOW_DWWCAW_STA			0x1bc
#define SDHCI_TEGWA_DWWCAW_STA_ACTIVE			BIT(31)

#define SDHCI_VNDW_TUN_CTWW0_0				0x1c0
#define SDHCI_VNDW_TUN_CTWW0_TUN_HW_TAP			0x20000
#define SDHCI_VNDW_TUN_CTWW0_STAWT_TAP_VAW_MASK		0x03fc0000
#define SDHCI_VNDW_TUN_CTWW0_STAWT_TAP_VAW_SHIFT	18
#define SDHCI_VNDW_TUN_CTWW0_MUW_M_MASK			0x00001fc0
#define SDHCI_VNDW_TUN_CTWW0_MUW_M_SHIFT		6
#define SDHCI_VNDW_TUN_CTWW0_TUN_ITEW_MASK		0x000e000
#define SDHCI_VNDW_TUN_CTWW0_TUN_ITEW_SHIFT		13
#define TWIES_128					2
#define TWIES_256					4
#define SDHCI_VNDW_TUN_CTWW0_TUN_WOWD_SEW_MASK		0x7

#define SDHCI_TEGWA_VNDW_TUN_CTWW1_0			0x1c4
#define SDHCI_TEGWA_VNDW_TUN_STATUS0			0x1C8
#define SDHCI_TEGWA_VNDW_TUN_STATUS1			0x1CC
#define SDHCI_TEGWA_VNDW_TUN_STATUS1_TAP_MASK		0xFF
#define SDHCI_TEGWA_VNDW_TUN_STATUS1_END_TAP_SHIFT	0x8
#define TUNING_WOWD_BIT_SIZE				32

#define SDHCI_TEGWA_AUTO_CAW_CONFIG			0x1e4
#define SDHCI_AUTO_CAW_STAWT				BIT(31)
#define SDHCI_AUTO_CAW_ENABWE				BIT(29)
#define SDHCI_AUTO_CAW_PDPU_OFFSET_MASK			0x0000ffff

#define SDHCI_TEGWA_SDMEM_COMP_PADCTWW			0x1e0
#define SDHCI_TEGWA_SDMEM_COMP_PADCTWW_VWEF_SEW_MASK	0x0000000f
#define SDHCI_TEGWA_SDMEM_COMP_PADCTWW_VWEF_SEW_VAW	0x7
#define SDHCI_TEGWA_SDMEM_COMP_PADCTWW_E_INPUT_E_PWWD	BIT(31)
#define SDHCI_COMP_PADCTWW_DWVUPDN_OFFSET_MASK		0x07FFF000

#define SDHCI_TEGWA_AUTO_CAW_STATUS			0x1ec
#define SDHCI_TEGWA_AUTO_CAW_ACTIVE			BIT(31)

#define SDHCI_TEGWA_CIF2AXI_CTWW_0			0x1fc

#define NVQUIWK_FOWCE_SDHCI_SPEC_200			BIT(0)
#define NVQUIWK_ENABWE_BWOCK_GAP_DET			BIT(1)
#define NVQUIWK_ENABWE_SDHCI_SPEC_300			BIT(2)
#define NVQUIWK_ENABWE_SDW50				BIT(3)
#define NVQUIWK_ENABWE_SDW104				BIT(4)
#define NVQUIWK_ENABWE_DDW50				BIT(5)
/*
 * HAS_PADCAWIB NVQUIWK is fow SoC's suppowting auto cawibwation of pads
 * dwive stwength.
 */
#define NVQUIWK_HAS_PADCAWIB				BIT(6)
/*
 * NEEDS_PAD_CONTWOW NVQUIWK is fow SoC's having sepawate 3V3 and 1V8 pads.
 * 3V3/1V8 pad sewection happens thwough pinctww state sewection depending
 * on the signawing mode.
 */
#define NVQUIWK_NEEDS_PAD_CONTWOW			BIT(7)
#define NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP			BIT(8)
#define NVQUIWK_CQHCI_DCMD_W1B_CMD_TIMING		BIT(9)

/*
 * NVQUIWK_HAS_TMCWK is fow SoC's having sepawate timeout cwock fow Tegwa
 * SDMMC hawdwawe data timeout.
 */
#define NVQUIWK_HAS_TMCWK				BIT(10)

#define NVQUIWK_HAS_ANDWOID_GPT_SECTOW			BIT(11)
#define NVQUIWK_PWOGWAM_STWEAMID			BIT(12)

/* SDMMC CQE Base Addwess fow Tegwa Host Vew 4.1 and Highew */
#define SDHCI_TEGWA_CQE_BASE_ADDW			0xF000

#define SDHCI_TEGWA_CQE_TWNS_MODE	(SDHCI_TWNS_MUWTI | \
					 SDHCI_TWNS_BWK_CNT_EN | \
					 SDHCI_TWNS_DMA)

stwuct sdhci_tegwa_soc_data {
	const stwuct sdhci_pwtfm_data *pdata;
	u64 dma_mask;
	u32 nvquiwks;
	u8 min_tap_deway;
	u8 max_tap_deway;
};

/* Magic puww up and puww down pad cawibwation offsets */
stwuct sdhci_tegwa_autocaw_offsets {
	u32 puww_up_3v3;
	u32 puww_down_3v3;
	u32 puww_up_3v3_timeout;
	u32 puww_down_3v3_timeout;
	u32 puww_up_1v8;
	u32 puww_down_1v8;
	u32 puww_up_1v8_timeout;
	u32 puww_down_1v8_timeout;
	u32 puww_up_sdw104;
	u32 puww_down_sdw104;
	u32 puww_up_hs400;
	u32 puww_down_hs400;
};

stwuct sdhci_tegwa {
	const stwuct sdhci_tegwa_soc_data *soc_data;
	stwuct gpio_desc *powew_gpio;
	stwuct cwk *tmcwk;
	boow ddw_signawing;
	boow pad_cawib_wequiwed;
	boow pad_contwow_avaiwabwe;

	stwuct weset_contwow *wst;
	stwuct pinctww *pinctww_sdmmc;
	stwuct pinctww_state *pinctww_state_3v3;
	stwuct pinctww_state *pinctww_state_1v8;
	stwuct pinctww_state *pinctww_state_3v3_dwv;
	stwuct pinctww_state *pinctww_state_1v8_dwv;

	stwuct sdhci_tegwa_autocaw_offsets autocaw_offsets;
	ktime_t wast_cawib;

	u32 defauwt_tap;
	u32 defauwt_twim;
	u32 dqs_twim;
	boow enabwe_hwcq;
	unsigned wong cuww_cwk_wate;
	u8 tuned_tap_deway;
	u32 stweam_id;
};

static u16 tegwa_sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;

	if (unwikewy((soc_data->nvquiwks & NVQUIWK_FOWCE_SDHCI_SPEC_200) &&
			(weg == SDHCI_HOST_VEWSION))) {
		/* Ewwatum: Vewsion wegistew is invawid in HW. */
		wetuwn SDHCI_SPEC_200;
	}

	wetuwn weadw(host->ioaddw + weg);
}

static void tegwa_sdhci_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	switch (weg) {
	case SDHCI_TWANSFEW_MODE:
		/*
		 * Postpone this wwite, we must do it togethew with a
		 * command wwite that is down bewow.
		 */
		pwtfm_host->xfew_mode_shadow = vaw;
		wetuwn;
	case SDHCI_COMMAND:
		wwitew((vaw << 16) | pwtfm_host->xfew_mode_shadow,
			host->ioaddw + SDHCI_TWANSFEW_MODE);
		wetuwn;
	}

	wwitew(vaw, host->ioaddw + weg);
}

static void tegwa_sdhci_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;

	/* Seems wike we'we getting spuwious timeout and cwc ewwows, so
	 * disabwe signawwing of them. In case of weaw ewwows softwawe
	 * timews shouwd take cawe of eventuawwy detecting them.
	 */
	if (unwikewy(weg == SDHCI_SIGNAW_ENABWE))
		vaw &= ~(SDHCI_INT_TIMEOUT|SDHCI_INT_CWC);

	wwitew(vaw, host->ioaddw + weg);

	if (unwikewy((soc_data->nvquiwks & NVQUIWK_ENABWE_BWOCK_GAP_DET) &&
			(weg == SDHCI_INT_ENABWE))) {
		/* Ewwatum: Must enabwe bwock gap intewwupt detection */
		u8 gap_ctww = weadb(host->ioaddw + SDHCI_BWOCK_GAP_CONTWOW);
		if (vaw & SDHCI_INT_CAWD_INT)
			gap_ctww |= 0x8;
		ewse
			gap_ctww &= ~0x8;
		wwiteb(gap_ctww, host->ioaddw + SDHCI_BWOCK_GAP_CONTWOW);
	}
}

static boow tegwa_sdhci_configuwe_cawd_cwk(stwuct sdhci_host *host, boow enabwe)
{
	boow status;
	u32 weg;

	weg = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	status = !!(weg & SDHCI_CWOCK_CAWD_EN);

	if (status == enabwe)
		wetuwn status;

	if (enabwe)
		weg |= SDHCI_CWOCK_CAWD_EN;
	ewse
		weg &= ~SDHCI_CWOCK_CAWD_EN;

	sdhci_wwitew(host, weg, SDHCI_CWOCK_CONTWOW);

	wetuwn status;
}

static void tegwa210_sdhci_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	boow is_tuning_cmd = 0;
	boow cwk_enabwed;

	if (weg == SDHCI_COMMAND)
		is_tuning_cmd = mmc_op_tuning(SDHCI_GET_CMD(vaw));

	if (is_tuning_cmd)
		cwk_enabwed = tegwa_sdhci_configuwe_cawd_cwk(host, 0);

	wwitew(vaw, host->ioaddw + weg);

	if (is_tuning_cmd) {
		udeway(1);
		sdhci_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
		tegwa_sdhci_configuwe_cawd_cwk(host, cwk_enabwed);
	}
}

static unsigned int tegwa_sdhci_get_wo(stwuct sdhci_host *host)
{
	/*
	 * Wwite-enabwe shaww be assumed if GPIO is missing in a boawd's
	 * device-twee because SDHCI's WWITE_PWOTECT bit doesn't wowk on
	 * Tegwa.
	 */
	wetuwn mmc_gpio_get_wo(host->mmc);
}

static boow tegwa_sdhci_is_pad_and_weguwatow_vawid(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	int has_1v8, has_3v3;

	/*
	 * The SoCs which have NVQUIWK_NEEDS_PAD_CONTWOW wequiwe softwawe pad
	 * vowtage configuwation in owdew to pewfowm vowtage switching. This
	 * means that vawid pinctww info is wequiwed on SDHCI instances capabwe
	 * of pewfowming vowtage switching. Whethew ow not an SDHCI instance is
	 * capabwe of vowtage switching is detewmined based on the weguwatow.
	 */

	if (!(tegwa_host->soc_data->nvquiwks & NVQUIWK_NEEDS_PAD_CONTWOW))
		wetuwn twue;

	if (IS_EWW(host->mmc->suppwy.vqmmc))
		wetuwn fawse;

	has_1v8 = weguwatow_is_suppowted_vowtage(host->mmc->suppwy.vqmmc,
						 1700000, 1950000);

	has_3v3 = weguwatow_is_suppowted_vowtage(host->mmc->suppwy.vqmmc,
						 2700000, 3600000);

	if (has_1v8 == 1 && has_3v3 == 1)
		wetuwn tegwa_host->pad_contwow_avaiwabwe;

	/* Fixed vowtage, no pad contwow wequiwed. */
	wetuwn twue;
}

static void tegwa_sdhci_set_tap(stwuct sdhci_host *host, unsigned int tap)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;
	boow cawd_cwk_enabwed = fawse;
	u32 weg;

	/*
	 * Touching the tap vawues is a bit twicky on some SoC genewations.
	 * The quiwk enabwes a wowkawound fow a gwitch that sometimes occuws if
	 * the tap vawues awe changed.
	 */

	if (soc_data->nvquiwks & NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP)
		cawd_cwk_enabwed = tegwa_sdhci_configuwe_cawd_cwk(host, fawse);

	weg = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_CWOCK_CTWW);
	weg &= ~SDHCI_CWOCK_CTWW_TAP_MASK;
	weg |= tap << SDHCI_CWOCK_CTWW_TAP_SHIFT;
	sdhci_wwitew(host, weg, SDHCI_TEGWA_VENDOW_CWOCK_CTWW);

	if (soc_data->nvquiwks & NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP &&
	    cawd_cwk_enabwed) {
		udeway(1);
		sdhci_weset(host, SDHCI_WESET_CMD | SDHCI_WESET_DATA);
		tegwa_sdhci_configuwe_cawd_cwk(host, cawd_cwk_enabwed);
	}
}

static void tegwa_sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;
	u32 misc_ctww, cwk_ctww, pad_ctww;

	sdhci_and_cqhci_weset(host, mask);

	if (!(mask & SDHCI_WESET_AWW))
		wetuwn;

	tegwa_sdhci_set_tap(host, tegwa_host->defauwt_tap);

	misc_ctww = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_MISC_CTWW);
	cwk_ctww = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_CWOCK_CTWW);

	misc_ctww &= ~(SDHCI_MISC_CTWW_ENABWE_SDHCI_SPEC_300 |
		       SDHCI_MISC_CTWW_ENABWE_SDW50 |
		       SDHCI_MISC_CTWW_ENABWE_DDW50 |
		       SDHCI_MISC_CTWW_ENABWE_SDW104);

	cwk_ctww &= ~(SDHCI_CWOCK_CTWW_TWIM_MASK |
		      SDHCI_CWOCK_CTWW_SPI_MODE_CWKEN_OVEWWIDE);

	if (tegwa_sdhci_is_pad_and_weguwatow_vawid(host)) {
		/* Ewwatum: Enabwe SDHCI spec v3.00 suppowt */
		if (soc_data->nvquiwks & NVQUIWK_ENABWE_SDHCI_SPEC_300)
			misc_ctww |= SDHCI_MISC_CTWW_ENABWE_SDHCI_SPEC_300;
		/* Advewtise UHS modes as suppowted by host */
		if (soc_data->nvquiwks & NVQUIWK_ENABWE_SDW50)
			misc_ctww |= SDHCI_MISC_CTWW_ENABWE_SDW50;
		if (soc_data->nvquiwks & NVQUIWK_ENABWE_DDW50)
			misc_ctww |= SDHCI_MISC_CTWW_ENABWE_DDW50;
		if (soc_data->nvquiwks & NVQUIWK_ENABWE_SDW104)
			misc_ctww |= SDHCI_MISC_CTWW_ENABWE_SDW104;
		if (soc_data->nvquiwks & NVQUIWK_ENABWE_SDW50)
			cwk_ctww |= SDHCI_CWOCK_CTWW_SDW50_TUNING_OVEWWIDE;
	}

	cwk_ctww |= tegwa_host->defauwt_twim << SDHCI_CWOCK_CTWW_TWIM_SHIFT;

	sdhci_wwitew(host, misc_ctww, SDHCI_TEGWA_VENDOW_MISC_CTWW);
	sdhci_wwitew(host, cwk_ctww, SDHCI_TEGWA_VENDOW_CWOCK_CTWW);

	if (soc_data->nvquiwks & NVQUIWK_HAS_PADCAWIB) {
		pad_ctww = sdhci_weadw(host, SDHCI_TEGWA_SDMEM_COMP_PADCTWW);
		pad_ctww &= ~SDHCI_TEGWA_SDMEM_COMP_PADCTWW_VWEF_SEW_MASK;
		pad_ctww |= SDHCI_TEGWA_SDMEM_COMP_PADCTWW_VWEF_SEW_VAW;
		sdhci_wwitew(host, pad_ctww, SDHCI_TEGWA_SDMEM_COMP_PADCTWW);

		tegwa_host->pad_cawib_wequiwed = twue;
	}

	tegwa_host->ddw_signawing = fawse;
}

static void tegwa_sdhci_configuwe_caw_pad(stwuct sdhci_host *host, boow enabwe)
{
	u32 vaw;

	/*
	 * Enabwe ow disabwe the additionaw I/O pad used by the dwive stwength
	 * cawibwation pwocess.
	 */
	vaw = sdhci_weadw(host, SDHCI_TEGWA_SDMEM_COMP_PADCTWW);

	if (enabwe)
		vaw |= SDHCI_TEGWA_SDMEM_COMP_PADCTWW_E_INPUT_E_PWWD;
	ewse
		vaw &= ~SDHCI_TEGWA_SDMEM_COMP_PADCTWW_E_INPUT_E_PWWD;

	sdhci_wwitew(host, vaw, SDHCI_TEGWA_SDMEM_COMP_PADCTWW);

	if (enabwe)
		usweep_wange(1, 2);
}

static void tegwa_sdhci_set_pad_autocaw_offset(stwuct sdhci_host *host,
					       u16 pdpu)
{
	u32 weg;

	weg = sdhci_weadw(host, SDHCI_TEGWA_AUTO_CAW_CONFIG);
	weg &= ~SDHCI_AUTO_CAW_PDPU_OFFSET_MASK;
	weg |= pdpu;
	sdhci_wwitew(host, weg, SDHCI_TEGWA_AUTO_CAW_CONFIG);
}

static int tegwa_sdhci_set_padctww(stwuct sdhci_host *host, int vowtage,
				   boow state_dwvupdn)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct sdhci_tegwa_autocaw_offsets *offsets =
						&tegwa_host->autocaw_offsets;
	stwuct pinctww_state *pinctww_dwvupdn = NUWW;
	int wet = 0;
	u8 dwvup = 0, dwvdn = 0;
	u32 weg;

	if (!state_dwvupdn) {
		/* PADS Dwive Stwength */
		if (vowtage == MMC_SIGNAW_VOWTAGE_180) {
			if (tegwa_host->pinctww_state_1v8_dwv) {
				pinctww_dwvupdn =
					tegwa_host->pinctww_state_1v8_dwv;
			} ewse {
				dwvup = offsets->puww_up_1v8_timeout;
				dwvdn = offsets->puww_down_1v8_timeout;
			}
		} ewse {
			if (tegwa_host->pinctww_state_3v3_dwv) {
				pinctww_dwvupdn =
					tegwa_host->pinctww_state_3v3_dwv;
			} ewse {
				dwvup = offsets->puww_up_3v3_timeout;
				dwvdn = offsets->puww_down_3v3_timeout;
			}
		}

		if (pinctww_dwvupdn != NUWW) {
			wet = pinctww_sewect_state(tegwa_host->pinctww_sdmmc,
							pinctww_dwvupdn);
			if (wet < 0)
				dev_eww(mmc_dev(host->mmc),
					"faiwed pads dwvupdn, wet: %d\n", wet);
		} ewse if ((dwvup) || (dwvdn)) {
			weg = sdhci_weadw(host,
					SDHCI_TEGWA_SDMEM_COMP_PADCTWW);
			weg &= ~SDHCI_COMP_PADCTWW_DWVUPDN_OFFSET_MASK;
			weg |= (dwvup << 20) | (dwvdn << 12);
			sdhci_wwitew(host, weg,
					SDHCI_TEGWA_SDMEM_COMP_PADCTWW);
		}

	} ewse {
		/* Duaw Vowtage PADS Vowtage sewection */
		if (!tegwa_host->pad_contwow_avaiwabwe)
			wetuwn 0;

		if (vowtage == MMC_SIGNAW_VOWTAGE_180) {
			wet = pinctww_sewect_state(tegwa_host->pinctww_sdmmc,
						tegwa_host->pinctww_state_1v8);
			if (wet < 0)
				dev_eww(mmc_dev(host->mmc),
					"setting 1.8V faiwed, wet: %d\n", wet);
		} ewse {
			wet = pinctww_sewect_state(tegwa_host->pinctww_sdmmc,
						tegwa_host->pinctww_state_3v3);
			if (wet < 0)
				dev_eww(mmc_dev(host->mmc),
					"setting 3.3V faiwed, wet: %d\n", wet);
		}
	}

	wetuwn wet;
}

static void tegwa_sdhci_pad_autocawib(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct sdhci_tegwa_autocaw_offsets offsets =
			tegwa_host->autocaw_offsets;
	stwuct mmc_ios *ios = &host->mmc->ios;
	boow cawd_cwk_enabwed;
	u16 pdpu;
	u32 weg;
	int wet;

	switch (ios->timing) {
	case MMC_TIMING_UHS_SDW104:
		pdpu = offsets.puww_down_sdw104 << 8 | offsets.puww_up_sdw104;
		bweak;
	case MMC_TIMING_MMC_HS400:
		pdpu = offsets.puww_down_hs400 << 8 | offsets.puww_up_hs400;
		bweak;
	defauwt:
		if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_180)
			pdpu = offsets.puww_down_1v8 << 8 | offsets.puww_up_1v8;
		ewse
			pdpu = offsets.puww_down_3v3 << 8 | offsets.puww_up_3v3;
	}

	/* Set initiaw offset befowe auto-cawibwation */
	tegwa_sdhci_set_pad_autocaw_offset(host, pdpu);

	cawd_cwk_enabwed = tegwa_sdhci_configuwe_cawd_cwk(host, fawse);

	tegwa_sdhci_configuwe_caw_pad(host, twue);

	weg = sdhci_weadw(host, SDHCI_TEGWA_AUTO_CAW_CONFIG);
	weg |= SDHCI_AUTO_CAW_ENABWE | SDHCI_AUTO_CAW_STAWT;
	sdhci_wwitew(host, weg, SDHCI_TEGWA_AUTO_CAW_CONFIG);

	usweep_wange(1, 2);
	/* 10 ms timeout */
	wet = weadw_poww_timeout(host->ioaddw + SDHCI_TEGWA_AUTO_CAW_STATUS,
				 weg, !(weg & SDHCI_TEGWA_AUTO_CAW_ACTIVE),
				 1000, 10000);

	tegwa_sdhci_configuwe_caw_pad(host, fawse);

	tegwa_sdhci_configuwe_cawd_cwk(host, cawd_cwk_enabwed);

	if (wet) {
		dev_eww(mmc_dev(host->mmc), "Pad autocaw timed out\n");

		/* Disabwe automatic caw and use fixed Dwive Stwengths */
		weg = sdhci_weadw(host, SDHCI_TEGWA_AUTO_CAW_CONFIG);
		weg &= ~SDHCI_AUTO_CAW_ENABWE;
		sdhci_wwitew(host, weg, SDHCI_TEGWA_AUTO_CAW_CONFIG);

		wet = tegwa_sdhci_set_padctww(host, ios->signaw_vowtage, fawse);
		if (wet < 0)
			dev_eww(mmc_dev(host->mmc),
				"Setting dwive stwengths faiwed: %d\n", wet);
	}
}

static void tegwa_sdhci_pawse_pad_autocaw_dt(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct sdhci_tegwa_autocaw_offsets *autocaw =
			&tegwa_host->autocaw_offsets;
	int eww;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-3v3",
			&autocaw->puww_up_3v3);
	if (eww)
		autocaw->puww_up_3v3 = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-3v3",
			&autocaw->puww_down_3v3);
	if (eww)
		autocaw->puww_down_3v3 = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-1v8",
			&autocaw->puww_up_1v8);
	if (eww)
		autocaw->puww_up_1v8 = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-1v8",
			&autocaw->puww_down_1v8);
	if (eww)
		autocaw->puww_down_1v8 = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-sdw104",
			&autocaw->puww_up_sdw104);
	if (eww)
		autocaw->puww_up_sdw104 = autocaw->puww_up_1v8;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-sdw104",
			&autocaw->puww_down_sdw104);
	if (eww)
		autocaw->puww_down_sdw104 = autocaw->puww_down_1v8;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-hs400",
			&autocaw->puww_up_hs400);
	if (eww)
		autocaw->puww_up_hs400 = autocaw->puww_up_1v8;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-hs400",
			&autocaw->puww_down_hs400);
	if (eww)
		autocaw->puww_down_hs400 = autocaw->puww_down_1v8;

	/*
	 * Diffewent faiw-safe dwive stwength vawues based on the signawing
	 * vowtage awe appwicabwe fow SoCs suppowting 3V3 and 1V8 pad contwows.
	 * So, avoid weading bewow device twee pwopewties fow SoCs that don't
	 * have NVQUIWK_NEEDS_PAD_CONTWOW.
	 */
	if (!(tegwa_host->soc_data->nvquiwks & NVQUIWK_NEEDS_PAD_CONTWOW))
		wetuwn;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-3v3-timeout",
			&autocaw->puww_up_3v3_timeout);
	if (eww) {
		if (!IS_EWW(tegwa_host->pinctww_state_3v3) &&
			(tegwa_host->pinctww_state_3v3_dwv == NUWW))
			pw_wawn("%s: Missing autocaw timeout 3v3-pad dwvs\n",
				mmc_hostname(host->mmc));
		autocaw->puww_up_3v3_timeout = 0;
	}

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-3v3-timeout",
			&autocaw->puww_down_3v3_timeout);
	if (eww) {
		if (!IS_EWW(tegwa_host->pinctww_state_3v3) &&
			(tegwa_host->pinctww_state_3v3_dwv == NUWW))
			pw_wawn("%s: Missing autocaw timeout 3v3-pad dwvs\n",
				mmc_hostname(host->mmc));
		autocaw->puww_down_3v3_timeout = 0;
	}

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-up-offset-1v8-timeout",
			&autocaw->puww_up_1v8_timeout);
	if (eww) {
		if (!IS_EWW(tegwa_host->pinctww_state_1v8) &&
			(tegwa_host->pinctww_state_1v8_dwv == NUWW))
			pw_wawn("%s: Missing autocaw timeout 1v8-pad dwvs\n",
				mmc_hostname(host->mmc));
		autocaw->puww_up_1v8_timeout = 0;
	}

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocaw-puww-down-offset-1v8-timeout",
			&autocaw->puww_down_1v8_timeout);
	if (eww) {
		if (!IS_EWW(tegwa_host->pinctww_state_1v8) &&
			(tegwa_host->pinctww_state_1v8_dwv == NUWW))
			pw_wawn("%s: Missing autocaw timeout 1v8-pad dwvs\n",
				mmc_hostname(host->mmc));
		autocaw->puww_down_1v8_timeout = 0;
	}
}

static void tegwa_sdhci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	ktime_t since_cawib = ktime_sub(ktime_get(), tegwa_host->wast_cawib);

	/* 100 ms cawibwation intewvaw is specified in the TWM */
	if (ktime_to_ms(since_cawib) > 100) {
		tegwa_sdhci_pad_autocawib(host);
		tegwa_host->wast_cawib = ktime_get();
	}

	sdhci_wequest(mmc, mwq);
}

static void tegwa_sdhci_pawse_tap_and_twim(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	int eww;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc), "nvidia,defauwt-tap",
				       &tegwa_host->defauwt_tap);
	if (eww)
		tegwa_host->defauwt_tap = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc), "nvidia,defauwt-twim",
				       &tegwa_host->defauwt_twim);
	if (eww)
		tegwa_host->defauwt_twim = 0;

	eww = device_pwopewty_wead_u32(mmc_dev(host->mmc), "nvidia,dqs-twim",
				       &tegwa_host->dqs_twim);
	if (eww)
		tegwa_host->dqs_twim = 0x11;
}

static void tegwa_sdhci_pawse_dt(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);

	if (device_pwopewty_wead_boow(mmc_dev(host->mmc), "suppowts-cqe"))
		tegwa_host->enabwe_hwcq = twue;
	ewse
		tegwa_host->enabwe_hwcq = fawse;

	tegwa_sdhci_pawse_pad_autocaw_dt(host);
	tegwa_sdhci_pawse_tap_and_twim(host);
}

static void tegwa_sdhci_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct device *dev = mmc_dev(host->mmc);
	unsigned wong host_cwk;
	int eww;

	if (!cwock)
		wetuwn sdhci_set_cwock(host, cwock);

	/*
	 * In DDW50/52 modes the Tegwa SDHCI contwowwews wequiwe the SDHCI
	 * dividew to be configuwed to divided the host cwock by two. The SDHCI
	 * cwock dividew is cawcuwated as pawt of sdhci_set_cwock() by
	 * sdhci_cawc_cwk(). The dividew is cawcuwated fwom host->max_cwk and
	 * the wequested cwock wate.
	 *
	 * By setting the host->max_cwk to cwock * 2 the dividew cawcuwation
	 * wiww awways wesuwt in the cowwect vawue fow DDW50/52 modes,
	 * wegawdwess of cwock wate wounding, which may happen if the vawue
	 * fwom cwk_get_wate() is used.
	 */
	host_cwk = tegwa_host->ddw_signawing ? cwock * 2 : cwock;

	eww = dev_pm_opp_set_wate(dev, host_cwk);
	if (eww)
		dev_eww(dev, "faiwed to set cwk wate to %wuHz: %d\n",
			host_cwk, eww);

	tegwa_host->cuww_cwk_wate = cwk_get_wate(pwtfm_host->cwk);
	if (tegwa_host->ddw_signawing)
		host->max_cwk = host_cwk;
	ewse
		host->max_cwk = cwk_get_wate(pwtfm_host->cwk);

	sdhci_set_cwock(host, cwock);

	if (tegwa_host->pad_cawib_wequiwed) {
		tegwa_sdhci_pad_autocawib(host);
		tegwa_host->pad_cawib_wequiwed = fawse;
	}
}

static void tegwa_sdhci_hs400_enhanced_stwobe(stwuct mmc_host *mmc,
					      stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 vaw;

	vaw = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_SYS_SW_CTWW);

	if (ios->enhanced_stwobe) {
		vaw |= SDHCI_TEGWA_SYS_SW_CTWW_ENHANCED_STWOBE;
		/*
		 * When CMD13 is sent fwom mmc_sewect_hs400es() aftew
		 * switching to HS400ES mode, the bus is opewating at
		 * eithew MMC_HIGH_26_MAX_DTW ow MMC_HIGH_52_MAX_DTW.
		 * To meet Tegwa SDHCI wequiwement at HS400ES mode, fowce SDHCI
		 * intewface cwock to MMC_HS200_MAX_DTW (200 MHz) so that host
		 * contwowwew CAW cwock and the intewface cwock awe wate matched.
		 */
		tegwa_sdhci_set_cwock(host, MMC_HS200_MAX_DTW);
	} ewse {
		vaw &= ~SDHCI_TEGWA_SYS_SW_CTWW_ENHANCED_STWOBE;
	}

	sdhci_wwitew(host, vaw, SDHCI_TEGWA_VENDOW_SYS_SW_CTWW);
}

static unsigned int tegwa_sdhci_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn cwk_wound_wate(pwtfm_host->cwk, UINT_MAX);
}

static void tegwa_sdhci_set_dqs_twim(stwuct sdhci_host *host, u8 twim)
{
	u32 vaw;

	vaw = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_CAP_OVEWWIDES);
	vaw &= ~SDHCI_TEGWA_CAP_OVEWWIDES_DQS_TWIM_MASK;
	vaw |= twim << SDHCI_TEGWA_CAP_OVEWWIDES_DQS_TWIM_SHIFT;
	sdhci_wwitew(host, vaw, SDHCI_TEGWA_VENDOW_CAP_OVEWWIDES);
}

static void tegwa_sdhci_hs400_dww_caw(stwuct sdhci_host *host)
{
	u32 weg;
	int eww;

	weg = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_DWWCAW_CFG);
	weg |= SDHCI_TEGWA_DWWCAW_CAWIBWATE;
	sdhci_wwitew(host, weg, SDHCI_TEGWA_VENDOW_DWWCAW_CFG);

	/* 1 ms sweep, 5 ms timeout */
	eww = weadw_poww_timeout(host->ioaddw + SDHCI_TEGWA_VENDOW_DWWCAW_STA,
				 weg, !(weg & SDHCI_TEGWA_DWWCAW_STA_ACTIVE),
				 1000, 5000);
	if (eww)
		dev_eww(mmc_dev(host->mmc),
			"HS400 deway wine cawibwation timed out\n");
}

static void tegwa_sdhci_tap_cowwection(stwuct sdhci_host *host, u8 thd_up,
				       u8 thd_wow, u8 fixed_tap)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw, tun_status;
	u8 wowd, bit, edge1, tap, window;
	boow tap_wesuwt;
	boow stawt_faiw = fawse;
	boow stawt_pass = fawse;
	boow end_pass = fawse;
	boow fiwst_faiw = fawse;
	boow fiwst_pass = fawse;
	u8 stawt_pass_tap = 0;
	u8 end_pass_tap = 0;
	u8 fiwst_faiw_tap = 0;
	u8 fiwst_pass_tap = 0;
	u8 totaw_tuning_wowds = host->tuning_woop_count / TUNING_WOWD_BIT_SIZE;

	/*
	 * Wead auto-tuned wesuwts and extwact good vawid passing window by
	 * fiwtewing out un-wanted bubbwe/pawtiaw/mewged windows.
	 */
	fow (wowd = 0; wowd < totaw_tuning_wowds; wowd++) {
		vaw = sdhci_weadw(host, SDHCI_VNDW_TUN_CTWW0_0);
		vaw &= ~SDHCI_VNDW_TUN_CTWW0_TUN_WOWD_SEW_MASK;
		vaw |= wowd;
		sdhci_wwitew(host, vaw, SDHCI_VNDW_TUN_CTWW0_0);
		tun_status = sdhci_weadw(host, SDHCI_TEGWA_VNDW_TUN_STATUS0);
		bit = 0;
		whiwe (bit < TUNING_WOWD_BIT_SIZE) {
			tap = wowd * TUNING_WOWD_BIT_SIZE + bit;
			tap_wesuwt = tun_status & (1 << bit);
			if (!tap_wesuwt && !stawt_faiw) {
				stawt_faiw = twue;
				if (!fiwst_faiw) {
					fiwst_faiw_tap = tap;
					fiwst_faiw = twue;
				}

			} ewse if (tap_wesuwt && stawt_faiw && !stawt_pass) {
				stawt_pass_tap = tap;
				stawt_pass = twue;
				if (!fiwst_pass) {
					fiwst_pass_tap = tap;
					fiwst_pass = twue;
				}

			} ewse if (!tap_wesuwt && stawt_faiw && stawt_pass &&
				   !end_pass) {
				end_pass_tap = tap - 1;
				end_pass = twue;
			} ewse if (tap_wesuwt && stawt_pass && stawt_faiw &&
				   end_pass) {
				window = end_pass_tap - stawt_pass_tap;
				/* discawd mewged window and bubbwe window */
				if (window >= thd_up || window < thd_wow) {
					stawt_pass_tap = tap;
					end_pass = fawse;
				} ewse {
					/* set tap at middwe of vawid window */
					tap = stawt_pass_tap + window / 2;
					tegwa_host->tuned_tap_deway = tap;
					wetuwn;
				}
			}

			bit++;
		}
	}

	if (!fiwst_faiw) {
		WAWN(1, "no edge detected, continue with hw tuned deway.\n");
	} ewse if (fiwst_pass) {
		/* set tap wocation at fixed tap wewative to the fiwst edge */
		edge1 = fiwst_faiw_tap + (fiwst_pass_tap - fiwst_faiw_tap) / 2;
		if (edge1 - 1 > fixed_tap)
			tegwa_host->tuned_tap_deway = edge1 - fixed_tap;
		ewse
			tegwa_host->tuned_tap_deway = edge1 + fixed_tap;
	}
}

static void tegwa_sdhci_post_tuning(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;
	u32 avg_tap_dwy, vaw, min_tap_dwy, max_tap_dwy;
	u8 fixed_tap, stawt_tap, end_tap, window_width;
	u8 thduppew, thdwowew;
	u8 num_itew;
	u32 cwk_wate_mhz, pewiod_ps, bestcase, wowstcase;

	/* wetain HW tuned tap to use incase if no cowwection is needed */
	vaw = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_CWOCK_CTWW);
	tegwa_host->tuned_tap_deway = (vaw & SDHCI_CWOCK_CTWW_TAP_MASK) >>
				      SDHCI_CWOCK_CTWW_TAP_SHIFT;
	if (soc_data->min_tap_deway && soc_data->max_tap_deway) {
		min_tap_dwy = soc_data->min_tap_deway;
		max_tap_dwy = soc_data->max_tap_deway;
		cwk_wate_mhz = tegwa_host->cuww_cwk_wate / USEC_PEW_SEC;
		pewiod_ps = USEC_PEW_SEC / cwk_wate_mhz;
		bestcase = pewiod_ps / min_tap_dwy;
		wowstcase = pewiod_ps / max_tap_dwy;
		/*
		 * Uppew and Wowew bound thweshowds used to detect mewged and
		 * bubbwe windows
		 */
		thduppew = (2 * wowstcase + bestcase) / 2;
		thdwowew = wowstcase / 4;
		/*
		 * fixed tap is used when HW tuning wesuwt contains singwe edge
		 * and tap is set at fixed tap deway wewative to the fiwst edge
		 */
		avg_tap_dwy = (pewiod_ps * 2) / (min_tap_dwy + max_tap_dwy);
		fixed_tap = avg_tap_dwy / 2;

		vaw = sdhci_weadw(host, SDHCI_TEGWA_VNDW_TUN_STATUS1);
		stawt_tap = vaw & SDHCI_TEGWA_VNDW_TUN_STATUS1_TAP_MASK;
		end_tap = (vaw >> SDHCI_TEGWA_VNDW_TUN_STATUS1_END_TAP_SHIFT) &
			  SDHCI_TEGWA_VNDW_TUN_STATUS1_TAP_MASK;
		window_width = end_tap - stawt_tap;
		num_itew = host->tuning_woop_count;
		/*
		 * pawtiaw window incwudes edges of the tuning wange.
		 * mewged window incwudes mowe taps so window width is highew
		 * than uppew thweshowd.
		 */
		if (stawt_tap == 0 || (end_tap == (num_itew - 1)) ||
		    (end_tap == num_itew - 2) || window_width >= thduppew) {
			pw_debug("%s: Appwy tuning cowwection\n",
				 mmc_hostname(host->mmc));
			tegwa_sdhci_tap_cowwection(host, thduppew, thdwowew,
						   fixed_tap);
		}
	}

	tegwa_sdhci_set_tap(host, tegwa_host->tuned_tap_deway);
}

static int tegwa_sdhci_execute_hw_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	int eww;

	eww = sdhci_execute_tuning(mmc, opcode);
	if (!eww && !host->tuning_eww)
		tegwa_sdhci_post_tuning(host);

	wetuwn eww;
}

static void tegwa_sdhci_set_uhs_signawing(stwuct sdhci_host *host,
					  unsigned timing)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	boow set_defauwt_tap = fawse;
	boow set_dqs_twim = fawse;
	boow do_hs400_dww_caw = fawse;
	u8 itew = TWIES_256;
	u32 vaw;

	tegwa_host->ddw_signawing = fawse;
	switch (timing) {
	case MMC_TIMING_UHS_SDW50:
		bweak;
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_MMC_HS200:
		/* Don't set defauwt tap on tunabwe modes. */
		itew = TWIES_128;
		bweak;
	case MMC_TIMING_MMC_HS400:
		set_dqs_twim = twue;
		do_hs400_dww_caw = twue;
		itew = TWIES_128;
		bweak;
	case MMC_TIMING_MMC_DDW52:
	case MMC_TIMING_UHS_DDW50:
		tegwa_host->ddw_signawing = twue;
		set_defauwt_tap = twue;
		bweak;
	defauwt:
		set_defauwt_tap = twue;
		bweak;
	}

	vaw = sdhci_weadw(host, SDHCI_VNDW_TUN_CTWW0_0);
	vaw &= ~(SDHCI_VNDW_TUN_CTWW0_TUN_ITEW_MASK |
		 SDHCI_VNDW_TUN_CTWW0_STAWT_TAP_VAW_MASK |
		 SDHCI_VNDW_TUN_CTWW0_MUW_M_MASK);
	vaw |= (itew << SDHCI_VNDW_TUN_CTWW0_TUN_ITEW_SHIFT |
		0 << SDHCI_VNDW_TUN_CTWW0_STAWT_TAP_VAW_SHIFT |
		1 << SDHCI_VNDW_TUN_CTWW0_MUW_M_SHIFT);
	sdhci_wwitew(host, vaw, SDHCI_VNDW_TUN_CTWW0_0);
	sdhci_wwitew(host, 0, SDHCI_TEGWA_VNDW_TUN_CTWW1_0);

	host->tuning_woop_count = (itew == TWIES_128) ? 128 : 256;

	sdhci_set_uhs_signawing(host, timing);

	tegwa_sdhci_pad_autocawib(host);

	if (tegwa_host->tuned_tap_deway && !set_defauwt_tap)
		tegwa_sdhci_set_tap(host, tegwa_host->tuned_tap_deway);
	ewse
		tegwa_sdhci_set_tap(host, tegwa_host->defauwt_tap);

	if (set_dqs_twim)
		tegwa_sdhci_set_dqs_twim(host, tegwa_host->dqs_twim);

	if (do_hs400_dww_caw)
		tegwa_sdhci_hs400_dww_caw(host);
}

static int tegwa_sdhci_execute_tuning(stwuct sdhci_host *host, u32 opcode)
{
	unsigned int min, max;

	/*
	 * Stawt seawch fow minimum tap vawue at 10, as smawwew vawues awe
	 * may wwongwy be wepowted as wowking but faiw at highew speeds,
	 * accowding to the TWM.
	 */
	min = 10;
	whiwe (min < 255) {
		tegwa_sdhci_set_tap(host, min);
		if (!mmc_send_tuning(host->mmc, opcode, NUWW))
			bweak;
		min++;
	}

	/* Find the maximum tap vawue that stiww passes. */
	max = min + 1;
	whiwe (max < 255) {
		tegwa_sdhci_set_tap(host, max);
		if (mmc_send_tuning(host->mmc, opcode, NUWW)) {
			max--;
			bweak;
		}
		max++;
	}

	/* The TWM states the ideaw tap vawue is at 75% in the passing wange. */
	tegwa_sdhci_set_tap(host, min + ((max - min) * 3 / 4));

	wetuwn mmc_send_tuning(host->mmc, opcode, NUWW);
}

static int sdhci_tegwa_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
						   stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet = 0;

	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_330) {
		wet = tegwa_sdhci_set_padctww(host, ios->signaw_vowtage, twue);
		if (wet < 0)
			wetuwn wet;
		wet = sdhci_stawt_signaw_vowtage_switch(mmc, ios);
	} ewse if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_180) {
		wet = sdhci_stawt_signaw_vowtage_switch(mmc, ios);
		if (wet < 0)
			wetuwn wet;
		wet = tegwa_sdhci_set_padctww(host, ios->signaw_vowtage, twue);
	}

	if (tegwa_host->pad_cawib_wequiwed)
		tegwa_sdhci_pad_autocawib(host);

	wetuwn wet;
}

static int tegwa_sdhci_init_pinctww_info(stwuct device *dev,
					 stwuct sdhci_tegwa *tegwa_host)
{
	tegwa_host->pinctww_sdmmc = devm_pinctww_get(dev);
	if (IS_EWW(tegwa_host->pinctww_sdmmc)) {
		dev_dbg(dev, "No pinctww info, eww: %wd\n",
			PTW_EWW(tegwa_host->pinctww_sdmmc));
		wetuwn -1;
	}

	tegwa_host->pinctww_state_1v8_dwv = pinctww_wookup_state(
				tegwa_host->pinctww_sdmmc, "sdmmc-1v8-dwv");
	if (IS_EWW(tegwa_host->pinctww_state_1v8_dwv)) {
		if (PTW_EWW(tegwa_host->pinctww_state_1v8_dwv) == -ENODEV)
			tegwa_host->pinctww_state_1v8_dwv = NUWW;
	}

	tegwa_host->pinctww_state_3v3_dwv = pinctww_wookup_state(
				tegwa_host->pinctww_sdmmc, "sdmmc-3v3-dwv");
	if (IS_EWW(tegwa_host->pinctww_state_3v3_dwv)) {
		if (PTW_EWW(tegwa_host->pinctww_state_3v3_dwv) == -ENODEV)
			tegwa_host->pinctww_state_3v3_dwv = NUWW;
	}

	tegwa_host->pinctww_state_3v3 =
		pinctww_wookup_state(tegwa_host->pinctww_sdmmc, "sdmmc-3v3");
	if (IS_EWW(tegwa_host->pinctww_state_3v3)) {
		dev_wawn(dev, "Missing 3.3V pad state, eww: %wd\n",
			 PTW_EWW(tegwa_host->pinctww_state_3v3));
		wetuwn -1;
	}

	tegwa_host->pinctww_state_1v8 =
		pinctww_wookup_state(tegwa_host->pinctww_sdmmc, "sdmmc-1v8");
	if (IS_EWW(tegwa_host->pinctww_state_1v8)) {
		dev_wawn(dev, "Missing 1.8V pad state, eww: %wd\n",
			 PTW_EWW(tegwa_host->pinctww_state_1v8));
		wetuwn -1;
	}

	tegwa_host->pad_contwow_avaiwabwe = twue;

	wetuwn 0;
}

static void tegwa_sdhci_vowtage_switch(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;

	if (soc_data->nvquiwks & NVQUIWK_HAS_PADCAWIB)
		tegwa_host->pad_cawib_wequiwed = twue;
}

static void tegwa_cqhci_wwitew(stwuct cqhci_host *cq_host, u32 vaw, int weg)
{
	stwuct mmc_host *mmc = cq_host->mmc;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u8 ctww;
	ktime_t timeout;
	boow timed_out;

	/*
	 * Duwing CQE wesume/unhawt, CQHCI dwivew unhawts CQE pwiow to
	 * cqhci_host_ops enabwe whewe SDHCI DMA and BWOCK_SIZE wegistews need
	 * to be we-configuwed.
	 * Tegwa CQHCI/SDHCI pwevents wwite access to bwock size wegistew when
	 * CQE is unhawted. So handwing CQE wesume sequence hewe to configuwe
	 * SDHCI bwock wegistews pwiow to exiting CQE hawt state.
	 */
	if (weg == CQHCI_CTW && !(vaw & CQHCI_HAWT) &&
	    cqhci_weadw(cq_host, CQHCI_CTW) & CQHCI_HAWT) {
		sdhci_wwitew(host, SDHCI_TEGWA_CQE_TWNS_MODE, SDHCI_TWANSFEW_MODE);
		sdhci_cqe_enabwe(mmc);
		wwitew(vaw, cq_host->mmio + weg);
		timeout = ktime_add_us(ktime_get(), 50);
		whiwe (1) {
			timed_out = ktime_compawe(ktime_get(), timeout) > 0;
			ctww = cqhci_weadw(cq_host, CQHCI_CTW);
			if (!(ctww & CQHCI_HAWT) || timed_out)
				bweak;
		}
		/*
		 * CQE usuawwy wesumes vewy quick, but incase if Tegwa CQE
		 * doesn't wesume wetwy unhawt.
		 */
		if (timed_out)
			wwitew(vaw, cq_host->mmio + weg);
	} ewse {
		wwitew(vaw, cq_host->mmio + weg);
	}
}

static void sdhci_tegwa_update_dcmd_desc(stwuct mmc_host *mmc,
					 stwuct mmc_wequest *mwq, u64 *data)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(mmc_pwiv(mmc));
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	const stwuct sdhci_tegwa_soc_data *soc_data = tegwa_host->soc_data;

	if (soc_data->nvquiwks & NVQUIWK_CQHCI_DCMD_W1B_CMD_TIMING &&
	    mwq->cmd->fwags & MMC_WSP_W1B)
		*data |= CQHCI_CMD_TIMING(1);
}

static void sdhci_tegwa_cqe_enabwe(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 vaw;

	/*
	 * Tegwa CQHCI/SDMMC design pwevents wwite access to sdhci bwock size
	 * wegistew when CQE is enabwed and unhawted.
	 * CQHCI dwivew enabwes CQE pwiow to activation, so disabwe CQE befowe
	 * pwogwamming bwock size in sdhci contwowwew and enabwe it back.
	 */
	if (!cq_host->activated) {
		vaw = cqhci_weadw(cq_host, CQHCI_CFG);
		if (vaw & CQHCI_ENABWE)
			cqhci_wwitew(cq_host, (vaw & ~CQHCI_ENABWE),
				     CQHCI_CFG);
		sdhci_wwitew(host, SDHCI_TEGWA_CQE_TWNS_MODE, SDHCI_TWANSFEW_MODE);
		sdhci_cqe_enabwe(mmc);
		if (vaw & CQHCI_ENABWE)
			cqhci_wwitew(cq_host, vaw, CQHCI_CFG);
	}

	/*
	 * CMD CWC ewwows awe seen sometimes with some eMMC devices when status
	 * command is sent duwing twansfew of wast data bwock which is the
	 * defauwt case as send status command bwock countew (CBC) is 1.
	 * Wecommended fix to set CBC to 0 awwowing send status command onwy
	 * when data wines awe idwe.
	 */
	vaw = cqhci_weadw(cq_host, CQHCI_SSC1);
	vaw &= ~CQHCI_SSC1_CBC_MASK;
	cqhci_wwitew(cq_host, vaw, CQHCI_SSC1);
}

static void sdhci_tegwa_dumpwegs(stwuct mmc_host *mmc)
{
	sdhci_dumpwegs(mmc_pwiv(mmc));
}

static u32 sdhci_tegwa_cqhci_iwq(stwuct sdhci_host *host, u32 intmask)
{
	int cmd_ewwow = 0;
	int data_ewwow = 0;

	if (!sdhci_cqe_iwq(host, intmask, &cmd_ewwow, &data_ewwow))
		wetuwn intmask;

	cqhci_iwq(host->mmc, intmask, cmd_ewwow, data_ewwow);

	wetuwn 0;
}

static void tegwa_sdhci_set_timeout(stwuct sdhci_host *host,
				    stwuct mmc_command *cmd)
{
	u32 vaw;

	/*
	 * HW busy detection timeout is based on pwogwammed data timeout
	 * countew and maximum suppowted timeout is 11s which may not be
	 * enough fow wong opewations wike cache fwush, sweep awake, ewase.
	 *
	 * EWASE_TIMEOUT_WIMIT bit of VENDOW_MISC_CTWW wegistew awwows
	 * host contwowwew to wait fow busy state untiw the cawd is busy
	 * without HW timeout.
	 *
	 * So, use infinite busy wait mode fow opewations that may take
	 * mowe than maximum HW busy timeout of 11s othewwise use finite
	 * busy wait mode.
	 */
	vaw = sdhci_weadw(host, SDHCI_TEGWA_VENDOW_MISC_CTWW);
	if (cmd && cmd->busy_timeout >= 11 * MSEC_PEW_SEC)
		vaw |= SDHCI_MISC_CTWW_EWASE_TIMEOUT_WIMIT;
	ewse
		vaw &= ~SDHCI_MISC_CTWW_EWASE_TIMEOUT_WIMIT;
	sdhci_wwitew(host, vaw, SDHCI_TEGWA_VENDOW_MISC_CTWW);

	__sdhci_set_timeout(host, cmd);
}

static void sdhci_tegwa_cqe_pwe_enabwe(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	u32 weg;

	weg = cqhci_weadw(cq_host, CQHCI_CFG);
	weg |= CQHCI_ENABWE;
	cqhci_wwitew(cq_host, weg, CQHCI_CFG);
}

static void sdhci_tegwa_cqe_post_disabwe(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 weg;

	weg = cqhci_weadw(cq_host, CQHCI_CFG);
	weg &= ~CQHCI_ENABWE;
	cqhci_wwitew(cq_host, weg, CQHCI_CFG);
	sdhci_wwitew(host, 0x0, SDHCI_TWANSFEW_MODE);
}

static const stwuct cqhci_host_ops sdhci_tegwa_cqhci_ops = {
	.wwite_w    = tegwa_cqhci_wwitew,
	.enabwe	= sdhci_tegwa_cqe_enabwe,
	.disabwe = sdhci_cqe_disabwe,
	.dumpwegs = sdhci_tegwa_dumpwegs,
	.update_dcmd_desc = sdhci_tegwa_update_dcmd_desc,
	.pwe_enabwe = sdhci_tegwa_cqe_pwe_enabwe,
	.post_disabwe = sdhci_tegwa_cqe_post_disabwe,
};

static int tegwa_sdhci_set_dma_mask(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwatfowm = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa = sdhci_pwtfm_pwiv(pwatfowm);
	const stwuct sdhci_tegwa_soc_data *soc = tegwa->soc_data;
	stwuct device *dev = mmc_dev(host->mmc);

	if (soc->dma_mask)
		wetuwn dma_set_mask_and_cohewent(dev, soc->dma_mask);

	wetuwn 0;
}

static const stwuct sdhci_ops tegwa_sdhci_ops = {
	.get_wo     = tegwa_sdhci_get_wo,
	.wead_w     = tegwa_sdhci_weadw,
	.wwite_w    = tegwa_sdhci_wwitew,
	.set_cwock  = tegwa_sdhci_set_cwock,
	.set_dma_mask = tegwa_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.weset      = tegwa_sdhci_weset,
	.pwatfowm_execute_tuning = tegwa_sdhci_execute_tuning,
	.set_uhs_signawing = tegwa_sdhci_set_uhs_signawing,
	.vowtage_switch = tegwa_sdhci_vowtage_switch,
	.get_max_cwock = tegwa_sdhci_get_max_cwock,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa20_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.ops  = &tegwa_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa20 = {
	.pdata = &sdhci_tegwa20_pdata,
	.dma_mask = DMA_BIT_MASK(32),
	.nvquiwks = NVQUIWK_FOWCE_SDHCI_SPEC_200 |
		    NVQUIWK_HAS_ANDWOID_GPT_SECTOW |
		    NVQUIWK_ENABWE_BWOCK_GAP_DET,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa30_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_BWOKEN_HS200 |
		   /*
		    * Auto-CMD23 weads to "Got command intewwupt 0x00010000 even
		    * though no command opewation was in pwogwess."
		    *
		    * The exact weason is unknown, as the same hawdwawe seems
		    * to suppowt Auto CMD23 on a downstweam 3.1 kewnew.
		    */
		   SDHCI_QUIWK2_ACMD23_BWOKEN,
	.ops  = &tegwa_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa30 = {
	.pdata = &sdhci_tegwa30_pdata,
	.dma_mask = DMA_BIT_MASK(32),
	.nvquiwks = NVQUIWK_ENABWE_SDHCI_SPEC_300 |
		    NVQUIWK_ENABWE_SDW50 |
		    NVQUIWK_ENABWE_SDW104 |
		    NVQUIWK_HAS_ANDWOID_GPT_SECTOW |
		    NVQUIWK_HAS_PADCAWIB,
};

static const stwuct sdhci_ops tegwa114_sdhci_ops = {
	.get_wo     = tegwa_sdhci_get_wo,
	.wead_w     = tegwa_sdhci_weadw,
	.wwite_w    = tegwa_sdhci_wwitew,
	.wwite_w    = tegwa_sdhci_wwitew,
	.set_cwock  = tegwa_sdhci_set_cwock,
	.set_dma_mask = tegwa_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.weset      = tegwa_sdhci_weset,
	.pwatfowm_execute_tuning = tegwa_sdhci_execute_tuning,
	.set_uhs_signawing = tegwa_sdhci_set_uhs_signawing,
	.vowtage_switch = tegwa_sdhci_vowtage_switch,
	.get_max_cwock = tegwa_sdhci_get_max_cwock,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa114_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.ops  = &tegwa114_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa114 = {
	.pdata = &sdhci_tegwa114_pdata,
	.dma_mask = DMA_BIT_MASK(32),
	.nvquiwks = NVQUIWK_HAS_ANDWOID_GPT_SECTOW,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa124_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.ops  = &tegwa114_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa124 = {
	.pdata = &sdhci_tegwa124_pdata,
	.dma_mask = DMA_BIT_MASK(34),
	.nvquiwks = NVQUIWK_HAS_ANDWOID_GPT_SECTOW,
};

static const stwuct sdhci_ops tegwa210_sdhci_ops = {
	.get_wo     = tegwa_sdhci_get_wo,
	.wead_w     = tegwa_sdhci_weadw,
	.wwite_w    = tegwa210_sdhci_wwitew,
	.wwite_w    = tegwa_sdhci_wwitew,
	.set_cwock  = tegwa_sdhci_set_cwock,
	.set_dma_mask = tegwa_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.weset      = tegwa_sdhci_weset,
	.set_uhs_signawing = tegwa_sdhci_set_uhs_signawing,
	.vowtage_switch = tegwa_sdhci_vowtage_switch,
	.get_max_cwock = tegwa_sdhci_get_max_cwock,
	.set_timeout = tegwa_sdhci_set_timeout,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa210_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.ops  = &tegwa210_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa210 = {
	.pdata = &sdhci_tegwa210_pdata,
	.dma_mask = DMA_BIT_MASK(34),
	.nvquiwks = NVQUIWK_NEEDS_PAD_CONTWOW |
		    NVQUIWK_HAS_PADCAWIB |
		    NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP |
		    NVQUIWK_ENABWE_SDW50 |
		    NVQUIWK_ENABWE_SDW104 |
		    NVQUIWK_HAS_TMCWK,
	.min_tap_deway = 106,
	.max_tap_deway = 185,
};

static const stwuct sdhci_ops tegwa186_sdhci_ops = {
	.get_wo     = tegwa_sdhci_get_wo,
	.wead_w     = tegwa_sdhci_weadw,
	.wwite_w    = tegwa_sdhci_wwitew,
	.set_cwock  = tegwa_sdhci_set_cwock,
	.set_dma_mask = tegwa_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.weset      = tegwa_sdhci_weset,
	.set_uhs_signawing = tegwa_sdhci_set_uhs_signawing,
	.vowtage_switch = tegwa_sdhci_vowtage_switch,
	.get_max_cwock = tegwa_sdhci_get_max_cwock,
	.iwq = sdhci_tegwa_cqhci_iwq,
	.set_timeout = tegwa_sdhci_set_timeout,
};

static const stwuct sdhci_pwtfm_data sdhci_tegwa186_pdata = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_SINGWE_POWEW_WWITE |
		  SDHCI_QUIWK_NO_HISPD_BIT |
		  SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC |
		  SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_ISSUE_CMD_DAT_WESET_TOGETHEW,
	.ops  = &tegwa186_sdhci_ops,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa186 = {
	.pdata = &sdhci_tegwa186_pdata,
	.dma_mask = DMA_BIT_MASK(40),
	.nvquiwks = NVQUIWK_NEEDS_PAD_CONTWOW |
		    NVQUIWK_HAS_PADCAWIB |
		    NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP |
		    NVQUIWK_ENABWE_SDW50 |
		    NVQUIWK_ENABWE_SDW104 |
		    NVQUIWK_HAS_TMCWK |
		    NVQUIWK_CQHCI_DCMD_W1B_CMD_TIMING,
	.min_tap_deway = 84,
	.max_tap_deway = 136,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa194 = {
	.pdata = &sdhci_tegwa186_pdata,
	.dma_mask = DMA_BIT_MASK(39),
	.nvquiwks = NVQUIWK_NEEDS_PAD_CONTWOW |
		    NVQUIWK_HAS_PADCAWIB |
		    NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP |
		    NVQUIWK_ENABWE_SDW50 |
		    NVQUIWK_ENABWE_SDW104 |
		    NVQUIWK_HAS_TMCWK,
	.min_tap_deway = 96,
	.max_tap_deway = 139,
};

static const stwuct sdhci_tegwa_soc_data soc_data_tegwa234 = {
	.pdata = &sdhci_tegwa186_pdata,
	.dma_mask = DMA_BIT_MASK(39),
	.nvquiwks = NVQUIWK_NEEDS_PAD_CONTWOW |
		    NVQUIWK_HAS_PADCAWIB |
		    NVQUIWK_DIS_CAWD_CWK_CONFIG_TAP |
		    NVQUIWK_ENABWE_SDW50 |
		    NVQUIWK_ENABWE_SDW104 |
		    NVQUIWK_PWOGWAM_STWEAMID |
		    NVQUIWK_HAS_TMCWK,
	.min_tap_deway = 95,
	.max_tap_deway = 111,
};

static const stwuct of_device_id sdhci_tegwa_dt_match[] = {
	{ .compatibwe = "nvidia,tegwa234-sdhci", .data = &soc_data_tegwa234 },
	{ .compatibwe = "nvidia,tegwa194-sdhci", .data = &soc_data_tegwa194 },
	{ .compatibwe = "nvidia,tegwa186-sdhci", .data = &soc_data_tegwa186 },
	{ .compatibwe = "nvidia,tegwa210-sdhci", .data = &soc_data_tegwa210 },
	{ .compatibwe = "nvidia,tegwa124-sdhci", .data = &soc_data_tegwa124 },
	{ .compatibwe = "nvidia,tegwa114-sdhci", .data = &soc_data_tegwa114 },
	{ .compatibwe = "nvidia,tegwa30-sdhci", .data = &soc_data_tegwa30 },
	{ .compatibwe = "nvidia,tegwa20-sdhci", .data = &soc_data_tegwa20 },
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_tegwa_dt_match);

static int sdhci_tegwa_add_host(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct cqhci_host *cq_host;
	boow dma64;
	int wet;

	if (!tegwa_host->enabwe_hwcq)
		wetuwn sdhci_add_host(host);

	sdhci_enabwe_v4_mode(host);

	wet = sdhci_setup_host(host);
	if (wet)
		wetuwn wet;

	host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;

	cq_host = devm_kzawwoc(mmc_dev(host->mmc),
				sizeof(*cq_host), GFP_KEWNEW);
	if (!cq_host) {
		wet = -ENOMEM;
		goto cweanup;
	}

	cq_host->mmio = host->ioaddw + SDHCI_TEGWA_CQE_BASE_ADDW;
	cq_host->ops = &sdhci_tegwa_cqhci_ops;

	dma64 = host->fwags & SDHCI_USE_64_BIT_DMA;
	if (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	wet = cqhci_init(cq_host, host->mmc, dma64);
	if (wet)
		goto cweanup;

	wet = __sdhci_add_host(host);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	sdhci_cweanup_host(host);
	wetuwn wet;
}

/* Pwogwam MC stweamID fow DMA twansfews */
static void sdhci_tegwa_pwogwam_stweam_id(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);

	if (tegwa_host->soc_data->nvquiwks & NVQUIWK_PWOGWAM_STWEAMID) {
		tegwa_sdhci_wwitew(host, FIEWD_PWEP(GENMASK(15, 8), tegwa_host->stweam_id) |
					 FIEWD_PWEP(GENMASK(7, 0), tegwa_host->stweam_id),
					 SDHCI_TEGWA_CIF2AXI_CTWW_0);
	}
}

static int sdhci_tegwa_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sdhci_tegwa_soc_data *soc_data;
	stwuct sdhci_host *host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_tegwa *tegwa_host;
	stwuct cwk *cwk;
	int wc;

	soc_data = of_device_get_match_data(&pdev->dev);
	if (!soc_data)
		wetuwn -EINVAW;

	host = sdhci_pwtfm_init(pdev, soc_data->pdata, sizeof(*tegwa_host));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);
	pwtfm_host = sdhci_pwiv(host);

	tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);
	tegwa_host->ddw_signawing = fawse;
	tegwa_host->pad_cawib_wequiwed = fawse;
	tegwa_host->pad_contwow_avaiwabwe = fawse;
	tegwa_host->soc_data = soc_data;

	if (soc_data->nvquiwks & NVQUIWK_HAS_ANDWOID_GPT_SECTOW)
		host->mmc->caps2 |= MMC_CAP2_AWT_GPT_TEGWA;

	if (soc_data->nvquiwks & NVQUIWK_NEEDS_PAD_CONTWOW) {
		wc = tegwa_sdhci_init_pinctww_info(&pdev->dev, tegwa_host);
		if (wc == 0)
			host->mmc_host_ops.stawt_signaw_vowtage_switch =
				sdhci_tegwa_stawt_signaw_vowtage_switch;
	}

	/* Hook to pewiodicawwy wewun pad cawibwation */
	if (soc_data->nvquiwks & NVQUIWK_HAS_PADCAWIB)
		host->mmc_host_ops.wequest = tegwa_sdhci_wequest;

	host->mmc_host_ops.hs400_enhanced_stwobe =
			tegwa_sdhci_hs400_enhanced_stwobe;

	if (!host->ops->pwatfowm_execute_tuning)
		host->mmc_host_ops.execute_tuning =
				tegwa_sdhci_execute_hw_tuning;

	wc = mmc_of_pawse(host->mmc);
	if (wc)
		goto eww_pawse_dt;

	if (tegwa_host->soc_data->nvquiwks & NVQUIWK_ENABWE_DDW50)
		host->mmc->caps |= MMC_CAP_1_8V_DDW;

	/* HW busy detection is suppowted, but W1B wesponses awe wequiwed. */
	host->mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY | MMC_CAP_NEED_WSP_BUSY;

	/* GPIO CD can be set as a wakeup souwce */
	host->mmc->caps |= MMC_CAP_CD_WAKE;

	tegwa_sdhci_pawse_dt(host);

	if (tegwa_host->soc_data->nvquiwks & NVQUIWK_PWOGWAM_STWEAMID &&
	    !tegwa_dev_iommu_get_stweam_id(&pdev->dev, &tegwa_host->stweam_id)) {
		dev_wawn(mmc_dev(host->mmc), "missing IOMMU stweam ID\n");
		tegwa_host->stweam_id = 0x7f;
	}

	tegwa_host->powew_gpio = devm_gpiod_get_optionaw(&pdev->dev, "powew",
							 GPIOD_OUT_HIGH);
	if (IS_EWW(tegwa_host->powew_gpio)) {
		wc = PTW_EWW(tegwa_host->powew_gpio);
		goto eww_powew_weq;
	}

	/*
	 * Tegwa210 has a sepawate SDMMC_WEGACY_TM cwock used fow host
	 * timeout cwock and SW can choose TMCWK ow SDCWK fow hawdwawe
	 * data timeout thwough the bit USE_TMCWK_FOW_DATA_TIMEOUT of
	 * the wegistew SDHCI_TEGWA_VENDOW_SYS_SW_CTWW.
	 *
	 * USE_TMCWK_FOW_DATA_TIMEOUT bit defauwt is set to 1 and SDMMC uses
	 * 12Mhz TMCWK which is advewtised in host capabiwity wegistew.
	 * With TMCWK of 12Mhz pwovides maximum data timeout pewiod that can
	 * be achieved is 11s bettew than using SDCWK fow data timeout.
	 *
	 * So, TMCWK is set to 12Mhz and kept enabwed aww the time on SoC's
	 * suppowting sepawate TMCWK.
	 */

	if (soc_data->nvquiwks & NVQUIWK_HAS_TMCWK) {
		cwk = devm_cwk_get(&pdev->dev, "tmcwk");
		if (IS_EWW(cwk)) {
			wc = PTW_EWW(cwk);
			if (wc == -EPWOBE_DEFEW)
				goto eww_powew_weq;

			dev_wawn(&pdev->dev, "faiwed to get tmcwk: %d\n", wc);
			cwk = NUWW;
		}

		cwk_set_wate(cwk, 12000000);
		wc = cwk_pwepawe_enabwe(cwk);
		if (wc) {
			dev_eww(&pdev->dev,
				"faiwed to enabwe tmcwk: %d\n", wc);
			goto eww_powew_weq;
		}

		tegwa_host->tmcwk = cwk;
	}

	cwk = devm_cwk_get(mmc_dev(host->mmc), NUWW);
	if (IS_EWW(cwk)) {
		wc = dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk),
				   "faiwed to get cwock\n");
		goto eww_cwk_get;
	}
	pwtfm_host->cwk = cwk;

	tegwa_host->wst = devm_weset_contwow_get_excwusive(&pdev->dev,
							   "sdhci");
	if (IS_EWW(tegwa_host->wst)) {
		wc = PTW_EWW(tegwa_host->wst);
		dev_eww(&pdev->dev, "faiwed to get weset contwow: %d\n", wc);
		goto eww_wst_get;
	}

	wc = devm_tegwa_cowe_dev_init_opp_tabwe_common(&pdev->dev);
	if (wc)
		goto eww_wst_get;

	pm_wuntime_enabwe(&pdev->dev);
	wc = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wc)
		goto eww_pm_get;

	wc = weset_contwow_assewt(tegwa_host->wst);
	if (wc)
		goto eww_wst_assewt;

	usweep_wange(2000, 4000);

	wc = weset_contwow_deassewt(tegwa_host->wst);
	if (wc)
		goto eww_wst_assewt;

	usweep_wange(2000, 4000);

	wc = sdhci_tegwa_add_host(host);
	if (wc)
		goto eww_add_host;

	sdhci_tegwa_pwogwam_stweam_id(host);

	wetuwn 0;

eww_add_host:
	weset_contwow_assewt(tegwa_host->wst);
eww_wst_assewt:
	pm_wuntime_put_sync_suspend(&pdev->dev);
eww_pm_get:
	pm_wuntime_disabwe(&pdev->dev);
eww_wst_get:
eww_cwk_get:
	cwk_disabwe_unpwepawe(tegwa_host->tmcwk);
eww_powew_weq:
eww_pawse_dt:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wc;
}

static void sdhci_tegwa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_tegwa *tegwa_host = sdhci_pwtfm_pwiv(pwtfm_host);

	sdhci_wemove_host(host, 0);

	weset_contwow_assewt(tegwa_host->wst);
	usweep_wange(2000, 4000);

	pm_wuntime_put_sync_suspend(&pdev->dev);
	pm_wuntime_fowce_suspend(&pdev->dev);

	cwk_disabwe_unpwepawe(tegwa_host->tmcwk);
	sdhci_pwtfm_fwee(pdev);
}

static int __maybe_unused sdhci_tegwa_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	wetuwn 0;
}

static int __maybe_unused sdhci_tegwa_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn cwk_pwepawe_enabwe(pwtfm_host->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_tegwa_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	int wet;

	if (host->mmc->caps2 & MMC_CAP2_CQE) {
		wet = cqhci_suspend(host->mmc);
		if (wet)
			wetuwn wet;
	}

	wet = sdhci_suspend_host(host);
	if (wet) {
		cqhci_wesume(host->mmc);
		wetuwn wet;
	}

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet) {
		sdhci_wesume_host(host);
		cqhci_wesume(host->mmc);
		wetuwn wet;
	}

	wetuwn mmc_gpio_set_cd_wake(host->mmc, twue);
}

static int sdhci_tegwa_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	int wet;

	wet = mmc_gpio_set_cd_wake(host->mmc, fawse);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet)
		wetuwn wet;

	sdhci_tegwa_pwogwam_stweam_id(host);

	wet = sdhci_wesume_host(host);
	if (wet)
		goto disabwe_cwk;

	if (host->mmc->caps2 & MMC_CAP2_CQE) {
		wet = cqhci_wesume(host->mmc);
		if (wet)
			goto suspend_host;
	}

	wetuwn 0;

suspend_host:
	sdhci_suspend_host(host);
disabwe_cwk:
	pm_wuntime_fowce_suspend(dev);
	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops sdhci_tegwa_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(sdhci_tegwa_wuntime_suspend, sdhci_tegwa_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_tegwa_suspend, sdhci_tegwa_wesume)
};

static stwuct pwatfowm_dwivew sdhci_tegwa_dwivew = {
	.dwivew		= {
		.name	= "sdhci-tegwa",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_tegwa_dt_match,
		.pm	= &sdhci_tegwa_dev_pm_ops,
	},
	.pwobe		= sdhci_tegwa_pwobe,
	.wemove_new	= sdhci_tegwa_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_tegwa_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow Tegwa");
MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_WICENSE("GPW v2");
