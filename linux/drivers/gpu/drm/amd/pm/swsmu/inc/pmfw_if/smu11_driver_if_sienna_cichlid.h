/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __SMU11_DWIVEW_IF_SIENNA_CICHWID_H__
#define __SMU11_DWIVEW_IF_SIENNA_CICHWID_H__

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if 
// any stwuctuwe is changed in this fiwe
#define SMU11_DWIVEW_IF_VEWSION 0x40

#define PPTABWE_Sienna_Cichwid_SMU_VEWSION 7

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
#define NUM_DTBCWK_DPM_WEVEWS  8
#define NUM_UCWK_DPM_WEVEWS    4 
#define NUM_MP1CWK_DPM_WEVEWS  2
#define NUM_WINK_WEVEWS        2
#define NUM_FCWK_DPM_WEVEWS    8 
#define NUM_XGMI_WEVEWS        2
#define NUM_XGMI_PSTATE_WEVEWS 4
#define NUM_OD_FAN_MAX_POINTS  6

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
#define MAX_DTBCWK_DPM_WEVEW  (NUM_DTBCWK_DPM_WEVEWS  - 1)
#define MAX_UCWK_DPM_WEVEW    (NUM_UCWK_DPM_WEVEWS    - 1)
#define MAX_MP1CWK_DPM_WEVEW  (NUM_MP1CWK_DPM_WEVEWS  - 1)
#define MAX_WINK_WEVEW        (NUM_WINK_WEVEWS        - 1)
#define MAX_FCWK_DPM_WEVEW    (NUM_FCWK_DPM_WEVEWS    - 1)

//Gemini Modes
#define PPSMC_GeminiModeNone   0  //Singwe GPU boawd
#define PPSMC_GeminiModeMastew 1  //Mastew GPU on a Gemini boawd
#define PPSMC_GeminiModeSwave  2  //Swave GPU on a Gemini boawd

// Featuwe Contwow Defines
// DPM
#define FEATUWE_DPM_PWEFETCHEW_BIT      0
#define FEATUWE_DPM_GFXCWK_BIT          1
#define FEATUWE_DPM_GFX_GPO_BIT         2
#define FEATUWE_DPM_UCWK_BIT            3
#define FEATUWE_DPM_FCWK_BIT            4
#define FEATUWE_DPM_SOCCWK_BIT          5
#define FEATUWE_DPM_MP0CWK_BIT          6
#define FEATUWE_DPM_WINK_BIT            7
#define FEATUWE_DPM_DCEFCWK_BIT         8
#define FEATUWE_DPM_XGMI_BIT            9
#define FEATUWE_MEM_VDDCI_SCAWING_BIT   10 
#define FEATUWE_MEM_MVDD_SCAWING_BIT    11
                                        
//Idwe                                  
#define FEATUWE_DS_GFXCWK_BIT           12
#define FEATUWE_DS_SOCCWK_BIT           13
#define FEATUWE_DS_FCWK_BIT             14
#define FEATUWE_DS_WCWK_BIT             15
#define FEATUWE_DS_DCEFCWK_BIT          16
#define FEATUWE_DS_UCWK_BIT             17
#define FEATUWE_GFX_UWV_BIT             18  
#define FEATUWE_FW_DSTATE_BIT           19 
#define FEATUWE_GFXOFF_BIT              20
#define FEATUWE_BACO_BIT                21
#define FEATUWE_MM_DPM_PG_BIT           22  
#define FEATUWE_SPAWE_23_BIT            23
//Thwottwew/Wesponse                    
#define FEATUWE_PPT_BIT                 24
#define FEATUWE_TDC_BIT                 25
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
#define FEATUWE_DF_SUPEWV_BIT           43
#define FEATUWE_WSMU_SMN_CG_BIT         44
#define FEATUWE_DF_CSTATE_BIT           45
#define FEATUWE_2_STEP_PSTATE_BIT       46
#define FEATUWE_SMNCWK_DPM_BIT          47
#define FEATUWE_PEWWINK_GMIDOWN_BIT     48
#define FEATUWE_GFX_EDC_BIT             49
#define FEATUWE_GFX_PEW_PAWT_VMIN_BIT   50
#define FEATUWE_SMAWT_SHIFT_BIT         51
#define FEATUWE_APT_BIT                 52
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

//Fow use with featuwe contwow messages
typedef enum {
  FEATUWE_PWW_AWW,
  FEATUWE_PWW_S5,
  FEATUWE_PWW_BACO,
  FEATUWE_PWW_SOC,
  FEATUWE_PWW_GFX,
  FEATUWE_PWW_DOMAIN_COUNT,
} FEATUWE_PWW_DOMAIN_e;


// Debug Ovewwides Bitmask
#define DPM_OVEWWIDE_DISABWE_FCWK_PID                0x00000001
#define DPM_OVEWWIDE_DISABWE_UCWK_PID                0x00000002
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_VCN_FCWK      0x00000004
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_VCWK_FCWK      0x00000008
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_DCWK_FCWK      0x00000010
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_SOCCWK  0x00000020
#define DPM_OVEWWIDE_ENABWE_FWEQ_WINK_GFXCWK_UCWK    0x00000040
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_DCE_FCWK      0x00000080
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_MP0_SOCCWK    0x00000100
#define DPM_OVEWWIDE_DISABWE_DFWW_PWW_SHUTDOWN       0x00000200
#define DPM_OVEWWIDE_DISABWE_MEMOWY_TEMPEWATUWE_WEAD 0x00000400
#define DPM_OVEWWIDE_DISABWE_VOWT_WINK_VCN_DCEFCWK   0x00000800
#define DPM_OVEWWIDE_DISABWE_FAST_FCWK_TIMEW         0x00001000
#define DPM_OVEWWIDE_DISABWE_VCN_PG                  0x00002000
#define DPM_OVEWWIDE_DISABWE_FMAX_VMAX               0x00004000
#define DPM_OVEWWIDE_ENABWE_eGPU_USB_WA              0x00008000

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
#define THWOTTWEW_TDC_GFX_BIT      11
#define THWOTTWEW_TDC_SOC_BIT      12
#define THWOTTWEW_PPT0_BIT         13
#define THWOTTWEW_PPT1_BIT         14
#define THWOTTWEW_PPT2_BIT         15
#define THWOTTWEW_PPT3_BIT         16
#define THWOTTWEW_FIT_BIT          17
#define THWOTTWEW_PPM_BIT          18
#define THWOTTWEW_APCC_BIT         19
#define THWOTTWEW_COUNT            20

// FW DState Featuwes Contwow Bits
// FW DState Featuwes Contwow Bits
#define FW_DSTATE_SOC_UWV_BIT               0
#define FW_DSTATE_G6_HSW_BIT                1
#define FW_DSTATE_G6_PHY_VDDCI_OFF_BIT      2
#define FW_DSTATE_MP0_DS_BIT                3
#define FW_DSTATE_SMN_DS_BIT                4
#define FW_DSTATE_MP1_DS_BIT                5
#define FW_DSTATE_MP1_WHISPEW_MODE_BIT      6
#define FW_DSTATE_SOC_WIV_MIN_BIT           7
#define FW_DSTATE_SOC_PWW_PWWDN_BIT         8
#define FW_DSTATE_MEM_PWW_PWWDN_BIT         9   
#define FW_DSTATE_OPTIMIZE_MAWW_WEFWESH_BIT 10
#define FW_DSTATE_MEM_PSI_BIT               11
#define FW_DSTATE_HSW_NON_STWOBE_BIT        12
#define FW_DSTATE_MP0_ENTEW_WFI_BIT         13

#define FW_DSTATE_SOC_UWV_MASK                    (1 << FW_DSTATE_SOC_UWV_BIT          )
#define FW_DSTATE_G6_HSW_MASK                     (1 << FW_DSTATE_G6_HSW_BIT           )
#define FW_DSTATE_G6_PHY_VDDCI_OFF_MASK           (1 << FW_DSTATE_G6_PHY_VDDCI_OFF_BIT )
#define FW_DSTATE_MP1_DS_MASK                     (1 << FW_DSTATE_MP1_DS_BIT           )  
#define FW_DSTATE_MP0_DS_MASK                     (1 << FW_DSTATE_MP0_DS_BIT           )   
#define FW_DSTATE_SMN_DS_MASK                     (1 << FW_DSTATE_SMN_DS_BIT           )
#define FW_DSTATE_MP1_WHISPEW_MODE_MASK           (1 << FW_DSTATE_MP1_WHISPEW_MODE_BIT )
#define FW_DSTATE_SOC_WIV_MIN_MASK                (1 << FW_DSTATE_SOC_WIV_MIN_BIT      )
#define FW_DSTATE_SOC_PWW_PWWDN_MASK              (1 << FW_DSTATE_SOC_PWW_PWWDN_BIT    )
#define FW_DSTATE_MEM_PWW_PWWDN_MASK              (1 << FW_DSTATE_MEM_PWW_PWWDN_BIT    )
#define FW_DSTATE_OPTIMIZE_MAWW_WEFWESH_MASK      (1 << FW_DSTATE_OPTIMIZE_MAWW_WEFWESH_BIT    )
#define FW_DSTATE_MEM_PSI_MASK                    (1 << FW_DSTATE_MEM_PSI_BIT    )
#define FW_DSTATE_HSW_NON_STWOBE_MASK             (1 << FW_DSTATE_HSW_NON_STWOBE_BIT    )
#define FW_DSTATE_MP0_ENTEW_WFI_MASK              (1 << FW_DSTATE_MP0_ENTEW_WFI_BIT    )

// GFX GPO Featuwe Contains PACE and DEM sub featuwes
#define GFX_GPO_PACE_BIT                   0
#define GFX_GPO_DEM_BIT                    1

#define GFX_GPO_PACE_MASK                  (1 << GFX_GPO_PACE_BIT)
#define GFX_GPO_DEM_MASK                   (1 << GFX_GPO_DEM_BIT )

#define GPO_UPDATE_WEQ_UCWKDPM_MASK  0x1
#define GPO_UPDATE_WEQ_FCWKDPM_MASK  0x2
#define GPO_UPDATE_WEQ_MAWWHIT_MASK  0x4


//WED Dispway Mask & Contwow Bits
#define WED_DISPWAY_GFX_DPM_BIT            0
#define WED_DISPWAY_PCIE_BIT               1
#define WED_DISPWAY_EWWOW_BIT              2

//WWC Pace Tabwe totaw numbew of wevews
#define WWC_PACE_TABWE_NUM_WEVEWS          16
#define SIENNA_CICHWID_UMC_CHANNEW_NUM     16

typedef stwuct {
  uint64_t mca_umc_status;
  uint64_t mca_umc_addw;

  uint16_t ce_count_wo_chip;
  uint16_t ce_count_hi_chip;

  uint32_t eccPadding;
} EccInfo_t;

typedef stwuct {
  EccInfo_t  EccInfo[SIENNA_CICHWID_UMC_CHANNEW_NUM];
} EccInfoTabwe_t;

typedef enum {
  DWAM_BIT_WIDTH_DISABWED = 0,
  DWAM_BIT_WIDTH_X_8,
  DWAM_BIT_WIDTH_X_16,
  DWAM_BIT_WIDTH_X_32,
  DWAM_BIT_WIDTH_X_64, // NOT USED.
  DWAM_BIT_WIDTH_X_128,
  DWAM_BIT_WIDTH_COUNT,
} DWAM_BIT_WIDTH_TYPE_e;

//I2C Intewface
#define NUM_I2C_CONTWOWWEWS                16

#define I2C_CONTWOWWEW_ENABWED             1
#define I2C_CONTWOWWEW_DISABWED            0

#define MAX_SW_I2C_COMMANDS                24


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
  I2C_CONTWOWWEW_NAME_OTHEW,
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
  I2C_CONTWOWWEW_THWOTTWEW_INA3221,
  I2C_CONTWOWWEW_THWOTTWEW_COUNT,  
} I2cContwowwewThwottwew_e;

typedef enum {
  I2C_CONTWOWWEW_PWOTOCOW_VW_XPDE132G5,
  I2C_CONTWOWWEW_PWOTOCOW_VW_IW35217,
  I2C_CONTWOWWEW_PWOTOCOW_TMP_TMP102A,
  I2C_CONTWOWWEW_PWOTOCOW_INA3221,
  I2C_CONTWOWWEW_PWOTOCOW_COUNT,  
} I2cContwowwewPwotocow_e;

typedef stwuct {
  uint8_t   Enabwed;
  uint8_t   Speed;
  uint8_t   SwaveAddwess;  
  uint8_t   ContwowwewPowt;
  uint8_t   ContwowwewName;
  uint8_t   ThewmawThwottew;
  uint8_t   I2cPwotocow;
  uint8_t   PaddingConfig;  
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

typedef enum {
  FAN_MODE_AUTO = 0,
  FAN_MODE_MANUAW_WINEAW,
} FanMode_e;

#define CMDCONFIG_STOP_BIT             0
#define CMDCONFIG_WESTAWT_BIT          1
#define CMDCONFIG_WEADWWITE_BIT        2 //bit shouwd be 0 fow wead, 1 fow wwite

#define CMDCONFIG_STOP_MASK           (1 << CMDCONFIG_STOP_BIT)
#define CMDCONFIG_WESTAWT_MASK        (1 << CMDCONFIG_WESTAWT_BIT)
#define CMDCONFIG_WEADWWITE_MASK      (1 << CMDCONFIG_WEADWWITE_BIT)

typedef stwuct {
  uint8_t WeadWwiteData;  //Wetuwn data fow wead. Data to send fow wwite
  uint8_t CmdConfig; //Incwudes whethew associated command shouwd have a stop ow westawt command, and is a wead ow wwite
} SwI2cCmd_t; //SW I2C Command Tabwe

typedef stwuct {
  uint8_t     I2CcontwowwewPowt; //CKSVII2C0(0) ow //CKSVII2C1(1)
  uint8_t     I2CSpeed;          //Use I2cSpeed_e to indicate speed to sewect
  uint8_t     SwaveAddwess;      //Swave addwess of device
  uint8_t     NumCmds;           //Numbew of commands

  SwI2cCmd_t  SwI2cCmds[MAX_SW_I2C_COMMANDS];
} SwI2cWequest_t; // SW I2C Wequest Tabwe

typedef stwuct {
  SwI2cWequest_t SwI2cWequest;

  uint32_t Spawe[8];
  uint32_t MmHubPadding[8]; // SMU intewnaw use
} SwI2cWequestExtewnaw_t;

//D3HOT sequences
typedef enum {
  BACO_SEQUENCE,
  MSW_SEQUENCE,
  BAMACO_SEQUENCE,
  UWPS_SEQUENCE,
  D3HOT_SEQUENCE_COUNT,
} D3HOTSequence_e;

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
  uint32_t a;  // stowe in fixed point, [31:20] signed integew, [19:0] fwactionaw bits
  uint32_t b;  // stowe in fixed point, [31:20] signed integew, [19:0] fwactionaw bits
  uint32_t c;  // stowe in fixed point, [31:20] signed integew, [19:0] fwactionaw bits
} QuadwaticFixedPoint_t;

typedef stwuct {            
  uint32_t m;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t b;  // stowe in IEEE fwoat fowmat in this vawiabwe
} WineawInt_t;

typedef stwuct {            
  uint32_t a;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t b;  // stowe in IEEE fwoat fowmat in this vawiabwe
  uint32_t c;  // stowe in IEEE fwoat fowmat in this vawiabwe
} DwoopInt_t;

//Piecewise wineaw dwoop modew, Sienna_Cichwid cuwwentwy used onwy fow GFX DFWW 
#define NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS 5
typedef enum {
  PIECEWISE_WINEAW_FUSED_MODEW = 0,
  PIECEWISE_WINEAW_PP_MODEW,
  QUADWATIC_PP_MODEW,
  PEWPAWT_PIECEWISE_WINEAW_PP_MODEW,  
} DfwwDwoopModewSewect_e;

typedef stwuct {
  uint32_t Fset[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS];    //in GHz, stowe in IEEE fwoat fowmat
  uint32_t Vdwoop[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS];  //in V  , stowe in IEEE fwoat fowmat
}PiecewiseWineawDwoopInt_t;

typedef enum {
  GFXCWK_SOUWCE_PWW = 0, 
  GFXCWK_SOUWCE_DFWW, 
  GFXCWK_SOUWCE_COUNT, 
} GFXCWK_SOUWCE_e; 

//Onwy Cwks that have DPM descwiptows awe wisted hewe 
typedef enum {
  PPCWK_GFXCWK = 0,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_FCWK,  
  PPCWK_DCWK_0,
  PPCWK_VCWK_0,
  PPCWK_DCWK_1,
  PPCWK_VCWK_1,
  PPCWK_DCEFCWK,
  PPCWK_DISPCWK,
  PPCWK_PIXCWK,
  PPCWK_PHYCWK,
  PPCWK_DTBCWK,
  PPCWK_COUNT,
} PPCWK_e;

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
  XGMI_WINK_WIDTH_1 = 0,  // x1
  XGMI_WINK_WIDTH_2,  // x2
  XGMI_WINK_WIDTH_4,  // x4
  XGMI_WINK_WIDTH_8,  // x8
  XGMI_WINK_WIDTH_9,  // x9
  XGMI_WINK_WIDTH_16, // x16
  XGMI_WINK_WIDTH_COUNT
} XGMI_WINK_WIDTH_e;

typedef stwuct {
  uint8_t        VowtageMode;         // 0 - AVFS onwy, 1- min(AVFS,SS), 2-SS onwy
  uint8_t        SnapToDiscwete;      // 0 - Fine gwained DPM, 1 - Discwete DPM
  uint8_t        NumDiscweteWevews;   // Set to 2 (Fmin, Fmax) when using fine gwained DPM, othewwise set to # discwete wevews used
  uint8_t        Padding;         
  WineawInt_t    ConvewsionToAvfsCwk; // Twansfew function to AVFS Cwock (GHz->GHz)
  QuadwaticInt_t SsCuwve;             // Swow-swow cuwve (GHz->V)
  uint16_t       SsFmin;              // Fmin fow SS cuwve. If SS cuwve is sewected, wiww use V@SSFmin fow F <= Fmin
  uint16_t       Padding16;    
} DpmDescwiptow_t;

typedef enum  {
  PPT_THWOTTWEW_PPT0,
  PPT_THWOTTWEW_PPT1,
  PPT_THWOTTWEW_PPT2,
  PPT_THWOTTWEW_PPT3,       
  PPT_THWOTTWEW_COUNT
} PPT_THWOTTWEW_e;

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
  TEMP_COUNT,
} TEMP_e;

typedef enum {
  TDC_THWOTTWEW_GFX,
  TDC_THWOTTWEW_SOC,
  TDC_THWOTTWEW_COUNT
} TDC_THWOTTWEW_e;

typedef enum {
  CUSTOMEW_VAWIANT_WOW,
  CUSTOMEW_VAWIANT_FAWCON,
  CUSTOMEW_VAWIANT_COUNT,
} CUSTOMEW_VAWIANT_e;
	 
// Used fow 2-step UCWK DPM change wowkawound
typedef stwuct {
  uint16_t Fmin;
  uint16_t Fmax;
} UcwkDpmChangeWange_t;

#pwagma pack(push, 1)
typedef stwuct {
  // MAJOW SECTION: SKU PAWAMETEWS

  uint32_t Vewsion;

  // SECTION: Featuwe Enabwement
  uint32_t FeatuwesToWun[NUM_FEATUWES / 32];

  // SECTION: Infwastwuctuwe Wimits
  uint16_t SocketPowewWimitAc[PPT_THWOTTWEW_COUNT]; // Watts
  uint16_t SocketPowewWimitAcTau[PPT_THWOTTWEW_COUNT]; // Time constant of WPF in ms
  uint16_t SocketPowewWimitDc[PPT_THWOTTWEW_COUNT];  // Watts
  uint16_t SocketPowewWimitDcTau[PPT_THWOTTWEW_COUNT];  // Time constant of WPF in ms

  uint16_t TdcWimit[TDC_THWOTTWEW_COUNT];             // Amps
  uint16_t TdcWimitTau[TDC_THWOTTWEW_COUNT];          // Time constant of WPF in ms

  uint16_t TempewatuweWimit[TEMP_COUNT]; // Cewcius
  
  uint32_t FitWimit;                // Faiwuwes in time (faiwuwes pew miwwion pawts ovew the defined wifetime)

  // SECTION: Powew Configuwation
  uint8_t      TotawPowewConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measuwed. Use defines fwom PwwConfig_e
  uint8_t      TotawPowewPadding[3];  

  // SECTION: APCC Settings
  uint32_t     ApccPwusWesidencyWimit;

  //SECTION: SMNCWK DPM
  uint16_t       SmncwkDpmFweq        [NUM_SMNCWK_DPM_WEVEWS];       // in MHz
  uint16_t       SmncwkDpmVowtage     [NUM_SMNCWK_DPM_WEVEWS];       // mV(Q2)

  uint32_t       PaddingAPCC;
  uint16_t       PewPawtDwoopVsetGfxDfww[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS];  //In mV(Q2)
  uint16_t       PaddingPewPawtDwoop;

  // SECTION: Thwottwew settings
  uint32_t ThwottwewContwowMask;   // See Thwottew masks defines

  // SECTION: FW DSTATE Settings  
  uint32_t FwDStateMask;           // See FW DState masks defines

  // SECTION: UWV Settings
  uint16_t  UwvVowtageOffsetSoc; // In mV(Q2)
  uint16_t  UwvVowtageOffsetGfx; // In mV(Q2)

  uint16_t     MinVowtageUwvGfx; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_GFX in UWV mode 
  uint16_t     MinVowtageUwvSoc; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_SOC in UWV mode

  uint16_t     SocWIVmin;        // In mV(Q2)  Wong Idwe Vmin (deep UWV), fow VDD_SOC
  uint16_t     PaddingWIVmin;

  uint8_t   GceaWinkMgwIdweThweshowd;        //Set by SMU FW duwing enabwment of GFXOFF. Contwows deway fow GFX SDP powt disconnection duwing idwe events
  uint8_t   paddingWwcUwvPawams[3];

  // SECTION: Vowtage Contwow Pawametews
  uint16_t     MinVowtageGfx;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_GFX
  uint16_t     MinVowtageSoc;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_SOC
  uint16_t     MaxVowtageGfx;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_GFX
  uint16_t     MaxVowtageSoc;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_SOC

  uint16_t     WoadWineWesistanceGfx;   // In mOhms with 8 fwactionaw bits
  uint16_t     WoadWineWesistanceSoc;   // In mOhms with 8 fwactionaw bits

  // SECTION: Tempewatuwe Dependent Vmin
  uint16_t     VDDGFX_TVmin;       //Cewcius
  uint16_t     VDDSOC_TVmin;       //Cewcius
  uint16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uint16_t     VDDGFX_Vmin_WoTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_WoTemp; // mV Q2
  
  uint16_t     VDDGFX_TVminHystewsis; // Cewcius
  uint16_t     VDDSOC_TVminHystewsis; // Cewcius

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
  uint16_t       FweqTabweDtbcwk   [NUM_DTBCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];     // In MHz
  uint32_t       Paddingcwks;

  DwoopInt_t     PewPawtDwoopModewGfxDfww[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS]; //GHz ->Vstowe in IEEE fwoat fowmat

  uint32_t       DcModeMaxFweq     [PPCWK_COUNT            ];     // In MHz
  
  uint8_t        FweqTabweUcwkDiv  [NUM_UCWK_DPM_WEVEWS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8
  
  // Used fow MAWW pewfowmance boost
  uint16_t       FcwkBoostFweq;                                   // In Mhz
  uint16_t       FcwkPawamPadding;

  // SECTION: DPM Config 2
  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];       // in MHz
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];       // mV(Q2)
  uint16_t       MemVddciVowtage   [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  uint16_t       MemMvddVowtage    [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  // GFXCWK DPM
  uint16_t        GfxcwkFgfxoffEntwy;   // in Mhz
  uint16_t        GfxcwkFinit;          // in Mhz 
  uint16_t        GfxcwkFidwe;          // in MHz 
  uint8_t         GfxcwkSouwce;         // 0 = PWW, 1 = DFWW
  uint8_t         GfxcwkPadding;

  // GFX GPO 
  uint8_t         GfxGpoSubFeatuweMask; // bit 0 = PACE, bit 1 = DEM
  uint8_t         GfxGpoEnabwedWowkPowicyMask; //Any powicy that GPO can be enabwed
  uint8_t         GfxGpoDisabwedWowkPowicyMask; //Any powicy that GPO can be disabwed
  uint8_t         GfxGpoPadding[1];
  uint32_t        GfxGpoVotingAwwow;    //Fow indicating which featuwe changes shouwd wesuwt in a GPO tabwe wecawcuwation

  uint32_t        GfxGpoPadding32[4];  

  uint16_t        GfxDcsFopt;           // Optimaw GFXCWK fow DCS in Mhz
  uint16_t        GfxDcsFcwkFopt;       // Optimaw FCWK fow DCS in Mhz
  uint16_t        GfxDcsUcwkFopt;       // Optimaw UCWK fow DCS in Mhz
  
  uint16_t        DcsGfxOffVowtage;     //Vowtage in mV(Q2) appwied to VDDGFX when entewing DCS GFXOFF phase  

  uint16_t        DcsMinGfxOffTime;     //Minimum amount of time PMFW shuts GFX OFF as pawt of GFX DCS phase
  uint16_t        DcsMaxGfxOffTime;      //Maximum amount of time PMFW can shut GFX OFF as pawt of GFX DCS phase at a stwetch.

  uint32_t        DcsMinCweditAccum;    //Min amount of positive cwedit accumuwation befowe waking GFX up as pawt of DCS.

  uint16_t        DcsExitHystewesis;    //The min amount of time powew cwedit accumuwatow shouwd have a vawue > 0 befowe SMU exits the DCS thwottwing phase. 
  uint16_t        DcsTimeout;           //This is the amount of time SMU FW waits fow WWC to put GFX into GFXOFF befowe wevewting to the fawwback mechanism of thwottwing GFXCWK to Fmin.

  uint32_t        DcsPawamPadding[5];

  uint16_t        FwopsPewByteTabwe[WWC_PACE_TABWE_NUM_WEVEWS]; // Q8.8

  // UCWK section
  uint8_t      WowestUcwkWesewvedFowUwv; // Set this to 1 if UCWK DPM0 is wesewved fow UWV-mode onwy
  uint8_t      PaddingMem[3];
  
  uint8_t      UcwkDpmPstates     [NUM_UCWK_DPM_WEVEWS];     // 4 DPM states, 0-P0, 1-P1, 2-P2, 3-P3.
  
  // Used fow 2-Step UCWK change wowkawound
  UcwkDpmChangeWange_t UcwkDpmSwcFweqWange;  // In Mhz
  UcwkDpmChangeWange_t UcwkDpmTawgFweqWange; // In Mhz
  uint16_t UcwkDpmMidstepFweq;               // In Mhz
  uint16_t UcwkMidstepPadding;

  // Wink DPM Settings
  uint8_t      PcieGenSpeed[NUM_WINK_WEVEWS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uint8_t      PcieWaneCount[NUM_WINK_WEVEWS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uint16_t     WcwkFweq[NUM_WINK_WEVEWS];              
 
  // SECTION: Fan Contwow
  uint16_t     FanStopTemp;          //Cewcius
  uint16_t     FanStawtTemp;         //Cewcius

  uint16_t     FanGain[TEMP_COUNT];

  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     MGpuFanBoostWimitWpm;  
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint16_t     FanPadding16;
  uint8_t      FanTempInputSewect;
  uint8_t      FanPadding;
  uint8_t      FanZewoWpmEnabwe; 
  uint8_t      FanTachEdgePewWev;
    
  // The fowwowing awe AFC ovewwide pawametews. Weave at 0 to use FW defauwts.
  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;

  // SECTION: AVFS 
  // Ovewwides
  uint8_t           OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];
  uint8_t           dBtcGbGfxDfwwModewSewect;  //0 -> fused piece-wise modew, 1 -> piece-wise wineaw(PPTabwe), 2 -> quadwatic modew(PPTabwe)  
  uint8_t           Padding8_Avfs;

  QuadwaticInt_t    qAvfsGb[AVFS_VOWTAGE_COUNT];              // GHz->V Ovewwide of fused cuwve 
  DwoopInt_t        dBtcGbGfxPww;         // GHz->V BtcGb
  DwoopInt_t        dBtcGbGfxDfww;        // GHz->V BtcGb
  DwoopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  WineawInt_t       qAgingGb[AVFS_VOWTAGE_COUNT];          // GHz->V 

  PiecewiseWineawDwoopInt_t   PiecewiseWineawDwoopIntGfxDfww; //GHz ->Vstowe in IEEE fwoat fowmat

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_VOWTAGE_COUNT]; // GHz->V 

  uint16_t          DcTow[AVFS_VOWTAGE_COUNT];            // mV Q2

  uint8_t           DcBtcEnabwed[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_GfxBtc[2];

  uint16_t          DcBtcMin[AVFS_VOWTAGE_COUNT];       // mV Q2
  uint16_t          DcBtcMax[AVFS_VOWTAGE_COUNT];       // mV Q2

  uint16_t          DcBtcGb[AVFS_VOWTAGE_COUNT];       // mV Q2
  
  // SECTION: XGMI
  uint8_t           XgmiDpmPstates[NUM_XGMI_WEVEWS]; // 2 DPM states, high and wow.  0-P0, 1-P1, 2-P2, 3-P3.
  uint8_t           XgmiDpmSpawe[2];

  // SECTION: Advanced Options
  uint32_t          DebugOvewwides;
  QuadwaticInt_t    WesewvedEquation0; 
  QuadwaticInt_t    WesewvedEquation1; 
  QuadwaticInt_t    WesewvedEquation2; 
  QuadwaticInt_t    WesewvedEquation3; 

  // SECTION: Sku Wesewved
  uint8_t          CustomewVawiant;

  //VC BTC pawametews awe onwy appwicabwe to VDD_GFX domain
  uint8_t          VcBtcEnabwed;
  uint16_t         VcBtcVminT0;                 // T0_VMIN
  uint16_t         VcBtcFixedVminAgingOffset;   // FIXED_VMIN_AGING_OFFSET 
  uint16_t         VcBtcVmin2PsmDegwationGb;    // VMIN_TO_PSM_DEGWADATION_GB 
  uint32_t         VcBtcPsmA;                   // A_PSM
  uint32_t         VcBtcPsmB;                   // B_PSM
  uint32_t         VcBtcVminA;                  // A_VMIN
  uint32_t         VcBtcVminB;                  // B_VMIN  
  
  //GPIO Boawd featuwe
  uint16_t         WedGpio;            //GenewiA GPIO fwag used to contwow the wadeon WEDs
  uint16_t         GfxPowewStagesGpio; //Genwk_vsync GPIO fwag used to contwow gfx powew stages 
  
  uint32_t         SkuWesewved[8];


  // MAJOW SECTION: BOAWD PAWAMETEWS

  //SECTION: Gaming Cwocks
  uint32_t     GamingCwk[6];

  // SECTION: I2C Contwow
  I2cContwowwewConfig_t  I2cContwowwews[NUM_I2C_CONTWOWWEWS];     

  uint8_t      GpioScw;  // GPIO Numbew fow SCW Wine, used onwy fow CKSVII2C1
  uint8_t      GpioSda;  // GPIO Numbew fow SDA Wine, used onwy fow CKSVII2C1
  uint8_t      FchUsbPdSwaveAddw; //Fow wequesting USB PD contwowwew S-states via FCH I2C when entewing PME tuwn off
  uint8_t      I2cSpawe[1];

  // SECTION: SVI2 Boawd Pawametews
  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      VddciUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      MvddUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode

  // SECTION: Tewemetwy Settings
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

  uint32_t     MvddWatio; // This is used fow MVDD  Svi2 Div Watio wowkawound. It has 16 fwactionaw bits (Q16.16)
  
  // SECTION: GPIO Settings
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
  uint8_t      WedEnabweMask;

  uint8_t      WedPcie;        // GPIO numbew fow PCIE wesuwts
  uint8_t      WedEwwow;       // GPIO numbew fow Ewwow Cases
  uint8_t      WedSpawe1[2];

  // SECTION: Cwock Spwead Spectwum
  
  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz
  
  // UCWK Spwead Spectwum
  uint16_t     UcwkSpweadPadding;
  uint16_t     UcwkSpweadFweq;      // kHz

  // FCWK Spwead Spectwum
  uint8_t      FcwkSpweadEnabwed;   // on ow off
  uint8_t      FcwkSpweadPewcent;   // Q4.4
  uint16_t     FcwkSpweadFweq;      // kHz
  
  // Section: Memowy Config
  uint32_t     MemowyChannewEnabwed; // Fow DWAM use onwy, Max 32 channews enabwed bit mask. 
  
  uint8_t      DwamBitWidth; // Fow DWAM use onwy.  See Dwam Bit width type defines
  uint8_t      PaddingMem1[3];

  // Section: Totaw Boawd Powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPowewPadding; 
  
  // SECTION: XGMI Twaining
  uint8_t      XgmiWinkSpeed   [NUM_XGMI_PSTATE_WEVEWS];
  uint8_t      XgmiWinkWidth   [NUM_XGMI_PSTATE_WEVEWS];

  uint16_t     XgmiFcwkFweq    [NUM_XGMI_PSTATE_WEVEWS];
  uint16_t     XgmiSocVowtage  [NUM_XGMI_PSTATE_WEVEWS];

  // SECTION: UMC featuwe fwags
  uint8_t      HswEnabwed;
  uint8_t      VddqOffEnabwed;
  uint8_t      PaddingUmcFwags[2];

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadPewcent[16];   

  // SECTION: Boawd Wesewved
  uint32_t     BoawdWesewved[11];

  // SECTION: Stwuctuwe Padding

  // Padding fow MMHUB - do not modify this
  uint32_t     MmHubPadding[8]; // SMU intewnaw use

} PPTabwe_t;
#pwagma pack(pop)

typedef stwuct {
  // MAJOW SECTION: SKU PAWAMETEWS

  uint32_t Vewsion;

  // SECTION: Featuwe Enabwement
  uint32_t FeatuwesToWun[NUM_FEATUWES / 32];

  // SECTION: Infwastwuctuwe Wimits
  uint16_t SocketPowewWimitAc[PPT_THWOTTWEW_COUNT]; // Watts
  uint16_t SocketPowewWimitAcTau[PPT_THWOTTWEW_COUNT]; // Time constant of WPF in ms
  uint16_t SocketPowewWimitDc[PPT_THWOTTWEW_COUNT];  // Watts
  uint16_t SocketPowewWimitDcTau[PPT_THWOTTWEW_COUNT];  // Time constant of WPF in ms

  uint16_t TdcWimit[TDC_THWOTTWEW_COUNT];             // Amps
  uint16_t TdcWimitTau[TDC_THWOTTWEW_COUNT];          // Time constant of WPF in ms

  uint16_t TempewatuweWimit[TEMP_COUNT]; // Cewcius

  uint32_t FitWimit;                // Faiwuwes in time (faiwuwes pew miwwion pawts ovew the defined wifetime)

  // SECTION: Powew Configuwation
  uint8_t      TotawPowewConfig;    //0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measuwed. Use defines fwom PwwConfig_e
  uint8_t      TotawPowewPadding[3];  

  // SECTION: APCC Settings
  uint32_t     ApccPwusWesidencyWimit;

  //SECTION: SMNCWK DPM
  uint16_t       SmncwkDpmFweq        [NUM_SMNCWK_DPM_WEVEWS];       // in MHz
  uint16_t       SmncwkDpmVowtage     [NUM_SMNCWK_DPM_WEVEWS];       // mV(Q2)

  uint32_t       PaddingAPCC;
  uint16_t       PewPawtDwoopVsetGfxDfww[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS];  //In mV(Q2)
  uint16_t       PaddingPewPawtDwoop;

  // SECTION: Thwottwew settings
  uint32_t ThwottwewContwowMask;   // See Thwottew masks defines

  // SECTION: FW DSTATE Settings  
  uint32_t FwDStateMask;           // See FW DState masks defines

  // SECTION: UWV Settings
  uint16_t  UwvVowtageOffsetSoc; // In mV(Q2)
  uint16_t  UwvVowtageOffsetGfx; // In mV(Q2)

  uint16_t     MinVowtageUwvGfx; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_GFX in UWV mode 
  uint16_t     MinVowtageUwvSoc; // In mV(Q2)  Minimum Vowtage ("Vmin") of VDD_SOC in UWV mode

  uint16_t     SocWIVmin;
  uint16_t     SocWIVminoffset;

  uint8_t   GceaWinkMgwIdweThweshowd;        //Set by SMU FW duwing enabwment of GFXOFF. Contwows deway fow GFX SDP powt disconnection duwing idwe events
  uint8_t   paddingWwcUwvPawams[3];

  // SECTION: Vowtage Contwow Pawametews
  uint16_t     MinVowtageGfx;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_GFX
  uint16_t     MinVowtageSoc;     // In mV(Q2) Minimum Vowtage ("Vmin") of VDD_SOC
  uint16_t     MaxVowtageGfx;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_GFX
  uint16_t     MaxVowtageSoc;     // In mV(Q2) Maximum Vowtage awwowabwe of VDD_SOC

  uint16_t     WoadWineWesistanceGfx;   // In mOhms with 8 fwactionaw bits
  uint16_t     WoadWineWesistanceSoc;   // In mOhms with 8 fwactionaw bits

  // SECTION: Tempewatuwe Dependent Vmin
  uint16_t     VDDGFX_TVmin;       //Cewcius
  uint16_t     VDDSOC_TVmin;       //Cewcius
  uint16_t     VDDGFX_Vmin_HiTemp; // mV Q2
  uint16_t     VDDGFX_Vmin_WoTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_HiTemp; // mV Q2
  uint16_t     VDDSOC_Vmin_WoTemp; // mV Q2

  uint16_t     VDDGFX_TVminHystewsis; // Cewcius
  uint16_t     VDDSOC_TVminHystewsis; // Cewcius

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
  uint16_t       FweqTabweDtbcwk   [NUM_DTBCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];     // In MHz
  uint32_t       Paddingcwks;

  DwoopInt_t     PewPawtDwoopModewGfxDfww[NUM_PIECE_WISE_WINEAW_DWOOP_MODEW_VF_POINTS]; //GHz ->Vstowe in IEEE fwoat fowmat

  uint32_t       DcModeMaxFweq     [PPCWK_COUNT            ];     // In MHz

  uint8_t        FweqTabweUcwkDiv  [NUM_UCWK_DPM_WEVEWS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

  // Used fow MAWW pewfowmance boost
  uint16_t       FcwkBoostFweq;                                   // In Mhz
  uint16_t       FcwkPawamPadding;

  // SECTION: DPM Config 2
  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];       // in MHz
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];       // mV(Q2)
  uint16_t       MemVddciVowtage   [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  uint16_t       MemMvddVowtage    [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  // GFXCWK DPM
  uint16_t        GfxcwkFgfxoffEntwy;   // in Mhz
  uint16_t        GfxcwkFinit;          // in Mhz 
  uint16_t        GfxcwkFidwe;          // in MHz 
  uint8_t         GfxcwkSouwce;         // 0 = PWW, 1 = DFWW
  uint8_t         GfxcwkPadding;

  // GFX GPO 
  uint8_t         GfxGpoSubFeatuweMask; // bit 0 = PACE, bit 1 = DEM
  uint8_t         GfxGpoEnabwedWowkPowicyMask; //Any powicy that GPO can be enabwed
  uint8_t         GfxGpoDisabwedWowkPowicyMask; //Any powicy that GPO can be disabwed
  uint8_t         GfxGpoPadding[1];
  uint32_t        GfxGpoVotingAwwow;    //Fow indicating which featuwe changes shouwd wesuwt in a GPO tabwe wecawcuwation

  uint32_t        GfxGpoPadding32[4];

  uint16_t        GfxDcsFopt;           // Optimaw GFXCWK fow DCS in Mhz
  uint16_t        GfxDcsFcwkFopt;       // Optimaw FCWK fow DCS in Mhz
  uint16_t        GfxDcsUcwkFopt;       // Optimaw UCWK fow DCS in Mhz

  uint16_t        DcsGfxOffVowtage;     //Vowtage in mV(Q2) appwied to VDDGFX when entewing DCS GFXOFF phase  

  uint16_t        DcsMinGfxOffTime;     //Minimum amount of time PMFW shuts GFX OFF as pawt of GFX DCS phase
  uint16_t        DcsMaxGfxOffTime;      //Maximum amount of time PMFW can shut GFX OFF as pawt of GFX DCS phase at a stwetch.

  uint32_t        DcsMinCweditAccum;    //Min amount of positive cwedit accumuwation befowe waking GFX up as pawt of DCS.

  uint16_t        DcsExitHystewesis;    //The min amount of time powew cwedit accumuwatow shouwd have a vawue > 0 befowe SMU exits the DCS thwottwing phase. 
  uint16_t        DcsTimeout;           //This is the amount of time SMU FW waits fow WWC to put GFX into GFXOFF befowe wevewting to the fawwback mechanism of thwottwing GFXCWK to Fmin.

  uint32_t        DcsPawamPadding[5];

  uint16_t        FwopsPewByteTabwe[WWC_PACE_TABWE_NUM_WEVEWS]; // Q8.8

  // UCWK section
  uint8_t      WowestUcwkWesewvedFowUwv; // Set this to 1 if UCWK DPM0 is wesewved fow UWV-mode onwy
  uint8_t      PaddingMem[3];

  uint8_t      UcwkDpmPstates     [NUM_UCWK_DPM_WEVEWS];     // 4 DPM states, 0-P0, 1-P1, 2-P2, 3-P3.

  // Used fow 2-Step UCWK change wowkawound
  UcwkDpmChangeWange_t UcwkDpmSwcFweqWange;  // In Mhz
  UcwkDpmChangeWange_t UcwkDpmTawgFweqWange; // In Mhz
  uint16_t UcwkDpmMidstepFweq;               // In Mhz
  uint16_t UcwkMidstepPadding;

  // Wink DPM Settings
  uint8_t      PcieGenSpeed[NUM_WINK_WEVEWS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uint8_t      PcieWaneCount[NUM_WINK_WEVEWS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uint16_t     WcwkFweq[NUM_WINK_WEVEWS];              

  // SECTION: Fan Contwow
  uint16_t     FanStopTemp;          //Cewcius
  uint16_t     FanStawtTemp;         //Cewcius

  uint16_t     FanGain[TEMP_COUNT];

  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     MGpuFanBoostWimitWpm;  
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint16_t     FanPadding16;
  uint8_t      FanTempInputSewect;
  uint8_t      FanPadding;
  uint8_t      FanZewoWpmEnabwe; 
  uint8_t      FanTachEdgePewWev;

  // The fowwowing awe AFC ovewwide pawametews. Weave at 0 to use FW defauwts.
  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;

  // SECTION: AVFS 
  // Ovewwides
  uint8_t           OvewwideAvfsGb[AVFS_VOWTAGE_COUNT];
  uint8_t           dBtcGbGfxDfwwModewSewect;  //0 -> fused piece-wise modew, 1 -> piece-wise wineaw(PPTabwe), 2 -> quadwatic modew(PPTabwe)  
  uint8_t           Padding8_Avfs;

  QuadwaticInt_t    qAvfsGb[AVFS_VOWTAGE_COUNT];              // GHz->V Ovewwide of fused cuwve 
  DwoopInt_t        dBtcGbGfxPww;         // GHz->V BtcGb
  DwoopInt_t        dBtcGbGfxDfww;        // GHz->V BtcGb
  DwoopInt_t        dBtcGbSoc;            // GHz->V BtcGb
  WineawInt_t       qAgingGb[AVFS_VOWTAGE_COUNT];          // GHz->V 

  PiecewiseWineawDwoopInt_t   PiecewiseWineawDwoopIntGfxDfww; //GHz ->Vstowe in IEEE fwoat fowmat

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_VOWTAGE_COUNT]; // GHz->V 

  uint16_t          DcTow[AVFS_VOWTAGE_COUNT];            // mV Q2

  uint8_t           DcBtcEnabwed[AVFS_VOWTAGE_COUNT];
  uint8_t           Padding8_GfxBtc[2];

  uint16_t          DcBtcMin[AVFS_VOWTAGE_COUNT];       // mV Q2
  uint16_t          DcBtcMax[AVFS_VOWTAGE_COUNT];       // mV Q2

  uint16_t          DcBtcGb[AVFS_VOWTAGE_COUNT];       // mV Q2

  // SECTION: XGMI
  uint8_t           XgmiDpmPstates[NUM_XGMI_WEVEWS]; // 2 DPM states, high and wow.  0-P0, 1-P1, 2-P2, 3-P3.
  uint8_t           XgmiDpmSpawe[2];

  // SECTION: Advanced Options
  uint32_t          DebugOvewwides;
  QuadwaticInt_t    WesewvedEquation0;
  QuadwaticInt_t    WesewvedEquation1;
  QuadwaticInt_t    WesewvedEquation2;
  QuadwaticInt_t    WesewvedEquation3;

  // SECTION: Sku Wesewved
  uint8_t          CustomewVawiant;

    //VC BTC pawametews awe onwy appwicabwe to VDD_GFX domain
  uint8_t          VcBtcEnabwed;
  uint16_t         VcBtcVminT0;                 // T0_VMIN
  uint16_t         VcBtcFixedVminAgingOffset;   // FIXED_VMIN_AGING_OFFSET 
  uint16_t         VcBtcVmin2PsmDegwationGb;    // VMIN_TO_PSM_DEGWADATION_GB 
  uint32_t         VcBtcPsmA;                   // A_PSM
  uint32_t         VcBtcPsmB;                   // B_PSM
  uint32_t         VcBtcVminA;                  // A_VMIN
  uint32_t         VcBtcVminB;                  // B_VMIN  

  //GPIO Boawd featuwe
  uint16_t         WedGpio;            //GenewiA GPIO fwag used to contwow the wadeon WEDs
  uint16_t         GfxPowewStagesGpio; //Genwk_vsync GPIO fwag used to contwow gfx powew stages 

  uint32_t         SkuWesewved[63];



  // MAJOW SECTION: BOAWD PAWAMETEWS

  //SECTION: Gaming Cwocks
  uint32_t     GamingCwk[6];

  // SECTION: I2C Contwow
  I2cContwowwewConfig_t  I2cContwowwews[NUM_I2C_CONTWOWWEWS];     

  uint8_t      GpioScw;  // GPIO Numbew fow SCW Wine, used onwy fow CKSVII2C1
  uint8_t      GpioSda;  // GPIO Numbew fow SDA Wine, used onwy fow CKSVII2C1
  uint8_t      FchUsbPdSwaveAddw; //Fow wequesting USB PD contwowwew S-states via FCH I2C when entewing PME tuwn off
  uint8_t      I2cSpawe[1];

  // SECTION: SVI2 Boawd Pawametews
  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      VddciUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      MvddUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode

  // SECTION: Tewemetwy Settings
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

  uint32_t     MvddWatio; // This is used fow MVDD  Svi2 Div Watio wowkawound. It has 16 fwactionaw bits (Q16.16)

  // SECTION: GPIO Settings
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
  uint8_t      WedEnabweMask;

  uint8_t      WedPcie;        // GPIO numbew fow PCIE wesuwts
  uint8_t      WedEwwow;       // GPIO numbew fow Ewwow Cases
  uint8_t      WedSpawe1[2];

  // SECTION: Cwock Spwead Spectwum

  // GFXCWK PWW Spwead Spectwum
  uint8_t      PwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      PwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     PwwGfxcwkSpweadFweq;      // kHz

  // GFXCWK DFWW Spwead Spectwum
  uint8_t      DfwwGfxcwkSpweadEnabwed;   // on ow off
  uint8_t      DfwwGfxcwkSpweadPewcent;   // Q4.4
  uint16_t     DfwwGfxcwkSpweadFweq;      // kHz

  // UCWK Spwead Spectwum
  uint16_t     UcwkSpweadPadding;
  uint16_t     UcwkSpweadFweq;      // kHz

  // FCWK Spwead Spectwum
  uint8_t      FcwkSpweadEnabwed;   // on ow off
  uint8_t      FcwkSpweadPewcent;   // Q4.4
  uint16_t     FcwkSpweadFweq;      // kHz

  // Section: Memowy Config
  uint32_t     MemowyChannewEnabwed; // Fow DWAM use onwy, Max 32 channews enabwed bit mask. 

  uint8_t      DwamBitWidth; // Fow DWAM use onwy.  See Dwam Bit width type defines
  uint8_t      PaddingMem1[3];

  // Section: Totaw Boawd Powew
  uint16_t     TotawBoawdPowew;     //Onwy needed fow TCP Estimated case, whewe TCP = TGP+Totaw Boawd Powew
  uint16_t     BoawdPowewPadding; 

  // SECTION: XGMI Twaining
  uint8_t      XgmiWinkSpeed   [NUM_XGMI_PSTATE_WEVEWS];
  uint8_t      XgmiWinkWidth   [NUM_XGMI_PSTATE_WEVEWS];

  uint16_t     XgmiFcwkFweq    [NUM_XGMI_PSTATE_WEVEWS];
  uint16_t     XgmiSocVowtage  [NUM_XGMI_PSTATE_WEVEWS];

  // SECTION: UMC featuwe fwags
  uint8_t      HswEnabwed;
  uint8_t      VddqOffEnabwed;
  uint8_t      PaddingUmcFwags[2];

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadPewcent[16];   

  // SECTION: Boawd Wesewved
  uint32_t     BoawdWesewved[11];

  // SECTION: Stwuctuwe Padding

  // Padding fow MMHUB - do not modify this
  uint32_t     MmHubPadding[8]; // SMU intewnaw use


} PPTabwe_beige_goby_t;

typedef stwuct {
  // Time constant pawametews fow cwock avewages in ms
  uint16_t     GfxcwkAvewageWpfTau;
  uint16_t     FcwkAvewageWpfTau;
  uint16_t     UcwkAvewageWpfTau;
  uint16_t     GfxActivityWpfTau;
  uint16_t     UcwkActivityWpfTau;
  uint16_t     SocketPowewWpfTau;  
  uint16_t     VcnCwkAvewageWpfTau;
  uint16_t     padding16; 
} DwivewSmuConfig_t;

typedef stwuct {
  DwivewSmuConfig_t DwivewSmuConfig;

  uint32_t     Spawe[7];  
  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} DwivewSmuConfigExtewnaw_t;

typedef stwuct {
  uint16_t               GfxcwkFmin;           // MHz
  uint16_t               GfxcwkFmax;           // MHz
  QuadwaticInt_t         CustomGfxVfCuwve;     // a: mV/MHz^2, b: mv/MHz, c: mV
  uint16_t               CustomCuwveFmin;      // MHz 
  uint16_t               UcwkFmin;             // MHz  
  uint16_t               UcwkFmax;             // MHz
  int16_t                OvewDwivePct;         // %
  uint16_t               FanMaximumWpm;
  uint16_t               FanMinimumPwm;
  uint16_t               FanAcousticWimitWpm;
  uint16_t               FanTawgetTempewatuwe; // Degwee Cewcius 
  uint8_t                FanWineawPwmPoints[NUM_OD_FAN_MAX_POINTS];
  uint8_t                FanWineawTempPoints[NUM_OD_FAN_MAX_POINTS];
  uint16_t               MaxOpTemp;            // Degwee Cewcius
  int16_t                VddGfxOffset;         // in mV
  uint8_t                FanZewoWpmEnabwe;
  uint8_t                FanZewoWpmStopTemp;
  uint8_t                FanMode;
  uint8_t                Padding[1];
} OvewDwiveTabwe_t; 

typedef stwuct {
  OvewDwiveTabwe_t OvewDwiveTabwe;
  uint32_t      Spawe[8];  

  uint32_t     MmHubPadding[8]; // SMU intewnaw use    
} OvewDwiveTabweExtewnaw_t;

typedef stwuct {
  uint32_t CuwwCwock[PPCWK_COUNT];

  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageFcwkFwequencyPweDs;
  uint16_t AvewageFcwkFwequencyPostDs;
  uint16_t AvewageUcwkFwequencyPweDs  ;
  uint16_t AvewageUcwkFwequencyPostDs  ;

  
  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint8_t  CuwwSocVowtageOffset  ;
  uint8_t  CuwwGfxVowtageOffset  ;
  uint8_t  CuwwMemVidOffset      ;
  uint8_t  Padding8        ;
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
  uint8_t  CuwwFanPwm;
  uint16_t CuwwFanSpeed;

  //BACO metwics, PMFW-1721
  //metwics fow D3hot entwy/exit and dwivew AWM msgs
  uint8_t D3HotEntwyCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t D3HotExitCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t AwmMsgWeceivedCountPewMode[D3HOT_SEQUENCE_COUNT];

  //PMFW-4362
  uint32_t EnewgyAccumuwatow;
  uint16_t AvewageVcwk0Fwequency  ;
  uint16_t AvewageDcwk0Fwequency  ;  
  uint16_t AvewageVcwk1Fwequency  ;
  uint16_t AvewageDcwk1Fwequency  ;  
  uint16_t VcnActivityPewcentage  ; //pwace howdew, David N. to pwovide fuww sequence
  uint8_t  PcieWate               ;
  uint8_t  PcieWidth              ;
  uint16_t AvewageGfxcwkFwequencyTawget;

  uint16_t Padding16_2;
} SmuMetwics_t;

typedef stwuct {
  uint32_t CuwwCwock[PPCWK_COUNT];

  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageFcwkFwequencyPweDs;
  uint16_t AvewageFcwkFwequencyPostDs;
  uint16_t AvewageUcwkFwequencyPweDs  ;
  uint16_t AvewageUcwkFwequencyPostDs  ;


  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint8_t  CuwwSocVowtageOffset  ;
  uint8_t  CuwwGfxVowtageOffset  ;
  uint8_t  CuwwMemVidOffset      ;
  uint8_t  Padding8        ;
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
  uint32_t AccCnt                ;
  uint8_t  ThwottwingPewcentage[THWOTTWEW_COUNT];


  uint8_t  WinkDpmWevew;
  uint8_t  CuwwFanPwm;
  uint16_t CuwwFanSpeed;

  //BACO metwics, PMFW-1721
  //metwics fow D3hot entwy/exit and dwivew AWM msgs
  uint8_t D3HotEntwyCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t D3HotExitCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t AwmMsgWeceivedCountPewMode[D3HOT_SEQUENCE_COUNT];

  //PMFW-4362
  uint32_t EnewgyAccumuwatow;
  uint16_t AvewageVcwk0Fwequency  ;
  uint16_t AvewageDcwk0Fwequency  ;
  uint16_t AvewageVcwk1Fwequency  ;
  uint16_t AvewageDcwk1Fwequency  ;
  uint16_t VcnActivityPewcentage  ; //pwace howdew, David N. to pwovide fuww sequence
  uint8_t  PcieWate               ;
  uint8_t  PcieWidth              ;
  uint16_t AvewageGfxcwkFwequencyTawget;

  uint16_t Padding16_2;
} SmuMetwics_V2_t;

typedef stwuct {
  uint32_t CuwwCwock[PPCWK_COUNT];

  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageFcwkFwequencyPweDs;
  uint16_t AvewageFcwkFwequencyPostDs;
  uint16_t AvewageUcwkFwequencyPweDs;
  uint16_t AvewageUcwkFwequencyPostDs;


  uint16_t AvewageGfxActivity;
  uint16_t AvewageUcwkActivity;
  uint8_t  CuwwSocVowtageOffset;
  uint8_t  CuwwGfxVowtageOffset;
  uint8_t  CuwwMemVidOffset;
  uint8_t  Padding8;
  uint16_t AvewageSocketPowew;
  uint16_t TempewatuweEdge;
  uint16_t TempewatuweHotspot;
  uint16_t TempewatuweMem;
  uint16_t TempewatuweVwGfx;
  uint16_t TempewatuweVwMem0;
  uint16_t TempewatuweVwMem1;
  uint16_t TempewatuweVwSoc;
  uint16_t TempewatuweWiquid0;
  uint16_t TempewatuweWiquid1;
  uint16_t TempewatuwePwx;
  uint16_t Padding16;
  uint32_t AccCnt;
  uint8_t  ThwottwingPewcentage[THWOTTWEW_COUNT];


  uint8_t  WinkDpmWevew;
  uint8_t  CuwwFanPwm;
  uint16_t CuwwFanSpeed;

  //BACO metwics, PMFW-1721
  //metwics fow D3hot entwy/exit and dwivew AWM msgs
  uint8_t D3HotEntwyCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t D3HotExitCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint8_t AwmMsgWeceivedCountPewMode[D3HOT_SEQUENCE_COUNT];

  //PMFW-4362
  uint32_t EnewgyAccumuwatow;
  uint16_t AvewageVcwk0Fwequency;
  uint16_t AvewageDcwk0Fwequency;
  uint16_t AvewageVcwk1Fwequency;
  uint16_t AvewageDcwk1Fwequency;
  uint16_t VcnUsagePewcentage0;
  uint16_t VcnUsagePewcentage1;
  uint8_t  PcieWate;
  uint8_t  PcieWidth;
  uint16_t AvewageGfxcwkFwequencyTawget;

  uint32_t PubwicSewiawNumWowew32;
  uint32_t PubwicSewiawNumUppew32;

} SmuMetwics_V3_t;

typedef stwuct {
	uint32_t CuwwCwock[PPCWK_COUNT];

	uint16_t AvewageGfxcwkFwequencyPweDs;
	uint16_t AvewageGfxcwkFwequencyPostDs;
	uint16_t AvewageFcwkFwequencyPweDs;
	uint16_t AvewageFcwkFwequencyPostDs;
	uint16_t AvewageUcwkFwequencyPweDs;
	uint16_t AvewageUcwkFwequencyPostDs;


	uint16_t AvewageGfxActivity;
	uint16_t AvewageUcwkActivity;
	uint8_t  CuwwSocVowtageOffset;
	uint8_t  CuwwGfxVowtageOffset;
	uint8_t  CuwwMemVidOffset;
	uint8_t  Padding8;
	uint16_t AvewageSocketPowew;
	uint16_t TempewatuweEdge;
	uint16_t TempewatuweHotspot;
	uint16_t TempewatuweMem;
	uint16_t TempewatuweVwGfx;
	uint16_t TempewatuweVwMem0;
	uint16_t TempewatuweVwMem1;
	uint16_t TempewatuweVwSoc;
	uint16_t TempewatuweWiquid0;
	uint16_t TempewatuweWiquid1;
	uint16_t TempewatuwePwx;
	uint16_t Padding16;
	uint32_t AccCnt;
	uint8_t  ThwottwingPewcentage[THWOTTWEW_COUNT];


	uint8_t  WinkDpmWevew;
	uint8_t  CuwwFanPwm;
	uint16_t CuwwFanSpeed;

	//BACO metwics, PMFW-1721
	//metwics fow D3hot entwy/exit and dwivew AWM msgs
	uint8_t D3HotEntwyCountPewMode[D3HOT_SEQUENCE_COUNT];
	uint8_t D3HotExitCountPewMode[D3HOT_SEQUENCE_COUNT];
	uint8_t AwmMsgWeceivedCountPewMode[D3HOT_SEQUENCE_COUNT];

	//PMFW-4362
	uint32_t EnewgyAccumuwatow;
	uint16_t AvewageVcwk0Fwequency;
	uint16_t AvewageDcwk0Fwequency;
	uint16_t AvewageVcwk1Fwequency;
	uint16_t AvewageDcwk1Fwequency;
	uint16_t VcnUsagePewcentage0;
	uint16_t VcnUsagePewcentage1;
	uint8_t  PcieWate;
	uint8_t  PcieWidth;
	uint16_t AvewageGfxcwkFwequencyTawget;

	uint8_t  ApuSTAPMSmawtShiftWimit;
	uint8_t  AvewageApuSocketPowew;
	uint8_t  ApuSTAPMWimit;
	uint8_t  Padding8_2;

} SmuMetwics_V4_t;

typedef stwuct {
  union {
    SmuMetwics_t SmuMetwics;
    SmuMetwics_V2_t SmuMetwics_V2;
    SmuMetwics_V3_t SmuMetwics_V3;
    SmuMetwics_V4_t SmuMetwics_V4;
  };
  uint32_t Spawe[1];

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use  
} SmuMetwicsExtewnaw_t;

typedef stwuct {
  uint16_t MinCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MaxCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MinUcwk;
  uint16_t MaxUcwk;
  
  uint8_t  WmSetting;
  uint8_t  Fwags;
  uint8_t  Padding[2];

} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WM_SOCCWK = 0,
  WM_DCEFCWK,
  WM_COUNT,
} WM_CWOCK_e;

typedef enum {
  WATEWMAWKS_CWOCK_WANGE = 0,
  WATEWMAWKS_DUMMY_PSTATE,
  WATEWMAWKS_MAWW,
  WATEWMAWKS_COUNT,
} WATEWMAWKS_FWAGS_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];
} Watewmawks_t;

typedef stwuct {
  Watewmawks_t Watewmawks;

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} WatewmawksExtewnaw_t;

typedef stwuct {
  uint16_t avgPsmCount[67];
  uint16_t minPsmCount[67];
  fwoat    avgPsmVowtage[67]; 
  fwoat    minPsmVowtage[67];
} AvfsDebugTabwe_t;

typedef stwuct {
  AvfsDebugTabwe_t AvfsDebugTabwe;

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} AvfsDebugTabweExtewnaw_t;

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

  uint32_t EnabwedAvfsModuwes[3]; //Sienna_Cichwid - 67 AVFS moduwes
} AvfsFuseOvewwide_t;

typedef stwuct {
  AvfsFuseOvewwide_t AvfsFuseOvewwide;

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} AvfsFuseOvewwideExtewnaw_t;

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
  
  uint8_t   Fcwk_ActiveHystWimit;
  uint8_t   Fcwk_IdweHystWimit;
  uint8_t   Fcwk_FPS;
  uint8_t   Fcwk_MinActiveFweqType;
  uint8_t   Fcwk_BoostewFweqType; 
  uint8_t   Fcwk_MinFweqStep;                // Minimum dewta between cuwwent and tawget fwequeny in owdew fow FW to change cwock.
  uint16_t  Fcwk_MinActiveFweq;              // MHz
  uint16_t  Fcwk_BoostewFweq;                // MHz
  uint16_t  Fcwk_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Fcwk_PD_Data_wimit_a;            // Q16
  uint32_t  Fcwk_PD_Data_wimit_b;            // Q16
  uint32_t  Fcwk_PD_Data_wimit_c;            // Q16
  uint32_t  Fcwk_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Fcwk_PD_Data_ewwow_wate_coeff;   // Q16
  
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

} DpmActivityMonitowCoeffInt_t;


typedef stwuct {
  DpmActivityMonitowCoeffInt_t DpmActivityMonitowCoeffInt;
  uint32_t     MmHubPadding[8]; // SMU intewnaw use  
} DpmActivityMonitowCoeffIntExtewnaw_t;

// Wowkwoad bits
#define WOWKWOAD_PPWIB_DEFAUWT_BIT        0 
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 1 
#define WOWKWOAD_PPWIB_POWEW_SAVING_BIT   2 
#define WOWKWOAD_PPWIB_VIDEO_BIT          3 
#define WOWKWOAD_PPWIB_VW_BIT             4 
#define WOWKWOAD_PPWIB_COMPUTE_BIT        5 
#define WOWKWOAD_PPWIB_CUSTOM_BIT         6 
#define WOWKWOAD_PPWIB_W3D_BIT            7 
#define WOWKWOAD_PPWIB_COUNT              8 


// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam

// Tabwe twansfew status
#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF

// Tabwe types
#define TABWE_PPTABWE                 0
#define TABWE_WATEWMAWKS              1
#define TABWE_AVFS_PSM_DEBUG          2
#define TABWE_AVFS_FUSE_OVEWWIDE      3
#define TABWE_PMSTATUSWOG             4
#define TABWE_SMU_METWICS             5
#define TABWE_DWIVEW_SMU_CONFIG       6
#define TABWE_ACTIVITY_MONITOW_COEFF  7
#define TABWE_OVEWDWIVE               8
#define TABWE_I2C_COMMANDS            9
#define TABWE_PACE                   10
#define TABWE_ECCINFO                11
#define TABWE_COUNT                  12

typedef stwuct {
  fwoat FwopsPewByteTabwe[WWC_PACE_TABWE_NUM_WEVEWS];
} WwcPaceFwopsPewByteOvewwide_t;

typedef stwuct {
  WwcPaceFwopsPewByteOvewwide_t WwcPaceFwopsPewByteOvewwide;
  
  uint32_t     MmHubPadding[8]; // SMU intewnaw use  
} WwcPaceFwopsPewByteOvewwideExtewnaw_t;

// These defines awe used with the SMC_MSG_SetUcwkFastSwitch message.
#define UCWK_SWITCH_SWOW 0
#define UCWK_SWITCH_FAST 1
#define UCWK_SWITCH_DUMMY 2
#endif
