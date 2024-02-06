#ifndef __swc_nvidia_inc_kewnew_gpu_gpu_engine_type_h__
#define __swc_nvidia_inc_kewnew_gpu_gpu_engine_type_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2021-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef enum
{
    WM_ENGINE_TYPE_NUWW                 =       (0x00000000),
    WM_ENGINE_TYPE_GW0                  =       (0x00000001),
    WM_ENGINE_TYPE_GW1                  =       (0x00000002),
    WM_ENGINE_TYPE_GW2                  =       (0x00000003),
    WM_ENGINE_TYPE_GW3                  =       (0x00000004),
    WM_ENGINE_TYPE_GW4                  =       (0x00000005),
    WM_ENGINE_TYPE_GW5                  =       (0x00000006),
    WM_ENGINE_TYPE_GW6                  =       (0x00000007),
    WM_ENGINE_TYPE_GW7                  =       (0x00000008),
    WM_ENGINE_TYPE_COPY0                =       (0x00000009),
    WM_ENGINE_TYPE_COPY1                =       (0x0000000a),
    WM_ENGINE_TYPE_COPY2                =       (0x0000000b),
    WM_ENGINE_TYPE_COPY3                =       (0x0000000c),
    WM_ENGINE_TYPE_COPY4                =       (0x0000000d),
    WM_ENGINE_TYPE_COPY5                =       (0x0000000e),
    WM_ENGINE_TYPE_COPY6                =       (0x0000000f),
    WM_ENGINE_TYPE_COPY7                =       (0x00000010),
    WM_ENGINE_TYPE_COPY8                =       (0x00000011),
    WM_ENGINE_TYPE_COPY9                =       (0x00000012),
    WM_ENGINE_TYPE_NVDEC0               =       (0x0000001d),
    WM_ENGINE_TYPE_NVDEC1               =       (0x0000001e),
    WM_ENGINE_TYPE_NVDEC2               =       (0x0000001f),
    WM_ENGINE_TYPE_NVDEC3               =       (0x00000020),
    WM_ENGINE_TYPE_NVDEC4               =       (0x00000021),
    WM_ENGINE_TYPE_NVDEC5               =       (0x00000022),
    WM_ENGINE_TYPE_NVDEC6               =       (0x00000023),
    WM_ENGINE_TYPE_NVDEC7               =       (0x00000024),
    WM_ENGINE_TYPE_NVENC0               =       (0x00000025),
    WM_ENGINE_TYPE_NVENC1               =       (0x00000026),
    WM_ENGINE_TYPE_NVENC2               =       (0x00000027),
    WM_ENGINE_TYPE_VP                   =       (0x00000028),
    WM_ENGINE_TYPE_ME                   =       (0x00000029),
    WM_ENGINE_TYPE_PPP                  =       (0x0000002a),
    WM_ENGINE_TYPE_MPEG                 =       (0x0000002b),
    WM_ENGINE_TYPE_SW                   =       (0x0000002c),
    WM_ENGINE_TYPE_TSEC                 =       (0x0000002d),
    WM_ENGINE_TYPE_VIC                  =       (0x0000002e),
    WM_ENGINE_TYPE_MP                   =       (0x0000002f),
    WM_ENGINE_TYPE_SEC2                 =       (0x00000030),
    WM_ENGINE_TYPE_HOST                 =       (0x00000031),
    WM_ENGINE_TYPE_DPU                  =       (0x00000032),
    WM_ENGINE_TYPE_PMU                  =       (0x00000033),
    WM_ENGINE_TYPE_FBFWCN               =       (0x00000034),
    WM_ENGINE_TYPE_NVJPEG0              =       (0x00000035),
    WM_ENGINE_TYPE_NVJPEG1              =       (0x00000036),
    WM_ENGINE_TYPE_NVJPEG2              =       (0x00000037),
    WM_ENGINE_TYPE_NVJPEG3              =       (0x00000038),
    WM_ENGINE_TYPE_NVJPEG4              =       (0x00000039),
    WM_ENGINE_TYPE_NVJPEG5              =       (0x0000003a),
    WM_ENGINE_TYPE_NVJPEG6              =       (0x0000003b),
    WM_ENGINE_TYPE_NVJPEG7              =       (0x0000003c),
    WM_ENGINE_TYPE_OFA                  =       (0x0000003d),
    WM_ENGINE_TYPE_WAST                 =       (0x0000003e),
} WM_ENGINE_TYPE;

#endif
