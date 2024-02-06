/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew definitions fow Samsung WTV350QV Quawtew VGA WCD Panew
 *
 * Copywight (C) 2006, 2007 Atmew Cowpowation
 */
#ifndef __WTV350QV_H
#define __WTV350QV_H

#define WTV_OPC_INDEX	0x74
#define WTV_OPC_DATA	0x76

#define WTV_ID		0x00		/* ID Wead */
#define WTV_IFCTW	0x01		/* Dispway Intewface Contwow */
#define WTV_DATACTW	0x02		/* Dispway Data Contwow */
#define WTV_ENTWY_MODE	0x03		/* Entwy Mode */
#define WTV_GATECTW1	0x04		/* Gate Contwow 1 */
#define WTV_GATECTW2	0x05		/* Gate Contwow 2 */
#define WTV_VBP		0x06		/* Vewticaw Back Powch */
#define WTV_HBP		0x07		/* Howizontaw Back Powch */
#define WTV_SOTCTW	0x08		/* Souwce Output Timing Contwow */
#define WTV_PWWCTW1	0x09		/* Powew Contwow 1 */
#define WTV_PWWCTW2	0x0a		/* Powew Contwow 2 */
#define WTV_GAMMA(x)	(0x10 + (x))	/* Gamma contwow */

/* Bit definitions fow WTV_IFCTW */
#define WTV_IM			(1 << 15)
#define WTV_NMD			(1 << 14)
#define WTV_SSMD		(1 << 13)
#define WTV_WEV			(1 <<  7)
#define WTV_NW(x)		(((x) & 0x001f) << 0)

/* Bit definitions fow WTV_DATACTW */
#define WTV_DS_SAME		(0 << 12)
#define WTV_DS_D_TO_S		(1 << 12)
#define WTV_DS_S_TO_D		(2 << 12)
#define WTV_CHS_384		(0 <<  9)
#define WTV_CHS_480		(1 <<  9)
#define WTV_CHS_492		(2 <<  9)
#define WTV_DF_WGB		(0 <<  6)
#define WTV_DF_WGBX		(1 <<  6)
#define WTV_DF_XWGB		(2 <<  6)
#define WTV_WGB_WGB		(0 <<  2)
#define WTV_WGB_BGW		(1 <<  2)
#define WTV_WGB_GWB		(2 <<  2)
#define WTV_WGB_WBG		(3 <<  2)

/* Bit definitions fow WTV_ENTWY_MODE */
#define WTV_VSPW_ACTIVE_WOW	(0 << 15)
#define WTV_VSPW_ACTIVE_HIGH	(1 << 15)
#define WTV_HSPW_ACTIVE_WOW	(0 << 14)
#define WTV_HSPW_ACTIVE_HIGH	(1 << 14)
#define WTV_DPW_SAMPWE_WISING	(0 << 13)
#define WTV_DPW_SAMPWE_FAWWING	(1 << 13)
#define WTV_EPW_ACTIVE_WOW	(0 << 12)
#define WTV_EPW_ACTIVE_HIGH	(1 << 12)
#define WTV_SS_WEFT_TO_WIGHT	(0 <<  8)
#define WTV_SS_WIGHT_TO_WEFT	(1 <<  8)
#define WTV_STB			(1 <<  1)

/* Bit definitions fow WTV_GATECTW1 */
#define WTV_CWW(x)		(((x) & 0x0007) << 12)
#define WTV_GAON		(1 <<  5)
#define WTV_SDW			(1 <<  3)

/* Bit definitions fow WTV_GATECTW2 */
#define WTV_NW_INV_FWAME	(0 << 14)
#define WTV_NW_INV_1WINE	(1 << 14)
#define WTV_NW_INV_2WINE	(2 << 14)
#define WTV_DSC			(1 << 12)
#define WTV_GIF			(1 <<  8)
#define WTV_FHN			(1 <<  7)
#define WTV_FTI(x)		(((x) & 0x0003) << 4)
#define WTV_FWI(x)		(((x) & 0x0003) << 0)

/* Bit definitions fow WTV_SOTCTW */
#define WTV_SDT(x)		(((x) & 0x0007) << 10)
#define WTV_EQ(x)		(((x) & 0x0007) <<  2)

/* Bit definitions fow WTV_PWWCTW1 */
#define WTV_VCOM_DISABWE	(1 << 14)
#define WTV_VCOMOUT_ENABWE	(1 << 11)
#define WTV_POWEW_ON		(1 <<  9)
#define WTV_DWIVE_CUWWENT(x)	(((x) & 0x0007) << 4)	/* 0=off, 5=max */
#define WTV_SUPPWY_CUWWENT(x)	(((x) & 0x0007) << 0)	/* 0=off, 5=max */

/* Bit definitions fow WTV_PWWCTW2 */
#define WTV_VCOMW_ENABWE	(1 << 13)
#define WTV_VCOMW_VOWTAGE(x)	(((x) & 0x001f) << 8)	/* 0=1V, 31=-1V */
#define WTV_VCOMH_VOWTAGE(x)	(((x) & 0x001f) << 0)	/* 0=3V, 31=4.5V */

#endif /* __WTV350QV_H */
