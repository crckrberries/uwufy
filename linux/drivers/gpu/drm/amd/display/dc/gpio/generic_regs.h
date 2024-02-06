/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#ifndef DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_GENEWIC_WEGS_H_
#define DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_GENEWIC_WEGS_H_

#incwude "gpio_wegs.h"

#define GENEWIC_GPIO_WEG_WIST_ENTWY(type, cd, id) \
	.type ## _weg =  WEG(DC_GPIO_GENEWIC_## type),\
	.type ## _mask =  DC_GPIO_GENEWIC_ ## type ## __DC_GPIO_GENEWIC ## id ## _ ## type ## _MASK,\
	.type ## _shift = DC_GPIO_GENEWIC_ ## type ## __DC_GPIO_GENEWIC ## id ## _ ## type ## __SHIFT

#define GENEWIC_GPIO_WEG_WIST(id) \
	{\
	GENEWIC_GPIO_WEG_WIST_ENTWY(MASK, cd, id),\
	GENEWIC_GPIO_WEG_WIST_ENTWY(A, cd, id),\
	GENEWIC_GPIO_WEG_WIST_ENTWY(EN, cd, id),\
	GENEWIC_GPIO_WEG_WIST_ENTWY(Y, cd, id)\
	}

#define GENEWIC_WEG_WIST(id) \
	GENEWIC_GPIO_WEG_WIST(id), \
	.mux = WEG(DC_GENEWIC ## id),\

#define GENEWIC_MASK_SH_WIST(mask_sh, cd) \
	{(DC_GENEWIC ## cd ##__GENEWIC ## cd ##_EN## mask_sh),\
	(DC_GENEWIC ## cd ##__GENEWIC ## cd ##_SEW## mask_sh)}

stwuct genewic_wegistews {
	stwuct gpio_wegistews gpio;
	uint32_t mux;
};

stwuct genewic_sh_mask {
	/* enabwe */
	uint32_t GENEWIC_EN;
	/* sewect */
	uint32_t GENEWIC_SEW;

};


#endif /* DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_GENEWIC_WEGS_H_ */
