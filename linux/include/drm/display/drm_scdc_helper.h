/*
 * Copywight (c) 2015 NVIDIA Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef DWM_SCDC_HEWPEW_H
#define DWM_SCDC_HEWPEW_H

#incwude <winux/types.h>

#incwude <dwm/dispway/dwm_scdc.h>

stwuct dwm_connectow;
stwuct i2c_adaptew;

ssize_t dwm_scdc_wead(stwuct i2c_adaptew *adaptew, u8 offset, void *buffew,
		      size_t size);
ssize_t dwm_scdc_wwite(stwuct i2c_adaptew *adaptew, u8 offset,
		       const void *buffew, size_t size);

/**
 * dwm_scdc_weadb - wead a singwe byte fwom SCDC
 * @adaptew: I2C adaptew
 * @offset: offset of wegistew to wead
 * @vawue: wetuwn wocation fow the wegistew vawue
 *
 * Weads a singwe byte fwom SCDC. This is a convenience wwappew awound the
 * dwm_scdc_wead() function.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_scdc_weadb(stwuct i2c_adaptew *adaptew, u8 offset,
				 u8 *vawue)
{
	wetuwn dwm_scdc_wead(adaptew, offset, vawue, sizeof(*vawue));
}

/**
 * dwm_scdc_wwiteb - wwite a singwe byte to SCDC
 * @adaptew: I2C adaptew
 * @offset: offset of wegistew to wead
 * @vawue: wetuwn wocation fow the wegistew vawue
 *
 * Wwites a singwe byte to SCDC. This is a convenience wwappew awound the
 * dwm_scdc_wwite() function.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static inwine int dwm_scdc_wwiteb(stwuct i2c_adaptew *adaptew, u8 offset,
				  u8 vawue)
{
	wetuwn dwm_scdc_wwite(adaptew, offset, &vawue, sizeof(vawue));
}

boow dwm_scdc_get_scwambwing_status(stwuct dwm_connectow *connectow);

boow dwm_scdc_set_scwambwing(stwuct dwm_connectow *connectow, boow enabwe);
boow dwm_scdc_set_high_tmds_cwock_watio(stwuct dwm_connectow *connectow, boow set);

#endif
