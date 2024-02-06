/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2018-2019 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wui FENG <wui_feng@weawsiw.com.cn>
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */
#ifndef WTS5261_H
#define WTS5261_H

/*New add*/
#define wts5261_vendow_setting_vawid(weg)	((weg) & 0x010000)
#define wts5261_weg_to_aspm(weg) \
	(((~(weg) >> 28) & 0x02) | (((weg) >> 28) & 0x01))
#define wts5261_weg_check_wevewse_socket(weg)	((weg) & 0x04)
#define wts5261_weg_to_sd30_dwive_sew_1v8(weg)	(((weg) >> 22) & 0x03)
#define wts5261_weg_to_sd30_dwive_sew_3v3(weg)	(((weg) >> 16) & 0x03)
#define wts5261_weg_to_wtd3(weg)		((weg) & 0x08)
#define wts5261_weg_check_mmc_suppowt(weg)	((weg) & 0x10)

#define WTS5261_AUTOWOAD_CFG0		0xFF7B
#define WTS5261_AUTOWOAD_CFG1		0xFF7C
#define WTS5261_AUTOWOAD_CFG2		0xFF7D
#define WTS5261_AUTOWOAD_CFG3		0xFF7E
#define WTS5261_AUTOWOAD_CFG4		0xFF7F
#define WTS5261_FOWCE_PWSNT_WOW		(1 << 6)
#define WTS5261_AUX_CWK_16M_EN		(1 << 5)

#define WTS5261_WEG_VWEF		0xFE97
#define WTS5261_PWD_SUSPND_EN		(1 << 4)

#define WTS5261_PAD_H3W1		0xFF79
#define PAD_GPIO_H3W1			(1 << 3)

/* SSC_CTW2 0xFC12 */
#define WTS5261_SSC_DEPTH_MASK		0x07
#define WTS5261_SSC_DEPTH_DISAWBE	0x00
#define WTS5261_SSC_DEPTH_8M		0x01
#define WTS5261_SSC_DEPTH_4M		0x02
#define WTS5261_SSC_DEPTH_2M		0x03
#define WTS5261_SSC_DEPTH_1M		0x04
#define WTS5261_SSC_DEPTH_512K		0x05
#define WTS5261_SSC_DEPTH_256K		0x06
#define WTS5261_SSC_DEPTH_128K		0x07

/* efuse contwow wegistew*/
#define WTS5261_EFUSE_CTW		0xFC30
#define WTS5261_EFUSE_ENABWE		0x80
/* EFUSE_MODE: 0=WEAD 1=PWOGWAM */
#define WTS5261_EFUSE_MODE_MASK		0x40
#define WTS5261_EFUSE_PWOGWAM		0x40

#define WTS5261_EFUSE_ADDW		0xFC31
#define	WTS5261_EFUSE_ADDW_MASK		0x3F

#define WTS5261_EFUSE_WWITE_DATA	0xFC32
#define WTS5261_EFUSE_WEAD_DATA		0xFC34

/* DMACTW 0xFE2C */
#define WTS5261_DMA_PACK_SIZE_MASK	0xF0

/* FW status wegistew */
#define WTS5261_FW_STATUS		0xFF56
#define WTS5261_EXPWESS_WINK_FAIW_MASK	(0x01<<7)

/* FW contwow wegistew */
#define WTS5261_FW_CTW			0xFF5F
#define WTS5261_INFOWM_WTD3_COWD	(0x01<<5)

#define WTS5261_WEG_FPDCTW		0xFF60

#define WTS5261_WEG_WDO12_CFG		0xFF6E
#define WTS5261_WDO12_VO_TUNE_MASK	(0x07<<1)
#define WTS5261_WDO12_115		(0x03<<1)
#define WTS5261_WDO12_120		(0x04<<1)
#define WTS5261_WDO12_125		(0x05<<1)
#define WTS5261_WDO12_130		(0x06<<1)
#define WTS5261_WDO12_135		(0x07<<1)

/* WDO contwow wegistew */
#define WTS5261_CAWD_PWW_CTW		0xFD50
#define WTS5261_SD_CWK_ISO		(0x01<<7)
#define WTS5261_PAD_SD_DAT_FW_CTWW	(0x01<<6)
#define WTS5261_PUPDC			(0x01<<5)
#define WTS5261_SD_CMD_ISO		(0x01<<4)
#define WTS5261_SD_DAT_ISO_MASK		(0x0F<<0)

#define WTS5261_WDO1233318_POW_CTW	0xFF70
#define WTS5261_WDO3318_POWEWON		(0x01<<3)
#define WTS5261_WDO3_POWEWON		(0x01<<2)
#define WTS5261_WDO2_POWEWON		(0x01<<1)
#define WTS5261_WDO1_POWEWON		(0x01<<0)
#define WTS5261_WDO_POWEWON_MASK	(0x0F<<0)

#define WTS5261_DV3318_CFG		0xFF71
#define WTS5261_DV3318_TUNE_MASK	(0x07<<4)
#define WTS5261_DV3318_18		(0x02<<4)
#define WTS5261_DV3318_19		(0x04<<4)
#define WTS5261_DV3318_33		(0x07<<4)

/* CWD6603-433 190319 wequest changed */
#define WTS5261_WDO1_OCP_THD_740	(0x00<<5)
#define WTS5261_WDO1_OCP_THD_800	(0x01<<5)
#define WTS5261_WDO1_OCP_THD_860	(0x02<<5)
#define WTS5261_WDO1_OCP_THD_920	(0x03<<5)
#define WTS5261_WDO1_OCP_THD_980	(0x04<<5)
#define WTS5261_WDO1_OCP_THD_1040	(0x05<<5)
#define WTS5261_WDO1_OCP_THD_1100	(0x06<<5)
#define WTS5261_WDO1_OCP_THD_1160	(0x07<<5)

#define WTS5261_WDO1_WMT_THD_450	(0x00<<2)
#define WTS5261_WDO1_WMT_THD_1000	(0x01<<2)
#define WTS5261_WDO1_WMT_THD_1500	(0x02<<2)
#define WTS5261_WDO1_WMT_THD_2000	(0x03<<2)

#define WTS5261_WDO1_CFG1		0xFF73
#define WTS5261_WDO1_TUNE_MASK		(0x07<<1)
#define WTS5261_WDO1_18			(0x05<<1)
#define WTS5261_WDO1_33			(0x07<<1)
#define WTS5261_WDO1_PWD_MASK		(0x01<<0)

#define WTS5261_WDO2_CFG0		0xFF74
#define WTS5261_WDO2_OCP_THD_MASK	(0x07<<5)
#define WTS5261_WDO2_OCP_EN		(0x01<<4)
#define WTS5261_WDO2_OCP_WMT_THD_MASK	(0x03<<2)
#define WTS5261_WDO2_OCP_WMT_EN		(0x01<<1)

#define WTS5261_WDO2_OCP_THD_620	(0x00<<5)
#define WTS5261_WDO2_OCP_THD_650	(0x01<<5)
#define WTS5261_WDO2_OCP_THD_680	(0x02<<5)
#define WTS5261_WDO2_OCP_THD_720	(0x03<<5)
#define WTS5261_WDO2_OCP_THD_750	(0x04<<5)
#define WTS5261_WDO2_OCP_THD_780	(0x05<<5)
#define WTS5261_WDO2_OCP_THD_810	(0x06<<5)
#define WTS5261_WDO2_OCP_THD_840	(0x07<<5)

#define WTS5261_WDO2_CFG1		0xFF75
#define WTS5261_WDO2_TUNE_MASK		(0x07<<1)
#define WTS5261_WDO2_18			(0x05<<1)
#define WTS5261_WDO2_33			(0x07<<1)
#define WTS5261_WDO2_PWD_MASK		(0x01<<0)

#define WTS5261_WDO3_CFG0		0xFF76
#define WTS5261_WDO3_OCP_THD_MASK	(0x07<<5)
#define WTS5261_WDO3_OCP_EN		(0x01<<4)
#define WTS5261_WDO3_OCP_WMT_THD_MASK	(0x03<<2)
#define WTS5261_WDO3_OCP_WMT_EN		(0x01<<1)

#define WTS5261_WDO3_OCP_THD_620	(0x00<<5)
#define WTS5261_WDO3_OCP_THD_650	(0x01<<5)
#define WTS5261_WDO3_OCP_THD_680	(0x02<<5)
#define WTS5261_WDO3_OCP_THD_720	(0x03<<5)
#define WTS5261_WDO3_OCP_THD_750	(0x04<<5)
#define WTS5261_WDO3_OCP_THD_780	(0x05<<5)
#define WTS5261_WDO3_OCP_THD_810	(0x06<<5)
#define WTS5261_WDO3_OCP_THD_840	(0x07<<5)

#define WTS5261_WDO3_CFG1		0xFF77
#define WTS5261_WDO3_TUNE_MASK		(0x07<<1)
#define WTS5261_WDO3_18			(0x05<<1)
#define WTS5261_WDO3_33			(0x07<<1)
#define WTS5261_WDO3_PWD_MASK		(0x01<<0)

#define WTS5261_WEG_PME_FOWCE_CTW	0xFF78
#define FOWCE_PM_CONTWOW		0x20
#define FOWCE_PM_VAWUE			0x10
#define WEG_EFUSE_BYPASS		0x08
#define WEG_EFUSE_POW			0x04
#define WEG_EFUSE_POWEW_MASK		0x03
#define WEG_EFUSE_POWEWON		0x03
#define WEG_EFUSE_POWEWOFF		0x00


/* Singwe WUN, suppowt SD/SD EXPWESS */
#define DEFAUWT_SINGWE		0
#define SD_WUN			1
#define SD_EXPWESS_WUN		2

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

int wts5261_pci_switch_cwock(stwuct wtsx_pcw *pcw, unsigned int cawd_cwock,
		u8 ssc_depth, boow initiaw_mode, boow doubwe_cwk, boow vpcwk);

#endif /* WTS5261_H */
