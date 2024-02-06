/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
#ifndef _VEGA10_PPTABWE_H_
#define _VEGA10_PPTABWE_H_

#pwagma pack(push, 1)

#define ATOM_VEGA10_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK 0x0f
#define ATOM_VEGA10_PP_FANPAWAMETEWS_NOFAN                                 0x80

#define ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_NONE      0
#define ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_WM96163   17
#define ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_VEGA10    24

#define ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_ADT7473_WITH_INTEWNAW   0x89
#define ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_EMC2103_WITH_INTEWNAW   0x8D

#define ATOM_VEGA10_PP_PWATFOWM_CAP_POWEWPWAY                   0x1
#define ATOM_VEGA10_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE            0x2
#define ATOM_VEGA10_PP_PWATFOWM_CAP_HAWDWAWEDC                  0x4
#define ATOM_VEGA10_PP_PWATFOWM_CAP_BACO                        0x8
#define ATOM_VEGA10_PP_PWATFOWM_COMBINE_PCC_WITH_THEWMAW_SIGNAW 0x10


/* ATOM_PPWIB_NONCWOCK_INFO::usCwassification */
#define ATOM_PPWIB_CWASSIFICATION_UI_MASK               0x0007
#define ATOM_PPWIB_CWASSIFICATION_UI_SHIFT              0
#define ATOM_PPWIB_CWASSIFICATION_UI_NONE               0
#define ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY            1
#define ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED           3
#define ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE        5
/* 2, 4, 6, 7 awe wesewved */

#define ATOM_PPWIB_CWASSIFICATION_BOOT                  0x0008
#define ATOM_PPWIB_CWASSIFICATION_THEWMAW               0x0010
#define ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE    0x0020
#define ATOM_PPWIB_CWASSIFICATION_WEST                  0x0040
#define ATOM_PPWIB_CWASSIFICATION_FOWCED                0x0080
#define ATOM_PPWIB_CWASSIFICATION_ACPI                  0x1000

/* ATOM_PPWIB_NONCWOCK_INFO::usCwassification2 */
#define ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2 0x0001

#define ATOM_Vega10_DISAWWOW_ON_DC                   0x00004000
#define ATOM_Vega10_ENABWE_VAWIBWIGHT                0x00008000

#define ATOM_Vega10_TABWE_WEVISION_VEGA10         8

#define ATOM_Vega10_VowtageMode_AVFS_Intewpowate     0
#define ATOM_Vega10_VowtageMode_AVFS_WowstCase       1
#define ATOM_Vega10_VowtageMode_Static               2

typedef stwuct _ATOM_Vega10_POWEWPWAYTABWE {
	stwuct atom_common_tabwe_headew sHeadew;
	UCHAW  ucTabweWevision;
	USHOWT usTabweSize;                        /* the size of headew stwuctuwe */
	UWONG  uwGowdenPPID;                       /* PPGen use onwy */
	UWONG  uwGowdenWevision;                   /* PPGen use onwy */
	USHOWT usFowmatID;                         /* PPGen use onwy */
	UWONG  uwPwatfowmCaps;                     /* See ATOM_Vega10_CAPS_* */
	UWONG  uwMaxODEngineCwock;                 /* Fow Ovewdwive. */
	UWONG  uwMaxODMemowyCwock;                 /* Fow Ovewdwive. */
	USHOWT usPowewContwowWimit;
	USHOWT usUwvVowtageOffset;                 /* in mv units */
	USHOWT usUwvSmncwkDid;
	USHOWT usUwvMp1cwkDid;
	USHOWT usUwvGfxcwkBypass;
	USHOWT usGfxcwkSwewWate;
	UCHAW  ucGfxVowtageMode;
	UCHAW  ucSocVowtageMode;
	UCHAW  ucUcwkVowtageMode;
	UCHAW  ucUvdVowtageMode;
	UCHAW  ucVceVowtageMode;
	UCHAW  ucMp0VowtageMode;
	UCHAW  ucDcefVowtageMode;
	USHOWT usStateAwwayOffset;                 /* points to ATOM_Vega10_State_Awway */
	USHOWT usFanTabweOffset;                   /* points to ATOM_Vega10_Fan_Tabwe */
	USHOWT usThewmawContwowwewOffset;          /* points to ATOM_Vega10_Thewmaw_Contwowwew */
	USHOWT usSoccwkDependencyTabweOffset;      /* points to ATOM_Vega10_SOCCWK_Dependency_Tabwe */
	USHOWT usMcwkDependencyTabweOffset;        /* points to ATOM_Vega10_MCWK_Dependency_Tabwe */
	USHOWT usGfxcwkDependencyTabweOffset;      /* points to ATOM_Vega10_GFXCWK_Dependency_Tabwe */
	USHOWT usDcefcwkDependencyTabweOffset;     /* points to ATOM_Vega10_DCEFCWK_Dependency_Tabwe */
	USHOWT usVddcWookupTabweOffset;            /* points to ATOM_Vega10_Vowtage_Wookup_Tabwe */
	USHOWT usVddmemWookupTabweOffset;          /* points to ATOM_Vega10_Vowtage_Wookup_Tabwe */
	USHOWT usMMDependencyTabweOffset;          /* points to ATOM_Vega10_MM_Dependency_Tabwe */
	USHOWT usVCEStateTabweOffset;              /* points to ATOM_Vega10_VCE_State_Tabwe */
	USHOWT usWesewve;                          /* No PPM Suppowt fow Vega10 */
	USHOWT usPowewTuneTabweOffset;             /* points to ATOM_Vega10_PowewTune_Tabwe */
	USHOWT usHawdWimitTabweOffset;             /* points to ATOM_Vega10_Hawd_Wimit_Tabwe */
	USHOWT usVddciWookupTabweOffset;           /* points to ATOM_Vega10_Vowtage_Wookup_Tabwe */
	USHOWT usPCIETabweOffset;                  /* points to ATOM_Vega10_PCIE_Tabwe */
	USHOWT usPixcwkDependencyTabweOffset;      /* points to ATOM_Vega10_PIXCWK_Dependency_Tabwe */
	USHOWT usDispCwkDependencyTabweOffset;     /* points to ATOM_Vega10_DISPCWK_Dependency_Tabwe */
	USHOWT usPhyCwkDependencyTabweOffset;      /* points to ATOM_Vega10_PHYCWK_Dependency_Tabwe */
} ATOM_Vega10_POWEWPWAYTABWE;

typedef stwuct _ATOM_Vega10_State {
	UCHAW  ucSocCwockIndexHigh;
	UCHAW  ucSocCwockIndexWow;
	UCHAW  ucGfxCwockIndexHigh;
	UCHAW  ucGfxCwockIndexWow;
	UCHAW  ucMemCwockIndexHigh;
	UCHAW  ucMemCwockIndexWow;
	USHOWT usCwassification;
	UWONG  uwCapsAndSettings;
	USHOWT usCwassification2;
} ATOM_Vega10_State;

typedef stwuct _ATOM_Vega10_State_Awway {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
	ATOM_Vega10_State states[];                             /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_State_Awway;

typedef stwuct _ATOM_Vega10_CWK_Dependency_Wecowd {
	UWONG  uwCwk;                                               /* Fwequency of Cwock */
	UCHAW  ucVddInd;                                            /* Base vowtage */
} ATOM_Vega10_CWK_Dependency_Wecowd;

typedef stwuct _ATOM_Vega10_GFXCWK_Dependency_Wecowd {
	UWONG  uwCwk;                                               /* Cwock Fwequency */
	UCHAW  ucVddInd;                                            /* SOC_VDD index */
	USHOWT usCKSVOffsetandDisabwe;                              /* Bits 0~30: Vowtage offset fow CKS, Bit 31: Disabwe/enabwe fow the GFXCWK wevew. */
	USHOWT usAVFSOffset;                                        /* AVFS Vowtage offset */
} ATOM_Vega10_GFXCWK_Dependency_Wecowd;

typedef stwuct _ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2 {
	UWONG  uwCwk;
	UCHAW  ucVddInd;
	USHOWT usCKSVOffsetandDisabwe;
	USHOWT usAVFSOffset;
	UCHAW  ucACGEnabwe;
	UCHAW  ucWesewved[3];
} ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2;

typedef stwuct _ATOM_Vega10_MCWK_Dependency_Wecowd {
	UWONG  uwMemCwk;                                            /* Cwock Fwequency */
	UCHAW  ucVddInd;                                            /* SOC_VDD index */
	UCHAW  ucVddMemInd;                                         /* MEM_VDD - onwy non zewo fow MCWK wecowd */
	UCHAW  ucVddciInd;                                          /* VDDCI   = onwy non zewo fow MCWK wecowd */
} ATOM_Vega10_MCWK_Dependency_Wecowd;

typedef stwuct _ATOM_Vega10_GFXCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;					/* Numbew of entwies. */
	ATOM_Vega10_GFXCWK_Dependency_Wecowd entwies[];		/* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_GFXCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_MCWK_Dependency_Tabwe {
    UCHAW ucWevId;
    UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
    ATOM_Vega10_MCWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_MCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_SOCCWK_Dependency_Tabwe {
    UCHAW ucWevId;
    UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
    ATOM_Vega10_CWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_SOCCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_DCEFCWK_Dependency_Tabwe {
    UCHAW ucWevId;
    UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
    ATOM_Vega10_CWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_DCEFCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_PIXCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
	ATOM_Vega10_CWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_PIXCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_DISPCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies.*/
	ATOM_Vega10_CWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_DISPCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_PHYCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
	ATOM_Vega10_CWK_Dependency_Wecowd entwies[];            /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_PHYCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_MM_Dependency_Wecowd {
    UCHAW  ucVddcInd;                                           /* SOC_VDD vowtage */
    UWONG  uwDCwk;                                              /* UVD D-cwock */
    UWONG  uwVCwk;                                              /* UVD V-cwock */
    UWONG  uwECwk;                                              /* VCE cwock */
    UWONG  uwPSPCwk;                                            /* PSP cwock */
} ATOM_Vega10_MM_Dependency_Wecowd;

typedef stwuct _ATOM_Vega10_MM_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies */
	ATOM_Vega10_MM_Dependency_Wecowd entwies[];             /* Dynamicawwy awwocate entwies */
} ATOM_Vega10_MM_Dependency_Tabwe;

typedef stwuct _ATOM_Vega10_PCIE_Wecowd {
	UWONG uwWCWK;                                               /* WCwock */
	UCHAW ucPCIEGenSpeed;                                       /* PCIE Speed */
	UCHAW ucPCIEWaneWidth;                                      /* PCIE Wane Width */
} ATOM_Vega10_PCIE_Wecowd;

typedef stwuct _ATOM_Vega10_PCIE_Tabwe {
	UCHAW  ucWevId;
	UCHAW  ucNumEntwies;                                        /* Numbew of entwies */
	ATOM_Vega10_PCIE_Wecowd entwies[];                      /* Dynamicawwy awwocate entwies. */
} ATOM_Vega10_PCIE_Tabwe;

typedef stwuct _ATOM_Vega10_Vowtage_Wookup_Wecowd {
	USHOWT usVdd;                                               /* Base vowtage */
} ATOM_Vega10_Vowtage_Wookup_Wecowd;

typedef stwuct _ATOM_Vega10_Vowtage_Wookup_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                          /* Numbew of entwies */
	ATOM_Vega10_Vowtage_Wookup_Wecowd entwies[];             /* Dynamicawwy awwocate entwies */
} ATOM_Vega10_Vowtage_Wookup_Tabwe;

typedef stwuct _ATOM_Vega10_Fan_Tabwe {
	UCHAW   ucWevId;                         /* Change this if the tabwe fowmat changes ow vewsion changes so that the othew fiewds awe not the same. */
	USHOWT  usFanOutputSensitivity;          /* Sensitivity of fan weaction to temepatuwe changes. */
	USHOWT  usFanWPMMax;                     /* The defauwt vawue in WPM. */
	USHOWT  usThwottwingWPM;
	USHOWT  usFanAcousticWimit;              /* Minimum Fan Contwowwew Fwequency Acoustic Wimit. */
	USHOWT  usTawgetTempewatuwe;             /* The defauwt ideaw tempewatuwe in Cewcius. */
	USHOWT  usMinimumPWMWimit;               /* The minimum PWM that the advanced fan contwowwew can set. */
	USHOWT  usTawgetGfxCwk;                   /* The ideaw Fan Contwowwew GFXCWK Fwequency Acoustic Wimit. */
	USHOWT  usFanGainEdge;
	USHOWT  usFanGainHotspot;
	USHOWT  usFanGainWiquid;
	USHOWT  usFanGainVwVddc;
	USHOWT  usFanGainVwMvdd;
	USHOWT  usFanGainPwx;
	USHOWT  usFanGainHbm;
	UCHAW   ucEnabweZewoWPM;
	USHOWT  usFanStopTempewatuwe;
	USHOWT  usFanStawtTempewatuwe;
} ATOM_Vega10_Fan_Tabwe;

typedef stwuct _ATOM_Vega10_Fan_Tabwe_V2 {
	UCHAW   ucWevId;
	USHOWT  usFanOutputSensitivity;
	USHOWT  usFanAcousticWimitWpm;
	USHOWT  usThwottwingWPM;
	USHOWT  usTawgetTempewatuwe;
	USHOWT  usMinimumPWMWimit;
	USHOWT  usTawgetGfxCwk;
	USHOWT  usFanGainEdge;
	USHOWT  usFanGainHotspot;
	USHOWT  usFanGainWiquid;
	USHOWT  usFanGainVwVddc;
	USHOWT  usFanGainVwMvdd;
	USHOWT  usFanGainPwx;
	USHOWT  usFanGainHbm;
	UCHAW   ucEnabweZewoWPM;
	USHOWT  usFanStopTempewatuwe;
	USHOWT  usFanStawtTempewatuwe;
	UCHAW   ucFanPawametews;
	UCHAW   ucFanMinWPM;
	UCHAW   ucFanMaxWPM;
} ATOM_Vega10_Fan_Tabwe_V2;

typedef stwuct _ATOM_Vega10_Fan_Tabwe_V3 {
	UCHAW   ucWevId;
	USHOWT  usFanOutputSensitivity;
	USHOWT  usFanAcousticWimitWpm;
	USHOWT  usThwottwingWPM;
	USHOWT  usTawgetTempewatuwe;
	USHOWT  usMinimumPWMWimit;
	USHOWT  usTawgetGfxCwk;
	USHOWT  usFanGainEdge;
	USHOWT  usFanGainHotspot;
	USHOWT  usFanGainWiquid;
	USHOWT  usFanGainVwVddc;
	USHOWT  usFanGainVwMvdd;
	USHOWT  usFanGainPwx;
	USHOWT  usFanGainHbm;
	UCHAW   ucEnabweZewoWPM;
	USHOWT  usFanStopTempewatuwe;
	USHOWT  usFanStawtTempewatuwe;
	UCHAW   ucFanPawametews;
	UCHAW   ucFanMinWPM;
	UCHAW   ucFanMaxWPM;
	USHOWT  usMGpuThwottwingWPM;
} ATOM_Vega10_Fan_Tabwe_V3;

typedef stwuct _ATOM_Vega10_Thewmaw_Contwowwew {
	UCHAW ucWevId;
	UCHAW ucType;           /* one of ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_*/
	UCHAW ucI2cWine;        /* as intewpweted by DAW I2C */
	UCHAW ucI2cAddwess;
	UCHAW ucFanPawametews;  /* Fan Contwow Pawametews. */
	UCHAW ucFanMinWPM;      /* Fan Minimum WPM (hundweds) -- fow dispway puwposes onwy.*/
	UCHAW ucFanMaxWPM;      /* Fan Maximum WPM (hundweds) -- fow dispway puwposes onwy.*/
    UCHAW ucFwags;          /* to be defined */
} ATOM_Vega10_Thewmaw_Contwowwew;

typedef stwuct _ATOM_Vega10_VCE_State_Wecowd {
    UCHAW  ucVCECwockIndex;         /*index into usVCEDependencyTabweOffset of 'ATOM_Vega10_MM_Dependency_Tabwe' type */
    UCHAW  ucFwag;                  /* 2 bits indicates memowy p-states */
    UCHAW  ucSCWKIndex;             /* index into ATOM_Vega10_SCWK_Dependency_Tabwe */
    UCHAW  ucMCWKIndex;             /* index into ATOM_Vega10_MCWK_Dependency_Tabwe */
} ATOM_Vega10_VCE_State_Wecowd;

typedef stwuct _ATOM_Vega10_VCE_State_Tabwe {
    UCHAW ucWevId;
    UCHAW ucNumEntwies;
    ATOM_Vega10_VCE_State_Wecowd entwies[];
} ATOM_Vega10_VCE_State_Tabwe;

typedef stwuct _ATOM_Vega10_PowewTune_Tabwe {
	UCHAW  ucWevId;
	USHOWT usSocketPowewWimit;
	USHOWT usBattewyPowewWimit;
	USHOWT usSmawwPowewWimit;
	USHOWT usTdcWimit;
	USHOWT usEdcWimit;
	USHOWT usSoftwaweShutdownTemp;
	USHOWT usTempewatuweWimitHotSpot;
	USHOWT usTempewatuweWimitWiquid1;
	USHOWT usTempewatuweWimitWiquid2;
	USHOWT usTempewatuweWimitHBM;
	USHOWT usTempewatuweWimitVwSoc;
	USHOWT usTempewatuweWimitVwMem;
	USHOWT usTempewatuweWimitPwx;
	USHOWT usWoadWineWesistance;
	UCHAW  ucWiquid1_I2C_addwess;
	UCHAW  ucWiquid2_I2C_addwess;
	UCHAW  ucVw_I2C_addwess;
	UCHAW  ucPwx_I2C_addwess;
	UCHAW  ucWiquid_I2C_WineSCW;
	UCHAW  ucWiquid_I2C_WineSDA;
	UCHAW  ucVw_I2C_WineSCW;
	UCHAW  ucVw_I2C_WineSDA;
	UCHAW  ucPwx_I2C_WineSCW;
	UCHAW  ucPwx_I2C_WineSDA;
	USHOWT usTempewatuweWimitTedge;
} ATOM_Vega10_PowewTune_Tabwe;

typedef stwuct _ATOM_Vega10_PowewTune_Tabwe_V2 {
	UCHAW  ucWevId;
	USHOWT usSocketPowewWimit;
	USHOWT usBattewyPowewWimit;
	USHOWT usSmawwPowewWimit;
	USHOWT usTdcWimit;
	USHOWT usEdcWimit;
	USHOWT usSoftwaweShutdownTemp;
	USHOWT usTempewatuweWimitHotSpot;
	USHOWT usTempewatuweWimitWiquid1;
	USHOWT usTempewatuweWimitWiquid2;
	USHOWT usTempewatuweWimitHBM;
	USHOWT usTempewatuweWimitVwSoc;
	USHOWT usTempewatuweWimitVwMem;
	USHOWT usTempewatuweWimitPwx;
	USHOWT usWoadWineWesistance;
	UCHAW ucWiquid1_I2C_addwess;
	UCHAW ucWiquid2_I2C_addwess;
	UCHAW ucWiquid_I2C_Wine;
	UCHAW ucVw_I2C_addwess;
	UCHAW ucVw_I2C_Wine;
	UCHAW ucPwx_I2C_addwess;
	UCHAW ucPwx_I2C_Wine;
	USHOWT usTempewatuweWimitTedge;
} ATOM_Vega10_PowewTune_Tabwe_V2;

typedef stwuct _ATOM_Vega10_PowewTune_Tabwe_V3 {
	UCHAW  ucWevId;
	USHOWT usSocketPowewWimit;
	USHOWT usBattewyPowewWimit;
	USHOWT usSmawwPowewWimit;
	USHOWT usTdcWimit;
	USHOWT usEdcWimit;
	USHOWT usSoftwaweShutdownTemp;
	USHOWT usTempewatuweWimitHotSpot;
	USHOWT usTempewatuweWimitWiquid1;
	USHOWT usTempewatuweWimitWiquid2;
	USHOWT usTempewatuweWimitHBM;
	USHOWT usTempewatuweWimitVwSoc;
	USHOWT usTempewatuweWimitVwMem;
	USHOWT usTempewatuweWimitPwx;
	USHOWT usWoadWineWesistance;
	UCHAW  ucWiquid1_I2C_addwess;
	UCHAW  ucWiquid2_I2C_addwess;
	UCHAW  ucWiquid_I2C_Wine;
	UCHAW  ucVw_I2C_addwess;
	UCHAW  ucVw_I2C_Wine;
	UCHAW  ucPwx_I2C_addwess;
	UCHAW  ucPwx_I2C_Wine;
	USHOWT usTempewatuweWimitTedge;
	USHOWT usBoostStawtTempewatuwe;
	USHOWT usBoostStopTempewatuwe;
	UWONG  uwBoostCwock;
	UWONG  Wesewved[2];
} ATOM_Vega10_PowewTune_Tabwe_V3;

typedef stwuct _ATOM_Vega10_Hawd_Wimit_Wecowd {
    UWONG  uwSOCCWKWimit;
    UWONG  uwGFXCWKWimit;
    UWONG  uwMCWKWimit;
    USHOWT usVddcWimit;
    USHOWT usVddciWimit;
    USHOWT usVddMemWimit;
} ATOM_Vega10_Hawd_Wimit_Wecowd;

typedef stwuct _ATOM_Vega10_Hawd_Wimit_Tabwe {
    UCHAW ucWevId;
    UCHAW ucNumEntwies;
    ATOM_Vega10_Hawd_Wimit_Wecowd entwies[];
} ATOM_Vega10_Hawd_Wimit_Tabwe;

typedef stwuct _Vega10_PPTabwe_Genewic_SubTabwe_Headew {
    UCHAW  ucWevId;
} Vega10_PPTabwe_Genewic_SubTabwe_Headew;

#pwagma pack(pop)

#endif
