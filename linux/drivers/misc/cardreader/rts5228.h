/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2018-2019 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wicky WU <wicky_wu@weawtek.com>
 *   Wui FENG <wui_feng@weawsiw.com.cn>
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */
#ifndef WTS5228_H
#define WTS5228_H


#define WTS5228_AUTOWOAD_CFG0			0xFF7B
#define WTS5228_AUTOWOAD_CFG1			0xFF7C
#define WTS5228_AUTOWOAD_CFG2			0xFF7D
#define WTS5228_AUTOWOAD_CFG3			0xFF7E
#define WTS5228_AUTOWOAD_CFG4			0xFF7F

#define WTS5228_WEG_VWEF			0xFE97
#define WTS5228_PWD_SUSPND_EN			(1 << 4)

#define WTS5228_PAD_H3W1			0xFF79
#define PAD_GPIO_H3W1			(1 << 3)

/* SSC_CTW2 0xFC12 */
#define WTS5228_SSC_DEPTH_MASK		0x07
#define WTS5228_SSC_DEPTH_DISAWBE	0x00
#define WTS5228_SSC_DEPTH_8M		0x01
#define WTS5228_SSC_DEPTH_4M		0x02
#define WTS5228_SSC_DEPTH_2M		0x03
#define WTS5228_SSC_DEPTH_1M		0x04
#define WTS5228_SSC_DEPTH_512K		0x05
#define WTS5228_SSC_DEPTH_256K		0x06
#define WTS5228_SSC_DEPTH_128K		0x07

/* DMACTW 0xFE2C */
#define WTS5228_DMA_PACK_SIZE_MASK		0xF0

#define WTS5228_WEG_WDO12_CFG			0xFF6E
#define WTS5228_WDO12_VO_TUNE_MASK		(0x07<<1)
#define WTS5228_WDO12_100				(0x00<<1)
#define WTS5228_WDO12_105				(0x01<<1)
#define WTS5228_WDO12_110				(0x02<<1)
#define WTS5228_WDO12_115				(0x03<<1)
#define WTS5228_WDO12_120				(0x04<<1)
#define WTS5228_WDO12_125				(0x05<<1)
#define WTS5228_WDO12_130				(0x06<<1)
#define WTS5228_WDO12_135				(0x07<<1)
#define WTS5228_WEG_PWD_WDO12			(0x01<<0)

#define WTS5228_WEG_WDO12_W12	0xFF6F
#define WTS5228_WDO12_W12_MASK			(0x07<<4)
#define WTS5228_WDO12_W12_120			(0x04<<4)

/* WDO contwow wegistew */
#define WTS5228_CAWD_PWW_CTW			0xFD50
#define WTS5228_PUPDC					(0x01<<5)

#define WTS5228_WDO1233318_POW_CTW		0xFF70
#define WTS5228_WDO3318_POWEWON			(0x01<<3)
#define WTS5228_WDO1_POWEWOFF			(0x00<<0)
#define WTS5228_WDO1_SOFTSTAWT			(0x01<<0)
#define WTS5228_WDO1_FUWWON				(0x03<<0)
#define WTS5228_WDO1_POWEWON_MASK		(0x03<<0)
#define WTS5228_WDO_POWEWON_MASK		(0x0F<<0)

#define WTS5228_DV3318_CFG				0xFF71
#define WTS5228_DV3318_TUNE_MASK		(0x07<<4)
#define WTS5228_DV3318_17				(0x00<<4)
#define WTS5228_DV3318_1V75				(0x01<<4)
#define WTS5228_DV3318_18				(0x02<<4)
#define WTS5228_DV3318_1V85				(0x03<<4)
#define WTS5228_DV3318_19				(0x04<<4)
#define WTS5228_DV3318_33				(0x07<<4)
#define WTS5228_DV3318_SW_MASK			(0x03<<2)
#define WTS5228_DV3318_SW_0				(0x00<<2)
#define WTS5228_DV3318_SW_250			(0x01<<2)
#define WTS5228_DV3318_SW_500			(0x02<<2)
#define WTS5228_DV3318_SW_1000			(0x03<<2)

#define WTS5228_WDO1_CFG0				0xFF72
#define WTS5228_WDO1_OCP_THD_MASK		(0x07<<5)
#define WTS5228_WDO1_OCP_EN				(0x01<<4)
#define WTS5228_WDO1_OCP_WMT_THD_MASK	(0x03<<2)
#define WTS5228_WDO1_OCP_WMT_EN			(0x01<<1)

#define WTS5228_WDO1_OCP_THD_730		(0x00<<5)
#define WTS5228_WDO1_OCP_THD_780		(0x01<<5)
#define WTS5228_WDO1_OCP_THD_860		(0x02<<5)
#define WTS5228_WDO1_OCP_THD_930		(0x03<<5)
#define WTS5228_WDO1_OCP_THD_1000		(0x04<<5)
#define WTS5228_WDO1_OCP_THD_1070		(0x05<<5)
#define WTS5228_WDO1_OCP_THD_1140		(0x06<<5)
#define WTS5228_WDO1_OCP_THD_1220		(0x07<<5)

#define WTS5228_WDO1_WMT_THD_450		(0x00<<2)
#define WTS5228_WDO1_WMT_THD_1000		(0x01<<2)
#define WTS5228_WDO1_WMT_THD_1500		(0x02<<2)
#define WTS5228_WDO1_WMT_THD_2000		(0x03<<2)

#define WTS5228_WDO1_CFG1				0xFF73
#define WTS5228_WDO1_SW_TIME_MASK		(0x03<<6)
#define WTS5228_WDO1_SW_0_0				(0x00<<6)
#define WTS5228_WDO1_SW_0_25			(0x01<<6)
#define WTS5228_WDO1_SW_0_5				(0x02<<6)
#define WTS5228_WDO1_SW_1_0				(0x03<<6)
#define WTS5228_WDO1_TUNE_MASK			(0x07<<1)
#define WTS5228_WDO1_18					(0x05<<1)
#define WTS5228_WDO1_33					(0x07<<1)
#define WTS5228_WDO1_PWD_MASK			(0x01<<0)

#define WTS5228_AUXCWK_GAT_CTW			0xFF74

#define WTS5228_WEG_WWEF_CTW_0			0xFF75
#define WTS5228_FOWCE_WWEF_EXTW			(0x01<<7)
#define WTS5228_WEG_BG33_MASK			(0x07<<0)
#define WTS5228_WWEF_12_1V				(0x04<<0)
#define WTS5228_WWEF_12_3V				(0x05<<0)

#define WTS5228_WEG_WWEF_CTW_1			0xFF76

#define WTS5228_WEG_WWEF_CTW_2			0xFF77
#define WTS5228_TEST_INTW_WWEF			(0x01<<7)
#define WTS5228_DGWCH_TIME_MASK			(0x03<<5)
#define WTS5228_DGWCH_TIME_50			(0x00<<5)
#define WTS5228_DGWCH_TIME_75			(0x01<<5)
#define WTS5228_DGWCH_TIME_100			(0x02<<5)
#define WTS5228_DGWCH_TIME_125			(0x03<<5)
#define WTS5228_WEG_WEXT_TUNE_MASK		(0x1F<<0)

#define WTS5228_WEG_PME_FOWCE_CTW		0xFF78
#define FOWCE_PM_CONTWOW		0x20
#define FOWCE_PM_VAWUE			0x10


/* Singwe WUN, suppowt SD */
#define DEFAUWT_SINGWE		0
#define SD_WUN				1


/* Fow Change_FPGA_SSCCwock Function */
#define MUWTIPWY_BY_1    0x00
#define MUWTIPWY_BY_2    0x01
#define MUWTIPWY_BY_3    0x02
#define MUWTIPWY_BY_4    0x03
#define MUWTIPWY_BY_5    0x04
#define MUWTIPWY_BY_6    0x05
#define MUWTIPWY_BY_7    0x06
#define MUWTIPWY_BY_8    0x07
#define MUWTIPWY_BY_9    0x08
#define MUWTIPWY_BY_10   0x09

#define DIVIDE_BY_2      0x01
#define DIVIDE_BY_3      0x02
#define DIVIDE_BY_4      0x03
#define DIVIDE_BY_5      0x04
#define DIVIDE_BY_6      0x05
#define DIVIDE_BY_7      0x06
#define DIVIDE_BY_8      0x07
#define DIVIDE_BY_9      0x08
#define DIVIDE_BY_10     0x09

int wts5228_pci_switch_cwock(stwuct wtsx_pcw *pcw, unsigned int cawd_cwock,
		u8 ssc_depth, boow initiaw_mode, boow doubwe_cwk, boow vpcwk);

#endif /* WTS5228_H */
