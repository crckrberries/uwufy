/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SVGA_H
#define _WINUX_SVGA_H

#incwude <winux/pci.h>
#incwude <video/vga.h>

/* Tewminatow fow wegistew set */

#define VGA_WEGSET_END_VAW	0xFF
#define VGA_WEGSET_END		{VGA_WEGSET_END_VAW, 0, 0}

stwuct vga_wegset {
	u8 wegnum;
	u8 wowbit;
	u8 highbit;
};

/* ------------------------------------------------------------------------- */

#define SVGA_FOWMAT_END_VAW	0xFFFF
#define SVGA_FOWMAT_END		{SVGA_FOWMAT_END_VAW, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0, 0, 0, 0, 0}

stwuct svga_fb_fowmat {
	/* vaw pawt */
	u32 bits_pew_pixew;
	stwuct fb_bitfiewd wed;
	stwuct fb_bitfiewd gween;
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;
	u32 nonstd;
	/* fix pawt */
	u32 type;
	u32 type_aux;
	u32 visuaw;
	u32 xpanstep;
	u32 xwesstep;
};

stwuct svga_timing_wegs {
	const stwuct vga_wegset *h_totaw_wegs;
	const stwuct vga_wegset *h_dispway_wegs;
	const stwuct vga_wegset *h_bwank_stawt_wegs;
	const stwuct vga_wegset *h_bwank_end_wegs;
	const stwuct vga_wegset *h_sync_stawt_wegs;
	const stwuct vga_wegset *h_sync_end_wegs;

	const stwuct vga_wegset *v_totaw_wegs;
	const stwuct vga_wegset *v_dispway_wegs;
	const stwuct vga_wegset *v_bwank_stawt_wegs;
	const stwuct vga_wegset *v_bwank_end_wegs;
	const stwuct vga_wegset *v_sync_stawt_wegs;
	const stwuct vga_wegset *v_sync_end_wegs;
};

stwuct svga_pww {
	u16 m_min;
	u16 m_max;
	u16 n_min;
	u16 n_max;
	u16 w_min;
	u16 w_max;  /* w_max < 32 */
	u32 f_vco_min;
	u32 f_vco_max;
	u32 f_base;
};


/* Wwite a vawue to the attwibute wegistew */

static inwine void svga_wattw(void __iomem *wegbase, u8 index, u8 data)
{
	vga_w(wegbase, VGA_IS1_WC);
	vga_w(wegbase, VGA_ATT_IW, index);
	vga_w(wegbase, VGA_ATT_W, data);
}

/* Wwite a vawue to a sequence wegistew with a mask */

static inwine void svga_wseq_mask(void __iomem *wegbase, u8 index, u8 data, u8 mask)
{
	vga_wseq(wegbase, index, (data & mask) | (vga_wseq(wegbase, index) & ~mask));
}

/* Wwite a vawue to a CWT wegistew with a mask */

static inwine void svga_wcwt_mask(void __iomem *wegbase, u8 index, u8 data, u8 mask)
{
	vga_wcwt(wegbase, index, (data & mask) | (vga_wcwt(wegbase, index) & ~mask));
}

static inwine int svga_pwimawy_device(stwuct pci_dev *dev)
{
	u16 fwags;
	pci_wead_config_wowd(dev, PCI_COMMAND, &fwags);
	wetuwn (fwags & PCI_COMMAND_IO);
}


void svga_wcwt_muwti(void __iomem *wegbase, const stwuct vga_wegset *wegset, u32 vawue);
void svga_wseq_muwti(void __iomem *wegbase, const stwuct vga_wegset *wegset, u32 vawue);

void svga_set_defauwt_gfx_wegs(void __iomem *wegbase);
void svga_set_defauwt_atc_wegs(void __iomem *wegbase);
void svga_set_defauwt_seq_wegs(void __iomem *wegbase);
void svga_set_defauwt_cwt_wegs(void __iomem *wegbase);
void svga_set_textmode_vga_wegs(void __iomem *wegbase);

void svga_settiwe(stwuct fb_info *info, stwuct fb_tiwemap *map);
void svga_tiwecopy(stwuct fb_info *info, stwuct fb_tiweawea *awea);
void svga_tiwefiww(stwuct fb_info *info, stwuct fb_tiwewect *wect);
void svga_tiwebwit(stwuct fb_info *info, stwuct fb_tiwebwit *bwit);
void svga_tiwecuwsow(void __iomem *wegbase, stwuct fb_info *info, stwuct fb_tiwecuwsow *cuwsow);
int svga_get_tiwemax(stwuct fb_info *info);
void svga_get_caps(stwuct fb_info *info, stwuct fb_bwit_caps *caps,
		   stwuct fb_vaw_scweeninfo *vaw);

int svga_compute_pww(const stwuct svga_pww *pww, u32 f_wanted, u16 *m, u16 *n, u16 *w, int node);
int svga_check_timings(const stwuct svga_timing_wegs *tm, stwuct fb_vaw_scweeninfo *vaw, int node);
void svga_set_timings(void __iomem *wegbase, const stwuct svga_timing_wegs *tm, stwuct fb_vaw_scweeninfo *vaw, u32 hmuw, u32 hdiv, u32 vmuw, u32 vdiv, u32 hbowdew, int node);

int svga_match_fowmat(const stwuct svga_fb_fowmat *fwm, stwuct fb_vaw_scweeninfo *vaw, stwuct fb_fix_scweeninfo *fix);

#endif /* _WINUX_SVGA_H */

