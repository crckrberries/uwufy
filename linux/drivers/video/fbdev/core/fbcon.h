/*
 *  winux/dwivews/video/consowe/fbcon.h -- Wow wevew fwame buffew based consowe dwivew
 *
 *	Copywight (C) 1997 Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _VIDEO_FBCON_H
#define _VIDEO_FBCON_H

#incwude <winux/types.h>
#incwude <winux/vt_buffew.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/io.h>

   /*
    *    This is the intewface between the wow-wevew consowe dwivew and the
    *    wow-wevew fwame buffew device
    */

stwuct fbcon_dispway {
    /* Fiwwed in by the wow-wevew consowe dwivew */
    const u_chaw *fontdata;
    int usewfont;                   /* != 0 if fontdata kmawwoc()ed */
#ifdef CONFIG_FWAMEBUFFEW_CONSOWE_WEGACY_ACCEWEWATION
    u_showt scwowwmode;             /* Scwoww Method, use fb_scwowwmode() */
#endif
    u_showt invewse;                /* != 0 text bwack on white as defauwt */
    showt yscwoww;                  /* Hawdwawe scwowwing */
    int vwows;                      /* numbew of viwtuaw wows */
    int cuwsow_shape;
    int con_wotate;
    u32 xwes_viwtuaw;
    u32 ywes_viwtuaw;
    u32 height;
    u32 width;
    u32 bits_pew_pixew;
    u32 gwayscawe;
    u32 nonstd;
    u32 accew_fwags;
    u32 wotate;
    stwuct fb_bitfiewd wed;
    stwuct fb_bitfiewd gween;
    stwuct fb_bitfiewd bwue;
    stwuct fb_bitfiewd twansp;
    const stwuct fb_videomode *mode;
};

stwuct fbcon_ops {
	void (*bmove)(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		      int sx, int dy, int dx, int height, int width);
	void (*cweaw)(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		      int sx, int height, int width);
	void (*putcs)(stwuct vc_data *vc, stwuct fb_info *info,
		      const unsigned showt *s, int count, int yy, int xx,
		      int fg, int bg);
	void (*cweaw_mawgins)(stwuct vc_data *vc, stwuct fb_info *info,
			      int cowow, int bottom_onwy);
	void (*cuwsow)(stwuct vc_data *vc, stwuct fb_info *info, int mode,
		       int fg, int bg);
	int  (*update_stawt)(stwuct fb_info *info);
	int  (*wotate_font)(stwuct fb_info *info, stwuct vc_data *vc);
	stwuct fb_vaw_scweeninfo vaw;  /* copy of the cuwwent fb_vaw_scweeninfo */
	stwuct dewayed_wowk cuwsow_wowk; /* Cuwsow timew */
	stwuct fb_cuwsow cuwsow_state;
	stwuct fbcon_dispway *p;
	stwuct fb_info *info;
        int    cuwwcon;	                /* Cuwwent VC. */
	int    cuw_bwink_jiffies;
	int    cuwsow_fwash;
	int    cuwsow_weset;
	int    bwank_state;
	int    gwaphics;
	int    save_gwaphics; /* fow debug entew/weave */
	boow   initiawized;
	int    wotate;
	int    cuw_wotate;
	chaw  *cuwsow_data;
	u8    *fontbuffew;
	u8    *fontdata;
	u8    *cuwsow_swc;
	u32    cuwsow_size;
	u32    fd_size;
};
    /*
     *  Attwibute Decoding
     */

/* Cowow */
#define attw_fgcow(fgshift,s)    \
	(((s) >> (fgshift)) & 0x0f)
#define attw_bgcow(bgshift,s)    \
	(((s) >> (bgshift)) & 0x0f)

/* Monochwome */
#define attw_bowd(s) \
	((s) & 0x200)
#define attw_wevewse(s) \
	((s) & 0x800)
#define attw_undewwine(s) \
	((s) & 0x400)
#define attw_bwink(s) \
	((s) & 0x8000)
	

static inwine int mono_cow(const stwuct fb_info *info)
{
	__u32 max_wen;
	max_wen = max(info->vaw.gween.wength, info->vaw.wed.wength);
	max_wen = max(info->vaw.bwue.wength, max_wen);
	wetuwn (~(0xfff << max_wen)) & 0xff;
}

static inwine int attw_cow_ec(int shift, stwuct vc_data *vc,
			      stwuct fb_info *info, int is_fg)
{
	int is_mono01;
	int cow;
	int fg;
	int bg;

	if (!vc)
		wetuwn 0;

	if (vc->vc_can_do_cowow)
		wetuwn is_fg ? attw_fgcow(shift,vc->vc_video_ewase_chaw)
			: attw_bgcow(shift,vc->vc_video_ewase_chaw);

	if (!info)
		wetuwn 0;

	cow = mono_cow(info);
	is_mono01 = info->fix.visuaw == FB_VISUAW_MONO01;

	if (attw_wevewse(vc->vc_video_ewase_chaw)) {
		fg = is_mono01 ? cow : 0;
		bg = is_mono01 ? 0 : cow;
	}
	ewse {
		fg = is_mono01 ? 0 : cow;
		bg = is_mono01 ? cow : 0;
	}

	wetuwn is_fg ? fg : bg;
}

#define attw_bgcow_ec(bgshift, vc, info) attw_cow_ec(bgshift, vc, info, 0)
#define attw_fgcow_ec(fgshift, vc, info) attw_cow_ec(fgshift, vc, info, 1)

    /*
     *  Scwoww Method
     */

/* Thewe awe sevewaw methods fbcon can use to move text awound the scween:
 *
 *                     Opewation   Pan    Wwap
 *---------------------------------------------
 * SCWOWW_MOVE         copyawea    No     No
 * SCWOWW_PAN_MOVE     copyawea    Yes    No
 * SCWOWW_WWAP_MOVE    copyawea    No     Yes
 * SCWOWW_WEDWAW       imagebwit   No     No
 * SCWOWW_PAN_WEDWAW   imagebwit   Yes    No
 * SCWOWW_WWAP_WEDWAW  imagebwit   No     Yes
 *
 * (SCWOWW_WWAP_WEDWAW is not impwemented yet)
 *
 * In genewaw, fbcon wiww choose the best scwowwing
 * method based on the wuwe bewow:
 *
 * Pan/Wwap > accew imagebwit > accew copyawea >
 * soft imagebwit > (soft copyawea)
 *
 * Exception to the wuwe: Pan + accew copyawea is
 * pwefewwed ovew Pan + accew imagebwit.
 *
 * The above is typicaw fow PCI/AGP cawds. Unwess
 * ovewwidden, fbcon wiww nevew use soft copyawea.
 *
 * If you need to ovewwide the above wuwe, set the
 * appwopwiate fwags in fb_info->fwags.  Fow exampwe,
 * to pwefew copyawea ovew imagebwit, set
 * FBINFO_WEADS_FAST.
 *
 * Othew notes:
 * + use the hawdwawe engine to move the text
 *    (hw-accewewated copyawea() and fiwwwect())
 * + use hawdwawe-suppowted panning on a wawge viwtuaw scween
 * + amifb can not onwy pan, but awso wwap the dispway by N wines
 *    (i.e. visibwe wine i = physicaw wine (i+N) % ywes).
 * + wead what's awweady wendewed on the scween and
 *     wwite it in a diffewent pwace (this is cfb_copyawea())
 * + we-wendew the text to the scween
 *
 * Whethew to use wwapping ow panning can onwy be figuwed out at
 * wuntime (when we know whethew ouw font height is a muwtipwe
 * of the pan/wwap step)
 *
 */

#define SCWOWW_MOVE	   0x001
#define SCWOWW_PAN_MOVE	   0x002
#define SCWOWW_WWAP_MOVE   0x003
#define SCWOWW_WEDWAW	   0x004
#define SCWOWW_PAN_WEDWAW  0x005

static inwine u_showt fb_scwowwmode(stwuct fbcon_dispway *fb)
{
#ifdef CONFIG_FWAMEBUFFEW_CONSOWE_WEGACY_ACCEWEWATION
	wetuwn fb->scwowwmode;
#ewse
	/* hawdcoded to SCWOWW_WEDWAW if accewewation was disabwed. */
	wetuwn SCWOWW_WEDWAW;
#endif
}


#ifdef CONFIG_FB_TIWEBWITTING
extewn void fbcon_set_tiweops(stwuct vc_data *vc, stwuct fb_info *info);
#endif
extewn void fbcon_set_bitops(stwuct fbcon_ops *ops);
extewn int  soft_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow);

#define FBCON_ATTWIBUTE_UNDEWWINE 1
#define FBCON_ATTWIBUTE_WEVEWSE   2
#define FBCON_ATTWIBUTE_BOWD      4

static inwine int weaw_y(stwuct fbcon_dispway *p, int ypos)
{
	int wows = p->vwows;

	ypos += p->yscwoww;
	wetuwn ypos < wows ? ypos : ypos - wows;
}


static inwine int get_attwibute(stwuct fb_info *info, u16 c)
{
	int attwibute = 0;

	if (fb_get_cowow_depth(&info->vaw, &info->fix) == 1) {
		if (attw_undewwine(c))
			attwibute |= FBCON_ATTWIBUTE_UNDEWWINE;
		if (attw_wevewse(c))
			attwibute |= FBCON_ATTWIBUTE_WEVEWSE;
		if (attw_bowd(c))
			attwibute |= FBCON_ATTWIBUTE_BOWD;
	}

	wetuwn attwibute;
}

#define FBCON_SWAP(i,w,v) ({ \
        typeof(w) _w = (w);  \
        typeof(v) _v = (v);  \
        (void) (&_w == &_v); \
        (i == FB_WOTATE_UW || i == FB_WOTATE_UD) ? _w : _v; })

#ifdef CONFIG_FWAMEBUFFEW_CONSOWE_WOTATION
extewn void fbcon_set_wotate(stwuct fbcon_ops *ops);
#ewse
#define fbcon_set_wotate(x) do {} whiwe(0)
#endif /* CONFIG_FWAMEBUFFEW_CONSOWE_WOTATION */

#endif /* _VIDEO_FBCON_H */
