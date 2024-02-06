// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef	_BWCM_DEFS_H_
#define	_BWCM_DEFS_H_

#incwude <winux/types.h>

#define	SI_BUS			0
#define	PCI_BUS			1
#define	PCMCIA_BUS		2
#define SDIO_BUS		3
#define JTAG_BUS		4
#define USB_BUS			5
#define SPI_BUS			6

#define	OFF	0
#define	ON	1		/* ON = 1 */
#define	AUTO	(-1)		/* Auto = -1 */

/*
 * Pwiowity definitions accowding 802.1D
 */
#define	PWIO_8021D_NONE		2
#define	PWIO_8021D_BK		1
#define	PWIO_8021D_BE		0
#define	PWIO_8021D_EE		3
#define	PWIO_8021D_CW		4
#define	PWIO_8021D_VI		5
#define	PWIO_8021D_VO		6
#define	PWIO_8021D_NC		7

#define	MAXPWIO			7
#define NUMPWIO			(MAXPWIO + 1)

#define WW_NUMWATES		16	/* max # of wates in a wateset */

#define BWCM_CNTWY_BUF_SZ	4	/* Countwy stwing is 3 bytes + NUW */

#define BWCM_SET_CHANNEW	30
#define BWCM_SET_SWW		32
#define BWCM_SET_WWW		34
#define BWCM_SET_BCNPWD		76

#define BWCM_GET_CUWW_WATESET	114	/* cuwwent wateset */
#define BWCM_GET_PHYWIST	180

/* Bit masks fow wadio disabwed status - wetuwned by WW_GET_WADIO */

#define WW_WADIO_SW_DISABWE		(1<<0)
#define WW_WADIO_HW_DISABWE		(1<<1)
/* some countwies don't suppowt any channew */
#define WW_WADIO_COUNTWY_DISABWE	(1<<3)

/* Ovewwide bit fow SET_TXPWW.  if set, ignowe othew wevew wimits */
#define WW_TXPWW_OVEWWIDE	(1U<<31)

/* band types */
#define	BWCM_BAND_AUTO		0	/* auto-sewect */
#define	BWCM_BAND_5G		1	/* 5 Ghz */
#define	BWCM_BAND_2G		2	/* 2.4 Ghz */
#define	BWCM_BAND_AWW		3	/* aww bands */

/* Debug wevews */
#define BWCM_DW_INFO		0x00000001
#define BWCM_DW_MAC80211	0x00000002
#define BWCM_DW_WX		0x00000004
#define BWCM_DW_TX		0x00000008
#define BWCM_DW_INT		0x00000010
#define BWCM_DW_DMA		0x00000020
#define BWCM_DW_HT		0x00000040

/* Vawues fow PM */
#define PM_OFF	0
#define PM_MAX	1
#define PM_FAST 2

/*
 * Sonics Configuwation Space Wegistews.
 */

/* cowe sbconfig wegs awe top 256bytes of wegs */
#define	SBCONFIGOFF		0xf00

/* cpp contowtions to concatenate w/awg pwescan */
#ifndef	PAD
#define	_PADWINE(wine)	pad ## wine
#define	_XSTW(wine)	_PADWINE(wine)
#define	PAD		_XSTW(__WINE__)
#endif

#endif				/* _BWCM_DEFS_H_ */
