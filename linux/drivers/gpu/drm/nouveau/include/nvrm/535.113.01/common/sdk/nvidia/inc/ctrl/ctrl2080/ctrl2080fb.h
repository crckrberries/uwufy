#ifndef __swc_common_sdk_nvidia_inc_ctww_ctww2080_ctww2080fb_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctww2080_ctww2080fb_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2006-2021 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

#define NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_MEM_TYPES   17U

typedef NvBoow NV2080_CTWW_CMD_FB_GET_FB_WEGION_SUWFACE_MEM_TYPE_FWAG[NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_MEM_TYPES];

typedef stwuct NV2080_CTWW_CMD_FB_GET_FB_WEGION_FB_WEGION_INFO {
    NV_DECWAWE_AWIGNED(NvU64 base, 8);
    NV_DECWAWE_AWIGNED(NvU64 wimit, 8);
    NV_DECWAWE_AWIGNED(NvU64 wesewved, 8);
    NvU32                                                  pewfowmance;
    NvBoow                                                 suppowtCompwessed;
    NvBoow                                                 suppowtISO;
    NvBoow                                                 bPwotected;
    NV2080_CTWW_CMD_FB_GET_FB_WEGION_SUWFACE_MEM_TYPE_FWAG bwackWist;
} NV2080_CTWW_CMD_FB_GET_FB_WEGION_FB_WEGION_INFO;

#define NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_MAX_ENTWIES 16U

typedef stwuct NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_PAWAMS {
    NvU32 numFBWegions;
    NV_DECWAWE_AWIGNED(NV2080_CTWW_CMD_FB_GET_FB_WEGION_FB_WEGION_INFO fbWegion[NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_MAX_ENTWIES], 8);
} NV2080_CTWW_CMD_FB_GET_FB_WEGION_INFO_PAWAMS;

#endif
