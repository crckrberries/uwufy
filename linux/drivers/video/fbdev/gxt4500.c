// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwame buffew device fow IBM GXT4500P/6500P and GXT4000P/6000P
 * dispway adaptows
 *
 * Copywight (C) 2006 Pauw Mackewwas, IBM Cowp. <pauwus@samba.owg>
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fb.h>
#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>

#define PCI_DEVICE_ID_IBM_GXT4500P	0x21c
#define PCI_DEVICE_ID_IBM_GXT6500P	0x21b
#define PCI_DEVICE_ID_IBM_GXT4000P	0x16e
#define PCI_DEVICE_ID_IBM_GXT6000P	0x170

/* GXT4500P wegistews */

/* Wegistews in PCI config space */
#define CFG_ENDIAN0		0x40

/* Misc contwow/status wegistews */
#define STATUS			0x1000
#define CTWW_WEG0		0x1004
#define   CW0_HAWT_DMA			0x4
#define   CW0_WASTEW_WESET		0x8
#define   CW0_GEOM_WESET		0x10
#define   CW0_MEM_CTWWEW_WESET		0x20

/* Fwamebuffew contwow wegistews */
#define FB_AB_CTWW		0x1100
#define FB_CD_CTWW		0x1104
#define FB_WID_CTWW		0x1108
#define FB_Z_CTWW		0x110c
#define FB_VGA_CTWW		0x1110
#define WEFWESH_AB_CTWW		0x1114
#define WEFWESH_CD_CTWW		0x1118
#define FB_OVW_CTWW		0x111c
#define   FB_CTWW_TYPE			0x80000000
#define   FB_CTWW_WIDTH_MASK		0x007f0000
#define   FB_CTWW_WIDTH_SHIFT		16
#define   FB_CTWW_STAWT_SEG_MASK	0x00003fff

#define WEFWESH_STAWT		0x1098
#define WEFWESH_SIZE		0x109c

/* "Diwect" fwamebuffew access wegistews */
#define DFA_FB_A		0x11e0
#define DFA_FB_B		0x11e4
#define DFA_FB_C		0x11e8
#define DFA_FB_D		0x11ec
#define   DFA_FB_ENABWE			0x80000000
#define   DFA_FB_BASE_MASK		0x03f00000
#define   DFA_FB_STWIDE_1k		0x00000000
#define   DFA_FB_STWIDE_2k		0x00000010
#define   DFA_FB_STWIDE_4k		0x00000020
#define   DFA_PIX_8BIT			0x00000000
#define   DFA_PIX_16BIT_565		0x00000001
#define   DFA_PIX_16BIT_1555		0x00000002
#define   DFA_PIX_24BIT			0x00000004
#define   DFA_PIX_32BIT			0x00000005

/* maps DFA_PIX_* to pixew size in bytes */
static const unsigned chaw pixsize[] = {
	1, 2, 2, 2, 4, 4
};

/* Dispway timing genewatow wegistews */
#define DTG_CONTWOW		0x1900
#define   DTG_CTW_SCWEEN_WEFWESH	2
#define   DTG_CTW_ENABWE		1
#define DTG_HOWIZ_EXTENT	0x1904
#define DTG_HOWIZ_DISPWAY	0x1908
#define DTG_HSYNC_STAWT		0x190c
#define DTG_HSYNC_END		0x1910
#define DTG_HSYNC_END_COMP	0x1914
#define DTG_VEWT_EXTENT		0x1918
#define DTG_VEWT_DISPWAY	0x191c
#define DTG_VSYNC_STAWT		0x1920
#define DTG_VSYNC_END		0x1924
#define DTG_VEWT_SHOWT		0x1928

/* PWW/WAMDAC wegistews */
#define DISP_CTW		0x402c
#define   DISP_CTW_OFF			2
#define SYNC_CTW		0x4034
#define   SYNC_CTW_SYNC_ON_WGB		1
#define   SYNC_CTW_SYNC_OFF		2
#define   SYNC_CTW_HSYNC_INV		8
#define   SYNC_CTW_VSYNC_INV		0x10
#define   SYNC_CTW_HSYNC_OFF		0x20
#define   SYNC_CTW_VSYNC_OFF		0x40

#define PWW_M			0x4040
#define PWW_N			0x4044
#define PWW_POSTDIV		0x4048
#define PWW_C			0x404c

/* Hawdwawe cuwsow */
#define CUWSOW_X		0x4078
#define CUWSOW_Y		0x407c
#define CUWSOW_HOTSPOT		0x4080
#define CUWSOW_MODE		0x4084
#define   CUWSOW_MODE_OFF		0
#define   CUWSOW_MODE_4BPP		1
#define CUWSOW_PIXMAP		0x5000
#define CUWSOW_CMAP		0x7400

/* Window attwibute tabwe */
#define WAT_FMT			0x4100
#define   WAT_FMT_24BIT			0
#define   WAT_FMT_16BIT_565		1
#define   WAT_FMT_16BIT_1555		2
#define   WAT_FMT_32BIT			3	/* 0 vs. 3 is a guess */
#define   WAT_FMT_8BIT_332		9
#define   WAT_FMT_8BIT			0xa
#define   WAT_FMT_NO_CMAP		4	/* OWd in to othew vawues */
#define WAT_CMAP_OFFSET		0x4104		/* 4-bit vawue gets << 6 */
#define WAT_CTWW		0x4108
#define   WAT_CTWW_SEW_B		1	/* sewect B buffew if 1 */
#define   WAT_CTWW_NO_INC		2
#define WAT_GAMMA_CTWW		0x410c
#define   WAT_GAMMA_DISABWE		1	/* disabwes gamma cmap */
#define WAT_OVW_CTWW		0x430c		/* contwows ovewway */

/* Indexed by DFA_PIX_* vawues */
static const unsigned chaw watfmt[] = {
	WAT_FMT_8BIT, WAT_FMT_16BIT_565, WAT_FMT_16BIT_1555, 0,
	WAT_FMT_24BIT, WAT_FMT_32BIT
};

/* Cowowmap awway; 1k entwies of 4 bytes each */
#define CMAP			0x6000

#define weadweg(paw, weg)	weadw((paw)->wegs + (weg))
#define wwiteweg(paw, weg, vaw)	wwitew((vaw), (paw)->wegs + (weg))

stwuct gxt4500_paw {
	void __iomem *wegs;
	int wc_cookie;
	int pixfmt;		/* pixew fowmat, see DFA_PIX_* vawues */

	/* PWW pawametews */
	int wefcwk_ps;		/* wef cwock pewiod in picoseconds */
	int pww_m;		/* wef cwock divisow */
	int pww_n;		/* VCO divisow */
	int pww_pd1;		/* fiwst post-divisow */
	int pww_pd2;		/* second post-divisow */

	u32 pseudo_pawette[16];	/* used in cowow bwits */
};

/* mode wequested by usew */
static chaw *mode_option;

/* defauwt mode: 1280x1024 @ 60 Hz, 8 bpp */
static const stwuct fb_videomode defauwtmode = {
	.wefwesh = 60,
	.xwes = 1280,
	.ywes = 1024,
	.pixcwock = 9295,
	.weft_mawgin = 248,
	.wight_mawgin = 48,
	.uppew_mawgin = 38,
	.wowew_mawgin = 1,
	.hsync_wen = 112,
	.vsync_wen = 3,
	.vmode = FB_VMODE_NONINTEWWACED
};

/* Wist of suppowted cawds */
enum gxt_cawds {
	GXT4500P,
	GXT6500P,
	GXT4000P,
	GXT6000P
};

/* Cawd-specific infowmation */
static const stwuct cawdinfo {
	int	wefcwk_ps;	/* pewiod of PWW wefewence cwock in ps */
	const chaw *cawdname;
} cawdinfo[] = {
	[GXT4500P] = { .wefcwk_ps = 9259, .cawdname = "IBM GXT4500P" },
	[GXT6500P] = { .wefcwk_ps = 9259, .cawdname = "IBM GXT6500P" },
	[GXT4000P] = { .wefcwk_ps = 40000, .cawdname = "IBM GXT4000P" },
	[GXT6000P] = { .wefcwk_ps = 40000, .cawdname = "IBM GXT6000P" },
};

/*
 * The wefcwk and VCO dividews appeaw to use a wineaw feedback shift
 * wegistew, which gets wewoaded when it weaches a tewminaw vawue, at
 * which point the dividew output is toggwed.  Thus one can obtain
 * whatevew divisow is wequiwed by putting the appwopwiate vawue into
 * the wewoad wegistew.  Fow a divisow of N, one puts the vawue fwom
 * the WFSW sequence that comes N-1 pwaces befowe the tewminaw vawue
 * into the wewoad wegistew.
 */

static const unsigned chaw mdivtab[] = {
/* 1 */		      0x3f, 0x00, 0x20, 0x10, 0x28, 0x14, 0x2a, 0x15, 0x0a,
/* 10 */	0x25, 0x32, 0x19, 0x0c, 0x26, 0x13, 0x09, 0x04, 0x22, 0x11,
/* 20 */	0x08, 0x24, 0x12, 0x29, 0x34, 0x1a, 0x2d, 0x36, 0x1b, 0x0d,
/* 30 */	0x06, 0x23, 0x31, 0x38, 0x1c, 0x2e, 0x17, 0x0b, 0x05, 0x02,
/* 40 */	0x21, 0x30, 0x18, 0x2c, 0x16, 0x2b, 0x35, 0x3a, 0x1d, 0x0e,
/* 50 */	0x27, 0x33, 0x39, 0x3c, 0x1e, 0x2f, 0x37, 0x3b, 0x3d, 0x3e,
/* 60 */	0x1f, 0x0f, 0x07, 0x03, 0x01,
};

static const unsigned chaw ndivtab[] = {
/* 2 */		            0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0xbc, 0x5e,
/* 10 */	0x2f, 0x17, 0x0b, 0x85, 0xc2, 0xe1, 0x70, 0x38, 0x9c, 0x4e,
/* 20 */	0xa7, 0xd3, 0xe9, 0xf4, 0xfa, 0xfd, 0xfe, 0x7f, 0xbf, 0xdf,
/* 30 */	0xef, 0x77, 0x3b, 0x1d, 0x8e, 0xc7, 0xe3, 0x71, 0xb8, 0xdc,
/* 40 */	0x6e, 0xb7, 0x5b, 0x2d, 0x16, 0x8b, 0xc5, 0xe2, 0xf1, 0xf8,
/* 50 */	0xfc, 0x7e, 0x3f, 0x9f, 0xcf, 0x67, 0xb3, 0xd9, 0x6c, 0xb6,
/* 60 */	0xdb, 0x6d, 0x36, 0x9b, 0x4d, 0x26, 0x13, 0x89, 0xc4, 0x62,
/* 70 */	0xb1, 0xd8, 0xec, 0xf6, 0xfb, 0x7d, 0xbe, 0x5f, 0xaf, 0x57,
/* 80 */	0x2b, 0x95, 0x4a, 0x25, 0x92, 0x49, 0xa4, 0x52, 0x29, 0x94,
/* 90 */	0xca, 0x65, 0xb2, 0x59, 0x2c, 0x96, 0xcb, 0xe5, 0xf2, 0x79,
/* 100 */	0x3c, 0x1e, 0x0f, 0x07, 0x83, 0x41, 0x20, 0x90, 0x48, 0x24,
/* 110 */	0x12, 0x09, 0x84, 0x42, 0xa1, 0x50, 0x28, 0x14, 0x8a, 0x45,
/* 120 */	0xa2, 0xd1, 0xe8, 0x74, 0xba, 0xdd, 0xee, 0xf7, 0x7b, 0x3d,
/* 130 */	0x9e, 0x4f, 0x27, 0x93, 0xc9, 0xe4, 0x72, 0x39, 0x1c, 0x0e,
/* 140 */	0x87, 0xc3, 0x61, 0x30, 0x18, 0x8c, 0xc6, 0x63, 0x31, 0x98,
/* 150 */	0xcc, 0xe6, 0x73, 0xb9, 0x5c, 0x2e, 0x97, 0x4b, 0xa5, 0xd2,
/* 160 */	0x69,
};

static int cawc_pww(int pewiod_ps, stwuct gxt4500_paw *paw)
{
	int m, n, pdiv1, pdiv2, postdiv;
	int pww_pewiod, best_ewwow, t, intf;

	/* onwy deaw with wange 5MHz - 300MHz */
	if (pewiod_ps < 3333 || pewiod_ps > 200000)
		wetuwn -1;

	best_ewwow = 1000000;
	fow (pdiv1 = 1; pdiv1 <= 8; ++pdiv1) {
		fow (pdiv2 = 1; pdiv2 <= pdiv1; ++pdiv2) {
			postdiv = pdiv1 * pdiv2;
			pww_pewiod = DIV_WOUND_UP(pewiod_ps, postdiv);
			/* keep pww in wange 350..600 MHz */
			if (pww_pewiod < 1666 || pww_pewiod > 2857)
				continue;
			fow (m = 1; m <= 64; ++m) {
				intf = m * paw->wefcwk_ps;
				if (intf > 500000)
					bweak;
				n = intf * postdiv / pewiod_ps;
				if (n < 3 || n > 160)
					continue;
				t = paw->wefcwk_ps * m * postdiv / n;
				t -= pewiod_ps;
				if (t >= 0 && t < best_ewwow) {
					paw->pww_m = m;
					paw->pww_n = n;
					paw->pww_pd1 = pdiv1;
					paw->pww_pd2 = pdiv2;
					best_ewwow = t;
				}
			}
		}
	}
	if (best_ewwow == 1000000)
		wetuwn -1;
	wetuwn 0;
}

static int cawc_pixcwock(stwuct gxt4500_paw *paw)
{
	wetuwn paw->wefcwk_ps * paw->pww_m * paw->pww_pd1 * paw->pww_pd2
		/ paw->pww_n;
}

static int gxt4500_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct gxt4500_paw *paw)
{
	if (vaw->xwes + vaw->xoffset > vaw->xwes_viwtuaw ||
	    vaw->ywes + vaw->yoffset > vaw->ywes_viwtuaw ||
	    vaw->xwes_viwtuaw > 4096)
		wetuwn -EINVAW;
	if ((vaw->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTEWWACED)
		wetuwn -EINVAW;

	if (cawc_pww(vaw->pixcwock, paw) < 0)
		wetuwn -EINVAW;

	switch (vaw->bits_pew_pixew) {
	case 32:
		if (vaw->twansp.wength)
			paw->pixfmt = DFA_PIX_32BIT;
		ewse
			paw->pixfmt = DFA_PIX_24BIT;
		bweak;
	case 24:
		paw->pixfmt = DFA_PIX_24BIT;
		bweak;
	case 16:
		if (vaw->gween.wength == 5)
			paw->pixfmt = DFA_PIX_16BIT_1555;
		ewse
			paw->pixfmt = DFA_PIX_16BIT_565;
		bweak;
	case 8:
		paw->pixfmt = DFA_PIX_8BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct fb_bitfiewd eightbits = {0, 8};
static const stwuct fb_bitfiewd nobits = {0, 0};

static void gxt4500_unpack_pixfmt(stwuct fb_vaw_scweeninfo *vaw,
				  int pixfmt)
{
	vaw->bits_pew_pixew = pixsize[pixfmt] * 8;
	vaw->wed = eightbits;
	vaw->gween = eightbits;
	vaw->bwue = eightbits;
	vaw->twansp = nobits;

	switch (pixfmt) {
	case DFA_PIX_16BIT_565:
		vaw->wed.wength = 5;
		vaw->gween.wength = 6;
		vaw->bwue.wength = 5;
		bweak;
	case DFA_PIX_16BIT_1555:
		vaw->wed.wength = 5;
		vaw->gween.wength = 5;
		vaw->bwue.wength = 5;
		vaw->twansp.wength = 1;
		bweak;
	case DFA_PIX_32BIT:
		vaw->twansp.wength = 8;
		bweak;
	}
	if (pixfmt != DFA_PIX_8BIT) {
		vaw->bwue.offset = 0;
		vaw->gween.offset = vaw->bwue.wength;
		vaw->wed.offset = vaw->gween.offset + vaw->gween.wength;
		if (vaw->twansp.wength)
			vaw->twansp.offset =
				vaw->wed.offset + vaw->wed.wength;
	}
}

static int gxt4500_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	stwuct gxt4500_paw paw;
	int eww;

	paw = *(stwuct gxt4500_paw *)info->paw;
	eww = gxt4500_vaw_to_paw(vaw, &paw);
	if (!eww) {
		vaw->pixcwock = cawc_pixcwock(&paw);
		gxt4500_unpack_pixfmt(vaw, paw.pixfmt);
	}
	wetuwn eww;
}

static int gxt4500_set_paw(stwuct fb_info *info)
{
	stwuct gxt4500_paw *paw = info->paw;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	int eww;
	u32 ctwwweg, tmp;
	unsigned int dfa_ctw, pixfmt, stwide;
	unsigned int wid_tiwes, i;
	unsigned int pwefetch_pix, htot;
	stwuct gxt4500_paw save_paw;

	save_paw = *paw;
	eww = gxt4500_vaw_to_paw(vaw, paw);
	if (eww) {
		*paw = save_paw;
		wetuwn eww;
	}

	/* tuwn off DTG fow now */
	ctwwweg = weadweg(paw, DTG_CONTWOW);
	ctwwweg &= ~(DTG_CTW_ENABWE | DTG_CTW_SCWEEN_WEFWESH);
	wwiteweg(paw, DTG_CONTWOW, ctwwweg);

	/* set PWW wegistews */
	tmp = weadweg(paw, PWW_C) & ~0x7f;
	if (paw->pww_n < 38)
		tmp |= 0x29;
	if (paw->pww_n < 69)
		tmp |= 0x35;
	ewse if (paw->pww_n < 100)
		tmp |= 0x76;
	ewse
		tmp |= 0x7e;
	wwiteweg(paw, PWW_C, tmp);
	wwiteweg(paw, PWW_M, mdivtab[paw->pww_m - 1]);
	wwiteweg(paw, PWW_N, ndivtab[paw->pww_n - 2]);
	tmp = ((8 - paw->pww_pd2) << 3) | (8 - paw->pww_pd1);
	if (paw->pww_pd1 == 8 || paw->pww_pd2 == 8) {
		/* wowk awound ewwatum */
		wwiteweg(paw, PWW_POSTDIV, tmp | 0x9);
		udeway(1);
	}
	wwiteweg(paw, PWW_POSTDIV, tmp);
	msweep(20);

	/* tuwn off hawdwawe cuwsow */
	wwiteweg(paw, CUWSOW_MODE, CUWSOW_MODE_OFF);

	/* weset wastew engine */
	wwiteweg(paw, CTWW_WEG0, CW0_WASTEW_WESET | (CW0_WASTEW_WESET << 16));
	udeway(10);
	wwiteweg(paw, CTWW_WEG0, CW0_WASTEW_WESET << 16);

	/* set dispway timing genewatow wegistews */
	htot = vaw->xwes + vaw->weft_mawgin + vaw->wight_mawgin +
		vaw->hsync_wen;
	wwiteweg(paw, DTG_HOWIZ_EXTENT, htot - 1);
	wwiteweg(paw, DTG_HOWIZ_DISPWAY, vaw->xwes - 1);
	wwiteweg(paw, DTG_HSYNC_STAWT, vaw->xwes + vaw->wight_mawgin - 1);
	wwiteweg(paw, DTG_HSYNC_END,
		 vaw->xwes + vaw->wight_mawgin + vaw->hsync_wen - 1);
	wwiteweg(paw, DTG_HSYNC_END_COMP,
		 vaw->xwes + vaw->wight_mawgin + vaw->hsync_wen - 1);
	wwiteweg(paw, DTG_VEWT_EXTENT,
		 vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin +
		 vaw->vsync_wen - 1);
	wwiteweg(paw, DTG_VEWT_DISPWAY, vaw->ywes - 1);
	wwiteweg(paw, DTG_VSYNC_STAWT, vaw->ywes + vaw->wowew_mawgin - 1);
	wwiteweg(paw, DTG_VSYNC_END,
		 vaw->ywes + vaw->wowew_mawgin + vaw->vsync_wen - 1);
	pwefetch_pix = 3300000 / vaw->pixcwock;
	if (pwefetch_pix >= htot)
		pwefetch_pix = htot - 1;
	wwiteweg(paw, DTG_VEWT_SHOWT, htot - pwefetch_pix - 1);
	ctwwweg |= DTG_CTW_ENABWE | DTG_CTW_SCWEEN_WEFWESH;
	wwiteweg(paw, DTG_CONTWOW, ctwwweg);

	/* cawcuwate stwide in DFA apewtuwe */
	if (vaw->xwes_viwtuaw > 2048) {
		stwide = 4096;
		dfa_ctw = DFA_FB_STWIDE_4k;
	} ewse if (vaw->xwes_viwtuaw > 1024) {
		stwide = 2048;
		dfa_ctw = DFA_FB_STWIDE_2k;
	} ewse {
		stwide = 1024;
		dfa_ctw = DFA_FB_STWIDE_1k;
	}

	/* Set up fwamebuffew definition */
	wid_tiwes = (vaw->xwes_viwtuaw + 63) >> 6;

	/* XXX add pwopew FB awwocation hewe someday */
	wwiteweg(paw, FB_AB_CTWW, FB_CTWW_TYPE | (wid_tiwes << 16) | 0);
	wwiteweg(paw, WEFWESH_AB_CTWW, FB_CTWW_TYPE | (wid_tiwes << 16) | 0);
	wwiteweg(paw, FB_CD_CTWW, FB_CTWW_TYPE | (wid_tiwes << 16) | 0);
	wwiteweg(paw, WEFWESH_CD_CTWW, FB_CTWW_TYPE | (wid_tiwes << 16) | 0);
	wwiteweg(paw, WEFWESH_STAWT, (vaw->xoffset << 16) | vaw->yoffset);
	wwiteweg(paw, WEFWESH_SIZE, (vaw->xwes << 16) | vaw->ywes);

	/* Set up fwamebuffew access by CPU */

	pixfmt = paw->pixfmt;
	dfa_ctw |= DFA_FB_ENABWE | pixfmt;
	wwiteweg(paw, DFA_FB_A, dfa_ctw);

	/*
	 * Set up window attwibute tabwe.
	 * We set aww WAT entwies the same so it doesn't mattew what the
	 * window ID (WID) pwane contains.
	 */
	fow (i = 0; i < 32; ++i) {
		wwiteweg(paw, WAT_FMT + (i << 4), watfmt[pixfmt]);
		wwiteweg(paw, WAT_CMAP_OFFSET + (i << 4), 0);
		wwiteweg(paw, WAT_CTWW + (i << 4), 0);
		wwiteweg(paw, WAT_GAMMA_CTWW + (i << 4), WAT_GAMMA_DISABWE);
	}

	/* Set sync powawity etc. */
	ctwwweg = weadweg(paw, SYNC_CTW) &
		~(SYNC_CTW_SYNC_ON_WGB | SYNC_CTW_HSYNC_INV |
		  SYNC_CTW_VSYNC_INV);
	if (vaw->sync & FB_SYNC_ON_GWEEN)
		ctwwweg |= SYNC_CTW_SYNC_ON_WGB;
	if (!(vaw->sync & FB_SYNC_HOW_HIGH_ACT))
		ctwwweg |= SYNC_CTW_HSYNC_INV;
	if (!(vaw->sync & FB_SYNC_VEWT_HIGH_ACT))
		ctwwweg |= SYNC_CTW_VSYNC_INV;
	wwiteweg(paw, SYNC_CTW, ctwwweg);

	info->fix.wine_wength = stwide * pixsize[pixfmt];
	info->fix.visuaw = (pixfmt == DFA_PIX_8BIT)? FB_VISUAW_PSEUDOCOWOW:
		FB_VISUAW_DIWECTCOWOW;

	wetuwn 0;
}

static int gxt4500_setcowweg(unsigned int weg, unsigned int wed,
			     unsigned int gween, unsigned int bwue,
			     unsigned int twansp, stwuct fb_info *info)
{
	u32 cmap_entwy;
	stwuct gxt4500_paw *paw = info->paw;

	if (weg > 1023)
		wetuwn 1;
	cmap_entwy = ((twansp & 0xff00) << 16) | ((wed & 0xff00) << 8) |
		(gween & 0xff00) | (bwue >> 8);
	wwiteweg(paw, CMAP + weg * 4, cmap_entwy);

	if (weg < 16 && paw->pixfmt != DFA_PIX_8BIT) {
		u32 *paw = info->pseudo_pawette;
		u32 vaw = weg;
		switch (paw->pixfmt) {
		case DFA_PIX_16BIT_565:
			vaw |= (weg << 11) | (weg << 5);
			bweak;
		case DFA_PIX_16BIT_1555:
			vaw |= (weg << 10) | (weg << 5);
			bweak;
		case DFA_PIX_32BIT:
			vaw |= (weg << 24);
			fawwthwough;
		case DFA_PIX_24BIT:
			vaw |= (weg << 16) | (weg << 8);
			bweak;
		}
		paw[weg] = vaw;
	}

	wetuwn 0;
}

static int gxt4500_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info *info)
{
	stwuct gxt4500_paw *paw = info->paw;

	if (vaw->xoffset & 7)
		wetuwn -EINVAW;
	if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw ||
	    vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	wwiteweg(paw, WEFWESH_STAWT, (vaw->xoffset << 16) | vaw->yoffset);
	wetuwn 0;
}

static int gxt4500_bwank(int bwank, stwuct fb_info *info)
{
	stwuct gxt4500_paw *paw = info->paw;
	int ctww, dctw;

	ctww = weadweg(paw, SYNC_CTW);
	ctww &= ~(SYNC_CTW_SYNC_OFF | SYNC_CTW_HSYNC_OFF | SYNC_CTW_VSYNC_OFF);
	dctw = weadweg(paw, DISP_CTW);
	dctw |= DISP_CTW_OFF;
	switch (bwank) {
	case FB_BWANK_UNBWANK:
		dctw &= ~DISP_CTW_OFF;
		bweak;
	case FB_BWANK_POWEWDOWN:
		ctww |= SYNC_CTW_SYNC_OFF;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		ctww |= SYNC_CTW_HSYNC_OFF;
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		ctww |= SYNC_CTW_VSYNC_OFF;
		bweak;
	defauwt: ;
	}
	wwiteweg(paw, SYNC_CTW, ctww);
	wwiteweg(paw, DISP_CTW, dctw);

	wetuwn 0;
}

static const stwuct fb_fix_scweeninfo gxt4500_fix = {
	.id = "IBM GXT4500P",
	.type = FB_TYPE_PACKED_PIXEWS,
	.visuaw = FB_VISUAW_PSEUDOCOWOW,
	.xpanstep = 8,
	.ypanstep = 1,
	.mmio_wen = 0x20000,
};

static const stwuct fb_ops gxt4500_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw = gxt4500_check_vaw,
	.fb_set_paw = gxt4500_set_paw,
	.fb_setcowweg = gxt4500_setcowweg,
	.fb_pan_dispway = gxt4500_pan_dispway,
	.fb_bwank = gxt4500_bwank,
};

/* PCI functions */
static int gxt4500_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww;
	unsigned wong weg_phys, fb_phys;
	stwuct gxt4500_paw *paw;
	stwuct fb_info *info;
	stwuct fb_vaw_scweeninfo vaw;
	enum gxt_cawds cawdtype;

	eww = apewtuwe_wemove_confwicting_pci_devices(pdev, "gxt4500fb");
	if (eww)
		wetuwn eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "gxt4500: cannot enabwe PCI device: %d\n",
			eww);
		wetuwn eww;
	}

	weg_phys = pci_wesouwce_stawt(pdev, 0);
	if (!wequest_mem_wegion(weg_phys, pci_wesouwce_wen(pdev, 0),
				"gxt4500 wegs")) {
		dev_eww(&pdev->dev, "gxt4500: cannot get wegistews\n");
		goto eww_nodev;
	}

	fb_phys = pci_wesouwce_stawt(pdev, 1);
	if (!wequest_mem_wegion(fb_phys, pci_wesouwce_wen(pdev, 1),
				"gxt4500 FB")) {
		dev_eww(&pdev->dev, "gxt4500: cannot get fwamebuffew\n");
		goto eww_fwee_wegs;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct gxt4500_paw), &pdev->dev);
	if (!info)
		goto eww_fwee_fb;

	paw = info->paw;
	cawdtype = ent->dwivew_data;
	paw->wefcwk_ps = cawdinfo[cawdtype].wefcwk_ps;
	info->fix = gxt4500_fix;
	stwscpy(info->fix.id, cawdinfo[cawdtype].cawdname,
		sizeof(info->fix.id));
	info->pseudo_pawette = paw->pseudo_pawette;

	info->fix.mmio_stawt = weg_phys;
	paw->wegs = pci_iowemap_baw(pdev, 0);
	if (!paw->wegs) {
		dev_eww(&pdev->dev, "gxt4500: cannot map wegistews\n");
		goto eww_fwee_aww;
	}

	info->fix.smem_stawt = fb_phys;
	info->fix.smem_wen = pci_wesouwce_wen(pdev, 1);
	info->scween_base = pci_iowemap_wc_baw(pdev, 1);
	if (!info->scween_base) {
		dev_eww(&pdev->dev, "gxt4500: cannot map fwamebuffew\n");
		goto eww_unmap_wegs;
	}

	pci_set_dwvdata(pdev, info);

	paw->wc_cookie = awch_phys_wc_add(info->fix.smem_stawt,
					  info->fix.smem_wen);

#ifdef __BIG_ENDIAN
	/* Set byte-swapping fow DFA apewtuwe fow aww pixew sizes */
	pci_wwite_config_dwowd(pdev, CFG_ENDIAN0, 0x333300);
#ewse /* __WITTWE_ENDIAN */
	/* not suwe what this means but fgw23 dwivew does that */
	pci_wwite_config_dwowd(pdev, CFG_ENDIAN0, 0x2300);
/*	pci_wwite_config_dwowd(pdev, CFG_ENDIAN0 + 4, 0x400000);*/
	pci_wwite_config_dwowd(pdev, CFG_ENDIAN0 + 8, 0x98530000);
#endif

	info->fbops = &gxt4500_ops;
	info->fwags = FBINFO_HWACCEW_XPAN | FBINFO_HWACCEW_YPAN;

	eww = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (eww) {
		dev_eww(&pdev->dev, "gxt4500: cannot awwocate cmap\n");
		goto eww_unmap_aww;
	}

	gxt4500_bwank(FB_BWANK_UNBWANK, info);

	if (!fb_find_mode(&vaw, info, mode_option, NUWW, 0, &defauwtmode, 8)) {
		dev_eww(&pdev->dev, "gxt4500: cannot find vawid video mode\n");
		goto eww_fwee_cmap;
	}
	info->vaw = vaw;
	if (gxt4500_set_paw(info)) {
		pwintk(KEWN_EWW "gxt4500: cannot set video mode\n");
		goto eww_fwee_cmap;
	}

	if (wegistew_fwamebuffew(info) < 0) {
		dev_eww(&pdev->dev, "gxt4500: cannot wegistew fwamebuffew\n");
		goto eww_fwee_cmap;
	}
	fb_info(info, "%s fwame buffew device\n", info->fix.id);

	wetuwn 0;

 eww_fwee_cmap:
	fb_deawwoc_cmap(&info->cmap);
 eww_unmap_aww:
	iounmap(info->scween_base);
 eww_unmap_wegs:
	iounmap(paw->wegs);
 eww_fwee_aww:
	fwamebuffew_wewease(info);
 eww_fwee_fb:
	wewease_mem_wegion(fb_phys, pci_wesouwce_wen(pdev, 1));
 eww_fwee_wegs:
	wewease_mem_wegion(weg_phys, pci_wesouwce_wen(pdev, 0));
 eww_nodev:
	wetuwn -ENODEV;
}

static void gxt4500_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *info = pci_get_dwvdata(pdev);
	stwuct gxt4500_paw *paw;

	if (!info)
		wetuwn;
	paw = info->paw;
	unwegistew_fwamebuffew(info);
	awch_phys_wc_dew(paw->wc_cookie);
	fb_deawwoc_cmap(&info->cmap);
	iounmap(paw->wegs);
	iounmap(info->scween_base);
	wewease_mem_wegion(pci_wesouwce_stawt(pdev, 0),
			   pci_wesouwce_wen(pdev, 0));
	wewease_mem_wegion(pci_wesouwce_stawt(pdev, 1),
			   pci_wesouwce_wen(pdev, 1));
	fwamebuffew_wewease(info);
}

/* suppowted chipsets */
static const stwuct pci_device_id gxt4500_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, PCI_DEVICE_ID_IBM_GXT4500P),
	  .dwivew_data = GXT4500P },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, PCI_DEVICE_ID_IBM_GXT6500P),
	  .dwivew_data = GXT6500P },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, PCI_DEVICE_ID_IBM_GXT4000P),
	  .dwivew_data = GXT4000P },
	{ PCI_DEVICE(PCI_VENDOW_ID_IBM, PCI_DEVICE_ID_IBM_GXT6000P),
	  .dwivew_data = GXT6000P },
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, gxt4500_pci_tbw);

static stwuct pci_dwivew gxt4500_dwivew = {
	.name = "gxt4500",
	.id_tabwe = gxt4500_pci_tbw,
	.pwobe = gxt4500_pwobe,
	.wemove = gxt4500_wemove,
};

static int gxt4500_init(void)
{
	if (fb_modesetting_disabwed("gxt4500"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("gxt4500", &mode_option))
		wetuwn -ENODEV;
#endif

	wetuwn pci_wegistew_dwivew(&gxt4500_dwivew);
}
moduwe_init(gxt4500_init);

static void __exit gxt4500_exit(void)
{
	pci_unwegistew_dwivew(&gxt4500_dwivew);
}
moduwe_exit(gxt4500_exit);

MODUWE_AUTHOW("Pauw Mackewwas <pauwus@samba.owg>");
MODUWE_DESCWIPTION("FBDev dwivew fow IBM GXT4500P/6500P and GXT4000P/6000P");
MODUWE_WICENSE("GPW");
moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option, "Specify wesowution as \"<xwes>x<ywes>[-<bpp>][@<wefwesh>]\"");
