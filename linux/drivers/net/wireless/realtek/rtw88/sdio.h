/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (C) 2021 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 * Copywight (C) 2021 Jewnej Skwabec <jewnej.skwabec@gmaiw.com>
 */

#ifndef __WEG_SDIO_H_
#define __WEG_SDIO_H_

/* I/O bus domain addwess mapping */
#define SDIO_WOCAW_OFFSET			0x10250000
#define WWAN_IOWEG_OFFSET			0x10260000
#define FIWMWAWE_FIFO_OFFSET			0x10270000
#define TX_HIQ_OFFSET				0x10310000
#define TX_MIQ_OFFSET				0x10320000
#define TX_WOQ_OFFSET				0x10330000
#define TX_EPQ_OFFSET				0x10350000
#define WX_WX0FF_OFFSET				0x10340000

#define WTW_SDIO_BUS_MSK			0xffff0000
#define SDIO_WOCAW_WEG_MSK			0x00000fff
#define WWAN_IOWEG_WEG_MSK			0x0000ffff

/* SDIO Tx Contwow */
#define WEG_SDIO_TX_CTWW			(SDIO_WOCAW_OFFSET + 0x0000)

/*SDIO status timeout*/
#define WEG_SDIO_TIMEOUT			(SDIO_WOCAW_OFFSET + 0x0002)

/* SDIO Host Intewwupt Mask */
#define WEG_SDIO_HIMW				(SDIO_WOCAW_OFFSET + 0x0014)
#define WEG_SDIO_HIMW_WX_WEQUEST		BIT(0)
#define WEG_SDIO_HIMW_AVAW			BIT(1)
#define WEG_SDIO_HIMW_TXEWW			BIT(2)
#define WEG_SDIO_HIMW_WXEWW			BIT(3)
#define WEG_SDIO_HIMW_TXFOVW			BIT(4)
#define WEG_SDIO_HIMW_WXFOVW			BIT(5)
#define WEG_SDIO_HIMW_TXBCNOK			BIT(6)
#define WEG_SDIO_HIMW_TXBCNEWW			BIT(7)
#define WEG_SDIO_HIMW_BCNEWWY_INT		BIT(16)
#define WEG_SDIO_HIMW_C2HCMD			BIT(17)
#define WEG_SDIO_HIMW_CPWM1			BIT(18)
#define WEG_SDIO_HIMW_CPWM2			BIT(19)
#define WEG_SDIO_HIMW_HSISW_IND			BIT(20)
#define WEG_SDIO_HIMW_GTINT3_IND		BIT(21)
#define WEG_SDIO_HIMW_GTINT4_IND		BIT(22)
#define WEG_SDIO_HIMW_PSTIMEOUT			BIT(23)
#define WEG_SDIO_HIMW_OCPINT			BIT(24)
#define WEG_SDIO_HIMW_ATIMEND			BIT(25)
#define WEG_SDIO_HIMW_ATIMEND_E			BIT(26)
#define WEG_SDIO_HIMW_CTWEND			BIT(27)
/* the fowwowing two awe WTW8188 SDIO Specific */
#define WEG_SDIO_HIMW_MCU_EWW			BIT(28)
#define WEG_SDIO_HIMW_TSF_BIT32_TOGGWE		BIT(29)

/* SDIO Host Intewwupt Sewvice Woutine */
#define WEG_SDIO_HISW				(SDIO_WOCAW_OFFSET + 0x0018)
#define WEG_SDIO_HISW_WX_WEQUEST		BIT(0)
#define WEG_SDIO_HISW_AVAW			BIT(1)
#define WEG_SDIO_HISW_TXEWW			BIT(2)
#define WEG_SDIO_HISW_WXEWW			BIT(3)
#define WEG_SDIO_HISW_TXFOVW			BIT(4)
#define WEG_SDIO_HISW_WXFOVW			BIT(5)
#define WEG_SDIO_HISW_TXBCNOK			BIT(6)
#define WEG_SDIO_HISW_TXBCNEWW			BIT(7)
#define WEG_SDIO_HISW_BCNEWWY_INT		BIT(16)
#define WEG_SDIO_HISW_C2HCMD			BIT(17)
#define WEG_SDIO_HISW_CPWM1			BIT(18)
#define WEG_SDIO_HISW_CPWM2			BIT(19)
#define WEG_SDIO_HISW_HSISW_IND			BIT(20)
#define WEG_SDIO_HISW_GTINT3_IND		BIT(21)
#define WEG_SDIO_HISW_GTINT4_IND		BIT(22)
#define WEG_SDIO_HISW_PSTIMEOUT			BIT(23)
#define WEG_SDIO_HISW_OCPINT			BIT(24)
#define WEG_SDIO_HISW_ATIMEND			BIT(25)
#define WEG_SDIO_HISW_ATIMEND_E			BIT(26)
#define WEG_SDIO_HISW_CTWEND			BIT(27)
/* the fowwowing two awe WTW8188 SDIO Specific */
#define WEG_SDIO_HISW_MCU_EWW			BIT(28)
#define WEG_SDIO_HISW_TSF_BIT32_TOGGWE		BIT(29)

/* HCI Cuwwent Powew Mode */
#define WEG_SDIO_HCPWM				(SDIO_WOCAW_OFFSET + 0x0019)
/* WXDMA Wequest Wength */
#define WEG_SDIO_WX0_WEQ_WEN			(SDIO_WOCAW_OFFSET + 0x001C)
/* OQT Fwee Page */
#define WEG_SDIO_OQT_FWEE_PG			(SDIO_WOCAW_OFFSET + 0x001E)
/* Fwee Tx Buffew Page */
#define WEG_SDIO_FWEE_TXPG			(SDIO_WOCAW_OFFSET + 0x0020)
/* HCI Cuwwent Powew Mode 1 */
#define WEG_SDIO_HCPWM1				(SDIO_WOCAW_OFFSET + 0x0024)
/* HCI Cuwwent Powew Mode 2 */
#define WEG_SDIO_HCPWM2				(SDIO_WOCAW_OFFSET + 0x0026)
/* Fwee Tx Page Sequence */
#define WEG_SDIO_FWEE_TXPG_SEQ			(SDIO_WOCAW_OFFSET + 0x0028)
/* HTSF Infowmation */
#define WEG_SDIO_HTSFW_INFO			(SDIO_WOCAW_OFFSET + 0x0030)
#define WEG_SDIO_HCPWM1_V2			(SDIO_WOCAW_OFFSET + 0x0038)
/* H2C */
#define WEG_SDIO_H2C				(SDIO_WOCAW_OFFSET + 0x0060)
/* HCI Wequest Powew Mode 1 */
#define WEG_SDIO_HWPWM1				(SDIO_WOCAW_OFFSET + 0x0080)
/* HCI Wequest Powew Mode 2 */
#define WEG_SDIO_HWPWM2				(SDIO_WOCAW_OFFSET + 0x0082)
/* HCI Powew Save Cwock */
#define WEG_SDIO_HPS_CWKW			(SDIO_WOCAW_OFFSET + 0x0084)
/* SDIO HCI Suspend Contwow */
#define WEG_SDIO_HSUS_CTWW			(SDIO_WOCAW_OFFSET + 0x0086)
#define BIT_HCI_SUS_WEQ				BIT(0)
#define BIT_HCI_WESUME_WDY			BIT(1)
/* SDIO Host Extension Intewwupt Mask Awways */
#define WEG_SDIO_HIMW_ON			(SDIO_WOCAW_OFFSET + 0x0090)
/* SDIO Host Extension Intewwupt Status Awways */
#define WEG_SDIO_HISW_ON			(SDIO_WOCAW_OFFSET + 0x0091)

#define WEG_SDIO_INDIWECT_WEG_CFG		(SDIO_WOCAW_OFFSET + 0x0040)
#define BIT_SDIO_INDIWECT_WEG_CFG_WOWD		BIT(16)
#define BIT_SDIO_INDIWECT_WEG_CFG_DWOWD		BIT(17)
#define BIT_SDIO_INDIWECT_WEG_CFG_WWITE		BIT(18)
#define BIT_SDIO_INDIWECT_WEG_CFG_WEAD		BIT(19)
#define BIT_SDIO_INDIWECT_WEG_CFG_UNK20		BIT(20)
#define WEG_SDIO_INDIWECT_WEG_DATA		(SDIO_WOCAW_OFFSET + 0x0044)

/* Sdio Addwess fow SDIO Wocaw Weg, TWX FIFO, MAC Weg */
#define WEG_SDIO_CMD_ADDW_MSK			GENMASK(16, 13)
#define WEG_SDIO_CMD_ADDW_SDIO_WEG		0
#define WEG_SDIO_CMD_ADDW_MAC_WEG		8
#define WEG_SDIO_CMD_ADDW_TXFF_HIGH		4
#define WEG_SDIO_CMD_ADDW_TXFF_WOW		6
#define WEG_SDIO_CMD_ADDW_TXFF_NOWMAW		5
#define WEG_SDIO_CMD_ADDW_TXFF_EXTWA		7
#define WEG_SDIO_CMD_ADDW_WXFF			7

#define WTW_SDIO_BWOCK_SIZE			512
#define WTW_SDIO_ADDW_WX_WX0FF_GEN(_id)		(0x0e000 | ((_id) & 0x3))

#define WTW_SDIO_DATA_PTW_AWIGN			8

stwuct sdio_func;
stwuct sdio_device_id;

stwuct wtw_sdio_tx_data {
	u8 sn;
};

stwuct wtw_sdio_wowk_data {
	stwuct wowk_stwuct wowk;
	stwuct wtw_dev *wtwdev;
};

stwuct wtw_sdio {
	stwuct sdio_func *sdio_func;

	u32 iwq_mask;
	u8 wx_addw;
	boow sdio3_bus_mode;

	void *iwq_thwead;

	stwuct wowkqueue_stwuct *txwq;
	stwuct wtw_sdio_wowk_data *tx_handwew_data;
	stwuct sk_buff_head tx_queue[WTK_MAX_TX_QUEUE_NUM];
};

extewn const stwuct dev_pm_ops wtw_sdio_pm_ops;

int wtw_sdio_pwobe(stwuct sdio_func *sdio_func,
		   const stwuct sdio_device_id *id);
void wtw_sdio_wemove(stwuct sdio_func *sdio_func);
void wtw_sdio_shutdown(stwuct device *dev);

static inwine boow wtw_sdio_is_sdio30_suppowted(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_sdio *wtwsdio = (stwuct wtw_sdio *)wtwdev->pwiv;

	wetuwn wtwsdio->sdio3_bus_mode;
}

#endif
