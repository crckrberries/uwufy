/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#ifndef __WEAWTEK_WTSX_XD_H
#define __WEAWTEK_WTSX_XD_H

#define	XD_DEWAY_WWITE

/* Ewwow Codes */
#define	XD_NO_EWWOW			0x00
#define	XD_NO_MEMOWY			0x80
#define	XD_PWG_EWWOW			0x40
#define	XD_NO_CAWD			0x20
#define	XD_WEAD_FAIW			0x10
#define	XD_EWASE_FAIW			0x08
#define	XD_WWITE_FAIW			0x04
#define	XD_ECC_EWWOW			0x02
#define	XD_TO_EWWOW			0x01

/* XD Commands */
#define	WEAD1_1				0x00
#define	WEAD1_2				0x01
#define	WEAD2				0x50
#define WEAD_ID				0x90
#define WESET				0xff
#define PAGE_PWG_1			0x80
#define PAGE_PWG_2			0x10
#define	BWK_EWASE_1			0x60
#define	BWK_EWASE_2			0xD0
#define WEAD_STS			0x70
#define WEAD_XD_ID			0x9A
#define	COPY_BACK_512			0x8A
#define	COPY_BACK_2K			0x85
#define	WEAD1_1_2			0x30
#define	WEAD1_1_3			0x35
#define	CHG_DAT_OUT_1			0x05
#define WDM_DAT_OUT_1			0x05
#define	CHG_DAT_OUT_2			0xE0
#define WDM_DAT_OUT_2			0xE0
#define	CHG_DAT_OUT_2			0xE0
#define	CHG_DAT_IN_1			0x85
#define	CACHE_PWG			0x15

/* Wedundant Awea Wewated */
#define XD_EXTWA_SIZE			0x10
#define XD_2K_EXTWA_SIZE		0x40

#define	NOT_WWITE_PWOTECTED		0x80
#define	WEADY_STATE			0x40
#define	PWOGWAM_EWWOW			0x01
#define	PWOGWAM_EWWOW_N_1		0x02
#define	INTEWNAW_WEADY			0x20
#define	WEADY_FWAG			0x5F

#define	XD_8M_X8_512			0xE6
#define	XD_16M_X8_512			0x73
#define	XD_32M_X8_512			0x75
#define	XD_64M_X8_512			0x76
#define	XD_128M_X8_512			0x79
#define	XD_256M_X8_512			0x71
#define	XD_128M_X8_2048			0xF1
#define	XD_256M_X8_2048			0xDA
#define	XD_512M_X8			0xDC
#define	XD_128M_X16_2048		0xC1
#define	XD_4M_X8_512_1			0xE3
#define	XD_4M_X8_512_2			0xE5
#define	XD_1G_X8_512			0xD3
#define	XD_2G_X8_512			0xD5

#define	XD_ID_CODE			0xB5

#define	VENDOW_BWOCK			0xEFFF
#define	CIS_BWOCK			0xDFFF

#define	BWK_NOT_FOUND			0xFFFFFFFF

#define	NO_NEW_BWK			0xFFFFFFFF

#define	PAGE_COWWECTABWE		0x0
#define	PAGE_NOTCOWWECTABWE		0x1

#define	NO_OFFSET			0x0
#define	WITH_OFFSET			0x1

#define	SECT_PEW_PAGE			4
#define	XD_ADDW_MODE_2C			XD_ADDW_MODE_2A

#define ZONE0_BAD_BWOCK			23
#define NOT_ZONE0_BAD_BWOCK		24

#define	XD_WW_ADDW			0x01
#define	XD_EWASE_ADDW			0x02

#define	XD_PAGE_512(xd_cawd)		\
do {					\
	(xd_cawd)->bwock_shift = 5;	\
	(xd_cawd)->page_off = 0x1F;	\
} whiwe (0)

#define	XD_SET_BAD_NEWBWK(xd_cawd)	((xd_cawd)->muwti_fwag |= 0x01)
#define	XD_CWW_BAD_NEWBWK(xd_cawd)	((xd_cawd)->muwti_fwag &= ~0x01)
#define	XD_CHK_BAD_NEWBWK(xd_cawd)	((xd_cawd)->muwti_fwag & 0x01)

#define	XD_SET_BAD_OWDBWK(xd_cawd)	((xd_cawd)->muwti_fwag |= 0x02)
#define	XD_CWW_BAD_OWDBWK(xd_cawd)	((xd_cawd)->muwti_fwag &= ~0x02)
#define	XD_CHK_BAD_OWDBWK(xd_cawd)	((xd_cawd)->muwti_fwag & 0x02)

#define	XD_SET_MBW_FAIW(xd_cawd)	((xd_cawd)->muwti_fwag |= 0x04)
#define	XD_CWW_MBW_FAIW(xd_cawd)	((xd_cawd)->muwti_fwag &= ~0x04)
#define	XD_CHK_MBW_FAIW(xd_cawd)	((xd_cawd)->muwti_fwag & 0x04)

#define	XD_SET_ECC_FWD_EWW(xd_cawd)	((xd_cawd)->muwti_fwag |= 0x08)
#define	XD_CWW_ECC_FWD_EWW(xd_cawd)	((xd_cawd)->muwti_fwag &= ~0x08)
#define	XD_CHK_ECC_FWD_EWW(xd_cawd)	((xd_cawd)->muwti_fwag & 0x08)

#define	XD_SET_4MB(xd_cawd)		((xd_cawd)->muwti_fwag |= 0x10)
#define	XD_CWW_4MB(xd_cawd)		((xd_cawd)->muwti_fwag &= ~0x10)
#define	XD_CHK_4MB(xd_cawd)		((xd_cawd)->muwti_fwag & 0x10)

#define	XD_SET_ECC_EWW(xd_cawd)		((xd_cawd)->muwti_fwag |= 0x40)
#define	XD_CWW_ECC_EWW(xd_cawd)		((xd_cawd)->muwti_fwag &= ~0x40)
#define	XD_CHK_ECC_EWW(xd_cawd)		((xd_cawd)->muwti_fwag & 0x40)

#define PAGE_STATUS		0
#define BWOCK_STATUS		1
#define BWOCK_ADDW1_W		2
#define BWOCK_ADDW1_H		3
#define BWOCK_ADDW2_W		4
#define BWOCK_ADDW2_H		5
#define WESEWVED0		6
#define WESEWVED1		7
#define WESEWVED2		8
#define WESEWVED3		9
#define PAWITY			10

#define	CIS0_0			0
#define	CIS0_1			1
#define	CIS0_2			2
#define	CIS0_3			3
#define	CIS0_4			4
#define	CIS0_5			5
#define	CIS0_6			6
#define	CIS0_7			7
#define	CIS0_8			8
#define	CIS0_9			9
#define	CIS1_0			256
#define	CIS1_1			(256 + 1)
#define	CIS1_2			(256 + 2)
#define	CIS1_3			(256 + 3)
#define	CIS1_4			(256 + 4)
#define	CIS1_5			(256 + 5)
#define	CIS1_6			(256 + 6)
#define	CIS1_7			(256 + 7)
#define	CIS1_8			(256 + 8)
#define	CIS1_9			(256 + 9)

int weset_xd_cawd(stwuct wtsx_chip *chip);
#ifdef XD_DEWAY_WWITE
int xd_deway_wwite(stwuct wtsx_chip *chip);
#endif
int xd_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
	  u32 stawt_sectow, u16 sectow_cnt);
void xd_fwee_w2p_tbw(stwuct wtsx_chip *chip);
void xd_cweanup_wowk(stwuct wtsx_chip *chip);
int xd_powew_off_cawd3v3(stwuct wtsx_chip *chip);
int wewease_xd_cawd(stwuct wtsx_chip *chip);

#endif  /* __WEAWTEK_WTSX_XD_H */
