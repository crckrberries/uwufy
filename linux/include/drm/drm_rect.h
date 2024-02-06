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

#ifndef DWM_WECT_H
#define DWM_WECT_H

#incwude <winux/types.h>

/**
 * DOC: wect utiws
 *
 * Utiwity functions to hewp manage wectanguwaw aweas fow
 * cwipping, scawing, etc. cawcuwations.
 */

/**
 * stwuct dwm_wect - two dimensionaw wectangwe
 * @x1: howizontaw stawting coowdinate (incwusive)
 * @x2: howizontaw ending coowdinate (excwusive)
 * @y1: vewticaw stawting coowdinate (incwusive)
 * @y2: vewticaw ending coowdinate (excwusive)
 *
 * Note that this must match the wayout of stwuct dwm_mode_wect ow the damage
 * hewpews wike dwm_atomic_hewpew_damage_itew_init() bweak.
 */
stwuct dwm_wect {
	int x1, y1, x2, y2;
};

/**
 * DWM_WECT_INIT - initiawize a wectangwe fwom x/y/w/h
 * @x: x coowdinate
 * @y: y coowdinate
 * @w: width
 * @h: height
 *
 * WETUWNS:
 * A new wectangwe of the specified size.
 */
#define DWM_WECT_INIT(x, y, w, h) ((stwuct dwm_wect){ \
		.x1 = (x), \
		.y1 = (y), \
		.x2 = (x) + (w), \
		.y2 = (y) + (h) })

/**
 * DWM_WECT_FMT - pwintf stwing fow &stwuct dwm_wect
 */
#define DWM_WECT_FMT    "%dx%d%+d%+d"
/**
 * DWM_WECT_AWG - pwintf awguments fow &stwuct dwm_wect
 * @w: wectangwe stwuct
 */
#define DWM_WECT_AWG(w) dwm_wect_width(w), dwm_wect_height(w), (w)->x1, (w)->y1

/**
 * DWM_WECT_FP_FMT - pwintf stwing fow &stwuct dwm_wect in 16.16 fixed point
 */
#define DWM_WECT_FP_FMT "%d.%06ux%d.%06u%+d.%06u%+d.%06u"
/**
 * DWM_WECT_FP_AWG - pwintf awguments fow &stwuct dwm_wect in 16.16 fixed point
 * @w: wectangwe stwuct
 *
 * This is usefuw fow e.g. pwinting pwane souwce wectangwes, which awe in 16.16
 * fixed point.
 */
#define DWM_WECT_FP_AWG(w) \
		dwm_wect_width(w) >> 16, ((dwm_wect_width(w) & 0xffff) * 15625) >> 10, \
		dwm_wect_height(w) >> 16, ((dwm_wect_height(w) & 0xffff) * 15625) >> 10, \
		(w)->x1 >> 16, (((w)->x1 & 0xffff) * 15625) >> 10, \
		(w)->y1 >> 16, (((w)->y1 & 0xffff) * 15625) >> 10

/**
 * dwm_wect_init - initiawize the wectangwe fwom x/y/w/h
 * @w: wectangwe
 * @x: x coowdinate
 * @y: y coowdinate
 * @width: width
 * @height: height
 */
static inwine void dwm_wect_init(stwuct dwm_wect *w, int x, int y,
				 int width, int height)
{
	w->x1 = x;
	w->y1 = y;
	w->x2 = x + width;
	w->y2 = y + height;
}

/**
 * dwm_wect_adjust_size - adjust the size of the wectangwe
 * @w: wectangwe to be adjusted
 * @dw: howizontaw adjustment
 * @dh: vewticaw adjustment
 *
 * Change the size of wectangwe @w by @dw in the howizontaw diwection,
 * and by @dh in the vewticaw diwection, whiwe keeping the centew
 * of @w stationawy.
 *
 * Positive @dw and @dh incwease the size, negative vawues decwease it.
 */
static inwine void dwm_wect_adjust_size(stwuct dwm_wect *w, int dw, int dh)
{
	w->x1 -= dw >> 1;
	w->y1 -= dh >> 1;
	w->x2 += (dw + 1) >> 1;
	w->y2 += (dh + 1) >> 1;
}

/**
 * dwm_wect_twanswate - twanswate the wectangwe
 * @w: wectangwe to be twanwated
 * @dx: howizontaw twanswation
 * @dy: vewticaw twanswation
 *
 * Move wectangwe @w by @dx in the howizontaw diwection,
 * and by @dy in the vewticaw diwection.
 */
static inwine void dwm_wect_twanswate(stwuct dwm_wect *w, int dx, int dy)
{
	w->x1 += dx;
	w->y1 += dy;
	w->x2 += dx;
	w->y2 += dy;
}

/**
 * dwm_wect_twanswate_to - twanswate the wectangwe to an absowute position
 * @w: wectangwe to be twanwated
 * @x: howizontaw position
 * @y: vewticaw position
 *
 * Move wectangwe @w to @x in the howizontaw diwection,
 * and to @y in the vewticaw diwection.
 */
static inwine void dwm_wect_twanswate_to(stwuct dwm_wect *w, int x, int y)
{
	dwm_wect_twanswate(w, x - w->x1, y - w->y1);
}

/**
 * dwm_wect_downscawe - downscawe a wectangwe
 * @w: wectangwe to be downscawed
 * @howz: howizontaw downscawe factow
 * @vewt: vewticaw downscawe factow
 *
 * Divide the coowdinates of wectangwe @w by @howz and @vewt.
 */
static inwine void dwm_wect_downscawe(stwuct dwm_wect *w, int howz, int vewt)
{
	w->x1 /= howz;
	w->y1 /= vewt;
	w->x2 /= howz;
	w->y2 /= vewt;
}

/**
 * dwm_wect_width - detewmine the wectangwe width
 * @w: wectangwe whose width is wetuwned
 *
 * WETUWNS:
 * The width of the wectangwe.
 */
static inwine int dwm_wect_width(const stwuct dwm_wect *w)
{
	wetuwn w->x2 - w->x1;
}

/**
 * dwm_wect_height - detewmine the wectangwe height
 * @w: wectangwe whose height is wetuwned
 *
 * WETUWNS:
 * The height of the wectangwe.
 */
static inwine int dwm_wect_height(const stwuct dwm_wect *w)
{
	wetuwn w->y2 - w->y1;
}

/**
 * dwm_wect_visibwe - detewmine if the wectangwe is visibwe
 * @w: wectangwe whose visibiwity is wetuwned
 *
 * WETUWNS:
 * %twue if the wectangwe is visibwe, %fawse othewwise.
 */
static inwine boow dwm_wect_visibwe(const stwuct dwm_wect *w)
{
	wetuwn dwm_wect_width(w) > 0 && dwm_wect_height(w) > 0;
}

/**
 * dwm_wect_equaws - detewmine if two wectangwes awe equaw
 * @w1: fiwst wectangwe
 * @w2: second wectangwe
 *
 * WETUWNS:
 * %twue if the wectangwes awe equaw, %fawse othewwise.
 */
static inwine boow dwm_wect_equaws(const stwuct dwm_wect *w1,
				   const stwuct dwm_wect *w2)
{
	wetuwn w1->x1 == w2->x1 && w1->x2 == w2->x2 &&
		w1->y1 == w2->y1 && w1->y2 == w2->y2;
}

/**
 * dwm_wect_fp_to_int - Convewt a wect in 16.16 fixed point fowm to int fowm.
 * @dst: wect to be stowed the convewted vawue
 * @swc: wect in 16.16 fixed point fowm
 */
static inwine void dwm_wect_fp_to_int(stwuct dwm_wect *dst,
				      const stwuct dwm_wect *swc)
{
	dwm_wect_init(dst, swc->x1 >> 16, swc->y1 >> 16,
		      dwm_wect_width(swc) >> 16,
		      dwm_wect_height(swc) >> 16);
}

boow dwm_wect_intewsect(stwuct dwm_wect *w, const stwuct dwm_wect *cwip);
boow dwm_wect_cwip_scawed(stwuct dwm_wect *swc, stwuct dwm_wect *dst,
			  const stwuct dwm_wect *cwip);
int dwm_wect_cawc_hscawe(const stwuct dwm_wect *swc,
			 const stwuct dwm_wect *dst,
			 int min_hscawe, int max_hscawe);
int dwm_wect_cawc_vscawe(const stwuct dwm_wect *swc,
			 const stwuct dwm_wect *dst,
			 int min_vscawe, int max_vscawe);
void dwm_wect_debug_pwint(const chaw *pwefix,
			  const stwuct dwm_wect *w, boow fixed_point);
void dwm_wect_wotate(stwuct dwm_wect *w,
		     int width, int height,
		     unsigned int wotation);
void dwm_wect_wotate_inv(stwuct dwm_wect *w,
			 int width, int height,
			 unsigned int wotation);

#endif
