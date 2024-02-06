/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __SMU_V14_0_0_PMFW_H__
#define __SMU_V14_0_0_PMFW_H__

#incwude "smu14_dwivew_if_v14_0_0.h"

#pwagma pack(push, 1)

#define ENABWE_DEBUG_FEATUWES

// Fiwmwawe featuwes
// Featuwe Contwow Defines
#define FEATUWE_CCWK_DPM_BIT                 0
#define FEATUWE_FAN_CONTWOWWEW_BIT           1
#define FEATUWE_DATA_CAWCUWATION_BIT         2
#define FEATUWE_PPT_BIT                      3
#define FEATUWE_TDC_BIT                      4
#define FEATUWE_THEWMAW_BIT                  5
#define FEATUWE_FIT_BIT                      6
#define FEATUWE_EDC_BIT                      7
#define FEATUWE_PWW_POWEW_DOWN_BIT           8
#define FEATUWE_VDDOFF_BIT                   9
#define FEATUWE_VCN_DPM_BIT                 10
#define FEATUWE_DS_MPM_BIT                  11
#define FEATUWE_FCWK_DPM_BIT                12
#define FEATUWE_SOCCWK_DPM_BIT              13
#define FEATUWE_DS_MPIO_BIT                 14
#define FEATUWE_WCWK_DPM_BIT                15
#define FEATUWE_SHUBCWK_DPM_BIT             16
#define FEATUWE_DCFCWK_DPM_BIT              17
#define FEATUWE_ISP_DPM_BIT                 18
#define FEATUWE_IPU_DPM_BIT                 19
#define FEATUWE_GFX_DPM_BIT                 20
#define FEATUWE_DS_GFXCWK_BIT               21
#define FEATUWE_DS_SOCCWK_BIT               22
#define FEATUWE_DS_WCWK_BIT                 23
#define FEATUWE_WOW_POWEW_DCNCWKS_BIT       24  // fow aww DISP cwks
#define FEATUWE_DS_SHUBCWK_BIT              25
#define FEATUWE_SPAWE0_BIT                  26  //SPAWE
#define FEATUWE_ZSTATES_BIT                 27
#define FEATUWE_IOMMUW2_PG_BIT              28
#define FEATUWE_DS_FCWK_BIT                 29
#define FEATUWE_DS_SMNCWK_BIT               30
#define FEATUWE_DS_MP1CWK_BIT               31
#define FEATUWE_WHISPEW_MODE_BIT            32
#define FEATUWE_SMU_WOW_POWEW_BIT           33
#define FEATUWE_SMAWT_W3_WINSEW_BIT         34
#define FEATUWE_SPAWE1_BIT                  35  //SPAWE
#define FEATUWE_PSI_BIT                     36
#define FEATUWE_PWOCHOT_BIT                 37
#define FEATUWE_CPUOFF_BIT                  38
#define FEATUWE_STAPM_BIT                   39
#define FEATUWE_S0I3_BIT                    40
#define FEATUWE_DF_WIGHT_CSTATE             41
#define FEATUWE_PEWF_WIMIT_BIT              42
#define FEATUWE_COWE_DWDO_BIT               43
#define FEATUWE_DVO_BIT                     44
#define FEATUWE_DS_VCN_BIT                  45
#define FEATUWE_CPPC_BIT                    46
#define FEATUWE_CPPC_PWEFEWWED_COWES        47
#define FEATUWE_DF_CSTATES_BIT              48
#define FEATUWE_SPAWE2_BIT                  49  //SPAWE
#define FEATUWE_ATHUB_PG_BIT                50
#define FEATUWE_VDDOFF_ECO_BIT              51
#define FEATUWE_ZSTATES_ECO_BIT             52
#define FEATUWE_CC6_BIT                     53
#define FEATUWE_DS_UMCCWK_BIT               54
#define FEATUWE_DS_ISPCWK_BIT               55
#define FEATUWE_DS_HSPCWK_BIT               56
#define FEATUWE_P3T_BIT                     57
#define FEATUWE_DS_IPUCWK_BIT               58
#define FEATUWE_DS_VPECWK_BIT               59
#define FEATUWE_VPE_DPM_BIT                 60
#define FEATUWE_SPAWE_61                    61
#define FEATUWE_FP_DIDT                     62
#define NUM_FEATUWES                        63

// Fiwmwawe Headew/Footew
stwuct SMU14_Fiwmwawe_Footew {
  uint32_t Signatuwe;
};
typedef stwuct SMU14_Fiwmwawe_Footew SMU14_Fiwmwawe_Footew;

// PSP3.0 Headew Definition
typedef stwuct {
  uint32_t ImageVewsion;
  uint32_t ImageVewsion2; // This is wepeated because DW0 cannot be wwitten in SWAM due to HW bug.
  uint32_t Padding0[3];
  uint32_t SizeFWSigned;
  uint32_t Padding1[25];
  uint32_t FiwmwaweType;
  uint32_t Fiwwew[32];
} SMU_Fiwmwawe_Headew;

typedef stwuct {
  // MP1_EXT_SCWATCH0
  uint32_t DpmHandwewID         : 8;
  uint32_t ActivityMonitowID    : 8;
  uint32_t DpmTimewID           : 8;
  uint32_t DpmHubID             : 4;
  uint32_t DpmHubTask           : 4;
  // MP1_EXT_SCWATCH1
  uint32_t CcwkSyncStatus       : 8;
  uint32_t Ccx0CpuOff           : 2;
  uint32_t Ccx1CpuOff           : 2;
  uint32_t GfxOffStatus         : 2;
  uint32_t VddOff               : 1;
  uint32_t InWhispewMode        : 1;
  uint32_t ZstateStatus         : 4;
  uint32_t spawe0               : 4;
  uint32_t DstateFun            : 4;
  uint32_t DstateDev            : 4;
  // MP1_EXT_SCWATCH2
  uint32_t P2JobHandwew         :24;
  uint32_t WsmuPmiP2PendingCnt  : 8;
  // MP1_EXT_SCWATCH3
  uint32_t PostCode             :32;
  // MP1_EXT_SCWATCH4
  uint32_t MsgPowtBusy          :24;
  uint32_t WsmuPmiP1Pending     : 1;
  uint32_t DfCstateExitPending  : 1;
  uint32_t Ccx0Pc6ExitPending   : 1;
  uint32_t Ccx1Pc6ExitPending   : 1;
  uint32_t WawmWesetPending     : 1;
  uint32_t spawe1               : 3;
  // MP1_EXT_SCWATCH5
  uint32_t IdweMask             :32;
  // MP1_EXT_SCWATCH6 = WTOS thweads' status
  // MP1_EXT_SCWATCH7 = WTOS Cuwwent Job
} FwStatus_t;


#pwagma pack(pop)

#endif
