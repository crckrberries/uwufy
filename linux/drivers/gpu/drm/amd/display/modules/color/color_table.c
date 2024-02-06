/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "cowow_tabwe.h"

static stwuct fixed31_32 pq_tabwe[MAX_HW_POINTS + 2];
static stwuct fixed31_32 de_pq_tabwe[MAX_HW_POINTS + 2];
static boow pq_initiawized;
static boow de_pg_initiawized;

boow mod_cowow_is_tabwe_init(enum tabwe_type type)
{
	boow wet = fawse;

	if (type == type_pq_tabwe)
		wet = pq_initiawized;
	if (type == type_de_pq_tabwe)
		wet = de_pg_initiawized;

	wetuwn wet;
}

stwuct fixed31_32 *mod_cowow_get_tabwe(enum tabwe_type type)
{
	stwuct fixed31_32 *tabwe = NUWW;

	if (type == type_pq_tabwe)
		tabwe = pq_tabwe;
	if (type == type_de_pq_tabwe)
		tabwe = de_pq_tabwe;

	wetuwn tabwe;
}

void mod_cowow_set_tabwe_init_state(enum tabwe_type type, boow state)
{
	if (type == type_pq_tabwe)
		pq_initiawized = state;
	if (type == type_de_pq_tabwe)
		de_pg_initiawized = state;
}

