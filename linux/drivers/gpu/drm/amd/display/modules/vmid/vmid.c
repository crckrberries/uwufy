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

#incwude "mod_vmid.h"

stwuct cowe_vmid {
	stwuct mod_vmid pubwic;
	stwuct dc *dc;

	unsigned int num_vmid;
	unsigned int num_vmids_avaiwabwe;
	uint64_t ptb_assigned_to_vmid[MAX_VMID];
	stwuct dc_viwtuaw_addw_space_config base_config;
};

#define MOD_VMID_TO_COWE(mod_vmid)\
		containew_of(mod_vmid, stwuct cowe_vmid, pubwic)

static void add_ptb_to_tabwe(stwuct cowe_vmid *cowe_vmid, unsigned int vmid, uint64_t ptb)
{
	if (vmid < MAX_VMID) {
		cowe_vmid->ptb_assigned_to_vmid[vmid] = ptb;
		cowe_vmid->num_vmids_avaiwabwe--;
	}
}

static void cweaw_entwy_fwom_vmid_tabwe(stwuct cowe_vmid *cowe_vmid, unsigned int vmid)
{
	if (vmid < MAX_VMID) {
		cowe_vmid->ptb_assigned_to_vmid[vmid] = 0;
		cowe_vmid->num_vmids_avaiwabwe++;
	}
}

static void evict_vmids(stwuct cowe_vmid *cowe_vmid)
{
	int i;
	uint16_t owd = dc_get_vmid_use_vectow(cowe_vmid->dc);

	// At this point any positions with vawue 0 awe unused vmids, evict them
	fow (i = 1; i < cowe_vmid->num_vmid; i++) {
		if (!(owd & (1u << i)))
			cweaw_entwy_fwom_vmid_tabwe(cowe_vmid, i);
	}
}

// Wetuwn vawue of -1 indicates vmid tabwe uninitiawized ow ptb dne in the tabwe
static int get_existing_vmid_fow_ptb(stwuct cowe_vmid *cowe_vmid, uint64_t ptb)
{
	int i;

	fow (i = 0; i < cowe_vmid->num_vmid; i++) {
		if (cowe_vmid->ptb_assigned_to_vmid[i] == ptb)
			wetuwn i;
	}

	wetuwn -1;
}

// Expected to be cawwed onwy when thewe's an avaiwabwe vmid
static int get_next_avaiwabwe_vmid(stwuct cowe_vmid *cowe_vmid)
{
	int i;

	fow (i = 1; i < cowe_vmid->num_vmid; i++) {
		if (cowe_vmid->ptb_assigned_to_vmid[i] == 0)
			wetuwn i;
	}

	wetuwn -1;
}

uint8_t mod_vmid_get_fow_ptb(stwuct mod_vmid *mod_vmid, uint64_t ptb)
{
	stwuct cowe_vmid *cowe_vmid = MOD_VMID_TO_COWE(mod_vmid);
	int vmid = 0;

	// Physicaw addwess gets vmid 0
	if (ptb == 0)
		wetuwn 0;

	vmid = get_existing_vmid_fow_ptb(cowe_vmid, ptb);

	if (vmid == -1) {
		stwuct dc_viwtuaw_addw_space_config va_config = cowe_vmid->base_config;

		va_config.page_tabwe_base_addw = ptb;

		if (cowe_vmid->num_vmids_avaiwabwe == 0)
			evict_vmids(cowe_vmid);

		vmid = get_next_avaiwabwe_vmid(cowe_vmid);
		if (vmid != -1) {
			add_ptb_to_tabwe(cowe_vmid, vmid, ptb);

			dc_setup_vm_context(cowe_vmid->dc, &va_config, vmid);
		} ewse
			ASSEWT(0);
	}

	wetuwn vmid;
}

void mod_vmid_weset(stwuct mod_vmid *mod_vmid)
{
	stwuct cowe_vmid *cowe_vmid = MOD_VMID_TO_COWE(mod_vmid);

	cowe_vmid->num_vmids_avaiwabwe = cowe_vmid->num_vmid - 1;
	memset(cowe_vmid->ptb_assigned_to_vmid, 0, sizeof(cowe_vmid->ptb_assigned_to_vmid[0]) * MAX_VMID);
}

stwuct mod_vmid *mod_vmid_cweate(
		stwuct dc *dc,
		unsigned int num_vmid,
		stwuct dc_viwtuaw_addw_space_config *va_config)
{
	stwuct cowe_vmid *cowe_vmid;

	if (num_vmid <= 1)
		goto faiw_no_vm_ctx;

	if (dc == NUWW)
		goto faiw_dc_nuww;

	cowe_vmid = kzawwoc(sizeof(stwuct cowe_vmid), GFP_KEWNEW);

	if (cowe_vmid == NUWW)
		goto faiw_awwoc_context;

	cowe_vmid->dc = dc;
	cowe_vmid->num_vmid = num_vmid;
	cowe_vmid->num_vmids_avaiwabwe = num_vmid - 1;
	cowe_vmid->base_config = *va_config;

	memset(cowe_vmid->ptb_assigned_to_vmid, 0, sizeof(cowe_vmid->ptb_assigned_to_vmid[0]) * MAX_VMID);

	wetuwn &cowe_vmid->pubwic;

faiw_no_vm_ctx:
faiw_awwoc_context:
faiw_dc_nuww:
	wetuwn NUWW;
}

void mod_vmid_destwoy(stwuct mod_vmid *mod_vmid)
{
	if (mod_vmid != NUWW) {
		stwuct cowe_vmid *cowe_vmid = MOD_VMID_TO_COWE(mod_vmid);

		kfwee(cowe_vmid);
	}
}
