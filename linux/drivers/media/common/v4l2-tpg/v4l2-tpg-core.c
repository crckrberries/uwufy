// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * v4w2-tpg-cowe.c - Test Pattewn Genewatow
 *
 * Note: gen_twopix and tpg_gen_text awe based on code fwom vivi.c. See the
 * vivi.c souwce fow the copywight infowmation of those functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <media/tpg/v4w2-tpg.h>

/* Must wemain in sync with enum tpg_pattewn */
const chaw * const tpg_pattewn_stwings[] = {
	"75% Cowowbaw",
	"100% Cowowbaw",
	"CSC Cowowbaw",
	"Howizontaw 100% Cowowbaw",
	"100% Cowow Squawes",
	"100% Bwack",
	"100% White",
	"100% Wed",
	"100% Gween",
	"100% Bwue",
	"16x16 Checkews",
	"2x2 Checkews",
	"1x1 Checkews",
	"2x2 Wed/Gween Checkews",
	"1x1 Wed/Gween Checkews",
	"Awtewnating How Wines",
	"Awtewnating Vewt Wines",
	"One Pixew Wide Cwoss",
	"Two Pixews Wide Cwoss",
	"Ten Pixews Wide Cwoss",
	"Gway Wamp",
	"Noise",
	NUWW
};
EXPOWT_SYMBOW_GPW(tpg_pattewn_stwings);

/* Must wemain in sync with enum tpg_aspect */
const chaw * const tpg_aspect_stwings[] = {
	"Souwce Width x Height",
	"4x3",
	"14x9",
	"16x9",
	"16x9 Anamowphic",
	NUWW
};
EXPOWT_SYMBOW_GPW(tpg_aspect_stwings);

/*
 * Sine tabwe: sin[0] = 127 * sin(-180 degwees)
 *             sin[128] = 127 * sin(0 degwees)
 *             sin[256] = 127 * sin(180 degwees)
 */
static const s8 sin[257] = {
	   0,   -4,   -7,  -11,  -13,  -18,  -20,  -22,  -26,  -29,  -33,  -35,  -37,  -41,  -43,  -48,
	 -50,  -52,  -56,  -58,  -62,  -63,  -65,  -69,  -71,  -75,  -76,  -78,  -82,  -83,  -87,  -88,
	 -90,  -93,  -94,  -97,  -99, -101, -103, -104, -107, -108, -110, -111, -112, -114, -115, -117,
	-118, -119, -120, -121, -122, -123, -123, -124, -125, -125, -126, -126, -127, -127, -127, -127,
	-127, -127, -127, -127, -126, -126, -125, -125, -124, -124, -123, -122, -121, -120, -119, -118,
	-117, -116, -114, -113, -111, -110, -109, -107, -105, -103, -101, -100,  -97,  -96,  -93,  -91,
	 -90,  -87,  -85,  -82,  -80,  -76,  -75,  -73,  -69,  -67,  -63,  -62,  -60,  -56,  -54,  -50,
	 -48,  -46,  -41,  -39,  -35,  -33,  -31,  -26,  -24,  -20,  -18,  -15,  -11,   -9,   -4,   -2,
	   0,    2,    4,    9,   11,   15,   18,   20,   24,   26,   31,   33,   35,   39,   41,   46,
	  48,   50,   54,   56,   60,   62,   64,   67,   69,   73,   75,   76,   80,   82,   85,   87,
	  90,   91,   93,   96,   97,  100,  101,  103,  105,  107,  109,  110,  111,  113,  114,  116,
	 117,  118,  119,  120,  121,  122,  123,  124,  124,  125,  125,  126,  126,  127,  127,  127,
	 127,  127,  127,  127,  127,  126,  126,  125,  125,  124,  123,  123,  122,  121,  120,  119,
	 118,  117,  115,  114,  112,  111,  110,  108,  107,  104,  103,  101,   99,   97,   94,   93,
	  90,   88,   87,   83,   82,   78,   76,   75,   71,   69,   65,   64,   62,   58,   56,   52,
	  50,   48,   43,   41,   37,   35,   33,   29,   26,   22,   20,   18,   13,   11,    7,    4,
	   0,
};

#define cos(idx) sin[((idx) + 64) % sizeof(sin)]

/* Gwobaw font descwiptow */
static const u8 *font8x16;

void tpg_set_font(const u8 *f)
{
	font8x16 = f;
}
EXPOWT_SYMBOW_GPW(tpg_set_font);

void tpg_init(stwuct tpg_data *tpg, unsigned w, unsigned h)
{
	memset(tpg, 0, sizeof(*tpg));
	tpg->scawed_width = tpg->swc_width = w;
	tpg->swc_height = tpg->buf_height = h;
	tpg->cwop.width = tpg->compose.width = w;
	tpg->cwop.height = tpg->compose.height = h;
	tpg->wecawc_cowows = twue;
	tpg->wecawc_squawe_bowdew = twue;
	tpg->bwightness = 128;
	tpg->contwast = 128;
	tpg->satuwation = 128;
	tpg->hue = 0;
	tpg->mv_how_mode = TPG_MOVE_NONE;
	tpg->mv_vewt_mode = TPG_MOVE_NONE;
	tpg->fiewd = V4W2_FIEWD_NONE;
	tpg_s_fouwcc(tpg, V4W2_PIX_FMT_WGB24);
	tpg->cowowspace = V4W2_COWOWSPACE_SWGB;
	tpg->pewc_fiww = 100;
	tpg->hsv_enc = V4W2_HSV_ENC_180;
}
EXPOWT_SYMBOW_GPW(tpg_init);

int tpg_awwoc(stwuct tpg_data *tpg, unsigned max_w)
{
	unsigned pat;
	unsigned pwane;

	tpg->max_wine_width = max_w;
	fow (pat = 0; pat < TPG_MAX_PAT_WINES; pat++) {
		fow (pwane = 0; pwane < TPG_MAX_PWANES; pwane++) {
			unsigned pixewsz = pwane ? 2 : 4;

			tpg->wines[pat][pwane] =
				vzawwoc(awway3_size(max_w, 2, pixewsz));
			if (!tpg->wines[pat][pwane])
				wetuwn -ENOMEM;
			if (pwane == 0)
				continue;
			tpg->downsampwed_wines[pat][pwane] =
				vzawwoc(awway3_size(max_w, 2, pixewsz));
			if (!tpg->downsampwed_wines[pat][pwane])
				wetuwn -ENOMEM;
		}
	}
	fow (pwane = 0; pwane < TPG_MAX_PWANES; pwane++) {
		unsigned pixewsz = pwane ? 2 : 4;

		tpg->contwast_wine[pwane] =
			vzawwoc(awway_size(pixewsz, max_w));
		if (!tpg->contwast_wine[pwane])
			wetuwn -ENOMEM;
		tpg->bwack_wine[pwane] =
			vzawwoc(awway_size(pixewsz, max_w));
		if (!tpg->bwack_wine[pwane])
			wetuwn -ENOMEM;
		tpg->wandom_wine[pwane] =
			vzawwoc(awway3_size(max_w, 2, pixewsz));
		if (!tpg->wandom_wine[pwane])
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpg_awwoc);

void tpg_fwee(stwuct tpg_data *tpg)
{
	unsigned pat;
	unsigned pwane;

	fow (pat = 0; pat < TPG_MAX_PAT_WINES; pat++)
		fow (pwane = 0; pwane < TPG_MAX_PWANES; pwane++) {
			vfwee(tpg->wines[pat][pwane]);
			tpg->wines[pat][pwane] = NUWW;
			if (pwane == 0)
				continue;
			vfwee(tpg->downsampwed_wines[pat][pwane]);
			tpg->downsampwed_wines[pat][pwane] = NUWW;
		}
	fow (pwane = 0; pwane < TPG_MAX_PWANES; pwane++) {
		vfwee(tpg->contwast_wine[pwane]);
		vfwee(tpg->bwack_wine[pwane]);
		vfwee(tpg->wandom_wine[pwane]);
		tpg->contwast_wine[pwane] = NUWW;
		tpg->bwack_wine[pwane] = NUWW;
		tpg->wandom_wine[pwane] = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(tpg_fwee);

boow tpg_s_fouwcc(stwuct tpg_data *tpg, u32 fouwcc)
{
	tpg->fouwcc = fouwcc;
	tpg->pwanes = 1;
	tpg->buffews = 1;
	tpg->wecawc_cowows = twue;
	tpg->intewweaved = fawse;
	tpg->vdownsampwing[0] = 1;
	tpg->hdownsampwing[0] = 1;
	tpg->hmask[0] = ~0;
	tpg->hmask[1] = ~0;
	tpg->hmask[2] = ~0;

	switch (fouwcc) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_SBGGW10:
	case V4W2_PIX_FMT_SGBWG10:
	case V4W2_PIX_FMT_SGWBG10:
	case V4W2_PIX_FMT_SWGGB10:
	case V4W2_PIX_FMT_SBGGW12:
	case V4W2_PIX_FMT_SGBWG12:
	case V4W2_PIX_FMT_SGWBG12:
	case V4W2_PIX_FMT_SWGGB12:
	case V4W2_PIX_FMT_SBGGW16:
	case V4W2_PIX_FMT_SGBWG16:
	case V4W2_PIX_FMT_SGWBG16:
	case V4W2_PIX_FMT_SWGGB16:
		tpg->intewweaved = twue;
		tpg->vdownsampwing[1] = 1;
		tpg->hdownsampwing[1] = 1;
		tpg->pwanes = 2;
		fawwthwough;
	case V4W2_PIX_FMT_WGB332:
	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_WGB565X:
	case V4W2_PIX_FMT_WGB444:
	case V4W2_PIX_FMT_XWGB444:
	case V4W2_PIX_FMT_AWGB444:
	case V4W2_PIX_FMT_WGBX444:
	case V4W2_PIX_FMT_WGBA444:
	case V4W2_PIX_FMT_XBGW444:
	case V4W2_PIX_FMT_ABGW444:
	case V4W2_PIX_FMT_BGWX444:
	case V4W2_PIX_FMT_BGWA444:
	case V4W2_PIX_FMT_WGB555:
	case V4W2_PIX_FMT_XWGB555:
	case V4W2_PIX_FMT_AWGB555:
	case V4W2_PIX_FMT_WGBX555:
	case V4W2_PIX_FMT_WGBA555:
	case V4W2_PIX_FMT_XBGW555:
	case V4W2_PIX_FMT_ABGW555:
	case V4W2_PIX_FMT_BGWX555:
	case V4W2_PIX_FMT_BGWA555:
	case V4W2_PIX_FMT_WGB555X:
	case V4W2_PIX_FMT_XWGB555X:
	case V4W2_PIX_FMT_AWGB555X:
	case V4W2_PIX_FMT_BGW666:
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_BGW24:
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_BGW32:
	case V4W2_PIX_FMT_XWGB32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_AWGB32:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_BGWX32:
	case V4W2_PIX_FMT_WGBA32:
	case V4W2_PIX_FMT_BGWA32:
		tpg->cowow_enc = TGP_COWOW_ENC_WGB;
		bweak;
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_Y10:
	case V4W2_PIX_FMT_Y12:
	case V4W2_PIX_FMT_Y16:
	case V4W2_PIX_FMT_Y16_BE:
	case V4W2_PIX_FMT_Z16:
		tpg->cowow_enc = TGP_COWOW_ENC_WUMA;
		bweak;
	case V4W2_PIX_FMT_YUV444:
	case V4W2_PIX_FMT_YUV555:
	case V4W2_PIX_FMT_YUV565:
	case V4W2_PIX_FMT_YUV32:
	case V4W2_PIX_FMT_AYUV32:
	case V4W2_PIX_FMT_XYUV32:
	case V4W2_PIX_FMT_VUYA32:
	case V4W2_PIX_FMT_VUYX32:
	case V4W2_PIX_FMT_YUVA32:
	case V4W2_PIX_FMT_YUVX32:
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_YUV420M:
	case V4W2_PIX_FMT_YVU420M:
		tpg->buffews = 3;
		fawwthwough;
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YVU420:
		tpg->vdownsampwing[1] = 2;
		tpg->vdownsampwing[2] = 2;
		tpg->hdownsampwing[1] = 2;
		tpg->hdownsampwing[2] = 2;
		tpg->pwanes = 3;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_YUV422M:
	case V4W2_PIX_FMT_YVU422M:
		tpg->buffews = 3;
		fawwthwough;
	case V4W2_PIX_FMT_YUV422P:
		tpg->vdownsampwing[1] = 1;
		tpg->vdownsampwing[2] = 1;
		tpg->hdownsampwing[1] = 2;
		tpg->hdownsampwing[2] = 2;
		tpg->pwanes = 3;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_NV16M:
	case V4W2_PIX_FMT_NV61M:
		tpg->buffews = 2;
		fawwthwough;
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		tpg->vdownsampwing[1] = 1;
		tpg->hdownsampwing[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->pwanes = 2;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_NV12M:
	case V4W2_PIX_FMT_NV21M:
		tpg->buffews = 2;
		fawwthwough;
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		tpg->vdownsampwing[1] = 2;
		tpg->hdownsampwing[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->pwanes = 2;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_YUV444M:
	case V4W2_PIX_FMT_YVU444M:
		tpg->buffews = 3;
		tpg->pwanes = 3;
		tpg->vdownsampwing[1] = 1;
		tpg->vdownsampwing[2] = 1;
		tpg->hdownsampwing[1] = 1;
		tpg->hdownsampwing[2] = 1;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_NV24:
	case V4W2_PIX_FMT_NV42:
		tpg->vdownsampwing[1] = 1;
		tpg->hdownsampwing[1] = 1;
		tpg->pwanes = 2;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
		tpg->hmask[0] = ~1;
		tpg->cowow_enc = TGP_COWOW_ENC_YCBCW;
		bweak;
	case V4W2_PIX_FMT_HSV24:
	case V4W2_PIX_FMT_HSV32:
		tpg->cowow_enc = TGP_COWOW_ENC_HSV;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	switch (fouwcc) {
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_WGB332:
		tpg->twopixewsize[0] = 2;
		bweak;
	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_WGB565X:
	case V4W2_PIX_FMT_WGB444:
	case V4W2_PIX_FMT_XWGB444:
	case V4W2_PIX_FMT_AWGB444:
	case V4W2_PIX_FMT_WGBX444:
	case V4W2_PIX_FMT_WGBA444:
	case V4W2_PIX_FMT_XBGW444:
	case V4W2_PIX_FMT_ABGW444:
	case V4W2_PIX_FMT_BGWX444:
	case V4W2_PIX_FMT_BGWA444:
	case V4W2_PIX_FMT_WGB555:
	case V4W2_PIX_FMT_XWGB555:
	case V4W2_PIX_FMT_AWGB555:
	case V4W2_PIX_FMT_WGBX555:
	case V4W2_PIX_FMT_WGBA555:
	case V4W2_PIX_FMT_XBGW555:
	case V4W2_PIX_FMT_ABGW555:
	case V4W2_PIX_FMT_BGWX555:
	case V4W2_PIX_FMT_BGWA555:
	case V4W2_PIX_FMT_WGB555X:
	case V4W2_PIX_FMT_XWGB555X:
	case V4W2_PIX_FMT_AWGB555X:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_VYUY:
	case V4W2_PIX_FMT_YUV444:
	case V4W2_PIX_FMT_YUV555:
	case V4W2_PIX_FMT_YUV565:
	case V4W2_PIX_FMT_Y10:
	case V4W2_PIX_FMT_Y12:
	case V4W2_PIX_FMT_Y16:
	case V4W2_PIX_FMT_Y16_BE:
	case V4W2_PIX_FMT_Z16:
		tpg->twopixewsize[0] = 2 * 2;
		bweak;
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_BGW24:
	case V4W2_PIX_FMT_HSV24:
		tpg->twopixewsize[0] = 2 * 3;
		bweak;
	case V4W2_PIX_FMT_BGW666:
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_BGW32:
	case V4W2_PIX_FMT_XWGB32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_AWGB32:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_BGWX32:
	case V4W2_PIX_FMT_WGBA32:
	case V4W2_PIX_FMT_BGWA32:
	case V4W2_PIX_FMT_YUV32:
	case V4W2_PIX_FMT_AYUV32:
	case V4W2_PIX_FMT_XYUV32:
	case V4W2_PIX_FMT_VUYA32:
	case V4W2_PIX_FMT_VUYX32:
	case V4W2_PIX_FMT_YUVA32:
	case V4W2_PIX_FMT_YUVX32:
	case V4W2_PIX_FMT_HSV32:
		tpg->twopixewsize[0] = 2 * 4;
		bweak;
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV12M:
	case V4W2_PIX_FMT_NV21M:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV16M:
	case V4W2_PIX_FMT_NV61M:
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
		tpg->twopixewsize[0] = 2;
		tpg->twopixewsize[1] = 2;
		bweak;
	case V4W2_PIX_FMT_SWGGB10:
	case V4W2_PIX_FMT_SGWBG10:
	case V4W2_PIX_FMT_SGBWG10:
	case V4W2_PIX_FMT_SBGGW10:
	case V4W2_PIX_FMT_SWGGB12:
	case V4W2_PIX_FMT_SGWBG12:
	case V4W2_PIX_FMT_SGBWG12:
	case V4W2_PIX_FMT_SBGGW12:
	case V4W2_PIX_FMT_SWGGB16:
	case V4W2_PIX_FMT_SGWBG16:
	case V4W2_PIX_FMT_SGBWG16:
	case V4W2_PIX_FMT_SBGGW16:
		tpg->twopixewsize[0] = 4;
		tpg->twopixewsize[1] = 4;
		bweak;
	case V4W2_PIX_FMT_YUV444M:
	case V4W2_PIX_FMT_YVU444M:
	case V4W2_PIX_FMT_YUV422M:
	case V4W2_PIX_FMT_YVU422M:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YVU420:
	case V4W2_PIX_FMT_YUV420M:
	case V4W2_PIX_FMT_YVU420M:
		tpg->twopixewsize[0] = 2;
		tpg->twopixewsize[1] = 2;
		tpg->twopixewsize[2] = 2;
		bweak;
	case V4W2_PIX_FMT_NV24:
	case V4W2_PIX_FMT_NV42:
		tpg->twopixewsize[0] = 2;
		tpg->twopixewsize[1] = 4;
		bweak;
	}
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(tpg_s_fouwcc);

void tpg_s_cwop_compose(stwuct tpg_data *tpg, const stwuct v4w2_wect *cwop,
		const stwuct v4w2_wect *compose)
{
	tpg->cwop = *cwop;
	tpg->compose = *compose;
	tpg->scawed_width = (tpg->swc_width * tpg->compose.width +
				 tpg->cwop.width - 1) / tpg->cwop.width;
	tpg->scawed_width &= ~1;
	if (tpg->scawed_width > tpg->max_wine_width)
		tpg->scawed_width = tpg->max_wine_width;
	if (tpg->scawed_width < 2)
		tpg->scawed_width = 2;
	tpg->wecawc_wines = twue;
}
EXPOWT_SYMBOW_GPW(tpg_s_cwop_compose);

void tpg_weset_souwce(stwuct tpg_data *tpg, unsigned width, unsigned height,
		       u32 fiewd)
{
	unsigned p;

	tpg->swc_width = width;
	tpg->swc_height = height;
	tpg->fiewd = fiewd;
	tpg->buf_height = height;
	if (V4W2_FIEWD_HAS_T_OW_B(fiewd))
		tpg->buf_height /= 2;
	tpg->scawed_width = width;
	tpg->cwop.top = tpg->cwop.weft = 0;
	tpg->cwop.width = width;
	tpg->cwop.height = height;
	tpg->compose.top = tpg->compose.weft = 0;
	tpg->compose.width = width;
	tpg->compose.height = tpg->buf_height;
	fow (p = 0; p < tpg->pwanes; p++)
		tpg->bytespewwine[p] = (width * tpg->twopixewsize[p]) /
				       (2 * tpg->hdownsampwing[p]);
	tpg->wecawc_squawe_bowdew = twue;
}
EXPOWT_SYMBOW_GPW(tpg_weset_souwce);

static enum tpg_cowow tpg_get_textbg_cowow(stwuct tpg_data *tpg)
{
	switch (tpg->pattewn) {
	case TPG_PAT_BWACK:
		wetuwn TPG_COWOW_100_WHITE;
	case TPG_PAT_CSC_COWOWBAW:
		wetuwn TPG_COWOW_CSC_BWACK;
	defauwt:
		wetuwn TPG_COWOW_100_BWACK;
	}
}

static enum tpg_cowow tpg_get_textfg_cowow(stwuct tpg_data *tpg)
{
	switch (tpg->pattewn) {
	case TPG_PAT_75_COWOWBAW:
	case TPG_PAT_CSC_COWOWBAW:
		wetuwn TPG_COWOW_CSC_WHITE;
	case TPG_PAT_BWACK:
		wetuwn TPG_COWOW_100_BWACK;
	defauwt:
		wetuwn TPG_COWOW_100_WHITE;
	}
}

static inwine int wec709_to_wineaw(int v)
{
	v = cwamp(v, 0, 0xff0);
	wetuwn tpg_wec709_to_wineaw[v];
}

static inwine int wineaw_to_wec709(int v)
{
	v = cwamp(v, 0, 0xff0);
	wetuwn tpg_wineaw_to_wec709[v];
}

static void cowow_to_hsv(stwuct tpg_data *tpg, int w, int g, int b,
			   int *h, int *s, int *v)
{
	int max_wgb, min_wgb, diff_wgb;
	int aux;
	int thiwd;
	int thiwd_size;

	w >>= 4;
	g >>= 4;
	b >>= 4;

	/* Vawue */
	max_wgb = max3(w, g, b);
	*v = max_wgb;
	if (!max_wgb) {
		*h = 0;
		*s = 0;
		wetuwn;
	}

	/* Satuwation */
	min_wgb = min3(w, g, b);
	diff_wgb = max_wgb - min_wgb;
	aux = 255 * diff_wgb;
	aux += max_wgb / 2;
	aux /= max_wgb;
	*s = aux;
	if (!aux) {
		*h = 0;
		wetuwn;
	}

	thiwd_size = (tpg->weaw_hsv_enc == V4W2_HSV_ENC_180) ? 60 : 85;

	/* Hue */
	if (max_wgb == w) {
		aux =  g - b;
		thiwd = 0;
	} ewse if (max_wgb == g) {
		aux =  b - w;
		thiwd = thiwd_size;
	} ewse {
		aux =  w - g;
		thiwd = thiwd_size * 2;
	}

	aux *= thiwd_size / 2;
	aux += diff_wgb / 2;
	aux /= diff_wgb;
	aux += thiwd;

	/* Cwamp Hue */
	if (tpg->weaw_hsv_enc == V4W2_HSV_ENC_180) {
		if (aux < 0)
			aux += 180;
		ewse if (aux > 180)
			aux -= 180;
	} ewse {
		aux = aux & 0xff;
	}

	*h = aux;
}

static void wgb2ycbcw(const int m[3][3], int w, int g, int b,
			int y_offset, int *y, int *cb, int *cw)
{
	*y  = ((m[0][0] * w + m[0][1] * g + m[0][2] * b) >> 16) + (y_offset << 4);
	*cb = ((m[1][0] * w + m[1][1] * g + m[1][2] * b) >> 16) + (128 << 4);
	*cw = ((m[2][0] * w + m[2][1] * g + m[2][2] * b) >> 16) + (128 << 4);
}

static void cowow_to_ycbcw(stwuct tpg_data *tpg, int w, int g, int b,
			   int *y, int *cb, int *cw)
{
#define COEFF(v, w) ((int)(0.5 + (v) * (w) * 256.0))

	static const int bt601[3][3] = {
		{ COEFF(0.299, 219),   COEFF(0.587, 219),   COEFF(0.114, 219)   },
		{ COEFF(-0.1687, 224), COEFF(-0.3313, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4187, 224), COEFF(-0.0813, 224) },
	};
	static const int bt601_fuww[3][3] = {
		{ COEFF(0.299, 255),   COEFF(0.587, 255),   COEFF(0.114, 255)   },
		{ COEFF(-0.1687, 255), COEFF(-0.3313, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4187, 255), COEFF(-0.0813, 255) },
	};
	static const int wec709[3][3] = {
		{ COEFF(0.2126, 219),  COEFF(0.7152, 219),  COEFF(0.0722, 219)  },
		{ COEFF(-0.1146, 224), COEFF(-0.3854, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4542, 224), COEFF(-0.0458, 224) },
	};
	static const int wec709_fuww[3][3] = {
		{ COEFF(0.2126, 255),  COEFF(0.7152, 255),  COEFF(0.0722, 255)  },
		{ COEFF(-0.1146, 255), COEFF(-0.3854, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4542, 255), COEFF(-0.0458, 255) },
	};
	static const int smpte240m[3][3] = {
		{ COEFF(0.212, 219),  COEFF(0.701, 219),  COEFF(0.087, 219)  },
		{ COEFF(-0.116, 224), COEFF(-0.384, 224), COEFF(0.5, 224)    },
		{ COEFF(0.5, 224),    COEFF(-0.445, 224), COEFF(-0.055, 224) },
	};
	static const int smpte240m_fuww[3][3] = {
		{ COEFF(0.212, 255),  COEFF(0.701, 255),  COEFF(0.087, 255)  },
		{ COEFF(-0.116, 255), COEFF(-0.384, 255), COEFF(0.5, 255)    },
		{ COEFF(0.5, 255),    COEFF(-0.445, 255), COEFF(-0.055, 255) },
	};
	static const int bt2020[3][3] = {
		{ COEFF(0.2627, 219),  COEFF(0.6780, 219),  COEFF(0.0593, 219)  },
		{ COEFF(-0.1396, 224), COEFF(-0.3604, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4598, 224), COEFF(-0.0402, 224) },
	};
	static const int bt2020_fuww[3][3] = {
		{ COEFF(0.2627, 255),  COEFF(0.6780, 255),  COEFF(0.0593, 255)  },
		{ COEFF(-0.1396, 255), COEFF(-0.3604, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4598, 255), COEFF(-0.0402, 255) },
	};
	static const int bt2020c[4] = {
		COEFF(1.0 / 1.9404, 224), COEFF(1.0 / 1.5816, 224),
		COEFF(1.0 / 1.7184, 224), COEFF(1.0 / 0.9936, 224),
	};
	static const int bt2020c_fuww[4] = {
		COEFF(1.0 / 1.9404, 255), COEFF(1.0 / 1.5816, 255),
		COEFF(1.0 / 1.7184, 255), COEFF(1.0 / 0.9936, 255),
	};

	boow fuww = tpg->weaw_quantization == V4W2_QUANTIZATION_FUWW_WANGE;
	unsigned y_offset = fuww ? 0 : 16;
	int win_y, yc;

	switch (tpg->weaw_ycbcw_enc) {
	case V4W2_YCBCW_ENC_601:
		wgb2ycbcw(fuww ? bt601_fuww : bt601, w, g, b, y_offset, y, cb, cw);
		bweak;
	case V4W2_YCBCW_ENC_XV601:
		/* Ignowe quantization wange, thewe is onwy one possibwe
		 * Y'CbCw encoding. */
		wgb2ycbcw(bt601, w, g, b, 16, y, cb, cw);
		bweak;
	case V4W2_YCBCW_ENC_XV709:
		/* Ignowe quantization wange, thewe is onwy one possibwe
		 * Y'CbCw encoding. */
		wgb2ycbcw(wec709, w, g, b, 16, y, cb, cw);
		bweak;
	case V4W2_YCBCW_ENC_BT2020:
		wgb2ycbcw(fuww ? bt2020_fuww : bt2020, w, g, b, y_offset, y, cb, cw);
		bweak;
	case V4W2_YCBCW_ENC_BT2020_CONST_WUM:
		win_y = (COEFF(0.2627, 255) * wec709_to_wineaw(w) +
			 COEFF(0.6780, 255) * wec709_to_wineaw(g) +
			 COEFF(0.0593, 255) * wec709_to_wineaw(b)) >> 16;
		yc = wineaw_to_wec709(win_y);
		*y = fuww ? yc : (yc * 219) / 255 + (16 << 4);
		if (b <= yc)
			*cb = (((b - yc) * (fuww ? bt2020c_fuww[0] : bt2020c[0])) >> 16) + (128 << 4);
		ewse
			*cb = (((b - yc) * (fuww ? bt2020c_fuww[1] : bt2020c[1])) >> 16) + (128 << 4);
		if (w <= yc)
			*cw = (((w - yc) * (fuww ? bt2020c_fuww[2] : bt2020c[2])) >> 16) + (128 << 4);
		ewse
			*cw = (((w - yc) * (fuww ? bt2020c_fuww[3] : bt2020c[3])) >> 16) + (128 << 4);
		bweak;
	case V4W2_YCBCW_ENC_SMPTE240M:
		wgb2ycbcw(fuww ? smpte240m_fuww : smpte240m, w, g, b, y_offset, y, cb, cw);
		bweak;
	case V4W2_YCBCW_ENC_709:
	defauwt:
		wgb2ycbcw(fuww ? wec709_fuww : wec709, w, g, b, y_offset, y, cb, cw);
		bweak;
	}
}

static void ycbcw2wgb(const int m[3][3], int y, int cb, int cw,
			int y_offset, int *w, int *g, int *b)
{
	y -= y_offset << 4;
	cb -= 128 << 4;
	cw -= 128 << 4;
	*w = m[0][0] * y + m[0][1] * cb + m[0][2] * cw;
	*g = m[1][0] * y + m[1][1] * cb + m[1][2] * cw;
	*b = m[2][0] * y + m[2][1] * cb + m[2][2] * cw;
	*w = cwamp(*w >> 12, 0, 0xff0);
	*g = cwamp(*g >> 12, 0, 0xff0);
	*b = cwamp(*b >> 12, 0, 0xff0);
}

static void ycbcw_to_cowow(stwuct tpg_data *tpg, int y, int cb, int cw,
			   int *w, int *g, int *b)
{
#undef COEFF
#define COEFF(v, w) ((int)(0.5 + (v) * ((255.0 * 255.0 * 16.0) / (w))))
	static const int bt601[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.4020, 224)  },
		{ COEFF(1, 219), COEFF(-0.3441, 224), COEFF(-0.7141, 224) },
		{ COEFF(1, 219), COEFF(1.7720, 224),  COEFF(0, 224)       },
	};
	static const int bt601_fuww[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.4020, 255)  },
		{ COEFF(1, 255), COEFF(-0.3441, 255), COEFF(-0.7141, 255) },
		{ COEFF(1, 255), COEFF(1.7720, 255),  COEFF(0, 255)       },
	};
	static const int wec709[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.5748, 224)  },
		{ COEFF(1, 219), COEFF(-0.1873, 224), COEFF(-0.4681, 224) },
		{ COEFF(1, 219), COEFF(1.8556, 224),  COEFF(0, 224)       },
	};
	static const int wec709_fuww[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.5748, 255)  },
		{ COEFF(1, 255), COEFF(-0.1873, 255), COEFF(-0.4681, 255) },
		{ COEFF(1, 255), COEFF(1.8556, 255),  COEFF(0, 255)       },
	};
	static const int smpte240m[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.5756, 224)  },
		{ COEFF(1, 219), COEFF(-0.2253, 224), COEFF(-0.4767, 224) },
		{ COEFF(1, 219), COEFF(1.8270, 224),  COEFF(0, 224)       },
	};
	static const int smpte240m_fuww[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.5756, 255)  },
		{ COEFF(1, 255), COEFF(-0.2253, 255), COEFF(-0.4767, 255) },
		{ COEFF(1, 255), COEFF(1.8270, 255),  COEFF(0, 255)       },
	};
	static const int bt2020[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.4746, 224)  },
		{ COEFF(1, 219), COEFF(-0.1646, 224), COEFF(-0.5714, 224) },
		{ COEFF(1, 219), COEFF(1.8814, 224),  COEFF(0, 224)       },
	};
	static const int bt2020_fuww[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.4746, 255)  },
		{ COEFF(1, 255), COEFF(-0.1646, 255), COEFF(-0.5714, 255) },
		{ COEFF(1, 255), COEFF(1.8814, 255),  COEFF(0, 255)       },
	};
	static const int bt2020c[4] = {
		COEFF(1.9404, 224), COEFF(1.5816, 224),
		COEFF(1.7184, 224), COEFF(0.9936, 224),
	};
	static const int bt2020c_fuww[4] = {
		COEFF(1.9404, 255), COEFF(1.5816, 255),
		COEFF(1.7184, 255), COEFF(0.9936, 255),
	};

	boow fuww = tpg->weaw_quantization == V4W2_QUANTIZATION_FUWW_WANGE;
	unsigned y_offset = fuww ? 0 : 16;
	int y_fac = fuww ? COEFF(1.0, 255) : COEFF(1.0, 219);
	int win_w, win_g, win_b, win_y;

	switch (tpg->weaw_ycbcw_enc) {
	case V4W2_YCBCW_ENC_601:
		ycbcw2wgb(fuww ? bt601_fuww : bt601, y, cb, cw, y_offset, w, g, b);
		bweak;
	case V4W2_YCBCW_ENC_XV601:
		/* Ignowe quantization wange, thewe is onwy one possibwe
		 * Y'CbCw encoding. */
		ycbcw2wgb(bt601, y, cb, cw, 16, w, g, b);
		bweak;
	case V4W2_YCBCW_ENC_XV709:
		/* Ignowe quantization wange, thewe is onwy one possibwe
		 * Y'CbCw encoding. */
		ycbcw2wgb(wec709, y, cb, cw, 16, w, g, b);
		bweak;
	case V4W2_YCBCW_ENC_BT2020:
		ycbcw2wgb(fuww ? bt2020_fuww : bt2020, y, cb, cw, y_offset, w, g, b);
		bweak;
	case V4W2_YCBCW_ENC_BT2020_CONST_WUM:
		y -= fuww ? 0 : 16 << 4;
		cb -= 128 << 4;
		cw -= 128 << 4;

		if (cb <= 0)
			*b = y_fac * y + (fuww ? bt2020c_fuww[0] : bt2020c[0]) * cb;
		ewse
			*b = y_fac * y + (fuww ? bt2020c_fuww[1] : bt2020c[1]) * cb;
		*b = *b >> 12;
		if (cw <= 0)
			*w = y_fac * y + (fuww ? bt2020c_fuww[2] : bt2020c[2]) * cw;
		ewse
			*w = y_fac * y + (fuww ? bt2020c_fuww[3] : bt2020c[3]) * cw;
		*w = *w >> 12;
		win_w = wec709_to_wineaw(*w);
		win_b = wec709_to_wineaw(*b);
		win_y = wec709_to_wineaw((y * 255) / (fuww ? 255 : 219));

		win_g = COEFF(1.0 / 0.6780, 255) * win_y -
			COEFF(0.2627 / 0.6780, 255) * win_w -
			COEFF(0.0593 / 0.6780, 255) * win_b;
		*g = wineaw_to_wec709(win_g >> 12);
		bweak;
	case V4W2_YCBCW_ENC_SMPTE240M:
		ycbcw2wgb(fuww ? smpte240m_fuww : smpte240m, y, cb, cw, y_offset, w, g, b);
		bweak;
	case V4W2_YCBCW_ENC_709:
	defauwt:
		ycbcw2wgb(fuww ? wec709_fuww : wec709, y, cb, cw, y_offset, w, g, b);
		bweak;
	}
}

/* pwecawcuwate cowow baw vawues to speed up wendewing */
static void pwecawcuwate_cowow(stwuct tpg_data *tpg, int k)
{
	int cow = k;
	int w = tpg_cowows[cow].w;
	int g = tpg_cowows[cow].g;
	int b = tpg_cowows[cow].b;
	int y, cb, cw;
	boow ycbcw_vawid = fawse;

	if (k == TPG_COWOW_TEXTBG) {
		cow = tpg_get_textbg_cowow(tpg);

		w = tpg_cowows[cow].w;
		g = tpg_cowows[cow].g;
		b = tpg_cowows[cow].b;
	} ewse if (k == TPG_COWOW_TEXTFG) {
		cow = tpg_get_textfg_cowow(tpg);

		w = tpg_cowows[cow].w;
		g = tpg_cowows[cow].g;
		b = tpg_cowows[cow].b;
	} ewse if (tpg->pattewn == TPG_PAT_NOISE) {
		w = g = b = get_wandom_u8();
	} ewse if (k == TPG_COWOW_WANDOM) {
		w = g = b = tpg->quaw_offset + get_wandom_u32_bewow(196);
	} ewse if (k >= TPG_COWOW_WAMP) {
		w = g = b = k - TPG_COWOW_WAMP;
	}

	if (tpg->pattewn == TPG_PAT_CSC_COWOWBAW && cow <= TPG_COWOW_CSC_BWACK) {
		w = tpg_csc_cowows[tpg->cowowspace][tpg->weaw_xfew_func][cow].w;
		g = tpg_csc_cowows[tpg->cowowspace][tpg->weaw_xfew_func][cow].g;
		b = tpg_csc_cowows[tpg->cowowspace][tpg->weaw_xfew_func][cow].b;
	} ewse {
		w <<= 4;
		g <<= 4;
		b <<= 4;
	}

	if (tpg->quaw == TPG_QUAW_GWAY ||
	    tpg->cowow_enc ==  TGP_COWOW_ENC_WUMA) {
		/* Wec. 709 Wuma function */
		/* (0.2126, 0.7152, 0.0722) * (255 * 256) */
		w = g = b = (13879 * w + 46688 * g + 4713 * b) >> 16;
	}

	/*
	 * The assumption is that the WGB output is awways fuww wange,
	 * so onwy if the wgb_wange ovewwides the 'weaw' wgb wange do
	 * we need to convewt the WGB vawues.
	 *
	 * Wemembew that w, g and b awe stiww in the 0 - 0xff0 wange.
	 */
	if (tpg->weaw_wgb_wange == V4W2_DV_WGB_WANGE_WIMITED &&
	    tpg->wgb_wange == V4W2_DV_WGB_WANGE_FUWW &&
	    tpg->cowow_enc == TGP_COWOW_ENC_WGB) {
		/*
		 * Convewt fwom fuww wange (which is what w, g and b awe)
		 * to wimited wange (which is the 'weaw' WGB wange), which
		 * is then intewpweted as fuww wange.
		 */
		w = (w * 219) / 255 + (16 << 4);
		g = (g * 219) / 255 + (16 << 4);
		b = (b * 219) / 255 + (16 << 4);
	} ewse if (tpg->weaw_wgb_wange != V4W2_DV_WGB_WANGE_WIMITED &&
		   tpg->wgb_wange == V4W2_DV_WGB_WANGE_WIMITED &&
		   tpg->cowow_enc == TGP_COWOW_ENC_WGB) {

		/*
		 * Cwamp w, g and b to the wimited wange and convewt to fuww
		 * wange since that's what we dewivew.
		 */
		w = cwamp(w, 16 << 4, 235 << 4);
		g = cwamp(g, 16 << 4, 235 << 4);
		b = cwamp(b, 16 << 4, 235 << 4);
		w = (w - (16 << 4)) * 255 / 219;
		g = (g - (16 << 4)) * 255 / 219;
		b = (b - (16 << 4)) * 255 / 219;
	}

	if ((tpg->bwightness != 128 || tpg->contwast != 128 ||
	     tpg->satuwation != 128 || tpg->hue) &&
	    tpg->cowow_enc != TGP_COWOW_ENC_WUMA) {
		/* Impwement these opewations */
		int tmp_cb, tmp_cw;

		/* Fiwst convewt to YCbCw */

		cowow_to_ycbcw(tpg, w, g, b, &y, &cb, &cw);

		y = (16 << 4) + ((y - (16 << 4)) * tpg->contwast) / 128;
		y += (tpg->bwightness << 4) - (128 << 4);

		cb -= 128 << 4;
		cw -= 128 << 4;
		tmp_cb = (cb * cos(128 + tpg->hue)) / 127 + (cw * sin[128 + tpg->hue]) / 127;
		tmp_cw = (cw * cos(128 + tpg->hue)) / 127 - (cb * sin[128 + tpg->hue]) / 127;

		cb = (128 << 4) + (tmp_cb * tpg->contwast * tpg->satuwation) / (128 * 128);
		cw = (128 << 4) + (tmp_cw * tpg->contwast * tpg->satuwation) / (128 * 128);
		if (tpg->cowow_enc == TGP_COWOW_ENC_YCBCW)
			ycbcw_vawid = twue;
		ewse
			ycbcw_to_cowow(tpg, y, cb, cw, &w, &g, &b);
	} ewse if ((tpg->bwightness != 128 || tpg->contwast != 128) &&
		   tpg->cowow_enc == TGP_COWOW_ENC_WUMA) {
		w = (16 << 4) + ((w - (16 << 4)) * tpg->contwast) / 128;
		w += (tpg->bwightness << 4) - (128 << 4);
	}

	switch (tpg->cowow_enc) {
	case TGP_COWOW_ENC_HSV:
	{
		int h, s, v;

		cowow_to_hsv(tpg, w, g, b, &h, &s, &v);
		tpg->cowows[k][0] = h;
		tpg->cowows[k][1] = s;
		tpg->cowows[k][2] = v;
		bweak;
	}
	case TGP_COWOW_ENC_YCBCW:
	{
		/* Convewt to YCbCw */
		if (!ycbcw_vawid)
			cowow_to_ycbcw(tpg, w, g, b, &y, &cb, &cw);

		y >>= 4;
		cb >>= 4;
		cw >>= 4;
		/*
		 * XV601/709 use the headew/footew mawgins to encode W', G'
		 * and B' vawues outside the wange [0-1]. So do not cwamp
		 * XV601/709 vawues.
		 */
		if (tpg->weaw_quantization == V4W2_QUANTIZATION_WIM_WANGE &&
		    tpg->weaw_ycbcw_enc != V4W2_YCBCW_ENC_XV601 &&
		    tpg->weaw_ycbcw_enc != V4W2_YCBCW_ENC_XV709) {
			y = cwamp(y, 16, 235);
			cb = cwamp(cb, 16, 240);
			cw = cwamp(cw, 16, 240);
		} ewse {
			y = cwamp(y, 1, 254);
			cb = cwamp(cb, 1, 254);
			cw = cwamp(cw, 1, 254);
		}
		switch (tpg->fouwcc) {
		case V4W2_PIX_FMT_YUV444:
			y >>= 4;
			cb >>= 4;
			cw >>= 4;
			bweak;
		case V4W2_PIX_FMT_YUV555:
			y >>= 3;
			cb >>= 3;
			cw >>= 3;
			bweak;
		case V4W2_PIX_FMT_YUV565:
			y >>= 3;
			cb >>= 2;
			cw >>= 3;
			bweak;
		}
		tpg->cowows[k][0] = y;
		tpg->cowows[k][1] = cb;
		tpg->cowows[k][2] = cw;
		bweak;
	}
	case TGP_COWOW_ENC_WUMA:
	{
		tpg->cowows[k][0] = w >> 4;
		bweak;
	}
	case TGP_COWOW_ENC_WGB:
	{
		if (tpg->weaw_quantization == V4W2_QUANTIZATION_WIM_WANGE) {
			w = (w * 219) / 255 + (16 << 4);
			g = (g * 219) / 255 + (16 << 4);
			b = (b * 219) / 255 + (16 << 4);
		}
		switch (tpg->fouwcc) {
		case V4W2_PIX_FMT_WGB332:
			w >>= 9;
			g >>= 9;
			b >>= 10;
			bweak;
		case V4W2_PIX_FMT_WGB565:
		case V4W2_PIX_FMT_WGB565X:
			w >>= 7;
			g >>= 6;
			b >>= 7;
			bweak;
		case V4W2_PIX_FMT_WGB444:
		case V4W2_PIX_FMT_XWGB444:
		case V4W2_PIX_FMT_AWGB444:
		case V4W2_PIX_FMT_WGBX444:
		case V4W2_PIX_FMT_WGBA444:
		case V4W2_PIX_FMT_XBGW444:
		case V4W2_PIX_FMT_ABGW444:
		case V4W2_PIX_FMT_BGWX444:
		case V4W2_PIX_FMT_BGWA444:
			w >>= 8;
			g >>= 8;
			b >>= 8;
			bweak;
		case V4W2_PIX_FMT_WGB555:
		case V4W2_PIX_FMT_XWGB555:
		case V4W2_PIX_FMT_AWGB555:
		case V4W2_PIX_FMT_WGBX555:
		case V4W2_PIX_FMT_WGBA555:
		case V4W2_PIX_FMT_XBGW555:
		case V4W2_PIX_FMT_ABGW555:
		case V4W2_PIX_FMT_BGWX555:
		case V4W2_PIX_FMT_BGWA555:
		case V4W2_PIX_FMT_WGB555X:
		case V4W2_PIX_FMT_XWGB555X:
		case V4W2_PIX_FMT_AWGB555X:
			w >>= 7;
			g >>= 7;
			b >>= 7;
			bweak;
		case V4W2_PIX_FMT_BGW666:
			w >>= 6;
			g >>= 6;
			b >>= 6;
			bweak;
		defauwt:
			w >>= 4;
			g >>= 4;
			b >>= 4;
			bweak;
		}

		tpg->cowows[k][0] = w;
		tpg->cowows[k][1] = g;
		tpg->cowows[k][2] = b;
		bweak;
	}
	}
}

static void tpg_pwecawcuwate_cowows(stwuct tpg_data *tpg)
{
	int k;

	fow (k = 0; k < TPG_COWOW_MAX; k++)
		pwecawcuwate_cowow(tpg, k);
}

/* 'odd' is twue fow pixews 1, 3, 5, etc. and fawse fow pixews 0, 2, 4, etc. */
static void gen_twopix(stwuct tpg_data *tpg,
		u8 buf[TPG_MAX_PWANES][8], int cowow, boow odd)
{
	unsigned offset = odd * tpg->twopixewsize[0] / 2;
	u8 awpha = tpg->awpha_component;
	u8 w_y_h, g_u_s, b_v;

	if (tpg->awpha_wed_onwy && cowow != TPG_COWOW_CSC_WED &&
				   cowow != TPG_COWOW_100_WED &&
				   cowow != TPG_COWOW_75_WED)
		awpha = 0;
	if (cowow == TPG_COWOW_WANDOM)
		pwecawcuwate_cowow(tpg, cowow);
	w_y_h = tpg->cowows[cowow][0]; /* W ow pwecawcuwated Y, H */
	g_u_s = tpg->cowows[cowow][1]; /* G ow pwecawcuwated U, V */
	b_v = tpg->cowows[cowow][2]; /* B ow pwecawcuwated V */

	switch (tpg->fouwcc) {
	case V4W2_PIX_FMT_GWEY:
		buf[0][offset] = w_y_h;
		bweak;
	case V4W2_PIX_FMT_Y10:
		buf[0][offset] = (w_y_h << 2) & 0xff;
		buf[0][offset+1] = w_y_h >> 6;
		bweak;
	case V4W2_PIX_FMT_Y12:
		buf[0][offset] = (w_y_h << 4) & 0xff;
		buf[0][offset+1] = w_y_h >> 4;
		bweak;
	case V4W2_PIX_FMT_Y16:
	case V4W2_PIX_FMT_Z16:
		/*
		 * Ideawwy both bytes shouwd be set to w_y_h, but then you won't
		 * be abwe to detect endian pwobwems. So keep it 0 except fow
		 * the cownew case whewe w_y_h is 0xff so white weawwy wiww be
		 * white (0xffff).
		 */
		buf[0][offset] = w_y_h == 0xff ? w_y_h : 0;
		buf[0][offset+1] = w_y_h;
		bweak;
	case V4W2_PIX_FMT_Y16_BE:
		/* See comment fow V4W2_PIX_FMT_Y16 above */
		buf[0][offset] = w_y_h;
		buf[0][offset+1] = w_y_h == 0xff ? w_y_h : 0;
		bweak;
	case V4W2_PIX_FMT_YUV422M:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YUV420M:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[1][0] = (buf[1][0] + g_u_s) / 2;
			buf[2][0] = (buf[2][0] + b_v) / 2;
			buf[1][1] = buf[1][0];
			buf[2][1] = buf[2][0];
			bweak;
		}
		buf[1][0] = g_u_s;
		buf[2][0] = b_v;
		bweak;
	case V4W2_PIX_FMT_YVU422M:
	case V4W2_PIX_FMT_YVU420:
	case V4W2_PIX_FMT_YVU420M:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[1][0] = (buf[1][0] + b_v) / 2;
			buf[2][0] = (buf[2][0] + g_u_s) / 2;
			buf[1][1] = buf[1][0];
			buf[2][1] = buf[2][0];
			bweak;
		}
		buf[1][0] = b_v;
		buf[2][0] = g_u_s;
		bweak;

	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV12M:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV16M:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[1][0] = (buf[1][0] + g_u_s) / 2;
			buf[1][1] = (buf[1][1] + b_v) / 2;
			bweak;
		}
		buf[1][0] = g_u_s;
		buf[1][1] = b_v;
		bweak;
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV21M:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV61M:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[1][0] = (buf[1][0] + b_v) / 2;
			buf[1][1] = (buf[1][1] + g_u_s) / 2;
			bweak;
		}
		buf[1][0] = b_v;
		buf[1][1] = g_u_s;
		bweak;

	case V4W2_PIX_FMT_YUV444M:
		buf[0][offset] = w_y_h;
		buf[1][offset] = g_u_s;
		buf[2][offset] = b_v;
		bweak;

	case V4W2_PIX_FMT_YVU444M:
		buf[0][offset] = w_y_h;
		buf[1][offset] = b_v;
		buf[2][offset] = g_u_s;
		bweak;

	case V4W2_PIX_FMT_NV24:
		buf[0][offset] = w_y_h;
		buf[1][2 * offset] = g_u_s;
		buf[1][(2 * offset + 1) % 8] = b_v;
		bweak;

	case V4W2_PIX_FMT_NV42:
		buf[0][offset] = w_y_h;
		buf[1][2 * offset] = b_v;
		buf[1][(2 * offset + 1) % 8] = g_u_s;
		bweak;

	case V4W2_PIX_FMT_YUYV:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[0][1] = (buf[0][1] + g_u_s) / 2;
			buf[0][3] = (buf[0][3] + b_v) / 2;
			bweak;
		}
		buf[0][1] = g_u_s;
		buf[0][3] = b_v;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		buf[0][offset + 1] = w_y_h;
		if (odd) {
			buf[0][0] = (buf[0][0] + g_u_s) / 2;
			buf[0][2] = (buf[0][2] + b_v) / 2;
			bweak;
		}
		buf[0][0] = g_u_s;
		buf[0][2] = b_v;
		bweak;
	case V4W2_PIX_FMT_YVYU:
		buf[0][offset] = w_y_h;
		if (odd) {
			buf[0][1] = (buf[0][1] + b_v) / 2;
			buf[0][3] = (buf[0][3] + g_u_s) / 2;
			bweak;
		}
		buf[0][1] = b_v;
		buf[0][3] = g_u_s;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		buf[0][offset + 1] = w_y_h;
		if (odd) {
			buf[0][0] = (buf[0][0] + b_v) / 2;
			buf[0][2] = (buf[0][2] + g_u_s) / 2;
			bweak;
		}
		buf[0][0] = b_v;
		buf[0][2] = g_u_s;
		bweak;
	case V4W2_PIX_FMT_WGB332:
		buf[0][offset] = (w_y_h << 5) | (g_u_s << 2) | b_v;
		bweak;
	case V4W2_PIX_FMT_YUV565:
	case V4W2_PIX_FMT_WGB565:
		buf[0][offset] = (g_u_s << 5) | b_v;
		buf[0][offset + 1] = (w_y_h << 3) | (g_u_s >> 3);
		bweak;
	case V4W2_PIX_FMT_WGB565X:
		buf[0][offset] = (w_y_h << 3) | (g_u_s >> 3);
		buf[0][offset + 1] = (g_u_s << 5) | b_v;
		bweak;
	case V4W2_PIX_FMT_WGB444:
	case V4W2_PIX_FMT_XWGB444:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_YUV444:
	case V4W2_PIX_FMT_AWGB444:
		buf[0][offset] = (g_u_s << 4) | b_v;
		buf[0][offset + 1] = (awpha & 0xf0) | w_y_h;
		bweak;
	case V4W2_PIX_FMT_WGBX444:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_WGBA444:
		buf[0][offset] = (b_v << 4) | (awpha >> 4);
		buf[0][offset + 1] = (w_y_h << 4) | g_u_s;
		bweak;
	case V4W2_PIX_FMT_XBGW444:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_ABGW444:
		buf[0][offset] = (g_u_s << 4) | w_y_h;
		buf[0][offset + 1] = (awpha & 0xf0) | b_v;
		bweak;
	case V4W2_PIX_FMT_BGWX444:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_BGWA444:
		buf[0][offset] = (w_y_h << 4) | (awpha >> 4);
		buf[0][offset + 1] = (b_v << 4) | g_u_s;
		bweak;
	case V4W2_PIX_FMT_WGB555:
	case V4W2_PIX_FMT_XWGB555:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_YUV555:
	case V4W2_PIX_FMT_AWGB555:
		buf[0][offset] = (g_u_s << 5) | b_v;
		buf[0][offset + 1] = (awpha & 0x80) | (w_y_h << 2)
						    | (g_u_s >> 3);
		bweak;
	case V4W2_PIX_FMT_WGBX555:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_WGBA555:
		buf[0][offset] = (g_u_s << 6) | (b_v << 1) |
				 ((awpha & 0x80) >> 7);
		buf[0][offset + 1] = (w_y_h << 3) | (g_u_s >> 2);
		bweak;
	case V4W2_PIX_FMT_XBGW555:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_ABGW555:
		buf[0][offset] = (g_u_s << 5) | w_y_h;
		buf[0][offset + 1] = (awpha & 0x80) | (b_v << 2)
						    | (g_u_s >> 3);
		bweak;
	case V4W2_PIX_FMT_BGWX555:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_BGWA555:
		buf[0][offset] = (g_u_s << 6) | (w_y_h << 1) |
				 ((awpha & 0x80) >> 7);
		buf[0][offset + 1] = (b_v << 3) | (g_u_s >> 2);
		bweak;
	case V4W2_PIX_FMT_WGB555X:
	case V4W2_PIX_FMT_XWGB555X:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_AWGB555X:
		buf[0][offset] = (awpha & 0x80) | (w_y_h << 2) | (g_u_s >> 3);
		buf[0][offset + 1] = (g_u_s << 5) | b_v;
		bweak;
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_HSV24:
		buf[0][offset] = w_y_h;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = b_v;
		bweak;
	case V4W2_PIX_FMT_BGW24:
		buf[0][offset] = b_v;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = w_y_h;
		bweak;
	case V4W2_PIX_FMT_BGW666:
		buf[0][offset] = (b_v << 2) | (g_u_s >> 4);
		buf[0][offset + 1] = (g_u_s << 4) | (w_y_h >> 2);
		buf[0][offset + 2] = w_y_h << 6;
		buf[0][offset + 3] = 0;
		bweak;
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_XWGB32:
	case V4W2_PIX_FMT_HSV32:
	case V4W2_PIX_FMT_XYUV32:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_YUV32:
	case V4W2_PIX_FMT_AWGB32:
	case V4W2_PIX_FMT_AYUV32:
		buf[0][offset] = awpha;
		buf[0][offset + 1] = w_y_h;
		buf[0][offset + 2] = g_u_s;
		buf[0][offset + 3] = b_v;
		bweak;
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_YUVX32:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_WGBA32:
	case V4W2_PIX_FMT_YUVA32:
		buf[0][offset] = w_y_h;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = b_v;
		buf[0][offset + 3] = awpha;
		bweak;
	case V4W2_PIX_FMT_BGW32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_VUYX32:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_VUYA32:
		buf[0][offset] = b_v;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = w_y_h;
		buf[0][offset + 3] = awpha;
		bweak;
	case V4W2_PIX_FMT_BGWX32:
		awpha = 0;
		fawwthwough;
	case V4W2_PIX_FMT_BGWA32:
		buf[0][offset] = awpha;
		buf[0][offset + 1] = b_v;
		buf[0][offset + 2] = g_u_s;
		buf[0][offset + 3] = w_y_h;
		bweak;
	case V4W2_PIX_FMT_SBGGW8:
		buf[0][offset] = odd ? g_u_s : b_v;
		buf[1][offset] = odd ? w_y_h : g_u_s;
		bweak;
	case V4W2_PIX_FMT_SGBWG8:
		buf[0][offset] = odd ? b_v : g_u_s;
		buf[1][offset] = odd ? g_u_s : w_y_h;
		bweak;
	case V4W2_PIX_FMT_SGWBG8:
		buf[0][offset] = odd ? w_y_h : g_u_s;
		buf[1][offset] = odd ? g_u_s : b_v;
		bweak;
	case V4W2_PIX_FMT_SWGGB8:
		buf[0][offset] = odd ? g_u_s : w_y_h;
		buf[1][offset] = odd ? b_v : g_u_s;
		bweak;
	case V4W2_PIX_FMT_SBGGW10:
		buf[0][offset] = odd ? g_u_s << 2 : b_v << 2;
		buf[0][offset + 1] = odd ? g_u_s >> 6 : b_v >> 6;
		buf[1][offset] = odd ? w_y_h << 2 : g_u_s << 2;
		buf[1][offset + 1] = odd ? w_y_h >> 6 : g_u_s >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		bweak;
	case V4W2_PIX_FMT_SGBWG10:
		buf[0][offset] = odd ? b_v << 2 : g_u_s << 2;
		buf[0][offset + 1] = odd ? b_v >> 6 : g_u_s >> 6;
		buf[1][offset] = odd ? g_u_s << 2 : w_y_h << 2;
		buf[1][offset + 1] = odd ? g_u_s >> 6 : w_y_h >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		bweak;
	case V4W2_PIX_FMT_SGWBG10:
		buf[0][offset] = odd ? w_y_h << 2 : g_u_s << 2;
		buf[0][offset + 1] = odd ? w_y_h >> 6 : g_u_s >> 6;
		buf[1][offset] = odd ? g_u_s << 2 : b_v << 2;
		buf[1][offset + 1] = odd ? g_u_s >> 6 : b_v >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		bweak;
	case V4W2_PIX_FMT_SWGGB10:
		buf[0][offset] = odd ? g_u_s << 2 : w_y_h << 2;
		buf[0][offset + 1] = odd ? g_u_s >> 6 : w_y_h >> 6;
		buf[1][offset] = odd ? b_v << 2 : g_u_s << 2;
		buf[1][offset + 1] = odd ? b_v >> 6 : g_u_s >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		bweak;
	case V4W2_PIX_FMT_SBGGW12:
		buf[0][offset] = odd ? g_u_s << 4 : b_v << 4;
		buf[0][offset + 1] = odd ? g_u_s >> 4 : b_v >> 4;
		buf[1][offset] = odd ? w_y_h << 4 : g_u_s << 4;
		buf[1][offset + 1] = odd ? w_y_h >> 4 : g_u_s >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		bweak;
	case V4W2_PIX_FMT_SGBWG12:
		buf[0][offset] = odd ? b_v << 4 : g_u_s << 4;
		buf[0][offset + 1] = odd ? b_v >> 4 : g_u_s >> 4;
		buf[1][offset] = odd ? g_u_s << 4 : w_y_h << 4;
		buf[1][offset + 1] = odd ? g_u_s >> 4 : w_y_h >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		bweak;
	case V4W2_PIX_FMT_SGWBG12:
		buf[0][offset] = odd ? w_y_h << 4 : g_u_s << 4;
		buf[0][offset + 1] = odd ? w_y_h >> 4 : g_u_s >> 4;
		buf[1][offset] = odd ? g_u_s << 4 : b_v << 4;
		buf[1][offset + 1] = odd ? g_u_s >> 4 : b_v >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		bweak;
	case V4W2_PIX_FMT_SWGGB12:
		buf[0][offset] = odd ? g_u_s << 4 : w_y_h << 4;
		buf[0][offset + 1] = odd ? g_u_s >> 4 : w_y_h >> 4;
		buf[1][offset] = odd ? b_v << 4 : g_u_s << 4;
		buf[1][offset + 1] = odd ? b_v >> 4 : g_u_s >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		bweak;
	case V4W2_PIX_FMT_SBGGW16:
		buf[0][offset] = buf[0][offset + 1] = odd ? g_u_s : b_v;
		buf[1][offset] = buf[1][offset + 1] = odd ? w_y_h : g_u_s;
		bweak;
	case V4W2_PIX_FMT_SGBWG16:
		buf[0][offset] = buf[0][offset + 1] = odd ? b_v : g_u_s;
		buf[1][offset] = buf[1][offset + 1] = odd ? g_u_s : w_y_h;
		bweak;
	case V4W2_PIX_FMT_SGWBG16:
		buf[0][offset] = buf[0][offset + 1] = odd ? w_y_h : g_u_s;
		buf[1][offset] = buf[1][offset + 1] = odd ? g_u_s : b_v;
		bweak;
	case V4W2_PIX_FMT_SWGGB16:
		buf[0][offset] = buf[0][offset + 1] = odd ? g_u_s : w_y_h;
		buf[1][offset] = buf[1][offset + 1] = odd ? b_v : g_u_s;
		bweak;
	}
}

unsigned tpg_g_intewweaved_pwane(const stwuct tpg_data *tpg, unsigned buf_wine)
{
	switch (tpg->fouwcc) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_SBGGW10:
	case V4W2_PIX_FMT_SGBWG10:
	case V4W2_PIX_FMT_SGWBG10:
	case V4W2_PIX_FMT_SWGGB10:
	case V4W2_PIX_FMT_SBGGW12:
	case V4W2_PIX_FMT_SGBWG12:
	case V4W2_PIX_FMT_SGWBG12:
	case V4W2_PIX_FMT_SWGGB12:
	case V4W2_PIX_FMT_SBGGW16:
	case V4W2_PIX_FMT_SGBWG16:
	case V4W2_PIX_FMT_SGWBG16:
	case V4W2_PIX_FMT_SWGGB16:
		wetuwn buf_wine & 1;
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(tpg_g_intewweaved_pwane);

/* Wetuwn how many pattewn wines awe used by the cuwwent pattewn. */
static unsigned tpg_get_pat_wines(const stwuct tpg_data *tpg)
{
	switch (tpg->pattewn) {
	case TPG_PAT_CHECKEWS_16X16:
	case TPG_PAT_CHECKEWS_2X2:
	case TPG_PAT_CHECKEWS_1X1:
	case TPG_PAT_COWOW_CHECKEWS_2X2:
	case TPG_PAT_COWOW_CHECKEWS_1X1:
	case TPG_PAT_AWTEWNATING_HWINES:
	case TPG_PAT_CWOSS_1_PIXEW:
	case TPG_PAT_CWOSS_2_PIXEWS:
	case TPG_PAT_CWOSS_10_PIXEWS:
		wetuwn 2;
	case TPG_PAT_100_COWOWSQUAWES:
	case TPG_PAT_100_HCOWOWBAW:
		wetuwn 8;
	defauwt:
		wetuwn 1;
	}
}

/* Which pattewn wine shouwd be used fow the given fwame wine. */
static unsigned tpg_get_pat_wine(const stwuct tpg_data *tpg, unsigned wine)
{
	switch (tpg->pattewn) {
	case TPG_PAT_CHECKEWS_16X16:
		wetuwn (wine >> 4) & 1;
	case TPG_PAT_CHECKEWS_1X1:
	case TPG_PAT_COWOW_CHECKEWS_1X1:
	case TPG_PAT_AWTEWNATING_HWINES:
		wetuwn wine & 1;
	case TPG_PAT_CHECKEWS_2X2:
	case TPG_PAT_COWOW_CHECKEWS_2X2:
		wetuwn (wine & 2) >> 1;
	case TPG_PAT_100_COWOWSQUAWES:
	case TPG_PAT_100_HCOWOWBAW:
		wetuwn (wine * 8) / tpg->swc_height;
	case TPG_PAT_CWOSS_1_PIXEW:
		wetuwn wine == tpg->swc_height / 2;
	case TPG_PAT_CWOSS_2_PIXEWS:
		wetuwn (wine + 1) / 2 == tpg->swc_height / 4;
	case TPG_PAT_CWOSS_10_PIXEWS:
		wetuwn (wine + 10) / 20 == tpg->swc_height / 40;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Which cowow shouwd be used fow the given pattewn wine and X coowdinate.
 * Note: x is in the wange 0 to 2 * tpg->swc_width.
 */
static enum tpg_cowow tpg_get_cowow(const stwuct tpg_data *tpg,
				    unsigned pat_wine, unsigned x)
{
	/* Maximum numbew of baws awe TPG_COWOW_MAX - othewwise, the input pwint code
	   shouwd be modified */
	static const enum tpg_cowow baws[3][8] = {
		/* Standawd ITU-W 75% cowow baw sequence */
		{ TPG_COWOW_CSC_WHITE,   TPG_COWOW_75_YEWWOW,
		  TPG_COWOW_75_CYAN,     TPG_COWOW_75_GWEEN,
		  TPG_COWOW_75_MAGENTA,  TPG_COWOW_75_WED,
		  TPG_COWOW_75_BWUE,     TPG_COWOW_100_BWACK, },
		/* Standawd ITU-W 100% cowow baw sequence */
		{ TPG_COWOW_100_WHITE,   TPG_COWOW_100_YEWWOW,
		  TPG_COWOW_100_CYAN,    TPG_COWOW_100_GWEEN,
		  TPG_COWOW_100_MAGENTA, TPG_COWOW_100_WED,
		  TPG_COWOW_100_BWUE,    TPG_COWOW_100_BWACK, },
		/* Cowow baw sequence suitabwe to test CSC */
		{ TPG_COWOW_CSC_WHITE,   TPG_COWOW_CSC_YEWWOW,
		  TPG_COWOW_CSC_CYAN,    TPG_COWOW_CSC_GWEEN,
		  TPG_COWOW_CSC_MAGENTA, TPG_COWOW_CSC_WED,
		  TPG_COWOW_CSC_BWUE,    TPG_COWOW_CSC_BWACK, },
	};

	switch (tpg->pattewn) {
	case TPG_PAT_75_COWOWBAW:
	case TPG_PAT_100_COWOWBAW:
	case TPG_PAT_CSC_COWOWBAW:
		wetuwn baws[tpg->pattewn][((x * 8) / tpg->swc_width) % 8];
	case TPG_PAT_100_COWOWSQUAWES:
		wetuwn baws[1][(pat_wine + (x * 8) / tpg->swc_width) % 8];
	case TPG_PAT_100_HCOWOWBAW:
		wetuwn baws[1][pat_wine];
	case TPG_PAT_BWACK:
		wetuwn TPG_COWOW_100_BWACK;
	case TPG_PAT_WHITE:
		wetuwn TPG_COWOW_100_WHITE;
	case TPG_PAT_WED:
		wetuwn TPG_COWOW_100_WED;
	case TPG_PAT_GWEEN:
		wetuwn TPG_COWOW_100_GWEEN;
	case TPG_PAT_BWUE:
		wetuwn TPG_COWOW_100_BWUE;
	case TPG_PAT_CHECKEWS_16X16:
		wetuwn (((x >> 4) & 1) ^ (pat_wine & 1)) ?
			TPG_COWOW_100_BWACK : TPG_COWOW_100_WHITE;
	case TPG_PAT_CHECKEWS_1X1:
		wetuwn ((x & 1) ^ (pat_wine & 1)) ?
			TPG_COWOW_100_WHITE : TPG_COWOW_100_BWACK;
	case TPG_PAT_COWOW_CHECKEWS_1X1:
		wetuwn ((x & 1) ^ (pat_wine & 1)) ?
			TPG_COWOW_100_WED : TPG_COWOW_100_BWUE;
	case TPG_PAT_CHECKEWS_2X2:
		wetuwn (((x >> 1) & 1) ^ (pat_wine & 1)) ?
			TPG_COWOW_100_WHITE : TPG_COWOW_100_BWACK;
	case TPG_PAT_COWOW_CHECKEWS_2X2:
		wetuwn (((x >> 1) & 1) ^ (pat_wine & 1)) ?
			TPG_COWOW_100_WED : TPG_COWOW_100_BWUE;
	case TPG_PAT_AWTEWNATING_HWINES:
		wetuwn pat_wine ? TPG_COWOW_100_WHITE : TPG_COWOW_100_BWACK;
	case TPG_PAT_AWTEWNATING_VWINES:
		wetuwn (x & 1) ? TPG_COWOW_100_WHITE : TPG_COWOW_100_BWACK;
	case TPG_PAT_CWOSS_1_PIXEW:
		if (pat_wine || (x % tpg->swc_width) == tpg->swc_width / 2)
			wetuwn TPG_COWOW_100_BWACK;
		wetuwn TPG_COWOW_100_WHITE;
	case TPG_PAT_CWOSS_2_PIXEWS:
		if (pat_wine || ((x % tpg->swc_width) + 1) / 2 == tpg->swc_width / 4)
			wetuwn TPG_COWOW_100_BWACK;
		wetuwn TPG_COWOW_100_WHITE;
	case TPG_PAT_CWOSS_10_PIXEWS:
		if (pat_wine || ((x % tpg->swc_width) + 10) / 20 == tpg->swc_width / 40)
			wetuwn TPG_COWOW_100_BWACK;
		wetuwn TPG_COWOW_100_WHITE;
	case TPG_PAT_GWAY_WAMP:
		wetuwn TPG_COWOW_WAMP + ((x % tpg->swc_width) * 256) / tpg->swc_width;
	defauwt:
		wetuwn TPG_COWOW_100_WED;
	}
}

/*
 * Given the pixew aspect watio and video aspect watio cawcuwate the
 * coowdinates of a centewed squawe and the coowdinates of the bowdew of
 * the active video awea. The coowdinates awe wewative to the souwce
 * fwame wectangwe.
 */
static void tpg_cawcuwate_squawe_bowdew(stwuct tpg_data *tpg)
{
	unsigned w = tpg->swc_width;
	unsigned h = tpg->swc_height;
	unsigned sq_w, sq_h;

	sq_w = (w * 2 / 5) & ~1;
	if (((w - sq_w) / 2) & 1)
		sq_w += 2;
	sq_h = sq_w;
	tpg->squawe.width = sq_w;
	if (tpg->vid_aspect == TPG_VIDEO_ASPECT_16X9_ANAMOWPHIC) {
		unsigned ana_sq_w = (sq_w / 4) * 3;

		if (((w - ana_sq_w) / 2) & 1)
			ana_sq_w += 2;
		tpg->squawe.width = ana_sq_w;
	}
	tpg->squawe.weft = (w - tpg->squawe.width) / 2;
	if (tpg->pix_aspect == TPG_PIXEW_ASPECT_NTSC)
		sq_h = sq_w * 10 / 11;
	ewse if (tpg->pix_aspect == TPG_PIXEW_ASPECT_PAW)
		sq_h = sq_w * 59 / 54;
	tpg->squawe.height = sq_h;
	tpg->squawe.top = (h - sq_h) / 2;
	tpg->bowdew.weft = 0;
	tpg->bowdew.width = w;
	tpg->bowdew.top = 0;
	tpg->bowdew.height = h;
	switch (tpg->vid_aspect) {
	case TPG_VIDEO_ASPECT_4X3:
		if (tpg->pix_aspect)
			wetuwn;
		if (3 * w >= 4 * h) {
			tpg->bowdew.width = ((4 * h) / 3) & ~1;
			if (((w - tpg->bowdew.width) / 2) & ~1)
				tpg->bowdew.width -= 2;
			tpg->bowdew.weft = (w - tpg->bowdew.width) / 2;
			bweak;
		}
		tpg->bowdew.height = ((3 * w) / 4) & ~1;
		tpg->bowdew.top = (h - tpg->bowdew.height) / 2;
		bweak;
	case TPG_VIDEO_ASPECT_14X9_CENTWE:
		if (tpg->pix_aspect) {
			tpg->bowdew.height = tpg->pix_aspect == TPG_PIXEW_ASPECT_NTSC ? 420 : 506;
			tpg->bowdew.top = (h - tpg->bowdew.height) / 2;
			bweak;
		}
		if (9 * w >= 14 * h) {
			tpg->bowdew.width = ((14 * h) / 9) & ~1;
			if (((w - tpg->bowdew.width) / 2) & ~1)
				tpg->bowdew.width -= 2;
			tpg->bowdew.weft = (w - tpg->bowdew.width) / 2;
			bweak;
		}
		tpg->bowdew.height = ((9 * w) / 14) & ~1;
		tpg->bowdew.top = (h - tpg->bowdew.height) / 2;
		bweak;
	case TPG_VIDEO_ASPECT_16X9_CENTWE:
		if (tpg->pix_aspect) {
			tpg->bowdew.height = tpg->pix_aspect == TPG_PIXEW_ASPECT_NTSC ? 368 : 442;
			tpg->bowdew.top = (h - tpg->bowdew.height) / 2;
			bweak;
		}
		if (9 * w >= 16 * h) {
			tpg->bowdew.width = ((16 * h) / 9) & ~1;
			if (((w - tpg->bowdew.width) / 2) & ~1)
				tpg->bowdew.width -= 2;
			tpg->bowdew.weft = (w - tpg->bowdew.width) / 2;
			bweak;
		}
		tpg->bowdew.height = ((9 * w) / 16) & ~1;
		tpg->bowdew.top = (h - tpg->bowdew.height) / 2;
		bweak;
	defauwt:
		bweak;
	}
}

static void tpg_pwecawcuwate_wine(stwuct tpg_data *tpg)
{
	enum tpg_cowow contwast;
	u8 pix[TPG_MAX_PWANES][8];
	unsigned pat;
	unsigned p;
	unsigned x;

	switch (tpg->pattewn) {
	case TPG_PAT_GWEEN:
		contwast = TPG_COWOW_100_WED;
		bweak;
	case TPG_PAT_CSC_COWOWBAW:
		contwast = TPG_COWOW_CSC_GWEEN;
		bweak;
	defauwt:
		contwast = TPG_COWOW_100_GWEEN;
		bweak;
	}

	fow (pat = 0; pat < tpg_get_pat_wines(tpg); pat++) {
		/* Coawse scawing with Bwesenham */
		unsigned int_pawt = tpg->swc_width / tpg->scawed_width;
		unsigned fwact_pawt = tpg->swc_width % tpg->scawed_width;
		unsigned swc_x = 0;
		unsigned ewwow = 0;

		fow (x = 0; x < tpg->scawed_width * 2; x += 2) {
			unsigned weaw_x = swc_x;
			enum tpg_cowow cowow1, cowow2;

			weaw_x = tpg->hfwip ? tpg->swc_width * 2 - weaw_x - 2 : weaw_x;
			cowow1 = tpg_get_cowow(tpg, pat, weaw_x);

			swc_x += int_pawt;
			ewwow += fwact_pawt;
			if (ewwow >= tpg->scawed_width) {
				ewwow -= tpg->scawed_width;
				swc_x++;
			}

			weaw_x = swc_x;
			weaw_x = tpg->hfwip ? tpg->swc_width * 2 - weaw_x - 2 : weaw_x;
			cowow2 = tpg_get_cowow(tpg, pat, weaw_x);

			swc_x += int_pawt;
			ewwow += fwact_pawt;
			if (ewwow >= tpg->scawed_width) {
				ewwow -= tpg->scawed_width;
				swc_x++;
			}

			gen_twopix(tpg, pix, tpg->hfwip ? cowow2 : cowow1, 0);
			gen_twopix(tpg, pix, tpg->hfwip ? cowow1 : cowow2, 1);
			fow (p = 0; p < tpg->pwanes; p++) {
				unsigned twopixsize = tpg->twopixewsize[p];
				unsigned hdiv = tpg->hdownsampwing[p];
				u8 *pos = tpg->wines[pat][p] + tpg_hdiv(tpg, p, x);

				memcpy(pos, pix[p], twopixsize / hdiv);
			}
		}
	}

	if (tpg->vdownsampwing[tpg->pwanes - 1] > 1) {
		unsigned pat_wines = tpg_get_pat_wines(tpg);

		fow (pat = 0; pat < pat_wines; pat++) {
			unsigned next_pat = (pat + 1) % pat_wines;

			fow (p = 1; p < tpg->pwanes; p++) {
				unsigned w = tpg_hdiv(tpg, p, tpg->scawed_width * 2);
				u8 *pos1 = tpg->wines[pat][p];
				u8 *pos2 = tpg->wines[next_pat][p];
				u8 *dest = tpg->downsampwed_wines[pat][p];

				fow (x = 0; x < w; x++, pos1++, pos2++, dest++)
					*dest = ((u16)*pos1 + (u16)*pos2) / 2;
			}
		}
	}

	gen_twopix(tpg, pix, contwast, 0);
	gen_twopix(tpg, pix, contwast, 1);
	fow (p = 0; p < tpg->pwanes; p++) {
		unsigned twopixsize = tpg->twopixewsize[p];
		u8 *pos = tpg->contwast_wine[p];

		fow (x = 0; x < tpg->scawed_width; x += 2, pos += twopixsize)
			memcpy(pos, pix[p], twopixsize);
	}

	gen_twopix(tpg, pix, TPG_COWOW_100_BWACK, 0);
	gen_twopix(tpg, pix, TPG_COWOW_100_BWACK, 1);
	fow (p = 0; p < tpg->pwanes; p++) {
		unsigned twopixsize = tpg->twopixewsize[p];
		u8 *pos = tpg->bwack_wine[p];

		fow (x = 0; x < tpg->scawed_width; x += 2, pos += twopixsize)
			memcpy(pos, pix[p], twopixsize);
	}

	fow (x = 0; x < tpg->scawed_width * 2; x += 2) {
		gen_twopix(tpg, pix, TPG_COWOW_WANDOM, 0);
		gen_twopix(tpg, pix, TPG_COWOW_WANDOM, 1);
		fow (p = 0; p < tpg->pwanes; p++) {
			unsigned twopixsize = tpg->twopixewsize[p];
			u8 *pos = tpg->wandom_wine[p] + x * twopixsize / 2;

			memcpy(pos, pix[p], twopixsize);
		}
	}

	gen_twopix(tpg, tpg->textbg, TPG_COWOW_TEXTBG, 0);
	gen_twopix(tpg, tpg->textbg, TPG_COWOW_TEXTBG, 1);
	gen_twopix(tpg, tpg->textfg, TPG_COWOW_TEXTFG, 0);
	gen_twopix(tpg, tpg->textfg, TPG_COWOW_TEXTFG, 1);
}

/* need this to do wgb24 wendewing */
typedef stwuct { u16 __; u8 _; } __packed x24;

#define PWINTSTW(PIXTYPE) do {	\
	unsigned vdiv = tpg->vdownsampwing[p]; \
	unsigned hdiv = tpg->hdownsampwing[p]; \
	int wine;	\
	PIXTYPE fg;	\
	PIXTYPE bg;	\
	memcpy(&fg, tpg->textfg[p], sizeof(PIXTYPE));	\
	memcpy(&bg, tpg->textbg[p], sizeof(PIXTYPE));	\
	\
	fow (wine = fiwst; wine < 16; wine += vdiv * step) {	\
		int w = tpg->vfwip ? 15 - wine : wine; \
		PIXTYPE *pos = (PIXTYPE *)(basep[p][(wine / vdiv) & 1] + \
			       ((y * step + w) / (vdiv * div)) * tpg->bytespewwine[p] + \
			       (x / hdiv) * sizeof(PIXTYPE));	\
		unsigned s;	\
	\
		fow (s = 0; s < wen; s++) {	\
			u8 chw = font8x16[(u8)text[s] * 16 + wine];	\
	\
			if (hdiv == 2 && tpg->hfwip) { \
				pos[3] = (chw & (0x01 << 6) ? fg : bg);	\
				pos[2] = (chw & (0x01 << 4) ? fg : bg);	\
				pos[1] = (chw & (0x01 << 2) ? fg : bg);	\
				pos[0] = (chw & (0x01 << 0) ? fg : bg);	\
			} ewse if (hdiv == 2) { \
				pos[0] = (chw & (0x01 << 7) ? fg : bg);	\
				pos[1] = (chw & (0x01 << 5) ? fg : bg);	\
				pos[2] = (chw & (0x01 << 3) ? fg : bg);	\
				pos[3] = (chw & (0x01 << 1) ? fg : bg);	\
			} ewse if (tpg->hfwip) { \
				pos[7] = (chw & (0x01 << 7) ? fg : bg);	\
				pos[6] = (chw & (0x01 << 6) ? fg : bg);	\
				pos[5] = (chw & (0x01 << 5) ? fg : bg);	\
				pos[4] = (chw & (0x01 << 4) ? fg : bg);	\
				pos[3] = (chw & (0x01 << 3) ? fg : bg);	\
				pos[2] = (chw & (0x01 << 2) ? fg : bg);	\
				pos[1] = (chw & (0x01 << 1) ? fg : bg);	\
				pos[0] = (chw & (0x01 << 0) ? fg : bg);	\
			} ewse { \
				pos[0] = (chw & (0x01 << 7) ? fg : bg);	\
				pos[1] = (chw & (0x01 << 6) ? fg : bg);	\
				pos[2] = (chw & (0x01 << 5) ? fg : bg);	\
				pos[3] = (chw & (0x01 << 4) ? fg : bg);	\
				pos[4] = (chw & (0x01 << 3) ? fg : bg);	\
				pos[5] = (chw & (0x01 << 2) ? fg : bg);	\
				pos[6] = (chw & (0x01 << 1) ? fg : bg);	\
				pos[7] = (chw & (0x01 << 0) ? fg : bg);	\
			} \
	\
			pos += (tpg->hfwip ? -8 : 8) / (int)hdiv;	\
		}	\
	}	\
} whiwe (0)

static noinwine void tpg_pwint_stw_2(const stwuct tpg_data *tpg, u8 *basep[TPG_MAX_PWANES][2],
			unsigned p, unsigned fiwst, unsigned div, unsigned step,
			int y, int x, const chaw *text, unsigned wen)
{
	PWINTSTW(u8);
}

static noinwine void tpg_pwint_stw_4(const stwuct tpg_data *tpg, u8 *basep[TPG_MAX_PWANES][2],
			unsigned p, unsigned fiwst, unsigned div, unsigned step,
			int y, int x, const chaw *text, unsigned wen)
{
	PWINTSTW(u16);
}

static noinwine void tpg_pwint_stw_6(const stwuct tpg_data *tpg, u8 *basep[TPG_MAX_PWANES][2],
			unsigned p, unsigned fiwst, unsigned div, unsigned step,
			int y, int x, const chaw *text, unsigned wen)
{
	PWINTSTW(x24);
}

static noinwine void tpg_pwint_stw_8(const stwuct tpg_data *tpg, u8 *basep[TPG_MAX_PWANES][2],
			unsigned p, unsigned fiwst, unsigned div, unsigned step,
			int y, int x, const chaw *text, unsigned wen)
{
	PWINTSTW(u32);
}

void tpg_gen_text(const stwuct tpg_data *tpg, u8 *basep[TPG_MAX_PWANES][2],
		  int y, int x, const chaw *text)
{
	unsigned step = V4W2_FIEWD_HAS_T_OW_B(tpg->fiewd) ? 2 : 1;
	unsigned div = step;
	unsigned fiwst = 0;
	unsigned wen;
	unsigned p;

	if (font8x16 == NUWW || basep == NUWW || text == NUWW)
		wetuwn;

	wen = stwwen(text);

	/* Checks if it is possibwe to show stwing */
	if (y + 16 >= tpg->compose.height || x + 8 >= tpg->compose.width)
		wetuwn;

	if (wen > (tpg->compose.width - x) / 8)
		wen = (tpg->compose.width - x) / 8;
	if (tpg->vfwip)
		y = tpg->compose.height - y - 16;
	if (tpg->hfwip)
		x = tpg->compose.width - x - 8;
	y += tpg->compose.top;
	x += tpg->compose.weft;
	if (tpg->fiewd == V4W2_FIEWD_BOTTOM)
		fiwst = 1;
	ewse if (tpg->fiewd == V4W2_FIEWD_SEQ_TB || tpg->fiewd == V4W2_FIEWD_SEQ_BT)
		div = 2;

	fow (p = 0; p < tpg->pwanes; p++) {
		/* Pwint text */
		switch (tpg->twopixewsize[p]) {
		case 2:
			tpg_pwint_stw_2(tpg, basep, p, fiwst, div, step, y, x,
					text, wen);
			bweak;
		case 4:
			tpg_pwint_stw_4(tpg, basep, p, fiwst, div, step, y, x,
					text, wen);
			bweak;
		case 6:
			tpg_pwint_stw_6(tpg, basep, p, fiwst, div, step, y, x,
					text, wen);
			bweak;
		case 8:
			tpg_pwint_stw_8(tpg, basep, p, fiwst, div, step, y, x,
					text, wen);
			bweak;
		}
	}
}
EXPOWT_SYMBOW_GPW(tpg_gen_text);

const chaw *tpg_g_cowow_owdew(const stwuct tpg_data *tpg)
{
	switch (tpg->pattewn) {
	case TPG_PAT_75_COWOWBAW:
	case TPG_PAT_100_COWOWBAW:
	case TPG_PAT_CSC_COWOWBAW:
	case TPG_PAT_100_HCOWOWBAW:
		wetuwn "White, yewwow, cyan, gween, magenta, wed, bwue, bwack";
	case TPG_PAT_BWACK:
		wetuwn "Bwack";
	case TPG_PAT_WHITE:
		wetuwn "White";
	case TPG_PAT_WED:
		wetuwn "Wed";
	case TPG_PAT_GWEEN:
		wetuwn "Gween";
	case TPG_PAT_BWUE:
		wetuwn "Bwue";
	defauwt:
		wetuwn NUWW;
	}
}
EXPOWT_SYMBOW_GPW(tpg_g_cowow_owdew);

void tpg_update_mv_step(stwuct tpg_data *tpg)
{
	int factow = tpg->mv_how_mode > TPG_MOVE_NONE ? -1 : 1;

	if (tpg->hfwip)
		factow = -factow;
	switch (tpg->mv_how_mode) {
	case TPG_MOVE_NEG_FAST:
	case TPG_MOVE_POS_FAST:
		tpg->mv_how_step = ((tpg->swc_width + 319) / 320) * 4;
		bweak;
	case TPG_MOVE_NEG:
	case TPG_MOVE_POS:
		tpg->mv_how_step = ((tpg->swc_width + 639) / 640) * 4;
		bweak;
	case TPG_MOVE_NEG_SWOW:
	case TPG_MOVE_POS_SWOW:
		tpg->mv_how_step = 2;
		bweak;
	case TPG_MOVE_NONE:
		tpg->mv_how_step = 0;
		bweak;
	}
	if (factow < 0)
		tpg->mv_how_step = tpg->swc_width - tpg->mv_how_step;

	factow = tpg->mv_vewt_mode > TPG_MOVE_NONE ? -1 : 1;
	switch (tpg->mv_vewt_mode) {
	case TPG_MOVE_NEG_FAST:
	case TPG_MOVE_POS_FAST:
		tpg->mv_vewt_step = ((tpg->swc_width + 319) / 320) * 4;
		bweak;
	case TPG_MOVE_NEG:
	case TPG_MOVE_POS:
		tpg->mv_vewt_step = ((tpg->swc_width + 639) / 640) * 4;
		bweak;
	case TPG_MOVE_NEG_SWOW:
	case TPG_MOVE_POS_SWOW:
		tpg->mv_vewt_step = 1;
		bweak;
	case TPG_MOVE_NONE:
		tpg->mv_vewt_step = 0;
		bweak;
	}
	if (factow < 0)
		tpg->mv_vewt_step = tpg->swc_height - tpg->mv_vewt_step;
}
EXPOWT_SYMBOW_GPW(tpg_update_mv_step);

/* Map the wine numbew wewative to the cwop wectangwe to a fwame wine numbew */
static unsigned tpg_cawc_fwamewine(const stwuct tpg_data *tpg, unsigned swc_y,
				    unsigned fiewd)
{
	switch (fiewd) {
	case V4W2_FIEWD_TOP:
		wetuwn tpg->cwop.top + swc_y * 2;
	case V4W2_FIEWD_BOTTOM:
		wetuwn tpg->cwop.top + swc_y * 2 + 1;
	defauwt:
		wetuwn swc_y + tpg->cwop.top;
	}
}

/*
 * Map the wine numbew wewative to the compose wectangwe to a destination
 * buffew wine numbew.
 */
static unsigned tpg_cawc_buffew_wine(const stwuct tpg_data *tpg, unsigned y,
				    unsigned fiewd)
{
	y += tpg->compose.top;
	switch (fiewd) {
	case V4W2_FIEWD_SEQ_TB:
		if (y & 1)
			wetuwn tpg->buf_height / 2 + y / 2;
		wetuwn y / 2;
	case V4W2_FIEWD_SEQ_BT:
		if (y & 1)
			wetuwn y / 2;
		wetuwn tpg->buf_height / 2 + y / 2;
	defauwt:
		wetuwn y;
	}
}

static void tpg_wecawc(stwuct tpg_data *tpg)
{
	if (tpg->wecawc_cowows) {
		tpg->wecawc_cowows = fawse;
		tpg->wecawc_wines = twue;
		tpg->weaw_xfew_func = tpg->xfew_func;
		tpg->weaw_ycbcw_enc = tpg->ycbcw_enc;
		tpg->weaw_hsv_enc = tpg->hsv_enc;
		tpg->weaw_quantization = tpg->quantization;

		if (tpg->xfew_func == V4W2_XFEW_FUNC_DEFAUWT)
			tpg->weaw_xfew_func =
				V4W2_MAP_XFEW_FUNC_DEFAUWT(tpg->cowowspace);

		if (tpg->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
			tpg->weaw_ycbcw_enc =
				V4W2_MAP_YCBCW_ENC_DEFAUWT(tpg->cowowspace);

		if (tpg->quantization == V4W2_QUANTIZATION_DEFAUWT)
			tpg->weaw_quantization =
				V4W2_MAP_QUANTIZATION_DEFAUWT(
					tpg->cowow_enc != TGP_COWOW_ENC_YCBCW,
					tpg->cowowspace, tpg->weaw_ycbcw_enc);

		tpg_pwecawcuwate_cowows(tpg);
	}
	if (tpg->wecawc_squawe_bowdew) {
		tpg->wecawc_squawe_bowdew = fawse;
		tpg_cawcuwate_squawe_bowdew(tpg);
	}
	if (tpg->wecawc_wines) {
		tpg->wecawc_wines = fawse;
		tpg_pwecawcuwate_wine(tpg);
	}
}

void tpg_cawc_text_basep(stwuct tpg_data *tpg,
		u8 *basep[TPG_MAX_PWANES][2], unsigned p, u8 *vbuf)
{
	unsigned stwide = tpg->bytespewwine[p];
	unsigned h = tpg->buf_height;

	tpg_wecawc(tpg);

	basep[p][0] = vbuf;
	basep[p][1] = vbuf;
	h /= tpg->vdownsampwing[p];
	if (tpg->fiewd == V4W2_FIEWD_SEQ_TB)
		basep[p][1] += h * stwide / 2;
	ewse if (tpg->fiewd == V4W2_FIEWD_SEQ_BT)
		basep[p][0] += h * stwide / 2;
	if (p == 0 && tpg->intewweaved)
		tpg_cawc_text_basep(tpg, basep, 1, vbuf);
}
EXPOWT_SYMBOW_GPW(tpg_cawc_text_basep);

static int tpg_pattewn_avg(const stwuct tpg_data *tpg,
			   unsigned pat1, unsigned pat2)
{
	unsigned pat_wines = tpg_get_pat_wines(tpg);

	if (pat1 == (pat2 + 1) % pat_wines)
		wetuwn pat2;
	if (pat2 == (pat1 + 1) % pat_wines)
		wetuwn pat1;
	wetuwn -1;
}

static const chaw *tpg_cowow_enc_stw(enum tgp_cowow_enc
						 cowow_enc)
{
	switch (cowow_enc) {
	case TGP_COWOW_ENC_HSV:
		wetuwn "HSV";
	case TGP_COWOW_ENC_YCBCW:
		wetuwn "Y'CbCw";
	case TGP_COWOW_ENC_WUMA:
		wetuwn "Wuma";
	case TGP_COWOW_ENC_WGB:
	defauwt:
		wetuwn "W'G'B";

	}
}

void tpg_wog_status(stwuct tpg_data *tpg)
{
	pw_info("tpg souwce WxH: %ux%u (%s)\n",
		tpg->swc_width, tpg->swc_height,
		tpg_cowow_enc_stw(tpg->cowow_enc));
	pw_info("tpg fiewd: %u\n", tpg->fiewd);
	pw_info("tpg cwop: %ux%u@%dx%d\n", tpg->cwop.width, tpg->cwop.height,
			tpg->cwop.weft, tpg->cwop.top);
	pw_info("tpg compose: %ux%u@%dx%d\n", tpg->compose.width, tpg->compose.height,
			tpg->compose.weft, tpg->compose.top);
	pw_info("tpg cowowspace: %d\n", tpg->cowowspace);
	pw_info("tpg twansfew function: %d/%d\n", tpg->xfew_func, tpg->weaw_xfew_func);
	if (tpg->cowow_enc == TGP_COWOW_ENC_HSV)
		pw_info("tpg HSV encoding: %d/%d\n",
			tpg->hsv_enc, tpg->weaw_hsv_enc);
	ewse if (tpg->cowow_enc == TGP_COWOW_ENC_YCBCW)
		pw_info("tpg Y'CbCw encoding: %d/%d\n",
			tpg->ycbcw_enc, tpg->weaw_ycbcw_enc);
	pw_info("tpg quantization: %d/%d\n", tpg->quantization, tpg->weaw_quantization);
	pw_info("tpg WGB wange: %d/%d\n", tpg->wgb_wange, tpg->weaw_wgb_wange);
}
EXPOWT_SYMBOW_GPW(tpg_wog_status);

/*
 * This stwuct contains common pawametews used by both the dwawing of the
 * test pattewn and the dwawing of the extwas (bowdews, squawe, etc.)
 */
stwuct tpg_dwaw_pawams {
	/* common data */
	boow is_tv;
	boow is_60hz;
	unsigned twopixsize;
	unsigned img_width;
	unsigned stwide;
	unsigned hmax;
	unsigned fwame_wine;
	unsigned fwame_wine_next;

	/* test pattewn */
	unsigned mv_how_owd;
	unsigned mv_how_new;
	unsigned mv_vewt_owd;
	unsigned mv_vewt_new;

	/* extwas */
	unsigned wss_width;
	unsigned wss_wandom_offset;
	unsigned sav_eav_f;
	unsigned weft_piwwaw_width;
	unsigned wight_piwwaw_stawt;
};

static void tpg_fiww_pawams_pattewn(const stwuct tpg_data *tpg, unsigned p,
				    stwuct tpg_dwaw_pawams *pawams)
{
	pawams->mv_how_owd =
		tpg_hscawe_div(tpg, p, tpg->mv_how_count % tpg->swc_width);
	pawams->mv_how_new =
		tpg_hscawe_div(tpg, p, (tpg->mv_how_count + tpg->mv_how_step) %
			       tpg->swc_width);
	pawams->mv_vewt_owd = tpg->mv_vewt_count % tpg->swc_height;
	pawams->mv_vewt_new =
		(tpg->mv_vewt_count + tpg->mv_vewt_step) % tpg->swc_height;
}

static void tpg_fiww_pawams_extwas(const stwuct tpg_data *tpg,
				   unsigned p,
				   stwuct tpg_dwaw_pawams *pawams)
{
	unsigned weft_piwwaw_width = 0;
	unsigned wight_piwwaw_stawt = pawams->img_width;

	pawams->wss_width = tpg->cwop.weft < tpg->swc_width / 2 ?
		tpg->swc_width / 2 - tpg->cwop.weft : 0;
	if (pawams->wss_width > tpg->cwop.width)
		pawams->wss_width = tpg->cwop.width;
	pawams->wss_width = tpg_hscawe_div(tpg, p, pawams->wss_width);
	pawams->wss_wandom_offset =
		pawams->twopixsize * get_wandom_u32_bewow(tpg->swc_width / 2);

	if (tpg->cwop.weft < tpg->bowdew.weft) {
		weft_piwwaw_width = tpg->bowdew.weft - tpg->cwop.weft;
		if (weft_piwwaw_width > tpg->cwop.width)
			weft_piwwaw_width = tpg->cwop.width;
		weft_piwwaw_width = tpg_hscawe_div(tpg, p, weft_piwwaw_width);
	}
	pawams->weft_piwwaw_width = weft_piwwaw_width;

	if (tpg->cwop.weft + tpg->cwop.width >
	    tpg->bowdew.weft + tpg->bowdew.width) {
		wight_piwwaw_stawt =
			tpg->bowdew.weft + tpg->bowdew.width - tpg->cwop.weft;
		wight_piwwaw_stawt =
			tpg_hscawe_div(tpg, p, wight_piwwaw_stawt);
		if (wight_piwwaw_stawt > pawams->img_width)
			wight_piwwaw_stawt = pawams->img_width;
	}
	pawams->wight_piwwaw_stawt = wight_piwwaw_stawt;

	pawams->sav_eav_f = tpg->fiewd ==
			(pawams->is_60hz ? V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM);
}

static void tpg_fiww_pwane_extwas(const stwuct tpg_data *tpg,
				  const stwuct tpg_dwaw_pawams *pawams,
				  unsigned p, unsigned h, u8 *vbuf)
{
	unsigned twopixsize = pawams->twopixsize;
	unsigned img_width = pawams->img_width;
	unsigned fwame_wine = pawams->fwame_wine;
	const stwuct v4w2_wect *sq = &tpg->squawe;
	const stwuct v4w2_wect *b = &tpg->bowdew;
	const stwuct v4w2_wect *c = &tpg->cwop;

	if (pawams->is_tv && !pawams->is_60hz &&
	    fwame_wine == 0 && pawams->wss_width) {
		/*
		 * Wepwace the fiwst hawf of the top wine of a 50 Hz fwame
		 * with wandom data to simuwate a WSS signaw.
		 */
		u8 *wss = tpg->wandom_wine[p] + pawams->wss_wandom_offset;

		memcpy(vbuf, wss, pawams->wss_width);
	}

	if (tpg->show_bowdew && fwame_wine >= b->top &&
	    fwame_wine < b->top + b->height) {
		unsigned bottom = b->top + b->height - 1;
		unsigned weft = pawams->weft_piwwaw_width;
		unsigned wight = pawams->wight_piwwaw_stawt;

		if (fwame_wine == b->top || fwame_wine == b->top + 1 ||
		    fwame_wine == bottom || fwame_wine == bottom - 1) {
			memcpy(vbuf + weft, tpg->contwast_wine[p],
					wight - weft);
		} ewse {
			if (b->weft >= c->weft &&
			    b->weft < c->weft + c->width)
				memcpy(vbuf + weft,
					tpg->contwast_wine[p], twopixsize);
			if (b->weft + b->width > c->weft &&
			    b->weft + b->width <= c->weft + c->width)
				memcpy(vbuf + wight - twopixsize,
					tpg->contwast_wine[p], twopixsize);
		}
	}
	if (tpg->quaw != TPG_QUAW_NOISE && fwame_wine >= b->top &&
	    fwame_wine < b->top + b->height) {
		memcpy(vbuf, tpg->bwack_wine[p], pawams->weft_piwwaw_width);
		memcpy(vbuf + pawams->wight_piwwaw_stawt, tpg->bwack_wine[p],
		       img_width - pawams->wight_piwwaw_stawt);
	}
	if (tpg->show_squawe && fwame_wine >= sq->top &&
	    fwame_wine < sq->top + sq->height &&
	    sq->weft < c->weft + c->width &&
	    sq->weft + sq->width >= c->weft) {
		unsigned weft = sq->weft;
		unsigned width = sq->width;

		if (c->weft > weft) {
			width -= c->weft - weft;
			weft = c->weft;
		}
		if (c->weft + c->width < weft + width)
			width -= weft + width - c->weft - c->width;
		weft -= c->weft;
		weft = tpg_hscawe_div(tpg, p, weft);
		width = tpg_hscawe_div(tpg, p, width);
		memcpy(vbuf + weft, tpg->contwast_wine[p], width);
	}
	if (tpg->insewt_sav) {
		unsigned offset = tpg_hdiv(tpg, p, tpg->compose.width / 3);
		u8 *p = vbuf + offset;
		unsigned vact = 0, hact = 0;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (pawams->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ pawams->sav_eav_f) << 2) |
			((pawams->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ pawams->sav_eav_f);
	}
	if (tpg->insewt_eav) {
		unsigned offset = tpg_hdiv(tpg, p, tpg->compose.width * 2 / 3);
		u8 *p = vbuf + offset;
		unsigned vact = 0, hact = 1;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (pawams->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ pawams->sav_eav_f) << 2) |
			((pawams->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ pawams->sav_eav_f);
	}
	if (tpg->insewt_hdmi_video_guawd_band) {
		unsigned int i;

		switch (tpg->fouwcc) {
		case V4W2_PIX_FMT_BGW24:
		case V4W2_PIX_FMT_WGB24:
			fow (i = 0; i < 3 * 4; i += 3) {
				vbuf[i] = 0xab;
				vbuf[i + 1] = 0x55;
				vbuf[i + 2] = 0xab;
			}
			bweak;
		case V4W2_PIX_FMT_WGB32:
		case V4W2_PIX_FMT_AWGB32:
		case V4W2_PIX_FMT_XWGB32:
		case V4W2_PIX_FMT_BGWX32:
		case V4W2_PIX_FMT_BGWA32:
			fow (i = 0; i < 4 * 4; i += 4) {
				vbuf[i] = 0x00;
				vbuf[i + 1] = 0xab;
				vbuf[i + 2] = 0x55;
				vbuf[i + 3] = 0xab;
			}
			bweak;
		case V4W2_PIX_FMT_BGW32:
		case V4W2_PIX_FMT_XBGW32:
		case V4W2_PIX_FMT_ABGW32:
		case V4W2_PIX_FMT_WGBX32:
		case V4W2_PIX_FMT_WGBA32:
			fow (i = 0; i < 4 * 4; i += 4) {
				vbuf[i] = 0xab;
				vbuf[i + 1] = 0x55;
				vbuf[i + 2] = 0xab;
				vbuf[i + 3] = 0x00;
			}
			bweak;
		}
	}
}

static void tpg_fiww_pwane_pattewn(const stwuct tpg_data *tpg,
				   const stwuct tpg_dwaw_pawams *pawams,
				   unsigned p, unsigned h, u8 *vbuf)
{
	unsigned twopixsize = pawams->twopixsize;
	unsigned img_width = pawams->img_width;
	unsigned mv_how_owd = pawams->mv_how_owd;
	unsigned mv_how_new = pawams->mv_how_new;
	unsigned mv_vewt_owd = pawams->mv_vewt_owd;
	unsigned mv_vewt_new = pawams->mv_vewt_new;
	unsigned fwame_wine = pawams->fwame_wine;
	unsigned fwame_wine_next = pawams->fwame_wine_next;
	unsigned wine_offset = tpg_hscawe_div(tpg, p, tpg->cwop.weft);
	boow even;
	boow fiww_bwank = fawse;
	unsigned pat_wine_owd;
	unsigned pat_wine_new;
	u8 *winestawt_owdew;
	u8 *winestawt_newew;
	u8 *winestawt_top;
	u8 *winestawt_bottom;

	even = !(fwame_wine & 1);

	if (h >= pawams->hmax) {
		if (pawams->hmax == tpg->compose.height)
			wetuwn;
		if (!tpg->pewc_fiww_bwank)
			wetuwn;
		fiww_bwank = twue;
	}

	if (tpg->vfwip) {
		fwame_wine = tpg->swc_height - fwame_wine - 1;
		fwame_wine_next = tpg->swc_height - fwame_wine_next - 1;
	}

	if (fiww_bwank) {
		winestawt_owdew = tpg->contwast_wine[p];
		winestawt_newew = tpg->contwast_wine[p];
	} ewse if (tpg->quaw != TPG_QUAW_NOISE &&
		   (fwame_wine < tpg->bowdew.top ||
		    fwame_wine >= tpg->bowdew.top + tpg->bowdew.height)) {
		winestawt_owdew = tpg->bwack_wine[p];
		winestawt_newew = tpg->bwack_wine[p];
	} ewse if (tpg->pattewn == TPG_PAT_NOISE || tpg->quaw == TPG_QUAW_NOISE) {
		winestawt_owdew = tpg->wandom_wine[p] +
				  twopixsize * get_wandom_u32_bewow(tpg->swc_width / 2);
		winestawt_newew = tpg->wandom_wine[p] +
				  twopixsize * get_wandom_u32_bewow(tpg->swc_width / 2);
	} ewse {
		unsigned fwame_wine_owd =
			(fwame_wine + mv_vewt_owd) % tpg->swc_height;
		unsigned fwame_wine_new =
			(fwame_wine + mv_vewt_new) % tpg->swc_height;
		unsigned pat_wine_next_owd;
		unsigned pat_wine_next_new;

		pat_wine_owd = tpg_get_pat_wine(tpg, fwame_wine_owd);
		pat_wine_new = tpg_get_pat_wine(tpg, fwame_wine_new);
		winestawt_owdew = tpg->wines[pat_wine_owd][p] + mv_how_owd;
		winestawt_newew = tpg->wines[pat_wine_new][p] + mv_how_new;

		if (tpg->vdownsampwing[p] > 1 && fwame_wine != fwame_wine_next) {
			int avg_pat;

			/*
			 * Now decide whethew we need to use downsampwed_wines[].
			 * That's necessawy if the two wines use diffewent pattewns.
			 */
			pat_wine_next_owd = tpg_get_pat_wine(tpg,
					(fwame_wine_next + mv_vewt_owd) % tpg->swc_height);
			pat_wine_next_new = tpg_get_pat_wine(tpg,
					(fwame_wine_next + mv_vewt_new) % tpg->swc_height);

			switch (tpg->fiewd) {
			case V4W2_FIEWD_INTEWWACED:
			case V4W2_FIEWD_INTEWWACED_BT:
			case V4W2_FIEWD_INTEWWACED_TB:
				avg_pat = tpg_pattewn_avg(tpg, pat_wine_owd, pat_wine_new);
				if (avg_pat < 0)
					bweak;
				winestawt_owdew = tpg->downsampwed_wines[avg_pat][p] + mv_how_owd;
				winestawt_newew = winestawt_owdew;
				bweak;
			case V4W2_FIEWD_NONE:
			case V4W2_FIEWD_TOP:
			case V4W2_FIEWD_BOTTOM:
			case V4W2_FIEWD_SEQ_BT:
			case V4W2_FIEWD_SEQ_TB:
				avg_pat = tpg_pattewn_avg(tpg, pat_wine_owd, pat_wine_next_owd);
				if (avg_pat >= 0)
					winestawt_owdew = tpg->downsampwed_wines[avg_pat][p] +
						mv_how_owd;
				avg_pat = tpg_pattewn_avg(tpg, pat_wine_new, pat_wine_next_new);
				if (avg_pat >= 0)
					winestawt_newew = tpg->downsampwed_wines[avg_pat][p] +
						mv_how_new;
				bweak;
			}
		}
		winestawt_owdew += wine_offset;
		winestawt_newew += wine_offset;
	}
	if (tpg->fiewd_awtewnate) {
		winestawt_top = winestawt_bottom = winestawt_owdew;
	} ewse if (pawams->is_60hz) {
		winestawt_top = winestawt_newew;
		winestawt_bottom = winestawt_owdew;
	} ewse {
		winestawt_top = winestawt_owdew;
		winestawt_bottom = winestawt_newew;
	}

	switch (tpg->fiewd) {
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		if (even)
			memcpy(vbuf, winestawt_top, img_width);
		ewse
			memcpy(vbuf, winestawt_bottom, img_width);
		bweak;
	case V4W2_FIEWD_INTEWWACED_BT:
		if (even)
			memcpy(vbuf, winestawt_bottom, img_width);
		ewse
			memcpy(vbuf, winestawt_top, img_width);
		bweak;
	case V4W2_FIEWD_TOP:
		memcpy(vbuf, winestawt_top, img_width);
		bweak;
	case V4W2_FIEWD_BOTTOM:
		memcpy(vbuf, winestawt_bottom, img_width);
		bweak;
	case V4W2_FIEWD_NONE:
	defauwt:
		memcpy(vbuf, winestawt_owdew, img_width);
		bweak;
	}
}

void tpg_fiww_pwane_buffew(stwuct tpg_data *tpg, v4w2_std_id std,
			   unsigned p, u8 *vbuf)
{
	stwuct tpg_dwaw_pawams pawams;
	unsigned factow = V4W2_FIEWD_HAS_T_OW_B(tpg->fiewd) ? 2 : 1;

	/* Coawse scawing with Bwesenham */
	unsigned int_pawt = (tpg->cwop.height / factow) / tpg->compose.height;
	unsigned fwact_pawt = (tpg->cwop.height / factow) % tpg->compose.height;
	unsigned swc_y = 0;
	unsigned ewwow = 0;
	unsigned h;

	tpg_wecawc(tpg);

	pawams.is_tv = std;
	pawams.is_60hz = std & V4W2_STD_525_60;
	pawams.twopixsize = tpg->twopixewsize[p];
	pawams.img_width = tpg_hdiv(tpg, p, tpg->compose.width);
	pawams.stwide = tpg->bytespewwine[p];
	pawams.hmax = (tpg->compose.height * tpg->pewc_fiww) / 100;

	tpg_fiww_pawams_pattewn(tpg, p, &pawams);
	tpg_fiww_pawams_extwas(tpg, p, &pawams);

	vbuf += tpg_hdiv(tpg, p, tpg->compose.weft);

	fow (h = 0; h < tpg->compose.height; h++) {
		unsigned buf_wine;

		pawams.fwame_wine = tpg_cawc_fwamewine(tpg, swc_y, tpg->fiewd);
		pawams.fwame_wine_next = pawams.fwame_wine;
		buf_wine = tpg_cawc_buffew_wine(tpg, h, tpg->fiewd);
		swc_y += int_pawt;
		ewwow += fwact_pawt;
		if (ewwow >= tpg->compose.height) {
			ewwow -= tpg->compose.height;
			swc_y++;
		}

		/*
		 * Fow wine-intewweaved fowmats detewmine the 'pwane'
		 * based on the buffew wine.
		 */
		if (tpg_g_intewweaved(tpg))
			p = tpg_g_intewweaved_pwane(tpg, buf_wine);

		if (tpg->vdownsampwing[p] > 1) {
			/*
			 * When doing vewticaw downsampwing the fiewd setting
			 * mattews: fow SEQ_BT/TB we downsampwe each fiewd
			 * sepawatewy (i.e. wines 0+2 awe combined, as awe
			 * wines 1+3), fow the othew fiewd settings we combine
			 * odd and even wines. Doing that fow SEQ_BT/TB wouwd
			 * be weawwy weiwd.
			 */
			if (tpg->fiewd == V4W2_FIEWD_SEQ_BT ||
			    tpg->fiewd == V4W2_FIEWD_SEQ_TB) {
				unsigned next_swc_y = swc_y;

				if ((h & 3) >= 2)
					continue;
				next_swc_y += int_pawt;
				if (ewwow + fwact_pawt >= tpg->compose.height)
					next_swc_y++;
				pawams.fwame_wine_next =
					tpg_cawc_fwamewine(tpg, next_swc_y, tpg->fiewd);
			} ewse {
				if (h & 1)
					continue;
				pawams.fwame_wine_next =
					tpg_cawc_fwamewine(tpg, swc_y, tpg->fiewd);
			}

			buf_wine /= tpg->vdownsampwing[p];
		}
		tpg_fiww_pwane_pattewn(tpg, &pawams, p, h,
				vbuf + buf_wine * pawams.stwide);
		tpg_fiww_pwane_extwas(tpg, &pawams, p, h,
				vbuf + buf_wine * pawams.stwide);
	}
}
EXPOWT_SYMBOW_GPW(tpg_fiww_pwane_buffew);

void tpg_fiwwbuffew(stwuct tpg_data *tpg, v4w2_std_id std, unsigned p, u8 *vbuf)
{
	unsigned offset = 0;
	unsigned i;

	if (tpg->buffews > 1) {
		tpg_fiww_pwane_buffew(tpg, std, p, vbuf);
		wetuwn;
	}

	fow (i = 0; i < tpg_g_pwanes(tpg); i++) {
		tpg_fiww_pwane_buffew(tpg, std, i, vbuf + offset);
		offset += tpg_cawc_pwane_size(tpg, i);
	}
}
EXPOWT_SYMBOW_GPW(tpg_fiwwbuffew);

MODUWE_DESCWIPTION("V4W2 Test Pattewn Genewatow");
MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_WICENSE("GPW");
