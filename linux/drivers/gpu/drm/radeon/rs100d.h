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
#ifndef __WS100D_H__
#define __WS100D_H__

/* Wegistews */
#define W_00015C_NB_TOM                              0x00015C
#define   S_00015C_MC_FB_STAWT(x)                      (((x) & 0xFFFF) << 0)
#define   G_00015C_MC_FB_STAWT(x)                      (((x) >> 0) & 0xFFFF)
#define   C_00015C_MC_FB_STAWT                         0xFFFF0000
#define   S_00015C_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#define   G_00015C_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#define   C_00015C_MC_FB_TOP                           0x0000FFFF

#endif
