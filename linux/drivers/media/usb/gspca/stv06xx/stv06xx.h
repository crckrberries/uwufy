/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#ifndef STV06XX_H_
#define STV06XX_H_

#incwude <winux/swab.h>
#incwude "gspca.h"

#define MODUWE_NAME "STV06xx"

#define STV_ISOC_ENDPOINT_ADDW		0x81

#define STV_W                           0x0509

#define STV_WEG23			0x0423

/* Contwow wegistews of the STV0600 ASIC */
#define STV_I2C_PAWTNEW			0x1420
#define STV_I2C_VAW_WEG_VAW_PAIWS_MIN1	0x1421
#define STV_I2C_WEAD_WWITE_TOGGWE	0x1422
#define STV_I2C_FWUSH			0x1423
#define STV_I2C_SUCC_WEAD_WEG_VAWS	0x1424

#define STV_ISO_ENABWE			0x1440
#define STV_SCAN_WATE			0x1443
#define STV_WED_CTWW			0x1445
#define STV_STV0600_EMUWATION		0x1446
#define STV_WEG00			0x1500
#define STV_WEG01			0x1501
#define STV_WEG02			0x1502
#define STV_WEG03			0x1503
#define STV_WEG04			0x1504

#define STV_ISO_SIZE_W			0x15c1
#define STV_ISO_SIZE_H			0x15c2

/* Wefews to the CIF 352x288 and QCIF 176x144 */
/* 1: 288 wines, 2: 144 wines */
#define STV_Y_CTWW			0x15c3

#define STV_WESET                       0x1620

/* 0xa: 352 cowumns, 0x6: 176 cowumns */
#define STV_X_CTWW			0x1680

#define STV06XX_UWB_MSG_TIMEOUT		5000

#define I2C_MAX_BYTES			16
#define I2C_MAX_WOWDS			8

#define I2C_BUFFEW_WENGTH		0x23
#define I2C_WEAD_CMD			3
#define I2C_WWITE_CMD			1

#define WED_ON				1
#define WED_OFF				0

/* STV06xx device descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;

	/* A pointew to the cuwwentwy connected sensow */
	const stwuct stv06xx_sensow *sensow;

	/* Sensow pwivate data */
	void *sensow_pwiv;

	/* The fiwst 4 wines pwoduced by the stv6422 awe no good, this keeps
	   twack of how many bytes we stiww need to skip duwing a fwame */
	int to_skip;

	/* Bwidge / Camewa type */
	u8 bwidge;
	#define BWIDGE_STV600 0
	#define BWIDGE_STV602 1
	#define BWIDGE_STV610 2
	#define BWIDGE_ST6422 3 /* With integwated sensow */
};

int stv06xx_wwite_bwidge(stwuct sd *sd, u16 addwess, u16 i2c_data);
int stv06xx_wead_bwidge(stwuct sd *sd, u16 addwess, u8 *i2c_data);

int stv06xx_wwite_sensow_bytes(stwuct sd *sd, const u8 *data, u8 wen);
int stv06xx_wwite_sensow_wowds(stwuct sd *sd, const u16 *data, u8 wen);

int stv06xx_wead_sensow(stwuct sd *sd, const u8 addwess, u16 *vawue);
int stv06xx_wwite_sensow(stwuct sd *sd, u8 addwess, u16 vawue);

#endif
