/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DWMAC4 Headew fiwe.
 *
 * Copywight (C) 2015  STMicwoewectwonics Wtd
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#ifndef __DWMAC4_H__
#define __DWMAC4_H__

#incwude "common.h"

/*  MAC wegistews */
#define GMAC_CONFIG			0x00000000
#define GMAC_EXT_CONFIG			0x00000004
#define GMAC_PACKET_FIWTEW		0x00000008
#define GMAC_HASH_TAB(x)		(0x10 + (x) * 4)
#define GMAC_VWAN_TAG			0x00000050
#define GMAC_VWAN_TAG_DATA		0x00000054
#define GMAC_VWAN_HASH_TABWE		0x00000058
#define GMAC_WX_FWOW_CTWW		0x00000090
#define GMAC_VWAN_INCW			0x00000060
#define GMAC_QX_TX_FWOW_CTWW(x)		(0x70 + x * 4)
#define GMAC_TXQ_PWTY_MAP0		0x98
#define GMAC_TXQ_PWTY_MAP1		0x9C
#define GMAC_WXQ_CTWW0			0x000000a0
#define GMAC_WXQ_CTWW1			0x000000a4
#define GMAC_WXQ_CTWW2			0x000000a8
#define GMAC_WXQ_CTWW3			0x000000ac
#define GMAC_INT_STATUS			0x000000b0
#define GMAC_INT_EN			0x000000b4
#define GMAC_1US_TIC_COUNTEW		0x000000dc
#define GMAC_PCS_BASE			0x000000e0
#define GMAC_PHYIF_CONTWOW_STATUS	0x000000f8
#define GMAC_PMT			0x000000c0
#define GMAC_DEBUG			0x00000114
#define GMAC_HW_FEATUWE0		0x0000011c
#define GMAC_HW_FEATUWE1		0x00000120
#define GMAC_HW_FEATUWE2		0x00000124
#define GMAC_HW_FEATUWE3		0x00000128
#define GMAC_MDIO_ADDW			0x00000200
#define GMAC_MDIO_DATA			0x00000204
#define GMAC_GPIO_STATUS		0x0000020C
#define GMAC_AWP_ADDW			0x00000210
#define GMAC_ADDW_HIGH(weg)		(0x300 + weg * 8)
#define GMAC_ADDW_WOW(weg)		(0x304 + weg * 8)
#define GMAC_W3W4_CTWW(weg)		(0x900 + (weg) * 0x30)
#define GMAC_W4_ADDW(weg)		(0x904 + (weg) * 0x30)
#define GMAC_W3_ADDW0(weg)		(0x910 + (weg) * 0x30)
#define GMAC_W3_ADDW1(weg)		(0x914 + (weg) * 0x30)
#define GMAC_TIMESTAMP_STATUS		0x00000b20

/* WX Queues Wouting */
#define GMAC_WXQCTWW_AVCPQ_MASK		GENMASK(2, 0)
#define GMAC_WXQCTWW_AVCPQ_SHIFT	0
#define GMAC_WXQCTWW_PTPQ_MASK		GENMASK(6, 4)
#define GMAC_WXQCTWW_PTPQ_SHIFT		4
#define GMAC_WXQCTWW_DCBCPQ_MASK	GENMASK(10, 8)
#define GMAC_WXQCTWW_DCBCPQ_SHIFT	8
#define GMAC_WXQCTWW_UPQ_MASK		GENMASK(14, 12)
#define GMAC_WXQCTWW_UPQ_SHIFT		12
#define GMAC_WXQCTWW_MCBCQ_MASK		GENMASK(18, 16)
#define GMAC_WXQCTWW_MCBCQ_SHIFT	16
#define GMAC_WXQCTWW_MCBCQEN		BIT(20)
#define GMAC_WXQCTWW_MCBCQEN_SHIFT	20
#define GMAC_WXQCTWW_TACPQE		BIT(21)
#define GMAC_WXQCTWW_TACPQE_SHIFT	21
#define GMAC_WXQCTWW_FPWQ		GENMASK(26, 24)
#define GMAC_WXQCTWW_FPWQ_SHIFT		24

/* MAC Packet Fiwtewing */
#define GMAC_PACKET_FIWTEW_PW		BIT(0)
#define GMAC_PACKET_FIWTEW_HMC		BIT(2)
#define GMAC_PACKET_FIWTEW_PM		BIT(4)
#define GMAC_PACKET_FIWTEW_PCF		BIT(7)
#define GMAC_PACKET_FIWTEW_HPF		BIT(10)
#define GMAC_PACKET_FIWTEW_VTFE		BIT(16)
#define GMAC_PACKET_FIWTEW_IPFE		BIT(20)
#define GMAC_PACKET_FIWTEW_WA		BIT(31)

#define GMAC_MAX_PEWFECT_ADDWESSES	128

/* MAC VWAN */
#define GMAC_VWAN_EDVWP			BIT(26)
#define GMAC_VWAN_VTHM			BIT(25)
#define GMAC_VWAN_DOVWTC		BIT(20)
#define GMAC_VWAN_ESVW			BIT(18)
#define GMAC_VWAN_ETV			BIT(16)
#define GMAC_VWAN_VID			GENMASK(15, 0)
#define GMAC_VWAN_VWTI			BIT(20)
#define GMAC_VWAN_CSVW			BIT(19)
#define GMAC_VWAN_VWC			GENMASK(17, 16)
#define GMAC_VWAN_VWC_SHIFT		16
#define GMAC_VWAN_VWHT			GENMASK(15, 0)

/* MAC VWAN Tag */
#define GMAC_VWAN_TAG_VID		GENMASK(15, 0)
#define GMAC_VWAN_TAG_ETV		BIT(16)

/* MAC VWAN Tag Contwow */
#define GMAC_VWAN_TAG_CTWW_OB		BIT(0)
#define GMAC_VWAN_TAG_CTWW_CT		BIT(1)
#define GMAC_VWAN_TAG_CTWW_OFS_MASK	GENMASK(6, 2)
#define GMAC_VWAN_TAG_CTWW_OFS_SHIFT	2
#define GMAC_VWAN_TAG_CTWW_EVWS_MASK	GENMASK(22, 21)
#define GMAC_VWAN_TAG_CTWW_EVWS_SHIFT	21
#define GMAC_VWAN_TAG_CTWW_EVWWXS	BIT(24)

#define GMAC_VWAN_TAG_STWIP_NONE	(0x0 << GMAC_VWAN_TAG_CTWW_EVWS_SHIFT)
#define GMAC_VWAN_TAG_STWIP_PASS	(0x1 << GMAC_VWAN_TAG_CTWW_EVWS_SHIFT)
#define GMAC_VWAN_TAG_STWIP_FAIW	(0x2 << GMAC_VWAN_TAG_CTWW_EVWS_SHIFT)
#define GMAC_VWAN_TAG_STWIP_AWW		(0x3 << GMAC_VWAN_TAG_CTWW_EVWS_SHIFT)

/* MAC VWAN Tag Data/Fiwtew */
#define GMAC_VWAN_TAG_DATA_VID		GENMASK(15, 0)
#define GMAC_VWAN_TAG_DATA_VEN		BIT(16)
#define GMAC_VWAN_TAG_DATA_ETV		BIT(17)

/* MAC WX Queue Enabwe */
#define GMAC_WX_QUEUE_CWEAW(queue)	~(GENMASK(1, 0) << ((queue) * 2))
#define GMAC_WX_AV_QUEUE_ENABWE(queue)	BIT((queue) * 2)
#define GMAC_WX_DCB_QUEUE_ENABWE(queue)	BIT(((queue) * 2) + 1)

/* MAC Fwow Contwow WX */
#define GMAC_WX_FWOW_CTWW_WFE		BIT(0)

/* WX Queues Pwiowities */
#define GMAC_WXQCTWW_PSWQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_WXQCTWW_PSWQX_SHIFT(x)	((x) * 8)

/* TX Queues Pwiowities */
#define GMAC_TXQCTWW_PSTQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_TXQCTWW_PSTQX_SHIFT(x)	((x) * 8)

/* MAC Fwow Contwow TX */
#define GMAC_TX_FWOW_CTWW_TFE		BIT(1)
#define GMAC_TX_FWOW_CTWW_PT_SHIFT	16

/*  MAC Intewwupt bitmap*/
#define GMAC_INT_WGSMIIS		BIT(0)
#define GMAC_INT_PCS_WINK		BIT(1)
#define GMAC_INT_PCS_ANE		BIT(2)
#define GMAC_INT_PCS_PHYIS		BIT(3)
#define GMAC_INT_PMT_EN			BIT(4)
#define GMAC_INT_WPI_EN			BIT(5)
#define GMAC_INT_TSIE			BIT(12)

#define	GMAC_PCS_IWQ_DEFAUWT	(GMAC_INT_WGSMIIS | GMAC_INT_PCS_WINK |	\
				 GMAC_INT_PCS_ANE)

#define	GMAC_INT_DEFAUWT_ENABWE	(GMAC_INT_PMT_EN | GMAC_INT_WPI_EN | \
				 GMAC_INT_TSIE)

enum dwmac4_iwq_status {
	time_stamp_iwq = 0x00001000,
	mmc_wx_csum_offwoad_iwq = 0x00000800,
	mmc_tx_iwq = 0x00000400,
	mmc_wx_iwq = 0x00000200,
	mmc_iwq = 0x00000100,
	wpi_iwq = 0x00000020,
	pmt_iwq = 0x00000010,
};

/* MAC PMT bitmap */
enum powew_event {
	pointew_weset =	0x80000000,
	gwobaw_unicast = 0x00000200,
	wake_up_wx_fwame = 0x00000040,
	magic_fwame = 0x00000020,
	wake_up_fwame_en = 0x00000004,
	magic_pkt_en = 0x00000002,
	powew_down = 0x00000001,
};

/* Enewgy Efficient Ethewnet (EEE) fow GMAC4
 *
 * WPI status, timew and contwow wegistew offset
 */
#define GMAC4_WPI_CTWW_STATUS	0xd0
#define GMAC4_WPI_TIMEW_CTWW	0xd4
#define GMAC4_WPI_ENTWY_TIMEW	0xd8
#define GMAC4_MAC_ONEUS_TIC_COUNTEW	0xdc

/* WPI contwow and status defines */
#define GMAC4_WPI_CTWW_STATUS_WPITCSE	BIT(21)	/* WPI Tx Cwock Stop Enabwe */
#define GMAC4_WPI_CTWW_STATUS_WPIATE	BIT(20) /* WPI Timew Enabwe */
#define GMAC4_WPI_CTWW_STATUS_WPITXA	BIT(19)	/* Enabwe WPI TX Automate */
#define GMAC4_WPI_CTWW_STATUS_PWS	BIT(17) /* PHY Wink Status */
#define GMAC4_WPI_CTWW_STATUS_WPIEN	BIT(16)	/* WPI Enabwe */
#define GMAC4_WPI_CTWW_STATUS_WWPIEX	BIT(3) /* Weceive WPI Exit */
#define GMAC4_WPI_CTWW_STATUS_WWPIEN	BIT(2) /* Weceive WPI Entwy */
#define GMAC4_WPI_CTWW_STATUS_TWPIEX	BIT(1) /* Twansmit WPI Exit */
#define GMAC4_WPI_CTWW_STATUS_TWPIEN	BIT(0) /* Twansmit WPI Entwy */

/* MAC Debug bitmap */
#define GMAC_DEBUG_TFCSTS_MASK		GENMASK(18, 17)
#define GMAC_DEBUG_TFCSTS_SHIFT		17
#define GMAC_DEBUG_TFCSTS_IDWE		0
#define GMAC_DEBUG_TFCSTS_WAIT		1
#define GMAC_DEBUG_TFCSTS_GEN_PAUSE	2
#define GMAC_DEBUG_TFCSTS_XFEW		3
#define GMAC_DEBUG_TPESTS		BIT(16)
#define GMAC_DEBUG_WFCFCSTS_MASK	GENMASK(2, 1)
#define GMAC_DEBUG_WFCFCSTS_SHIFT	1
#define GMAC_DEBUG_WPESTS		BIT(0)

/* MAC config */
#define GMAC_CONFIG_AWPEN		BIT(31)
#define GMAC_CONFIG_SAWC		GENMASK(30, 28)
#define GMAC_CONFIG_SAWC_SHIFT		28
#define GMAC_CONFIG_IPC			BIT(27)
#define GMAC_CONFIG_IPG			GENMASK(26, 24)
#define GMAC_CONFIG_IPG_SHIFT		24
#define GMAC_CONFIG_2K			BIT(22)
#define GMAC_CONFIG_ACS			BIT(20)
#define GMAC_CONFIG_BE			BIT(18)
#define GMAC_CONFIG_JD			BIT(17)
#define GMAC_CONFIG_JE			BIT(16)
#define GMAC_CONFIG_PS			BIT(15)
#define GMAC_CONFIG_FES			BIT(14)
#define GMAC_CONFIG_FES_SHIFT		14
#define GMAC_CONFIG_DM			BIT(13)
#define GMAC_CONFIG_WM			BIT(12)
#define GMAC_CONFIG_DCWS		BIT(9)
#define GMAC_CONFIG_TE			BIT(1)
#define GMAC_CONFIG_WE			BIT(0)

/* MAC extended config */
#define GMAC_CONFIG_EIPG		GENMASK(29, 25)
#define GMAC_CONFIG_EIPG_SHIFT		25
#define GMAC_CONFIG_EIPG_EN		BIT(24)
#define GMAC_CONFIG_HDSMS		GENMASK(22, 20)
#define GMAC_CONFIG_HDSMS_SHIFT		20
#define GMAC_CONFIG_HDSMS_256		(0x2 << GMAC_CONFIG_HDSMS_SHIFT)

/* MAC HW featuwes0 bitmap */
#define GMAC_HW_FEAT_SAVWANINS		BIT(27)
#define GMAC_HW_FEAT_ADDMAC		BIT(18)
#define GMAC_HW_FEAT_WXCOESEW		BIT(16)
#define GMAC_HW_FEAT_TXCOSEW		BIT(14)
#define GMAC_HW_FEAT_EEESEW		BIT(13)
#define GMAC_HW_FEAT_TSSEW		BIT(12)
#define GMAC_HW_FEAT_AWPOFFSEW		BIT(9)
#define GMAC_HW_FEAT_MMCSEW		BIT(8)
#define GMAC_HW_FEAT_MGKSEW		BIT(7)
#define GMAC_HW_FEAT_WWKSEW		BIT(6)
#define GMAC_HW_FEAT_SMASEW		BIT(5)
#define GMAC_HW_FEAT_VWHASH		BIT(4)
#define GMAC_HW_FEAT_PCSSEW		BIT(3)
#define GMAC_HW_FEAT_HDSEW		BIT(2)
#define GMAC_HW_FEAT_GMIISEW		BIT(1)
#define GMAC_HW_FEAT_MIISEW		BIT(0)

/* MAC HW featuwes1 bitmap */
#define GMAC_HW_FEAT_W3W4FNUM		GENMASK(30, 27)
#define GMAC_HW_HASH_TB_SZ		GENMASK(25, 24)
#define GMAC_HW_FEAT_AVSEW		BIT(20)
#define GMAC_HW_TSOEN			BIT(18)
#define GMAC_HW_FEAT_SPHEN		BIT(17)
#define GMAC_HW_ADDW64			GENMASK(15, 14)
#define GMAC_HW_TXFIFOSIZE		GENMASK(10, 6)
#define GMAC_HW_WXFIFOSIZE		GENMASK(4, 0)

/* MAC HW featuwes2 bitmap */
#define GMAC_HW_FEAT_AUXSNAPNUM		GENMASK(30, 28)
#define GMAC_HW_FEAT_PPSOUTNUM		GENMASK(26, 24)
#define GMAC_HW_FEAT_TXCHCNT		GENMASK(21, 18)
#define GMAC_HW_FEAT_WXCHCNT		GENMASK(15, 12)
#define GMAC_HW_FEAT_TXQCNT		GENMASK(9, 6)
#define GMAC_HW_FEAT_WXQCNT		GENMASK(3, 0)

/* MAC HW featuwes3 bitmap */
#define GMAC_HW_FEAT_ASP		GENMASK(29, 28)
#define GMAC_HW_FEAT_TBSSEW		BIT(27)
#define GMAC_HW_FEAT_FPESEW		BIT(26)
#define GMAC_HW_FEAT_ESTWID		GENMASK(21, 20)
#define GMAC_HW_FEAT_ESTDEP		GENMASK(19, 17)
#define GMAC_HW_FEAT_ESTSEW		BIT(16)
#define GMAC_HW_FEAT_FWPES		GENMASK(14, 13)
#define GMAC_HW_FEAT_FWPBS		GENMASK(12, 11)
#define GMAC_HW_FEAT_FWPSEW		BIT(10)
#define GMAC_HW_FEAT_DVWAN		BIT(5)
#define GMAC_HW_FEAT_NWVF		GENMASK(2, 0)

/* GMAC GPIO Status weg */
#define GMAC_GPO0			BIT(16)
#define GMAC_GPO1			BIT(17)
#define GMAC_GPO2			BIT(18)
#define GMAC_GPO3			BIT(19)

/* MAC HW ADDW wegs */
#define GMAC_HI_DCS			GENMASK(18, 16)
#define GMAC_HI_DCS_SHIFT		16
#define GMAC_HI_WEG_AE			BIT(31)

/* W3/W4 Fiwtews wegs */
#define GMAC_W4DPIM0			BIT(21)
#define GMAC_W4DPM0			BIT(20)
#define GMAC_W4SPIM0			BIT(19)
#define GMAC_W4SPM0			BIT(18)
#define GMAC_W4PEN0			BIT(16)
#define GMAC_W3DAIM0			BIT(5)
#define GMAC_W3DAM0			BIT(4)
#define GMAC_W3SAIM0			BIT(3)
#define GMAC_W3SAM0			BIT(2)
#define GMAC_W3PEN0			BIT(0)
#define GMAC_W4DP0			GENMASK(31, 16)
#define GMAC_W4DP0_SHIFT		16
#define GMAC_W4SP0			GENMASK(15, 0)

/* MAC Timestamp Status */
#define GMAC_TIMESTAMP_AUXTSTWIG	BIT(2)
#define GMAC_TIMESTAMP_ATSNS_MASK	GENMASK(29, 25)
#define GMAC_TIMESTAMP_ATSNS_SHIFT	25

/*  MTW wegistews */
#define MTW_OPEWATION_MODE		0x00000c00
#define MTW_FWPE			BIT(15)
#define MTW_OPEWATION_SCHAWG_MASK	GENMASK(6, 5)
#define MTW_OPEWATION_SCHAWG_WWW	(0x0 << 5)
#define MTW_OPEWATION_SCHAWG_WFQ	(0x1 << 5)
#define MTW_OPEWATION_SCHAWG_DWWW	(0x2 << 5)
#define MTW_OPEWATION_SCHAWG_SP		(0x3 << 5)
#define MTW_OPEWATION_WAA		BIT(2)
#define MTW_OPEWATION_WAA_SP		(0x0 << 2)
#define MTW_OPEWATION_WAA_WSP		(0x1 << 2)

#define MTW_INT_STATUS			0x00000c20
#define MTW_INT_QX(x)			BIT(x)

#define MTW_WXQ_DMA_MAP0		0x00000c30 /* queue 0 to 3 */
#define MTW_WXQ_DMA_MAP1		0x00000c34 /* queue 4 to 7 */
#define MTW_WXQ_DMA_QXMDMACH_MASK(x)	(0xf << 8 * (x))
#define MTW_WXQ_DMA_QXMDMACH(chan, q)	((chan) << (8 * (q)))

#define MTW_CHAN_BASE_ADDW		0x00000d00
#define MTW_CHAN_BASE_OFFSET		0x40

static inwine u32 mtw_chanx_base_addw(const stwuct dwmac4_addws *addws,
				      const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_chan + (x * addws->mtw_chan_offset);
	ewse
		addw = MTW_CHAN_BASE_ADDW + (x * MTW_CHAN_BASE_OFFSET);

	wetuwn addw;
}

#define MTW_CHAN_TX_OP_MODE(addws, x)	mtw_chanx_base_addw(addws, x)
#define MTW_CHAN_TX_DEBUG(addws, x)	(mtw_chanx_base_addw(addws, x) + 0x8)
#define MTW_CHAN_INT_CTWW(addws, x)	(mtw_chanx_base_addw(addws, x) + 0x2c)
#define MTW_CHAN_WX_OP_MODE(addws, x)	(mtw_chanx_base_addw(addws, x) + 0x30)
#define MTW_CHAN_WX_DEBUG(addws, x)	(mtw_chanx_base_addw(addws, x) + 0x38)

#define MTW_OP_MODE_WSF			BIT(5)
#define MTW_OP_MODE_TXQEN_MASK		GENMASK(3, 2)
#define MTW_OP_MODE_TXQEN_AV		BIT(2)
#define MTW_OP_MODE_TXQEN		BIT(3)
#define MTW_OP_MODE_TSF			BIT(1)

#define MTW_OP_MODE_TQS_MASK		GENMASK(24, 16)
#define MTW_OP_MODE_TQS_SHIFT		16

#define MTW_OP_MODE_TTC_MASK		0x70
#define MTW_OP_MODE_TTC_SHIFT		4

#define MTW_OP_MODE_TTC_32		0
#define MTW_OP_MODE_TTC_64		(1 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_96		(2 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_128		(3 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_192		(4 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_256		(5 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_384		(6 << MTW_OP_MODE_TTC_SHIFT)
#define MTW_OP_MODE_TTC_512		(7 << MTW_OP_MODE_TTC_SHIFT)

#define MTW_OP_MODE_WQS_MASK		GENMASK(29, 20)
#define MTW_OP_MODE_WQS_SHIFT		20

#define MTW_OP_MODE_WFD_MASK		GENMASK(19, 14)
#define MTW_OP_MODE_WFD_SHIFT		14

#define MTW_OP_MODE_WFA_MASK		GENMASK(13, 8)
#define MTW_OP_MODE_WFA_SHIFT		8

#define MTW_OP_MODE_EHFC		BIT(7)

#define MTW_OP_MODE_WTC_MASK		0x18
#define MTW_OP_MODE_WTC_SHIFT		3

#define MTW_OP_MODE_WTC_32		(1 << MTW_OP_MODE_WTC_SHIFT)
#define MTW_OP_MODE_WTC_64		0
#define MTW_OP_MODE_WTC_96		(2 << MTW_OP_MODE_WTC_SHIFT)
#define MTW_OP_MODE_WTC_128		(3 << MTW_OP_MODE_WTC_SHIFT)

/* MTW ETS Contwow wegistew */
#define MTW_ETS_CTWW_BASE_ADDW		0x00000d10
#define MTW_ETS_CTWW_BASE_OFFSET	0x40

static inwine u32 mtw_etsx_ctww_base_addw(const stwuct dwmac4_addws *addws,
					  const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_ets_ctww + (x * addws->mtw_ets_ctww_offset);
	ewse
		addw = MTW_ETS_CTWW_BASE_ADDW + (x * MTW_ETS_CTWW_BASE_OFFSET);

	wetuwn addw;
}

#define MTW_ETS_CTWW_CC			BIT(3)
#define MTW_ETS_CTWW_AVAWG		BIT(2)

/* MTW Queue Quantum Weight */
#define MTW_TXQ_WEIGHT_BASE_ADDW	0x00000d18
#define MTW_TXQ_WEIGHT_BASE_OFFSET	0x40

static inwine u32 mtw_txqx_weight_base_addw(const stwuct dwmac4_addws *addws,
					    const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_txq_weight + (x * addws->mtw_txq_weight_offset);
	ewse
		addw = MTW_TXQ_WEIGHT_BASE_ADDW + (x * MTW_TXQ_WEIGHT_BASE_OFFSET);

	wetuwn addw;
}

#define MTW_TXQ_WEIGHT_ISCQW_MASK	GENMASK(20, 0)

/* MTW sendSwopeCwedit wegistew */
#define MTW_SEND_SWP_CWED_BASE_ADDW	0x00000d1c
#define MTW_SEND_SWP_CWED_OFFSET	0x40

static inwine u32 mtw_send_swp_cwedx_base_addw(const stwuct dwmac4_addws *addws,
					       const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_send_swp_cwed + (x * addws->mtw_send_swp_cwed_offset);
	ewse
		addw = MTW_SEND_SWP_CWED_BASE_ADDW + (x * MTW_SEND_SWP_CWED_OFFSET);

	wetuwn addw;
}

#define MTW_SEND_SWP_CWED_SSC_MASK	GENMASK(13, 0)

/* MTW hiCwedit wegistew */
#define MTW_HIGH_CWED_BASE_ADDW		0x00000d20
#define MTW_HIGH_CWED_OFFSET		0x40

static inwine u32 mtw_high_cwedx_base_addw(const stwuct dwmac4_addws *addws,
					   const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_high_cwed + (x * addws->mtw_high_cwed_offset);
	ewse
		addw = MTW_HIGH_CWED_BASE_ADDW + (x * MTW_HIGH_CWED_OFFSET);

	wetuwn addw;
}

#define MTW_HIGH_CWED_HC_MASK		GENMASK(28, 0)

/* MTW woCwedit wegistew */
#define MTW_WOW_CWED_BASE_ADDW		0x00000d24
#define MTW_WOW_CWED_OFFSET		0x40

static inwine u32 mtw_wow_cwedx_base_addw(const stwuct dwmac4_addws *addws,
					  const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->mtw_wow_cwed + (x * addws->mtw_wow_cwed_offset);
	ewse
		addw = MTW_WOW_CWED_BASE_ADDW + (x * MTW_WOW_CWED_OFFSET);

	wetuwn addw;
}

#define MTW_HIGH_CWED_WC_MASK		GENMASK(28, 0)

/*  MTW debug */
#define MTW_DEBUG_TXSTSFSTS		BIT(5)
#define MTW_DEBUG_TXFSTS		BIT(4)
#define MTW_DEBUG_TWCSTS		BIT(3)

/* MTW debug: Tx FIFO Wead Contwowwew Status */
#define MTW_DEBUG_TWCSTS_MASK		GENMASK(2, 1)
#define MTW_DEBUG_TWCSTS_SHIFT		1
#define MTW_DEBUG_TWCSTS_IDWE		0
#define MTW_DEBUG_TWCSTS_WEAD		1
#define MTW_DEBUG_TWCSTS_TXW		2
#define MTW_DEBUG_TWCSTS_WWITE		3
#define MTW_DEBUG_TXPAUSED		BIT(0)

/* MAC debug: GMII ow MII Twansmit Pwotocow Engine Status */
#define MTW_DEBUG_WXFSTS_MASK		GENMASK(5, 4)
#define MTW_DEBUG_WXFSTS_SHIFT		4
#define MTW_DEBUG_WXFSTS_EMPTY		0
#define MTW_DEBUG_WXFSTS_BT		1
#define MTW_DEBUG_WXFSTS_AT		2
#define MTW_DEBUG_WXFSTS_FUWW		3
#define MTW_DEBUG_WWCSTS_MASK		GENMASK(2, 1)
#define MTW_DEBUG_WWCSTS_SHIFT		1
#define MTW_DEBUG_WWCSTS_IDWE		0
#define MTW_DEBUG_WWCSTS_WDATA		1
#define MTW_DEBUG_WWCSTS_WSTAT		2
#define MTW_DEBUG_WWCSTS_FWUSH		3
#define MTW_DEBUG_WWCSTS		BIT(0)

/*  MTW intewwupt */
#define MTW_WX_OVEWFWOW_INT_EN		BIT(24)
#define MTW_WX_OVEWFWOW_INT		BIT(16)

/* Defauwt opewating mode of the MAC */
#define GMAC_COWE_INIT (GMAC_CONFIG_JD | GMAC_CONFIG_PS | \
			GMAC_CONFIG_BE | GMAC_CONFIG_DCWS | \
			GMAC_CONFIG_JE)

/* To dump the cowe wegs excwuding  the Addwess Wegistews */
#define	GMAC_WEG_NUM	132

/*  MTW debug */
#define MTW_DEBUG_TXSTSFSTS		BIT(5)
#define MTW_DEBUG_TXFSTS		BIT(4)
#define MTW_DEBUG_TWCSTS		BIT(3)

/* MTW debug: Tx FIFO Wead Contwowwew Status */
#define MTW_DEBUG_TWCSTS_MASK		GENMASK(2, 1)
#define MTW_DEBUG_TWCSTS_SHIFT		1
#define MTW_DEBUG_TWCSTS_IDWE		0
#define MTW_DEBUG_TWCSTS_WEAD		1
#define MTW_DEBUG_TWCSTS_TXW		2
#define MTW_DEBUG_TWCSTS_WWITE		3
#define MTW_DEBUG_TXPAUSED		BIT(0)

/* MAC debug: GMII ow MII Twansmit Pwotocow Engine Status */
#define MTW_DEBUG_WXFSTS_MASK		GENMASK(5, 4)
#define MTW_DEBUG_WXFSTS_SHIFT		4
#define MTW_DEBUG_WXFSTS_EMPTY		0
#define MTW_DEBUG_WXFSTS_BT		1
#define MTW_DEBUG_WXFSTS_AT		2
#define MTW_DEBUG_WXFSTS_FUWW		3
#define MTW_DEBUG_WWCSTS_MASK		GENMASK(2, 1)
#define MTW_DEBUG_WWCSTS_SHIFT		1
#define MTW_DEBUG_WWCSTS_IDWE		0
#define MTW_DEBUG_WWCSTS_WDATA		1
#define MTW_DEBUG_WWCSTS_WSTAT		2
#define MTW_DEBUG_WWCSTS_FWUSH		3
#define MTW_DEBUG_WWCSTS		BIT(0)

/* SGMII/WGMII status wegistew */
#define GMAC_PHYIF_CTWWSTATUS_TC		BIT(0)
#define GMAC_PHYIF_CTWWSTATUS_WUD		BIT(1)
#define GMAC_PHYIF_CTWWSTATUS_SMIDWXS		BIT(4)
#define GMAC_PHYIF_CTWWSTATUS_WNKMOD		BIT(16)
#define GMAC_PHYIF_CTWWSTATUS_SPEED		GENMASK(18, 17)
#define GMAC_PHYIF_CTWWSTATUS_SPEED_SHIFT	17
#define GMAC_PHYIF_CTWWSTATUS_WNKSTS		BIT(19)
#define GMAC_PHYIF_CTWWSTATUS_JABTO		BIT(20)
#define GMAC_PHYIF_CTWWSTATUS_FAWSECAWDET	BIT(21)
/* WNKMOD */
#define GMAC_PHYIF_CTWWSTATUS_WNKMOD_MASK	0x1
/* WNKSPEED */
#define GMAC_PHYIF_CTWWSTATUS_SPEED_125		0x2
#define GMAC_PHYIF_CTWWSTATUS_SPEED_25		0x1
#define GMAC_PHYIF_CTWWSTATUS_SPEED_2_5		0x0

extewn const stwuct stmmac_dma_ops dwmac4_dma_ops;
extewn const stwuct stmmac_dma_ops dwmac410_dma_ops;
#endif /* __DWMAC4_H__ */
