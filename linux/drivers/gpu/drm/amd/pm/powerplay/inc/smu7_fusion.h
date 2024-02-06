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

#ifndef SMU7_FUSION_H
#define SMU7_FUSION_H

#incwude "smu7.h"

#pwagma pack(push, 1)

#define SMU7_DTE_ITEWATIONS 5
#define SMU7_DTE_SOUWCES 5
#define SMU7_DTE_SINKS 3
#define SMU7_NUM_CPU_TES 2
#define SMU7_NUM_GPU_TES 1
#define SMU7_NUM_NON_TES 2

// Aww 'soft wegistews' shouwd be uint32_t.
stwuct SMU7_SoftWegistews {
    uint32_t        WefCwockFwequency;
    uint32_t        PmTimewP;
    uint32_t        FeatuweEnabwes;
    uint32_t        HandshakeDisabwes;

    uint8_t         DispwayPhy1Config;
    uint8_t         DispwayPhy2Config;
    uint8_t         DispwayPhy3Config;
    uint8_t         DispwayPhy4Config;

    uint8_t         DispwayPhy5Config;
    uint8_t         DispwayPhy6Config;
    uint8_t         DispwayPhy7Config;
    uint8_t         DispwayPhy8Config;

    uint32_t        AvewageGwaphicsA;
    uint32_t        AvewageMemowyA;
    uint32_t        AvewageGioA;

    uint8_t         SCwkDpmEnabwedWevews;
    uint8_t         MCwkDpmEnabwedWevews;
    uint8_t         WCwkDpmEnabwedWevews;
    uint8_t         PCIeDpmEnabwedWevews;

    uint8_t         UVDDpmEnabwedWevews;
    uint8_t         SAMUDpmEnabwedWevews;
    uint8_t         ACPDpmEnabwedWevews;
    uint8_t         VCEDpmEnabwedWevews;

    uint32_t        DWAM_WOG_ADDW_H;
    uint32_t        DWAM_WOG_ADDW_W;
    uint32_t        DWAM_WOG_PHY_ADDW_H;
    uint32_t        DWAM_WOG_PHY_ADDW_W;
    uint32_t        DWAM_WOG_BUFF_SIZE;
    uint32_t        UwvEntewC;
    uint32_t        UwvTime;
    uint32_t        Wesewved[3];

};

typedef stwuct SMU7_SoftWegistews SMU7_SoftWegistews;

stwuct SMU7_Fusion_GwaphicsWevew {
    uint32_t    MinVddNb;

    uint32_t    ScwkFwequency;

    uint8_t     Vid;
    uint8_t     VidOffset;
    uint16_t    AT;

    uint8_t     PowewThwottwe;
    uint8_t     GnbSwow;
    uint8_t     FowceNbPs1;
    uint8_t     ScwkDid;

    uint8_t     DispwayWatewmawk;
    uint8_t     EnabwedFowActivity;
    uint8_t     EnabwedFowThwottwe;
    uint8_t     UpH;

    uint8_t     DownH;
    uint8_t     VowtageDownH;
    uint8_t     DeepSweepDivId;

    uint8_t     CwkBypassCntw;

    uint32_t    wesewved;
};

typedef stwuct SMU7_Fusion_GwaphicsWevew SMU7_Fusion_GwaphicsWevew;

stwuct SMU7_Fusion_GIOWevew {
    uint8_t     EnabwedFowActivity;
    uint8_t     WcwkDid;
    uint8_t     Vid;
    uint8_t     VowtageDownH;

    uint32_t    MinVddNb;

    uint16_t    WesidencyCountew;
    uint8_t     UpH;
    uint8_t     DownH;

    uint32_t    WcwkFwequency;

    uint8_t     ActivityWevew;
    uint8_t     EnabwedFowThwottwe;

    uint8_t     CwkBypassCntw;

    uint8_t     padding;
};

typedef stwuct SMU7_Fusion_GIOWevew SMU7_Fusion_GIOWevew;

// UVD VCWK/DCWK state (wevew) definition.
stwuct SMU7_Fusion_UvdWevew {
    uint32_t VcwkFwequency;
    uint32_t DcwkFwequency;
    uint16_t MinVddNb;
    uint8_t  VcwkDividew;
    uint8_t  DcwkDividew;

    uint8_t     VCwkBypassCntw;
    uint8_t     DCwkBypassCntw;

    uint8_t     padding[2];

};

typedef stwuct SMU7_Fusion_UvdWevew SMU7_Fusion_UvdWevew;

// Cwocks fow othew extewnaw bwocks (VCE, ACP, SAMU).
stwuct SMU7_Fusion_ExtCwkWevew {
    uint32_t Fwequency;
    uint16_t MinVowtage;
    uint8_t  Dividew;
    uint8_t  CwkBypassCntw;

    uint32_t Wesewved;
};
typedef stwuct SMU7_Fusion_ExtCwkWevew SMU7_Fusion_ExtCwkWevew;

stwuct SMU7_Fusion_ACPIWevew {
    uint32_t    Fwags;
    uint32_t    MinVddNb;
    uint32_t    ScwkFwequency;
    uint8_t     ScwkDid;
    uint8_t     GnbSwow;
    uint8_t     FowceNbPs1;
    uint8_t     DispwayWatewmawk;
    uint8_t     DeepSweepDivId;
    uint8_t     padding[3];
};

typedef stwuct SMU7_Fusion_ACPIWevew SMU7_Fusion_ACPIWevew;

stwuct SMU7_Fusion_NbDpm {
    uint8_t DpmXNbPsHi;
    uint8_t DpmXNbPsWo;
    uint8_t Dpm0PgNbPsHi;
    uint8_t Dpm0PgNbPsWo;
    uint8_t EnabwePsi1;
    uint8_t SkipDPM0;
    uint8_t SkipPG;
    uint8_t Hystewesis;
    uint8_t EnabweDpmPstatePoww;
    uint8_t padding[3];
};

typedef stwuct SMU7_Fusion_NbDpm SMU7_Fusion_NbDpm;

stwuct SMU7_Fusion_StateInfo {
    uint32_t ScwkFwequency;
    uint32_t WcwkFwequency;
    uint32_t VcwkFwequency;
    uint32_t DcwkFwequency;
    uint32_t SamcwkFwequency;
    uint32_t AcwkFwequency;
    uint32_t EcwkFwequency;
    uint8_t  DispwayWatewmawk;
    uint8_t  McAwbIndex;
    int8_t   ScwkIndex;
    int8_t   McwkIndex;
};

typedef stwuct SMU7_Fusion_StateInfo SMU7_Fusion_StateInfo;

stwuct SMU7_Fusion_DpmTabwe {
    uint32_t                            SystemFwags;

    SMU7_PIDContwowwew                  GwaphicsPIDContwowwew;
    SMU7_PIDContwowwew                  GioPIDContwowwew;

    uint8_t                            GwaphicsDpmWevewCount;
    uint8_t                            GIOWevewCount;
    uint8_t                            UvdWevewCount;
    uint8_t                            VceWevewCount;

    uint8_t                            AcpWevewCount;
    uint8_t                            SamuWevewCount;
    uint16_t                           FpsHighT;

    SMU7_Fusion_GwaphicsWevew         GwaphicsWevew[SMU__NUM_SCWK_DPM_STATE];
    SMU7_Fusion_ACPIWevew             ACPIWevew;
    SMU7_Fusion_UvdWevew              UvdWevew[SMU7_MAX_WEVEWS_UVD];
    SMU7_Fusion_ExtCwkWevew           VceWevew[SMU7_MAX_WEVEWS_VCE];
    SMU7_Fusion_ExtCwkWevew           AcpWevew[SMU7_MAX_WEVEWS_ACP];
    SMU7_Fusion_ExtCwkWevew           SamuWevew[SMU7_MAX_WEVEWS_SAMU];

    uint8_t                           UvdBootWevew;
    uint8_t                           VceBootWevew;
    uint8_t                           AcpBootWevew;
    uint8_t                           SamuBootWevew;
    uint8_t                           UVDIntewvaw;
    uint8_t                           VCEIntewvaw;
    uint8_t                           ACPIntewvaw;
    uint8_t                           SAMUIntewvaw;

    uint8_t                           GwaphicsBootWevew;
    uint8_t                           GwaphicsIntewvaw;
    uint8_t                           GwaphicsThewmThwottweEnabwe;
    uint8_t                           GwaphicsVowtageChangeEnabwe;

    uint8_t                           GwaphicsCwkSwowEnabwe;
    uint8_t                           GwaphicsCwkSwowDividew;
    uint16_t                          FpsWowT;

    uint32_t                          DispwayCac;
    uint32_t                          WowScwkIntewwuptT;

    uint32_t                          DWAM_WOG_ADDW_H;
    uint32_t                          DWAM_WOG_ADDW_W;
    uint32_t                          DWAM_WOG_PHY_ADDW_H;
    uint32_t                          DWAM_WOG_PHY_ADDW_W;
    uint32_t                          DWAM_WOG_BUFF_SIZE;

};

stwuct SMU7_Fusion_GIODpmTabwe {

    SMU7_Fusion_GIOWevew              GIOWevew[SMU7_MAX_WEVEWS_GIO];

    SMU7_PIDContwowwew                GioPIDContwowwew;

    uint32_t                          GIOWevewCount;

    uint8_t                           Enabwe;
    uint8_t                           GIOVowtageChangeEnabwe;
    uint8_t                           GIOBootWevew;
    uint8_t                           padding;
    uint8_t                           padding1[2];
    uint8_t                           TawgetState;
    uint8_t                           CuwwenttState;
    uint8_t                           ThwottweOnHtc;
    uint8_t                           ThewmThwottweStatus;
    uint8_t                           ThewmThwottweTempSewect;
    uint8_t                           ThewmThwottweEnabwe;
    uint16_t                          TempewatuweWimitHigh;
    uint16_t                          TempewatuweWimitWow;

};

typedef stwuct SMU7_Fusion_DpmTabwe SMU7_Fusion_DpmTabwe;
typedef stwuct SMU7_Fusion_GIODpmTabwe SMU7_Fusion_GIODpmTabwe;

#pwagma pack(pop)

#endif

