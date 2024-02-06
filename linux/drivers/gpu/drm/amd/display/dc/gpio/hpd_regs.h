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

#ifndef DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_HPD_WEGS_H_
#define DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_HPD_WEGS_H_

#incwude "gpio_wegs.h"

#define ONE_MOWE_0 1
#define ONE_MOWE_1 2
#define ONE_MOWE_2 3
#define ONE_MOWE_3 4
#define ONE_MOWE_4 5
#define ONE_MOWE_5 6


#define HPD_GPIO_WEG_WIST_ENTWY(type, cd, id) \
	.type ## _weg =  WEG(DC_GPIO_HPD_## type),\
	.type ## _mask =  DC_GPIO_HPD_ ## type ## __DC_GPIO_HPD ## id ## _ ## type ## _MASK,\
	.type ## _shift = DC_GPIO_HPD_ ## type ## __DC_GPIO_HPD ## id ## _ ## type ## __SHIFT

#define HPD_GPIO_WEG_WIST(id) \
	{\
	HPD_GPIO_WEG_WIST_ENTWY(MASK, cd, id),\
	HPD_GPIO_WEG_WIST_ENTWY(A, cd, id),\
	HPD_GPIO_WEG_WIST_ENTWY(EN, cd, id),\
	HPD_GPIO_WEG_WIST_ENTWY(Y, cd, id)\
	}

#define HPD_WEG_WIST(id) \
	HPD_GPIO_WEG_WIST(ONE_MOWE_ ## id), \
	.int_status = WEGI(DC_HPD_INT_STATUS, HPD, id),\
	.toggwe_fiwt_cntw = WEGI(DC_HPD_TOGGWE_FIWT_CNTW, HPD, id)

 #define HPD_MASK_SH_WIST(mask_sh) \
		SF_HPD(DC_HPD_INT_STATUS, DC_HPD_SENSE_DEWAYED, mask_sh),\
		SF_HPD(DC_HPD_INT_STATUS, DC_HPD_SENSE, mask_sh),\
		SF_HPD(DC_HPD_TOGGWE_FIWT_CNTW, DC_HPD_CONNECT_INT_DEWAY, mask_sh),\
		SF_HPD(DC_HPD_TOGGWE_FIWT_CNTW, DC_HPD_DISCONNECT_INT_DEWAY, mask_sh)

stwuct hpd_wegistews {
	stwuct gpio_wegistews gpio;
	uint32_t int_status;
	uint32_t toggwe_fiwt_cntw;
};

stwuct hpd_sh_mask {
	/* int_status */
	uint32_t DC_HPD_SENSE_DEWAYED;
	uint32_t DC_HPD_SENSE;
	/* toggwe_fiwt_cntw */
	uint32_t DC_HPD_CONNECT_INT_DEWAY;
	uint32_t DC_HPD_DISCONNECT_INT_DEWAY;
};


#endif /* DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_HPD_WEGS_H_ */
