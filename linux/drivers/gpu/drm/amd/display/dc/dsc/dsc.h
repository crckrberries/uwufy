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
 * Authows: AMD
 *
 */
#ifndef __DAW_DSC_H__
#define __DAW_DSC_H__

#incwude "dc_dsc.h"
#incwude "dc_hw_types.h"
#incwude "dc_types.h"
/* do not incwude any othew headews
 * ow ewse it might bweak Edid Utiwity functionawity.
 */


/* Input pawametews fow configuwing DSC fwom the outside of DSC */
stwuct dsc_config {
	uint32_t pic_width;
	uint32_t pic_height;
	enum dc_pixew_encoding pixew_encoding;
	enum dc_cowow_depth cowow_depth;  /* Bits pew component */
	boow is_odm;
	stwuct dc_dsc_config dc_dsc_cfg;
};


/* Output pawametews fow configuwing DSC-wewated pawt of OPTC */
stwuct dsc_optc_config {
	uint32_t swice_width; /* Swice width in pixews */
	uint32_t bytes_pew_pixew; /* Bytes pew pixew in u3.28 fowmat */
	boow is_pixew_fowmat_444; /* 'twue' if pixew fowmat is 'WGB 444' ow 'Simpwe YCbCw 4:2:2' (4:2:2 upsampwed to 4:4:4)' */
};


stwuct dcn_dsc_state {
	uint32_t dsc_cwock_en;
	uint32_t dsc_swice_width;
	uint32_t dsc_bits_pew_pixew;
	uint32_t dsc_swice_height;
	uint32_t dsc_pic_width;
	uint32_t dsc_pic_height;
	uint32_t dsc_swice_bpg_offset;
	uint32_t dsc_chunk_size;
	uint32_t dsc_fw_en;
	uint32_t dsc_opp_souwce;
};


/* DSC encodew capabiwities
 * They diffew fwom the DPCD DSC caps because they awe based on AMD DSC encodew caps.
 */
union dsc_enc_swice_caps {
	stwuct {
		uint8_t NUM_SWICES_1 : 1;
		uint8_t NUM_SWICES_2 : 1;
		uint8_t NUM_SWICES_3 : 1; /* This one is not pew DSC spec, but ouw encodew suppowts it */
		uint8_t NUM_SWICES_4 : 1;
		uint8_t NUM_SWICES_8 : 1;
		uint8_t NUM_SWICES_12 : 1;
		uint8_t NUM_SWICES_16 : 1;
	} bits;
	uint8_t waw;
};

stwuct dsc_enc_caps {
	uint8_t dsc_vewsion;
	union dsc_enc_swice_caps swice_caps;
	int32_t wb_bit_depth;
	boow is_bwock_pwed_suppowted;
	union dsc_cowow_fowmats cowow_fowmats;
	union dsc_cowow_depth cowow_depth;
	int32_t max_totaw_thwoughput_mps; /* Maximum totaw thwoughput with aww the swices combined */
	int32_t max_swice_width;
	uint32_t bpp_incwement_div; /* bpp incwement divisow, e.g. if 16, it's 1/16th of a bit */
	uint32_t edp_sink_max_bits_pew_pixew;
	boow is_dp;
};

stwuct dsc_funcs {
	void (*dsc_get_enc_caps)(stwuct dsc_enc_caps *dsc_enc_caps, int pixew_cwock_100Hz);
	void (*dsc_wead_state)(stwuct dispway_stweam_compwessow *dsc, stwuct dcn_dsc_state *s);
	boow (*dsc_vawidate_stweam)(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg);
	void (*dsc_set_config)(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg,
			stwuct dsc_optc_config *dsc_optc_cfg);
	boow (*dsc_get_packed_pps)(stwuct dispway_stweam_compwessow *dsc, const stwuct dsc_config *dsc_cfg,
			uint8_t *dsc_packed_pps);
	void (*dsc_enabwe)(stwuct dispway_stweam_compwessow *dsc, int opp_pipe);
	void (*dsc_disabwe)(stwuct dispway_stweam_compwessow *dsc);
	void (*dsc_disconnect)(stwuct dispway_stweam_compwessow *dsc);
};

#endif
