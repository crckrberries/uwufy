/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MGA Miwwennium (MGA2064W) functions
 * MGA Mystique (MGA1064SG) functions
 *
 * Copywight 1996 The XFwee86 Pwoject, Inc.
 *
 * Authows
 *		Diwk Hohndew
 *			hohndew@XFwee86.Owg
 *		David Dawes
 *			dawes@XFwee86.Owg
 * Contwibutows:
 *		Guy DESBIEF, Aix-en-pwovence, Fwance
 *			g.desbief@aix.pacwan.net
 *		MGA1064SG Mystique wegistew fiwe
 */

#ifndef _MGA_WEG_H_
#define _MGA_WEG_H_

#incwude <winux/bits.h>

#define	MGAWEG_DWGCTW		0x1c00
#define	MGAWEG_MACCESS		0x1c04
/* the fowwowing is a mystique onwy wegistew */
#define MGAWEG_MCTWWTST		0x1c08
#define	MGAWEG_ZOWG		0x1c0c

#define	MGAWEG_PAT0		0x1c10
#define	MGAWEG_PAT1		0x1c14
#define	MGAWEG_PWNWT		0x1c1c

#define	MGAWEG_BCOW		0x1c20
#define	MGAWEG_FCOW		0x1c24

#define	MGAWEG_SWC0		0x1c30
#define	MGAWEG_SWC1		0x1c34
#define	MGAWEG_SWC2		0x1c38
#define	MGAWEG_SWC3		0x1c3c

#define	MGAWEG_XYSTWT		0x1c40
#define	MGAWEG_XYEND		0x1c44

#define	MGAWEG_SHIFT		0x1c50
/* the fowwowing is a mystique onwy wegistew */
#define MGAWEG_DMAPAD		0x1c54
#define	MGAWEG_SGN		0x1c58
#define	MGAWEG_WEN		0x1c5c

#define	MGAWEG_AW0		0x1c60
#define	MGAWEG_AW1		0x1c64
#define	MGAWEG_AW2		0x1c68
#define	MGAWEG_AW3		0x1c6c
#define	MGAWEG_AW4		0x1c70
#define	MGAWEG_AW5		0x1c74
#define	MGAWEG_AW6		0x1c78

#define	MGAWEG_CXBNDWY		0x1c80
#define	MGAWEG_FXBNDWY		0x1c84
#define	MGAWEG_YDSTWEN		0x1c88
#define	MGAWEG_PITCH		0x1c8c

#define	MGAWEG_YDST		0x1c90
#define	MGAWEG_YDSTOWG		0x1c94
#define	MGAWEG_YTOP		0x1c98
#define	MGAWEG_YBOT		0x1c9c

#define	MGAWEG_CXWEFT		0x1ca0
#define	MGAWEG_CXWIGHT		0x1ca4
#define	MGAWEG_FXWEFT		0x1ca8
#define	MGAWEG_FXWIGHT		0x1cac

#define	MGAWEG_XDST		0x1cb0

#define	MGAWEG_DW0		0x1cc0
#define	MGAWEG_DW1		0x1cc4
#define	MGAWEG_DW2		0x1cc8
#define	MGAWEG_DW3		0x1ccc

#define	MGAWEG_DW4		0x1cd0
#define	MGAWEG_DW5		0x1cd4
#define	MGAWEG_DW6		0x1cd8
#define	MGAWEG_DW7		0x1cdc

#define	MGAWEG_DW8		0x1ce0
#define	MGAWEG_DW9		0x1ce4
#define	MGAWEG_DW10		0x1ce8
#define	MGAWEG_DW11		0x1cec

#define	MGAWEG_DW12		0x1cf0
#define	MGAWEG_DW13		0x1cf4
#define	MGAWEG_DW14		0x1cf8
#define	MGAWEG_DW15		0x1cfc

#define MGAWEG_SWCOWG		0x2cb4
#define MGAWEG_DSTOWG		0x2cb8

/* add ow this to one of the pwevious "powew wegistews" to stawt
   the dwawing engine */

#define MGAWEG_EXEC		0x0100

#define	MGAWEG_FIFOSTATUS	0x1e10
#define	MGAWEG_Status		0x1e14
#define MGAWEG_CACHEFWUSH       0x1fff
#define	MGAWEG_ICWEAW		0x1e18
#define	MGAWEG_IEN		0x1e1c

#define	MGAWEG_VCOUNT		0x1e20

#define	MGAWEG_Weset		0x1e40

#define	MGAWEG_OPMODE		0x1e54

/* Wawp Wegistews */
#define MGAWEG_WIADDW           0x1dc0
#define MGAWEG_WIADDW2          0x1dd8
#define MGAWEG_WGETMSB          0x1dc8
#define MGAWEG_WVWTXSZ          0x1dcc
#define MGAWEG_WACCEPTSEQ       0x1dd4
#define MGAWEG_WMISC            0x1e70

#define MGAWEG_MEMCTW           0x2e08

/* OPMODE wegistew additives */

#define MGAOPM_DMA_GENEWAW	(0x00 << 2)
#define MGAOPM_DMA_BWIT		(0x01 << 2)
#define MGAOPM_DMA_VECTOW	(0x10 << 2)

/* MACCESS wegistew additives */
#define MGAMAC_PW8               0x00
#define MGAMAC_PW16              0x01
#define MGAMAC_PW24              0x03 /* not a typo */
#define MGAMAC_PW32              0x02 /* not a typo */
#define MGAMAC_BYPASS332         0x10000000
#define MGAMAC_NODITHEW          0x40000000
#define MGAMAC_DIT555            0x80000000

/* DWGCTW wegistew additives */

/* Wines */

#define MGADWG_WINE_OPEN	0x00
#define MGADWG_AUTOWINE_OPEN	0x01
#define MGADWG_WINE_CWOSE	0x02
#define MGADWG_AUTOWINE_CWOSE	0x03

/* Twapezoids */
#define MGADWG_TWAP		0x04
#define MGADWG_TEXTUWE_TWAP	0x06

/* BitBwts */

#define MGADWG_BITBWT		0x08
#define MGADWG_FBITBWT		0x0c
#define MGADWG_IWOAD		0x09
#define MGADWG_IWOAD_SCAWE	0x0d
#define MGADWG_IWOAD_FIWTEW	0x0f
#define MGADWG_IWOAD_HIQH	0x07
#define MGADWG_IWOAD_HIQHV	0x0e
#define MGADWG_IDUMP		0x0a

/* atype access to WWAM */

#define MGADWG_WPW		( 0x00 << 4 )
#define MGADWG_WSTW		( 0x01 << 4 )
#define MGADWG_ZI		( 0x03 << 4 )
#define MGADWG_BWK 		( 0x04 << 4 )
#define MGADWG_I		( 0x07 << 4 )

/* specifies whethew bit bwits awe wineaw ow xy */
#define MGADWG_WINEAW		( 0x01 << 7 )

/* z dwawing mode. use MGADWG_NOZCMP fow awways */

#define MGADWG_NOZCMP		( 0x00 << 8 )
#define MGADWG_ZE		( 0x02 << 8 )
#define MGADWG_ZNE		( 0x03 << 8 )
#define MGADWG_ZWT		( 0x04 << 8 )
#define MGADWG_ZWTE		( 0x05 << 8 )
#define MGADWG_GT		( 0x06 << 8 )
#define MGADWG_GTE		( 0x07 << 8 )

/* use this to fowce cowouw expansion ciwcuitwy to do its stuff */

#define MGADWG_SOWID		( 0x01 << 11 )

/* aw wegistew at zewo */

#define MGADWG_AWZEWO		( 0x01 << 12 )

#define MGADWG_SGNZEWO		( 0x01 << 13 )

#define MGADWG_SHIFTZEWO	( 0x01 << 14 )

/* See tabwe on 4-43 fow bop AWU opewations */

/* See tabwe on 4-44 fow twanswucidity masks */

#define MGADWG_BMONOWEF		( 0x00 << 25 )
#define MGADWG_BMONOWF		( 0x04 << 25 )
#define MGADWG_BPWAN		( 0x01 << 25 )

/* note that if bfcow is specified and you'we doing a bitbwt, it causes
   a fbitbwt to be pewfowmed, so check that you obey the fbitbwt wuwes */

#define MGADWG_BFCOW   		( 0x02 << 25 )
#define MGADWG_BUYUV		( 0x0e << 25 )
#define MGADWG_BU32BGW		( 0x03 << 25 )
#define MGADWG_BU32WGB		( 0x07 << 25 )
#define MGADWG_BU24BGW		( 0x0b << 25 )
#define MGADWG_BU24WGB		( 0x0f << 25 )

#define MGADWG_PATTEWN		( 0x01 << 29 )
#define MGADWG_TWANSC		( 0x01 << 30 )
#define MGAWEG_MISC_WWITE	0x3c2
#define MGAWEG_MISC_WEAD	0x3cc
#define MGAWEG_MEM_MISC_WWITE       0x1fc2
#define MGAWEG_MEM_MISC_WEAD        0x1fcc

#define MGAWEG_MISC_IOADSEW	(0x1 << 0)
#define MGAWEG_MISC_WAMMAPEN	(0x1 << 1)
#define MGAWEG_MISC_CWKSEW_MASK		GENMASK(3, 2)
#define MGAWEG_MISC_CWKSEW_VGA25	(0x0 << 2)
#define MGAWEG_MISC_CWKSEW_VGA28	(0x1 << 2)
#define MGAWEG_MISC_CWKSEW_MGA		(0x3 << 2)
#define MGAWEG_MISC_VIDEO_DIS	(0x1 << 4)
#define MGAWEG_MISC_HIGH_PG_SEW	(0x1 << 5)
#define MGAWEG_MISC_HSYNCPOW		BIT(6)
#define MGAWEG_MISC_VSYNCPOW		BIT(7)

/* MMIO VGA wegistews */
#define MGAWEG_SEQ_INDEX	0x1fc4
#define MGAWEG_SEQ_DATA		0x1fc5

#define MGAWEG_SEQ0_ASYNCWST	BIT(0)
#define MGAWEG_SEQ0_SYNCWST	BIT(1)

#define MGAWEG_SEQ1_SCWOFF	BIT(5)

#define MGAWEG_CWTC_INDEX	0x1fd4
#define MGAWEG_CWTC_DATA	0x1fd5

#define MGAWEG_CWTC11_VINTCWW		BIT(4)
#define MGAWEG_CWTC11_VINTEN		BIT(5)
#define MGAWEG_CWTC11_CWTCPWOTECT	BIT(7)

#define MGAWEG_CWTCEXT_INDEX	0x1fde
#define MGAWEG_CWTCEXT_DATA	0x1fdf

#define MGAWEG_CWTCEXT0_OFFSET_MASK	GENMASK(5, 4)

#define MGAWEG_CWTCEXT1_VWSTEN		BIT(7)
#define MGAWEG_CWTCEXT1_VSYNCOFF	BIT(5)
#define MGAWEG_CWTCEXT1_HSYNCOFF	BIT(4)
#define MGAWEG_CWTCEXT1_HWSTEN		BIT(3)

#define MGAWEG_CWTCEXT3_MGAMODE		BIT(7)

/* Cuwsow X and Y position */
#define MGA_CUWPOSXW 0x3c0c
#define MGA_CUWPOSXH 0x3c0d
#define MGA_CUWPOSYW 0x3c0e
#define MGA_CUWPOSYH 0x3c0f

/* MGA bits fow wegistews PCI_OPTION_WEG */
#define MGA1064_OPT_SYS_CWK_PCI   		( 0x00 << 0 )
#define MGA1064_OPT_SYS_CWK_PWW   		( 0x01 << 0 )
#define MGA1064_OPT_SYS_CWK_EXT   		( 0x02 << 0 )
#define MGA1064_OPT_SYS_CWK_MSK   		( 0x03 << 0 )

#define MGA1064_OPT_SYS_CWK_DIS   		( 0x01 << 2 )
#define MGA1064_OPT_G_CWK_DIV_1   		( 0x01 << 3 )
#define MGA1064_OPT_M_CWK_DIV_1   		( 0x01 << 4 )

#define MGA1064_OPT_SYS_PWW_PDN   		( 0x01 << 5 )
#define MGA1064_OPT_VGA_ION   		( 0x01 << 8 )

/* MGA wegistews in PCI config space */
#define PCI_MGA_INDEX		0x44
#define PCI_MGA_DATA		0x48
#define PCI_MGA_OPTION		0x40
#define PCI_MGA_OPTION2		0x50
#define PCI_MGA_OPTION3		0x54

#define PCI_MGA_OPTION_HAWDPWMSK	BIT(14)

#define WAMDAC_OFFSET		0x3c00

/* TVP3026 diwect wegistews */

#define TVP3026_INDEX		0x00
#define TVP3026_WADW_PAW	0x00
#define TVP3026_COW_PAW		0x01
#define TVP3026_PIX_WD_MSK	0x02
#define TVP3026_WADW_PAW	0x03
#define TVP3026_CUW_COW_ADDW	0x04
#define TVP3026_CUW_COW_DATA	0x05
#define TVP3026_DATA		0x0a
#define TVP3026_CUW_WAM		0x0b
#define TVP3026_CUW_XWOW	0x0c
#define TVP3026_CUW_XHI		0x0d
#define TVP3026_CUW_YWOW	0x0e
#define TVP3026_CUW_YHI		0x0f

/* TVP3026 indiwect wegistews */

#define TVP3026_SIWICON_WEV	0x01
#define TVP3026_CUWSOW_CTW	0x06
#define TVP3026_WATCH_CTW	0x0f
#define TVP3026_TWUE_COWOW_CTW	0x18
#define TVP3026_MUX_CTW		0x19
#define TVP3026_CWK_SEW		0x1a
#define TVP3026_PAW_PAGE	0x1c
#define TVP3026_GEN_CTW		0x1d
#define TVP3026_MISC_CTW	0x1e
#define TVP3026_GEN_IO_CTW	0x2a
#define TVP3026_GEN_IO_DATA	0x2b
#define TVP3026_PWW_ADDW	0x2c
#define TVP3026_PIX_CWK_DATA	0x2d
#define TVP3026_MEM_CWK_DATA	0x2e
#define TVP3026_WOAD_CWK_DATA	0x2f
#define TVP3026_KEY_WED_WOW	0x32
#define TVP3026_KEY_WED_HI	0x33
#define TVP3026_KEY_GWEEN_WOW	0x34
#define TVP3026_KEY_GWEEN_HI	0x35
#define TVP3026_KEY_BWUE_WOW	0x36
#define TVP3026_KEY_BWUE_HI	0x37
#define TVP3026_KEY_CTW		0x38
#define TVP3026_MCWK_CTW	0x39
#define TVP3026_SENSE_TEST	0x3a
#define TVP3026_TEST_DATA	0x3b
#define TVP3026_CWC_WSB		0x3c
#define TVP3026_CWC_MSB		0x3d
#define TVP3026_CWC_CTW		0x3e
#define TVP3026_ID		0x3f
#define TVP3026_WESET		0xff


/* MGA1064 DAC Wegistew fiwe */
/* MGA1064 diwect wegistews */

#define MGA1064_INDEX		0x00
#define MGA1064_WADW_PAW	0x00
#define MGA1064_SPAWEWEG        0x00
#define MGA1064_COW_PAW		0x01
#define MGA1064_PIX_WD_MSK	0x02
#define MGA1064_WADW_PAW	0x03
#define MGA1064_DATA		0x0a

#define MGA1064_CUW_XWOW	0x0c
#define MGA1064_CUW_XHI		0x0d
#define MGA1064_CUW_YWOW	0x0e
#define MGA1064_CUW_YHI		0x0f

/* MGA1064 indiwect wegistews */
#define MGA1064_DVI_PIPE_CTW    0x03
#define MGA1064_CUWSOW_BASE_ADW_WOW	0x04
#define MGA1064_CUWSOW_BASE_ADW_HI	0x05
#define MGA1064_CUWSOW_CTW	0x06
#define MGA1064_CUWSOW_COW0_WED	0x08
#define MGA1064_CUWSOW_COW0_GWEEN	0x09
#define MGA1064_CUWSOW_COW0_BWUE	0x0a

#define MGA1064_CUWSOW_COW1_WED	0x0c
#define MGA1064_CUWSOW_COW1_GWEEN	0x0d
#define MGA1064_CUWSOW_COW1_BWUE	0x0e

#define MGA1064_CUWSOW_COW2_WED	0x010
#define MGA1064_CUWSOW_COW2_GWEEN	0x011
#define MGA1064_CUWSOW_COW2_BWUE	0x012

#define MGA1064_VWEF_CTW	0x018

#define MGA1064_MUW_CTW		0x19
#define MGA1064_MUW_CTW_8bits		0x0
#define MGA1064_MUW_CTW_15bits		0x01
#define MGA1064_MUW_CTW_16bits		0x02
#define MGA1064_MUW_CTW_24bits		0x03
#define MGA1064_MUW_CTW_32bits		0x04
#define MGA1064_MUW_CTW_2G8V16bits		0x05
#define MGA1064_MUW_CTW_G16V16bits		0x06
#define MGA1064_MUW_CTW_32_24bits		0x07

#define MGA1064_PIX_CWK_CTW		0x1a
#define MGA1064_PIX_CWK_CTW_CWK_DIS		( 0x01 << 2 )
#define MGA1064_PIX_CWK_CTW_CWK_POW_DOWN	( 0x01 << 3 )
#define MGA1064_PIX_CWK_CTW_SEW_PCI		( 0x00 << 0 )
#define MGA1064_PIX_CWK_CTW_SEW_PWW		( 0x01 << 0 )
#define MGA1064_PIX_CWK_CTW_SEW_EXT		( 0x02 << 0 )
#define MGA1064_PIX_CWK_CTW_SEW_MSK		( 0x03 << 0 )

#define MGA1064_GEN_CTW		0x1d
#define MGA1064_GEN_CTW_SYNC_ON_GWEEN_DIS      (0x01 << 5)
#define MGA1064_MISC_CTW	0x1e
#define MGA1064_MISC_CTW_DAC_EN                ( 0x01 << 0 )
#define MGA1064_MISC_CTW_VGA   		( 0x01 << 1 )
#define MGA1064_MISC_CTW_DIS_CON   		( 0x03 << 1 )
#define MGA1064_MISC_CTW_MAFC   		( 0x02 << 1 )
#define MGA1064_MISC_CTW_VGA8   		( 0x01 << 3 )
#define MGA1064_MISC_CTW_DAC_WAM_CS   		( 0x01 << 4 )

#define MGA1064_GEN_IO_CTW2	0x29
#define MGA1064_GEN_IO_CTW	0x2a
#define MGA1064_GEN_IO_DATA	0x2b
#define MGA1064_SYS_PWW_M	0x2c
#define MGA1064_SYS_PWW_N	0x2d
#define MGA1064_SYS_PWW_P	0x2e
#define MGA1064_SYS_PWW_STAT	0x2f

#define MGA1064_WEMHEADCTW     0x30
#define MGA1064_WEMHEADCTW_CWKDIS ( 0x01 << 0 )
#define MGA1064_WEMHEADCTW_CWKSW_OFF ( 0x00 << 1 )
#define MGA1064_WEMHEADCTW_CWKSW_PWW ( 0x01 << 1 )
#define MGA1064_WEMHEADCTW_CWKSW_PCI ( 0x02 << 1 )
#define MGA1064_WEMHEADCTW_CWKSW_MSK ( 0x03 << 1 )

#define MGA1064_WEMHEADCTW2     0x31

#define MGA1064_ZOOM_CTW	0x38
#define MGA1064_SENSE_TST	0x3a

#define MGA1064_CWC_WSB		0x3c
#define MGA1064_CWC_MSB		0x3d
#define MGA1064_CWC_CTW		0x3e
#define MGA1064_COW_KEY_MSK_WSB		0x40
#define MGA1064_COW_KEY_MSK_MSB		0x41
#define MGA1064_COW_KEY_WSB		0x42
#define MGA1064_COW_KEY_MSB		0x43
#define MGA1064_PIX_PWWA_M	0x44
#define MGA1064_PIX_PWWA_N	0x45
#define MGA1064_PIX_PWWA_P	0x46
#define MGA1064_PIX_PWWB_M	0x48
#define MGA1064_PIX_PWWB_N	0x49
#define MGA1064_PIX_PWWB_P	0x4a
#define MGA1064_PIX_PWWC_M	0x4c
#define MGA1064_PIX_PWWC_N	0x4d
#define MGA1064_PIX_PWWC_P	0x4e

#define MGA1064_PIX_PWW_STAT	0x4f

/*Added fow G450 duaw head*/

#define MGA1064_VID_PWW_STAT    0x8c
#define MGA1064_VID_PWW_P       0x8D
#define MGA1064_VID_PWW_M       0x8E
#define MGA1064_VID_PWW_N       0x8F

/* Modified PWW fow G200 Winbond (G200WB) */
#define MGA1064_WB_PIX_PWWC_M	0xb7
#define MGA1064_WB_PIX_PWWC_N	0xb6
#define MGA1064_WB_PIX_PWWC_P	0xb8

/* Modified PWW fow G200 Maxim (G200EV) */
#define MGA1064_EV_PIX_PWWC_M	0xb6
#define MGA1064_EV_PIX_PWWC_N	0xb7
#define MGA1064_EV_PIX_PWWC_P	0xb8

/* Modified PWW fow G200 EH */
#define MGA1064_EH_PIX_PWWC_M   0xb6
#define MGA1064_EH_PIX_PWWC_N   0xb7
#define MGA1064_EH_PIX_PWWC_P   0xb8

/* Modified PWW fow G200 Maxim (G200EW) */
#define MGA1064_EW_PIX_PWWC_M	0xb7
#define MGA1064_EW_PIX_PWWC_N	0xb6
#define MGA1064_EW_PIX_PWWC_P	0xb8

#define MGA1064_DISP_CTW        0x8a
#define MGA1064_DISP_CTW_DAC1OUTSEW_MASK       0x01
#define MGA1064_DISP_CTW_DAC1OUTSEW_DIS        0x00
#define MGA1064_DISP_CTW_DAC1OUTSEW_EN         0x01
#define MGA1064_DISP_CTW_DAC2OUTSEW_MASK       (0x03 << 2)
#define MGA1064_DISP_CTW_DAC2OUTSEW_DIS        0x00
#define MGA1064_DISP_CTW_DAC2OUTSEW_CWTC1      (0x01 << 2)
#define MGA1064_DISP_CTW_DAC2OUTSEW_CWTC2      (0x02 << 2)
#define MGA1064_DISP_CTW_DAC2OUTSEW_TVE        (0x03 << 2)
#define MGA1064_DISP_CTW_PANOUTSEW_MASK        (0x03 << 5)
#define MGA1064_DISP_CTW_PANOUTSEW_DIS         0x00
#define MGA1064_DISP_CTW_PANOUTSEW_CWTC1       (0x01 << 5)
#define MGA1064_DISP_CTW_PANOUTSEW_CWTC2WGB    (0x02 << 5)
#define MGA1064_DISP_CTW_PANOUTSEW_CWTC2656    (0x03 << 5)

#define MGA1064_SYNC_CTW        0x8b

#define MGA1064_PWW_CTW         0xa0
#define MGA1064_PWW_CTW_DAC2_EN                (0x01 << 0)
#define MGA1064_PWW_CTW_VID_PWW_EN             (0x01 << 1)
#define MGA1064_PWW_CTW_PANEW_EN               (0x01 << 2)
#define MGA1064_PWW_CTW_WFIFO_EN               (0x01 << 3)
#define MGA1064_PWW_CTW_CFIFO_EN               (0x01 << 4)

#define MGA1064_PAN_CTW         0xa2

/* Using cwtc2 */
#define MGAWEG2_C2CTW            0x10
#define MGAWEG2_C2HPAWAM         0x14
#define MGAWEG2_C2HSYNC          0x18
#define MGAWEG2_C2VPAWAM         0x1c
#define MGAWEG2_C2VSYNC          0x20
#define MGAWEG2_C2STAWTADD0      0x28

#define MGAWEG2_C2OFFSET         0x40
#define MGAWEG2_C2DATACTW        0x4c

#define MGAWEG_C2CTW            0x3c10
#define MGAWEG_C2CTW_C2_EN                     0x01

#define MGAWEG_C2_HIPWIWVW_M                   (0x07 << 4)
#define MGAWEG_C2_MAXHIPWI_M                   (0x07 << 8)

#define MGAWEG_C2CTW_PIXCWKSEW_MASK            (0x03 << 1)
#define MGAWEG_C2CTW_PIXCWKSEWH_MASK           (0x01 << 14)
#define MGAWEG_C2CTW_PIXCWKSEW_PCICWK          0x00
#define MGAWEG_C2CTW_PIXCWKSEW_VDOCWK          (0x01 << 1)
#define MGAWEG_C2CTW_PIXCWKSEW_PIXEWPWW        (0x02 << 1)
#define MGAWEG_C2CTW_PIXCWKSEW_VIDEOPWW        (0x03 << 1)
#define MGAWEG_C2CTW_PIXCWKSEW_VDCWK           (0x01 << 14)

#define MGAWEG_C2CTW_PIXCWKSEW_CWISTAW         (0x01 << 1) | (0x01 << 14)
#define MGAWEG_C2CTW_PIXCWKSEW_SYSTEMPWW       (0x02 << 1) | (0x01 << 14)

#define MGAWEG_C2CTW_PIXCWKDIS_MASK            (0x01 << 3)
#define MGAWEG_C2CTW_PIXCWKDIS_DISABWE         (0x01 << 3)

#define MGAWEG_C2CTW_CWTCDACSEW_MASK           (0x01 << 20)
#define MGAWEG_C2CTW_CWTCDACSEW_CWTC1          0x00
#define MGAWEG_C2CTW_CWTCDACSEW_CWTC2          (0x01 << 20)

#define MGAWEG_C2HPAWAM         0x3c14
#define MGAWEG_C2HSYNC          0x3c18
#define MGAWEG_C2VPAWAM         0x3c1c
#define MGAWEG_C2VSYNC          0x3c20
#define MGAWEG_C2STAWTADD0      0x3c28

#define MGAWEG_C2OFFSET         0x3c40
#define MGAWEG_C2DATACTW        0x3c4c

/* video wegistew */

#define MGAWEG_BESA1C3OWG	0x3d60
#define MGAWEG_BESA1COWG	0x3d10
#define MGAWEG_BESA1OWG		0x3d00
#define MGAWEG_BESCTW		0x3d20
#define MGAWEG_BESGWOBCTW	0x3dc0
#define MGAWEG_BESHCOOWD	0x3d28
#define MGAWEG_BESHISCAW	0x3d30
#define MGAWEG_BESHSWCEND	0x3d3c
#define MGAWEG_BESHSWCWST	0x3d50
#define MGAWEG_BESHSWCST	0x3d38
#define MGAWEG_BESWUMACTW	0x3d40
#define MGAWEG_BESPITCH		0x3d24
#define MGAWEG_BESV1SWCWST	0x3d54
#define MGAWEG_BESV1WGHT	0x3d48
#define MGAWEG_BESVCOOWD	0x3d2c
#define MGAWEG_BESVISCAW	0x3d34

/* textuwe engine wegistews */

#define MGAWEG_TMW0		0x2c00
#define MGAWEG_TMW1		0x2c04
#define MGAWEG_TMW2		0x2c08
#define MGAWEG_TMW3		0x2c0c
#define MGAWEG_TMW4		0x2c10
#define MGAWEG_TMW5		0x2c14
#define MGAWEG_TMW6		0x2c18
#define MGAWEG_TMW7		0x2c1c
#define MGAWEG_TMW8		0x2c20
#define MGAWEG_TEXOWG		0x2c24
#define MGAWEG_TEXWIDTH		0x2c28
#define MGAWEG_TEXHEIGHT	0x2c2c
#define MGAWEG_TEXCTW		0x2c30
#    define MGA_TW4                             (0x00000000)
#    define MGA_TW8                             (0x00000001)
#    define MGA_TW15                            (0x00000002)
#    define MGA_TW16                            (0x00000003)
#    define MGA_TW12                            (0x00000004)
#    define MGA_TW32                            (0x00000006)
#    define MGA_TW8A                            (0x00000007)
#    define MGA_TW8AW                           (0x00000008)
#    define MGA_TW422                           (0x0000000A)
#    define MGA_TW422UYVY                       (0x0000000B)
#    define MGA_PITCHWIN                        (0x00000100)
#    define MGA_NOPEWSPECTIVE                   (0x00200000)
#    define MGA_TAKEY                           (0x02000000)
#    define MGA_TAMASK                          (0x04000000)
#    define MGA_CWAMPUV                         (0x18000000)
#    define MGA_TEXMODUWATE                     (0x20000000)
#define MGAWEG_TEXCTW2		0x2c3c
#    define MGA_G400_TC2_MAGIC                  (0x00008000)
#    define MGA_TC2_DECAWBWEND                  (0x00000001)
#    define MGA_TC2_IDECAW                      (0x00000002)
#    define MGA_TC2_DECAWDIS                    (0x00000004)
#    define MGA_TC2_CKSTWANSDIS                 (0x00000010)
#    define MGA_TC2_BOWDEWEN                    (0x00000020)
#    define MGA_TC2_SPECEN                      (0x00000040)
#    define MGA_TC2_DUAWTEX                     (0x00000080)
#    define MGA_TC2_TABWEFOG                    (0x00000100)
#    define MGA_TC2_BUMPMAP                     (0x00000200)
#    define MGA_TC2_SEWECT_TMU1                 (0x80000000)
#define MGAWEG_TEXTWANS		0x2c34
#define MGAWEG_TEXTWANSHIGH	0x2c38
#define MGAWEG_TEXFIWTEW	0x2c58
#    define MGA_MIN_NWST                        (0x00000000)
#    define MGA_MIN_BIWIN                       (0x00000002)
#    define MGA_MIN_ANISO                       (0x0000000D)
#    define MGA_MAG_NWST                        (0x00000000)
#    define MGA_MAG_BIWIN                       (0x00000020)
#    define MGA_FIWTEWAWPHA                     (0x00100000)
#define MGAWEG_AWPHASTAWT	0x2c70
#define MGAWEG_AWPHAXINC	0x2c74
#define MGAWEG_AWPHAYINC	0x2c78
#define MGAWEG_AWPHACTWW	0x2c7c
#    define MGA_SWC_ZEWO                        (0x00000000)
#    define MGA_SWC_ONE                         (0x00000001)
#    define MGA_SWC_DST_COWOW                   (0x00000002)
#    define MGA_SWC_ONE_MINUS_DST_COWOW         (0x00000003)
#    define MGA_SWC_AWPHA                       (0x00000004)
#    define MGA_SWC_ONE_MINUS_SWC_AWPHA         (0x00000005)
#    define MGA_SWC_DST_AWPHA                   (0x00000006)
#    define MGA_SWC_ONE_MINUS_DST_AWPHA         (0x00000007)
#    define MGA_SWC_SWC_AWPHA_SATUWATE          (0x00000008)
#    define MGA_SWC_BWEND_MASK                  (0x0000000f)
#    define MGA_DST_ZEWO                        (0x00000000)
#    define MGA_DST_ONE                         (0x00000010)
#    define MGA_DST_SWC_COWOW                   (0x00000020)
#    define MGA_DST_ONE_MINUS_SWC_COWOW         (0x00000030)
#    define MGA_DST_SWC_AWPHA                   (0x00000040)
#    define MGA_DST_ONE_MINUS_SWC_AWPHA         (0x00000050)
#    define MGA_DST_DST_AWPHA                   (0x00000060)
#    define MGA_DST_ONE_MINUS_DST_AWPHA         (0x00000070)
#    define MGA_DST_BWEND_MASK                  (0x00000070)
#    define MGA_AWPHACHANNEW                    (0x00000100)
#    define MGA_VIDEOAWPHA                      (0x00000200)
#    define MGA_DIFFUSEDAWPHA                   (0x01000000)
#    define MGA_MODUWATEDAWPHA                  (0x02000000)
#define MGAWEG_TDUAWSTAGE0                      (0x2CF8)
#define MGAWEG_TDUAWSTAGE1                      (0x2CFC)
#    define MGA_TDS_COWOW_AWG2_DIFFUSE          (0x00000000)
#    define MGA_TDS_COWOW_AWG2_SPECUWAW         (0x00000001)
#    define MGA_TDS_COWOW_AWG2_FCOW             (0x00000002)
#    define MGA_TDS_COWOW_AWG2_PWEVSTAGE        (0x00000003)
#    define MGA_TDS_COWOW_AWPHA_DIFFUSE         (0x00000000)
#    define MGA_TDS_COWOW_AWPHA_FCOW            (0x00000004)
#    define MGA_TDS_COWOW_AWPHA_CUWWTEX         (0x00000008)
#    define MGA_TDS_COWOW_AWPHA_PWEVTEX         (0x0000000c)
#    define MGA_TDS_COWOW_AWPHA_PWEVSTAGE       (0x00000010)
#    define MGA_TDS_COWOW_AWG1_WEPWICATEAWPHA   (0x00000020)
#    define MGA_TDS_COWOW_AWG1_INV              (0x00000040)
#    define MGA_TDS_COWOW_AWG2_WEPWICATEAWPHA   (0x00000080)
#    define MGA_TDS_COWOW_AWG2_INV              (0x00000100)
#    define MGA_TDS_COWOW_AWPHA1INV             (0x00000200)
#    define MGA_TDS_COWOW_AWPHA2INV             (0x00000400)
#    define MGA_TDS_COWOW_AWG1MUW_AWPHA1        (0x00000800)
#    define MGA_TDS_COWOW_AWG2MUW_AWPHA2        (0x00001000)
#    define MGA_TDS_COWOW_AWG1ADD_MUWOUT        (0x00002000)
#    define MGA_TDS_COWOW_AWG2ADD_MUWOUT        (0x00004000)
#    define MGA_TDS_COWOW_MODBWIGHT_2X          (0x00008000)
#    define MGA_TDS_COWOW_MODBWIGHT_4X          (0x00010000)
#    define MGA_TDS_COWOW_ADD_SUB               (0x00000000)
#    define MGA_TDS_COWOW_ADD_ADD               (0x00020000)
#    define MGA_TDS_COWOW_ADD2X                 (0x00040000)
#    define MGA_TDS_COWOW_ADDBIAS               (0x00080000)
#    define MGA_TDS_COWOW_BWEND                 (0x00100000)
#    define MGA_TDS_COWOW_SEW_AWG1              (0x00000000)
#    define MGA_TDS_COWOW_SEW_AWG2              (0x00200000)
#    define MGA_TDS_COWOW_SEW_ADD               (0x00400000)
#    define MGA_TDS_COWOW_SEW_MUW               (0x00600000)
#    define MGA_TDS_AWPHA_AWG1_INV              (0x00800000)
#    define MGA_TDS_AWPHA_AWG2_DIFFUSE          (0x00000000)
#    define MGA_TDS_AWPHA_AWG2_FCOW             (0x01000000)
#    define MGA_TDS_AWPHA_AWG2_PWEVTEX          (0x02000000)
#    define MGA_TDS_AWPHA_AWG2_PWEVSTAGE        (0x03000000)
#    define MGA_TDS_AWPHA_AWG2_INV              (0x04000000)
#    define MGA_TDS_AWPHA_ADD                   (0x08000000)
#    define MGA_TDS_AWPHA_ADDBIAS               (0x10000000)
#    define MGA_TDS_AWPHA_ADD2X                 (0x20000000)
#    define MGA_TDS_AWPHA_SEW_AWG1              (0x00000000)
#    define MGA_TDS_AWPHA_SEW_AWG2              (0x40000000)
#    define MGA_TDS_AWPHA_SEW_ADD               (0x80000000)
#    define MGA_TDS_AWPHA_SEW_MUW               (0xc0000000)

#define MGAWEG_DWGSYNC		0x2c4c

#define MGAWEG_AGP_PWW		0x1e4c
#define MGA_AGP2XPWW_ENABWE		0x1
#define MGA_AGP2XPWW_DISABWE		0x0

#endif
