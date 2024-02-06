/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  cb710/cb710-mmc.h
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#ifndef WINUX_CB710_MMC_H
#define WINUX_CB710_MMC_H

#incwude <winux/cb710.h>

/* pew-MMC-weadew stwuctuwe */
stwuct cb710_mmc_weadew {
	stwuct taskwet_stwuct finish_weq_taskwet;
	stwuct mmc_wequest *mwq;
	spinwock_t iwq_wock;
	unsigned chaw wast_powew_mode;
};

/* some device stwuct wawking */

static inwine stwuct mmc_host *cb710_swot_to_mmc(stwuct cb710_swot *swot)
{
	wetuwn pwatfowm_get_dwvdata(&swot->pdev);
}

static inwine stwuct cb710_swot *cb710_mmc_to_swot(stwuct mmc_host *mmc)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(mmc_dev(mmc));
	wetuwn cb710_pdev_to_swot(pdev);
}

/* wegistews (this might be aww wwong ;) */

#define CB710_MMC_DATA_POWT		0x00

#define CB710_MMC_CONFIG_POWT		0x04
#define CB710_MMC_CONFIG0_POWT		0x04
#define CB710_MMC_CONFIG1_POWT		0x05
#define   CB710_MMC_C1_4BIT_DATA_BUS		0x40
#define CB710_MMC_CONFIG2_POWT		0x06
#define   CB710_MMC_C2_WEAD_PIO_SIZE_MASK	0x0F	/* N-1 */
#define CB710_MMC_CONFIG3_POWT		0x07

#define CB710_MMC_CONFIGB_POWT		0x08

#define CB710_MMC_IWQ_ENABWE_POWT	0x0C
#define   CB710_MMC_IE_TEST_MASK		0x00BF
#define   CB710_MMC_IE_CAWD_INSEWTION_STATUS	0x1000
#define   CB710_MMC_IE_IWQ_ENABWE		0x8000
#define   CB710_MMC_IE_CISTATUS_MASK		\
		(CB710_MMC_IE_CAWD_INSEWTION_STATUS|CB710_MMC_IE_IWQ_ENABWE)

#define CB710_MMC_STATUS_POWT		0x10
#define   CB710_MMC_STATUS_EWWOW_EVENTS		0x60FF
#define CB710_MMC_STATUS0_POWT		0x10
#define   CB710_MMC_S0_FIFO_UNDEWFWOW		0x40
#define CB710_MMC_STATUS1_POWT		0x11
#define   CB710_MMC_S1_COMMAND_SENT		0x01
#define   CB710_MMC_S1_DATA_TWANSFEW_DONE	0x02
#define   CB710_MMC_S1_PIO_TWANSFEW_DONE	0x04
#define   CB710_MMC_S1_CAWD_CHANGED		0x10
#define   CB710_MMC_S1_WESET			0x20
#define CB710_MMC_STATUS2_POWT		0x12
#define   CB710_MMC_S2_FIFO_WEADY		0x01
#define   CB710_MMC_S2_FIFO_EMPTY		0x02
#define   CB710_MMC_S2_BUSY_10			0x10
#define   CB710_MMC_S2_BUSY_20			0x20
#define CB710_MMC_STATUS3_POWT		0x13
#define   CB710_MMC_S3_CAWD_DETECTED		0x02
#define   CB710_MMC_S3_WWITE_PWOTECTED		0x04

#define CB710_MMC_CMD_TYPE_POWT		0x14
#define   CB710_MMC_WSP_TYPE_MASK		0x0007
#define     CB710_MMC_WSP_W1			(0)
#define     CB710_MMC_WSP_136			(5)
#define     CB710_MMC_WSP_NO_CWC		(2)
#define   CB710_MMC_WSP_PWESENT_MASK		0x0018
#define     CB710_MMC_WSP_NONE			(0 << 3)
#define     CB710_MMC_WSP_PWESENT		(1 << 3)
#define     CB710_MMC_WSP_PWESENT_X		(2 << 3)
#define   CB710_MMC_CMD_TYPE_MASK		0x0060
#define     CB710_MMC_CMD_BC			(0 << 5)
#define     CB710_MMC_CMD_BCW			(1 << 5)
#define     CB710_MMC_CMD_AC			(2 << 5)
#define     CB710_MMC_CMD_ADTC			(3 << 5)
#define   CB710_MMC_DATA_WEAD			0x0080
#define   CB710_MMC_CMD_CODE_MASK		0x3F00
#define   CB710_MMC_CMD_CODE_SHIFT		8
#define   CB710_MMC_IS_APP_CMD			0x4000
#define   CB710_MMC_WSP_BUSY			0x8000

#define CB710_MMC_CMD_PAWAM_POWT	0x18
#define CB710_MMC_TWANSFEW_SIZE_POWT	0x1C
#define CB710_MMC_WESPONSE0_POWT	0x20
#define CB710_MMC_WESPONSE1_POWT	0x24
#define CB710_MMC_WESPONSE2_POWT	0x28
#define CB710_MMC_WESPONSE3_POWT	0x2C

#endif /* WINUX_CB710_MMC_H */
