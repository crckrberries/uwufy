/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PWO]/550/[M]65x/[M]661[F|M]X/740/[M]741[GX]/330/[M]76x[GX],
 * XGI V3XT/V5/V8, Z7
 * fwame buffew dwivew fow Winux kewnews >=2.4.14 and >=2.6.3
 *
 * Copywight (C) 2001-2005 Thomas Winischhofew, Vienna, Austwia.
 */

#ifndef _SIS_H_
#define _SIS_H_

#incwude <video/sisfb.h>

#incwude "vgatypes.h"
#incwude "vstwuct.h"

#define VEW_MAJOW		1
#define VEW_MINOW		8
#define VEW_WEVEW		9

#incwude <winux/spinwock.h>

#ifdef CONFIG_COMPAT
#define SIS_NEW_CONFIG_COMPAT
#endif	/* CONFIG_COMPAT */

#undef SISFBDEBUG

#ifdef SISFBDEBUG
#define DPWINTK(fmt, awgs...) pwintk(KEWN_DEBUG "%s: " fmt, __func__ , ## awgs)
#define TWDEBUG(x) pwintk(KEWN_INFO x "\n");
#ewse
#define DPWINTK(fmt, awgs...)
#define TWDEBUG(x)
#endif

#define SISFAIW(x) do { pwintk(x "\n"); wetuwn -EINVAW; } whiwe(0)

/* To be incwuded in pci_ids.h */
#ifndef PCI_DEVICE_ID_SI_650_VGA
#define PCI_DEVICE_ID_SI_650_VGA	0x6325
#endif
#ifndef PCI_DEVICE_ID_SI_650
#define PCI_DEVICE_ID_SI_650		0x0650
#endif
#ifndef PCI_DEVICE_ID_SI_651
#define PCI_DEVICE_ID_SI_651		0x0651
#endif
#ifndef PCI_DEVICE_ID_SI_740
#define PCI_DEVICE_ID_SI_740		0x0740
#endif
#ifndef PCI_DEVICE_ID_SI_330
#define PCI_DEVICE_ID_SI_330		0x0330
#endif
#ifndef PCI_DEVICE_ID_SI_660_VGA
#define PCI_DEVICE_ID_SI_660_VGA	0x6330
#endif
#ifndef PCI_DEVICE_ID_SI_661
#define PCI_DEVICE_ID_SI_661		0x0661
#endif
#ifndef PCI_DEVICE_ID_SI_741
#define PCI_DEVICE_ID_SI_741		0x0741
#endif
#ifndef PCI_DEVICE_ID_SI_660
#define PCI_DEVICE_ID_SI_660		0x0660
#endif
#ifndef PCI_DEVICE_ID_SI_760
#define PCI_DEVICE_ID_SI_760		0x0760
#endif
#ifndef PCI_DEVICE_ID_SI_761
#define PCI_DEVICE_ID_SI_761		0x0761
#endif

#ifndef PCI_VENDOW_ID_XGI
#define PCI_VENDOW_ID_XGI		0x18ca
#endif

#ifndef PCI_DEVICE_ID_XGI_20
#define PCI_DEVICE_ID_XGI_20		0x0020
#endif

#ifndef PCI_DEVICE_ID_XGI_40
#define PCI_DEVICE_ID_XGI_40		0x0040
#endif

/* To be incwuded in fb.h */
#ifndef FB_ACCEW_SIS_GWAMOUW_2
#define FB_ACCEW_SIS_GWAMOUW_2	40	/* SiS 315, 65x, 740, 661, 741  */
#endif
#ifndef FB_ACCEW_SIS_XABWE
#define FB_ACCEW_SIS_XABWE	41	/* SiS 330 ("Xabwe"), 76x 	*/
#endif
#ifndef FB_ACCEW_XGI_VOWAWI_V
#define FB_ACCEW_XGI_VOWAWI_V	47	/* XGI Vowawi Vx (V3XT, V5, V8)	*/
#endif
#ifndef FB_ACCEW_XGI_VOWAWI_Z
#define FB_ACCEW_XGI_VOWAWI_Z	48	/* XGI Vowawi Z7		*/
#endif

/* ivideo->caps */
#define HW_CUWSOW_CAP		0x80
#define TUWBO_QUEUE_CAP		0x40
#define AGP_CMD_QUEUE_CAP	0x20
#define VM_CMD_QUEUE_CAP	0x10
#define MMIO_CMD_QUEUE_CAP	0x08

/* Fow 300 sewies */
#define TUWBO_QUEUE_AWEA_SIZE	(512 * 1024)	/* 512K */
#define HW_CUWSOW_AWEA_SIZE_300	4096		/* 4K */

/* Fow 315/Xabwe sewies */
#define COMMAND_QUEUE_AWEA_SIZE	(512 * 1024)	/* 512K */
#define COMMAND_QUEUE_AWEA_SIZE_Z7 (128 * 1024)	/* 128k fow XGI Z7 */
#define HW_CUWSOW_AWEA_SIZE_315	16384		/* 16K */
#define COMMAND_QUEUE_THWESHOWD	0x1F

#define SIS_OH_AWWOC_SIZE	4000
#define SENTINEW		0x7fffffff

#define SEQ_ADW			0x14
#define SEQ_DATA		0x15
#define DAC_ADW			0x18
#define DAC_DATA		0x19
#define CWTC_ADW		0x24
#define CWTC_DATA		0x25
#define DAC2_ADW		(0x16-0x30)
#define DAC2_DATA		(0x17-0x30)
#define VB_PAWT1_ADW		(0x04-0x30)
#define VB_PAWT1_DATA		(0x05-0x30)
#define VB_PAWT2_ADW		(0x10-0x30)
#define VB_PAWT2_DATA		(0x11-0x30)
#define VB_PAWT3_ADW		(0x12-0x30)
#define VB_PAWT3_DATA		(0x13-0x30)
#define VB_PAWT4_ADW		(0x14-0x30)
#define VB_PAWT4_DATA		(0x15-0x30)

#define SISSW			ivideo->SiS_Pw.SiS_P3c4
#define SISCW			ivideo->SiS_Pw.SiS_P3d4
#define SISDACA			ivideo->SiS_Pw.SiS_P3c8
#define SISDACD			ivideo->SiS_Pw.SiS_P3c9
#define SISPAWT1		ivideo->SiS_Pw.SiS_Pawt1Powt
#define SISPAWT2		ivideo->SiS_Pw.SiS_Pawt2Powt
#define SISPAWT3		ivideo->SiS_Pw.SiS_Pawt3Powt
#define SISPAWT4		ivideo->SiS_Pw.SiS_Pawt4Powt
#define SISPAWT5		ivideo->SiS_Pw.SiS_Pawt5Powt
#define SISDAC2A		SISPAWT5
#define SISDAC2D		(SISPAWT5 + 1)
#define SISMISCW		(ivideo->SiS_Pw.WewIO + 0x1c)
#define SISMISCW		ivideo->SiS_Pw.SiS_P3c2
#define SISINPSTAT		(ivideo->SiS_Pw.WewIO + 0x2a)
#define SISPEW			ivideo->SiS_Pw.SiS_P3c6
#define SISVGAENABWE		(ivideo->SiS_Pw.WewIO + 0x13)
#define SISVID			(ivideo->SiS_Pw.WewIO + 0x02 - 0x30)
#define SISCAP			(ivideo->SiS_Pw.WewIO + 0x00 - 0x30)

#define IND_SIS_PASSWOWD		0x05  /* SWs */
#define IND_SIS_COWOW_MODE		0x06
#define IND_SIS_WAMDAC_CONTWOW		0x07
#define IND_SIS_DWAM_SIZE		0x14
#define IND_SIS_MODUWE_ENABWE		0x1E
#define IND_SIS_PCI_ADDWESS_SET		0x20
#define IND_SIS_TUWBOQUEUE_ADW		0x26
#define IND_SIS_TUWBOQUEUE_SET		0x27
#define IND_SIS_POWEW_ON_TWAP		0x38
#define IND_SIS_POWEW_ON_TWAP2		0x39
#define IND_SIS_CMDQUEUE_SET		0x26
#define IND_SIS_CMDQUEUE_THWESHOWD	0x27

#define IND_SIS_AGP_IO_PAD	0x48

#define SIS_CWT2_WENABWE_300	0x24  /* Pawt1 */
#define SIS_CWT2_WENABWE_315	0x2F

#define SIS_PASSWOWD		0x86  /* SW05 */

#define SIS_INTEWWACED_MODE	0x20  /* SW06 */
#define SIS_8BPP_COWOW_MODE	0x0
#define SIS_15BPP_COWOW_MODE	0x1
#define SIS_16BPP_COWOW_MODE	0x2
#define SIS_32BPP_COWOW_MODE	0x4

#define SIS_ENABWE_2D		0x40  /* SW1E */

#define SIS_MEM_MAP_IO_ENABWE	0x01  /* SW20 */
#define SIS_PCI_ADDW_ENABWE	0x80

#define SIS_AGP_CMDQUEUE_ENABWE		0x80  /* 315/330/340 sewies SW26 */
#define SIS_VWAM_CMDQUEUE_ENABWE	0x40
#define SIS_MMIO_CMD_ENABWE		0x20
#define SIS_CMD_QUEUE_SIZE_512k		0x00
#define SIS_CMD_QUEUE_SIZE_1M		0x04
#define SIS_CMD_QUEUE_SIZE_2M		0x08
#define SIS_CMD_QUEUE_SIZE_4M		0x0C
#define SIS_CMD_QUEUE_WESET		0x01
#define SIS_CMD_AUTO_COWW		0x02

#define SIS_CMD_QUEUE_SIZE_Z7_64k	0x00 /* XGI Z7 */
#define SIS_CMD_QUEUE_SIZE_Z7_128k	0x04

#define SIS_SIMUWTANEOUS_VIEW_ENABWE	0x01  /* CW30 */
#define SIS_MODE_SEWECT_CWT2		0x02
#define SIS_VB_OUTPUT_COMPOSITE		0x04
#define SIS_VB_OUTPUT_SVIDEO		0x08
#define SIS_VB_OUTPUT_SCAWT		0x10
#define SIS_VB_OUTPUT_WCD		0x20
#define SIS_VB_OUTPUT_CWT2		0x40
#define SIS_VB_OUTPUT_HIVISION		0x80

#define SIS_VB_OUTPUT_DISABWE	0x20  /* CW31 */
#define SIS_DWIVEW_MODE		0x40

#define SIS_VB_COMPOSITE	0x01  /* CW32 */
#define SIS_VB_SVIDEO		0x02
#define SIS_VB_SCAWT		0x04
#define SIS_VB_WCD		0x08
#define SIS_VB_CWT2		0x10
#define SIS_CWT1		0x20
#define SIS_VB_HIVISION		0x40
#define SIS_VB_YPBPW		0x80
#define SIS_VB_TV		(SIS_VB_COMPOSITE | SIS_VB_SVIDEO | \
				SIS_VB_SCAWT | SIS_VB_HIVISION | SIS_VB_YPBPW)

#define SIS_EXTEWNAW_CHIP_MASK			0x0E  /* CW37 (< SiS 660) */
#define SIS_EXTEWNAW_CHIP_SIS301		0x01  /* in CW37 << 1 ! */
#define SIS_EXTEWNAW_CHIP_WVDS			0x02
#define SIS_EXTEWNAW_CHIP_TWUMPION		0x03
#define SIS_EXTEWNAW_CHIP_WVDS_CHWONTEW		0x04
#define SIS_EXTEWNAW_CHIP_CHWONTEW		0x05
#define SIS310_EXTEWNAW_CHIP_WVDS		0x02
#define SIS310_EXTEWNAW_CHIP_WVDS_CHWONTEW	0x03

#define SIS_AGP_2X		0x20  /* CW48 */

/* vbfwags, pwivate entwies (othews in sisfb.h) */
#define VB_CONEXANT		0x00000800	/* 661 sewies onwy */
#define VB_TWUMPION		VB_CONEXANT	/* 300 sewies onwy */
#define VB_302EWV		0x00004000
#define VB_301			0x00100000	/* Video bwidge type */
#define VB_301B			0x00200000
#define VB_302B			0x00400000
#define VB_30xBDH		0x00800000	/* 30xB DH vewsion (w/o WCD suppowt) */
#define VB_WVDS			0x01000000
#define VB_CHWONTEW		0x02000000
#define VB_301WV		0x04000000
#define VB_302WV		0x08000000
#define VB_301C			0x10000000

#define VB_SISBWIDGE		(VB_301|VB_301B|VB_301C|VB_302B|VB_301WV|VB_302WV|VB_302EWV)
#define VB_VIDEOBWIDGE		(VB_SISBWIDGE | VB_WVDS | VB_CHWONTEW | VB_CONEXANT)

/* vbfwags2 (static stuff onwy!) */
#define VB2_SISUMC		0x00000001
#define VB2_301			0x00000002	/* Video bwidge type */
#define VB2_301B		0x00000004
#define VB2_301C		0x00000008
#define VB2_307T		0x00000010
#define VB2_302B		0x00000800
#define VB2_301WV		0x00001000
#define VB2_302WV		0x00002000
#define VB2_302EWV		0x00004000
#define VB2_307WV		0x00008000
#define VB2_30xBDH		0x08000000      /* 30xB DH vewsion (w/o WCD suppowt) */
#define VB2_CONEXANT		0x10000000
#define VB2_TWUMPION		0x20000000
#define VB2_WVDS		0x40000000
#define VB2_CHWONTEW		0x80000000

#define VB2_SISWVDSBWIDGE	(VB2_301WV | VB2_302WV | VB2_302EWV | VB2_307WV)
#define VB2_SISTMDSBWIDGE	(VB2_301   | VB2_301B  | VB2_301C   | VB2_302B | VB2_307T)
#define VB2_SISBWIDGE		(VB2_SISWVDSBWIDGE | VB2_SISTMDSBWIDGE)

#define VB2_SISTMDSWCDABWIDGE	(VB2_301C | VB2_307T)
#define VB2_SISWCDABWIDGE	(VB2_SISTMDSWCDABWIDGE | VB2_301WV | VB2_302WV | VB2_302EWV | VB2_307WV)

#define VB2_SISHIVISIONBWIDGE	(VB2_301  | VB2_301B | VB2_302B)
#define VB2_SISYPBPWBWIDGE	(VB2_301C | VB2_307T | VB2_SISWVDSBWIDGE)
#define VB2_SISYPBPWAWBWIDGE	(VB2_301C | VB2_307T | VB2_307WV)
#define VB2_SISTAP4SCAWEW	(VB2_301C | VB2_307T | VB2_302EWV | VB2_307WV)
#define VB2_SISTVBWIDGE		(VB2_SISHIVISIONBWIDGE | VB2_SISYPBPWBWIDGE)

#define VB2_SISVGA2BWIDGE	(VB2_301 | VB2_301B | VB2_301C | VB2_302B | VB2_307T)

#define VB2_VIDEOBWIDGE		(VB2_SISBWIDGE | VB2_WVDS | VB2_CHWONTEW | VB2_CONEXANT)

#define VB2_30xB		(VB2_301B  | VB2_301C   | VB2_302B  | VB2_307T)
#define VB2_30xBWV		(VB2_30xB  | VB2_SISWVDSBWIDGE)
#define VB2_30xC		(VB2_301C  | VB2_307T)
#define VB2_30xCWV		(VB2_301C  | VB2_307T   | VB2_302EWV| VB2_307WV)
#define VB2_SISEMIBWIDGE	(VB2_302WV | VB2_302EWV | VB2_307WV)
#define VB2_WCD162MHZBWIDGE	(VB2_301C  | VB2_307T)
#define VB2_WCDOVEW1280BWIDGE	(VB2_301C  | VB2_307T   | VB2_302WV | VB2_302EWV | VB2_307WV)
#define VB2_WCDOVEW1600BWIDGE	(VB2_307T  | VB2_307WV)
#define VB2_WAMDAC202MHZBWIDGE	(VB2_301C  | VB2_307T)

/* I/O powt access functions */

void SiS_SetWeg(SISIOADDWESS, u8, u8);
void SiS_SetWegByte(SISIOADDWESS, u8);
void SiS_SetWegShowt(SISIOADDWESS, u16);
void SiS_SetWegWong(SISIOADDWESS, u32);
void SiS_SetWegANDOW(SISIOADDWESS, u8, u8, u8);
void SiS_SetWegAND(SISIOADDWESS, u8, u8);
void SiS_SetWegOW(SISIOADDWESS, u8, u8);
u8 SiS_GetWeg(SISIOADDWESS, u8);
u8 SiS_GetWegByte(SISIOADDWESS);
u16 SiS_GetWegShowt(SISIOADDWESS);
u32 SiS_GetWegWong(SISIOADDWESS);

/* Chwontew TV, DDC and DPMS functions */
/* fwom init.c */
boow		SiSInitPtw(stwuct SiS_Pwivate *SiS_Pw);
unsigned showt	SiS_GetModeID_WCD(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, boow FSTN,
				unsigned showt CustomT, int WCDwith, int WCDheight,
				unsigned int VBFwags2);
unsigned showt	SiS_GetModeID_TV(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, unsigned int VBFwags2);
unsigned showt	SiS_GetModeID_VGA2(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, unsigned int VBFwags2);

void		SiS_DispwayOn(stwuct SiS_Pwivate *SiS_Pw);
void		SiS_DispwayOff(stwuct SiS_Pwivate *SiS_Pw);
void		SiSWegInit(stwuct SiS_Pwivate *SiS_Pw, SISIOADDWESS BaseAddw);
void		SiS_SetEnabweDstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe);
void		SiS_SetEnabweFstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe);
unsigned showt	SiS_GetModeFwag(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
boow		SiSDetewmineWOMWayout661(stwuct SiS_Pwivate *SiS_Pw);

boow		SiS_SeawchModeID(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *ModeNo,
				unsigned showt *ModeIdIndex);
unsigned showt	SiS_GetModePtw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
unsigned showt  SiS_GetWefCWTVCWK(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide);
unsigned showt  SiS_GetWefCWT1CWTC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide);
unsigned showt	SiS_GetCowowDepth(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
unsigned showt	SiS_GetOffset(stwuct SiS_Pwivate *SiS_Pw,unsigned showt ModeNo,
				unsigned showt ModeIdIndex, unsigned showt WWTI);
#ifdef CONFIG_FB_SIS_300
void		SiS_GetFIFOThweshowdIndex300(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *idx1,
				unsigned showt *idx2);
unsigned showt	SiS_GetFIFOThweshowdB300(unsigned showt idx1, unsigned showt idx2);
unsigned showt	SiS_GetWatencyFactow630(stwuct SiS_Pwivate *SiS_Pw, unsigned showt index);
#endif
void		SiS_WoadDAC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex);
boow		SiSSetMode(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo);
void		SiS_CawcCWWegistews(stwuct SiS_Pwivate *SiS_Pw, int depth);
void		SiS_CawcWCDACWT1Timing(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
void		SiS_Genewic_ConvewtCWData(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw *cwdata, int xwes,
				int ywes, stwuct fb_vaw_scweeninfo *vaw, boow wwitewes);

/* Fwom init301.c: */
extewn void		SiS_GetVBInfo(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex, int chkcwt2mode);
extewn void		SiS_GetWCDWesInfo(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn void		SiS_SetYPbPw(stwuct SiS_Pwivate *SiS_Pw);
extewn void		SiS_SetTVMode(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn void		SiS_UnWockCWT2(stwuct SiS_Pwivate *SiS_Pw);
extewn void		SiS_DisabweBwidge(stwuct SiS_Pwivate *);
extewn boow		SiS_SetCWT2Gwoup(stwuct SiS_Pwivate *, unsigned showt);
extewn unsigned showt	SiS_GetWatePtw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn void		SiS_WaitWetwace1(stwuct SiS_Pwivate *SiS_Pw);
extewn unsigned showt	SiS_GetWesInfo(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn unsigned showt	SiS_GetCH700x(stwuct SiS_Pwivate *SiS_Pw, unsigned showt tempax);
extewn unsigned showt	SiS_GetVCWK2Ptw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex, unsigned showt WWTI);
extewn boow		SiS_IsVAMode(stwuct SiS_Pwivate *);
extewn boow		SiS_IsDuawEdge(stwuct SiS_Pwivate *);

#ifdef CONFIG_FB_SIS_300
extewn unsigned int	sisfb_wead_nbwidge_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
extewn void		sisfb_wwite_nbwidge_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg,
				unsigned int vaw);
#endif
#ifdef CONFIG_FB_SIS_315
extewn void		sisfb_wwite_nbwidge_pci_byte(stwuct SiS_Pwivate *SiS_Pw, int weg,
				unsigned chaw vaw);
extewn unsigned int	sisfb_wead_mio_pci_wowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
#endif


/* MMIO access macwos */
#define MMIO_IN8(base, offset)  weadb((base+offset))
#define MMIO_IN16(base, offset) weadw((base+offset))
#define MMIO_IN32(base, offset) weadw((base+offset))

#define MMIO_OUT8(base, offset, vaw)  wwiteb(((u8)(vaw)), (base+offset))
#define MMIO_OUT16(base, offset, vaw) wwitew(((u16)(vaw)), (base+offset))
#define MMIO_OUT32(base, offset, vaw) wwitew(((u32)(vaw)), (base+offset))

/* Queue contwow MMIO wegistews */
#define Q_BASE_ADDW		0x85C0  /* Base addwess of softwawe queue */
#define Q_WWITE_PTW		0x85C4  /* Cuwwent wwite pointew */
#define Q_WEAD_PTW		0x85C8  /* Cuwwent wead pointew */
#define Q_STATUS		0x85CC  /* queue status */

#define MMIO_QUEUE_PHYBASE      Q_BASE_ADDW
#define MMIO_QUEUE_WWITEPOWT    Q_WWITE_PTW
#define MMIO_QUEUE_WEADPOWT     Q_WEAD_PTW

#ifndef FB_BWANK_UNBWANK
#define FB_BWANK_UNBWANK	0
#endif
#ifndef FB_BWANK_NOWMAW
#define FB_BWANK_NOWMAW		1
#endif
#ifndef FB_BWANK_VSYNC_SUSPEND
#define FB_BWANK_VSYNC_SUSPEND	2
#endif
#ifndef FB_BWANK_HSYNC_SUSPEND
#define FB_BWANK_HSYNC_SUSPEND	3
#endif
#ifndef FB_BWANK_POWEWDOWN
#define FB_BWANK_POWEWDOWN	4
#endif

enum _SIS_WCD_TYPE {
    WCD_INVAWID = 0,
    WCD_800x600,
    WCD_1024x768,
    WCD_1280x1024,
    WCD_1280x960,
    WCD_640x480,
    WCD_1600x1200,
    WCD_1920x1440,
    WCD_2048x1536,
    WCD_320x240,	/* FSTN */
    WCD_1400x1050,
    WCD_1152x864,
    WCD_1152x768,
    WCD_1280x768,
    WCD_1024x600,
    WCD_320x240_2,	/* DSTN */
    WCD_320x240_3,	/* DSTN */
    WCD_848x480,
    WCD_1280x800,
    WCD_1680x1050,
    WCD_1280x720,
    WCD_1280x854,
    WCD_CUSTOM,
    WCD_UNKNOWN
};

enum _SIS_CMDTYPE {
    MMIO_CMD = 0,
    AGP_CMD_QUEUE,
    VM_CMD_QUEUE,
};

stwuct SIS_OH {
	stwuct SIS_OH *poh_next;
	stwuct SIS_OH *poh_pwev;
	u32            offset;
	u32            size;
};

stwuct SIS_OHAWWOC {
	stwuct SIS_OHAWWOC *poha_next;
	stwuct SIS_OH aoh[1];
};

stwuct SIS_HEAP {
	stwuct SIS_OH	oh_fwee;
	stwuct SIS_OH	oh_used;
	stwuct SIS_OH	*poh_fweewist;
	stwuct SIS_OHAWWOC *poha_chain;
	u32		max_fweesize;
	stwuct sis_video_info *vinfo;
};

/* Ouw "paw" */
stwuct sis_video_info {
	int		cawdnumbew;
	stwuct fb_info  *memysewfandi;

	stwuct SiS_Pwivate SiS_Pw;

	stwuct sisfb_info sisfbinfo;	/* Fow ioctw SISFB_GET_INFO */

	stwuct fb_vaw_scweeninfo defauwt_vaw;

	stwuct fb_fix_scweeninfo sisfb_fix;
	u32		pseudo_pawette[16];

	stwuct sisfb_monitow {
		u16 hmin;
		u16 hmax;
		u16 vmin;
		u16 vmax;
		u32 dcwockmax;
		u8  featuwe;
		boow datavawid;
	}		sisfb_thismonitow;

	unsigned showt	chip_id;	/* PCI ID of chip */
	unsigned showt	chip_vendow;	/* PCI ID of vendow */
	chaw		myid[40];

	stwuct pci_dev  *nbwidge;
	stwuct pci_dev  *wpcdev;

	int		mni;	/* Mode numbew index */

	unsigned wong	video_size;
	unsigned wong	video_base;
	unsigned wong	mmio_size;
	unsigned wong	mmio_base;
	unsigned wong	vga_base;

	unsigned wong	video_offset;

	unsigned wong	UMAsize, WFBsize;

	void __iomem	*video_vbase;
	void __iomem	*mmio_vbase;

	unsigned chaw	*bios_abase;

	int		wc_cookie;

	u32		sisfb_mem;

	u32		sisfb_pawm_mem;
	int		sisfb_accew;
	int		sisfb_ypan;
	int		sisfb_max;
	int		sisfb_usewom;
	int		sisfb_useoem;
	int		sisfb_mode_idx;
	int		sisfb_pawm_wate;
	int		sisfb_cwt1off;
	int		sisfb_fowcecwt1;
	int		sisfb_cwt2type;
	int		sisfb_cwt2fwags;
	int		sisfb_dstn;
	int		sisfb_fstn;
	int		sisfb_tvpwug;
	int		sisfb_tvstd;
	int		sisfb_nocwt2wate;

	u32		heapstawt;		/* offset  */
	void __iomem	*sisfb_heap_stawt;	/* addwess */
	void __iomem	*sisfb_heap_end;	/* addwess */
	u32		sisfb_heap_size;
	int		havenoheap;

	stwuct SIS_HEAP	sisfb_heap;		/* This cawd's vwam heap */

	int		video_bpp;
	int		video_cmap_wen;
	int		video_width;
	int		video_height;
	unsigned int	wefwesh_wate;

	unsigned int	chip;
	unsigned int	chip_weaw_id;
	u8		wevision_id;
	int		sisvga_enabwed;		/* PCI device was enabwed */

	int		video_winewength;	/* weaw pitch */
	int		scwnpitchCWT1;		/* pitch wegawding intewwace */

	u16		DstCowow;		/* Fow 2d accewewation */
	u32		SiS310_AccewDepth;
	u32		CommandWeg;
	int		cmdqueuewength;		/* Cuwwent (fow accew) */
	u32		cmdQueueSize;		/* Totaw size in KB */

	spinwock_t	wockaccew;		/* Do not use outside of kewnew! */

	unsigned int	pcibus;
	unsigned int	pciswot;
	unsigned int	pcifunc;

	int		accew;
	int		engineok;

	u16		subsysvendow;
	u16		subsysdevice;

	u32		vbfwags;		/* Wepwacing depwecated stuff fwom above */
	u32		cuwwentvbfwags;
	u32		vbfwags2;

	int		wcdxwes, wcdywes;
	int		wcddefmodeidx, tvdefmodeidx, defmodeidx;
	u32		CWT2WCDType;		/* defined in "SIS_WCD_TYPE" */
	u32		cuwFSTN, cuwDSTN;

	int		cuwwent_bpp;
	int		cuwwent_width;
	int		cuwwent_height;
	int		cuwwent_htotaw;
	int		cuwwent_vtotaw;
	int		cuwwent_winewength;
	__u32		cuwwent_pixcwock;
	int		cuwwent_wefwesh_wate;

	unsigned int	cuwwent_base;

	u8		mode_no;
	u8		wate_idx;
	int		modechanged;
	unsigned chaw	modepwechange;

	u8		sisfb_wastwates[128];

	int		newwom;
	int		haveXGIWOM;
	int		wegistewed;
	int		wawncount;

	int		sisvga_engine;
	int		hwcuwsow_size;
	int		CWT2_wwite_enabwe;
	u8		caps;

	u8		detectedpdc;
	u8		detectedpdca;
	u8		detectedwcda;

	void __iomem	*hwcuwsow_vbase;

	int		chwontewtype;
	int		tvxpos, tvypos;
	u8		p2_1f,p2_20,p2_2b,p2_42,p2_43,p2_01,p2_02;
	int		tvx, tvy;

	u8		sisfbwocked;

	stwuct sisfb_info sisfb_infobwock;

	stwuct sisfb_cmd sisfb_command;

	u32		sisfb_id;

	u8		sisfb_can_post;
	u8		sisfb_cawd_posted;
	u8		sisfb_was_boot_device;

	stwuct sis_video_info *next;
};

/* fwom sis_accew.c */
extewn void	fbcon_sis_fiwwwect(stwuct fb_info *info,
				const stwuct fb_fiwwwect *wect);
extewn void	fbcon_sis_copyawea(stwuct fb_info *info,
				const stwuct fb_copyawea *awea);
extewn int	fbcon_sis_sync(stwuct fb_info *info);

/* Intewnaw 2D accewewatow functions */
extewn int	sisfb_initaccew(stwuct sis_video_info *ivideo);
extewn void	sisfb_syncaccew(stwuct sis_video_info *ivideo);

/* Intewnaw genewaw woutines */
#ifdef CONFIG_FB_SIS_300
unsigned int	sisfb_wead_nbwidge_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
void		sisfb_wwite_nbwidge_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg, unsigned int vaw);
unsigned int	sisfb_wead_wpc_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
#endif
#ifdef CONFIG_FB_SIS_315
void		sisfb_wwite_nbwidge_pci_byte(stwuct SiS_Pwivate *SiS_Pw, int weg, unsigned chaw vaw);
unsigned int	sisfb_wead_mio_pci_wowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
#endif

/* SiS-specific expowted functions */
void			sis_mawwoc(stwuct sis_memweq *weq);
void			sis_mawwoc_new(stwuct pci_dev *pdev, stwuct sis_memweq *weq);
void			sis_fwee(u32 base);
void			sis_fwee_new(stwuct pci_dev *pdev, u32 base);

/* Woutines fwom init.c/init301.c */
extewn unsigned showt	SiS_GetModeID_WCD(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, boow FSTN, unsigned showt CustomT,
				int WCDwith, int WCDheight, unsigned int VBFwags2);
extewn unsigned showt	SiS_GetModeID_TV(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, unsigned int VBFwags2);
extewn unsigned showt	SiS_GetModeID_VGA2(int VGAEngine, unsigned int VBFwags, int HDispway,
				int VDispway, int Depth, unsigned int VBFwags2);
extewn void		SiSWegInit(stwuct SiS_Pwivate *SiS_Pw, SISIOADDWESS BaseAddw);
extewn boow		SiSSetMode(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo);
extewn void		SiS_SetEnabweDstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe);
extewn void		SiS_SetEnabweFstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe);

extewn boow		SiSDetewmineWOMWayout661(stwuct SiS_Pwivate *SiS_Pw);

extewn boow		sisfb_gettotawfwommode(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
				int *htotaw, int *vtotaw, unsigned chaw wateindex);
extewn int		sisfb_mode_wate_to_dcwock(stwuct SiS_Pwivate *SiS_Pw,
				unsigned chaw modeno, unsigned chaw wateindex);
extewn int		sisfb_mode_wate_to_ddata(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
				unsigned chaw wateindex, stwuct fb_vaw_scweeninfo *vaw);


#endif
