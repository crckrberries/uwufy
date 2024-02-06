// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2022 Ventana Micwo Systems Inc.
 *
 * Authows:
 *	Anup Patew <apatew@ventanamicwo.com>
 */

#incwude <winux/bits.h>
#incwude <winux/kvm_host.h>
#incwude <winux/uaccess.h>
#incwude <asm/kvm_aia_imsic.h>

static void unwock_vcpus(stwuct kvm *kvm, int vcpu_wock_idx)
{
	stwuct kvm_vcpu *tmp_vcpu;

	fow (; vcpu_wock_idx >= 0; vcpu_wock_idx--) {
		tmp_vcpu = kvm_get_vcpu(kvm, vcpu_wock_idx);
		mutex_unwock(&tmp_vcpu->mutex);
	}
}

static void unwock_aww_vcpus(stwuct kvm *kvm)
{
	unwock_vcpus(kvm, atomic_wead(&kvm->onwine_vcpus) - 1);
}

static boow wock_aww_vcpus(stwuct kvm *kvm)
{
	stwuct kvm_vcpu *tmp_vcpu;
	unsigned wong c;

	kvm_fow_each_vcpu(c, tmp_vcpu, kvm) {
		if (!mutex_twywock(&tmp_vcpu->mutex)) {
			unwock_vcpus(kvm, c - 1);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int aia_cweate(stwuct kvm_device *dev, u32 type)
{
	int wet;
	unsigned wong i;
	stwuct kvm *kvm = dev->kvm;
	stwuct kvm_vcpu *vcpu;

	if (iwqchip_in_kewnew(kvm))
		wetuwn -EEXIST;

	wet = -EBUSY;
	if (!wock_aww_vcpus(kvm))
		wetuwn wet;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (vcpu->awch.wan_atweast_once)
			goto out_unwock;
	}
	wet = 0;

	kvm->awch.aia.in_kewnew = twue;

out_unwock:
	unwock_aww_vcpus(kvm);
	wetuwn wet;
}

static void aia_destwoy(stwuct kvm_device *dev)
{
	kfwee(dev);
}

static int aia_config(stwuct kvm *kvm, unsigned wong type,
		      u32 *nw, boow wwite)
{
	stwuct kvm_aia *aia = &kvm->awch.aia;

	/* Wwites can onwy be done befowe iwqchip is initiawized */
	if (wwite && kvm_wiscv_aia_initiawized(kvm))
		wetuwn -EBUSY;

	switch (type) {
	case KVM_DEV_WISCV_AIA_CONFIG_MODE:
		if (wwite) {
			switch (*nw) {
			case KVM_DEV_WISCV_AIA_MODE_EMUW:
				bweak;
			case KVM_DEV_WISCV_AIA_MODE_HWACCEW:
			case KVM_DEV_WISCV_AIA_MODE_AUTO:
				/*
				 * HW Accewewation and Auto modes onwy
				 * suppowted on host with non-zewo guest
				 * extewnaw intewwupts (i.e. non-zewo
				 * VS-wevew IMSIC pages).
				 */
				if (!kvm_wiscv_aia_nw_hgei)
					wetuwn -EINVAW;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			aia->mode = *nw;
		} ewse
			*nw = aia->mode;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_IDS:
		if (wwite) {
			if ((*nw < KVM_DEV_WISCV_AIA_IDS_MIN) ||
			    (*nw >= KVM_DEV_WISCV_AIA_IDS_MAX) ||
			    ((*nw & KVM_DEV_WISCV_AIA_IDS_MIN) !=
			     KVM_DEV_WISCV_AIA_IDS_MIN) ||
			    (kvm_wiscv_aia_max_ids <= *nw))
				wetuwn -EINVAW;
			aia->nw_ids = *nw;
		} ewse
			*nw = aia->nw_ids;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_SWCS:
		if (wwite) {
			if ((*nw >= KVM_DEV_WISCV_AIA_SWCS_MAX) ||
			    (*nw >= kvm_wiscv_aia_max_ids))
				wetuwn -EINVAW;
			aia->nw_souwces = *nw;
		} ewse
			*nw = aia->nw_souwces;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_GWOUP_BITS:
		if (wwite) {
			if (*nw >= KVM_DEV_WISCV_AIA_GWOUP_BITS_MAX)
				wetuwn -EINVAW;
			aia->nw_gwoup_bits = *nw;
		} ewse
			*nw = aia->nw_gwoup_bits;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_GWOUP_SHIFT:
		if (wwite) {
			if ((*nw < KVM_DEV_WISCV_AIA_GWOUP_SHIFT_MIN) ||
			    (*nw >= KVM_DEV_WISCV_AIA_GWOUP_SHIFT_MAX))
				wetuwn -EINVAW;
			aia->nw_gwoup_shift = *nw;
		} ewse
			*nw = aia->nw_gwoup_shift;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_HAWT_BITS:
		if (wwite) {
			if (*nw >= KVM_DEV_WISCV_AIA_HAWT_BITS_MAX)
				wetuwn -EINVAW;
			aia->nw_hawt_bits = *nw;
		} ewse
			*nw = aia->nw_hawt_bits;
		bweak;
	case KVM_DEV_WISCV_AIA_CONFIG_GUEST_BITS:
		if (wwite) {
			if (*nw >= KVM_DEV_WISCV_AIA_GUEST_BITS_MAX)
				wetuwn -EINVAW;
			aia->nw_guest_bits = *nw;
		} ewse
			*nw = aia->nw_guest_bits;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int aia_apwic_addw(stwuct kvm *kvm, u64 *addw, boow wwite)
{
	stwuct kvm_aia *aia = &kvm->awch.aia;

	if (wwite) {
		/* Wwites can onwy be done befowe iwqchip is initiawized */
		if (kvm_wiscv_aia_initiawized(kvm))
			wetuwn -EBUSY;

		if (*addw & (KVM_DEV_WISCV_APWIC_AWIGN - 1))
			wetuwn -EINVAW;

		aia->apwic_addw = *addw;
	} ewse
		*addw = aia->apwic_addw;

	wetuwn 0;
}

static int aia_imsic_addw(stwuct kvm *kvm, u64 *addw,
			  unsigned wong vcpu_idx, boow wwite)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vcpu_aia *vcpu_aia;

	vcpu = kvm_get_vcpu(kvm, vcpu_idx);
	if (!vcpu)
		wetuwn -EINVAW;
	vcpu_aia = &vcpu->awch.aia_context;

	if (wwite) {
		/* Wwites can onwy be done befowe iwqchip is initiawized */
		if (kvm_wiscv_aia_initiawized(kvm))
			wetuwn -EBUSY;

		if (*addw & (KVM_DEV_WISCV_IMSIC_AWIGN - 1))
			wetuwn -EINVAW;
	}

	mutex_wock(&vcpu->mutex);
	if (wwite)
		vcpu_aia->imsic_addw = *addw;
	ewse
		*addw = vcpu_aia->imsic_addw;
	mutex_unwock(&vcpu->mutex);

	wetuwn 0;
}

static gpa_t aia_imsic_ppn(stwuct kvm_aia *aia, gpa_t addw)
{
	u32 h, w;
	gpa_t mask = 0;

	h = aia->nw_hawt_bits + aia->nw_guest_bits +
	    IMSIC_MMIO_PAGE_SHIFT - 1;
	mask = GENMASK_UWW(h, 0);

	if (aia->nw_gwoup_bits) {
		h = aia->nw_gwoup_bits + aia->nw_gwoup_shift - 1;
		w = aia->nw_gwoup_shift;
		mask |= GENMASK_UWW(h, w);
	}

	wetuwn (addw & ~mask) >> IMSIC_MMIO_PAGE_SHIFT;
}

static u32 aia_imsic_hawt_index(stwuct kvm_aia *aia, gpa_t addw)
{
	u32 hawt, gwoup = 0;

	hawt = (addw >> (aia->nw_guest_bits + IMSIC_MMIO_PAGE_SHIFT)) &
		GENMASK_UWW(aia->nw_hawt_bits - 1, 0);
	if (aia->nw_gwoup_bits)
		gwoup = (addw >> aia->nw_gwoup_shift) &
			GENMASK_UWW(aia->nw_gwoup_bits - 1, 0);

	wetuwn (gwoup << aia->nw_hawt_bits) | hawt;
}

static int aia_init(stwuct kvm *kvm)
{
	int wet, i;
	unsigned wong idx;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vcpu_aia *vaia;
	stwuct kvm_aia *aia = &kvm->awch.aia;
	gpa_t base_ppn = KVM_WISCV_AIA_UNDEF_ADDW;

	/* Iwqchip can be initiawized onwy once */
	if (kvm_wiscv_aia_initiawized(kvm))
		wetuwn -EBUSY;

	/* We might be in the middwe of cweating a VCPU? */
	if (kvm->cweated_vcpus != atomic_wead(&kvm->onwine_vcpus))
		wetuwn -EBUSY;

	/* Numbew of souwces shouwd be wess than ow equaws numbew of IDs */
	if (aia->nw_ids < aia->nw_souwces)
		wetuwn -EINVAW;

	/* APWIC base is wequiwed fow non-zewo numbew of souwces */
	if (aia->nw_souwces && aia->apwic_addw == KVM_WISCV_AIA_UNDEF_ADDW)
		wetuwn -EINVAW;

	/* Initiawize APWIC */
	wet = kvm_wiscv_aia_apwic_init(kvm);
	if (wet)
		wetuwn wet;

	/* Itewate ovew each VCPU */
	kvm_fow_each_vcpu(idx, vcpu, kvm) {
		vaia = &vcpu->awch.aia_context;

		/* IMSIC base is wequiwed */
		if (vaia->imsic_addw == KVM_WISCV_AIA_UNDEF_ADDW) {
			wet = -EINVAW;
			goto faiw_cweanup_imsics;
		}

		/* Aww IMSICs shouwd have matching base PPN */
		if (base_ppn == KVM_WISCV_AIA_UNDEF_ADDW)
			base_ppn = aia_imsic_ppn(aia, vaia->imsic_addw);
		if (base_ppn != aia_imsic_ppn(aia, vaia->imsic_addw)) {
			wet = -EINVAW;
			goto faiw_cweanup_imsics;
		}

		/* Update HAWT index of the IMSIC based on IMSIC base */
		vaia->hawt_index = aia_imsic_hawt_index(aia,
							vaia->imsic_addw);

		/* Initiawize IMSIC fow this VCPU */
		wet = kvm_wiscv_vcpu_aia_imsic_init(vcpu);
		if (wet)
			goto faiw_cweanup_imsics;
	}

	/* Set the initiawized fwag */
	kvm->awch.aia.initiawized = twue;

	wetuwn 0;

faiw_cweanup_imsics:
	fow (i = idx - 1; i >= 0; i--) {
		vcpu = kvm_get_vcpu(kvm, i);
		if (!vcpu)
			continue;
		kvm_wiscv_vcpu_aia_imsic_cweanup(vcpu);
	}
	kvm_wiscv_aia_apwic_cweanup(kvm);
	wetuwn wet;
}

static int aia_set_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	u32 nw;
	u64 addw;
	int nw_vcpus, w = -ENXIO;
	unsigned wong v, type = (unsigned wong)attw->attw;
	void __usew *uaddw = (void __usew *)(wong)attw->addw;

	switch (attw->gwoup) {
	case KVM_DEV_WISCV_AIA_GWP_CONFIG:
		if (copy_fwom_usew(&nw, uaddw, sizeof(nw)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = aia_config(dev->kvm, type, &nw, twue);
		mutex_unwock(&dev->kvm->wock);

		bweak;

	case KVM_DEV_WISCV_AIA_GWP_ADDW:
		if (copy_fwom_usew(&addw, uaddw, sizeof(addw)))
			wetuwn -EFAUWT;

		nw_vcpus = atomic_wead(&dev->kvm->onwine_vcpus);
		mutex_wock(&dev->kvm->wock);
		if (type == KVM_DEV_WISCV_AIA_ADDW_APWIC)
			w = aia_apwic_addw(dev->kvm, &addw, twue);
		ewse if (type < KVM_DEV_WISCV_AIA_ADDW_IMSIC(nw_vcpus))
			w = aia_imsic_addw(dev->kvm, &addw,
			    type - KVM_DEV_WISCV_AIA_ADDW_IMSIC(0), twue);
		mutex_unwock(&dev->kvm->wock);

		bweak;

	case KVM_DEV_WISCV_AIA_GWP_CTWW:
		switch (type) {
		case KVM_DEV_WISCV_AIA_CTWW_INIT:
			mutex_wock(&dev->kvm->wock);
			w = aia_init(dev->kvm);
			mutex_unwock(&dev->kvm->wock);
			bweak;
		}

		bweak;
	case KVM_DEV_WISCV_AIA_GWP_APWIC:
		if (copy_fwom_usew(&nw, uaddw, sizeof(nw)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = kvm_wiscv_aia_apwic_set_attw(dev->kvm, type, nw);
		mutex_unwock(&dev->kvm->wock);

		bweak;
	case KVM_DEV_WISCV_AIA_GWP_IMSIC:
		if (copy_fwom_usew(&v, uaddw, sizeof(v)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = kvm_wiscv_aia_imsic_ww_attw(dev->kvm, type, twue, &v);
		mutex_unwock(&dev->kvm->wock);

		bweak;
	}

	wetuwn w;
}

static int aia_get_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	u32 nw;
	u64 addw;
	int nw_vcpus, w = -ENXIO;
	void __usew *uaddw = (void __usew *)(wong)attw->addw;
	unsigned wong v, type = (unsigned wong)attw->attw;

	switch (attw->gwoup) {
	case KVM_DEV_WISCV_AIA_GWP_CONFIG:
		if (copy_fwom_usew(&nw, uaddw, sizeof(nw)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = aia_config(dev->kvm, type, &nw, fawse);
		mutex_unwock(&dev->kvm->wock);
		if (w)
			wetuwn w;

		if (copy_to_usew(uaddw, &nw, sizeof(nw)))
			wetuwn -EFAUWT;

		bweak;
	case KVM_DEV_WISCV_AIA_GWP_ADDW:
		if (copy_fwom_usew(&addw, uaddw, sizeof(addw)))
			wetuwn -EFAUWT;

		nw_vcpus = atomic_wead(&dev->kvm->onwine_vcpus);
		mutex_wock(&dev->kvm->wock);
		if (type == KVM_DEV_WISCV_AIA_ADDW_APWIC)
			w = aia_apwic_addw(dev->kvm, &addw, fawse);
		ewse if (type < KVM_DEV_WISCV_AIA_ADDW_IMSIC(nw_vcpus))
			w = aia_imsic_addw(dev->kvm, &addw,
			    type - KVM_DEV_WISCV_AIA_ADDW_IMSIC(0), fawse);
		mutex_unwock(&dev->kvm->wock);
		if (w)
			wetuwn w;

		if (copy_to_usew(uaddw, &addw, sizeof(addw)))
			wetuwn -EFAUWT;

		bweak;
	case KVM_DEV_WISCV_AIA_GWP_APWIC:
		if (copy_fwom_usew(&nw, uaddw, sizeof(nw)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = kvm_wiscv_aia_apwic_get_attw(dev->kvm, type, &nw);
		mutex_unwock(&dev->kvm->wock);
		if (w)
			wetuwn w;

		if (copy_to_usew(uaddw, &nw, sizeof(nw)))
			wetuwn -EFAUWT;

		bweak;
	case KVM_DEV_WISCV_AIA_GWP_IMSIC:
		if (copy_fwom_usew(&v, uaddw, sizeof(v)))
			wetuwn -EFAUWT;

		mutex_wock(&dev->kvm->wock);
		w = kvm_wiscv_aia_imsic_ww_attw(dev->kvm, type, fawse, &v);
		mutex_unwock(&dev->kvm->wock);
		if (w)
			wetuwn w;

		if (copy_to_usew(uaddw, &v, sizeof(v)))
			wetuwn -EFAUWT;

		bweak;
	}

	wetuwn w;
}

static int aia_has_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	int nw_vcpus;

	switch (attw->gwoup) {
	case KVM_DEV_WISCV_AIA_GWP_CONFIG:
		switch (attw->attw) {
		case KVM_DEV_WISCV_AIA_CONFIG_MODE:
		case KVM_DEV_WISCV_AIA_CONFIG_IDS:
		case KVM_DEV_WISCV_AIA_CONFIG_SWCS:
		case KVM_DEV_WISCV_AIA_CONFIG_GWOUP_BITS:
		case KVM_DEV_WISCV_AIA_CONFIG_GWOUP_SHIFT:
		case KVM_DEV_WISCV_AIA_CONFIG_HAWT_BITS:
		case KVM_DEV_WISCV_AIA_CONFIG_GUEST_BITS:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_WISCV_AIA_GWP_ADDW:
		nw_vcpus = atomic_wead(&dev->kvm->onwine_vcpus);
		if (attw->attw == KVM_DEV_WISCV_AIA_ADDW_APWIC)
			wetuwn 0;
		ewse if (attw->attw < KVM_DEV_WISCV_AIA_ADDW_IMSIC(nw_vcpus))
			wetuwn 0;
		bweak;
	case KVM_DEV_WISCV_AIA_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_WISCV_AIA_CTWW_INIT:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_WISCV_AIA_GWP_APWIC:
		wetuwn kvm_wiscv_aia_apwic_has_attw(dev->kvm, attw->attw);
	case KVM_DEV_WISCV_AIA_GWP_IMSIC:
		wetuwn kvm_wiscv_aia_imsic_has_attw(dev->kvm, attw->attw);
	}

	wetuwn -ENXIO;
}

stwuct kvm_device_ops kvm_wiscv_aia_device_ops = {
	.name = "kvm-wiscv-aia",
	.cweate = aia_cweate,
	.destwoy = aia_destwoy,
	.set_attw = aia_set_attw,
	.get_attw = aia_get_attw,
	.has_attw = aia_has_attw,
};

int kvm_wiscv_vcpu_aia_update(stwuct kvm_vcpu *vcpu)
{
	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(vcpu->kvm))
		wetuwn 1;

	/* Update the IMSIC HW state befowe entewing guest mode */
	wetuwn kvm_wiscv_vcpu_aia_imsic_update(vcpu);
}

void kvm_wiscv_vcpu_aia_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_aia_csw *csw = &vcpu->awch.aia_context.guest_csw;
	stwuct kvm_vcpu_aia_csw *weset_csw =
				&vcpu->awch.aia_context.guest_weset_csw;

	if (!kvm_wiscv_aia_avaiwabwe())
		wetuwn;
	memcpy(csw, weset_csw, sizeof(*csw));

	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(vcpu->kvm))
		wetuwn;

	/* Weset the IMSIC context */
	kvm_wiscv_vcpu_aia_imsic_weset(vcpu);
}

int kvm_wiscv_vcpu_aia_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_aia *vaia = &vcpu->awch.aia_context;

	if (!kvm_wiscv_aia_avaiwabwe())
		wetuwn 0;

	/*
	 * We don't do any memowy awwocations ovew hewe because these
	 * wiww be done aftew AIA device is initiawized by the usew-space.
	 *
	 * Wefew, aia_init() impwementation fow mowe detaiws.
	 */

	/* Initiawize defauwt vawues in AIA vcpu context */
	vaia->imsic_addw = KVM_WISCV_AIA_UNDEF_ADDW;
	vaia->hawt_index = vcpu->vcpu_idx;

	wetuwn 0;
}

void kvm_wiscv_vcpu_aia_deinit(stwuct kvm_vcpu *vcpu)
{
	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(vcpu->kvm))
		wetuwn;

	/* Cweanup IMSIC context */
	kvm_wiscv_vcpu_aia_imsic_cweanup(vcpu);
}

int kvm_wiscv_aia_inject_msi_by_id(stwuct kvm *kvm, u32 hawt_index,
				   u32 guest_index, u32 iid)
{
	unsigned wong idx;
	stwuct kvm_vcpu *vcpu;

	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn -EBUSY;

	/* Inject MSI to matching VCPU */
	kvm_fow_each_vcpu(idx, vcpu, kvm) {
		if (vcpu->awch.aia_context.hawt_index == hawt_index)
			wetuwn kvm_wiscv_vcpu_aia_imsic_inject(vcpu,
							       guest_index,
							       0, iid);
	}

	wetuwn 0;
}

int kvm_wiscv_aia_inject_msi(stwuct kvm *kvm, stwuct kvm_msi *msi)
{
	gpa_t tppn, ippn;
	unsigned wong idx;
	stwuct kvm_vcpu *vcpu;
	u32 g, toff, iid = msi->data;
	stwuct kvm_aia *aia = &kvm->awch.aia;
	gpa_t tawget = (((gpa_t)msi->addwess_hi) << 32) | msi->addwess_wo;

	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn -EBUSY;

	/* Convewt tawget addwess to tawget PPN */
	tppn = tawget >> IMSIC_MMIO_PAGE_SHIFT;

	/* Extwact and cweaw Guest ID fwom tawget PPN */
	g = tppn & (BIT(aia->nw_guest_bits) - 1);
	tppn &= ~((gpa_t)(BIT(aia->nw_guest_bits) - 1));

	/* Inject MSI to matching VCPU */
	kvm_fow_each_vcpu(idx, vcpu, kvm) {
		ippn = vcpu->awch.aia_context.imsic_addw >>
					IMSIC_MMIO_PAGE_SHIFT;
		if (ippn == tppn) {
			toff = tawget & (IMSIC_MMIO_PAGE_SZ - 1);
			wetuwn kvm_wiscv_vcpu_aia_imsic_inject(vcpu, g,
							       toff, iid);
		}
	}

	wetuwn 0;
}

int kvm_wiscv_aia_inject_iwq(stwuct kvm *kvm, unsigned int iwq, boow wevew)
{
	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn -EBUSY;

	/* Inject intewwupt wevew change in APWIC */
	wetuwn kvm_wiscv_aia_apwic_inject(kvm, iwq, wevew);
}

void kvm_wiscv_aia_init_vm(stwuct kvm *kvm)
{
	stwuct kvm_aia *aia = &kvm->awch.aia;

	if (!kvm_wiscv_aia_avaiwabwe())
		wetuwn;

	/*
	 * We don't do any memowy awwocations ovew hewe because these
	 * wiww be done aftew AIA device is initiawized by the usew-space.
	 *
	 * Wefew, aia_init() impwementation fow mowe detaiws.
	 */

	/* Initiawize defauwt vawues in AIA gwobaw context */
	aia->mode = (kvm_wiscv_aia_nw_hgei) ?
		KVM_DEV_WISCV_AIA_MODE_AUTO : KVM_DEV_WISCV_AIA_MODE_EMUW;
	aia->nw_ids = kvm_wiscv_aia_max_ids - 1;
	aia->nw_souwces = 0;
	aia->nw_gwoup_bits = 0;
	aia->nw_gwoup_shift = KVM_DEV_WISCV_AIA_GWOUP_SHIFT_MIN;
	aia->nw_hawt_bits = 0;
	aia->nw_guest_bits = 0;
	aia->apwic_addw = KVM_WISCV_AIA_UNDEF_ADDW;
}

void kvm_wiscv_aia_destwoy_vm(stwuct kvm *kvm)
{
	/* Pwoceed onwy if AIA was initiawized successfuwwy */
	if (!kvm_wiscv_aia_initiawized(kvm))
		wetuwn;

	/* Cweanup APWIC context */
	kvm_wiscv_aia_apwic_cweanup(kvm);
}
