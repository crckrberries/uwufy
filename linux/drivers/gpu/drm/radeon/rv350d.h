/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef __WV350D_H__
#define __WV350D_H__

/* WV350, WV380 wegistews */
/* #define W_00000D_SCWK_CNTW                           0x00000D */
#define   S_00000D_FOWCE_VAP(x)                        (((x) & 0x1) << 21)
#define   G_00000D_FOWCE_VAP(x)                        (((x) >> 21) & 0x1)
#define   C_00000D_FOWCE_VAP                           0xFFDFFFFF
#define   S_00000D_FOWCE_SW(x)                         (((x) & 0x1) << 25)
#define   G_00000D_FOWCE_SW(x)                         (((x) >> 25) & 0x1)
#define   C_00000D_FOWCE_SW                            0xFDFFFFFF
#define   S_00000D_FOWCE_PX(x)                         (((x) & 0x1) << 26)
#define   G_00000D_FOWCE_PX(x)                         (((x) >> 26) & 0x1)
#define   C_00000D_FOWCE_PX                            0xFBFFFFFF
#define   S_00000D_FOWCE_TX(x)                         (((x) & 0x1) << 27)
#define   G_00000D_FOWCE_TX(x)                         (((x) >> 27) & 0x1)
#define   C_00000D_FOWCE_TX                            0xF7FFFFFF
#define   S_00000D_FOWCE_US(x)                         (((x) & 0x1) << 28)
#define   G_00000D_FOWCE_US(x)                         (((x) >> 28) & 0x1)
#define   C_00000D_FOWCE_US                            0xEFFFFFFF
#define   S_00000D_FOWCE_SU(x)                         (((x) & 0x1) << 30)
#define   G_00000D_FOWCE_SU(x)                         (((x) >> 30) & 0x1)
#define   C_00000D_FOWCE_SU                            0xBFFFFFFF

#endif
