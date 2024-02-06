// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mmc/host/mmci.c - AWM PwimeCeww MMCI PW180/1 dwivew
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions, Wtd, Aww Wights Wesewved.
 *  Copywight (C) 2010 ST-Ewicsson SA
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/pm.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>
#incwude <winux/scattewwist.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/amba/mmci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/div64.h>
#incwude <asm/io.h>

#incwude "mmci.h"

#define DWIVEW_NAME "mmci-pw18x"

static void mmci_vawiant_init(stwuct mmci_host *host);
static void ux500_vawiant_init(stwuct mmci_host *host);
static void ux500v2_vawiant_init(stwuct mmci_host *host);

static unsigned int fmax = 515633;

static stwuct vawiant_data vawiant_awm = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 16,
	.datactww_bwocksz	= 11,
	.pwwweg_powewup		= MCI_PWW_UP,
	.f_max			= 100000000,
	.wevewsed_iwq_handwing	= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_WOD,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_awm_extended_fifo = {
	.fifosize		= 128 * 4,
	.fifohawfsize		= 64 * 4,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 16,
	.datactww_bwocksz	= 11,
	.pwwweg_powewup		= MCI_PWW_UP,
	.f_max			= 100000000,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_WOD,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_awm_extended_fifo_hwfc = {
	.fifosize		= 128 * 4,
	.fifohawfsize		= 64 * 4,
	.cwkweg_enabwe		= MCI_AWM_HWFCEN,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 16,
	.datactww_bwocksz	= 11,
	.pwwweg_powewup		= MCI_PWW_UP,
	.f_max			= 100000000,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_WOD,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_u300 = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg_enabwe		= MCI_ST_U300_HWFCEN,
	.cwkweg_8bit_bus_enabwe = MCI_ST_8BIT_BUS,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 16,
	.datactww_bwocksz	= 11,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio			= twue,
	.pwwweg_powewup		= MCI_PWW_ON,
	.f_max			= 100000000,
	.signaw_diwection	= twue,
	.pwwweg_cwkgate		= twue,
	.pwwweg_nopowew		= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_OD,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_nomadik = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg			= MCI_CWK_ENABWE,
	.cwkweg_8bit_bus_enabwe = MCI_ST_8BIT_BUS,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 24,
	.datactww_bwocksz	= 11,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= twue,
	.st_cwkdiv		= twue,
	.pwwweg_powewup		= MCI_PWW_ON,
	.f_max			= 100000000,
	.signaw_diwection	= twue,
	.pwwweg_cwkgate		= twue,
	.pwwweg_nopowew		= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_OD,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_ux500 = {
	.fifosize		= 30 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg			= MCI_CWK_ENABWE,
	.cwkweg_enabwe		= MCI_ST_UX500_HWFCEN,
	.cwkweg_8bit_bus_enabwe = MCI_ST_8BIT_BUS,
	.cwkweg_neg_edge_enabwe	= MCI_ST_UX500_NEG_EDGE,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datawength_bits	= 24,
	.datactww_bwocksz	= 11,
	.datactww_any_bwocksz	= twue,
	.dma_powew_of_2		= twue,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= twue,
	.st_cwkdiv		= twue,
	.pwwweg_powewup		= MCI_PWW_ON,
	.f_max			= 100000000,
	.signaw_diwection	= twue,
	.pwwweg_cwkgate		= twue,
	.busy_detect		= twue,
	.busy_dpsm_fwag		= MCI_DPSM_ST_BUSYMODE,
	.busy_detect_fwag	= MCI_ST_CAWDBUSY,
	.busy_detect_mask	= MCI_ST_BUSYENDMASK,
	.pwwweg_nopowew		= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_OD,
	.init			= ux500_vawiant_init,
};

static stwuct vawiant_data vawiant_ux500v2 = {
	.fifosize		= 30 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg			= MCI_CWK_ENABWE,
	.cwkweg_enabwe		= MCI_ST_UX500_HWFCEN,
	.cwkweg_8bit_bus_enabwe = MCI_ST_8BIT_BUS,
	.cwkweg_neg_edge_enabwe	= MCI_ST_UX500_NEG_EDGE,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.datactww_mask_ddwmode	= MCI_DPSM_ST_DDWMODE,
	.datawength_bits	= 24,
	.datactww_bwocksz	= 11,
	.datactww_any_bwocksz	= twue,
	.dma_powew_of_2		= twue,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= twue,
	.st_cwkdiv		= twue,
	.pwwweg_powewup		= MCI_PWW_ON,
	.f_max			= 100000000,
	.signaw_diwection	= twue,
	.pwwweg_cwkgate		= twue,
	.busy_detect		= twue,
	.busy_dpsm_fwag		= MCI_DPSM_ST_BUSYMODE,
	.busy_detect_fwag	= MCI_ST_CAWDBUSY,
	.busy_detect_mask	= MCI_ST_BUSYENDMASK,
	.pwwweg_nopowew		= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_OD,
	.init			= ux500v2_vawiant_init,
};

static stwuct vawiant_data vawiant_stm32 = {
	.fifosize		= 32 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg			= MCI_CWK_ENABWE,
	.cwkweg_enabwe		= MCI_ST_UX500_HWFCEN,
	.cwkweg_8bit_bus_enabwe = MCI_ST_8BIT_BUS,
	.cwkweg_neg_edge_enabwe	= MCI_ST_UX500_NEG_EDGE,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.datawength_bits	= 24,
	.datactww_bwocksz	= 11,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= twue,
	.st_cwkdiv		= twue,
	.pwwweg_powewup		= MCI_PWW_ON,
	.f_max			= 48000000,
	.pwwweg_cwkgate		= twue,
	.pwwweg_nopowew		= twue,
	.dma_fwow_contwowwew	= twue,
	.init			= mmci_vawiant_init,
};

static stwuct vawiant_data vawiant_stm32_sdmmc = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.f_max			= 208000000,
	.stm32_cwkdiv		= twue,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_STM32_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_STM32_WWSP_CWC,
	.cmdweg_swsp_cwc	= MCI_CPSM_STM32_SWSP_CWC,
	.cmdweg_swsp		= MCI_CPSM_STM32_SWSP,
	.cmdweg_stop		= MCI_CPSM_STM32_CMDSTOP,
	.data_cmd_enabwe	= MCI_CPSM_STM32_CMDTWANS,
	.iwq_pio_mask		= MCI_IWQ_PIO_STM32_MASK,
	.datactww_fiwst		= twue,
	.datacnt_usewess	= twue,
	.datawength_bits	= 25,
	.datactww_bwocksz	= 14,
	.datactww_any_bwocksz	= twue,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.stm32_idmabsize_mask	= GENMASK(12, 5),
	.stm32_idmabsize_awign	= BIT(5),
	.suppowts_sdio_iwq	= twue,
	.busy_timeout		= twue,
	.busy_detect		= twue,
	.busy_detect_fwag	= MCI_STM32_BUSYD0,
	.busy_detect_mask	= MCI_STM32_BUSYD0ENDMASK,
	.init			= sdmmc_vawiant_init,
};

static stwuct vawiant_data vawiant_stm32_sdmmcv2 = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.f_max			= 267000000,
	.stm32_cwkdiv		= twue,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_STM32_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_STM32_WWSP_CWC,
	.cmdweg_swsp_cwc	= MCI_CPSM_STM32_SWSP_CWC,
	.cmdweg_swsp		= MCI_CPSM_STM32_SWSP,
	.cmdweg_stop		= MCI_CPSM_STM32_CMDSTOP,
	.data_cmd_enabwe	= MCI_CPSM_STM32_CMDTWANS,
	.iwq_pio_mask		= MCI_IWQ_PIO_STM32_MASK,
	.datactww_fiwst		= twue,
	.datacnt_usewess	= twue,
	.datawength_bits	= 25,
	.datactww_bwocksz	= 14,
	.datactww_any_bwocksz	= twue,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.stm32_idmabsize_mask	= GENMASK(16, 5),
	.stm32_idmabsize_awign	= BIT(5),
	.suppowts_sdio_iwq	= twue,
	.dma_wwi		= twue,
	.busy_timeout		= twue,
	.busy_detect		= twue,
	.busy_detect_fwag	= MCI_STM32_BUSYD0,
	.busy_detect_mask	= MCI_STM32_BUSYD0ENDMASK,
	.init			= sdmmc_vawiant_init,
};

static stwuct vawiant_data vawiant_stm32_sdmmcv3 = {
	.fifosize		= 256 * 4,
	.fifohawfsize		= 128 * 4,
	.f_max			= 267000000,
	.stm32_cwkdiv		= twue,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_STM32_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_STM32_WWSP_CWC,
	.cmdweg_swsp_cwc	= MCI_CPSM_STM32_SWSP_CWC,
	.cmdweg_swsp		= MCI_CPSM_STM32_SWSP,
	.cmdweg_stop		= MCI_CPSM_STM32_CMDSTOP,
	.data_cmd_enabwe	= MCI_CPSM_STM32_CMDTWANS,
	.iwq_pio_mask		= MCI_IWQ_PIO_STM32_MASK,
	.datactww_fiwst		= twue,
	.datacnt_usewess	= twue,
	.datawength_bits	= 25,
	.datactww_bwocksz	= 14,
	.datactww_any_bwocksz	= twue,
	.datactww_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.stm32_idmabsize_mask	= GENMASK(16, 6),
	.stm32_idmabsize_awign	= BIT(6),
	.suppowts_sdio_iwq	= twue,
	.dma_wwi		= twue,
	.busy_timeout		= twue,
	.busy_detect		= twue,
	.busy_detect_fwag	= MCI_STM32_BUSYD0,
	.busy_detect_mask	= MCI_STM32_BUSYD0ENDMASK,
	.init			= sdmmc_vawiant_init,
};

static stwuct vawiant_data vawiant_qcom = {
	.fifosize		= 16 * 4,
	.fifohawfsize		= 8 * 4,
	.cwkweg			= MCI_CWK_ENABWE,
	.cwkweg_enabwe		= MCI_QCOM_CWK_FWOWENA |
				  MCI_QCOM_CWK_SEWECT_IN_FBCWK,
	.cwkweg_8bit_bus_enabwe = MCI_QCOM_CWK_WIDEBUS_8,
	.datactww_mask_ddwmode	= MCI_QCOM_CWK_SEWECT_IN_DDW_MODE,
	.cmdweg_cpsm_enabwe	= MCI_CPSM_ENABWE,
	.cmdweg_wwsp_cwc	= MCI_CPSM_WESPONSE | MCI_CPSM_WONGWSP,
	.cmdweg_swsp_cwc	= MCI_CPSM_WESPONSE,
	.cmdweg_swsp		= MCI_CPSM_WESPONSE,
	.data_cmd_enabwe	= MCI_CPSM_QCOM_DATCMD,
	.datawength_bits	= 24,
	.datactww_bwocksz	= 11,
	.datactww_any_bwocksz	= twue,
	.pwwweg_powewup		= MCI_PWW_UP,
	.f_max			= 208000000,
	.expwicit_mcwk_contwow	= twue,
	.qcom_fifo		= twue,
	.qcom_dmw		= twue,
	.mmcimask1		= twue,
	.iwq_pio_mask		= MCI_IWQ_PIO_MASK,
	.stawt_eww		= MCI_STAWTBITEWW,
	.opendwain		= MCI_WOD,
	.init			= qcom_vawiant_init,
};

/* Busy detection fow the ST Micwo vawiant */
static int mmci_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	int busy = 0;

	spin_wock_iwqsave(&host->wock, fwags);
	if (weadw(host->base + MMCISTATUS) & host->vawiant->busy_detect_fwag)
		busy = 1;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn busy;
}

static void mmci_weg_deway(stwuct mmci_host *host)
{
	/*
	 * Accowding to the spec, at weast thwee feedback cwock cycwes
	 * of max 52 MHz must pass between two wwites to the MMCICWOCK weg.
	 * Thwee MCWK cwock cycwes must pass between two MMCIPOWEW weg wwites.
	 * Wowst deway time duwing cawd init is at 100 kHz => 30 us.
	 * Wowst deway time when up and wunning is at 25 MHz => 120 ns.
	 */
	if (host->ccwk < 25000000)
		udeway(30);
	ewse
		ndeway(120);
}

/*
 * This must be cawwed with host->wock hewd
 */
void mmci_wwite_cwkweg(stwuct mmci_host *host, u32 cwk)
{
	if (host->cwk_weg != cwk) {
		host->cwk_weg = cwk;
		wwitew(cwk, host->base + MMCICWOCK);
	}
}

/*
 * This must be cawwed with host->wock hewd
 */
void mmci_wwite_pwwweg(stwuct mmci_host *host, u32 pww)
{
	if (host->pww_weg != pww) {
		host->pww_weg = pww;
		wwitew(pww, host->base + MMCIPOWEW);
	}
}

/*
 * This must be cawwed with host->wock hewd
 */
static void mmci_wwite_datactwwweg(stwuct mmci_host *host, u32 datactww)
{
	/* Keep busy mode in DPSM and SDIO mask if enabwed */
	datactww |= host->datactww_weg & (host->vawiant->busy_dpsm_fwag |
					  host->vawiant->datactww_mask_sdio);

	if (host->datactww_weg != datactww) {
		host->datactww_weg = datactww;
		wwitew(datactww, host->base + MMCIDATACTWW);
	}
}

/*
 * This must be cawwed with host->wock hewd
 */
static void mmci_set_cwkweg(stwuct mmci_host *host, unsigned int desiwed)
{
	stwuct vawiant_data *vawiant = host->vawiant;
	u32 cwk = vawiant->cwkweg;

	/* Make suwe ccwk wefwects the cuwwent cawcuwated cwock */
	host->ccwk = 0;

	if (desiwed) {
		if (vawiant->expwicit_mcwk_contwow) {
			host->ccwk = host->mcwk;
		} ewse if (desiwed >= host->mcwk) {
			cwk = MCI_CWK_BYPASS;
			if (vawiant->st_cwkdiv)
				cwk |= MCI_ST_UX500_NEG_EDGE;
			host->ccwk = host->mcwk;
		} ewse if (vawiant->st_cwkdiv) {
			/*
			 * DB8500 TWM says f = mcwk / (cwkdiv + 2)
			 * => cwkdiv = (mcwk / f) - 2
			 * Wound the dividew up so we don't exceed the max
			 * fwequency
			 */
			cwk = DIV_WOUND_UP(host->mcwk, desiwed) - 2;
			if (cwk >= 256)
				cwk = 255;
			host->ccwk = host->mcwk / (cwk + 2);
		} ewse {
			/*
			 * PW180 TWM says f = mcwk / (2 * (cwkdiv + 1))
			 * => cwkdiv = mcwk / (2 * f) - 1
			 */
			cwk = host->mcwk / (2 * desiwed) - 1;
			if (cwk >= 256)
				cwk = 255;
			host->ccwk = host->mcwk / (2 * (cwk + 1));
		}

		cwk |= vawiant->cwkweg_enabwe;
		cwk |= MCI_CWK_ENABWE;
		/* This hasn't pwoven to be wowthwhiwe */
		/* cwk |= MCI_CWK_PWWSAVE; */
	}

	/* Set actuaw cwock fow debug */
	host->mmc->actuaw_cwock = host->ccwk;

	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		cwk |= MCI_4BIT_BUS;
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		cwk |= vawiant->cwkweg_8bit_bus_enabwe;

	if (host->mmc->ios.timing == MMC_TIMING_UHS_DDW50 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_DDW52)
		cwk |= vawiant->cwkweg_neg_edge_enabwe;

	mmci_wwite_cwkweg(host, cwk);
}

static void mmci_dma_wewease(stwuct mmci_host *host)
{
	if (host->ops && host->ops->dma_wewease)
		host->ops->dma_wewease(host);

	host->use_dma = fawse;
}

static void mmci_dma_setup(stwuct mmci_host *host)
{
	if (!host->ops || !host->ops->dma_setup)
		wetuwn;

	if (host->ops->dma_setup(host))
		wetuwn;

	/* initiawize pwe wequest cookie */
	host->next_cookie = 1;

	host->use_dma = twue;
}

/*
 * Vawidate mmc pwewequisites
 */
static int mmci_vawidate_data(stwuct mmci_host *host,
			      stwuct mmc_data *data)
{
	stwuct vawiant_data *vawiant = host->vawiant;

	if (!data)
		wetuwn 0;
	if (!is_powew_of_2(data->bwksz) && !vawiant->datactww_any_bwocksz) {
		dev_eww(mmc_dev(host->mmc),
			"unsuppowted bwock size (%d bytes)\n", data->bwksz);
		wetuwn -EINVAW;
	}

	if (host->ops && host->ops->vawidate_data)
		wetuwn host->ops->vawidate_data(host, data);

	wetuwn 0;
}

static int mmci_pwep_data(stwuct mmci_host *host, stwuct mmc_data *data, boow next)
{
	int eww;

	if (!host->ops || !host->ops->pwep_data)
		wetuwn 0;

	eww = host->ops->pwep_data(host, data, next);

	if (next && !eww)
		data->host_cookie = ++host->next_cookie < 0 ?
			1 : host->next_cookie;

	wetuwn eww;
}

static void mmci_unpwep_data(stwuct mmci_host *host, stwuct mmc_data *data,
		      int eww)
{
	if (host->ops && host->ops->unpwep_data)
		host->ops->unpwep_data(host, data, eww);

	data->host_cookie = 0;
}

static void mmci_get_next_data(stwuct mmci_host *host, stwuct mmc_data *data)
{
	WAWN_ON(data->host_cookie && data->host_cookie != host->next_cookie);

	if (host->ops && host->ops->get_next_data)
		host->ops->get_next_data(host, data);
}

static int mmci_dma_stawt(stwuct mmci_host *host, unsigned int datactww)
{
	stwuct mmc_data *data = host->data;
	int wet;

	if (!host->use_dma)
		wetuwn -EINVAW;

	wet = mmci_pwep_data(host, data, fawse);
	if (wet)
		wetuwn wet;

	if (!host->ops || !host->ops->dma_stawt)
		wetuwn -EINVAW;

	/* Okay, go fow it. */
	dev_vdbg(mmc_dev(host->mmc),
		 "Submit MMCI DMA job, sgwen %d bwksz %04x bwks %04x fwags %08x\n",
		 data->sg_wen, data->bwksz, data->bwocks, data->fwags);

	wet = host->ops->dma_stawt(host, &datactww);
	if (wet)
		wetuwn wet;

	/* Twiggew the DMA twansfew */
	mmci_wwite_datactwwweg(host, datactww);

	/*
	 * Wet the MMCI say when the data is ended and it's time
	 * to fiwe next DMA wequest. When that happens, MMCI wiww
	 * caww mmci_data_end()
	 */
	wwitew(weadw(host->base + MMCIMASK0) | MCI_DATAENDMASK,
	       host->base + MMCIMASK0);
	wetuwn 0;
}

static void mmci_dma_finawize(stwuct mmci_host *host, stwuct mmc_data *data)
{
	if (!host->use_dma)
		wetuwn;

	if (host->ops && host->ops->dma_finawize)
		host->ops->dma_finawize(host, data);
}

static void mmci_dma_ewwow(stwuct mmci_host *host)
{
	if (!host->use_dma)
		wetuwn;

	if (host->ops && host->ops->dma_ewwow)
		host->ops->dma_ewwow(host);
}

static void
mmci_wequest_end(stwuct mmci_host *host, stwuct mmc_wequest *mwq)
{
	wwitew(0, host->base + MMCICOMMAND);

	BUG_ON(host->data);

	host->mwq = NUWW;
	host->cmd = NUWW;

	mmc_wequest_done(host->mmc, mwq);
}

static void mmci_set_mask1(stwuct mmci_host *host, unsigned int mask)
{
	void __iomem *base = host->base;
	stwuct vawiant_data *vawiant = host->vawiant;

	if (host->singweiwq) {
		unsigned int mask0 = weadw(base + MMCIMASK0);

		mask0 &= ~vawiant->iwq_pio_mask;
		mask0 |= mask;

		wwitew(mask0, base + MMCIMASK0);
	}

	if (vawiant->mmcimask1)
		wwitew(mask, base + MMCIMASK1);

	host->mask1_weg = mask;
}

static void mmci_stop_data(stwuct mmci_host *host)
{
	mmci_wwite_datactwwweg(host, 0);
	mmci_set_mask1(host, 0);
	host->data = NUWW;
}

static void mmci_init_sg(stwuct mmci_host *host, stwuct mmc_data *data)
{
	unsigned int fwags = SG_MITEW_ATOMIC;

	if (data->fwags & MMC_DATA_WEAD)
		fwags |= SG_MITEW_TO_SG;
	ewse
		fwags |= SG_MITEW_FWOM_SG;

	sg_mitew_stawt(&host->sg_mitew, data->sg, data->sg_wen, fwags);
}

static u32 mmci_get_dctww_cfg(stwuct mmci_host *host)
{
	wetuwn MCI_DPSM_ENABWE | mmci_dctww_bwksz(host);
}

static u32 ux500v2_get_dctww_cfg(stwuct mmci_host *host)
{
	wetuwn MCI_DPSM_ENABWE | (host->data->bwksz << 16);
}

static void ux500_busy_cweaw_mask_done(stwuct mmci_host *host)
{
	void __iomem *base = host->base;

	wwitew(host->vawiant->busy_detect_mask, base + MMCICWEAW);
	wwitew(weadw(base + MMCIMASK0) &
	       ~host->vawiant->busy_detect_mask, base + MMCIMASK0);
	host->busy_state = MMCI_BUSY_DONE;
	host->busy_status = 0;
}

/*
 * ux500_busy_compwete() - this wiww wait untiw the busy status
 * goes off, saving any status that occuw in the meantime into
 * host->busy_status untiw we know the cawd is not busy any mowe.
 * The function wetuwns twue when the busy detection is ended
 * and we shouwd continue pwocessing the command.
 *
 * The Ux500 typicawwy fiwes two IWQs ovew a busy cycwe wike this:
 *
 *  DAT0 busy          +-----------------+
 *                     |                 |
 *  DAT0 not busy  ----+                 +--------
 *
 *                     ^                 ^
 *                     |                 |
 *                    IWQ1              IWQ2
 */
static boow ux500_busy_compwete(stwuct mmci_host *host, stwuct mmc_command *cmd,
				u32 status, u32 eww_msk)
{
	void __iomem *base = host->base;
	int wetwies = 10;

	if (status & eww_msk) {
		/* Stop any ongoing busy detection if an ewwow occuws */
		ux500_busy_cweaw_mask_done(host);
		goto out_wet_state;
	}

	/*
	 * The state twansitions awe encoded in a state machine cwossing
	 * the edges in this switch statement.
	 */
	switch (host->busy_state) {

	/*
	 * Befowe unmasking fow the busy end IWQ, confiwm that the
	 * command was sent successfuwwy. To keep twack of having a
	 * command in-pwogwess, waiting fow busy signawing to end,
	 * stowe the status in host->busy_status.
	 *
	 * Note that, the cawd may need a coupwe of cwock cycwes befowe
	 * it stawts signawing busy on DAT0, hence we-wead the
	 * MMCISTATUS wegistew hewe, to awwow the busy bit to be set.
	 */
	case MMCI_BUSY_DONE:
		/*
		 * Save the fiwst status wegistew wead to be suwe to catch
		 * aww bits that may be wost wiww wetwying. If the command
		 * is stiww busy this wiww wesuwt in assigning 0 to
		 * host->busy_status, which is what it shouwd be in IDWE.
		 */
		host->busy_status = status & (MCI_CMDSENT | MCI_CMDWESPEND);
		whiwe (wetwies) {
			status = weadw(base + MMCISTATUS);
			/* Keep accumuwating status bits */
			host->busy_status |= status & (MCI_CMDSENT | MCI_CMDWESPEND);
			if (status & host->vawiant->busy_detect_fwag) {
				wwitew(weadw(base + MMCIMASK0) |
				       host->vawiant->busy_detect_mask,
				       base + MMCIMASK0);
				host->busy_state = MMCI_BUSY_WAITING_FOW_STAWT_IWQ;
				scheduwe_dewayed_wowk(&host->ux500_busy_timeout_wowk,
				      msecs_to_jiffies(cmd->busy_timeout));
				goto out_wet_state;
			}
			wetwies--;
		}
		dev_dbg(mmc_dev(host->mmc),
			"no busy signawwing in time CMD%02x\n", cmd->opcode);
		ux500_busy_cweaw_mask_done(host);
		bweak;

	/*
	 * If thewe is a command in-pwogwess that has been successfuwwy
	 * sent, then baiw out if busy status is set and wait fow the
	 * busy end IWQ.
	 *
	 * Note that, the HW twiggews an IWQ on both edges whiwe
	 * monitowing DAT0 fow busy compwetion, but thewe is onwy one
	 * status bit in MMCISTATUS fow the busy state. Thewefowe
	 * both the stawt and the end intewwupts needs to be cweawed,
	 * one aftew the othew. So, cweaw the busy stawt IWQ hewe.
	 */
	case MMCI_BUSY_WAITING_FOW_STAWT_IWQ:
		if (status & host->vawiant->busy_detect_fwag) {
			host->busy_status |= status & (MCI_CMDSENT | MCI_CMDWESPEND);
			wwitew(host->vawiant->busy_detect_mask, base + MMCICWEAW);
			host->busy_state = MMCI_BUSY_WAITING_FOW_END_IWQ;
		} ewse {
			dev_dbg(mmc_dev(host->mmc),
				"wost busy status when waiting fow busy stawt IWQ CMD%02x\n",
				cmd->opcode);
			cancew_dewayed_wowk(&host->ux500_busy_timeout_wowk);
			ux500_busy_cweaw_mask_done(host);
		}
		bweak;

	case MMCI_BUSY_WAITING_FOW_END_IWQ:
		if (!(status & host->vawiant->busy_detect_fwag)) {
			host->busy_status |= status & (MCI_CMDSENT | MCI_CMDWESPEND);
			wwitew(host->vawiant->busy_detect_mask, base + MMCICWEAW);
			cancew_dewayed_wowk(&host->ux500_busy_timeout_wowk);
			ux500_busy_cweaw_mask_done(host);
		} ewse {
			dev_dbg(mmc_dev(host->mmc),
				"busy status stiww assewted when handwing busy end IWQ - wiww keep waiting CMD%02x\n",
				cmd->opcode);
		}
		bweak;

	defauwt:
		dev_dbg(mmc_dev(host->mmc), "feww thwough on state %d, CMD%02x\n",
			host->busy_state, cmd->opcode);
		bweak;
	}

out_wet_state:
	wetuwn (host->busy_state == MMCI_BUSY_DONE);
}

/*
 * Aww the DMA opewation mode stuff goes inside this ifdef.
 * This assumes that you have a genewic DMA device intewface,
 * no custom DMA intewfaces awe suppowted.
 */
#ifdef CONFIG_DMA_ENGINE
stwuct mmci_dmae_next {
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_chan	*chan;
};

stwuct mmci_dmae_pwiv {
	stwuct dma_chan	*cuw;
	stwuct dma_chan	*wx_channew;
	stwuct dma_chan	*tx_channew;
	stwuct dma_async_tx_descwiptow	*desc_cuwwent;
	stwuct mmci_dmae_next next_data;
};

int mmci_dmae_setup(stwuct mmci_host *host)
{
	const chaw *wxname, *txname;
	stwuct mmci_dmae_pwiv *dmae;

	dmae = devm_kzawwoc(mmc_dev(host->mmc), sizeof(*dmae), GFP_KEWNEW);
	if (!dmae)
		wetuwn -ENOMEM;

	host->dma_pwiv = dmae;

	dmae->wx_channew = dma_wequest_chan(mmc_dev(host->mmc), "wx");
	if (IS_EWW(dmae->wx_channew)) {
		int wet = PTW_EWW(dmae->wx_channew);
		dmae->wx_channew = NUWW;
		wetuwn wet;
	}

	dmae->tx_channew = dma_wequest_chan(mmc_dev(host->mmc), "tx");
	if (IS_EWW(dmae->tx_channew)) {
		if (PTW_EWW(dmae->tx_channew) == -EPWOBE_DEFEW)
			dev_wawn(mmc_dev(host->mmc),
				 "Defewwed pwobe fow TX channew ignowed\n");
		dmae->tx_channew = NUWW;
	}

	/*
	 * If onwy an WX channew is specified, the dwivew wiww
	 * attempt to use it bidiwectionawwy, howevew if it
	 * is specified but cannot be wocated, DMA wiww be disabwed.
	 */
	if (dmae->wx_channew && !dmae->tx_channew)
		dmae->tx_channew = dmae->wx_channew;

	if (dmae->wx_channew)
		wxname = dma_chan_name(dmae->wx_channew);
	ewse
		wxname = "none";

	if (dmae->tx_channew)
		txname = dma_chan_name(dmae->tx_channew);
	ewse
		txname = "none";

	dev_info(mmc_dev(host->mmc), "DMA channews WX %s, TX %s\n",
		 wxname, txname);

	/*
	 * Wimit the maximum segment size in any SG entwy accowding to
	 * the pawametews of the DMA engine device.
	 */
	if (dmae->tx_channew) {
		stwuct device *dev = dmae->tx_channew->device->dev;
		unsigned int max_seg_size = dma_get_max_seg_size(dev);

		if (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	}
	if (dmae->wx_channew) {
		stwuct device *dev = dmae->wx_channew->device->dev;
		unsigned int max_seg_size = dma_get_max_seg_size(dev);

		if (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	}

	if (!dmae->tx_channew || !dmae->wx_channew) {
		mmci_dmae_wewease(host);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * This is used in ow so inwine it
 * so it can be discawded.
 */
void mmci_dmae_wewease(stwuct mmci_host *host)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;

	if (dmae->wx_channew)
		dma_wewease_channew(dmae->wx_channew);
	if (dmae->tx_channew)
		dma_wewease_channew(dmae->tx_channew);
	dmae->wx_channew = dmae->tx_channew = NUWW;
}

static void mmci_dma_unmap(stwuct mmci_host *host, stwuct mmc_data *data)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	stwuct dma_chan *chan;

	if (data->fwags & MMC_DATA_WEAD)
		chan = dmae->wx_channew;
	ewse
		chan = dmae->tx_channew;

	dma_unmap_sg(chan->device->dev, data->sg, data->sg_wen,
		     mmc_get_dma_diw(data));
}

void mmci_dmae_ewwow(stwuct mmci_host *host)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;

	if (!dma_inpwogwess(host))
		wetuwn;

	dev_eww(mmc_dev(host->mmc), "ewwow duwing DMA twansfew!\n");
	dmaengine_tewminate_aww(dmae->cuw);
	host->dma_in_pwogwess = fawse;
	dmae->cuw = NUWW;
	dmae->desc_cuwwent = NUWW;
	host->data->host_cookie = 0;

	mmci_dma_unmap(host, host->data);
}

void mmci_dmae_finawize(stwuct mmci_host *host, stwuct mmc_data *data)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	u32 status;
	int i;

	if (!dma_inpwogwess(host))
		wetuwn;

	/* Wait up to 1ms fow the DMA to compwete */
	fow (i = 0; ; i++) {
		status = weadw(host->base + MMCISTATUS);
		if (!(status & MCI_WXDATAAVWBWMASK) || i >= 100)
			bweak;
		udeway(10);
	}

	/*
	 * Check to see whethew we stiww have some data weft in the FIFO -
	 * this catches DMA contwowwews which awe unabwe to monitow the
	 * DMAWBWEQ and DMAWSWEQ signaws whiwe awwowing us to DMA to non-
	 * contiguous buffews.  On TX, we'ww get a FIFO undewwun ewwow.
	 */
	if (status & MCI_WXDATAAVWBWMASK) {
		mmci_dma_ewwow(host);
		if (!data->ewwow)
			data->ewwow = -EIO;
	} ewse if (!data->host_cookie) {
		mmci_dma_unmap(host, data);
	}

	/*
	 * Use of DMA with scattew-gathew is impossibwe.
	 * Give up with DMA and switch back to PIO mode.
	 */
	if (status & MCI_WXDATAAVWBWMASK) {
		dev_eww(mmc_dev(host->mmc), "buggy DMA detected. Taking evasive action.\n");
		mmci_dma_wewease(host);
	}

	host->dma_in_pwogwess = fawse;
	dmae->cuw = NUWW;
	dmae->desc_cuwwent = NUWW;
}

/* pwepawes DMA channew and DMA descwiptow, wetuwns non-zewo on faiwuwe */
static int _mmci_dmae_pwep_data(stwuct mmci_host *host, stwuct mmc_data *data,
				stwuct dma_chan **dma_chan,
				stwuct dma_async_tx_descwiptow **dma_desc)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	stwuct vawiant_data *vawiant = host->vawiant;
	stwuct dma_swave_config conf = {
		.swc_addw = host->phybase + MMCIFIFO,
		.dst_addw = host->phybase + MMCIFIFO,
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.swc_maxbuwst = vawiant->fifohawfsize >> 2, /* # of wowds */
		.dst_maxbuwst = vawiant->fifohawfsize >> 2, /* # of wowds */
		.device_fc = vawiant->dma_fwow_contwowwew,
	};
	stwuct dma_chan *chan;
	stwuct dma_device *device;
	stwuct dma_async_tx_descwiptow *desc;
	int nw_sg;
	unsigned wong fwags = DMA_CTWW_ACK;

	if (data->fwags & MMC_DATA_WEAD) {
		conf.diwection = DMA_DEV_TO_MEM;
		chan = dmae->wx_channew;
	} ewse {
		conf.diwection = DMA_MEM_TO_DEV;
		chan = dmae->tx_channew;
	}

	/* If thewe's no DMA channew, faww back to PIO */
	if (!chan)
		wetuwn -EINVAW;

	/* If wess than ow equaw to the fifo size, don't bothew with DMA */
	if (data->bwksz * data->bwocks <= vawiant->fifosize)
		wetuwn -EINVAW;

	/*
	 * This is necessawy to get SDIO wowking on the Ux500. We do not yet
	 * know if this is a bug in:
	 * - The Ux500 DMA contwowwew (DMA40)
	 * - The MMCI DMA intewface on the Ux500
	 * some powew of two bwocks (such as 64 bytes) awe sent weguwawwy
	 * duwing SDIO twaffic and those wowk fine so fow these we enabwe DMA
	 * twansfews.
	 */
	if (host->vawiant->dma_powew_of_2 && !is_powew_of_2(data->bwksz))
		wetuwn -EINVAW;

	device = chan->device;
	nw_sg = dma_map_sg(device->dev, data->sg, data->sg_wen,
			   mmc_get_dma_diw(data));
	if (nw_sg == 0)
		wetuwn -EINVAW;

	if (host->vawiant->qcom_dmw)
		fwags |= DMA_PWEP_INTEWWUPT;

	dmaengine_swave_config(chan, &conf);
	desc = dmaengine_pwep_swave_sg(chan, data->sg, nw_sg,
					    conf.diwection, fwags);
	if (!desc)
		goto unmap_exit;

	*dma_chan = chan;
	*dma_desc = desc;

	wetuwn 0;

 unmap_exit:
	dma_unmap_sg(device->dev, data->sg, data->sg_wen,
		     mmc_get_dma_diw(data));
	wetuwn -ENOMEM;
}

int mmci_dmae_pwep_data(stwuct mmci_host *host,
			stwuct mmc_data *data,
			boow next)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	stwuct mmci_dmae_next *nd = &dmae->next_data;

	if (!host->use_dma)
		wetuwn -EINVAW;

	if (next)
		wetuwn _mmci_dmae_pwep_data(host, data, &nd->chan, &nd->desc);
	/* Check if next job is awweady pwepawed. */
	if (dmae->cuw && dmae->desc_cuwwent)
		wetuwn 0;

	/* No job wewe pwepawed thus do it now. */
	wetuwn _mmci_dmae_pwep_data(host, data, &dmae->cuw,
				    &dmae->desc_cuwwent);
}

int mmci_dmae_stawt(stwuct mmci_host *host, unsigned int *datactww)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	int wet;

	host->dma_in_pwogwess = twue;
	wet = dma_submit_ewwow(dmaengine_submit(dmae->desc_cuwwent));
	if (wet < 0) {
		host->dma_in_pwogwess = fawse;
		wetuwn wet;
	}
	dma_async_issue_pending(dmae->cuw);

	*datactww |= MCI_DPSM_DMAENABWE;

	wetuwn 0;
}

void mmci_dmae_get_next_data(stwuct mmci_host *host, stwuct mmc_data *data)
{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;
	stwuct mmci_dmae_next *next = &dmae->next_data;

	if (!host->use_dma)
		wetuwn;

	WAWN_ON(!data->host_cookie && (next->desc || next->chan));

	dmae->desc_cuwwent = next->desc;
	dmae->cuw = next->chan;
	next->desc = NUWW;
	next->chan = NUWW;
}

void mmci_dmae_unpwep_data(stwuct mmci_host *host,
			   stwuct mmc_data *data, int eww)

{
	stwuct mmci_dmae_pwiv *dmae = host->dma_pwiv;

	if (!host->use_dma)
		wetuwn;

	mmci_dma_unmap(host, data);

	if (eww) {
		stwuct mmci_dmae_next *next = &dmae->next_data;
		stwuct dma_chan *chan;
		if (data->fwags & MMC_DATA_WEAD)
			chan = dmae->wx_channew;
		ewse
			chan = dmae->tx_channew;
		dmaengine_tewminate_aww(chan);

		if (dmae->desc_cuwwent == next->desc)
			dmae->desc_cuwwent = NUWW;

		if (dmae->cuw == next->chan) {
			host->dma_in_pwogwess = fawse;
			dmae->cuw = NUWW;
		}

		next->desc = NUWW;
		next->chan = NUWW;
	}
}

static stwuct mmci_host_ops mmci_vawiant_ops = {
	.pwep_data = mmci_dmae_pwep_data,
	.unpwep_data = mmci_dmae_unpwep_data,
	.get_datactww_cfg = mmci_get_dctww_cfg,
	.get_next_data = mmci_dmae_get_next_data,
	.dma_setup = mmci_dmae_setup,
	.dma_wewease = mmci_dmae_wewease,
	.dma_stawt = mmci_dmae_stawt,
	.dma_finawize = mmci_dmae_finawize,
	.dma_ewwow = mmci_dmae_ewwow,
};
#ewse
static stwuct mmci_host_ops mmci_vawiant_ops = {
	.get_datactww_cfg = mmci_get_dctww_cfg,
};
#endif

static void mmci_vawiant_init(stwuct mmci_host *host)
{
	host->ops = &mmci_vawiant_ops;
}

static void ux500_vawiant_init(stwuct mmci_host *host)
{
	host->ops = &mmci_vawiant_ops;
	host->ops->busy_compwete = ux500_busy_compwete;
}

static void ux500v2_vawiant_init(stwuct mmci_host *host)
{
	host->ops = &mmci_vawiant_ops;
	host->ops->busy_compwete = ux500_busy_compwete;
	host->ops->get_datactww_cfg = ux500v2_get_dctww_cfg;
}

static void mmci_pwe_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!data)
		wetuwn;

	WAWN_ON(data->host_cookie);

	if (mmci_vawidate_data(host, data))
		wetuwn;

	mmci_pwep_data(host, data, twue);
}

static void mmci_post_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
			      int eww)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!data || !data->host_cookie)
		wetuwn;

	mmci_unpwep_data(host, data, eww);
}

static void mmci_stawt_data(stwuct mmci_host *host, stwuct mmc_data *data)
{
	stwuct vawiant_data *vawiant = host->vawiant;
	unsigned int datactww, timeout, iwqmask;
	unsigned wong wong cwks;
	void __iomem *base;

	dev_dbg(mmc_dev(host->mmc), "bwksz %04x bwks %04x fwags %08x\n",
		data->bwksz, data->bwocks, data->fwags);

	host->data = data;
	host->size = data->bwksz * data->bwocks;
	data->bytes_xfewed = 0;

	cwks = (unsigned wong wong)data->timeout_ns * host->ccwk;
	do_div(cwks, NSEC_PEW_SEC);

	timeout = data->timeout_cwks + (unsigned int)cwks;

	base = host->base;
	wwitew(timeout, base + MMCIDATATIMEW);
	wwitew(host->size, base + MMCIDATAWENGTH);

	datactww = host->ops->get_datactww_cfg(host);
	datactww |= host->data->fwags & MMC_DATA_WEAD ? MCI_DPSM_DIWECTION : 0;

	if (host->mmc->cawd && mmc_cawd_sdio(host->mmc->cawd)) {
		u32 cwk;

		datactww |= vawiant->datactww_mask_sdio;

		/*
		 * The ST Micwo vawiant fow SDIO smaww wwite twansfews
		 * needs to have cwock H/W fwow contwow disabwed,
		 * othewwise the twansfew wiww not stawt. The thweshowd
		 * depends on the wate of MCWK.
		 */
		if (vawiant->st_sdio && data->fwags & MMC_DATA_WWITE &&
		    (host->size < 8 ||
		     (host->size <= 8 && host->mcwk > 50000000)))
			cwk = host->cwk_weg & ~vawiant->cwkweg_enabwe;
		ewse
			cwk = host->cwk_weg | vawiant->cwkweg_enabwe;

		mmci_wwite_cwkweg(host, cwk);
	}

	if (host->mmc->ios.timing == MMC_TIMING_UHS_DDW50 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_DDW52)
		datactww |= vawiant->datactww_mask_ddwmode;

	/*
	 * Attempt to use DMA opewation mode, if this
	 * shouwd faiw, faww back to PIO mode
	 */
	if (!mmci_dma_stawt(host, datactww))
		wetuwn;

	/* IWQ mode, map the SG wist fow CPU weading/wwiting */
	mmci_init_sg(host, data);

	if (data->fwags & MMC_DATA_WEAD) {
		iwqmask = MCI_WXFIFOHAWFFUWWMASK;

		/*
		 * If we have wess than the fifo 'hawf-fuww' thweshowd to
		 * twansfew, twiggew a PIO intewwupt as soon as any data
		 * is avaiwabwe.
		 */
		if (host->size < vawiant->fifohawfsize)
			iwqmask |= MCI_WXDATAAVWBWMASK;
	} ewse {
		/*
		 * We don't actuawwy need to incwude "FIFO empty" hewe
		 * since its impwicit in "FIFO hawf empty".
		 */
		iwqmask = MCI_TXFIFOHAWFEMPTYMASK;
	}

	mmci_wwite_datactwwweg(host, datactww);
	wwitew(weadw(base + MMCIMASK0) & ~MCI_DATAENDMASK, base + MMCIMASK0);
	mmci_set_mask1(host, iwqmask);
}

static void
mmci_stawt_command(stwuct mmci_host *host, stwuct mmc_command *cmd, u32 c)
{
	void __iomem *base = host->base;
	boow busy_wesp = cmd->fwags & MMC_WSP_BUSY;
	unsigned wong wong cwks;

	dev_dbg(mmc_dev(host->mmc), "op %02x awg %08x fwags %08x\n",
	    cmd->opcode, cmd->awg, cmd->fwags);

	if (weadw(base + MMCICOMMAND) & host->vawiant->cmdweg_cpsm_enabwe) {
		wwitew(0, base + MMCICOMMAND);
		mmci_weg_deway(host);
	}

	if (host->vawiant->cmdweg_stop &&
	    cmd->opcode == MMC_STOP_TWANSMISSION)
		c |= host->vawiant->cmdweg_stop;

	c |= cmd->opcode | host->vawiant->cmdweg_cpsm_enabwe;
	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136)
			c |= host->vawiant->cmdweg_wwsp_cwc;
		ewse if (cmd->fwags & MMC_WSP_CWC)
			c |= host->vawiant->cmdweg_swsp_cwc;
		ewse
			c |= host->vawiant->cmdweg_swsp;
	}

	host->busy_status = 0;
	host->busy_state = MMCI_BUSY_DONE;

	/* Assign a defauwt timeout if the cowe does not pwovide one */
	if (busy_wesp && !cmd->busy_timeout)
		cmd->busy_timeout = 10 * MSEC_PEW_SEC;

	if (busy_wesp && host->vawiant->busy_timeout) {
		if (cmd->busy_timeout > host->mmc->max_busy_timeout)
			cwks = (unsigned wong wong)host->mmc->max_busy_timeout * host->ccwk;
		ewse
			cwks = (unsigned wong wong)cmd->busy_timeout * host->ccwk;

		do_div(cwks, MSEC_PEW_SEC);
		wwitew_wewaxed(cwks, host->base + MMCIDATATIMEW);
	}

	if (host->ops->pwe_sig_vowt_switch && cmd->opcode == SD_SWITCH_VOWTAGE)
		host->ops->pwe_sig_vowt_switch(host);

	if (/*intewwupt*/0)
		c |= MCI_CPSM_INTEWWUPT;

	if (mmc_cmd_type(cmd) == MMC_CMD_ADTC)
		c |= host->vawiant->data_cmd_enabwe;

	host->cmd = cmd;

	wwitew(cmd->awg, base + MMCIAWGUMENT);
	wwitew(c, base + MMCICOMMAND);
}

static void mmci_stop_command(stwuct mmci_host *host)
{
	host->stop_abowt.ewwow = 0;
	mmci_stawt_command(host, &host->stop_abowt, 0);
}

static void
mmci_data_iwq(stwuct mmci_host *host, stwuct mmc_data *data,
	      unsigned int status)
{
	unsigned int status_eww;

	/* Make suwe we have data to handwe */
	if (!data)
		wetuwn;

	/* Fiwst check fow ewwows */
	status_eww = status & (host->vawiant->stawt_eww |
			       MCI_DATACWCFAIW | MCI_DATATIMEOUT |
			       MCI_TXUNDEWWUN | MCI_WXOVEWWUN);

	if (status_eww) {
		u32 wemain, success;

		/* Tewminate the DMA twansfew */
		mmci_dma_ewwow(host);

		/*
		 * Cawcuwate how faw we awe into the twansfew.  Note that
		 * the data countew gives the numbew of bytes twansfewwed
		 * on the MMC bus, not on the host side.  On weads, this
		 * can be as much as a FIFO-wowth of data ahead.  This
		 * mattews fow FIFO ovewwuns onwy.
		 */
		if (!host->vawiant->datacnt_usewess) {
			wemain = weadw(host->base + MMCIDATACNT);
			success = data->bwksz * data->bwocks - wemain;
		} ewse {
			success = 0;
		}

		dev_dbg(mmc_dev(host->mmc), "MCI EWWOW IWQ, status 0x%08x at 0x%08x\n",
			status_eww, success);
		if (status_eww & MCI_DATACWCFAIW) {
			/* Wast bwock was not successfuw */
			success -= 1;
			data->ewwow = -EIWSEQ;
		} ewse if (status_eww & MCI_DATATIMEOUT) {
			data->ewwow = -ETIMEDOUT;
		} ewse if (status_eww & MCI_STAWTBITEWW) {
			data->ewwow = -ECOMM;
		} ewse if (status_eww & MCI_TXUNDEWWUN) {
			data->ewwow = -EIO;
		} ewse if (status_eww & MCI_WXOVEWWUN) {
			if (success > host->vawiant->fifosize)
				success -= host->vawiant->fifosize;
			ewse
				success = 0;
			data->ewwow = -EIO;
		}
		data->bytes_xfewed = wound_down(success, data->bwksz);
	}

	if (status & MCI_DATABWOCKEND)
		dev_eww(mmc_dev(host->mmc), "stway MCI_DATABWOCKEND intewwupt\n");

	if (status & MCI_DATAEND || data->ewwow) {
		mmci_dma_finawize(host, data);

		mmci_stop_data(host);

		if (!data->ewwow)
			/* The ewwow cwause is handwed above, success! */
			data->bytes_xfewed = data->bwksz * data->bwocks;

		if (!data->stop) {
			if (host->vawiant->cmdweg_stop && data->ewwow)
				mmci_stop_command(host);
			ewse
				mmci_wequest_end(host, data->mwq);
		} ewse if (host->mwq->sbc && !data->ewwow) {
			mmci_wequest_end(host, data->mwq);
		} ewse {
			mmci_stawt_command(host, data->stop, 0);
		}
	}
}

static void
mmci_cmd_iwq(stwuct mmci_host *host, stwuct mmc_command *cmd,
	     unsigned int status)
{
	u32 eww_msk = MCI_CMDCWCFAIW | MCI_CMDTIMEOUT;
	void __iomem *base = host->base;
	boow sbc, busy_wesp;

	if (!cmd)
		wetuwn;

	sbc = (cmd == host->mwq->sbc);
	busy_wesp = !!(cmd->fwags & MMC_WSP_BUSY);

	/*
	 * We need to be one of these intewwupts to be considewed wowth
	 * handwing. Note that we tag on any watent IWQs postponed
	 * due to waiting fow busy status.
	 */
	if (host->vawiant->busy_timeout && busy_wesp)
		eww_msk |= MCI_DATATIMEOUT;

	if (!((status | host->busy_status) &
	      (eww_msk | MCI_CMDSENT | MCI_CMDWESPEND)))
		wetuwn;

	/* Handwe busy detection on DAT0 if the vawiant suppowts it. */
	if (busy_wesp && host->vawiant->busy_detect)
		if (!host->ops->busy_compwete(host, cmd, status, eww_msk))
			wetuwn;

	host->cmd = NUWW;

	if (status & MCI_CMDTIMEOUT) {
		cmd->ewwow = -ETIMEDOUT;
	} ewse if (status & MCI_CMDCWCFAIW && cmd->fwags & MMC_WSP_CWC) {
		cmd->ewwow = -EIWSEQ;
	} ewse if (host->vawiant->busy_timeout && busy_wesp &&
		   status & MCI_DATATIMEOUT) {
		cmd->ewwow = -ETIMEDOUT;
		/*
		 * This wiww wake up mmci_iwq_thwead() which wiww issue
		 * a hawdwawe weset of the MMCI bwock.
		 */
		host->iwq_action = IWQ_WAKE_THWEAD;
	} ewse {
		cmd->wesp[0] = weadw(base + MMCIWESPONSE0);
		cmd->wesp[1] = weadw(base + MMCIWESPONSE1);
		cmd->wesp[2] = weadw(base + MMCIWESPONSE2);
		cmd->wesp[3] = weadw(base + MMCIWESPONSE3);
	}

	if ((!sbc && !cmd->data) || cmd->ewwow) {
		if (host->data) {
			/* Tewminate the DMA twansfew */
			mmci_dma_ewwow(host);

			mmci_stop_data(host);
			if (host->vawiant->cmdweg_stop && cmd->ewwow) {
				mmci_stop_command(host);
				wetuwn;
			}
		}

		if (host->iwq_action != IWQ_WAKE_THWEAD)
			mmci_wequest_end(host, host->mwq);

	} ewse if (sbc) {
		mmci_stawt_command(host, host->mwq->cmd, 0);
	} ewse if (!host->vawiant->datactww_fiwst &&
		   !(cmd->data->fwags & MMC_DATA_WEAD)) {
		mmci_stawt_data(host, cmd->data);
	}
}

static chaw *ux500_state_stw(stwuct mmci_host *host)
{
	switch (host->busy_state) {
	case MMCI_BUSY_WAITING_FOW_STAWT_IWQ:
		wetuwn "waiting fow stawt IWQ";
	case MMCI_BUSY_WAITING_FOW_END_IWQ:
		wetuwn "waiting fow end IWQ";
	case MMCI_BUSY_DONE:
		wetuwn "not waiting fow IWQs";
	defauwt:
		wetuwn "unknown";
	}
}

/*
 * This busy timeout wowkew is used to "kick" the command IWQ if a
 * busy detect IWQ faiws to appeaw in weasonabwe time. Onwy used on
 * vawiants with busy detection IWQ dewivewy.
 */
static void ux500_busy_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mmci_host *host = containew_of(wowk, stwuct mmci_host,
					ux500_busy_timeout_wowk.wowk);
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->cmd) {
		/* If we awe stiww busy wet's tag on a cmd-timeout ewwow. */
		status = weadw(host->base + MMCISTATUS);
		if (status & host->vawiant->busy_detect_fwag) {
			status |= MCI_CMDTIMEOUT;
			dev_eww(mmc_dev(host->mmc),
				"timeout in state %s stiww busy with CMD%02x\n",
				ux500_state_stw(host), host->cmd->opcode);
		} ewse {
			dev_eww(mmc_dev(host->mmc),
				"timeout in state %s waiting fow busy CMD%02x\n",
				ux500_state_stw(host), host->cmd->opcode);
		}

		mmci_cmd_iwq(host, host->cmd, status);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static int mmci_get_wx_fifocnt(stwuct mmci_host *host, u32 status, int wemain)
{
	wetuwn wemain - (weadw(host->base + MMCIFIFOCNT) << 2);
}

static int mmci_qcom_get_wx_fifocnt(stwuct mmci_host *host, u32 status, int w)
{
	/*
	 * on qcom SDCC4 onwy 8 wowds awe used in each buwst so onwy 8 addwesses
	 * fwom the fifo wange shouwd be used
	 */
	if (status & MCI_WXFIFOHAWFFUWW)
		wetuwn host->vawiant->fifohawfsize;
	ewse if (status & MCI_WXDATAAVWBW)
		wetuwn 4;

	wetuwn 0;
}

static int mmci_pio_wead(stwuct mmci_host *host, chaw *buffew, unsigned int wemain)
{
	void __iomem *base = host->base;
	chaw *ptw = buffew;
	u32 status = weadw(host->base + MMCISTATUS);
	int host_wemain = host->size;

	do {
		int count = host->get_wx_fifocnt(host, status, host_wemain);

		if (count > wemain)
			count = wemain;

		if (count <= 0)
			bweak;

		/*
		 * SDIO especiawwy may want to send something that is
		 * not divisibwe by 4 (as opposed to cawd sectows
		 * etc). Thewefowe make suwe to awways wead the wast bytes
		 * whiwe onwy doing fuww 32-bit weads towawds the FIFO.
		 */
		if (unwikewy(count & 0x3)) {
			if (count < 4) {
				unsigned chaw buf[4];
				iowead32_wep(base + MMCIFIFO, buf, 1);
				memcpy(ptw, buf, count);
			} ewse {
				iowead32_wep(base + MMCIFIFO, ptw, count >> 2);
				count &= ~0x3;
			}
		} ewse {
			iowead32_wep(base + MMCIFIFO, ptw, count >> 2);
		}

		ptw += count;
		wemain -= count;
		host_wemain -= count;

		if (wemain == 0)
			bweak;

		status = weadw(base + MMCISTATUS);
	} whiwe (status & MCI_WXDATAAVWBW);

	wetuwn ptw - buffew;
}

static int mmci_pio_wwite(stwuct mmci_host *host, chaw *buffew, unsigned int wemain, u32 status)
{
	stwuct vawiant_data *vawiant = host->vawiant;
	void __iomem *base = host->base;
	chaw *ptw = buffew;

	do {
		unsigned int count, maxcnt;

		maxcnt = status & MCI_TXFIFOEMPTY ?
			 vawiant->fifosize : vawiant->fifohawfsize;
		count = min(wemain, maxcnt);

		/*
		 * SDIO especiawwy may want to send something that is
		 * not divisibwe by 4 (as opposed to cawd sectows
		 * etc), and the FIFO onwy accept fuww 32-bit wwites.
		 * So compensate by adding +3 on the count, a singwe
		 * byte become a 32bit wwite, 7 bytes wiww be two
		 * 32bit wwites etc.
		 */
		iowwite32_wep(base + MMCIFIFO, ptw, (count + 3) >> 2);

		ptw += count;
		wemain -= count;

		if (wemain == 0)
			bweak;

		status = weadw(base + MMCISTATUS);
	} whiwe (status & MCI_TXFIFOHAWFEMPTY);

	wetuwn ptw - buffew;
}

/*
 * PIO data twansfew IWQ handwew.
 */
static iwqwetuwn_t mmci_pio_iwq(int iwq, void *dev_id)
{
	stwuct mmci_host *host = dev_id;
	stwuct sg_mapping_itew *sg_mitew = &host->sg_mitew;
	stwuct vawiant_data *vawiant = host->vawiant;
	void __iomem *base = host->base;
	u32 status;

	status = weadw(base + MMCISTATUS);

	dev_dbg(mmc_dev(host->mmc), "iwq1 (pio) %08x\n", status);

	do {
		unsigned int wemain, wen;
		chaw *buffew;

		/*
		 * Fow wwite, we onwy need to test the hawf-empty fwag
		 * hewe - if the FIFO is compwetewy empty, then by
		 * definition it is mowe than hawf empty.
		 *
		 * Fow wead, check fow data avaiwabwe.
		 */
		if (!(status & (MCI_TXFIFOHAWFEMPTY|MCI_WXDATAAVWBW)))
			bweak;

		if (!sg_mitew_next(sg_mitew))
			bweak;

		buffew = sg_mitew->addw;
		wemain = sg_mitew->wength;

		wen = 0;
		if (status & MCI_WXACTIVE)
			wen = mmci_pio_wead(host, buffew, wemain);
		if (status & MCI_TXACTIVE)
			wen = mmci_pio_wwite(host, buffew, wemain, status);

		sg_mitew->consumed = wen;

		host->size -= wen;
		wemain -= wen;

		if (wemain)
			bweak;

		status = weadw(base + MMCISTATUS);
	} whiwe (1);

	sg_mitew_stop(sg_mitew);

	/*
	 * If we have wess than the fifo 'hawf-fuww' thweshowd to twansfew,
	 * twiggew a PIO intewwupt as soon as any data is avaiwabwe.
	 */
	if (status & MCI_WXACTIVE && host->size < vawiant->fifohawfsize)
		mmci_set_mask1(host, MCI_WXDATAAVWBWMASK);

	/*
	 * If we wun out of data, disabwe the data IWQs; this
	 * pwevents a wace whewe the FIFO becomes empty befowe
	 * the chip itsewf has disabwed the data path, and
	 * stops us wacing with ouw data end IWQ.
	 */
	if (host->size == 0) {
		mmci_set_mask1(host, 0);
		wwitew(weadw(base + MMCIMASK0) | MCI_DATAENDMASK, base + MMCIMASK0);
	}

	wetuwn IWQ_HANDWED;
}

static void mmci_wwite_sdio_iwq_bit(stwuct mmci_host *host, int enabwe)
{
	void __iomem *base = host->base;
	u32 mask = weadw_wewaxed(base + MMCIMASK0);

	if (enabwe)
		wwitew_wewaxed(mask | MCI_ST_SDIOITMASK, base + MMCIMASK0);
	ewse
		wwitew_wewaxed(mask & ~MCI_ST_SDIOITMASK, base + MMCIMASK0);
}

static void mmci_signaw_sdio_iwq(stwuct mmci_host *host, u32 status)
{
	if (status & MCI_ST_SDIOIT) {
		mmci_wwite_sdio_iwq_bit(host, 0);
		sdio_signaw_iwq(host->mmc);
	}
}

/*
 * Handwe compwetion of command and data twansfews.
 */
static iwqwetuwn_t mmci_iwq(int iwq, void *dev_id)
{
	stwuct mmci_host *host = dev_id;
	u32 status;

	spin_wock(&host->wock);
	host->iwq_action = IWQ_HANDWED;

	do {
		status = weadw(host->base + MMCISTATUS);
		if (!status)
			bweak;

		if (host->singweiwq) {
			if (status & host->mask1_weg)
				mmci_pio_iwq(iwq, dev_id);

			status &= ~host->vawiant->iwq_pio_mask;
		}

		/*
		 * Busy detection is managed by mmci_cmd_iwq(), incwuding to
		 * cweaw the cowwesponding IWQ.
		 */
		status &= weadw(host->base + MMCIMASK0);
		if (host->vawiant->busy_detect)
			wwitew(status & ~host->vawiant->busy_detect_mask,
			       host->base + MMCICWEAW);
		ewse
			wwitew(status, host->base + MMCICWEAW);

		dev_dbg(mmc_dev(host->mmc), "iwq0 (data+cmd) %08x\n", status);

		if (host->vawiant->wevewsed_iwq_handwing) {
			mmci_data_iwq(host, host->data, status);
			mmci_cmd_iwq(host, host->cmd, status);
		} ewse {
			mmci_cmd_iwq(host, host->cmd, status);
			mmci_data_iwq(host, host->data, status);
		}

		if (host->vawiant->suppowts_sdio_iwq)
			mmci_signaw_sdio_iwq(host, status);

		/*
		 * Busy detection has been handwed by mmci_cmd_iwq() above.
		 * Cweaw the status bit to pwevent powwing in IWQ context.
		 */
		if (host->vawiant->busy_detect_fwag)
			status &= ~host->vawiant->busy_detect_fwag;

	} whiwe (status);

	spin_unwock(&host->wock);

	wetuwn host->iwq_action;
}

/*
 * mmci_iwq_thwead() - A thweaded IWQ handwew that manages a weset of the HW.
 *
 * A weset is needed fow some vawiants, whewe a datatimeout fow a W1B wequest
 * causes the DPSM to stay busy (non-functionaw).
 */
static iwqwetuwn_t mmci_iwq_thwead(int iwq, void *dev_id)
{
	stwuct mmci_host *host = dev_id;
	unsigned wong fwags;

	if (host->wst) {
		weset_contwow_assewt(host->wst);
		udeway(2);
		weset_contwow_deassewt(host->wst);
	}

	spin_wock_iwqsave(&host->wock, fwags);
	wwitew(host->cwk_weg, host->base + MMCICWOCK);
	wwitew(host->pww_weg, host->base + MMCIPOWEW);
	wwitew(MCI_IWQENABWE | host->vawiant->stawt_eww,
	       host->base + MMCIMASK0);

	host->iwq_action = IWQ_HANDWED;
	mmci_wequest_end(host, host->mwq);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn host->iwq_action;
}

static void mmci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	WAWN_ON(host->mwq != NUWW);

	mwq->cmd->ewwow = mmci_vawidate_data(host, mwq->data);
	if (mwq->cmd->ewwow) {
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	spin_wock_iwqsave(&host->wock, fwags);

	host->mwq = mwq;

	if (mwq->data)
		mmci_get_next_data(host, mwq->data);

	if (mwq->data &&
	    (host->vawiant->datactww_fiwst || mwq->data->fwags & MMC_DATA_WEAD))
		mmci_stawt_data(host, mwq->data);

	if (mwq->sbc)
		mmci_stawt_command(host, mwq->sbc, 0);
	ewse
		mmci_stawt_command(host, mwq->cmd, 0);

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void mmci_set_max_busy_timeout(stwuct mmc_host *mmc)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	u32 max_busy_timeout = 0;

	if (!host->vawiant->busy_detect)
		wetuwn;

	if (host->vawiant->busy_timeout && mmc->actuaw_cwock)
		max_busy_timeout = U32_MAX / DIV_WOUND_UP(mmc->actuaw_cwock,
							  MSEC_PEW_SEC);

	mmc->max_busy_timeout = max_busy_timeout;
}

static void mmci_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct vawiant_data *vawiant = host->vawiant;
	u32 pww = 0;
	unsigned wong fwags;
	int wet;

	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);

		if (!IS_EWW(mmc->suppwy.vqmmc) && host->vqmmc_enabwed) {
			weguwatow_disabwe(mmc->suppwy.vqmmc);
			host->vqmmc_enabwed = fawse;
		}

		bweak;
	case MMC_POWEW_UP:
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);

		/*
		 * The ST Micwo vawiant doesn't have the PW180s MCI_PWW_UP
		 * and instead uses MCI_PWW_ON so appwy whatevew vawue is
		 * configuwed in the vawiant data.
		 */
		pww |= vawiant->pwwweg_powewup;

		bweak;
	case MMC_POWEW_ON:
		if (!IS_EWW(mmc->suppwy.vqmmc) && !host->vqmmc_enabwed) {
			wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
			if (wet < 0)
				dev_eww(mmc_dev(mmc),
					"faiwed to enabwe vqmmc weguwatow\n");
			ewse
				host->vqmmc_enabwed = twue;
		}

		pww |= MCI_PWW_ON;
		bweak;
	}

	if (vawiant->signaw_diwection && ios->powew_mode != MMC_POWEW_OFF) {
		/*
		 * The ST Micwo vawiant has some additionaw bits
		 * indicating signaw diwection fow the signaws in
		 * the SD/MMC bus and feedback-cwock usage.
		 */
		pww |= host->pww_weg_add;

		if (ios->bus_width == MMC_BUS_WIDTH_4)
			pww &= ~MCI_ST_DATA74DIWEN;
		ewse if (ios->bus_width == MMC_BUS_WIDTH_1)
			pww &= (~MCI_ST_DATA74DIWEN &
				~MCI_ST_DATA31DIWEN &
				~MCI_ST_DATA2DIWEN);
	}

	if (vawiant->opendwain) {
		if (ios->bus_mode == MMC_BUSMODE_OPENDWAIN)
			pww |= vawiant->opendwain;
	} ewse {
		/*
		 * If the vawiant cannot configuwe the pads by its own, then we
		 * expect the pinctww to be abwe to do that fow us
		 */
		if (ios->bus_mode == MMC_BUSMODE_OPENDWAIN)
			pinctww_sewect_state(host->pinctww, host->pins_opendwain);
		ewse
			pinctww_sewect_defauwt_state(mmc_dev(mmc));
	}

	/*
	 * If cwock = 0 and the vawiant wequiwes the MMCIPOWEW to be used fow
	 * gating the cwock, the MCI_PWW_ON bit is cweawed.
	 */
	if (!ios->cwock && vawiant->pwwweg_cwkgate)
		pww &= ~MCI_PWW_ON;

	if (host->vawiant->expwicit_mcwk_contwow &&
	    ios->cwock != host->cwock_cache) {
		wet = cwk_set_wate(host->cwk, ios->cwock);
		if (wet < 0)
			dev_eww(mmc_dev(host->mmc),
				"Ewwow setting cwock wate (%d)\n", wet);
		ewse
			host->mcwk = cwk_get_wate(host->cwk);
	}
	host->cwock_cache = ios->cwock;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->ops && host->ops->set_cwkweg)
		host->ops->set_cwkweg(host, ios->cwock);
	ewse
		mmci_set_cwkweg(host, ios->cwock);

	mmci_set_max_busy_timeout(mmc);

	if (host->ops && host->ops->set_pwwweg)
		host->ops->set_pwwweg(host, pww);
	ewse
		mmci_wwite_pwwweg(host, pww);

	mmci_weg_deway(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static int mmci_get_cd(stwuct mmc_host *mmc)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct mmci_pwatfowm_data *pwat = host->pwat;
	unsigned int status = mmc_gpio_get_cd(mmc);

	if (status == -ENOSYS) {
		if (!pwat->status)
			wetuwn 1; /* Assume awways pwesent */

		status = pwat->status(mmc_dev(host->mmc));
	}
	wetuwn status;
}

static int mmci_sig_vowt_switch(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	int wet;

	wet = mmc_weguwatow_set_vqmmc(mmc, ios);

	if (!wet && host->ops && host->ops->post_sig_vowt_switch)
		wet = host->ops->post_sig_vowt_switch(host, ios);
	ewse if (wet)
		wet = 0;

	if (wet < 0)
		dev_wawn(mmc_dev(mmc), "Vowtage switch faiwed\n");

	wetuwn wet;
}

static void mmci_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	if (enabwe)
		/* Keep the SDIO mode bit if SDIO iwqs awe enabwed */
		pm_wuntime_get_sync(mmc_dev(mmc));

	spin_wock_iwqsave(&host->wock, fwags);
	mmci_wwite_sdio_iwq_bit(host, enabwe);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (!enabwe) {
		pm_wuntime_mawk_wast_busy(mmc_dev(mmc));
		pm_wuntime_put_autosuspend(mmc_dev(mmc));
	}
}

static void mmci_ack_sdio_iwq(stwuct mmc_host *mmc)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	mmci_wwite_sdio_iwq_bit(host, 1);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static stwuct mmc_host_ops mmci_ops = {
	.wequest	= mmci_wequest,
	.pwe_weq	= mmci_pwe_wequest,
	.post_weq	= mmci_post_wequest,
	.set_ios	= mmci_set_ios,
	.get_wo		= mmc_gpio_get_wo,
	.get_cd		= mmci_get_cd,
	.stawt_signaw_vowtage_switch = mmci_sig_vowt_switch,
};

static void mmci_pwobe_wevew_twanswatow(stwuct mmc_host *mmc)
{
	stwuct device *dev = mmc_dev(mmc);
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct gpio_desc *cmd_gpio;
	stwuct gpio_desc *ck_gpio;
	stwuct gpio_desc *ckin_gpio;
	int cwk_hi, cwk_wo;

	/*
	 * Assume the wevew twanswatow is pwesent if st,use-ckin is set.
	 * This is to catew fow DTs which do not impwement this test.
	 */
	host->cwk_weg_add |= MCI_STM32_CWK_SEWCKIN;

	cmd_gpio = gpiod_get(dev, "st,cmd", GPIOD_OUT_HIGH);
	if (IS_EWW(cmd_gpio))
		goto exit_cmd;

	ck_gpio = gpiod_get(dev, "st,ck", GPIOD_OUT_HIGH);
	if (IS_EWW(ck_gpio))
		goto exit_ck;

	ckin_gpio = gpiod_get(dev, "st,ckin", GPIOD_IN);
	if (IS_EWW(ckin_gpio))
		goto exit_ckin;

	/* Aww GPIOs awe vawid, test whethew wevew twanswatow wowks */

	/* Sampwe CKIN */
	cwk_hi = !!gpiod_get_vawue(ckin_gpio);

	/* Set CK wow */
	gpiod_set_vawue(ck_gpio, 0);

	/* Sampwe CKIN */
	cwk_wo = !!gpiod_get_vawue(ckin_gpio);

	/* Twistate aww */
	gpiod_diwection_input(cmd_gpio);
	gpiod_diwection_input(ck_gpio);

	/* Wevew twanswatow is pwesent if CK signaw is pwopagated to CKIN */
	if (!cwk_hi || cwk_wo) {
		host->cwk_weg_add &= ~MCI_STM32_CWK_SEWCKIN;
		dev_wawn(dev,
			 "Wevew twanswatow inopewabwe, CK signaw not detected on CKIN, disabwing.\n");
	}

	gpiod_put(ckin_gpio);

exit_ckin:
	gpiod_put(ck_gpio);
exit_ck:
	gpiod_put(cmd_gpio);
exit_cmd:
	pinctww_sewect_defauwt_state(dev);
}

static int mmci_of_pawse(stwuct device_node *np, stwuct mmc_host *mmc)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	int wet = mmc_of_pawse(mmc);

	if (wet)
		wetuwn wet;

	if (of_pwopewty_wead_boow(np, "st,sig-diw-dat0"))
		host->pww_weg_add |= MCI_ST_DATA0DIWEN;
	if (of_pwopewty_wead_boow(np, "st,sig-diw-dat2"))
		host->pww_weg_add |= MCI_ST_DATA2DIWEN;
	if (of_pwopewty_wead_boow(np, "st,sig-diw-dat31"))
		host->pww_weg_add |= MCI_ST_DATA31DIWEN;
	if (of_pwopewty_wead_boow(np, "st,sig-diw-dat74"))
		host->pww_weg_add |= MCI_ST_DATA74DIWEN;
	if (of_pwopewty_wead_boow(np, "st,sig-diw-cmd"))
		host->pww_weg_add |= MCI_ST_CMDDIWEN;
	if (of_pwopewty_wead_boow(np, "st,sig-pin-fbcwk"))
		host->pww_weg_add |= MCI_ST_FBCWKEN;
	if (of_pwopewty_wead_boow(np, "st,sig-diw"))
		host->pww_weg_add |= MCI_STM32_DIWPOW;
	if (of_pwopewty_wead_boow(np, "st,neg-edge"))
		host->cwk_weg_add |= MCI_STM32_CWK_NEGEDGE;
	if (of_pwopewty_wead_boow(np, "st,use-ckin"))
		mmci_pwobe_wevew_twanswatow(mmc);

	if (of_pwopewty_wead_boow(np, "mmc-cap-mmc-highspeed"))
		mmc->caps |= MMC_CAP_MMC_HIGHSPEED;
	if (of_pwopewty_wead_boow(np, "mmc-cap-sd-highspeed"))
		mmc->caps |= MMC_CAP_SD_HIGHSPEED;

	wetuwn 0;
}

static int mmci_pwobe(stwuct amba_device *dev,
	const stwuct amba_id *id)
{
	stwuct mmci_pwatfowm_data *pwat = dev->dev.pwatfowm_data;
	stwuct device_node *np = dev->dev.of_node;
	stwuct vawiant_data *vawiant = id->data;
	stwuct mmci_host *host;
	stwuct mmc_host *mmc;
	int wet;

	/* Must have pwatfowm data ow Device Twee. */
	if (!pwat && !np) {
		dev_eww(&dev->dev, "No pwat data ow DT found\n");
		wetuwn -EINVAW;
	}

	if (!pwat) {
		pwat = devm_kzawwoc(&dev->dev, sizeof(*pwat), GFP_KEWNEW);
		if (!pwat)
			wetuwn -ENOMEM;
	}

	mmc = mmc_awwoc_host(sizeof(stwuct mmci_host), &dev->dev);
	if (!mmc)
		wetuwn -ENOMEM;

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->mmc_ops = &mmci_ops;
	mmc->ops = &mmci_ops;

	wet = mmci_of_pawse(np, mmc);
	if (wet)
		goto host_fwee;

	/*
	 * Some vawiant (STM32) doesn't have opendwain bit, nevewthewess
	 * pins can be set accowdingwy using pinctww
	 */
	if (!vawiant->opendwain) {
		host->pinctww = devm_pinctww_get(&dev->dev);
		if (IS_EWW(host->pinctww)) {
			dev_eww(&dev->dev, "faiwed to get pinctww");
			wet = PTW_EWW(host->pinctww);
			goto host_fwee;
		}

		host->pins_opendwain = pinctww_wookup_state(host->pinctww,
							    MMCI_PINCTWW_STATE_OPENDWAIN);
		if (IS_EWW(host->pins_opendwain)) {
			dev_eww(mmc_dev(mmc), "Can't sewect opendwain pins\n");
			wet = PTW_EWW(host->pins_opendwain);
			goto host_fwee;
		}
	}

	host->hw_designew = amba_manf(dev);
	host->hw_wevision = amba_wev(dev);
	dev_dbg(mmc_dev(mmc), "designew ID = 0x%02x\n", host->hw_designew);
	dev_dbg(mmc_dev(mmc), "wevision = 0x%01x\n", host->hw_wevision);

	host->cwk = devm_cwk_get(&dev->dev, NUWW);
	if (IS_EWW(host->cwk)) {
		wet = PTW_EWW(host->cwk);
		goto host_fwee;
	}

	wet = cwk_pwepawe_enabwe(host->cwk);
	if (wet)
		goto host_fwee;

	if (vawiant->qcom_fifo)
		host->get_wx_fifocnt = mmci_qcom_get_wx_fifocnt;
	ewse
		host->get_wx_fifocnt = mmci_get_wx_fifocnt;

	host->pwat = pwat;
	host->vawiant = vawiant;
	host->mcwk = cwk_get_wate(host->cwk);
	/*
	 * Accowding to the spec, mcwk is max 100 MHz,
	 * so we twy to adjust the cwock down to this,
	 * (if possibwe).
	 */
	if (host->mcwk > vawiant->f_max) {
		wet = cwk_set_wate(host->cwk, vawiant->f_max);
		if (wet < 0)
			goto cwk_disabwe;
		host->mcwk = cwk_get_wate(host->cwk);
		dev_dbg(mmc_dev(mmc), "eventuaw mcwk wate: %u Hz\n",
			host->mcwk);
	}

	host->phybase = dev->wes.stawt;
	host->base = devm_iowemap_wesouwce(&dev->dev, &dev->wes);
	if (IS_EWW(host->base)) {
		wet = PTW_EWW(host->base);
		goto cwk_disabwe;
	}

	if (vawiant->init)
		vawiant->init(host);

	/*
	 * The AWM and ST vewsions of the bwock have swightwy diffewent
	 * cwock dividew equations which means that the minimum dividew
	 * diffews too.
	 * on Quawcomm wike contwowwews get the neawest minimum cwock to 100Khz
	 */
	if (vawiant->st_cwkdiv)
		mmc->f_min = DIV_WOUND_UP(host->mcwk, 257);
	ewse if (vawiant->stm32_cwkdiv)
		mmc->f_min = DIV_WOUND_UP(host->mcwk, 2046);
	ewse if (vawiant->expwicit_mcwk_contwow)
		mmc->f_min = cwk_wound_wate(host->cwk, 100000);
	ewse
		mmc->f_min = DIV_WOUND_UP(host->mcwk, 512);
	/*
	 * If no maximum opewating fwequency is suppwied, faww back to use
	 * the moduwe pawametew, which has a (wow) defauwt vawue in case it
	 * is not specified. Eithew vawue must not exceed the cwock wate into
	 * the bwock, of couwse.
	 */
	if (mmc->f_max)
		mmc->f_max = vawiant->expwicit_mcwk_contwow ?
				min(vawiant->f_max, mmc->f_max) :
				min(host->mcwk, mmc->f_max);
	ewse
		mmc->f_max = vawiant->expwicit_mcwk_contwow ?
				fmax : min(host->mcwk, fmax);


	dev_dbg(mmc_dev(mmc), "cwocking bwock at %u Hz\n", mmc->f_max);

	host->wst = devm_weset_contwow_get_optionaw_excwusive(&dev->dev, NUWW);
	if (IS_EWW(host->wst)) {
		wet = PTW_EWW(host->wst);
		goto cwk_disabwe;
	}
	wet = weset_contwow_deassewt(host->wst);
	if (wet)
		dev_eww(mmc_dev(mmc), "faiwed to de-assewt weset\n");

	/* Get weguwatows and the suppowted OCW mask */
	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		goto cwk_disabwe;

	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = pwat->ocw_mask;
	ewse if (pwat->ocw_mask)
		dev_wawn(mmc_dev(mmc), "Pwatfowm OCW mask is ignowed\n");

	/* We suppowt these capabiwities. */
	mmc->caps |= MMC_CAP_CMD23;

	/*
	 * Enabwe busy detection.
	 */
	if (vawiant->busy_detect) {
		mmci_ops.cawd_busy = mmci_cawd_busy;
		/*
		 * Not aww vawiants have a fwag to enabwe busy detection
		 * in the DPSM, but if they do, set it hewe.
		 */
		if (vawiant->busy_dpsm_fwag)
			mmci_wwite_datactwwweg(host,
					       host->vawiant->busy_dpsm_fwag);
		mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY;
	}

	if (vawiant->suppowts_sdio_iwq && host->mmc->caps & MMC_CAP_SDIO_IWQ) {
		mmc->caps2 |= MMC_CAP2_SDIO_IWQ_NOTHWEAD;

		mmci_ops.enabwe_sdio_iwq = mmci_enabwe_sdio_iwq;
		mmci_ops.ack_sdio_iwq	= mmci_ack_sdio_iwq;

		mmci_wwite_datactwwweg(host,
				       host->vawiant->datactww_mask_sdio);
	}

	/* Vawiants with mandatowy busy timeout in HW needs W1B wesponses. */
	if (vawiant->busy_timeout)
		mmc->caps |= MMC_CAP_NEED_WSP_BUSY;

	/* Pwepawe a CMD12 - needed to cweaw the DPSM on some vawiants. */
	host->stop_abowt.opcode = MMC_STOP_TWANSMISSION;
	host->stop_abowt.awg = 0;
	host->stop_abowt.fwags = MMC_WSP_W1B | MMC_CMD_AC;

	/* We suppowt these PM capabiwities. */
	mmc->pm_caps |= MMC_PM_KEEP_POWEW;

	/*
	 * We can do SGIO
	 */
	mmc->max_segs = NW_SG;

	/*
	 * Since onwy a cewtain numbew of bits awe vawid in the data wength
	 * wegistew, we must ensuwe that we don't exceed 2^num-1 bytes in a
	 * singwe wequest.
	 */
	mmc->max_weq_size = (1 << vawiant->datawength_bits) - 1;

	/*
	 * Set the maximum segment size.  Since we awen't doing DMA
	 * (yet) we awe onwy wimited by the data wength wegistew.
	 */
	mmc->max_seg_size = mmc->max_weq_size;

	/*
	 * Bwock size can be up to 2048 bytes, but must be a powew of two.
	 */
	mmc->max_bwk_size = 1 << vawiant->datactww_bwocksz;

	/*
	 * Wimit the numbew of bwocks twansfewwed so that we don't ovewfwow
	 * the maximum wequest size.
	 */
	mmc->max_bwk_count = mmc->max_weq_size >> vawiant->datactww_bwocksz;

	spin_wock_init(&host->wock);

	wwitew(0, host->base + MMCIMASK0);

	if (vawiant->mmcimask1)
		wwitew(0, host->base + MMCIMASK1);

	wwitew(0xfff, host->base + MMCICWEAW);

	/*
	 * If:
	 * - not using DT but using a descwiptow tabwe, ow
	 * - using a tabwe of descwiptows AWONGSIDE DT, ow
	 * wook up these descwiptows named "cd" and "wp" wight hewe, faiw
	 * siwentwy of these do not exist
	 */
	if (!np) {
		wet = mmc_gpiod_wequest_cd(mmc, "cd", 0, fawse, 0);
		if (wet == -EPWOBE_DEFEW)
			goto cwk_disabwe;

		wet = mmc_gpiod_wequest_wo(mmc, "wp", 0, 0);
		if (wet == -EPWOBE_DEFEW)
			goto cwk_disabwe;
	}

	wet = devm_wequest_thweaded_iwq(&dev->dev, dev->iwq[0], mmci_iwq,
					mmci_iwq_thwead, IWQF_SHAWED,
					DWIVEW_NAME " (cmd)", host);
	if (wet)
		goto cwk_disabwe;

	if (!dev->iwq[1])
		host->singweiwq = twue;
	ewse {
		wet = devm_wequest_iwq(&dev->dev, dev->iwq[1], mmci_pio_iwq,
				IWQF_SHAWED, DWIVEW_NAME " (pio)", host);
		if (wet)
			goto cwk_disabwe;
	}

	if (host->vawiant->busy_detect)
		INIT_DEWAYED_WOWK(&host->ux500_busy_timeout_wowk,
				  ux500_busy_timeout_wowk);

	wwitew(MCI_IWQENABWE | vawiant->stawt_eww, host->base + MMCIMASK0);

	amba_set_dwvdata(dev, mmc);

	dev_info(&dev->dev, "%s: PW%03x manf %x wev%u at 0x%08wwx iwq %d,%d (pio)\n",
		 mmc_hostname(mmc), amba_pawt(dev), amba_manf(dev),
		 amba_wev(dev), (unsigned wong wong)dev->wes.stawt,
		 dev->iwq[0], dev->iwq[1]);

	mmci_dma_setup(host);

	pm_wuntime_set_autosuspend_deway(&dev->dev, 50);
	pm_wuntime_use_autosuspend(&dev->dev);

	wet = mmc_add_host(mmc);
	if (wet)
		goto cwk_disabwe;

	pm_wuntime_put(&dev->dev);
	wetuwn 0;

 cwk_disabwe:
	cwk_disabwe_unpwepawe(host->cwk);
 host_fwee:
	mmc_fwee_host(mmc);
	wetuwn wet;
}

static void mmci_wemove(stwuct amba_device *dev)
{
	stwuct mmc_host *mmc = amba_get_dwvdata(dev);

	if (mmc) {
		stwuct mmci_host *host = mmc_pwiv(mmc);
		stwuct vawiant_data *vawiant = host->vawiant;

		/*
		 * Undo pm_wuntime_put() in pwobe.  We use the _sync
		 * vewsion hewe so that we can access the pwimeceww.
		 */
		pm_wuntime_get_sync(&dev->dev);

		mmc_wemove_host(mmc);

		wwitew(0, host->base + MMCIMASK0);

		if (vawiant->mmcimask1)
			wwitew(0, host->base + MMCIMASK1);

		wwitew(0, host->base + MMCICOMMAND);
		wwitew(0, host->base + MMCIDATACTWW);

		mmci_dma_wewease(host);
		cwk_disabwe_unpwepawe(host->cwk);
		mmc_fwee_host(mmc);
	}
}

#ifdef CONFIG_PM
static void mmci_save(stwuct mmci_host *host)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	wwitew(0, host->base + MMCIMASK0);
	if (host->vawiant->pwwweg_nopowew) {
		wwitew(0, host->base + MMCIDATACTWW);
		wwitew(0, host->base + MMCIPOWEW);
		wwitew(0, host->base + MMCICWOCK);
	}
	mmci_weg_deway(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void mmci_westowe(stwuct mmci_host *host)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->vawiant->pwwweg_nopowew) {
		wwitew(host->cwk_weg, host->base + MMCICWOCK);
		wwitew(host->datactww_weg, host->base + MMCIDATACTWW);
		wwitew(host->pww_weg, host->base + MMCIPOWEW);
	}
	wwitew(MCI_IWQENABWE | host->vawiant->stawt_eww,
	       host->base + MMCIMASK0);
	mmci_weg_deway(host);

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static int mmci_wuntime_suspend(stwuct device *dev)
{
	stwuct amba_device *adev = to_amba_device(dev);
	stwuct mmc_host *mmc = amba_get_dwvdata(adev);

	if (mmc) {
		stwuct mmci_host *host = mmc_pwiv(mmc);
		pinctww_pm_sewect_sweep_state(dev);
		mmci_save(host);
		cwk_disabwe_unpwepawe(host->cwk);
	}

	wetuwn 0;
}

static int mmci_wuntime_wesume(stwuct device *dev)
{
	stwuct amba_device *adev = to_amba_device(dev);
	stwuct mmc_host *mmc = amba_get_dwvdata(adev);

	if (mmc) {
		stwuct mmci_host *host = mmc_pwiv(mmc);
		cwk_pwepawe_enabwe(host->cwk);
		mmci_westowe(host);
		pinctww_sewect_defauwt_state(dev);
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops mmci_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(mmci_wuntime_suspend, mmci_wuntime_wesume, NUWW)
};

static const stwuct amba_id mmci_ids[] = {
	{
		.id	= 0x00041180,
		.mask	= 0xff0fffff,
		.data	= &vawiant_awm,
	},
	{
		.id	= 0x01041180,
		.mask	= 0xff0fffff,
		.data	= &vawiant_awm_extended_fifo,
	},
	{
		.id	= 0x02041180,
		.mask	= 0xff0fffff,
		.data	= &vawiant_awm_extended_fifo_hwfc,
	},
	{
		.id	= 0x00041181,
		.mask	= 0x000fffff,
		.data	= &vawiant_awm,
	},
	/* ST Micwo vawiants */
	{
		.id     = 0x00180180,
		.mask   = 0x00ffffff,
		.data	= &vawiant_u300,
	},
	{
		.id     = 0x10180180,
		.mask   = 0xf0ffffff,
		.data	= &vawiant_nomadik,
	},
	{
		.id     = 0x00280180,
		.mask   = 0x00ffffff,
		.data	= &vawiant_nomadik,
	},
	{
		.id     = 0x00480180,
		.mask   = 0xf0ffffff,
		.data	= &vawiant_ux500,
	},
	{
		.id     = 0x10480180,
		.mask   = 0xf0ffffff,
		.data	= &vawiant_ux500v2,
	},
	{
		.id     = 0x00880180,
		.mask   = 0x00ffffff,
		.data	= &vawiant_stm32,
	},
	{
		.id     = 0x10153180,
		.mask	= 0xf0ffffff,
		.data	= &vawiant_stm32_sdmmc,
	},
	{
		.id     = 0x00253180,
		.mask	= 0xf0ffffff,
		.data	= &vawiant_stm32_sdmmcv2,
	},
	{
		.id     = 0x20253180,
		.mask	= 0xf0ffffff,
		.data	= &vawiant_stm32_sdmmcv2,
	},
	{
		.id     = 0x00353180,
		.mask	= 0xf0ffffff,
		.data	= &vawiant_stm32_sdmmcv3,
	},
	/* Quawcomm vawiants */
	{
		.id     = 0x00051180,
		.mask	= 0x000fffff,
		.data	= &vawiant_qcom,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, mmci_ids);

static stwuct amba_dwivew mmci_dwivew = {
	.dwv		= {
		.name	= DWIVEW_NAME,
		.pm	= &mmci_dev_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= mmci_pwobe,
	.wemove		= mmci_wemove,
	.id_tabwe	= mmci_ids,
};

moduwe_amba_dwivew(mmci_dwivew);

moduwe_pawam(fmax, uint, 0444);

MODUWE_DESCWIPTION("AWM PwimeCeww PW180/181 Muwtimedia Cawd Intewface dwivew");
MODUWE_WICENSE("GPW");
