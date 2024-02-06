#ifndef __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073system_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctww0073_ctww0073system_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2005-2021 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

#define NV0073_CTWW_CMD_SYSTEM_GET_NUM_HEADS (0x730102U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_SYSTEM_INTEWFACE_ID << 8) | NV0073_CTWW_SYSTEM_GET_NUM_HEADS_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_SYSTEM_GET_NUM_HEADS_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 fwags;
    NvU32 numHeads;
} NV0073_CTWW_SYSTEM_GET_NUM_HEADS_PAWAMS;

#define NV0073_CTWW_CMD_SYSTEM_GET_SUPPOWTED (0x730120U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_SYSTEM_INTEWFACE_ID << 8) | NV0073_CTWW_SYSTEM_GET_SUPPOWTED_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_SYSTEM_GET_SUPPOWTED_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 dispwayMask;
    NvU32 dispwayMaskDDC;
} NV0073_CTWW_SYSTEM_GET_SUPPOWTED_PAWAMS;

#define NV0073_CTWW_CMD_SYSTEM_GET_CONNECT_STATE (0x730122U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_SYSTEM_INTEWFACE_ID << 8) | NV0073_CTWW_SYSTEM_GET_CONNECT_STATE_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_SYSTEM_GET_CONNECT_STATE_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 fwags;
    NvU32 dispwayMask;
    NvU32 wetwyTimeMs;
} NV0073_CTWW_SYSTEM_GET_CONNECT_STATE_PAWAMS;

#define NV0073_CTWW_CMD_SYSTEM_GET_ACTIVE                (0x730126U) /* finn: Evawuated fwom "(FINN_NV04_DISPWAY_COMMON_SYSTEM_INTEWFACE_ID << 8) | NV0073_CTWW_SYSTEM_GET_ACTIVE_PAWAMS_MESSAGE_ID" */

typedef stwuct NV0073_CTWW_SYSTEM_GET_ACTIVE_PAWAMS {
    NvU32 subDeviceInstance;
    NvU32 head;
    NvU32 fwags;
    NvU32 dispwayId;
} NV0073_CTWW_SYSTEM_GET_ACTIVE_PAWAMS;

#define NV0073_CTWW_SYSTEM_ACPI_ID_MAP_MAX_DISPWAYS             (16U)

#endif
