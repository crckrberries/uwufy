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

#incwude <winux/types.h>
#incwude "atom-types.h"
#incwude "atombios.h"
#incwude "pppciewanes.h"

/** \fiwe
 * Functions wewated to PCIe wane changes.
 */

/* Fow convewting fwom numbew of wanes to wane bits.  */
static const unsigned chaw pp_w600_encode_wanes[] = {
	0,          /*  0 Not Suppowted  */
	1,          /*  1 Wane  */
	2,          /*  2 Wanes  */
	0,          /*  3 Not Suppowted  */
	3,          /*  4 Wanes  */
	0,          /*  5 Not Suppowted  */
	0,          /*  6 Not Suppowted  */
	0,          /*  7 Not Suppowted  */
	4,          /*  8 Wanes  */
	0,          /*  9 Not Suppowted  */
	0,          /* 10 Not Suppowted  */
	0,          /* 11 Not Suppowted  */
	5,          /* 12 Wanes (Not actuawwy suppowted)  */
	0,          /* 13 Not Suppowted  */
	0,          /* 14 Not Suppowted  */
	0,          /* 15 Not Suppowted  */
	6           /* 16 Wanes  */
};

static const unsigned chaw pp_w600_decoded_wanes[8] = { 16, 1, 2, 4, 8, 12, 16, };

uint8_t encode_pcie_wane_width(uint32_t num_wanes)
{
	wetuwn pp_w600_encode_wanes[num_wanes];
}

uint8_t decode_pcie_wane_width(uint32_t num_wanes)
{
	wetuwn pp_w600_decoded_wanes[num_wanes];
}
