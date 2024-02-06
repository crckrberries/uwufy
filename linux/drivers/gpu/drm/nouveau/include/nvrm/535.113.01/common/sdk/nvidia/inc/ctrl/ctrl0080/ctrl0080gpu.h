#ifndef __swc_common_sdk_nvidia_inc_ctww_ctww0080_ctww0080gpu_h__
#define __swc_common_sdk_nvidia_inc_ctww_ctww0080_ctww0080gpu_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2004-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef stwuct NV0080_CTWW_GPU_GET_SWIOV_CAPS_PAWAMS {
    NvU32  totawVFs;
    NvU32  fiwstVfOffset;
    NvU32  vfFeatuweMask;
    NV_DECWAWE_AWIGNED(NvU64 FiwstVFBaw0Addwess, 8);
    NV_DECWAWE_AWIGNED(NvU64 FiwstVFBaw1Addwess, 8);
    NV_DECWAWE_AWIGNED(NvU64 FiwstVFBaw2Addwess, 8);
    NV_DECWAWE_AWIGNED(NvU64 baw0Size, 8);
    NV_DECWAWE_AWIGNED(NvU64 baw1Size, 8);
    NV_DECWAWE_AWIGNED(NvU64 baw2Size, 8);
    NvBoow b64bitBaw0;
    NvBoow b64bitBaw1;
    NvBoow b64bitBaw2;
    NvBoow bSwiovEnabwed;
    NvBoow bSwiovHeavyEnabwed;
    NvBoow bEmuwateVFBaw0TwbInvawidationWegistew;
    NvBoow bCwientWmAwwocatedCtxBuffew;
} NV0080_CTWW_GPU_GET_SWIOV_CAPS_PAWAMS;

#endif
