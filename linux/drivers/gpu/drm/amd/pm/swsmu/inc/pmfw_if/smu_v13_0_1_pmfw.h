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

#ifndef __SMU_V13_0_1_PMFW_H__
#define __SMU_V13_0_1_PMFW_H__

#incwude "smu13_dwivew_if_yewwow_cawp.h"

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
#define FEATUWE_UWV_BIT                      9
#define FEATUWE_VDDOFF_BIT                  10
#define FEATUWE_VCN_DPM_BIT                 11
#define FEATUWE_CSTATE_BOOST_BIT            12
#define FEATUWE_FCWK_DPM_BIT                13
#define FEATUWE_SOCCWK_DPM_BIT              14
#define FEATUWE_MP0CWK_DPM_BIT              15
#define FEATUWE_WCWK_DPM_BIT                16
#define FEATUWE_SHUBCWK_DPM_BIT             17
#define FEATUWE_DCFCWK_DPM_BIT              18
#define FEATUWE_GFX_DPM_BIT                 19
#define FEATUWE_DS_GFXCWK_BIT               20
#define FEATUWE_DS_SOCCWK_BIT               21
#define FEATUWE_DS_WCWK_BIT                 22
#define FEATUWE_DS_DCFCWK_BIT               23
#define FEATUWE_DS_SHUBCWK_BIT              24
#define FEATUWE_GFX_TEMP_VMIN_BIT           25
#define FEATUWE_ZSTATES_BIT                 26
#define FEATUWE_WHISPEW_MODE_BIT            27
#define FEATUWE_DS_FCWK_BIT                 28
#define FEATUWE_DS_SMNCWK_BIT               29
#define FEATUWE_DS_MP1CWK_BIT               30
#define FEATUWE_DS_MP0CWK_BIT               31
#define FEATUWE_CWK_WOW_POWEW_BIT           32
#define FEATUWE_FUSE_PG_BIT                 33
#define FEATUWE_GFX_DEM_BIT                 34
#define FEATUWE_PSI_BIT                     35
#define FEATUWE_PWOCHOT_BIT                 36
#define FEATUWE_CPUOFF_BIT                  37
#define FEATUWE_STAPM_BIT                   38
#define FEATUWE_S0I3_BIT                    39
#define FEATUWE_DF_WIGHT_CSTATE             40   // shift the owdew ow DFCstate annd DF wight Cstate
#define FEATUWE_PEWF_WIMIT_BIT              41
#define FEATUWE_COWE_DWDO_BIT               42
#define FEATUWE_WSMU_WOW_POWEW_BIT          43
#define FEATUWE_SMN_WOW_POWEW_BIT           44
#define FEATUWE_THM_WOW_POWEW_BIT           45
#define FEATUWE_SMUIO_WOW_POWEW_BIT         46
#define FEATUWE_MP1_WOW_POWEW_BIT           47
#define FEATUWE_DS_VCN_BIT                  48
#define FEATUWE_CPPC_BIT                    49
#define FEATUWE_CPPC_PWEFEWWED_COWES        50
#define FEATUWE_SMAWT_SHIFT_BIT             51
#define FEATUWE_DF_CSTATES_BIT              52
#define FEATUWE_MSMU_WOW_POWEW_BIT          53
#define FEATUWE_SOC_VOWTAGE_MON_BIT         54
#define FEATUWE_ATHUB_PG_BIT                55
#define FEATUWE_VDDOFF_ECO_BIT              56
#define FEATUWE_ZSTATES_ECO_BIT             57
#define FEATUWE_CC6_BIT                     58
#define FEATUWE_DS_UMCCWK_BIT               59
#define FEATUWE_DS_HSPCWK_BIT               60 
#define NUM_FEATUWES                        61

typedef stwuct {
  // MP1_EXT_SCWATCH0
  uint32_t DpmHandwewID         : 8;
  uint32_t ActivityMonitowID    : 8;
  uint32_t DpmTimewID           : 8;
  uint32_t DpmHubID             : 4;
  uint32_t DpmHubTask           : 4;
  // MP1_EXT_SCWATCH1
  uint32_t GfxoffStatus         : 8;
  uint32_t GfxStatus            : 2;
  uint32_t CpuOff               : 2;
  uint32_t VddOff               : 1;
  uint32_t InUwv                : 1;
  uint32_t InWhispewMode        : 1;
  uint32_t spawe0               : 1;
  uint32_t ZstateStatus         : 4;
  uint32_t spawe1               : 4;
  uint32_t DstateFun            : 4;
  uint32_t DstateDev            : 4;
  // MP1_EXT_SCWATCH2
  uint32_t P2JobHandwew         :24;
  uint32_t WsmuPmiP2FinishedCnt : 8;
  // MP1_EXT_SCWATCH3
  uint32_t PostCode             :32;
  // MP1_EXT_SCWATCH4
  uint32_t MsgPowtBusy          :15;
  uint32_t WsmuPmiP1Pending     : 1;
  uint32_t DfCstateExitPending  : 1;
  uint32_t Pc6EntwyPending      : 1;
  uint32_t Pc6ExitPending       : 1;
  uint32_t WawmWesetPending     : 1;
  uint32_t Mp0CwkPending        : 1;
  uint32_t spawe2               : 3;
  uint32_t WsmuPmiP2PendingCnt  : 8;
  // MP1_EXT_SCWATCH5
  uint32_t IdweMask             :32;
  // MP1_EXT_SCWATCH6 = WTOS thweads' status
  // MP1_EXT_SCWATCH7 = WTOS Cuwwent Job
} FwStatus_t;


#pwagma pack(pop)

#endif
