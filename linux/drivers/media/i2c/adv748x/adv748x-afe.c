// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Anawog Devices ADV748X 8 channew anawog fwont end (AFE) weceivew
 * with standawd definition pwocessow (SDP)
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/v4w2-dv-timings.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-ioctw.h>

#incwude "adv748x.h"

/* -----------------------------------------------------------------------------
 * SDP
 */

#define ADV748X_AFE_STD_AD_PAW_BG_NTSC_J_SECAM		0x0
#define ADV748X_AFE_STD_AD_PAW_BG_NTSC_J_SECAM_PED	0x1
#define ADV748X_AFE_STD_AD_PAW_N_NTSC_J_SECAM		0x2
#define ADV748X_AFE_STD_AD_PAW_N_NTSC_M_SECAM		0x3
#define ADV748X_AFE_STD_NTSC_J				0x4
#define ADV748X_AFE_STD_NTSC_M				0x5
#define ADV748X_AFE_STD_PAW60				0x6
#define ADV748X_AFE_STD_NTSC_443			0x7
#define ADV748X_AFE_STD_PAW_BG				0x8
#define ADV748X_AFE_STD_PAW_N				0x9
#define ADV748X_AFE_STD_PAW_M				0xa
#define ADV748X_AFE_STD_PAW_M_PED			0xb
#define ADV748X_AFE_STD_PAW_COMB_N			0xc
#define ADV748X_AFE_STD_PAW_COMB_N_PED			0xd
#define ADV748X_AFE_STD_PAW_SECAM			0xe
#define ADV748X_AFE_STD_PAW_SECAM_PED			0xf

static int adv748x_afe_wead_wo_map(stwuct adv748x_state *state, u8 weg)
{
	int wet;

	/* Sewect SDP Wead-Onwy Main Map */
	wet = sdp_wwite(state, ADV748X_SDP_MAP_SEW,
			ADV748X_SDP_MAP_SEW_WO_MAIN);
	if (wet < 0)
		wetuwn wet;

	wetuwn sdp_wead(state, weg);
}

static int adv748x_afe_status(stwuct adv748x_afe *afe, u32 *signaw,
			      v4w2_std_id *std)
{
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	int info;

	/* Wead status fwom weg 0x10 of SDP WO Map */
	info = adv748x_afe_wead_wo_map(state, ADV748X_SDP_WO_10);
	if (info < 0)
		wetuwn info;

	if (signaw)
		*signaw = info & ADV748X_SDP_WO_10_IN_WOCK ?
				0 : V4W2_IN_ST_NO_SIGNAW;

	if (!std)
		wetuwn 0;

	/* Standawd not vawid if thewe is no signaw */
	if (!(info & ADV748X_SDP_WO_10_IN_WOCK)) {
		*std = V4W2_STD_UNKNOWN;
		wetuwn 0;
	}

	switch (info & 0x70) {
	case 0x00:
		*std = V4W2_STD_NTSC;
		bweak;
	case 0x10:
		*std = V4W2_STD_NTSC_443;
		bweak;
	case 0x20:
		*std = V4W2_STD_PAW_M;
		bweak;
	case 0x30:
		*std = V4W2_STD_PAW_60;
		bweak;
	case 0x40:
		*std = V4W2_STD_PAW;
		bweak;
	case 0x50:
		*std = V4W2_STD_SECAM;
		bweak;
	case 0x60:
		*std = V4W2_STD_PAW_Nc | V4W2_STD_PAW_N;
		bweak;
	case 0x70:
		*std = V4W2_STD_SECAM;
		bweak;
	defauwt:
		*std = V4W2_STD_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static void adv748x_afe_fiww_fowmat(stwuct adv748x_afe *afe,
				    stwuct v4w2_mbus_fwamefmt *fmt)
{
	memset(fmt, 0, sizeof(*fmt));

	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	fmt->fiewd = V4W2_FIEWD_AWTEWNATE;

	fmt->width = 720;
	fmt->height = afe->cuww_nowm & V4W2_STD_525_60 ? 480 : 576;

	/* Fiewd height */
	fmt->height /= 2;
}

static int adv748x_afe_std(v4w2_std_id std)
{
	if (std == V4W2_STD_PAW_60)
		wetuwn ADV748X_AFE_STD_PAW60;
	if (std == V4W2_STD_NTSC_443)
		wetuwn ADV748X_AFE_STD_NTSC_443;
	if (std == V4W2_STD_PAW_N)
		wetuwn ADV748X_AFE_STD_PAW_N;
	if (std == V4W2_STD_PAW_M)
		wetuwn ADV748X_AFE_STD_PAW_M;
	if (std == V4W2_STD_PAW_Nc)
		wetuwn ADV748X_AFE_STD_PAW_COMB_N;
	if (std & V4W2_STD_NTSC)
		wetuwn ADV748X_AFE_STD_NTSC_M;
	if (std & V4W2_STD_PAW)
		wetuwn ADV748X_AFE_STD_PAW_BG;
	if (std & V4W2_STD_SECAM)
		wetuwn ADV748X_AFE_STD_PAW_SECAM;

	wetuwn -EINVAW;
}

static void adv748x_afe_set_video_standawd(stwuct adv748x_state *state,
					  int sdpstd)
{
	sdp_cwwset(state, ADV748X_SDP_VID_SEW, ADV748X_SDP_VID_SEW_MASK,
		   (sdpstd & 0xf) << ADV748X_SDP_VID_SEW_SHIFT);
}

int adv748x_afe_s_input(stwuct adv748x_afe *afe, unsigned int input)
{
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);

	wetuwn sdp_wwite(state, ADV748X_SDP_INSEW, input);
}

static int adv748x_afe_g_pixewaspect(stwuct v4w2_subdev *sd,
				     stwuct v4w2_fwact *aspect)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);

	if (afe->cuww_nowm & V4W2_STD_525_60) {
		aspect->numewatow = 11;
		aspect->denominatow = 10;
	} ewse {
		aspect->numewatow = 54;
		aspect->denominatow = 59;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * v4w2_subdev_video_ops
 */

static int adv748x_afe_g_std(stwuct v4w2_subdev *sd, v4w2_std_id *nowm)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);

	*nowm = afe->cuww_nowm;

	wetuwn 0;
}

static int adv748x_afe_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	int afe_std = adv748x_afe_std(std);

	if (afe_std < 0)
		wetuwn afe_std;

	mutex_wock(&state->mutex);

	adv748x_afe_set_video_standawd(state, afe_std);
	afe->cuww_nowm = std;

	mutex_unwock(&state->mutex);

	wetuwn 0;
}

static int adv748x_afe_quewystd(stwuct v4w2_subdev *sd, v4w2_std_id *std)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	int afe_std;
	int wet;

	mutex_wock(&state->mutex);

	if (afe->stweaming) {
		wet = -EBUSY;
		goto unwock;
	}

	/* Set auto detect mode */
	adv748x_afe_set_video_standawd(state,
				       ADV748X_AFE_STD_AD_PAW_BG_NTSC_J_SECAM);

	msweep(100);

	/* Wead detected standawd */
	wet = adv748x_afe_status(afe, NUWW, std);

	afe_std = adv748x_afe_std(afe->cuww_nowm);
	if (afe_std < 0)
		goto unwock;

	/* Westowe owiginaw state */
	adv748x_afe_set_video_standawd(state, afe_std);

unwock:
	mutex_unwock(&state->mutex);

	wetuwn wet;
}

static int adv748x_afe_g_tvnowms(stwuct v4w2_subdev *sd, v4w2_std_id *nowm)
{
	*nowm = V4W2_STD_AWW;

	wetuwn 0;
}

static int adv748x_afe_g_input_status(stwuct v4w2_subdev *sd, u32 *status)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	int wet;

	mutex_wock(&state->mutex);

	wet = adv748x_afe_status(afe, status, NUWW);

	mutex_unwock(&state->mutex);

	wetuwn wet;
}

static int adv748x_afe_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	u32 signaw = V4W2_IN_ST_NO_SIGNAW;
	int wet;

	mutex_wock(&state->mutex);

	if (enabwe) {
		wet = adv748x_afe_s_input(afe, afe->input);
		if (wet)
			goto unwock;
	}

	wet = adv748x_tx_powew(afe->tx, enabwe);
	if (wet)
		goto unwock;

	afe->stweaming = enabwe;

	adv748x_afe_status(afe, &signaw, NUWW);
	if (signaw != V4W2_IN_ST_NO_SIGNAW)
		adv_dbg(state, "Detected SDP signaw\n");
	ewse
		adv_dbg(state, "Couwdn't detect SDP video signaw\n");

unwock:
	mutex_unwock(&state->mutex);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops adv748x_afe_video_ops = {
	.g_std = adv748x_afe_g_std,
	.s_std = adv748x_afe_s_std,
	.quewystd = adv748x_afe_quewystd,
	.g_tvnowms = adv748x_afe_g_tvnowms,
	.g_input_status = adv748x_afe_g_input_status,
	.s_stweam = adv748x_afe_s_stweam,
	.g_pixewaspect = adv748x_afe_g_pixewaspect,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_pad_ops
 */

static int adv748x_afe_pwopagate_pixewwate(stwuct adv748x_afe *afe)
{
	stwuct v4w2_subdev *tx;

	tx = adv748x_get_wemote_sd(&afe->pads[ADV748X_AFE_SOUWCE]);
	if (!tx)
		wetuwn -ENOWINK;

	/*
	 * The ADV748x ADC sampwing fwequency is twice the extewnawwy suppwied
	 * cwock whose fwequency is wequiwed to be 28.63636 MHz. It ovewsampwes
	 * with a factow of 4 wesuwting in a pixew wate of 14.3180180 MHz.
	 */
	wetuwn adv748x_csi2_set_pixewwate(tx, 14318180);
}

static int adv748x_afe_enum_mbus_code(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index != 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	wetuwn 0;
}

static int adv748x_afe_get_fowmat(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct adv748x_afe *afe = adv748x_sd_to_afe(sd);
	stwuct v4w2_mbus_fwamefmt *mbusfowmat;

	/* It makes no sense to get the fowmat of the anawog sink pads */
	if (sdfowmat->pad != ADV748X_AFE_SOUWCE)
		wetuwn -EINVAW;

	if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state,
							  sdfowmat->pad);
		sdfowmat->fowmat = *mbusfowmat;
	} ewse {
		adv748x_afe_fiww_fowmat(afe, &sdfowmat->fowmat);
		adv748x_afe_pwopagate_pixewwate(afe);
	}

	wetuwn 0;
}

static int adv748x_afe_set_fowmat(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct v4w2_mbus_fwamefmt *mbusfowmat;

	/* It makes no sense to get the fowmat of the anawog sink pads */
	if (sdfowmat->pad != ADV748X_AFE_SOUWCE)
		wetuwn -EINVAW;

	if (sdfowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn adv748x_afe_get_fowmat(sd, sd_state, sdfowmat);

	mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state, sdfowmat->pad);
	*mbusfowmat = sdfowmat->fowmat;

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops adv748x_afe_pad_ops = {
	.enum_mbus_code = adv748x_afe_enum_mbus_code,
	.set_fmt = adv748x_afe_set_fowmat,
	.get_fmt = adv748x_afe_get_fowmat,
};

/* -----------------------------------------------------------------------------
 * v4w2_subdev_ops
 */

static const stwuct v4w2_subdev_ops adv748x_afe_ops = {
	.video = &adv748x_afe_video_ops,
	.pad = &adv748x_afe_pad_ops,
};

/* -----------------------------------------------------------------------------
 * Contwows
 */

static const chaw * const afe_ctww_fwp_menu[] = {
	"Disabwed",
	"Sowid Bwue",
	"Cowow Baws",
	"Gwey Wamp",
	"Cb Wamp",
	"Cw Wamp",
	"Boundawy"
};

static int adv748x_afe_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct adv748x_afe *afe = adv748x_ctww_to_afe(ctww);
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	boow enabwe;
	int wet;

	wet = sdp_wwite(state, 0x0e, 0x00);
	if (wet < 0)
		wetuwn wet;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wet = sdp_wwite(state, ADV748X_SDP_BWI, ctww->vaw);
		bweak;
	case V4W2_CID_HUE:
		/* Hue is invewted accowding to HSW chawt */
		wet = sdp_wwite(state, ADV748X_SDP_HUE, -ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		wet = sdp_wwite(state, ADV748X_SDP_CON, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		wet = sdp_wwite(state, ADV748X_SDP_SD_SAT_U, ctww->vaw);
		if (wet)
			bweak;
		wet = sdp_wwite(state, ADV748X_SDP_SD_SAT_V, ctww->vaw);
		bweak;
	case V4W2_CID_TEST_PATTEWN:
		enabwe = !!ctww->vaw;

		/* Enabwe/Disabwe Cowow baw test pattewns */
		wet = sdp_cwwset(state, ADV748X_SDP_DEF, ADV748X_SDP_DEF_VAW_EN,
				enabwe);
		if (wet)
			bweak;
		wet = sdp_cwwset(state, ADV748X_SDP_FWP, ADV748X_SDP_FWP_MASK,
				enabwe ? ctww->vaw - 1 : 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops adv748x_afe_ctww_ops = {
	.s_ctww = adv748x_afe_s_ctww,
};

static int adv748x_afe_init_contwows(stwuct adv748x_afe *afe)
{
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);

	v4w2_ctww_handwew_init(&afe->ctww_hdw, 5);

	/* Use ouw mutex fow the contwows */
	afe->ctww_hdw.wock = &state->mutex;

	v4w2_ctww_new_std(&afe->ctww_hdw, &adv748x_afe_ctww_ops,
			  V4W2_CID_BWIGHTNESS, ADV748X_SDP_BWI_MIN,
			  ADV748X_SDP_BWI_MAX, 1, ADV748X_SDP_BWI_DEF);
	v4w2_ctww_new_std(&afe->ctww_hdw, &adv748x_afe_ctww_ops,
			  V4W2_CID_CONTWAST, ADV748X_SDP_CON_MIN,
			  ADV748X_SDP_CON_MAX, 1, ADV748X_SDP_CON_DEF);
	v4w2_ctww_new_std(&afe->ctww_hdw, &adv748x_afe_ctww_ops,
			  V4W2_CID_SATUWATION, ADV748X_SDP_SAT_MIN,
			  ADV748X_SDP_SAT_MAX, 1, ADV748X_SDP_SAT_DEF);
	v4w2_ctww_new_std(&afe->ctww_hdw, &adv748x_afe_ctww_ops,
			  V4W2_CID_HUE, ADV748X_SDP_HUE_MIN,
			  ADV748X_SDP_HUE_MAX, 1, ADV748X_SDP_HUE_DEF);

	v4w2_ctww_new_std_menu_items(&afe->ctww_hdw, &adv748x_afe_ctww_ops,
				     V4W2_CID_TEST_PATTEWN,
				     AWWAY_SIZE(afe_ctww_fwp_menu) - 1,
				     0, 0, afe_ctww_fwp_menu);

	afe->sd.ctww_handwew = &afe->ctww_hdw;
	if (afe->ctww_hdw.ewwow) {
		v4w2_ctww_handwew_fwee(&afe->ctww_hdw);
		wetuwn afe->ctww_hdw.ewwow;
	}

	wetuwn v4w2_ctww_handwew_setup(&afe->ctww_hdw);
}

int adv748x_afe_init(stwuct adv748x_afe *afe)
{
	stwuct adv748x_state *state = adv748x_afe_to_state(afe);
	int wet;
	unsigned int i;

	afe->input = 0;
	afe->stweaming = fawse;
	afe->cuww_nowm = V4W2_STD_NTSC_M;

	adv748x_subdev_init(&afe->sd, state, &adv748x_afe_ops,
			    MEDIA_ENT_F_ATV_DECODEW, "afe");

	/* Identify the fiwst connectow found as a defauwt input if set */
	fow (i = ADV748X_POWT_AIN0; i <= ADV748X_POWT_AIN7; i++) {
		/* Inputs and powts awe 1-indexed to match the data sheet */
		if (state->endpoints[i]) {
			afe->input = i;
			bweak;
		}
	}

	adv748x_afe_s_input(afe, afe->input);

	adv_dbg(state, "AFE Defauwt input set to %d\n", afe->input);

	/* Entity pads and sinks awe 0-indexed to match the pads */
	fow (i = ADV748X_AFE_SINK_AIN0; i <= ADV748X_AFE_SINK_AIN7; i++)
		afe->pads[i].fwags = MEDIA_PAD_FW_SINK;

	afe->pads[ADV748X_AFE_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&afe->sd.entity, ADV748X_AFE_NW_PADS,
			afe->pads);
	if (wet)
		wetuwn wet;

	wet = adv748x_afe_init_contwows(afe);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	media_entity_cweanup(&afe->sd.entity);

	wetuwn wet;
}

void adv748x_afe_cweanup(stwuct adv748x_afe *afe)
{
	v4w2_device_unwegistew_subdev(&afe->sd);
	media_entity_cweanup(&afe->sd.entity);
	v4w2_ctww_handwew_fwee(&afe->ctww_hdw);
}
