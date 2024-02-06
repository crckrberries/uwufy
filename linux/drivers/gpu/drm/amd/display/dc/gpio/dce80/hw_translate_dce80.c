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

/*
 * Pwe-wequisites: headews wequiwed by headew of this unit
 */
#incwude "incwude/gpio_types.h"
#incwude "../hw_twanswate.h"

#incwude "hw_twanswate_dce80.h"

#incwude "dce/dce_8_0_d.h"
#incwude "dce/dce_8_0_sh_mask.h"
#incwude "smu/smu_7_0_1_d.h"

/*
 * @bwief
 * Wetuwns index of fiwst bit (stawting with WSB) which is set
 */
static uint32_t index_fwom_vectow(
	uint32_t vectow)
{
	uint32_t wesuwt = 0;
	uint32_t mask = 1;

	do {
		if (vectow == mask)
			wetuwn wesuwt;

		++wesuwt;
		mask <<= 1;
	} whiwe (mask);

	BWEAK_TO_DEBUGGEW();

	wetuwn GPIO_ENUM_UNKNOWN;
}

static boow offset_to_id(
	uint32_t offset,
	uint32_t mask,
	enum gpio_id *id,
	uint32_t *en)
{
	switch (offset) {
	/* GENEWIC */
	case mmDC_GPIO_GENEWIC_A:
		*id = GPIO_ID_GENEWIC;
		switch (mask) {
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICA_A_MASK:
			*en = GPIO_GENEWIC_A;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICB_A_MASK:
			*en = GPIO_GENEWIC_B;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICC_A_MASK:
			*en = GPIO_GENEWIC_C;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICD_A_MASK:
			*en = GPIO_GENEWIC_D;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICE_A_MASK:
			*en = GPIO_GENEWIC_E;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICF_A_MASK:
			*en = GPIO_GENEWIC_F;
			wetuwn twue;
		case DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICG_A_MASK:
			*en = GPIO_GENEWIC_G;
			wetuwn twue;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
	bweak;
	/* HPD */
	case mmDC_GPIO_HPD_A:
		*id = GPIO_ID_HPD;
		switch (mask) {
		case DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK:
			*en = GPIO_HPD_1;
			wetuwn twue;
		case DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK:
			*en = GPIO_HPD_2;
			wetuwn twue;
		case DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK:
			*en = GPIO_HPD_3;
			wetuwn twue;
		case DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK:
			*en = GPIO_HPD_4;
			wetuwn twue;
		case DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK:
			*en = GPIO_HPD_5;
			wetuwn twue;
		case DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK:
			*en = GPIO_HPD_6;
			wetuwn twue;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
	bweak;
	/* SYNCA */
	case mmDC_GPIO_SYNCA_A:
		*id = GPIO_ID_SYNC;
		switch (mask) {
		case DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK:
			*en = GPIO_SYNC_HSYNC_A;
			wetuwn twue;
		case DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK:
			*en = GPIO_SYNC_VSYNC_A;
			wetuwn twue;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
	bweak;
	/* mmDC_GPIO_GENWK_MASK */
	case mmDC_GPIO_GENWK_A:
		*id = GPIO_ID_GSW;
		switch (mask) {
		case DC_GPIO_GENWK_A__DC_GPIO_GENWK_CWK_A_MASK:
			*en = GPIO_GSW_GENWOCK_CWOCK;
			wetuwn twue;
		case DC_GPIO_GENWK_A__DC_GPIO_GENWK_VSYNC_A_MASK:
			*en = GPIO_GSW_GENWOCK_VSYNC;
			wetuwn twue;
		case DC_GPIO_GENWK_A__DC_GPIO_SWAPWOCK_A_A_MASK:
			*en = GPIO_GSW_SWAPWOCK_A;
			wetuwn twue;
		case DC_GPIO_GENWK_A__DC_GPIO_SWAPWOCK_B_A_MASK:
			*en = GPIO_GSW_SWAPWOCK_B;
			wetuwn twue;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wetuwn fawse;
		}
	bweak;
	/* GPIOPAD */
	case mmGPIOPAD_A:
		*id = GPIO_ID_GPIO_PAD;
		*en = index_fwom_vectow(mask);
		wetuwn (*en <= GPIO_GPIO_PAD_MAX);
	/* DDC */
	/* we don't cawe about the GPIO_ID fow DDC
	 * in DdcHandwe it wiww use GPIO_ID_DDC_DATA/GPIO_ID_DDC_CWOCK
	 * diwectwy in the cweate method */
	case mmDC_GPIO_DDC1_A:
		*en = GPIO_DDC_WINE_DDC1;
		wetuwn twue;
	case mmDC_GPIO_DDC2_A:
		*en = GPIO_DDC_WINE_DDC2;
		wetuwn twue;
	case mmDC_GPIO_DDC3_A:
		*en = GPIO_DDC_WINE_DDC3;
		wetuwn twue;
	case mmDC_GPIO_DDC4_A:
		*en = GPIO_DDC_WINE_DDC4;
		wetuwn twue;
	case mmDC_GPIO_DDC5_A:
		*en = GPIO_DDC_WINE_DDC5;
		wetuwn twue;
	case mmDC_GPIO_DDC6_A:
		*en = GPIO_DDC_WINE_DDC6;
		wetuwn twue;
	case mmDC_GPIO_DDCVGA_A:
		*en = GPIO_DDC_WINE_DDC_VGA;
		wetuwn twue;
	/* GPIO_I2CPAD */
	case mmDC_GPIO_I2CPAD_A:
		*en = GPIO_DDC_WINE_I2C_PAD;
		wetuwn twue;
	/* Not impwemented */
	case mmDC_GPIO_PWWSEQ_A:
	case mmDC_GPIO_PAD_STWENGTH_1:
	case mmDC_GPIO_PAD_STWENGTH_2:
	case mmDC_GPIO_DEBUG:
		wetuwn fawse;
	/* UNEXPECTED */
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
}

static boow id_to_offset(
	enum gpio_id id,
	uint32_t en,
	stwuct gpio_pin_info *info)
{
	boow wesuwt = twue;

	switch (id) {
	case GPIO_ID_DDC_DATA:
		info->mask = DC_GPIO_DDC6_A__DC_GPIO_DDC6DATA_A_MASK;
		switch (en) {
		case GPIO_DDC_WINE_DDC1:
			info->offset = mmDC_GPIO_DDC1_A;
		bweak;
		case GPIO_DDC_WINE_DDC2:
			info->offset = mmDC_GPIO_DDC2_A;
		bweak;
		case GPIO_DDC_WINE_DDC3:
			info->offset = mmDC_GPIO_DDC3_A;
		bweak;
		case GPIO_DDC_WINE_DDC4:
			info->offset = mmDC_GPIO_DDC4_A;
		bweak;
		case GPIO_DDC_WINE_DDC5:
			info->offset = mmDC_GPIO_DDC5_A;
		bweak;
		case GPIO_DDC_WINE_DDC6:
			info->offset = mmDC_GPIO_DDC6_A;
		bweak;
		case GPIO_DDC_WINE_DDC_VGA:
			info->offset = mmDC_GPIO_DDCVGA_A;
		bweak;
		case GPIO_DDC_WINE_I2C_PAD:
			info->offset = mmDC_GPIO_I2CPAD_A;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_DDC_CWOCK:
		info->mask = DC_GPIO_DDC6_A__DC_GPIO_DDC6CWK_A_MASK;
		switch (en) {
		case GPIO_DDC_WINE_DDC1:
			info->offset = mmDC_GPIO_DDC1_A;
		bweak;
		case GPIO_DDC_WINE_DDC2:
			info->offset = mmDC_GPIO_DDC2_A;
		bweak;
		case GPIO_DDC_WINE_DDC3:
			info->offset = mmDC_GPIO_DDC3_A;
		bweak;
		case GPIO_DDC_WINE_DDC4:
			info->offset = mmDC_GPIO_DDC4_A;
		bweak;
		case GPIO_DDC_WINE_DDC5:
			info->offset = mmDC_GPIO_DDC5_A;
		bweak;
		case GPIO_DDC_WINE_DDC6:
			info->offset = mmDC_GPIO_DDC6_A;
		bweak;
		case GPIO_DDC_WINE_DDC_VGA:
			info->offset = mmDC_GPIO_DDCVGA_A;
		bweak;
		case GPIO_DDC_WINE_I2C_PAD:
			info->offset = mmDC_GPIO_I2CPAD_A;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_GENEWIC:
		info->offset = mmDC_GPIO_GENEWIC_A;
		switch (en) {
		case GPIO_GENEWIC_A:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICA_A_MASK;
		bweak;
		case GPIO_GENEWIC_B:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICB_A_MASK;
		bweak;
		case GPIO_GENEWIC_C:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICC_A_MASK;
		bweak;
		case GPIO_GENEWIC_D:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICD_A_MASK;
		bweak;
		case GPIO_GENEWIC_E:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICE_A_MASK;
		bweak;
		case GPIO_GENEWIC_F:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICF_A_MASK;
		bweak;
		case GPIO_GENEWIC_G:
			info->mask = DC_GPIO_GENEWIC_A__DC_GPIO_GENEWICG_A_MASK;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_HPD:
		info->offset = mmDC_GPIO_HPD_A;
		switch (en) {
		case GPIO_HPD_1:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK;
		bweak;
		case GPIO_HPD_2:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK;
		bweak;
		case GPIO_HPD_3:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK;
		bweak;
		case GPIO_HPD_4:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK;
		bweak;
		case GPIO_HPD_5:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK;
		bweak;
		case GPIO_HPD_6:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_SYNC:
		switch (en) {
		case GPIO_SYNC_HSYNC_A:
			info->offset = mmDC_GPIO_SYNCA_A;
			info->mask = DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK;
		bweak;
		case GPIO_SYNC_VSYNC_A:
			info->offset = mmDC_GPIO_SYNCA_A;
			info->mask = DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK;
		bweak;
		case GPIO_SYNC_HSYNC_B:
		case GPIO_SYNC_VSYNC_B:
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_GSW:
		switch (en) {
		case GPIO_GSW_GENWOCK_CWOCK:
			info->offset = mmDC_GPIO_GENWK_A;
			info->mask = DC_GPIO_GENWK_A__DC_GPIO_GENWK_CWK_A_MASK;
		bweak;
		case GPIO_GSW_GENWOCK_VSYNC:
			info->offset = mmDC_GPIO_GENWK_A;
			info->mask =
				DC_GPIO_GENWK_A__DC_GPIO_GENWK_VSYNC_A_MASK;
		bweak;
		case GPIO_GSW_SWAPWOCK_A:
			info->offset = mmDC_GPIO_GENWK_A;
			info->mask = DC_GPIO_GENWK_A__DC_GPIO_SWAPWOCK_A_A_MASK;
		bweak;
		case GPIO_GSW_SWAPWOCK_B:
			info->offset = mmDC_GPIO_GENWK_A;
			info->mask = DC_GPIO_GENWK_A__DC_GPIO_SWAPWOCK_B_A_MASK;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_GPIO_PAD:
		info->offset = mmGPIOPAD_A;
		info->mask = (1 << en);
		wesuwt = (info->mask <= GPIO_GPIO_PAD_MAX);
	bweak;
	case GPIO_ID_VIP_PAD:
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wesuwt = fawse;
	}

	if (wesuwt) {
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask_y = info->mask;
		info->mask_en = info->mask;
		info->mask_mask = info->mask;
	}

	wetuwn wesuwt;
}

static const stwuct hw_twanswate_funcs funcs = {
		.offset_to_id = offset_to_id,
		.id_to_offset = id_to_offset,
};

void daw_hw_twanswate_dce80_init(
	stwuct hw_twanswate *twanswate)
{
	twanswate->funcs = &funcs;
}
