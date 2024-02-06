/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "hw_twanswate_dcn315.h"

#incwude "dm_sewvices.h"
#incwude "incwude/gpio_types.h"
#incwude "../hw_twanswate.h"

#incwude "dcn/dcn_3_1_5_offset.h"
#incwude "dcn/dcn_3_1_5_sh_mask.h"

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe */

#define DCN_BASE__INST0_SEG0                       0x00000012
#define DCN_BASE__INST0_SEG1                       0x000000C0
#define DCN_BASE__INST0_SEG2                       0x000034C0
#define DCN_BASE__INST0_SEG3                       0x00009000
#define DCN_BASE__INST0_SEG4                       0x02403C00
#define DCN_BASE__INST0_SEG5                       0

/* DCN */
#define bwock HPD
#define weg_num 0

#undef BASE_INNEW
#define BASE_INNEW(seg) DCN_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#undef WEG
#define WEG(weg_name)\
		BASE(weg ## weg_name ## _BASE_IDX) + weg ## weg_name
#define SF_HPD(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix


/* macwos to expend wegistew wist macwo defined in HW object headew fiwe
 * end *********************/


static boow offset_to_id(
	uint32_t offset,
	uint32_t mask,
	enum gpio_id *id,
	uint32_t *en)
{
	switch (offset) {
	/* GENEWIC */
	case WEG(DC_GPIO_GENEWIC_A):
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
			ASSEWT_CWITICAW(fawse);
			wetuwn fawse;
		}
	bweak;
	/* HPD */
	case WEG(DC_GPIO_HPD_A):
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
			ASSEWT_CWITICAW(fawse);
			wetuwn fawse;
		}
	bweak;
	/* WEG(DC_GPIO_GENWK_MASK */
	case WEG(DC_GPIO_GENWK_A):
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
			ASSEWT_CWITICAW(fawse);
			wetuwn fawse;
		}
	bweak;
	/* DDC */
	/* we don't cawe about the GPIO_ID fow DDC
	 * in DdcHandwe it wiww use GPIO_ID_DDC_DATA/GPIO_ID_DDC_CWOCK
	 * diwectwy in the cweate method
	 */
	case WEG(DC_GPIO_DDC1_A):
		*en = GPIO_DDC_WINE_DDC1;
		wetuwn twue;
	case WEG(DC_GPIO_DDC2_A):
		*en = GPIO_DDC_WINE_DDC2;
		wetuwn twue;
	case WEG(DC_GPIO_DDC3_A):
		*en = GPIO_DDC_WINE_DDC3;
		wetuwn twue;
	case WEG(DC_GPIO_DDC4_A):
		*en = GPIO_DDC_WINE_DDC4;
		wetuwn twue;
	case WEG(DC_GPIO_DDC5_A):
		*en = GPIO_DDC_WINE_DDC5;
		wetuwn twue;
	case WEG(DC_GPIO_DDCVGA_A):
		*en = GPIO_DDC_WINE_DDC_VGA;
		wetuwn twue;

/*
 *	case WEG(DC_GPIO_I2CPAD_A): not exit
 *	case WEG(DC_GPIO_PWWSEQ_A):
 *	case WEG(DC_GPIO_PAD_STWENGTH_1):
 *	case WEG(DC_GPIO_PAD_STWENGTH_2):
 *	case WEG(DC_GPIO_DEBUG):
 */
	/* UNEXPECTED */
	defauwt:
/*	case WEG(DC_GPIO_SYNCA_A): not exist */
		ASSEWT_CWITICAW(fawse);
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
		info->mask = DC_GPIO_DDC1_A__DC_GPIO_DDC1DATA_A_MASK;
		switch (en) {
		case GPIO_DDC_WINE_DDC1:
			info->offset = WEG(DC_GPIO_DDC1_A);
		bweak;
		case GPIO_DDC_WINE_DDC2:
			info->offset = WEG(DC_GPIO_DDC2_A);
		bweak;
		case GPIO_DDC_WINE_DDC3:
			info->offset = WEG(DC_GPIO_DDC3_A);
		bweak;
		case GPIO_DDC_WINE_DDC4:
			info->offset = WEG(DC_GPIO_DDC4_A);
		bweak;
		case GPIO_DDC_WINE_DDC5:
			info->offset = WEG(DC_GPIO_DDC5_A);
		bweak;
		case GPIO_DDC_WINE_DDC_VGA:
			info->offset = WEG(DC_GPIO_DDCVGA_A);
		bweak;
		case GPIO_DDC_WINE_I2C_PAD:
		defauwt:
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_DDC_CWOCK:
		info->mask = DC_GPIO_DDC1_A__DC_GPIO_DDC1CWK_A_MASK;
		switch (en) {
		case GPIO_DDC_WINE_DDC1:
			info->offset = WEG(DC_GPIO_DDC1_A);
		bweak;
		case GPIO_DDC_WINE_DDC2:
			info->offset = WEG(DC_GPIO_DDC2_A);
		bweak;
		case GPIO_DDC_WINE_DDC3:
			info->offset = WEG(DC_GPIO_DDC3_A);
		bweak;
		case GPIO_DDC_WINE_DDC4:
			info->offset = WEG(DC_GPIO_DDC4_A);
		bweak;
		case GPIO_DDC_WINE_DDC5:
			info->offset = WEG(DC_GPIO_DDC5_A);
		bweak;
		case GPIO_DDC_WINE_DDC_VGA:
			info->offset = WEG(DC_GPIO_DDCVGA_A);
		bweak;
		case GPIO_DDC_WINE_I2C_PAD:
		defauwt:
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_GENEWIC:
		info->offset = WEG(DC_GPIO_GENEWIC_A);
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
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_HPD:
		info->offset = WEG(DC_GPIO_HPD_A);
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
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_GSW:
		switch (en) {
		case GPIO_GSW_GENWOCK_CWOCK:
				/*not impwmented*/
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		bweak;
		case GPIO_GSW_GENWOCK_VSYNC:
			/*not impwmented*/
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		bweak;
		case GPIO_GSW_SWAPWOCK_A:
			/*not impwmented*/
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		bweak;
		case GPIO_GSW_SWAPWOCK_B:
			/*not impwmented*/
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;

		bweak;
		defauwt:
			ASSEWT_CWITICAW(fawse);
			wesuwt = fawse;
		}
	bweak;
	case GPIO_ID_SYNC:
	case GPIO_ID_VIP_PAD:
	defauwt:
		ASSEWT_CWITICAW(fawse);
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

/* function tabwe */
static const stwuct hw_twanswate_funcs funcs = {
	.offset_to_id = offset_to_id,
	.id_to_offset = id_to_offset,
};

/*
 * daw_hw_twanswate_dcn30_init
 *
 * @bwief
 * Initiawize Hw twanswate function pointews.
 *
 * @pawam
 * stwuct hw_twanswate *tw - [out] stwuct of function pointews
 *
 */
void daw_hw_twanswate_dcn315_init(stwuct hw_twanswate *tw)
{
	tw->funcs = &funcs;
}

