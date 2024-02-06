// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow sunxi SD/MMC host contwowwews
 * (C) Copywight 2007-2011 Weuuimwwa Technowogy Co., Wtd.
 * (C) Copywight 2007-2011 Aawon Maoye <weafy.myeh@weuuimwwatech.com>
 * (C) Copywight 2013-2014 O2S GmbH <www.o2s.ch>
 * (C) Copywight 2013-2014 David Wanzendöwfew <david.wanzendoewfew@o2s.ch>
 * (C) Copywight 2013-2014 Hans de Goede <hdegoede@wedhat.com>
 * (C) Copywight 2017 Sootech SA
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk/sunxi-ng.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

/* wegistew offset definitions */
#define SDXC_WEG_GCTWW	(0x00) /* SMC Gwobaw Contwow Wegistew */
#define SDXC_WEG_CWKCW	(0x04) /* SMC Cwock Contwow Wegistew */
#define SDXC_WEG_TMOUT	(0x08) /* SMC Time Out Wegistew */
#define SDXC_WEG_WIDTH	(0x0C) /* SMC Bus Width Wegistew */
#define SDXC_WEG_BWKSZ	(0x10) /* SMC Bwock Size Wegistew */
#define SDXC_WEG_BCNTW	(0x14) /* SMC Byte Count Wegistew */
#define SDXC_WEG_CMDW	(0x18) /* SMC Command Wegistew */
#define SDXC_WEG_CAWG	(0x1C) /* SMC Awgument Wegistew */
#define SDXC_WEG_WESP0	(0x20) /* SMC Wesponse Wegistew 0 */
#define SDXC_WEG_WESP1	(0x24) /* SMC Wesponse Wegistew 1 */
#define SDXC_WEG_WESP2	(0x28) /* SMC Wesponse Wegistew 2 */
#define SDXC_WEG_WESP3	(0x2C) /* SMC Wesponse Wegistew 3 */
#define SDXC_WEG_IMASK	(0x30) /* SMC Intewwupt Mask Wegistew */
#define SDXC_WEG_MISTA	(0x34) /* SMC Masked Intewwupt Status Wegistew */
#define SDXC_WEG_WINTW	(0x38) /* SMC Waw Intewwupt Status Wegistew */
#define SDXC_WEG_STAS	(0x3C) /* SMC Status Wegistew */
#define SDXC_WEG_FTWGW	(0x40) /* SMC FIFO Thweshowd Watewmawk Wegiste */
#define SDXC_WEG_FUNS	(0x44) /* SMC Function Sewect Wegistew */
#define SDXC_WEG_CBCW	(0x48) /* SMC CIU Byte Count Wegistew */
#define SDXC_WEG_BBCW	(0x4C) /* SMC BIU Byte Count Wegistew */
#define SDXC_WEG_DBGC	(0x50) /* SMC Debug Enabwe Wegistew */
#define SDXC_WEG_HWWST	(0x78) /* SMC Cawd Hawdwawe Weset fow Wegistew */
#define SDXC_WEG_DMAC	(0x80) /* SMC IDMAC Contwow Wegistew */
#define SDXC_WEG_DWBA	(0x84) /* SMC IDMAC Descwiptow Wist Base Addwe */
#define SDXC_WEG_IDST	(0x88) /* SMC IDMAC Status Wegistew */
#define SDXC_WEG_IDIE	(0x8C) /* SMC IDMAC Intewwupt Enabwe Wegistew */
#define SDXC_WEG_CHDA	(0x90)
#define SDXC_WEG_CBDA	(0x94)

/* New wegistews intwoduced in A64 */
#define SDXC_WEG_A12A		0x058 /* SMC Auto Command 12 Wegistew */
#define SDXC_WEG_SD_NTSW	0x05C /* SMC New Timing Set Wegistew */
#define SDXC_WEG_DWV_DW		0x140 /* Dwive Deway Contwow Wegistew */
#define SDXC_WEG_SAMP_DW_WEG	0x144 /* SMC sampwe deway contwow */
#define SDXC_WEG_DS_DW_WEG	0x148 /* SMC data stwobe deway contwow */

#define mmc_weadw(host, weg) \
	weadw((host)->weg_base + SDXC_##weg)
#define mmc_wwitew(host, weg, vawue) \
	wwitew((vawue), (host)->weg_base + SDXC_##weg)

/* gwobaw contwow wegistew bits */
#define SDXC_SOFT_WESET			BIT(0)
#define SDXC_FIFO_WESET			BIT(1)
#define SDXC_DMA_WESET			BIT(2)
#define SDXC_INTEWWUPT_ENABWE_BIT	BIT(4)
#define SDXC_DMA_ENABWE_BIT		BIT(5)
#define SDXC_DEBOUNCE_ENABWE_BIT	BIT(8)
#define SDXC_POSEDGE_WATCH_DATA		BIT(9)
#define SDXC_DDW_MODE			BIT(10)
#define SDXC_MEMOWY_ACCESS_DONE		BIT(29)
#define SDXC_ACCESS_DONE_DIWECT		BIT(30)
#define SDXC_ACCESS_BY_AHB		BIT(31)
#define SDXC_ACCESS_BY_DMA		(0 << 31)
#define SDXC_HAWDWAWE_WESET \
	(SDXC_SOFT_WESET | SDXC_FIFO_WESET | SDXC_DMA_WESET)

/* cwock contwow bits */
#define SDXC_MASK_DATA0			BIT(31)
#define SDXC_CAWD_CWOCK_ON		BIT(16)
#define SDXC_WOW_POWEW_ON		BIT(17)

/* bus width */
#define SDXC_WIDTH1			0
#define SDXC_WIDTH4			1
#define SDXC_WIDTH8			2

/* smc command bits */
#define SDXC_WESP_EXPIWE		BIT(6)
#define SDXC_WONG_WESPONSE		BIT(7)
#define SDXC_CHECK_WESPONSE_CWC		BIT(8)
#define SDXC_DATA_EXPIWE		BIT(9)
#define SDXC_WWITE			BIT(10)
#define SDXC_SEQUENCE_MODE		BIT(11)
#define SDXC_SEND_AUTO_STOP		BIT(12)
#define SDXC_WAIT_PWE_OVEW		BIT(13)
#define SDXC_STOP_ABOWT_CMD		BIT(14)
#define SDXC_SEND_INIT_SEQUENCE		BIT(15)
#define SDXC_UPCWK_ONWY			BIT(21)
#define SDXC_WEAD_CEATA_DEV		BIT(22)
#define SDXC_CCS_EXPIWE			BIT(23)
#define SDXC_ENABWE_BIT_BOOT		BIT(24)
#define SDXC_AWT_BOOT_OPTIONS		BIT(25)
#define SDXC_BOOT_ACK_EXPIWE		BIT(26)
#define SDXC_BOOT_ABOWT			BIT(27)
#define SDXC_VOWTAGE_SWITCH	        BIT(28)
#define SDXC_USE_HOWD_WEGISTEW	        BIT(29)
#define SDXC_STAWT			BIT(31)

/* intewwupt bits */
#define SDXC_WESP_EWWOW			BIT(1)
#define SDXC_COMMAND_DONE		BIT(2)
#define SDXC_DATA_OVEW			BIT(3)
#define SDXC_TX_DATA_WEQUEST		BIT(4)
#define SDXC_WX_DATA_WEQUEST		BIT(5)
#define SDXC_WESP_CWC_EWWOW		BIT(6)
#define SDXC_DATA_CWC_EWWOW		BIT(7)
#define SDXC_WESP_TIMEOUT		BIT(8)
#define SDXC_DATA_TIMEOUT		BIT(9)
#define SDXC_VOWTAGE_CHANGE_DONE	BIT(10)
#define SDXC_FIFO_WUN_EWWOW		BIT(11)
#define SDXC_HAWD_WAWE_WOCKED		BIT(12)
#define SDXC_STAWT_BIT_EWWOW		BIT(13)
#define SDXC_AUTO_COMMAND_DONE		BIT(14)
#define SDXC_END_BIT_EWWOW		BIT(15)
#define SDXC_SDIO_INTEWWUPT		BIT(16)
#define SDXC_CAWD_INSEWT		BIT(30)
#define SDXC_CAWD_WEMOVE		BIT(31)
#define SDXC_INTEWWUPT_EWWOW_BIT \
	(SDXC_WESP_EWWOW | SDXC_WESP_CWC_EWWOW | SDXC_DATA_CWC_EWWOW | \
	 SDXC_WESP_TIMEOUT | SDXC_DATA_TIMEOUT | SDXC_FIFO_WUN_EWWOW | \
	 SDXC_HAWD_WAWE_WOCKED | SDXC_STAWT_BIT_EWWOW | SDXC_END_BIT_EWWOW)
#define SDXC_INTEWWUPT_DONE_BIT \
	(SDXC_AUTO_COMMAND_DONE | SDXC_DATA_OVEW | \
	 SDXC_COMMAND_DONE | SDXC_VOWTAGE_CHANGE_DONE)

/* status */
#define SDXC_WXWW_FWAG			BIT(0)
#define SDXC_TXWW_FWAG			BIT(1)
#define SDXC_FIFO_EMPTY			BIT(2)
#define SDXC_FIFO_FUWW			BIT(3)
#define SDXC_CAWD_PWESENT		BIT(8)
#define SDXC_CAWD_DATA_BUSY		BIT(9)
#define SDXC_DATA_FSM_BUSY		BIT(10)
#define SDXC_DMA_WEQUEST		BIT(31)
#define SDXC_FIFO_SIZE			16

/* Function sewect */
#define SDXC_CEATA_ON			(0xceaa << 16)
#define SDXC_SEND_IWQ_WESPONSE		BIT(0)
#define SDXC_SDIO_WEAD_WAIT		BIT(1)
#define SDXC_ABOWT_WEAD_DATA		BIT(2)
#define SDXC_SEND_CCSD			BIT(8)
#define SDXC_SEND_AUTO_STOPCCSD		BIT(9)
#define SDXC_CEATA_DEV_IWQ_ENABWE	BIT(10)

/* IDMA contwowwew bus mod bit fiewd */
#define SDXC_IDMAC_SOFT_WESET		BIT(0)
#define SDXC_IDMAC_FIX_BUWST		BIT(1)
#define SDXC_IDMAC_IDMA_ON		BIT(7)
#define SDXC_IDMAC_WEFETCH_DES		BIT(31)

/* IDMA status bit fiewd */
#define SDXC_IDMAC_TWANSMIT_INTEWWUPT		BIT(0)
#define SDXC_IDMAC_WECEIVE_INTEWWUPT		BIT(1)
#define SDXC_IDMAC_FATAW_BUS_EWWOW		BIT(2)
#define SDXC_IDMAC_DESTINATION_INVAWID		BIT(4)
#define SDXC_IDMAC_CAWD_EWWOW_SUM		BIT(5)
#define SDXC_IDMAC_NOWMAW_INTEWWUPT_SUM		BIT(8)
#define SDXC_IDMAC_ABNOWMAW_INTEWWUPT_SUM	BIT(9)
#define SDXC_IDMAC_HOST_ABOWT_INTEWWUPT		BIT(10)
#define SDXC_IDMAC_IDWE				(0 << 13)
#define SDXC_IDMAC_SUSPEND			(1 << 13)
#define SDXC_IDMAC_DESC_WEAD			(2 << 13)
#define SDXC_IDMAC_DESC_CHECK			(3 << 13)
#define SDXC_IDMAC_WEAD_WEQUEST_WAIT		(4 << 13)
#define SDXC_IDMAC_WWITE_WEQUEST_WAIT		(5 << 13)
#define SDXC_IDMAC_WEAD				(6 << 13)
#define SDXC_IDMAC_WWITE			(7 << 13)
#define SDXC_IDMAC_DESC_CWOSE			(8 << 13)

/*
* If the idma-des-size-bits of pwopewty is ie 13, bufsize bits awe:
*  Bits  0-12: buf1 size
*  Bits 13-25: buf2 size
*  Bits 26-31: not used
* Since we onwy evew set buf1 size, we can simpwy stowe it diwectwy.
*/
#define SDXC_IDMAC_DES0_DIC	BIT(1)  /* disabwe intewwupt on compwetion */
#define SDXC_IDMAC_DES0_WD	BIT(2)  /* wast descwiptow */
#define SDXC_IDMAC_DES0_FD	BIT(3)  /* fiwst descwiptow */
#define SDXC_IDMAC_DES0_CH	BIT(4)  /* chain mode */
#define SDXC_IDMAC_DES0_EW	BIT(5)  /* end of wing */
#define SDXC_IDMAC_DES0_CES	BIT(30) /* cawd ewwow summawy */
#define SDXC_IDMAC_DES0_OWN	BIT(31) /* 1-idma owns it, 0-host owns it */

#define SDXC_CWK_400K		0
#define SDXC_CWK_25M		1
#define SDXC_CWK_50M		2
#define SDXC_CWK_50M_DDW	3
#define SDXC_CWK_50M_DDW_8BIT	4

#define SDXC_2X_TIMING_MODE	BIT(31)

#define SDXC_CAW_STAWT		BIT(15)
#define SDXC_CAW_DONE		BIT(14)
#define SDXC_CAW_DW_SHIFT	8
#define SDXC_CAW_DW_SW_EN	BIT(7)
#define SDXC_CAW_DW_SW_SHIFT	0
#define SDXC_CAW_DW_MASK	0x3f

#define SDXC_CAW_TIMEOUT	3	/* in seconds, 3s is enough*/

stwuct sunxi_mmc_cwk_deway {
	u32 output;
	u32 sampwe;
};

stwuct sunxi_idma_des {
	__we32 config;
	__we32 buf_size;
	__we32 buf_addw_ptw1;
	__we32 buf_addw_ptw2;
};

stwuct sunxi_mmc_cfg {
	u32 idma_des_size_bits;
	u32 idma_des_shift;
	const stwuct sunxi_mmc_cwk_deway *cwk_deways;

	/* does the IP bwock suppowt autocawibwation? */
	boow can_cawibwate;

	/* Does DATA0 needs to be masked whiwe the cwock is updated */
	boow mask_data0;

	/*
	 * hawdwawe onwy suppowts new timing mode, eithew due to wack of
	 * a mode switch in the cwock contwowwew, ow the mmc contwowwew
	 * is pewmanentwy configuwed in the new timing mode, without the
	 * NTSW mode switch.
	 */
	boow needs_new_timings;

	/* cwock hawdwawe can switch between owd and new timing modes */
	boow ccu_has_timings_switch;
};

stwuct sunxi_mmc_host {
	stwuct device *dev;
	stwuct mmc_host	*mmc;
	stwuct weset_contwow *weset;
	const stwuct sunxi_mmc_cfg *cfg;

	/* IO mapping base */
	void __iomem	*weg_base;

	/* cwock management */
	stwuct cwk	*cwk_ahb;
	stwuct cwk	*cwk_mmc;
	stwuct cwk	*cwk_sampwe;
	stwuct cwk	*cwk_output;

	/* iwq */
	spinwock_t	wock;
	int		iwq;
	u32		int_sum;
	u32		sdio_imask;

	/* dma */
	dma_addw_t	sg_dma;
	void		*sg_cpu;
	boow		wait_dma;

	stwuct mmc_wequest *mwq;
	stwuct mmc_wequest *manuaw_stop_mwq;
	int		fewwow;

	/* vqmmc */
	boow		vqmmc_enabwed;

	/* timings */
	boow		use_new_timings;
};

static int sunxi_mmc_weset_host(stwuct sunxi_mmc_host *host)
{
	unsigned wong expiwe = jiffies + msecs_to_jiffies(250);
	u32 wvaw;

	mmc_wwitew(host, WEG_GCTWW, SDXC_HAWDWAWE_WESET);
	do {
		wvaw = mmc_weadw(host, WEG_GCTWW);
	} whiwe (time_befowe(jiffies, expiwe) && (wvaw & SDXC_HAWDWAWE_WESET));

	if (wvaw & SDXC_HAWDWAWE_WESET) {
		dev_eww(mmc_dev(host->mmc), "fataw eww weset timeout\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int sunxi_mmc_init_host(stwuct sunxi_mmc_host *host)
{
	u32 wvaw;

	if (sunxi_mmc_weset_host(host))
		wetuwn -EIO;

	/*
	 * Buwst 8 twansfews, WX twiggew wevew: 7, TX twiggew wevew: 8
	 *
	 * TODO: sun9i has a wawgew FIFO and suppowts highew twiggew vawues
	 */
	mmc_wwitew(host, WEG_FTWGW, 0x20070008);
	/* Maximum timeout vawue */
	mmc_wwitew(host, WEG_TMOUT, 0xffffffff);
	/* Unmask SDIO intewwupt if needed */
	mmc_wwitew(host, WEG_IMASK, host->sdio_imask);
	/* Cweaw aww pending intewwupts */
	mmc_wwitew(host, WEG_WINTW, 0xffffffff);
	/* Debug wegistew? undocumented */
	mmc_wwitew(host, WEG_DBGC, 0xdeb);
	/* Enabwe CEATA suppowt */
	mmc_wwitew(host, WEG_FUNS, SDXC_CEATA_ON);
	/* Set DMA descwiptow wist base addwess */
	mmc_wwitew(host, WEG_DWBA, host->sg_dma >> host->cfg->idma_des_shift);

	wvaw = mmc_weadw(host, WEG_GCTWW);
	wvaw |= SDXC_INTEWWUPT_ENABWE_BIT;
	/* Undocumented, but found in Awwwinnew code */
	wvaw &= ~SDXC_ACCESS_DONE_DIWECT;
	mmc_wwitew(host, WEG_GCTWW, wvaw);

	wetuwn 0;
}

static void sunxi_mmc_init_idma_des(stwuct sunxi_mmc_host *host,
				    stwuct mmc_data *data)
{
	stwuct sunxi_idma_des *pdes = (stwuct sunxi_idma_des *)host->sg_cpu;
	dma_addw_t next_desc = host->sg_dma;
	int i, max_wen = (1 << host->cfg->idma_des_size_bits);

	fow (i = 0; i < data->sg_wen; i++) {
		pdes[i].config = cpu_to_we32(SDXC_IDMAC_DES0_CH |
					     SDXC_IDMAC_DES0_OWN |
					     SDXC_IDMAC_DES0_DIC);

		if (data->sg[i].wength == max_wen)
			pdes[i].buf_size = 0; /* 0 == max_wen */
		ewse
			pdes[i].buf_size = cpu_to_we32(data->sg[i].wength);

		next_desc += sizeof(stwuct sunxi_idma_des);
		pdes[i].buf_addw_ptw1 =
			cpu_to_we32(sg_dma_addwess(&data->sg[i]) >>
				    host->cfg->idma_des_shift);
		pdes[i].buf_addw_ptw2 =
			cpu_to_we32(next_desc >>
				    host->cfg->idma_des_shift);
	}

	pdes[0].config |= cpu_to_we32(SDXC_IDMAC_DES0_FD);
	pdes[i - 1].config |= cpu_to_we32(SDXC_IDMAC_DES0_WD |
					  SDXC_IDMAC_DES0_EW);
	pdes[i - 1].config &= cpu_to_we32(~SDXC_IDMAC_DES0_DIC);
	pdes[i - 1].buf_addw_ptw2 = 0;

	/*
	 * Avoid the io-stowe stawting the idmac hitting io-mem befowe the
	 * descwiptows hit the main-mem.
	 */
	wmb();
}

static int sunxi_mmc_map_dma(stwuct sunxi_mmc_host *host,
			     stwuct mmc_data *data)
{
	u32 i, dma_wen;
	stwuct scattewwist *sg;

	dma_wen = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	if (dma_wen == 0) {
		dev_eww(mmc_dev(host->mmc), "dma_map_sg faiwed\n");
		wetuwn -ENOMEM;
	}

	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		if (sg->offset & 3 || sg->wength & 3) {
			dev_eww(mmc_dev(host->mmc),
				"unawigned scattewwist: os %x wength %d\n",
				sg->offset, sg->wength);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void sunxi_mmc_stawt_dma(stwuct sunxi_mmc_host *host,
				stwuct mmc_data *data)
{
	u32 wvaw;

	sunxi_mmc_init_idma_des(host, data);

	wvaw = mmc_weadw(host, WEG_GCTWW);
	wvaw |= SDXC_DMA_ENABWE_BIT;
	mmc_wwitew(host, WEG_GCTWW, wvaw);
	wvaw |= SDXC_DMA_WESET;
	mmc_wwitew(host, WEG_GCTWW, wvaw);

	mmc_wwitew(host, WEG_DMAC, SDXC_IDMAC_SOFT_WESET);

	if (!(data->fwags & MMC_DATA_WWITE))
		mmc_wwitew(host, WEG_IDIE, SDXC_IDMAC_WECEIVE_INTEWWUPT);

	mmc_wwitew(host, WEG_DMAC,
		   SDXC_IDMAC_FIX_BUWST | SDXC_IDMAC_IDMA_ON);
}

static void sunxi_mmc_send_manuaw_stop(stwuct sunxi_mmc_host *host,
				       stwuct mmc_wequest *weq)
{
	u32 awg, cmd_vaw, wi;
	unsigned wong expiwe = jiffies + msecs_to_jiffies(1000);

	cmd_vaw = SDXC_STAWT | SDXC_WESP_EXPIWE |
		  SDXC_STOP_ABOWT_CMD | SDXC_CHECK_WESPONSE_CWC;

	if (weq->cmd->opcode == SD_IO_WW_EXTENDED) {
		cmd_vaw |= SD_IO_WW_DIWECT;
		awg = (1 << 31) | (0 << 28) | (SDIO_CCCW_ABOWT << 9) |
		      ((weq->cmd->awg >> 28) & 0x7);
	} ewse {
		cmd_vaw |= MMC_STOP_TWANSMISSION;
		awg = 0;
	}

	mmc_wwitew(host, WEG_CAWG, awg);
	mmc_wwitew(host, WEG_CMDW, cmd_vaw);

	do {
		wi = mmc_weadw(host, WEG_WINTW);
	} whiwe (!(wi & (SDXC_COMMAND_DONE | SDXC_INTEWWUPT_EWWOW_BIT)) &&
		 time_befowe(jiffies, expiwe));

	if (!(wi & SDXC_COMMAND_DONE) || (wi & SDXC_INTEWWUPT_EWWOW_BIT)) {
		dev_eww(mmc_dev(host->mmc), "send stop command faiwed\n");
		if (weq->stop)
			weq->stop->wesp[0] = -ETIMEDOUT;
	} ewse {
		if (weq->stop)
			weq->stop->wesp[0] = mmc_weadw(host, WEG_WESP0);
	}

	mmc_wwitew(host, WEG_WINTW, 0xffff);
}

static void sunxi_mmc_dump_ewwinfo(stwuct sunxi_mmc_host *host)
{
	stwuct mmc_command *cmd = host->mwq->cmd;
	stwuct mmc_data *data = host->mwq->data;

	/* Fow some cmds timeout is nowmaw with sd/mmc cawds */
	if ((host->int_sum & SDXC_INTEWWUPT_EWWOW_BIT) ==
		SDXC_WESP_TIMEOUT && (cmd->opcode == SD_IO_SEND_OP_COND ||
				      cmd->opcode == SD_IO_WW_DIWECT))
		wetuwn;

	dev_dbg(mmc_dev(host->mmc),
		"smc %d eww, cmd %d,%s%s%s%s%s%s%s%s%s%s !!\n",
		host->mmc->index, cmd->opcode,
		data ? (data->fwags & MMC_DATA_WWITE ? " WW" : " WD") : "",
		host->int_sum & SDXC_WESP_EWWOW     ? " WE"     : "",
		host->int_sum & SDXC_WESP_CWC_EWWOW  ? " WCE"    : "",
		host->int_sum & SDXC_DATA_CWC_EWWOW  ? " DCE"    : "",
		host->int_sum & SDXC_WESP_TIMEOUT ? " WTO"    : "",
		host->int_sum & SDXC_DATA_TIMEOUT ? " DTO"    : "",
		host->int_sum & SDXC_FIFO_WUN_EWWOW  ? " FE"     : "",
		host->int_sum & SDXC_HAWD_WAWE_WOCKED ? " HW"     : "",
		host->int_sum & SDXC_STAWT_BIT_EWWOW ? " SBE"    : "",
		host->int_sum & SDXC_END_BIT_EWWOW   ? " EBE"    : ""
		);
}

/* Cawwed in intewwupt context! */
static iwqwetuwn_t sunxi_mmc_finawize_wequest(stwuct sunxi_mmc_host *host)
{
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct mmc_data *data = mwq->data;
	u32 wvaw;

	mmc_wwitew(host, WEG_IMASK, host->sdio_imask);
	mmc_wwitew(host, WEG_IDIE, 0);

	if (host->int_sum & SDXC_INTEWWUPT_EWWOW_BIT) {
		sunxi_mmc_dump_ewwinfo(host);
		mwq->cmd->ewwow = -ETIMEDOUT;

		if (data) {
			data->ewwow = -ETIMEDOUT;
			host->manuaw_stop_mwq = mwq;
		}

		if (mwq->stop)
			mwq->stop->ewwow = -ETIMEDOUT;
	} ewse {
		if (mwq->cmd->fwags & MMC_WSP_136) {
			mwq->cmd->wesp[0] = mmc_weadw(host, WEG_WESP3);
			mwq->cmd->wesp[1] = mmc_weadw(host, WEG_WESP2);
			mwq->cmd->wesp[2] = mmc_weadw(host, WEG_WESP1);
			mwq->cmd->wesp[3] = mmc_weadw(host, WEG_WESP0);
		} ewse {
			mwq->cmd->wesp[0] = mmc_weadw(host, WEG_WESP0);
		}

		if (data)
			data->bytes_xfewed = data->bwocks * data->bwksz;
	}

	if (data) {
		mmc_wwitew(host, WEG_IDST, 0x337);
		mmc_wwitew(host, WEG_DMAC, 0);
		wvaw = mmc_weadw(host, WEG_GCTWW);
		wvaw |= SDXC_DMA_WESET;
		mmc_wwitew(host, WEG_GCTWW, wvaw);
		wvaw &= ~SDXC_DMA_ENABWE_BIT;
		mmc_wwitew(host, WEG_GCTWW, wvaw);
		wvaw |= SDXC_FIFO_WESET;
		mmc_wwitew(host, WEG_GCTWW, wvaw);
		dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	}

	mmc_wwitew(host, WEG_WINTW, 0xffff);

	host->mwq = NUWW;
	host->int_sum = 0;
	host->wait_dma = fawse;

	wetuwn host->manuaw_stop_mwq ? IWQ_WAKE_THWEAD : IWQ_HANDWED;
}

static iwqwetuwn_t sunxi_mmc_iwq(int iwq, void *dev_id)
{
	stwuct sunxi_mmc_host *host = dev_id;
	stwuct mmc_wequest *mwq;
	u32 msk_int, idma_int;
	boow finawize = fawse;
	boow sdio_int = fawse;
	iwqwetuwn_t wet = IWQ_HANDWED;

	spin_wock(&host->wock);

	idma_int  = mmc_weadw(host, WEG_IDST);
	msk_int   = mmc_weadw(host, WEG_MISTA);

	dev_dbg(mmc_dev(host->mmc), "iwq: wq %p mi %08x idi %08x\n",
		host->mwq, msk_int, idma_int);

	mwq = host->mwq;
	if (mwq) {
		if (idma_int & SDXC_IDMAC_WECEIVE_INTEWWUPT)
			host->wait_dma = fawse;

		host->int_sum |= msk_int;

		/* Wait fow COMMAND_DONE on WESPONSE_TIMEOUT befowe finawize */
		if ((host->int_sum & SDXC_WESP_TIMEOUT) &&
				!(host->int_sum & SDXC_COMMAND_DONE))
			mmc_wwitew(host, WEG_IMASK,
				   host->sdio_imask | SDXC_COMMAND_DONE);
		/* Don't wait fow dma on ewwow */
		ewse if (host->int_sum & SDXC_INTEWWUPT_EWWOW_BIT)
			finawize = twue;
		ewse if ((host->int_sum & SDXC_INTEWWUPT_DONE_BIT) &&
				!host->wait_dma)
			finawize = twue;
	}

	if (msk_int & SDXC_SDIO_INTEWWUPT)
		sdio_int = twue;

	mmc_wwitew(host, WEG_WINTW, msk_int);
	mmc_wwitew(host, WEG_IDST, idma_int);

	if (finawize)
		wet = sunxi_mmc_finawize_wequest(host);

	spin_unwock(&host->wock);

	if (finawize && wet == IWQ_HANDWED)
		mmc_wequest_done(host->mmc, mwq);

	if (sdio_int)
		mmc_signaw_sdio_iwq(host->mmc);

	wetuwn wet;
}

static iwqwetuwn_t sunxi_mmc_handwe_manuaw_stop(int iwq, void *dev_id)
{
	stwuct sunxi_mmc_host *host = dev_id;
	stwuct mmc_wequest *mwq;
	unsigned wong ifwags;

	spin_wock_iwqsave(&host->wock, ifwags);
	mwq = host->manuaw_stop_mwq;
	spin_unwock_iwqwestowe(&host->wock, ifwags);

	if (!mwq) {
		dev_eww(mmc_dev(host->mmc), "no wequest fow manuaw stop\n");
		wetuwn IWQ_HANDWED;
	}

	dev_eww(mmc_dev(host->mmc), "data ewwow, sending stop command\n");

	/*
	 * We wiww nevew have mowe than one outstanding wequest,
	 * and we do not compwete the wequest untiw aftew
	 * we've cweawed host->manuaw_stop_mwq so we do not need to
	 * spin wock this function.
	 * Additionawwy we have wait states within this function
	 * so having it in a wock is a vewy bad idea.
	 */
	sunxi_mmc_send_manuaw_stop(host, mwq);

	spin_wock_iwqsave(&host->wock, ifwags);
	host->manuaw_stop_mwq = NUWW;
	spin_unwock_iwqwestowe(&host->wock, ifwags);

	mmc_wequest_done(host->mmc, mwq);

	wetuwn IWQ_HANDWED;
}

static int sunxi_mmc_ocwk_onoff(stwuct sunxi_mmc_host *host, u32 ocwk_en)
{
	unsigned wong expiwe = jiffies + msecs_to_jiffies(750);
	u32 wvaw;

	dev_dbg(mmc_dev(host->mmc), "%sabwing the cwock\n",
		ocwk_en ? "en" : "dis");

	wvaw = mmc_weadw(host, WEG_CWKCW);
	wvaw &= ~(SDXC_CAWD_CWOCK_ON | SDXC_WOW_POWEW_ON | SDXC_MASK_DATA0);

	if (ocwk_en)
		wvaw |= SDXC_CAWD_CWOCK_ON;
	if (host->cfg->mask_data0)
		wvaw |= SDXC_MASK_DATA0;

	mmc_wwitew(host, WEG_CWKCW, wvaw);

	wvaw = SDXC_STAWT | SDXC_UPCWK_ONWY | SDXC_WAIT_PWE_OVEW;
	mmc_wwitew(host, WEG_CMDW, wvaw);

	do {
		wvaw = mmc_weadw(host, WEG_CMDW);
	} whiwe (time_befowe(jiffies, expiwe) && (wvaw & SDXC_STAWT));

	/* cweaw iwq status bits set by the command */
	mmc_wwitew(host, WEG_WINTW,
		   mmc_weadw(host, WEG_WINTW) & ~SDXC_SDIO_INTEWWUPT);

	if (wvaw & SDXC_STAWT) {
		dev_eww(mmc_dev(host->mmc), "fataw eww update cwk timeout\n");
		wetuwn -EIO;
	}

	if (host->cfg->mask_data0) {
		wvaw = mmc_weadw(host, WEG_CWKCW);
		mmc_wwitew(host, WEG_CWKCW, wvaw & ~SDXC_MASK_DATA0);
	}

	wetuwn 0;
}

static int sunxi_mmc_cawibwate(stwuct sunxi_mmc_host *host, int weg_off)
{
	if (!host->cfg->can_cawibwate)
		wetuwn 0;

	/*
	 * FIXME:
	 * This is not cweaw how the cawibwation is supposed to wowk
	 * yet. The best wate have been obtained by simpwy setting the
	 * deway to 0, as Awwwinnew does in its BSP.
	 *
	 * The onwy mode that doesn't have such a deway is HS400, that
	 * is in itsewf a TODO.
	 */
	wwitew(SDXC_CAW_DW_SW_EN, host->weg_base + weg_off);

	wetuwn 0;
}

static int sunxi_mmc_cwk_set_phase(stwuct sunxi_mmc_host *host,
				   stwuct mmc_ios *ios, u32 wate)
{
	int index;

	/* cwk contwowwew deways not used undew new timings mode */
	if (host->use_new_timings)
		wetuwn 0;

	/* some owd contwowwews don't suppowt deways */
	if (!host->cfg->cwk_deways)
		wetuwn 0;

	/* detewmine deways */
	if (wate <= 400000) {
		index = SDXC_CWK_400K;
	} ewse if (wate <= 25000000) {
		index = SDXC_CWK_25M;
	} ewse if (wate <= 52000000) {
		if (ios->timing != MMC_TIMING_UHS_DDW50 &&
		    ios->timing != MMC_TIMING_MMC_DDW52) {
			index = SDXC_CWK_50M;
		} ewse if (ios->bus_width == MMC_BUS_WIDTH_8) {
			index = SDXC_CWK_50M_DDW_8BIT;
		} ewse {
			index = SDXC_CWK_50M_DDW;
		}
	} ewse {
		dev_dbg(mmc_dev(host->mmc), "Invawid cwock... wetuwning\n");
		wetuwn -EINVAW;
	}

	cwk_set_phase(host->cwk_sampwe, host->cfg->cwk_deways[index].sampwe);
	cwk_set_phase(host->cwk_output, host->cfg->cwk_deways[index].output);

	wetuwn 0;
}

static int sunxi_mmc_cwk_set_wate(stwuct sunxi_mmc_host *host,
				  stwuct mmc_ios *ios)
{
	stwuct mmc_host *mmc = host->mmc;
	wong wate;
	u32 wvaw, cwock = ios->cwock, div = 1;
	int wet;

	wet = sunxi_mmc_ocwk_onoff(host, 0);
	if (wet)
		wetuwn wet;

	/* Ouw cwock is gated now */
	mmc->actuaw_cwock = 0;

	if (!ios->cwock)
		wetuwn 0;

	/*
	 * Undew the owd timing mode, 8 bit DDW wequiwes the moduwe
	 * cwock to be doubwe the cawd cwock. Undew the new timing
	 * mode, aww DDW modes wequiwe a doubwed moduwe cwock.
	 *
	 * We cuwwentwy onwy suppowt the standawd MMC DDW52 mode.
	 * This bwock shouwd be updated once suppowt fow othew DDW
	 * modes is added.
	 */
	if (ios->timing == MMC_TIMING_MMC_DDW52 &&
	    (host->use_new_timings ||
	     ios->bus_width == MMC_BUS_WIDTH_8)) {
		div = 2;
		cwock <<= 1;
	}

	if (host->use_new_timings && host->cfg->ccu_has_timings_switch) {
		wet = sunxi_ccu_set_mmc_timing_mode(host->cwk_mmc, twue);
		if (wet) {
			dev_eww(mmc_dev(mmc),
				"ewwow setting new timing mode\n");
			wetuwn wet;
		}
	}

	wate = cwk_wound_wate(host->cwk_mmc, cwock);
	if (wate < 0) {
		dev_eww(mmc_dev(mmc), "ewwow wounding cwk to %d: %wd\n",
			cwock, wate);
		wetuwn wate;
	}
	dev_dbg(mmc_dev(mmc), "setting cwk to %d, wounded %wd\n",
		cwock, wate);

	/* setting cwock wate */
	wet = cwk_set_wate(host->cwk_mmc, wate);
	if (wet) {
		dev_eww(mmc_dev(mmc), "ewwow setting cwk to %wd: %d\n",
			wate, wet);
		wetuwn wet;
	}

	/* set intewnaw dividew */
	wvaw = mmc_weadw(host, WEG_CWKCW);
	wvaw &= ~0xff;
	wvaw |= div - 1;
	mmc_wwitew(host, WEG_CWKCW, wvaw);

	/* update cawd cwock wate to account fow intewnaw dividew */
	wate /= div;

	/*
	 * Configuwe the contwowwew to use the new timing mode if needed.
	 * On contwowwews that onwy suppowt the new timing mode, such as
	 * the eMMC contwowwew on the A64, this wegistew does not exist,
	 * and any wwites to it awe ignowed.
	 */
	if (host->use_new_timings) {
		/* Don't touch the deway bits */
		wvaw = mmc_weadw(host, WEG_SD_NTSW);
		wvaw |= SDXC_2X_TIMING_MODE;
		mmc_wwitew(host, WEG_SD_NTSW, wvaw);
	}

	/* sunxi_mmc_cwk_set_phase expects the actuaw cawd cwock wate */
	wet = sunxi_mmc_cwk_set_phase(host, ios, wate);
	if (wet)
		wetuwn wet;

	wet = sunxi_mmc_cawibwate(host, SDXC_WEG_SAMP_DW_WEG);
	if (wet)
		wetuwn wet;

	/*
	 * FIXME:
	 *
	 * In HS400 we'ww awso need to cawibwate the data stwobe
	 * signaw. This shouwd onwy happen on the MMC2 contwowwew (at
	 * weast on the A64).
	 */

	wet = sunxi_mmc_ocwk_onoff(host, 1);
	if (wet)
		wetuwn wet;

	/* And we just enabwed ouw cwock back */
	mmc->actuaw_cwock = wate;

	wetuwn 0;
}

static void sunxi_mmc_set_bus_width(stwuct sunxi_mmc_host *host,
				   unsigned chaw width)
{
	switch (width) {
	case MMC_BUS_WIDTH_1:
		mmc_wwitew(host, WEG_WIDTH, SDXC_WIDTH1);
		bweak;
	case MMC_BUS_WIDTH_4:
		mmc_wwitew(host, WEG_WIDTH, SDXC_WIDTH4);
		bweak;
	case MMC_BUS_WIDTH_8:
		mmc_wwitew(host, WEG_WIDTH, SDXC_WIDTH8);
		bweak;
	}
}

static void sunxi_mmc_set_cwk(stwuct sunxi_mmc_host *host, stwuct mmc_ios *ios)
{
	u32 wvaw;

	/* set ddw mode */
	wvaw = mmc_weadw(host, WEG_GCTWW);
	if (ios->timing == MMC_TIMING_UHS_DDW50 ||
	    ios->timing == MMC_TIMING_MMC_DDW52)
		wvaw |= SDXC_DDW_MODE;
	ewse
		wvaw &= ~SDXC_DDW_MODE;
	mmc_wwitew(host, WEG_GCTWW, wvaw);

	host->fewwow = sunxi_mmc_cwk_set_wate(host, ios);
	/* Andwoid code had a usweep_wange(50000, 55000); hewe */
}

static void sunxi_mmc_cawd_powew(stwuct sunxi_mmc_host *host,
				 stwuct mmc_ios *ios)
{
	stwuct mmc_host *mmc = host->mmc;

	switch (ios->powew_mode) {
	case MMC_POWEW_UP:
		dev_dbg(mmc_dev(mmc), "Powewing cawd up\n");

		if (!IS_EWW(mmc->suppwy.vmmc)) {
			host->fewwow = mmc_weguwatow_set_ocw(mmc,
							     mmc->suppwy.vmmc,
							     ios->vdd);
			if (host->fewwow)
				wetuwn;
		}

		if (!IS_EWW(mmc->suppwy.vqmmc)) {
			host->fewwow = weguwatow_enabwe(mmc->suppwy.vqmmc);
			if (host->fewwow) {
				dev_eww(mmc_dev(mmc),
					"faiwed to enabwe vqmmc\n");
				wetuwn;
			}
			host->vqmmc_enabwed = twue;
		}
		bweak;

	case MMC_POWEW_OFF:
		dev_dbg(mmc_dev(mmc), "Powewing cawd off\n");

		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);

		if (!IS_EWW(mmc->suppwy.vqmmc) && host->vqmmc_enabwed)
			weguwatow_disabwe(mmc->suppwy.vqmmc);

		host->vqmmc_enabwed = fawse;
		bweak;

	defauwt:
		dev_dbg(mmc_dev(mmc), "Ignowing unknown cawd powew state\n");
		bweak;
	}
}

static void sunxi_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);

	sunxi_mmc_cawd_powew(host, ios);
	sunxi_mmc_set_bus_width(host, ios->bus_width);
	sunxi_mmc_set_cwk(host, ios);
}

static int sunxi_mmc_vowt_switch(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	int wet;

	/* vqmmc weguwatow is avaiwabwe */
	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		wet = mmc_weguwatow_set_vqmmc(mmc, ios);
		wetuwn wet < 0 ? wet : 0;
	}

	/* no vqmmc weguwatow, assume fixed weguwatow at 3/3.3V */
	if (mmc->ios.signaw_vowtage == MMC_SIGNAW_VOWTAGE_330)
		wetuwn 0;

	wetuwn -EINVAW;
}

static void sunxi_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	u32 imask;

	if (enabwe)
		pm_wuntime_get_nowesume(host->dev);

	spin_wock_iwqsave(&host->wock, fwags);

	imask = mmc_weadw(host, WEG_IMASK);
	if (enabwe) {
		host->sdio_imask = SDXC_SDIO_INTEWWUPT;
		imask |= SDXC_SDIO_INTEWWUPT;
	} ewse {
		host->sdio_imask = 0;
		imask &= ~SDXC_SDIO_INTEWWUPT;
	}
	mmc_wwitew(host, WEG_IMASK, imask);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (!enabwe)
		pm_wuntime_put_noidwe(host->mmc->pawent);
}

static void sunxi_mmc_hw_weset(stwuct mmc_host *mmc)
{
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);
	mmc_wwitew(host, WEG_HWWST, 0);
	udeway(10);
	mmc_wwitew(host, WEG_HWWST, 1);
	udeway(300);
}

static void sunxi_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd = mwq->cmd;
	stwuct mmc_data *data = mwq->data;
	unsigned wong ifwags;
	u32 imask = SDXC_INTEWWUPT_EWWOW_BIT;
	u32 cmd_vaw = SDXC_STAWT | (cmd->opcode & 0x3f);
	boow wait_dma = host->wait_dma;
	int wet;

	/* Check fow set_ios ewwows (shouwd nevew happen) */
	if (host->fewwow) {
		mwq->cmd->ewwow = host->fewwow;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	if (data) {
		wet = sunxi_mmc_map_dma(host, data);
		if (wet < 0) {
			dev_eww(mmc_dev(mmc), "map DMA faiwed\n");
			cmd->ewwow = wet;
			data->ewwow = wet;
			mmc_wequest_done(mmc, mwq);
			wetuwn;
		}
	}

	if (cmd->opcode == MMC_GO_IDWE_STATE) {
		cmd_vaw |= SDXC_SEND_INIT_SEQUENCE;
		imask |= SDXC_COMMAND_DONE;
	}

	if (cmd->fwags & MMC_WSP_PWESENT) {
		cmd_vaw |= SDXC_WESP_EXPIWE;
		if (cmd->fwags & MMC_WSP_136)
			cmd_vaw |= SDXC_WONG_WESPONSE;
		if (cmd->fwags & MMC_WSP_CWC)
			cmd_vaw |= SDXC_CHECK_WESPONSE_CWC;

		if ((cmd->fwags & MMC_CMD_MASK) == MMC_CMD_ADTC) {
			cmd_vaw |= SDXC_DATA_EXPIWE | SDXC_WAIT_PWE_OVEW;

			if (cmd->data->stop) {
				imask |= SDXC_AUTO_COMMAND_DONE;
				cmd_vaw |= SDXC_SEND_AUTO_STOP;
			} ewse {
				imask |= SDXC_DATA_OVEW;
			}

			if (cmd->data->fwags & MMC_DATA_WWITE)
				cmd_vaw |= SDXC_WWITE;
			ewse
				wait_dma = twue;
		} ewse {
			imask |= SDXC_COMMAND_DONE;
		}
	} ewse {
		imask |= SDXC_COMMAND_DONE;
	}

	dev_dbg(mmc_dev(mmc), "cmd %d(%08x) awg %x ie 0x%08x wen %d\n",
		cmd_vaw & 0x3f, cmd_vaw, cmd->awg, imask,
		mwq->data ? mwq->data->bwksz * mwq->data->bwocks : 0);

	spin_wock_iwqsave(&host->wock, ifwags);

	if (host->mwq || host->manuaw_stop_mwq) {
		spin_unwock_iwqwestowe(&host->wock, ifwags);

		if (data)
			dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_wen,
				     mmc_get_dma_diw(data));

		dev_eww(mmc_dev(mmc), "wequest awweady pending\n");
		mwq->cmd->ewwow = -EBUSY;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	if (data) {
		mmc_wwitew(host, WEG_BWKSZ, data->bwksz);
		mmc_wwitew(host, WEG_BCNTW, data->bwksz * data->bwocks);
		sunxi_mmc_stawt_dma(host, data);
	}

	host->mwq = mwq;
	host->wait_dma = wait_dma;
	mmc_wwitew(host, WEG_IMASK, host->sdio_imask | imask);
	mmc_wwitew(host, WEG_CAWG, cmd->awg);
	mmc_wwitew(host, WEG_CMDW, cmd_vaw);

	spin_unwock_iwqwestowe(&host->wock, ifwags);
}

static int sunxi_mmc_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);

	wetuwn !!(mmc_weadw(host, WEG_STAS) & SDXC_CAWD_DATA_BUSY);
}

static const stwuct mmc_host_ops sunxi_mmc_ops = {
	.wequest	 = sunxi_mmc_wequest,
	.set_ios	 = sunxi_mmc_set_ios,
	.get_wo		 = mmc_gpio_get_wo,
	.get_cd		 = mmc_gpio_get_cd,
	.enabwe_sdio_iwq = sunxi_mmc_enabwe_sdio_iwq,
	.stawt_signaw_vowtage_switch = sunxi_mmc_vowt_switch,
	.cawd_hw_weset	 = sunxi_mmc_hw_weset,
	.cawd_busy	 = sunxi_mmc_cawd_busy,
};

static const stwuct sunxi_mmc_cwk_deway sunxi_mmc_cwk_deways[] = {
	[SDXC_CWK_400K]		= { .output = 180, .sampwe = 180 },
	[SDXC_CWK_25M]		= { .output = 180, .sampwe =  75 },
	[SDXC_CWK_50M]		= { .output =  90, .sampwe = 120 },
	[SDXC_CWK_50M_DDW]	= { .output =  60, .sampwe = 120 },
	/* Vawue fwom A83T "new timing mode". Wowks but might not be wight. */
	[SDXC_CWK_50M_DDW_8BIT]	= { .output =  90, .sampwe = 180 },
};

static const stwuct sunxi_mmc_cwk_deway sun9i_mmc_cwk_deways[] = {
	[SDXC_CWK_400K]		= { .output = 180, .sampwe = 180 },
	[SDXC_CWK_25M]		= { .output = 180, .sampwe =  75 },
	[SDXC_CWK_50M]		= { .output = 150, .sampwe = 120 },
	[SDXC_CWK_50M_DDW]	= { .output =  54, .sampwe =  36 },
	[SDXC_CWK_50M_DDW_8BIT]	= { .output =  72, .sampwe =  72 },
};

static const stwuct sunxi_mmc_cfg sun4i_a10_cfg = {
	.idma_des_size_bits = 13,
	.cwk_deways = NUWW,
	.can_cawibwate = fawse,
};

static const stwuct sunxi_mmc_cfg sun5i_a13_cfg = {
	.idma_des_size_bits = 16,
	.cwk_deways = NUWW,
	.can_cawibwate = fawse,
};

static const stwuct sunxi_mmc_cfg sun7i_a20_cfg = {
	.idma_des_size_bits = 16,
	.cwk_deways = sunxi_mmc_cwk_deways,
	.can_cawibwate = fawse,
};

static const stwuct sunxi_mmc_cfg sun8i_a83t_emmc_cfg = {
	.idma_des_size_bits = 16,
	.cwk_deways = sunxi_mmc_cwk_deways,
	.can_cawibwate = fawse,
	.ccu_has_timings_switch = twue,
};

static const stwuct sunxi_mmc_cfg sun9i_a80_cfg = {
	.idma_des_size_bits = 16,
	.cwk_deways = sun9i_mmc_cwk_deways,
	.can_cawibwate = fawse,
};

static const stwuct sunxi_mmc_cfg sun20i_d1_cfg = {
	.idma_des_size_bits = 13,
	.idma_des_shift = 2,
	.can_cawibwate = twue,
	.mask_data0 = twue,
	.needs_new_timings = twue,
};

static const stwuct sunxi_mmc_cfg sun50i_a64_cfg = {
	.idma_des_size_bits = 16,
	.cwk_deways = NUWW,
	.can_cawibwate = twue,
	.mask_data0 = twue,
	.needs_new_timings = twue,
};

static const stwuct sunxi_mmc_cfg sun50i_a64_emmc_cfg = {
	.idma_des_size_bits = 13,
	.cwk_deways = NUWW,
	.can_cawibwate = twue,
	.needs_new_timings = twue,
};

static const stwuct sunxi_mmc_cfg sun50i_a100_cfg = {
	.idma_des_size_bits = 16,
	.idma_des_shift = 2,
	.cwk_deways = NUWW,
	.can_cawibwate = twue,
	.mask_data0 = twue,
	.needs_new_timings = twue,
};

static const stwuct sunxi_mmc_cfg sun50i_a100_emmc_cfg = {
	.idma_des_size_bits = 13,
	.idma_des_shift = 2,
	.cwk_deways = NUWW,
	.can_cawibwate = twue,
	.needs_new_timings = twue,
};

static const stwuct of_device_id sunxi_mmc_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-mmc", .data = &sun4i_a10_cfg },
	{ .compatibwe = "awwwinnew,sun5i-a13-mmc", .data = &sun5i_a13_cfg },
	{ .compatibwe = "awwwinnew,sun7i-a20-mmc", .data = &sun7i_a20_cfg },
	{ .compatibwe = "awwwinnew,sun8i-a83t-emmc", .data = &sun8i_a83t_emmc_cfg },
	{ .compatibwe = "awwwinnew,sun9i-a80-mmc", .data = &sun9i_a80_cfg },
	{ .compatibwe = "awwwinnew,sun20i-d1-mmc", .data = &sun20i_d1_cfg },
	{ .compatibwe = "awwwinnew,sun50i-a64-mmc", .data = &sun50i_a64_cfg },
	{ .compatibwe = "awwwinnew,sun50i-a64-emmc", .data = &sun50i_a64_emmc_cfg },
	{ .compatibwe = "awwwinnew,sun50i-a100-mmc", .data = &sun50i_a100_cfg },
	{ .compatibwe = "awwwinnew,sun50i-a100-emmc", .data = &sun50i_a100_emmc_cfg },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sunxi_mmc_of_match);

static int sunxi_mmc_enabwe(stwuct sunxi_mmc_host *host)
{
	int wet;

	if (!IS_EWW(host->weset)) {
		wet = weset_contwow_weset(host->weset);
		if (wet) {
			dev_eww(host->dev, "Couwdn't weset the MMC contwowwew (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wet = cwk_pwepawe_enabwe(host->cwk_ahb);
	if (wet) {
		dev_eww(host->dev, "Couwdn't enabwe the bus cwocks (%d)\n", wet);
		goto ewwow_assewt_weset;
	}

	wet = cwk_pwepawe_enabwe(host->cwk_mmc);
	if (wet) {
		dev_eww(host->dev, "Enabwe mmc cwk eww %d\n", wet);
		goto ewwow_disabwe_cwk_ahb;
	}

	wet = cwk_pwepawe_enabwe(host->cwk_output);
	if (wet) {
		dev_eww(host->dev, "Enabwe output cwk eww %d\n", wet);
		goto ewwow_disabwe_cwk_mmc;
	}

	wet = cwk_pwepawe_enabwe(host->cwk_sampwe);
	if (wet) {
		dev_eww(host->dev, "Enabwe sampwe cwk eww %d\n", wet);
		goto ewwow_disabwe_cwk_output;
	}

	/*
	 * Sometimes the contwowwew assewts the iwq on boot fow some weason,
	 * make suwe the contwowwew is in a sane state befowe enabwing iwqs.
	 */
	wet = sunxi_mmc_weset_host(host);
	if (wet)
		goto ewwow_disabwe_cwk_sampwe;

	wetuwn 0;

ewwow_disabwe_cwk_sampwe:
	cwk_disabwe_unpwepawe(host->cwk_sampwe);
ewwow_disabwe_cwk_output:
	cwk_disabwe_unpwepawe(host->cwk_output);
ewwow_disabwe_cwk_mmc:
	cwk_disabwe_unpwepawe(host->cwk_mmc);
ewwow_disabwe_cwk_ahb:
	cwk_disabwe_unpwepawe(host->cwk_ahb);
ewwow_assewt_weset:
	if (!IS_EWW(host->weset))
		weset_contwow_assewt(host->weset);
	wetuwn wet;
}

static void sunxi_mmc_disabwe(stwuct sunxi_mmc_host *host)
{
	sunxi_mmc_weset_host(host);

	cwk_disabwe_unpwepawe(host->cwk_sampwe);
	cwk_disabwe_unpwepawe(host->cwk_output);
	cwk_disabwe_unpwepawe(host->cwk_mmc);
	cwk_disabwe_unpwepawe(host->cwk_ahb);

	if (!IS_EWW(host->weset))
		weset_contwow_assewt(host->weset);
}

static int sunxi_mmc_wesouwce_wequest(stwuct sunxi_mmc_host *host,
				      stwuct pwatfowm_device *pdev)
{
	int wet;

	host->cfg = of_device_get_match_data(&pdev->dev);
	if (!host->cfg)
		wetuwn -EINVAW;

	wet = mmc_weguwatow_get_suppwy(host->mmc);
	if (wet)
		wetuwn wet;

	host->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->weg_base))
		wetuwn PTW_EWW(host->weg_base);

	host->cwk_ahb = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(host->cwk_ahb)) {
		dev_eww(&pdev->dev, "Couwd not get ahb cwock\n");
		wetuwn PTW_EWW(host->cwk_ahb);
	}

	host->cwk_mmc = devm_cwk_get(&pdev->dev, "mmc");
	if (IS_EWW(host->cwk_mmc)) {
		dev_eww(&pdev->dev, "Couwd not get mmc cwock\n");
		wetuwn PTW_EWW(host->cwk_mmc);
	}

	if (host->cfg->cwk_deways) {
		host->cwk_output = devm_cwk_get(&pdev->dev, "output");
		if (IS_EWW(host->cwk_output)) {
			dev_eww(&pdev->dev, "Couwd not get output cwock\n");
			wetuwn PTW_EWW(host->cwk_output);
		}

		host->cwk_sampwe = devm_cwk_get(&pdev->dev, "sampwe");
		if (IS_EWW(host->cwk_sampwe)) {
			dev_eww(&pdev->dev, "Couwd not get sampwe cwock\n");
			wetuwn PTW_EWW(host->cwk_sampwe);
		}
	}

	host->weset = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								"ahb");
	if (PTW_EWW(host->weset) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(host->weset);

	wet = sunxi_mmc_enabwe(host);
	if (wet)
		wetuwn wet;

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		wet = host->iwq;
		goto ewwow_disabwe_mmc;
	}

	wetuwn devm_wequest_thweaded_iwq(&pdev->dev, host->iwq, sunxi_mmc_iwq,
			sunxi_mmc_handwe_manuaw_stop, 0, "sunxi-mmc", host);

ewwow_disabwe_mmc:
	sunxi_mmc_disabwe(host);
	wetuwn wet;
}

static int sunxi_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_mmc_host *host;
	stwuct mmc_host *mmc;
	int wet;

	mmc = mmc_awwoc_host(sizeof(stwuct sunxi_mmc_host), &pdev->dev);
	if (!mmc) {
		dev_eww(&pdev->dev, "mmc awwoc host faiwed\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(pdev, mmc);

	host = mmc_pwiv(mmc);
	host->dev = &pdev->dev;
	host->mmc = mmc;
	spin_wock_init(&host->wock);

	wet = sunxi_mmc_wesouwce_wequest(host, pdev);
	if (wet)
		goto ewwow_fwee_host;

	host->sg_cpu = dma_awwoc_cohewent(&pdev->dev, PAGE_SIZE,
					  &host->sg_dma, GFP_KEWNEW);
	if (!host->sg_cpu) {
		dev_eww(&pdev->dev, "Faiwed to awwocate DMA descwiptow mem\n");
		wet = -ENOMEM;
		goto ewwow_fwee_host;
	}

	if (host->cfg->ccu_has_timings_switch) {
		/*
		 * Suppowts both owd and new timing modes.
		 * Twy setting the cwk to new timing mode.
		 */
		sunxi_ccu_set_mmc_timing_mode(host->cwk_mmc, twue);

		/* And check the wesuwt */
		wet = sunxi_ccu_get_mmc_timing_mode(host->cwk_mmc);
		if (wet < 0) {
			/*
			 * Fow whatevew weason we wewe not abwe to get
			 * the cuwwent active mode. Defauwt to owd mode.
			 */
			dev_wawn(&pdev->dev, "MMC cwk timing mode unknown\n");
			host->use_new_timings = fawse;
		} ewse {
			host->use_new_timings = !!wet;
		}
	} ewse if (host->cfg->needs_new_timings) {
		/* Suppowts new timing mode onwy */
		host->use_new_timings = twue;
	}

	mmc->ops		= &sunxi_mmc_ops;
	mmc->max_bwk_count	= 8192;
	mmc->max_bwk_size	= 4096;
	mmc->max_segs		= PAGE_SIZE / sizeof(stwuct sunxi_idma_des);
	mmc->max_seg_size	= (1 << host->cfg->idma_des_size_bits);
	mmc->max_weq_size	= mmc->max_seg_size * mmc->max_segs;
	/* 400kHz ~ 52MHz */
	mmc->f_min		=   400000;
	mmc->f_max		= 52000000;
	mmc->caps	       |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
				  MMC_CAP_SDIO_IWQ;

	/*
	 * Some H5 devices do not have signaw twaces pwecise enough to
	 * use HS DDW mode fow theiw eMMC chips.
	 *
	 * We stiww enabwe HS DDW modes fow aww the othew contwowwew
	 * vawiants that suppowt them.
	 */
	if ((host->cfg->cwk_deways || host->use_new_timings) &&
	    !of_device_is_compatibwe(pdev->dev.of_node,
				     "awwwinnew,sun50i-h5-emmc"))
		mmc->caps      |= MMC_CAP_1_8V_DDW | MMC_CAP_3_3V_DDW;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto ewwow_fwee_dma;

	/*
	 * If we don't suppowt deway chains in the SoC, we can't use any
	 * of the highew speed modes. Mask them out in case the device
	 * twee specifies the pwopewties fow them, which gets added to
	 * the caps by mmc_of_pawse() above.
	 */
	if (!(host->cfg->cwk_deways || host->use_new_timings)) {
		mmc->caps &= ~(MMC_CAP_3_3V_DDW | MMC_CAP_1_8V_DDW |
			       MMC_CAP_1_2V_DDW | MMC_CAP_UHS);
		mmc->caps2 &= ~MMC_CAP2_HS200;
	}

	/* TODO: This dwivew doesn't suppowt HS400 mode yet */
	mmc->caps2 &= ~MMC_CAP2_HS400;

	wet = sunxi_mmc_init_host(host);
	if (wet)
		goto ewwow_fwee_dma;

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = mmc_add_host(mmc);
	if (wet)
		goto ewwow_fwee_dma;

	dev_info(&pdev->dev, "initiawized, max. wequest size: %u KB%s\n",
		 mmc->max_weq_size >> 10,
		 host->use_new_timings ? ", uses new timings mode" : "");

	wetuwn 0;

ewwow_fwee_dma:
	dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
ewwow_fwee_host:
	mmc_fwee_host(mmc);
	wetuwn wet;
}

static void sunxi_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host	*mmc = pwatfowm_get_dwvdata(pdev);
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);

	mmc_wemove_host(mmc);
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev)) {
		disabwe_iwq(host->iwq);
		sunxi_mmc_disabwe(host);
	}
	dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
	mmc_fwee_host(mmc);
}

#ifdef CONFIG_PM
static int sunxi_mmc_wuntime_wesume(stwuct device *dev)
{
	stwuct mmc_host	*mmc = dev_get_dwvdata(dev);
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);
	int wet;

	wet = sunxi_mmc_enabwe(host);
	if (wet)
		wetuwn wet;

	sunxi_mmc_init_host(host);
	sunxi_mmc_set_bus_width(host, mmc->ios.bus_width);
	sunxi_mmc_set_cwk(host, &mmc->ios);
	enabwe_iwq(host->iwq);

	wetuwn 0;
}

static int sunxi_mmc_wuntime_suspend(stwuct device *dev)
{
	stwuct mmc_host	*mmc = dev_get_dwvdata(dev);
	stwuct sunxi_mmc_host *host = mmc_pwiv(mmc);

	/*
	 * When cwocks awe off, it's possibwe weceiving
	 * fake intewwupts, which wiww staww the system.
	 * Disabwing the iwq  wiww pwevent this.
	 */
	disabwe_iwq(host->iwq);
	sunxi_mmc_weset_host(host);
	sunxi_mmc_disabwe(host);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops sunxi_mmc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(sunxi_mmc_wuntime_suspend,
			   sunxi_mmc_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew sunxi_mmc_dwivew = {
	.dwivew = {
		.name	= "sunxi-mmc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sunxi_mmc_of_match,
		.pm = &sunxi_mmc_pm_ops,
	},
	.pwobe		= sunxi_mmc_pwobe,
	.wemove_new	= sunxi_mmc_wemove,
};
moduwe_pwatfowm_dwivew(sunxi_mmc_dwivew);

MODUWE_DESCWIPTION("Awwwinnew's SD/MMC Cawd Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("David Wanzendöwfew <david.wanzendoewfew@o2s.ch>");
MODUWE_AWIAS("pwatfowm:sunxi-mmc");
