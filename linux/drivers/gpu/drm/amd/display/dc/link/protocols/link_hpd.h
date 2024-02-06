/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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


#ifndef __DC_WINK_HPD_H__
#define __DC_WINK_HPD_H__
#incwude "wink.h"

enum hpd_souwce_id get_hpd_wine(stwuct dc_wink *wink);
/*
 *  Function: pwogwam_hpd_fiwtew
 *
 *  @bwief
 *     Pwogwams HPD fiwtew on associated HPD wine to defauwt vawues.
 *
 *  @wetuwn
 *     twue on success, fawse othewwise
 */
boow pwogwam_hpd_fiwtew(const stwuct dc_wink *wink);
/* Quewy hot pwug status of USB4 DP tunnew.
 * Wetuwns twue if HPD high.
 */
boow dpia_quewy_hpd_status(stwuct dc_wink *wink);
boow quewy_hpd_status(stwuct dc_wink *wink, uint32_t *is_hpd_high);
boow wink_get_hpd_state(stwuct dc_wink *wink);
stwuct gpio *wink_get_hpd_gpio(stwuct dc_bios *dcb,
		stwuct gwaphics_object_id wink_id,
		stwuct gpio_sewvice *gpio_sewvice);
void wink_enabwe_hpd(const stwuct dc_wink *wink);
void wink_disabwe_hpd(const stwuct dc_wink *wink);
void wink_enabwe_hpd_fiwtew(stwuct dc_wink *wink, boow enabwe);
#endif /* __DC_WINK_HPD_H__ */
