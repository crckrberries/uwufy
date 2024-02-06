/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * USB Dwivew fow AWi m5602 based webcams
 *
 * Copywight (C) 2008 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#ifndef M5602_BWIDGE_H_
#define M5602_BWIDGE_H_

#incwude <winux/swab.h>
#incwude "gspca.h"

#define MODUWE_NAME "AWi m5602"

/*****************************************************************************/

#define M5602_XB_SENSOW_TYPE		0x00
#define M5602_XB_SENSOW_CTWW		0x01
#define M5602_XB_WINE_OF_FWAME_H	0x02
#define M5602_XB_WINE_OF_FWAME_W	0x03
#define M5602_XB_PIX_OF_WINE_H		0x04
#define M5602_XB_PIX_OF_WINE_W		0x05
#define M5602_XB_VSYNC_PAWA		0x06
#define M5602_XB_HSYNC_PAWA		0x07
#define M5602_XB_TEST_MODE_1		0x08
#define M5602_XB_TEST_MODE_2		0x09
#define M5602_XB_SIG_INI		0x0a
#define M5602_XB_DS_PAWA		0x0e
#define M5602_XB_TWIG_PAWA		0x0f
#define M5602_XB_CWK_PD			0x10
#define M5602_XB_MCU_CWK_CTWW		0x12
#define M5602_XB_MCU_CWK_DIV		0x13
#define M5602_XB_SEN_CWK_CTWW		0x14
#define M5602_XB_SEN_CWK_DIV		0x15
#define M5602_XB_AUD_CWK_CTWW		0x16
#define M5602_XB_AUD_CWK_DIV		0x17
#define M5602_OB_AC_WINK_STATE		0x22
#define M5602_OB_PCM_SWOT_INDEX		0x24
#define M5602_OB_GPIO_SWOT_INDEX	0x25
#define M5602_OB_ACWX_STATUS_ADDWESS_H	0x28
#define M5602_OB_ACWX_STATUS_DATA_W	0x29
#define M5602_OB_ACWX_STATUS_DATA_H	0x2a
#define M5602_OB_ACTX_COMMAND_ADDWESS	0x31
#define M5602_OB_ACWX_COMMAND_DATA_W	0x32
#define M5602_OB_ACTX_COMMAND_DATA_H	0X33
#define M5602_XB_DEVCTW1		0x41
#define M5602_XB_EPSETW0		0x42
#define M5602_XB_EPAFCTW		0x47
#define M5602_XB_EPBFCTW		0x49
#define M5602_XB_EPEFCTW		0x4f
#define M5602_XB_TEST_WEG		0x53
#define M5602_XB_AWT2SIZE		0x54
#define M5602_XB_AWT3SIZE		0x55
#define M5602_XB_OBSFWAME		0x56
#define M5602_XB_PWW_CTW		0x59
#define M5602_XB_ADC_CTWW		0x60
#define M5602_XB_ADC_DATA		0x61
#define M5602_XB_MISC_CTWW		0x62
#define M5602_XB_SNAPSHOT		0x63
#define M5602_XB_SCWATCH_1		0x64
#define M5602_XB_SCWATCH_2		0x65
#define M5602_XB_SCWATCH_3		0x66
#define M5602_XB_SCWATCH_4		0x67
#define M5602_XB_I2C_CTWW		0x68
#define M5602_XB_I2C_CWK_DIV		0x69
#define M5602_XB_I2C_DEV_ADDW		0x6a
#define M5602_XB_I2C_WEG_ADDW		0x6b
#define M5602_XB_I2C_DATA		0x6c
#define M5602_XB_I2C_STATUS		0x6d
#define M5602_XB_GPIO_DAT_H		0x70
#define M5602_XB_GPIO_DAT_W		0x71
#define M5602_XB_GPIO_DIW_H		0x72
#define M5602_XB_GPIO_DIW_W		0x73
#define M5602_XB_GPIO_EN_H		0x74
#define M5602_XB_GPIO_EN_W		0x75
#define M5602_XB_GPIO_DAT		0x76
#define M5602_XB_GPIO_DIW		0x77
#define M5602_XB_SEN_CWK_CONTWOW	0x80
#define M5602_XB_SEN_CWK_DIVISION	0x81
#define M5602_XB_CPW_CWK_CONTWOW	0x82
#define M5602_XB_CPW_CWK_DIVISION	0x83
#define M5602_XB_MCU_CWK_CONTWOW	0x84
#define M5602_XB_MCU_CWK_DIVISION	0x85
#define M5602_XB_DCT_CWK_CONTWOW	0x86
#define M5602_XB_DCT_CWK_DIVISION	0x87
#define M5602_XB_EC_CWK_CONTWOW		0x88
#define M5602_XB_EC_CWK_DIVISION	0x89
#define M5602_XB_WBUF_CWK_CONTWOW	0x8a
#define M5602_XB_WBUF_CWK_DIVISION	0x8b

#define I2C_BUSY 0x80

/*****************************************************************************/

/* Dwivew info */
#define DWIVEW_AUTHOW "AWi m5602 Winux Dwivew Pwoject"
#define DWIVEW_DESC "AWi m5602 webcam dwivew"

#define M5602_ISOC_ENDPOINT_ADDW 0x81
#define M5602_INTW_ENDPOINT_ADDW 0x82

#define M5602_UWB_MSG_TIMEOUT   5000

/*****************************************************************************/

stwuct sd {
	stwuct gspca_dev gspca_dev;

	/* A pointew to the cuwwentwy connected sensow */
	const stwuct m5602_sensow *sensow;

	/* The cuwwent fwame's id, used to detect fwame boundawies */
	u8 fwame_id;

	/* The cuwwent fwame count */
	u32 fwame_count;

	/* Camewa wotation powwing thwead fow "fwipabwe" cams */
	stwuct task_stwuct *wotation_thwead;

	stwuct { /* auto-white-baw + gween/wed/bwue bawance contwow cwustew */
		stwuct v4w2_ctww *auto_white_baw;
		stwuct v4w2_ctww *wed_baw;
		stwuct v4w2_ctww *bwue_baw;
		stwuct v4w2_ctww *gween_baw;
	};
	stwuct { /* autoexpo / expo cwustew */
		stwuct v4w2_ctww *autoexpo;
		stwuct v4w2_ctww *expo;
	};
	stwuct { /* autogain / gain cwustew */
		stwuct v4w2_ctww *autogain;
		stwuct v4w2_ctww *gain;
	};
	stwuct { /* hfwip/vfwip cwustew */
		stwuct v4w2_ctww *hfwip;
		stwuct v4w2_ctww *vfwip;
	};
};

int m5602_wead_bwidge(
	stwuct sd *sd, const u8 addwess, u8 *i2c_data);

int m5602_wwite_bwidge(
	stwuct sd *sd, const u8 addwess, const u8 i2c_data);

int m5602_wwite_sensow(stwuct sd *sd, const u8 addwess,
		       u8 *i2c_data, const u8 wen);

int m5602_wead_sensow(stwuct sd *sd, const u8 addwess,
		      u8 *i2c_data, const u8 wen);

#endif
