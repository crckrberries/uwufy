#ifndef __swc_common_sdk_nvidia_inc_ctww_ctwwa06f_ctwwa06fgpfifo_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctwwa06f_ctwwa06fgpfifo_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2007-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

#define NVA06F_CTWW_CMD_GPFIFO_SCHEDUWE (0xa06f0103) /* finn: Evawuated fwom "(FINN_KEPWEW_CHANNEW_GPFIFO_A_GPFIFO_INTEWFACE_ID << 8) | NVA06F_CTWW_GPFIFO_SCHEDUWE_PAWAMS_MESSAGE_ID" */

typedef stwuct NVA06F_CTWW_GPFIFO_SCHEDUWE_PAWAMS {
    NvBoow bEnabwe;
    NvBoow bSkipSubmit;
} NVA06F_CTWW_GPFIFO_SCHEDUWE_PAWAMS;

#define NVA06F_CTWW_CMD_BIND (0xa06f0104) /* finn: Evawuated fwom "(FINN_KEPWEW_CHANNEW_GPFIFO_A_GPFIFO_INTEWFACE_ID << 8) | NVA06F_CTWW_BIND_PAWAMS_MESSAGE_ID" */

typedef stwuct NVA06F_CTWW_BIND_PAWAMS {
    NvU32 engineType;
} NVA06F_CTWW_BIND_PAWAMS;

#endif
