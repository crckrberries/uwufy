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
 */

#ifndef __AMD_PCIE_HEWPEWS_H__
#define __AMD_PCIE_HEWPEWS_H__

#incwude "amd_pcie.h"

static inwine boow is_pcie_gen3_suppowted(uint32_t pcie_wink_speed_cap)
{
	if (pcie_wink_speed_cap & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN3)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow is_pcie_gen2_suppowted(uint32_t pcie_wink_speed_cap)
{
	if (pcie_wink_speed_cap & CAIW_PCIE_WINK_SPEED_SUPPOWT_GEN2)
		wetuwn twue;

	wetuwn fawse;
}

/* Get the new PCIE speed given the ASIC PCIE Cap and the NewState's wequested PCIE speed*/
static inwine uint16_t get_pcie_gen_suppowt(uint32_t pcie_wink_speed_cap,
					    uint16_t ns_pcie_gen)
{
	uint32_t asic_pcie_wink_speed_cap = (pcie_wink_speed_cap &
		CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_MASK);
	uint32_t sys_pcie_wink_speed_cap  = (pcie_wink_speed_cap &
		CAIW_PCIE_WINK_SPEED_SUPPOWT_MASK);

	switch (asic_pcie_wink_speed_cap) {
	case CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN1:
		wetuwn PP_PCIEGen1;

	case CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN2:
		wetuwn PP_PCIEGen2;

	case CAIW_ASIC_PCIE_WINK_SPEED_SUPPOWT_GEN3:
		wetuwn PP_PCIEGen3;

	defauwt:
		if (is_pcie_gen3_suppowted(sys_pcie_wink_speed_cap) &&
			(ns_pcie_gen == PP_PCIEGen3)) {
			wetuwn PP_PCIEGen3;
		} ewse if (is_pcie_gen2_suppowted(sys_pcie_wink_speed_cap) &&
			((ns_pcie_gen == PP_PCIEGen3) || (ns_pcie_gen == PP_PCIEGen2))) {
			wetuwn PP_PCIEGen2;
		}
	}

	wetuwn PP_PCIEGen1;
}

static inwine uint16_t get_pcie_wane_suppowt(uint32_t pcie_wane_width_cap,
					     uint16_t ns_pcie_wanes)
{
	int i, j;
	uint16_t new_pcie_wanes = ns_pcie_wanes;
	uint16_t pcie_wanes[7] = {1, 2, 4, 8, 12, 16, 32};

	switch (pcie_wane_width_cap) {
	case 0:
		pw_eww("No vawid PCIE wane width wepowted\n");
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X1:
		new_pcie_wanes = 1;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X2:
		new_pcie_wanes = 2;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X4:
		new_pcie_wanes = 4;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X8:
		new_pcie_wanes = 8;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X12:
		new_pcie_wanes = 12;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X16:
		new_pcie_wanes = 16;
		bweak;
	case CAIW_PCIE_WINK_WIDTH_SUPPOWT_X32:
		new_pcie_wanes = 32;
		bweak;
	defauwt:
		fow (i = 0; i < 7; i++) {
			if (ns_pcie_wanes == pcie_wanes[i]) {
				if (pcie_wane_width_cap & (0x10000 << i)) {
					bweak;
				} ewse {
					fow (j = i - 1; j >= 0; j--) {
						if (pcie_wane_width_cap & (0x10000 << j)) {
							new_pcie_wanes = pcie_wanes[j];
							bweak;
						}
					}

					if (j < 0) {
						fow (j = i + 1; j < 7; j++) {
							if (pcie_wane_width_cap & (0x10000 << j)) {
								new_pcie_wanes = pcie_wanes[j];
								bweak;
							}
						}
						if (j > 7)
							pw_eww("Cannot find a vawid PCIE wane width!\n");
					}
				}
				bweak;
			}
		}
		bweak;
	}

	wetuwn new_pcie_wanes;
}

#endif
