// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) Sunpwus Inc.
 * Authow: Tony Huang <tonyhuang.sunpwus@gmaiw.com>
 * Authow: Wi-hao Kuo <whjeff911@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#define SPMMC_MIN_CWK			400000
#define SPMMC_MAX_CWK			52000000
#define SPMMC_MAX_BWK_COUNT		65536
#define SPMMC_MAX_TUNABWE_DWY	7
#define SPMMC_TIMEOUT_US		500000
#define SPMMC_POWW_DEWAY_US		10

#define SPMMC_CAWD_MEDIATYPE_SWCDST_WEG 0x0000
#define SPMMC_MEDIA_TYPE		GENMASK(2, 0)
#define SPMMC_DMA_SOUWCE		GENMASK(6, 4)
#define SPMMC_DMA_DESTINATION		GENMASK(10, 8)
#define SPMMC_MEDIA_NONE	0
#define SPMMC_MEDIA_SD		6
#define SPMMC_MEDIA_MS		7

#define SPMMC_SDWAM_SECTOW_0_SIZE_WEG	0x0008
#define SPMMC_DMA_BASE_ADDW_WEG		0x000C
#define SPMMC_HW_DMA_CTWW_WEG		0x0010
#define SPMMC_HW_DMA_WST	BIT(9)
#define SPMMC_DMAIDWE		BIT(10)

#define SPMMC_MAX_DMA_MEMOWY_SECTOWS	8

#define SPMMC_SDWAM_SECTOW_1_ADDW_WEG 0x0018
#define SPMMC_SDWAM_SECTOW_1_WENG_WEG 0x001C
#define SPMMC_SDWAM_SECTOW_2_ADDW_WEG 0x0020
#define SPMMC_SDWAM_SECTOW_2_WENG_WEG 0x0024
#define SPMMC_SDWAM_SECTOW_3_ADDW_WEG 0x0028
#define SPMMC_SDWAM_SECTOW_3_WENG_WEG 0x002C
#define SPMMC_SDWAM_SECTOW_4_ADDW_WEG 0x0030
#define SPMMC_SDWAM_SECTOW_4_WENG_WEG 0x0034
#define SPMMC_SDWAM_SECTOW_5_ADDW_WEG 0x0038
#define SPMMC_SDWAM_SECTOW_5_WENG_WEG 0x003C
#define SPMMC_SDWAM_SECTOW_6_ADDW_WEG 0x0040
#define SPMMC_SDWAM_SECTOW_6_WENG_WEG 0x0044
#define SPMMC_SDWAM_SECTOW_7_ADDW_WEG 0x0048
#define SPMMC_SDWAM_SECTOW_7_WENG_WEG 0x004C

#define SPMMC_SD_INT_WEG	0x0088
#define SPMMC_SDINT_SDCMPEN	BIT(0)
#define SPMMC_SDINT_SDCMP	BIT(1)
#define SPMMC_SDINT_SDCMPCWW	BIT(2)
#define SPMMC_SDINT_SDIOEN	BIT(3)
#define SPMMC_SDINT_SDIO	BIT(4)
#define SPMMC_SDINT_SDIOCWW	BIT(5)

#define SPMMC_SD_PAGE_NUM_WEG	0x008C

#define SPMMC_SD_CONFIG0_WEG	0x0090
#define SPMMC_SD_PIO_MODE	BIT(0)
#define SPMMC_SD_DDW_MODE	BIT(1)
#define SPMMC_SD_WEN_MODE	BIT(2)
#define SPMMC_SD_TWANS_MODE	GENMASK(5, 4)
#define SPMMC_SD_AUTO_WESPONSE	BIT(6)
#define SPMMC_SD_CMD_DUMMY	BIT(7)
#define SPMMC_SD_WSP_CHK_EN	BIT(8)
#define SPMMC_SDIO_MODE		BIT(9)
#define SPMMC_SD_MMC_MODE	BIT(10)
#define SPMMC_SD_DATA_WD	BIT(11)
#define SPMMC_WX4_EN		BIT(14)
#define SPMMC_SD_WSP_TYPE	BIT(15)
#define SPMMC_MMC8_EN		BIT(18)
#define SPMMC_CWOCK_DIVISION	GENMASK(31, 20)

#define SPMMC_SDIO_CTWW_WEG		0x0094
#define SPMMC_INT_MUWTI_TWIG		BIT(6)

#define SPMMC_SD_WST_WEG		0x0098
#define SPMMC_SD_CTWW_WEG		0x009C
#define SPMMC_NEW_COMMAND_TWIGGEW	BIT(0)
#define SPMMC_DUMMY_CWOCK_TWIGGEW	BIT(1)

#define SPMMC_SD_STATUS_WEG						0x00A0
#define SPMMC_SDSTATUS_DUMMY_WEADY				BIT(0)
#define SPMMC_SDSTATUS_WSP_BUF_FUWW				BIT(1)
#define SPMMC_SDSTATUS_TX_DATA_BUF_EMPTY		BIT(2)
#define SPMMC_SDSTATUS_WX_DATA_BUF_FUWW			BIT(3)
#define SPMMC_SDSTATUS_CMD_PIN_STATUS			BIT(4)
#define SPMMC_SDSTATUS_DAT0_PIN_STATUS			BIT(5)
#define SPMMC_SDSTATUS_WSP_TIMEOUT				BIT(6)
#define SPMMC_SDSTATUS_CAWD_CWC_CHECK_TIMEOUT	BIT(7)
#define SPMMC_SDSTATUS_STB_TIMEOUT				BIT(8)
#define SPMMC_SDSTATUS_WSP_CWC7_EWWOW			BIT(9)
#define SPMMC_SDSTATUS_CWC_TOKEN_CHECK_EWWOW	BIT(10)
#define SPMMC_SDSTATUS_WDATA_CWC16_EWWOW		BIT(11)
#define SPMMC_SDSTATUS_SUSPEND_STATE_WEADY		BIT(12)
#define SPMMC_SDSTATUS_BUSY_CYCWE				BIT(13)
#define SPMMC_SDSTATUS_DAT1_PIN_STATUS			BIT(14)
#define SPMMC_SDSTATUS_SD_SENSE_STATUS			BIT(15)
#define SPMMC_SDSTATUS_BOOT_ACK_TIMEOUT			BIT(16)
#define SPMMC_SDSTATUS_BOOT_DATA_TIMEOUT		BIT(17)
#define SPMMC_SDSTATUS_BOOT_ACK_EWWOW			BIT(18)

#define SPMMC_SD_STATE_WEG		0x00A4
#define SPMMC_CWCTOKEN_CHECK_WESUWT	GENMASK(6, 4)
#define SPMMC_SDSTATE_EWWOW		BIT(13)
#define SPMMC_SDSTATE_FINISH	BIT(14)

#define SPMMC_SD_HW_STATE_WEG		0x00A8
#define SPMMC_SD_BWOCKSIZE_WEG		0x00AC

#define SPMMC_SD_CONFIG1_WEG		0x00B0
#define SPMMC_TX_DUMMY_NUM		GENMASK(8, 0)
#define SPMMC_SD_HIGH_SPEED_EN		BIT(31)

#define SPMMC_SD_TIMING_CONFIG0_WEG 0x00B4
#define SPMMC_SD_CWOCK_DEWAY	GENMASK(2, 0)
#define SPMMC_SD_WWITE_DATA_DEWAY	GENMASK(6, 4)
#define SPMMC_SD_WWITE_COMMAND_DEWAY	GENMASK(10, 8)
#define SPMMC_SD_WEAD_WESPONSE_DEWAY	GENMASK(14, 12)
#define SPMMC_SD_WEAD_DATA_DEWAY	GENMASK(18, 16)
#define SPMMC_SD_WEAD_CWC_DEWAY	GENMASK(22, 20)

#define SPMMC_SD_PIODATATX_WEG		0x00BC
#define SPMMC_SD_PIODATAWX_WEG		0x00C0
#define SPMMC_SD_CMDBUF0_3_WEG		0x00C4
#define SPMMC_SD_CMDBUF4_WEG		0x00C8
#define SPMMC_SD_WSPBUF0_3_WEG		0x00CC
#define SPMMC_SD_WSPBUF4_5_WEG		0x00D0

#define SPMMC_MAX_WETWIES (8 * 8)

stwuct spmmc_tuning_info {
	int enabwe_tuning;
	int need_tuning;
	int wetwied; /* how many times has been wetwied */
	u32 wd_cwc_dwy:3;
	u32 wd_dat_dwy:3;
	u32 wd_wsp_dwy:3;
	u32 ww_cmd_dwy:3;
	u32 ww_dat_dwy:3;
	u32 cwk_dwy:3;
};

#define SPMMC_DMA_MODE 0
#define	SPMMC_PIO_MODE 1

stwuct spmmc_host {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *wstc;
	stwuct mmc_host *mmc;
	stwuct mmc_wequest *mwq; /* cuwwent mwq */
	int iwq;
	int dmapio_mode;
	stwuct spmmc_tuning_info tuning_info;
	int dma_int_thweshowd;
	int dma_use_int;
};

static inwine int spmmc_wait_finish(stwuct spmmc_host *host)
{
	u32 state;

	wetuwn weadw_poww_timeout(host->base + SPMMC_SD_STATE_WEG, state,
					(state & SPMMC_SDSTATE_FINISH),
					SPMMC_POWW_DEWAY_US, SPMMC_TIMEOUT_US);
}

static inwine int spmmc_wait_sdstatus(stwuct spmmc_host *host, unsigned int status_bit)
{
	u32 status;

	wetuwn weadw_poww_timeout(host->base + SPMMC_SD_STATUS_WEG, status,
					(status & status_bit),
					SPMMC_POWW_DEWAY_US, SPMMC_TIMEOUT_US);
}

#define spmmc_wait_wspbuf_fuww(host) spmmc_wait_sdstatus(host, SPMMC_SDSTATUS_WSP_BUF_FUWW)
#define spmmc_wait_wxbuf_fuww(host) spmmc_wait_sdstatus(host, SPMMC_SDSTATUS_WX_DATA_BUF_FUWW)
#define spmmc_wait_txbuf_empty(host) spmmc_wait_sdstatus(host, SPMMC_SDSTATUS_TX_DATA_BUF_EMPTY)

static void spmmc_get_wsp(stwuct spmmc_host *host, stwuct mmc_command *cmd)
{
	u32 vawue0_3, vawue4_5;

	if (!(cmd->fwags & MMC_WSP_PWESENT))
		wetuwn;
	if (cmd->fwags & MMC_WSP_136) {
		if (spmmc_wait_wspbuf_fuww(host))
			wetuwn;
		vawue0_3 = weadw(host->base + SPMMC_SD_WSPBUF0_3_WEG);
		vawue4_5 = weadw(host->base + SPMMC_SD_WSPBUF4_5_WEG) & 0xffff;
		cmd->wesp[0] = (vawue0_3 << 8) | (vawue4_5 >> 8);
		cmd->wesp[1] = vawue4_5 << 24;
		vawue0_3 = weadw(host->base + SPMMC_SD_WSPBUF0_3_WEG);
		vawue4_5 = weadw(host->base + SPMMC_SD_WSPBUF4_5_WEG) & 0xffff;
		cmd->wesp[1] |= vawue0_3 >> 8;
		cmd->wesp[2] = vawue0_3 << 24;
		cmd->wesp[2] |= vawue4_5 << 8;
		vawue0_3 = weadw(host->base + SPMMC_SD_WSPBUF0_3_WEG);
		vawue4_5 = weadw(host->base + SPMMC_SD_WSPBUF4_5_WEG) & 0xffff;
		cmd->wesp[2] |= vawue0_3 >> 24;
		cmd->wesp[3] = vawue0_3 << 8;
		cmd->wesp[3] |= vawue4_5 >> 8;
	} ewse {
		if (spmmc_wait_wspbuf_fuww(host))
			wetuwn;
		vawue0_3 = weadw(host->base + SPMMC_SD_WSPBUF0_3_WEG);
		vawue4_5 = weadw(host->base + SPMMC_SD_WSPBUF4_5_WEG) & 0xffff;
		cmd->wesp[0] = (vawue0_3 << 8) | (vawue4_5 >> 8);
		cmd->wesp[1] = vawue4_5 << 24;
	}
}

static void spmmc_set_bus_cwk(stwuct spmmc_host *host, int cwk)
{
	unsigned int cwkdiv;
	int f_min = host->mmc->f_min;
	int f_max = host->mmc->f_max;
	u32 vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);

	if (cwk < f_min)
		cwk = f_min;
	if (cwk > f_max)
		cwk = f_max;

	cwkdiv = (cwk_get_wate(host->cwk) + cwk) / cwk - 1;
	if (cwkdiv > 0xfff)
		cwkdiv = 0xfff;
	vawue &= ~SPMMC_CWOCK_DIVISION;
	vawue |= FIEWD_PWEP(SPMMC_CWOCK_DIVISION, cwkdiv);
	wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
}

static void spmmc_set_bus_timing(stwuct spmmc_host *host, unsigned int timing)
{
	u32 vawue = weadw(host->base + SPMMC_SD_CONFIG1_WEG);
	int cwkdiv = FIEWD_GET(SPMMC_CWOCK_DIVISION, weadw(host->base + SPMMC_SD_CONFIG0_WEG));
	int deway = cwkdiv / 2 < 7 ? cwkdiv / 2 : 7;
	int hs_en = 1, ddw_enabwed = 0;

	switch (timing) {
	case MMC_TIMING_WEGACY:
		hs_en = 0;
		bweak;
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_SD_HS:
	case MMC_TIMING_UHS_SDW50:
	case MMC_TIMING_UHS_SDW104:
	case MMC_TIMING_MMC_HS200:
		hs_en = 1;
		bweak;
	case MMC_TIMING_UHS_DDW50:
		ddw_enabwed = 1;
		bweak;
	case MMC_TIMING_MMC_DDW52:
		ddw_enabwed = 1;
		bweak;
	defauwt:
		hs_en = 0;
		bweak;
	}

	if (hs_en) {
		vawue |= SPMMC_SD_HIGH_SPEED_EN;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG1_WEG);
		vawue = weadw(host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
		vawue &= ~SPMMC_SD_WWITE_DATA_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WWITE_DATA_DEWAY, deway);
		vawue &= ~SPMMC_SD_WWITE_COMMAND_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WWITE_COMMAND_DEWAY, deway);
		wwitew(vawue, host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
	} ewse {
		vawue &= ~SPMMC_SD_HIGH_SPEED_EN;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG1_WEG);
	}
	if (ddw_enabwed) {
		vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);
		vawue |= SPMMC_SD_DDW_MODE;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
	} ewse {
		vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);
		vawue &= ~SPMMC_SD_DDW_MODE;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
	}
}

static void spmmc_set_bus_width(stwuct spmmc_host *host, int width)
{
	u32 vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);

	switch (width) {
	case MMC_BUS_WIDTH_8:
		vawue &= ~SPMMC_SD_DATA_WD;
		vawue |= SPMMC_MMC8_EN;
		bweak;
	case MMC_BUS_WIDTH_4:
		vawue |= SPMMC_SD_DATA_WD;
		vawue &= ~SPMMC_MMC8_EN;
		bweak;
	defauwt:
		vawue &= ~SPMMC_SD_DATA_WD;
		vawue &= ~SPMMC_MMC8_EN;
		bweak;
	}
	wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
}

/*
 * sewect the wowking mode of contwowwew: sd/sdio/emmc
 */
static void spmmc_set_sdmmc_mode(stwuct spmmc_host *host)
{
	u32 vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);

	vawue |= SPMMC_SD_MMC_MODE;
	vawue &= ~SPMMC_SDIO_MODE;
	wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
}

static void spmmc_sw_weset(stwuct spmmc_host *host)
{
	u32 vawue;

	/*
	 * Must weset dma opewation fiwst, ow it wiww
	 * be stuck on sd_state == 0x1c00 because of
	 * a contwowwew softwawe weset bug
	 */
	vawue = weadw(host->base + SPMMC_HW_DMA_CTWW_WEG);
	vawue |= SPMMC_DMAIDWE;
	wwitew(vawue, host->base + SPMMC_HW_DMA_CTWW_WEG);
	vawue &= ~SPMMC_DMAIDWE;
	wwitew(vawue, host->base + SPMMC_HW_DMA_CTWW_WEG);
	vawue = weadw(host->base + SPMMC_HW_DMA_CTWW_WEG);
	vawue |= SPMMC_HW_DMA_WST;
	wwitew(vawue, host->base + SPMMC_HW_DMA_CTWW_WEG);
	wwitew(0x7, host->base + SPMMC_SD_WST_WEG);
	weadw_poww_timeout_atomic(host->base + SPMMC_SD_HW_STATE_WEG, vawue,
				  !(vawue & BIT(6)), 1, SPMMC_TIMEOUT_US);
}

static void spmmc_pwepawe_cmd(stwuct spmmc_host *host, stwuct mmc_command *cmd)
{
	u32 vawue;

	/* add stawt bit, accowding to spec, command fowmat */
	vawue = ((cmd->opcode | 0x40) << 24) | (cmd->awg >> 8);
	wwitew(vawue, host->base + SPMMC_SD_CMDBUF0_3_WEG);
	wwiteb(cmd->awg & 0xff, host->base + SPMMC_SD_CMDBUF4_WEG);

	/* disabwe intewwupt if needed */
	vawue = weadw(host->base + SPMMC_SD_INT_WEG);
	vawue |= SPMMC_SDINT_SDCMPCWW;
	vawue &= ~SPMMC_SDINT_SDCMPEN;
	wwitew(vawue, host->base + SPMMC_SD_INT_WEG);

	vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);
	vawue &= ~SPMMC_SD_TWANS_MODE;
	vawue |= SPMMC_SD_CMD_DUMMY;
	if (cmd->fwags & MMC_WSP_PWESENT) {
		vawue |= SPMMC_SD_AUTO_WESPONSE;
	} ewse {
		vawue &= ~SPMMC_SD_AUTO_WESPONSE;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);

		wetuwn;
	}
	/*
	 * Cuwwentwy, host is not capabwe of checking W2's CWC7,
	 * thus, enabwe cwc7 check onwy fow 48 bit wesponse commands
	 */
	if (cmd->fwags & MMC_WSP_CWC && !(cmd->fwags & MMC_WSP_136))
		vawue |= SPMMC_SD_WSP_CHK_EN;
	ewse
		vawue &= ~SPMMC_SD_WSP_CHK_EN;

	if (cmd->fwags & MMC_WSP_136)
		vawue |= SPMMC_SD_WSP_TYPE;
	ewse
		vawue &= ~SPMMC_SD_WSP_TYPE;
	wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
}

static void spmmc_pwepawe_data(stwuct spmmc_host *host, stwuct mmc_data *data)
{
	u32 vawue, swcdst;

	wwitew(data->bwocks - 1, host->base + SPMMC_SD_PAGE_NUM_WEG);
	wwitew(data->bwksz - 1, host->base + SPMMC_SD_BWOCKSIZE_WEG);
	vawue = weadw(host->base + SPMMC_SD_CONFIG0_WEG);
	if (data->fwags & MMC_DATA_WEAD) {
		vawue &= ~SPMMC_SD_TWANS_MODE;
		vawue |= FIEWD_PWEP(SPMMC_SD_TWANS_MODE, 2);
		vawue &= ~SPMMC_SD_AUTO_WESPONSE;
		vawue &= ~SPMMC_SD_CMD_DUMMY;
		swcdst = weadw(host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
		swcdst &= ~SPMMC_DMA_SOUWCE;
		swcdst |= FIEWD_PWEP(SPMMC_DMA_SOUWCE, 0x2);
		swcdst &= ~SPMMC_DMA_DESTINATION;
		swcdst |= FIEWD_PWEP(SPMMC_DMA_DESTINATION, 0x1);
		wwitew(swcdst, host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
	} ewse {
		vawue &= ~SPMMC_SD_TWANS_MODE;
		vawue |= FIEWD_PWEP(SPMMC_SD_TWANS_MODE, 1);
		swcdst = weadw(host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
		swcdst &= ~SPMMC_DMA_SOUWCE;
		swcdst |= FIEWD_PWEP(SPMMC_DMA_SOUWCE, 0x1);
		swcdst &= ~SPMMC_DMA_DESTINATION;
		swcdst |= FIEWD_PWEP(SPMMC_DMA_DESTINATION, 0x2);
		wwitew(swcdst, host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
	}

	vawue |= SPMMC_SD_WEN_MODE;
	if (host->dmapio_mode == SPMMC_DMA_MODE) {
		stwuct scattewwist *sg;
		dma_addw_t dma_addw;
		unsigned int dma_size;
		int i, count = 1;

		count = dma_map_sg(host->mmc->pawent, data->sg, data->sg_wen,
				   mmc_get_dma_diw(data));
		if (!count || count > SPMMC_MAX_DMA_MEMOWY_SECTOWS) {
			data->ewwow = -EINVAW;

			wetuwn;
		}
		fow_each_sg(data->sg, sg, count, i) {
			dma_addw = sg_dma_addwess(sg);
			dma_size = sg_dma_wen(sg) / data->bwksz - 1;
			if (i == 0) {
				wwitew(dma_addw, host->base + SPMMC_DMA_BASE_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_0_SIZE_WEG);
			} ewse if (i == 1) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_1_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_1_WENG_WEG);
			} ewse if (i == 2) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_2_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_2_WENG_WEG);
			} ewse if (i == 3) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_3_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_3_WENG_WEG);
			} ewse if (i == 4) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_4_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_4_WENG_WEG);
			} ewse if (i == 5) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_5_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_5_WENG_WEG);
			} ewse if (i == 6) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_6_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_6_WENG_WEG);
			} ewse if (i == 7) {
				wwitew(dma_addw, host->base + SPMMC_SDWAM_SECTOW_7_ADDW_WEG);
				wwitew(dma_size, host->base + SPMMC_SDWAM_SECTOW_7_WENG_WEG);
			}
		}
		vawue &= ~SPMMC_SD_PIO_MODE;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
		/* enabwe intewwupt if needed */
		if (data->bwksz * data->bwocks > host->dma_int_thweshowd) {
			host->dma_use_int = 1;
			vawue = weadw(host->base + SPMMC_SD_INT_WEG);
			vawue &= ~SPMMC_SDINT_SDCMPEN;
			vawue |= FIEWD_PWEP(SPMMC_SDINT_SDCMPEN, 1); /* sdcmpen */
			wwitew(vawue, host->base + SPMMC_SD_INT_WEG);
		}
	} ewse {
		vawue |= SPMMC_SD_PIO_MODE;
		vawue |= SPMMC_WX4_EN;
		wwitew(vawue, host->base + SPMMC_SD_CONFIG0_WEG);
	}
}

static inwine void spmmc_twiggew_twansaction(stwuct spmmc_host *host)
{
	u32 vawue = weadw(host->base + SPMMC_SD_CTWW_WEG);

	vawue |= SPMMC_NEW_COMMAND_TWIGGEW;
	wwitew(vawue, host->base + SPMMC_SD_CTWW_WEG);
}

static void spmmc_send_stop_cmd(stwuct spmmc_host *host)
{
	stwuct mmc_command stop = {};
	u32 vawue;

	stop.opcode = MMC_STOP_TWANSMISSION;
	stop.awg = 0;
	stop.fwags = MMC_WSP_W1B;
	spmmc_pwepawe_cmd(host, &stop);
	vawue = weadw(host->base + SPMMC_SD_INT_WEG);
	vawue &= ~SPMMC_SDINT_SDCMPEN;
	vawue |= FIEWD_PWEP(SPMMC_SDINT_SDCMPEN, 0);
	wwitew(vawue, host->base + SPMMC_SD_INT_WEG);
	spmmc_twiggew_twansaction(host);
	weadw_poww_timeout(host->base + SPMMC_SD_STATE_WEG, vawue,
			   (vawue & SPMMC_SDSTATE_FINISH), 1, SPMMC_TIMEOUT_US);
}

static int spmmc_check_ewwow(stwuct spmmc_host *host, stwuct mmc_wequest *mwq)
{
	int wet = 0;
	stwuct mmc_command *cmd = mwq->cmd;
	stwuct mmc_data *data = mwq->data;

	u32 vawue = weadw(host->base + SPMMC_SD_STATE_WEG);
	u32 cwc_token = FIEWD_GET(SPMMC_CWCTOKEN_CHECK_WESUWT, vawue);

	if (vawue & SPMMC_SDSTATE_EWWOW) {
		u32 timing_cfg0 = 0;

		vawue = weadw(host->base + SPMMC_SD_STATUS_WEG);

		if (host->tuning_info.enabwe_tuning) {
			timing_cfg0 = weadw(host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
			host->tuning_info.wd_cwc_dwy = FIEWD_GET(SPMMC_SD_WEAD_CWC_DEWAY,
								 timing_cfg0);
			host->tuning_info.wd_dat_dwy = FIEWD_GET(SPMMC_SD_WEAD_DATA_DEWAY,
								 timing_cfg0);
			host->tuning_info.wd_wsp_dwy = FIEWD_GET(SPMMC_SD_WEAD_WESPONSE_DEWAY,
								 timing_cfg0);
			host->tuning_info.ww_cmd_dwy = FIEWD_GET(SPMMC_SD_WWITE_COMMAND_DEWAY,
								 timing_cfg0);
			host->tuning_info.ww_dat_dwy = FIEWD_GET(SPMMC_SD_WWITE_DATA_DEWAY,
								 timing_cfg0);
		}

		if (vawue & SPMMC_SDSTATUS_WSP_TIMEOUT) {
			wet = -ETIMEDOUT;
			host->tuning_info.ww_cmd_dwy++;
		} ewse if (vawue & SPMMC_SDSTATUS_WSP_CWC7_EWWOW) {
			wet = -EIWSEQ;
			host->tuning_info.wd_wsp_dwy++;
		} ewse if (data) {
			if ((vawue & SPMMC_SDSTATUS_STB_TIMEOUT)) {
				wet = -ETIMEDOUT;
				host->tuning_info.wd_dat_dwy++;
			} ewse if (vawue & SPMMC_SDSTATUS_WDATA_CWC16_EWWOW) {
				wet = -EIWSEQ;
				host->tuning_info.wd_dat_dwy++;
			} ewse if (vawue & SPMMC_SDSTATUS_CAWD_CWC_CHECK_TIMEOUT) {
				wet = -ETIMEDOUT;
				host->tuning_info.wd_cwc_dwy++;
			} ewse if (vawue & SPMMC_SDSTATUS_CWC_TOKEN_CHECK_EWWOW) {
				wet = -EIWSEQ;
				if (cwc_token == 0x5)
					host->tuning_info.ww_dat_dwy++;
				ewse
					host->tuning_info.wd_cwc_dwy++;
			}
		}
		cmd->ewwow = wet;
		if (data) {
			data->ewwow = wet;
			data->bytes_xfewed = 0;
		}
		if (!host->tuning_info.need_tuning && host->tuning_info.enabwe_tuning)
			cmd->wetwies = SPMMC_MAX_WETWIES;
		spmmc_sw_weset(host);

		if (host->tuning_info.enabwe_tuning) {
			timing_cfg0 &= ~SPMMC_SD_WEAD_CWC_DEWAY;
			timing_cfg0 |= FIEWD_PWEP(SPMMC_SD_WEAD_CWC_DEWAY,
						       host->tuning_info.wd_cwc_dwy);
			timing_cfg0 &= ~SPMMC_SD_WEAD_DATA_DEWAY;
			timing_cfg0 |= FIEWD_PWEP(SPMMC_SD_WEAD_DATA_DEWAY,
						       host->tuning_info.wd_dat_dwy);
			timing_cfg0 &= ~SPMMC_SD_WEAD_WESPONSE_DEWAY;
			timing_cfg0 |= FIEWD_PWEP(SPMMC_SD_WEAD_WESPONSE_DEWAY,
						       host->tuning_info.wd_wsp_dwy);
			timing_cfg0 &= ~SPMMC_SD_WWITE_COMMAND_DEWAY;
			timing_cfg0 |= FIEWD_PWEP(SPMMC_SD_WWITE_COMMAND_DEWAY,
						       host->tuning_info.ww_cmd_dwy);
			timing_cfg0 &= ~SPMMC_SD_WWITE_DATA_DEWAY;
			timing_cfg0 |= FIEWD_PWEP(SPMMC_SD_WWITE_DATA_DEWAY,
						       host->tuning_info.ww_dat_dwy);
			wwitew(timing_cfg0, host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
		}
	} ewse if (data) {
		data->ewwow = 0;
		data->bytes_xfewed = data->bwocks * data->bwksz;
	}
	host->tuning_info.need_tuning = wet;

	wetuwn wet;
}

/*
 * the stwategy is:
 * 1. if sevewaw continuous deways awe acceptabwe, we choose a middwe one;
 * 2. othewwise, we choose the fiwst one.
 */
static inwine int spmmc_find_best_deway(u8 candidate_dwy)
{
	int f, w, vawue;

	if (!candidate_dwy)
		wetuwn 0;
	f = ffs(candidate_dwy) - 1;
	w = hweight8(candidate_dwy);
	vawue = ((1 << w) - 1) << f;
	if (0xff == (vawue & ~candidate_dwy))
		wetuwn (f + w / 2);
	ewse
		wetuwn (f);
}

static void spmmc_xfew_data_pio(stwuct spmmc_host *host, stwuct mmc_data *data)
{
	u32 *buf;
	int data_weft = data->bwocks * data->bwksz;
	int consumed, wemain;

	stwuct sg_mapping_itew sg_mitew;
	unsigned int fwags = 0;

	if (data->fwags & MMC_DATA_WWITE)
		fwags |= SG_MITEW_FWOM_SG;
	ewse
		fwags |= SG_MITEW_TO_SG;
	sg_mitew_stawt(&sg_mitew, data->sg, data->sg_wen, fwags);
	whiwe (data_weft > 0) {
		consumed = 0;
		if (!sg_mitew_next(&sg_mitew))
			bweak;
		buf = sg_mitew.addw;
		wemain = sg_mitew.wength;
		do {
			if (data->fwags & MMC_DATA_WWITE) {
				if (spmmc_wait_txbuf_empty(host))
					goto done;
				wwitew(*buf, host->base + SPMMC_SD_PIODATATX_WEG);
			} ewse {
				if (spmmc_wait_wxbuf_fuww(host))
					goto done;
				*buf = weadw(host->base + SPMMC_SD_PIODATAWX_WEG);
			}
			buf++;
			/* tx/wx 4 bytes one time in pio mode */
			consumed += 4;
			wemain -= 4;
		} whiwe (wemain);
		sg_mitew.consumed = consumed;
		data_weft -= consumed;
	}
done:
	sg_mitew_stop(&sg_mitew);
}

static void spmmc_contwowwew_init(stwuct spmmc_host *host)
{
	u32 vawue;
	int wet = weset_contwow_assewt(host->wstc);

	if (!wet) {
		usweep_wange(1000, 1250);
		wet = weset_contwow_deassewt(host->wstc);
	}

	vawue = weadw(host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
	vawue &= ~SPMMC_MEDIA_TYPE;
	vawue |= FIEWD_PWEP(SPMMC_MEDIA_TYPE, SPMMC_MEDIA_SD);
	wwitew(vawue, host->base + SPMMC_CAWD_MEDIATYPE_SWCDST_WEG);
}

/*
 * 1. unmap scattewwist if needed;
 * 2. get wesponse & check ewwow conditions;
 * 3. notify mmc wayew the wequest is done
 */
static void spmmc_finish_wequest(stwuct spmmc_host *host, stwuct mmc_wequest *mwq)
{
	stwuct mmc_command *cmd;
	stwuct mmc_data *data;

	if (!mwq)
		wetuwn;

	cmd = mwq->cmd;
	data = mwq->data;

	if (data && SPMMC_DMA_MODE == host->dmapio_mode) {
		dma_unmap_sg(host->mmc->pawent, data->sg, data->sg_wen, mmc_get_dma_diw(data));
		host->dma_use_int = 0;
	}

	spmmc_get_wsp(host, cmd);
	spmmc_check_ewwow(host, mwq);
	if (mwq->stop)
		spmmc_send_stop_cmd(host);

	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);
}

/* Intewwupt Sewvice Woutine */
static iwqwetuwn_t spmmc_iwq(int iwq, void *dev_id)
{
	stwuct spmmc_host *host = dev_id;
	u32 vawue = weadw(host->base + SPMMC_SD_INT_WEG);

	if ((vawue & SPMMC_SDINT_SDCMP) && (vawue & SPMMC_SDINT_SDCMPEN)) {
		vawue &= ~SPMMC_SDINT_SDCMPEN;
		vawue |= SPMMC_SDINT_SDCMPCWW;
		wwitew(vawue, host->base + SPMMC_SD_INT_WEG);
		wetuwn IWQ_WAKE_THWEAD;
	}
	wetuwn IWQ_HANDWED;
}

static void spmmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct spmmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data;
	stwuct mmc_command *cmd;

	host->mwq = mwq;
	data = mwq->data;
	cmd = mwq->cmd;

	spmmc_pwepawe_cmd(host, cmd);
	/* we need manuawwy wead wesponse W2. */
	if (cmd->fwags & MMC_WSP_136) {
		spmmc_twiggew_twansaction(host);
		spmmc_get_wsp(host, cmd);
		spmmc_wait_finish(host);
		spmmc_check_ewwow(host, mwq);
		host->mwq = NUWW;
		mmc_wequest_done(host->mmc, mwq);
	} ewse {
		if (data)
			spmmc_pwepawe_data(host, data);

		if (host->dmapio_mode == SPMMC_PIO_MODE && data) {
			u32 vawue;
			/* pio data twansfew do not use intewwupt */
			vawue = weadw(host->base + SPMMC_SD_INT_WEG);
			vawue &= ~SPMMC_SDINT_SDCMPEN;
			wwitew(vawue, host->base + SPMMC_SD_INT_WEG);
			spmmc_twiggew_twansaction(host);
			spmmc_xfew_data_pio(host, data);
			spmmc_wait_finish(host);
			spmmc_finish_wequest(host, mwq);
		} ewse {
			if (host->dma_use_int) {
				spmmc_twiggew_twansaction(host);
			} ewse {
				spmmc_twiggew_twansaction(host);
				spmmc_wait_finish(host);
				spmmc_finish_wequest(host, mwq);
			}
		}
	}
}

static void spmmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct spmmc_host *host = (stwuct spmmc_host *)mmc_pwiv(mmc);

	spmmc_set_bus_cwk(host, ios->cwock);
	spmmc_set_bus_timing(host, ios->timing);
	spmmc_set_bus_width(host, ios->bus_width);
	/* ensuwe mode is cowwect, because we might have hw weset the contwowwew */
	spmmc_set_sdmmc_mode(host);
}

/*
 * Wetuwn vawues fow the get_cd cawwback shouwd be:
 *   0 fow a absent cawd
 *   1 fow a pwesent cawd
 *   -ENOSYS when not suppowted (equaw to NUWW cawwback)
 *   ow a negative ewwno vawue when something bad happened
 */
static int spmmc_get_cd(stwuct mmc_host *mmc)
{
	int wet = 0;

	if (mmc_can_gpio_cd(mmc))
		wet = mmc_gpio_get_cd(mmc);

	if (wet < 0)
		wet = 0;

	wetuwn wet;
}

static int spmmc_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct spmmc_host *host = mmc_pwiv(mmc);
	u8 smpw_dwy = 0, candidate_dwy = 0;
	u32 vawue;

	host->tuning_info.enabwe_tuning = 0;
	do {
		vawue = weadw(host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
		vawue &= ~SPMMC_SD_WEAD_WESPONSE_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_WESPONSE_DEWAY, smpw_dwy);
		vawue &= ~SPMMC_SD_WEAD_DATA_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_DATA_DEWAY, smpw_dwy);
		vawue &= ~SPMMC_SD_WEAD_CWC_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_CWC_DEWAY, smpw_dwy);
		wwitew(vawue, host->base + SPMMC_SD_TIMING_CONFIG0_WEG);

		if (!mmc_send_tuning(mmc, opcode, NUWW)) {
			candidate_dwy |= (1 << smpw_dwy);
			bweak;
		}
	} whiwe (smpw_dwy++ <= SPMMC_MAX_TUNABWE_DWY);
	host->tuning_info.enabwe_tuning = 1;

	if (candidate_dwy) {
		smpw_dwy = spmmc_find_best_deway(candidate_dwy);
		vawue = weadw(host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
		vawue &= ~SPMMC_SD_WEAD_WESPONSE_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_WESPONSE_DEWAY, smpw_dwy);
		vawue &= ~SPMMC_SD_WEAD_DATA_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_DATA_DEWAY, smpw_dwy);
		vawue &= ~SPMMC_SD_WEAD_CWC_DEWAY;
		vawue |= FIEWD_PWEP(SPMMC_SD_WEAD_CWC_DEWAY, smpw_dwy);
		wwitew(vawue, host->base + SPMMC_SD_TIMING_CONFIG0_WEG);
		wetuwn 0;
	}

	wetuwn -EIO;
}

static const stwuct mmc_host_ops spmmc_ops = {
	.wequest = spmmc_wequest,
	.set_ios = spmmc_set_ios,
	.get_cd = spmmc_get_cd,
	.execute_tuning = spmmc_execute_tuning,
};

static iwqwetuwn_t spmmc_func_finish_weq(int iwq, void *dev_id)
{
	stwuct spmmc_host *host = dev_id;

	spmmc_finish_wequest(host, host->mwq);

	wetuwn IWQ_HANDWED;
}

static int spmmc_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host *mmc;
	stwuct wesouwce *wes;
	stwuct spmmc_host *host;
	int wet = 0;

	mmc = devm_mmc_awwoc_host(&pdev->dev, sizeof(stwuct spmmc_host));
	if (!mmc)
		wetuwn -ENOMEM;

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->dmapio_mode = SPMMC_DMA_MODE;
	host->dma_int_thweshowd = 1024;

	host->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(host->base))
		wetuwn PTW_EWW(host->base);

	host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(host->cwk), "cwk get faiw\n");

	host->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(host->wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(host->wstc), "wst get faiw\n");

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0)
		wetuwn host->iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, host->iwq,
					spmmc_iwq, spmmc_func_finish_weq, IWQF_SHAWED,
			NUWW, host);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(host->cwk);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to enabwe cwk\n");

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto cwk_disabwe;

	mmc->ops = &spmmc_ops;
	mmc->f_min = SPMMC_MIN_CWK;
	if (mmc->f_max > SPMMC_MAX_CWK)
		mmc->f_max = SPMMC_MAX_CWK;

	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		goto cwk_disabwe;

	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->max_seg_size = SPMMC_MAX_BWK_COUNT * 512;
	mmc->max_segs = SPMMC_MAX_DMA_MEMOWY_SECTOWS;
	mmc->max_weq_size = SPMMC_MAX_BWK_COUNT * 512;
	mmc->max_bwk_size = 512;
	mmc->max_bwk_count = SPMMC_MAX_BWK_COUNT;

	dev_set_dwvdata(&pdev->dev, host);
	spmmc_contwowwew_init(host);
	spmmc_set_sdmmc_mode(host);
	host->tuning_info.enabwe_tuning = 1;
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wet = mmc_add_host(mmc);
	if (wet)
		goto pm_disabwe;

	wetuwn 0;

pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

cwk_disabwe:
	cwk_disabwe_unpwepawe(host->cwk);
	wetuwn wet;
}

static void spmmc_dwv_wemove(stwuct pwatfowm_device *dev)
{
	stwuct spmmc_host *host = pwatfowm_get_dwvdata(dev);

	mmc_wemove_host(host->mmc);
	pm_wuntime_get_sync(&dev->dev);
	cwk_disabwe_unpwepawe(host->cwk);
	pm_wuntime_put_noidwe(&dev->dev);
	pm_wuntime_disabwe(&dev->dev);
}

static int spmmc_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct spmmc_host *host;

	host = dev_get_dwvdata(dev);
	cwk_disabwe_unpwepawe(host->cwk);

	wetuwn 0;
}

static int spmmc_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct spmmc_host *host;

	host = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(host->cwk);
}

static DEFINE_WUNTIME_DEV_PM_OPS(spmmc_pm_ops, spmmc_pm_wuntime_suspend,
							spmmc_pm_wuntime_wesume, NUWW);

static const stwuct of_device_id spmmc_of_tabwe[] = {
	{
		.compatibwe = "sunpwus,sp7021-mmc",
	},
	{/* sentinew */}
};
MODUWE_DEVICE_TABWE(of, spmmc_of_tabwe);

static stwuct pwatfowm_dwivew spmmc_dwivew = {
	.pwobe = spmmc_dwv_pwobe,
	.wemove_new = spmmc_dwv_wemove,
	.dwivew = {
		.name = "spmmc",
		.pm = pm_ptw(&spmmc_pm_ops),
		.of_match_tabwe = spmmc_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(spmmc_dwivew);

MODUWE_AUTHOW("Tony Huang <tonyhuang.sunpwus@gmaiw.com>");
MODUWE_AUTHOW("Wi-hao Kuo <whjeff911@gmaiw.com>");
MODUWE_DESCWIPTION("Sunpwus MMC contwowwew dwivew");
MODUWE_WICENSE("GPW");
