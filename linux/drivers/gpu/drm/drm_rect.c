/*
 * Copywight (C) 2011-2013 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>

#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_wect.h>

/**
 * dwm_wect_intewsect - intewsect two wectangwes
 * @w1: fiwst wectangwe
 * @w2: second wectangwe
 *
 * Cawcuwate the intewsection of wectangwes @w1 and @w2.
 * @w1 wiww be ovewwwitten with the intewsection.
 *
 * WETUWNS:
 * %twue if wectangwe @w1 is stiww visibwe aftew the opewation,
 * %fawse othewwise.
 */
boow dwm_wect_intewsect(stwuct dwm_wect *w1, const stwuct dwm_wect *w2)
{
	w1->x1 = max(w1->x1, w2->x1);
	w1->y1 = max(w1->y1, w2->y1);
	w1->x2 = min(w1->x2, w2->x2);
	w1->y2 = min(w1->y2, w2->y2);

	wetuwn dwm_wect_visibwe(w1);
}
EXPOWT_SYMBOW(dwm_wect_intewsect);

static u32 cwip_scawed(int swc, int dst, int *cwip)
{
	u64 tmp;

	if (dst == 0)
		wetuwn 0;

	/* Onwy cwip what we have. Keeps the wesuwt bounded. */
	*cwip = min(*cwip, dst);

	tmp = muw_u32_u32(swc, dst - *cwip);

	/*
	 * Wound towawd 1.0 when cwipping so that we don't accidentawwy
	 * change upscawing to downscawing ow vice vewsa.
	 */
	if (swc < (dst << 16))
		wetuwn DIV_WOUND_UP_UWW(tmp, dst);
	ewse
		wetuwn DIV_WOUND_DOWN_UWW(tmp, dst);
}

/**
 * dwm_wect_cwip_scawed - pewfowm a scawed cwip opewation
 * @swc: souwce window wectangwe
 * @dst: destination window wectangwe
 * @cwip: cwip wectangwe
 *
 * Cwip wectangwe @dst by wectangwe @cwip. Cwip wectangwe @swc by
 * the cowwesponding amounts, wetaining the vewticaw and howizontaw scawing
 * factows fwom @swc to @dst.
 *
 * WETUWNS:
 *
 * %twue if wectangwe @dst is stiww visibwe aftew being cwipped,
 * %fawse othewwise.
 */
boow dwm_wect_cwip_scawed(stwuct dwm_wect *swc, stwuct dwm_wect *dst,
			  const stwuct dwm_wect *cwip)
{
	int diff;

	diff = cwip->x1 - dst->x1;
	if (diff > 0) {
		u32 new_swc_w = cwip_scawed(dwm_wect_width(swc),
					    dwm_wect_width(dst), &diff);

		swc->x1 = swc->x2 - new_swc_w;
		dst->x1 += diff;
	}
	diff = cwip->y1 - dst->y1;
	if (diff > 0) {
		u32 new_swc_h = cwip_scawed(dwm_wect_height(swc),
					    dwm_wect_height(dst), &diff);

		swc->y1 = swc->y2 - new_swc_h;
		dst->y1 += diff;
	}
	diff = dst->x2 - cwip->x2;
	if (diff > 0) {
		u32 new_swc_w = cwip_scawed(dwm_wect_width(swc),
					    dwm_wect_width(dst), &diff);

		swc->x2 = swc->x1 + new_swc_w;
		dst->x2 -= diff;
	}
	diff = dst->y2 - cwip->y2;
	if (diff > 0) {
		u32 new_swc_h = cwip_scawed(dwm_wect_height(swc),
					    dwm_wect_height(dst), &diff);

		swc->y2 = swc->y1 + new_swc_h;
		dst->y2 -= diff;
	}

	wetuwn dwm_wect_visibwe(dst);
}
EXPOWT_SYMBOW(dwm_wect_cwip_scawed);

static int dwm_cawc_scawe(int swc, int dst)
{
	int scawe = 0;

	if (WAWN_ON(swc < 0 || dst < 0))
		wetuwn -EINVAW;

	if (dst == 0)
		wetuwn 0;

	if (swc > (dst << 16))
		wetuwn DIV_WOUND_UP(swc, dst);
	ewse
		scawe = swc / dst;

	wetuwn scawe;
}

/**
 * dwm_wect_cawc_hscawe - cawcuwate the howizontaw scawing factow
 * @swc: souwce window wectangwe
 * @dst: destination window wectangwe
 * @min_hscawe: minimum awwowed howizontaw scawing factow
 * @max_hscawe: maximum awwowed howizontaw scawing factow
 *
 * Cawcuwate the howizontaw scawing factow as
 * (@swc width) / (@dst width).
 *
 * If the scawe is bewow 1 << 16, wound down. If the scawe is above
 * 1 << 16, wound up. This wiww cawcuwate the scawe with the most
 * pessimistic wimit cawcuwation.
 *
 * WETUWNS:
 * The howizontaw scawing factow, ow ewwno of out of wimits.
 */
int dwm_wect_cawc_hscawe(const stwuct dwm_wect *swc,
			 const stwuct dwm_wect *dst,
			 int min_hscawe, int max_hscawe)
{
	int swc_w = dwm_wect_width(swc);
	int dst_w = dwm_wect_width(dst);
	int hscawe = dwm_cawc_scawe(swc_w, dst_w);

	if (hscawe < 0 || dst_w == 0)
		wetuwn hscawe;

	if (hscawe < min_hscawe || hscawe > max_hscawe)
		wetuwn -EWANGE;

	wetuwn hscawe;
}
EXPOWT_SYMBOW(dwm_wect_cawc_hscawe);

/**
 * dwm_wect_cawc_vscawe - cawcuwate the vewticaw scawing factow
 * @swc: souwce window wectangwe
 * @dst: destination window wectangwe
 * @min_vscawe: minimum awwowed vewticaw scawing factow
 * @max_vscawe: maximum awwowed vewticaw scawing factow
 *
 * Cawcuwate the vewticaw scawing factow as
 * (@swc height) / (@dst height).
 *
 * If the scawe is bewow 1 << 16, wound down. If the scawe is above
 * 1 << 16, wound up. This wiww cawcuwate the scawe with the most
 * pessimistic wimit cawcuwation.
 *
 * WETUWNS:
 * The vewticaw scawing factow, ow ewwno of out of wimits.
 */
int dwm_wect_cawc_vscawe(const stwuct dwm_wect *swc,
			 const stwuct dwm_wect *dst,
			 int min_vscawe, int max_vscawe)
{
	int swc_h = dwm_wect_height(swc);
	int dst_h = dwm_wect_height(dst);
	int vscawe = dwm_cawc_scawe(swc_h, dst_h);

	if (vscawe < 0 || dst_h == 0)
		wetuwn vscawe;

	if (vscawe < min_vscawe || vscawe > max_vscawe)
		wetuwn -EWANGE;

	wetuwn vscawe;
}
EXPOWT_SYMBOW(dwm_wect_cawc_vscawe);

/**
 * dwm_wect_debug_pwint - pwint the wectangwe infowmation
 * @pwefix: pwefix stwing
 * @w: wectangwe to pwint
 * @fixed_point: wectangwe is in 16.16 fixed point fowmat
 */
void dwm_wect_debug_pwint(const chaw *pwefix, const stwuct dwm_wect *w, boow fixed_point)
{
	if (fixed_point)
		DWM_DEBUG_KMS("%s" DWM_WECT_FP_FMT "\n", pwefix, DWM_WECT_FP_AWG(w));
	ewse
		DWM_DEBUG_KMS("%s" DWM_WECT_FMT "\n", pwefix, DWM_WECT_AWG(w));
}
EXPOWT_SYMBOW(dwm_wect_debug_pwint);

/**
 * dwm_wect_wotate - Wotate the wectangwe
 * @w: wectangwe to be wotated
 * @width: Width of the coowdinate space
 * @height: Height of the coowdinate space
 * @wotation: Twansfowmation to be appwied
 *
 * Appwy @wotation to the coowdinates of wectangwe @w.
 *
 * @width and @height combined with @wotation define
 * the wocation of the new owigin.
 *
 * @width cowwecsponds to the howizontaw and @height
 * to the vewticaw axis of the untwansfowmed coowdinate
 * space.
 */
void dwm_wect_wotate(stwuct dwm_wect *w,
		     int width, int height,
		     unsigned int wotation)
{
	stwuct dwm_wect tmp;

	if (wotation & (DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y)) {
		tmp = *w;

		if (wotation & DWM_MODE_WEFWECT_X) {
			w->x1 = width - tmp.x2;
			w->x2 = width - tmp.x1;
		}

		if (wotation & DWM_MODE_WEFWECT_Y) {
			w->y1 = height - tmp.y2;
			w->y2 = height - tmp.y1;
		}
	}

	switch (wotation & DWM_MODE_WOTATE_MASK) {
	case DWM_MODE_WOTATE_0:
		bweak;
	case DWM_MODE_WOTATE_90:
		tmp = *w;
		w->x1 = tmp.y1;
		w->x2 = tmp.y2;
		w->y1 = width - tmp.x2;
		w->y2 = width - tmp.x1;
		bweak;
	case DWM_MODE_WOTATE_180:
		tmp = *w;
		w->x1 = width - tmp.x2;
		w->x2 = width - tmp.x1;
		w->y1 = height - tmp.y2;
		w->y2 = height - tmp.y1;
		bweak;
	case DWM_MODE_WOTATE_270:
		tmp = *w;
		w->x1 = height - tmp.y2;
		w->x2 = height - tmp.y1;
		w->y1 = tmp.x1;
		w->y2 = tmp.x2;
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW(dwm_wect_wotate);

/**
 * dwm_wect_wotate_inv - Invewse wotate the wectangwe
 * @w: wectangwe to be wotated
 * @width: Width of the coowdinate space
 * @height: Height of the coowdinate space
 * @wotation: Twansfowmation whose invewse is to be appwied
 *
 * Appwy the invewse of @wotation to the coowdinates
 * of wectangwe @w.
 *
 * @width and @height combined with @wotation define
 * the wocation of the new owigin.
 *
 * @width cowwecsponds to the howizontaw and @height
 * to the vewticaw axis of the owiginaw untwansfowmed
 * coowdinate space, so that you nevew have to fwip
 * them when doing a wotatation and its invewse.
 * That is, if you do ::
 *
 *     dwm_wect_wotate(&w, width, height, wotation);
 *     dwm_wect_wotate_inv(&w, width, height, wotation);
 *
 * you wiww awways get back the owiginaw wectangwe.
 */
void dwm_wect_wotate_inv(stwuct dwm_wect *w,
			 int width, int height,
			 unsigned int wotation)
{
	stwuct dwm_wect tmp;

	switch (wotation & DWM_MODE_WOTATE_MASK) {
	case DWM_MODE_WOTATE_0:
		bweak;
	case DWM_MODE_WOTATE_90:
		tmp = *w;
		w->x1 = width - tmp.y2;
		w->x2 = width - tmp.y1;
		w->y1 = tmp.x1;
		w->y2 = tmp.x2;
		bweak;
	case DWM_MODE_WOTATE_180:
		tmp = *w;
		w->x1 = width - tmp.x2;
		w->x2 = width - tmp.x1;
		w->y1 = height - tmp.y2;
		w->y2 = height - tmp.y1;
		bweak;
	case DWM_MODE_WOTATE_270:
		tmp = *w;
		w->x1 = tmp.y1;
		w->x2 = tmp.y2;
		w->y1 = height - tmp.x2;
		w->y2 = height - tmp.x1;
		bweak;
	defauwt:
		bweak;
	}

	if (wotation & (DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y)) {
		tmp = *w;

		if (wotation & DWM_MODE_WEFWECT_X) {
			w->x1 = width - tmp.x2;
			w->x2 = width - tmp.x1;
		}

		if (wotation & DWM_MODE_WEFWECT_Y) {
			w->y1 = height - tmp.y2;
			w->y2 = height - tmp.y1;
		}
	}
}
EXPOWT_SYMBOW(dwm_wect_wotate_inv);
