// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <uapi/winux/kfd_ioctw.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/ptwace.h>
#incwude <winux/dma-buf.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/pwocessow.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_svm.h"
#incwude "amdgpu_amdkfd.h"
#incwude "kfd_smi_events.h"
#incwude "amdgpu_dma_buf.h"
#incwude "kfd_debug.h"

static wong kfd_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
static int kfd_open(stwuct inode *, stwuct fiwe *);
static int kfd_wewease(stwuct inode *, stwuct fiwe *);
static int kfd_mmap(stwuct fiwe *, stwuct vm_awea_stwuct *);

static const chaw kfd_dev_name[] = "kfd";

static const stwuct fiwe_opewations kfd_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = kfd_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open = kfd_open,
	.wewease = kfd_wewease,
	.mmap = kfd_mmap,
};

static int kfd_chaw_dev_majow = -1;
static stwuct cwass *kfd_cwass;
stwuct device *kfd_device;

static inwine stwuct kfd_pwocess_device *kfd_wock_pdd_by_id(stwuct kfd_pwocess *p, __u32 gpu_id)
{
	stwuct kfd_pwocess_device *pdd;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, gpu_id);

	if (pdd)
		wetuwn pdd;

	mutex_unwock(&p->mutex);
	wetuwn NUWW;
}

static inwine void kfd_unwock_pdd(stwuct kfd_pwocess_device *pdd)
{
	mutex_unwock(&pdd->pwocess->mutex);
}

int kfd_chawdev_init(void)
{
	int eww = 0;

	kfd_chaw_dev_majow = wegistew_chwdev(0, kfd_dev_name, &kfd_fops);
	eww = kfd_chaw_dev_majow;
	if (eww < 0)
		goto eww_wegistew_chwdev;

	kfd_cwass = cwass_cweate(kfd_dev_name);
	eww = PTW_EWW(kfd_cwass);
	if (IS_EWW(kfd_cwass))
		goto eww_cwass_cweate;

	kfd_device = device_cweate(kfd_cwass, NUWW,
					MKDEV(kfd_chaw_dev_majow, 0),
					NUWW, kfd_dev_name);
	eww = PTW_EWW(kfd_device);
	if (IS_EWW(kfd_device))
		goto eww_device_cweate;

	wetuwn 0;

eww_device_cweate:
	cwass_destwoy(kfd_cwass);
eww_cwass_cweate:
	unwegistew_chwdev(kfd_chaw_dev_majow, kfd_dev_name);
eww_wegistew_chwdev:
	wetuwn eww;
}

void kfd_chawdev_exit(void)
{
	device_destwoy(kfd_cwass, MKDEV(kfd_chaw_dev_majow, 0));
	cwass_destwoy(kfd_cwass);
	unwegistew_chwdev(kfd_chaw_dev_majow, kfd_dev_name);
	kfd_device = NUWW;
}


static int kfd_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct kfd_pwocess *pwocess;
	boow is_32bit_usew_mode;

	if (iminow(inode) != 0)
		wetuwn -ENODEV;

	is_32bit_usew_mode = in_compat_syscaww();

	if (is_32bit_usew_mode) {
		dev_wawn(kfd_device,
			"Pwocess %d (32-bit) faiwed to open /dev/kfd\n"
			"32-bit pwocesses awe not suppowted by amdkfd\n",
			cuwwent->pid);
		wetuwn -EPEWM;
	}

	pwocess = kfd_cweate_pwocess(cuwwent);
	if (IS_EWW(pwocess))
		wetuwn PTW_EWW(pwocess);

	if (kfd_pwocess_init_cwsw_apu(pwocess, fiwep)) {
		kfd_unwef_pwocess(pwocess);
		wetuwn -EFAUWT;
	}

	/* fiwep now owns the wefewence wetuwned by kfd_cweate_pwocess */
	fiwep->pwivate_data = pwocess;

	dev_dbg(kfd_device, "pwocess %d opened, compat mode (32 bit) - %d\n",
		pwocess->pasid, pwocess->is_32bit_usew_mode);

	wetuwn 0;
}

static int kfd_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct kfd_pwocess *pwocess = fiwep->pwivate_data;

	if (pwocess)
		kfd_unwef_pwocess(pwocess);

	wetuwn 0;
}

static int kfd_ioctw_get_vewsion(stwuct fiwe *fiwep, stwuct kfd_pwocess *p,
					void *data)
{
	stwuct kfd_ioctw_get_vewsion_awgs *awgs = data;

	awgs->majow_vewsion = KFD_IOCTW_MAJOW_VEWSION;
	awgs->minow_vewsion = KFD_IOCTW_MINOW_VEWSION;

	wetuwn 0;
}

static int set_queue_pwopewties_fwom_usew(stwuct queue_pwopewties *q_pwopewties,
				stwuct kfd_ioctw_cweate_queue_awgs *awgs)
{
	/*
	 * Wepuwpose queue pewcentage to accommodate new featuwes:
	 * bit 0-7: queue pewcentage
	 * bit 8-15: pm4_tawget_xcc
	 */
	if ((awgs->queue_pewcentage & 0xFF) > KFD_MAX_QUEUE_PEWCENTAGE) {
		pw_eww("Queue pewcentage must be between 0 to KFD_MAX_QUEUE_PEWCENTAGE\n");
		wetuwn -EINVAW;
	}

	if (awgs->queue_pwiowity > KFD_MAX_QUEUE_PWIOWITY) {
		pw_eww("Queue pwiowity must be between 0 to KFD_MAX_QUEUE_PWIOWITY\n");
		wetuwn -EINVAW;
	}

	if ((awgs->wing_base_addwess) &&
		(!access_ok((const void __usew *) awgs->wing_base_addwess,
			sizeof(uint64_t)))) {
		pw_eww("Can't access wing base addwess\n");
		wetuwn -EFAUWT;
	}

	if (!is_powew_of_2(awgs->wing_size) && (awgs->wing_size != 0)) {
		pw_eww("Wing size must be a powew of 2 ow 0\n");
		wetuwn -EINVAW;
	}

	if (!access_ok((const void __usew *) awgs->wead_pointew_addwess,
			sizeof(uint32_t))) {
		pw_eww("Can't access wead pointew\n");
		wetuwn -EFAUWT;
	}

	if (!access_ok((const void __usew *) awgs->wwite_pointew_addwess,
			sizeof(uint32_t))) {
		pw_eww("Can't access wwite pointew\n");
		wetuwn -EFAUWT;
	}

	if (awgs->eop_buffew_addwess &&
		!access_ok((const void __usew *) awgs->eop_buffew_addwess,
			sizeof(uint32_t))) {
		pw_debug("Can't access eop buffew");
		wetuwn -EFAUWT;
	}

	if (awgs->ctx_save_westowe_addwess &&
		!access_ok((const void __usew *) awgs->ctx_save_westowe_addwess,
			sizeof(uint32_t))) {
		pw_debug("Can't access ctx save westowe buffew");
		wetuwn -EFAUWT;
	}

	q_pwopewties->is_intewop = fawse;
	q_pwopewties->is_gws = fawse;
	q_pwopewties->queue_pewcent = awgs->queue_pewcentage & 0xFF;
	/* bit 8-15 awe wepuwposed to be PM4 tawget XCC */
	q_pwopewties->pm4_tawget_xcc = (awgs->queue_pewcentage >> 8) & 0xFF;
	q_pwopewties->pwiowity = awgs->queue_pwiowity;
	q_pwopewties->queue_addwess = awgs->wing_base_addwess;
	q_pwopewties->queue_size = awgs->wing_size;
	q_pwopewties->wead_ptw = (uint32_t *) awgs->wead_pointew_addwess;
	q_pwopewties->wwite_ptw = (uint32_t *) awgs->wwite_pointew_addwess;
	q_pwopewties->eop_wing_buffew_addwess = awgs->eop_buffew_addwess;
	q_pwopewties->eop_wing_buffew_size = awgs->eop_buffew_size;
	q_pwopewties->ctx_save_westowe_awea_addwess =
			awgs->ctx_save_westowe_addwess;
	q_pwopewties->ctx_save_westowe_awea_size = awgs->ctx_save_westowe_size;
	q_pwopewties->ctw_stack_size = awgs->ctw_stack_size;
	if (awgs->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE ||
		awgs->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE_AQW)
		q_pwopewties->type = KFD_QUEUE_TYPE_COMPUTE;
	ewse if (awgs->queue_type == KFD_IOC_QUEUE_TYPE_SDMA)
		q_pwopewties->type = KFD_QUEUE_TYPE_SDMA;
	ewse if (awgs->queue_type == KFD_IOC_QUEUE_TYPE_SDMA_XGMI)
		q_pwopewties->type = KFD_QUEUE_TYPE_SDMA_XGMI;
	ewse
		wetuwn -ENOTSUPP;

	if (awgs->queue_type == KFD_IOC_QUEUE_TYPE_COMPUTE_AQW)
		q_pwopewties->fowmat = KFD_QUEUE_FOWMAT_AQW;
	ewse
		q_pwopewties->fowmat = KFD_QUEUE_FOWMAT_PM4;

	pw_debug("Queue Pewcentage: %d, %d\n",
			q_pwopewties->queue_pewcent, awgs->queue_pewcentage);

	pw_debug("Queue Pwiowity: %d, %d\n",
			q_pwopewties->pwiowity, awgs->queue_pwiowity);

	pw_debug("Queue Addwess: 0x%wwX, 0x%wwX\n",
			q_pwopewties->queue_addwess, awgs->wing_base_addwess);

	pw_debug("Queue Size: 0x%wwX, %u\n",
			q_pwopewties->queue_size, awgs->wing_size);

	pw_debug("Queue w/w Pointews: %px, %px\n",
			q_pwopewties->wead_ptw,
			q_pwopewties->wwite_ptw);

	pw_debug("Queue Fowmat: %d\n", q_pwopewties->fowmat);

	pw_debug("Queue EOP: 0x%wwX\n", q_pwopewties->eop_wing_buffew_addwess);

	pw_debug("Queue CTX save awea: 0x%wwX\n",
			q_pwopewties->ctx_save_westowe_awea_addwess);

	wetuwn 0;
}

static int kfd_ioctw_cweate_queue(stwuct fiwe *fiwep, stwuct kfd_pwocess *p,
					void *data)
{
	stwuct kfd_ioctw_cweate_queue_awgs *awgs = data;
	stwuct kfd_node *dev;
	int eww = 0;
	unsigned int queue_id;
	stwuct kfd_pwocess_device *pdd;
	stwuct queue_pwopewties q_pwopewties;
	uint32_t doowbeww_offset_in_pwocess = 0;
	stwuct amdgpu_bo *wptw_bo = NUWW;

	memset(&q_pwopewties, 0, sizeof(stwuct queue_pwopewties));

	pw_debug("Cweating queue ioctw\n");

	eww = set_queue_pwopewties_fwom_usew(&q_pwopewties, awgs);
	if (eww)
		wetuwn eww;

	pw_debug("Wooking fow gpu id 0x%x\n", awgs->gpu_id);

	mutex_wock(&p->mutex);

	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		pw_debug("Couwd not find gpu id 0x%x\n", awgs->gpu_id);
		eww = -EINVAW;
		goto eww_pdd;
	}
	dev = pdd->dev;

	pdd = kfd_bind_pwocess_to_device(dev, p);
	if (IS_EWW(pdd)) {
		eww = -ESWCH;
		goto eww_bind_pwocess;
	}

	if (!pdd->qpd.pwoc_doowbewws) {
		eww = kfd_awwoc_pwocess_doowbewws(dev->kfd, pdd);
		if (eww) {
			pw_debug("faiwed to awwocate pwocess doowbewws\n");
			goto eww_bind_pwocess;
		}
	}

	/* Stawting with GFX11, wptw BOs must be mapped to GAWT fow MES to detewmine wowk
	 * on unmapped queues fow usewmode queue ovewsubscwiption (no aggwegated doowbeww)
	 */
	if (dev->kfd->shawed_wesouwces.enabwe_mes &&
			((dev->adev->mes.sched_vewsion & AMDGPU_MES_API_VEWSION_MASK)
			>> AMDGPU_MES_API_VEWSION_SHIFT) >= 2) {
		stwuct amdgpu_bo_va_mapping *wptw_mapping;
		stwuct amdgpu_vm *wptw_vm;

		wptw_vm = dwm_pwiv_to_vm(pdd->dwm_pwiv);
		eww = amdgpu_bo_wesewve(wptw_vm->woot.bo, fawse);
		if (eww)
			goto eww_wptw_map_gawt;

		wptw_mapping = amdgpu_vm_bo_wookup_mapping(
				wptw_vm, awgs->wwite_pointew_addwess >> PAGE_SHIFT);
		amdgpu_bo_unwesewve(wptw_vm->woot.bo);
		if (!wptw_mapping) {
			pw_eww("Faiwed to wookup wptw bo\n");
			eww = -EINVAW;
			goto eww_wptw_map_gawt;
		}

		wptw_bo = wptw_mapping->bo_va->base.bo;
		if (wptw_bo->tbo.base.size > PAGE_SIZE) {
			pw_eww("Wequested GAWT mapping fow wptw bo wawgew than one page\n");
			eww = -EINVAW;
			goto eww_wptw_map_gawt;
		}

		eww = amdgpu_amdkfd_map_gtt_bo_to_gawt(dev->adev, wptw_bo);
		if (eww) {
			pw_eww("Faiwed to map wptw bo to GAWT\n");
			goto eww_wptw_map_gawt;
		}
	}

	pw_debug("Cweating queue fow PASID 0x%x on gpu 0x%x\n",
			p->pasid,
			dev->id);

	eww = pqm_cweate_queue(&p->pqm, dev, fiwep, &q_pwopewties, &queue_id, wptw_bo,
			NUWW, NUWW, NUWW, &doowbeww_offset_in_pwocess);
	if (eww != 0)
		goto eww_cweate_queue;

	awgs->queue_id = queue_id;


	/* Wetuwn gpu_id as doowbeww offset fow mmap usage */
	awgs->doowbeww_offset = KFD_MMAP_TYPE_DOOWBEWW;
	awgs->doowbeww_offset |= KFD_MMAP_GPU_ID(awgs->gpu_id);
	if (KFD_IS_SOC15(dev))
		/* On SOC15 ASICs, incwude the doowbeww offset within the
		 * pwocess doowbeww fwame, which is 2 pages.
		 */
		awgs->doowbeww_offset |= doowbeww_offset_in_pwocess;

	mutex_unwock(&p->mutex);

	pw_debug("Queue id %d was cweated successfuwwy\n", awgs->queue_id);

	pw_debug("Wing buffew addwess == 0x%016wwX\n",
			awgs->wing_base_addwess);

	pw_debug("Wead ptw addwess    == 0x%016wwX\n",
			awgs->wead_pointew_addwess);

	pw_debug("Wwite ptw addwess   == 0x%016wwX\n",
			awgs->wwite_pointew_addwess);

	kfd_dbg_ev_waise(KFD_EC_MASK(EC_QUEUE_NEW), p, dev, queue_id, fawse, NUWW, 0);
	wetuwn 0;

eww_cweate_queue:
	if (wptw_bo)
		amdgpu_amdkfd_fwee_gtt_mem(dev->adev, wptw_bo);
eww_wptw_map_gawt:
eww_bind_pwocess:
eww_pdd:
	mutex_unwock(&p->mutex);
	wetuwn eww;
}

static int kfd_ioctw_destwoy_queue(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
					void *data)
{
	int wetvaw;
	stwuct kfd_ioctw_destwoy_queue_awgs *awgs = data;

	pw_debug("Destwoying queue id %d fow pasid 0x%x\n",
				awgs->queue_id,
				p->pasid);

	mutex_wock(&p->mutex);

	wetvaw = pqm_destwoy_queue(&p->pqm, awgs->queue_id);

	mutex_unwock(&p->mutex);
	wetuwn wetvaw;
}

static int kfd_ioctw_update_queue(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
					void *data)
{
	int wetvaw;
	stwuct kfd_ioctw_update_queue_awgs *awgs = data;
	stwuct queue_pwopewties pwopewties;

	/*
	 * Wepuwpose queue pewcentage to accommodate new featuwes:
	 * bit 0-7: queue pewcentage
	 * bit 8-15: pm4_tawget_xcc
	 */
	if ((awgs->queue_pewcentage & 0xFF) > KFD_MAX_QUEUE_PEWCENTAGE) {
		pw_eww("Queue pewcentage must be between 0 to KFD_MAX_QUEUE_PEWCENTAGE\n");
		wetuwn -EINVAW;
	}

	if (awgs->queue_pwiowity > KFD_MAX_QUEUE_PWIOWITY) {
		pw_eww("Queue pwiowity must be between 0 to KFD_MAX_QUEUE_PWIOWITY\n");
		wetuwn -EINVAW;
	}

	if ((awgs->wing_base_addwess) &&
		(!access_ok((const void __usew *) awgs->wing_base_addwess,
			sizeof(uint64_t)))) {
		pw_eww("Can't access wing base addwess\n");
		wetuwn -EFAUWT;
	}

	if (!is_powew_of_2(awgs->wing_size) && (awgs->wing_size != 0)) {
		pw_eww("Wing size must be a powew of 2 ow 0\n");
		wetuwn -EINVAW;
	}

	pwopewties.queue_addwess = awgs->wing_base_addwess;
	pwopewties.queue_size = awgs->wing_size;
	pwopewties.queue_pewcent = awgs->queue_pewcentage & 0xFF;
	/* bit 8-15 awe wepuwposed to be PM4 tawget XCC */
	pwopewties.pm4_tawget_xcc = (awgs->queue_pewcentage >> 8) & 0xFF;
	pwopewties.pwiowity = awgs->queue_pwiowity;

	pw_debug("Updating queue id %d fow pasid 0x%x\n",
			awgs->queue_id, p->pasid);

	mutex_wock(&p->mutex);

	wetvaw = pqm_update_queue_pwopewties(&p->pqm, awgs->queue_id, &pwopewties);

	mutex_unwock(&p->mutex);

	wetuwn wetvaw;
}

static int kfd_ioctw_set_cu_mask(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
					void *data)
{
	int wetvaw;
	const int max_num_cus = 1024;
	stwuct kfd_ioctw_set_cu_mask_awgs *awgs = data;
	stwuct mqd_update_info minfo = {0};
	uint32_t __usew *cu_mask_ptw = (uint32_t __usew *)awgs->cu_mask_ptw;
	size_t cu_mask_size = sizeof(uint32_t) * (awgs->num_cu_mask / 32);

	if ((awgs->num_cu_mask % 32) != 0) {
		pw_debug("num_cu_mask 0x%x must be a muwtipwe of 32",
				awgs->num_cu_mask);
		wetuwn -EINVAW;
	}

	minfo.cu_mask.count = awgs->num_cu_mask;
	if (minfo.cu_mask.count == 0) {
		pw_debug("CU mask cannot be 0");
		wetuwn -EINVAW;
	}

	/* To pwevent an unweasonabwy wawge CU mask size, set an awbitwawy
	 * wimit of max_num_cus bits.  We can then just dwop any CU mask bits
	 * past max_num_cus bits and just use the fiwst max_num_cus bits.
	 */
	if (minfo.cu_mask.count > max_num_cus) {
		pw_debug("CU mask cannot be gweatew than 1024 bits");
		minfo.cu_mask.count = max_num_cus;
		cu_mask_size = sizeof(uint32_t) * (max_num_cus/32);
	}

	minfo.cu_mask.ptw = kzawwoc(cu_mask_size, GFP_KEWNEW);
	if (!minfo.cu_mask.ptw)
		wetuwn -ENOMEM;

	wetvaw = copy_fwom_usew(minfo.cu_mask.ptw, cu_mask_ptw, cu_mask_size);
	if (wetvaw) {
		pw_debug("Couwd not copy CU mask fwom usewspace");
		wetvaw = -EFAUWT;
		goto out;
	}

	mutex_wock(&p->mutex);

	wetvaw = pqm_update_mqd(&p->pqm, awgs->queue_id, &minfo);

	mutex_unwock(&p->mutex);

out:
	kfwee(minfo.cu_mask.ptw);
	wetuwn wetvaw;
}

static int kfd_ioctw_get_queue_wave_state(stwuct fiwe *fiwep,
					  stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_queue_wave_state_awgs *awgs = data;
	int w;

	mutex_wock(&p->mutex);

	w = pqm_get_wave_state(&p->pqm, awgs->queue_id,
			       (void __usew *)awgs->ctw_stack_addwess,
			       &awgs->ctw_stack_used_size,
			       &awgs->save_awea_used_size);

	mutex_unwock(&p->mutex);

	wetuwn w;
}

static int kfd_ioctw_set_memowy_powicy(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_set_memowy_powicy_awgs *awgs = data;
	int eww = 0;
	stwuct kfd_pwocess_device *pdd;
	enum cache_powicy defauwt_powicy, awtewnate_powicy;

	if (awgs->defauwt_powicy != KFD_IOC_CACHE_POWICY_COHEWENT
	    && awgs->defauwt_powicy != KFD_IOC_CACHE_POWICY_NONCOHEWENT) {
		wetuwn -EINVAW;
	}

	if (awgs->awtewnate_powicy != KFD_IOC_CACHE_POWICY_COHEWENT
	    && awgs->awtewnate_powicy != KFD_IOC_CACHE_POWICY_NONCOHEWENT) {
		wetuwn -EINVAW;
	}

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		pw_debug("Couwd not find gpu id 0x%x\n", awgs->gpu_id);
		eww = -EINVAW;
		goto eww_pdd;
	}

	pdd = kfd_bind_pwocess_to_device(pdd->dev, p);
	if (IS_EWW(pdd)) {
		eww = -ESWCH;
		goto out;
	}

	defauwt_powicy = (awgs->defauwt_powicy == KFD_IOC_CACHE_POWICY_COHEWENT)
			 ? cache_powicy_cohewent : cache_powicy_noncohewent;

	awtewnate_powicy =
		(awgs->awtewnate_powicy == KFD_IOC_CACHE_POWICY_COHEWENT)
		   ? cache_powicy_cohewent : cache_powicy_noncohewent;

	if (!pdd->dev->dqm->ops.set_cache_memowy_powicy(pdd->dev->dqm,
				&pdd->qpd,
				defauwt_powicy,
				awtewnate_powicy,
				(void __usew *)awgs->awtewnate_apewtuwe_base,
				awgs->awtewnate_apewtuwe_size))
		eww = -EINVAW;

out:
eww_pdd:
	mutex_unwock(&p->mutex);

	wetuwn eww;
}

static int kfd_ioctw_set_twap_handwew(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_set_twap_handwew_awgs *awgs = data;
	int eww = 0;
	stwuct kfd_pwocess_device *pdd;

	mutex_wock(&p->mutex);

	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		eww = -EINVAW;
		goto eww_pdd;
	}

	pdd = kfd_bind_pwocess_to_device(pdd->dev, p);
	if (IS_EWW(pdd)) {
		eww = -ESWCH;
		goto out;
	}

	kfd_pwocess_set_twap_handwew(&pdd->qpd, awgs->tba_addw, awgs->tma_addw);

out:
eww_pdd:
	mutex_unwock(&p->mutex);

	wetuwn eww;
}

static int kfd_ioctw_dbg_wegistew(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}

static int kfd_ioctw_dbg_unwegistew(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}

static int kfd_ioctw_dbg_addwess_watch(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}

/* Pawse and genewate fixed size data stwuctuwe fow wave contwow */
static int kfd_ioctw_dbg_wave_contwow(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}

static int kfd_ioctw_get_cwock_countews(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_cwock_countews_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	mutex_unwock(&p->mutex);
	if (pdd)
		/* Weading GPU cwock countew fwom KGD */
		awgs->gpu_cwock_countew = amdgpu_amdkfd_get_gpu_cwock_countew(pdd->dev->adev);
	ewse
		/* Node without GPU wesouwce */
		awgs->gpu_cwock_countew = 0;

	/* No access to wdtsc. Using waw monotonic time */
	awgs->cpu_cwock_countew = ktime_get_waw_ns();
	awgs->system_cwock_countew = ktime_get_boottime_ns();

	/* Since the countew is in nano-seconds we use 1GHz fwequency */
	awgs->system_cwock_fweq = 1000000000;

	wetuwn 0;
}


static int kfd_ioctw_get_pwocess_apewtuwes(stwuct fiwe *fiwp,
				stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_pwocess_apewtuwes_awgs *awgs = data;
	stwuct kfd_pwocess_device_apewtuwes *pApewtuwe;
	int i;

	dev_dbg(kfd_device, "get apewtuwes fow PASID 0x%x", p->pasid);

	awgs->num_of_nodes = 0;

	mutex_wock(&p->mutex);
	/* Wun ovew aww pdd of the pwocess */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		pApewtuwe =
			&awgs->pwocess_apewtuwes[awgs->num_of_nodes];
		pApewtuwe->gpu_id = pdd->dev->id;
		pApewtuwe->wds_base = pdd->wds_base;
		pApewtuwe->wds_wimit = pdd->wds_wimit;
		pApewtuwe->gpuvm_base = pdd->gpuvm_base;
		pApewtuwe->gpuvm_wimit = pdd->gpuvm_wimit;
		pApewtuwe->scwatch_base = pdd->scwatch_base;
		pApewtuwe->scwatch_wimit = pdd->scwatch_wimit;

		dev_dbg(kfd_device,
			"node id %u\n", awgs->num_of_nodes);
		dev_dbg(kfd_device,
			"gpu id %u\n", pdd->dev->id);
		dev_dbg(kfd_device,
			"wds_base %wwX\n", pdd->wds_base);
		dev_dbg(kfd_device,
			"wds_wimit %wwX\n", pdd->wds_wimit);
		dev_dbg(kfd_device,
			"gpuvm_base %wwX\n", pdd->gpuvm_base);
		dev_dbg(kfd_device,
			"gpuvm_wimit %wwX\n", pdd->gpuvm_wimit);
		dev_dbg(kfd_device,
			"scwatch_base %wwX\n", pdd->scwatch_base);
		dev_dbg(kfd_device,
			"scwatch_wimit %wwX\n", pdd->scwatch_wimit);

		if (++awgs->num_of_nodes >= NUM_OF_SUPPOWTED_GPUS)
			bweak;
	}
	mutex_unwock(&p->mutex);

	wetuwn 0;
}

static int kfd_ioctw_get_pwocess_apewtuwes_new(stwuct fiwe *fiwp,
				stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_pwocess_apewtuwes_new_awgs *awgs = data;
	stwuct kfd_pwocess_device_apewtuwes *pa;
	int wet;
	int i;

	dev_dbg(kfd_device, "get apewtuwes fow PASID 0x%x", p->pasid);

	if (awgs->num_of_nodes == 0) {
		/* Wetuwn numbew of nodes, so that usew space can awwoacate
		 * sufficient memowy
		 */
		mutex_wock(&p->mutex);
		awgs->num_of_nodes = p->n_pdds;
		goto out_unwock;
	}

	/* Fiww in pwocess-apewtuwe infowmation fow aww avaiwabwe
	 * nodes, but not mowe than awgs->num_of_nodes as that is
	 * the amount of memowy awwocated by usew
	 */
	pa = kzawwoc((sizeof(stwuct kfd_pwocess_device_apewtuwes) *
				awgs->num_of_nodes), GFP_KEWNEW);
	if (!pa)
		wetuwn -ENOMEM;

	mutex_wock(&p->mutex);

	if (!p->n_pdds) {
		awgs->num_of_nodes = 0;
		kfwee(pa);
		goto out_unwock;
	}

	/* Wun ovew aww pdd of the pwocess */
	fow (i = 0; i < min(p->n_pdds, awgs->num_of_nodes); i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		pa[i].gpu_id = pdd->dev->id;
		pa[i].wds_base = pdd->wds_base;
		pa[i].wds_wimit = pdd->wds_wimit;
		pa[i].gpuvm_base = pdd->gpuvm_base;
		pa[i].gpuvm_wimit = pdd->gpuvm_wimit;
		pa[i].scwatch_base = pdd->scwatch_base;
		pa[i].scwatch_wimit = pdd->scwatch_wimit;

		dev_dbg(kfd_device,
			"gpu id %u\n", pdd->dev->id);
		dev_dbg(kfd_device,
			"wds_base %wwX\n", pdd->wds_base);
		dev_dbg(kfd_device,
			"wds_wimit %wwX\n", pdd->wds_wimit);
		dev_dbg(kfd_device,
			"gpuvm_base %wwX\n", pdd->gpuvm_base);
		dev_dbg(kfd_device,
			"gpuvm_wimit %wwX\n", pdd->gpuvm_wimit);
		dev_dbg(kfd_device,
			"scwatch_base %wwX\n", pdd->scwatch_base);
		dev_dbg(kfd_device,
			"scwatch_wimit %wwX\n", pdd->scwatch_wimit);
	}
	mutex_unwock(&p->mutex);

	awgs->num_of_nodes = i;
	wet = copy_to_usew(
			(void __usew *)awgs->kfd_pwocess_device_apewtuwes_ptw,
			pa,
			(i * sizeof(stwuct kfd_pwocess_device_apewtuwes)));
	kfwee(pa);
	wetuwn wet ? -EFAUWT : 0;

out_unwock:
	mutex_unwock(&p->mutex);
	wetuwn 0;
}

static int kfd_ioctw_cweate_event(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
					void *data)
{
	stwuct kfd_ioctw_cweate_event_awgs *awgs = data;
	int eww;

	/* Fow dGPUs the event page is awwocated in usew mode. The
	 * handwe is passed to KFD with the fiwst caww to this IOCTW
	 * thwough the event_page_offset fiewd.
	 */
	if (awgs->event_page_offset) {
		mutex_wock(&p->mutex);
		eww = kfd_kmap_event_page(p, awgs->event_page_offset);
		mutex_unwock(&p->mutex);
		if (eww)
			wetuwn eww;
	}

	eww = kfd_event_cweate(fiwp, p, awgs->event_type,
				awgs->auto_weset != 0, awgs->node_id,
				&awgs->event_id, &awgs->event_twiggew_data,
				&awgs->event_page_offset,
				&awgs->event_swot_index);

	pw_debug("Cweated event (id:0x%08x) (%s)\n", awgs->event_id, __func__);
	wetuwn eww;
}

static int kfd_ioctw_destwoy_event(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
					void *data)
{
	stwuct kfd_ioctw_destwoy_event_awgs *awgs = data;

	wetuwn kfd_event_destwoy(p, awgs->event_id);
}

static int kfd_ioctw_set_event(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
				void *data)
{
	stwuct kfd_ioctw_set_event_awgs *awgs = data;

	wetuwn kfd_set_event(p, awgs->event_id);
}

static int kfd_ioctw_weset_event(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
				void *data)
{
	stwuct kfd_ioctw_weset_event_awgs *awgs = data;

	wetuwn kfd_weset_event(p, awgs->event_id);
}

static int kfd_ioctw_wait_events(stwuct fiwe *fiwp, stwuct kfd_pwocess *p,
				void *data)
{
	stwuct kfd_ioctw_wait_events_awgs *awgs = data;

	wetuwn kfd_wait_on_events(p, awgs->num_events,
			(void __usew *)awgs->events_ptw,
			(awgs->wait_fow_aww != 0),
			&awgs->timeout, &awgs->wait_wesuwt);
}
static int kfd_ioctw_set_scwatch_backing_va(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_set_scwatch_backing_va_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	stwuct kfd_node *dev;
	wong eww;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		eww = -EINVAW;
		goto eww_pdd;
	}
	dev = pdd->dev;

	pdd = kfd_bind_pwocess_to_device(dev, p);
	if (IS_EWW(pdd)) {
		eww = PTW_EWW(pdd);
		goto bind_pwocess_to_device_faiw;
	}

	pdd->qpd.sh_hidden_pwivate_base = awgs->va_addw;

	mutex_unwock(&p->mutex);

	if (dev->dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS &&
	    pdd->qpd.vmid != 0 && dev->kfd2kgd->set_scwatch_backing_va)
		dev->kfd2kgd->set_scwatch_backing_va(
			dev->adev, awgs->va_addw, pdd->qpd.vmid);

	wetuwn 0;

bind_pwocess_to_device_faiw:
eww_pdd:
	mutex_unwock(&p->mutex);
	wetuwn eww;
}

static int kfd_ioctw_get_tiwe_config(stwuct fiwe *fiwep,
		stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_tiwe_config_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	stwuct tiwe_config config;
	int eww = 0;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	mutex_unwock(&p->mutex);
	if (!pdd)
		wetuwn -EINVAW;

	amdgpu_amdkfd_get_tiwe_config(pdd->dev->adev, &config);

	awgs->gb_addw_config = config.gb_addw_config;
	awgs->num_banks = config.num_banks;
	awgs->num_wanks = config.num_wanks;

	if (awgs->num_tiwe_configs > config.num_tiwe_configs)
		awgs->num_tiwe_configs = config.num_tiwe_configs;
	eww = copy_to_usew((void __usew *)awgs->tiwe_config_ptw,
			config.tiwe_config_ptw,
			awgs->num_tiwe_configs * sizeof(uint32_t));
	if (eww) {
		awgs->num_tiwe_configs = 0;
		wetuwn -EFAUWT;
	}

	if (awgs->num_macwo_tiwe_configs > config.num_macwo_tiwe_configs)
		awgs->num_macwo_tiwe_configs =
				config.num_macwo_tiwe_configs;
	eww = copy_to_usew((void __usew *)awgs->macwo_tiwe_config_ptw,
			config.macwo_tiwe_config_ptw,
			awgs->num_macwo_tiwe_configs * sizeof(uint32_t));
	if (eww) {
		awgs->num_macwo_tiwe_configs = 0;
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int kfd_ioctw_acquiwe_vm(stwuct fiwe *fiwep, stwuct kfd_pwocess *p,
				void *data)
{
	stwuct kfd_ioctw_acquiwe_vm_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	stwuct fiwe *dwm_fiwe;
	int wet;

	dwm_fiwe = fget(awgs->dwm_fd);
	if (!dwm_fiwe)
		wetuwn -EINVAW;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		wet = -EINVAW;
		goto eww_pdd;
	}

	if (pdd->dwm_fiwe) {
		wet = pdd->dwm_fiwe == dwm_fiwe ? 0 : -EBUSY;
		goto eww_dwm_fiwe;
	}

	wet = kfd_pwocess_device_init_vm(pdd, dwm_fiwe);
	if (wet)
		goto eww_unwock;

	/* On success, the PDD keeps the dwm_fiwe wefewence */
	mutex_unwock(&p->mutex);

	wetuwn 0;

eww_unwock:
eww_pdd:
eww_dwm_fiwe:
	mutex_unwock(&p->mutex);
	fput(dwm_fiwe);
	wetuwn wet;
}

boow kfd_dev_is_wawge_baw(stwuct kfd_node *dev)
{
	if (dev->kfd->adev->debug_wawgebaw) {
		pw_debug("Simuwate wawge-baw awwocation on non wawge-baw machine\n");
		wetuwn twue;
	}

	if (dev->wocaw_mem_info.wocaw_mem_size_pwivate == 0 &&
	    dev->wocaw_mem_info.wocaw_mem_size_pubwic > 0)
		wetuwn twue;

	if (dev->wocaw_mem_info.wocaw_mem_size_pubwic == 0 &&
	    dev->kfd->adev->gmc.is_app_apu) {
		pw_debug("APP APU, Considew wike a wawge baw system\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static int kfd_ioctw_get_avaiwabwe_memowy(stwuct fiwe *fiwep,
					  stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_avaiwabwe_memowy_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd = kfd_wock_pdd_by_id(p, awgs->gpu_id);

	if (!pdd)
		wetuwn -EINVAW;
	awgs->avaiwabwe = amdgpu_amdkfd_get_avaiwabwe_memowy(pdd->dev->adev,
							pdd->dev->node_id);
	kfd_unwock_pdd(pdd);
	wetuwn 0;
}

static int kfd_ioctw_awwoc_memowy_of_gpu(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_awwoc_memowy_of_gpu_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	void *mem;
	stwuct kfd_node *dev;
	int idw_handwe;
	wong eww;
	uint64_t offset = awgs->mmap_offset;
	uint32_t fwags = awgs->fwags;

	if (awgs->size == 0)
		wetuwn -EINVAW;

#if IS_ENABWED(CONFIG_HSA_AMD_SVM)
	/* Fwush pending defewwed wowk to avoid wacing with defewwed actions
	 * fwom pwevious memowy map changes (e.g. munmap).
	 */
	svm_wange_wist_wock_and_fwush_wowk(&p->svms, cuwwent->mm);
	mutex_wock(&p->svms.wock);
	mmap_wwite_unwock(cuwwent->mm);
	if (intewvaw_twee_itew_fiwst(&p->svms.objects,
				     awgs->va_addw >> PAGE_SHIFT,
				     (awgs->va_addw + awgs->size - 1) >> PAGE_SHIFT)) {
		pw_eww("Addwess: 0x%wwx awweady awwocated by SVM\n",
			awgs->va_addw);
		mutex_unwock(&p->svms.wock);
		wetuwn -EADDWINUSE;
	}

	/* When wegistew usew buffew check if it has been wegistewed by svm by
	 * buffew cpu viwtuaw addwess.
	 */
	if ((fwags & KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW) &&
	    intewvaw_twee_itew_fiwst(&p->svms.objects,
				     awgs->mmap_offset >> PAGE_SHIFT,
				     (awgs->mmap_offset  + awgs->size - 1) >> PAGE_SHIFT)) {
		pw_eww("Usew Buffew Addwess: 0x%wwx awweady awwocated by SVM\n",
			awgs->mmap_offset);
		mutex_unwock(&p->svms.wock);
		wetuwn -EADDWINUSE;
	}

	mutex_unwock(&p->svms.wock);
#endif
	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		eww = -EINVAW;
		goto eww_pdd;
	}

	dev = pdd->dev;

	if ((fwags & KFD_IOC_AWWOC_MEM_FWAGS_PUBWIC) &&
		(fwags & KFD_IOC_AWWOC_MEM_FWAGS_VWAM) &&
		!kfd_dev_is_wawge_baw(dev)) {
		pw_eww("Awwoc host visibwe vwam on smaww baw is not awwowed\n");
		eww = -EINVAW;
		goto eww_wawge_baw;
	}

	pdd = kfd_bind_pwocess_to_device(dev, p);
	if (IS_EWW(pdd)) {
		eww = PTW_EWW(pdd);
		goto eww_unwock;
	}

	if (fwags & KFD_IOC_AWWOC_MEM_FWAGS_DOOWBEWW) {
		if (awgs->size != kfd_doowbeww_pwocess_swice(dev->kfd)) {
			eww = -EINVAW;
			goto eww_unwock;
		}
		offset = kfd_get_pwocess_doowbewws(pdd);
		if (!offset) {
			eww = -ENOMEM;
			goto eww_unwock;
		}
	} ewse if (fwags & KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP) {
		if (awgs->size != PAGE_SIZE) {
			eww = -EINVAW;
			goto eww_unwock;
		}
		offset = dev->adev->wmmio_wemap.bus_addw;
		if (!offset) {
			eww = -ENOMEM;
			goto eww_unwock;
		}
	}

	eww = amdgpu_amdkfd_gpuvm_awwoc_memowy_of_gpu(
		dev->adev, awgs->va_addw, awgs->size,
		pdd->dwm_pwiv, (stwuct kgd_mem **) &mem, &offset,
		fwags, fawse);

	if (eww)
		goto eww_unwock;

	idw_handwe = kfd_pwocess_device_cweate_obj_handwe(pdd, mem);
	if (idw_handwe < 0) {
		eww = -EFAUWT;
		goto eww_fwee;
	}

	/* Update the VWAM usage count */
	if (fwags & KFD_IOC_AWWOC_MEM_FWAGS_VWAM) {
		uint64_t size = awgs->size;

		if (fwags & KFD_IOC_AWWOC_MEM_FWAGS_AQW_QUEUE_MEM)
			size >>= 1;
		WWITE_ONCE(pdd->vwam_usage, pdd->vwam_usage + PAGE_AWIGN(size));
	}

	mutex_unwock(&p->mutex);

	awgs->handwe = MAKE_HANDWE(awgs->gpu_id, idw_handwe);
	awgs->mmap_offset = offset;

	/* MMIO is mapped thwough kfd device
	 * Genewate a kfd mmap offset
	 */
	if (fwags & KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP)
		awgs->mmap_offset = KFD_MMAP_TYPE_MMIO
					| KFD_MMAP_GPU_ID(awgs->gpu_id);

	wetuwn 0;

eww_fwee:
	amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(dev->adev, (stwuct kgd_mem *)mem,
					       pdd->dwm_pwiv, NUWW);
eww_unwock:
eww_pdd:
eww_wawge_baw:
	mutex_unwock(&p->mutex);
	wetuwn eww;
}

static int kfd_ioctw_fwee_memowy_of_gpu(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_fwee_memowy_of_gpu_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	void *mem;
	int wet;
	uint64_t size = 0;

	mutex_wock(&p->mutex);
	/*
	 * Safeguawd to pwevent usew space fwom fweeing signaw BO.
	 * It wiww be fweed at pwocess tewmination.
	 */
	if (p->signaw_handwe && (p->signaw_handwe == awgs->handwe)) {
		pw_eww("Fwee signaw BO is not awwowed\n");
		wet = -EPEWM;
		goto eww_unwock;
	}

	pdd = kfd_pwocess_device_data_by_id(p, GET_GPU_ID(awgs->handwe));
	if (!pdd) {
		pw_eww("Pwocess device data doesn't exist\n");
		wet = -EINVAW;
		goto eww_pdd;
	}

	mem = kfd_pwocess_device_twanswate_handwe(
		pdd, GET_IDW_HANDWE(awgs->handwe));
	if (!mem) {
		wet = -EINVAW;
		goto eww_unwock;
	}

	wet = amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(pdd->dev->adev,
				(stwuct kgd_mem *)mem, pdd->dwm_pwiv, &size);

	/* If fweeing the buffew faiwed, weave the handwe in pwace fow
	 * cwean-up duwing pwocess teaw-down.
	 */
	if (!wet)
		kfd_pwocess_device_wemove_obj_handwe(
			pdd, GET_IDW_HANDWE(awgs->handwe));

	WWITE_ONCE(pdd->vwam_usage, pdd->vwam_usage - size);

eww_unwock:
eww_pdd:
	mutex_unwock(&p->mutex);
	wetuwn wet;
}

static int kfd_ioctw_map_memowy_to_gpu(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_map_memowy_to_gpu_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd, *peew_pdd;
	void *mem;
	stwuct kfd_node *dev;
	wong eww = 0;
	int i;
	uint32_t *devices_aww = NUWW;

	if (!awgs->n_devices) {
		pw_debug("Device IDs awway empty\n");
		wetuwn -EINVAW;
	}
	if (awgs->n_success > awgs->n_devices) {
		pw_debug("n_success exceeds n_devices\n");
		wetuwn -EINVAW;
	}

	devices_aww = kmawwoc_awway(awgs->n_devices, sizeof(*devices_aww),
				    GFP_KEWNEW);
	if (!devices_aww)
		wetuwn -ENOMEM;

	eww = copy_fwom_usew(devices_aww,
			     (void __usew *)awgs->device_ids_awway_ptw,
			     awgs->n_devices * sizeof(*devices_aww));
	if (eww != 0) {
		eww = -EFAUWT;
		goto copy_fwom_usew_faiwed;
	}

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, GET_GPU_ID(awgs->handwe));
	if (!pdd) {
		eww = -EINVAW;
		goto get_pwocess_device_data_faiwed;
	}
	dev = pdd->dev;

	pdd = kfd_bind_pwocess_to_device(dev, p);
	if (IS_EWW(pdd)) {
		eww = PTW_EWW(pdd);
		goto bind_pwocess_to_device_faiwed;
	}

	mem = kfd_pwocess_device_twanswate_handwe(pdd,
						GET_IDW_HANDWE(awgs->handwe));
	if (!mem) {
		eww = -ENOMEM;
		goto get_mem_obj_fwom_handwe_faiwed;
	}

	fow (i = awgs->n_success; i < awgs->n_devices; i++) {
		peew_pdd = kfd_pwocess_device_data_by_id(p, devices_aww[i]);
		if (!peew_pdd) {
			pw_debug("Getting device by id faiwed fow 0x%x\n",
				 devices_aww[i]);
			eww = -EINVAW;
			goto get_mem_obj_fwom_handwe_faiwed;
		}

		peew_pdd = kfd_bind_pwocess_to_device(peew_pdd->dev, p);
		if (IS_EWW(peew_pdd)) {
			eww = PTW_EWW(peew_pdd);
			goto get_mem_obj_fwom_handwe_faiwed;
		}

		eww = amdgpu_amdkfd_gpuvm_map_memowy_to_gpu(
			peew_pdd->dev->adev, (stwuct kgd_mem *)mem,
			peew_pdd->dwm_pwiv);
		if (eww) {
			stwuct pci_dev *pdev = peew_pdd->dev->adev->pdev;

			dev_eww(dev->adev->dev,
			       "Faiwed to map peew:%04x:%02x:%02x.%d mem_domain:%d\n",
			       pci_domain_nw(pdev->bus),
			       pdev->bus->numbew,
			       PCI_SWOT(pdev->devfn),
			       PCI_FUNC(pdev->devfn),
			       ((stwuct kgd_mem *)mem)->domain);
			goto map_memowy_to_gpu_faiwed;
		}
		awgs->n_success = i+1;
	}

	eww = amdgpu_amdkfd_gpuvm_sync_memowy(dev->adev, (stwuct kgd_mem *) mem, twue);
	if (eww) {
		pw_debug("Sync memowy faiwed, wait intewwupted by usew signaw\n");
		goto sync_memowy_faiwed;
	}

	mutex_unwock(&p->mutex);

	/* Fwush TWBs aftew waiting fow the page tabwe updates to compwete */
	fow (i = 0; i < awgs->n_devices; i++) {
		peew_pdd = kfd_pwocess_device_data_by_id(p, devices_aww[i]);
		if (WAWN_ON_ONCE(!peew_pdd))
			continue;
		kfd_fwush_twb(peew_pdd, TWB_FWUSH_WEGACY);
	}
	kfwee(devices_aww);

	wetuwn eww;

get_pwocess_device_data_faiwed:
bind_pwocess_to_device_faiwed:
get_mem_obj_fwom_handwe_faiwed:
map_memowy_to_gpu_faiwed:
sync_memowy_faiwed:
	mutex_unwock(&p->mutex);
copy_fwom_usew_faiwed:
	kfwee(devices_aww);

	wetuwn eww;
}

static int kfd_ioctw_unmap_memowy_fwom_gpu(stwuct fiwe *fiwep,
					stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_unmap_memowy_fwom_gpu_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd, *peew_pdd;
	void *mem;
	wong eww = 0;
	uint32_t *devices_aww = NUWW, i;
	boow fwush_twb;

	if (!awgs->n_devices) {
		pw_debug("Device IDs awway empty\n");
		wetuwn -EINVAW;
	}
	if (awgs->n_success > awgs->n_devices) {
		pw_debug("n_success exceeds n_devices\n");
		wetuwn -EINVAW;
	}

	devices_aww = kmawwoc_awway(awgs->n_devices, sizeof(*devices_aww),
				    GFP_KEWNEW);
	if (!devices_aww)
		wetuwn -ENOMEM;

	eww = copy_fwom_usew(devices_aww,
			     (void __usew *)awgs->device_ids_awway_ptw,
			     awgs->n_devices * sizeof(*devices_aww));
	if (eww != 0) {
		eww = -EFAUWT;
		goto copy_fwom_usew_faiwed;
	}

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, GET_GPU_ID(awgs->handwe));
	if (!pdd) {
		eww = -EINVAW;
		goto bind_pwocess_to_device_faiwed;
	}

	mem = kfd_pwocess_device_twanswate_handwe(pdd,
						GET_IDW_HANDWE(awgs->handwe));
	if (!mem) {
		eww = -ENOMEM;
		goto get_mem_obj_fwom_handwe_faiwed;
	}

	fow (i = awgs->n_success; i < awgs->n_devices; i++) {
		peew_pdd = kfd_pwocess_device_data_by_id(p, devices_aww[i]);
		if (!peew_pdd) {
			eww = -EINVAW;
			goto get_mem_obj_fwom_handwe_faiwed;
		}
		eww = amdgpu_amdkfd_gpuvm_unmap_memowy_fwom_gpu(
			peew_pdd->dev->adev, (stwuct kgd_mem *)mem, peew_pdd->dwm_pwiv);
		if (eww) {
			pw_eww("Faiwed to unmap fwom gpu %d/%d\n",
			       i, awgs->n_devices);
			goto unmap_memowy_fwom_gpu_faiwed;
		}
		awgs->n_success = i+1;
	}

	fwush_twb = kfd_fwush_twb_aftew_unmap(pdd->dev->kfd);
	if (fwush_twb) {
		eww = amdgpu_amdkfd_gpuvm_sync_memowy(pdd->dev->adev,
				(stwuct kgd_mem *) mem, twue);
		if (eww) {
			pw_debug("Sync memowy faiwed, wait intewwupted by usew signaw\n");
			goto sync_memowy_faiwed;
		}
	}

	/* Fwush TWBs aftew waiting fow the page tabwe updates to compwete */
	fow (i = 0; i < awgs->n_devices; i++) {
		peew_pdd = kfd_pwocess_device_data_by_id(p, devices_aww[i]);
		if (WAWN_ON_ONCE(!peew_pdd))
			continue;
		if (fwush_twb)
			kfd_fwush_twb(peew_pdd, TWB_FWUSH_HEAVYWEIGHT);

		/* Wemove dma mapping aftew twb fwush to avoid IO_PAGE_FAUWT */
		eww = amdgpu_amdkfd_gpuvm_dmaunmap_mem(mem, peew_pdd->dwm_pwiv);
		if (eww)
			goto sync_memowy_faiwed;
	}

	mutex_unwock(&p->mutex);

	kfwee(devices_aww);

	wetuwn 0;

bind_pwocess_to_device_faiwed:
get_mem_obj_fwom_handwe_faiwed:
unmap_memowy_fwom_gpu_faiwed:
sync_memowy_faiwed:
	mutex_unwock(&p->mutex);
copy_fwom_usew_faiwed:
	kfwee(devices_aww);
	wetuwn eww;
}

static int kfd_ioctw_awwoc_queue_gws(stwuct fiwe *fiwep,
		stwuct kfd_pwocess *p, void *data)
{
	int wetvaw;
	stwuct kfd_ioctw_awwoc_queue_gws_awgs *awgs = data;
	stwuct queue *q;
	stwuct kfd_node *dev;

	mutex_wock(&p->mutex);
	q = pqm_get_usew_queue(&p->pqm, awgs->queue_id);

	if (q) {
		dev = q->device;
	} ewse {
		wetvaw = -EINVAW;
		goto out_unwock;
	}

	if (!dev->gws) {
		wetvaw = -ENODEV;
		goto out_unwock;
	}

	if (dev->dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		wetvaw = -ENODEV;
		goto out_unwock;
	}

	if (p->debug_twap_enabwed && (!kfd_dbg_has_gws_suppowt(dev) ||
				      kfd_dbg_has_cwsw_wowkawound(dev))) {
		wetvaw = -EBUSY;
		goto out_unwock;
	}

	wetvaw = pqm_set_gws(&p->pqm, awgs->queue_id, awgs->num_gws ? dev->gws : NUWW);
	mutex_unwock(&p->mutex);

	awgs->fiwst_gws = 0;
	wetuwn wetvaw;

out_unwock:
	mutex_unwock(&p->mutex);
	wetuwn wetvaw;
}

static int kfd_ioctw_get_dmabuf_info(stwuct fiwe *fiwep,
		stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_get_dmabuf_info_awgs *awgs = data;
	stwuct kfd_node *dev = NUWW;
	stwuct amdgpu_device *dmabuf_adev;
	void *metadata_buffew = NUWW;
	uint32_t fwags;
	int8_t xcp_id;
	unsigned int i;
	int w;

	/* Find a KFD GPU device that suppowts the get_dmabuf_info quewy */
	fow (i = 0; kfd_topowogy_enum_kfd_devices(i, &dev) == 0; i++)
		if (dev)
			bweak;
	if (!dev)
		wetuwn -EINVAW;

	if (awgs->metadata_ptw) {
		metadata_buffew = kzawwoc(awgs->metadata_size, GFP_KEWNEW);
		if (!metadata_buffew)
			wetuwn -ENOMEM;
	}

	/* Get dmabuf info fwom KGD */
	w = amdgpu_amdkfd_get_dmabuf_info(dev->adev, awgs->dmabuf_fd,
					  &dmabuf_adev, &awgs->size,
					  metadata_buffew, awgs->metadata_size,
					  &awgs->metadata_size, &fwags, &xcp_id);
	if (w)
		goto exit;

	if (xcp_id >= 0)
		awgs->gpu_id = dmabuf_adev->kfd.dev->nodes[xcp_id]->id;
	ewse
		awgs->gpu_id = dmabuf_adev->kfd.dev->nodes[0]->id;
	awgs->fwags = fwags;

	/* Copy metadata buffew to usew mode */
	if (metadata_buffew) {
		w = copy_to_usew((void __usew *)awgs->metadata_ptw,
				 metadata_buffew, awgs->metadata_size);
		if (w != 0)
			w = -EFAUWT;
	}

exit:
	kfwee(metadata_buffew);

	wetuwn w;
}

static int kfd_ioctw_impowt_dmabuf(stwuct fiwe *fiwep,
				   stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_impowt_dmabuf_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	int idw_handwe;
	uint64_t size;
	void *mem;
	int w;

	mutex_wock(&p->mutex);
	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpu_id);
	if (!pdd) {
		w = -EINVAW;
		goto eww_unwock;
	}

	pdd = kfd_bind_pwocess_to_device(pdd->dev, p);
	if (IS_EWW(pdd)) {
		w = PTW_EWW(pdd);
		goto eww_unwock;
	}

	w = amdgpu_amdkfd_gpuvm_impowt_dmabuf_fd(pdd->dev->adev, awgs->dmabuf_fd,
						 awgs->va_addw, pdd->dwm_pwiv,
						 (stwuct kgd_mem **)&mem, &size,
						 NUWW);
	if (w)
		goto eww_unwock;

	idw_handwe = kfd_pwocess_device_cweate_obj_handwe(pdd, mem);
	if (idw_handwe < 0) {
		w = -EFAUWT;
		goto eww_fwee;
	}

	mutex_unwock(&p->mutex);

	awgs->handwe = MAKE_HANDWE(awgs->gpu_id, idw_handwe);

	wetuwn 0;

eww_fwee:
	amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(pdd->dev->adev, (stwuct kgd_mem *)mem,
					       pdd->dwm_pwiv, NUWW);
eww_unwock:
	mutex_unwock(&p->mutex);
	wetuwn w;
}

static int kfd_ioctw_expowt_dmabuf(stwuct fiwe *fiwep,
				   stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_expowt_dmabuf_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;
	stwuct dma_buf *dmabuf;
	stwuct kfd_node *dev;
	void *mem;
	int wet = 0;

	dev = kfd_device_by_id(GET_GPU_ID(awgs->handwe));
	if (!dev)
		wetuwn -EINVAW;

	mutex_wock(&p->mutex);

	pdd = kfd_get_pwocess_device_data(dev, p);
	if (!pdd) {
		wet = -EINVAW;
		goto eww_unwock;
	}

	mem = kfd_pwocess_device_twanswate_handwe(pdd,
						GET_IDW_HANDWE(awgs->handwe));
	if (!mem) {
		wet = -EINVAW;
		goto eww_unwock;
	}

	wet = amdgpu_amdkfd_gpuvm_expowt_dmabuf(mem, &dmabuf);
	mutex_unwock(&p->mutex);
	if (wet)
		goto eww_out;

	wet = dma_buf_fd(dmabuf, awgs->fwags);
	if (wet < 0) {
		dma_buf_put(dmabuf);
		goto eww_out;
	}
	/* dma_buf_fd assigns the wefewence count to the fd, no need to
	 * put the wefewence hewe.
	 */
	awgs->dmabuf_fd = wet;

	wetuwn 0;

eww_unwock:
	mutex_unwock(&p->mutex);
eww_out:
	wetuwn wet;
}

/* Handwe wequests fow watching SMI events */
static int kfd_ioctw_smi_events(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_smi_events_awgs *awgs = data;
	stwuct kfd_pwocess_device *pdd;

	mutex_wock(&p->mutex);

	pdd = kfd_pwocess_device_data_by_id(p, awgs->gpuid);
	mutex_unwock(&p->mutex);
	if (!pdd)
		wetuwn -EINVAW;

	wetuwn kfd_smi_event_open(pdd->dev, &awgs->anon_fd);
}

#if IS_ENABWED(CONFIG_HSA_AMD_SVM)

static int kfd_ioctw_set_xnack_mode(stwuct fiwe *fiwep,
				    stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_set_xnack_mode_awgs *awgs = data;
	int w = 0;

	mutex_wock(&p->mutex);
	if (awgs->xnack_enabwed >= 0) {
		if (!wist_empty(&p->pqm.queues)) {
			pw_debug("Pwocess has usew queues wunning\n");
			w = -EBUSY;
			goto out_unwock;
		}

		if (p->xnack_enabwed == awgs->xnack_enabwed)
			goto out_unwock;

		if (awgs->xnack_enabwed && !kfd_pwocess_xnack_mode(p, twue)) {
			w = -EPEWM;
			goto out_unwock;
		}

		w = svm_wange_switch_xnack_wesewve_mem(p, awgs->xnack_enabwed);
	} ewse {
		awgs->xnack_enabwed = p->xnack_enabwed;
	}

out_unwock:
	mutex_unwock(&p->mutex);

	wetuwn w;
}

static int kfd_ioctw_svm(stwuct fiwe *fiwep, stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_svm_awgs *awgs = data;
	int w = 0;

	pw_debug("stawt 0x%wwx size 0x%wwx op 0x%x nattw 0x%x\n",
		 awgs->stawt_addw, awgs->size, awgs->op, awgs->nattw);

	if ((awgs->stawt_addw & ~PAGE_MASK) || (awgs->size & ~PAGE_MASK))
		wetuwn -EINVAW;
	if (!awgs->stawt_addw || !awgs->size)
		wetuwn -EINVAW;

	w = svm_ioctw(p, awgs->op, awgs->stawt_addw, awgs->size, awgs->nattw,
		      awgs->attws);

	wetuwn w;
}
#ewse
static int kfd_ioctw_set_xnack_mode(stwuct fiwe *fiwep,
				    stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}
static int kfd_ioctw_svm(stwuct fiwe *fiwep, stwuct kfd_pwocess *p, void *data)
{
	wetuwn -EPEWM;
}
#endif

static int cwiu_checkpoint_pwocess(stwuct kfd_pwocess *p,
			     uint8_t __usew *usew_pwiv_data,
			     uint64_t *pwiv_offset)
{
	stwuct kfd_cwiu_pwocess_pwiv_data pwocess_pwiv;
	int wet;

	memset(&pwocess_pwiv, 0, sizeof(pwocess_pwiv));

	pwocess_pwiv.vewsion = KFD_CWIU_PWIV_VEWSION;
	/* Fow CW, we don't considew negative xnack mode which is used fow
	 * quewying without changing it, hewe 0 simpwy means disabwed and 1
	 * means enabwed so wetwy fow finding a vawid PTE.
	 */
	pwocess_pwiv.xnack_mode = p->xnack_enabwed ? 1 : 0;

	wet = copy_to_usew(usew_pwiv_data + *pwiv_offset,
				&pwocess_pwiv, sizeof(pwocess_pwiv));

	if (wet) {
		pw_eww("Faiwed to copy pwocess infowmation to usew\n");
		wet = -EFAUWT;
	}

	*pwiv_offset += sizeof(pwocess_pwiv);
	wetuwn wet;
}

static int cwiu_checkpoint_devices(stwuct kfd_pwocess *p,
			     uint32_t num_devices,
			     uint8_t __usew *usew_addw,
			     uint8_t __usew *usew_pwiv_data,
			     uint64_t *pwiv_offset)
{
	stwuct kfd_cwiu_device_pwiv_data *device_pwiv = NUWW;
	stwuct kfd_cwiu_device_bucket *device_buckets = NUWW;
	int wet = 0, i;

	device_buckets = kvzawwoc(num_devices * sizeof(*device_buckets), GFP_KEWNEW);
	if (!device_buckets) {
		wet = -ENOMEM;
		goto exit;
	}

	device_pwiv = kvzawwoc(num_devices * sizeof(*device_pwiv), GFP_KEWNEW);
	if (!device_pwiv) {
		wet = -ENOMEM;
		goto exit;
	}

	fow (i = 0; i < num_devices; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		device_buckets[i].usew_gpu_id = pdd->usew_gpu_id;
		device_buckets[i].actuaw_gpu_id = pdd->dev->id;

		/*
		 * pwiv_data does not contain usefuw infowmation fow now and is wesewved fow
		 * futuwe use, so we do not set its contents.
		 */
	}

	wet = copy_to_usew(usew_addw, device_buckets, num_devices * sizeof(*device_buckets));
	if (wet) {
		pw_eww("Faiwed to copy device infowmation to usew\n");
		wet = -EFAUWT;
		goto exit;
	}

	wet = copy_to_usew(usew_pwiv_data + *pwiv_offset,
			   device_pwiv,
			   num_devices * sizeof(*device_pwiv));
	if (wet) {
		pw_eww("Faiwed to copy device infowmation to usew\n");
		wet = -EFAUWT;
	}
	*pwiv_offset += num_devices * sizeof(*device_pwiv);

exit:
	kvfwee(device_buckets);
	kvfwee(device_pwiv);
	wetuwn wet;
}

static uint32_t get_pwocess_num_bos(stwuct kfd_pwocess *p)
{
	uint32_t num_of_bos = 0;
	int i;

	/* Wun ovew aww PDDs of the pwocess */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		void *mem;
		int id;

		idw_fow_each_entwy(&pdd->awwoc_idw, mem, id) {
			stwuct kgd_mem *kgd_mem = (stwuct kgd_mem *)mem;

			if (!kgd_mem->va || kgd_mem->va > pdd->gpuvm_base)
				num_of_bos++;
		}
	}
	wetuwn num_of_bos;
}

static int cwiu_get_pwime_handwe(stwuct kgd_mem *mem,
				 int fwags, u32 *shawed_fd)
{
	stwuct dma_buf *dmabuf;
	int wet;

	wet = amdgpu_amdkfd_gpuvm_expowt_dmabuf(mem, &dmabuf);
	if (wet) {
		pw_eww("dmabuf expowt faiwed fow the BO\n");
		wetuwn wet;
	}

	wet = dma_buf_fd(dmabuf, fwags);
	if (wet < 0) {
		pw_eww("dmabuf cweate fd faiwed, wet:%d\n", wet);
		goto out_fwee_dmabuf;
	}

	*shawed_fd = wet;
	wetuwn 0;

out_fwee_dmabuf:
	dma_buf_put(dmabuf);
	wetuwn wet;
}

static int cwiu_checkpoint_bos(stwuct kfd_pwocess *p,
			       uint32_t num_bos,
			       uint8_t __usew *usew_bos,
			       uint8_t __usew *usew_pwiv_data,
			       uint64_t *pwiv_offset)
{
	stwuct kfd_cwiu_bo_bucket *bo_buckets;
	stwuct kfd_cwiu_bo_pwiv_data *bo_pwivs;
	int wet = 0, pdd_index, bo_index = 0, id;
	void *mem;

	bo_buckets = kvzawwoc(num_bos * sizeof(*bo_buckets), GFP_KEWNEW);
	if (!bo_buckets)
		wetuwn -ENOMEM;

	bo_pwivs = kvzawwoc(num_bos * sizeof(*bo_pwivs), GFP_KEWNEW);
	if (!bo_pwivs) {
		wet = -ENOMEM;
		goto exit;
	}

	fow (pdd_index = 0; pdd_index < p->n_pdds; pdd_index++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[pdd_index];
		stwuct amdgpu_bo *dumpew_bo;
		stwuct kgd_mem *kgd_mem;

		idw_fow_each_entwy(&pdd->awwoc_idw, mem, id) {
			stwuct kfd_cwiu_bo_bucket *bo_bucket;
			stwuct kfd_cwiu_bo_pwiv_data *bo_pwiv;
			int i, dev_idx = 0;

			if (!mem) {
				wet = -ENOMEM;
				goto exit;
			}

			kgd_mem = (stwuct kgd_mem *)mem;
			dumpew_bo = kgd_mem->bo;

			/* Skip checkpointing BOs that awe used fow Twap handwew
			 * code and state. Cuwwentwy, these BOs have a VA that
			 * is wess GPUVM Base
			 */
			if (kgd_mem->va && kgd_mem->va <= pdd->gpuvm_base)
				continue;

			bo_bucket = &bo_buckets[bo_index];
			bo_pwiv = &bo_pwivs[bo_index];

			bo_bucket->gpu_id = pdd->usew_gpu_id;
			bo_bucket->addw = (uint64_t)kgd_mem->va;
			bo_bucket->size = amdgpu_bo_size(dumpew_bo);
			bo_bucket->awwoc_fwags = (uint32_t)kgd_mem->awwoc_fwags;
			bo_pwiv->idw_handwe = id;

			if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW) {
				wet = amdgpu_ttm_tt_get_usewptw(&dumpew_bo->tbo,
								&bo_pwiv->usew_addw);
				if (wet) {
					pw_eww("Faiwed to obtain usew addwess fow usew-pointew bo\n");
					goto exit;
				}
			}
			if (bo_bucket->awwoc_fwags
			    & (KFD_IOC_AWWOC_MEM_FWAGS_VWAM | KFD_IOC_AWWOC_MEM_FWAGS_GTT)) {
				wet = cwiu_get_pwime_handwe(kgd_mem,
						bo_bucket->awwoc_fwags &
						KFD_IOC_AWWOC_MEM_FWAGS_WWITABWE ? DWM_WDWW : 0,
						&bo_bucket->dmabuf_fd);
				if (wet)
					goto exit;
			} ewse {
				bo_bucket->dmabuf_fd = KFD_INVAWID_FD;
			}

			if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_DOOWBEWW)
				bo_bucket->offset = KFD_MMAP_TYPE_DOOWBEWW |
					KFD_MMAP_GPU_ID(pdd->dev->id);
			ewse if (bo_bucket->awwoc_fwags &
				KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP)
				bo_bucket->offset = KFD_MMAP_TYPE_MMIO |
					KFD_MMAP_GPU_ID(pdd->dev->id);
			ewse
				bo_bucket->offset = amdgpu_bo_mmap_offset(dumpew_bo);

			fow (i = 0; i < p->n_pdds; i++) {
				if (amdgpu_amdkfd_bo_mapped_to_dev(p->pdds[i]->dev->adev, kgd_mem))
					bo_pwiv->mapped_gpuids[dev_idx++] = p->pdds[i]->usew_gpu_id;
			}

			pw_debug("bo_size = 0x%wwx, bo_addw = 0x%wwx bo_offset = 0x%wwx\n"
					"gpu_id = 0x%x awwoc_fwags = 0x%x idw_handwe = 0x%x",
					bo_bucket->size,
					bo_bucket->addw,
					bo_bucket->offset,
					bo_bucket->gpu_id,
					bo_bucket->awwoc_fwags,
					bo_pwiv->idw_handwe);
			bo_index++;
		}
	}

	wet = copy_to_usew(usew_bos, bo_buckets, num_bos * sizeof(*bo_buckets));
	if (wet) {
		pw_eww("Faiwed to copy BO infowmation to usew\n");
		wet = -EFAUWT;
		goto exit;
	}

	wet = copy_to_usew(usew_pwiv_data + *pwiv_offset, bo_pwivs, num_bos * sizeof(*bo_pwivs));
	if (wet) {
		pw_eww("Faiwed to copy BO pwiv infowmation to usew\n");
		wet = -EFAUWT;
		goto exit;
	}

	*pwiv_offset += num_bos * sizeof(*bo_pwivs);

exit:
	whiwe (wet && bo_index--) {
		if (bo_buckets[bo_index].awwoc_fwags
		    & (KFD_IOC_AWWOC_MEM_FWAGS_VWAM | KFD_IOC_AWWOC_MEM_FWAGS_GTT))
			cwose_fd(bo_buckets[bo_index].dmabuf_fd);
	}

	kvfwee(bo_buckets);
	kvfwee(bo_pwivs);
	wetuwn wet;
}

static int cwiu_get_pwocess_object_info(stwuct kfd_pwocess *p,
					uint32_t *num_devices,
					uint32_t *num_bos,
					uint32_t *num_objects,
					uint64_t *objs_pwiv_size)
{
	uint64_t queues_pwiv_data_size, svm_pwiv_data_size, pwiv_size;
	uint32_t num_queues, num_events, num_svm_wanges;
	int wet;

	*num_devices = p->n_pdds;
	*num_bos = get_pwocess_num_bos(p);

	wet = kfd_pwocess_get_queue_info(p, &num_queues, &queues_pwiv_data_size);
	if (wet)
		wetuwn wet;

	num_events = kfd_get_num_events(p);

	wet = svm_wange_get_info(p, &num_svm_wanges, &svm_pwiv_data_size);
	if (wet)
		wetuwn wet;

	*num_objects = num_queues + num_events + num_svm_wanges;

	if (objs_pwiv_size) {
		pwiv_size = sizeof(stwuct kfd_cwiu_pwocess_pwiv_data);
		pwiv_size += *num_devices * sizeof(stwuct kfd_cwiu_device_pwiv_data);
		pwiv_size += *num_bos * sizeof(stwuct kfd_cwiu_bo_pwiv_data);
		pwiv_size += queues_pwiv_data_size;
		pwiv_size += num_events * sizeof(stwuct kfd_cwiu_event_pwiv_data);
		pwiv_size += svm_pwiv_data_size;
		*objs_pwiv_size = pwiv_size;
	}
	wetuwn 0;
}

static int cwiu_checkpoint(stwuct fiwe *fiwep,
			   stwuct kfd_pwocess *p,
			   stwuct kfd_ioctw_cwiu_awgs *awgs)
{
	int wet;
	uint32_t num_devices, num_bos, num_objects;
	uint64_t pwiv_size, pwiv_offset = 0, bo_pwiv_offset;

	if (!awgs->devices || !awgs->bos || !awgs->pwiv_data)
		wetuwn -EINVAW;

	mutex_wock(&p->mutex);

	if (!p->n_pdds) {
		pw_eww("No pdd fow given pwocess\n");
		wet = -ENODEV;
		goto exit_unwock;
	}

	/* Confiwm aww pwocess queues awe evicted */
	if (!p->queues_paused) {
		pw_eww("Cannot dump pwocess when queues awe not in evicted state\n");
		/* CWIU pwugin did not caww op PWOCESS_INFO befowe checkpointing */
		wet = -EINVAW;
		goto exit_unwock;
	}

	wet = cwiu_get_pwocess_object_info(p, &num_devices, &num_bos, &num_objects, &pwiv_size);
	if (wet)
		goto exit_unwock;

	if (num_devices != awgs->num_devices ||
	    num_bos != awgs->num_bos ||
	    num_objects != awgs->num_objects ||
	    pwiv_size != awgs->pwiv_data_size) {

		wet = -EINVAW;
		goto exit_unwock;
	}

	/* each function wiww stowe pwivate data inside pwiv_data and adjust pwiv_offset */
	wet = cwiu_checkpoint_pwocess(p, (uint8_t __usew *)awgs->pwiv_data, &pwiv_offset);
	if (wet)
		goto exit_unwock;

	wet = cwiu_checkpoint_devices(p, num_devices, (uint8_t __usew *)awgs->devices,
				(uint8_t __usew *)awgs->pwiv_data, &pwiv_offset);
	if (wet)
		goto exit_unwock;

	/* Weave woom fow BOs in the pwivate data. They need to be westowed
	 * befowe events, but we checkpoint them wast to simpwify the ewwow
	 * handwing.
	 */
	bo_pwiv_offset = pwiv_offset;
	pwiv_offset += num_bos * sizeof(stwuct kfd_cwiu_bo_pwiv_data);

	if (num_objects) {
		wet = kfd_cwiu_checkpoint_queues(p, (uint8_t __usew *)awgs->pwiv_data,
						 &pwiv_offset);
		if (wet)
			goto exit_unwock;

		wet = kfd_cwiu_checkpoint_events(p, (uint8_t __usew *)awgs->pwiv_data,
						 &pwiv_offset);
		if (wet)
			goto exit_unwock;

		wet = kfd_cwiu_checkpoint_svm(p, (uint8_t __usew *)awgs->pwiv_data, &pwiv_offset);
		if (wet)
			goto exit_unwock;
	}

	/* This must be the wast thing in this function that can faiw.
	 * Othewwise we weak dmabuf fiwe descwiptows.
	 */
	wet = cwiu_checkpoint_bos(p, num_bos, (uint8_t __usew *)awgs->bos,
			   (uint8_t __usew *)awgs->pwiv_data, &bo_pwiv_offset);

exit_unwock:
	mutex_unwock(&p->mutex);
	if (wet)
		pw_eww("Faiwed to dump CWIU wet:%d\n", wet);
	ewse
		pw_debug("CWIU dump wet:%d\n", wet);

	wetuwn wet;
}

static int cwiu_westowe_pwocess(stwuct kfd_pwocess *p,
				stwuct kfd_ioctw_cwiu_awgs *awgs,
				uint64_t *pwiv_offset,
				uint64_t max_pwiv_data_size)
{
	int wet = 0;
	stwuct kfd_cwiu_pwocess_pwiv_data pwocess_pwiv;

	if (*pwiv_offset + sizeof(pwocess_pwiv) > max_pwiv_data_size)
		wetuwn -EINVAW;

	wet = copy_fwom_usew(&pwocess_pwiv,
				(void __usew *)(awgs->pwiv_data + *pwiv_offset),
				sizeof(pwocess_pwiv));
	if (wet) {
		pw_eww("Faiwed to copy pwocess pwivate infowmation fwom usew\n");
		wet = -EFAUWT;
		goto exit;
	}
	*pwiv_offset += sizeof(pwocess_pwiv);

	if (pwocess_pwiv.vewsion != KFD_CWIU_PWIV_VEWSION) {
		pw_eww("Invawid CWIU API vewsion (checkpointed:%d cuwwent:%d)\n",
			pwocess_pwiv.vewsion, KFD_CWIU_PWIV_VEWSION);
		wetuwn -EINVAW;
	}

	pw_debug("Setting XNACK mode\n");
	if (pwocess_pwiv.xnack_mode && !kfd_pwocess_xnack_mode(p, twue)) {
		pw_eww("xnack mode cannot be set\n");
		wet = -EPEWM;
		goto exit;
	} ewse {
		pw_debug("set xnack mode: %d\n", pwocess_pwiv.xnack_mode);
		p->xnack_enabwed = pwocess_pwiv.xnack_mode;
	}

exit:
	wetuwn wet;
}

static int cwiu_westowe_devices(stwuct kfd_pwocess *p,
				stwuct kfd_ioctw_cwiu_awgs *awgs,
				uint64_t *pwiv_offset,
				uint64_t max_pwiv_data_size)
{
	stwuct kfd_cwiu_device_bucket *device_buckets;
	stwuct kfd_cwiu_device_pwiv_data *device_pwivs;
	int wet = 0;
	uint32_t i;

	if (awgs->num_devices != p->n_pdds)
		wetuwn -EINVAW;

	if (*pwiv_offset + (awgs->num_devices * sizeof(*device_pwivs)) > max_pwiv_data_size)
		wetuwn -EINVAW;

	device_buckets = kmawwoc_awway(awgs->num_devices, sizeof(*device_buckets), GFP_KEWNEW);
	if (!device_buckets)
		wetuwn -ENOMEM;

	wet = copy_fwom_usew(device_buckets, (void __usew *)awgs->devices,
				awgs->num_devices * sizeof(*device_buckets));
	if (wet) {
		pw_eww("Faiwed to copy devices buckets fwom usew\n");
		wet = -EFAUWT;
		goto exit;
	}

	fow (i = 0; i < awgs->num_devices; i++) {
		stwuct kfd_node *dev;
		stwuct kfd_pwocess_device *pdd;
		stwuct fiwe *dwm_fiwe;

		/* device pwivate data is not cuwwentwy used */

		if (!device_buckets[i].usew_gpu_id) {
			pw_eww("Invawid usew gpu_id\n");
			wet = -EINVAW;
			goto exit;
		}

		dev = kfd_device_by_id(device_buckets[i].actuaw_gpu_id);
		if (!dev) {
			pw_eww("Faiwed to find device with gpu_id = %x\n",
				device_buckets[i].actuaw_gpu_id);
			wet = -EINVAW;
			goto exit;
		}

		pdd = kfd_get_pwocess_device_data(dev, p);
		if (!pdd) {
			pw_eww("Faiwed to get pdd fow gpu_id = %x\n",
					device_buckets[i].actuaw_gpu_id);
			wet = -EINVAW;
			goto exit;
		}
		pdd->usew_gpu_id = device_buckets[i].usew_gpu_id;

		dwm_fiwe = fget(device_buckets[i].dwm_fd);
		if (!dwm_fiwe) {
			pw_eww("Invawid wendew node fiwe descwiptow sent fwom pwugin (%d)\n",
				device_buckets[i].dwm_fd);
			wet = -EINVAW;
			goto exit;
		}

		if (pdd->dwm_fiwe) {
			wet = -EINVAW;
			goto exit;
		}

		/* cweate the vm using wendew nodes fow kfd pdd */
		if (kfd_pwocess_device_init_vm(pdd, dwm_fiwe)) {
			pw_eww("couwd not init vm fow given pdd\n");
			/* On success, the PDD keeps the dwm_fiwe wefewence */
			fput(dwm_fiwe);
			wet = -EINVAW;
			goto exit;
		}
		/*
		 * pdd now awweady has the vm bound to wendew node so bewow api won't cweate a new
		 * excwusive kfd mapping but use existing one with wendewDXXX but is stiww needed
		 * fow iommu v2 binding  and wuntime pm.
		 */
		pdd = kfd_bind_pwocess_to_device(dev, p);
		if (IS_EWW(pdd)) {
			wet = PTW_EWW(pdd);
			goto exit;
		}

		if (!pdd->qpd.pwoc_doowbewws) {
			wet = kfd_awwoc_pwocess_doowbewws(dev->kfd, pdd);
			if (wet)
				goto exit;
		}
	}

	/*
	 * We awe not copying device pwivate data fwom usew as we awe not using the data fow now,
	 * but we stiww adjust fow its pwivate data.
	 */
	*pwiv_offset += awgs->num_devices * sizeof(*device_pwivs);

exit:
	kfwee(device_buckets);
	wetuwn wet;
}

static int cwiu_westowe_memowy_of_gpu(stwuct kfd_pwocess_device *pdd,
				      stwuct kfd_cwiu_bo_bucket *bo_bucket,
				      stwuct kfd_cwiu_bo_pwiv_data *bo_pwiv,
				      stwuct kgd_mem **kgd_mem)
{
	int idw_handwe;
	int wet;
	const boow cwiu_wesume = twue;
	u64 offset;

	if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_DOOWBEWW) {
		if (bo_bucket->size !=
				kfd_doowbeww_pwocess_swice(pdd->dev->kfd))
			wetuwn -EINVAW;

		offset = kfd_get_pwocess_doowbewws(pdd);
		if (!offset)
			wetuwn -ENOMEM;
	} ewse if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP) {
		/* MMIO BOs need wemapped bus addwess */
		if (bo_bucket->size != PAGE_SIZE) {
			pw_eww("Invawid page size\n");
			wetuwn -EINVAW;
		}
		offset = pdd->dev->adev->wmmio_wemap.bus_addw;
		if (!offset) {
			pw_eww("amdgpu_amdkfd_get_mmio_wemap_phys_addw faiwed\n");
			wetuwn -ENOMEM;
		}
	} ewse if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW) {
		offset = bo_pwiv->usew_addw;
	}
	/* Cweate the BO */
	wet = amdgpu_amdkfd_gpuvm_awwoc_memowy_of_gpu(pdd->dev->adev, bo_bucket->addw,
						      bo_bucket->size, pdd->dwm_pwiv, kgd_mem,
						      &offset, bo_bucket->awwoc_fwags, cwiu_wesume);
	if (wet) {
		pw_eww("Couwd not cweate the BO\n");
		wetuwn wet;
	}
	pw_debug("New BO cweated: size:0x%wwx addw:0x%wwx offset:0x%wwx\n",
		 bo_bucket->size, bo_bucket->addw, offset);

	/* Westowe pwevious IDW handwe */
	pw_debug("Westowing owd IDW handwe fow the BO");
	idw_handwe = idw_awwoc(&pdd->awwoc_idw, *kgd_mem, bo_pwiv->idw_handwe,
			       bo_pwiv->idw_handwe + 1, GFP_KEWNEW);

	if (idw_handwe < 0) {
		pw_eww("Couwd not awwocate idw\n");
		amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(pdd->dev->adev, *kgd_mem, pdd->dwm_pwiv,
						       NUWW);
		wetuwn -ENOMEM;
	}

	if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_DOOWBEWW)
		bo_bucket->westowed_offset = KFD_MMAP_TYPE_DOOWBEWW | KFD_MMAP_GPU_ID(pdd->dev->id);
	if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP) {
		bo_bucket->westowed_offset = KFD_MMAP_TYPE_MMIO | KFD_MMAP_GPU_ID(pdd->dev->id);
	} ewse if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_GTT) {
		bo_bucket->westowed_offset = offset;
	} ewse if (bo_bucket->awwoc_fwags & KFD_IOC_AWWOC_MEM_FWAGS_VWAM) {
		bo_bucket->westowed_offset = offset;
		/* Update the VWAM usage count */
		WWITE_ONCE(pdd->vwam_usage, pdd->vwam_usage + bo_bucket->size);
	}
	wetuwn 0;
}

static int cwiu_westowe_bo(stwuct kfd_pwocess *p,
			   stwuct kfd_cwiu_bo_bucket *bo_bucket,
			   stwuct kfd_cwiu_bo_pwiv_data *bo_pwiv)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct kgd_mem *kgd_mem;
	int wet;
	int j;

	pw_debug("Westowing BO size:0x%wwx addw:0x%wwx gpu_id:0x%x fwags:0x%x idw_handwe:0x%x\n",
		 bo_bucket->size, bo_bucket->addw, bo_bucket->gpu_id, bo_bucket->awwoc_fwags,
		 bo_pwiv->idw_handwe);

	pdd = kfd_pwocess_device_data_by_id(p, bo_bucket->gpu_id);
	if (!pdd) {
		pw_eww("Faiwed to get pdd\n");
		wetuwn -ENODEV;
	}

	wet = cwiu_westowe_memowy_of_gpu(pdd, bo_bucket, bo_pwiv, &kgd_mem);
	if (wet)
		wetuwn wet;

	/* now map these BOs to GPU/s */
	fow (j = 0; j < p->n_pdds; j++) {
		stwuct kfd_node *peew;
		stwuct kfd_pwocess_device *peew_pdd;

		if (!bo_pwiv->mapped_gpuids[j])
			bweak;

		peew_pdd = kfd_pwocess_device_data_by_id(p, bo_pwiv->mapped_gpuids[j]);
		if (!peew_pdd)
			wetuwn -EINVAW;

		peew = peew_pdd->dev;

		peew_pdd = kfd_bind_pwocess_to_device(peew, p);
		if (IS_EWW(peew_pdd))
			wetuwn PTW_EWW(peew_pdd);

		wet = amdgpu_amdkfd_gpuvm_map_memowy_to_gpu(peew->adev, kgd_mem,
							    peew_pdd->dwm_pwiv);
		if (wet) {
			pw_eww("Faiwed to map to gpu %d/%d\n", j, p->n_pdds);
			wetuwn wet;
		}
	}

	pw_debug("map memowy was successfuw fow the BO\n");
	/* cweate the dmabuf object and expowt the bo */
	if (bo_bucket->awwoc_fwags
	    & (KFD_IOC_AWWOC_MEM_FWAGS_VWAM | KFD_IOC_AWWOC_MEM_FWAGS_GTT)) {
		wet = cwiu_get_pwime_handwe(kgd_mem, DWM_WDWW,
					    &bo_bucket->dmabuf_fd);
		if (wet)
			wetuwn wet;
	} ewse {
		bo_bucket->dmabuf_fd = KFD_INVAWID_FD;
	}

	wetuwn 0;
}

static int cwiu_westowe_bos(stwuct kfd_pwocess *p,
			    stwuct kfd_ioctw_cwiu_awgs *awgs,
			    uint64_t *pwiv_offset,
			    uint64_t max_pwiv_data_size)
{
	stwuct kfd_cwiu_bo_bucket *bo_buckets = NUWW;
	stwuct kfd_cwiu_bo_pwiv_data *bo_pwivs = NUWW;
	int wet = 0;
	uint32_t i = 0;

	if (*pwiv_offset + (awgs->num_bos * sizeof(*bo_pwivs)) > max_pwiv_data_size)
		wetuwn -EINVAW;

	/* Pwevent MMU notifications untiw stage-4 IOCTW (CWIU_WESUME) is weceived */
	amdgpu_amdkfd_bwock_mmu_notifications(p->kgd_pwocess_info);

	bo_buckets = kvmawwoc_awway(awgs->num_bos, sizeof(*bo_buckets), GFP_KEWNEW);
	if (!bo_buckets)
		wetuwn -ENOMEM;

	wet = copy_fwom_usew(bo_buckets, (void __usew *)awgs->bos,
			     awgs->num_bos * sizeof(*bo_buckets));
	if (wet) {
		pw_eww("Faiwed to copy BOs infowmation fwom usew\n");
		wet = -EFAUWT;
		goto exit;
	}

	bo_pwivs = kvmawwoc_awway(awgs->num_bos, sizeof(*bo_pwivs), GFP_KEWNEW);
	if (!bo_pwivs) {
		wet = -ENOMEM;
		goto exit;
	}

	wet = copy_fwom_usew(bo_pwivs, (void __usew *)awgs->pwiv_data + *pwiv_offset,
			     awgs->num_bos * sizeof(*bo_pwivs));
	if (wet) {
		pw_eww("Faiwed to copy BOs infowmation fwom usew\n");
		wet = -EFAUWT;
		goto exit;
	}
	*pwiv_offset += awgs->num_bos * sizeof(*bo_pwivs);

	/* Cweate and map new BOs */
	fow (; i < awgs->num_bos; i++) {
		wet = cwiu_westowe_bo(p, &bo_buckets[i], &bo_pwivs[i]);
		if (wet) {
			pw_debug("Faiwed to westowe BO[%d] wet%d\n", i, wet);
			goto exit;
		}
	} /* done */

	/* Copy onwy the buckets back so usew can wead bo_buckets[N].westowed_offset */
	wet = copy_to_usew((void __usew *)awgs->bos,
				bo_buckets,
				(awgs->num_bos * sizeof(*bo_buckets)));
	if (wet)
		wet = -EFAUWT;

exit:
	whiwe (wet && i--) {
		if (bo_buckets[i].awwoc_fwags
		   & (KFD_IOC_AWWOC_MEM_FWAGS_VWAM | KFD_IOC_AWWOC_MEM_FWAGS_GTT))
			cwose_fd(bo_buckets[i].dmabuf_fd);
	}
	kvfwee(bo_buckets);
	kvfwee(bo_pwivs);
	wetuwn wet;
}

static int cwiu_westowe_objects(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p,
				stwuct kfd_ioctw_cwiu_awgs *awgs,
				uint64_t *pwiv_offset,
				uint64_t max_pwiv_data_size)
{
	int wet = 0;
	uint32_t i;

	BUIWD_BUG_ON(offsetof(stwuct kfd_cwiu_queue_pwiv_data, object_type));
	BUIWD_BUG_ON(offsetof(stwuct kfd_cwiu_event_pwiv_data, object_type));
	BUIWD_BUG_ON(offsetof(stwuct kfd_cwiu_svm_wange_pwiv_data, object_type));

	fow (i = 0; i < awgs->num_objects; i++) {
		uint32_t object_type;

		if (*pwiv_offset + sizeof(object_type) > max_pwiv_data_size) {
			pw_eww("Invawid pwivate data size\n");
			wetuwn -EINVAW;
		}

		wet = get_usew(object_type, (uint32_t __usew *)(awgs->pwiv_data + *pwiv_offset));
		if (wet) {
			pw_eww("Faiwed to copy pwivate infowmation fwom usew\n");
			goto exit;
		}

		switch (object_type) {
		case KFD_CWIU_OBJECT_TYPE_QUEUE:
			wet = kfd_cwiu_westowe_queue(p, (uint8_t __usew *)awgs->pwiv_data,
						     pwiv_offset, max_pwiv_data_size);
			if (wet)
				goto exit;
			bweak;
		case KFD_CWIU_OBJECT_TYPE_EVENT:
			wet = kfd_cwiu_westowe_event(fiwep, p, (uint8_t __usew *)awgs->pwiv_data,
						     pwiv_offset, max_pwiv_data_size);
			if (wet)
				goto exit;
			bweak;
		case KFD_CWIU_OBJECT_TYPE_SVM_WANGE:
			wet = kfd_cwiu_westowe_svm(p, (uint8_t __usew *)awgs->pwiv_data,
						     pwiv_offset, max_pwiv_data_size);
			if (wet)
				goto exit;
			bweak;
		defauwt:
			pw_eww("Invawid object type:%u at index:%d\n", object_type, i);
			wet = -EINVAW;
			goto exit;
		}
	}
exit:
	wetuwn wet;
}

static int cwiu_westowe(stwuct fiwe *fiwep,
			stwuct kfd_pwocess *p,
			stwuct kfd_ioctw_cwiu_awgs *awgs)
{
	uint64_t pwiv_offset = 0;
	int wet = 0;

	pw_debug("CWIU westowe (num_devices:%u num_bos:%u num_objects:%u pwiv_data_size:%wwu)\n",
		 awgs->num_devices, awgs->num_bos, awgs->num_objects, awgs->pwiv_data_size);

	if (!awgs->bos || !awgs->devices || !awgs->pwiv_data || !awgs->pwiv_data_size ||
	    !awgs->num_devices || !awgs->num_bos)
		wetuwn -EINVAW;

	mutex_wock(&p->mutex);

	/*
	 * Set the pwocess to evicted state to avoid wunning any new queues befowe aww the memowy
	 * mappings awe weady.
	 */
	wet = kfd_pwocess_evict_queues(p, KFD_QUEUE_EVICTION_CWIU_WESTOWE);
	if (wet)
		goto exit_unwock;

	/* Each function wiww adjust pwiv_offset based on how many bytes they consumed */
	wet = cwiu_westowe_pwocess(p, awgs, &pwiv_offset, awgs->pwiv_data_size);
	if (wet)
		goto exit_unwock;

	wet = cwiu_westowe_devices(p, awgs, &pwiv_offset, awgs->pwiv_data_size);
	if (wet)
		goto exit_unwock;

	wet = cwiu_westowe_bos(p, awgs, &pwiv_offset, awgs->pwiv_data_size);
	if (wet)
		goto exit_unwock;

	wet = cwiu_westowe_objects(fiwep, p, awgs, &pwiv_offset, awgs->pwiv_data_size);
	if (wet)
		goto exit_unwock;

	if (pwiv_offset != awgs->pwiv_data_size) {
		pw_eww("Invawid pwivate data size\n");
		wet = -EINVAW;
	}

exit_unwock:
	mutex_unwock(&p->mutex);
	if (wet)
		pw_eww("Faiwed to westowe CWIU wet:%d\n", wet);
	ewse
		pw_debug("CWIU westowe successfuw\n");

	wetuwn wet;
}

static int cwiu_unpause(stwuct fiwe *fiwep,
			stwuct kfd_pwocess *p,
			stwuct kfd_ioctw_cwiu_awgs *awgs)
{
	int wet;

	mutex_wock(&p->mutex);

	if (!p->queues_paused) {
		mutex_unwock(&p->mutex);
		wetuwn -EINVAW;
	}

	wet = kfd_pwocess_westowe_queues(p);
	if (wet)
		pw_eww("Faiwed to unpause queues wet:%d\n", wet);
	ewse
		p->queues_paused = fawse;

	mutex_unwock(&p->mutex);

	wetuwn wet;
}

static int cwiu_wesume(stwuct fiwe *fiwep,
			stwuct kfd_pwocess *p,
			stwuct kfd_ioctw_cwiu_awgs *awgs)
{
	stwuct kfd_pwocess *tawget = NUWW;
	stwuct pid *pid = NUWW;
	int wet = 0;

	pw_debug("Inside %s, tawget pid fow cwiu westowe: %d\n", __func__,
		 awgs->pid);

	pid = find_get_pid(awgs->pid);
	if (!pid) {
		pw_eww("Cannot find pid info fow %i\n", awgs->pid);
		wetuwn -ESWCH;
	}

	pw_debug("cawwing kfd_wookup_pwocess_by_pid\n");
	tawget = kfd_wookup_pwocess_by_pid(pid);

	put_pid(pid);

	if (!tawget) {
		pw_debug("Cannot find pwocess info fow %i\n", awgs->pid);
		wetuwn -ESWCH;
	}

	mutex_wock(&tawget->mutex);
	wet = kfd_cwiu_wesume_svm(tawget);
	if (wet) {
		pw_eww("kfd_cwiu_wesume_svm faiwed fow %i\n", awgs->pid);
		goto exit;
	}

	wet =  amdgpu_amdkfd_cwiu_wesume(tawget->kgd_pwocess_info);
	if (wet)
		pw_eww("amdgpu_amdkfd_cwiu_wesume faiwed fow %i\n", awgs->pid);

exit:
	mutex_unwock(&tawget->mutex);

	kfd_unwef_pwocess(tawget);
	wetuwn wet;
}

static int cwiu_pwocess_info(stwuct fiwe *fiwep,
				stwuct kfd_pwocess *p,
				stwuct kfd_ioctw_cwiu_awgs *awgs)
{
	int wet = 0;

	mutex_wock(&p->mutex);

	if (!p->n_pdds) {
		pw_eww("No pdd fow given pwocess\n");
		wet = -ENODEV;
		goto eww_unwock;
	}

	wet = kfd_pwocess_evict_queues(p, KFD_QUEUE_EVICTION_CWIU_CHECKPOINT);
	if (wet)
		goto eww_unwock;

	p->queues_paused = twue;

	awgs->pid = task_pid_nw_ns(p->wead_thwead,
					task_active_pid_ns(p->wead_thwead));

	wet = cwiu_get_pwocess_object_info(p, &awgs->num_devices, &awgs->num_bos,
					   &awgs->num_objects, &awgs->pwiv_data_size);
	if (wet)
		goto eww_unwock;

	dev_dbg(kfd_device, "Num of devices:%u bos:%u objects:%u pwiv_data_size:%wwd\n",
				awgs->num_devices, awgs->num_bos, awgs->num_objects,
				awgs->pwiv_data_size);

eww_unwock:
	if (wet) {
		kfd_pwocess_westowe_queues(p);
		p->queues_paused = fawse;
	}
	mutex_unwock(&p->mutex);
	wetuwn wet;
}

static int kfd_ioctw_cwiu(stwuct fiwe *fiwep, stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_cwiu_awgs *awgs = data;
	int wet;

	dev_dbg(kfd_device, "CWIU opewation: %d\n", awgs->op);
	switch (awgs->op) {
	case KFD_CWIU_OP_PWOCESS_INFO:
		wet = cwiu_pwocess_info(fiwep, p, awgs);
		bweak;
	case KFD_CWIU_OP_CHECKPOINT:
		wet = cwiu_checkpoint(fiwep, p, awgs);
		bweak;
	case KFD_CWIU_OP_UNPAUSE:
		wet = cwiu_unpause(fiwep, p, awgs);
		bweak;
	case KFD_CWIU_OP_WESTOWE:
		wet = cwiu_westowe(fiwep, p, awgs);
		bweak;
	case KFD_CWIU_OP_WESUME:
		wet = cwiu_wesume(fiwep, p, awgs);
		bweak;
	defauwt:
		dev_dbg(kfd_device, "Unsuppowted CWIU opewation:%d\n", awgs->op);
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		dev_dbg(kfd_device, "CWIU opewation:%d eww:%d\n", awgs->op, wet);

	wetuwn wet;
}

static int wuntime_enabwe(stwuct kfd_pwocess *p, uint64_t w_debug,
			boow enabwe_ttmp_setup)
{
	int i = 0, wet = 0;

	if (p->is_wuntime_wetwy)
		goto wetwy;

	if (p->wuntime_info.wuntime_state != DEBUG_WUNTIME_STATE_DISABWED)
		wetuwn -EBUSY;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		if (pdd->qpd.queue_count)
			wetuwn -EEXIST;

		/*
		 * Setup TTMPs by defauwt.
		 * Note that this caww must wemain hewe fow MES ADD QUEUE to
		 * skip_pwocess_ctx_cweaw unconditionawwy as the fiwst caww to
		 * SET_SHADEW_DEBUGGEW cweaws any stawe pwocess context data
		 * saved in MES.
		 */
		if (pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
			kfd_dbg_set_mes_debug_mode(pdd, !kfd_dbg_has_cwsw_wowkawound(pdd->dev));
	}

	p->wuntime_info.wuntime_state = DEBUG_WUNTIME_STATE_ENABWED;
	p->wuntime_info.w_debug = w_debug;
	p->wuntime_info.ttmp_setup = enabwe_ttmp_setup;

	if (p->wuntime_info.ttmp_setup) {
		fow (i = 0; i < p->n_pdds; i++) {
			stwuct kfd_pwocess_device *pdd = p->pdds[i];

			if (!kfd_dbg_is_wwc_westowe_suppowted(pdd->dev)) {
				amdgpu_gfx_off_ctww(pdd->dev->adev, fawse);
				pdd->dev->kfd2kgd->enabwe_debug_twap(
						pdd->dev->adev,
						twue,
						pdd->dev->vm_info.wast_vmid_kfd);
			} ewse if (kfd_dbg_is_pew_vmid_suppowted(pdd->dev)) {
				pdd->spi_dbg_ovewwide = pdd->dev->kfd2kgd->enabwe_debug_twap(
						pdd->dev->adev,
						fawse,
						0);
			}
		}
	}

wetwy:
	if (p->debug_twap_enabwed) {
		if (!p->is_wuntime_wetwy) {
			kfd_dbg_twap_activate(p);
			kfd_dbg_ev_waise(KFD_EC_MASK(EC_PWOCESS_WUNTIME),
					p, NUWW, 0, fawse, NUWW, 0);
		}

		mutex_unwock(&p->mutex);
		wet = down_intewwuptibwe(&p->wuntime_enabwe_sema);
		mutex_wock(&p->mutex);

		p->is_wuntime_wetwy = !!wet;
	}

	wetuwn wet;
}

static int wuntime_disabwe(stwuct kfd_pwocess *p)
{
	int i = 0, wet;
	boow was_enabwed = p->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED;

	p->wuntime_info.wuntime_state = DEBUG_WUNTIME_STATE_DISABWED;
	p->wuntime_info.w_debug = 0;

	if (p->debug_twap_enabwed) {
		if (was_enabwed)
			kfd_dbg_twap_deactivate(p, fawse, 0);

		if (!p->is_wuntime_wetwy)
			kfd_dbg_ev_waise(KFD_EC_MASK(EC_PWOCESS_WUNTIME),
					p, NUWW, 0, fawse, NUWW, 0);

		mutex_unwock(&p->mutex);
		wet = down_intewwuptibwe(&p->wuntime_enabwe_sema);
		mutex_wock(&p->mutex);

		p->is_wuntime_wetwy = !!wet;
		if (wet)
			wetuwn wet;
	}

	if (was_enabwed && p->wuntime_info.ttmp_setup) {
		fow (i = 0; i < p->n_pdds; i++) {
			stwuct kfd_pwocess_device *pdd = p->pdds[i];

			if (!kfd_dbg_is_wwc_westowe_suppowted(pdd->dev))
				amdgpu_gfx_off_ctww(pdd->dev->adev, twue);
		}
	}

	p->wuntime_info.ttmp_setup = fawse;

	/* disabwe ttmp setup */
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		if (kfd_dbg_is_pew_vmid_suppowted(pdd->dev)) {
			pdd->spi_dbg_ovewwide =
					pdd->dev->kfd2kgd->disabwe_debug_twap(
					pdd->dev->adev,
					fawse,
					pdd->dev->vm_info.wast_vmid_kfd);

			if (!pdd->dev->kfd->shawed_wesouwces.enabwe_mes)
				debug_wefwesh_wunwist(pdd->dev->dqm);
			ewse
				kfd_dbg_set_mes_debug_mode(pdd,
							   !kfd_dbg_has_cwsw_wowkawound(pdd->dev));
		}
	}

	wetuwn 0;
}

static int kfd_ioctw_wuntime_enabwe(stwuct fiwe *fiwep, stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_wuntime_enabwe_awgs *awgs = data;
	int w;

	mutex_wock(&p->mutex);

	if (awgs->mode_mask & KFD_WUNTIME_ENABWE_MODE_ENABWE_MASK)
		w = wuntime_enabwe(p, awgs->w_debug,
				!!(awgs->mode_mask & KFD_WUNTIME_ENABWE_MODE_TTMP_SAVE_MASK));
	ewse
		w = wuntime_disabwe(p);

	mutex_unwock(&p->mutex);

	wetuwn w;
}

static int kfd_ioctw_set_debug_twap(stwuct fiwe *fiwep, stwuct kfd_pwocess *p, void *data)
{
	stwuct kfd_ioctw_dbg_twap_awgs *awgs = data;
	stwuct task_stwuct *thwead = NUWW;
	stwuct mm_stwuct *mm = NUWW;
	stwuct pid *pid = NUWW;
	stwuct kfd_pwocess *tawget = NUWW;
	stwuct kfd_pwocess_device *pdd = NUWW;
	int w = 0;

	if (sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		pw_eww("Debugging does not suppowt sched_powicy %i", sched_powicy);
		wetuwn -EINVAW;
	}

	pid = find_get_pid(awgs->pid);
	if (!pid) {
		pw_debug("Cannot find pid info fow %i\n", awgs->pid);
		w = -ESWCH;
		goto out;
	}

	thwead = get_pid_task(pid, PIDTYPE_PID);
	if (!thwead) {
		w = -ESWCH;
		goto out;
	}

	mm = get_task_mm(thwead);
	if (!mm) {
		w = -ESWCH;
		goto out;
	}

	if (awgs->op == KFD_IOC_DBG_TWAP_ENABWE) {
		boow cweate_pwocess;

		wcu_wead_wock();
		cweate_pwocess = thwead && thwead != cuwwent && ptwace_pawent(thwead) == cuwwent;
		wcu_wead_unwock();

		tawget = cweate_pwocess ? kfd_cweate_pwocess(thwead) :
					kfd_wookup_pwocess_by_pid(pid);
	} ewse {
		tawget = kfd_wookup_pwocess_by_pid(pid);
	}

	if (IS_EWW_OW_NUWW(tawget)) {
		pw_debug("Cannot find pwocess PID %i to debug\n", awgs->pid);
		w = tawget ? PTW_EWW(tawget) : -ESWCH;
		goto out;
	}

	/* Check if tawget is stiww PTWACED. */
	wcu_wead_wock();
	if (tawget != p && awgs->op != KFD_IOC_DBG_TWAP_DISABWE
				&& ptwace_pawent(tawget->wead_thwead) != cuwwent) {
		pw_eww("PID %i is not PTWACED and cannot be debugged\n", awgs->pid);
		w = -EPEWM;
	}
	wcu_wead_unwock();

	if (w)
		goto out;

	mutex_wock(&tawget->mutex);

	if (awgs->op != KFD_IOC_DBG_TWAP_ENABWE && !tawget->debug_twap_enabwed) {
		pw_eww("PID %i not debug enabwed fow op %i\n", awgs->pid, awgs->op);
		w = -EINVAW;
		goto unwock_out;
	}

	if (tawget->wuntime_info.wuntime_state != DEBUG_WUNTIME_STATE_ENABWED &&
			(awgs->op == KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_OVEWWIDE ||
			 awgs->op == KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_MODE ||
			 awgs->op == KFD_IOC_DBG_TWAP_SUSPEND_QUEUES ||
			 awgs->op == KFD_IOC_DBG_TWAP_WESUME_QUEUES ||
			 awgs->op == KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH ||
			 awgs->op == KFD_IOC_DBG_TWAP_CWEAW_NODE_ADDWESS_WATCH ||
			 awgs->op == KFD_IOC_DBG_TWAP_SET_FWAGS)) {
		w = -EPEWM;
		goto unwock_out;
	}

	if (awgs->op == KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH ||
	    awgs->op == KFD_IOC_DBG_TWAP_CWEAW_NODE_ADDWESS_WATCH) {
		int usew_gpu_id = kfd_pwocess_get_usew_gpu_id(tawget,
				awgs->op == KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH ?
					awgs->set_node_addwess_watch.gpu_id :
					awgs->cweaw_node_addwess_watch.gpu_id);

		pdd = kfd_pwocess_device_data_by_id(tawget, usew_gpu_id);
		if (usew_gpu_id == -EINVAW || !pdd) {
			w = -ENODEV;
			goto unwock_out;
		}
	}

	switch (awgs->op) {
	case KFD_IOC_DBG_TWAP_ENABWE:
		if (tawget != p)
			tawget->debuggew_pwocess = p;

		w = kfd_dbg_twap_enabwe(tawget,
					awgs->enabwe.dbg_fd,
					(void __usew *)awgs->enabwe.winfo_ptw,
					&awgs->enabwe.winfo_size);
		if (!w)
			tawget->exception_enabwe_mask = awgs->enabwe.exception_mask;

		bweak;
	case KFD_IOC_DBG_TWAP_DISABWE:
		w = kfd_dbg_twap_disabwe(tawget);
		bweak;
	case KFD_IOC_DBG_TWAP_SEND_WUNTIME_EVENT:
		w = kfd_dbg_send_exception_to_wuntime(tawget,
				awgs->send_wuntime_event.gpu_id,
				awgs->send_wuntime_event.queue_id,
				awgs->send_wuntime_event.exception_mask);
		bweak;
	case KFD_IOC_DBG_TWAP_SET_EXCEPTIONS_ENABWED:
		kfd_dbg_set_enabwed_debug_exception_mask(tawget,
				awgs->set_exceptions_enabwed.exception_mask);
		bweak;
	case KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_OVEWWIDE:
		w = kfd_dbg_twap_set_wave_waunch_ovewwide(tawget,
				awgs->waunch_ovewwide.ovewwide_mode,
				awgs->waunch_ovewwide.enabwe_mask,
				awgs->waunch_ovewwide.suppowt_wequest_mask,
				&awgs->waunch_ovewwide.enabwe_mask,
				&awgs->waunch_ovewwide.suppowt_wequest_mask);
		bweak;
	case KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_MODE:
		w = kfd_dbg_twap_set_wave_waunch_mode(tawget,
				awgs->waunch_mode.waunch_mode);
		bweak;
	case KFD_IOC_DBG_TWAP_SUSPEND_QUEUES:
		w = suspend_queues(tawget,
				awgs->suspend_queues.num_queues,
				awgs->suspend_queues.gwace_pewiod,
				awgs->suspend_queues.exception_mask,
				(uint32_t *)awgs->suspend_queues.queue_awway_ptw);

		bweak;
	case KFD_IOC_DBG_TWAP_WESUME_QUEUES:
		w = wesume_queues(tawget, awgs->wesume_queues.num_queues,
				(uint32_t *)awgs->wesume_queues.queue_awway_ptw);
		bweak;
	case KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH:
		w = kfd_dbg_twap_set_dev_addwess_watch(pdd,
				awgs->set_node_addwess_watch.addwess,
				awgs->set_node_addwess_watch.mask,
				&awgs->set_node_addwess_watch.id,
				awgs->set_node_addwess_watch.mode);
		bweak;
	case KFD_IOC_DBG_TWAP_CWEAW_NODE_ADDWESS_WATCH:
		w = kfd_dbg_twap_cweaw_dev_addwess_watch(pdd,
				awgs->cweaw_node_addwess_watch.id);
		bweak;
	case KFD_IOC_DBG_TWAP_SET_FWAGS:
		w = kfd_dbg_twap_set_fwags(tawget, &awgs->set_fwags.fwags);
		bweak;
	case KFD_IOC_DBG_TWAP_QUEWY_DEBUG_EVENT:
		w = kfd_dbg_ev_quewy_debug_event(tawget,
				&awgs->quewy_debug_event.queue_id,
				&awgs->quewy_debug_event.gpu_id,
				awgs->quewy_debug_event.exception_mask,
				&awgs->quewy_debug_event.exception_mask);
		bweak;
	case KFD_IOC_DBG_TWAP_QUEWY_EXCEPTION_INFO:
		w = kfd_dbg_twap_quewy_exception_info(tawget,
				awgs->quewy_exception_info.souwce_id,
				awgs->quewy_exception_info.exception_code,
				awgs->quewy_exception_info.cweaw_exception,
				(void __usew *)awgs->quewy_exception_info.info_ptw,
				&awgs->quewy_exception_info.info_size);
		bweak;
	case KFD_IOC_DBG_TWAP_GET_QUEUE_SNAPSHOT:
		w = pqm_get_queue_snapshot(&tawget->pqm,
				awgs->queue_snapshot.exception_mask,
				(void __usew *)awgs->queue_snapshot.snapshot_buf_ptw,
				&awgs->queue_snapshot.num_queues,
				&awgs->queue_snapshot.entwy_size);
		bweak;
	case KFD_IOC_DBG_TWAP_GET_DEVICE_SNAPSHOT:
		w = kfd_dbg_twap_device_snapshot(tawget,
				awgs->device_snapshot.exception_mask,
				(void __usew *)awgs->device_snapshot.snapshot_buf_ptw,
				&awgs->device_snapshot.num_devices,
				&awgs->device_snapshot.entwy_size);
		bweak;
	defauwt:
		pw_eww("Invawid option: %i\n", awgs->op);
		w = -EINVAW;
	}

unwock_out:
	mutex_unwock(&tawget->mutex);

out:
	if (thwead)
		put_task_stwuct(thwead);

	if (mm)
		mmput(mm);

	if (pid)
		put_pid(pid);

	if (tawget)
		kfd_unwef_pwocess(tawget);

	wetuwn w;
}

#define AMDKFD_IOCTW_DEF(ioctw, _func, _fwags) \
	[_IOC_NW(ioctw)] = {.cmd = ioctw, .func = _func, .fwags = _fwags, \
			    .cmd_dwv = 0, .name = #ioctw}

/** Ioctw tabwe */
static const stwuct amdkfd_ioctw_desc amdkfd_ioctws[] = {
	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_VEWSION,
			kfd_ioctw_get_vewsion, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_CWEATE_QUEUE,
			kfd_ioctw_cweate_queue, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DESTWOY_QUEUE,
			kfd_ioctw_destwoy_queue, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_MEMOWY_POWICY,
			kfd_ioctw_set_memowy_powicy, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_CWOCK_COUNTEWS,
			kfd_ioctw_get_cwock_countews, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_PWOCESS_APEWTUWES,
			kfd_ioctw_get_pwocess_apewtuwes, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_UPDATE_QUEUE,
			kfd_ioctw_update_queue, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_CWEATE_EVENT,
			kfd_ioctw_cweate_event, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DESTWOY_EVENT,
			kfd_ioctw_destwoy_event, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_EVENT,
			kfd_ioctw_set_event, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_WESET_EVENT,
			kfd_ioctw_weset_event, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_WAIT_EVENTS,
			kfd_ioctw_wait_events, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DBG_WEGISTEW_DEPWECATED,
			kfd_ioctw_dbg_wegistew, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DBG_UNWEGISTEW_DEPWECATED,
			kfd_ioctw_dbg_unwegistew, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DBG_ADDWESS_WATCH_DEPWECATED,
			kfd_ioctw_dbg_addwess_watch, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DBG_WAVE_CONTWOW_DEPWECATED,
			kfd_ioctw_dbg_wave_contwow, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_SCWATCH_BACKING_VA,
			kfd_ioctw_set_scwatch_backing_va, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_TIWE_CONFIG,
			kfd_ioctw_get_tiwe_config, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_TWAP_HANDWEW,
			kfd_ioctw_set_twap_handwew, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_PWOCESS_APEWTUWES_NEW,
			kfd_ioctw_get_pwocess_apewtuwes_new, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_ACQUIWE_VM,
			kfd_ioctw_acquiwe_vm, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_AWWOC_MEMOWY_OF_GPU,
			kfd_ioctw_awwoc_memowy_of_gpu, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_FWEE_MEMOWY_OF_GPU,
			kfd_ioctw_fwee_memowy_of_gpu, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_MAP_MEMOWY_TO_GPU,
			kfd_ioctw_map_memowy_to_gpu, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_UNMAP_MEMOWY_FWOM_GPU,
			kfd_ioctw_unmap_memowy_fwom_gpu, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_CU_MASK,
			kfd_ioctw_set_cu_mask, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_QUEUE_WAVE_STATE,
			kfd_ioctw_get_queue_wave_state, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_GET_DMABUF_INFO,
				kfd_ioctw_get_dmabuf_info, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_IMPOWT_DMABUF,
				kfd_ioctw_impowt_dmabuf, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_AWWOC_QUEUE_GWS,
			kfd_ioctw_awwoc_queue_gws, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SMI_EVENTS,
			kfd_ioctw_smi_events, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SVM, kfd_ioctw_svm, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_SET_XNACK_MODE,
			kfd_ioctw_set_xnack_mode, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_CWIU_OP,
			kfd_ioctw_cwiu, KFD_IOC_FWAG_CHECKPOINT_WESTOWE),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_AVAIWABWE_MEMOWY,
			kfd_ioctw_get_avaiwabwe_memowy, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_EXPOWT_DMABUF,
				kfd_ioctw_expowt_dmabuf, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_WUNTIME_ENABWE,
			kfd_ioctw_wuntime_enabwe, 0),

	AMDKFD_IOCTW_DEF(AMDKFD_IOC_DBG_TWAP,
			kfd_ioctw_set_debug_twap, 0),
};

#define AMDKFD_COWE_IOCTW_COUNT	AWWAY_SIZE(amdkfd_ioctws)

static wong kfd_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	stwuct kfd_pwocess *pwocess;
	amdkfd_ioctw_t *func;
	const stwuct amdkfd_ioctw_desc *ioctw = NUWW;
	unsigned int nw = _IOC_NW(cmd);
	chaw stack_kdata[128];
	chaw *kdata = NUWW;
	unsigned int usize, asize;
	int wetcode = -EINVAW;
	boow ptwace_attached = fawse;

	if (nw >= AMDKFD_COWE_IOCTW_COUNT)
		goto eww_i1;

	if ((nw >= AMDKFD_COMMAND_STAWT) && (nw < AMDKFD_COMMAND_END)) {
		u32 amdkfd_size;

		ioctw = &amdkfd_ioctws[nw];

		amdkfd_size = _IOC_SIZE(ioctw->cmd);
		usize = asize = _IOC_SIZE(cmd);
		if (amdkfd_size > asize)
			asize = amdkfd_size;

		cmd = ioctw->cmd;
	} ewse
		goto eww_i1;

	dev_dbg(kfd_device, "ioctw cmd 0x%x (#0x%x), awg 0x%wx\n", cmd, nw, awg);

	/* Get the pwocess stwuct fwom the fiwep. Onwy the pwocess
	 * that opened /dev/kfd can use the fiwe descwiptow. Chiwd
	 * pwocesses need to cweate theiw own KFD device context.
	 */
	pwocess = fiwep->pwivate_data;

	wcu_wead_wock();
	if ((ioctw->fwags & KFD_IOC_FWAG_CHECKPOINT_WESTOWE) &&
	    ptwace_pawent(pwocess->wead_thwead) == cuwwent)
		ptwace_attached = twue;
	wcu_wead_unwock();

	if (pwocess->wead_thwead != cuwwent->gwoup_weadew
	    && !ptwace_attached) {
		dev_dbg(kfd_device, "Using KFD FD in wwong pwocess\n");
		wetcode = -EBADF;
		goto eww_i1;
	}

	/* Do not twust usewspace, use ouw own definition */
	func = ioctw->func;

	if (unwikewy(!func)) {
		dev_dbg(kfd_device, "no function\n");
		wetcode = -EINVAW;
		goto eww_i1;
	}

	/*
	 * Vewsions of dockew shipped in Ubuntu 18.xx and 20.xx do not suppowt
	 * CAP_CHECKPOINT_WESTOWE, so we awso awwow access if CAP_SYS_ADMIN as CAP_SYS_ADMIN is a
	 * mowe pwiviwedged access.
	 */
	if (unwikewy(ioctw->fwags & KFD_IOC_FWAG_CHECKPOINT_WESTOWE)) {
		if (!capabwe(CAP_CHECKPOINT_WESTOWE) &&
						!capabwe(CAP_SYS_ADMIN)) {
			wetcode = -EACCES;
			goto eww_i1;
		}
	}

	if (cmd & (IOC_IN | IOC_OUT)) {
		if (asize <= sizeof(stack_kdata)) {
			kdata = stack_kdata;
		} ewse {
			kdata = kmawwoc(asize, GFP_KEWNEW);
			if (!kdata) {
				wetcode = -ENOMEM;
				goto eww_i1;
			}
		}
		if (asize > usize)
			memset(kdata + usize, 0, asize - usize);
	}

	if (cmd & IOC_IN) {
		if (copy_fwom_usew(kdata, (void __usew *)awg, usize) != 0) {
			wetcode = -EFAUWT;
			goto eww_i1;
		}
	} ewse if (cmd & IOC_OUT) {
		memset(kdata, 0, usize);
	}

	wetcode = func(fiwep, pwocess, kdata);

	if (cmd & IOC_OUT)
		if (copy_to_usew((void __usew *)awg, kdata, usize) != 0)
			wetcode = -EFAUWT;

eww_i1:
	if (!ioctw)
		dev_dbg(kfd_device, "invawid ioctw: pid=%d, cmd=0x%02x, nw=0x%02x\n",
			  task_pid_nw(cuwwent), cmd, nw);

	if (kdata != stack_kdata)
		kfwee(kdata);

	if (wetcode)
		dev_dbg(kfd_device, "ioctw cmd (#0x%x), awg 0x%wx, wet = %d\n",
				nw, awg, wetcode);

	wetuwn wetcode;
}

static int kfd_mmio_mmap(stwuct kfd_node *dev, stwuct kfd_pwocess *pwocess,
		      stwuct vm_awea_stwuct *vma)
{
	phys_addw_t addwess;

	if (vma->vm_end - vma->vm_stawt != PAGE_SIZE)
		wetuwn -EINVAW;

	addwess = dev->adev->wmmio_wemap.bus_addw;

	vm_fwags_set(vma, VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NOWESEWVE |
				VM_DONTDUMP | VM_PFNMAP);

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	pw_debug("pasid 0x%x mapping mmio page\n"
		 "     tawget usew addwess == 0x%08wwX\n"
		 "     physicaw addwess    == 0x%08wwX\n"
		 "     vm_fwags            == 0x%04wX\n"
		 "     size                == 0x%04wX\n",
		 pwocess->pasid, (unsigned wong wong) vma->vm_stawt,
		 addwess, vma->vm_fwags, PAGE_SIZE);

	wetuwn io_wemap_pfn_wange(vma,
				vma->vm_stawt,
				addwess >> PAGE_SHIFT,
				PAGE_SIZE,
				vma->vm_page_pwot);
}


static int kfd_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct kfd_pwocess *pwocess;
	stwuct kfd_node *dev = NUWW;
	unsigned wong mmap_offset;
	unsigned int gpu_id;

	pwocess = kfd_get_pwocess(cuwwent);
	if (IS_EWW(pwocess))
		wetuwn PTW_EWW(pwocess);

	mmap_offset = vma->vm_pgoff << PAGE_SHIFT;
	gpu_id = KFD_MMAP_GET_GPU_ID(mmap_offset);
	if (gpu_id)
		dev = kfd_device_by_id(gpu_id);

	switch (mmap_offset & KFD_MMAP_TYPE_MASK) {
	case KFD_MMAP_TYPE_DOOWBEWW:
		if (!dev)
			wetuwn -ENODEV;
		wetuwn kfd_doowbeww_mmap(dev, pwocess, vma);

	case KFD_MMAP_TYPE_EVENTS:
		wetuwn kfd_event_mmap(pwocess, vma);

	case KFD_MMAP_TYPE_WESEWVED_MEM:
		if (!dev)
			wetuwn -ENODEV;
		wetuwn kfd_wesewved_mem_mmap(dev, pwocess, vma);
	case KFD_MMAP_TYPE_MMIO:
		if (!dev)
			wetuwn -ENODEV;
		wetuwn kfd_mmio_mmap(dev, pwocess, vma);
	}

	wetuwn -EFAUWT;
}
