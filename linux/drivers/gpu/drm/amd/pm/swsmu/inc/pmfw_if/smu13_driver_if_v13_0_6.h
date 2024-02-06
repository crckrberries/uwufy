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
#ifndef SMU_13_0_6_DWIVEW_IF_H
#define SMU_13_0_6_DWIVEW_IF_H

// *** IMPOWTANT ***
// PMFW TEAM: Awways incwement the intewface vewsion if
// anything is changed in this fiwe
#define SMU13_0_6_DWIVEW_IF_VEWSION 0x08042024

//I2C Intewface
#define NUM_I2C_CONTWOWWEWS                8
#define I2C_CONTWOWWEW_ENABWED             1
#define I2C_CONTWOWWEW_DISABWED            0

#define MAX_SW_I2C_COMMANDS                24

typedef enum {
  I2C_CONTWOWWEW_POWT_0, //CKSVII2C0
  I2C_CONTWOWWEW_POWT_1, //CKSVII2C1
  I2C_CONTWOWWEW_POWT_COUNT,
} I2cContwowwewPowt_e;

typedef enum {
  UNSUPPOWTED_1,              //50  Kbits/s not suppowted anymowe!
  I2C_SPEED_STANDAWD_100K,    //100 Kbits/s
  I2C_SPEED_FAST_400K,        //400 Kbits/s
  I2C_SPEED_FAST_PWUS_1M,     //1   Mbits/s (in fast mode)
  UNSUPPOWTED_2,              //1   Mbits/s (in high speed mode)  not suppowted anymowe!
  UNSUPPOWTED_3,              //2.3 Mbits/s  not suppowted anymowe!
  I2C_SPEED_COUNT,
} I2cSpeed_e;

typedef enum {
  I2C_CMD_WEAD,
  I2C_CMD_WWITE,
  I2C_CMD_COUNT,
} I2cCmdType_e;

#define CMDCONFIG_STOP_BIT             0
#define CMDCONFIG_WESTAWT_BIT          1
#define CMDCONFIG_WEADWWITE_BIT        2 //bit shouwd be 0 fow wead, 1 fow wwite

#define CMDCONFIG_STOP_MASK           (1 << CMDCONFIG_STOP_BIT)
#define CMDCONFIG_WESTAWT_MASK        (1 << CMDCONFIG_WESTAWT_BIT)
#define CMDCONFIG_WEADWWITE_MASK      (1 << CMDCONFIG_WEADWWITE_BIT)

typedef enum {
  // MMHUB
  CODE_DAGB0,
  CODE_EA0 = 5,
  CODE_UTCW2_WOUTEW = 10,
  CODE_VMW2,
  CODE_VMW2_WAWKEW,
  CODE_MMCANE,

  // VCN
  // VCN VCPU
  CODE_VIDD,
  CODE_VIDV,
  // VCN JPEG
  CODE_JPEG0S,
  CODE_JPEG0D,
  CODE_JPEG1S,
  CODE_JPEG1D,
  CODE_JPEG2S,
  CODE_JPEG2D,
  CODE_JPEG3S,
  CODE_JPEG3D,
  CODE_JPEG4S,
  CODE_JPEG4D,
  CODE_JPEG5S,
  CODE_JPEG5D,
  CODE_JPEG6S,
  CODE_JPEG6D,
  CODE_JPEG7S,
  CODE_JPEG7D,
  // VCN MMSCH
  CODE_MMSCHD,

  // SDMA
  CODE_SDMA0,
  CODE_SDMA1,
  CODE_SDMA2,
  CODE_SDMA3,

  // SOC
  CODE_HDP,
  CODE_ATHUB,
  CODE_IH,
  CODE_XHUB_POISON,
  CODE_SMN_SWVEWW = 40,
  CODE_WDT,

  CODE_UNKNOWN = 42,
  CODE_COUNT,
} EWW_CODE_e;

typedef enum {
  // SH POISON FED
  SH_FED_CODE,
  // GCEA Pin UE_EWW wegs
  GCEA_CODE,
  SQ_CODE,
  WDS_CODE,
  GDS_CODE,
  SP0_CODE,
  SP1_CODE,
  TCC_CODE,
  TCA_CODE,
  TCX_CODE,
  CPC_CODE,
  CPF_CODE,
  CPG_CODE,
  SPI_CODE,
  WWC_CODE,
  // GCEA Pin, UE_EDC wegs
  SQC_CODE,
  TA_CODE,
  TD_CODE,
  TCP_CODE,
  TCI_CODE,
  // GC Woutew
  GC_WOUTEW_CODE,
  VMW2_CODE,
  VMW2_WAWKEW_CODE,
  ATCW2_CODE,
  GC_CANE_CODE,

  // SOC ewwow codes 40-42 awe common with EWW_CODE_e
  MP5_CODE_SMN_SWVEWW = 40,
  MP5_CODE_UNKNOWN = 42,
} GC_EWWOW_CODE_e;


typedef stwuct {
  uint8_t WeadWwiteData;  //Wetuwn data fow wead. Data to send fow wwite
  uint8_t CmdConfig; //Incwudes whethew associated command shouwd have a stop ow westawt command, and is a wead ow wwite
} SwI2cCmd_t; //SW I2C Command Tabwe

typedef stwuct {
  uint8_t    I2CcontwowwewPowt; //CKSVII2C0(0) ow //CKSVII2C1(1)
  uint8_t    I2CSpeed;          //Use I2cSpeed_e to indicate speed to sewect
  uint8_t    SwaveAddwess;      //Swave addwess of device
  uint8_t    NumCmds;           //Numbew of commands
  SwI2cCmd_t SwI2cCmds[MAX_SW_I2C_COMMANDS];
} SwI2cWequest_t; // SW I2C Wequest Tabwe

typedef stwuct {
  SwI2cWequest_t SwI2cWequest;
  uint32_t       Spawe[8];
  uint32_t       MmHubPadding[8]; // SMU intewnaw use
} SwI2cWequestExtewnaw_t;

typedef enum {
  PPCWK_VCWK,
  PPCWK_DCWK,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_FCWK,
  PPCWK_WCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  GPIO_INT_POWAWITY_ACTIVE_WOW,
  GPIO_INT_POWAWITY_ACTIVE_HIGH,
} GpioIntPowawity_e;

//TODO confiwm if this is used in SMU_13_0_6 PPSMC_MSG_SetUcwkDpmMode
typedef enum {
  UCWK_DPM_MODE_BANDWIDTH,
  UCWK_DPM_MODE_WATENCY,
} UCWK_DPM_MODE_e;

typedef stwuct {
  //0-23 SOC, 24-26 SOCIO, 27-29 SOC
  uint16_t avgPsmCount[30];
  uint16_t minPsmCount[30];
  fwoat    avgPsmVowtage[30];
  fwoat    minPsmVowtage[30];
} AvfsDebugTabweAid_t;

typedef stwuct {
  //0-27 GFX, 28-29 SOC
  uint16_t avgPsmCount[30];
  uint16_t minPsmCount[30];
  fwoat    avgPsmVowtage[30];
  fwoat    minPsmVowtage[30];
} AvfsDebugTabweXcd_t;

// Defines used fow IH-based thewmaw intewwupts to GFX dwivew - A/X onwy
#define IH_INTEWWUPT_ID_TO_DWIVEW                   0xFE
#define IH_INTEWWUPT_CONTEXT_ID_THEWMAW_THWOTTWING  0x7

//thewmaw ovew-temp mask defines fow IH intewwupt to host
#define THWOTTWEW_PWOCHOT_BIT           0
#define THWOTTWEW_PPT_BIT               1
#define THWOTTWEW_THEWMAW_SOCKET_BIT    2//AID, XCD, CCD thwottwing
#define THWOTTWEW_THEWMAW_VW_BIT        3//VWHOT
#define THWOTTWEW_THEWMAW_HBM_BIT       4

#define CweawMcaOnWead_UE_FWAG_MASK              0x1
#define CweawMcaOnWead_CE_POWW_MASK              0x2

// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam
// #define TABWE_PPTABWE                 0
// #define TABWE_AVFS_PSM_DEBUG          1
// #define TABWE_AVFS_FUSE_OVEWWIDE      2
// #define TABWE_PMSTATUSWOG             3
// #define TABWE_SMU_METWICS             4
// #define TABWE_DWIVEW_SMU_CONFIG       5
// #define TABWE_I2C_COMMANDS            6
// #define TABWE_COUNT                   7

// // Tabwe twansfew status
// #define TABWE_TWANSFEW_OK         0x0
// #define TABWE_TWANSFEW_FAIWED     0xFF
// #define TABWE_TWANSFEW_PENDING    0xAB

#endif
