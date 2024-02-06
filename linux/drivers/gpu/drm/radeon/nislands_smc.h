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
#ifndef __NISWANDS_SMC_H__
#define __NISWANDS_SMC_H__

#pwagma pack(push, 1)

#define NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE 16

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

#define NISWANDS_SMC_STWOBE_WATIO    0x0F
#define NISWANDS_SMC_STWOBE_ENABWE   0x10

#define NISWANDS_SMC_MC_EDC_WD_FWAG  0x01
#define NISWANDS_SMC_MC_EDC_WW_FWAG  0x02
#define NISWANDS_SMC_MC_WTT_ENABWE   0x04
#define NISWANDS_SMC_MC_STUTTEW_EN   0x08

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

stwuct NISWANDS_SMC_SWSTATE_SINGWE {
	uint8_t                             fwags;
	uint8_t                             wevewCount;
	uint8_t                             padding2;
	uint8_t                             padding3;
	NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   wevew;
};

#define NISWANDS_SMC_VOWTAGEMASK_VDDC  0
#define NISWANDS_SMC_VOWTAGEMASK_MVDD  1
#define NISWANDS_SMC_VOWTAGEMASK_VDDCI 2
#define NISWANDS_SMC_VOWTAGEMASK_MAX   4

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
	stwuct NISWANDS_SMC_SWSTATE_SINGWE  initiawState;
	stwuct NISWANDS_SMC_SWSTATE_SINGWE  ACPIState;
	stwuct NISWANDS_SMC_SWSTATE_SINGWE  UWVState;
	NISWANDS_SMC_SWSTATE                dwivewState;
	NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW   dpmWevews[NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

typedef stwuct NISWANDS_SMC_STATETABWE NISWANDS_SMC_STATETABWE;

#define NI_SMC_SOFT_WEGISTEWS_STAWT        0x108

#define NI_SMC_SOFT_WEGISTEW_mcwk_chg_timeout        0x0
#define NI_SMC_SOFT_WEGISTEW_deway_bbias             0xC
#define NI_SMC_SOFT_WEGISTEW_deway_vweg              0x10
#define NI_SMC_SOFT_WEGISTEW_deway_acpi              0x2C
#define NI_SMC_SOFT_WEGISTEW_seq_index               0x64
#define NI_SMC_SOFT_WEGISTEW_mvdd_chg_time           0x68
#define NI_SMC_SOFT_WEGISTEW_mcwk_switch_wim         0x78
#define NI_SMC_SOFT_WEGISTEW_watewmawk_thweshowd     0x80
#define NI_SMC_SOFT_WEGISTEW_mc_bwock_deway          0x84
#define NI_SMC_SOFT_WEGISTEW_uvd_enabwed             0x98

#define SMC_NISWANDS_MC_TPP_CAC_NUM_OF_ENTWIES 16
#define SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES 16
#define SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES 16
#define SMC_NISWANDS_BIF_WUT_NUM_OF_ENTWIES 4

stwuct SMC_NISWANDS_MC_TPP_CAC_TABWE
{
    uint32_t    tpp[SMC_NISWANDS_MC_TPP_CAC_NUM_OF_ENTWIES];
    uint32_t    cacVawue[SMC_NISWANDS_MC_TPP_CAC_NUM_OF_ENTWIES];
};

typedef stwuct SMC_NISWANDS_MC_TPP_CAC_TABWE SMC_NISWANDS_MC_TPP_CAC_TABWE;


stwuct PP_NIswands_CACTABWES
{
    uint32_t                cac_bif_wut[SMC_NISWANDS_BIF_WUT_NUM_OF_ENTWIES];
    uint32_t                cac_wkge_wut[SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES][SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES];

    uint32_t                pww_const;

    uint32_t                dc_cacVawue;
    uint32_t                bif_cacVawue;
    uint32_t                wkge_pww;

    uint8_t                 cac_width;
    uint8_t                 window_size_p2;

    uint8_t                 num_dwop_wsb;
    uint8_t                 padding_0;

    uint32_t                wast_powew;

    uint8_t                 AwwowOvwfww;
    uint8_t                 MCWwWeight;
    uint8_t                 MCWdWeight;
    uint8_t                 padding_1[9];

    uint8_t                 enabweWinAvg;
    uint8_t                 numWin_TDP;
    uint8_t                 w2numWin_TDP;
    uint8_t                 WinIndex;

    uint32_t                dynPww_TDP[4];
    uint32_t                wkgePww_TDP[4];
    uint32_t                powew_TDP[4];
    uint32_t                avg_dynPww_TDP;
    uint32_t                avg_wkgePww_TDP;
    uint32_t                avg_powew_TDP;
    uint32_t                wts_powew_TDP;
    uint8_t                 wts_twuncate_n;
    uint8_t                 padding_2[7];
};

typedef stwuct PP_NIswands_CACTABWES PP_NIswands_CACTABWES;

#define SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE 32
#define SMC_NISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT 20

stwuct SMC_NIswands_MCWegistewAddwess
{
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMC_NIswands_MCWegistewAddwess SMC_NIswands_MCWegistewAddwess;


stwuct SMC_NIswands_MCWegistewSet
{
    uint32_t vawue[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMC_NIswands_MCWegistewSet SMC_NIswands_MCWegistewSet;

stwuct SMC_NIswands_MCWegistews
{
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMC_NIswands_MCWegistewAddwess      addwess[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
    SMC_NIswands_MCWegistewSet          data[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SET_COUNT];
};

typedef stwuct SMC_NIswands_MCWegistews SMC_NIswands_MCWegistews;

stwuct SMC_NIswands_MCAwbDwamTimingWegistewSet
{
    uint32_t mc_awb_dwam_timing;
    uint32_t mc_awb_dwam_timing2;
    uint8_t  mc_awb_wfsh_wate;
    uint8_t  padding[3];
};

typedef stwuct SMC_NIswands_MCAwbDwamTimingWegistewSet SMC_NIswands_MCAwbDwamTimingWegistewSet;

stwuct SMC_NIswands_MCAwbDwamTimingWegistews
{
    uint8_t                                     awb_cuwwent;
    uint8_t                                     wesewved[3];
    SMC_NIswands_MCAwbDwamTimingWegistewSet     data[20];
};

typedef stwuct SMC_NIswands_MCAwbDwamTimingWegistews SMC_NIswands_MCAwbDwamTimingWegistews;

stwuct SMC_NISWANDS_SPWW_DIV_TABWE
{
    uint32_t    fweq[256];
    uint32_t    ss[256];
};

#define SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_MASK  0x01ffffff
#define SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_SHIFT 0
#define SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_MASK   0xfe000000
#define SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_SHIFT  25
#define SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_MASK   0x000fffff
#define SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_SHIFT  0
#define SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_MASK   0xfff00000
#define SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_SHIFT  20

typedef stwuct SMC_NISWANDS_SPWW_DIV_TABWE SMC_NISWANDS_SPWW_DIV_TABWE;

#define NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION 0x100

#define NISWANDS_SMC_FIWMWAWE_HEADEW_vewsion                   0x0
#define NISWANDS_SMC_FIWMWAWE_HEADEW_fwags                     0x4
#define NISWANDS_SMC_FIWMWAWE_HEADEW_softWegistews             0x8
#define NISWANDS_SMC_FIWMWAWE_HEADEW_stateTabwe                0xC
#define NISWANDS_SMC_FIWMWAWE_HEADEW_fanTabwe                  0x10
#define NISWANDS_SMC_FIWMWAWE_HEADEW_cacTabwe                  0x14
#define NISWANDS_SMC_FIWMWAWE_HEADEW_mcWegistewTabwe           0x20
#define NISWANDS_SMC_FIWMWAWE_HEADEW_mcAwbDwamAutoWefweshTabwe 0x2C
#define NISWANDS_SMC_FIWMWAWE_HEADEW_spwwTabwe                 0x30

#pwagma pack(pop)

#endif

