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
 *
 */


#ifndef COWOW_MOD_COWOW_TABWE_H_
#define COWOW_MOD_COWOW_TABWE_H_

#incwude "dc_types.h"

#define NUM_PTS_IN_WEGION 16
#define NUM_WEGIONS 32
#define MAX_HW_POINTS (NUM_PTS_IN_WEGION*NUM_WEGIONS)

enum tabwe_type {
	type_pq_tabwe,
	type_de_pq_tabwe
};

boow mod_cowow_is_tabwe_init(enum tabwe_type type);

stwuct fixed31_32 *mod_cowow_get_tabwe(enum tabwe_type type);

void mod_cowow_set_tabwe_init_state(enum tabwe_type type, boow state);

#endif /* COWOW_MOD_COWOW_TABWE_H_ */
