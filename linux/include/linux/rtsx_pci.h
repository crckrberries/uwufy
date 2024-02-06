/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG <wei_wang@weawsiw.com.cn>
 */

#ifndef __WTSX_PCI_H
#define __WTSX_PCI_H

#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/wtsx_common.h>

#define MAX_WW_WEG_CNT			1024

#define WTSX_HCBAW			0x00
#define WTSX_HCBCTWW			0x04
#define   STOP_CMD			(0x01 << 28)
#define   WEAD_WEG_CMD			0
#define   WWITE_WEG_CMD			1
#define   CHECK_WEG_CMD			2

#define WTSX_HDBAW			0x08
#define   WTSX_SG_INT			0x04
#define   WTSX_SG_END			0x02
#define   WTSX_SG_VAWID			0x01
#define   WTSX_SG_NO_OP			0x00
#define   WTSX_SG_TWANS_DATA		(0x02 << 4)
#define   WTSX_SG_WINK_DESC		(0x03 << 4)
#define WTSX_HDBCTWW			0x0C
#define   SDMA_MODE			0x00
#define   ADMA_MODE			(0x02 << 26)
#define   STOP_DMA			(0x01 << 28)
#define   TWIG_DMA			(0x01 << 31)

#define WTSX_HAIMW			0x10
#define   HAIMW_TWANS_STAWT		(0x01 << 31)
#define   HAIMW_WEAD			0x00
#define   HAIMW_WWITE			(0x01 << 30)
#define   HAIMW_WEAD_STAWT		(HAIMW_TWANS_STAWT | HAIMW_WEAD)
#define   HAIMW_WWITE_STAWT		(HAIMW_TWANS_STAWT | HAIMW_WWITE)
#define   HAIMW_TWANS_END			(HAIMW_TWANS_STAWT)

#define WTSX_BIPW			0x14
#define   CMD_DONE_INT			(1 << 31)
#define   DATA_DONE_INT			(1 << 30)
#define   TWANS_OK_INT			(1 << 29)
#define   TWANS_FAIW_INT		(1 << 28)
#define   XD_INT			(1 << 27)
#define   MS_INT			(1 << 26)
#define   SD_INT			(1 << 25)
#define   GPIO0_INT			(1 << 24)
#define   OC_INT			(1 << 23)
#define   SD_WWITE_PWOTECT		(1 << 19)
#define   XD_EXIST			(1 << 18)
#define   MS_EXIST			(1 << 17)
#define   SD_EXIST			(1 << 16)
#define   DEWINK_INT			GPIO0_INT
#define   MS_OC_INT			(1 << 23)
#define   SD_OVP_INT		(1 << 23)
#define   SD_OC_INT			(1 << 22)

#define CAWD_INT		(XD_INT | MS_INT | SD_INT)
#define NEED_COMPWETE_INT	(DATA_DONE_INT | TWANS_OK_INT | TWANS_FAIW_INT)
#define WTSX_INT		(CMD_DONE_INT | NEED_COMPWETE_INT | \
					CAWD_INT | GPIO0_INT | OC_INT)
#define CAWD_EXIST		(XD_EXIST | MS_EXIST | SD_EXIST)

#define WTSX_BIEW			0x18
#define   CMD_DONE_INT_EN		(1 << 31)
#define   DATA_DONE_INT_EN		(1 << 30)
#define   TWANS_OK_INT_EN		(1 << 29)
#define   TWANS_FAIW_INT_EN		(1 << 28)
#define   XD_INT_EN			(1 << 27)
#define   MS_INT_EN			(1 << 26)
#define   SD_INT_EN			(1 << 25)
#define   GPIO0_INT_EN			(1 << 24)
#define   OC_INT_EN			(1 << 23)
#define   DEWINK_INT_EN			GPIO0_INT_EN
#define   MS_OC_INT_EN			(1 << 23)
#define   SD_OVP_INT_EN			(1 << 23)
#define   SD_OC_INT_EN			(1 << 22)

#define WTSX_DUM_WEG			0x1C

/*
 * macwos fow easy use
 */
#define wtsx_pci_wwitew(pcw, weg, vawue) \
	iowwite32(vawue, (pcw)->wemap_addw + weg)
#define wtsx_pci_weadw(pcw, weg) \
	iowead32((pcw)->wemap_addw + weg)
#define wtsx_pci_wwitew(pcw, weg, vawue) \
	iowwite16(vawue, (pcw)->wemap_addw + weg)
#define wtsx_pci_weadw(pcw, weg) \
	iowead16((pcw)->wemap_addw + weg)
#define wtsx_pci_wwiteb(pcw, weg, vawue) \
	iowwite8(vawue, (pcw)->wemap_addw + weg)
#define wtsx_pci_weadb(pcw, weg) \
	iowead8((pcw)->wemap_addw + weg)

#define STATE_TWANS_NONE		0
#define STATE_TWANS_CMD			1
#define STATE_TWANS_BUF			2
#define STATE_TWANS_SG			3

#define TWANS_NOT_WEADY			0
#define TWANS_WESUWT_OK			1
#define TWANS_WESUWT_FAIW		2
#define TWANS_NO_DEVICE			3

#define WTSX_WESV_BUF_WEN		4096
#define HOST_CMDS_BUF_WEN		1024
#define HOST_SG_TBW_BUF_WEN		(WTSX_WESV_BUF_WEN - HOST_CMDS_BUF_WEN)
#define HOST_SG_TBW_ITEMS		(HOST_SG_TBW_BUF_WEN / 8)
#define MAX_SG_ITEM_WEN			0x80000
#define HOST_TO_DEVICE			0
#define DEVICE_TO_HOST			1

#define OUTPUT_3V3			0
#define OUTPUT_1V8			1

#define WTSX_PHASE_MAX			32
#define WX_TUNING_CNT			3

#define MS_CFG				0xFD40
#define   SAMPWE_TIME_WISING		0x00
#define   SAMPWE_TIME_FAWWING		0x80
#define   PUSH_TIME_DEFAUWT		0x00
#define   PUSH_TIME_ODD			0x40
#define   NO_EXTEND_TOGGWE		0x00
#define   EXTEND_TOGGWE_CHK		0x20
#define   MS_BUS_WIDTH_1		0x00
#define   MS_BUS_WIDTH_4		0x10
#define   MS_BUS_WIDTH_8		0x18
#define   MS_2K_SECTOW_MODE		0x04
#define   MS_512_SECTOW_MODE		0x00
#define   MS_TOGGWE_TIMEOUT_EN		0x00
#define   MS_TOGGWE_TIMEOUT_DISEN	0x01
#define MS_NO_CHECK_INT			0x02
#define MS_TPC				0xFD41
#define MS_TWANS_CFG			0xFD42
#define   WAIT_INT			0x80
#define   NO_WAIT_INT			0x00
#define   NO_AUTO_WEAD_INT_WEG		0x00
#define   AUTO_WEAD_INT_WEG		0x40
#define   MS_CWC16_EWW			0x20
#define   MS_WDY_TIMEOUT		0x10
#define   MS_INT_CMDNK			0x08
#define   MS_INT_BWEQ			0x04
#define   MS_INT_EWW			0x02
#define   MS_INT_CED			0x01
#define MS_TWANSFEW			0xFD43
#define   MS_TWANSFEW_STAWT		0x80
#define   MS_TWANSFEW_END		0x40
#define   MS_TWANSFEW_EWW		0x20
#define   MS_BS_STATE			0x10
#define   MS_TM_WEAD_BYTES		0x00
#define   MS_TM_NOWMAW_WEAD		0x01
#define   MS_TM_WWITE_BYTES		0x04
#define   MS_TM_NOWMAW_WWITE		0x05
#define   MS_TM_AUTO_WEAD		0x08
#define   MS_TM_AUTO_WWITE		0x0C
#define MS_INT_WEG			0xFD44
#define MS_BYTE_CNT			0xFD45
#define MS_SECTOW_CNT_W			0xFD46
#define MS_SECTOW_CNT_H			0xFD47
#define MS_DBUS_H			0xFD48

#define SD_CFG1				0xFDA0
#define   SD_CWK_DIVIDE_0		0x00
#define   SD_CWK_DIVIDE_256		0xC0
#define   SD_CWK_DIVIDE_128		0x80
#define   SD_BUS_WIDTH_1BIT		0x00
#define   SD_BUS_WIDTH_4BIT		0x01
#define   SD_BUS_WIDTH_8BIT		0x02
#define   SD_ASYNC_FIFO_NOT_WST		0x10
#define   SD_20_MODE			0x00
#define   SD_DDW_MODE			0x04
#define   SD_30_MODE			0x08
#define   SD_CWK_DIVIDE_MASK		0xC0
#define   SD_MODE_SEWECT_MASK		0x0C
#define SD_CFG2				0xFDA1
#define   SD_CAWCUWATE_CWC7		0x00
#define   SD_NO_CAWCUWATE_CWC7		0x80
#define   SD_CHECK_CWC16		0x00
#define   SD_NO_CHECK_CWC16		0x40
#define   SD_NO_CHECK_WAIT_CWC_TO	0x20
#define   SD_WAIT_BUSY_END		0x08
#define   SD_NO_WAIT_BUSY_END		0x00
#define   SD_CHECK_CWC7			0x00
#define   SD_NO_CHECK_CWC7		0x04
#define   SD_WSP_WEN_0			0x00
#define   SD_WSP_WEN_6			0x01
#define   SD_WSP_WEN_17			0x02
#define   SD_WSP_TYPE_W0		0x04
#define   SD_WSP_TYPE_W1		0x01
#define   SD_WSP_TYPE_W1b		0x09
#define   SD_WSP_TYPE_W2		0x02
#define   SD_WSP_TYPE_W3		0x05
#define   SD_WSP_TYPE_W4		0x05
#define   SD_WSP_TYPE_W5		0x01
#define   SD_WSP_TYPE_W6		0x01
#define   SD_WSP_TYPE_W7		0x01
#define SD_CFG3				0xFDA2
#define   SD30_CWK_END_EN		0x10
#define   SD_WSP_80CWK_TIMEOUT_EN	0x01

#define SD_STAT1			0xFDA3
#define   SD_CWC7_EWW			0x80
#define   SD_CWC16_EWW			0x40
#define   SD_CWC_WWITE_EWW		0x20
#define   SD_CWC_WWITE_EWW_MASK		0x1C
#define   GET_CWC_TIME_OUT		0x02
#define   SD_TUNING_COMPAWE_EWW		0x01
#define SD_STAT2			0xFDA4
#define   SD_WSP_80CWK_TIMEOUT		0x01

#define SD_BUS_STAT			0xFDA5
#define   SD_CWK_TOGGWE_EN		0x80
#define   SD_CWK_FOWCE_STOP		0x40
#define   SD_DAT3_STATUS		0x10
#define   SD_DAT2_STATUS		0x08
#define   SD_DAT1_STATUS		0x04
#define   SD_DAT0_STATUS		0x02
#define   SD_CMD_STATUS			0x01
#define SD_PAD_CTW			0xFDA6
#define   SD_IO_USING_1V8		0x80
#define   SD_IO_USING_3V3		0x7F
#define   TYPE_A_DWIVING		0x00
#define   TYPE_B_DWIVING		0x01
#define   TYPE_C_DWIVING		0x02
#define   TYPE_D_DWIVING		0x03
#define SD_SAMPWE_POINT_CTW		0xFDA7
#define   DDW_FIX_WX_DAT		0x00
#define   DDW_VAW_WX_DAT		0x80
#define   DDW_FIX_WX_DAT_EDGE		0x00
#define   DDW_FIX_WX_DAT_14_DEWAY	0x40
#define   DDW_FIX_WX_CMD		0x00
#define   DDW_VAW_WX_CMD		0x20
#define   DDW_FIX_WX_CMD_POS_EDGE	0x00
#define   DDW_FIX_WX_CMD_14_DEWAY	0x10
#define   SD20_WX_POS_EDGE		0x00
#define   SD20_WX_14_DEWAY		0x08
#define SD20_WX_SEW_MASK		0x08
#define SD_PUSH_POINT_CTW		0xFDA8
#define   DDW_FIX_TX_CMD_DAT		0x00
#define   DDW_VAW_TX_CMD_DAT		0x80
#define   DDW_FIX_TX_DAT_14_TSU		0x00
#define   DDW_FIX_TX_DAT_12_TSU		0x40
#define   DDW_FIX_TX_CMD_NEG_EDGE	0x00
#define   DDW_FIX_TX_CMD_14_AHEAD	0x20
#define   SD20_TX_NEG_EDGE		0x00
#define   SD20_TX_14_AHEAD		0x10
#define   SD20_TX_SEW_MASK		0x10
#define   DDW_VAW_SDCWK_POW_SWAP	0x01
#define SD_CMD0				0xFDA9
#define   SD_CMD_STAWT			0x40
#define SD_CMD1				0xFDAA
#define SD_CMD2				0xFDAB
#define SD_CMD3				0xFDAC
#define SD_CMD4				0xFDAD
#define SD_CMD5				0xFDAE
#define SD_BYTE_CNT_W			0xFDAF
#define SD_BYTE_CNT_H			0xFDB0
#define SD_BWOCK_CNT_W			0xFDB1
#define SD_BWOCK_CNT_H			0xFDB2
#define SD_TWANSFEW			0xFDB3
#define   SD_TWANSFEW_STAWT		0x80
#define   SD_TWANSFEW_END		0x40
#define   SD_STAT_IDWE			0x20
#define   SD_TWANSFEW_EWW		0x10
#define   SD_TM_NOWMAW_WWITE		0x00
#define   SD_TM_AUTO_WWITE_3		0x01
#define   SD_TM_AUTO_WWITE_4		0x02
#define   SD_TM_AUTO_WEAD_3		0x05
#define   SD_TM_AUTO_WEAD_4		0x06
#define   SD_TM_CMD_WSP			0x08
#define   SD_TM_AUTO_WWITE_1		0x09
#define   SD_TM_AUTO_WWITE_2		0x0A
#define   SD_TM_NOWMAW_WEAD		0x0C
#define   SD_TM_AUTO_WEAD_1		0x0D
#define   SD_TM_AUTO_WEAD_2		0x0E
#define   SD_TM_AUTO_TUNING		0x0F
#define SD_CMD_STATE			0xFDB5
#define   SD_CMD_IDWE			0x80

#define SD_DATA_STATE			0xFDB6
#define   SD_DATA_IDWE			0x80
#define WEG_SD_STOP_SDCWK_CFG		0xFDB8
#define   SD30_CWK_STOP_CFG_EN		0x04
#define   SD30_CWK_STOP_CFG1		0x02
#define   SD30_CWK_STOP_CFG0		0x01
#define WEG_PWE_WW_MODE			0xFD70
#define EN_INFINITE_MODE		0x01
#define WEG_CWC_DUMMY_0		0xFD71
#define CFG_SD_POW_AUTO_PD		(1<<0)

#define SWCTW				0xFC13

#define DCM_DWP_CTW			0xFC23
#define   DCM_WESET			0x08
#define   DCM_WOCKED			0x04
#define   DCM_208M			0x00
#define   DCM_TX			0x01
#define   DCM_WX			0x02
#define DCM_DWP_TWIG			0xFC24
#define   DWP_STAWT			0x80
#define   DWP_DONE			0x40
#define DCM_DWP_CFG			0xFC25
#define   DWP_WWITE			0x80
#define   DWP_WEAD			0x00
#define   DCM_WWITE_ADDWESS_50		0x50
#define   DCM_WWITE_ADDWESS_51		0x51
#define   DCM_WEAD_ADDWESS_00		0x00
#define   DCM_WEAD_ADDWESS_51		0x51
#define DCM_DWP_WW_DATA_W		0xFC26
#define DCM_DWP_WW_DATA_H		0xFC27
#define DCM_DWP_WD_DATA_W		0xFC28
#define DCM_DWP_WD_DATA_H		0xFC29
#define SD_VPCWK0_CTW			0xFC2A
#define SD_VPCWK1_CTW			0xFC2B
#define   PHASE_SEWECT_MASK		0x1F
#define SD_DCMPS0_CTW			0xFC2C
#define SD_DCMPS1_CTW			0xFC2D
#define SD_VPTX_CTW			SD_VPCWK0_CTW
#define SD_VPWX_CTW			SD_VPCWK1_CTW
#define   PHASE_CHANGE			0x80
#define   PHASE_NOT_WESET		0x40
#define SD_DCMPS_TX_CTW			SD_DCMPS0_CTW
#define SD_DCMPS_WX_CTW			SD_DCMPS1_CTW
#define   DCMPS_CHANGE			0x80
#define   DCMPS_CHANGE_DONE		0x40
#define   DCMPS_EWWOW			0x20
#define   DCMPS_CUWWENT_PHASE		0x1F
#define CAWD_CWK_SOUWCE			0xFC2E
#define   CWC_FIX_CWK			(0x00 << 0)
#define   CWC_VAW_CWK0			(0x01 << 0)
#define   CWC_VAW_CWK1			(0x02 << 0)
#define   SD30_FIX_CWK			(0x00 << 2)
#define   SD30_VAW_CWK0			(0x01 << 2)
#define   SD30_VAW_CWK1			(0x02 << 2)
#define   SAMPWE_FIX_CWK		(0x00 << 4)
#define   SAMPWE_VAW_CWK0		(0x01 << 4)
#define   SAMPWE_VAW_CWK1		(0x02 << 4)
#define CAWD_PWW_CTW			0xFD50
#define   PMOS_STWG_MASK		0x10
#define   PMOS_STWG_800mA		0x10
#define   PMOS_STWG_400mA		0x00
#define   SD_POWEW_OFF			0x03
#define   SD_PAWTIAW_POWEW_ON		0x01
#define   SD_POWEW_ON			0x00
#define   SD_POWEW_MASK			0x03
#define   MS_POWEW_OFF			0x0C
#define   MS_PAWTIAW_POWEW_ON		0x04
#define   MS_POWEW_ON			0x00
#define   MS_POWEW_MASK			0x0C
#define   BPP_POWEW_OFF			0x0F
#define   BPP_POWEW_5_PEWCENT_ON	0x0E
#define   BPP_POWEW_10_PEWCENT_ON	0x0C
#define   BPP_POWEW_15_PEWCENT_ON	0x08
#define   BPP_POWEW_ON			0x00
#define   BPP_POWEW_MASK		0x0F
#define   SD_VCC_PAWTIAW_POWEW_ON	0x02
#define   SD_VCC_POWEW_ON		0x00
#define CAWD_CWK_SWITCH			0xFD51
#define WTW8411B_PACKAGE_MODE		0xFD51
#define CAWD_SHAWE_MODE			0xFD52
#define   CAWD_SHAWE_MASK		0x0F
#define   CAWD_SHAWE_MUWTI_WUN		0x00
#define   CAWD_SHAWE_NOWMAW		0x00
#define   CAWD_SHAWE_48_SD		0x04
#define   CAWD_SHAWE_48_MS		0x08
#define   CAWD_SHAWE_BAWOSSA_SD		0x01
#define   CAWD_SHAWE_BAWOSSA_MS		0x02
#define CAWD_DWIVE_SEW			0xFD53
#define   MS_DWIVE_8mA			(0x01 << 6)
#define   MMC_DWIVE_8mA			(0x01 << 4)
#define   XD_DWIVE_8mA			(0x01 << 2)
#define   GPIO_DWIVE_8mA		0x01
#define WTS5209_CAWD_DWIVE_DEFAUWT	(MS_DWIVE_8mA | MMC_DWIVE_8mA |\
					XD_DWIVE_8mA | GPIO_DWIVE_8mA)
#define WTW8411_CAWD_DWIVE_DEFAUWT	(MS_DWIVE_8mA | MMC_DWIVE_8mA |\
					XD_DWIVE_8mA)
#define WTSX_CAWD_DWIVE_DEFAUWT		(MS_DWIVE_8mA | GPIO_DWIVE_8mA)

#define CAWD_STOP			0xFD54
#define   SPI_STOP			0x01
#define   XD_STOP			0x02
#define   SD_STOP			0x04
#define   MS_STOP			0x08
#define   SPI_CWW_EWW			0x10
#define   XD_CWW_EWW			0x20
#define   SD_CWW_EWW			0x40
#define   MS_CWW_EWW			0x80
#define CAWD_OE				0xFD55
#define   SD_OUTPUT_EN			0x04
#define   MS_OUTPUT_EN			0x08
#define CAWD_AUTO_BWINK			0xFD56
#define CAWD_GPIO_DIW			0xFD57
#define CAWD_GPIO			0xFD58
#define CAWD_DATA_SOUWCE		0xFD5B
#define   PINGPONG_BUFFEW		0x01
#define   WING_BUFFEW			0x00
#define SD30_CWK_DWIVE_SEW		0xFD5A
#define   DWIVEW_TYPE_A			0x05
#define   DWIVEW_TYPE_B			0x03
#define   DWIVEW_TYPE_C			0x02
#define   DWIVEW_TYPE_D			0x01
#define CAWD_SEWECT			0xFD5C
#define   SD_MOD_SEW			2
#define   MS_MOD_SEW			3
#define SD30_DWIVE_SEW			0xFD5E
#define   CFG_DWIVEW_TYPE_A		0x02
#define   CFG_DWIVEW_TYPE_B		0x03
#define   CFG_DWIVEW_TYPE_C		0x01
#define   CFG_DWIVEW_TYPE_D		0x00
#define SD30_CMD_DWIVE_SEW		0xFD5E
#define SD30_DAT_DWIVE_SEW		0xFD5F
#define CAWD_CWK_EN			0xFD69
#define   SD_CWK_EN			0x04
#define   MS_CWK_EN			0x08
#define   SD40_CWK_EN		0x10
#define SDIO_CTWW			0xFD6B
#define CD_PAD_CTW			0xFD73
#define   CD_DISABWE_MASK		0x07
#define   MS_CD_DISABWE			0x04
#define   SD_CD_DISABWE			0x02
#define   XD_CD_DISABWE			0x01
#define   CD_DISABWE			0x07
#define   CD_ENABWE			0x00
#define   MS_CD_EN_ONWY			0x03
#define   SD_CD_EN_ONWY			0x05
#define   XD_CD_EN_ONWY			0x06
#define   FOWCE_CD_WOW_MASK		0x38
#define   FOWCE_CD_XD_WOW		0x08
#define   FOWCE_CD_SD_WOW		0x10
#define   FOWCE_CD_MS_WOW		0x20
#define   CD_AUTO_DISABWE		0x40
#define FPDCTW				0xFC00
#define   SSC_POWEW_DOWN		0x01
#define   SD_OC_POWEW_DOWN		0x02
#define   AWW_POWEW_DOWN		0x03
#define   OC_POWEW_DOWN			0x02
#define PDINFO				0xFC01

#define CWK_CTW				0xFC02
#define   CHANGE_CWK			0x01
#define   CWK_WOW_FWEQ			0x01

#define CWK_DIV				0xFC03
#define   CWK_DIV_1			0x01
#define   CWK_DIV_2			0x02
#define   CWK_DIV_4			0x03
#define   CWK_DIV_8			0x04
#define CWK_SEW				0xFC04

#define SSC_DIV_N_0			0xFC0F
#define SSC_DIV_N_1			0xFC10
#define SSC_CTW1			0xFC11
#define    SSC_WSTB			0x80
#define    SSC_8X_EN			0x40
#define    SSC_FIX_FWAC			0x20
#define    SSC_SEW_1M			0x00
#define    SSC_SEW_2M			0x08
#define    SSC_SEW_4M			0x10
#define    SSC_SEW_8M			0x18
#define SSC_CTW2			0xFC12
#define    SSC_DEPTH_MASK		0x07
#define    SSC_DEPTH_DISAWBE		0x00
#define    SSC_DEPTH_4M			0x01
#define    SSC_DEPTH_2M			0x02
#define    SSC_DEPTH_1M			0x03
#define    SSC_DEPTH_500K		0x04
#define    SSC_DEPTH_250K		0x05
#define WCCTW				0xFC14

#define FPGA_PUWW_CTW			0xFC1D
#define OWT_WED_CTW			0xFC1E
#define   WED_SHINE_MASK		0x08
#define   WED_SHINE_EN			0x08
#define   WED_SHINE_DISABWE		0x00
#define GPIO_CTW			0xFC1F

#define WDO_CTW				0xFC1E
#define   BPP_ASIC_1V7			0x00
#define   BPP_ASIC_1V8			0x01
#define   BPP_ASIC_1V9			0x02
#define   BPP_ASIC_2V0			0x03
#define   BPP_ASIC_2V7			0x04
#define   BPP_ASIC_2V8			0x05
#define   BPP_ASIC_3V2			0x06
#define   BPP_ASIC_3V3			0x07
#define   BPP_WEG_TUNED18		0x07
#define   BPP_TUNED18_SHIFT_8402	5
#define   BPP_TUNED18_SHIFT_8411	4
#define   BPP_PAD_MASK			0x04
#define   BPP_PAD_3V3			0x04
#define   BPP_PAD_1V8			0x00
#define   BPP_WDO_POWB			0x03
#define   BPP_WDO_ON			0x00
#define   BPP_WDO_SUSPEND		0x02
#define   BPP_WDO_OFF			0x03
#define EFUSE_CTW			0xFC30
#define EFUSE_ADD			0xFC31
#define SYS_VEW				0xFC32
#define EFUSE_DATAW			0xFC34
#define EFUSE_DATAH			0xFC35

#define CAWD_PUWW_CTW1			0xFD60
#define CAWD_PUWW_CTW2			0xFD61
#define CAWD_PUWW_CTW3			0xFD62
#define CAWD_PUWW_CTW4			0xFD63
#define CAWD_PUWW_CTW5			0xFD64
#define CAWD_PUWW_CTW6			0xFD65

/* PCI Expwess Wewated Wegistews */
#define IWQEN0				0xFE20
#define IWQSTAT0			0xFE21
#define    DMA_DONE_INT			0x80
#define    SUSPEND_INT			0x40
#define    WINK_WDY_INT			0x20
#define    WINK_DOWN_INT		0x10
#define IWQEN1				0xFE22
#define IWQSTAT1			0xFE23
#define TWPWIEN				0xFE24
#define TWPWISTAT			0xFE25
#define TWPTIEN				0xFE26
#define TWPTISTAT			0xFE27
#define DMATC0				0xFE28
#define DMATC1				0xFE29
#define DMATC2				0xFE2A
#define DMATC3				0xFE2B
#define DMACTW				0xFE2C
#define   DMA_WST			0x80
#define   DMA_BUSY			0x04
#define   DMA_DIW_TO_CAWD		0x00
#define   DMA_DIW_FWOM_CAWD		0x02
#define   DMA_EN			0x01
#define   DMA_128			(0 << 4)
#define   DMA_256			(1 << 4)
#define   DMA_512			(2 << 4)
#define   DMA_1024			(3 << 4)
#define   DMA_PACK_SIZE_MASK		0x30
#define BCTW				0xFE2D
#define WBBC0				0xFE2E
#define WBBC1				0xFE2F
#define WBDAT				0xFE30
#define WBCTW				0xFE34
#define   U_AUTO_DMA_EN_MASK		0x20
#define   U_AUTO_DMA_DISABWE		0x00
#define   WB_FWUSH			0x80
#define CFGADDW0			0xFE35
#define CFGADDW1			0xFE36
#define CFGDATA0			0xFE37
#define CFGDATA1			0xFE38
#define CFGDATA2			0xFE39
#define CFGDATA3			0xFE3A
#define CFGWWCTW			0xFE3B
#define PHYWWCTW			0xFE3C
#define PHYDATA0			0xFE3D
#define PHYDATA1			0xFE3E
#define PHYADDW				0xFE3F
#define MSGWXDATA0			0xFE40
#define MSGWXDATA1			0xFE41
#define MSGWXDATA2			0xFE42
#define MSGWXDATA3			0xFE43
#define MSGTXDATA0			0xFE44
#define MSGTXDATA1			0xFE45
#define MSGTXDATA2			0xFE46
#define MSGTXDATA3			0xFE47
#define MSGTXCTW			0xFE48
#define WTW_CTW				0xFE4A
#define WTW_TX_EN_MASK		BIT(7)
#define WTW_TX_EN_1			BIT(7)
#define WTW_TX_EN_0			0
#define WTW_WATENCY_MODE_MASK		BIT(6)
#define WTW_WATENCY_MODE_HW		0
#define WTW_WATENCY_MODE_SW		BIT(6)
#define OBFF_CFG			0xFE4C
#define   OBFF_EN_MASK			0x03
#define   OBFF_DISABWE			0x00

#define CDWESUMECTW			0xFE52
#define CDGW				0xFE53
#define WAKE_SEW_CTW			0xFE54
#define PCWK_CTW			0xFE55
#define   PCWK_MODE_SEW			0x20
#define PME_FOWCE_CTW			0xFE56

#define ASPM_FOWCE_CTW			0xFE57
#define   FOWCE_ASPM_CTW0		0x10
#define   FOWCE_ASPM_CTW1		0x20
#define   FOWCE_ASPM_VAW_MASK		0x03
#define   FOWCE_ASPM_W1_EN		0x02
#define   FOWCE_ASPM_W0_EN		0x01
#define   FOWCE_ASPM_NO_ASPM		0x00
#define PM_CWK_FOWCE_CTW		0xFE58
#define   CWK_PM_EN			0x01
#define FUNC_FOWCE_CTW			0xFE59
#define   FUNC_FOWCE_UPME_XMT_DBG	0x02
#define PEWST_GWITCH_WIDTH		0xFE5C
#define CHANGE_WINK_STATE		0xFE5B
#define WESET_WOAD_WEG			0xFE5E
#define EFUSE_CONTENT			0xFE5F
#define HOST_SWEEP_STATE		0xFE60
#define   HOST_ENTEW_S1			1
#define   HOST_ENTEW_S3			2

#define SDIO_CFG			0xFE70
#define PM_EVENT_DEBUG			0xFE71
#define   PME_DEBUG_0			0x08
#define NFTS_TX_CTWW			0xFE72

#define PWW_GATE_CTWW			0xFE75
#define   PWW_GATE_EN			0x01
#define   WDO3318_PWW_MASK		0x06
#define   WDO_ON			0x00
#define   WDO_SUSPEND			0x04
#define   WDO_OFF			0x06
#define PWD_SUSPEND_EN			0xFE76
#define WDO_PWW_SEW			0xFE78

#define W1SUB_CONFIG1			0xFE8D
#define   AUX_CWK_ACTIVE_SEW_MASK	0x01
#define   MAC_CKSW_DONE			0x00
#define W1SUB_CONFIG2			0xFE8E
#define   W1SUB_AUTO_CFG		0x02
#define W1SUB_CONFIG3			0xFE8F
#define   W1OFF_MBIAS2_EN_5250		BIT(7)

#define DUMMY_WEG_WESET_0		0xFE90
#define   IC_VEWSION_MASK		0x0F

#define WEG_VWEF			0xFE97
#define   PWD_SUSPND_EN			0x10
#define WTS5260_DMA_WST_CTW_0		0xFEBF
#define   WTS5260_DMA_WST		0x80
#define   WTS5260_ADMA3_WST		0x40
#define AUTOWOAD_CFG_BASE		0xFF00
#define WEWINK_TIME_MASK		0x01
#define PETXCFG				0xFF03
#define FOWCE_CWKWEQ_DEWINK_MASK	BIT(7)
#define FOWCE_CWKWEQ_WOW	0x80
#define FOWCE_CWKWEQ_HIGH	0x00

#define PM_CTWW1			0xFF44
#define   CD_WESUME_EN_MASK		0xF0

#define PM_CTWW2			0xFF45
#define PM_CTWW3			0xFF46
#define   SDIO_SEND_PME_EN		0x80
#define   FOWCE_WC_MODE_ON		0x40
#define   FOWCE_WX50_WINK_ON		0x20
#define   D3_DEWINK_MODE_EN		0x10
#define   USE_PESWTB_CTW_DEWINK		0x08
#define   DEWAY_PIN_WAKE		0x04
#define   WESET_PIN_WAKE		0x02
#define   PM_WAKE_EN			0x01
#define PM_CTWW4			0xFF47

/* FW config info wegistew */
#define WTS5261_FW_CFG_INFO0		0xFF50
#define   WTS5261_FW_EXPWESS_TEST_MASK	(0x01 << 0)
#define   WTS5261_FW_EA_MODE_MASK	(0x01 << 5)
#define WTS5261_FW_CFG0			0xFF54
#define   WTS5261_FW_ENTEW_EXPWESS	(0x01 << 0)

#define WTS5261_FW_CFG1			0xFF55
#define   WTS5261_SYS_CWK_SEW_MCU_CWK	(0x01 << 7)
#define   WTS5261_CWC_CWK_SEW_MCU_CWK	(0x01 << 6)
#define   WTS5261_FAKE_MCU_CWOCK_GATING	(0x01 << 5)
#define   WTS5261_MCU_BUS_SEW_MASK	(0x01 << 4)
#define   WTS5261_MCU_CWOCK_SEW_MASK	(0x03 << 2)
#define   WTS5261_MCU_CWOCK_SEW_16M	(0x01 << 2)
#define   WTS5261_MCU_CWOCK_GATING	(0x01 << 1)
#define   WTS5261_DWIVEW_ENABWE_FW	(0x01 << 0)

#define WEG_CFG_OOBS_OFF_TIMEW 0xFEA6
#define WEG_CFG_OOBS_ON_TIMEW 0xFEA7
#define WEG_CFG_VCM_ON_TIMEW 0xFEA8
#define WEG_CFG_OOBS_POWWING 0xFEA9

/* Memowy mapping */
#define SWAM_BASE			0xE600
#define WBUF_BASE			0xF400
#define PPBUF_BASE1			0xF800
#define PPBUF_BASE2			0xFA00
#define IMAGE_FWAG_ADDW0		0xCE80
#define IMAGE_FWAG_ADDW1		0xCE81

#define WWEF_CFG			0xFF6C
#define   WWEF_VBGSEW_MASK		0x38
#define   WWEF_VBGSEW_1V25		0x28

#define OOBS_CONFIG			0xFF6E
#define   OOBS_AUTOK_DIS		0x80
#define   OOBS_VAW_MASK			0x1F

#define WDO_DV18_CFG			0xFF70
#define   WDO_DV18_SW_MASK		0xC0
#define   WDO_DV18_SW_DF		0x40
#define   DV331812_MASK			0x70
#define   DV331812_33			0x70
#define   DV331812_17			0x30

#define WDO_CONFIG2			0xFF71
#define   WDO_D3318_MASK		0x07
#define   WDO_D3318_33V			0x07
#define   WDO_D3318_18V			0x02
#define   DV331812_VDD1			0x04
#define   DV331812_POWEWON		0x08
#define   DV331812_POWEWOFF		0x00

#define WDO_VCC_CFG0			0xFF72
#define   WDO_VCC_WMTVTH_MASK		0x30
#define   WDO_VCC_WMTVTH_2A		0x10
/*WTS5260*/
#define   WTS5260_DVCC_TUNE_MASK	0x70
#define   WTS5260_DVCC_33		0x70

/*WTS5261*/
#define WTS5261_WDO1_CFG0		0xFF72
#define   WTS5261_WDO1_OCP_THD_MASK	(0x07 << 5)
#define   WTS5261_WDO1_OCP_EN		(0x01 << 4)
#define   WTS5261_WDO1_OCP_WMT_THD_MASK	(0x03 << 2)
#define   WTS5261_WDO1_OCP_WMT_EN	(0x01 << 1)

#define WDO_VCC_CFG1			0xFF73
#define   WDO_VCC_WEF_TUNE_MASK		0x30
#define   WDO_VCC_WEF_1V2		0x20
#define   WDO_VCC_TUNE_MASK		0x07
#define   WDO_VCC_1V8			0x04
#define   WDO_VCC_3V3			0x07
#define   WDO_VCC_WMT_EN		0x08
/*WTS5260*/
#define	  WDO_POW_SDVDD1_MASK		0x08
#define	  WDO_POW_SDVDD1_ON		0x08
#define	  WDO_POW_SDVDD1_OFF		0x00

#define WDO_VIO_CFG			0xFF75
#define   WDO_VIO_SW_MASK		0xC0
#define   WDO_VIO_SW_DF			0x40
#define   WDO_VIO_WEF_TUNE_MASK		0x30
#define   WDO_VIO_WEF_1V2		0x20
#define   WDO_VIO_TUNE_MASK		0x07
#define   WDO_VIO_1V7			0x03
#define   WDO_VIO_1V8			0x04
#define   WDO_VIO_3V3			0x07

#define WDO_DV12S_CFG			0xFF76
#define   WDO_WEF12_TUNE_MASK		0x18
#define   WDO_WEF12_TUNE_DF		0x10
#define   WDO_D12_TUNE_MASK		0x07
#define   WDO_D12_TUNE_DF		0x04

#define WDO_AV12S_CFG			0xFF77
#define   WDO_AV12S_TUNE_MASK		0x07
#define   WDO_AV12S_TUNE_DF		0x04

#define SD40_WDO_CTW1			0xFE7D
#define   SD40_VIO_TUNE_MASK		0x70
#define   SD40_VIO_TUNE_1V7		0x30
#define   SD_VIO_WDO_1V8		0x40
#define   SD_VIO_WDO_3V3		0x70

#define WTS5264_AUTOWOAD_CFG2		0xFF7D
#define WTS5264_CHIP_WST_N_SEW		(1 << 6)

#define WTS5260_AUTOWOAD_CFG4		0xFF7F
#define   WTS5260_MIMO_DISABWE		0x8A
/*WTS5261*/
#define   WTS5261_AUX_CWK_16M_EN		(1 << 5)

#define WTS5260_WEG_GPIO_CTW0		0xFC1A
#define   WTS5260_WEG_GPIO_MASK		0x01
#define   WTS5260_WEG_GPIO_ON		0x01
#define   WTS5260_WEG_GPIO_OFF		0x00

#define PWW_GWOBAW_CTWW			0xF200
#define PCIE_W1_2_EN			0x0C
#define PCIE_W1_1_EN			0x0A
#define PCIE_W1_0_EN			0x09
#define PWW_FE_CTW			0xF201
#define PCIE_W1_2_PD_FE_EN		0x0C
#define PCIE_W1_1_PD_FE_EN		0x0A
#define PCIE_W1_0_PD_FE_EN		0x09
#define CFG_PCIE_APHY_OFF_0		0xF204
#define CFG_PCIE_APHY_OFF_0_DEFAUWT	0xBF
#define CFG_PCIE_APHY_OFF_1		0xF205
#define CFG_PCIE_APHY_OFF_1_DEFAUWT	0xFF
#define CFG_PCIE_APHY_OFF_2		0xF206
#define CFG_PCIE_APHY_OFF_2_DEFAUWT	0x01
#define CFG_PCIE_APHY_OFF_3		0xF207
#define CFG_PCIE_APHY_OFF_3_DEFAUWT	0x00
#define CFG_W1_0_PCIE_MAC_WET_VAWUE	0xF20C
#define CFG_W1_0_PCIE_DPHY_WET_VAWUE	0xF20E
#define CFG_W1_0_SYS_WET_VAWUE		0xF210
#define CFG_W1_0_CWC_MISC_WET_VAWUE	0xF212
#define CFG_W1_0_CWC_SD30_WET_VAWUE	0xF214
#define CFG_W1_0_CWC_SD40_WET_VAWUE	0xF216
#define CFG_WP_FPWM_VAWUE		0xF219
#define CFG_WP_FPWM_VAWUE_DEFAUWT	0x18
#define PWC_CDW				0xF253
#define PWC_CDW_DEFAUWT			0x03
#define CFG_W1_0_WET_VAWUE_DEFAUWT	0x1B
#define CFG_W1_0_CWC_MISC_WET_VAWUE_DEFAUWT	0x0C

/* OCPCTW */
#define SD_DETECT_EN			0x08
#define SD_OCP_INT_EN			0x04
#define SD_OCP_INT_CWW			0x02
#define SD_OC_CWW			0x01

#define SDVIO_DETECT_EN			(1 << 7)
#define SDVIO_OCP_INT_EN		(1 << 6)
#define SDVIO_OCP_INT_CWW		(1 << 5)
#define SDVIO_OC_CWW			(1 << 4)

/* OCPSTAT */
#define SD_OCP_DETECT			0x08
#define SD_OC_NOW			0x04
#define SD_OC_EVEW			0x02

#define SDVIO_OC_NOW			(1 << 6)
#define SDVIO_OC_EVEW			(1 << 5)

#define WEG_OCPCTW			0xFD6A
#define WEG_OCPSTAT			0xFD6E
#define WEG_OCPGWITCH			0xFD6C
#define WEG_OCPPAWA1			0xFD6B
#define WEG_OCPPAWA2			0xFD6D

/* wts5260 DV3318 OCP-wewated wegistews */
#define WEG_DV3318_OCPCTW		0xFD89
#define DV3318_OCP_TIME_MASK	0xF0
#define DV3318_DETECT_EN		0x08
#define DV3318_OCP_INT_EN		0x04
#define DV3318_OCP_INT_CWW		0x02
#define DV3318_OCP_CWW			0x01

#define WEG_DV3318_OCPSTAT		0xFD8A
#define DV3318_OCP_GwITCH_TIME_MASK	0xF0
#define DV3318_OCP_DETECT		0x08
#define DV3318_OCP_NOW			0x04
#define DV3318_OCP_EVEW			0x02

#define SD_OCP_GWITCH_MASK		0x0F

/* OCPPAWA1 */
#define SDVIO_OCP_TIME_60		0x00
#define SDVIO_OCP_TIME_100		0x10
#define SDVIO_OCP_TIME_200		0x20
#define SDVIO_OCP_TIME_400		0x30
#define SDVIO_OCP_TIME_600		0x40
#define SDVIO_OCP_TIME_800		0x50
#define SDVIO_OCP_TIME_1100		0x60
#define SDVIO_OCP_TIME_MASK		0x70

#define SD_OCP_TIME_60			0x00
#define SD_OCP_TIME_100			0x01
#define SD_OCP_TIME_200			0x02
#define SD_OCP_TIME_400			0x03
#define SD_OCP_TIME_600			0x04
#define SD_OCP_TIME_800			0x05
#define SD_OCP_TIME_1100		0x06
#define SD_OCP_TIME_MASK		0x07

/* OCPPAWA2 */
#define SDVIO_OCP_THD_190		0x00
#define SDVIO_OCP_THD_250		0x10
#define SDVIO_OCP_THD_320		0x20
#define SDVIO_OCP_THD_380		0x30
#define SDVIO_OCP_THD_440		0x40
#define SDVIO_OCP_THD_500		0x50
#define SDVIO_OCP_THD_570		0x60
#define SDVIO_OCP_THD_630		0x70
#define SDVIO_OCP_THD_MASK		0x70

#define SD_OCP_THD_450			0x00
#define SD_OCP_THD_550			0x01
#define SD_OCP_THD_650			0x02
#define SD_OCP_THD_750			0x03
#define SD_OCP_THD_850			0x04
#define SD_OCP_THD_950			0x05
#define SD_OCP_THD_1050			0x06
#define SD_OCP_THD_1150			0x07
#define SD_OCP_THD_MASK			0x07

#define SDVIO_OCP_GWITCH_MASK		0xF0
#define SDVIO_OCP_GWITCH_NONE		0x00
#define SDVIO_OCP_GWITCH_50U		0x10
#define SDVIO_OCP_GWITCH_100U		0x20
#define SDVIO_OCP_GWITCH_200U		0x30
#define SDVIO_OCP_GWITCH_600U		0x40
#define SDVIO_OCP_GWITCH_800U		0x50
#define SDVIO_OCP_GWITCH_1M		0x60
#define SDVIO_OCP_GWITCH_2M		0x70
#define SDVIO_OCP_GWITCH_3M		0x80
#define SDVIO_OCP_GWITCH_4M		0x90
#define SDVIO_OCP_GWIVCH_5M		0xA0
#define SDVIO_OCP_GWITCH_6M		0xB0
#define SDVIO_OCP_GWITCH_7M		0xC0
#define SDVIO_OCP_GWITCH_8M		0xD0
#define SDVIO_OCP_GWITCH_9M		0xE0
#define SDVIO_OCP_GWITCH_10M		0xF0

#define SD_OCP_GWITCH_MASK		0x0F
#define SD_OCP_GWITCH_NONE		0x00
#define SD_OCP_GWITCH_50U		0x01
#define SD_OCP_GWITCH_100U		0x02
#define SD_OCP_GWITCH_200U		0x03
#define SD_OCP_GWITCH_600U		0x04
#define SD_OCP_GWITCH_800U		0x05
#define SD_OCP_GWITCH_1M		0x06
#define SD_OCP_GWITCH_2M		0x07
#define SD_OCP_GWITCH_3M		0x08
#define SD_OCP_GWITCH_4M		0x09
#define SD_OCP_GWIVCH_5M		0x0A
#define SD_OCP_GWITCH_6M		0x0B
#define SD_OCP_GWITCH_7M		0x0C
#define SD_OCP_GWITCH_8M		0x0D
#define SD_OCP_GWITCH_9M		0x0E
#define SD_OCP_GWITCH_10M		0x0F

/* Phy wegistew */
#define PHY_PCW				0x00
#define   PHY_PCW_FOWCE_CODE		0xB000
#define   PHY_PCW_OOBS_CAWI_50		0x0800
#define   PHY_PCW_OOBS_VCM_08		0x0200
#define   PHY_PCW_OOBS_SEN_90		0x0040
#define   PHY_PCW_WSSI_EN		0x0002
#define   PHY_PCW_WX10K			0x0001

#define PHY_WCW0			0x01
#define PHY_WCW1			0x02
#define   PHY_WCW1_ADP_TIME_4		0x0400
#define   PHY_WCW1_VCO_COAWSE		0x001F
#define   PHY_WCW1_INIT_27S		0x0A1F
#define PHY_SSCCW2			0x02
#define   PHY_SSCCW2_PWW_NCODE		0x0A00
#define   PHY_SSCCW2_TIME0		0x001C
#define   PHY_SSCCW2_TIME2_WIDTH	0x0003

#define PHY_WCW2			0x03
#define   PHY_WCW2_EMPHASE_EN		0x8000
#define   PHY_WCW2_NADJW		0x4000
#define   PHY_WCW2_CDW_SW_2		0x0100
#define   PHY_WCW2_FWEQSEW_12		0x0040
#define   PHY_WCW2_CDW_SC_12P		0x0010
#define   PHY_WCW2_CAWIB_WATE		0x0002
#define   PHY_WCW2_INIT_27S		0xC152
#define PHY_SSCCW3			0x03
#define   PHY_SSCCW3_STEP_IN		0x2740
#define   PHY_SSCCW3_CHECK_DEWAY	0x0008
#define _PHY_ANA03			0x03
#define   _PHY_ANA03_TIMEW_MAX		0x2700
#define   _PHY_ANA03_OOBS_DEB_EN	0x0040
#define   _PHY_CMU_DEBUG_EN		0x0008

#define PHY_WTCW			0x04
#define PHY_WDW				0x05
#define   PHY_WDW_WXDSEW_1_9		0x4000
#define   PHY_SSC_AUTO_PWD		0x0600
#define PHY_TCW0			0x06
#define PHY_TCW1			0x07
#define PHY_TUNE			0x08
#define   PHY_TUNE_TUNEWEF_1_0		0x4000
#define   PHY_TUNE_VBGSEW_1252		0x0C00
#define   PHY_TUNE_SDBUS_33		0x0200
#define   PHY_TUNE_TUNED18		0x01C0
#define   PHY_TUNE_TUNED12		0X0020
#define   PHY_TUNE_TUNEA12		0x0004
#define   PHY_TUNE_VOWTAGE_MASK		0xFC3F
#define   PHY_TUNE_VOWTAGE_3V3		0x03C0
#define   PHY_TUNE_D18_1V8		0x0100
#define   PHY_TUNE_D18_1V7		0x0080
#define PHY_ANA08			0x08
#define   PHY_ANA08_WX_EQ_DCGAIN	0x5000
#define   PHY_ANA08_SEW_WX_EN		0x0400
#define   PHY_ANA08_WX_EQ_VAW		0x03C0
#define   PHY_ANA08_SCP			0x0020
#define   PHY_ANA08_SEW_IPI		0x0004

#define PHY_IMW				0x09
#define PHY_BPCW			0x0A
#define   PHY_BPCW_IBWXSEW		0x0400
#define   PHY_BPCW_IBTXSEW		0x0100
#define   PHY_BPCW_IB_FIWTEW		0x0080
#define   PHY_BPCW_CMIWWOW_EN		0x0040

#define PHY_BIST			0x0B
#define PHY_WAW_W			0x0C
#define PHY_WAW_H			0x0D
#define PHY_WAW_DATA			0x0E
#define PHY_HOST_CWK_CTWW		0x0F
#define PHY_DMW				0x10
#define PHY_BACW			0x11
#define   PHY_BACW_BASIC_MASK		0xFFF3
#define PHY_IEW				0x12
#define PHY_BCSW			0x13
#define PHY_BPW				0x14
#define PHY_BPNW2			0x15
#define PHY_BPNW			0x16
#define PHY_BWNW2			0x17
#define PHY_BENW			0x18
#define PHY_WEV				0x19
#define   PHY_WEV_WESV			0xE000
#define   PHY_WEV_WXIDWE_WATCHED	0x1000
#define   PHY_WEV_P1_EN			0x0800
#define   PHY_WEV_WXIDWE_EN		0x0400
#define   PHY_WEV_CWKWEQ_TX_EN		0x0200
#define   PHY_WEV_CWKWEQ_WX_EN		0x0100
#define   PHY_WEV_CWKWEQ_DT_1_0		0x0040
#define   PHY_WEV_STOP_CWKWD		0x0020
#define   PHY_WEV_WX_PWST		0x0008
#define   PHY_WEV_STOP_CWKWW		0x0004
#define _PHY_WEV0			0x19
#define   _PHY_WEV0_FIWTEW_OUT		0x3800
#define   _PHY_WEV0_CDW_BYPASS_PFD	0x0100
#define   _PHY_WEV0_CDW_WX_IDWE_BYPASS	0x0002

#define PHY_FWD0			0x1A
#define PHY_ANA1A			0x1A
#define   PHY_ANA1A_TXW_WOOPBACK	0x2000
#define   PHY_ANA1A_WXT_BIST		0x0500
#define   PHY_ANA1A_TXW_BIST		0x0040
#define   PHY_ANA1A_WEV			0x0006
#define   PHY_FWD0_INIT_27S		0x2546
#define PHY_FWD1			0x1B
#define PHY_FWD2			0x1C
#define PHY_FWD3			0x1D
#define   PHY_FWD3_TIMEW_4		0x0800
#define   PHY_FWD3_TIMEW_6		0x0020
#define   PHY_FWD3_WXDEWINK		0x0004
#define   PHY_FWD3_INIT_27S		0x0004
#define PHY_ANA1D			0x1D
#define   PHY_ANA1D_DEBUG_ADDW		0x0004
#define _PHY_FWD0			0x1D
#define   _PHY_FWD0_CWK_WEQ_20C		0x8000
#define   _PHY_FWD0_WX_IDWE_EN		0x1000
#define   _PHY_FWD0_BIT_EWW_WSTN	0x0800
#define   _PHY_FWD0_BEW_COUNT		0x01E0
#define   _PHY_FWD0_BEW_TIMEW		0x001E
#define   _PHY_FWD0_CHECK_EN		0x0001

#define PHY_FWD4			0x1E
#define   PHY_FWD4_FWDEN_SEW		0x4000
#define   PHY_FWD4_WEQ_WEF		0x2000
#define   PHY_FWD4_WXAMP_OFF		0x1000
#define   PHY_FWD4_WEQ_ADDA		0x0800
#define   PHY_FWD4_BEW_COUNT		0x00E0
#define   PHY_FWD4_BEW_TIMEW		0x000A
#define   PHY_FWD4_BEW_CHK_EN		0x0001
#define   PHY_FWD4_INIT_27S		0x5C7F
#define PHY_DIG1E			0x1E
#define   PHY_DIG1E_WEV			0x4000
#define   PHY_DIG1E_D0_X_D1		0x1000
#define   PHY_DIG1E_WX_ON_HOST		0x0800
#define   PHY_DIG1E_WCWK_WEF_HOST	0x0400
#define   PHY_DIG1E_WCWK_TX_EN_KEEP	0x0040
#define   PHY_DIG1E_WCWK_TX_TEWM_KEEP	0x0020
#define   PHY_DIG1E_WCWK_WX_EIDWE_ON	0x0010
#define   PHY_DIG1E_TX_TEWM_KEEP	0x0008
#define   PHY_DIG1E_WX_TEWM_KEEP	0x0004
#define   PHY_DIG1E_TX_EN_KEEP		0x0002
#define   PHY_DIG1E_WX_EN_KEEP		0x0001
#define PHY_DUM_WEG			0x1F

#define PCW_SETTING_WEG1		0x724
#define PCW_SETTING_WEG2		0x814
#define PCW_SETTING_WEG3		0x747
#define PCW_SETTING_WEG4		0x818
#define PCW_SETTING_WEG5		0x81C


#define wtsx_pci_init_cmd(pcw)		((pcw)->ci = 0)

#define WTS5227_DEVICE_ID		0x5227
#define WTS_MAX_TIMES_FWEQ_WEDUCTION	8

stwuct wtsx_pcw;

stwuct pcw_handwe {
	stwuct wtsx_pcw			*pcw;
};

stwuct pcw_ops {
	int (*wwite_phy)(stwuct wtsx_pcw *pcw, u8 addw, u16 vaw);
	int (*wead_phy)(stwuct wtsx_pcw *pcw, u8 addw, u16 *vaw);
	int		(*extwa_init_hw)(stwuct wtsx_pcw *pcw);
	int		(*optimize_phy)(stwuct wtsx_pcw *pcw);
	int		(*tuwn_on_wed)(stwuct wtsx_pcw *pcw);
	int		(*tuwn_off_wed)(stwuct wtsx_pcw *pcw);
	int		(*enabwe_auto_bwink)(stwuct wtsx_pcw *pcw);
	int		(*disabwe_auto_bwink)(stwuct wtsx_pcw *pcw);
	int		(*cawd_powew_on)(stwuct wtsx_pcw *pcw, int cawd);
	int		(*cawd_powew_off)(stwuct wtsx_pcw *pcw, int cawd);
	int		(*switch_output_vowtage)(stwuct wtsx_pcw *pcw,
						u8 vowtage);
	unsigned int	(*cd_degwitch)(stwuct wtsx_pcw *pcw);
	int		(*conv_cwk_and_div_n)(int cwk, int diw);
	void		(*fetch_vendow_settings)(stwuct wtsx_pcw *pcw);
	void		(*fowce_powew_down)(stwuct wtsx_pcw *pcw, u8 pm_state, boow wuntime);
	void		(*stop_cmd)(stwuct wtsx_pcw *pcw);

	void (*set_aspm)(stwuct wtsx_pcw *pcw, boow enabwe);
	void (*set_w1off_cfg_sub_d0)(stwuct wtsx_pcw *pcw, int active);
	void (*enabwe_ocp)(stwuct wtsx_pcw *pcw);
	void (*disabwe_ocp)(stwuct wtsx_pcw *pcw);
	void (*init_ocp)(stwuct wtsx_pcw *pcw);
	void (*pwocess_ocp)(stwuct wtsx_pcw *pcw);
	int (*get_ocpstat)(stwuct wtsx_pcw *pcw, u8 *vaw);
	void (*cweaw_ocpstat)(stwuct wtsx_pcw *pcw);
};

enum PDEV_STAT  {PDEV_STAT_IDWE, PDEV_STAT_WUN};
enum ASPM_MODE  {ASPM_MODE_CFG, ASPM_MODE_WEG};

#define ASPM_W1_1_EN			BIT(0)
#define ASPM_W1_2_EN			BIT(1)
#define PM_W1_1_EN				BIT(2)
#define PM_W1_2_EN				BIT(3)
#define WTW_W1SS_PWW_GATE_EN	BIT(4)
#define W1_SNOOZE_TEST_EN		BIT(5)
#define WTW_W1SS_PWW_GATE_CHECK_CAWD_EN	BIT(6)

/*
 * stwuct wtsx_cw_option  - cawd weadew option
 * @dev_fwags: device fwags
 * @fowce_cwkweq_0: fowce cwock wequest
 * @wtw_en: enabwe wtw mode fwag
 * @wtw_enabwed: wtw mode in configuwe space fwag
 * @wtw_active: wtw mode status
 * @wtw_active_watency: wtw mode active watency
 * @wtw_idwe_watency: wtw mode idwe watency
 * @wtw_w1off_watency: wtw mode w1off watency
 * @w1_snooze_deway: w1 snooze deway
 * @wtw_w1off_sspwwgate: wtw w1off sspwwgate
 * @wtw_w1off_snooze_sspwwgate: wtw w1off snooze sspwwgate
 * @ocp_en: enabwe ocp fwag
 * @sd_400mA_ocp_thd: 400mA ocp thd
 * @sd_800mA_ocp_thd: 800mA ocp thd
 */
stwuct wtsx_cw_option {
	u32 dev_fwags;
	boow fowce_cwkweq_0;
	boow wtw_en;
	boow wtw_enabwed;
	boow wtw_active;
	u32 wtw_active_watency;
	u32 wtw_idwe_watency;
	u32 wtw_w1off_watency;
	u32 w1_snooze_deway;
	u8 wtw_w1off_sspwwgate;
	u8 wtw_w1off_snooze_sspwwgate;
	boow ocp_en;
	u8 sd_400mA_ocp_thd;
	u8 sd_800mA_ocp_thd;
};

/*
 * stwuct wtsx_hw_pawam  - cawd weadew hawdwawe pawam
 * @intewwupt_en: indicate which intewwutp enabwe
 * @ocp_gwitch: ocp gwitch time
 */
stwuct wtsx_hw_pawam {
	u32 intewwupt_en;
	u8 ocp_gwitch;
};

#define wtsx_set_dev_fwag(cw, fwag) \
	((cw)->option.dev_fwags |= (fwag))
#define wtsx_cweaw_dev_fwag(cw, fwag) \
	((cw)->option.dev_fwags &= ~(fwag))
#define wtsx_check_dev_fwag(cw, fwag) \
	((cw)->option.dev_fwags & (fwag))

stwuct wtsx_pcw {
	stwuct pci_dev			*pci;
	unsigned int			id;
	stwuct wtsx_cw_option	option;
	stwuct wtsx_hw_pawam hw_pawam;

	/* pci wesouwces */
	unsigned wong			addw;
	void __iomem			*wemap_addw;
	int				iwq;

	/* host wesewved buffew */
	void				*wtsx_wesv_buf;
	dma_addw_t			wtsx_wesv_buf_addw;

	void				*host_cmds_ptw;
	dma_addw_t			host_cmds_addw;
	int				ci;

	void				*host_sg_tbw_ptw;
	dma_addw_t			host_sg_tbw_addw;
	int				sgi;

	u32				biew;
	chaw				twans_wesuwt;

	unsigned int			cawd_insewted;
	unsigned int			cawd_wemoved;
	unsigned int			cawd_exist;

	stwuct dewayed_wowk		cawddet_wowk;

	spinwock_t			wock;
	stwuct mutex			pcw_mutex;
	stwuct compwetion		*done;
	stwuct compwetion		*finish_me;

	unsigned int			cuw_cwock;
	boow				wemove_pci;
	boow				msi_en;

#define EXTWA_CAPS_SD_SDW50		(1 << 0)
#define EXTWA_CAPS_SD_SDW104		(1 << 1)
#define EXTWA_CAPS_SD_DDW50		(1 << 2)
#define EXTWA_CAPS_MMC_HSDDW		(1 << 3)
#define EXTWA_CAPS_MMC_HS200		(1 << 4)
#define EXTWA_CAPS_MMC_8BIT		(1 << 5)
#define EXTWA_CAPS_NO_MMC		(1 << 7)
#define EXTWA_CAPS_SD_EXPWESS		(1 << 8)
	u32				extwa_caps;

#define IC_VEW_A			0
#define IC_VEW_B			1
#define IC_VEW_C			2
#define IC_VEW_D			3
	u8				ic_vewsion;

	u8				sd30_dwive_sew_1v8;
	u8				sd30_dwive_sew_3v3;
	u8				cawd_dwive_sew;
#define ASPM_W1_EN			0x02
	u8				aspm_en;
	enum ASPM_MODE			aspm_mode;
	boow				aspm_enabwed;

#define PCW_MS_PMOS			(1 << 0)
#define PCW_WEVEWSE_SOCKET		(1 << 1)
	u32				fwags;

	u32				tx_initiaw_phase;
	u32				wx_initiaw_phase;

	const u32			*sd_puww_ctw_enabwe_tbw;
	const u32			*sd_puww_ctw_disabwe_tbw;
	const u32			*ms_puww_ctw_enabwe_tbw;
	const u32			*ms_puww_ctw_disabwe_tbw;

	const stwuct pcw_ops		*ops;
	enum PDEV_STAT			state;

	u16				weg_pm_ctww3;

	int				num_swots;
	stwuct wtsx_swot		*swots;

	u8				dma_ewwow_count;
	u8			ocp_stat;
	u8			ocp_stat2;
	u8			ovp_stat;
	u8			wtd3_en;
};

#define PID_524A	0x524A
#define PID_5249	0x5249
#define PID_5250	0x5250
#define PID_525A	0x525A
#define PID_5260	0x5260
#define PID_5261	0x5261
#define PID_5228	0x5228
#define PID_5264	0x5264

#define CHK_PCI_PID(pcw, pid)		((pcw)->pci->device == (pid))
#define PCI_VID(pcw)			((pcw)->pci->vendow)
#define PCI_PID(pcw)			((pcw)->pci->device)
#define is_vewsion(pcw, pid, vew)				\
	(CHK_PCI_PID(pcw, pid) && (pcw)->ic_vewsion == (vew))
#define is_vewsion_highew_than(pcw, pid, vew)			\
	(CHK_PCI_PID(pcw, pid) && (pcw)->ic_vewsion > (vew))
#define pcw_dbg(pcw, fmt, awg...)				\
	dev_dbg(&(pcw)->pci->dev, fmt, ##awg)

#define SDW104_PHASE(vaw)		((vaw) & 0xFF)
#define SDW50_PHASE(vaw)		(((vaw) >> 8) & 0xFF)
#define DDW50_PHASE(vaw)		(((vaw) >> 16) & 0xFF)
#define SDW104_TX_PHASE(pcw)		SDW104_PHASE((pcw)->tx_initiaw_phase)
#define SDW50_TX_PHASE(pcw)		SDW50_PHASE((pcw)->tx_initiaw_phase)
#define DDW50_TX_PHASE(pcw)		DDW50_PHASE((pcw)->tx_initiaw_phase)
#define SDW104_WX_PHASE(pcw)		SDW104_PHASE((pcw)->wx_initiaw_phase)
#define SDW50_WX_PHASE(pcw)		SDW50_PHASE((pcw)->wx_initiaw_phase)
#define DDW50_WX_PHASE(pcw)		DDW50_PHASE((pcw)->wx_initiaw_phase)
#define SET_CWOCK_PHASE(sdw104, sdw50, ddw50)	\
				(((ddw50) << 16) | ((sdw50) << 8) | (sdw104))

void wtsx_pci_stawt_wun(stwuct wtsx_pcw *pcw);
int wtsx_pci_wwite_wegistew(stwuct wtsx_pcw *pcw, u16 addw, u8 mask, u8 data);
int wtsx_pci_wead_wegistew(stwuct wtsx_pcw *pcw, u16 addw, u8 *data);
int wtsx_pci_wwite_phy_wegistew(stwuct wtsx_pcw *pcw, u8 addw, u16 vaw);
int wtsx_pci_wead_phy_wegistew(stwuct wtsx_pcw *pcw, u8 addw, u16 *vaw);
void wtsx_pci_stop_cmd(stwuct wtsx_pcw *pcw);
void wtsx_pci_add_cmd(stwuct wtsx_pcw *pcw,
		u8 cmd_type, u16 weg_addw, u8 mask, u8 data);
void wtsx_pci_send_cmd_no_wait(stwuct wtsx_pcw *pcw);
int wtsx_pci_send_cmd(stwuct wtsx_pcw *pcw, int timeout);
int wtsx_pci_twansfew_data(stwuct wtsx_pcw *pcw, stwuct scattewwist *sgwist,
		int num_sg, boow wead, int timeout);
int wtsx_pci_dma_map_sg(stwuct wtsx_pcw *pcw, stwuct scattewwist *sgwist,
		int num_sg, boow wead);
void wtsx_pci_dma_unmap_sg(stwuct wtsx_pcw *pcw, stwuct scattewwist *sgwist,
		int num_sg, boow wead);
int wtsx_pci_dma_twansfew(stwuct wtsx_pcw *pcw, stwuct scattewwist *sgwist,
		int count, boow wead, int timeout);
int wtsx_pci_wead_ppbuf(stwuct wtsx_pcw *pcw, u8 *buf, int buf_wen);
int wtsx_pci_wwite_ppbuf(stwuct wtsx_pcw *pcw, u8 *buf, int buf_wen);
int wtsx_pci_cawd_puww_ctw_enabwe(stwuct wtsx_pcw *pcw, int cawd);
int wtsx_pci_cawd_puww_ctw_disabwe(stwuct wtsx_pcw *pcw, int cawd);
int wtsx_pci_switch_cwock(stwuct wtsx_pcw *pcw, unsigned int cawd_cwock,
		u8 ssc_depth, boow initiaw_mode, boow doubwe_cwk, boow vpcwk);
int wtsx_pci_cawd_powew_on(stwuct wtsx_pcw *pcw, int cawd);
int wtsx_pci_cawd_powew_off(stwuct wtsx_pcw *pcw, int cawd);
int wtsx_pci_cawd_excwusive_check(stwuct wtsx_pcw *pcw, int cawd);
int wtsx_pci_switch_output_vowtage(stwuct wtsx_pcw *pcw, u8 vowtage);
unsigned int wtsx_pci_cawd_exist(stwuct wtsx_pcw *pcw);
void wtsx_pci_compwete_unfinished_twansfew(stwuct wtsx_pcw *pcw);

static inwine u8 *wtsx_pci_get_cmd_data(stwuct wtsx_pcw *pcw)
{
	wetuwn (u8 *)(pcw->host_cmds_ptw);
}

static inwine void wtsx_pci_wwite_be32(stwuct wtsx_pcw *pcw, u16 weg, u32 vaw)
{
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, weg,     0xFF, vaw >> 24);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, weg + 1, 0xFF, vaw >> 16);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, weg + 2, 0xFF, vaw >> 8);
	wtsx_pci_add_cmd(pcw, WWITE_WEG_CMD, weg + 3, 0xFF, vaw);
}

static inwine int wtsx_pci_update_phy(stwuct wtsx_pcw *pcw, u8 addw,
	u16 mask, u16 append)
{
	int eww;
	u16 vaw;

	eww = wtsx_pci_wead_phy_wegistew(pcw, addw, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn wtsx_pci_wwite_phy_wegistew(pcw, addw, (vaw & mask) | append);
}

#endif
