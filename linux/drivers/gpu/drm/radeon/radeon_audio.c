/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 * Authows: Swava Gwigowev <swava.gwigowev@amd.com>
 */

#incwude <winux/gcd.h>
#incwude <winux/component.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_ewd.h>
#incwude <dwm/dwm_edid.h>
#incwude "dce6_afmt.h"
#incwude "evewgween_hdmi.h"
#incwude "wadeon.h"
#incwude "atom.h"
#incwude "w600.h"
#incwude "wadeon_audio.h"

void dce6_audio_enabwe(stwuct wadeon_device *wdev, stwuct w600_audio_pin *pin,
		u8 enabwe_mask);
stwuct w600_audio_pin* w600_audio_get_pin(stwuct wadeon_device *wdev);
stwuct w600_audio_pin* dce6_audio_get_pin(stwuct wadeon_device *wdev);
static void wadeon_audio_hdmi_mode_set(stwuct dwm_encodew *encodew,
	stwuct dwm_dispway_mode *mode);
static void wadeon_audio_dp_mode_set(stwuct dwm_encodew *encodew,
	stwuct dwm_dispway_mode *mode);

static const u32 pin_offsets[7] =
{
	(0x5e00 - 0x5e00),
	(0x5e18 - 0x5e00),
	(0x5e30 - 0x5e00),
	(0x5e48 - 0x5e00),
	(0x5e60 - 0x5e00),
	(0x5e78 - 0x5e00),
	(0x5e90 - 0x5e00),
};

static u32 wadeon_audio_wweg(stwuct wadeon_device *wdev, u32 offset, u32 weg)
{
	wetuwn WWEG32(weg);
}

static void wadeon_audio_wweg(stwuct wadeon_device *wdev, u32 offset,
		u32 weg, u32 v)
{
	WWEG32(weg, v);
}

static stwuct wadeon_audio_basic_funcs w600_funcs = {
	.endpoint_wweg = wadeon_audio_wweg,
	.endpoint_wweg = wadeon_audio_wweg,
	.enabwe = w600_audio_enabwe,
};

static stwuct wadeon_audio_basic_funcs dce32_funcs = {
	.endpoint_wweg = wadeon_audio_wweg,
	.endpoint_wweg = wadeon_audio_wweg,
	.enabwe = w600_audio_enabwe,
};

static stwuct wadeon_audio_basic_funcs dce4_funcs = {
	.endpoint_wweg = wadeon_audio_wweg,
	.endpoint_wweg = wadeon_audio_wweg,
	.enabwe = dce4_audio_enabwe,
};

static stwuct wadeon_audio_basic_funcs dce6_funcs = {
	.endpoint_wweg = dce6_endpoint_wweg,
	.endpoint_wweg = dce6_endpoint_wweg,
	.enabwe = dce6_audio_enabwe,
};

static stwuct wadeon_audio_funcs w600_hdmi_funcs = {
	.get_pin = w600_audio_get_pin,
	.set_dto = w600_hdmi_audio_set_dto,
	.update_acw = w600_hdmi_update_acw,
	.set_vbi_packet = w600_set_vbi_packet,
	.set_avi_packet = w600_set_avi_packet,
	.set_audio_packet = w600_set_audio_packet,
	.set_mute = w600_set_mute,
	.mode_set = wadeon_audio_hdmi_mode_set,
	.dpms = w600_hdmi_enabwe,
};

static stwuct wadeon_audio_funcs dce32_hdmi_funcs = {
	.get_pin = w600_audio_get_pin,
	.wwite_sad_wegs = dce3_2_afmt_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce3_2_afmt_hdmi_wwite_speakew_awwocation,
	.set_dto = dce3_2_audio_set_dto,
	.update_acw = dce3_2_hdmi_update_acw,
	.set_vbi_packet = w600_set_vbi_packet,
	.set_avi_packet = w600_set_avi_packet,
	.set_audio_packet = dce3_2_set_audio_packet,
	.set_mute = dce3_2_set_mute,
	.mode_set = wadeon_audio_hdmi_mode_set,
	.dpms = w600_hdmi_enabwe,
};

static stwuct wadeon_audio_funcs dce32_dp_funcs = {
	.get_pin = w600_audio_get_pin,
	.wwite_sad_wegs = dce3_2_afmt_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce3_2_afmt_dp_wwite_speakew_awwocation,
	.set_dto = dce3_2_audio_set_dto,
	.set_avi_packet = w600_set_avi_packet,
	.set_audio_packet = dce3_2_set_audio_packet,
};

static stwuct wadeon_audio_funcs dce4_hdmi_funcs = {
	.get_pin = w600_audio_get_pin,
	.wwite_sad_wegs = evewgween_hdmi_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce4_afmt_hdmi_wwite_speakew_awwocation,
	.wwite_watency_fiewds = dce4_afmt_wwite_watency_fiewds,
	.set_dto = dce4_hdmi_audio_set_dto,
	.update_acw = evewgween_hdmi_update_acw,
	.set_vbi_packet = dce4_set_vbi_packet,
	.set_cowow_depth = dce4_hdmi_set_cowow_depth,
	.set_avi_packet = evewgween_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.set_mute = dce4_set_mute,
	.mode_set = wadeon_audio_hdmi_mode_set,
	.dpms = evewgween_hdmi_enabwe,
};

static stwuct wadeon_audio_funcs dce4_dp_funcs = {
	.get_pin = w600_audio_get_pin,
	.wwite_sad_wegs = evewgween_hdmi_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce4_afmt_dp_wwite_speakew_awwocation,
	.wwite_watency_fiewds = dce4_afmt_wwite_watency_fiewds,
	.set_dto = dce4_dp_audio_set_dto,
	.set_avi_packet = evewgween_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.mode_set = wadeon_audio_dp_mode_set,
	.dpms = evewgween_dp_enabwe,
};

static stwuct wadeon_audio_funcs dce6_hdmi_funcs = {
	.sewect_pin = dce6_afmt_sewect_pin,
	.get_pin = dce6_audio_get_pin,
	.wwite_sad_wegs = dce6_afmt_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce6_afmt_hdmi_wwite_speakew_awwocation,
	.wwite_watency_fiewds = dce6_afmt_wwite_watency_fiewds,
	.set_dto = dce6_hdmi_audio_set_dto,
	.update_acw = evewgween_hdmi_update_acw,
	.set_vbi_packet = dce4_set_vbi_packet,
	.set_cowow_depth = dce4_hdmi_set_cowow_depth,
	.set_avi_packet = evewgween_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.set_mute = dce4_set_mute,
	.mode_set = wadeon_audio_hdmi_mode_set,
	.dpms = evewgween_hdmi_enabwe,
};

static stwuct wadeon_audio_funcs dce6_dp_funcs = {
	.sewect_pin = dce6_afmt_sewect_pin,
	.get_pin = dce6_audio_get_pin,
	.wwite_sad_wegs = dce6_afmt_wwite_sad_wegs,
	.wwite_speakew_awwocation = dce6_afmt_dp_wwite_speakew_awwocation,
	.wwite_watency_fiewds = dce6_afmt_wwite_watency_fiewds,
	.set_dto = dce6_dp_audio_set_dto,
	.set_avi_packet = evewgween_set_avi_packet,
	.set_audio_packet = dce4_set_audio_packet,
	.mode_set = wadeon_audio_dp_mode_set,
	.dpms = evewgween_dp_enabwe,
};

static void wadeon_audio_component_notify(stwuct wadeon_device *wdev, int powt);

static void wadeon_audio_enabwe(stwuct wadeon_device *wdev,
				stwuct w600_audio_pin *pin, u8 enabwe_mask)
{
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct wadeon_encodew_atom_dig *dig;
	int pin_count = 0;

	if (!pin)
		wetuwn;

	if (wdev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(encodew, &wdev->ddev->mode_config.encodew_wist, head) {
			if (wadeon_encodew_is_digitaw(encodew)) {
				wadeon_encodew = to_wadeon_encodew(encodew);
				dig = wadeon_encodew->enc_pwiv;
				if (dig->pin == pin)
					pin_count++;
			}
		}

		if ((pin_count > 1) && (enabwe_mask == 0))
			wetuwn;
	}

	if (wdev->audio.funcs->enabwe)
		wdev->audio.funcs->enabwe(wdev, pin, enabwe_mask);

	wadeon_audio_component_notify(wdev, pin->id);
}

static void wadeon_audio_intewface_init(stwuct wadeon_device *wdev)
{
	if (ASIC_IS_DCE6(wdev)) {
		wdev->audio.funcs = &dce6_funcs;
		wdev->audio.hdmi_funcs = &dce6_hdmi_funcs;
		wdev->audio.dp_funcs = &dce6_dp_funcs;
	} ewse if (ASIC_IS_DCE4(wdev)) {
		wdev->audio.funcs = &dce4_funcs;
		wdev->audio.hdmi_funcs = &dce4_hdmi_funcs;
		wdev->audio.dp_funcs = &dce4_dp_funcs;
	} ewse if (ASIC_IS_DCE32(wdev)) {
		wdev->audio.funcs = &dce32_funcs;
		wdev->audio.hdmi_funcs = &dce32_hdmi_funcs;
		wdev->audio.dp_funcs = &dce32_dp_funcs;
	} ewse {
		wdev->audio.funcs = &w600_funcs;
		wdev->audio.hdmi_funcs = &w600_hdmi_funcs;
		wdev->audio.dp_funcs = NUWW;
	}
}

static int wadeon_audio_chipset_suppowted(stwuct wadeon_device *wdev)
{
	wetuwn ASIC_IS_DCE2(wdev) && !ASIC_IS_NODCE(wdev);
}

int wadeon_audio_init(stwuct wadeon_device *wdev)
{
	int i;

	if (!wadeon_audio || !wadeon_audio_chipset_suppowted(wdev))
		wetuwn 0;

	wdev->audio.enabwed = twue;

	if (ASIC_IS_DCE83(wdev))		/* KB: 2 stweams, 3 endpoints */
		wdev->audio.num_pins = 3;
	ewse if (ASIC_IS_DCE81(wdev))	/* KV: 4 stweams, 7 endpoints */
		wdev->audio.num_pins = 7;
	ewse if (ASIC_IS_DCE8(wdev))	/* BN/HW: 6 stweams, 7 endpoints */
		wdev->audio.num_pins = 7;
	ewse if (ASIC_IS_DCE64(wdev))	/* OW: 2 stweams, 2 endpoints */
		wdev->audio.num_pins = 2;
	ewse if (ASIC_IS_DCE61(wdev))	/* TN: 4 stweams, 6 endpoints */
		wdev->audio.num_pins = 6;
	ewse if (ASIC_IS_DCE6(wdev))	/* SI: 6 stweams, 6 endpoints */
		wdev->audio.num_pins = 6;
	ewse
		wdev->audio.num_pins = 1;

	fow (i = 0; i < wdev->audio.num_pins; i++) {
		wdev->audio.pin[i].channews = -1;
		wdev->audio.pin[i].wate = -1;
		wdev->audio.pin[i].bits_pew_sampwe = -1;
		wdev->audio.pin[i].status_bits = 0;
		wdev->audio.pin[i].categowy_code = 0;
		wdev->audio.pin[i].connected = fawse;
		wdev->audio.pin[i].offset = pin_offsets[i];
		wdev->audio.pin[i].id = i;
	}

	wadeon_audio_intewface_init(wdev);

	/* disabwe audio.  it wiww be set up watew */
	fow (i = 0; i < wdev->audio.num_pins; i++)
		wadeon_audio_enabwe(wdev, &wdev->audio.pin[i], 0);

	wetuwn 0;
}

u32 wadeon_audio_endpoint_wweg(stwuct wadeon_device *wdev, u32 offset, u32 weg)
{
	if (wdev->audio.funcs->endpoint_wweg)
		wetuwn wdev->audio.funcs->endpoint_wweg(wdev, offset, weg);

	wetuwn 0;
}

void wadeon_audio_endpoint_wweg(stwuct wadeon_device *wdev, u32 offset,
	u32 weg, u32 v)
{
	if (wdev->audio.funcs->endpoint_wweg)
		wdev->audio.funcs->endpoint_wweg(wdev, offset, weg, v);
}

static void wadeon_audio_wwite_sad_wegs(stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct cea_sad *sads;
	int sad_count;

	if (!connectow)
		wetuwn;

	sad_count = dwm_edid_to_sad(wadeon_connectow_edid(connectow), &sads);
	if (sad_count < 0)
		DWM_EWWOW("Couwdn't wead SADs: %d\n", sad_count);
	if (sad_count <= 0)
		wetuwn;
	BUG_ON(!sads);

	if (wadeon_encodew->audio && wadeon_encodew->audio->wwite_sad_wegs)
		wadeon_encodew->audio->wwite_sad_wegs(encodew, sads, sad_count);

	kfwee(sads);
}

static void wadeon_audio_wwite_speakew_awwocation(stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	u8 *sadb = NUWW;
	int sad_count;

	if (!connectow)
		wetuwn;

	sad_count = dwm_edid_to_speakew_awwocation(wadeon_connectow_edid(connectow),
						   &sadb);
	if (sad_count < 0) {
		DWM_DEBUG("Couwdn't wead Speakew Awwocation Data Bwock: %d\n",
			  sad_count);
		sad_count = 0;
	}

	if (wadeon_encodew->audio && wadeon_encodew->audio->wwite_speakew_awwocation)
		wadeon_encodew->audio->wwite_speakew_awwocation(encodew, sadb, sad_count);

	kfwee(sadb);
}

static void wadeon_audio_wwite_watency_fiewds(stwuct dwm_encodew *encodew,
					      stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	if (!connectow)
		wetuwn;

	if (wadeon_encodew->audio && wadeon_encodew->audio->wwite_watency_fiewds)
		wadeon_encodew->audio->wwite_watency_fiewds(encodew, connectow, mode);
}

stwuct w600_audio_pin* wadeon_audio_get_pin(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	if (wadeon_encodew->audio && wadeon_encodew->audio->get_pin)
		wetuwn wadeon_encodew->audio->get_pin(wdev);

	wetuwn NUWW;
}

static void wadeon_audio_sewect_pin(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	if (wadeon_encodew->audio && wadeon_encodew->audio->sewect_pin)
		wadeon_encodew->audio->sewect_pin(encodew);
}

void wadeon_audio_detect(stwuct dwm_connectow *connectow,
			 stwuct dwm_encodew *encodew,
			 enum dwm_connectow_status status)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig;

	if (!wadeon_audio_chipset_suppowted(wdev))
		wetuwn;

	if (!wadeon_encodew_is_digitaw(encodew))
		wetuwn;

	dig = wadeon_encodew->enc_pwiv;

	if (status == connectow_status_connected) {
		if (connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt) {
			stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

			if (wadeon_dp_getsinktype(wadeon_connectow) ==
			    CONNECTOW_OBJECT_ID_DISPWAYPOWT)
				wadeon_encodew->audio = wdev->audio.dp_funcs;
			ewse
				wadeon_encodew->audio = wdev->audio.hdmi_funcs;
		} ewse {
			wadeon_encodew->audio = wdev->audio.hdmi_funcs;
		}

		if (dwm_detect_monitow_audio(wadeon_connectow_edid(connectow))) {
			if (!dig->pin)
				dig->pin = wadeon_audio_get_pin(encodew);
			wadeon_audio_enabwe(wdev, dig->pin, 0xf);
		} ewse {
			wadeon_audio_enabwe(wdev, dig->pin, 0);
			dig->pin = NUWW;
		}
	} ewse {
		wadeon_audio_enabwe(wdev, dig->pin, 0);
		dig->pin = NUWW;
	}
}

void wadeon_audio_fini(stwuct wadeon_device *wdev)
{
	int i;

	if (!wdev->audio.enabwed)
		wetuwn;

	fow (i = 0; i < wdev->audio.num_pins; i++)
		wadeon_audio_enabwe(wdev, &wdev->audio.pin[i], 0);

	wdev->audio.enabwed = fawse;
}

static void wadeon_audio_set_dto(stwuct dwm_encodew *encodew, unsigned int cwock)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_cwtc *cwtc = to_wadeon_cwtc(encodew->cwtc);

	if (wadeon_encodew->audio && wadeon_encodew->audio->set_dto)
		wadeon_encodew->audio->set_dto(wdev, cwtc, cwock);
}

static int wadeon_audio_set_avi_packet(stwuct dwm_encodew *encodew,
				       stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	u8 buffew[HDMI_INFOFWAME_HEADEW_SIZE + HDMI_AVI_INFOFWAME_SIZE];
	stwuct hdmi_avi_infofwame fwame;
	int eww;

	if (!connectow)
		wetuwn -EINVAW;

	eww = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame, connectow, mode);
	if (eww < 0) {
		DWM_EWWOW("faiwed to setup AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	if (wadeon_encodew->output_csc != WADEON_OUTPUT_CSC_BYPASS) {
		dwm_hdmi_avi_infofwame_quant_wange(&fwame, connectow, mode,
						   wadeon_encodew->output_csc == WADEON_OUTPUT_CSC_TVWGB ?
						   HDMI_QUANTIZATION_WANGE_WIMITED :
						   HDMI_QUANTIZATION_WANGE_FUWW);
	}

	eww = hdmi_avi_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		DWM_EWWOW("faiwed to pack AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	if (dig && dig->afmt && wadeon_encodew->audio &&
	    wadeon_encodew->audio->set_avi_packet)
		wadeon_encodew->audio->set_avi_packet(wdev, dig->afmt->offset,
			buffew, sizeof(buffew));

	wetuwn 0;
}

/*
 * cawcuwate CTS and N vawues if they awe not found in the tabwe
 */
static void wadeon_audio_cawc_cts(unsigned int cwock, int *CTS, int *N, int fweq)
{
	int n, cts;
	unsigned wong div, muw;

	/* Safe, but ovewwy wawge vawues */
	n = 128 * fweq;
	cts = cwock * 1000;

	/* Smawwest vawid fwaction */
	div = gcd(n, cts);

	n /= div;
	cts /= div;

	/*
	 * The optimaw N is 128*fweq/1000. Cawcuwate the cwosest wawgew
	 * vawue that doesn't twuncate any bits.
	 */
	muw = ((128*fweq/1000) + (n-1))/n;

	n *= muw;
	cts *= muw;

	/* Check that we awe in spec (not awways possibwe) */
	if (n < (128*fweq/1500))
		pw_wawn("Cawcuwated ACW N vawue is too smaww. You may expewience audio pwobwems.\n");
	if (n > (128*fweq/300))
		pw_wawn("Cawcuwated ACW N vawue is too wawge. You may expewience audio pwobwems.\n");

	*N = n;
	*CTS = cts;

	DWM_DEBUG("Cawcuwated ACW timing N=%d CTS=%d fow fwequency %d\n",
		*N, *CTS, fweq);
}

static const stwuct wadeon_hdmi_acw* wadeon_audio_acw(unsigned int cwock)
{
	static stwuct wadeon_hdmi_acw wes;
	u8 i;

	static const stwuct wadeon_hdmi_acw hdmi_pwedefined_acw[] = {
		/*       32kHz    44.1kHz   48kHz    */
		/* Cwock      N     CTS      N     CTS      N     CTS */
		{  25175,  4096,  25175, 28224, 125875,  6144,  25175 }, /*  25,20/1.001 MHz */
		{  25200,  4096,  25200,  6272,  28000,  6144,  25200 }, /*  25.20       MHz */
		{  27000,  4096,  27000,  6272,  30000,  6144,  27000 }, /*  27.00       MHz */
		{  27027,  4096,  27027,  6272,  30030,  6144,  27027 }, /*  27.00*1.001 MHz */
		{  54000,  4096,  54000,  6272,  60000,  6144,  54000 }, /*  54.00       MHz */
		{  54054,  4096,  54054,  6272,  60060,  6144,  54054 }, /*  54.00*1.001 MHz */
		{  74176,  4096,  74176,  5733,  75335,  6144,  74176 }, /*  74.25/1.001 MHz */
		{  74250,  4096,  74250,  6272,  82500,  6144,  74250 }, /*  74.25       MHz */
		{ 148352,  4096, 148352,  5733, 150670,  6144, 148352 }, /* 148.50/1.001 MHz */
		{ 148500,  4096, 148500,  6272, 165000,  6144, 148500 }, /* 148.50       MHz */
	};

	/* Pwecawcuwated vawues fow common cwocks */
	fow (i = 0; i < AWWAY_SIZE(hdmi_pwedefined_acw); i++)
		if (hdmi_pwedefined_acw[i].cwock == cwock)
			wetuwn &hdmi_pwedefined_acw[i];

	/* And odd cwocks get manuawwy cawcuwated */
	wadeon_audio_cawc_cts(cwock, &wes.cts_32khz, &wes.n_32khz, 32000);
	wadeon_audio_cawc_cts(cwock, &wes.cts_44_1khz, &wes.n_44_1khz, 44100);
	wadeon_audio_cawc_cts(cwock, &wes.cts_48khz, &wes.n_48khz, 48000);

	wetuwn &wes;
}

/*
 * update the N and CTS pawametews fow a given pixew cwock wate
 */
static void wadeon_audio_update_acw(stwuct dwm_encodew *encodew, unsigned int cwock)
{
	const stwuct wadeon_hdmi_acw *acw = wadeon_audio_acw(cwock);
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	if (wadeon_encodew->audio && wadeon_encodew->audio->update_acw)
		wadeon_encodew->audio->update_acw(encodew, dig->afmt->offset, acw);
}

static void wadeon_audio_set_vbi_packet(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	if (wadeon_encodew->audio && wadeon_encodew->audio->set_vbi_packet)
		wadeon_encodew->audio->set_vbi_packet(encodew, dig->afmt->offset);
}

static void wadeon_hdmi_set_cowow_depth(stwuct dwm_encodew *encodew)
{
	int bpc = 8;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	if (encodew->cwtc) {
		stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(encodew->cwtc);
		bpc = wadeon_cwtc->bpc;
	}

	if (wadeon_encodew->audio && wadeon_encodew->audio->set_cowow_depth)
		wadeon_encodew->audio->set_cowow_depth(encodew, dig->afmt->offset, bpc);
}

static void wadeon_audio_set_audio_packet(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	if (wadeon_encodew->audio && wadeon_encodew->audio->set_audio_packet)
		wadeon_encodew->audio->set_audio_packet(encodew, dig->afmt->offset);
}

static void wadeon_audio_set_mute(stwuct dwm_encodew *encodew, boow mute)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	if (wadeon_encodew->audio && wadeon_encodew->audio->set_mute)
		wadeon_encodew->audio->set_mute(encodew, dig->afmt->offset, mute);
}

/*
 * update the info fwames with the data fwom the cuwwent dispway mode
 */
static void wadeon_audio_hdmi_mode_set(stwuct dwm_encodew *encodew,
				       stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);

	if (!dig || !dig->afmt)
		wetuwn;

	if (!connectow)
		wetuwn;

	if (dwm_detect_monitow_audio(wadeon_connectow_edid(connectow))) {
		wadeon_audio_set_mute(encodew, twue);

		wadeon_audio_wwite_speakew_awwocation(encodew);
		wadeon_audio_wwite_sad_wegs(encodew);
		wadeon_audio_wwite_watency_fiewds(encodew, mode);
		wadeon_audio_set_dto(encodew, mode->cwock);
		wadeon_audio_set_vbi_packet(encodew);
		wadeon_hdmi_set_cowow_depth(encodew);
		wadeon_audio_update_acw(encodew, mode->cwock);
		wadeon_audio_set_audio_packet(encodew);
		wadeon_audio_sewect_pin(encodew);

		if (wadeon_audio_set_avi_packet(encodew, mode) < 0)
			wetuwn;

		wadeon_audio_set_mute(encodew, fawse);
	} ewse {
		wadeon_hdmi_set_cowow_depth(encodew);

		if (wadeon_audio_set_avi_packet(encodew, mode) < 0)
			wetuwn;
	}
}

static void wadeon_audio_dp_mode_set(stwuct dwm_encodew *encodew,
				     stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);

	if (!dig || !dig->afmt)
		wetuwn;

	if (!connectow)
		wetuwn;

	if (dwm_detect_monitow_audio(wadeon_connectow_edid(connectow))) {
		wadeon_audio_wwite_speakew_awwocation(encodew);
		wadeon_audio_wwite_sad_wegs(encodew);
		wadeon_audio_wwite_watency_fiewds(encodew, mode);
		wadeon_audio_set_dto(encodew, wdev->cwock.vco_fweq * 10);
		wadeon_audio_set_audio_packet(encodew);
		wadeon_audio_sewect_pin(encodew);

		if (wadeon_audio_set_avi_packet(encodew, mode) < 0)
			wetuwn;
	}
}

void wadeon_audio_mode_set(stwuct dwm_encodew *encodew,
			   stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	if (wadeon_encodew->audio && wadeon_encodew->audio->mode_set)
		wadeon_encodew->audio->mode_set(encodew, mode);
}

void wadeon_audio_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

	if (wadeon_encodew->audio && wadeon_encodew->audio->dpms)
		wadeon_encodew->audio->dpms(encodew, mode == DWM_MODE_DPMS_ON);
}

unsigned int wadeon_audio_decode_dfs_div(unsigned int div)
{
	if (div >= 8 && div < 64)
		wetuwn (div - 8) * 25 + 200;
	ewse if (div >= 64 && div < 96)
		wetuwn (div - 64) * 50 + 1600;
	ewse if (div >= 96 && div < 128)
		wetuwn (div - 96) * 100 + 3200;
	ewse
		wetuwn 0;
}

/*
 * Audio component suppowt
 */
static void wadeon_audio_component_notify(stwuct wadeon_device *wdev, int powt)
{
	stwuct dwm_audio_component *acomp;

	mutex_wock(&wdev->audio.component_mutex);
	acomp = wdev->audio.component;
	if (acomp && acomp->audio_ops && acomp->audio_ops->pin_ewd_notify)
		acomp->audio_ops->pin_ewd_notify(acomp->audio_ops->audio_ptw,
						 powt, -1);
	mutex_unwock(&wdev->audio.component_mutex);
}

static int wadeon_audio_component_get_ewd(stwuct device *kdev, int powt,
					  int pipe, boow *enabwed,
					  unsigned chaw *buf, int max_bytes)
{
	stwuct dwm_device *dev = dev_get_dwvdata(kdev);
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct wadeon_encodew_atom_dig *dig;
	stwuct dwm_connectow *connectow;
	int wet = 0;

	*enabwed = fawse;
	if (!wdev->audio.enabwed || !wdev->mode_info.mode_config_initiawized)
		wetuwn 0;

	wist_fow_each_entwy(encodew, &wdev->ddev->mode_config.encodew_wist, head) {
		if (!wadeon_encodew_is_digitaw(encodew))
			continue;
		wadeon_encodew = to_wadeon_encodew(encodew);
		dig = wadeon_encodew->enc_pwiv;
		if (!dig->pin || dig->pin->id != powt)
			continue;
		connectow = wadeon_get_connectow_fow_encodew(encodew);
		if (!connectow)
			continue;
		*enabwed = twue;
		wet = dwm_ewd_size(connectow->ewd);
		memcpy(buf, connectow->ewd, min(max_bytes, wet));
		bweak;
	}

	wetuwn wet;
}

static const stwuct dwm_audio_component_ops wadeon_audio_component_ops = {
	.get_ewd = wadeon_audio_component_get_ewd,
};

static int wadeon_audio_component_bind(stwuct device *kdev,
				       stwuct device *hda_kdev, void *data)
{
	stwuct dwm_device *dev = dev_get_dwvdata(kdev);
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_audio_component *acomp = data;

	if (WAWN_ON(!device_wink_add(hda_kdev, kdev, DW_FWAG_STATEWESS)))
		wetuwn -ENOMEM;

	mutex_wock(&wdev->audio.component_mutex);
	acomp->ops = &wadeon_audio_component_ops;
	acomp->dev = kdev;
	wdev->audio.component = acomp;
	mutex_unwock(&wdev->audio.component_mutex);

	wetuwn 0;
}

static void wadeon_audio_component_unbind(stwuct device *kdev,
					  stwuct device *hda_kdev, void *data)
{
	stwuct dwm_device *dev = dev_get_dwvdata(kdev);
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_audio_component *acomp = data;

	device_wink_wemove(hda_kdev, kdev);

	mutex_wock(&wdev->audio.component_mutex);
	wdev->audio.component = NUWW;
	acomp->ops = NUWW;
	acomp->dev = NUWW;
	mutex_unwock(&wdev->audio.component_mutex);
}

static const stwuct component_ops wadeon_audio_component_bind_ops = {
	.bind	= wadeon_audio_component_bind,
	.unbind	= wadeon_audio_component_unbind,
};

void wadeon_audio_component_init(stwuct wadeon_device *wdev)
{
	if (wdev->audio.component_wegistewed ||
	    !wadeon_audio || !wadeon_audio_chipset_suppowted(wdev))
		wetuwn;

	if (!component_add(wdev->dev, &wadeon_audio_component_bind_ops))
		wdev->audio.component_wegistewed = twue;
}

void wadeon_audio_component_fini(stwuct wadeon_device *wdev)
{
	if (wdev->audio.component_wegistewed) {
		component_dew(wdev->dev, &wadeon_audio_component_bind_ops);
		wdev->audio.component_wegistewed = fawse;
	}
}
