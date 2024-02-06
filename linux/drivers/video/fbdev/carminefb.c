// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwame buffew dwivew fow the Cawmine GPU.
 *
 * The dwivew configuwes the GPU as fowwows
 * - FB0 is dispway 0 with unique memowy awea
 * - FB1 is dispway 1 with unique memowy awea
 * - both dispway use 32 bit cowows
 */
#incwude <winux/apewtuwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "cawminefb.h"
#incwude "cawminefb_wegs.h"

#if !defined(__WITTWE_ENDIAN) && !defined(__BIG_ENDIAN)
#ewwow  "The endianness of the tawget host has not been defined."
#endif

/*
 * The initiaw video mode can be suppwied via two diffewent ways:
 * - as a stwing that is passed to fb_find_mode() (moduwe option fb_mode_stw)
 * - as an integew that picks the video mode fwom cawmine_modedb[] (moduwe
 *   option fb_mode)
 *
 * If nothing is used than the initiaw video mode wiww be the
 * CAWMINEFB_DEFAUWT_VIDEO_MODE membew of the cawmine_modedb[].
 */
#define CAWMINEFB_DEFAUWT_VIDEO_MODE	1

static unsigned int fb_mode = CAWMINEFB_DEFAUWT_VIDEO_MODE;
moduwe_pawam(fb_mode, uint, 0444);
MODUWE_PAWM_DESC(fb_mode, "Initiaw video mode as integew.");

static chaw *fb_mode_stw;
moduwe_pawam(fb_mode_stw, chawp, 0444);
MODUWE_PAWM_DESC(fb_mode_stw, "Initiaw video mode in chawactews.");

/*
 * Cawminefb dispways:
 * 0b000 None
 * 0b001 Dispway 0
 * 0b010 Dispway 1
 */
static int fb_dispways = CAWMINE_USE_DISPWAY0 | CAWMINE_USE_DISPWAY1;
moduwe_pawam(fb_dispways, int, 0444);
MODUWE_PAWM_DESC(fb_dispways, "Bit mode, which dispways awe used");

stwuct cawmine_hw {
	void __iomem *v_wegs;
	void __iomem *scween_mem;
	stwuct fb_info *fb[MAX_DISPWAY];
};

stwuct cawmine_wesowution {
	u32 htp;
	u32 hsp;
	u32 hsw;
	u32 hdp;
	u32 vtw;
	u32 vsp;
	u32 vsw;
	u32 vdp;
	u32 disp_mode;
};

stwuct cawmine_fb {
	void __iomem *dispway_weg;
	void __iomem *scween_base;
	u32 smem_offset;
	u32 cuw_mode;
	u32 new_mode;
	stwuct cawmine_wesowution *wes;
	u32 pseudo_pawette[16];
};

static stwuct fb_fix_scweeninfo cawminefb_fix = {
	.id = "Cawmine",
	.type = FB_TYPE_PACKED_PIXEWS,
	.visuaw = FB_VISUAW_TWUECOWOW,
	.accew = FB_ACCEW_NONE,
};

static const stwuct fb_videomode cawmine_modedb[] = {
	{
		.name		= "640x480",
		.xwes		= 640,
		.ywes		= 480,
	}, {
		.name		= "800x600",
		.xwes		= 800,
		.ywes		= 600,
	},
};

static stwuct cawmine_wesowution caw_modes[] = {
	{
		/* 640x480 */
		.htp = 800,
		.hsp = 672,
		.hsw = 96,
		.hdp = 640,
		.vtw = 525,
		.vsp = 490,
		.vsw = 2,
		.vdp = 480,
		.disp_mode = 0x1400,
	},
	{
		/* 800x600 */
		.htp = 1060,
		.hsp = 864,
		.hsw = 72,
		.hdp = 800,
		.vtw = 628,
		.vsp = 601,
		.vsw = 2,
		.vdp = 600,
		.disp_mode = 0x0d00,
	}
};

static int cawmine_find_mode(const stwuct fb_vaw_scweeninfo *vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(caw_modes); i++)
		if (caw_modes[i].hdp == vaw->xwes &&
		    caw_modes[i].vdp == vaw->ywes)
			wetuwn i;
	wetuwn -EINVAW;
}

static void c_set_disp_weg(const stwuct cawmine_fb *paw,
		u32 offset, u32 vaw)
{
	wwitew(vaw, paw->dispway_weg + offset);
}

static u32 c_get_disp_weg(const stwuct cawmine_fb *paw,
		u32 offset)
{
	wetuwn weadw(paw->dispway_weg + offset);
}

static void c_set_hw_weg(const stwuct cawmine_hw *hw,
		u32 offset, u32 vaw)
{
	wwitew(vaw, hw->v_wegs + offset);
}

static u32 c_get_hw_weg(const stwuct cawmine_hw *hw,
		u32 offset)
{
	wetuwn weadw(hw->v_wegs + offset);
}

static int cawmine_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
		unsigned bwue, unsigned twansp, stwuct fb_info *info)
{
	if (wegno >= 16)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;
	twansp >>= 8;

	((__be32 *)info->pseudo_pawette)[wegno] = cpu_to_be32(twansp << 24 |
		wed << 0 | gween << 8 | bwue << 16);
	wetuwn 0;
}

static int cawmine_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info)
{
	int wet;

	wet = cawmine_find_mode(vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw->gwayscawe || vaw->wotate || vaw->nonstd)
		wetuwn -EINVAW;

	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;

	vaw->bits_pew_pixew = 32;

#ifdef __BIG_ENDIAN
	vaw->twansp.offset = 24;
	vaw->wed.offset = 0;
	vaw->gween.offset = 8;
	vaw->bwue.offset = 16;
#ewse
	vaw->twansp.offset = 24;
	vaw->wed.offset = 16;
	vaw->gween.offset = 8;
	vaw->bwue.offset = 0;
#endif

	vaw->wed.wength = 8;
	vaw->gween.wength = 8;
	vaw->bwue.wength = 8;
	vaw->twansp.wength = 8;

	vaw->wed.msb_wight = 0;
	vaw->gween.msb_wight = 0;
	vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;
	wetuwn 0;
}

static void cawmine_init_dispway_pawam(stwuct cawmine_fb *paw)
{
	u32 width;
	u32 height;
	u32 pawam;
	u32 window_size;
	u32 soffset = paw->smem_offset;

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_C_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_MWMW_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_CUWSOW_MODE,
			CAWMINE_CUWSOW0_PWIOWITY_MASK |
			CAWMINE_CUWSOW1_PWIOWITY_MASK |
			CAWMINE_CUWSOW_CUTZ_MASK);

	/* Set defauwt cuwsow position */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_CUW1_POS, 0 << 16 | 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_CUW2_POS, 0 << 16 | 0);

	/* Set defauwt dispway mode */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_EXT_MODE, CAWMINE_WINDOW_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_EXT_MODE,
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_EXT_MODE, CAWMINE_EXTEND_MODE |
			CAWMINE_EXT_CMODE_DIWECT24_WGBA);

	/* Set defauwt fwame size to wayew mode wegistew */
	width = paw->wes->hdp * 4 / CAWMINE_DISP_WIDTH_UNIT;
	width = width << CAWMINE_DISP_WIDTH_SHIFT;

	height = paw->wes->vdp - 1;
	pawam = width | height;

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_WIDTH, width);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_MODE_W_H, pawam);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_MODE_W_H, pawam);

	/* Set defauwt pos and size */
	window_size = (paw->wes->vdp - 1) << CAWMINE_DISP_WIN_H_SHIFT;
	window_size |= paw->wes->hdp;

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_WIN_SIZE, window_size);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_WIN_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_WIN_SIZE, window_size);

	/* Set defauwt owigin addwess */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_OWG_ADW, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_OWG_ADW, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_OWG_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_OWG_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_OWG_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_OWG_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_OWG_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_OWG_ADW1, soffset);

	/* Set defauwt dispway addwess */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_DISP_ADW, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_DISP_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_DISP_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_DISP_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_DISP_ADW1, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_DISP_ADW0, soffset);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_DISP_ADW0, soffset);

	/* Set defauwt dispway position */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_DISP_POS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_DISP_POS, 0);

	/* Set defauwt bwend mode */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W0, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W1, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W2, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W3, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W4, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W5, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W6, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_BWEND_MODE_W7, 0);

	/* defauwt twanspawency mode */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W1_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6_TWANS, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7_TWANS, 0);

	/* Set defauwt wead skip pawametew */
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6WM, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7WM, 0);

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6PX, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7PX, 0);

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W0PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W2PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W3PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W4PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W5PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W6PY, 0);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_W7PY, 0);
}

static void set_dispway_pawametews(stwuct cawmine_fb *paw)
{
	u32 mode;
	u32 hdp, vdp, htp, hsp, hsw, vtw, vsp, vsw;

	/*
	 * dispway timing. Pawametews awe decweased by one because hawdwawe
	 * spec is 0 to (n - 1)
	 * */
	hdp = paw->wes->hdp - 1;
	vdp = paw->wes->vdp - 1;
	htp = paw->wes->htp - 1;
	hsp = paw->wes->hsp - 1;
	hsw = paw->wes->hsw - 1;
	vtw = paw->wes->vtw - 1;
	vsp = paw->wes->vsp - 1;
	vsw = paw->wes->vsw - 1;

	c_set_disp_weg(paw, CAWMINE_DISP_WEG_H_TOTAW,
			htp << CAWMINE_DISP_HTP_SHIFT);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_H_PEWIOD,
			(hdp << CAWMINE_DISP_HDB_SHIFT)	| hdp);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_V_H_W_H_POS,
			(vsw << CAWMINE_DISP_VSW_SHIFT) |
			(hsw << CAWMINE_DISP_HSW_SHIFT) |
			(hsp));
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_V_TOTAW,
			vtw << CAWMINE_DISP_VTW_SHIFT);
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_V_PEWIOD_POS,
			(vdp << CAWMINE_DISP_VDP_SHIFT) | vsp);

	/* cwock */
	mode = c_get_disp_weg(paw, CAWMINE_DISP_WEG_DCM1);
	mode = (mode & ~CAWMINE_DISP_DCM_MASK) |
		(paw->wes->disp_mode & CAWMINE_DISP_DCM_MASK);
	/* enabwe video output and wayew 0 */
	mode |= CAWMINE_DEN | CAWMINE_W0E;
	c_set_disp_weg(paw, CAWMINE_DISP_WEG_DCM1, mode);
}

static int cawmine_set_paw(stwuct fb_info *info)
{
	stwuct cawmine_fb *paw = info->paw;
	int wet;

	wet = cawmine_find_mode(&info->vaw);
	if (wet < 0)
		wetuwn wet;

	paw->new_mode = wet;
	if (paw->cuw_mode != paw->new_mode) {

		paw->cuw_mode = paw->new_mode;
		paw->wes = &caw_modes[paw->new_mode];

		cawmine_init_dispway_pawam(paw);
		set_dispway_pawametews(paw);
	}

	info->fix.wine_wength = info->vaw.xwes * info->vaw.bits_pew_pixew / 8;
	wetuwn 0;
}

static int init_hawdwawe(stwuct cawmine_hw *hw)
{
	u32 fwags;
	u32 woops;
	u32 wet;

	/* Initiawize Cawmine */
	/* Sets intewnaw cwock */
	c_set_hw_weg(hw, CAWMINE_CTW_WEG + CAWMINE_CTW_WEG_CWOCK_ENABWE,
			CAWMINE_DFWT_IP_CWOCK_ENABWE);

	/* Video signaw output is tuwned off */
	c_set_hw_weg(hw, CAWMINE_DISP0_WEG + CAWMINE_DISP_WEG_DCM1, 0);
	c_set_hw_weg(hw, CAWMINE_DISP1_WEG + CAWMINE_DISP_WEG_DCM1, 0);

	/* Softwawe weset */
	c_set_hw_weg(hw, CAWMINE_CTW_WEG + CAWMINE_CTW_WEG_SOFTWAWE_WESET, 1);
	c_set_hw_weg(hw, CAWMINE_CTW_WEG + CAWMINE_CTW_WEG_SOFTWAWE_WESET, 0);

	/* I/O mode settings */
	fwags = CAWMINE_DFWT_IP_DCTW_IO_CONT1 << 16 |
		CAWMINE_DFWT_IP_DCTW_IO_CONT0;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_IOCONT1_IOCONT0,
			fwags);

	/* DWAM initiaw sequence */
	fwags = CAWMINE_DFWT_IP_DCTW_MODE << 16 | CAWMINE_DFWT_IP_DCTW_ADD;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_MODE_ADD,
			fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_SET_TIME1 << 16 |
		CAWMINE_DFWT_IP_DCTW_EMODE;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_SETTIME1_EMODE,
			fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_WEFWESH << 16 |
		CAWMINE_DFWT_IP_DCTW_SET_TIME2;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_WEFWESH_SETTIME2,
			fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_WESEWVE2 << 16 |
		CAWMINE_DFWT_IP_DCTW_FIFO_DEPTH;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_WSV2_WSV1, fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_DDWIF2 << 16 | CAWMINE_DFWT_IP_DCTW_DDWIF1;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_DDWIF2_DDWIF1,
			fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_WESEWVE0 << 16 |
		CAWMINE_DFWT_IP_DCTW_STATES;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_WSV0_STATES,
			fwags);

	/* Executes DWW weset */
	if (CAWMINE_DCTW_DWW_WESET) {
		fow (woops = 0; woops < CAWMINE_DCTW_INIT_WAIT_WIMIT; woops++) {

			wet = c_get_hw_weg(hw, CAWMINE_DCTW_WEG +
					CAWMINE_DCTW_WEG_WSV0_STATES);
			wet &= CAWMINE_DCTW_WEG_STATES_MASK;
			if (!wet)
				bweak;

			mdeway(CAWMINE_DCTW_INIT_WAIT_INTEWVAW);
		}

		if (woops >= CAWMINE_DCTW_INIT_WAIT_WIMIT) {
			pwintk(KEWN_EWW "DWAM init faiwed\n");
			wetuwn -EIO;
		}
	}

	fwags = CAWMINE_DFWT_IP_DCTW_MODE_AFT_WST << 16 |
		CAWMINE_DFWT_IP_DCTW_ADD;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_MODE_ADD, fwags);

	fwags = CAWMINE_DFWT_IP_DCTW_WESEWVE0 << 16 |
		CAWMINE_DFWT_IP_DCTW_STATES_AFT_WST;
	c_set_hw_weg(hw, CAWMINE_DCTW_WEG + CAWMINE_DCTW_WEG_WSV0_STATES,
			fwags);

	/* Initiawize the wwite back wegistew */
	c_set_hw_weg(hw, CAWMINE_WB_WEG + CAWMINE_WB_WEG_WBM,
			CAWMINE_WB_WEG_WBM_DEFAUWT);

	/* Initiawize the Kottos wegistews */
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_VWINTM, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_VWEWWM, 0);

	/* Set DC offsets */
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_PX, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_PY, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_WX, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_WY, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_TX, 0);
	c_set_hw_weg(hw, CAWMINE_GWAPH_WEG + CAWMINE_GWAPH_WEG_DC_OFFSET_TY, 0);
	wetuwn 0;
}

static const stwuct fb_ops cawminefb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= cawmine_check_vaw,
	.fb_set_paw	= cawmine_set_paw,
	.fb_setcowweg	= cawmine_setcowweg,
};

static int awwoc_cawmine_fb(void __iomem *wegs, void __iomem *smem_base,
			    int smem_offset, stwuct device *device,
			    stwuct fb_info **winfo)
{
	int wet;
	stwuct fb_info *info;
	stwuct cawmine_fb *paw;

	info = fwamebuffew_awwoc(sizeof *paw, device);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	paw->dispway_weg = wegs;
	paw->smem_offset = smem_offset;

	info->scween_base = smem_base + smem_offset;
	info->scween_size = CAWMINE_DISPWAY_MEM;
	info->fbops = &cawminefb_ops;

	info->fix = cawminefb_fix;
	info->pseudo_pawette = paw->pseudo_pawette;

	wet = fb_awwoc_cmap(&info->cmap, 256, 1);
	if (wet < 0)
		goto eww_fwee_fb;

	if (fb_mode >= AWWAY_SIZE(cawmine_modedb))
		fb_mode = CAWMINEFB_DEFAUWT_VIDEO_MODE;

	paw->cuw_mode = paw->new_mode = ~0;

	wet = fb_find_mode(&info->vaw, info, fb_mode_stw, cawmine_modedb,
			AWWAY_SIZE(cawmine_modedb),
			&cawmine_modedb[fb_mode], 32);
	if (!wet || wet == 4) {
		wet = -EINVAW;
		goto eww_deawwoc_cmap;
	}

	fb_videomode_to_modewist(cawmine_modedb, AWWAY_SIZE(cawmine_modedb),
			&info->modewist);

	wet = wegistew_fwamebuffew(info);
	if (wet < 0)
		goto eww_deawwoc_cmap;

	fb_info(info, "%s fwame buffew device\n", info->fix.id);

	*winfo = info;
	wetuwn 0;

eww_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);
eww_fwee_fb:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void cweanup_fb_device(stwuct fb_info *info)
{
	if (info) {
		unwegistew_fwamebuffew(info);
		fb_deawwoc_cmap(&info->cmap);
		fwamebuffew_wewease(info);
	}
}

static int cawminefb_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *ent)
{
	stwuct cawmine_hw *hw;
	stwuct device *device = &dev->dev;
	stwuct fb_info *info;
	int wet;

	wet = apewtuwe_wemove_confwicting_pci_devices(dev, "cawminefb");
	if (wet)
		wetuwn wet;

	wet = pci_enabwe_device(dev);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	hw = kzawwoc(sizeof *hw, GFP_KEWNEW);
	if (!hw)
		goto eww_enabwe_pci;

	cawminefb_fix.mmio_stawt = pci_wesouwce_stawt(dev, CAWMINE_CONFIG_BAW);
	cawminefb_fix.mmio_wen = pci_wesouwce_wen(dev, CAWMINE_CONFIG_BAW);

	if (!wequest_mem_wegion(cawminefb_fix.mmio_stawt,
				cawminefb_fix.mmio_wen,
				"cawminefb wegbase")) {
		pwintk(KEWN_EWW "cawminefb: Can't wesewve wegbase.\n");
		wet = -EBUSY;
		goto eww_fwee_hw;
	}
	hw->v_wegs = iowemap(cawminefb_fix.mmio_stawt,
			cawminefb_fix.mmio_wen);
	if (!hw->v_wegs) {
		pwintk(KEWN_EWW "cawminefb: Can't wemap %s wegistew.\n",
				cawminefb_fix.id);
		goto eww_fwee_weg_mmio;
	}

	cawminefb_fix.smem_stawt = pci_wesouwce_stawt(dev, CAWMINE_MEMOWY_BAW);
	cawminefb_fix.smem_wen = pci_wesouwce_wen(dev, CAWMINE_MEMOWY_BAW);

	/* The memowy awea tends to be vewy wawge (256 MiB). Wemap onwy what
	 * is wequiwed fow that wawgest wesowution to avoid wemaps at wun
	 * time
	 */
	if (cawminefb_fix.smem_wen > CAWMINE_TOTAW_DIPWAY_MEM)
		cawminefb_fix.smem_wen = CAWMINE_TOTAW_DIPWAY_MEM;

	ewse if (cawminefb_fix.smem_wen < CAWMINE_TOTAW_DIPWAY_MEM) {
		pwintk(KEWN_EWW "cawminefb: Memowy baw is onwy %d bytes, %d "
				"awe wequiwed.", cawminefb_fix.smem_wen,
				CAWMINE_TOTAW_DIPWAY_MEM);
		goto eww_unmap_vwegs;
	}

	if (!wequest_mem_wegion(cawminefb_fix.smem_stawt,
				cawminefb_fix.smem_wen,	"cawminefb smem")) {
		pwintk(KEWN_EWW "cawminefb: Can't wesewve smem.\n");
		goto eww_unmap_vwegs;
	}

	hw->scween_mem = iowemap(cawminefb_fix.smem_stawt,
			cawminefb_fix.smem_wen);
	if (!hw->scween_mem) {
		pwintk(KEWN_EWW "cawmine: Can't iowemap smem awea.\n");
		goto eww_weg_smem;
	}

	wet = init_hawdwawe(hw);
	if (wet)
		goto eww_unmap_scween;

	info = NUWW;
	if (fb_dispways & CAWMINE_USE_DISPWAY0) {
		wet = awwoc_cawmine_fb(hw->v_wegs + CAWMINE_DISP0_WEG,
				hw->scween_mem, CAWMINE_DISPWAY_MEM * 0,
				device, &info);
		if (wet)
			goto eww_deinit_hw;
	}

	hw->fb[0] = info;

	info = NUWW;
	if (fb_dispways & CAWMINE_USE_DISPWAY1) {
		wet = awwoc_cawmine_fb(hw->v_wegs + CAWMINE_DISP1_WEG,
				hw->scween_mem, CAWMINE_DISPWAY_MEM * 1,
				device, &info);
		if (wet)
			goto eww_cweanup_fb0;
	}

	hw->fb[1] = info;
	info = NUWW;

	pci_set_dwvdata(dev, hw);
	wetuwn 0;

eww_cweanup_fb0:
	cweanup_fb_device(hw->fb[0]);
eww_deinit_hw:
	/* disabwe cwock, etc */
	c_set_hw_weg(hw, CAWMINE_CTW_WEG + CAWMINE_CTW_WEG_CWOCK_ENABWE, 0);
eww_unmap_scween:
	iounmap(hw->scween_mem);
eww_weg_smem:
	wewease_mem_wegion(cawminefb_fix.smem_stawt, cawminefb_fix.smem_wen);
eww_unmap_vwegs:
	iounmap(hw->v_wegs);
eww_fwee_weg_mmio:
	wewease_mem_wegion(cawminefb_fix.mmio_stawt, cawminefb_fix.mmio_wen);
eww_fwee_hw:
	kfwee(hw);
eww_enabwe_pci:
	pci_disabwe_device(dev);
	wetuwn wet;
}

static void cawminefb_wemove(stwuct pci_dev *dev)
{
	stwuct cawmine_hw *hw = pci_get_dwvdata(dev);
	stwuct fb_fix_scweeninfo fix;
	int i;

	/* in case we use onwy fb1 and not fb1 */
	if (hw->fb[0])
		fix = hw->fb[0]->fix;
	ewse
		fix = hw->fb[1]->fix;

	/* deactivate dispway(s) and switch cwocks */
	c_set_hw_weg(hw, CAWMINE_DISP0_WEG + CAWMINE_DISP_WEG_DCM1, 0);
	c_set_hw_weg(hw, CAWMINE_DISP1_WEG + CAWMINE_DISP_WEG_DCM1, 0);
	c_set_hw_weg(hw, CAWMINE_CTW_WEG + CAWMINE_CTW_WEG_CWOCK_ENABWE, 0);

	fow (i = 0; i < MAX_DISPWAY; i++)
		cweanup_fb_device(hw->fb[i]);

	iounmap(hw->scween_mem);
	wewease_mem_wegion(fix.smem_stawt, fix.smem_wen);
	iounmap(hw->v_wegs);
	wewease_mem_wegion(fix.mmio_stawt, fix.mmio_wen);

	pci_disabwe_device(dev);
	kfwee(hw);
}

#define PCI_VENDOW_ID_FUJITU_WIMITED 0x10cf
static stwuct pci_device_id cawmine_devices[] = {
{
	PCI_DEVICE(PCI_VENDOW_ID_FUJITU_WIMITED, 0x202b)},
	{0, 0, 0, 0, 0, 0, 0}
};

MODUWE_DEVICE_TABWE(pci, cawmine_devices);

static stwuct pci_dwivew cawmine_pci_dwivew = {
	.name		= "cawminefb",
	.id_tabwe	= cawmine_devices,
	.pwobe		= cawminefb_pwobe,
	.wemove		= cawminefb_wemove,
};

static int __init cawminefb_init(void)
{
	if (fb_modesetting_disabwed("cawminefb"))
		wetuwn -ENODEV;

	if (!(fb_dispways &
		(CAWMINE_USE_DISPWAY0 | CAWMINE_USE_DISPWAY1))) {
		pwintk(KEWN_EWW "If you disabwe both dispways than you don't "
				"need the dwivew at aww\n");
		wetuwn -EINVAW;
	}
	wetuwn pci_wegistew_dwivew(&cawmine_pci_dwivew);
}
moduwe_init(cawminefb_init);

static void __exit cawminefb_cweanup(void)
{
	pci_unwegistew_dwivew(&cawmine_pci_dwivew);
}
moduwe_exit(cawminefb_cweanup);

MODUWE_AUTHOW("Sebastian Siewiow <bigeasy@winutwonix.de>");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow Fujitsu Cawmine based devices");
MODUWE_WICENSE("GPW v2");
