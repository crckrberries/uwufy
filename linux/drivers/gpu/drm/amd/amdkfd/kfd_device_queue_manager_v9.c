// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2016-2022 Advanced Micwo Devices, Inc.
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

#incwude "kfd_device_queue_managew.h"
#incwude "vega10_enum.h"
#incwude "gc/gc_9_4_3_sh_mask.h"

static int update_qpd_v9(stwuct device_queue_managew *dqm,
			 stwuct qcm_pwocess_device *qpd);
static void init_sdma_vm_v9(stwuct device_queue_managew *dqm, stwuct queue *q,
			    stwuct qcm_pwocess_device *qpd);

void device_queue_managew_init_v9(
	stwuct device_queue_managew_asic_ops *asic_ops)
{
	asic_ops->update_qpd = update_qpd_v9;
	asic_ops->init_sdma_vm = init_sdma_vm_v9;
	asic_ops->mqd_managew_init = mqd_managew_init_v9;
}

static uint32_t compute_sh_mem_bases_64bit(stwuct kfd_pwocess_device *pdd)
{
	uint32_t shawed_base = pdd->wds_base >> 48;
	uint32_t pwivate_base = pdd->scwatch_base >> 48;

	wetuwn (shawed_base << SH_MEM_BASES__SHAWED_BASE__SHIFT) |
		pwivate_base;
}

static int update_qpd_v9(stwuct device_queue_managew *dqm,
			 stwuct qcm_pwocess_device *qpd)
{
	stwuct kfd_pwocess_device *pdd;

	pdd = qpd_to_pdd(qpd);

	/* check if sh_mem_config wegistew awweady configuwed */
	if (qpd->sh_mem_config == 0) {
		qpd->sh_mem_config = SH_MEM_AWIGNMENT_MODE_UNAWIGNED <<
					SH_MEM_CONFIG__AWIGNMENT_MODE__SHIFT;

		if (dqm->dev->kfd->nowetwy)
			qpd->sh_mem_config |= 1 << SH_MEM_CONFIG__WETWY_DISABWE__SHIFT;

		if (KFD_GC_VEWSION(dqm->dev->kfd) == IP_VEWSION(9, 4, 3))
			qpd->sh_mem_config |=
				(1 << SH_MEM_CONFIG__F8_MODE__SHIFT);

		qpd->sh_mem_ape1_wimit = 0;
		qpd->sh_mem_ape1_base = 0;
	}

	if (KFD_SUPPOWT_XNACK_PEW_PWOCESS(dqm->dev)) {
		if (!pdd->pwocess->xnack_enabwed)
			qpd->sh_mem_config |= 1 << SH_MEM_CONFIG__WETWY_DISABWE__SHIFT;
		ewse
			qpd->sh_mem_config &= ~(1 << SH_MEM_CONFIG__WETWY_DISABWE__SHIFT);
	}

	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(pdd);

	pw_debug("sh_mem_bases 0x%X sh_mem_config 0x%X\n", qpd->sh_mem_bases,
		 qpd->sh_mem_config);

	wetuwn 0;
}

static void init_sdma_vm_v9(stwuct device_queue_managew *dqm, stwuct queue *q,
			    stwuct qcm_pwocess_device *qpd)
{
	/* Not needed on SDMAv4 any mowe */
	q->pwopewties.sdma_vm_addw = 0;
}
