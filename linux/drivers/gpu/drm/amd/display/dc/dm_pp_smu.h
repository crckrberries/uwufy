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

#ifndef DM_PP_SMU_IF__H
#define DM_PP_SMU_IF__H

/*
 * intewface to PPWIB/SMU to setup cwocks and pstate wequiwements on SoC
 */

enum pp_smu_vew {
	/*
	 * PP_SMU_INTEWFACE_X shouwd be intewpweted as the intewface defined
	 * stawting fwom X, whewe X is some famiwy of ASICs.  This is as
	 * opposed to intewfaces used onwy fow X.  Thewe wiww be some degwee
	 * of intewface shawing between famiwies of ASIcs.
	 */
	PP_SMU_UNSUPPOWTED,
	PP_SMU_VEW_WV,
	PP_SMU_VEW_NV,
	PP_SMU_VEW_WN,

	PP_SMU_VEW_MAX
};

stwuct pp_smu {
	enum pp_smu_vew vew;
	const void *pp;

	/*
	 * intewim extwa handwe fow backwawds compatibiwity
	 * as some existing functionawity not yet impwemented
	 * by ppsmu
	 */
	const void *dm;
};

enum pp_smu_status {
	PP_SMU_WESUWT_UNDEFINED = 0,
	PP_SMU_WESUWT_OK = 1,
	PP_SMU_WESUWT_FAIW,
	PP_SMU_WESUWT_UNSUPPOWTED
};

#define PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN 0x0
#define PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX 0xFFFF

enum wm_type {
	WM_TYPE_PSTATE_CHG = 0,
	WM_TYPE_WETWAINING = 1,
};

/* This stwuctuwe is a copy of WatewmawkWowGenewic_t defined by smuxx_dwivew_if.h*/
stwuct pp_smu_wm_set_wange {
	uint16_t min_fiww_cwk_mhz;
	uint16_t max_fiww_cwk_mhz;
	uint16_t min_dwain_cwk_mhz;
	uint16_t max_dwain_cwk_mhz;

	uint8_t wm_inst;
	uint8_t wm_type;
};

#define MAX_WATEWMAWK_SETS 4

stwuct pp_smu_wm_wange_sets {
	unsigned int num_weadew_wm_sets;
	stwuct pp_smu_wm_set_wange weadew_wm_sets[MAX_WATEWMAWK_SETS];

	unsigned int num_wwitew_wm_sets;
	stwuct pp_smu_wm_set_wange wwitew_wm_sets[MAX_WATEWMAWK_SETS];
};

stwuct pp_smu_funcs_wv {
	stwuct pp_smu pp_smu;

	/* PPSMC_MSG_SetDispwayCount
	 * 0 twiggews S0i2 optimization
	 */

	void (*set_dispway_count)(stwuct pp_smu *pp, int count);

	/* weadew and wwitew WM's awe sent togethew as pawt of one tabwe*/
	/*
	 * PPSMC_MSG_SetDwivewDwamAddwHigh
	 * PPSMC_MSG_SetDwivewDwamAddwWow
	 * PPSMC_MSG_TwansfewTabweDwam2Smu
	 *
	 * */
	void (*set_wm_wanges)(stwuct pp_smu *pp,
			stwuct pp_smu_wm_wange_sets *wanges);

	/* PPSMC_MSG_SetHawdMinDcfcwkByFweq
	 * fixed cwock at wequested fweq, eithew fwom FCH bypass ow DFS
	 */
	void (*set_hawd_min_dcfcwk_by_fweq)(stwuct pp_smu *pp, int mhz);

	/* PPSMC_MSG_SetMinDeepSweepDcfcwk
	 * when DF is in cstate, dcf cwock is fuwthew divided down
	 * to just above given fwequency
	 */
	void (*set_min_deep_sweep_dcfcwk)(stwuct pp_smu *pp, int mhz);

	/* PPSMC_MSG_SetHawdMinFcwkByFweq
	 * FCWK wiww vawy with DPM, but nevew bewow wequested hawd min
	 */
	void (*set_hawd_min_fcwk_by_fweq)(stwuct pp_smu *pp, int mhz);

	/* PPSMC_MSG_SetHawdMinSoccwkByFweq
	 * Needed fow DWB suppowt
	 */
	void (*set_hawd_min_soccwk_by_fweq)(stwuct pp_smu *pp, int mhz);

	/* PME w/a */
	void (*set_pme_wa_enabwe)(stwuct pp_smu *pp);
};

/* Used by pp_smu_funcs_nv.set_vowtage_by_fweq
 *
 */
enum pp_smu_nv_cwock_id {
	PP_SMU_NV_DISPCWK,
	PP_SMU_NV_PHYCWK,
	PP_SMU_NV_PIXEWCWK
};

/*
 * Used by pp_smu_funcs_nv.get_maximum_sustainabwe_cwocks
 */
stwuct pp_smu_nv_cwock_tabwe {
	// vowtage managed SMU, fweq set by dwivew
	unsigned int    dispwayCwockInKhz;
	unsigned int	dppCwockInKhz;
	unsigned int    phyCwockInKhz;
	unsigned int    pixewCwockInKhz;
	unsigned int	dscCwockInKhz;

	// fweq/vowtage managed by SMU
	unsigned int	fabwicCwockInKhz;
	unsigned int	socCwockInKhz;
	unsigned int    dcfCwockInKhz;
	unsigned int    uCwockInKhz;
};

stwuct pp_smu_funcs_nv {
	stwuct pp_smu pp_smu;

	/* PPSMC_MSG_SetDispwayCount
	 * 0 twiggews S0i2 optimization
	 */
	enum pp_smu_status (*set_dispway_count)(stwuct pp_smu *pp, int count);

	/* PPSMC_MSG_SetHawdMinDcfcwkByFweq
	 * fixed cwock at wequested fweq, eithew fwom FCH bypass ow DFS
	 */
	enum pp_smu_status (*set_hawd_min_dcfcwk_by_fweq)(stwuct pp_smu *pp, int Mhz);

	/* PPSMC_MSG_SetMinDeepSweepDcfcwk
	 * when DF is in cstate, dcf cwock is fuwthew divided down
	 * to just above given fwequency
	 */
	enum pp_smu_status (*set_min_deep_sweep_dcfcwk)(stwuct pp_smu *pp, int Mhz);

	/* PPSMC_MSG_SetHawdMinUcwkByFweq
	 * UCWK wiww vawy with DPM, but nevew bewow wequested hawd min
	 */
	enum pp_smu_status (*set_hawd_min_ucwk_by_fweq)(stwuct pp_smu *pp, int Mhz);

	/* PPSMC_MSG_SetHawdMinSoccwkByFweq
	 * Needed fow DWB suppowt
	 */
	enum pp_smu_status (*set_hawd_min_soccwk_by_fweq)(stwuct pp_smu *pp, int Mhz);

	/* PME w/a */
	enum pp_smu_status (*set_pme_wa_enabwe)(stwuct pp_smu *pp);

	/* PPSMC_MSG_SetHawdMinByFweq
	 * Needed to set ASIC vowtages fow cwocks pwogwammed by DAW
	 */
	enum pp_smu_status (*set_vowtage_by_fweq)(stwuct pp_smu *pp,
			enum pp_smu_nv_cwock_id cwock_id, int Mhz);

	/* weadew and wwitew WM's awe sent togethew as pawt of one tabwe*/
	/*
	 * PPSMC_MSG_SetDwivewDwamAddwHigh
	 * PPSMC_MSG_SetDwivewDwamAddwWow
	 * PPSMC_MSG_TwansfewTabweDwam2Smu
	 *
	 * on DCN20:
	 * 	weadew fiww cwk = ucwk
	 * 	weadew dwain cwk = dcfcwk
	 * 	wwitew fiww cwk = soccwk
	 * 	wwitew dwain cwk = ucwk
	 * */
	enum pp_smu_status (*set_wm_wanges)(stwuct pp_smu *pp,
			stwuct pp_smu_wm_wange_sets *wanges);

	/* Not a singwe SMU message.  This caww shouwd wetuwn maximum sustainabwe wimit fow aww
	 * cwocks that DC depends on.  These wiww be used as basis fow mode enumewation.
	 */
	enum pp_smu_status (*get_maximum_sustainabwe_cwocks)(stwuct pp_smu *pp,
			stwuct pp_smu_nv_cwock_tabwe *max_cwocks);

	/* This caww shouwd wetuwn the discwete ucwk DPM states avaiwabwe
	 */
	enum pp_smu_status (*get_ucwk_dpm_states)(stwuct pp_smu *pp,
			unsigned int *cwock_vawues_in_khz, unsigned int *num_states);

	/* Not a singwe SMU message.  This caww infowms PPWIB that dispway wiww not be abwe
	 * to pewfowm pstate handshaking in its cuwwent state.  Typicawwy this handshake
	 * is used to pewfowm uCWK switching, so disabwing pstate disabwes uCWK switching.
	 *
	 * Note that when setting handshake to unsuppowted, the caww is pwe-emptive.  That means
	 * DC wiww make the caww BEFOWE setting up the dispway state which wouwd cause pstate
	 * wequest to go un-acked.  Onwy when the caww compwetes shouwd such a state be appwied to
	 * DC hawdwawe
	 */
	enum pp_smu_status (*set_pstate_handshake_suppowt)(stwuct pp_smu *pp,
			boow pstate_handshake_suppowted);
};

#define PP_SMU_NUM_SOCCWK_DPM_WEVEWS  8
#define PP_SMU_NUM_DCFCWK_DPM_WEVEWS  8
#define PP_SMU_NUM_FCWK_DPM_WEVEWS    4
#define PP_SMU_NUM_MEMCWK_DPM_WEVEWS  4
#define PP_SMU_NUM_DCWK_DPM_WEVEWS    8
#define PP_SMU_NUM_VCWK_DPM_WEVEWS    8
#define PP_SMU_NUM_VPECWK_DPM_WEVEWS  8

stwuct dpm_cwock {
  uint32_t  Fweq;    // In MHz
  uint32_t  Vow;     // Miwwivowts with 2 fwactionaw bits
};


/* this is a copy of the stwuctuwe defined in smuxx_dwivew_if.h*/
stwuct dpm_cwocks {
	stwuct dpm_cwock DcfCwocks[PP_SMU_NUM_DCFCWK_DPM_WEVEWS];
	stwuct dpm_cwock SocCwocks[PP_SMU_NUM_SOCCWK_DPM_WEVEWS];
	stwuct dpm_cwock FCwocks[PP_SMU_NUM_FCWK_DPM_WEVEWS];
	stwuct dpm_cwock MemCwocks[PP_SMU_NUM_MEMCWK_DPM_WEVEWS];
	stwuct dpm_cwock VCwocks[PP_SMU_NUM_VCWK_DPM_WEVEWS];
	stwuct dpm_cwock DCwocks[PP_SMU_NUM_DCWK_DPM_WEVEWS];
	stwuct dpm_cwock VPECwocks[PP_SMU_NUM_VPECWK_DPM_WEVEWS];
};


stwuct pp_smu_funcs_wn {
	stwuct pp_smu pp_smu;

	/*
	 * weadew and wwitew WM's awe sent togethew as pawt of one tabwe
	 *
	 * PPSMC_MSG_SetDwivewDwamAddwHigh
	 * PPSMC_MSG_SetDwivewDwamAddwWow
	 * PPSMC_MSG_TwansfewTabweDwam2Smu
	 *
	 */
	enum pp_smu_status (*set_wm_wanges)(stwuct pp_smu *pp,
			stwuct pp_smu_wm_wange_sets *wanges);

	enum pp_smu_status (*get_dpm_cwock_tabwe) (stwuct pp_smu *pp,
			stwuct dpm_cwocks *cwock_tabwe);
};

stwuct pp_smu_funcs_vgh {
	stwuct pp_smu pp_smu;

	/*
	 * weadew and wwitew WM's awe sent togethew as pawt of one tabwe
	 *
	 * PPSMC_MSG_SetDwivewDwamAddwHigh
	 * PPSMC_MSG_SetDwivewDwamAddwWow
	 * PPSMC_MSG_TwansfewTabweDwam2Smu
	 *
	 */
	// TODO: Check whethew this is moved to DAW, and wemove as needed
	enum pp_smu_status (*set_wm_wanges)(stwuct pp_smu *pp,
			stwuct pp_smu_wm_wange_sets *wanges);

	// TODO: Check whethew this is moved to DAW, and wemove as needed
	enum pp_smu_status (*get_dpm_cwock_tabwe) (stwuct pp_smu *pp,
			stwuct dpm_cwocks *cwock_tabwe);

	enum pp_smu_status (*notify_smu_timeout) (stwuct pp_smu *pp);
};

stwuct pp_smu_funcs {
	stwuct pp_smu ctx;
	union {
		stwuct pp_smu_funcs_wv wv_funcs;
		stwuct pp_smu_funcs_nv nv_funcs;
		stwuct pp_smu_funcs_wn wn_funcs;
		stwuct pp_smu_funcs_vgh vgh_funcs;
	};
};

#endif /* DM_PP_SMU_IF__H */
