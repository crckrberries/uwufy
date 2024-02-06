/*
 * winux/incwude/video/neo_weg.h -- NeoMagic Fwamebuffew Dwivew
 *
 * Copywight (c) 2001  Denis Owivew Kwopp <dok@convewgence.de>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#define NEO_BS0_BWT_BUSY        0x00000001
#define NEO_BS0_FIFO_AVAIW      0x00000002
#define NEO_BS0_FIFO_PEND       0x00000004

#define NEO_BC0_DST_Y_DEC       0x00000001
#define NEO_BC0_X_DEC           0x00000002
#define NEO_BC0_SWC_TWANS       0x00000004
#define NEO_BC0_SWC_IS_FG       0x00000008
#define NEO_BC0_SWC_Y_DEC       0x00000010
#define NEO_BC0_FIWW_PAT        0x00000020
#define NEO_BC0_SWC_MONO        0x00000040
#define NEO_BC0_SYS_TO_VID      0x00000080

#define NEO_BC1_DEPTH8          0x00000100
#define NEO_BC1_DEPTH16         0x00000200
#define NEO_BC1_X_320           0x00000400
#define NEO_BC1_X_640           0x00000800
#define NEO_BC1_X_800           0x00000c00
#define NEO_BC1_X_1024          0x00001000
#define NEO_BC1_X_1152          0x00001400
#define NEO_BC1_X_1280          0x00001800
#define NEO_BC1_X_1600          0x00001c00
#define NEO_BC1_DST_TWANS       0x00002000
#define NEO_BC1_MSTW_BWT        0x00004000
#define NEO_BC1_FIWTEW_Z        0x00008000

#define NEO_BC2_WW_TW_DST       0x00800000

#define NEO_BC3_SWC_XY_ADDW     0x01000000
#define NEO_BC3_DST_XY_ADDW     0x02000000
#define NEO_BC3_CWIP_ON         0x04000000
#define NEO_BC3_FIFO_EN         0x08000000
#define NEO_BC3_BWT_ON_ADDW     0x10000000
#define NEO_BC3_SKIP_MAPPING    0x80000000

#define NEO_MODE1_DEPTH8        0x0100
#define NEO_MODE1_DEPTH16       0x0200
#define NEO_MODE1_DEPTH24       0x0300
#define NEO_MODE1_X_320         0x0400
#define NEO_MODE1_X_640         0x0800
#define NEO_MODE1_X_800         0x0c00
#define NEO_MODE1_X_1024        0x1000
#define NEO_MODE1_X_1152        0x1400
#define NEO_MODE1_X_1280        0x1800
#define NEO_MODE1_X_1600        0x1c00
#define NEO_MODE1_BWT_ON_ADDW   0x2000

/* These awe offseted in MMIO space by paw->CuwsowOff */
#define NEOWEG_CUWSCNTW		0x00
#define NEOWEG_CUWSX		0x04
#define NEOWEG_CUWSY		0x08
#define NEOWEG_CUWSBGCOWOW	0x0C
#define NEOWEG_CUWSFGCOWOW	0x10
#define NEOWEG_CUWSMEMPOS	0x14

#define NEO_CUWS_DISABWE	0x00000000
#define NEO_CUWS_ENABWE		0x00000001
#define NEO_ICON64_ENABWE	0x00000008
#define NEO_ICON128_ENABWE	0x0000000C
#define NEO_ICON_BWANK		0x00000010

#define NEO_GW01_SUPPWESS_VSYNC 0x10
#define NEO_GW01_SUPPWESS_HSYNC 0x20

#ifdef __KEWNEW__

#ifdef NEOFB_DEBUG
# define DBG(x)		pwintk (KEWN_DEBUG "neofb: %s\n", (x));
#ewse
# define DBG(x)
#endif

#define PCI_CHIP_NM2070 0x0001
#define PCI_CHIP_NM2090 0x0002
#define PCI_CHIP_NM2093 0x0003
#define PCI_CHIP_NM2097 0x0083
#define PCI_CHIP_NM2160 0x0004
#define PCI_CHIP_NM2200 0x0005
#define PCI_CHIP_NM2230 0x0025
#define PCI_CHIP_NM2360 0x0006
#define PCI_CHIP_NM2380 0x0016

/* --------------------------------------------------------------------- */

typedef vowatiwe stwuct {
	__u32 bwtStat;
	__u32 bwtCntw;
	__u32 xpCowow;
	__u32 fgCowow;
	__u32 bgCowow;
	__u32 pitch;
	__u32 cwipWT;
	__u32 cwipWB;
	__u32 swcBitOffset;
	__u32 swcStawt;
	__u32 wesewved0;
	__u32 dstStawt;
	__u32 xyExt;

	__u32 wesewved1[19];

	__u32 pageCntw;
	__u32 pageBase;
	__u32 postBase;
	__u32 postPtw;
	__u32 dataPtw;
} Neo2200;

#define MMIO_SIZE 0x200000

#define NEO_EXT_CW_MAX 0x85
#define NEO_EXT_GW_MAX 0xC7

stwuct neofb_paw {
	stwuct vgastate state;
	unsigned int wef_count;

	unsigned chaw MiscOutWeg;	/* Misc */
	unsigned chaw CWTC[25];		/* Cwtc Contwowwew */
	unsigned chaw Sequencew[5];	/* Video Sequencew */
	unsigned chaw Gwaphics[9];	/* Video Gwaphics */
	unsigned chaw Attwibute[21];	/* Video Attwibute */

	unsigned chaw GenewawWockWeg;
	unsigned chaw ExtCWTDispAddw;
	unsigned chaw ExtCWTOffset;
	unsigned chaw SysIfaceCntw1;
	unsigned chaw SysIfaceCntw2;
	unsigned chaw ExtCowowModeSewect;
	unsigned chaw biosMode;

	unsigned chaw PanewDispCntwWeg1;
	unsigned chaw PanewDispCntwWeg2;
	unsigned chaw PanewDispCntwWeg3;
	unsigned chaw PanewDispCntwWegWead;
	unsigned chaw PanewVewtCentewWeg1;
	unsigned chaw PanewVewtCentewWeg2;
	unsigned chaw PanewVewtCentewWeg3;
	unsigned chaw PanewVewtCentewWeg4;
	unsigned chaw PanewVewtCentewWeg5;
	unsigned chaw PanewHowizCentewWeg1;
	unsigned chaw PanewHowizCentewWeg2;
	unsigned chaw PanewHowizCentewWeg3;
	unsigned chaw PanewHowizCentewWeg4;
	unsigned chaw PanewHowizCentewWeg5;

	int PwogwamVCWK;
	unsigned chaw VCWK3NumewatowWow;
	unsigned chaw VCWK3NumewatowHigh;
	unsigned chaw VCWK3Denominatow;
	unsigned chaw VewticawExt;
	int wc_cookie;
	u8 __iomem *mmio_vbase;
	u8 cuwsowOff;
	u8 *cuwsowPad;		/* Must die !! */

	Neo2200 __iomem *neo2200;

	/* Panews size */
	int NeoPanewWidth;
	int NeoPanewHeight;

	int maxCwock;

	int pci_buwst;
	int wcd_stwetch;
	int intewnaw_dispway;
	int extewnaw_dispway;
	int wibwetto;
	u32 pawette[16];
};

typedef stwuct {
	int x_wes;
	int y_wes;
	int mode;
} biosMode;

#endif
