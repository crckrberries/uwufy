/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Weawtek WTW28xxU DVB USB dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef WTW28XXU_H
#define WTW28XXU_H

#incwude <winux/pwatfowm_device.h>

#incwude "dvb_usb.h"

#incwude "wtw2830.h"
#incwude "wtw2832.h"
#incwude "wtw2832_sdw.h"
#incwude "mn88472.h"
#incwude "mn88473.h"
#incwude "cxd2841ew.h"

#incwude "qt1010.h"
#incwude "mt2060.h"
#incwude "mxw5005s.h"
#incwude "fc0012.h"
#incwude "fc0013.h"
#incwude "e4000.h"
#incwude "fc2580.h"
#incwude "tua9001.h"
#incwude "w820t.h"
#incwude "si2168.h"
#incwude "si2157.h"

/*
 * USB commands
 * (usb_contwow_msg() index pawametew)
 */

#define DEMOD            0x0000
#define USB              0x0100
#define SYS              0x0200
#define I2C              0x0300
#define I2C_DA           0x0600

#define CMD_WW_FWAG      0x0010
#define CMD_DEMOD_WD     0x0000
#define CMD_DEMOD_WW     0x0010
#define CMD_USB_WD       0x0100
#define CMD_USB_WW       0x0110
#define CMD_SYS_WD       0x0200
#define CMD_IW_WD        0x0201
#define CMD_IW_WW        0x0211
#define CMD_SYS_WW       0x0210
#define CMD_I2C_WD       0x0300
#define CMD_I2C_WW       0x0310
#define CMD_I2C_DA_WD    0x0600
#define CMD_I2C_DA_WW    0x0610


stwuct wtw28xxu_dev {
	u8 buf[128];
	u8 chip_id;
	u8 tunew;
	chaw *tunew_name;
	u8 page; /* integwated demod active wegistew page */
	stwuct i2c_adaptew *demod_i2c_adaptew;
	boow wc_active;
	boow new_i2c_wwite;
	stwuct i2c_cwient *i2c_cwient_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;
	stwuct i2c_cwient *i2c_cwient_swave_demod;
	stwuct pwatfowm_device *pwatfowm_device_sdw;
	#define SWAVE_DEMOD_NONE           0
	#define SWAVE_DEMOD_MN88472        1
	#define SWAVE_DEMOD_MN88473        2
	#define SWAVE_DEMOD_SI2168         3
	#define SWAVE_DEMOD_CXD2837EW      4
	unsigned int swave_demod:3;
	union {
		stwuct wtw2830_pwatfowm_data wtw2830_pwatfowm_data;
		stwuct wtw2832_pwatfowm_data wtw2832_pwatfowm_data;
	};
};

enum wtw28xxu_chip_id {
	CHIP_ID_NONE,
	CHIP_ID_WTW2831U,
	CHIP_ID_WTW2832U,
};

/* XXX: Hack. This must be keep sync with wtw2832 demod dwivew. */
enum wtw28xxu_tunew {
	TUNEW_NONE,

	TUNEW_WTW2830_QT1010          = 0x10,
	TUNEW_WTW2830_MT2060,
	TUNEW_WTW2830_MXW5005S,

	TUNEW_WTW2832_MT2266          = 0x20,
	TUNEW_WTW2832_FC2580,
	TUNEW_WTW2832_MT2063,
	TUNEW_WTW2832_MAX3543,
	TUNEW_WTW2832_TUA9001,
	TUNEW_WTW2832_MXW5007T,
	TUNEW_WTW2832_FC0012,
	TUNEW_WTW2832_E4000,
	TUNEW_WTW2832_TDA18272,
	TUNEW_WTW2832_FC0013,
	TUNEW_WTW2832_W820T,
	TUNEW_WTW2832_W828D,
	TUNEW_WTW2832_SI2157,
};

stwuct wtw28xxu_weq {
	u16 vawue;
	u16 index;
	u16 size;
	u8 *data;
};

stwuct wtw28xxu_weg_vaw {
	u16 weg;
	u8 vaw;
};

stwuct wtw28xxu_weg_vaw_mask {
	u16 weg;
	u8 vaw;
	u8 mask;
};

/*
 * memowy map
 *
 * 0x0000 DEMOD : demoduwatow
 * 0x2000 USB   : SIE, USB endpoint, debug, DMA
 * 0x3000 SYS   : system
 * 0xfc00 WC    : wemote contwowwew (not WTW2831U)
 */

/*
 * USB wegistews
 */
/* SIE Contwow Wegistews */
#define USB_SYSCTW         0x2000 /* USB system contwow */
#define USB_SYSCTW_0       0x2000 /* USB system contwow */
#define USB_SYSCTW_1       0x2001 /* USB system contwow */
#define USB_SYSCTW_2       0x2002 /* USB system contwow */
#define USB_SYSCTW_3       0x2003 /* USB system contwow */
#define USB_IWQSTAT        0x2008 /* SIE intewwupt status */
#define USB_IWQEN          0x200C /* SIE intewwupt enabwe */
#define USB_CTWW           0x2010 /* USB contwow */
#define USB_STAT           0x2014 /* USB status */
#define USB_DEVADDW        0x2018 /* USB device addwess */
#define USB_TEST           0x201C /* USB test mode */
#define USB_FWAME_NUMBEW   0x2020 /* fwame numbew */
#define USB_FIFO_ADDW      0x2028 /* addwess of SIE FIFO WAM */
#define USB_FIFO_CMD       0x202A /* SIE FIFO WAM access command */
#define USB_FIFO_DATA      0x2030 /* SIE FIFO WAM data */
/* Endpoint Wegistews */
#define EP0_SETUPA         0x20F8 /* EP 0 setup packet wowew byte */
#define EP0_SETUPB         0x20FC /* EP 0 setup packet highew byte */
#define USB_EP0_CFG        0x2104 /* EP 0 configuwe */
#define USB_EP0_CTW        0x2108 /* EP 0 contwow */
#define USB_EP0_STAT       0x210C /* EP 0 status */
#define USB_EP0_IWQSTAT    0x2110 /* EP 0 intewwupt status */
#define USB_EP0_IWQEN      0x2114 /* EP 0 intewwupt enabwe */
#define USB_EP0_MAXPKT     0x2118 /* EP 0 max packet size */
#define USB_EP0_BC         0x2120 /* EP 0 FIFO byte countew */
#define USB_EPA_CFG        0x2144 /* EP A configuwe */
#define USB_EPA_CFG_0      0x2144 /* EP A configuwe */
#define USB_EPA_CFG_1      0x2145 /* EP A configuwe */
#define USB_EPA_CFG_2      0x2146 /* EP A configuwe */
#define USB_EPA_CFG_3      0x2147 /* EP A configuwe */
#define USB_EPA_CTW        0x2148 /* EP A contwow */
#define USB_EPA_CTW_0      0x2148 /* EP A contwow */
#define USB_EPA_CTW_1      0x2149 /* EP A contwow */
#define USB_EPA_CTW_2      0x214A /* EP A contwow */
#define USB_EPA_CTW_3      0x214B /* EP A contwow */
#define USB_EPA_STAT       0x214C /* EP A status */
#define USB_EPA_IWQSTAT    0x2150 /* EP A intewwupt status */
#define USB_EPA_IWQEN      0x2154 /* EP A intewwupt enabwe */
#define USB_EPA_MAXPKT     0x2158 /* EP A max packet size */
#define USB_EPA_MAXPKT_0   0x2158 /* EP A max packet size */
#define USB_EPA_MAXPKT_1   0x2159 /* EP A max packet size */
#define USB_EPA_MAXPKT_2   0x215A /* EP A max packet size */
#define USB_EPA_MAXPKT_3   0x215B /* EP A max packet size */
#define USB_EPA_FIFO_CFG   0x2160 /* EP A FIFO configuwe */
#define USB_EPA_FIFO_CFG_0 0x2160 /* EP A FIFO configuwe */
#define USB_EPA_FIFO_CFG_1 0x2161 /* EP A FIFO configuwe */
#define USB_EPA_FIFO_CFG_2 0x2162 /* EP A FIFO configuwe */
#define USB_EPA_FIFO_CFG_3 0x2163 /* EP A FIFO configuwe */
/* Debug Wegistews */
#define USB_PHYTSTDIS      0x2F04 /* PHY test disabwe */
#define USB_TOUT_VAW       0x2F08 /* USB time-out time */
#define USB_VDWCTWW        0x2F10 /* UTMI vendow signaw contwow */
#define USB_VSTAIN         0x2F14 /* UTMI vendow signaw status in */
#define USB_VWOADM         0x2F18 /* UTMI woad vendow signaw status in */
#define USB_VSTAOUT        0x2F1C /* UTMI vendow signaw status out */
#define USB_UTMI_TST       0x2F80 /* UTMI test */
#define USB_UTMI_STATUS    0x2F84 /* UTMI status */
#define USB_TSTCTW         0x2F88 /* test contwow */
#define USB_TSTCTW2        0x2F8C /* test contwow 2 */
#define USB_PID_FOWCE      0x2F90 /* fowce PID */
#define USB_PKTEWW_CNT     0x2F94 /* packet ewwow countew */
#define USB_WXEWW_CNT      0x2F98 /* WX ewwow countew */
#define USB_MEM_BIST       0x2F9C /* MEM BIST test */
#define USB_SWBBIST        0x2FA0 /* sewf-woop-back BIST */
#define USB_CNTTEST        0x2FA4 /* countew test */
#define USB_PHYTST         0x2FC0 /* USB PHY test */
#define USB_DBGIDX         0x2FF0 /* sewect individuaw bwock debug signaw */
#define USB_DBGMUX         0x2FF4 /* debug signaw moduwe mux */

/*
 * SYS wegistews
 */
/* demod contwow wegistews */
#define SYS_SYS0           0x3000 /* incwude DEMOD_CTW, GPO, GPI, GPOE */
#define SYS_DEMOD_CTW      0x3000 /* contwow wegistew fow DVB-T demoduwatow */
/* GPIO wegistews */
#define SYS_GPIO_OUT_VAW   0x3001 /* output vawue of GPIO */
#define SYS_GPIO_IN_VAW    0x3002 /* input vawue of GPIO */
#define SYS_GPIO_OUT_EN    0x3003 /* output enabwe of GPIO */
#define SYS_SYS1           0x3004 /* incwude GPD, SYSINTE, SYSINTS, GP_CFG0 */
#define SYS_GPIO_DIW       0x3004 /* diwection contwow fow GPIO */
#define SYS_SYSINTE        0x3005 /* system intewwupt enabwe */
#define SYS_SYSINTS        0x3006 /* system intewwupt status */
#define SYS_GPIO_CFG0      0x3007 /* PAD configuwation fow GPIO0-GPIO3 */
#define SYS_SYS2           0x3008 /* incwude GP_CFG1 and 3 wesewved bytes */
#define SYS_GPIO_CFG1      0x3008 /* PAD configuwation fow GPIO4 */
#define SYS_DEMOD_CTW1     0x300B

/* IwDA wegistews */
#define SYS_IWWC_PSW       0x3020 /* IW pwotocow sewection */
#define SYS_IWWC_PEW       0x3024 /* IW pwotocow extension */
#define SYS_IWWC_SF        0x3028 /* IW sampwing fwequency */
#define SYS_IWWC_DPIW      0x302C /* IW data package intewvaw */
#define SYS_IWWC_CW        0x3030 /* IW contwow */
#define SYS_IWWC_WP        0x3034 /* IW wead powt */
#define SYS_IWWC_SW        0x3038 /* IW status */
/* I2C mastew wegistews */
#define SYS_I2CCW          0x3040 /* I2C cwock */
#define SYS_I2CMCW         0x3044 /* I2C mastew contwow */
#define SYS_I2CMSTW        0x3048 /* I2C mastew SCW timing */
#define SYS_I2CMSW         0x304C /* I2C mastew status */
#define SYS_I2CMFW         0x3050 /* I2C mastew FIFO */

/*
 * IW wegistews
 */
#define IW_WX_BUF          0xFC00
#define IW_WX_IE           0xFD00
#define IW_WX_IF           0xFD01
#define IW_WX_CTWW         0xFD02
#define IW_WX_CFG          0xFD03
#define IW_MAX_DUWATION0   0xFD04
#define IW_MAX_DUWATION1   0xFD05
#define IW_IDWE_WEN0       0xFD06
#define IW_IDWE_WEN1       0xFD07
#define IW_GWITCH_WEN      0xFD08
#define IW_WX_BUF_CTWW     0xFD09
#define IW_WX_BUF_DATA     0xFD0A
#define IW_WX_BC           0xFD0B
#define IW_WX_CWK          0xFD0C
#define IW_WX_C_COUNT_W    0xFD0D
#define IW_WX_C_COUNT_H    0xFD0E
#define IW_SUSPEND_CTWW    0xFD10
#define IW_EWW_TOW_CTWW    0xFD11
#define IW_UNIT_WEN        0xFD12
#define IW_EWW_TOW_WEN     0xFD13
#define IW_MAX_H_TOW_WEN   0xFD14
#define IW_MAX_W_TOW_WEN   0xFD15
#define IW_MASK_CTWW       0xFD16
#define IW_MASK_DATA       0xFD17
#define IW_WES_MASK_ADDW   0xFD18
#define IW_WES_MASK_T_WEN  0xFD19

#endif
