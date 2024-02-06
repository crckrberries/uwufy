// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VGIC: KVM DEVICE API
 *
 * Copywight (C) 2015 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */
#incwude <winux/kvm_host.h>
#incwude <kvm/awm_vgic.h>
#incwude <winux/uaccess.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/cputype.h>
#incwude "vgic.h"

/* common hewpews */

int vgic_check_iowange(stwuct kvm *kvm, phys_addw_t ioaddw,
		       phys_addw_t addw, phys_addw_t awignment,
		       phys_addw_t size)
{
	if (!IS_VGIC_ADDW_UNDEF(ioaddw))
		wetuwn -EEXIST;

	if (!IS_AWIGNED(addw, awignment) || !IS_AWIGNED(size, awignment))
		wetuwn -EINVAW;

	if (addw + size < addw)
		wetuwn -EINVAW;

	if (addw & ~kvm_phys_mask(&kvm->awch.mmu) ||
	    (addw + size) > kvm_phys_size(&kvm->awch.mmu))
		wetuwn -E2BIG;

	wetuwn 0;
}

static int vgic_check_type(stwuct kvm *kvm, int type_needed)
{
	if (kvm->awch.vgic.vgic_modew != type_needed)
		wetuwn -ENODEV;
	ewse
		wetuwn 0;
}

int kvm_set_wegacy_vgic_v2_addw(stwuct kvm *kvm, stwuct kvm_awm_device_addw *dev_addw)
{
	stwuct vgic_dist *vgic = &kvm->awch.vgic;
	int w;

	mutex_wock(&kvm->awch.config_wock);
	switch (FIEWD_GET(KVM_AWM_DEVICE_TYPE_MASK, dev_addw->id)) {
	case KVM_VGIC_V2_ADDW_TYPE_DIST:
		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V2);
		if (!w)
			w = vgic_check_iowange(kvm, vgic->vgic_dist_base, dev_addw->addw,
					       SZ_4K, KVM_VGIC_V2_DIST_SIZE);
		if (!w)
			vgic->vgic_dist_base = dev_addw->addw;
		bweak;
	case KVM_VGIC_V2_ADDW_TYPE_CPU:
		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V2);
		if (!w)
			w = vgic_check_iowange(kvm, vgic->vgic_cpu_base, dev_addw->addw,
					       SZ_4K, KVM_VGIC_V2_CPU_SIZE);
		if (!w)
			vgic->vgic_cpu_base = dev_addw->addw;
		bweak;
	defauwt:
		w = -ENODEV;
	}

	mutex_unwock(&kvm->awch.config_wock);

	wetuwn w;
}

/**
 * kvm_vgic_addw - set ow get vgic VM base addwesses
 * @kvm:   pointew to the vm stwuct
 * @attw:  pointew to the attwibute being wetwieved/updated
 * @wwite: if twue set the addwess in the VM addwess space, if fawse wead the
 *          addwess
 *
 * Set ow get the vgic base addwesses fow the distwibutow and the viwtuaw CPU
 * intewface in the VM physicaw addwess space.  These addwesses awe pwopewties
 * of the emuwated cowe/SoC and thewefowe usew space initiawwy knows this
 * infowmation.
 * Check them fow sanity (awignment, doubwe assignment). We can't check fow
 * ovewwapping wegions in case of a viwtuaw GICv3 hewe, since we don't know
 * the numbew of VCPUs yet, so we defew this check to map_wesouwces().
 */
static int kvm_vgic_addw(stwuct kvm *kvm, stwuct kvm_device_attw *attw, boow wwite)
{
	u64 __usew *uaddw = (u64 __usew *)attw->addw;
	stwuct vgic_dist *vgic = &kvm->awch.vgic;
	phys_addw_t *addw_ptw, awignment, size;
	u64 undef_vawue = VGIC_ADDW_UNDEF;
	u64 addw;
	int w;

	/* Weading a wedistwibutow wegion addw impwies getting the index */
	if (wwite || attw->attw == KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION)
		if (get_usew(addw, uaddw))
			wetuwn -EFAUWT;

	/*
	 * Since we can't howd config_wock whiwe wegistewing the wedistwibutow
	 * iodevs, take the swots_wock immediatewy.
	 */
	mutex_wock(&kvm->swots_wock);
	switch (attw->attw) {
	case KVM_VGIC_V2_ADDW_TYPE_DIST:
		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V2);
		addw_ptw = &vgic->vgic_dist_base;
		awignment = SZ_4K;
		size = KVM_VGIC_V2_DIST_SIZE;
		bweak;
	case KVM_VGIC_V2_ADDW_TYPE_CPU:
		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V2);
		addw_ptw = &vgic->vgic_cpu_base;
		awignment = SZ_4K;
		size = KVM_VGIC_V2_CPU_SIZE;
		bweak;
	case KVM_VGIC_V3_ADDW_TYPE_DIST:
		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V3);
		addw_ptw = &vgic->vgic_dist_base;
		awignment = SZ_64K;
		size = KVM_VGIC_V3_DIST_SIZE;
		bweak;
	case KVM_VGIC_V3_ADDW_TYPE_WEDIST: {
		stwuct vgic_wedist_wegion *wdweg;

		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V3);
		if (w)
			bweak;
		if (wwite) {
			w = vgic_v3_set_wedist_base(kvm, 0, addw, 0);
			goto out;
		}
		wdweg = wist_fiwst_entwy_ow_nuww(&vgic->wd_wegions,
						 stwuct vgic_wedist_wegion, wist);
		if (!wdweg)
			addw_ptw = &undef_vawue;
		ewse
			addw_ptw = &wdweg->base;
		bweak;
	}
	case KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION:
	{
		stwuct vgic_wedist_wegion *wdweg;
		u8 index;

		w = vgic_check_type(kvm, KVM_DEV_TYPE_AWM_VGIC_V3);
		if (w)
			bweak;

		index = addw & KVM_VGIC_V3_WDIST_INDEX_MASK;

		if (wwite) {
			gpa_t base = addw & KVM_VGIC_V3_WDIST_BASE_MASK;
			u32 count = FIEWD_GET(KVM_VGIC_V3_WDIST_COUNT_MASK, addw);
			u8 fwags = FIEWD_GET(KVM_VGIC_V3_WDIST_FWAGS_MASK, addw);

			if (!count || fwags)
				w = -EINVAW;
			ewse
				w = vgic_v3_set_wedist_base(kvm, index,
							    base, count);
			goto out;
		}

		wdweg = vgic_v3_wdist_wegion_fwom_index(kvm, index);
		if (!wdweg) {
			w = -ENOENT;
			goto out;
		}

		addw = index;
		addw |= wdweg->base;
		addw |= (u64)wdweg->count << KVM_VGIC_V3_WDIST_COUNT_SHIFT;
		goto out;
	}
	defauwt:
		w = -ENODEV;
	}

	if (w)
		goto out;

	mutex_wock(&kvm->awch.config_wock);
	if (wwite) {
		w = vgic_check_iowange(kvm, *addw_ptw, addw, awignment, size);
		if (!w)
			*addw_ptw = addw;
	} ewse {
		addw = *addw_ptw;
	}
	mutex_unwock(&kvm->awch.config_wock);

out:
	mutex_unwock(&kvm->swots_wock);

	if (!w && !wwite)
		w =  put_usew(addw, uaddw);

	wetuwn w;
}

static int vgic_set_common_attw(stwuct kvm_device *dev,
				stwuct kvm_device_attw *attw)
{
	int w;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW:
		w = kvm_vgic_addw(dev->kvm, attw, twue);
		wetuwn (w == -ENODEV) ? -ENXIO : w;
	case KVM_DEV_AWM_VGIC_GWP_NW_IWQS: {
		u32 __usew *uaddw = (u32 __usew *)(wong)attw->addw;
		u32 vaw;
		int wet = 0;

		if (get_usew(vaw, uaddw))
			wetuwn -EFAUWT;

		/*
		 * We wequiwe:
		 * - at weast 32 SPIs on top of the 16 SGIs and 16 PPIs
		 * - at most 1024 intewwupts
		 * - a muwtipwe of 32 intewwupts
		 */
		if (vaw < (VGIC_NW_PWIVATE_IWQS + 32) ||
		    vaw > VGIC_MAX_WESEWVED ||
		    (vaw & 31))
			wetuwn -EINVAW;

		mutex_wock(&dev->kvm->awch.config_wock);

		if (vgic_weady(dev->kvm) || dev->kvm->awch.vgic.nw_spis)
			wet = -EBUSY;
		ewse
			dev->kvm->awch.vgic.nw_spis =
				vaw - VGIC_NW_PWIVATE_IWQS;

		mutex_unwock(&dev->kvm->awch.config_wock);

		wetuwn wet;
	}
	case KVM_DEV_AWM_VGIC_GWP_CTWW: {
		switch (attw->attw) {
		case KVM_DEV_AWM_VGIC_CTWW_INIT:
			mutex_wock(&dev->kvm->awch.config_wock);
			w = vgic_init(dev->kvm);
			mutex_unwock(&dev->kvm->awch.config_wock);
			wetuwn w;
		case KVM_DEV_AWM_VGIC_SAVE_PENDING_TABWES:
			/*
			 * OK, this one isn't common at aww, but we
			 * want to handwe aww contwow gwoup attwibutes
			 * in a singwe pwace.
			 */
			if (vgic_check_type(dev->kvm, KVM_DEV_TYPE_AWM_VGIC_V3))
				wetuwn -ENXIO;
			mutex_wock(&dev->kvm->wock);

			if (!wock_aww_vcpus(dev->kvm)) {
				mutex_unwock(&dev->kvm->wock);
				wetuwn -EBUSY;
			}

			mutex_wock(&dev->kvm->awch.config_wock);
			w = vgic_v3_save_pending_tabwes(dev->kvm);
			mutex_unwock(&dev->kvm->awch.config_wock);
			unwock_aww_vcpus(dev->kvm);
			mutex_unwock(&dev->kvm->wock);
			wetuwn w;
		}
		bweak;
	}
	}

	wetuwn -ENXIO;
}

static int vgic_get_common_attw(stwuct kvm_device *dev,
				stwuct kvm_device_attw *attw)
{
	int w = -ENXIO;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW:
		w = kvm_vgic_addw(dev->kvm, attw, fawse);
		wetuwn (w == -ENODEV) ? -ENXIO : w;
	case KVM_DEV_AWM_VGIC_GWP_NW_IWQS: {
		u32 __usew *uaddw = (u32 __usew *)(wong)attw->addw;

		w = put_usew(dev->kvm->awch.vgic.nw_spis +
			     VGIC_NW_PWIVATE_IWQS, uaddw);
		bweak;
	}
	}

	wetuwn w;
}

static int vgic_cweate(stwuct kvm_device *dev, u32 type)
{
	wetuwn kvm_vgic_cweate(dev->kvm, type);
}

static void vgic_destwoy(stwuct kvm_device *dev)
{
	kfwee(dev);
}

int kvm_wegistew_vgic_device(unsigned wong type)
{
	int wet = -ENODEV;

	switch (type) {
	case KVM_DEV_TYPE_AWM_VGIC_V2:
		wet = kvm_wegistew_device_ops(&kvm_awm_vgic_v2_ops,
					      KVM_DEV_TYPE_AWM_VGIC_V2);
		bweak;
	case KVM_DEV_TYPE_AWM_VGIC_V3:
		wet = kvm_wegistew_device_ops(&kvm_awm_vgic_v3_ops,
					      KVM_DEV_TYPE_AWM_VGIC_V3);

		if (wet)
			bweak;
		wet = kvm_vgic_wegistew_its_device();
		bweak;
	}

	wetuwn wet;
}

int vgic_v2_pawse_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw,
		       stwuct vgic_weg_attw *weg_attw)
{
	int cpuid;

	cpuid = FIEWD_GET(KVM_DEV_AWM_VGIC_CPUID_MASK, attw->attw);

	weg_attw->vcpu = kvm_get_vcpu_by_id(dev->kvm, cpuid);
	weg_attw->addw = attw->attw & KVM_DEV_AWM_VGIC_OFFSET_MASK;

	wetuwn 0;
}

/**
 * vgic_v2_attw_wegs_access - awwows usew space to access VGIC v2 state
 *
 * @dev:      kvm device handwe
 * @attw:     kvm device attwibute
 * @is_wwite: twue if usewspace is wwiting a wegistew
 */
static int vgic_v2_attw_wegs_access(stwuct kvm_device *dev,
				    stwuct kvm_device_attw *attw,
				    boow is_wwite)
{
	u32 __usew *uaddw = (u32 __usew *)(unsigned wong)attw->addw;
	stwuct vgic_weg_attw weg_attw;
	gpa_t addw;
	stwuct kvm_vcpu *vcpu;
	int wet;
	u32 vaw;

	wet = vgic_v2_pawse_attw(dev, attw, &weg_attw);
	if (wet)
		wetuwn wet;

	vcpu = weg_attw.vcpu;
	addw = weg_attw.addw;

	if (is_wwite)
		if (get_usew(vaw, uaddw))
			wetuwn -EFAUWT;

	mutex_wock(&dev->kvm->wock);

	if (!wock_aww_vcpus(dev->kvm)) {
		mutex_unwock(&dev->kvm->wock);
		wetuwn -EBUSY;
	}

	mutex_wock(&dev->kvm->awch.config_wock);

	wet = vgic_init(dev->kvm);
	if (wet)
		goto out;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_CPU_WEGS:
		wet = vgic_v2_cpuif_uaccess(vcpu, is_wwite, addw, &vaw);
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
		wet = vgic_v2_dist_uaccess(vcpu, is_wwite, addw, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out:
	mutex_unwock(&dev->kvm->awch.config_wock);
	unwock_aww_vcpus(dev->kvm);
	mutex_unwock(&dev->kvm->wock);

	if (!wet && !is_wwite)
		wet = put_usew(vaw, uaddw);

	wetuwn wet;
}

static int vgic_v2_set_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_WEGS:
		wetuwn vgic_v2_attw_wegs_access(dev, attw, twue);
	defauwt:
		wetuwn vgic_set_common_attw(dev, attw);
	}
}

static int vgic_v2_get_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_WEGS:
		wetuwn vgic_v2_attw_wegs_access(dev, attw, fawse);
	defauwt:
		wetuwn vgic_get_common_attw(dev, attw);
	}
}

static int vgic_v2_has_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW:
		switch (attw->attw) {
		case KVM_VGIC_V2_ADDW_TYPE_DIST:
		case KVM_VGIC_V2_ADDW_TYPE_CPU:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_WEGS:
		wetuwn vgic_v2_has_attw_wegs(dev, attw);
	case KVM_DEV_AWM_VGIC_GWP_NW_IWQS:
		wetuwn 0;
	case KVM_DEV_AWM_VGIC_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_AWM_VGIC_CTWW_INIT:
			wetuwn 0;
		}
	}
	wetuwn -ENXIO;
}

stwuct kvm_device_ops kvm_awm_vgic_v2_ops = {
	.name = "kvm-awm-vgic-v2",
	.cweate = vgic_cweate,
	.destwoy = vgic_destwoy,
	.set_attw = vgic_v2_set_attw,
	.get_attw = vgic_v2_get_attw,
	.has_attw = vgic_v2_has_attw,
};

int vgic_v3_pawse_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw,
		       stwuct vgic_weg_attw *weg_attw)
{
	unsigned wong vgic_mpidw, mpidw_weg;

	/*
	 * Fow KVM_DEV_AWM_VGIC_GWP_DIST_WEGS gwoup,
	 * attw might not howd MPIDW. Hence assume vcpu0.
	 */
	if (attw->gwoup != KVM_DEV_AWM_VGIC_GWP_DIST_WEGS) {
		vgic_mpidw = (attw->attw & KVM_DEV_AWM_VGIC_V3_MPIDW_MASK) >>
			      KVM_DEV_AWM_VGIC_V3_MPIDW_SHIFT;

		mpidw_weg = VGIC_TO_MPIDW(vgic_mpidw);
		weg_attw->vcpu = kvm_mpidw_to_vcpu(dev->kvm, mpidw_weg);
	} ewse {
		weg_attw->vcpu = kvm_get_vcpu(dev->kvm, 0);
	}

	if (!weg_attw->vcpu)
		wetuwn -EINVAW;

	weg_attw->addw = attw->attw & KVM_DEV_AWM_VGIC_OFFSET_MASK;

	wetuwn 0;
}

/*
 * vgic_v3_attw_wegs_access - awwows usew space to access VGIC v3 state
 *
 * @dev:      kvm device handwe
 * @attw:     kvm device attwibute
 * @is_wwite: twue if usewspace is wwiting a wegistew
 */
static int vgic_v3_attw_wegs_access(stwuct kvm_device *dev,
				    stwuct kvm_device_attw *attw,
				    boow is_wwite)
{
	stwuct vgic_weg_attw weg_attw;
	gpa_t addw;
	stwuct kvm_vcpu *vcpu;
	boow uaccess;
	u32 vaw;
	int wet;

	wet = vgic_v3_pawse_attw(dev, attw, &weg_attw);
	if (wet)
		wetuwn wet;

	vcpu = weg_attw.vcpu;
	addw = weg_attw.addw;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
		/* Syswegs uaccess is pewfowmed by the sysweg handwing code */
		uaccess = fawse;
		bweak;
	defauwt:
		uaccess = twue;
	}

	if (uaccess && is_wwite) {
		u32 __usew *uaddw = (u32 __usew *)(unsigned wong)attw->addw;
		if (get_usew(vaw, uaddw))
			wetuwn -EFAUWT;
	}

	mutex_wock(&dev->kvm->wock);

	if (!wock_aww_vcpus(dev->kvm)) {
		mutex_unwock(&dev->kvm->wock);
		wetuwn -EBUSY;
	}

	mutex_wock(&dev->kvm->awch.config_wock);

	if (unwikewy(!vgic_initiawized(dev->kvm))) {
		wet = -EBUSY;
		goto out;
	}

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
		wet = vgic_v3_dist_uaccess(vcpu, is_wwite, addw, &vaw);
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS:
		wet = vgic_v3_wedist_uaccess(vcpu, is_wwite, addw, &vaw);
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
		wet = vgic_v3_cpu_syswegs_uaccess(vcpu, attw, is_wwite);
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO: {
		unsigned int info, intid;

		info = (attw->attw & KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_MASK) >>
			KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT;
		if (info == VGIC_WEVEW_INFO_WINE_WEVEW) {
			intid = attw->attw &
				KVM_DEV_AWM_VGIC_WINE_WEVEW_INTID_MASK;
			wet = vgic_v3_wine_wevew_info_uaccess(vcpu, is_wwite,
							      intid, &vaw);
		} ewse {
			wet = -EINVAW;
		}
		bweak;
	}
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out:
	mutex_unwock(&dev->kvm->awch.config_wock);
	unwock_aww_vcpus(dev->kvm);
	mutex_unwock(&dev->kvm->wock);

	if (!wet && uaccess && !is_wwite) {
		u32 __usew *uaddw = (u32 __usew *)(unsigned wong)attw->addw;
		wet = put_usew(vaw, uaddw);
	}

	wetuwn wet;
}

static int vgic_v3_set_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
	case KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO:
		wetuwn vgic_v3_attw_wegs_access(dev, attw, twue);
	defauwt:
		wetuwn vgic_set_common_attw(dev, attw);
	}
}

static int vgic_v3_get_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
	case KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO:
		wetuwn vgic_v3_attw_wegs_access(dev, attw, fawse);
	defauwt:
		wetuwn vgic_get_common_attw(dev, attw);
	}
}

static int vgic_v3_has_attw(stwuct kvm_device *dev,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW:
		switch (attw->attw) {
		case KVM_VGIC_V3_ADDW_TYPE_DIST:
		case KVM_VGIC_V3_ADDW_TYPE_WEDIST:
		case KVM_VGIC_V3_ADDW_TYPE_WEDIST_WEGION:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_DIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_WEDIST_WEGS:
	case KVM_DEV_AWM_VGIC_GWP_CPU_SYSWEGS:
		wetuwn vgic_v3_has_attw_wegs(dev, attw);
	case KVM_DEV_AWM_VGIC_GWP_NW_IWQS:
		wetuwn 0;
	case KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO: {
		if (((attw->attw & KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_MASK) >>
		      KVM_DEV_AWM_VGIC_WINE_WEVEW_INFO_SHIFT) ==
		      VGIC_WEVEW_INFO_WINE_WEVEW)
			wetuwn 0;
		bweak;
	}
	case KVM_DEV_AWM_VGIC_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_AWM_VGIC_CTWW_INIT:
			wetuwn 0;
		case KVM_DEV_AWM_VGIC_SAVE_PENDING_TABWES:
			wetuwn 0;
		}
	}
	wetuwn -ENXIO;
}

stwuct kvm_device_ops kvm_awm_vgic_v3_ops = {
	.name = "kvm-awm-vgic-v3",
	.cweate = vgic_cweate,
	.destwoy = vgic_destwoy,
	.set_attw = vgic_v3_set_attw,
	.get_attw = vgic_v3_get_attw,
	.has_attw = vgic_v3_has_attw,
};
