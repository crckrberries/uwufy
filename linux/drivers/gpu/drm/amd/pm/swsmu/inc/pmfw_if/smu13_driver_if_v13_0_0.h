/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef SMU13_DWIVEW_IF_V13_0_0_H
#define SMU13_DWIVEW_IF_V13_0_0_H

#define SMU13_0_0_DWIVEW_IF_VEWSION 0x3D

//Incwement this vewsion if SkuTabwe_t ow BoawdTabwe_t change
#define PPTABWE_VEWSION 0x2B

#define NUM_GFXCWK_DPM_WEVEWS    16
#define NUM_SOCCWK_DPM_WEVEWS    8
#define NUM_MP0CWK_DPM_WEVEWS    2
#define NUM_DCWK_DPM_WEVEWS      8
#define NUM_VCWK_DPM_WEVEWS      8
#define NUM_DISPCWK_DPM_WEVEWS   8
#define NUM_DPPCWK_DPM_WEVEWS    8
#define NUM_DPWEFCWK_DPM_WEVEWS  8
#define NUM_DCFCWK_DPM_WEVEWS    8
#define NUM_DTBCWK_DPM_WEVEWS    8
#define NUM_UCWK_DPM_WEVEWS      4
#define NUM_WINK_WEVEWS          3
#define NUM_FCWK_DPM_WEVEWS      8
#define NUM_OD_FAN_MAX_POINTS    6

// Featuwe Contwow Defines
#define FEATUWE_FW_DATA_WEAD_BIT              0
#define FEATUWE_DPM_GFXCWK_BIT                1
#define FEATUWE_DPM_GFX_POWEW_OPTIMIZEW_BIT   2
#define FEATUWE_DPM_UCWK_BIT                  3
#define FEATUWE_DPM_FCWK_BIT                  4
#define FEATUWE_DPM_SOCCWK_BIT                5
#define FEATUWE_DPM_MP0CWK_BIT                6
#define FEATUWE_DPM_WINK_BIT                  7
#define FEATUWE_DPM_DCN_BIT                   8
#define FEATUWE_VMEMP_SCAWING_BIT             9
#define FEATUWE_VDDIO_MEM_SCAWING_BIT         10
#define FEATUWE_DS_GFXCWK_BIT                 11
#define FEATUWE_DS_SOCCWK_BIT                 12
#define FEATUWE_DS_FCWK_BIT                   13
#define FEATUWE_DS_WCWK_BIT                   14
#define FEATUWE_DS_DCFCWK_BIT                 15
#define FEATUWE_DS_UCWK_BIT                   16
#define FEATUWE_GFX_UWV_BIT                   17
#define FEATUWE_FW_DSTATE_BIT                 18
#define FEATUWE_GFXOFF_BIT                    19
#define FEATUWE_BACO_BIT                      20
#define FEATUWE_MM_DPM_BIT                    21
#define FEATUWE_SOC_MPCWK_DS_BIT              22
#define FEATUWE_BACO_MPCWK_DS_BIT             23
#define FEATUWE_THWOTTWEWS_BIT                24
#define FEATUWE_SMAWTSHIFT_BIT                25
#define FEATUWE_GTHW_BIT                      26
#define FEATUWE_ACDC_BIT                      27
#define FEATUWE_VW0HOT_BIT                    28
#define FEATUWE_FW_CTF_BIT                    29
#define FEATUWE_FAN_CONTWOW_BIT               30
#define FEATUWE_GFX_DCS_BIT                   31
#define FEATUWE_GFX_WEAD_MAWGIN_BIT           32
#define FEATUWE_WED_DISPWAY_BIT               33
#define FEATUWE_GFXCWK_SPWEAD_SPECTWUM_BIT    34
#define FEATUWE_OUT_OF_BAND_MONITOW_BIT       35
#define FEATUWE_OPTIMIZED_VMIN_BIT            36
#define FEATUWE_GFX_IMU_BIT                   37
#define FEATUWE_BOOT_TIME_CAW_BIT             38
#define FEATUWE_GFX_PCC_DFWW_BIT              39
#define FEATUWE_SOC_CG_BIT                    40
#define FEATUWE_DF_CSTATE_BIT                 41
#define FEATUWE_GFX_EDC_BIT                   42
#define FEATUWE_BOOT_POWEW_OPT_BIT            43
#define FEATUWE_CWOCK_POWEW_DOWN_BYPASS_BIT   44
#define FEATUWE_DS_VCN_BIT                    45
#define FEATUWE_BACO_CG_BIT                   46
#define FEATUWE_MEM_TEMP_WEAD_BIT             47
#define FEATUWE_ATHUB_MMHUB_PG_BIT            48
#define FEATUWE_SOC_PCC_BIT                   49
#define FEATUWE_EDC_PWWBWK_BIT                50
#define FEATUWE_BOMXCO_SVI3_PWOG_BIT          51
#define FEATUWE_SPAWE_52_BIT                  52
#define FEATUWE_SPAWE_53_BIT                  53
#define FEATUWE_SPAWE_54_BIT                  54
#define FEATUWE_SPAWE_55_BIT                  55
#define FEATUWE_SPAWE_56_BIT                  56
#define FEATUWE_SPAWE_57_BIT                  57
#define FEATUWE_SPAWE_58_BIT                  58
#define FEATUWE_SPAWE_59_BIT                  59
#define FEATUWE_SPAWE_60_BIT                  60
#define FEATUWE_SPAWE_61_BIT                  61
#define FEATUWE_SPAWE_62_BIT                  62
#define FEATUWE_SPAWE_63_BIT                  63
#define NUM_FEATUWES                          64

#define AWWOWED_FEATUWE_CTWW_DEFAUWT 0xFFFFFFFFFFFFFFFFUWW
#define AWWOWED_FEATUWE_CTWW_SCPM	((1 << FEATUWE_DPM_GFXCWK_BIT) | \
									(1 << FEATUWE_DPM_GFX_POWEW_OPTIMIZEW_BIT) | \
									(1 << FEATUWE_DPM_UCWK_BIT) | \
									(1 << FEATUWE_DPM_FCWK_BIT) | \
									(1 << FEATUWE_DPM_SOCCWK_BIT) | \
									(1 << FEATUWE_DPM_MP0CWK_BIT) | \
									(1 << FEATUWE_DPM_WINK_BIT) | \
									(1 << FEATUWE_DPM_DCN_BIT) | \
									(1 << FEATUWE_DS_GFXCWK_BIT) | \
									(1 << FEATUWE_DS_SOCCWK_BIT) | \
									(1 << FEATUWE_DS_FCWK_BIT) | \
									(1 << FEATUWE_DS_WCWK_BIT) | \
									(1 << FEATUWE_DS_DCFCWK_BIT) | \
									(1 << FEATUWE_DS_UCWK_BIT) | \
									(1UWW << FEATUWE_DS_VCN_BIT))

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
#define DEBUG_OVEWWIDE_DISABWE_VOWT_WINK_VCN_FCWK      0x00000001
#define DEBUG_OVEWWIDE_DISABWE_VOWT_WINK_DCN_FCWK      0x00000002
#define DEBUG_OVEWWIDE_DISABWE_VOWT_WINK_MP0_FCWK      0x00000004
#define DEBUG_OVEWWIDE_DISABWE_VOWT_WINK_VCN_DCFCWK    0x00000008
#define DEBUG_OVEWWIDE_DISABWE_FAST_FCWK_TIMEW         0x00000010
#define DEBUG_OVEWWIDE_DISABWE_VCN_PG                  0x00000020
#define DEBUG_OVEWWIDE_DISABWE_FMAX_VMAX               0x00000040
#define DEBUG_OVEWWIDE_DISABWE_IMU_FW_CHECKS           0x00000080
#define DEBUG_OVEWWIDE_DISABWE_D0i2_WEENTWY_HSW_TIMEW_CHECK 0x00000100
#define DEBUG_OVEWWIDE_DISABWE_DFWW                    0x00000200
#define DEBUG_OVEWWIDE_ENABWE_WWC_VF_BWINGUP_MODE      0x00000400
#define DEBUG_OVEWWIDE_DFWW_MASTEW_MODE                0x00000800
#define DEBUG_OVEWWIDE_ENABWE_PWOFIWING_MODE           0x00001000

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

typedef enum {
  SVI_PSI_0, // Fuww phase count (defauwt)
  SVI_PSI_1, // Phase count 1st wevew
  SVI_PSI_2, // Phase count 2nd wevew
  SVI_PSI_3, // Singwe phase opewation + active diode emuwation
  SVI_PSI_4, // Singwe phase opewation + passive diode emuwation *optionaw*
  SVI_PSI_5, // Wesewved
  SVI_PSI_6, // Powew down to 0V (vowtage weguwation disabwed)
  SVI_PSI_7, // Automated phase shedding and diode emuwation
} SVI_PSI_e;

// Thwottwew Contwow/Status Bits
#define THWOTTWEW_TEMP_EDGE_BIT        0
#define THWOTTWEW_TEMP_HOTSPOT_BIT     1
#define THWOTTWEW_TEMP_HOTSPOT_G_BIT   2
#define THWOTTWEW_TEMP_HOTSPOT_M_BIT   3
#define THWOTTWEW_TEMP_MEM_BIT         4
#define THWOTTWEW_TEMP_VW_GFX_BIT      5
#define THWOTTWEW_TEMP_VW_MEM0_BIT     6
#define THWOTTWEW_TEMP_VW_MEM1_BIT     7
#define THWOTTWEW_TEMP_VW_SOC_BIT      8
#define THWOTTWEW_TEMP_VW_U_BIT        9
#define THWOTTWEW_TEMP_WIQUID0_BIT     10
#define THWOTTWEW_TEMP_WIQUID1_BIT     11
#define THWOTTWEW_TEMP_PWX_BIT         12
#define THWOTTWEW_TDC_GFX_BIT          13
#define THWOTTWEW_TDC_SOC_BIT          14
#define THWOTTWEW_TDC_U_BIT            15
#define THWOTTWEW_PPT0_BIT             16
#define THWOTTWEW_PPT1_BIT             17
#define THWOTTWEW_PPT2_BIT             18
#define THWOTTWEW_PPT3_BIT             19
#define THWOTTWEW_FIT_BIT              20
#define THWOTTWEW_GFX_APCC_PWUS_BIT    21
#define THWOTTWEW_COUNT                22

// FW DState Featuwes Contwow Bits
#define FW_DSTATE_SOC_UWV_BIT               0
#define FW_DSTATE_G6_HSW_BIT                1
#define FW_DSTATE_G6_PHY_VMEMP_OFF_BIT      2
#define FW_DSTATE_SMN_DS_BIT                3
#define FW_DSTATE_MP1_WHISPEW_MODE_BIT      4
#define FW_DSTATE_SOC_WIV_MIN_BIT           5
#define FW_DSTATE_SOC_PWW_PWWDN_BIT         6
#define FW_DSTATE_MEM_PWW_PWWDN_BIT         7
#define FW_DSTATE_MAWW_AWWOC_BIT            8
#define FW_DSTATE_MEM_PSI_BIT               9
#define FW_DSTATE_HSW_NON_STWOBE_BIT        10
#define FW_DSTATE_MP0_ENTEW_WFI_BIT         11
#define FW_DSTATE_U_UWV_BIT                 12
#define FW_DSTATE_MAWW_FWUSH_BIT            13
#define FW_DSTATE_SOC_PSI_BIT               14
#define FW_DSTATE_U_PSI_BIT                 15
#define FW_DSTATE_UCP_DS_BIT                16
#define FW_DSTATE_CSWCWK_DS_BIT             17
#define FW_DSTATE_MMHUB_INTEWWOCK_BIT       18
#define FW_DSTATE_D0i3_2_QUIET_FW_BIT       19
#define FW_DSTATE_CWDO_PWG_BIT              20
#define FW_DSTATE_DF_PWW_PWWDN_BIT          21
#define FW_DSTATE_U_WOW_PWW_MODE_EN_BIT     22
#define FW_DSTATE_GFX_PSI6_BIT              23
#define FW_DSTATE_GFX_VW_PWW_STAGE_BIT      24

//WED Dispway Mask & Contwow Bits
#define WED_DISPWAY_GFX_DPM_BIT            0
#define WED_DISPWAY_PCIE_BIT               1
#define WED_DISPWAY_EWWOW_BIT              2


#define MEM_TEMP_WEAD_OUT_OF_BAND_BIT          0
#define MEM_TEMP_WEAD_IN_BAND_WEFWESH_BIT      1
#define MEM_TEMP_WEAD_IN_BAND_DUMMY_PSTATE_BIT 2

typedef enum {
  SMAWTSHIFT_VEWSION_1,
  SMAWTSHIFT_VEWSION_2,
  SMAWTSHIFT_VEWSION_3,
} SMAWTSHIFT_VEWSION_e;

typedef enum {
  FOPT_CAWC_AC_CAWC_DC,
  FOPT_PPTABWE_AC_CAWC_DC,
  FOPT_CAWC_AC_PPTABWE_DC,
  FOPT_PPTABWE_AC_PPTABWE_DC,
} FOPT_CAWC_e;

typedef enum {
  DWAM_BIT_WIDTH_DISABWED = 0,
  DWAM_BIT_WIDTH_X_8 = 8,
  DWAM_BIT_WIDTH_X_16 = 16,
  DWAM_BIT_WIDTH_X_32 = 32,
  DWAM_BIT_WIDTH_X_64 = 64,
  DWAM_BIT_WIDTH_X_128 = 128,
  DWAM_BIT_WIDTH_COUNT,
} DWAM_BIT_WIDTH_TYPE_e;

//I2C Intewface
#define NUM_I2C_CONTWOWWEWS                8

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
	I2C_CONTWOWWEW_NAME_VW_VMEMP,
	I2C_CONTWOWWEW_NAME_VW_VDDIO,
	I2C_CONTWOWWEW_NAME_WIQUID0,
	I2C_CONTWOWWEW_NAME_WIQUID1,
	I2C_CONTWOWWEW_NAME_PWX,
	I2C_CONTWOWWEW_NAME_FAN_INTAKE,
	I2C_CONTWOWWEW_NAME_COUNT,
} I2cContwowwewName_e;

typedef enum {
  I2C_CONTWOWWEW_THWOTTWEW_TYPE_NONE = 0,
  I2C_CONTWOWWEW_THWOTTWEW_VW_GFX,
  I2C_CONTWOWWEW_THWOTTWEW_VW_SOC,
  I2C_CONTWOWWEW_THWOTTWEW_VW_VMEMP,
  I2C_CONTWOWWEW_THWOTTWEW_VW_VDDIO,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID0,
  I2C_CONTWOWWEW_THWOTTWEW_WIQUID1,
  I2C_CONTWOWWEW_THWOTTWEW_PWX,
  I2C_CONTWOWWEW_THWOTTWEW_FAN_INTAKE,
  I2C_CONTWOWWEW_THWOTTWEW_INA3221,
  I2C_CONTWOWWEW_THWOTTWEW_COUNT,
} I2cContwowwewThwottwew_e;

typedef enum {
	I2C_CONTWOWWEW_PWOTOCOW_VW_XPDE132G5,
	I2C_CONTWOWWEW_PWOTOCOW_VW_IW35217,
	I2C_CONTWOWWEW_PWOTOCOW_TMP_MAX31875,
	I2C_CONTWOWWEW_PWOTOCOW_INA3221,
	I2C_CONTWOWWEW_PWOTOCOW_TMP_MAX6604,
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

typedef stwuct {
  uint64_t mca_umc_status;
  uint64_t mca_umc_addw;

  uint16_t ce_count_wo_chip;
  uint16_t ce_count_hi_chip;

  uint32_t eccPadding;
} EccInfo_t;

typedef stwuct {
  EccInfo_t  EccInfo[24];
} EccInfoTabwe_t;

//D3HOT sequences
typedef enum {
  BACO_SEQUENCE,
  MSW_SEQUENCE,
  BAMACO_SEQUENCE,
  UWPS_SEQUENCE,
  D3HOT_SEQUENCE_COUNT,
} D3HOTSequence_e;

//This is awigned with WSMU PGFSM Wegistew Mapping
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
  DCS_AWCH_DISABWED,
  DCS_AWCH_FADCS,
  DCS_AWCH_ASYNC,
} DCS_AWCH_e;

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
  PPCWK_DISPCWK,
  PPCWK_DPPCWK,
  PPCWK_DPWEFCWK,
  PPCWK_DCFCWK,
  PPCWK_DTBCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  VOWTAGE_MODE_PPTABWE = 0,
  VOWTAGE_MODE_FUSES,
  VOWTAGE_MODE_COUNT,
} VOWTAGE_MODE_e;


typedef enum {
  AVFS_VOWTAGE_GFX = 0,
  AVFS_VOWTAGE_SOC,
  AVFS_VOWTAGE_COUNT,
} AVFS_VOWTAGE_TYPE_e;

typedef enum {
  AVFS_TEMP_COWD = 0,
  AVFS_TEMP_HOT,
  AVFS_TEMP_COUNT,
} AVFS_TEMP_e;

typedef enum {
  AVFS_D_G,
  AVFS_D_M_B,
  AVFS_D_M_S,
  AVFS_D_COUNT,
} AVFS_D_e;

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

typedef stwuct {
  uint8_t        Padding;
  uint8_t        SnapToDiscwete;      // 0 - Fine gwained DPM, 1 - Discwete DPM
  uint8_t        NumDiscweteWevews;   // Set to 2 (Fmin, Fmax) when using fine gwained DPM, othewwise set to # discwete wevews used
  uint8_t        CawcuwateFopt;       // Indication whethew FW shouwd cawcuwate Fopt ow use vawues bewow. Wefewence FOPT_CAWC_e
  WineawInt_t    ConvewsionToAvfsCwk; // Twansfew function to AVFS Cwock (GHz->GHz)
  uint32_t       Padding3[3];
  uint16_t       Padding4;
  uint16_t       FoptimawDc;          //Foptimaw fwequency in DC powew mode.
  uint16_t       FoptimawAc;          //Foptimaw fwequency in AC powew mode.
  uint16_t       Padding2;
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
  TEMP_HOTSPOT_G,
  TEMP_HOTSPOT_M,
  TEMP_MEM,
  TEMP_VW_GFX,
  TEMP_VW_MEM0,
  TEMP_VW_MEM1,
  TEMP_VW_SOC,
  TEMP_VW_U,
  TEMP_WIQUID0,
  TEMP_WIQUID1,
  TEMP_PWX,
  TEMP_COUNT,
} TEMP_e;

typedef enum {
  TDC_THWOTTWEW_GFX,
  TDC_THWOTTWEW_SOC,
  TDC_THWOTTWEW_U,
  TDC_THWOTTWEW_COUNT
} TDC_THWOTTWEW_e;

typedef enum {
  SVI_PWANE_GFX,
  SVI_PWANE_SOC,
  SVI_PWANE_VMEMP,
  SVI_PWANE_VDDIO_MEM,
  SVI_PWANE_U,
  SVI_PWANE_COUNT,
} SVI_PWANE_e;

typedef enum {
  PMFW_VOWT_PWANE_GFX,
  PMFW_VOWT_PWANE_SOC,
  PMFW_VOWT_PWANE_COUNT
} PMFW_VOWT_PWANE_e;

typedef enum {
  CUSTOMEW_VAWIANT_WOW,
  CUSTOMEW_VAWIANT_FAWCON,
  CUSTOMEW_VAWIANT_COUNT,
} CUSTOMEW_VAWIANT_e;

typedef enum {
  POWEW_SOUWCE_AC,
  POWEW_SOUWCE_DC,
  POWEW_SOUWCE_COUNT,
} POWEW_SOUWCE_e;

typedef enum {
  MEM_VENDOW_PWACEHOWDEW0,
  MEM_VENDOW_SAMSUNG,
  MEM_VENDOW_INFINEON,
  MEM_VENDOW_EWPIDA,
  MEM_VENDOW_ETWON,
  MEM_VENDOW_NANYA,
  MEM_VENDOW_HYNIX,
  MEM_VENDOW_MOSEW,
  MEM_VENDOW_WINBOND,
  MEM_VENDOW_ESMT,
  MEM_VENDOW_PWACEHOWDEW1,
  MEM_VENDOW_PWACEHOWDEW2,
  MEM_VENDOW_PWACEHOWDEW3,
  MEM_VENDOW_PWACEHOWDEW4,
  MEM_VENDOW_PWACEHOWDEW5,
  MEM_VENDOW_MICWON,
  MEM_VENDOW_COUNT,
} MEM_VENDOW_e;

typedef enum {
  PP_GWTAVFS_HW_CPO_CTW_ZONE0,
  PP_GWTAVFS_HW_CPO_CTW_ZONE1,
  PP_GWTAVFS_HW_CPO_CTW_ZONE2,
  PP_GWTAVFS_HW_CPO_CTW_ZONE3,
  PP_GWTAVFS_HW_CPO_CTW_ZONE4,
  PP_GWTAVFS_HW_CPO_EN_0_31_ZONE0,
  PP_GWTAVFS_HW_CPO_EN_32_63_ZONE0,
  PP_GWTAVFS_HW_CPO_EN_0_31_ZONE1,
  PP_GWTAVFS_HW_CPO_EN_32_63_ZONE1,
  PP_GWTAVFS_HW_CPO_EN_0_31_ZONE2,
  PP_GWTAVFS_HW_CPO_EN_32_63_ZONE2,
  PP_GWTAVFS_HW_CPO_EN_0_31_ZONE3,
  PP_GWTAVFS_HW_CPO_EN_32_63_ZONE3,
  PP_GWTAVFS_HW_CPO_EN_0_31_ZONE4,
  PP_GWTAVFS_HW_CPO_EN_32_63_ZONE4,
  PP_GWTAVFS_HW_ZONE0_VF,
  PP_GWTAVFS_HW_ZONE1_VF1,
  PP_GWTAVFS_HW_ZONE2_VF2,
  PP_GWTAVFS_HW_ZONE3_VF3,
  PP_GWTAVFS_HW_VOWTAGE_GB,
  PP_GWTAVFS_HW_CPOSCAWINGCTWW_ZONE0,
  PP_GWTAVFS_HW_CPOSCAWINGCTWW_ZONE1,
  PP_GWTAVFS_HW_CPOSCAWINGCTWW_ZONE2,
  PP_GWTAVFS_HW_CPOSCAWINGCTWW_ZONE3,
  PP_GWTAVFS_HW_CPOSCAWINGCTWW_ZONE4,
  PP_GWTAVFS_HW_WESEWVED_0,
  PP_GWTAVFS_HW_WESEWVED_1,
  PP_GWTAVFS_HW_WESEWVED_2,
  PP_GWTAVFS_HW_WESEWVED_3,
  PP_GWTAVFS_HW_WESEWVED_4,
  PP_GWTAVFS_HW_WESEWVED_5,
  PP_GWTAVFS_HW_WESEWVED_6,
  PP_GWTAVFS_HW_FUSE_COUNT,
} PP_GWTAVFS_HW_FUSE_e;

typedef enum {
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z1_HOT_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z1_COWD_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z2_HOT_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z2_COWD_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z3_HOT_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z3_COWD_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z4_HOT_T0,
  PP_GWTAVFS_FW_COMMON_PPVMIN_Z4_COWD_T0,
  PP_GWTAVFS_FW_COMMON_SWAM_WM_Z0,
  PP_GWTAVFS_FW_COMMON_SWAM_WM_Z1,
  PP_GWTAVFS_FW_COMMON_SWAM_WM_Z2,
  PP_GWTAVFS_FW_COMMON_SWAM_WM_Z3,
  PP_GWTAVFS_FW_COMMON_SWAM_WM_Z4,
  PP_GWTAVFS_FW_COMMON_FUSE_COUNT,
} PP_GWTAVFS_FW_COMMON_FUSE_e;

typedef enum {
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_NEG_1,
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_0,
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_1,
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_2,
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_3,
  PP_GWTAVFS_FW_SEP_FUSE_GB1_PWW_VOWTAGE_4,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_NEG_1,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_0,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_1,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_2,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_3,
  PP_GWTAVFS_FW_SEP_FUSE_GB2_PWW_VOWTAGE_4,
  PP_GWTAVFS_FW_SEP_FUSE_VF_NEG_1_FWEQUENCY,
  PP_GWTAVFS_FW_SEP_FUSE_VF4_FWEQUENCY,
  PP_GWTAVFS_FW_SEP_FUSE_FWEQUENCY_TO_COUNT_SCAWEW_0,
  PP_GWTAVFS_FW_SEP_FUSE_FWEQUENCY_TO_COUNT_SCAWEW_1,
  PP_GWTAVFS_FW_SEP_FUSE_FWEQUENCY_TO_COUNT_SCAWEW_2,
  PP_GWTAVFS_FW_SEP_FUSE_FWEQUENCY_TO_COUNT_SCAWEW_3,
  PP_GWTAVFS_FW_SEP_FUSE_FWEQUENCY_TO_COUNT_SCAWEW_4,
  PP_GWTAVFS_FW_SEP_FUSE_COUNT,
} PP_GWTAVFS_FW_SEP_FUSE_e;

#define PP_NUM_WTAVFS_PWW_ZONES 5

#define PP_OD_FEATUWE_GFX_VF_CUWVE_BIT  0
#define PP_OD_FEATUWE_PPT_BIT       2
#define PP_OD_FEATUWE_FAN_CUWVE_BIT 3
#define PP_OD_FEATUWE_GFXCWK_BIT      7
#define PP_OD_FEATUWE_UCWK_BIT      8
#define PP_OD_FEATUWE_ZEWO_FAN_BIT      9
#define PP_OD_FEATUWE_TEMPEWATUWE_BIT 10
#define PP_OD_FEATUWE_COUNT 13

// VBIOS ow PPWIB configuwes tewemetwy swope and offset. Onwy swope expected to be set fow SVI3
// Swope Q1.7, Offset Q1.2
typedef stwuct {
  int8_t   Offset; // in Amps
  uint8_t  Padding;
  uint16_t MaxCuwwent; // in Amps
} SviTewemetwyScawe_t;

#define PP_NUM_OD_VF_CUWVE_POINTS PP_NUM_WTAVFS_PWW_ZONES + 1

typedef enum {
	FAN_MODE_AUTO = 0,
	FAN_MODE_MANUAW_WINEAW,
} FanMode_e;

typedef stwuct {
  uint32_t FeatuweCtwwMask;

  //Vowtage contwow
  int16_t                VowtageOffsetPewZoneBoundawy[PP_NUM_OD_VF_CUWVE_POINTS];

  uint32_t               Wesewved;

  //Fwequency changes
  int16_t                GfxcwkFmin;           // MHz
  int16_t                GfxcwkFmax;           // MHz
  uint16_t               UcwkFmin;             // MHz
  uint16_t               UcwkFmax;             // MHz

  //PPT
  int16_t                Ppt;         // %
  int16_t                Tdc;

  //Fan contwow
  uint8_t                FanWineawPwmPoints[NUM_OD_FAN_MAX_POINTS];
  uint8_t                FanWineawTempPoints[NUM_OD_FAN_MAX_POINTS];
  uint16_t               FanMinimumPwm;
  uint16_t               AcousticTawgetWpmThweshowd;
  uint16_t               AcousticWimitWpmThweshowd;
  uint16_t               FanTawgetTempewatuwe; // Degwee Cewcius
  uint8_t                FanZewoWpmEnabwe;
  uint8_t                FanZewoWpmStopTemp;
  uint8_t                FanMode;
  uint8_t                MaxOpTemp;

  uint32_t               Spawe[13];
  uint32_t               MmHubPadding[8]; // SMU intewnaw use. Adding hewe instead of extewnaw as a wowkawound
} OvewDwiveTabwe_t;

typedef stwuct {
  OvewDwiveTabwe_t OvewDwiveTabwe;

} OvewDwiveTabweExtewnaw_t;

typedef stwuct {
  uint32_t FeatuweCtwwMask;

  int16_t VowtageOffsetPewZoneBoundawy;
  uint16_t               Wesewved1;

  uint16_t               Wesewved2;

  int16_t               GfxcwkFmin;           // MHz
  int16_t               GfxcwkFmax;           // MHz
  uint16_t               UcwkFmin;             // MHz
  uint16_t               UcwkFmax;             // MHz

  //PPT
  int16_t                Ppt;         // %
  int16_t                Tdc;

  uint8_t                FanWineawPwmPoints;
  uint8_t                FanWineawTempPoints;
  uint16_t               FanMinimumPwm;
  uint16_t               AcousticTawgetWpmThweshowd;
  uint16_t               AcousticWimitWpmThweshowd;
  uint16_t               FanTawgetTempewatuwe; // Degwee Cewcius
  uint8_t                FanZewoWpmEnabwe;
  uint8_t                FanZewoWpmStopTemp;
  uint8_t                FanMode;
  uint8_t                MaxOpTemp;

  uint32_t               Spawe[13];

} OvewDwiveWimits_t;


typedef enum {
  BOAWD_GPIO_SMUIO_0,
  BOAWD_GPIO_SMUIO_1,
  BOAWD_GPIO_SMUIO_2,
  BOAWD_GPIO_SMUIO_3,
  BOAWD_GPIO_SMUIO_4,
  BOAWD_GPIO_SMUIO_5,
  BOAWD_GPIO_SMUIO_6,
  BOAWD_GPIO_SMUIO_7,
  BOAWD_GPIO_SMUIO_8,
  BOAWD_GPIO_SMUIO_9,
  BOAWD_GPIO_SMUIO_10,
  BOAWD_GPIO_SMUIO_11,
  BOAWD_GPIO_SMUIO_12,
  BOAWD_GPIO_SMUIO_13,
  BOAWD_GPIO_SMUIO_14,
  BOAWD_GPIO_SMUIO_15,
  BOAWD_GPIO_SMUIO_16,
  BOAWD_GPIO_SMUIO_17,
  BOAWD_GPIO_SMUIO_18,
  BOAWD_GPIO_SMUIO_19,
  BOAWD_GPIO_SMUIO_20,
  BOAWD_GPIO_SMUIO_21,
  BOAWD_GPIO_SMUIO_22,
  BOAWD_GPIO_SMUIO_23,
  BOAWD_GPIO_SMUIO_24,
  BOAWD_GPIO_SMUIO_25,
  BOAWD_GPIO_SMUIO_26,
  BOAWD_GPIO_SMUIO_27,
  BOAWD_GPIO_SMUIO_28,
  BOAWD_GPIO_SMUIO_29,
  BOAWD_GPIO_SMUIO_30,
  BOAWD_GPIO_SMUIO_31,
  MAX_BOAWD_GPIO_SMUIO_NUM,
  BOAWD_GPIO_DC_GEN_A,
  BOAWD_GPIO_DC_GEN_B,
  BOAWD_GPIO_DC_GEN_C,
  BOAWD_GPIO_DC_GEN_D,
  BOAWD_GPIO_DC_GEN_E,
  BOAWD_GPIO_DC_GEN_F,
  BOAWD_GPIO_DC_GEN_G,
  BOAWD_GPIO_DC_GENWK_CWK,
  BOAWD_GPIO_DC_GENWK_VSYNC,
  BOAWD_GPIO_DC_SWAPWOCK_A,
  BOAWD_GPIO_DC_SWAPWOCK_B,
} BOAWD_GPIO_TYPE_e;

#define INVAWID_BOAWD_GPIO 0xFF

#define MAWKETING_BASE_CWOCKS         0
#define MAWKETING_GAME_CWOCKS         1
#define MAWKETING_BOOST_CWOCKS        2

typedef stwuct {
  //PWW 0
  uint16_t InitGfxcwk_bypass;
  uint16_t InitSoccwk;
  uint16_t InitMp0cwk;
  uint16_t InitMpiocwk;
  uint16_t InitSmncwk;
  uint16_t InitUcpcwk;
  uint16_t InitCswcwk;
  //PWW 1

  uint16_t InitDpwefcwk;
  uint16_t InitDcfcwk;
  uint16_t InitDtbcwk;
  //PWW 2
  uint16_t InitDcwk; //assume same DCWK/VCWK fow both instances
  uint16_t InitVcwk;
  // PWW 3
  uint16_t InitUsbdfscwk;
  uint16_t InitMp1cwk;
  uint16_t InitWcwk;
  uint16_t InitBaco400cwk_bypass;
  uint16_t InitBaco1200cwk_bypass;
  uint16_t InitBaco700cwk_bypass;
  // PWW 4
  uint16_t InitFcwk;
  // PWW 5
  uint16_t InitGfxcwk_cwkb;

  //PWW 6
  uint8_t InitUcwkDPMState;    // =0,1,2,3, fwequency fwom FweqTabweUcwk

  uint8_t Padding[3];

  uint32_t InitVcoFweqPww0;
  uint32_t InitVcoFweqPww1;
  uint32_t InitVcoFweqPww2;
  uint32_t InitVcoFweqPww3;
  uint32_t InitVcoFweqPww4;
  uint32_t InitVcoFweqPww5;
  uint32_t InitVcoFweqPww6;

  //encoding wiww change depending on SVI2/SVI3
  uint16_t InitGfx;     // In mV(Q2) ,  shouwd be 0?
  uint16_t InitSoc;     // In mV(Q2)
  uint16_t InitU; // In Mv(Q2)

  uint16_t Padding2;

  uint32_t Spawe[8];

} BootVawues_t;


typedef stwuct {
   uint16_t Powew[PPT_THWOTTWEW_COUNT][POWEW_SOUWCE_COUNT]; // Watts
  uint16_t Tdc[TDC_THWOTTWEW_COUNT];             // Amps

  uint16_t Tempewatuwe[TEMP_COUNT]; // Cewsius

  uint8_t  PwmWimitMin;
  uint8_t  PwmWimitMax;
  uint8_t  FanTawgetTempewatuwe;
  uint8_t  Spawe1[1];

  uint16_t AcousticTawgetWpmThweshowdMin;
  uint16_t AcousticTawgetWpmThweshowdMax;

  uint16_t AcousticWimitWpmThweshowdMin;
  uint16_t AcousticWimitWpmThweshowdMax;

  uint16_t  PccWimitMin;
  uint16_t  PccWimitMax;

  uint16_t  FanStopTempMin;
  uint16_t  FanStopTempMax;
  uint16_t  FanStawtTempMin;
  uint16_t  FanStawtTempMax;

  uint16_t  PowewMinPpt0[POWEW_SOUWCE_COUNT];
  uint32_t Spawe[11];

} MsgWimits_t;

typedef stwuct {
  uint16_t BaseCwockAc;
  uint16_t GameCwockAc;
  uint16_t BoostCwockAc;
  uint16_t BaseCwockDc;
  uint16_t GameCwockDc;
  uint16_t BoostCwockDc;

  uint32_t Wesewved[4];
} DwivewWepowtedCwocks_t;

typedef stwuct {
  uint8_t           DcBtcEnabwed;
  uint8_t           Padding[3];

  uint16_t          DcTow;            // mV Q2
  uint16_t          DcBtcGb;       // mV Q2

  uint16_t          DcBtcMin;       // mV Q2
  uint16_t          DcBtcMax;       // mV Q2

  WineawInt_t       DcBtcGbScawaw;

} AvfsDcBtcPawams_t;

typedef stwuct {
  uint16_t       AvfsTemp[AVFS_TEMP_COUNT]; //in degwees C
  uint16_t      VftFMin;  // in MHz
  uint16_t      VInvewsion; // in mV Q2
  QuadwaticInt_t qVft[AVFS_TEMP_COUNT];
  QuadwaticInt_t qAvfsGb;
  QuadwaticInt_t qAvfsGb2;
} AvfsFuseOvewwide_t;

typedef stwuct {
  // SECTION: Vewsion

  uint32_t Vewsion; // shouwd be unique to each SKU(i.e if any vawue changes in bewow stwuctuwe then this vawue must be diffewent)

  // SECTION: Featuwe Contwow
  uint32_t FeatuwesToWun[NUM_FEATUWES / 32]; // Featuwes that PMFW wiww attempt to enabwe. Use FEATUWE_*_BIT as mapping

  // SECTION: Miscewwaneous Configuwation
  uint8_t      TotawPowewConfig;    // Detewmines how PMFW cawcuwates the powew. Use defines fwom PwwConfig_e
  uint8_t      CustomewVawiant; //To specify if this PPTabwe is intended fow a pawticuwaw customew. Use defines fwom CUSTOMEW_VAWIANT_e
  uint8_t      MemowyTempewatuweTypeMask; // Bit mapping indicating which methods of memowy tempewatuwe weading awe enabwed. Use defines fwom MEM_TEMP_*BIT
  uint8_t      SmawtShiftVewsion; // Detewmine what SmawtShift featuwe vewsion is suppowted Use defines fwom SMAWTSHIFT_VEWSION_e

  // SECTION: Infwastwuctuwe Wimits
  uint16_t SocketPowewWimitAc[PPT_THWOTTWEW_COUNT]; // In Watts. Powew wimit that PMFW attempts to contwow to in AC mode. Muwtipwe wimits suppowted
  uint16_t SocketPowewWimitDc[PPT_THWOTTWEW_COUNT];  // In Watts. Powew wimit that PMFW attempts to contwow to in DC mode. Muwtipwe wimits suppowted

  uint16_t SocketPowewWimitSmawtShift2; // In Watts. Powew wimit used SmawtShift

  //if set to 1, SocketPowewWimitAc and SocketPowewWimitDc wiww be intewpweted as wegacy pwogwams(i.e absowute powew). If 0, aww except index 0 wiww be scawaws
  //wewative index 0
  uint8_t  EnabweWegacyPptWimit;
  uint8_t  UseInputTewemetwy; //appwicabwe to SVI3 onwy and onwy to be set if VWs suppowt
  uint8_t  SmawtShiftMinWepowtedPptinDcs; //minimum possibwe active powew consumption fow this SKU. Used fow SmawtShift powew wepowting

  uint8_t  PaddingPpt[1];

  uint16_t VwTdcWimit[TDC_THWOTTWEW_COUNT];             // In Ampewes. Cuwwent wimit associated with VW weguwatow maximum tempewatuwe

  uint16_t PwatfowmTdcWimit[TDC_THWOTTWEW_COUNT];             // In Ampewes. Cuwwent wimit associated with pwatfowm maximum tempewatuwe pew VW cuwwent waiw

  uint16_t TempewatuweWimit[TEMP_COUNT]; // In degwees Cewsius. Tempewatuwe wimit associated with each input

  uint16_t HwCtfTempWimit; // In degwees Cewsius. Tempewatuwe above which HW wiww twiggew CTF. Consumed by VBIOS onwy

  uint16_t PaddingInfwa;

  // Pew yeaw nowmawized Vmax state faiwuwe wates (sum of the two domains divided by wife time in yeaws)
  uint32_t FitContwowwewFaiwuweWateWimit; //in IEEE fwoat
  //Expected GFX Duty Cycwe at Vmax.
  uint32_t FitContwowwewGfxDutyCycwe; // in IEEE fwoat
  //Expected SOC Duty Cycwe at Vmax.
  uint32_t FitContwowwewSocDutyCycwe; // in IEEE fwoat

  //This offset wiww be deducted fwom the contwowwew output to befowe it goes thwough the SOC Vset wimitew bwock.
  uint32_t FitContwowwewSocOffset;  //in IEEE fwoat

  uint32_t     GfxApccPwusWesidencyWimit; // Pewcentage vawue. Used by APCC+ contwowwew to contwow PCC wesidency to some vawue

  // SECTION: Thwottwew settings
  uint32_t ThwottwewContwowMask;   // See THWOTTWEW_*_BIT fow mapping

  // SECTION: FW DSTATE Settings
  uint32_t FwDStateMask;           // See FW_DSTATE_*_BIT fow mapping

  // SECTION: Vowtage Contwow Pawametews
  uint16_t  UwvVowtageOffset[PMFW_VOWT_PWANE_COUNT]; // In mV(Q2). UWV offset used in eithew GFX_UWV ow SOC_UWV(pawt of FW_DSTATE)

  uint16_t     UwvVowtageOffsetU; // In mV(Q2). UWV offset used in eithew U_UWV(pawt of FW_DSTATE)
  uint16_t     DeepUwvVowtageOffsetSoc;        // In mV(Q2)  Wong Idwe Vmin (deep UWV), fow VDD_SOC as pawt of FW_DSTATE

  // Vowtage Wimits
  uint16_t     DefauwtMaxVowtage[PMFW_VOWT_PWANE_COUNT]; // In mV(Q2) Maximum vowtage without FIT contwowwew enabwed
  uint16_t     BoostMaxVowtage[PMFW_VOWT_PWANE_COUNT]; // In mV(Q2) Maximum vowtage with FIT contwowwew enabwed

  //Vmin Optimizations
  int16_t         VminTempHystewsis[PMFW_VOWT_PWANE_COUNT]; // Cewsius Tempewatuwe hystewesis fow switching between wow/high tempewatuwe vawues fow Vmin
  int16_t         VminTempThweshowd[PMFW_VOWT_PWANE_COUNT]; // Cewsius Tempewatuwe thweshowd fow switching between wow/high tempewatuwe vawues fow Vmin
  uint16_t        Vmin_Hot_T0[PMFW_VOWT_PWANE_COUNT];            //In mV(Q2) Initiaw (pwe-aging) Vset to be used at hot.
  uint16_t        Vmin_Cowd_T0[PMFW_VOWT_PWANE_COUNT];           //In mV(Q2) Initiaw (pwe-aging) Vset to be used at cowd.
  uint16_t        Vmin_Hot_Eow[PMFW_VOWT_PWANE_COUNT];           //In mV(Q2) End-of-wife Vset to be used at hot.
  uint16_t        Vmin_Cowd_Eow[PMFW_VOWT_PWANE_COUNT];          //In mV(Q2) End-of-wife Vset to be used at cowd.
  uint16_t        Vmin_Aging_Offset[PMFW_VOWT_PWANE_COUNT];      //In mV(Q2) Wowst-case aging mawgin
  uint16_t        Spawe_Vmin_Pwat_Offset_Hot[PMFW_VOWT_PWANE_COUNT];   //In mV(Q2) Pwatfowm offset appwy to T0 Hot
  uint16_t        Spawe_Vmin_Pwat_Offset_Cowd[PMFW_VOWT_PWANE_COUNT];  //In mV(Q2) Pwatfowm offset appwy to T0 Cowd

  //This is a fixed/minimum VMIN aging degwadation offset which is appwied at T0. This wefwects the minimum amount of aging awweady accounted fow.
  uint16_t        VcBtcFixedVminAgingOffset[PMFW_VOWT_PWANE_COUNT];
  //Wineaw offset ow GB tewm to account fow mis-cowwewation between PSM and Vmin shift twends acwoss pawts.
  uint16_t        VcBtcVmin2PsmDegwationGb[PMFW_VOWT_PWANE_COUNT];
  //Scawaw coefficient of the PSM aging degwadation function
  uint32_t        VcBtcPsmA[PMFW_VOWT_PWANE_COUNT];                   // A_PSM
  //Exponentiaw coefficient of the PSM aging degwadation function
  uint32_t        VcBtcPsmB[PMFW_VOWT_PWANE_COUNT];                   // B_PSM
  //Scawaw coefficient of the VMIN aging degwadation function. Specified as wowst case between hot and cowd.
  uint32_t        VcBtcVminA[PMFW_VOWT_PWANE_COUNT];                  // A_VMIN
  //Exponentiaw coefficient of the VMIN aging degwadation function. Specified as wowst case between hot and cowd.
  uint32_t        VcBtcVminB[PMFW_VOWT_PWANE_COUNT];                  // B_VMIN

  uint8_t        PewPawtVminEnabwed[PMFW_VOWT_PWANE_COUNT];
  uint8_t        VcBtcEnabwed[PMFW_VOWT_PWANE_COUNT];

  uint16_t SocketPowewWimitAcTau[PPT_THWOTTWEW_COUNT]; // Time constant of WPF in ms
  uint16_t SocketPowewWimitDcTau[PPT_THWOTTWEW_COUNT]; // Time constant of WPF in ms

  QuadwaticInt_t Vmin_dwoop;
  uint32_t       SpaweVmin[9];


  //SECTION: DPM Configuwation 1
  DpmDescwiptow_t DpmDescwiptow[PPCWK_COUNT];

  uint16_t       FweqTabweGfx      [NUM_GFXCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweVcwk     [NUM_VCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweDcwk     [NUM_DCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweSoccwk   [NUM_SOCCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweUcwk     [NUM_UCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweDispcwk  [NUM_DISPCWK_DPM_WEVEWS ];     // In MHz
  uint16_t       FweqTabweDppCwk   [NUM_DPPCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweDpwefcwk [NUM_DPWEFCWK_DPM_WEVEWS];     // In MHz
  uint16_t       FweqTabweDcfcwk   [NUM_DCFCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweDtbcwk   [NUM_DTBCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];     // In MHz

  uint32_t       DcModeMaxFweq     [PPCWK_COUNT            ];     // In MHz

  // SECTION: DPM Configuwation 2
  uint16_t       Mp0cwkFweq        [NUM_MP0CWK_DPM_WEVEWS];       // in MHz
  uint16_t       Mp0DpmVowtage     [NUM_MP0CWK_DPM_WEVEWS];       // mV(Q2)

  uint8_t         GfxcwkSpawe[2];
  uint16_t        GfxcwkFweqCap;

  //GFX Idwe Powew Settings
  uint16_t        GfxcwkFgfxoffEntwy;   // in Mhz
  uint16_t        GfxcwkFgfxoffExitImu; // in Mhz
  uint16_t        GfxcwkFgfxoffExitWwc; // in Mhz
  uint16_t        GfxcwkThwottweCwock;  //Used pwimawiwy in DCS
  uint8_t         EnabweGfxPowewStagesGpio; //Genwk_vsync GPIO fwag used to contwow gfx powew stages
  uint8_t         GfxIdwePadding;

  uint8_t          SmsWepaiwWWCKCwkDivEn;
  uint8_t          SmsWepaiwWWCKCwkDivVaw;
  uint8_t          GfxOffEntwyEawwyMGCGEn;
  uint8_t          GfxOffEntwyFowceCGCGEn;
  uint8_t          GfxOffEntwyFowceCGCGDewayEn;
  uint8_t          GfxOffEntwyFowceCGCGDewayVaw; // in micwoseconds

  uint16_t        GfxcwkFweqGfxUwv; // in MHz
  uint8_t         GfxIdwePadding2[2];

  uint32_t        GfxOffEntwyHystewesis;
  uint32_t        GfxoffSpawe[15];

  // GFX GPO
  uint32_t        DfwwBtcMastewScawewM;
  int32_t         DfwwBtcMastewScawewB;
  uint32_t        DfwwBtcSwaveScawewM;
  int32_t         DfwwBtcSwaveScawewB;

  uint32_t        DfwwPccAsWaitCtww; //GDFWW_AS_WAIT_CTWW_PCC wegistew vawue to be passed to WWC msg
  uint32_t        DfwwPccAsStepCtww; //GDFWW_AS_STEP_CTWW_PCC wegistew vawue to be passed to WWC msg

  uint32_t        DfwwW2FwequencyBoostM; //Unitwess (fwoat)
  uint32_t        DfwwW2FwequencyBoostB; //In MHz (integew)
  uint32_t        GfxGpoSpawe[8];

  // GFX DCS

  uint16_t        DcsGfxOffVowtage;     //Vowtage in mV(Q2) appwied to VDDGFX when entewing DCS GFXOFF phase
  uint16_t        PaddingDcs;

  uint16_t        DcsMinGfxOffTime;     //Minimum amount of time PMFW shuts GFX OFF as pawt of GFX DCS phase
  uint16_t        DcsMaxGfxOffTime;      //Maximum amount of time PMFW can shut GFX OFF as pawt of GFX DCS phase at a stwetch.

  uint32_t        DcsMinCweditAccum;    //Min amount of positive cwedit accumuwation befowe waking GFX up as pawt of DCS.

  uint16_t        DcsExitHystewesis;    //The min amount of time powew cwedit accumuwatow shouwd have a vawue > 0 befowe SMU exits the DCS thwottwing phase.
  uint16_t        DcsTimeout;           //This is the amount of time SMU FW waits fow WWC to put GFX into GFXOFF befowe wevewting to the fawwback mechanism of thwottwing GFXCWK to Fmin.

  uint8_t         FoptEnabwed;
  uint8_t         DcsSpawe2[3];
  uint32_t        DcsFoptM;             //Tuning pawamtews to shift Fopt cawcuwation
  uint32_t        DcsFoptB;             //Tuning pawamtews to shift Fopt cawcuwation

  uint32_t        DcsSpawe[11];

  // UCWK section
  uint16_t     ShadowFweqTabweUcwk[NUM_UCWK_DPM_WEVEWS];     // In MHz
  uint8_t      UseStwobeModeOptimizations; //Set to indicate that FW shouwd use stwobe mode optimizations
  uint8_t      PaddingMem[3];

  uint8_t      UcwkDpmPstates     [NUM_UCWK_DPM_WEVEWS];     // 4 DPM states, 0-P0, 1-P1, 2-P2, 3-P3.
  uint8_t      FweqTabweUcwkDiv  [NUM_UCWK_DPM_WEVEWS    ];     // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

  uint16_t     MemVmempVowtage   [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)
  uint16_t     MemVddioVowtage    [NUM_UCWK_DPM_WEVEWS];         // mV(Q2)

  //FCWK Section

  uint8_t      FcwkDpmUPstates[NUM_FCWK_DPM_WEVEWS]; // U P-state ID associated with each FCWK DPM state.
  uint16_t     FcwkDpmVddU[NUM_FCWK_DPM_WEVEWS]; // mV(Q2) Vset U vowtage associated with each FCWK DPM state.
  uint16_t     FcwkDpmUSpeed[NUM_FCWK_DPM_WEVEWS]; //U speed associated with each FCWK DPM state
  uint16_t     FcwkDpmDisawwowPstateFweq;  //Fwequency which FW wiww tawget when indicated that dispway config cannot suppowt P-state. Set to 0 use FW cawcuwated vawue
  uint16_t     PaddingFcwk;

  // Wink DPM Settings
  uint8_t      PcieGenSpeed[NUM_WINK_WEVEWS];           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
  uint8_t      PcieWaneCount[NUM_WINK_WEVEWS];          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
  uint16_t     WcwkFweq[NUM_WINK_WEVEWS];

  // SECTION: Fan Contwow
  uint16_t     FanStopTemp[TEMP_COUNT];          //Cewsius
  uint16_t     FanStawtTemp[TEMP_COUNT];         //Cewsius

  uint16_t     FanGain[TEMP_COUNT];
  uint16_t     FanGainPadding;

  uint16_t     FanPwmMin;
  uint16_t     AcousticTawgetWpmThweshowd;
  uint16_t     AcousticWimitWpmThweshowd;
  uint16_t     FanMaximumWpm;
  uint16_t     MGpuAcousticWimitWpmThweshowd;
  uint16_t     FanTawgetGfxcwk;
  uint32_t     TempInputSewectMask;
  uint8_t      FanZewoWpmEnabwe;
  uint8_t      FanTachEdgePewWev;
  uint16_t     FanTawgetTempewatuwe[TEMP_COUNT];

  // The fowwowing awe AFC ovewwide pawametews. Weave at 0 to use FW defauwts.
  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;

  uint16_t     FwCtfWimit[TEMP_COUNT];

  uint16_t IntakeTempEnabweWPM;
  int16_t IntakeTempOffsetTemp;
  uint16_t IntakeTempWeweaseTemp;
  uint16_t IntakeTempHighIntakeAcousticWimit;
  uint16_t IntakeTempAcouticWimitWeweaseWate;

  int16_t FanAbnowmawTempWimitOffset;
  uint16_t FanStawwedTwiggewWpm;
  uint16_t FanAbnowmawTwiggewWpmCoeff;
  uint16_t FanAbnowmawDetectionEnabwe;

  uint8_t      FanIntakeSensowSuppowt;
  uint8_t      FanIntakePadding[3];
  uint32_t     FanSpawe[13];

  // SECTION: VDD_GFX AVFS

  uint8_t      OvewwideGfxAvfsFuses;
  uint8_t      GfxAvfsPadding[3];

  uint32_t     W2HwWtAvfsFuses[PP_GWTAVFS_HW_FUSE_COUNT]; //see fusedoc fow encoding
  uint32_t     SeHwWtAvfsFuses[PP_GWTAVFS_HW_FUSE_COUNT];

  uint32_t     CommonWtAvfs[PP_GWTAVFS_FW_COMMON_FUSE_COUNT];

  uint32_t     W2FwWtAvfsFuses[PP_GWTAVFS_FW_SEP_FUSE_COUNT];
  uint32_t     SeFwWtAvfsFuses[PP_GWTAVFS_FW_SEP_FUSE_COUNT];

  uint32_t    Dwoop_PWW_F[PP_NUM_WTAVFS_PWW_ZONES];
  uint32_t    Dwoop_PWW_a[PP_NUM_WTAVFS_PWW_ZONES];
  uint32_t    Dwoop_PWW_b[PP_NUM_WTAVFS_PWW_ZONES];
  uint32_t    Dwoop_PWW_c[PP_NUM_WTAVFS_PWW_ZONES];

  uint32_t   Static_PWW_Offset[PP_NUM_WTAVFS_PWW_ZONES];

  uint32_t   dGbV_dT_vmin;
  uint32_t   dGbV_dT_vmax;

  //Unused: PMFW-9370
  uint32_t   V2F_vmin_wange_wow;
  uint32_t   V2F_vmin_wange_high;
  uint32_t   V2F_vmax_wange_wow;
  uint32_t   V2F_vmax_wange_high;

  AvfsDcBtcPawams_t DcBtcGfxPawams;

  uint32_t   GfxAvfsSpawe[32];

  //SECTION: VDD_SOC AVFS

  uint8_t      OvewwideSocAvfsFuses;
  uint8_t      MinSocAvfsWevision;
  uint8_t      SocAvfsPadding[2];

  AvfsFuseOvewwide_t SocAvfsFuseOvewwide[AVFS_D_COUNT];

  DwoopInt_t        dBtcGbSoc[AVFS_D_COUNT];            // GHz->V BtcGb

  WineawInt_t       qAgingGb[AVFS_D_COUNT];          // GHz->V

  QuadwaticInt_t    qStaticVowtageOffset[AVFS_D_COUNT]; // GHz->V

  AvfsDcBtcPawams_t DcBtcSocPawams[AVFS_D_COUNT];

  uint32_t   SocAvfsSpawe[32];

  //SECTION: Boot cwock and vowtage vawues
  BootVawues_t BootVawues;

  //SECTION: Dwivew Wepowted Cwocks
  DwivewWepowtedCwocks_t DwivewWepowtedCwocks;

  //SECTION: Message Wimits
  MsgWimits_t MsgWimits;

  //SECTION: OvewDwive Wimits
  OvewDwiveWimits_t OvewDwiveWimitsMin;
  OvewDwiveWimits_t OvewDwiveWimitsBasicMax;
  uint32_t wesewved[22];

  // SECTION: Advanced Options
  uint32_t          DebugOvewwides;

  // Section: Totaw Boawd Powew idwe vs active coefficients
  uint8_t     TotawBoawdPowewSuppowt;
  uint8_t     TotawBoawdPowewPadding[3];

  int16_t     TotawIdweBoawdPowewM;
  int16_t     TotawIdweBoawdPowewB;
  int16_t     TotawBoawdPowewM;
  int16_t     TotawBoawdPowewB;

  //PMFW-11158
  QuadwaticInt_t qFeffCoeffGameCwock[POWEW_SOUWCE_COUNT];
  QuadwaticInt_t qFeffCoeffBaseCwock[POWEW_SOUWCE_COUNT];
  QuadwaticInt_t qFeffCoeffBoostCwock[POWEW_SOUWCE_COUNT];

  uint16_t TempewatuweWimit_Hynix; // In degwees Cewsius. Memowy tempewatuwe wimit associated with Hynix
  uint16_t TempewatuweWimit_Micwon; // In degwees Cewsius. Memowy tempewatuwe wimit associated with Micwon
  uint16_t TempewatuweFwCtfWimit_Hynix;
  uint16_t TempewatuweFwCtfWimit_Micwon;

  // SECTION: Sku Wesewved
  uint32_t         Spawe[41];

  // Padding fow MMHUB - do not modify this
  uint32_t     MmHubPadding[8];

} SkuTabwe_t;

typedef stwuct {
  // SECTION: Vewsion
  uint32_t    Vewsion; //shouwd be unique to each boawd type


  // SECTION: I2C Contwow
  I2cContwowwewConfig_t  I2cContwowwews[NUM_I2C_CONTWOWWEWS];

  // SECTION: SVI2 Boawd Pawametews
  uint8_t      VddGfxVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddSocVwMapping;   // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem0VwMapping;  // Use VW_MAPPING* bitfiewds
  uint8_t      VddMem1VwMapping;  // Use VW_MAPPING* bitfiewds

  uint8_t      GfxUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      SocUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      VmempUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode
  uint8_t      VddioUwvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in UWV mode

  //SECTION SVI3 Boawd Pawametews
  uint8_t      SwaveAddwMapping[SVI_PWANE_COUNT];
  uint8_t      VwPsiSuppowt[SVI_PWANE_COUNT];

  uint8_t      PaddingPsi[SVI_PWANE_COUNT];
  uint8_t      EnabwePsi6[SVI_PWANE_COUNT];       // onwy appwicabwe in SVI3

  // SECTION: Vowtage Weguwatow Settings
  SviTewemetwyScawe_t SviTewemetwyScawe[SVI_PWANE_COUNT];
  uint32_t     VowtageTewemetwyWatio[SVI_PWANE_COUNT]; // This is used fow VDDIO  Svi2 Div Watio wowkawound. It has 16 fwactionaw bits (Q16.16)

  uint8_t      DownSwewWateVw[SVI_PWANE_COUNT];

  // SECTION: GPIO Settings

  uint8_t      WedOffGpio;
  uint8_t      FanOffGpio;
  uint8_t      GfxVwPowewStageOffGpio;

  uint8_t      AcDcGpio;        // GPIO pin configuwed fow AC/DC switching
  uint8_t      AcDcPowawity;    // GPIO powawity fow AC/DC switching
  uint8_t      VW0HotGpio;      // GPIO pin configuwed fow VW0 HOT event
  uint8_t      VW0HotPowawity;  // GPIO powawity fow VW0 HOT event

  uint8_t      GthwGpio;        // GPIO pin configuwed fow GTHW Event
  uint8_t      GthwPowawity;    // wepwace GPIO powawity fow GTHW

  // WED Dispway Settings
  uint8_t      WedPin0;         // GPIO numbew fow WedPin[0]
  uint8_t      WedPin1;         // GPIO numbew fow WedPin[1]
  uint8_t      WedPin2;         // GPIO numbew fow WedPin[2]
  uint8_t      WedEnabweMask;

  uint8_t      WedPcie;        // GPIO numbew fow PCIE wesuwts
  uint8_t      WedEwwow;       // GPIO numbew fow Ewwow Cases

  // SECTION: Cwock Spwead Spectwum

  // UCWK Spwead Spectwum
  uint8_t      UcwkTwainingModeSpweadPewcent;
  uint8_t      UcwkSpweadPadding;
  uint16_t     UcwkSpweadFweq;      // kHz

  // UCWK Spwead Spectwum
  uint8_t      UcwkSpweadPewcent[MEM_VENDOW_COUNT];

  uint8_t      GfxcwkSpweadEnabwe;

  // FCWK Spwead Spectwum
  uint8_t      FcwkSpweadPewcent;   // Q4.4
  uint16_t     FcwkSpweadFweq;      // kHz

  // Section: Memowy Config
  uint8_t      DwamWidth; // Width of intewface to the channew fow each DWAM moduwe. See DWAM_BIT_WIDTH_TYPE_e
  uint8_t      PaddingMem1[7];

  // SECTION: UMC featuwe fwags
  uint8_t      HswEnabwed;
  uint8_t      VddqOffEnabwed;
  uint8_t      PaddingUmcFwags[2];

  uint32_t    PostVowtageSetBacoDeway; // in micwoseconds. Amount of time FW wiww wait aftew powew good is estabwished ow PSI0 command is issued
  uint32_t    BacoEntwyDeway; // in miwwiseconds. Amount of time FW wiww wait to twiggew BACO entwy aftew weceiving entwy notification fwom OS

  uint8_t     FuseWwitePowewMuxPwesent;
  uint8_t     FuseWwitePadding[3];

  // SECTION: Boawd Wesewved
  uint32_t     BoawdSpawe[63];

  // SECTION: Stwuctuwe Padding

  // Padding fow MMHUB - do not modify this
  uint32_t     MmHubPadding[8];
} BoawdTabwe_t;

#pwagma pack(push, 1)
typedef stwuct {
  SkuTabwe_t SkuTabwe;
  BoawdTabwe_t BoawdTabwe;
} PPTabwe_t;
#pwagma pack(pop)

typedef stwuct {
  // Time constant pawametews fow cwock avewages in ms
  uint16_t     GfxcwkAvewageWpfTau;
  uint16_t     FcwkAvewageWpfTau;
  uint16_t     UcwkAvewageWpfTau;
  uint16_t     GfxActivityWpfTau;
  uint16_t     UcwkActivityWpfTau;
  uint16_t     SocketPowewWpfTau;
  uint16_t     VcnCwkAvewageWpfTau;
  uint16_t     VcnUsageAvewageWpfTau;
} DwivewSmuConfig_t;

typedef stwuct {
  DwivewSmuConfig_t DwivewSmuConfig;

  uint32_t     Spawe[8];
  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} DwivewSmuConfigExtewnaw_t;


typedef stwuct {

  uint16_t       FweqTabweGfx      [NUM_GFXCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweVcwk     [NUM_VCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweDcwk     [NUM_DCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweSoccwk   [NUM_SOCCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweUcwk     [NUM_UCWK_DPM_WEVEWS    ];     // In MHz
  uint16_t       FweqTabweDispcwk  [NUM_DISPCWK_DPM_WEVEWS ];     // In MHz
  uint16_t       FweqTabweDppCwk   [NUM_DPPCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweDpwefcwk [NUM_DPWEFCWK_DPM_WEVEWS];     // In MHz
  uint16_t       FweqTabweDcfcwk   [NUM_DCFCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweDtbcwk   [NUM_DTBCWK_DPM_WEVEWS  ];     // In MHz
  uint16_t       FweqTabweFcwk     [NUM_FCWK_DPM_WEVEWS    ];     // In MHz

  uint16_t       DcModeMaxFweq     [PPCWK_COUNT            ];     // In MHz

  uint16_t       Padding;

  uint32_t Spawe[32];

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use

} DwivewInfoTabwe_t;

typedef stwuct {
  uint32_t CuwwCwock[PPCWK_COUNT];

  uint16_t AvewageGfxcwkFwequencyTawget;
  uint16_t AvewageGfxcwkFwequencyPweDs;
  uint16_t AvewageGfxcwkFwequencyPostDs;
  uint16_t AvewageFcwkFwequencyPweDs;
  uint16_t AvewageFcwkFwequencyPostDs;
  uint16_t AvewageMemcwkFwequencyPweDs  ; // this is scawed to actuaw memowy cwock
  uint16_t AvewageMemcwkFwequencyPostDs  ; // this is scawed to actuaw memowy cwock
  uint16_t AvewageVcwk0Fwequency  ;
  uint16_t AvewageDcwk0Fwequency  ;
  uint16_t AvewageVcwk1Fwequency  ;
  uint16_t AvewageDcwk1Fwequency  ;
  uint16_t PCIeBusy;
  uint16_t dGPU_W_MAX;
  uint16_t padding;

  uint32_t MetwicsCountew;

  uint16_t AvgVowtage[SVI_PWANE_COUNT];
  uint16_t AvgCuwwent[SVI_PWANE_COUNT];

  uint16_t AvewageGfxActivity    ;
  uint16_t AvewageUcwkActivity   ;
  uint16_t Vcn0ActivityPewcentage  ;
  uint16_t Vcn1ActivityPewcentage  ;

  uint32_t EnewgyAccumuwatow;
  uint16_t AvewageSocketPowew;
  uint16_t AvewageTotawBoawdPowew;

  uint16_t AvgTempewatuwe[TEMP_COUNT];
  uint16_t AvgTempewatuweFanIntake;

  uint8_t  PcieWate               ;
  uint8_t  PcieWidth              ;

  uint8_t  AvgFanPwm;
  uint8_t  Padding[1];
  uint16_t AvgFanWpm;


  uint8_t ThwottwingPewcentage[THWOTTWEW_COUNT];
  uint8_t VmaxThwottwingPewcentage;
  uint8_t Padding1[3];

  //metwics fow D3hot entwy/exit and dwivew AWM msgs
  uint32_t D3HotEntwyCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint32_t D3HotExitCountPewMode[D3HOT_SEQUENCE_COUNT];
  uint32_t AwmMsgWeceivedCountPewMode[D3HOT_SEQUENCE_COUNT];

  uint16_t ApuSTAPMSmawtShiftWimit;
  uint16_t ApuSTAPMWimit;
  uint16_t AvgApuSocketPowew;

  uint16_t AvewageUcwkActivity_MAX;

  uint32_t PubwicSewiawNumbewWowew;
  uint32_t PubwicSewiawNumbewUppew;

} SmuMetwics_t;

typedef stwuct {
  SmuMetwics_t SmuMetwics;
  uint32_t Spawe[29];

  // Padding - ignowe
  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} SmuMetwicsExtewnaw_t;

typedef stwuct {
  uint8_t  WmSetting;
  uint8_t  Fwags;
  uint8_t  Padding[2];

} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WATEWMAWKS_CWOCK_WANGE = 0,
  WATEWMAWKS_DUMMY_PSTATE,
  WATEWMAWKS_MAWW,
  WATEWMAWKS_COUNT,
} WATEWMAWKS_FWAGS_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[NUM_WM_WANGES];
} Watewmawks_t;

typedef stwuct {
  Watewmawks_t Watewmawks;
  uint32_t  Spawe[16];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} WatewmawksExtewnaw_t;

typedef stwuct {
  uint16_t avgPsmCount[214];
  uint16_t minPsmCount[214];
  fwoat    avgPsmVowtage[214];
  fwoat    minPsmVowtage[214];
} AvfsDebugTabwe_t;

typedef stwuct {
  AvfsDebugTabwe_t AvfsDebugTabwe;

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} AvfsDebugTabweExtewnaw_t;


typedef stwuct {
  uint8_t   Gfx_ActiveHystWimit;
  uint8_t   Gfx_IdweHystWimit;
  uint8_t   Gfx_FPS;
  uint8_t   Gfx_MinActiveFweqType;
  uint8_t   Gfx_BoostewFweqType;
  uint8_t   PaddingGfx;
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
  uint8_t   PaddingFcwk;
  uint16_t  Fcwk_MinActiveFweq;              // MHz
  uint16_t  Fcwk_BoostewFweq;                // MHz
  uint16_t  Fcwk_PD_Data_time_constant;      // Time constant of PD contwowwew in ms
  uint32_t  Fcwk_PD_Data_wimit_a;            // Q16
  uint32_t  Fcwk_PD_Data_wimit_b;            // Q16
  uint32_t  Fcwk_PD_Data_wimit_c;            // Q16
  uint32_t  Fcwk_PD_Data_ewwow_coeff;        // Q16
  uint32_t  Fcwk_PD_Data_ewwow_wate_coeff;   // Q16

  uint32_t  Mem_UpThweshowd_Wimit[NUM_UCWK_DPM_WEVEWS];          // Q16
  uint8_t   Mem_UpHystWimit[NUM_UCWK_DPM_WEVEWS];
  uint8_t   Mem_DownHystWimit[NUM_UCWK_DPM_WEVEWS];
  uint16_t  Mem_Fps;
  uint8_t   padding[2];

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
#define WOWKWOAD_PPWIB_WINDOW_3D_BIT      7
#define WOWKWOAD_PPWIB_COUNT              8


// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam

// Tabwe twansfew status
#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF
#define TABWE_TWANSFEW_PENDING    0xAB

// Tabwe types
#define TABWE_PPTABWE                 0
#define TABWE_COMBO_PPTABWE           1
#define TABWE_WATEWMAWKS              2
#define TABWE_AVFS_PSM_DEBUG          3
#define TABWE_PMSTATUSWOG             4
#define TABWE_SMU_METWICS             5
#define TABWE_DWIVEW_SMU_CONFIG       6
#define TABWE_ACTIVITY_MONITOW_COEFF  7
#define TABWE_OVEWDWIVE               8
#define TABWE_I2C_COMMANDS            9
#define TABWE_DWIVEW_INFO             10
#define TABWE_ECCINFO                 11
#define TABWE_WIFIBAND                12
#define TABWE_COUNT                   13

//IH Intewupt ID
#define IH_INTEWWUPT_ID_TO_DWIVEW                   0xFE
#define IH_INTEWWUPT_CONTEXT_ID_BACO                0x2
#define IH_INTEWWUPT_CONTEXT_ID_AC                  0x3
#define IH_INTEWWUPT_CONTEXT_ID_DC                  0x4
#define IH_INTEWWUPT_CONTEXT_ID_AUDIO_D0            0x5
#define IH_INTEWWUPT_CONTEXT_ID_AUDIO_D3            0x6
#define IH_INTEWWUPT_CONTEXT_ID_THEWMAW_THWOTTWING  0x7
#define IH_INTEWWUPT_CONTEXT_ID_FAN_ABNOWMAW        0x8
#define IH_INTEWWUPT_CONTEXT_ID_FAN_WECOVEWY        0x9

#endif
