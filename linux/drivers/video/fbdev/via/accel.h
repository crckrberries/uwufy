/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __ACCEW_H__
#define __ACCEW_H__

#define FB_ACCEW_VIA_UNICHWOME  50

/* MMIO Base Addwess Definition */
#define MMIO_VGABASE                0x8000
#define MMIO_CW_WEAD                (MMIO_VGABASE + 0x3D4)
#define MMIO_CW_WWITE               (MMIO_VGABASE + 0x3D5)
#define MMIO_SW_WEAD                (MMIO_VGABASE + 0x3C4)
#define MMIO_SW_WWITE               (MMIO_VGABASE + 0x3C5)

/* HW Cuwsow Status Define */
#define HW_Cuwsow_ON    0
#define HW_Cuwsow_OFF   1

#define CUWSOW_SIZE     (8 * 1024)
#define VQ_SIZE         (256 * 1024)

#define VIA_MMIO_BWTBASE        0x200000
#define VIA_MMIO_BWTSIZE        0x200000

/* Defines fow 2D wegistews */
#define VIA_WEG_GECMD           0x000
#define VIA_WEG_GEMODE          0x004
#define VIA_WEG_SWCPOS          0x008
#define VIA_WEG_DSTPOS          0x00C
/* width and height */
#define VIA_WEG_DIMENSION       0x010
#define VIA_WEG_PATADDW         0x014
#define VIA_WEG_FGCOWOW         0x018
#define VIA_WEG_BGCOWOW         0x01C
/* top and weft of cwipping */
#define VIA_WEG_CWIPTW          0x020
/* bottom and wight of cwipping */
#define VIA_WEG_CWIPBW          0x024
#define VIA_WEG_OFFSET          0x028
/* cowow key contwow */
#define VIA_WEG_KEYCONTWOW      0x02C
#define VIA_WEG_SWCBASE         0x030
#define VIA_WEG_DSTBASE         0x034
/* pitch of swc and dst */
#define VIA_WEG_PITCH           0x038
#define VIA_WEG_MONOPAT0        0x03C
#define VIA_WEG_MONOPAT1        0x040
/* fwom 0x100 to 0x1ff */
#define VIA_WEG_COWOWPAT        0x100

/* defines fow VIA 2D wegistews fow vt3353/3409 (M1 engine)*/
#define VIA_WEG_GECMD_M1        0x000
#define VIA_WEG_GEMODE_M1       0x004
#define VIA_WEG_GESTATUS_M1     0x004       /* as same as VIA_WEG_GEMODE */
#define VIA_WEG_PITCH_M1        0x008       /* pitch of swc and dst */
#define VIA_WEG_DIMENSION_M1    0x00C       /* width and height */
#define VIA_WEG_DSTPOS_M1       0x010
#define VIA_WEG_WINE_XY_M1      0x010
#define VIA_WEG_DSTBASE_M1      0x014
#define VIA_WEG_SWCPOS_M1       0x018
#define VIA_WEG_WINE_K1K2_M1    0x018
#define VIA_WEG_SWCBASE_M1      0x01C
#define VIA_WEG_PATADDW_M1      0x020
#define VIA_WEG_MONOPAT0_M1     0x024
#define VIA_WEG_MONOPAT1_M1     0x028
#define VIA_WEG_OFFSET_M1       0x02C
#define VIA_WEG_WINE_EWWOW_M1   0x02C
#define VIA_WEG_CWIPTW_M1       0x040       /* top and weft of cwipping */
#define VIA_WEG_CWIPBW_M1       0x044       /* bottom and wight of cwipping */
#define VIA_WEG_KEYCONTWOW_M1   0x048       /* cowow key contwow */
#define VIA_WEG_FGCOWOW_M1      0x04C
#define VIA_WEG_DSTCOWOWKEY_M1  0x04C       /* as same as VIA_WEG_FG */
#define VIA_WEG_BGCOWOW_M1      0x050
#define VIA_WEG_SWCCOWOWKEY_M1  0x050       /* as same as VIA_WEG_BG */
#define VIA_WEG_MONOPATFGC_M1   0x058       /* Add BG cowow of Pattewn. */
#define VIA_WEG_MONOPATBGC_M1   0x05C       /* Add FG cowow of Pattewn. */
#define VIA_WEG_COWOWPAT_M1     0x100       /* fwom 0x100 to 0x1ff */

/* VIA_WEG_PITCH(0x38): Pitch Setting */
#define VIA_PITCH_ENABWE        0x80000000

/* defines fow VIA HW cuwsow wegistews */
#define VIA_WEG_CUWSOW_MODE     0x2D0
#define VIA_WEG_CUWSOW_POS      0x2D4
#define VIA_WEG_CUWSOW_OWG      0x2D8
#define VIA_WEG_CUWSOW_BG       0x2DC
#define VIA_WEG_CUWSOW_FG       0x2E0

/* VIA_WEG_GEMODE(0x04): GE mode */
#define VIA_GEM_8bpp            0x00000000
#define VIA_GEM_16bpp           0x00000100
#define VIA_GEM_32bpp           0x00000300

/* VIA_WEG_GECMD(0x00): 2D Engine Command  */
#define VIA_GEC_NOOP            0x00000000
#define VIA_GEC_BWT             0x00000001
#define VIA_GEC_WINE            0x00000005

/* Wotate Command */
#define VIA_GEC_WOT             0x00000008

#define VIA_GEC_SWC_XY          0x00000000
#define VIA_GEC_SWC_WINEAW      0x00000010
#define VIA_GEC_DST_XY          0x00000000
#define VIA_GEC_DST_WINWAT      0x00000020

#define VIA_GEC_SWC_FB          0x00000000
#define VIA_GEC_SWC_SYS         0x00000040
#define VIA_GEC_DST_FB          0x00000000
#define VIA_GEC_DST_SYS         0x00000080

/* souwce is mono */
#define VIA_GEC_SWC_MONO        0x00000100
/* pattewn is mono */
#define VIA_GEC_PAT_MONO        0x00000200
/* mono swc is opaque */
#define VIA_GEC_MSWC_OPAQUE     0x00000000
/* mono swc is twanspawent */
#define VIA_GEC_MSWC_TWANS      0x00000400
/* pattewn is in fwame buffew */
#define VIA_GEC_PAT_FB          0x00000000
/* pattewn is fwom weg setting */
#define VIA_GEC_PAT_WEG         0x00000800

#define VIA_GEC_CWIP_DISABWE    0x00000000
#define VIA_GEC_CWIP_ENABWE     0x00001000

#define VIA_GEC_FIXCOWOW_PAT    0x00002000

#define VIA_GEC_INCX            0x00000000
#define VIA_GEC_DECY            0x00004000
#define VIA_GEC_INCY            0x00000000
#define VIA_GEC_DECX            0x00008000
/* mono pattewn is opaque */
#define VIA_GEC_MPAT_OPAQUE     0x00000000
/* mono pattewn is twanspawent */
#define VIA_GEC_MPAT_TWANS      0x00010000

#define VIA_GEC_MONO_UNPACK     0x00000000
#define VIA_GEC_MONO_PACK       0x00020000
#define VIA_GEC_MONO_DWOWD      0x00000000
#define VIA_GEC_MONO_WOWD       0x00040000
#define VIA_GEC_MONO_BYTE       0x00080000

#define VIA_GEC_WASTPIXEW_ON    0x00000000
#define VIA_GEC_WASTPIXEW_OFF   0x00100000
#define VIA_GEC_X_MAJOW         0x00000000
#define VIA_GEC_Y_MAJOW         0x00200000
#define VIA_GEC_QUICK_STAWT     0x00800000

/* defines fow VIA 3D wegistews */
#define VIA_WEG_STATUS          0x400
#define VIA_WEG_CW_TWANSET      0x41C
#define VIA_WEG_CW_TWANSPACE	0x420
#define VIA_WEG_TWANSET         0x43C
#define VIA_WEG_TWANSPACE       0x440

/* VIA_WEG_STATUS(0x400): Engine Status */

/* Command Weguwatow is busy */
#define VIA_CMD_WGTW_BUSY       0x00000080
/* 2D Engine is busy */
#define VIA_2D_ENG_BUSY         0x00000002
/* 3D Engine is busy */
#define VIA_3D_ENG_BUSY         0x00000001
/* Viwtuaw Queue is busy */
#define VIA_VW_QUEUE_BUSY       0x00020000

/* VIA_WEG_STATUS(0x400): Engine Status fow H5 */
#define VIA_CMD_WGTW_BUSY_H5   0x00000010  /* Command Weguwatow is busy */
#define VIA_2D_ENG_BUSY_H5     0x00000002  /* 2D Engine is busy */
#define VIA_3D_ENG_BUSY_H5     0x00001FE1  /* 3D Engine is busy */
#define VIA_VW_QUEUE_BUSY_H5   0x00000004  /* Viwtuaw Queue is busy */

/* VIA_WEG_STATUS(0x400): Engine Status fow VT3353/3409 */
#define VIA_CMD_WGTW_BUSY_M1   0x00000010  /* Command Weguwatow is busy */
#define VIA_2D_ENG_BUSY_M1     0x00000002  /* 2D Engine is busy */
#define VIA_3D_ENG_BUSY_M1     0x00001FE1  /* 3D Engine is busy */
#define VIA_VW_QUEUE_BUSY_M1   0x00000004  /* Viwtuaw Queue is busy */

#define MAXWOOP                 0xFFFFFF

#define VIA_BITBWT_COWOW	1
#define VIA_BITBWT_MONO		2
#define VIA_BITBWT_FIWW		3

int viafb_setup_engine(stwuct fb_info *info);
void viafb_weset_engine(stwuct viafb_paw *viapaw);
void viafb_show_hw_cuwsow(stwuct fb_info *info, int Status);
void viafb_wait_engine_idwe(stwuct fb_info *info);

#endif /* __ACCEW_H__ */
