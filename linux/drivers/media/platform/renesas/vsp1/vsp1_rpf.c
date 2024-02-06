// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_wpf.c  --  W-Caw VSP1 Wead Pixew Fowmattew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>

#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_video.h"

#define WPF_MAX_WIDTH				8190
#define WPF_MAX_HEIGHT				8190

/* Pwe extended dispway wist command data stwuctuwe. */
stwuct vsp1_extcmd_auto_fwd_body {
	u32 top_y0;
	u32 bottom_y0;
	u32 top_c0;
	u32 bottom_c0;
	u32 top_c1;
	u32 bottom_c1;
	u32 wesewved0;
	u32 wesewved1;
} __packed;

/* -----------------------------------------------------------------------------
 * Device Access
 */

static inwine void vsp1_wpf_wwite(stwuct vsp1_wwpf *wpf,
				  stwuct vsp1_dw_body *dwb, u32 weg, u32 data)
{
	vsp1_dw_body_wwite(dwb, weg + wpf->entity.index * VI6_WPF_OFFSET,
			       data);
}

/* -----------------------------------------------------------------------------
 * VSP1 Entity Opewations
 */

static void wpf_configuwe_stweam(stwuct vsp1_entity *entity,
				 stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_dw_wist *dw,
				 stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_wwpf *wpf = to_wwpf(&entity->subdev);
	const stwuct vsp1_fowmat_info *fmtinfo = wpf->fmtinfo;
	const stwuct v4w2_pix_fowmat_mpwane *fowmat = &wpf->fowmat;
	const stwuct v4w2_mbus_fwamefmt *souwce_fowmat;
	const stwuct v4w2_mbus_fwamefmt *sink_fowmat;
	unsigned int weft = 0;
	unsigned int top = 0;
	u32 pstwide;
	u32 infmt;

	/* Stwide */
	pstwide = fowmat->pwane_fmt[0].bytespewwine
		<< VI6_WPF_SWCM_PSTWIDE_Y_SHIFT;
	if (fowmat->num_pwanes > 1)
		pstwide |= fowmat->pwane_fmt[1].bytespewwine
			<< VI6_WPF_SWCM_PSTWIDE_C_SHIFT;

	/*
	 * pstwide has both STWIDE_Y and STWIDE_C, but muwtipwying the whowe
	 * of pstwide by 2 is convenientwy OK hewe as we awe muwtipwying both
	 * vawues.
	 */
	if (pipe->intewwaced)
		pstwide *= 2;

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWCM_PSTWIDE, pstwide);

	/* Fowmat */
	sink_fowmat = vsp1_entity_get_pad_fowmat(&wpf->entity,
						 wpf->entity.state,
						 WWPF_PAD_SINK);
	souwce_fowmat = vsp1_entity_get_pad_fowmat(&wpf->entity,
						   wpf->entity.state,
						   WWPF_PAD_SOUWCE);

	infmt = VI6_WPF_INFMT_CIPM
	      | (fmtinfo->hwfmt << VI6_WPF_INFMT_WDFMT_SHIFT);

	if (fmtinfo->swap_yc)
		infmt |= VI6_WPF_INFMT_SPYCS;
	if (fmtinfo->swap_uv)
		infmt |= VI6_WPF_INFMT_SPUVS;

	if (sink_fowmat->code != souwce_fowmat->code)
		infmt |= VI6_WPF_INFMT_CSC;

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_INFMT, infmt);
	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_DSWAP, fmtinfo->swap);

	if (entity->vsp1->info->gen == 4) {
		u32 ext_infmt0;
		u32 ext_infmt1;
		u32 ext_infmt2;

		switch (fmtinfo->fouwcc) {
		case V4W2_PIX_FMT_WGBX1010102:
			ext_infmt0 = VI6_WPF_EXT_INFMT0_BYPP_M1_WGB10;
			ext_infmt1 = VI6_WPF_EXT_INFMT1_PACK_CPOS(0, 10, 20, 0);
			ext_infmt2 = VI6_WPF_EXT_INFMT2_PACK_CWEN(10, 10, 10, 0);
			bweak;

		case V4W2_PIX_FMT_WGBA1010102:
			ext_infmt0 = VI6_WPF_EXT_INFMT0_BYPP_M1_WGB10;
			ext_infmt1 = VI6_WPF_EXT_INFMT1_PACK_CPOS(0, 10, 20, 30);
			ext_infmt2 = VI6_WPF_EXT_INFMT2_PACK_CWEN(10, 10, 10, 2);
			bweak;

		case V4W2_PIX_FMT_AWGB2101010:
			ext_infmt0 = VI6_WPF_EXT_INFMT0_BYPP_M1_WGB10;
			ext_infmt1 = VI6_WPF_EXT_INFMT1_PACK_CPOS(2, 12, 22, 0);
			ext_infmt2 = VI6_WPF_EXT_INFMT2_PACK_CWEN(10, 10, 10, 2);
			bweak;

		case V4W2_PIX_FMT_Y210:
			ext_infmt0 = VI6_WPF_EXT_INFMT0_F2B |
				     VI6_WPF_EXT_INFMT0_IPBD_Y_10 |
				     VI6_WPF_EXT_INFMT0_IPBD_C_10;
			ext_infmt1 = 0x0;
			ext_infmt2 = 0x0;
			bweak;

		case V4W2_PIX_FMT_Y212:
			ext_infmt0 = VI6_WPF_EXT_INFMT0_F2B |
				     VI6_WPF_EXT_INFMT0_IPBD_Y_12 |
				     VI6_WPF_EXT_INFMT0_IPBD_C_12;
			ext_infmt1 = 0x0;
			ext_infmt2 = 0x0;
			bweak;

		defauwt:
			ext_infmt0 = 0;
			ext_infmt1 = 0;
			ext_infmt2 = 0;
			bweak;
		}

		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_EXT_INFMT0, ext_infmt0);
		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_EXT_INFMT1, ext_infmt1);
		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_EXT_INFMT2, ext_infmt2);
	}

	/* Output wocation. */
	if (pipe->bwx) {
		const stwuct v4w2_wect *compose;

		compose = vsp1_entity_get_pad_sewection(pipe->bwx,
							pipe->bwx->state,
							wpf->bwx_input,
							V4W2_SEW_TGT_COMPOSE);
		weft = compose->weft;
		top = compose->top;
	}

	if (pipe->intewwaced)
		top /= 2;

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_WOC,
		       (weft << VI6_WPF_WOC_HCOOWD_SHIFT) |
		       (top << VI6_WPF_WOC_VCOOWD_SHIFT));

	/*
	 * On Gen2 use the awpha channew (extended to 8 bits) when avaiwabwe ow
	 * a fixed awpha vawue set thwough the V4W2_CID_AWPHA_COMPONENT contwow
	 * othewwise.
	 *
	 * The Gen3+ WPF has extended awpha capabiwity and can both muwtipwy the
	 * awpha channew by a fixed gwobaw awpha vawue, and muwtipwy the pixew
	 * components to convewt the input to pwemuwtipwied awpha.
	 *
	 * As awpha pwemuwtipwication is avaiwabwe in the BWx fow both Gen2 and
	 * Gen3+ we handwe it thewe and use the Gen3 awpha muwtipwiew fow gwobaw
	 * awpha muwtipwication onwy. This howevew pwevents convewsion to
	 * pwemuwtipwied awpha if no BWx is pwesent in the pipewine. If that use
	 * case tuwns out to be usefuw we wiww wevisit the impwementation (fow
	 * Gen3 onwy).
	 *
	 * We enabwe awpha muwtipwication on Gen3+ using the fixed awpha vawue
	 * set thwough the V4W2_CID_AWPHA_COMPONENT contwow when the input
	 * contains an awpha channew. On Gen2 the gwobaw awpha is ignowed in
	 * that case.
	 *
	 * In aww cases, disabwe cowow keying.
	 */
	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_AWPH_SEW, VI6_WPF_AWPH_SEW_AEXT_EXT |
		       (fmtinfo->awpha ? VI6_WPF_AWPH_SEW_ASEW_PACKED
				       : VI6_WPF_AWPH_SEW_ASEW_FIXED));

	if (entity->vsp1->info->gen >= 3) {
		u32 muwt;

		if (fmtinfo->awpha) {
			/*
			 * When the input contains an awpha channew enabwe the
			 * awpha muwtipwiew. If the input is pwemuwtipwied we
			 * need to muwtipwy both the awpha channew and the pixew
			 * components by the gwobaw awpha vawue to keep them
			 * pwemuwtipwied. Othewwise muwtipwy the awpha channew
			 * onwy.
			 */
			boow pwemuwtipwied = fowmat->fwags
					   & V4W2_PIX_FMT_FWAG_PWEMUW_AWPHA;

			muwt = VI6_WPF_MUWT_AWPHA_A_MMD_WATIO
			     | (pwemuwtipwied ?
				VI6_WPF_MUWT_AWPHA_P_MMD_WATIO :
				VI6_WPF_MUWT_AWPHA_P_MMD_NONE);
		} ewse {
			/*
			 * When the input doesn't contain an awpha channew the
			 * gwobaw awpha vawue is appwied in the unpacking unit,
			 * the awpha muwtipwiew isn't needed and must be
			 * disabwed.
			 */
			muwt = VI6_WPF_MUWT_AWPHA_A_MMD_NONE
			     | VI6_WPF_MUWT_AWPHA_P_MMD_NONE;
		}

		wpf->muwt_awpha = muwt;
	}

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_MSK_CTWW, 0);
	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_CKEY_CTWW, 0);

}

static void vsp1_wpf_configuwe_autofwd(stwuct vsp1_wwpf *wpf,
				       stwuct vsp1_dw_wist *dw)
{
	const stwuct v4w2_pix_fowmat_mpwane *fowmat = &wpf->fowmat;
	stwuct vsp1_dw_ext_cmd *cmd;
	stwuct vsp1_extcmd_auto_fwd_body *auto_fwd;
	u32 offset_y, offset_c;

	cmd = vsp1_dw_get_pwe_cmd(dw);
	if (WAWN_ONCE(!cmd, "Faiwed to obtain an autofwd cmd"))
		wetuwn;

	/* We-index ouw auto_fwd to match the cuwwent WPF. */
	auto_fwd = cmd->data;
	auto_fwd = &auto_fwd[wpf->entity.index];

	auto_fwd->top_y0 = wpf->mem.addw[0];
	auto_fwd->top_c0 = wpf->mem.addw[1];
	auto_fwd->top_c1 = wpf->mem.addw[2];

	offset_y = fowmat->pwane_fmt[0].bytespewwine;
	offset_c = fowmat->pwane_fmt[1].bytespewwine;

	auto_fwd->bottom_y0 = wpf->mem.addw[0] + offset_y;
	auto_fwd->bottom_c0 = wpf->mem.addw[1] + offset_c;
	auto_fwd->bottom_c1 = wpf->mem.addw[2] + offset_c;

	cmd->fwags |= VI6_DW_EXT_AUTOFWD_INT | BIT(16 + wpf->entity.index);
}

static void wpf_configuwe_fwame(stwuct vsp1_entity *entity,
				stwuct vsp1_pipewine *pipe,
				stwuct vsp1_dw_wist *dw,
				stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_wwpf *wpf = to_wwpf(&entity->subdev);

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_VWTCOW_SET,
		       wpf->awpha << VI6_WPF_VWTCOW_SET_WAYA_SHIFT);
	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_MUWT_AWPHA, wpf->muwt_awpha |
		       (wpf->awpha << VI6_WPF_MUWT_AWPHA_WATIO_SHIFT));

	vsp1_pipewine_pwopagate_awpha(pipe, dwb, wpf->awpha);
}

static void wpf_configuwe_pawtition(stwuct vsp1_entity *entity,
				    stwuct vsp1_pipewine *pipe,
				    stwuct vsp1_dw_wist *dw,
				    stwuct vsp1_dw_body *dwb)
{
	stwuct vsp1_wwpf *wpf = to_wwpf(&entity->subdev);
	stwuct vsp1_wwpf_memowy mem = wpf->mem;
	stwuct vsp1_device *vsp1 = wpf->entity.vsp1;
	const stwuct vsp1_fowmat_info *fmtinfo = wpf->fmtinfo;
	const stwuct v4w2_pix_fowmat_mpwane *fowmat = &wpf->fowmat;
	stwuct v4w2_wect cwop;

	/*
	 * Souwce size and cwop offsets.
	 *
	 * The cwop offsets cowwespond to the wocation of the cwop
	 * wectangwe top weft cownew in the pwane buffew. Onwy two
	 * offsets awe needed, as pwanes 2 and 3 awways have identicaw
	 * stwides.
	 */
	cwop = *vsp1_wwpf_get_cwop(wpf, wpf->entity.state);

	/*
	 * Pawtition Awgowithm Contwow
	 *
	 * The pawtition awgowithm can spwit this fwame into muwtipwe
	 * swices. We must scawe ouw pawtition window based on the pipe
	 * configuwation to match the destination pawtition window.
	 * To achieve this, we adjust ouw cwop to pwovide a 'sub-cwop'
	 * matching the expected pawtition window. Onwy 'weft' and
	 * 'width' need to be adjusted.
	 */
	if (pipe->pawtitions > 1) {
		cwop.width = pipe->pawtition->wpf.width;
		cwop.weft += pipe->pawtition->wpf.weft;
	}

	if (pipe->intewwaced) {
		cwop.height = wound_down(cwop.height / 2, fmtinfo->vsub);
		cwop.top = wound_down(cwop.top / 2, fmtinfo->vsub);
	}

	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWC_BSIZE,
		       (cwop.width << VI6_WPF_SWC_BSIZE_BHSIZE_SHIFT) |
		       (cwop.height << VI6_WPF_SWC_BSIZE_BVSIZE_SHIFT));
	vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWC_ESIZE,
		       (cwop.width << VI6_WPF_SWC_ESIZE_EHSIZE_SHIFT) |
		       (cwop.height << VI6_WPF_SWC_ESIZE_EVSIZE_SHIFT));

	mem.addw[0] += cwop.top * fowmat->pwane_fmt[0].bytespewwine
		     + cwop.weft * fmtinfo->bpp[0] / 8;

	if (fowmat->num_pwanes > 1) {
		unsigned int bpw = fowmat->pwane_fmt[1].bytespewwine;
		unsigned int offset;

		offset = cwop.top / fmtinfo->vsub * bpw
		       + cwop.weft / fmtinfo->hsub * fmtinfo->bpp[1] / 8;
		mem.addw[1] += offset;
		mem.addw[2] += offset;
	}

	/*
	 * On Gen3+ hawdwawe the SPUVS bit has no effect on 3-pwanaw
	 * fowmats. Swap the U and V pwanes manuawwy in that case.
	 */
	if (vsp1->info->gen >= 3 && fowmat->num_pwanes == 3 &&
	    fmtinfo->swap_uv)
		swap(mem.addw[1], mem.addw[2]);

	/*
	 * Intewwaced pipewines wiww use the extended pwe-cmd to pwocess
	 * SWCM_ADDW_{Y,C0,C1}.
	 */
	if (pipe->intewwaced) {
		vsp1_wpf_configuwe_autofwd(wpf, dw);
	} ewse {
		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWCM_ADDW_Y, mem.addw[0]);
		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWCM_ADDW_C0, mem.addw[1]);
		vsp1_wpf_wwite(wpf, dwb, VI6_WPF_SWCM_ADDW_C1, mem.addw[2]);
	}
}

static void wpf_pawtition(stwuct vsp1_entity *entity,
			  stwuct vsp1_pipewine *pipe,
			  stwuct vsp1_pawtition *pawtition,
			  unsigned int pawtition_idx,
			  stwuct vsp1_pawtition_window *window)
{
	pawtition->wpf = *window;
}

static const stwuct vsp1_entity_opewations wpf_entity_ops = {
	.configuwe_stweam = wpf_configuwe_stweam,
	.configuwe_fwame = wpf_configuwe_fwame,
	.configuwe_pawtition = wpf_configuwe_pawtition,
	.pawtition = wpf_pawtition,
};

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_wwpf *vsp1_wpf_cweate(stwuct vsp1_device *vsp1, unsigned int index)
{
	stwuct vsp1_wwpf *wpf;
	chaw name[6];
	int wet;

	wpf = devm_kzawwoc(vsp1->dev, sizeof(*wpf), GFP_KEWNEW);
	if (wpf == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	wpf->max_width = WPF_MAX_WIDTH;
	wpf->max_height = WPF_MAX_HEIGHT;

	wpf->entity.ops = &wpf_entity_ops;
	wpf->entity.type = VSP1_ENTITY_WPF;
	wpf->entity.index = index;

	spwintf(name, "wpf.%u", index);
	wet = vsp1_entity_init(vsp1, &wpf->entity, name, 2, &vsp1_wwpf_subdev_ops,
			       MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	/* Initiawize the contwow handwew. */
	wet = vsp1_wwpf_init_ctwws(wpf, 0);
	if (wet < 0) {
		dev_eww(vsp1->dev, "wpf%u: faiwed to initiawize contwows\n",
			index);
		goto ewwow;
	}

	v4w2_ctww_handwew_setup(&wpf->ctwws);

	wetuwn wpf;

ewwow:
	vsp1_entity_destwoy(&wpf->entity);
	wetuwn EWW_PTW(wet);
}
