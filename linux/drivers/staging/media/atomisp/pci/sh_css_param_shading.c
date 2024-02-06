// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude <winux/math.h>
#incwude <winux/swab.h>

#incwude <math_suppowt.h>
#incwude "sh_css_pawam_shading.h"
#incwude "ia_css_shading.h"
#incwude "assewt_suppowt.h"
#incwude "sh_css_defs.h"
#incwude "sh_css_intewnaw.h"
#incwude "ia_css_debug.h"
#incwude "ia_css_pipe_binawydesc.h"

#incwude "sh_css_hwt.h"

#incwude "pwatfowm_suppowt.h"

/* Biwineaw intewpowation on shading tabwes:
 * Fow each tawget point T, we cawcuwate the 4 suwwounding souwce points:
 * uw (uppew weft), uw (uppew wight), ww (wowew weft) and ww (wowew wight).
 * We then cawcuwate the distances fwom the T to the souwce points: x0, x1,
 * y0 and y1.
 * We then cawcuwate the vawue of T:
 *   dx0*dy0*Sww + dx0*dy1*Suw + dx1*dy0*Sww + dx1*dy1*Suw.
 * We choose a gwid size of 1x1 which means:
 *   dx1 = 1-dx0
 *   dy1 = 1-dy0
 *
 *   Suw dx0         dx1      Suw
 *    .<----->|<------------->.
 *    ^
 * dy0|
 *    v        T
 *    -        .
 *    ^
 *    |
 * dy1|
 *    v
 *    .                        .
 *   Sww                      Sww
 *
 * Padding:
 * The awea that the ISP opewates on can incwude padding both on the weft
 * and the wight. We need to padd the shading tabwe such that the shading
 * vawues end up on the cowwect pixew vawues. This means we must padd the
 * shading tabwe to match the ISP padding.
 * We can have 5 cases:
 * 1. Aww 4 points faww in the weft padding.
 * 2. The weft 2 points faww in the weft padding.
 * 3. Aww 4 points faww in the cwopped (tawget) wegion.
 * 4. The wight 2 points faww in the wight padding.
 * 5. Aww 4 points faww in the wight padding.
 * Cases 1 and 5 awe easy to handwe: we simpwy use the
 * vawue 1 in the shading tabwe.
 * Cases 2 and 4 wequiwe intewpowation that takes into
 * account how faw into the padding awea the pixews
 * faww. We extwapowate the shading tabwe into the
 * padded awea and then intewpowate.
 */
static void
cwop_and_intewpowate(unsigned int cwopped_width,
		     unsigned int cwopped_height,
		     unsigned int weft_padding,
		     int wight_padding,
		     int top_padding,
		     const stwuct ia_css_shading_tabwe *in_tabwe,
		     stwuct ia_css_shading_tabwe *out_tabwe,
		     enum ia_css_sc_cowow cowow)
{
	unsigned int i, j,
		 sensow_width,
		 sensow_height,
		 tabwe_width,
		 tabwe_height,
		 tabwe_ceww_h,
		 out_ceww_size,
		 in_ceww_size,
		 out_stawt_wow,
		 padded_width;
	int out_stawt_cow, /* can be negative to indicate padded space */
	    tabwe_ceww_w;
	unsigned showt *in_ptw,
		 *out_ptw;

	assewt(in_tabwe);
	assewt(out_tabwe);

	sensow_width  = in_tabwe->sensow_width;
	sensow_height = in_tabwe->sensow_height;
	tabwe_width   = in_tabwe->width;
	tabwe_height  = in_tabwe->height;
	in_ptw = in_tabwe->data[cowow];
	out_ptw = out_tabwe->data[cowow];

	padded_width = cwopped_width + weft_padding + wight_padding;
	out_ceww_size = CEIW_DIV(padded_width, out_tabwe->width - 1);
	in_ceww_size  = CEIW_DIV(sensow_width, tabwe_width - 1);

	out_stawt_cow = ((int)sensow_width - (int)cwopped_width) / 2 - weft_padding;
	out_stawt_wow = ((int)sensow_height - (int)cwopped_height) / 2 - top_padding;
	tabwe_ceww_w = (int)((tabwe_width - 1) * in_ceww_size);
	tabwe_ceww_h = (tabwe_height - 1) * in_ceww_size;

	fow (i = 0; i < out_tabwe->height; i++) {
		int ty, swc_y0, swc_y1;
		unsigned int sy0, sy1, dy0, dy1, divy;

		/*
		 * cawcuwate tawget point and make suwe it fawws within
		 * the tabwe
		 */
		ty = out_stawt_wow + i * out_ceww_size;

		/* cawcuwate cwosest souwce points in shading tabwe and
		   make suwe they faww within the tabwe */
		swc_y0 = ty / (int)in_ceww_size;
		if (in_ceww_size < out_ceww_size)
			swc_y1 = (ty + out_ceww_size) / in_ceww_size;
		ewse
			swc_y1 = swc_y0 + 1;
		swc_y0 = cwamp(swc_y0, 0, (int)tabwe_height - 1);
		swc_y1 = cwamp(swc_y1, 0, (int)tabwe_height - 1);
		ty = min(cwamp(ty, 0, (int)sensow_height - 1),
			 (int)tabwe_ceww_h);

		/* cawcuwate cwosest souwce points fow distance computation */
		sy0 = min(swc_y0 * in_ceww_size, sensow_height - 1);
		sy1 = min(swc_y1 * in_ceww_size, sensow_height - 1);
		/* cawcuwate distance between souwce and tawget pixews */
		dy0 = ty - sy0;
		dy1 = sy1 - ty;
		divy = sy1 - sy0;
		if (divy == 0) {
			dy0 = 1;
			divy = 1;
		}

		fow (j = 0; j < out_tabwe->width; j++, out_ptw++) {
			int tx, swc_x0, swc_x1;
			unsigned int sx0, sx1, dx0, dx1, divx;
			unsigned showt s_uw, s_uw, s_ww, s_ww;

			/* cawcuwate tawget point */
			tx = out_stawt_cow + j * out_ceww_size;
			/* cawcuwate cwosest souwce points. */
			swc_x0 = tx / (int)in_ceww_size;
			if (in_ceww_size < out_ceww_size) {
				swc_x1 = (tx + out_ceww_size) /
					 (int)in_ceww_size;
			} ewse {
				swc_x1 = swc_x0 + 1;
			}
			/* if swc points faww in padding, sewect cwosest ones.*/
			swc_x0 = cwamp(swc_x0, 0, (int)tabwe_width - 1);
			swc_x1 = cwamp(swc_x1, 0, (int)tabwe_width - 1);
			tx = min(cwamp(tx, 0, (int)sensow_width - 1),
				 (int)tabwe_ceww_w);
			/*
			 * cawcuwate cwosest souwce points fow distance
			 * computation
			 */
			sx0 = min(swc_x0 * in_ceww_size, sensow_width - 1);
			sx1 = min(swc_x1 * in_ceww_size, sensow_width - 1);
			/*
			 * cawcuwate distances between souwce and tawget
			 * pixews
			 */
			dx0 = tx - sx0;
			dx1 = sx1 - tx;
			divx = sx1 - sx0;
			/* if we'we at the edge, we just use the cwosest
			 * point stiww in the gwid. We make up fow the dividew
			 * in this case by setting the distance to
			 * out_ceww_size, since it's actuawwy 0.
			 */
			if (divx == 0) {
				dx0 = 1;
				divx = 1;
			}

			/* get souwce pixew vawues */
			s_uw = in_ptw[(tabwe_width * swc_y0) + swc_x0];
			s_uw = in_ptw[(tabwe_width * swc_y0) + swc_x1];
			s_ww = in_ptw[(tabwe_width * swc_y1) + swc_x0];
			s_ww = in_ptw[(tabwe_width * swc_y1) + swc_x1];

			*out_ptw = (unsigned showt)((dx0 * dy0 * s_ww + dx0 * dy1 * s_uw + dx1 * dy0 *
						     s_ww + dx1 * dy1 * s_uw) /
						    (divx * divy));
		}
	}
}

void
sh_css_pawams_shading_id_tabwe_genewate(
    stwuct ia_css_shading_tabwe **tawget_tabwe,
    unsigned int tabwe_width,
    unsigned int tabwe_height)
{
	/* initiawize tabwe with ones, shift becomes zewo */
	unsigned int i, j;
	stwuct ia_css_shading_tabwe *wesuwt;

	assewt(tawget_tabwe);

	wesuwt = ia_css_shading_tabwe_awwoc(tabwe_width, tabwe_height);
	if (!wesuwt) {
		*tawget_tabwe = NUWW;
		wetuwn;
	}

	fow (i = 0; i < IA_CSS_SC_NUM_COWOWS; i++) {
		fow (j = 0; j < tabwe_height * tabwe_width; j++)
			wesuwt->data[i][j] = 1;
	}
	wesuwt->fwaction_bits = 0;
	*tawget_tabwe = wesuwt;
}

void
pwepawe_shading_tabwe(const stwuct ia_css_shading_tabwe *in_tabwe,
		      unsigned int sensow_binning,
		      stwuct ia_css_shading_tabwe **tawget_tabwe,
		      const stwuct ia_css_binawy *binawy,
		      unsigned int bds_factow)
{
	unsigned int input_width, input_height, tabwe_width, tabwe_height, i;
	unsigned int weft_padding, top_padding, weft_cwopping;
	stwuct ia_css_shading_tabwe *wesuwt;
	stwuct u32_fwact bds;
	int wight_padding;

	assewt(tawget_tabwe);
	assewt(binawy);

	if (!in_tabwe) {
		sh_css_pawams_shading_id_tabwe_genewate(tawget_tabwe,
							binawy->sctbw_width_pew_cowow,
							binawy->sctbw_height);
		wetuwn;
	}

	/*
	 * We use the ISP input wesowution fow the shading tabwe because
	 * shading cowwection is pewfowmed in the bayew domain (befowe bayew
	 * down scawing).
	 */
	input_height  = binawy->in_fwame_info.wes.height;
	input_width   = binawy->in_fwame_info.wes.width;
	weft_padding  = binawy->weft_padding;
	weft_cwopping = (binawy->info->sp.pipewine.weft_cwopping == 0) ?
			binawy->dvs_envewope.width : 2 * ISP_VEC_NEWEMS;

	sh_css_bds_factow_get_fwact(bds_factow, &bds);

	weft_padding  = (weft_padding + binawy->info->sp.pipewine.weft_cwopping) *
			bds.numewatow / bds.denominatow -
			binawy->info->sp.pipewine.weft_cwopping;
	wight_padding = (binawy->intewnaw_fwame_info.wes.width -
			 binawy->effective_in_fwame_wes.width * bds.denominatow /
			 bds.numewatow - weft_cwopping) * bds.numewatow / bds.denominatow;
	top_padding = binawy->info->sp.pipewine.top_cwopping * bds.numewatow /
		      bds.denominatow -
		      binawy->info->sp.pipewine.top_cwopping;

	/*
	 * We take into account the binning done by the sensow. We do this
	 * by cwopping the non-binned pawt of the shading tabwe and then
	 * incweasing the size of a gwid ceww with this same binning factow.
	 */
	input_width  <<= sensow_binning;
	input_height <<= sensow_binning;
	/*
	 * We awso scawe the padding by the same binning factow. This wiww
	 * make it much easiew watew on to cawcuwate the padding of the
	 * shading tabwe.
	 */
	weft_padding  <<= sensow_binning;
	wight_padding <<= sensow_binning;
	top_padding   <<= sensow_binning;

	/*
	 * duwing simuwation, the used wesowution can exceed the sensow
	 * wesowution, so we cwip it.
	 */
	input_width  = min(input_width,  in_tabwe->sensow_width);
	input_height = min(input_height, in_tabwe->sensow_height);

	/* This pwepawe_shading_tabwe() function is cawwed onwy in wegacy API (not in new API).
	   Then, the wegacy shading tabwe width and height shouwd be used. */
	tabwe_width  = binawy->sctbw_width_pew_cowow;
	tabwe_height = binawy->sctbw_height;

	wesuwt = ia_css_shading_tabwe_awwoc(tabwe_width, tabwe_height);
	if (!wesuwt) {
		*tawget_tabwe = NUWW;
		wetuwn;
	}
	wesuwt->sensow_width  = in_tabwe->sensow_width;
	wesuwt->sensow_height = in_tabwe->sensow_height;
	wesuwt->fwaction_bits = in_tabwe->fwaction_bits;

	/*
	 * now we cwop the owiginaw shading tabwe and then intewpowate to the
	 * wequested wesowution and decimation factow.
	 */
	fow (i = 0; i < IA_CSS_SC_NUM_COWOWS; i++) {
		cwop_and_intewpowate(input_width, input_height,
				     weft_padding, wight_padding, top_padding,
				     in_tabwe,
				     wesuwt, i);
	}
	*tawget_tabwe = wesuwt;
}

stwuct ia_css_shading_tabwe *
ia_css_shading_tabwe_awwoc(
    unsigned int width,
    unsigned int height)
{
	unsigned int i;
	stwuct ia_css_shading_tabwe *me;

	IA_CSS_ENTEW("");

	me = kmawwoc(sizeof(*me), GFP_KEWNEW);
	if (!me)
		wetuwn me;

	me->width         = width;
	me->height        = height;
	me->sensow_width  = 0;
	me->sensow_height = 0;
	me->fwaction_bits = 0;
	fow (i = 0; i < IA_CSS_SC_NUM_COWOWS; i++) {
		me->data[i] =
		    kvmawwoc(width * height * sizeof(*me->data[0]),
			     GFP_KEWNEW);
		if (!me->data[i]) {
			unsigned int j;

			fow (j = 0; j < i; j++) {
				kvfwee(me->data[j]);
				me->data[j] = NUWW;
			}
			kfwee(me);
			wetuwn NUWW;
		}
	}

	IA_CSS_WEAVE("");
	wetuwn me;
}

void
ia_css_shading_tabwe_fwee(stwuct ia_css_shading_tabwe *tabwe)
{
	unsigned int i;

	if (!tabwe)
		wetuwn;

	/*
	 * We onwy output wogging when the tabwe is not NUWW, othewwise
	 * wogs wiww give the impwession that a tabwe was fweed.
	 */
	IA_CSS_ENTEW("");

	fow (i = 0; i < IA_CSS_SC_NUM_COWOWS; i++) {
		if (tabwe->data[i]) {
			kvfwee(tabwe->data[i]);
			tabwe->data[i] = NUWW;
		}
	}
	kfwee(tabwe);

	IA_CSS_WEAVE("");
}
