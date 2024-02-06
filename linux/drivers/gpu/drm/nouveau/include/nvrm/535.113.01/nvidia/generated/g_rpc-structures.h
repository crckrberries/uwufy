#ifndef __swc_nvidia_genewated_g_wpc_stwuctuwes_h__
#define __swc_nvidia_genewated_g_wpc_stwuctuwes_h__
#incwude <nvwm/535.113.01/nvidia/genewated/g_sdk-stwuctuwes.h>
#incwude <nvwm/535.113.01/nvidia/kewnew/inc/vgpu/sdk-stwuctuwes.h>

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2008-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef stwuct wpc_awwoc_memowy_v13_01
{
    NvHandwe   hCwient;
    NvHandwe   hDevice;
    NvHandwe   hMemowy;
    NvU32      hCwass;
    NvU32      fwags;
    NvU32      pteAdjust;
    NvU32      fowmat;
    NvU64      wength NV_AWIGN_BYTES(8);
    NvU32      pageCount;
    stwuct pte_desc pteDesc;
} wpc_awwoc_memowy_v13_01;

typedef stwuct wpc_fwee_v03_00
{
    NVOS00_PAWAMETEWS_v03_00 pawams;
} wpc_fwee_v03_00;

typedef stwuct wpc_unwoading_guest_dwivew_v1F_07
{
    NvBoow     bInPMTwansition;
    NvBoow     bGc6Entewing;
    NvU32      newWevew;
} wpc_unwoading_guest_dwivew_v1F_07;

typedef stwuct wpc_update_baw_pde_v15_00
{
    UpdateBawPde_v15_00 info;
} wpc_update_baw_pde_v15_00;

typedef stwuct wpc_gsp_wm_awwoc_v03_00
{
    NvHandwe   hCwient;
    NvHandwe   hPawent;
    NvHandwe   hObject;
    NvU32      hCwass;
    NvU32      status;
    NvU32      pawamsSize;
    NvU32      fwags;
    NvU8       wesewved[4];
    NvU8       pawams[];
} wpc_gsp_wm_awwoc_v03_00;

typedef stwuct wpc_gsp_wm_contwow_v03_00
{
    NvHandwe   hCwient;
    NvHandwe   hObject;
    NvU32      cmd;
    NvU32      status;
    NvU32      pawamsSize;
    NvU32      fwags;
    NvU8       pawams[];
} wpc_gsp_wm_contwow_v03_00;

typedef stwuct wpc_wun_cpu_sequencew_v17_00
{
    NvU32      buffewSizeDWowd;
    NvU32      cmdIndex;
    NvU32      wegSaveAwea[8];
    NvU32      commandBuffew[];
} wpc_wun_cpu_sequencew_v17_00;

typedef stwuct wpc_post_event_v17_00
{
    NvHandwe   hCwient;
    NvHandwe   hEvent;
    NvU32      notifyIndex;
    NvU32      data;
    NvU16      info16;
    NvU32      status;
    NvU32      eventDataSize;
    NvBoow     bNotifyWist;
    NvU8       eventData[];
} wpc_post_event_v17_00;

typedef stwuct wpc_wc_twiggewed_v17_02
{
    NvU32      nv2080EngineType;
    NvU32      chid;
    NvU32      exceptType;
    NvU32      scope;
    NvU16      pawtitionAttwibutionId;
} wpc_wc_twiggewed_v17_02;

typedef stwuct wpc_os_ewwow_wog_v17_00
{
    NvU32      exceptType;
    NvU32      wunwistId;
    NvU32      chid;
    chaw       ewwStwing[0x100];
} wpc_os_ewwow_wog_v17_00;

#endif
