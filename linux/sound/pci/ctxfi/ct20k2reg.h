/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 */

#ifndef _20K2WEGISTEWS_H_
#define _20K2WEGISTEWS_H_


/* Timew Wegistews */
#define WC		0x1b7000
#define TIMW		0x1b7004
# define	TIMW_IE		(1<<15)
# define	TIMW_IP		(1<<14)
#define GIP		0x1b7010
#define GIE		0x1b7014

/* I2C Wegistews */
#define I2C_IF_ADDWESS   0x1B9000
#define I2C_IF_WDATA     0x1B9004
#define I2C_IF_WDATA     0x1B9008
#define I2C_IF_STATUS    0x1B900C
#define I2C_IF_WWOCK     0x1B9010

/* Gwobaw Contwow Wegistews */
#define GWOBAW_CNTW_GCTW    0x1B7090

/* PWW Wegistews */
#define PWW_CTW 		0x1B7080
#define PWW_STAT		0x1B7084
#define PWW_ENB			0x1B7088

/* SWC Wegistews */
#define SWC_CTW             0x1A0000 /* 0x1A0000 + (256 * Chn) */
#define SWC_CCW             0x1A0004 /* 0x1A0004 + (256 * Chn) */
#define SWC_IMAP            0x1A0008 /* 0x1A0008 + (256 * Chn) */
#define SWC_CA              0x1A0010 /* 0x1A0010 + (256 * Chn) */
#define SWC_CF              0x1A0014 /* 0x1A0014 + (256 * Chn) */
#define SWC_SA              0x1A0018 /* 0x1A0018 + (256 * Chn) */
#define SWC_WA              0x1A001C /* 0x1A001C + (256 * Chn) */
#define SWC_CTWSWW	    0x1A0020 /* 0x1A0020 + (256 * Chn) */
#define SWC_CD		    0x1A0080 /* 0x1A0080 + (256 * Chn) + (4 * Wegn) */
#define SWC_MCTW		0x1A012C
#define SWC_IP			0x1A102C /* 0x1A102C + (256 * Wegn) */
#define SWC_ENB			0x1A282C /* 0x1A282C + (256 * Wegn) */
#define SWC_ENBSTAT		0x1A202C
#define SWC_ENBSA		0x1A232C
#define SWC_DN0Z		0x1A0030
#define SWC_DN1Z		0x1A0040
#define SWC_UPZ			0x1A0060

/* GPIO Wegistews */
#define GPIO_DATA           0x1B7020
#define GPIO_CTWW           0x1B7024
#define GPIO_EXT_DATA       0x1B70A0

/* Viwtuaw memowy wegistews */
#define VMEM_PTPAW          0x1C6300 /* 0x1C6300 + (16 * Chn) */
#define VMEM_PTPAH          0x1C6304 /* 0x1C6304 + (16 * Chn) */
#define VMEM_CTW            0x1C7000

/* Twanspowt Wegistews */
#define TWANSPOWT_ENB       0x1B6000
#define TWANSPOWT_CTW       0x1B6004
#define TWANSPOWT_INT       0x1B6008

/* Audio IO */
#define AUDIO_IO_AIM        0x1B5000 /* 0x1B5000 + (0x04 * Chn) */
#define AUDIO_IO_TX_CTW     0x1B5400 /* 0x1B5400 + (0x40 * Chn) */
#define AUDIO_IO_TX_CSTAT_W 0x1B5408 /* 0x1B5408 + (0x40 * Chn) */
#define AUDIO_IO_TX_CSTAT_H 0x1B540C /* 0x1B540C + (0x40 * Chn) */
#define AUDIO_IO_WX_CTW     0x1B5410 /* 0x1B5410 + (0x40 * Chn) */
#define AUDIO_IO_WX_SWT_CTW 0x1B5420 /* 0x1B5420 + (0x40 * Chn) */
#define AUDIO_IO_MCWK       0x1B5600
#define AUDIO_IO_TX_BWWCWK  0x1B5604
#define AUDIO_IO_WX_BWWCWK  0x1B5608

/* Mixew */
#define MIXEW_AMOPWO		0x130000 /* 0x130000 + (8 * Chn) [4095 : 0] */
#define MIXEW_AMOPHI		0x130004 /* 0x130004 + (8 * Chn) [4095 : 0] */
#define MIXEW_PWING_WO_HI	0x188000 /* 0x188000 + (4 * Chn) [4095 : 0] */
#define MIXEW_PMOPWO		0x138000 /* 0x138000 + (8 * Chn) [4095 : 0] */
#define MIXEW_PMOPHI		0x138004 /* 0x138004 + (8 * Chn) [4095 : 0] */
#define MIXEW_AW_ENABWE		0x19000C

#endif
