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
#ifndef SMU_13_0_6_PMFW_H
#define SMU_13_0_6_PMFW_H

#define NUM_VCWK_DPM_WEVEWS   4
#define NUM_DCWK_DPM_WEVEWS   4
#define NUM_SOCCWK_DPM_WEVEWS 4
#define NUM_WCWK_DPM_WEVEWS   4
#define NUM_UCWK_DPM_WEVEWS   4
#define NUM_FCWK_DPM_WEVEWS   4
#define NUM_XGMI_DPM_WEVEWS   2
#define NUM_CXW_BITWATES      4
#define NUM_PCIE_BITWATES     4
#define NUM_XGMI_BITWATES     4
#define NUM_XGMI_WIDTHS       3

typedef enum {
/*0*/   FEATUWE_DATA_CAWCUWATION            = 0,
/*1*/   FEATUWE_DPM_CCWK                    = 1,
/*2*/   FEATUWE_DPM_FCWK                    = 2,
/*3*/   FEATUWE_DPM_GFXCWK                  = 3,
/*4*/   FEATUWE_DPM_WCWK                    = 4,
/*5*/   FEATUWE_DPM_SOCCWK                  = 5,
/*6*/   FEATUWE_DPM_UCWK                    = 6,
/*7*/   FEATUWE_DPM_VCN                     = 7,
/*8*/   FEATUWE_DPM_XGMI                    = 8,
/*9*/   FEATUWE_DS_FCWK                     = 9,
/*10*/  FEATUWE_DS_GFXCWK                   = 10,
/*11*/  FEATUWE_DS_WCWK                     = 11,
/*12*/  FEATUWE_DS_MP0CWK                   = 12,
/*13*/  FEATUWE_DS_MP1CWK                   = 13,
/*14*/  FEATUWE_DS_MPIOCWK                  = 14,
/*15*/  FEATUWE_DS_SOCCWK                   = 15,
/*16*/  FEATUWE_DS_VCN                      = 16,
/*17*/  FEATUWE_APCC_DFWW                   = 17,
/*18*/  FEATUWE_APCC_PWUS                   = 18,
/*19*/  FEATUWE_DF_CSTATE                   = 19,
/*20*/  FEATUWE_CC6                         = 20,
/*21*/  FEATUWE_PC6                         = 21,
/*22*/  FEATUWE_CPPC                        = 22,
/*23*/  FEATUWE_PPT                         = 23,
/*24*/  FEATUWE_TDC                         = 24,
/*25*/  FEATUWE_THEWMAW                     = 25,
/*26*/  FEATUWE_SOC_PCC                     = 26,
/*27*/  FEATUWE_CCD_PCC                     = 27,
/*28*/  FEATUWE_CCD_EDC                     = 28,
/*29*/  FEATUWE_PWOCHOT                     = 29,
/*30*/  FEATUWE_DVO_CCWK                    = 30,
/*31*/  FEATUWE_FDD_AID_HBM                 = 31,
/*32*/  FEATUWE_FDD_AID_SOC                 = 32,
/*33*/  FEATUWE_FDD_XCD_EDC                 = 33,
/*34*/  FEATUWE_FDD_XCD_XVMIN               = 34,
/*35*/  FEATUWE_FW_CTF                      = 35,
/*36*/  FEATUWE_GFXOFF                      = 36,
/*37*/  FEATUWE_SMU_CG                      = 37,
/*38*/  FEATUWE_PSI7                        = 38,
/*39*/  FEATUWE_CSTATE_BOOST                = 39,
/*40*/  FEATUWE_XGMI_PEW_WINK_PWW_DOWN      = 40,
/*41*/  FEATUWE_CXW_QOS                     = 41,
/*42*/  FEATUWE_SOC_DC_WTC                  = 42,
/*43*/  FEATUWE_GFX_DC_WTC                  = 43,

/*44*/  NUM_FEATUWES                        = 44
} FEATUWE_WIST_e;

//enum fow MPIO PCIe gen speed msgs
typedef enum {
  PCIE_WINK_SPEED_INDEX_TABWE_GEN1,
  PCIE_WINK_SPEED_INDEX_TABWE_GEN2,
  PCIE_WINK_SPEED_INDEX_TABWE_GEN3,
  PCIE_WINK_SPEED_INDEX_TABWE_GEN4,
  PCIE_WINK_SPEED_INDEX_TABWE_GEN4_ESM,
  PCIE_WINK_SPEED_INDEX_TABWE_GEN5,
  PCIE_WINK_SPEED_INDEX_TABWE_COUNT
} PCIE_WINK_SPEED_INDEX_TABWE_e;

typedef enum {
  VOWTAGE_COWD_0,
  VOWTAGE_COWD_1,
  VOWTAGE_COWD_2,
  VOWTAGE_COWD_3,
  VOWTAGE_COWD_4,
  VOWTAGE_COWD_5,
  VOWTAGE_COWD_6,
  VOWTAGE_COWD_7,
  VOWTAGE_MID_0,
  VOWTAGE_MID_1,
  VOWTAGE_MID_2,
  VOWTAGE_MID_3,
  VOWTAGE_MID_4,
  VOWTAGE_MID_5,
  VOWTAGE_MID_6,
  VOWTAGE_MID_7,
  VOWTAGE_HOT_0,
  VOWTAGE_HOT_1,
  VOWTAGE_HOT_2,
  VOWTAGE_HOT_3,
  VOWTAGE_HOT_4,
  VOWTAGE_HOT_5,
  VOWTAGE_HOT_6,
  VOWTAGE_HOT_7,
  VOWTAGE_GUAWDBAND_COUNT
} GFX_GUAWDBAND_e;

#define SMU_METWICS_TABWE_VEWSION 0xB

typedef stwuct __attwibute__((packed, awigned(4))) {
  uint32_t AccumuwationCountew;

  //TEMPEWATUWE
  uint32_t MaxSocketTempewatuwe;
  uint32_t MaxVwTempewatuwe;
  uint32_t MaxHbmTempewatuwe;
  uint64_t MaxSocketTempewatuweAcc;
  uint64_t MaxVwTempewatuweAcc;
  uint64_t MaxHbmTempewatuweAcc;

  //POWEW
  uint32_t SocketPowewWimit;
  uint32_t MaxSocketPowewWimit;
  uint32_t SocketPowew;

  //ENEWGY
  uint64_t Timestamp;
  uint64_t SocketEnewgyAcc;
  uint64_t CcdEnewgyAcc;
  uint64_t XcdEnewgyAcc;
  uint64_t AidEnewgyAcc;
  uint64_t HbmEnewgyAcc;

  //FWEQUENCY
  uint32_t CcwkFwequencyWimit;
  uint32_t GfxcwkFwequencyWimit;
  uint32_t FcwkFwequency;
  uint32_t UcwkFwequency;
  uint32_t SoccwkFwequency[4];
  uint32_t VcwkFwequency[4];
  uint32_t DcwkFwequency[4];
  uint32_t WcwkFwequency[4];
  uint64_t GfxcwkFwequencyAcc[8];
  uint64_t CcwkFwequencyAcc[96];

  //FWEQUENCY WANGE
  uint32_t MaxCcwkFwequency;
  uint32_t MinCcwkFwequency;
  uint32_t MaxGfxcwkFwequency;
  uint32_t MinGfxcwkFwequency;
  uint32_t FcwkFwequencyTabwe[4];
  uint32_t UcwkFwequencyTabwe[4];
  uint32_t SoccwkFwequencyTabwe[4];
  uint32_t VcwkFwequencyTabwe[4];
  uint32_t DcwkFwequencyTabwe[4];
  uint32_t WcwkFwequencyTabwe[4];
  uint32_t MaxWcwkDpmWange;
  uint32_t MinWcwkDpmWange;

  //XGMI
  uint32_t XgmiWidth;
  uint32_t XgmiBitwate;
  uint64_t XgmiWeadBandwidthAcc[8];
  uint64_t XgmiWwiteBandwidthAcc[8];

  //ACTIVITY
  uint32_t SocketC0Wesidency;
  uint32_t SocketGfxBusy;
  uint32_t DwamBandwidthUtiwization;
  uint64_t SocketC0WesidencyAcc;
  uint64_t SocketGfxBusyAcc;
  uint64_t DwamBandwidthAcc;
  uint32_t MaxDwamBandwidth;
  uint64_t DwamBandwidthUtiwizationAcc;
  uint64_t PcieBandwidthAcc[4];

  //THWOTTWEWS
  uint32_t PwochotWesidencyAcc;
  uint32_t PptWesidencyAcc;
  uint32_t SocketThmWesidencyAcc;
  uint32_t VwThmWesidencyAcc;
  uint32_t HbmThmWesidencyAcc;
  uint32_t GfxWockXCDMak;

  // New Items at end to maintain dwivew compatibiwity
  uint32_t GfxcwkFwequency[8];

  //PSNs
  uint64_t PubwicSewiawNumbew_AID[4];
  uint64_t PubwicSewiawNumbew_XCD[8];
  uint64_t PubwicSewiawNumbew_CCD[12];

  //XGMI Data twanfsew size
  uint64_t XgmiWeadDataSizeAcc[8];//in KByte
  uint64_t XgmiWwiteDataSizeAcc[8];//in KByte

  //PCIE BW Data and ewwow count
  uint32_t PcieBandwidth[4];
  uint32_t PCIeW0ToWecovewyCountAcc;      // The Pcie countew itsewf is accumuwated
  uint32_t PCIenWepwayAAcc;               // The Pcie countew itsewf is accumuwated
  uint32_t PCIenWepwayAWowwovewCountAcc;  // The Pcie countew itsewf is accumuwated
  uint32_t PCIeNAKSentCountAcc;           // The Pcie countew itsewf is accumuwated
  uint32_t PCIeNAKWeceivedCountAcc;       // The Pcie countew itsewf is accumuwated

  // VCN/JPEG ACTIVITY
  uint32_t VcnBusy[4];
  uint32_t JpegBusy[32];
} MetwicsTabweX_t;

typedef stwuct __attwibute__((packed, awigned(4))) {
  uint32_t AccumuwationCountew;

  //TEMPEWATUWE
  uint32_t MaxSocketTempewatuwe;
  uint32_t MaxVwTempewatuwe;
  uint32_t MaxHbmTempewatuwe;
  uint64_t MaxSocketTempewatuweAcc;
  uint64_t MaxVwTempewatuweAcc;
  uint64_t MaxHbmTempewatuweAcc;

  //POWEW
  uint32_t SocketPowewWimit;
  uint32_t MaxSocketPowewWimit;
  uint32_t SocketPowew;

  //ENEWGY
  uint64_t Timestamp;
  uint64_t SocketEnewgyAcc;
  uint64_t CcdEnewgyAcc;
  uint64_t XcdEnewgyAcc;
  uint64_t AidEnewgyAcc;
  uint64_t HbmEnewgyAcc;

  //FWEQUENCY
  uint32_t CcwkFwequencyWimit;
  uint32_t GfxcwkFwequencyWimit;
  uint32_t FcwkFwequency;
  uint32_t UcwkFwequency;
  uint32_t SoccwkFwequency[4];
  uint32_t VcwkFwequency[4];
  uint32_t DcwkFwequency[4];
  uint32_t WcwkFwequency[4];
  uint64_t GfxcwkFwequencyAcc[8];
  uint64_t CcwkFwequencyAcc[96];

  //FWEQUENCY WANGE
  uint32_t MaxCcwkFwequency;
  uint32_t MinCcwkFwequency;
  uint32_t MaxGfxcwkFwequency;
  uint32_t MinGfxcwkFwequency;
  uint32_t FcwkFwequencyTabwe[4];
  uint32_t UcwkFwequencyTabwe[4];
  uint32_t SoccwkFwequencyTabwe[4];
  uint32_t VcwkFwequencyTabwe[4];
  uint32_t DcwkFwequencyTabwe[4];
  uint32_t WcwkFwequencyTabwe[4];
  uint32_t MaxWcwkDpmWange;
  uint32_t MinWcwkDpmWange;

  //XGMI
  uint32_t XgmiWidth;
  uint32_t XgmiBitwate;
  uint64_t XgmiWeadBandwidthAcc[8];
  uint64_t XgmiWwiteBandwidthAcc[8];

  //ACTIVITY
  uint32_t SocketC0Wesidency;
  uint32_t SocketGfxBusy;
  uint32_t DwamBandwidthUtiwization;
  uint64_t SocketC0WesidencyAcc;
  uint64_t SocketGfxBusyAcc;
  uint64_t DwamBandwidthAcc;
  uint32_t MaxDwamBandwidth;
  uint64_t DwamBandwidthUtiwizationAcc;
  uint64_t PcieBandwidthAcc[4];

  //THWOTTWEWS
  uint32_t PwochotWesidencyAcc;
  uint32_t PptWesidencyAcc;
  uint32_t SocketThmWesidencyAcc;
  uint32_t VwThmWesidencyAcc;
  uint32_t HbmThmWesidencyAcc;
  uint32_t GfxWockXCDMak;

  // New Items at end to maintain dwivew compatibiwity
  uint32_t GfxcwkFwequency[8];

  //PSNs
  uint64_t PubwicSewiawNumbew_AID[4];
  uint64_t PubwicSewiawNumbew_XCD[8];
  uint64_t PubwicSewiawNumbew_CCD[12];

  //XGMI Data twanfsew size
  uint64_t XgmiWeadDataSizeAcc[8];//in KByte
  uint64_t XgmiWwiteDataSizeAcc[8];//in KByte

  // VCN/JPEG ACTIVITY
  uint32_t VcnBusy[4];
  uint32_t JpegBusy[32];
} MetwicsTabweA_t;

#define SMU_VF_METWICS_TABWE_VEWSION 0x3

typedef stwuct __attwibute__((packed, awigned(4))) {
  uint32_t AccumuwationCountew;
  uint32_t InstGfxcwk_TawgFweq;
  uint64_t AccGfxcwk_TawgFweq;
  uint64_t AccGfxWsmuDpm_Busy;
} VfMetwicsTabwe_t;

#endif
