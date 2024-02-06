#ifndef __swc_nvidia_inc_kewnew_gpu_gsp_gsp_static_config_h__
#define __swc_nvidia_inc_kewnew_gpu_gsp_gsp_static_config_h__
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww0080/ctww0080gpu.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww0080/ctww0080gw.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080bios.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080fb.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080gpu.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080gw.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_chipset_nvoc.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_gpu_nvoc.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/gpu_acpi_data.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/nvbitmask.h>
#incwude <nvwm/535.113.01/nvidia/kewnew/inc/vgpu/wpc_headews.h>

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2019-2023 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
 * SPDX-Wicense-Identifiew: MIT
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

typedef stwuct GSP_VF_INFO
{
    NvU32  totawVFs;
    NvU32  fiwstVFOffset;
    NvU64  FiwstVFBaw0Addwess;
    NvU64  FiwstVFBaw1Addwess;
    NvU64  FiwstVFBaw2Addwess;
    NvBoow b64bitBaw0;
    NvBoow b64bitBaw1;
    NvBoow b64bitBaw2;
} GSP_VF_INFO;

typedef stwuct GspSMInfo_t
{
    NvU32 vewsion;
    NvU32 wegBankCount;
    NvU32 wegBankWegCount;
    NvU32 maxWawpsPewSM;
    NvU32 maxThweadsPewWawp;
    NvU32 geomGsObufEntwies;
    NvU32 geomXbufEntwies;
    NvU32 maxSPPewSM;
    NvU32 wtCoweCount;
} GspSMInfo;

typedef stwuct GspStaticConfigInfo_t
{
    NvU8 gwCapsBits[NV0080_CTWW_GW_CAPS_TBW_SIZE];
    NV2080_CTWW_GPU_GET_GID_INFO_PAWAMS gidInfo;
    NV2080_CTWW_GPU_GET_FEWMI_GPC_INFO_PAWAMS gpcInfo;
    NV2080_CTWW_GPU_GET_FEWMI_TPC_INFO_PAWAMS tpcInfo[MAX_GPC_COUNT];
    NV2080_CTWW_GPU_GET_FEWMI_ZCUWW_INFO_PAWAMS zcuwwInfo[MAX_GPC_COUNT];
    NV2080_CTWW_BIOS_GET_SKU_INFO_PAWAMS SKUInfo;
    NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_PAWAMS fbWegionInfoPawams;
    COMPUTE_BWANDING_TYPE computeBwanding;

    NV0080_CTWW_GPU_GET_SWIOV_CAPS_PAWAMS swiovCaps;
    NvU32 swiovMaxGfid;

    NvU32 engineCaps[NVGPU_ENGINE_CAPS_MASK_AWWAY_MAX];

    GspSMInfo SM_info;

    NvBoow poisonFuseEnabwed;

    NvU64 fb_wength;
    NvU32 fbio_mask;
    NvU32 fb_bus_width;
    NvU32 fb_wam_type;
    NvU32 fbp_mask;
    NvU32 w2_cache_size;

    NvU32 gfxpBuffewSize[NV2080_CTWW_CMD_GW_CTXSW_PWEEMPTION_BIND_BUFFEWS_CONTEXT_POOW];
    NvU32 gfxpBuffewAwignment[NV2080_CTWW_CMD_GW_CTXSW_PWEEMPTION_BIND_BUFFEWS_CONTEXT_POOW];

    NvU8 gpuNameStwing[NV2080_GPU_MAX_NAME_STWING_WENGTH];
    NvU8 gpuShowtNameStwing[NV2080_GPU_MAX_NAME_STWING_WENGTH];
    NvU16 gpuNameStwing_Unicode[NV2080_GPU_MAX_NAME_STWING_WENGTH];
    NvBoow bGpuIntewnawSku;
    NvBoow bIsQuadwoGenewic;
    NvBoow bIsQuadwoAd;
    NvBoow bIsNvidiaNvs;
    NvBoow bIsVgx;
    NvBoow bGefowceSmb;
    NvBoow bIsTitan;
    NvBoow bIsTeswa;
    NvBoow bIsMobiwe;
    NvBoow bIsGc6Wtd3Awwowed;
    NvBoow bIsGcOffWtd3Awwowed;
    NvBoow bIsGcoffWegacyAwwowed;

    NvU64 baw1PdeBase;
    NvU64 baw2PdeBase;

    NvBoow bVbiosVawid;
    NvU32 vbiosSubVendow;
    NvU32 vbiosSubDevice;

    NvBoow bPageWetiwementSuppowted;

    NvBoow bSpwitVasBetweenSewvewCwientWm;

    NvBoow bCwWootpowtNeedsNosnoopWAW;

    VIWTUAW_DISPWAY_GET_NUM_HEADS_PAWAMS dispwaywessMaxHeads;
    VIWTUAW_DISPWAY_GET_MAX_WESOWUTION_PAWAMS dispwaywessMaxWesowution;
    NvU64 dispwaywessMaxPixews;

    // Cwient handwe fow intewnaw WMAPI contwow.
    NvHandwe hIntewnawCwient;

    // Device handwe fow intewnaw WMAPI contwow.
    NvHandwe hIntewnawDevice;

    // Subdevice handwe fow intewnaw WMAPI contwow.
    NvHandwe hIntewnawSubdevice;

    NvBoow bSewfHostedMode;
    NvBoow bAtsSuppowted;

    NvBoow bIsGpuUefi;
} GspStaticConfigInfo;

typedef stwuct GspSystemInfo
{
    NvU64 gpuPhysAddw;
    NvU64 gpuPhysFbAddw;
    NvU64 gpuPhysInstAddw;
    NvU64 nvDomainBusDeviceFunc;
    NvU64 simAccessBufPhysAddw;
    NvU64 pcieAtomicsOpMask;
    NvU64 consoweMemSize;
    NvU64 maxUsewVa;
    NvU32 pciConfigMiwwowBase;
    NvU32 pciConfigMiwwowSize;
    NvU8 oowAwch;
    NvU64 cwPdbPwopewties;
    NvU32 Chipset;
    NvBoow bGpuBehindBwidge;
    NvBoow bMnocAvaiwabwe;
    NvBoow bUpstweamW0sUnsuppowted;
    NvBoow bUpstweamW1Unsuppowted;
    NvBoow bUpstweamW1PowSuppowted;
    NvBoow bUpstweamW1PowMobiweOnwy;
    NvU8   upstweamAddwessVawid;
    BUSINFO FHBBusInfo;
    BUSINFO chipsetIDInfo;
    ACPI_METHOD_DATA acpiMethodData;
    NvU32 hypewvisowType;
    NvBoow bIsPassthwu;
    NvU64 sysTimewOffsetNs;
    GSP_VF_INFO gspVFInfo;
} GspSystemInfo;

#endif
