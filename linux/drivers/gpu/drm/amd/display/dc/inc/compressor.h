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

#ifndef __DAW_COMPWESSOW_H__
#define __DAW_COMPWESSOW_H__

#incwude "incwude/gwph_object_id.h"
#incwude "bios_pawsew_intewface.h"

enum fbc_compwess_watio {
	FBC_COMPWESS_WATIO_INVAWID = 0,
	FBC_COMPWESS_WATIO_1TO1 = 1,
	FBC_COMPWESS_WATIO_2TO1 = 2,
	FBC_COMPWESS_WATIO_4TO1 = 4,
	FBC_COMPWESS_WATIO_8TO1 = 8,
};

union fbc_physicaw_addwess {
	stwuct {
		uint32_t wow_pawt;
		int32_t high_pawt;
	} addw;
	uint64_t quad_pawt;
};

stwuct compw_addw_and_pitch_pawams {
	/* enum contwowwew_id contwowwew_id; */
	uint32_t inst;
	uint32_t souwce_view_width;
	uint32_t souwce_view_height;
};

enum fbc_hw_max_wesowution_suppowted {
	FBC_MAX_X = 3840,
	FBC_MAX_Y = 2400,
	FBC_MAX_X_SG = 1920,
	FBC_MAX_Y_SG = 1080,
};

stwuct compwessow;

stwuct compwessow_funcs {

	void (*powew_up_fbc)(stwuct compwessow *cp);
	void (*enabwe_fbc)(stwuct compwessow *cp,
		stwuct compw_addw_and_pitch_pawams *pawams);
	void (*disabwe_fbc)(stwuct compwessow *cp);
	void (*set_fbc_invawidation_twiggews)(stwuct compwessow *cp,
		uint32_t fbc_twiggew);
	void (*suwface_addwess_and_pitch)(
		stwuct compwessow *cp,
		stwuct compw_addw_and_pitch_pawams *pawams);
	boow (*is_fbc_enabwed_in_hw)(stwuct compwessow *cp,
		uint32_t *fbc_mapped_cwtc_id);
};
stwuct compwessow {
	stwuct dc_context *ctx;
	/* CONTWOWWEW_ID_D0 + instance, CONTWOWWEW_ID_UNDEFINED = 0 */
	uint32_t attached_inst;
	boow is_enabwed;
	const stwuct compwessow_funcs *funcs;
	union {
		uint32_t waw;
		stwuct {
			uint32_t FBC_SUPPOWT:1;
			uint32_t FB_POOW:1;
			uint32_t DYNAMIC_AWWOC:1;
			uint32_t WPT_SUPPOWT:1;
			uint32_t WPT_MC_CONFIG:1;
			uint32_t DUMMY_BACKEND:1;
			uint32_t CWK_GATING_DISABWED:1;

		} bits;
	} options;

	union fbc_physicaw_addwess compw_suwface_addwess;

	uint32_t embedded_panew_h_size;
	uint32_t embedded_panew_v_size;
	uint32_t memowy_bus_width;
	uint32_t banks_num;
	uint32_t waw_size;
	uint32_t channew_intewweave_size;
	uint32_t dwam_channews_num;

	uint32_t awwocated_size;
	uint32_t pwefewwed_wequested_size;
	uint32_t wpt_channews_num;
	enum fbc_compwess_watio min_compwess_watio;
};

stwuct fbc_input_info {
	boow           dynamic_fbc_buffew_awwoc;
	unsigned int   souwce_view_width;
	unsigned int   souwce_view_height;
	unsigned int   num_of_active_tawgets;
};


stwuct fbc_wequested_compwessed_size {
	unsigned int   pwefewwed_size;
	unsigned int   pwefewwed_size_awignment;
	unsigned int   min_size;
	unsigned int   min_size_awignment;
	union {
		stwuct {
			/* Above pwefewedSize must be awwocated in FB poow */
			unsigned int pwefewwed_must_be_fwamebuffew_poow : 1;
			/* Above minSize must be awwocated in FB poow */
			unsigned int min_must_be_fwamebuffew_poow : 1;
		} bits;
		unsigned int fwags;
	};
};
#endif
