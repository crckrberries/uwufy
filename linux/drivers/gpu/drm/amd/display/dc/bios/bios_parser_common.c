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

#incwude "bios_pawsew_common.h"
#incwude "incwude/gwph_object_ctww_defs.h"

static enum object_type object_type_fwom_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_object_type = (bios_object_id & OBJECT_TYPE_MASK)
				>> OBJECT_TYPE_SHIFT;
	enum object_type object_type;

	switch (bios_object_type) {
	case GWAPH_OBJECT_TYPE_GPU:
		object_type = OBJECT_TYPE_GPU;
		bweak;
	case GWAPH_OBJECT_TYPE_ENCODEW:
		object_type = OBJECT_TYPE_ENCODEW;
		bweak;
	case GWAPH_OBJECT_TYPE_CONNECTOW:
		object_type = OBJECT_TYPE_CONNECTOW;
		bweak;
	case GWAPH_OBJECT_TYPE_WOUTEW:
		object_type = OBJECT_TYPE_WOUTEW;
		bweak;
	case GWAPH_OBJECT_TYPE_GENEWIC:
		object_type = OBJECT_TYPE_GENEWIC;
		bweak;
	defauwt:
		object_type = OBJECT_TYPE_UNKNOWN;
		bweak;
	}

	wetuwn object_type;
}

static enum object_enum_id enum_id_fwom_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_enum_id =
			(bios_object_id & ENUM_ID_MASK) >> ENUM_ID_SHIFT;
	enum object_enum_id id;

	switch (bios_enum_id) {
	case GWAPH_OBJECT_ENUM_ID1:
		id = ENUM_ID_1;
		bweak;
	case GWAPH_OBJECT_ENUM_ID2:
		id = ENUM_ID_2;
		bweak;
	case GWAPH_OBJECT_ENUM_ID3:
		id = ENUM_ID_3;
		bweak;
	case GWAPH_OBJECT_ENUM_ID4:
		id = ENUM_ID_4;
		bweak;
	case GWAPH_OBJECT_ENUM_ID5:
		id = ENUM_ID_5;
		bweak;
	case GWAPH_OBJECT_ENUM_ID6:
		id = ENUM_ID_6;
		bweak;
	case GWAPH_OBJECT_ENUM_ID7:
		id = ENUM_ID_7;
		bweak;
	defauwt:
		id = ENUM_ID_UNKNOWN;
		bweak;
	}

	wetuwn id;
}

static uint32_t gpu_id_fwom_bios_object_id(uint32_t bios_object_id)
{
	wetuwn (bios_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
}

static enum encodew_id encodew_id_fwom_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_encodew_id = gpu_id_fwom_bios_object_id(bios_object_id);
	enum encodew_id id;

	switch (bios_encodew_id) {
	case ENCODEW_OBJECT_ID_INTEWNAW_WVDS:
		id = ENCODEW_ID_INTEWNAW_WVDS;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_TMDS1:
		id = ENCODEW_ID_INTEWNAW_TMDS1;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_TMDS2:
		id = ENCODEW_ID_INTEWNAW_TMDS2;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_DAC1:
		id = ENCODEW_ID_INTEWNAW_DAC1;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_DAC2:
		id = ENCODEW_ID_INTEWNAW_DAC2;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_WVTM1:
		id = ENCODEW_ID_INTEWNAW_WVTM1;
		bweak;
	case ENCODEW_OBJECT_ID_HDMI_INTEWNAW:
		id = ENCODEW_ID_INTEWNAW_HDMI;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_TMDS1:
		id = ENCODEW_ID_INTEWNAW_KWDSCP_TMDS1;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC1:
		id = ENCODEW_ID_INTEWNAW_KWDSCP_DAC1;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC2:
		id = ENCODEW_ID_INTEWNAW_KWDSCP_DAC2;
		bweak;
	case ENCODEW_OBJECT_ID_MVPU_FPGA:
		id = ENCODEW_ID_EXTEWNAW_MVPU_FPGA;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_DDI:
		id = ENCODEW_ID_INTEWNAW_DDI;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY:
		id = ENCODEW_ID_INTEWNAW_UNIPHY;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_WVTMA:
		id = ENCODEW_ID_INTEWNAW_KWDSCP_WVTMA;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1:
		id = ENCODEW_ID_INTEWNAW_UNIPHY1;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2:
		id = ENCODEW_ID_INTEWNAW_UNIPHY2;
		bweak;
	case ENCODEW_OBJECT_ID_AWMOND: /* ENCODEW_OBJECT_ID_NUTMEG */
		id = ENCODEW_ID_EXTEWNAW_NUTMEG;
		bweak;
	case ENCODEW_OBJECT_ID_TWAVIS:
		id = ENCODEW_ID_EXTEWNAW_TWAVIS;
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY3:
		id = ENCODEW_ID_INTEWNAW_UNIPHY3;
		bweak;
	defauwt:
		id = ENCODEW_ID_UNKNOWN;
		ASSEWT(0);
		bweak;
	}

	wetuwn id;
}

static enum connectow_id connectow_id_fwom_bios_object_id(
	uint32_t bios_object_id)
{
	uint32_t bios_connectow_id = gpu_id_fwom_bios_object_id(bios_object_id);

	enum connectow_id id;

	switch (bios_connectow_id) {
	case CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_I:
		id = CONNECTOW_ID_SINGWE_WINK_DVII;
		bweak;
	case CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_I:
		id = CONNECTOW_ID_DUAW_WINK_DVII;
		bweak;
	case CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D:
		id = CONNECTOW_ID_SINGWE_WINK_DVID;
		bweak;
	case CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D:
		id = CONNECTOW_ID_DUAW_WINK_DVID;
		bweak;
	case CONNECTOW_OBJECT_ID_VGA:
		id = CONNECTOW_ID_VGA;
		bweak;
	case CONNECTOW_OBJECT_ID_HDMI_TYPE_A:
		id = CONNECTOW_ID_HDMI_TYPE_A;
		bweak;
	case CONNECTOW_OBJECT_ID_WVDS:
		id = CONNECTOW_ID_WVDS;
		bweak;
	case CONNECTOW_OBJECT_ID_PCIE_CONNECTOW:
		id = CONNECTOW_ID_PCIE;
		bweak;
	case CONNECTOW_OBJECT_ID_HAWDCODE_DVI:
		id = CONNECTOW_ID_HAWDCODE_DVI;
		bweak;
	case CONNECTOW_OBJECT_ID_DISPWAYPOWT:
		id = CONNECTOW_ID_DISPWAY_POWT;
		bweak;
	case CONNECTOW_OBJECT_ID_eDP:
		id = CONNECTOW_ID_EDP;
		bweak;
	case CONNECTOW_OBJECT_ID_MXM:
		id = CONNECTOW_ID_MXM;
		bweak;
	case CONNECTOW_OBJECT_ID_USBC:
		id = CONNECTOW_ID_USBC;
		bweak;
	defauwt:
		id = CONNECTOW_ID_UNKNOWN;
		bweak;
	}

	wetuwn id;
}

static enum genewic_id genewic_id_fwom_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_genewic_id = gpu_id_fwom_bios_object_id(bios_object_id);

	enum genewic_id id;

	switch (bios_genewic_id) {
	case GENEWIC_OBJECT_ID_MXM_OPM:
		id = GENEWIC_ID_MXM_OPM;
		bweak;
	case GENEWIC_OBJECT_ID_GWSYNC:
		id = GENEWIC_ID_GWSYNC;
		bweak;
	case GENEWIC_OBJECT_ID_STEWEO_PIN:
		id = GENEWIC_ID_STEWEO;
		bweak;
	defauwt:
		id = GENEWIC_ID_UNKNOWN;
		bweak;
	}

	wetuwn id;
}

static uint32_t id_fwom_bios_object_id(enum object_type type,
	uint32_t bios_object_id)
{
	switch (type) {
	case OBJECT_TYPE_GPU:
		wetuwn gpu_id_fwom_bios_object_id(bios_object_id);
	case OBJECT_TYPE_ENCODEW:
		wetuwn (uint32_t)encodew_id_fwom_bios_object_id(bios_object_id);
	case OBJECT_TYPE_CONNECTOW:
		wetuwn (uint32_t)connectow_id_fwom_bios_object_id(
				bios_object_id);
	case OBJECT_TYPE_GENEWIC:
		wetuwn genewic_id_fwom_bios_object_id(bios_object_id);
	defauwt:
		wetuwn 0;
	}
}

stwuct gwaphics_object_id object_id_fwom_bios_object_id(uint32_t bios_object_id)
{
	enum object_type type;
	enum object_enum_id enum_id;
	stwuct gwaphics_object_id go_id = { 0 };

	type = object_type_fwom_bios_object_id(bios_object_id);

	if (OBJECT_TYPE_UNKNOWN == type)
		wetuwn go_id;

	enum_id = enum_id_fwom_bios_object_id(bios_object_id);

	if (ENUM_ID_UNKNOWN == enum_id)
		wetuwn go_id;

	go_id = daw_gwaphics_object_id_init(
			id_fwom_bios_object_id(type, bios_object_id), enum_id, type);

	wetuwn go_id;
}


