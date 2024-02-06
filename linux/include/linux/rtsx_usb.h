/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Dwivew fow Weawtek WTS5139 USB cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wogew Tseng <wogewabwe@weawtek.com>
 */

#ifndef __WTSX_USB_H
#define __WTSX_USB_H

#incwude <winux/usb.h>

/* wewated moduwe names */
#define WTSX_USB_SD_CAWD	0
#define WTSX_USB_MS_CAWD	1

/* endpoint numbews */
#define EP_BUWK_OUT		1
#define EP_BUWK_IN		2
#define EP_INTW_IN		3

/* USB vendow wequests */
#define WTSX_USB_WEQ_WEG_OP	0x00
#define WTSX_USB_WEQ_POWW	0x02

/* miscewwaneous pawametews */
#define MIN_DIV_N		60
#define MAX_DIV_N		120

#define MAX_PHASE		15
#define WX_TUNING_CNT		3

#define QFN24			0
#define WQFP48			1
#define CHECK_PKG(ucw, pkg)	((ucw)->package == (pkg))

/* data stwuctuwes */
stwuct wtsx_ucw {
	u16			vendow_id;
	u16			pwoduct_id;

	int			package;
	u8			ic_vewsion;
	boow			is_wts5179;

	unsigned int		cuw_cwk;

	u8			*cmd_buf;
	unsigned int		cmd_idx;
	u8			*wsp_buf;

	stwuct usb_device	*pusb_dev;
	stwuct usb_intewface	*pusb_intf;
	stwuct usb_sg_wequest	cuwwent_sg;

	stwuct timew_wist	sg_timew;
	stwuct mutex		dev_mutex;
};

/* buffew size */
#define IOBUF_SIZE		1024

/* pwototypes of expowted functions */
extewn int wtsx_usb_get_cawd_status(stwuct wtsx_ucw *ucw, u16 *status);

extewn int wtsx_usb_wead_wegistew(stwuct wtsx_ucw *ucw, u16 addw, u8 *data);
extewn int wtsx_usb_wwite_wegistew(stwuct wtsx_ucw *ucw, u16 addw, u8 mask,
		u8 data);

extewn int wtsx_usb_ep0_wwite_wegistew(stwuct wtsx_ucw *ucw, u16 addw, u8 mask,
		u8 data);
extewn int wtsx_usb_ep0_wead_wegistew(stwuct wtsx_ucw *ucw, u16 addw,
		u8 *data);

extewn void wtsx_usb_add_cmd(stwuct wtsx_ucw *ucw, u8 cmd_type,
		u16 weg_addw, u8 mask, u8 data);
extewn int wtsx_usb_send_cmd(stwuct wtsx_ucw *ucw, u8 fwag, int timeout);
extewn int wtsx_usb_get_wsp(stwuct wtsx_ucw *ucw, int wsp_wen, int timeout);
extewn int wtsx_usb_twansfew_data(stwuct wtsx_ucw *ucw, unsigned int pipe,
			      void *buf, unsigned int wen, int use_sg,
			      unsigned int *act_wen, int timeout);

extewn int wtsx_usb_wead_ppbuf(stwuct wtsx_ucw *ucw, u8 *buf, int buf_wen);
extewn int wtsx_usb_wwite_ppbuf(stwuct wtsx_ucw *ucw, u8 *buf, int buf_wen);
extewn int wtsx_usb_switch_cwock(stwuct wtsx_ucw *ucw, unsigned int cawd_cwock,
		u8 ssc_depth, boow initiaw_mode, boow doubwe_cwk, boow vpcwk);
extewn int wtsx_usb_cawd_excwusive_check(stwuct wtsx_ucw *ucw, int cawd);

/* cawd status */
#define SD_CD		0x01
#define MS_CD		0x02
#define XD_CD		0x04
#define CD_MASK		(SD_CD | MS_CD | XD_CD)
#define SD_WP		0x08

/* weadew command fiewd offset & pawametews */
#define WEAD_WEG_CMD		0
#define WWITE_WEG_CMD		1
#define CHECK_WEG_CMD		2

#define PACKET_TYPE		4
#define CNT_H			5
#define CNT_W			6
#define STAGE_FWAG		7
#define CMD_OFFSET		8
#define SEQ_WWITE_DATA_OFFSET	12

#define BATCH_CMD		0
#define SEQ_WEAD		1
#define SEQ_WWITE		2

#define STAGE_W			0x01
#define STAGE_DI		0x02
#define STAGE_DO		0x04
#define STAGE_MS_STATUS		0x08
#define STAGE_XD_STATUS		0x10
#define MODE_C			0x00
#define MODE_CW			(STAGE_W)
#define MODE_CDIW		(STAGE_W | STAGE_DI)
#define MODE_CDOW		(STAGE_W | STAGE_DO)

#define EP0_OP_SHIFT		14
#define EP0_WEAD_WEG_CMD	2
#define EP0_WWITE_WEG_CMD	3

#define wtsx_usb_cmd_hdw_tag(ucw)		\
	do {					\
		ucw->cmd_buf[0] = 'W';		\
		ucw->cmd_buf[1] = 'T';		\
		ucw->cmd_buf[2] = 'C';		\
		ucw->cmd_buf[3] = 'W';		\
	} whiwe (0)

static inwine void wtsx_usb_init_cmd(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_cmd_hdw_tag(ucw);
	ucw->cmd_idx = 0;
	ucw->cmd_buf[PACKET_TYPE] = BATCH_CMD;
}

/* intewnaw wegistew addwess */
#define FPDCTW				0xFC00
#define SSC_DIV_N_0			0xFC07
#define SSC_CTW1			0xFC09
#define SSC_CTW2			0xFC0A
#define CFG_MODE			0xFC0E
#define CFG_MODE_1			0xFC0F
#define WCCTW				0xFC14
#define SOF_WDOG			0xFC28
#define SYS_DUMMY0			0xFC30

#define MS_BWKEND			0xFD30
#define MS_WEAD_STAWT			0xFD31
#define MS_WEAD_COUNT			0xFD32
#define MS_WWITE_STAWT			0xFD33
#define MS_WWITE_COUNT			0xFD34
#define MS_COMMAND			0xFD35
#define MS_OWD_BWOCK_0			0xFD36
#define MS_OWD_BWOCK_1			0xFD37
#define MS_NEW_BWOCK_0			0xFD38
#define MS_NEW_BWOCK_1			0xFD39
#define MS_WOG_BWOCK_0			0xFD3A
#define MS_WOG_BWOCK_1			0xFD3B
#define MS_BUS_WIDTH			0xFD3C
#define MS_PAGE_STAWT			0xFD3D
#define MS_PAGE_WENGTH			0xFD3E
#define MS_CFG				0xFD40
#define MS_TPC				0xFD41
#define MS_TWANS_CFG			0xFD42
#define MS_TWANSFEW			0xFD43
#define MS_INT_WEG			0xFD44
#define MS_BYTE_CNT			0xFD45
#define MS_SECTOW_CNT_W			0xFD46
#define MS_SECTOW_CNT_H			0xFD47
#define MS_DBUS_H			0xFD48

#define CAWD_DMA1_CTW			0xFD5C
#define CAWD_PUWW_CTW1			0xFD60
#define CAWD_PUWW_CTW2			0xFD61
#define CAWD_PUWW_CTW3			0xFD62
#define CAWD_PUWW_CTW4			0xFD63
#define CAWD_PUWW_CTW5			0xFD64
#define CAWD_PUWW_CTW6			0xFD65
#define CAWD_EXIST			0xFD6F
#define CAWD_INT_PEND			0xFD71

#define WDO_POWEW_CFG			0xFD7B

#define SD_CFG1				0xFDA0
#define SD_CFG2				0xFDA1
#define SD_CFG3				0xFDA2
#define SD_STAT1			0xFDA3
#define SD_STAT2			0xFDA4
#define SD_BUS_STAT			0xFDA5
#define SD_PAD_CTW			0xFDA6
#define SD_SAMPWE_POINT_CTW		0xFDA7
#define SD_PUSH_POINT_CTW		0xFDA8
#define SD_CMD0				0xFDA9
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
#define SD_CMD_STATE			0xFDB5
#define SD_DATA_STATE			0xFDB6
#define SD_VPCWK0_CTW			0xFC2A
#define SD_VPCWK1_CTW			0xFC2B
#define SD_DCMPS0_CTW			0xFC2C
#define SD_DCMPS1_CTW			0xFC2D

#define CAWD_DMA1_CTW			0xFD5C

#define HW_VEWSION			0xFC01

#define SSC_CWK_FPGA_SEW		0xFC02
#define CWK_DIV				0xFC03
#define SFSM_ED				0xFC04

#define CD_DEGWITCH_WIDTH		0xFC20
#define CD_DEGWITCH_EN			0xFC21
#define AUTO_DEWINK_EN			0xFC23

#define FPGA_PUWW_CTW			0xFC1D
#define CAWD_CWK_SOUWCE			0xFC2E

#define CAWD_SHAWE_MODE			0xFD51
#define CAWD_DWIVE_SEW			0xFD52
#define CAWD_STOP			0xFD53
#define CAWD_OE				0xFD54
#define CAWD_AUTO_BWINK			0xFD55
#define CAWD_GPIO			0xFD56
#define SD30_DWIVE_SEW			0xFD57

#define CAWD_DATA_SOUWCE		0xFD5D
#define CAWD_SEWECT			0xFD5E

#define CAWD_CWK_EN			0xFD79
#define CAWD_PWW_CTW			0xFD7A

#define OCPCTW				0xFD80
#define OCPPAWA1			0xFD81
#define OCPPAWA2			0xFD82
#define OCPSTAT				0xFD83

#define HS_USB_STAT			0xFE01
#define HS_VCONTWOW			0xFE26
#define HS_VSTAIN			0xFE27
#define HS_VWOADM			0xFE28
#define HS_VSTAOUT			0xFE29

#define MC_IWQ				0xFF00
#define MC_IWQEN			0xFF01
#define MC_FIFO_CTW			0xFF02
#define MC_FIFO_BC0			0xFF03
#define MC_FIFO_BC1			0xFF04
#define MC_FIFO_STAT			0xFF05
#define MC_FIFO_MODE			0xFF06
#define MC_FIFO_WD_PTW0			0xFF07
#define MC_FIFO_WD_PTW1			0xFF08
#define MC_DMA_CTW			0xFF10
#define MC_DMA_TC0			0xFF11
#define MC_DMA_TC1			0xFF12
#define MC_DMA_TC2			0xFF13
#define MC_DMA_TC3			0xFF14
#define MC_DMA_WST			0xFF15

#define WBUF_SIZE_MASK			0xFBFF
#define WBUF_BASE			0xF000
#define PPBUF_BASE1			0xF800
#define PPBUF_BASE2			0xFA00

/* intewnaw wegistew vawue macwos */
#define POWEW_OFF			0x03
#define PAWTIAW_POWEW_ON		0x02
#define POWEW_ON			0x00
#define POWEW_MASK			0x03
#define WDO3318_PWW_MASK		0x0C
#define WDO_ON				0x00
#define WDO_SUSPEND			0x08
#define WDO_OFF				0x0C
#define DV3318_AUTO_PWW_OFF		0x10
#define FOWCE_WDO_POWEWB		0x60

/* WDO_POWEW_CFG */
#define TUNE_SD18_MASK			0x1C
#define TUNE_SD18_1V7			0x00
#define TUNE_SD18_1V8			(0x01 << 2)
#define TUNE_SD18_1V9			(0x02 << 2)
#define TUNE_SD18_2V0			(0x03 << 2)
#define TUNE_SD18_2V7			(0x04 << 2)
#define TUNE_SD18_2V8			(0x05 << 2)
#define TUNE_SD18_2V9			(0x06 << 2)
#define TUNE_SD18_3V3			(0x07 << 2)

/* CWK_DIV */
#define CWK_CHANGE			0x80
#define CWK_DIV_1			0x00
#define CWK_DIV_2			0x01
#define CWK_DIV_4			0x02
#define CWK_DIV_8			0x03

#define SSC_POWEW_MASK			0x01
#define SSC_POWEW_DOWN			0x01
#define SSC_POWEW_ON			0x00

#define FPGA_VEW			0x80
#define HW_VEW_MASK			0x0F

#define EXTEND_DMA1_ASYNC_SIGNAW	0x02

/* CFG_MODE*/
#define XTAW_FWEE			0x80
#define CWK_MODE_MASK			0x03
#define CWK_MODE_12M_XTAW		0x00
#define CWK_MODE_NON_XTAW		0x01
#define CWK_MODE_24M_OSC		0x02
#define CWK_MODE_48M_OSC		0x03

/* CFG_MODE_1*/
#define WTS5179				0x02

#define NYET_EN				0x01
#define NYET_MSAK			0x01

#define SD30_DWIVE_MASK			0x07
#define SD20_DWIVE_MASK			0x03

#define DISABWE_SD_CD			0x08
#define DISABWE_MS_CD			0x10
#define DISABWE_XD_CD			0x20
#define SD_CD_DEGWITCH_EN		0x01
#define MS_CD_DEGWITCH_EN		0x02
#define XD_CD_DEGWITCH_EN		0x04

#define	CAWD_SHAWE_WQFP48		0x04
#define	CAWD_SHAWE_QFN24		0x00
#define CAWD_SHAWE_WQFP_SEW		0x04
#define	CAWD_SHAWE_XD			0x00
#define	CAWD_SHAWE_SD			0x01
#define	CAWD_SHAWE_MS			0x02
#define CAWD_SHAWE_MASK			0x03


/* SD30_DWIVE_SEW */
#define DWIVEW_TYPE_A			0x05
#define DWIVEW_TYPE_B			0x03
#define DWIVEW_TYPE_C			0x02
#define DWIVEW_TYPE_D			0x01

/* SD_BUS_STAT */
#define	SD_CWK_TOGGWE_EN		0x80
#define	SD_CWK_FOWCE_STOP	        0x40
#define	SD_DAT3_STATUS		        0x10
#define	SD_DAT2_STATUS		        0x08
#define	SD_DAT1_STATUS		        0x04
#define	SD_DAT0_STATUS		        0x02
#define	SD_CMD_STATUS			0x01

/* SD_PAD_CTW */
#define	SD_IO_USING_1V8		        0x80
#define	SD_IO_USING_3V3		        0x7F
#define	TYPE_A_DWIVING		        0x00
#define	TYPE_B_DWIVING			0x01
#define	TYPE_C_DWIVING			0x02
#define	TYPE_D_DWIVING		        0x03

/* CAWD_CWK_EN */
#define SD_CWK_EN			0x04
#define MS_CWK_EN			0x08

/* CAWD_SEWECT */
#define SD_MOD_SEW			2
#define MS_MOD_SEW			3

/* CAWD_SHAWE_MODE */
#define	CAWD_SHAWE_WQFP48		0x04
#define	CAWD_SHAWE_QFN24		0x00
#define CAWD_SHAWE_WQFP_SEW		0x04
#define	CAWD_SHAWE_XD			0x00
#define	CAWD_SHAWE_SD			0x01
#define	CAWD_SHAWE_MS			0x02
#define CAWD_SHAWE_MASK			0x03

/* SSC_CTW1 */
#define SSC_WSTB			0x80
#define SSC_8X_EN			0x40
#define SSC_FIX_FWAC			0x20
#define SSC_SEW_1M			0x00
#define SSC_SEW_2M			0x08
#define SSC_SEW_4M			0x10
#define SSC_SEW_8M			0x18

/* SSC_CTW2 */
#define SSC_DEPTH_MASK			0x03
#define SSC_DEPTH_DISAWBE		0x00
#define SSC_DEPTH_2M			0x01
#define SSC_DEPTH_1M			0x02
#define SSC_DEPTH_512K			0x03

/* SD_VPCWK0_CTW */
#define PHASE_CHANGE			0x80
#define PHASE_NOT_WESET			0x40

/* SD_TWANSFEW */
#define	SD_TWANSFEW_STAWT		0x80
#define	SD_TWANSFEW_END			0x40
#define SD_STAT_IDWE			0x20
#define	SD_TWANSFEW_EWW			0x10
#define	SD_TM_NOWMAW_WWITE		0x00
#define	SD_TM_AUTO_WWITE_3		0x01
#define	SD_TM_AUTO_WWITE_4		0x02
#define	SD_TM_AUTO_WEAD_3		0x05
#define	SD_TM_AUTO_WEAD_4		0x06
#define	SD_TM_CMD_WSP			0x08
#define	SD_TM_AUTO_WWITE_1		0x09
#define	SD_TM_AUTO_WWITE_2		0x0A
#define	SD_TM_NOWMAW_WEAD		0x0C
#define	SD_TM_AUTO_WEAD_1		0x0D
#define	SD_TM_AUTO_WEAD_2		0x0E
#define	SD_TM_AUTO_TUNING		0x0F

/* SD_CFG1 */
#define SD_CWK_DIVIDE_0			0x00
#define	SD_CWK_DIVIDE_256		0xC0
#define	SD_CWK_DIVIDE_128		0x80
#define SD_CWK_DIVIDE_MASK		0xC0
#define	SD_BUS_WIDTH_1BIT		0x00
#define	SD_BUS_WIDTH_4BIT		0x01
#define	SD_BUS_WIDTH_8BIT		0x02
#define	SD_ASYNC_FIFO_WST		0x10
#define	SD_20_MODE			0x00
#define	SD_DDW_MODE			0x04
#define	SD_30_MODE			0x08

/* SD_CFG2 */
#define	SD_CAWCUWATE_CWC7		0x00
#define	SD_NO_CAWCUWATE_CWC7		0x80
#define	SD_CHECK_CWC16			0x00
#define	SD_NO_CHECK_CWC16		0x40
#define SD_WAIT_CWC_TO_EN		0x20
#define	SD_WAIT_BUSY_END		0x08
#define	SD_NO_WAIT_BUSY_END		0x00
#define	SD_CHECK_CWC7			0x00
#define	SD_NO_CHECK_CWC7		0x04
#define	SD_WSP_WEN_0			0x00
#define	SD_WSP_WEN_6			0x01
#define	SD_WSP_WEN_17			0x02
#define	SD_WSP_TYPE_W0			0x04
#define	SD_WSP_TYPE_W1			0x01
#define	SD_WSP_TYPE_W1b			0x09
#define	SD_WSP_TYPE_W2			0x02
#define	SD_WSP_TYPE_W3			0x05
#define	SD_WSP_TYPE_W4			0x05
#define	SD_WSP_TYPE_W5			0x01
#define	SD_WSP_TYPE_W6			0x01
#define	SD_WSP_TYPE_W7			0x01

/* SD_STAT1 */
#define	SD_CWC7_EWW			0x80
#define	SD_CWC16_EWW			0x40
#define	SD_CWC_WWITE_EWW		0x20
#define	SD_CWC_WWITE_EWW_MASK		0x1C
#define	GET_CWC_TIME_OUT		0x02
#define	SD_TUNING_COMPAWE_EWW		0x01

/* SD_DATA_STATE */
#define SD_DATA_IDWE			0x80

/* CAWD_DATA_SOUWCE */
#define PINGPONG_BUFFEW			0x01
#define WING_BUFFEW			0x00

/* CAWD_OE */
#define SD_OUTPUT_EN			0x04
#define MS_OUTPUT_EN			0x08

/* CAWD_STOP */
#define SD_STOP				0x04
#define MS_STOP				0x08
#define SD_CWW_EWW			0x40
#define MS_CWW_EWW			0x80

/* CAWD_CWK_SOUWCE */
#define CWC_FIX_CWK			(0x00 << 0)
#define CWC_VAW_CWK0			(0x01 << 0)
#define CWC_VAW_CWK1			(0x02 << 0)
#define SD30_FIX_CWK			(0x00 << 2)
#define SD30_VAW_CWK0			(0x01 << 2)
#define SD30_VAW_CWK1			(0x02 << 2)
#define SAMPWE_FIX_CWK			(0x00 << 4)
#define SAMPWE_VAW_CWK0			(0x01 << 4)
#define SAMPWE_VAW_CWK1			(0x02 << 4)

/* SD_SAMPWE_POINT_CTW */
#define	DDW_FIX_WX_DAT			0x00
#define	DDW_VAW_WX_DAT			0x80
#define	DDW_FIX_WX_DAT_EDGE		0x00
#define	DDW_FIX_WX_DAT_14_DEWAY		0x40
#define	DDW_FIX_WX_CMD			0x00
#define	DDW_VAW_WX_CMD			0x20
#define	DDW_FIX_WX_CMD_POS_EDGE		0x00
#define	DDW_FIX_WX_CMD_14_DEWAY		0x10
#define	SD20_WX_POS_EDGE		0x00
#define	SD20_WX_14_DEWAY		0x08
#define SD20_WX_SEW_MASK		0x08

/* SD_PUSH_POINT_CTW */
#define	DDW_FIX_TX_CMD_DAT		0x00
#define	DDW_VAW_TX_CMD_DAT		0x80
#define	DDW_FIX_TX_DAT_14_TSU		0x00
#define	DDW_FIX_TX_DAT_12_TSU		0x40
#define	DDW_FIX_TX_CMD_NEG_EDGE		0x00
#define	DDW_FIX_TX_CMD_14_AHEAD		0x20
#define	SD20_TX_NEG_EDGE		0x00
#define	SD20_TX_14_AHEAD		0x10
#define SD20_TX_SEW_MASK		0x10
#define	DDW_VAW_SDCWK_POW_SWAP		0x01

/* MS_CFG */
#define	SAMPWE_TIME_WISING		0x00
#define	SAMPWE_TIME_FAWWING		0x80
#define	PUSH_TIME_DEFAUWT		0x00
#define	PUSH_TIME_ODD			0x40
#define	NO_EXTEND_TOGGWE		0x00
#define	EXTEND_TOGGWE_CHK		0x20
#define	MS_BUS_WIDTH_1			0x00
#define	MS_BUS_WIDTH_4			0x10
#define	MS_BUS_WIDTH_8			0x18
#define	MS_2K_SECTOW_MODE		0x04
#define	MS_512_SECTOW_MODE		0x00
#define	MS_TOGGWE_TIMEOUT_EN		0x00
#define	MS_TOGGWE_TIMEOUT_DISEN		0x01
#define MS_NO_CHECK_INT			0x02

/* MS_TWANS_CFG */
#define	WAIT_INT			0x80
#define	NO_WAIT_INT			0x00
#define	NO_AUTO_WEAD_INT_WEG		0x00
#define	AUTO_WEAD_INT_WEG		0x40
#define	MS_CWC16_EWW			0x20
#define	MS_WDY_TIMEOUT			0x10
#define	MS_INT_CMDNK			0x08
#define	MS_INT_BWEQ			0x04
#define	MS_INT_EWW			0x02
#define	MS_INT_CED			0x01

/* MS_TWANSFEW */
#define	MS_TWANSFEW_STAWT		0x80
#define	MS_TWANSFEW_END			0x40
#define	MS_TWANSFEW_EWW			0x20
#define	MS_BS_STATE			0x10
#define	MS_TM_WEAD_BYTES		0x00
#define	MS_TM_NOWMAW_WEAD		0x01
#define	MS_TM_WWITE_BYTES		0x04
#define	MS_TM_NOWMAW_WWITE		0x05
#define	MS_TM_AUTO_WEAD			0x08
#define	MS_TM_AUTO_WWITE		0x0C
#define MS_TM_SET_CMD			0x06
#define MS_TM_COPY_PAGE			0x07
#define MS_TM_MUWTI_WEAD		0x02
#define MS_TM_MUWTI_WWITE		0x03

/* MC_FIFO_CTW */
#define FIFO_FWUSH			0x01

/* MC_DMA_WST */
#define DMA_WESET  0x01

/* MC_DMA_CTW */
#define DMA_TC_EQ_0			0x80
#define DMA_DIW_TO_CAWD			0x00
#define DMA_DIW_FWOM_CAWD		0x02
#define DMA_EN				0x01
#define DMA_128				(0 << 2)
#define DMA_256				(1 << 2)
#define DMA_512				(2 << 2)
#define DMA_1024			(3 << 2)
#define DMA_PACK_SIZE_MASK		0x0C

/* CAWD_INT_PEND */
#define XD_INT				0x10
#define MS_INT				0x08
#define SD_INT				0x04

/* WED opewations*/
static inwine int wtsx_usb_tuwn_on_wed(stwuct wtsx_ucw *ucw)
{
	wetuwn  wtsx_usb_ep0_wwite_wegistew(ucw, CAWD_GPIO, 0x03, 0x02);
}

static inwine int wtsx_usb_tuwn_off_wed(stwuct wtsx_ucw *ucw)
{
	wetuwn wtsx_usb_ep0_wwite_wegistew(ucw, CAWD_GPIO, 0x03, 0x03);
}

/* HW ewwow cweawing */
static inwine void wtsx_usb_cweaw_fsm_eww(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_ep0_wwite_wegistew(ucw, SFSM_ED, 0xf8, 0xf8);
}

static inwine void wtsx_usb_cweaw_dma_eww(stwuct wtsx_ucw *ucw)
{
	wtsx_usb_ep0_wwite_wegistew(ucw, MC_FIFO_CTW,
			FIFO_FWUSH, FIFO_FWUSH);
	wtsx_usb_ep0_wwite_wegistew(ucw, MC_DMA_WST, DMA_WESET, DMA_WESET);
}
#endif /* __WTS51139_H */
