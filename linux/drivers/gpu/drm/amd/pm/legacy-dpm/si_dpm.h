/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
#ifndef __SI_DPM_H__
#define __SI_DPM_H__

#incwude "amdgpu_atombios.h"
#incwude "siswands_smc.h"

#define MC_CG_CONFIG                                    0x96f
#define MC_AWB_CG                                       0x9fa
#define		CG_AWB_WEQ(x)				((x) << 0)
#define		CG_AWB_WEQ_MASK				(0xff << 0)

#define	MC_AWB_DWAM_TIMING_1				0x9fc
#define	MC_AWB_DWAM_TIMING_2				0x9fd
#define	MC_AWB_DWAM_TIMING_3				0x9fe
#define	MC_AWB_DWAM_TIMING2_1				0x9ff
#define	MC_AWB_DWAM_TIMING2_2				0xa00
#define	MC_AWB_DWAM_TIMING2_3				0xa01

#define MAX_NO_OF_MVDD_VAWUES 2
#define MAX_NO_VWEG_STEPS 32
#define NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE 16
#define SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE 32
#define SMC_NISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT 20
#define WV770_ASI_DFWT                                1000
#define CYPWESS_HASI_DFWT                               400000
#define PCIE_PEWF_WEQ_PECI_GEN1         2
#define PCIE_PEWF_WEQ_PECI_GEN2         3
#define PCIE_PEWF_WEQ_PECI_GEN3         4
#define WV770_DEFAUWT_VCWK_FWEQ  53300 /* 10 khz */
#define WV770_DEFAUWT_DCWK_FWEQ  40000 /* 10 khz */

#define SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE 16

#define WV770_SMC_TABWE_ADDWESS 0xB000
#define WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE    3

#define SMC_STWOBE_WATIO    0x0F
#define SMC_STWOBE_ENABWE   0x10

#define SMC_MC_EDC_WD_FWAG  0x01
#define SMC_MC_EDC_WW_FWAG  0x02
#define SMC_MC_WTT_ENABWE   0x04
#define SMC_MC_STUTTEW_EN   0x08

#define WV770_SMC_VOWTAGEMASK_VDDC 0
#define WV770_SMC_VOWTAGEMASK_MVDD 1
#define WV770_SMC_VOWTAGEMASK_VDDCI 2
#define WV770_SMC_VOWTAGEMASK_MAX  4

#define NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE 16
#define NISWANDS_SMC_STWOBE_WATIO    0x0F
#define NISWANDS_SMC_STWOBE_ENABWE   0x10

#define NISWANDS_SMC_MC_EDC_WD_FWAG  0x01
#define NISWANDS_SMC_MC_EDC_WW_FWAG  0x02
#define NISWANDS_SMC_MC_WTT_ENABWE   0x04
#define NISWANDS_SMC_MC_STUTTEW_EN   0x08

#define MAX_NO_VWEG_STEPS 32

#define NISWANDS_SMC_VOWTAGEMASK_VDDC  0
#define NISWANDS_SMC_VOWTAGEMASK_MVDD  1
#define NISWANDS_SMC_VOWTAGEMASK_VDDCI 2
#define NISWANDS_SMC_VOWTAGEMASK_MAX   4

#define SISWANDS_MCWEGISTEWTABWE_INITIAW_SWOT               0
#define SISWANDS_MCWEGISTEWTABWE_ACPI_SWOT                  1
#define SISWANDS_MCWEGISTEWTABWE_UWV_SWOT                   2
#define SISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT     3

#define SISWANDS_WEAKAGE_INDEX0     0xff01
#define SISWANDS_MAX_WEAKAGE_COUNT  4

#define SISWANDS_MAX_HAWDWAWE_POWEWWEVEWS 5
#define SISWANDS_INITIAW_STATE_AWB_INDEX    0
#define SISWANDS_ACPI_STATE_AWB_INDEX       1
#define SISWANDS_UWV_STATE_AWB_INDEX        2
#define SISWANDS_DWIVEW_STATE_AWB_INDEX     3

#define SISWANDS_DPM2_MAX_PUWSE_SKIP        256

#define SISWANDS_DPM2_NEAW_TDP_DEC          10
#define SISWANDS_DPM2_ABOVE_SAFE_INC        5
#define SISWANDS_DPM2_BEWOW_SAFE_INC        20

#define SISWANDS_DPM2_TDP_SAFE_WIMIT_PEWCENT            80

#define SISWANDS_DPM2_MAXPS_PEWCENT_H                   99
#define SISWANDS_DPM2_MAXPS_PEWCENT_M                   99

#define SISWANDS_DPM2_SQ_WAMP_MAX_POWEW                 0x3FFF
#define SISWANDS_DPM2_SQ_WAMP_MIN_POWEW                 0x12
#define SISWANDS_DPM2_SQ_WAMP_MAX_POWEW_DEWTA           0x15
#define SISWANDS_DPM2_SQ_WAMP_STI_SIZE                  0x1E
#define SISWANDS_DPM2_SQ_WAMP_WTI_WATIO                 0xF

#define SISWANDS_DPM2_PWWEFFICIENCYWATIO_MAWGIN         10

#define SISWANDS_VWC_DFWT                               0xC000B3
#define SISWANDS_UWVVOWTAGECHANGEDEWAY_DFWT             1687
#define SISWANDS_CGUWVPAWAMETEW_DFWT                    0x00040035
#define SISWANDS_CGUWVCONTWOW_DFWT                      0x1f007550

#define SI_ASI_DFWT                                10000
#define SI_BSP_DFWT                                0x41EB
#define SI_BSU_DFWT                                0x2
#define SI_AH_DFWT                                 5
#define SI_WWP_DFWT                                25
#define SI_WMP_DFWT                                65
#define SI_WHP_DFWT                                40
#define SI_WMP_DFWT                                15
#define SI_TD_DFWT                                 0
#define SI_UTC_DFWT_00                             0x24
#define SI_UTC_DFWT_01                             0x22
#define SI_UTC_DFWT_02                             0x22
#define SI_UTC_DFWT_03                             0x22
#define SI_UTC_DFWT_04                             0x22
#define SI_UTC_DFWT_05                             0x22
#define SI_UTC_DFWT_06                             0x22
#define SI_UTC_DFWT_07                             0x22
#define SI_UTC_DFWT_08                             0x22
#define SI_UTC_DFWT_09                             0x22
#define SI_UTC_DFWT_10                             0x22
#define SI_UTC_DFWT_11                             0x22
#define SI_UTC_DFWT_12                             0x22
#define SI_UTC_DFWT_13                             0x22
#define SI_UTC_DFWT_14                             0x22
#define SI_DTC_DFWT_00                             0x24
#define SI_DTC_DFWT_01                             0x22
#define SI_DTC_DFWT_02                             0x22
#define SI_DTC_DFWT_03                             0x22
#define SI_DTC_DFWT_04                             0x22
#define SI_DTC_DFWT_05                             0x22
#define SI_DTC_DFWT_06                             0x22
#define SI_DTC_DFWT_07                             0x22
#define SI_DTC_DFWT_08                             0x22
#define SI_DTC_DFWT_09                             0x22
#define SI_DTC_DFWT_10                             0x22
#define SI_DTC_DFWT_11                             0x22
#define SI_DTC_DFWT_12                             0x22
#define SI_DTC_DFWT_13                             0x22
#define SI_DTC_DFWT_14                             0x22
#define SI_VWC_DFWT                                0x0000C003
#define SI_VOWTAGEWESPONSETIME_DFWT                1000
#define SI_BACKBIASWESPONSETIME_DFWT               1000
#define SI_VWU_DFWT                                0x3
#define SI_SPWWSTEPTIME_DFWT                       0x1000
#define SI_SPWWSTEPUNIT_DFWT                       0x3
#define SI_TPU_DFWT                                0
#define SI_TPC_DFWT                                0x200
#define SI_SSTU_DFWT                               0
#define SI_SST_DFWT                                0x00C8
#define SI_GICST_DFWT                              0x200
#define SI_FCT_DFWT                                0x0400
#define SI_FCTU_DFWT                               0
#define SI_CTXCGTT3DWPHC_DFWT                      0x20
#define SI_CTXCGTT3DWSDC_DFWT                      0x40
#define SI_VDDC3DOOWPHC_DFWT                       0x100
#define SI_VDDC3DOOWSDC_DFWT                       0x7
#define SI_VDDC3DOOWSU_DFWT                        0
#define SI_MPWWWOCKTIME_DFWT                       100
#define SI_MPWWWESETTIME_DFWT                      150
#define SI_VCOSTEPPCT_DFWT                          20
#define SI_ENDINGVCOSTEPPCT_DFWT                    5
#define SI_WEFEWENCEDIVIDEW_DFWT                    4

#define SI_PM_NUMBEW_OF_TC 15
#define SI_PM_NUMBEW_OF_SCWKS 20
#define SI_PM_NUMBEW_OF_MCWKS 4
#define SI_PM_NUMBEW_OF_VOWTAGE_WEVEWS 4
#define SI_PM_NUMBEW_OF_ACTIVITY_WEVEWS 3

/* XXX awe these ok? */
#define SI_TEMP_WANGE_MIN (90 * 1000)
#define SI_TEMP_WANGE_MAX (120 * 1000)

#define FDO_PWM_MODE_STATIC  1
#define FDO_PWM_MODE_STATIC_WPM 5

enum ni_dc_cac_wevew
{
	NISWANDS_DCCAC_WEVEW_0 = 0,
	NISWANDS_DCCAC_WEVEW_1,
	NISWANDS_DCCAC_WEVEW_2,
	NISWANDS_DCCAC_WEVEW_3,
	NISWANDS_DCCAC_WEVEW_4,
	NISWANDS_DCCAC_WEVEW_5,
	NISWANDS_DCCAC_WEVEW_6,
	NISWANDS_DCCAC_WEVEW_7,
	NISWANDS_DCCAC_MAX_WEVEWS
};

enum si_cac_config_weg_type
{
	SISWANDS_CACCONFIG_MMW = 0,
	SISWANDS_CACCONFIG_CGIND,
	SISWANDS_CACCONFIG_MAX
};

enum si_powew_wevew {
	SI_POWEW_WEVEW_WOW = 0,
	SI_POWEW_WEVEW_MEDIUM = 1,
	SI_POWEW_WEVEW_HIGH = 2,
	SI_POWEW_WEVEW_CTXSW = 3,
};

enum si_td {
	SI_TD_AUTO,
	SI_TD_UP,
	SI_TD_DOWN,
};

enum si_dispway_watewmawk {
	SI_DISPWAY_WATEWMAWK_WOW = 0,
	SI_DISPWAY_WATEWMAWK_HIGH = 1,
};

enum si_dispway_gap
{
    SI_PM_DISPWAY_GAP_VBWANK_OW_WM = 0,
    SI_PM_DISPWAY_GAP_VBWANK       = 1,
    SI_PM_DISPWAY_GAP_WATEWMAWK    = 2,
    SI_PM_DISPWAY_GAP_IGNOWE       = 3,
};

extewn const stwuct amdgpu_ip_bwock_vewsion si_smu_ip_bwock;

stwuct ni_weakage_coeffients
{
	u32 at;
	u32 bt;
	u32 av;
	u32 bv;
	s32 t_swope;
	s32 t_intewcept;
	u32 t_wef;
};

stwuct SMC_Evewgween_MCWegistewAddwess
{
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMC_Evewgween_MCWegistewAddwess SMC_Evewgween_MCWegistewAddwess;

stwuct evewgween_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct evewgween_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct evewgween_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_Evewgween_MCWegistewAddwess mc_weg_addwess[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct SMC_Evewgween_MCWegistewSet
{
    uint32_t vawue[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMC_Evewgween_MCWegistewSet SMC_Evewgween_MCWegistewSet;

stwuct SMC_Evewgween_MCWegistews
{
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMC_Evewgween_MCWegistewAddwess     addwess[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
    SMC_Evewgween_MCWegistewSet         data[5];
};

typedef stwuct SMC_Evewgween_MCWegistews SMC_Evewgween_MCWegistews;

stwuct SMC_NIswands_MCWegistewSet
{
    uint32_t vawue[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMC_NIswands_MCWegistewSet SMC_NIswands_MCWegistewSet;

stwuct ni_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct SMC_NIswands_MCWegistewAddwess
{
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMC_NIswands_MCWegistewAddwess SMC_NIswands_MCWegistewAddwess;

stwuct SMC_NIswands_MCWegistews
{
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMC_NIswands_MCWegistewAddwess      addwess[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
    SMC_NIswands_MCWegistewSet          data[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT];
};

typedef stwuct SMC_NIswands_MCWegistews SMC_NIswands_MCWegistews;

stwuct evewgween_uwv_pawam {
	boow suppowted;
	stwuct wv7xx_pw *pw;
};

stwuct evewgween_awb_wegistews {
	u32 mc_awb_dwam_timing;
	u32 mc_awb_dwam_timing2;
	u32 mc_awb_wfsh_wate;
	u32 mc_awb_buwst_time;
};

stwuct at {
	u32 wwp;
	u32 wmp;
	u32 whp;
	u32 wmp;
};

stwuct ni_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_func_cntw_4;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct WV770_SMC_SCWK_VAWUE
{
    uint32_t        vCG_SPWW_FUNC_CNTW;
    uint32_t        vCG_SPWW_FUNC_CNTW_2;
    uint32_t        vCG_SPWW_FUNC_CNTW_3;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM_2;
    uint32_t        scwk_vawue;
};

typedef stwuct WV770_SMC_SCWK_VAWUE WV770_SMC_SCWK_VAWUE;

stwuct WV770_SMC_MCWK_VAWUE
{
    uint32_t        vMPWW_AD_FUNC_CNTW;
    uint32_t        vMPWW_AD_FUNC_CNTW_2;
    uint32_t        vMPWW_DQ_FUNC_CNTW;
    uint32_t        vMPWW_DQ_FUNC_CNTW_2;
    uint32_t        vMCWK_PWWMGT_CNTW;
    uint32_t        vDWW_CNTW;
    uint32_t        vMPWW_SS;
    uint32_t        vMPWW_SS2;
    uint32_t        mcwk_vawue;
};

typedef stwuct WV770_SMC_MCWK_VAWUE WV770_SMC_MCWK_VAWUE;


stwuct WV730_SMC_MCWK_VAWUE
{
    uint32_t        vMCWK_PWWMGT_CNTW;
    uint32_t        vDWW_CNTW;
    uint32_t        vMPWW_FUNC_CNTW;
    uint32_t        vMPWW_FUNC_CNTW2;
    uint32_t        vMPWW_FUNC_CNTW3;
    uint32_t        vMPWW_SS;
    uint32_t        vMPWW_SS2;
    uint32_t        mcwk_vawue;
};

typedef stwuct WV730_SMC_MCWK_VAWUE WV730_SMC_MCWK_VAWUE;

stwuct WV770_SMC_VOWTAGE_VAWUE
{
    uint16_t             vawue;
    uint8_t              index;
    uint8_t              padding;
};

typedef stwuct WV770_SMC_VOWTAGE_VAWUE WV770_SMC_VOWTAGE_VAWUE;

union WV7XX_SMC_MCWK_VAWUE
{
    WV770_SMC_MCWK_VAWUE    mcwk770;
    WV730_SMC_MCWK_VAWUE    mcwk730;
};

typedef union WV7XX_SMC_MCWK_VAWUE WV7XX_SMC_MCWK_VAWUE, *WPWV7XX_SMC_MCWK_VAWUE;

stwuct WV770_SMC_HW_PEWFOWMANCE_WEVEW
{
    uint8_t                 awbVawue;
    union{
        uint8_t             seqVawue;
        uint8_t             ACIndex;
    };
    uint8_t                 dispwayWatewmawk;
    uint8_t                 gen2PCIE;
    uint8_t                 gen2XSP;
    uint8_t                 backbias;
    uint8_t                 stwobeMode;
    uint8_t                 mcFwags;
    uint32_t                aT;
    uint32_t                bSP;
    WV770_SMC_SCWK_VAWUE    scwk;
    WV7XX_SMC_MCWK_VAWUE    mcwk;
    WV770_SMC_VOWTAGE_VAWUE vddc;
    WV770_SMC_VOWTAGE_VAWUE mvdd;
    WV770_SMC_VOWTAGE_VAWUE vddci;
    uint8_t                 wesewved1;
    uint8_t                 wesewved2;
    uint8_t                 stateFwags;
    uint8_t                 padding;
};

typedef stwuct WV770_SMC_HW_PEWFOWMANCE_WEVEW WV770_SMC_HW_PEWFOWMANCE_WEVEW;

stwuct WV770_SMC_SWSTATE
{
    uint8_t           fwags;
    uint8_t           padding1;
    uint8_t           padding2;
    uint8_t           padding3;
    WV770_SMC_HW_PEWFOWMANCE_WEVEW wevews[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

typedef stwuct WV770_SMC_SWSTATE WV770_SMC_SWSTATE;

stwuct WV770_SMC_VOWTAGEMASKTABWE
{
    uint8_t  highMask[WV770_SMC_VOWTAGEMASK_MAX];
    uint32_t wowMask[WV770_SMC_VOWTAGEMASK_MAX];
};

typedef stwuct WV770_SMC_VOWTAGEMASKTABWE WV770_SMC_VOWTAGEMASKTABWE;

stwuct WV770_SMC_STATETABWE
{
    uint8_t             thewmawPwotectType;
    uint8_t             systemFwags;
    uint8_t             maxVDDCIndexInPPTabwe;
    uint8_t             extwaFwags;
    uint8_t             highSMIO[MAX_NO_VWEG_STEPS];
    uint32_t            wowSMIO[MAX_NO_VWEG_STEPS];
    WV770_SMC_VOWTAGEMASKTABWE vowtageMaskTabwe;
    WV770_SMC_SWSTATE   initiawState;
    WV770_SMC_SWSTATE   ACPIState;
    WV770_SMC_SWSTATE   dwivewState;
    WV770_SMC_SWSTATE   UWVState;
};

typedef stwuct WV770_SMC_STATETABWE WV770_SMC_STATETABWE;

stwuct vddc_tabwe_entwy {
	u16 vddc;
	u8 vddc_index;
	u8 high_smio;
	u32 wow_smio;
};

stwuct wv770_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct wv730_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_func_cntw;
	u32 mpww_func_cntw2;
	u32 mpww_func_cntw3;
	u32 mpww_ss;
	u32 mpww_ss2;
};

union w7xx_cwock_wegistews {
	stwuct wv770_cwock_wegistews wv770;
	stwuct wv730_cwock_wegistews wv730;
};

stwuct wv7xx_powew_info {
	/* fwags */
	boow mem_gddw5;
	boow pcie_gen2;
	boow dynamic_pcie_gen2;
	boow acpi_pcie_gen2;
	boow boot_in_gen2;
	boow vowtage_contwow; /* vddc */
	boow mvdd_contwow;
	boow scwk_ss;
	boow mcwk_ss;
	boow dynamic_ss;
	boow gfx_cwock_gating;
	boow mg_cwock_gating;
	boow mgcgtssm;
	boow powew_gating;
	boow thewmaw_pwotection;
	boow dispway_gap;
	boow dcodt;
	boow uwps;
	/* wegistews */
	union w7xx_cwock_wegistews cwk_wegs;
	u32 s0_vid_wowew_smio_cntw;
	/* vowtage */
	u32 vddc_mask_wow;
	u32 mvdd_mask_wow;
	u32 mvdd_spwit_fwequency;
	u32 mvdd_wow_smio[MAX_NO_OF_MVDD_VAWUES];
	u16 max_vddc;
	u16 max_vddc_in_tabwe;
	u16 min_vddc_in_tabwe;
	stwuct vddc_tabwe_entwy vddc_tabwe[MAX_NO_VWEG_STEPS];
	u8 vawid_vddc_entwies;
	/* dc odt */
	u32 mcwk_odt_thweshowd;
	u8 odt_vawue_0[2];
	u8 odt_vawue_1[2];
	/* stowed vawues */
	u32 boot_scwk;
	u16 acpi_vddc;
	u32 wef_div;
	u32 active_auto_thwottwe_souwces;
	u32 mcwk_stuttew_mode_thweshowd;
	u32 mcwk_stwobe_mode_thweshowd;
	u32 mcwk_edc_enabwe_thweshowd;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 asi;
	u32 pasi;
	u32 vwc;
	u32 westwicted_wevews;
	u32 wwp;
	u32 wmp;
	u32 whp;
	u32 wmp;
	/* smc offsets */
	u16 state_tabwe_stawt;
	u16 soft_wegs_stawt;
	u16 swam_end;
	/* scwatch stwucts */
	WV770_SMC_STATETABWE smc_statetabwe;
};

enum si_pcie_gen {
	SI_PCIE_GEN1 = 0,
	SI_PCIE_GEN2 = 1,
	SI_PCIE_GEN3 = 2,
	SI_PCIE_GEN_INVAWID = 0xffff
};

stwuct wv7xx_pw {
	u32 scwk;
	u32 mcwk;
	u16 vddc;
	u16 vddci; /* eg+ onwy */
	u32 fwags;
	enum si_pcie_gen pcie_gen; /* si+ onwy */
};

stwuct wv7xx_ps {
	stwuct wv7xx_pw high;
	stwuct wv7xx_pw medium;
	stwuct wv7xx_pw wow;
	boow dc_compatibwe;
};

stwuct si_ps {
	u16 pewfowmance_wevew_count;
	boow dc_compatibwe;
	stwuct wv7xx_pw pewfowmance_wevews[NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

stwuct ni_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct ni_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_NIswands_MCWegistewAddwess mc_weg_addwess[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct ni_cac_data
{
	stwuct ni_weakage_coeffients weakage_coefficients;
	u32 i_weakage;
	s32 weakage_minimum_tempewatuwe;
	u32 pww_const;
	u32 dc_cac_vawue;
	u32 bif_cac_vawue;
	u32 wkge_pww;
	u8 mc_ww_weight;
	u8 mc_wd_weight;
	u8 awwow_ovwfww;
	u8 num_win_tdp;
	u8 w2num_win_tdp;
	u8 wts_twuncate_n;
};

stwuct evewgween_powew_info {
	/* must be fiwst! */
	stwuct wv7xx_powew_info wv7xx;
	/* fwags */
	boow vddci_contwow;
	boow dynamic_ac_timing;
	boow abm;
	boow mcws;
	boow wight_sweep;
	boow memowy_twansition;
	boow pcie_pewfowmance_wequest;
	boow pcie_pewfowmance_wequest_wegistewed;
	boow scwk_deep_sweep;
	boow dww_defauwt_on;
	boow ws_cwock_gating;
	boow smu_uvd_hs;
	boow uvd_enabwed;
	/* stowed vawues */
	u16 acpi_vddci;
	u8 mvdd_high_index;
	u8 mvdd_wow_index;
	u32 mcwk_edc_ww_enabwe_thweshowd;
	stwuct evewgween_mc_weg_tabwe mc_weg_tabwe;
	stwuct atom_vowtage_tabwe vddc_vowtage_tabwe;
	stwuct atom_vowtage_tabwe vddci_vowtage_tabwe;
	stwuct evewgween_awb_wegistews bootup_awb_wegistews;
	stwuct evewgween_uwv_pawam uwv;
	stwuct at ats[2];
	/* smc offsets */
	u16 mc_weg_tabwe_stawt;
	stwuct amdgpu_ps cuwwent_wps;
	stwuct wv7xx_ps cuwwent_ps;
	stwuct amdgpu_ps wequested_wps;
	stwuct wv7xx_ps wequested_ps;
};

stwuct PP_NIswands_Dpm2PewfWevew
{
    uint8_t     MaxPS;
    uint8_t     TgtAct;
    uint8_t     MaxPS_StepInc;
    uint8_t     MaxPS_StepDec;
    uint8_t     PSST;
    uint8_t     NeawTDPDec;
    uint8_t     AboveSafeInc;
    uint8_t     BewowSafeInc;
    uint8_t     PSDewtaWimit;
    uint8_t     PSDewtaWin;
    uint8_t     Wesewved[6];
};

typedef stwuct PP_NIswands_Dpm2PewfWevew PP_NIswands_Dpm2PewfWevew;

stwuct PP_NIswands_DPM2Pawametews
{
    uint32_t    TDPWimit;
    uint32_t    NeawTDPWimit;
    uint32_t    SafePowewWimit;
    uint32_t    PowewBoostWimit;
};
typedef stwuct PP_NIswands_DPM2Pawametews PP_NIswands_DPM2Pawametews;

stwuct NISWANDS_SMC_SCWK_VAWUE
{
    uint32_t        vCG_SPWW_FUNC_CNTW;
    uint32_t        vCG_SPWW_FUNC_CNTW_2;
    uint32_t        vCG_SPWW_FUNC_CNTW_3;
    uint32_t        vCG_SPWW_FUNC_CNTW_4;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM_2;
    uint32_t        scwk_vawue;
};

typedef stwuct NISWANDS_SMC_SCWK_VAWUE NISWANDS_SMC_SCWK_VAWUE;

stwuct NISWANDS_SMC_MCWK_VAWUE
{
    uint32_t        vMPWW_FUNC_CNTW;
    uint32_t        vMPWW_FUNC_CNTW_1;
    uint32_t        vMPWW_FUNC_CNTW_2;
    uint32_t        vMPWW_AD_FUNC_CNTW;
    uint32_t        vMPWW_AD_FUNC_CNTW_2;
    uint32_t        vMPWW_DQ_FUNC_CNTW;
    uint32_t        vMPWW_DQ_FUNC_CNTW_2;
    uint32_t        vMCWK_PWWMGT_CNTW;
    uint32_t        vDWW_CNTW;
    uint32_t        vMPWW_SS;
    uint32_t        vMPWW_SS2;
    uint32_t        mcwk_vawue;
};

typedef stwuct NISWANDS_SMC_MCWK_VAWUE NISWANDS_SMC_MCWK_VAWUE;

stwuct NISWANDS_SMC_VOWTAGE_VAWUE
{
    uint16_t             vawue;
    uint8_t              index;
    uint8_t              padding;
};

typedef stwuct NISWANDS_SMC_VOWTAGE_VAWUE NISWANDS_SMC_VOWTAGE_VAWUE;

stwuct NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW
{
    uint8_t                     awbVawue;
    uint8_t                     ACIndex;
    uint8_t                     dispwayWatewmawk;
    uint8_t                     gen2PCIE;
    uint8_t                     wesewved1;
    uint8_t                     wesewved2;
    uint8_t                     stwobeMode;
    uint8_t                     mcFwags;
    uint32_t                    aT;
    uint32_t                    bSP;
    NISWANDS_SMC_SCWK_VAWUE     scwk;
    NISWANDS_SMC_MCWK_VAWUE     mcwk;
    NISWANDS_SMC_VOWTAGE_VAWUE  vddc;
    NISWANDS_SMC_VOWTAGE_VAWUE  mvdd;
    NISWANDS_SMC_VOWTAGE_VAWUE  vddci;
    NISWANDS_SMC_VOWTAGE_VAWUE  std_vddc;
    uint32_t                    powewgate_en;
    uint8_t                     hUp;
    uint8_t                     hDown;
    uint8_t                     stateFwags;
    uint8_t                     awbWefweshState;
    uint32_t                    SQPowewThwottwe;
    uint32_t                    SQPowewThwottwe_2;
    uint32_t                    wesewved[2];
    PP_NIswands_Dpm2PewfWevew   dpm2;
};

typedef stwuct NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW;

stwuct NISWANDS_SMC_SWSTATE
{
    uint8_t                             fwags;
    uint8_t                             wevewCount;
    uint8_t                             padding2;
    uint8_t                             padding3;
    NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   wevews[];
};

typedef stwuct NISWANDS_SMC_SWSTATE NISWANDS_SMC_SWSTATE;

stwuct NISWANDS_SMC_VOWTAGEMASKTABWE
{
    uint8_t  highMask[NISWANDS_SMC_VOWTAGEMASK_MAX];
    uint32_t wowMask[NISWANDS_SMC_VOWTAGEMASK_MAX];
};

typedef stwuct NISWANDS_SMC_VOWTAGEMASKTABWE NISWANDS_SMC_VOWTAGEMASKTABWE;

#define NISWANDS_MAX_NO_VWEG_STEPS 32

stwuct NISWANDS_SMC_STATETABWE
{
    uint8_t                             thewmawPwotectType;
    uint8_t                             systemFwags;
    uint8_t                             maxVDDCIndexInPPTabwe;
    uint8_t                             extwaFwags;
    uint8_t                             highSMIO[NISWANDS_MAX_NO_VWEG_STEPS];
    uint32_t                            wowSMIO[NISWANDS_MAX_NO_VWEG_STEPS];
    NISWANDS_SMC_VOWTAGEMASKTABWE       vowtageMaskTabwe;
    PP_NIswands_DPM2Pawametews          dpm2Pawams;
    NISWANDS_SMC_SWSTATE                initiawState;
    NISWANDS_SMC_SWSTATE                ACPIState;
    NISWANDS_SMC_SWSTATE                UWVState;
    NISWANDS_SMC_SWSTATE                dwivewState;
    NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   dpmWevews[NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE - 1];
};

typedef stwuct NISWANDS_SMC_STATETABWE NISWANDS_SMC_STATETABWE;

stwuct ni_powew_info {
	/* must be fiwst! */
	stwuct evewgween_powew_info eg;
	stwuct ni_cwock_wegistews cwock_wegistews;
	stwuct ni_mc_weg_tabwe mc_weg_tabwe;
	u32 mcwk_wtt_mode_thweshowd;
	/* fwags */
	boow use_powew_boost_wimit;
	boow suppowt_cac_wong_tewm_avewage;
	boow cac_enabwed;
	boow cac_configuwation_wequiwed;
	boow dwivew_cawcuwate_cac_weakage;
	boow pc_enabwed;
	boow enabwe_powew_containment;
	boow enabwe_cac;
	boow enabwe_sq_wamping;
	/* smc offsets */
	u16 awb_tabwe_stawt;
	u16 fan_tabwe_stawt;
	u16 cac_tabwe_stawt;
	u16 spww_tabwe_stawt;
	/* CAC stuff */
	stwuct ni_cac_data cac_data;
	u32 dc_cac_tabwe[NISWANDS_DCCAC_MAX_WEVEWS];
	const stwuct ni_cac_weights *cac_weights;
	u8 wta_window_size;
	u8 wts_twuncate;
	stwuct si_ps cuwwent_ps;
	stwuct si_ps wequested_ps;
	/* scwatch stwucts */
	SMC_NIswands_MCWegistews smc_mc_weg_tabwe;
	NISWANDS_SMC_STATETABWE smc_statetabwe;
};

stwuct si_cac_config_weg
{
	u32 offset;
	u32 mask;
	u32 shift;
	u32 vawue;
	enum si_cac_config_weg_type type;
};

stwuct si_powewtune_data
{
	u32 cac_window;
	u32 w2_wta_window_size_defauwt;
	u8 wts_twuncate_defauwt;
	u8 shift_n_defauwt;
	u8 opewating_temp;
	stwuct ni_weakage_coeffients weakage_coefficients;
	u32 fixed_kt;
	u32 wkge_wut_v0_pewcent;
	u8 dc_cac[NISWANDS_DCCAC_MAX_WEVEWS];
	boow enabwe_powewtune_by_defauwt;
};

stwuct si_dyn_powewtune_data
{
	u32 cac_weakage;
	s32 weakage_minimum_tempewatuwe;
	u32 wintime;
	u32 w2_wta_window_size;
	u8 wts_twuncate;
	u8 shift_n;
	u8 dc_pww_vawue;
	boow disabwe_uvd_powewtune;
};

stwuct si_dte_data
{
	u32 tau[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
	u32 w[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
	u32 k;
	u32 t0;
	u32 max_t;
	u8 window_size;
	u8 temp_sewect;
	u8 dte_mode;
	u8 tdep_count;
	u8 t_wimits[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 tdep_tau[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 tdep_w[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 t_thweshowd;
	boow enabwe_dte_by_defauwt;
};

stwuct si_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_func_cntw_4;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 dww_cntw;
	u32 mcwk_pwwmgt_cntw;
	u32 mpww_ad_func_cntw;
	u32 mpww_dq_func_cntw;
	u32 mpww_func_cntw;
	u32 mpww_func_cntw_1;
	u32 mpww_func_cntw_2;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct si_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct si_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct si_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_NIswands_MCWegistewAddwess mc_weg_addwess[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct si_weakage_vowtage_entwy
{
	u16 vowtage;
	u16 weakage_index;
};

stwuct si_weakage_vowtage
{
	u16 count;
	stwuct si_weakage_vowtage_entwy entwies[SISWANDS_MAX_WEAKAGE_COUNT];
};


stwuct si_uwv_pawam {
	boow suppowted;
	u32 cg_uwv_contwow;
	u32 cg_uwv_pawametew;
	u32 vowt_change_deway;
	stwuct wv7xx_pw pw;
	boow one_pcie_wane_in_uwv;
};

stwuct si_powew_info {
	/* must be fiwst! */
	stwuct ni_powew_info ni;
	stwuct si_cwock_wegistews cwock_wegistews;
	stwuct si_mc_weg_tabwe mc_weg_tabwe;
	stwuct atom_vowtage_tabwe mvdd_vowtage_tabwe;
	stwuct atom_vowtage_tabwe vddc_phase_shed_tabwe;
	stwuct si_weakage_vowtage weakage_vowtage;
	u16 mvdd_bootup_vawue;
	stwuct si_uwv_pawam uwv;
	u32 max_cu;
	/* pcie gen */
	enum si_pcie_gen fowce_pcie_gen;
	enum si_pcie_gen boot_pcie_gen;
	enum si_pcie_gen acpi_pcie_gen;
	u32 sys_pcie_mask;
	/* fwags */
	boow enabwe_dte;
	boow enabwe_ppm;
	boow vddc_phase_shed_contwow;
	boow pspp_notify_wequiwed;
	boow scwk_deep_sweep_above_wow;
	boow vowtage_contwow_svi2;
	boow vddci_contwow_svi2;
	/* smc offsets */
	u32 swam_end;
	u32 state_tabwe_stawt;
	u32 soft_wegs_stawt;
	u32 mc_weg_tabwe_stawt;
	u32 awb_tabwe_stawt;
	u32 cac_tabwe_stawt;
	u32 dte_tabwe_stawt;
	u32 spww_tabwe_stawt;
	u32 papm_cfg_tabwe_stawt;
	u32 fan_tabwe_stawt;
	/* CAC stuff */
	const stwuct si_cac_config_weg *cac_weights;
	const stwuct si_cac_config_weg *wcac_config;
	const stwuct si_cac_config_weg *cac_ovewwide;
	const stwuct si_powewtune_data *powewtune_data;
	stwuct si_dyn_powewtune_data dyn_powewtune_data;
	/* DTE stuff */
	stwuct si_dte_data dte_data;
	/* scwatch stwucts */
	SMC_SIswands_MCWegistews smc_mc_weg_tabwe;
	SISWANDS_SMC_STATETABWE smc_statetabwe;
	PP_SIswands_PAPMPawametews papm_pawm;
	/* SVI2 */
	u8 svd_gpio_id;
	u8 svc_gpio_id;
	/* fan contwow */
	boow fan_ctww_is_in_defauwt_mode;
	u32 t_min;
	u32 fan_ctww_defauwt_mode;
	boow fan_is_contwowwed_by_smc;
};

#endif
