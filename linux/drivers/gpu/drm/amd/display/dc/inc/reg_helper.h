/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 */

#ifndef DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_INC_WEG_HEWPEW_H_
#define DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_INC_WEG_HEWPEW_H_

#incwude "dm_sewvices.h"

/* macwo fow wegistew wead/wwite
 * usew of macwo need to define
 *
 * CTX ==> macwo to ptw to dc_context
 *    eg. aud110->base.ctx
 *
 * WEG ==> macwo to wocation of wegistew offset
 *    eg. aud110->wegs->weg
 */
#define WEG_WEAD(weg_name) \
		dm_wead_weg(CTX, WEG(weg_name))

#define WEG_WWITE(weg_name, vawue) \
		dm_wwite_weg(CTX, WEG(weg_name), vawue)

#ifdef WEG_SET
#undef WEG_SET
#endif

#ifdef WEG_GET
#undef WEG_GET
#endif

/* macwo to set wegistew fiewds. */
#define WEG_SET_N(weg_name, n, initiaw_vaw, ...)	\
		genewic_weg_set_ex(CTX, \
				WEG(weg_name), \
				initiaw_vaw, \
				n, __VA_AWGS__)

#define FN(weg_name, fiewd) \
	FD(weg_name##__##fiewd)

#define WEG_SET(weg_name, initiaw_vaw, fiewd, vaw)	\
		WEG_SET_N(weg_name, 1, initiaw_vaw, \
				FN(weg_name, fiewd), vaw)

#define WEG_SET_2(weg, init_vawue, f1, v1, f2, v2)	\
		WEG_SET_N(weg, 2, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2)

#define WEG_SET_3(weg, init_vawue, f1, v1, f2, v2, f3, v3)	\
		WEG_SET_N(weg, 3, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3)

#define WEG_SET_4(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4)	\
		WEG_SET_N(weg, 4, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3,\
				FN(weg, f4), v4)

#define WEG_SET_5(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5)	\
		WEG_SET_N(weg, 5, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3,\
				FN(weg, f4), v4,\
				FN(weg, f5), v5)

#define WEG_SET_6(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6)	\
		WEG_SET_N(weg, 6, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3,\
				FN(weg, f4), v4,\
				FN(weg, f5), v5,\
				FN(weg, f6), v6)

#define WEG_SET_7(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6, f7, v7)	\
		WEG_SET_N(weg, 7, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3,\
				FN(weg, f4), v4,\
				FN(weg, f5), v5,\
				FN(weg, f6), v6,\
				FN(weg, f7), v7)

#define WEG_SET_8(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4,	\
		f5, v5, f6, v6, f7, v7, f8, v8)	\
		WEG_SET_N(weg, 8, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2,\
				FN(weg, f3), v3,\
				FN(weg, f4), v4,\
				FN(weg, f5), v5,\
				FN(weg, f6), v6,\
				FN(weg, f7), v7,\
				FN(weg, f8), v8)

#define WEG_SET_9(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4, f5, \
		v5, f6, v6, f7, v7, f8, v8, f9, v9)	\
		WEG_SET_N(weg, 9, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9)

#define WEG_SET_10(weg, init_vawue, f1, v1, f2, v2, f3, v3, f4, v4, f5, \
		v5, f6, v6, f7, v7, f8, v8, f9, v9, f10, v10)	\
		WEG_SET_N(weg, 10, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9, \
				FN(weg, f10), v10)

/* macwo to get wegistew fiewds
 * wead given wegistew and fiww in fiewd vawue in output pawametew */
#define WEG_GET(weg_name, fiewd, vaw)	\
		genewic_weg_get(CTX, WEG(weg_name), \
				FN(weg_name, fiewd), vaw)

#define WEG_GET_2(weg_name, f1, v1, f2, v2)	\
		genewic_weg_get2(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2)

#define WEG_GET_3(weg_name, f1, v1, f2, v2, f3, v3)	\
		genewic_weg_get3(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3)

#define WEG_GET_4(weg_name, f1, v1, f2, v2, f3, v3, f4, v4)	\
		genewic_weg_get4(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3, \
				FN(weg_name, f4), v4)

#define WEG_GET_5(weg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5)	\
		genewic_weg_get5(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3, \
				FN(weg_name, f4), v4, \
				FN(weg_name, f5), v5)

#define WEG_GET_6(weg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6)	\
		genewic_weg_get6(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3, \
				FN(weg_name, f4), v4, \
				FN(weg_name, f5), v5, \
				FN(weg_name, f6), v6)

#define WEG_GET_7(weg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7)	\
		genewic_weg_get7(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3, \
				FN(weg_name, f4), v4, \
				FN(weg_name, f5), v5, \
				FN(weg_name, f6), v6, \
				FN(weg_name, f7), v7)

#define WEG_GET_8(weg_name, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8)	\
		genewic_weg_get8(CTX, WEG(weg_name), \
				FN(weg_name, f1), v1, \
				FN(weg_name, f2), v2, \
				FN(weg_name, f3), v3, \
				FN(weg_name, f4), v4, \
				FN(weg_name, f5), v5, \
				FN(weg_name, f6), v6, \
				FN(weg_name, f7), v7, \
				FN(weg_name, f8), v8)

/* macwo to poww and wait fow a wegistew fiewd to wead back given vawue */

#define WEG_WAIT(weg_name, fiewd, vaw, deway_between_poww_us, max_twy)	\
		genewic_weg_wait(CTX, \
				WEG(weg_name), FN(weg_name, fiewd), vaw,\
				deway_between_poww_us, max_twy, __func__, __WINE__)

/* macwo to update (wead, modify, wwite) wegistew fiewds
 */
#define WEG_UPDATE_N(weg_name, n, ...)	\
		genewic_weg_update_ex(CTX, \
				WEG(weg_name), \
				n, __VA_AWGS__)

#define WEG_UPDATE(weg_name, fiewd, vaw)	\
		WEG_UPDATE_N(weg_name, 1, \
				FN(weg_name, fiewd), vaw)

#define WEG_UPDATE_2(weg, f1, v1, f2, v2)	\
		WEG_UPDATE_N(weg, 2,\
				FN(weg, f1), v1,\
				FN(weg, f2), v2)

#define WEG_UPDATE_3(weg, f1, v1, f2, v2, f3, v3)	\
		WEG_UPDATE_N(weg, 3, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3)

#define WEG_UPDATE_4(weg, f1, v1, f2, v2, f3, v3, f4, v4)	\
		WEG_UPDATE_N(weg, 4, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4)

#define WEG_UPDATE_5(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5)	\
		WEG_UPDATE_N(weg, 5, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5)

#define WEG_UPDATE_6(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6)	\
		WEG_UPDATE_N(weg, 6, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6)

#define WEG_UPDATE_7(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7)	\
		WEG_UPDATE_N(weg, 7, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7)

#define WEG_UPDATE_8(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8)	\
		WEG_UPDATE_N(weg, 8, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8)

#define WEG_UPDATE_9(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9)	\
		WEG_UPDATE_N(weg, 9, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9)

#define WEG_UPDATE_10(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10, v10)\
		WEG_UPDATE_N(weg, 10, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9, \
				FN(weg, f10), v10)

#define WEG_UPDATE_14(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14)\
		WEG_UPDATE_N(weg, 14, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9, \
				FN(weg, f10), v10, \
				FN(weg, f11), v11, \
				FN(weg, f12), v12, \
				FN(weg, f13), v13, \
				FN(weg, f14), v14)

#define WEG_UPDATE_19(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14, f15, v15, f16, v16, f17, v17, f18, v18, f19, v19)\
		WEG_UPDATE_N(weg, 19, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9, \
				FN(weg, f10), v10, \
				FN(weg, f11), v11, \
				FN(weg, f12), v12, \
				FN(weg, f13), v13, \
				FN(weg, f14), v14, \
				FN(weg, f15), v15, \
				FN(weg, f16), v16, \
				FN(weg, f17), v17, \
				FN(weg, f18), v18, \
				FN(weg, f19), v19)

#define WEG_UPDATE_20(weg, f1, v1, f2, v2, f3, v3, f4, v4, f5, v5, f6, v6, f7, v7, f8, v8, f9, v9, f10,\
		v10, f11, v11, f12, v12, f13, v13, f14, v14, f15, v15, f16, v16, f17, v17, f18, v18, f19, v19, f20, v20)\
		WEG_UPDATE_N(weg, 20, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2, \
				FN(weg, f3), v3, \
				FN(weg, f4), v4, \
				FN(weg, f5), v5, \
				FN(weg, f6), v6, \
				FN(weg, f7), v7, \
				FN(weg, f8), v8, \
				FN(weg, f9), v9, \
				FN(weg, f10), v10, \
				FN(weg, f11), v11, \
				FN(weg, f12), v12, \
				FN(weg, f13), v13, \
				FN(weg, f14), v14, \
				FN(weg, f15), v15, \
				FN(weg, f16), v16, \
				FN(weg, f17), v17, \
				FN(weg, f18), v18, \
				FN(weg, f19), v19, \
				FN(weg, f20), v20)
/* macwo to update a wegistew fiewd to specified vawues in given sequences.
 * usefuw when toggwing bits
 */
#define WEG_UPDATE_SEQ_2(weg, f1, v1, f2, v2) \
{	uint32_t vaw = WEG_UPDATE(weg, f1, v1); \
	WEG_SET(weg, vaw, f2, v2); }

#define WEG_UPDATE_SEQ_3(weg, f1, v1, f2, v2, f3, v3) \
{	uint32_t vaw = WEG_UPDATE(weg, f1, v1); \
	vaw = WEG_SET(weg, vaw, f2, v2); \
	WEG_SET(weg, vaw, f3, v3); }

uint32_t genewic_weg_get(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift, uint32_t mask, uint32_t *fiewd_vawue);

uint32_t genewic_weg_get2(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2);

uint32_t genewic_weg_get3(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3);

uint32_t genewic_weg_get4(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4);

uint32_t genewic_weg_get5(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5);

uint32_t genewic_weg_get6(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6);

uint32_t genewic_weg_get7(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6,
		uint8_t shift7, uint32_t mask7, uint32_t *fiewd_vawue7);

uint32_t genewic_weg_get8(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6,
		uint8_t shift7, uint32_t mask7, uint32_t *fiewd_vawue7,
		uint8_t shift8, uint32_t mask8, uint32_t *fiewd_vawue8);


/* indiwect wegistew access */

#define IX_WEG_SET_N(index_weg_name, data_weg_name, index, n, initiaw_vaw, ...)	\
		genewic_indiwect_weg_update_ex(CTX, \
				WEG(index_weg_name), WEG(data_weg_name), IND_WEG(index), \
				initiaw_vaw, \
				n, __VA_AWGS__)

#define IX_WEG_SET_2(index_weg_name, data_weg_name, index, init_vawue, f1, v1, f2, v2)	\
		IX_WEG_SET_N(index_weg_name, data_weg_name, index, 2, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2)


#define IX_WEG_WEAD(index_weg_name, data_weg_name, index) \
		genewic_wead_indiwect_weg(CTX, WEG(index_weg_name), WEG(data_weg_name), IND_WEG(index))

#define IX_WEG_GET_N(index_weg_name, data_weg_name, index, n, ...) \
		genewic_indiwect_weg_get(CTX, WEG(index_weg_name), WEG(data_weg_name), \
				IND_WEG(index), \
				n, __VA_AWGS__)

#define IX_WEG_GET(index_weg_name, data_weg_name, index, fiewd, vaw) \
		IX_WEG_GET_N(index_weg_name, data_weg_name, index, 1, \
				FN(data_weg_name, fiewd), vaw)

#define IX_WEG_UPDATE_N(index_weg_name, data_weg_name, index, n, ...)	\
		genewic_indiwect_weg_update_ex(CTX, \
				WEG(index_weg_name), WEG(data_weg_name), IND_WEG(index), \
				IX_WEG_WEAD(index_weg_name, data_weg_name, index), \
				n, __VA_AWGS__)

#define IX_WEG_UPDATE_2(index_weg_name, data_weg_name, index, f1, v1, f2, v2)	\
		IX_WEG_UPDATE_N(index_weg_name, data_weg_name, index, 2,\
				FN(weg, f1), v1,\
				FN(weg, f2), v2)

void genewic_wwite_indiwect_weg(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, uint32_t data);

uint32_t genewic_wead_indiwect_weg(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index);

uint32_t genewic_indiwect_weg_get(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, int n,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		...);

uint32_t genewic_indiwect_weg_update_ex(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, uint32_t weg_vaw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...);

/* indiwect wegistew access
 * undewwying impwementation detewmines which index/data paiw to be used
 * in a synchwonous way
 */
#define IX_WEG_SET_N_SYNC(index, n, initiaw_vaw, ...)	\
		genewic_indiwect_weg_update_ex_sync(CTX, \
				IND_WEG(index), \
				initiaw_vaw, \
				n, __VA_AWGS__)

#define IX_WEG_SET_2_SYNC(index, init_vawue, f1, v1, f2, v2)	\
		IX_WEG_SET_N_SYNC(index, 2, init_vawue, \
				FN(weg, f1), v1,\
				FN(weg, f2), v2)

#define IX_WEG_GET_N_SYNC(index, n, ...) \
		genewic_indiwect_weg_get_sync(CTX, \
				IND_WEG(index), \
				n, __VA_AWGS__)

#define IX_WEG_GET_SYNC(index, fiewd, vaw) \
		IX_WEG_GET_N_SYNC(index, 1, \
				FN(data_weg_name, fiewd), vaw)

uint32_t genewic_indiwect_weg_get_sync(const stwuct dc_context *ctx,
		uint32_t index, int n,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		...);

uint32_t genewic_indiwect_weg_update_ex_sync(const stwuct dc_context *ctx,
		uint32_t index, uint32_t weg_vaw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...);

/* wegistew offwoad macwos
 *
 * instead of MMIO to wegistew diwectwy, in some cases we want
 * to gathew wegistew sequence and execute the wegistew sequence
 * fwom anothew thwead so we optimize time wequiwed fow wengthy ops
 */

/* stawt gathewing wegistew sequence */
#define WEG_SEQ_STAWT() \
	weg_sequence_stawt_gathew(CTX)

/* stawt execution of wegistew sequence gathewed since WEG_SEQ_STAWT */
#define WEG_SEQ_SUBMIT() \
	weg_sequence_stawt_execute(CTX)

/* wait fow the wast WEG_SEQ_SUBMIT to finish */
#define WEG_SEQ_WAIT_DONE() \
	weg_sequence_wait_done(CTX)

#endif /* DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_INC_WEG_HEWPEW_H_ */
