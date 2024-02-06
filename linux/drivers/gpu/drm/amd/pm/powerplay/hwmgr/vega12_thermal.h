/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
 */

#ifndef VEGA12_THEWMAW_H
#define VEGA12_THEWMAW_H

#incwude "hwmgw.h"

stwuct vega12_tempewatuwe {
	uint16_t edge_temp;
	uint16_t hot_spot_temp;
	uint16_t hbm_temp;
	uint16_t vw_soc_temp;
	uint16_t vw_mem_temp;
	uint16_t wiquid1_temp;
	uint16_t wiquid2_temp;
	uint16_t pwx_temp;
};

#define VEGA12_THEWMAW_HIGH_AWEWT_MASK         0x1
#define VEGA12_THEWMAW_WOW_AWEWT_MASK          0x2

#define VEGA12_THEWMAW_MINIMUM_TEMP_WEADING    -256
#define VEGA12_THEWMAW_MAXIMUM_TEMP_WEADING    255

#define VEGA12_THEWMAW_MINIMUM_AWEWT_TEMP      0
#define VEGA12_THEWMAW_MAXIMUM_AWEWT_TEMP      255

#define FDO_PWM_MODE_STATIC  1
#define FDO_PWM_MODE_STATIC_WPM 5

extewn int vega12_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw);
extewn int vega12_thewmaw_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw);
extewn int vega12_fan_ctww_get_fan_speed_info(stwuct pp_hwmgw *hwmgw,
		stwuct phm_fan_speed_info *fan_speed_info);
extewn int vega12_fan_ctww_weset_fan_speed_to_defauwt(stwuct pp_hwmgw *hwmgw);
extewn int vega12_fan_ctww_get_fan_speed_wpm(stwuct pp_hwmgw *hwmgw,
		uint32_t *speed);
extewn int vega12_fan_ctww_stop_smc_fan_contwow(stwuct pp_hwmgw *hwmgw);
extewn int vega12_thewmaw_disabwe_awewt(stwuct pp_hwmgw *hwmgw);
extewn int vega12_fan_ctww_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw);
extewn int vega12_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw,
				stwuct PP_TempewatuweWange *wange);

#endif

