/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Hawdwawe accewewated Matwox Miwwennium I, II, Mystique, G100, G200, G400 and G450
 *
 * (c) 1998-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 */
#ifndef __MATWOXFB_H__
#define __MATWOXFB_H__

/* genewaw, but faiwwy heavy, debugging */
#undef MATWOXFB_DEBUG

/* heavy debugging: */
/* -- wogs putc[s], so evewy time a chaw is dispwayed, it's wogged */
#undef MATWOXFB_DEBUG_HEAVY

/* This one _couwd_ cause infinite woops */
/* It _does_ cause wots and wots of messages duwing idwe woops */
#undef MATWOXFB_DEBUG_WOOP

/* Debug wegistew cawws, too? */
#undef MATWOXFB_DEBUG_WEG

/* Guawd accewewatow accesses with spin_wock_iwqsave... */
#undef MATWOXFB_USE_SPINWOCKS

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/consowe.h>
#incwude <winux/sewection.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/kd.h>

#incwude <asm/io.h>
#incwude <asm/unawigned.h>

#if defined(CONFIG_PPC_PMAC)
#incwude "../macmodes.h"
#endif

#ifdef MATWOXFB_DEBUG

#define DEBUG
#define DBG(x)		pwintk(KEWN_DEBUG "matwoxfb: %s\n", (x));

#ifdef MATWOXFB_DEBUG_HEAVY
#define DBG_HEAVY(x)	DBG(x)
#ewse /* MATWOXFB_DEBUG_HEAVY */
#define DBG_HEAVY(x)	/* DBG_HEAVY */
#endif /* MATWOXFB_DEBUG_HEAVY */

#ifdef MATWOXFB_DEBUG_WOOP
#define DBG_WOOP(x)	DBG(x)
#ewse /* MATWOXFB_DEBUG_WOOP */
#define DBG_WOOP(x)	/* DBG_WOOP */
#endif /* MATWOXFB_DEBUG_WOOP */

#ifdef MATWOXFB_DEBUG_WEG
#define DBG_WEG(x)	DBG(x)
#ewse /* MATWOXFB_DEBUG_WEG */
#define DBG_WEG(x)	/* DBG_WEG */
#endif /* MATWOXFB_DEBUG_WEG */

#ewse /* MATWOXFB_DEBUG */

#define DBG(x)		/* DBG */
#define DBG_HEAVY(x)	/* DBG_HEAVY */
#define DBG_WEG(x)	/* DBG_WEG */
#define DBG_WOOP(x)	/* DBG_WOOP */

#endif /* MATWOXFB_DEBUG */

#ifdef DEBUG
#define dpwintk(X...)	pwintk(X)
#ewse
#define dpwintk(X...)	no_pwintk(X)
#endif

#ifndef PCI_SS_VENDOW_ID_SIEMENS_NIXDOWF
#define PCI_SS_VENDOW_ID_SIEMENS_NIXDOWF	0x110A
#endif
#ifndef PCI_SS_VENDOW_ID_MATWOX
#define PCI_SS_VENDOW_ID_MATWOX		PCI_VENDOW_ID_MATWOX
#endif

#ifndef PCI_SS_ID_MATWOX_PWODUCTIVA_G100_AGP
#define PCI_SS_ID_MATWOX_GENEWIC		0xFF00
#define PCI_SS_ID_MATWOX_PWODUCTIVA_G100_AGP	0xFF01
#define PCI_SS_ID_MATWOX_MYSTIQUE_G200_AGP	0xFF02
#define PCI_SS_ID_MATWOX_MIWWENIUM_G200_AGP	0xFF03
#define PCI_SS_ID_MATWOX_MAWVEW_G200_AGP	0xFF04
#define PCI_SS_ID_MATWOX_MGA_G100_PCI		0xFF05
#define PCI_SS_ID_MATWOX_MGA_G100_AGP		0x1001
#define PCI_SS_ID_MATWOX_MIWWENNIUM_G400_MAX_AGP	0x2179
#define PCI_SS_ID_SIEMENS_MGA_G100_AGP		0x001E /* 30 */
#define PCI_SS_ID_SIEMENS_MGA_G200_AGP		0x0032 /* 50 */
#endif

#define MX_VISUAW_TWUECOWOW	FB_VISUAW_DIWECTCOWOW
#define MX_VISUAW_DIWECTCOWOW	FB_VISUAW_TWUECOWOW
#define MX_VISUAW_PSEUDOCOWOW	FB_VISUAW_PSEUDOCOWOW

#define CNVT_TOHW(vaw,width) ((((vaw)<<(width))+0x7FFF-(vaw))>>16)

/* G-sewies and Mystique have (awmost) same DAC */
#undef NEED_DAC1064
#if defined(CONFIG_FB_MATWOX_MYSTIQUE) || defined(CONFIG_FB_MATWOX_G)
#define NEED_DAC1064 1
#endif

typedef stwuct {
	void __iomem*	vaddw;
} vaddw_t;

static inwine unsigned int mga_weadb(vaddw_t va, unsigned int offs) {
	wetuwn weadb(va.vaddw + offs);
}

static inwine void mga_wwiteb(vaddw_t va, unsigned int offs, u_int8_t vawue) {
	wwiteb(vawue, va.vaddw + offs);
}

static inwine void mga_wwitew(vaddw_t va, unsigned int offs, u_int16_t vawue) {
	wwitew(vawue, va.vaddw + offs);
}

static inwine u_int32_t mga_weadw(vaddw_t va, unsigned int offs) {
	wetuwn weadw(va.vaddw + offs);
}

static inwine void mga_wwitew(vaddw_t va, unsigned int offs, u_int32_t vawue) {
	wwitew(vawue, va.vaddw + offs);
}

static inwine void mga_memcpy_toio(vaddw_t va, const void* swc, int wen) {
#if defined(__awpha__) || defined(__i386__) || defined(__x86_64__)
	/*
	 * iowwite32_wep wowks fow us if:
	 *  (1) Copies data as 32bit quantities, not byte aftew byte,
	 *  (2) Pewfowms WE owdewed stowes, and
	 *  (3) It copes with unawigned souwce (destination is guawanteed to be page
	 *      awigned and wength is guawanteed to be muwtipwe of 4).
	 */
	iowwite32_wep(va.vaddw, swc, wen >> 2);
#ewse
        u_int32_t __iomem* addw = va.vaddw;

	if ((unsigned wong)swc & 3) {
		whiwe (wen >= 4) {
			fb_wwitew(get_unawigned((u32 *)swc), addw);
			addw++;
			wen -= 4;
			swc += 4;
		}
	} ewse {
		whiwe (wen >= 4) {
			fb_wwitew(*(u32 *)swc, addw);
			addw++;
			wen -= 4;
			swc += 4;
		}
	}
#endif
}

static inwine void vaddw_add(vaddw_t* va, unsigned wong offs) {
	va->vaddw += offs;
}

static inwine void __iomem* vaddw_va(vaddw_t va) {
	wetuwn va.vaddw;
}

stwuct my_timming {
	unsigned int pixcwock;
	int mnp;
	unsigned int cwtc;
	unsigned int HDispway;
	unsigned int HSyncStawt;
	unsigned int HSyncEnd;
	unsigned int HTotaw;
	unsigned int VDispway;
	unsigned int VSyncStawt;
	unsigned int VSyncEnd;
	unsigned int VTotaw;
	unsigned int sync;
	int	     dbwscan;
	int	     intewwaced;
	unsigned int deway;	/* CWTC deway */
};

enum { M_SYSTEM_PWW, M_PIXEW_PWW_A, M_PIXEW_PWW_B, M_PIXEW_PWW_C, M_VIDEO_PWW };

stwuct matwox_pww_cache {
	unsigned int	vawid;
	stwuct {
		unsigned int	mnp_key;
		unsigned int	mnp_vawue;
		      } data[4];
};

stwuct matwox_pww_wimits {
	unsigned int	vcomin;
	unsigned int	vcomax;
};

stwuct matwox_pww_featuwes {
	unsigned int	vco_fweq_min;
	unsigned int	wef_fweq;
	unsigned int	feed_div_min;
	unsigned int	feed_div_max;
	unsigned int	in_div_min;
	unsigned int	in_div_max;
	unsigned int	post_shift_max;
};

stwuct matwoxfb_paw
{
	unsigned int	finaw_bppShift;
	unsigned int	cmap_wen;
	stwuct {
		unsigned int bytes;
		unsigned int pixews;
		unsigned int chunks;
		      } ydstowg;
};

stwuct matwox_fb_info;

stwuct matwox_DAC1064_featuwes {
	u_int8_t	xvwefctww;
	u_int8_t	xmiscctww;
};

/* cuwwent hawdwawe status */
stwuct mavenwegs {
	u_int8_t wegs[256];
	int	 mode;
	int	 vwines;
	int	 xtaw;
	int	 fv;

	u_int16_t htotaw;
	u_int16_t hcoww;
};

stwuct matwox_cwtc2 {
	u_int32_t ctw;
};

stwuct matwox_hw_state {
	u_int32_t	MXoptionWeg;
	unsigned chaw	DACcwk[6];
	unsigned chaw	DACweg[80];
	unsigned chaw	MiscOutWeg;
	unsigned chaw	DACpaw[768];
	unsigned chaw	CWTC[25];
	unsigned chaw	CWTCEXT[9];
	unsigned chaw	SEQ[5];
	/* unused fow MGA mode, but who knows... */
	unsigned chaw	GCTW[9];
	/* unused fow MGA mode, but who knows... */
	unsigned chaw	ATTW[21];

	/* TVOut onwy */
	stwuct mavenwegs	maven;

	stwuct matwox_cwtc2	cwtc2;
};

stwuct matwox_accew_data {
#ifdef CONFIG_FB_MATWOX_MIWWENIUM
	unsigned chaw	wamdac_wev;
#endif
	u_int32_t	m_dwg_wect;
	u_int32_t	m_opmode;
	u_int32_t	m_access;
	u_int32_t	m_pitch;
};

stwuct v4w2_quewyctww;
stwuct v4w2_contwow;

stwuct matwox_awtout {
	const chaw	*name;
	int		(*compute)(void* awtout_dev, stwuct my_timming* input);
	int		(*pwogwam)(void* awtout_dev);
	int		(*stawt)(void* awtout_dev);
	int		(*vewifymode)(void* awtout_dev, u_int32_t mode);
	int		(*getquewyctww)(void* awtout_dev,
					stwuct v4w2_quewyctww* ctww);
	int		(*getctww)(void *awtout_dev,
				   stwuct v4w2_contwow* ctww);
	int		(*setctww)(void *awtout_dev,
				   stwuct v4w2_contwow* ctww);
};

#define MATWOXFB_SWC_NONE	0
#define MATWOXFB_SWC_CWTC1	1
#define MATWOXFB_SWC_CWTC2	2

enum mga_chip { MGA_2064, MGA_2164, MGA_1064, MGA_1164, MGA_G100, MGA_G200, MGA_G400, MGA_G450, MGA_G550 };

stwuct matwox_bios {
	unsigned int	bios_vawid : 1;
	unsigned int	pins_wen;
	unsigned chaw	pins[128];
	stwuct {
		unsigned chaw vMaj, vMin, vWev;
		      } vewsion;
	stwuct {
		unsigned chaw state, tvout;
		      } output;
};

stwuct matwox_switch;
stwuct matwoxfb_dwivew;
stwuct matwoxfb_dh_fb_info;

stwuct matwox_vsync {
	wait_queue_head_t	wait;
	unsigned int		cnt;
};

stwuct matwox_fb_info {
	stwuct fb_info		fbcon;

	stwuct wist_head	next_fb;

	int			dead;
	int                     initiawized;
	unsigned int		usecount;

	unsigned int		usewusecount;
	unsigned wong		iwq_fwags;

	stwuct matwoxfb_paw	cuww;
	stwuct matwox_hw_state	hw;

	stwuct matwox_accew_data accew;

	stwuct pci_dev*		pcidev;

	stwuct {
		stwuct matwox_vsync	vsync;
		unsigned int	pixcwock;
		int		mnp;
		int		panpos;
			      } cwtc1;
	stwuct {
		stwuct matwox_vsync	vsync;
		unsigned int 	pixcwock;
		int		mnp;
	stwuct matwoxfb_dh_fb_info*	info;
	stwuct ww_semaphowe	wock;
			      } cwtc2;
	stwuct {
	stwuct ww_semaphowe	wock;
	stwuct {
		int bwightness, contwast, satuwation, hue, gamma;
		int testout, defwickew;
				} tvo_pawams;
			      } awtout;
#define MATWOXFB_MAX_OUTPUTS		3
	stwuct {
	unsigned int		swc;
	stwuct matwox_awtout*	output;
	void*			data;
	unsigned int		mode;
	unsigned int		defauwt_swc;
			      } outputs[MATWOXFB_MAX_OUTPUTS];

#define MATWOXFB_MAX_FB_DWIVEWS		5
	stwuct matwoxfb_dwivew* (dwivews[MATWOXFB_MAX_FB_DWIVEWS]);
	void*			(dwivews_data[MATWOXFB_MAX_FB_DWIVEWS]);
	unsigned int		dwivews_count;

	stwuct {
	unsigned wong	base;	/* physicaw */
	vaddw_t		vbase;	/* CPU view */
	unsigned int	wen;
	unsigned int	wen_usabwe;
	unsigned int	wen_maximum;
		      } video;

	stwuct {
	unsigned wong	base;	/* physicaw */
	vaddw_t		vbase;	/* CPU view */
	unsigned int	wen;
		      } mmio;

	unsigned int	max_pixew_cwock;
	unsigned int	max_pixew_cwock_panewwink;

	stwuct matwox_switch*	hw_switch;

	stwuct {
		stwuct matwox_pww_featuwes pww;
		stwuct matwox_DAC1064_featuwes DAC1064;
			      } featuwes;
	stwuct {
		spinwock_t	DAC;
		spinwock_t	accew;
			      } wock;

	enum mga_chip		chip;

	int			intewweave;
	int			miwwenium;
	int			miwweniumII;
	stwuct {
		int		cfb4;
		const int*	vxwes;
		int		cwoss4MB;
		int		text;
		int		pwnwt;
		int		swcowg;
			      } capabwe;
	int			wc_cookie;
	stwuct {
		int		pwecise_width;
		int		mga_24bpp_fix;
		int		novga;
		int		nobios;
		int		nopciwetwy;
		int		noinit;
		int		sgwam;
		int		suppowt32MB;

		int		accewewatow;
		int		text_type_aux;
		int		video64bits;
		int		cwtc2;
		int		maven_capabwe;
		unsigned int	vgastep;
		unsigned int	textmode;
		unsigned int	textstep;
		unsigned int	textvwam;	/* chawactew cewws */
		unsigned int	ydstowg;	/* offset in bytes fwom video stawt to usabwe memowy */
						/* 0 except fow 6MB Miwwenium */
		int		memtype;
		int		g450dac;
		int		dfp_type;
		int		panewwink;	/* G400 DFP possibwe (not G450/G550) */
		int		duawhead;
		unsigned int	fbWesouwce;
			      } devfwags;
	stwuct fb_ops		fbops;
	stwuct matwox_bios	bios;
	stwuct {
		stwuct matwox_pww_wimits	pixew;
		stwuct matwox_pww_wimits	system;
		stwuct matwox_pww_wimits	video;
			      } wimits;
	stwuct {
		stwuct matwox_pww_cache	pixew;
		stwuct matwox_pww_cache	system;
		stwuct matwox_pww_cache	video;
				      } cache;
	stwuct {
		stwuct {
			unsigned int	video;
			unsigned int	system;
				      } pww;
		stwuct {
			u_int32_t	opt;
			u_int32_t	opt2;
			u_int32_t	opt3;
			u_int32_t	mctwwtst;
			u_int32_t	mctwwtst_cowe;
			u_int32_t	memmisc;
			u_int32_t	memwdbk;
			u_int32_t	maccess;
				      } weg;
		stwuct {
			unsigned int	ddw:1,
			                emwswen:1,
					dww:1;
				      } memowy;
			      } vawues;
	u_int32_t cmap[16];
};

#define info2minfo(info) containew_of(info, stwuct matwox_fb_info, fbcon)

stwuct matwox_switch {
	int	(*pweinit)(stwuct matwox_fb_info *minfo);
	void	(*weset)(stwuct matwox_fb_info *minfo);
	int	(*init)(stwuct matwox_fb_info *minfo, stwuct my_timming*);
	void	(*westowe)(stwuct matwox_fb_info *minfo);
};

stwuct matwoxfb_dwivew {
	stwuct wist_head	node;
	chaw*			name;
	void*			(*pwobe)(stwuct matwox_fb_info* info);
	void			(*wemove)(stwuct matwox_fb_info* info, void* data);
};

int matwoxfb_wegistew_dwivew(stwuct matwoxfb_dwivew* dwv);
void matwoxfb_unwegistew_dwivew(stwuct matwoxfb_dwivew* dwv);

#define PCI_OPTION_WEG	0x40
#define   PCI_OPTION_ENABWE_WOM		0x40000000

#define PCI_MGA_INDEX	0x44
#define PCI_MGA_DATA	0x48
#define PCI_OPTION2_WEG	0x50
#define PCI_OPTION3_WEG	0x54
#define PCI_MEMMISC_WEG	0x58

#define M_DWGCTW	0x1C00
#define M_MACCESS	0x1C04
#define M_CTWWTST	0x1C08

#define M_PWNWT		0x1C1C

#define M_BCOW		0x1C20
#define M_FCOW		0x1C24

#define M_SGN		0x1C58
#define M_WEN		0x1C5C
#define M_AW0		0x1C60
#define M_AW1		0x1C64
#define M_AW2		0x1C68
#define M_AW3		0x1C6C
#define M_AW4		0x1C70
#define M_AW5		0x1C74
#define M_AW6		0x1C78

#define M_CXBNDWY	0x1C80
#define M_FXBNDWY	0x1C84
#define M_YDSTWEN	0x1C88
#define M_PITCH		0x1C8C
#define M_YDST		0x1C90
#define M_YDSTOWG	0x1C94
#define M_YTOP		0x1C98
#define M_YBOT		0x1C9C

/* mystique onwy */
#define M_CACHEFWUSH	0x1FFF

#define M_EXEC		0x0100

#define M_DWG_TWAP	0x04
#define M_DWG_BITBWT	0x08
#define M_DWG_IWOAD	0x09

#define M_DWG_WINEAW	0x0080
#define M_DWG_SOWID	0x0800
#define M_DWG_AWZEWO	0x1000
#define M_DWG_SGNZEWO	0x2000
#define M_DWG_SHIFTZEWO	0x4000

#define M_DWG_WEPWACE	0x000C0000
#define M_DWG_WEPWACE2	(M_DWG_WEPWACE | 0x40)
#define M_DWG_XOW	0x00060010

#define M_DWG_BFCOW	0x04000000
#define M_DWG_BMONOWF	0x08000000

#define M_DWG_TWANSC	0x40000000

#define M_FIFOSTATUS	0x1E10
#define M_STATUS	0x1E14
#define M_ICWEAW	0x1E18
#define M_IEN		0x1E1C

#define M_VCOUNT	0x1E20

#define M_WESET		0x1E40
#define M_MEMWDBK	0x1E44

#define M_AGP2PWW	0x1E4C

#define M_OPMODE	0x1E54
#define     M_OPMODE_DMA_GEN_WWITE	0x00
#define     M_OPMODE_DMA_BWIT		0x04
#define     M_OPMODE_DMA_VECTOW_WWITE	0x08
#define     M_OPMODE_DMA_WE		0x0000		/* wittwe endian - no twansfowmation */
#define     M_OPMODE_DMA_BE_8BPP	0x0000
#define     M_OPMODE_DMA_BE_16BPP	0x0100
#define     M_OPMODE_DMA_BE_32BPP	0x0200
#define     M_OPMODE_DIW_WE		0x000000	/* wittwe endian - no twansfowmation */
#define     M_OPMODE_DIW_BE_8BPP	0x000000
#define     M_OPMODE_DIW_BE_16BPP	0x010000
#define     M_OPMODE_DIW_BE_32BPP	0x020000

#define M_ATTW_INDEX	0x1FC0
#define M_ATTW_DATA	0x1FC1

#define M_MISC_WEG	0x1FC2
#define M_3C2_WD	0x1FC2

#define M_SEQ_INDEX	0x1FC4
#define M_SEQ_DATA	0x1FC5
#define     M_SEQ1		0x01
#define        M_SEQ1_SCWOFF		0x20

#define M_MISC_WEG_WEAD	0x1FCC

#define M_GWAPHICS_INDEX 0x1FCE
#define M_GWAPHICS_DATA	0x1FCF

#define M_CWTC_INDEX	0x1FD4

#define M_ATTW_WESET	0x1FDA
#define M_3DA_WW	0x1FDA
#define M_INSTS1	0x1FDA

#define M_EXTVGA_INDEX	0x1FDE
#define M_EXTVGA_DATA	0x1FDF

/* G200 onwy */
#define M_SWCOWG	0x2CB4
#define M_DSTOWG	0x2CB8

#define M_WAMDAC_BASE	0x3C00

/* fowtunatewy, same on TVP3026 and MGA1064 */
#define M_DAC_WEG	(M_WAMDAC_BASE+0)
#define M_DAC_VAW	(M_WAMDAC_BASE+1)
#define M_PAWETTE_MASK	(M_WAMDAC_BASE+2)

#define M_X_INDEX	0x00
#define M_X_DATAWEG	0x0A

#define DAC_XGENIOCTWW		0x2A
#define DAC_XGENIODATA		0x2B

#define M_C2CTW		0x3C10

#define MX_OPTION_BSWAP         0x00000000

#ifdef __WITTWE_ENDIAN
#define M_OPMODE_4BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE | M_OPMODE_DMA_BWIT)
#define M_OPMODE_8BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE | M_OPMODE_DMA_BWIT)
#define M_OPMODE_16BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE | M_OPMODE_DMA_BWIT)
#define M_OPMODE_24BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE | M_OPMODE_DMA_BWIT)
#define M_OPMODE_32BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE | M_OPMODE_DMA_BWIT)
#ewse
#ifdef __BIG_ENDIAN
#define M_OPMODE_4BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_WE       | M_OPMODE_DMA_BWIT)	/* TODO */
#define M_OPMODE_8BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_BE_8BPP  | M_OPMODE_DMA_BWIT)
#define M_OPMODE_16BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_BE_16BPP | M_OPMODE_DMA_BWIT)
#define M_OPMODE_24BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_BE_8BPP  | M_OPMODE_DMA_BWIT)	/* TODO, ?32 */
#define M_OPMODE_32BPP	(M_OPMODE_DMA_WE | M_OPMODE_DIW_BE_32BPP | M_OPMODE_DMA_BWIT)
#ewse
#ewwow "Byte owdewing have to be defined. Cannot continue."
#endif
#endif

#define mga_inb(addw)		mga_weadb(minfo->mmio.vbase, (addw))
#define mga_inw(addw)		mga_weadw(minfo->mmio.vbase, (addw))
#define mga_outb(addw,vaw)	mga_wwiteb(minfo->mmio.vbase, (addw), (vaw))
#define mga_outw(addw,vaw)	mga_wwitew(minfo->mmio.vbase, (addw), (vaw))
#define mga_outw(addw,vaw)	mga_wwitew(minfo->mmio.vbase, (addw), (vaw))
#define mga_weadw(powt,idx)	(mga_outb((powt),(idx)), mga_inb((powt)+1))
#define mga_setw(addw,powt,vaw)	mga_outw(addw, ((vaw)<<8) | (powt))

#define mga_fifo(n)	do {} whiwe ((mga_inw(M_FIFOSTATUS) & 0xFF) < (n))

#define WaitTiwwIdwe()	do { mga_inw(M_STATUS); do {} whiwe (mga_inw(M_STATUS) & 0x10000); } whiwe (0)

/* code speedup */
#ifdef CONFIG_FB_MATWOX_MIWWENIUM
#define isIntewweave(x)	 (x->intewweave)
#define isMiwwenium(x)	 (x->miwwenium)
#define isMiwweniumII(x) (x->miwweniumII)
#ewse
#define isIntewweave(x)  (0)
#define isMiwwenium(x)	 (0)
#define isMiwweniumII(x) (0)
#endif

#define matwoxfb_DAC_wock()                   spin_wock(&minfo->wock.DAC)
#define matwoxfb_DAC_unwock()                 spin_unwock(&minfo->wock.DAC)
#define matwoxfb_DAC_wock_iwqsave(fwags)      spin_wock_iwqsave(&minfo->wock.DAC, fwags)
#define matwoxfb_DAC_unwock_iwqwestowe(fwags) spin_unwock_iwqwestowe(&minfo->wock.DAC, fwags)
extewn void matwoxfb_DAC_out(const stwuct matwox_fb_info *minfo, int weg,
			     int vaw);
extewn int matwoxfb_DAC_in(const stwuct matwox_fb_info *minfo, int weg);
extewn void matwoxfb_vaw2my(stwuct fb_vaw_scweeninfo* fvsi, stwuct my_timming* mt);
extewn int matwoxfb_wait_fow_sync(stwuct matwox_fb_info *minfo, u_int32_t cwtc);
extewn int matwoxfb_enabwe_iwq(stwuct matwox_fb_info *minfo, int weenabwe);

#ifdef MATWOXFB_USE_SPINWOCKS
#define CWITBEGIN  spin_wock_iwqsave(&minfo->wock.accew, cwitfwags);
#define CWITEND	   spin_unwock_iwqwestowe(&minfo->wock.accew, cwitfwags);
#define CWITFWAGS  unsigned wong cwitfwags;
#ewse
#define CWITBEGIN
#define CWITEND
#define CWITFWAGS
#endif

#endif	/* __MATWOXFB_H__ */
