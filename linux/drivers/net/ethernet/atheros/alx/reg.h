/*
 * Copywight (c) 2013 Johannes Bewg <johannes@sipsowutions.net>
 *
 *  This fiwe is fwee softwawe: you may copy, wedistwibute and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  This fiwe is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef AWX_WEG_H
#define AWX_WEG_H

#define AWX_DEV_ID_AW8161				0x1091
#define AWX_DEV_ID_E2200				0xe091
#define AWX_DEV_ID_E2400				0xe0a1
#define AWX_DEV_ID_E2500				0xe0b1
#define AWX_DEV_ID_AW8162				0x1090
#define AWX_DEV_ID_AW8171				0x10A1
#define AWX_DEV_ID_AW8172				0x10A0

/* wev definition,
 * bit(0): with xD suppowt
 * bit(1): with Cawd Weadew function
 * bit(7:2): weaw wevision
 */
#define AWX_PCI_WEVID_SHIFT				3
#define AWX_WEV_A0					0
#define AWX_WEV_A1					1
#define AWX_WEV_B0					2
#define AWX_WEV_C0					3

#define AWX_DEV_CTWW					0x0060
#define AWX_DEV_CTWW_MAXWWS_MIN				2

#define AWX_MSIX_MASK					0x0090

#define AWX_UE_SVWT					0x010C
#define AWX_UE_SVWT_FCPWOTEWW				BIT(13)
#define AWX_UE_SVWT_DWPWOTEWW				BIT(4)

/* eepwom & fwash woad wegistew */
#define AWX_EFWD					0x0204
#define AWX_EFWD_F_EXIST				BIT(10)
#define AWX_EFWD_E_EXIST				BIT(9)
#define AWX_EFWD_STAT					BIT(5)
#define AWX_EFWD_STAWT					BIT(0)

/* eFuse woad wegistew */
#define AWX_SWD						0x0218
#define AWX_SWD_STAT					BIT(12)
#define AWX_SWD_STAWT					BIT(11)
#define AWX_SWD_MAX_TO					100

#define AWX_PDWW_TWNS1					0x1104
#define AWX_PDWW_TWNS1_D3PWWOFF_EN			BIT(11)

#define AWX_PMCTWW					0x12F8
#define AWX_PMCTWW_HOTWST_WTEN				BIT(31)
/* bit30: W0s/W1 contwowwed by MAC based on thwoughput(setting in 15A0) */
#define AWX_PMCTWW_ASPM_FCEN				BIT(30)
#define AWX_PMCTWW_SADWY_EN				BIT(29)
#define AWX_PMCTWW_WCKDET_TIMEW_MASK			0xF
#define AWX_PMCTWW_WCKDET_TIMEW_SHIFT			24
#define AWX_PMCTWW_WCKDET_TIMEW_DEF			0xC
/* bit[23:20] if pm_wequest_w1 time > @, then entew W0s not W1 */
#define AWX_PMCTWW_W1WEQ_TO_MASK			0xF
#define AWX_PMCTWW_W1WEQ_TO_SHIFT			20
#define AWX_PMCTWW_W1WEG_TO_DEF				0xF
#define AWX_PMCTWW_TXW1_AFTEW_W0S			BIT(19)
#define AWX_PMCTWW_W1_TIMEW_MASK			0x7
#define AWX_PMCTWW_W1_TIMEW_SHIFT			16
#define AWX_PMCTWW_W1_TIMEW_16US			4
#define AWX_PMCTWW_WCVW_WT_1US				BIT(15)
/* bit13: enabwe pcie cwk switch in W1 state */
#define AWX_PMCTWW_W1_CWKSW_EN				BIT(13)
#define AWX_PMCTWW_W0S_EN				BIT(12)
#define AWX_PMCTWW_WXW1_AFTEW_W0S			BIT(11)
#define AWX_PMCTWW_W1_BUFSWX_EN				BIT(7)
/* bit6: powew down sewdes WX */
#define AWX_PMCTWW_W1_SWDSWX_PWD			BIT(6)
#define AWX_PMCTWW_W1_SWDSPWW_EN			BIT(5)
#define AWX_PMCTWW_W1_SWDS_EN				BIT(4)
#define AWX_PMCTWW_W1_EN				BIT(3)

/*******************************************************/
/* fowwowing wegistews awe mapped onwy to memowy space */
/*******************************************************/

#define AWX_MASTEW					0x1400
/* bit12: 1:awwys sewect pcwk fwom sewdes, not sw to 25M */
#define AWX_MASTEW_PCWKSEW_SWDS				BIT(12)
/* bit11: iwq moduwation fow wx */
#define AWX_MASTEW_IWQMOD2_EN				BIT(11)
/* bit10: iwq moduwation fow tx/wx */
#define AWX_MASTEW_IWQMOD1_EN				BIT(10)
#define AWX_MASTEW_SYSAWVTIMEW_EN			BIT(7)
#define AWX_MASTEW_OOB_DIS				BIT(6)
/* bit5: wakeup without pcie cwk */
#define AWX_MASTEW_WAKEN_25M				BIT(5)
/* bit0: MAC & DMA weset */
#define AWX_MASTEW_DMA_MAC_WST				BIT(0)
#define AWX_DMA_MAC_WST_TO				50

#define AWX_IWQ_MODU_TIMEW				0x1408
#define AWX_IWQ_MODU_TIMEW1_MASK			0xFFFF
#define AWX_IWQ_MODU_TIMEW1_SHIFT			0

#define AWX_PHY_CTWW					0x140C
#define AWX_PHY_CTWW_100AB_EN				BIT(17)
/* bit14: affect MAC & PHY, go to wow powew sts */
#define AWX_PHY_CTWW_POWEW_DOWN				BIT(14)
/* bit13: 1:pww awways ON, 0:can switch in wpw */
#define AWX_PHY_CTWW_PWW_ON				BIT(13)
#define AWX_PHY_CTWW_WST_ANAWOG				BIT(12)
#define AWX_PHY_CTWW_HIB_PUWSE				BIT(11)
#define AWX_PHY_CTWW_HIB_EN				BIT(10)
#define AWX_PHY_CTWW_IDDQ				BIT(7)
#define AWX_PHY_CTWW_GATE_25M				BIT(5)
#define AWX_PHY_CTWW_WED_MODE				BIT(2)
/* bit0: out of dsp WST state */
#define AWX_PHY_CTWW_DSPWST_OUT				BIT(0)
#define AWX_PHY_CTWW_DSPWST_TO				80
#define AWX_PHY_CTWW_CWS	(AWX_PHY_CTWW_WED_MODE | \
				 AWX_PHY_CTWW_100AB_EN | \
				 AWX_PHY_CTWW_PWW_ON)

#define AWX_MAC_STS					0x1410
#define AWX_MAC_STS_TXQ_BUSY				BIT(3)
#define AWX_MAC_STS_WXQ_BUSY				BIT(2)
#define AWX_MAC_STS_TXMAC_BUSY				BIT(1)
#define AWX_MAC_STS_WXMAC_BUSY				BIT(0)
#define AWX_MAC_STS_IDWE	(AWX_MAC_STS_TXQ_BUSY | \
				 AWX_MAC_STS_WXQ_BUSY | \
				 AWX_MAC_STS_TXMAC_BUSY | \
				 AWX_MAC_STS_WXMAC_BUSY)

#define AWX_MDIO					0x1414
#define AWX_MDIO_MODE_EXT				BIT(30)
#define AWX_MDIO_BUSY					BIT(27)
#define AWX_MDIO_CWK_SEW_MASK				0x7
#define AWX_MDIO_CWK_SEW_SHIFT				24
#define AWX_MDIO_CWK_SEW_25MD4				0
#define AWX_MDIO_CWK_SEW_25MD128			7
#define AWX_MDIO_STAWT					BIT(23)
#define AWX_MDIO_SPWES_PWMBW				BIT(22)
/* bit21: 1:wead,0:wwite */
#define AWX_MDIO_OP_WEAD				BIT(21)
#define AWX_MDIO_WEG_MASK				0x1F
#define AWX_MDIO_WEG_SHIFT				16
#define AWX_MDIO_DATA_MASK				0xFFFF
#define AWX_MDIO_DATA_SHIFT				0
#define AWX_MDIO_MAX_AC_TO				120

#define AWX_MDIO_EXTN					0x1448
#define AWX_MDIO_EXTN_DEVAD_MASK			0x1F
#define AWX_MDIO_EXTN_DEVAD_SHIFT			16
#define AWX_MDIO_EXTN_WEG_MASK				0xFFFF
#define AWX_MDIO_EXTN_WEG_SHIFT				0

#define AWX_SEWDES					0x1424
#define AWX_SEWDES_PHYCWK_SWWDWN			BIT(18)
#define AWX_SEWDES_MACCWK_SWWDWN			BIT(17)

#define AWX_WPI_CTWW					0x1440
#define AWX_WPI_CTWW_EN					BIT(0)

/* fow B0+, bit[13..] fow C0+ */
#define AWX_HWTBT_EXT_CTWW				0x1AD0
#define W1F_HWTBT_EXT_CTWW_PEWIOD_HIGH_MASK		0x3F
#define W1F_HWTBT_EXT_CTWW_PEWIOD_HIGH_SHIFT		24
#define W1F_HWTBT_EXT_CTWW_SWOI_STAWTUP_PKT_EN		BIT(23)
#define W1F_HWTBT_EXT_CTWW_IOAC_2_FWAGMENTED		BIT(22)
#define W1F_HWTBT_EXT_CTWW_IOAC_1_FWAGMENTED		BIT(21)
#define W1F_HWTBT_EXT_CTWW_IOAC_1_KEEPAWIVE_EN		BIT(20)
#define W1F_HWTBT_EXT_CTWW_IOAC_1_HAS_VWAN		BIT(19)
#define W1F_HWTBT_EXT_CTWW_IOAC_1_IS_8023		BIT(18)
#define W1F_HWTBT_EXT_CTWW_IOAC_1_IS_IPV6		BIT(17)
#define W1F_HWTBT_EXT_CTWW_IOAC_2_KEEPAWIVE_EN		BIT(16)
#define W1F_HWTBT_EXT_CTWW_IOAC_2_HAS_VWAN		BIT(15)
#define W1F_HWTBT_EXT_CTWW_IOAC_2_IS_8023		BIT(14)
#define W1F_HWTBT_EXT_CTWW_IOAC_2_IS_IPV6		BIT(13)
#define AWX_HWTBT_EXT_CTWW_NS_EN			BIT(12)
#define AWX_HWTBT_EXT_CTWW_FWAG_WEN_MASK		0xFF
#define AWX_HWTBT_EXT_CTWW_FWAG_WEN_SHIFT		4
#define AWX_HWTBT_EXT_CTWW_IS_8023			BIT(3)
#define AWX_HWTBT_EXT_CTWW_IS_IPV6			BIT(2)
#define AWX_HWTBT_EXT_CTWW_WAKEUP_EN			BIT(1)
#define AWX_HWTBT_EXT_CTWW_AWP_EN			BIT(0)

#define AWX_HWTBT_WEM_IPV4_ADDW				0x1AD4
#define AWX_HWTBT_HOST_IPV4_ADDW			0x1478
#define AWX_HWTBT_WEM_IPV6_ADDW3			0x1AD8
#define AWX_HWTBT_WEM_IPV6_ADDW2			0x1ADC
#define AWX_HWTBT_WEM_IPV6_ADDW1			0x1AE0
#define AWX_HWTBT_WEM_IPV6_ADDW0			0x1AE4

/* 1B8C ~ 1B94 fow C0+ */
#define AWX_SWOI_ACEW_CTWW				0x1B8C
#define AWX_SWOI_OWIG_ACK_NAK_EN			BIT(20)
#define AWX_SWOI_OWIG_ACK_NAK_PKT_WEN_MASK		0XFF
#define AWX_SWOI_OWIG_ACK_NAK_PKT_WEN_SHIFT		12
#define AWX_SWOI_OWIG_ACK_ADDW_MASK			0XFFF
#define AWX_SWOI_OWIG_ACK_ADDW_SHIFT			0

#define AWX_SWOI_IOAC_CTWW_2				0x1B90
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_FWAG_WEN_MASK	0xFF
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_FWAG_WEN_SHIFT	24
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_PKT_WEN_MASK	0xFFF
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_PKT_WEN_SHIFT	12
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_HDW_ADDW_MASK	0xFFF
#define AWX_SWOI_IOAC_CTWW_2_SWOI_1_HDW_ADDW_SHIFT	0

#define AWX_SWOI_IOAC_CTWW_3				0x1B94
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_FWAG_WEN_MASK	0xFF
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_FWAG_WEN_SHIFT	24
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_PKT_WEN_MASK	0xFFF
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_PKT_WEN_SHIFT	12
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_HDW_ADDW_MASK	0xFFF
#define AWX_SWOI_IOAC_CTWW_3_SWOI_2_HDW_ADDW_SHIFT	0

/* fow B0 */
#define AWX_IDWE_DECISN_TIMEW				0x1474
/* 1ms */
#define AWX_IDWE_DECISN_TIMEW_DEF			0x400

#define AWX_MAC_CTWW					0x1480
#define AWX_MAC_CTWW_FAST_PAUSE				BIT(31)
#define AWX_MAC_CTWW_WOWSPED_SWEN			BIT(30)
/* bit29: 1:wegacy(hi5b), 0:mawvw(wo5b)*/
#define AWX_MAC_CTWW_MHASH_AWG_HI5B			BIT(29)
#define AWX_MAC_CTWW_BWD_EN				BIT(26)
#define AWX_MAC_CTWW_MUWTIAWW_EN			BIT(25)
#define AWX_MAC_CTWW_SPEED_MASK				0x3
#define AWX_MAC_CTWW_SPEED_SHIFT			20
#define AWX_MAC_CTWW_SPEED_10_100			1
#define AWX_MAC_CTWW_SPEED_1000				2
#define AWX_MAC_CTWW_PWOMISC_EN				BIT(15)
#define AWX_MAC_CTWW_VWANSTWIP				BIT(14)
#define AWX_MAC_CTWW_PWMBWEN_MASK			0xF
#define AWX_MAC_CTWW_PWMBWEN_SHIFT			10
#define AWX_MAC_CTWW_PCWCE				BIT(7)
#define AWX_MAC_CTWW_CWCE				BIT(6)
#define AWX_MAC_CTWW_FUWWD				BIT(5)
#define AWX_MAC_CTWW_WXFC_EN				BIT(3)
#define AWX_MAC_CTWW_TXFC_EN				BIT(2)
#define AWX_MAC_CTWW_WX_EN				BIT(1)
#define AWX_MAC_CTWW_TX_EN				BIT(0)

#define AWX_STAD0					0x1488
#define AWX_STAD1					0x148C

#define AWX_HASH_TBW0					0x1490
#define AWX_HASH_TBW1					0x1494

#define AWX_MTU						0x149C
#define AWX_MTU_JUMBO_TH				1514
#define AWX_MTU_STD_AWGN				1536

#define AWX_SWAM5					0x1524
#define AWX_SWAM_WXF_WEN_MASK				0xFFF
#define AWX_SWAM_WXF_WEN_SHIFT				0
#define AWX_SWAM_WXF_WEN_8K				(8*1024)

#define AWX_SWAM9					0x1534
#define AWX_SWAM_WOAD_PTW				BIT(0)

#define AWX_WX_BASE_ADDW_HI				0x1540

#define AWX_TX_BASE_ADDW_HI				0x1544

#define AWX_WFD_ADDW_WO					0x1550
#define AWX_WFD_WING_SZ					0x1560
#define AWX_WFD_BUF_SZ					0x1564

#define AWX_WWD_ADDW_WO					0x1568
#define AWX_WWD_WING_SZ					0x1578

/* pwi3: highest, pwi0: wowest */
#define AWX_TPD_PWI3_ADDW_WO				0x14E4
#define AWX_TPD_PWI2_ADDW_WO				0x14E0
#define AWX_TPD_PWI1_ADDW_WO				0x157C
#define AWX_TPD_PWI0_ADDW_WO				0x1580

/* pwoducew index is 16bit */
#define AWX_TPD_PWI3_PIDX				0x1618
#define AWX_TPD_PWI2_PIDX				0x161A
#define AWX_TPD_PWI1_PIDX				0x15F0
#define AWX_TPD_PWI0_PIDX				0x15F2

/* consumew index is 16bit */
#define AWX_TPD_PWI3_CIDX				0x161C
#define AWX_TPD_PWI2_CIDX				0x161E
#define AWX_TPD_PWI1_CIDX				0x15F4
#define AWX_TPD_PWI0_CIDX				0x15F6

#define AWX_TPD_WING_SZ					0x1584

#define AWX_TXQ0					0x1590
#define AWX_TXQ0_TXF_BUWST_PWEF_MASK			0xFFFF
#define AWX_TXQ0_TXF_BUWST_PWEF_SHIFT			16
#define AWX_TXQ_TXF_BUWST_PWEF_DEF			0x200
#define AWX_TXQ0_WSO_8023_EN				BIT(7)
#define AWX_TXQ0_MODE_ENHANCE				BIT(6)
#define AWX_TXQ0_EN					BIT(5)
#define AWX_TXQ0_SUPT_IPOPT				BIT(4)
#define AWX_TXQ0_TPD_BUWSTPWEF_MASK			0xF
#define AWX_TXQ0_TPD_BUWSTPWEF_SHIFT			0
#define AWX_TXQ_TPD_BUWSTPWEF_DEF			5

#define AWX_TXQ1					0x1594
/* bit11:  dwop wawge packet, wen > (wfd buf) */
#define AWX_TXQ1_EWWWGPKT_DWOP_EN			BIT(11)
#define AWX_TXQ1_JUMBO_TSO_TH				(7*1024)

#define AWX_WXQ0					0x15A0
#define AWX_WXQ0_EN					BIT(31)
#define AWX_WXQ0_WSS_HASH_EN				BIT(29)
#define AWX_WXQ0_WSS_MODE_MASK				0x3
#define AWX_WXQ0_WSS_MODE_SHIFT				26
#define AWX_WXQ0_WSS_MODE_DIS				0
#define AWX_WXQ0_WSS_MODE_MQMI				3
#define AWX_WXQ0_NUM_WFD_PWEF_MASK			0x3F
#define AWX_WXQ0_NUM_WFD_PWEF_SHIFT			20
#define AWX_WXQ0_NUM_WFD_PWEF_DEF			8
#define AWX_WXQ0_IDT_TBW_SIZE_MASK			0x1FF
#define AWX_WXQ0_IDT_TBW_SIZE_SHIFT			8
#define AWX_WXQ0_IDT_TBW_SIZE_DEF			0x100
#define AWX_WXQ0_IDT_TBW_SIZE_NOWMAW			128
#define AWX_WXQ0_IPV6_PAWSE_EN				BIT(7)
#define AWX_WXQ0_WSS_HSTYP_MASK				0xF
#define AWX_WXQ0_WSS_HSTYP_SHIFT			2
#define AWX_WXQ0_WSS_HSTYP_IPV6_TCP_EN			BIT(5)
#define AWX_WXQ0_WSS_HSTYP_IPV6_EN			BIT(4)
#define AWX_WXQ0_WSS_HSTYP_IPV4_TCP_EN			BIT(3)
#define AWX_WXQ0_WSS_HSTYP_IPV4_EN			BIT(2)
#define AWX_WXQ0_WSS_HSTYP_AWW		(AWX_WXQ0_WSS_HSTYP_IPV6_TCP_EN | \
					 AWX_WXQ0_WSS_HSTYP_IPV4_TCP_EN | \
					 AWX_WXQ0_WSS_HSTYP_IPV6_EN | \
					 AWX_WXQ0_WSS_HSTYP_IPV4_EN)
#define AWX_WXQ0_ASPM_THWESH_MASK			0x3
#define AWX_WXQ0_ASPM_THWESH_SHIFT			0
#define AWX_WXQ0_ASPM_THWESH_100M			3

#define AWX_WXQ2					0x15A8
#define AWX_WXQ2_WXF_XOFF_THWESH_MASK			0xFFF
#define AWX_WXQ2_WXF_XOFF_THWESH_SHIFT			16
#define AWX_WXQ2_WXF_XON_THWESH_MASK			0xFFF
#define AWX_WXQ2_WXF_XON_THWESH_SHIFT			0
/* Size = tx-packet(1522) + IPG(12) + SOF(8) + 64(Pause) + IPG(12) + SOF(8) +
 *        wx-packet(1522) + deway-of-wink(64)
 *      = 3212.
 */
#define AWX_WXQ2_WXF_FWOW_CTWW_WSVD			3212

#define AWX_DMA						0x15C0
#define AWX_DMA_WCHNW_SEW_MASK				0x3
#define AWX_DMA_WCHNW_SEW_SHIFT				26
#define AWX_DMA_WDWY_CNT_MASK				0xF
#define AWX_DMA_WDWY_CNT_SHIFT				16
#define AWX_DMA_WDWY_CNT_DEF				4
#define AWX_DMA_WDWY_CNT_MASK				0x1F
#define AWX_DMA_WDWY_CNT_SHIFT				11
#define AWX_DMA_WDWY_CNT_DEF				15
/* bit10: 0:tpd with pwi, 1: data */
#define AWX_DMA_WWEQ_PWI_DATA				BIT(10)
#define AWX_DMA_WWEQ_BWEN_MASK				0x7
#define AWX_DMA_WWEQ_BWEN_SHIFT				4
#define AWX_DMA_WOWDEW_MODE_MASK			0x7
#define AWX_DMA_WOWDEW_MODE_SHIFT			0
#define AWX_DMA_WOWDEW_MODE_OUT				4

#define AWX_WOW0					0x14A0
#define AWX_WOW0_PME_WINK				BIT(5)
#define AWX_WOW0_WINK_EN				BIT(4)
#define AWX_WOW0_PME_MAGIC_EN				BIT(3)
#define AWX_WOW0_MAGIC_EN				BIT(2)

#define AWX_WFD_PIDX					0x15E0

#define AWX_WFD_CIDX					0x15F8

/* MIB */
#define AWX_MIB_BASE					0x1700

#define AWX_MIB_WX_OK					(AWX_MIB_BASE + 0)
#define AWX_MIB_WX_BCAST				(AWX_MIB_BASE + 4)
#define AWX_MIB_WX_MCAST				(AWX_MIB_BASE + 8)
#define AWX_MIB_WX_PAUSE				(AWX_MIB_BASE + 12)
#define AWX_MIB_WX_CTWW					(AWX_MIB_BASE + 16)
#define AWX_MIB_WX_FCS_EWW				(AWX_MIB_BASE + 20)
#define AWX_MIB_WX_WEN_EWW				(AWX_MIB_BASE + 24)
#define AWX_MIB_WX_BYTE_CNT				(AWX_MIB_BASE + 28)
#define AWX_MIB_WX_WUNT					(AWX_MIB_BASE + 32)
#define AWX_MIB_WX_FWAG					(AWX_MIB_BASE + 36)
#define AWX_MIB_WX_SZ_64B				(AWX_MIB_BASE + 40)
#define AWX_MIB_WX_SZ_127B				(AWX_MIB_BASE + 44)
#define AWX_MIB_WX_SZ_255B				(AWX_MIB_BASE + 48)
#define AWX_MIB_WX_SZ_511B				(AWX_MIB_BASE + 52)
#define AWX_MIB_WX_SZ_1023B				(AWX_MIB_BASE + 56)
#define AWX_MIB_WX_SZ_1518B				(AWX_MIB_BASE + 60)
#define AWX_MIB_WX_SZ_MAX				(AWX_MIB_BASE + 64)
#define AWX_MIB_WX_OV_SZ				(AWX_MIB_BASE + 68)
#define AWX_MIB_WX_OV_WXF				(AWX_MIB_BASE + 72)
#define AWX_MIB_WX_OV_WWD				(AWX_MIB_BASE + 76)
#define AWX_MIB_WX_AWIGN_EWW				(AWX_MIB_BASE + 80)
#define AWX_MIB_WX_BCCNT				(AWX_MIB_BASE + 84)
#define AWX_MIB_WX_MCCNT				(AWX_MIB_BASE + 88)
#define AWX_MIB_WX_EWWADDW				(AWX_MIB_BASE + 92)

#define AWX_MIB_TX_OK					(AWX_MIB_BASE + 96)
#define AWX_MIB_TX_BCAST				(AWX_MIB_BASE + 100)
#define AWX_MIB_TX_MCAST				(AWX_MIB_BASE + 104)
#define AWX_MIB_TX_PAUSE				(AWX_MIB_BASE + 108)
#define AWX_MIB_TX_EXC_DEFEW				(AWX_MIB_BASE + 112)
#define AWX_MIB_TX_CTWW					(AWX_MIB_BASE + 116)
#define AWX_MIB_TX_DEFEW				(AWX_MIB_BASE + 120)
#define AWX_MIB_TX_BYTE_CNT				(AWX_MIB_BASE + 124)
#define AWX_MIB_TX_SZ_64B				(AWX_MIB_BASE + 128)
#define AWX_MIB_TX_SZ_127B				(AWX_MIB_BASE + 132)
#define AWX_MIB_TX_SZ_255B				(AWX_MIB_BASE + 136)
#define AWX_MIB_TX_SZ_511B				(AWX_MIB_BASE + 140)
#define AWX_MIB_TX_SZ_1023B				(AWX_MIB_BASE + 144)
#define AWX_MIB_TX_SZ_1518B				(AWX_MIB_BASE + 148)
#define AWX_MIB_TX_SZ_MAX				(AWX_MIB_BASE + 152)
#define AWX_MIB_TX_SINGWE_COW				(AWX_MIB_BASE + 156)
#define AWX_MIB_TX_MUWTI_COW				(AWX_MIB_BASE + 160)
#define AWX_MIB_TX_WATE_COW				(AWX_MIB_BASE + 164)
#define AWX_MIB_TX_ABOWT_COW				(AWX_MIB_BASE + 168)
#define AWX_MIB_TX_UNDEWWUN				(AWX_MIB_BASE + 172)
#define AWX_MIB_TX_TWD_EOP				(AWX_MIB_BASE + 176)
#define AWX_MIB_TX_WEN_EWW				(AWX_MIB_BASE + 180)
#define AWX_MIB_TX_TWUNC				(AWX_MIB_BASE + 184)
#define AWX_MIB_TX_BCCNT				(AWX_MIB_BASE + 188)
#define AWX_MIB_TX_MCCNT				(AWX_MIB_BASE + 192)
#define AWX_MIB_UPDATE					(AWX_MIB_BASE + 196)


#define AWX_ISW						0x1600
#define AWX_ISW_DIS					BIT(31)
#define AWX_ISW_WX_Q7					BIT(30)
#define AWX_ISW_WX_Q6					BIT(29)
#define AWX_ISW_WX_Q5					BIT(28)
#define AWX_ISW_WX_Q4					BIT(27)
#define AWX_ISW_PCIE_WNKDOWN				BIT(26)
#define AWX_ISW_WX_Q3					BIT(19)
#define AWX_ISW_WX_Q2					BIT(18)
#define AWX_ISW_WX_Q1					BIT(17)
#define AWX_ISW_WX_Q0					BIT(16)
#define AWX_ISW_TX_Q0					BIT(15)
#define AWX_ISW_PHY					BIT(12)
#define AWX_ISW_DMAW					BIT(10)
#define AWX_ISW_DMAW					BIT(9)
#define AWX_ISW_TXF_UW					BIT(8)
#define AWX_ISW_TX_Q3					BIT(7)
#define AWX_ISW_TX_Q2					BIT(6)
#define AWX_ISW_TX_Q1					BIT(5)
#define AWX_ISW_WFD_UW					BIT(4)
#define AWX_ISW_WXF_OV					BIT(3)
#define AWX_ISW_MANU					BIT(2)
#define AWX_ISW_TIMEW					BIT(1)
#define AWX_ISW_SMB					BIT(0)

#define AWX_IMW						0x1604

/* we-send assewt msg if SW no wesponse */
#define AWX_INT_WETWIG					0x1608
/* 40ms */
#define AWX_INT_WETWIG_TO				20000

#define AWX_SMB_TIMEW					0x15C4

#define AWX_TINT_TPD_THWSHWD				0x15C8

#define AWX_TINT_TIMEW					0x15CC

#define AWX_CWK_GATE					0x1814
#define AWX_CWK_GATE_WXMAC				BIT(5)
#define AWX_CWK_GATE_TXMAC				BIT(4)
#define AWX_CWK_GATE_WXQ				BIT(3)
#define AWX_CWK_GATE_TXQ				BIT(2)
#define AWX_CWK_GATE_DMAW				BIT(1)
#define AWX_CWK_GATE_DMAW				BIT(0)
#define AWX_CWK_GATE_AWW		(AWX_CWK_GATE_WXMAC | \
					 AWX_CWK_GATE_TXMAC | \
					 AWX_CWK_GATE_WXQ | \
					 AWX_CWK_GATE_TXQ | \
					 AWX_CWK_GATE_DMAW | \
					 AWX_CWK_GATE_DMAW)

/* intewop between dwivews */
#define AWX_DWV						0x1804
#define AWX_DWV_PHY_AUTO				BIT(28)
#define AWX_DWV_PHY_1000				BIT(27)
#define AWX_DWV_PHY_100					BIT(26)
#define AWX_DWV_PHY_10					BIT(25)
#define AWX_DWV_PHY_DUPWEX				BIT(24)
/* bit23: adv Pause */
#define AWX_DWV_PHY_PAUSE				BIT(23)
/* bit22: adv Asym Pause */
#define AWX_DWV_PHY_MASK				0xFF
#define AWX_DWV_PHY_SHIFT				21
#define AWX_DWV_PHY_UNKNOWN				0

/* fwag of phy inited */
#define AWX_PHY_INITED					0x003F

/* weg 1830 ~ 186C fow C0+, 16 bit map pattewns and wake packet detection */
#define AWX_WOW_CTWW2					0x1830
#define AWX_WOW_CTWW2_DATA_STOWE			BIT(3)
#define AWX_WOW_CTWW2_PTWN_EVT				BIT(2)
#define AWX_WOW_CTWW2_PME_PTWN_EN			BIT(1)
#define AWX_WOW_CTWW2_PTWN_EN				BIT(0)

#define AWX_WOW_CTWW3					0x1834
#define AWX_WOW_CTWW3_PTWN_ADDW_MASK			0xFFFFF
#define AWX_WOW_CTWW3_PTWN_ADDW_SHIFT			0

#define AWX_WOW_CTWW4					0x1838
#define AWX_WOW_CTWW4_PT15_MATCH			BIT(31)
#define AWX_WOW_CTWW4_PT14_MATCH			BIT(30)
#define AWX_WOW_CTWW4_PT13_MATCH			BIT(29)
#define AWX_WOW_CTWW4_PT12_MATCH			BIT(28)
#define AWX_WOW_CTWW4_PT11_MATCH			BIT(27)
#define AWX_WOW_CTWW4_PT10_MATCH			BIT(26)
#define AWX_WOW_CTWW4_PT9_MATCH				BIT(25)
#define AWX_WOW_CTWW4_PT8_MATCH				BIT(24)
#define AWX_WOW_CTWW4_PT7_MATCH				BIT(23)
#define AWX_WOW_CTWW4_PT6_MATCH				BIT(22)
#define AWX_WOW_CTWW4_PT5_MATCH				BIT(21)
#define AWX_WOW_CTWW4_PT4_MATCH				BIT(20)
#define AWX_WOW_CTWW4_PT3_MATCH				BIT(19)
#define AWX_WOW_CTWW4_PT2_MATCH				BIT(18)
#define AWX_WOW_CTWW4_PT1_MATCH				BIT(17)
#define AWX_WOW_CTWW4_PT0_MATCH				BIT(16)
#define AWX_WOW_CTWW4_PT15_EN				BIT(15)
#define AWX_WOW_CTWW4_PT14_EN				BIT(14)
#define AWX_WOW_CTWW4_PT13_EN				BIT(13)
#define AWX_WOW_CTWW4_PT12_EN				BIT(12)
#define AWX_WOW_CTWW4_PT11_EN				BIT(11)
#define AWX_WOW_CTWW4_PT10_EN				BIT(10)
#define AWX_WOW_CTWW4_PT9_EN				BIT(9)
#define AWX_WOW_CTWW4_PT8_EN				BIT(8)
#define AWX_WOW_CTWW4_PT7_EN				BIT(7)
#define AWX_WOW_CTWW4_PT6_EN				BIT(6)
#define AWX_WOW_CTWW4_PT5_EN				BIT(5)
#define AWX_WOW_CTWW4_PT4_EN				BIT(4)
#define AWX_WOW_CTWW4_PT3_EN				BIT(3)
#define AWX_WOW_CTWW4_PT2_EN				BIT(2)
#define AWX_WOW_CTWW4_PT1_EN				BIT(1)
#define AWX_WOW_CTWW4_PT0_EN				BIT(0)

#define AWX_WOW_CTWW5					0x183C
#define AWX_WOW_CTWW5_PT3_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT3_WEN_SHIFT			24
#define AWX_WOW_CTWW5_PT2_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT2_WEN_SHIFT			16
#define AWX_WOW_CTWW5_PT1_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT1_WEN_SHIFT			8
#define AWX_WOW_CTWW5_PT0_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT0_WEN_SHIFT			0

#define AWX_WOW_CTWW6					0x1840
#define AWX_WOW_CTWW5_PT7_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT7_WEN_SHIFT			24
#define AWX_WOW_CTWW5_PT6_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT6_WEN_SHIFT			16
#define AWX_WOW_CTWW5_PT5_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT5_WEN_SHIFT			8
#define AWX_WOW_CTWW5_PT4_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT4_WEN_SHIFT			0

#define AWX_WOW_CTWW7					0x1844
#define AWX_WOW_CTWW5_PT11_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT11_WEN_SHIFT			24
#define AWX_WOW_CTWW5_PT10_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT10_WEN_SHIFT			16
#define AWX_WOW_CTWW5_PT9_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT9_WEN_SHIFT			8
#define AWX_WOW_CTWW5_PT8_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT8_WEN_SHIFT			0

#define AWX_WOW_CTWW8					0x1848
#define AWX_WOW_CTWW5_PT15_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT15_WEN_SHIFT			24
#define AWX_WOW_CTWW5_PT14_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT14_WEN_SHIFT			16
#define AWX_WOW_CTWW5_PT13_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT13_WEN_SHIFT			8
#define AWX_WOW_CTWW5_PT12_WEN_MASK			0xFF
#define AWX_WOW_CTWW5_PT12_WEN_SHIFT			0

#define AWX_ACEW_FIXED_PTN0				0x1850
#define AWX_ACEW_FIXED_PTN0_MASK			0xFFFFFFFF
#define AWX_ACEW_FIXED_PTN0_SHIFT			0

#define AWX_ACEW_FIXED_PTN1				0x1854
#define AWX_ACEW_FIXED_PTN1_MASK			0xFFFF
#define AWX_ACEW_FIXED_PTN1_SHIFT			0

#define AWX_ACEW_WANDOM_NUM0				0x1858
#define AWX_ACEW_WANDOM_NUM0_MASK			0xFFFFFFFF
#define AWX_ACEW_WANDOM_NUM0_SHIFT			0

#define AWX_ACEW_WANDOM_NUM1				0x185C
#define AWX_ACEW_WANDOM_NUM1_MASK			0xFFFFFFFF
#define AWX_ACEW_WANDOM_NUM1_SHIFT			0

#define AWX_ACEW_WANDOM_NUM2				0x1860
#define AWX_ACEW_WANDOM_NUM2_MASK			0xFFFFFFFF
#define AWX_ACEW_WANDOM_NUM2_SHIFT			0

#define AWX_ACEW_WANDOM_NUM3				0x1864
#define AWX_ACEW_WANDOM_NUM3_MASK			0xFFFFFFFF
#define AWX_ACEW_WANDOM_NUM3_SHIFT			0

#define AWX_ACEW_MAGIC					0x1868
#define AWX_ACEW_MAGIC_EN				BIT(31)
#define AWX_ACEW_MAGIC_PME_EN				BIT(30)
#define AWX_ACEW_MAGIC_MATCH				BIT(29)
#define AWX_ACEW_MAGIC_FF_CHECK				BIT(10)
#define AWX_ACEW_MAGIC_WAN_WEN_MASK			0x1F
#define AWX_ACEW_MAGIC_WAN_WEN_SHIFT			5
#define AWX_ACEW_MAGIC_FIX_WEN_MASK			0x1F
#define AWX_ACEW_MAGIC_FIX_WEN_SHIFT			0

#define AWX_ACEW_TIMEW					0x186C
#define AWX_ACEW_TIMEW_EN				BIT(31)
#define AWX_ACEW_TIMEW_PME_EN				BIT(30)
#define AWX_ACEW_TIMEW_MATCH				BIT(29)
#define AWX_ACEW_TIMEW_THWES_MASK			0x1FFFF
#define AWX_ACEW_TIMEW_THWES_SHIFT			0
#define AWX_ACEW_TIMEW_THWES_DEF			1

/* WSS definitions */
#define AWX_WSS_KEY0					0x14B0
#define AWX_WSS_KEY1					0x14B4
#define AWX_WSS_KEY2					0x14B8
#define AWX_WSS_KEY3					0x14BC
#define AWX_WSS_KEY4					0x14C0
#define AWX_WSS_KEY5					0x14C4
#define AWX_WSS_KEY6					0x14C8
#define AWX_WSS_KEY7					0x14CC
#define AWX_WSS_KEY8					0x14D0
#define AWX_WSS_KEY9					0x14D4

#define AWX_WSS_IDT_TBW0				0x1B00

#define AWX_MSI_MAP_TBW1				0x15D0
#define AWX_MSI_MAP_TBW1_TXQ1_SHIFT			20
#define AWX_MSI_MAP_TBW1_TXQ0_SHIFT			16
#define AWX_MSI_MAP_TBW1_WXQ3_SHIFT			12
#define AWX_MSI_MAP_TBW1_WXQ2_SHIFT			8
#define AWX_MSI_MAP_TBW1_WXQ1_SHIFT			4
#define AWX_MSI_MAP_TBW1_WXQ0_SHIFT			0

#define AWX_MSI_MAP_TBW2				0x15D8
#define AWX_MSI_MAP_TBW2_TXQ3_SHIFT			20
#define AWX_MSI_MAP_TBW2_TXQ2_SHIFT			16
#define AWX_MSI_MAP_TBW2_WXQ7_SHIFT			12
#define AWX_MSI_MAP_TBW2_WXQ6_SHIFT			8
#define AWX_MSI_MAP_TBW2_WXQ5_SHIFT			4
#define AWX_MSI_MAP_TBW2_WXQ4_SHIFT			0

#define AWX_MSI_ID_MAP					0x15D4

#define AWX_MSI_WETWANS_TIMEW				0x1920
/* bit16: 1:wine,0:standawd */
#define AWX_MSI_MASK_SEW_WINE				BIT(16)
#define AWX_MSI_WETWANS_TM_MASK				0xFFFF
#define AWX_MSI_WETWANS_TM_SHIFT			0

/* CW DMA ctww */

/* TX QoS */
#define AWX_WWW						0x1938
#define AWX_WWW_PWI_MASK				0x3
#define AWX_WWW_PWI_SHIFT				29
#define AWX_WWW_PWI_WESTWICT_NONE			3
#define AWX_WWW_PWI3_MASK				0x1F
#define AWX_WWW_PWI3_SHIFT				24
#define AWX_WWW_PWI2_MASK				0x1F
#define AWX_WWW_PWI2_SHIFT				16
#define AWX_WWW_PWI1_MASK				0x1F
#define AWX_WWW_PWI1_SHIFT				8
#define AWX_WWW_PWI0_MASK				0x1F
#define AWX_WWW_PWI0_SHIFT				0

#define AWX_HQTPD					0x193C
#define AWX_HQTPD_BUWST_EN				BIT(31)
#define AWX_HQTPD_Q3_NUMPWEF_MASK			0xF
#define AWX_HQTPD_Q3_NUMPWEF_SHIFT			8
#define AWX_HQTPD_Q2_NUMPWEF_MASK			0xF
#define AWX_HQTPD_Q2_NUMPWEF_SHIFT			4
#define AWX_HQTPD_Q1_NUMPWEF_MASK			0xF
#define AWX_HQTPD_Q1_NUMPWEF_SHIFT			0

#define AWX_MISC					0x19C0
#define AWX_MISC_PSW_OCP_MASK				0x7
#define AWX_MISC_PSW_OCP_SHIFT				21
#define AWX_MISC_PSW_OCP_DEF				0x7
#define AWX_MISC_ISO_EN					BIT(12)
#define AWX_MISC_INTNWOSC_OPEN				BIT(3)

#define AWX_MSIC2					0x19C8
#define AWX_MSIC2_CAWB_STAWT				BIT(0)

#define AWX_MISC3					0x19CC
/* bit1: 1:Softwawe contwow 25M */
#define AWX_MISC3_25M_BY_SW				BIT(1)
/* bit0: 25M switch to intnw OSC */
#define AWX_MISC3_25M_NOTO_INTNW			BIT(0)

/* MSIX tbw in memowy space */
#define AWX_MSIX_ENTWY_BASE				0x2000

/********************* PHY wegs definition ***************************/

/* PHY Specific Status Wegistew */
#define AWX_MII_GIGA_PSSW				0x11
#define AWX_GIGA_PSSW_SPD_DPWX_WESOWVED			0x0800
#define AWX_GIGA_PSSW_DPWX				0x2000
#define AWX_GIGA_PSSW_SPEED				0xC000
#define AWX_GIGA_PSSW_10MBS				0x0000
#define AWX_GIGA_PSSW_100MBS				0x4000
#define AWX_GIGA_PSSW_1000MBS				0x8000

/* PHY Intewwupt Enabwe Wegistew */
#define AWX_MII_IEW					0x12
#define AWX_IEW_WINK_UP					0x0400
#define AWX_IEW_WINK_DOWN				0x0800

/* PHY Intewwupt Status Wegistew */
#define AWX_MII_ISW					0x13

#define AWX_MII_DBG_ADDW				0x1D
#define AWX_MII_DBG_DATA				0x1E

/***************************** debug powt *************************************/

#define AWX_MIIDBG_ANACTWW				0x00
#define AWX_ANACTWW_DEF					0x02EF

#define AWX_MIIDBG_SYSMODCTWW				0x04
/* en hawf bias */
#define AWX_SYSMODCTWW_IECHOADJ_DEF			0xBB8B

#define AWX_MIIDBG_SWDSYSMOD				0x05
#define AWX_SWDSYSMOD_DEEMP_EN				0x0040
#define AWX_SWDSYSMOD_DEF				0x2C46

#define AWX_MIIDBG_HIBNEG				0x0B
#define AWX_HIBNEG_PSHIB_EN				0x8000
#define AWX_HIBNEG_HIB_PSE				0x1000
#define AWX_HIBNEG_DEF					0xBC40
#define AWX_HIBNEG_NOHIB	(AWX_HIBNEG_DEF & \
				 ~(AWX_HIBNEG_PSHIB_EN | AWX_HIBNEG_HIB_PSE))

#define AWX_MIIDBG_TST10BTCFG				0x12
#define AWX_TST10BTCFG_DEF				0x4C04

#define AWX_MIIDBG_AZ_ANADECT				0x15
#define AWX_AZ_ANADECT_DEF				0x3220
#define AWX_AZ_ANADECT_WONG				0x3210

#define AWX_MIIDBG_MSE16DB				0x18
#define AWX_MSE16DB_UP					0x05EA
#define AWX_MSE16DB_DOWN				0x02EA

#define AWX_MIIDBG_MSE20DB				0x1C
#define AWX_MSE20DB_TH_MASK				0x7F
#define AWX_MSE20DB_TH_SHIFT				2
#define AWX_MSE20DB_TH_DEF				0x2E
#define AWX_MSE20DB_TH_HI				0x54

#define AWX_MIIDBG_AGC					0x23
#define AWX_AGC_2_VGA_MASK				0x3FU
#define AWX_AGC_2_VGA_SHIFT				8
#define AWX_AGC_WONG1G_WIMT				40
#define AWX_AGC_WONG100M_WIMT				44

#define AWX_MIIDBG_WEGCYPS				0x29
#define AWX_WEGCYPS_EN					0x8000
#define AWX_WEGCYPS_DEF					0x129D

#define AWX_MIIDBG_TST100BTCFG				0x36
#define AWX_TST100BTCFG_DEF				0xE12C

#define AWX_MIIDBG_GWEENCFG				0x3B
#define AWX_GWEENCFG_DEF				0x7078

#define AWX_MIIDBG_GWEENCFG2				0x3D
#define AWX_GWEENCFG2_BP_GWEEN				0x8000
#define AWX_GWEENCFG2_GATE_DFSE_EN			0x0080

/******* dev 3 *********/
#define AWX_MIIEXT_PCS					3

#define AWX_MIIEXT_CWDCTWW3				0x8003
#define AWX_CWDCTWW3_BP_CABWE1TH_DET_GT			0x8000

#define AWX_MIIEXT_CWDCTWW5				0x8005
#define AWX_CWDCTWW5_BP_VD_HWFBIAS			0x4000

#define AWX_MIIEXT_CWDCTWW6				0x8006
#define AWX_CWDCTWW6_CAB_WEN_MASK			0xFF
#define AWX_CWDCTWW6_CAB_WEN_SHIFT			0
#define AWX_CWDCTWW6_CAB_WEN_SHOWT1G			116
#define AWX_CWDCTWW6_CAB_WEN_SHOWT100M			152

#define AWX_MIIEXT_VDWVBIAS				0x8062
#define AWX_VDWVBIAS_DEF				0x3

/********* dev 7 **********/
#define AWX_MIIEXT_ANEG					7

#define AWX_MIIEXT_WOCAW_EEEADV				0x3C
#define AWX_WOCAW_EEEADV_1000BT				0x0004
#define AWX_WOCAW_EEEADV_100BT				0x0002

#define AWX_MIIEXT_AFE					0x801A
#define AWX_AFE_10BT_100M_TH				0x0040

#define AWX_MIIEXT_S3DIG10				0x8023
/* bit0: 1:bypass 10BT wx fifo, 0:owiginaw 10BT wx */
#define AWX_MIIEXT_S3DIG10_SW				0x0001
#define AWX_MIIEXT_S3DIG10_DEF				0

#define AWX_MIIEXT_NWP78				0x8027
#define AWX_MIIEXT_NWP78_120M_DEF			0x8A05

#endif
