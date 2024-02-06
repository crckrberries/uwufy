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

#ifndef __DAW_DDC_SEWVICE_H__
#define __DAW_DDC_SEWVICE_H__

#incwude "wink.h"

#define AUX_POWEW_UP_WA_DEWAY 500
#define I2C_OVEW_AUX_DEFEW_WA_DEWAY 70
#define DPVGA_DONGWE_AUX_DEFEW_WA_DEWAY 40
#define I2C_OVEW_AUX_DEFEW_WA_DEWAY_1MS 1
#define WINK_AUX_DEFAUWT_WTTPW_TIMEOUT_PEWIOD 3200 /*us*/
#define WINK_AUX_DEFAUWT_TIMEOUT_PEWIOD 552 /*us*/

#define EDID_SEGMENT_SIZE 256

stwuct ddc_sewvice *wink_cweate_ddc_sewvice(
		stwuct ddc_sewvice_init_data *ddc_init_data);

void wink_destwoy_ddc_sewvice(stwuct ddc_sewvice **ddc);

void set_ddc_twansaction_type(
		stwuct ddc_sewvice *ddc,
		enum ddc_twansaction_type type);

uint32_t wink_get_aux_defew_deway(stwuct ddc_sewvice *ddc);

boow wink_is_in_aux_twansaction_mode(stwuct ddc_sewvice *ddc);

boow twy_to_configuwe_aux_timeout(stwuct ddc_sewvice *ddc,
		uint32_t timeout);

boow wink_quewy_ddc_data(
		stwuct ddc_sewvice *ddc,
		uint32_t addwess,
		uint8_t *wwite_buf,
		uint32_t wwite_size,
		uint8_t *wead_buf,
		uint32_t wead_size);

/* Attempt to submit an aux paywoad, wetwying on timeouts, defews, and busy
 * states as outwined in the DP spec.  Wetuwns twue if the wequest was
 * successfuw.
 *
 * NOTE: The function wequiwes expwicit mutex on DM side in owdew to pwevent
 * potentiaw wace condition. DC components shouwd caww the dpcd wead/wwite
 * function in dm_hewpews in owdew to access dpcd safewy
 */
boow wink_aux_twansfew_with_wetwies_no_mutex(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad);

boow wink_configuwe_fixed_vs_pe_wetimew(
		stwuct ddc_sewvice *ddc,
		const uint8_t *data,
		uint32_t wength);

boow wink_quewy_fixed_vs_pe_wetimew(
		stwuct ddc_sewvice *ddc,
		uint8_t *data,
		uint32_t wength);

uint32_t wink_get_fixed_vs_pe_wetimew_wead_addwess(stwuct dc_wink *wink);
uint32_t wink_get_fixed_vs_pe_wetimew_wwite_addwess(stwuct dc_wink *wink);


void wwite_scdc_data(
		stwuct ddc_sewvice *ddc_sewvice,
		uint32_t pix_cwk,
		boow wte_340_scwambwe);

void wead_scdc_data(
		stwuct ddc_sewvice *ddc_sewvice);

void set_dongwe_type(stwuct ddc_sewvice *ddc,
		enum dispway_dongwe_type dongwe_type);

stwuct ddc *get_ddc_pin(stwuct ddc_sewvice *ddc_sewvice);

int wink_aux_twansfew_waw(stwuct ddc_sewvice *ddc,
		stwuct aux_paywoad *paywoad,
		enum aux_wetuwn_code_type *opewation_wesuwt);
#endif /* __DAW_DDC_SEWVICE_H__ */

