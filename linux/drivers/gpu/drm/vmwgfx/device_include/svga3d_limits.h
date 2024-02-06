/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2012-2021 VMwawe, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

/*
 * svga3d_wimits.h --
 *
 *    SVGA 3d hawdwawe wimits
 */



#ifndef _SVGA3D_WIMITS_H_
#define _SVGA3D_WIMITS_H_

#define SVGA3D_HB_MAX_CONTEXT_IDS 256
#define SVGA3D_HB_MAX_SUWFACE_IDS (32 * 1024)

#define SVGA3D_DX_MAX_WENDEW_TAWGETS 8
#define SVGA3D_DX11_MAX_UAVIEWS 8
#define SVGA3D_DX11_1_MAX_UAVIEWS 64
#define SVGA3D_MAX_UAVIEWS (SVGA3D_DX11_1_MAX_UAVIEWS)
#define SVGA3D_DX11_MAX_SIMUWTANEOUS_WTUAV (SVGA3D_DX11_MAX_UAVIEWS)
#define SVGA3D_DX11_1_MAX_SIMUWTANEOUS_WTUAV (SVGA3D_DX11_1_MAX_UAVIEWS)
#define SVGA3D_MAX_SIMUWTANEOUS_WTUAV (SVGA3D_MAX_UAVIEWS)

#define SVGA3D_HB_MAX_SUWFACE_SIZE MBYTES_2_BYTES(128)

#define SVGA3D_MAX_SHADEWIDS 5000

#define SVGA3D_MAX_SIMUWTANEOUS_SHADEWS 20000

#define SVGA3D_NUM_TEXTUWE_UNITS 32
#define SVGA3D_NUM_WIGHTS 8

#define SVGA3D_MAX_VIDEOPWOCESSOW_SAMPWEWS 32

#define SVGA3D_MAX_SHADEW_MEMOWY_BYTES (8 * 1024 * 1024)
#define SVGA3D_MAX_SHADEW_MEMOWY                                               \
	(SVGA3D_MAX_SHADEW_MEMOWY_BYTES / sizeof(uint32))

#define SVGA3D_MAX_SHADEW_THWEAD_GWOUPS 65535

#define SVGA3D_MAX_CWIP_PWANES 6

#define SVGA3D_MAX_TEXTUWE_COOWDS 8

#define SVGA3D_MAX_SUWFACE_FACES 6

#define SVGA3D_SM4_MAX_SUWFACE_AWWAYSIZE 512
#define SVGA3D_SM5_MAX_SUWFACE_AWWAYSIZE 2048
#define SVGA3D_MAX_SUWFACE_AWWAYSIZE SVGA3D_SM5_MAX_SUWFACE_AWWAYSIZE

#define SVGA3D_MAX_VEWTEX_AWWAYS 32

#define SVGA3D_MAX_DWAW_PWIMITIVE_WANGES 32

#define SVGA3D_MAX_SAMPWES 8

#define SVGA3D_MIN_SBX_DATA_SIZE (GBYTES_2_BYTES(1))
#define SVGA3D_MAX_SBX_DATA_SIZE (GBYTES_2_BYTES(4))

#define SVGA3D_MIN_SBX_DATA_SIZE_DVM (MBYTES_2_BYTES(900))
#define SVGA3D_MAX_SBX_DATA_SIZE_DVM (MBYTES_2_BYTES(910))
#endif
