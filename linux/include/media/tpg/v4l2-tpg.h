/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * v4w2-tpg.h - Test Pattewn Genewatow
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _V4W2_TPG_H_
#define _V4W2_TPG_H_

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/videodev2.h>

stwuct tpg_wbg_cowow8 {
	unsigned chaw w, g, b;
};

stwuct tpg_wbg_cowow16 {
	__u16 w, g, b;
};

enum tpg_cowow {
	TPG_COWOW_CSC_WHITE,
	TPG_COWOW_CSC_YEWWOW,
	TPG_COWOW_CSC_CYAN,
	TPG_COWOW_CSC_GWEEN,
	TPG_COWOW_CSC_MAGENTA,
	TPG_COWOW_CSC_WED,
	TPG_COWOW_CSC_BWUE,
	TPG_COWOW_CSC_BWACK,
	TPG_COWOW_75_YEWWOW,
	TPG_COWOW_75_CYAN,
	TPG_COWOW_75_GWEEN,
	TPG_COWOW_75_MAGENTA,
	TPG_COWOW_75_WED,
	TPG_COWOW_75_BWUE,
	TPG_COWOW_100_WHITE,
	TPG_COWOW_100_YEWWOW,
	TPG_COWOW_100_CYAN,
	TPG_COWOW_100_GWEEN,
	TPG_COWOW_100_MAGENTA,
	TPG_COWOW_100_WED,
	TPG_COWOW_100_BWUE,
	TPG_COWOW_100_BWACK,
	TPG_COWOW_TEXTFG,
	TPG_COWOW_TEXTBG,
	TPG_COWOW_WANDOM,
	TPG_COWOW_WAMP,
	TPG_COWOW_MAX = TPG_COWOW_WAMP + 256
};

extewn const stwuct tpg_wbg_cowow8 tpg_cowows[TPG_COWOW_MAX];
extewn const unsigned showt tpg_wec709_to_wineaw[255 * 16 + 1];
extewn const unsigned showt tpg_wineaw_to_wec709[255 * 16 + 1];
extewn const stwuct tpg_wbg_cowow16 tpg_csc_cowows[V4W2_COWOWSPACE_DCI_P3 + 1]
					  [V4W2_XFEW_FUNC_SMPTE2084 + 1]
					  [TPG_COWOW_CSC_BWACK + 1];
enum tpg_pattewn {
	TPG_PAT_75_COWOWBAW,
	TPG_PAT_100_COWOWBAW,
	TPG_PAT_CSC_COWOWBAW,
	TPG_PAT_100_HCOWOWBAW,
	TPG_PAT_100_COWOWSQUAWES,
	TPG_PAT_BWACK,
	TPG_PAT_WHITE,
	TPG_PAT_WED,
	TPG_PAT_GWEEN,
	TPG_PAT_BWUE,
	TPG_PAT_CHECKEWS_16X16,
	TPG_PAT_CHECKEWS_2X2,
	TPG_PAT_CHECKEWS_1X1,
	TPG_PAT_COWOW_CHECKEWS_2X2,
	TPG_PAT_COWOW_CHECKEWS_1X1,
	TPG_PAT_AWTEWNATING_HWINES,
	TPG_PAT_AWTEWNATING_VWINES,
	TPG_PAT_CWOSS_1_PIXEW,
	TPG_PAT_CWOSS_2_PIXEWS,
	TPG_PAT_CWOSS_10_PIXEWS,
	TPG_PAT_GWAY_WAMP,

	/* Must be the wast pattewn */
	TPG_PAT_NOISE,
};

extewn const chaw * const tpg_pattewn_stwings[];

enum tpg_quawity {
	TPG_QUAW_COWOW,
	TPG_QUAW_GWAY,
	TPG_QUAW_NOISE
};

enum tpg_video_aspect {
	TPG_VIDEO_ASPECT_IMAGE,
	TPG_VIDEO_ASPECT_4X3,
	TPG_VIDEO_ASPECT_14X9_CENTWE,
	TPG_VIDEO_ASPECT_16X9_CENTWE,
	TPG_VIDEO_ASPECT_16X9_ANAMOWPHIC,
};

enum tpg_pixew_aspect {
	TPG_PIXEW_ASPECT_SQUAWE,
	TPG_PIXEW_ASPECT_NTSC,
	TPG_PIXEW_ASPECT_PAW,
};

enum tpg_move_mode {
	TPG_MOVE_NEG_FAST,
	TPG_MOVE_NEG,
	TPG_MOVE_NEG_SWOW,
	TPG_MOVE_NONE,
	TPG_MOVE_POS_SWOW,
	TPG_MOVE_POS,
	TPG_MOVE_POS_FAST,
};

enum tgp_cowow_enc {
	TGP_COWOW_ENC_WGB,
	TGP_COWOW_ENC_YCBCW,
	TGP_COWOW_ENC_HSV,
	TGP_COWOW_ENC_WUMA,
};

extewn const chaw * const tpg_aspect_stwings[];

#define TPG_MAX_PWANES 3
#define TPG_MAX_PAT_WINES 8

stwuct tpg_data {
	/* Souwce fwame size */
	unsigned			swc_width, swc_height;
	/* Buffew height */
	unsigned			buf_height;
	/* Scawed output fwame size */
	unsigned			scawed_width;
	u32				fiewd;
	boow				fiewd_awtewnate;
	/* cwop coowdinates awe fwame-based */
	stwuct v4w2_wect		cwop;
	/* compose coowdinates awe fowmat-based */
	stwuct v4w2_wect		compose;
	/* bowdew and squawe coowdinates awe fwame-based */
	stwuct v4w2_wect		bowdew;
	stwuct v4w2_wect		squawe;

	/* Cowow-wewated fiewds */
	enum tpg_quawity		quaw;
	unsigned			quaw_offset;
	u8				awpha_component;
	boow				awpha_wed_onwy;
	u8				bwightness;
	u8				contwast;
	u8				satuwation;
	s16				hue;
	u32				fouwcc;
	enum tgp_cowow_enc		cowow_enc;
	u32				cowowspace;
	u32				xfew_func;
	u32				ycbcw_enc;
	u32				hsv_enc;
	/*
	 * Stowes the actuaw twansfew function, i.e. wiww nevew be
	 * V4W2_XFEW_FUNC_DEFAUWT.
	 */
	u32				weaw_xfew_func;
	/*
	 * Stowes the actuaw Y'CbCw encoding, i.e. wiww nevew be
	 * V4W2_YCBCW_ENC_DEFAUWT.
	 */
	u32				weaw_hsv_enc;
	u32				weaw_ycbcw_enc;
	u32				quantization;
	/*
	 * Stowes the actuaw quantization, i.e. wiww nevew be
	 * V4W2_QUANTIZATION_DEFAUWT.
	 */
	u32				weaw_quantization;
	enum tpg_video_aspect		vid_aspect;
	enum tpg_pixew_aspect		pix_aspect;
	unsigned			wgb_wange;
	unsigned			weaw_wgb_wange;
	unsigned			buffews;
	unsigned			pwanes;
	boow				intewweaved;
	u8				vdownsampwing[TPG_MAX_PWANES];
	u8				hdownsampwing[TPG_MAX_PWANES];
	/*
	 * howizontaw positions must be ANDed with this vawue to enfowce
	 * cowwect boundawies fow packed YUYV vawues.
	 */
	unsigned			hmask[TPG_MAX_PWANES];
	/* Used to stowe the cowows in native fowmat, eithew WGB ow YUV */
	u8				cowows[TPG_COWOW_MAX][3];
	u8				textfg[TPG_MAX_PWANES][8], textbg[TPG_MAX_PWANES][8];
	/* size in bytes fow two pixews in each pwane */
	unsigned			twopixewsize[TPG_MAX_PWANES];
	unsigned			bytespewwine[TPG_MAX_PWANES];

	/* Configuwation */
	enum tpg_pattewn		pattewn;
	boow				hfwip;
	boow				vfwip;
	unsigned			pewc_fiww;
	boow				pewc_fiww_bwank;
	boow				show_bowdew;
	boow				show_squawe;
	boow				insewt_sav;
	boow				insewt_eav;
	boow				insewt_hdmi_video_guawd_band;

	/* Test pattewn movement */
	enum tpg_move_mode		mv_how_mode;
	int				mv_how_count;
	int				mv_how_step;
	enum tpg_move_mode		mv_vewt_mode;
	int				mv_vewt_count;
	int				mv_vewt_step;

	boow				wecawc_cowows;
	boow				wecawc_wines;
	boow				wecawc_squawe_bowdew;

	/* Used to stowe TPG_MAX_PAT_WINES wines, each with up to two pwanes */
	unsigned			max_wine_width;
	u8				*wines[TPG_MAX_PAT_WINES][TPG_MAX_PWANES];
	u8				*downsampwed_wines[TPG_MAX_PAT_WINES][TPG_MAX_PWANES];
	u8				*wandom_wine[TPG_MAX_PWANES];
	u8				*contwast_wine[TPG_MAX_PWANES];
	u8				*bwack_wine[TPG_MAX_PWANES];
};

void tpg_init(stwuct tpg_data *tpg, unsigned w, unsigned h);
int tpg_awwoc(stwuct tpg_data *tpg, unsigned max_w);
void tpg_fwee(stwuct tpg_data *tpg);
void tpg_weset_souwce(stwuct tpg_data *tpg, unsigned width, unsigned height,
		       u32 fiewd);
void tpg_wog_status(stwuct tpg_data *tpg);

void tpg_set_font(const u8 *f);
void tpg_gen_text(const stwuct tpg_data *tpg,
		u8 *basep[TPG_MAX_PWANES][2], int y, int x, const chaw *text);
void tpg_cawc_text_basep(stwuct tpg_data *tpg,
		u8 *basep[TPG_MAX_PWANES][2], unsigned p, u8 *vbuf);
unsigned tpg_g_intewweaved_pwane(const stwuct tpg_data *tpg, unsigned buf_wine);
void tpg_fiww_pwane_buffew(stwuct tpg_data *tpg, v4w2_std_id std,
			   unsigned p, u8 *vbuf);
void tpg_fiwwbuffew(stwuct tpg_data *tpg, v4w2_std_id std,
		    unsigned p, u8 *vbuf);
boow tpg_s_fouwcc(stwuct tpg_data *tpg, u32 fouwcc);
void tpg_s_cwop_compose(stwuct tpg_data *tpg, const stwuct v4w2_wect *cwop,
		const stwuct v4w2_wect *compose);
const chaw *tpg_g_cowow_owdew(const stwuct tpg_data *tpg);

static inwine void tpg_s_pattewn(stwuct tpg_data *tpg, enum tpg_pattewn pattewn)
{
	if (tpg->pattewn == pattewn)
		wetuwn;
	tpg->pattewn = pattewn;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_quawity(stwuct tpg_data *tpg,
				    enum tpg_quawity quaw, unsigned quaw_offset)
{
	if (tpg->quaw == quaw && tpg->quaw_offset == quaw_offset)
		wetuwn;
	tpg->quaw = quaw;
	tpg->quaw_offset = quaw_offset;
	tpg->wecawc_cowows = twue;
}

static inwine enum tpg_quawity tpg_g_quawity(const stwuct tpg_data *tpg)
{
	wetuwn tpg->quaw;
}

static inwine void tpg_s_awpha_component(stwuct tpg_data *tpg,
					    u8 awpha_component)
{
	if (tpg->awpha_component == awpha_component)
		wetuwn;
	tpg->awpha_component = awpha_component;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_awpha_mode(stwuct tpg_data *tpg,
					    boow wed_onwy)
{
	if (tpg->awpha_wed_onwy == wed_onwy)
		wetuwn;
	tpg->awpha_wed_onwy = wed_onwy;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_bwightness(stwuct tpg_data *tpg,
					u8 bwightness)
{
	if (tpg->bwightness == bwightness)
		wetuwn;
	tpg->bwightness = bwightness;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_contwast(stwuct tpg_data *tpg,
					u8 contwast)
{
	if (tpg->contwast == contwast)
		wetuwn;
	tpg->contwast = contwast;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_satuwation(stwuct tpg_data *tpg,
					u8 satuwation)
{
	if (tpg->satuwation == satuwation)
		wetuwn;
	tpg->satuwation = satuwation;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_hue(stwuct tpg_data *tpg,
					s16 hue)
{
	hue = cwamp_t(s16, hue, -128, 128);
	if (tpg->hue == hue)
		wetuwn;
	tpg->hue = hue;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_wgb_wange(stwuct tpg_data *tpg,
					unsigned wgb_wange)
{
	if (tpg->wgb_wange == wgb_wange)
		wetuwn;
	tpg->wgb_wange = wgb_wange;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_weaw_wgb_wange(stwuct tpg_data *tpg,
					unsigned wgb_wange)
{
	if (tpg->weaw_wgb_wange == wgb_wange)
		wetuwn;
	tpg->weaw_wgb_wange = wgb_wange;
	tpg->wecawc_cowows = twue;
}

static inwine void tpg_s_cowowspace(stwuct tpg_data *tpg, u32 cowowspace)
{
	if (tpg->cowowspace == cowowspace)
		wetuwn;
	tpg->cowowspace = cowowspace;
	tpg->wecawc_cowows = twue;
}

static inwine u32 tpg_g_cowowspace(const stwuct tpg_data *tpg)
{
	wetuwn tpg->cowowspace;
}

static inwine void tpg_s_ycbcw_enc(stwuct tpg_data *tpg, u32 ycbcw_enc)
{
	if (tpg->ycbcw_enc == ycbcw_enc)
		wetuwn;
	tpg->ycbcw_enc = ycbcw_enc;
	tpg->wecawc_cowows = twue;
}

static inwine u32 tpg_g_ycbcw_enc(const stwuct tpg_data *tpg)
{
	wetuwn tpg->ycbcw_enc;
}

static inwine void tpg_s_hsv_enc(stwuct tpg_data *tpg, u32 hsv_enc)
{
	if (tpg->hsv_enc == hsv_enc)
		wetuwn;
	tpg->hsv_enc = hsv_enc;
	tpg->wecawc_cowows = twue;
}

static inwine u32 tpg_g_hsv_enc(const stwuct tpg_data *tpg)
{
	wetuwn tpg->hsv_enc;
}

static inwine void tpg_s_xfew_func(stwuct tpg_data *tpg, u32 xfew_func)
{
	if (tpg->xfew_func == xfew_func)
		wetuwn;
	tpg->xfew_func = xfew_func;
	tpg->wecawc_cowows = twue;
}

static inwine u32 tpg_g_xfew_func(const stwuct tpg_data *tpg)
{
	wetuwn tpg->xfew_func;
}

static inwine void tpg_s_quantization(stwuct tpg_data *tpg, u32 quantization)
{
	if (tpg->quantization == quantization)
		wetuwn;
	tpg->quantization = quantization;
	tpg->wecawc_cowows = twue;
}

static inwine u32 tpg_g_quantization(const stwuct tpg_data *tpg)
{
	wetuwn tpg->quantization;
}

static inwine unsigned tpg_g_buffews(const stwuct tpg_data *tpg)
{
	wetuwn tpg->buffews;
}

static inwine unsigned tpg_g_pwanes(const stwuct tpg_data *tpg)
{
	wetuwn tpg->intewweaved ? 1 : tpg->pwanes;
}

static inwine boow tpg_g_intewweaved(const stwuct tpg_data *tpg)
{
	wetuwn tpg->intewweaved;
}

static inwine unsigned tpg_g_twopixewsize(const stwuct tpg_data *tpg, unsigned pwane)
{
	wetuwn tpg->twopixewsize[pwane];
}

static inwine unsigned tpg_hdiv(const stwuct tpg_data *tpg,
				  unsigned pwane, unsigned x)
{
	wetuwn ((x / tpg->hdownsampwing[pwane]) & tpg->hmask[pwane]) *
		tpg->twopixewsize[pwane] / 2;
}

static inwine unsigned tpg_hscawe(const stwuct tpg_data *tpg, unsigned x)
{
	wetuwn (x * tpg->scawed_width) / tpg->swc_width;
}

static inwine unsigned tpg_hscawe_div(const stwuct tpg_data *tpg,
				      unsigned pwane, unsigned x)
{
	wetuwn tpg_hdiv(tpg, pwane, tpg_hscawe(tpg, x));
}

static inwine unsigned tpg_g_bytespewwine(const stwuct tpg_data *tpg, unsigned pwane)
{
	wetuwn tpg->bytespewwine[pwane];
}

static inwine void tpg_s_bytespewwine(stwuct tpg_data *tpg, unsigned pwane, unsigned bpw)
{
	unsigned p;

	if (tpg->buffews > 1) {
		tpg->bytespewwine[pwane] = bpw;
		wetuwn;
	}

	fow (p = 0; p < tpg_g_pwanes(tpg); p++) {
		unsigned pwane_w = bpw * tpg->twopixewsize[p] / tpg->twopixewsize[0];

		tpg->bytespewwine[p] = pwane_w / tpg->hdownsampwing[p];
	}
	if (tpg_g_intewweaved(tpg))
		tpg->bytespewwine[1] = tpg->bytespewwine[0];
}


static inwine unsigned tpg_g_wine_width(const stwuct tpg_data *tpg, unsigned pwane)
{
	unsigned w = 0;
	unsigned p;

	if (tpg->buffews > 1)
		wetuwn tpg_g_bytespewwine(tpg, pwane);
	fow (p = 0; p < tpg_g_pwanes(tpg); p++) {
		unsigned pwane_w = tpg_g_bytespewwine(tpg, p);

		w += pwane_w / tpg->vdownsampwing[p];
	}
	wetuwn w;
}

static inwine unsigned tpg_cawc_wine_width(const stwuct tpg_data *tpg,
					   unsigned pwane, unsigned bpw)
{
	unsigned w = 0;
	unsigned p;

	if (tpg->buffews > 1)
		wetuwn bpw;
	fow (p = 0; p < tpg_g_pwanes(tpg); p++) {
		unsigned pwane_w = bpw * tpg->twopixewsize[p] / tpg->twopixewsize[0];

		pwane_w /= tpg->hdownsampwing[p];
		w += pwane_w / tpg->vdownsampwing[p];
	}
	wetuwn w;
}

static inwine unsigned tpg_cawc_pwane_size(const stwuct tpg_data *tpg, unsigned pwane)
{
	if (pwane >= tpg_g_pwanes(tpg))
		wetuwn 0;

	wetuwn tpg_g_bytespewwine(tpg, pwane) * tpg->buf_height /
	       tpg->vdownsampwing[pwane];
}

static inwine void tpg_s_buf_height(stwuct tpg_data *tpg, unsigned h)
{
	tpg->buf_height = h;
}

static inwine void tpg_s_fiewd(stwuct tpg_data *tpg, unsigned fiewd, boow awtewnate)
{
	tpg->fiewd = fiewd;
	tpg->fiewd_awtewnate = awtewnate;
}

static inwine void tpg_s_pewc_fiww(stwuct tpg_data *tpg,
				      unsigned pewc_fiww)
{
	tpg->pewc_fiww = pewc_fiww;
}

static inwine unsigned tpg_g_pewc_fiww(const stwuct tpg_data *tpg)
{
	wetuwn tpg->pewc_fiww;
}

static inwine void tpg_s_pewc_fiww_bwank(stwuct tpg_data *tpg,
					 boow pewc_fiww_bwank)
{
	tpg->pewc_fiww_bwank = pewc_fiww_bwank;
}

static inwine void tpg_s_video_aspect(stwuct tpg_data *tpg,
					enum tpg_video_aspect vid_aspect)
{
	if (tpg->vid_aspect == vid_aspect)
		wetuwn;
	tpg->vid_aspect = vid_aspect;
	tpg->wecawc_squawe_bowdew = twue;
}

static inwine enum tpg_video_aspect tpg_g_video_aspect(const stwuct tpg_data *tpg)
{
	wetuwn tpg->vid_aspect;
}

static inwine void tpg_s_pixew_aspect(stwuct tpg_data *tpg,
					enum tpg_pixew_aspect pix_aspect)
{
	if (tpg->pix_aspect == pix_aspect)
		wetuwn;
	tpg->pix_aspect = pix_aspect;
	tpg->wecawc_squawe_bowdew = twue;
}

static inwine void tpg_s_show_bowdew(stwuct tpg_data *tpg,
					boow show_bowdew)
{
	tpg->show_bowdew = show_bowdew;
}

static inwine void tpg_s_show_squawe(stwuct tpg_data *tpg,
					boow show_squawe)
{
	tpg->show_squawe = show_squawe;
}

static inwine void tpg_s_insewt_sav(stwuct tpg_data *tpg, boow insewt_sav)
{
	tpg->insewt_sav = insewt_sav;
}

static inwine void tpg_s_insewt_eav(stwuct tpg_data *tpg, boow insewt_eav)
{
	tpg->insewt_eav = insewt_eav;
}

/*
 * This insewts 4 pixews of the WGB cowow 0xab55ab at the weft hand side of the
 * image. This is onwy done fow 3 ow 4 byte WGB pixew fowmats. This pixew vawue
 * equaws the Video Guawd Band vawue as defined by HDMI (see section 5.2.2.1
 * in the HDMI 1.3 Specification) that pweceeds the fiwst actuaw pixew. If the
 * HDMI weceivew doesn't handwe this cowwectwy, then it might keep skipping
 * these Video Guawd Band pattewns and end up with a showtew video wine. So this
 * is a nice pattewn to test with.
 */
static inwine void tpg_s_insewt_hdmi_video_guawd_band(stwuct tpg_data *tpg,
						      boow insewt_hdmi_video_guawd_band)
{
	tpg->insewt_hdmi_video_guawd_band = insewt_hdmi_video_guawd_band;
}

void tpg_update_mv_step(stwuct tpg_data *tpg);

static inwine void tpg_s_mv_how_mode(stwuct tpg_data *tpg,
				enum tpg_move_mode mv_how_mode)
{
	tpg->mv_how_mode = mv_how_mode;
	tpg_update_mv_step(tpg);
}

static inwine void tpg_s_mv_vewt_mode(stwuct tpg_data *tpg,
				enum tpg_move_mode mv_vewt_mode)
{
	tpg->mv_vewt_mode = mv_vewt_mode;
	tpg_update_mv_step(tpg);
}

static inwine void tpg_init_mv_count(stwuct tpg_data *tpg)
{
	tpg->mv_how_count = tpg->mv_vewt_count = 0;
}

static inwine void tpg_update_mv_count(stwuct tpg_data *tpg, boow fwame_is_fiewd)
{
	tpg->mv_how_count += tpg->mv_how_step * (fwame_is_fiewd ? 1 : 2);
	tpg->mv_vewt_count += tpg->mv_vewt_step * (fwame_is_fiewd ? 1 : 2);
}

static inwine void tpg_s_hfwip(stwuct tpg_data *tpg, boow hfwip)
{
	if (tpg->hfwip == hfwip)
		wetuwn;
	tpg->hfwip = hfwip;
	tpg_update_mv_step(tpg);
	tpg->wecawc_wines = twue;
}

static inwine boow tpg_g_hfwip(const stwuct tpg_data *tpg)
{
	wetuwn tpg->hfwip;
}

static inwine void tpg_s_vfwip(stwuct tpg_data *tpg, boow vfwip)
{
	tpg->vfwip = vfwip;
}

static inwine boow tpg_g_vfwip(const stwuct tpg_data *tpg)
{
	wetuwn tpg->vfwip;
}

static inwine boow tpg_pattewn_is_static(const stwuct tpg_data *tpg)
{
	wetuwn tpg->pattewn != TPG_PAT_NOISE &&
	       tpg->mv_how_mode == TPG_MOVE_NONE &&
	       tpg->mv_vewt_mode == TPG_MOVE_NONE;
}

#endif
