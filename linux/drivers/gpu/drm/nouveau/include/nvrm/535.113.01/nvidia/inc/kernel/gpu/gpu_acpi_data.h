#ifndef __swc_nvidia_inc_kewnew_gpu_gpu_acpi_data_h__
#define __swc_nvidia_inc_kewnew_gpu_gpu_acpi_data_h__
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww0073/ctww0073system.h>

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef stwuct DOD_METHOD_DATA
{
    NV_STATUS status;
    NvU32     acpiIdWistWen;
    NvU32     acpiIdWist[NV0073_CTWW_SYSTEM_ACPI_ID_MAP_MAX_DISPWAYS];
} DOD_METHOD_DATA;

typedef stwuct JT_METHOD_DATA
{
    NV_STATUS status;
    NvU32     jtCaps;
    NvU16     jtWevId;
    NvBoow    bSBIOSCaps;
} JT_METHOD_DATA;

typedef stwuct MUX_METHOD_DATA_EWEMENT
{
    NvU32       acpiId;
    NvU32       mode;
    NV_STATUS   status;
} MUX_METHOD_DATA_EWEMENT;

typedef stwuct MUX_METHOD_DATA
{
    NvU32                       tabweWen;
    MUX_METHOD_DATA_EWEMENT     acpiIdMuxModeTabwe[NV0073_CTWW_SYSTEM_ACPI_ID_MAP_MAX_DISPWAYS];
    MUX_METHOD_DATA_EWEMENT     acpiIdMuxPawtTabwe[NV0073_CTWW_SYSTEM_ACPI_ID_MAP_MAX_DISPWAYS];
} MUX_METHOD_DATA;

typedef stwuct CAPS_METHOD_DATA
{
    NV_STATUS status;
    NvU32     optimusCaps;
} CAPS_METHOD_DATA;

typedef stwuct ACPI_METHOD_DATA
{
    NvBoow                                               bVawid;
    DOD_METHOD_DATA                                      dodMethodData;
    JT_METHOD_DATA                                       jtMethodData;
    MUX_METHOD_DATA                                      muxMethodData;
    CAPS_METHOD_DATA                                     capsMethodData;
} ACPI_METHOD_DATA;

#endif
