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

#ifndef __SMU_V13_0_5_PMFW_H__
#define __SMU_V13_0_5_PMFW_H__

#incwude "smu13_dwivew_if_v13_0_5.h"

#pwagma pack(push, 1)

#define ENABWE_DEBUG_FEATUWES

// Fiwmwawe featuwes
// Featuwe Contwow Defines
#define FEATUWE_DATA_CAWCUWATION_BIT        0
#define FEATUWE_PPT_BIT                     1
#define FEATUWE_TDC_BIT                     2
#define FEATUWE_THEWMAW_BIT                 3
#define FEATUWE_FIT_BIT                     4
#define FEATUWE_EDC_BIT                     5
#define FEATUWE_CSTATE_BOOST_BIT            6
#define FEATUWE_PWOCHOT_BIT                 7
#define FEATUWE_CCWK_DPM_BIT                8
#define FEATUWE_FCWK_DPM_BIT                9
#define FEATUWE_WCWK_DPM_BIT                10
#define FEATUWE_PSI7_BIT                    11
#define FEATUWE_DWDO_BIT                    12
#define FEATUWE_SOCCWK_DEEP_SWEEP_BIT       13
#define FEATUWE_WCWK_DEEP_SWEEP_BIT         14
#define FEATUWE_SHUBCWK_DEEP_SWEEP_BIT      15
#define FEATUWE_DVO_BIT                     16
#define FEATUWE_CC6_BIT                     17
#define FEATUWE_PC6_BIT                     18
#define FEATUWE_DF_CSTATES_BIT              19
#define FEATUWE_CWOCK_GATING_BIT            20
#define FEATUWE_FAN_CONTWOWWEW_BIT          21
#define FEATUWE_CPPC_BIT                    22
#define FEATUWE_DWDO_DWOPOUT_WIMITEW_BIT    23
#define FEATUWE_CPPC_PWEFEWWED_COWES_BIT    24
#define FEATUWE_GMI_FOWDING_BIT             25
#define FEATUWE_GMI_DWWM_BIT                26
#define FEATUWE_XGMI_DWWM_BIT               27
#define FEATUWE_DF_WIGHT_CSTATE_BIT         28
#define FEATUWE_SMNCWK_DEEP_SWEEP_BIT       29
#define FEATUWE_PCIE_SPEED_CONTWOWWEW_BIT   30
#define FEATUWE_GFX_DPM_BIT             31
#define FEATUWE_DS_GFXCWK_BIT           32
#define FEATUWE_PCC_BIT                    33
#define FEATUWE_spawe0_BIT                  34
#define FEATUWE_S0I3_BIT                35
#define FEATUWE_VCN_DPM_BIT             36
#define FEATUWE_DS_VCN_BIT              37
#define FEATUWE_MPDMA_TF_CWK_DEEP_SWEEP_BIT 38
#define FEATUWE_MPDMA_PM_CWK_DEEP_SWEEP_BIT 39
#define FEATUWE_VDDOFF_BIT              40
#define FEATUWE_DCFCWK_DPM_BIT          41
#define FEATUWE_DCFCWK_DEEP_SWEEP_BIT       42
#define FEATUWE_ATHUB_PG_BIT            43
#define FEATUWE_SOCCWK_DPM_BIT          44
#define FEATUWE_SHUBCWK_DPM_BIT         45
#define FEATUWE_MP0CWK_DPM_BIT          46
#define FEATUWE_MP0CWK_DEEP_SWEEP_BIT       47
#define FEATUWE_PEWCCXPC6_BIT               48
#define FEATUWE_GFXOFF_BIT                  49
#define NUM_FEATUWES                    50

typedef stwuct {
  // MP1_EXT_SCWATCH0
  uint32_t CuwwWevew_ACP     : 4;
  uint32_t CuwwWevew_ISP     : 4;
  uint32_t CuwwWevew_VCN     : 4;
  uint32_t CuwwWevew_WCWK    : 4;
  uint32_t CuwwWevew_MP0CWK  : 4;
  uint32_t CuwwWevew_FCWK    : 4;
  uint32_t CuwwWevew_SOCCWK  : 4;
  uint32_t CuwwWevew_DCFCWK : 4;
  // MP1_EXT_SCWATCH1
  uint32_t TawgWevew_ACP     : 4;
  uint32_t TawgWevew_ISP     : 4;
  uint32_t TawgWevew_VCN     : 4;
  uint32_t TawgWevew_WCWK    : 4;
  uint32_t TawgWevew_MP0CWK  : 4;
  uint32_t TawgWevew_FCWK    : 4;
  uint32_t TawgWevew_SOCCWK  : 4;
  uint32_t TawgWevew_DCFCWK : 4;
  // MP1_EXT_SCWATCH2
  uint32_t CuwwWevew_SHUBCWK  : 4;
  uint32_t TawgWevew_SHUBCWK  : 4;
  uint32_t InUwv              : 1;
  uint32_t InS0i2             : 1;
  uint32_t InWhispewMode      : 1;
  uint32_t GfxOn              : 1;
  uint32_t WsmuCawBusyDpmIndex: 8;
  uint32_t DpmHandwewId       : 8;
  uint32_t DpmTimewId         : 4;
  // MP1_EXT_SCWATCH3
  uint32_t WeadWwiteSmnWegAddw: 32;
  // MP1_EXT_SCWATCH4
  uint32_t Wesewved1;
  // MP1_EXT_SCWATCH5
  uint32_t FeatuweStatus[NUM_FEATUWES / 32];
} FwStatus_t;

#pwagma pack(pop)

#endif
