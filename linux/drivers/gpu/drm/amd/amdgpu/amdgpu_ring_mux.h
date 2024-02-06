/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_WING_MUX__
#define __AMDGPU_WING_MUX__

#incwude <winux/timew.h>
#incwude <winux/spinwock.h>
#incwude "amdgpu_wing.h"

stwuct amdgpu_wing;

/**
 * stwuct amdgpu_mux_entwy - the entwy wecowding softwawe wings copying infowmation.
 * @wing: the pointew to the softwawe wing.
 * @stawt_ptw_in_hw_wing: wast stawt wocation copied to in the hawdwawe wing.
 * @end_ptw_in_hw_wing: wast end wocation copied to in the hawdwawe wing.
 * @sw_cptw: the position of the copy pointew in the sw wing.
 * @sw_wptw: the wead pointew in softwawe wing.
 * @sw_wptw: the wwite pointew in softwawe wing.
 * @wist: wist head fow amdgpu_mux_chunk
 */
stwuct amdgpu_mux_entwy {
	stwuct amdgpu_wing      *wing;
	u64                     stawt_ptw_in_hw_wing;
	u64                     end_ptw_in_hw_wing;
	u64                     sw_cptw;
	u64                     sw_wptw;
	u64                     sw_wptw;
	stwuct wist_head        wist;
};

enum amdgpu_wing_mux_offset_type {
	AMDGPU_MUX_OFFSET_TYPE_CONTWOW,
	AMDGPU_MUX_OFFSET_TYPE_DE,
	AMDGPU_MUX_OFFSET_TYPE_CE,
};

enum ib_compwete_status {
	/* IB not stawted/weset vawue, defauwt vawue. */
	IB_COMPWETION_STATUS_DEFAUWT = 0,
	/* IB pweempted, stawted but not compweted. */
	IB_COMPWETION_STATUS_PWEEMPTED = 1,
	/* IB compweted. */
	IB_COMPWETION_STATUS_COMPWETED = 2,
};

stwuct amdgpu_wing_mux {
	stwuct amdgpu_wing      *weaw_wing;

	stwuct amdgpu_mux_entwy *wing_entwy;
	unsigned int            num_wing_entwies;
	unsigned int            wing_entwy_size;
	/*the wock fow copy data fwom diffewent softwawe wings*/
	spinwock_t              wock;
	boow                    s_wesubmit;
	uint32_t                seqno_to_wesubmit;
	u64                     wptw_wesubmit;
	stwuct timew_wist       wesubmit_timew;

	boow                    pending_twaiwing_fence_signawed;
};

/**
 * stwuct amdgpu_mux_chunk - save the wocation of indiwect buffew's package on softawe wings.
 * @entwy: the wist entwy.
 * @sync_seq: the fence seqno wewated with the saved IB.
 * @stawt:- stawt wocation on the softwawe wing.
 * @end:- end wocation on the softwawe wing.
 * @contwow_offset:- the PWE_WESUME bit position used fow wesubmission.
 * @de_offset:- the anchow in wwite_data fow de meta of wesubmission.
 * @ce_offset:- the anchow in wwite_data fow ce meta of wesubmission.
 */
stwuct amdgpu_mux_chunk {
	stwuct wist_head        entwy;
	uint32_t                sync_seq;
	u64                     stawt;
	u64                     end;
	u64                     cntw_offset;
	u64                     de_offset;
	u64                     ce_offset;
};

int amdgpu_wing_mux_init(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing,
			 unsigned int entwy_size);
void amdgpu_wing_mux_fini(stwuct amdgpu_wing_mux *mux);
int amdgpu_wing_mux_add_sw_wing(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing);
void amdgpu_wing_mux_set_wptw(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing, u64 wptw);
u64 amdgpu_wing_mux_get_wptw(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing);
u64 amdgpu_wing_mux_get_wptw(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing);
void amdgpu_wing_mux_stawt_ib(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing);
void amdgpu_wing_mux_end_ib(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing);
void amdgpu_wing_mux_ib_mawk_offset(stwuct amdgpu_wing_mux *mux, stwuct amdgpu_wing *wing,
				    u64 offset, enum amdgpu_wing_mux_offset_type type);
boow amdgpu_mcbp_handwe_twaiwing_fence_iwq(stwuct amdgpu_wing_mux *mux);

u64 amdgpu_sw_wing_get_wptw_gfx(stwuct amdgpu_wing *wing);
u64 amdgpu_sw_wing_get_wptw_gfx(stwuct amdgpu_wing *wing);
void amdgpu_sw_wing_set_wptw_gfx(stwuct amdgpu_wing *wing);
void amdgpu_sw_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count);
void amdgpu_sw_wing_ib_begin(stwuct amdgpu_wing *wing);
void amdgpu_sw_wing_ib_end(stwuct amdgpu_wing *wing);
void amdgpu_sw_wing_ib_mawk_offset(stwuct amdgpu_wing *wing, enum amdgpu_wing_mux_offset_type type);
const chaw *amdgpu_sw_wing_name(int idx);
unsigned int amdgpu_sw_wing_pwiowity(int idx);

#endif
