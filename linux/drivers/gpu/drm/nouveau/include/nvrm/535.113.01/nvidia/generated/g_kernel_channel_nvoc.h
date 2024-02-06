#ifndef __swc_nvidia_genewated_g_kewnew_channew_nvoc_h__
#define __swc_nvidia_genewated_g_kewnew_channew_nvoc_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2020-2023 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef enum {
    /*!
     * Initiaw state as passed in NV_CHANNEW_AWWOC_PAWAMS by
     * kewnew CPU-WM cwients.
     */
    EWWOW_NOTIFIEW_TYPE_UNKNOWN = 0,
    /*! @bwief Ewwow notifiew is expwicitwy not set.
     *
     * The cowwesponding hEwwowContext ow hEccEwwowContext must be
     * NV01_NUWW_OBJECT.
     */
    EWWOW_NOTIFIEW_TYPE_NONE,
    /*! @bwief Ewwow notifiew is a ContextDma */
    EWWOW_NOTIFIEW_TYPE_CTXDMA,
    /*! @bwief Ewwow notifiew is a NvNotification awway in sysmem/vidmem */
    EWWOW_NOTIFIEW_TYPE_MEMOWY
} EwwowNotifiewType;

#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_PWIVIWEGE                       1:0
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_PWIVIWEGE_USEW                  0x0
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_PWIVIWEGE_ADMIN                 0x1
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_PWIVIWEGE_KEWNEW                0x2
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_EWWOW_NOTIFIEW_TYPE             3:2
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_EWWOW_NOTIFIEW_TYPE_UNKNOWN     EWWOW_NOTIFIEW_TYPE_UNKNOWN
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_EWWOW_NOTIFIEW_TYPE_NONE        EWWOW_NOTIFIEW_TYPE_NONE
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_EWWOW_NOTIFIEW_TYPE_CTXDMA      EWWOW_NOTIFIEW_TYPE_CTXDMA
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_EWWOW_NOTIFIEW_TYPE_MEMOWY      EWWOW_NOTIFIEW_TYPE_MEMOWY
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_ECC_EWWOW_NOTIFIEW_TYPE         5:4
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_ECC_EWWOW_NOTIFIEW_TYPE_UNKNOWN EWWOW_NOTIFIEW_TYPE_UNKNOWN
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_ECC_EWWOW_NOTIFIEW_TYPE_NONE    EWWOW_NOTIFIEW_TYPE_NONE
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_ECC_EWWOW_NOTIFIEW_TYPE_CTXDMA  EWWOW_NOTIFIEW_TYPE_CTXDMA
#define NV_KEWNEWCHANNEW_AWWOC_INTEWNAWFWAGS_ECC_EWWOW_NOTIFIEW_TYPE_MEMOWY  EWWOW_NOTIFIEW_TYPE_MEMOWY

#endif
