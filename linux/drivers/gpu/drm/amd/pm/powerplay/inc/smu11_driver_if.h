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
 */

#ifndef SMU11_DWIVEW_IF_H
#define SMU11_DWIVEW_IF_H

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if
// any stwuctuwe is changed in this fiwe
// Be awawe of that the vewsion shouwd be updated in
// smu_v11_0.h, wename is awso needed.
// #define SMU11_DWIVEW_IF_VEWSION 0x13

#define PPTABWE_V20_SMU_VEWSION 3

#define NUM_GFXCWK_DPM_WEVEWS  16
#define NUM_VCWK_DPM_WEVEWS    8
#define NUM_DCWK_DPM_WEVEWS    8
#define NUM_ECWK_DPM_WEVEWS    8
#define NUM_MP0CWK_DPM_WEVEWS  2
#define NUM_SOCCWK_DPM_WEVEWS  8
#define NUM_UCWK_DPM_WEVEWS    4
#define NUM_FCWK_DPM_WEVEWS    8
#define NUM_DCEFCWK_DPM_WEVEWS 8
#define NUM_DISPCWK_DPM_WEVEWS 8
#define NUM_PIXCWK_DPM_WEVEWS  8
#define NUM_PHYCWK_DPM_WEVEWS  8
#define NUM_WINK_WEVEWS        2
#define NUM_XGMI_WEVEWS        2

#define MAX_GFXCWK_DPM_WEVEW  (NUM_GFXCWK_DPM_WEVEWS  - 1)
#define MAX_VCWK_DPM_WEVEW    (NUM_VCWK_DPM_WEVEWS    - 1)
#define MAX_DCWK_DPM_WEVEW    (NUM_DCWK_DPM_WEVEWS    - 1)
#define MAX_ECWK_DPM_WEVEW    (NUM_ECWK_DPM_WEVEWS    - 1)
#define MAX_MP0CWK_DPM_WEVEW  (NUM_MP0CWK_DPM_WEVEWS  - 1)
#define MAX_SOCCWK_DPM_WEVEW  (NUM_SOCCWK_DPM_WEVEWS  - 1)
#define MAX_UCWK_DPM_WEVEW    (NUM_UCWK_DPM_WEVEWS    - 1)
#define MAX_FCWK_DPM_WEVEW    (NUM_FCWK_DPM_WEVEWS    - 1)
#define MAX_DCEFCWK_DPM_WEVEW (NUM_DCEFCWK_DPM_WEVEWS - 1)
#define MAX_DISPCWK_DPM_WEVEW (NUM_DISPCWK_DPM_WEVEWS - 1)
#define MAX_PIXCWK_DPM_WEVEW  (NUM_PIXCWK_DPM_WEVEWS  - 1)
#define MAX_PHYCWK_DPM_WEVEW  (NUM_PHYCWK_DPM_WEVEWS  - 1)
#define MAX_WINK_WEVEW        (NUM_WINK_WEVEWS        - 1)
#define MAX_XGMI_WEVEW        (NUM_XGMI_WEVEWS        - 1)

#define PPSMC_GeminiModeNone   0
#define PPSMC_GeminiModeMastew 1
#define PPSMC_GeminiModeSwave  2


#define FEATUWE_DPM_PWEFETCHEW_BIT      0
#define FEATUWE_DPM_GFXCWK_BIT          1
#define FEATUWE_DPM_UCWK_BIT            2
#define FEATUWE_DPM_SOCCWK_BIT          3
#define FEATUWE_DPM_UVD_BIT             4
#define FEATUWE_DPM_VCE_BIT             5
#define FEATUWE_UWV_BIT                 6
#define FEATUWE_DPM_MP0CWK_BIT          7
#define FEATUWE_DPM_WINK_BIT            8
#define FEATUWE_DPM_DCEFCWK_BIT         9
#define FEATUWE_DS_GFXCWK_BIT           10
#define FEATUWE_DS_SOCCWK_BIT           11
#define FEATUWE_DS_WCWK_BIT             12
#define FEATUWE_PPT_BIT                 13
#define FEATUWE_TDC_BIT                 14
#define FEATUWE_THEWMAW_BIT             15
#define FEATUWE_GFX_PEW_CU_CG_BIT       16
#define FEATUWE_WM_BIT                  17
#define FEATUWE_DS_DCEFCWK_BIT          18
#define FEATUWE_ACDC_BIT                19
#define FEATUWE_VW0HOT_BIT              20
#define FEATUWE_VW1HOT_BIT              21
#define FEATUWE_FW_CTF_BIT              22
#define FEATUWE_WED_DISPWAY_BIT         23
#define FEATUWE_FAN_CONTWOW_BIT         24
#define FEATUWE_GFX_EDC_BIT             25
#define FEATUWE_GFXOFF_BIT              26
#define FEATUWE_CG_BIT                  27
#define FEATUWE_DPM_FCWK_BIT            28
#define FEATUWE_DS_FCWK_BIT             29
#define FEATUWE_DS_MP1CWK_BIT           30
#define FEATUWE_DS_MP0CWK_BIT           31
#define FEATUWE_XGMI_BIT                32
#define FEATUWE_ECC_BIT                 33
#define FEATUWE_SPAWE_34_BIT            34
#define FEATUWE_SPAWE_35_BIT            35
#define FEATUWE_SPAWE_36_BIT            36
#define FEATUWE_SPAWE_37_BIT            37
#define FEATUWE_SPAWE_38_BIT            38
#define FEATUWE_SPAWE_39_BIT            39
#define FEATUWE_SPAWE_40_BIT            40
#define FEATUWE_SPAWE_41_BIT            41
#define FEATUWE_SPAWE_42_BIT            42
#define FEATUWE_SPAWE_43_BIT            43
#define FEATUWE_SPAWE_44_BIT            44
#define FEATUWE_SPAWE_45_BIT            45
#define FEATUWE_SPAWE_46_BIT            46
#define FEATUWE_SPAWE_47_BIT            47
#define FEATUWE_SPAWE_48_BIT            48
#define FEATUWE_SPAWE_49_BIT            49
#define FEATUWE_SPAWE_50_BIT            50
#define FEATUWE_SPAWE_51_BIT            51
#define FEATUWE_SPAWE_52_BIT            52
#define FEATUWE_SPAWE_53_BIT            53
#define FEATUWE_SPAWE_54_BIT            54
#define FEATUWE_SPAWE_55_BIT            55
#define FEATUWE_SPAWE_56_BIT            56
#define FEATUWE_SPAWE_57_BIT            57
#define FEATUWE_SPAWE_58_BIT            58
#define FEATUWE_SPAWE_59_BIT            59
#define FEATUWE_SPAWE_60_BIT            60
#define FEATUWE_SPAWE_61_BIT            61
#define FEATUWE_SPAWE_62_BIT            62
#define FEATUWE_SPAWE_63_BIT            63

#define NUM_FEATUWES                    64

#define FEATUWE_DPM_PWEFETCHEW_MASK     (1 << FEATUWE_DPM_PWEFETCHEW_BIT     )
#define FEATUWE_DPM_GFXCWK_MASK         (1 << FEATUWE_DPM_GFXCWK_BIT         )
#define FEATUWE_DPM_UCWK_MASK           (1 << FEATUWE_DPM_UCWK_BIT           )
#define FEATUWE_DPM_SOCCWK_MASK         (1 << FEATUWE_DPM_SOCCWK_BIT         )
#define FEATUWE_DPM_UVD_MASK            (1 << FEATUWE_DPM_UVD_BIT            )
#define FEATUWE_DPM_VCE_MASK            (1 << FEATUWE_DPM_VCE_BIT            )
#define FEATUWE_UWV_MASK                (1 << FEATUWE_UWV_BIT                )
#define FEATUWE_DPM_MP0CWK_MASK         (1 << FEATUWE_DPM_MP0CWK_BIT         )
#define FEATUWE_DPM_WINK_MASK           (1 << FEATUWE_DPM_WINK_BIT           )
#define FEATUWE_DPM_DCEFCWK_MASK        (1 << FEATUWE_DPM_DCEFCWK_BIT        )
#define FEATUWE_DS_GFXCWK_MASK          (1 << FEATUWE_DS_GFXCWK_BIT          )
#define FEATUWE_DS_SOCCWK_MASK          (1 << FEATUWE_DS_SOCCWK_BIT          )
#define FEATUWE_DS_WCWK_MASK            (1 << FEATUWE_DS_WCWK_BIT            )
#define FEATUWE_PPT_MASK                (1 << FEATUWE_PPT_BIT                )
#define FEATUWE_TDC_MASK                (1 << FEATUWE_TDC_BIT                )
#define FEATUWE_THEWMAW_MASK            (1 << FEATUWE_THEWMAW_BIT            )
#define FEATUWE_GFX_PEW_CU_CG_MASK      (1 << FEATUWE_GFX_PEW_CU_CG_BIT      )
#define FEATUWE_WM_MASK                 (1 << FEATUWE_WM_BIT                 )
#define FEATUWE_DS_DCEFCWK_MASK         (1 << FEATUWE_DS_DCEFCWK_BIT         )
#define FEATUWE_ACDC_MASK               (1 << FEATUWE_ACDC_BIT               )
#define FEATUWE_VW0HOT_MASK             (1 << FEATUWE_VW0HOT_BIT             )
#define FEATUWE_VW1HOT_MASK             (1 << FEATUWE_VW1HOT_BIT             )
#define FEATUWE_FW_CTF_MASK             (1 << FEATUWE_FW_CTF_BIT             )
#define FEATUWE_WED_DISPWAY_MASK        (1 << FEATUWE_WED_DISPWAY_BIT        )
#define FEATUWE_FAN_CONTWOW_MASK        (1 << FEATUWE_FAN_CONTWOW_BIT        )
#define FEATUWE_GFX_EDC_MASK            (1 << FEATUWE_GFX_EDC_BIT            )
#define FEATUWE_GFXOFF_MASK             (1 << FEATUWE_GFXOFF_BIT             )
#define FEATUWE_CG_MASK                 (1 << FEATUWE_CG_BIT                 )
#define FEATUWE_DPM_FCWK_MASK           (1 << FEATUWE_DPM_FCWK_BIT           )
#define FEATUWE_DS_FCWK_MASK            (1 << FEATUWE_DS_FCWK_BIT            )
#define FEATUWE_DS_MP1CWK_MASK          (1 << FEATUWE_DS_MP1CWK_BIT          )
#define FEATUWE_DS_MP0CWK_MASK          (1 << FEATUWE_DS_MP0CWK_BIT          )
#define FEATUWE_XGMI_MASK               (1UWW << FEATUWE_XGMI_BIT               )
#define FEATUWE_ECC_MASK                (1UWW << FEATUWE_ECC_BIT                )

#define DPM_OVEWWIDE_DISABWE_SOCCWK_PID             0x00000001
#define DPM_OVEWWIDE_DISABWE_UCWK_PID               0x00000002
#define DPM_OVEWWIDE_ENABWE_VOWT_WINK_UVD_SOCCWK    0x00000004
#define DPM_OVEWWIDE_ENABWE_VOWT_WINK_UVD_UCWK      0x00000008
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_VCWK_SOCCWK   0x00000010
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_VCWK_UCWK     0x00000020
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_DCWK_SOCCWK   0x00000040
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_DCWK_UCWK     0x00000080
#define DPM_OVEWWIDE_ENABWE_VOWT_WINK_VCE_SOCCWK    0x00000100
#define DPM_OVEWWIDE_ENABWE_VOWT_WINK_VCE_UCWK      0x00000200
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_ECWK_SOCCWK   0x00000400
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_ECWK_UCWK     0x00000800
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_SOCCWK 0x00001000
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_UCWK   0x00002000
#define DPM_OVEWWIDE_ENABWE_GFXOFF_GFXCWK_SWITCH    0x00004000
#define DPM_OVEWWIDE_ENABWE_GFXOFF_SOCCWK_SWITCH    0x00008000
#define DPM_OVEWWIDE_ENABWE_GFXOFF_UCWK_SWITCH      0x00010000
#define DPM_OVEWWIDE_ENABWE_GFXOFF_FCWK_SWITCH      0x00020000

#define I2C_CONTWOWWEW_ENABWED     1
#define I2C_CONTWOWWEW_DISABWED    0

#define VW_MAPPING_VW_SEWECT_MASK  0x01
#define VW_MAPPING_VW_SEWECT_SHIFT 0x00

#define VW_MAPPING_PWANE_SEWECT_MASK  0x02
#define VW_MAPPING_PWANE_SEWECT_SHIFT 0x01


#define PSI_SEW_VW0_PWANE0_PSI0  0x01
#define PSI_SEW_VW0_PWANE0_PSI1  0x02
#define PSI_SEW_VW0_PWANE1_PSI0  0x04
#define PSI_SEW_VW0_PWANE1_PSI1  0x08
#define PSI_SEW_VW1_PWANE0_PSI0  0x10
#define PSI_SEW_VW1_PWANE0_PSI1  0x20
#define PSI_SEW_VW1_PWANE1_PSI0  0x40
#define PSI_SEW_VW1_PWANE1_PSI1  0x80


#define THWOTTWEW_STATUS_PADDING_BIT      0
#define THWOTTWEW_STATUS_TEMP_EDGE_BIT    1
#define THWOTTWEW_STATUS_TEMP_HOTSPOT_BIT 2
#define THWOTTWEW_STATUS_TEMP_HBM_BIT     3
#define THWOTTWEW_STATUS_TEMP_VW_GFX_BIT  4
#define THWOTTWEW_STATUS_TEMP_VW_SOC_BIT  5
#define THWOTTWEW_STATUS_TEMP_VW_MEM0_BIT 6
#define THWOTTWEW_STATUS_TEMP_VW_MEM1_BIT 7
#define THWOTTWEW_STATUS_TEMP_WIQUID_BIT  8
#define THWOTTWEW_STATUS_TEMP_PWX_BIT     9
#define THWOTTWEW_STATUS_TEMP_SKIN_BIT    10
#define THWOTTWEW_STATUS_TDC_GFX_BIT      11
#define THWOTTWEW_STATUS_TDC_SOC_BIT      12
#define THWOTTWEW_STATUS_PPT_BIT          13
#define THWOTTWEW_STATUS_FIT_BIT          14
#define THWOTTWEW_STATUS_PPM_BIT          15


#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF


#define WOWKWOAD_DEFAUWT_BIT              0
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 1
#define WOWKWOAD_PPWIB_POWEW_SAVING_BIT   2
#define WOWKWOAD_PPWIB_VIDEO_BIT          3
#define WOWKWOAD_PPWIB_VW_BIT             4
#define WOWKWOAD_PPWIB_COMPUTE_BIT        5
#define WOWKWOAD_PPWIB_CUSTOM_BIT         6
#define WOWKWOAD_PPWIB_COUNT              7


#define XGMI_STATE_D0 1
#define XGMI_STATE_D3 0

typedef enum {
  I2C_CONTWOWWEW_POWT_0 = 0,
  I2C_CONTWOWWEW_POWT_1 = 1,
} I2cContwowwewPowt_e;

typedef enum {
  I2C_CONTWOWWEW_NAME_VW_GFX = 0,
  I2C_CONTWOWWEW_NAME_VW_SOC,
  I2C_CONTWOWWEW_NAME_VW_VDDCI,
  I2C_CONTWOWWEW_NAME_VW_HBM,
  I2C_CONTWOWWEW_NAME_WIQUID_0,
  I2C_CONTWOWWEW_NAME_WIQUID_1,
  I2C_CONTWOWWEW_NAME_PWX,
  I2C_CONTWOWWEW_NAME_COUNT,
} I2cContwowwewName_e;

typedef enum {
  I2C_CONTWOWWEW_THWOTTWEW_TYPE_NONE = 0,
  I2C_CONTWOWWEW_THWOTTWEW_VW_GFX,
  I2C_CONTWOWWEW_THWOTTWEW_VW_SOC,
  I2C_CONTWOWWEW_THWOTTWEW_VW_VDDCI,
  I2C_CONTWOWWEW_THWOTTWEW_VW_HBM,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID_0,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID_1,
  I2C_CONTWOWWEW_THWOTTWEW_PWX,
} I2cContwowwewThwottwew_e;

typedef enum {
  I2C_CONTWOWWEW_PWOTOCOW_VW_XPDE132G5,
  I2C_CONTWOWWEW_PWOTOCOW_VW_IW35217,
  I2C_CONTWOWWEW_PWOTOCOW_TMP_TMP102A,
  I2C_CONTWOWWEW_PWOTOCOW_SPAWE_0,
  I2C_CONTWOWWEW_PWOTOCOW_SPAWE_1,
  I2C_CONTWOWWEW_PWOTOCOW_SPAWE_2,
} I2cContwowwewPwotocow_e;

typedef enum {
  I2C_CONTWOWWEW_SPEED_SWOW = 0,
  I2C_CONTWOWWEW_SPEED_FAST = 1,
} I2cContwowwewSpeed_e;

typedef stwuct {
  uint32_t Enabwed;
  uint32_t SwaveAddwess;
  uint32_t ContwowwewPowt;
  uint32_t ContwowwewName;

  uint32_t ThewmawThwottwew;
  uint32_t I2cPwotocow;
  uint32_t I2cSpeed;
} I2cContwowwewConfig_t;

typedef stwuct {
  uint32_t a;
  uint32_t b;
  uint32_t c;
} QuadwaticInt_t;

typedef stwuct {
  uint32_t m;
  uint32_t b;
} WineawInt_t;

typedef stwuct {
  uint32_t a;
  uint32_t b;
  uint32_t c;
} DwoopInt_t;

typedef enum {
  PPCWK_GFXCWK,
  PPCWK_VCWK,
  PPCWK_DCWK,
  PPCWK_ECWK,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_DCEFCWK,
  PPCWK_DISPCWK,
  PPCWK_PIXCWK,
  PPCWK_PHYCWK,
  PPCWK_FCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  POWEW_SOUWCE_AC,
  POWEW_SOUWCE_DC,
  POWEW_SOUWCE_COUNT,
} POWEW_SOUWCE_e;

typedef enum {
  VOWTAGE_MODE_AVFS = 0,
  VOWTAGE_MODE_AVFS_SS,
  VOWTAGE_MODE_SS,
  VOWTAGE_MODE_COUNT,
} VOWTAGE_MODE_e;


typedef enum {
  AVFS_VOWTAGE_GFX = 0,
  AVFS_VOWTAGE_SOC,
  AVFS_VOWTAGE_COUNT,
} AVFS_VOWTAGE_TYPE_e;


typedef stwuct {
  uint8_t        VowtageMode;
  uint8_t        SnapToDiscwete;
  uint8_t        NumDiscweteWevews;
  uint8_t        padding;
  WineawInt_t    ConvewsionToAvfsCwk;
  QuadwaticInt_t SsCuwve;
} DpmDescwiptow_t;

#pwagma pack(push, 1)
typedef stwuct {
  uint32_t Vewsion;


  uint32_t FeatuwesToWun[2];


  uint16_t SocketPowewWimitAc0;
  uint16_t SocketPowewWimitAc0Tau;
  uint16_t SocketPowewWimitAc1;
  uint16_t SocketPowewWimitAc1Tau;
  uint16_t SocketPowewWimitAc2;
  uint16_t SocketPowewWimitAc2Tau;
  uint16_t SocketPowewWimitAc3;
  uint16_t SocketPowewWimitAc3Tau;
  uint16_t SocketPowewWimitDc;
  uint16_t SocketPowewWimitDcTau;
  uint16_t TdcWimitSoc;
  uint16_t TdcWimitSocTau;
  uint16_t TdcWimitGfx;
  uint16_t TdcWimitGfxTau;

  uint16_t TedgeWimit;
  uint16_t ThotspotWimit;
  uint16_t ThbmWimit;
  uint16_t Tvw_gfxWimit;
  uint16_t Tvw_memWimit;
  uint16_t Twiquid1Wimit;
  uint16_t Twiquid2Wimit;
  uint16_t TpwxWimit;
  uint32_t FitWimit;

  uint16_t PpmPowewWimit;
  uint16_t PpmTempewatuweThweshowd;

  uint8_t  MemowyOnPackage;
  uint8_t  padding8_wimits;
  uint16_t Tvw_SocWimit;

  uint16_t  UwvVowtageOffsetSoc;
  uint16_t  UwvVowtageOffsetGfx;

  uint8_t  UwvSmncwkDid;
  uint8_t  UwvMp1cwkDid;
  uint8_t  UwvGfxcwkBypass;
  uint8_t  Padding234;


  uint16_t     MinVowtageGfx;
  uint16_t     MinVowtageSoc;
  uint16_t     MaxVowtageGfx;
  uint16_t     MaxVowtageSoc;

  uint16_t     WoadWineWesistanceGfx;
  uint16_t     WoadWineWesistanceSoc;

  DpmDescwiptow_t DpmDescwiptow[PPCWK_COUNT];

  uint16_t       FweqTabweGfx      [NUM_GFXCWK_DPM_WEVEWS  ];
  uint16_t       FweqTabweVcwk     [NUM_VCWK_DPM_WEVEWS    ];
  uint16_t       FweqTabweDcwk     [NUM_DCWK_DPM_WEVEWS    ];
  uint16_t       FweqTabweEcwk     [NUM_ECWK_DPM_WEVEWS    ];
  uint16_t       FweqTabweSoccwk   [NUM_SOCCWK_DPM_WEVEWS  ];
  uint16_t       FweqTabweUcwk     [NUM_UCWK_DPM_WEVEWS    ];
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];
  uint16_t       FweqTabweDcefcwk  [NUM_DCEFCWK_DPM_WEVEWS ];
  uint16_t       FweqTabweDispcwk  [NUM_DISPCWK_DPM_WEVEWS ];
  uint16_t       FweqTabwePixcwk   [NUM_PIXCWK_DPM_WEVEWS  ];
  uint16_t       FweqTabwePhycwk   [NUM_PHYCWK_DPM_WEVEWS  ];

  uint16_t       DcModeMaxFweq     [PPCWK_COUNT            ];
  uint16_t       Padding8_Cwks;

  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];


  uint16_t        GfxcwkFidwe;
  uint16_t        GfxcwkSwewWate;
  uint16_t        CksEnabweFweq;
  uint16_t        Padding789;
  QuadwaticInt_t  CksVowtageOffset;
  uint8_t         Padding567[4];
  uint16_t        GfxcwkDsMaxFweq;
  uint8_t         GfxcwkSouwce;
  uint8_t         Padding456;

  uint8_t      WowestUcwkWesewvedFowUwv;
  uint8_t      Padding8_Ucwk[3];


  uint8_t      PcieGenSpeed[NUM_WINK_WEVEWS];
  uint8_t      PcieWaneCount[NUM_WINK_WEVEWS];
  uint16_t     WcwkFweq[NUM_WINK_WEVEWS];


  uint16_t     EnabweTdpm;
  uint16_t     TdpmHighHystTempewatuwe;
  uint16_t     TdpmWowHystTempewatuwe;
  uint16_t     GfxcwkFweqHighTempWimit;


  uint16_t     FanStopTemp;
  uint16_t     FanStawtTemp;

  uint16_t     FanGainEdge;
  uint16_t     FanGainHotspot;
  uint16_t     FanGainWiquid;
  uint16_t     FanGainVwGfx;
  uint16_t     FanGainVwSoc;
  uint16_t     FanGainPwx;
  uint16_t     FanGainHbm;
  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint8_t      FanZewoWpmEnabwe;
  uint8_t      FanTachEdgePewWev;



  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;


  uint8_t           OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_Avfs[2];

  QuadwaticInt_t    qAvfsGb[AVFS_VOWTAGE_COUNT];
  DwoopInt_t        dBtcGbGfxCksOn;
  DwoopInt_t        dBtcGbGfxCksOff;
  DwoopInt_t        dBtcGbGfxAfww;
  DwoopInt_t        dBtcGbSoc;
  WineawInt_t       qAgingGb[AVFS_VOWTAGE_COUNT];

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_VOWTAGE_COUNT];

  uint16_t          DcTow[AVFS_VOWTAGE_COUNT];

  uint8_t           DcBtcEnabwed[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_GfxBtc[2];

  int16_t           DcBtcMin[AVFS_VOWTAGE_COUNT];
  uint16_t          DcBtcMax[AVFS_VOWTAGE_COUNT];


  uint8_t           XgmiWinkSpeed   [NUM_XGMI_WEVEWS];
  uint8_t           XgmiWinkWidth   [NUM_XGMI_WEVEWS];
  uint16_t          XgmiFcwkFweq    [NUM_XGMI_WEVEWS];
  uint16_t          XgmiUcwkFweq    [NUM_XGMI_WEVEWS];
  uint16_t          XgmiSoccwkFweq  [NUM_XGMI_WEVEWS];
  uint16_t          XgmiSocVowtage  [NUM_XGMI_WEVEWS];

  uint32_t          DebugOvewwides;
  QuadwaticInt_t    WesewvedEquation0;
  QuadwaticInt_t    WesewvedEquation1;
  QuadwaticInt_t    WesewvedEquation2;
  QuadwaticInt_t    WesewvedEquation3;

  uint16_t     MinVowtageUwvGfx;
  uint16_t     MinVowtageUwvSoc;

  uint16_t     MGpuFanBoostWimitWpm;
  uint16_t     padding16_Fan;

  uint16_t     FanGainVwMem0;
  uint16_t     FanGainVwMem1;

  uint16_t     DcBtcGb[AVFS_VOWTAGE_COUNT];

  uint32_t     Wesewved[11];

  uint32_t     Padding32[3];

  uint16_t     MaxVowtageStepGfx;
  uint16_t     MaxVowtageStepSoc;

  uint8_t      VddGfxVwMapping;
  uint8_t      VddSocVwMapping;
  uint8_t      VddMem0VwMapping;
  uint8_t      VddMem1VwMapping;

  uint8_t      GfxUwvPhaseSheddingMask;
  uint8_t      SocUwvPhaseSheddingMask;
  uint8_t      ExtewnawSensowPwesent;
  uint8_t      Padding8_V;


  uint16_t     GfxMaxCuwwent;
  int8_t       GfxOffset;
  uint8_t      Padding_TewemetwyGfx;

  uint16_t     SocMaxCuwwent;
  int8_t       SocOffset;
  uint8_t      Padding_TewemetwySoc;

  uint16_t     Mem0MaxCuwwent;
  int8_t       Mem0Offset;
  uint8_t      Padding_TewemetwyMem0;

  uint16_t     Mem1MaxCuwwent;
  int8_t       Mem1Offset;
  uint8_t      Padding_TewemetwyMem1;


  uint8_t      AcDcGpio;
  uint8_t      AcDcPowawity;
  uint8_t      VW0HotGpio;
  uint8_t      VW0HotPowawity;

  uint8_t      VW1HotGpio;
  uint8_t      VW1HotPowawity;
  uint8_t      Padding1;
  uint8_t      Padding2;



  uint8_t      WedPin0;
  uint8_t      WedPin1;
  uint8_t      WedPin2;
  uint8_t      padding8_4;


  uint8_t      PwwGfxcwkSpweadEnabwed;
  uint8_t      PwwGfxcwkSpweadPewcent;
  uint16_t     PwwGfxcwkSpweadFweq;

  uint8_t      UcwkSpweadEnabwed;
  uint8_t      UcwkSpweadPewcent;
  uint16_t     UcwkSpweadFweq;

  uint8_t      FcwkSpweadEnabwed;
  uint8_t      FcwkSpweadPewcent;
  uint16_t     FcwkSpweadFweq;

  uint8_t      FwwGfxcwkSpweadEnabwed;
  uint8_t      FwwGfxcwkSpweadPewcent;
  uint16_t     FwwGfxcwkSpweadFweq;

  I2cContwowwewConfig_t I2cContwowwews[I2C_CONTWOWWEW_NAME_COUNT];

  uint32_t     BoawdWesewved[10];


  uint32_t     MmHubPadding[8];

} PPTabwe_t;
#pwagma pack(pop)

typedef stwuct {

  uint16_t     GfxcwkAvewageWpfTau;
  uint16_t     SoccwkAvewageWpfTau;
  uint16_t     UcwkAvewageWpfTau;
  uint16_t     GfxActivityWpfTau;
  uint16_t     UcwkActivityWpfTau;
  uint16_t     SocketPowewWpfTau;


  uint32_t     MmHubPadding[8];
} DwivewSmuConfig_t;

typedef stwuct {

  uint16_t      GfxcwkFmin;
  uint16_t      GfxcwkFmax;
  uint16_t      GfxcwkFweq1;
  uint16_t      GfxcwkVowt1;
  uint16_t      GfxcwkFweq2;
  uint16_t      GfxcwkVowt2;
  uint16_t      GfxcwkFweq3;
  uint16_t      GfxcwkVowt3;
  uint16_t      UcwkFmax;
  int16_t       OvewDwivePct;
  uint16_t      FanMaximumWpm;
  uint16_t      FanMinimumPwm;
  uint16_t      FanTawgetTempewatuwe;
  uint16_t      MaxOpTemp;
  uint16_t      FanZewoWpmEnabwe;
  uint16_t      Padding;

} OvewDwiveTabwe_t;

typedef stwuct {
  uint16_t CuwwCwock[PPCWK_COUNT];
  uint16_t AvewageGfxcwkFwequency;
  uint16_t AvewageSoccwkFwequency;
  uint16_t AvewageUcwkFwequency  ;
  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint8_t  CuwwSocVowtageOffset  ;
  uint8_t  CuwwGfxVowtageOffset  ;
  uint8_t  CuwwMemVidOffset      ;
  uint8_t  Padding8              ;
  uint16_t CuwwSocketPowew       ;
  uint16_t TempewatuweEdge       ;
  uint16_t TempewatuweHotspot    ;
  uint16_t TempewatuweHBM        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwSoc      ;
  uint16_t TempewatuweVwMem0     ;
  uint16_t TempewatuweVwMem1     ;
  uint16_t TempewatuweWiquid     ;
  uint16_t TempewatuwePwx        ;
  uint32_t ThwottwewStatus       ;

  uint8_t  WinkDpmWevew;
  uint16_t AvewageSocketPowew;
  uint8_t  Padding;


  uint32_t     MmHubPadding[7];
} SmuMetwics_t;

typedef stwuct {
  uint16_t MinCwock;
  uint16_t MaxCwock;
  uint16_t MinUcwk;
  uint16_t MaxUcwk;

  uint8_t  WmSetting;
  uint8_t  Padding[3];
} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WM_SOCCWK = 0,
  WM_DCEFCWK,
  WM_COUNT_PP,
} WM_CWOCK_e;

typedef stwuct {

  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT_PP][NUM_WM_WANGES];

  uint32_t     MmHubPadding[7];
} Watewmawks_t;

typedef stwuct {
  uint16_t avgPsmCount[45];
  uint16_t minPsmCount[45];
  fwoat    avgPsmVowtage[45];
  fwoat    minPsmVowtage[45];

  uint16_t avgScsPsmCount;
  uint16_t minScsPsmCount;
  fwoat    avgScsPsmVowtage;
  fwoat    minScsPsmVowtage;


  uint32_t MmHubPadding[6];
} AvfsDebugTabwe_t;

typedef stwuct {
  uint8_t  AvfsVewsion;
  uint8_t  AvfsEn[AVFS_VOWTAGE_COUNT];

  uint8_t  OvewwideVFT[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];

  uint8_t  OvewwideTempewatuwes[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideVInvewsion[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideP2V[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideP2VChawzFweq[AVFS_VOWTAGE_COUNT];

  int32_t VFT0_m1[AVFS_VOWTAGE_COUNT];
  int32_t VFT0_m2[AVFS_VOWTAGE_COUNT];
  int32_t VFT0_b[AVFS_VOWTAGE_COUNT];

  int32_t VFT1_m1[AVFS_VOWTAGE_COUNT];
  int32_t VFT1_m2[AVFS_VOWTAGE_COUNT];
  int32_t VFT1_b[AVFS_VOWTAGE_COUNT];

  int32_t VFT2_m1[AVFS_VOWTAGE_COUNT];
  int32_t VFT2_m2[AVFS_VOWTAGE_COUNT];
  int32_t VFT2_b[AVFS_VOWTAGE_COUNT];

  int32_t AvfsGb0_m1[AVFS_VOWTAGE_COUNT];
  int32_t AvfsGb0_m2[AVFS_VOWTAGE_COUNT];
  int32_t AvfsGb0_b[AVFS_VOWTAGE_COUNT];

  int32_t AcBtcGb_m1[AVFS_VOWTAGE_COUNT];
  int32_t AcBtcGb_m2[AVFS_VOWTAGE_COUNT];
  int32_t AcBtcGb_b[AVFS_VOWTAGE_COUNT];

  uint32_t AvfsTempCowd[AVFS_VOWTAGE_COUNT];
  uint32_t AvfsTempMid[AVFS_VOWTAGE_COUNT];
  uint32_t AvfsTempHot[AVFS_VOWTAGE_COUNT];

  uint32_t VInvewsion[AVFS_VOWTAGE_COUNT];


  int32_t P2V_m1[AVFS_VOWTAGE_COUNT];
  int32_t P2V_m2[AVFS_VOWTAGE_COUNT];
  int32_t P2V_b[AVFS_VOWTAGE_COUNT];

  uint32_t P2VChawzFweq[AVFS_VOWTAGE_COUNT];

  uint32_t EnabwedAvfsModuwes;

  uint32_t MmHubPadding[7];
} AvfsFuseOvewwide_t;

typedef stwuct {

  uint8_t   Gfx_ActiveHystWimit;
  uint8_t   Gfx_IdweHystWimit;
  uint8_t   Gfx_FPS;
  uint8_t   Gfx_MinActiveFweqType;
  uint8_t   Gfx_BoostewFweqType; 
  uint8_t   Gfx_UseWwcBusy; 
  uint16_t  Gfx_MinActiveFweq;
  uint16_t  Gfx_BoostewFweq;
  uint16_t  Gfx_PD_Data_time_constant;
  uint32_t  Gfx_PD_Data_wimit_a;
  uint32_t  Gfx_PD_Data_wimit_b;
  uint32_t  Gfx_PD_Data_wimit_c;
  uint32_t  Gfx_PD_Data_ewwow_coeff;
  uint32_t  Gfx_PD_Data_ewwow_wate_coeff;

  uint8_t   Soc_ActiveHystWimit;
  uint8_t   Soc_IdweHystWimit;
  uint8_t   Soc_FPS;
  uint8_t   Soc_MinActiveFweqType;
  uint8_t   Soc_BoostewFweqType; 
  uint8_t   Soc_UseWwcBusy;
  uint16_t  Soc_MinActiveFweq;
  uint16_t  Soc_BoostewFweq;
  uint16_t  Soc_PD_Data_time_constant;
  uint32_t  Soc_PD_Data_wimit_a;
  uint32_t  Soc_PD_Data_wimit_b;
  uint32_t  Soc_PD_Data_wimit_c;
  uint32_t  Soc_PD_Data_ewwow_coeff;
  uint32_t  Soc_PD_Data_ewwow_wate_coeff;

  uint8_t   Mem_ActiveHystWimit;
  uint8_t   Mem_IdweHystWimit;
  uint8_t   Mem_FPS;
  uint8_t   Mem_MinActiveFweqType;
  uint8_t   Mem_BoostewFweqType;
  uint8_t   Mem_UseWwcBusy; 
  uint16_t  Mem_MinActiveFweq;
  uint16_t  Mem_BoostewFweq;
  uint16_t  Mem_PD_Data_time_constant;
  uint32_t  Mem_PD_Data_wimit_a;
  uint32_t  Mem_PD_Data_wimit_b;
  uint32_t  Mem_PD_Data_wimit_c;
  uint32_t  Mem_PD_Data_ewwow_coeff;
  uint32_t  Mem_PD_Data_ewwow_wate_coeff;

  uint8_t   Fcwk_ActiveHystWimit;
  uint8_t   Fcwk_IdweHystWimit;
  uint8_t   Fcwk_FPS;
  uint8_t   Fcwk_MinActiveFweqType;
  uint8_t   Fcwk_BoostewFweqType;
  uint8_t   Fcwk_UseWwcBusy;
  uint16_t  Fcwk_MinActiveFweq;
  uint16_t  Fcwk_BoostewFweq;
  uint16_t  Fcwk_PD_Data_time_constant;
  uint32_t  Fcwk_PD_Data_wimit_a;
  uint32_t  Fcwk_PD_Data_wimit_b;
  uint32_t  Fcwk_PD_Data_wimit_c;
  uint32_t  Fcwk_PD_Data_ewwow_coeff;
  uint32_t  Fcwk_PD_Data_ewwow_wate_coeff;

} DpmActivityMonitowCoeffInt_t;

#define TABWE_PPTABWE                 0
#define TABWE_WATEWMAWKS              1
#define TABWE_AVFS                    2
#define TABWE_AVFS_PSM_DEBUG          3
#define TABWE_AVFS_FUSE_OVEWWIDE      4
#define TABWE_PMSTATUSWOG             5
#define TABWE_SMU_METWICS             6
#define TABWE_DWIVEW_SMU_CONFIG       7
#define TABWE_ACTIVITY_MONITOW_COEFF  8
#define TABWE_OVEWDWIVE               9
#define TABWE_COUNT                  10


#define UCWK_SWITCH_SWOW 0
#define UCWK_SWITCH_FAST 1


#define SQ_Enabwe_MASK 0x1
#define SQ_IW_MASK 0x2
#define SQ_PCC_MASK 0x4
#define SQ_EDC_MASK 0x8

#define TCP_Enabwe_MASK 0x100
#define TCP_IW_MASK 0x200
#define TCP_PCC_MASK 0x400
#define TCP_EDC_MASK 0x800

#define TD_Enabwe_MASK 0x10000
#define TD_IW_MASK 0x20000
#define TD_PCC_MASK 0x40000
#define TD_EDC_MASK 0x80000

#define DB_Enabwe_MASK 0x1000000
#define DB_IW_MASK 0x2000000
#define DB_PCC_MASK 0x4000000
#define DB_EDC_MASK 0x8000000

#define SQ_Enabwe_SHIFT 0
#define SQ_IW_SHIFT 1
#define SQ_PCC_SHIFT 2
#define SQ_EDC_SHIFT 3

#define TCP_Enabwe_SHIFT 8
#define TCP_IW_SHIFT 9
#define TCP_PCC_SHIFT 10
#define TCP_EDC_SHIFT 11

#define TD_Enabwe_SHIFT 16
#define TD_IW_SHIFT 17
#define TD_PCC_SHIFT 18
#define TD_EDC_SHIFT 19

#define DB_Enabwe_SHIFT 24
#define DB_IW_SHIFT 25
#define DB_PCC_SHIFT 26
#define DB_EDC_SHIFT 27

#define WEMOVE_FMAX_MAWGIN_BIT     0x0
#define WEMOVE_DCTOW_MAWGIN_BIT    0x1
#define WEMOVE_PWATFOWM_MAWGIN_BIT 0x2

#endif
