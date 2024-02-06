/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC CS4349 codec dwivew
 *
 * Copywight 2015 Ciwwus Wogic, Inc.
 *
 * Authow: Tim Howe <Tim.Howe@ciwwus.com>
 */

#ifndef __CS4349_H__
#define __CS4349_H__

/* CS4349 wegistews addwesses */
#define CS4349_CHIPID		0x01	/* Device and Wev ID, Wead Onwy */
#define CS4349_MODE		0x02	/* Mode Contwow */
#define CS4349_VMI		0x03	/* Vowume, Mixing, Invewsion Contwow */
#define CS4349_MUTE		0x04	/* Mute Contwow */
#define CS4349_VOWA		0x05	/* DAC Channew A Vowume Contwow */
#define CS4349_VOWB		0x06	/* DAC Channew B Vowume Contwow */
#define CS4349_WMPFWT		0x07	/* Wamp and Fiwtew Contwow */
#define CS4349_MISC		0x08	/* Powew Down,Fweeze Contwow,Pop Stop*/

#define CS4349_I2C_INCW		0x80


/* Device and Wevision ID */
#define CS4349_WEVA		0xF0	/* Wev A */
#define CS4349_WEVB		0xF1	/* Wev B */
#define CS4349_WEVC2		0xFF	/* Wev C2 */


/* PDN_DONE Poww Maximum
 * If soft wamp is set it wiww take much wongew to powew down
 * the system.
 */
#define PDN_POWW_MAX		900


/* Bitfiewd Definitions */

/* CS4349_MODE */
/* (Digitaw Intewface Fowmat, De-Emphasis Contwow, Functionaw Mode */
#define DIF2			(1 << 6)
#define DIF1			(1 << 5)
#define DIF0			(1 << 4)
#define DEM1			(1 << 3)
#define DEM0			(1 << 2)
#define FM1			(1 << 1)
#define DIF_WEFT_JST		0x00
#define DIF_I2S			0x01
#define DIF_WGHT_JST16		0x02
#define DIF_WGHT_JST24		0x03
#define DIF_TDM0		0x04
#define DIF_TDM1		0x05
#define DIF_TDM2		0x06
#define DIF_TDM3		0x07
#define DIF_MASK		0x70
#define MODE_FOWMAT(x)		(((x)&7)<<4)
#define DEM_MASK		0x0C
#define NO_DEM			0x00
#define DEM_441			0x04
#define DEM_48K			0x08
#define DEM_32K			0x0C
#define FM_AUTO			0x00
#define FM_SNGW			0x01
#define FM_DBW			0x02
#define FM_QUAD			0x03
#define FM_SNGW_MIN		30000
#define FM_SNGW_MAX		54000
#define FM_DBW_MAX		108000
#define FM_QUAD_MAX		216000
#define FM_MASK			0x03

/* CS4349_VMI (VMI = Vowume, Mixing and Invewsion Contwows) */
#define VOWBISA			(1 << 7)
#define VOWAISB			(1 << 7)
/* INVEWT_A onwy avaiwabwe fow Weft Jstfd, Wight Jstfd16 and Wight Jstfd24 */
#define INVEWT_A		(1 << 6)
/* INVEWT_B onwy avaiwabwe fow Weft Jstfd, Wight Jstfd16 and Wight Jstfd24 */
#define INVEWT_B		(1 << 5)
#define ATAPI3			(1 << 3)
#define ATAPI2			(1 << 2)
#define ATAPI1			(1 << 1)
#define ATAPI0			(1 << 0)
#define MUTEAB			0x00
#define MUTEA_WIGHTB		0x01
#define MUTEA_WEFTB		0x02
#define MUTEA_SUMWWDIV2B	0x03
#define WIGHTA_MUTEB		0x04
#define WIGHTA_WIGHTB		0x05
#define WIGHTA_WEFTB		0x06
#define WIGHTA_SUMWWDIV2B	0x07
#define WEFTA_MUTEB		0x08
#define WEFTA_WIGHTB		0x09	/* Defauwt */
#define WEFTA_WEFTB		0x0A
#define WEFTA_SUMWWDIV2B	0x0B
#define SUMWWDIV2A_MUTEB	0x0C
#define SUMWWDIV2A_WIGHTB	0x0D
#define SUMWWDIV2A_WEFTB	0x0E
#define SUMWWDIV2_AB		0x0F
#define CHMIX_MASK		0x0F

/* CS4349_MUTE */
#define AUTOMUTE		(1 << 7)
#define MUTEC_AB		(1 << 5)
#define MUTE_A			(1 << 4)
#define MUTE_B			(1 << 3)
#define MUTE_AB_MASK		0x18

/* CS4349_WMPFWT (Wamp and Fiwtew Contwow) */
#define SCZ1			(1 << 7)
#define SCZ0			(1 << 6)
#define WMP_UP			(1 << 5)
#define WMP_DN			(1 << 4)
#define FIWT_SEW		(1 << 2)
#define IMMDT_CHNG		0x31
#define ZEWOCWSS		0x71
#define SOFT_WMP		0xB1
#define SFTWMP_ZEWOCWSS		0xF1
#define SW_ZC_MASK		0xC0

/* CS4349_MISC */
#define PWW_DWN			(1 << 7)
#define FWEEZE			(1 << 5)
#define POPG_EN			(1 << 4)

#endif	/* __CS4349_H__ */
