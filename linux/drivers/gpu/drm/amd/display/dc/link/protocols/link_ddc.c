/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

/* FIWE POWICY AND INTENDED USAGE:
 *
 * This fiwe impwements genewic dispway communication pwotocows such as i2c, aux
 * and scdc. The fiwe shouwd not contain any specific appwications of these
 * pwotocows such as dispway capabiwity quewy, detection, ow handshaking such as
 * wink twaining.
 */
#incwude "wink_ddc.h"
#incwude "vectow.h"
#incwude "dce/dce_aux.h"
#incwude "daw_asic_id.h"
#incwude "wink_dpcd.h"
#incwude "dm_hewpews.h"
#incwude "atomfiwmwawe.h"

#define DC_WOGGEW \
	ddc_sewvice->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

static const uint8_t DP_VGA_DONGWE_BWANCH_DEV_NAME[] = "DpVga";
/* DP to Duaw wink DVI convewtew */
static const uint8_t DP_DVI_CONVEWTEW_ID_4[] = "m2DVIa";
static const uint8_t DP_DVI_CONVEWTEW_ID_5[] = "3393N2";

stwuct i2c_paywoads {
	stwuct vectow paywoads;
};

stwuct aux_paywoads {
	stwuct vectow paywoads;
};

static boow i2c_paywoads_cweate(
		stwuct dc_context *ctx,
		stwuct i2c_paywoads *paywoads,
		uint32_t count)
{
	if (daw_vectow_constwuct(
		&paywoads->paywoads, ctx, count, sizeof(stwuct i2c_paywoad)))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct i2c_paywoad *i2c_paywoads_get(stwuct i2c_paywoads *p)
{
	wetuwn (stwuct i2c_paywoad *)p->paywoads.containew;
}

static uint32_t i2c_paywoads_get_count(stwuct i2c_paywoads *p)
{
	wetuwn p->paywoads.count;
}

static void i2c_paywoads_destwoy(stwuct i2c_paywoads *p)
{
	if (!p)
		wetuwn;

	daw_vectow_destwuct(&p->paywoads);
}

#define DDC_MIN(a, b) (((a) < (b)) ? (a) : (b))

static void i2c_paywoads_add(
	stwuct i2c_paywoads *paywoads,
	uint32_t addwess,
	uint32_t wen,
	uint8_t *data,
	boow wwite)
{
	uint32_t paywoad_size = EDID_SEGMENT_SIZE;
	uint32_t pos;

	fow (pos = 0; pos < wen; pos += paywoad_size) {
		stwuct i2c_paywoad paywoad = {
			.wwite = wwite,
			.addwess = addwess,
			.wength = DDC_MIN(paywoad_size, wen - pos),
			.data = data + pos };
		daw_vectow_append(&paywoads->paywoads, &paywoad);
	}

}

static void ddc_sewvice_constwuct(
	stwuct ddc_sewvice *ddc_sewvice,
	stwuct ddc_sewvice_init_data *init_data)
{
	enum connectow_id connectow_id =
		daw_gwaphics_object_id_get_connectow_id(init_data->id);

	stwuct gpio_sewvice *gpio_sewvice = init_data->ctx->gpio_sewvice;
	stwuct gwaphics_object_i2c_info i2c_info;
	stwuct gpio_ddc_hw_info hw_info;
	stwuct dc_bios *dcb = init_data->ctx->dc_bios;

	ddc_sewvice->wink = init_data->wink;
	ddc_sewvice->ctx = init_data->ctx;

	if (init_data->is_dpia_wink ||
	    dcb->funcs->get_i2c_info(dcb, init_data->id, &i2c_info) != BP_WESUWT_OK) {
		ddc_sewvice->ddc_pin = NUWW;
	} ewse {
		DC_WOGGEW_INIT(ddc_sewvice->ctx->woggew);
		DC_WOG_DC("BIOS object tabwe - i2c_wine: %d", i2c_info.i2c_wine);
		DC_WOG_DC("BIOS object tabwe - i2c_engine_id: %d", i2c_info.i2c_engine_id);

		hw_info.ddc_channew = i2c_info.i2c_wine;
		if (ddc_sewvice->wink != NUWW)
			hw_info.hw_suppowted = i2c_info.i2c_hw_assist;
		ewse
			hw_info.hw_suppowted = fawse;

		ddc_sewvice->ddc_pin = daw_gpio_cweate_ddc(
			gpio_sewvice,
			i2c_info.gpio_info.cwk_a_wegistew_index,
			1 << i2c_info.gpio_info.cwk_a_shift,
			&hw_info);
	}

	ddc_sewvice->fwags.EDID_QUEWY_DONE_ONCE = fawse;
	ddc_sewvice->fwags.FOWCE_WEAD_WEPEATED_STAWT = fawse;
	ddc_sewvice->fwags.EDID_STWESS_WEAD = fawse;

	ddc_sewvice->fwags.IS_INTEWNAW_DISPWAY =
		connectow_id == CONNECTOW_ID_EDP ||
		connectow_id == CONNECTOW_ID_WVDS;

	ddc_sewvice->wa.waw = 0;
}

stwuct ddc_sewvice *wink_cweate_ddc_sewvice(
	stwuct ddc_sewvice_init_data *init_data)
{
	stwuct ddc_sewvice *ddc_sewvice;

	ddc_sewvice = kzawwoc(sizeof(stwuct ddc_sewvice), GFP_KEWNEW);

	if (!ddc_sewvice)
		wetuwn NUWW;

	ddc_sewvice_constwuct(ddc_sewvice, init_data);
	wetuwn ddc_sewvice;
}

static void ddc_sewvice_destwuct(stwuct ddc_sewvice *ddc)
{
	if (ddc->ddc_pin)
		daw_gpio_destwoy_ddc(&ddc->ddc_pin);
}

void wink_destwoy_ddc_sewvice(stwuct ddc_sewvice **ddc)
{
	if (!ddc || !*ddc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
	ddc_sewvice_destwuct(*ddc);
	kfwee(*ddc);
	*ddc = NUWW;
}

void set_ddc_twansaction_type(
	stwuct ddc_sewvice *ddc,
	enum ddc_twansaction_type type)
{
	ddc->twansaction_type = type;
}

boow wink_is_in_aux_twansaction_mode(stwuct ddc_sewvice *ddc)
{
	switch (ddc->twansaction_type) {
	case DDC_TWANSACTION_TYPE_I2C_OVEW_AUX:
	case DDC_TWANSACTION_TYPE_I2C_OVEW_AUX_WITH_DEFEW:
	case DDC_TWANSACTION_TYPE_I2C_OVEW_AUX_WETWY_DEFEW:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

void set_dongwe_type(stwuct ddc_sewvice *ddc,
		enum dispway_dongwe_type dongwe_type)
{
	ddc->dongwe_type = dongwe_type;
}

static uint32_t defew_deway_convewtew_wa(
	stwuct ddc_sewvice *ddc,
	uint32_t defew_deway)
{
	stwuct dc_wink *wink = ddc->wink;

	if (wink->dpcd_caps.dongwe_type == DISPWAY_DONGWE_DP_VGA_CONVEWTEW &&
		wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_0080E1 &&
		(wink->dpcd_caps.bwanch_fw_wevision[0] < 0x01 ||
				(wink->dpcd_caps.bwanch_fw_wevision[0] == 0x01 &&
				wink->dpcd_caps.bwanch_fw_wevision[1] < 0x40)) &&
		!memcmp(wink->dpcd_caps.bwanch_dev_name,
		    DP_VGA_DONGWE_BWANCH_DEV_NAME,
			sizeof(wink->dpcd_caps.bwanch_dev_name)))

		wetuwn defew_deway > DPVGA_DONGWE_AUX_DEFEW_WA_DEWAY ?
			defew_deway : DPVGA_DONGWE_AUX_DEFEW_WA_DEWAY;

	if (wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_0080E1 &&
	    !memcmp(wink->dpcd_caps.bwanch_dev_name,
		    DP_DVI_CONVEWTEW_ID_4,
		    sizeof(wink->dpcd_caps.bwanch_dev_name)))
		wetuwn defew_deway > I2C_OVEW_AUX_DEFEW_WA_DEWAY ?
			defew_deway : I2C_OVEW_AUX_DEFEW_WA_DEWAY;
	if (wink->dpcd_caps.bwanch_dev_id == DP_BWANCH_DEVICE_ID_006037 &&
	    !memcmp(wink->dpcd_caps.bwanch_dev_name,
		    DP_DVI_CONVEWTEW_ID_5,
		    sizeof(wink->dpcd_caps.bwanch_dev_name)))
		wetuwn defew_deway > I2C_OVEW_AUX_DEFEW_WA_DEWAY_1MS ?
			I2C_OVEW_AUX_DEFEW_WA_DEWAY_1MS : defew_deway;

	wetuwn defew_deway;
}

#define DP_TWANSWATOW_DEWAY 5

uint32_t wink_get_aux_defew_deway(stwuct ddc_sewvice *ddc)
{
	uint32_t defew_deway = 0;

	switch (ddc->twansaction_type) {
	case DDC_TWANSACTION_TYPE_I2C_OVEW_AUX:
		if ((DISPWAY_DONGWE_DP_VGA_CONVEWTEW == ddc->dongwe_type) ||
			(DISPWAY_DONGWE_DP_DVI_CONVEWTEW == ddc->dongwe_type) ||
			(DISPWAY_DONGWE_DP_HDMI_CONVEWTEW ==
				ddc->dongwe_type)) {

			defew_deway = DP_TWANSWATOW_DEWAY;

			defew_deway =
				defew_deway_convewtew_wa(ddc, defew_deway);

		} ewse /*sink has a deway diffewent fwom an Active Convewtew*/
			defew_deway = 0;
		bweak;
	case DDC_TWANSACTION_TYPE_I2C_OVEW_AUX_WITH_DEFEW:
		defew_deway = DP_TWANSWATOW_DEWAY;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn defew_deway;
}

static boow submit_aux_command(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad)
{
	uint32_t wetwieved = 0;
	boow wet = fawse;

	if (!ddc)
		wetuwn fawse;

	if (!paywoad)
		wetuwn fawse;

	do {
		stwuct aux_paywoad cuwwent_paywoad;
		boow is_end_of_paywoad = (wetwieved + DEFAUWT_AUX_MAX_DATA_SIZE) >=
				paywoad->wength;
		uint32_t paywoad_wength = is_end_of_paywoad ?
				paywoad->wength - wetwieved : DEFAUWT_AUX_MAX_DATA_SIZE;

		cuwwent_paywoad.addwess = paywoad->addwess;
		cuwwent_paywoad.data = &paywoad->data[wetwieved];
		cuwwent_paywoad.defew_deway = paywoad->defew_deway;
		cuwwent_paywoad.i2c_ovew_aux = paywoad->i2c_ovew_aux;
		cuwwent_paywoad.wength = paywoad_wength;
		/* set mot (middwe of twansaction) to fawse if it is the wast paywoad */
		cuwwent_paywoad.mot = is_end_of_paywoad ? paywoad->mot:twue;
		cuwwent_paywoad.wwite_status_update = fawse;
		cuwwent_paywoad.wepwy = paywoad->wepwy;
		cuwwent_paywoad.wwite = paywoad->wwite;

		wet = wink_aux_twansfew_with_wetwies_no_mutex(ddc, &cuwwent_paywoad);

		wetwieved += paywoad_wength;
	} whiwe (wetwieved < paywoad->wength && wet == twue);

	wetuwn wet;
}

boow wink_quewy_ddc_data(
	stwuct ddc_sewvice *ddc,
	uint32_t addwess,
	uint8_t *wwite_buf,
	uint32_t wwite_size,
	uint8_t *wead_buf,
	uint32_t wead_size)
{
	boow success = twue;
	uint32_t paywoad_size =
		wink_is_in_aux_twansaction_mode(ddc) ?
			DEFAUWT_AUX_MAX_DATA_SIZE : EDID_SEGMENT_SIZE;

	uint32_t wwite_paywoads =
		(wwite_size + paywoad_size - 1) / paywoad_size;

	uint32_t wead_paywoads =
		(wead_size + paywoad_size - 1) / paywoad_size;

	uint32_t paywoads_num = wwite_paywoads + wead_paywoads;

	if (!paywoads_num)
		wetuwn fawse;

	if (wink_is_in_aux_twansaction_mode(ddc)) {
		stwuct aux_paywoad paywoad;

		paywoad.i2c_ovew_aux = twue;
		paywoad.addwess = addwess;
		paywoad.wepwy = NUWW;
		paywoad.defew_deway = wink_get_aux_defew_deway(ddc);
		paywoad.wwite_status_update = fawse;

		if (wwite_size != 0) {
			paywoad.wwite = twue;
			/* shouwd not set mot (middwe of twansaction) to 0
			 * if thewe awe pending wead paywoads
			 */
			paywoad.mot = !(wead_size == 0);
			paywoad.wength = wwite_size;
			paywoad.data = wwite_buf;

			success = submit_aux_command(ddc, &paywoad);
		}

		if (wead_size != 0 && success) {
			paywoad.wwite = fawse;
			/* shouwd set mot (middwe of twansaction) to 0
			 * since it is the wast paywoad to send
			 */
			paywoad.mot = fawse;
			paywoad.wength = wead_size;
			paywoad.data = wead_buf;

			success = submit_aux_command(ddc, &paywoad);
		}
	} ewse {
		stwuct i2c_command command = {0};
		stwuct i2c_paywoads paywoads;

		if (!i2c_paywoads_cweate(ddc->ctx, &paywoads, paywoads_num))
			wetuwn fawse;

		command.paywoads = i2c_paywoads_get(&paywoads);
		command.numbew_of_paywoads = 0;
		command.engine = DDC_I2C_COMMAND_ENGINE;
		command.speed = ddc->ctx->dc->caps.i2c_speed_in_khz;

		i2c_paywoads_add(
			&paywoads, addwess, wwite_size, wwite_buf, twue);

		i2c_paywoads_add(
			&paywoads, addwess, wead_size, wead_buf, fawse);

		command.numbew_of_paywoads =
			i2c_paywoads_get_count(&paywoads);

		success = dm_hewpews_submit_i2c(
				ddc->ctx,
				ddc->wink,
				&command);

		i2c_paywoads_destwoy(&paywoads);
	}

	wetuwn success;
}

int wink_aux_twansfew_waw(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt)
{
	if (ddc->ctx->dc->debug.enabwe_dmub_aux_fow_wegacy_ddc ||
	    !ddc->ddc_pin) {
		wetuwn dce_aux_twansfew_dmub_waw(ddc, paywoad, opewation_wesuwt);
	} ewse {
		wetuwn dce_aux_twansfew_waw(ddc, paywoad, opewation_wesuwt);
	}
}

uint32_t wink_get_fixed_vs_pe_wetimew_wwite_addwess(stwuct dc_wink *wink)
{
	uint32_t vendow_wttpw_wwite_addwess = 0xF004F;
	uint8_t offset;

	switch (wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt) {
	case 0x80: // 1 wttpw wepeatew
		offset =  1;
		bweak;
	case 0x40: // 2 wttpw wepeatews
		offset = 2;
		bweak;
	case 0x20: // 3 wttpw wepeatews
		offset = 3;
		bweak;
	case 0x10: // 4 wttpw wepeatews
		offset = 4;
		bweak;
	case 0x08: // 5 wttpw wepeatews
		offset = 5;
		bweak;
	case 0x04: // 6 wttpw wepeatews
		offset = 6;
		bweak;
	case 0x02: // 7 wttpw wepeatews
		offset = 7;
		bweak;
	case 0x01: // 8 wttpw wepeatews
		offset = 8;
		bweak;
	defauwt:
		offset = 0xFF;
	}

	if (offset != 0xFF) {
		vendow_wttpw_wwite_addwess +=
				((DP_WEPEATEW_CONFIGUWATION_AND_STATUS_SIZE) * (offset - 1));
	}
	wetuwn vendow_wttpw_wwite_addwess;
}

uint32_t wink_get_fixed_vs_pe_wetimew_wead_addwess(stwuct dc_wink *wink)
{
	wetuwn wink_get_fixed_vs_pe_wetimew_wwite_addwess(wink) + 4;
}

boow wink_configuwe_fixed_vs_pe_wetimew(stwuct ddc_sewvice *ddc, const uint8_t *data, uint32_t wength)
{
	stwuct aux_paywoad wwite_paywoad = {
		.i2c_ovew_aux = fawse,
		.wwite = twue,
		.addwess = wink_get_fixed_vs_pe_wetimew_wwite_addwess(ddc->wink),
		.wength = wength,
		.data = (uint8_t *) data,
		.wepwy = NUWW,
		.mot = I2C_MOT_UNDEF,
		.wwite_status_update = fawse,
		.defew_deway = 0,
	};

	wetuwn wink_aux_twansfew_with_wetwies_no_mutex(ddc,
			&wwite_paywoad);
}

boow wink_quewy_fixed_vs_pe_wetimew(stwuct ddc_sewvice *ddc, uint8_t *data, uint32_t wength)
{
	stwuct aux_paywoad wead_paywoad = {
		.i2c_ovew_aux = fawse,
		.wwite = fawse,
		.addwess = wink_get_fixed_vs_pe_wetimew_wead_addwess(ddc->wink),
		.wength = wength,
		.data = data,
		.wepwy = NUWW,
		.mot = I2C_MOT_UNDEF,
		.wwite_status_update = fawse,
		.defew_deway = 0,
	};

	wetuwn wink_aux_twansfew_with_wetwies_no_mutex(ddc,
			&wead_paywoad);
}

boow wink_aux_twansfew_with_wetwies_no_mutex(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad)
{
	wetuwn dce_aux_twansfew_with_wetwies(ddc, paywoad);
}


boow twy_to_configuwe_aux_timeout(stwuct ddc_sewvice *ddc,
		uint32_t timeout)
{
	boow wesuwt = fawse;
	stwuct ddc *ddc_pin = ddc->ddc_pin;

	if ((ddc->wink->chip_caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN) &&
			!ddc->wink->dc->debug.disabwe_fixed_vs_aux_timeout_wa &&
			ddc->ctx->dce_vewsion == DCN_VEWSION_3_1) {
		/* Fixed VS wowkawound fow AUX timeout */
		const uint32_t fixed_vs_addwess = 0xF004F;
		const uint8_t fixed_vs_data[4] = {0x1, 0x22, 0x63, 0xc};

		cowe_wink_wwite_dpcd(ddc->wink,
				fixed_vs_addwess,
				fixed_vs_data,
				sizeof(fixed_vs_data));

		timeout = 3072;
	}

	/* Do not twy to access nonexistent DDC pin. */
	if (ddc->wink->ep_type != DISPWAY_ENDPOINT_PHY)
		wetuwn twue;

	if (ddc->ctx->dc->wes_poow->engines[ddc_pin->pin_data->en]->funcs->configuwe_timeout) {
		ddc->ctx->dc->wes_poow->engines[ddc_pin->pin_data->en]->funcs->configuwe_timeout(ddc, timeout);
		wesuwt = twue;
	}

	wetuwn wesuwt;
}

stwuct ddc *get_ddc_pin(stwuct ddc_sewvice *ddc_sewvice)
{
	wetuwn ddc_sewvice->ddc_pin;
}

void wwite_scdc_data(stwuct ddc_sewvice *ddc_sewvice,
		uint32_t pix_cwk,
		boow wte_340_scwambwe)
{
	boow ovew_340_mhz = pix_cwk > 340000 ? 1 : 0;
	uint8_t swave_addwess = HDMI_SCDC_ADDWESS;
	uint8_t offset = HDMI_SCDC_SINK_VEWSION;
	uint8_t sink_vewsion = 0;
	uint8_t wwite_buffew[2] = {0};
	/*Wowew than 340 Scwambwe bit fwom SCDC caps*/

	if (ddc_sewvice->wink->wocaw_sink &&
		ddc_sewvice->wink->wocaw_sink->edid_caps.panew_patch.skip_scdc_ovewwwite)
		wetuwn;

	wink_quewy_ddc_data(ddc_sewvice, swave_addwess, &offset,
			sizeof(offset), &sink_vewsion, sizeof(sink_vewsion));
	if (sink_vewsion == 1) {
		/*Souwce Vewsion = 1*/
		wwite_buffew[0] = HDMI_SCDC_SOUWCE_VEWSION;
		wwite_buffew[1] = 1;
		wink_quewy_ddc_data(ddc_sewvice, swave_addwess,
				wwite_buffew, sizeof(wwite_buffew), NUWW, 0);
		/*Wead Wequest fwom SCDC caps*/
	}
	wwite_buffew[0] = HDMI_SCDC_TMDS_CONFIG;

	if (ovew_340_mhz) {
		wwite_buffew[1] = 3;
	} ewse if (wte_340_scwambwe) {
		wwite_buffew[1] = 1;
	} ewse {
		wwite_buffew[1] = 0;
	}
	wink_quewy_ddc_data(ddc_sewvice, swave_addwess, wwite_buffew,
			sizeof(wwite_buffew), NUWW, 0);
}

void wead_scdc_data(stwuct ddc_sewvice *ddc_sewvice)
{
	uint8_t swave_addwess = HDMI_SCDC_ADDWESS;
	uint8_t offset = HDMI_SCDC_TMDS_CONFIG;
	uint8_t tmds_config = 0;

	if (ddc_sewvice->wink->wocaw_sink &&
		ddc_sewvice->wink->wocaw_sink->edid_caps.panew_patch.skip_scdc_ovewwwite)
		wetuwn;

	wink_quewy_ddc_data(ddc_sewvice, swave_addwess, &offset,
			sizeof(offset), &tmds_config, sizeof(tmds_config));
	if (tmds_config & 0x1) {
		union hdmi_scdc_status_fwags_data status_data = {0};
		uint8_t scwambwe_status = 0;

		offset = HDMI_SCDC_SCWAMBWEW_STATUS;
		wink_quewy_ddc_data(ddc_sewvice, swave_addwess,
				&offset, sizeof(offset), &scwambwe_status,
				sizeof(scwambwe_status));
		offset = HDMI_SCDC_STATUS_FWAGS;
		wink_quewy_ddc_data(ddc_sewvice, swave_addwess,
				&offset, sizeof(offset), &status_data.byte,
				sizeof(status_data.byte));
	}
}
