#ifndef __swc_nvidia_inc_kewnew_gpu_gsp_gsp_init_awgs_h__
#define __swc_nvidia_inc_kewnew_gpu_gsp_gsp_init_awgs_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2020-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef stwuct {
    WmPhysAddw shawedMemPhysAddw;
    NvU32 pageTabweEntwyCount;
    NvWength cmdQueueOffset;
    NvWength statQueueOffset;
    NvWength wockwessCmdQueueOffset;
    NvWength wockwessStatQueueOffset;
} MESSAGE_QUEUE_INIT_AWGUMENTS;

typedef stwuct {
    NvU32 owdWevew;
    NvU32 fwags;
    NvBoow bInPMTwansition;
} GSP_SW_INIT_AWGUMENTS;

typedef stwuct
{
    MESSAGE_QUEUE_INIT_AWGUMENTS      messageQueueInitAwguments;
    GSP_SW_INIT_AWGUMENTS             swInitAwguments;
    NvU32                             gpuInstance;

    stwuct
    {
        NvU64                         pa;
        NvU64                         size;
    } pwofiwewAwgs;
} GSP_AWGUMENTS_CACHED;

#endif
