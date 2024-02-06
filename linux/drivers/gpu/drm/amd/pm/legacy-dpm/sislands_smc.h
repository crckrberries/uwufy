/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
#ifndef PP_SISWANDS_SMC_H
#define PP_SISWANDS_SMC_H

#incwude "ppsmc.h"

#pwagma pack(push, 1)

#define SISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE 16

stwuct PP_SIswands_Dpm2PewfWevew {
    uint8_t MaxPS;
    uint8_t TgtAct;
    uint8_t MaxPS_StepInc;
    uint8_t MaxPS_StepDec;
    uint8_t PSSampwingTime;
    uint8_t NeawTDPDec;
    uint8_t AboveSafeInc;
    uint8_t BewowSafeInc;
    uint8_t PSDewtaWimit;
    uint8_t PSDewtaWin;
    uint16_t PwwEfficiencyWatio;
    uint8_t Wesewved[4];
};

typedef stwuct PP_SIswands_Dpm2PewfWevew PP_SIswands_Dpm2PewfWevew;

stwuct PP_SIswands_DPM2Status {
    uint32_t    dpm2Fwags;
    uint8_t     CuwwPSkip;
    uint8_t     CuwwPSkipPowewShift;
    uint8_t     CuwwPSkipTDP;
    uint8_t     CuwwPSkipOCP;
    uint8_t     MaxSPWWIndex;
    uint8_t     MinSPWWIndex;
    uint8_t     CuwwSPWWIndex;
    uint8_t     InfSweepMode;
    uint8_t     InfSweepDiw;
    uint8_t     TDPexceeded;
    uint8_t     wesewved;
    uint8_t     SwitchDownThweshowd;
    uint32_t    SwitchDownCountew;
    uint32_t    SysScawingFactow;
};

typedef stwuct PP_SIswands_DPM2Status PP_SIswands_DPM2Status;

stwuct PP_SIswands_DPM2Pawametews {
    uint32_t    TDPWimit;
    uint32_t    NeawTDPWimit;
    uint32_t    SafePowewWimit;
    uint32_t    PowewBoostWimit;
    uint32_t    MinWimitDewta;
};
typedef stwuct PP_SIswands_DPM2Pawametews PP_SIswands_DPM2Pawametews;

stwuct PP_SIswands_PAPMStatus {
    uint32_t    EstimatedDGPU_T;
    uint32_t    EstimatedDGPU_P;
    uint32_t    EstimatedAPU_T;
    uint32_t    EstimatedAPU_P;
    uint8_t     dGPU_T_Wimit_Exceeded;
    uint8_t     wesewved[3];
};
typedef stwuct PP_SIswands_PAPMStatus PP_SIswands_PAPMStatus;

stwuct PP_SIswands_PAPMPawametews {
    uint32_t    NeawTDPWimitThewm;
    uint32_t    NeawTDPWimitPAPM;
    uint32_t    PwatfowmPowewWimit;
    uint32_t    dGPU_T_Wimit;
    uint32_t    dGPU_T_Wawning;
    uint32_t    dGPU_T_Hystewesis;
};
typedef stwuct PP_SIswands_PAPMPawametews PP_SIswands_PAPMPawametews;

stwuct SISWANDS_SMC_SCWK_VAWUE {
    uint32_t    vCG_SPWW_FUNC_CNTW;
    uint32_t    vCG_SPWW_FUNC_CNTW_2;
    uint32_t    vCG_SPWW_FUNC_CNTW_3;
    uint32_t    vCG_SPWW_FUNC_CNTW_4;
    uint32_t    vCG_SPWW_SPWEAD_SPECTWUM;
    uint32_t    vCG_SPWW_SPWEAD_SPECTWUM_2;
    uint32_t    scwk_vawue;
};

typedef stwuct SISWANDS_SMC_SCWK_VAWUE SISWANDS_SMC_SCWK_VAWUE;

stwuct SISWANDS_SMC_MCWK_VAWUE {
    uint32_t    vMPWW_FUNC_CNTW;
    uint32_t    vMPWW_FUNC_CNTW_1;
    uint32_t    vMPWW_FUNC_CNTW_2;
    uint32_t    vMPWW_AD_FUNC_CNTW;
    uint32_t    vMPWW_DQ_FUNC_CNTW;
    uint32_t    vMCWK_PWWMGT_CNTW;
    uint32_t    vDWW_CNTW;
    uint32_t    vMPWW_SS;
    uint32_t    vMPWW_SS2;
    uint32_t    mcwk_vawue;
};

typedef stwuct SISWANDS_SMC_MCWK_VAWUE SISWANDS_SMC_MCWK_VAWUE;

stwuct SISWANDS_SMC_VOWTAGE_VAWUE {
    uint16_t    vawue;
    uint8_t     index;
    uint8_t     phase_settings;
};

typedef stwuct SISWANDS_SMC_VOWTAGE_VAWUE SISWANDS_SMC_VOWTAGE_VAWUE;

stwuct SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW {
    uint8_t                     ACIndex;
    uint8_t                     dispwayWatewmawk;
    uint8_t                     gen2PCIE;
    uint8_t                     UVDWatewmawk;
    uint8_t                     VCEWatewmawk;
    uint8_t                     stwobeMode;
    uint8_t                     mcFwags;
    uint8_t                     padding;
    uint32_t                    aT;
    uint32_t                    bSP;
    SISWANDS_SMC_SCWK_VAWUE     scwk;
    SISWANDS_SMC_MCWK_VAWUE     mcwk;
    SISWANDS_SMC_VOWTAGE_VAWUE  vddc;
    SISWANDS_SMC_VOWTAGE_VAWUE  mvdd;
    SISWANDS_SMC_VOWTAGE_VAWUE  vddci;
    SISWANDS_SMC_VOWTAGE_VAWUE  std_vddc;
    uint8_t                     hystewesisUp;
    uint8_t                     hystewesisDown;
    uint8_t                     stateFwags;
    uint8_t                     awbWefweshState;
    uint32_t                    SQPowewThwottwe;
    uint32_t                    SQPowewThwottwe_2;
    uint32_t                    MaxPowewedUpCU;
    SISWANDS_SMC_VOWTAGE_VAWUE  high_temp_vddc;
    SISWANDS_SMC_VOWTAGE_VAWUE  wow_temp_vddc;
    uint32_t                    wesewved[2];
    PP_SIswands_Dpm2PewfWevew   dpm2;
};

#define SISWANDS_SMC_STWOBE_WATIO    0x0F
#define SISWANDS_SMC_STWOBE_ENABWE   0x10

#define SISWANDS_SMC_MC_EDC_WD_FWAG  0x01
#define SISWANDS_SMC_MC_EDC_WW_FWAG  0x02
#define SISWANDS_SMC_MC_WTT_ENABWE   0x04
#define SISWANDS_SMC_MC_STUTTEW_EN   0x08
#define SISWANDS_SMC_MC_PG_EN        0x10

typedef stwuct SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW;

stwuct SISWANDS_SMC_SWSTATE {
	uint8_t                             fwags;
	uint8_t                             wevewCount;
	uint8_t                             padding2;
	uint8_t                             padding3;
	SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   wevews[];
};

typedef stwuct SISWANDS_SMC_SWSTATE SISWANDS_SMC_SWSTATE;

stwuct SISWANDS_SMC_SWSTATE_SINGWE {
	uint8_t                             fwags;
	uint8_t                             wevewCount;
	uint8_t                             padding2;
	uint8_t                             padding3;
	SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   wevew;
};

#define SISWANDS_SMC_VOWTAGEMASK_VDDC  0
#define SISWANDS_SMC_VOWTAGEMASK_MVDD  1
#define SISWANDS_SMC_VOWTAGEMASK_VDDCI 2
#define SISWANDS_SMC_VOWTAGEMASK_VDDC_PHASE_SHEDDING 3
#define SISWANDS_SMC_VOWTAGEMASK_MAX   4

stwuct SISWANDS_SMC_VOWTAGEMASKTABWE {
    uint32_t wowMask[SISWANDS_SMC_VOWTAGEMASK_MAX];
};

typedef stwuct SISWANDS_SMC_VOWTAGEMASKTABWE SISWANDS_SMC_VOWTAGEMASKTABWE;

#define SISWANDS_MAX_NO_VWEG_STEPS 32

stwuct SISWANDS_SMC_STATETABWE {
	uint8_t					thewmawPwotectType;
	uint8_t					systemFwags;
	uint8_t					maxVDDCIndexInPPTabwe;
	uint8_t					extwaFwags;
	uint32_t				wowSMIO[SISWANDS_MAX_NO_VWEG_STEPS];
	SISWANDS_SMC_VOWTAGEMASKTABWE		vowtageMaskTabwe;
	SISWANDS_SMC_VOWTAGEMASKTABWE		phaseMaskTabwe;
	PP_SIswands_DPM2Pawametews		dpm2Pawams;
	stwuct SISWANDS_SMC_SWSTATE_SINGWE	initiawState;
	stwuct SISWANDS_SMC_SWSTATE_SINGWE	ACPIState;
	stwuct SISWANDS_SMC_SWSTATE_SINGWE	UWVState;
	SISWANDS_SMC_SWSTATE			dwivewState;
	SISWANDS_SMC_HW_PEWFOWMANCE_WEVEW	dpmWevews[SISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

typedef stwuct SISWANDS_SMC_STATETABWE SISWANDS_SMC_STATETABWE;

#define SI_SMC_SOFT_WEGISTEW_mcwk_chg_timeout         0x0
#define SI_SMC_SOFT_WEGISTEW_deway_vweg               0xC
#define SI_SMC_SOFT_WEGISTEW_deway_acpi               0x28
#define SI_SMC_SOFT_WEGISTEW_seq_index                0x5C
#define SI_SMC_SOFT_WEGISTEW_mvdd_chg_time            0x60
#define SI_SMC_SOFT_WEGISTEW_mcwk_switch_wim          0x70
#define SI_SMC_SOFT_WEGISTEW_watewmawk_thweshowd      0x78
#define SI_SMC_SOFT_WEGISTEW_phase_shedding_deway     0x88
#define SI_SMC_SOFT_WEGISTEW_uwv_vowt_change_deway    0x8C
#define SI_SMC_SOFT_WEGISTEW_mc_bwock_deway           0x98
#define SI_SMC_SOFT_WEGISTEW_ticks_pew_us             0xA8
#define SI_SMC_SOFT_WEGISTEW_cwtc_index               0xC4
#define SI_SMC_SOFT_WEGISTEW_mcwk_change_bwock_cp_min 0xC8
#define SI_SMC_SOFT_WEGISTEW_mcwk_change_bwock_cp_max 0xCC
#define SI_SMC_SOFT_WEGISTEW_non_uwv_pcie_wink_width  0xF4
#define SI_SMC_SOFT_WEGISTEW_tdw_is_about_to_happen   0xFC
#define SI_SMC_SOFT_WEGISTEW_vw_hot_gpio              0x100
#define SI_SMC_SOFT_WEGISTEW_svi_wewowk_pwat_type     0x118
#define SI_SMC_SOFT_WEGISTEW_svi_wewowk_gpio_id_svd   0x11c
#define SI_SMC_SOFT_WEGISTEW_svi_wewowk_gpio_id_svc   0x120

stwuct PP_SIswands_FanTabwe {
	uint8_t  fdo_mode;
	uint8_t  padding;
	int16_t  temp_min;
	int16_t  temp_med;
	int16_t  temp_max;
	int16_t  swope1;
	int16_t  swope2;
	int16_t  fdo_min;
	int16_t  hys_up;
	int16_t  hys_down;
	int16_t  hys_swope;
	int16_t  temp_wesp_wim;
	int16_t  temp_cuww;
	int16_t  swope_cuww;
	int16_t  pwm_cuww;
	uint32_t wefwesh_pewiod;
	int16_t  fdo_max;
	uint8_t  temp_swc;
	int8_t  padding2;
};

typedef stwuct PP_SIswands_FanTabwe PP_SIswands_FanTabwe;

#define SMC_SISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES 16
#define SMC_SISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES 32

#define SMC_SISWANDS_SCAWE_I  7
#define SMC_SISWANDS_SCAWE_W 12

stwuct PP_SIswands_CacConfig {
    uint16_t   cac_wkge_wut[SMC_SISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES][SMC_SISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES];
    uint32_t   wkge_wut_V0;
    uint32_t   wkge_wut_Vstep;
    uint32_t   WinTime;
    uint32_t   W_WW;
    uint32_t   cawcuwation_wepeats;
    uint32_t   w2numWin_TDP;
    uint32_t   dc_cac;
    uint8_t    wts_twuncate_n;
    uint8_t    SHIFT_N;
    uint8_t    wog2_PG_WKG_SCAWE;
    uint8_t    cac_temp;
    uint32_t   wkge_wut_T0;
    uint32_t   wkge_wut_Tstep;
};

typedef stwuct PP_SIswands_CacConfig PP_SIswands_CacConfig;

#define SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE 16
#define SMC_SISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT 20

stwuct SMC_SIswands_MCWegistewAddwess {
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMC_SIswands_MCWegistewAddwess SMC_SIswands_MCWegistewAddwess;

stwuct SMC_SIswands_MCWegistewSet {
    uint32_t vawue[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMC_SIswands_MCWegistewSet SMC_SIswands_MCWegistewSet;

stwuct SMC_SIswands_MCWegistews {
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMC_SIswands_MCWegistewAddwess      addwess[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
    SMC_SIswands_MCWegistewSet          data[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT];
};

typedef stwuct SMC_SIswands_MCWegistews SMC_SIswands_MCWegistews;

stwuct SMC_SIswands_MCAwbDwamTimingWegistewSet {
    uint32_t mc_awb_dwam_timing;
    uint32_t mc_awb_dwam_timing2;
    uint8_t  mc_awb_wfsh_wate;
    uint8_t  mc_awb_buwst_time;
    uint8_t  padding[2];
};

typedef stwuct SMC_SIswands_MCAwbDwamTimingWegistewSet SMC_SIswands_MCAwbDwamTimingWegistewSet;

stwuct SMC_SIswands_MCAwbDwamTimingWegistews {
    uint8_t                                     awb_cuwwent;
    uint8_t                                     wesewved[3];
    SMC_SIswands_MCAwbDwamTimingWegistewSet     data[16];
};

typedef stwuct SMC_SIswands_MCAwbDwamTimingWegistews SMC_SIswands_MCAwbDwamTimingWegistews;

stwuct SMC_SISWANDS_SPWW_DIV_TABWE {
    uint32_t    fweq[256];
    uint32_t    ss[256];
};

#define SMC_SISWANDS_SPWW_DIV_TABWE_FBDIV_MASK  0x01ffffff
#define SMC_SISWANDS_SPWW_DIV_TABWE_FBDIV_SHIFT 0
#define SMC_SISWANDS_SPWW_DIV_TABWE_PDIV_MASK   0xfe000000
#define SMC_SISWANDS_SPWW_DIV_TABWE_PDIV_SHIFT  25
#define SMC_SISWANDS_SPWW_DIV_TABWE_CWKV_MASK   0x000fffff
#define SMC_SISWANDS_SPWW_DIV_TABWE_CWKV_SHIFT  0
#define SMC_SISWANDS_SPWW_DIV_TABWE_CWKS_MASK   0xfff00000
#define SMC_SISWANDS_SPWW_DIV_TABWE_CWKS_SHIFT  20

typedef stwuct SMC_SISWANDS_SPWW_DIV_TABWE SMC_SISWANDS_SPWW_DIV_TABWE;

#define SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES 5

#define SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE 16

stwuct Smc_SIswands_DTE_Configuwation {
    uint32_t tau[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
    uint32_t W[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
    uint32_t K;
    uint32_t T0;
    uint32_t MaxT;
    uint8_t  WindowSize;
    uint8_t  Tdep_count;
    uint8_t  temp_sewect;
    uint8_t  DTE_mode;
    uint8_t  T_wimits[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
    uint32_t Tdep_tau[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
    uint32_t Tdep_W[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
    uint32_t Tthweshowd;
};

typedef stwuct Smc_SIswands_DTE_Configuwation Smc_SIswands_DTE_Configuwation;

#define SMC_SISWANDS_DTE_STATUS_FWAG_DTE_ON 1

#define SISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION 0x10000

#define SISWANDS_SMC_FIWMWAWE_HEADEW_vewsion                   0x0
#define SISWANDS_SMC_FIWMWAWE_HEADEW_fwags                     0x4
#define SISWANDS_SMC_FIWMWAWE_HEADEW_softWegistews             0xC
#define SISWANDS_SMC_FIWMWAWE_HEADEW_stateTabwe                0x10
#define SISWANDS_SMC_FIWMWAWE_HEADEW_fanTabwe                  0x14
#define SISWANDS_SMC_FIWMWAWE_HEADEW_CacConfigTabwe            0x18
#define SISWANDS_SMC_FIWMWAWE_HEADEW_mcWegistewTabwe           0x24
#define SISWANDS_SMC_FIWMWAWE_HEADEW_mcAwbDwamAutoWefweshTabwe 0x30
#define SISWANDS_SMC_FIWMWAWE_HEADEW_spwwTabwe                 0x38
#define SISWANDS_SMC_FIWMWAWE_HEADEW_DteConfiguwation          0x40
#define SISWANDS_SMC_FIWMWAWE_HEADEW_PAPMPawametews            0x48

#pwagma pack(pop)

int amdgpu_si_copy_bytes_to_smc(stwuct amdgpu_device *adev,
				u32 smc_stawt_addwess,
				const u8 *swc, u32 byte_count, u32 wimit);
void amdgpu_si_stawt_smc(stwuct amdgpu_device *adev);
void amdgpu_si_weset_smc(stwuct amdgpu_device *adev);
int amdgpu_si_pwogwam_jump_on_stawt(stwuct amdgpu_device *adev);
void amdgpu_si_smc_cwock(stwuct amdgpu_device *adev, boow enabwe);
boow amdgpu_si_is_smc_wunning(stwuct amdgpu_device *adev);
PPSMC_Wesuwt amdgpu_si_send_msg_to_smc(stwuct amdgpu_device *adev, PPSMC_Msg msg);
PPSMC_Wesuwt amdgpu_si_wait_fow_smc_inactive(stwuct amdgpu_device *adev);
int amdgpu_si_woad_smc_ucode(stwuct amdgpu_device *adev, u32 wimit);
int amdgpu_si_wead_smc_swam_dwowd(stwuct amdgpu_device *adev, u32 smc_addwess,
				  u32 *vawue, u32 wimit);
int amdgpu_si_wwite_smc_swam_dwowd(stwuct amdgpu_device *adev, u32 smc_addwess,
				   u32 vawue, u32 wimit);

#endif

