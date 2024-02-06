/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef SMU11_DWIVEW_IF_AWCTUWUS_H
#define SMU11_DWIVEW_IF_AWCTUWUS_H

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if
// any stwuctuwe is changed in this fiwe
//#define SMU11_DWIVEW_IF_VEWSION 0x09

#define PPTABWE_AWCTUWUS_SMU_VEWSION 4

#define NUM_GFXCWK_DPM_WEVEWS  16
#define NUM_VCWK_DPM_WEVEWS    8
#define NUM_DCWK_DPM_WEVEWS    8
#define NUM_MP0CWK_DPM_WEVEWS  2
#define NUM_SOCCWK_DPM_WEVEWS  8
#define NUM_UCWK_DPM_WEVEWS    4
#define NUM_FCWK_DPM_WEVEWS    8
#define NUM_XGMI_WEVEWS        2
#define NUM_XGMI_PSTATE_WEVEWS 4

#define MAX_GFXCWK_DPM_WEVEW  (NUM_GFXCWK_DPM_WEVEWS  - 1)
#define MAX_VCWK_DPM_WEVEW    (NUM_VCWK_DPM_WEVEWS    - 1)
#define MAX_DCWK_DPM_WEVEW    (NUM_DCWK_DPM_WEVEWS    - 1)
#define MAX_MP0CWK_DPM_WEVEW  (NUM_MP0CWK_DPM_WEVEWS  - 1)
#define MAX_SOCCWK_DPM_WEVEW  (NUM_SOCCWK_DPM_WEVEWS  - 1)
#define MAX_UCWK_DPM_WEVEW    (NUM_UCWK_DPM_WEVEWS    - 1)
#define MAX_FCWK_DPM_WEVEW    (NUM_FCWK_DPM_WEVEWS    - 1)
#define MAX_XGMI_WEVEW        (NUM_XGMI_WEVEWS        - 1)
#define MAX_XGMI_PSTATE_WEVEW (NUM_XGMI_PSTATE_WEVEWS - 1)

// Featuwe Contwow Defines
// DPM
#define FEATUWE_DPM_PWEFETCHEW_BIT      0
#define FEATUWE_DPM_GFXCWK_BIT          1
#define FEATUWE_DPM_UCWK_BIT            2
#define FEATUWE_DPM_SOCCWK_BIT          3
#define FEATUWE_DPM_FCWK_BIT            4
#define FEATUWE_DPM_MP0CWK_BIT          5
#define FEATUWE_DPM_XGMI_BIT            6
// Idwe
#define FEATUWE_DS_GFXCWK_BIT           7
#define FEATUWE_DS_SOCCWK_BIT           8
#define FEATUWE_DS_WCWK_BIT             9
#define FEATUWE_DS_FCWK_BIT             10
#define FEATUWE_DS_UCWK_BIT             11
#define FEATUWE_GFX_UWV_BIT             12
#define FEATUWE_DPM_VCN_BIT             13
#define FEATUWE_WSMU_SMN_CG_BIT         14
#define FEATUWE_WAFW_CG_BIT             15
// Thwottwew/Wesponse
#define FEATUWE_PPT_BIT                 16
#define FEATUWE_TDC_BIT                 17
#define FEATUWE_APCC_PWUS_BIT           18
#define FEATUWE_VW0HOT_BIT              19
#define FEATUWE_VW1HOT_BIT              20
#define FEATUWE_FW_CTF_BIT              21
#define FEATUWE_FAN_CONTWOW_BIT         22
#define FEATUWE_THEWMAW_BIT             23
// Othew
#define FEATUWE_OUT_OF_BAND_MONITOW_BIT 24
#define FEATUWE_TEMP_DEPENDENT_VMIN_BIT 25
#define FEATUWE_PEW_PAWT_VMIN_BIT       26

#define FEATUWE_SPAWE_27_BIT            27
#define FEATUWE_SPAWE_28_BIT            28
#define FEATUWE_SPAWE_29_BIT            29
#define FEATUWE_SPAWE_30_BIT            30
#define FEATUWE_SPAWE_31_BIT            31
#define FEATUWE_SPAWE_32_BIT            32
#define FEATUWE_SPAWE_33_BIT            33
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


#define FEATUWE_DPM_PWEFETCHEW_MASK       (1 << FEATUWE_DPM_PWEFETCHEW_BIT       )
#define FEATUWE_DPM_GFXCWK_MASK           (1 << FEATUWE_DPM_GFXCWK_BIT           )
#define FEATUWE_DPM_UCWK_MASK             (1 << FEATUWE_DPM_UCWK_BIT             )
#define FEATUWE_DPM_SOCCWK_MASK           (1 << FEATUWE_DPM_SOCCWK_BIT           )
#define FEATUWE_DPM_FCWK_MASK             (1 << FEATUWE_DPM_FCWK_BIT             )
#define FEATUWE_DPM_MP0CWK_MASK           (1 << FEATUWE_DPM_MP0CWK_BIT           )
#define FEATUWE_DPM_XGMI_MASK             (1 << FEATUWE_DPM_XGMI_BIT             )

#define FEATUWE_DS_GFXCWK_MASK            (1 << FEATUWE_DS_GFXCWK_BIT            )
#define FEATUWE_DS_SOCCWK_MASK            (1 << FEATUWE_DS_SOCCWK_BIT            )
#define FEATUWE_DS_WCWK_MASK              (1 << FEATUWE_DS_WCWK_BIT              )
#define FEATUWE_DS_FCWK_MASK              (1 << FEATUWE_DS_FCWK_BIT              )
#define FEATUWE_DS_UCWK_MASK              (1 << FEATUWE_DS_UCWK_BIT              )
#define FEATUWE_GFX_UWV_MASK              (1 << FEATUWE_GFX_UWV_BIT              )
#define FEATUWE_DPM_VCN_MASK              (1 << FEATUWE_DPM_VCN_BIT              )
#define FEATUWE_WSMU_SMN_CG_MASK          (1 << FEATUWE_WSMU_SMN_CG_BIT          )
#define FEATUWE_WAFW_CG_MASK              (1 << FEATUWE_WAFW_CG_BIT              )

#define FEATUWE_PPT_MASK                  (1 << FEATUWE_PPT_BIT                  )
#define FEATUWE_TDC_MASK                  (1 << FEATUWE_TDC_BIT                  )
#define FEATUWE_APCC_PWUS_MASK            (1 << FEATUWE_APCC_PWUS_BIT            )
#define FEATUWE_VW0HOT_MASK               (1 << FEATUWE_VW0HOT_BIT               )
#define FEATUWE_VW1HOT_MASK               (1 << FEATUWE_VW1HOT_BIT               )
#define FEATUWE_FW_CTF_MASK               (1 << FEATUWE_FW_CTF_BIT               )
#define FEATUWE_FAN_CONTWOW_MASK          (1 << FEATUWE_FAN_CONTWOW_BIT          )
#define FEATUWE_THEWMAW_MASK              (1 << FEATUWE_THEWMAW_BIT              )

#define FEATUWE_OUT_OF_BAND_MONITOW_MASK  (1 << FEATUWE_OUT_OF_BAND_MONITOW_BIT   )
#define FEATUWE_TEMP_DEPENDENT_VMIN_MASK  (1 << FEATUWE_TEMP_DEPENDENT_VMIN_BIT )
#define FEATUWE_PEW_PAWT_VMIN_MASK        (1 << FEATUWE_PEW_PAWT_VMIN_BIT        )


//FIXME need updating
// Debug Ovewwides Bitmask
#define DPM_OVEWWIDE_DISABWE_UCWK_PID               0x00000001
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_VCN_FCWK     0x00000002

// I2C Config Bit Defines
#define I2C_CONTWOWWEW_ENABWED           1
#define I2C_CONTWOWWEW_DISABWED          0

// VW Mapping Bit Defines
#define VW_MAPPING_VW_SEWECT_MASK  0x01
#define VW_MAPPING_VW_SEWECT_SHIFT 0x00

#define VW_MAPPING_PWANE_SEWECT_MASK  0x02
#define VW_MAPPING_PWANE_SEWECT_SHIFT 0x01

// PSI Bit Defines
#define PSI_SEW_VW0_PWANE0_PSI0  0x01
#define PSI_SEW_VW0_PWANE0_PSI1  0x02
#define PSI_SEW_VW0_PWANE1_PSI0  0x04
#define PSI_SEW_VW0_PWANE1_PSI1  0x08
#define PSI_SEW_VW1_PWANE0_PSI0  0x10
#define PSI_SEW_VW1_PWANE0_PSI1  0x20
#define PSI_SEW_VW1_PWANE1_PSI0  0x40
#define PSI_SEW_VW1_PWANE1_PSI1  0x80

// Thwottwew Contwow/Status Bits
#define THWOTTWEW_PADDING_BIT      0
#define THWOTTWEW_TEMP_EDGE_BIT    1
#define THWOTTWEW_TEMP_HOTSPOT_BIT 2
#define THWOTTWEW_TEMP_MEM_BIT     3
#define THWOTTWEW_TEMP_VW_GFX_BIT  4
#define THWOTTWEW_TEMP_VW_MEM_BIT  5
#define THWOTTWEW_TEMP_VW_SOC_BIT  6
#define THWOTTWEW_TDC_GFX_BIT      7
#define THWOTTWEW_TDC_SOC_BIT      8
#define THWOTTWEW_PPT0_BIT         9
#define THWOTTWEW_PPT1_BIT         10
#define THWOTTWEW_PPT2_BIT         11
#define THWOTTWEW_PPT3_BIT         12
#define THWOTTWEW_PPM_BIT          13
#define THWOTTWEW_FIT_BIT          14
#define THWOTTWEW_APCC_BIT         15
#define THWOTTWEW_VWHOT0_BIT       16
#define THWOTTWEW_VWHOT1_BIT       17

// Tabwe twansfew status
#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF
#define TABWE_TWANSFEW_PENDING    0xAB

// Wowkwoad bits
#define WOWKWOAD_PPWIB_DEFAUWT_BIT        0
#define WOWKWOAD_PPWIB_POWEW_SAVING_BIT   1
#define WOWKWOAD_PPWIB_VIDEO_BIT          2
#define WOWKWOAD_PPWIB_COMPUTE_BIT        3
#define WOWKWOAD_PPWIB_CUSTOM_BIT         4
#define WOWKWOAD_PPWIB_COUNT              5

//XGMI pewfowmance states
#define XGMI_STATE_D0 1
#define XGMI_STATE_D3 0

#define NUM_I2C_CONTWOWWEWS                8

#define I2C_CONTWOWWEW_ENABWED             1
#define I2C_CONTWOWWEW_DISABWED            0

#define MAX_SW_I2C_COMMANDS                8

typedef enum {
  I2C_CONTWOWWEW_POWT_0 = 0,  //CKSVII2C0
  I2C_CONTWOWWEW_POWT_1 = 1,  //CKSVII2C1
  I2C_CONTWOWWEW_POWT_COUNT,
} I2cContwowwewPowt_e;

typedef enum {
  I2C_CONTWOWWEW_NAME_VW_GFX = 0,
  I2C_CONTWOWWEW_NAME_VW_SOC,
  I2C_CONTWOWWEW_NAME_VW_MEM,
  I2C_CONTWOWWEW_NAME_SPAWE,
  I2C_CONTWOWWEW_NAME_COUNT,
} I2cContwowwewName_e;

typedef enum {
  I2C_CONTWOWWEW_THWOTTWEW_TYPE_NONE = 0,
  I2C_CONTWOWWEW_THWOTTWEW_VW_GFX,
  I2C_CONTWOWWEW_THWOTTWEW_VW_SOC,
  I2C_CONTWOWWEW_THWOTTWEW_VW_MEM,
  I2C_CONTWOWWEW_THWOTTWEW_COUNT,
} I2cContwowwewThwottwew_e;

typedef enum {
  I2C_CONTWOWWEW_PWOTOCOW_VW_0,
  I2C_CONTWOWWEW_PWOTOCOW_VW_1,
  I2C_CONTWOWWEW_PWOTOCOW_TMP_0,
  I2C_CONTWOWWEW_PWOTOCOW_TMP_1,
  I2C_CONTWOWWEW_PWOTOCOW_SPAWE_0,
  I2C_CONTWOWWEW_PWOTOCOW_SPAWE_1,
  I2C_CONTWOWWEW_PWOTOCOW_COUNT,
} I2cContwowwewPwotocow_e;

typedef stwuct {
  uint8_t   Enabwed;
  uint8_t   Speed;
  uint8_t   Padding[2];
  uint32_t  SwaveAddwess;
  uint8_t   ContwowwewPowt;
  uint8_t   ContwowwewName;
  uint8_t   ThewmawThwottew;
  uint8_t   I2cPwotocow;
} I2cContwowwewConfig_t;

typedef enum {
  I2C_POWT_SVD_SCW = 0,
  I2C_POWT_GPIO,
} I2cPowt_e;

typedef enum {
  I2C_SPEED_FAST_50K = 0,      //50  Kbits/s
  I2C_SPEED_FAST_100K,         //100 Kbits/s
  I2C_SPEED_FAST_400K,         //400 Kbits/s
  I2C_SPEED_FAST_PWUS_1M,      //1   Mbits/s (in fast mode)
  I2C_SPEED_HIGH_1M,           //1   Mbits/s (in high speed mode)
  I2C_SPEED_HIGH_2M,           //2.3 Mbits/s
  I2C_SPEED_COUNT,
} I2cSpeed_e;

typedef enum {
  I2C_CMD_WEAD = 0,
  I2C_CMD_WWITE,
  I2C_CMD_COUNT,
} I2cCmdType_e;

#define CMDCONFIG_STOP_BIT      0
#define CMDCONFIG_WESTAWT_BIT   1

#define CMDCONFIG_STOP_MASK     (1 << CMDCONFIG_STOP_BIT)
#define CMDCONFIG_WESTAWT_MASK  (1 << CMDCONFIG_WESTAWT_BIT)

typedef stwuct {
  uint8_t WegistewAddw; ////onwy vawid fow wwite, ignowed fow wead
  uint8_t Cmd;  //Wead(0) ow Wwite(1)
  uint8_t Data;  //Wetuwn data fow wead. Data to send fow wwite
  uint8_t CmdConfig; //Incwudes whethew associated command shouwd have a stop ow westawt command
} SwI2cCmd_t; //SW I2C Command Tabwe

typedef stwuct {
  uint8_t     I2CcontwowwewPowt; //CKSVII2C0(0) ow //CKSVII2C1(1)
  uint8_t     I2CSpeed;          //Swow(0) ow Fast(1)
  uint16_t    SwaveAddwess;
  uint8_t     NumCmds;           //Numbew of commands
  uint8_t     Padding[3];

  SwI2cCmd_t  SwI2cCmds[MAX_SW_I2C_COMMANDS];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use

} SwI2cWequest_t; // SW I2C Wequest Tabwe

//D3HOT sequences
typedef enum {
  BACO_SEQUENCE,
  MSW_SEQUENCE,
  BAMACO_SEQUENCE,
  UWPS_SEQUENCE,
  D3HOT_SEQUENCE_COUNT,
}D3HOTSequence_e;

//THis is awigned with WSMU PGFSM Wegistew Mapping
typedef enum {
  PG_DYNAMIC_MODE = 0,
  PG_STATIC_MODE,
} PowewGatingMode_e;

//This is awigned with WSMU PGFSM Wegistew Mapping
typedef enum {
  PG_POWEW_DOWN = 0,
  PG_POWEW_UP,
} PowewGatingSettings_e;

typedef stwuct {
  uint32_t a;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t b;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t c;  // stowe in IEEE fwoat fowmat in this vawiabwe
} QuadwaticInt_t;

typedef stwuct {
  uint32_t m;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t b;  // stowe in IEEE fwoat fowmat in this vawiabwe
} WineawInt_t;

typedef stwuct {
  uint32_t a;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t b;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t c;  // stowe in IEEE fwoat fowmat in this vawiabwe
} DwoopInt_t;

typedef enum {
  GFXCWK_SOUWCE_PWW = 0,
  GFXCWK_SOUWCE_AFWW,
  GFXCWK_SOUWCE_COUNT,
} GfxcwkSwc_e;

typedef enum {
  PPCWK_GFXCWK,
  PPCWK_VCWK,
  PPCWK_DCWK,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_FCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  POWEW_SOUWCE_AC,
  POWEW_SOUWCE_DC,
  POWEW_SOUWCE_COUNT,
} POWEW_SOUWCE_e;

typedef enum {
  TEMP_EDGE,
  TEMP_HOTSPOT,
  TEMP_MEM,
  TEMP_VW_GFX,
  TEMP_VW_SOC,
  TEMP_VW_MEM,
  TEMP_COUNT
} TEMP_TYPE_e;

typedef enum  {
  PPT_THWOTTWEW_PPT0,
  PPT_THWOTTWEW_PPT1,
  PPT_THWOTTWEW_PPT2,
  PPT_THWOTTWEW_PPT3,
  PPT_THWOTTWEW_COUNT
} PPT_THWOTTWEW_e;

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

typedef enum {
  GPIO_INT_POWAWITY_ACTIVE_WOW = 0,
  GPIO_INT_POWAWITY_ACTIVE_HIGH,
} GpioIntPowawity_e;

typedef enum {
  MEMOWY_TYPE_GDDW6 = 0,
  MEMOWY_TYPE_HBM,
} MemowyType_e;

typedef enum {
  PWW_CONFIG_TDP = 0,
  PWW_CONFIG_TGP,
  PWW_CONFIG_TCP_ESTIMATED,
  PWW_CONFIG_TCP_MEASUWED,
} PwwConfig_e;

typedef enum {
  XGMI_WINK_WATE_2 = 2,    // 2Gbps
  XGMI_WINK_WATE_4 = 4,    // 4Gbps
  XGMI_WINK_WATE_8 = 8,    // 8Gbps
  XGMI_WINK_WATE_12 = 12,  // 12Gbps
  XGMI_WINK_WATE_16 = 16,  // 16Gbps
  XGMI_WINK_WATE_17 = 17,  // 17Gbps
  XGMI_WINK_WATE_18 = 18,  // 18Gbps
  XGMI_WINK_WATE_19 = 19,  // 19Gbps
  XGMI_WINK_WATE_20 = 20,  // 20Gbps
  XGMI_WINK_WATE_21 = 21,  // 21Gbps
  XGMI_WINK_WATE_22 = 22,  // 22Gbps
  XGMI_WINK_WATE_23 = 23,  // 23Gbps
  XGMI_WINK_WATE_24 = 24,  // 24Gbps
  XGMI_WINK_WATE_25 = 25,  // 25Gbps
  XGMI_WINK_WATE_COUNT
} XGMI_WINK_WATE_e;

typedef enum {
  XGMI_WINK_WIDTH_1 = 1,   // x1
  XGMI_WINK_WIDTH_2 = 2,   // x2
  XGMI_WINK_WIDTH_4 = 4,   // x4
  XGMI_WINK_WIDTH_8 = 8,   // x8
  XGMI_WINK_WIDTH_9 = 9,   // x9
  XGMI_WINK_WIDTH_16 = 16, // x16
  XGMI_WINK_WIDTH_COUNT
} XGMI_WINK_WIDTH_e;

typedef stwuct {
  uint8_t        VowtageMode;         // 0 - AVFS onwy, 1- min(AVFS,SS), 2-SS onwy
  uint8_t        SnapToDiscwete;      // 0 - Fine gwained DPM, 1 - Discwete DPM
  uint8_t        NumDiscweteWevews;   // Set to 2 (Fmin, Fmax) when using fine gwained DPM, othewwise set to # discwete wevews used
  uint8_t        padding;
  WineawInt_t    ConvewsionToAvfsCwk; // Twansfew function to AVFS Cwock (GHz->GHz)
  QuadwaticInt_t SsCuwve;             // Swow-swow cuwve (GHz->V)
  uint16_t       SsFmin;              // Fmin fow SS cuwve. If SS cuwve is sewected, wiww use V@SSFmin fow F <= Fmin
  uint16_t       Padding16;
} DpmDescwiptow_t;

#pwagma pack(push, 1)
typedef stwuct {
  uint32_t Vewsion;

  // SECTION: Featuwe Enabwement
  uint32_t FeatuwesToWun[2];

  // SECTION: Infwastwuctuwe Wimits
  uint16_t SocketPowewWimitAc[PPT_THWOTTWEW_COUNT];
  uint16_t SocketPowewWimitAcTau[PPT_THWOTTWEW_COUNT];
  uint16_t TdcWimitSoc;             // Amps
  uint16_t TdcWimitSocTau;          // Time constant of WPF in ms
  uint16_t TdcWimitGfx;             // Amps
  uint16_t TdcWimitGfxTau;          // Time constant of WPF in ms

  uint16_t TedgeWimit;              // Cewcius
  uint16_t ThotspotWimit;           // Cewcius
  uint16_t TmemWimit;               // Cewcius
  uint16_t Tvw_gfxWimit;            // Cewcius
  uint16_t Tvw_memWimit;            // Cewcius
  uint16_t Tvw_socWimit;            // Cewcius
  uint32_t FitWimit;                // Faiwuwes in time (faiwuwes pew miwwion pawts ovew the defined wifetime)

  uint16_t PpmPowewWimit;           // Switch this this powew wimit when tempewatuwe is above PpmTempThweshowd
  uint16_t PpmTempewatuweThweshowd;

  // SECTION: Thwottwew settings
  uint32_t ThwottwewContwowMask;   // See Thwottew masks defines

  // SECTION: UWV Settings
  uint16_t  UwvVowtageOffsetGfx; // In mV(Q2)
  uint16_t  UwvPadding;          // Padding

  uint8_t  UwvGfxcwkBypass;  // 1 to tuwn off/bypass Gfxcwk duwing UWV, 0 to weave Gfxcwk on duwing UWV
  uint8_t  Padding234[3];

  // SECTION: Vowtage Contwow Pawametews
  uint16_t     MinVowtageGfx;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_GFX
  uint16_t     MinVowtageSoc;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_SOC
  uint16_t     MaxVowtageGfx;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_GFX
  uint16_t     MaxVowtageSoc;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_SOC

  uint16_t     WoadWineWesistanceGfx;   // In mOhms with 8 fwactionaw bits
  uint16_t     WoadWineWesistanceSoc;   // In mOhms with 8 fwactionaw bits

  //SECTION: DPM Config 1
  DpmDescwiptow_t DpmDescwiptow[PPCWK_COUNT];

  uint16_t       FweqTabweGfx      [NUM_GFXCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweVcwk     [NUM_VCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweDcwk     [NUM_DCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweSoccwk   [NUM_SOCCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweUcwk     [NUM_UCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];     // In MHz

  uint32_t       Paddingcwks[16];

  // SECTION: DPM Config 2
  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];       // in MHz
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];       // mV(Q2)

  // GFXCWK DPM
  uint16_t        GfxcwkFidwe;          // In MHz
  uint16_t        GfxcwkSwewWate;       // fow PWW babystepping???
  uint8_t         Padding567[4];
  uint16_t        GfxcwkDsMaxFweq;      // In MHz
  uint8_t         GfxcwkSouwce;         // 0 = PWW, 1 = AFWW
  uint8_t         Padding456;

  // GFXCWK Thewmaw DPM (fowmewwy 'Boost' Settings)
  uint16_t     EnabweTdpm;
  uint16_t     TdpmHighHystTempewatuwe;
  uint16_t     TdpmWowHystTempewatuwe;
  uint16_t     GfxcwkFweqHighTempWimit; // High wimit on GFXCWK when tempewatuwe is high, fow wewiabiwity.

  // SECTION: Fan Contwow
  uint16_t     FanStopTemp;          //Cewcius
  uint16_t     FanStawtTemp;         //Cewcius

  uint16_t     FanGainEdge;
  uint16_t     FanGainHotspot;
  uint16_t     FanGainVwGfx;
  uint16_t     FanGainVwSoc;
  uint16_t     FanGainVwMem;
  uint16_t     FanGainHbm;
  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint8_t      FanZewoWpmEnabwe;
  uint8_t      FanTachEdgePewWev;
  uint8_t      FanTempInputSewect;
  uint8_t      padding8_Fan;

  // The fowwowing awe AFC ovewwide pawametews. Weave at 0 to use FW defauwts.
  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;


  // SECTION: AVFS
  // Ovewwides
  uint8_t           OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_Avfs[2];

  QuadwaticInt_t    qAvfsGb[AVFS_VOWTAGE_COUNT];              // GHz->V Ovewwide of fused cuwve
  DwoopInt_t        dBtcGbGfxPww;       // GHz->V BtcGb
  DwoopInt_t        dBtcGbGfxAfww;        // GHz->V BtcGb
  DwoopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  WineawInt_t       qAgingGb[AVFS_VOWTAGE_COUNT];          // GHz->V

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_VOWTAGE_COUNT]; // GHz->V

  uint16_t          DcTow[AVFS_VOWTAGE_COUNT];            // mV Q2

  uint8_t           DcBtcEnabwed[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_GfxBtc[2];

  uint16_t          DcBtcMin[AVFS_VOWTAGE_COUNT];       // mV Q2
  uint16_t          DcBtcMax[AVFS_VOWTAGE_COUNT];       // mV Q2

  uint16_t          DcBtcGb[AVFS_VOWTAGE_COUNT];        // mV Q2

  // SECTION: XGMI
  uint8_t           XgmiDpmPstates[NUM_XGMI_WEVEWS]; // 2 DPM states, high and wow.  0-P0, 1-P1, 2-P2, 3-P3.
  uint8_t           XgmiDpmSpawe[2];

  // Tempewatuwe Dependent Vmin
  uint16_t     VDDGFX_TVmin;       //Cewcius
  uint16_t     VDDSOC_TVmin;       //Cewcius
  uint16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uint16_t     VDDGFX_Vmin_WoTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_WoTemp; // mV Q2

  uint16_t     VDDGFX_TVminHystewsis; // Cewcius
  uint16_t     VDDSOC_TVminHystewsis; // Cewcius


  // SECTION: Advanced Options
  uint32_t          DebugOvewwides;
  QuadwaticInt_t    WesewvedEquation0;
  QuadwaticInt_t    WesewvedEquation1;
  QuadwaticInt_t    WesewvedEquation2;
  QuadwaticInt_t    WesewvedEquation3;

  uint16_t     MinVowtageUwvGfx; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_GFX in UWV mode
  uint16_t     PaddingUwv;       // Padding

  // Totaw Powew configuwation, use defines fwom PwwConfig_e
  uint8_t      TotawPowewConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measuwed
  uint8_t      TotawPowewSpawe1;
  uint16_t     TotawPowewSpawe2;

  // APCC Settings
  uint16_t     PccThweshowdWow;
  uint16_t     PccThweshowdHigh;
  uint32_t     PaddingAPCC[6];  //FIXME pending SPEC

  // OOB Settings
  uint16_t BasePewfowmanceCawdPowew;
  uint16_t MaxPewfowmanceCawdPowew;
  uint16_t BasePewfowmanceFwequencyCap;   //In Mhz
  uint16_t MaxPewfowmanceFwequencyCap;    //In Mhz

  // Pew-Pawt Vmin
  uint16_t VDDGFX_VminWow;        // mv Q2
  uint16_t VDDGFX_TVminWow;       //Cewcius
  uint16_t VDDGFX_VminWow_HiTemp; // mv Q2
  uint16_t VDDGFX_VminWow_WoTemp; // mv Q2

  // SECTION: Wesewved
  uint32_t     Wesewved[7];

  // SECTION: BOAWD PAWAMETEWS

  // SVI2 Boawd Pawametews
  uint16_t     MaxVowtageStepGfx; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.
  uint16_t     MaxVowtageStepSoc; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.

  uint8_t      VddGfxVwMapping;     // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;     // Use VW_MAPPING* bitfiewds
  uint8_t      VddMemVwMapping;     // Use VW_MAPPING* bitfiewds
  uint8_t      BoawdVwMapping;      // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      ExtewnawSensowPwesent; // Extewnaw WDI connected to TMON (aka TEMP IN)
  uint8_t      Padding8_V[2];

  // Tewemetwy Settings
  uint16_t     GfxMaxCuwwent;   // in Amps
  int8_t       GfxOffset;       // in Amps
  uint8_t      Padding_TewemetwyGfx;

  uint16_t     SocMaxCuwwent;   // in Amps
  int8_t       SocOffset;       // in Amps
  uint8_t      Padding_TewemetwySoc;

  uint16_t     MemMaxCuwwent;   // in Amps
  int8_t       MemOffset;       // in Amps
  uint8_t      Padding_TewemetwyMem;

  uint16_t     BoawdMaxCuwwent;   // in Amps
  int8_t       BoawdOffset;       // in Amps
  uint8_t      Padding_TewemetwyBoawdInput;

  // GPIO Settings
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event
  uint8_t      VW1HotGpio;      // GPIO pin configuwed fow VW1 HOT event
  uint8_t      VW1HotPowawity;  // GPIO powawity fow VW1 HOT event

  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadEnabwed;   // on ow off
  uint8_t      UcwkSpweadPewcent;   // Q4.4
  uint16_t     UcwkSpweadFweq;      // kHz

  // FCWK Spwead Spectwum
  uint8_t      FcwkSpweadEnabwed;   // on ow off
  uint8_t      FcwkSpweadPewcent;   // Q4.4
  uint16_t     FcwkSpweadFweq;      // kHz

  // GFXCWK Fww Spwead Spectwum
  uint8_t      FwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      FwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     FwwGfxcwkSpweadFweq;      // kHz

  // I2C Contwowwew Stwuctuwe
  I2cContwowwewConfig_t  I2cContwowwews[NUM_I2C_CONTWOWWEWS];

  // Memowy section
  uint32_t     MemowyChannewEnabwed; // Fow DWAM use onwy, Max 32 channews enabwed bit mask.

  uint8_t      DwamBitWidth; // Fow DWAM use onwy.  See Dwam Bit width type defines
  uint8_t      PaddingMem[3];

  // Totaw boawd powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPadding;

  // SECTION: XGMI Twaining
  uint8_t           XgmiWinkSpeed   [NUM_XGMI_PSTATE_WEVEWS];
  uint8_t           XgmiWinkWidth   [NUM_XGMI_PSTATE_WEVEWS];

  uint16_t          XgmiFcwkFweq    [NUM_XGMI_PSTATE_WEVEWS];
  uint16_t          XgmiSocVowtage  [NUM_XGMI_PSTATE_WEVEWS];

  // GPIO pins fow I2C communications with 2nd contwowwew fow Input Tewemetwy Sequence
  uint8_t      GpioI2cScw;          // Sewiaw Cwock
  uint8_t      GpioI2cSda;          // Sewiaw Data
  uint16_t     GpioPadding;

  // Pwatfowm input tewemetwy vowtage coefficient
  uint32_t     BoawdVowtageCoeffA;    // decode by /1000
  uint32_t     BoawdVowtageCoeffB;    // decode by /1000

  uint32_t     BoawdWesewved[7];

  // Padding fow MMHUB - do not modify this
  uint32_t     MmHubPadding[8]; // SMU intewnaw use

} PPTabwe_t;
#pwagma pack(pop)

typedef stwuct {
  // Time constant pawametews fow cwock avewages in ms
  uint16_t     GfxcwkAvewageWpfTau;
  uint16_t     SoccwkAvewageWpfTau;
  uint16_t     UcwkAvewageWpfTau;
  uint16_t     GfxActivityWpfTau;
  uint16_t     UcwkActivityWpfTau;

  uint16_t     SocketPowewWpfTau;

  uint16_t     VcnCwkAvewageWpfTau;
  uint16_t     padding16;

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} DwivewSmuConfig_t;

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
  uint16_t AvewageSocketPowew    ;
  uint16_t TempewatuweEdge       ;
  uint16_t TempewatuweHotspot    ;
  uint16_t TempewatuweHBM        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwSoc      ;
  uint16_t TempewatuweVwMem      ;
  uint32_t ThwottwewStatus       ;

  uint16_t CuwwFanSpeed          ;
  uint16_t AvewageVcwkFwequency  ;
  uint16_t AvewageDcwkFwequency  ;
  uint16_t VcnActivityPewcentage ;
  uint32_t EnewgyAccumuwatow     ;

  uint32_t Padding[2];

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwics_t;


typedef stwuct {
  uint16_t avgPsmCount[75];
  uint16_t minPsmCount[75];
  fwoat    avgPsmVowtage[75];
  fwoat    minPsmVowtage[75];

  uint32_t MmHubPadding[8]; // SMU intewnaw use
} AvfsDebugTabwe_t;

typedef stwuct {
  uint8_t  AvfsVewsion;
  uint8_t  Padding;
  uint8_t  AvfsEn[AVFS_VOWTAGE_COUNT];

  uint8_t  OvewwideVFT[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];

  uint8_t  OvewwideTempewatuwes[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideVInvewsion[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideP2V[AVFS_VOWTAGE_COUNT];
  uint8_t  OvewwideP2VChawzFweq[AVFS_VOWTAGE_COUNT];

  int32_t VFT0_m1[AVFS_VOWTAGE_COUNT]; // Q8.24
  int32_t VFT0_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t VFT0_b[AVFS_VOWTAGE_COUNT];  // Q32

  int32_t VFT1_m1[AVFS_VOWTAGE_COUNT]; // Q8.16
  int32_t VFT1_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t VFT1_b[AVFS_VOWTAGE_COUNT];  // Q32

  int32_t VFT2_m1[AVFS_VOWTAGE_COUNT]; // Q8.16
  int32_t VFT2_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t VFT2_b[AVFS_VOWTAGE_COUNT];  // Q32

  int32_t AvfsGb0_m1[AVFS_VOWTAGE_COUNT]; // Q8.24
  int32_t AvfsGb0_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t AvfsGb0_b[AVFS_VOWTAGE_COUNT];  // Q32

  int32_t AcBtcGb_m1[AVFS_VOWTAGE_COUNT]; // Q8.24
  int32_t AcBtcGb_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t AcBtcGb_b[AVFS_VOWTAGE_COUNT];  // Q32

  uint32_t AvfsTempCowd[AVFS_VOWTAGE_COUNT];
  uint32_t AvfsTempMid[AVFS_VOWTAGE_COUNT];
  uint32_t AvfsTempHot[AVFS_VOWTAGE_COUNT];

  uint32_t VInvewsion[AVFS_VOWTAGE_COUNT]; // in mV with 2 fwactionaw bits


  int32_t P2V_m1[AVFS_VOWTAGE_COUNT]; // Q8.24
  int32_t P2V_m2[AVFS_VOWTAGE_COUNT]; // Q12.12
  int32_t P2V_b[AVFS_VOWTAGE_COUNT];  // Q32

  uint32_t P2VChawzFweq[AVFS_VOWTAGE_COUNT]; // in 10KHz units

  uint32_t EnabwedAvfsModuwes[3];

  uint32_t MmHubPadding[8]; // SMU intewnaw use
} AvfsFuseOvewwide_t;

typedef stwuct {
  uint8_t   Gfx_ActiveHystWimit;
  uint8_t   Gfx_IdweHystWimit;
  uint8_t   Gfx_FPS;
  uint8_t   Gfx_MinActiveFweqType;
  uint8_t   Gfx_BoostewFweqType;
  uint8_t   Gfx_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
  uint8_t   Gfx_UseWwcBusy;
  uint8_t   PaddingGfx[3];
  uint16_t  Gfx_MinActiveFweq;              // MHz
  uint16_t  Gfx_BoostewFweq;                // MHz
  uint16_t  Gfx_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Gfx_PD_Data_wimit_a;            // Q16
  uint32_t  Gfx_PD_Data_wimit_b;            // Q16
  uint32_t  Gfx_PD_Data_wimit_c;            // Q16
  uint32_t  Gfx_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Gfx_PD_Data_ewwow_wate_coeff;   // Q16

  uint8_t   Mem_ActiveHystWimit;
  uint8_t   Mem_IdweHystWimit;
  uint8_t   Mem_FPS;
  uint8_t   Mem_MinActiveFweqType;
  uint8_t   Mem_BoostewFweqType;
  uint8_t   Mem_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
  uint8_t   Mem_UseWwcBusy;
  uint8_t   PaddingMem[3];
  uint16_t  Mem_MinActiveFweq;              // MHz
  uint16_t  Mem_BoostewFweq;                // MHz
  uint16_t  Mem_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Mem_PD_Data_wimit_a;            // Q16
  uint32_t  Mem_PD_Data_wimit_b;            // Q16
  uint32_t  Mem_PD_Data_wimit_c;            // Q16
  uint32_t  Mem_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Mem_PD_Data_ewwow_wate_coeff;   // Q16

  uint32_t  Mem_UpThweshowd_Wimit;          // Q16
  uint8_t   Mem_UpHystWimit;
  uint8_t   Mem_DownHystWimit;
  uint16_t  Mem_Fps;

  uint32_t  BusyThweshowd;                  // Q16
  uint32_t  BusyHyst;
  uint32_t  IdweHyst;

  uint32_t  MmHubPadding[8]; // SMU intewnaw use
} DpmActivityMonitowCoeffInt_t;

// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam
#define TABWE_PPTABWE                 0
#define TABWE_AVFS                    1
#define TABWE_AVFS_PSM_DEBUG          2
#define TABWE_AVFS_FUSE_OVEWWIDE      3
#define TABWE_PMSTATUSWOG             4
#define TABWE_SMU_METWICS             5
#define TABWE_DWIVEW_SMU_CONFIG       6
#define TABWE_OVEWDWIVE               7
#define TABWE_WAFW_XGMI_TOPOWOGY      8
#define TABWE_I2C_COMMANDS            9
#define TABWE_ACTIVITY_MONITOW_COEFF  10
#define TABWE_COUNT                   11

// These defines awe used with the SMC_MSG_SetUcwkFastSwitch message.
typedef enum {
  DF_SWITCH_TYPE_FAST = 0,
  DF_SWITCH_TYPE_SWOW,
  DF_SWITCH_TYPE_COUNT,
} DF_SWITCH_TYPE_e;

typedef enum {
  DWAM_BIT_WIDTH_DISABWED = 0,
  DWAM_BIT_WIDTH_X_8,
  DWAM_BIT_WIDTH_X_16,
  DWAM_BIT_WIDTH_X_32,
  DWAM_BIT_WIDTH_X_64, // NOT USED.
  DWAM_BIT_WIDTH_X_128,
  DWAM_BIT_WIDTH_COUNT,
} DWAM_BIT_WIDTH_TYPE_e;

#define WEMOVE_FMAX_MAWGIN_BIT     0x0
#define WEMOVE_DCTOW_MAWGIN_BIT    0x1
#define WEMOVE_PWATFOWM_MAWGIN_BIT 0x2

#endif
