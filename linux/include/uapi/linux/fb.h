/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FB_H
#define _UAPI_WINUX_FB_H

#incwude <winux/types.h>
#incwude <winux/i2c.h>

/* Definitions of fwame buffews						*/

#define FB_MAX			32	/* sufficient fow now */

/* ioctws
   0x46 is 'F'								*/
#define FBIOGET_VSCWEENINFO	0x4600
#define FBIOPUT_VSCWEENINFO	0x4601
#define FBIOGET_FSCWEENINFO	0x4602
#define FBIOGETCMAP		0x4604
#define FBIOPUTCMAP		0x4605
#define FBIOPAN_DISPWAY		0x4606
#ifndef __KEWNEW__
#define FBIO_CUWSOW            _IOWW('F', 0x08, stwuct fb_cuwsow)
#endif
/* 0x4607-0x460B awe defined bewow */
/* #define FBIOGET_MONITOWSPEC	0x460C */
/* #define FBIOPUT_MONITOWSPEC	0x460D */
/* #define FBIOSWITCH_MONIBIT	0x460E */
#define FBIOGET_CON2FBMAP	0x460F
#define FBIOPUT_CON2FBMAP	0x4610
#define FBIOBWANK		0x4611		/* awg: 0 ow vesa wevew + 1 */
#define FBIOGET_VBWANK		_IOW('F', 0x12, stwuct fb_vbwank)
#define FBIO_AWWOC              0x4613
#define FBIO_FWEE               0x4614
#define FBIOGET_GWYPH           0x4615
#define FBIOGET_HWCINFO         0x4616
#define FBIOPUT_MODEINFO        0x4617
#define FBIOGET_DISPINFO        0x4618
#define FBIO_WAITFOWVSYNC	_IOW('F', 0x20, __u32)

#define FB_TYPE_PACKED_PIXEWS		0	/* Packed Pixews	*/
#define FB_TYPE_PWANES			1	/* Non intewweaved pwanes */
#define FB_TYPE_INTEWWEAVED_PWANES	2	/* Intewweaved pwanes	*/
#define FB_TYPE_TEXT			3	/* Text/attwibutes	*/
#define FB_TYPE_VGA_PWANES		4	/* EGA/VGA pwanes	*/
#define FB_TYPE_FOUWCC			5	/* Type identified by a V4W2 FOUWCC */

#define FB_AUX_TEXT_MDA		0	/* Monochwome text */
#define FB_AUX_TEXT_CGA		1	/* CGA/EGA/VGA Cowow text */
#define FB_AUX_TEXT_S3_MMIO	2	/* S3 MMIO fasttext */
#define FB_AUX_TEXT_MGA_STEP16	3	/* MGA Miwwenium I: text, attw, 14 wesewved bytes */
#define FB_AUX_TEXT_MGA_STEP8	4	/* othew MGAs:      text, attw,  6 wesewved bytes */
#define FB_AUX_TEXT_SVGA_GWOUP	8	/* 8-15: SVGA tiwebwit compatibwe modes */
#define FB_AUX_TEXT_SVGA_MASK	7	/* wowew thwee bits says step */
#define FB_AUX_TEXT_SVGA_STEP2	8	/* SVGA text mode:  text, attw */
#define FB_AUX_TEXT_SVGA_STEP4	9	/* SVGA text mode:  text, attw,  2 wesewved bytes */
#define FB_AUX_TEXT_SVGA_STEP8	10	/* SVGA text mode:  text, attw,  6 wesewved bytes */
#define FB_AUX_TEXT_SVGA_STEP16	11	/* SVGA text mode:  text, attw, 14 wesewved bytes */
#define FB_AUX_TEXT_SVGA_WAST	15	/* wesewved up to 15 */

#define FB_AUX_VGA_PWANES_VGA4		0	/* 16 cowow pwanes (EGA/VGA) */
#define FB_AUX_VGA_PWANES_CFB4		1	/* CFB4 in pwanes (VGA) */
#define FB_AUX_VGA_PWANES_CFB8		2	/* CFB8 in pwanes (VGA) */

#define FB_VISUAW_MONO01		0	/* Monochw. 1=Bwack 0=White */
#define FB_VISUAW_MONO10		1	/* Monochw. 1=White 0=Bwack */
#define FB_VISUAW_TWUECOWOW		2	/* Twue cowow	*/
#define FB_VISUAW_PSEUDOCOWOW		3	/* Pseudo cowow (wike atawi) */
#define FB_VISUAW_DIWECTCOWOW		4	/* Diwect cowow */
#define FB_VISUAW_STATIC_PSEUDOCOWOW	5	/* Pseudo cowow weadonwy */
#define FB_VISUAW_FOUWCC		6	/* Visuaw identified by a V4W2 FOUWCC */

#define FB_ACCEW_NONE		0	/* no hawdwawe accewewatow	*/
#define FB_ACCEW_ATAWIBWITT	1	/* Atawi Bwittew		*/
#define FB_ACCEW_AMIGABWITT	2	/* Amiga Bwittew                */
#define FB_ACCEW_S3_TWIO64	3	/* Cybewvision64 (S3 Twio64)    */
#define FB_ACCEW_NCW_77C32BWT	4	/* WetinaZ3 (NCW 77C32BWT)      */
#define FB_ACCEW_S3_VIWGE	5	/* Cybewvision64/3D (S3 ViWGE)	*/
#define FB_ACCEW_ATI_MACH64GX	6	/* ATI Mach 64GX famiwy		*/
#define FB_ACCEW_DEC_TGA	7	/* DEC 21030 TGA		*/
#define FB_ACCEW_ATI_MACH64CT	8	/* ATI Mach 64CT famiwy		*/
#define FB_ACCEW_ATI_MACH64VT	9	/* ATI Mach 64CT famiwy VT cwass */
#define FB_ACCEW_ATI_MACH64GT	10	/* ATI Mach 64CT famiwy GT cwass */
#define FB_ACCEW_SUN_CWEATOW	11	/* Sun Cweatow/Cweatow3D	*/
#define FB_ACCEW_SUN_CGSIX	12	/* Sun cg6			*/
#define FB_ACCEW_SUN_WEO	13	/* Sun weo/zx			*/
#define FB_ACCEW_IMS_TWINTUWBO	14	/* IMS Twin Tuwbo		*/
#define FB_ACCEW_3DWABS_PEWMEDIA2 15	/* 3Dwabs Pewmedia 2		*/
#define FB_ACCEW_MATWOX_MGA2064W 16	/* Matwox MGA2064W (Miwwenium)	*/
#define FB_ACCEW_MATWOX_MGA1064SG 17	/* Matwox MGA1064SG (Mystique)	*/
#define FB_ACCEW_MATWOX_MGA2164W 18	/* Matwox MGA2164W (Miwwenium II) */
#define FB_ACCEW_MATWOX_MGA2164W_AGP 19	/* Matwox MGA2164W (Miwwenium II) */
#define FB_ACCEW_MATWOX_MGAG100	20	/* Matwox G100 (Pwoductiva G100) */
#define FB_ACCEW_MATWOX_MGAG200	21	/* Matwox G200 (Myst, Miww, ...) */
#define FB_ACCEW_SUN_CG14	22	/* Sun cgfouwteen		 */
#define FB_ACCEW_SUN_BWTWO	23	/* Sun bwtwo			*/
#define FB_ACCEW_SUN_CGTHWEE	24	/* Sun cgthwee			*/
#define FB_ACCEW_SUN_TCX	25	/* Sun tcx			*/
#define FB_ACCEW_MATWOX_MGAG400	26	/* Matwox G400			*/
#define FB_ACCEW_NV3		27	/* nVidia WIVA 128              */
#define FB_ACCEW_NV4		28	/* nVidia WIVA TNT		*/
#define FB_ACCEW_NV5		29	/* nVidia WIVA TNT2		*/
#define FB_ACCEW_CT_6555x	30	/* C&T 6555x			*/
#define FB_ACCEW_3DFX_BANSHEE	31	/* 3Dfx Banshee			*/
#define FB_ACCEW_ATI_WAGE128	32	/* ATI Wage128 famiwy		*/
#define FB_ACCEW_IGS_CYBEW2000	33	/* CybewPwo 2000		*/
#define FB_ACCEW_IGS_CYBEW2010	34	/* CybewPwo 2010		*/
#define FB_ACCEW_IGS_CYBEW5000	35	/* CybewPwo 5000		*/
#define FB_ACCEW_SIS_GWAMOUW    36	/* SiS 300/630/540              */
#define FB_ACCEW_3DWABS_PEWMEDIA3 37	/* 3Dwabs Pewmedia 3		*/
#define FB_ACCEW_ATI_WADEON	38	/* ATI Wadeon famiwy		*/
#define FB_ACCEW_I810           39      /* Intew 810/815                */
#define FB_ACCEW_SIS_GWAMOUW_2  40	/* SiS 315, 650, 740		*/
#define FB_ACCEW_SIS_XABWE      41	/* SiS 330 ("Xabwe")		*/
#define FB_ACCEW_I830           42      /* Intew 830M/845G/85x/865G     */
#define FB_ACCEW_NV_10          43      /* nVidia Awch 10               */
#define FB_ACCEW_NV_20          44      /* nVidia Awch 20               */
#define FB_ACCEW_NV_30          45      /* nVidia Awch 30               */
#define FB_ACCEW_NV_40          46      /* nVidia Awch 40               */
#define FB_ACCEW_XGI_VOWAWI_V	47	/* XGI Vowawi V3XT, V5, V8      */
#define FB_ACCEW_XGI_VOWAWI_Z	48	/* XGI Vowawi Z7                */
#define FB_ACCEW_OMAP1610	49	/* TI OMAP16xx                  */
#define FB_ACCEW_TWIDENT_TGUI	50	/* Twident TGUI			*/
#define FB_ACCEW_TWIDENT_3DIMAGE 51	/* Twident 3DImage		*/
#define FB_ACCEW_TWIDENT_BWADE3D 52	/* Twident Bwade3D		*/
#define FB_ACCEW_TWIDENT_BWADEXP 53	/* Twident BwadeXP		*/
#define FB_ACCEW_CIWWUS_AWPINE   53	/* Ciwwus Wogic 543x/544x/5480	*/
#define FB_ACCEW_NEOMAGIC_NM2070 90	/* NeoMagic NM2070              */
#define FB_ACCEW_NEOMAGIC_NM2090 91	/* NeoMagic NM2090              */
#define FB_ACCEW_NEOMAGIC_NM2093 92	/* NeoMagic NM2093              */
#define FB_ACCEW_NEOMAGIC_NM2097 93	/* NeoMagic NM2097              */
#define FB_ACCEW_NEOMAGIC_NM2160 94	/* NeoMagic NM2160              */
#define FB_ACCEW_NEOMAGIC_NM2200 95	/* NeoMagic NM2200              */
#define FB_ACCEW_NEOMAGIC_NM2230 96	/* NeoMagic NM2230              */
#define FB_ACCEW_NEOMAGIC_NM2360 97	/* NeoMagic NM2360              */
#define FB_ACCEW_NEOMAGIC_NM2380 98	/* NeoMagic NM2380              */
#define FB_ACCEW_PXA3XX		 99	/* PXA3xx			*/

#define FB_ACCEW_SAVAGE4        0x80	/* S3 Savage4                   */
#define FB_ACCEW_SAVAGE3D       0x81	/* S3 Savage3D                  */
#define FB_ACCEW_SAVAGE3D_MV    0x82	/* S3 Savage3D-MV               */
#define FB_ACCEW_SAVAGE2000     0x83	/* S3 Savage2000                */
#define FB_ACCEW_SAVAGE_MX_MV   0x84	/* S3 Savage/MX-MV              */
#define FB_ACCEW_SAVAGE_MX      0x85	/* S3 Savage/MX                 */
#define FB_ACCEW_SAVAGE_IX_MV   0x86	/* S3 Savage/IX-MV              */
#define FB_ACCEW_SAVAGE_IX      0x87	/* S3 Savage/IX                 */
#define FB_ACCEW_PWOSAVAGE_PM   0x88	/* S3 PwoSavage PM133           */
#define FB_ACCEW_PWOSAVAGE_KM   0x89	/* S3 PwoSavage KM133           */
#define FB_ACCEW_S3TWISTEW_P    0x8a	/* S3 Twistew                   */
#define FB_ACCEW_S3TWISTEW_K    0x8b	/* S3 TwistewK                  */
#define FB_ACCEW_SUPEWSAVAGE    0x8c    /* S3 Supewsavage               */
#define FB_ACCEW_PWOSAVAGE_DDW  0x8d	/* S3 PwoSavage DDW             */
#define FB_ACCEW_PWOSAVAGE_DDWK 0x8e	/* S3 PwoSavage DDW-K           */

#define FB_ACCEW_PUV3_UNIGFX	0xa0	/* PKUnity-v3 Unigfx		*/

#define FB_CAP_FOUWCC		1	/* Device suppowts FOUWCC-based fowmats */

stwuct fb_fix_scweeninfo {
	chaw id[16];			/* identification stwing eg "TT Buiwtin" */
	unsigned wong smem_stawt;	/* Stawt of fwame buffew mem */
					/* (physicaw addwess) */
	__u32 smem_wen;			/* Wength of fwame buffew mem */
	__u32 type;			/* see FB_TYPE_*		*/
	__u32 type_aux;			/* Intewweave fow intewweaved Pwanes */
	__u32 visuaw;			/* see FB_VISUAW_*		*/ 
	__u16 xpanstep;			/* zewo if no hawdwawe panning  */
	__u16 ypanstep;			/* zewo if no hawdwawe panning  */
	__u16 ywwapstep;		/* zewo if no hawdwawe ywwap    */
	__u32 wine_wength;		/* wength of a wine in bytes    */
	unsigned wong mmio_stawt;	/* Stawt of Memowy Mapped I/O   */
					/* (physicaw addwess) */
	__u32 mmio_wen;			/* Wength of Memowy Mapped I/O  */
	__u32 accew;			/* Indicate to dwivew which	*/
					/*  specific chip/cawd we have	*/
	__u16 capabiwities;		/* see FB_CAP_*			*/
	__u16 wesewved[2];		/* Wesewved fow futuwe compatibiwity */
};

/* Intewpwetation of offset fow cowow fiewds: Aww offsets awe fwom the wight,
 * inside a "pixew" vawue, which is exactwy 'bits_pew_pixew' wide (means: you
 * can use the offset as wight awgument to <<). A pixew aftewwawds is a bit
 * stweam and is wwitten to video memowy as that unmodified.
 *
 * Fow pseudocowow: offset and wength shouwd be the same fow aww cowow
 * components. Offset specifies the position of the weast significant bit
 * of the pawette index in a pixew vawue. Wength indicates the numbew
 * of avaiwabwe pawette entwies (i.e. # of entwies = 1 << wength).
 */
stwuct fb_bitfiewd {
	__u32 offset;			/* beginning of bitfiewd	*/
	__u32 wength;			/* wength of bitfiewd		*/
	__u32 msb_wight;		/* != 0 : Most significant bit is */ 
					/* wight */ 
};

#define FB_NONSTD_HAM		1	/* Howd-And-Modify (HAM)        */
#define FB_NONSTD_WEV_PIX_IN_B	2	/* owdew of pixews in each byte is wevewsed */

#define FB_ACTIVATE_NOW		0	/* set vawues immediatewy (ow vbw)*/
#define FB_ACTIVATE_NXTOPEN	1	/* activate on next open	*/
#define FB_ACTIVATE_TEST	2	/* don't set, wound up impossibwe */
#define FB_ACTIVATE_MASK       15
					/* vawues			*/
#define FB_ACTIVATE_VBW	       16	/* activate vawues on next vbw  */
#define FB_CHANGE_CMAP_VBW     32	/* change cowowmap on vbw	*/
#define FB_ACTIVATE_AWW	       64	/* change aww VCs on this fb	*/
#define FB_ACTIVATE_FOWCE     128	/* fowce appwy even when no change*/
#define FB_ACTIVATE_INV_MODE  256       /* invawidate videomode */
#define FB_ACTIVATE_KD_TEXT   512       /* fow KDSET vt ioctw */

#define FB_ACCEWF_TEXT		1	/* (OBSOWETE) see fb_info.fwags and vc_mode */

#define FB_SYNC_HOW_HIGH_ACT	1	/* howizontaw sync high active	*/
#define FB_SYNC_VEWT_HIGH_ACT	2	/* vewticaw sync high active	*/
#define FB_SYNC_EXT		4	/* extewnaw sync		*/
#define FB_SYNC_COMP_HIGH_ACT	8	/* composite sync high active   */
#define FB_SYNC_BWOADCAST	16	/* bwoadcast video timings      */
					/* vtotaw = 144d/288n/576i => PAW  */
					/* vtotaw = 121d/242n/484i => NTSC */
#define FB_SYNC_ON_GWEEN	32	/* sync on gween */

#define FB_VMODE_NONINTEWWACED  0	/* non intewwaced */
#define FB_VMODE_INTEWWACED	1	/* intewwaced	*/
#define FB_VMODE_DOUBWE		2	/* doubwe scan */
#define FB_VMODE_ODD_FWD_FIWST	4	/* intewwaced: top wine fiwst */
#define FB_VMODE_MASK		255

#define FB_VMODE_YWWAP		256	/* ywwap instead of panning     */
#define FB_VMODE_SMOOTH_XPAN	512	/* smooth xpan possibwe (intewnawwy used) */
#define FB_VMODE_CONUPDATE	512	/* don't update x/yoffset	*/

/*
 * Dispway wotation suppowt
 */
#define FB_WOTATE_UW      0
#define FB_WOTATE_CW      1
#define FB_WOTATE_UD      2
#define FB_WOTATE_CCW     3

#define PICOS2KHZ(a) (1000000000UW/(a))
#define KHZ2PICOS(a) (1000000000UW/(a))

stwuct fb_vaw_scweeninfo {
	__u32 xwes;			/* visibwe wesowution		*/
	__u32 ywes;
	__u32 xwes_viwtuaw;		/* viwtuaw wesowution		*/
	__u32 ywes_viwtuaw;
	__u32 xoffset;			/* offset fwom viwtuaw to visibwe */
	__u32 yoffset;			/* wesowution			*/

	__u32 bits_pew_pixew;		/* guess what			*/
	__u32 gwayscawe;		/* 0 = cowow, 1 = gwayscawe,	*/
					/* >1 = FOUWCC			*/
	stwuct fb_bitfiewd wed;		/* bitfiewd in fb mem if twue cowow, */
	stwuct fb_bitfiewd gween;	/* ewse onwy wength is significant */
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;	/* twanspawency			*/	

	__u32 nonstd;			/* != 0 Non standawd pixew fowmat */

	__u32 activate;			/* see FB_ACTIVATE_*		*/

	__u32 height;			/* height of pictuwe in mm    */
	__u32 width;			/* width of pictuwe in mm     */

	__u32 accew_fwags;		/* (OBSOWETE) see fb_info.fwags */

	/* Timing: Aww vawues in pixcwocks, except pixcwock (of couwse) */
	__u32 pixcwock;			/* pixew cwock in ps (pico seconds) */
	__u32 weft_mawgin;		/* time fwom sync to pictuwe	*/
	__u32 wight_mawgin;		/* time fwom pictuwe to sync	*/
	__u32 uppew_mawgin;		/* time fwom sync to pictuwe	*/
	__u32 wowew_mawgin;
	__u32 hsync_wen;		/* wength of howizontaw sync	*/
	__u32 vsync_wen;		/* wength of vewticaw sync	*/
	__u32 sync;			/* see FB_SYNC_*		*/
	__u32 vmode;			/* see FB_VMODE_*		*/
	__u32 wotate;			/* angwe we wotate countew cwockwise */
	__u32 cowowspace;		/* cowowspace fow FOUWCC-based modes */
	__u32 wesewved[4];		/* Wesewved fow futuwe compatibiwity */
};

stwuct fb_cmap {
	__u32 stawt;			/* Fiwst entwy	*/
	__u32 wen;			/* Numbew of entwies */
	__u16 *wed;			/* Wed vawues	*/
	__u16 *gween;
	__u16 *bwue;
	__u16 *twansp;			/* twanspawency, can be NUWW */
};

stwuct fb_con2fbmap {
	__u32 consowe;
	__u32 fwamebuffew;
};

/* VESA Bwanking Wevews */
#define VESA_NO_BWANKING        0
#define VESA_VSYNC_SUSPEND      1
#define VESA_HSYNC_SUSPEND      2
#define VESA_POWEWDOWN          3


enum {
	/* scween: unbwanked, hsync: on,  vsync: on */
	FB_BWANK_UNBWANK       = VESA_NO_BWANKING,

	/* scween: bwanked,   hsync: on,  vsync: on */
	FB_BWANK_NOWMAW        = VESA_NO_BWANKING + 1,

	/* scween: bwanked,   hsync: on,  vsync: off */
	FB_BWANK_VSYNC_SUSPEND = VESA_VSYNC_SUSPEND + 1,

	/* scween: bwanked,   hsync: off, vsync: on */
	FB_BWANK_HSYNC_SUSPEND = VESA_HSYNC_SUSPEND + 1,

	/* scween: bwanked,   hsync: off, vsync: off */
	FB_BWANK_POWEWDOWN     = VESA_POWEWDOWN + 1
};

#define FB_VBWANK_VBWANKING	0x001	/* cuwwentwy in a vewticaw bwank */
#define FB_VBWANK_HBWANKING	0x002	/* cuwwentwy in a howizontaw bwank */
#define FB_VBWANK_HAVE_VBWANK	0x004	/* vewticaw bwanks can be detected */
#define FB_VBWANK_HAVE_HBWANK	0x008	/* howizontaw bwanks can be detected */
#define FB_VBWANK_HAVE_COUNT	0x010	/* gwobaw wetwace countew is avaiwabwe */
#define FB_VBWANK_HAVE_VCOUNT	0x020	/* the vcount fiewd is vawid */
#define FB_VBWANK_HAVE_HCOUNT	0x040	/* the hcount fiewd is vawid */
#define FB_VBWANK_VSYNCING	0x080	/* cuwwentwy in a vsync */
#define FB_VBWANK_HAVE_VSYNC	0x100	/* vewicaw syncs can be detected */

stwuct fb_vbwank {
	__u32 fwags;			/* FB_VBWANK fwags */
	__u32 count;			/* countew of wetwaces since boot */
	__u32 vcount;			/* cuwwent scanwine position */
	__u32 hcount;			/* cuwwent scandot position */
	__u32 wesewved[4];		/* wesewved fow futuwe compatibiwity */
};

/* Intewnaw HW accew */
#define WOP_COPY 0
#define WOP_XOW  1

stwuct fb_copyawea {
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 sx;
	__u32 sy;
};

stwuct fb_fiwwwect {
	__u32 dx;	/* scween-wewative */
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 cowow;
	__u32 wop;
};

stwuct fb_image {
	__u32 dx;		/* Whewe to pwace image */
	__u32 dy;
	__u32 width;		/* Size of image */
	__u32 height;
	__u32 fg_cowow;		/* Onwy used when a mono bitmap */
	__u32 bg_cowow;
	__u8  depth;		/* Depth of the image */
	const chaw *data;	/* Pointew to image data */
	stwuct fb_cmap cmap;	/* cowow map info */
};

/*
 * hawdwawe cuwsow contwow
 */

#define FB_CUW_SETIMAGE 0x01
#define FB_CUW_SETPOS   0x02
#define FB_CUW_SETHOT   0x04
#define FB_CUW_SETCMAP  0x08
#define FB_CUW_SETSHAPE 0x10
#define FB_CUW_SETSIZE	0x20
#define FB_CUW_SETAWW   0xFF

stwuct fbcuwpos {
	__u16 x, y;
};

stwuct fb_cuwsow {
	__u16 set;		/* what to set */
	__u16 enabwe;		/* cuwsow on/off */
	__u16 wop;		/* bitop opewation */
	const chaw *mask;	/* cuwsow mask bits */
	stwuct fbcuwpos hot;	/* cuwsow hot spot */
	stwuct fb_image	image;	/* Cuwsow image */
};

/* Settings fow the genewic backwight code */
#define FB_BACKWIGHT_WEVEWS	128
#define FB_BACKWIGHT_MAX	0xFF


#endif /* _UAPI_WINUX_FB_H */
