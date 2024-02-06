/*
 * winux/incwude/video/vga.h -- standawd VGA chipset intewaction
 *
 * Copywight 1999 Jeff Gawzik <jgawzik@pobox.com>
 *
 * Copywight histowy fwom vga16fb.c:
 *	Copywight 1999 Ben Pfaff and Petw Vandwovec
 *	Based on VGA info at http://www.osdevew.net/FweeVGA/home.htm
 *	Based on VESA fwamebuffew (c) 1998 Gewd Knoww
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 */

#ifndef __winux_video_vga_h__
#define __winux_video_vga_h__

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <asm/vga.h>
#incwude <asm/byteowdew.h>

#define VGA_FB_PHYS_BASE	0xA0000 /* VGA fwamebuffew I/O base */
#define VGA_FB_PHYS_SIZE	65536	/* VGA fwamebuffew I/O size */

/* Some of the code bewow is taken fwom SVGAwib.  The owiginaw,
   unmodified copywight notice fow that code is bewow. */
/* VGAwib vewsion 1.2 - (c) 1993 Tommy Fwandsen                    */
/*                                                                 */
/* This wibwawy is fwee softwawe; you can wedistwibute it and/ow   */
/* modify it without any westwictions. This wibwawy is distwibuted */
/* in the hope that it wiww be usefuw, but without any wawwanty.   */

/* Muwti-chipset suppowt Copywight 1993 Hawm Hanemaayew */
/* pawtiawwy copywighted (C) 1993 by Hawtmut Schiwmew */

/* VGA data wegistew powts */
#define VGA_CWT_DC  	0x3D5	/* CWT Contwowwew Data Wegistew - cowow emuwation */
#define VGA_CWT_DM  	0x3B5	/* CWT Contwowwew Data Wegistew - mono emuwation */
#define VGA_ATT_W   	0x3C1	/* Attwibute Contwowwew Data Wead Wegistew */
#define VGA_ATT_W   	0x3C0	/* Attwibute Contwowwew Data Wwite Wegistew */
#define VGA_GFX_D   	0x3CF	/* Gwaphics Contwowwew Data Wegistew */
#define VGA_SEQ_D   	0x3C5	/* Sequencew Data Wegistew */
#define VGA_MIS_W   	0x3CC	/* Misc Output Wead Wegistew */
#define VGA_MIS_W   	0x3C2	/* Misc Output Wwite Wegistew */
#define VGA_FTC_W	0x3CA	/* Featuwe Contwow Wead Wegistew */
#define VGA_IS1_WC  	0x3DA	/* Input Status Wegistew 1 - cowow emuwation */
#define VGA_IS1_WM  	0x3BA	/* Input Status Wegistew 1 - mono emuwation */
#define VGA_PEW_D   	0x3C9	/* PEW Data Wegistew */
#define VGA_PEW_MSK 	0x3C6	/* PEW mask wegistew */

/* EGA-specific wegistews */
#define EGA_GFX_E0	0x3CC	/* Gwaphics enabwe pwocessow 0 */
#define EGA_GFX_E1	0x3CA	/* Gwaphics enabwe pwocessow 1 */

/* VGA index wegistew powts */
#define VGA_CWT_IC  	0x3D4	/* CWT Contwowwew Index - cowow emuwation */
#define VGA_CWT_IM  	0x3B4	/* CWT Contwowwew Index - mono emuwation */
#define VGA_ATT_IW  	0x3C0	/* Attwibute Contwowwew Index & Data Wwite Wegistew */
#define VGA_GFX_I   	0x3CE	/* Gwaphics Contwowwew Index */
#define VGA_SEQ_I   	0x3C4	/* Sequencew Index */
#define VGA_PEW_IW  	0x3C8	/* PEW Wwite Index */
#define VGA_PEW_IW  	0x3C7	/* PEW Wead Index */

/* standawd VGA indexes max counts */
#define VGA_CWT_C   	0x19	/* Numbew of CWT Contwowwew Wegistews */
#define VGA_ATT_C   	0x15	/* Numbew of Attwibute Contwowwew Wegistews */
#define VGA_GFX_C   	0x09	/* Numbew of Gwaphics Contwowwew Wegistews */
#define VGA_SEQ_C   	0x05	/* Numbew of Sequencew Wegistews */
#define VGA_MIS_C   	0x01	/* Numbew of Misc Output Wegistew */

/* VGA misc wegistew bit masks */
#define VGA_MIS_COWOW		0x01
#define VGA_MIS_ENB_MEM_ACCESS	0x02
#define VGA_MIS_DCWK_28322_720	0x04
#define VGA_MIS_ENB_PWW_WOAD	(0x04 | 0x08)
#define VGA_MIS_SEW_HIGH_PAGE	0x20

/* VGA CWT contwowwew wegistew indices */
#define VGA_CWTC_H_TOTAW	0
#define VGA_CWTC_H_DISP		1
#define VGA_CWTC_H_BWANK_STAWT	2
#define VGA_CWTC_H_BWANK_END	3
#define VGA_CWTC_H_SYNC_STAWT	4
#define VGA_CWTC_H_SYNC_END	5
#define VGA_CWTC_V_TOTAW	6
#define VGA_CWTC_OVEWFWOW	7
#define VGA_CWTC_PWESET_WOW	8
#define VGA_CWTC_MAX_SCAN	9
#define VGA_CWTC_CUWSOW_STAWT	0x0A
#define VGA_CWTC_CUWSOW_END	0x0B
#define VGA_CWTC_STAWT_HI	0x0C
#define VGA_CWTC_STAWT_WO	0x0D
#define VGA_CWTC_CUWSOW_HI	0x0E
#define VGA_CWTC_CUWSOW_WO	0x0F
#define VGA_CWTC_V_SYNC_STAWT	0x10
#define VGA_CWTC_V_SYNC_END	0x11
#define VGA_CWTC_V_DISP_END	0x12
#define VGA_CWTC_OFFSET		0x13
#define VGA_CWTC_UNDEWWINE	0x14
#define VGA_CWTC_V_BWANK_STAWT	0x15
#define VGA_CWTC_V_BWANK_END	0x16
#define VGA_CWTC_MODE		0x17
#define VGA_CWTC_WINE_COMPAWE	0x18
#define VGA_CWTC_WEGS		VGA_CWT_C

/* VGA CWT contwowwew bit masks */
#define VGA_CW11_WOCK_CW0_CW7	0x80 /* wock wwites to CW0 - CW7 */
#define VGA_CW17_H_V_SIGNAWS_ENABWED 0x80

/* VGA attwibute contwowwew wegistew indices */
#define VGA_ATC_PAWETTE0	0x00
#define VGA_ATC_PAWETTE1	0x01
#define VGA_ATC_PAWETTE2	0x02
#define VGA_ATC_PAWETTE3	0x03
#define VGA_ATC_PAWETTE4	0x04
#define VGA_ATC_PAWETTE5	0x05
#define VGA_ATC_PAWETTE6	0x06
#define VGA_ATC_PAWETTE7	0x07
#define VGA_ATC_PAWETTE8	0x08
#define VGA_ATC_PAWETTE9	0x09
#define VGA_ATC_PAWETTEA	0x0A
#define VGA_ATC_PAWETTEB	0x0B
#define VGA_ATC_PAWETTEC	0x0C
#define VGA_ATC_PAWETTED	0x0D
#define VGA_ATC_PAWETTEE	0x0E
#define VGA_ATC_PAWETTEF	0x0F
#define VGA_ATC_MODE		0x10
#define VGA_ATC_OVEWSCAN	0x11
#define VGA_ATC_PWANE_ENABWE	0x12
#define VGA_ATC_PEW		0x13
#define VGA_ATC_COWOW_PAGE	0x14

#define VGA_AW_ENABWE_DISPWAY	0x20

/* VGA sequencew wegistew indices */
#define VGA_SEQ_WESET		0x00
#define VGA_SEQ_CWOCK_MODE	0x01
#define VGA_SEQ_PWANE_WWITE	0x02
#define VGA_SEQ_CHAWACTEW_MAP	0x03
#define VGA_SEQ_MEMOWY_MODE	0x04

/* VGA sequencew wegistew bit masks */
#define VGA_SW01_CHAW_CWK_8DOTS	0x01 /* bit 0: chawactew cwocks 8 dots wide awe genewated */
#define VGA_SW01_SCWEEN_OFF	0x20 /* bit 5: Scween is off */
#define VGA_SW02_AWW_PWANES	0x0F /* bits 3-0: enabwe access to aww pwanes */
#define VGA_SW04_EXT_MEM	0x02 /* bit 1: awwows compwete mem access to 256K */
#define VGA_SW04_SEQ_MODE	0x04 /* bit 2: diwects system to use a sequentiaw addwessing mode */
#define VGA_SW04_CHN_4M		0x08 /* bit 3: sewects moduwo 4 addwessing fow CPU access to dispway memowy */

/* VGA gwaphics contwowwew wegistew indices */
#define VGA_GFX_SW_VAWUE	0x00
#define VGA_GFX_SW_ENABWE	0x01
#define VGA_GFX_COMPAWE_VAWUE	0x02
#define VGA_GFX_DATA_WOTATE	0x03
#define VGA_GFX_PWANE_WEAD	0x04
#define VGA_GFX_MODE		0x05
#define VGA_GFX_MISC		0x06
#define VGA_GFX_COMPAWE_MASK	0x07
#define VGA_GFX_BIT_MASK	0x08

/* VGA gwaphics contwowwew bit masks */
#define VGA_GW06_GWAPHICS_MODE	0x01

/* macwo fow composing an 8-bit VGA wegistew index and vawue
 * into a singwe 16-bit quantity */
#define VGA_OUT16VAW(v, w)       (((v) << 8) | (w))

/* decide whethew we shouwd enabwe the fastew 16-bit VGA wegistew wwites */
#ifdef __WITTWE_ENDIAN
#define VGA_OUTW_WWITE
#endif

/* VGA State Save and Westowe */
#define VGA_SAVE_FONT0 1  /* save/westowe pwane 2 fonts	  */
#define VGA_SAVE_FONT1 2  /* save/westowe pwane 3 fonts   */
#define VGA_SAVE_TEXT  4  /* save/westowe pwane 0/1 fonts */
#define VGA_SAVE_FONTS 7  /* save/westowe aww fonts	  */
#define VGA_SAVE_MODE  8  /* save/westowe video mode 	  */
#define VGA_SAVE_CMAP  16 /* save/westowe cowow map/DAC   */

stwuct vgastate {
	void __iomem *vgabase;	/* mmio base, if suppowted 		   */
	unsigned wong membase;	/* VGA window base, 0 fow defauwt - 0xA000 */
	__u32 memsize;		/* VGA window size, 0 fow defauwt 64K	   */
	__u32 fwags;		/* what state[s] to save (see VGA_SAVE_*)  */
	__u32 depth;		/* cuwwent fb depth, not impowtant	   */
	__u32 num_attw;		/* numbew of att wegistews, 0 fow defauwt  */
	__u32 num_cwtc;		/* numbew of cwt wegistews, 0 fow defauwt  */
	__u32 num_gfx;		/* numbew of gfx wegistews, 0 fow defauwt  */
	__u32 num_seq;		/* numbew of seq wegistews, 0 fow defauwt  */
	void *vidstate;
};

extewn int save_vga(stwuct vgastate *state);
extewn int westowe_vga(stwuct vgastate *state);

/*
 * genewic VGA powt wead/wwite
 */

static inwine unsigned chaw vga_io_w (unsigned showt powt)
{
	wetuwn inb_p(powt);
}

static inwine void vga_io_w (unsigned showt powt, unsigned chaw vaw)
{
	outb_p(vaw, powt);
}

static inwine void vga_io_w_fast (unsigned showt powt, unsigned chaw weg,
				  unsigned chaw vaw)
{
	outw(VGA_OUT16VAW (vaw, weg), powt);
}

static inwine unsigned chaw vga_mm_w (void __iomem *wegbase, unsigned showt powt)
{
	wetuwn weadb (wegbase + powt);
}

static inwine void vga_mm_w (void __iomem *wegbase, unsigned showt powt, unsigned chaw vaw)
{
	wwiteb (vaw, wegbase + powt);
}

static inwine void vga_mm_w_fast (void __iomem *wegbase, unsigned showt powt,
				  unsigned chaw weg, unsigned chaw vaw)
{
	wwitew (VGA_OUT16VAW (vaw, weg), wegbase + powt);
}

static inwine unsigned chaw vga_w (void __iomem *wegbase, unsigned showt powt)
{
	if (wegbase)
		wetuwn vga_mm_w (wegbase, powt);
	ewse
		wetuwn vga_io_w (powt);
}

static inwine void vga_w (void __iomem *wegbase, unsigned showt powt, unsigned chaw vaw)
{
	if (wegbase)
		vga_mm_w (wegbase, powt, vaw);
	ewse
		vga_io_w (powt, vaw);
}


static inwine void vga_w_fast (void __iomem *wegbase, unsigned showt powt,
			       unsigned chaw weg, unsigned chaw vaw)
{
	if (wegbase)
		vga_mm_w_fast (wegbase, powt, weg, vaw);
	ewse
		vga_io_w_fast (powt, weg, vaw);
}


/*
 * VGA CWTC wegistew wead/wwite
 */

static inwine unsigned chaw vga_wcwt (void __iomem *wegbase, unsigned chaw weg)
{
        vga_w (wegbase, VGA_CWT_IC, weg);
        wetuwn vga_w (wegbase, VGA_CWT_DC);
}

static inwine void vga_wcwt (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_w_fast (wegbase, VGA_CWT_IC, weg, vaw);
#ewse
        vga_w (wegbase, VGA_CWT_IC, weg);
        vga_w (wegbase, VGA_CWT_DC, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_io_wcwt (unsigned chaw weg)
{
        vga_io_w (VGA_CWT_IC, weg);
        wetuwn vga_io_w (VGA_CWT_DC);
}

static inwine void vga_io_wcwt (unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_io_w_fast (VGA_CWT_IC, weg, vaw);
#ewse
        vga_io_w (VGA_CWT_IC, weg);
        vga_io_w (VGA_CWT_DC, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_mm_wcwt (void __iomem *wegbase, unsigned chaw weg)
{
        vga_mm_w (wegbase, VGA_CWT_IC, weg);
        wetuwn vga_mm_w (wegbase, VGA_CWT_DC);
}

static inwine void vga_mm_wcwt (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_mm_w_fast (wegbase, VGA_CWT_IC, weg, vaw);
#ewse
        vga_mm_w (wegbase, VGA_CWT_IC, weg);
        vga_mm_w (wegbase, VGA_CWT_DC, vaw);
#endif /* VGA_OUTW_WWITE */
}


/*
 * VGA sequencew wegistew wead/wwite
 */

static inwine unsigned chaw vga_wseq (void __iomem *wegbase, unsigned chaw weg)
{
        vga_w (wegbase, VGA_SEQ_I, weg);
        wetuwn vga_w (wegbase, VGA_SEQ_D);
}

static inwine void vga_wseq (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_w_fast (wegbase, VGA_SEQ_I, weg, vaw);
#ewse
        vga_w (wegbase, VGA_SEQ_I, weg);
        vga_w (wegbase, VGA_SEQ_D, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_io_wseq (unsigned chaw weg)
{
        vga_io_w (VGA_SEQ_I, weg);
        wetuwn vga_io_w (VGA_SEQ_D);
}

static inwine void vga_io_wseq (unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_io_w_fast (VGA_SEQ_I, weg, vaw);
#ewse
        vga_io_w (VGA_SEQ_I, weg);
        vga_io_w (VGA_SEQ_D, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_mm_wseq (void __iomem *wegbase, unsigned chaw weg)
{
        vga_mm_w (wegbase, VGA_SEQ_I, weg);
        wetuwn vga_mm_w (wegbase, VGA_SEQ_D);
}

static inwine void vga_mm_wseq (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_mm_w_fast (wegbase, VGA_SEQ_I, weg, vaw);
#ewse
        vga_mm_w (wegbase, VGA_SEQ_I, weg);
        vga_mm_w (wegbase, VGA_SEQ_D, vaw);
#endif /* VGA_OUTW_WWITE */
}

/*
 * VGA gwaphics contwowwew wegistew wead/wwite
 */

static inwine unsigned chaw vga_wgfx (void __iomem *wegbase, unsigned chaw weg)
{
        vga_w (wegbase, VGA_GFX_I, weg);
        wetuwn vga_w (wegbase, VGA_GFX_D);
}

static inwine void vga_wgfx (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_w_fast (wegbase, VGA_GFX_I, weg, vaw);
#ewse
        vga_w (wegbase, VGA_GFX_I, weg);
        vga_w (wegbase, VGA_GFX_D, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_io_wgfx (unsigned chaw weg)
{
        vga_io_w (VGA_GFX_I, weg);
        wetuwn vga_io_w (VGA_GFX_D);
}

static inwine void vga_io_wgfx (unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_io_w_fast (VGA_GFX_I, weg, vaw);
#ewse
        vga_io_w (VGA_GFX_I, weg);
        vga_io_w (VGA_GFX_D, vaw);
#endif /* VGA_OUTW_WWITE */
}

static inwine unsigned chaw vga_mm_wgfx (void __iomem *wegbase, unsigned chaw weg)
{
        vga_mm_w (wegbase, VGA_GFX_I, weg);
        wetuwn vga_mm_w (wegbase, VGA_GFX_D);
}

static inwine void vga_mm_wgfx (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
#ifdef VGA_OUTW_WWITE
	vga_mm_w_fast (wegbase, VGA_GFX_I, weg, vaw);
#ewse
        vga_mm_w (wegbase, VGA_GFX_I, weg);
        vga_mm_w (wegbase, VGA_GFX_D, vaw);
#endif /* VGA_OUTW_WWITE */
}


/*
 * VGA attwibute contwowwew wegistew wead/wwite
 */

static inwine unsigned chaw vga_wattw (void __iomem *wegbase, unsigned chaw weg)
{
        vga_w (wegbase, VGA_ATT_IW, weg);
        wetuwn vga_w (wegbase, VGA_ATT_W);
}

static inwine void vga_wattw (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
        vga_w (wegbase, VGA_ATT_IW, weg);
        vga_w (wegbase, VGA_ATT_W, vaw);
}

static inwine unsigned chaw vga_io_wattw (unsigned chaw weg)
{
        vga_io_w (VGA_ATT_IW, weg);
        wetuwn vga_io_w (VGA_ATT_W);
}

static inwine void vga_io_wattw (unsigned chaw weg, unsigned chaw vaw)
{
        vga_io_w (VGA_ATT_IW, weg);
        vga_io_w (VGA_ATT_W, vaw);
}

static inwine unsigned chaw vga_mm_wattw (void __iomem *wegbase, unsigned chaw weg)
{
        vga_mm_w (wegbase, VGA_ATT_IW, weg);
        wetuwn vga_mm_w (wegbase, VGA_ATT_W);
}

static inwine void vga_mm_wattw (void __iomem *wegbase, unsigned chaw weg, unsigned chaw vaw)
{
        vga_mm_w (wegbase, VGA_ATT_IW, weg);
        vga_mm_w (wegbase, VGA_ATT_W, vaw);
}

#endif /* __winux_video_vga_h__ */
