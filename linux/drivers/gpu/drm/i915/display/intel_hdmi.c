/*
 * Copywight 2006 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight © 2006-2009 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dispway/dwm_hdcp_hewpew.h>
#incwude <dwm/dispway/dwm_hdmi_hewpew.h>
#incwude <dwm/dispway/dwm_scdc_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/intew_wpe_audio.h>

#incwude "g4x_hdmi.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_audio.h"
#incwude "intew_connectow.h"
#incwude "intew_cx0_phy.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_gmbus.h"
#incwude "intew_hdcp.h"
#incwude "intew_hdcp_wegs.h"
#incwude "intew_hdmi.h"
#incwude "intew_wspcon.h"
#incwude "intew_panew.h"
#incwude "intew_snps_phy.h"

inwine stwuct dwm_i915_pwivate *intew_hdmi_to_i915(stwuct intew_hdmi *intew_hdmi)
{
	wetuwn to_i915(hdmi_to_dig_powt(intew_hdmi)->base.base.dev);
}

static void
assewt_hdmi_powt_disabwed(stwuct intew_hdmi *intew_hdmi)
{
	stwuct dwm_i915_pwivate *dev_pwiv = intew_hdmi_to_i915(intew_hdmi);
	u32 enabwed_bits;

	enabwed_bits = HAS_DDI(dev_pwiv) ? DDI_BUF_CTW_ENABWE : SDVO_ENABWE;

	dwm_WAWN(&dev_pwiv->dwm,
		 intew_de_wead(dev_pwiv, intew_hdmi->hdmi_weg) & enabwed_bits,
		 "HDMI powt enabwed, expecting disabwed\n");
}

static void
assewt_hdmi_twanscodew_func_disabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				     enum twanscodew cpu_twanscodew)
{
	dwm_WAWN(&dev_pwiv->dwm,
		 intew_de_wead(dev_pwiv, TWANS_DDI_FUNC_CTW(cpu_twanscodew)) &
		 TWANS_DDI_FUNC_ENABWE,
		 "HDMI twanscodew function enabwed, expecting disabwed\n");
}

static u32 g4x_infofwame_index(unsigned int type)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		wetuwn VIDEO_DIP_SEWECT_GAMUT;
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn VIDEO_DIP_SEWECT_AVI;
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn VIDEO_DIP_SEWECT_SPD;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn VIDEO_DIP_SEWECT_VENDOW;
	defauwt:
		MISSING_CASE(type);
		wetuwn 0;
	}
}

static u32 g4x_infofwame_enabwe(unsigned int type)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GENEWAW_CONTWOW:
		wetuwn VIDEO_DIP_ENABWE_GCP;
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		wetuwn VIDEO_DIP_ENABWE_GAMUT;
	case DP_SDP_VSC:
		wetuwn 0;
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn VIDEO_DIP_ENABWE_AVI;
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn VIDEO_DIP_ENABWE_SPD;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn VIDEO_DIP_ENABWE_VENDOW;
	case HDMI_INFOFWAME_TYPE_DWM:
		wetuwn 0;
	defauwt:
		MISSING_CASE(type);
		wetuwn 0;
	}
}

static u32 hsw_infofwame_enabwe(unsigned int type)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GENEWAW_CONTWOW:
		wetuwn VIDEO_DIP_ENABWE_GCP_HSW;
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		wetuwn VIDEO_DIP_ENABWE_GMP_HSW;
	case DP_SDP_VSC:
		wetuwn VIDEO_DIP_ENABWE_VSC_HSW;
	case DP_SDP_PPS:
		wetuwn VDIP_ENABWE_PPS;
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn VIDEO_DIP_ENABWE_AVI_HSW;
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn VIDEO_DIP_ENABWE_SPD_HSW;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn VIDEO_DIP_ENABWE_VS_HSW;
	case HDMI_INFOFWAME_TYPE_DWM:
		wetuwn VIDEO_DIP_ENABWE_DWM_GWK;
	defauwt:
		MISSING_CASE(type);
		wetuwn 0;
	}
}

static i915_weg_t
hsw_dip_data_weg(stwuct dwm_i915_pwivate *dev_pwiv,
		 enum twanscodew cpu_twanscodew,
		 unsigned int type,
		 int i)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		wetuwn HSW_TVIDEO_DIP_GMP_DATA(cpu_twanscodew, i);
	case DP_SDP_VSC:
		wetuwn HSW_TVIDEO_DIP_VSC_DATA(cpu_twanscodew, i);
	case DP_SDP_PPS:
		wetuwn ICW_VIDEO_DIP_PPS_DATA(cpu_twanscodew, i);
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn HSW_TVIDEO_DIP_AVI_DATA(cpu_twanscodew, i);
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn HSW_TVIDEO_DIP_SPD_DATA(cpu_twanscodew, i);
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn HSW_TVIDEO_DIP_VS_DATA(cpu_twanscodew, i);
	case HDMI_INFOFWAME_TYPE_DWM:
		wetuwn GWK_TVIDEO_DIP_DWM_DATA(cpu_twanscodew, i);
	defauwt:
		MISSING_CASE(type);
		wetuwn INVAWID_MMIO_WEG;
	}
}

static int hsw_dip_data_size(stwuct dwm_i915_pwivate *dev_pwiv,
			     unsigned int type)
{
	switch (type) {
	case DP_SDP_VSC:
		wetuwn VIDEO_DIP_VSC_DATA_SIZE;
	case DP_SDP_PPS:
		wetuwn VIDEO_DIP_PPS_DATA_SIZE;
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		if (DISPWAY_VEW(dev_pwiv) >= 11)
			wetuwn VIDEO_DIP_GMP_DATA_SIZE;
		ewse
			wetuwn VIDEO_DIP_DATA_SIZE;
	defauwt:
		wetuwn VIDEO_DIP_DATA_SIZE;
	}
}

static void g4x_wwite_infofwame(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				unsigned int type,
				const void *fwame, ssize_t wen)
{
	const u32 *data = fwame;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 vaw = intew_de_wead(dev_pwiv, VIDEO_DIP_CTW);
	int i;

	dwm_WAWN(&dev_pwiv->dwm, !(vaw & VIDEO_DIP_ENABWE),
		 "Wwiting DIP with CTW weg disabwed\n");

	vaw &= ~(VIDEO_DIP_SEWECT_MASK | 0xf); /* cweaw DIP data offset */
	vaw |= g4x_infofwame_index(type);

	vaw &= ~g4x_infofwame_enabwe(type);

	intew_de_wwite(dev_pwiv, VIDEO_DIP_CTW, vaw);

	fow (i = 0; i < wen; i += 4) {
		intew_de_wwite(dev_pwiv, VIDEO_DIP_DATA, *data);
		data++;
	}
	/* Wwite evewy possibwe data byte to fowce cowwect ECC cawcuwation. */
	fow (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		intew_de_wwite(dev_pwiv, VIDEO_DIP_DATA, 0);

	vaw |= g4x_infofwame_enabwe(type);
	vaw &= ~VIDEO_DIP_FWEQ_MASK;
	vaw |= VIDEO_DIP_FWEQ_VSYNC;

	intew_de_wwite(dev_pwiv, VIDEO_DIP_CTW, vaw);
	intew_de_posting_wead(dev_pwiv, VIDEO_DIP_CTW);
}

static void g4x_wead_infofwame(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       unsigned int type,
			       void *fwame, ssize_t wen)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 *data = fwame;
	int i;

	intew_de_wmw(dev_pwiv, VIDEO_DIP_CTW,
		     VIDEO_DIP_SEWECT_MASK | 0xf, g4x_infofwame_index(type));

	fow (i = 0; i < wen; i += 4)
		*data++ = intew_de_wead(dev_pwiv, VIDEO_DIP_DATA);
}

static u32 g4x_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 vaw = intew_de_wead(dev_pwiv, VIDEO_DIP_CTW);

	if ((vaw & VIDEO_DIP_ENABWE) == 0)
		wetuwn 0;

	if ((vaw & VIDEO_DIP_POWT_MASK) != VIDEO_DIP_POWT(encodew->powt))
		wetuwn 0;

	wetuwn vaw & (VIDEO_DIP_ENABWE_AVI |
		      VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_SPD);
}

static void ibx_wwite_infofwame(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				unsigned int type,
				const void *fwame, ssize_t wen)
{
	const u32 *data = fwame;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	i915_weg_t weg = TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	int i;

	dwm_WAWN(&dev_pwiv->dwm, !(vaw & VIDEO_DIP_ENABWE),
		 "Wwiting DIP with CTW weg disabwed\n");

	vaw &= ~(VIDEO_DIP_SEWECT_MASK | 0xf); /* cweaw DIP data offset */
	vaw |= g4x_infofwame_index(type);

	vaw &= ~g4x_infofwame_enabwe(type);

	intew_de_wwite(dev_pwiv, weg, vaw);

	fow (i = 0; i < wen; i += 4) {
		intew_de_wwite(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe),
			       *data);
		data++;
	}
	/* Wwite evewy possibwe data byte to fowce cowwect ECC cawcuwation. */
	fow (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		intew_de_wwite(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe), 0);

	vaw |= g4x_infofwame_enabwe(type);
	vaw &= ~VIDEO_DIP_FWEQ_MASK;
	vaw |= VIDEO_DIP_FWEQ_VSYNC;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);
}

static void ibx_wead_infofwame(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       unsigned int type,
			       void *fwame, ssize_t wen)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	u32 *data = fwame;
	int i;

	intew_de_wmw(dev_pwiv, TVIDEO_DIP_CTW(cwtc->pipe),
		     VIDEO_DIP_SEWECT_MASK | 0xf, g4x_infofwame_index(type));

	fow (i = 0; i < wen; i += 4)
		*data++ = intew_de_wead(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe));
}

static u32 ibx_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum pipe pipe = to_intew_cwtc(pipe_config->uapi.cwtc)->pipe;
	i915_weg_t weg = TVIDEO_DIP_CTW(pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);

	if ((vaw & VIDEO_DIP_ENABWE) == 0)
		wetuwn 0;

	if ((vaw & VIDEO_DIP_POWT_MASK) != VIDEO_DIP_POWT(encodew->powt))
		wetuwn 0;

	wetuwn vaw & (VIDEO_DIP_ENABWE_AVI |
		      VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		      VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
}

static void cpt_wwite_infofwame(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				unsigned int type,
				const void *fwame, ssize_t wen)
{
	const u32 *data = fwame;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	i915_weg_t weg = TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	int i;

	dwm_WAWN(&dev_pwiv->dwm, !(vaw & VIDEO_DIP_ENABWE),
		 "Wwiting DIP with CTW weg disabwed\n");

	vaw &= ~(VIDEO_DIP_SEWECT_MASK | 0xf); /* cweaw DIP data offset */
	vaw |= g4x_infofwame_index(type);

	/* The DIP contwow wegistew spec says that we need to update the AVI
	 * infofwame without cweawing its enabwe bit */
	if (type != HDMI_INFOFWAME_TYPE_AVI)
		vaw &= ~g4x_infofwame_enabwe(type);

	intew_de_wwite(dev_pwiv, weg, vaw);

	fow (i = 0; i < wen; i += 4) {
		intew_de_wwite(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe),
			       *data);
		data++;
	}
	/* Wwite evewy possibwe data byte to fowce cowwect ECC cawcuwation. */
	fow (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		intew_de_wwite(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe), 0);

	vaw |= g4x_infofwame_enabwe(type);
	vaw &= ~VIDEO_DIP_FWEQ_MASK;
	vaw |= VIDEO_DIP_FWEQ_VSYNC;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);
}

static void cpt_wead_infofwame(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       unsigned int type,
			       void *fwame, ssize_t wen)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	u32 *data = fwame;
	int i;

	intew_de_wmw(dev_pwiv, TVIDEO_DIP_CTW(cwtc->pipe),
		     VIDEO_DIP_SEWECT_MASK | 0xf, g4x_infofwame_index(type));

	fow (i = 0; i < wen; i += 4)
		*data++ = intew_de_wead(dev_pwiv, TVIDEO_DIP_DATA(cwtc->pipe));
}

static u32 cpt_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum pipe pipe = to_intew_cwtc(pipe_config->uapi.cwtc)->pipe;
	u32 vaw = intew_de_wead(dev_pwiv, TVIDEO_DIP_CTW(pipe));

	if ((vaw & VIDEO_DIP_ENABWE) == 0)
		wetuwn 0;

	wetuwn vaw & (VIDEO_DIP_ENABWE_AVI |
		      VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		      VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
}

static void vwv_wwite_infofwame(stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *cwtc_state,
				unsigned int type,
				const void *fwame, ssize_t wen)
{
	const u32 *data = fwame;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	i915_weg_t weg = VWV_TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	int i;

	dwm_WAWN(&dev_pwiv->dwm, !(vaw & VIDEO_DIP_ENABWE),
		 "Wwiting DIP with CTW weg disabwed\n");

	vaw &= ~(VIDEO_DIP_SEWECT_MASK | 0xf); /* cweaw DIP data offset */
	vaw |= g4x_infofwame_index(type);

	vaw &= ~g4x_infofwame_enabwe(type);

	intew_de_wwite(dev_pwiv, weg, vaw);

	fow (i = 0; i < wen; i += 4) {
		intew_de_wwite(dev_pwiv,
			       VWV_TVIDEO_DIP_DATA(cwtc->pipe), *data);
		data++;
	}
	/* Wwite evewy possibwe data byte to fowce cowwect ECC cawcuwation. */
	fow (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		intew_de_wwite(dev_pwiv,
			       VWV_TVIDEO_DIP_DATA(cwtc->pipe), 0);

	vaw |= g4x_infofwame_enabwe(type);
	vaw &= ~VIDEO_DIP_FWEQ_MASK;
	vaw |= VIDEO_DIP_FWEQ_VSYNC;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);
}

static void vwv_wead_infofwame(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       unsigned int type,
			       void *fwame, ssize_t wen)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	u32 *data = fwame;
	int i;

	intew_de_wmw(dev_pwiv, VWV_TVIDEO_DIP_CTW(cwtc->pipe),
		     VIDEO_DIP_SEWECT_MASK | 0xf, g4x_infofwame_index(type));

	fow (i = 0; i < wen; i += 4)
		*data++ = intew_de_wead(dev_pwiv,
				        VWV_TVIDEO_DIP_DATA(cwtc->pipe));
}

static u32 vwv_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum pipe pipe = to_intew_cwtc(pipe_config->uapi.cwtc)->pipe;
	u32 vaw = intew_de_wead(dev_pwiv, VWV_TVIDEO_DIP_CTW(pipe));

	if ((vaw & VIDEO_DIP_ENABWE) == 0)
		wetuwn 0;

	if ((vaw & VIDEO_DIP_POWT_MASK) != VIDEO_DIP_POWT(encodew->powt))
		wetuwn 0;

	wetuwn vaw & (VIDEO_DIP_ENABWE_AVI |
		      VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		      VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
}

void hsw_wwite_infofwame(stwuct intew_encodew *encodew,
			 const stwuct intew_cwtc_state *cwtc_state,
			 unsigned int type,
			 const void *fwame, ssize_t wen)
{
	const u32 *data = fwame;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	i915_weg_t ctw_weg = HSW_TVIDEO_DIP_CTW(cpu_twanscodew);
	int data_size;
	int i;
	u32 vaw = intew_de_wead(dev_pwiv, ctw_weg);

	data_size = hsw_dip_data_size(dev_pwiv, type);

	dwm_WAWN_ON(&dev_pwiv->dwm, wen > data_size);

	vaw &= ~hsw_infofwame_enabwe(type);
	intew_de_wwite(dev_pwiv, ctw_weg, vaw);

	fow (i = 0; i < wen; i += 4) {
		intew_de_wwite(dev_pwiv,
			       hsw_dip_data_weg(dev_pwiv, cpu_twanscodew, type, i >> 2),
			       *data);
		data++;
	}
	/* Wwite evewy possibwe data byte to fowce cowwect ECC cawcuwation. */
	fow (; i < data_size; i += 4)
		intew_de_wwite(dev_pwiv,
			       hsw_dip_data_weg(dev_pwiv, cpu_twanscodew, type, i >> 2),
			       0);

	/* Wa_14013475917 */
	if (IS_DISPWAY_VEW(dev_pwiv, 13, 14) && cwtc_state->has_psw && type == DP_SDP_VSC)
		wetuwn;

	vaw |= hsw_infofwame_enabwe(type);
	intew_de_wwite(dev_pwiv, ctw_weg, vaw);
	intew_de_posting_wead(dev_pwiv, ctw_weg);
}

void hsw_wead_infofwame(stwuct intew_encodew *encodew,
			const stwuct intew_cwtc_state *cwtc_state,
			unsigned int type, void *fwame, ssize_t wen)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	u32 *data = fwame;
	int i;

	fow (i = 0; i < wen; i += 4)
		*data++ = intew_de_wead(dev_pwiv,
				        hsw_dip_data_weg(dev_pwiv, cpu_twanscodew, type, i >> 2));
}

static u32 hsw_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 vaw = intew_de_wead(dev_pwiv,
				HSW_TVIDEO_DIP_CTW(pipe_config->cpu_twanscodew));
	u32 mask;

	mask = (VIDEO_DIP_ENABWE_VSC_HSW | VIDEO_DIP_ENABWE_AVI_HSW |
		VIDEO_DIP_ENABWE_GCP_HSW | VIDEO_DIP_ENABWE_VS_HSW |
		VIDEO_DIP_ENABWE_GMP_HSW | VIDEO_DIP_ENABWE_SPD_HSW);

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		mask |= VIDEO_DIP_ENABWE_DWM_GWK;

	wetuwn vaw & mask;
}

static const u8 infofwame_type_to_idx[] = {
	HDMI_PACKET_TYPE_GENEWAW_CONTWOW,
	HDMI_PACKET_TYPE_GAMUT_METADATA,
	DP_SDP_VSC,
	HDMI_INFOFWAME_TYPE_AVI,
	HDMI_INFOFWAME_TYPE_SPD,
	HDMI_INFOFWAME_TYPE_VENDOW,
	HDMI_INFOFWAME_TYPE_DWM,
};

u32 intew_hdmi_infofwame_enabwe(unsigned int type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(infofwame_type_to_idx); i++) {
		if (infofwame_type_to_idx[i] == type)
			wetuwn BIT(i);
	}

	wetuwn 0;
}

u32 intew_hdmi_infofwames_enabwed(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	u32 vaw, wet = 0;
	int i;

	vaw = dig_powt->infofwames_enabwed(encodew, cwtc_state);

	/* map fwom hawdwawe bits to dip idx */
	fow (i = 0; i < AWWAY_SIZE(infofwame_type_to_idx); i++) {
		unsigned int type = infofwame_type_to_idx[i];

		if (HAS_DDI(dev_pwiv)) {
			if (vaw & hsw_infofwame_enabwe(type))
				wet |= BIT(i);
		} ewse {
			if (vaw & g4x_infofwame_enabwe(type))
				wet |= BIT(i);
		}
	}

	wetuwn wet;
}

/*
 * The data we wwite to the DIP data buffew wegistews is 1 byte biggew than the
 * HDMI infofwame size because of an ECC/wesewved byte at position 3 (stawting
 * at 0). It's awso a byte used by DispwayPowt so the same DIP wegistews can be
 * used fow both technowogies.
 *
 * DW0: Wesewved/ECC/DP | HB2 | HB1 | HB0
 * DW1:       DB3       | DB2 | DB1 | DB0
 * DW2:       DB7       | DB6 | DB5 | DB4
 * DW3: ...
 *
 * (HB is Headew Byte, DB is Data Byte)
 *
 * The hdmi pack() functions don't know about that hawdwawe specific howe so we
 * twick them by giving an offset into the buffew and moving back the headew
 * bytes by one.
 */
static void intew_wwite_infofwame(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state,
				  enum hdmi_infofwame_type type,
				  const union hdmi_infofwame *fwame)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	u8 buffew[VIDEO_DIP_DATA_SIZE];
	ssize_t wen;

	if ((cwtc_state->infofwames.enabwe &
	     intew_hdmi_infofwame_enabwe(type)) == 0)
		wetuwn;

	if (dwm_WAWN_ON(encodew->base.dev, fwame->any.type != type))
		wetuwn;

	/* see comment above fow the weason fow this offset */
	wen = hdmi_infofwame_pack_onwy(fwame, buffew + 1, sizeof(buffew) - 1);
	if (dwm_WAWN_ON(encodew->base.dev, wen < 0))
		wetuwn;

	/* Insewt the 'howe' (see big comment above) at position 3 */
	memmove(&buffew[0], &buffew[1], 3);
	buffew[3] = 0;
	wen++;

	dig_powt->wwite_infofwame(encodew, cwtc_state, type, buffew, wen);
}

void intew_wead_infofwame(stwuct intew_encodew *encodew,
			  const stwuct intew_cwtc_state *cwtc_state,
			  enum hdmi_infofwame_type type,
			  union hdmi_infofwame *fwame)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	u8 buffew[VIDEO_DIP_DATA_SIZE];
	int wet;

	if ((cwtc_state->infofwames.enabwe &
	     intew_hdmi_infofwame_enabwe(type)) == 0)
		wetuwn;

	dig_powt->wead_infofwame(encodew, cwtc_state,
				       type, buffew, sizeof(buffew));

	/* Fiww the 'howe' (see big comment above) at position 3 */
	memmove(&buffew[1], &buffew[0], 3);

	/* see comment above fow the weason fow this offset */
	wet = hdmi_infofwame_unpack(fwame, buffew + 1, sizeof(buffew) - 1);
	if (wet) {
		dwm_dbg_kms(encodew->base.dev,
			    "Faiwed to unpack infofwame type 0x%02x\n", type);
		wetuwn;
	}

	if (fwame->any.type != type)
		dwm_dbg_kms(encodew->base.dev,
			    "Found the wwong infofwame type 0x%x (expected 0x%02x)\n",
			    fwame->any.type, type);
}

static boow
intew_hdmi_compute_avi_infofwame(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *cwtc_state,
				 stwuct dwm_connectow_state *conn_state)
{
	stwuct hdmi_avi_infofwame *fwame = &cwtc_state->infofwames.avi.avi;
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	stwuct dwm_connectow *connectow = conn_state->connectow;
	int wet;

	if (!cwtc_state->has_infofwame)
		wetuwn twue;

	cwtc_state->infofwames.enabwe |=
		intew_hdmi_infofwame_enabwe(HDMI_INFOFWAME_TYPE_AVI);

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(fwame, connectow,
						       adjusted_mode);
	if (wet)
		wetuwn fawse;

	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420)
		fwame->cowowspace = HDMI_COWOWSPACE_YUV420;
	ewse if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444)
		fwame->cowowspace = HDMI_COWOWSPACE_YUV444;
	ewse
		fwame->cowowspace = HDMI_COWOWSPACE_WGB;

	dwm_hdmi_avi_infofwame_cowowimetwy(fwame, conn_state);

	/* nonsense combination */
	dwm_WAWN_ON(encodew->base.dev, cwtc_state->wimited_cowow_wange &&
		    cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB);

	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_WGB) {
		dwm_hdmi_avi_infofwame_quant_wange(fwame, connectow,
						   adjusted_mode,
						   cwtc_state->wimited_cowow_wange ?
						   HDMI_QUANTIZATION_WANGE_WIMITED :
						   HDMI_QUANTIZATION_WANGE_FUWW);
	} ewse {
		fwame->quantization_wange = HDMI_QUANTIZATION_WANGE_DEFAUWT;
		fwame->ycc_quantization_wange = HDMI_YCC_QUANTIZATION_WANGE_WIMITED;
	}

	dwm_hdmi_avi_infofwame_content_type(fwame, conn_state);

	/* TODO: handwe pixew wepetition fow YCBCW420 outputs */

	wet = hdmi_avi_infofwame_check(fwame);
	if (dwm_WAWN_ON(encodew->base.dev, wet))
		wetuwn fawse;

	wetuwn twue;
}

static boow
intew_hdmi_compute_spd_infofwame(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *cwtc_state,
				 stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct hdmi_spd_infofwame *fwame = &cwtc_state->infofwames.spd.spd;
	int wet;

	if (!cwtc_state->has_infofwame)
		wetuwn twue;

	cwtc_state->infofwames.enabwe |=
		intew_hdmi_infofwame_enabwe(HDMI_INFOFWAME_TYPE_SPD);

	if (IS_DGFX(i915))
		wet = hdmi_spd_infofwame_init(fwame, "Intew", "Discwete gfx");
	ewse
		wet = hdmi_spd_infofwame_init(fwame, "Intew", "Integwated gfx");

	if (dwm_WAWN_ON(encodew->base.dev, wet))
		wetuwn fawse;

	fwame->sdi = HDMI_SPD_SDI_PC;

	wet = hdmi_spd_infofwame_check(fwame);
	if (dwm_WAWN_ON(encodew->base.dev, wet))
		wetuwn fawse;

	wetuwn twue;
}

static boow
intew_hdmi_compute_hdmi_infofwame(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state,
				  stwuct dwm_connectow_state *conn_state)
{
	stwuct hdmi_vendow_infofwame *fwame =
		&cwtc_state->infofwames.hdmi.vendow.hdmi;
	const stwuct dwm_dispway_info *info =
		&conn_state->connectow->dispway_info;
	int wet;

	if (!cwtc_state->has_infofwame || !info->has_hdmi_infofwame)
		wetuwn twue;

	cwtc_state->infofwames.enabwe |=
		intew_hdmi_infofwame_enabwe(HDMI_INFOFWAME_TYPE_VENDOW);

	wet = dwm_hdmi_vendow_infofwame_fwom_dispway_mode(fwame,
							  conn_state->connectow,
							  &cwtc_state->hw.adjusted_mode);
	if (dwm_WAWN_ON(encodew->base.dev, wet))
		wetuwn fawse;

	wet = hdmi_vendow_infofwame_check(fwame);
	if (dwm_WAWN_ON(encodew->base.dev, wet))
		wetuwn fawse;

	wetuwn twue;
}

static boow
intew_hdmi_compute_dwm_infofwame(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *cwtc_state,
				 stwuct dwm_connectow_state *conn_state)
{
	stwuct hdmi_dwm_infofwame *fwame = &cwtc_state->infofwames.dwm.dwm;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	int wet;

	if (DISPWAY_VEW(dev_pwiv) < 10)
		wetuwn twue;

	if (!cwtc_state->has_infofwame)
		wetuwn twue;

	if (!conn_state->hdw_output_metadata)
		wetuwn twue;

	cwtc_state->infofwames.enabwe |=
		intew_hdmi_infofwame_enabwe(HDMI_INFOFWAME_TYPE_DWM);

	wet = dwm_hdmi_infofwame_set_hdw_metadata(fwame, conn_state);
	if (wet < 0) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "couwdn't set HDW metadata in infofwame\n");
		wetuwn fawse;
	}

	wet = hdmi_dwm_infofwame_check(fwame);
	if (dwm_WAWN_ON(&dev_pwiv->dwm, wet))
		wetuwn fawse;

	wetuwn twue;
}

static void g4x_set_infofwames(stwuct intew_encodew *encodew,
			       boow enabwe,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_hdmi *intew_hdmi = &dig_powt->hdmi;
	i915_weg_t weg = VIDEO_DIP_CTW;
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	u32 powt = VIDEO_DIP_POWT(encodew->powt);

	assewt_hdmi_powt_disabwed(intew_hdmi);

	/* If the wegistews wewe not initiawized yet, they might be zewoes,
	 * which means we'we sewecting the AVI DIP and we'we setting its
	 * fwequency to once. This seems to weawwy confuse the HW and make
	 * things stop wowking (the wegistew spec says the AVI awways needs to
	 * be sent evewy VSync). So hewe we avoid wwiting to the wegistew mowe
	 * than we need and awso expwicitwy sewect the AVI DIP and expwicitwy
	 * set its fwequency to evewy VSync. Avoiding to wwite it twice seems to
	 * be enough to sowve the pwobwem, but being defensive shouwdn't huwt us
	 * eithew. */
	vaw |= VIDEO_DIP_SEWECT_AVI | VIDEO_DIP_FWEQ_VSYNC;

	if (!enabwe) {
		if (!(vaw & VIDEO_DIP_ENABWE))
			wetuwn;
		if (powt != (vaw & VIDEO_DIP_POWT_MASK)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "video DIP stiww enabwed on powt %c\n",
				    (vaw & VIDEO_DIP_POWT_MASK) >> 29);
			wetuwn;
		}
		vaw &= ~(VIDEO_DIP_ENABWE | VIDEO_DIP_ENABWE_AVI |
			 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_SPD);
		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);
		wetuwn;
	}

	if (powt != (vaw & VIDEO_DIP_POWT_MASK)) {
		if (vaw & VIDEO_DIP_ENABWE) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "video DIP awweady enabwed on powt %c\n",
				    (vaw & VIDEO_DIP_POWT_MASK) >> 29);
			wetuwn;
		}
		vaw &= ~VIDEO_DIP_POWT_MASK;
		vaw |= powt;
	}

	vaw |= VIDEO_DIP_ENABWE;
	vaw &= ~(VIDEO_DIP_ENABWE_AVI |
		 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_SPD);

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);

	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_AVI,
			      &cwtc_state->infofwames.avi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_SPD,
			      &cwtc_state->infofwames.spd);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_VENDOW,
			      &cwtc_state->infofwames.hdmi);
}

/*
 * Detewmine if defauwt_phase=1 can be indicated in the GCP infofwame.
 *
 * Fwom HDMI specification 1.4a:
 * - The fiwst pixew of each Video Data Pewiod shaww awways have a pixew packing phase of 0
 * - The fiwst pixew fowwowing each Video Data Pewiod shaww have a pixew packing phase of 0
 * - The PP bits shaww be constant fow aww GCPs and wiww be equaw to the wast packing phase
 * - The fiwst pixew fowwowing evewy twansition of HSYNC ow VSYNC shaww have a pixew packing
 *   phase of 0
 */
static boow gcp_defauwt_phase_possibwe(int pipe_bpp,
				       const stwuct dwm_dispway_mode *mode)
{
	unsigned int pixews_pew_gwoup;

	switch (pipe_bpp) {
	case 30:
		/* 4 pixews in 5 cwocks */
		pixews_pew_gwoup = 4;
		bweak;
	case 36:
		/* 2 pixews in 3 cwocks */
		pixews_pew_gwoup = 2;
		bweak;
	case 48:
		/* 1 pixew in 2 cwocks */
		pixews_pew_gwoup = 1;
		bweak;
	defauwt:
		/* phase infowmation not wewevant fow 8bpc */
		wetuwn fawse;
	}

	wetuwn mode->cwtc_hdispway % pixews_pew_gwoup == 0 &&
		mode->cwtc_htotaw % pixews_pew_gwoup == 0 &&
		mode->cwtc_hbwank_stawt % pixews_pew_gwoup == 0 &&
		mode->cwtc_hbwank_end % pixews_pew_gwoup == 0 &&
		mode->cwtc_hsync_stawt % pixews_pew_gwoup == 0 &&
		mode->cwtc_hsync_end % pixews_pew_gwoup == 0 &&
		((mode->fwags & DWM_MODE_FWAG_INTEWWACE) == 0 ||
		 mode->cwtc_htotaw/2 % pixews_pew_gwoup == 0);
}

static boow intew_hdmi_set_gcp_infofwame(stwuct intew_encodew *encodew,
					 const stwuct intew_cwtc_state *cwtc_state,
					 const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	i915_weg_t weg;

	if ((cwtc_state->infofwames.enabwe &
	     intew_hdmi_infofwame_enabwe(HDMI_PACKET_TYPE_GENEWAW_CONTWOW)) == 0)
		wetuwn fawse;

	if (HAS_DDI(dev_pwiv))
		weg = HSW_TVIDEO_DIP_GCP(cwtc_state->cpu_twanscodew);
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		weg = VWV_TVIDEO_DIP_GCP(cwtc->pipe);
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		weg = TVIDEO_DIP_GCP(cwtc->pipe);
	ewse
		wetuwn fawse;

	intew_de_wwite(dev_pwiv, weg, cwtc_state->infofwames.gcp);

	wetuwn twue;
}

void intew_hdmi_wead_gcp_infofwame(stwuct intew_encodew *encodew,
				   stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	i915_weg_t weg;

	if ((cwtc_state->infofwames.enabwe &
	     intew_hdmi_infofwame_enabwe(HDMI_PACKET_TYPE_GENEWAW_CONTWOW)) == 0)
		wetuwn;

	if (HAS_DDI(dev_pwiv))
		weg = HSW_TVIDEO_DIP_GCP(cwtc_state->cpu_twanscodew);
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		weg = VWV_TVIDEO_DIP_GCP(cwtc->pipe);
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		weg = TVIDEO_DIP_GCP(cwtc->pipe);
	ewse
		wetuwn;

	cwtc_state->infofwames.gcp = intew_de_wead(dev_pwiv, weg);
}

static void intew_hdmi_compute_gcp_infofwame(stwuct intew_encodew *encodew,
					     stwuct intew_cwtc_state *cwtc_state,
					     stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (IS_G4X(dev_pwiv) || !cwtc_state->has_infofwame)
		wetuwn;

	cwtc_state->infofwames.enabwe |=
		intew_hdmi_infofwame_enabwe(HDMI_PACKET_TYPE_GENEWAW_CONTWOW);

	/* Indicate cowow indication fow deep cowow mode */
	if (cwtc_state->pipe_bpp > 24)
		cwtc_state->infofwames.gcp |= GCP_COWOW_INDICATION;

	/* Enabwe defauwt_phase whenevew the dispway mode is suitabwy awigned */
	if (gcp_defauwt_phase_possibwe(cwtc_state->pipe_bpp,
				       &cwtc_state->hw.adjusted_mode))
		cwtc_state->infofwames.gcp |= GCP_DEFAUWT_PHASE_ENABWE;
}

static void ibx_set_infofwames(stwuct intew_encodew *encodew,
			       boow enabwe,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_hdmi *intew_hdmi = &dig_powt->hdmi;
	i915_weg_t weg = TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	u32 powt = VIDEO_DIP_POWT(encodew->powt);

	assewt_hdmi_powt_disabwed(intew_hdmi);

	/* See the big comment in g4x_set_infofwames() */
	vaw |= VIDEO_DIP_SEWECT_AVI | VIDEO_DIP_FWEQ_VSYNC;

	if (!enabwe) {
		if (!(vaw & VIDEO_DIP_ENABWE))
			wetuwn;
		vaw &= ~(VIDEO_DIP_ENABWE | VIDEO_DIP_ENABWE_AVI |
			 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
			 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);
		wetuwn;
	}

	if (powt != (vaw & VIDEO_DIP_POWT_MASK)) {
		dwm_WAWN(&dev_pwiv->dwm, vaw & VIDEO_DIP_ENABWE,
			 "DIP awweady enabwed on powt %c\n",
			 (vaw & VIDEO_DIP_POWT_MASK) >> 29);
		vaw &= ~VIDEO_DIP_POWT_MASK;
		vaw |= powt;
	}

	vaw |= VIDEO_DIP_ENABWE;
	vaw &= ~(VIDEO_DIP_ENABWE_AVI |
		 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);

	if (intew_hdmi_set_gcp_infofwame(encodew, cwtc_state, conn_state))
		vaw |= VIDEO_DIP_ENABWE_GCP;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);

	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_AVI,
			      &cwtc_state->infofwames.avi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_SPD,
			      &cwtc_state->infofwames.spd);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_VENDOW,
			      &cwtc_state->infofwames.hdmi);
}

static void cpt_set_infofwames(stwuct intew_encodew *encodew,
			       boow enabwe,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_hdmi *intew_hdmi = enc_to_intew_hdmi(encodew);
	i915_weg_t weg = TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);

	assewt_hdmi_powt_disabwed(intew_hdmi);

	/* See the big comment in g4x_set_infofwames() */
	vaw |= VIDEO_DIP_SEWECT_AVI | VIDEO_DIP_FWEQ_VSYNC;

	if (!enabwe) {
		if (!(vaw & VIDEO_DIP_ENABWE))
			wetuwn;
		vaw &= ~(VIDEO_DIP_ENABWE | VIDEO_DIP_ENABWE_AVI |
			 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
			 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);
		wetuwn;
	}

	/* Set both togethew, unset both togethew: see the spec. */
	vaw |= VIDEO_DIP_ENABWE | VIDEO_DIP_ENABWE_AVI;
	vaw &= ~(VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);

	if (intew_hdmi_set_gcp_infofwame(encodew, cwtc_state, conn_state))
		vaw |= VIDEO_DIP_ENABWE_GCP;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);

	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_AVI,
			      &cwtc_state->infofwames.avi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_SPD,
			      &cwtc_state->infofwames.spd);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_VENDOW,
			      &cwtc_state->infofwames.hdmi);
}

static void vwv_set_infofwames(stwuct intew_encodew *encodew,
			       boow enabwe,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_hdmi *intew_hdmi = enc_to_intew_hdmi(encodew);
	i915_weg_t weg = VWV_TVIDEO_DIP_CTW(cwtc->pipe);
	u32 vaw = intew_de_wead(dev_pwiv, weg);
	u32 powt = VIDEO_DIP_POWT(encodew->powt);

	assewt_hdmi_powt_disabwed(intew_hdmi);

	/* See the big comment in g4x_set_infofwames() */
	vaw |= VIDEO_DIP_SEWECT_AVI | VIDEO_DIP_FWEQ_VSYNC;

	if (!enabwe) {
		if (!(vaw & VIDEO_DIP_ENABWE))
			wetuwn;
		vaw &= ~(VIDEO_DIP_ENABWE | VIDEO_DIP_ENABWE_AVI |
			 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
			 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);
		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);
		wetuwn;
	}

	if (powt != (vaw & VIDEO_DIP_POWT_MASK)) {
		dwm_WAWN(&dev_pwiv->dwm, vaw & VIDEO_DIP_ENABWE,
			 "DIP awweady enabwed on powt %c\n",
			 (vaw & VIDEO_DIP_POWT_MASK) >> 29);
		vaw &= ~VIDEO_DIP_POWT_MASK;
		vaw |= powt;
	}

	vaw |= VIDEO_DIP_ENABWE;
	vaw &= ~(VIDEO_DIP_ENABWE_AVI |
		 VIDEO_DIP_ENABWE_VENDOW | VIDEO_DIP_ENABWE_GAMUT |
		 VIDEO_DIP_ENABWE_SPD | VIDEO_DIP_ENABWE_GCP);

	if (intew_hdmi_set_gcp_infofwame(encodew, cwtc_state, conn_state))
		vaw |= VIDEO_DIP_ENABWE_GCP;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);

	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_AVI,
			      &cwtc_state->infofwames.avi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_SPD,
			      &cwtc_state->infofwames.spd);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_VENDOW,
			      &cwtc_state->infofwames.hdmi);
}

static void hsw_set_infofwames(stwuct intew_encodew *encodew,
			       boow enabwe,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	i915_weg_t weg = HSW_TVIDEO_DIP_CTW(cwtc_state->cpu_twanscodew);
	u32 vaw = intew_de_wead(dev_pwiv, weg);

	assewt_hdmi_twanscodew_func_disabwed(dev_pwiv,
					     cwtc_state->cpu_twanscodew);

	vaw &= ~(VIDEO_DIP_ENABWE_VSC_HSW | VIDEO_DIP_ENABWE_AVI_HSW |
		 VIDEO_DIP_ENABWE_GCP_HSW | VIDEO_DIP_ENABWE_VS_HSW |
		 VIDEO_DIP_ENABWE_GMP_HSW | VIDEO_DIP_ENABWE_SPD_HSW |
		 VIDEO_DIP_ENABWE_DWM_GWK);

	if (!enabwe) {
		intew_de_wwite(dev_pwiv, weg, vaw);
		intew_de_posting_wead(dev_pwiv, weg);
		wetuwn;
	}

	if (intew_hdmi_set_gcp_infofwame(encodew, cwtc_state, conn_state))
		vaw |= VIDEO_DIP_ENABWE_GCP_HSW;

	intew_de_wwite(dev_pwiv, weg, vaw);
	intew_de_posting_wead(dev_pwiv, weg);

	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_AVI,
			      &cwtc_state->infofwames.avi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_SPD,
			      &cwtc_state->infofwames.spd);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_VENDOW,
			      &cwtc_state->infofwames.hdmi);
	intew_wwite_infofwame(encodew, cwtc_state,
			      HDMI_INFOFWAME_TYPE_DWM,
			      &cwtc_state->infofwames.dwm);
}

void intew_dp_duaw_mode_set_tmds_output(stwuct intew_hdmi *hdmi, boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = intew_hdmi_to_i915(hdmi);
	stwuct i2c_adaptew *ddc = hdmi->attached_connectow->base.ddc;

	if (hdmi->dp_duaw_mode.type < DWM_DP_DUAW_MODE_TYPE2_DVI)
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm, "%s DP duaw mode adaptow TMDS output\n",
		    enabwe ? "Enabwing" : "Disabwing");

	dwm_dp_duaw_mode_set_tmds_output(&dev_pwiv->dwm,
					 hdmi->dp_duaw_mode.type, ddc, enabwe);
}

static int intew_hdmi_hdcp_wead(stwuct intew_digitaw_powt *dig_powt,
				unsigned int offset, void *buffew, size_t size)
{
	stwuct intew_hdmi *hdmi = &dig_powt->hdmi;
	stwuct i2c_adaptew *ddc = hdmi->attached_connectow->base.ddc;
	int wet;
	u8 stawt = offset & 0xff;
	stwuct i2c_msg msgs[] = {
		{
			.addw = DWM_HDCP_DDC_ADDW,
			.fwags = 0,
			.wen = 1,
			.buf = &stawt,
		},
		{
			.addw = DWM_HDCP_DDC_ADDW,
			.fwags = I2C_M_WD,
			.wen = size,
			.buf = buffew
		}
	};
	wet = i2c_twansfew(ddc, msgs, AWWAY_SIZE(msgs));
	if (wet == AWWAY_SIZE(msgs))
		wetuwn 0;
	wetuwn wet >= 0 ? -EIO : wet;
}

static int intew_hdmi_hdcp_wwite(stwuct intew_digitaw_powt *dig_powt,
				 unsigned int offset, void *buffew, size_t size)
{
	stwuct intew_hdmi *hdmi = &dig_powt->hdmi;
	stwuct i2c_adaptew *ddc = hdmi->attached_connectow->base.ddc;
	int wet;
	u8 *wwite_buf;
	stwuct i2c_msg msg;

	wwite_buf = kzawwoc(size + 1, GFP_KEWNEW);
	if (!wwite_buf)
		wetuwn -ENOMEM;

	wwite_buf[0] = offset & 0xff;
	memcpy(&wwite_buf[1], buffew, size);

	msg.addw = DWM_HDCP_DDC_ADDW;
	msg.fwags = 0,
	msg.wen = size + 1,
	msg.buf = wwite_buf;

	wet = i2c_twansfew(ddc, &msg, 1);
	if (wet == 1)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	kfwee(wwite_buf);
	wetuwn wet;
}

static
int intew_hdmi_hdcp_wwite_an_aksv(stwuct intew_digitaw_powt *dig_powt,
				  u8 *an)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_hdmi *hdmi = &dig_powt->hdmi;
	stwuct i2c_adaptew *ddc = hdmi->attached_connectow->base.ddc;
	int wet;

	wet = intew_hdmi_hdcp_wwite(dig_powt, DWM_HDCP_DDC_AN, an,
				    DWM_HDCP_AN_WEN);
	if (wet) {
		dwm_dbg_kms(&i915->dwm, "Wwite An ovew DDC faiwed (%d)\n",
			    wet);
		wetuwn wet;
	}

	wet = intew_gmbus_output_aksv(ddc);
	if (wet < 0) {
		dwm_dbg_kms(&i915->dwm, "Faiwed to output aksv (%d)\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int intew_hdmi_hdcp_wead_bksv(stwuct intew_digitaw_powt *dig_powt,
				     u8 *bksv)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);

	int wet;
	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_BKSV, bksv,
				   DWM_HDCP_KSV_WEN);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "Wead Bksv ovew DDC faiwed (%d)\n",
			    wet);
	wetuwn wet;
}

static
int intew_hdmi_hdcp_wead_bstatus(stwuct intew_digitaw_powt *dig_powt,
				 u8 *bstatus)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);

	int wet;
	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_BSTATUS,
				   bstatus, DWM_HDCP_BSTATUS_WEN);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "Wead bstatus ovew DDC faiwed (%d)\n",
			    wet);
	wetuwn wet;
}

static
int intew_hdmi_hdcp_wepeatew_pwesent(stwuct intew_digitaw_powt *dig_powt,
				     boow *wepeatew_pwesent)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	int wet;
	u8 vaw;

	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_BCAPS, &vaw, 1);
	if (wet) {
		dwm_dbg_kms(&i915->dwm, "Wead bcaps ovew DDC faiwed (%d)\n",
			    wet);
		wetuwn wet;
	}
	*wepeatew_pwesent = vaw & DWM_HDCP_DDC_BCAPS_WEPEATEW_PWESENT;
	wetuwn 0;
}

static
int intew_hdmi_hdcp_wead_wi_pwime(stwuct intew_digitaw_powt *dig_powt,
				  u8 *wi_pwime)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);

	int wet;
	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_WI_PWIME,
				   wi_pwime, DWM_HDCP_WI_WEN);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "Wead Wi' ovew DDC faiwed (%d)\n",
			    wet);
	wetuwn wet;
}

static
int intew_hdmi_hdcp_wead_ksv_weady(stwuct intew_digitaw_powt *dig_powt,
				   boow *ksv_weady)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	int wet;
	u8 vaw;

	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_BCAPS, &vaw, 1);
	if (wet) {
		dwm_dbg_kms(&i915->dwm, "Wead bcaps ovew DDC faiwed (%d)\n",
			    wet);
		wetuwn wet;
	}
	*ksv_weady = vaw & DWM_HDCP_DDC_BCAPS_KSV_FIFO_WEADY;
	wetuwn 0;
}

static
int intew_hdmi_hdcp_wead_ksv_fifo(stwuct intew_digitaw_powt *dig_powt,
				  int num_downstweam, u8 *ksv_fifo)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	int wet;
	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_KSV_FIFO,
				   ksv_fifo, num_downstweam * DWM_HDCP_KSV_WEN);
	if (wet) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead ksv fifo ovew DDC faiwed (%d)\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static
int intew_hdmi_hdcp_wead_v_pwime_pawt(stwuct intew_digitaw_powt *dig_powt,
				      int i, u32 *pawt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	int wet;

	if (i >= DWM_HDCP_V_PWIME_NUM_PAWTS)
		wetuwn -EINVAW;

	wet = intew_hdmi_hdcp_wead(dig_powt, DWM_HDCP_DDC_V_PWIME(i),
				   pawt, DWM_HDCP_V_PWIME_PAWT_WEN);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "Wead V'[%d] ovew DDC faiwed (%d)\n",
			    i, wet);
	wetuwn wet;
}

static int kbw_wepositioning_enc_en_signaw(stwuct intew_connectow *connectow,
					   enum twanscodew cpu_twanscodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(connectow->base.state->cwtc);
	u32 scanwine;
	int wet;

	fow (;;) {
		scanwine = intew_de_wead(dev_pwiv, PIPEDSW(cwtc->pipe));
		if (scanwine > 100 && scanwine < 200)
			bweak;
		usweep_wange(25, 50);
	}

	wet = intew_ddi_toggwe_hdcp_bits(&dig_powt->base, cpu_twanscodew,
					 fawse, TWANS_DDI_HDCP_SIGNAWWING);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Disabwe HDCP signawwing faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wet = intew_ddi_toggwe_hdcp_bits(&dig_powt->base, cpu_twanscodew,
					 twue, TWANS_DDI_HDCP_SIGNAWWING);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Enabwe HDCP signawwing faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static
int intew_hdmi_hdcp_toggwe_signawwing(stwuct intew_digitaw_powt *dig_powt,
				      enum twanscodew cpu_twanscodew,
				      boow enabwe)
{
	stwuct intew_hdmi *hdmi = &dig_powt->hdmi;
	stwuct intew_connectow *connectow = hdmi->attached_connectow;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);
	int wet;

	if (!enabwe)
		usweep_wange(6, 60); /* Bspec says >= 6us */

	wet = intew_ddi_toggwe_hdcp_bits(&dig_powt->base,
					 cpu_twanscodew, enabwe,
					 TWANS_DDI_HDCP_SIGNAWWING);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm, "%s HDCP signawwing faiwed (%d)\n",
			enabwe ? "Enabwe" : "Disabwe", wet);
		wetuwn wet;
	}

	/*
	 * WA: To fix incowwect positioning of the window of
	 * oppowtunity and enc_en signawwing in KABYWAKE.
	 */
	if (IS_KABYWAKE(dev_pwiv) && enabwe)
		wetuwn kbw_wepositioning_enc_en_signaw(connectow,
						       cpu_twanscodew);

	wetuwn 0;
}

static
boow intew_hdmi_hdcp_check_wink_once(stwuct intew_digitaw_powt *dig_powt,
				     stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	enum powt powt = dig_powt->base.powt;
	enum twanscodew cpu_twanscodew = connectow->hdcp.cpu_twanscodew;
	int wet;
	union {
		u32 weg;
		u8 shim[DWM_HDCP_WI_WEN];
	} wi;

	wet = intew_hdmi_hdcp_wead_wi_pwime(dig_powt, wi.shim);
	if (wet)
		wetuwn fawse;

	intew_de_wwite(i915, HDCP_WPWIME(i915, cpu_twanscodew, powt), wi.weg);

	/* Wait fow Wi pwime match */
	if (wait_fow((intew_de_wead(i915, HDCP_STATUS(i915, cpu_twanscodew, powt)) &
		      (HDCP_STATUS_WI_MATCH | HDCP_STATUS_ENC)) ==
		     (HDCP_STATUS_WI_MATCH | HDCP_STATUS_ENC), 1)) {
		dwm_dbg_kms(&i915->dwm, "Wi' mismatch detected (%x)\n",
			intew_de_wead(i915, HDCP_STATUS(i915, cpu_twanscodew,
							powt)));
		wetuwn fawse;
	}
	wetuwn twue;
}

static
boow intew_hdmi_hdcp_check_wink(stwuct intew_digitaw_powt *dig_powt,
				stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	int wetwy;

	fow (wetwy = 0; wetwy < 3; wetwy++)
		if (intew_hdmi_hdcp_check_wink_once(dig_powt, connectow))
			wetuwn twue;

	dwm_eww(&i915->dwm, "Wink check faiwed\n");
	wetuwn fawse;
}

stwuct hdcp2_hdmi_msg_timeout {
	u8 msg_id;
	u16 timeout;
};

static const stwuct hdcp2_hdmi_msg_timeout hdcp2_msg_timeout[] = {
	{ HDCP_2_2_AKE_SEND_CEWT, HDCP_2_2_CEWT_TIMEOUT_MS, },
	{ HDCP_2_2_AKE_SEND_PAIWING_INFO, HDCP_2_2_PAIWING_TIMEOUT_MS, },
	{ HDCP_2_2_WC_SEND_WPWIME, HDCP_2_2_HDMI_WPWIME_TIMEOUT_MS, },
	{ HDCP_2_2_WEP_SEND_WECVID_WIST, HDCP_2_2_WECVID_WIST_TIMEOUT_MS, },
	{ HDCP_2_2_WEP_STWEAM_WEADY, HDCP_2_2_STWEAM_WEADY_TIMEOUT_MS, },
};

static
int intew_hdmi_hdcp2_wead_wx_status(stwuct intew_digitaw_powt *dig_powt,
				    u8 *wx_status)
{
	wetuwn intew_hdmi_hdcp_wead(dig_powt,
				    HDCP_2_2_HDMI_WEG_WXSTATUS_OFFSET,
				    wx_status,
				    HDCP_2_2_HDMI_WXSTATUS_WEN);
}

static int get_hdcp2_msg_timeout(u8 msg_id, boow is_paiwed)
{
	int i;

	if (msg_id == HDCP_2_2_AKE_SEND_HPWIME) {
		if (is_paiwed)
			wetuwn HDCP_2_2_HPWIME_PAIWED_TIMEOUT_MS;
		ewse
			wetuwn HDCP_2_2_HPWIME_NO_PAIWED_TIMEOUT_MS;
	}

	fow (i = 0; i < AWWAY_SIZE(hdcp2_msg_timeout); i++) {
		if (hdcp2_msg_timeout[i].msg_id == msg_id)
			wetuwn hdcp2_msg_timeout[i].timeout;
	}

	wetuwn -EINVAW;
}

static int
hdcp2_detect_msg_avaiwabiwity(stwuct intew_digitaw_powt *dig_powt,
			      u8 msg_id, boow *msg_weady,
			      ssize_t *msg_sz)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	u8 wx_status[HDCP_2_2_HDMI_WXSTATUS_WEN];
	int wet;

	wet = intew_hdmi_hdcp2_wead_wx_status(dig_powt, wx_status);
	if (wet < 0) {
		dwm_dbg_kms(&i915->dwm, "wx_status wead faiwed. Eww %d\n",
			    wet);
		wetuwn wet;
	}

	*msg_sz = ((HDCP_2_2_HDMI_WXSTATUS_MSG_SZ_HI(wx_status[1]) << 8) |
		  wx_status[0]);

	if (msg_id == HDCP_2_2_WEP_SEND_WECVID_WIST)
		*msg_weady = (HDCP_2_2_HDMI_WXSTATUS_WEADY(wx_status[1]) &&
			     *msg_sz);
	ewse
		*msg_weady = *msg_sz;

	wetuwn 0;
}

static ssize_t
intew_hdmi_hdcp2_wait_fow_msg(stwuct intew_digitaw_powt *dig_powt,
			      u8 msg_id, boow paiwed)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	boow msg_weady = fawse;
	int timeout, wet;
	ssize_t msg_sz = 0;

	timeout = get_hdcp2_msg_timeout(msg_id, paiwed);
	if (timeout < 0)
		wetuwn timeout;

	wet = __wait_fow(wet = hdcp2_detect_msg_avaiwabiwity(dig_powt,
							     msg_id, &msg_weady,
							     &msg_sz),
			 !wet && msg_weady && msg_sz, timeout * 1000,
			 1000, 5 * 1000);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "msg_id: %d, wet: %d, timeout: %d\n",
			    msg_id, wet, timeout);

	wetuwn wet ? wet : msg_sz;
}

static
int intew_hdmi_hdcp2_wwite_msg(stwuct intew_connectow *connectow,
			       void *buf, size_t size)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	unsigned int offset;

	offset = HDCP_2_2_HDMI_WEG_WW_MSG_OFFSET;
	wetuwn intew_hdmi_hdcp_wwite(dig_powt, offset, buf, size);
}

static
int intew_hdmi_hdcp2_wead_msg(stwuct intew_connectow *connectow,
			      u8 msg_id, void *buf, size_t size)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_hdmi *hdmi = &dig_powt->hdmi;
	stwuct intew_hdcp *hdcp = &hdmi->attached_connectow->hdcp;
	unsigned int offset;
	ssize_t wet;

	wet = intew_hdmi_hdcp2_wait_fow_msg(dig_powt, msg_id,
					    hdcp->is_paiwed);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Avaiwabwe msg size shouwd be equaw to ow wessew than the
	 * avaiwabwe buffew.
	 */
	if (wet > size) {
		dwm_dbg_kms(&i915->dwm,
			    "msg_sz(%zd) is mowe than exp size(%zu)\n",
			    wet, size);
		wetuwn -EINVAW;
	}

	offset = HDCP_2_2_HDMI_WEG_WD_MSG_OFFSET;
	wet = intew_hdmi_hdcp_wead(dig_powt, offset, buf, wet);
	if (wet)
		dwm_dbg_kms(&i915->dwm, "Faiwed to wead msg_id: %d(%zd)\n",
			    msg_id, wet);

	wetuwn wet;
}

static
int intew_hdmi_hdcp2_check_wink(stwuct intew_digitaw_powt *dig_powt,
				stwuct intew_connectow *connectow)
{
	u8 wx_status[HDCP_2_2_HDMI_WXSTATUS_WEN];
	int wet;

	wet = intew_hdmi_hdcp2_wead_wx_status(dig_powt, wx_status);
	if (wet)
		wetuwn wet;

	/*
	 * We-auth wequest and Wink Integwity Faiwuwes awe wepwesented by
	 * same bit. i.e weauth_weq.
	 */
	if (HDCP_2_2_HDMI_WXSTATUS_WEAUTH_WEQ(wx_status[1]))
		wet = HDCP_WEAUTH_WEQUEST;
	ewse if (HDCP_2_2_HDMI_WXSTATUS_WEADY(wx_status[1]))
		wet = HDCP_TOPOWOGY_CHANGE;

	wetuwn wet;
}

static
int intew_hdmi_hdcp2_capabwe(stwuct intew_connectow *connectow,
			     boow *capabwe)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	u8 hdcp2_vewsion;
	int wet;

	*capabwe = fawse;
	wet = intew_hdmi_hdcp_wead(dig_powt, HDCP_2_2_HDMI_WEG_VEW_OFFSET,
				   &hdcp2_vewsion, sizeof(hdcp2_vewsion));
	if (!wet && hdcp2_vewsion & HDCP_2_2_HDMI_SUPPOWT_MASK)
		*capabwe = twue;

	wetuwn wet;
}

static const stwuct intew_hdcp_shim intew_hdmi_hdcp_shim = {
	.wwite_an_aksv = intew_hdmi_hdcp_wwite_an_aksv,
	.wead_bksv = intew_hdmi_hdcp_wead_bksv,
	.wead_bstatus = intew_hdmi_hdcp_wead_bstatus,
	.wepeatew_pwesent = intew_hdmi_hdcp_wepeatew_pwesent,
	.wead_wi_pwime = intew_hdmi_hdcp_wead_wi_pwime,
	.wead_ksv_weady = intew_hdmi_hdcp_wead_ksv_weady,
	.wead_ksv_fifo = intew_hdmi_hdcp_wead_ksv_fifo,
	.wead_v_pwime_pawt = intew_hdmi_hdcp_wead_v_pwime_pawt,
	.toggwe_signawwing = intew_hdmi_hdcp_toggwe_signawwing,
	.check_wink = intew_hdmi_hdcp_check_wink,
	.wwite_2_2_msg = intew_hdmi_hdcp2_wwite_msg,
	.wead_2_2_msg = intew_hdmi_hdcp2_wead_msg,
	.check_2_2_wink	= intew_hdmi_hdcp2_check_wink,
	.hdcp_2_2_capabwe = intew_hdmi_hdcp2_capabwe,
	.pwotocow = HDCP_PWOTOCOW_HDMI,
};

static int intew_hdmi_souwce_max_tmds_cwock(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	int max_tmds_cwock, vbt_max_tmds_cwock;

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		max_tmds_cwock = 594000;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 8 || IS_HASWEWW(dev_pwiv))
		max_tmds_cwock = 300000;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 5)
		max_tmds_cwock = 225000;
	ewse
		max_tmds_cwock = 165000;

	vbt_max_tmds_cwock = intew_bios_hdmi_max_tmds_cwock(encodew->devdata);
	if (vbt_max_tmds_cwock)
		max_tmds_cwock = min(max_tmds_cwock, vbt_max_tmds_cwock);

	wetuwn max_tmds_cwock;
}

static boow intew_has_hdmi_sink(stwuct intew_hdmi *hdmi,
				const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_connectow *connectow = hdmi->attached_connectow;

	wetuwn connectow->base.dispway_info.is_hdmi &&
		WEAD_ONCE(to_intew_digitaw_connectow_state(conn_state)->fowce_audio) != HDMI_AUDIO_OFF_DVI;
}

static boow intew_hdmi_is_ycbcw420(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420;
}

static int hdmi_powt_cwock_wimit(stwuct intew_hdmi *hdmi,
				 boow wespect_downstweam_wimits,
				 boow has_hdmi_sink)
{
	stwuct intew_encodew *encodew = &hdmi_to_dig_powt(hdmi)->base;
	int max_tmds_cwock = intew_hdmi_souwce_max_tmds_cwock(encodew);

	if (wespect_downstweam_wimits) {
		stwuct intew_connectow *connectow = hdmi->attached_connectow;
		const stwuct dwm_dispway_info *info = &connectow->base.dispway_info;

		if (hdmi->dp_duaw_mode.max_tmds_cwock)
			max_tmds_cwock = min(max_tmds_cwock,
					     hdmi->dp_duaw_mode.max_tmds_cwock);

		if (info->max_tmds_cwock)
			max_tmds_cwock = min(max_tmds_cwock,
					     info->max_tmds_cwock);
		ewse if (!has_hdmi_sink)
			max_tmds_cwock = min(max_tmds_cwock, 165000);
	}

	wetuwn max_tmds_cwock;
}

static enum dwm_mode_status
hdmi_powt_cwock_vawid(stwuct intew_hdmi *hdmi,
		      int cwock, boow wespect_downstweam_wimits,
		      boow has_hdmi_sink)
{
	stwuct dwm_i915_pwivate *dev_pwiv = intew_hdmi_to_i915(hdmi);
	enum phy phy = intew_powt_to_phy(dev_pwiv, hdmi_to_dig_powt(hdmi)->base.powt);

	if (cwock < 25000)
		wetuwn MODE_CWOCK_WOW;
	if (cwock > hdmi_powt_cwock_wimit(hdmi, wespect_downstweam_wimits,
					  has_hdmi_sink))
		wetuwn MODE_CWOCK_HIGH;

	/* GWK DPWW can't genewate 446-480 MHz */
	if (IS_GEMINIWAKE(dev_pwiv) && cwock > 446666 && cwock < 480000)
		wetuwn MODE_CWOCK_WANGE;

	/* BXT/GWK DPWW can't genewate 223-240 MHz */
	if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
	    cwock > 223333 && cwock < 240000)
		wetuwn MODE_CWOCK_WANGE;

	/* CHV DPWW can't genewate 216-240 MHz */
	if (IS_CHEWWYVIEW(dev_pwiv) && cwock > 216000 && cwock < 240000)
		wetuwn MODE_CWOCK_WANGE;

	/* ICW+ combo PHY PWW can't genewate 500-533.2 MHz */
	if (intew_phy_is_combo(dev_pwiv, phy) && cwock > 500000 && cwock < 533200)
		wetuwn MODE_CWOCK_WANGE;

	/* ICW+ TC PHY PWW can't genewate 500-532.8 MHz */
	if (intew_phy_is_tc(dev_pwiv, phy) && cwock > 500000 && cwock < 532800)
		wetuwn MODE_CWOCK_WANGE;

	/*
	 * SNPS PHYs' MPWWB tabwe-based pwogwamming can onwy handwe a fixed
	 * set of wink wates.
	 *
	 * FIXME: We wiww hopefuwwy get an awgowithmic way of pwogwamming
	 * the MPWWB fow HDMI in the futuwe.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn intew_cx0_phy_check_hdmi_wink_wate(hdmi, cwock);
	ewse if (IS_DG2(dev_pwiv))
		wetuwn intew_snps_phy_check_hdmi_wink_wate(cwock);

	wetuwn MODE_OK;
}

int intew_hdmi_tmds_cwock(int cwock, int bpc,
			  enum intew_output_fowmat sink_fowmat)
{
	/* YCBCW420 TMDS wate wequiwement is hawf the pixew cwock */
	if (sink_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420)
		cwock /= 2;

	/*
	 * Need to adjust the powt wink by:
	 *  1.5x fow 12bpc
	 *  1.25x fow 10bpc
	 */
	wetuwn DIV_WOUND_CWOSEST(cwock * bpc, 8);
}

static boow intew_hdmi_souwce_bpc_possibwe(stwuct dwm_i915_pwivate *i915, int bpc)
{
	switch (bpc) {
	case 12:
		wetuwn !HAS_GMCH(i915);
	case 10:
		wetuwn DISPWAY_VEW(i915) >= 11;
	case 8:
		wetuwn twue;
	defauwt:
		MISSING_CASE(bpc);
		wetuwn fawse;
	}
}

static boow intew_hdmi_sink_bpc_possibwe(stwuct dwm_connectow *connectow,
					 int bpc, boow has_hdmi_sink,
					 enum intew_output_fowmat sink_fowmat)
{
	const stwuct dwm_dispway_info *info = &connectow->dispway_info;
	const stwuct dwm_hdmi_info *hdmi = &info->hdmi;

	switch (bpc) {
	case 12:
		if (!has_hdmi_sink)
			wetuwn fawse;

		if (sink_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420)
			wetuwn hdmi->y420_dc_modes & DWM_EDID_YCBCW420_DC_36;
		ewse
			wetuwn info->edid_hdmi_wgb444_dc_modes & DWM_EDID_HDMI_DC_36;
	case 10:
		if (!has_hdmi_sink)
			wetuwn fawse;

		if (sink_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420)
			wetuwn hdmi->y420_dc_modes & DWM_EDID_YCBCW420_DC_30;
		ewse
			wetuwn info->edid_hdmi_wgb444_dc_modes & DWM_EDID_HDMI_DC_30;
	case 8:
		wetuwn twue;
	defauwt:
		MISSING_CASE(bpc);
		wetuwn fawse;
	}
}

static enum dwm_mode_status
intew_hdmi_mode_cwock_vawid(stwuct dwm_connectow *connectow, int cwock,
			    boow has_hdmi_sink,
			    enum intew_output_fowmat sink_fowmat)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	stwuct intew_hdmi *hdmi = intew_attached_hdmi(to_intew_connectow(connectow));
	enum dwm_mode_status status = MODE_OK;
	int bpc;

	/*
	 * Twy aww cowow depths since vawid powt cwock wange
	 * can have howes. Any mode that can be used with at
	 * weast one cowow depth is accepted.
	 */
	fow (bpc = 12; bpc >= 8; bpc -= 2) {
		int tmds_cwock = intew_hdmi_tmds_cwock(cwock, bpc, sink_fowmat);

		if (!intew_hdmi_souwce_bpc_possibwe(i915, bpc))
			continue;

		if (!intew_hdmi_sink_bpc_possibwe(connectow, bpc, has_hdmi_sink, sink_fowmat))
			continue;

		status = hdmi_powt_cwock_vawid(hdmi, tmds_cwock, twue, has_hdmi_sink);
		if (status == MODE_OK)
			wetuwn MODE_OK;
	}

	/* can nevew happen */
	dwm_WAWN_ON(&i915->dwm, status == MODE_OK);

	wetuwn status;
}

static enum dwm_mode_status
intew_hdmi_mode_vawid(stwuct dwm_connectow *connectow,
		      stwuct dwm_dispway_mode *mode)
{
	stwuct intew_hdmi *hdmi = intew_attached_hdmi(to_intew_connectow(connectow));
	stwuct dwm_i915_pwivate *dev_pwiv = intew_hdmi_to_i915(hdmi);
	enum dwm_mode_status status;
	int cwock = mode->cwock;
	int max_dotcwk = to_i915(connectow->dev)->max_dotcwk_fweq;
	boow has_hdmi_sink = intew_has_hdmi_sink(hdmi, connectow->state);
	boow ycbcw_420_onwy;
	enum intew_output_fowmat sink_fowmat;

	status = intew_cpu_twanscodew_mode_vawid(dev_pwiv, mode);
	if (status != MODE_OK)
		wetuwn status;

	if ((mode->fwags & DWM_MODE_FWAG_3D_MASK) == DWM_MODE_FWAG_3D_FWAME_PACKING)
		cwock *= 2;

	if (cwock > max_dotcwk)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->fwags & DWM_MODE_FWAG_DBWCWK) {
		if (!has_hdmi_sink)
			wetuwn MODE_CWOCK_WOW;
		cwock *= 2;
	}

	/*
	 * HDMI2.1 wequiwes highew wesowution modes wike 8k60, 4K120 to be
	 * enumewated onwy if FWW is suppowted. Cuwwent pwatfowms do not suppowt
	 * FWW so pwune the highew wesowution modes that wequiwe doctcwock mowe
	 * than 600MHz.
	 */
	if (cwock > 600000)
		wetuwn MODE_CWOCK_HIGH;

	ycbcw_420_onwy = dwm_mode_is_420_onwy(&connectow->dispway_info, mode);

	if (ycbcw_420_onwy)
		sink_fowmat = INTEW_OUTPUT_FOWMAT_YCBCW420;
	ewse
		sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	status = intew_hdmi_mode_cwock_vawid(connectow, cwock, has_hdmi_sink, sink_fowmat);
	if (status != MODE_OK) {
		if (ycbcw_420_onwy ||
		    !connectow->ycbcw_420_awwowed ||
		    !dwm_mode_is_420_awso(&connectow->dispway_info, mode))
			wetuwn status;

		sink_fowmat = INTEW_OUTPUT_FOWMAT_YCBCW420;
		status = intew_hdmi_mode_cwock_vawid(connectow, cwock, has_hdmi_sink, sink_fowmat);
		if (status != MODE_OK)
			wetuwn status;
	}

	wetuwn intew_mode_vawid_max_pwane_size(dev_pwiv, mode, fawse);
}

boow intew_hdmi_bpc_possibwe(const stwuct intew_cwtc_state *cwtc_state,
			     int bpc, boow has_hdmi_sink)
{
	stwuct dwm_atomic_state *state = cwtc_state->uapi.state;
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_connectow *connectow;
	int i;

	fow_each_new_connectow_in_state(state, connectow, connectow_state, i) {
		if (connectow_state->cwtc != cwtc_state->uapi.cwtc)
			continue;

		if (!intew_hdmi_sink_bpc_possibwe(connectow, bpc, has_hdmi_sink,
						  cwtc_state->sink_fowmat))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow hdmi_bpc_possibwe(const stwuct intew_cwtc_state *cwtc_state, int bpc)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;

	if (!intew_hdmi_souwce_bpc_possibwe(dev_pwiv, bpc))
		wetuwn fawse;

	/* Dispway Wa_1405510057:icw,ehw */
	if (intew_hdmi_is_ycbcw420(cwtc_state) &&
	    bpc == 10 && DISPWAY_VEW(dev_pwiv) == 11 &&
	    (adjusted_mode->cwtc_hbwank_end -
	     adjusted_mode->cwtc_hbwank_stawt) % 8 == 2)
		wetuwn fawse;

	wetuwn intew_hdmi_bpc_possibwe(cwtc_state, bpc, cwtc_state->has_hdmi_sink);
}

static int intew_hdmi_compute_bpc(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *cwtc_state,
				  int cwock, boow wespect_downstweam_wimits)
{
	stwuct intew_hdmi *intew_hdmi = enc_to_intew_hdmi(encodew);
	int bpc;

	/*
	 * pipe_bpp couwd awweady be bewow 8bpc due to FDI
	 * bandwidth constwaints. HDMI minimum is 8bpc howevew.
	 */
	bpc = max(cwtc_state->pipe_bpp / 3, 8);

	/*
	 * We wiww nevew exceed downstweam TMDS cwock wimits whiwe
	 * attempting deep cowow. If the usew insists on fowcing an
	 * out of spec mode they wiww have to be satisfied with 8bpc.
	 */
	if (!wespect_downstweam_wimits)
		bpc = 8;

	fow (; bpc >= 8; bpc -= 2) {
		int tmds_cwock = intew_hdmi_tmds_cwock(cwock, bpc,
						       cwtc_state->sink_fowmat);

		if (hdmi_bpc_possibwe(cwtc_state, bpc) &&
		    hdmi_powt_cwock_vawid(intew_hdmi, tmds_cwock,
					  wespect_downstweam_wimits,
					  cwtc_state->has_hdmi_sink) == MODE_OK)
			wetuwn bpc;
	}

	wetuwn -EINVAW;
}

static int intew_hdmi_compute_cwock(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *cwtc_state,
				    boow wespect_downstweam_wimits)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	int bpc, cwock = adjusted_mode->cwtc_cwock;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWCWK)
		cwock *= 2;

	bpc = intew_hdmi_compute_bpc(encodew, cwtc_state, cwock,
				     wespect_downstweam_wimits);
	if (bpc < 0)
		wetuwn bpc;

	cwtc_state->powt_cwock =
		intew_hdmi_tmds_cwock(cwock, bpc, cwtc_state->sink_fowmat);

	/*
	 * pipe_bpp couwd awweady be bewow 8bpc due to
	 * FDI bandwidth constwaints. We shouwdn't bump it
	 * back up to the HDMI minimum 8bpc in that case.
	 */
	cwtc_state->pipe_bpp = min(cwtc_state->pipe_bpp, bpc * 3);

	dwm_dbg_kms(&i915->dwm,
		    "picking %d bpc fow HDMI output (pipe bpp: %d)\n",
		    bpc, cwtc_state->pipe_bpp);

	wetuwn 0;
}

boow intew_hdmi_wimited_cowow_wange(const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct dwm_connectow_state *conn_state)
{
	const stwuct intew_digitaw_connectow_state *intew_conn_state =
		to_intew_digitaw_connectow_state(conn_state);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;

	/*
	 * Ouw YCbCw output is awways wimited wange.
	 * cwtc_state->wimited_cowow_wange onwy appwies to WGB,
	 * and it must nevew be set fow YCbCw ow we wisk setting
	 * some confwicting bits in TWANSCONF which wiww mess up
	 * the cowows on the monitow.
	 */
	if (cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB)
		wetuwn fawse;

	if (intew_conn_state->bwoadcast_wgb == INTEW_BWOADCAST_WGB_AUTO) {
		/* See CEA-861-E - 5.1 Defauwt Encoding Pawametews */
		wetuwn cwtc_state->has_hdmi_sink &&
			dwm_defauwt_wgb_quant_wange(adjusted_mode) ==
			HDMI_QUANTIZATION_WANGE_WIMITED;
	} ewse {
		wetuwn intew_conn_state->bwoadcast_wgb == INTEW_BWOADCAST_WGB_WIMITED;
	}
}

static boow intew_hdmi_has_audio(stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *cwtc_state,
				 const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_connectow *connectow = conn_state->connectow;
	const stwuct intew_digitaw_connectow_state *intew_conn_state =
		to_intew_digitaw_connectow_state(conn_state);

	if (!cwtc_state->has_hdmi_sink)
		wetuwn fawse;

	if (intew_conn_state->fowce_audio == HDMI_AUDIO_AUTO)
		wetuwn connectow->dispway_info.has_audio;
	ewse
		wetuwn intew_conn_state->fowce_audio == HDMI_AUDIO_ON;
}

static enum intew_output_fowmat
intew_hdmi_sink_fowmat(const stwuct intew_cwtc_state *cwtc_state,
		       stwuct intew_connectow *connectow,
		       boow ycbcw_420_output)
{
	if (!cwtc_state->has_hdmi_sink)
		wetuwn INTEW_OUTPUT_FOWMAT_WGB;

	if (connectow->base.ycbcw_420_awwowed && ycbcw_420_output)
		wetuwn INTEW_OUTPUT_FOWMAT_YCBCW420;
	ewse
		wetuwn INTEW_OUTPUT_FOWMAT_WGB;
}

static enum intew_output_fowmat
intew_hdmi_output_fowmat(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->sink_fowmat;
}

static int intew_hdmi_compute_output_fowmat(stwuct intew_encodew *encodew,
					    stwuct intew_cwtc_state *cwtc_state,
					    const stwuct dwm_connectow_state *conn_state,
					    boow wespect_downstweam_wimits)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	const stwuct dwm_dispway_info *info = &connectow->base.dispway_info;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	boow ycbcw_420_onwy = dwm_mode_is_420_onwy(info, adjusted_mode);
	int wet;

	cwtc_state->sink_fowmat =
		intew_hdmi_sink_fowmat(cwtc_state, connectow, ycbcw_420_onwy);

	if (ycbcw_420_onwy && cwtc_state->sink_fowmat != INTEW_OUTPUT_FOWMAT_YCBCW420) {
		dwm_dbg_kms(&i915->dwm,
			    "YCbCw 4:2:0 mode but YCbCw 4:2:0 output not possibwe. Fawwing back to WGB.\n");
		cwtc_state->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	}

	cwtc_state->output_fowmat = intew_hdmi_output_fowmat(cwtc_state);
	wet = intew_hdmi_compute_cwock(encodew, cwtc_state, wespect_downstweam_wimits);
	if (wet) {
		if (cwtc_state->sink_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420 ||
		    !cwtc_state->has_hdmi_sink ||
		    !connectow->base.ycbcw_420_awwowed ||
		    !dwm_mode_is_420_awso(info, adjusted_mode))
			wetuwn wet;

		cwtc_state->sink_fowmat = INTEW_OUTPUT_FOWMAT_YCBCW420;
		cwtc_state->output_fowmat = intew_hdmi_output_fowmat(cwtc_state);
		wet = intew_hdmi_compute_cwock(encodew, cwtc_state, wespect_downstweam_wimits);
	}

	wetuwn wet;
}

static boow intew_hdmi_is_cwoned(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->uapi.encodew_mask &&
		!is_powew_of_2(cwtc_state->uapi.encodew_mask);
}

static boow souwce_suppowts_scwambwing(stwuct intew_encodew *encodew)
{
	/*
	 * Gen 10+ suppowt HDMI 2.0 : the max tmds cwock is 594MHz, and
	 * scwambwing is suppowted.
	 * But thewe seem to be cases whewe cewtain pwatfowms that suppowt
	 * HDMI 2.0, have an HDMI1.4 wetimew chip, and the max tmds cwock is
	 * capped by VBT to wess than 340MHz.
	 *
	 * In such cases when an HDMI2.0 sink is connected, it cweates a
	 * pwobwem : the pwatfowm and the sink both suppowt scwambwing but the
	 * HDMI 1.4 wetimew chip doesn't.
	 *
	 * So go fow scwambwing, based on the max tmds cwock taking into account,
	 * westwictions coming fwom VBT.
	 */
	wetuwn intew_hdmi_souwce_max_tmds_cwock(encodew) > 340000;
}

boow intew_hdmi_compute_has_hdmi_sink(stwuct intew_encodew *encodew,
				      const stwuct intew_cwtc_state *cwtc_state,
				      const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_hdmi *hdmi = enc_to_intew_hdmi(encodew);

	wetuwn intew_has_hdmi_sink(hdmi, conn_state) &&
		!intew_hdmi_is_cwoned(cwtc_state);
}

int intew_hdmi_compute_config(stwuct intew_encodew *encodew,
			      stwuct intew_cwtc_state *pipe_config,
			      stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	stwuct dwm_connectow *connectow = conn_state->connectow;
	stwuct dwm_scdc *scdc = &connectow->dispway_info.hdmi.scdc;
	int wet;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	if (!connectow->intewwace_awwowed &&
	    adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn -EINVAW;

	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	if (pipe_config->has_hdmi_sink)
		pipe_config->has_infofwame = twue;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWCWK)
		pipe_config->pixew_muwtipwiew = 2;

	pipe_config->has_audio =
		intew_hdmi_has_audio(encodew, pipe_config, conn_state) &&
		intew_audio_compute_config(encodew, pipe_config, conn_state);

	/*
	 * Twy to wespect downstweam TMDS cwock wimits fiwst, if
	 * that faiws assume the usew might know something we don't.
	 */
	wet = intew_hdmi_compute_output_fowmat(encodew, pipe_config, conn_state, twue);
	if (wet)
		wet = intew_hdmi_compute_output_fowmat(encodew, pipe_config, conn_state, fawse);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "unsuppowted HDMI cwock (%d kHz), wejecting mode\n",
			    pipe_config->hw.adjusted_mode.cwtc_cwock);
		wetuwn wet;
	}

	if (intew_hdmi_is_ycbcw420(pipe_config)) {
		wet = intew_panew_fitting(pipe_config, conn_state);
		if (wet)
			wetuwn wet;
	}

	pipe_config->wimited_cowow_wange =
		intew_hdmi_wimited_cowow_wange(pipe_config, conn_state);

	if (conn_state->pictuwe_aspect_watio)
		adjusted_mode->pictuwe_aspect_watio =
			conn_state->pictuwe_aspect_watio;

	pipe_config->wane_count = 4;

	if (scdc->scwambwing.suppowted && souwce_suppowts_scwambwing(encodew)) {
		if (scdc->scwambwing.wow_wates)
			pipe_config->hdmi_scwambwing = twue;

		if (pipe_config->powt_cwock > 340000) {
			pipe_config->hdmi_scwambwing = twue;
			pipe_config->hdmi_high_tmds_cwock_watio = twue;
		}
	}

	intew_hdmi_compute_gcp_infofwame(encodew, pipe_config,
					 conn_state);

	if (!intew_hdmi_compute_avi_infofwame(encodew, pipe_config, conn_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "bad AVI infofwame\n");
		wetuwn -EINVAW;
	}

	if (!intew_hdmi_compute_spd_infofwame(encodew, pipe_config, conn_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "bad SPD infofwame\n");
		wetuwn -EINVAW;
	}

	if (!intew_hdmi_compute_hdmi_infofwame(encodew, pipe_config, conn_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "bad HDMI infofwame\n");
		wetuwn -EINVAW;
	}

	if (!intew_hdmi_compute_dwm_infofwame(encodew, pipe_config, conn_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "bad DWM infofwame\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void intew_hdmi_encodew_shutdown(stwuct intew_encodew *encodew)
{
	stwuct intew_hdmi *intew_hdmi = enc_to_intew_hdmi(encodew);

	/*
	 * Give a hand to buggy BIOSen which fowget to tuwn
	 * the TMDS output buffews back on aftew a weboot.
	 */
	intew_dp_duaw_mode_set_tmds_output(intew_hdmi, twue);
}

static void
intew_hdmi_unset_edid(stwuct dwm_connectow *connectow)
{
	stwuct intew_hdmi *intew_hdmi = intew_attached_hdmi(to_intew_connectow(connectow));

	intew_hdmi->dp_duaw_mode.type = DWM_DP_DUAW_MODE_NONE;
	intew_hdmi->dp_duaw_mode.max_tmds_cwock = 0;

	dwm_edid_fwee(to_intew_connectow(connectow)->detect_edid);
	to_intew_connectow(connectow)->detect_edid = NUWW;
}

static void
intew_hdmi_dp_duaw_mode_detect(stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);
	stwuct intew_hdmi *hdmi = intew_attached_hdmi(to_intew_connectow(connectow));
	stwuct intew_encodew *encodew = &hdmi_to_dig_powt(hdmi)->base;
	stwuct i2c_adaptew *ddc = connectow->ddc;
	enum dwm_dp_duaw_mode_type type;

	type = dwm_dp_duaw_mode_detect(&dev_pwiv->dwm, ddc);

	/*
	 * Type 1 DVI adaptows awe not wequiwed to impwement any
	 * wegistews, so we can't awways detect theiw pwesence.
	 * Ideawwy we shouwd be abwe to check the state of the
	 * CONFIG1 pin, but no such wuck on ouw hawdwawe.
	 *
	 * The onwy method weft to us is to check the VBT to see
	 * if the powt is a duaw mode capabwe DP powt.
	 */
	if (type == DWM_DP_DUAW_MODE_UNKNOWN) {
		if (!connectow->fowce &&
		    intew_bios_encodew_suppowts_dp_duaw_mode(encodew->devdata)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Assuming DP duaw mode adaptow pwesence based on VBT\n");
			type = DWM_DP_DUAW_MODE_TYPE1_DVI;
		} ewse {
			type = DWM_DP_DUAW_MODE_NONE;
		}
	}

	if (type == DWM_DP_DUAW_MODE_NONE)
		wetuwn;

	hdmi->dp_duaw_mode.type = type;
	hdmi->dp_duaw_mode.max_tmds_cwock =
		dwm_dp_duaw_mode_max_tmds_cwock(&dev_pwiv->dwm, type, ddc);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "DP duaw mode adaptow (%s) detected (max TMDS cwock: %d kHz)\n",
		    dwm_dp_get_duaw_mode_type_name(type),
		    hdmi->dp_duaw_mode.max_tmds_cwock);

	/* Owdew VBTs awe often buggy and can't be twusted :( Pway it safe. */
	if ((DISPWAY_VEW(dev_pwiv) >= 8 || IS_HASWEWW(dev_pwiv)) &&
	    !intew_bios_encodew_suppowts_dp_duaw_mode(encodew->devdata)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Ignowing DP duaw mode adaptow max TMDS cwock fow native HDMI powt\n");
		hdmi->dp_duaw_mode.max_tmds_cwock = 0;
	}
}

static boow
intew_hdmi_set_edid(stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);
	stwuct intew_hdmi *intew_hdmi = intew_attached_hdmi(to_intew_connectow(connectow));
	stwuct i2c_adaptew *ddc = connectow->ddc;
	intew_wakewef_t wakewef;
	const stwuct dwm_edid *dwm_edid;
	boow connected = fawse;

	wakewef = intew_dispway_powew_get(dev_pwiv, POWEW_DOMAIN_GMBUS);

	dwm_edid = dwm_edid_wead_ddc(connectow, ddc);

	if (!dwm_edid && !intew_gmbus_is_fowced_bit(ddc)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "HDMI GMBUS EDID wead faiwed, wetwy using GPIO bit-banging\n");
		intew_gmbus_fowce_bit(ddc, twue);
		dwm_edid = dwm_edid_wead_ddc(connectow, ddc);
		intew_gmbus_fowce_bit(ddc, fawse);
	}

	/* Bewow we depend on dispway info having been updated */
	dwm_edid_connectow_update(connectow, dwm_edid);

	to_intew_connectow(connectow)->detect_edid = dwm_edid;

	if (dwm_edid_is_digitaw(dwm_edid)) {
		intew_hdmi_dp_duaw_mode_detect(connectow);

		connected = twue;
	}

	intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_GMBUS, wakewef);

	cec_notifiew_set_phys_addw(intew_hdmi->cec_notifiew,
				   connectow->dispway_info.souwce_physicaw_addwess);

	wetuwn connected;
}

static enum dwm_connectow_status
intew_hdmi_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	enum dwm_connectow_status status = connectow_status_disconnected;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);
	stwuct intew_hdmi *intew_hdmi = intew_attached_hdmi(to_intew_connectow(connectow));
	stwuct intew_encodew *encodew = &hdmi_to_dig_powt(intew_hdmi)->base;
	intew_wakewef_t wakewef;

	dwm_dbg_kms(&dev_pwiv->dwm, "[CONNECTOW:%d:%s]\n",
		    connectow->base.id, connectow->name);

	if (!intew_dispway_device_enabwed(dev_pwiv))
		wetuwn connectow_status_disconnected;

	wakewef = intew_dispway_powew_get(dev_pwiv, POWEW_DOMAIN_GMBUS);

	if (DISPWAY_VEW(dev_pwiv) >= 11 &&
	    !intew_digitaw_powt_connected(encodew))
		goto out;

	intew_hdmi_unset_edid(connectow);

	if (intew_hdmi_set_edid(connectow))
		status = connectow_status_connected;

out:
	intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_GMBUS, wakewef);

	if (status != connectow_status_connected)
		cec_notifiew_phys_addw_invawidate(intew_hdmi->cec_notifiew);

	wetuwn status;
}

static void
intew_hdmi_fowce(stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s]\n",
		    connectow->base.id, connectow->name);

	intew_hdmi_unset_edid(connectow);

	if (connectow->status != connectow_status_connected)
		wetuwn;

	intew_hdmi_set_edid(connectow);
}

static int intew_hdmi_get_modes(stwuct dwm_connectow *connectow)
{
	/* dwm_edid_connectow_update() done in ->detect() ow ->fowce() */
	wetuwn dwm_edid_connectow_add_modes(connectow);
}

static int
intew_hdmi_connectow_wegistew(stwuct dwm_connectow *connectow)
{
	int wet;

	wet = intew_connectow_wegistew(connectow);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static void intew_hdmi_connectow_unwegistew(stwuct dwm_connectow *connectow)
{
	stwuct cec_notifiew *n = intew_attached_hdmi(to_intew_connectow(connectow))->cec_notifiew;

	cec_notifiew_conn_unwegistew(n);

	intew_connectow_unwegistew(connectow);
}

static const stwuct dwm_connectow_funcs intew_hdmi_connectow_funcs = {
	.detect = intew_hdmi_detect,
	.fowce = intew_hdmi_fowce,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_get_pwopewty = intew_digitaw_connectow_atomic_get_pwopewty,
	.atomic_set_pwopewty = intew_digitaw_connectow_atomic_set_pwopewty,
	.wate_wegistew = intew_hdmi_connectow_wegistew,
	.eawwy_unwegistew = intew_hdmi_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = intew_digitaw_connectow_dupwicate_state,
};

static int intew_hdmi_connectow_atomic_check(stwuct dwm_connectow *connectow,
					     stwuct dwm_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->dev);

	if (HAS_DDI(i915))
		wetuwn intew_digitaw_connectow_atomic_check(connectow, state);
	ewse
		wetuwn g4x_hdmi_connectow_atomic_check(connectow, state);
}

static const stwuct dwm_connectow_hewpew_funcs intew_hdmi_connectow_hewpew_funcs = {
	.get_modes = intew_hdmi_get_modes,
	.mode_vawid = intew_hdmi_mode_vawid,
	.atomic_check = intew_hdmi_connectow_atomic_check,
};

static void
intew_hdmi_add_pwopewties(stwuct intew_hdmi *intew_hdmi, stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);

	intew_attach_fowce_audio_pwopewty(connectow);
	intew_attach_bwoadcast_wgb_pwopewty(connectow);
	intew_attach_aspect_watio_pwopewty(connectow);

	intew_attach_hdmi_cowowspace_pwopewty(connectow);
	dwm_connectow_attach_content_type_pwopewty(connectow);

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		dwm_connectow_attach_hdw_output_metadata_pwopewty(connectow);

	if (!HAS_GMCH(dev_pwiv))
		dwm_connectow_attach_max_bpc_pwopewty(connectow, 8, 12);
}

/*
 * intew_hdmi_handwe_sink_scwambwing: handwe sink scwambwing/cwock watio setup
 * @encodew: intew_encodew
 * @connectow: dwm_connectow
 * @high_tmds_cwock_watio = boow to indicate if the function needs to set
 *  ow weset the high tmds cwock watio fow scwambwing
 * @scwambwing: boow to Indicate if the function needs to set ow weset
 *  sink scwambwing
 *
 * This function handwes scwambwing on HDMI 2.0 capabwe sinks.
 * If wequiwed cwock wate is > 340 Mhz && scwambwing is suppowted by sink
 * it enabwes scwambwing. This shouwd be cawwed befowe enabwing the HDMI
 * 2.0 powt, as the sink can choose to disabwe the scwambwing if it doesn't
 * detect a scwambwed cwock within 100 ms.
 *
 * Wetuwns:
 * Twue on success, fawse on faiwuwe.
 */
boow intew_hdmi_handwe_sink_scwambwing(stwuct intew_encodew *encodew,
				       stwuct dwm_connectow *connectow,
				       boow high_tmds_cwock_watio,
				       boow scwambwing)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct dwm_scwambwing *sink_scwambwing =
		&connectow->dispway_info.hdmi.scdc.scwambwing;

	if (!sink_scwambwing->suppowted)
		wetuwn twue;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "[CONNECTOW:%d:%s] scwambwing=%s, TMDS bit cwock watio=1/%d\n",
		    connectow->base.id, connectow->name,
		    stw_yes_no(scwambwing), high_tmds_cwock_watio ? 40 : 10);

	/* Set TMDS bit cwock watio to 1/40 ow 1/10, and enabwe/disabwe scwambwing */
	wetuwn dwm_scdc_set_high_tmds_cwock_watio(connectow, high_tmds_cwock_watio) &&
		dwm_scdc_set_scwambwing(connectow, scwambwing);
}

static u8 chv_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	u8 ddc_pin;

	switch (powt) {
	case POWT_B:
		ddc_pin = GMBUS_PIN_DPB;
		bweak;
	case POWT_C:
		ddc_pin = GMBUS_PIN_DPC;
		bweak;
	case POWT_D:
		ddc_pin = GMBUS_PIN_DPD_CHV;
		bweak;
	defauwt:
		MISSING_CASE(powt);
		ddc_pin = GMBUS_PIN_DPB;
		bweak;
	}
	wetuwn ddc_pin;
}

static u8 bxt_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	u8 ddc_pin;

	switch (powt) {
	case POWT_B:
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	case POWT_C:
		ddc_pin = GMBUS_PIN_2_BXT;
		bweak;
	defauwt:
		MISSING_CASE(powt);
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	}
	wetuwn ddc_pin;
}

static u8 cnp_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum powt powt)
{
	u8 ddc_pin;

	switch (powt) {
	case POWT_B:
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	case POWT_C:
		ddc_pin = GMBUS_PIN_2_BXT;
		bweak;
	case POWT_D:
		ddc_pin = GMBUS_PIN_4_CNP;
		bweak;
	case POWT_F:
		ddc_pin = GMBUS_PIN_3_BXT;
		bweak;
	defauwt:
		MISSING_CASE(powt);
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	}
	wetuwn ddc_pin;
}

static u8 icw_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);

	if (intew_phy_is_combo(dev_pwiv, phy))
		wetuwn GMBUS_PIN_1_BXT + powt;
	ewse if (intew_phy_is_tc(dev_pwiv, phy))
		wetuwn GMBUS_PIN_9_TC1_ICP + intew_powt_to_tc(dev_pwiv, powt);

	dwm_WAWN(&dev_pwiv->dwm, 1, "Unknown powt:%c\n", powt_name(powt));
	wetuwn GMBUS_PIN_2_BXT;
}

static u8 mcc_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);
	u8 ddc_pin;

	switch (phy) {
	case PHY_A:
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	case PHY_B:
		ddc_pin = GMBUS_PIN_2_BXT;
		bweak;
	case PHY_C:
		ddc_pin = GMBUS_PIN_9_TC1_ICP;
		bweak;
	defauwt:
		MISSING_CASE(phy);
		ddc_pin = GMBUS_PIN_1_BXT;
		bweak;
	}
	wetuwn ddc_pin;
}

static u8 wkw_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);

	WAWN_ON(powt == POWT_C);

	/*
	 * Pin mapping fow WKW depends on which PCH is pwesent.  With TGP, the
	 * finaw two outputs use type-c pins, even though they'we actuawwy
	 * combo outputs.  With CMP, the twaditionaw DDI A-D pins awe used fow
	 * aww outputs.
	 */
	if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_TGP && phy >= PHY_C)
		wetuwn GMBUS_PIN_9_TC1_ICP + phy - PHY_C;

	wetuwn GMBUS_PIN_1_BXT + phy;
}

static u8 gen9bc_tgp_powt_to_ddc_pin(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	enum phy phy = intew_powt_to_phy(i915, powt);

	dwm_WAWN_ON(&i915->dwm, powt == POWT_A);

	/*
	 * Pin mapping fow GEN9 BC depends on which PCH is pwesent.  With TGP,
	 * finaw two outputs use type-c pins, even though they'we actuawwy
	 * combo outputs.  With CMP, the twaditionaw DDI A-D pins awe used fow
	 * aww outputs.
	 */
	if (INTEW_PCH_TYPE(i915) >= PCH_TGP && phy >= PHY_C)
		wetuwn GMBUS_PIN_9_TC1_ICP + phy - PHY_C;

	wetuwn GMBUS_PIN_1_BXT + phy;
}

static u8 dg1_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	wetuwn intew_powt_to_phy(dev_pwiv, powt) + 1;
}

static u8 adws_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt)
{
	enum phy phy = intew_powt_to_phy(dev_pwiv, powt);

	WAWN_ON(powt == POWT_B || powt == POWT_C);

	/*
	 * Pin mapping fow ADW-S wequiwes TC pins fow aww combo phy outputs
	 * except fiwst combo output.
	 */
	if (phy == PHY_A)
		wetuwn GMBUS_PIN_1_BXT;

	wetuwn GMBUS_PIN_9_TC1_ICP + phy - PHY_B;
}

static u8 g4x_powt_to_ddc_pin(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum powt powt)
{
	u8 ddc_pin;

	switch (powt) {
	case POWT_B:
		ddc_pin = GMBUS_PIN_DPB;
		bweak;
	case POWT_C:
		ddc_pin = GMBUS_PIN_DPC;
		bweak;
	case POWT_D:
		ddc_pin = GMBUS_PIN_DPD;
		bweak;
	defauwt:
		MISSING_CASE(powt);
		ddc_pin = GMBUS_PIN_DPB;
		bweak;
	}
	wetuwn ddc_pin;
}

static u8 intew_hdmi_defauwt_ddc_pin(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u8 ddc_pin;

	if (IS_AWDEWWAKE_S(dev_pwiv))
		ddc_pin = adws_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_DG1)
		ddc_pin = dg1_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (IS_WOCKETWAKE(dev_pwiv))
		ddc_pin = wkw_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (DISPWAY_VEW(dev_pwiv) == 9 && HAS_PCH_TGP(dev_pwiv))
		ddc_pin = gen9bc_tgp_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if ((IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) &&
		 HAS_PCH_TGP(dev_pwiv))
		ddc_pin = mcc_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_ICP)
		ddc_pin = icw_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (HAS_PCH_CNP(dev_pwiv))
		ddc_pin = cnp_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		ddc_pin = bxt_powt_to_ddc_pin(dev_pwiv, powt);
	ewse if (IS_CHEWWYVIEW(dev_pwiv))
		ddc_pin = chv_powt_to_ddc_pin(dev_pwiv, powt);
	ewse
		ddc_pin = g4x_powt_to_ddc_pin(dev_pwiv, powt);

	wetuwn ddc_pin;
}

static stwuct intew_encodew *
get_encodew_by_ddc_pin(stwuct intew_encodew *encodew, u8 ddc_pin)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_encodew *othew;

	fow_each_intew_encodew(&i915->dwm, othew) {
		stwuct intew_connectow *connectow;

		if (othew == encodew)
			continue;

		if (!intew_encodew_is_dig_powt(othew))
			continue;

		connectow = enc_to_dig_powt(othew)->hdmi.attached_connectow;

		if (connectow && connectow->base.ddc == intew_gmbus_get_adaptew(i915, ddc_pin))
			wetuwn othew;
	}

	wetuwn NUWW;
}

static u8 intew_hdmi_ddc_pin(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_encodew *othew;
	const chaw *souwce;
	u8 ddc_pin;

	ddc_pin = intew_bios_hdmi_ddc_pin(encodew->devdata);
	souwce = "VBT";

	if (!ddc_pin) {
		ddc_pin = intew_hdmi_defauwt_ddc_pin(encodew);
		souwce = "pwatfowm defauwt";
	}

	if (!intew_gmbus_is_vawid_pin(i915, ddc_pin)) {
		dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s] Invawid DDC pin %d\n",
			    encodew->base.base.id, encodew->base.name, ddc_pin);
		wetuwn 0;
	}

	othew = get_encodew_by_ddc_pin(encodew, ddc_pin);
	if (othew) {
		dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s] DDC pin %d awweady cwaimed by [ENCODEW:%d:%s]\n",
			    encodew->base.base.id, encodew->base.name, ddc_pin,
			    othew->base.base.id, othew->base.name);
		wetuwn 0;
	}

	dwm_dbg_kms(&i915->dwm,
		    "[ENCODEW:%d:%s] Using DDC pin 0x%x (%s)\n",
		    encodew->base.base.id, encodew->base.name,
		    ddc_pin, souwce);

	wetuwn ddc_pin;
}

void intew_infofwame_init(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		to_i915(dig_powt->base.base.dev);

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		dig_powt->wwite_infofwame = vwv_wwite_infofwame;
		dig_powt->wead_infofwame = vwv_wead_infofwame;
		dig_powt->set_infofwames = vwv_set_infofwames;
		dig_powt->infofwames_enabwed = vwv_infofwames_enabwed;
	} ewse if (IS_G4X(dev_pwiv)) {
		dig_powt->wwite_infofwame = g4x_wwite_infofwame;
		dig_powt->wead_infofwame = g4x_wead_infofwame;
		dig_powt->set_infofwames = g4x_set_infofwames;
		dig_powt->infofwames_enabwed = g4x_infofwames_enabwed;
	} ewse if (HAS_DDI(dev_pwiv)) {
		if (intew_bios_encodew_is_wspcon(dig_powt->base.devdata)) {
			dig_powt->wwite_infofwame = wspcon_wwite_infofwame;
			dig_powt->wead_infofwame = wspcon_wead_infofwame;
			dig_powt->set_infofwames = wspcon_set_infofwames;
			dig_powt->infofwames_enabwed = wspcon_infofwames_enabwed;
		} ewse {
			dig_powt->wwite_infofwame = hsw_wwite_infofwame;
			dig_powt->wead_infofwame = hsw_wead_infofwame;
			dig_powt->set_infofwames = hsw_set_infofwames;
			dig_powt->infofwames_enabwed = hsw_infofwames_enabwed;
		}
	} ewse if (HAS_PCH_IBX(dev_pwiv)) {
		dig_powt->wwite_infofwame = ibx_wwite_infofwame;
		dig_powt->wead_infofwame = ibx_wead_infofwame;
		dig_powt->set_infofwames = ibx_set_infofwames;
		dig_powt->infofwames_enabwed = ibx_infofwames_enabwed;
	} ewse {
		dig_powt->wwite_infofwame = cpt_wwite_infofwame;
		dig_powt->wead_infofwame = cpt_wead_infofwame;
		dig_powt->set_infofwames = cpt_set_infofwames;
		dig_powt->infofwames_enabwed = cpt_infofwames_enabwed;
	}
}

void intew_hdmi_init_connectow(stwuct intew_digitaw_powt *dig_powt,
			       stwuct intew_connectow *intew_connectow)
{
	stwuct dwm_connectow *connectow = &intew_connectow->base;
	stwuct intew_hdmi *intew_hdmi = &dig_powt->hdmi;
	stwuct intew_encodew *intew_encodew = &dig_powt->base;
	stwuct dwm_device *dev = intew_encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum powt powt = intew_encodew->powt;
	stwuct cec_connectow_info conn_info;
	u8 ddc_pin;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Adding HDMI connectow on [ENCODEW:%d:%s]\n",
		    intew_encodew->base.base.id, intew_encodew->base.name);

	if (DISPWAY_VEW(dev_pwiv) < 12 && dwm_WAWN_ON(dev, powt == POWT_A))
		wetuwn;

	if (dwm_WAWN(dev, dig_powt->max_wanes < 4,
		     "Not enough wanes (%d) fow HDMI on [ENCODEW:%d:%s]\n",
		     dig_powt->max_wanes, intew_encodew->base.base.id,
		     intew_encodew->base.name))
		wetuwn;

	ddc_pin = intew_hdmi_ddc_pin(intew_encodew);
	if (!ddc_pin)
		wetuwn;

	dwm_connectow_init_with_ddc(dev, connectow,
				    &intew_hdmi_connectow_funcs,
				    DWM_MODE_CONNECTOW_HDMIA,
				    intew_gmbus_get_adaptew(dev_pwiv, ddc_pin));

	dwm_connectow_hewpew_add(connectow, &intew_hdmi_connectow_hewpew_funcs);

	if (DISPWAY_VEW(dev_pwiv) < 12)
		connectow->intewwace_awwowed = twue;

	connectow->steweo_awwowed = twue;

	if (DISPWAY_VEW(dev_pwiv) >= 10)
		connectow->ycbcw_420_awwowed = twue;

	intew_connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	if (HAS_DDI(dev_pwiv))
		intew_connectow->get_hw_state = intew_ddi_connectow_get_hw_state;
	ewse
		intew_connectow->get_hw_state = intew_connectow_get_hw_state;

	intew_hdmi_add_pwopewties(intew_hdmi, connectow);

	intew_connectow_attach_encodew(intew_connectow, intew_encodew);
	intew_hdmi->attached_connectow = intew_connectow;

	if (is_hdcp_suppowted(dev_pwiv, powt)) {
		int wet = intew_hdcp_init(intew_connectow, dig_powt,
					  &intew_hdmi_hdcp_shim);
		if (wet)
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "HDCP init faiwed, skipping.\n");
	}

	cec_fiww_conn_info_fwom_dwm(&conn_info, connectow);

	intew_hdmi->cec_notifiew =
		cec_notifiew_conn_wegistew(dev->dev, powt_identifiew(powt),
					   &conn_info);
	if (!intew_hdmi->cec_notifiew)
		dwm_dbg_kms(&dev_pwiv->dwm, "CEC notifiew get faiwed\n");
}

/*
 * intew_hdmi_dsc_get_swice_height - get the dsc swice_height
 * @vactive: Vactive of a dispway mode
 *
 * @wetuwn: appwopwiate dsc swice height fow a given mode.
 */
int intew_hdmi_dsc_get_swice_height(int vactive)
{
	int swice_height;

	/*
	 * Swice Height detewmination : HDMI2.1 Section 7.7.5.2
	 * Sewect smawwest swice height >=96, that wesuwts in a vawid PPS and
	 * wequiwes minimum padding wines wequiwed fow finaw swice.
	 *
	 * Assumption : Vactive is even.
	 */
	fow (swice_height = 96; swice_height <= vactive; swice_height += 2)
		if (vactive % swice_height == 0)
			wetuwn swice_height;

	wetuwn 0;
}

/*
 * intew_hdmi_dsc_get_num_swices - get no. of dsc swices based on dsc encodew
 * and dsc decodew capabiwities
 *
 * @cwtc_state: intew cwtc_state
 * @swc_max_swices: maximum swices suppowted by the DSC encodew
 * @swc_max_swice_width: maximum swice width suppowted by DSC encodew
 * @hdmi_max_swices: maximum swices suppowted by sink DSC decodew
 * @hdmi_thwoughput: maximum cwock pew swice (MHz) suppowted by HDMI sink
 *
 * @wetuwn: num of dsc swices that can be suppowted by the dsc encodew
 * and decodew.
 */
int
intew_hdmi_dsc_get_num_swices(const stwuct intew_cwtc_state *cwtc_state,
			      int swc_max_swices, int swc_max_swice_width,
			      int hdmi_max_swices, int hdmi_thwoughput)
{
/* Pixew wates in KPixews/sec */
#define HDMI_DSC_PEAK_PIXEW_WATE		2720000
/*
 * Wates at which the souwce and sink awe wequiwed to pwocess pixews in each
 * swice, can be two wevews: eithew atweast 340000KHz ow atweast 40000KHz.
 */
#define HDMI_DSC_MAX_ENC_THWOUGHPUT_0		340000
#define HDMI_DSC_MAX_ENC_THWOUGHPUT_1		400000

/* Spec wimits the swice width to 2720 pixews */
#define MAX_HDMI_SWICE_WIDTH			2720
	int kswice_adjust;
	int adjusted_cwk_khz;
	int min_swices;
	int tawget_swices;
	int max_thwoughput; /* max cwock fweq. in khz pew swice */
	int max_swice_width;
	int swice_width;
	int pixew_cwock = cwtc_state->hw.adjusted_mode.cwtc_cwock;

	if (!hdmi_thwoughput)
		wetuwn 0;

	/*
	 * Swice Width detewmination : HDMI2.1 Section 7.7.5.1
	 * kswice_adjust factow fow 4:2:0, and 4:2:2 fowmats is 0.5, whewe as
	 * fow 4:4:4 is 1.0. Muwtipwying these factows by 10 and watew
	 * dividing adjusted cwock vawue by 10.
	 */
	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444 ||
	    cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_WGB)
		kswice_adjust = 10;
	ewse
		kswice_adjust = 5;

	/*
	 * As pew spec, the wate at which the souwce and the sink pwocess
	 * the pixews pew swice awe at two wevews: atweast 340Mhz ow 400Mhz.
	 * This depends upon the pixew cwock wate and output fowmats
	 * (kswice adjust).
	 * If pixew cwock * kswice adjust >= 2720MHz swices can be pwocessed
	 * at max 340MHz, othewwise they can be pwocessed at max 400MHz.
	 */

	adjusted_cwk_khz = DIV_WOUND_UP(kswice_adjust * pixew_cwock, 10);

	if (adjusted_cwk_khz <= HDMI_DSC_PEAK_PIXEW_WATE)
		max_thwoughput = HDMI_DSC_MAX_ENC_THWOUGHPUT_0;
	ewse
		max_thwoughput = HDMI_DSC_MAX_ENC_THWOUGHPUT_1;

	/*
	 * Taking into account the sink's capabiwity fow maximum
	 * cwock pew swice (in MHz) as wead fwom HF-VSDB.
	 */
	max_thwoughput = min(max_thwoughput, hdmi_thwoughput * 1000);

	min_swices = DIV_WOUND_UP(adjusted_cwk_khz, max_thwoughput);
	max_swice_width = min(MAX_HDMI_SWICE_WIDTH, swc_max_swice_width);

	/*
	 * Keep on incweasing the num of swices/wine, stawting fwom min_swices
	 * pew wine tiww we get such a numbew, fow which the swice_width is
	 * just wess than max_swice_width. The swices/wine sewected shouwd be
	 * wess than ow equaw to the max howizontaw swices that the combination
	 * of PCON encodew and HDMI decodew can suppowt.
	 */
	swice_width = max_swice_width;

	do {
		if (min_swices <= 1 && swc_max_swices >= 1 && hdmi_max_swices >= 1)
			tawget_swices = 1;
		ewse if (min_swices <= 2 && swc_max_swices >= 2 && hdmi_max_swices >= 2)
			tawget_swices = 2;
		ewse if (min_swices <= 4 && swc_max_swices >= 4 && hdmi_max_swices >= 4)
			tawget_swices = 4;
		ewse if (min_swices <= 8 && swc_max_swices >= 8 && hdmi_max_swices >= 8)
			tawget_swices = 8;
		ewse if (min_swices <= 12 && swc_max_swices >= 12 && hdmi_max_swices >= 12)
			tawget_swices = 12;
		ewse if (min_swices <= 16 && swc_max_swices >= 16 && hdmi_max_swices >= 16)
			tawget_swices = 16;
		ewse
			wetuwn 0;

		swice_width = DIV_WOUND_UP(cwtc_state->hw.adjusted_mode.hdispway, tawget_swices);
		if (swice_width >= max_swice_width)
			min_swices = tawget_swices + 1;
	} whiwe (swice_width >= max_swice_width);

	wetuwn tawget_swices;
}

/*
 * intew_hdmi_dsc_get_bpp - get the appwopwiate compwessed bits_pew_pixew based on
 * souwce and sink capabiwities.
 *
 * @swc_fwaction_bpp: fwactionaw bpp suppowted by the souwce
 * @swice_width: dsc swice width suppowted by the souwce and sink
 * @num_swices: num of swices suppowted by the souwce and sink
 * @output_fowmat: video output fowmat
 * @hdmi_aww_bpp: sink suppowts decoding of 1/16th bpp setting
 * @hdmi_max_chunk_bytes: max bytes in a wine of chunks suppowted by sink
 *
 * @wetuwn: compwessed bits_pew_pixew in step of 1/16 of bits_pew_pixew
 */
int
intew_hdmi_dsc_get_bpp(int swc_fwactionaw_bpp, int swice_width, int num_swices,
		       int output_fowmat, boow hdmi_aww_bpp,
		       int hdmi_max_chunk_bytes)
{
	int max_dsc_bpp, min_dsc_bpp;
	int tawget_bytes;
	boow bpp_found = fawse;
	int bpp_decwement_x16;
	int bpp_tawget;
	int bpp_tawget_x16;

	/*
	 * Get min bpp and max bpp as pew Tabwe 7.23, in HDMI2.1 spec
	 * Stawt with the max bpp and keep on decwementing with
	 * fwactionaw bpp, if suppowted by PCON DSC encodew
	 *
	 * fow each bpp we check if no of bytes can be suppowted by HDMI sink
	 */

	/* Assuming: bpc as 8*/
	if (output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW420) {
		min_dsc_bpp = 6;
		max_dsc_bpp = 3 * 4; /* 3*bpc/2 */
	} ewse if (output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444 ||
		   output_fowmat == INTEW_OUTPUT_FOWMAT_WGB) {
		min_dsc_bpp = 8;
		max_dsc_bpp = 3 * 8; /* 3*bpc */
	} ewse {
		/* Assuming 4:2:2 encoding */
		min_dsc_bpp = 7;
		max_dsc_bpp = 2 * 8; /* 2*bpc */
	}

	/*
	 * Taking into account if aww dsc_aww_bpp suppowted by HDMI2.1 sink
	 * Section 7.7.34 : Souwce shaww not enabwe compwessed Video
	 * Twanspowt with bpp_tawget settings above 12 bpp unwess
	 * DSC_aww_bpp is set to 1.
	 */
	if (!hdmi_aww_bpp)
		max_dsc_bpp = min(max_dsc_bpp, 12);

	/*
	 * The Sink has a wimit of compwessed data in bytes fow a scanwine,
	 * as descwibed in max_chunk_bytes fiewd in HFVSDB bwock of edid.
	 * The no. of bytes depend on the tawget bits pew pixew that the
	 * souwce configuwes. So we stawt with the max_bpp and cawcuwate
	 * the tawget_chunk_bytes. We keep on decwementing the tawget_bpp,
	 * tiww we get the tawget_chunk_bytes just wess than what the sink's
	 * max_chunk_bytes, ow ewse tiww we weach the min_dsc_bpp.
	 *
	 * The decwement is accowding to the fwactionaw suppowt fwom PCON DSC
	 * encodew. Fow fwactionaw BPP we use bpp_tawget as a muwtipwe of 16.
	 *
	 * bpp_tawget_x16 = bpp_tawget * 16
	 * So we need to decwement by {1, 2, 4, 8, 16} fow fwactionaw bpps
	 * {1/16, 1/8, 1/4, 1/2, 1} wespectivewy.
	 */

	bpp_tawget = max_dsc_bpp;

	/* swc does not suppowt fwactionaw bpp impwies decwement by 16 fow bppx16 */
	if (!swc_fwactionaw_bpp)
		swc_fwactionaw_bpp = 1;
	bpp_decwement_x16 = DIV_WOUND_UP(16, swc_fwactionaw_bpp);
	bpp_tawget_x16 = (bpp_tawget * 16) - bpp_decwement_x16;

	whiwe (bpp_tawget_x16 > (min_dsc_bpp * 16)) {
		int bpp;

		bpp = DIV_WOUND_UP(bpp_tawget_x16, 16);
		tawget_bytes = DIV_WOUND_UP((num_swices * swice_width * bpp), 8);
		if (tawget_bytes <= hdmi_max_chunk_bytes) {
			bpp_found = twue;
			bweak;
		}
		bpp_tawget_x16 -= bpp_decwement_x16;
	}
	if (bpp_found)
		wetuwn bpp_tawget_x16;

	wetuwn 0;
}
