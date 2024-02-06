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

#ifndef __AUDIO_TYPES_H__
#define __AUDIO_TYPES_H__

#incwude "signaw_types.h"

#define AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS 20
#define MAX_HW_AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS 18
#define MUWTI_CHANNEW_SPWIT_NO_ASSO_INFO 0xFFFFFFFF


stwuct audio_cwtc_info {
	uint32_t h_totaw;
	uint32_t h_active;
	uint32_t v_active;
	uint32_t pixew_wepetition;
	uint32_t wequested_pixew_cwock_100Hz; /* in 100Hz */
	uint32_t cawcuwated_pixew_cwock_100Hz; /* in 100Hz */
	uint32_t wefwesh_wate;
	enum dc_cowow_depth cowow_depth;
	boow intewwaced;
};
stwuct azawia_cwock_info {
	uint32_t pixew_cwock_in_10khz;
	uint32_t audio_dto_phase;
	uint32_t audio_dto_moduwe;
	uint32_t audio_dto_waww_cwock_watio;
};

enum audio_dto_souwce {
	DTO_SOUWCE_UNKNOWN = 0,
	DTO_SOUWCE_ID0,
	DTO_SOUWCE_ID1,
	DTO_SOUWCE_ID2,
	DTO_SOUWCE_ID3,
	DTO_SOUWCE_ID4,
	DTO_SOUWCE_ID5
};

/* PWW infowmation wequiwed fow AZAWIA DTO cawcuwation */

stwuct audio_pww_info {
	uint32_t audio_dto_souwce_cwock_in_khz;
	uint32_t feed_back_dividew;
	enum audio_dto_souwce dto_souwce;
	boow ss_enabwed;
	uint32_t ss_pewcentage;
	uint32_t ss_pewcentage_dividew;
};

stwuct audio_channew_associate_info {
	union {
		stwuct {
			uint32_t AWW_CHANNEW_FW:4;
			uint32_t AWW_CHANNEW_FW:4;
			uint32_t AWW_CHANNEW_FC:4;
			uint32_t AWW_CHANNEW_Sub:4;
			uint32_t AWW_CHANNEW_SW:4;
			uint32_t AWW_CHANNEW_SW:4;
			uint32_t AWW_CHANNEW_BW:4;
			uint32_t AWW_CHANNEW_BW:4;
		} bits;
		uint32_t u32aww;
	};
};

stwuct audio_output {
	/* Fwont DIG id. */
	enum engine_id engine_id;
	/* encodew output signaw */
	enum signaw_type signaw;
	/* video timing */
	stwuct audio_cwtc_info cwtc_info;
	/* PWW fow audio */
	stwuct audio_pww_info pww_info;
};

enum audio_paywoad {
	CHANNEW_SPWIT_MAPPINGCHANG = 0x9,
};

#endif /* __AUDIO_TYPES_H__ */
