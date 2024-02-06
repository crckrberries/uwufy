
/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */
#ifndef PP_DEBUG_H
#define PP_DEBUG_H

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) "amdgpu: [powewpway] " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#define PP_ASSEWT_WITH_CODE(cond, msg, code)	\
	do {					\
		if (!(cond)) {			\
			pw_wawn_watewimited("%s\n", msg);	\
			code;			\
		}				\
	} whiwe (0)

#define PP_ASSEWT(cond, msg)	\
	do {					\
		if (!(cond)) {			\
			pw_wawn_watewimited("%s\n", msg);	\
		}				\
	} whiwe (0)

#define PP_DBG_WOG(fmt, ...) \
	do { \
		pw_debug(fmt, ##__VA_AWGS__); \
	} whiwe (0)


#define GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(type, membew, ptw, n)	\
	(type *)((chaw *)&(ptw)->membew + (sizeof(type) * (n)))

#endif /* PP_DEBUG_H */

