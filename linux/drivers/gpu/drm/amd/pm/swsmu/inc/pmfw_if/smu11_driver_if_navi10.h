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
#ifndef __SMU11_DWIVEW_IF_NAVI10_H__
#define __SMU11_DWIVEW_IF_NAVI10_H__

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if 
// any stwuctuwe is changed in this fiwe
// Be awawe of that the vewsion shouwd be updated in
// smu_v11_0.h, maybe wename is awso needed.
// #define SMU11_DWIVEW_IF_VEWSION 0x33

#define PPTABWE_NV10_SMU_VEWSION 8

#define NUM_GFXCWK_DPM_WEVEWS  16
#define NUM_SMNCWK_DPM_WEVEWS  2
#define NUM_SOCCWK_DPM_WEVEWS  8
#define NUM_MP0CWK_DPM_WEVEWS  2
#define NUM_DCWK_DPM_WEVEWS    8
#define NUM_VCWK_DPM_WEVEWS    8
#define NUM_DCEFCWK_DPM_WEVEWS 8
#define NUM_PHYCWK_DPM_WEVEWS  8
#define NUM_DISPCWK_DPM_WEVEWS 8
#define NUM_PIXCWK_DPM_WEVEWS  8
#define NUM_UCWK_DPM_WEVEWS    4 
#define NUM_MP1CWK_DPM_WEVEWS  2
#define NUM_WINK_WEVEWS        2


#define MAX_GFXCWK_DPM_WEVEW  (NUM_GFXCWK_DPM_WEVEWS  - 1)
#define MAX_SMNCWK_DPM_WEVEW  (NUM_SMNCWK_DPM_WEVEWS  - 1)
#define MAX_SOCCWK_DPM_WEVEW  (NUM_SOCCWK_DPM_WEVEWS  - 1)
#define MAX_MP0CWK_DPM_WEVEW  (NUM_MP0CWK_DPM_WEVEWS  - 1)
#define MAX_DCWK_DPM_WEVEW    (NUM_DCWK_DPM_WEVEWS    - 1)
#define MAX_VCWK_DPM_WEVEW    (NUM_VCWK_DPM_WEVEWS    - 1)
#define MAX_DCEFCWK_DPM_WEVEW (NUM_DCEFCWK_DPM_WEVEWS - 1)
#define MAX_DISPCWK_DPM_WEVEW (NUM_DISPCWK_DPM_WEVEWS - 1)
#define MAX_PIXCWK_DPM_WEVEW  (NUM_PIXCWK_DPM_WEVEWS  - 1)
#define MAX_PHYCWK_DPM_WEVEW  (NUM_PHYCWK_DPM_WEVEWS  - 1)
#define MAX_UCWK_DPM_WEVEW    (NUM_UCWK_DPM_WEVEWS    - 1)
#define MAX_MP1CWK_DPM_WEVEW  (NUM_MP1CWK_DPM_WEVEWS  - 1)
#define MAX_WINK_WEVEW        (NUM_WINK_WEVEWS        - 1)

//Gemini Modes
#define PPSMC_GeminiModeNone   0  //Singwe GPU boawd
#define PPSMC_GeminiModeMastew 1  //Mastew GPU on a Gemini boawd
#define PPSMC_GeminiModeSwave  2  //Swave GPU on a Gemini boawd

// Featuwe Contwow Defines
// DPM
#define FEATUWE_DPM_PWEFETCHEW_BIT      0
#define FEATUWE_DPM_GFXCWK_BIT          1
#define FEATUWE_DPM_GFX_PACE_BIT        2
#define FEATUWE_DPM_UCWK_BIT            3
#define FEATUWE_DPM_SOCCWK_BIT          4
#define FEATUWE_DPM_MP0CWK_BIT          5
#define FEATUWE_DPM_WINK_BIT            6
#define FEATUWE_DPM_DCEFCWK_BIT         7
#define FEATUWE_MEM_VDDCI_SCAWING_BIT   8 
#define FEATUWE_MEM_MVDD_SCAWING_BIT    9
                                        
//Idwe                                  
#define FEATUWE_DS_GFXCWK_BIT           10
#define FEATUWE_DS_SOCCWK_BIT           11
#define FEATUWE_DS_WCWK_BIT             12
#define FEATUWE_DS_DCEFCWK_BIT          13
#define FEATUWE_DS_UCWK_BIT             14
#define FEATUWE_GFX_UWV_BIT             15  
#define FEATUWE_FW_DSTATE_BIT           16 
#define FEATUWE_GFXOFF_BIT              17
#define FEATUWE_BACO_BIT                18
#define FEATUWE_VCN_PG_BIT              19  
#define FEATUWE_JPEG_PG_BIT             20
#define FEATUWE_USB_PG_BIT              21
#define FEATUWE_WSMU_SMN_CG_BIT         22
//Thwottwew/Wesponse                    
#define FEATUWE_PPT_BIT                 23
#define FEATUWE_TDC_BIT                 24
#define FEATUWE_GFX_EDC_BIT             25
#define FEATUWE_APCC_PWUS_BIT           26
#define FEATUWE_GTHW_BIT                27
#define FEATUWE_ACDC_BIT                28
#define FEATUWE_VW0HOT_BIT              29
#define FEATUWE_VW1HOT_BIT              30  
#define FEATUWE_FW_CTF_BIT              31
#define FEATUWE_FAN_CONTWOW_BIT         32
#define FEATUWE_THEWMAW_BIT             33
#define FEATUWE_GFX_DCS_BIT             34
//VF                                    
#define FEATUWE_WM_BIT                  35
#define FEATUWE_WED_DISPWAY_BIT         36
//Othew                                 
#define FEATUWE_GFX_SS_BIT              37
#define FEATUWE_OUT_OF_BAND_MONITOW_BIT 38
#define FEATUWE_TEMP_DEPENDENT_VMIN_BIT 39

#define FEATUWE_MMHUB_PG_BIT            40
#define FEATUWE_ATHUB_PG_BIT            41
#define FEATUWE_APCC_DFWW_BIT           42
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

// Debug Ovewwides Bitmask
#define DPM_OVEWWIDE_DISABWE_SOCCWK_PID             0x00000001
#define DPM_OVEWWIDE_DISABWE_UCWK_PID               0x00000002
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_VCN_SOCCWK   0x00000004
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_VCWK_SOCCWK   0x00000008
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_DCWK_SOCCWK   0x00000010
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_SOCCWK 0x00000020
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_UCWK   0x00000040
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_DCE_SOCCWK   0x00000080
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_MP0_SOCCWK   0x00000100
#define DPM_OVEWWIDE_DISABWE_DFWW_PWW_SHUTDOWN      0x00000200
#define DPM_OVEWWIDE_DISABWE_MEMOWY_TEMPEWATUWE_WEAD 0x00000400

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
#define THWOTTWEW_TEMP_VW_MEM0_BIT 5
#define THWOTTWEW_TEMP_VW_MEM1_BIT 6
#define THWOTTWEW_TEMP_VW_SOC_BIT  7
#define THWOTTWEW_TEMP_WIQUID0_BIT 8
#define THWOTTWEW_TEMP_WIQUID1_BIT 9
#define THWOTTWEW_TEMP_PWX_BIT     10
#define THWOTTWEW_TEMP_SKIN_BIT    11
#define THWOTTWEW_TDC_GFX_BIT      12
#define THWOTTWEW_TDC_SOC_BIT      13
#define THWOTTWEW_PPT0_BIT         14
#define THWOTTWEW_PPT1_BIT         15
#define THWOTTWEW_PPT2_BIT         16
#define THWOTTWEW_PPT3_BIT         17
#define THWOTTWEW_FIT_BIT          18
#define THWOTTWEW_PPM_BIT          19
#define THWOTTWEW_APCC_BIT         20

// FW DState Featuwes Contwow Bits
#define FW_DSTATE_SOC_UWV_BIT              0
#define FW_DSTATE_G6_HSW_BIT               1
#define FW_DSTATE_G6_PHY_VDDCI_OFF_BIT     2
#define FW_DSTATE_MP0_DS_BIT               3
#define FW_DSTATE_SMN_DS_BIT               4
#define FW_DSTATE_MP1_DS_BIT               5
#define FW_DSTATE_MP1_WHISPEW_MODE_BIT     6
#define FW_DSTATE_WIV_MIN_BIT              7
#define FW_DSTATE_SOC_PWW_PWWDN_BIT        8   

#define FW_DSTATE_SOC_UWV_MASK             (1 << FW_DSTATE_SOC_UWV_BIT          )
#define FW_DSTATE_G6_HSW_MASK              (1 << FW_DSTATE_G6_HSW_BIT           )
#define FW_DSTATE_G6_PHY_VDDCI_OFF_MASK    (1 << FW_DSTATE_G6_PHY_VDDCI_OFF_BIT )
#define FW_DSTATE_MP1_DS_MASK              (1 << FW_DSTATE_MP1_DS_BIT           )  
#define FW_DSTATE_MP0_DS_MASK              (1 << FW_DSTATE_MP0_DS_BIT           )   
#define FW_DSTATE_SMN_DS_MASK              (1 << FW_DSTATE_SMN_DS_BIT           )
#define FW_DSTATE_MP1_WHISPEW_MODE_MASK    (1 << FW_DSTATE_MP1_WHISPEW_MODE_BIT )
#define FW_DSTATE_WIV_MIN_MASK             (1 << FW_DSTATE_WIV_MIN_BIT          )
#define FW_DSTATE_SOC_PWW_PWWDN_MASK       (1 << FW_DSTATE_SOC_PWW_PWWDN_BIT    )

//I2C Intewface

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
  I2C_CONTWOWWEW_NAME_VW_VDDCI,
  I2C_CONTWOWWEW_NAME_VW_MVDD,
  I2C_CONTWOWWEW_NAME_WIQUID0,
  I2C_CONTWOWWEW_NAME_WIQUID1,  
  I2C_CONTWOWWEW_NAME_PWX,
  I2C_CONTWOWWEW_NAME_SPAWE,
  I2C_CONTWOWWEW_NAME_COUNT,  
} I2cContwowwewName_e;

typedef enum {
  I2C_CONTWOWWEW_THWOTTWEW_TYPE_NONE = 0,
  I2C_CONTWOWWEW_THWOTTWEW_VW_GFX,
  I2C_CONTWOWWEW_THWOTTWEW_VW_SOC,
  I2C_CONTWOWWEW_THWOTTWEW_VW_VDDCI,
  I2C_CONTWOWWEW_THWOTTWEW_VW_MVDD,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID0,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID1,  
  I2C_CONTWOWWEW_THWOTTWEW_PWX,
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
  GFXCWK_SOUWCE_DFWW, 
  GFXCWK_SOUWCE_COUNT, 
} GfxcwkSwc_e; 

//Onwy Cwks that have DPM descwiptows awe wisted hewe 
typedef enum {
  PPCWK_GFXCWK = 0,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_DCWK,
  PPCWK_VCWK,
  PPCWK_DCEFCWK,
  PPCWK_DISPCWK,
  PPCWK_PIXCWK,
  PPCWK_PHYCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  POWEW_SOUWCE_AC,
  POWEW_SOUWCE_DC,
  POWEW_SOUWCE_COUNT,
} POWEW_SOUWCE_e;

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
  UCWK_DIV_BY_1 = 0,
  UCWK_DIV_BY_2,
  UCWK_DIV_BY_4,
  UCWK_DIV_BY_8,
} UCWK_DIV_e;

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

typedef stwuct {
  uint8_t        VowtageMode;         // 0 - AVFS onwy, 1- min(AVFS,SS), 2-SS onwy
  uint8_t        SnapToDiscwete;      // 0 - Fine gwained DPM, 1 - Discwete DPM
  uint8_t        NumDiscweteWevews;   // Set to 2 (Fmin, Fmax) when using fine gwained DPM, othewwise set to # discwete wevews used
  uint8_t        Padding;         
  WineawInt_t    ConvewsionToAvfsCwk; // Twansfew function to AVFS Cwock (GHz->GHz)
  QuadwaticInt_t SsCuwve;             // Swow-swow cuwve (GHz->V)
} DpmDescwiptow_t;

typedef enum  {
  TEMP_EDGE,
  TEMP_HOTSPOT,
  TEMP_MEM,
  TEMP_VW_GFX,
  TEMP_VW_MEM0,
  TEMP_VW_MEM1,
  TEMP_VW_SOC,  
  TEMP_WIQUID0,
  TEMP_WIQUID1,  
  TEMP_PWX,
  TEMP_COUNT
} TEMP_e;

//Out of band monitow status defines
//see SPEC //gpu/doc/soc_awch/spec/featuwe/SMBUS/SMBUS.xwsx
#define POWEW_MANAGEW_CONTWOWWEW_NOT_WUNNING 0
#define POWEW_MANAGEW_CONTWOWWEW_WUNNING     1

#define POWEW_MANAGEW_CONTWOWWEW_BIT                             0
#define MAXIMUM_DPM_STATE_GFX_ENGINE_WESTWICTED_BIT              8
#define GPU_DIE_TEMPEWATUWE_THWOTTWING_BIT                       9
#define HBM_DIE_TEMPEWATUWE_THWOTTWING_BIT                       10
#define TGP_THWOTTWING_BIT                                       11
#define PCC_THWOTTWING_BIT                                       12
#define HBM_TEMPEWATUWE_EXCEEDING_TEMPEWATUWE_WIMIT_BIT          13
#define HBM_TEMPEWATUWE_EXCEEDING_MAX_MEMOWY_TEMPEWATUWE_BIT     14

#define POWEW_MANAGEW_CONTWOWWEW_MASK                            (1 << POWEW_MANAGEW_CONTWOWWEW_BIT                        ) 
#define MAXIMUM_DPM_STATE_GFX_ENGINE_WESTWICTED_MASK             (1 << MAXIMUM_DPM_STATE_GFX_ENGINE_WESTWICTED_BIT         )
#define GPU_DIE_TEMPEWATUWE_THWOTTWING_MASK                      (1 << GPU_DIE_TEMPEWATUWE_THWOTTWING_BIT                  ) 
#define HBM_DIE_TEMPEWATUWE_THWOTTWING_MASK                      (1 << HBM_DIE_TEMPEWATUWE_THWOTTWING_BIT                  )
#define TGP_THWOTTWING_MASK                                      (1 << TGP_THWOTTWING_BIT                                  )
#define PCC_THWOTTWING_MASK                                      (1 << PCC_THWOTTWING_BIT                                  )
#define HBM_TEMPEWATUWE_EXCEEDING_TEMPEWATUWE_WIMIT_MASK         (1 << HBM_TEMPEWATUWE_EXCEEDING_TEMPEWATUWE_WIMIT_BIT     )
#define HBM_TEMPEWATUWE_EXCEEDING_MAX_MEMOWY_TEMPEWATUWE_MASK    (1 << HBM_TEMPEWATUWE_EXCEEDING_MAX_MEMOWY_TEMPEWATUWE_BIT) 

//This stwuctuwe to be DMA to SMBUS Config wegistew space
typedef stwuct {
  uint8_t  MinowInfoVewsion;
  uint8_t  MajowInfoVewsion;
  uint8_t  TabweSize;
  uint8_t  Wesewved;

  uint8_t  Wesewved1;
  uint8_t  WevID;
  uint16_t DeviceID;

  uint16_t DieTempewatuweWimit;
  uint16_t FanTawgetTempewatuwe;

  uint16_t MemowyTempewatuweWimit;
  uint16_t MemowyTempewatuweWimit1;

  uint16_t TGP;
  uint16_t CawdPowew;

  uint32_t DieTempewatuweWegistewOffset;

  uint32_t Wesewved2;
  
  uint32_t Wesewved3;

  uint32_t Status;

  uint16_t DieTempewatuwe;
  uint16_t CuwwentMemowyTempewatuwe;

  uint16_t MemowyTempewatuwe;
  uint8_t MemowyHotspotPosition;
  uint8_t Wesewved4;

  uint32_t BoawdWevewEnewgyAccumuwatow;  
} OutOfBandMonitow_t;

#pwagma pack(push, 1)
typedef stwuct {
  uint32_t Vewsion;

  // SECTION: Featuwe Enabwement
  uint32_t FeatuwesToWun[2];

  // SECTION: Infwastwuctuwe Wimits
  uint16_t SocketPowewWimitAc[PPT_THWOTTWEW_COUNT];
  uint16_t SocketPowewWimitAcTau[PPT_THWOTTWEW_COUNT];
  uint16_t SocketPowewWimitDc[PPT_THWOTTWEW_COUNT];
  uint16_t SocketPowewWimitDcTau[PPT_THWOTTWEW_COUNT];  

  uint16_t TdcWimitSoc;             // Amps
  uint16_t TdcWimitSocTau;          // Time constant of WPF in ms
  uint16_t TdcWimitGfx;             // Amps
  uint16_t TdcWimitGfxTau;          // Time constant of WPF in ms
  
  uint16_t TedgeWimit;              // Cewcius
  uint16_t ThotspotWimit;           // Cewcius
  uint16_t TmemWimit;               // Cewcius
  uint16_t Tvw_gfxWimit;            // Cewcius
  uint16_t Tvw_mem0Wimit;           // Cewcius
  uint16_t Tvw_mem1Wimit;           // Cewcius  
  uint16_t Tvw_socWimit;            // Cewcius
  uint16_t Twiquid0Wimit;           // Cewcius
  uint16_t Twiquid1Wimit;           // Cewcius
  uint16_t TpwxWimit;               // Cewcius
  uint32_t FitWimit;                // Faiwuwes in time (faiwuwes pew miwwion pawts ovew the defined wifetime)

  uint16_t PpmPowewWimit;           // Switch this this powew wimit when tempewatuwe is above PpmTempThweshowd
  uint16_t PpmTempewatuweThweshowd;
  
  // SECTION: Thwottwew settings
  uint32_t ThwottwewContwowMask;   // See Thwottew masks defines

  // SECTION: FW DSTATE Settings  
  uint32_t FwDStateMask;           // See FW DState masks defines

  // SECTION: UWV Settings
  uint16_t  UwvVowtageOffsetSoc; // In mV(Q2)
  uint16_t  UwvVowtageOffsetGfx; // In mV(Q2)

  uint8_t   GceaWinkMgwIdweThweshowd;        //Set by SMU FW duwing enabwment of SOC_UWV. Contwows deway fow GFX SDP powt disconnection duwing idwe events
  uint8_t   paddingWwcUwvPawams[3];
  
  uint8_t  UwvSmncwkDid;     //DID fow UWV mode. 0 means CWK wiww not be modified in UWV.
  uint8_t  UwvMp1cwkDid;     //DID fow UWV mode. 0 means CWK wiww not be modified in UWV.
  uint8_t  UwvGfxcwkBypass;  // 1 to tuwn off/bypass Gfxcwk duwing UWV, 0 to weave Gfxcwk on duwing UWV
  uint8_t  Padding234;

  uint16_t     MinVowtageUwvGfx; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_GFX in UWV mode 
  uint16_t     MinVowtageUwvSoc; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_SOC in UWV mode


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
  uint16_t       FweqTabweDcefcwk  [NUM_DCEFCWK_DPM_WEVEWS ];     // In MHz
  uint16_t       FweqTabweDispcwk  [NUM_DISPCWK_DPM_WEVEWS ];     // In MHz
  uint16_t       FweqTabwePixcwk   [NUM_PIXCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabwePhycwk   [NUM_PHYCWK_DPM_WEVEWS  ];     // In MHz
  uint32_t       Paddingcwks[16];

  uint16_t       DcModeMaxFweq     [PPCWK_COUNT            ];     // In MHz
  uint16_t       Padding8_Cwks;
  
  uint8_t        FweqTabweUcwkDiv  [NUM_UCWK_DPM_WEVEWS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

  // SECTION: DPM Config 2
  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];       // in MHz
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];       // mV(Q2)
  uint16_t       MemVddciVowtage   [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  uint16_t       MemMvddVowtage    [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  // GFXCWK DPM
  uint16_t        GfxcwkFgfxoffEntwy;   // in Mhz
  uint16_t        GfxcwkFinit;          // in Mhz 
  uint16_t        GfxcwkFidwe;          // in MHz
  uint16_t        GfxcwkSwewWate;       // fow PWW babystepping???
  uint16_t        GfxcwkFopt;           // in Mhz
  uint8_t         Padding567[2]; 
  uint16_t        GfxcwkDsMaxFweq;      // in MHz
  uint8_t         GfxcwkSouwce;         // 0 = PWW, 1 = DFWW
  uint8_t         Padding456;

  // UCWK section
  uint8_t      WowestUcwkWesewvedFowUwv; // Set this to 1 if UCWK DPM0 is wesewved fow UWV-mode onwy
  uint8_t      paddingUcwk[3];
  
  uint8_t      MemowyType;          // 0-GDDW6, 1-HBM
  uint8_t      MemowyChannews;
  uint8_t      PaddingMem[2];

  // Wink DPM Settings
  uint8_t      PcieGenSpeed[NUM_WINK_WEVEWS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uint8_t      PcieWaneCount[NUM_WINK_WEVEWS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uint16_t     WcwkFweq[NUM_WINK_WEVEWS];              

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
  uint16_t     FanGainWiquid0;
  uint16_t     FanGainWiquid1;  
  uint16_t     FanGainVwGfx;
  uint16_t     FanGainVwSoc;
  uint16_t     FanGainVwMem0;
  uint16_t     FanGainVwMem1;  
  uint16_t     FanGainPwx;
  uint16_t     FanGainMem;
  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint8_t      FanTempInputSewect;
  uint8_t      FanPadding;
  uint8_t      FanZewoWpmEnabwe; 
  uint8_t      FanTachEdgePewWev;
  //uint8_t      padding8_Fan[2];
    
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
  DwoopInt_t        dBtcGbGfxPww;         // GHz->V BtcGb
  DwoopInt_t        dBtcGbGfxDfww;        // GHz->V BtcGb
  DwoopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  WineawInt_t       qAgingGb[AVFS_VOWTAGE_COUNT];          // GHz->V 

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_VOWTAGE_COUNT]; // GHz->V 

  uint16_t          DcTow[AVFS_VOWTAGE_COUNT];            // mV Q2

  uint8_t           DcBtcEnabwed[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_GfxBtc[2];

  uint16_t          DcBtcMin[AVFS_VOWTAGE_COUNT];       // mV Q2
  uint16_t          DcBtcMax[AVFS_VOWTAGE_COUNT];       // mV Q2

  // SECTION: Advanced Options
  uint32_t          DebugOvewwides;
  QuadwaticInt_t    WesewvedEquation0; 
  QuadwaticInt_t    WesewvedEquation1; 
  QuadwaticInt_t    WesewvedEquation2; 
  QuadwaticInt_t    WesewvedEquation3; 
  
  // Totaw Powew configuwation, use defines fwom PwwConfig_e
  uint8_t      TotawPowewConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measuwed
  uint8_t      TotawPowewSpawe1;  
  uint16_t     TotawPowewSpawe2;

  // APCC Settings
  uint16_t     PccThweshowdWow;
  uint16_t     PccThweshowdHigh;
  uint32_t     MGpuFanBoostWimitWpm;
  uint32_t     PaddingAPCC[5];

  // Tempewatuwe Dependent Vmin
  uint16_t     VDDGFX_TVmin;       //Cewcius
  uint16_t     VDDSOC_TVmin;       //Cewcius
  uint16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uint16_t     VDDGFX_Vmin_WoTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_WoTemp; // mV Q2
  
  uint16_t     VDDGFX_TVminHystewsis; // Cewcius
  uint16_t     VDDSOC_TVminHystewsis; // Cewcius

  // BTC Setting
  uint32_t     BtcConfig;
  
  uint16_t     SsFmin[10]; // PPtabwe vawue to function simiwaw to VFTFmin fow SS Cuwve; Size is PPCWK_COUNT wounded to neawest muwtipwe of 2
  uint16_t     DcBtcGb[AVFS_VOWTAGE_COUNT];

  // SECTION: Boawd Wesewved
  uint32_t     Wesewved[8];

  // SECTION: BOAWD PAWAMETEWS
  // I2C Contwow
  I2cContwowwewConfig_t  I2cContwowwews[NUM_I2C_CONTWOWWEWS];     

  // SVI2 Boawd Pawametews
  uint16_t     MaxVowtageStepGfx; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.
  uint16_t     MaxVowtageStepSoc; // In mV(Q2) Max vowtage step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue.
  
  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      ExtewnawSensowPwesent; // Extewnaw WDI connected to TMON (aka TEMP IN)
  uint8_t      Padding8_V; 

  // Tewemetwy Settings
  uint16_t     GfxMaxCuwwent;   // in Amps
  int8_t       GfxOffset;       // in Amps
  uint8_t      Padding_TewemetwyGfx;

  uint16_t     SocMaxCuwwent;   // in Amps
  int8_t       SocOffset;       // in Amps
  uint8_t      Padding_TewemetwySoc;

  uint16_t     Mem0MaxCuwwent;   // in Amps
  int8_t       Mem0Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem0;
  
  uint16_t     Mem1MaxCuwwent;   // in Amps
  int8_t       Mem1Offset;       // in Amps
  uint8_t      Padding_TewemetwyMem1;
  
  // GPIO Settings
  uint8_t      AcDcGpio;        // GPIO pin configuwed fow AC/DC switching
  uint8_t      AcDcPowawity;    // GPIO powawity fow AC/DC switching
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event

  uint8_t      VW1HotGpio;      // GPIO pin configuwed fow VW1 HOT event 
  uint8_t      VW1HotPowawity;  // GPIO powawity fow VW1 HOT event 
  uint8_t      GthwGpio;        // GPIO pin configuwed fow GTHW Event
  uint8_t      GthwPowawity;    // wepwace GPIO powawity fow GTHW

  // WED Dispway Settings
  uint8_t      WedPin0;         // GPIO numbew fow WedPin[0]
  uint8_t      WedPin1;         // GPIO numbew fow WedPin[1]
  uint8_t      WedPin2;         // GPIO numbew fow WedPin[2]
  uint8_t      padding8_4;
 
  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz
  
  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadEnabwed;   // on ow off
  uint8_t      UcwkSpweadPewcent;   // Q4.4
  uint16_t     UcwkSpweadFweq;      // kHz

  // SOCCWK Spwead Spectwum
  uint8_t      SocwkSpweadEnabwed;   // on ow off
  uint8_t      SoccwkSpweadPewcent;   // Q4.4
  uint16_t     SoccwkSpweadFweq;      // kHz

  // Totaw boawd powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPadding; 

  // Mvdd Svi2 Div Watio Setting
  uint32_t     MvddWatio; // This is used fow MVDD Vid wowkawound. It has 16 fwactionaw bits (Q16.16)

  uint8_t      WenesesWoadWineEnabwed;
  uint8_t      GfxWoadwineWesistance;
  uint8_t      SocWoadwineWesistance;
  uint8_t      Padding8_Woadwine;

  uint32_t     BoawdWesewved[8];

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

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} DwivewSmuConfig_t;

typedef stwuct {
  
  uint16_t      GfxcwkFmin;           // MHz
  uint16_t      GfxcwkFmax;           // MHz
  uint16_t      GfxcwkFweq1;          // MHz
  uint16_t      GfxcwkVowt1;          // mV (Q2)
  uint16_t      GfxcwkFweq2;          // MHz
  uint16_t      GfxcwkVowt2;          // mV (Q2)
  uint16_t      GfxcwkFweq3;          // MHz
  uint16_t      GfxcwkVowt3;          // mV (Q2)
  uint16_t      UcwkFmax;             // MHz
  int16_t       OvewDwivePct;         // %
  uint16_t      FanMaximumWpm;
  uint16_t      FanMinimumPwm;
  uint16_t      FanTawgetTempewatuwe; // Degwee Cewcius 
  uint16_t      FanMode;
  uint16_t      FanMaxPwm;
  uint16_t      FanMinPwm;
  uint16_t      FanMaxTemp; // Degwee Cewcius
  uint16_t      FanMinTemp; // Degwee Cewcius
  uint16_t      MaxOpTemp;            // Degwee Cewcius
  uint16_t      FanZewoWpmEnabwe;

  uint32_t     MmHubPadding[6]; // SMU intewnaw use

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
  uint16_t AvewageSocketPowew    ;
  uint16_t TempewatuweEdge       ;
  uint16_t TempewatuweHotspot    ;
  uint16_t TempewatuweMem        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwMem0     ;
  uint16_t TempewatuweVwMem1     ;  
  uint16_t TempewatuweVwSoc      ;  
  uint16_t TempewatuweWiquid0    ;
  uint16_t TempewatuweWiquid1    ;  
  uint16_t TempewatuwePwx        ;
  uint16_t Padding16             ;
  uint32_t ThwottwewStatus       ; 
 
  uint8_t  WinkDpmWevew;
  uint8_t  Padding8_2;
  uint16_t CuwwFanSpeed;

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwics_wegacy_t;

typedef stwuct {
  uint16_t CuwwCwock[PPCWK_COUNT];
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageSoccwkFwequency;
  uint16_t AvewageUcwkFwequencyPostDs;
  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint8_t  CuwwSocVowtageOffset  ;
  uint8_t  CuwwGfxVowtageOffset  ;
  uint8_t  CuwwMemVidOffset      ;
  uint8_t  Padding8              ;
  uint16_t AvewageSocketPowew    ;
  uint16_t TempewatuweEdge       ;
  uint16_t TempewatuweHotspot    ;
  uint16_t TempewatuweMem        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwMem0     ;
  uint16_t TempewatuweVwMem1     ;  
  uint16_t TempewatuweVwSoc      ;  
  uint16_t TempewatuweWiquid0    ;
  uint16_t TempewatuweWiquid1    ;  
  uint16_t TempewatuwePwx        ;
  uint16_t Padding16             ;
  uint32_t ThwottwewStatus       ; 
 
  uint8_t  WinkDpmWevew;
  uint8_t  Padding8_2;
  uint16_t CuwwFanSpeed;

  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageUcwkFwequencyPweDs;
  uint8_t  PcieWate;
  uint8_t  PcieWidth;
  uint8_t  Padding8_3[2];

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwics_t;

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
  uint16_t TempewatuweMem        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwMem0     ;
  uint16_t TempewatuweVwMem1     ;
  uint16_t TempewatuweVwSoc      ;
  uint16_t TempewatuweWiquid0    ;
  uint16_t TempewatuweWiquid1    ;
  uint16_t TempewatuwePwx        ;
  uint16_t Padding16             ;
  uint32_t ThwottwewStatus       ;

  uint8_t  WinkDpmWevew;
  uint8_t  Padding8_2;
  uint16_t CuwwFanSpeed;

  uint32_t EnewgyAccumuwatow;
  uint16_t AvewageVcwkFwequency  ;
  uint16_t AvewageDcwkFwequency  ;
  uint16_t VcnActivityPewcentage ;
  uint16_t padding16_2;

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwics_NV12_wegacy_t;

typedef stwuct {
  uint16_t CuwwCwock[PPCWK_COUNT];
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageSoccwkFwequency;
  uint16_t AvewageUcwkFwequencyPostDs;
  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint8_t  CuwwSocVowtageOffset  ;
  uint8_t  CuwwGfxVowtageOffset  ;
  uint8_t  CuwwMemVidOffset      ;
  uint8_t  Padding8              ;
  uint16_t AvewageSocketPowew    ;
  uint16_t TempewatuweEdge       ;
  uint16_t TempewatuweHotspot    ;
  uint16_t TempewatuweMem        ;
  uint16_t TempewatuweVwGfx      ;
  uint16_t TempewatuweVwMem0     ;
  uint16_t TempewatuweVwMem1     ;
  uint16_t TempewatuweVwSoc      ;
  uint16_t TempewatuweWiquid0    ;
  uint16_t TempewatuweWiquid1    ;
  uint16_t TempewatuwePwx        ;
  uint16_t Padding16             ;
  uint32_t ThwottwewStatus       ;

  uint8_t  WinkDpmWevew;
  uint8_t  Padding8_2;
  uint16_t CuwwFanSpeed;

  uint16_t AvewageVcwkFwequency  ;
  uint16_t AvewageDcwkFwequency  ;
  uint16_t VcnActivityPewcentage ;
  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageUcwkFwequencyPweDs;
  uint8_t  PcieWate;
  uint8_t  PcieWidth;

  uint32_t Padding32_1;
  uint64_t EnewgyAccumuwatow;

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwics_NV12_t;

typedef union SmuMetwics {
	SmuMetwics_wegacy_t		nv10_wegacy_metwics;
	SmuMetwics_t			nv10_metwics;
	SmuMetwics_NV12_wegacy_t	nv12_wegacy_metwics;
	SmuMetwics_NV12_t		nv12_metwics;
} SmuMetwics_NV1X_t;

typedef stwuct {
  uint16_t MinCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MaxCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MinUcwk;
  uint16_t MaxUcwk;
  
  uint8_t  WmSetting;
  uint8_t  Padding[3];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use  
} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WM_SOCCWK = 0,
  WM_DCEFCWK,
  WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} Watewmawks_t;

typedef stwuct {
  uint16_t avgPsmCount[28];
  uint16_t minPsmCount[28];
  fwoat    avgPsmVowtage[28];
  fwoat    minPsmVowtage[28];

  uint32_t     MmHubPadding[32]; // SMU intewnaw use
} AvfsDebugTabwe_t_NV14;

typedef stwuct {
  uint16_t avgPsmCount[36];
  uint16_t minPsmCount[36];
  fwoat    avgPsmVowtage[36]; 
  fwoat    minPsmVowtage[36];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} AvfsDebugTabwe_t_NV10;

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

  uint32_t EnabwedAvfsModuwes[2]; //NV10 - 36 AVFS moduwes

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} AvfsFuseOvewwide_t;

typedef stwuct {

  uint8_t   Gfx_ActiveHystWimit;
  uint8_t   Gfx_IdweHystWimit;
  uint8_t   Gfx_FPS;
  uint8_t   Gfx_MinActiveFweqType;
  uint8_t   Gfx_BoostewFweqType; 
  uint8_t   Gfx_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
  uint16_t  Gfx_MinActiveFweq;              // MHz
  uint16_t  Gfx_BoostewFweq;                // MHz
  uint16_t  Gfx_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Gfx_PD_Data_wimit_a;            // Q16
  uint32_t  Gfx_PD_Data_wimit_b;            // Q16
  uint32_t  Gfx_PD_Data_wimit_c;            // Q16
  uint32_t  Gfx_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Gfx_PD_Data_ewwow_wate_coeff;   // Q16
  
  uint8_t   Soc_ActiveHystWimit;
  uint8_t   Soc_IdweHystWimit;
  uint8_t   Soc_FPS;
  uint8_t   Soc_MinActiveFweqType;
  uint8_t   Soc_BoostewFweqType; 
  uint8_t   Soc_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
  uint16_t  Soc_MinActiveFweq;              // MHz
  uint16_t  Soc_BoostewFweq;                // MHz
  uint16_t  Soc_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Soc_PD_Data_wimit_a;            // Q16
  uint32_t  Soc_PD_Data_wimit_b;            // Q16
  uint32_t  Soc_PD_Data_wimit_c;            // Q16
  uint32_t  Soc_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Soc_PD_Data_ewwow_wate_coeff;   // Q16
  
  uint8_t   Mem_ActiveHystWimit;
  uint8_t   Mem_IdweHystWimit;
  uint8_t   Mem_FPS;
  uint8_t   Mem_MinActiveFweqType;
  uint8_t   Mem_BoostewFweqType;
  uint8_t   Mem_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
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

  uint32_t     MmHubPadding[8]; // SMU intewnaw use  

} DpmActivityMonitowCoeffInt_t;


// Wowkwoad bits
#define WOWKWOAD_PPWIB_DEFAUWT_BIT        0 
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 1 
#define WOWKWOAD_PPWIB_POWEW_SAVING_BIT   2 
#define WOWKWOAD_PPWIB_VIDEO_BIT          3 
#define WOWKWOAD_PPWIB_VW_BIT             4 
#define WOWKWOAD_PPWIB_COMPUTE_BIT        5 
#define WOWKWOAD_PPWIB_CUSTOM_BIT         6 
#define WOWKWOAD_PPWIB_COUNT              7 


// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam

// Tabwe twansfew status
#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF

// Tabwe types
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
#define TABWE_I2C_COMMANDS           10
#define TABWE_PACE                   11
#define TABWE_COUNT                  12

//WWC Pace Tabwe totaw numbew of wevews
#define WWC_PACE_TABWE_NUM_WEVEWS 16

typedef stwuct {
  fwoat FwopsPewByteTabwe[WWC_PACE_TABWE_NUM_WEVEWS];
  
  uint32_t     MmHubPadding[8]; // SMU intewnaw use  
} WwcPaceFwopsPewByteOvewwide_t;

// These defines awe used with the SMC_MSG_SetUcwkFastSwitch message.
#define UCWK_SWITCH_SWOW 0
#define UCWK_SWITCH_FAST 1
#endif
