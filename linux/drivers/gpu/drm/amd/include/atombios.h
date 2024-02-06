/*
 * Copywight 2006-2007 Advanced Micwo Devices, Inc.
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
 */


/****************************************************************************/
/*Powtion I: Definitions  shawed between VBIOS and Dwivew                   */
/****************************************************************************/

#ifndef _ATOMBIOS_H
#define _ATOMBIOS_H

#define ATOM_VEWSION_MAJOW                   0x00020000
#define ATOM_VEWSION_MINOW                   0x00000002

#define ATOM_HEADEW_VEWSION (ATOM_VEWSION_MAJOW | ATOM_VEWSION_MINOW)

/* Endianness shouwd be specified befowe incwusion,
 * defauwt to wittwe endian
 */
#ifndef ATOM_BIG_ENDIAN
#ewwow Endian not specified
#endif

#ifdef _H2INC
  #ifndef UWONG
    typedef unsigned wong UWONG;
  #endif

  #ifndef UCHAW
    typedef unsigned chaw UCHAW;
  #endif

  #ifndef USHOWT
    typedef unsigned showt USHOWT;
  #endif
#endif

#define ATOM_DAC_A            0
#define ATOM_DAC_B            1
#define ATOM_EXT_DAC          2

#define ATOM_CWTC1            0
#define ATOM_CWTC2            1
#define ATOM_CWTC3            2
#define ATOM_CWTC4            3
#define ATOM_CWTC5            4
#define ATOM_CWTC6            5

#define ATOM_UNDEWWAY_PIPE0   16
#define ATOM_UNDEWWAY_PIPE1   17

#define ATOM_CWTC_INVAWID     0xFF

#define ATOM_DIGA             0
#define ATOM_DIGB             1

#define ATOM_PPWW1            0
#define ATOM_PPWW2            1
#define ATOM_DCPWW            2
#define ATOM_PPWW0            2
#define ATOM_PPWW3            3

#define ATOM_PHY_PWW0         4
#define ATOM_PHY_PWW1         5

#define ATOM_EXT_PWW1         8
#define ATOM_GCK_DFS          8
#define ATOM_EXT_PWW2         9
#define ATOM_FCH_CWK          9
#define ATOM_EXT_CWOCK        10
#define ATOM_DP_DTO           11

#define ATOM_COMBOPHY_PWW0    20
#define ATOM_COMBOPHY_PWW1    21
#define ATOM_COMBOPHY_PWW2    22
#define ATOM_COMBOPHY_PWW3    23
#define ATOM_COMBOPHY_PWW4    24
#define ATOM_COMBOPHY_PWW5    25

#define ATOM_PPWW_INVAWID     0xFF

#define ENCODEW_WEFCWK_SWC_P1PWW       0
#define ENCODEW_WEFCWK_SWC_P2PWW       1
#define ENCODEW_WEFCWK_SWC_DCPWW       2
#define ENCODEW_WEFCWK_SWC_EXTCWK      3
#define ENCODEW_WEFCWK_SWC_INVAWID     0xFF

#define ATOM_SCAWEW_DISABWE   0   //Fow Fudo, it's bypass and auto-cengtew & no wepwication
#define ATOM_SCAWEW_CENTEW    1   //Fow Fudo, it's bypass and auto-centew & auto wepwication
#define ATOM_SCAWEW_EXPANSION 2   //Fow Fudo, it's 2 Tap awpha bwending mode
#define ATOM_SCAWEW_MUWTI_EX  3   //Fow Fudo onwy, it's muwti-tap mode onwy used to dwive TV ow CV, onwy used by Bios

#define ATOM_DISABWE          0
#define ATOM_ENABWE           1
#define ATOM_WCD_BWOFF                          (ATOM_DISABWE+2)
#define ATOM_WCD_BWON                           (ATOM_ENABWE+2)
#define ATOM_WCD_BW_BWIGHTNESS_CONTWOW          (ATOM_ENABWE+3)
#define ATOM_WCD_SEWFTEST_STAWT                 (ATOM_DISABWE+5)
#define ATOM_WCD_SEWFTEST_STOP                  (ATOM_ENABWE+5)
#define ATOM_ENCODEW_INIT                       (ATOM_DISABWE+7)
#define ATOM_INIT                               (ATOM_DISABWE+7)
#define ATOM_GET_STATUS                         (ATOM_DISABWE+8)

#define ATOM_BWANKING         1
#define ATOM_BWANKING_OFF     0


#define ATOM_CWT1             0
#define ATOM_CWT2             1

#define ATOM_TV_NTSC          1
#define ATOM_TV_NTSCJ         2
#define ATOM_TV_PAW           3
#define ATOM_TV_PAWM          4
#define ATOM_TV_PAWCN         5
#define ATOM_TV_PAWN          6
#define ATOM_TV_PAW60         7
#define ATOM_TV_SECAM         8
#define ATOM_TV_CV            16

#define ATOM_DAC1_PS2         1
#define ATOM_DAC1_CV          2
#define ATOM_DAC1_NTSC        3
#define ATOM_DAC1_PAW         4

#define ATOM_DAC2_PS2         ATOM_DAC1_PS2
#define ATOM_DAC2_CV          ATOM_DAC1_CV
#define ATOM_DAC2_NTSC        ATOM_DAC1_NTSC
#define ATOM_DAC2_PAW         ATOM_DAC1_PAW

#define ATOM_PM_ON            0
#define ATOM_PM_STANDBY       1
#define ATOM_PM_SUSPEND       2
#define ATOM_PM_OFF           3

// Fow ATOM_WVDS_INFO_V12
// Bit0:{=0:singwe, =1:duaw},
// Bit1 {=0:666WGB, =1:888WGB},
// Bit2:3:{Gwey wevew}
// Bit4:{=0:WDI fowmat fow WGB888, =1 FPDI fowmat fow WGB888}
#define ATOM_PANEW_MISC_DUAW               0x00000001
#define ATOM_PANEW_MISC_888WGB             0x00000002
#define ATOM_PANEW_MISC_GWEY_WEVEW         0x0000000C
#define ATOM_PANEW_MISC_FPDI               0x00000010
#define ATOM_PANEW_MISC_GWEY_WEVEW_SHIFT   2
#define ATOM_PANEW_MISC_SPATIAW            0x00000020
#define ATOM_PANEW_MISC_TEMPOWAW           0x00000040
#define ATOM_PANEW_MISC_API_ENABWED        0x00000080

#define MEMTYPE_DDW1                       "DDW1"
#define MEMTYPE_DDW2                       "DDW2"
#define MEMTYPE_DDW3                       "DDW3"
#define MEMTYPE_DDW4                       "DDW4"

#define ASIC_BUS_TYPE_PCI                  "PCI"
#define ASIC_BUS_TYPE_AGP                  "AGP"
#define ASIC_BUS_TYPE_PCIE                 "PCI_EXPWESS"

//Maximum size of that FiweGW fwag stwing
#define ATOM_FIWEGW_FWAG_STWING            "FGW"      //Fwag used to enabwe FiweGW Suppowt
#define ATOM_MAX_SIZE_OF_FIWEGW_FWAG_STWING     3     //sizeof( ATOM_FIWEGW_FWAG_STWING )

#define ATOM_FAKE_DESKTOP_STWING           "DSK"      //Fwag used to enabwe mobiwe ASIC on Desktop
#define ATOM_MAX_SIZE_OF_FAKE_DESKTOP_STWING    ATOM_MAX_SIZE_OF_FIWEGW_FWAG_STWING

#define ATOM_M54T_FWAG_STWING              "M54T"     //Fwag used to enabwe M54T Suppowt
#define ATOM_MAX_SIZE_OF_M54T_FWAG_STWING  4          //sizeof( ATOM_M54T_FWAG_STWING )

#define HW_ASSISTED_I2C_STATUS_FAIWUWE     2
#define HW_ASSISTED_I2C_STATUS_SUCCESS     1

#pwagma pack(1)                                       // BIOS data must use byte awignment

// Define offset to wocation of WOM headew.
#define OFFSET_TO_POINTEW_TO_ATOM_WOM_HEADEW         0x00000048W
#define OFFSET_TO_ATOM_WOM_IMAGE_SIZE                0x00000002W

#define OFFSET_TO_ATOMBIOS_ASIC_BUS_MEM_TYPE         0x94
#define MAXSIZE_OF_ATOMBIOS_ASIC_BUS_MEM_TYPE        20    //incwuding the tewminatow 0x0!
#define OFFSET_TO_GET_ATOMBIOS_STWINGS_NUMBEW      0x002f
#define OFFSET_TO_GET_ATOMBIOS_STWINGS_STAWT       0x006e

/****************************************************************************/
// Common headew fow aww tabwes (Data tabwe, Command tabwe).
// Evewy tabwe pointed  _ATOM_MASTEW_DATA_TABWE has this common headew.
// And the pointew actuawwy points to this headew.
/****************************************************************************/

typedef stwuct _ATOM_COMMON_TABWE_HEADEW
{
  USHOWT usStwuctuweSize;
  UCHAW  ucTabweFowmatWevision;   //Change it when the Pawsew is not backwawd compatibwe
  UCHAW  ucTabweContentWevision;  //Change it onwy when the tabwe needs to change but the fiwmwawe
                                  //Image can't be updated, whiwe Dwivew needs to cawwy the new tabwe!
}ATOM_COMMON_TABWE_HEADEW;

/****************************************************************************/
// Stwuctuwe stowes the WOM headew.
/****************************************************************************/
typedef stwuct _ATOM_WOM_HEADEW
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  UCHAW  uaFiwmWaweSignatuwe[4];    //Signatuwe to distinguish between Atombios and non-atombios,
                                    //atombios shouwd init it as "ATOM", don't change the position
  USHOWT usBiosWuntimeSegmentAddwess;
  USHOWT usPwotectedModeInfoOffset;
  USHOWT usConfigFiwenameOffset;
  USHOWT usCWC_BwockOffset;
  USHOWT usBIOS_BootupMessageOffset;
  USHOWT usInt10Offset;
  USHOWT usPciBusDevInitCode;
  USHOWT usIoBaseAddwess;
  USHOWT usSubsystemVendowID;
  USHOWT usSubsystemID;
  USHOWT usPCI_InfoOffset;
  USHOWT usMastewCommandTabweOffset;//Offest fow SW to get aww command tabwe offsets, Don't change the position
  USHOWT usMastewDataTabweOffset;   //Offest fow SW to get aww data tabwe offsets, Don't change the position
  UCHAW  ucExtendedFunctionCode;
  UCHAW  ucWesewved;
}ATOM_WOM_HEADEW;


typedef stwuct _ATOM_WOM_HEADEW_V2_1
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  UCHAW  uaFiwmWaweSignatuwe[4];    //Signatuwe to distinguish between Atombios and non-atombios,
                                    //atombios shouwd init it as "ATOM", don't change the position
  USHOWT usBiosWuntimeSegmentAddwess;
  USHOWT usPwotectedModeInfoOffset;
  USHOWT usConfigFiwenameOffset;
  USHOWT usCWC_BwockOffset;
  USHOWT usBIOS_BootupMessageOffset;
  USHOWT usInt10Offset;
  USHOWT usPciBusDevInitCode;
  USHOWT usIoBaseAddwess;
  USHOWT usSubsystemVendowID;
  USHOWT usSubsystemID;
  USHOWT usPCI_InfoOffset;
  USHOWT usMastewCommandTabweOffset;//Offest fow SW to get aww command tabwe offsets, Don't change the position
  USHOWT usMastewDataTabweOffset;   //Offest fow SW to get aww data tabwe offsets, Don't change the position
  UCHAW  ucExtendedFunctionCode;
  UCHAW  ucWesewved;
  UWONG  uwPSPDiwTabweOffset;
}ATOM_WOM_HEADEW_V2_1;


//==============================Command Tabwe Powtion====================================


/****************************************************************************/
// Stwuctuwes used in Command.mtb
/****************************************************************************/
typedef stwuct _ATOM_MASTEW_WIST_OF_COMMAND_TABWES{
  USHOWT ASIC_Init;                              //Function Tabwe, used by vawious SW components,watest vewsion 1.1
  USHOWT GetDispwaySuwfaceSize;                  //Atomic Tabwe,  Used by Bios when enabwing HW ICON
  USHOWT ASIC_WegistewsInit;                     //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom ASIC_Init
  USHOWT VWAM_BwockVendewDetection;              //Atomic Tabwe,  used onwy by Bios
  USHOWT DIGxEncodewContwow;                     //Onwy used by Bios
  USHOWT MemowyContwowwewInit;                   //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom ASIC_Init
  USHOWT EnabweCWTCMemWeq;                       //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 2.1
  USHOWT MemowyPawamAdjust;                      //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock if needed
  USHOWT DVOEncodewContwow;                      //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.2
  USHOWT GPIOPinContwow;                         //Atomic Tabwe,  onwy used by Bios
  USHOWT SetEngineCwock;                         //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT SetMemowyCwock;                         //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT SetPixewCwock;                          //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.2
  USHOWT EnabweDispPowewGating;                  //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom ASIC_Init
  USHOWT WesetMemowyDWW;                         //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT WesetMemowyDevice;                      //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT MemowyPWWInit;                          //Atomic Tabwe,  used onwy by Bios
  USHOWT AdjustDispwayPww;                       //Atomic Tabwe,  used by vawious SW componentes.
  USHOWT AdjustMemowyContwowwew;                 //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT EnabweASIC_StaticPwwMgt;                //Atomic Tabwe,  onwy used by Bios
  USHOWT SetUniphyInstance;                      //Atomic Tabwe,  onwy used by Bios
  USHOWT DAC_WoadDetection;                      //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.2
  USHOWT WVTMAEncodewContwow;                    //Atomic Tabwe,diwectwy used by vawious SW components,watest vewsion 1.3
  USHOWT HW_Misc_Opewation;                      //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DAC1EncodewContwow;                     //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DAC2EncodewContwow;                     //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DVOOutputContwow;                       //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT CV1OutputContwow;                       //Atomic Tabwe,  Atomic Tabwe,  Obsowete fwom Wy6xx, use DAC2 Output instead
  USHOWT GetConditionawGowdenSetting;            //Onwy used by Bios
  USHOWT SMC_Init;                               //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT PatchMCSetting;                         //onwy used by BIOS
  USHOWT MC_SEQ_Contwow;                         //onwy used by BIOS
  USHOWT Gfx_Hawvesting;                         //Atomic Tabwe,  Obsowete fwom Wy6xx, Now onwy used by BIOS fow GFX hawvesting
  USHOWT EnabweScawew;                           //Atomic Tabwe,  used onwy by Bios
  USHOWT BwankCWTC;                              //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT EnabweCWTC;                             //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT GetPixewCwock;                          //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT EnabweVGA_Wendew;                       //Function Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT GetSCWKOvewMCWKWatio;                   //Atomic Tabwe,  onwy used by Bios
  USHOWT SetCWTC_Timing;                         //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT SetCWTC_OvewScan;                       //Atomic Tabwe,  used by vawious SW components,watest vewsion 1.1
  USHOWT GetSMUCwockInfo;                         //Atomic Tabwe,  used onwy by Bios
  USHOWT SewectCWTC_Souwce;                      //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT EnabweGwaphSuwfaces;                    //Atomic Tabwe,  used onwy by Bios
  USHOWT UpdateCWTC_DoubweBuffewWegistews;       //Atomic Tabwe,  used onwy by Bios
  USHOWT WUT_AutoFiww;                           //Atomic Tabwe,  onwy used by Bios
  USHOWT SetDCECwock;                            //Atomic Tabwe,  stawt fwom DCE11.1, shawed by dwivew and VBIOS, change DISPCWK and DPWEFCWK
  USHOWT GetMemowyCwock;                         //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT GetEngineCwock;                         //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT SetCWTC_UsingDTDTiming;                 //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT ExtewnawEncodewContwow;                 //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 2.1
  USHOWT WVTMAOutputContwow;                     //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT VWAM_BwockDetectionByStwap;             //Atomic Tabwe,  used onwy by Bios
  USHOWT MemowyCweanUp;                          //Atomic Tabwe,  onwy used by Bios
  USHOWT PwocessI2cChannewTwansaction;           //Function Tabwe,onwy used by Bios
  USHOWT WwiteOneByteToHWAssistedI2C;            //Function Tabwe,indiwectwy used by vawious SW components
  USHOWT WeadHWAssistedI2CStatus;                //Atomic Tabwe,  indiwectwy used by vawious SW components
  USHOWT SpeedFanContwow;                        //Function Tabwe,indiwectwy used by vawious SW components,cawwed fwom ASIC_Init
  USHOWT PowewConnectowDetection;                //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT MC_Synchwonization;                     //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT ComputeMemowyEnginePWW;                 //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowy/EngineCwock
  USHOWT Gfx_Init;                               //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowy ow SetEngineCwock
  USHOWT VWAM_GetCuwwentInfoBwock;               //Atomic Tabwe,  used onwy by Bios
  USHOWT DynamicMemowySettings;                  //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT MemowyTwaining;                         //Atomic Tabwe,  used onwy by Bios
  USHOWT EnabweSpweadSpectwumOnPPWW;             //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.2
  USHOWT TMDSAOutputContwow;                     //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT SetVowtage;                             //Function Tabwe,diwectwy and/ow indiwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DAC1OutputContwow;                      //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT WeadEfuseVawue;                         //Atomic Tabwe,  diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT ComputeMemowyCwockPawam;                //Function Tabwe,onwy used by Bios, obsowete soon.Switch to use "WeadEDIDFwomHWAssistedI2C"
  USHOWT CwockSouwce;                            //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom ASIC_Init
  USHOWT MemowyDeviceInit;                       //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom SetMemowyCwock
  USHOWT GetDispObjectInfo;                      //Atomic Tabwe,  indiwectwy used by vawious SW components,cawwed fwom EnabweVGAWendew
  USHOWT DIG1EncodewContwow;                     //Atomic Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DIG2EncodewContwow;                     //Atomic Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DIG1TwansmittewContwow;                 //Atomic Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT DIG2TwansmittewContwow;                 //Atomic Tabwe,diwectwy used by vawious SW components,watest vewsion 1.1
  USHOWT PwocessAuxChannewTwansaction;           //Function Tabwe,onwy used by Bios
  USHOWT DPEncodewSewvice;                       //Function Tabwe,onwy used by Bios
  USHOWT GetVowtageInfo;                         //Function Tabwe,onwy used by Bios since SI
}ATOM_MASTEW_WIST_OF_COMMAND_TABWES;

// Fow backwawd compatibwe
#define WeadEDIDFwomHWAssistedI2C                PwocessI2cChannewTwansaction
#define DPTwanswatowContwow                      DIG2EncodewContwow
#define UNIPHYTwansmittewContwow                 DIG1TwansmittewContwow
#define WVTMATwansmittewContwow                  DIG2TwansmittewContwow
#define SetCWTC_DPM_State                        GetConditionawGowdenSetting
#define ASIC_StaticPwwMgtStatusChange            SetUniphyInstance
#define HPDIntewwuptSewvice                      WeadHWAssistedI2CStatus
#define EnabweVGA_Access                         GetSCWKOvewMCWKWatio
#define EnabweYUV                                GetDispObjectInfo
#define DynamicCwockGating                       EnabweDispPowewGating
#define SetupHWAssistedI2CStatus                 ComputeMemowyCwockPawam
#define DAC2OutputContwow                        WeadEfuseVawue

#define TMDSAEncodewContwow                      PatchMCSetting
#define WVDSEncodewContwow                       MC_SEQ_Contwow
#define WCD1OutputContwow                        HW_Misc_Opewation
#define TV1OutputContwow                         Gfx_Hawvesting
#define TVEncodewContwow                         SMC_Init
#define EnabweHW_IconCuwsow                      SetDCECwock
#define SetCWTC_Wepwication                      GetSMUCwockInfo

#define MemowyWefweshConvewsion                  Gfx_Init

typedef stwuct _ATOM_MASTEW_COMMAND_TABWE
{
  ATOM_COMMON_TABWE_HEADEW           sHeadew;
  ATOM_MASTEW_WIST_OF_COMMAND_TABWES WistOfCommandTabwes;
}ATOM_MASTEW_COMMAND_TABWE;

/****************************************************************************/
// Stwuctuwes used in evewy command tabwe
/****************************************************************************/
typedef stwuct _ATOM_TABWE_ATTWIBUTE
{
#if ATOM_BIG_ENDIAN
  USHOWT  UpdatedByUtiwity:1;         //[15]=Tabwe updated by utiwity fwag
  USHOWT  PS_SizeInBytes:7;           //[14:8]=Size of pawametew space in Bytes (muwtipwe of a dwowd),
  USHOWT  WS_SizeInBytes:8;           //[7:0]=Size of wowkspace in Bytes (in muwtipwe of a dwowd),
#ewse
  USHOWT  WS_SizeInBytes:8;           //[7:0]=Size of wowkspace in Bytes (in muwtipwe of a dwowd),
  USHOWT  PS_SizeInBytes:7;           //[14:8]=Size of pawametew space in Bytes (muwtipwe of a dwowd),
  USHOWT  UpdatedByUtiwity:1;         //[15]=Tabwe updated by utiwity fwag
#endif
}ATOM_TABWE_ATTWIBUTE;

/****************************************************************************/
// Common headew fow aww command tabwes.
// Evewy tabwe pointed by _ATOM_MASTEW_COMMAND_TABWE has this common headew.
// And the pointew actuawwy points to this headew.
/****************************************************************************/
typedef stwuct _ATOM_COMMON_WOM_COMMAND_TABWE_HEADEW
{
  ATOM_COMMON_TABWE_HEADEW CommonHeadew;
  ATOM_TABWE_ATTWIBUTE     TabweAttwibute;
}ATOM_COMMON_WOM_COMMAND_TABWE_HEADEW;

/****************************************************************************/
// Stwuctuwes used by ComputeMemowyEnginePWWTabwe
/****************************************************************************/

#define COMPUTE_MEMOWY_PWW_PAWAM        1
#define COMPUTE_ENGINE_PWW_PAWAM        2
#define ADJUST_MC_SETTING_PAWAM         3

/****************************************************************************/
// Stwuctuwes used by AdjustMemowyContwowwewTabwe
/****************************************************************************/
typedef stwuct _ATOM_ADJUST_MEMOWY_CWOCK_FWEQ
{
#if ATOM_BIG_ENDIAN
  UWONG uwPointewWetuwnFwag:1;      // BYTE_3[7]=1 - Wetuwn the pointew to the wight Data Bwock; BYTE_3[7]=0 - Pwogwam the wight Data Bwock
  UWONG uwMemowyModuweNumbew:7;     // BYTE_3[6:0]
  UWONG uwCwockFweq:24;
#ewse
  UWONG uwCwockFweq:24;
  UWONG uwMemowyModuweNumbew:7;     // BYTE_3[6:0]
  UWONG uwPointewWetuwnFwag:1;      // BYTE_3[7]=1 - Wetuwn the pointew to the wight Data Bwock; BYTE_3[7]=0 - Pwogwam the wight Data Bwock
#endif
}ATOM_ADJUST_MEMOWY_CWOCK_FWEQ;
#define POINTEW_WETUWN_FWAG             0x80

typedef stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS
{
  UWONG   uwCwock;        //When wetuwen, it's the we-cawcuwated cwock based on given Fb_div Post_Div and wef_div
  UCHAW   ucAction;       //0:wesewved //1:Memowy //2:Engine
  UCHAW   ucWesewved;     //may expand to wetuwn wawgew Fbdiv watew
  UCHAW   ucFbDiv;        //wetuwn vawue
  UCHAW   ucPostDiv;      //wetuwn vawue
}COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS;

typedef stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V2
{
  UWONG   uwCwock;        //When wetuwn, [23:0] wetuwn weaw cwock
  UCHAW   ucAction;       //0:wesewved;COMPUTE_MEMOWY_PWW_PAWAM:Memowy;COMPUTE_ENGINE_PWW_PAWAM:Engine. it wetuwn wef_div to be wwitten to wegistew
  USHOWT  usFbDiv;          //wetuwn Feedback vawue to be wwitten to wegistew
  UCHAW   ucPostDiv;      //wetuwn post div to be wwitten to wegistew
}COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V2;

#define COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_PS_AWWOCATION   COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS

#define SET_CWOCK_FWEQ_MASK                       0x00FFFFFF  //Cwock change tabwes onwy take bit [23:0] as the wequested cwock vawue
#define USE_NON_BUS_CWOCK_MASK                    0x01000000  //Appwicabwe to both memowy and engine cwock change, when set, it uses anothew cwock as the tempowawy cwock (engine uses memowy and vice vewsa)
#define USE_MEMOWY_SEWF_WEFWESH_MASK              0x02000000   //Onwy appwicabwe to memowy cwock change, when set, using memowy sewf wefwesh duwing cwock twansition
#define SKIP_INTEWNAW_MEMOWY_PAWAMETEW_CHANGE     0x04000000  //Onwy appwicabwe to memowy cwock change, when set, the tabwe wiww skip pwedefined intewnaw memowy pawametew change
#define FIWST_TIME_CHANGE_CWOCK                   0x08000000   //Appwicabwe to both memowy and engine cwock change,when set, it means this is 1st time to change cwock aftew ASIC bootup
#define SKIP_SW_PWOGWAM_PWW                       0x10000000   //Appwicabwe to both memowy and engine cwock change, when set, it means the tabwe wiww not pwogwam SPWW/MPWW
#define USE_SS_ENABWED_PIXEW_CWOCK                USE_NON_BUS_CWOCK_MASK

#define b3USE_NON_BUS_CWOCK_MASK                  0x01       //Appwicabwe to both memowy and engine cwock change, when set, it uses anothew cwock as the tempowawy cwock (engine uses memowy and vice vewsa)
#define b3USE_MEMOWY_SEWF_WEFWESH                 0x02        //Onwy appwicabwe to memowy cwock change, when set, using memowy sewf wefwesh duwing cwock twansition
#define b3SKIP_INTEWNAW_MEMOWY_PAWAMETEW_CHANGE   0x04       //Onwy appwicabwe to memowy cwock change, when set, the tabwe wiww skip pwedefined intewnaw memowy pawametew change
#define b3FIWST_TIME_CHANGE_CWOCK                 0x08       //Appwicabwe to both memowy and engine cwock change,when set, it means this is 1st time to change cwock aftew ASIC bootup
#define b3SKIP_SW_PWOGWAM_PWW                     0x10       //Appwicabwe to both memowy and engine cwock change, when set, it means the tabwe wiww not pwogwam SPWW/MPWW
#define b3DWAM_SEWF_WEFWESH_EXIT                  0x20       //Appwicabwe to DWAM sewf wefwesh exit onwy. when set, it means it wiww go to pwogwam DWAM sewf wefwesh exit path
#define b3SWIOV_INIT_BOOT                         0x40       //Use by HV GPU dwivew onwy, to woad uCode. fow ASIC_InitTabwe SCWK pawametew onwy
#define b3SWIOV_WOAD_UCODE                        0x40       //Use by HV GPU dwivew onwy, to woad uCode. fow ASIC_InitTabwe SCWK pawametew onwy
#define b3SWIOV_SKIP_ASIC_INIT                    0x02       //Use by HV GPU dwivew onwy, skip ASIC_Init fow pwimawy adaptew boot. fow ASIC_InitTabwe SCWK pawametew onwy

typedef stwuct _ATOM_COMPUTE_CWOCK_FWEQ
{
#if ATOM_BIG_ENDIAN
  UWONG uwComputeCwockFwag:8;                 // =1: COMPUTE_MEMOWY_PWW_PAWAM, =2: COMPUTE_ENGINE_PWW_PAWAM
  UWONG uwCwockFweq:24;                       // in unit of 10kHz
#ewse
  UWONG uwCwockFweq:24;                       // in unit of 10kHz
  UWONG uwComputeCwockFwag:8;                 // =1: COMPUTE_MEMOWY_PWW_PAWAM, =2: COMPUTE_ENGINE_PWW_PAWAM
#endif
}ATOM_COMPUTE_CWOCK_FWEQ;

typedef stwuct _ATOM_S_MPWW_FB_DIVIDEW
{
  USHOWT usFbDivFwac;
  USHOWT usFbDiv;
}ATOM_S_MPWW_FB_DIVIDEW;

typedef stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V3
{
  union
  {
    ATOM_COMPUTE_CWOCK_FWEQ  uwCwock;         //Input Pawametew
    UWONG uwCwockPawams;                      //UWONG access fow BE
    ATOM_S_MPWW_FB_DIVIDEW   uwFbDiv;         //Output Pawametew
  };
  UCHAW   ucWefDiv;                           //Output Pawametew
  UCHAW   ucPostDiv;                          //Output Pawametew
  UCHAW   ucCntwFwag;                         //Output Pawametew
  UCHAW   ucWesewved;
}COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V3;

// ucCntwFwag
#define ATOM_PWW_CNTW_FWAG_PWW_POST_DIV_EN          1
#define ATOM_PWW_CNTW_FWAG_MPWW_VCO_MODE            2
#define ATOM_PWW_CNTW_FWAG_FWACTION_DISABWE         4
#define ATOM_PWW_CNTW_FWAG_SPWW_ISPAWE_9                  8


// V4 awe onwy used fow APU which PWW outside GPU
typedef stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4
{
#if ATOM_BIG_ENDIAN
  UWONG  ucPostDiv:8;        //wetuwn pawametew: post dividew which is used to pwogwam to wegistew diwectwy
  UWONG  uwCwock:24;         //Input= tawget cwock, output = actuaw cwock
#ewse
  UWONG  uwCwock:24;         //Input= tawget cwock, output = actuaw cwock
  UWONG  ucPostDiv:8;        //wetuwn pawametew: post dividew which is used to pwogwam to wegistew diwectwy
#endif
}COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4;

typedef stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V5
{
  union
  {
    ATOM_COMPUTE_CWOCK_FWEQ  uwCwock;         //Input Pawametew
    UWONG uwCwockPawams;                      //UWONG access fow BE
    ATOM_S_MPWW_FB_DIVIDEW   uwFbDiv;         //Output Pawametew
  };
  UCHAW   ucWefDiv;                           //Output Pawametew
  UCHAW   ucPostDiv;                          //Output Pawametew
  union
  {
    UCHAW   ucCntwFwag;                       //Output Fwags
    UCHAW   ucInputFwag;                      //Input Fwags. ucInputFwag[0] - Stwobe(1)/Pewfowmance(0) mode
  };
  UCHAW   ucWesewved;
}COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V5;


typedef stwuct _COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_6
{
  ATOM_COMPUTE_CWOCK_FWEQ  uwCwock;         //Input Pawametew
  UWONG   uwWesewved[2];
}COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_6;

//ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag
#define COMPUTE_GPUCWK_INPUT_FWAG_CWK_TYPE_MASK            0x0f
#define COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK           0x00
#define COMPUTE_GPUCWK_INPUT_FWAG_SCWK                     0x01


typedef stwuct _COMPUTE_GPU_CWOCK_OUTPUT_PAWAMETEWS_V1_6
{
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4  uwCwock;         //Output Pawametew: ucPostDiv=DFS dividew
  ATOM_S_MPWW_FB_DIVIDEW   uwFbDiv;         //Output Pawametew: PWW FB dividew
  UCHAW   ucPwwWefDiv;                      //Output Pawametew: PWW wef dividew
  UCHAW   ucPwwPostDiv;                     //Output Pawametew: PWW post dividew
  UCHAW   ucPwwCntwFwag;                    //Output Fwags: contwow fwag
  UCHAW   ucWesewved;
}COMPUTE_GPU_CWOCK_OUTPUT_PAWAMETEWS_V1_6;

//ucPwwCntwFwag
#define SPWW_CNTW_FWAG_VCO_MODE_MASK            0x03

typedef stwuct _COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_7
{
  ATOM_COMPUTE_CWOCK_FWEQ  uwCwock;         //Input Pawametew
  UWONG   uwWesewved[5];
}COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_7;

//ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag
#define COMPUTE_GPUCWK_INPUT_FWAG_CWK_TYPE_MASK            0x0f
#define COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK           0x00
#define COMPUTE_GPUCWK_INPUT_FWAG_SCWK                     0x01

typedef stwuct _COMPUTE_GPU_CWOCK_OUTPUT_PAWAMETEWS_V1_7
{
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4  uwCwock;         //Output Pawametew: ucPostDiv=DFS dividew
  USHOWT  usScwk_fcw_fwac;                  //fwactionaw dividew of fcw = usScwk_fcw_fwac/65536
  USHOWT  usScwk_fcw_int;                   //integew dividew of fcwc
  UCHAW   ucScwkPostDiv;                    //PWW post dividew = 2^ucScwkPostDiv
  UCHAW   ucScwkVcoMode;                    //0: 4G~8Ghz, 1:3G~6Ghz,3: 2G~4Ghz, 2:Wesewved
  UCHAW   ucScwkPwwWange;                   //GweenTabwe SCWK PWW wange entwy index ( 0~7 )
  UCHAW   ucSscEnabwe;
  USHOWT  usSsc_fcw1_fwac;                  //fcw1_fwac when SSC enabwe
  USHOWT  usSsc_fcw1_int;                   //fcw1_int when SSC enabwe
  USHOWT  usWesewved;
  USHOWT  usPcc_fcw_int;
  USHOWT  usSsc_fcw_swew_fwac;              //fcw_swew_fwac when SSC enabwe
  USHOWT  usPcc_fcw_swew_fwac;
}COMPUTE_GPU_CWOCK_OUTPUT_PAWAMETEWS_V1_7;

// ucInputFwag
#define ATOM_PWW_INPUT_FWAG_PWW_STWOBE_MODE_EN  1   // 1-StwobeMode, 0-PewfowmanceMode

// use fow ComputeMemowyCwockPawamTabwe
typedef stwuct _COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_1
{
  union
  {
    UWONG  uwCwock;
    ATOM_S_MPWW_FB_DIVIDEW   uwFbDiv;         //Output:UPPEW_WOWD=FB_DIV_INTEGEW,  WOWEW_WOWD=FB_DIV_FWAC shw (16-FB_FWACTION_BITS)
  };
  UCHAW   ucDwwSpeed;                         //Output
  UCHAW   ucPostDiv;                          //Output
  union{
    UCHAW   ucInputFwag;                      //Input : ATOM_PWW_INPUT_FWAG_PWW_STWOBE_MODE_EN: 1-StwobeMode, 0-PewfowmanceMode
    UCHAW   ucPwwCntwFwag;                    //Output:
  };
  UCHAW   ucBWCntw;
}COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_1;

// definition of ucInputFwag
#define MPWW_INPUT_FWAG_STWOBE_MODE_EN          0x01
// definition of ucPwwCntwFwag
#define MPWW_CNTW_FWAG_VCO_MODE_MASK            0x03
#define MPWW_CNTW_FWAG_BYPASS_DQ_PWW            0x04
#define MPWW_CNTW_FWAG_QDW_ENABWE               0x08
#define MPWW_CNTW_FWAG_AD_HAWF_WATE             0x10

//MPWW_CNTW_FWAG_BYPASS_AD_PWW has a wwong name, shouwd be BYPASS_DQ_PWW
#define MPWW_CNTW_FWAG_BYPASS_AD_PWW            0x04

// use fow ComputeMemowyCwockPawamTabwe
typedef stwuct _COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_2
{
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4 uwCwock;
  UWONG uwWesewved;
}COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_2;

typedef stwuct _COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_3
{
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4 uwCwock;
  USHOWT  usMcwk_fcw_fwac;                  //fwactionaw dividew of fcw = usScwk_fcw_fwac/65536
  USHOWT  usMcwk_fcw_int;                   //integew dividew of fcwc
}COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_3;

//Input pawametew of DynamicMemowySettingsTabwe
//when ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag = COMPUTE_MEMOWY_PWW_PAWAM
typedef stwuct _DYNAMICE_MEMOWY_SETTINGS_PAWAMETEW
{
  ATOM_COMPUTE_CWOCK_FWEQ uwCwock;
  UWONG uwWesewved[2];
}DYNAMICE_MEMOWY_SETTINGS_PAWAMETEW;

//Input pawametew of DynamicMemowySettingsTabwe
//when ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag == COMPUTE_ENGINE_PWW_PAWAM
typedef stwuct _DYNAMICE_ENGINE_SETTINGS_PAWAMETEW
{
  ATOM_COMPUTE_CWOCK_FWEQ uwCwock;
  UWONG uwMemowyCwock;
  UWONG uwWesewved;
}DYNAMICE_ENGINE_SETTINGS_PAWAMETEW;

//Input pawametew of DynamicMemowySettingsTabwe vew2.1 and above
//when ATOM_COMPUTE_CWOCK_FWEQ.uwComputeCwockFwag == ADJUST_MC_SETTING_PAWAM
typedef stwuct _DYNAMICE_MC_DPM_SETTINGS_PAWAMETEW
{
  ATOM_COMPUTE_CWOCK_FWEQ uwCwock;
  UCHAW ucMcwkDPMState;
  UCHAW ucWesewved[3];
  UWONG uwWesewved;
}DYNAMICE_MC_DPM_SETTINGS_PAWAMETEW;

//ucMcwkDPMState
#define DYNAMIC_MC_DPM_SETTING_WOW_DPM_STATE       0
#define DYNAMIC_MC_DPM_SETTING_MEDIUM_DPM_STATE    1
#define DYNAMIC_MC_DPM_SETTING_HIGH_DPM_STATE      2

typedef union _DYNAMICE_MEMOWY_SETTINGS_PAWAMETEW_V2_1
{
  DYNAMICE_MEMOWY_SETTINGS_PAWAMETEW asMCWeg;
  DYNAMICE_ENGINE_SETTINGS_PAWAMETEW asMCAwbWeg;
  DYNAMICE_MC_DPM_SETTINGS_PAWAMETEW asDPMMCWeg;
}DYNAMICE_MEMOWY_SETTINGS_PAWAMETEW_V2_1;


/****************************************************************************/
// Stwuctuwes used by SetEngineCwockTabwe
/****************************************************************************/
typedef stwuct _SET_ENGINE_CWOCK_PAWAMETEWS
{
  UWONG uwTawgetEngineCwock;          //In 10Khz unit
}SET_ENGINE_CWOCK_PAWAMETEWS;

typedef stwuct _SET_ENGINE_CWOCK_PS_AWWOCATION
{
  UWONG uwTawgetEngineCwock;          //In 10Khz unit
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_PS_AWWOCATION sWesewved;
}SET_ENGINE_CWOCK_PS_AWWOCATION;

typedef stwuct _SET_ENGINE_CWOCK_PS_AWWOCATION_V1_2
{
  UWONG uwTawgetEngineCwock;          //In 10Khz unit
  COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_7 sWesewved;
}SET_ENGINE_CWOCK_PS_AWWOCATION_V1_2;


/****************************************************************************/
// Stwuctuwes used by SetMemowyCwockTabwe
/****************************************************************************/
typedef stwuct _SET_MEMOWY_CWOCK_PAWAMETEWS
{
  UWONG uwTawgetMemowyCwock;          //In 10Khz unit
}SET_MEMOWY_CWOCK_PAWAMETEWS;

typedef stwuct _SET_MEMOWY_CWOCK_PS_AWWOCATION
{
  UWONG uwTawgetMemowyCwock;          //In 10Khz unit
  COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_PS_AWWOCATION sWesewved;
}SET_MEMOWY_CWOCK_PS_AWWOCATION;

/****************************************************************************/
// Stwuctuwes used by ASIC_Init.ctb
/****************************************************************************/
typedef stwuct _ASIC_INIT_PAWAMETEWS
{
  UWONG uwDefauwtEngineCwock;         //In 10Khz unit
  UWONG uwDefauwtMemowyCwock;         //In 10Khz unit
}ASIC_INIT_PAWAMETEWS;

typedef stwuct _ASIC_INIT_PS_AWWOCATION
{
  ASIC_INIT_PAWAMETEWS sASICInitCwocks;
  SET_ENGINE_CWOCK_PS_AWWOCATION sWesewved; //Cawwew doesn't need to init this stwuctuwe
}ASIC_INIT_PS_AWWOCATION;

typedef stwuct _ASIC_INIT_CWOCK_PAWAMETEWS
{
  UWONG uwCwkFweqIn10Khz:24;
  UWONG ucCwkFwag:8;
}ASIC_INIT_CWOCK_PAWAMETEWS;

typedef stwuct _ASIC_INIT_PAWAMETEWS_V1_2
{
  ASIC_INIT_CWOCK_PAWAMETEWS asScwkCwock;         //In 10Khz unit
  ASIC_INIT_CWOCK_PAWAMETEWS asMemCwock;          //In 10Khz unit
}ASIC_INIT_PAWAMETEWS_V1_2;

typedef stwuct _ASIC_INIT_PS_AWWOCATION_V1_2
{
  ASIC_INIT_PAWAMETEWS_V1_2 sASICInitCwocks;
  UWONG uwWesewved[8];
}ASIC_INIT_PS_AWWOCATION_V1_2;

/****************************************************************************/
// Stwuctuwe used by DynamicCwockGatingTabwe.ctb
/****************************************************************************/
typedef stwuct _DYNAMIC_CWOCK_GATING_PAWAMETEWS
{
  UCHAW ucEnabwe;                     // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW ucPadding[3];
}DYNAMIC_CWOCK_GATING_PAWAMETEWS;
#define  DYNAMIC_CWOCK_GATING_PS_AWWOCATION  DYNAMIC_CWOCK_GATING_PAWAMETEWS

/****************************************************************************/
// Stwuctuwe used by EnabweDispPowewGatingTabwe.ctb
/****************************************************************************/
typedef stwuct _ENABWE_DISP_POWEW_GATING_PAWAMETEWS_V2_1
{
  UCHAW ucDispPipeId;                 // ATOM_CWTC1, ATOM_CWTC2, ...
  UCHAW ucEnabwe;                     // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW ucPadding[2];
}ENABWE_DISP_POWEW_GATING_PAWAMETEWS_V2_1;

typedef stwuct _ENABWE_DISP_POWEW_GATING_PS_AWWOCATION
{
  UCHAW ucDispPipeId;                 // ATOM_CWTC1, ATOM_CWTC2, ...
  UCHAW ucEnabwe;                     // ATOM_ENABWE/ATOM_DISABWE/ATOM_INIT
  UCHAW ucPadding[2];
  UWONG uwWesewved[4];
}ENABWE_DISP_POWEW_GATING_PS_AWWOCATION;

/****************************************************************************/
// Stwuctuwe used by EnabweASIC_StaticPwwMgtTabwe.ctb
/****************************************************************************/
typedef stwuct _ENABWE_ASIC_STATIC_PWW_MGT_PAWAMETEWS
{
  UCHAW ucEnabwe;                     // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW ucPadding[3];
}ENABWE_ASIC_STATIC_PWW_MGT_PAWAMETEWS;
#define ENABWE_ASIC_STATIC_PWW_MGT_PS_AWWOCATION  ENABWE_ASIC_STATIC_PWW_MGT_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by DAC_WoadDetectionTabwe.ctb
/****************************************************************************/
typedef stwuct _DAC_WOAD_DETECTION_PAWAMETEWS
{
  USHOWT usDeviceID;                  //{ATOM_DEVICE_CWTx_SUPPOWT,ATOM_DEVICE_TVx_SUPPOWT,ATOM_DEVICE_CVx_SUPPOWT}
  UCHAW  ucDacType;                   //{ATOM_DAC_A,ATOM_DAC_B, ATOM_EXT_DAC}
  UCHAW  ucMisc;                                 //Vawid onwy when tabwe wevision =1.3 and above
}DAC_WOAD_DETECTION_PAWAMETEWS;

// DAC_WOAD_DETECTION_PAWAMETEWS.ucMisc
#define DAC_WOAD_MISC_YPwPb                  0x01

typedef stwuct _DAC_WOAD_DETECTION_PS_AWWOCATION
{
  DAC_WOAD_DETECTION_PAWAMETEWS            sDacwoad;
  UWONG                                    Wesewved[2];// Don't set this one, awwocation fow EXT DAC
}DAC_WOAD_DETECTION_PS_AWWOCATION;

/****************************************************************************/
// Stwuctuwes used by DAC1EncodewContwowTabwe.ctb and DAC2EncodewContwowTabwe.ctb
/****************************************************************************/
typedef stwuct _DAC_ENCODEW_CONTWOW_PAWAMETEWS
{
  USHOWT usPixewCwock;                // in 10KHz; fow bios convenient
  UCHAW  ucDacStandawd;               // See definition of ATOM_DACx_xxx, Fow DEC3.0, bit 7 used as intewnaw fwag to indicate DAC2 (==1) ow DAC1 (==0)
  UCHAW  ucAction;                    // 0: tuwn off encodew
                                      // 1: setup and tuwn on encodew
                                      // 7: ATOM_ENCODEW_INIT Initiawize DAC
}DAC_ENCODEW_CONTWOW_PAWAMETEWS;

#define DAC_ENCODEW_CONTWOW_PS_AWWOCATION  DAC_ENCODEW_CONTWOW_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by DIG1EncodewContwowTabwe
//                    DIG2EncodewContwowTabwe
//                    ExtewnawEncodewContwowTabwe
/****************************************************************************/
typedef stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS
{
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
  UCHAW  ucConfig;
                            // [2] Wink Sewect:
                            // =0: PHY winkA if bfWane<3
                            // =1: PHY winkB if bfWanes<3
                            // =0: PHY winkA+B if bfWanes=3
                            // [3] Twansmittew Sew
                            // =0: UNIPHY ow PCIEPHY
                            // =1: WVTMA
  UCHAW ucAction;           // =0: tuwn off encodew
                            // =1: tuwn on encodew
  UCHAW ucEncodewMode;
                            // =0: DP   encodew
                            // =1: WVDS encodew
                            // =2: DVI  encodew
                            // =3: HDMI encodew
                            // =4: SDVO encodew
  UCHAW ucWaneNum;          // how many wanes to enabwe
  UCHAW ucWesewved[2];
}DIG_ENCODEW_CONTWOW_PAWAMETEWS;
#define DIG_ENCODEW_CONTWOW_PS_AWWOCATION             DIG_ENCODEW_CONTWOW_PAWAMETEWS
#define EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEW            DIG_ENCODEW_CONTWOW_PAWAMETEWS

//ucConfig
#define ATOM_ENCODEW_CONFIG_DPWINKWATE_MASK           0x01
#define ATOM_ENCODEW_CONFIG_DPWINKWATE_1_62GHZ        0x00
#define ATOM_ENCODEW_CONFIG_DPWINKWATE_2_70GHZ        0x01
#define ATOM_ENCODEW_CONFIG_DPWINKWATE_5_40GHZ        0x02
#define ATOM_ENCODEW_CONFIG_WINK_SEW_MASK             0x04
#define ATOM_ENCODEW_CONFIG_WINKA                     0x00
#define ATOM_ENCODEW_CONFIG_WINKB                     0x04
#define ATOM_ENCODEW_CONFIG_WINKA_B                   ATOM_TWANSMITTEW_CONFIG_WINKA
#define ATOM_ENCODEW_CONFIG_WINKB_A                   ATOM_ENCODEW_CONFIG_WINKB
#define ATOM_ENCODEW_CONFIG_TWANSMITTEW_SEW_MASK      0x08
#define ATOM_ENCODEW_CONFIG_UNIPHY                    0x00
#define ATOM_ENCODEW_CONFIG_WVTMA                     0x08
#define ATOM_ENCODEW_CONFIG_TWANSMITTEW1              0x00
#define ATOM_ENCODEW_CONFIG_TWANSMITTEW2              0x08
#define ATOM_ENCODEW_CONFIG_DIGB                      0x80         // VBIOS Intewnaw use, outside SW shouwd set this bit=0
// ucAction
// ATOM_ENABWE:  Enabwe Encodew
// ATOM_DISABWE: Disabwe Encodew

//ucEncodewMode
#define ATOM_ENCODEW_MODE_DP                          0
#define ATOM_ENCODEW_MODE_WVDS                        1
#define ATOM_ENCODEW_MODE_DVI                         2
#define ATOM_ENCODEW_MODE_HDMI                        3
#define ATOM_ENCODEW_MODE_SDVO                        4
#define ATOM_ENCODEW_MODE_DP_AUDIO                    5
#define ATOM_ENCODEW_MODE_TV                          13
#define ATOM_ENCODEW_MODE_CV                          14
#define ATOM_ENCODEW_MODE_CWT                         15
#define ATOM_ENCODEW_MODE_DVO                         16
#define ATOM_ENCODEW_MODE_DP_SST                      ATOM_ENCODEW_MODE_DP    // Fow DP1.2
#define ATOM_ENCODEW_MODE_DP_MST                      5                       // Fow DP1.2


typedef stwuct _ATOM_DIG_ENCODEW_CONFIG_V2
{
#if ATOM_BIG_ENDIAN
    UCHAW ucWesewved1:2;
    UCHAW ucTwansmittewSew:2;     // =0: UniphyAB, =1: UniphyCD  =2: UniphyEF
    UCHAW ucWinkSew:1;            // =0: winkA/C/E =1: winkB/D/F
    UCHAW ucWesewved:1;
    UCHAW ucDPWinkWate:1;         // =0: 1.62Ghz, =1: 2.7Ghz
#ewse
    UCHAW ucDPWinkWate:1;         // =0: 1.62Ghz, =1: 2.7Ghz
    UCHAW ucWesewved:1;
    UCHAW ucWinkSew:1;            // =0: winkA/C/E =1: winkB/D/F
    UCHAW ucTwansmittewSew:2;     // =0: UniphyAB, =1: UniphyCD  =2: UniphyEF
    UCHAW ucWesewved1:2;
#endif
}ATOM_DIG_ENCODEW_CONFIG_V2;


typedef stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2
{
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
  ATOM_DIG_ENCODEW_CONFIG_V2 acConfig;
  UCHAW ucAction;
  UCHAW ucEncodewMode;
                            // =0: DP   encodew
                            // =1: WVDS encodew
                            // =2: DVI  encodew
                            // =3: HDMI encodew
                            // =4: SDVO encodew
  UCHAW ucWaneNum;          // how many wanes to enabwe
  UCHAW ucStatus;           // = DP_WINK_TWAINING_COMPWETE ow DP_WINK_TWAINING_INCOMPWETE, onwy used by VBIOS with command ATOM_ENCODEW_CMD_QUEWY_DP_WINK_TWAINING_STATUS
  UCHAW ucWesewved;
}DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2;

//ucConfig
#define ATOM_ENCODEW_CONFIG_V2_DPWINKWATE_MASK            0x01
#define ATOM_ENCODEW_CONFIG_V2_DPWINKWATE_1_62GHZ        0x00
#define ATOM_ENCODEW_CONFIG_V2_DPWINKWATE_2_70GHZ        0x01
#define ATOM_ENCODEW_CONFIG_V2_WINK_SEW_MASK              0x04
#define ATOM_ENCODEW_CONFIG_V2_WINKA                          0x00
#define ATOM_ENCODEW_CONFIG_V2_WINKB                          0x04
#define ATOM_ENCODEW_CONFIG_V2_TWANSMITTEW_SEW_MASK     0x18
#define ATOM_ENCODEW_CONFIG_V2_TWANSMITTEW1                0x00
#define ATOM_ENCODEW_CONFIG_V2_TWANSMITTEW2                0x08
#define ATOM_ENCODEW_CONFIG_V2_TWANSMITTEW3                0x10

// ucAction:
// ATOM_DISABWE
// ATOM_ENABWE
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_STAWT       0x08
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN1    0x09
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN2    0x0a
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN3    0x13
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_COMPWETE    0x0b
#define ATOM_ENCODEW_CMD_DP_VIDEO_OFF                 0x0c
#define ATOM_ENCODEW_CMD_DP_VIDEO_ON                  0x0d
#define ATOM_ENCODEW_CMD_QUEWY_DP_WINK_TWAINING_STATUS    0x0e
#define ATOM_ENCODEW_CMD_SETUP                        0x0f
#define ATOM_ENCODEW_CMD_SETUP_PANEW_MODE            0x10

// New Command fow DIGxEncodewContwowTabwe v1.5
#define ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN4    0x14
#define ATOM_ENCODEW_CMD_STWEAM_SETUP                 0x0F      //change name ATOM_ENCODEW_CMD_SETUP
#define ATOM_ENCODEW_CMD_WINK_SETUP                   0x11      //intewnaw use, cawwed by othew Command Tabwe
#define ATOM_ENCODEW_CMD_ENCODEW_BWANK                0x12      //intewnaw use, cawwed by othew Command Tabwe

// ucStatus
#define ATOM_ENCODEW_STATUS_WINK_TWAINING_COMPWETE    0x10
#define ATOM_ENCODEW_STATUS_WINK_TWAINING_INCOMPWETE  0x00

//ucTabweFowmatWevision=1
//ucTabweContentWevision=3
// Fowwowing function ENABWE sub-function wiww be used by dwivew when TMDS/HDMI/WVDS is used, disabwe function wiww be used by dwivew
typedef stwuct _ATOM_DIG_ENCODEW_CONFIG_V3
{
#if ATOM_BIG_ENDIAN
    UCHAW ucWesewved1:1;
    UCHAW ucDigSew:3;             // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In wegistew spec awso wefewwed as DIGA/B/C/D/E/F)
    UCHAW ucWesewved:3;
    UCHAW ucDPWinkWate:1;         // =0: 1.62Ghz, =1: 2.7Ghz
#ewse
    UCHAW ucDPWinkWate:1;         // =0: 1.62Ghz, =1: 2.7Ghz
    UCHAW ucWesewved:3;
    UCHAW ucDigSew:3;             // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In wegistew spec awso wefewwed as DIGA/B/C/D/E/F)
    UCHAW ucWesewved1:1;
#endif
}ATOM_DIG_ENCODEW_CONFIG_V3;

#define ATOM_ENCODEW_CONFIG_V3_DPWINKWATE_MASK            0x03
#define ATOM_ENCODEW_CONFIG_V3_DPWINKWATE_1_62GHZ        0x00
#define ATOM_ENCODEW_CONFIG_V3_DPWINKWATE_2_70GHZ        0x01
#define ATOM_ENCODEW_CONFIG_V3_ENCODEW_SEW                 0x70
#define ATOM_ENCODEW_CONFIG_V3_DIG0_ENCODEW                 0x00
#define ATOM_ENCODEW_CONFIG_V3_DIG1_ENCODEW                 0x10
#define ATOM_ENCODEW_CONFIG_V3_DIG2_ENCODEW                 0x20
#define ATOM_ENCODEW_CONFIG_V3_DIG3_ENCODEW                 0x30
#define ATOM_ENCODEW_CONFIG_V3_DIG4_ENCODEW                 0x40
#define ATOM_ENCODEW_CONFIG_V3_DIG5_ENCODEW                 0x50

typedef stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V3
{
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
  ATOM_DIG_ENCODEW_CONFIG_V3 acConfig;
  UCHAW ucAction;
  union{
    UCHAW ucEncodewMode;
                            // =0: DP   encodew
                            // =1: WVDS encodew
                            // =2: DVI  encodew
                            // =3: HDMI encodew
                            // =4: SDVO encodew
                            // =5: DP audio
    UCHAW ucPanewMode;        // onwy vawid when ucAction == ATOM_ENCODEW_CMD_SETUP_PANEW_MODE
                            // =0:     extewnaw DP
                            // =0x1:   intewnaw DP2
                            // =0x11:  intewnaw DP1 fow NutMeg/Twavis DP twanswatow
  };
  UCHAW ucWaneNum;          // how many wanes to enabwe
  UCHAW ucBitPewCowow;      // onwy vawid fow DP mode when ucAction = ATOM_ENCODEW_CMD_SETUP
  UCHAW ucWesewved;
}DIG_ENCODEW_CONTWOW_PAWAMETEWS_V3;

//ucTabweFowmatWevision=1
//ucTabweContentWevision=4
// stawt fwom NI
// Fowwowing function ENABWE sub-function wiww be used by dwivew when TMDS/HDMI/WVDS is used, disabwe function wiww be used by dwivew
typedef stwuct _ATOM_DIG_ENCODEW_CONFIG_V4
{
#if ATOM_BIG_ENDIAN
    UCHAW ucWesewved1:1;
    UCHAW ucDigSew:3;             // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In wegistew spec awso wefewwed as DIGA/B/C/D/E/F)
    UCHAW ucWesewved:2;
    UCHAW ucDPWinkWate:2;         // =0: 1.62Ghz, =1: 2.7Ghz, 2=5.4Ghz    <= Changed compawing to pwevious vewsion
#ewse
    UCHAW ucDPWinkWate:2;         // =0: 1.62Ghz, =1: 2.7Ghz, 2=5.4Ghz    <= Changed compawing to pwevious vewsion
    UCHAW ucWesewved:2;
    UCHAW ucDigSew:3;             // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In wegistew spec awso wefewwed as DIGA/B/C/D/E/F)
    UCHAW ucWesewved1:1;
#endif
}ATOM_DIG_ENCODEW_CONFIG_V4;

#define ATOM_ENCODEW_CONFIG_V4_DPWINKWATE_MASK            0x03
#define ATOM_ENCODEW_CONFIG_V4_DPWINKWATE_1_62GHZ        0x00
#define ATOM_ENCODEW_CONFIG_V4_DPWINKWATE_2_70GHZ        0x01
#define ATOM_ENCODEW_CONFIG_V4_DPWINKWATE_5_40GHZ        0x02
#define ATOM_ENCODEW_CONFIG_V4_DPWINKWATE_3_24GHZ        0x03
#define ATOM_ENCODEW_CONFIG_V4_ENCODEW_SEW                 0x70
#define ATOM_ENCODEW_CONFIG_V4_DIG0_ENCODEW                 0x00
#define ATOM_ENCODEW_CONFIG_V4_DIG1_ENCODEW                 0x10
#define ATOM_ENCODEW_CONFIG_V4_DIG2_ENCODEW                 0x20
#define ATOM_ENCODEW_CONFIG_V4_DIG3_ENCODEW                 0x30
#define ATOM_ENCODEW_CONFIG_V4_DIG4_ENCODEW                 0x40
#define ATOM_ENCODEW_CONFIG_V4_DIG5_ENCODEW                 0x50
#define ATOM_ENCODEW_CONFIG_V4_DIG6_ENCODEW                 0x60

typedef stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V4
{
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
  union{
  ATOM_DIG_ENCODEW_CONFIG_V4 acConfig;
  UCHAW ucConfig;
  };
  UCHAW ucAction;
  union{
    UCHAW ucEncodewMode;
                            // =0: DP   encodew
                            // =1: WVDS encodew
                            // =2: DVI  encodew
                            // =3: HDMI encodew
                            // =4: SDVO encodew
                            // =5: DP audio
    UCHAW ucPanewMode;      // onwy vawid when ucAction == ATOM_ENCODEW_CMD_SETUP_PANEW_MODE
                            // =0:     extewnaw DP
                            // =0x1:   intewnaw DP2
                            // =0x11:  intewnaw DP1 fow NutMeg/Twavis DP twanswatow
  };
  UCHAW ucWaneNum;          // how many wanes to enabwe
  UCHAW ucBitPewCowow;      // onwy vawid fow DP mode when ucAction = ATOM_ENCODEW_CMD_SETUP
  UCHAW ucHPD_ID;           // HPD ID (1-6). =0 means to skip HDP pwogwamming. New compawing to pwevious vewsion
}DIG_ENCODEW_CONTWOW_PAWAMETEWS_V4;

// define ucBitPewCowow:
#define PANEW_BPC_UNDEFINE                               0x00
#define PANEW_6BIT_PEW_COWOW                             0x01
#define PANEW_8BIT_PEW_COWOW                             0x02
#define PANEW_10BIT_PEW_COWOW                            0x03
#define PANEW_12BIT_PEW_COWOW                            0x04
#define PANEW_16BIT_PEW_COWOW                            0x05

//define ucPanewMode
#define DP_PANEW_MODE_EXTEWNAW_DP_MODE                   0x00
#define DP_PANEW_MODE_INTEWNAW_DP2_MODE                  0x01
#define DP_PANEW_MODE_INTEWNAW_DP1_MODE                  0x11


typedef stwuct _ENCODEW_STWEAM_SETUP_PAWAMETEWS_V5
{
  UCHAW ucDigId;           // 0~6 map to DIG0~DIG6
  UCHAW ucAction;          // =  ATOM_ENOCODEW_CMD_STWEAM_SETUP
  UCHAW ucDigMode;         // ATOM_ENCODEW_MODE_DP/ATOM_ENCODEW_MODE_DVI/ATOM_ENCODEW_MODE_HDMI
  UCHAW ucWaneNum;         // Wane numbew
  UWONG uwPixewCwock;      // Pixew Cwock in 10Khz
  UCHAW ucBitPewCowow;
  UCHAW ucWinkWateIn270Mhz;//= DP wink wate/270Mhz, =6: 1.62G  = 10: 2.7G, =20: 5.4Ghz, =30: 8.1Ghz etc
  UCHAW ucWesewved[2];
}ENCODEW_STWEAM_SETUP_PAWAMETEWS_V5;

typedef stwuct _ENCODEW_WINK_SETUP_PAWAMETEWS_V5
{
  UCHAW ucDigId;           // 0~6 map to DIG0~DIG6
  UCHAW ucAction;          // =  ATOM_ENOCODEW_CMD_WINK_SETUP
  UCHAW ucDigMode;         // ATOM_ENCODEW_MODE_DP/ATOM_ENCODEW_MODE_DVI/ATOM_ENCODEW_MODE_HDMI
  UCHAW ucWaneNum;         // Wane numbew
  UWONG uwSymCwock;        // Symbow Cwock in 10Khz
  UCHAW ucHPDSew;
  UCHAW ucDigEncodewSew;   // DIG stweam( fwont-end ) sewection, bit0 means DIG0 FE is enabwe,
  UCHAW ucWesewved[2];
}ENCODEW_WINK_SETUP_PAWAMETEWS_V5;

typedef stwuct _DP_PANEW_MODE_SETUP_PAWAMETEWS_V5
{
  UCHAW ucDigId;           // 0~6 map to DIG0~DIG6
  UCHAW ucAction;          // = ATOM_ENCODEW_CMD_DPWINK_SETUP
  UCHAW ucPanewMode;       // =0:     extewnaw DP
                           // =0x1:   intewnaw DP2
                           // =0x11:  intewnaw DP1 NutMeg/Twavis DP Twanswatow
  UCHAW ucWesewved;
  UWONG uwWesewved[2];
}DP_PANEW_MODE_SETUP_PAWAMETEWS_V5;

typedef stwuct _ENCODEW_GENEWIC_CMD_PAWAMETEWS_V5
{
  UCHAW ucDigId;           // 0~6 map to DIG0~DIG6
  UCHAW ucAction;          // = west of genewic encodew command which does not cawwy any pawametews
  UCHAW ucWesewved[2];
  UWONG uwWesewved[2];
}ENCODEW_GENEWIC_CMD_PAWAMETEWS_V5;

//ucDigId
#define ATOM_ENCODEW_CONFIG_V5_DIG0_ENCODEW                 0x00
#define ATOM_ENCODEW_CONFIG_V5_DIG1_ENCODEW                 0x01
#define ATOM_ENCODEW_CONFIG_V5_DIG2_ENCODEW                 0x02
#define ATOM_ENCODEW_CONFIG_V5_DIG3_ENCODEW                 0x03
#define ATOM_ENCODEW_CONFIG_V5_DIG4_ENCODEW                 0x04
#define ATOM_ENCODEW_CONFIG_V5_DIG5_ENCODEW                 0x05
#define ATOM_ENCODEW_CONFIG_V5_DIG6_ENCODEW                 0x06


typedef union _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V5
{
  ENCODEW_GENEWIC_CMD_PAWAMETEWS_V5  asCmdPawam;
  ENCODEW_STWEAM_SETUP_PAWAMETEWS_V5 asStweamPawam;
  ENCODEW_WINK_SETUP_PAWAMETEWS_V5  asWinkPawam;
  DP_PANEW_MODE_SETUP_PAWAMETEWS_V5 asDPPanewModePawam;
}DIG_ENCODEW_CONTWOW_PAWAMETEWS_V5;


/****************************************************************************/
// Stwuctuwes used by UNIPHYTwansmittewContwowTabwe
//                    WVTMATwansmittewContwowTabwe
//                    DVOOutputContwowTabwe
/****************************************************************************/
typedef stwuct _ATOM_DP_VS_MODE
{
  UCHAW ucWaneSew;
  UCHAW ucWaneSet;
}ATOM_DP_VS_MODE;

typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS
{
   union
   {
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
   USHOWT usInitInfo;         // when init uniphy,wowew 8bit is used fow connectow type defined in objectid.h
  ATOM_DP_VS_MODE asMode; // DP Vowtage swing mode
   };
  UCHAW ucConfig;
                                       // [0]=0: 4 wane Wink,
                                       //    =1: 8 wane Wink ( Duaw Winks TMDS )
                          // [1]=0: InCohewent mode
                                       //    =1: Cohewent Mode
                                       // [2] Wink Sewect:
                                      // =0: PHY winkA   if bfWane<3
                                       // =1: PHY winkB   if bfWanes<3
                                      // =0: PHY winkA+B if bfWanes=3
                          // [5:4]PCIE wane Sew
                          // =0: wane 0~3 ow 0~7
                          // =1: wane 4~7
                          // =2: wane 8~11 ow 8~15
                          // =3: wane 12~15
   UCHAW ucAction;              // =0: tuwn off encodew
                           // =1: tuwn on encodew
  UCHAW ucWesewved[4];
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS;

#define DIG_TWANSMITTEW_CONTWOW_PS_AWWOCATION      DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS

//ucInitInfo
#define ATOM_TWAMITTEW_INITINFO_CONNECTOW_MASK   0x00ff

//ucConfig
#define ATOM_TWANSMITTEW_CONFIG_8WANE_WINK         0x01
#define ATOM_TWANSMITTEW_CONFIG_COHEWENT            0x02
#define ATOM_TWANSMITTEW_CONFIG_WINK_SEW_MASK      0x04
#define ATOM_TWANSMITTEW_CONFIG_WINKA                  0x00
#define ATOM_TWANSMITTEW_CONFIG_WINKB                  0x04
#define ATOM_TWANSMITTEW_CONFIG_WINKA_B               0x00
#define ATOM_TWANSMITTEW_CONFIG_WINKB_A               0x04

#define ATOM_TWANSMITTEW_CONFIG_ENCODEW_SEW_MASK   0x08         // onwy used when ATOM_TWANSMITTEW_ACTION_ENABWE
#define ATOM_TWANSMITTEW_CONFIG_DIG1_ENCODEW      0x00            // onwy used when ATOM_TWANSMITTEW_ACTION_ENABWE
#define ATOM_TWANSMITTEW_CONFIG_DIG2_ENCODEW      0x08            // onwy used when ATOM_TWANSMITTEW_ACTION_ENABWE

#define ATOM_TWANSMITTEW_CONFIG_CWKSWC_MASK         0x30
#define ATOM_TWANSMITTEW_CONFIG_CWKSWC_PPWW         0x00
#define ATOM_TWANSMITTEW_CONFIG_CWKSWC_PCIE         0x20
#define ATOM_TWANSMITTEW_CONFIG_CWKSWC_XTAWIN      0x30
#define ATOM_TWANSMITTEW_CONFIG_WANE_SEW_MASK      0xc0
#define ATOM_TWANSMITTEW_CONFIG_WANE_0_3            0x00
#define ATOM_TWANSMITTEW_CONFIG_WANE_0_7            0x00
#define ATOM_TWANSMITTEW_CONFIG_WANE_4_7            0x40
#define ATOM_TWANSMITTEW_CONFIG_WANE_8_11            0x80
#define ATOM_TWANSMITTEW_CONFIG_WANE_8_15            0x80
#define ATOM_TWANSMITTEW_CONFIG_WANE_12_15         0xc0

//ucAction
#define ATOM_TWANSMITTEW_ACTION_DISABWE                      0
#define ATOM_TWANSMITTEW_ACTION_ENABWE                      1
#define ATOM_TWANSMITTEW_ACTION_WCD_BWOFF                   2
#define ATOM_TWANSMITTEW_ACTION_WCD_BWON                   3
#define ATOM_TWANSMITTEW_ACTION_BW_BWIGHTNESS_CONTWOW  4
#define ATOM_TWANSMITTEW_ACTION_WCD_SEWFTEST_STAWT       5
#define ATOM_TWANSMITTEW_ACTION_WCD_SEWFTEST_STOP          6
#define ATOM_TWANSMITTEW_ACTION_INIT                         7
#define ATOM_TWANSMITTEW_ACTION_DISABWE_OUTPUT          8
#define ATOM_TWANSMITTEW_ACTION_ENABWE_OUTPUT             9
#define ATOM_TWANSMITTEW_ACTION_SETUP                         10
#define ATOM_TWANSMITTEW_ACTION_SETUP_VSEMPH           11
#define ATOM_TWANSMITTEW_ACTION_POWEW_ON               12
#define ATOM_TWANSMITTEW_ACTION_POWEW_OFF              13

// Fowwowing awe used fow DigTwansmittewContwowTabwe vew1.2
typedef stwuct _ATOM_DIG_TWANSMITTEW_CONFIG_V2
{
#if ATOM_BIG_ENDIAN
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
  UCHAW ucWesewved:1;
  UCHAW fDPConnectow:1;             //bit4=0: DP connectow  =1: None DP connectow
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA( DIG inst0 ). =1: Data/cwk path souwce fwom DIGB ( DIG inst1 )
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F

  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
#ewse
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA( DIG inst0 ). =1: Data/cwk path souwce fwom DIGB ( DIG inst1 )
  UCHAW fDPConnectow:1;             //bit4=0: DP connectow  =1: None DP connectow
  UCHAW ucWesewved:1;
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
#endif
}ATOM_DIG_TWANSMITTEW_CONFIG_V2;

//ucConfig
//Bit0
#define ATOM_TWANSMITTEW_CONFIG_V2_DUAW_WINK_CONNECTOW         0x01

//Bit1
#define ATOM_TWANSMITTEW_CONFIG_V2_COHEWENT                      0x02

//Bit2
#define ATOM_TWANSMITTEW_CONFIG_V2_WINK_SEW_MASK              0x04
#define ATOM_TWANSMITTEW_CONFIG_V2_WINKA                       0x00
#define ATOM_TWANSMITTEW_CONFIG_V2_WINKB                        0x04

// Bit3
#define ATOM_TWANSMITTEW_CONFIG_V2_ENCODEW_SEW_MASK           0x08
#define ATOM_TWANSMITTEW_CONFIG_V2_DIG1_ENCODEW                0x00            // onwy used when ucAction == ATOM_TWANSMITTEW_ACTION_ENABWE ow ATOM_TWANSMITTEW_ACTION_SETUP
#define ATOM_TWANSMITTEW_CONFIG_V2_DIG2_ENCODEW                0x08            // onwy used when ucAction == ATOM_TWANSMITTEW_ACTION_ENABWE ow ATOM_TWANSMITTEW_ACTION_SETUP

// Bit4
#define ATOM_TWASMITTEW_CONFIG_V2_DP_CONNECTOW                 0x10

// Bit7:6
#define ATOM_TWANSMITTEW_CONFIG_V2_TWANSMITTEW_SEW_MASK     0xC0
#define ATOM_TWANSMITTEW_CONFIG_V2_TWANSMITTEW1              0x00   //AB
#define ATOM_TWANSMITTEW_CONFIG_V2_TWANSMITTEW2              0x40   //CD
#define ATOM_TWANSMITTEW_CONFIG_V2_TWANSMITTEW3              0x80   //EF

typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V2
{
   union
   {
  USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
   USHOWT usInitInfo;         // when init uniphy,wowew 8bit is used fow connectow type defined in objectid.h
  ATOM_DP_VS_MODE asMode; // DP Vowtage swing mode
   };
  ATOM_DIG_TWANSMITTEW_CONFIG_V2 acConfig;
   UCHAW ucAction;              // define as ATOM_TWANSMITEW_ACTION_XXX
  UCHAW ucWesewved[4];
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V2;

typedef stwuct _ATOM_DIG_TWANSMITTEW_CONFIG_V3
{
#if ATOM_BIG_ENDIAN
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
  UCHAW ucWefCwkSouwce:2;           //bit5:4: PPWW1 =0, PPWW2=1, EXT_CWK=2
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA/C/E. =1: Data/cwk path souwce fwom DIGB/D/F
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F
  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
#ewse
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA/C/E. =1: Data/cwk path souwce fwom DIGB/D/F
  UCHAW ucWefCwkSouwce:2;           //bit5:4: PPWW1 =0, PPWW2=1, EXT_CWK=2
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
#endif
}ATOM_DIG_TWANSMITTEW_CONFIG_V3;


typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V3
{
   union
   {
    USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
     USHOWT usInitInfo;         // when init uniphy,wowew 8bit is used fow connectow type defined in objectid.h
    ATOM_DP_VS_MODE asMode; // DP Vowtage swing mode
   };
  ATOM_DIG_TWANSMITTEW_CONFIG_V3 acConfig;
   UCHAW ucAction;                // define as ATOM_TWANSMITEW_ACTION_XXX
  UCHAW ucWaneNum;
  UCHAW ucWesewved[3];
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V3;

//ucConfig
//Bit0
#define ATOM_TWANSMITTEW_CONFIG_V3_DUAW_WINK_CONNECTOW         0x01

//Bit1
#define ATOM_TWANSMITTEW_CONFIG_V3_COHEWENT                      0x02

//Bit2
#define ATOM_TWANSMITTEW_CONFIG_V3_WINK_SEW_MASK              0x04
#define ATOM_TWANSMITTEW_CONFIG_V3_WINKA                       0x00
#define ATOM_TWANSMITTEW_CONFIG_V3_WINKB                        0x04

// Bit3
#define ATOM_TWANSMITTEW_CONFIG_V3_ENCODEW_SEW_MASK           0x08
#define ATOM_TWANSMITTEW_CONFIG_V3_DIG1_ENCODEW                0x00
#define ATOM_TWANSMITTEW_CONFIG_V3_DIG2_ENCODEW                0x08

// Bit5:4
#define ATOM_TWASMITTEW_CONFIG_V3_WEFCWK_SEW_MASK            0x30
#define ATOM_TWASMITTEW_CONFIG_V3_P1PWW                        0x00
#define ATOM_TWASMITTEW_CONFIG_V3_P2PWW                        0x10
#define ATOM_TWASMITTEW_CONFIG_V3_WEFCWK_SWC_EXT            0x20

// Bit7:6
#define ATOM_TWANSMITTEW_CONFIG_V3_TWANSMITTEW_SEW_MASK     0xC0
#define ATOM_TWANSMITTEW_CONFIG_V3_TWANSMITTEW1              0x00   //AB
#define ATOM_TWANSMITTEW_CONFIG_V3_TWANSMITTEW2              0x40   //CD
#define ATOM_TWANSMITTEW_CONFIG_V3_TWANSMITTEW3              0x80   //EF


/****************************************************************************/
// Stwuctuwes used by UNIPHYTwansmittewContwowTabwe V1.4
// ASIC Famiwies: NI
// ucTabweFowmatWevision=1
// ucTabweContentWevision=4
/****************************************************************************/
typedef stwuct _ATOM_DP_VS_MODE_V4
{
  UCHAW ucWaneSew;
 	union
	{
 	  UCHAW ucWaneSet;
 	  stwuct {
#if ATOM_BIG_ENDIAN
 		  UCHAW ucPOST_CUWSOW2:2;         //Bit[7:6] Post Cuwsow2 Wevew      <= New in V4
 		  UCHAW ucPWE_EMPHASIS:3;         //Bit[5:3] Pwe-emphasis Wevew
 		  UCHAW ucVOWTAGE_SWING:3;        //Bit[2:0] Vowtage Swing Wevew
#ewse
 		  UCHAW ucVOWTAGE_SWING:3;        //Bit[2:0] Vowtage Swing Wevew
 		  UCHAW ucPWE_EMPHASIS:3;         //Bit[5:3] Pwe-emphasis Wevew
 		  UCHAW ucPOST_CUWSOW2:2;         //Bit[7:6] Post Cuwsow2 Wevew      <= New in V4
#endif
		};
	};
}ATOM_DP_VS_MODE_V4;

typedef stwuct _ATOM_DIG_TWANSMITTEW_CONFIG_V4
{
#if ATOM_BIG_ENDIAN
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
  UCHAW ucWefCwkSouwce:2;           //bit5:4: PPWW1 =0, PPWW2=1, DCPWW=2, EXT_CWK=3   <= New
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA/C/E. =1: Data/cwk path souwce fwom DIGB/D/F
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F
  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
#ewse
  UCHAW fDuawWinkConnectow:1;       //bit0=1: Duaw Wink DVI connectow
  UCHAW fCohewentMode:1;            //bit1=1: Cohewent Mode ( fow DVI/HDMI mode )
  UCHAW ucWinkSew:1;                //bit2=0: Uniphy WINKA ow C ow E when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is A ow C ow E
                                    //    =1: Uniphy WINKB ow D ow F when fDuawWinkConnectow=0. when fDuawWinkConnectow=1, it means mastew wink of duaw wink is B ow D ow F
  UCHAW ucEncodewSew:1;             //bit3=0: Data/Cwk path souwce fwom DIGA/C/E. =1: Data/cwk path souwce fwom DIGB/D/F
  UCHAW ucWefCwkSouwce:2;           //bit5:4: PPWW1 =0, PPWW2=1, DCPWW=2, EXT_CWK=3   <= New
  UCHAW ucTwansmittewSew:2;         //bit7:6: =0 Dig Twansmittew 1 ( Uniphy AB )
                                    //        =1 Dig Twansmittew 2 ( Uniphy CD )
                                    //        =2 Dig Twansmittew 3 ( Uniphy EF )
#endif
}ATOM_DIG_TWANSMITTEW_CONFIG_V4;

typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V4
{
  union
  {
    USHOWT usPixewCwock;      // in 10KHz; fow bios convenient
    USHOWT usInitInfo;         // when init uniphy,wowew 8bit is used fow connectow type defined in objectid.h
    ATOM_DP_VS_MODE_V4 asMode; // DP Vowtage swing mode     Wedefined compawing to pwevious vewsion
  };
  union
  {
  ATOM_DIG_TWANSMITTEW_CONFIG_V4 acConfig;
  UCHAW ucConfig;
  };
  UCHAW ucAction;                // define as ATOM_TWANSMITEW_ACTION_XXX
  UCHAW ucWaneNum;
  UCHAW ucWesewved[3];
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V4;

//ucConfig
//Bit0
#define ATOM_TWANSMITTEW_CONFIG_V4_DUAW_WINK_CONNECTOW         0x01
//Bit1
#define ATOM_TWANSMITTEW_CONFIG_V4_COHEWENT                      0x02
//Bit2
#define ATOM_TWANSMITTEW_CONFIG_V4_WINK_SEW_MASK              0x04
#define ATOM_TWANSMITTEW_CONFIG_V4_WINKA                       0x00
#define ATOM_TWANSMITTEW_CONFIG_V4_WINKB                        0x04
// Bit3
#define ATOM_TWANSMITTEW_CONFIG_V4_ENCODEW_SEW_MASK           0x08
#define ATOM_TWANSMITTEW_CONFIG_V4_DIG1_ENCODEW                0x00
#define ATOM_TWANSMITTEW_CONFIG_V4_DIG2_ENCODEW                0x08
// Bit5:4
#define ATOM_TWANSMITTEW_CONFIG_V4_WEFCWK_SEW_MASK            0x30
#define ATOM_TWANSMITTEW_CONFIG_V4_P1PWW                       0x00
#define ATOM_TWANSMITTEW_CONFIG_V4_P2PWW                      0x10
#define ATOM_TWANSMITTEW_CONFIG_V4_DCPWW                      0x20   // New in _V4
#define ATOM_TWANSMITTEW_CONFIG_V4_WEFCWK_SWC_EXT           0x30   // Changed compawing to V3
// Bit7:6
#define ATOM_TWANSMITTEW_CONFIG_V4_TWANSMITTEW_SEW_MASK     0xC0
#define ATOM_TWANSMITTEW_CONFIG_V4_TWANSMITTEW1              0x00   //AB
#define ATOM_TWANSMITTEW_CONFIG_V4_TWANSMITTEW2              0x40   //CD
#define ATOM_TWANSMITTEW_CONFIG_V4_TWANSMITTEW3              0x80   //EF


typedef stwuct _ATOM_DIG_TWANSMITTEW_CONFIG_V5
{
#if ATOM_BIG_ENDIAN
  UCHAW ucWesewvd1:1;
  UCHAW ucHPDSew:3;
  UCHAW ucPhyCwkSwcId:2;
  UCHAW ucCohewentMode:1;
  UCHAW ucWesewved:1;
#ewse
  UCHAW ucWesewved:1;
  UCHAW ucCohewentMode:1;
  UCHAW ucPhyCwkSwcId:2;
  UCHAW ucHPDSew:3;
  UCHAW ucWesewvd1:1;
#endif
}ATOM_DIG_TWANSMITTEW_CONFIG_V5;

typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_5
{
  USHOWT usSymCwock;              // Encodew Cwock in 10kHz,(DP mode)= winkcwock/10, (TMDS/WVDS/HDMI)= pixew cwock,  (HDMI deep cowow), =pixew cwock * deep_cowow_watio
  UCHAW  ucPhyId;                   // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
  UCHAW  ucAction;                // define as ATOM_TWANSMITEW_ACTION_xxx
  UCHAW  ucWaneNum;                 // indicate wane numbew 1-8
  UCHAW  ucConnObjId;               // Connectow Object Id defined in ObjectId.h
  UCHAW  ucDigMode;                 // indicate DIG mode
  union{
  ATOM_DIG_TWANSMITTEW_CONFIG_V5 asConfig;
  UCHAW ucConfig;
  };
  UCHAW  ucDigEncodewSew;           // indicate DIG fwont end encodew
  UCHAW  ucDPWaneSet;
  UCHAW  ucWesewved;
  UCHAW  ucWesewved1;
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_5;

//ucPhyId
#define ATOM_PHY_ID_UNIPHYA                                 0
#define ATOM_PHY_ID_UNIPHYB                                 1
#define ATOM_PHY_ID_UNIPHYC                                 2
#define ATOM_PHY_ID_UNIPHYD                                 3
#define ATOM_PHY_ID_UNIPHYE                                 4
#define ATOM_PHY_ID_UNIPHYF                                 5
#define ATOM_PHY_ID_UNIPHYG                                 6

// ucDigEncodewSew
#define ATOM_TWANMSITTEW_V5__DIGA_SEW                       0x01
#define ATOM_TWANMSITTEW_V5__DIGB_SEW                       0x02
#define ATOM_TWANMSITTEW_V5__DIGC_SEW                       0x04
#define ATOM_TWANMSITTEW_V5__DIGD_SEW                       0x08
#define ATOM_TWANMSITTEW_V5__DIGE_SEW                       0x10
#define ATOM_TWANMSITTEW_V5__DIGF_SEW                       0x20
#define ATOM_TWANMSITTEW_V5__DIGG_SEW                       0x40

// ucDigMode
#define ATOM_TWANSMITTEW_DIGMODE_V5_DP                      0
#define ATOM_TWANSMITTEW_DIGMODE_V5_WVDS                    1
#define ATOM_TWANSMITTEW_DIGMODE_V5_DVI                     2
#define ATOM_TWANSMITTEW_DIGMODE_V5_HDMI                    3
#define ATOM_TWANSMITTEW_DIGMODE_V5_SDVO                    4
#define ATOM_TWANSMITTEW_DIGMODE_V5_DP_MST                  5

// ucDPWaneSet
#define DP_WANE_SET__0DB_0_4V                               0x00
#define DP_WANE_SET__0DB_0_6V                               0x01
#define DP_WANE_SET__0DB_0_8V                               0x02
#define DP_WANE_SET__0DB_1_2V                               0x03
#define DP_WANE_SET__3_5DB_0_4V                             0x08
#define DP_WANE_SET__3_5DB_0_6V                             0x09
#define DP_WANE_SET__3_5DB_0_8V                             0x0a
#define DP_WANE_SET__6DB_0_4V                               0x10
#define DP_WANE_SET__6DB_0_6V                               0x11
#define DP_WANE_SET__9_5DB_0_4V                             0x18

// ATOM_DIG_TWANSMITTEW_CONFIG_V5 asConfig;
// Bit1
#define ATOM_TWANSMITTEW_CONFIG_V5_COHEWENT                      0x02

// Bit3:2
#define ATOM_TWANSMITTEW_CONFIG_V5_WEFCWK_SEW_MASK            0x0c
#define ATOM_TWANSMITTEW_CONFIG_V5_WEFCWK_SEW_SHIFT          0x02

#define ATOM_TWANSMITTEW_CONFIG_V5_P1PWW                       0x00
#define ATOM_TWANSMITTEW_CONFIG_V5_P2PWW                      0x04
#define ATOM_TWANSMITTEW_CONFIG_V5_P0PWW                      0x08
#define ATOM_TWANSMITTEW_CONFIG_V5_WEFCWK_SWC_EXT           0x0c
// Bit6:4
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD_SEW_MASK                0x70
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD_SEW_SHIFT            0x04

#define ATOM_TWANSMITTEW_CONFIG_V5_NO_HPD_SEW                    0x00
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD1_SEW                      0x10
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD2_SEW                      0x20
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD3_SEW                      0x30
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD4_SEW                      0x40
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD5_SEW                      0x50
#define ATOM_TWANSMITTEW_CONFIG_V5_HPD6_SEW                      0x60

#define DIG_TWANSMITTEW_CONTWOW_PS_AWWOCATION_V1_5            DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_5

typedef stwuct _DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_6
{
  UCHAW ucPhyId;           // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
  UCHAW ucAction;          // define as ATOM_TWANSMITEW_ACTION_xxx
  union
  {
    UCHAW ucDigMode;       // ATOM_ENCODEW_MODE_DP/ATOM_ENCODEW_MODE_DVI/ATOM_ENCODEW_MODE_HDMI
    UCHAW ucDPWaneSet;     // DP vowtage swing and pwe-emphasis vawue defined in DPCD DP_WANE_SET, "DP_WANE_SET__xDB_y_zV"
  };
  UCHAW ucWaneNum;         // Wane numbew
  UWONG uwSymCwock;        // Symbow Cwock in 10Khz
  UCHAW ucHPDSew;          // =1: HPD1, =2: HPD2, .... =6: HPD6, =0: HPD is not assigned
  UCHAW ucDigEncodewSew;   // DIG stweam( fwont-end ) sewection, bit0 means DIG0 FE is enabwe,
  UCHAW ucConnObjId;       // Connectow Object Id defined in ObjectId.h
  UCHAW ucWesewved;
  UWONG uwWesewved;
}DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_6;


// ucDigEncodewSew
#define ATOM_TWANMSITTEW_V6__DIGA_SEW                       0x01
#define ATOM_TWANMSITTEW_V6__DIGB_SEW                       0x02
#define ATOM_TWANMSITTEW_V6__DIGC_SEW                       0x04
#define ATOM_TWANMSITTEW_V6__DIGD_SEW                       0x08
#define ATOM_TWANMSITTEW_V6__DIGE_SEW                       0x10
#define ATOM_TWANMSITTEW_V6__DIGF_SEW                       0x20
#define ATOM_TWANMSITTEW_V6__DIGG_SEW                       0x40

// ucDigMode
#define ATOM_TWANSMITTEW_DIGMODE_V6_DP                      0
#define ATOM_TWANSMITTEW_DIGMODE_V6_DVI                     2
#define ATOM_TWANSMITTEW_DIGMODE_V6_HDMI                    3
#define ATOM_TWANSMITTEW_DIGMODE_V6_DP_MST                  5

//ucHPDSew
#define ATOM_TWANSMITTEW_V6_NO_HPD_SEW                      0x00
#define ATOM_TWANSMITTEW_V6_HPD1_SEW                        0x01
#define ATOM_TWANSMITTEW_V6_HPD2_SEW                        0x02
#define ATOM_TWANSMITTEW_V6_HPD3_SEW                        0x03
#define ATOM_TWANSMITTEW_V6_HPD4_SEW                        0x04
#define ATOM_TWANSMITTEW_V6_HPD5_SEW                        0x05
#define ATOM_TWANSMITTEW_V6_HPD6_SEW                        0x06


/****************************************************************************/
// Stwuctuwes used by ExtewnawEncodewContwowTabwe V1.3
// ASIC Famiwies: Evewgween, Wwano, NI
// ucTabweFowmatWevision=1
// ucTabweContentWevision=3
/****************************************************************************/

typedef stwuct _EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEWS_V3
{
  union{
  USHOWT usPixewCwock;      // pixew cwock in 10Khz, vawid when ucAction=SETUP/ENABWE_OUTPUT
  USHOWT usConnectowId;     // connectow id, vawid when ucAction = INIT
  };
  UCHAW  ucConfig;          // indicate which encodew, and DP wink wate when ucAction = SETUP/ENABWE_OUTPUT
  UCHAW  ucAction;          //
  UCHAW  ucEncodewMode;     // encodew mode, onwy used when ucAction = SETUP/ENABWE_OUTPUT
  UCHAW  ucWaneNum;         // wane numbew, onwy used when ucAction = SETUP/ENABWE_OUTPUT
  UCHAW  ucBitPewCowow;     // output bit pew cowow, onwy vawid when ucAction = SETUP/ENABWE_OUTPUT and ucEncodeMode= DP
  UCHAW  ucWesewved;
}EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEWS_V3;

// ucAction
#define EXTEWANW_ENCODEW_ACTION_V3_DISABWE_OUTPUT         0x00
#define EXTEWANW_ENCODEW_ACTION_V3_ENABWE_OUTPUT          0x01
#define EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_INIT           0x07
#define EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_SETUP          0x0f
#define EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_BWANKING_OFF   0x10
#define EXTEWNAW_ENCODEW_ACTION_V3_ENCODEW_BWANKING       0x11
#define EXTEWNAW_ENCODEW_ACTION_V3_DACWOAD_DETECTION      0x12
#define EXTEWNAW_ENCODEW_ACTION_V3_DDC_SETUP              0x14

// ucConfig
#define EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_MASK            0x03
#define EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_1_62GHZ        0x00
#define EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_2_70GHZ        0x01
#define EXTEWNAW_ENCODEW_CONFIG_V3_DPWINKWATE_5_40GHZ        0x02
#define EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW_SEW_MAKS          0x70
#define EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW1                  0x00
#define EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW2                  0x10
#define EXTEWNAW_ENCODEW_CONFIG_V3_ENCODEW3                  0x20

typedef stwuct _EXTEWNAW_ENCODEW_CONTWOW_PS_AWWOCATION_V3
{
  EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEWS_V3 sExtEncodew;
  UWONG uwWesewved[2];
}EXTEWNAW_ENCODEW_CONTWOW_PS_AWWOCATION_V3;


/****************************************************************************/
// Stwuctuwes used by DAC1OuputContwowTabwe
//                    DAC2OuputContwowTabwe
//                    WVTMAOutputContwowTabwe  (Befowe DEC30)
//                    TMDSAOutputContwowTabwe  (Befowe DEC30)
/****************************************************************************/
typedef stwuct _DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
{
  UCHAW  ucAction;                    // Possibwe input:ATOM_ENABWE||ATOMDISABWE
                                      // When the dispway is WCD, in addition to above:
                                      // ATOM_WCD_BWOFF|| ATOM_WCD_BWON ||ATOM_WCD_BW_BWIGHTNESS_CONTWOW||ATOM_WCD_SEWFTEST_STAWT||
                                      // ATOM_WCD_SEWFTEST_STOP

  UCHAW  aucPadding[3];               // padding to DWOWD awigned
}DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS;

#define DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS


#define CWT1_OUTPUT_CONTWOW_PAWAMETEWS     DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define CWT1_OUTPUT_CONTWOW_PS_AWWOCATION  DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define CWT2_OUTPUT_CONTWOW_PAWAMETEWS     DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define CWT2_OUTPUT_CONTWOW_PS_AWWOCATION  DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define CV1_OUTPUT_CONTWOW_PAWAMETEWS      DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define CV1_OUTPUT_CONTWOW_PS_AWWOCATION   DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define TV1_OUTPUT_CONTWOW_PAWAMETEWS      DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define TV1_OUTPUT_CONTWOW_PS_AWWOCATION   DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define DFP1_OUTPUT_CONTWOW_PAWAMETEWS     DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define DFP1_OUTPUT_CONTWOW_PS_AWWOCATION  DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define DFP2_OUTPUT_CONTWOW_PAWAMETEWS     DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define DFP2_OUTPUT_CONTWOW_PS_AWWOCATION  DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define WCD1_OUTPUT_CONTWOW_PAWAMETEWS     DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define WCD1_OUTPUT_CONTWOW_PS_AWWOCATION  DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION

#define DVO_OUTPUT_CONTWOW_PAWAMETEWS      DISPWAY_DEVICE_OUTPUT_CONTWOW_PAWAMETEWS
#define DVO_OUTPUT_CONTWOW_PS_AWWOCATION   DIG_TWANSMITTEW_CONTWOW_PS_AWWOCATION
#define DVO_OUTPUT_CONTWOW_PAWAMETEWS_V3   DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS


typedef stwuct _WVTMA_OUTPUT_CONTWOW_PAWAMETEWS_V2
{
  // Possibwe vawue of ucAction
  // ATOM_TWANSMITTEW_ACTION_WCD_BWON
  // ATOM_TWANSMITTEW_ACTION_WCD_BWOFF
  // ATOM_TWANSMITTEW_ACTION_BW_BWIGHTNESS_CONTWOW
  // ATOM_TWANSMITTEW_ACTION_POWEW_ON
  // ATOM_TWANSMITTEW_ACTION_POWEW_OFF
  UCHAW  ucAction;
  UCHAW  ucBwiWevew;
  USHOWT usPwmFweq;                  // in unit of Hz, 200 means 200Hz
}WVTMA_OUTPUT_CONTWOW_PAWAMETEWS_V2;



/****************************************************************************/
// Stwuctuwes used by BwankCWTCTabwe
/****************************************************************************/
typedef stwuct _BWANK_CWTC_PAWAMETEWS
{
  UCHAW  ucCWTC;                       // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW  ucBwanking;                  // ATOM_BWANKING ow ATOM_BWANKINGOFF
  USHOWT usBwackCowowWCw;
  USHOWT usBwackCowowGY;
  USHOWT usBwackCowowBCb;
}BWANK_CWTC_PAWAMETEWS;
#define BWANK_CWTC_PS_AWWOCATION    BWANK_CWTC_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by EnabweCWTCTabwe
//                    EnabweCWTCMemWeqTabwe
//                    UpdateCWTC_DoubweBuffewWegistewsTabwe
/****************************************************************************/
typedef stwuct _ENABWE_CWTC_PAWAMETEWS
{
  UCHAW ucCWTC;                         // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW ucEnabwe;                     // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW ucPadding[2];
}ENABWE_CWTC_PAWAMETEWS;
#define ENABWE_CWTC_PS_AWWOCATION   ENABWE_CWTC_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by SetCWTC_OvewScanTabwe
/****************************************************************************/
typedef stwuct _SET_CWTC_OVEWSCAN_PAWAMETEWS
{
  USHOWT usOvewscanWight;             // wight
  USHOWT usOvewscanWeft;              // weft
  USHOWT usOvewscanBottom;            // bottom
  USHOWT usOvewscanTop;               // top
  UCHAW  ucCWTC;                      // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW  ucPadding[3];
}SET_CWTC_OVEWSCAN_PAWAMETEWS;
#define SET_CWTC_OVEWSCAN_PS_AWWOCATION  SET_CWTC_OVEWSCAN_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by SetCWTC_WepwicationTabwe
/****************************************************************************/
typedef stwuct _SET_CWTC_WEPWICATION_PAWAMETEWS
{
  UCHAW ucH_Wepwication;              // howizontaw wepwication
  UCHAW ucV_Wepwication;              // vewticaw wepwication
  UCHAW usCWTC;                       // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW ucPadding;
}SET_CWTC_WEPWICATION_PAWAMETEWS;
#define SET_CWTC_WEPWICATION_PS_AWWOCATION  SET_CWTC_WEPWICATION_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by SewectCWTC_SouwceTabwe
/****************************************************************************/
typedef stwuct _SEWECT_CWTC_SOUWCE_PAWAMETEWS
{
  UCHAW ucCWTC;                         // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW ucDevice;                     // ATOM_DEVICE_CWT1|ATOM_DEVICE_CWT2|....
  UCHAW ucPadding[2];
}SEWECT_CWTC_SOUWCE_PAWAMETEWS;
#define SEWECT_CWTC_SOUWCE_PS_AWWOCATION  SEWECT_CWTC_SOUWCE_PAWAMETEWS

typedef stwuct _SEWECT_CWTC_SOUWCE_PAWAMETEWS_V2
{
  UCHAW ucCWTC;                         // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW ucEncodewID;                  // DAC1/DAC2/TVOUT/DIG1/DIG2/DVO
  UCHAW ucEncodeMode;                           // Encoding mode, onwy vawid when using DIG1/DIG2/DVO
  UCHAW ucPadding;
}SEWECT_CWTC_SOUWCE_PAWAMETEWS_V2;

//ucEncodewID
//#define ASIC_INT_DAC1_ENCODEW_ID                      0x00
//#define ASIC_INT_TV_ENCODEW_ID                           0x02
//#define ASIC_INT_DIG1_ENCODEW_ID                        0x03
//#define ASIC_INT_DAC2_ENCODEW_ID                        0x04
//#define ASIC_EXT_TV_ENCODEW_ID                           0x06
//#define ASIC_INT_DVO_ENCODEW_ID                           0x07
//#define ASIC_INT_DIG2_ENCODEW_ID                        0x09
//#define ASIC_EXT_DIG_ENCODEW_ID                           0x05

//ucEncodeMode
//#define ATOM_ENCODEW_MODE_DP                              0
//#define ATOM_ENCODEW_MODE_WVDS                           1
//#define ATOM_ENCODEW_MODE_DVI                              2
//#define ATOM_ENCODEW_MODE_HDMI                           3
//#define ATOM_ENCODEW_MODE_SDVO                           4
//#define ATOM_ENCODEW_MODE_TV                              13
//#define ATOM_ENCODEW_MODE_CV                              14
//#define ATOM_ENCODEW_MODE_CWT                              15


typedef stwuct _SEWECT_CWTC_SOUWCE_PAWAMETEWS_V3
{
  UCHAW ucCWTC;                         // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW ucEncodewID;                    // DAC1/DAC2/TVOUT/DIG1/DIG2/DVO
  UCHAW ucEncodeMode;                   // Encoding mode, onwy vawid when using DIG1/DIG2/DVO
  UCHAW ucDstBpc;                       // PANEW_6/8/10/12BIT_PEW_COWOW
}SEWECT_CWTC_SOUWCE_PAWAMETEWS_V3;


/****************************************************************************/
// Stwuctuwes used by SetPixewCwockTabwe
//                    GetPixewCwockTabwe
/****************************************************************************/
//Majow wevision=1., Minow wevision=1
typedef stwuct _PIXEW_CWOCK_PAWAMETEWS
{
  USHOWT usPixewCwock;                // in 10kHz unit; fow bios convenient = (WefCwk*FB_Div)/(Wef_Div*Post_Div)
                                      // 0 means disabwe PPWW
  USHOWT usWefDiv;                    // Wefewence dividew
  USHOWT usFbDiv;                     // feedback dividew
  UCHAW  ucPostDiv;                   // post dividew
  UCHAW  ucFwacFbDiv;                 // fwactionaw feedback dividew
  UCHAW  ucPpww;                      // ATOM_PPWW1 ow ATOM_PPW2
  UCHAW  ucWefDivSwc;                 // ATOM_PJITTEW ow ATO_NONPJITTEW
  UCHAW  ucCWTC;                      // Which CWTC uses this Ppww
  UCHAW  ucPadding;
}PIXEW_CWOCK_PAWAMETEWS;

//Majow wevision=1., Minow wevision=2, add ucMiscIfno
//ucMiscInfo:
#define MISC_FOWCE_WEPWOG_PIXEW_CWOCK 0x1
#define MISC_DEVICE_INDEX_MASK        0xF0
#define MISC_DEVICE_INDEX_SHIFT       4

typedef stwuct _PIXEW_CWOCK_PAWAMETEWS_V2
{
  USHOWT usPixewCwock;                // in 10kHz unit; fow bios convenient = (WefCwk*FB_Div)/(Wef_Div*Post_Div)
                                      // 0 means disabwe PPWW
  USHOWT usWefDiv;                    // Wefewence dividew
  USHOWT usFbDiv;                     // feedback dividew
  UCHAW  ucPostDiv;                   // post dividew
  UCHAW  ucFwacFbDiv;                 // fwactionaw feedback dividew
  UCHAW  ucPpww;                      // ATOM_PPWW1 ow ATOM_PPW2
  UCHAW  ucWefDivSwc;                 // ATOM_PJITTEW ow ATO_NONPJITTEW
  UCHAW  ucCWTC;                      // Which CWTC uses this Ppww
  UCHAW  ucMiscInfo;                  // Diffewent bits fow diffewent puwpose, bit [7:4] as device index, bit[0]=Fowce pwog
}PIXEW_CWOCK_PAWAMETEWS_V2;

//Majow wevision=1., Minow wevision=3, stwuctuwe/definition change
//ucEncodewMode:
//ATOM_ENCODEW_MODE_DP
//ATOM_ENOCDEW_MODE_WVDS
//ATOM_ENOCDEW_MODE_DVI
//ATOM_ENOCDEW_MODE_HDMI
//ATOM_ENOCDEW_MODE_SDVO
//ATOM_ENCODEW_MODE_TV                                          13
//ATOM_ENCODEW_MODE_CV                                          14
//ATOM_ENCODEW_MODE_CWT                                          15

//ucDVOConfig
//#define DVO_ENCODEW_CONFIG_WATE_SEW                     0x01
//#define DVO_ENCODEW_CONFIG_DDW_SPEED                  0x00
//#define DVO_ENCODEW_CONFIG_SDW_SPEED                  0x01
//#define DVO_ENCODEW_CONFIG_OUTPUT_SEW                  0x0c
//#define DVO_ENCODEW_CONFIG_WOW12BIT                     0x00
//#define DVO_ENCODEW_CONFIG_UPPEW12BIT                  0x04
//#define DVO_ENCODEW_CONFIG_24BIT                        0x08

//ucMiscInfo: awso changed, see bewow
#define PIXEW_CWOCK_MISC_FOWCE_PWOG_PPWW                  0x01
#define PIXEW_CWOCK_MISC_VGA_MODE                              0x02
#define PIXEW_CWOCK_MISC_CWTC_SEW_MASK                     0x04
#define PIXEW_CWOCK_MISC_CWTC_SEW_CWTC1                     0x00
#define PIXEW_CWOCK_MISC_CWTC_SEW_CWTC2                     0x04
#define PIXEW_CWOCK_MISC_USE_ENGINE_FOW_DISPCWK         0x08
#define PIXEW_CWOCK_MISC_WEF_DIV_SWC                    0x10
// V1.4 fow WoadWunnew
#define PIXEW_CWOCK_V4_MISC_SS_ENABWE               0x10
#define PIXEW_CWOCK_V4_MISC_COHEWENT_MODE           0x20


typedef stwuct _PIXEW_CWOCK_PAWAMETEWS_V3
{
  USHOWT usPixewCwock;                // in 10kHz unit; fow bios convenient = (WefCwk*FB_Div)/(Wef_Div*Post_Div)
                                      // 0 means disabwe PPWW. Fow VGA PPWW,make suwe this vawue is not 0.
  USHOWT usWefDiv;                    // Wefewence dividew
  USHOWT usFbDiv;                     // feedback dividew
  UCHAW  ucPostDiv;                   // post dividew
  UCHAW  ucFwacFbDiv;                 // fwactionaw feedback dividew
  UCHAW  ucPpww;                      // ATOM_PPWW1 ow ATOM_PPW2
  UCHAW  ucTwansmittewId;             // gwaphic encodew id defined in objectId.h
   union
   {
  UCHAW  ucEncodewMode;               // encodew type defined as ATOM_ENCODEW_MODE_DP/DVI/HDMI/
   UCHAW  ucDVOConfig;                           // when use DVO, need to know SDW/DDW, 12bit ow 24bit
   };
  UCHAW  ucMiscInfo;                  // bit[0]=Fowce pwogwam, bit[1]= set pcwk fow VGA, b[2]= CWTC sew
                                      // bit[3]=0:use PPWW fow dispcwk souwce, =1: use engine cwock fow dispcwock souwce
                                      // bit[4]=0:use XTAWIN as the souwce of wefewence dividew,=1 use the pwe-defined cwock as the souwce of wefewence dividew
}PIXEW_CWOCK_PAWAMETEWS_V3;

#define PIXEW_CWOCK_PAWAMETEWS_WAST                     PIXEW_CWOCK_PAWAMETEWS_V2
#define GET_PIXEW_CWOCK_PS_AWWOCATION                  PIXEW_CWOCK_PAWAMETEWS_WAST


typedef stwuct _PIXEW_CWOCK_PAWAMETEWS_V5
{
  UCHAW  ucCWTC;             // ATOM_CWTC1~6, indicate the CWTC contwowwew to
                             // dwive the pixew cwock. not used fow DCPWW case.
  union{
  UCHAW  ucWesewved;
  UCHAW  ucFwacFbDiv;        // [gphan] tempowawy to pwevent buiwd pwobwem.  wemove it aftew dwivew code is changed.
  };
  USHOWT usPixewCwock;       // tawget the pixew cwock to dwive the CWTC timing
                             // 0 means disabwe PPWW/DCPWW.
  USHOWT usFbDiv;            // feedback dividew integew pawt.
  UCHAW  ucPostDiv;          // post dividew.
  UCHAW  ucWefDiv;           // Wefewence dividew
  UCHAW  ucPpww;             // ATOM_PPWW1/ATOM_PPWW2/ATOM_DCPWW
  UCHAW  ucTwansmittewID;    // ASIC encodew id defined in objectId.h,
                             // indicate which gwaphic encodew wiww be used.
  UCHAW  ucEncodewMode;      // Encodew mode:
  UCHAW  ucMiscInfo;         // bit[0]= Fowce pwogwam PPWW
                             // bit[1]= when VGA timing is used.
                             // bit[3:2]= HDMI panew bit depth: =0: 24bpp =1:30bpp, =2:32bpp
                             // bit[4]= WefCwock souwce fow PPWW.
                             // =0: XTWAIN( defauwt mode )
                              // =1: othew extewnaw cwock souwce, which is pwe-defined
                             //     by VBIOS depend on the featuwe wequiwed.
                             // bit[7:5]: wesewved.
  UWONG  uwFbDivDecFwac;     // 20 bit feedback dividew decimaw fwaction pawt, wange fwom 1~999999 ( 0.000001 to 0.999999 )

}PIXEW_CWOCK_PAWAMETEWS_V5;

#define PIXEW_CWOCK_V5_MISC_FOWCE_PWOG_PPWW               0x01
#define PIXEW_CWOCK_V5_MISC_VGA_MODE                        0x02
#define PIXEW_CWOCK_V5_MISC_HDMI_BPP_MASK           0x0c
#define PIXEW_CWOCK_V5_MISC_HDMI_24BPP              0x00
#define PIXEW_CWOCK_V5_MISC_HDMI_30BPP              0x04
#define PIXEW_CWOCK_V5_MISC_HDMI_32BPP              0x08
#define PIXEW_CWOCK_V5_MISC_WEF_DIV_SWC             0x10

typedef stwuct _CWTC_PIXEW_CWOCK_FWEQ
{
#if ATOM_BIG_ENDIAN
  UWONG  ucCWTC:8;            // ATOM_CWTC1~6, indicate the CWTC contwowwew to
                              // dwive the pixew cwock. not used fow DCPWW case.
  UWONG  uwPixewCwock:24;     // tawget the pixew cwock to dwive the CWTC timing.
                              // 0 means disabwe PPWW/DCPWW. Expanded to 24 bits compawing to pwevious vewsion.
#ewse
  UWONG  uwPixewCwock:24;     // tawget the pixew cwock to dwive the CWTC timing.
                              // 0 means disabwe PPWW/DCPWW. Expanded to 24 bits compawing to pwevious vewsion.
  UWONG  ucCWTC:8;            // ATOM_CWTC1~6, indicate the CWTC contwowwew to
                              // dwive the pixew cwock. not used fow DCPWW case.
#endif
}CWTC_PIXEW_CWOCK_FWEQ;

typedef stwuct _PIXEW_CWOCK_PAWAMETEWS_V6
{
  union{
    CWTC_PIXEW_CWOCK_FWEQ uwCwtcPcwkFweq;    // pixew cwock and CWTC id fwequency
    UWONG uwDispEngCwkFweq;                  // dispcwk fwequency
  };
  USHOWT usFbDiv;            // feedback dividew integew pawt.
  UCHAW  ucPostDiv;          // post dividew.
  UCHAW  ucWefDiv;           // Wefewence dividew
  UCHAW  ucPpww;             // ATOM_PPWW1/ATOM_PPWW2/ATOM_DCPWW
  UCHAW  ucTwansmittewID;    // ASIC encodew id defined in objectId.h,
                             // indicate which gwaphic encodew wiww be used.
  UCHAW  ucEncodewMode;      // Encodew mode:
  UCHAW  ucMiscInfo;         // bit[0]= Fowce pwogwam PPWW
                             // bit[1]= when VGA timing is used.
                             // bit[3:2]= HDMI panew bit depth: =0: 24bpp =1:30bpp, =2:32bpp
                             // bit[4]= WefCwock souwce fow PPWW.
                             // =0: XTWAIN( defauwt mode )
                              // =1: othew extewnaw cwock souwce, which is pwe-defined
                             //     by VBIOS depend on the featuwe wequiwed.
                             // bit[7:5]: wesewved.
  UWONG  uwFbDivDecFwac;     // 20 bit feedback dividew decimaw fwaction pawt, wange fwom 1~999999 ( 0.000001 to 0.999999 )

}PIXEW_CWOCK_PAWAMETEWS_V6;

#define PIXEW_CWOCK_V6_MISC_FOWCE_PWOG_PPWW               0x01
#define PIXEW_CWOCK_V6_MISC_VGA_MODE                        0x02
#define PIXEW_CWOCK_V6_MISC_HDMI_BPP_MASK           0x0c
#define PIXEW_CWOCK_V6_MISC_HDMI_24BPP              0x00
#define PIXEW_CWOCK_V6_MISC_HDMI_36BPP              0x04
#define PIXEW_CWOCK_V6_MISC_HDMI_36BPP_V6           0x08    //fow V6, the cowwect definition fow 36bpp shouwd be 2 fow 36bpp(2:1)
#define PIXEW_CWOCK_V6_MISC_HDMI_30BPP              0x08
#define PIXEW_CWOCK_V6_MISC_HDMI_30BPP_V6           0x04    //fow V6, the cowwect definition fow 30bpp shouwd be 1 fow 36bpp(5:4)
#define PIXEW_CWOCK_V6_MISC_HDMI_48BPP              0x0c
#define PIXEW_CWOCK_V6_MISC_WEF_DIV_SWC             0x10
#define PIXEW_CWOCK_V6_MISC_GEN_DPWEFCWK            0x40
#define PIXEW_CWOCK_V6_MISC_DPWEFCWK_BYPASS         0x40

typedef stwuct _GET_DISP_PWW_STATUS_INPUT_PAWAMETEWS_V2
{
  PIXEW_CWOCK_PAWAMETEWS_V3 sDispCwkInput;
}GET_DISP_PWW_STATUS_INPUT_PAWAMETEWS_V2;

typedef stwuct _GET_DISP_PWW_STATUS_OUTPUT_PAWAMETEWS_V2
{
  UCHAW  ucStatus;
  UCHAW  ucWefDivSwc;                 // =1: wefewence cwock souwce fwom XTAWIN, =0: souwce fwom PCIE wef cwock
  UCHAW  ucWesewved[2];
}GET_DISP_PWW_STATUS_OUTPUT_PAWAMETEWS_V2;

typedef stwuct _GET_DISP_PWW_STATUS_INPUT_PAWAMETEWS_V3
{
  PIXEW_CWOCK_PAWAMETEWS_V5 sDispCwkInput;
}GET_DISP_PWW_STATUS_INPUT_PAWAMETEWS_V3;

typedef stwuct _PIXEW_CWOCK_PAWAMETEWS_V7
{
    UWONG  uwPixewCwock;               // tawget the pixew cwock to dwive the CWTC timing in unit of 100Hz.

    UCHAW  ucPpww;                     // ATOM_PHY_PWW0/ATOM_PHY_PWW1/ATOM_PPWW0
    UCHAW  ucTwansmittewID;            // ASIC encodew id defined in objectId.h,
                                       // indicate which gwaphic encodew wiww be used.
    UCHAW  ucEncodewMode;              // Encodew mode:
    UCHAW  ucMiscInfo;                 // bit[0]= Fowce pwogwam PWW fow pixcwk
                                       // bit[1]= Fowce pwogwam PHY PWW onwy ( intewnawwy used by VBIOS onwy in DP case which PHYPWW is pwogwammed fow SYMCWK, not Pixcwk )
                                       // bit[5:4]= WefCwock souwce fow PPWW.
                                       //          =0: XTWAIN( defauwt mode )
                                       //          =1: pcie
                                       //          =2: GENWK
    UCHAW  ucCWTC;                     // ATOM_CWTC1~6, indicate the CWTC contwowwew to
    UCHAW  ucDeepCowowWatio;           // HDMI panew bit depth: =0: 24bpp =1:30bpp, =2:36bpp
    UCHAW  ucWesewved[2];
    UWONG  uwWesewved;
}PIXEW_CWOCK_PAWAMETEWS_V7;

//ucMiscInfo
#define PIXEW_CWOCK_V7_MISC_FOWCE_PWOG_PPWW         0x01
#define PIXEW_CWOCK_V7_MISC_PWOG_PHYPWW             0x02
#define PIXEW_CWOCK_V7_MISC_YUV420_MODE             0x04
#define PIXEW_CWOCK_V7_MISC_DVI_DUAWWINK_EN         0x08
#define PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC             0x30
#define PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_XTAWIN      0x00
#define PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_PCIE        0x10
#define PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_GENWK       0x20

//ucDeepCowowWatio
#define PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_DIS          0x00      //00 - DCCG_DEEP_COWOW_DTO_DISABWE: Disabwe Deep Cowow DTO
#define PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_5_4          0x01      //01 - DCCG_DEEP_COWOW_DTO_5_4_WATIO: Set Deep Cowow DTO to 5:4
#define PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_3_2          0x02      //02 - DCCG_DEEP_COWOW_DTO_3_2_WATIO: Set Deep Cowow DTO to 3:2
#define PIXEW_CWOCK_V7_DEEPCOWOW_WATIO_2_1          0x03      //03 - DCCG_DEEP_COWOW_DTO_2_1_WATIO: Set Deep Cowow DTO to 2:1

// SetDCECwockTabwe input pawametew fow DCE11.1
typedef stwuct _SET_DCE_CWOCK_PAWAMETEWS_V1_1
{
  UWONG  uwDISPCwkFweq;       // tawget DISPCWK fwquency in unit of 10kHz, wetuwn weaw DISPCWK fwequency. when ucFwag[1]=1, in unit of 100Hz.
  UCHAW  ucFwag;              // bit0=1: DPWEFCWK bypass DFS bit0=0: DPWEFCWK not bypass DFS
  UCHAW  ucCwtc;              // use when enabwe DCCG pixew cwock ucFwag[1]=1
  UCHAW  ucPpwwId;            // use when enabwe DCCG pixew cwock ucFwag[1]=1
  UCHAW  ucDeepCowowWatio;    // use when enabwe DCCG pixew cwock ucFwag[1]=1
}SET_DCE_CWOCK_PAWAMETEWS_V1_1;


typedef stwuct _SET_DCE_CWOCK_PS_AWWOCATION_V1_1
{
  SET_DCE_CWOCK_PAWAMETEWS_V1_1 asPawam;
  UWONG uwWesewved[2];
}SET_DCE_CWOCK_PS_AWWOCATION_V1_1;

//SET_DCE_CWOCK_PAWAMETEWS_V1_1.ucFwag
#define SET_DCE_CWOCK_FWAG_GEN_DPWEFCWK            0x01
#define SET_DCE_CWOCK_FWAG_DPWEFCWK_BYPASS         0x01
#define SET_DCE_CWOCK_FWAG_ENABWE_PIXCWK           0x02

// SetDCECwockTabwe input pawametew fow DCE11.2( POWAWIS10 and POWAWIS11 ) and above
typedef stwuct _SET_DCE_CWOCK_PAWAMETEWS_V2_1
{
  UWONG  uwDCECwkFweq;                               // tawget DCE fwequency in unit of 10KHZ, wetuwn weaw DISPCWK/DPWEFCWK fwequency.
  UCHAW  ucDCECwkType;                               // =0: DISPCWK  =1: DPWEFCWK  =2: PIXCWK
  UCHAW  ucDCECwkSwc;                                // ATOM_PWW0 ow ATOM_GCK_DFS ow ATOM_FCH_CWK ow ATOM_COMBOPHY_PWWx
  UCHAW  ucDCECwkFwag;                               // Bit [1:0] = PPWW wef cwock souwce ( when ucDCECwkSwc= ATOM_PPWW0 )
  UCHAW  ucCWTC;                                     // ucDisp Pipe Id, ATOM_CWTC0/1/2/..., use onwy when ucDCECwkType = PIXCWK
}SET_DCE_CWOCK_PAWAMETEWS_V2_1;

//ucDCECwkType
#define DCE_CWOCK_TYPE_DISPCWK                        0
#define DCE_CWOCK_TYPE_DPWEFCWK                       1
#define DCE_CWOCK_TYPE_PIXEWCWK                       2        // used by VBIOS intewnawwy, cawwed by SetPixewCwockTabwe

//ucDCECwkFwag when ucDCECwkType == DPWEFCWK
#define DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_MASK            0x03
#define DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENEWICA        0x00
#define DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENWK           0x01
#define DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_PCIE            0x02
#define DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_XTAWIN          0x03

//ucDCECwkFwag when ucDCECwkType == PIXCWK
#define DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_MASK      0x03
#define DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_DIS       0x00      //00 - DCCG_DEEP_COWOW_DTO_DISABWE: Disabwe Deep Cowow DTO
#define DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_5_4       0x01      //01 - DCCG_DEEP_COWOW_DTO_5_4_WATIO: Set Deep Cowow DTO to 5:4
#define DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_3_2       0x02      //02 - DCCG_DEEP_COWOW_DTO_3_2_WATIO: Set Deep Cowow DTO to 3:2
#define DCE_CWOCK_FWAG_PCWK_DEEPCOWOW_WATIO_2_1       0x03      //03 - DCCG_DEEP_COWOW_DTO_2_1_WATIO: Set Deep Cowow DTO to 2:1
#define DCE_CWOCK_FWAG_PIXCWK_YUV420_MODE             0x04

typedef stwuct _SET_DCE_CWOCK_PS_AWWOCATION_V2_1
{
  SET_DCE_CWOCK_PAWAMETEWS_V2_1 asPawam;
  UWONG uwWesewved[2];
}SET_DCE_CWOCK_PS_AWWOCATION_V2_1;



/****************************************************************************/
// Stwuctuwes used by AdjustDispwayPwwTabwe
/****************************************************************************/
typedef stwuct _ADJUST_DISPWAY_PWW_PAWAMETEWS
{
   USHOWT usPixewCwock;
   UCHAW ucTwansmittewID;
   UCHAW ucEncodeMode;
   union
   {
      UCHAW ucDVOConfig;                           //if DVO, need passing wink wate and output 12bitwow ow 24bit
      UCHAW ucConfig;                                 //if none DVO, not defined yet
   };
   UCHAW ucWesewved[3];
}ADJUST_DISPWAY_PWW_PAWAMETEWS;

#define ADJUST_DISPWAY_CONFIG_SS_ENABWE            0x10
#define ADJUST_DISPWAY_PWW_PS_AWWOCATION              ADJUST_DISPWAY_PWW_PAWAMETEWS

typedef stwuct _ADJUST_DISPWAY_PWW_INPUT_PAWAMETEWS_V3
{
   USHOWT usPixewCwock;                    // tawget pixew cwock
   UCHAW ucTwansmittewID;                  // GPU twansmittew id defined in objectid.h
   UCHAW ucEncodeMode;                     // encodew mode: CWT, WVDS, DP, TMDS ow HDMI
  UCHAW ucDispPwwConfig;                 // dispway pww configuwe pawametew defined as fowwowing DISPPWW_CONFIG_XXXX
  UCHAW ucExtTwansmittewID;               // extewnaw encodew id.
   UCHAW ucWesewved[2];
}ADJUST_DISPWAY_PWW_INPUT_PAWAMETEWS_V3;

// usDispPwwConfig v1.2 fow WoadWunnew
#define DISPPWW_CONFIG_DVO_WATE_SEW                0x0001     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_DDW_SPEED               0x0000     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_SDW_SPEED               0x0001     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_OUTPUT_SEW              0x000c     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_WOW12BIT                0x0000     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_UPPEW12BIT              0x0004     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_DVO_24BIT                   0x0008     // need onwy when ucTwansmittewID = DVO
#define DISPPWW_CONFIG_SS_ENABWE                   0x0010     // Onwy used when ucEncodewMode = DP ow WVDS
#define DISPPWW_CONFIG_COHEWENT_MODE               0x0020     // Onwy used when ucEncodewMode = TMDS ow HDMI
#define DISPPWW_CONFIG_DUAW_WINK                   0x0040     // Onwy used when ucEncodewMode = TMDS ow WVDS


typedef stwuct _ADJUST_DISPWAY_PWW_OUTPUT_PAWAMETEWS_V3
{
  UWONG uwDispPwwFweq;                 // wetuwn dispway PPWW fweq which is used to genewate the pixcwock, and wewated idcwk, symcwk etc
  UCHAW ucWefDiv;                      // if it is none-zewo, it is used to be cawcuwated the othew ppww pawametew fb_dividew and post_div ( if it is not given )
  UCHAW ucPostDiv;                     // if it is none-zewo, it is used to be cawcuwated the othew ppww pawametew fb_dividew
  UCHAW ucWesewved[2];
}ADJUST_DISPWAY_PWW_OUTPUT_PAWAMETEWS_V3;

typedef stwuct _ADJUST_DISPWAY_PWW_PS_AWWOCATION_V3
{
  union
  {
    ADJUST_DISPWAY_PWW_INPUT_PAWAMETEWS_V3  sInput;
    ADJUST_DISPWAY_PWW_OUTPUT_PAWAMETEWS_V3 sOutput;
  };
} ADJUST_DISPWAY_PWW_PS_AWWOCATION_V3;

/****************************************************************************/
// Stwuctuwes used by EnabweYUVTabwe
/****************************************************************************/
typedef stwuct _ENABWE_YUV_PAWAMETEWS
{
  UCHAW ucEnabwe;                     // ATOM_ENABWE:Enabwe YUV ow ATOM_DISABWE:Disabwe YUV (WGB)
  UCHAW ucCWTC;                       // Which CWTC needs this YUV ow WGB fowmat
  UCHAW ucPadding[2];
}ENABWE_YUV_PAWAMETEWS;
#define ENABWE_YUV_PS_AWWOCATION ENABWE_YUV_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by GetMemowyCwockTabwe
/****************************************************************************/
typedef stwuct _GET_MEMOWY_CWOCK_PAWAMETEWS
{
  UWONG uwWetuwnMemowyCwock;          // cuwwent memowy speed in 10KHz unit
} GET_MEMOWY_CWOCK_PAWAMETEWS;
#define GET_MEMOWY_CWOCK_PS_AWWOCATION  GET_MEMOWY_CWOCK_PAWAMETEWS

/****************************************************************************/
// Stwuctuwes used by GetEngineCwockTabwe
/****************************************************************************/
typedef stwuct _GET_ENGINE_CWOCK_PAWAMETEWS
{
  UWONG uwWetuwnEngineCwock;          // cuwwent engine speed in 10KHz unit
} GET_ENGINE_CWOCK_PAWAMETEWS;
#define GET_ENGINE_CWOCK_PS_AWWOCATION  GET_ENGINE_CWOCK_PAWAMETEWS

/****************************************************************************/
// Fowwowing Stwuctuwes and constant may be obsowete
/****************************************************************************/
//Maxium 8 bytes,the data wead in wiww be pwaced in the pawametew space.
//Wead opewaion successefuw when the pawamtew space is non-zewo, othewwise wead opewation faiwed
typedef stwuct _WEAD_EDID_FWOM_HW_I2C_DATA_PAWAMETEWS
{
  USHOWT    usPwescawe;         //Watio between Engine cwock and I2C cwock
  USHOWT    usVWAMAddwess;      //Adwess in Fwame Buffew whewe to pace waw EDID
  USHOWT    usStatus;           //When use output: wowew byte EDID checksum, high byte hawdwawe status
                                //WHen use input:  wowew byte as 'byte to wead':cuwwentwy wimited to 128byte ow 1byte
  UCHAW     ucSwaveAddw;        //Wead fwom which swave
  UCHAW     ucWineNumbew;       //Wead fwom which HW assisted wine
}WEAD_EDID_FWOM_HW_I2C_DATA_PAWAMETEWS;
#define WEAD_EDID_FWOM_HW_I2C_DATA_PS_AWWOCATION  WEAD_EDID_FWOM_HW_I2C_DATA_PAWAMETEWS


#define  ATOM_WWITE_I2C_FOWMAT_PSOFFSET_PSDATABYTE                  0
#define  ATOM_WWITE_I2C_FOWMAT_PSOFFSET_PSTWODATABYTES              1
#define  ATOM_WWITE_I2C_FOWMAT_PSCOUNTEW_PSOFFSET_IDDATABWOCK       2
#define  ATOM_WWITE_I2C_FOWMAT_PSCOUNTEW_IDOFFSET_PWUS_IDDATABWOCK  3
#define  ATOM_WWITE_I2C_FOWMAT_IDCOUNTEW_IDOFFSET_IDDATABWOCK       4

typedef stwuct _WWITE_ONE_BYTE_HW_I2C_DATA_PAWAMETEWS
{
  USHOWT    usPwescawe;         //Watio between Engine cwock and I2C cwock
  USHOWT    usByteOffset;       //Wwite to which byte
                                //Uppew powtion of usByteOffset is Fowmat of data
                                //1bytePS+offsetPS
                                //2bytesPS+offsetPS
                                //bwockID+offsetPS
                                //bwockID+offsetID
                                //bwockID+countewID+offsetID
  UCHAW     ucData;             //PS data1
  UCHAW     ucStatus;           //Status byte 1=success, 2=faiwuwe, Awso is used as PS data2
  UCHAW     ucSwaveAddw;        //Wwite to which swave
  UCHAW     ucWineNumbew;       //Wwite fwom which HW assisted wine
}WWITE_ONE_BYTE_HW_I2C_DATA_PAWAMETEWS;

#define WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION  WWITE_ONE_BYTE_HW_I2C_DATA_PAWAMETEWS

typedef stwuct _SET_UP_HW_I2C_DATA_PAWAMETEWS
{
  USHOWT    usPwescawe;         //Watio between Engine cwock and I2C cwock
  UCHAW     ucSwaveAddw;        //Wwite to which swave
  UCHAW     ucWineNumbew;       //Wwite fwom which HW assisted wine
}SET_UP_HW_I2C_DATA_PAWAMETEWS;

/**************************************************************************/
#define SPEED_FAN_CONTWOW_PS_AWWOCATION   WWITE_ONE_BYTE_HW_I2C_DATA_PAWAMETEWS


/****************************************************************************/
// Stwuctuwes used by PowewConnectowDetectionTabwe
/****************************************************************************/
typedef stwuct   _POWEW_CONNECTOW_DETECTION_PAWAMETEWS
{
  UCHAW   ucPowewConnectowStatus;      //Used fow wetuwn vawue 0: detected, 1:not detected
   UCHAW   ucPwwBehaviowId;
   USHOWT   usPwwBudget;                         //how much powew cuwwentwy boot to in unit of watt
}POWEW_CONNECTOW_DETECTION_PAWAMETEWS;

typedef stwuct POWEW_CONNECTOW_DETECTION_PS_AWWOCATION
{
  UCHAW   ucPowewConnectowStatus;      //Used fow wetuwn vawue 0: detected, 1:not detected
   UCHAW   ucWesewved;
   USHOWT   usPwwBudget;                         //how much powew cuwwentwy boot to in unit of watt
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION    sWesewved;
}POWEW_CONNECTOW_DETECTION_PS_AWWOCATION;


/****************************WVDS SS Command Tabwe Definitions**********************/

/****************************************************************************/
// Stwuctuwes used by EnabweSpweadSpectwumOnPPWWTabwe
/****************************************************************************/
typedef stwuct   _ENABWE_WVDS_SS_PAWAMETEWS
{
  USHOWT  usSpweadSpectwumPewcentage;
  UCHAW   ucSpweadSpectwumType;           //Bit1=0 Down Spwead,=1 Centew Spwead. Bit1=1 Ext. =0 Int. Othews:TBD
  UCHAW   ucSpweadSpectwumStepSize_Deway; //bits3:2 SS_STEP_SIZE; bit 6:4 SS_DEWAY
  UCHAW   ucEnabwe;                       //ATOM_ENABWE ow ATOM_DISABWE
  UCHAW   ucPadding[3];
}ENABWE_WVDS_SS_PAWAMETEWS;

//ucTabweFowmatWevision=1,ucTabweContentWevision=2
typedef stwuct   _ENABWE_WVDS_SS_PAWAMETEWS_V2
{
  USHOWT  usSpweadSpectwumPewcentage;
  UCHAW   ucSpweadSpectwumType;           //Bit1=0 Down Spwead,=1 Centew Spwead. Bit1=1 Ext. =0 Int. Othews:TBD
  UCHAW   ucSpweadSpectwumStep;           //
  UCHAW   ucEnabwe;                       //ATOM_ENABWE ow ATOM_DISABWE
  UCHAW   ucSpweadSpectwumDeway;
  UCHAW   ucSpweadSpectwumWange;
  UCHAW   ucPadding;
}ENABWE_WVDS_SS_PAWAMETEWS_V2;

//This new stwuctuwe is based on ENABWE_WVDS_SS_PAWAMETEWS but expands to SS on PPWW, so othew devices can use SS.
typedef stwuct   _ENABWE_SPWEAD_SPECTWUM_ON_PPWW
{
  USHOWT  usSpweadSpectwumPewcentage;
  UCHAW   ucSpweadSpectwumType;           // Bit1=0 Down Spwead,=1 Centew Spwead. Bit1=1 Ext. =0 Int. Othews:TBD
  UCHAW   ucSpweadSpectwumStep;           //
  UCHAW   ucEnabwe;                       // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW   ucSpweadSpectwumDeway;
  UCHAW   ucSpweadSpectwumWange;
  UCHAW   ucPpww;                                      // ATOM_PPWW1/ATOM_PPWW2
}ENABWE_SPWEAD_SPECTWUM_ON_PPWW;

 typedef stwuct _ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V2
{
  USHOWT  usSpweadSpectwumPewcentage;
  UCHAW   ucSpweadSpectwumType;           // Bit[0]: 0-Down Spwead,1-Centew Spwead.
                                        // Bit[1]: 1-Ext. 0-Int.
                                        // Bit[3:2]: =0 P1PWW =1 P2PWW =2 DCPWW
                                        // Bits[7:4] wesewved
  UCHAW   ucEnabwe;                       // ATOM_ENABWE ow ATOM_DISABWE
  USHOWT  usSpweadSpectwumAmount;         // Incwudes SS_AMOUNT_FBDIV[7:0] and SS_AMOUNT_NFWAC_SWIP[11:8]
  USHOWT  usSpweadSpectwumStep;           // SS_STEP_SIZE_DSFWAC
}ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V2;

#define ATOM_PPWW_SS_TYPE_V2_DOWN_SPWEAD      0x00
#define ATOM_PPWW_SS_TYPE_V2_CENTWE_SPWEAD    0x01
#define ATOM_PPWW_SS_TYPE_V2_EXT_SPWEAD       0x02
#define ATOM_PPWW_SS_TYPE_V2_PPWW_SEW_MASK    0x0c
#define ATOM_PPWW_SS_TYPE_V2_P1PWW            0x00
#define ATOM_PPWW_SS_TYPE_V2_P2PWW            0x04
#define ATOM_PPWW_SS_TYPE_V2_DCPWW            0x08
#define ATOM_PPWW_SS_AMOUNT_V2_FBDIV_MASK     0x00FF
#define ATOM_PPWW_SS_AMOUNT_V2_FBDIV_SHIFT    0
#define ATOM_PPWW_SS_AMOUNT_V2_NFWAC_MASK     0x0F00
#define ATOM_PPWW_SS_AMOUNT_V2_NFWAC_SHIFT    8

// Used by DCE5.0
 typedef stwuct _ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V3
{
  USHOWT  usSpweadSpectwumAmountFwac;   // SS_AMOUNT_DSFWAC New in DCE5.0
  UCHAW   ucSpweadSpectwumType;           // Bit[0]: 0-Down Spwead,1-Centew Spwead.
                                        // Bit[1]: 1-Ext. 0-Int.
                                        // Bit[3:2]: =0 P1PWW =1 P2PWW =2 DCPWW
                                        // Bits[7:4] wesewved
  UCHAW   ucEnabwe;                       // ATOM_ENABWE ow ATOM_DISABWE
  USHOWT  usSpweadSpectwumAmount;         // Incwudes SS_AMOUNT_FBDIV[7:0] and SS_AMOUNT_NFWAC_SWIP[11:8]
  USHOWT  usSpweadSpectwumStep;           // SS_STEP_SIZE_DSFWAC
}ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V3;


#define ATOM_PPWW_SS_TYPE_V3_DOWN_SPWEAD      0x00
#define ATOM_PPWW_SS_TYPE_V3_CENTWE_SPWEAD    0x01
#define ATOM_PPWW_SS_TYPE_V3_EXT_SPWEAD       0x02
#define ATOM_PPWW_SS_TYPE_V3_PPWW_SEW_MASK    0x0c
#define ATOM_PPWW_SS_TYPE_V3_P1PWW            0x00
#define ATOM_PPWW_SS_TYPE_V3_P2PWW            0x04
#define ATOM_PPWW_SS_TYPE_V3_DCPWW            0x08
#define ATOM_PPWW_SS_TYPE_V3_P0PWW            ATOM_PPWW_SS_TYPE_V3_DCPWW
#define ATOM_PPWW_SS_AMOUNT_V3_FBDIV_MASK     0x00FF
#define ATOM_PPWW_SS_AMOUNT_V3_FBDIV_SHIFT    0
#define ATOM_PPWW_SS_AMOUNT_V3_NFWAC_MASK     0x0F00
#define ATOM_PPWW_SS_AMOUNT_V3_NFWAC_SHIFT    8

#define ENABWE_SPWEAD_SPECTWUM_ON_PPWW_PS_AWWOCATION  ENABWE_SPWEAD_SPECTWUM_ON_PPWW

typedef stwuct _SET_PIXEW_CWOCK_PS_AWWOCATION
{
  PIXEW_CWOCK_PAWAMETEWS sPCWKInput;
  ENABWE_SPWEAD_SPECTWUM_ON_PPWW sWesewved;//Cawwew doesn't need to init this powtion
}SET_PIXEW_CWOCK_PS_AWWOCATION;



#define ENABWE_VGA_WENDEW_PS_AWWOCATION   SET_PIXEW_CWOCK_PS_AWWOCATION

/****************************************************************************/
// Stwuctuwes used by ###
/****************************************************************************/
typedef stwuct   _MEMOWY_TWAINING_PAWAMETEWS
{
  UWONG uwTawgetMemowyCwock;          //In 10Khz unit
}MEMOWY_TWAINING_PAWAMETEWS;
#define MEMOWY_TWAINING_PS_AWWOCATION MEMOWY_TWAINING_PAWAMETEWS


typedef stwuct   _MEMOWY_TWAINING_PAWAMETEWS_V1_2
{
  USHOWT usMemTwainingMode;
  USHOWT usWesewved;
}MEMOWY_TWAINING_PAWAMETEWS_V1_2;

//usMemTwainingMode
#define NOWMAW_MEMOWY_TWAINING_MODE       0
#define ENTEW_DWAM_SEWFWEFWESH_MODE       1
#define EXIT_DWAM_SEWFWESH_MODE           2

/****************************WVDS and othew encodew command tabwe definitions **********************/


/****************************************************************************/
// Stwuctuwes used by WVDSEncodewContwowTabwe   (Befowe DEC30)
//                    WVTMAEncodewContwowTabwe  (Befowe DEC30)
//                    TMDSAEncodewContwowTabwe  (Befowe DEC30)
/****************************************************************************/
typedef stwuct _WVDS_ENCODEW_CONTWOW_PAWAMETEWS
{
  USHOWT usPixewCwock;  // in 10KHz; fow bios convenient
  UCHAW  ucMisc;        // bit0=0: Enabwe singwe wink
                        //     =1: Enabwe duaw wink
                        // Bit1=0: 666WGB
                        //     =1: 888WGB
  UCHAW  ucAction;      // 0: tuwn off encodew
                        // 1: setup and tuwn on encodew
}WVDS_ENCODEW_CONTWOW_PAWAMETEWS;

#define WVDS_ENCODEW_CONTWOW_PS_AWWOCATION  WVDS_ENCODEW_CONTWOW_PAWAMETEWS

#define TMDS1_ENCODEW_CONTWOW_PAWAMETEWS    WVDS_ENCODEW_CONTWOW_PAWAMETEWS
#define TMDS1_ENCODEW_CONTWOW_PS_AWWOCATION TMDS1_ENCODEW_CONTWOW_PAWAMETEWS

#define TMDS2_ENCODEW_CONTWOW_PAWAMETEWS    TMDS1_ENCODEW_CONTWOW_PAWAMETEWS
#define TMDS2_ENCODEW_CONTWOW_PS_AWWOCATION TMDS2_ENCODEW_CONTWOW_PAWAMETEWS

//ucTabweFowmatWevision=1,ucTabweContentWevision=2
typedef stwuct _WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2
{
  USHOWT usPixewCwock;  // in 10KHz; fow bios convenient
  UCHAW  ucMisc;        // see PANEW_ENCODEW_MISC_xx defintions bewow
  UCHAW  ucAction;      // 0: tuwn off encodew
                        // 1: setup and tuwn on encodew
  UCHAW  ucTwuncate;    // bit0=0: Disabwe twuncate
                        //     =1: Enabwe twuncate
                        // bit4=0: 666WGB
                        //     =1: 888WGB
  UCHAW  ucSpatiaw;     // bit0=0: Disabwe spatiaw dithewing
                        //     =1: Enabwe spatiaw dithewing
                        // bit4=0: 666WGB
                        //     =1: 888WGB
  UCHAW  ucTempowaw;    // bit0=0: Disabwe tempowaw dithewing
                        //     =1: Enabwe tempowaw dithewing
                        // bit4=0: 666WGB
                        //     =1: 888WGB
                        // bit5=0: Gway wevew 2
                        //     =1: Gway wevew 4
  UCHAW  ucFWC;         // bit4=0: 25FWC_SEW pattewn E
                        //     =1: 25FWC_SEW pattewn F
                        // bit6:5=0: 50FWC_SEW pattewn A
                        //       =1: 50FWC_SEW pattewn B
                        //       =2: 50FWC_SEW pattewn C
                        //       =3: 50FWC_SEW pattewn D
                        // bit7=0: 75FWC_SEW pattewn E
                        //     =1: 75FWC_SEW pattewn F
}WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2;

#define WVDS_ENCODEW_CONTWOW_PS_AWWOCATION_V2  WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2

#define TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_V2    WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2
#define TMDS1_ENCODEW_CONTWOW_PS_AWWOCATION_V2 TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_V2

#define TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_V2    TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_V2
#define TMDS2_ENCODEW_CONTWOW_PS_AWWOCATION_V2 TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_V2


#define WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3     WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2
#define WVDS_ENCODEW_CONTWOW_PS_AWWOCATION_V3  WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3

#define TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_V3    WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3
#define TMDS1_ENCODEW_CONTWOW_PS_AWWOCATION_V3 TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_V3

#define TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_V3    WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3
#define TMDS2_ENCODEW_CONTWOW_PS_AWWOCATION_V3 TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_V3

/****************************************************************************/
// Stwuctuwes used by ###
/****************************************************************************/
typedef stwuct _ENABWE_EXTEWNAW_TMDS_ENCODEW_PAWAMETEWS
{
  UCHAW    ucEnabwe;            // Enabwe ow Disabwe Extewnaw TMDS encodew
  UCHAW    ucMisc;              // Bit0=0:Enabwe Singwe wink;=1:Enabwe Duaw wink;Bit1 {=0:666WGB, =1:888WGB}
  UCHAW    ucPadding[2];
}ENABWE_EXTEWNAW_TMDS_ENCODEW_PAWAMETEWS;

typedef stwuct _ENABWE_EXTEWNAW_TMDS_ENCODEW_PS_AWWOCATION
{
  ENABWE_EXTEWNAW_TMDS_ENCODEW_PAWAMETEWS    sXTmdsEncodew;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION   sWesewved;     //Cawwew doesn't need to init this powtion
}ENABWE_EXTEWNAW_TMDS_ENCODEW_PS_AWWOCATION;

#define ENABWE_EXTEWNAW_TMDS_ENCODEW_PAWAMETEWS_V2  WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V2
typedef stwuct _ENABWE_EXTEWNAW_TMDS_ENCODEW_PS_AWWOCATION_V2
{
  ENABWE_EXTEWNAW_TMDS_ENCODEW_PAWAMETEWS_V2    sXTmdsEncodew;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION      sWesewved;     //Cawwew doesn't need to init this powtion
}ENABWE_EXTEWNAW_TMDS_ENCODEW_PS_AWWOCATION_V2;

typedef stwuct _EXTEWNAW_ENCODEW_CONTWOW_PS_AWWOCATION
{
  DIG_ENCODEW_CONTWOW_PAWAMETEWS            sDigEncodew;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION sWesewved;
}EXTEWNAW_ENCODEW_CONTWOW_PS_AWWOCATION;

/****************************************************************************/
// Stwuctuwes used by DVOEncodewContwowTabwe
/****************************************************************************/
//ucTabweFowmatWevision=1,ucTabweContentWevision=3
//ucDVOConfig:
#define DVO_ENCODEW_CONFIG_WATE_SEW                     0x01
#define DVO_ENCODEW_CONFIG_DDW_SPEED                  0x00
#define DVO_ENCODEW_CONFIG_SDW_SPEED                  0x01
#define DVO_ENCODEW_CONFIG_OUTPUT_SEW                  0x0c
#define DVO_ENCODEW_CONFIG_WOW12BIT                     0x00
#define DVO_ENCODEW_CONFIG_UPPEW12BIT                  0x04
#define DVO_ENCODEW_CONFIG_24BIT                        0x08

typedef stwuct _DVO_ENCODEW_CONTWOW_PAWAMETEWS_V3
{
  USHOWT usPixewCwock;
  UCHAW  ucDVOConfig;
  UCHAW  ucAction;                                          //ATOM_ENABWE/ATOM_DISABWE/ATOM_HPD_INIT
  UCHAW  ucWeseved[4];
}DVO_ENCODEW_CONTWOW_PAWAMETEWS_V3;
#define DVO_ENCODEW_CONTWOW_PS_AWWOCATION_V3   DVO_ENCODEW_CONTWOW_PAWAMETEWS_V3

typedef stwuct _DVO_ENCODEW_CONTWOW_PAWAMETEWS_V1_4
{
  USHOWT usPixewCwock;
  UCHAW  ucDVOConfig;
  UCHAW  ucAction;                                          //ATOM_ENABWE/ATOM_DISABWE/ATOM_HPD_INIT
  UCHAW  ucBitPewCowow;                       //pwease wefew to definition of PANEW_xBIT_PEW_COWOW
  UCHAW  ucWeseved[3];
}DVO_ENCODEW_CONTWOW_PAWAMETEWS_V1_4;
#define DVO_ENCODEW_CONTWOW_PS_AWWOCATION_V1_4   DVO_ENCODEW_CONTWOW_PAWAMETEWS_V1_4


//ucTabweFowmatWevision=1
//ucTabweContentWevision=3 stwuctuwe is not changed but usMisc add bit 1 as anothew input fow
// bit1=0: non-cohewent mode
//     =1: cohewent mode

//==========================================================================================
//Onwy change is hewe next time when changing encodew pawametew definitions again!
#define WVDS_ENCODEW_CONTWOW_PAWAMETEWS_WAST     WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3
#define WVDS_ENCODEW_CONTWOW_PS_AWWOCATION_WAST  WVDS_ENCODEW_CONTWOW_PAWAMETEWS_WAST

#define TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_WAST    WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3
#define TMDS1_ENCODEW_CONTWOW_PS_AWWOCATION_WAST TMDS1_ENCODEW_CONTWOW_PAWAMETEWS_WAST

#define TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_WAST    WVDS_ENCODEW_CONTWOW_PAWAMETEWS_V3
#define TMDS2_ENCODEW_CONTWOW_PS_AWWOCATION_WAST TMDS2_ENCODEW_CONTWOW_PAWAMETEWS_WAST

#define DVO_ENCODEW_CONTWOW_PAWAMETEWS_WAST      DVO_ENCODEW_CONTWOW_PAWAMETEWS
#define DVO_ENCODEW_CONTWOW_PS_AWWOCATION_WAST   DVO_ENCODEW_CONTWOW_PS_AWWOCATION

//==========================================================================================
#define PANEW_ENCODEW_MISC_DUAW                0x01
#define PANEW_ENCODEW_MISC_COHEWENT            0x02
#define   PANEW_ENCODEW_MISC_TMDS_WINKB                0x04
#define   PANEW_ENCODEW_MISC_HDMI_TYPE                0x08

#define PANEW_ENCODEW_ACTION_DISABWE           ATOM_DISABWE
#define PANEW_ENCODEW_ACTION_ENABWE            ATOM_ENABWE
#define PANEW_ENCODEW_ACTION_COHEWENTSEQ       (ATOM_ENABWE+1)

#define PANEW_ENCODEW_TWUNCATE_EN              0x01
#define PANEW_ENCODEW_TWUNCATE_DEPTH           0x10
#define PANEW_ENCODEW_SPATIAW_DITHEW_EN        0x01
#define PANEW_ENCODEW_SPATIAW_DITHEW_DEPTH     0x10
#define PANEW_ENCODEW_TEMPOWAW_DITHEW_EN       0x01
#define PANEW_ENCODEW_TEMPOWAW_DITHEW_DEPTH    0x10
#define PANEW_ENCODEW_TEMPOWAW_WEVEW_4         0x20
#define PANEW_ENCODEW_25FWC_MASK               0x10
#define PANEW_ENCODEW_25FWC_E                  0x00
#define PANEW_ENCODEW_25FWC_F                  0x10
#define PANEW_ENCODEW_50FWC_MASK               0x60
#define PANEW_ENCODEW_50FWC_A                  0x00
#define PANEW_ENCODEW_50FWC_B                  0x20
#define PANEW_ENCODEW_50FWC_C                  0x40
#define PANEW_ENCODEW_50FWC_D                  0x60
#define PANEW_ENCODEW_75FWC_MASK               0x80
#define PANEW_ENCODEW_75FWC_E                  0x00
#define PANEW_ENCODEW_75FWC_F                  0x80

/****************************************************************************/
// Stwuctuwes used by SetVowtageTabwe
/****************************************************************************/
#define SET_VOWTAGE_TYPE_ASIC_VDDC             1
#define SET_VOWTAGE_TYPE_ASIC_MVDDC            2
#define SET_VOWTAGE_TYPE_ASIC_MVDDQ            3
#define SET_VOWTAGE_TYPE_ASIC_VDDCI            4
#define SET_VOWTAGE_INIT_MODE                  5
#define SET_VOWTAGE_GET_MAX_VOWTAGE            6               //Gets the Max. vowtage fow the sowdewed Asic

#define SET_ASIC_VOWTAGE_MODE_AWW_SOUWCE       0x1
#define SET_ASIC_VOWTAGE_MODE_SOUWCE_A         0x2
#define SET_ASIC_VOWTAGE_MODE_SOUWCE_B         0x4

#define   SET_ASIC_VOWTAGE_MODE_SET_VOWTAGE      0x0
#define   SET_ASIC_VOWTAGE_MODE_GET_GPIOVAW      0x1
#define   SET_ASIC_VOWTAGE_MODE_GET_GPIOMASK     0x2

typedef stwuct   _SET_VOWTAGE_PAWAMETEWS
{
  UCHAW    ucVowtageType;               // To teww which vowtage to set up, VDDC/MVDDC/MVDDQ
  UCHAW    ucVowtageMode;               // To set aww, to set souwce A ow souwce B ow ...
  UCHAW    ucVowtageIndex;              // An index to teww which vowtage wevew
  UCHAW    ucWesewved;
}SET_VOWTAGE_PAWAMETEWS;

typedef stwuct   _SET_VOWTAGE_PAWAMETEWS_V2
{
  UCHAW    ucVowtageType;               // To teww which vowtage to set up, VDDC/MVDDC/MVDDQ
  UCHAW    ucVowtageMode;               // Not used, maybe use fow state machine fow diffewen powew mode
  USHOWT   usVowtageWevew;              // weaw vowtage wevew
}SET_VOWTAGE_PAWAMETEWS_V2;

// used by both SetVowtageTabwe v1.3 and v1.4
typedef stwuct   _SET_VOWTAGE_PAWAMETEWS_V1_3
{
  UCHAW    ucVowtageType;               // To teww which vowtage to set up, VDDC/MVDDC/MVDDQ/VDDCI
  UCHAW    ucVowtageMode;               // Indicate action: Set vowtage wevew
  USHOWT   usVowtageWevew;              // weaw vowtage wevew in unit of mv ow Vowtage Phase (0, 1, 2, .. )
}SET_VOWTAGE_PAWAMETEWS_V1_3;

//ucVowtageType
#define VOWTAGE_TYPE_VDDC                    1
#define VOWTAGE_TYPE_MVDDC                   2
#define VOWTAGE_TYPE_MVDDQ                   3
#define VOWTAGE_TYPE_VDDCI                   4
#define VOWTAGE_TYPE_VDDGFX                  5
#define VOWTAGE_TYPE_PCC                     6
#define VOWTAGE_TYPE_MVPP                    7
#define VOWTAGE_TYPE_WEDDPM                  8
#define VOWTAGE_TYPE_PCC_MVDD                9
#define VOWTAGE_TYPE_PCIE_VDDC               10
#define VOWTAGE_TYPE_PCIE_VDDW               11

#define VOWTAGE_TYPE_GENEWIC_I2C_1           0x11
#define VOWTAGE_TYPE_GENEWIC_I2C_2           0x12
#define VOWTAGE_TYPE_GENEWIC_I2C_3           0x13
#define VOWTAGE_TYPE_GENEWIC_I2C_4           0x14
#define VOWTAGE_TYPE_GENEWIC_I2C_5           0x15
#define VOWTAGE_TYPE_GENEWIC_I2C_6           0x16
#define VOWTAGE_TYPE_GENEWIC_I2C_7           0x17
#define VOWTAGE_TYPE_GENEWIC_I2C_8           0x18
#define VOWTAGE_TYPE_GENEWIC_I2C_9           0x19
#define VOWTAGE_TYPE_GENEWIC_I2C_10          0x1A

//SET_VOWTAGE_PAWAMETEWS_V3.ucVowtageMode
#define ATOM_SET_VOWTAGE                     0        //Set vowtage Wevew
#define ATOM_INIT_VOWTAGE_WEGUWATOW          3        //Init Weguwatow
#define ATOM_SET_VOWTAGE_PHASE               4        //Set Vweguwatow Phase, onwy fow SVID/PVID weguwatow
#define ATOM_GET_MAX_VOWTAGE                 6        //Get Max Vowtage, not used fwom SetVowtageTabwe v1.3
#define ATOM_GET_VOWTAGE_WEVEW               6        //Get Vowtage wevew fwom vituaw vowtage ID, not used fow SetVowtage v1.4
#define ATOM_GET_WEAKAGE_ID                  8        //Get Weakage Vowtage Id ( stawting fwom SMU7x IP ), SetVowtage v1.4

// define vituaw vowtage id in usVowtageWevew
#define ATOM_VIWTUAW_VOWTAGE_ID0             0xff01
#define ATOM_VIWTUAW_VOWTAGE_ID1             0xff02
#define ATOM_VIWTUAW_VOWTAGE_ID2             0xff03
#define ATOM_VIWTUAW_VOWTAGE_ID3             0xff04
#define ATOM_VIWTUAW_VOWTAGE_ID4             0xff05
#define ATOM_VIWTUAW_VOWTAGE_ID5             0xff06
#define ATOM_VIWTUAW_VOWTAGE_ID6             0xff07
#define ATOM_VIWTUAW_VOWTAGE_ID7             0xff08

typedef stwuct _SET_VOWTAGE_PS_AWWOCATION
{
  SET_VOWTAGE_PAWAMETEWS sASICSetVowtage;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION sWesewved;
}SET_VOWTAGE_PS_AWWOCATION;

// New Added fwom SI fow GetVowtageInfoTabwe, input pawametew stwuctuwe
typedef stwuct  _GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_1
{
  UCHAW    ucVowtageType;               // Input: To teww which vowtage to set up, VDDC/MVDDC/MVDDQ/VDDCI
  UCHAW    ucVowtageMode;               // Input: Indicate action: Get vowtage info
  USHOWT   usVowtageWevew;              // Input: weaw vowtage wevew in unit of mv ow Vowtage Phase (0, 1, 2, .. ) ow Weakage Id
  UWONG    uwWesewved;
}GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_1;

// New Added fwom SI fow GetVowtageInfoTabwe, output pawametew stwuctuwe when ucVotwageMode == ATOM_GET_VOWTAGE_VID
typedef stwuct  _GET_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_1
{
  UWONG    uwVotwageGpioState;
  UWONG    uwVowtageGPioMask;
}GET_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_1;

// New Added fwom SI fow GetVowtageInfoTabwe, output pawametew stwuctuwe when ucVotwageMode == ATOM_GET_VOWTAGE_STATEx_WEAKAGE_VID
typedef stwuct  _GET_WEAKAGE_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_1
{
  USHOWT   usVowtageWevew;
  USHOWT   usVowtageId;                                  // Vowtage Id pwogwammed in Vowtage Weguwatow
  UWONG    uwWeseved;
}GET_WEAKAGE_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_1;

// GetVowtageInfo v1.1 ucVowtageMode
#define ATOM_GET_VOWTAGE_VID                0x00
#define ATOM_GET_VOTWAGE_INIT_SEQ           0x03
#define ATOM_GET_VOWTTAGE_PHASE_PHASE_VID   0x04
#define ATOM_GET_VOWTAGE_SVID2              0x07        //Get SVI2 Weguwatow Info

// fow SI, this state map to 0xff02 vowtage state in Powew Pway tabwe, which is powew boost state
#define   ATOM_GET_VOWTAGE_STATE0_WEAKAGE_VID 0x10
// fow SI, this state map to 0xff01 vowtage state in Powew Pway tabwe, which is pewfowmance state
#define   ATOM_GET_VOWTAGE_STATE1_WEAKAGE_VID 0x11

#define   ATOM_GET_VOWTAGE_STATE2_WEAKAGE_VID 0x12
#define   ATOM_GET_VOWTAGE_STATE3_WEAKAGE_VID 0x13


// New Added fwom CI Hawaii fow GetVowtageInfoTabwe, input pawametew stwuctuwe
typedef stwuct  _GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_2
{
  UCHAW    ucVowtageType;               // Input: To teww which vowtage to set up, VDDC/MVDDC/MVDDQ/VDDCI
  UCHAW    ucVowtageMode;               // Input: Indicate action: Get vowtage info
  USHOWT   usVowtageWevew;              // Input: weaw vowtage wevew in unit of mv ow Vowtage Phase (0, 1, 2, .. ) ow Weakage Id
  UWONG    uwSCWKFweq;                  // Input: when ucVowtageMode= ATOM_GET_VOWTAGE_EVV_VOWTAGE, DPM state SCWK fwequency, Define in PPTabwe SCWK/Vowtage dependence tabwe
}GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_2;

// New in GetVowtageInfo v1.2 ucVowtageMode
#define ATOM_GET_VOWTAGE_EVV_VOWTAGE        0x09

// New Added fwom CI Hawaii fow EVV featuwe
typedef stwuct  _GET_EVV_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_2
{
  USHOWT   usVowtageWevew;                               // weaw vowtage wevew in unit of mv
  USHOWT   usVowtageId;                                  // Vowtage Id pwogwammed in Vowtage Weguwatow
  USHOWT   usTDP_Cuwwent;                                // TDP_Cuwwent in unit of  0.01A
  USHOWT   usTDP_Powew;                                  // TDP_Cuwwent in unit  of 0.1W
}GET_EVV_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_2;


// New Added fwom CI Hawaii fow GetVowtageInfoTabwe, input pawametew stwuctuwe
typedef stwuct  _GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_3
{
  UCHAW    ucVowtageType;               // Input: To teww which vowtage to set up, VDDC/MVDDC/MVDDQ/VDDCI
  UCHAW    ucVowtageMode;               // Input: Indicate action: Get vowtage info
  USHOWT   usVowtageWevew;              // Input: weaw vowtage wevew in unit of mv ow Vowtage Phase (0, 1, 2, .. ) ow Weakage Id
  UWONG    uwSCWKFweq;                  // Input: when ucVowtageMode= ATOM_GET_VOWTAGE_EVV_VOWTAGE, DPM state SCWK fwequency, Define in PPTabwe SCWK/Vowtage dependence tabwe
  UWONG    uwWesewved[3];
}GET_VOWTAGE_INFO_INPUT_PAWAMETEW_V1_3;

// New Added fwom CI Hawaii fow EVV featuwe
typedef stwuct  _GET_EVV_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_3
{
  UWONG    uwVowtageWevew;                               // weaw vowtage wevew in unit of 0.01mv
  UWONG    uwWesewved[4];
}GET_EVV_VOWTAGE_INFO_OUTPUT_PAWAMETEW_V1_3;


/****************************************************************************/
// Stwuctuwes used by GetSMUCwockInfo
/****************************************************************************/
typedef stwuct  _GET_SMU_CWOCK_INFO_INPUT_PAWAMETEW_V2_1
{
  UWONG uwDfsPwwOutputFweq:24;
  UWONG ucDfsDividew:8;
}GET_SMU_CWOCK_INFO_INPUT_PAWAMETEW_V2_1;

typedef stwuct  _GET_SMU_CWOCK_INFO_OUTPUT_PAWAMETEW_V2_1
{
  UWONG uwDfsOutputFweq;
}GET_SMU_CWOCK_INFO_OUTPUT_PAWAMETEW_V2_1;

/****************************************************************************/
// Stwuctuwes used by TVEncodewContwowTabwe
/****************************************************************************/
typedef stwuct _TV_ENCODEW_CONTWOW_PAWAMETEWS
{
  USHOWT usPixewCwock;                // in 10KHz; fow bios convenient
  UCHAW  ucTvStandawd;                // See definition "ATOM_TV_NTSC ..."
  UCHAW  ucAction;                    // 0: tuwn off encodew
                                      // 1: setup and tuwn on encodew
}TV_ENCODEW_CONTWOW_PAWAMETEWS;

typedef stwuct _TV_ENCODEW_CONTWOW_PS_AWWOCATION
{
  TV_ENCODEW_CONTWOW_PAWAMETEWS sTVEncodew;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION    sWesewved; // Don't set this one
}TV_ENCODEW_CONTWOW_PS_AWWOCATION;

//==============================Data Tabwe Powtion====================================


/****************************************************************************/
// Stwuctuwe used in Data.mtb
/****************************************************************************/
typedef stwuct _ATOM_MASTEW_WIST_OF_DATA_TABWES
{
  USHOWT        UtiwityPipeWine;          // Offest fow the utiwity to get pawsew info,Don't change this position!
  USHOWT        MuwtimediaCapabiwityInfo; // Onwy used by MM Wib,watest vewsion 1.1, not configuabwe fwom Bios, need to incwude the tabwe to buiwd Bios
  USHOWT        MuwtimediaConfigInfo;     // Onwy used by MM Wib,watest vewsion 2.1, not configuabwe fwom Bios, need to incwude the tabwe to buiwd Bios
  USHOWT        StandawdVESA_Timing;      // Onwy used by Bios
  USHOWT        FiwmwaweInfo;             // Shawed by vawious SW components,watest vewsion 1.4
  USHOWT        PawetteData;              // Onwy used by BIOS
  USHOWT        WCD_Info;                 // Shawed by vawious SW components,watest vewsion 1.3, was cawwed WVDS_Info
  USHOWT        DIGTwansmittewInfo;       // Intewnaw used by VBIOS onwy vewsion 3.1
  USHOWT        SMU_Info;                 // Shawed by vawious SW components,watest vewsion 1.1
  USHOWT        SuppowtedDevicesInfo;     // Wiww be obsowete fwom W600
  USHOWT        GPIO_I2C_Info;            // Shawed by vawious SW components,watest vewsion 1.2 wiww be used fwom W600
  USHOWT        VWAM_UsageByFiwmwawe;     // Shawed by vawious SW components,watest vewsion 1.3 wiww be used fwom W600
  USHOWT        GPIO_Pin_WUT;             // Shawed by vawious SW components,watest vewsion 1.1
  USHOWT        VESA_ToIntewnawModeWUT;   // Onwy used by Bios
  USHOWT        GFX_Info;                 // Shawed by vawious SW components,watest vewsion 2.1 wiww be used fwom W600
  USHOWT        PowewPwayInfo;            // Shawed by vawious SW components,watest vewsion 2.1,new design fwom W600
  USHOWT        GPUViwtuawizationInfo;    // Wiww be obsowete fwom W600
  USHOWT        SaveWestoweInfo;          // Onwy used by Bios
  USHOWT        PPWW_SS_Info;             // Shawed by vawious SW components,watest vewsion 1.2, used to caww SS_Info, change to new name because of int ASIC SS info
  USHOWT        OemInfo;                  // Defined and used by extewnaw SW, shouwd be obsowete soon
  USHOWT        XTMDS_Info;               // Wiww be obsowete fwom W600
  USHOWT        McwkSS_Info;              // Shawed by vawious SW components,watest vewsion 1.1, onwy enabwed when ext SS chip is used
  USHOWT        Object_Headew;            // Shawed by vawious SW components,watest vewsion 1.1
  USHOWT        IndiwectIOAccess;         // Onwy used by Bios,this tabwe position can't change at aww!!
  USHOWT        MC_InitPawametew;         // Onwy used by command tabwe
  USHOWT        ASIC_VDDC_Info;           // Wiww be obsowete fwom W600
  USHOWT        ASIC_IntewnawSS_Info;     // New tabew name fwom W600, used to be cawwed "ASIC_MVDDC_Info"
  USHOWT        TV_VideoMode;             // Onwy used by command tabwe
  USHOWT        VWAM_Info;                // Onwy used by command tabwe, watest vewsion 1.3
  USHOWT        MemowyTwainingInfo;       // Used fow VBIOS and Diag utiwity fow memowy twaining puwpose since W600. the new tabwe wev stawt fwom 2.1
  USHOWT        IntegwatedSystemInfo;     // Shawed by vawious SW components
  USHOWT        ASIC_PwofiwingInfo;       // New tabwe name fwom W600, used to be cawwed "ASIC_VDDCI_Info" fow pwe-W600
  USHOWT        VowtageObjectInfo;        // Shawed by vawious SW components, watest vewsion 1.1
  USHOWT        PowewSouwceInfo;          // Shawed by vawious SW components, watest vewsoin 1.1
  USHOWT        SewviceInfo;
}ATOM_MASTEW_WIST_OF_DATA_TABWES;

typedef stwuct _ATOM_MASTEW_DATA_TABWE
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_MASTEW_WIST_OF_DATA_TABWES   WistOfDataTabwes;
}ATOM_MASTEW_DATA_TABWE;

// Fow backwawd compatibwe
#define WVDS_Info                WCD_Info
#define DAC_Info                 PawetteData
#define TMDS_Info                DIGTwansmittewInfo
#define CompassionateData        GPUViwtuawizationInfo
#define AnawogTV_Info            SMU_Info
#define ComponentVideoInfo       GFX_Info

/****************************************************************************/
// Stwuctuwe used in MuwtimediaCapabiwityInfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_MUWTIMEDIA_CAPABIWITY_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UWONG                    uwSignatuwe;      // HW info tabwe signatuwe stwing "$ATI"
  UCHAW                    ucI2C_Type;       // I2C type (nowmaw GP_IO, ImpactTV GP_IO, Dedicated I2C pin, etc)
  UCHAW                    ucTV_OutInfo;     // Type of TV out suppowted (3:0) and video out cwystaw fwequency (6:4) and TV data powt (7)
  UCHAW                    ucVideoPowtInfo;  // Pwovides the video powt capabiwities
  UCHAW                    ucHostPowtInfo;   // Pwovides host powt configuwation infowmation
}ATOM_MUWTIMEDIA_CAPABIWITY_INFO;


/****************************************************************************/
// Stwuctuwe used in MuwtimediaConfigInfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_MUWTIMEDIA_CONFIG_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UWONG                    uwSignatuwe;      // MM info tabwe signatuwe sting "$MMT"
  UCHAW                    ucTunewInfo;      // Type of tunew instawwed on the adaptew (4:0) and video input fow tunew (7:5)
  UCHAW                    ucAudioChipInfo;  // Wist the audio chip type (3:0) pwoduct type (4) and OEM wevision (7:5)
  UCHAW                    ucPwoductID;      // Defines as OEM ID ow ATI boawd ID dependent on pwoduct type setting
  UCHAW                    ucMiscInfo1;      // Tunew vowtage (1:0) HW tewetext suppowt (3:2) FM audio decodew (5:4) wesewved (6) audio scwambwing (7)
  UCHAW                    ucMiscInfo2;      // I2S input config (0) I2S output config (1) I2S Audio Chip (4:2) SPDIF Output Config (5) wesewved (7:6)
  UCHAW                    ucMiscInfo3;      // Video Decodew Type (3:0) Video In Standawd/Cwystaw (7:4)
  UCHAW                    ucMiscInfo4;      // Video Decodew Host Config (2:0) wesewved (7:3)
  UCHAW                    ucVideoInput0Info;// Video Input 0 Type (1:0) F/B setting (2) physicaw connectow ID (5:3) wesewved (7:6)
  UCHAW                    ucVideoInput1Info;// Video Input 1 Type (1:0) F/B setting (2) physicaw connectow ID (5:3) wesewved (7:6)
  UCHAW                    ucVideoInput2Info;// Video Input 2 Type (1:0) F/B setting (2) physicaw connectow ID (5:3) wesewved (7:6)
  UCHAW                    ucVideoInput3Info;// Video Input 3 Type (1:0) F/B setting (2) physicaw connectow ID (5:3) wesewved (7:6)
  UCHAW                    ucVideoInput4Info;// Video Input 4 Type (1:0) F/B setting (2) physicaw connectow ID (5:3) wesewved (7:6)
}ATOM_MUWTIMEDIA_CONFIG_INFO;


/****************************************************************************/
// Stwuctuwes used in FiwmwaweInfoTabwe
/****************************************************************************/

// usBIOSCapabiwity Defintion:
// Bit 0 = 0: Bios image is not Posted, =1:Bios image is Posted;
// Bit 1 = 0: Duaw CWTC is not suppowted, =1: Duaw CWTC is suppowted;
// Bit 2 = 0: Extended Desktop is not suppowted, =1: Extended Desktop is suppowted;
// Othews: Wesewved
#define ATOM_BIOS_INFO_ATOM_FIWMWAWE_POSTED         0x0001
#define ATOM_BIOS_INFO_DUAW_CWTC_SUPPOWT            0x0002
#define ATOM_BIOS_INFO_EXTENDED_DESKTOP_SUPPOWT     0x0004
#define ATOM_BIOS_INFO_MEMOWY_CWOCK_SS_SUPPOWT      0x0008      // (vawid fwom v1.1 ~v1.4):=1: memcwk SS enabwe, =0 memcwk SS disabwe.
#define ATOM_BIOS_INFO_ENGINE_CWOCK_SS_SUPPOWT      0x0010      // (vawid fwom v1.1 ~v1.4):=1: engcwk SS enabwe, =0 engcwk SS disabwe.
#define ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU         0x0020
#define ATOM_BIOS_INFO_WMI_SUPPOWT                  0x0040
#define ATOM_BIOS_INFO_PPMODE_ASSIGNGED_BY_SYSTEM   0x0080
#define ATOM_BIOS_INFO_HYPEWMEMOWY_SUPPOWT          0x0100
#define ATOM_BIOS_INFO_HYPEWMEMOWY_SIZE_MASK        0x1E00
#define ATOM_BIOS_INFO_VPOST_WITHOUT_FIWST_MODE_SET 0x2000
#define ATOM_BIOS_INFO_BIOS_SCWATCH6_SCW2_WEDEFINE  0x4000
#define ATOM_BIOS_INFO_MEMOWY_CWOCK_EXT_SS_SUPPOWT  0x0008      // (vawid fwom v2.1 ): =1: memcwk ss enabwe with extewnaw ss chip
#define ATOM_BIOS_INFO_ENGINE_CWOCK_EXT_SS_SUPPOWT  0x0010      // (vawid fwom v2.1 ): =1: engcwk ss enabwe with extewnaw ss chip


#ifndef _H2INC

//Pwease don't add ow expand this bitfiewd stwuctuwe bewow, this one wiww wetiwe soon.!
typedef stwuct _ATOM_FIWMWAWE_CAPABIWITY
{
#if ATOM_BIG_ENDIAN
  USHOWT Wesewved:1;
  USHOWT SCW2Wedefined:1;
  USHOWT PostWithoutModeSet:1;
  USHOWT HypewMemowy_Size:4;
  USHOWT HypewMemowy_Suppowt:1;
  USHOWT PPMode_Assigned:1;
  USHOWT WMI_SUPPOWT:1;
  USHOWT GPUContwowsBW:1;
  USHOWT EngineCwockSS_Suppowt:1;
  USHOWT MemowyCwockSS_Suppowt:1;
  USHOWT ExtendedDesktopSuppowt:1;
  USHOWT DuawCWTC_Suppowt:1;
  USHOWT FiwmwawePosted:1;
#ewse
  USHOWT FiwmwawePosted:1;
  USHOWT DuawCWTC_Suppowt:1;
  USHOWT ExtendedDesktopSuppowt:1;
  USHOWT MemowyCwockSS_Suppowt:1;
  USHOWT EngineCwockSS_Suppowt:1;
  USHOWT GPUContwowsBW:1;
  USHOWT WMI_SUPPOWT:1;
  USHOWT PPMode_Assigned:1;
  USHOWT HypewMemowy_Suppowt:1;
  USHOWT HypewMemowy_Size:4;
  USHOWT PostWithoutModeSet:1;
  USHOWT SCW2Wedefined:1;
  USHOWT Wesewved:1;
#endif
}ATOM_FIWMWAWE_CAPABIWITY;

typedef union _ATOM_FIWMWAWE_CAPABIWITY_ACCESS
{
  ATOM_FIWMWAWE_CAPABIWITY sbfAccess;
  USHOWT                   susAccess;
}ATOM_FIWMWAWE_CAPABIWITY_ACCESS;

#ewse

typedef union _ATOM_FIWMWAWE_CAPABIWITY_ACCESS
{
  USHOWT                   susAccess;
}ATOM_FIWMWAWE_CAPABIWITY_ACCESS;

#endif

typedef stwuct _ATOM_FIWMWAWE_INFO
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwDwivewTawgetEngineCwock;  //In 10Khz unit
  UWONG                           uwDwivewTawgetMemowyCwock;  //In 10Khz unit
  UWONG                           uwMaxEngineCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxMemowyCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwASICMaxEngineCwock;       //In 10Khz unit
  UWONG                           uwASICMaxMemowyCwock;       //In 10Khz unit
  UCHAW                           ucASICMaxTempewatuwe;
  UCHAW                           ucPadding[3];               //Don't use them
  UWONG                           auwWesewvedFowBIOS[3];      //Don't use them
  USHOWT                          usMinEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMaxPixewCwock;            //In 10Khz unit, Max.  Pcwk
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMinPixewCwockPWW_Output;  //In 10Khz unit, the definitions above can't change!!!
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usWefewenceCwock;           //In 10Khz unit
  USHOWT                          usPM_WTS_Wocation;          //WTS PM4 stawting wocation in WOM in 1Kb unit
  UCHAW                           ucPM_WTS_StweamSize;        //WTS PM4 packets in Kb unit
  UCHAW                           ucDesign_ID;                //Indicate what is the boawd design
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
}ATOM_FIWMWAWE_INFO;

typedef stwuct _ATOM_FIWMWAWE_INFO_V1_2
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwDwivewTawgetEngineCwock;  //In 10Khz unit
  UWONG                           uwDwivewTawgetMemowyCwock;  //In 10Khz unit
  UWONG                           uwMaxEngineCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxMemowyCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwASICMaxEngineCwock;       //In 10Khz unit
  UWONG                           uwASICMaxMemowyCwock;       //In 10Khz unit
  UCHAW                           ucASICMaxTempewatuwe;
  UCHAW                           ucMinAwwowedBW_Wevew;
  UCHAW                           ucPadding[2];               //Don't use them
  UWONG                           auwWesewvedFowBIOS[2];      //Don't use them
  UWONG                           uwMinPixewCwockPWW_Output;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMaxPixewCwock;            //In 10Khz unit, Max.  Pcwk
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMinPixewCwockPWW_Output;  //In 10Khz unit - wowew 16bit of uwMinPixewCwockPWW_Output
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usWefewenceCwock;           //In 10Khz unit
  USHOWT                          usPM_WTS_Wocation;          //WTS PM4 stawting wocation in WOM in 1Kb unit
  UCHAW                           ucPM_WTS_StweamSize;        //WTS PM4 packets in Kb unit
  UCHAW                           ucDesign_ID;                //Indicate what is the boawd design
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
}ATOM_FIWMWAWE_INFO_V1_2;

typedef stwuct _ATOM_FIWMWAWE_INFO_V1_3
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwDwivewTawgetEngineCwock;  //In 10Khz unit
  UWONG                           uwDwivewTawgetMemowyCwock;  //In 10Khz unit
  UWONG                           uwMaxEngineCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxMemowyCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwASICMaxEngineCwock;       //In 10Khz unit
  UWONG                           uwASICMaxMemowyCwock;       //In 10Khz unit
  UCHAW                           ucASICMaxTempewatuwe;
  UCHAW                           ucMinAwwowedBW_Wevew;
  UCHAW                           ucPadding[2];               //Don't use them
  UWONG                           auwWesewvedFowBIOS;         //Don't use them
  UWONG                           uw3DAccewewationEngineCwock;//In 10Khz unit
  UWONG                           uwMinPixewCwockPWW_Output;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMaxPixewCwock;            //In 10Khz unit, Max.  Pcwk
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMinPixewCwockPWW_Output;  //In 10Khz unit - wowew 16bit of uwMinPixewCwockPWW_Output
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usWefewenceCwock;           //In 10Khz unit
  USHOWT                          usPM_WTS_Wocation;          //WTS PM4 stawting wocation in WOM in 1Kb unit
  UCHAW                           ucPM_WTS_StweamSize;        //WTS PM4 packets in Kb unit
  UCHAW                           ucDesign_ID;                //Indicate what is the boawd design
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
}ATOM_FIWMWAWE_INFO_V1_3;

typedef stwuct _ATOM_FIWMWAWE_INFO_V1_4
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwDwivewTawgetEngineCwock;  //In 10Khz unit
  UWONG                           uwDwivewTawgetMemowyCwock;  //In 10Khz unit
  UWONG                           uwMaxEngineCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxMemowyCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwASICMaxEngineCwock;       //In 10Khz unit
  UWONG                           uwASICMaxMemowyCwock;       //In 10Khz unit
  UCHAW                           ucASICMaxTempewatuwe;
  UCHAW                           ucMinAwwowedBW_Wevew;
  USHOWT                          usBootUpVDDCVowtage;        //In MV unit
  USHOWT                          usWcdMinPixewCwockPWW_Output; // In MHz unit
  USHOWT                          usWcdMaxPixewCwockPWW_Output; // In MHz unit
  UWONG                           uw3DAccewewationEngineCwock;//In 10Khz unit
  UWONG                           uwMinPixewCwockPWW_Output;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMaxPixewCwock;            //In 10Khz unit, Max.  Pcwk
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMinPixewCwockPWW_Output;  //In 10Khz unit - wowew 16bit of uwMinPixewCwockPWW_Output
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usWefewenceCwock;           //In 10Khz unit
  USHOWT                          usPM_WTS_Wocation;          //WTS PM4 stawting wocation in WOM in 1Kb unit
  UCHAW                           ucPM_WTS_StweamSize;        //WTS PM4 packets in Kb unit
  UCHAW                           ucDesign_ID;                //Indicate what is the boawd design
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
}ATOM_FIWMWAWE_INFO_V1_4;

//the stwuctuwe bewow to be used fwom Cypwess
typedef stwuct _ATOM_FIWMWAWE_INFO_V2_1
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwWesewved1;
  UWONG                           uwWesewved2;
  UWONG                           uwMaxEngineCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxMemowyCwockPWW_Output; //In 10Khz unit
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwBinawyAwtewedInfo;        //Was uwASICMaxEngineCwock
  UWONG                           uwDefauwtDispEngineCwkFweq; //In 10Khz unit
  UCHAW                           ucWesewved1;                //Was ucASICMaxTempewatuwe;
  UCHAW                           ucMinAwwowedBW_Wevew;
  USHOWT                          usBootUpVDDCVowtage;        //In MV unit
  USHOWT                          usWcdMinPixewCwockPWW_Output; // In MHz unit
  USHOWT                          usWcdMaxPixewCwockPWW_Output; // In MHz unit
  UWONG                           uwWesewved4;                //Was uwAsicMaximumVowtage
  UWONG                           uwMinPixewCwockPWW_Output;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxEngineCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinEngineCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMaxMemowyCwockPWW_Input;  //In 10Khz unit
  USHOWT                          usMinMemowyCwockPWW_Output; //In 10Khz unit
  USHOWT                          usMaxPixewCwock;            //In 10Khz unit, Max.  Pcwk
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMinPixewCwockPWW_Output;  //In 10Khz unit - wowew 16bit of uwMinPixewCwockPWW_Output
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usCoweWefewenceCwock;       //In 10Khz unit
  USHOWT                          usMemowyWefewenceCwock;     //In 10Khz unit
  USHOWT                          usUniphyDPModeExtCwkFweq;   //In 10Khz unit, if it is 0, In DP Mode Uniphy Input cwock fwom intewnaw PPWW, othewwise Input cwock fwom extewnaw Spwead cwock
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
  UCHAW                           ucWesewved4[3];

}ATOM_FIWMWAWE_INFO_V2_1;

//the stwuctuwe bewow to be used fwom NI
//ucTabweFowmatWevision=2
//ucTabweContentWevision=2

typedef stwuct _PWODUCT_BWANDING
{
    UCHAW     ucEMBEDDED_CAP:2;          // Bit[1:0] Embedded featuwe wevew
    UCHAW     ucWesewved:2;              // Bit[3:2] Wesewved
    UCHAW     ucBWANDING_ID:4;           // Bit[7:4] Bwanding ID
}PWODUCT_BWANDING;

typedef stwuct _ATOM_FIWMWAWE_INFO_V2_2
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwFiwmwaweWevision;
  UWONG                           uwDefauwtEngineCwock;       //In 10Khz unit
  UWONG                           uwDefauwtMemowyCwock;       //In 10Khz unit
  UWONG                           uwSPWW_OutputFweq;          //In 10Khz unit
  UWONG                           uwGPUPWW_OutputFweq;        //In 10Khz unit
  UWONG                           uwWesewved1;                //Was uwMaxEngineCwockPWW_Output; //In 10Khz unit*
  UWONG                           uwWesewved2;                //Was uwMaxMemowyCwockPWW_Output; //In 10Khz unit*
  UWONG                           uwMaxPixewCwockPWW_Output;  //In 10Khz unit
  UWONG                           uwBinawyAwtewedInfo;        //Was uwASICMaxEngineCwock  ?
  UWONG                           uwDefauwtDispEngineCwkFweq; //In 10Khz unit. This is the fwequency befowe DCDTO, cowwesponding to usBootUpVDDCVowtage.
  UCHAW                           ucWesewved3;                //Was ucASICMaxTempewatuwe;
  UCHAW                           ucMinAwwowedBW_Wevew;
  USHOWT                          usBootUpVDDCVowtage;        //In MV unit
  USHOWT                          usWcdMinPixewCwockPWW_Output; // In MHz unit
  USHOWT                          usWcdMaxPixewCwockPWW_Output; // In MHz unit
  UWONG                           uwWesewved4;                //Was uwAsicMaximumVowtage
  UWONG                           uwMinPixewCwockPWW_Output;  //In 10Khz unit
  UCHAW                           ucWemoteDispwayConfig;
  UCHAW                           ucWesewved5[3];             //Was usMinEngineCwockPWW_Input and usMaxEngineCwockPWW_Input
  UWONG                           uwWesewved6;                //Was usMinEngineCwockPWW_Output and usMinMemowyCwockPWW_Input
  UWONG                           uwWesewved7;                //Was usMaxMemowyCwockPWW_Input and usMinMemowyCwockPWW_Output
  USHOWT                          usWesewved11;               //Was usMaxPixewCwock;  //In 10Khz unit, Max.  Pcwk used onwy fow DAC
  USHOWT                          usMinPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usMaxPixewCwockPWW_Input;   //In 10Khz unit
  USHOWT                          usBootUpVDDCIVowtage;       //In unit of mv; Was usMinPixewCwockPWW_Output;
  ATOM_FIWMWAWE_CAPABIWITY_ACCESS usFiwmwaweCapabiwity;
  USHOWT                          usCoweWefewenceCwock;       //In 10Khz unit
  USHOWT                          usMemowyWefewenceCwock;     //In 10Khz unit
  USHOWT                          usUniphyDPModeExtCwkFweq;   //In 10Khz unit, if it is 0, In DP Mode Uniphy Input cwock fwom intewnaw PPWW, othewwise Input cwock fwom extewnaw Spwead cwock
  UCHAW                           ucMemowyModuwe_ID;          //Indicate what is the boawd design
  UCHAW                           ucCoowingSowution_ID;       //0: Aiw coowing; 1: Wiquid coowing ... [COOWING_SOWUTION]
  PWODUCT_BWANDING                ucPwoductBwanding;          // Bit[7:4]ucBWANDING_ID: Bwanding ID, Bit[3:2]ucWesewved: Wesewved, Bit[1:0]ucEMBEDDED_CAP: Embedded featuwe wevew.
  UCHAW                           ucWesewved9;
  USHOWT                          usBootUpMVDDCVowtage;       //In unit of mv; Was usMinPixewCwockPWW_Output;
  USHOWT                          usBootUpVDDGFXVowtage;      //In unit of mv;
  UWONG                           uwWesewved10[3];            // New added compawing to pwevious vewsion
}ATOM_FIWMWAWE_INFO_V2_2;

#define ATOM_FIWMWAWE_INFO_WAST  ATOM_FIWMWAWE_INFO_V2_2


// definition of ucWemoteDispwayConfig
#define WEMOTE_DISPWAY_DISABWE                   0x00
#define WEMOTE_DISPWAY_ENABWE                    0x01

/****************************************************************************/
// Stwuctuwes used in IntegwatedSystemInfoTabwe
/****************************************************************************/
#define IGP_CAP_FWAG_DYNAMIC_CWOCK_EN      0x2
#define IGP_CAP_FWAG_AC_CAWD               0x4
#define IGP_CAP_FWAG_SDVO_CAWD             0x8
#define IGP_CAP_FWAG_POSTDIV_BY_2_MODE     0x10

typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO
{
  ATOM_COMMON_TABWE_HEADEW        sHeadew;
  UWONG                           uwBootUpEngineCwock;          //in 10kHz unit
  UWONG                           uwBootUpMemowyCwock;          //in 10kHz unit
  UWONG                           uwMaxSystemMemowyCwock;       //in 10kHz unit
  UWONG                           uwMinSystemMemowyCwock;       //in 10kHz unit
  UCHAW                           ucNumbewOfCycwesInPewiodHi;
  UCHAW                           ucWCDTimingSew;             //=0:not vawid.!=0 sew this timing descwiptow fwom WCD EDID.
  USHOWT                          usWesewved1;
  USHOWT                          usIntewNBVowtageWow;        //An intewmidiate PMW vawue to set the vowtage
  USHOWT                          usIntewNBVowtageHigh;       //Anothew intewmidiate PMW vawue to set the vowtage
  UWONG                           uwWesewved[2];

  USHOWT                          usFSBCwock;                     //In MHz unit
  USHOWT                          usCapabiwityFwag;              //Bit0=1 indicates the fake HDMI suppowt,Bit1=0/1 fow Dynamic cwocking dis/enabwe
                                                                              //Bit[3:2]== 0:No PCIE cawd, 1:AC cawd, 2:SDVO cawd
                                                              //Bit[4]==1: P/2 mode, ==0: P/1 mode
  USHOWT                          usPCIENBCfgWeg7;                //bit[7:0]=MUX_Sew, bit[9:8]=MUX_SEW_WEVEW2, bit[10]=Wane_Wevewsaw
  USHOWT                          usK8MemowyCwock;            //in MHz unit
  USHOWT                          usK8SyncStawtDeway;         //in 0.01 us unit
  USHOWT                          usK8DataWetuwnTime;         //in 0.01 us unit
  UCHAW                           ucMaxNBVowtage;
  UCHAW                           ucMinNBVowtage;
  UCHAW                           ucMemowyType;                     //[7:4]=1:DDW1;=2:DDW2;=3:DDW3.[3:0] is wesewved
  UCHAW                           ucNumbewOfCycwesInPewiod;      //CG.FVTHWOT_PWM_CTWW_WEG0.NumbewOfCycwesInPewiod
  UCHAW                           ucStawtingPWM_HighTime;     //CG.FVTHWOT_PWM_CTWW_WEG0.StawtingPWM_HighTime
  UCHAW                           ucHTWinkWidth;              //16 bit vs. 8 bit
  UCHAW                           ucMaxNBVowtageHigh;
  UCHAW                           ucMinNBVowtageHigh;
}ATOM_INTEGWATED_SYSTEM_INFO;

/* Expwanation on entwies in ATOM_INTEGWATED_SYSTEM_INFO
uwBootUpMemowyCwock:    Fow Intew IGP,it's the UMA system memowy cwock
                        Fow AMD IGP,it's 0 if no SidePowt memowy instawwed ow it's the boot-up SidePowt memowy cwock
uwMaxSystemMemowyCwock: Fow Intew IGP,it's the Max fweq fwom memowy SPD if memowy wuns in ASYNC mode ow othewwise (SYNC mode) it's 0
                        Fow AMD IGP,fow now this can be 0
uwMinSystemMemowyCwock: Fow Intew IGP,it's 133MHz if memowy wuns in ASYNC mode ow othewwise (SYNC mode) it's 0
                        Fow AMD IGP,fow now this can be 0

usFSBCwock:             Fow Intew IGP,it's FSB Fweq
                        Fow AMD IGP,it's HT Wink Speed

usK8MemowyCwock:        Fow AMD IGP onwy. Fow WevF CPU, set it to 200
usK8SyncStawtDeway:     Fow AMD IGP onwy. Memowy access watency in K8, wequiwed fow watewmawk cawcuwation
usK8DataWetuwnTime:     Fow AMD IGP onwy. Memowy access watency in K8, wequiwed fow watewmawk cawcuwation

VC:Vowtage Contwow
ucMaxNBVowtage:         Vowtage weguwatow dependent PWM vawue. Wow 8 bits of the vawue fow the max vowtage.Set this one to 0xFF if VC without PWM. Set this to 0x0 if no VC at aww.
ucMinNBVowtage:         Vowtage weguwatow dependent PWM vawue. Wow 8 bits of the vawue fow the min vowtage.Set this one to 0x00 if VC without PWM ow no VC at aww.

ucNumbewOfCycwesInPewiod:   Indicate how many cycwes when PWM duty is 100%. wow 8 bits of the vawue.
ucNumbewOfCycwesInPewiodHi: Indicate how many cycwes when PWM duty is 100%. high 8 bits of the vawue.If the PWM has an invewtew,set bit [7]==1,othewwise set it 0

ucMaxNBVowtageHigh:     Vowtage weguwatow dependent PWM vawue. High 8 bits of  the vawue fow the max vowtage.Set this one to 0xFF if VC without PWM. Set this to 0x0 if no VC at aww.
ucMinNBVowtageHigh:     Vowtage weguwatow dependent PWM vawue. High 8 bits of the vawue fow the min vowtage.Set this one to 0x00 if VC without PWM ow no VC at aww.


usIntewNBVowtageWow:    Vowtage weguwatow dependent PWM vawue. The vawue makes the vowtage >=Min NB vowtage but <=IntewNBVowtageHigh. Set this to 0x0000 if VC without PWM ow no VC at aww.
usIntewNBVowtageHigh:   Vowtage weguwatow dependent PWM vawue. The vawue makes the vowtage >=IntewNBVowtageWow but <=Max NB vowtage.Set this to 0x0000 if VC without PWM ow no VC at aww.
*/


/*
The fowwowing IGP tabwe is intwoduced fwom WS780, which is supposed to be put by SBIOS in FB befowe IGP VBIOS stawts VPOST;
Then VBIOS wiww copy the whowe stwuctuwe to its image so aww GPU SW components can access this data stwuctuwe to get whatevew they need.
The enough wesewvation shouwd awwow us to nevew change tabwe wevisions. Whenevew needed, a GPU SW component can use wesewved powtion fow new data entwies.

SW components can access the IGP system infow stwuctuwe in the same way as befowe
*/


typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V2
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG                      uwBootUpEngineCwock;       //in 10kHz unit
  UWONG                      uwWesewved1[2];            //must be 0x0 fow the wesewved
  UWONG                      uwBootUpUMACwock;          //in 10kHz unit
  UWONG                      uwBootUpSidePowtCwock;     //in 10kHz unit
  UWONG                      uwMinSidePowtCwock;        //in 10kHz unit
  UWONG                      uwWesewved2[6];            //must be 0x0 fow the wesewved
  UWONG                      uwSystemConfig;            //see expwanation bewow
  UWONG                      uwBootUpWeqDispwayVectow;
  UWONG                      uwOthewDispwayMisc;
  UWONG                      uwDDISwot1Config;
  UWONG                      uwDDISwot2Config;
  UCHAW                      ucMemowyType;              //[3:0]=1:DDW1;=2:DDW2;=3:DDW3.[7:4] is wesewved
  UCHAW                      ucUMAChannewNumbew;
  UCHAW                      ucDockingPinBit;
  UCHAW                      ucDockingPinPowawity;
  UWONG                      uwDockingPinCFGInfo;
  UWONG                      uwCPUCapInfo;
  USHOWT                     usNumbewOfCycwesInPewiod;
  USHOWT                     usMaxNBVowtage;
  USHOWT                     usMinNBVowtage;
  USHOWT                     usBootUpNBVowtage;
  UWONG                      uwHTWinkFweq;              //in 10Khz
  USHOWT                     usMinHTWinkWidth;
  USHOWT                     usMaxHTWinkWidth;
  USHOWT                     usUMASyncStawtDeway;
  USHOWT                     usUMADataWetuwnTime;
  USHOWT                     usWinkStatusZewoTime;
  USHOWT                     usDACEfuse;            //fow stowing badgap vawue (fow WS880 onwy)
  UWONG                      uwHighVowtageHTWinkFweq;     // in 10Khz
  UWONG                      uwWowVowtageHTWinkFweq;      // in 10Khz
  USHOWT                     usMaxUpStweamHTWinkWidth;
  USHOWT                     usMaxDownStweamHTWinkWidth;
  USHOWT                     usMinUpStweamHTWinkWidth;
  USHOWT                     usMinDownStweamHTWinkWidth;
  USHOWT                     usFiwmwaweVewsion;         //0 means FW is not suppowted. Othewwise it's the FW vewsion woaded by SBIOS and dwivew shouwd enabwe FW.
  USHOWT                     usFuwwT0Time;             // Input to cawcuwate minimum HT wink change time wequiwed by NB P-State. Unit is 0.01us.
  UWONG                      uwWesewved3[96];          //must be 0x0
}ATOM_INTEGWATED_SYSTEM_INFO_V2;

/*
uwBootUpEngineCwock:   Boot-up Engine Cwock in 10Khz;
uwBootUpUMACwock:      Boot-up UMA Cwock in 10Khz; it must be 0x0 when UMA is not pwesent
uwBootUpSidePowtCwock: Boot-up SidePowt Cwock in 10Khz; it must be 0x0 when SidePowt Memowy is not pwesent,this couwd be equaw to ow wess than maximum suppowted Sidepowt memowy cwock

uwSystemConfig:
Bit[0]=1: PowewExpwess mode =0 Non-PowewExpwess mode;
Bit[1]=1: system boots up at AMD ovewdwived state ow usew customized  mode. In this case, dwivew wiww just stick to this boot-up mode. No othew PowewPway state
      =0: system boots up at dwivew contwow state. Powew state depends on PowewPway tabwe.
Bit[2]=1: PWM method is used on NB vowtage contwow. =0: GPIO method is used.
Bit[3]=1: Onwy one powew state(Pewfowmance) wiww be suppowted.
      =0: Muwtipwe powew states suppowted fwom PowewPway tabwe.
Bit[4]=1: CWMC is suppowted and enabwed on cuwwent system.
      =0: CWMC is not suppowted ow enabwed on cuwwent system. SBIOS need to suppowt HT wink/fweq change thwough ATIF intewface.
Bit[5]=1: Enabwe CDWW fow aww dwivew contwow powew states. Max HT width is fwom SBIOS, whiwe Min HT width is detewmined by dispway wequiwement.
      =0: CDWW is disabwed. If CWMC is enabwed case, Min HT width wiww be set equaw to Max HT width. If CWMC disabwed case, Max HT width wiww be appwied.
Bit[6]=1: High Vowtage wequested fow aww powew states. In this case, vowtage wiww be fowced at 1.1v and powewpway tabwe vowtage dwop/thwottwing wequest wiww be ignowed.
      =0: Vowtage settings is detewmined by powewpway tabwe.
Bit[7]=1: Enabwe CWMC as hybwid Mode. CDWD and CIWW wiww be disabwed in this case and we'we using wegacy C1E. This is wowkawound fow CPU(Gwiffin) pewfowmance issue.
      =0: Enabwe CWMC as weguwaw mode, CDWD and CIWW wiww be enabwed.
Bit[8]=1: CDWF is suppowted and enabwed on cuwwent system.
      =0: CDWF is not suppowted ow enabwed on cuwwent system.
Bit[9]=1: DWW Shut Down featuwe is enabwed on cuwwent system.
      =0: DWW Shut Down featuwe is not enabwed ow suppowted on cuwwent system.

uwBootUpWeqDispwayVectow: This dwowd is a bit vectow indicates what dispway devices awe wequested duwing boot-up. Wefew to ATOM_DEVICE_xxx_SUPPOWT fow the bit vectow definitions.

uwOthewDispwayMisc: [15:8]- Bootup WCD Expansion sewection; 0-centew, 1-fuww panew size expansion;
                       [7:0] - BootupTV standawd sewection; This is a bit vectow to indicate what TV standawds awe suppowted by the system. Wefew to ucTVSupppowtedStd definition;

uwDDISwot1Config: Descwibes the PCIE wane configuwation on this DDI PCIE swot (ADD2 cawd) ow connectow (Mobiwe design).
      [3:0]  - Bit vectow to indicate PCIE wane config of the DDI swot/connectow on chassis (bit 0=1 wane 3:0; bit 1=1 wane 7:4; bit 2=1 wane 11:8; bit 3=1 wane 15:12)
         [7:4]  - Bit vectow to indicate PCIE wane config of the same DDI swot/connectow on docking station (bit 4=1 wane 3:0; bit 5=1 wane 7:4; bit 6=1 wane 11:8; bit 7=1 wane 15:12)
      When a DDI connectow is not "paiwed" (meaming two connections mutuawexcwusive on chassis ow docking, onwy one of them can be connected at one time.
      in both chassis and docking, SBIOS has to dupwicate the same PCIE wane info fwom chassis to docking ow vice vewsa. Fow exampwe:
      one DDI connectow is onwy popuwated in docking with PCIE wane 8-11, but thewe is no paiwed connection on chassis, SBIOS has to copy bit 6 to bit 2.

         [15:8] - Wane configuwation attwibute;
      [23:16]- Connectow type, possibwe vawue:
               CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D
               CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D
               CONNECTOW_OBJECT_ID_HDMI_TYPE_A
               CONNECTOW_OBJECT_ID_DISPWAYPOWT
               CONNECTOW_OBJECT_ID_eDP
         [31:24]- Wesewved

uwDDISwot2Config: Same as Swot1.
ucMemowyType: SidePowt memowy type, set it to 0x0 when Sidepowt memowy is not instawwed. Dwivew needs this info to change sidepowt memowy cwock. Not fow dispway in CCC.
Fow IGP, Hypewmemowy is the onwy memowy type showed in CCC.

ucUMAChannewNumbew:  how many channews fow the UMA;

uwDockingPinCFGInfo: [15:0]-Bus/Device/Function # to CFG to wead this Docking Pin; [31:16]-weg offset in CFG to wead this pin
ucDockingPinBit:     which bit in this wegistew to wead the pin status;
ucDockingPinPowawity:Powawity of the pin when docked;

uwCPUCapInfo:        [7:0]=1:Gwiffin;[7:0]=2:Gweyhound;[7:0]=3:K8, [7:0]=4:Phawaoh, othew bits wesewved fow now and must be 0x0

usNumbewOfCycwesInPewiod:Indicate how many cycwes when PWM duty is 100%.

usMaxNBVowtage:Max. vowtage contwow vawue in eithew PWM ow GPIO mode.
usMinNBVowtage:Min. vowtage contwow vawue in eithew PWM ow GPIO mode.
                    GPIO mode: both usMaxNBVowtage & usMinNBVowtage have a vawid vawue uwSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOWTAGE=0
                    PWM mode: both usMaxNBVowtage & usMinNBVowtage have a vawid vawue uwSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOWTAGE=1
                    GPU SW don't contwow mode: usMaxNBVowtage & usMinNBVowtage=0 and no cawe about uwSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOWTAGE

usBootUpNBVowtage:Boot-up vowtage weguwatow dependent PWM vawue.


uwHTWinkFweq:       Bootup HT wink Fwequency in 10Khz.
usMinHTWinkWidth:   Bootup minimum HT wink width. If CDWW disabwed, this is equaw to usMaxHTWinkWidth.
                    If CDWW enabwed, both upstweam and downstweam width shouwd be the same duwing bootup.
usMaxHTWinkWidth:   Bootup maximum HT wink width. If CDWW disabwed, this is equaw to usMinHTWinkWidth.
                    If CDWW enabwed, both upstweam and downstweam width shouwd be the same duwing bootup.

usUMASyncStawtDeway: Memowy access watency, wequiwed fow watewmawk cawcuwation
usUMADataWetuwnTime: Memowy access watency, wequiwed fow watewmawk cawcuwation
usWinkStatusZewoTime:Memowy access watency wequiwed fow watewmawk cawcuwation, set this to 0x0 fow K8 CPU, set a pwopew vawue in 0.01 the unit of us
fow Gwiffin ow Gweyhound. SBIOS needs to convewt to actuaw time by:
                     if T0Ttime [5:4]=00b, then usWinkStatusZewoTime=T0Ttime [3:0]*0.1us (0.0 to 1.5us)
                     if T0Ttime [5:4]=01b, then usWinkStatusZewoTime=T0Ttime [3:0]*0.5us (0.0 to 7.5us)
                     if T0Ttime [5:4]=10b, then usWinkStatusZewoTime=T0Ttime [3:0]*2.0us (0.0 to 30us)
                     if T0Ttime [5:4]=11b, and T0Ttime [3:0]=0x0 to 0xa, then usWinkStatusZewoTime=T0Ttime [3:0]*20us (0.0 to 200us)

uwHighVowtageHTWinkFweq:     HT wink fwequency fow powew state with wow vowtage. If boot up wuns in HT1, this must be 0.
                             This must be wess than ow equaw to uwHTWinkFweq(bootup fwequency).
uwWowVowtageHTWinkFweq:      HT wink fwequency fow powew state with wow vowtage ow vowtage scawing 1.0v~1.1v. If boot up wuns in HT1, this must be 0.
                             This must be wess than ow equaw to uwHighVowtageHTWinkFweq.

usMaxUpStweamHTWinkWidth:    Asymmetwic wink width suppowt in the futuwe, to wepwace usMaxHTWinkWidth. Not used fow now.
usMaxDownStweamHTWinkWidth:  same as above.
usMinUpStweamHTWinkWidth:    Asymmetwic wink width suppowt in the futuwe, to wepwace usMinHTWinkWidth. Not used fow now.
usMinDownStweamHTWinkWidth:  same as above.
*/

// ATOM_INTEGWATED_SYSTEM_INFO::uwCPUCapInfo  - CPU type definition
#define    INTEGWATED_SYSTEM_INFO__UNKNOWN_CPU             0
#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__GWIFFIN        1
#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__GWEYHOUND      2
#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__K8             3
#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__PHAWAOH        4
#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__OWOCHI         5

#define    INTEGWATED_SYSTEM_INFO__AMD_CPU__MAX_CODE       INTEGWATED_SYSTEM_INFO__AMD_CPU__OWOCHI    // this deff wefwects max defined CPU code

#define SYSTEM_CONFIG_POWEWEXPWESS_ENABWE                 0x00000001
#define SYSTEM_CONFIG_WUN_AT_OVEWDWIVE_ENGINE             0x00000002
#define SYSTEM_CONFIG_USE_PWM_ON_VOWTAGE                  0x00000004
#define SYSTEM_CONFIG_PEWFOWMANCE_POWEWSTATE_ONWY         0x00000008
#define SYSTEM_CONFIG_CWMC_ENABWED                        0x00000010
#define SYSTEM_CONFIG_CDWW_ENABWED                        0x00000020
#define SYSTEM_CONFIG_HIGH_VOWTAGE_WEQUESTED              0x00000040
#define SYSTEM_CONFIG_CWMC_HYBWID_MODE_ENABWED            0x00000080
#define SYSTEM_CONFIG_CDWF_ENABWED                        0x00000100
#define SYSTEM_CONFIG_DWW_SHUTDOWN_ENABWED                0x00000200

#define IGP_DDI_SWOT_WANE_CONFIG_MASK                     0x000000FF

#define b0IGP_DDI_SWOT_WANE_MAP_MASK                      0x0F
#define b0IGP_DDI_SWOT_DOCKING_WANE_MAP_MASK              0xF0
#define b0IGP_DDI_SWOT_CONFIG_WANE_0_3                    0x01
#define b0IGP_DDI_SWOT_CONFIG_WANE_4_7                    0x02
#define b0IGP_DDI_SWOT_CONFIG_WANE_8_11                   0x04
#define b0IGP_DDI_SWOT_CONFIG_WANE_12_15                  0x08

#define IGP_DDI_SWOT_ATTWIBUTE_MASK                       0x0000FF00
#define IGP_DDI_SWOT_CONFIG_WEVEWSED                      0x00000100
#define b1IGP_DDI_SWOT_CONFIG_WEVEWSED                    0x01

#define IGP_DDI_SWOT_CONNECTOW_TYPE_MASK                  0x00FF0000

// IntegwatedSystemInfoTabwe new Wev is V5 aftew V2, because of the weaw wev of V2 is v1.4. This wev is used fow WW
typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V5
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG                        uwBootUpEngineCwock;       //in 10kHz unit
  UWONG                      uwDentistVCOFweq;          //Dentist VCO cwock in 10kHz unit, the souwce of GPU SCWK, WCWK, UCWK and VCWK.
  UWONG                      uwWCwockFweq;              //GPU Wcwk fweq in 10kHz unit, have wewationship with NCWK in NowthBwidge
  UWONG                        uwBootUpUMACwock;          //in 10kHz unit
  UWONG                      uwWesewved1[8];            //must be 0x0 fow the wesewved
  UWONG                      uwBootUpWeqDispwayVectow;
  UWONG                      uwOthewDispwayMisc;
  UWONG                      uwWesewved2[4];            //must be 0x0 fow the wesewved
  UWONG                      uwSystemConfig;            //TBD
  UWONG                      uwCPUCapInfo;              //TBD
  USHOWT                     usMaxNBVowtage;            //high NB vowtage, cawcuwated using cuwwent VDDNB (D24F2xDC) and VDDNB offset fuse;
  USHOWT                     usMinNBVowtage;            //wow NB vowtage, cawcuwated using cuwwent VDDNB (D24F2xDC) and VDDNB offset fuse;
  USHOWT                     usBootUpNBVowtage;         //boot up NB vowtage
  UCHAW                      ucHtcTmpWmt;               //bit [22:16] of D24F3x64 Hawdwawe Thewmaw Contwow (HTC) Wegistew, may not be needed, TBD
  UCHAW                      ucTjOffset;                //bit [28:22] of D24F3xE4 Thewmtwip Status Wegistew,may not be needed, TBD
  UWONG                      uwWesewved3[4];            //must be 0x0 fow the wesewved
  UWONG                      uwDDISwot1Config;          //see above uwDDISwot1Config definition
  UWONG                      uwDDISwot2Config;
  UWONG                      uwDDISwot3Config;
  UWONG                      uwDDISwot4Config;
  UWONG                      uwWesewved4[4];            //must be 0x0 fow the wesewved
  UCHAW                      ucMemowyType;              //[3:0]=1:DDW1;=2:DDW2;=3:DDW3.[7:4] is wesewved
  UCHAW                      ucUMAChannewNumbew;
  USHOWT                     usWesewved;
  UWONG                      uwWesewved5[4];            //must be 0x0 fow the wesewved
  UWONG                      uwCSW_M3_AWB_CNTW_DEFAUWT[10];//awways with vawues fow CSW M3 awbitew fow defauwt
  UWONG                      uwCSW_M3_AWB_CNTW_UVD[10]; //awways with vawues fow CSW M3 awbitew fow UVD pwayback
  UWONG                      uwCSW_M3_AWB_CNTW_FS3D[10];//awways with vawues fow CSW M3 awbitew fow Fuww Scween 3D appwications
  UWONG                      uwWesewved6[61];           //must be 0x0
}ATOM_INTEGWATED_SYSTEM_INFO_V5;



/****************************************************************************/
// Stwuctuwe used in GPUViwtuawizationInfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_GPU_VIWTUAWIZATION_INFO_V2_1
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG uwMCUcodeWomStawtAddw;
  UWONG uwMCUcodeWength;
  UWONG uwSMCUcodeWomStawtAddw;
  UWONG uwSMCUcodeWength;
  UWONG uwWWCVUcodeWomStawtAddw;
  UWONG uwWWCVUcodeWength;
  UWONG uwTOCUcodeStawtAddw;
  UWONG uwTOCUcodeWength;
  UWONG uwSMCPatchTabweStawtAddw;
  UWONG uwSmcPatchTabweWength;
  UWONG uwSystemFwag;
}ATOM_GPU_VIWTUAWIZATION_INFO_V2_1;


#define ATOM_CWT_INT_ENCODEW1_INDEX                       0x00000000
#define ATOM_WCD_INT_ENCODEW1_INDEX                       0x00000001
#define ATOM_TV_INT_ENCODEW1_INDEX                        0x00000002
#define ATOM_DFP_INT_ENCODEW1_INDEX                       0x00000003
#define ATOM_CWT_INT_ENCODEW2_INDEX                       0x00000004
#define ATOM_WCD_EXT_ENCODEW1_INDEX                       0x00000005
#define ATOM_TV_EXT_ENCODEW1_INDEX                        0x00000006
#define ATOM_DFP_EXT_ENCODEW1_INDEX                       0x00000007
#define ATOM_CV_INT_ENCODEW1_INDEX                        0x00000008
#define ATOM_DFP_INT_ENCODEW2_INDEX                       0x00000009
#define ATOM_CWT_EXT_ENCODEW1_INDEX                       0x0000000A
#define ATOM_CV_EXT_ENCODEW1_INDEX                        0x0000000B
#define ATOM_DFP_INT_ENCODEW3_INDEX                       0x0000000C
#define ATOM_DFP_INT_ENCODEW4_INDEX                       0x0000000D

// define ASIC intewnaw encodew id ( bit vectow ), used fow CWTC_SouwceSewTabwe
#define ASIC_INT_DAC1_ENCODEW_ID                                     0x00
#define ASIC_INT_TV_ENCODEW_ID                                       0x02
#define ASIC_INT_DIG1_ENCODEW_ID                                     0x03
#define ASIC_INT_DAC2_ENCODEW_ID                                     0x04
#define ASIC_EXT_TV_ENCODEW_ID                                       0x06
#define ASIC_INT_DVO_ENCODEW_ID                                      0x07
#define ASIC_INT_DIG2_ENCODEW_ID                                     0x09
#define ASIC_EXT_DIG_ENCODEW_ID                                      0x05
#define ASIC_EXT_DIG2_ENCODEW_ID                                     0x08
#define ASIC_INT_DIG3_ENCODEW_ID                                     0x0a
#define ASIC_INT_DIG4_ENCODEW_ID                                     0x0b
#define ASIC_INT_DIG5_ENCODEW_ID                                     0x0c
#define ASIC_INT_DIG6_ENCODEW_ID                                     0x0d
#define ASIC_INT_DIG7_ENCODEW_ID                                     0x0e

//define Encodew attwibute
#define ATOM_ANAWOG_ENCODEW                                                0
#define ATOM_DIGITAW_ENCODEW                                             1
#define ATOM_DP_ENCODEW                                                   2

#define ATOM_ENCODEW_ENUM_MASK                            0x70
#define ATOM_ENCODEW_ENUM_ID1                             0x00
#define ATOM_ENCODEW_ENUM_ID2                             0x10
#define ATOM_ENCODEW_ENUM_ID3                             0x20
#define ATOM_ENCODEW_ENUM_ID4                             0x30
#define ATOM_ENCODEW_ENUM_ID5                             0x40
#define ATOM_ENCODEW_ENUM_ID6                             0x50

#define ATOM_DEVICE_CWT1_INDEX                            0x00000000
#define ATOM_DEVICE_WCD1_INDEX                            0x00000001
#define ATOM_DEVICE_TV1_INDEX                             0x00000002
#define ATOM_DEVICE_DFP1_INDEX                            0x00000003
#define ATOM_DEVICE_CWT2_INDEX                            0x00000004
#define ATOM_DEVICE_WCD2_INDEX                            0x00000005
#define ATOM_DEVICE_DFP6_INDEX                            0x00000006
#define ATOM_DEVICE_DFP2_INDEX                            0x00000007
#define ATOM_DEVICE_CV_INDEX                              0x00000008
#define ATOM_DEVICE_DFP3_INDEX                            0x00000009
#define ATOM_DEVICE_DFP4_INDEX                            0x0000000A
#define ATOM_DEVICE_DFP5_INDEX                            0x0000000B

#define ATOM_DEVICE_WESEWVEDC_INDEX                       0x0000000C
#define ATOM_DEVICE_WESEWVEDD_INDEX                       0x0000000D
#define ATOM_DEVICE_WESEWVEDE_INDEX                       0x0000000E
#define ATOM_DEVICE_WESEWVEDF_INDEX                       0x0000000F
#define ATOM_MAX_SUPPOWTED_DEVICE_INFO                    (ATOM_DEVICE_DFP3_INDEX+1)
#define ATOM_MAX_SUPPOWTED_DEVICE_INFO_2                  ATOM_MAX_SUPPOWTED_DEVICE_INFO
#define ATOM_MAX_SUPPOWTED_DEVICE_INFO_3                  (ATOM_DEVICE_DFP5_INDEX + 1 )

#define ATOM_MAX_SUPPOWTED_DEVICE                         (ATOM_DEVICE_WESEWVEDF_INDEX+1)

#define ATOM_DEVICE_CWT1_SUPPOWT                          (0x1W << ATOM_DEVICE_CWT1_INDEX )
#define ATOM_DEVICE_WCD1_SUPPOWT                          (0x1W << ATOM_DEVICE_WCD1_INDEX )
#define ATOM_DEVICE_TV1_SUPPOWT                           (0x1W << ATOM_DEVICE_TV1_INDEX  )
#define ATOM_DEVICE_DFP1_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP1_INDEX )
#define ATOM_DEVICE_CWT2_SUPPOWT                          (0x1W << ATOM_DEVICE_CWT2_INDEX )
#define ATOM_DEVICE_WCD2_SUPPOWT                          (0x1W << ATOM_DEVICE_WCD2_INDEX )
#define ATOM_DEVICE_DFP6_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP6_INDEX )
#define ATOM_DEVICE_DFP2_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP2_INDEX )
#define ATOM_DEVICE_CV_SUPPOWT                            (0x1W << ATOM_DEVICE_CV_INDEX   )
#define ATOM_DEVICE_DFP3_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP3_INDEX )
#define ATOM_DEVICE_DFP4_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP4_INDEX )
#define ATOM_DEVICE_DFP5_SUPPOWT                          (0x1W << ATOM_DEVICE_DFP5_INDEX )


#define ATOM_DEVICE_CWT_SUPPOWT                           (ATOM_DEVICE_CWT1_SUPPOWT | ATOM_DEVICE_CWT2_SUPPOWT)
#define ATOM_DEVICE_DFP_SUPPOWT                           (ATOM_DEVICE_DFP1_SUPPOWT | ATOM_DEVICE_DFP2_SUPPOWT |  ATOM_DEVICE_DFP3_SUPPOWT | ATOM_DEVICE_DFP4_SUPPOWT | ATOM_DEVICE_DFP5_SUPPOWT | ATOM_DEVICE_DFP6_SUPPOWT)
#define ATOM_DEVICE_TV_SUPPOWT                            ATOM_DEVICE_TV1_SUPPOWT
#define ATOM_DEVICE_WCD_SUPPOWT                           (ATOM_DEVICE_WCD1_SUPPOWT | ATOM_DEVICE_WCD2_SUPPOWT)

#define ATOM_DEVICE_CONNECTOW_TYPE_MASK                   0x000000F0
#define ATOM_DEVICE_CONNECTOW_TYPE_SHIFT                  0x00000004
#define ATOM_DEVICE_CONNECTOW_VGA                         0x00000001
#define ATOM_DEVICE_CONNECTOW_DVI_I                       0x00000002
#define ATOM_DEVICE_CONNECTOW_DVI_D                       0x00000003
#define ATOM_DEVICE_CONNECTOW_DVI_A                       0x00000004
#define ATOM_DEVICE_CONNECTOW_SVIDEO                      0x00000005
#define ATOM_DEVICE_CONNECTOW_COMPOSITE                   0x00000006
#define ATOM_DEVICE_CONNECTOW_WVDS                        0x00000007
#define ATOM_DEVICE_CONNECTOW_DIGI_WINK                   0x00000008
#define ATOM_DEVICE_CONNECTOW_SCAWT                       0x00000009
#define ATOM_DEVICE_CONNECTOW_HDMI_TYPE_A                 0x0000000A
#define ATOM_DEVICE_CONNECTOW_HDMI_TYPE_B                 0x0000000B
#define ATOM_DEVICE_CONNECTOW_CASE_1                      0x0000000E
#define ATOM_DEVICE_CONNECTOW_DISPWAYPOWT                 0x0000000F


#define ATOM_DEVICE_DAC_INFO_MASK                         0x0000000F
#define ATOM_DEVICE_DAC_INFO_SHIFT                        0x00000000
#define ATOM_DEVICE_DAC_INFO_NODAC                        0x00000000
#define ATOM_DEVICE_DAC_INFO_DACA                         0x00000001
#define ATOM_DEVICE_DAC_INFO_DACB                         0x00000002
#define ATOM_DEVICE_DAC_INFO_EXDAC                        0x00000003

#define ATOM_DEVICE_I2C_ID_NOI2C                          0x00000000

#define ATOM_DEVICE_I2C_WINEMUX_MASK                      0x0000000F
#define ATOM_DEVICE_I2C_WINEMUX_SHIFT                     0x00000000

#define ATOM_DEVICE_I2C_ID_MASK                           0x00000070
#define ATOM_DEVICE_I2C_ID_SHIFT                          0x00000004
#define ATOM_DEVICE_I2C_ID_IS_FOW_NON_MM_USE              0x00000001
#define ATOM_DEVICE_I2C_ID_IS_FOW_MM_USE                  0x00000002
#define ATOM_DEVICE_I2C_ID_IS_FOW_SDVO_USE                0x00000003    //Fow IGP WS600
#define ATOM_DEVICE_I2C_ID_IS_FOW_DAC_SCW                 0x00000004    //Fow IGP WS690

#define ATOM_DEVICE_I2C_HAWDWAWE_CAP_MASK                 0x00000080
#define ATOM_DEVICE_I2C_HAWDWAWE_CAP_SHIFT                0x00000007
#define ATOM_DEVICE_USES_SOFTWAWE_ASSISTED_I2C            0x00000000
#define ATOM_DEVICE_USES_HAWDWAWE_ASSISTED_I2C            0x00000001

//  usDeviceSuppowt:
//  Bits0   = 0 - no CWT1 suppowt= 1- CWT1 is suppowted
//  Bit 1   = 0 - no WCD1 suppowt= 1- WCD1 is suppowted
//  Bit 2   = 0 - no TV1  suppowt= 1- TV1  is suppowted
//  Bit 3   = 0 - no DFP1 suppowt= 1- DFP1 is suppowted
//  Bit 4   = 0 - no CWT2 suppowt= 1- CWT2 is suppowted
//  Bit 5   = 0 - no WCD2 suppowt= 1- WCD2 is suppowted
//  Bit 6   = 0 - no DFP6 suppowt= 1- DFP6 is suppowted
//  Bit 7   = 0 - no DFP2 suppowt= 1- DFP2 is suppowted
//  Bit 8   = 0 - no CV   suppowt= 1- CV   is suppowted
//  Bit 9   = 0 - no DFP3 suppowt= 1- DFP3 is suppowted
//  Bit 10= 0 - no DFP4 suppowt= 1- DFP4 is suppowted
//  Bit 11= 0 - no DFP5 suppowt= 1- DFP5 is suppowted
//
//

/****************************************************************************/
// Stwuctuwe used in McwkSS_InfoTabwe
/****************************************************************************/
//      ucI2C_ConfigID
//    [7:0] - I2C WINE Associate ID
//          = 0   - no I2C
//    [7]      -   HW_Cap        =   1,  [6:0]=HW assisted I2C ID(HW wine sewection)
//                          =   0,  [6:0]=SW assisted I2C ID
//    [6-4]   - HW_ENGINE_ID  =   1,  HW engine fow NON muwtimedia use
//                          =   2,   HW engine fow Muwtimedia use
//                          =   3-7   Wesewved fow futuwe I2C engines
//      [3-0] - I2C_WINE_MUX  = A Mux numbew when it's HW assisted I2C ow GPIO ID when it's SW I2C

typedef stwuct _ATOM_I2C_ID_CONFIG
{
#if ATOM_BIG_ENDIAN
  UCHAW   bfHW_Capabwe:1;
  UCHAW   bfHW_EngineID:3;
  UCHAW   bfI2C_WineMux:4;
#ewse
  UCHAW   bfI2C_WineMux:4;
  UCHAW   bfHW_EngineID:3;
  UCHAW   bfHW_Capabwe:1;
#endif
}ATOM_I2C_ID_CONFIG;

typedef union _ATOM_I2C_ID_CONFIG_ACCESS
{
  ATOM_I2C_ID_CONFIG sbfAccess;
  UCHAW              ucAccess;
}ATOM_I2C_ID_CONFIG_ACCESS;


/****************************************************************************/
// Stwuctuwe used in GPIO_I2C_InfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_GPIO_I2C_ASSIGMENT
{
  USHOWT                    usCwkMaskWegistewIndex;
  USHOWT                    usCwkEnWegistewIndex;
  USHOWT                    usCwkY_WegistewIndex;
  USHOWT                    usCwkA_WegistewIndex;
  USHOWT                    usDataMaskWegistewIndex;
  USHOWT                    usDataEnWegistewIndex;
  USHOWT                    usDataY_WegistewIndex;
  USHOWT                    usDataA_WegistewIndex;
  ATOM_I2C_ID_CONFIG_ACCESS sucI2cId;
  UCHAW                     ucCwkMaskShift;
  UCHAW                     ucCwkEnShift;
  UCHAW                     ucCwkY_Shift;
  UCHAW                     ucCwkA_Shift;
  UCHAW                     ucDataMaskShift;
  UCHAW                     ucDataEnShift;
  UCHAW                     ucDataY_Shift;
  UCHAW                     ucDataA_Shift;
  UCHAW                     ucWesewved1;
  UCHAW                     ucWesewved2;
}ATOM_GPIO_I2C_ASSIGMENT;

typedef stwuct _ATOM_GPIO_I2C_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  ATOM_GPIO_I2C_ASSIGMENT   asGPIO_Info[ATOM_MAX_SUPPOWTED_DEVICE];
}ATOM_GPIO_I2C_INFO;

/****************************************************************************/
// Common Stwuctuwe used in othew stwuctuwes
/****************************************************************************/

#ifndef _H2INC

//Pwease don't add ow expand this bitfiewd stwuctuwe bewow, this one wiww wetiwe soon.!
typedef stwuct _ATOM_MODE_MISC_INFO
{
#if ATOM_BIG_ENDIAN
  USHOWT Wesewved:6;
  USHOWT WGB888:1;
  USHOWT DoubweCwock:1;
  USHOWT Intewwace:1;
  USHOWT CompositeSync:1;
  USHOWT V_WepwicationBy2:1;
  USHOWT H_WepwicationBy2:1;
  USHOWT VewticawCutOff:1;
  USHOWT VSyncPowawity:1;      //0=Active High, 1=Active Wow
  USHOWT HSyncPowawity:1;      //0=Active High, 1=Active Wow
  USHOWT HowizontawCutOff:1;
#ewse
  USHOWT HowizontawCutOff:1;
  USHOWT HSyncPowawity:1;      //0=Active High, 1=Active Wow
  USHOWT VSyncPowawity:1;      //0=Active High, 1=Active Wow
  USHOWT VewticawCutOff:1;
  USHOWT H_WepwicationBy2:1;
  USHOWT V_WepwicationBy2:1;
  USHOWT CompositeSync:1;
  USHOWT Intewwace:1;
  USHOWT DoubweCwock:1;
  USHOWT WGB888:1;
  USHOWT Wesewved:6;
#endif
}ATOM_MODE_MISC_INFO;

typedef union _ATOM_MODE_MISC_INFO_ACCESS
{
  ATOM_MODE_MISC_INFO sbfAccess;
  USHOWT              usAccess;
}ATOM_MODE_MISC_INFO_ACCESS;

#ewse

typedef union _ATOM_MODE_MISC_INFO_ACCESS
{
  USHOWT              usAccess;
}ATOM_MODE_MISC_INFO_ACCESS;

#endif

// usModeMiscInfo-
#define ATOM_H_CUTOFF           0x01
#define ATOM_HSYNC_POWAWITY     0x02             //0=Active High, 1=Active Wow
#define ATOM_VSYNC_POWAWITY     0x04             //0=Active High, 1=Active Wow
#define ATOM_V_CUTOFF           0x08
#define ATOM_H_WEPWICATIONBY2   0x10
#define ATOM_V_WEPWICATIONBY2   0x20
#define ATOM_COMPOSITESYNC      0x40
#define ATOM_INTEWWACE          0x80
#define ATOM_DOUBWE_CWOCK_MODE  0x100
#define ATOM_WGB888_MODE        0x200

//usWefweshWate-
#define ATOM_WEFWESH_43         43
#define ATOM_WEFWESH_47         47
#define ATOM_WEFWESH_56         56
#define ATOM_WEFWESH_60         60
#define ATOM_WEFWESH_65         65
#define ATOM_WEFWESH_70         70
#define ATOM_WEFWESH_72         72
#define ATOM_WEFWESH_75         75
#define ATOM_WEFWESH_85         85

// ATOM_MODE_TIMING data awe exactwy the same as VESA timing data.
// Twanswation fwom EDID to ATOM_MODE_TIMING, use the fowwowing fowmuwa.
//
//   VESA_HTOTAW         =   VESA_ACTIVE + 2* VESA_BOWDEW + VESA_BWANK
//                  =   EDID_HA + EDID_HBW
//   VESA_HDISP         =   VESA_ACTIVE   =   EDID_HA
//   VESA_HSYNC_STAWT   =   VESA_ACTIVE + VESA_BOWDEW + VESA_FWONT_POWCH
//                  =   EDID_HA + EDID_HSO
//   VESA_HSYNC_WIDTH   =   VESA_HSYNC_TIME   =   EDID_HSPW
//   VESA_BOWDEW         =   EDID_BOWDEW


/****************************************************************************/
// Stwuctuwe used in SetCWTC_UsingDTDTimingTabwe
/****************************************************************************/
typedef stwuct _SET_CWTC_USING_DTD_TIMING_PAWAMETEWS
{
  USHOWT  usH_Size;
  USHOWT  usH_Bwanking_Time;
  USHOWT  usV_Size;
  USHOWT  usV_Bwanking_Time;
  USHOWT  usH_SyncOffset;
  USHOWT  usH_SyncWidth;
  USHOWT  usV_SyncOffset;
  USHOWT  usV_SyncWidth;
  ATOM_MODE_MISC_INFO_ACCESS  susModeMiscInfo;
  UCHAW   ucH_Bowdew;         // Fwom DFP EDID
  UCHAW   ucV_Bowdew;
  UCHAW   ucCWTC;             // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW   ucPadding[3];
}SET_CWTC_USING_DTD_TIMING_PAWAMETEWS;

/****************************************************************************/
// Stwuctuwe used in SetCWTC_TimingTabwe
/****************************************************************************/
typedef stwuct _SET_CWTC_TIMING_PAWAMETEWS
{
  USHOWT                      usH_Totaw;        // howizontaw totaw
  USHOWT                      usH_Disp;         // howizontaw dispway
  USHOWT                      usH_SyncStawt;    // howozontaw Sync stawt
  USHOWT                      usH_SyncWidth;    // howizontaw Sync width
  USHOWT                      usV_Totaw;        // vewticaw totaw
  USHOWT                      usV_Disp;         // vewticaw dispway
  USHOWT                      usV_SyncStawt;    // vewticaw Sync stawt
  USHOWT                      usV_SyncWidth;    // vewticaw Sync width
  ATOM_MODE_MISC_INFO_ACCESS  susModeMiscInfo;
  UCHAW                       ucCWTC;           // ATOM_CWTC1 ow ATOM_CWTC2
  UCHAW                       ucOvewscanWight;  // wight
  UCHAW                       ucOvewscanWeft;   // weft
  UCHAW                       ucOvewscanBottom; // bottom
  UCHAW                       ucOvewscanTop;    // top
  UCHAW                       ucWesewved;
}SET_CWTC_TIMING_PAWAMETEWS;
#define SET_CWTC_TIMING_PAWAMETEWS_PS_AWWOCATION SET_CWTC_TIMING_PAWAMETEWS


/****************************************************************************/
// Stwuctuwe used in StandawdVESA_TimingTabwe
//                   AnawogTV_InfoTabwe
//                   ComponentVideoInfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_MODE_TIMING
{
  USHOWT  usCWTC_H_Totaw;
  USHOWT  usCWTC_H_Disp;
  USHOWT  usCWTC_H_SyncStawt;
  USHOWT  usCWTC_H_SyncWidth;
  USHOWT  usCWTC_V_Totaw;
  USHOWT  usCWTC_V_Disp;
  USHOWT  usCWTC_V_SyncStawt;
  USHOWT  usCWTC_V_SyncWidth;
  USHOWT  usPixewCwock;                                //in 10Khz unit
  ATOM_MODE_MISC_INFO_ACCESS  susModeMiscInfo;
  USHOWT  usCWTC_OvewscanWight;
  USHOWT  usCWTC_OvewscanWeft;
  USHOWT  usCWTC_OvewscanBottom;
  USHOWT  usCWTC_OvewscanTop;
  USHOWT  usWesewve;
  UCHAW   ucIntewnawModeNumbew;
  UCHAW   ucWefweshWate;
}ATOM_MODE_TIMING;

typedef stwuct _ATOM_DTD_FOWMAT
{
  USHOWT  usPixCwk;
  USHOWT  usHActive;
  USHOWT  usHBwanking_Time;
  USHOWT  usVActive;
  USHOWT  usVBwanking_Time;
  USHOWT  usHSyncOffset;
  USHOWT  usHSyncWidth;
  USHOWT  usVSyncOffset;
  USHOWT  usVSyncWidth;
  USHOWT  usImageHSize;
  USHOWT  usImageVSize;
  UCHAW   ucHBowdew;
  UCHAW   ucVBowdew;
  ATOM_MODE_MISC_INFO_ACCESS susModeMiscInfo;
  UCHAW   ucIntewnawModeNumbew;
  UCHAW   ucWefweshWate;
}ATOM_DTD_FOWMAT;

/****************************************************************************/
// Stwuctuwe used in WVDS_InfoTabwe
//  * Need a document to descwibe this tabwe
/****************************************************************************/
#define SUPPOWTED_WCD_WEFWESHWATE_30Hz          0x0004
#define SUPPOWTED_WCD_WEFWESHWATE_40Hz          0x0008
#define SUPPOWTED_WCD_WEFWESHWATE_50Hz          0x0010
#define SUPPOWTED_WCD_WEFWESHWATE_60Hz          0x0020
#define SUPPOWTED_WCD_WEFWESHWATE_48Hz          0x0040

//ucTabweFowmatWevision=1
//ucTabweContentWevision=1
typedef stwuct _ATOM_WVDS_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_DTD_FOWMAT     sWCDTiming;
  USHOWT              usModePatchTabweOffset;
  USHOWT              usSuppowtedWefweshWate;     //Wefew to panew info tabwe in ATOMBIOS extension Spec.
  USHOWT              usOffDewayInMs;
  UCHAW               ucPowewSequenceDigOntoDEin10Ms;
  UCHAW               ucPowewSequenceDEtoBWOnin10Ms;
  UCHAW               ucWVDS_Misc;               // Bit0:{=0:singwe, =1:duaw},Bit1 {=0:666WGB, =1:888WGB},Bit2:3:{Gwey wevew}
                                                 // Bit4:{=0:WDI fowmat fow WGB888, =1 FPDI fowmat fow WGB888}
                                                 // Bit5:{=0:Spatiaw Dithewing disabwed;1 Spatiaw Dithewing enabwed}
                                                 // Bit6:{=0:Tempowaw Dithewing disabwed;1 Tempowaw Dithewing enabwed}
  UCHAW               ucPanewDefauwtWefweshWate;
  UCHAW               ucPanewIdentification;
  UCHAW               ucSS_Id;
}ATOM_WVDS_INFO;

//ucTabweFowmatWevision=1
//ucTabweContentWevision=2
typedef stwuct _ATOM_WVDS_INFO_V12
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_DTD_FOWMAT     sWCDTiming;
  USHOWT              usExtInfoTabweOffset;
  USHOWT              usSuppowtedWefweshWate;     //Wefew to panew info tabwe in ATOMBIOS extension Spec.
  USHOWT              usOffDewayInMs;
  UCHAW               ucPowewSequenceDigOntoDEin10Ms;
  UCHAW               ucPowewSequenceDEtoBWOnin10Ms;
  UCHAW               ucWVDS_Misc;               // Bit0:{=0:singwe, =1:duaw},Bit1 {=0:666WGB, =1:888WGB},Bit2:3:{Gwey wevew}
                                                 // Bit4:{=0:WDI fowmat fow WGB888, =1 FPDI fowmat fow WGB888}
                                                 // Bit5:{=0:Spatiaw Dithewing disabwed;1 Spatiaw Dithewing enabwed}
                                                 // Bit6:{=0:Tempowaw Dithewing disabwed;1 Tempowaw Dithewing enabwed}
  UCHAW               ucPanewDefauwtWefweshWate;
  UCHAW               ucPanewIdentification;
  UCHAW               ucSS_Id;
  USHOWT              usWCDVendewID;
  USHOWT              usWCDPwoductID;
  UCHAW               ucWCDPanew_SpeciawHandwingCap;
   UCHAW                        ucPanewInfoSize;               //  stawt fwom ATOM_DTD_FOWMAT to end of panew info, incwude ExtInfoTabwe
  UCHAW               ucWesewved[2];
}ATOM_WVDS_INFO_V12;

//Definitions fow ucWCDPanew_SpeciawHandwingCap:

//Once DAW sees this CAP is set, it wiww wead EDID fwom WCD on its own instead of using sWCDTiming in ATOM_WVDS_INFO_V12.
//Othew entwies in ATOM_WVDS_INFO_V12 awe stiww vawid/usefuw to DAW
#define   WCDPANEW_CAP_WEAD_EDID                  0x1

//If a design suppowts DWW (dynamic wefwesh wate) on intewnaw panews (WVDS ow EDP), this cap is set in ucWCDPanew_SpeciawHandwingCap togethew
//with muwtipwe suppowted wefwesh wates@usSuppowtedWefweshWate. This cap shouwd not be set when onwy swow wefwesh wate is suppowted (static
//wefwesh wate switch by SW. This is onwy vawid fwom ATOM_WVDS_INFO_V12
#define   WCDPANEW_CAP_DWW_SUPPOWTED              0x2

//Use this cap bit fow a quick wefewence whethew an embadded panew (WCD1 ) is WVDS ow eDP.
#define   WCDPANEW_CAP_eDP                        0x4


//Cowow Bit Depth definition in EDID V1.4 @BYTE 14h
//Bit 6  5  4
                              //      0  0  0  -  Cowow bit depth is undefined
                              //      0  0  1  -  6 Bits pew Pwimawy Cowow
                              //      0  1  0  -  8 Bits pew Pwimawy Cowow
                              //      0  1  1  - 10 Bits pew Pwimawy Cowow
                              //      1  0  0  - 12 Bits pew Pwimawy Cowow
                              //      1  0  1  - 14 Bits pew Pwimawy Cowow
                              //      1  1  0  - 16 Bits pew Pwimawy Cowow
                              //      1  1  1  - Wesewved

#define PANEW_COWOW_BIT_DEPTH_MASK    0x70

// Bit7:{=0:Wandom Dithewing disabwed;1 Wandom Dithewing enabwed}
#define PANEW_WANDOM_DITHEW   0x80
#define PANEW_WANDOM_DITHEW_MASK   0x80

#define ATOM_WVDS_INFO_WAST  ATOM_WVDS_INFO_V12   // no need to change this


typedef stwuct _ATOM_WCD_WEFWESH_WATE_SUPPOWT
{
    UCHAW ucSuppowtedWefweshWate;
    UCHAW ucMinWefweshWateFowDWW;
}ATOM_WCD_WEFWESH_WATE_SUPPOWT;

/****************************************************************************/
// Stwuctuwes used by WCD_InfoTabwe V1.3    Note: pwevious vewsion was cawwed ATOM_WVDS_INFO_V12
// ASIC Famiwies:  NI
// ucTabweFowmatWevision=1
// ucTabweContentWevision=3
/****************************************************************************/
typedef stwuct _ATOM_WCD_INFO_V13
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_DTD_FOWMAT     sWCDTiming;
  USHOWT              usExtInfoTabweOffset;
  union
  {
    USHOWT            usSuppowtedWefweshWate;
    ATOM_WCD_WEFWESH_WATE_SUPPOWT sWefweshWateSuppowt;
  };
  UWONG               uwWesewved0;
  UCHAW               ucWCD_Misc;                // Weowganized in V13
                                                 // Bit0: {=0:singwe, =1:duaw},
                                                 // Bit1: {=0:WDI fowmat fow WGB888, =1 FPDI fowmat fow WGB888}  // was {=0:666WGB, =1:888WGB},
                                                 // Bit3:2: {Gwey wevew}
                                                 // Bit6:4 Cowow Bit Depth definition (see bewow definition in EDID V1.4 @BYTE 14h)
                                                 // Bit7   Wesewved.  was fow ATOM_PANEW_MISC_API_ENABWED, stiww need it?
  UCHAW               ucPanewDefauwtWefweshWate;
  UCHAW               ucPanewIdentification;
  UCHAW               ucSS_Id;
  USHOWT              usWCDVendewID;
  USHOWT              usWCDPwoductID;
  UCHAW               ucWCDPanew_SpeciawHandwingCap;  // Weowganized in V13
                                                 // Bit0: Once DAW sees this CAP is set, it wiww wead EDID fwom WCD on its own
                                                 // Bit1: See WCDPANEW_CAP_DWW_SUPPOWTED
                                                 // Bit2: a quick wefewence whethew an embadded panew (WCD1 ) is WVDS (0) ow eDP (1)
                                                 // Bit7-3: Wesewved
  UCHAW               ucPanewInfoSize;                //  stawt fwom ATOM_DTD_FOWMAT to end of panew info, incwude ExtInfoTabwe
  USHOWT              usBackwightPWM;            //  Backwight PWM in Hz. New in _V13

  UCHAW               ucPowewSequenceDIGONtoDE_in4Ms;
  UCHAW               ucPowewSequenceDEtoVAWY_BW_in4Ms;
  UCHAW               ucPowewSequenceVAWY_BWtoDE_in4Ms;
  UCHAW               ucPowewSequenceDEtoDIGON_in4Ms;

  UCHAW               ucOffDeway_in4Ms;
  UCHAW               ucPowewSequenceVAWY_BWtoBWON_in4Ms;
  UCHAW               ucPowewSequenceBWONtoVAWY_BW_in4Ms;
  UCHAW               ucWesewved1;

  UCHAW               ucDPCD_eDP_CONFIGUWATION_CAP;     // dpcd 0dh
  UCHAW               ucDPCD_MAX_WINK_WATE;             // dpcd 01h
  UCHAW               ucDPCD_MAX_WANE_COUNT;            // dpcd 02h
  UCHAW               ucDPCD_MAX_DOWNSPWEAD;            // dpcd 03h

  USHOWT              usMaxPcwkFweqInSingweWink;        // Max PixewCwock fwequency in singwe wink mode.
  UCHAW               uceDPToWVDSWxId;
  UCHAW               ucWcdWesewvd;
  UWONG               uwWesewved[2];
}ATOM_WCD_INFO_V13;

#define ATOM_WCD_INFO_WAST  ATOM_WCD_INFO_V13

//Definitions fow ucWCD_Misc
#define ATOM_PANEW_MISC_V13_DUAW                   0x00000001
#define ATOM_PANEW_MISC_V13_FPDI                   0x00000002
#define ATOM_PANEW_MISC_V13_GWEY_WEVEW             0x0000000C
#define ATOM_PANEW_MISC_V13_GWEY_WEVEW_SHIFT       2
#define ATOM_PANEW_MISC_V13_COWOW_BIT_DEPTH_MASK   0x70
#define ATOM_PANEW_MISC_V13_6BIT_PEW_COWOW         0x10
#define ATOM_PANEW_MISC_V13_8BIT_PEW_COWOW         0x20

//Cowow Bit Depth definition in EDID V1.4 @BYTE 14h
//Bit 6  5  4
                              //      0  0  0  -  Cowow bit depth is undefined
                              //      0  0  1  -  6 Bits pew Pwimawy Cowow
                              //      0  1  0  -  8 Bits pew Pwimawy Cowow
                              //      0  1  1  - 10 Bits pew Pwimawy Cowow
                              //      1  0  0  - 12 Bits pew Pwimawy Cowow
                              //      1  0  1  - 14 Bits pew Pwimawy Cowow
                              //      1  1  0  - 16 Bits pew Pwimawy Cowow
                              //      1  1  1  - Wesewved

//Definitions fow ucWCDPanew_SpeciawHandwingCap:

//Once DAW sees this CAP is set, it wiww wead EDID fwom WCD on its own instead of using sWCDTiming in ATOM_WVDS_INFO_V12.
//Othew entwies in ATOM_WVDS_INFO_V12 awe stiww vawid/usefuw to DAW
#define   WCDPANEW_CAP_V13_WEAD_EDID              0x1        // = WCDPANEW_CAP_WEAD_EDID no change compawing to pwevious vewsion

//If a design suppowts DWW (dynamic wefwesh wate) on intewnaw panews (WVDS ow EDP), this cap is set in ucWCDPanew_SpeciawHandwingCap togethew
//with muwtipwe suppowted wefwesh wates@usSuppowtedWefweshWate. This cap shouwd not be set when onwy swow wefwesh wate is suppowted (static
//wefwesh wate switch by SW. This is onwy vawid fwom ATOM_WVDS_INFO_V12
#define   WCDPANEW_CAP_V13_DWW_SUPPOWTED          0x2        // = WCDPANEW_CAP_DWW_SUPPOWTED no change compawing to pwevious vewsion

//Use this cap bit fow a quick wefewence whethew an embadded panew (WCD1 ) is WVDS ow eDP.
#define   WCDPANEW_CAP_V13_eDP                    0x4        // = WCDPANEW_CAP_eDP no change compawing to pwevious vewsion

//uceDPToWVDSWxId
#define eDP_TO_WVDS_WX_DISABWE                  0x00       // no eDP->WVDS twanswatow chip
#define eDP_TO_WVDS_COMMON_ID                   0x01       // common eDP->WVDS twanswatow chip without AMD SW init
#define eDP_TO_WVDS_WT_ID                       0x02       // WT tansawtow which wequiwe AMD SW init

typedef stwuct  _ATOM_PATCH_WECOWD_MODE
{
  UCHAW     ucWecowdType;
  USHOWT    usHDisp;
  USHOWT    usVDisp;
}ATOM_PATCH_WECOWD_MODE;

typedef stwuct  _ATOM_WCD_WTS_WECOWD
{
  UCHAW     ucWecowdType;
  UCHAW     ucWTSVawue;
}ATOM_WCD_WTS_WECOWD;

//!! If the wecowd bewow exits, it shoud awways be the fiwst wecowd fow easy use in command tabwe!!!
// The wecowd bewow is onwy used when WVDS_Info is pwesent. Fwom ATOM_WVDS_INFO_V12, use ucWCDPanew_SpeciawHandwingCap instead.
typedef stwuct  _ATOM_WCD_MODE_CONTWOW_CAP
{
  UCHAW     ucWecowdType;
  USHOWT    usWCDCap;
}ATOM_WCD_MODE_CONTWOW_CAP;

#define WCD_MODE_CAP_BW_OFF                   1
#define WCD_MODE_CAP_CWTC_OFF                 2
#define WCD_MODE_CAP_PANEW_OFF                4


typedef stwuct _ATOM_FAKE_EDID_PATCH_WECOWD
{
  UCHAW ucWecowdType;
  UCHAW ucFakeEDIDWength;       // = 128 means EDID wength is 128 bytes, othewwise the EDID wength = ucFakeEDIDWength*128
  UCHAW ucFakeEDIDStwing[];     // This actuawwy has ucFakeEdidWength ewements.
} ATOM_FAKE_EDID_PATCH_WECOWD;

typedef stwuct  _ATOM_PANEW_WESOWUTION_PATCH_WECOWD
{
   UCHAW    ucWecowdType;
   USHOWT      usHSize;
   USHOWT      usVSize;
}ATOM_PANEW_WESOWUTION_PATCH_WECOWD;

#define WCD_MODE_PATCH_WECOWD_MODE_TYPE       1
#define WCD_WTS_WECOWD_TYPE                   2
#define WCD_CAP_WECOWD_TYPE                   3
#define WCD_FAKE_EDID_PATCH_WECOWD_TYPE       4
#define WCD_PANEW_WESOWUTION_WECOWD_TYPE      5
#define WCD_EDID_OFFSET_PATCH_WECOWD_TYPE     6
#define ATOM_WECOWD_END_TYPE                  0xFF

/****************************Spwead Spectwum Info Tabwe Definitions **********************/

//ucTabweFowmatWevision=1
//ucTabweContentWevision=2
typedef stwuct _ATOM_SPWEAD_SPECTWUM_ASSIGNMENT
{
  USHOWT              usSpweadSpectwumPewcentage;
  UCHAW               ucSpweadSpectwumType;       //Bit1=0 Down Spwead,=1 Centew Spwead. Bit1=1 Ext. =0 Int. Bit2=1: PCIE WEFCWK SS =0 itewnaw PPWW SS  Othews:TBD
  UCHAW               ucSS_Step;
  UCHAW               ucSS_Deway;
  UCHAW               ucSS_Id;
  UCHAW               ucWecommendedWef_Div;
  UCHAW               ucSS_Wange;               //it was wesewved fow V11
}ATOM_SPWEAD_SPECTWUM_ASSIGNMENT;

#define ATOM_MAX_SS_ENTWY                      16
#define ATOM_DP_SS_ID1                                     0x0f1         // SS ID fow intewnaw DP stweam at 2.7Ghz. if ATOM_DP_SS_ID2 does not exist in SS_InfoTabwe, it is used fow intewnaw DP stweam at 1.62Ghz as weww.
#define ATOM_DP_SS_ID2                                     0x0f2         // SS ID fow intewnaw DP stweam at 1.62Ghz, if it exists in SS_InfoTabwe.
#define ATOM_WVWINK_2700MHz_SS_ID              0x0f3      // SS ID fow WV wink twanswatow chip at 2.7Ghz
#define ATOM_WVWINK_1620MHz_SS_ID              0x0f4      // SS ID fow WV wink twanswatow chip at 1.62Ghz



#define ATOM_SS_DOWN_SPWEAD_MODE_MASK          0x00000000
#define ATOM_SS_DOWN_SPWEAD_MODE               0x00000000
#define ATOM_SS_CENTWE_SPWEAD_MODE_MASK        0x00000001
#define ATOM_SS_CENTWE_SPWEAD_MODE             0x00000001
#define ATOM_INTEWNAW_SS_MASK                  0x00000000
#define ATOM_EXTEWNAW_SS_MASK                  0x00000002
#define EXEC_SS_STEP_SIZE_SHIFT                2
#define EXEC_SS_DEWAY_SHIFT                    4
#define ACTIVEDATA_TO_BWON_DEWAY_SHIFT         4

typedef stwuct _ATOM_SPWEAD_SPECTWUM_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  ATOM_SPWEAD_SPECTWUM_ASSIGNMENT   asSS_Info[ATOM_MAX_SS_ENTWY];
}ATOM_SPWEAD_SPECTWUM_INFO;


/****************************************************************************/
// Stwuctuwe used in AnawogTV_InfoTabwe (Top wevew)
/****************************************************************************/
//ucTVBootUpDefauwtStd definiton:

//ATOM_TV_NTSC                1
//ATOM_TV_NTSCJ               2
//ATOM_TV_PAW                 3
//ATOM_TV_PAWM                4
//ATOM_TV_PAWCN               5
//ATOM_TV_PAWN                6
//ATOM_TV_PAW60               7
//ATOM_TV_SECAM               8

//ucTVSupppowtedStd definition:
#define NTSC_SUPPOWT          0x1
#define NTSCJ_SUPPOWT         0x2

#define PAW_SUPPOWT           0x4
#define PAWM_SUPPOWT          0x8
#define PAWCN_SUPPOWT         0x10
#define PAWN_SUPPOWT          0x20
#define PAW60_SUPPOWT         0x40
#define SECAM_SUPPOWT         0x80

#define MAX_SUPPOWTED_TV_TIMING    2

typedef stwuct _ATOM_ANAWOG_TV_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UCHAW                    ucTV_SupppowtedStandawd;
  UCHAW                    ucTV_BootUpDefauwtStandawd;
  UCHAW                    ucExt_TV_ASIC_ID;
  UCHAW                    ucExt_TV_ASIC_SwaveAddw;
  ATOM_DTD_FOWMAT          aModeTimings[MAX_SUPPOWTED_TV_TIMING];
}ATOM_ANAWOG_TV_INFO;

typedef stwuct _ATOM_DPCD_INFO
{
  UCHAW   ucWevisionNumbew;        //10h : Wevision 1.0; 11h : Wevision 1.1
  UCHAW   ucMaxWinkWate;           //06h : 1.62Gbps pew wane; 0Ah = 2.7Gbps pew wane
  UCHAW   ucMaxWane;               //Bits 4:0 = MAX_WANE_COUNT (1/2/4). Bit 7 = ENHANCED_FWAME_CAP
  UCHAW   ucMaxDownSpwead;         //Bit0 = 0: No Down spwead; Bit0 = 1: 0.5% (Subject to change accowding to DP spec)
}ATOM_DPCD_INFO;

#define ATOM_DPCD_MAX_WANE_MASK    0x1F

/**************************************************************************/
// VWAM usage and theiw defintions

// One chunk of VWAM used by Bios awe fow HWICON suwfaces,EDID data.
// Cuwwent Mode timing and Daiw Timing and/ow STD timing data EACH device. They can be bwoken down as bewow.
// Aww the addwesses bewow awe the offsets fwom the fwame buffew stawt.They aww MUST be Dwowd awigned!
// To dwivew: The physicaw addwess of this memowy powtion=mmFB_STAWT(4K awigned)+ATOMBIOS_VWAM_USAGE_STAWT_ADDW+ATOM_x_ADDW
// To Bios:  ATOMBIOS_VWAM_USAGE_STAWT_ADDW+ATOM_x_ADDW->MM_INDEX

// Moved VESA_MEMOWY_IN_64K_BWOCK definition to "AtomConfig.h" so that it can be wedefined in design (SKU).
//#ifndef VESA_MEMOWY_IN_64K_BWOCK
//#define VESA_MEMOWY_IN_64K_BWOCK        0x100       //256*64K=16Mb (Max. VESA memowy is 16Mb!)
//#endif

#define ATOM_EDID_WAW_DATASIZE          256         //In Bytes
#define ATOM_HWICON_SUWFACE_SIZE        4096        //In Bytes
#define ATOM_HWICON_INFOTABWE_SIZE      32
#define MAX_DTD_MODE_IN_VWAM            6
#define ATOM_DTD_MODE_SUPPOWT_TBW_SIZE  (MAX_DTD_MODE_IN_VWAM*28)    //28= (SIZEOF ATOM_DTD_FOWMAT)
#define ATOM_STD_MODE_SUPPOWT_TBW_SIZE  32*8                         //32 is a pwedefined numbew,8= (SIZEOF ATOM_STD_FOWMAT)
//20 bytes fow Encodew Type and DPCD in STD EDID awea
#define DFP_ENCODEW_TYPE_OFFSET         (ATOM_EDID_WAW_DATASIZE + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE + ATOM_STD_MODE_SUPPOWT_TBW_SIZE - 20)
#define ATOM_DP_DPCD_OFFSET             (DFP_ENCODEW_TYPE_OFFSET + 4 )

#define ATOM_HWICON1_SUWFACE_ADDW       0
#define ATOM_HWICON2_SUWFACE_ADDW       (ATOM_HWICON1_SUWFACE_ADDW + ATOM_HWICON_SUWFACE_SIZE)
#define ATOM_HWICON_INFOTABWE_ADDW      (ATOM_HWICON2_SUWFACE_ADDW + ATOM_HWICON_SUWFACE_SIZE)
#define ATOM_CWT1_EDID_ADDW             (ATOM_HWICON_INFOTABWE_ADDW + ATOM_HWICON_INFOTABWE_SIZE)
#define ATOM_CWT1_DTD_MODE_TBW_ADDW     (ATOM_CWT1_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_CWT1_STD_MODE_TBW_ADDW       (ATOM_CWT1_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_WCD1_EDID_ADDW             (ATOM_CWT1_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_WCD1_DTD_MODE_TBW_ADDW     (ATOM_WCD1_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_WCD1_STD_MODE_TBW_ADDW      (ATOM_WCD1_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_TV1_DTD_MODE_TBW_ADDW      (ATOM_WCD1_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP1_EDID_ADDW             (ATOM_TV1_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP1_DTD_MODE_TBW_ADDW     (ATOM_DFP1_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP1_STD_MODE_TBW_ADDW       (ATOM_DFP1_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_CWT2_EDID_ADDW             (ATOM_DFP1_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_CWT2_DTD_MODE_TBW_ADDW     (ATOM_CWT2_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_CWT2_STD_MODE_TBW_ADDW       (ATOM_CWT2_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_WCD2_EDID_ADDW             (ATOM_CWT2_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_WCD2_DTD_MODE_TBW_ADDW     (ATOM_WCD2_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_WCD2_STD_MODE_TBW_ADDW      (ATOM_WCD2_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP6_EDID_ADDW             (ATOM_WCD2_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP6_DTD_MODE_TBW_ADDW     (ATOM_DFP6_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP6_STD_MODE_TBW_ADDW     (ATOM_DFP6_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP2_EDID_ADDW             (ATOM_DFP6_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP2_DTD_MODE_TBW_ADDW     (ATOM_DFP2_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP2_STD_MODE_TBW_ADDW     (ATOM_DFP2_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_CV_EDID_ADDW               (ATOM_DFP2_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_CV_DTD_MODE_TBW_ADDW       (ATOM_CV_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_CV_STD_MODE_TBW_ADDW       (ATOM_CV_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP3_EDID_ADDW             (ATOM_CV_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP3_DTD_MODE_TBW_ADDW     (ATOM_DFP3_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP3_STD_MODE_TBW_ADDW     (ATOM_DFP3_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP4_EDID_ADDW             (ATOM_DFP3_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP4_DTD_MODE_TBW_ADDW     (ATOM_DFP4_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP4_STD_MODE_TBW_ADDW     (ATOM_DFP4_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DFP5_EDID_ADDW             (ATOM_DFP4_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)
#define ATOM_DFP5_DTD_MODE_TBW_ADDW     (ATOM_DFP5_EDID_ADDW + ATOM_EDID_WAW_DATASIZE)
#define ATOM_DFP5_STD_MODE_TBW_ADDW     (ATOM_DFP5_DTD_MODE_TBW_ADDW + ATOM_DTD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_DP_TWAINING_TBW_ADDW       (ATOM_DFP5_STD_MODE_TBW_ADDW + ATOM_STD_MODE_SUPPOWT_TBW_SIZE)

#define ATOM_STACK_STOWAGE_STAWT        (ATOM_DP_TWAINING_TBW_ADDW + 1024)
#define ATOM_STACK_STOWAGE_END          ATOM_STACK_STOWAGE_STAWT + 512

//The size bewow is in Kb!
#define ATOM_VWAM_WESEWVE_SIZE         ((((ATOM_STACK_STOWAGE_END - ATOM_HWICON1_SUWFACE_ADDW)>>10)+4)&0xFFFC)

#define ATOM_VWAM_WESEWVE_V2_SIZE      32

#define   ATOM_VWAM_OPEWATION_FWAGS_MASK         0xC0000000W
#define ATOM_VWAM_OPEWATION_FWAGS_SHIFT        30
#define   ATOM_VWAM_BWOCK_NEEDS_NO_WESEWVATION   0x1
#define   ATOM_VWAM_BWOCK_NEEDS_WESEWVATION      0x0
#define   ATOM_VWAM_BWOCK_SWIOV_MSG_SHAWE_WESEWVATION 0x2

/***********************************************************************************/
// Stwuctuwe used in VWAM_UsageByFiwmwaweTabwe
// Note1: This tabwe is fiwwed by SetBiosWesewvationStawtInFB in CoweCommSubs.asm
//        at wunning time.
// note2: Fwom WV770, the memowy is mowe than 32bit addwessabwe, so we wiww change
//        ucTabweFowmatWevision=1,ucTabweContentWevision=4, the stwcutuwe wemains
//        exactwy same as 1.1 and 1.2 (1.3 is nevew in use), but uwStawtAddwUsedByFiwmwawe
//        (in offset to stawt of memowy addwess) is KB awigned instead of byte awigend.
// Note3:
/* If we change usWesewved to "usFBUsedbyDwvInKB", then to VBIOS this usFBUsedbyDwvInKB is a pwedefined, unchanged
constant acwoss VGA ow non VGA adaptew,
fow CAIW, The size of FB access awea is known, onwy thing missing is the Offset of FB Access awea, so we can  have:

If (uwStawtAddwUsedByFiwmwawe!=0)
FBAccessAweaOffset= uwStawtAddwUsedByFiwmwawe - usFBUsedbyDwvInKB;
Wesewved awea has been cwaimed by VBIOS incwuding this FB access awea; CAIW doesn't need to wesewve any extwa awea fow this puwpose
ewse   //Non VGA case
 if (FB_Size<=2Gb)
    FBAccessAweaOffset= FB_Size - usFBUsedbyDwvInKB;
 ewse
     FBAccessAweaOffset= Apew_Size - usFBUsedbyDwvInKB

CAIW needs to cwaim an wesewved awea defined by FBAccessAweaOffset and usFBUsedbyDwvInKB in non VGA case.*/

/***********************************************************************************/
#define ATOM_MAX_FIWMWAWE_VWAM_USAGE_INFO         1

typedef stwuct _ATOM_FIWMWAWE_VWAM_WESEWVE_INFO
{
  UWONG   uwStawtAddwUsedByFiwmwawe;
  USHOWT  usFiwmwaweUseInKb;
  USHOWT  usWesewved;
}ATOM_FIWMWAWE_VWAM_WESEWVE_INFO;

typedef stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_FIWMWAWE_VWAM_WESEWVE_INFO   asFiwmwaweVwamWesewveInfo[ATOM_MAX_FIWMWAWE_VWAM_USAGE_INFO];
}ATOM_VWAM_USAGE_BY_FIWMWAWE;

// change vewion to 1.5, when awwow dwivew to awwocate the vwam awea fow command tabwe access.
typedef stwuct _ATOM_FIWMWAWE_VWAM_WESEWVE_INFO_V1_5
{
  UWONG   uwStawtAddwUsedByFiwmwawe;
  USHOWT  usFiwmwaweUseInKb;
  USHOWT  usFBUsedByDwvInKb;
}ATOM_FIWMWAWE_VWAM_WESEWVE_INFO_V1_5;

typedef stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE_V1_5
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_FIWMWAWE_VWAM_WESEWVE_INFO_V1_5   asFiwmwaweVwamWesewveInfo[ATOM_MAX_FIWMWAWE_VWAM_USAGE_INFO];
}ATOM_VWAM_USAGE_BY_FIWMWAWE_V1_5;

/****************************************************************************/
// Stwuctuwe used in GPIO_Pin_WUTTabwe
/****************************************************************************/
typedef stwuct _ATOM_GPIO_PIN_ASSIGNMENT
{
  USHOWT                   usGpioPin_AIndex;
  UCHAW                    ucGpioPinBitShift;
  UCHAW                    ucGPIO_ID;
}ATOM_GPIO_PIN_ASSIGNMENT;

//ucGPIO_ID pwe-define id fow muwtipwe usage
// GPIO use to contwow PCIE_VDDC in cewtain SWT boawd
#define PCIE_VDDC_CONTWOW_GPIO_PINID        56

//fwom SMU7.x, if ucGPIO_ID=PP_AC_DC_SWITCH_GPIO_PINID in GPIO_WUTTabwe, AC/DC switching featuwe is enabwe
#define PP_AC_DC_SWITCH_GPIO_PINID          60
//fwom SMU7.x, if ucGPIO_ID=VDDC_WEGUWATOW_VWHOT_GPIO_PINID in GPIO_WUTabwe, VWHot featuwe is enabwe
#define VDDC_VWHOT_GPIO_PINID               61
//if ucGPIO_ID=VDDC_PCC_GPIO_PINID in GPIO_WUTabwe, Peak Cuwwent Contwow featuwe is enabwed
#define VDDC_PCC_GPIO_PINID                 62
// Onwy used on cewtain SWT/PA boawd to awwow utiwity to cut Efuse.
#define EFUSE_CUT_ENABWE_GPIO_PINID         63
// ucGPIO=DWAM_SEWF_WEFWESH_GPIO_PIND uses  fow memowy sewf wefwesh (ucGPIO=0, DWAM sewf-wefwesh; ucGPIO=
#define DWAM_SEWF_WEFWESH_GPIO_PINID        64
// Thewmaw intewwupt output->system thewmaw chip GPIO pin
#define THEWMAW_INT_OUTPUT_GPIO_PINID       65


typedef stwuct _ATOM_GPIO_PIN_WUT
{
  ATOM_COMMON_TABWE_HEADEW  sHeadew;
  ATOM_GPIO_PIN_ASSIGNMENT   asGPIO_Pin[];
}ATOM_GPIO_PIN_WUT;

/****************************************************************************/
// Stwuctuwe used in ComponentVideoInfoTabwe
/****************************************************************************/
#define GPIO_PIN_ACTIVE_HIGH          0x1
#define MAX_SUPPOWTED_CV_STANDAWDS    5

// definitions fow ATOM_D_INFO.ucSettings
#define ATOM_GPIO_SETTINGS_BITSHIFT_MASK  0x1F    // [4:0]
#define ATOM_GPIO_SETTINGS_WESEWVED_MASK  0x60    // [6:5] = must be zewoed out
#define ATOM_GPIO_SETTINGS_ACTIVE_MASK    0x80    // [7]

typedef stwuct _ATOM_GPIO_INFO
{
  USHOWT  usAOffset;
  UCHAW   ucSettings;
  UCHAW   ucWesewved;
}ATOM_GPIO_INFO;

// definitions fow ATOM_COMPONENT_VIDEO_INFO.ucMiscInfo (bit vectow)
#define ATOM_CV_WESTWICT_FOWMAT_SEWECTION           0x2

// definitions fow ATOM_COMPONENT_VIDEO_INFO.uc480i/uc480p/uc720p/uc1080i
#define ATOM_GPIO_DEFAUWT_MODE_EN                   0x80 //[7];
#define ATOM_GPIO_SETTING_PEWMODE_MASK              0x7F //[6:0]

// definitions fow ATOM_COMPONENT_VIDEO_INFO.ucWettewBoxMode
//Wine 3 out put 5V.
#define ATOM_CV_WINE3_ASPECTWATIO_16_9_GPIO_A       0x01     //wepwesent gpio 3 state fow 16:9
#define ATOM_CV_WINE3_ASPECTWATIO_16_9_GPIO_B       0x02     //wepwesent gpio 4 state fow 16:9
#define ATOM_CV_WINE3_ASPECTWATIO_16_9_GPIO_SHIFT   0x0

//Wine 3 out put 2.2V
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_WETBOX_GPIO_A 0x04     //wepwesent gpio 3 state fow 4:3 Wettew box
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_WETBOX_GPIO_B 0x08     //wepwesent gpio 4 state fow 4:3 Wettew box
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_WETBOX_GPIO_SHIFT 0x2

//Wine 3 out put 0V
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_GPIO_A        0x10     //wepwesent gpio 3 state fow 4:3
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_GPIO_B        0x20     //wepwesent gpio 4 state fow 4:3
#define ATOM_CV_WINE3_ASPECTWATIO_4_3_GPIO_SHIFT    0x4

#define ATOM_CV_WINE3_ASPECTWATIO_MASK              0x3F     // bit [5:0]

#define ATOM_CV_WINE3_ASPECTWATIO_EXIST             0x80     //bit 7

//GPIO bit index in gpio setting pew mode vawue, awso wepwesend the bwock no. in gpio bwocks.
#define ATOM_GPIO_INDEX_WINE3_ASPECWATIO_GPIO_A   3   //bit 3 in uc480i/uc480p/uc720p/uc1080i, which wepwesend the defauwt gpio bit setting fow the mode.
#define ATOM_GPIO_INDEX_WINE3_ASPECWATIO_GPIO_B   4   //bit 4 in uc480i/uc480p/uc720p/uc1080i, which wepwesend the defauwt gpio bit setting fow the mode.


typedef stwuct _ATOM_COMPONENT_VIDEO_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT             usMask_PinWegistewIndex;
  USHOWT             usEN_PinWegistewIndex;
  USHOWT             usY_PinWegistewIndex;
  USHOWT             usA_PinWegistewIndex;
  UCHAW              ucBitShift;
  UCHAW              ucPinActiveState;  //ucPinActiveState: Bit0=1 active high, =0 active wow
  ATOM_DTD_FOWMAT    sWesewved;         // must be zewoed out
  UCHAW              ucMiscInfo;
  UCHAW              uc480i;
  UCHAW              uc480p;
  UCHAW              uc720p;
  UCHAW              uc1080i;
  UCHAW              ucWettewBoxMode;
  UCHAW              ucWesewved[3];
  UCHAW              ucNumOfWbGpioBwocks; //Fow Component video D-Connectow suppowt. If zewe, NTSC type connectow
  ATOM_GPIO_INFO     aWbGpioStateBwock[MAX_SUPPOWTED_CV_STANDAWDS];
  ATOM_DTD_FOWMAT    aModeTimings[MAX_SUPPOWTED_CV_STANDAWDS];
}ATOM_COMPONENT_VIDEO_INFO;

//ucTabweFowmatWevision=2
//ucTabweContentWevision=1
typedef stwuct _ATOM_COMPONENT_VIDEO_INFO_V21
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UCHAW              ucMiscInfo;
  UCHAW              uc480i;
  UCHAW              uc480p;
  UCHAW              uc720p;
  UCHAW              uc1080i;
  UCHAW              ucWesewved;
  UCHAW              ucWettewBoxMode;
  UCHAW              ucNumOfWbGpioBwocks; //Fow Component video D-Connectow suppowt. If zewe, NTSC type connectow
  ATOM_GPIO_INFO     aWbGpioStateBwock[MAX_SUPPOWTED_CV_STANDAWDS];
  ATOM_DTD_FOWMAT    aModeTimings[MAX_SUPPOWTED_CV_STANDAWDS];
}ATOM_COMPONENT_VIDEO_INFO_V21;

#define ATOM_COMPONENT_VIDEO_INFO_WAST  ATOM_COMPONENT_VIDEO_INFO_V21

/****************************************************************************/
// Stwuctuwe used in object_InfoTabwe
/****************************************************************************/
typedef stwuct _ATOM_OBJECT_HEADEW
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                    usDeviceSuppowt;
  USHOWT                    usConnectowObjectTabweOffset;
  USHOWT                    usWoutewObjectTabweOffset;
  USHOWT                    usEncodewObjectTabweOffset;
  USHOWT                    usPwotectionObjectTabweOffset; //onwy avaiwabwe when Pwotection bwock is independent.
  USHOWT                    usDispwayPathTabweOffset;
}ATOM_OBJECT_HEADEW;

typedef stwuct _ATOM_OBJECT_HEADEW_V3
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                    usDeviceSuppowt;
  USHOWT                    usConnectowObjectTabweOffset;
  USHOWT                    usWoutewObjectTabweOffset;
  USHOWT                    usEncodewObjectTabweOffset;
  USHOWT                    usPwotectionObjectTabweOffset; //onwy avaiwabwe when Pwotection bwock is independent.
  USHOWT                    usDispwayPathTabweOffset;
  USHOWT                    usMiscObjectTabweOffset;
}ATOM_OBJECT_HEADEW_V3;


typedef stwuct  _ATOM_DISPWAY_OBJECT_PATH
{
  USHOWT    usDeviceTag;                                   //suppowted device
  USHOWT    usSize;                                        //the size of ATOM_DISPWAY_OBJECT_PATH
  USHOWT    usConnObjectId;                                //Connectow Object ID
  USHOWT    usGPUObjectId;                                 //GPU ID
  USHOWT    usGwaphicObjIds[];                            //1st Encodew Obj souwce fwom GPU to wast Gwaphic Obj destinate to connectow.
}ATOM_DISPWAY_OBJECT_PATH;

typedef stwuct  _ATOM_DISPWAY_EXTEWNAW_OBJECT_PATH
{
  USHOWT    usDeviceTag;                                   //suppowted device
  USHOWT    usSize;                                        //the size of ATOM_DISPWAY_OBJECT_PATH
  USHOWT    usConnObjectId;                                //Connectow Object ID
  USHOWT    usGPUObjectId;                                 //GPU ID
  USHOWT    usGwaphicObjIds[2];                            //usGwaphicObjIds[0]= GPU intewnaw encodew, usGwaphicObjIds[1]= extewnaw encodew
}ATOM_DISPWAY_EXTEWNAW_OBJECT_PATH;

typedef stwuct _ATOM_DISPWAY_OBJECT_PATH_TABWE
{
  UCHAW                           ucNumOfDispPath;
  UCHAW                           ucVewsion;
  UCHAW                           ucPadding[2];
  ATOM_DISPWAY_OBJECT_PATH        asDispPath[];
}ATOM_DISPWAY_OBJECT_PATH_TABWE;

typedef stwuct _ATOM_OBJECT                                //each object has this stwuctuwe
{
  USHOWT              usObjectID;
  USHOWT              usSwcDstTabweOffset;
  USHOWT              usWecowdOffset;                     //this pointing to a bunch of wecowds defined bewow
  USHOWT              usWesewved;
}ATOM_OBJECT;

typedef stwuct _ATOM_OBJECT_TABWE                         //Above 4 object tabwe offset pointing to a bunch of objects aww have this stwuctuwe
{
  UCHAW               ucNumbewOfObjects;
  UCHAW               ucPadding[3];
  ATOM_OBJECT         asObjects[];
}ATOM_OBJECT_TABWE;

typedef stwuct _ATOM_SWC_DST_TABWE_FOW_ONE_OBJECT         //usSwcDstTabweOffset pointing to this stwuctuwe
{
  UCHAW               ucNumbewOfSwc;
  USHOWT              usSwcObjectID[1];
  UCHAW               ucNumbewOfDst;
  USHOWT              usDstObjectID[1];
}ATOM_SWC_DST_TABWE_FOW_ONE_OBJECT;


//Two definitions bewow awe fow OPM on MXM moduwe designs

#define EXT_HPDPIN_WUTINDEX_0                   0
#define EXT_HPDPIN_WUTINDEX_1                   1
#define EXT_HPDPIN_WUTINDEX_2                   2
#define EXT_HPDPIN_WUTINDEX_3                   3
#define EXT_HPDPIN_WUTINDEX_4                   4
#define EXT_HPDPIN_WUTINDEX_5                   5
#define EXT_HPDPIN_WUTINDEX_6                   6
#define EXT_HPDPIN_WUTINDEX_7                   7
#define MAX_NUMBEW_OF_EXT_HPDPIN_WUT_ENTWIES   (EXT_HPDPIN_WUTINDEX_7+1)

#define EXT_AUXDDC_WUTINDEX_0                   0
#define EXT_AUXDDC_WUTINDEX_1                   1
#define EXT_AUXDDC_WUTINDEX_2                   2
#define EXT_AUXDDC_WUTINDEX_3                   3
#define EXT_AUXDDC_WUTINDEX_4                   4
#define EXT_AUXDDC_WUTINDEX_5                   5
#define EXT_AUXDDC_WUTINDEX_6                   6
#define EXT_AUXDDC_WUTINDEX_7                   7
#define MAX_NUMBEW_OF_EXT_AUXDDC_WUT_ENTWIES   (EXT_AUXDDC_WUTINDEX_7+1)

//ucChannewMapping awe defined as fowwowing
//fow DP connectow, eDP, DP to VGA/WVDS
//Bit[1:0]: Define which pin connect to DP connectow DP_Wane0, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[3:2]: Define which pin connect to DP connectow DP_Wane1, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[5:4]: Define which pin connect to DP connectow DP_Wane2, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[7:6]: Define which pin connect to DP connectow DP_Wane3, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
typedef stwuct _ATOM_DP_CONN_CHANNEW_MAPPING
{
#if ATOM_BIG_ENDIAN
  UCHAW ucDP_Wane3_Souwce:2;
  UCHAW ucDP_Wane2_Souwce:2;
  UCHAW ucDP_Wane1_Souwce:2;
  UCHAW ucDP_Wane0_Souwce:2;
#ewse
  UCHAW ucDP_Wane0_Souwce:2;
  UCHAW ucDP_Wane1_Souwce:2;
  UCHAW ucDP_Wane2_Souwce:2;
  UCHAW ucDP_Wane3_Souwce:2;
#endif
}ATOM_DP_CONN_CHANNEW_MAPPING;

//fow DVI/HDMI, in duaw wink case, both winks have to have same mapping.
//Bit[1:0]: Define which pin connect to DVI connectow data Wane2, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[3:2]: Define which pin connect to DVI connectow data Wane1, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[5:4]: Define which pin connect to DVI connectow data Wane0, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
//Bit[7:6]: Define which pin connect to DVI connectow cwock wane, =0: souwce fwom GPU pin TX0, =1: fwom GPU pin TX1, =2: fwom GPU pin TX2, =3 fwom GPU pin TX3
typedef stwuct _ATOM_DVI_CONN_CHANNEW_MAPPING
{
#if ATOM_BIG_ENDIAN
  UCHAW ucDVI_CWK_Souwce:2;
  UCHAW ucDVI_DATA0_Souwce:2;
  UCHAW ucDVI_DATA1_Souwce:2;
  UCHAW ucDVI_DATA2_Souwce:2;
#ewse
  UCHAW ucDVI_DATA2_Souwce:2;
  UCHAW ucDVI_DATA1_Souwce:2;
  UCHAW ucDVI_DATA0_Souwce:2;
  UCHAW ucDVI_CWK_Souwce:2;
#endif
}ATOM_DVI_CONN_CHANNEW_MAPPING;

typedef stwuct _EXT_DISPWAY_PATH
{
  USHOWT  usDeviceTag;                    //A bit vectow to show what devices awe suppowted
  USHOWT  usDeviceACPIEnum;               //16bit device ACPI id.
  USHOWT  usDeviceConnectow;              //A physicaw connectow fow dispways to pwug in, using object connectow definitions
  UCHAW   ucExtAUXDDCWutIndex;            //An index into extewnaw AUX/DDC channew WUT
  UCHAW   ucExtHPDPINWutIndex;            //An index into extewnaw HPD pin WUT
  USHOWT  usExtEncodewObjId;              //extewnaw encodew object id
  union{
    UCHAW   ucChannewMapping;                  // if ucChannewMapping=0, using defauwt one to one mapping
    ATOM_DP_CONN_CHANNEW_MAPPING asDPMapping;
    ATOM_DVI_CONN_CHANNEW_MAPPING asDVIMapping;
  };
  UCHAW   ucChPNInvewt;                   // bit vectow fow up to 8 wanes, =0: P and N is not invewt, =1 P and N is invewted
  USHOWT  usCaps;
  USHOWT  usWesewved;
}EXT_DISPWAY_PATH;

#define NUMBEW_OF_UCHAW_FOW_GUID          16
#define MAX_NUMBEW_OF_EXT_DISPWAY_PATH    7

//usCaps
#define  EXT_DISPWAY_PATH_CAPS__HBW2_DISABWE               0x0001
#define  EXT_DISPWAY_PATH_CAPS__DP_FIXED_VS_EN             0x0002
#define  EXT_DISPWAY_PATH_CAPS__EXT_CHIP_MASK              0x007C
#define  EXT_DISPWAY_PATH_CAPS__HDMI20_PI3EQX1204          (0x01 << 2 )     //PI wedwivew chip
#define  EXT_DISPWAY_PATH_CAPS__HDMI20_TISN65DP159WSBT     (0x02 << 2 )     //TI wetimew chip
#define  EXT_DISPWAY_PATH_CAPS__HDMI20_PAWADE_PS175        (0x03 << 2 )     //Pawade DP->HDMI wecovewtew chip




typedef  stwuct _ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UCHAW                    ucGuid [NUMBEW_OF_UCHAW_FOW_GUID];     // a GUID is a 16 byte wong stwing
  EXT_DISPWAY_PATH         sPath[MAX_NUMBEW_OF_EXT_DISPWAY_PATH]; // totaw of fixed 7 entwies.
  UCHAW                    ucChecksum;                            // a simpwe Checksum of the sum of whowe stwuctuwe equaw to 0x0.
  UCHAW                    uc3DSteweoPinId;                       // use fow eDP panew
  UCHAW                    ucWemoteDispwayConfig;
  UCHAW                    uceDPToWVDSWxId;
  UCHAW                    ucFixDPVowtageSwing;                   // usCaps[1]=1, this indicate DP_WANE_SET vawue
  UCHAW                    Wesewved[3];                           // fow potentiaw expansion
}ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO;

//Wewated definitions, aww wecowds awe diffewent but they have a common headew
typedef stwuct _ATOM_COMMON_WECOWD_HEADEW
{
  UCHAW               ucWecowdType;                      //An emun to indicate the wecowd type
  UCHAW               ucWecowdSize;                      //The size of the whowe wecowd in byte
}ATOM_COMMON_WECOWD_HEADEW;


#define ATOM_I2C_WECOWD_TYPE                           1
#define ATOM_HPD_INT_WECOWD_TYPE                       2
#define ATOM_OUTPUT_PWOTECTION_WECOWD_TYPE             3
#define ATOM_CONNECTOW_DEVICE_TAG_WECOWD_TYPE          4
#define ATOM_CONNECTOW_DVI_EXT_INPUT_WECOWD_TYPE       5 //Obsowete, switch to use GPIO_CNTW_WECOWD_TYPE
#define ATOM_ENCODEW_FPGA_CONTWOW_WECOWD_TYPE          6 //Obsowete, switch to use GPIO_CNTW_WECOWD_TYPE
#define ATOM_CONNECTOW_CVTV_SHAWE_DIN_WECOWD_TYPE      7
#define ATOM_JTAG_WECOWD_TYPE                          8 //Obsowete, switch to use GPIO_CNTW_WECOWD_TYPE
#define ATOM_OBJECT_GPIO_CNTW_WECOWD_TYPE              9
#define ATOM_ENCODEW_DVO_CF_WECOWD_TYPE                10
#define ATOM_CONNECTOW_CF_WECOWD_TYPE                  11
#define ATOM_CONNECTOW_HAWDCODE_DTD_WECOWD_TYPE        12
#define ATOM_CONNECTOW_PCIE_SUBCONNECTOW_WECOWD_TYPE   13
#define ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD_TYPE        14
#define ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD_TYPE 15
#define ATOM_CONNECTOW_HPDPIN_WUT_WECOWD_TYPE          16 //This is fow the case when connectows awe not known to object tabwe
#define ATOM_CONNECTOW_AUXDDC_WUT_WECOWD_TYPE          17 //This is fow the case when connectows awe not known to object tabwe
#define ATOM_OBJECT_WINK_WECOWD_TYPE                   18 //Once this wecowd is pwesent undew one object, it indicats the oobject is winked to anothew obj descwibed by the wecowd
#define ATOM_CONNECTOW_WEMOTE_CAP_WECOWD_TYPE          19
#define ATOM_ENCODEW_CAP_WECOWD_TYPE                   20
#define ATOM_BWACKET_WAYOUT_WECOWD_TYPE                21
#define ATOM_CONNECTOW_FOWCED_TMDS_CAP_WECOWD_TYPE     22

//Must be updated when new wecowd type is added,equaw to that wecowd definition!
#define ATOM_MAX_OBJECT_WECOWD_NUMBEW                  ATOM_CONNECTOW_FOWCED_TMDS_CAP_WECOWD_TYPE

typedef stwuct  _ATOM_I2C_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  ATOM_I2C_ID_CONFIG          sucI2cId;
  UCHAW                       ucI2CAddw;              //The swave addwess, it's 0 when the wecowd is attached to connectow fow DDC
}ATOM_I2C_WECOWD;

typedef stwuct  _ATOM_HPD_INT_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucHPDIntGPIOID;         //Cowwesponding bwock in GPIO_PIN_INFO tabwe gives the pin info
  UCHAW                       ucPwugged_PinState;
}ATOM_HPD_INT_WECOWD;


typedef stwuct  _ATOM_OUTPUT_PWOTECTION_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucPwotectionFwag;
  UCHAW                       ucWesewved;
}ATOM_OUTPUT_PWOTECTION_WECOWD;

typedef stwuct  _ATOM_CONNECTOW_DEVICE_TAG
{
  UWONG                       uwACPIDeviceEnum;       //Wesewved fow now
  USHOWT                      usDeviceID;             //This Id is same as "ATOM_DEVICE_XXX_SUPPOWT"
  USHOWT                      usPadding;
}ATOM_CONNECTOW_DEVICE_TAG;

typedef stwuct  _ATOM_CONNECTOW_DEVICE_TAG_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucNumbewOfDevice;
  UCHAW                       ucWesewved;
  ATOM_CONNECTOW_DEVICE_TAG   asDeviceTag[];	       //This Id is same as "ATOM_DEVICE_XXX_SUPPOWT"
}ATOM_CONNECTOW_DEVICE_TAG_WECOWD;


typedef stwuct  _ATOM_CONNECTOW_DVI_EXT_INPUT_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                              ucConfigGPIOID;
  UCHAW                              ucConfigGPIOState;       //Set to 1 when it's active high to enabwe extewnaw fwow in
  UCHAW                       ucFwowinGPIPID;
  UCHAW                       ucExtInGPIPID;
}ATOM_CONNECTOW_DVI_EXT_INPUT_WECOWD;

typedef stwuct  _ATOM_ENCODEW_FPGA_CONTWOW_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucCTW1GPIO_ID;
  UCHAW                       ucCTW1GPIOState;        //Set to 1 when it's active high
  UCHAW                       ucCTW2GPIO_ID;
  UCHAW                       ucCTW2GPIOState;        //Set to 1 when it's active high
  UCHAW                       ucCTW3GPIO_ID;
  UCHAW                       ucCTW3GPIOState;        //Set to 1 when it's active high
  UCHAW                       ucCTWFPGA_IN_ID;
  UCHAW                       ucPadding[3];
}ATOM_ENCODEW_FPGA_CONTWOW_WECOWD;

typedef stwuct  _ATOM_CONNECTOW_CVTV_SHAWE_DIN_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucGPIOID;               //Cowwesponding bwock in GPIO_PIN_INFO tabwe gives the pin info
  UCHAW                       ucTVActiveState;        //Indicating when the pin==0 ow 1 when TV is connected
}ATOM_CONNECTOW_CVTV_SHAWE_DIN_WECOWD;

typedef stwuct  _ATOM_JTAG_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucTMSGPIO_ID;
  UCHAW                       ucTMSGPIOState;         //Set to 1 when it's active high
  UCHAW                       ucTCKGPIO_ID;
  UCHAW                       ucTCKGPIOState;         //Set to 1 when it's active high
  UCHAW                       ucTDOGPIO_ID;
  UCHAW                       ucTDOGPIOState;         //Set to 1 when it's active high
  UCHAW                       ucTDIGPIO_ID;
  UCHAW                       ucTDIGPIOState;         //Set to 1 when it's active high
  UCHAW                       ucPadding[2];
}ATOM_JTAG_WECOWD;


//The fowwowing genewic object gpio pin contwow wecowd type wiww wepwace JTAG_WECOWD/FPGA_CONTWOW_WECOWD/DVI_EXT_INPUT_WECOWD above gwaduawwy
typedef stwuct _ATOM_GPIO_PIN_CONTWOW_PAIW
{
  UCHAW                       ucGPIOID;               // GPIO_ID, find the cowwesponding ID in GPIO_WUT tabwe
  UCHAW                       ucGPIO_PinState;        // Pin state showing how to set-up the pin
}ATOM_GPIO_PIN_CONTWOW_PAIW;

typedef stwuct  _ATOM_OBJECT_GPIO_CNTW_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucFwags;                // Futuwe expnadibiwity
  UCHAW                       ucNumbewOfPins;         // Numbew of GPIO pins used to contwow the object
  ATOM_GPIO_PIN_CONTWOW_PAIW  asGpio[];               // the weaw gpio pin paiw detewmined by numbew of pins ucNumbewOfPins
}ATOM_OBJECT_GPIO_CNTW_WECOWD;

//Definitions fow GPIO pin state
#define GPIO_PIN_TYPE_INPUT             0x00
#define GPIO_PIN_TYPE_OUTPUT            0x10
#define GPIO_PIN_TYPE_HW_CONTWOW        0x20

//Fow GPIO_PIN_TYPE_OUTPUT the fowwowing is defined
#define GPIO_PIN_OUTPUT_STATE_MASK      0x01
#define GPIO_PIN_OUTPUT_STATE_SHIFT     0
#define GPIO_PIN_STATE_ACTIVE_WOW       0x0
#define GPIO_PIN_STATE_ACTIVE_HIGH      0x1

// Indexes to GPIO awway in GWSync wecowd
// GWSync wecowd is fow Fwame Wock/Gen Wock featuwe.
#define ATOM_GPIO_INDEX_GWSYNC_WEFCWK    0
#define ATOM_GPIO_INDEX_GWSYNC_HSYNC     1
#define ATOM_GPIO_INDEX_GWSYNC_VSYNC     2
#define ATOM_GPIO_INDEX_GWSYNC_SWAP_WEQ  3
#define ATOM_GPIO_INDEX_GWSYNC_SWAP_GNT  4
#define ATOM_GPIO_INDEX_GWSYNC_INTEWWUPT 5
#define ATOM_GPIO_INDEX_GWSYNC_V_WESET   6
#define ATOM_GPIO_INDEX_GWSYNC_SWAP_CNTW 7
#define ATOM_GPIO_INDEX_GWSYNC_SWAP_SEW  8
#define ATOM_GPIO_INDEX_GWSYNC_MAX       9

typedef stwuct  _ATOM_ENCODEW_DVO_CF_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UWONG                       uwStwengthContwow;      // DVOA stwength contwow fow CF
  UCHAW                       ucPadding[2];
}ATOM_ENCODEW_DVO_CF_WECOWD;

// Bit maps fow ATOM_ENCODEW_CAP_WECOWD.usEncodewCap
#define ATOM_ENCODEW_CAP_WECOWD_HBW2                  0x01         // DP1.2 HBW2 is suppowted by HW encodew, it is wetiwed in NI. the weaw meaning fwom SI is MST_EN
#define ATOM_ENCODEW_CAP_WECOWD_MST_EN                0x01         // fwom SI, this bit means DP MST is enabwe ow not.
#define ATOM_ENCODEW_CAP_WECOWD_HBW2_EN               0x02         // DP1.2 HBW2 setting is quawified and HBW2 can be enabwed
#define ATOM_ENCODEW_CAP_WECOWD_HDMI6Gbps_EN          0x04         // HDMI2.0 6Gbps enabwe ow not.
#define ATOM_ENCODEW_CAP_WECOWD_HBW3_EN               0x08         // DP1.3 HBW3 is suppowted by boawd.

typedef stwuct  _ATOM_ENCODEW_CAP_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  union {
    USHOWT                    usEncodewCap;
    stwuct {
#if ATOM_BIG_ENDIAN
      USHOWT                  usWesewved:14;        // Bit1-15 may be defined fow othew capabiwity in futuwe
      USHOWT                  usHBW2En:1;           // Bit1 is fow DP1.2 HBW2 enabwe
      USHOWT                  usHBW2Cap:1;          // Bit0 is fow DP1.2 HBW2 capabiwity.
#ewse
      USHOWT                  usHBW2Cap:1;          // Bit0 is fow DP1.2 HBW2 capabiwity.
      USHOWT                  usHBW2En:1;           // Bit1 is fow DP1.2 HBW2 enabwe
      USHOWT                  usWesewved:14;        // Bit1-15 may be defined fow othew capabiwity in futuwe
#endif
    };
  };
}ATOM_ENCODEW_CAP_WECOWD;

// Used aftew SI
typedef stwuct  _ATOM_ENCODEW_CAP_WECOWD_V2
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  union {
    USHOWT                    usEncodewCap;
    stwuct {
#if ATOM_BIG_ENDIAN
      USHOWT                  usWesewved:12;        // Bit4-15 may be defined fow othew capabiwity in futuwe
      USHOWT                  usHBW3En:1;           // bit3 is fow DP1.3 HBW3 enabwe
      USHOWT                  usHDMI6GEn:1;         // Bit2 is fow HDMI6Gbps enabwe, this bit is used stawting fwom CZ( APU) Ewwemewe (dGPU)
      USHOWT                  usHBW2En:1;           // Bit1 is fow DP1.2 HBW2 enabwe
      USHOWT                  usMSTEn:1;            // Bit0 is fow DP1.2 MST enabwe
#ewse
      USHOWT                  usMSTEn:1;            // Bit0 is fow DP1.2 MST enabwe
      USHOWT                  usHBW2En:1;           // Bit1 is fow DP1.2 HBW2 enabwe
      USHOWT                  usHDMI6GEn:1;         // Bit2 is fow HDMI6Gbps enabwe, this bit is used stawting fwom CZ( APU) Ewwemewe (dGPU)
      USHOWT                  usHBW3En:1;           // bit3 is fow DP1.3 HBW3 enabwe
      USHOWT                  usWesewved:12;        // Bit4-15 may be defined fow othew capabiwity in futuwe
#endif
    };
  };
}ATOM_ENCODEW_CAP_WECOWD_V2;


// vawue fow ATOM_CONNECTOW_CF_WECOWD.ucConnectedDvoBundwe
#define ATOM_CONNECTOW_CF_WECOWD_CONNECTED_UPPEW12BITBUNDWEA   1
#define ATOM_CONNECTOW_CF_WECOWD_CONNECTED_WOWEW12BITBUNDWEB   2

typedef stwuct  _ATOM_CONNECTOW_CF_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  USHOWT                      usMaxPixCwk;
  UCHAW                       ucFwowCntwGpioId;
  UCHAW                       ucSwapCntwGpioId;
  UCHAW                       ucConnectedDvoBundwe;
  UCHAW                       ucPadding;
}ATOM_CONNECTOW_CF_WECOWD;

typedef stwuct  _ATOM_CONNECTOW_HAWDCODE_DTD_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
   ATOM_DTD_FOWMAT                     asTiming;
}ATOM_CONNECTOW_HAWDCODE_DTD_WECOWD;

typedef stwuct _ATOM_CONNECTOW_PCIE_SUBCONNECTOW_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;                //ATOM_CONNECTOW_PCIE_SUBCONNECTOW_WECOWD_TYPE
  UCHAW                       ucSubConnectowType;     //CONNECTOW_OBJECT_ID_SINGWE_WINK_DVI_D|X_ID_DUAW_WINK_DVI_D|HDMI_TYPE_A
  UCHAW                       ucWesewved;
}ATOM_CONNECTOW_PCIE_SUBCONNECTOW_WECOWD;


typedef stwuct _ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD
{
   ATOM_COMMON_WECOWD_HEADEW   sheadew;
   UCHAW                                    ucMuxType;                     //decide the numbew of ucMuxState, =0, no pin state, =1: singwe state with compwement, >1: muwtipwe state
   UCHAW                                    ucMuxContwowPin;
   UCHAW                                    ucMuxState[2];               //fow awwigment puwpose
}ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD;

typedef stwuct _ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD
{
   ATOM_COMMON_WECOWD_HEADEW   sheadew;
   UCHAW                                    ucMuxType;
   UCHAW                                    ucMuxContwowPin;
   UCHAW                                    ucMuxState[2];               //fow awwigment puwpose
}ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD;

// define ucMuxType
#define ATOM_WOUTEW_MUX_PIN_STATE_MASK                        0x0f
#define ATOM_WOUTEW_MUX_PIN_SINGWE_STATE_COMPWEMENT      0x01

typedef stwuct _ATOM_CONNECTOW_HPDPIN_WUT_WECOWD     //wecowd fow ATOM_CONNECTOW_HPDPIN_WUT_WECOWD_TYPE
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucHPDPINMap[MAX_NUMBEW_OF_EXT_HPDPIN_WUT_ENTWIES];  //An fixed size awway which maps extewnaw pins to intewnaw GPIO_PIN_INFO tabwe
}ATOM_CONNECTOW_HPDPIN_WUT_WECOWD;

typedef stwuct _ATOM_CONNECTOW_AUXDDC_WUT_WECOWD  //wecowd fow ATOM_CONNECTOW_AUXDDC_WUT_WECOWD_TYPE
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  ATOM_I2C_ID_CONFIG          ucAUXDDCMap[MAX_NUMBEW_OF_EXT_AUXDDC_WUT_ENTWIES];  //An fixed size awway which maps extewnaw pins to intewnaw DDC ID
}ATOM_CONNECTOW_AUXDDC_WUT_WECOWD;

typedef stwuct _ATOM_OBJECT_WINK_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  USHOWT                      usObjectID;         //couwd be connectow, encowdew ow othew object in object.h
}ATOM_OBJECT_WINK_WECOWD;

typedef stwuct _ATOM_CONNECTOW_WEMOTE_CAP_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  USHOWT                      usWesewved;
}ATOM_CONNECTOW_WEMOTE_CAP_WECOWD;


typedef stwuct  _ATOM_CONNECTOW_FOWCED_TMDS_CAP_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  // ovewwide TMDS capabiwity on this connectow when it opewate in TMDS mode.  usMaxTmdsCwkWate = max TMDS Cwock in Mhz/2.5
  UCHAW                       ucMaxTmdsCwkWateIn2_5Mhz;
  UCHAW                       ucWesewved;
} ATOM_CONNECTOW_FOWCED_TMDS_CAP_WECOWD;


typedef stwuct  _ATOM_CONNECTOW_WAYOUT_INFO
{
   USHOWT usConnectowObjectId;
   UCHAW  ucConnectowType;
   UCHAW  ucPosition;
}ATOM_CONNECTOW_WAYOUT_INFO;

// define ATOM_CONNECTOW_WAYOUT_INFO.ucConnectowType to descwibe the dispway connectow size
#define CONNECTOW_TYPE_DVI_D                 1
#define CONNECTOW_TYPE_DVI_I                 2
#define CONNECTOW_TYPE_VGA                   3
#define CONNECTOW_TYPE_HDMI                  4
#define CONNECTOW_TYPE_DISPWAY_POWT          5
#define CONNECTOW_TYPE_MINI_DISPWAY_POWT     6

typedef stwuct  _ATOM_BWACKET_WAYOUT_WECOWD
{
  ATOM_COMMON_WECOWD_HEADEW   sheadew;
  UCHAW                       ucWength;
  UCHAW                       ucWidth;
  UCHAW                       ucConnNum;
  UCHAW                       ucWesewved;
  ATOM_CONNECTOW_WAYOUT_INFO  asConnInfo[];
}ATOM_BWACKET_WAYOUT_WECOWD;


/****************************************************************************/
// Stwuctuwe used in XXXX
/****************************************************************************/
typedef stwuct  _ATOM_VOWTAGE_INFO_HEADEW
{
   USHOWT   usVDDCBaseWevew;                //In numbew of 50mv unit
   USHOWT   usWesewved;                     //Fow possibwe extension tabwe offset
   UCHAW    ucNumOfVowtageEntwies;
   UCHAW    ucBytesPewVowtageEntwy;
   UCHAW    ucVowtageStep;                  //Indicating in how many mv incweament is one step, 0.5mv unit
   UCHAW    ucDefauwtVowtageEntwy;
   UCHAW    ucVowtageContwowI2cWine;
   UCHAW    ucVowtageContwowAddwess;
   UCHAW    ucVowtageContwowOffset;
}ATOM_VOWTAGE_INFO_HEADEW;

typedef stwuct  _ATOM_VOWTAGE_INFO
{
   ATOM_COMMON_TABWE_HEADEW   sHeadew;
   ATOM_VOWTAGE_INFO_HEADEW viHeadew;
   UCHAW    ucVowtageEntwies[64];            //64 is fow awwocation, the actuaw numbew of entwy is pwesent at ucNumOfVowtageEntwies*ucBytesPewVowtageEntwy
}ATOM_VOWTAGE_INFO;


typedef stwuct  _ATOM_VOWTAGE_FOWMUWA
{
   USHOWT   usVowtageBaseWevew;             // In numbew of 1mv unit
   USHOWT   usVowtageStep;                  // Indicating in how many mv incweament is one step, 1mv unit
   UCHAW    ucNumOfVowtageEntwies;          // Numbew of Vowtage Entwy, which indicate max Vowtage
   UCHAW    ucFwag;                         // bit0=0 :step is 1mv =1 0.5mv
   UCHAW    ucBaseVID;                      // if thewe is no wookup tabwe, VID= BaseVID + ( Vow - BaseWevwe ) /VowtageStep
   UCHAW    ucWesewved;
   UCHAW    ucVIDAdjustEntwies[32];         // 32 is fow awwocation, the actuaw numbew of entwy is pwesent at ucNumOfVowtageEntwies
}ATOM_VOWTAGE_FOWMUWA;

typedef stwuct  _VOWTAGE_WUT_ENTWY
{
    USHOWT     usVowtageCode;               // The Vowtage ID, eithew GPIO ow I2C code
    USHOWT     usVowtageVawue;              // The cowwesponding Vowtage Vawue, in mV
}VOWTAGE_WUT_ENTWY;

typedef stwuct  _ATOM_VOWTAGE_FOWMUWA_V2
{
    UCHAW      ucNumOfVowtageEntwies;               // Numbew of Vowtage Entwy, which indicate max Vowtage
    UCHAW      ucWesewved[3];
    VOWTAGE_WUT_ENTWY asVIDAdjustEntwies[32];// 32 is fow awwocation, the actuaw numbew of entwies is in ucNumOfVowtageEntwies
}ATOM_VOWTAGE_FOWMUWA_V2;

typedef stwuct _ATOM_VOWTAGE_CONTWOW
{
  UCHAW    ucVowtageContwowId;                     //Indicate it is contwowwed by I2C ow GPIO ow HW state machine
  UCHAW    ucVowtageContwowI2cWine;
  UCHAW    ucVowtageContwowAddwess;
  UCHAW    ucVowtageContwowOffset;
  USHOWT   usGpioPin_AIndex;                       //GPIO_PAD wegistew index
  UCHAW    ucGpioPinBitShift[9];                   //at most 8 pin suppowt 255 VIDs, tewmintate with 0xff
  UCHAW    ucWesewved;
}ATOM_VOWTAGE_CONTWOW;

// Define ucVowtageContwowId
#define VOWTAGE_CONTWOWWED_BY_HW              0x00
#define VOWTAGE_CONTWOWWED_BY_I2C_MASK        0x7F
#define VOWTAGE_CONTWOWWED_BY_GPIO            0x80
#define VOWTAGE_CONTWOW_ID_WM64               0x01                           //I2C contwow, used fow W5xx Cowe Vowtage
#define VOWTAGE_CONTWOW_ID_DAC                0x02                           //I2C contwow, used fow W5xx/W6xx MVDDC,MVDDQ ow VDDCI
#define VOWTAGE_CONTWOW_ID_VT116xM            0x03                           //I2C contwow, used fow W6xx Cowe Vowtage
#define VOWTAGE_CONTWOW_ID_DS4402             0x04
#define VOWTAGE_CONTWOW_ID_UP6266             0x05
#define VOWTAGE_CONTWOW_ID_SCOWPIO            0x06
#define VOWTAGE_CONTWOW_ID_VT1556M            0x07
#define VOWTAGE_CONTWOW_ID_CHW822x            0x08
#define VOWTAGE_CONTWOW_ID_VT1586M            0x09
#define VOWTAGE_CONTWOW_ID_UP1637             0x0A
#define VOWTAGE_CONTWOW_ID_CHW8214            0x0B
#define VOWTAGE_CONTWOW_ID_UP1801             0x0C
#define VOWTAGE_CONTWOW_ID_ST6788A            0x0D
#define VOWTAGE_CONTWOW_ID_CHWIW3564SVI2      0x0E
#define VOWTAGE_CONTWOW_ID_AD527x             0x0F
#define VOWTAGE_CONTWOW_ID_NCP81022           0x10
#define VOWTAGE_CONTWOW_ID_WTC2635            0x11
#define VOWTAGE_CONTWOW_ID_NCP4208            0x12
#define VOWTAGE_CONTWOW_ID_IW35xx             0x13
#define VOWTAGE_CONTWOW_ID_WT9403             0x14

#define VOWTAGE_CONTWOW_ID_GENEWIC_I2C        0x40

typedef stwuct  _ATOM_VOWTAGE_OBJECT
{
   UCHAW      ucVowtageType;                           //Indicate Vowtage Souwce: VDDC, MVDDC, MVDDQ ow MVDDCI
   UCHAW      ucSize;                                       //Size of Object
   ATOM_VOWTAGE_CONTWOW         asContwow;         //descwib how to contwow
   ATOM_VOWTAGE_FOWMUWA         asFowmuwa;         //Indicate How to convewt weaw Vowtage to VID
}ATOM_VOWTAGE_OBJECT;

typedef stwuct  _ATOM_VOWTAGE_OBJECT_V2
{
    UCHAW ucVowtageType;                      //Indicate Vowtage Souwce: VDDC, MVDDC, MVDDQ ow MVDDCI
    UCHAW ucSize;                             //Size of Object
    ATOM_VOWTAGE_CONTWOW    asContwow;        //descwib how to contwow
    ATOM_VOWTAGE_FOWMUWA_V2 asFowmuwa;        //Indicate How to convewt weaw Vowtage to VID
}ATOM_VOWTAGE_OBJECT_V2;

typedef stwuct  _ATOM_VOWTAGE_OBJECT_INFO
{
   ATOM_COMMON_TABWE_HEADEW   sHeadew;
   ATOM_VOWTAGE_OBJECT        asVowtageObj[3];   //Info fow Vowtage contwow
}ATOM_VOWTAGE_OBJECT_INFO;

typedef stwuct  _ATOM_VOWTAGE_OBJECT_INFO_V2
{
   ATOM_COMMON_TABWE_HEADEW   sHeadew;
    ATOM_VOWTAGE_OBJECT_V2    asVowtageObj[3];   //Info fow Vowtage contwow
}ATOM_VOWTAGE_OBJECT_INFO_V2;

typedef stwuct  _ATOM_WEAKID_VOWTAGE
{
   UCHAW    ucWeakageId;
   UCHAW    ucWesewved;
   USHOWT   usVowtage;
}ATOM_WEAKID_VOWTAGE;

typedef stwuct _ATOM_VOWTAGE_OBJECT_HEADEW_V3{
   UCHAW    ucVowtageType;                            //Indicate Vowtage Souwce: VDDC, MVDDC, MVDDQ ow MVDDCI
   UCHAW    ucVowtageMode;                            //Indicate vowtage contwow mode: Init/Set/Weakage/Set phase
   USHOWT   usSize;                                   //Size of Object
}ATOM_VOWTAGE_OBJECT_HEADEW_V3;

// ATOM_VOWTAGE_OBJECT_HEADEW_V3.ucVowtageMode
#define VOWTAGE_OBJ_GPIO_WUT                 0        //VOWTAGE and GPIO Wookup tabwe ->ATOM_GPIO_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_VW_I2C_INIT_SEQ          3        //VOWTAGE WEGUWATOW INIT sequece thwough I2C -> ATOM_I2C_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_PHASE_WUT                4        //Set Vweguwatow Phase wookup tabwe ->ATOM_GPIO_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_SVID2                    7        //Indicate vowtage contwow by SVID2 ->ATOM_SVID2_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_EVV                      8
#define VOWTAGE_OBJ_PWWBOOST_WEAKAGE_WUT     0x10     //Powewboost Vowtage and WeakageId wookup tabwe->ATOM_WEAKAGE_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_HIGH_STATE_WEAKAGE_WUT   0x11     //High vowtage state Vowtage and WeakageId wookup tabwe->ATOM_WEAKAGE_VOWTAGE_OBJECT_V3
#define VOWTAGE_OBJ_HIGH1_STATE_WEAKAGE_WUT  0x12     //High1 vowtage state Vowtage and WeakageId wookup tabwe->ATOM_WEAKAGE_VOWTAGE_OBJECT_V3

typedef stwuct  _VOWTAGE_WUT_ENTWY_V2
{
  UWONG   uwVowtageId;                       // The Vowtage ID which is used to pwogwam GPIO wegistew
  USHOWT  usVowtageVawue;                    // The cowwesponding Vowtage Vawue, in mV
}VOWTAGE_WUT_ENTWY_V2;

typedef stwuct  _WEAKAGE_VOWTAGE_WUT_ENTWY_V2
{
  USHOWT  usVowtageWevew;                    // The Vowtage ID which is used to pwogwam GPIO wegistew
  USHOWT  usVowtageId;
  USHOWT  usWeakageId;                       // The cowwesponding Vowtage Vawue, in mV
}WEAKAGE_VOWTAGE_WUT_ENTWY_V2;


typedef stwuct  _ATOM_I2C_VOWTAGE_OBJECT_V3
{
   ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = VOWTAGE_OBJ_VW_I2C_INIT_SEQ
   UCHAW  ucVowtageWeguwatowId;              //Indicate Vowtage Weguwatow Id
   UCHAW  ucVowtageContwowI2cWine;
   UCHAW  ucVowtageContwowAddwess;
   UCHAW  ucVowtageContwowOffset;
   UCHAW  ucVowtageContwowFwag;              // Bit0: 0 - One byte data; 1 - Two byte data
   UCHAW  uwWesewved[3];
   VOWTAGE_WUT_ENTWY asVowI2cWut[];         // end with 0xff
}ATOM_I2C_VOWTAGE_OBJECT_V3;

// ATOM_I2C_VOWTAGE_OBJECT_V3.ucVowtageContwowFwag
#define VOWTAGE_DATA_ONE_BYTE                0
#define VOWTAGE_DATA_TWO_BYTE                1

typedef stwuct  _ATOM_GPIO_VOWTAGE_OBJECT_V3
{
   ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = VOWTAGE_OBJ_GPIO_WUT ow VOWTAGE_OBJ_PHASE_WUT
   UCHAW  ucVowtageGpioCntwId;               // defauwt is 0 which indicate contwow thwough CG VID mode
   UCHAW  ucGpioEntwyNum;                    // indiate the entwy numbews of Votwage/Gpio vawue Wook up tabwe
   UCHAW  ucPhaseDeway;                      // phase deway in unit of micwo second
   UCHAW  ucWesewved;
   UWONG  uwGpioMaskVaw;                     // GPIO Mask vawue
   VOWTAGE_WUT_ENTWY_V2 asVowGpioWut[];
}ATOM_GPIO_VOWTAGE_OBJECT_V3;

typedef stwuct  _ATOM_WEAKAGE_VOWTAGE_OBJECT_V3
{
   ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = 0x10/0x11/0x12
   UCHAW    ucWeakageCntwId;                 // defauwt is 0
   UCHAW    ucWeakageEntwyNum;               // indicate the entwy numbew of WeakageId/Vowtage Wut tabwe
   UCHAW    ucWesewved[2];
   UWONG    uwMaxVowtageWevew;
   WEAKAGE_VOWTAGE_WUT_ENTWY_V2 asWeakageIdWut[];
}ATOM_WEAKAGE_VOWTAGE_OBJECT_V3;


typedef stwuct  _ATOM_SVID2_VOWTAGE_OBJECT_V3
{
   ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = VOWTAGE_OBJ_SVID2
// 14:7 - PSI0_VID
// 6 - PSI0_EN
// 5 - PSI1
// 4:2 - woad wine swope twim.
// 1:0 - offset twim,
   USHOWT   usWoadWine_PSI;
// GPU GPIO pin Id to SVID2 weguwatow VWHot pin. possibwe vawue 0~31. 0 means GPIO0, 31 means GPIO31
   UCHAW    ucSVDGpioId;     //0~31 indicate GPIO0~31
   UCHAW    ucSVCGpioId;     //0~31 indicate GPIO0~31
   UWONG    uwWesewved;
}ATOM_SVID2_VOWTAGE_OBJECT_V3;



typedef stwuct  _ATOM_MEWGED_VOWTAGE_OBJECT_V3
{
   ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = VOWTAGE_OBJ_MEWGED_POWEW
   UCHAW    ucMewgedVType;                   // VDDC/VDCCI/....
   UCHAW    ucWesewved[3];
}ATOM_MEWGED_VOWTAGE_OBJECT_V3;


typedef stwuct _ATOM_EVV_DPM_INFO
{
  UWONG uwDPMScwk;            // DPM state SCWK
  USHOWT usVAdjOffset;        // Adjust Vowtage offset in unit of mv
  UCHAW ucDPMTbwVIndex;       // Vowtage Index in SMC_DPM_Tabwe stwuctuwe VddcTabwe/VddGfxTabwe
  UCHAW ucDPMState;           // DPMState0~7
} ATOM_EVV_DPM_INFO;

// ucVowtageMode = VOWTAGE_OBJ_EVV
typedef stwuct  _ATOM_EVV_VOWTAGE_OBJECT_V3
{
  ATOM_VOWTAGE_OBJECT_HEADEW_V3 sHeadew;    // vowtage mode = VOWTAGE_OBJ_SVID2
  ATOM_EVV_DPM_INFO asEvvDpmWist[8];
}ATOM_EVV_VOWTAGE_OBJECT_V3;


typedef union _ATOM_VOWTAGE_OBJECT_V3{
  ATOM_GPIO_VOWTAGE_OBJECT_V3 asGpioVowtageObj;
  ATOM_I2C_VOWTAGE_OBJECT_V3 asI2cVowtageObj;
  ATOM_WEAKAGE_VOWTAGE_OBJECT_V3 asWeakageObj;
  ATOM_SVID2_VOWTAGE_OBJECT_V3 asSVID2Obj;
  ATOM_EVV_VOWTAGE_OBJECT_V3 asEvvObj;
}ATOM_VOWTAGE_OBJECT_V3;

typedef stwuct  _ATOM_VOWTAGE_OBJECT_INFO_V3_1
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  ATOM_VOWTAGE_OBJECT_V3     asVowtageObj[3];   //Info fow Vowtage contwow
}ATOM_VOWTAGE_OBJECT_INFO_V3_1;


typedef stwuct  _ATOM_ASIC_PWOFIWE_VOWTAGE
{
   UCHAW    ucPwofiweId;
   UCHAW    ucWesewved;
   USHOWT   usSize;
   USHOWT   usEfuseSpaweStawtAddw;
   USHOWT   usFuseIndex[8];                                    //fwom WSB to MSB, Max 8bit,end of 0xffff if wess than 8 efuse id,
   ATOM_WEAKID_VOWTAGE               asWeakVow[2];         //Weakid and wewatd vowtage
}ATOM_ASIC_PWOFIWE_VOWTAGE;

//ucPwofiweId
#define   ATOM_ASIC_PWOFIWE_ID_EFUSE_VOWTAGE                     1
#define   ATOM_ASIC_PWOFIWE_ID_EFUSE_PEWFOWMANCE_VOWTAGE         1
#define   ATOM_ASIC_PWOFIWE_ID_EFUSE_THEWMAW_VOWTAGE             2

typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  ATOM_ASIC_PWOFIWE_VOWTAGE        asVowtage;
}ATOM_ASIC_PWOFIWING_INFO;

typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V2_1
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UCHAW  ucWeakageBinNum;                // indicate the entwy numbew of WeakageId/Vowtage Wut tabwe
  USHOWT usWeakageBinAwwayOffset;        // offset of USHOWT Weakage Bin wist awway ( fwom wowew WeakageId to highew)

  UCHAW  ucEwbVDDC_Num;
  USHOWT usEwbVDDC_IdAwwayOffset;        // offset of USHOWT viwtuaw VDDC vowtage id ( 0xff01~0xff08 )
  USHOWT usEwbVDDC_WevewAwwayOffset;     // offset of 2 dimension vowtage wevew USHOWT awway

  UCHAW  ucEwbVDDCI_Num;
  USHOWT usEwbVDDCI_IdAwwayOffset;       // offset of USHOWT viwtuaw VDDCI vowtage id ( 0xff01~0xff08 )
  USHOWT usEwbVDDCI_WevewAwwayOffset;    // offset of 2 dimension vowtage wevew USHOWT awway
}ATOM_ASIC_PWOFIWING_INFO_V2_1;


//Hewe is pawametew to convewt Efuse vawue to Measuwe vawue
//Measuwed = WN((2^Bitsize-1)/EFUSE-1)*(Wange)/(-awpha)+(Max+Min)/2
typedef stwuct _EFUSE_WOGISTIC_FUNC_PAWAM
{
  USHOWT usEfuseIndex;                  // Efuse Index in DWOWD addwess, fow exampwe Index 911, usEuseIndex=112
  UCHAW  ucEfuseBitWSB;                 // Efuse bit WSB in DWOWD addwess, fow exampwe Index 911, usEfuseBitWSB= 911-112*8=15
  UCHAW  ucEfuseWength;                 // Efuse bits wength,
  UWONG  uwEfuseEncodeWange;            // Wange = Max - Min, bit31 indicate the efuse is negative numbew
  UWONG  uwEfuseEncodeAvewage;          // Avewage = ( Max + Min )/2
}EFUSE_WOGISTIC_FUNC_PAWAM;

//Wineaw Function: Measuwed = Wound ( Efuse * ( Max-Min )/(2^BitSize -1 ) + Min )
typedef stwuct _EFUSE_WINEAW_FUNC_PAWAM
{
  USHOWT usEfuseIndex;                  // Efuse Index in DWOWD addwess, fow exampwe Index 911, usEuseIndex=112
  UCHAW  ucEfuseBitWSB;                 // Efuse bit WSB in DWOWD addwess, fow exampwe Index 911, usEfuseBitWSB= 911-112*8=15
  UCHAW  ucEfuseWength;                 // Efuse bits wength,
  UWONG  uwEfuseEncodeWange;            // Wange = Max - Min, bit31 indicate the efuse is negative numbew
  UWONG  uwEfuseMin;                    // Min
}EFUSE_WINEAW_FUNC_PAWAM;


typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_1
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwEvvDewateTdp;
  UWONG  uwEvvDewateTdc;
  UWONG  uwBoawdCoweTemp;
  UWONG  uwMaxVddc;
  UWONG  uwMinVddc;
  UWONG  uwWoadWineSwop;
  UWONG  uwWeakageTemp;
  UWONG  uwWeakageVowtage;
  EFUSE_WINEAW_FUNC_PAWAM sCACm;
  EFUSE_WINEAW_FUNC_PAWAM sCACb;
  EFUSE_WOGISTIC_FUNC_PAWAM sKt_b;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_m;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_b;
  USHOWT usWkgEuseIndex;
  UCHAW  ucWkgEfuseBitWSB;
  UCHAW  ucWkgEfuseWength;
  UWONG  uwWkgEncodeWn_MaxDivMin;
  UWONG  uwWkgEncodeMax;
  UWONG  uwWkgEncodeMin;
  UWONG  uwEfuseWogisticAwpha;
  USHOWT usPowewDpm0;
  USHOWT usCuwwentDpm0;
  USHOWT usPowewDpm1;
  USHOWT usCuwwentDpm1;
  USHOWT usPowewDpm2;
  USHOWT usCuwwentDpm2;
  USHOWT usPowewDpm3;
  USHOWT usCuwwentDpm3;
  USHOWT usPowewDpm4;
  USHOWT usCuwwentDpm4;
  USHOWT usPowewDpm5;
  USHOWT usCuwwentDpm5;
  USHOWT usPowewDpm6;
  USHOWT usCuwwentDpm6;
  USHOWT usPowewDpm7;
  USHOWT usCuwwentDpm7;
}ATOM_ASIC_PWOFIWING_INFO_V3_1;


typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_2
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwEvvWkgFactow;
  UWONG  uwBoawdCoweTemp;
  UWONG  uwMaxVddc;
  UWONG  uwMinVddc;
  UWONG  uwWoadWineSwop;
  UWONG  uwWeakageTemp;
  UWONG  uwWeakageVowtage;
  EFUSE_WINEAW_FUNC_PAWAM sCACm;
  EFUSE_WINEAW_FUNC_PAWAM sCACb;
  EFUSE_WOGISTIC_FUNC_PAWAM sKt_b;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_m;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_b;
  USHOWT usWkgEuseIndex;
  UCHAW  ucWkgEfuseBitWSB;
  UCHAW  ucWkgEfuseWength;
  UWONG  uwWkgEncodeWn_MaxDivMin;
  UWONG  uwWkgEncodeMax;
  UWONG  uwWkgEncodeMin;
  UWONG  uwEfuseWogisticAwpha;
  USHOWT usPowewDpm0;
  USHOWT usPowewDpm1;
  USHOWT usPowewDpm2;
  USHOWT usPowewDpm3;
  USHOWT usPowewDpm4;
  USHOWT usPowewDpm5;
  USHOWT usPowewDpm6;
  USHOWT usPowewDpm7;
  UWONG  uwTdpDewateDPM0;
  UWONG  uwTdpDewateDPM1;
  UWONG  uwTdpDewateDPM2;
  UWONG  uwTdpDewateDPM3;
  UWONG  uwTdpDewateDPM4;
  UWONG  uwTdpDewateDPM5;
  UWONG  uwTdpDewateDPM6;
  UWONG  uwTdpDewateDPM7;
}ATOM_ASIC_PWOFIWING_INFO_V3_2;


// fow Tonga/Fiji speed EVV awgowithm
typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_3
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwEvvWkgFactow;
  UWONG  uwBoawdCoweTemp;
  UWONG  uwMaxVddc;
  UWONG  uwMinVddc;
  UWONG  uwWoadWineSwop;
  UWONG  uwWeakageTemp;
  UWONG  uwWeakageVowtage;
  EFUSE_WINEAW_FUNC_PAWAM sCACm;
  EFUSE_WINEAW_FUNC_PAWAM sCACb;
  EFUSE_WOGISTIC_FUNC_PAWAM sKt_b;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_m;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_b;
  USHOWT usWkgEuseIndex;
  UCHAW  ucWkgEfuseBitWSB;
  UCHAW  ucWkgEfuseWength;
  UWONG  uwWkgEncodeWn_MaxDivMin;
  UWONG  uwWkgEncodeMax;
  UWONG  uwWkgEncodeMin;
  UWONG  uwEfuseWogisticAwpha;

  union{
  USHOWT usPowewDpm0;
  USHOWT usPawamNegFwag;          //bit0 =1 :indicate uwWoBeta is Negative, bit1=1 indicate Kv_m  max is postive
  };
  USHOWT usPowewDpm1;
  USHOWT usPowewDpm2;
  USHOWT usPowewDpm3;
  USHOWT usPowewDpm4;
  USHOWT usPowewDpm5;
  USHOWT usPowewDpm6;
  USHOWT usPowewDpm7;
  UWONG  uwTdpDewateDPM0;
  UWONG  uwTdpDewateDPM1;
  UWONG  uwTdpDewateDPM2;
  UWONG  uwTdpDewateDPM3;
  UWONG  uwTdpDewateDPM4;
  UWONG  uwTdpDewateDPM5;
  UWONG  uwTdpDewateDPM6;
  UWONG  uwTdpDewateDPM7;
  EFUSE_WINEAW_FUNC_PAWAM sWoFuse;
  UWONG  uwWoAwpha;
  UWONG  uwWoBeta;
  UWONG  uwWoGamma;
  UWONG  uwWoEpsiwon;
  UWONG  uwATewmWo;
  UWONG  uwBTewmWo;
  UWONG  uwCTewmWo;
  UWONG  uwScwkMawgin;
  UWONG  uwFmaxPewcent;
  UWONG  uwCWPewcent;
  UWONG  uwSFmaxPewcent;
  UWONG  uwSCWPewcent;
  UWONG  uwSDCMawgine;
}ATOM_ASIC_PWOFIWING_INFO_V3_3;

// fow Fiji speed EVV awgowithm
typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_4
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwEvvWkgFactow;
  UWONG  uwBoawdCoweTemp;
  UWONG  uwMaxVddc;
  UWONG  uwMinVddc;
  UWONG  uwWoadWineSwop;
  UWONG  uwWeakageTemp;
  UWONG  uwWeakageVowtage;
  EFUSE_WINEAW_FUNC_PAWAM sCACm;
  EFUSE_WINEAW_FUNC_PAWAM sCACb;
  EFUSE_WOGISTIC_FUNC_PAWAM sKt_b;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_m;
  EFUSE_WOGISTIC_FUNC_PAWAM sKv_b;
  USHOWT usWkgEuseIndex;
  UCHAW  ucWkgEfuseBitWSB;
  UCHAW  ucWkgEfuseWength;
  UWONG  uwWkgEncodeWn_MaxDivMin;
  UWONG  uwWkgEncodeMax;
  UWONG  uwWkgEncodeMin;
  UWONG  uwEfuseWogisticAwpha;
  USHOWT usPowewDpm0;
  USHOWT usPowewDpm1;
  USHOWT usPowewDpm2;
  USHOWT usPowewDpm3;
  USHOWT usPowewDpm4;
  USHOWT usPowewDpm5;
  USHOWT usPowewDpm6;
  USHOWT usPowewDpm7;
  UWONG  uwTdpDewateDPM0;
  UWONG  uwTdpDewateDPM1;
  UWONG  uwTdpDewateDPM2;
  UWONG  uwTdpDewateDPM3;
  UWONG  uwTdpDewateDPM4;
  UWONG  uwTdpDewateDPM5;
  UWONG  uwTdpDewateDPM6;
  UWONG  uwTdpDewateDPM7;
  EFUSE_WINEAW_FUNC_PAWAM sWoFuse;
  UWONG  uwEvvDefauwtVddc;
  UWONG  uwEvvNoCawcVddc;
  USHOWT usPawamNegFwag;
  USHOWT usSpeed_Modew;
  UWONG  uwSM_A0;
  UWONG  uwSM_A1;
  UWONG  uwSM_A2;
  UWONG  uwSM_A3;
  UWONG  uwSM_A4;
  UWONG  uwSM_A5;
  UWONG  uwSM_A6;
  UWONG  uwSM_A7;
  UCHAW  ucSM_A0_sign;
  UCHAW  ucSM_A1_sign;
  UCHAW  ucSM_A2_sign;
  UCHAW  ucSM_A3_sign;
  UCHAW  ucSM_A4_sign;
  UCHAW  ucSM_A5_sign;
  UCHAW  ucSM_A6_sign;
  UCHAW  ucSM_A7_sign;
  UWONG uwMawgin_WO_a;
  UWONG uwMawgin_WO_b;
  UWONG uwMawgin_WO_c;
  UWONG uwMawgin_fixed;
  UWONG uwMawgin_Fmax_mean;
  UWONG uwMawgin_pwat_mean;
  UWONG uwMawgin_Fmax_sigma;
  UWONG uwMawgin_pwat_sigma;
  UWONG uwMawgin_DC_sigma;
  UWONG uwWesewved[8];            // Wesewved fow futuwe ASIC
}ATOM_ASIC_PWOFIWING_INFO_V3_4;

// fow  Powawis10/Powawis11 speed EVV awgowithm
typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_5
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwMaxVddc;               //Maximum vowtage fow aww pawts, in unit of 0.01mv
  UWONG  uwMinVddc;               //Minimum vowtage fow aww pawts, in unit of 0.01mv
  USHOWT usWkgEuseIndex;          //Efuse Wkg_FT addwess ( BYTE addwess )
  UCHAW  ucWkgEfuseBitWSB;        //Efuse Wkg_FT bit shift in 32bit DWOWD
  UCHAW  ucWkgEfuseWength;        //Efuse Wkg_FT wength
  UWONG  uwWkgEncodeWn_MaxDivMin; //vawue of wn(Max_Wkg_Ft/Min_Wkg_Ft ) in unit of 0.00001 ( unit=100000 )
  UWONG  uwWkgEncodeMax;          //Maximum Wkg_Ft measuwed vawue ( ow efuse decode vawue ), in unit of 0.00001 ( unit=100000 )
  UWONG  uwWkgEncodeMin;          //Minimum Wkg_Ft measuwed vawue ( ow efuse decode vawue ), in unit of 0.00001 ( unit=100000 )
  EFUSE_WINEAW_FUNC_PAWAM sWoFuse;//Efuse WO info: DWOWD addwess, bit shift, wength, max/min measuwe vawue. in unit of 1.
  UWONG  uwEvvDefauwtVddc;        //def="EVV_DEFAUWT_VDDC" descw="wetuwn defauwt VDDC(v) when Efuse not cut" unit="100000"/>
  UWONG  uwEvvNoCawcVddc;         //def="EVV_NOCAWC_VDDC" descw="wetuwn VDDC(v) when Cawcuwation is bad" unit="100000"/>
  UWONG  uwSpeed_Modew;           //def="EVV_SPEED_MODEW" descw="0 = Gweek modew, 1 = muwtivawiate modew" unit="1"/>
  UWONG  uwSM_A0;                 //def="EVV_SM_A0" descw="Weakage coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A1;                 //def="EVV_SM_A1" descw="Weakage/SCWK coeff(Muwtivawiant Mode)." unit="1000000"/>
  UWONG  uwSM_A2;                 //def="EVV_SM_A2" descw="Awpha( Gweek Mode ) ow VDDC/SCWK coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A3;                 //def="EVV_SM_A3" descw="Beta( Gweek Mode ) ow SCWK coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A4;                 //def="EVV_SM_A4" descw="VDDC^2/SCWK coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A5;                 //def="EVV_SM_A5" descw="VDDC^2 coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A6;                 //def="EVV_SM_A6" descw="Gamma( Gweek Mode ) ow VDDC coeff(Muwtivawiant Mode)." unit="100000"/>
  UWONG  uwSM_A7;                 //def="EVV_SM_A7" descw="Epsiwon( Gweek Mode ) ow constant(Muwtivawiant Mode)." unit="100000"/>
  UCHAW  ucSM_A0_sign;            //def="EVV_SM_A0_SIGN" descw="=0 SM_A0 is postive. =1: SM_A0 is negative" unit="1"/>
  UCHAW  ucSM_A1_sign;            //def="EVV_SM_A1_SIGN" descw="=0 SM_A1 is postive. =1: SM_A1 is negative" unit="1"/>
  UCHAW  ucSM_A2_sign;            //def="EVV_SM_A2_SIGN" descw="=0 SM_A2 is postive. =1: SM_A2 is negative" unit="1"/>
  UCHAW  ucSM_A3_sign;            //def="EVV_SM_A3_SIGN" descw="=0 SM_A3 is postive. =1: SM_A3 is negative" unit="1"/>
  UCHAW  ucSM_A4_sign;            //def="EVV_SM_A4_SIGN" descw="=0 SM_A4 is postive. =1: SM_A4 is negative" unit="1"/>
  UCHAW  ucSM_A5_sign;            //def="EVV_SM_A5_SIGN" descw="=0 SM_A5 is postive. =1: SM_A5 is negative" unit="1"/>
  UCHAW  ucSM_A6_sign;            //def="EVV_SM_A6_SIGN" descw="=0 SM_A6 is postive. =1: SM_A6 is negative" unit="1"/>
  UCHAW  ucSM_A7_sign;            //def="EVV_SM_A7_SIGN" descw="=0 SM_A7 is postive. =1: SM_A7 is negative" unit="1"/>
  UWONG  uwMawgin_WO_a;           //def="EVV_MAWGIN_WO_A" descw="A Tewm to wepwesent WO equation in Ax2+Bx+C, unit=1"
  UWONG  uwMawgin_WO_b;           //def="EVV_MAWGIN_WO_B" descw="B Tewm to wepwesent WO equation in Ax2+Bx+C, unit=1"
  UWONG  uwMawgin_WO_c;           //def="EVV_MAWGIN_WO_C" descw="C Tewm to wepwesent WO equation in Ax2+Bx+C, unit=1"
  UWONG  uwMawgin_fixed;          //def="EVV_MAWGIN_FIXED" descw="Fixed MHz to add to SCWK mawgin, unit=1" unit="1"/>
  UWONG  uwMawgin_Fmax_mean;      //def="EVV_MAWGIN_FMAX_MEAN" descw="Pewcentage to add fow Fmas mean mawgin unit=10000" unit="10000"/>
  UWONG  uwMawgin_pwat_mean;      //def="EVV_MAWGIN_PWAT_MEAN" descw="Pewcentage to add fow pwatfowm mean mawgin unit=10000" unit="10000"/>
  UWONG  uwMawgin_Fmax_sigma;     //def="EVV_MAWGIN_FMAX_SIGMA" descw="Pewcentage to add fow Fmax sigma mawgin unit=10000" unit="10000"/>
  UWONG  uwMawgin_pwat_sigma;     //def="EVV_MAWGIN_PWAT_SIGMA" descw="Pewcentage to add fow pwatfowm sigma mawgin unit=10000" unit="10000"/>
  UWONG  uwMawgin_DC_sigma;       //def="EVV_MAWGIN_DC_SIGMA" descw="Weguwatow DC towewance mawgin (mV) unit=100" unit="100"/>
  UWONG  uwWesewved[12];
}ATOM_ASIC_PWOFIWING_INFO_V3_5;

/* fow Powaws10/11 AVFS pawametews */
typedef stwuct  _ATOM_ASIC_PWOFIWING_INFO_V3_6
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UWONG  uwMaxVddc;
  UWONG  uwMinVddc;
  USHOWT usWkgEuseIndex;
  UCHAW  ucWkgEfuseBitWSB;
  UCHAW  ucWkgEfuseWength;
  UWONG  uwWkgEncodeWn_MaxDivMin;
  UWONG  uwWkgEncodeMax;
  UWONG  uwWkgEncodeMin;
  EFUSE_WINEAW_FUNC_PAWAM sWoFuse;
  UWONG  uwEvvDefauwtVddc;
  UWONG  uwEvvNoCawcVddc;
  UWONG  uwSpeed_Modew;
  UWONG  uwSM_A0;
  UWONG  uwSM_A1;
  UWONG  uwSM_A2;
  UWONG  uwSM_A3;
  UWONG  uwSM_A4;
  UWONG  uwSM_A5;
  UWONG  uwSM_A6;
  UWONG  uwSM_A7;
  UCHAW  ucSM_A0_sign;
  UCHAW  ucSM_A1_sign;
  UCHAW  ucSM_A2_sign;
  UCHAW  ucSM_A3_sign;
  UCHAW  ucSM_A4_sign;
  UCHAW  ucSM_A5_sign;
  UCHAW  ucSM_A6_sign;
  UCHAW  ucSM_A7_sign;
  UWONG  uwMawgin_WO_a;
  UWONG  uwMawgin_WO_b;
  UWONG  uwMawgin_WO_c;
  UWONG  uwMawgin_fixed;
  UWONG  uwMawgin_Fmax_mean;
  UWONG  uwMawgin_pwat_mean;
  UWONG  uwMawgin_Fmax_sigma;
  UWONG  uwMawgin_pwat_sigma;
  UWONG  uwMawgin_DC_sigma;
  UWONG  uwWoadWineSwop;
  UWONG  uwaTDCwimitPewDPM[8];
  UWONG  uwaNoCawcVddcPewDPM[8];
  UWONG  uwAVFS_meanNsigma_Acontant0;
  UWONG  uwAVFS_meanNsigma_Acontant1;
  UWONG  uwAVFS_meanNsigma_Acontant2;
  USHOWT usAVFS_meanNsigma_DC_tow_sigma;
  USHOWT usAVFS_meanNsigma_Pwatfowm_mean;
  USHOWT usAVFS_meanNsigma_Pwatfowm_sigma;
  UWONG  uwGB_VDWOOP_TABWE_CKSOFF_a0;
  UWONG  uwGB_VDWOOP_TABWE_CKSOFF_a1;
  UWONG  uwGB_VDWOOP_TABWE_CKSOFF_a2;
  UWONG  uwGB_VDWOOP_TABWE_CKSON_a0;
  UWONG  uwGB_VDWOOP_TABWE_CKSON_a1;
  UWONG  uwGB_VDWOOP_TABWE_CKSON_a2;
  UWONG  uwAVFSGB_FUSE_TABWE_CKSOFF_m1;
  USHOWT usAVFSGB_FUSE_TABWE_CKSOFF_m2;
  UWONG  uwAVFSGB_FUSE_TABWE_CKSOFF_b;
  UWONG  uwAVFSGB_FUSE_TABWE_CKSON_m1;
  USHOWT usAVFSGB_FUSE_TABWE_CKSON_m2;
  UWONG  uwAVFSGB_FUSE_TABWE_CKSON_b;
  USHOWT usMaxVowtage_0_25mv;
  UCHAW  ucEnabweGB_VDWOOP_TABWE_CKSOFF;
  UCHAW  ucEnabweGB_VDWOOP_TABWE_CKSON;
  UCHAW  ucEnabweGB_FUSE_TABWE_CKSOFF;
  UCHAW  ucEnabweGB_FUSE_TABWE_CKSON;
  USHOWT usPSM_Age_ComFactow;
  UCHAW  ucEnabweAppwyAVFS_CKS_OFF_Vowtage;
  UCHAW  ucWesewved;
}ATOM_ASIC_PWOFIWING_INFO_V3_6;


typedef stwuct _ATOM_SCWK_FCW_WANGE_ENTWY_V1{
  UWONG  uwMaxScwkFweq;
  UCHAW  ucVco_setting;      // 1: 3-6GHz, 3: 2-4GHz
  UCHAW  ucPostdiv;          // divide by 2^n
  USHOWT ucFcw_pcc;
  USHOWT ucFcw_twans_uppew;
  USHOWT ucWcw_twans_wowew;
}ATOM_SCWK_FCW_WANGE_ENTWY_V1;


// SMU_InfoTabwe fow  Powawis10/Powawis11
typedef stwuct  _ATOM_SMU_INFO_V2_1
{
  ATOM_COMMON_TABWE_HEADEW         asHeadew;
  UCHAW ucScwkEntwyNum;            // fow potentiaw futuwe extend, indicate the numbew of ATOM_SCWK_FCW_WANGE_ENTWY_V1
  UCHAW ucSMUVew;
  UCHAW ucShawePowewSouwce;
  UCHAW ucWesewved;
  ATOM_SCWK_FCW_WANGE_ENTWY_V1     asScwkFcwWangeEntwy[8];
}ATOM_SMU_INFO_V2_1;


// GFX_InfoTabwe fow Powawis10/Powawis11
typedef stwuct  _ATOM_GFX_INFO_V2_1
{
  ATOM_COMMON_TABWE_HEADEW asHeadew;
  UCHAW GfxIpMinVew;
  UCHAW GfxIpMajVew;
  UCHAW max_shadew_engines;
  UCHAW max_tiwe_pipes;
  UCHAW max_cu_pew_sh;
  UCHAW max_sh_pew_se;
  UCHAW max_backends_pew_se;
  UCHAW max_textuwe_channew_caches;
}ATOM_GFX_INFO_V2_1;

typedef stwuct  _ATOM_GFX_INFO_V2_3
{
  ATOM_COMMON_TABWE_HEADEW asHeadew;
  UCHAW GfxIpMinVew;
  UCHAW GfxIpMajVew;
  UCHAW max_shadew_engines;
  UCHAW max_tiwe_pipes;
  UCHAW max_cu_pew_sh;
  UCHAW max_sh_pew_se;
  UCHAW max_backends_pew_se;
  UCHAW max_textuwe_channew_caches;
  USHOWT usHiWoWeakageThweshowd;
  USHOWT usEdcDidtWoDpm7TabweOffset; //offset of DPM7 wow weakage tabwe _ATOM_EDC_DIDT_TABWE_V1
  USHOWT usEdcDidtHiDpm7TabweOffset; //offset of DPM7 high weakage tabwe _ATOM_EDC_DIDT_TABWE_V1
  USHOWT usWesewvewd[3];
}ATOM_GFX_INFO_V2_3;

typedef stwuct _ATOM_POWEW_SOUWCE_OBJECT
{
   UCHAW  ucPwwSwcId;                                   // Powew souwce
   UCHAW  ucPwwSensowType;                              // GPIO, I2C ow none
   UCHAW  ucPwwSensId;                                  // if GPIO detect, it is GPIO id,  if I2C detect, it is I2C id
   UCHAW  ucPwwSensSwaveAddw;                           // Swave addwess if I2C detect
   UCHAW  ucPwwSensWegIndex;                            // I2C wegistew Index if I2C detect
   UCHAW  ucPwwSensWegBitMask;                          // detect which bit is used if I2C detect
   UCHAW  ucPwwSensActiveState;                         // high active ow wow active
   UCHAW  ucWesewve[3];                                 // wesewve
   USHOWT usSensPww;                                    // in unit of watt
}ATOM_POWEW_SOUWCE_OBJECT;

typedef stwuct _ATOM_POWEW_SOUWCE_INFO
{
      ATOM_COMMON_TABWE_HEADEW      asHeadew;
      UCHAW                                    asPwwbehave[16];
      ATOM_POWEW_SOUWCE_OBJECT      asPwwObj[1];
}ATOM_POWEW_SOUWCE_INFO;


//Define ucPwwSwcId
#define POWEWSOUWCE_PCIE_ID1                  0x00
#define POWEWSOUWCE_6PIN_CONNECTOW_ID1   0x01
#define POWEWSOUWCE_8PIN_CONNECTOW_ID1   0x02
#define POWEWSOUWCE_6PIN_CONNECTOW_ID2   0x04
#define POWEWSOUWCE_8PIN_CONNECTOW_ID2   0x08

//define ucPwwSensowId
#define POWEW_SENSOW_AWWAYS                     0x00
#define POWEW_SENSOW_GPIO                        0x01
#define POWEW_SENSOW_I2C                        0x02

typedef stwuct _ATOM_CWK_VOWT_CAPABIWITY
{
  UWONG      uwVowtageIndex;                      // The Vowtage Index indicated by FUSE, same vowtage index shawed with SCWK DPM fuse tabwe
  UWONG      uwMaximumSuppowtedCWK;               // Maximum cwock suppowted with specified vowtage index, unit in 10kHz
}ATOM_CWK_VOWT_CAPABIWITY;


typedef stwuct _ATOM_CWK_VOWT_CAPABIWITY_V2
{
  USHOWT     usVowtageWevew;                      // The weaw Vowtage Wevew wound up vawue in unit of mv,
  UWONG      uwMaximumSuppowtedCWK;               // Maximum cwock suppowted with specified vowtage index, unit in 10kHz
}ATOM_CWK_VOWT_CAPABIWITY_V2;

typedef stwuct _ATOM_AVAIWABWE_SCWK_WIST
{
  UWONG      uwSuppowtedSCWK;               // Maximum cwock suppowted with specified vowtage index,  unit in 10kHz
  USHOWT     usVowtageIndex;                // The Vowtage Index indicated by FUSE fow specified SCWK
  USHOWT     usVowtageID;                   // The Vowtage ID indicated by FUSE fow specified SCWK
}ATOM_AVAIWABWE_SCWK_WIST;

// ATOM_INTEGWATED_SYSTEM_INFO_V6 uwSystemConfig cap definition
#define ATOM_IGP_INFO_V6_SYSTEM_CONFIG__PCIE_POWEW_GATING_ENABWE             1       // wefew to uwSystemConfig bit[0]

// this IntegwateSystemInfoTabwe is used fow Wiano/Ontawio APU
typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V6
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG  uwBootUpEngineCwock;
  UWONG  uwDentistVCOFweq;
  UWONG  uwBootUpUMACwock;
  ATOM_CWK_VOWT_CAPABIWITY   sDISPCWK_Vowtage[4];
  UWONG  uwBootUpWeqDispwayVectow;
  UWONG  uwOthewDispwayMisc;
  UWONG  uwGPUCapInfo;
  UWONG  uwSB_MMIO_Base_Addw;
  USHOWT usWequestedPWMFweqInHz;
  UCHAW  ucHtcTmpWmt;
  UCHAW  ucHtcHystWmt;
  UWONG  uwMinEngineCwock;
  UWONG  uwSystemConfig;
  UWONG  uwCPUCapInfo;
  USHOWT usNBP0Vowtage;
  USHOWT usNBP1Vowtage;
  USHOWT usBootUpNBVowtage;
  USHOWT usExtDispConnInfoOffset;
  USHOWT usPanewWefweshWateWange;
  UCHAW  ucMemowyType;
  UCHAW  ucUMAChannewNumbew;
  UWONG  uwCSW_M3_AWB_CNTW_DEFAUWT[10];
  UWONG  uwCSW_M3_AWB_CNTW_UVD[10];
  UWONG  uwCSW_M3_AWB_CNTW_FS3D[10];
  ATOM_AVAIWABWE_SCWK_WIST   sAvaiw_SCWK[5];
  UWONG  uwGMCWestoweWesetTime;
  UWONG  uwMinimumNCwk;
  UWONG  uwIdweNCwk;
  UWONG  uwDDW_DWW_PowewUpTime;
  UWONG  uwDDW_PWW_PowewUpTime;
  USHOWT usPCIECwkSSPewcentage;
  USHOWT usPCIECwkSSType;
  USHOWT usWvdsSSPewcentage;
  USHOWT usWvdsSSpweadWateIn10Hz;
  USHOWT usHDMISSPewcentage;
  USHOWT usHDMISSpweadWateIn10Hz;
  USHOWT usDVISSPewcentage;
  USHOWT usDVISSpweadWateIn10Hz;
  UWONG  ScwkDpmBoostMawgin;
  UWONG  ScwkDpmThwottweMawgin;
  USHOWT ScwkDpmTdpWimitPG;
  USHOWT ScwkDpmTdpWimitBoost;
  UWONG  uwBoostEngineCWock;
  UCHAW  uwBoostVid_2bit;
  UCHAW  EnabweBoost;
  USHOWT GnbTdpWimit;
  USHOWT usMaxWVDSPcwkFweqInSingweWink;
  UCHAW  ucWvdsMisc;
  UCHAW  ucWVDSWesewved;
  UWONG  uwWesewved3[15];
  ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO sExtDispConnInfo;
}ATOM_INTEGWATED_SYSTEM_INFO_V6;

// uwGPUCapInfo
#define INTEGWATED_SYSTEM_INFO_V6_GPUCAPINFO__TMDSHDMI_COHEWENT_SINGWEPWW_MODE       0x01
#define INTEGWATED_SYSTEM_INFO_V6_GPUCAPINFO__DISABWE_AUX_HW_MODE_DETECTION          0x08

//ucWVDSMisc:
#define SYS_INFO_WVDSMISC__888_FPDI_MODE                                             0x01
#define SYS_INFO_WVDSMISC__DW_CH_SWAP                                                0x02
#define SYS_INFO_WVDSMISC__888_BPC                                                   0x04
#define SYS_INFO_WVDSMISC__OVEWWIDE_EN                                               0x08
#define SYS_INFO_WVDSMISC__BWON_ACTIVE_WOW                                           0x10
// new since Twinity
#define SYS_INFO_WVDSMISC__TWAVIS_WVDS_VOW_OVEWWIDE_EN                               0x20

// not used any mowe
#define SYS_INFO_WVDSMISC__VSYNC_ACTIVE_WOW                                          0x04
#define SYS_INFO_WVDSMISC__HSYNC_ACTIVE_WOW                                          0x08

/**********************************************************************************************************************
  ATOM_INTEGWATED_SYSTEM_INFO_V6 Descwiption
uwBootUpEngineCwock:              VBIOS bootup Engine cwock fwequency, in 10kHz unit. if it is equaw 0, then VBIOS use pwe-defined bootup engine cwock
uwDentistVCOFweq:                 Dentist VCO cwock in 10kHz unit.
uwBootUpUMACwock:                 System memowy boot up cwock fwequency in 10Khz unit.
sDISPCWK_Vowtage:                 Wepowt Dispway cwock vowtage wequiwement.

uwBootUpWeqDispwayVectow:         VBIOS boot up dispway IDs, fowwowing awe suppowted devices in Wiano/Ontaio pwojects:
                                  ATOM_DEVICE_CWT1_SUPPOWT                  0x0001
                                  ATOM_DEVICE_CWT2_SUPPOWT                  0x0010
                                  ATOM_DEVICE_DFP1_SUPPOWT                  0x0008
                                  ATOM_DEVICE_DFP6_SUPPOWT                  0x0040
                                  ATOM_DEVICE_DFP2_SUPPOWT                  0x0080
                                  ATOM_DEVICE_DFP3_SUPPOWT                  0x0200
                                  ATOM_DEVICE_DFP4_SUPPOWT                  0x0400
                                  ATOM_DEVICE_DFP5_SUPPOWT                  0x0800
                                  ATOM_DEVICE_WCD1_SUPPOWT                  0x0002
uwOthewDispwayMisc:                 Othew dispway wewated fwags, not defined yet.
uwGPUCapInfo:                     bit[0]=0: TMDS/HDMI Cohewent Mode use cascade PWW mode.
                                        =1: TMDS/HDMI Cohewent Mode use signew PWW mode.
                                  bit[3]=0: Enabwe HW AUX mode detection wogic
                                        =1: Disabwe HW AUX mode dettion wogic
uwSB_MMIO_Base_Addw:              Physicaw Base addwess to SB MMIO space. Dwivew needs to initiawize it fow SMU usage.

usWequestedPWMFweqInHz:           When it's set to 0x0 by SBIOS: the WCD BackWight is not contwowwed by GPU(SW).
                                  Any attempt to change BW using VBIOS function ow enabwe VawiBwi fwom PP tabwe is not effective since ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==0;

                                  When it's set to a non-zewo fwequency, the BackWight is contwowwed by GPU (SW) in one of two ways bewow:
                                  1. SW uses the GPU BW PWM output to contwow the BW, in chis case, this non-zewo fwequency detewmines what fweq GPU shouwd use;
                                  VBIOS wiww set up pwopew PWM fwequency and ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1,as the wesuwt,
                                  Changing BW using VBIOS function is functionaw in both dwivew and non-dwivew pwesent enviwonment;
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

                                  2. SW uses othew means to contwow BW (wike DPCD),this non-zewo fwequency sewves as a fwag onwy indicating
                                  that BW contwow fwom GPU is expected.
                                  VBIOS wiww NOT set up PWM fwequency but make ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1
                                  Changing BW using VBIOS function couwd be functionaw in both dwivew and non-dwivew pwesent enviwonment,but
                                  it's pew pwatfowm
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

ucHtcTmpWmt:                      Wefew to D18F3x64 bit[22:16], HtcTmpWmt.
                                  Thweshowd on vawue to entew HTC_active state.
ucHtcHystWmt:                     Wefew to D18F3x64 bit[27:24], HtcHystWmt.
                                  To cawcuwate thweshowd off vawue to exit HTC_active state, which is Thweshowd on vwaue minus ucHtcHystWmt.
uwMinEngineCwock:                 Minimum SCWK awwowed in 10kHz unit. This is cawcuwated based on WWCK Fuse settings.
uwSystemConfig:                   Bit[0]=0: PCIE Powew Gating Disabwed
                                        =1: PCIE Powew Gating Enabwed
                                  Bit[1]=0: DDW-DWW shut-down featuwe disabwed.
                                         1: DDW-DWW shut-down featuwe enabwed.
                                  Bit[2]=0: DDW-PWW Powew down featuwe disabwed.
                                         1: DDW-PWW Powew down featuwe enabwed.
uwCPUCapInfo:                     TBD
usNBP0Vowtage:                    VID fow vowtage on NB P0 State
usNBP1Vowtage:                    VID fow vowtage on NB P1 State
usBootUpNBVowtage:                Vowtage Index of GNB vowtage configuwed by SBIOS, which is suffcient to suppowt VBIOS DISPCWK wequiwement.
usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the stwuctuwe
usPanewWefweshWateWange:          Bit vectow fow WCD suppowted wefwesh wate wange. If DWW is wequestd by the pwatfowm, at weast two bits need to be set
                                  to indicate a wange.
                                  SUPPOWTED_WCD_WEFWESHWATE_30Hz          0x0004
                                  SUPPOWTED_WCD_WEFWESHWATE_40Hz          0x0008
                                  SUPPOWTED_WCD_WEFWESHWATE_50Hz          0x0010
                                  SUPPOWTED_WCD_WEFWESHWATE_60Hz          0x0020
ucMemowyType:                     [3:0]=1:DDW1;=2:DDW2;=3:DDW3.[7:4] is wesewved.
ucUMAChannewNumbew:                 System memowy channew numbews.
uwCSW_M3_AWB_CNTW_DEFAUWT[10]:    Awways with vawues fow CSW M3 awbitew fow defauwt
uwCSW_M3_AWB_CNTW_UVD[10]:        Awways with vawues fow CSW M3 awbitew fow UVD pwayback.
uwCSW_M3_AWB_CNTW_FS3D[10]:       Awways with vawues fow CSW M3 awbitew fow Fuww Scween 3D appwications.
sAvaiw_SCWK[5]:                   Awways to pwovide avaiwabe wist of SWCK and cowwesponding vowtage, owdew fwom wow to high
uwGMCWestoweWesetTime:            GMC powew westowe and GMC weset time to cawcuwate data weconnection watency. Unit in ns.
uwMinimumNCwk:                    Minimum NCWK speed among aww NB-Pstates to cawcuawte data weconnection watency. Unit in 10kHz.
uwIdweNCwk:                       NCWK speed whiwe memowy wuns in sewf-wefwesh state. Unit in 10kHz.
uwDDW_DWW_PowewUpTime:            DDW PHY DWW powew up time. Unit in ns.
uwDDW_PWW_PowewUpTime:            DDW PHY PWW powew up time. Unit in ns.
usPCIECwkSSPewcentage:            PCIE Cwock Spwed Spectwum Pewcentage in unit 0.01%; 100 mean 1%.
usPCIECwkSSType:                  PCIE Cwock Spwed Spectwum Type. 0 fow Down spwead(defauwt); 1 fow Centew spwead.
usWvdsSSPewcentage:               WVDS panew ( not incwude eDP ) Spwead Spectwum Pewcentage in unit of 0.01%, =0, use VBIOS defauwt setting.
usWvdsSSpweadWateIn10Hz:          WVDS panew ( not incwude eDP ) Spwead Spectwum fwequency in unit of 10Hz, =0, use VBIOS defauwt setting.
usHDMISSPewcentage:               HDMI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usHDMISSpweadWateIn10Hz:          HDMI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.
usDVISSPewcentage:                DVI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usDVISSpweadWateIn10Hz:           DVI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.
usMaxWVDSPcwkFweqInSingweWink:    Max pixew cwock WVDS panew singwe wink, if=0 means VBIOS use defauwt thwehowd, wight now it is 85Mhz
ucWVDSMisc:                       [bit0] WVDS 888bit panew mode =0: WVDS 888 panew in WDI mode, =1: WVDS 888 panew in FPDI mode
                                  [bit1] WVDS panew wowew and uppew wink mapping =0: wowew wink and uppew wink not swap, =1: wowew wink and uppew wink awe swapped
                                  [bit2] WVDS 888bit pew cowow mode  =0: 666 bit pew cowow =1:888 bit pew cowow
                                  [bit3] WVDS pawametew ovewwide enabwe  =0: ucWvdsMisc pawametew awe not used =1: ucWvdsMisc pawametew shouwd be used
                                  [bit4] Powawity of signaw sent to digitaw BWON output pin. =0: not invewted(active high) =1: invewted ( active wow )
**********************************************************************************************************************/

// this Tabwe is used fow Wiano/Ontawio APU
typedef stwuct _ATOM_FUSION_SYSTEM_INFO_V1
{
  ATOM_INTEGWATED_SYSTEM_INFO_V6    sIntegwatedSysInfo;
  UWONG  uwPowewpwayTabwe[128];
}ATOM_FUSION_SYSTEM_INFO_V1;


typedef stwuct _ATOM_TDP_CONFIG_BITS
{
#if ATOM_BIG_ENDIAN
  UWONG   uWesewved:2;
  UWONG   uTDP_Vawue:14;  // Owiginaw TDP vawue in tens of miwwi watts
  UWONG   uCTDP_Vawue:14; // Ovewwide vawue in tens of miwwi watts
  UWONG   uCTDP_Enabwe:2; // = (uCTDP_Vawue > uTDP_Vawue? 2: (uCTDP_Vawue < uTDP_Vawue))
#ewse
  UWONG   uCTDP_Enabwe:2; // = (uCTDP_Vawue > uTDP_Vawue? 2: (uCTDP_Vawue < uTDP_Vawue))
  UWONG   uCTDP_Vawue:14; // Ovewwide vawue in tens of miwwi watts
  UWONG   uTDP_Vawue:14;  // Owiginaw TDP vawue in tens of miwwi watts
  UWONG   uWesewved:2;
#endif
}ATOM_TDP_CONFIG_BITS;

typedef union _ATOM_TDP_CONFIG
{
  ATOM_TDP_CONFIG_BITS TDP_config;
  UWONG            TDP_config_aww;
}ATOM_TDP_CONFIG;

/**********************************************************************************************************************
  ATOM_FUSION_SYSTEM_INFO_V1 Descwiption
sIntegwatedSysInfo:               wefew to ATOM_INTEGWATED_SYSTEM_INFO_V6 definition.
uwPowewpwayTabwe[128]:            This 512 bytes memowy is used to save ATOM_PPWIB_POWEWPWAYTABWE3, stawting fowm uwPowewpwayTabwe[0]
**********************************************************************************************************************/

// this IntegwateSystemInfoTabwe is used fow Twinity APU
typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_7
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG  uwBootUpEngineCwock;
  UWONG  uwDentistVCOFweq;
  UWONG  uwBootUpUMACwock;
  ATOM_CWK_VOWT_CAPABIWITY   sDISPCWK_Vowtage[4];
  UWONG  uwBootUpWeqDispwayVectow;
  UWONG  uwOthewDispwayMisc;
  UWONG  uwGPUCapInfo;
  UWONG  uwSB_MMIO_Base_Addw;
  USHOWT usWequestedPWMFweqInHz;
  UCHAW  ucHtcTmpWmt;
  UCHAW  ucHtcHystWmt;
  UWONG  uwMinEngineCwock;
  UWONG  uwSystemConfig;
  UWONG  uwCPUCapInfo;
  USHOWT usNBP0Vowtage;
  USHOWT usNBP1Vowtage;
  USHOWT usBootUpNBVowtage;
  USHOWT usExtDispConnInfoOffset;
  USHOWT usPanewWefweshWateWange;
  UCHAW  ucMemowyType;
  UCHAW  ucUMAChannewNumbew;
  UCHAW  stwVBIOSMsg[40];
  ATOM_TDP_CONFIG  asTdpConfig;
  UWONG  uwWesewved[19];
  ATOM_AVAIWABWE_SCWK_WIST   sAvaiw_SCWK[5];
  UWONG  uwGMCWestoweWesetTime;
  UWONG  uwMinimumNCwk;
  UWONG  uwIdweNCwk;
  UWONG  uwDDW_DWW_PowewUpTime;
  UWONG  uwDDW_PWW_PowewUpTime;
  USHOWT usPCIECwkSSPewcentage;
  USHOWT usPCIECwkSSType;
  USHOWT usWvdsSSPewcentage;
  USHOWT usWvdsSSpweadWateIn10Hz;
  USHOWT usHDMISSPewcentage;
  USHOWT usHDMISSpweadWateIn10Hz;
  USHOWT usDVISSPewcentage;
  USHOWT usDVISSpweadWateIn10Hz;
  UWONG  ScwkDpmBoostMawgin;
  UWONG  ScwkDpmThwottweMawgin;
  USHOWT ScwkDpmTdpWimitPG;
  USHOWT ScwkDpmTdpWimitBoost;
  UWONG  uwBoostEngineCWock;
  UCHAW  uwBoostVid_2bit;
  UCHAW  EnabweBoost;
  USHOWT GnbTdpWimit;
  USHOWT usMaxWVDSPcwkFweqInSingweWink;
  UCHAW  ucWvdsMisc;
  UCHAW  ucTwavisWVDSVowAdjust;
  UCHAW  ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
  UCHAW  ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
  UCHAW  ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
  UCHAW  ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
  UCHAW  ucWVDSOffToOnDeway_in4Ms;
  UCHAW  ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
  UCHAW  ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
  UCHAW  ucMinAwwowedBW_Wevew;
  UWONG  uwWCDBitDepthContwowVaw;
  UWONG  uwNbpStateMemcwkFweq[4];
  USHOWT usNBP2Vowtage;
  USHOWT usNBP3Vowtage;
  UWONG  uwNbpStateNCwkFweq[4];
  UCHAW  ucNBDPMEnabwe;
  UCHAW  ucWesewved[3];
  UCHAW  ucDPMState0VcwkFid;
  UCHAW  ucDPMState0DcwkFid;
  UCHAW  ucDPMState1VcwkFid;
  UCHAW  ucDPMState1DcwkFid;
  UCHAW  ucDPMState2VcwkFid;
  UCHAW  ucDPMState2DcwkFid;
  UCHAW  ucDPMState3VcwkFid;
  UCHAW  ucDPMState3DcwkFid;
  ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO sExtDispConnInfo;
}ATOM_INTEGWATED_SYSTEM_INFO_V1_7;

// uwOthewDispwayMisc
#define INTEGWATED_SYSTEM_INFO__GET_EDID_CAWWBACK_FUNC_SUPPOWT            0x01
#define INTEGWATED_SYSTEM_INFO__GET_BOOTUP_DISPWAY_CAWWBACK_FUNC_SUPPOWT  0x02
#define INTEGWATED_SYSTEM_INFO__GET_EXPANSION_CAWWBACK_FUNC_SUPPOWT       0x04
#define INTEGWATED_SYSTEM_INFO__FAST_BOOT_SUPPOWT                         0x08

// uwGPUCapInfo
#define SYS_INFO_GPUCAPS__TMDSHDMI_COHEWENT_SINGWEPWW_MODE                0x01
#define SYS_INFO_GPUCAPS__DP_SINGWEPWW_MODE                               0x02
#define SYS_INFO_GPUCAPS__DISABWE_AUX_MODE_DETECT                         0x08
#define SYS_INFO_GPUCAPS__ENABEW_DFS_BYPASS                               0x10
//uwGPUCapInfo[16]=1 indicate SMC fiwmwawe is abwe to suppowt GNB fast wesume function, so that dwivew can caww SMC to pwogwam most of GNB wegistew duwing wesuming, fwom MW
#define SYS_INFO_GPUCAPS__GNB_FAST_WESUME_CAPABWE                         0x00010000

//uwGPUCapInfo[17]=1 indicate battewy boost featuwe is enabwe, fwom MW
#define SYS_INFO_GPUCAPS__BATTEWY_BOOST_ENABWE                            0x00020000

/**********************************************************************************************************************
  ATOM_INTEGWATED_SYSTEM_INFO_V1_7 Descwiption
uwBootUpEngineCwock:              VBIOS bootup Engine cwock fwequency, in 10kHz unit. if it is equaw 0, then VBIOS use pwe-defined bootup engine cwock
uwDentistVCOFweq:                 Dentist VCO cwock in 10kHz unit.
uwBootUpUMACwock:                 System memowy boot up cwock fwequency in 10Khz unit.
sDISPCWK_Vowtage:                 Wepowt Dispway cwock vowtage wequiwement.

uwBootUpWeqDispwayVectow:         VBIOS boot up dispway IDs, fowwowing awe suppowted devices in Twinity pwojects:
                                  ATOM_DEVICE_CWT1_SUPPOWT                  0x0001
                                  ATOM_DEVICE_DFP1_SUPPOWT                  0x0008
                                  ATOM_DEVICE_DFP6_SUPPOWT                  0x0040
                                  ATOM_DEVICE_DFP2_SUPPOWT                  0x0080
                                  ATOM_DEVICE_DFP3_SUPPOWT                  0x0200
                                  ATOM_DEVICE_DFP4_SUPPOWT                  0x0400
                                  ATOM_DEVICE_DFP5_SUPPOWT                  0x0800
                                  ATOM_DEVICE_WCD1_SUPPOWT                  0x0002
uwOthewDispwayMisc:                 bit[0]=0: INT15 cawwback function Get WCD EDID ( ax=4e08, bw=1b ) is not suppowted by SBIOS.
                                        =1: INT15 cawwback function Get WCD EDID ( ax=4e08, bw=1b ) is suppowted by SBIOS.
                                  bit[1]=0: INT15 cawwback function Get boot dispway( ax=4e08, bw=01h) is not suppowted by SBIOS
                                        =1: INT15 cawwback function Get boot dispway( ax=4e08, bw=01h) is suppowted by SBIOS
                                  bit[2]=0: INT15 cawwback function Get panew Expansion ( ax=4e08, bw=02h) is not suppowted by SBIOS
                                        =1: INT15 cawwback function Get panew Expansion ( ax=4e08, bw=02h) is suppowted by SBIOS
                                  bit[3]=0: VBIOS fast boot is disabwe
                                        =1: VBIOS fast boot is enabwe. ( VBIOS skip dispway device detection in evewy set mode if WCD panew is connect and WID is open)
uwGPUCapInfo:                     bit[0]=0: TMDS/HDMI Cohewent Mode use cascade PWW mode.
                                        =1: TMDS/HDMI Cohewent Mode use signew PWW mode.
                                  bit[1]=0: DP mode use cascade PWW mode ( New fow Twinity )
                                        =1: DP mode use singwe PWW mode
                                  bit[3]=0: Enabwe AUX HW mode detection wogic
                                        =1: Disabwe AUX HW mode detection wogic

uwSB_MMIO_Base_Addw:              Physicaw Base addwess to SB MMIO space. Dwivew needs to initiawize it fow SMU usage.

usWequestedPWMFweqInHz:           When it's set to 0x0 by SBIOS: the WCD BackWight is not contwowwed by GPU(SW).
                                  Any attempt to change BW using VBIOS function ow enabwe VawiBwi fwom PP tabwe is not effective since ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==0;

                                  When it's set to a non-zewo fwequency, the BackWight is contwowwed by GPU (SW) in one of two ways bewow:
                                  1. SW uses the GPU BW PWM output to contwow the BW, in chis case, this non-zewo fwequency detewmines what fweq GPU shouwd use;
                                  VBIOS wiww set up pwopew PWM fwequency and ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1,as the wesuwt,
                                  Changing BW using VBIOS function is functionaw in both dwivew and non-dwivew pwesent enviwonment;
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

                                  2. SW uses othew means to contwow BW (wike DPCD),this non-zewo fwequency sewves as a fwag onwy indicating
                                  that BW contwow fwom GPU is expected.
                                  VBIOS wiww NOT set up PWM fwequency but make ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1
                                  Changing BW using VBIOS function couwd be functionaw in both dwivew and non-dwivew pwesent enviwonment,but
                                  it's pew pwatfowm
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

ucHtcTmpWmt:                      Wefew to D18F3x64 bit[22:16], HtcTmpWmt.
                                  Thweshowd on vawue to entew HTC_active state.
ucHtcHystWmt:                     Wefew to D18F3x64 bit[27:24], HtcHystWmt.
                                  To cawcuwate thweshowd off vawue to exit HTC_active state, which is Thweshowd on vwaue minus ucHtcHystWmt.
uwMinEngineCwock:                 Minimum SCWK awwowed in 10kHz unit. This is cawcuwated based on WWCK Fuse settings.
uwSystemConfig:                   Bit[0]=0: PCIE Powew Gating Disabwed
                                        =1: PCIE Powew Gating Enabwed
                                  Bit[1]=0: DDW-DWW shut-down featuwe disabwed.
                                         1: DDW-DWW shut-down featuwe enabwed.
                                  Bit[2]=0: DDW-PWW Powew down featuwe disabwed.
                                         1: DDW-PWW Powew down featuwe enabwed.
uwCPUCapInfo:                     TBD
usNBP0Vowtage:                    VID fow vowtage on NB P0 State
usNBP1Vowtage:                    VID fow vowtage on NB P1 State
usNBP2Vowtage:                    VID fow vowtage on NB P2 State
usNBP3Vowtage:                    VID fow vowtage on NB P3 State
usBootUpNBVowtage:                Vowtage Index of GNB vowtage configuwed by SBIOS, which is suffcient to suppowt VBIOS DISPCWK wequiwement.
usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the stwuctuwe
usPanewWefweshWateWange:          Bit vectow fow WCD suppowted wefwesh wate wange. If DWW is wequestd by the pwatfowm, at weast two bits need to be set
                                  to indicate a wange.
                                  SUPPOWTED_WCD_WEFWESHWATE_30Hz          0x0004
                                  SUPPOWTED_WCD_WEFWESHWATE_40Hz          0x0008
                                  SUPPOWTED_WCD_WEFWESHWATE_50Hz          0x0010
                                  SUPPOWTED_WCD_WEFWESHWATE_60Hz          0x0020
ucMemowyType:                     [3:0]=1:DDW1;=2:DDW2;=3:DDW3.[7:4] is wesewved.
ucUMAChannewNumbew:                 System memowy channew numbews.
uwCSW_M3_AWB_CNTW_DEFAUWT[10]:    Awways with vawues fow CSW M3 awbitew fow defauwt
uwCSW_M3_AWB_CNTW_UVD[10]:        Awways with vawues fow CSW M3 awbitew fow UVD pwayback.
uwCSW_M3_AWB_CNTW_FS3D[10]:       Awways with vawues fow CSW M3 awbitew fow Fuww Scween 3D appwications.
sAvaiw_SCWK[5]:                   Awways to pwovide avaiwabe wist of SWCK and cowwesponding vowtage, owdew fwom wow to high
uwGMCWestoweWesetTime:            GMC powew westowe and GMC weset time to cawcuwate data weconnection watency. Unit in ns.
uwMinimumNCwk:                    Minimum NCWK speed among aww NB-Pstates to cawcuawte data weconnection watency. Unit in 10kHz.
uwIdweNCwk:                       NCWK speed whiwe memowy wuns in sewf-wefwesh state. Unit in 10kHz.
uwDDW_DWW_PowewUpTime:            DDW PHY DWW powew up time. Unit in ns.
uwDDW_PWW_PowewUpTime:            DDW PHY PWW powew up time. Unit in ns.
usPCIECwkSSPewcentage:            PCIE Cwock Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%.
usPCIECwkSSType:                  PCIE Cwock Spwead Spectwum Type. 0 fow Down spwead(defauwt); 1 fow Centew spwead.
usWvdsSSPewcentage:               WVDS panew ( not incwude eDP ) Spwead Spectwum Pewcentage in unit of 0.01%, =0, use VBIOS defauwt setting.
usWvdsSSpweadWateIn10Hz:          WVDS panew ( not incwude eDP ) Spwead Spectwum fwequency in unit of 10Hz, =0, use VBIOS defauwt setting.
usHDMISSPewcentage:               HDMI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usHDMISSpweadWateIn10Hz:          HDMI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.
usDVISSPewcentage:                DVI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usDVISSpweadWateIn10Hz:           DVI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.
usMaxWVDSPcwkFweqInSingweWink:    Max pixew cwock WVDS panew singwe wink, if=0 means VBIOS use defauwt thwehowd, wight now it is 85Mhz
ucWVDSMisc:                       [bit0] WVDS 888bit panew mode =0: WVDS 888 panew in WDI mode, =1: WVDS 888 panew in FPDI mode
                                  [bit1] WVDS panew wowew and uppew wink mapping =0: wowew wink and uppew wink not swap, =1: wowew wink and uppew wink awe swapped
                                  [bit2] WVDS 888bit pew cowow mode  =0: 666 bit pew cowow =1:888 bit pew cowow
                                  [bit3] WVDS pawametew ovewwide enabwe  =0: ucWvdsMisc pawametew awe not used =1: ucWvdsMisc pawametew shouwd be used
                                  [bit4] Powawity of signaw sent to digitaw BWON output pin. =0: not invewted(active high) =1: invewted ( active wow )
                                  [bit5] Twavid WVDS output vowtage ovewwide enabwe, when =1, use ucTwavisWVDSVowAdjust vawue to ovewwwite Twaivs wegistew WVDS_CTWW_4
ucTwavisWVDSVowAdjust             When ucWVDSMisc[5]=1,it means pwatfowm SBIOS want to ovewwwite TwavisWVDSVowtage. Then VBIOS wiww use ucTwavisWVDSVowAdjust
                                  vawue to pwogwam Twavis wegistew WVDS_CTWW_4
ucWVDSPwwOnSeqDIGONtoDE_in4Ms:    WVDS powew up sequence time in unit of 4ms, time deway fwom DIGON signaw active to data enabwe signaw active( DE ).
                                  =0 mean use VBIOS defauwt which is 8 ( 32ms ). The WVDS powew up sequence is as fowwowing: DIGON->DE->VAWY_BW->BWON.
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSPwwOnDEtoVAWY_BW_in4Ms:     WVDS powew up sequence time in unit of 4ms., time deway fwom DE( data enabwe ) active to Vawy Bwightness enabwe signaw active( VAWY_BW ).
                                  =0 mean use VBIOS defauwt which is 90 ( 360ms ). The WVDS powew up sequence is as fowwowing: DIGON->DE->VAWY_BW->BWON.
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSPwwOffVAWY_BWtoDE_in4Ms:    WVDS powew down sequence time in unit of 4ms, time deway fwom data enabwe ( DE ) signaw off to WCDVCC (DIGON) off.
                                  =0 mean use VBIOS defauwt deway which is 8 ( 32ms ). The WVDS powew down sequence is as fowwowing: BWON->VAWY_BW->DE->DIGON
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSPwwOffDEtoDIGON_in4Ms:      WVDS powew down sequence time in unit of 4ms, time deway fwom vawy bwightness enabwe signaw( VAWY_BW) off to data enabwe ( DE ) signaw off.
                                  =0 mean use VBIOS defauwt which is 90 ( 360ms ). The WVDS powew down sequence is as fowwowing: BWON->VAWY_BW->DE->DIGON
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSOffToOnDeway_in4Ms:         WVDS powew down sequence time in unit of 4ms. Time deway fwom DIGON signaw off to DIGON signaw active.
                                  =0 means to use VBIOS defauwt deway which is 125 ( 500ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms:
                                  WVDS powew up sequence time in unit of 4ms. Time deway fwom VAWY_BW signaw on to DWON signaw active.
                                  =0 means to use VBIOS defauwt deway which is 0 ( 0ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms:
                                  WVDS powew down sequence time in unit of 4ms. Time deway fwom BWON signaw off to VAWY_BW signaw off.
                                  =0 means to use VBIOS defauwt deway which is 0 ( 0ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucMinAwwowedBW_Wevew:             Wowest WCD backwight PWM wevew. This is customew pwatfowm specific pawametews. By defauwt it is 0.

uwNbpStateMemcwkFweq[4]:          system memowy cwock fwequncey in unit of 10Khz in diffewent NB pstate.

**********************************************************************************************************************/

// this IntegwateSystemInfoTabwe is used fow Kavewi & Kabini APU
typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_8
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG  uwBootUpEngineCwock;
  UWONG  uwDentistVCOFweq;
  UWONG  uwBootUpUMACwock;
  ATOM_CWK_VOWT_CAPABIWITY   sDISPCWK_Vowtage[4];
  UWONG  uwBootUpWeqDispwayVectow;
  UWONG  uwVBIOSMisc;
  UWONG  uwGPUCapInfo;
  UWONG  uwDISP_CWK2Fweq;
  USHOWT usWequestedPWMFweqInHz;
  UCHAW  ucHtcTmpWmt;
  UCHAW  ucHtcHystWmt;
  UWONG  uwWesewved2;
  UWONG  uwSystemConfig;
  UWONG  uwCPUCapInfo;
  UWONG  uwWesewved3;
  USHOWT usGPUWesewvedSysMemSize;
  USHOWT usExtDispConnInfoOffset;
  USHOWT usPanewWefweshWateWange;
  UCHAW  ucMemowyType;
  UCHAW  ucUMAChannewNumbew;
  UCHAW  stwVBIOSMsg[40];
  ATOM_TDP_CONFIG  asTdpConfig;
  UWONG  uwWesewved[19];
  ATOM_AVAIWABWE_SCWK_WIST   sAvaiw_SCWK[5];
  UWONG  uwGMCWestoweWesetTime;
  UWONG  uwWesewved4;
  UWONG  uwIdweNCwk;
  UWONG  uwDDW_DWW_PowewUpTime;
  UWONG  uwDDW_PWW_PowewUpTime;
  USHOWT usPCIECwkSSPewcentage;
  USHOWT usPCIECwkSSType;
  USHOWT usWvdsSSPewcentage;
  USHOWT usWvdsSSpweadWateIn10Hz;
  USHOWT usHDMISSPewcentage;
  USHOWT usHDMISSpweadWateIn10Hz;
  USHOWT usDVISSPewcentage;
  USHOWT usDVISSpweadWateIn10Hz;
  UWONG  uwGPUWesewvedSysMemBaseAddwWo;
  UWONG  uwGPUWesewvedSysMemBaseAddwHi;
  ATOM_CWK_VOWT_CAPABIWITY   s5thDISPCWK_Vowtage;
  UWONG  uwWesewved5;
  USHOWT usMaxWVDSPcwkFweqInSingweWink;
  UCHAW  ucWvdsMisc;
  UCHAW  ucTwavisWVDSVowAdjust;
  UCHAW  ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
  UCHAW  ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
  UCHAW  ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
  UCHAW  ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
  UCHAW  ucWVDSOffToOnDeway_in4Ms;
  UCHAW  ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
  UCHAW  ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
  UCHAW  ucMinAwwowedBW_Wevew;
  UWONG  uwWCDBitDepthContwowVaw;
  UWONG  uwNbpStateMemcwkFweq[4];
  UWONG  uwPSPVewsion;
  UWONG  uwNbpStateNCwkFweq[4];
  USHOWT usNBPStateVowtage[4];
  USHOWT usBootUpNBVowtage;
  USHOWT usWesewved2;
  ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO sExtDispConnInfo;
}ATOM_INTEGWATED_SYSTEM_INFO_V1_8;

/**********************************************************************************************************************
  ATOM_INTEGWATED_SYSTEM_INFO_V1_8 Descwiption
uwBootUpEngineCwock:              VBIOS bootup Engine cwock fwequency, in 10kHz unit. if it is equaw 0, then VBIOS use pwe-defined bootup engine cwock
uwDentistVCOFweq:                 Dentist VCO cwock in 10kHz unit.
uwBootUpUMACwock:                 System memowy boot up cwock fwequency in 10Khz unit.
sDISPCWK_Vowtage:                 Wepowt Dispway cwock fwequency wequiwement on GNB vowtage(up to 4 vowtage wevews).

uwBootUpWeqDispwayVectow:         VBIOS boot up dispway IDs, fowwowing awe suppowted devices in Twinity pwojects:
                                  ATOM_DEVICE_CWT1_SUPPOWT                  0x0001
                                  ATOM_DEVICE_DFP1_SUPPOWT                  0x0008
                                  ATOM_DEVICE_DFP6_SUPPOWT                  0x0040
                                  ATOM_DEVICE_DFP2_SUPPOWT                  0x0080
                                  ATOM_DEVICE_DFP3_SUPPOWT                  0x0200
                                  ATOM_DEVICE_DFP4_SUPPOWT                  0x0400
                                  ATOM_DEVICE_DFP5_SUPPOWT                  0x0800
                                  ATOM_DEVICE_WCD1_SUPPOWT                  0x0002

uwVBIOSMisc:                       Miscewwenous fwags fow VBIOS wequiwement and intewface
                                  bit[0]=0: INT15 cawwback function Get WCD EDID ( ax=4e08, bw=1b ) is not suppowted by SBIOS.
                                        =1: INT15 cawwback function Get WCD EDID ( ax=4e08, bw=1b ) is suppowted by SBIOS.
                                  bit[1]=0: INT15 cawwback function Get boot dispway( ax=4e08, bw=01h) is not suppowted by SBIOS
                                        =1: INT15 cawwback function Get boot dispway( ax=4e08, bw=01h) is suppowted by SBIOS
                                  bit[2]=0: INT15 cawwback function Get panew Expansion ( ax=4e08, bw=02h) is not suppowted by SBIOS
                                        =1: INT15 cawwback function Get panew Expansion ( ax=4e08, bw=02h) is suppowted by SBIOS
                                  bit[3]=0: VBIOS fast boot is disabwe
                                        =1: VBIOS fast boot is enabwe. ( VBIOS skip dispway device detection in evewy set mode if WCD panew is connect and WID is open)

uwGPUCapInfo:                     bit[0~2]= Wesewved
                                  bit[3]=0: Enabwe AUX HW mode detection wogic
                                        =1: Disabwe AUX HW mode detection wogic
                                  bit[4]=0: Disabwe DFS bypass featuwe
                                        =1: Enabwe DFS bypass featuwe

usWequestedPWMFweqInHz:           When it's set to 0x0 by SBIOS: the WCD BackWight is not contwowwed by GPU(SW).
                                  Any attempt to change BW using VBIOS function ow enabwe VawiBwi fwom PP tabwe is not effective since ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==0;

                                  When it's set to a non-zewo fwequency, the BackWight is contwowwed by GPU (SW) in one of two ways bewow:
                                  1. SW uses the GPU BW PWM output to contwow the BW, in chis case, this non-zewo fwequency detewmines what fweq GPU shouwd use;
                                  VBIOS wiww set up pwopew PWM fwequency and ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1,as the wesuwt,
                                  Changing BW using VBIOS function is functionaw in both dwivew and non-dwivew pwesent enviwonment;
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

                                  2. SW uses othew means to contwow BW (wike DPCD),this non-zewo fwequency sewves as a fwag onwy indicating
                                  that BW contwow fwom GPU is expected.
                                  VBIOS wiww NOT set up PWM fwequency but make ATOM_BIOS_INFO_BW_CONTWOWWED_BY_GPU==1
                                  Changing BW using VBIOS function couwd be functionaw in both dwivew and non-dwivew pwesent enviwonment,but
                                  it's pew pwatfowm
                                  and enabwing VawiBwi undew the dwivew enviwonment fwom PP tabwe is optionaw.

ucHtcTmpWmt:                      Wefew to D18F3x64 bit[22:16], HtcTmpWmt. Thweshowd on vawue to entew HTC_active state.
ucHtcHystWmt:                     Wefew to D18F3x64 bit[27:24], HtcHystWmt.
                                  To cawcuwate thweshowd off vawue to exit HTC_active state, which is Thweshowd on vwaue minus ucHtcHystWmt.

uwSystemConfig:                   Bit[0]=0: PCIE Powew Gating Disabwed
                                        =1: PCIE Powew Gating Enabwed
                                  Bit[1]=0: DDW-DWW shut-down featuwe disabwed.
                                         1: DDW-DWW shut-down featuwe enabwed.
                                  Bit[2]=0: DDW-PWW Powew down featuwe disabwed.
                                         1: DDW-PWW Powew down featuwe enabwed.
                                  Bit[3]=0: GNB DPM is disabwed
                                        =1: GNB DPM is enabwed
uwCPUCapInfo:                     TBD

usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the stwuctuwe
usPanewWefweshWateWange:          Bit vectow fow WCD suppowted wefwesh wate wange. If DWW is wequestd by the pwatfowm, at weast two bits need to be set
                                  to indicate a wange.
                                  SUPPOWTED_WCD_WEFWESHWATE_30Hz          0x0004
                                  SUPPOWTED_WCD_WEFWESHWATE_40Hz          0x0008
                                  SUPPOWTED_WCD_WEFWESHWATE_50Hz          0x0010
                                  SUPPOWTED_WCD_WEFWESHWATE_60Hz          0x0020

ucMemowyType:                     [3:0]=1:DDW1;=2:DDW2;=3:DDW3;=5:GDDW5; [7:4] is wesewved.
ucUMAChannewNumbew:                 System memowy channew numbews.

stwVBIOSMsg[40]:                  VBIOS boot up customized message stwing

sAvaiw_SCWK[5]:                   Awways to pwovide avaiwabe wist of SWCK and cowwesponding vowtage, owdew fwom wow to high

uwGMCWestoweWesetTime:            GMC powew westowe and GMC weset time to cawcuwate data weconnection watency. Unit in ns.
uwIdweNCwk:                       NCWK speed whiwe memowy wuns in sewf-wefwesh state, used to cawcuwate sewf-wefwesh watency. Unit in 10kHz.
uwDDW_DWW_PowewUpTime:            DDW PHY DWW powew up time. Unit in ns.
uwDDW_PWW_PowewUpTime:            DDW PHY PWW powew up time. Unit in ns.

usPCIECwkSSPewcentage:            PCIE Cwock Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%.
usPCIECwkSSType:                  PCIE Cwock Spwead Spectwum Type. 0 fow Down spwead(defauwt); 1 fow Centew spwead.
usWvdsSSPewcentage:               WVDS panew ( not incwude eDP ) Spwead Spectwum Pewcentage in unit of 0.01%, =0, use VBIOS defauwt setting.
usWvdsSSpweadWateIn10Hz:          WVDS panew ( not incwude eDP ) Spwead Spectwum fwequency in unit of 10Hz, =0, use VBIOS defauwt setting.
usHDMISSPewcentage:               HDMI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usHDMISSpweadWateIn10Hz:          HDMI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.
usDVISSPewcentage:                DVI Spwead Spectwum Pewcentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS defauwt setting.
usDVISSpweadWateIn10Hz:           DVI Spwead Spectwum fwequency in unit of 10Hz,  =0, use VBIOS defauwt setting.

usGPUWesewvedSysMemSize:          Wesewved system memowy size fow ACP engine in APU GNB, units in MB. 0/2/4MB based on CMOS options, cuwwent defauwt couwd be 0MB. KV onwy, not on KB.
uwGPUWesewvedSysMemBaseAddwWo:    Wow 32 bits base addwess to the wesewved system memowy.
uwGPUWesewvedSysMemBaseAddwHi:    High 32 bits base addwess to the wesewved system memowy.

usMaxWVDSPcwkFweqInSingweWink:    Max pixew cwock WVDS panew singwe wink, if=0 means VBIOS use defauwt thwehowd, wight now it is 85Mhz
ucWVDSMisc:                       [bit0] WVDS 888bit panew mode =0: WVDS 888 panew in WDI mode, =1: WVDS 888 panew in FPDI mode
                                  [bit1] WVDS panew wowew and uppew wink mapping =0: wowew wink and uppew wink not swap, =1: wowew wink and uppew wink awe swapped
                                  [bit2] WVDS 888bit pew cowow mode  =0: 666 bit pew cowow =1:888 bit pew cowow
                                  [bit3] WVDS pawametew ovewwide enabwe  =0: ucWvdsMisc pawametew awe not used =1: ucWvdsMisc pawametew shouwd be used
                                  [bit4] Powawity of signaw sent to digitaw BWON output pin. =0: not invewted(active high) =1: invewted ( active wow )
                                  [bit5] Twavid WVDS output vowtage ovewwide enabwe, when =1, use ucTwavisWVDSVowAdjust vawue to ovewwwite Twaivs wegistew WVDS_CTWW_4
ucTwavisWVDSVowAdjust             When ucWVDSMisc[5]=1,it means pwatfowm SBIOS want to ovewwwite TwavisWVDSVowtage. Then VBIOS wiww use ucTwavisWVDSVowAdjust
                                  vawue to pwogwam Twavis wegistew WVDS_CTWW_4
ucWVDSPwwOnSeqDIGONtoDE_in4Ms:
                                  WVDS powew up sequence time in unit of 4ms, time deway fwom DIGON signaw active to data enabwe signaw active( DE ).
                                  =0 mean use VBIOS defauwt which is 8 ( 32ms ). The WVDS powew up sequence is as fowwowing: DIGON->DE->VAWY_BW->BWON.
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSPwwOnDEtoVAWY_BW_in4Ms:
                                  WVDS powew up sequence time in unit of 4ms., time deway fwom DE( data enabwe ) active to Vawy Bwightness enabwe signaw active( VAWY_BW ).
                                  =0 mean use VBIOS defauwt which is 90 ( 360ms ). The WVDS powew up sequence is as fowwowing: DIGON->DE->VAWY_BW->BWON.
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSPwwOffVAWY_BWtoDE_in4Ms:
                                  WVDS powew down sequence time in unit of 4ms, time deway fwom data enabwe ( DE ) signaw off to WCDVCC (DIGON) off.
                                  =0 mean use VBIOS defauwt deway which is 8 ( 32ms ). The WVDS powew down sequence is as fowwowing: BWON->VAWY_BW->DE->DIGON
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSPwwOffDEtoDIGON_in4Ms:
                                   WVDS powew down sequence time in unit of 4ms, time deway fwom vawy bwightness enabwe signaw( VAWY_BW) off to data enabwe ( DE ) signaw off.
                                  =0 mean use VBIOS defauwt which is 90 ( 360ms ). The WVDS powew down sequence is as fowwowing: BWON->VAWY_BW->DE->DIGON
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSOffToOnDeway_in4Ms:
                                  WVDS powew down sequence time in unit of 4ms. Time deway fwom DIGON signaw off to DIGON signaw active.
                                  =0 means to use VBIOS defauwt deway which is 125 ( 500ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms:
                                  WVDS powew up sequence time in unit of 4ms. Time deway fwom VAWY_BW signaw on to DWON signaw active.
                                  =0 means to use VBIOS defauwt deway which is 0 ( 0ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.

ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms:
                                  WVDS powew down sequence time in unit of 4ms. Time deway fwom BWON signaw off to VAWY_BW signaw off.
                                  =0 means to use VBIOS defauwt deway which is 0 ( 0ms ).
                                  This pawametew is used by VBIOS onwy. VBIOS wiww patch WVDS_InfoTabwe.
ucMinAwwowedBW_Wevew:             Wowest WCD backwight PWM wevew. This is customew pwatfowm specific pawametews. By defauwt it is 0.

uwWCDBitDepthContwowVaw:          GPU dispway contwow encodew bit dithew contwow setting, used to pwogwam wegistew mmFMT_BIT_DEPTH_CONTWOW

uwNbpStateMemcwkFweq[4]:          system memowy cwock fwequncey in unit of 10Khz in diffewent NB P-State(P0, P1, P2 & P3).
uwNbpStateNCwkFweq[4]:            NB P-State NCwk fwequency in diffewent NB P-State
usNBPStateVowtage[4]:             NB P-State (P0/P1 & P2/P3) vowtage; NBP3 wefews to wowes vowtage
usBootUpNBVowtage:                NB P-State vowtage duwing boot up befowe dwivew woaded
sExtDispConnInfo:                 Dispway connectow infowmation tabwe pwovided to VBIOS

**********************************************************************************************************************/

typedef stwuct _ATOM_I2C_WEG_INFO
{
  UCHAW ucI2cWegIndex;
  UCHAW ucI2cWegVaw;
}ATOM_I2C_WEG_INFO;

// this IntegwateSystemInfoTabwe is used fow Cawwizo
typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_9
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG  uwBootUpEngineCwock;
  UWONG  uwDentistVCOFweq;
  UWONG  uwBootUpUMACwock;
  ATOM_CWK_VOWT_CAPABIWITY   sDISPCWK_Vowtage[4];       // no wongew used, keep it as is to avoid dwivew compiwing ewwow
  UWONG  uwBootUpWeqDispwayVectow;
  UWONG  uwVBIOSMisc;
  UWONG  uwGPUCapInfo;
  UWONG  uwDISP_CWK2Fweq;
  USHOWT usWequestedPWMFweqInHz;
  UCHAW  ucHtcTmpWmt;
  UCHAW  ucHtcHystWmt;
  UWONG  uwWesewved2;
  UWONG  uwSystemConfig;
  UWONG  uwCPUCapInfo;
  UWONG  uwWesewved3;
  USHOWT usGPUWesewvedSysMemSize;
  USHOWT usExtDispConnInfoOffset;
  USHOWT usPanewWefweshWateWange;
  UCHAW  ucMemowyType;
  UCHAW  ucUMAChannewNumbew;
  UCHAW  stwVBIOSMsg[40];
  ATOM_TDP_CONFIG  asTdpConfig;
  UCHAW  ucExtHDMIWeDwvSwvAddw;
  UCHAW  ucExtHDMIWeDwvWegNum;
  ATOM_I2C_WEG_INFO asExtHDMIWegSetting[9];
  UWONG  uwWesewved[2];
  ATOM_CWK_VOWT_CAPABIWITY_V2   sDispCwkVowtageMapping[8];
  ATOM_AVAIWABWE_SCWK_WIST   sAvaiw_SCWK[5];            // no wongew used, keep it as is to avoid dwivew compiwing ewwow
  UWONG  uwGMCWestoweWesetTime;
  UWONG  uwWesewved4;
  UWONG  uwIdweNCwk;
  UWONG  uwDDW_DWW_PowewUpTime;
  UWONG  uwDDW_PWW_PowewUpTime;
  USHOWT usPCIECwkSSPewcentage;
  USHOWT usPCIECwkSSType;
  USHOWT usWvdsSSPewcentage;
  USHOWT usWvdsSSpweadWateIn10Hz;
  USHOWT usHDMISSPewcentage;
  USHOWT usHDMISSpweadWateIn10Hz;
  USHOWT usDVISSPewcentage;
  USHOWT usDVISSpweadWateIn10Hz;
  UWONG  uwGPUWesewvedSysMemBaseAddwWo;
  UWONG  uwGPUWesewvedSysMemBaseAddwHi;
  UWONG  uwWesewved5[3];
  USHOWT usMaxWVDSPcwkFweqInSingweWink;
  UCHAW  ucWvdsMisc;
  UCHAW  ucTwavisWVDSVowAdjust;
  UCHAW  ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
  UCHAW  ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
  UCHAW  ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
  UCHAW  ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
  UCHAW  ucWVDSOffToOnDeway_in4Ms;
  UCHAW  ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
  UCHAW  ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
  UCHAW  ucMinAwwowedBW_Wevew;
  UWONG  uwWCDBitDepthContwowVaw;
  UWONG  uwNbpStateMemcwkFweq[4];          // onwy 2 wevew is changed.
  UWONG  uwPSPVewsion;
  UWONG  uwNbpStateNCwkFweq[4];
  USHOWT usNBPStateVowtage[4];
  USHOWT usBootUpNBVowtage;
  UCHAW  ucEDPv1_4VSMode;
  UCHAW  ucWesewved2;
  ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO sExtDispConnInfo;
}ATOM_INTEGWATED_SYSTEM_INFO_V1_9;


// definition fow ucEDPv1_4VSMode
#define EDP_VS_WEGACY_MODE                  0
#define EDP_VS_WOW_VDIFF_MODE               1
#define EDP_VS_HIGH_VDIFF_MODE              2
#define EDP_VS_STWETCH_MODE                 3
#define EDP_VS_SINGWE_VDIFF_MODE            4
#define EDP_VS_VAWIABWE_PWEM_MODE           5


// uwGPUCapInfo
#define SYS_INFO_V1_9_GPUCAPSINFO_DISABWE_AUX_MODE_DETECT                         0x08
#define SYS_INFO_V1_9_GPUCAPSINFO_ENABEW_DFS_BYPASS                               0x10
//uwGPUCapInfo[16]=1 indicate SMC fiwmwawe is abwe to suppowt GNB fast wesume function, so that dwivew can caww SMC to pwogwam most of GNB wegistew duwing wesuming, fwom MW
#define SYS_INFO_V1_9_GPUCAPSINFO_GNB_FAST_WESUME_CAPABWE                         0x00010000
//uwGPUCapInfo[18]=1 indicate the IOMMU is not avaiwabwe
#define SYS_INFO_V1_9_GPUCAPINFO_IOMMU_DISABWE                                    0x00040000
//uwGPUCapInfo[19]=1 indicate the MAWC Apewtuwe is opened.
#define SYS_INFO_V1_9_GPUCAPINFO_MAWC_APEWTUWE_ENABWE                             0x00080000


typedef stwuct _DPHY_TIMING_PAWA
{
    UCHAW  ucPwofiweID;       // SENSOW_PWOFIWES
    UWONG  ucPawa;
} DPHY_TIMING_PAWA;

typedef stwuct _DPHY_EWEC_PAWA
{
    USHOWT  usPawa[3];
} DPHY_EWEC_PAWA;

typedef stwuct _CAMEWA_MODUWE_INFO
{
    UCHAW    ucID;                    // 0: Weaw, 1: Fwont wight of usew, 2: Fwont weft of usew
    UCHAW    stwModuweName[8];
    DPHY_TIMING_PAWA asTimingPawa[6]; // Exact numbew is undew estimation and confiwmation fwom sensow vendow
} CAMEWA_MODUWE_INFO;

typedef stwuct _FWASHWIGHT_INFO
{
    UCHAW    ucID;         // 0: Weaw, 1: Fwont
    UCHAW    stwName[8];
} FWASHWIGHT_INFO;

typedef stwuct _CAMEWA_DATA
{
    UWONG                   uwVewsionCode;
    CAMEWA_MODUWE_INFO      asCamewaInfo[3];     // Assuming 3 camewa sensows max
    FWASHWIGHT_INFO         asFwashInfo;      // Assuming 1 fwashwight max
    DPHY_EWEC_PAWA          asDphyEwecPawa;
    UWONG                   uwCwcVaw;         // CWC
}CAMEWA_DATA;

typedef stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_10
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UWONG  uwBootUpEngineCwock;
  UWONG  uwDentistVCOFweq;
  UWONG  uwBootUpUMACwock;
  UWONG  uwWesewved0[8];
  UWONG  uwBootUpWeqDispwayVectow;
  UWONG  uwVBIOSMisc;
  UWONG  uwGPUCapInfo;
  UWONG  uwWesewved1;
  USHOWT usWequestedPWMFweqInHz;
  UCHAW  ucHtcTmpWmt;
  UCHAW  ucHtcHystWmt;
  UWONG  uwWesewved2;
  UWONG  uwSystemConfig;
  UWONG  uwCPUCapInfo;
  UWONG  uwWesewved3;
  USHOWT usGPUWesewvedSysMemSize;
  USHOWT usExtDispConnInfoOffset;
  USHOWT usPanewWefweshWateWange;
  UCHAW  ucMemowyType;
  UCHAW  ucUMAChannewNumbew;
  UWONG  uwMsgWesewved[10];
  ATOM_TDP_CONFIG  asTdpConfig;
  UWONG  uwWesewved[7];
  ATOM_CWK_VOWT_CAPABIWITY_V2   sDispCwkVowtageMapping[8];
  UWONG  uwWesewved6[10];
  UWONG  uwGMCWestoweWesetTime;
  UWONG  uwWesewved4;
  UWONG  uwIdweNCwk;
  UWONG  uwDDW_DWW_PowewUpTime;
  UWONG  uwDDW_PWW_PowewUpTime;
  USHOWT usPCIECwkSSPewcentage;
  USHOWT usPCIECwkSSType;
  USHOWT usWvdsSSPewcentage;
  USHOWT usWvdsSSpweadWateIn10Hz;
  USHOWT usHDMISSPewcentage;
  USHOWT usHDMISSpweadWateIn10Hz;
  USHOWT usDVISSPewcentage;
  USHOWT usDVISSpweadWateIn10Hz;
  UWONG  uwGPUWesewvedSysMemBaseAddwWo;
  UWONG  uwGPUWesewvedSysMemBaseAddwHi;
  UWONG  uwWesewved5[3];
  USHOWT usMaxWVDSPcwkFweqInSingweWink;
  UCHAW  ucWvdsMisc;
  UCHAW  ucTwavisWVDSVowAdjust;
  UCHAW  ucWVDSPwwOnSeqDIGONtoDE_in4Ms;
  UCHAW  ucWVDSPwwOnSeqDEtoVAWY_BW_in4Ms;
  UCHAW  ucWVDSPwwOffSeqVAWY_BWtoDE_in4Ms;
  UCHAW  ucWVDSPwwOffSeqDEtoDIGON_in4Ms;
  UCHAW  ucWVDSOffToOnDeway_in4Ms;
  UCHAW  ucWVDSPwwOnSeqVAWY_BWtoBWON_in4Ms;
  UCHAW  ucWVDSPwwOffSeqBWONtoVAWY_BW_in4Ms;
  UCHAW  ucMinAwwowedBW_Wevew;
  UWONG  uwWCDBitDepthContwowVaw;
  UWONG  uwNbpStateMemcwkFweq[2];
  UWONG  uwWesewved7[2];
  UWONG  uwPSPVewsion;
  UWONG  uwNbpStateNCwkFweq[4];
  USHOWT usNBPStateVowtage[4];
  USHOWT usBootUpNBVowtage;
  UCHAW  ucEDPv1_4VSMode;
  UCHAW  ucWesewved2;
  ATOM_EXTEWNAW_DISPWAY_CONNECTION_INFO sExtDispConnInfo;
  CAMEWA_DATA asCamewaInfo;
  UWONG  uwWesewved8[29];
}ATOM_INTEGWATED_SYSTEM_INFO_V1_10;


// this Tabwe is used fow Kavewi/Kabini APU
typedef stwuct _ATOM_FUSION_SYSTEM_INFO_V2
{
  ATOM_INTEGWATED_SYSTEM_INFO_V1_8    sIntegwatedSysInfo;       // wefew to ATOM_INTEGWATED_SYSTEM_INFO_V1_8 definition
  UWONG                               uwPowewpwayTabwe[128];    // Update comments hewe to wink new powewpway tabwe definition stwuctuwe
}ATOM_FUSION_SYSTEM_INFO_V2;


typedef stwuct _ATOM_FUSION_SYSTEM_INFO_V3
{
  ATOM_INTEGWATED_SYSTEM_INFO_V1_10   sIntegwatedSysInfo;           // wefew to ATOM_INTEGWATED_SYSTEM_INFO_V1_8 definition
  UWONG                               uwPowewpwayTabwe[192];        // Wesewve 768 bytes space fow PowewPwayInfoTabwe
}ATOM_FUSION_SYSTEM_INFO_V3;

#define FUSION_V3_OFFSET_FWOM_TOP_OF_FB 0x800

/**************************************************************************/
// This powtion is onwy used when ext thewmaw chip ow engine/memowy cwock SS chip is popuwated on a design
//Memowy SS Info Tabwe
//Define Memowy Cwock SS chip ID
#define ICS91719  1
#define ICS91720  2

//Define one stwuctuwe to infowm SW a "bwock of data" wwiting to extewnaw SS chip via I2C pwotocow
typedef stwuct _ATOM_I2C_DATA_WECOWD
{
  UCHAW         ucNunbewOfBytes;                                              //Indicates how many bytes SW needs to wwite to the extewnaw ASIC fow one bwock, besides to "Stawt" and "Stop"
  UCHAW         ucI2CData[];                                                  //I2C data in bytes, shouwd be wess than 16 bytes usuawwy
}ATOM_I2C_DATA_WECOWD;


//Define one stwuctuwe to infowm SW how many bwocks of data wwiting to extewnaw SS chip via I2C pwotocow, in addition to othew infowmation
typedef stwuct _ATOM_I2C_DEVICE_SETUP_INFO
{
  ATOM_I2C_ID_CONFIG_ACCESS       sucI2cId;               //I2C wine and HW/SW assisted cap.
  UCHAW                              ucSSChipID;             //SS chip being used
  UCHAW                              ucSSChipSwaveAddw;      //Swave Addwess to set up this SS chip
  UCHAW                           ucNumOfI2CDataWecowds;  //numbew of data bwock
  ATOM_I2C_DATA_WECOWD            asI2CData[];
}ATOM_I2C_DEVICE_SETUP_INFO;

//==========================================================================================
typedef stwuct  _ATOM_ASIC_MVDD_INFO
{
  ATOM_COMMON_TABWE_HEADEW         sHeadew;
  ATOM_I2C_DEVICE_SETUP_INFO      asI2CSetup[];
}ATOM_ASIC_MVDD_INFO;

//==========================================================================================
#define ATOM_MCWK_SS_INFO         ATOM_ASIC_MVDD_INFO

//==========================================================================================
/**************************************************************************/

typedef stwuct _ATOM_ASIC_SS_ASSIGNMENT
{
   UWONG                        uwTawgetCwockWange;                  //Cwock Out fwequence (VCO ), in unit of 10Khz
  USHOWT              usSpweadSpectwumPewcentage;      //in unit of 0.01%
   USHOWT                     usSpweadWateInKhz;                  //in unit of kHz, moduwation fweq
  UCHAW               ucCwockIndication;                 //Indicate which cwock souwce needs SS
   UCHAW                        ucSpweadSpectwumMode;               //Bit1=0 Down Spwead,=1 Centew Spwead.
   UCHAW                        ucWesewved[2];
}ATOM_ASIC_SS_ASSIGNMENT;

//Define ucCwockIndication, SW uses the IDs bewow to seawch if the SS is wequwied/enabwed on a cwock bwanch/signaw type.
//SS is not wequiwed ow enabwed if a match is not found.
#define ASIC_INTEWNAW_MEMOWY_SS            1
#define ASIC_INTEWNAW_ENGINE_SS            2
#define ASIC_INTEWNAW_UVD_SS             3
#define ASIC_INTEWNAW_SS_ON_TMDS         4
#define ASIC_INTEWNAW_SS_ON_HDMI         5
#define ASIC_INTEWNAW_SS_ON_WVDS         6
#define ASIC_INTEWNAW_SS_ON_DP           7
#define ASIC_INTEWNAW_SS_ON_DCPWW        8
#define ASIC_EXTEWNAW_SS_ON_DP_CWOCK     9
#define ASIC_INTEWNAW_VCE_SS             10
#define ASIC_INTEWNAW_GPUPWW_SS          11


typedef stwuct _ATOM_ASIC_SS_ASSIGNMENT_V2
{
   UWONG                        uwTawgetCwockWange;                  //Fow mem/engine/uvd, Cwock Out fwequence (VCO ), in unit of 10Khz
                                                    //Fow TMDS/HDMI/WVDS, it is pixew cwock , fow DP, it is wink cwock ( 27000 ow 16200 )
  USHOWT              usSpweadSpectwumPewcentage;      //in unit of 0.01%
   USHOWT                     usSpweadWateIn10Hz;                  //in unit of 10Hz, moduwation fweq
  UCHAW               ucCwockIndication;                 //Indicate which cwock souwce needs SS
   UCHAW                        ucSpweadSpectwumMode;               //Bit0=0 Down Spwead,=1 Centew Spwead, bit1=0: intewnaw SS bit1=1: extewnaw SS
   UCHAW                        ucWesewved[2];
}ATOM_ASIC_SS_ASSIGNMENT_V2;

//ucSpweadSpectwumMode
//#define ATOM_SS_DOWN_SPWEAD_MODE_MASK          0x00000000
//#define ATOM_SS_DOWN_SPWEAD_MODE               0x00000000
//#define ATOM_SS_CENTWE_SPWEAD_MODE_MASK        0x00000001
//#define ATOM_SS_CENTWE_SPWEAD_MODE             0x00000001
//#define ATOM_INTEWNAW_SS_MASK                  0x00000000
//#define ATOM_EXTEWNAW_SS_MASK                  0x00000002

typedef stwuct _ATOM_ASIC_INTEWNAW_SS_INFO
{
  ATOM_COMMON_TABWE_HEADEW         sHeadew;
  ATOM_ASIC_SS_ASSIGNMENT            asSpweadSpectwum[4];
}ATOM_ASIC_INTEWNAW_SS_INFO;

typedef stwuct _ATOM_ASIC_INTEWNAW_SS_INFO_V2
{
  ATOM_COMMON_TABWE_HEADEW         sHeadew;
  ATOM_ASIC_SS_ASSIGNMENT_V2        asSpweadSpectwum[];      //this is point onwy.
}ATOM_ASIC_INTEWNAW_SS_INFO_V2;

typedef stwuct _ATOM_ASIC_SS_ASSIGNMENT_V3
{
   UWONG                        uwTawgetCwockWange;                  //Fow mem/engine/uvd, Cwock Out fwequence (VCO ), in unit of 10Khz
                                                    //Fow TMDS/HDMI/WVDS, it is pixew cwock , fow DP, it is wink cwock ( 27000 ow 16200 )
  USHOWT              usSpweadSpectwumPewcentage;      //in unit of 0.01% ow 0.001%, decided by ucSpweadSpectwumMode bit4
   USHOWT                     usSpweadWateIn10Hz;                  //in unit of 10Hz, moduwation fweq
  UCHAW               ucCwockIndication;                 //Indicate which cwock souwce needs SS
   UCHAW                        ucSpweadSpectwumMode;               //Bit0=0 Down Spwead,=1 Centew Spwead, bit1=0: intewnaw SS bit1=1: extewnaw SS
   UCHAW                        ucWesewved[2];
}ATOM_ASIC_SS_ASSIGNMENT_V3;

//ATOM_ASIC_SS_ASSIGNMENT_V3.ucSpweadSpectwumMode
#define SS_MODE_V3_CENTWE_SPWEAD_MASK             0x01
#define SS_MODE_V3_EXTEWNAW_SS_MASK               0x02
#define SS_MODE_V3_PEWCENTAGE_DIV_BY_1000_MASK    0x10

typedef stwuct _ATOM_ASIC_INTEWNAW_SS_INFO_V3
{
  ATOM_COMMON_TABWE_HEADEW         sHeadew;
  ATOM_ASIC_SS_ASSIGNMENT_V3        asSpweadSpectwum[];      //this is pointew onwy.
}ATOM_ASIC_INTEWNAW_SS_INFO_V3;


//==============================Scwatch Pad Definition Powtion===============================
#define ATOM_DEVICE_CONNECT_INFO_DEF  0
#define ATOM_WOM_WOCATION_DEF         1
#define ATOM_TV_STANDAWD_DEF          2
#define ATOM_ACTIVE_INFO_DEF          3
#define ATOM_WCD_INFO_DEF             4
#define ATOM_DOS_WEQ_INFO_DEF         5
#define ATOM_ACC_CHANGE_INFO_DEF      6
#define ATOM_DOS_MODE_INFO_DEF        7
#define ATOM_I2C_CHANNEW_STATUS_DEF   8
#define ATOM_I2C_CHANNEW_STATUS1_DEF  9
#define ATOM_INTEWNAW_TIMEW_DEF       10

// BIOS_0_SCWATCH Definition
#define ATOM_S0_CWT1_MONO               0x00000001W
#define ATOM_S0_CWT1_COWOW              0x00000002W
#define ATOM_S0_CWT1_MASK               (ATOM_S0_CWT1_MONO+ATOM_S0_CWT1_COWOW)

#define ATOM_S0_TV1_COMPOSITE_A         0x00000004W
#define ATOM_S0_TV1_SVIDEO_A            0x00000008W
#define ATOM_S0_TV1_MASK_A              (ATOM_S0_TV1_COMPOSITE_A+ATOM_S0_TV1_SVIDEO_A)

#define ATOM_S0_CV_A                    0x00000010W
#define ATOM_S0_CV_DIN_A                0x00000020W
#define ATOM_S0_CV_MASK_A               (ATOM_S0_CV_A+ATOM_S0_CV_DIN_A)


#define ATOM_S0_CWT2_MONO               0x00000100W
#define ATOM_S0_CWT2_COWOW              0x00000200W
#define ATOM_S0_CWT2_MASK               (ATOM_S0_CWT2_MONO+ATOM_S0_CWT2_COWOW)

#define ATOM_S0_TV1_COMPOSITE           0x00000400W
#define ATOM_S0_TV1_SVIDEO              0x00000800W
#define ATOM_S0_TV1_SCAWT               0x00004000W
#define ATOM_S0_TV1_MASK                (ATOM_S0_TV1_COMPOSITE+ATOM_S0_TV1_SVIDEO+ATOM_S0_TV1_SCAWT)

#define ATOM_S0_CV                      0x00001000W
#define ATOM_S0_CV_DIN                  0x00002000W
#define ATOM_S0_CV_MASK                 (ATOM_S0_CV+ATOM_S0_CV_DIN)

#define ATOM_S0_DFP1                    0x00010000W
#define ATOM_S0_DFP2                    0x00020000W
#define ATOM_S0_WCD1                    0x00040000W
#define ATOM_S0_WCD2                    0x00080000W
#define ATOM_S0_DFP6                    0x00100000W
#define ATOM_S0_DFP3                    0x00200000W
#define ATOM_S0_DFP4                    0x00400000W
#define ATOM_S0_DFP5                    0x00800000W


#define ATOM_S0_DFP_MASK                ATOM_S0_DFP1 | ATOM_S0_DFP2 | ATOM_S0_DFP3 | ATOM_S0_DFP4 | ATOM_S0_DFP5 | ATOM_S0_DFP6

#define ATOM_S0_FAD_WEGISTEW_BUG        0x02000000W // If set, indicates we awe wunning a PCIE asic with
                                                    // the FAD/HDP weg access bug.  Bit is wead by DAW, this is obsowete fwom WV5xx

#define ATOM_S0_THEWMAW_STATE_MASK      0x1C000000W
#define ATOM_S0_THEWMAW_STATE_SHIFT     26

#define ATOM_S0_SYSTEM_POWEW_STATE_MASK 0xE0000000W
#define ATOM_S0_SYSTEM_POWEW_STATE_SHIFT 29

#define ATOM_S0_SYSTEM_POWEW_STATE_VAWUE_AC     1
#define ATOM_S0_SYSTEM_POWEW_STATE_VAWUE_DC     2
#define ATOM_S0_SYSTEM_POWEW_STATE_VAWUE_WITEAC 3
#define ATOM_S0_SYSTEM_POWEW_STATE_VAWUE_WIT2AC 4

//Byte awigned defintion fow BIOS usage
#define ATOM_S0_CWT1_MONOb0             0x01
#define ATOM_S0_CWT1_COWOWb0            0x02
#define ATOM_S0_CWT1_MASKb0             (ATOM_S0_CWT1_MONOb0+ATOM_S0_CWT1_COWOWb0)

#define ATOM_S0_TV1_COMPOSITEb0         0x04
#define ATOM_S0_TV1_SVIDEOb0            0x08
#define ATOM_S0_TV1_MASKb0              (ATOM_S0_TV1_COMPOSITEb0+ATOM_S0_TV1_SVIDEOb0)

#define ATOM_S0_CVb0                    0x10
#define ATOM_S0_CV_DINb0                0x20
#define ATOM_S0_CV_MASKb0               (ATOM_S0_CVb0+ATOM_S0_CV_DINb0)

#define ATOM_S0_CWT2_MONOb1             0x01
#define ATOM_S0_CWT2_COWOWb1            0x02
#define ATOM_S0_CWT2_MASKb1             (ATOM_S0_CWT2_MONOb1+ATOM_S0_CWT2_COWOWb1)

#define ATOM_S0_TV1_COMPOSITEb1         0x04
#define ATOM_S0_TV1_SVIDEOb1            0x08
#define ATOM_S0_TV1_SCAWTb1             0x40
#define ATOM_S0_TV1_MASKb1              (ATOM_S0_TV1_COMPOSITEb1+ATOM_S0_TV1_SVIDEOb1+ATOM_S0_TV1_SCAWTb1)

#define ATOM_S0_CVb1                    0x10
#define ATOM_S0_CV_DINb1                0x20
#define ATOM_S0_CV_MASKb1               (ATOM_S0_CVb1+ATOM_S0_CV_DINb1)

#define ATOM_S0_DFP1b2                  0x01
#define ATOM_S0_DFP2b2                  0x02
#define ATOM_S0_WCD1b2                  0x04
#define ATOM_S0_WCD2b2                  0x08
#define ATOM_S0_DFP6b2                  0x10
#define ATOM_S0_DFP3b2                  0x20
#define ATOM_S0_DFP4b2                  0x40
#define ATOM_S0_DFP5b2                  0x80


#define ATOM_S0_THEWMAW_STATE_MASKb3    0x1C
#define ATOM_S0_THEWMAW_STATE_SHIFTb3   2

#define ATOM_S0_SYSTEM_POWEW_STATE_MASKb3 0xE0
#define ATOM_S0_WCD1_SHIFT              18

// BIOS_1_SCWATCH Definition
#define ATOM_S1_WOM_WOCATION_MASK       0x0000FFFFW
#define ATOM_S1_PCI_BUS_DEV_MASK        0xFFFF0000W

//   BIOS_2_SCWATCH Definition
#define ATOM_S2_TV1_STANDAWD_MASK       0x0000000FW
#define ATOM_S2_CUWWENT_BW_WEVEW_MASK   0x0000FF00W
#define ATOM_S2_CUWWENT_BW_WEVEW_SHIFT  8

#define ATOM_S2_FOWCEDWOWPWWMODE_STATE_MASK       0x0C000000W
#define ATOM_S2_FOWCEDWOWPWWMODE_STATE_MASK_SHIFT 26
#define ATOM_S2_FOWCEDWOWPWWMODE_STATE_CHANGE     0x10000000W

#define ATOM_S2_DEVICE_DPMS_STATE       0x00010000W
#define ATOM_S2_VWI_BWIGHT_ENABWE       0x20000000W

#define ATOM_S2_DISPWAY_WOTATION_0_DEGWEE     0x0
#define ATOM_S2_DISPWAY_WOTATION_90_DEGWEE    0x1
#define ATOM_S2_DISPWAY_WOTATION_180_DEGWEE   0x2
#define ATOM_S2_DISPWAY_WOTATION_270_DEGWEE   0x3
#define ATOM_S2_DISPWAY_WOTATION_DEGWEE_SHIFT 30
#define ATOM_S2_DISPWAY_WOTATION_ANGWE_MASK   0xC0000000W


//Byte awigned defintion fow BIOS usage
#define ATOM_S2_TV1_STANDAWD_MASKb0     0x0F
#define ATOM_S2_CUWWENT_BW_WEVEW_MASKb1 0xFF
#define ATOM_S2_DEVICE_DPMS_STATEb2     0x01

#define ATOM_S2_TMDS_COHEWENT_MODEb3    0x10          // used by VBIOS code onwy, use cohewent mode fow TMDS/HDMI mode
#define ATOM_S2_VWI_BWIGHT_ENABWEb3     0x20
#define ATOM_S2_WOTATION_STATE_MASKb3   0xC0


// BIOS_3_SCWATCH Definition
#define ATOM_S3_CWT1_ACTIVE             0x00000001W
#define ATOM_S3_WCD1_ACTIVE             0x00000002W
#define ATOM_S3_TV1_ACTIVE              0x00000004W
#define ATOM_S3_DFP1_ACTIVE             0x00000008W
#define ATOM_S3_CWT2_ACTIVE             0x00000010W
#define ATOM_S3_WCD2_ACTIVE             0x00000020W
#define ATOM_S3_DFP6_ACTIVE             0x00000040W
#define ATOM_S3_DFP2_ACTIVE             0x00000080W
#define ATOM_S3_CV_ACTIVE               0x00000100W
#define ATOM_S3_DFP3_ACTIVE             0x00000200W
#define ATOM_S3_DFP4_ACTIVE             0x00000400W
#define ATOM_S3_DFP5_ACTIVE             0x00000800W


#define ATOM_S3_DEVICE_ACTIVE_MASK      0x00000FFFW

#define ATOM_S3_WCD_FUWWEXPANSION_ACTIVE         0x00001000W
#define ATOM_S3_WCD_EXPANSION_ASPEC_WATIO_ACTIVE 0x00002000W

#define ATOM_S3_CWT1_CWTC_ACTIVE        0x00010000W
#define ATOM_S3_WCD1_CWTC_ACTIVE        0x00020000W
#define ATOM_S3_TV1_CWTC_ACTIVE         0x00040000W
#define ATOM_S3_DFP1_CWTC_ACTIVE        0x00080000W
#define ATOM_S3_CWT2_CWTC_ACTIVE        0x00100000W
#define ATOM_S3_WCD2_CWTC_ACTIVE        0x00200000W
#define ATOM_S3_DFP6_CWTC_ACTIVE        0x00400000W
#define ATOM_S3_DFP2_CWTC_ACTIVE        0x00800000W
#define ATOM_S3_CV_CWTC_ACTIVE          0x01000000W
#define ATOM_S3_DFP3_CWTC_ACTIVE        0x02000000W
#define ATOM_S3_DFP4_CWTC_ACTIVE        0x04000000W
#define ATOM_S3_DFP5_CWTC_ACTIVE        0x08000000W


#define ATOM_S3_DEVICE_CWTC_ACTIVE_MASK 0x0FFF0000W
#define ATOM_S3_ASIC_GUI_ENGINE_HUNG    0x20000000W
//Bewow two definitions awe not suppowted in ppwib, but in the owd powewpway in DAW
#define ATOM_S3_AWWOW_FAST_PWW_SWITCH   0x40000000W
#define ATOM_S3_WQST_GPU_USE_MIN_PWW    0x80000000W



//Byte awigned defintion fow BIOS usage
#define ATOM_S3_CWT1_ACTIVEb0           0x01
#define ATOM_S3_WCD1_ACTIVEb0           0x02
#define ATOM_S3_TV1_ACTIVEb0            0x04
#define ATOM_S3_DFP1_ACTIVEb0           0x08
#define ATOM_S3_CWT2_ACTIVEb0           0x10
#define ATOM_S3_WCD2_ACTIVEb0           0x20
#define ATOM_S3_DFP6_ACTIVEb0           0x40
#define ATOM_S3_DFP2_ACTIVEb0           0x80
#define ATOM_S3_CV_ACTIVEb1             0x01
#define ATOM_S3_DFP3_ACTIVEb1           0x02
#define ATOM_S3_DFP4_ACTIVEb1           0x04
#define ATOM_S3_DFP5_ACTIVEb1           0x08


#define ATOM_S3_ACTIVE_CWTC1w0          0xFFF

#define ATOM_S3_CWT1_CWTC_ACTIVEb2      0x01
#define ATOM_S3_WCD1_CWTC_ACTIVEb2      0x02
#define ATOM_S3_TV1_CWTC_ACTIVEb2       0x04
#define ATOM_S3_DFP1_CWTC_ACTIVEb2      0x08
#define ATOM_S3_CWT2_CWTC_ACTIVEb2      0x10
#define ATOM_S3_WCD2_CWTC_ACTIVEb2      0x20
#define ATOM_S3_DFP6_CWTC_ACTIVEb2      0x40
#define ATOM_S3_DFP2_CWTC_ACTIVEb2      0x80
#define ATOM_S3_CV_CWTC_ACTIVEb3        0x01
#define ATOM_S3_DFP3_CWTC_ACTIVEb3      0x02
#define ATOM_S3_DFP4_CWTC_ACTIVEb3      0x04
#define ATOM_S3_DFP5_CWTC_ACTIVEb3      0x08


#define ATOM_S3_ACTIVE_CWTC2w1          0xFFF


// BIOS_4_SCWATCH Definition
#define ATOM_S4_WCD1_PANEW_ID_MASK      0x000000FFW
#define ATOM_S4_WCD1_WEFWESH_MASK       0x0000FF00W
#define ATOM_S4_WCD1_WEFWESH_SHIFT      8

//Byte awigned defintion fow BIOS usage
#define ATOM_S4_WCD1_PANEW_ID_MASKb0    0x0FF
#define ATOM_S4_WCD1_WEFWESH_MASKb1     ATOM_S4_WCD1_PANEW_ID_MASKb0
#define ATOM_S4_VWAM_INFO_MASKb2        ATOM_S4_WCD1_PANEW_ID_MASKb0

// BIOS_5_SCWATCH Definition, BIOS_5_SCWATCH is used by Fiwmwawe onwy !!!!
#define ATOM_S5_DOS_WEQ_CWT1b0          0x01
#define ATOM_S5_DOS_WEQ_WCD1b0          0x02
#define ATOM_S5_DOS_WEQ_TV1b0           0x04
#define ATOM_S5_DOS_WEQ_DFP1b0          0x08
#define ATOM_S5_DOS_WEQ_CWT2b0          0x10
#define ATOM_S5_DOS_WEQ_WCD2b0          0x20
#define ATOM_S5_DOS_WEQ_DFP6b0          0x40
#define ATOM_S5_DOS_WEQ_DFP2b0          0x80
#define ATOM_S5_DOS_WEQ_CVb1            0x01
#define ATOM_S5_DOS_WEQ_DFP3b1          0x02
#define ATOM_S5_DOS_WEQ_DFP4b1          0x04
#define ATOM_S5_DOS_WEQ_DFP5b1          0x08


#define ATOM_S5_DOS_WEQ_DEVICEw0        0x0FFF

#define ATOM_S5_DOS_WEQ_CWT1            0x0001
#define ATOM_S5_DOS_WEQ_WCD1            0x0002
#define ATOM_S5_DOS_WEQ_TV1             0x0004
#define ATOM_S5_DOS_WEQ_DFP1            0x0008
#define ATOM_S5_DOS_WEQ_CWT2            0x0010
#define ATOM_S5_DOS_WEQ_WCD2            0x0020
#define ATOM_S5_DOS_WEQ_DFP6            0x0040
#define ATOM_S5_DOS_WEQ_DFP2            0x0080
#define ATOM_S5_DOS_WEQ_CV              0x0100
#define ATOM_S5_DOS_WEQ_DFP3            0x0200
#define ATOM_S5_DOS_WEQ_DFP4            0x0400
#define ATOM_S5_DOS_WEQ_DFP5            0x0800

#define ATOM_S5_DOS_FOWCE_CWT1b2        ATOM_S5_DOS_WEQ_CWT1b0
#define ATOM_S5_DOS_FOWCE_TV1b2         ATOM_S5_DOS_WEQ_TV1b0
#define ATOM_S5_DOS_FOWCE_CWT2b2        ATOM_S5_DOS_WEQ_CWT2b0
#define ATOM_S5_DOS_FOWCE_CVb3          ATOM_S5_DOS_WEQ_CVb1
#define ATOM_S5_DOS_FOWCE_DEVICEw1      (ATOM_S5_DOS_FOWCE_CWT1b2+ATOM_S5_DOS_FOWCE_TV1b2+ATOM_S5_DOS_FOWCE_CWT2b2+\
                                        (ATOM_S5_DOS_FOWCE_CVb3<<8))
// BIOS_6_SCWATCH Definition
#define ATOM_S6_DEVICE_CHANGE           0x00000001W
#define ATOM_S6_SCAWEW_CHANGE           0x00000002W
#define ATOM_S6_WID_CHANGE              0x00000004W
#define ATOM_S6_DOCKING_CHANGE          0x00000008W
#define ATOM_S6_ACC_MODE                0x00000010W
#define ATOM_S6_EXT_DESKTOP_MODE        0x00000020W
#define ATOM_S6_WID_STATE               0x00000040W
#define ATOM_S6_DOCK_STATE              0x00000080W
#define ATOM_S6_CWITICAW_STATE          0x00000100W
#define ATOM_S6_HW_I2C_BUSY_STATE       0x00000200W
#define ATOM_S6_THEWMAW_STATE_CHANGE    0x00000400W
#define ATOM_S6_INTEWWUPT_SET_BY_BIOS   0x00000800W
#define ATOM_S6_WEQ_WCD_EXPANSION_FUWW         0x00001000W //Nowmaw expansion Wequest bit fow WCD
#define ATOM_S6_WEQ_WCD_EXPANSION_ASPEC_WATIO  0x00002000W //Aspect watio expansion Wequest bit fow WCD

#define ATOM_S6_DISPWAY_STATE_CHANGE    0x00004000W        //This bit is wecycwed when ATOM_BIOS_INFO_BIOS_SCWATCH6_SCW2_WEDEFINE is set,pweviouswy it's SCW2_H_expansion
#define ATOM_S6_I2C_STATE_CHANGE        0x00008000W        //This bit is wecycwed,when ATOM_BIOS_INFO_BIOS_SCWATCH6_SCW2_WEDEFINE is set,pweviouswy it's SCW2_V_expansion

#define ATOM_S6_ACC_WEQ_CWT1            0x00010000W
#define ATOM_S6_ACC_WEQ_WCD1            0x00020000W
#define ATOM_S6_ACC_WEQ_TV1             0x00040000W
#define ATOM_S6_ACC_WEQ_DFP1            0x00080000W
#define ATOM_S6_ACC_WEQ_CWT2            0x00100000W
#define ATOM_S6_ACC_WEQ_WCD2            0x00200000W
#define ATOM_S6_ACC_WEQ_DFP6            0x00400000W
#define ATOM_S6_ACC_WEQ_DFP2            0x00800000W
#define ATOM_S6_ACC_WEQ_CV              0x01000000W
#define ATOM_S6_ACC_WEQ_DFP3                  0x02000000W
#define ATOM_S6_ACC_WEQ_DFP4                  0x04000000W
#define ATOM_S6_ACC_WEQ_DFP5                  0x08000000W

#define ATOM_S6_ACC_WEQ_MASK                0x0FFF0000W
#define ATOM_S6_SYSTEM_POWEW_MODE_CHANGE    0x10000000W
#define ATOM_S6_ACC_BWOCK_DISPWAY_SWITCH    0x20000000W
#define ATOM_S6_VWI_BWIGHTNESS_CHANGE       0x40000000W
#define ATOM_S6_CONFIG_DISPWAY_CHANGE_MASK  0x80000000W

//Byte awigned defintion fow BIOS usage
#define ATOM_S6_DEVICE_CHANGEb0         0x01
#define ATOM_S6_SCAWEW_CHANGEb0         0x02
#define ATOM_S6_WID_CHANGEb0            0x04
#define ATOM_S6_DOCKING_CHANGEb0        0x08
#define ATOM_S6_ACC_MODEb0              0x10
#define ATOM_S6_EXT_DESKTOP_MODEb0      0x20
#define ATOM_S6_WID_STATEb0             0x40
#define ATOM_S6_DOCK_STATEb0            0x80
#define ATOM_S6_CWITICAW_STATEb1        0x01
#define ATOM_S6_HW_I2C_BUSY_STATEb1     0x02
#define ATOM_S6_THEWMAW_STATE_CHANGEb1  0x04
#define ATOM_S6_INTEWWUPT_SET_BY_BIOSb1 0x08
#define ATOM_S6_WEQ_WCD_EXPANSION_FUWWb1        0x10
#define ATOM_S6_WEQ_WCD_EXPANSION_ASPEC_WATIOb1 0x20

#define ATOM_S6_ACC_WEQ_CWT1b2          0x01
#define ATOM_S6_ACC_WEQ_WCD1b2          0x02
#define ATOM_S6_ACC_WEQ_TV1b2           0x04
#define ATOM_S6_ACC_WEQ_DFP1b2          0x08
#define ATOM_S6_ACC_WEQ_CWT2b2          0x10
#define ATOM_S6_ACC_WEQ_WCD2b2          0x20
#define ATOM_S6_ACC_WEQ_DFP6b2          0x40
#define ATOM_S6_ACC_WEQ_DFP2b2          0x80
#define ATOM_S6_ACC_WEQ_CVb3            0x01
#define ATOM_S6_ACC_WEQ_DFP3b3          0x02
#define ATOM_S6_ACC_WEQ_DFP4b3          0x04
#define ATOM_S6_ACC_WEQ_DFP5b3          0x08

#define ATOM_S6_ACC_WEQ_DEVICEw1        ATOM_S5_DOS_WEQ_DEVICEw0
#define ATOM_S6_SYSTEM_POWEW_MODE_CHANGEb3 0x10
#define ATOM_S6_ACC_BWOCK_DISPWAY_SWITCHb3 0x20
#define ATOM_S6_VWI_BWIGHTNESS_CHANGEb3    0x40
#define ATOM_S6_CONFIG_DISPWAY_CHANGEb3    0x80

#define ATOM_S6_DEVICE_CHANGE_SHIFT             0
#define ATOM_S6_SCAWEW_CHANGE_SHIFT             1
#define ATOM_S6_WID_CHANGE_SHIFT                2
#define ATOM_S6_DOCKING_CHANGE_SHIFT            3
#define ATOM_S6_ACC_MODE_SHIFT                  4
#define ATOM_S6_EXT_DESKTOP_MODE_SHIFT          5
#define ATOM_S6_WID_STATE_SHIFT                 6
#define ATOM_S6_DOCK_STATE_SHIFT                7
#define ATOM_S6_CWITICAW_STATE_SHIFT            8
#define ATOM_S6_HW_I2C_BUSY_STATE_SHIFT         9
#define ATOM_S6_THEWMAW_STATE_CHANGE_SHIFT      10
#define ATOM_S6_INTEWWUPT_SET_BY_BIOS_SHIFT     11
#define ATOM_S6_WEQ_SCAWEW_SHIFT                12
#define ATOM_S6_WEQ_SCAWEW_AWATIO_SHIFT         13
#define ATOM_S6_DISPWAY_STATE_CHANGE_SHIFT      14
#define ATOM_S6_I2C_STATE_CHANGE_SHIFT          15
#define ATOM_S6_SYSTEM_POWEW_MODE_CHANGE_SHIFT  28
#define ATOM_S6_ACC_BWOCK_DISPWAY_SWITCH_SHIFT  29
#define ATOM_S6_VWI_BWIGHTNESS_CHANGE_SHIFT     30
#define ATOM_S6_CONFIG_DISPWAY_CHANGE_SHIFT     31

// BIOS_7_SCWATCH Definition, BIOS_7_SCWATCH is used by Fiwmwawe onwy !!!!
#define ATOM_S7_DOS_MODE_TYPEb0             0x03
#define ATOM_S7_DOS_MODE_VGAb0              0x00
#define ATOM_S7_DOS_MODE_VESAb0             0x01
#define ATOM_S7_DOS_MODE_EXTb0              0x02
#define ATOM_S7_DOS_MODE_PIXEW_DEPTHb0      0x0C
#define ATOM_S7_DOS_MODE_PIXEW_FOWMATb0     0xF0
#define ATOM_S7_DOS_8BIT_DAC_ENb1           0x01
#define ATOM_S7_ASIC_INIT_COMPWETEb1        0x02
#define ATOM_S7_ASIC_INIT_COMPWETE_MASK     0x00000200
#define ATOM_S7_DOS_MODE_NUMBEWw1           0x0FFFF

#define ATOM_S7_DOS_8BIT_DAC_EN_SHIFT       8

// BIOS_8_SCWATCH Definition
#define ATOM_S8_I2C_CHANNEW_BUSY_MASK       0x00000FFFF
#define ATOM_S8_I2C_HW_ENGINE_BUSY_MASK     0x0FFFF0000

#define ATOM_S8_I2C_CHANNEW_BUSY_SHIFT      0
#define ATOM_S8_I2C_ENGINE_BUSY_SHIFT       16

// BIOS_9_SCWATCH Definition
#ifndef ATOM_S9_I2C_CHANNEW_COMPWETED_MASK
#define ATOM_S9_I2C_CHANNEW_COMPWETED_MASK  0x0000FFFF
#endif
#ifndef ATOM_S9_I2C_CHANNEW_ABOWTED_MASK
#define ATOM_S9_I2C_CHANNEW_ABOWTED_MASK    0xFFFF0000
#endif
#ifndef ATOM_S9_I2C_CHANNEW_COMPWETED_SHIFT
#define ATOM_S9_I2C_CHANNEW_COMPWETED_SHIFT 0
#endif
#ifndef ATOM_S9_I2C_CHANNEW_ABOWTED_SHIFT
#define ATOM_S9_I2C_CHANNEW_ABOWTED_SHIFT   16
#endif


#define ATOM_FWAG_SET                         0x20
#define ATOM_FWAG_CWEAW                       0
#define CWEAW_ATOM_S6_ACC_MODE                ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_ACC_MODE_SHIFT | ATOM_FWAG_CWEAW)
#define SET_ATOM_S6_DEVICE_CHANGE             ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DEVICE_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_VWI_BWIGHTNESS_CHANGE     ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_VWI_BWIGHTNESS_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_SCAWEW_CHANGE             ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_SCAWEW_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_WID_CHANGE                ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WID_CHANGE_SHIFT | ATOM_FWAG_SET)

#define SET_ATOM_S6_WID_STATE                 ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WID_STATE_SHIFT | ATOM_FWAG_SET)
#define CWEAW_ATOM_S6_WID_STATE               ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WID_STATE_SHIFT | ATOM_FWAG_CWEAW)

#define SET_ATOM_S6_DOCK_CHANGE                   ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCKING_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_DOCK_STATE                ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCK_STATE_SHIFT | ATOM_FWAG_SET)
#define CWEAW_ATOM_S6_DOCK_STATE              ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCK_STATE_SHIFT | ATOM_FWAG_CWEAW)

#define SET_ATOM_S6_THEWMAW_STATE_CHANGE      ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_THEWMAW_STATE_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_SYSTEM_POWEW_MODE_CHANGE  ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_SYSTEM_POWEW_MODE_CHANGE_SHIFT | ATOM_FWAG_SET)
#define SET_ATOM_S6_INTEWWUPT_SET_BY_BIOS     ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_INTEWWUPT_SET_BY_BIOS_SHIFT | ATOM_FWAG_SET)

#define SET_ATOM_S6_CWITICAW_STATE            ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CWITICAW_STATE_SHIFT | ATOM_FWAG_SET)
#define CWEAW_ATOM_S6_CWITICAW_STATE          ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CWITICAW_STATE_SHIFT | ATOM_FWAG_CWEAW)

#define SET_ATOM_S6_WEQ_SCAWEW                ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WEQ_SCAWEW_SHIFT | ATOM_FWAG_SET)
#define CWEAW_ATOM_S6_WEQ_SCAWEW              ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WEQ_SCAWEW_SHIFT | ATOM_FWAG_CWEAW )

#define SET_ATOM_S6_WEQ_SCAWEW_AWATIO         ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WEQ_SCAWEW_AWATIO_SHIFT | ATOM_FWAG_SET )
#define CWEAW_ATOM_S6_WEQ_SCAWEW_AWATIO       ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_WEQ_SCAWEW_AWATIO_SHIFT | ATOM_FWAG_CWEAW )

#define SET_ATOM_S6_I2C_STATE_CHANGE          ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_I2C_STATE_CHANGE_SHIFT | ATOM_FWAG_SET )

#define SET_ATOM_S6_DISPWAY_STATE_CHANGE      ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DISPWAY_STATE_CHANGE_SHIFT | ATOM_FWAG_SET )

#define SET_ATOM_S6_DEVICE_WECONFIG           ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CONFIG_DISPWAY_CHANGE_SHIFT | ATOM_FWAG_SET)
#define CWEAW_ATOM_S0_WCD1                    ((ATOM_DEVICE_CONNECT_INFO_DEF << 8 )|  ATOM_S0_WCD1_SHIFT | ATOM_FWAG_CWEAW )
#define SET_ATOM_S7_DOS_8BIT_DAC_EN           ((ATOM_DOS_MODE_INFO_DEF << 8 )|ATOM_S7_DOS_8BIT_DAC_EN_SHIFT | ATOM_FWAG_SET )
#define CWEAW_ATOM_S7_DOS_8BIT_DAC_EN         ((ATOM_DOS_MODE_INFO_DEF << 8 )|ATOM_S7_DOS_8BIT_DAC_EN_SHIFT | ATOM_FWAG_CWEAW )

/****************************************************************************/
//Powtion II: Definitinos onwy used in Dwivew
/****************************************************************************/

// Macwos used by dwivew

#ifdef __cpwuspwus
#define GetIndexIntoMastewTabwe(MastewOwData, FiewdName) ((weintewpwet_cast<chaw*>(&(static_cast<ATOM_MASTEW_WIST_OF_##MastewOwData##_TABWES*>(0))->FiewdName)-static_cast<chaw*>(0))/sizeof(USHOWT))

#define GET_COMMAND_TABWE_COMMANDSET_WEVISION(TABWE_HEADEW_OFFSET) (((static_cast<ATOM_COMMON_TABWE_HEADEW*>(TABWE_HEADEW_OFFSET))->ucTabweFowmatWevision )&0x3F)
#define GET_COMMAND_TABWE_PAWAMETEW_WEVISION(TABWE_HEADEW_OFFSET)  (((static_cast<ATOM_COMMON_TABWE_HEADEW*>(TABWE_HEADEW_OFFSET))->ucTabweContentWevision)&0x3F)
#ewse // not __cpwuspwus
#define   GetIndexIntoMastewTabwe(MastewOwData, FiewdName) (offsetof(ATOM_MASTEW_WIST_OF_##MastewOwData##_TABWES, FiewdName) / sizeof(USHOWT))

#define GET_COMMAND_TABWE_COMMANDSET_WEVISION(TABWE_HEADEW_OFFSET) ((((ATOM_COMMON_TABWE_HEADEW*)TABWE_HEADEW_OFFSET)->ucTabweFowmatWevision)&0x3F)
#define GET_COMMAND_TABWE_PAWAMETEW_WEVISION(TABWE_HEADEW_OFFSET)  ((((ATOM_COMMON_TABWE_HEADEW*)TABWE_HEADEW_OFFSET)->ucTabweContentWevision)&0x3F)
#endif // __cpwuspwus

#define GET_DATA_TABWE_MAJOW_WEVISION GET_COMMAND_TABWE_COMMANDSET_WEVISION
#define GET_DATA_TABWE_MINOW_WEVISION GET_COMMAND_TABWE_PAWAMETEW_WEVISION

/****************************************************************************/
//Powtion III: Definitinos onwy used in VBIOS
/****************************************************************************/
#define ATOM_DAC_SWC               0x80
#define ATOM_SWC_DAC1               0
#define ATOM_SWC_DAC2               0x80



typedef stwuct _MEMOWY_PWWINIT_PAWAMETEWS
{
  UWONG uwTawgetMemowyCwock; //In 10Khz unit
  UCHAW   ucAction;                //not define yet
  UCHAW   ucFbDiv_Hi;             //Fbdiv Hi byte
  UCHAW   ucFbDiv;                //FB vawue
  UCHAW   ucPostDiv;             //Post div
}MEMOWY_PWWINIT_PAWAMETEWS;

#define MEMOWY_PWWINIT_PS_AWWOCATION  MEMOWY_PWWINIT_PAWAMETEWS


#define   GPIO_PIN_WWITE                                       0x01
#define   GPIO_PIN_WEAD                                          0x00

typedef stwuct  _GPIO_PIN_CONTWOW_PAWAMETEWS
{
  UCHAW ucGPIO_ID;           //wetuwn vawue, wead fwom GPIO pins
  UCHAW ucGPIOBitShift;        //define which bit in uGPIOBitVaw need to be update
   UCHAW ucGPIOBitVaw;           //Set/Weset cowwesponding bit defined in ucGPIOBitMask
  UCHAW ucAction;                 //=GPIO_PIN_WWITE: Wead; =GPIO_PIN_WEAD: Wwite
}GPIO_PIN_CONTWOW_PAWAMETEWS;

typedef stwuct _ENABWE_SCAWEW_PAWAMETEWS
{
  UCHAW ucScawew;            // ATOM_SCAWEW1, ATOM_SCAWEW2
  UCHAW ucEnabwe;            // ATOM_SCAWEW_DISABWE ow ATOM_SCAWEW_CENTEW ow ATOM_SCAWEW_EXPANSION
  UCHAW ucTVStandawd;        //
  UCHAW ucPadding[1];
}ENABWE_SCAWEW_PAWAMETEWS;
#define ENABWE_SCAWEW_PS_AWWOCATION ENABWE_SCAWEW_PAWAMETEWS

//ucEnabwe:
#define SCAWEW_BYPASS_AUTO_CENTEW_NO_WEPWICATION    0
#define SCAWEW_BYPASS_AUTO_CENTEW_AUTO_WEPWICATION  1
#define SCAWEW_ENABWE_2TAP_AWPHA_MODE               2
#define SCAWEW_ENABWE_MUWTITAP_MODE                 3

typedef stwuct _ENABWE_HAWDWAWE_ICON_CUWSOW_PAWAMETEWS
{
  UWONG  usHWIconHowzVewtPosn;        // Hawdwawe Icon Vewticaw position
  UCHAW  ucHWIconVewtOffset;          // Hawdwawe Icon Vewticaw offset
  UCHAW  ucHWIconHowzOffset;          // Hawdwawe Icon Howizontaw offset
  UCHAW  ucSewection;                 // ATOM_CUWSOW1 ow ATOM_ICON1 ow ATOM_CUWSOW2 ow ATOM_ICON2
  UCHAW  ucEnabwe;                    // ATOM_ENABWE ow ATOM_DISABWE
}ENABWE_HAWDWAWE_ICON_CUWSOW_PAWAMETEWS;

typedef stwuct _ENABWE_HAWDWAWE_ICON_CUWSOW_PS_AWWOCATION
{
  ENABWE_HAWDWAWE_ICON_CUWSOW_PAWAMETEWS  sEnabweIcon;
  ENABWE_CWTC_PAWAMETEWS                  sWesewved;
}ENABWE_HAWDWAWE_ICON_CUWSOW_PS_AWWOCATION;

typedef stwuct _ENABWE_GWAPH_SUWFACE_PAWAMETEWS
{
  USHOWT usHight;                     // Image Hight
  USHOWT usWidth;                     // Image Width
  UCHAW  ucSuwface;                   // Suwface 1 ow 2
  UCHAW  ucPadding[3];
}ENABWE_GWAPH_SUWFACE_PAWAMETEWS;

typedef stwuct _ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_2
{
  USHOWT usHight;                     // Image Hight
  USHOWT usWidth;                     // Image Width
  UCHAW  ucSuwface;                   // Suwface 1 ow 2
  UCHAW  ucEnabwe;                    // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW  ucPadding[2];
}ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_2;

typedef stwuct _ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_3
{
  USHOWT usHight;                     // Image Hight
  USHOWT usWidth;                     // Image Width
  UCHAW  ucSuwface;                   // Suwface 1 ow 2
  UCHAW  ucEnabwe;                    // ATOM_ENABWE ow ATOM_DISABWE
  USHOWT usDeviceId;                  // Active Device Id fow this suwface. If no device, set to 0.
}ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_3;

typedef stwuct _ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_4
{
  USHOWT usHight;                     // Image Hight
  USHOWT usWidth;                     // Image Width
  USHOWT usGwaphPitch;
  UCHAW  ucCowowDepth;
  UCHAW  ucPixewFowmat;
  UCHAW  ucSuwface;                   // Suwface 1 ow 2
  UCHAW  ucEnabwe;                    // ATOM_ENABWE ow ATOM_DISABWE
  UCHAW  ucModeType;
  UCHAW  ucWesewved;
}ENABWE_GWAPH_SUWFACE_PAWAMETEWS_V1_4;

// ucEnabwe
#define ATOM_GWAPH_CONTWOW_SET_PITCH             0x0f
#define ATOM_GWAPH_CONTWOW_SET_DISP_STAWT        0x10

typedef stwuct _ENABWE_GWAPH_SUWFACE_PS_AWWOCATION
{
  ENABWE_GWAPH_SUWFACE_PAWAMETEWS sSetSuwface;
  ENABWE_YUV_PS_AWWOCATION        sWesewved; // Don't set this one
}ENABWE_GWAPH_SUWFACE_PS_AWWOCATION;

typedef stwuct _MEMOWY_CWEAN_UP_PAWAMETEWS
{
  USHOWT  usMemowyStawt;                //in 8Kb boundwy, offset fwom memowy base addwess
  USHOWT  usMemowySize;                 //8Kb bwocks awigned
}MEMOWY_CWEAN_UP_PAWAMETEWS;

#define MEMOWY_CWEAN_UP_PS_AWWOCATION MEMOWY_CWEAN_UP_PAWAMETEWS

typedef stwuct  _GET_DISPWAY_SUWFACE_SIZE_PAWAMETEWS
{
  USHOWT  usX_Size;                     //When use as input pawametew, usX_Size indicates which CWTC
  USHOWT  usY_Size;
}GET_DISPWAY_SUWFACE_SIZE_PAWAMETEWS;

typedef stwuct  _GET_DISPWAY_SUWFACE_SIZE_PAWAMETEWS_V2
{
  union{
    USHOWT  usX_Size;                     //When use as input pawametew, usX_Size indicates which CWTC
    USHOWT  usSuwface;
  };
  USHOWT usY_Size;
  USHOWT usDispXStawt;
  USHOWT usDispYStawt;
}GET_DISPWAY_SUWFACE_SIZE_PAWAMETEWS_V2;


typedef stwuct _PAWETTE_DATA_CONTWOW_PAWAMETEWS_V3
{
  UCHAW  ucWutId;
  UCHAW  ucAction;
  USHOWT usWutStawtIndex;
  USHOWT usWutWength;
  USHOWT usWutOffsetInVwam;
}PAWETTE_DATA_CONTWOW_PAWAMETEWS_V3;

// ucAction:
#define PAWETTE_DATA_AUTO_FIWW            1
#define PAWETTE_DATA_WEAD                 2
#define PAWETTE_DATA_WWITE                3


typedef stwuct _INTEWWUPT_SEWVICE_PAWAMETEWS_V2
{
  UCHAW  ucIntewwuptId;
  UCHAW  ucSewviceId;
  UCHAW  ucStatus;
  UCHAW  ucWesewved;
}INTEWWUPT_SEWVICE_PAWAMETEW_V2;

// ucIntewwuptId
#define HDP1_INTEWWUPT_ID                 1
#define HDP2_INTEWWUPT_ID                 2
#define HDP3_INTEWWUPT_ID                 3
#define HDP4_INTEWWUPT_ID                 4
#define HDP5_INTEWWUPT_ID                 5
#define HDP6_INTEWWUPT_ID                 6
#define SW_INTEWWUPT_ID                   11

// ucAction
#define INTEWWUPT_SEWVICE_GEN_SW_INT      1
#define INTEWWUPT_SEWVICE_GET_STATUS      2

 // ucStatus
#define INTEWWUPT_STATUS__INT_TWIGGEW     1
#define INTEWWUPT_STATUS__HPD_HIGH        2

typedef stwuct _EFUSE_INPUT_PAWAMETEW
{
  USHOWT usEfuseIndex;
  UCHAW  ucBitShift;
  UCHAW  ucBitWength;
}EFUSE_INPUT_PAWAMETEW;

// WeadEfuseVawue command tabwe input/output pawametew
typedef union _WEAD_EFUSE_VAWUE_PAWAMETEW
{
  EFUSE_INPUT_PAWAMETEW sEfuse;
  UWONG                 uwEfuseVawue;
}WEAD_EFUSE_VAWUE_PAWAMETEW;

typedef stwuct _INDIWECT_IO_ACCESS
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  UCHAW                    IOAccessSequence[256];
} INDIWECT_IO_ACCESS;

#define INDIWECT_WEAD              0x00
#define INDIWECT_WWITE             0x80

#define INDIWECT_IO_MM             0
#define INDIWECT_IO_PWW            1
#define INDIWECT_IO_MC             2
#define INDIWECT_IO_PCIE           3
#define INDIWECT_IO_PCIEP          4
#define INDIWECT_IO_NBMISC         5
#define INDIWECT_IO_SMU            5

#define INDIWECT_IO_PWW_WEAD       INDIWECT_IO_PWW   | INDIWECT_WEAD
#define INDIWECT_IO_PWW_WWITE      INDIWECT_IO_PWW   | INDIWECT_WWITE
#define INDIWECT_IO_MC_WEAD        INDIWECT_IO_MC    | INDIWECT_WEAD
#define INDIWECT_IO_MC_WWITE       INDIWECT_IO_MC    | INDIWECT_WWITE
#define INDIWECT_IO_PCIE_WEAD      INDIWECT_IO_PCIE  | INDIWECT_WEAD
#define INDIWECT_IO_PCIE_WWITE     INDIWECT_IO_PCIE  | INDIWECT_WWITE
#define INDIWECT_IO_PCIEP_WEAD     INDIWECT_IO_PCIEP | INDIWECT_WEAD
#define INDIWECT_IO_PCIEP_WWITE    INDIWECT_IO_PCIEP | INDIWECT_WWITE
#define INDIWECT_IO_NBMISC_WEAD    INDIWECT_IO_NBMISC | INDIWECT_WEAD
#define INDIWECT_IO_NBMISC_WWITE   INDIWECT_IO_NBMISC | INDIWECT_WWITE
#define INDIWECT_IO_SMU_WEAD       INDIWECT_IO_SMU | INDIWECT_WEAD
#define INDIWECT_IO_SMU_WWITE      INDIWECT_IO_SMU | INDIWECT_WWITE


typedef stwuct _ATOM_OEM_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  ATOM_I2C_ID_CONFIG_ACCESS sucI2cId;
}ATOM_OEM_INFO;

typedef stwuct _ATOM_TV_MODE
{
   UCHAW   ucVMode_Num;           //Video mode numbew
   UCHAW   ucTV_Mode_Num;         //Intewnaw TV mode numbew
}ATOM_TV_MODE;

typedef stwuct _ATOM_BIOS_INT_TVSTD_MODE
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
   USHOWT   usTV_Mode_WUT_Offset;   // Pointew to standawd to intewnaw numbew convewsion tabwe
   USHOWT   usTV_FIFO_Offset;        // Pointew to FIFO entwy tabwe
   USHOWT   usNTSC_Tbw_Offset;      // Pointew to SDTV_Mode_NTSC tabwe
   USHOWT   usPAW_Tbw_Offset;        // Pointew to SDTV_Mode_PAW tabwe
   USHOWT   usCV_Tbw_Offset;        // Pointew to SDTV_Mode_PAW tabwe
}ATOM_BIOS_INT_TVSTD_MODE;


typedef stwuct _ATOM_TV_MODE_SCAWEW_PTW
{
   USHOWT   ucFiwtew0_Offset;      //Pointew to fiwtew fowmat 0 coefficients
   USHOWT   usFiwtew1_Offset;      //Pointew to fiwtew fowmat 0 coefficients
   UCHAW   ucTV_Mode_Num;
}ATOM_TV_MODE_SCAWEW_PTW;

typedef stwuct _ATOM_STANDAWD_VESA_TIMING
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  ATOM_DTD_FOWMAT              aModeTimings[16];      // 16 is not the weaw awway numbew, just fow initiaw awwocation
}ATOM_STANDAWD_VESA_TIMING;


typedef stwuct _ATOM_STD_FOWMAT
{
  USHOWT    usSTD_HDisp;
  USHOWT    usSTD_VDisp;
  USHOWT    usSTD_WefweshWate;
  USHOWT    usWesewved;
}ATOM_STD_FOWMAT;

typedef stwuct _ATOM_VESA_TO_EXTENDED_MODE
{
  USHOWT  usVESA_ModeNumbew;
  USHOWT  usExtendedModeNumbew;
}ATOM_VESA_TO_EXTENDED_MODE;

typedef stwuct _ATOM_VESA_TO_INTENAW_MODE_WUT
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  ATOM_VESA_TO_EXTENDED_MODE asVESA_ToExtendedModeInfo[76];
}ATOM_VESA_TO_INTENAW_MODE_WUT;

/*************** ATOM Memowy Wewated Data Stwuctuwe ***********************/
typedef stwuct _ATOM_MEMOWY_VENDOW_BWOCK{
   UCHAW                                    ucMemowyType;
   UCHAW                                    ucMemowyVendow;
   UCHAW                                    ucAdjMCId;
   UCHAW                                    ucDynCwkId;
   UWONG                                    uwDwwWesetCwkWange;
}ATOM_MEMOWY_VENDOW_BWOCK;


typedef stwuct _ATOM_MEMOWY_SETTING_ID_CONFIG{
#if ATOM_BIG_ENDIAN
	UWONG												ucMemBwkId:8;
	UWONG												uwMemCwockWange:24;
#ewse
	UWONG												uwMemCwockWange:24;
	UWONG												ucMemBwkId:8;
#endif
}ATOM_MEMOWY_SETTING_ID_CONFIG;

typedef union _ATOM_MEMOWY_SETTING_ID_CONFIG_ACCESS
{
  ATOM_MEMOWY_SETTING_ID_CONFIG swAccess;
  UWONG                         uwAccess;
}ATOM_MEMOWY_SETTING_ID_CONFIG_ACCESS;


typedef stwuct _ATOM_MEMOWY_SETTING_DATA_BWOCK{
   ATOM_MEMOWY_SETTING_ID_CONFIG_ACCESS  uwMemowyID;
   UWONG                                 auwMemData[1];
}ATOM_MEMOWY_SETTING_DATA_BWOCK;


typedef stwuct _ATOM_INIT_WEG_INDEX_FOWMAT{
    USHOWT usWegIndex;                                     // MC wegistew index
    UCHAW  ucPweWegDataWength;                             // offset in ATOM_INIT_WEG_DATA_BWOCK.saWegDataBuf
}ATOM_INIT_WEG_INDEX_FOWMAT;


typedef stwuct _ATOM_INIT_WEG_BWOCK{
   USHOWT                           usWegIndexTbwSize;          //size of asWegIndexBuf
   USHOWT                           usWegDataBwkSize;           //size of ATOM_MEMOWY_SETTING_DATA_BWOCK
   ATOM_INIT_WEG_INDEX_FOWMAT       asWegIndexBuf[1];
   ATOM_MEMOWY_SETTING_DATA_BWOCK   asWegDataBuf[1];
}ATOM_INIT_WEG_BWOCK;

#define END_OF_WEG_INDEX_BWOCK  0x0ffff
#define END_OF_WEG_DATA_BWOCK   0x00000000
#define ATOM_INIT_WEG_MASK_FWAG 0x80               //Not used in BIOS
#define CWOCK_WANGE_HIGHEST     0x00ffffff

#define VAWUE_DWOWD             SIZEOF UWONG
#define VAWUE_SAME_AS_ABOVE     0
#define VAWUE_MASK_DWOWD        0x84

#define INDEX_ACCESS_WANGE_BEGIN       (VAWUE_DWOWD + 1)
#define INDEX_ACCESS_WANGE_END          (INDEX_ACCESS_WANGE_BEGIN + 1)
#define VAWUE_INDEX_ACCESS_SINGWE       (INDEX_ACCESS_WANGE_END + 1)
//#define ACCESS_MCIODEBUGIND            0x40       //defined in BIOS code
#define ACCESS_PWACEHOWDEW             0x80


typedef stwuct _ATOM_MC_INIT_PAWAM_TABWE
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  USHOWT                        usAdjustAWB_SEQDataOffset;
  USHOWT                        usMCInitMemTypeTbwOffset;
  USHOWT                        usMCInitCommonTbwOffset;
  USHOWT                        usMCInitPowewDownTbwOffset;
  UWONG                         uwAWB_SEQDataBuf[32];
  ATOM_INIT_WEG_BWOCK           asMCInitMemType;
  ATOM_INIT_WEG_BWOCK           asMCInitCommon;
}ATOM_MC_INIT_PAWAM_TABWE;


typedef stwuct _ATOM_WEG_INIT_SETTING
{
  USHOWT  usWegIndex;
  UWONG   uwWegVawue;
}ATOM_WEG_INIT_SETTING;

typedef stwuct _ATOM_MC_INIT_PAWAM_TABWE_V2_1
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  UWONG                         uwMCUcodeVewsion;
  UWONG                         uwMCUcodeWomStawtAddw;
  UWONG                         uwMCUcodeWength;
  USHOWT                        usMcWegInitTabweOffset;     // offset of ATOM_WEG_INIT_SETTING awway fow MC cowe wegistew settings.
  USHOWT                        usWesewved;                 // offset of ATOM_INIT_WEG_BWOCK fow MC SEQ/PHY wegistew setting
}ATOM_MC_INIT_PAWAM_TABWE_V2_1;


#define _4Mx16              0x2
#define _4Mx32              0x3
#define _8Mx16              0x12
#define _8Mx32              0x13
#define _8Mx128             0x15
#define _16Mx16             0x22
#define _16Mx32             0x23
#define _16Mx128            0x25
#define _32Mx16             0x32
#define _32Mx32             0x33
#define _32Mx128            0x35
#define _64Mx8              0x41
#define _64Mx16             0x42
#define _64Mx32             0x43
#define _64Mx128            0x45
#define _128Mx8             0x51
#define _128Mx16            0x52
#define _128Mx32            0x53
#define _256Mx8             0x61
#define _256Mx16            0x62
#define _256Mx32            0x63
#define _512Mx8             0x71
#define _512Mx16            0x72


#define SAMSUNG             0x1
#define INFINEON            0x2
#define EWPIDA              0x3
#define ETWON               0x4
#define NANYA               0x5
#define HYNIX               0x6
#define MOSEW               0x7
#define WINBOND             0x8
#define ESMT                0x9
#define MICWON              0xF

#define QIMONDA             INFINEON
#define PWOMOS              MOSEW
#define KWETON              INFINEON
#define EWIXIW              NANYA
#define MEZZA               EWPIDA


/////////////Suppowt fow GDDW5 MC uCode to weside in uppew 64K of WOM/////////////

#define UCODE_WOM_STAWT_ADDWESS      0x1b800
#define   UCODE_SIGNATUWE         0x4375434d // 'MCuC' - MC uCode

//uCode bwock headew fow wefewence

typedef stwuct _MCuCodeHeadew
{
  UWONG  uwSignatuwe;
  UCHAW  ucWevision;
  UCHAW  ucChecksum;
  UCHAW  ucWesewved1;
  UCHAW  ucWesewved2;
  USHOWT usPawametewsWength;
  USHOWT usUCodeWength;
  USHOWT usWesewved1;
  USHOWT usWesewved2;
} MCuCodeHeadew;

//////////////////////////////////////////////////////////////////////////////////

#define ATOM_MAX_NUMBEW_OF_VWAM_MODUWE   16

#define ATOM_VWAM_MODUWE_MEMOWY_VENDOW_ID_MASK   0xF
typedef stwuct _ATOM_VWAM_MODUWE_V1
{
  UWONG                      uwWesewved;
  USHOWT                     usEMWSVawue;
  USHOWT                     usMWSVawue;
  USHOWT                     usWesewved;
  UCHAW                      ucExtMemowyID;     // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW                      ucMemowyType;      // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4;[3:0] wesewved;
  UCHAW                      ucMemowyVendewID;  // Pwedefined,nevew change acwoss designs ow memowy type/vendew
  UCHAW                      ucMemowyDeviceCfg; // [7:4]=0x0:4M;=0x1:8M;=0x2:16M;0x3:32M....[3:0]=0x0:x4;=0x1:x8;=0x2:x16;=0x3:x32...
  UCHAW                      ucWow;             // Numbew of Wow,in powew of 2;
  UCHAW                      ucCowumn;          // Numbew of Cowumn,in powew of 2;
  UCHAW                      ucBank;            // Nunbew of Bank;
  UCHAW                      ucWank;            // Numbew of Wank, in powew of 2
  UCHAW                      ucChannewNum;      // Numbew of channew;
  UCHAW                      ucChannewConfig;   // [3:0]=Indication of what channew combination;[4:7]=Channew bit width, in numbew of 2
  UCHAW                      ucDefauwtMVDDQ_ID; // Defauwt MVDDQ setting fow this memowy bwock, ID winking to MVDDQ info tabwe to find weaw set-up data;
  UCHAW                      ucDefauwtMVDDC_ID; // Defauwt MVDDC setting fow this memowy bwock, ID winking to MVDDC info tabwe to find weaw set-up data;
  UCHAW                      ucWesewved[2];
}ATOM_VWAM_MODUWE_V1;


typedef stwuct _ATOM_VWAM_MODUWE_V2
{
  UWONG                      uwWesewved;
  UWONG                      uwFwags;              // To enabwe/disabwe functionawities based on memowy type
  UWONG                      uwEngineCwock;     // Ovewwide of defauwt engine cwock fow pawticuwaw memowy type
  UWONG                      uwMemowyCwock;     // Ovewwide of defauwt memowy cwock fow pawticuwaw memowy type
  USHOWT                     usEMWS2Vawue;      // EMWS2 Vawue is used fow GDDW2 and GDDW4 memowy type
  USHOWT                     usEMWS3Vawue;      // EMWS3 Vawue is used fow GDDW2 and GDDW4 memowy type
  USHOWT                     usEMWSVawue;
  USHOWT                     usMWSVawue;
  USHOWT                     usWesewved;
  UCHAW                      ucExtMemowyID;     // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW                      ucMemowyType;      // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4;[3:0] - must not be used fow now;
  UCHAW                      ucMemowyVendewID;  // Pwedefined,nevew change acwoss designs ow memowy type/vendew. If not pwedefined, vendow detection tabwe gets executed
  UCHAW                      ucMemowyDeviceCfg; // [7:4]=0x0:4M;=0x1:8M;=0x2:16M;0x3:32M....[3:0]=0x0:x4;=0x1:x8;=0x2:x16;=0x3:x32...
  UCHAW                      ucWow;             // Numbew of Wow,in powew of 2;
  UCHAW                      ucCowumn;          // Numbew of Cowumn,in powew of 2;
  UCHAW                      ucBank;            // Nunbew of Bank;
  UCHAW                      ucWank;            // Numbew of Wank, in powew of 2
  UCHAW                      ucChannewNum;      // Numbew of channew;
  UCHAW                      ucChannewConfig;   // [3:0]=Indication of what channew combination;[4:7]=Channew bit width, in numbew of 2
  UCHAW                      ucDefauwtMVDDQ_ID; // Defauwt MVDDQ setting fow this memowy bwock, ID winking to MVDDQ info tabwe to find weaw set-up data;
  UCHAW                      ucDefauwtMVDDC_ID; // Defauwt MVDDC setting fow this memowy bwock, ID winking to MVDDC info tabwe to find weaw set-up data;
  UCHAW                      ucWefweshWateFactow;
  UCHAW                      ucWesewved[3];
}ATOM_VWAM_MODUWE_V2;


typedef   stwuct _ATOM_MEMOWY_TIMING_FOWMAT
{
   UWONG                     uwCwkWange;            // memowy cwock in 10kHz unit, when tawget memowy cwock is bewow this cwock, use this memowy timing
  union{
    USHOWT                   usMWS;                 // mode wegistew
    USHOWT                   usDDW3_MW0;
  };
  union{
    USHOWT                   usEMWS;                  // extended mode wegistew
    USHOWT                   usDDW3_MW1;
  };
   UCHAW                     ucCW;                    // CAS watency
   UCHAW                     ucWW;                    // WWITE Watency
   UCHAW                     uctWAS;                  // tWAS
   UCHAW                     uctWC;                   // tWC
   UCHAW                     uctWFC;                  // tWFC
   UCHAW                     uctWCDW;                 // tWCDW
   UCHAW                     uctWCDW;                 // tWCDW
   UCHAW                     uctWP;                   // tWP
   UCHAW                     uctWWD;                  // tWWD
   UCHAW                     uctWW;                   // tWW
   UCHAW                     uctWTW;                  // tWTW
   UCHAW                     uctPDIX;                 // tPDIX
   UCHAW                     uctFAW;                  // tFAW
   UCHAW                     uctAOND;                 // tAOND
  union
  {
    stwuct {
       UCHAW                                  ucfwag;                  // fwag to contwow memowy timing cawcuwation. bit0= contwow EMWS2 Infineon
       UCHAW                                  ucWesewved;
    };
    USHOWT                   usDDW3_MW2;
  };
}ATOM_MEMOWY_TIMING_FOWMAT;


typedef   stwuct _ATOM_MEMOWY_TIMING_FOWMAT_V1
{
   UWONG                      uwCwkWange;            // memowy cwock in 10kHz unit, when tawget memowy cwock is bewow this cwock, use this memowy timing
   USHOWT                     usMWS;                 // mode wegistew
   USHOWT                     usEMWS;                // extended mode wegistew
   UCHAW                      ucCW;                  // CAS watency
   UCHAW                      ucWW;                  // WWITE Watency
   UCHAW                      uctWAS;                // tWAS
   UCHAW                      uctWC;                 // tWC
   UCHAW                      uctWFC;                // tWFC
   UCHAW                      uctWCDW;               // tWCDW
   UCHAW                      uctWCDW;               // tWCDW
   UCHAW                      uctWP;                 // tWP
   UCHAW                      uctWWD;                // tWWD
   UCHAW                      uctWW;                 // tWW
   UCHAW                      uctWTW;                // tWTW
   UCHAW                      uctPDIX;               // tPDIX
   UCHAW                      uctFAW;                // tFAW
   UCHAW                      uctAOND;               // tAOND
   UCHAW                      ucfwag;                // fwag to contwow memowy timing cawcuwation. bit0= contwow EMWS2 Infineon
////////////////////////////////////GDDW pawametews///////////////////////////////////
   UCHAW                      uctCCDW;               //
   UCHAW                      uctCWCWW;              //
   UCHAW                      uctCWCWW;              //
   UCHAW                      uctCKE;                //
   UCHAW                      uctCKWSE;              //
   UCHAW                      uctCKWSX;              //
   UCHAW                      uctFAW32;              //
   UCHAW                      ucMW5wo;               //
   UCHAW                      ucMW5hi;               //
   UCHAW                      ucTewminatow;
}ATOM_MEMOWY_TIMING_FOWMAT_V1;




typedef   stwuct _ATOM_MEMOWY_TIMING_FOWMAT_V2
{
   UWONG                                  uwCwkWange;            // memowy cwock in 10kHz unit, when tawget memowy cwock is bewow this cwock, use this memowy timing
   USHOWT                               usMWS;                     // mode wegistew
   USHOWT                               usEMWS;                  // extended mode wegistew
   UCHAW                                  ucCW;                     // CAS watency
   UCHAW                                  ucWW;                     // WWITE Watency
   UCHAW                                  uctWAS;                  // tWAS
   UCHAW                                  uctWC;                     // tWC
   UCHAW                                  uctWFC;                  // tWFC
   UCHAW                                  uctWCDW;                  // tWCDW
   UCHAW                                  uctWCDW;                  // tWCDW
   UCHAW                                  uctWP;                     // tWP
   UCHAW                                  uctWWD;                  // tWWD
   UCHAW                                  uctWW;                     // tWW
   UCHAW                                  uctWTW;                  // tWTW
   UCHAW                                  uctPDIX;                  // tPDIX
   UCHAW                                  uctFAW;                  // tFAW
   UCHAW                                  uctAOND;                  // tAOND
   UCHAW                                  ucfwag;                  // fwag to contwow memowy timing cawcuwation. bit0= contwow EMWS2 Infineon
////////////////////////////////////GDDW pawametews///////////////////////////////////
   UCHAW                                  uctCCDW;                  //
   UCHAW                                  uctCWCWW;                  //
   UCHAW                                  uctCWCWW;                  //
   UCHAW                                  uctCKE;                  //
   UCHAW                                  uctCKWSE;                  //
   UCHAW                                  uctCKWSX;                  //
   UCHAW                                  uctFAW32;                  //
   UCHAW                                  ucMW4wo;               //
   UCHAW                                  ucMW4hi;               //
   UCHAW                                  ucMW5wo;               //
   UCHAW                                  ucMW5hi;               //
   UCHAW                                  ucTewminatow;
   UCHAW                                  ucWesewved;
}ATOM_MEMOWY_TIMING_FOWMAT_V2;


typedef   stwuct _ATOM_MEMOWY_FOWMAT
{
   UWONG                       uwDwwDisCwock;     // memowy DWW wiww be disabwe when tawget memowy cwock is bewow this cwock
  union{
    USHOWT                     usEMWS2Vawue;      // EMWS2 Vawue is used fow GDDW2 and GDDW4 memowy type
    USHOWT                     usDDW3_Wesewved;   // Not used fow DDW3 memowy
  };
  union{
    USHOWT                     usEMWS3Vawue;      // EMWS3 Vawue is used fow GDDW2 and GDDW4 memowy type
    USHOWT                     usDDW3_MW3;        // Used fow DDW3 memowy
  };
  UCHAW                        ucMemowyType;      // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4;[3:0] - must not be used fow now;
  UCHAW                        ucMemowyVendewID;  // Pwedefined,nevew change acwoss designs ow memowy type/vendew. If not pwedefined, vendow detection tabwe gets executed
  UCHAW                        ucWow;             // Numbew of Wow,in powew of 2;
  UCHAW                        ucCowumn;          // Numbew of Cowumn,in powew of 2;
  UCHAW                        ucBank;            // Nunbew of Bank;
  UCHAW                        ucWank;            // Numbew of Wank, in powew of 2
  UCHAW                        ucBuwstSize;           // buwst size, 0= buwst size=4  1= buwst size=8
  UCHAW                        ucDwwDisBit;           // position of DWW Enabwe/Disabwe bit in EMWS ( Extended Mode Wegistew )
  UCHAW                        ucWefweshWateFactow;   // memowy wefwesh wate in unit of ms
  UCHAW                        ucDensity;             // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  UCHAW                        ucPweambwe;            // [7:4] Wwite Pweambwe, [3:0] Wead Pweambwe
  UCHAW                        ucMemAttwib;           // Memowy Device Addwibute, wike WDBI/WDBI etc
  ATOM_MEMOWY_TIMING_FOWMAT    asMemTiming[5];        // Memowy Timing bwock sowt fwom wowew cwock to highew cwock
}ATOM_MEMOWY_FOWMAT;


typedef stwuct _ATOM_VWAM_MODUWE_V3
{
  UWONG                      uwChannewMapCfg;     // boawd dependent pawamentew:Channew combination
  USHOWT                     usSize;              // size of ATOM_VWAM_MODUWE_V3
  USHOWT                     usDefauwtMVDDQ;      // boawd dependent pawametew:Defauwt Memowy Cowe Vowtage
  USHOWT                     usDefauwtMVDDC;      // boawd dependent pawametew:Defauwt Memowy IO Vowtage
  UCHAW                      ucExtMemowyID;       // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW                      ucChannewNum;        // boawd dependent pawametew:Numbew of channew;
  UCHAW                      ucChannewSize;       // boawd dependent pawametew:32bit ow 64bit
  UCHAW                      ucVWEFI;             // boawd dependnt pawametew: EXT ow INT +160mv to -140mv
  UCHAW                      ucNPW_WT;            // boawd dependent pawametew:NPW wound twip deway, used fow cawcuwate memowy timing pawametews
  UCHAW                      ucFwag;              // To enabwe/disabwe functionawities based on memowy type
  ATOM_MEMOWY_FOWMAT         asMemowy;            // descwib aww of video memowy pawametews fwom memowy spec
}ATOM_VWAM_MODUWE_V3;


//ATOM_VWAM_MODUWE_V3.ucNPW_WT
#define NPW_WT_MASK                                         0x0f
#define BATTEWY_ODT_MASK                                    0xc0

#define ATOM_VWAM_MODUWE       ATOM_VWAM_MODUWE_V3

typedef stwuct _ATOM_VWAM_MODUWE_V4
{
  UWONG     uwChannewMapCfg;                   // boawd dependent pawametew: Channew combination
  USHOWT  usModuweSize;                     // size of ATOM_VWAM_MODUWE_V4, make it easy fow VBIOS to wook fow next entwy of VWAM_MODUWE
  USHOWT  usPwivateWesewved;                // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // MC_AWB_WAMCFG (incwudes NOOFBANK,NOOFWANKS,NOOFWOWS,NOOFCOWS)
  USHOWT  usWesewved;
  UCHAW   ucExtMemowyID;                      // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW   ucMemowyType;                     // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4; 0x5:DDW5 [3:0] - Must be 0x0 fow now;
  UCHAW   ucChannewNum;                     // Numbew of channews pwesent in this moduwe config
  UCHAW   ucChannewWidth;                   // 0 - 32 bits; 1 - 64 bits
   UCHAW   ucDensity;                        // _8Mx32, _16Mx32, _16Mx16, _32Mx16
   UCHAW     ucFwag;                                  // To enabwe/disabwe functionawities based on memowy type
   UCHAW     ucMisc;                                  // bit0: 0 - singwe wank; 1 - duaw wank;   bit2: 0 - buwstwength 4, 1 - buwstwength 8
  UCHAW      ucVWEFI;                          // boawd dependent pawametew
  UCHAW   ucNPW_WT;                         // boawd dependent pawametew:NPW wound twip deway, used fow cawcuwate memowy timing pawametews
  UCHAW      ucPweambwe;                       // [7:4] Wwite Pweambwe, [3:0] Wead Pweambwe
  UCHAW   ucMemowySize;                     // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // Totaw memowy size in unit of 16MB fow CONFIG_MEMSIZE - bit[23:0] zewos
  UCHAW   ucWesewved[3];

//compawe with V3, we fwat the stwuct by mewging ATOM_MEMOWY_FOWMAT (as is) into V4 as the same wevew
  union{
    USHOWT   usEMWS2Vawue;                   // EMWS2 Vawue is used fow GDDW2 and GDDW4 memowy type
    USHOWT  usDDW3_Wesewved;
  };
  union{
    USHOWT   usEMWS3Vawue;                   // EMWS3 Vawue is used fow GDDW2 and GDDW4 memowy type
    USHOWT  usDDW3_MW3;                     // Used fow DDW3 memowy
  };
  UCHAW   ucMemowyVendewID;                    // Pwedefined, If not pwedefined, vendow detection tabwe gets executed
  UCHAW     ucWefweshWateFactow;              // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  UCHAW   ucWesewved2[2];
  ATOM_MEMOWY_TIMING_FOWMAT  asMemTiming[5];//Memowy Timing bwock sowt fwom wowew cwock to highew cwock
}ATOM_VWAM_MODUWE_V4;

#define VWAM_MODUWE_V4_MISC_WANK_MASK       0x3
#define VWAM_MODUWE_V4_MISC_DUAW_WANK       0x1
#define VWAM_MODUWE_V4_MISC_BW_MASK         0x4
#define VWAM_MODUWE_V4_MISC_BW8             0x4
#define VWAM_MODUWE_V4_MISC_DUAW_CS         0x10

typedef stwuct _ATOM_VWAM_MODUWE_V5
{
  UWONG     uwChannewMapCfg;                   // boawd dependent pawametew: Channew combination
  USHOWT  usModuweSize;                     // size of ATOM_VWAM_MODUWE_V4, make it easy fow VBIOS to wook fow next entwy of VWAM_MODUWE
  USHOWT  usPwivateWesewved;                // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // MC_AWB_WAMCFG (incwudes NOOFBANK,NOOFWANKS,NOOFWOWS,NOOFCOWS)
  USHOWT  usWesewved;
  UCHAW   ucExtMemowyID;                      // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW   ucMemowyType;                     // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4; 0x5:DDW5 [3:0] - Must be 0x0 fow now;
  UCHAW   ucChannewNum;                     // Numbew of channews pwesent in this moduwe config
  UCHAW   ucChannewWidth;                   // 0 - 32 bits; 1 - 64 bits
   UCHAW   ucDensity;                        // _8Mx32, _16Mx32, _16Mx16, _32Mx16
   UCHAW     ucFwag;                                  // To enabwe/disabwe functionawities based on memowy type
   UCHAW     ucMisc;                                  // bit0: 0 - singwe wank; 1 - duaw wank;   bit2: 0 - buwstwength 4, 1 - buwstwength 8
  UCHAW      ucVWEFI;                          // boawd dependent pawametew
  UCHAW   ucNPW_WT;                         // boawd dependent pawametew:NPW wound twip deway, used fow cawcuwate memowy timing pawametews
  UCHAW      ucPweambwe;                       // [7:4] Wwite Pweambwe, [3:0] Wead Pweambwe
  UCHAW   ucMemowySize;                     // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // Totaw memowy size in unit of 16MB fow CONFIG_MEMSIZE - bit[23:0] zewos
  UCHAW   ucWesewved[3];

//compawe with V3, we fwat the stwuct by mewging ATOM_MEMOWY_FOWMAT (as is) into V4 as the same wevew
  USHOWT   usEMWS2Vawue;                        // EMWS2 Vawue is used fow GDDW2 and GDDW4 memowy type
  USHOWT   usEMWS3Vawue;                        // EMWS3 Vawue is used fow GDDW2 and GDDW4 memowy type
  UCHAW   ucMemowyVendewID;                    // Pwedefined, If not pwedefined, vendow detection tabwe gets executed
  UCHAW     ucWefweshWateFactow;              // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  UCHAW     ucFIFODepth;                         // FIFO depth supposes to be detected duwing vendow detection, but if we dont do vendow detection we have to hawdcode FIFO Depth
  UCHAW   ucCDW_Bandwidth;         // [0:3]=Wead CDW bandwidth, [4:7] - Wwite CDW Bandwidth
  ATOM_MEMOWY_TIMING_FOWMAT_V1  asMemTiming[5];//Memowy Timing bwock sowt fwom wowew cwock to highew cwock
}ATOM_VWAM_MODUWE_V5;


typedef stwuct _ATOM_VWAM_MODUWE_V6
{
  UWONG     uwChannewMapCfg;                   // boawd dependent pawametew: Channew combination
  USHOWT  usModuweSize;                     // size of ATOM_VWAM_MODUWE_V4, make it easy fow VBIOS to wook fow next entwy of VWAM_MODUWE
  USHOWT  usPwivateWesewved;                // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // MC_AWB_WAMCFG (incwudes NOOFBANK,NOOFWANKS,NOOFWOWS,NOOFCOWS)
  USHOWT  usWesewved;
  UCHAW   ucExtMemowyID;                      // An extewnaw indicatow (by hawdcode, cawwback ow pin) to teww what is the cuwwent memowy moduwe
  UCHAW   ucMemowyType;                     // [7:4]=0x1:DDW1;=0x2:DDW2;=0x3:DDW3;=0x4:DDW4; 0x5:DDW5 [3:0] - Must be 0x0 fow now;
  UCHAW   ucChannewNum;                     // Numbew of channews pwesent in this moduwe config
  UCHAW   ucChannewWidth;                   // 0 - 32 bits; 1 - 64 bits
   UCHAW   ucDensity;                        // _8Mx32, _16Mx32, _16Mx16, _32Mx16
   UCHAW     ucFwag;                                  // To enabwe/disabwe functionawities based on memowy type
   UCHAW     ucMisc;                                  // bit0: 0 - singwe wank; 1 - duaw wank;   bit2: 0 - buwstwength 4, 1 - buwstwength 8
  UCHAW      ucVWEFI;                          // boawd dependent pawametew
  UCHAW   ucNPW_WT;                         // boawd dependent pawametew:NPW wound twip deway, used fow cawcuwate memowy timing pawametews
  UCHAW      ucPweambwe;                       // [7:4] Wwite Pweambwe, [3:0] Wead Pweambwe
  UCHAW   ucMemowySize;                     // BIOS intewnaw wesewved space to optimize code size, updated by the compiwew, shouwdn't be modified manuawwy!!
                                            // Totaw memowy size in unit of 16MB fow CONFIG_MEMSIZE - bit[23:0] zewos
  UCHAW   ucWesewved[3];

//compawe with V3, we fwat the stwuct by mewging ATOM_MEMOWY_FOWMAT (as is) into V4 as the same wevew
  USHOWT   usEMWS2Vawue;                        // EMWS2 Vawue is used fow GDDW2 and GDDW4 memowy type
  USHOWT   usEMWS3Vawue;                        // EMWS3 Vawue is used fow GDDW2 and GDDW4 memowy type
  UCHAW   ucMemowyVendewID;                    // Pwedefined, If not pwedefined, vendow detection tabwe gets executed
  UCHAW     ucWefweshWateFactow;              // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  UCHAW     ucFIFODepth;                         // FIFO depth supposes to be detected duwing vendow detection, but if we dont do vendow detection we have to hawdcode FIFO Depth
  UCHAW   ucCDW_Bandwidth;         // [0:3]=Wead CDW bandwidth, [4:7] - Wwite CDW Bandwidth
  ATOM_MEMOWY_TIMING_FOWMAT_V2  asMemTiming[5];//Memowy Timing bwock sowt fwom wowew cwock to highew cwock
}ATOM_VWAM_MODUWE_V6;

typedef stwuct _ATOM_VWAM_MODUWE_V7
{
// Design Specific Vawues
  UWONG   uwChannewMapCfg;                   // mmMC_SHAWED_CHWEMAP
  USHOWT  usModuweSize;                     // Size of ATOM_VWAM_MODUWE_V7
  USHOWT  usPwivateWesewved;                // MC_AWB_WAMCFG (incwudes NOOFBANK,NOOFWANKS,NOOFWOWS,NOOFCOWS)
  USHOWT  usEnabweChannews;                 // bit vectow which indicate which channews awe enabwed
  UCHAW   ucExtMemowyID;                    // Cuwwent memowy moduwe ID
  UCHAW   ucMemowyType;                     // MEM_TYPE_DDW2/DDW3/GDDW3/GDDW5
  UCHAW   ucChannewNum;                     // Numbew of mem. channews suppowted in this moduwe
  UCHAW   ucChannewWidth;                   // CHANNEW_16BIT/CHANNEW_32BIT/CHANNEW_64BIT
  UCHAW   ucDensity;                        // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  UCHAW   ucWesewve;                        // In MC7x, the wowew 4 bits awe used as bit8-11 of memowy size. In othew MC code, it's not used.
  UCHAW   ucMisc;                           // WANK_OF_THISMEMOWY etc.
  UCHAW   ucVWEFI;                          // Not used.
  UCHAW   ucNPW_WT;                         // Wound twip deway (MC_SEQ_CAS_TIMING [28:24]:TCW=CW+NPW_WT-2). Awways 2.
  UCHAW   ucPweambwe;                       // [7:4] Wwite Pweambwe, [3:0] Wead Pweambwe
  UCHAW   ucMemowySize;                     // Totaw memowy size in unit of 16MB fow CONFIG_MEMSIZE - bit[23:0] zewos
  USHOWT  usSEQSettingOffset;
  UCHAW   ucWesewved;
// Memowy Moduwe specific vawues
  USHOWT  usEMWS2Vawue;                     // EMWS2/MW2 Vawue.
  USHOWT  usEMWS3Vawue;                     // EMWS3/MW3 Vawue.
  UCHAW   ucMemowyVendewID;                 // [7:4] Wevision, [3:0] Vendow code
  UCHAW   ucWefweshWateFactow;              // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  UCHAW   ucFIFODepth;                      // FIFO depth can be detected duwing vendow detection, hewe is hawdcoded pew memowy
  UCHAW   ucCDW_Bandwidth;                  // [0:3]=Wead CDW bandwidth, [4:7] - Wwite CDW Bandwidth
  chaw    stwMemPNStwing[20];               // pawt numbew end with '0'.
}ATOM_VWAM_MODUWE_V7;


typedef stwuct _ATOM_VWAM_MODUWE_V8
{
// Design Specific Vawues
  UWONG   uwChannewMapCfg;                  // mmMC_SHAWED_CHWEMAP
  USHOWT  usModuweSize;                     // Size of ATOM_VWAM_MODUWE_V7
  USHOWT  usMcWamCfg;                       // MC_AWB_WAMCFG (incwudes NOOFBANK,NOOFWANKS,NOOFWOWS,NOOFCOWS)
  USHOWT  usEnabweChannews;                 // bit vectow which indicate which channews awe enabwed
  UCHAW   ucExtMemowyID;                    // Cuwwent memowy moduwe ID
  UCHAW   ucMemowyType;                     // MEM_TYPE_DDW2/DDW3/GDDW3/GDDW5
  UCHAW   ucChannewNum;                     // Numbew of mem. channews suppowted in this moduwe
  UCHAW   ucChannewWidth;                   // CHANNEW_16BIT/CHANNEW_32BIT/CHANNEW_64BIT
  UCHAW   ucDensity;                        // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  UCHAW   ucBankCow;                        // bit[3:2]= BANK ( =2:16bank, =1:8bank, =0:4bank ) bit[1:0]=Cow ( =2: 10 bit, =1:9bit, =0:8bit )
  UCHAW   ucMisc;                           // WANK_OF_THISMEMOWY etc.
  UCHAW   ucVWEFI;                          // Not used.
  USHOWT  usWesewved;                       // Not used
  USHOWT  usMemowySize;                     // Totaw memowy size in unit of MB fow CONFIG_MEMSIZE zewos
  UCHAW   ucMcTunningSetId;                 // MC phy wegistews set pew.
  UCHAW   ucWowNum;
// Memowy Moduwe specific vawues
  USHOWT  usEMWS2Vawue;                     // EMWS2/MW2 Vawue.
  USHOWT  usEMWS3Vawue;                     // EMWS3/MW3 Vawue.
  UCHAW   ucMemowyVendewID;                 // [7:4] Wevision, [3:0] Vendow code
  UCHAW   ucWefweshWateFactow;              // [1:0]=WefweshFactow (00=8ms, 01=16ms, 10=32ms,11=64ms)
  UCHAW   ucFIFODepth;                      // FIFO depth can be detected duwing vendow detection, hewe is hawdcoded pew memowy
  UCHAW   ucCDW_Bandwidth;                  // [0:3]=Wead CDW bandwidth, [4:7] - Wwite CDW Bandwidth

  UWONG   uwChannewMapCfg1;                 // channew mapping fow channew8~15
  UWONG   uwBankMapCfg;
  UWONG   uwWesewved;
  chaw    stwMemPNStwing[20];               // pawt numbew end with '0'.
}ATOM_VWAM_MODUWE_V8;


typedef stwuct _ATOM_VWAM_INFO_V2
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UCHAW                      ucNumOfVWAMModuwe;
  ATOM_VWAM_MODUWE           aVwamInfo[ATOM_MAX_NUMBEW_OF_VWAM_MODUWE];      // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
}ATOM_VWAM_INFO_V2;

typedef stwuct _ATOM_VWAM_INFO_V3
{
  ATOM_COMMON_TABWE_HEADEW  sHeadew;
  USHOWT                    usMemAdjustTbwOffset;                            // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy vendow specific MC adjust setting
  USHOWT                    usMemCwkPatchTbwOffset;                          // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy cwock specific MC setting
  USHOWT                    usWewseved;
  UCHAW                     aVID_PinsShift[9];                               // 8 bit stwap maximum+tewminatow
  UCHAW                     ucNumOfVWAMModuwe;
  ATOM_VWAM_MODUWE          aVwamInfo[ATOM_MAX_NUMBEW_OF_VWAM_MODUWE];       // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
  ATOM_INIT_WEG_BWOCK       asMemPatch;                                      // fow awwocation

}ATOM_VWAM_INFO_V3;

#define   ATOM_VWAM_INFO_WAST        ATOM_VWAM_INFO_V3

typedef stwuct _ATOM_VWAM_INFO_V4
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                     usMemAdjustTbwOffset;                           // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy vendow specific MC adjust setting
  USHOWT                     usMemCwkPatchTbwOffset;                         // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy cwock specific MC setting
  USHOWT                     usWewseved;
  UCHAW                      ucMemDQ7_0ByteWemap;                            // DQ wine byte wemap, =0: Memowy Data wine BYTE0, =1: BYTE1, =2: BYTE2, =3: BYTE3
  UWONG                      uwMemDQ7_0BitWemap;                             // each DQ wine ( 7~0) use 3bits, wike: DQ0=Bit[2:0], DQ1:[5:3], ... DQ7:[23:21]
  UCHAW                      ucWesewvde[4];
  UCHAW                      ucNumOfVWAMModuwe;
  ATOM_VWAM_MODUWE_V4        aVwamInfo[ATOM_MAX_NUMBEW_OF_VWAM_MODUWE];      // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
  ATOM_INIT_WEG_BWOCK        asMemPatch;                                     // fow awwocation
}ATOM_VWAM_INFO_V4;

typedef stwuct _ATOM_VWAM_INFO_HEADEW_V2_1
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                     usMemAdjustTbwOffset;                           // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy vendow specific MC adjust setting
  USHOWT                     usMemCwkPatchTbwOffset;                         // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy cwock specific MC setting
  USHOWT                     usPewBytePwesetOffset;                          // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow Pew Byte Offset Pweset Settings
  USHOWT                     usWesewved[3];
  UCHAW                      ucNumOfVWAMModuwe;                              // indicate numbew of VWAM moduwe
  UCHAW                      ucMemowyCwkPatchTbwVew;                         // vewsion of memowy AC timing wegistew wist
  UCHAW                      ucVwamModuweVew;                                // indicate ATOM_VWAM_MODUE vewsion
  UCHAW                      ucWesewved;
  ATOM_VWAM_MODUWE_V7        aVwamInfo[ATOM_MAX_NUMBEW_OF_VWAM_MODUWE];      // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
}ATOM_VWAM_INFO_HEADEW_V2_1;

typedef stwuct _ATOM_VWAM_INFO_HEADEW_V2_2
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                     usMemAdjustTbwOffset;                           // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy vendow specific MC adjust setting
  USHOWT                     usMemCwkPatchTbwOffset;                         // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow memowy cwock specific MC setting
  USHOWT                     usMcAdjustPewTiweTbwOffset;                     // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow Pew Byte Offset Pweset Settings
  USHOWT                     usMcPhyInitTabweOffset;                         // offset of ATOM_INIT_WEG_BWOCK stwuctuwe fow MC phy init set
  USHOWT                     usDwamDataWemapTbwOffset;                       // offset of ATOM_DWAM_DATA_WEMAP awway to indicate DWAM data wane to GPU mapping
  USHOWT                     usWesewved1;
  UCHAW                      ucNumOfVWAMModuwe;                              // indicate numbew of VWAM moduwe
  UCHAW                      ucMemowyCwkPatchTbwVew;                         // vewsion of memowy AC timing wegistew wist
  UCHAW                      ucVwamModuweVew;                                // indicate ATOM_VWAM_MODUE vewsion
  UCHAW                      ucMcPhyTiweNum;                                 // indicate the MCD tiwe numbew which use in DwamDataWemapTbw and usMcAdjustPewTiweTbwOffset
  ATOM_VWAM_MODUWE_V8        aVwamInfo[ATOM_MAX_NUMBEW_OF_VWAM_MODUWE];      // just fow awwocation, weaw numbew of bwocks is in ucNumOfVWAMModuwe;
}ATOM_VWAM_INFO_HEADEW_V2_2;


typedef stwuct _ATOM_DWAM_DATA_WEMAP
{
  UCHAW ucByteWemapCh0;
  UCHAW ucByteWemapCh1;
  UWONG uwByte0BitWemapCh0;
  UWONG uwByte1BitWemapCh0;
  UWONG uwByte2BitWemapCh0;
  UWONG uwByte3BitWemapCh0;
  UWONG uwByte0BitWemapCh1;
  UWONG uwByte1BitWemapCh1;
  UWONG uwByte2BitWemapCh1;
  UWONG uwByte3BitWemapCh1;
}ATOM_DWAM_DATA_WEMAP;

typedef stwuct _ATOM_VWAM_GPIO_DETECTION_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UCHAW                      aVID_PinsShift[9];                              // 8 bit stwap maximum+tewminatow
}ATOM_VWAM_GPIO_DETECTION_INFO;


typedef stwuct _ATOM_MEMOWY_TWAINING_INFO
{
   ATOM_COMMON_TABWE_HEADEW   sHeadew;
   UCHAW                                  ucTwainingWoop;
   UCHAW                                  ucWesewved[3];
   ATOM_INIT_WEG_BWOCK             asMemTwainingSetting;
}ATOM_MEMOWY_TWAINING_INFO;


typedef stwuct _ATOM_MEMOWY_TWAINING_INFO_V3_1
{
   ATOM_COMMON_TABWE_HEADEW   sHeadew;
   UWONG                      uwMCUcodeVewsion;
   USHOWT                     usMCIOInitWen;         //wen of ATOM_WEG_INIT_SETTING awway
   USHOWT                     usMCUcodeWen;          //wen of ATOM_MC_UCODE_DATA awway
   USHOWT                     usMCIOWegInitOffset;   //point of offset of ATOM_WEG_INIT_SETTING awway
   USHOWT                     usMCUcodeOffset;       //point of offset of MC uCode UWONG awway.
}ATOM_MEMOWY_TWAINING_INFO_V3_1;


typedef stwuct SW_I2C_CNTW_DATA_PAWAMETEWS
{
  UCHAW    ucContwow;
  UCHAW    ucData;
  UCHAW    ucSatus;
  UCHAW    ucTemp;
} SW_I2C_CNTW_DATA_PAWAMETEWS;

#define SW_I2C_CNTW_DATA_PS_AWWOCATION  SW_I2C_CNTW_DATA_PAWAMETEWS

typedef stwuct _SW_I2C_IO_DATA_PAWAMETEWS
{
  USHOWT   GPIO_Info;
  UCHAW    ucAct;
  UCHAW    ucData;
 } SW_I2C_IO_DATA_PAWAMETEWS;

#define SW_I2C_IO_DATA_PS_AWWOCATION  SW_I2C_IO_DATA_PAWAMETEWS

/****************************SW I2C CNTW DEFINITIONS**********************/
#define SW_I2C_IO_WESET       0
#define SW_I2C_IO_GET         1
#define SW_I2C_IO_DWIVE       2
#define SW_I2C_IO_SET         3
#define SW_I2C_IO_STAWT       4

#define SW_I2C_IO_CWOCK       0
#define SW_I2C_IO_DATA        0x80

#define SW_I2C_IO_ZEWO        0
#define SW_I2C_IO_ONE         0x100

#define SW_I2C_CNTW_WEAD      0
#define SW_I2C_CNTW_WWITE     1
#define SW_I2C_CNTW_STAWT     2
#define SW_I2C_CNTW_STOP      3
#define SW_I2C_CNTW_OPEN      4
#define SW_I2C_CNTW_CWOSE     5
#define SW_I2C_CNTW_WWITE1BIT 6

//==============================VESA definition Powtion===============================
#define VESA_OEM_PWODUCT_WEV                     '01.00'
#define VESA_MODE_ATTWIBUTE_MODE_SUPPOWT        0xBB   //wefew to VBE spec p.32, no TTY suppowt
#define VESA_MODE_WIN_ATTWIBUTE                       7
#define VESA_WIN_SIZE                                      64

typedef stwuct _PTW_32_BIT_STWUCTUWE
{
   USHOWT   Offset16;
   USHOWT   Segment16;
} PTW_32_BIT_STWUCTUWE;

typedef union _PTW_32_BIT_UNION
{
   PTW_32_BIT_STWUCTUWE   SegmentOffset;
   UWONG                       Ptw32_Bit;
} PTW_32_BIT_UNION;

typedef stwuct _VBE_1_2_INFO_BWOCK_UPDATABWE
{
   UCHAW                  VbeSignatuwe[4];
   USHOWT                VbeVewsion;
   PTW_32_BIT_UNION   OemStwingPtw;
   UCHAW                  Capabiwities[4];
   PTW_32_BIT_UNION   VideoModePtw;
   USHOWT                TotawMemowy;
} VBE_1_2_INFO_BWOCK_UPDATABWE;


typedef stwuct _VBE_2_0_INFO_BWOCK_UPDATABWE
{
   VBE_1_2_INFO_BWOCK_UPDATABWE   CommonBwock;
   USHOWT                         OemSoftWev;
   PTW_32_BIT_UNION            OemVendowNamePtw;
   PTW_32_BIT_UNION            OemPwoductNamePtw;
   PTW_32_BIT_UNION            OemPwoductWevPtw;
} VBE_2_0_INFO_BWOCK_UPDATABWE;

typedef union _VBE_VEWSION_UNION
{
   VBE_2_0_INFO_BWOCK_UPDATABWE   VBE_2_0_InfoBwock;
   VBE_1_2_INFO_BWOCK_UPDATABWE   VBE_1_2_InfoBwock;
} VBE_VEWSION_UNION;

typedef stwuct _VBE_INFO_BWOCK
{
   VBE_VEWSION_UNION         UpdatabweVBE_Info;
   UCHAW                        Wesewved[222];
   UCHAW                        OemData[256];
} VBE_INFO_BWOCK;

typedef stwuct _VBE_FP_INFO
{
  USHOWT   HSize;
  USHOWT   VSize;
  USHOWT   FPType;
  UCHAW    WedBPP;
  UCHAW    GweenBPP;
  UCHAW    BwueBPP;
  UCHAW    WesewvedBPP;
  UWONG    WsvdOffScwnMemSize;
  UWONG    WsvdOffScwnMEmPtw;
  UCHAW    Wesewved[14];
} VBE_FP_INFO;

typedef stwuct _VESA_MODE_INFO_BWOCK
{
// Mandatowy infowmation fow aww VBE wevisions
  USHOWT   ModeAttwibutes;  //         dw   ?   ; mode attwibutes
  UCHAW    WinAAttwibutes;  //         db   ?   ; window A attwibutes
  UCHAW    WinBAttwibutes;  //         db   ?   ; window B attwibutes
  USHOWT   WinGwanuwawity;  //         dw   ?   ; window gwanuwawity
  USHOWT   WinSize;         //         dw   ?   ; window size
  USHOWT   WinASegment;     //         dw   ?   ; window A stawt segment
  USHOWT   WinBSegment;     //         dw   ?   ; window B stawt segment
  UWONG    WinFuncPtw;      //         dd   ?   ; weaw mode pointew to window function
  USHOWT   BytesPewScanWine;//         dw   ?   ; bytes pew scan wine

//; Mandatowy infowmation fow VBE 1.2 and above
  USHOWT   XWesowution;      //         dw   ?   ; howizontaw wesowution in pixews ow chawactews
  USHOWT   YWesowution;      //         dw   ?   ; vewticaw wesowution in pixews ow chawactews
  UCHAW    XChawSize;        //         db   ?   ; chawactew ceww width in pixews
  UCHAW    YChawSize;        //         db   ?   ; chawactew ceww height in pixews
  UCHAW    NumbewOfPwanes;   //         db   ?   ; numbew of memowy pwanes
  UCHAW    BitsPewPixew;     //         db   ?   ; bits pew pixew
  UCHAW    NumbewOfBanks;    //         db   ?   ; numbew of banks
  UCHAW    MemowyModew;      //         db   ?   ; memowy modew type
  UCHAW    BankSize;         //         db   ?   ; bank size in KB
  UCHAW    NumbewOfImagePages;//        db   ?   ; numbew of images
  UCHAW    WesewvedFowPageFunction;//db   1   ; wesewved fow page function

//; Diwect Cowow fiewds(wequiwed fow diwect/6 and YUV/7 memowy modews)
  UCHAW    WedMaskSize;        //      db   ?   ; size of diwect cowow wed mask in bits
  UCHAW    WedFiewdPosition;   //      db   ?   ; bit position of wsb of wed mask
  UCHAW    GweenMaskSize;      //      db   ?   ; size of diwect cowow gween mask in bits
  UCHAW    GweenFiewdPosition; //      db   ?   ; bit position of wsb of gween mask
  UCHAW    BwueMaskSize;       //      db   ?   ; size of diwect cowow bwue mask in bits
  UCHAW    BwueFiewdPosition;  //      db   ?   ; bit position of wsb of bwue mask
  UCHAW    WsvdMaskSize;       //      db   ?   ; size of diwect cowow wesewved mask in bits
  UCHAW    WsvdFiewdPosition;  //      db   ?   ; bit position of wsb of wesewved mask
  UCHAW    DiwectCowowModeInfo;//      db   ?   ; diwect cowow mode attwibutes

//; Mandatowy infowmation fow VBE 2.0 and above
  UWONG    PhysBasePtw;        //      dd   ?   ; physicaw addwess fow fwat memowy fwame buffew
  UWONG    Wesewved_1;         //      dd   0   ; wesewved - awways set to 0
  USHOWT   Wesewved_2;         //     dw   0   ; wesewved - awways set to 0

//; Mandatowy infowmation fow VBE 3.0 and above
  USHOWT   WinBytesPewScanWine;  //   dw   ?   ; bytes pew scan wine fow wineaw modes
  UCHAW    BnkNumbewOfImagePages;//   db   ?   ; numbew of images fow banked modes
  UCHAW    WinNumbewOfImagPages; //   db   ?   ; numbew of images fow wineaw modes
  UCHAW    WinWedMaskSize;       //   db   ?   ; size of diwect cowow wed mask(wineaw modes)
  UCHAW    WinWedFiewdPosition;  //   db   ?   ; bit position of wsb of wed mask(wineaw modes)
  UCHAW    WinGweenMaskSize;     //   db   ?   ; size of diwect cowow gween mask(wineaw modes)
  UCHAW    WinGweenFiewdPosition;//   db   ?   ; bit position of wsb of gween mask(wineaw modes)
  UCHAW    WinBwueMaskSize;      //   db   ?   ; size of diwect cowow bwue mask(wineaw modes)
  UCHAW    WinBwueFiewdPosition; //   db   ?   ; bit position of wsb of bwue mask(wineaw modes)
  UCHAW    WinWsvdMaskSize;      //   db   ?   ; size of diwect cowow wesewved mask(wineaw modes)
  UCHAW    WinWsvdFiewdPosition; //   db   ?   ; bit position of wsb of wesewved mask(wineaw modes)
  UWONG    MaxPixewCwock;        //   dd   ?   ; maximum pixew cwock(in Hz) fow gwaphics mode
  UCHAW    Wesewved;             //   db   190 dup (0)
} VESA_MODE_INFO_BWOCK;

// BIOS function CAWWS
#define ATOM_BIOS_EXTENDED_FUNCTION_CODE        0xA0           // ATI Extended Function code
#define ATOM_BIOS_FUNCTION_COP_MODE             0x00
#define ATOM_BIOS_FUNCTION_SHOWT_QUEWY1         0x04
#define ATOM_BIOS_FUNCTION_SHOWT_QUEWY2         0x05
#define ATOM_BIOS_FUNCTION_SHOWT_QUEWY3         0x06
#define ATOM_BIOS_FUNCTION_GET_DDC              0x0B
#define ATOM_BIOS_FUNCTION_ASIC_DSTATE          0x0E
#define ATOM_BIOS_FUNCTION_DEBUG_PWAY           0x0F
#define ATOM_BIOS_FUNCTION_STV_STD              0x16
#define ATOM_BIOS_FUNCTION_DEVICE_DET           0x17
#define ATOM_BIOS_FUNCTION_DEVICE_SWITCH        0x18

#define ATOM_BIOS_FUNCTION_PANEW_CONTWOW        0x82
#define ATOM_BIOS_FUNCTION_OWD_DEVICE_DET       0x83
#define ATOM_BIOS_FUNCTION_OWD_DEVICE_SWITCH    0x84
#define ATOM_BIOS_FUNCTION_HW_ICON              0x8A
#define ATOM_BIOS_FUNCTION_SET_CMOS             0x8B
#define SUB_FUNCTION_UPDATE_DISPWAY_INFO        0x8000          // Sub function 80
#define SUB_FUNCTION_UPDATE_EXPANSION_INFO      0x8100          // Sub function 80

#define ATOM_BIOS_FUNCTION_DISPWAY_INFO         0x8D
#define ATOM_BIOS_FUNCTION_DEVICE_ON_OFF        0x8E
#define ATOM_BIOS_FUNCTION_VIDEO_STATE          0x8F
#define ATOM_SUB_FUNCTION_GET_CWITICAW_STATE    0x0300          // Sub function 03
#define ATOM_SUB_FUNCTION_GET_WIDSTATE          0x0700          // Sub function 7
#define ATOM_SUB_FUNCTION_THEWMAW_STATE_NOTICE  0x1400          // Notify cawwew the cuwwent thewmaw state
#define ATOM_SUB_FUNCTION_CWITICAW_STATE_NOTICE 0x8300          // Notify cawwew the cuwwent cwiticaw state
#define ATOM_SUB_FUNCTION_SET_WIDSTATE          0x8500          // Sub function 85
#define ATOM_SUB_FUNCTION_GET_WEQ_DISPWAY_FWOM_SBIOS_MODE 0x8900// Sub function 89
#define ATOM_SUB_FUNCTION_INFOWM_ADC_SUPPOWT    0x9400          // Notify cawwew that ADC is suppowted


#define ATOM_BIOS_FUNCTION_VESA_DPMS            0x4F10          // Set DPMS
#define ATOM_SUB_FUNCTION_SET_DPMS              0x0001          // BW: Sub function 01
#define ATOM_SUB_FUNCTION_GET_DPMS              0x0002          // BW: Sub function 02
#define ATOM_PAWAMETEW_VESA_DPMS_ON             0x0000          // BH Pawametew fow DPMS ON.
#define ATOM_PAWAMETEW_VESA_DPMS_STANDBY        0x0100          // BH Pawametew fow DPMS STANDBY
#define ATOM_PAWAMETEW_VESA_DPMS_SUSPEND        0x0200          // BH Pawametew fow DPMS SUSPEND
#define ATOM_PAWAMETEW_VESA_DPMS_OFF            0x0400          // BH Pawametew fow DPMS OFF
#define ATOM_PAWAMETEW_VESA_DPMS_WEDUCE_ON      0x0800          // BH Pawametew fow DPMS WEDUCE ON (NOT SUPPOWTED)

#define ATOM_BIOS_WETUWN_CODE_MASK              0x0000FF00W
#define ATOM_BIOS_WEG_HIGH_MASK                 0x0000FF00W
#define ATOM_BIOS_WEG_WOW_MASK                  0x000000FFW

// stwuctuwe used fow VBIOS onwy

//DispOutInfoTabwe
typedef stwuct _ASIC_TWANSMITTEW_INFO
{
   USHOWT usTwansmittewObjId;
   USHOWT usSuppowtDevice;
   UCHAW  ucTwansmittewCmdTbwId;
   UCHAW  ucConfig;
   UCHAW  ucEncodewID;                //avaiwabwe 1st encodew ( defauwt )
   UCHAW  ucOptionEncodewID;    //avaiwabwe 2nd encodew ( optionaw )
   UCHAW  uc2ndEncodewID;
   UCHAW  ucWesewved;
}ASIC_TWANSMITTEW_INFO;

#define ASIC_TWANSMITTEW_INFO_CONFIG__DVO_SDW_MODE          0x01
#define ASIC_TWANSMITTEW_INFO_CONFIG__COHEWENT_MODE         0x02
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEWOBJ_ID_MASK    0xc4
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_A             0x00
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_B             0x04
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_C             0x40
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_D             0x44
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_E             0x80
#define ASIC_TWANSMITTEW_INFO_CONFIG__ENCODEW_F             0x84

typedef stwuct _ASIC_ENCODEW_INFO
{
   UCHAW ucEncodewID;
   UCHAW ucEncodewConfig;
  USHOWT usEncodewCmdTbwId;
}ASIC_ENCODEW_INFO;

typedef stwuct _ATOM_DISP_OUT_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
   USHOWT ptwTwansmittewInfo;
   USHOWT ptwEncodewInfo;
   ASIC_TWANSMITTEW_INFO  asTwansmittewInfo[1];
   ASIC_ENCODEW_INFO      asEncodewInfo[1];
}ATOM_DISP_OUT_INFO;


typedef stwuct _ATOM_DISP_OUT_INFO_V2
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
   USHOWT ptwTwansmittewInfo;
   USHOWT ptwEncodewInfo;
  USHOWT ptwMainCawwPawsewFaw;                  // diwect addwess of main pawsew caww in VBIOS binawy.
   ASIC_TWANSMITTEW_INFO  asTwansmittewInfo[1];
   ASIC_ENCODEW_INFO      asEncodewInfo[1];
}ATOM_DISP_OUT_INFO_V2;


typedef stwuct _ATOM_DISP_CWOCK_ID {
  UCHAW ucPpwwId;
  UCHAW ucPpwwAttwibute;
}ATOM_DISP_CWOCK_ID;

// ucPpwwAttwibute
#define CWOCK_SOUWCE_SHAWEABWE            0x01
#define CWOCK_SOUWCE_DP_MODE              0x02
#define CWOCK_SOUWCE_NONE_DP_MODE         0x04

//DispOutInfoTabwe
typedef stwuct _ASIC_TWANSMITTEW_INFO_V2
{
   USHOWT usTwansmittewObjId;
   USHOWT usDispCwkIdOffset;    // point to cwock souwce id wist suppowted by Encodew Object
  UCHAW  ucTwansmittewCmdTbwId;
   UCHAW  ucConfig;
   UCHAW  ucEncodewID;                // avaiwabwe 1st encodew ( defauwt )
   UCHAW  ucOptionEncodewID;    // avaiwabwe 2nd encodew ( optionaw )
   UCHAW  uc2ndEncodewID;
   UCHAW  ucWesewved;
}ASIC_TWANSMITTEW_INFO_V2;

typedef stwuct _ATOM_DISP_OUT_INFO_V3
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT ptwTwansmittewInfo;
  USHOWT ptwEncodewInfo;
  USHOWT ptwMainCawwPawsewFaw;                  // diwect addwess of main pawsew caww in VBIOS binawy.
  USHOWT usWesewved;
  UCHAW  ucDCEWevision;
  UCHAW  ucMaxDispEngineNum;
  UCHAW  ucMaxActiveDispEngineNum;
  UCHAW  ucMaxPPWWNum;
  UCHAW  ucCoweWefCwkSouwce;                    // vawue of COWE_WEF_CWK_SOUWCE
  UCHAW  ucDispCaps;
  UCHAW  ucWesewved[2];
  ASIC_TWANSMITTEW_INFO_V2  asTwansmittewInfo[1];     // fow awwigment onwy
}ATOM_DISP_OUT_INFO_V3;

//ucDispCaps
#define DISPWAY_CAPS__DP_PCWK_FWOM_PPWW        0x01
#define DISPWAY_CAPS__FOWCE_DISPDEV_CONNECTED  0x02

typedef enum COWE_WEF_CWK_SOUWCE{
  CWOCK_SWC_XTAWIN=0,
  CWOCK_SWC_XO_IN=1,
  CWOCK_SWC_XO_IN2=2,
}COWE_WEF_CWK_SOUWCE;

// DispDevicePwiowityInfo
typedef stwuct _ATOM_DISPWAY_DEVICE_PWIOWITY_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
   USHOWT asDevicePwiowity[16];
}ATOM_DISPWAY_DEVICE_PWIOWITY_INFO;

//PwocessAuxChannewTwansactionTabwe
typedef stwuct _PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS
{
   USHOWT  wpAuxWequest;
   USHOWT  wpDataOut;
   UCHAW   ucChannewID;
   union
   {
  UCHAW   ucWepwyStatus;
   UCHAW   ucDeway;
   };
  UCHAW   ucDataOutWen;
   UCHAW   ucWesewved;
}PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS;

//PwocessAuxChannewTwansactionTabwe
typedef stwuct _PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS_V2
{
   USHOWT   wpAuxWequest;
   USHOWT  wpDataOut;
   UCHAW      ucChannewID;
   union
   {
  UCHAW   ucWepwyStatus;
   UCHAW   ucDeway;
   };
  UCHAW   ucDataOutWen;
   UCHAW   ucHPD_ID;                                       //=0: HPD1, =1: HPD2, =2: HPD3, =3: HPD4, =4: HPD5, =5: HPD6
}PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS_V2;

#define PWOCESS_AUX_CHANNEW_TWANSACTION_PS_AWWOCATION         PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS

//GetSinkType

typedef stwuct _DP_ENCODEW_SEWVICE_PAWAMETEWS
{
   USHOWT ucWinkCwock;
   union
   {
   UCHAW ucConfig;            // fow DP twaining command
   UCHAW ucI2cId;            // use fow GET_SINK_TYPE command
   };
   UCHAW ucAction;
   UCHAW ucStatus;
   UCHAW ucWaneNum;
   UCHAW ucWesewved[2];
}DP_ENCODEW_SEWVICE_PAWAMETEWS;

// ucAction
#define ATOM_DP_ACTION_GET_SINK_TYPE                     0x01

#define DP_ENCODEW_SEWVICE_PS_AWWOCATION            WWITE_ONE_BYTE_HW_I2C_DATA_PAWAMETEWS


typedef stwuct _DP_ENCODEW_SEWVICE_PAWAMETEWS_V2
{
   USHOWT usExtEncodewObjId;   // Extewnaw Encodew Object Id, output pawametew onwy, use when ucAction = DP_SEWVICE_V2_ACTION_DET_EXT_CONNECTION
  UCHAW  ucAuxId;
  UCHAW  ucAction;
  UCHAW  ucSinkType;          // Iput and Output pawametews.
  UCHAW  ucHPDId;             // Input pawametew, used when ucAction = DP_SEWVICE_V2_ACTION_DET_EXT_CONNECTION
   UCHAW  ucWesewved[2];
}DP_ENCODEW_SEWVICE_PAWAMETEWS_V2;

typedef stwuct _DP_ENCODEW_SEWVICE_PS_AWWOCATION_V2
{
  DP_ENCODEW_SEWVICE_PAWAMETEWS_V2 asDPSewvicePawam;
  PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS_V2 asAuxPawam;
}DP_ENCODEW_SEWVICE_PS_AWWOCATION_V2;

// ucAction
#define DP_SEWVICE_V2_ACTION_GET_SINK_TYPE                     0x01
#define DP_SEWVICE_V2_ACTION_DET_WCD_CONNECTION             0x02


// DP_TWAINING_TABWE
#define DPCD_SET_WINKWATE_WANENUM_PATTEWN1_TBW_ADDW            ATOM_DP_TWAINING_TBW_ADDW
#define DPCD_SET_SS_CNTW_TBW_ADDW                                       (ATOM_DP_TWAINING_TBW_ADDW + 8 )
#define DPCD_SET_WANE_VSWING_PWEEMP_TBW_ADDW                     (ATOM_DP_TWAINING_TBW_ADDW + 16 )
#define DPCD_SET_TWAINING_PATTEWN0_TBW_ADDW                        (ATOM_DP_TWAINING_TBW_ADDW + 24 )
#define DPCD_SET_TWAINING_PATTEWN2_TBW_ADDW                        (ATOM_DP_TWAINING_TBW_ADDW + 32)
#define DPCD_GET_WINKWATE_WANENUM_SS_TBW_ADDW                     (ATOM_DP_TWAINING_TBW_ADDW + 40)
#define   DPCD_GET_WANE_STATUS_ADJUST_TBW_ADDW                     (ATOM_DP_TWAINING_TBW_ADDW + 48)
#define DP_I2C_AUX_DDC_WWITE_STAWT_TBW_ADDW                        (ATOM_DP_TWAINING_TBW_ADDW + 60)
#define DP_I2C_AUX_DDC_WWITE_TBW_ADDW                                 (ATOM_DP_TWAINING_TBW_ADDW + 64)
#define DP_I2C_AUX_DDC_WEAD_STAWT_TBW_ADDW                        (ATOM_DP_TWAINING_TBW_ADDW + 72)
#define DP_I2C_AUX_DDC_WEAD_TBW_ADDW                                 (ATOM_DP_TWAINING_TBW_ADDW + 76)
#define DP_I2C_AUX_DDC_WWITE_END_TBW_ADDW                 (ATOM_DP_TWAINING_TBW_ADDW + 80)
#define DP_I2C_AUX_DDC_WEAD_END_TBW_ADDW                           (ATOM_DP_TWAINING_TBW_ADDW + 84)


typedef stwuct _PWOCESS_I2C_CHANNEW_TWANSACTION_PAWAMETEWS
{
   UCHAW   ucI2CSpeed;
    union
   {
   UCHAW ucWegIndex;
   UCHAW ucStatus;
   };
   USHOWT  wpI2CDataOut;
  UCHAW   ucFwag;
  UCHAW   ucTwansBytes;
  UCHAW   ucSwaveAddw;
  UCHAW   ucWineNumbew;
}PWOCESS_I2C_CHANNEW_TWANSACTION_PAWAMETEWS;

#define PWOCESS_I2C_CHANNEW_TWANSACTION_PS_AWWOCATION       PWOCESS_I2C_CHANNEW_TWANSACTION_PAWAMETEWS

//ucFwag
#define HW_I2C_WWITE        1
#define HW_I2C_WEAD         0
#define I2C_2BYTE_ADDW      0x02

/****************************************************************************/
// Stwuctuwes used by HW_Misc_OpewationTabwe
/****************************************************************************/
typedef stwuct  _ATOM_HW_MISC_OPEWATION_INPUT_PAWAMETEW_V1_1
{
  UCHAW  ucCmd;                //  Input: To teww which action to take
  UCHAW  ucWesewved[3];
  UWONG  uwWesewved;
}ATOM_HW_MISC_OPEWATION_INPUT_PAWAMETEW_V1_1;

typedef stwuct  _ATOM_HW_MISC_OPEWATION_OUTPUT_PAWAMETEW_V1_1
{
  UCHAW  ucWetuwnCode;        // Output: Wetuwn vawue base on action was taken
  UCHAW  ucWesewved[3];
  UWONG  uwWesewved;
}ATOM_HW_MISC_OPEWATION_OUTPUT_PAWAMETEW_V1_1;

// Actions code
#define  ATOM_GET_SDI_SUPPOWT              0xF0

// Wetuwn code
#define  ATOM_UNKNOWN_CMD                   0
#define  ATOM_FEATUWE_NOT_SUPPOWTED         1
#define  ATOM_FEATUWE_SUPPOWTED             2

typedef stwuct _ATOM_HW_MISC_OPEWATION_PS_AWWOCATION
{
   ATOM_HW_MISC_OPEWATION_INPUT_PAWAMETEW_V1_1        sInput_Output;
   PWOCESS_I2C_CHANNEW_TWANSACTION_PAWAMETEWS         sWesewved;
}ATOM_HW_MISC_OPEWATION_PS_AWWOCATION;

/****************************************************************************/

typedef stwuct _SET_HWBWOCK_INSTANCE_PAWAMETEW_V2
{
   UCHAW ucHWBwkInst;                // HW bwock instance, 0, 1, 2, ...
   UCHAW ucWesewved[3];
}SET_HWBWOCK_INSTANCE_PAWAMETEW_V2;

#define HWBWKINST_INSTANCE_MASK       0x07
#define HWBWKINST_HWBWK_MASK          0xF0
#define HWBWKINST_HWBWK_SHIFT         0x04

//ucHWBwock
#define SEWECT_DISP_ENGINE            0
#define SEWECT_DISP_PWW               1
#define SEWECT_DCIO_UNIPHY_WINK0      2
#define SEWECT_DCIO_UNIPHY_WINK1      3
#define SEWECT_DCIO_IMPCAW            4
#define SEWECT_DCIO_DIG               6
#define SEWECT_CWTC_PIXEW_WATE        7
#define SEWECT_VGA_BWK                8

// DIGTwansmittewInfoTabwe stwuctuwe used to pwogwam UNIPHY settings
typedef stwuct _DIG_TWANSMITTEW_INFO_HEADEW_V3_1{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT usDPVsPweEmphSettingOffset;     // offset of PHY_ANAWOG_SETTING_INFO * with DP Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT usPhyAnawogWegWistOffset;       // offset of CWOCK_CONDITION_WEGESTEW_INFO* with None-DP mode Anawog Setting's wegistew Info
  USHOWT usPhyAnawogSettingOffset;       // offset of CWOCK_CONDITION_SETTING_ENTWY* with None-DP mode Anawog Setting fow each wink cwock wange
  USHOWT usPhyPwwWegWistOffset;          // offset of CWOCK_CONDITION_WEGESTEW_INFO* with Phy Pww wegistew Info
  USHOWT usPhyPwwSettingOffset;          // offset of CWOCK_CONDITION_SETTING_ENTWY* with Phy Pww Settings
}DIG_TWANSMITTEW_INFO_HEADEW_V3_1;

typedef stwuct _DIG_TWANSMITTEW_INFO_HEADEW_V3_2{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT usDPVsPweEmphSettingOffset;     // offset of PHY_ANAWOG_SETTING_INFO * with DP Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT usPhyAnawogWegWistOffset;       // offset of CWOCK_CONDITION_WEGESTEW_INFO* with None-DP mode Anawog Setting's wegistew Info
  USHOWT usPhyAnawogSettingOffset;       // offset of CWOCK_CONDITION_SETTING_ENTWY* with None-DP mode Anawog Setting fow each wink cwock wange
  USHOWT usPhyPwwWegWistOffset;          // offset of CWOCK_CONDITION_WEGESTEW_INFO* with Phy Pww wegistew Info
  USHOWT usPhyPwwSettingOffset;          // offset of CWOCK_CONDITION_SETTING_ENTWY* with Phy Pww Settings
  USHOWT usDPSSWegWistOffset;            // offset of CWOCK_CONDITION_WEGESTEW_INFO* with Phy SS Pww wegistew Info
  USHOWT usDPSSSettingOffset;            // offset of CWOCK_CONDITION_SETTING_ENTWY* with Phy SS Pww Settings
}DIG_TWANSMITTEW_INFO_HEADEW_V3_2;


typedef stwuct _DIG_TWANSMITTEW_INFO_HEADEW_V3_3{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT usDPVsPweEmphSettingOffset;     // offset of PHY_ANAWOG_SETTING_INFO * with DP Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT usPhyAnawogWegWistOffset;       // offset of CWOCK_CONDITION_WEGESTEW_INFO* with None-DP mode Anawog Setting's wegistew Info
  USHOWT usPhyAnawogSettingOffset;       // offset of CWOCK_CONDITION_SETTING_ENTWY* with None-DP mode Anawog Setting fow each wink cwock wange
  USHOWT usPhyPwwWegWistOffset;          // offset of CWOCK_CONDITION_WEGESTEW_INFO* with Phy Pww wegistew Info
  USHOWT usPhyPwwSettingOffset;          // offset of CWOCK_CONDITION_SETTING_ENTWY* with Phy Pww Settings
  USHOWT usDPSSWegWistOffset;            // offset of CWOCK_CONDITION_WEGESTEW_INFO* with Phy SS Pww wegistew Info
  USHOWT usDPSSSettingOffset;            // offset of CWOCK_CONDITION_SETTING_ENTWY* with Phy SS Pww Settings
  USHOWT usEDPVsWegacyModeOffset;        // offset of PHY_ANAWOG_SETTING_INFO * with eDP Wegacy Mode Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT useDPVsWowVdiffModeOffset;      // offset of PHY_ANAWOG_SETTING_INFO * with eDP Wow VDiff Mode Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT useDPVsHighVdiffModeOffset;     // offset of PHY_ANAWOG_SETTING_INFO * with eDP High VDiff Mode Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT useDPVsStwetchModeOffset;       // offset of PHY_ANAWOG_SETTING_INFO * with eDP Stwetch Mode Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT useDPVsSingweVdiffModeOffset;   // offset of PHY_ANAWOG_SETTING_INFO * with eDP Singwe Vdiff Mode Vowtage Swing and Pwe-Emphasis fow each Wink cwock
  USHOWT useDPVsVawiabwePwemModeOffset;  // offset of PHY_ANAWOG_SETTING_INFO * with eDP Singwe Vidff+Vawiabwe PweEmphasis Vowtage Swing and Pwe-Emphasis fow each Wink cwock
}DIG_TWANSMITTEW_INFO_HEADEW_V3_3;


typedef stwuct _CWOCK_CONDITION_WEGESTEW_INFO{
  USHOWT usWegistewIndex;
  UCHAW  ucStawtBit;
  UCHAW  ucEndBit;
}CWOCK_CONDITION_WEGESTEW_INFO;

typedef stwuct _CWOCK_CONDITION_SETTING_ENTWY{
  USHOWT usMaxCwockFweq;
  UCHAW  ucEncodeMode;
  UCHAW  ucPhySew;
  UWONG  uwAnawogSetting[1];
}CWOCK_CONDITION_SETTING_ENTWY;

typedef stwuct _CWOCK_CONDITION_SETTING_INFO{
  USHOWT usEntwySize;
  CWOCK_CONDITION_SETTING_ENTWY asCwkCondSettingEntwy[1];
}CWOCK_CONDITION_SETTING_INFO;

typedef stwuct _PHY_CONDITION_WEG_VAW{
  UWONG  uwCondition;
  UWONG  uwWegVaw;
}PHY_CONDITION_WEG_VAW;

typedef stwuct _PHY_CONDITION_WEG_VAW_V2{
  UWONG  uwCondition;
  UCHAW  ucCondition2;
  UWONG  uwWegVaw;
}PHY_CONDITION_WEG_VAW_V2;

typedef stwuct _PHY_CONDITION_WEG_INFO{
  USHOWT usWegIndex;
  USHOWT usSize;
  PHY_CONDITION_WEG_VAW asWegVaw[1];
}PHY_CONDITION_WEG_INFO;

typedef stwuct _PHY_CONDITION_WEG_INFO_V2{
  USHOWT usWegIndex;
  USHOWT usSize;
  PHY_CONDITION_WEG_VAW_V2 asWegVaw[1];
}PHY_CONDITION_WEG_INFO_V2;

typedef stwuct _PHY_ANAWOG_SETTING_INFO{
  UCHAW  ucEncodeMode;
  UCHAW  ucPhySew;
  USHOWT usSize;
  PHY_CONDITION_WEG_INFO  asAnawogSetting[1];
}PHY_ANAWOG_SETTING_INFO;

typedef stwuct _PHY_ANAWOG_SETTING_INFO_V2{
  UCHAW  ucEncodeMode;
  UCHAW  ucPhySew;
  USHOWT usSize;
  PHY_CONDITION_WEG_INFO_V2  asAnawogSetting[1];
}PHY_ANAWOG_SETTING_INFO_V2;


typedef stwuct _GFX_HAVESTING_PAWAMETEWS {
  UCHAW ucGfxBwkId;                        //GFX bwk id to be hawvested, wike CU, WB ow PWIM
  UCHAW ucWesewved;                        //wesewved
  UCHAW ucActiveUnitNumPewSH;              //wequested active CU/WB/PWIM numbew pew shadew awway
  UCHAW ucMaxUnitNumPewSH;                 //max CU/WB/PWIM numbew pew shadew awway
} GFX_HAVESTING_PAWAMETEWS;

//ucGfxBwkId
#define GFX_HAWVESTING_CU_ID               0
#define GFX_HAWVESTING_WB_ID               1
#define GFX_HAWVESTING_PWIM_ID             2


typedef stwuct _VBIOS_WOM_HEADEW{
  UCHAW  PciWomSignatuwe[2];
  UCHAW  ucPciWomSizeIn512bytes;
  UCHAW  ucJumpCoweMainInitBIOS;
  USHOWT usWabewCoweMainInitBIOS;
  UCHAW  PciWesewvedSpace[18];
  USHOWT usPciDataStwuctuweOffset;
  UCHAW  Wsvd1d_1a[4];
  chaw   stwIbm[3];
  UCHAW  CheckSum[14];
  UCHAW  ucBiosMsgNumbew;
  chaw   stw761295520[16];
  USHOWT usWabewCoweVPOSTNoMode;
  USHOWT usSpeciawPostOffset;
  UCHAW  ucSpeicawPostImageSizeIn512Bytes;
  UCHAW  Wsved47_45[3];
  USHOWT usWOM_HeadewInfowmationTabweOffset;
  UCHAW  Wsved4f_4a[6];
  chaw   stwBuiwdTimeStamp[20];
  UCHAW  ucJumpCoweXFuncFawHandwew;
  USHOWT usCoweXFuncFawHandwewOffset;
  UCHAW  ucWsved67;
  UCHAW  ucJumpCoweVFuncFawHandwew;
  USHOWT usCoweVFuncFawHandwewOffset;
  UCHAW  Wsved6d_6b[3];
  USHOWT usATOM_BIOS_MESSAGE_Offset;
}VBIOS_WOM_HEADEW;

/****************************************************************************/
//Powtion VI: Definitinos fow vbios MC scwatch wegistews that dwivew used
/****************************************************************************/

#define MC_MISC0__MEMOWY_TYPE_MASK    0xF0000000
#define MC_MISC0__MEMOWY_TYPE__GDDW1  0x10000000
#define MC_MISC0__MEMOWY_TYPE__DDW2   0x20000000
#define MC_MISC0__MEMOWY_TYPE__GDDW3  0x30000000
#define MC_MISC0__MEMOWY_TYPE__GDDW4  0x40000000
#define MC_MISC0__MEMOWY_TYPE__GDDW5  0x50000000
#define MC_MISC0__MEMOWY_TYPE__HBM    0x60000000
#define MC_MISC0__MEMOWY_TYPE__DDW3   0xB0000000

#define ATOM_MEM_TYPE_DDW_STWING      "DDW"
#define ATOM_MEM_TYPE_DDW2_STWING     "DDW2"
#define ATOM_MEM_TYPE_GDDW3_STWING    "GDDW3"
#define ATOM_MEM_TYPE_GDDW4_STWING    "GDDW4"
#define ATOM_MEM_TYPE_GDDW5_STWING    "GDDW5"
#define ATOM_MEM_TYPE_HBM_STWING      "HBM"
#define ATOM_MEM_TYPE_DDW3_STWING     "DDW3"

/****************************************************************************/
//Powtion VII: Definitinos being obosewete
/****************************************************************************/

//==========================================================================================
//Wemove the definitions bewow when dwivew is weady!
typedef stwuct _ATOM_DAC_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT                   usMaxFwequency;      // in 10kHz unit
  USHOWT                   usWesewved;
}ATOM_DAC_INFO;


typedef stwuct  _COMPASSIONATE_DATA
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;

  //==============================  DAC1 powtion
  UCHAW   ucDAC1_BG_Adjustment;
  UCHAW   ucDAC1_DAC_Adjustment;
  USHOWT  usDAC1_FOWCE_Data;
  //==============================  DAC2 powtion
  UCHAW   ucDAC2_CWT2_BG_Adjustment;
  UCHAW   ucDAC2_CWT2_DAC_Adjustment;
  USHOWT  usDAC2_CWT2_FOWCE_Data;
  USHOWT  usDAC2_CWT2_MUX_WegistewIndex;
  UCHAW   ucDAC2_CWT2_MUX_WegistewInfo;     //Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Wow
  UCHAW   ucDAC2_NTSC_BG_Adjustment;
  UCHAW   ucDAC2_NTSC_DAC_Adjustment;
  USHOWT  usDAC2_TV1_FOWCE_Data;
  USHOWT  usDAC2_TV1_MUX_WegistewIndex;
  UCHAW   ucDAC2_TV1_MUX_WegistewInfo;      //Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Wow
  UCHAW   ucDAC2_CV_BG_Adjustment;
  UCHAW   ucDAC2_CV_DAC_Adjustment;
  USHOWT  usDAC2_CV_FOWCE_Data;
  USHOWT  usDAC2_CV_MUX_WegistewIndex;
  UCHAW   ucDAC2_CV_MUX_WegistewInfo;       //Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Wow
  UCHAW   ucDAC2_PAW_BG_Adjustment;
  UCHAW   ucDAC2_PAW_DAC_Adjustment;
  USHOWT  usDAC2_TV2_FOWCE_Data;
}COMPASSIONATE_DATA;

/****************************Suppowted Device Info Tabwe Definitions**********************/
//  ucConnectInfo:
//    [7:4] - connectow type
//      = 1   - VGA connectow
//      = 2   - DVI-I
//      = 3   - DVI-D
//      = 4   - DVI-A
//      = 5   - SVIDEO
//      = 6   - COMPOSITE
//      = 7   - WVDS
//      = 8   - DIGITAW WINK
//      = 9   - SCAWT
//      = 0xA - HDMI_type A
//      = 0xB - HDMI_type B
//      = 0xE - Speciaw case1 (DVI+DIN)
//      Othews=TBD
//    [3:0] - DAC Associated
//      = 0   - no DAC
//      = 1   - DACA
//      = 2   - DACB
//      = 3   - Extewnaw DAC
//      Othews=TBD
//

typedef stwuct _ATOM_CONNECTOW_INFO
{
#if ATOM_BIG_ENDIAN
  UCHAW   bfConnectowType:4;
  UCHAW   bfAssociatedDAC:4;
#ewse
  UCHAW   bfAssociatedDAC:4;
  UCHAW   bfConnectowType:4;
#endif
}ATOM_CONNECTOW_INFO;

typedef union _ATOM_CONNECTOW_INFO_ACCESS
{
  ATOM_CONNECTOW_INFO sbfAccess;
  UCHAW               ucAccess;
}ATOM_CONNECTOW_INFO_ACCESS;

typedef stwuct _ATOM_CONNECTOW_INFO_I2C
{
  ATOM_CONNECTOW_INFO_ACCESS sucConnectowInfo;
  ATOM_I2C_ID_CONFIG_ACCESS  sucI2cId;
}ATOM_CONNECTOW_INFO_I2C;


typedef stwuct _ATOM_SUPPOWTED_DEVICES_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                    usDeviceSuppowt;
  ATOM_CONNECTOW_INFO_I2C   asConnInfo[ATOM_MAX_SUPPOWTED_DEVICE_INFO];
}ATOM_SUPPOWTED_DEVICES_INFO;

#define NO_INT_SWC_MAPPED       0xFF

typedef stwuct _ATOM_CONNECTOW_INC_SWC_BITMAP
{
  UCHAW   ucIntSwcBitmap;
}ATOM_CONNECTOW_INC_SWC_BITMAP;

typedef stwuct _ATOM_SUPPOWTED_DEVICES_INFO_2
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  USHOWT                        usDeviceSuppowt;
  ATOM_CONNECTOW_INFO_I2C       asConnInfo[ATOM_MAX_SUPPOWTED_DEVICE_INFO_2];
  ATOM_CONNECTOW_INC_SWC_BITMAP asIntSwcInfo[ATOM_MAX_SUPPOWTED_DEVICE_INFO_2];
}ATOM_SUPPOWTED_DEVICES_INFO_2;

typedef stwuct _ATOM_SUPPOWTED_DEVICES_INFO_2d1
{
  ATOM_COMMON_TABWE_HEADEW      sHeadew;
  USHOWT                        usDeviceSuppowt;
  ATOM_CONNECTOW_INFO_I2C       asConnInfo[ATOM_MAX_SUPPOWTED_DEVICE];
  ATOM_CONNECTOW_INC_SWC_BITMAP asIntSwcInfo[ATOM_MAX_SUPPOWTED_DEVICE];
}ATOM_SUPPOWTED_DEVICES_INFO_2d1;

#define ATOM_SUPPOWTED_DEVICES_INFO_WAST ATOM_SUPPOWTED_DEVICES_INFO_2d1



typedef stwuct _ATOM_MISC_CONTWOW_INFO
{
   USHOWT usFwequency;
   UCHAW  ucPWW_ChawgePump;                            // PWW chawge-pump gain contwow
   UCHAW  ucPWW_DutyCycwe;                            // PWW duty cycwe contwow
   UCHAW  ucPWW_VCO_Gain;                              // PWW VCO gain contwow
   UCHAW  ucPWW_VowtageSwing;                         // PWW dwivew vowtage swing contwow
}ATOM_MISC_CONTWOW_INFO;


#define ATOM_MAX_MISC_INFO       4

typedef stwuct _ATOM_TMDS_INFO
{
  ATOM_COMMON_TABWE_HEADEW sHeadew;
  USHOWT                     usMaxFwequency;             // in 10Khz
  ATOM_MISC_CONTWOW_INFO            asMiscInfo[ATOM_MAX_MISC_INFO];
}ATOM_TMDS_INFO;


typedef stwuct _ATOM_ENCODEW_ANAWOG_ATTWIBUTE
{
  UCHAW ucTVStandawd;     //Same as TV standawds defined above,
  UCHAW ucPadding[1];
}ATOM_ENCODEW_ANAWOG_ATTWIBUTE;

typedef stwuct _ATOM_ENCODEW_DIGITAW_ATTWIBUTE
{
  UCHAW ucAttwibute;      //Same as othew digitaw encodew attwibutes defined above
  UCHAW ucPadding[1];
}ATOM_ENCODEW_DIGITAW_ATTWIBUTE;

typedef union _ATOM_ENCODEW_ATTWIBUTE
{
  ATOM_ENCODEW_ANAWOG_ATTWIBUTE sAwgAttwib;
  ATOM_ENCODEW_DIGITAW_ATTWIBUTE sDigAttwib;
}ATOM_ENCODEW_ATTWIBUTE;


typedef stwuct _DVO_ENCODEW_CONTWOW_PAWAMETEWS
{
  USHOWT usPixewCwock;
  USHOWT usEncodewID;
  UCHAW  ucDeviceType;                                    //Use ATOM_DEVICE_xxx1_Index to indicate device type onwy.
  UCHAW  ucAction;                                          //ATOM_ENABWE/ATOM_DISABWE/ATOM_HPD_INIT
  ATOM_ENCODEW_ATTWIBUTE usDevAttw;
}DVO_ENCODEW_CONTWOW_PAWAMETEWS;

typedef stwuct _DVO_ENCODEW_CONTWOW_PS_AWWOCATION
{
  DVO_ENCODEW_CONTWOW_PAWAMETEWS    sDVOEncodew;
  WWITE_ONE_BYTE_HW_I2C_DATA_PS_AWWOCATION      sWesewved;     //Cawwew doesn't need to init this powtion
}DVO_ENCODEW_CONTWOW_PS_AWWOCATION;


#define ATOM_XTMDS_ASIC_SI164_ID        1
#define ATOM_XTMDS_ASIC_SI178_ID        2
#define ATOM_XTMDS_ASIC_TFP513_ID       3
#define ATOM_XTMDS_SUPPOWTED_SINGWEWINK 0x00000001
#define ATOM_XTMDS_SUPPOWTED_DUAWWINK   0x00000002
#define ATOM_XTMDS_MVPU_FPGA            0x00000004


typedef stwuct _ATOM_XTMDS_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  USHOWT                     usSingweWinkMaxFwequency;
  ATOM_I2C_ID_CONFIG_ACCESS  sucI2cId;           //Point the ID on which I2C is used to contwow extewnaw chip
  UCHAW                      ucXtwansimittewID;
  UCHAW                      ucSuppowtedWink;    // Bit fiewd, bit0=1, singwe wink suppowted;bit1=1,duaw wink suppowted
  UCHAW                      ucSequnceAwtewID;   // Even with the same extewnaw TMDS asic, it's possibwe that the pwogwam seqence awtews
                                                 // due to design. This ID is used to awewt dwivew that the sequence is not "standawd"!
  UCHAW                      ucMastewAddwess;    // Addwess to contwow Mastew xTMDS Chip
  UCHAW                      ucSwaveAddwess;     // Addwess to contwow Swave xTMDS Chip
}ATOM_XTMDS_INFO;

typedef stwuct _DFP_DPMS_STATUS_CHANGE_PAWAMETEWS
{
  UCHAW ucEnabwe;                     // ATOM_ENABWE=On ow ATOM_DISABWE=Off
  UCHAW ucDevice;                     // ATOM_DEVICE_DFP1_INDEX....
  UCHAW ucPadding[2];
}DFP_DPMS_STATUS_CHANGE_PAWAMETEWS;

/****************************Wegacy Powew Pway Tabwe Definitions **********************/

//Definitions fow uwPowewPwayMiscInfo
#define ATOM_PM_MISCINFO_SPWIT_CWOCK                     0x00000000W
#define ATOM_PM_MISCINFO_USING_MCWK_SWC                  0x00000001W
#define ATOM_PM_MISCINFO_USING_SCWK_SWC                  0x00000002W

#define ATOM_PM_MISCINFO_VOWTAGE_DWOP_SUPPOWT            0x00000004W
#define ATOM_PM_MISCINFO_VOWTAGE_DWOP_ACTIVE_HIGH        0x00000008W

#define ATOM_PM_MISCINFO_WOAD_PEWFOWMANCE_EN             0x00000010W

#define ATOM_PM_MISCINFO_ENGINE_CWOCK_CONTWW_EN          0x00000020W
#define ATOM_PM_MISCINFO_MEMOWY_CWOCK_CONTWW_EN          0x00000040W
#define ATOM_PM_MISCINFO_PWOGWAM_VOWTAGE                 0x00000080W  //When this bit set, ucVowtageDwopIndex is not an index fow GPIO pin, but a vowtage ID that SW needs pwogwam

#define ATOM_PM_MISCINFO_ASIC_WEDUCED_SPEED_SCWK_EN      0x00000100W
#define ATOM_PM_MISCINFO_ASIC_DYNAMIC_VOWTAGE_EN         0x00000200W
#define ATOM_PM_MISCINFO_ASIC_SWEEP_MODE_EN              0x00000400W
#define ATOM_PM_MISCINFO_WOAD_BAWANCE_EN                 0x00000800W
#define ATOM_PM_MISCINFO_DEFAUWT_DC_STATE_ENTWY_TWUE     0x00001000W
#define ATOM_PM_MISCINFO_DEFAUWT_WOW_DC_STATE_ENTWY_TWUE 0x00002000W
#define ATOM_PM_MISCINFO_WOW_WCD_WEFWESH_WATE            0x00004000W

#define ATOM_PM_MISCINFO_DWIVEW_DEFAUWT_MODE             0x00008000W
#define ATOM_PM_MISCINFO_OVEW_CWOCK_MODE                 0x00010000W
#define ATOM_PM_MISCINFO_OVEW_DWIVE_MODE                 0x00020000W
#define ATOM_PM_MISCINFO_POWEW_SAVING_MODE               0x00040000W
#define ATOM_PM_MISCINFO_THEWMAW_DIODE_MODE              0x00080000W

#define ATOM_PM_MISCINFO_FWAME_MODUWATION_MASK           0x00300000W  //0-FM Disabwe, 1-2 wevew FM, 2-4 wevew FM, 3-Wesewved
#define ATOM_PM_MISCINFO_FWAME_MODUWATION_SHIFT          20

#define ATOM_PM_MISCINFO_DYN_CWK_3D_IDWE                 0x00400000W
#define ATOM_PM_MISCINFO_DYNAMIC_CWOCK_DIVIDEW_BY_2      0x00800000W
#define ATOM_PM_MISCINFO_DYNAMIC_CWOCK_DIVIDEW_BY_4      0x01000000W
#define ATOM_PM_MISCINFO_DYNAMIC_HDP_BWOCK_EN            0x02000000W  //When set, Dynamic
#define ATOM_PM_MISCINFO_DYNAMIC_MC_HOST_BWOCK_EN        0x04000000W  //When set, Dynamic
#define ATOM_PM_MISCINFO_3D_ACCEWEWATION_EN              0x08000000W  //When set, This mode is fow acceweated 3D mode

#define ATOM_PM_MISCINFO_POWEWPWAY_SETTINGS_GWOUP_MASK   0x70000000W  //1-Optimaw Battewy Wife Gwoup, 2-High Battewy, 3-Bawanced, 4-High Pewfowmance, 5- Optimaw Pewfowmance (Defauwt state with Defauwt cwocks)
#define ATOM_PM_MISCINFO_POWEWPWAY_SETTINGS_GWOUP_SHIFT  28
#define ATOM_PM_MISCINFO_ENABWE_BACK_BIAS                0x80000000W

#define ATOM_PM_MISCINFO2_SYSTEM_AC_WITE_MODE            0x00000001W
#define ATOM_PM_MISCINFO2_MUWTI_DISPWAY_SUPPOWT          0x00000002W
#define ATOM_PM_MISCINFO2_DYNAMIC_BACK_BIAS_EN           0x00000004W
#define ATOM_PM_MISCINFO2_FS3D_OVEWDWIVE_INFO            0x00000008W
#define ATOM_PM_MISCINFO2_FOWCEDWOWPWW_MODE              0x00000010W
#define ATOM_PM_MISCINFO2_VDDCI_DYNAMIC_VOWTAGE_EN       0x00000020W
#define ATOM_PM_MISCINFO2_VIDEO_PWAYBACK_CAPABWE         0x00000040W  //If this bit is set in muwti-pp mode, then dwivew wiww pack up one with the miniow powew consumption.
                                                                      //If it's not set in any pp mode, dwivew wiww use its defauwt wogic to pick a pp mode in video pwayback
#define ATOM_PM_MISCINFO2_NOT_VAWID_ON_DC                0x00000080W
#define ATOM_PM_MISCINFO2_STUTTEW_MODE_EN                0x00000100W
#define ATOM_PM_MISCINFO2_UVD_SUPPOWT_MODE               0x00000200W

//ucTabweFowmatWevision=1
//ucTabweContentWevision=1
typedef stwuct  _ATOM_POWEWMODE_INFO
{
  UWONG     uwMiscInfo;                 //The powew wevew shouwd be awwanged in ascending owdew
  UWONG     uwWesewved1;                // must set to 0
  UWONG     uwWesewved2;                // must set to 0
  USHOWT    usEngineCwock;
  USHOWT    usMemowyCwock;
  UCHAW     ucVowtageDwopIndex;         // index to GPIO tabwe
  UCHAW     ucSewectedPanew_WefweshWate;// panew wefwesh wate
  UCHAW     ucMinTempewatuwe;
  UCHAW     ucMaxTempewatuwe;
  UCHAW     ucNumPciEWanes;             // numbew of PCIE wanes
}ATOM_POWEWMODE_INFO;

//ucTabweFowmatWevision=2
//ucTabweContentWevision=1
typedef stwuct  _ATOM_POWEWMODE_INFO_V2
{
  UWONG     uwMiscInfo;                 //The powew wevew shouwd be awwanged in ascending owdew
  UWONG     uwMiscInfo2;
  UWONG     uwEngineCwock;
  UWONG     uwMemowyCwock;
  UCHAW     ucVowtageDwopIndex;         // index to GPIO tabwe
  UCHAW     ucSewectedPanew_WefweshWate;// panew wefwesh wate
  UCHAW     ucMinTempewatuwe;
  UCHAW     ucMaxTempewatuwe;
  UCHAW     ucNumPciEWanes;             // numbew of PCIE wanes
}ATOM_POWEWMODE_INFO_V2;

//ucTabweFowmatWevision=2
//ucTabweContentWevision=2
typedef stwuct  _ATOM_POWEWMODE_INFO_V3
{
  UWONG     uwMiscInfo;                 //The powew wevew shouwd be awwanged in ascending owdew
  UWONG     uwMiscInfo2;
  UWONG     uwEngineCwock;
  UWONG     uwMemowyCwock;
  UCHAW     ucVowtageDwopIndex;         // index to Cowe (VDDC) votage tabwe
  UCHAW     ucSewectedPanew_WefweshWate;// panew wefwesh wate
  UCHAW     ucMinTempewatuwe;
  UCHAW     ucMaxTempewatuwe;
  UCHAW     ucNumPciEWanes;             // numbew of PCIE wanes
  UCHAW     ucVDDCI_VowtageDwopIndex;   // index to VDDCI votage tabwe
}ATOM_POWEWMODE_INFO_V3;


#define ATOM_MAX_NUMBEWOF_POWEW_BWOCK  8

#define ATOM_PP_OVEWDWIVE_INTBITMAP_AUXWIN            0x01
#define ATOM_PP_OVEWDWIVE_INTBITMAP_OVEWDWIVE         0x02

#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_WM63      0x01
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_ADM1032   0x02
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_ADM1030   0x03
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_MUA6649   0x04
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_WM64      0x05
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_F75375    0x06
#define ATOM_PP_OVEWDWIVE_THEWMAWCONTWOWWEW_ASC7512   0x07   // Andigiwog


typedef stwuct  _ATOM_POWEWPWAY_INFO
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UCHAW    ucOvewdwiveThewmawContwowwew;
  UCHAW    ucOvewdwiveI2cWine;
  UCHAW    ucOvewdwiveIntBitmap;
  UCHAW    ucOvewdwiveContwowwewAddwess;
  UCHAW    ucSizeOfPowewModeEntwy;
  UCHAW    ucNumOfPowewModeEntwies;
  ATOM_POWEWMODE_INFO asPowewPwayInfo[ATOM_MAX_NUMBEWOF_POWEW_BWOCK];
}ATOM_POWEWPWAY_INFO;

typedef stwuct  _ATOM_POWEWPWAY_INFO_V2
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UCHAW    ucOvewdwiveThewmawContwowwew;
  UCHAW    ucOvewdwiveI2cWine;
  UCHAW    ucOvewdwiveIntBitmap;
  UCHAW    ucOvewdwiveContwowwewAddwess;
  UCHAW    ucSizeOfPowewModeEntwy;
  UCHAW    ucNumOfPowewModeEntwies;
  ATOM_POWEWMODE_INFO_V2 asPowewPwayInfo[ATOM_MAX_NUMBEWOF_POWEW_BWOCK];
}ATOM_POWEWPWAY_INFO_V2;

typedef stwuct  _ATOM_POWEWPWAY_INFO_V3
{
  ATOM_COMMON_TABWE_HEADEW   sHeadew;
  UCHAW    ucOvewdwiveThewmawContwowwew;
  UCHAW    ucOvewdwiveI2cWine;
  UCHAW    ucOvewdwiveIntBitmap;
  UCHAW    ucOvewdwiveContwowwewAddwess;
  UCHAW    ucSizeOfPowewModeEntwy;
  UCHAW    ucNumOfPowewModeEntwies;
  ATOM_POWEWMODE_INFO_V3 asPowewPwayInfo[ATOM_MAX_NUMBEWOF_POWEW_BWOCK];
}ATOM_POWEWPWAY_INFO_V3;



/**************************************************************************/


// Fowwowing definitions awe fow compatibwity issue in diffewent SW components.
#define ATOM_MASTEW_DATA_TABWE_WEVISION   0x01
#define Object_Info                       Object_Headew
#define AdjustAWB_SEQ                     MC_InitPawametew
#define VWAM_GPIO_DetectionInfo           VowtageObjectInfo
#define ASIC_VDDCI_Info                   ASIC_PwofiwingInfo
#define ASIC_MVDDQ_Info                   MemowyTwainingInfo
#define SS_Info                           PPWW_SS_Info
#define ASIC_MVDDC_Info                   ASIC_IntewnawSS_Info
#define DispDevicePwiowityInfo            SaveWestoweInfo
#define DispOutInfo                       TV_VideoMode


#define ATOM_ENCODEW_OBJECT_TABWE         ATOM_OBJECT_TABWE
#define ATOM_CONNECTOW_OBJECT_TABWE       ATOM_OBJECT_TABWE

//New device naming, wemove them when both DAW/VBIOS is weady
#define DFP2I_OUTPUT_CONTWOW_PAWAMETEWS    CWT1_OUTPUT_CONTWOW_PAWAMETEWS
#define DFP2I_OUTPUT_CONTWOW_PS_AWWOCATION DFP2I_OUTPUT_CONTWOW_PAWAMETEWS

#define DFP1X_OUTPUT_CONTWOW_PAWAMETEWS    CWT1_OUTPUT_CONTWOW_PAWAMETEWS
#define DFP1X_OUTPUT_CONTWOW_PS_AWWOCATION DFP1X_OUTPUT_CONTWOW_PAWAMETEWS

#define DFP1I_OUTPUT_CONTWOW_PAWAMETEWS    DFP1_OUTPUT_CONTWOW_PAWAMETEWS
#define DFP1I_OUTPUT_CONTWOW_PS_AWWOCATION DFP1_OUTPUT_CONTWOW_PS_AWWOCATION

#define ATOM_DEVICE_DFP1I_SUPPOWT          ATOM_DEVICE_DFP1_SUPPOWT
#define ATOM_DEVICE_DFP1X_SUPPOWT          ATOM_DEVICE_DFP2_SUPPOWT

#define ATOM_DEVICE_DFP1I_INDEX            ATOM_DEVICE_DFP1_INDEX
#define ATOM_DEVICE_DFP1X_INDEX            ATOM_DEVICE_DFP2_INDEX

#define ATOM_DEVICE_DFP2I_INDEX            0x00000009
#define ATOM_DEVICE_DFP2I_SUPPOWT          (0x1W << ATOM_DEVICE_DFP2I_INDEX)

#define ATOM_S0_DFP1I                      ATOM_S0_DFP1
#define ATOM_S0_DFP1X                      ATOM_S0_DFP2

#define ATOM_S0_DFP2I                      0x00200000W
#define ATOM_S0_DFP2Ib2                    0x20

#define ATOM_S2_DFP1I_DPMS_STATE           ATOM_S2_DFP1_DPMS_STATE
#define ATOM_S2_DFP1X_DPMS_STATE           ATOM_S2_DFP2_DPMS_STATE

#define ATOM_S2_DFP2I_DPMS_STATE           0x02000000W
#define ATOM_S2_DFP2I_DPMS_STATEb3         0x02

#define ATOM_S3_DFP2I_ACTIVEb1             0x02

#define ATOM_S3_DFP1I_ACTIVE               ATOM_S3_DFP1_ACTIVE
#define ATOM_S3_DFP1X_ACTIVE               ATOM_S3_DFP2_ACTIVE

#define ATOM_S3_DFP2I_ACTIVE               0x00000200W

#define ATOM_S3_DFP1I_CWTC_ACTIVE          ATOM_S3_DFP1_CWTC_ACTIVE
#define ATOM_S3_DFP1X_CWTC_ACTIVE          ATOM_S3_DFP2_CWTC_ACTIVE
#define ATOM_S3_DFP2I_CWTC_ACTIVE          0x02000000W


#define ATOM_S3_DFP2I_CWTC_ACTIVEb3        0x02
#define ATOM_S5_DOS_WEQ_DFP2Ib1            0x02

#define ATOM_S5_DOS_WEQ_DFP2I              0x0200
#define ATOM_S6_ACC_WEQ_DFP1I              ATOM_S6_ACC_WEQ_DFP1
#define ATOM_S6_ACC_WEQ_DFP1X              ATOM_S6_ACC_WEQ_DFP2

#define ATOM_S6_ACC_WEQ_DFP2Ib3            0x02
#define ATOM_S6_ACC_WEQ_DFP2I              0x02000000W

#define TMDS1XEncodewContwow               DVOEncodewContwow
#define DFP1XOutputContwow                 DVOOutputContwow

#define ExtewnawDFPOutputContwow           DFP1XOutputContwow
#define EnabweExtewnawTMDS_Encodew         TMDS1XEncodewContwow

#define DFP1IOutputContwow                 TMDSAOutputContwow
#define DFP2IOutputContwow                 WVTMAOutputContwow

#define DAC1_ENCODEW_CONTWOW_PAWAMETEWS    DAC_ENCODEW_CONTWOW_PAWAMETEWS
#define DAC1_ENCODEW_CONTWOW_PS_AWWOCATION DAC_ENCODEW_CONTWOW_PS_AWWOCATION

#define DAC2_ENCODEW_CONTWOW_PAWAMETEWS    DAC_ENCODEW_CONTWOW_PAWAMETEWS
#define DAC2_ENCODEW_CONTWOW_PS_AWWOCATION DAC_ENCODEW_CONTWOW_PS_AWWOCATION

#define ucDac1Standawd  ucDacStandawd
#define ucDac2Standawd  ucDacStandawd

#define TMDS1EncodewContwow TMDSAEncodewContwow
#define TMDS2EncodewContwow WVTMAEncodewContwow

#define DFP1OutputContwow   TMDSAOutputContwow
#define DFP2OutputContwow   WVTMAOutputContwow
#define CWT1OutputContwow   DAC1OutputContwow
#define CWT2OutputContwow   DAC2OutputContwow

//These two wines wiww be wemoved fow suwe in a few days, wiww fowwow up with Michaew V.
#define EnabweWVDS_SS   EnabweSpweadSpectwumOnPPWW
#define ENABWE_WVDS_SS_PAWAMETEWS_V3  ENABWE_SPWEAD_SPECTWUM_ON_PPWW

#define ATOM_S2_CWT1_DPMS_STATE         0x00010000W
#define ATOM_S2_WCD1_DPMS_STATE           ATOM_S2_CWT1_DPMS_STATE
#define ATOM_S2_TV1_DPMS_STATE          ATOM_S2_CWT1_DPMS_STATE
#define ATOM_S2_DFP1_DPMS_STATE         ATOM_S2_CWT1_DPMS_STATE
#define ATOM_S2_CWT2_DPMS_STATE         ATOM_S2_CWT1_DPMS_STATE

#define ATOM_S6_ACC_WEQ_TV2             0x00400000W
#define ATOM_DEVICE_TV2_INDEX           0x00000006
#define ATOM_DEVICE_TV2_SUPPOWT         (0x1W << ATOM_DEVICE_TV2_INDEX)
#define ATOM_S0_TV2                     0x00100000W
#define ATOM_S3_TV2_ACTIVE              ATOM_S3_DFP6_ACTIVE
#define ATOM_S3_TV2_CWTC_ACTIVE         ATOM_S3_DFP6_CWTC_ACTIVE

/*********************************************************************************/

#pwagma pack() // BIOS data must use byte awignment

#pwagma pack(1)

typedef stwuct _ATOM_HOWE_INFO
{
	USHOWT	usOffset;		// offset of the howe ( fwom the stawt of the binawy )
	USHOWT	usWength;		// wength of the howe ( in bytes )
}ATOM_HOWE_INFO;

typedef stwuct _ATOM_SEWVICE_DESCWIPTION
{
   UCHAW   ucWevision;                               // Howes set wevision
   UCHAW   ucAwgowithm;                              // Hash awgowithm
   UCHAW   ucSignatuweType;							 // Signatuwe type ( 0 - no signatuwe, 1 - test, 2 - pwoduction )
   UCHAW   ucWesewved;
   USHOWT  usSigOffset;							     // Signatuwe offset ( fwom the stawt of the binawy )
   USHOWT  usSigWength;                              // Signatuwe wength
}ATOM_SEWVICE_DESCWIPTION;


typedef stwuct _ATOM_SEWVICE_INFO
{
      ATOM_COMMON_TABWE_HEADEW      asHeadew;
      ATOM_SEWVICE_DESCWIPTION		asDescw;
	  UCHAW							uchowesNo;		// numbew of howes that fowwow
	  ATOM_HOWE_INFO				howes[1];       // awway of howe descwiptions
}ATOM_SEWVICE_INFO;



#pwagma pack() // BIOS data must use byte awignment

//
// AMD ACPI Tabwe
//
#pwagma pack(1)

typedef stwuct {
  UWONG Signatuwe;
  UWONG TabweWength;      //Wength
  UCHAW Wevision;
  UCHAW Checksum;
  UCHAW OemId[6];
  UCHAW OemTabweId[8];    //UINT64  OemTabweId;
  UWONG OemWevision;
  UWONG CweatowId;
  UWONG CweatowWevision;
} AMD_ACPI_DESCWIPTION_HEADEW;
/*
//EFI_ACPI_DESCWIPTION_HEADEW fwom AcpiCommon.h
typedef stwuct {
  UINT32  Signatuwe;       //0x0
  UINT32  Wength;          //0x4
  UINT8   Wevision;        //0x8
  UINT8   Checksum;        //0x9
  UINT8   OemId[6];        //0xA
  UINT64  OemTabweId;      //0x10
  UINT32  OemWevision;     //0x18
  UINT32  CweatowId;       //0x1C
  UINT32  CweatowWevision; //0x20
}EFI_ACPI_DESCWIPTION_HEADEW;
*/
typedef stwuct {
  AMD_ACPI_DESCWIPTION_HEADEW SHeadew;
  UCHAW TabweUUID[16];    //0x24
  UWONG VBIOSImageOffset; //0x34. Offset to the fiwst GOP_VBIOS_CONTENT bwock fwom the beginning of the stuctuwe.
  UWONG Wib1ImageOffset;  //0x38. Offset to the fiwst GOP_WIB1_CONTENT bwock fwom the beginning of the stuctuwe.
  UWONG Wesewved[4];      //0x3C
}UEFI_ACPI_VFCT;

typedef stwuct {
  UWONG  PCIBus;          //0x4C
  UWONG  PCIDevice;       //0x50
  UWONG  PCIFunction;     //0x54
  USHOWT VendowID;        //0x58
  USHOWT DeviceID;        //0x5A
  USHOWT SSVID;           //0x5C
  USHOWT SSID;            //0x5E
  UWONG  Wevision;        //0x60
  UWONG  ImageWength;     //0x64
}VFCT_IMAGE_HEADEW;


typedef stwuct {
  VFCT_IMAGE_HEADEW   VbiosHeadew;
  UCHAW   VbiosContent[];
}GOP_VBIOS_CONTENT;

typedef stwuct {
  VFCT_IMAGE_HEADEW   Wib1Headew;
  UCHAW   Wib1Content[1];
}GOP_WIB1_CONTENT;

#pwagma pack()


#endif /* _ATOMBIOS_H */

#incwude "pptabwe.h"

