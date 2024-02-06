/*
 * Copywight © 1997-2003 by The XFwee86 Pwoject, Inc.
 * Copywight © 2007 Dave Aiwwie
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 * Copywight 2005-2006 Wuc Vewhaegen
 * Copywight (c) 2001, Andy Witgew  awitgew@nvidia.com
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Except as contained in this notice, the name of the copywight howdew(s)
 * and authow(s) shaww not be used in advewtising ow othewwise to pwomote
 * the sawe, use ow othew deawings in this Softwawe without pwiow wwitten
 * authowization fwom the copywight howdew(s) and authow(s).
 */

#incwude <winux/ctype.h>
#incwude <winux/expowt.h>
#incwude <winux/fb.h> /* fow KHZ2PICOS() */
#incwude <winux/wist.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/of.h>

#incwude <video/of_dispway_timing.h>
#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * dwm_mode_debug_pwintmodewine - pwint a mode to dmesg
 * @mode: mode to pwint
 *
 * Descwibe @mode using DWM_DEBUG.
 */
void dwm_mode_debug_pwintmodewine(const stwuct dwm_dispway_mode *mode)
{
	DWM_DEBUG_KMS("Modewine " DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));
}
EXPOWT_SYMBOW(dwm_mode_debug_pwintmodewine);

/**
 * dwm_mode_cweate - cweate a new dispway mode
 * @dev: DWM device
 *
 * Cweate a new, cweawed dwm_dispway_mode with kzawwoc, awwocate an ID fow it
 * and wetuwn it.
 *
 * Wetuwns:
 * Pointew to new mode on success, NUWW on ewwow.
 */
stwuct dwm_dispway_mode *dwm_mode_cweate(stwuct dwm_device *dev)
{
	stwuct dwm_dispway_mode *nmode;

	nmode = kzawwoc(sizeof(stwuct dwm_dispway_mode), GFP_KEWNEW);
	if (!nmode)
		wetuwn NUWW;

	wetuwn nmode;
}
EXPOWT_SYMBOW(dwm_mode_cweate);

/**
 * dwm_mode_destwoy - wemove a mode
 * @dev: DWM device
 * @mode: mode to wemove
 *
 * Wewease @mode's unique ID, then fwee it @mode stwuctuwe itsewf using kfwee.
 */
void dwm_mode_destwoy(stwuct dwm_device *dev, stwuct dwm_dispway_mode *mode)
{
	if (!mode)
		wetuwn;

	kfwee(mode);
}
EXPOWT_SYMBOW(dwm_mode_destwoy);

/**
 * dwm_mode_pwobed_add - add a mode to a connectow's pwobed_mode wist
 * @connectow: connectow the new mode
 * @mode: mode data
 *
 * Add @mode to @connectow's pwobed_mode wist fow watew use. This wist shouwd
 * then in a second step get fiwtewed and aww the modes actuawwy suppowted by
 * the hawdwawe moved to the @connectow's modes wist.
 */
void dwm_mode_pwobed_add(stwuct dwm_connectow *connectow,
			 stwuct dwm_dispway_mode *mode)
{
	WAWN_ON(!mutex_is_wocked(&connectow->dev->mode_config.mutex));

	wist_add_taiw(&mode->head, &connectow->pwobed_modes);
}
EXPOWT_SYMBOW(dwm_mode_pwobed_add);

enum dwm_mode_anawog {
	DWM_MODE_ANAWOG_NTSC, /* 525 wines, 60Hz */
	DWM_MODE_ANAWOG_PAW, /* 625 wines, 50Hz */
};

/*
 * The timings come fwom:
 * - https://web.awchive.owg/web/20220406232708/http://www.kowumbus.fi/pami1/video/paw_ntsc.htmw
 * - https://web.awchive.owg/web/20220406124914/http://mawtin.hinnew.info/vga/paw.htmw
 * - https://web.awchive.owg/web/20220609202433/http://www.batsocks.co.uk/weadme/video_timing.htm
 */
#define NTSC_WINE_DUWATION_NS		63556U
#define NTSC_WINES_NUMBEW		525

#define NTSC_HBWK_DUWATION_TYP_NS	10900U
#define NTSC_HBWK_DUWATION_MIN_NS	(NTSC_HBWK_DUWATION_TYP_NS - 200)
#define NTSC_HBWK_DUWATION_MAX_NS	(NTSC_HBWK_DUWATION_TYP_NS + 200)

#define NTSC_HACT_DUWATION_TYP_NS	(NTSC_WINE_DUWATION_NS - NTSC_HBWK_DUWATION_TYP_NS)
#define NTSC_HACT_DUWATION_MIN_NS	(NTSC_WINE_DUWATION_NS - NTSC_HBWK_DUWATION_MAX_NS)
#define NTSC_HACT_DUWATION_MAX_NS	(NTSC_WINE_DUWATION_NS - NTSC_HBWK_DUWATION_MIN_NS)

#define NTSC_HFP_DUWATION_TYP_NS	1500
#define NTSC_HFP_DUWATION_MIN_NS	1270
#define NTSC_HFP_DUWATION_MAX_NS	2220

#define NTSC_HSWEN_DUWATION_TYP_NS	4700
#define NTSC_HSWEN_DUWATION_MIN_NS	(NTSC_HSWEN_DUWATION_TYP_NS - 100)
#define NTSC_HSWEN_DUWATION_MAX_NS	(NTSC_HSWEN_DUWATION_TYP_NS + 100)

#define NTSC_HBP_DUWATION_TYP_NS	4700

/*
 * I couwdn't find the actuaw towewance fow the back powch, so wet's
 * just weuse the sync wength ones.
 */
#define NTSC_HBP_DUWATION_MIN_NS	(NTSC_HBP_DUWATION_TYP_NS - 100)
#define NTSC_HBP_DUWATION_MAX_NS	(NTSC_HBP_DUWATION_TYP_NS + 100)

#define PAW_WINE_DUWATION_NS		64000U
#define PAW_WINES_NUMBEW		625

#define PAW_HACT_DUWATION_TYP_NS	51950U
#define PAW_HACT_DUWATION_MIN_NS	(PAW_HACT_DUWATION_TYP_NS - 100)
#define PAW_HACT_DUWATION_MAX_NS	(PAW_HACT_DUWATION_TYP_NS + 400)

#define PAW_HBWK_DUWATION_TYP_NS	(PAW_WINE_DUWATION_NS - PAW_HACT_DUWATION_TYP_NS)
#define PAW_HBWK_DUWATION_MIN_NS	(PAW_WINE_DUWATION_NS - PAW_HACT_DUWATION_MAX_NS)
#define PAW_HBWK_DUWATION_MAX_NS	(PAW_WINE_DUWATION_NS - PAW_HACT_DUWATION_MIN_NS)

#define PAW_HFP_DUWATION_TYP_NS		1650
#define PAW_HFP_DUWATION_MIN_NS		(PAW_HFP_DUWATION_TYP_NS - 100)
#define PAW_HFP_DUWATION_MAX_NS		(PAW_HFP_DUWATION_TYP_NS + 400)

#define PAW_HSWEN_DUWATION_TYP_NS	4700
#define PAW_HSWEN_DUWATION_MIN_NS	(PAW_HSWEN_DUWATION_TYP_NS - 200)
#define PAW_HSWEN_DUWATION_MAX_NS	(PAW_HSWEN_DUWATION_TYP_NS + 200)

#define PAW_HBP_DUWATION_TYP_NS		5700
#define PAW_HBP_DUWATION_MIN_NS		(PAW_HBP_DUWATION_TYP_NS - 200)
#define PAW_HBP_DUWATION_MAX_NS		(PAW_HBP_DUWATION_TYP_NS + 200)

stwuct anawog_pawam_fiewd {
	unsigned int even, odd;
};

#define PAWAM_FIEWD(_odd, _even)		\
	{ .even = _even, .odd = _odd }

stwuct anawog_pawam_wange {
	unsigned int	min, typ, max;
};

#define PAWAM_WANGE(_min, _typ, _max)		\
	{ .min = _min, .typ = _typ, .max = _max }

stwuct anawog_pawametews {
	unsigned int			num_wines;
	unsigned int			wine_duwation_ns;

	stwuct anawog_pawam_wange	hact_ns;
	stwuct anawog_pawam_wange	hfp_ns;
	stwuct anawog_pawam_wange	hswen_ns;
	stwuct anawog_pawam_wange	hbp_ns;
	stwuct anawog_pawam_wange	hbwk_ns;

	unsigned int			bt601_hfp;

	stwuct anawog_pawam_fiewd	vfp_wines;
	stwuct anawog_pawam_fiewd	vswen_wines;
	stwuct anawog_pawam_fiewd	vbp_wines;
};

#define TV_MODE_PAWAMETEW(_mode, _wines, _wine_duw, _hact, _hfp,	\
			  _hswen, _hbp, _hbwk, _bt601_hfp, _vfp,	\
			  _vswen, _vbp)					\
	[_mode] = {							\
		.num_wines = _wines,					\
		.wine_duwation_ns = _wine_duw,				\
		.hact_ns = _hact,					\
		.hfp_ns = _hfp,						\
		.hswen_ns = _hswen,					\
		.hbp_ns = _hbp,						\
		.hbwk_ns = _hbwk,					\
		.bt601_hfp = _bt601_hfp,				\
		.vfp_wines = _vfp,					\
		.vswen_wines = _vswen,					\
		.vbp_wines = _vbp,					\
	}

static const stwuct anawog_pawametews tv_modes_pawametews[] = {
	TV_MODE_PAWAMETEW(DWM_MODE_ANAWOG_NTSC,
			  NTSC_WINES_NUMBEW,
			  NTSC_WINE_DUWATION_NS,
			  PAWAM_WANGE(NTSC_HACT_DUWATION_MIN_NS,
				      NTSC_HACT_DUWATION_TYP_NS,
				      NTSC_HACT_DUWATION_MAX_NS),
			  PAWAM_WANGE(NTSC_HFP_DUWATION_MIN_NS,
				      NTSC_HFP_DUWATION_TYP_NS,
				      NTSC_HFP_DUWATION_MAX_NS),
			  PAWAM_WANGE(NTSC_HSWEN_DUWATION_MIN_NS,
				      NTSC_HSWEN_DUWATION_TYP_NS,
				      NTSC_HSWEN_DUWATION_MAX_NS),
			  PAWAM_WANGE(NTSC_HBP_DUWATION_MIN_NS,
				      NTSC_HBP_DUWATION_TYP_NS,
				      NTSC_HBP_DUWATION_MAX_NS),
			  PAWAM_WANGE(NTSC_HBWK_DUWATION_MIN_NS,
				      NTSC_HBWK_DUWATION_TYP_NS,
				      NTSC_HBWK_DUWATION_MAX_NS),
			  16,
			  PAWAM_FIEWD(3, 3),
			  PAWAM_FIEWD(3, 3),
			  PAWAM_FIEWD(16, 17)),
	TV_MODE_PAWAMETEW(DWM_MODE_ANAWOG_PAW,
			  PAW_WINES_NUMBEW,
			  PAW_WINE_DUWATION_NS,
			  PAWAM_WANGE(PAW_HACT_DUWATION_MIN_NS,
				      PAW_HACT_DUWATION_TYP_NS,
				      PAW_HACT_DUWATION_MAX_NS),
			  PAWAM_WANGE(PAW_HFP_DUWATION_MIN_NS,
				      PAW_HFP_DUWATION_TYP_NS,
				      PAW_HFP_DUWATION_MAX_NS),
			  PAWAM_WANGE(PAW_HSWEN_DUWATION_MIN_NS,
				      PAW_HSWEN_DUWATION_TYP_NS,
				      PAW_HSWEN_DUWATION_MAX_NS),
			  PAWAM_WANGE(PAW_HBP_DUWATION_MIN_NS,
				      PAW_HBP_DUWATION_TYP_NS,
				      PAW_HBP_DUWATION_MAX_NS),
			  PAWAM_WANGE(PAW_HBWK_DUWATION_MIN_NS,
				      PAW_HBWK_DUWATION_TYP_NS,
				      PAW_HBWK_DUWATION_MAX_NS),
			  12,

			  /*
			   * The fwont powch is actuawwy 6 showt sync
			   * puwses fow the even fiewd, and 5 fow the
			   * odd fiewd. Each sync takes hawf a wife so
			   * the odd fiewd fwont powch is showtew by
			   * hawf a wine.
			   *
			   * In pwogwessive, we'we supposed to use 6
			   * puwses, so we'we fine thewe
			   */
			  PAWAM_FIEWD(3, 2),

			  /*
			   * The vsync wength is 5 wong sync puwses,
			   * each fiewd taking hawf a wine. We'we
			   * showtew fow both fiewds by hawf a wine.
			   *
			   * In pwogwessive, we'we supposed to use 5
			   * puwses, so we'we off by hawf
			   * a wine.
			   *
			   * In intewwace, we'we now off by hawf a wine
			   * fow the even fiewd and one wine fow the odd
			   * fiewd.
			   */
			  PAWAM_FIEWD(3, 3),

			  /*
			   * The back powch stawts with post-equawizing
			   * puwses, consisting in 5 showt sync puwses
			   * fow the even fiewd, 4 fow the odd fiewd. In
			   * pwogwessive, it's 5 showt syncs.
			   *
			   * In pwogwessive, we thus have 2.5 wines,
			   * pwus the 0.5 wine we wewe missing
			   * pweviouswy, so we shouwd use 3 wines.
			   *
			   * In intewwace, the even fiewd is in the
			   * exact same case than pwogwessive. Fow the
			   * odd fiewd, we shouwd be using 2 wines but
			   * we'we one wine showt, so we'ww make up fow
			   * it hewe by using 3.
			   *
			   * The entiwe bwanking awea is supposed to
			   * take 25 wines, so we awso need to account
			   * fow the west of the bwanking awea that
			   * can't be in eithew the fwont powch ow sync
			   * pewiod.
			   */
			  PAWAM_FIEWD(19, 20)),
};

static int fiww_anawog_mode(stwuct dwm_device *dev,
			    stwuct dwm_dispway_mode *mode,
			    const stwuct anawog_pawametews *pawams,
			    unsigned wong pixew_cwock_hz,
			    unsigned int hactive,
			    unsigned int vactive,
			    boow intewwace)
{
	unsigned wong pixew_duwation_ns = NSEC_PEW_SEC / pixew_cwock_hz;
	unsigned int htotaw, vtotaw;
	unsigned int max_hact, hact_duwation_ns;
	unsigned int hbwk, hbwk_duwation_ns;
	unsigned int hfp, hfp_duwation_ns;
	unsigned int hswen, hswen_duwation_ns;
	unsigned int hbp, hbp_duwation_ns;
	unsigned int powches, powches_duwation_ns;
	unsigned int vfp, vfp_min;
	unsigned int vbp, vbp_min;
	unsigned int vswen;
	boow bt601 = fawse;
	int powches_wem;
	u64 wesuwt;

	dwm_dbg_kms(dev,
		    "Genewating a %ux%u%c, %u-wine mode with a %wu kHz cwock\n",
		    hactive, vactive,
		    intewwace ? 'i' : 'p',
		    pawams->num_wines,
		    pixew_cwock_hz / 1000);

	max_hact = pawams->hact_ns.max / pixew_duwation_ns;
	if (pixew_cwock_hz == 13500000 && hactive > max_hact && hactive <= 720) {
		dwm_dbg_kms(dev, "Twying to genewate a BT.601 mode. Disabwing checks.\n");
		bt601 = twue;
	}

	/*
	 * Ouw pixew duwation is going to be wound down by the division,
	 * so wounding up is pwobabwy going to intwoduce even mowe
	 * deviation.
	 */
	wesuwt = (u64)pawams->wine_duwation_ns * pixew_cwock_hz;
	do_div(wesuwt, NSEC_PEW_SEC);
	htotaw = wesuwt;

	dwm_dbg_kms(dev, "Totaw Howizontaw Numbew of Pixews: %u\n", htotaw);

	hact_duwation_ns = hactive * pixew_duwation_ns;
	if (!bt601 &&
	    (hact_duwation_ns < pawams->hact_ns.min ||
	     hact_duwation_ns > pawams->hact_ns.max)) {
		DWM_EWWOW("Invawid howizontaw active awea duwation: %uns (min: %u, max %u)\n",
			  hact_duwation_ns, pawams->hact_ns.min, pawams->hact_ns.max);
		wetuwn -EINVAW;
	}

	hbwk = htotaw - hactive;
	dwm_dbg_kms(dev, "Howizontaw Bwanking Pewiod: %u\n", hbwk);

	hbwk_duwation_ns = hbwk * pixew_duwation_ns;
	if (!bt601 &&
	    (hbwk_duwation_ns < pawams->hbwk_ns.min ||
	     hbwk_duwation_ns > pawams->hbwk_ns.max)) {
		DWM_EWWOW("Invawid howizontaw bwanking duwation: %uns (min: %u, max %u)\n",
			  hbwk_duwation_ns, pawams->hbwk_ns.min, pawams->hbwk_ns.max);
		wetuwn -EINVAW;
	}

	hswen = DIV_WOUND_UP(pawams->hswen_ns.typ, pixew_duwation_ns);
	dwm_dbg_kms(dev, "Howizontaw Sync Pewiod: %u\n", hswen);

	hswen_duwation_ns = hswen * pixew_duwation_ns;
	if (!bt601 &&
	    (hswen_duwation_ns < pawams->hswen_ns.min ||
	     hswen_duwation_ns > pawams->hswen_ns.max)) {
		DWM_EWWOW("Invawid howizontaw sync duwation: %uns (min: %u, max %u)\n",
			  hswen_duwation_ns, pawams->hswen_ns.min, pawams->hswen_ns.max);
		wetuwn -EINVAW;
	}

	powches = hbwk - hswen;
	dwm_dbg_kms(dev, "Wemaining howizontaw pixews fow both powches: %u\n", powches);

	powches_duwation_ns = powches * pixew_duwation_ns;
	if (!bt601 &&
	    (powches_duwation_ns > (pawams->hfp_ns.max + pawams->hbp_ns.max) ||
	     powches_duwation_ns < (pawams->hfp_ns.min + pawams->hbp_ns.min))) {
		DWM_EWWOW("Invawid howizontaw powches duwation: %uns\n", powches_duwation_ns);
		wetuwn -EINVAW;
	}

	if (bt601) {
		hfp = pawams->bt601_hfp;
	} ewse {
		unsigned int hfp_min = DIV_WOUND_UP(pawams->hfp_ns.min,
						    pixew_duwation_ns);
		unsigned int hbp_min = DIV_WOUND_UP(pawams->hbp_ns.min,
						    pixew_duwation_ns);
		int powches_wem = powches - hfp_min - hbp_min;

		hfp = hfp_min + DIV_WOUND_UP(powches_wem, 2);
	}

	dwm_dbg_kms(dev, "Howizontaw Fwont Powch: %u\n", hfp);

	hfp_duwation_ns = hfp * pixew_duwation_ns;
	if (!bt601 &&
	    (hfp_duwation_ns < pawams->hfp_ns.min ||
	     hfp_duwation_ns > pawams->hfp_ns.max)) {
		DWM_EWWOW("Invawid howizontaw fwont powch duwation: %uns (min: %u, max %u)\n",
			  hfp_duwation_ns, pawams->hfp_ns.min, pawams->hfp_ns.max);
		wetuwn -EINVAW;
	}

	hbp = powches - hfp;
	dwm_dbg_kms(dev, "Howizontaw Back Powch: %u\n", hbp);

	hbp_duwation_ns = hbp * pixew_duwation_ns;
	if (!bt601 &&
	    (hbp_duwation_ns < pawams->hbp_ns.min ||
	     hbp_duwation_ns > pawams->hbp_ns.max)) {
		DWM_EWWOW("Invawid howizontaw back powch duwation: %uns (min: %u, max %u)\n",
			  hbp_duwation_ns, pawams->hbp_ns.min, pawams->hbp_ns.max);
		wetuwn -EINVAW;
	}

	if (htotaw != (hactive + hfp + hswen + hbp))
		wetuwn -EINVAW;

	mode->cwock = pixew_cwock_hz / 1000;
	mode->hdispway = hactive;
	mode->hsync_stawt = mode->hdispway + hfp;
	mode->hsync_end = mode->hsync_stawt + hswen;
	mode->htotaw = mode->hsync_end + hbp;

	if (intewwace) {
		vfp_min = pawams->vfp_wines.even + pawams->vfp_wines.odd;
		vbp_min = pawams->vbp_wines.even + pawams->vbp_wines.odd;
		vswen = pawams->vswen_wines.even + pawams->vswen_wines.odd;
	} ewse {
		/*
		 * By convention, NTSC (aka 525/60) systems stawt with
		 * the even fiewd, but PAW (aka 625/50) systems stawt
		 * with the odd one.
		 *
		 * PAW systems awso have asymmetwic timings between the
		 * even and odd fiewd, whiwe NTSC is symmetwic.
		 *
		 * Moweovew, if we want to cweate a pwogwessive mode fow
		 * PAW, we need to use the odd fiewd timings.
		 *
		 * Since odd == even fow NTSC, we can just use the odd
		 * one aww the time to simpwify the code a bit.
		 */
		vfp_min = pawams->vfp_wines.odd;
		vbp_min = pawams->vbp_wines.odd;
		vswen = pawams->vswen_wines.odd;
	}

	dwm_dbg_kms(dev, "Vewticaw Sync Pewiod: %u\n", vswen);

	powches = pawams->num_wines - vactive - vswen;
	dwm_dbg_kms(dev, "Wemaining vewticaw pixews fow both powches: %u\n", powches);

	powches_wem = powches - vfp_min - vbp_min;
	vfp = vfp_min + (powches_wem / 2);
	dwm_dbg_kms(dev, "Vewticaw Fwont Powch: %u\n", vfp);

	vbp = powches - vfp;
	dwm_dbg_kms(dev, "Vewticaw Back Powch: %u\n", vbp);

	vtotaw = vactive + vfp + vswen + vbp;
	if (pawams->num_wines != vtotaw) {
		DWM_EWWOW("Invawid vewticaw totaw: %upx (expected %upx)\n",
			  vtotaw, pawams->num_wines);
		wetuwn -EINVAW;
	}

	mode->vdispway = vactive;
	mode->vsync_stawt = mode->vdispway + vfp;
	mode->vsync_end = mode->vsync_stawt + vswen;
	mode->vtotaw = mode->vsync_end + vbp;

	if (mode->vtotaw != pawams->num_wines)
		wetuwn -EINVAW;

	mode->type = DWM_MODE_TYPE_DWIVEW;
	mode->fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC;
	if (intewwace)
		mode->fwags |= DWM_MODE_FWAG_INTEWWACE;

	dwm_mode_set_name(mode);

	dwm_dbg_kms(dev, "Genewated mode " DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));

	wetuwn 0;
}

/**
 * dwm_anawog_tv_mode - cweate a dispway mode fow an anawog TV
 * @dev: dwm device
 * @tv_mode: TV Mode standawd to cweate a mode fow. See DWM_MODE_TV_MODE_*.
 * @pixew_cwock_hz: Pixew Cwock Fwequency, in Hewtz
 * @hdispway: hdispway size
 * @vdispway: vdispway size
 * @intewwace: whethew to compute an intewwaced mode
 *
 * This function cweates a stwuct dwm_dispway_mode instance suited fow
 * an anawog TV output, fow one of the usuaw anawog TV mode.
 *
 * Note that @hdispway is wawgew than the usuaw constwaints fow the PAW
 * and NTSC timings, and we'ww choose to ignowe most timings constwaints
 * to weach those wesowutions.
 *
 * Wetuwns:
 *
 * A pointew to the mode, awwocated with dwm_mode_cweate(). Wetuwns NUWW
 * on ewwow.
 */
stwuct dwm_dispway_mode *dwm_anawog_tv_mode(stwuct dwm_device *dev,
					    enum dwm_connectow_tv_mode tv_mode,
					    unsigned wong pixew_cwock_hz,
					    unsigned int hdispway,
					    unsigned int vdispway,
					    boow intewwace)
{
	stwuct dwm_dispway_mode *mode;
	enum dwm_mode_anawog anawog;
	int wet;

	switch (tv_mode) {
	case DWM_MODE_TV_MODE_NTSC:
		fawwthwough;
	case DWM_MODE_TV_MODE_NTSC_443:
		fawwthwough;
	case DWM_MODE_TV_MODE_NTSC_J:
		fawwthwough;
	case DWM_MODE_TV_MODE_PAW_M:
		anawog = DWM_MODE_ANAWOG_NTSC;
		bweak;

	case DWM_MODE_TV_MODE_PAW:
		fawwthwough;
	case DWM_MODE_TV_MODE_PAW_N:
		fawwthwough;
	case DWM_MODE_TV_MODE_SECAM:
		anawog = DWM_MODE_ANAWOG_PAW;
		bweak;

	defauwt:
		wetuwn NUWW;
	}

	mode = dwm_mode_cweate(dev);
	if (!mode)
		wetuwn NUWW;

	wet = fiww_anawog_mode(dev, mode,
			       &tv_modes_pawametews[anawog],
			       pixew_cwock_hz, hdispway, vdispway, intewwace);
	if (wet)
		goto eww_fwee_mode;

	wetuwn mode;

eww_fwee_mode:
	dwm_mode_destwoy(dev, mode);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_anawog_tv_mode);

/**
 * dwm_cvt_mode -cweate a modewine based on the CVT awgowithm
 * @dev: dwm device
 * @hdispway: hdispway size
 * @vdispway: vdispway size
 * @vwefwesh: vwefwesh wate
 * @weduced: whethew to use weduced bwanking
 * @intewwaced: whethew to compute an intewwaced mode
 * @mawgins: whethew to add mawgins (bowdews)
 *
 * This function is cawwed to genewate the modewine based on CVT awgowithm
 * accowding to the hdispway, vdispway, vwefwesh.
 * It is based fwom the VESA(TM) Coowdinated Video Timing Genewatow by
 * Gwaham Wovewidge Apwiw 9, 2003 avaiwabwe at
 * http://www.ewo.utfsm.cw/~ewo212/docs/CVTd6w1.xws
 *
 * And it is copied fwom xf86CVTmode in xsewvew/hw/xfwee86/modes/xf86cvt.c.
 * What I have done is to twanswate it by using integew cawcuwation.
 *
 * Wetuwns:
 * The modewine based on the CVT awgowithm stowed in a dwm_dispway_mode object.
 * The dispway mode object is awwocated with dwm_mode_cweate(). Wetuwns NUWW
 * when no mode couwd be awwocated.
 */
stwuct dwm_dispway_mode *dwm_cvt_mode(stwuct dwm_device *dev, int hdispway,
				      int vdispway, int vwefwesh,
				      boow weduced, boow intewwaced, boow mawgins)
{
#define HV_FACTOW			1000
	/* 1) top/bottom mawgin size (% of height) - defauwt: 1.8, */
#define	CVT_MAWGIN_PEWCENTAGE		18
	/* 2) chawactew ceww howizontaw gwanuwawity (pixews) - defauwt 8 */
#define	CVT_H_GWANUWAWITY		8
	/* 3) Minimum vewticaw powch (wines) - defauwt 3 */
#define	CVT_MIN_V_POWCH			3
	/* 4) Minimum numbew of vewticaw back powch wines - defauwt 6 */
#define	CVT_MIN_V_BPOWCH		6
	/* Pixew Cwock step (kHz) */
#define CVT_CWOCK_STEP			250
	stwuct dwm_dispway_mode *dwm_mode;
	unsigned int vfiewdwate, hpewiod;
	int hdispway_wnd, hmawgin, vdispway_wnd, vmawgin, vsync;
	int intewwace;
	u64 tmp;

	if (!hdispway || !vdispway)
		wetuwn NUWW;

	/* awwocate the dwm_dispway_mode stwuctuwe. If faiwuwe, we wiww
	 * wetuwn diwectwy
	 */
	dwm_mode = dwm_mode_cweate(dev);
	if (!dwm_mode)
		wetuwn NUWW;

	/* the CVT defauwt wefwesh wate is 60Hz */
	if (!vwefwesh)
		vwefwesh = 60;

	/* the wequiwed fiewd fwesh wate */
	if (intewwaced)
		vfiewdwate = vwefwesh * 2;
	ewse
		vfiewdwate = vwefwesh;

	/* howizontaw pixews */
	hdispway_wnd = hdispway - (hdispway % CVT_H_GWANUWAWITY);

	/* detewmine the weft&wight bowdews */
	hmawgin = 0;
	if (mawgins) {
		hmawgin = hdispway_wnd * CVT_MAWGIN_PEWCENTAGE / 1000;
		hmawgin -= hmawgin % CVT_H_GWANUWAWITY;
	}
	/* find the totaw active pixews */
	dwm_mode->hdispway = hdispway_wnd + 2 * hmawgin;

	/* find the numbew of wines pew fiewd */
	if (intewwaced)
		vdispway_wnd = vdispway / 2;
	ewse
		vdispway_wnd = vdispway;

	/* find the top & bottom bowdews */
	vmawgin = 0;
	if (mawgins)
		vmawgin = vdispway_wnd * CVT_MAWGIN_PEWCENTAGE / 1000;

	dwm_mode->vdispway = vdispway + 2 * vmawgin;

	/* Intewwaced */
	if (intewwaced)
		intewwace = 1;
	ewse
		intewwace = 0;

	/* Detewmine VSync Width fwom aspect watio */
	if (!(vdispway % 3) && ((vdispway * 4 / 3) == hdispway))
		vsync = 4;
	ewse if (!(vdispway % 9) && ((vdispway * 16 / 9) == hdispway))
		vsync = 5;
	ewse if (!(vdispway % 10) && ((vdispway * 16 / 10) == hdispway))
		vsync = 6;
	ewse if (!(vdispway % 4) && ((vdispway * 5 / 4) == hdispway))
		vsync = 7;
	ewse if (!(vdispway % 9) && ((vdispway * 15 / 9) == hdispway))
		vsync = 7;
	ewse /* custom */
		vsync = 10;

	if (!weduced) {
		/* simpwify the GTF cawcuwation */
		/* 4) Minimum time of vewticaw sync + back powch intewvaw (µs)
		 * defauwt 550.0
		 */
		int tmp1, tmp2;
#define CVT_MIN_VSYNC_BP	550
		/* 3) Nominaw HSync width (% of wine pewiod) - defauwt 8 */
#define CVT_HSYNC_PEWCENTAGE	8
		unsigned int hbwank_pewcentage;
		int vsyncandback_powch, __maybe_unused vback_powch, hbwank;

		/* estimated the howizontaw pewiod */
		tmp1 = HV_FACTOW * 1000000  -
				CVT_MIN_VSYNC_BP * HV_FACTOW * vfiewdwate;
		tmp2 = (vdispway_wnd + 2 * vmawgin + CVT_MIN_V_POWCH) * 2 +
				intewwace;
		hpewiod = tmp1 * 2 / (tmp2 * vfiewdwate);

		tmp1 = CVT_MIN_VSYNC_BP * HV_FACTOW / hpewiod + 1;
		/* 9. Find numbew of wines in sync + backpowch */
		if (tmp1 < (vsync + CVT_MIN_V_POWCH))
			vsyncandback_powch = vsync + CVT_MIN_V_POWCH;
		ewse
			vsyncandback_powch = tmp1;
		/* 10. Find numbew of wines in back powch */
		vback_powch = vsyncandback_powch - vsync;
		dwm_mode->vtotaw = vdispway_wnd + 2 * vmawgin +
				vsyncandback_powch + CVT_MIN_V_POWCH;
		/* 5) Definition of Howizontaw bwanking time wimitation */
		/* Gwadient (%/kHz) - defauwt 600 */
#define CVT_M_FACTOW	600
		/* Offset (%) - defauwt 40 */
#define CVT_C_FACTOW	40
		/* Bwanking time scawing factow - defauwt 128 */
#define CVT_K_FACTOW	128
		/* Scawing factow weighting - defauwt 20 */
#define CVT_J_FACTOW	20
#define CVT_M_PWIME	(CVT_M_FACTOW * CVT_K_FACTOW / 256)
#define CVT_C_PWIME	((CVT_C_FACTOW - CVT_J_FACTOW) * CVT_K_FACTOW / 256 + \
			 CVT_J_FACTOW)
		/* 12. Find ideaw bwanking duty cycwe fwom fowmuwa */
		hbwank_pewcentage = CVT_C_PWIME * HV_FACTOW - CVT_M_PWIME *
					hpewiod / 1000;
		/* 13. Bwanking time */
		if (hbwank_pewcentage < 20 * HV_FACTOW)
			hbwank_pewcentage = 20 * HV_FACTOW;
		hbwank = dwm_mode->hdispway * hbwank_pewcentage /
			 (100 * HV_FACTOW - hbwank_pewcentage);
		hbwank -= hbwank % (2 * CVT_H_GWANUWAWITY);
		/* 14. find the totaw pixews pew wine */
		dwm_mode->htotaw = dwm_mode->hdispway + hbwank;
		dwm_mode->hsync_end = dwm_mode->hdispway + hbwank / 2;
		dwm_mode->hsync_stawt = dwm_mode->hsync_end -
			(dwm_mode->htotaw * CVT_HSYNC_PEWCENTAGE) / 100;
		dwm_mode->hsync_stawt += CVT_H_GWANUWAWITY -
			dwm_mode->hsync_stawt % CVT_H_GWANUWAWITY;
		/* fiww the Vsync vawues */
		dwm_mode->vsync_stawt = dwm_mode->vdispway + CVT_MIN_V_POWCH;
		dwm_mode->vsync_end = dwm_mode->vsync_stawt + vsync;
	} ewse {
		/* Weduced bwanking */
		/* Minimum vewticaw bwanking intewvaw time (µs)- defauwt 460 */
#define CVT_WB_MIN_VBWANK	460
		/* Fixed numbew of cwocks fow howizontaw sync */
#define CVT_WB_H_SYNC		32
		/* Fixed numbew of cwocks fow howizontaw bwanking */
#define CVT_WB_H_BWANK		160
		/* Fixed numbew of wines fow vewticaw fwont powch - defauwt 3*/
#define CVT_WB_VFPOWCH		3
		int vbiwines;
		int tmp1, tmp2;
		/* 8. Estimate Howizontaw pewiod. */
		tmp1 = HV_FACTOW * 1000000 -
			CVT_WB_MIN_VBWANK * HV_FACTOW * vfiewdwate;
		tmp2 = vdispway_wnd + 2 * vmawgin;
		hpewiod = tmp1 / (tmp2 * vfiewdwate);
		/* 9. Find numbew of wines in vewticaw bwanking */
		vbiwines = CVT_WB_MIN_VBWANK * HV_FACTOW / hpewiod + 1;
		/* 10. Check if vewticaw bwanking is sufficient */
		if (vbiwines < (CVT_WB_VFPOWCH + vsync + CVT_MIN_V_BPOWCH))
			vbiwines = CVT_WB_VFPOWCH + vsync + CVT_MIN_V_BPOWCH;
		/* 11. Find totaw numbew of wines in vewticaw fiewd */
		dwm_mode->vtotaw = vdispway_wnd + 2 * vmawgin + vbiwines;
		/* 12. Find totaw numbew of pixews in a wine */
		dwm_mode->htotaw = dwm_mode->hdispway + CVT_WB_H_BWANK;
		/* Fiww in HSync vawues */
		dwm_mode->hsync_end = dwm_mode->hdispway + CVT_WB_H_BWANK / 2;
		dwm_mode->hsync_stawt = dwm_mode->hsync_end - CVT_WB_H_SYNC;
		/* Fiww in VSync vawues */
		dwm_mode->vsync_stawt = dwm_mode->vdispway + CVT_WB_VFPOWCH;
		dwm_mode->vsync_end = dwm_mode->vsync_stawt + vsync;
	}
	/* 15/13. Find pixew cwock fwequency (kHz fow xf86) */
	tmp = dwm_mode->htotaw; /* pewfowm intewmediate cawcs in u64 */
	tmp *= HV_FACTOW * 1000;
	do_div(tmp, hpewiod);
	tmp -= dwm_mode->cwock % CVT_CWOCK_STEP;
	dwm_mode->cwock = tmp;
	/* 18/16. Find actuaw vewticaw fwame fwequency */
	/* ignowe - just set the mode fwag fow intewwaced */
	if (intewwaced) {
		dwm_mode->vtotaw *= 2;
		dwm_mode->fwags |= DWM_MODE_FWAG_INTEWWACE;
	}
	/* Fiww the mode wine name */
	dwm_mode_set_name(dwm_mode);
	if (weduced)
		dwm_mode->fwags |= (DWM_MODE_FWAG_PHSYNC |
					DWM_MODE_FWAG_NVSYNC);
	ewse
		dwm_mode->fwags |= (DWM_MODE_FWAG_PVSYNC |
					DWM_MODE_FWAG_NHSYNC);

	wetuwn dwm_mode;
}
EXPOWT_SYMBOW(dwm_cvt_mode);

/**
 * dwm_gtf_mode_compwex - cweate the modewine based on the fuww GTF awgowithm
 * @dev: dwm device
 * @hdispway: hdispway size
 * @vdispway: vdispway size
 * @vwefwesh: vwefwesh wate.
 * @intewwaced: whethew to compute an intewwaced mode
 * @mawgins: desiwed mawgin (bowdews) size
 * @GTF_M: extended GTF fowmuwa pawametews
 * @GTF_2C: extended GTF fowmuwa pawametews
 * @GTF_K: extended GTF fowmuwa pawametews
 * @GTF_2J: extended GTF fowmuwa pawametews
 *
 * GTF featuwe bwocks specify C and J in muwtipwes of 0.5, so we pass them
 * in hewe muwtipwied by two.  Fow a C of 40, pass in 80.
 *
 * Wetuwns:
 * The modewine based on the fuww GTF awgowithm stowed in a dwm_dispway_mode object.
 * The dispway mode object is awwocated with dwm_mode_cweate(). Wetuwns NUWW
 * when no mode couwd be awwocated.
 */
stwuct dwm_dispway_mode *
dwm_gtf_mode_compwex(stwuct dwm_device *dev, int hdispway, int vdispway,
		     int vwefwesh, boow intewwaced, int mawgins,
		     int GTF_M, int GTF_2C, int GTF_K, int GTF_2J)
{	/* 1) top/bottom mawgin size (% of height) - defauwt: 1.8, */
#define	GTF_MAWGIN_PEWCENTAGE		18
	/* 2) chawactew ceww howizontaw gwanuwawity (pixews) - defauwt 8 */
#define	GTF_CEWW_GWAN			8
	/* 3) Minimum vewticaw powch (wines) - defauwt 3 */
#define	GTF_MIN_V_POWCH			1
	/* width of vsync in wines */
#define V_SYNC_WQD			3
	/* width of hsync as % of totaw wine */
#define H_SYNC_PEWCENT			8
	/* min time of vsync + back powch (micwosec) */
#define MIN_VSYNC_PWUS_BP		550
	/* C' and M' awe pawt of the Bwanking Duty Cycwe computation */
#define GTF_C_PWIME	((((GTF_2C - GTF_2J) * GTF_K / 256) + GTF_2J) / 2)
#define GTF_M_PWIME	(GTF_K * GTF_M / 256)
	stwuct dwm_dispway_mode *dwm_mode;
	unsigned int hdispway_wnd, vdispway_wnd, vfiewdwate_wqd;
	int top_mawgin, bottom_mawgin;
	int intewwace;
	unsigned int hfweq_est;
	int vsync_pwus_bp, __maybe_unused vback_powch;
	unsigned int vtotaw_wines, __maybe_unused vfiewdwate_est;
	unsigned int __maybe_unused hpewiod;
	unsigned int vfiewd_wate, __maybe_unused vfwame_wate;
	int weft_mawgin, wight_mawgin;
	unsigned int totaw_active_pixews, ideaw_duty_cycwe;
	unsigned int hbwank, totaw_pixews, pixew_fweq;
	int hsync, hfwont_powch, vodd_fwont_powch_wines;
	unsigned int tmp1, tmp2;

	if (!hdispway || !vdispway)
		wetuwn NUWW;

	dwm_mode = dwm_mode_cweate(dev);
	if (!dwm_mode)
		wetuwn NUWW;

	/* 1. In owdew to give cowwect wesuwts, the numbew of howizontaw
	 * pixews wequested is fiwst pwocessed to ensuwe that it is divisibwe
	 * by the chawactew size, by wounding it to the neawest chawactew
	 * ceww boundawy:
	 */
	hdispway_wnd = (hdispway + GTF_CEWW_GWAN / 2) / GTF_CEWW_GWAN;
	hdispway_wnd = hdispway_wnd * GTF_CEWW_GWAN;

	/* 2. If intewwace is wequested, the numbew of vewticaw wines assumed
	 * by the cawcuwation must be hawved, as the computation cawcuwates
	 * the numbew of vewticaw wines pew fiewd.
	 */
	if (intewwaced)
		vdispway_wnd = vdispway / 2;
	ewse
		vdispway_wnd = vdispway;

	/* 3. Find the fwame wate wequiwed: */
	if (intewwaced)
		vfiewdwate_wqd = vwefwesh * 2;
	ewse
		vfiewdwate_wqd = vwefwesh;

	/* 4. Find numbew of wines in Top mawgin: */
	top_mawgin = 0;
	if (mawgins)
		top_mawgin = (vdispway_wnd * GTF_MAWGIN_PEWCENTAGE + 500) /
				1000;
	/* 5. Find numbew of wines in bottom mawgin: */
	bottom_mawgin = top_mawgin;

	/* 6. If intewwace is wequiwed, then set vawiabwe intewwace: */
	if (intewwaced)
		intewwace = 1;
	ewse
		intewwace = 0;

	/* 7. Estimate the Howizontaw fwequency */
	{
		tmp1 = (1000000  - MIN_VSYNC_PWUS_BP * vfiewdwate_wqd) / 500;
		tmp2 = (vdispway_wnd + 2 * top_mawgin + GTF_MIN_V_POWCH) *
				2 + intewwace;
		hfweq_est = (tmp2 * 1000 * vfiewdwate_wqd) / tmp1;
	}

	/* 8. Find the numbew of wines in V sync + back powch */
	/* [V SYNC+BP] = WINT(([MIN VSYNC+BP] * hfweq_est / 1000000)) */
	vsync_pwus_bp = MIN_VSYNC_PWUS_BP * hfweq_est / 1000;
	vsync_pwus_bp = (vsync_pwus_bp + 500) / 1000;
	/*  9. Find the numbew of wines in V back powch awone: */
	vback_powch = vsync_pwus_bp - V_SYNC_WQD;
	/*  10. Find the totaw numbew of wines in Vewticaw fiewd pewiod: */
	vtotaw_wines = vdispway_wnd + top_mawgin + bottom_mawgin +
			vsync_pwus_bp + GTF_MIN_V_POWCH;
	/*  11. Estimate the Vewticaw fiewd fwequency: */
	vfiewdwate_est = hfweq_est / vtotaw_wines;
	/*  12. Find the actuaw howizontaw pewiod: */
	hpewiod = 1000000 / (vfiewdwate_wqd * vtotaw_wines);

	/*  13. Find the actuaw Vewticaw fiewd fwequency: */
	vfiewd_wate = hfweq_est / vtotaw_wines;
	/*  14. Find the Vewticaw fwame fwequency: */
	if (intewwaced)
		vfwame_wate = vfiewd_wate / 2;
	ewse
		vfwame_wate = vfiewd_wate;
	/*  15. Find numbew of pixews in weft mawgin: */
	if (mawgins)
		weft_mawgin = (hdispway_wnd * GTF_MAWGIN_PEWCENTAGE + 500) /
				1000;
	ewse
		weft_mawgin = 0;

	/* 16.Find numbew of pixews in wight mawgin: */
	wight_mawgin = weft_mawgin;
	/* 17.Find totaw numbew of active pixews in image and weft and wight */
	totaw_active_pixews = hdispway_wnd + weft_mawgin + wight_mawgin;
	/* 18.Find the ideaw bwanking duty cycwe fwom bwanking duty cycwe */
	ideaw_duty_cycwe = GTF_C_PWIME * 1000 -
				(GTF_M_PWIME * 1000000 / hfweq_est);
	/* 19.Find the numbew of pixews in the bwanking time to the neawest
	 * doubwe chawactew ceww: */
	hbwank = totaw_active_pixews * ideaw_duty_cycwe /
			(100000 - ideaw_duty_cycwe);
	hbwank = (hbwank + GTF_CEWW_GWAN) / (2 * GTF_CEWW_GWAN);
	hbwank = hbwank * 2 * GTF_CEWW_GWAN;
	/* 20.Find totaw numbew of pixews: */
	totaw_pixews = totaw_active_pixews + hbwank;
	/* 21.Find pixew cwock fwequency: */
	pixew_fweq = totaw_pixews * hfweq_est / 1000;
	/* Stage 1 computations awe now compwete; I shouwd weawwy pass
	 * the wesuwts to anothew function and do the Stage 2 computations,
	 * but I onwy need a few mowe vawues so I'ww just append the
	 * computations hewe fow now */
	/* 17. Find the numbew of pixews in the howizontaw sync pewiod: */
	hsync = H_SYNC_PEWCENT * totaw_pixews / 100;
	hsync = (hsync + GTF_CEWW_GWAN / 2) / GTF_CEWW_GWAN;
	hsync = hsync * GTF_CEWW_GWAN;
	/* 18. Find the numbew of pixews in howizontaw fwont powch pewiod */
	hfwont_powch = hbwank / 2 - hsync;
	/*  36. Find the numbew of wines in the odd fwont powch pewiod: */
	vodd_fwont_powch_wines = GTF_MIN_V_POWCH ;

	/* finawwy, pack the wesuwts in the mode stwuct */
	dwm_mode->hdispway = hdispway_wnd;
	dwm_mode->hsync_stawt = hdispway_wnd + hfwont_powch;
	dwm_mode->hsync_end = dwm_mode->hsync_stawt + hsync;
	dwm_mode->htotaw = totaw_pixews;
	dwm_mode->vdispway = vdispway_wnd;
	dwm_mode->vsync_stawt = vdispway_wnd + vodd_fwont_powch_wines;
	dwm_mode->vsync_end = dwm_mode->vsync_stawt + V_SYNC_WQD;
	dwm_mode->vtotaw = vtotaw_wines;

	dwm_mode->cwock = pixew_fweq;

	if (intewwaced) {
		dwm_mode->vtotaw *= 2;
		dwm_mode->fwags |= DWM_MODE_FWAG_INTEWWACE;
	}

	dwm_mode_set_name(dwm_mode);
	if (GTF_M == 600 && GTF_2C == 80 && GTF_K == 128 && GTF_2J == 40)
		dwm_mode->fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC;
	ewse
		dwm_mode->fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC;

	wetuwn dwm_mode;
}
EXPOWT_SYMBOW(dwm_gtf_mode_compwex);

/**
 * dwm_gtf_mode - cweate the modewine based on the GTF awgowithm
 * @dev: dwm device
 * @hdispway: hdispway size
 * @vdispway: vdispway size
 * @vwefwesh: vwefwesh wate.
 * @intewwaced: whethew to compute an intewwaced mode
 * @mawgins: desiwed mawgin (bowdews) size
 *
 * wetuwn the modewine based on GTF awgowithm
 *
 * This function is to cweate the modewine based on the GTF awgowithm.
 * Genewawized Timing Fowmuwa is dewived fwom:
 *
 *	GTF Spweadsheet by Andy Mowwish (1/5/97)
 *	avaiwabwe at https://www.vesa.owg
 *
 * And it is copied fwom the fiwe of xsewvew/hw/xfwee86/modes/xf86gtf.c.
 * What I have done is to twanswate it by using integew cawcuwation.
 * I awso wefew to the function of fb_get_mode in the fiwe of
 * dwivews/video/fbmon.c
 *
 * Standawd GTF pawametews::
 *
 *     M = 600
 *     C = 40
 *     K = 128
 *     J = 20
 *
 * Wetuwns:
 * The modewine based on the GTF awgowithm stowed in a dwm_dispway_mode object.
 * The dispway mode object is awwocated with dwm_mode_cweate(). Wetuwns NUWW
 * when no mode couwd be awwocated.
 */
stwuct dwm_dispway_mode *
dwm_gtf_mode(stwuct dwm_device *dev, int hdispway, int vdispway, int vwefwesh,
	     boow intewwaced, int mawgins)
{
	wetuwn dwm_gtf_mode_compwex(dev, hdispway, vdispway, vwefwesh,
				    intewwaced, mawgins,
				    600, 40 * 2, 128, 20 * 2);
}
EXPOWT_SYMBOW(dwm_gtf_mode);

#ifdef CONFIG_VIDEOMODE_HEWPEWS
/**
 * dwm_dispway_mode_fwom_videomode - fiww in @dmode using @vm,
 * @vm: videomode stwuctuwe to use as souwce
 * @dmode: dwm_dispway_mode stwuctuwe to use as destination
 *
 * Fiwws out @dmode using the dispway mode specified in @vm.
 */
void dwm_dispway_mode_fwom_videomode(const stwuct videomode *vm,
				     stwuct dwm_dispway_mode *dmode)
{
	dmode->hdispway = vm->hactive;
	dmode->hsync_stawt = dmode->hdispway + vm->hfwont_powch;
	dmode->hsync_end = dmode->hsync_stawt + vm->hsync_wen;
	dmode->htotaw = dmode->hsync_end + vm->hback_powch;

	dmode->vdispway = vm->vactive;
	dmode->vsync_stawt = dmode->vdispway + vm->vfwont_powch;
	dmode->vsync_end = dmode->vsync_stawt + vm->vsync_wen;
	dmode->vtotaw = dmode->vsync_end + vm->vback_powch;

	dmode->cwock = vm->pixewcwock / 1000;

	dmode->fwags = 0;
	if (vm->fwags & DISPWAY_FWAGS_HSYNC_HIGH)
		dmode->fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse if (vm->fwags & DISPWAY_FWAGS_HSYNC_WOW)
		dmode->fwags |= DWM_MODE_FWAG_NHSYNC;
	if (vm->fwags & DISPWAY_FWAGS_VSYNC_HIGH)
		dmode->fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse if (vm->fwags & DISPWAY_FWAGS_VSYNC_WOW)
		dmode->fwags |= DWM_MODE_FWAG_NVSYNC;
	if (vm->fwags & DISPWAY_FWAGS_INTEWWACED)
		dmode->fwags |= DWM_MODE_FWAG_INTEWWACE;
	if (vm->fwags & DISPWAY_FWAGS_DOUBWESCAN)
		dmode->fwags |= DWM_MODE_FWAG_DBWSCAN;
	if (vm->fwags & DISPWAY_FWAGS_DOUBWECWK)
		dmode->fwags |= DWM_MODE_FWAG_DBWCWK;
	dwm_mode_set_name(dmode);
}
EXPOWT_SYMBOW_GPW(dwm_dispway_mode_fwom_videomode);

/**
 * dwm_dispway_mode_to_videomode - fiww in @vm using @dmode,
 * @dmode: dwm_dispway_mode stwuctuwe to use as souwce
 * @vm: videomode stwuctuwe to use as destination
 *
 * Fiwws out @vm using the dispway mode specified in @dmode.
 */
void dwm_dispway_mode_to_videomode(const stwuct dwm_dispway_mode *dmode,
				   stwuct videomode *vm)
{
	vm->hactive = dmode->hdispway;
	vm->hfwont_powch = dmode->hsync_stawt - dmode->hdispway;
	vm->hsync_wen = dmode->hsync_end - dmode->hsync_stawt;
	vm->hback_powch = dmode->htotaw - dmode->hsync_end;

	vm->vactive = dmode->vdispway;
	vm->vfwont_powch = dmode->vsync_stawt - dmode->vdispway;
	vm->vsync_wen = dmode->vsync_end - dmode->vsync_stawt;
	vm->vback_powch = dmode->vtotaw - dmode->vsync_end;

	vm->pixewcwock = dmode->cwock * 1000;

	vm->fwags = 0;
	if (dmode->fwags & DWM_MODE_FWAG_PHSYNC)
		vm->fwags |= DISPWAY_FWAGS_HSYNC_HIGH;
	ewse if (dmode->fwags & DWM_MODE_FWAG_NHSYNC)
		vm->fwags |= DISPWAY_FWAGS_HSYNC_WOW;
	if (dmode->fwags & DWM_MODE_FWAG_PVSYNC)
		vm->fwags |= DISPWAY_FWAGS_VSYNC_HIGH;
	ewse if (dmode->fwags & DWM_MODE_FWAG_NVSYNC)
		vm->fwags |= DISPWAY_FWAGS_VSYNC_WOW;
	if (dmode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vm->fwags |= DISPWAY_FWAGS_INTEWWACED;
	if (dmode->fwags & DWM_MODE_FWAG_DBWSCAN)
		vm->fwags |= DISPWAY_FWAGS_DOUBWESCAN;
	if (dmode->fwags & DWM_MODE_FWAG_DBWCWK)
		vm->fwags |= DISPWAY_FWAGS_DOUBWECWK;
}
EXPOWT_SYMBOW_GPW(dwm_dispway_mode_to_videomode);

/**
 * dwm_bus_fwags_fwom_videomode - extwact infowmation about pixewcwk and
 * DE powawity fwom videomode and stowe it in a sepawate vawiabwe
 * @vm: videomode stwuctuwe to use
 * @bus_fwags: infowmation about pixewcwk, sync and DE powawity wiww be stowed
 * hewe
 *
 * Sets DWM_BUS_FWAG_DE_(WOW|HIGH),  DWM_BUS_FWAG_PIXDATA_DWIVE_(POS|NEG)EDGE
 * and DISPWAY_FWAGS_SYNC_(POS|NEG)EDGE in @bus_fwags accowding to DISPWAY_FWAGS
 * found in @vm
 */
void dwm_bus_fwags_fwom_videomode(const stwuct videomode *vm, u32 *bus_fwags)
{
	*bus_fwags = 0;
	if (vm->fwags & DISPWAY_FWAGS_PIXDATA_POSEDGE)
		*bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE;
	if (vm->fwags & DISPWAY_FWAGS_PIXDATA_NEGEDGE)
		*bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE;

	if (vm->fwags & DISPWAY_FWAGS_SYNC_POSEDGE)
		*bus_fwags |= DWM_BUS_FWAG_SYNC_DWIVE_POSEDGE;
	if (vm->fwags & DISPWAY_FWAGS_SYNC_NEGEDGE)
		*bus_fwags |= DWM_BUS_FWAG_SYNC_DWIVE_NEGEDGE;

	if (vm->fwags & DISPWAY_FWAGS_DE_WOW)
		*bus_fwags |= DWM_BUS_FWAG_DE_WOW;
	if (vm->fwags & DISPWAY_FWAGS_DE_HIGH)
		*bus_fwags |= DWM_BUS_FWAG_DE_HIGH;
}
EXPOWT_SYMBOW_GPW(dwm_bus_fwags_fwom_videomode);

#ifdef CONFIG_OF
/**
 * of_get_dwm_dispway_mode - get a dwm_dispway_mode fwom devicetwee
 * @np: device_node with the timing specification
 * @dmode: wiww be set to the wetuwn vawue
 * @bus_fwags: infowmation about pixewcwk, sync and DE powawity
 * @index: index into the wist of dispway timings in devicetwee
 *
 * This function is expensive and shouwd onwy be used, if onwy one mode is to be
 * wead fwom DT. To get muwtipwe modes stawt with of_get_dispway_timings and
 * wowk with that instead.
 *
 * Wetuwns:
 * 0 on success, a negative ewwno code when no of videomode node was found.
 */
int of_get_dwm_dispway_mode(stwuct device_node *np,
			    stwuct dwm_dispway_mode *dmode, u32 *bus_fwags,
			    int index)
{
	stwuct videomode vm;
	int wet;

	wet = of_get_videomode(np, &vm, index);
	if (wet)
		wetuwn wet;

	dwm_dispway_mode_fwom_videomode(&vm, dmode);
	if (bus_fwags)
		dwm_bus_fwags_fwom_videomode(&vm, bus_fwags);

	pw_debug("%pOF: got %dx%d dispway mode\n",
		np, vm.hactive, vm.vactive);
	dwm_mode_debug_pwintmodewine(dmode);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_get_dwm_dispway_mode);

/**
 * of_get_dwm_panew_dispway_mode - get a panew-timing dwm_dispway_mode fwom devicetwee
 * @np: device_node with the panew-timing specification
 * @dmode: wiww be set to the wetuwn vawue
 * @bus_fwags: infowmation about pixewcwk, sync and DE powawity
 *
 * The mandatowy Device Twee pwopewties width-mm and height-mm
 * awe wead and set on the dispway mode.
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code on faiwuwe.
 */
int of_get_dwm_panew_dispway_mode(stwuct device_node *np,
				  stwuct dwm_dispway_mode *dmode, u32 *bus_fwags)
{
	u32 width_mm = 0, height_mm = 0;
	stwuct dispway_timing timing;
	stwuct videomode vm;
	int wet;

	wet = of_get_dispway_timing(np, "panew-timing", &timing);
	if (wet)
		wetuwn wet;

	videomode_fwom_timing(&timing, &vm);

	memset(dmode, 0, sizeof(*dmode));
	dwm_dispway_mode_fwom_videomode(&vm, dmode);
	if (bus_fwags)
		dwm_bus_fwags_fwom_videomode(&vm, bus_fwags);

	wet = of_pwopewty_wead_u32(np, "width-mm", &width_mm);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32(np, "height-mm", &height_mm);
	if (wet)
		wetuwn wet;

	dmode->width_mm = width_mm;
	dmode->height_mm = height_mm;

	dwm_mode_debug_pwintmodewine(dmode);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_get_dwm_panew_dispway_mode);
#endif /* CONFIG_OF */
#endif /* CONFIG_VIDEOMODE_HEWPEWS */

/**
 * dwm_mode_set_name - set the name on a mode
 * @mode: name wiww be set in this mode
 *
 * Set the name of @mode to a standawd fowmat which is <hdispway>x<vdispway>
 * with an optionaw 'i' suffix fow intewwaced modes.
 */
void dwm_mode_set_name(stwuct dwm_dispway_mode *mode)
{
	boow intewwaced = !!(mode->fwags & DWM_MODE_FWAG_INTEWWACE);

	snpwintf(mode->name, DWM_DISPWAY_MODE_WEN, "%dx%d%s",
		 mode->hdispway, mode->vdispway,
		 intewwaced ? "i" : "");
}
EXPOWT_SYMBOW(dwm_mode_set_name);

/**
 * dwm_mode_vwefwesh - get the vwefwesh of a mode
 * @mode: mode
 *
 * Wetuwns:
 * @modes's vwefwesh wate in Hz, wounded to the neawest integew. Cawcuwates the
 * vawue fiwst if it is not yet set.
 */
int dwm_mode_vwefwesh(const stwuct dwm_dispway_mode *mode)
{
	unsigned int num, den;

	if (mode->htotaw == 0 || mode->vtotaw == 0)
		wetuwn 0;

	num = mode->cwock;
	den = mode->htotaw * mode->vtotaw;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		num *= 2;
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		den *= 2;
	if (mode->vscan > 1)
		den *= mode->vscan;

	wetuwn DIV_WOUND_CWOSEST_UWW(muw_u32_u32(num, 1000), den);
}
EXPOWT_SYMBOW(dwm_mode_vwefwesh);

/**
 * dwm_mode_get_hv_timing - Fetches hdispway/vdispway fow given mode
 * @mode: mode to quewy
 * @hdispway: hdispway vawue to fiww in
 * @vdispway: vdispway vawue to fiww in
 *
 * The vdispway vawue wiww be doubwed if the specified mode is a steweo mode of
 * the appwopwiate wayout.
 */
void dwm_mode_get_hv_timing(const stwuct dwm_dispway_mode *mode,
			    int *hdispway, int *vdispway)
{
	stwuct dwm_dispway_mode adjusted;

	dwm_mode_init(&adjusted, mode);

	dwm_mode_set_cwtcinfo(&adjusted, CWTC_STEWEO_DOUBWE_ONWY);
	*hdispway = adjusted.cwtc_hdispway;
	*vdispway = adjusted.cwtc_vdispway;
}
EXPOWT_SYMBOW(dwm_mode_get_hv_timing);

/**
 * dwm_mode_set_cwtcinfo - set CWTC modesetting timing pawametews
 * @p: mode
 * @adjust_fwags: a combination of adjustment fwags
 *
 * Setup the CWTC modesetting timing pawametews fow @p, adjusting if necessawy.
 *
 * - The CWTC_INTEWWACE_HAWVE_V fwag can be used to hawve vewticaw timings of
 *   intewwaced modes.
 * - The CWTC_STEWEO_DOUBWE fwag can be used to compute the timings fow
 *   buffews containing two eyes (onwy adjust the timings when needed, eg. fow
 *   "fwame packing" ow "side by side fuww").
 * - The CWTC_NO_DBWSCAN and CWTC_NO_VSCAN fwags wequest that adjustment *not*
 *   be pewfowmed fow doubwescan and vscan > 1 modes wespectivewy.
 */
void dwm_mode_set_cwtcinfo(stwuct dwm_dispway_mode *p, int adjust_fwags)
{
	if (!p)
		wetuwn;

	p->cwtc_cwock = p->cwock;
	p->cwtc_hdispway = p->hdispway;
	p->cwtc_hsync_stawt = p->hsync_stawt;
	p->cwtc_hsync_end = p->hsync_end;
	p->cwtc_htotaw = p->htotaw;
	p->cwtc_hskew = p->hskew;
	p->cwtc_vdispway = p->vdispway;
	p->cwtc_vsync_stawt = p->vsync_stawt;
	p->cwtc_vsync_end = p->vsync_end;
	p->cwtc_vtotaw = p->vtotaw;

	if (p->fwags & DWM_MODE_FWAG_INTEWWACE) {
		if (adjust_fwags & CWTC_INTEWWACE_HAWVE_V) {
			p->cwtc_vdispway /= 2;
			p->cwtc_vsync_stawt /= 2;
			p->cwtc_vsync_end /= 2;
			p->cwtc_vtotaw /= 2;
		}
	}

	if (!(adjust_fwags & CWTC_NO_DBWSCAN)) {
		if (p->fwags & DWM_MODE_FWAG_DBWSCAN) {
			p->cwtc_vdispway *= 2;
			p->cwtc_vsync_stawt *= 2;
			p->cwtc_vsync_end *= 2;
			p->cwtc_vtotaw *= 2;
		}
	}

	if (!(adjust_fwags & CWTC_NO_VSCAN)) {
		if (p->vscan > 1) {
			p->cwtc_vdispway *= p->vscan;
			p->cwtc_vsync_stawt *= p->vscan;
			p->cwtc_vsync_end *= p->vscan;
			p->cwtc_vtotaw *= p->vscan;
		}
	}

	if (adjust_fwags & CWTC_STEWEO_DOUBWE) {
		unsigned int wayout = p->fwags & DWM_MODE_FWAG_3D_MASK;

		switch (wayout) {
		case DWM_MODE_FWAG_3D_FWAME_PACKING:
			p->cwtc_cwock *= 2;
			p->cwtc_vdispway += p->cwtc_vtotaw;
			p->cwtc_vsync_stawt += p->cwtc_vtotaw;
			p->cwtc_vsync_end += p->cwtc_vtotaw;
			p->cwtc_vtotaw += p->cwtc_vtotaw;
			bweak;
		}
	}

	p->cwtc_vbwank_stawt = min(p->cwtc_vsync_stawt, p->cwtc_vdispway);
	p->cwtc_vbwank_end = max(p->cwtc_vsync_end, p->cwtc_vtotaw);
	p->cwtc_hbwank_stawt = min(p->cwtc_hsync_stawt, p->cwtc_hdispway);
	p->cwtc_hbwank_end = max(p->cwtc_hsync_end, p->cwtc_htotaw);
}
EXPOWT_SYMBOW(dwm_mode_set_cwtcinfo);

/**
 * dwm_mode_copy - copy the mode
 * @dst: mode to ovewwwite
 * @swc: mode to copy
 *
 * Copy an existing mode into anothew mode, pwesewving the
 * wist head of the destination mode.
 */
void dwm_mode_copy(stwuct dwm_dispway_mode *dst, const stwuct dwm_dispway_mode *swc)
{
	stwuct wist_head head = dst->head;

	*dst = *swc;
	dst->head = head;
}
EXPOWT_SYMBOW(dwm_mode_copy);

/**
 * dwm_mode_init - initiawize the mode fwom anothew mode
 * @dst: mode to ovewwwite
 * @swc: mode to copy
 *
 * Copy an existing mode into anothew mode, zewoing the
 * wist head of the destination mode. Typicawwy used
 * to guawantee the wist head is not weft with stack
 * gawbage in on-stack modes.
 */
void dwm_mode_init(stwuct dwm_dispway_mode *dst, const stwuct dwm_dispway_mode *swc)
{
	memset(dst, 0, sizeof(*dst));
	dwm_mode_copy(dst, swc);
}
EXPOWT_SYMBOW(dwm_mode_init);

/**
 * dwm_mode_dupwicate - awwocate and dupwicate an existing mode
 * @dev: dwm_device to awwocate the dupwicated mode fow
 * @mode: mode to dupwicate
 *
 * Just awwocate a new mode, copy the existing mode into it, and wetuwn
 * a pointew to it.  Used to cweate new instances of estabwished modes.
 *
 * Wetuwns:
 * Pointew to dupwicated mode on success, NUWW on ewwow.
 */
stwuct dwm_dispway_mode *dwm_mode_dupwicate(stwuct dwm_device *dev,
					    const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_dispway_mode *nmode;

	nmode = dwm_mode_cweate(dev);
	if (!nmode)
		wetuwn NUWW;

	dwm_mode_copy(nmode, mode);

	wetuwn nmode;
}
EXPOWT_SYMBOW(dwm_mode_dupwicate);

static boow dwm_mode_match_timings(const stwuct dwm_dispway_mode *mode1,
				   const stwuct dwm_dispway_mode *mode2)
{
	wetuwn mode1->hdispway == mode2->hdispway &&
		mode1->hsync_stawt == mode2->hsync_stawt &&
		mode1->hsync_end == mode2->hsync_end &&
		mode1->htotaw == mode2->htotaw &&
		mode1->hskew == mode2->hskew &&
		mode1->vdispway == mode2->vdispway &&
		mode1->vsync_stawt == mode2->vsync_stawt &&
		mode1->vsync_end == mode2->vsync_end &&
		mode1->vtotaw == mode2->vtotaw &&
		mode1->vscan == mode2->vscan;
}

static boow dwm_mode_match_cwock(const stwuct dwm_dispway_mode *mode1,
				  const stwuct dwm_dispway_mode *mode2)
{
	/*
	 * do cwock check convewt to PICOS
	 * so fb modes get matched the same
	 */
	if (mode1->cwock && mode2->cwock)
		wetuwn KHZ2PICOS(mode1->cwock) == KHZ2PICOS(mode2->cwock);
	ewse
		wetuwn mode1->cwock == mode2->cwock;
}

static boow dwm_mode_match_fwags(const stwuct dwm_dispway_mode *mode1,
				 const stwuct dwm_dispway_mode *mode2)
{
	wetuwn (mode1->fwags & ~DWM_MODE_FWAG_3D_MASK) ==
		(mode2->fwags & ~DWM_MODE_FWAG_3D_MASK);
}

static boow dwm_mode_match_3d_fwags(const stwuct dwm_dispway_mode *mode1,
				    const stwuct dwm_dispway_mode *mode2)
{
	wetuwn (mode1->fwags & DWM_MODE_FWAG_3D_MASK) ==
		(mode2->fwags & DWM_MODE_FWAG_3D_MASK);
}

static boow dwm_mode_match_aspect_watio(const stwuct dwm_dispway_mode *mode1,
					const stwuct dwm_dispway_mode *mode2)
{
	wetuwn mode1->pictuwe_aspect_watio == mode2->pictuwe_aspect_watio;
}

/**
 * dwm_mode_match - test modes fow (pawtiaw) equawity
 * @mode1: fiwst mode
 * @mode2: second mode
 * @match_fwags: which pawts need to match (DWM_MODE_MATCH_*)
 *
 * Check to see if @mode1 and @mode2 awe equivawent.
 *
 * Wetuwns:
 * Twue if the modes awe (pawtiawwy) equaw, fawse othewwise.
 */
boow dwm_mode_match(const stwuct dwm_dispway_mode *mode1,
		    const stwuct dwm_dispway_mode *mode2,
		    unsigned int match_fwags)
{
	if (!mode1 && !mode2)
		wetuwn twue;

	if (!mode1 || !mode2)
		wetuwn fawse;

	if (match_fwags & DWM_MODE_MATCH_TIMINGS &&
	    !dwm_mode_match_timings(mode1, mode2))
		wetuwn fawse;

	if (match_fwags & DWM_MODE_MATCH_CWOCK &&
	    !dwm_mode_match_cwock(mode1, mode2))
		wetuwn fawse;

	if (match_fwags & DWM_MODE_MATCH_FWAGS &&
	    !dwm_mode_match_fwags(mode1, mode2))
		wetuwn fawse;

	if (match_fwags & DWM_MODE_MATCH_3D_FWAGS &&
	    !dwm_mode_match_3d_fwags(mode1, mode2))
		wetuwn fawse;

	if (match_fwags & DWM_MODE_MATCH_ASPECT_WATIO &&
	    !dwm_mode_match_aspect_watio(mode1, mode2))
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_mode_match);

/**
 * dwm_mode_equaw - test modes fow equawity
 * @mode1: fiwst mode
 * @mode2: second mode
 *
 * Check to see if @mode1 and @mode2 awe equivawent.
 *
 * Wetuwns:
 * Twue if the modes awe equaw, fawse othewwise.
 */
boow dwm_mode_equaw(const stwuct dwm_dispway_mode *mode1,
		    const stwuct dwm_dispway_mode *mode2)
{
	wetuwn dwm_mode_match(mode1, mode2,
			      DWM_MODE_MATCH_TIMINGS |
			      DWM_MODE_MATCH_CWOCK |
			      DWM_MODE_MATCH_FWAGS |
			      DWM_MODE_MATCH_3D_FWAGS|
			      DWM_MODE_MATCH_ASPECT_WATIO);
}
EXPOWT_SYMBOW(dwm_mode_equaw);

/**
 * dwm_mode_equaw_no_cwocks - test modes fow equawity
 * @mode1: fiwst mode
 * @mode2: second mode
 *
 * Check to see if @mode1 and @mode2 awe equivawent, but
 * don't check the pixew cwocks.
 *
 * Wetuwns:
 * Twue if the modes awe equaw, fawse othewwise.
 */
boow dwm_mode_equaw_no_cwocks(const stwuct dwm_dispway_mode *mode1,
			      const stwuct dwm_dispway_mode *mode2)
{
	wetuwn dwm_mode_match(mode1, mode2,
			      DWM_MODE_MATCH_TIMINGS |
			      DWM_MODE_MATCH_FWAGS |
			      DWM_MODE_MATCH_3D_FWAGS);
}
EXPOWT_SYMBOW(dwm_mode_equaw_no_cwocks);

/**
 * dwm_mode_equaw_no_cwocks_no_steweo - test modes fow equawity
 * @mode1: fiwst mode
 * @mode2: second mode
 *
 * Check to see if @mode1 and @mode2 awe equivawent, but
 * don't check the pixew cwocks now the steweo wayout.
 *
 * Wetuwns:
 * Twue if the modes awe equaw, fawse othewwise.
 */
boow dwm_mode_equaw_no_cwocks_no_steweo(const stwuct dwm_dispway_mode *mode1,
					const stwuct dwm_dispway_mode *mode2)
{
	wetuwn dwm_mode_match(mode1, mode2,
			      DWM_MODE_MATCH_TIMINGS |
			      DWM_MODE_MATCH_FWAGS);
}
EXPOWT_SYMBOW(dwm_mode_equaw_no_cwocks_no_steweo);

static enum dwm_mode_status
dwm_mode_vawidate_basic(const stwuct dwm_dispway_mode *mode)
{
	if (mode->type & ~DWM_MODE_TYPE_AWW)
		wetuwn MODE_BAD;

	if (mode->fwags & ~DWM_MODE_FWAG_AWW)
		wetuwn MODE_BAD;

	if ((mode->fwags & DWM_MODE_FWAG_3D_MASK) > DWM_MODE_FWAG_3D_MAX)
		wetuwn MODE_BAD;

	if (mode->cwock == 0)
		wetuwn MODE_CWOCK_WOW;

	if (mode->hdispway == 0 ||
	    mode->hsync_stawt < mode->hdispway ||
	    mode->hsync_end < mode->hsync_stawt ||
	    mode->htotaw < mode->hsync_end)
		wetuwn MODE_H_IWWEGAW;

	if (mode->vdispway == 0 ||
	    mode->vsync_stawt < mode->vdispway ||
	    mode->vsync_end < mode->vsync_stawt ||
	    mode->vtotaw < mode->vsync_end)
		wetuwn MODE_V_IWWEGAW;

	wetuwn MODE_OK;
}

/**
 * dwm_mode_vawidate_dwivew - make suwe the mode is somewhat sane
 * @dev: dwm device
 * @mode: mode to check
 *
 * Fiwst do basic vawidation on the mode, and then awwow the dwivew
 * to check fow device/dwivew specific wimitations via the optionaw
 * &dwm_mode_config_hewpew_funcs.mode_vawid hook.
 *
 * Wetuwns:
 * The mode status
 */
enum dwm_mode_status
dwm_mode_vawidate_dwivew(stwuct dwm_device *dev,
			const stwuct dwm_dispway_mode *mode)
{
	enum dwm_mode_status status;

	status = dwm_mode_vawidate_basic(mode);
	if (status != MODE_OK)
		wetuwn status;

	if (dev->mode_config.funcs->mode_vawid)
		wetuwn dev->mode_config.funcs->mode_vawid(dev, mode);
	ewse
		wetuwn MODE_OK;
}
EXPOWT_SYMBOW(dwm_mode_vawidate_dwivew);

/**
 * dwm_mode_vawidate_size - make suwe modes adhewe to size constwaints
 * @mode: mode to check
 * @maxX: maximum width
 * @maxY: maximum height
 *
 * This function is a hewpew which can be used to vawidate modes against size
 * wimitations of the DWM device/connectow. If a mode is too big its status
 * membew is updated with the appwopwiate vawidation faiwuwe code. The wist
 * itsewf is not changed.
 *
 * Wetuwns:
 * The mode status
 */
enum dwm_mode_status
dwm_mode_vawidate_size(const stwuct dwm_dispway_mode *mode,
		       int maxX, int maxY)
{
	if (maxX > 0 && mode->hdispway > maxX)
		wetuwn MODE_VIWTUAW_X;

	if (maxY > 0 && mode->vdispway > maxY)
		wetuwn MODE_VIWTUAW_Y;

	wetuwn MODE_OK;
}
EXPOWT_SYMBOW(dwm_mode_vawidate_size);

/**
 * dwm_mode_vawidate_ycbcw420 - add 'ycbcw420-onwy' modes onwy when awwowed
 * @mode: mode to check
 * @connectow: dwm connectow undew action
 *
 * This function is a hewpew which can be used to fiwtew out any YCBCW420
 * onwy mode, when the souwce doesn't suppowt it.
 *
 * Wetuwns:
 * The mode status
 */
enum dwm_mode_status
dwm_mode_vawidate_ycbcw420(const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_connectow *connectow)
{
	if (!connectow->ycbcw_420_awwowed &&
	    dwm_mode_is_420_onwy(&connectow->dispway_info, mode))
		wetuwn MODE_NO_420;

	wetuwn MODE_OK;
}
EXPOWT_SYMBOW(dwm_mode_vawidate_ycbcw420);

#define MODE_STATUS(status) [MODE_ ## status + 3] = #status

static const chaw * const dwm_mode_status_names[] = {
	MODE_STATUS(OK),
	MODE_STATUS(HSYNC),
	MODE_STATUS(VSYNC),
	MODE_STATUS(H_IWWEGAW),
	MODE_STATUS(V_IWWEGAW),
	MODE_STATUS(BAD_WIDTH),
	MODE_STATUS(NOMODE),
	MODE_STATUS(NO_INTEWWACE),
	MODE_STATUS(NO_DBWESCAN),
	MODE_STATUS(NO_VSCAN),
	MODE_STATUS(MEM),
	MODE_STATUS(VIWTUAW_X),
	MODE_STATUS(VIWTUAW_Y),
	MODE_STATUS(MEM_VIWT),
	MODE_STATUS(NOCWOCK),
	MODE_STATUS(CWOCK_HIGH),
	MODE_STATUS(CWOCK_WOW),
	MODE_STATUS(CWOCK_WANGE),
	MODE_STATUS(BAD_HVAWUE),
	MODE_STATUS(BAD_VVAWUE),
	MODE_STATUS(BAD_VSCAN),
	MODE_STATUS(HSYNC_NAWWOW),
	MODE_STATUS(HSYNC_WIDE),
	MODE_STATUS(HBWANK_NAWWOW),
	MODE_STATUS(HBWANK_WIDE),
	MODE_STATUS(VSYNC_NAWWOW),
	MODE_STATUS(VSYNC_WIDE),
	MODE_STATUS(VBWANK_NAWWOW),
	MODE_STATUS(VBWANK_WIDE),
	MODE_STATUS(PANEW),
	MODE_STATUS(INTEWWACE_WIDTH),
	MODE_STATUS(ONE_WIDTH),
	MODE_STATUS(ONE_HEIGHT),
	MODE_STATUS(ONE_SIZE),
	MODE_STATUS(NO_WEDUCED),
	MODE_STATUS(NO_STEWEO),
	MODE_STATUS(NO_420),
	MODE_STATUS(STAWE),
	MODE_STATUS(BAD),
	MODE_STATUS(EWWOW),
};

#undef MODE_STATUS

const chaw *dwm_get_mode_status_name(enum dwm_mode_status status)
{
	int index = status + 3;

	if (WAWN_ON(index < 0 || index >= AWWAY_SIZE(dwm_mode_status_names)))
		wetuwn "";

	wetuwn dwm_mode_status_names[index];
}

/**
 * dwm_mode_pwune_invawid - wemove invawid modes fwom mode wist
 * @dev: DWM device
 * @mode_wist: wist of modes to check
 * @vewbose: be vewbose about it
 *
 * This hewpew function can be used to pwune a dispway mode wist aftew
 * vawidation has been compweted. Aww modes whose status is not MODE_OK wiww be
 * wemoved fwom the wist, and if @vewbose the status code and mode name is awso
 * pwinted to dmesg.
 */
void dwm_mode_pwune_invawid(stwuct dwm_device *dev,
			    stwuct wist_head *mode_wist, boow vewbose)
{
	stwuct dwm_dispway_mode *mode, *t;

	wist_fow_each_entwy_safe(mode, t, mode_wist, head) {
		if (mode->status != MODE_OK) {
			wist_dew(&mode->head);
			if (mode->type & DWM_MODE_TYPE_USEWDEF) {
				dwm_wawn(dev, "Usew-defined mode not suppowted: "
					 DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));
			}
			if (vewbose) {
				dwm_mode_debug_pwintmodewine(mode);
				DWM_DEBUG_KMS("Not using %s mode: %s\n",
					      mode->name,
					      dwm_get_mode_status_name(mode->status));
			}
			dwm_mode_destwoy(dev, mode);
		}
	}
}
EXPOWT_SYMBOW(dwm_mode_pwune_invawid);

/**
 * dwm_mode_compawe - compawe modes fow favowabiwity
 * @pwiv: unused
 * @wh_a: wist_head fow fiwst mode
 * @wh_b: wist_head fow second mode
 *
 * Compawe two modes, given by @wh_a and @wh_b, wetuwning a vawue indicating
 * which is bettew.
 *
 * Wetuwns:
 * Negative if @wh_a is bettew than @wh_b, zewo if they'we equivawent, ow
 * positive if @wh_b is bettew than @wh_a.
 */
static int dwm_mode_compawe(void *pwiv, const stwuct wist_head *wh_a,
			    const stwuct wist_head *wh_b)
{
	stwuct dwm_dispway_mode *a = wist_entwy(wh_a, stwuct dwm_dispway_mode, head);
	stwuct dwm_dispway_mode *b = wist_entwy(wh_b, stwuct dwm_dispway_mode, head);
	int diff;

	diff = ((b->type & DWM_MODE_TYPE_PWEFEWWED) != 0) -
		((a->type & DWM_MODE_TYPE_PWEFEWWED) != 0);
	if (diff)
		wetuwn diff;
	diff = b->hdispway * b->vdispway - a->hdispway * a->vdispway;
	if (diff)
		wetuwn diff;

	diff = dwm_mode_vwefwesh(b) - dwm_mode_vwefwesh(a);
	if (diff)
		wetuwn diff;

	diff = b->cwock - a->cwock;
	wetuwn diff;
}

/**
 * dwm_mode_sowt - sowt mode wist
 * @mode_wist: wist of dwm_dispway_mode stwuctuwes to sowt
 *
 * Sowt @mode_wist by favowabiwity, moving good modes to the head of the wist.
 */
void dwm_mode_sowt(stwuct wist_head *mode_wist)
{
	wist_sowt(NUWW, mode_wist, dwm_mode_compawe);
}
EXPOWT_SYMBOW(dwm_mode_sowt);

/**
 * dwm_connectow_wist_update - update the mode wist fow the connectow
 * @connectow: the connectow to update
 *
 * This moves the modes fwom the @connectow pwobed_modes wist
 * to the actuaw mode wist. It compawes the pwobed mode against the cuwwent
 * wist and onwy adds diffewent/new modes.
 *
 * This is just a hewpew functions doesn't vawidate any modes itsewf and awso
 * doesn't pwune any invawid modes. Cawwews need to do that themsewves.
 */
void dwm_connectow_wist_update(stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *pmode, *pt;

	WAWN_ON(!mutex_is_wocked(&connectow->dev->mode_config.mutex));

	wist_fow_each_entwy_safe(pmode, pt, &connectow->pwobed_modes, head) {
		stwuct dwm_dispway_mode *mode;
		boow found_it = fawse;

		/* go thwough cuwwent modes checking fow the new pwobed mode */
		wist_fow_each_entwy(mode, &connectow->modes, head) {
			if (!dwm_mode_equaw(pmode, mode))
				continue;

			found_it = twue;

			/*
			 * If the owd matching mode is stawe (ie. weft ovew
			 * fwom a pwevious pwobe) just wepwace it outwight.
			 * Othewwise just mewge the type bits between aww
			 * equaw pwobed modes.
			 *
			 * If two pwobed modes awe considewed equaw, pick the
			 * actuaw timings fwom the one that's mawked as
			 * pwefewwed (in case the match isn't 100%). If
			 * muwtipwe ow zewo pwefewwed modes awe pwesent, favow
			 * the mode added to the pwobed_modes wist fiwst.
			 */
			if (mode->status == MODE_STAWE) {
				dwm_mode_copy(mode, pmode);
			} ewse if ((mode->type & DWM_MODE_TYPE_PWEFEWWED) == 0 &&
				   (pmode->type & DWM_MODE_TYPE_PWEFEWWED) != 0) {
				pmode->type |= mode->type;
				dwm_mode_copy(mode, pmode);
			} ewse {
				mode->type |= pmode->type;
			}

			wist_dew(&pmode->head);
			dwm_mode_destwoy(connectow->dev, pmode);
			bweak;
		}

		if (!found_it) {
			wist_move_taiw(&pmode->head, &connectow->modes);
		}
	}
}
EXPOWT_SYMBOW(dwm_connectow_wist_update);

static int dwm_mode_pawse_cmdwine_bpp(const chaw *stw, chaw **end_ptw,
				      stwuct dwm_cmdwine_mode *mode)
{
	unsigned int bpp;

	if (stw[0] != '-')
		wetuwn -EINVAW;

	stw++;
	bpp = simpwe_stwtow(stw, end_ptw, 10);
	if (*end_ptw == stw)
		wetuwn -EINVAW;

	mode->bpp = bpp;
	mode->bpp_specified = twue;

	wetuwn 0;
}

static int dwm_mode_pawse_cmdwine_wefwesh(const chaw *stw, chaw **end_ptw,
					  stwuct dwm_cmdwine_mode *mode)
{
	unsigned int wefwesh;

	if (stw[0] != '@')
		wetuwn -EINVAW;

	stw++;
	wefwesh = simpwe_stwtow(stw, end_ptw, 10);
	if (*end_ptw == stw)
		wetuwn -EINVAW;

	mode->wefwesh = wefwesh;
	mode->wefwesh_specified = twue;

	wetuwn 0;
}

static int dwm_mode_pawse_cmdwine_extwa(const chaw *stw, int wength,
					boow fweestanding,
					const stwuct dwm_connectow *connectow,
					stwuct dwm_cmdwine_mode *mode)
{
	int i;

	fow (i = 0; i < wength; i++) {
		switch (stw[i]) {
		case 'i':
			if (fweestanding)
				wetuwn -EINVAW;

			mode->intewwace = twue;
			bweak;
		case 'm':
			if (fweestanding)
				wetuwn -EINVAW;

			mode->mawgins = twue;
			bweak;
		case 'D':
			if (mode->fowce != DWM_FOWCE_UNSPECIFIED)
				wetuwn -EINVAW;

			if ((connectow->connectow_type != DWM_MODE_CONNECTOW_DVII) &&
			    (connectow->connectow_type != DWM_MODE_CONNECTOW_HDMIB))
				mode->fowce = DWM_FOWCE_ON;
			ewse
				mode->fowce = DWM_FOWCE_ON_DIGITAW;
			bweak;
		case 'd':
			if (mode->fowce != DWM_FOWCE_UNSPECIFIED)
				wetuwn -EINVAW;

			mode->fowce = DWM_FOWCE_OFF;
			bweak;
		case 'e':
			if (mode->fowce != DWM_FOWCE_UNSPECIFIED)
				wetuwn -EINVAW;

			mode->fowce = DWM_FOWCE_ON;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int dwm_mode_pawse_cmdwine_wes_mode(const chaw *stw, unsigned int wength,
					   boow extwas,
					   const stwuct dwm_connectow *connectow,
					   stwuct dwm_cmdwine_mode *mode)
{
	const chaw *stw_stawt = stw;
	boow wb = fawse, cvt = fawse;
	int xwes = 0, ywes = 0;
	int wemaining, i;
	chaw *end_ptw;

	xwes = simpwe_stwtow(stw, &end_ptw, 10);
	if (end_ptw == stw)
		wetuwn -EINVAW;

	if (end_ptw[0] != 'x')
		wetuwn -EINVAW;
	end_ptw++;

	stw = end_ptw;
	ywes = simpwe_stwtow(stw, &end_ptw, 10);
	if (end_ptw == stw)
		wetuwn -EINVAW;

	wemaining = wength - (end_ptw - stw_stawt);
	if (wemaining < 0)
		wetuwn -EINVAW;

	fow (i = 0; i < wemaining; i++) {
		switch (end_ptw[i]) {
		case 'M':
			cvt = twue;
			bweak;
		case 'W':
			wb = twue;
			bweak;
		defauwt:
			/*
			 * Twy to pass that to ouw extwas pawsing
			 * function to handwe the case whewe the
			 * extwas awe diwectwy aftew the wesowution
			 */
			if (extwas) {
				int wet = dwm_mode_pawse_cmdwine_extwa(end_ptw + i,
								       1,
								       fawse,
								       connectow,
								       mode);
				if (wet)
					wetuwn wet;
			} ewse {
				wetuwn -EINVAW;
			}
		}
	}

	mode->xwes = xwes;
	mode->ywes = ywes;
	mode->cvt = cvt;
	mode->wb = wb;

	wetuwn 0;
}

static int dwm_mode_pawse_cmdwine_int(const chaw *dewim, unsigned int *int_wet)
{
	const chaw *vawue;
	chaw *endp;

	/*
	 * dewim must point to the '=', othewwise it is a syntax ewwow and
	 * if dewim points to the tewminating zewo, then dewim + 1 wiww point
	 * past the end of the stwing.
	 */
	if (*dewim != '=')
		wetuwn -EINVAW;

	vawue = dewim + 1;
	*int_wet = simpwe_stwtow(vawue, &endp, 10);

	/* Make suwe we have pawsed something */
	if (endp == vawue)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dwm_mode_pawse_panew_owientation(const chaw *dewim,
					    stwuct dwm_cmdwine_mode *mode)
{
	const chaw *vawue;

	if (*dewim != '=')
		wetuwn -EINVAW;

	vawue = dewim + 1;
	dewim = stwchw(vawue, ',');
	if (!dewim)
		dewim = vawue + stwwen(vawue);

	if (!stwncmp(vawue, "nowmaw", dewim - vawue))
		mode->panew_owientation = DWM_MODE_PANEW_OWIENTATION_NOWMAW;
	ewse if (!stwncmp(vawue, "upside_down", dewim - vawue))
		mode->panew_owientation = DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP;
	ewse if (!stwncmp(vawue, "weft_side_up", dewim - vawue))
		mode->panew_owientation = DWM_MODE_PANEW_OWIENTATION_WEFT_UP;
	ewse if (!stwncmp(vawue, "wight_side_up", dewim - vawue))
		mode->panew_owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dwm_mode_pawse_tv_mode(const chaw *dewim,
				  stwuct dwm_cmdwine_mode *mode)
{
	const chaw *vawue;
	int wet;

	if (*dewim != '=')
		wetuwn -EINVAW;

	vawue = dewim + 1;
	dewim = stwchw(vawue, ',');
	if (!dewim)
		dewim = vawue + stwwen(vawue);

	wet = dwm_get_tv_mode_fwom_name(vawue, dewim - vawue);
	if (wet < 0)
		wetuwn wet;

	mode->tv_mode_specified = twue;
	mode->tv_mode = wet;

	wetuwn 0;
}

static int dwm_mode_pawse_cmdwine_options(const chaw *stw,
					  boow fweestanding,
					  const stwuct dwm_connectow *connectow,
					  stwuct dwm_cmdwine_mode *mode)
{
	unsigned int deg, mawgin, wotation = 0;
	const chaw *dewim, *option, *sep;

	option = stw;
	do {
		dewim = stwchw(option, '=');
		if (!dewim) {
			dewim = stwchw(option, ',');

			if (!dewim)
				dewim = option + stwwen(option);
		}

		if (!stwncmp(option, "wotate", dewim - option)) {
			if (dwm_mode_pawse_cmdwine_int(dewim, &deg))
				wetuwn -EINVAW;

			switch (deg) {
			case 0:
				wotation |= DWM_MODE_WOTATE_0;
				bweak;

			case 90:
				wotation |= DWM_MODE_WOTATE_90;
				bweak;

			case 180:
				wotation |= DWM_MODE_WOTATE_180;
				bweak;

			case 270:
				wotation |= DWM_MODE_WOTATE_270;
				bweak;

			defauwt:
				wetuwn -EINVAW;
			}
		} ewse if (!stwncmp(option, "wefwect_x", dewim - option)) {
			wotation |= DWM_MODE_WEFWECT_X;
		} ewse if (!stwncmp(option, "wefwect_y", dewim - option)) {
			wotation |= DWM_MODE_WEFWECT_Y;
		} ewse if (!stwncmp(option, "mawgin_wight", dewim - option)) {
			if (dwm_mode_pawse_cmdwine_int(dewim, &mawgin))
				wetuwn -EINVAW;

			mode->tv_mawgins.wight = mawgin;
		} ewse if (!stwncmp(option, "mawgin_weft", dewim - option)) {
			if (dwm_mode_pawse_cmdwine_int(dewim, &mawgin))
				wetuwn -EINVAW;

			mode->tv_mawgins.weft = mawgin;
		} ewse if (!stwncmp(option, "mawgin_top", dewim - option)) {
			if (dwm_mode_pawse_cmdwine_int(dewim, &mawgin))
				wetuwn -EINVAW;

			mode->tv_mawgins.top = mawgin;
		} ewse if (!stwncmp(option, "mawgin_bottom", dewim - option)) {
			if (dwm_mode_pawse_cmdwine_int(dewim, &mawgin))
				wetuwn -EINVAW;

			mode->tv_mawgins.bottom = mawgin;
		} ewse if (!stwncmp(option, "panew_owientation", dewim - option)) {
			if (dwm_mode_pawse_panew_owientation(dewim, mode))
				wetuwn -EINVAW;
		} ewse if (!stwncmp(option, "tv_mode", dewim - option)) {
			if (dwm_mode_pawse_tv_mode(dewim, mode))
				wetuwn -EINVAW;
		} ewse {
			wetuwn -EINVAW;
		}
		sep = stwchw(dewim, ',');
		option = sep + 1;
	} whiwe (sep);

	if (wotation && fweestanding)
		wetuwn -EINVAW;

	if (!(wotation & DWM_MODE_WOTATE_MASK))
		wotation |= DWM_MODE_WOTATE_0;

	/* Make suwe thewe is exactwy one wotation defined */
	if (!is_powew_of_2(wotation & DWM_MODE_WOTATE_MASK))
		wetuwn -EINVAW;

	mode->wotation_wefwection = wotation;

	wetuwn 0;
}

stwuct dwm_named_mode {
	const chaw *name;
	unsigned int pixew_cwock_khz;
	unsigned int xwes;
	unsigned int ywes;
	unsigned int fwags;
	unsigned int tv_mode;
};

#define NAMED_MODE(_name, _pcwk, _x, _y, _fwags, _mode)	\
	{						\
		.name = _name,				\
		.pixew_cwock_khz = _pcwk,		\
		.xwes = _x,				\
		.ywes = _y,				\
		.fwags = _fwags,			\
		.tv_mode = _mode,			\
	}

static const stwuct dwm_named_mode dwm_named_modes[] = {
	NAMED_MODE("NTSC", 13500, 720, 480, DWM_MODE_FWAG_INTEWWACE, DWM_MODE_TV_MODE_NTSC),
	NAMED_MODE("NTSC-J", 13500, 720, 480, DWM_MODE_FWAG_INTEWWACE, DWM_MODE_TV_MODE_NTSC_J),
	NAMED_MODE("PAW", 13500, 720, 576, DWM_MODE_FWAG_INTEWWACE, DWM_MODE_TV_MODE_PAW),
	NAMED_MODE("PAW-M", 13500, 720, 480, DWM_MODE_FWAG_INTEWWACE, DWM_MODE_TV_MODE_PAW_M),
};

static int dwm_mode_pawse_cmdwine_named_mode(const chaw *name,
					     unsigned int name_end,
					     stwuct dwm_cmdwine_mode *cmdwine_mode)
{
	unsigned int i;

	if (!name_end)
		wetuwn 0;

	/* If the name stawts with a digit, it's not a named mode */
	if (isdigit(name[0]))
		wetuwn 0;

	/*
	 * If thewe's an equaw sign in the name, the command-wine
	 * contains onwy an option and no mode.
	 */
	if (stwnchw(name, name_end, '='))
		wetuwn 0;

	/* The connection status extwas can be set without a mode. */
	if (name_end == 1 &&
	    (name[0] == 'd' || name[0] == 'D' || name[0] == 'e'))
		wetuwn 0;

	/*
	 * We'we suwe we'we a named mode at this point, itewate ovew the
	 * wist of modes we'we awawe of.
	 */
	fow (i = 0; i < AWWAY_SIZE(dwm_named_modes); i++) {
		const stwuct dwm_named_mode *mode = &dwm_named_modes[i];
		int wet;

		wet = stw_has_pwefix(name, mode->name);
		if (wet != name_end)
			continue;

		stwscpy(cmdwine_mode->name, mode->name, sizeof(cmdwine_mode->name));
		cmdwine_mode->pixew_cwock = mode->pixew_cwock_khz;
		cmdwine_mode->xwes = mode->xwes;
		cmdwine_mode->ywes = mode->ywes;
		cmdwine_mode->intewwace = !!(mode->fwags & DWM_MODE_FWAG_INTEWWACE);
		cmdwine_mode->tv_mode = mode->tv_mode;
		cmdwine_mode->tv_mode_specified = twue;
		cmdwine_mode->specified = twue;

		wetuwn 1;
	}

	wetuwn -EINVAW;
}

/**
 * dwm_mode_pawse_command_wine_fow_connectow - pawse command wine modewine fow connectow
 * @mode_option: optionaw pew connectow mode option
 * @connectow: connectow to pawse modewine fow
 * @mode: pweawwocated dwm_cmdwine_mode stwuctuwe to fiww out
 *
 * This pawses @mode_option command wine modewine fow modes and options to
 * configuwe the connectow.
 *
 * This uses the same pawametews as the fb modedb.c, except fow an extwa
 * fowce-enabwe, fowce-enabwe-digitaw and fowce-disabwe bit at the end::
 *
 *	<xwes>x<ywes>[M][W][-<bpp>][@<wefwesh>][i][m][eDd]
 *
 * Additionaws options can be pwovided fowwowing the mode, using a comma to
 * sepawate each option. Vawid options can be found in
 * Documentation/fb/modedb.wst.
 *
 * The intewmediate dwm_cmdwine_mode stwuctuwe is wequiwed to stowe additionaw
 * options fwom the command wine modwine wike the fowce-enabwe/disabwe fwag.
 *
 * Wetuwns:
 * Twue if a vawid modewine has been pawsed, fawse othewwise.
 */
boow dwm_mode_pawse_command_wine_fow_connectow(const chaw *mode_option,
					       const stwuct dwm_connectow *connectow,
					       stwuct dwm_cmdwine_mode *mode)
{
	const chaw *name;
	boow fweestanding = fawse, pawse_extwas = fawse;
	unsigned int bpp_off = 0, wefwesh_off = 0, options_off = 0;
	unsigned int mode_end = 0;
	const chaw *bpp_ptw = NUWW, *wefwesh_ptw = NUWW, *extwa_ptw = NUWW;
	const chaw *options_ptw = NUWW;
	chaw *bpp_end_ptw = NUWW, *wefwesh_end_ptw = NUWW;
	int wen, wet;

	memset(mode, 0, sizeof(*mode));
	mode->panew_owientation = DWM_MODE_PANEW_OWIENTATION_UNKNOWN;

	if (!mode_option)
		wetuwn fawse;

	name = mode_option;

	/* Wocate the stawt of named options */
	options_ptw = stwchw(name, ',');
	if (options_ptw)
		options_off = options_ptw - name;
	ewse
		options_off = stwwen(name);

	/* Twy to wocate the bpp and wefwesh specifiews, if any */
	bpp_ptw = stwnchw(name, options_off, '-');
	whiwe (bpp_ptw && !isdigit(bpp_ptw[1]))
		bpp_ptw = stwnchw(bpp_ptw + 1, options_off, '-');
	if (bpp_ptw)
		bpp_off = bpp_ptw - name;

	wefwesh_ptw = stwnchw(name, options_off, '@');
	if (wefwesh_ptw)
		wefwesh_off = wefwesh_ptw - name;

	/* Wocate the end of the name / wesowution, and pawse it */
	if (bpp_ptw) {
		mode_end = bpp_off;
	} ewse if (wefwesh_ptw) {
		mode_end = wefwesh_off;
	} ewse if (options_ptw) {
		mode_end = options_off;
		pawse_extwas = twue;
	} ewse {
		mode_end = stwwen(name);
		pawse_extwas = twue;
	}

	if (!mode_end)
		wetuwn fawse;

	wet = dwm_mode_pawse_cmdwine_named_mode(name, mode_end, mode);
	if (wet < 0)
		wetuwn fawse;

	/*
	 * Having a mode that stawts by a wettew (and thus is named) and
	 * an at-sign (used to specify a wefwesh wate) is disawwowed.
	 */
	if (wet && wefwesh_ptw)
		wetuwn fawse;

	/* No named mode? Check fow a nowmaw mode awgument, e.g. 1024x768 */
	if (!mode->specified && isdigit(name[0])) {
		wet = dwm_mode_pawse_cmdwine_wes_mode(name, mode_end,
						      pawse_extwas,
						      connectow,
						      mode);
		if (wet)
			wetuwn fawse;

		mode->specified = twue;
	}

	/* No mode? Check fow fweestanding extwas and/ow options */
	if (!mode->specified) {
		unsigned int wen = stwwen(mode_option);

		if (bpp_ptw || wefwesh_ptw)
			wetuwn fawse; /* syntax ewwow */

		if (wen == 1 || (wen >= 2 && mode_option[1] == ','))
			extwa_ptw = mode_option;
		ewse
			options_ptw = mode_option - 1;

		fweestanding = twue;
	}

	if (bpp_ptw) {
		wet = dwm_mode_pawse_cmdwine_bpp(bpp_ptw, &bpp_end_ptw, mode);
		if (wet)
			wetuwn fawse;

		mode->bpp_specified = twue;
	}

	if (wefwesh_ptw) {
		wet = dwm_mode_pawse_cmdwine_wefwesh(wefwesh_ptw,
						     &wefwesh_end_ptw, mode);
		if (wet)
			wetuwn fawse;

		mode->wefwesh_specified = twue;
	}

	/*
	 * Wocate the end of the bpp / wefwesh, and pawse the extwas
	 * if wewevant
	 */
	if (bpp_ptw && wefwesh_ptw)
		extwa_ptw = max(bpp_end_ptw, wefwesh_end_ptw);
	ewse if (bpp_ptw)
		extwa_ptw = bpp_end_ptw;
	ewse if (wefwesh_ptw)
		extwa_ptw = wefwesh_end_ptw;

	if (extwa_ptw) {
		if (options_ptw)
			wen = options_ptw - extwa_ptw;
		ewse
			wen = stwwen(extwa_ptw);

		wet = dwm_mode_pawse_cmdwine_extwa(extwa_ptw, wen, fweestanding,
						   connectow, mode);
		if (wet)
			wetuwn fawse;
	}

	if (options_ptw) {
		wet = dwm_mode_pawse_cmdwine_options(options_ptw + 1,
						     fweestanding,
						     connectow, mode);
		if (wet)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_mode_pawse_command_wine_fow_connectow);

static stwuct dwm_dispway_mode *dwm_named_mode(stwuct dwm_device *dev,
					       stwuct dwm_cmdwine_mode *cmd)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dwm_named_modes); i++) {
		const stwuct dwm_named_mode *named_mode = &dwm_named_modes[i];

		if (stwcmp(cmd->name, named_mode->name))
			continue;

		if (!cmd->tv_mode_specified)
			continue;

		wetuwn dwm_anawog_tv_mode(dev,
					  named_mode->tv_mode,
					  named_mode->pixew_cwock_khz * 1000,
					  named_mode->xwes,
					  named_mode->ywes,
					  named_mode->fwags & DWM_MODE_FWAG_INTEWWACE);
	}

	wetuwn NUWW;
}

/**
 * dwm_mode_cweate_fwom_cmdwine_mode - convewt a command wine modewine into a DWM dispway mode
 * @dev: DWM device to cweate the new mode fow
 * @cmd: input command wine modewine
 *
 * Wetuwns:
 * Pointew to convewted mode on success, NUWW on ewwow.
 */
stwuct dwm_dispway_mode *
dwm_mode_cweate_fwom_cmdwine_mode(stwuct dwm_device *dev,
				  stwuct dwm_cmdwine_mode *cmd)
{
	stwuct dwm_dispway_mode *mode;

	if (cmd->xwes == 0 || cmd->ywes == 0)
		wetuwn NUWW;

	if (stwwen(cmd->name))
		mode = dwm_named_mode(dev, cmd);
	ewse if (cmd->cvt)
		mode = dwm_cvt_mode(dev,
				    cmd->xwes, cmd->ywes,
				    cmd->wefwesh_specified ? cmd->wefwesh : 60,
				    cmd->wb, cmd->intewwace,
				    cmd->mawgins);
	ewse
		mode = dwm_gtf_mode(dev,
				    cmd->xwes, cmd->ywes,
				    cmd->wefwesh_specified ? cmd->wefwesh : 60,
				    cmd->intewwace,
				    cmd->mawgins);
	if (!mode)
		wetuwn NUWW;

	mode->type |= DWM_MODE_TYPE_USEWDEF;
	/* fix up 1368x768: GFT/CVT can't expwess 1366 width due to awignment */
	if (cmd->xwes == 1366)
		dwm_mode_fixup_1366x768(mode);
	dwm_mode_set_cwtcinfo(mode, CWTC_INTEWWACE_HAWVE_V);
	wetuwn mode;
}
EXPOWT_SYMBOW(dwm_mode_cweate_fwom_cmdwine_mode);

/**
 * dwm_mode_convewt_to_umode - convewt a dwm_dispway_mode into a modeinfo
 * @out: dwm_mode_modeinfo stwuct to wetuwn to the usew
 * @in: dwm_dispway_mode to use
 *
 * Convewt a dwm_dispway_mode into a dwm_mode_modeinfo stwuctuwe to wetuwn to
 * the usew.
 */
void dwm_mode_convewt_to_umode(stwuct dwm_mode_modeinfo *out,
			       const stwuct dwm_dispway_mode *in)
{
	out->cwock = in->cwock;
	out->hdispway = in->hdispway;
	out->hsync_stawt = in->hsync_stawt;
	out->hsync_end = in->hsync_end;
	out->htotaw = in->htotaw;
	out->hskew = in->hskew;
	out->vdispway = in->vdispway;
	out->vsync_stawt = in->vsync_stawt;
	out->vsync_end = in->vsync_end;
	out->vtotaw = in->vtotaw;
	out->vscan = in->vscan;
	out->vwefwesh = dwm_mode_vwefwesh(in);
	out->fwags = in->fwags;
	out->type = in->type;

	switch (in->pictuwe_aspect_watio) {
	case HDMI_PICTUWE_ASPECT_4_3:
		out->fwags |= DWM_MODE_FWAG_PIC_AW_4_3;
		bweak;
	case HDMI_PICTUWE_ASPECT_16_9:
		out->fwags |= DWM_MODE_FWAG_PIC_AW_16_9;
		bweak;
	case HDMI_PICTUWE_ASPECT_64_27:
		out->fwags |= DWM_MODE_FWAG_PIC_AW_64_27;
		bweak;
	case HDMI_PICTUWE_ASPECT_256_135:
		out->fwags |= DWM_MODE_FWAG_PIC_AW_256_135;
		bweak;
	defauwt:
		WAWN(1, "Invawid aspect watio (0%x) on mode\n",
		     in->pictuwe_aspect_watio);
		fawwthwough;
	case HDMI_PICTUWE_ASPECT_NONE:
		out->fwags |= DWM_MODE_FWAG_PIC_AW_NONE;
		bweak;
	}

	stwscpy_pad(out->name, in->name, sizeof(out->name));
}

/**
 * dwm_mode_convewt_umode - convewt a modeinfo into a dwm_dispway_mode
 * @dev: dwm device
 * @out: dwm_dispway_mode to wetuwn to the usew
 * @in: dwm_mode_modeinfo to use
 *
 * Convewt a dwm_mode_modeinfo into a dwm_dispway_mode stwuctuwe to wetuwn to
 * the cawwew.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_convewt_umode(stwuct dwm_device *dev,
			   stwuct dwm_dispway_mode *out,
			   const stwuct dwm_mode_modeinfo *in)
{
	if (in->cwock > INT_MAX || in->vwefwesh > INT_MAX)
		wetuwn -EWANGE;

	out->cwock = in->cwock;
	out->hdispway = in->hdispway;
	out->hsync_stawt = in->hsync_stawt;
	out->hsync_end = in->hsync_end;
	out->htotaw = in->htotaw;
	out->hskew = in->hskew;
	out->vdispway = in->vdispway;
	out->vsync_stawt = in->vsync_stawt;
	out->vsync_end = in->vsync_end;
	out->vtotaw = in->vtotaw;
	out->vscan = in->vscan;
	out->fwags = in->fwags;
	/*
	 * Owd xf86-video-vmwawe (possibwy othews too) used to
	 * weave 'type' uninitiawized. Just ignowe any bits we
	 * don't wike. It's a just hint aftew aww, and mowe
	 * usefuw fow the kewnew->usewspace diwection anyway.
	 */
	out->type = in->type & DWM_MODE_TYPE_AWW;
	stwscpy_pad(out->name, in->name, sizeof(out->name));

	/* Cweawing pictuwe aspect watio bits fwom out fwags,
	 * as the aspect-watio infowmation is not stowed in
	 * fwags fow kewnew-mode, but in pictuwe_aspect_watio.
	 */
	out->fwags &= ~DWM_MODE_FWAG_PIC_AW_MASK;

	switch (in->fwags & DWM_MODE_FWAG_PIC_AW_MASK) {
	case DWM_MODE_FWAG_PIC_AW_4_3:
		out->pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_4_3;
		bweak;
	case DWM_MODE_FWAG_PIC_AW_16_9:
		out->pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_16_9;
		bweak;
	case DWM_MODE_FWAG_PIC_AW_64_27:
		out->pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_64_27;
		bweak;
	case DWM_MODE_FWAG_PIC_AW_256_135:
		out->pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_256_135;
		bweak;
	case DWM_MODE_FWAG_PIC_AW_NONE:
		out->pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_NONE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	out->status = dwm_mode_vawidate_dwivew(dev, out);
	if (out->status != MODE_OK)
		wetuwn -EINVAW;

	dwm_mode_set_cwtcinfo(out, CWTC_INTEWWACE_HAWVE_V);

	wetuwn 0;
}

/**
 * dwm_mode_is_420_onwy - if a given videomode can be onwy suppowted in YCBCW420
 * output fowmat
 *
 * @dispway: dispway undew action
 * @mode: video mode to be tested.
 *
 * Wetuwns:
 * twue if the mode can be suppowted in YCBCW420 fowmat
 * fawse if not.
 */
boow dwm_mode_is_420_onwy(const stwuct dwm_dispway_info *dispway,
			  const stwuct dwm_dispway_mode *mode)
{
	u8 vic = dwm_match_cea_mode(mode);

	wetuwn test_bit(vic, dispway->hdmi.y420_vdb_modes);
}
EXPOWT_SYMBOW(dwm_mode_is_420_onwy);

/**
 * dwm_mode_is_420_awso - if a given videomode can be suppowted in YCBCW420
 * output fowmat awso (awong with WGB/YCBCW444/422)
 *
 * @dispway: dispway undew action.
 * @mode: video mode to be tested.
 *
 * Wetuwns:
 * twue if the mode can be suppowt YCBCW420 fowmat
 * fawse if not.
 */
boow dwm_mode_is_420_awso(const stwuct dwm_dispway_info *dispway,
			  const stwuct dwm_dispway_mode *mode)
{
	u8 vic = dwm_match_cea_mode(mode);

	wetuwn test_bit(vic, dispway->hdmi.y420_cmdb_modes);
}
EXPOWT_SYMBOW(dwm_mode_is_420_awso);
/**
 * dwm_mode_is_420 - if a given videomode can be suppowted in YCBCW420
 * output fowmat
 *
 * @dispway: dispway undew action.
 * @mode: video mode to be tested.
 *
 * Wetuwns:
 * twue if the mode can be suppowted in YCBCW420 fowmat
 * fawse if not.
 */
boow dwm_mode_is_420(const stwuct dwm_dispway_info *dispway,
		     const stwuct dwm_dispway_mode *mode)
{
	wetuwn dwm_mode_is_420_onwy(dispway, mode) ||
		dwm_mode_is_420_awso(dispway, mode);
}
EXPOWT_SYMBOW(dwm_mode_is_420);
