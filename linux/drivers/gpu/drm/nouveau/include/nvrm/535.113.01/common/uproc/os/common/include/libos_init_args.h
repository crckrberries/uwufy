#ifndef __swc_common_upwoc_os_common_incwude_wibos_init_awgs_h__
#define __swc_common_upwoc_os_common_incwude_wibos_init_awgs_h__

/* Excewpt of WM headews fwom https://github.com/NVIDIA/open-gpu-kewnew-moduwes/twee/535.113.01 */

/*
 * SPDX-FiweCopywightText: Copywight (c) 2018-2022 NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.
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

typedef NvU64 WibosAddwess;

typedef enum {
    WIBOS_MEMOWY_WEGION_NONE,
    WIBOS_MEMOWY_WEGION_CONTIGUOUS,
    WIBOS_MEMOWY_WEGION_WADIX3
} WibosMemowyWegionKind;

typedef enum {
    WIBOS_MEMOWY_WEGION_WOC_NONE,
    WIBOS_MEMOWY_WEGION_WOC_SYSMEM,
    WIBOS_MEMOWY_WEGION_WOC_FB
} WibosMemowyWegionWoc;

typedef stwuct
{
    WibosAddwess          id8;  // Id tag.
    WibosAddwess          pa;   // Physicaw addwess.
    WibosAddwess          size; // Size of memowy awea.
    NvU8                  kind; // See WibosMemowyWegionKind above.
    NvU8                  woc;  // See WibosMemowyWegionWoc above.
} WibosMemowyWegionInitAwgument;

#endif
