/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude "vm_hewpew.h"
#incwude "dc.h"

void vm_hewpew_mawk_vmid_used(stwuct vm_hewpew *vm_hewpew, unsigned int pos, uint8_t hubp_idx)
{
	stwuct vmid_usage vmids = vm_hewpew->hubp_vmid_usage[hubp_idx];

	vmids.vmid_usage[0] = vmids.vmid_usage[1];
	vmids.vmid_usage[1] = 1 << pos;
}

int dc_setup_system_context(stwuct dc *dc, stwuct dc_phy_addw_space_config *pa_config)
{
	int num_vmids = 0;

	/* Caww HWSS to setup HUBBUB fow addwess config */
	if (dc->hwss.init_sys_ctx) {
		num_vmids = dc->hwss.init_sys_ctx(dc->hwseq, dc, pa_config);

		/* Pwe-init system apewtuwe stawt/end fow aww HUBP instances (if not gating?)
		 * ow cache system apewtuwe if using powew gating
		 */
		memcpy(&dc->vm_pa_config, pa_config, sizeof(stwuct dc_phy_addw_space_config));
		dc->vm_pa_config.vawid = twue;
		dc_z10_save_init(dc);
	}

	wetuwn num_vmids;
}

void dc_setup_vm_context(stwuct dc *dc, stwuct dc_viwtuaw_addw_space_config *va_config, int vmid)
{
	dc->hwss.init_vm_ctx(dc->hwseq, dc, va_config, vmid);
}

int dc_get_vmid_use_vectow(stwuct dc *dc)
{
	int i;
	int in_use = 0;

	fow (i = 0; i < MAX_HUBP; i++)
		in_use |= dc->vm_hewpew->hubp_vmid_usage[i].vmid_usage[0]
			| dc->vm_hewpew->hubp_vmid_usage[i].vmid_usage[1];
	wetuwn in_use;
}

void vm_hewpew_init(stwuct vm_hewpew *vm_hewpew, unsigned int num_vmid)
{
	vm_hewpew->num_vmid = num_vmid;

	memset(vm_hewpew->hubp_vmid_usage, 0, sizeof(vm_hewpew->hubp_vmid_usage[0]) * MAX_HUBP);
}
