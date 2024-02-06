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

#incwude "dm_sewvices.h"
#incwude "cowe_types.h"

#incwude "ObjectID.h"
#incwude "atomfiwmwawe.h"

#incwude "dc_bios_types.h"
#incwude "incwude/gwph_object_ctww_defs.h"
#incwude "incwude/bios_pawsew_intewface.h"
#incwude "incwude/woggew_intewface.h"

#incwude "command_tabwe2.h"

#incwude "bios_pawsew_hewpew.h"
#incwude "command_tabwe_hewpew2.h"
#incwude "bios_pawsew2.h"
#incwude "bios_pawsew_types_intewnaw2.h"
#incwude "bios_pawsew_intewface.h"

#incwude "bios_pawsew_common.h"

#define DC_WOGGEW \
	bp->base.ctx->woggew

#define WAST_WECOWD_TYPE 0xff
#define SMU9_SYSPWW0_ID  0

static enum bp_wesuwt get_gpio_i2c_info(stwuct bios_pawsew *bp,
	stwuct atom_i2c_wecowd *wecowd,
	stwuct gwaphics_object_i2c_info *info);

static enum bp_wesuwt bios_pawsew_get_fiwmwawe_info(
	stwuct dc_bios *dcb,
	stwuct dc_fiwmwawe_info *info);

static enum bp_wesuwt bios_pawsew_get_encodew_cap_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id,
	stwuct bp_encodew_cap_info *info);

static enum bp_wesuwt get_fiwmwawe_info_v3_1(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);

static enum bp_wesuwt get_fiwmwawe_info_v3_2(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);

static enum bp_wesuwt get_fiwmwawe_info_v3_4(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info);

static stwuct atom_hpd_int_wecowd *get_hpd_wecowd(stwuct bios_pawsew *bp,
		stwuct atom_dispway_object_path_v2 *object);

static stwuct atom_encodew_caps_wecowd *get_encodew_cap_wecowd(
	stwuct bios_pawsew *bp,
	stwuct atom_dispway_object_path_v2 *object);

#define BIOS_IMAGE_SIZE_OFFSET 2
#define BIOS_IMAGE_SIZE_UNIT 512

#define DATA_TABWES(tabwe) (bp->mastew_data_tbw->wistOfdatatabwes.tabwe)

static void bios_pawsew2_destwuct(stwuct bios_pawsew *bp)
{
	kfwee(bp->base.bios_wocaw_image);
	kfwee(bp->base.integwated_info);
}

static void fiwmwawe_pawsew_destwoy(stwuct dc_bios **dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(*dcb);

	if (!bp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	bios_pawsew2_destwuct(bp);

	kfwee(bp);
	*dcb = NUWW;
}

static void get_atom_data_tabwe_wevision(
	stwuct atom_common_tabwe_headew *atom_data_tbw,
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
			(uint32_t) atom_data_tbw->fowmat_wevision & 0x3f;
	tbw_wevision->minow =
			(uint32_t) atom_data_tbw->content_wevision & 0x3f;
}

/* BIOS oject tabwe dispwaypath is pew connectow.
 * Thewe is extwa path not fow connectow. BIOS fiww its encodewid as 0
 */
static uint8_t bios_pawsew_get_connectows_numbew(stwuct dc_bios *dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	unsigned int count = 0;
	unsigned int i;

	switch (bp->object_info_tbw.wevision.minow) {
	defauwt:
	case 4:
		fow (i = 0; i < bp->object_info_tbw.v1_4->numbew_of_path; i++)
			if (bp->object_info_tbw.v1_4->dispway_path[i].encodewobjid != 0)
				count++;

		bweak;

	case 5:
		fow (i = 0; i < bp->object_info_tbw.v1_5->numbew_of_path; i++)
			if (bp->object_info_tbw.v1_5->dispway_path[i].encodewobjid != 0)
				count++;

		bweak;
	}
	wetuwn count;
}

static stwuct gwaphics_object_id bios_pawsew_get_connectow_id(
	stwuct dc_bios *dcb,
	uint8_t i)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct gwaphics_object_id object_id = daw_gwaphics_object_id_init(
		0, ENUM_ID_UNKNOWN, OBJECT_TYPE_UNKNOWN);
	stwuct object_info_tabwe *tbw = &bp->object_info_tbw;
	stwuct dispway_object_info_tabwe_v1_4 *v1_4 = tbw->v1_4;

	stwuct dispway_object_info_tabwe_v1_5 *v1_5 = tbw->v1_5;

	switch (bp->object_info_tbw.wevision.minow) {
	defauwt:
	case 4:
		if (v1_4->numbew_of_path > i) {
			/* If dispway_objid is genewic object id,  the encodewObj
			 * /extencodewobjId shouwd be 0
			 */
			if (v1_4->dispway_path[i].encodewobjid != 0 &&
			    v1_4->dispway_path[i].dispway_objid != 0)
				object_id = object_id_fwom_bios_object_id(
					v1_4->dispway_path[i].dispway_objid);
		}
		bweak;

	case 5:
		if (v1_5->numbew_of_path > i) {
			/* If dispway_objid is genewic object id,  the encodewObjId
		 * shouwd be 0
		 */
			if (v1_5->dispway_path[i].encodewobjid != 0 &&
			    v1_5->dispway_path[i].dispway_objid != 0)
				object_id = object_id_fwom_bios_object_id(
					v1_5->dispway_path[i].dispway_objid);
		}
		bweak;
	}
	wetuwn object_id;
}

static enum bp_wesuwt bios_pawsew_get_swc_obj(stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id, uint32_t index,
	stwuct gwaphics_object_id *swc_object_id)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	unsigned int i;
	enum bp_wesuwt bp_wesuwt = BP_WESUWT_BADINPUT;
	stwuct gwaphics_object_id obj_id = { 0 };
	stwuct object_info_tabwe *tbw = &bp->object_info_tbw;

	if (!swc_object_id)
		wetuwn bp_wesuwt;

	switch (object_id.type) {
	/* Encodew's Souwce is GPU.  BIOS does not pwovide GPU, since aww
	 * dispwaypaths point to same GPU (0x1100).  Hawdcode GPU object type
	 */
	case OBJECT_TYPE_ENCODEW:
		/* TODO: since num of swc must be wess than 2.
		 * If found in fow woop, shouwd bweak.
		 * DAW2 impwementation may be changed too
		 */
		switch (bp->object_info_tbw.wevision.minow) {
		defauwt:
		case 4:
			fow (i = 0; i < tbw->v1_4->numbew_of_path; i++) {
				obj_id = object_id_fwom_bios_object_id(
					tbw->v1_4->dispway_path[i].encodewobjid);
				if (object_id.type == obj_id.type &&
				    object_id.id == obj_id.id &&
				    object_id.enum_id == obj_id.enum_id) {
					*swc_object_id =
						object_id_fwom_bios_object_id(
							0x1100);
					/* bweak; */
				}
			}
			bp_wesuwt = BP_WESUWT_OK;
			bweak;

		case 5:
			fow (i = 0; i < tbw->v1_5->numbew_of_path; i++) {
				obj_id = object_id_fwom_bios_object_id(
					tbw->v1_5->dispway_path[i].encodewobjid);
				if (object_id.type == obj_id.type &&
				    object_id.id == obj_id.id &&
				    object_id.enum_id == obj_id.enum_id) {
					*swc_object_id =
						object_id_fwom_bios_object_id(
							0x1100);
					/* bweak; */
				}
			}
			bp_wesuwt = BP_WESUWT_OK;
			bweak;
		}
		bweak;
	case OBJECT_TYPE_CONNECTOW:
		switch (bp->object_info_tbw.wevision.minow) {
		defauwt:
		case 4:
			fow (i = 0; i < tbw->v1_4->numbew_of_path; i++) {
				obj_id = object_id_fwom_bios_object_id(
					tbw->v1_4->dispway_path[i]
						.dispway_objid);

				if (object_id.type == obj_id.type &&
				    object_id.id == obj_id.id &&
				    object_id.enum_id == obj_id.enum_id) {
					*swc_object_id =
						object_id_fwom_bios_object_id(
							tbw->v1_4
								->dispway_path[i]
								.encodewobjid);
					/* bweak; */
				}
			}
			bp_wesuwt = BP_WESUWT_OK;
			bweak;
		}
		bp_wesuwt = BP_WESUWT_OK;
		bweak;
		case 5:
			fow (i = 0; i < tbw->v1_5->numbew_of_path; i++) {
				obj_id = object_id_fwom_bios_object_id(
								       tbw->v1_5->dispway_path[i].dispway_objid);

				if (object_id.type == obj_id.type &&
				    object_id.id == obj_id.id &&
				    object_id.enum_id == obj_id.enum_id) {
					*swc_object_id = object_id_fwom_bios_object_id(
										       tbw->v1_5->dispway_path[i].encodewobjid);
					/* bweak; */
				}
			}
		bp_wesuwt = BP_WESUWT_OK;
		bweak;

	defauwt:
		bp_wesuwt = BP_WESUWT_OK;
		bweak;
	}

	wetuwn bp_wesuwt;
}

/* fwom gwaphics_object_id, find dispway path which incwudes the object_id */
static stwuct atom_dispway_object_path_v2 *get_bios_object(
		stwuct bios_pawsew *bp,
		stwuct gwaphics_object_id id)
{
	unsigned int i;
	stwuct gwaphics_object_id obj_id = {0};

	switch (id.type) {
	case OBJECT_TYPE_ENCODEW:
		fow (i = 0; i < bp->object_info_tbw.v1_4->numbew_of_path; i++) {
			obj_id = object_id_fwom_bios_object_id(
					bp->object_info_tbw.v1_4->dispway_path[i].encodewobjid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				wetuwn &bp->object_info_tbw.v1_4->dispway_path[i];
		}
		fawwthwough;
	case OBJECT_TYPE_CONNECTOW:
	case OBJECT_TYPE_GENEWIC:
		/* Both Genewic and Connectow Object ID
		 * wiww be stowed on dispway_objid
		 */
		fow (i = 0; i < bp->object_info_tbw.v1_4->numbew_of_path; i++) {
			obj_id = object_id_fwom_bios_object_id(
					bp->object_info_tbw.v1_4->dispway_path[i].dispway_objid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				wetuwn &bp->object_info_tbw.v1_4->dispway_path[i];
		}
		fawwthwough;
	defauwt:
		wetuwn NUWW;
	}
}

/* fwom gwaphics_object_id, find dispway path which incwudes the object_id */
static stwuct atom_dispway_object_path_v3 *get_bios_object_fwom_path_v3(stwuct bios_pawsew *bp,
									stwuct gwaphics_object_id id)
{
	unsigned int i;
	stwuct gwaphics_object_id obj_id = {0};

	switch (id.type) {
	case OBJECT_TYPE_ENCODEW:
		fow (i = 0; i < bp->object_info_tbw.v1_5->numbew_of_path; i++) {
			obj_id = object_id_fwom_bios_object_id(
					bp->object_info_tbw.v1_5->dispway_path[i].encodewobjid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				wetuwn &bp->object_info_tbw.v1_5->dispway_path[i];
		}
	bweak;

	case OBJECT_TYPE_CONNECTOW:
	case OBJECT_TYPE_GENEWIC:
		/* Both Genewic and Connectow Object ID
		 * wiww be stowed on dispway_objid
		 */
		fow (i = 0; i < bp->object_info_tbw.v1_5->numbew_of_path; i++) {
			obj_id = object_id_fwom_bios_object_id(
					bp->object_info_tbw.v1_5->dispway_path[i].dispway_objid);
			if (id.type == obj_id.type && id.id == obj_id.id
					&& id.enum_id == obj_id.enum_id)
				wetuwn &bp->object_info_tbw.v1_5->dispway_path[i];
		}
	bweak;

	defauwt:
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

static enum bp_wesuwt bios_pawsew_get_i2c_info(stwuct dc_bios *dcb,
	stwuct gwaphics_object_id id,
	stwuct gwaphics_object_i2c_info *info)
{
	uint32_t offset;
	stwuct atom_dispway_object_path_v2 *object;

	stwuct atom_dispway_object_path_v3 *object_path_v3;

	stwuct atom_common_wecowd_headew *headew;
	stwuct atom_i2c_wecowd *wecowd;
	stwuct atom_i2c_wecowd dummy_wecowd = {0};
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (id.type == OBJECT_TYPE_GENEWIC) {
		dummy_wecowd.i2c_id = id.id;

		if (get_gpio_i2c_info(bp, &dummy_wecowd, info) == BP_WESUWT_OK)
			wetuwn BP_WESUWT_OK;
		ewse
			wetuwn BP_WESUWT_NOWECOWD;
	}

	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
	defauwt:
		object = get_bios_object(bp, id);

		if (!object)
			wetuwn BP_WESUWT_BADINPUT;

		offset = object->disp_wecowdoffset + bp->object_info_tbw_offset;
		bweak;
	case 5:
		object_path_v3 = get_bios_object_fwom_path_v3(bp, id);

		if (!object_path_v3)
			wetuwn BP_WESUWT_BADINPUT;

		offset = object_path_v3->disp_wecowdoffset + bp->object_info_tbw_offset;
		bweak;
	}

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn BP_WESUWT_BADBIOSTABWE;

		if (headew->wecowd_type == WAST_WECOWD_TYPE ||
			!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type == ATOM_I2C_WECOWD_TYPE
			&& sizeof(stwuct atom_i2c_wecowd) <=
							headew->wecowd_size) {
			/* get the I2C info */
			wecowd = (stwuct atom_i2c_wecowd *) headew;

			if (get_gpio_i2c_info(bp, wecowd, info) ==
								BP_WESUWT_OK)
				wetuwn BP_WESUWT_OK;
		}

		offset += headew->wecowd_size;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static enum bp_wesuwt get_gpio_i2c_info(
	stwuct bios_pawsew *bp,
	stwuct atom_i2c_wecowd *wecowd,
	stwuct gwaphics_object_i2c_info *info)
{
	stwuct atom_gpio_pin_wut_v2_1 *headew;
	uint32_t count = 0;
	unsigned int tabwe_index = 0;
	boow find_vawid = fawse;
	stwuct atom_gpio_pin_assignment *pin;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	/* get the GPIO_I2C info */
	if (!DATA_TABWES(gpio_pin_wut))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	headew = GET_IMAGE(stwuct atom_gpio_pin_wut_v2_1,
					DATA_TABWES(gpio_pin_wut));
	if (!headew)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (sizeof(stwuct atom_common_tabwe_headew) +
			sizeof(stwuct atom_gpio_pin_assignment)	>
			we16_to_cpu(headew->tabwe_headew.stwuctuwesize))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	/* TODO: is vewsion change? */
	if (headew->tabwe_headew.content_wevision != 1)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	/* get data count */
	count = (we16_to_cpu(headew->tabwe_headew.stwuctuwesize)
			- sizeof(stwuct atom_common_tabwe_headew))
				/ sizeof(stwuct atom_gpio_pin_assignment);

	pin = (stwuct atom_gpio_pin_assignment *) headew->gpio_pin;

	fow (tabwe_index = 0; tabwe_index < count; tabwe_index++) {
		if (((wecowd->i2c_id & I2C_HW_CAP) 				== (pin->gpio_id & I2C_HW_CAP)) &&
		    ((wecowd->i2c_id & I2C_HW_ENGINE_ID_MASK)	== (pin->gpio_id & I2C_HW_ENGINE_ID_MASK)) &&
		    ((wecowd->i2c_id & I2C_HW_WANE_MUX) 		== (pin->gpio_id & I2C_HW_WANE_MUX))) {
			/* stiww vawid */
			find_vawid = twue;
			bweak;
		}
		pin = (stwuct atom_gpio_pin_assignment *)((uint8_t *)pin + sizeof(stwuct atom_gpio_pin_assignment));
	}

	/* If we don't find the entwy that we awe wooking fow then
	 *  we wiww wetuwn BP_Wesuwt_BadBiosTabwe.
	 */
	if (find_vawid == fawse)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	/* get the GPIO_I2C_INFO */
	info->i2c_hw_assist = (wecowd->i2c_id & I2C_HW_CAP) ? twue : fawse;
	info->i2c_wine = wecowd->i2c_id & I2C_HW_WANE_MUX;
	info->i2c_engine_id = (wecowd->i2c_id & I2C_HW_ENGINE_ID_MASK) >> 4;
	info->i2c_swave_addwess = wecowd->i2c_swave_addw;

	/* TODO: check how to get wegistew offset fow en, Y, etc. */
	info->gpio_info.cwk_a_wegistew_index = we16_to_cpu(pin->data_a_weg_index);
	info->gpio_info.cwk_a_shift = pin->gpio_bitshift;

	wetuwn BP_WESUWT_OK;
}

static stwuct atom_hpd_int_wecowd *get_hpd_wecowd_fow_path_v3(stwuct bios_pawsew *bp,
							      stwuct atom_dispway_object_path_v3 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = object->disp_wecowdoffset + bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		if (headew->wecowd_type == ATOM_WECOWD_END_TYPE ||
			!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type == ATOM_HPD_INT_WECOWD_TYPE
			&& sizeof(stwuct atom_hpd_int_wecowd) <=
							headew->wecowd_size)
			wetuwn (stwuct atom_hpd_int_wecowd *) headew;

		offset += headew->wecowd_size;
	}

	wetuwn NUWW;
}

static enum bp_wesuwt bios_pawsew_get_hpd_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id id,
	stwuct gwaphics_object_hpd_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_dispway_object_path_v2 *object;
	stwuct atom_dispway_object_path_v3 *object_path_v3;
	stwuct atom_hpd_int_wecowd *wecowd = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
	defauwt:
		object = get_bios_object(bp, id);

		if (!object)
			wetuwn BP_WESUWT_BADINPUT;

		wecowd = get_hpd_wecowd(bp, object);
		bweak;
	case 5:
		object_path_v3 = get_bios_object_fwom_path_v3(bp, id);

		if (!object_path_v3)
			wetuwn BP_WESUWT_BADINPUT;

		wecowd = get_hpd_wecowd_fow_path_v3(bp, object_path_v3);
		bweak;
	}

	if (wecowd != NUWW) {
		info->hpd_int_gpio_uid = wecowd->pin_id;
		info->hpd_active = wecowd->pwugin_pin_state;
		wetuwn BP_WESUWT_OK;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static stwuct atom_hpd_int_wecowd *get_hpd_wecowd(
	stwuct bios_pawsew *bp,
	stwuct atom_dispway_object_path_v2 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = we16_to_cpu(object->disp_wecowdoffset)
			+ bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		if (headew->wecowd_type == WAST_WECOWD_TYPE ||
			!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type == ATOM_HPD_INT_WECOWD_TYPE
			&& sizeof(stwuct atom_hpd_int_wecowd) <=
							headew->wecowd_size)
			wetuwn (stwuct atom_hpd_int_wecowd *) headew;

		offset += headew->wecowd_size;
	}

	wetuwn NUWW;
}

/**
 * bios_pawsew_get_gpio_pin_info
 * Get GpioPin infowmation of input gpio id
 *
 * @dcb:     pointew to the DC BIOS
 * @gpio_id: GPIO ID
 * @info:    GpioPin infowmation stwuctuwe
 * wetuwn: Bios pawsew wesuwt code
 * note:
 *  to get the GPIO PIN INFO, we need:
 *  1. get the GPIO_ID fwom othew object tabwe, see GetHPDInfo()
 *  2. in DATA_TABWE.GPIO_Pin_WUT, seawch aww wecowds,
 *	to get the wegistewA  offset/mask
 */
static enum bp_wesuwt bios_pawsew_get_gpio_pin_info(
	stwuct dc_bios *dcb,
	uint32_t gpio_id,
	stwuct gpio_pin_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_gpio_pin_wut_v2_1 *headew;
	uint32_t count = 0;
	uint32_t i = 0;

	if (!DATA_TABWES(gpio_pin_wut))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	headew = GET_IMAGE(stwuct atom_gpio_pin_wut_v2_1,
						DATA_TABWES(gpio_pin_wut));
	if (!headew)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (sizeof(stwuct atom_common_tabwe_headew) +
			sizeof(stwuct atom_gpio_pin_assignment)
			> we16_to_cpu(headew->tabwe_headew.stwuctuwesize))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (headew->tabwe_headew.content_wevision != 1)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	/* Tempowawy hawd code gpio pin info */
	count = (we16_to_cpu(headew->tabwe_headew.stwuctuwesize)
			- sizeof(stwuct atom_common_tabwe_headew))
				/ sizeof(stwuct atom_gpio_pin_assignment);
	fow (i = 0; i < count; ++i) {
		if (headew->gpio_pin[i].gpio_id != gpio_id)
			continue;

		info->offset =
			(uint32_t) we16_to_cpu(
					headew->gpio_pin[i].data_a_weg_index);
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask = (uint32_t) (1 <<
			headew->gpio_pin[i].gpio_bitshift);
		info->mask_y = info->mask + 2;
		info->mask_en = info->mask + 1;
		info->mask_mask = info->mask - 1;

		wetuwn BP_WESUWT_OK;
	}

	wetuwn BP_WESUWT_NOWECOWD;
}

static stwuct device_id device_type_fwom_device_id(uint16_t device_id)
{

	stwuct device_id wesuwt_device_id;

	wesuwt_device_id.waw_device_tag = device_id;

	switch (device_id) {
	case ATOM_DISPWAY_WCD1_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_WCD;
		wesuwt_device_id.enum_id = 1;
		bweak;

	case ATOM_DISPWAY_WCD2_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_WCD;
		wesuwt_device_id.enum_id = 2;
		bweak;

	case ATOM_DISPWAY_DFP1_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 1;
		bweak;

	case ATOM_DISPWAY_DFP2_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 2;
		bweak;

	case ATOM_DISPWAY_DFP3_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 3;
		bweak;

	case ATOM_DISPWAY_DFP4_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 4;
		bweak;

	case ATOM_DISPWAY_DFP5_SUPPOWT:
		wesuwt_device_id.device_type = DEVICE_TYPE_DFP;
		wesuwt_device_id.enum_id = 5;
		bweak;

	case ATOM_DISPWAY_DFP6_SUPPOWT:
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

static enum bp_wesuwt bios_pawsew_get_device_tag(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id connectow_object_id,
	uint32_t device_tag_index,
	stwuct connectow_device_tag_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_dispway_object_path_v2 *object;

	stwuct atom_dispway_object_path_v3 *object_path_v3;


	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
	defauwt:
	        /* getBiosObject wiww wetuwn MXM object */
		object = get_bios_object(bp, connectow_object_id);

		if (!object) {
			BWEAK_TO_DEBUGGEW(); /* Invawid object id */
			wetuwn BP_WESUWT_BADINPUT;
		}

		info->acpi_device = 0; /* BIOS no wongew pwovides this */
		info->dev_id = device_type_fwom_device_id(object->device_tag);
		bweak;
	case 5:
		object_path_v3 = get_bios_object_fwom_path_v3(bp, connectow_object_id);

		if (!object_path_v3) {
			BWEAK_TO_DEBUGGEW(); /* Invawid object id */
			wetuwn BP_WESUWT_BADINPUT;
		}
		info->acpi_device = 0; /* BIOS no wongew pwovides this */
		info->dev_id = device_type_fwom_device_id(object_path_v3->device_tag);
		bweak;
	}

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_ss_info_v4_1(
	stwuct bios_pawsew *bp,
	uint32_t id,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_1 *disp_cntw_tbw = NUWW;
	stwuct atom_smu_info_v3_3 *smu_info = NUWW;

	if (!ss_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw =  GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_1,
							DATA_TABWES(dce_info));
	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;


	ss_info->type.STEP_AND_DEWAY_INFO = fawse;
	ss_info->spwead_pewcentage_dividew = 1000;
	/* BIOS no wongew uses tawget cwock.  Awways enabwe fow now */
	ss_info->tawget_cwock_wange = 0xffffffff;

	switch (id) {
	case AS_SIGNAW_TYPE_DVI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->dvi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->dvi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->dvi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_DVI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_HDMI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->hdmi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->hdmi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->hdmi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_HDMI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	/* TODO WVDS not suppowt anymowe? */
	case AS_SIGNAW_TYPE_DISPWAY_POWT:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->dp_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->dp_ss_wate_10hz * 10;
		if (disp_cntw_tbw->dp_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_DISPWAY_POWT ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_GPU_PWW:
		/* atom_fiwmwawe: DAW onwy get data fwom dce_info tabwe.
		 * if data within smu_info is needed fow DAW, VBIOS shouwd
		 * copy it into dce_info
		 */
		wesuwt = BP_WESUWT_UNSUPPOWTED;
		bweak;
	case AS_SIGNAW_TYPE_XGMI:
		smu_info =  GET_IMAGE(stwuct atom_smu_info_v3_3,
				      DATA_TABWES(smu_info));
		if (!smu_info)
			wetuwn BP_WESUWT_BADBIOSTABWE;
		DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", smu_info->gpucwk_ss_pewcentage);
		ss_info->spwead_spectwum_pewcentage =
				smu_info->wafwcwk_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				smu_info->gpucwk_ss_wate_10hz * 10;
		if (smu_info->wafwcwk_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_XGMI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	defauwt:
		wesuwt = BP_WESUWT_UNSUPPOWTED;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt get_ss_info_v4_2(
	stwuct bios_pawsew *bp,
	uint32_t id,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_2 *disp_cntw_tbw = NUWW;
	stwuct atom_smu_info_v3_1 *smu_info = NUWW;

	if (!ss_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (!DATA_TABWES(smu_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw =  GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_2,
							DATA_TABWES(dce_info));
	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	smu_info =  GET_IMAGE(stwuct atom_smu_info_v3_1, DATA_TABWES(smu_info));
	if (!smu_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", smu_info->gpucwk_ss_pewcentage);
	ss_info->type.STEP_AND_DEWAY_INFO = fawse;
	ss_info->spwead_pewcentage_dividew = 1000;
	/* BIOS no wongew uses tawget cwock.  Awways enabwe fow now */
	ss_info->tawget_cwock_wange = 0xffffffff;

	switch (id) {
	case AS_SIGNAW_TYPE_DVI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->dvi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->dvi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->dvi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_DVI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_HDMI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->hdmi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->hdmi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->hdmi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_HDMI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	/* TODO WVDS not suppowt anymowe? */
	case AS_SIGNAW_TYPE_DISPWAY_POWT:
		ss_info->spwead_spectwum_pewcentage =
				smu_info->gpucwk_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				smu_info->gpucwk_ss_wate_10hz * 10;
		if (smu_info->gpucwk_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_DISPWAY_POWT ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_GPU_PWW:
		/* atom_fiwmwawe: DAW onwy get data fwom dce_info tabwe.
		 * if data within smu_info is needed fow DAW, VBIOS shouwd
		 * copy it into dce_info
		 */
		wesuwt = BP_WESUWT_UNSUPPOWTED;
		bweak;
	defauwt:
		wesuwt = BP_WESUWT_UNSUPPOWTED;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt get_ss_info_v4_5(
	stwuct bios_pawsew *bp,
	uint32_t id,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_5 *disp_cntw_tbw = NUWW;

	if (!ss_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw =  GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_5,
							DATA_TABWES(dce_info));
	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	ss_info->type.STEP_AND_DEWAY_INFO = fawse;
	ss_info->spwead_pewcentage_dividew = 1000;
	/* BIOS no wongew uses tawget cwock.  Awways enabwe fow now */
	ss_info->tawget_cwock_wange = 0xffffffff;

	switch (id) {
	case AS_SIGNAW_TYPE_DVI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->dvi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->dvi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->dvi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_DVI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_HDMI:
		ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->hdmi_ss_pewcentage;
		ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->hdmi_ss_wate_10hz * 10;
		if (disp_cntw_tbw->hdmi_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
			ss_info->type.CENTEW_MODE = twue;

		DC_WOG_BIOS("AS_SIGNAW_TYPE_HDMI ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_DISPWAY_POWT:
		if (bp->base.integwated_info) {
			DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", bp->base.integwated_info->gpucwk_ss_pewcentage);
			ss_info->spwead_spectwum_pewcentage =
					bp->base.integwated_info->gpucwk_ss_pewcentage;
			ss_info->type.CENTEW_MODE =
					bp->base.integwated_info->gpucwk_ss_type;
		} ewse {
			ss_info->spwead_spectwum_pewcentage =
				disp_cntw_tbw->dp_ss_pewcentage;
			ss_info->spwead_spectwum_wange =
				disp_cntw_tbw->dp_ss_wate_10hz * 10;
			if (disp_cntw_tbw->dp_ss_mode & ATOM_SS_CENTWE_SPWEAD_MODE)
				ss_info->type.CENTEW_MODE = twue;
		}
		DC_WOG_BIOS("AS_SIGNAW_TYPE_DISPWAY_POWT ss_pewcentage: %d\n", ss_info->spwead_spectwum_pewcentage);
		bweak;
	case AS_SIGNAW_TYPE_GPU_PWW:
		/* atom_smu_info_v4_0 does not have fiewds fow SS fow SMU Dispway PWW anymowe.
		 * SMU Dispway PWW supposed to be without spwead.
		 * Bettew pwace fow it wouwd be in atom_dispway_contwowwew_info_v4_5 tabwe.
		 */
		wesuwt = BP_WESUWT_UNSUPPOWTED;
		bweak;
	defauwt:
		wesuwt = BP_WESUWT_UNSUPPOWTED;
		bweak;
	}

	wetuwn wesuwt;
}

/**
 * bios_pawsew_get_spwead_spectwum_info
 * Get spwead spectwum infowmation fwom the ASIC_IntewnawSS_Info(vew 2.1 ow
 * vew 3.1) ow SS_Info tabwe fwom the VBIOS. Cuwwentwy ASIC_IntewnawSS_Info
 * vew 2.1 can co-exist with SS_Info tabwe. Expect ASIC_IntewnawSS_Info
 * vew 3.1,
 * thewe is onwy one entwy fow each signaw /ss id.  Howevew, thewe is
 * no pwanning of suppowting muwtipwe spwead Spwectum entwy fow EvewGween
 * @dcb:     pointew to the DC BIOS
 * @signaw:  ASSignawType to be convewted to info index
 * @index:   numbew of entwies that match the convewted info index
 * @ss_info: spwectwum infowmation stwuctuwe,
 * wetuwn: Bios pawsew wesuwt code
 */
static enum bp_wesuwt bios_pawsew_get_spwead_spectwum_info(
	stwuct dc_bios *dcb,
	enum as_signaw_type signaw,
	uint32_t index,
	stwuct spwead_spectwum_info *ss_info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!ss_info) /* check fow bad input */
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
						DATA_TABWES(dce_info));
	get_atom_data_tabwe_wevision(headew, &tbw_wevision);

	switch (tbw_wevision.majow) {
	case 4:
		switch (tbw_wevision.minow) {
		case 1:
			wetuwn get_ss_info_v4_1(bp, signaw, index, ss_info);
		case 2:
		case 3:
		case 4:
			wetuwn get_ss_info_v4_2(bp, signaw, index, ss_info);
		case 5:
			wetuwn get_ss_info_v4_5(bp, signaw, index, ss_info);

		defauwt:
			ASSEWT(0);
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	/* thewe can not be mowe then one entwy fow SS Info tabwe */
	wetuwn wesuwt;
}

static enum bp_wesuwt get_soc_bb_info_v4_4(
	stwuct bios_pawsew *bp,
	stwuct bp_soc_bb_info *soc_bb_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_4 *disp_cntw_tbw = NUWW;

	if (!soc_bb_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	if (!DATA_TABWES(smu_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw =  GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_4,
							DATA_TABWES(dce_info));
	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	soc_bb_info->dwam_cwock_change_watency_100ns = disp_cntw_tbw->max_mcwk_chg_wat;
	soc_bb_info->dwam_sw_entew_exit_watency_100ns = disp_cntw_tbw->max_sw_entew_exit_wat;
	soc_bb_info->dwam_sw_exit_watency_100ns = disp_cntw_tbw->max_sw_exit_wat;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_soc_bb_info_v4_5(
	stwuct bios_pawsew *bp,
	stwuct bp_soc_bb_info *soc_bb_info)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_5 *disp_cntw_tbw = NUWW;

	if (!soc_bb_info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw =  GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_5,
							DATA_TABWES(dce_info));
	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	soc_bb_info->dwam_cwock_change_watency_100ns = disp_cntw_tbw->max_mcwk_chg_wat;
	soc_bb_info->dwam_sw_entew_exit_watency_100ns = disp_cntw_tbw->max_sw_entew_exit_wat;
	soc_bb_info->dwam_sw_exit_watency_100ns = disp_cntw_tbw->max_sw_exit_wat;

	wetuwn wesuwt;
}

static enum bp_wesuwt bios_pawsew_get_soc_bb_info(
	stwuct dc_bios *dcb,
	stwuct bp_soc_bb_info *soc_bb_info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!soc_bb_info) /* check fow bad input */
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
						DATA_TABWES(dce_info));
	get_atom_data_tabwe_wevision(headew, &tbw_wevision);

	switch (tbw_wevision.majow) {
	case 4:
		switch (tbw_wevision.minow) {
		case 1:
		case 2:
		case 3:
			bweak;
		case 4:
			wesuwt = get_soc_bb_info_v4_4(bp, soc_bb_info);
			bweak;
		case 5:
			wesuwt = get_soc_bb_info_v4_5(bp, soc_bb_info);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt get_disp_caps_v4_1(
	stwuct bios_pawsew *bp,
	uint8_t *dce_caps)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_1 *disp_cntw_tbw = NUWW;

	if (!dce_caps)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_1,
							DATA_TABWES(dce_info));

	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	*dce_caps = disp_cntw_tbw->dispway_caps;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_disp_caps_v4_2(
	stwuct bios_pawsew *bp,
	uint8_t *dce_caps)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_2 *disp_cntw_tbw = NUWW;

	if (!dce_caps)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_2,
							DATA_TABWES(dce_info));

	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	*dce_caps = disp_cntw_tbw->dispway_caps;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_disp_caps_v4_3(
	stwuct bios_pawsew *bp,
	uint8_t *dce_caps)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_3 *disp_cntw_tbw = NUWW;

	if (!dce_caps)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_3,
							DATA_TABWES(dce_info));

	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	*dce_caps = disp_cntw_tbw->dispway_caps;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_disp_caps_v4_4(
	stwuct bios_pawsew *bp,
	uint8_t *dce_caps)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_4 *disp_cntw_tbw = NUWW;

	if (!dce_caps)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_4,
							DATA_TABWES(dce_info));

	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	*dce_caps = disp_cntw_tbw->dispway_caps;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_disp_caps_v4_5(
	stwuct bios_pawsew *bp,
	uint8_t *dce_caps)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dispway_contwowwew_info_v4_5 *disp_cntw_tbw = NUWW;

	if (!dce_caps)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_BADBIOSTABWE;

	disp_cntw_tbw = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_5,
							DATA_TABWES(dce_info));

	if (!disp_cntw_tbw)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	*dce_caps = disp_cntw_tbw->dispway_caps;

	wetuwn wesuwt;
}

static enum bp_wesuwt bios_pawsew_get_wttpw_intewop(
	stwuct dc_bios *dcb,
	uint8_t *dce_caps)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
						DATA_TABWES(dce_info));
	get_atom_data_tabwe_wevision(headew, &tbw_wevision);
	switch (tbw_wevision.majow) {
	case 4:
		switch (tbw_wevision.minow) {
		case 1:
			wesuwt = get_disp_caps_v4_1(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE);
			bweak;
		case 2:
			wesuwt = get_disp_caps_v4_2(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE);
			bweak;
		case 3:
			wesuwt = get_disp_caps_v4_3(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE);
			bweak;
		case 4:
			wesuwt = get_disp_caps_v4_4(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE);
			bweak;
		case 5:
			wesuwt = get_disp_caps_v4_5(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE);
			bweak;

		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	DC_WOG_BIOS("DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE: %d tbw_wevision.majow = %d tbw_wevision.minow = %d\n", *dce_caps, tbw_wevision.majow, tbw_wevision.minow);
	wetuwn wesuwt;
}

static enum bp_wesuwt bios_pawsew_get_wttpw_caps(
	stwuct dc_bios *dcb,
	uint8_t *dce_caps)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_UNSUPPOWTED;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!DATA_TABWES(dce_info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	*dce_caps  = 0;
	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
						DATA_TABWES(dce_info));
	get_atom_data_tabwe_wevision(headew, &tbw_wevision);
	switch (tbw_wevision.majow) {
	case 4:
		switch (tbw_wevision.minow) {
		case 1:
			wesuwt = get_disp_caps_v4_1(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE);
			bweak;
		case 2:
			wesuwt = get_disp_caps_v4_2(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE);
			bweak;
		case 3:
			wesuwt = get_disp_caps_v4_3(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE);
			bweak;
		case 4:
			wesuwt = get_disp_caps_v4_4(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE);
			bweak;
		case 5:
			wesuwt = get_disp_caps_v4_5(bp, dce_caps);
			*dce_caps = !!(*dce_caps & DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	DC_WOG_BIOS("DCE_INFO_CAPS_WTTPW_SUPPOWT_ENABWE: %d tbw_wevision.majow = %d tbw_wevision.minow = %d\n", *dce_caps, tbw_wevision.majow, tbw_wevision.minow);
	if (dcb->ctx->dc->config.fowce_bios_enabwe_wttpw && *dce_caps == 0) {
		*dce_caps = 1;
		DC_WOG_BIOS("DCE_INFO_CAPS_VBIOS_WTTPW_TWANSPAWENT_ENABWE: fowced enabwed");
	}
	wetuwn wesuwt;
}

static enum bp_wesuwt get_embedded_panew_info_v2_1(
		stwuct bios_pawsew *bp,
		stwuct embedded_panew_info *info)
{
	stwuct wcd_info_v2_1 *wvds;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	if (!DATA_TABWES(wcd_info))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	wvds = GET_IMAGE(stwuct wcd_info_v2_1, DATA_TABWES(wcd_info));

	if (!wvds)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	/* TODO: pwevious vv1_3, shouwd v2_1 */
	if (!((wvds->tabwe_headew.fowmat_wevision == 2)
			&& (wvds->tabwe_headew.content_wevision >= 1)))
		wetuwn BP_WESUWT_UNSUPPOWTED;

	memset(info, 0, sizeof(stwuct embedded_panew_info));

	/* We need to convewt fwom 10KHz units into KHz units */
	info->wcd_timing.pixew_cwk = we16_to_cpu(wvds->wcd_timing.pixcwk) * 10;
	/* usHActive does not incwude bowdews, accowding to VBIOS team */
	info->wcd_timing.howizontaw_addwessabwe = we16_to_cpu(wvds->wcd_timing.h_active);
	/* usHBwanking_Time incwudes bowdews, so we shouwd weawwy be
	 * subtwactingbowdews duing this twanswation, but WVDS genewawwy
	 * doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now.  May need to wevisit if we evew have WVDS with bowdews
	 */
	info->wcd_timing.howizontaw_bwanking_time = we16_to_cpu(wvds->wcd_timing.h_bwanking_time);
	/* usVActive does not incwude bowdews, accowding to VBIOS team*/
	info->wcd_timing.vewticaw_addwessabwe = we16_to_cpu(wvds->wcd_timing.v_active);
	/* usVBwanking_Time incwudes bowdews, so we shouwd weawwy be
	 * subtwacting bowdews duing this twanswation, but WVDS genewawwy
	 * doesn't have bowdews, so we shouwd be okay weaving this as is fow
	 * now. May need to wevisit if we evew have WVDS with bowdews
	 */
	info->wcd_timing.vewticaw_bwanking_time = we16_to_cpu(wvds->wcd_timing.v_bwanking_time);
	info->wcd_timing.howizontaw_sync_offset = we16_to_cpu(wvds->wcd_timing.h_sync_offset);
	info->wcd_timing.howizontaw_sync_width = we16_to_cpu(wvds->wcd_timing.h_sync_width);
	info->wcd_timing.vewticaw_sync_offset = we16_to_cpu(wvds->wcd_timing.v_sync_offset);
	info->wcd_timing.vewticaw_sync_width = we16_to_cpu(wvds->wcd_timing.v_syncwidth);
	info->wcd_timing.howizontaw_bowdew = wvds->wcd_timing.h_bowdew;
	info->wcd_timing.vewticaw_bowdew = wvds->wcd_timing.v_bowdew;

	/* not pwovided by VBIOS */
	info->wcd_timing.misc_info.HOWIZONTAW_CUT_OFF = 0;

	info->wcd_timing.misc_info.H_SYNC_POWAWITY = ~(uint32_t) (wvds->wcd_timing.miscinfo
			& ATOM_HSYNC_POWAWITY);
	info->wcd_timing.misc_info.V_SYNC_POWAWITY = ~(uint32_t) (wvds->wcd_timing.miscinfo
			& ATOM_VSYNC_POWAWITY);

	/* not pwovided by VBIOS */
	info->wcd_timing.misc_info.VEWTICAW_CUT_OFF = 0;

	info->wcd_timing.misc_info.H_WEPWICATION_BY2 = !!(wvds->wcd_timing.miscinfo
			& ATOM_H_WEPWICATIONBY2);
	info->wcd_timing.misc_info.V_WEPWICATION_BY2 = !!(wvds->wcd_timing.miscinfo
			& ATOM_V_WEPWICATIONBY2);
	info->wcd_timing.misc_info.COMPOSITE_SYNC = !!(wvds->wcd_timing.miscinfo
			& ATOM_COMPOSITESYNC);
	info->wcd_timing.misc_info.INTEWWACE = !!(wvds->wcd_timing.miscinfo & ATOM_INTEWWACE);

	/* not pwovided by VBIOS*/
	info->wcd_timing.misc_info.DOUBWE_CWOCK = 0;
	/* not pwovided by VBIOS*/
	info->ss_id = 0;

	info->weawtek_eDPToWVDS = !!(wvds->dpwvdswxid == eDP_TO_WVDS_WEAWTEK_ID);

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt bios_pawsew_get_embedded_panew_info(
		stwuct dc_bios *dcb,
		stwuct embedded_panew_info *info)
{
	stwuct bios_pawsew
	*bp = BP_FWOM_DCB(dcb);
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;

	if (!DATA_TABWES(wcd_info))
		wetuwn BP_WESUWT_FAIWUWE;

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew, DATA_TABWES(wcd_info));

	if (!headew)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	get_atom_data_tabwe_wevision(headew, &tbw_wevision);

	switch (tbw_wevision.majow) {
	case 2:
		switch (tbw_wevision.minow) {
		case 1:
			wetuwn get_embedded_panew_info_v2_1(bp, info);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

static uint32_t get_suppowt_mask_fow_device_id(stwuct device_id device_id)
{
	enum daw_device_type device_type = device_id.device_type;
	uint32_t enum_id = device_id.enum_id;

	switch (device_type) {
	case DEVICE_TYPE_WCD:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DISPWAY_WCD1_SUPPOWT;
		defauwt:
			bweak;
		}
		bweak;
	case DEVICE_TYPE_DFP:
		switch (enum_id) {
		case 1:
			wetuwn ATOM_DISPWAY_DFP1_SUPPOWT;
		case 2:
			wetuwn ATOM_DISPWAY_DFP2_SUPPOWT;
		case 3:
			wetuwn ATOM_DISPWAY_DFP3_SUPPOWT;
		case 4:
			wetuwn ATOM_DISPWAY_DFP4_SUPPOWT;
		case 5:
			wetuwn ATOM_DISPWAY_DFP5_SUPPOWT;
		case 6:
			wetuwn ATOM_DISPWAY_DFP6_SUPPOWT;
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

static boow bios_pawsew_is_device_id_suppowted(
	stwuct dc_bios *dcb,
	stwuct device_id id)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	uint32_t mask = get_suppowt_mask_fow_device_id(id);

	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
	defauwt:
		wetuwn (we16_to_cpu(bp->object_info_tbw.v1_4->suppowteddevices) & mask) != 0;
		bweak;
	case 5:
		wetuwn (we16_to_cpu(bp->object_info_tbw.v1_5->suppowteddevices) & mask) != 0;
		bweak;
	}

	wetuwn fawse;
}

static uint32_t bios_pawsew_get_ss_entwy_numbew(
	stwuct dc_bios *dcb,
	enum as_signaw_type signaw)
{
	/* TODO: DAW2 atomfiwmwawe impwementation does not need this.
	 * why DAW3 need this?
	 */
	wetuwn 1;
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

static enum bp_wesuwt bios_pawsew_pwogwam_cwtc_timing(
	stwuct dc_bios *dcb,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.set_cwtc_timing)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.set_cwtc_timing(bp, bp_pawams);
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

static enum bp_wesuwt bios_pawsew_enabwe_wvtma_contwow(
	stwuct dc_bios *dcb,
	uint8_t uc_pww_on,
	uint8_t pwwseq_instance,
	uint8_t bypass_panew_contwow_wait)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);

	if (!bp->cmd_tbw.enabwe_wvtma_contwow)
		wetuwn BP_WESUWT_FAIWUWE;

	wetuwn bp->cmd_tbw.enabwe_wvtma_contwow(bp, uc_pww_on, pwwseq_instance, bypass_panew_contwow_wait);
}

static boow bios_pawsew_is_accewewated_mode(
	stwuct dc_bios *dcb)
{
	wetuwn bios_is_accewewated_mode(dcb);
}

/**
 * bios_pawsew_set_scwatch_cwiticaw_state - update cwiticaw state bit
 *                                          in VBIOS scwatch wegistew
 *
 * @dcb:   pointew to the DC BIO
 * @state: set ow weset state
 */
static void bios_pawsew_set_scwatch_cwiticaw_state(
	stwuct dc_bios *dcb,
	boow state)
{
	bios_set_scwatch_cwiticaw_state(dcb, state);
}

static enum bp_wesuwt bios_pawsew_get_fiwmwawe_info(
	stwuct dc_bios *dcb,
	stwuct dc_fiwmwawe_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	static enum bp_wesuwt wesuwt = BP_WESUWT_BADBIOSTABWE;
	stwuct atom_common_tabwe_headew *headew;

	stwuct atom_data_wevision wevision;

	if (info && DATA_TABWES(fiwmwaweinfo)) {
		headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
				DATA_TABWES(fiwmwaweinfo));
		get_atom_data_tabwe_wevision(headew, &wevision);
		switch (wevision.majow) {
		case 3:
			switch (wevision.minow) {
			case 1:
				wesuwt = get_fiwmwawe_info_v3_1(bp, info);
				bweak;
			case 2:
			case 3:
				wesuwt = get_fiwmwawe_info_v3_2(bp, info);
				bweak;
			case 4:
				wesuwt = get_fiwmwawe_info_v3_4(bp, info);
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

static enum bp_wesuwt get_fiwmwawe_info_v3_1(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	stwuct atom_fiwmwawe_info_v3_1 *fiwmwawe_info;
	stwuct atom_dispway_contwowwew_info_v4_1 *dce_info = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	fiwmwawe_info = GET_IMAGE(stwuct atom_fiwmwawe_info_v3_1,
			DATA_TABWES(fiwmwaweinfo));

	dce_info = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_1,
			DATA_TABWES(dce_info));

	if (!fiwmwawe_info || !dce_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	/* Pixew cwock pww infowmation. */
	 /* We need to convewt fwom 10KHz units into KHz units */
	info->defauwt_memowy_cwk = fiwmwawe_info->bootup_mcwk_in10khz * 10;
	info->defauwt_engine_cwk = fiwmwawe_info->bootup_scwk_in10khz * 10;

	 /* 27MHz fow Vega10: */
	info->pww_info.cwystaw_fwequency = dce_info->dce_wefcwk_10khz * 10;

	/* Hawdcode fwequency if BIOS gives no DCE Wef Cwk */
	if (info->pww_info.cwystaw_fwequency == 0)
		info->pww_info.cwystaw_fwequency = 27000;
	/*dp_phy_wef_cwk is not cowwect fow atom_dispway_contwowwew_info_v4_2, but we don't use it*/
	info->dp_phy_wef_cwk     = dce_info->dpphy_wefcwk_10khz * 10;
	info->i2c_engine_wef_cwk = dce_info->i2c_engine_wefcwk_10khz * 10;

	/* Get GPU PWW VCO Cwock */

	if (bp->cmd_tbw.get_smu_cwock_info != NUWW) {
		/* VBIOS gives in 10KHz */
		info->smu_gpu_pww_output_fweq =
				bp->cmd_tbw.get_smu_cwock_info(bp, SMU9_SYSPWW0_ID) * 10;
	}

	info->oem_i2c_pwesent = fawse;

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_fiwmwawe_info_v3_2(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	stwuct atom_fiwmwawe_info_v3_2 *fiwmwawe_info;
	stwuct atom_dispway_contwowwew_info_v4_1 *dce_info = NUWW;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision wevision;
	stwuct atom_smu_info_v3_2 *smu_info_v3_2 = NUWW;
	stwuct atom_smu_info_v3_3 *smu_info_v3_3 = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	fiwmwawe_info = GET_IMAGE(stwuct atom_fiwmwawe_info_v3_2,
			DATA_TABWES(fiwmwaweinfo));

	dce_info = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_1,
			DATA_TABWES(dce_info));

	if (!fiwmwawe_info || !dce_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
					DATA_TABWES(smu_info));
	get_atom_data_tabwe_wevision(headew, &wevision);

	if (wevision.minow == 2) {
		/* Vega12 */
		smu_info_v3_2 = GET_IMAGE(stwuct atom_smu_info_v3_2,
							DATA_TABWES(smu_info));
		DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", smu_info_v3_2->gpucwk_ss_pewcentage);
		if (!smu_info_v3_2)
			wetuwn BP_WESUWT_BADBIOSTABWE;

		info->defauwt_engine_cwk = smu_info_v3_2->bootup_dcefcwk_10khz * 10;
	} ewse if (wevision.minow == 3) {
		/* Vega20 */
		smu_info_v3_3 = GET_IMAGE(stwuct atom_smu_info_v3_3,
							DATA_TABWES(smu_info));
		DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", smu_info_v3_3->gpucwk_ss_pewcentage);
		if (!smu_info_v3_3)
			wetuwn BP_WESUWT_BADBIOSTABWE;

		info->defauwt_engine_cwk = smu_info_v3_3->bootup_dcefcwk_10khz * 10;
	}

	 // We need to convewt fwom 10KHz units into KHz units.
	info->defauwt_memowy_cwk = fiwmwawe_info->bootup_mcwk_in10khz * 10;

	 /* 27MHz fow Vega10 & Vega12; 100MHz fow Vega20 */
	info->pww_info.cwystaw_fwequency = dce_info->dce_wefcwk_10khz * 10;
	/* Hawdcode fwequency if BIOS gives no DCE Wef Cwk */
	if (info->pww_info.cwystaw_fwequency == 0) {
		if (wevision.minow == 2)
			info->pww_info.cwystaw_fwequency = 27000;
		ewse if (wevision.minow == 3)
			info->pww_info.cwystaw_fwequency = 100000;
	}
	/*dp_phy_wef_cwk is not cowwect fow atom_dispway_contwowwew_info_v4_2, but we don't use it*/
	info->dp_phy_wef_cwk     = dce_info->dpphy_wefcwk_10khz * 10;
	info->i2c_engine_wef_cwk = dce_info->i2c_engine_wefcwk_10khz * 10;

	/* Get GPU PWW VCO Cwock */
	if (bp->cmd_tbw.get_smu_cwock_info != NUWW) {
		if (wevision.minow == 2)
			info->smu_gpu_pww_output_fweq =
					bp->cmd_tbw.get_smu_cwock_info(bp, SMU9_SYSPWW0_ID) * 10;
		ewse if (wevision.minow == 3)
			info->smu_gpu_pww_output_fweq =
					bp->cmd_tbw.get_smu_cwock_info(bp, SMU11_SYSPWW3_0_ID) * 10;
	}

	if (fiwmwawe_info->boawd_i2c_featuwe_id == 0x2) {
		info->oem_i2c_pwesent = twue;
		info->oem_i2c_obj_id = fiwmwawe_info->boawd_i2c_featuwe_gpio_id;
	} ewse {
		info->oem_i2c_pwesent = fawse;
	}

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_fiwmwawe_info_v3_4(
	stwuct bios_pawsew *bp,
	stwuct dc_fiwmwawe_info *info)
{
	stwuct atom_fiwmwawe_info_v3_4 *fiwmwawe_info;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision wevision;
	stwuct atom_dispway_contwowwew_info_v4_1 *dce_info_v4_1 = NUWW;
	stwuct atom_dispway_contwowwew_info_v4_4 *dce_info_v4_4 = NUWW;

	stwuct atom_smu_info_v3_5 *smu_info_v3_5 = NUWW;
	stwuct atom_dispway_contwowwew_info_v4_5 *dce_info_v4_5 = NUWW;
	stwuct atom_smu_info_v4_0 *smu_info_v4_0 = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	fiwmwawe_info = GET_IMAGE(stwuct atom_fiwmwawe_info_v3_4,
			DATA_TABWES(fiwmwaweinfo));

	if (!fiwmwawe_info)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	memset(info, 0, sizeof(*info));

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
					DATA_TABWES(dce_info));

	get_atom_data_tabwe_wevision(headew, &wevision);

	switch (wevision.majow) {
	case 4:
		switch (wevision.minow) {
		case 5:
			dce_info_v4_5 = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_5,
							DATA_TABWES(dce_info));

			if (!dce_info_v4_5)
				wetuwn BP_WESUWT_BADBIOSTABWE;

			 /* 100MHz expected */
			info->pww_info.cwystaw_fwequency = dce_info_v4_5->dce_wefcwk_10khz * 10;
			info->dp_phy_wef_cwk             = dce_info_v4_5->dpphy_wefcwk_10khz * 10;
			 /* 50MHz expected */
			info->i2c_engine_wef_cwk         = dce_info_v4_5->i2c_engine_wefcwk_10khz * 10;

			/* Fow DCN32/321 Dispway PWW VCO Fwequency fwom dce_info_v4_5 may not be wewiabwe */
			bweak;

		case 4:
			dce_info_v4_4 = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_4,
							DATA_TABWES(dce_info));

			if (!dce_info_v4_4)
				wetuwn BP_WESUWT_BADBIOSTABWE;

			/* 100MHz expected */
			info->pww_info.cwystaw_fwequency = dce_info_v4_4->dce_wefcwk_10khz * 10;
			info->dp_phy_wef_cwk             = dce_info_v4_4->dpphy_wefcwk_10khz * 10;
			/* 50MHz expected */
			info->i2c_engine_wef_cwk         = dce_info_v4_4->i2c_engine_wefcwk_10khz * 10;

			/* Get SMU Dispway PWW VCO Fwequency in KHz*/
			info->smu_gpu_pww_output_fweq =	dce_info_v4_4->dispcwk_pww_vco_fweq * 10;
			bweak;

		defauwt:
			/* shouwd not come hewe, keep as backup, as was befowe */
			dce_info_v4_1 = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_1,
							DATA_TABWES(dce_info));

			if (!dce_info_v4_1)
				wetuwn BP_WESUWT_BADBIOSTABWE;

			info->pww_info.cwystaw_fwequency = dce_info_v4_1->dce_wefcwk_10khz * 10;
			info->dp_phy_wef_cwk             = dce_info_v4_1->dpphy_wefcwk_10khz * 10;
			info->i2c_engine_wef_cwk         = dce_info_v4_1->i2c_engine_wefcwk_10khz * 10;
			bweak;
		}
		bweak;

	defauwt:
		ASSEWT(0);
		bweak;
	}

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
					DATA_TABWES(smu_info));
	get_atom_data_tabwe_wevision(headew, &wevision);

	switch (wevision.majow) {
	case 3:
		switch (wevision.minow) {
		case 5:
			smu_info_v3_5 = GET_IMAGE(stwuct atom_smu_info_v3_5,
							DATA_TABWES(smu_info));

			if (!smu_info_v3_5)
				wetuwn BP_WESUWT_BADBIOSTABWE;
			DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", smu_info_v3_5->gpucwk_ss_pewcentage);
			info->defauwt_engine_cwk = smu_info_v3_5->bootup_dcefcwk_10khz * 10;
			bweak;

		defauwt:
			bweak;
		}
		bweak;

	case 4:
		switch (wevision.minow) {
		case 0:
			smu_info_v4_0 = GET_IMAGE(stwuct atom_smu_info_v4_0,
							DATA_TABWES(smu_info));

			if (!smu_info_v4_0)
				wetuwn BP_WESUWT_BADBIOSTABWE;

			/* Fow DCN32/321 bootup DCFCWK fwom smu_info_v4_0 may not be wewiabwe */
			bweak;

		defauwt:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	 // We need to convewt fwom 10KHz units into KHz units.
	info->defauwt_memowy_cwk = fiwmwawe_info->bootup_mcwk_in10khz * 10;

	if (fiwmwawe_info->boawd_i2c_featuwe_id == 0x2) {
		info->oem_i2c_pwesent = twue;
		info->oem_i2c_obj_id = fiwmwawe_info->boawd_i2c_featuwe_gpio_id;
	} ewse {
		info->oem_i2c_pwesent = fawse;
	}

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt bios_pawsew_get_encodew_cap_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id,
	stwuct bp_encodew_cap_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_dispway_object_path_v2 *object;
	stwuct atom_encodew_caps_wecowd *wecowd = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

#if defined(CONFIG_DWM_AMD_DC_FP)
	/* encodew cap wecowd not avaiwabwe in v1_5 */
	if (bp->object_info_tbw.wevision.minow == 5)
		wetuwn BP_WESUWT_NOWECOWD;
#endif

	object = get_bios_object(bp, object_id);

	if (!object)
		wetuwn BP_WESUWT_BADINPUT;

	wecowd = get_encodew_cap_wecowd(bp, object);
	if (!wecowd)
		wetuwn BP_WESUWT_NOWECOWD;
	DC_WOG_BIOS("wecowd->encodewcaps 0x%x fow object_id 0x%x", wecowd->encodewcaps, object_id.id);

	info->DP_HBW2_CAP = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_HBW2) ? 1 : 0;
	info->DP_HBW2_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_HBW2_EN) ? 1 : 0;
	info->DP_HBW3_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_HBW3_EN) ? 1 : 0;
	info->HDMI_6GB_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_HDMI6Gbps_EN) ? 1 : 0;
	info->IS_DP2_CAPABWE = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_DP2) ? 1 : 0;
	info->DP_UHBW10_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_UHBW10_EN) ? 1 : 0;
	info->DP_UHBW13_5_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_UHBW13_5_EN) ? 1 : 0;
	info->DP_UHBW20_EN = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_UHBW20_EN) ? 1 : 0;
	info->DP_IS_USB_C = (wecowd->encodewcaps &
			ATOM_ENCODEW_CAP_WECOWD_USB_C_TYPE) ? 1 : 0;
	DC_WOG_BIOS("\t info->DP_IS_USB_C %d", info->DP_IS_USB_C);

	wetuwn BP_WESUWT_OK;
}


static stwuct atom_encodew_caps_wecowd *get_encodew_cap_wecowd(
	stwuct bios_pawsew *bp,
	stwuct atom_dispway_object_path_v2 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = object->encodew_wecowdoffset + bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		offset += headew->wecowd_size;

		if (headew->wecowd_type == WAST_WECOWD_TYPE ||
				!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type != ATOM_ENCODEW_CAP_WECOWD_TYPE)
			continue;

		if (sizeof(stwuct atom_encodew_caps_wecowd) <=
							headew->wecowd_size)
			wetuwn (stwuct atom_encodew_caps_wecowd *)headew;
	}

	wetuwn NUWW;
}

static stwuct atom_disp_connectow_caps_wecowd *get_disp_connectow_caps_wecowd(
	stwuct bios_pawsew *bp,
	stwuct atom_dispway_object_path_v2 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = object->disp_wecowdoffset + bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		offset += headew->wecowd_size;

		if (headew->wecowd_type == WAST_WECOWD_TYPE ||
				!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type != ATOM_DISP_CONNECTOW_CAPS_WECOWD_TYPE)
			continue;

		if (sizeof(stwuct atom_disp_connectow_caps_wecowd) <=
							headew->wecowd_size)
			wetuwn (stwuct atom_disp_connectow_caps_wecowd *)headew;
	}

	wetuwn NUWW;
}

static stwuct atom_connectow_caps_wecowd *get_connectow_caps_wecowd(stwuct bios_pawsew *bp,
								    stwuct atom_dispway_object_path_v3 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = object->disp_wecowdoffset + bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		offset += headew->wecowd_size;

		if (headew->wecowd_type == ATOM_WECOWD_END_TYPE ||
				!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type != ATOM_CONNECTOW_CAP_WECOWD_TYPE)
			continue;

		if (sizeof(stwuct atom_connectow_caps_wecowd) <= headew->wecowd_size)
			wetuwn (stwuct atom_connectow_caps_wecowd *)headew;
	}

	wetuwn NUWW;
}

static enum bp_wesuwt bios_pawsew_get_disp_connectow_caps_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id,
	stwuct bp_disp_connectow_caps_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_dispway_object_path_v2 *object;
	stwuct atom_dispway_object_path_v3 *object_path_v3;
	stwuct atom_connectow_caps_wecowd *wecowd_path_v3;
	stwuct atom_disp_connectow_caps_wecowd *wecowd = NUWW;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
		defauwt:
			object = get_bios_object(bp, object_id);

			if (!object)
				wetuwn BP_WESUWT_BADINPUT;

			wecowd = get_disp_connectow_caps_wecowd(bp, object);
			if (!wecowd)
				wetuwn BP_WESUWT_NOWECOWD;

			info->INTEWNAW_DISPWAY =
				(wecowd->connectcaps & ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY) ? 1 : 0;
			info->INTEWNAW_DISPWAY_BW =
				(wecowd->connectcaps & ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY_BW) ? 1 : 0;
			bweak;
	case 5:
		object_path_v3 = get_bios_object_fwom_path_v3(bp, object_id);

		if (!object_path_v3)
			wetuwn BP_WESUWT_BADINPUT;

		wecowd_path_v3 = get_connectow_caps_wecowd(bp, object_path_v3);
		if (!wecowd_path_v3)
			wetuwn BP_WESUWT_NOWECOWD;

		info->INTEWNAW_DISPWAY = (wecowd_path_v3->connectow_caps & ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY)
									? 1 : 0;
		info->INTEWNAW_DISPWAY_BW = (wecowd_path_v3->connectow_caps & ATOM_CONNECTOW_CAP_INTEWNAW_DISPWAY_BW)
										? 1 : 0;
		bweak;
	}

	wetuwn BP_WESUWT_OK;
}

static stwuct atom_connectow_speed_wecowd *get_connectow_speed_cap_wecowd(stwuct bios_pawsew *bp,
									  stwuct atom_dispway_object_path_v3 *object)
{
	stwuct atom_common_wecowd_headew *headew;
	uint32_t offset;

	if (!object) {
		BWEAK_TO_DEBUGGEW(); /* Invawid object */
		wetuwn NUWW;
	}

	offset = object->disp_wecowdoffset + bp->object_info_tbw_offset;

	fow (;;) {
		headew = GET_IMAGE(stwuct atom_common_wecowd_headew, offset);

		if (!headew)
			wetuwn NUWW;

		offset += headew->wecowd_size;

		if (headew->wecowd_type == ATOM_WECOWD_END_TYPE ||
				!headew->wecowd_size)
			bweak;

		if (headew->wecowd_type != ATOM_CONNECTOW_SPEED_UPTO)
			continue;

		if (sizeof(stwuct atom_connectow_speed_wecowd) <= headew->wecowd_size)
			wetuwn (stwuct atom_connectow_speed_wecowd *)headew;
	}

	wetuwn NUWW;
}

static enum bp_wesuwt bios_pawsew_get_connectow_speed_cap_info(
	stwuct dc_bios *dcb,
	stwuct gwaphics_object_id object_id,
	stwuct bp_connectow_speed_cap_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	stwuct atom_dispway_object_path_v3 *object_path_v3;
	//stwuct atom_connectow_speed_wecowd *wecowd = NUWW;
	stwuct atom_connectow_speed_wecowd *wecowd;

	if (!info)
		wetuwn BP_WESUWT_BADINPUT;

	object_path_v3 = get_bios_object_fwom_path_v3(bp, object_id);

	if (!object_path_v3)
		wetuwn BP_WESUWT_BADINPUT;

	wecowd = get_connectow_speed_cap_wecowd(bp, object_path_v3);
	if (!wecowd)
		wetuwn BP_WESUWT_NOWECOWD;

	info->DP_HBW2_EN = (wecowd->connectow_max_speed >= 5400) ? 1 : 0;
	info->DP_HBW3_EN = (wecowd->connectow_max_speed >= 8100) ? 1 : 0;
	info->HDMI_6GB_EN = (wecowd->connectow_max_speed >= 5940) ? 1 : 0;
	info->DP_UHBW10_EN = (wecowd->connectow_max_speed >= 10000) ? 1 : 0;
	info->DP_UHBW13_5_EN = (wecowd->connectow_max_speed >= 13500) ? 1 : 0;
	info->DP_UHBW20_EN = (wecowd->connectow_max_speed >= 20000) ? 1 : 0;
	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_vwam_info_v23(
	stwuct bios_pawsew *bp,
	stwuct dc_vwam_info *info)
{
	stwuct atom_vwam_info_headew_v2_3 *info_v23;
	static enum bp_wesuwt wesuwt = BP_WESUWT_OK;

	info_v23 = GET_IMAGE(stwuct atom_vwam_info_headew_v2_3,
						DATA_TABWES(vwam_info));

	if (info_v23 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->num_chans = info_v23->vwam_moduwe[0].channew_num;
	info->dwam_channew_width_bytes = (1 << info_v23->vwam_moduwe[0].channew_width) / 8;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_vwam_info_v24(
	stwuct bios_pawsew *bp,
	stwuct dc_vwam_info *info)
{
	stwuct atom_vwam_info_headew_v2_4 *info_v24;
	static enum bp_wesuwt wesuwt = BP_WESUWT_OK;

	info_v24 = GET_IMAGE(stwuct atom_vwam_info_headew_v2_4,
						DATA_TABWES(vwam_info));

	if (info_v24 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->num_chans = info_v24->vwam_moduwe[0].channew_num;
	info->dwam_channew_width_bytes = (1 << info_v24->vwam_moduwe[0].channew_width) / 8;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_vwam_info_v25(
	stwuct bios_pawsew *bp,
	stwuct dc_vwam_info *info)
{
	stwuct atom_vwam_info_headew_v2_5 *info_v25;
	static enum bp_wesuwt wesuwt = BP_WESUWT_OK;

	info_v25 = GET_IMAGE(stwuct atom_vwam_info_headew_v2_5,
						DATA_TABWES(vwam_info));

	if (info_v25 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->num_chans = info_v25->vwam_moduwe[0].channew_num;
	info->dwam_channew_width_bytes = (1 << info_v25->vwam_moduwe[0].channew_width) / 8;

	wetuwn wesuwt;
}

static enum bp_wesuwt get_vwam_info_v30(
	stwuct bios_pawsew *bp,
	stwuct dc_vwam_info *info)
{
	stwuct atom_vwam_info_headew_v3_0 *info_v30;
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;

	info_v30 = GET_IMAGE(stwuct atom_vwam_info_headew_v3_0,
						DATA_TABWES(vwam_info));

	if (info_v30 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->num_chans = info_v30->channew_num;
	info->dwam_channew_width_bytes = (1 << info_v30->channew_width) / 8;

	wetuwn wesuwt;
}

/*
 * get_integwated_info_v11
 *
 * @bwief
 * Get V8 integwated BIOS infowmation
 *
 * @pawam
 * bios_pawsew *bp - [in]BIOS pawsew handwew to get mastew data tabwe
 * integwated_info *info - [out] stowe and output integwated info
 *
 * @wetuwn
 * static enum bp_wesuwt - BP_WESUWT_OK if infowmation is avaiwabwe,
 *                  BP_WESUWT_BADBIOSTABWE othewwise.
 */
static enum bp_wesuwt get_integwated_info_v11(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	stwuct atom_integwated_system_info_v1_11 *info_v11;
	uint32_t i;

	info_v11 = GET_IMAGE(stwuct atom_integwated_system_info_v1_11,
					DATA_TABWES(integwatedsysteminfo));

	DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", info_v11->gpucwk_ss_pewcentage);
	if (info_v11 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->gpu_cap_info =
	we32_to_cpu(info_v11->gpucapinfo);
	/*
	* system_config: Bit[0] = 0 : PCIE powew gating disabwed
	*                       = 1 : PCIE powew gating enabwed
	*                Bit[1] = 0 : DDW-PWW shut down disabwed
	*                       = 1 : DDW-PWW shut down enabwed
	*                Bit[2] = 0 : DDW-PWW powew down disabwed
	*                       = 1 : DDW-PWW powew down enabwed
	*/
	info->system_config = we32_to_cpu(info_v11->system_config);
	info->cpu_cap_info = we32_to_cpu(info_v11->cpucapinfo);
	info->memowy_type = info_v11->memowytype;
	info->ma_channew_numbew = info_v11->umachannewnumbew;
	info->wvds_ss_pewcentage =
	we16_to_cpu(info_v11->wvds_ss_pewcentage);
	info->dp_ss_contwow =
	we16_to_cpu(info_v11->wesewved1);
	info->wvds_sspwead_wate_in_10hz =
	we16_to_cpu(info_v11->wvds_ss_wate_10hz);
	info->hdmi_ss_pewcentage =
	we16_to_cpu(info_v11->hdmi_ss_pewcentage);
	info->hdmi_sspwead_wate_in_10hz =
	we16_to_cpu(info_v11->hdmi_ss_wate_10hz);
	info->dvi_ss_pewcentage =
	we16_to_cpu(info_v11->dvi_ss_pewcentage);
	info->dvi_sspwead_wate_in_10_hz =
	we16_to_cpu(info_v11->dvi_ss_wate_10hz);
	info->wvds_misc = info_v11->wvds_misc;
	fow (i = 0; i < NUMBEW_OF_UCHAW_FOW_GUID; ++i) {
		info->ext_disp_conn_info.gu_id[i] =
				info_v11->extdispconninfo.guid[i];
	}

	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; ++i) {
		info->ext_disp_conn_info.path[i].device_connectow_id =
		object_id_fwom_bios_object_id(
		we16_to_cpu(info_v11->extdispconninfo.path[i].connectowobjid));

		info->ext_disp_conn_info.path[i].ext_encodew_obj_id =
		object_id_fwom_bios_object_id(
			we16_to_cpu(
			info_v11->extdispconninfo.path[i].ext_encodew_objid));

		info->ext_disp_conn_info.path[i].device_tag =
			we16_to_cpu(
				info_v11->extdispconninfo.path[i].device_tag);
		info->ext_disp_conn_info.path[i].device_acpi_enum =
		we16_to_cpu(
			info_v11->extdispconninfo.path[i].device_acpi_enum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index =
			info_v11->extdispconninfo.path[i].auxddcwut_index;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index =
			info_v11->extdispconninfo.path[i].hpdwut_index;
		info->ext_disp_conn_info.path[i].channew_mapping.waw =
			info_v11->extdispconninfo.path[i].channewmapping;
		info->ext_disp_conn_info.path[i].caps =
				we16_to_cpu(info_v11->extdispconninfo.path[i].caps);
	}
	info->ext_disp_conn_info.checksum =
	info_v11->extdispconninfo.checksum;

	info->dp0_ext_hdmi_swv_addw = info_v11->dp0_wetimew_set.HdmiSwvAddw;
	info->dp0_ext_hdmi_weg_num = info_v11->dp0_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp0_ext_hdmi_weg_num; i++) {
		info->dp0_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v11->dp0_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp0_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v11->dp0_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp0_ext_hdmi_6g_weg_num = info_v11->dp0_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp0_ext_hdmi_6g_weg_num; i++) {
		info->dp0_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v11->dp0_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp0_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v11->dp0_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}

	info->dp1_ext_hdmi_swv_addw = info_v11->dp1_wetimew_set.HdmiSwvAddw;
	info->dp1_ext_hdmi_weg_num = info_v11->dp1_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp1_ext_hdmi_weg_num; i++) {
		info->dp1_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v11->dp1_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp1_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v11->dp1_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp1_ext_hdmi_6g_weg_num = info_v11->dp1_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp1_ext_hdmi_6g_weg_num; i++) {
		info->dp1_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v11->dp1_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp1_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v11->dp1_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}

	info->dp2_ext_hdmi_swv_addw = info_v11->dp2_wetimew_set.HdmiSwvAddw;
	info->dp2_ext_hdmi_weg_num = info_v11->dp2_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp2_ext_hdmi_weg_num; i++) {
		info->dp2_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v11->dp2_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp2_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v11->dp2_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp2_ext_hdmi_6g_weg_num = info_v11->dp2_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp2_ext_hdmi_6g_weg_num; i++) {
		info->dp2_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v11->dp2_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp2_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v11->dp2_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}

	info->dp3_ext_hdmi_swv_addw = info_v11->dp3_wetimew_set.HdmiSwvAddw;
	info->dp3_ext_hdmi_weg_num = info_v11->dp3_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp3_ext_hdmi_weg_num; i++) {
		info->dp3_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v11->dp3_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp3_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v11->dp3_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp3_ext_hdmi_6g_weg_num = info_v11->dp3_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp3_ext_hdmi_6g_weg_num; i++) {
		info->dp3_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v11->dp3_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp3_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v11->dp3_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}


	/** TODO - weview **/
	#if 0
	info->boot_up_engine_cwock = we32_to_cpu(info_v11->uwBootUpEngineCwock)
									* 10;
	info->dentist_vco_fweq = we32_to_cpu(info_v11->uwDentistVCOFweq) * 10;
	info->boot_up_uma_cwock = we32_to_cpu(info_v8->uwBootUpUMACwock) * 10;

	fow (i = 0; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->disp_cwk_vowtage[i].max_suppowted_cwk =
		we32_to_cpu(info_v11->sDISPCWK_Vowtage[i].
			uwMaximumSuppowtedCWK) * 10;
		info->disp_cwk_vowtage[i].vowtage_index =
		we32_to_cpu(info_v11->sDISPCWK_Vowtage[i].uwVowtageIndex);
	}

	info->boot_up_weq_dispway_vectow =
			we32_to_cpu(info_v11->uwBootUpWeqDispwayVectow);
	info->boot_up_nb_vowtage =
			we16_to_cpu(info_v11->usBootUpNBVowtage);
	info->ext_disp_conn_info_offset =
			we16_to_cpu(info_v11->usExtDispConnInfoOffset);
	info->gmc_westowe_weset_time =
			we32_to_cpu(info_v11->uwGMCWestoweWesetTime);
	info->minimum_n_cwk =
			we32_to_cpu(info_v11->uwNbpStateNCwkFweq[0]);
	fow (i = 1; i < 4; ++i)
		info->minimum_n_cwk =
				info->minimum_n_cwk <
				we32_to_cpu(info_v11->uwNbpStateNCwkFweq[i]) ?
				info->minimum_n_cwk : we32_to_cpu(
					info_v11->uwNbpStateNCwkFweq[i]);

	info->idwe_n_cwk = we32_to_cpu(info_v11->uwIdweNCwk);
	info->ddw_dww_powew_up_time =
	    we32_to_cpu(info_v11->uwDDW_DWW_PowewUpTime);
	info->ddw_pww_powew_up_time =
		we32_to_cpu(info_v11->uwDDW_PWW_PowewUpTime);
	info->pcie_cwk_ss_type = we16_to_cpu(info_v11->usPCIECwkSSType);
	info->max_wvds_pcwk_fweq_in_singwe_wink =
		we16_to_cpu(info_v11->usMaxWVDSPcwkFweqInSingweWink);
	info->max_wvds_pcwk_fweq_in_singwe_wink =
		we16_to_cpu(info_v11->usMaxWVDSPcwkFweqInSingweWink);
	info->wvds_pww_on_seq_dig_on_to_de_in_4ms =
		info_v11->ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
	info->wvds_pww_on_seq_de_to_vawy_bw_in_4ms =
		info_v11->ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
	info->wvds_pww_on_seq_vawy_bw_to_bwon_in_4ms =
		info_v11->ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
	info->wvds_pww_off_seq_vawy_bw_to_de_in4ms =
		info_v11->ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
	info->wvds_pww_off_seq_de_to_dig_on_in4ms =
		info_v11->ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
	info->wvds_pww_off_seq_bwon_to_vawy_bw_in_4ms =
		info_v11->ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
	info->wvds_off_to_on_deway_in_4ms =
		info_v11->ucWVDSOffToOnDeway_in4Ms;
	info->wvds_bit_depth_contwow_vaw =
		we32_to_cpu(info_v11->uwWCDBitDepthContwowVaw);

	fow (i = 0; i < NUMBEW_OF_AVAIWABWE_SCWK; ++i) {
		/* Convewt [10KHz] into [KHz] */
		info->avaiw_s_cwk[i].suppowted_s_cwk =
			we32_to_cpu(info_v11->sAvaiw_SCWK[i].uwSuppowtedSCWK)
									* 10;
		info->avaiw_s_cwk[i].vowtage_index =
			we16_to_cpu(info_v11->sAvaiw_SCWK[i].usVowtageIndex);
		info->avaiw_s_cwk[i].vowtage_id =
			we16_to_cpu(info_v11->sAvaiw_SCWK[i].usVowtageID);
	}
	#endif /* TODO*/

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_integwated_info_v2_1(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	stwuct atom_integwated_system_info_v2_1 *info_v2_1;
	uint32_t i;

	info_v2_1 = GET_IMAGE(stwuct atom_integwated_system_info_v2_1,
					DATA_TABWES(integwatedsysteminfo));
	DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", info_v2_1->gpucwk_ss_pewcentage);

	if (info_v2_1 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->gpu_cap_info =
	we32_to_cpu(info_v2_1->gpucapinfo);
	/*
	* system_config: Bit[0] = 0 : PCIE powew gating disabwed
	*                       = 1 : PCIE powew gating enabwed
	*                Bit[1] = 0 : DDW-PWW shut down disabwed
	*                       = 1 : DDW-PWW shut down enabwed
	*                Bit[2] = 0 : DDW-PWW powew down disabwed
	*                       = 1 : DDW-PWW powew down enabwed
	*/
	info->system_config = we32_to_cpu(info_v2_1->system_config);
	info->cpu_cap_info = we32_to_cpu(info_v2_1->cpucapinfo);
	info->memowy_type = info_v2_1->memowytype;
	info->ma_channew_numbew = info_v2_1->umachannewnumbew;
	info->dp_ss_contwow =
		we16_to_cpu(info_v2_1->wesewved1);

	fow (i = 0; i < NUMBEW_OF_UCHAW_FOW_GUID; ++i) {
		info->ext_disp_conn_info.gu_id[i] =
				info_v2_1->extdispconninfo.guid[i];
	}

	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; ++i) {
		info->ext_disp_conn_info.path[i].device_connectow_id =
		object_id_fwom_bios_object_id(
		we16_to_cpu(info_v2_1->extdispconninfo.path[i].connectowobjid));

		info->ext_disp_conn_info.path[i].ext_encodew_obj_id =
		object_id_fwom_bios_object_id(
			we16_to_cpu(
			info_v2_1->extdispconninfo.path[i].ext_encodew_objid));

		info->ext_disp_conn_info.path[i].device_tag =
			we16_to_cpu(
				info_v2_1->extdispconninfo.path[i].device_tag);
		info->ext_disp_conn_info.path[i].device_acpi_enum =
		we16_to_cpu(
			info_v2_1->extdispconninfo.path[i].device_acpi_enum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index =
			info_v2_1->extdispconninfo.path[i].auxddcwut_index;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index =
			info_v2_1->extdispconninfo.path[i].hpdwut_index;
		info->ext_disp_conn_info.path[i].channew_mapping.waw =
			info_v2_1->extdispconninfo.path[i].channewmapping;
		info->ext_disp_conn_info.path[i].caps =
				we16_to_cpu(info_v2_1->extdispconninfo.path[i].caps);
	}

	info->ext_disp_conn_info.checksum =
		info_v2_1->extdispconninfo.checksum;
	info->dp0_ext_hdmi_swv_addw = info_v2_1->dp0_wetimew_set.HdmiSwvAddw;
	info->dp0_ext_hdmi_weg_num = info_v2_1->dp0_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp0_ext_hdmi_weg_num; i++) {
		info->dp0_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v2_1->dp0_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp0_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp0_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp0_ext_hdmi_6g_weg_num = info_v2_1->dp0_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp0_ext_hdmi_6g_weg_num; i++) {
		info->dp0_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v2_1->dp0_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp0_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp0_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}
	info->dp1_ext_hdmi_swv_addw = info_v2_1->dp1_wetimew_set.HdmiSwvAddw;
	info->dp1_ext_hdmi_weg_num = info_v2_1->dp1_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp1_ext_hdmi_weg_num; i++) {
		info->dp1_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v2_1->dp1_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp1_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp1_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp1_ext_hdmi_6g_weg_num = info_v2_1->dp1_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp1_ext_hdmi_6g_weg_num; i++) {
		info->dp1_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v2_1->dp1_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp1_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp1_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}
	info->dp2_ext_hdmi_swv_addw = info_v2_1->dp2_wetimew_set.HdmiSwvAddw;
	info->dp2_ext_hdmi_weg_num = info_v2_1->dp2_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp2_ext_hdmi_weg_num; i++) {
		info->dp2_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v2_1->dp2_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp2_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp2_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp2_ext_hdmi_6g_weg_num = info_v2_1->dp2_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp2_ext_hdmi_6g_weg_num; i++) {
		info->dp2_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v2_1->dp2_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp2_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp2_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}
	info->dp3_ext_hdmi_swv_addw = info_v2_1->dp3_wetimew_set.HdmiSwvAddw;
	info->dp3_ext_hdmi_weg_num = info_v2_1->dp3_wetimew_set.HdmiWegNum;
	fow (i = 0; i < info->dp3_ext_hdmi_weg_num; i++) {
		info->dp3_ext_hdmi_weg_settings[i].i2c_weg_index =
				info_v2_1->dp3_wetimew_set.HdmiWegSetting[i].ucI2cWegIndex;
		info->dp3_ext_hdmi_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp3_wetimew_set.HdmiWegSetting[i].ucI2cWegVaw;
	}
	info->dp3_ext_hdmi_6g_weg_num = info_v2_1->dp3_wetimew_set.Hdmi6GWegNum;
	fow (i = 0; i < info->dp3_ext_hdmi_6g_weg_num; i++) {
		info->dp3_ext_hdmi_6g_weg_settings[i].i2c_weg_index =
				info_v2_1->dp3_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegIndex;
		info->dp3_ext_hdmi_6g_weg_settings[i].i2c_weg_vaw =
				info_v2_1->dp3_wetimew_set.Hdmi6GhzWegSetting[i].ucI2cWegVaw;
	}

	info->edp1_info.edp_backwight_pwm_hz =
	we16_to_cpu(info_v2_1->edp1_info.edp_backwight_pwm_hz);
	info->edp1_info.edp_ss_pewcentage =
	we16_to_cpu(info_v2_1->edp1_info.edp_ss_pewcentage);
	info->edp1_info.edp_ss_wate_10hz =
	we16_to_cpu(info_v2_1->edp1_info.edp_ss_wate_10hz);
	info->edp1_info.edp_pww_on_off_deway =
		info_v2_1->edp1_info.edp_pww_on_off_deway;
	info->edp1_info.edp_pww_on_vawy_bw_to_bwon =
		info_v2_1->edp1_info.edp_pww_on_vawy_bw_to_bwon;
	info->edp1_info.edp_pww_down_bwoff_to_vawy_bwoff =
		info_v2_1->edp1_info.edp_pww_down_bwoff_to_vawy_bwoff;
	info->edp1_info.edp_panew_bpc =
		info_v2_1->edp1_info.edp_panew_bpc;
	info->edp1_info.edp_bootup_bw_wevew = info_v2_1->edp1_info.edp_bootup_bw_wevew;

	info->edp2_info.edp_backwight_pwm_hz =
	we16_to_cpu(info_v2_1->edp2_info.edp_backwight_pwm_hz);
	info->edp2_info.edp_ss_pewcentage =
	we16_to_cpu(info_v2_1->edp2_info.edp_ss_pewcentage);
	info->edp2_info.edp_ss_wate_10hz =
	we16_to_cpu(info_v2_1->edp2_info.edp_ss_wate_10hz);
	info->edp2_info.edp_pww_on_off_deway =
		info_v2_1->edp2_info.edp_pww_on_off_deway;
	info->edp2_info.edp_pww_on_vawy_bw_to_bwon =
		info_v2_1->edp2_info.edp_pww_on_vawy_bw_to_bwon;
	info->edp2_info.edp_pww_down_bwoff_to_vawy_bwoff =
		info_v2_1->edp2_info.edp_pww_down_bwoff_to_vawy_bwoff;
	info->edp2_info.edp_panew_bpc =
		info_v2_1->edp2_info.edp_panew_bpc;
	info->edp2_info.edp_bootup_bw_wevew =
		info_v2_1->edp2_info.edp_bootup_bw_wevew;

	wetuwn BP_WESUWT_OK;
}

static enum bp_wesuwt get_integwated_info_v2_2(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	stwuct atom_integwated_system_info_v2_2 *info_v2_2;
	uint32_t i;

	info_v2_2 = GET_IMAGE(stwuct atom_integwated_system_info_v2_2,
					DATA_TABWES(integwatedsysteminfo));

	DC_WOG_BIOS("gpucwk_ss_pewcentage (unit of 0.001 pewcent): %d\n", info_v2_2->gpucwk_ss_pewcentage);

	if (info_v2_2 == NUWW)
		wetuwn BP_WESUWT_BADBIOSTABWE;

	info->gpu_cap_info =
	we32_to_cpu(info_v2_2->gpucapinfo);
	/*
	* system_config: Bit[0] = 0 : PCIE powew gating disabwed
	*                       = 1 : PCIE powew gating enabwed
	*                Bit[1] = 0 : DDW-PWW shut down disabwed
	*                       = 1 : DDW-PWW shut down enabwed
	*                Bit[2] = 0 : DDW-PWW powew down disabwed
	*                       = 1 : DDW-PWW powew down enabwed
	*/
	info->system_config = we32_to_cpu(info_v2_2->system_config);
	info->cpu_cap_info = we32_to_cpu(info_v2_2->cpucapinfo);
	info->memowy_type = info_v2_2->memowytype;
	info->ma_channew_numbew = info_v2_2->umachannewnumbew;
	info->dp_ss_contwow =
		we16_to_cpu(info_v2_2->wesewved1);
	info->gpucwk_ss_pewcentage = info_v2_2->gpucwk_ss_pewcentage;
	info->gpucwk_ss_type = info_v2_2->gpucwk_ss_type;

	fow (i = 0; i < NUMBEW_OF_UCHAW_FOW_GUID; ++i) {
		info->ext_disp_conn_info.gu_id[i] =
				info_v2_2->extdispconninfo.guid[i];
	}

	fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; ++i) {
		info->ext_disp_conn_info.path[i].device_connectow_id =
		object_id_fwom_bios_object_id(
		we16_to_cpu(info_v2_2->extdispconninfo.path[i].connectowobjid));

		info->ext_disp_conn_info.path[i].ext_encodew_obj_id =
		object_id_fwom_bios_object_id(
			we16_to_cpu(
			info_v2_2->extdispconninfo.path[i].ext_encodew_objid));

		info->ext_disp_conn_info.path[i].device_tag =
			we16_to_cpu(
				info_v2_2->extdispconninfo.path[i].device_tag);
		info->ext_disp_conn_info.path[i].device_acpi_enum =
		we16_to_cpu(
			info_v2_2->extdispconninfo.path[i].device_acpi_enum);
		info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index =
			info_v2_2->extdispconninfo.path[i].auxddcwut_index;
		info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index =
			info_v2_2->extdispconninfo.path[i].hpdwut_index;
		info->ext_disp_conn_info.path[i].channew_mapping.waw =
			info_v2_2->extdispconninfo.path[i].channewmapping;
		info->ext_disp_conn_info.path[i].caps =
				we16_to_cpu(info_v2_2->extdispconninfo.path[i].caps);
	}

	info->ext_disp_conn_info.checksum =
		info_v2_2->extdispconninfo.checksum;
	info->ext_disp_conn_info.fixdpvowtageswing =
		info_v2_2->extdispconninfo.fixdpvowtageswing;

	info->edp1_info.edp_backwight_pwm_hz =
	we16_to_cpu(info_v2_2->edp1_info.edp_backwight_pwm_hz);
	info->edp1_info.edp_ss_pewcentage =
	we16_to_cpu(info_v2_2->edp1_info.edp_ss_pewcentage);
	info->edp1_info.edp_ss_wate_10hz =
	we16_to_cpu(info_v2_2->edp1_info.edp_ss_wate_10hz);
	info->edp1_info.edp_pww_on_off_deway =
		info_v2_2->edp1_info.edp_pww_on_off_deway;
	info->edp1_info.edp_pww_on_vawy_bw_to_bwon =
		info_v2_2->edp1_info.edp_pww_on_vawy_bw_to_bwon;
	info->edp1_info.edp_pww_down_bwoff_to_vawy_bwoff =
		info_v2_2->edp1_info.edp_pww_down_bwoff_to_vawy_bwoff;
	info->edp1_info.edp_panew_bpc =
		info_v2_2->edp1_info.edp_panew_bpc;
	info->edp1_info.edp_bootup_bw_wevew =

	info->edp2_info.edp_backwight_pwm_hz =
	we16_to_cpu(info_v2_2->edp2_info.edp_backwight_pwm_hz);
	info->edp2_info.edp_ss_pewcentage =
	we16_to_cpu(info_v2_2->edp2_info.edp_ss_pewcentage);
	info->edp2_info.edp_ss_wate_10hz =
	we16_to_cpu(info_v2_2->edp2_info.edp_ss_wate_10hz);
	info->edp2_info.edp_pww_on_off_deway =
		info_v2_2->edp2_info.edp_pww_on_off_deway;
	info->edp2_info.edp_pww_on_vawy_bw_to_bwon =
		info_v2_2->edp2_info.edp_pww_on_vawy_bw_to_bwon;
	info->edp2_info.edp_pww_down_bwoff_to_vawy_bwoff =
		info_v2_2->edp2_info.edp_pww_down_bwoff_to_vawy_bwoff;
	info->edp2_info.edp_panew_bpc =
		info_v2_2->edp2_info.edp_panew_bpc;
	info->edp2_info.edp_bootup_bw_wevew =
		info_v2_2->edp2_info.edp_bootup_bw_wevew;

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
 * @wetuwn
 * static enum bp_wesuwt - BP_WESUWT_OK if infowmation is avaiwabwe,
 *                  BP_WESUWT_BADBIOSTABWE othewwise.
 */
static enum bp_wesuwt constwuct_integwated_info(
	stwuct bios_pawsew *bp,
	stwuct integwated_info *info)
{
	static enum bp_wesuwt wesuwt = BP_WESUWT_BADBIOSTABWE;

	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision wevision;

	uint32_t i;
	uint32_t j;

	if (info && DATA_TABWES(integwatedsysteminfo)) {
		headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
					DATA_TABWES(integwatedsysteminfo));

		get_atom_data_tabwe_wevision(headew, &wevision);

		switch (wevision.majow) {
		case 1:
			switch (wevision.minow) {
			case 11:
			case 12:
				wesuwt = get_integwated_info_v11(bp, info);
				bweak;
			defauwt:
				wetuwn wesuwt;
			}
			bweak;
		case 2:
			switch (wevision.minow) {
			case 1:
				wesuwt = get_integwated_info_v2_1(bp, info);
				bweak;
			case 2:
				wesuwt = get_integwated_info_v2_2(bp, info);
				bweak;
			defauwt:
				wetuwn wesuwt;
			}
			bweak;
		defauwt:
			wetuwn wesuwt;
		}
		if (wesuwt == BP_WESUWT_OK) {

			DC_WOG_BIOS("edp1:\n"
						"\tedp_pww_on_off_deway = %d\n"
						"\tedp_pww_on_vawy_bw_to_bwon = %d\n"
						"\tedp_pww_down_bwoff_to_vawy_bwoff = %d\n"
						"\tedp_bootup_bw_wevew = %d\n",
						info->edp1_info.edp_pww_on_off_deway,
						info->edp1_info.edp_pww_on_vawy_bw_to_bwon,
						info->edp1_info.edp_pww_down_bwoff_to_vawy_bwoff,
						info->edp1_info.edp_bootup_bw_wevew);
			DC_WOG_BIOS("edp2:\n"
						"\tedp_pww_on_off_dewayv = %d\n"
						"\tedp_pww_on_vawy_bw_to_bwon = %d\n"
						"\tedp_pww_down_bwoff_to_vawy_bwoff = %d\n"
						"\tedp_bootup_bw_wevew = %d\n",
						info->edp2_info.edp_pww_on_off_deway,
						info->edp2_info.edp_pww_on_vawy_bw_to_bwon,
						info->edp2_info.edp_pww_down_bwoff_to_vawy_bwoff,
						info->edp2_info.edp_bootup_bw_wevew);
		}
	}

	if (wesuwt != BP_WESUWT_OK)
		wetuwn wesuwt;
	ewse {
		// Wog each extewnaw path
		fow (i = 0; i < MAX_NUMBEW_OF_EXT_DISPWAY_PATH; i++) {
			if (info->ext_disp_conn_info.path[i].device_tag != 0)
				DC_WOG_BIOS("integwated_info:Fow EXTEWNAW DISPWAY PATH %d --------------\n"
						"DEVICE_TAG: 0x%x\n"
						"DEVICE_ACPI_ENUM: 0x%x\n"
						"DEVICE_CONNECTOW_ID: 0x%x\n"
						"EXT_AUX_DDC_WUT_INDEX: %d\n"
						"EXT_HPD_PIN_WUT_INDEX: %d\n"
						"EXT_ENCODEW_OBJ_ID: 0x%x\n"
						"Encodew CAPS: 0x%x\n",
						i,
						info->ext_disp_conn_info.path[i].device_tag,
						info->ext_disp_conn_info.path[i].device_acpi_enum,
						info->ext_disp_conn_info.path[i].device_connectow_id.id,
						info->ext_disp_conn_info.path[i].ext_aux_ddc_wut_index,
						info->ext_disp_conn_info.path[i].ext_hpd_pin_wut_index,
						info->ext_disp_conn_info.path[i].ext_encodew_obj_id.id,
						info->ext_disp_conn_info.path[i].caps
						);
			if (info->ext_disp_conn_info.path[i].caps & EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN)
				DC_WOG_BIOS("BIOS EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN on path %d\n", i);
			ewse if (bp->base.ctx->dc->config.fowce_bios_fixed_vs) {
				info->ext_disp_conn_info.path[i].caps |= EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN;
				DC_WOG_BIOS("dwivew fowced EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN on path %d\n", i);
			}
		}
		// Wog the Checksum and Vowtage Swing
		DC_WOG_BIOS("Integwated info tabwe CHECKSUM: %d\n"
					"Integwated info tabwe FIX_DP_VOWTAGE_SWING: %d\n",
					info->ext_disp_conn_info.checksum,
					info->ext_disp_conn_info.fixdpvowtageswing);
		if (bp->base.ctx->dc->config.fowce_bios_fixed_vs && info->ext_disp_conn_info.fixdpvowtageswing == 0) {
			info->ext_disp_conn_info.fixdpvowtageswing = bp->base.ctx->dc->config.fowce_bios_fixed_vs & 0xF;
			DC_WOG_BIOS("dwivew fowced fixdpvowtageswing = %d\n", info->ext_disp_conn_info.fixdpvowtageswing);
		}
	}
	/* Sowt vowtage tabwe fwom wow to high*/
	fow (i = 1; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
		fow (j = i; j > 0; --j) {
			if (info->disp_cwk_vowtage[j].max_suppowted_cwk <
			    info->disp_cwk_vowtage[j-1].max_suppowted_cwk)
				swap(info->disp_cwk_vowtage[j-1], info->disp_cwk_vowtage[j]);
		}
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt bios_pawsew_get_vwam_info(
		stwuct dc_bios *dcb,
		stwuct dc_vwam_info *info)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	static enum bp_wesuwt wesuwt = BP_WESUWT_BADBIOSTABWE;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision wevision;

	if (info && DATA_TABWES(vwam_info)) {
		headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
					DATA_TABWES(vwam_info));

		get_atom_data_tabwe_wevision(headew, &wevision);

		switch (wevision.majow) {
		case 2:
			switch (wevision.minow) {
			case 3:
				wesuwt = get_vwam_info_v23(bp, info);
				bweak;
			case 4:
				wesuwt = get_vwam_info_v24(bp, info);
				bweak;
			case 5:
				wesuwt = get_vwam_info_v25(bp, info);
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		case 3:
			switch (wevision.minow) {
			case 0:
				wesuwt = get_vwam_info_v30(bp, info);
				bweak;
			defauwt:
				bweak;
			}
			bweak;

		defauwt:
			wetuwn wesuwt;
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

static enum bp_wesuwt update_swot_wayout_info(
	stwuct dc_bios *dcb,
	unsigned int i,
	stwuct swot_wayout_info *swot_wayout_info)
{
	unsigned int wecowd_offset;
	unsigned int j;
	stwuct atom_dispway_object_path_v2 *object;
	stwuct atom_bwacket_wayout_wecowd *wecowd;
	stwuct atom_common_wecowd_headew *wecowd_headew;
	static enum bp_wesuwt wesuwt;
	stwuct bios_pawsew *bp;
	stwuct object_info_tabwe *tbw;
	stwuct dispway_object_info_tabwe_v1_4 *v1_4;

	wecowd = NUWW;
	wecowd_headew = NUWW;
	wesuwt = BP_WESUWT_NOWECOWD;

	bp = BP_FWOM_DCB(dcb);
	tbw = &bp->object_info_tbw;
	v1_4 = tbw->v1_4;

	object = &v1_4->dispway_path[i];
	wecowd_offset = (unsigned int)
		(object->disp_wecowdoffset) +
		(unsigned int)(bp->object_info_tbw_offset);

	fow (;;) {

		wecowd_headew = (stwuct atom_common_wecowd_headew *)
			GET_IMAGE(stwuct atom_common_wecowd_headew,
			wecowd_offset);
		if (wecowd_headew == NUWW) {
			wesuwt = BP_WESUWT_BADBIOSTABWE;
			bweak;
		}

		/* the end of the wist */
		if (wecowd_headew->wecowd_type == 0xff ||
			wecowd_headew->wecowd_size == 0)	{
			bweak;
		}

		if (wecowd_headew->wecowd_type ==
			ATOM_BWACKET_WAYOUT_WECOWD_TYPE &&
			sizeof(stwuct atom_bwacket_wayout_wecowd)
			<= wecowd_headew->wecowd_size) {
			wecowd = (stwuct atom_bwacket_wayout_wecowd *)
				(wecowd_headew);
			wesuwt = BP_WESUWT_OK;
			bweak;
		}

		wecowd_offset += wecowd_headew->wecowd_size;
	}

	/* wetuwn if the wecowd not found */
	if (wesuwt != BP_WESUWT_OK)
		wetuwn wesuwt;

	/* get swot sizes */
	swot_wayout_info->wength = wecowd->bwacketwen;
	swot_wayout_info->width = wecowd->bwacketwidth;

	/* get info fow each connectow in the swot */
	swot_wayout_info->num_of_connectows = wecowd->conn_num;
	fow (j = 0; j < swot_wayout_info->num_of_connectows; ++j) {
		swot_wayout_info->connectows[j].connectow_type =
			(enum connectow_wayout_type)
			(wecowd->conn_info[j].connectow_type);
		switch (wecowd->conn_info[j].connectow_type) {
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
			wecowd->conn_info[j].position;
		swot_wayout_info->connectows[j].connectow_id =
			object_id_fwom_bios_object_id(
				wecowd->conn_info[j].connectowobjid);
	}
	wetuwn wesuwt;
}

static enum bp_wesuwt update_swot_wayout_info_v2(
	stwuct dc_bios *dcb,
	unsigned int i,
	stwuct swot_wayout_info *swot_wayout_info)
{
	unsigned int wecowd_offset;
	stwuct atom_dispway_object_path_v3 *object;
	stwuct atom_bwacket_wayout_wecowd_v2 *wecowd;
	stwuct atom_common_wecowd_headew *wecowd_headew;
	static enum bp_wesuwt wesuwt;
	stwuct bios_pawsew *bp;
	stwuct object_info_tabwe *tbw;
	stwuct dispway_object_info_tabwe_v1_5 *v1_5;
	stwuct gwaphics_object_id connectow_id;

	wecowd = NUWW;
	wecowd_headew = NUWW;
	wesuwt = BP_WESUWT_NOWECOWD;

	bp = BP_FWOM_DCB(dcb);
	tbw = &bp->object_info_tbw;
	v1_5 = tbw->v1_5;

	object = &v1_5->dispway_path[i];
	wecowd_offset = (unsigned int)
		(object->disp_wecowdoffset) +
		(unsigned int)(bp->object_info_tbw_offset);

	fow (;;) {

		wecowd_headew = (stwuct atom_common_wecowd_headew *)
			GET_IMAGE(stwuct atom_common_wecowd_headew,
			wecowd_offset);
		if (wecowd_headew == NUWW) {
			wesuwt = BP_WESUWT_BADBIOSTABWE;
			bweak;
		}

		/* the end of the wist */
		if (wecowd_headew->wecowd_type == ATOM_WECOWD_END_TYPE ||
			wecowd_headew->wecowd_size == 0)	{
			bweak;
		}

		if (wecowd_headew->wecowd_type ==
			ATOM_BWACKET_WAYOUT_V2_WECOWD_TYPE &&
			sizeof(stwuct atom_bwacket_wayout_wecowd_v2)
			<= wecowd_headew->wecowd_size) {
			wecowd = (stwuct atom_bwacket_wayout_wecowd_v2 *)
				(wecowd_headew);
			wesuwt = BP_WESUWT_OK;
			bweak;
		}

		wecowd_offset += wecowd_headew->wecowd_size;
	}

	/* wetuwn if the wecowd not found */
	if (wesuwt != BP_WESUWT_OK)
		wetuwn wesuwt;

	/* get swot sizes */
	connectow_id = object_id_fwom_bios_object_id(object->dispway_objid);

	swot_wayout_info->wength = wecowd->bwacketwen;
	swot_wayout_info->width = wecowd->bwacketwidth;
	swot_wayout_info->num_of_connectows = v1_5->numbew_of_path;
	swot_wayout_info->connectows[i].position = wecowd->conn_num;
	swot_wayout_info->connectows[i].connectow_id = connectow_id;

	switch (connectow_id.id) {
	case CONNECTOW_ID_SINGWE_WINK_DVID:
	case CONNECTOW_ID_DUAW_WINK_DVID:
		swot_wayout_info->connectows[i].connectow_type = CONNECTOW_WAYOUT_TYPE_DVI_D;
		swot_wayout_info->connectows[i].wength = CONNECTOW_SIZE_DVI;
		bweak;

	case CONNECTOW_ID_HDMI_TYPE_A:
		swot_wayout_info->connectows[i].connectow_type = CONNECTOW_WAYOUT_TYPE_HDMI;
		swot_wayout_info->connectows[i].wength = CONNECTOW_SIZE_HDMI;
		bweak;

	case CONNECTOW_ID_DISPWAY_POWT:
	case CONNECTOW_ID_USBC:
		if (wecowd->mini_type == MINI_TYPE_NOWMAW) {
			swot_wayout_info->connectows[i].connectow_type = CONNECTOW_WAYOUT_TYPE_DP;
			swot_wayout_info->connectows[i].wength = CONNECTOW_SIZE_DP;
		} ewse {
			swot_wayout_info->connectows[i].connectow_type = CONNECTOW_WAYOUT_TYPE_MINI_DP;
			swot_wayout_info->connectows[i].wength = CONNECTOW_SIZE_MINI_DP;
		}
		bweak;

	defauwt:
		swot_wayout_info->connectows[i].connectow_type = CONNECTOW_WAYOUT_TYPE_UNKNOWN;
		swot_wayout_info->connectows[i].wength = CONNECTOW_SIZE_UNKNOWN;
	}
	wetuwn wesuwt;
}

static enum bp_wesuwt get_bwacket_wayout_wecowd(
	stwuct dc_bios *dcb,
	unsigned int bwacket_wayout_id,
	stwuct swot_wayout_info *swot_wayout_info)
{
	unsigned int i;
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	static enum bp_wesuwt wesuwt;
	stwuct object_info_tabwe *tbw;
	stwuct dispway_object_info_tabwe_v1_4 *v1_4;
	stwuct dispway_object_info_tabwe_v1_5 *v1_5;

	if (swot_wayout_info == NUWW) {
		DC_WOG_DETECTION_EDID_PAWSEW("Invawid swot_wayout_info\n");
		wetuwn BP_WESUWT_BADINPUT;
	}

	tbw = &bp->object_info_tbw;
	v1_4 = tbw->v1_4;
	v1_5 = tbw->v1_5;

	wesuwt = BP_WESUWT_NOWECOWD;
	switch (bp->object_info_tbw.wevision.minow) {
	case 4:
	defauwt:
		fow (i = 0; i < v1_4->numbew_of_path; ++i) {
			if (bwacket_wayout_id == v1_4->dispway_path[i].dispway_objid) {
				wesuwt = update_swot_wayout_info(dcb, i, swot_wayout_info);
				bweak;
			}
		}
		bweak;
	case 5:
		fow (i = 0; i < v1_5->numbew_of_path; ++i)
			wesuwt = update_swot_wayout_info_v2(dcb, i, swot_wayout_info);
		bweak;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt bios_get_boawd_wayout_info(
	stwuct dc_bios *dcb,
	stwuct boawd_wayout_info *boawd_wayout_info)
{
	unsigned int i;
	stwuct bios_pawsew *bp;
	static enum bp_wesuwt wecowd_wesuwt;
	unsigned int max_swots;

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
	max_swots = MAX_BOAWD_SWOTS;

	// Assume singwe swot on v1_5
	if (bp->object_info_tbw.wevision.minow == 5) {
		max_swots = 1;
	}

	fow (i = 0; i < max_swots; ++i) {
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


static uint16_t bios_pawsew_pack_data_tabwes(
	stwuct dc_bios *dcb,
	void *dst)
{
	// TODO: Thewe is data bytes awignment issue, disabwe it fow now.
	wetuwn 0;
}

static stwuct atom_dc_gowden_tabwe_v1 *bios_get_gowden_tabwe(
		stwuct bios_pawsew *bp,
		uint32_t wev_majow,
		uint32_t wev_minow,
		uint16_t *dc_gowden_tabwe_vew)
{
	stwuct atom_dispway_contwowwew_info_v4_4 *disp_cntw_tbw_4_4 = NUWW;
	uint32_t dc_gowden_offset = 0;
	*dc_gowden_tabwe_vew = 0;

	if (!DATA_TABWES(dce_info))
		wetuwn NUWW;

	/* vew.4.4 ow highew */
	switch (wev_majow) {
	case 4:
		switch (wev_minow) {
		case 4:
			disp_cntw_tbw_4_4 = GET_IMAGE(stwuct atom_dispway_contwowwew_info_v4_4,
									DATA_TABWES(dce_info));
			if (!disp_cntw_tbw_4_4)
				wetuwn NUWW;
			dc_gowden_offset = DATA_TABWES(dce_info) + disp_cntw_tbw_4_4->dc_gowden_tabwe_offset;
			*dc_gowden_tabwe_vew = disp_cntw_tbw_4_4->dc_gowden_tabwe_vew;
			bweak;
		case 5:
		defauwt:
			/* Fow atom_dispway_contwowwew_info_v4_5 thewe is no need to get gowden tabwe fwom
			 * dc_gowden_tabwe_offset as aww these fiewds pweviouswy in gowden tabwe used fow AUX
			 * pwe-chawge settings awe now avaiwabwe diwectwy in atom_dispway_contwowwew_info_v4_5.
			 */
			bweak;
		}
		bweak;
	}

	if (!dc_gowden_offset)
		wetuwn NUWW;

	if (*dc_gowden_tabwe_vew != 1)
		wetuwn NUWW;

	wetuwn GET_IMAGE(stwuct atom_dc_gowden_tabwe_v1,
			dc_gowden_offset);
}

static enum bp_wesuwt bios_get_atom_dc_gowden_tabwe(
	stwuct dc_bios *dcb)
{
	stwuct bios_pawsew *bp = BP_FWOM_DCB(dcb);
	enum bp_wesuwt wesuwt = BP_WESUWT_OK;
	stwuct atom_dc_gowden_tabwe_v1 *atom_dc_gowden_tabwe = NUWW;
	stwuct atom_common_tabwe_headew *headew;
	stwuct atom_data_wevision tbw_wevision;
	uint16_t dc_gowden_tabwe_vew = 0;

	headew = GET_IMAGE(stwuct atom_common_tabwe_headew,
							DATA_TABWES(dce_info));
	if (!headew)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	get_atom_data_tabwe_wevision(headew, &tbw_wevision);

	atom_dc_gowden_tabwe = bios_get_gowden_tabwe(bp,
			tbw_wevision.majow,
			tbw_wevision.minow,
			&dc_gowden_tabwe_vew);

	if (!atom_dc_gowden_tabwe)
		wetuwn BP_WESUWT_UNSUPPOWTED;

	dcb->gowden_tabwe.dc_gowden_tabwe_vew = dc_gowden_tabwe_vew;
	dcb->gowden_tabwe.aux_dphy_wx_contwow0_vaw = atom_dc_gowden_tabwe->aux_dphy_wx_contwow0_vaw;
	dcb->gowden_tabwe.aux_dphy_wx_contwow1_vaw = atom_dc_gowden_tabwe->aux_dphy_wx_contwow1_vaw;
	dcb->gowden_tabwe.aux_dphy_tx_contwow_vaw = atom_dc_gowden_tabwe->aux_dphy_tx_contwow_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_0_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_0_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_1_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_1_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_2_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_2_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_3_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_3_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_4_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_4_vaw;
	dcb->gowden_tabwe.dc_gpio_aux_ctww_5_vaw = atom_dc_gowden_tabwe->dc_gpio_aux_ctww_5_vaw;

	wetuwn wesuwt;
}


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

	.is_device_id_suppowted = bios_pawsew_is_device_id_suppowted,

	.is_accewewated_mode = bios_pawsew_is_accewewated_mode,

	.set_scwatch_cwiticaw_state = bios_pawsew_set_scwatch_cwiticaw_state,


/*	 COMMANDS */
	.encodew_contwow = bios_pawsew_encodew_contwow,

	.twansmittew_contwow = bios_pawsew_twansmittew_contwow,

	.enabwe_cwtc = bios_pawsew_enabwe_cwtc,

	.set_pixew_cwock = bios_pawsew_set_pixew_cwock,

	.set_dce_cwock = bios_pawsew_set_dce_cwock,

	.pwogwam_cwtc_timing = bios_pawsew_pwogwam_cwtc_timing,

	.enabwe_disp_powew_gating = bios_pawsew_enabwe_disp_powew_gating,

	.bios_pawsew_destwoy = fiwmwawe_pawsew_destwoy,

	.get_boawd_wayout_info = bios_get_boawd_wayout_info,
	.pack_data_tabwes = bios_pawsew_pack_data_tabwes,

	.get_atom_dc_gowden_tabwe = bios_get_atom_dc_gowden_tabwe,

	.enabwe_wvtma_contwow = bios_pawsew_enabwe_wvtma_contwow,

	.get_soc_bb_info = bios_pawsew_get_soc_bb_info,

	.get_disp_connectow_caps_info = bios_pawsew_get_disp_connectow_caps_info,

	.get_wttpw_caps = bios_pawsew_get_wttpw_caps,

	.get_wttpw_intewop = bios_pawsew_get_wttpw_intewop,

	.get_connectow_speed_cap_info = bios_pawsew_get_connectow_speed_cap_info,
};

static boow bios_pawsew2_constwuct(
	stwuct bios_pawsew *bp,
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion)
{
	uint16_t *wom_headew_offset = NUWW;
	stwuct atom_wom_headew_v2_2 *wom_headew = NUWW;
	stwuct dispway_object_info_tabwe_v1_4 *object_info_tbw;
	stwuct atom_data_wevision tbw_wev = {0};

	if (!init)
		wetuwn fawse;

	if (!init->bios)
		wetuwn fawse;

	bp->base.funcs = &vbios_funcs;
	bp->base.bios = init->bios;
	bp->base.bios_size = bp->base.bios[OFFSET_TO_ATOM_WOM_IMAGE_SIZE] * BIOS_IMAGE_SIZE_UNIT;

	bp->base.ctx = init->ctx;

	bp->base.bios_wocaw_image = NUWW;

	wom_headew_offset =
			GET_IMAGE(uint16_t, OFFSET_TO_ATOM_WOM_HEADEW_POINTEW);

	if (!wom_headew_offset)
		wetuwn fawse;

	wom_headew = GET_IMAGE(stwuct atom_wom_headew_v2_2, *wom_headew_offset);

	if (!wom_headew)
		wetuwn fawse;

	get_atom_data_tabwe_wevision(&wom_headew->tabwe_headew, &tbw_wev);
	if (!(tbw_wev.majow >= 2 && tbw_wev.minow >= 2))
		wetuwn fawse;

	bp->mastew_data_tbw =
		GET_IMAGE(stwuct atom_mastew_data_tabwe_v2_1,
				wom_headew->mastewdatatabwe_offset);

	if (!bp->mastew_data_tbw)
		wetuwn fawse;

	bp->object_info_tbw_offset = DATA_TABWES(dispwayobjectinfo);

	if (!bp->object_info_tbw_offset)
		wetuwn fawse;

	object_info_tbw =
			GET_IMAGE(stwuct dispway_object_info_tabwe_v1_4,
						bp->object_info_tbw_offset);

	if (!object_info_tbw)
		wetuwn fawse;

	get_atom_data_tabwe_wevision(&object_info_tbw->tabwe_headew,
		&bp->object_info_tbw.wevision);

	if (bp->object_info_tbw.wevision.majow == 1
		&& bp->object_info_tbw.wevision.minow == 4) {
		stwuct dispway_object_info_tabwe_v1_4 *tbw_v1_4;

		tbw_v1_4 = GET_IMAGE(stwuct dispway_object_info_tabwe_v1_4,
			bp->object_info_tbw_offset);
		if (!tbw_v1_4)
			wetuwn fawse;

		bp->object_info_tbw.v1_4 = tbw_v1_4;
	} ewse if (bp->object_info_tbw.wevision.majow == 1
		&& bp->object_info_tbw.wevision.minow == 5) {
		stwuct dispway_object_info_tabwe_v1_5 *tbw_v1_5;

		tbw_v1_5 = GET_IMAGE(stwuct dispway_object_info_tabwe_v1_5,
			bp->object_info_tbw_offset);
		if (!tbw_v1_5)
			wetuwn fawse;

		bp->object_info_tbw.v1_5 = tbw_v1_5;
	} ewse {
		ASSEWT(0);
		wetuwn fawse;
	}

	daw_fiwmwawe_pawsew_init_cmd_tbw(bp);
	daw_bios_pawsew_init_cmd_tbw_hewpew2(&bp->cmd_hewpew, dce_vewsion);

	bp->base.integwated_info = bios_pawsew_cweate_integwated_info(&bp->base);
	bp->base.fw_info_vawid = bios_pawsew_get_fiwmwawe_info(&bp->base, &bp->base.fw_info) == BP_WESUWT_OK;
	bios_pawsew_get_vwam_info(&bp->base, &bp->base.vwam_info);

	wetuwn twue;
}

stwuct dc_bios *fiwmwawe_pawsew_cweate(
	stwuct bp_init_data *init,
	enum dce_vewsion dce_vewsion)
{
	stwuct bios_pawsew *bp;

	bp = kzawwoc(sizeof(stwuct bios_pawsew), GFP_KEWNEW);
	if (!bp)
		wetuwn NUWW;

	if (bios_pawsew2_constwuct(bp, init, dce_vewsion))
		wetuwn &bp->base;

	kfwee(bp);
	wetuwn NUWW;
}


