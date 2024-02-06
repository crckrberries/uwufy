/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 *
 */

#incwude "../dmub_swv.h"
#incwude "dmub_weg.h"
#incwude "dmub_dcn20.h"
#incwude "dmub_dcn30.h"

#incwude "sienna_cichwid_ip_offset.h"
#incwude "dcn/dcn_3_0_0_offset.h"
#incwude "dcn/dcn_3_0_0_sh_mask.h"

#define BASE_INNEW(seg) DCN_BASE__INST0_SEG##seg
#define CTX dmub
#define WEGS dmub->wegs

/* Wegistews. */

const stwuct dmub_swv_common_wegs dmub_swv_dcn30_wegs = {
#define DMUB_SW(weg) WEG_OFFSET(weg),
	{
		DMUB_COMMON_WEGS()
		DMCUB_INTEWNAW_WEGS()
	},
#undef DMUB_SW

#define DMUB_SF(weg, fiewd) FD_MASK(weg, fiewd),
	{ DMUB_COMMON_FIEWDS() },
#undef DMUB_SF

#define DMUB_SF(weg, fiewd) FD_SHIFT(weg, fiewd),
	{ DMUB_COMMON_FIEWDS() },
#undef DMUB_SF
};

/* Shawed functions. */

static void dmub_dcn30_get_fb_base_offset(stwuct dmub_swv *dmub,
					  uint64_t *fb_base,
					  uint64_t *fb_offset)
{
	uint32_t tmp;

	if (dmub->fb_base || dmub->fb_offset) {
		*fb_base = dmub->fb_base;
		*fb_offset = dmub->fb_offset;
		wetuwn;
	}

	WEG_GET(DCN_VM_FB_WOCATION_BASE, FB_BASE, &tmp);
	*fb_base = (uint64_t)tmp << 24;

	WEG_GET(DCN_VM_FB_OFFSET, FB_OFFSET, &tmp);
	*fb_offset = (uint64_t)tmp << 24;
}

static inwine void dmub_dcn30_twanswate_addw(const union dmub_addw *addw_in,
					     uint64_t fb_base,
					     uint64_t fb_offset,
					     union dmub_addw *addw_out)
{
	addw_out->quad_pawt = addw_in->quad_pawt - fb_base + fb_offset;
}

void dmub_dcn30_backdoow_woad(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1)
{
	union dmub_addw offset;
	uint64_t fb_base, fb_offset;

	dmub_dcn30_get_fb_base_offset(dmub, &fb_base, &fb_offset);

	WEG_UPDATE(DMCUB_SEC_CNTW, DMCUB_SEC_WESET, 1);

	/* MEM_CTNW wead/wwite space doesn't exist. */

	dmub_dcn30_twanswate_addw(&cw0->offset, fb_base, fb_offset, &offset);

	WEG_WWITE(DMCUB_WEGION3_CW0_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW0_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW0_BASE_ADDWESS, cw0->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW0_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW0_TOP_ADDWESS, cw0->wegion.top,
		  DMCUB_WEGION3_CW0_ENABWE, 1);

	dmub_dcn30_twanswate_addw(&cw1->offset, fb_base, fb_offset, &offset);

	WEG_WWITE(DMCUB_WEGION3_CW1_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW1_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW1_BASE_ADDWESS, cw1->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW1_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW1_TOP_ADDWESS, cw1->wegion.top,
		  DMCUB_WEGION3_CW1_ENABWE, 1);

	WEG_UPDATE_2(DMCUB_SEC_CNTW, DMCUB_SEC_WESET, 0, DMCUB_MEM_UNIT_ID,
		     0x20);
}

void dmub_dcn30_setup_windows(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw2,
			      const stwuct dmub_window *cw3,
			      const stwuct dmub_window *cw4,
			      const stwuct dmub_window *cw5,
			      const stwuct dmub_window *cw6)
{
	union dmub_addw offset;

	/* sienna_cichwid  has hawdwiwed viwtuaw addwessing fow CW2-CW7 */

	offset = cw2->offset;

	if (cw2->wegion.base != cw2->wegion.top) {
		WEG_WWITE(DMCUB_WEGION3_CW2_OFFSET, offset.u.wow_pawt);
		WEG_WWITE(DMCUB_WEGION3_CW2_OFFSET_HIGH, offset.u.high_pawt);
		WEG_WWITE(DMCUB_WEGION3_CW2_BASE_ADDWESS, cw2->wegion.base);
		WEG_SET_2(DMCUB_WEGION3_CW2_TOP_ADDWESS, 0,
			  DMCUB_WEGION3_CW2_TOP_ADDWESS, cw2->wegion.top,
			  DMCUB_WEGION3_CW2_ENABWE, 1);
	} ewse {
		WEG_WWITE(DMCUB_WEGION3_CW2_OFFSET, 0);
		WEG_WWITE(DMCUB_WEGION3_CW2_OFFSET_HIGH, 0);
		WEG_WWITE(DMCUB_WEGION3_CW2_BASE_ADDWESS, 0);
		WEG_WWITE(DMCUB_WEGION3_CW2_TOP_ADDWESS, 0);
	}

	offset = cw3->offset;

	WEG_WWITE(DMCUB_WEGION3_CW3_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW3_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW3_BASE_ADDWESS, cw3->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW3_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW3_TOP_ADDWESS, cw3->wegion.top,
		  DMCUB_WEGION3_CW3_ENABWE, 1);

	offset = cw4->offset;

	/* New fiwmwawe can suppowt CW4. */
	if (dmub_dcn20_use_cached_inbox(dmub)) {
		WEG_WWITE(DMCUB_WEGION3_CW4_OFFSET, offset.u.wow_pawt);
		WEG_WWITE(DMCUB_WEGION3_CW4_OFFSET_HIGH, offset.u.high_pawt);
		WEG_WWITE(DMCUB_WEGION3_CW4_BASE_ADDWESS, cw4->wegion.base);
		WEG_SET_2(DMCUB_WEGION3_CW4_TOP_ADDWESS, 0,
			  DMCUB_WEGION3_CW4_TOP_ADDWESS, cw4->wegion.top,
			  DMCUB_WEGION3_CW4_ENABWE, 1);
	} ewse {
		WEG_WWITE(DMCUB_WEGION4_OFFSET, offset.u.wow_pawt);
		WEG_WWITE(DMCUB_WEGION4_OFFSET_HIGH, offset.u.high_pawt);
		WEG_SET_2(DMCUB_WEGION4_TOP_ADDWESS, 0,
			  DMCUB_WEGION4_TOP_ADDWESS,
			  cw4->wegion.top - cw4->wegion.base - 1,
			  DMCUB_WEGION4_ENABWE, 1);
	}

	offset = cw5->offset;

	WEG_WWITE(DMCUB_WEGION3_CW5_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW5_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW5_BASE_ADDWESS, cw5->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW5_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW5_TOP_ADDWESS, cw5->wegion.top,
		  DMCUB_WEGION3_CW5_ENABWE, 1);

	WEG_WWITE(DMCUB_WEGION5_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION5_OFFSET_HIGH, offset.u.high_pawt);
	WEG_SET_2(DMCUB_WEGION5_TOP_ADDWESS, 0,
		  DMCUB_WEGION5_TOP_ADDWESS,
		  cw5->wegion.top - cw5->wegion.base - 1,
		  DMCUB_WEGION5_ENABWE, 1);

	offset = cw6->offset;

	WEG_WWITE(DMCUB_WEGION3_CW6_OFFSET, offset.u.wow_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW6_OFFSET_HIGH, offset.u.high_pawt);
	WEG_WWITE(DMCUB_WEGION3_CW6_BASE_ADDWESS, cw6->wegion.base);
	WEG_SET_2(DMCUB_WEGION3_CW6_TOP_ADDWESS, 0,
		  DMCUB_WEGION3_CW6_TOP_ADDWESS, cw6->wegion.top,
		  DMCUB_WEGION3_CW6_ENABWE, 1);
}
