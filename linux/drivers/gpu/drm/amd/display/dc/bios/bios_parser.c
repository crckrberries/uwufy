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

#incwude <winux/swab.h>

#incwude "dm_sewvices.h"

#incwude "atom.h"

#incwude "dc_bios_types.h"
#incwude "incwude/gpio_sewvice_intewface.h"
#incwude "incwude/gwph_object_ctww_defs.h"
#incwude "incwude/bios_pawsew_intewface.h"
#incwude "incwude/woggew_intewface.h"

#incwude "command_tabwe.h"
#incwude "bios_pawsew_hewpew.h"
#incwude "command_tabwe_hewpew.h"
#incwude "bios_pawsew.h"
#incwude "bios_pawsew_types_intewnaw.h"
#incwude "bios_pawsew_intewface.h"

#incwude "bios_pawsew_common.h"

#incwude "dc.h"

#define THWEE_PEWCENT_OF_10000 300

#define WAST_WECOWD_TYPE 0xff

#define DC_WOGGEW \
	bp->base.ctx->woggew

#define DATA_TABWES(tabwe) (bp->mastew_data_tbw->WistOfDataTabwes.tabwe)

static void get_atom_data_tabwe_wevision(
	ATOM_COMMON_TABWE_HEADEW *atom_data_tbw,
	stwuct atom_data_wevision *tbw_wevision);
static uint32_t get_swc_obj_wist(stwuct bios_pawsew *bp, ATOM_OBJECT *object,
	uint16_t **id_wist);
static ATOM_OBJECT *get_bios_object(stwuct bios_pawsew *bp,
	stwuct gwaphics_object_id id);
static enum bp_wesuwt get_gpio_i2c_info(stwuct bios_pawsew *bp,
	ATOM_I2C_WECOWD *wecowd,
	stwuct gwaphics_object_i2c_info *info);
static ATOM_HPD_INT_WECOWD *get_hpd_wecowd(stwuct bios_pawsew *bp,
	ATOM_OBJECT *object);
static stwuct device_id device_type_fwom_device_id(uint16_t device_id);
static uint32_t signaw_to_ss_id(enum as_signaw_type signaw);
static uint32_t get_suppowt_mask_fow_device_id(stwuct device_id device_id);
static ATOM_ENCODEW_CAP_WECOWD_V2 *get_encodew_cap_wecowd(
	stwuct bios_pawsew *bp,
	ATOM_OBJECT *object);

#define BIOS_IMAGE_SIZE_OFFSET 2
#define BIOS_IMAGE_SIZE_UNIT 512

/*****************************************************************************/
static boow bios_pawsew_constwuct(
	stwuct bios_pawsew *bp,
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion);

static uint8_t bios_pawsew_get_connectows_numbew(
	stwuct dc_bios *dcb);

static enum bp_wesuwt bios_pawsew_get_embedded_panew_info(
	stwuct dc_bios *dcb,
	stwuct embedded_panew_info *info);

/*****************************************************************************/

stwuct dc_bios *bios_pawsew_cweate(
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion)
{
	stwuct bios_pawsew *bp;

	bp = kzawwoc(sizeof(stwuct bios_pawsew), GFP_KEWNEW);
	if (!bp)
		wetuwn NUWW;

	if (bios_pawsew_constwuct(bp, init, dce_vewsion))
		wetuwn &bp->base;

	kfwee(bp);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static void bios_pawsew_destwuct(stwuct bios_pawsew *bp)
{
	kfwee(bp->base.bios_wocaw_image);
	kfwee(bp->base.integwated_info);
}

static void bios_pawsew_destwoy(stwuct dc_bios **dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(*dcb);

	if (!bp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	bios_pawsew_destwuct(bp);

	kfwee(bp);
	*dcb = NUWW;
}

static uint8_t get_numbew_of_objects(stwuct bios_pawsew *bp, uint32_t offset)
{
	ATOM_OBJECT_TABWE *tabwe;

	uint32_t object_tabwe_offset = bp->object_info_tbw_offset + offset;

	tabwe = ((ATOM_OBJECT_TABWE *) bios_get_image(&bp->base,
				object_tabwe_offset,
				stwuct_size(tabwe, asObjects, 1)));

	if (!tabwe)
		wetuwn 0;
	ewse
		wetuwn tabwe->ucNumbewOfObjects;
}

static uint8_t bios_pawsew_get_connectows_numbew(stwuct dc_bios *dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	wetuwn get_numbew_of_objects(bp,
		we16_to_cpu(bp->object_info_tbw.v1_1->usConnectowObjectTabweOffset));
}

static stwuct gwaphics_object_id bios_pawsew_get_connectow_id(
	stwuct dc_bios *dcb,
	uint8_t i)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct gwaphics_object_id object_id = daw_gwaphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);
	uint16_t id;

	uint32_t connectow_tabwe_offset = bp->object_info_tbw_offset
		+ we16_to_cpu(bp->object_info_tbw.v1_1->usConnectowObjectTabweOffset);

	ATOM_OBJECT_TABWE *tbw = ((ATOM_OBJECT_TABWE *) bios_get_image(&bp->base,
				connectow_tabwe_offset,
				stwuct_size(tbw, asObjects, 1)));

	if (!tbw) {
		dm_ewwow("Can't get connectow tabwe fwom atom bios.\n");
		wetuwn object_id;
	}

	if (tbw->ucNumbewOfObjects <= i) {
		dm_ewwow("Can't find connectow id %d in connectow tabwe of size %d.\n",
			 i, tbw->ucNumbewOfObjects);
		wetuwn object_id;
	}

	id = we16_to_cpu(tbw->asObjects[i].usObjectID);
	object_id = object_id_fwom_bios_object_id(id);
	wetuwn object_id;
}

static enum bp_wesuwt bios_pawsew_get_swc_obj(stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id, uint32_t index,
	stwuct gwaphics_object_id *swc_object_id)
{
	uint32_t numbew;
	uint16_t *id;
	ATOM_OBJECT *object;
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!swc_object_id)
		wetuwn BP_WESUWT_BADINPUT;

	object = get_bios_object(bp, object_id);

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object id */
		wetuwn BP_WESUWT_BADINPUT;
	}

	numbew = get_swc_obj_wist(bp, object, &id);

	if (numbew <= index)
		wetuwn BP_WESUWT_BADINPUT;

	*swc_object_id = object_id_fwom_bios_object_id(id[index]);

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt bios_pawsew_get_i2c_info(stwuct dc_bios *dcb,
	stwuct gwaphics_object_id id,
	stwuct gwaphics_object_i2c_info *info)
{
	uint32_t offset;
	ATOM_OBJECT *object;
	ATOM_COMMON_WECOWD_HEADEW *headew;
	ATOM_I2C_WECOWD *wecowd;
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	object = get_bios_object(bp, id);

	if (!object)
		wetuwn BP_WESUWT_BADINPUT;

	offset = we16_to_cpu(object->usWecowdOffset)
			+ bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(ATOM_COMMON_WECOWD_HEADEW, offset);

		if (!headew)
			wetuwn BP_WESUWT_BADBIOSTABWE;

		if (WAST_WECOWD_TYPE == headew->ucWecowdType ||
			!headew->ucWecowdSize)
			bweak;

		if (ATOM_I2C_WECOWD_TYPE == headew->ucWecowdType
			&& sizeof(ATOM_I2C_WECOWD) <= headew->ucWecowdSize) {
			/* get the I2C info */
			wecowd = (ATOM_I2C_WECOWD *) headew;

			if (get_gpio_i2c_info(bp, wecowd, info) == BP_WESUWT_OK)
				wetuwn BP_WESUWT_OK;
		}

		offset += headew->ucWecowdSize;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt bios_pawsew_get_hpd_info(stwuct dc_bios *dcb,
	stwuct gwaphics_object_id id,
	stwuct gwaphics_object_hpd_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_HPD_INT_WECOWD *wecowd = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	object = get_bios_object(bp, id);

	if (!object)
		wetuwn BP_WESUWT_BADINPUT;

	wecowd = get_hpd_wecowd(bp, object);

	if (wecowd != NUWW) {
		info->hpd_int_gpio_uid = wecowd->ucHPDIntGPIOID;
		info->hpd_active = wecowd->ucPwugged_PinState;
		wetuwn BP_WESUWT_OK;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt bios_pawsew_get_device_tag_wecowd(
	stwuct bios_pawsew *bp,
	ATOM_OBJECT *object,
	ATOM_CONNECTOW_DEVICE_TAG_WECOWD **wecowd)
{
	ATOM_COMMON_WECOWD_HEADEW *headew;
	uint32_t offset;

	offset = we16_to_cpu(object->usWecowdOffset)
			+ bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(ATOM_COMMON_WECOWD_HEADEW, offset);

		if (!headew)
			wetuwn BP_WESUWT_BADBIOSTABWE;

		offset += headew->ucWecowdSize;

		if (WAST_WECOWD_TYPE == headew->ucWecowdType ||
			!headew->ucWecowdSize)
			bweak;

		if (ATOM_CONNECTOW_DEVICE_TAG_WECOWD_TYPE !=
			headew->ucWecowdType)
			continue;

		if (sizeof(ATOM_CONNECTOW_DEVICE_TAG) > headew->ucWecowdSize)
			continue;

		*wecowd = (ATOM_CONNECTOW_DEVICE_TAG_WECOWD *) headew;
		wetuwn BP_WESUWT_OK;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt bios_pawsew_get_device_tag(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id connectow_object_id,
	uint32_t device_tag_index,
	stwuct connectow_device_tag_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_CONNECTOW_DEVICE_TAG_WECOWD *wecowd = NUWW;
	ATOM_CONNECTOW_DEVICE_TAG *device_tag;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	/* getBiosObject wiww wetuwn MXM object */
	object = get_bios_object(bp, connectow_object_id);

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object id */
		wetuwn BP_WESUWT_BADINPUT;
	}

	if (bios_pawsew_get_device_tag_wecowd(bp, object, &wecowd)
		!= BP_WESUWT_OK)
		wetuwn BP_WESUWT_NOWECOWD;

	if (device_tag_index >= wecowd->ucNumbewOfDevice)
		wetuwn BP_WESUWT_NOWECOWD;

	device_tag = &wecowd->asDeviceTag[device_tag_index];

	info->acpi_device = we32_to_cpu(device_tag->uwACPIDeviceEnum);
	info->dev_id =
		device_type_fwom_device_id(we16_to_cpu(device_tag->usDeviceID));

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_fiwmwawe_info_v1_4(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);
static enum bp_wesuwt get_fiwmwawe_info_v2_1(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);
static enum bp_wesuwt get_fiwmwawe_info_v2_2(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);

static enum bp_wesuwt bios_pawsew_get_fiwmwawe_info(
	stwuct dc_bios *dcb,
	stwuct dc_fiwmwawe_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_BADBIOSTABWE;
	ATOM_COMMON_TABWE_HEADEW *headew;
	stwuct atom_data_wevision wevision;

	if (info && DATA_TABWES(FiwmwaweInfo)) {
		headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW,
			DATA_TABWES(FiwmwaweInfo));
		get_atom_data_tabwe_wevision(headew, &wevision);
		switch (wevision.majow) {
		case 1:
			switch (wevision.minow) {
			case 4:
				wesuwt = get_fiwmwawe_info_v1_4(bp, info);
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case 2:
			switch (wevision.minow) {
			case 1:
				wesuwt = get_fiwmwawe_info_v2_1(bp, info);
				bweak;
			case 2:
				wesuwt = get_fiwmwawe_info_v2_2(bp, info);
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt get_fiwmwawe_info_v1_4(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	ATOM_FIWMWAWE_INFO_V1_4 *fiwmwawe_info =
		GET_IMAGE(ATOM_FIWMWAWE_INFO_V1_4,
			DATA_TABWES(FiwmwaweInfo));

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!fiwmwawe_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	/* Pixew cwock pww infowmation. We need to convewt fwom 10KHz units into
	 * KHz units */
	info->pww_info.cwystaw_fwequency =
		we16_to_cpu(fiwmwawe_info->usWefewenceCwock) * 10;
	info->pww_info.min_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwawe_info->usMinPixewCwockPWW_Input) * 10;
	info->pww_info.max_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwawe_info->usMaxPixewCwockPWW_Input) * 10;
	info->pww_info.min_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwawe_info->uwMinPixewCwockPWW_Output) * 10;
	info->pww_info.max_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwawe_info->uwMaxPixewCwockPWW_Output) * 10;

	if (fiwmwawe_info->usFiwmwaweCapabiwity.sbfAccess.MemowyCwockSS_Suppowt)
		/* Since thewe is no infowmation on the SS, wepowt consewvative
		 * vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.memowy_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;

	if (fiwmwawe_info->usFiwmwaweCapabiwity.sbfAccess.EngineCwockSS_Suppowt)
		/* Since thewe is no infowmation on the SS,wepowt consewvative
		 * vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.engine_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_ss_info_v3_1(
	stwuct bios_pawsew *bp,
	uint32_t id,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info);

static enum bp_wesuwt get_fiwmwawe_info_v2_1(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	ATOM_FIWMWAWE_INFO_V2_1 *fiwmwaweInfo =
		GET_IMAGE(ATOM_FIWMWAWE_INFO_V2_1, DATA_TABWES(FiwmwaweInfo));
	stwuct spwead_spectwum_info intewnawSS;
	uint32_t index;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!fiwmwaweInfo)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	/* Pixew cwock pww infowmation. We need to convewt fwom 10KHz units into
	 * KHz units */
	info->pww_info.cwystaw_fwequency =
		we16_to_cpu(fiwmwaweInfo->usCoweWefewenceCwock) * 10;
	info->pww_info.min_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwaweInfo->usMinPixewCwockPWW_Input) * 10;
	info->pww_info.max_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwaweInfo->usMaxPixewCwockPWW_Input) * 10;
	info->pww_info.min_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwaweInfo->uwMinPixewCwockPWW_Output) * 10;
	info->pww_info.max_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwaweInfo->uwMaxPixewCwockPWW_Output) * 10;
	info->defauwt_dispway_engine_pww_fwequency =
		we32_to_cpu(fiwmwaweInfo->uwDefauwtDispEngineCwkFweq) * 10;
	info->extewnaw_cwock_souwce_fwequency_fow_dp =
		we16_to_cpu(fiwmwaweInfo->usUniphyDPModeExtCwkFweq) * 10;
	info->min_awwowed_bw_wevew = fiwmwaweInfo->ucMinAwwowedBW_Wevew;

	/* Thewe shouwd be onwy one entwy in the SS info tabwe fow Memowy Cwock
	 */
	index = 0;
	if (fiwmwaweInfo->usFiwmwaweCapabiwity.sbfAccess.MemowyCwockSS_Suppowt)
		/* Since thewe is no infowmation fow extewnaw SS, wepowt
		 *  consewvative vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.memowy_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;
	ewse if (get_ss_info_v3_1(bp,
		ASIC_INTEWNAW_MEMOWY_SS, index, &intewnawSS) == BP_WESUWT_OK) {
		if (intewnawSS.spwead_spectwum_pewcentage) {
			info->featuwe.memowy_cwk_ss_pewcentage =
				intewnawSS.spwead_spectwum_pewcentage;
			if (intewnawSS.type.CENTEW_MODE) {
				/* if it is centewmode, the exact SS Pewcentage
				 * wiww be wound up of hawf of the pewcentage
				 * wepowted in the SS tabwe */
				++info->featuwe.memowy_cwk_ss_pewcentage;
				info->featuwe.memowy_cwk_ss_pewcentage /= 2;
			}
		}
	}

	/* Thewe shouwd be onwy one entwy in the SS info tabwe fow Engine Cwock
	 */
	index = 1;
	if (fiwmwaweInfo->usFiwmwaweCapabiwity.sbfAccess.EngineCwockSS_Suppowt)
		/* Since thewe is no infowmation fow extewnaw SS, wepowt
		 * consewvative vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.engine_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;
	ewse if (get_ss_info_v3_1(bp,
		ASIC_INTEWNAW_ENGINE_SS, index, &intewnawSS) == BP_WESUWT_OK) {
		if (intewnawSS.spwead_spectwum_pewcentage) {
			info->featuwe.engine_cwk_ss_pewcentage =
				intewnawSS.spwead_spectwum_pewcentage;
			if (intewnawSS.type.CENTEW_MODE) {
				/* if it is centewmode, the exact SS Pewcentage
				 * wiww be wound up of hawf of the pewcentage
				 * wepowted in the SS tabwe */
				++info->featuwe.engine_cwk_ss_pewcentage;
				info->featuwe.engine_cwk_ss_pewcentage /= 2;
			}
		}
	}

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_fiwmwawe_info_v2_2(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	ATOM_FIWMWAWE_INFO_V2_2 *fiwmwawe_info;
	stwuct spwead_spectwum_info intewnaw_ss;
	uint32_t index;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	fiwmwawe_info = GET_IMAGE(ATOM_FIWMWAWE_INFO_V2_2,
		DATA_TABWES(FiwmwaweInfo));

	if (!fiwmwawe_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	/* Pixew cwock pww infowmation. We need to convewt fwom 10KHz units into
	 * KHz units */
	info->pww_info.cwystaw_fwequency =
		we16_to_cpu(fiwmwawe_info->usCoweWefewenceCwock) * 10;
	info->pww_info.min_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwawe_info->usMinPixewCwockPWW_Input) * 10;
	info->pww_info.max_input_pxw_cwk_pww_fwequency =
		we16_to_cpu(fiwmwawe_info->usMaxPixewCwockPWW_Input) * 10;
	info->pww_info.min_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwawe_info->uwMinPixewCwockPWW_Output) * 10;
	info->pww_info.max_output_pxw_cwk_pww_fwequency =
		we32_to_cpu(fiwmwawe_info->uwMaxPixewCwockPWW_Output) * 10;
	info->defauwt_dispway_engine_pww_fwequency =
		we32_to_cpu(fiwmwawe_info->uwDefauwtDispEngineCwkFweq) * 10;
	info->extewnaw_cwock_souwce_fwequency_fow_dp =
		we16_to_cpu(fiwmwawe_info->usUniphyDPModeExtCwkFweq) * 10;

	/* Thewe shouwd be onwy one entwy in the SS info tabwe fow Memowy Cwock
	 */
	index = 0;
	if (fiwmwawe_info->usFiwmwaweCapabiwity.sbfAccess.MemowyCwockSS_Suppowt)
		/* Since thewe is no infowmation fow extewnaw SS, wepowt
		 *  consewvative vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.memowy_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;
	ewse if (get_ss_info_v3_1(bp,
			ASIC_INTEWNAW_MEMOWY_SS, index, &intewnaw_ss) == BP_WESUWT_OK) {
		if (intewnaw_ss.spwead_spectwum_pewcentage) {
			info->featuwe.memowy_cwk_ss_pewcentage =
					intewnaw_ss.spwead_spectwum_pewcentage;
			if (intewnaw_ss.type.CENTEW_MODE) {
				/* if it is centewmode, the exact SS Pewcentage
				 * wiww be wound up of hawf of the pewcentage
				 * wepowted in the SS tabwe */
				++info->featuwe.memowy_cwk_ss_pewcentage;
				info->featuwe.memowy_cwk_ss_pewcentage /= 2;
			}
		}
	}

	/* Thewe shouwd be onwy one entwy in the SS info tabwe fow Engine Cwock
	 */
	index = 1;
	if (fiwmwawe_info->usFiwmwaweCapabiwity.sbfAccess.EngineCwockSS_Suppowt)
		/* Since thewe is no infowmation fow extewnaw SS, wepowt
		 * consewvative vawue 3% fow bandwidth cawcuwation */
		/* unit of 0.01% */
		info->featuwe.engine_cwk_ss_pewcentage = THWEE_PEWCENT_OF_10000;
	ewse if (get_ss_info_v3_1(bp,
			ASIC_INTEWNAW_ENGINE_SS, index, &intewnaw_ss) == BP_WESUWT_OK) {
		if (intewnaw_ss.spwead_spectwum_pewcentage) {
			info->featuwe.engine_cwk_ss_pewcentage =
					intewnaw_ss.spwead_spectwum_pewcentage;
			if (intewnaw_ss.type.CENTEW_MODE) {
				/* if it is centewmode, the exact SS Pewcentage
				 * wiww be wound up of hawf of the pewcentage
				 * wepowted in the SS tabwe */
				++info->featuwe.engine_cwk_ss_pewcentage;
				info->featuwe.engine_cwk_ss_pewcentage /= 2;
			}
		}
	}

	/* Wemote Dispway */
	info->wemote_dispway_config = fiwmwawe_info->ucWemoteDispwayConfig;

	/* Is awwowed minimum BW wevew */
	info->min_awwowed_bw_wevew = fiwmwawe_info->ucMinAwwowedBW_Wevew;
	/* Used stawting fwom CI */
	info->smu_gpu_pww_output_fweq =
			(uint32_t) (we32_to_cpu(fiwmwawe_info->uwGPUPWW_OutputFweq) * 10);

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_ss_info_v3_1(
	stwuct bios_pawsew *bp,
	uint32_t id,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	ATOM_ASIC_INTEWNAW_SS_INFO_V3 *ss_tabwe_headew_incwude;
	ATOM_ASIC_SS_ASSIGNMENT_V3 *tbw;
	uint32_t tabwe_size;
	uint32_t i;
	uint32_t tabwe_index = 0;

	if (!ss_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	ss_tabwe_headew_incwude = ((ATOM_ASIC_INTEWNAW_SS_INFO_V3 *) bios_get_image(&bp->base,
				DATA_TABWES(ASIC_IntewnawSS_Info),
				stwuct_size(ss_tabwe_headew_incwude, asSpweadSpectwum, 1)));
	tabwe_size =
		(we16_to_cpu(ss_tabwe_headew_incwude->sHeadew.usStwuctuweSize)
				- sizeof(ATOM_COMMON_TABWE_HEADEW))
				/ sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3);

	tbw = (ATOM_ASIC_SS_ASSIGNMENT_V3 *)
				&ss_tabwe_headew_incwude->asSpweadSpectwum[0];

	memset(ss_info, 0, sizeof(stwuct spwead_spectwum_info));

	fow (i = 0; i < tabwe_size; i++) {
		if (tbw[i].ucCwockIndication != (uint8_t) id)
			continue;

		if (tabwe_index != index) {
			tabwe_index++;
			continue;
		}
		/* VBIOS intwoduced new defines fow Vewsion 3, same vawues as
		 *  befowe, so now use these new ones fow Vewsion 3.
		 * Shouwdn't affect fiewd VBIOS's V3 as define vawues awe stiww
		 *  same.
		 * #define SS_MODE_V3_CENTWE_SPWEAD_MASK                0x01
		 * #define SS_MODE_V3_EXTEWNAW_SS_MASK                  0x02

		 * Owd VBIOS defines:
		 * #define ATOM_SS_CENTWE_SPWEAD_MODE_MASK        0x00000001
		 * #define ATOM_EXTEWNAW_SS_MASK                  0x00000002
		 */

		if (SS_MODE_V3_EXTEWNAW_SS_MASK & tbw[i].ucSpweadSpectwumMode)
			ss_info->type.EXTEWNAW = twue;

		if (SS_MODE_V3_CENTWE_SPWEAD_MASK & tbw[i].ucSpweadSpectwumMode)
			ss_info->type.CENTEW_MODE = twue;

		/* Owdew VBIOS (in fiewd) awways pwovides SS pewcentage in 0.01%
		 * units set Dividew to 100 */
		ss_info->spwead_pewcentage_dividew = 100;

		/* #define SS_MODE_V3_PEWCENTAGE_DIV_BY_1000_MASK 0x10 */
		if (SS_MODE_V3_PEWCENTAGE_DIV_BY_1000_MASK
				& tbw[i].ucSpweadSpectwumMode)
			ss_info->spwead_pewcentage_dividew = 1000;

		ss_info->type.STEP_AND_DEWAY_INFO = fawse;
		/* convewt [10KHz] into [KHz] */
		ss_info->tawget_cwock_wange =
				we32_to_cpu(tbw[i].uwTawgetCwockWange) * 10;
		ss_info->spwead_spectwum_pewcentage =
				(uint32_t)we16_to_cpu(tbw[i].usSpweadSpectwumPewcentage);
		ss_info->spwead_spectwum_wange =
				(uint32_t)(we16_to_cpu(tbw[i].usSpweadWateIn10Hz) * 10);

		wetuwn BP_WESUWT_OK;
	}
	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt bios_pawsew_twansmittew_contwow(
	stwuct dc_bios *dcb,
	stwuct bp_twansmittew_contwow *cntw)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.twansmittew_contwow)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.twansmittew_contwow(bp, cntw);
}

static enum bp_wesuwt bios_pawsew_encodew_contwow(
	stwuct dc_bios *dcb,
	stwuct bp_encodew_contwow *cntw)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.dig_encodew_contwow)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.dig_encodew_contwow(bp, cntw);
}

static enum bp_wesuwt bios_pawsew_adjust_pixew_cwock(
	stwuct dc_bios *dcb,
	stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.adjust_dispway_pww)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.adjust_dispway_pww(bp, bp_pawams);
}

static enum bp_wesuwt bios_pawsew_set_pixew_cwock(
	stwuct dc_bios *dcb,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.set_pixew_cwock)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.set_pixew_cwock(bp, bp_pawams);
}

static enum bp_wesuwt bios_pawsew_set_dce_cwock(
	stwuct dc_bios *dcb,
	stwuct bp_set_dce_cwock_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.set_dce_cwock)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.set_dce_cwock(bp, bp_pawams);
}

static enum bp_wesuwt bios_pawsew_enabwe_spwead_spectwum_on_ppww(
	stwuct dc_bios *dcb,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww(
			bp, bp_pawams, enabwe);

}

static enum bp_wesuwt bios_pawsew_pwogwam_cwtc_timing(
	stwuct dc_bios *dcb,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.set_cwtc_timing)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.set_cwtc_timing(bp, bp_pawams);
}

static enum bp_wesuwt bios_pawsew_pwogwam_dispway_engine_pww(
	stwuct dc_bios *dcb,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.pwogwam_cwock)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.pwogwam_cwock(bp, bp_pawams);

}


static enum bp_wesuwt bios_pawsew_enabwe_cwtc(
	stwuct dc_bios *dcb,
	enum contwowwew_id id,
	boow enabwe)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.enabwe_cwtc)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.enabwe_cwtc(bp, id, enabwe);
}

static enum bp_wesuwt bios_pawsew_enabwe_disp_powew_gating(
	stwuct dc_bios *dcb,
	enum contwowwew_id contwowwew_id,
	enum bp_pipe_contwow_action action)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.enabwe_disp_powew_gating)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.enabwe_disp_powew_gating(bp, contwowwew_id,
		action);
}

static boow bios_pawsew_is_device_id_suppowted(
	stwuct dc_bios *dcb,
	stwuct device_id id)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	uint32_t mask = get_suppowt_mask_fow_device_id(id);

	wetuwn (we16_to_cpu(bp->object_info_tbw.v1_1->usDeviceSuppowt) & mask) != 0;
}

static ATOM_HPD_INT_WECOWD *get_hpd_wecowd(stwuct bios_pawsew *bp,
	ATOM_OBJECT *object)
{
	ATOM_COMMON_WECOWD_HEADEW *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = we16_to_cpu(object->usWecowdOffset)
			+ bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(ATOM_COMMON_WECOWD_HEADEW, offset);

		if (!headew)
			wetuwn NUWW;

		if (WAST_WECOWD_TYPE == headew->ucWecowdType ||
			!headew->ucWecowdSize)
			bweak;

		if (ATOM_HPD_INT_WECOWD_TYPE == headew->ucWecowdType
			&& sizeof(ATOM_HPD_INT_WECOWD) <= headew->ucWecowdSize)
			wetuwn (ATOM_HPD_INT_WECOWD *) headew;

		offset += headew->ucWecowdSize;
	}

	wetuwn NUWW;
}

static enum bp_wesuwt get_ss_info_fwom_ss_info_tabwe(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *ss_info);
static enum bp_wesuwt get_ss_info_fwom_tbw(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *ss_info);
/**
 * bios_pawsew_get_spwead_spectwum_info
 * Get spwead spectwum infowmation fwom the ASIC_IntewnawSS_Info(vew 2.1 ow
 * vew 3.1) ow SS_Info tabwe fwom the VBIOS. Cuwwentwy ASIC_IntewnawSS_Info
 * vew 2.1 can co-exist with SS_Info tabwe. Expect ASIC_IntewnawSS_Info vew 3.1,
 * thewe is onwy one entwy fow each signaw /ss id.  Howevew, thewe is
 * no pwanning of suppowting muwtipwe spwead Spwectum entwy fow EvewGween
 * @dcb:     pointew to the DC BIOS
 * @signaw:  ASSignawType to be convewted to info index
 * @index:   numbew of entwies that match the convewted info index
 * @ss_info: spwectwum infowmation stwuctuwe,
 * wetuwn:   Bios pawsew wesuwt code
 */
static enum bp_wesuwt bios_pawsew_get_spwead_spectwum_info(
	stwuct dc_bios *dcb,
	enum as_signaw_type signaw,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	uint32_t cwk_id_ss = 0;
	ATOM_COMMON_TABWE_HEADEW *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!ss_info) /* check fow bad input */
		wetuwn BP_WESUWT_BADINPUT;
	/* signaw twanswation */
	cwk_id_ss = signaw_to_ss_id(signaw);

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		if (!index)
			wetuwn get_ss_info_fwom_ss_info_tabwe(bp, cwk_id_ss,
				ss_info);

	headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW,
		DATA_TABWES(ASIC_IntewnawSS_Info));
	get_atom_data_tabwe_wevision(headew, &tbw_wevision);

	switch (tbw_wevision.majow) {
	case 2:
		switch (tbw_wevision.minow) {
		case 1:
			/* thewe can not be mowe then one entwy fow Intewnaw
			 * SS Info tabwe vewsion 2.1 */
			if (!index)
				wetuwn get_ss_info_fwom_tbw(bp, cwk_id_ss,
						ss_info);
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	case 3:
		switch (tbw_wevision.minow) {
		case 1:
			wetuwn get_ss_info_v3_1(bp, cwk_id_ss, index, ss_info);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	/* thewe can not be mowe then one entwy fow SS Info tabwe */
	wetuwn wesuwt;
}

static enum bp_wesuwt get_ss_info_fwom_intewnaw_ss_info_tbw_V2_1(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *info);

/**
 * get_ss_info_fwom_tbw
 * Get spwead spwectwum infowmation fwom the ASIC_IntewnawSS_Info Vew 2.1 ow
 * SS_Info tabwe fwom the VBIOS
 * Thewe can not be mowe than 1 entwy fow  ASIC_IntewnawSS_Info Vew 2.1 ow
 * SS_Info.
 *
 * @bp:      pointew to the BIOS pawsew
 * @id:      spwead spwectwum info index
 * @ss_info: spwectwum infowmation stwuctuwe,
 * wetuwn:   BIOS pawsew wesuwt code
 */
static enum bp_wesuwt get_ss_info_fwom_tbw(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *ss_info)
{
	if (!ss_info) /* check fow bad input, if ss_info is not NUWW */
		wetuwn BP_WESUWT_BADINPUT;
	/* fow SS_Info tabwe onwy suppowt DP and WVDS */
	if (id == ASIC_INTEWNAW_SS_ON_DP || id == ASIC_INTEWNAW_SS_ON_WVDS)
		wetuwn get_ss_info_fwom_ss_info_tabwe(bp, id, ss_info);
	ewse
		wetuwn get_ss_info_fwom_intewnaw_ss_info_tbw_V2_1(bp, id,
			ss_info);
}

/**
 * get_ss_info_fwom_intewnaw_ss_info_tbw_V2_1
 * Get spwead spwectwum infowmation fwom the ASIC_IntewnawSS_Info tabwe Vew 2.1
 * fwom the VBIOS
 * Thewe wiww not be muwtipwe entwy fow Vew 2.1
 *
 * @bp:    pointew to the Bios pawsew
 * @id:    spwead spwectwum info index
 * @info:  spwectwum infowmation stwuctuwe,
 * wetuwn: Bios pawsew wesuwt code
 */
static enum bp_wesuwt get_ss_info_fwom_intewnaw_ss_info_tbw_V2_1(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	ATOM_ASIC_INTEWNAW_SS_INFO_V2 *headew;
	ATOM_ASIC_SS_ASSIGNMENT_V2 *tbw;
	uint32_t tbw_size, i;

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		wetuwn wesuwt;

	headew = ((ATOM_ASIC_INTEWNAW_SS_INFO_V2 *) bios_get_image(
				&bp->base,
				DATA_TABWES(ASIC_IntewnawSS_Info),
				stwuct_size(headew, asSpweadSpectwum, 1)));

	memset(info, 0, sizeof(stwuct spwead_spectwum_info));

	tbw_size = (we16_to_cpu(headew->sHeadew.usStwuctuweSize)
			- sizeof(ATOM_COMMON_TABWE_HEADEW))
					/ sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2);

	tbw = (ATOM_ASIC_SS_ASSIGNMENT_V2 *)
					&(headew->asSpweadSpectwum[0]);
	fow (i = 0; i < tbw_size; i++) {
		wesuwt = BP_WESUWT_NOWECOWD;

		if (tbw[i].ucCwockIndication != (uint8_t)id)
			continue;

		if (ATOM_EXTEWNAW_SS_MASK
			& tbw[i].ucSpweadSpectwumMode) {
			info->type.EXTEWNAW = twue;
		}
		if (ATOM_SS_CENTWE_SPWEAD_MODE_MASK
			& tbw[i].ucSpweadSpectwumMode) {
			info->type.CENTEW_MODE = twue;
		}
		info->type.STEP_AND_DEWAY_INFO = fawse;
		/* convewt [10KHz] into [KHz] */
		info->tawget_cwock_wange =
			we32_to_cpu(tbw[i].uwTawgetCwockWange) * 10;
		info->spwead_spectwum_pewcentage =
			(uint32_t)we16_to_cpu(tbw[i].usSpweadSpectwumPewcentage);
		info->spwead_spectwum_wange =
			(uint32_t)(we16_to_cpu(tbw[i].usSpweadWateIn10Hz) * 10);
		wesuwt = BP_WESUWT_OK;
		bweak;
	}

	wetuwn wesuwt;

}

/**
 * get_ss_info_fwom_ss_info_tabwe
 * Get spwead spwectwum infowmation fwom the SS_Info tabwe fwom the VBIOS
 * if the pointew to info is NUWW, indicate the cawwew what to know the numbew
 * of entwies that matches the id
 * fow, the SS_Info tabwe, thewe shouwd not be mowe than 1 entwy match.
 *
 * @bp:      pointew to the Bios pawsew
 * @id:      spwead spwectwum id
 * @ss_info: spwectwum infowmation stwuctuwe,
 * wetuwn:   Bios pawsew wesuwt code
 */
static enum bp_wesuwt get_ss_info_fwom_ss_info_tabwe(
	stwuct bios_pawsew *bp,
	uint32_t id,
	stwuct spwead_spectwum_info *ss_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	ATOM_SPWEAD_SPECTWUM_INFO *tbw;
	ATOM_COMMON_TABWE_HEADEW *headew;
	uint32_t tabwe_size;
	uint32_t i;
	uint32_t id_wocaw = SS_ID_UNKNOWN;
	stwuct atom_data_wevision wevision;

	/* exist of the SS_Info tabwe */
	/* check fow bad input, pSSinfo can not be NUWW */
	if (!DATA_TABWES(SS_Info) || !ss_info)
		wetuwn wesuwt;

	headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW, DATA_TABWES(SS_Info));
	get_atom_data_tabwe_wevision(headew, &wevision);

	tbw = GET_IMAGE(ATOM_SPWEAD_SPECTWUM_INFO, DATA_TABWES(SS_Info));

	if (1 != wevision.majow || 2 > wevision.minow)
		wetuwn wesuwt;

	/* have to convewt fwom Intewnaw_SS fowmat to SS_Info fowmat */
	switch (id) {
	case ASIC_INTEWNAW_SS_ON_DP:
		id_wocaw = SS_ID_DP1;
		bweak;
	case ASIC_INTEWNAW_SS_ON_WVDS:
	{
		stwuct embedded_panew_info panew_info;

		if (bios_pawsew_get_embedded_panew_info(&bp->base, &panew_info)
				== BP_WESUWT_OK)
			id_wocaw = panew_info.ss_id;
		bweak;
	}
	defauwt:
		bweak;
	}

	if (id_wocaw == SS_ID_UNKNOWN)
		wetuwn wesuwt;

	tabwe_size = (we16_to_cpu(tbw->sHeadew.usStwuctuweSize) -
			sizeof(ATOM_COMMON_TABWE_HEADEW)) /
					sizeof(ATOM_SPWEAD_SPECTWUM_ASSIGNMENT);

	fow (i = 0; i < tabwe_size; i++) {
		if (id_wocaw != (uint32_t)tbw->asSS_Info[i].ucSS_Id)
			continue;

		memset(ss_info, 0, sizeof(stwuct spwead_spectwum_info));

		if (ATOM_EXTEWNAW_SS_MASK &
				tbw->asSS_Info[i].ucSpweadSpectwumType)
			ss_info->type.EXTEWNAW = twue;

		if (ATOM_SS_CENTWE_SPWEAD_MODE_MASK &
				tbw->asSS_Info[i].ucSpweadSpectwumType)
			ss_info->type.CENTEW_MODE = twue;

		ss_info->type.STEP_AND_DEWAY_INFO = twue;
		ss_info->spwead_spectwum_pewcentage =
			(uint32_t)we16_to_cpu(tbw->asSS_Info[i].usSpweadSpectwumPewcentage);
		ss_info->step_and_deway_info.step = tbw->asSS_Info[i].ucSS_Step;
		ss_info->step_and_deway_info.deway =
			tbw->asSS_Info[i].ucSS_Deway;
		ss_info->step_and_deway_info.wecommended_wef_div =
			tbw->asSS_Info[i].ucWecommendedWef_Div;
		ss_info->spwead_spectwum_wange =
			(uint32_t)tbw->asSS_Info[i].ucSS_Wange * 10000;

		/* thewe wiww be onwy one entwy fow each dispway type in SS_info
		 * tabwe */
		wesuwt = BP_WESUWT_OK;
		bweak;
	}

	wetuwn wesuwt;
}
static enum bp_wesuwt get_embedded_panew_info_v1_2(
	stwuct bios_pawsew *bp,
	stwuct embedded_panew_info *info);
static enum bp_wesuwt get_embedded_panew_info_v1_3(
	stwuct bios_pawsew *bp,
	stwuct embedded_panew_info *info);

static enum bp_wesuwt bios_pawsew_get_embedded_panew_info(
	stwuct dc_bios *dcb,
	stwuct embedded_panew_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	ATOM_COMMON_TABWE_HEADEW *hdw;

	if (!DATA_TABWES(WCD_Info))
		wetuwn BP_WESUWT_FAIWUWE;

	hdw = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW, DATA_TABWES(WCD_Info));

	if (!hdw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	switch (hdw->ucTabweFowmatWevision) {
	case 1:
		switch (hdw->ucTabweContentWevision) {
		case 0:
		case 1:
		case 2:
			wetuwn get_embedded_panew_info_v1_2(bp, info);
		case 3:
			wetuwn get_embedded_panew_info_v1_3(bp, info);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

static enum bp_wesuwt get_embedded_panew_info_v1_2(
	stwuct bios_pawsew *bp,
	stwuct embedded_panew_info *info)
{
	ATOM_WVDS_INFO_V12 *wvds;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(WVDS_Info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	wvds =
		GET_IMAGE(ATOM_WVDS_INFO_V12, DATA_TABWES(WVDS_Info));

	if (!wvds)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (1 != wvds->sHeadew.ucTabweFowmatWevision
		|| 2 > wvds->sHeadew.ucTabweContentWevision)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	memset(info, 0, sizeof(stwuct embedded_panew_info));

	/* We need to convewt fwom 10KHz units into KHz units*/
	info->wcd_timing.pixew_cwk =
		we16_to_cpu(wvds->sWCDTiming.usPixCwk) * 10;
	/* usHActive does not incwude bowdews, accowding to VBIOS team*/
	info->wcd_timing.howizontaw_addwessabwe =
		we16_to_cpu(wvds->sWCDTiming.usHActive);
	/* usHBwanking_Time incwudes bowdews, so we shouwd weawwy be subtwacting
	 * bowdews duing this twanswation, but WVDS genewawwy*/
	/* doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now.  May need to wevisit if we evew have WVDS with bowdews*/
	info->wcd_timing.howizontaw_bwanking_time =
			we16_to_cpu(wvds->sWCDTiming.usHBwanking_Time);
	/* usVActive does not incwude bowdews, accowding to VBIOS team*/
	info->wcd_timing.vewticaw_addwessabwe =
			we16_to_cpu(wvds->sWCDTiming.usVActive);
	/* usVBwanking_Time incwudes bowdews, so we shouwd weawwy be subtwacting
	 * bowdews duing this twanswation, but WVDS genewawwy*/
	/* doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now. May need to wevisit if we evew have WVDS with bowdews*/
	info->wcd_timing.vewticaw_bwanking_time =
		we16_to_cpu(wvds->sWCDTiming.usVBwanking_Time);
	info->wcd_timing.howizontaw_sync_offset =
		we16_to_cpu(wvds->sWCDTiming.usHSyncOffset);
	info->wcd_timing.howizontaw_sync_width =
		we16_to_cpu(wvds->sWCDTiming.usHSyncWidth);
	info->wcd_timing.vewticaw_sync_offset =
		we16_to_cpu(wvds->sWCDTiming.usVSyncOffset);
	info->wcd_timing.vewticaw_sync_width =
		we16_to_cpu(wvds->sWCDTiming.usVSyncWidth);
	info->wcd_timing.howizontaw_bowdew = wvds->sWCDTiming.ucHBowdew;
	info->wcd_timing.vewticaw_bowdew = wvds->sWCDTiming.ucVBowdew;
	info->wcd_timing.misc_info.HOWIZONTAW_CUT_OFF =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.HowizontawCutOff;
	info->wcd_timing.misc_info.H_SYNC_POWAWITY =
		~(uint32_t)
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.HSyncPowawity;
	info->wcd_timing.misc_info.V_SYNC_POWAWITY =
		~(uint32_t)
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.VSyncPowawity;
	info->wcd_timing.misc_info.VEWTICAW_CUT_OFF =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.VewticawCutOff;
	info->wcd_timing.misc_info.H_WEPWICATION_BY2 =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.H_WepwicationBy2;
	info->wcd_timing.misc_info.V_WEPWICATION_BY2 =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.V_WepwicationBy2;
	info->wcd_timing.misc_info.COMPOSITE_SYNC =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.CompositeSync;
	info->wcd_timing.misc_info.INTEWWACE =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.Intewwace;
	info->wcd_timing.misc_info.DOUBWE_CWOCK =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.DoubweCwock;
	info->ss_id = wvds->ucSS_Id;

	{
		uint8_t ww = we16_to_cpu(wvds->usSuppowtedWefweshWate);
		/* Get minimum suppowted wefwesh wate*/
		if (SUPPOWTED_WCD_WEFWESHWATE_30Hz & ww)
			info->suppowted_ww.WEFWESH_WATE_30HZ = 1;
		ewse if (SUPPOWTED_WCD_WEFWESHWATE_40Hz & ww)
			info->suppowted_ww.WEFWESH_WATE_40HZ = 1;
		ewse if (SUPPOWTED_WCD_WEFWESHWATE_48Hz & ww)
			info->suppowted_ww.WEFWESH_WATE_48HZ = 1;
		ewse if (SUPPOWTED_WCD_WEFWESHWATE_50Hz & ww)
			info->suppowted_ww.WEFWESH_WATE_50HZ = 1;
		ewse if (SUPPOWTED_WCD_WEFWESHWATE_60Hz & ww)
			info->suppowted_ww.WEFWESH_WATE_60HZ = 1;
	}

	/*Dww panew suppowt can be wepowted by VBIOS*/
	if (WCDPANEW_CAP_DWW_SUPPOWTED
			& wvds->ucWCDPanew_SpeciawHandwingCap)
		info->dww_enabwed = 1;

	if (ATOM_PANEW_MISC_DUAW & wvds->ucWVDS_Misc)
		info->wcd_timing.misc_info.DOUBWE_CWOCK = twue;

	if (ATOM_PANEW_MISC_888WGB & wvds->ucWVDS_Misc)
		info->wcd_timing.misc_info.WGB888 = twue;

	info->wcd_timing.misc_info.GWEY_WEVEW =
		(uint32_t) (ATOM_PANEW_MISC_GWEY_WEVEW &
			wvds->ucWVDS_Misc) >> ATOM_PANEW_MISC_GWEY_WEVEW_SHIFT;

	if (ATOM_PANEW_MISC_SPATIAW & wvds->ucWVDS_Misc)
		info->wcd_timing.misc_info.SPATIAW = twue;

	if (ATOM_PANEW_MISC_TEMPOWAW & wvds->ucWVDS_Misc)
		info->wcd_timing.misc_info.TEMPOWAW = twue;

	if (ATOM_PANEW_MISC_API_ENABWED & wvds->ucWVDS_Misc)
		info->wcd_timing.misc_info.API_ENABWED = twue;

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_embedded_panew_info_v1_3(
	stwuct bios_pawsew *bp,
	stwuct embedded_panew_info *info)
{
	ATOM_WCD_INFO_V13 *wvds;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(WCD_Info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	wvds = GET_IMAGE(ATOM_WCD_INFO_V13, DATA_TABWES(WCD_Info));

	if (!wvds)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (!((1 == wvds->sHeadew.ucTabweFowmatWevision)
			&& (3 <= wvds->sHeadew.ucTabweContentWevision)))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	memset(info, 0, sizeof(stwuct embedded_panew_info));

	/* We need to convewt fwom 10KHz units into KHz units */
	info->wcd_timing.pixew_cwk =
			we16_to_cpu(wvds->sWCDTiming.usPixCwk) * 10;
	/* usHActive does not incwude bowdews, accowding to VBIOS team */
	info->wcd_timing.howizontaw_addwessabwe =
			we16_to_cpu(wvds->sWCDTiming.usHActive);
	/* usHBwanking_Time incwudes bowdews, so we shouwd weawwy be subtwacting
	 * bowdews duing this twanswation, but WVDS genewawwy*/
	/* doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now.  May need to wevisit if we evew have WVDS with bowdews*/
	info->wcd_timing.howizontaw_bwanking_time =
		we16_to_cpu(wvds->sWCDTiming.usHBwanking_Time);
	/* usVActive does not incwude bowdews, accowding to VBIOS team*/
	info->wcd_timing.vewticaw_addwessabwe =
		we16_to_cpu(wvds->sWCDTiming.usVActive);
	/* usVBwanking_Time incwudes bowdews, so we shouwd weawwy be subtwacting
	 * bowdews duing this twanswation, but WVDS genewawwy*/
	/* doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now. May need to wevisit if we evew have WVDS with bowdews*/
	info->wcd_timing.vewticaw_bwanking_time =
		we16_to_cpu(wvds->sWCDTiming.usVBwanking_Time);
	info->wcd_timing.howizontaw_sync_offset =
		we16_to_cpu(wvds->sWCDTiming.usHSyncOffset);
	info->wcd_timing.howizontaw_sync_width =
		we16_to_cpu(wvds->sWCDTiming.usHSyncWidth);
	info->wcd_timing.vewticaw_sync_offset =
		we16_to_cpu(wvds->sWCDTiming.usVSyncOffset);
	info->wcd_timing.vewticaw_sync_width =
		we16_to_cpu(wvds->sWCDTiming.usVSyncWidth);
	info->wcd_timing.howizontaw_bowdew = wvds->sWCDTiming.ucHBowdew;
	info->wcd_timing.vewticaw_bowdew = wvds->sWCDTiming.ucVBowdew;
	info->wcd_timing.misc_info.HOWIZONTAW_CUT_OFF =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.HowizontawCutOff;
	info->wcd_timing.misc_info.H_SYNC_POWAWITY =
		~(uint32_t)
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.HSyncPowawity;
	info->wcd_timing.misc_info.V_SYNC_POWAWITY =
		~(uint32_t)
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.VSyncPowawity;
	info->wcd_timing.misc_info.VEWTICAW_CUT_OFF =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.VewticawCutOff;
	info->wcd_timing.misc_info.H_WEPWICATION_BY2 =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.H_WepwicationBy2;
	info->wcd_timing.misc_info.V_WEPWICATION_BY2 =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.V_WepwicationBy2;
	info->wcd_timing.misc_info.COMPOSITE_SYNC =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.CompositeSync;
	info->wcd_timing.misc_info.INTEWWACE =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.Intewwace;
	info->wcd_timing.misc_info.DOUBWE_CWOCK =
		wvds->sWCDTiming.susModeMiscInfo.sbfAccess.DoubweCwock;
	info->ss_id = wvds->ucSS_Id;

	/* Dww panew suppowt can be wepowted by VBIOS*/
	if (WCDPANEW_CAP_V13_DWW_SUPPOWTED
			& wvds->ucWCDPanew_SpeciawHandwingCap)
		info->dww_enabwed = 1;

	/* Get suppowted wefwesh wate*/
	if (info->dww_enabwed == 1) {
		uint8_t min_ww =
				wvds->sWefweshWateSuppowt.ucMinWefweshWateFowDWW;
		uint8_t ww = wvds->sWefweshWateSuppowt.ucSuppowtedWefweshWate;

		if (min_ww != 0) {
			if (SUPPOWTED_WCD_WEFWESHWATE_30Hz & min_ww)
				info->suppowted_ww.WEFWESH_WATE_30HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_40Hz & min_ww)
				info->suppowted_ww.WEFWESH_WATE_40HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_48Hz & min_ww)
				info->suppowted_ww.WEFWESH_WATE_48HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_50Hz & min_ww)
				info->suppowted_ww.WEFWESH_WATE_50HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_60Hz & min_ww)
				info->suppowted_ww.WEFWESH_WATE_60HZ = 1;
		} ewse {
			if (SUPPOWTED_WCD_WEFWESHWATE_30Hz & ww)
				info->suppowted_ww.WEFWESH_WATE_30HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_40Hz & ww)
				info->suppowted_ww.WEFWESH_WATE_40HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_48Hz & ww)
				info->suppowted_ww.WEFWESH_WATE_48HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_50Hz & ww)
				info->suppowted_ww.WEFWESH_WATE_50HZ = 1;
			ewse if (SUPPOWTED_WCD_WEFWESHWATE_60Hz & ww)
				info->suppowted_ww.WEFWESH_WATE_60HZ = 1;
		}
	}

	if (ATOM_PANEW_MISC_V13_DUAW & wvds->ucWCD_Misc)
		info->wcd_timing.misc_info.DOUBWE_CWOCK = twue;

	if (ATOM_PANEW_MISC_V13_8BIT_PEW_COWOW & wvds->ucWCD_Misc)
		info->wcd_timing.misc_info.WGB888 = twue;

	info->wcd_timing.misc_info.GWEY_WEVEW =
			(uint32_t) (ATOM_PANEW_MISC_V13_GWEY_WEVEW &
				wvds->ucWCD_Misc) >> ATOM_PANEW_MISC_V13_GWEY_WEVEW_SHIFT;

	wetuwn BP_WESUWT_OK;
}

/**
 * bios_pawsew_get_encodew_cap_info - get encodew capabiwity
 *                                    infowmation of input object id
 *
 * @dcb:       pointew to the DC BIOS
 * @object_id: object id
 * @info:      encodew cap infowmation stwuctuwe
 *
 * wetuwn: Bios pawsew wesuwt code
 */
static enum bp_wesuwt bios_pawsew_get_encodew_cap_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id,
	stwuct bp_encodew_cap_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	ATOM_OBJECT *object;
	ATOM_ENCODEW_CAP_WECOWD_V2 *wecowd = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	object = get_bios_object(bp, object_id);

	if (!object)
		wetuwn BP_WESUWT_BADINPUT;

	wecowd = get_encodew_cap_wecowd(bp, object);
	if (!wecowd)
		wetuwn BP_WESUWT_NOWECOWD;

	info->DP_HBW2_EN = wecowd->usHBW2En;
	info->DP_HBW3_EN = wecowd->usHBW3En;
	info->HDMI_6GB_EN = wecowd->usHDMI6GEn;
	wetuwn BP_WESUWT_OK;
}

/**
 * get_encodew_cap_wecowd - Get encodew cap wecowd fow the object
 *
 * @bp:      pointew to the BIOS pawsew
 * @object:  ATOM object
 * wetuwn:   atom encodew cap wecowd
 * note:     seawch aww wecowds to find the ATOM_ENCODEW_CAP_WECOWD_V2 wecowd
 */
static ATOM_ENCODEW_CAP_WECOWD_V2 *get_encodew_cap_wecowd(
	stwuct bios_pawsew *bp,
	ATOM_OBJECT *object)
{
	ATOM_COMMON_WECOWD_HEADEW *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = we16_to_cpu(object->usWecowdOffset)
					+ bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(ATOM_COMMON_WECOWD_HEADEW, offset);

		if (!headew)
			wetuwn NUWW;

		offset += headew->ucWecowdSize;

		if (WAST_WECOWD_TYPE == headew->ucWecowdType ||
				!headew->ucWecowdSize)
			bweak;

		if (ATOM_ENCODEW_CAP_WECOWD_TYPE != headew->ucWecowdType)
			continue;

		if (sizeof(ATOM_ENCODEW_CAP_WECOWD_V2) <= headew->ucWecowdSize)
			wetuwn (ATOM_ENCODEW_CAP_WECOWD_V2 *)headew;
	}

	wetuwn NUWW;
}

static uint32_t get_ss_entwy_numbew(
	stwuct bios_pawsew *bp,
	uint32_t id);
static uint32_t get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_v2_1(
	stwuct bios_pawsew *bp,
	uint32_t id);
static uint32_t get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_V3_1(
	stwuct bios_pawsew *bp,
	uint32_t id);
static uint32_t get_ss_entwy_numbew_fwom_ss_info_tbw(
	stwuct bios_pawsew *bp,
	uint32_t id);

/**
 * bios_pawsew_get_ss_entwy_numbew
 * Get Numbew of SpweadSpectwum Entwy fwom the ASIC_IntewnawSS_Info tabwe fwom
 * the VBIOS that match the SSid (to be convewted fwom signaw)
 *
 * @dcb:    pointew to the DC BIOS
 * @signaw: ASSignawType to be convewted to SSid
 * wetuwn: numbew of SS Entwy that match the signaw
 */
static uint32_t bios_pawsew_get_ss_entwy_numbew(
	stwuct dc_bios *dcb,
	enum as_signaw_type signaw)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	uint32_t ss_id = 0;
	ATOM_COMMON_TABWE_HEADEW *headew;
	stwuct atom_data_wevision wevision;

	ss_id = signaw_to_ss_id(signaw);

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		wetuwn get_ss_entwy_numbew_fwom_ss_info_tbw(bp, ss_id);

	headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW,
			DATA_TABWES(ASIC_IntewnawSS_Info));
	get_atom_data_tabwe_wevision(headew, &wevision);

	switch (wevision.majow) {
	case 2:
		switch (wevision.minow) {
		case 1:
			wetuwn get_ss_entwy_numbew(bp, ss_id);
		defauwt:
			bweak;
		}
		bweak;
	case 3:
		switch (wevision.minow) {
		case 1:
			wetuwn
				get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_V3_1(
						bp, ss_id);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 * get_ss_entwy_numbew_fwom_ss_info_tbw
 * Get Numbew of spwead spectwum entwy fwom the SS_Info tabwe fwom the VBIOS.
 *
 * @bp:  pointew to the BIOS pawsew
 * @id:  spwead spectwum id
 * wetuwn: numbew of SS Entwy that match the id
 * note: Thewe can onwy be one entwy fow each id fow SS_Info Tabwe
 */
static uint32_t get_ss_entwy_numbew_fwom_ss_info_tbw(
	stwuct bios_pawsew *bp,
	uint32_t id)
{
	ATOM_SPWEAD_SPECTWUM_INFO *tbw;
	ATOM_COMMON_TABWE_HEADEW *headew;
	uint32_t tabwe_size;
	uint32_t i;
	uint32_t numbew = 0;
	uint32_t id_wocaw = SS_ID_UNKNOWN;
	stwuct atom_data_wevision wevision;

	/* SS_Info tabwe exist */
	if (!DATA_TABWES(SS_Info))
		wetuwn numbew;

	headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW,
			DATA_TABWES(SS_Info));
	get_atom_data_tabwe_wevision(headew, &wevision);

	tbw = GET_IMAGE(ATOM_SPWEAD_SPECTWUM_INFO,
			DATA_TABWES(SS_Info));

	if (1 != wevision.majow || 2 > wevision.minow)
		wetuwn numbew;

	/* have to convewt fwom Intewnaw_SS fowmat to SS_Info fowmat */
	switch (id) {
	case ASIC_INTEWNAW_SS_ON_DP:
		id_wocaw = SS_ID_DP1;
		bweak;
	case ASIC_INTEWNAW_SS_ON_WVDS: {
		stwuct embedded_panew_info panew_info;

		if (bios_pawsew_get_embedded_panew_info(&bp->base, &panew_info)
				== BP_WESUWT_OK)
			id_wocaw = panew_info.ss_id;
		bweak;
	}
	defauwt:
		bweak;
	}

	if (id_wocaw == SS_ID_UNKNOWN)
		wetuwn numbew;

	tabwe_size = (we16_to_cpu(tbw->sHeadew.usStwuctuweSize) -
			sizeof(ATOM_COMMON_TABWE_HEADEW)) /
					sizeof(ATOM_SPWEAD_SPECTWUM_ASSIGNMENT);

	fow (i = 0; i < tabwe_size; i++)
		if (id_wocaw == (uint32_t)tbw->asSS_Info[i].ucSS_Id) {
			numbew = 1;
			bweak;
		}

	wetuwn numbew;
}

/**
 * get_ss_entwy_numbew
 * Get spwead spwectwum infowmation fwom the ASIC_IntewnawSS_Info Vew 2.1 ow
 * SS_Info tabwe fwom the VBIOS
 * Thewe can not be mowe than 1 entwy fow  ASIC_IntewnawSS_Info Vew 2.1 ow
 * SS_Info.
 *
 * @bp:    pointew to the BIOS pawsew
 * @id:    spwead spwectwum info index
 * wetuwn: Bios pawsew wesuwt code
 */
static uint32_t get_ss_entwy_numbew(stwuct bios_pawsew *bp, uint32_t id)
{
	if (id == ASIC_INTEWNAW_SS_ON_DP || id == ASIC_INTEWNAW_SS_ON_WVDS)
		wetuwn get_ss_entwy_numbew_fwom_ss_info_tbw(bp, id);

	wetuwn get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_v2_1(bp, id);
}

/**
 * get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_v2_1
 * Get NUmbew of spwead spwectwum entwy fwom the ASIC_IntewnawSS_Info tabwe
 * Vew 2.1 fwom the VBIOS
 * Thewe wiww not be muwtipwe entwy fow Vew 2.1
 *
 * @bp:    pointew to the BIOS pawsew
 * @id:    spwead spwectwum info index
 * wetuwn: numbew of SS Entwy that match the id
 */
static uint32_t get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_v2_1(
	stwuct bios_pawsew *bp,
	uint32_t id)
{
	ATOM_ASIC_INTEWNAW_SS_INFO_V2 *headew_incwude;
	ATOM_ASIC_SS_ASSIGNMENT_V2 *tbw;
	uint32_t size;
	uint32_t i;

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		wetuwn 0;

	headew_incwude = ((ATOM_ASIC_INTEWNAW_SS_INFO_V2 *) bios_get_image(
				&bp->base,
				DATA_TABWES(ASIC_IntewnawSS_Info),
				stwuct_size(headew_incwude, asSpweadSpectwum, 1)));

	size = (we16_to_cpu(headew_incwude->sHeadew.usStwuctuweSize)
			- sizeof(ATOM_COMMON_TABWE_HEADEW))
						/ sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2);

	tbw = (ATOM_ASIC_SS_ASSIGNMENT_V2 *)
				&headew_incwude->asSpweadSpectwum[0];
	fow (i = 0; i < size; i++)
		if (tbw[i].ucCwockIndication == (uint8_t)id)
			wetuwn 1;

	wetuwn 0;
}
/**
 * get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_V3_1
 * Get Numbew of SpweadSpectwum Entwy fwom the ASIC_IntewnawSS_Info tabwe of
 * the VBIOS that matches id
 *
 * @bp:    pointew to the BIOS pawsew
 * @id:    spwead spwectwum id
 * wetuwn: numbew of SS Entwy that match the id
 */
static uint32_t get_ss_entwy_numbew_fwom_intewnaw_ss_info_tbw_V3_1(
	stwuct bios_pawsew *bp,
	uint32_t id)
{
	uint32_t numbew = 0;
	ATOM_ASIC_INTEWNAW_SS_INFO_V3 *headew_incwude;
	ATOM_ASIC_SS_ASSIGNMENT_V3 *tbw;
	uint32_t size;
	uint32_t i;

	if (!DATA_TABWES(ASIC_IntewnawSS_Info))
		wetuwn numbew;

	headew_incwude = ((ATOM_ASIC_INTEWNAW_SS_INFO_V3 *) bios_get_image(&bp->base,
				DATA_TABWES(ASIC_IntewnawSS_Info),
				stwuct_size(headew_incwude, asSpweadSpectwum, 1)));
	size = (we16_to_cpu(headew_incwude->sHeadew.usStwuctuweSize) -
			sizeof(ATOM_COMMON_TABWE_HEADEW)) /
					sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3);

	tbw = (ATOM_ASIC_SS_ASSIGNMENT_V3 *)
				&headew_incwude->asSpweadSpectwum[0];

	fow (i = 0; i < size; i++)
		if (tbw[i].ucCwockIndication == (uint8_t)id)
			numbew++;

	wetuwn numbew;
}

/**
 * bios_pawsew_get_gpio_pin_info
 * Get GpioPin infowmation of input gpio id
 *
 * @dcb:     pointew to the DC BIOS
 * @gpio_id: GPIO ID
 * @info:    GpioPin infowmation stwuctuwe
 * wetuwn:   Bios pawsew wesuwt code
 * note:
 *  to get the GPIO PIN INFO, we need:
 *  1. get the GPIO_ID fwom othew object tabwe, see GetHPDInfo()
 *  2. in DATA_TABWE.GPIO_Pin_WUT, seawch aww wecowds, to get the wegistewA
 *  offset/mask
 */
static enum bp_wesuwt bios_pawsew_get_gpio_pin_info(
	stwuct dc_bios *dcb,
	uint32_t gpio_id,
	stwuct gpio_pin_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	ATOM_GPIO_PIN_WUT *headew;
	uint32_t count = 0;
	uint32_t i = 0;

	if (!DATA_TABWES(GPIO_Pin_WUT))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	headew = ((ATOM_GPIO_PIN_WUT *) bios_get_image(&bp->base,
				DATA_TABWES(GPIO_Pin_WUT),
				stwuct_size(headew, asGPIO_Pin, 1)));
	if (!headew)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (sizeof(ATOM_COMMON_TABWE_HEADEW) + stwuct_size(headew, asGPIO_Pin, 1)
			> we16_to_cpu(headew->sHeadew.usStwuctuweSize))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (1 != headew->sHeadew.ucTabweContentWevision)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	count = (we16_to_cpu(headew->sHeadew.usStwuctuweSize)
			- sizeof(ATOM_COMMON_TABWE_HEADEW))
				/ sizeof(ATOM_GPIO_PIN_ASSIGNMENT);
	fow (i = 0; i < count; ++i) {
		if (headew->asGPIO_Pin[i].ucGPIO_ID != gpio_id)
			continue;

		info->offset =
			(uint32_t) we16_to_cpu(headew->asGPIO_Pin[i].usGpioPin_AIndex);
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask = (uint32_t) (1 <<
			headew->asGPIO_Pin[i].ucGpioPinBitShift);
		info->mask_y = info->mask + 2;
		info->mask_en = info->mask + 1;
		info->mask_mask = info->mask - 1;

		wetuwn BP_WESUWT_OK;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt get_gpio_i2c_info(stwuct bios_pawsew *bp,
	ATOM_I2C_WECOWD *wecowd,
	stwuct gwaphics_object_i2c_info *info)
{
	ATOM_GPIO_I2C_INFO *headew;
	uint32_t count = 0;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	/* get the GPIO_I2C info */
	if (!DATA_TABWES(GPIO_I2C_Info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	headew = GET_IMAGE(ATOM_GPIO_I2C_INFO, DATA_TABWES(GPIO_I2C_Info));
	if (!headew)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (sizeof(ATOM_COMMON_TABWE_HEADEW) + sizeof(ATOM_GPIO_I2C_ASSIGMENT)
			> we16_to_cpu(headew->sHeadew.usStwuctuweSize))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (1 != headew->sHeadew.ucTabweContentWevision)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	/* get data count */
	count = (we16_to_cpu(headew->sHeadew.usStwuctuweSize)
			- sizeof(ATOM_COMMON_TABWE_HEADEW))
				/ sizeof(ATOM_GPIO_I2C_ASSIGMENT);
	if (count < wecowd->sucI2cId.bfI2C_WineMux)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	/* get the GPIO_I2C_INFO */
	info->i2c_hw_assist = wecowd->sucI2cId.bfHW_Capabwe;
	info->i2c_wine = wecowd->sucI2cId.bfI2C_WineMux;
	info->i2c_engine_id = wecowd->sucI2cId.bfHW_EngineID;
	info->i2c_swave_addwess = wecowd->ucI2CAddw;

	info->gpio_info.cwk_mask_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usCwkMaskWegistewIndex);
	info->gpio_info.cwk_en_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usCwkEnWegistewIndex);
	info->gpio_info.cwk_y_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usCwkY_WegistewIndex);
	info->gpio_info.cwk_a_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usCwkA_WegistewIndex);
	info->gpio_info.data_mask_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usDataMaskWegistewIndex);
	info->gpio_info.data_en_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usDataEnWegistewIndex);
	info->gpio_info.data_y_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usDataY_WegistewIndex);
	info->gpio_info.data_a_wegistew_index =
			we16_to_cpu(headew->asGPIO_Info[info->i2c_wine].usDataA_WegistewIndex);

	info->gpio_info.cwk_mask_shift =
			headew->asGPIO_Info[info->i2c_wine].ucCwkMaskShift;
	info->gpio_info.cwk_en_shift =
			headew->asGPIO_Info[info->i2c_wine].ucCwkEnShift;
	info->gpio_info.cwk_y_shift =
			headew->asGPIO_Info[info->i2c_wine].ucCwkY_Shift;
	info->gpio_info.cwk_a_shift =
			headew->asGPIO_Info[info->i2c_wine].ucCwkA_Shift;
	info->gpio_info.data_mask_shift =
			headew->asGPIO_Info[info->i2c_wine].ucDataMaskShift;
	info->gpio_info.data_en_shift =
			headew->asGPIO_Info[info->i2c_wine].ucDataEnShift;
	info->gpio_info.data_y_shift =
			headew->asGPIO_Info[info->i2c_wine].ucDataY_Shift;
	info->gpio_info.data_a_shift =
			headew->asGPIO_Info[info->i2c_wine].ucDataA_Shift;

	wetuwn BP_WESUWT_OK;
}

static boow daw_gwaphics_object_id_is_vawid(stwuct gwaphics_object_id id)
{
	boow wc = twue;

	switch (id.type) {
	case OBJECT_TYPE_UNKNOWN:
		wc = fawse;
		bweak;
	case OBJECT_TYPE_GPU:
	case OBJECT_TYPE_ENGINE:
		/* do NOT check fow id.id == 0 */
		if (id.enum_id == ENUM_ID_UNKNOWN)
			wc = fawse;
		bweak;
	defauwt:
		if (id.id == 0 || id.enum_id == ENUM_ID_UNKNOWN)
			wc = fawse;
		bweak;
	}

	wetuwn wc;
}

static boow daw_gwaphics_object_id_is_equaw(
	stwuct gwaphics_object_id id1,
	stwuct gwaphics_object_id id2)
{
	if (fawse == daw_gwaphics_object_id_is_vawid(id1)) {
		dm_output_to_consowe(
		"%s: Wawning: compawing invawid object 'id1'!\n", __func__);
		wetuwn fawse;
	}

	if (fawse == daw_gwaphics_object_id_is_vawid(id2)) {
		dm_output_to_consowe(
		"%s: Wawning: compawing invawid object 'id2'!\n", __func__);
		wetuwn fawse;
	}

	if (id1.id == id2.id && id1.enum_id == id2.enum_id
		&& id1.type == id2.type)
		wetuwn twue;

	wetuwn fawse;
}

static ATOM_OBJECT *get_bios_object(stwuct bios_pawsew *bp,
	stwuct gwaphics_object_id id)
{
	uint32_t offset;
	ATOM_OBJECT_TABWE *tbw;
	uint32_t i;

	switch (id.type) {
	case OBJECT_TYPE_ENCODEW:
		offset = we16_to_cpu(bp->object_info_tbw.v1_1->usEncodewObjectTabweOffset);
		bweak;

	case OBJECT_TYPE_CONNECTOW:
		offset = we16_to_cpu(bp->object_info_tbw.v1_1->usConnectowObjectTabweOffset);
		bweak;

	case OBJECT_TYPE_WOUTEW:
		offset = we16_to_cpu(bp->object_info_tbw.v1_1->usWoutewObjectTabweOffset);
		bweak;

	case OBJECT_TYPE_GENEWIC:
		if (bp->object_info_tbw.wevision.minow < 3)
			wetuwn NUWW;
		offset = we16_to_cpu(bp->object_info_tbw.v1_3->usMiscObjectTabweOffset);
		bweak;

	defauwt:
		wetuwn NUWW;
	}

	offset += bp->object_info_tbw_offset;

	tbw = ((ATOM_OBJECT_TABWE *) bios_get_image(&bp->base, offset,
				stwuct_size(tbw, asObjects, 1)));
	if (!tbw)
		wetuwn NUWW;

	fow (i = 0; i < tbw->ucNumbewOfObjects; i++)
		if (daw_gwaphics_object_id_is_equaw(id,
				object_id_fwom_bios_object_id(
						we16_to_cpu(tbw->asObjects[i].usObjectID))))
			wetuwn &tbw->asObjects[i];

	wetuwn NUWW;
}

static uint32_t get_swc_obj_wist(stwuct bios_pawsew *bp, ATOM_OBJECT *object,
	uint16_t **id_wist)
{
	uint32_t offset;
	uint8_t *numbew;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object id */
		wetuwn 0;
	}

	offset = we16_to_cpu(object->usSwcDstTabweOffset)
					+ bp->object_info_tbw_offset;

	numbew = GET_IMAGE(uint8_t, offset);
	if (!numbew)
		wetuwn 0;

	offset += sizeof(uint8_t);
	*id_wist = (uint16_t *)bios_get_image(&bp->base, offset, *numbew * sizeof(uint16_t));

	if (!*id_wist)
		wetuwn 0;

	wetuwn *numbew;
}

static stwuct device_id device_type_fwom_device_id(uint16_t device_id)
{

	stwuct device_id wesuwt_device_id = {0};

	switch (device_id) {
	case ATOM_DEVICE_WCD1_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_WCD;
		wesuwt_device_id.enum_id = 1;
		bweak;

	case ATOM_DEVICE_WCD2_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_WCD;
		wesuwt_device_id.enum_id = 2;
		bweak;

	case ATOM_DEVICE_CWT1_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_CWT;
		wesuwt_device_id.enum_id = 1;
		bweak;

	case ATOM_DEVICE_CWT2_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_CWT;
		wesuwt_device_id.enum_id = 2;
		bweak;

	case ATOM_DEVICE_DFP1_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 1;
		bweak;

	case ATOM_DEVICE_DFP2_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 2;
		bweak;

	case ATOM_DEVICE_DFP3_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 3;
		bweak;

	case ATOM_DEVICE_DFP4_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 4;
		bweak;

	case ATOM_DEVICE_DFP5_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 5;
		bweak;

	case ATOM_DEVICE_DFP6_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 6;
		bweak;

	defauwt:
		BWEAK_TO_DEBUGGEW(); /* Invawid device Id */
		wesuwt_device_id.device_type = DEVICE_TYPE_UNKNOWN;
		wesuwt_device_id.enum_id = 0;
	}
	wetuwn wesuwt_device_id;
}

static void get_atom_data_tabwe_wevision(
	ATOM_COMMON_TABWE_HEADEW *atom_data_tbw,
	stwuct atom_data_wevision *tbw_wevision)
{
	if (!tbw_wevision)
		wetuwn;

	/* initiawize the wevision to 0 which is invawid wevision */
	tbw_wevision->majow = 0;
	tbw_wevision->minow = 0;

	if (!atom_data_tbw)
		wetuwn;

	tbw_wevision->majow =
			(uint32_t) GET_DATA_TABWE_MAJOW_WEVISION(atom_data_tbw);
	tbw_wevision->minow =
			(uint32_t) GET_DATA_TABWE_MINOW_WEVISION(atom_data_tbw);
}

static uint32_t signaw_to_ss_id(enum as_signaw_type signaw)
{
	uint32_t cwk_id_ss = 0;

	switch (signaw) {
	case AS_SIGNAW_TYPE_DVI:
		cwk_id_ss = ASIC_INTEWNAW_SS_ON_TMDS;
		bweak;
	case AS_SIGNAW_TYPE_HDMI:
		cwk_id_ss = ASIC_INTEWNAW_SS_ON_HDMI;
		bweak;
	case AS_SIGNAW_TYPE_WVDS:
		cwk_id_ss = ASIC_INTEWNAW_SS_ON_WVDS;
		bweak;
	case AS_SIGNAW_TYPE_DISPWAY_POWT:
		cwk_id_ss = ASIC_INTEWNAW_SS_ON_DP;
		bweak;
	case AS_SIGNAW_TYPE_GPU_PWW:
		cwk_id_ss = ASIC_INTEWNAW_GPUPWW_SS;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn cwk_id_ss;
}

static uint32_t get_suppowt_mask_fow_device_id(stwuct device_id device_id)
{
	enum daw_device_type device_type = device_id.device_type;
	uint32_t enum_id = device_id.enum_id;

	switch (device_type) {
	case DEVICE_TYPE_WCD:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DEVICE_WCD1_SUPPOWT;
		case 2:
			wetuwn ATOM_DEVICE_WCD2_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	case DEVICE_TYPE_CWT:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DEVICE_CWT1_SUPPOWT;
		case 2:
			wetuwn ATOM_DEVICE_CWT2_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	case DEVICE_TYPE_DFP:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DEVICE_DFP1_SUPPOWT;
		case 2:
			wetuwn ATOM_DEVICE_DFP2_SUPPOWT;
		case 3:
			wetuwn ATOM_DEVICE_DFP3_SUPPOWT;
		case 4:
			wetuwn ATOM_DEVICE_DFP4_SUPPOWT;
		case 5:
			wetuwn ATOM_DEVICE_DFP5_SUPPOWT;
		case 6:
			wetuwn ATOM_DEVICE_DFP6_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	case DEVICE_TYPE_CV:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DEVICE_CV_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	case DEVICE_TYPE_TV:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DEVICE_TV1_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	/* Unidentified device ID, wetuwn empty suppowt mask. */
	wetuwn 0;
}

/**
 * bios_pawsew_set_scwatch_cwiticaw_state - update cwiticaw state
 *                                          bit in VBIOS scwatch wegistew
 * @dcb:    pointew to the DC BIOS
 * @state:  set ow weset state
 */
static void bios_pawsew_set_scwatch_cwiticaw_state(
	stwuct dc_bios *dcb,
	boow state)
{
	bios_set_scwatch_cwiticaw_state(dcb, state);
}

/*
 * get_integwated_info_v8
 *
 * @bwief
 * Get V8 integwated BIOS infowmation
 *
 * @pawam
 * bios_pawsew *bp - [in]BIOS pawsew handwew to get mastew data tabwe
 * integwated_info *info - [out] stowe and output integwated info
 *
 * wetuwn:
 * enum bp_wesuwt - BP_WESUWT_OK if infowmation is avaiwabwe,
 *                  BP_WESUWT_BADBIOSTABWE othewwise.
 */
static enum bp_wesuwt get_integwated_info_v8(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	ATOM_INTEGWATED_SYSTEM_INFO_V1_8 *info_v8;
	uint32_t i;

	info_v8 = GET_IMAGE(ATOM_INTEGWATED_SYSTEM_INFO_V1_8,
			bp->mastew_data_tbw->WistOfDataTabwes.IntegwatedSystemInfo);

	if (info_v8 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;
	info->boot_up_engine_cwock = we32_to_cpu(info_v8->uwBootUpEngineCwock) * 10;
	info->dentist_vco_fweq = we32_to_cpu(info_v8->uwDentistVCOFweq) * 10;
	info->boot_up_uma_cwock = we32_to_cpu(info_v8->uwBootUpUMACwock) * 10;

	fow (i = 0; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->disp_cwk_vowtage[i].max_suppowted_cwk =
			we32_to_cpu(info_v8->sDISPCWK_Vowtage[i].
				    uwMaximumSuppowtedCWK) * 10;
		info->disp_cwk_vowtage[i].vowtage_index =
			we32_to_cpu(info_v8->sDISPCWK_Vowtage[i].uwVowtageIndex);
	}

	info->boot_up_weq_dispway_vectow =
		we32_to_cpu(info_v8->uwBootUpWeqDispwayVectow);
	info->gpu_cap_info =
		we32_to_cpu(info_v8->uwGPUCapInfo);

	/*
	 * system_config: Bit[0] = 0 : PCIE powew gating disabwed
	 *                       = 1 : PCIE powew gating enabwed
	 *                Bit[1] = 0 : DDW-PWW shut down disabwed
	 *                       = 1 : DDW-PWW shut down enabwed
	 *                Bit[2] = 0 : DDW-PWW powew down disabwed
	 *                       = 1 : DDW-PWW powew down enabwed
	 */
	info->system_config = we32_to_cpu(info_v8->uwSystemConfig);
	info->cpu_cap_info = we32_to_cpu(info_v8->uwCPUCapInfo);
	info->boot_up_nb_vowtage =
		we16_to_cpu(info_v8->usBootUpNBVowtage);
	info->ext_disp_conn_info_offset =
		we16_to_cpu(info_v8->usExtDispConnInfoOffset);
	info->memowy_type = info_v8->ucMemowyType;
	info->ma_channew_numbew = info_v8->ucUMAChannewNumbew;
	info->gmc_westowe_weset_time =
		we32_to_cpu(info_v8->uwGMCWestoweWesetTime);

	info->minimum_n_cwk =
		we32_to_cpu(info_v8->uwNbpStateNCwkFweq[0]);
	fow (i = 1; i < 4; ++i)
		info->minimum_n_cwk =
			info->minimum_n_cwk < we32_to_cpu(info_v8->uwNbpStateNCwkFweq[i]) ?
			info->minimum_n_cwk : we32_to_cpu(info_v8->uwNbpStateNCwkFweq[i]);

	info->idwe_n_cwk = we32_to_cpu(info_v8->uwIdweNCwk);
	info->ddw_dww_powew_up_time =
		we32_to_cpu(info_v8->uwDDW_DWW_PowewUpTime);
	info->ddw_pww_powew_up_time =
		we32_to_cpu(info_v8->uwDDW_PWW_PowewUpTime);
	info->pcie_cwk_ss_type = we16_to_cpu(info_v8->usPCIECwkSSType);
	info->wvds_ss_pewcentage =
		we16_to_cpu(info_v8->usWvdsSSPewcentage);
	info->wvds_sspwead_wate_in_10hz =
		we16_to_cpu(info_v8->usWvdsSSpweadWateIn10Hz);
	info->hdmi_ss_pewcentage =
		we16_to_cpu(info_v8->usHDMISSPewcentage);
	info->hdmi_sspwead_wate_in_10hz =
		we16_to_cpu(info_v8->usHDMISSpweadWateIn10Hz);
	info->dvi_ss_pewcentage =
		we16_to_cpu(info_v8->usDVISSPewcentage);
	info->dvi_sspwead_wate_in_10_hz =
		we16_to_cpu(info_v8->usDVISSpweadWateIn10Hz);

	info->max_wvds_pcwk_fweq_in_singwe_wink =
		we16_to_cpu(info_v8->usMaxWVDSPcwkFweqInSingweWink);
	info->wvds_misc = info_v8->ucWvdsMisc;
	info->wvds_pww_on_seq_dig_on_to_de_in_4ms =
		info_v8->ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
	info->wvds_pww_on_seq_de_to_vawy_bw_in_4ms =
		info_v8->ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
	info->wvds_pww_on_seq_vawy_bw_to_bwon_in_4ms =
		info_v8->ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
	info->wvds_pww_off_seq_vawy_bw_to_de_in4ms =
		info_v8->ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
	info->wvds_pww_off_seq_de_to_dig_on_in4ms =
		info_v8->ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
	info->wvds_pww_off_seq_bwon_to_vawy_bw_in_4ms =
		info_v8->ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
	info->wvds_off_to_on_deway_in_4ms =
		info_v8->ucWVDSOffToOnDeway_in4Ms;
	info->wvds_bit_depth_contwow_vaw =
		we32_to_cpu(info_v8->uwWCDBitDepthContwowVaw);

	fow (i = 0; i < NUMBEW_OF_AVAIWABWE_SCWK; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->avaiw_s_cwk[i].suppowted_s_cwk =
			we32_to_cpu(info_v8->sAvaiw_SCWK[i].uwSuppowtedSCWK) * 10;
		info->avaiw_s_cwk[i].vowtage_index =
			we16_to_cpu(info_v8->sAvaiw_SCWK[i].usVowtageIndex);
		info->avaiw_s_cwk[i].vowtage_id =
			we16_to_cpu(info_v8->sAvaiw_SCWK[i].usVowtageID);
	}

	fow (i = 0; i < NUMBEW_OF_UCHAW_FOW_GUID; ++i) {
		info->ext_disp_conn_info.gu_id[i] =
			info_v8->sExtDispConnInfo.ucGuid[i];
	}

	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; ++i) {
		info->ext_disp_conn_info.path[i].device_connectow_id =
			object_id_fwom_bios_object_id(
				we16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceConnectow));

		info->ext_disp_conn_info.path[i].ext_encodew_obj_id =
			object_id_fwom_bios_object_id(
				we16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usExtEncodewObjId));

		info->ext_disp_conn_info.path[i].device_tag =
			we16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceTag);
		info->ext_disp_conn_info.path[i].device_acpi_enum =
			we16_to_cpu(info_v8->sExtDispConnInfo.sPath[i].usDeviceACPIEnum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index =
			info_v8->sExtDispConnInfo.sPath[i].ucExtAUXDDCWutIndex;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index =
			info_v8->sExtDispConnInfo.sPath[i].ucExtHPDPINWutIndex;
		info->ext_disp_conn_info.path[i].channew_mapping.waw =
			info_v8->sExtDispConnInfo.sPath[i].ucChannewMapping;
	}
	info->ext_disp_conn_info.checksum =
		info_v8->sExtDispConnInfo.ucChecksum;

	wetuwn BP_WESUWT_OK;
}

/*
 * get_integwated_info_v8
 *
 * @bwief
 * Get V8 integwated BIOS infowmation
 *
 * @pawam
 * bios_pawsew *bp - [in]BIOS pawsew handwew to get mastew data tabwe
 * integwated_info *info - [out] stowe and output integwated info
 *
 * wetuwn:
 * enum bp_wesuwt - BP_WESUWT_OK if infowmation is avaiwabwe,
 *                  BP_WESUWT_BADBIOSTABWE othewwise.
 */
static enum bp_wesuwt get_integwated_info_v9(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	ATOM_INTEGWATED_SYSTEM_INFO_V1_9 *info_v9;
	uint32_t i;

	info_v9 = GET_IMAGE(ATOM_INTEGWATED_SYSTEM_INFO_V1_9,
			bp->mastew_data_tbw->WistOfDataTabwes.IntegwatedSystemInfo);

	if (!info_v9)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->boot_up_engine_cwock = we32_to_cpu(info_v9->uwBootUpEngineCwock) * 10;
	info->dentist_vco_fweq = we32_to_cpu(info_v9->uwDentistVCOFweq) * 10;
	info->boot_up_uma_cwock = we32_to_cpu(info_v9->uwBootUpUMACwock) * 10;

	fow (i = 0; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->disp_cwk_vowtage[i].max_suppowted_cwk =
			we32_to_cpu(info_v9->sDISPCWK_Vowtage[i].uwMaximumSuppowtedCWK) * 10;
		info->disp_cwk_vowtage[i].vowtage_index =
			we32_to_cpu(info_v9->sDISPCWK_Vowtage[i].uwVowtageIndex);
	}

	info->boot_up_weq_dispway_vectow =
		we32_to_cpu(info_v9->uwBootUpWeqDispwayVectow);
	info->gpu_cap_info = we32_to_cpu(info_v9->uwGPUCapInfo);

	/*
	 * system_config: Bit[0] = 0 : PCIE powew gating disabwed
	 *                       = 1 : PCIE powew gating enabwed
	 *                Bit[1] = 0 : DDW-PWW shut down disabwed
	 *                       = 1 : DDW-PWW shut down enabwed
	 *                Bit[2] = 0 : DDW-PWW powew down disabwed
	 *                       = 1 : DDW-PWW powew down enabwed
	 */
	info->system_config = we32_to_cpu(info_v9->uwSystemConfig);
	info->cpu_cap_info = we32_to_cpu(info_v9->uwCPUCapInfo);
	info->boot_up_nb_vowtage = we16_to_cpu(info_v9->usBootUpNBVowtage);
	info->ext_disp_conn_info_offset = we16_to_cpu(info_v9->usExtDispConnInfoOffset);
	info->memowy_type = info_v9->ucMemowyType;
	info->ma_channew_numbew = info_v9->ucUMAChannewNumbew;
	info->gmc_westowe_weset_time = we32_to_cpu(info_v9->uwGMCWestoweWesetTime);

	info->minimum_n_cwk = we32_to_cpu(info_v9->uwNbpStateNCwkFweq[0]);
	fow (i = 1; i < 4; ++i)
		info->minimum_n_cwk =
			info->minimum_n_cwk < we32_to_cpu(info_v9->uwNbpStateNCwkFweq[i]) ?
			info->minimum_n_cwk : we32_to_cpu(info_v9->uwNbpStateNCwkFweq[i]);

	info->idwe_n_cwk = we32_to_cpu(info_v9->uwIdweNCwk);
	info->ddw_dww_powew_up_time = we32_to_cpu(info_v9->uwDDW_DWW_PowewUpTime);
	info->ddw_pww_powew_up_time = we32_to_cpu(info_v9->uwDDW_PWW_PowewUpTime);
	info->pcie_cwk_ss_type = we16_to_cpu(info_v9->usPCIECwkSSType);
	info->wvds_ss_pewcentage = we16_to_cpu(info_v9->usWvdsSSPewcentage);
	info->wvds_sspwead_wate_in_10hz = we16_to_cpu(info_v9->usWvdsSSpweadWateIn10Hz);
	info->hdmi_ss_pewcentage = we16_to_cpu(info_v9->usHDMISSPewcentage);
	info->hdmi_sspwead_wate_in_10hz = we16_to_cpu(info_v9->usHDMISSpweadWateIn10Hz);
	info->dvi_ss_pewcentage = we16_to_cpu(info_v9->usDVISSPewcentage);
	info->dvi_sspwead_wate_in_10_hz = we16_to_cpu(info_v9->usDVISSpweadWateIn10Hz);

	info->max_wvds_pcwk_fweq_in_singwe_wink =
		we16_to_cpu(info_v9->usMaxWVDSPcwkFweqInSingweWink);
	info->wvds_misc = info_v9->ucWvdsMisc;
	info->wvds_pww_on_seq_dig_on_to_de_in_4ms =
		info_v9->ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
	info->wvds_pww_on_seq_de_to_vawy_bw_in_4ms =
		info_v9->ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
	info->wvds_pww_on_seq_vawy_bw_to_bwon_in_4ms =
		info_v9->ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
	info->wvds_pww_off_seq_vawy_bw_to_de_in4ms =
		info_v9->ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
	info->wvds_pww_off_seq_de_to_dig_on_in4ms =
		info_v9->ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
	info->wvds_pww_off_seq_bwon_to_vawy_bw_in_4ms =
		info_v9->ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
	info->wvds_off_to_on_deway_in_4ms =
		info_v9->ucWVDSOffToOnDeway_in4Ms;
	info->wvds_bit_depth_contwow_vaw =
		we32_to_cpu(info_v9->uwWCDBitDepthContwowVaw);

	fow (i = 0; i < NUMBEW_OF_AVAIWABWE_SCWK; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->avaiw_s_cwk[i].suppowted_s_cwk =
			we32_to_cpu(info_v9->sAvaiw_SCWK[i].uwSuppowtedSCWK) * 10;
		info->avaiw_s_cwk[i].vowtage_index =
			we16_to_cpu(info_v9->sAvaiw_SCWK[i].usVowtageIndex);
		info->avaiw_s_cwk[i].vowtage_id =
			we16_to_cpu(info_v9->sAvaiw_SCWK[i].usVowtageID);
	}

	fow (i = 0; i < NUMBEW_OF_UCHAW_FOW_GUID; ++i) {
		info->ext_disp_conn_info.gu_id[i] =
			info_v9->sExtDispConnInfo.ucGuid[i];
	}

	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; ++i) {
		info->ext_disp_conn_info.path[i].device_connectow_id =
			object_id_fwom_bios_object_id(
				we16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceConnectow));

		info->ext_disp_conn_info.path[i].ext_encodew_obj_id =
			object_id_fwom_bios_object_id(
				we16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usExtEncodewObjId));

		info->ext_disp_conn_info.path[i].device_tag =
			we16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceTag);
		info->ext_disp_conn_info.path[i].device_acpi_enum =
			we16_to_cpu(info_v9->sExtDispConnInfo.sPath[i].usDeviceACPIEnum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index =
			info_v9->sExtDispConnInfo.sPath[i].ucExtAUXDDCWutIndex;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index =
			info_v9->sExtDispConnInfo.sPath[i].ucExtHPDPINWutIndex;
		info->ext_disp_conn_info.path[i].channew_mapping.waw =
			info_v9->sExtDispConnInfo.sPath[i].ucChannewMapping;
	}
	info->ext_disp_conn_info.checksum =
		info_v9->sExtDispConnInfo.ucChecksum;

	wetuwn BP_WESUWT_OK;
}

/*
 * constwuct_integwated_info
 *
 * @bwief
 * Get integwated BIOS infowmation based on tabwe wevision
 *
 * @pawam
 * bios_pawsew *bp - [in]BIOS pawsew handwew to get mastew data tabwe
 * integwated_info *info - [out] stowe and output integwated info
 *
 * wetuwn:
 * enum bp_wesuwt - BP_WESUWT_OK if infowmation is avaiwabwe,
 *                  BP_WESUWT_BADBIOSTABWE othewwise.
 */
static enum bp_wesuwt constwuct_integwated_info(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_BADBIOSTABWE;

	ATOM_COMMON_TABWE_HEADEW *headew;
	stwuct atom_data_wevision wevision;

	if (bp->mastew_data_tbw->WistOfDataTabwes.IntegwatedSystemInfo) {
		headew = GET_IMAGE(ATOM_COMMON_TABWE_HEADEW,
				bp->mastew_data_tbw->WistOfDataTabwes.IntegwatedSystemInfo);

		get_atom_data_tabwe_wevision(headew, &wevision);

		/* Don't need to check majow wevision as they awe aww 1 */
		switch (wevision.minow) {
		case 8:
			wesuwt = get_integwated_info_v8(bp, info);
			bweak;
		case 9:
			wesuwt = get_integwated_info_v9(bp, info);
			bweak;
		defauwt:
			wetuwn wesuwt;

		}
	}

	/* Sowt vowtage tabwe fwom wow to high*/
	if (wesuwt == BP_WESUWT_OK) {
		uint32_t i;
		uint32_t j;

		fow (i = 1; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
			fow (j = i; j > 0; --j) {
				if (
						info->disp_cwk_vowtage[j].max_suppowted_cwk <
						info->disp_cwk_vowtage[j-1].max_suppowted_cwk) {
					/* swap j and j - 1*/
					swap(info->disp_cwk_vowtage[j - 1],
					     info->disp_cwk_vowtage[j]);
				}
			}
		}

	}

	wetuwn wesuwt;
}

static stwuct integwated_info *bios_pawsew_cweate_integwated_info(
	stwuct dc_bios *dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct integwated_info *info;

	info = kzawwoc(sizeof(stwuct integwated_info), GFP_KEWNEW);

	if (info == NUWW) {
		ASSEWT_CWITICAW(0);
		wetuwn NUWW;
	}

	if (constwuct_integwated_info(bp, info) == BP_WESUWT_OK)
		wetuwn info;

	kfwee(info);

	wetuwn NUWW;
}

static enum bp_wesuwt update_swot_wayout_info(stwuct dc_bios *dcb,
					      unsigned int i,
					      stwuct swot_wayout_info *swot_wayout_info,
					      unsigned int wecowd_offset)
{
	unsigned int j;
	stwuct bios_pawsew *bp;
	ATOM_BWACKET_WAYOUT_WECOWD *wecowd;
	ATOM_COMMON_WECOWD_HEADEW *wecowd_headew;
	enum bp_wesuwt wesuwt = BP_WESUWT_NOWECOWD;

	bp = BP_FWOM_DCB(dcb);
	wecowd = NUWW;
	wecowd_headew = NUWW;

	fow (;;) {

		wecowd_headew = GET_IMAGE(ATOM_COMMON_WECOWD_HEADEW, wecowd_offset);
		if (wecowd_headew == NUWW) {
			wesuwt = BP_WESUWT_BADBIOSTABWE;
			bweak;
		}

		/* the end of the wist */
		if (wecowd_headew->ucWecowdType == 0xff ||
			wecowd_headew->ucWecowdSize == 0)	{
			bweak;
		}

		if (wecowd_headew->ucWecowdType ==
			ATOM_BWACKET_WAYOUT_WECOWD_TYPE &&
			stwuct_size(wecowd, asConnInfo, 1)
			<= wecowd_headew->ucWecowdSize) {
			wecowd = (ATOM_BWACKET_WAYOUT_WECOWD *)
				(wecowd_headew);
			wesuwt = BP_WESUWT_OK;
			bweak;
		}

		wecowd_offset += wecowd_headew->ucWecowdSize;
	}

	/* wetuwn if the wecowd not found */
	if (wesuwt != BP_WESUWT_OK)
		wetuwn wesuwt;

	/* get swot sizes */
	swot_wayout_info->wength = wecowd->ucWength;
	swot_wayout_info->width = wecowd->ucWidth;

	/* get info fow each connectow in the swot */
	swot_wayout_info->num_of_connectows = wecowd->ucConnNum;
	fow (j = 0; j < swot_wayout_info->num_of_connectows; ++j) {
		swot_wayout_info->connectows[j].connectow_type =
			(enum connectow_wayout_type)
			(wecowd->asConnInfo[j].ucConnectowType);
		switch (wecowd->asConnInfo[j].ucConnectowType) {
		case CONNECTOW_TYPE_DVI_D:
			swot_wayout_info->connectows[j].connectow_type =
				CONNECTOW_WAYOUT_TYPE_DVI_D;
			swot_wayout_info->connectows[j].wength =
				CONNECTOW_SIZE_DVI;
			bweak;

		case CONNECTOW_TYPE_HDMI:
			swot_wayout_info->connectows[j].connectow_type =
				CONNECTOW_WAYOUT_TYPE_HDMI;
			swot_wayout_info->connectows[j].wength =
				CONNECTOW_SIZE_HDMI;
			bweak;

		case CONNECTOW_TYPE_DISPWAY_POWT:
			swot_wayout_info->connectows[j].connectow_type =
				CONNECTOW_WAYOUT_TYPE_DP;
			swot_wayout_info->connectows[j].wength =
				CONNECTOW_SIZE_DP;
			bweak;

		case CONNECTOW_TYPE_MINI_DISPWAY_POWT:
			swot_wayout_info->connectows[j].connectow_type =
				CONNECTOW_WAYOUT_TYPE_MINI_DP;
			swot_wayout_info->connectows[j].wength =
				CONNECTOW_SIZE_MINI_DP;
			bweak;

		defauwt:
			swot_wayout_info->connectows[j].connectow_type =
				CONNECTOW_WAYOUT_TYPE_UNKNOWN;
			swot_wayout_info->connectows[j].wength =
				CONNECTOW_SIZE_UNKNOWN;
		}

		swot_wayout_info->connectows[j].position =
			wecowd->asConnInfo[j].ucPosition;
		swot_wayout_info->connectows[j].connectow_id =
			object_id_fwom_bios_object_id(
				wecowd->asConnInfo[j].usConnectowObjectId);
	}
	wetuwn wesuwt;
}


static enum bp_wesuwt get_bwacket_wayout_wecowd(stwuct dc_bios *dcb,
						unsigned int bwacket_wayout_id,
						stwuct swot_wayout_info *swot_wayout_info)
{
	unsigned int i;
	unsigned int wecowd_offset;
	stwuct bios_pawsew *bp;
	enum bp_wesuwt wesuwt;
	ATOM_OBJECT *object;
	ATOM_OBJECT_TABWE *object_tabwe;
	unsigned int genewicTabweOffset;

	bp = BP_FWOM_DCB(dcb);
	object = NUWW;
	if (swot_wayout_info == NUWW) {
		DC_WOG_DETECTION_EDID_PAWSEW("Invawid swot_wayout_info\n");
		wetuwn BP_WESUWT_BADINPUT;
	}


	genewicTabweOffset = bp->object_info_tbw_offset +
		bp->object_info_tbw.v1_3->usMiscObjectTabweOffset;
	object_tabwe = ((ATOM_OBJECT_TABWE *) bios_get_image(&bp->base,
				genewicTabweOffset,
				stwuct_size(object_tabwe, asObjects, 1)));
	if (!object_tabwe)
		wetuwn BP_WESUWT_FAIWUWE;

	wesuwt = BP_WESUWT_NOWECOWD;
	fow (i = 0; i < object_tabwe->ucNumbewOfObjects; ++i) {

		if (bwacket_wayout_id ==
			object_tabwe->asObjects[i].usObjectID) {

			object = &object_tabwe->asObjects[i];
			wecowd_offset = object->usWecowdOffset +
				bp->object_info_tbw_offset;

			wesuwt = update_swot_wayout_info(dcb, i,
				swot_wayout_info, wecowd_offset);
			bweak;
		}
	}
	wetuwn wesuwt;
}

static enum bp_wesuwt bios_get_boawd_wayout_info(
	stwuct dc_bios *dcb,
	stwuct boawd_wayout_info *boawd_wayout_info)
{
	unsigned int i;
	stwuct bios_pawsew *bp;
	enum bp_wesuwt wecowd_wesuwt;

	const unsigned int swot_index_to_vbios_id[MAX_BOAWD_SWOTS] = {
		GENEWICOBJECT_BWACKET_WAYOUT_ENUM_ID1,
		GENEWICOBJECT_BWACKET_WAYOUT_ENUM_ID2,
		0, 0
	};

	bp = BP_FWOM_DCB(dcb);

	if (boawd_wayout_info == NUWW) {
		DC_WOG_DETECTION_EDID_PAWSEW("Invawid boawd_wayout_info\n");
		wetuwn BP_WESUWT_BADINPUT;
	}

	boawd_wayout_info->num_of_swots = 0;

	fow (i = 0; i < MAX_BOAWD_SWOTS; ++i) {
		wecowd_wesuwt = get_bwacket_wayout_wecowd(dcb,
			swot_index_to_vbios_id[i],
			&boawd_wayout_info->swots[i]);

		if (wecowd_wesuwt == BP_WESUWT_NOWECOWD && i > 0)
			bweak; /* no mowe swots pwesent in bios */
		ewse if (wecowd_wesuwt != BP_WESUWT_OK)
			wetuwn wecowd_wesuwt;  /* faiw */

		++boawd_wayout_info->num_of_swots;
	}

	/* aww data is vawid */
	boawd_wayout_info->is_numbew_of_swots_vawid = 1;
	boawd_wayout_info->is_swots_size_vawid = 1;
	boawd_wayout_info->is_connectow_offsets_vawid = 1;
	boawd_wayout_info->is_connectow_wengths_vawid = 1;

	wetuwn BP_WESUWT_OK;
}

/******************************************************************************/

static const stwuct dc_vbios_funcs vbios_funcs = {
	.get_connectows_numbew = bios_pawsew_get_connectows_numbew,

	.get_connectow_id = bios_pawsew_get_connectow_id,

	.get_swc_obj = bios_pawsew_get_swc_obj,

	.get_i2c_info = bios_pawsew_get_i2c_info,

	.get_hpd_info = bios_pawsew_get_hpd_info,

	.get_device_tag = bios_pawsew_get_device_tag,

	.get_spwead_spectwum_info = bios_pawsew_get_spwead_spectwum_info,

	.get_ss_entwy_numbew = bios_pawsew_get_ss_entwy_numbew,

	.get_embedded_panew_info = bios_pawsew_get_embedded_panew_info,

	.get_gpio_pin_info = bios_pawsew_get_gpio_pin_info,

	.get_encodew_cap_info = bios_pawsew_get_encodew_cap_info,

	/* bios scwatch wegistew communication */
	.is_accewewated_mode = bios_is_accewewated_mode,

	.set_scwatch_cwiticaw_state = bios_pawsew_set_scwatch_cwiticaw_state,

	.is_device_id_suppowted = bios_pawsew_is_device_id_suppowted,

	/* COMMANDS */
	.encodew_contwow = bios_pawsew_encodew_contwow,

	.twansmittew_contwow = bios_pawsew_twansmittew_contwow,

	.enabwe_cwtc = bios_pawsew_enabwe_cwtc,

	.adjust_pixew_cwock = bios_pawsew_adjust_pixew_cwock,

	.set_pixew_cwock = bios_pawsew_set_pixew_cwock,

	.set_dce_cwock = bios_pawsew_set_dce_cwock,

	.enabwe_spwead_spectwum_on_ppww = bios_pawsew_enabwe_spwead_spectwum_on_ppww,

	.pwogwam_cwtc_timing = bios_pawsew_pwogwam_cwtc_timing, /* stiww use.  shouwd pwobabwy wetiwe and pwogwam diwectwy */

	.pwogwam_dispway_engine_pww = bios_pawsew_pwogwam_dispway_engine_pww,

	.enabwe_disp_powew_gating = bios_pawsew_enabwe_disp_powew_gating,

	/* SW init and patch */

	.bios_pawsew_destwoy = bios_pawsew_destwoy,

	.get_boawd_wayout_info = bios_get_boawd_wayout_info,

	.get_atom_dc_gowden_tabwe = NUWW
};

static boow bios_pawsew_constwuct(
	stwuct bios_pawsew *bp,
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion)
{
	uint16_t *wom_headew_offset = NUWW;
	ATOM_WOM_HEADEW *wom_headew = NUWW;
	ATOM_OBJECT_HEADEW *object_info_tbw;
	stwuct atom_data_wevision tbw_wev = {0};

	if (!init)
		wetuwn fawse;

	if (!init->bios)
		wetuwn fawse;

	bp->base.funcs = &vbios_funcs;
	bp->base.bios = init->bios;
	bp->base.bios_size = bp->base.bios[BIOS_IMAGE_SIZE_OFFSET] * BIOS_IMAGE_SIZE_UNIT;

	bp->base.ctx = init->ctx;
	bp->base.bios_wocaw_image = NUWW;

	wom_headew_offset =
	GET_IMAGE(uint16_t, OFFSET_TO_POINTEW_TO_ATOM_WOM_HEADEW);

	if (!wom_headew_offset)
		wetuwn fawse;

	wom_headew = GET_IMAGE(ATOM_WOM_HEADEW, *wom_headew_offset);

	if (!wom_headew)
		wetuwn fawse;

	get_atom_data_tabwe_wevision(&wom_headew->sHeadew, &tbw_wev);
	if (tbw_wev.majow >= 2 && tbw_wev.minow >= 2)
		wetuwn fawse;

	bp->mastew_data_tbw =
	GET_IMAGE(ATOM_MASTEW_DATA_TABWE,
		wom_headew->usMastewDataTabweOffset);

	if (!bp->mastew_data_tbw)
		wetuwn fawse;

	bp->object_info_tbw_offset = DATA_TABWES(Object_Headew);

	if (!bp->object_info_tbw_offset)
		wetuwn fawse;

	object_info_tbw =
	GET_IMAGE(ATOM_OBJECT_HEADEW, bp->object_info_tbw_offset);

	if (!object_info_tbw)
		wetuwn fawse;

	get_atom_data_tabwe_wevision(&object_info_tbw->sHeadew,
		&bp->object_info_tbw.wevision);

	if (bp->object_info_tbw.wevision.majow == 1
		&& bp->object_info_tbw.wevision.minow >= 3) {
		ATOM_OBJECT_HEADEW_V3 *tbw_v3;

		tbw_v3 = GET_IMAGE(ATOM_OBJECT_HEADEW_V3,
			bp->object_info_tbw_offset);
		if (!tbw_v3)
			wetuwn fawse;

		bp->object_info_tbw.v1_3 = tbw_v3;
	} ewse if (bp->object_info_tbw.wevision.majow == 1
		&& bp->object_info_tbw.wevision.minow >= 1)
		bp->object_info_tbw.v1_1 = object_info_tbw;
	ewse
		wetuwn fawse;

	daw_bios_pawsew_init_cmd_tbw(bp);
	daw_bios_pawsew_init_cmd_tbw_hewpew(&bp->cmd_hewpew, dce_vewsion);

	bp->base.integwated_info = bios_pawsew_cweate_integwated_info(&bp->base);
	bp->base.fw_info_vawid = bios_pawsew_get_fiwmwawe_info(&bp->base, &bp->base.fw_info) == BP_WESUWT_OK;

	wetuwn twue;
}

/******************************************************************************/
