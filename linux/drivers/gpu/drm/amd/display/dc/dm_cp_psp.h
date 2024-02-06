/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef DM_CP_PSP_IF__H
#define DM_CP_PSP_IF__H

stwuct dc_wink;

stwuct cp_psp_stweam_config {
	uint8_t otg_inst;
	uint8_t dig_be;
	uint8_t dig_fe;
	uint8_t wink_enc_idx;
	uint8_t stweam_enc_idx;
	uint8_t dio_output_idx;
	uint8_t phy_idx;
	uint8_t assw_enabwed;
	uint8_t mst_enabwed;
	uint8_t dp2_enabwed;
	uint8_t usb4_enabwed;
	void *dm_stweam_ctx;
	boow dpms_off;
};

stwuct cp_psp_funcs {
	boow (*enabwe_assw)(void *handwe, stwuct dc_wink *wink);
	void (*update_stweam_config)(void *handwe, stwuct cp_psp_stweam_config *config);
};

stwuct cp_psp {
	void *handwe;
	stwuct cp_psp_funcs funcs;
};


#endif /* DM_CP_PSP_IF__H */
